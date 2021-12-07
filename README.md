# **CPSC 254 Final Project - NotesApp**
- Nicholas Lui
- Omar Mann
- Cesar Sepulveda

## **Program Description**
This program is a note-taking application written in C++ and uses the graphics library GTK to provide a graphical user interface (GUI) for users. First, the application will use the GUI to prompt the user to enter some notes. It will then append the date to the notes and create a text file with both the notes and the date.

## **How To Compile**
In order to compile this program, you need to have gtkmm-3.0 and g++ installed on your system.
To do that you will use the following commands:

  - sudo apt-get install libgtkmm-3.0-dev
If you do not have g++ installed, do the following command:

  - sudo apt install g++
 
To compile use the following commands:
  - g++ -c -Wall notesApp.cc -o notesApp.o \`pkg-config gtkmm-3.0 --cflags\`
  - g++ -c -Wall main.cc -o main.o \`pkg-config gtkmm-3.0 --cflags\`
  - g++ notesApp.o main.o notesApp \`pkg-config gtkmm-3.0 --libs\`
To execute and run the program use the following command:
  - ./notesApp

## Libraries
  - iostream: Is C++’s Standard Input/Output Streams Library. This library defines the standard input/output stream objects used in C++.
  - gtkmm/stock.h: Is a GTK header that adds various functions such as add(), lookup() and get_ids() to help manage stock items.
  - gtkmm.h: The gtkmm.h header includes the entire gtkmm kit.
  - gtkmm/application.h: The Gtk::Application header handles gtkmm initialization, session management, basic scriptability, and shell integration by exporting menus and actions. It also allows for the life-cycle of an application to be applied to the life-cycle of a list of top-level windows.
