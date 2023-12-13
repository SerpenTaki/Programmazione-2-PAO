#include <iostream>
using std::cout; 
using std::endl;
//#include "Queue_item.h"
#include "Queue.h"

int main() {
    Queue<int>* pi = new Queue<int>;
    //vengono istanziati la classe Queue<int> ed il suo costruttore
    //Queue<int>() perchè new deve costruire un oggetto della classe
    int i;
    for(i = 0; i < 10; i++) pi ->add(i);
    //vengono istanziati i metodi add<int> e is_empty<int>, la classe
    // QueueItem<int> e il suo costruttore QueueItem<int>()
    for(i = 0; i < 10; i++) cout << pi->remove() << endl;
    // viene istanziato il metodo remove<int>
}