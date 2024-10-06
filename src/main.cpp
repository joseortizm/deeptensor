#include <iostream>
#include <string>

#include "deeptensor.hpp"

using namespace std;


int main() {
    //string nombre = "Jose"; 
    //string saludo = hi(nombre);
    //cout<<saludo<<endl;


    ListaArreglo<int> *lista = new ListaArreglo<int>();
  lista->agregar(19);
  lista->agregar(22);
  lista->agregar(23);
  lista->moverAPosicion(1);
  lista->insertar(38);

  for(lista->moverAlInicio(); 
      lista->posicionActual() < lista->longitud();
      lista->siguiente()){
        cout<<"Elemento: "<<lista->getValor()<<endl; 
   }
    
   delete lista; 





}
