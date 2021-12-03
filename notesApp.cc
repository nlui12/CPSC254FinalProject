#include <gtkmm.h>
#include <gtkmm/application.h>
int main(int argc, char *argv[]){
auto app = Gtk::Application::create(argc, argv);
Gtk::Window myWindow;
Gtk::Button myButton("Hello World");
myWindow.set_default_size(600, 360);
myWindow.set_position(Gtk::WIN_POS_CENTER);
myWindow.add(myButton);
myButton.show();
return app->run(myWindow);
}