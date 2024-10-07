#ifndef DEEPTENSOR_HPP
#define DEEPTENSOR_HPP

//#include "deeptensor.cpp"
#include <string>


using namespace std;


//string hi(const string& nombre);

//clase padre: lista abstracta
template<typename E> class Lista{
  private:

  public:
  //constructor
  Lista(){}
  ~Lista(){}

  virtual void limpiar() = 0; //limpiar la lista
  virtual void insertar(E elemento) = 0; //inserta en puntero actual, empuja otros
  virtual void agregar(E elemento) = 0;//agrega al final de lista
  virtual void moverAlInicio() = 0; //mover puntero Actual a inicio 
  virtual void moverAlFinal() = 0; //mover al final: 1er espacio disponible
  virtual void anterior() = 0; //mover actual a posicion anterior(izq)
  virtual void siguiente() = 0; //mover actual a posicion posterior(der)
  virtual int longitud() = 0; //retorna numero de elementos en lista
  virtual int posicionActual() = 0; //retorna posicion actual del elemento
  virtual void moverAPosicion(int pos) = 0; //mover puntero actual a pos
  virtual E getValor() = 0; //retorna valor en pos actual
  virtual void setValor(E elemento) = 0; //modifica valor de pos actual
  virtual E eliminar() = 0; //elimina, libera memoria y retorna el eliminado

  virtual void imprimirListas() = 0;
  virtual E getLista(int i) = 0;


};


template<typename T> class Value{
  private:

  public:
  //constructor
  Value(){}
  ~Value(){}

  virtual void set(int row, int col, T value) = 0; 
  virtual  T get(int row, int col) const = 0;      
  virtual void print() const = 0;
  virtual pair<int, int> shape() const = 0;        

};






#include "../src/deeptensor.cpp"




#endif 

