Una **VMT** (*tabella dei metodi virtuali, tabella delle funzioni virtuali, tabella delle chiamate virtuali*) è un meccanismo utilizzato in un *linguaggio di programmazione* per supportare il *dispatch dinamico*.

Ogni volta che una classe definisce una *funzione virtuale*, la maggior parte dei compilatori aggiunge alla classe una variabile membro nascosta che punta a un array di puntatori a funzioni (*virtuali*) chiamato VTM *vtable*. Questi puntatori vengono utilizzati in fase di esecuzione per invocare le implementazioni delle funzioni appropriate, perché in fase di compilazione potrebbe non essere ancora noto se deve essere chiamata la funzione di base o una funzione derivata implementata da una classe che eredita dalla classe di base.

![[Pasted image 20231127155113.png]]

````C++
class B{
public:
	FunctionPointer* vptr; //vpointer aggiunto dal compilatore
	virtual void m0() {}
	virtual void m1() {}
	virtual void m2() {}
};

class D: public B{
public:
	virtual void m0() {} //overriding
	virtual void m2() {} //overriding
};
B* p;

p = &b;
p->m2();
//chiama la funzione all'indirizzo *((p->vptr)+2) cioè chiama B::m2()

p = &d;
p->m2();
//chiama la funzione all'indirizzo *((p->vptr)+2) cioè chiama D::m2()
````

**Back to `poligono`**

````C++
slide 32 10/31
````