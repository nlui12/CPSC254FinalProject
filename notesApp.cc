#include "notesApp.h"
#include <gtkmm/stock.h>
#include <iostream>
#include <fstream>
#include <string>
notesApp::notesApp()
: m_Box(Gtk::ORIENTATION_VERTICAL),
  d_Box(Gtk::ORIENTATION_VERTICAL),
  h1_Box(Gtk::ORIENTATION_HORIZONTAL),
  h2_Box(Gtk::ORIENTATION_HORIZONTAL),
  h3_Box(Gtk::ORIENTATION_HORIZONTAL)

{
  set_title("Notes");
  set_default_size(800,400); //window size resolution
  add(m_Box); //adding a main box widget

  //add box which contain all window elements below the menu
  m_Box.add(d_Box);
  //add h2_box to main box widget
  d_Box.add(h2_Box);
  h2_Box.set_vexpand(false);

  //creating an add entry text region
  notesEntry->set_text("add notes");
  set_focus_child(*notesEntry);
  notesEntry->set_text(notesEntry->get_text() + " to list");
  notesEntry->select_region(0, notesEntry->get_text_length());
  notesEntry->signal_changed().connect(sigc::mem_fun(*this, &notesApp::on_text_changed));
  h2_Box.pack_start(*notesEntry, true, true, 5);

  //adds new note
  b_add->signal_clicked().connect(sigc::mem_fun(*this, &notesApp::on_addEntry_clicked));
  h2_Box.pack_start(*b_add, false, true, 5);

  Glib::ustring someNote = "some note";
  //adds an edit button
  b_edit->signal_clicked().connect(sigc::mem_fun(*this, &notesApp::on_edit_clicked));
  b_edit->set_sensitive(false);
  h2_Box.pack_start(*b_edit, false, true, 5);

  //adds a delete button
  b_delete->signal_clicked().connect(sigc::mem_fun(*this, &notesApp::on_delete_clicked));
  b_delete->set_sensitive(false);
  h2_Box.pack_start(*b_delete, false, true, 5);

  m_ScrolledWindow.add(m_TreeView);
  m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);

  //Create the Tree model to display list of notes:
  m_refTreeModel = Gtk::ListStore::create(m_Columns);
  m_TreeView.set_model(m_refTreeModel);
    
count = 1;

//reads from notes.txt and appends lines to our TreeModel
//serves as the save functionality of the program
std::string note_content;
std::string line;
std::ifstream inFile ("notes.txt");
if (inFile.is_open())
{
  while(std::getline(inFile,line))
  {
    note_content = line;
    note_content = line.substr(13);

    row = *(m_refTreeModel->append());
    row[m_Columns.m_col_id]=count;
    row[m_Columns.m_col_name] = note_content;
    count++;
  }
  inFile.close();
}

//row = *(m_refTreeModel->append());
//row[m_Columns.m_col_id]=1;
//row[m_Columns.m_col_name] = "Test text";

m_refTreeSelection = m_TreeView.get_selection();
m_refTreeSelection->signal_changed().connect( sigc::mem_fun(*this,&notesApp::on_selection_changed));

//Header bar at the top of the list
m_TreeView.append_column("ID", m_Columns.m_col_id);
m_TreeView.append_column("Note Entry", m_Columns.m_col_name);

d_Box.add(h3_Box);
h3_Box.set_vexpand(true);

h3_Box.pack_start(m_ScrolledWindow,true,true,5);

  show_all_children();
}

notesApp::~notesApp()
{
}

void notesApp::on_text_changed()
{

  bool is_button_active = b_edit->get_sensitive();

  if(any_row_selected && !is_button_active)
  {
      b_edit->set_sensitive(true);
  }

  std::cout << "text has changed" << std::endl;

}

void notesApp::on_addEntry_clicked() {
    //count++;

    row = *(m_refTreeModel->append());
    row[m_Columns.m_col_id] = count;
    row[m_Columns.m_col_name] = notesEntry->get_text();
    std::ofstream outObj;
    outObj.open("notes.txt", std::ios_base::app);
    outObj << "note ID: " << count << " - " << notesEntry->get_text() << std::endl;
    outObj.close();
    count++;
}

void notesApp::add_entry(Glib::ustring note)
{
  std::cout << note << std::endl;

}

void notesApp::on_selection_changed()
{
    any_row_selected = true;

    b_edit->set_sensitive(true);
    b_delete->set_sensitive(true);


    Gtk::TreeModel::iterator iter = m_refTreeSelection->get_selected();
    Gtk::TreeModel::Row row = *iter;

    Glib::ustring note_string = row.get_value(m_Columns.m_col_name);
    unsigned int selected_id = row.get_value(m_Columns.m_col_id);

    notesEntry->set_text(note_string);


  std::cout<< selected_id<< std::endl;
}

void notesApp::on_edit_clicked()
{
    b_edit->set_sensitive(false);

    Gtk::TreeModel::iterator iter = m_refTreeSelection->get_selected();
    Gtk::TreeModel::Row row = *iter;

    Glib::ustring new_entry = notesEntry->get_text();
    row.set_value(m_Columns.m_col_name, new_entry);
}

void notesApp::on_delete_clicked()
{
    Gtk::TreeModel::iterator store_iter = m_refTreeSelection->get_selected();
    m_refTreeModel->erase(store_iter);
}

