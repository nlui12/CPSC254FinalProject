#ifndef NOTESAPP_H
#define NOTESAPP_H

#include <gtkmm.h>

class notesApp : public Gtk::Window
{
    public:
        notesApp();
        virtual ~notesApp();

    protected:
    class ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
  public:

    ModelColumns()
    { add(m_col_id); add(m_col_percentage); add(m_col_name);}

    Gtk::TreeModelColumn<unsigned int> m_col_id;
    Gtk::TreeModelColumn<int> m_col_percentage;
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
  Gtk::EventBox event_box;
  Gtk::Label m_Label;
  Gtk::Scale m_HScale;
  Gdk::Pixbuf *pixmap;

  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::TreeView m_TreeView;
  Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
  Gtk::TreeModel::Row row;

  Glib::RefPtr<Gtk::TreeSelection> m_refTreeSelection;
  Glib::RefPtr<Gtk::UIManager> m_refUIManager;
  Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
  Glib::RefPtr<Gtk::RadioAction> m_refChoiceOne, m_refChoiceTwo;
};
#endif