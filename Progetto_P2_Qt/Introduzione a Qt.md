# Overview
è uno dei modi per passare dalla *linea di comando (CLI)* a un (GUI= *Graphical User Interface*) rendendolo semplice all'utente.
Ad esempio *LaTeX* permette di fare tutto ma per un'utente base potrebbe essere difficile, mentre avere un interfaccia grafica ad esempio per le tabelle può semplificare la vita *(immagina avere un'interfaccia che ti chieda quante righe e colonne per una tabella)*.

**Qt**:
--
- fully Object Oriented
- Scritto in C++
- Aziende serie che lo usano

**Come sviluppare in Qt**:
1. install Qt
2. scrivi il codice
3. genera un project file
4. fix project file
5. generate Makefile
6. compile
7. modify your code
8. repeat from  5 or 6
https://doc.qt.io/qt-5/gettingstarted.html

````C++
//Includes Qt header files
#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[]){
	//Define an application object
	QApplication app(argc, argv);
	//A piece of text
	QLabel hello("Hello world!");
	//Tells Qt to actually show the label
	hello.show();
	//Runs application
	return app.exec();
}
````
Generate the **Qt project file** *hello-world.pro* by running
`qmake -project`
edit the *hello-world.pro* file by adding QT += widgets:
````C++
TEMPLATE = app
TARGET = hello-world
INCLUDEPATH +=
QT += widgets

#Input
SOURCES += main.cpp
````
Generate the *makefile* and compile the code
```
qmake
make
```
the make command will show compilation info/warning/errors.
`./hello-world`
e abbiamo la nostra finestra.
-> Se modifichiamo un file esistente
`make`
-> Se aggiungi o rimuovi file *modifica hello-world.pro* e:
```
qmake
make
```
### Ciclo di vita di un progetto
1. Idea
2. Sketch
3. Modello
4. GUI
5. Test
*A volte toccherà ripetere più volte le fasi*
##### Idea
La progettazione parte da un bisogno
##### Sketch
Disegnare un interfaccia grafica, che identifichi le varie entità presenti nell'interfaccia, tipo il nemico, le caratteristiche del protagonista, del nemico. I vari container di comandi ad esempio
##### Modello
- Pianifica un *modello logico*
	- Quali sono i loro elementi?
		- nell'esempio abbiamo eroe e mostro, con info comuni... SOL: *classe astratta* Personaggio da cui deriviamo l'*Eroe* e il *Mostro*
- Come si fa un modello del genere?
	- UML class diagrams *Cheatsheet*
		- one box = one class
		- attributes and member function
		- colon defines types
		- `-`for private fields, `#`for protected, `+`for public
		- arrows for inheritance
		- italics for virtual, bold&italic fore pure virtuale
Free-SW for UML: https://wiki.gnome.org/Apps/Dia

