#ifndef NOTESAPP_H
#define NOTESAPP_H

#include <gtkmm.h>
class notesApp : public Gtk::Window
{
    public:
      notesApp();
      virtual ~notesApp();
      Gtk::Entry *notesEntry = Gtk::manage(new Gtk::Entry());
      Gtk::Button *b_add = Gtk::manage(new Gtk::Button("Add New Note"));
      Glib::RefPtr<Gtk::AccelGroup> group = Gtk::AccelGroup::create();
      Glib::RefPtr<Gtk::Adjustment> m_adjustment;

    protected:
    void on_addEntry_clicked();
    void add_entry(Glib::ustring task);
    void on_selection_changed();
    void on_text_changed();

    class ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
    public:

    ModelColumns()
    { add(m_col_id); add(m_col_name);}

    Gtk::TreeModelColumn<unsigned int> m_col_id;
    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
  };

  ModelColumns m_Columns;

  int count;
  bool any_row_selected = false;

  //Child widgets:
  Gtk::Box m_Box;
  Gtk::Box d_Box;
  Gtk::Box h1_Box;
  Gtk::Box h2_Box;
  Gtk::Box h3_Box;
  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::TreeView m_TreeView;
  Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
  Gtk::TreeModel::Row row;

  Glib::RefPtr<Gtk::TreeSelection> m_refTreeSelection;
  Glib::RefPtr<Gtk::UIManager> myUIManager;
  Glib::RefPtr<Gtk::ActionGroup> actionGroup;
  Glib::RefPtr<Gtk::RadioAction> m_refChoiceOne, m_refChoiceTwo;
};
#endif
