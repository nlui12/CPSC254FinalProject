#include "notesApp.h"
#include <gtkmm/stock.h>
#include <iostream>

notesApp::notesApp()
: m_Box(Gtk::ORIENTATION_VERTICAL),
  d_Box(Gtk::ORIENTATION_VERTICAL),
  h1_Box(Gtk::ORIENTATION_HORIZONTAL),
  h2_Box(Gtk::ORIENTATION_HORIZONTAL),
  h3_Box(Gtk::ORIENTATION_HORIZONTAL)

{
  set_title("Notes");
  set_default_size(800,400);


  add(m_Box);

  //d_Box.add(h2_Box);
  //h2_Box.set_vexpand(false);

  //File|New sub menu:
  actionGroup = Gtk::ActionGroup::create();
  actionGroup->add(Gtk::Action::create("FileNewStandard",
              Gtk::Stock::NEW, "_New", "Create a new file"),
          sigc::mem_fun(*this, &notesApp::on_menu_file_new_generic));

  actionGroup->add(Gtk::Action::create("FileNewFile",
              Gtk::Stock::NEW, "New File", "Create a new foo"),
          sigc::mem_fun(*this, &notesApp::on_menu_file_new_generic));

  actionGroup->add(Gtk::Action::create("FileNewWindow",
              Gtk::Stock::NEW, "_New Window", "Create a new goo"),
          sigc::mem_fun(*this, &notesApp::on_menu_file_new_generic));

  actionGroup->add(Gtk::Action::create("FileMenu", "File"));
  actionGroup->add(Gtk::Action::create("FileNew", Gtk::Stock::NEW));
  actionGroup->add(Gtk::Action::create("FileQuit", Gtk::Stock::QUIT),
          sigc::mem_fun(*this, &notesApp::on_menu_file_quit));

  myUIManager = Gtk::UIManager::create();

  myUIManager->insert_action_group(actionGroup);
  add_accel_group(myUIManager->get_accel_group());

Glib::ustring ui_info =
        "<ui>"
        "  <menubar name='MenuBar'>"
        "    <menu action='FileMenu'>"
        "      <menu action='FileNew'>"
        "        <menuitem action='FileNewStandard'/>"
        "        <menuitem action='FileNewFile'/>"
        "        <menuitem action='FileNewWindow'/>"
        "      </menu>"
        "      <separator/>"
        "      <menuitem action='FileQuit'/>"
        "    </menu>"
        "    <menu action='EditMenu'>"
        "      <menuitem action='EditCopy'/>"
        "      <menuitem action='EditPaste'/>"
        "      <menuitem action='EditSomething'/>"
        "    </menu>"
        "    <menu action='ChoicesMenu'>"
        "      <menuitem action='ChoiceOne'/>"
        "      <menuitem action='ChoiceTwo'/>"
        "    </menu>"
        "    <menu action='HelpMenu'>"
        "      <menuitem action='HelpAbout'/>"
        "    </menu>"
        "  </menubar>"
        "  <toolbar  name='ToolBar'>"
        "    <toolitem action='FileNewStandard'/>"
        "    <toolitem action='FileQuit'/>"
        "  </toolbar>"
        "</ui>";

  try
  {
    myUIManager->add_ui_from_string(ui_info);
  }
  catch(const Glib::Error& ex)
  {
    std::cerr << "building menus failed: " <<  ex.what();
  }
  //add menu widget menu container
  Gtk::Widget* pMenubar = myUIManager->get_widget("/MenuBar");
  if(pMenubar)
    m_Box.pack_start(*pMenubar, Gtk::PACK_SHRINK);

  //add toolbar widget to menu container
  Gtk::Widget* pToolbar = myUIManager->get_widget("/ToolBar") ;
  if(pToolbar)
    m_Box.pack_start(*pToolbar, Gtk::PACK_SHRINK);

  //add box which contain all window elements below the menu
  m_Box.add(d_Box);
  //add h2_box to main box
  d_Box.add(h2_Box);
  h2_Box.set_vexpand(false);

    //set and add entry to box
  notesEntry->set_text("add notes");
  set_focus_child(*notesEntry);
  notesEntry->set_text(notesEntry->get_text() + " to list");
  notesEntry->select_region(0, notesEntry->get_text_length());
  notesEntry->signal_changed().connect(sigc::mem_fun(*this, &notesApp::on_text_changed));
  h2_Box.pack_start(*notesEntry, true, true, 5);

  //add new task button
  b_add->signal_clicked().connect(sigc::mem_fun(*this, &notesApp::on_addEntry_clicked));
  h2_Box.pack_start(*b_add, false, true, 5);



  Glib::ustring someTask = "some task";
  //add Button which saves editing
  b_saveEdit->signal_clicked().connect(sigc::mem_fun(*this, &notesApp::onSaveEdit_clicked));
  b_saveEdit->set_sensitive(false);
  h2_Box.pack_start(*b_saveEdit, false, true, 5);

  //delete button
  b_delete->signal_clicked().connect(sigc::mem_fun(*this, &notesApp::on_delete_clicked));
  b_delete->set_sensitive(false);
  h2_Box.pack_start(*b_delete, false, true, 5);

  m_ScrolledWindow.add(m_TreeView);

  m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);

    //Create the Tree model:
  m_refTreeModel = Gtk::ListStore::create(m_Columns);

  m_TreeView.set_model(m_refTreeModel);

row = *(m_refTreeModel->append());
row[m_Columns.m_col_id]=1;
row[m_Columns.m_col_percentage]=15;
row[m_Columns.m_col_name] = "Test text";

m_refTreeSelection = m_TreeView.get_selection();
m_refTreeSelection->signal_changed().connect( sigc::mem_fun(*this,&notesApp::on_selection_changed));

count=1;

m_TreeView.append_column("ID", m_Columns.m_col_id);
m_TreeView.append_column("Task completed", m_Columns.m_col_percentage);
m_TreeView.append_column("Task Description", m_Columns.m_col_name);

d_Box.add(h3_Box);
h3_Box.set_vexpand(true);

h3_Box.pack_start(m_ScrolledWindow,true,true,5);

//fill in the treeview Model






  show_all_children();
}

notesApp::~notesApp()
{
}

void notesApp::on_menu_file_new_generic()
{
   std::cout << "A File|New menu item was selected." << std::endl;
}

void notesApp::on_text_changed()
{
    bool is_button_active = b_saveEdit->get_sensitive();

    if(any_row_selected && !is_button_active) {
        b_saveEdit->set_sensitive(true);
    }

     std::cout << "text has changed" << std::endl;
}

void notesApp::on_addEntry_clicked() {
    count++;

    row = *(m_refTreeModel->append());
    row[m_Columns.m_col_id] = count;
    row[m_Columns.m_col_name] = notesEntry->get_text();
    row[m_Columns.m_col_percentage] = m_HScale.get_value();
}

void notesApp::add_entry(Glib::ustring task, int percentage)
{
  std::cout << task << std::endl;
    std::cout << percentage << std::endl;

}

void notesApp::on_selection_changed()
{
    any_row_selected = true;
    b_saveEdit->set_sensitive(true);
    b_delete->set_sensitive(true);

    Gtk::TreeModel::iterator iter = m_refTreeSelection->get_selected();
    Gtk::TreeModel::Row row = *iter;

    Glib::ustring task_string = row.get_value(m_Columns.m_col_name);
    int selected_percentage = row.get_value(m_Columns.m_col_percentage);
    unsigned int selected_id = row.get_value(m_Columns.m_col_id);

    notesEntry->set_text(task_string);
    double scale_value = (double) selected_percentage;
    m_HScale.set_value(scale_value);

  std::cout<< selected_id<< std::endl;
}

void notesApp::onSaveEdit_clicked()
{
    b_saveEdit->set_sensitive(false);

    Gtk::TreeModel::iterator iter = m_refTreeSelection->get_selected();
    Gtk::TreeModel::Row row = *iter;

    Glib::ustring new_entry = notesEntry->get_text();
    row.set_value(m_Columns.m_col_name, new_entry);
    int new_percentage = m_HScale.get_value();
    row.set_value(m_Columns.m_col_percentage, new_percentage);
}


void notesApp::on_menu_file_quit()
{
             //Gtk::MESSAGE_ERROR
         Gtk::MessageDialog quitDialog("Are you sure you want to Quit?",
                                        false,
                                        Gtk::MESSAGE_ERROR,
                                        Gtk::BUTTONS_YES_NO,
                                        true);
            quitDialog.set_title("Quit Dialog");
            //save dialog result in order to handle the click
            int result = quitDialog.run();
        switch(result) {
            // default YES response id
            case(yes_response):
                hide();

                break;
            // default NO response id
            case(no_response):
                // hide previews dialog, or it gets messy
                quitDialog.hide();
                break;
            }
}

void notesApp::on_delete_clicked()
{
    Gtk::TreeModel::iterator store_iter = m_refTreeSelection->get_selected();
    m_refTreeModel->erase(store_iter);
}
