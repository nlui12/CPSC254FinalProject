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
  set_default_size(800,400);
  add(m_Box);

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

  //adds new note
  b_add->signal_clicked().connect(sigc::mem_fun(*this, &notesApp::on_addEntry_clicked));
  h2_Box.pack_start(*b_add, false, true, 5);

  Glib::ustring someTask = "some note";
  //add Button which saves editing


  m_ScrolledWindow.add(m_TreeView);

  m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);

    //Create the Tree model:
  m_refTreeModel = Gtk::ListStore::create(m_Columns);

  m_TreeView.set_model(m_refTreeModel);

row = *(m_refTreeModel->append());
row[m_Columns.m_col_id]=1;
row[m_Columns.m_col_name] = "Test text";

m_refTreeSelection = m_TreeView.get_selection();
m_refTreeSelection->signal_changed().connect( sigc::mem_fun(*this,&notesApp::on_selection_changed));

count=1;

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
     std::cout << "text has changed" << std::endl;
}

void notesApp::on_addEntry_clicked() {
    count++;

    row = *(m_refTreeModel->append());
    row[m_Columns.m_col_id] = count;
    row[m_Columns.m_col_name] = notesEntry->get_text();
    std::ofstream outObj;
    outObj.open("notes.txt", std::ios_base::app);
    outObj << notesEntry->get_text() << std::endl;
    outObj.close();
}

void notesApp::add_entry(Glib::ustring task)
{
  std::cout << task << std::endl;

}

void notesApp::on_selection_changed()
{
    any_row_selected = true;

    Gtk::TreeModel::iterator iter = m_refTreeSelection->get_selected();
    Gtk::TreeModel::Row row = *iter;

    Glib::ustring task_string = row.get_value(m_Columns.m_col_name);
    unsigned int selected_id = row.get_value(m_Columns.m_col_id);

    notesEntry->set_text(task_string);

  std::cout<< selected_id<< std::endl;
}

