/*En programaci�n orientada a objetos, el patr�n visitor es una forma de separar el algoritmo de la estructura de un objeto.

La idea b�sica es que se tiene un conjunto de clases elemento que conforman la estructura de un objeto. 
Cada una de estas clases elemento tiene un m�todo aceptar (accept()) que recibe al objeto visitante (visitor) como argumento. 
El visitante es una interfaz que tiene un m�todo visit diferente para cada clase elemento; por tanto habr� implementaciones de la interfaz
visitor de la forma: visitorClase1, visitorClase2... visitorClaseN. El m�todo accept de una clase elemento llama al m�todo visit de su clase.
Clases concretas de un visitante pueden entonces ser escritas para hacer una operaci�n en particular*/

//Algunas partes del patron fueron sacadas de internet para poder lograr la ejecucion.

#include <iostream>
#include <string>
using namespace std;

// 1. Agregar un m�todo de aceptaci�n (Visitante) a la jerarqu�a de "elemento".


 class Element
 { public: virtual void accept(class Visitor &v) = 0;
  };
   class This: public Element
	{
	 public: 
	 /*virtual*/void accept(Visitor &v);
	  string thiss()
	 {
	 return "EL PRIMERO";
	  }
	   };


 class That: public Element
  { public: 
  /*virtual*/void accept(Visitor &v);
  string that()
   {
	return "EL SEGUNDO";
	}
	 };


 class TheOther: public Element
  {
  public: /*virtual*/void accept(Visitor &v);
   string theOther()
	{
	return "EL TERCERO "; }
	 };

   
// 2. Creando una clase de "visitante" con un m�todo visit () para cada tipo de "elemento".

   class Visitor
	{
	public:
	virtual void visit(This *e) = 0;
	virtual void visit(That *e) = 0;
	virtual void visit(TheOther *e) = 0;
	 };
	 /*virtual*/void This::accept(Visitor &v)

	  {
	  v.visit(this);
	  }
	  /*virtual*/
	  void That::accept(Visitor &v)

	   {

		v.visit(this);

		 }


		 /*virtual*/

		 void TheOther::accept(Visitor &v)

		  {

		   v.visit(this);

		   }

 // 3. Crear una clase derivada de "visitante" para cada "operaci�n" para hacer "elementos".

class UpVisitor: public Visitor

 {

 void visit(This *e)
	 {

	 cout << " mover para arriba " + e->thiss() << '\n';

	  }
	  /*virtual*/void visit(That *e)
	   {

	   cout << " mover para arriba " + e->that() << '\n';

	   }
	   /*virtual*/void visit(TheOther *e)
		{

		 cout << " mover para arriba " + e->theOther() << '\n';
		  }

 };

 class DownVisitor: public Visitor
 {
 /*virtual*/void visit(This *e)

  {

   cout << "mover para abajo " + e->thiss() << '\n';

	}

	 /*virtual*/void visit(That *e)

	 {

	 cout << "mover para abajo " + e->that() << '\n';

	 }

	/*virtual*/void visit(TheOther *e)

	 {

	 cout << "mover para abajo " + e->theOther() << '\n';
	 }

  };

  int main()
   {
  
  cout<<"\nPatron visitor\n"<<endl;
  
   Element *list[]
	= { 
	
	new This(), new That(), new TheOther() 
	
	};

	 UpVisitor up;
	 DownVisitor down; 
	  for (int i = 0; i < 3; i++) 
	  
	  list[i]->accept(up);
	   
	   cout<<endl<<endl;
	   for (int i = 0; i < 3; i++)
	   list[i]->accept(down);
	  
	    }
