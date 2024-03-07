```C++
//Hello world
#include <QApplication>
#include <QLabel>

int main(int argc, char **argv){
	QApplication app(argc, argv);
	QLabel l("Hello World!");
	l.show();
	return app.exec();
	QPushButton b("Close All");
	b.show();
}
```

## L'entry point di un'applicazione widget-based
Funzione `main()`
```C++
#include "mainwindow.h"
	#include<QApplication>
	#include<QStyleFactory>
	int main(int argc, char *argv[]){
		//parametrizzazione dell'applicazione con metodi statici
		QApplication::setStyle(QStyleFactory::create("Fusion"));
		//Costruzione dell'oggetto applicazione che gestisce anche gli argomenti da riga di comando
		QApplication a(argc, argv);
		//Inizializzazione MainWindow w
		MainWindow w;
		w.show();
		//punto di inizio dell'event loop del thread GUI
		return a.exec()
	}
```
In Qt esiste una gerarchia di classi che modella il concetto di applicazione declidandolo nelle sue varianti di applicazione senza GUI (`QCoreApplication`), applicazione con GUI (`QGuiApplication`) e applicazione con GUI basata su widgets (`QApplication`).
La classe `QApplication` estende per ereditarietà le funzionalità di `QCoreApplication` e `QGuiApplication` specializzandone il comportamento per il caso di applicazioni che fanno uso di widgets.

`QApplication` sovrintende la corretta inizializzazione di tutte le impostazioni che riguardano il rendering delle widgets e la gestione degli argomenti passati da riga di comando. Pertanto, deve essere inizializzata prima di instanziare la finestra principale dell'applicazione o ogni altra widget.

La configurazione dei parametri dell'istanza avviene tramite l'uso di API statiche della classe, invocate _prima_ della costruzione dell'oggetto stesso. In questo caso, ad esempio, l'istanza di `QApplication` viene configurata per usare lo stile _Fusion_ invece che quello nativo del sistema.

Seguono le istruzioni relative alla creazione di una istanza dalla finestra principale che viene mostrata a schermo a seguito dell'invocazione del metodo `show()`.

Infine, il valore di ritorno della funzione `main()` è quello restituito dal metodo `exec()` dell'istanza di `QApplication`. L'invocazione di `exec()` è bloccante fino alla ricezione di un segnale di terminazione del programma, ad esempio la chiusura normale dell'applicazione. 

## Struttura di una classe widget-based
Innanzi tutto si osservi la presenza della macro `Q_OBJECT` che ricorre per via del legame di diretta discendenza che lega la classe QWidget alla classe [QObject](https://www.html.it/pag/72800/la-classe-qobject/).
```C++
#ifndef MAINWINDOW_H
	#define MAINWINDOW_H
	#include <QMainWindow>
	// forward declaration della classe Ui::MainWindow
	namespace Ui {
	class MainWindow;
	}
	class MainWindow : public QMainWindow
	{
		Q_OBJECT
	public:
		explicit MainWindow(QWidget *parent = nullptr);
		~MainWindow();
	private:
		// le caratteristiche dell'oggeto ui sono determinate da Qt Designer
		Ui::MainWindow *ui;
	};
	#endif // MAINWINDOW_H
```

[[Qt Designer]]
