#include "notesApp.h"
#include "gtkmm/application.h"

int main (int argc, char *argv[]){
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv);

    notesApp notes;

    return app->run(notes);
}
