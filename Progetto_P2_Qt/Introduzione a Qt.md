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
### Pensiamo alla GUI
-> I widgets should **depend on** the model
Info widget
````C++
class Info: public QWidget {
	Q_OBJECT
private:
	Character& character;
	Qlabel* name_label;
	Qlabel* hit_points_label;
	Qlabel* strength_label;
public:
	Info(character& character, QWidget* parent=0);
	void show();
};

Info::Info(Character& character, QWidget* parent) : QWidget(parent), character(character){
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

	name_label = new QLabel();
	layout->addWidget(name_label);

	hit_points_label = new QLabel();
	layout->addWidget(hit_points_label);

	strength_label = new QLabel();
	layout->addWidget(strenght_label);
}

void Info::show() {
	name_label->setText(QString::fromStdString(character.getName()));
	hit_points_label->setText("HP: " + QString::number(character.getHitPoints()) + "/" + QString::number(character.getMaxHitPoints()));
	strength_label->setText("Strength: " + QString::number(character.getStrength()));
}
````
The **info** widget wrap-up:
- extend **QWidget**
- use **Q_OBJECT** macro
- **QVBoxLayout** to arrange widget vertically
- mind *alignment*
- use **QString**

**THE HERO PANEL WIDGET**:
````C++
class HeroPanel: public QWidget{
	Q_OBJECT
private:
	QLabel* artwork;
	Info* info;
public:
	HeroPanel(Game::Hero& hero, QWidget* parent = 0);
	void refresh();
};

HeroPanel::HeroPanel(Game::Hero& hero, QWidget) : QWidget(parent)
{
	QHBoxLayout* layout = new QHBoxLayout(this); layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

	QPixmap image(":assets/" + QString::fromStdString(hero,getName()) + ".png");
	artwork = new QLabel();
	artwork->setPixmap(image.scaledToHeight(256));
	layout->addWidget(artwork);

	info = new Info(hero);
	info->show();
	layout->addWidget(info);
}
// Adds commands
QGridLayout* commands = new QGridLayout();
layout->addLayout(commands);

QPushButton* items = new QPushButton("items");
items->setEnambled(false);
commands->addWidget(items, 0, 1, 1, 1);

QPushButton* skills = new QPushButton("skills");
skills->setEnabled(false);
commands->addWidget(skills, 1, 0, 1, 1);
}

void HeroPanel::refresh() {info->show();}
````
//*gli asset sono utili per le cose che non devono cambiare spesso ad esempio se si pensa ad un browser l'icona di firefox o il layout è negli assets, tutto il resto viene gestito in modo dinamico e quindi in quel caso è meglio usare i percorsi e non gli asset.*

The **HeroPanel** widget wrap-up:
- **QHBoxLayout** to arrange widgets horizontally
- **QPixmap** and **QLabel** for images
- **QGridLayout** for a grid widgets
- commands as **QPushButtom**
- commands as **QPushButtom**
- member function to encapsulate *refresh* logic
The **MonsterPanel** is analogous without buttons.

**THE _BATTLE_ WIDGET**:
````C++
class Battle: public QWidget{
Q_OBJECT
private:
	Game::Hero& hero;
	Game::Monster& monster;
	HeroPanel* hero_panel;
	MonsterPanel* monster_panel;
public:
	Battle(Game::Hero& hero, Game::Monster& monste, QWidget* parent = 0);

public slots:
	void playerAttacks();
}

Battle::Battle(Game::Hero& hero, Game::Monster& monster, QWidget* parent) : QWidget(parent), hero(hero), monster(monster){
	QVBoxLayout* layout = new QVBoxLayout(this);

	monster_panel = new MonsterPanel(monster);
	layout->addWidget(monster_panel);

	layout->addStretch();

	hero_panel = new HeroPanel(hero);
	layout->addWidget(hero_panel);
}

void Battle::playerAttacks() {
	hero.attack(monster);
	monster_panel->refresh();
	monster.attack(hero);
	hero_panel->refresh();
}
````
The **Battle** widget wrap-up:
- **QHVoxLayout** to arrange widgets vertically
- work by **Aggregating** other widgets
- expose member functions to *react to events*

//slide 30/75

