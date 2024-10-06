#include "deeptensor.hpp"
#include <iostream>

using namespace std;

//string hi(const string& nombre) {
//    return "Hello " + nombre;
//}

template<typename E> class ListaArreglo:public Lista<E>{
  private:
  //atributos es decir variables que tendra esta hija
  E* arreglo; //arreglo de elementos
  int tamMax; //tamano fijo 
  int tamLista; //tamano de la lista
  int actual; //indice actual

  public:
  //constructor
  ListaArreglo(int tamMax = 100){
   this->tamMax = tamMax;
   this->tamLista = this->actual = 0;
   this->arreglo = new E[this->tamMax];
  }  

  //destructor
  ~ListaArreglo(){
   delete[] this->arreglo;
  }

 //implementacion de metodos del padre:

  void limpiar(){
    delete[] this->arreglo;
    this->tamLista = this->actual = 0;
    this->arreglo = new E[this->tamMax]; 
  }
  void insertar(E elemento){
    for(int i = this->tamLista; i > this->actual; i--){
      this->arreglo[i] = this->arreglo[i-1];
    } 
    this->arreglo[this->actual] = elemento;
    this->tamLista++;
      
  }
  void agregar(E elemento){
    this->arreglo[this->tamLista] = elemento;
    this->tamLista++;
  }
  void moverAlInicio(){
   this->actual = 0;
  } 
  void moverAlFinal(){
   this->actual = this->tamLista;
  }

  void anterior(){
    if(this->actual < 0){
      this->actual--;
    }
  } 
  void siguiente(){
    if(this->actual < this->tamLista){
      this->actual++;
    }
  }
  int longitud(){
    return this->tamLista;
  }
  int posicionActual(){
    return this->actual;
  }
  void moverAPosicion(int pos){
    if(pos >= 0 && pos < this->tamLista){
      this->actual = pos;
    }
  }
  E getValor(){
    return this->arreglo[this->actual];
  }
 void setValor(E elemento){
  this->arreglo[this->actual] = elemento;
  }
  E eliminar(){
    E eliminado = this->arreglo[this->actual];
    for(int i = this->actual; i < this->tamLista; ++i){
      this->arreglo[i] = this->arreglo[i+1];
    }
    this->tamLista--;
    return eliminado;
  }

};
