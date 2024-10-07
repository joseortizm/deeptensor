#include <iostream>
#include <string>
#include <Accelerate/Accelerate.h>
#include "deeptensor.hpp"
using namespace std;


int main() {

  //string nombre = "Jose"; 
  //string saludo = hi(nombre);
  //cout<<saludo<<endl;

  //ListaArreglo<int> *lista = new ListaArreglo<int>();
  //lista->agregar(19);
  //lista->agregar(22);
  //lista->agregar(23);
  //lista->moverAPosicion(1);
  //lista->insertar(38);
  //for(lista->moverAlInicio(); 
  //    lista->posicionActual() < lista->longitud();
  //    lista->siguiente()){
  //      cout<<"Elemento: "<<lista->getValor()<<endl; 
  // }
  // delete lista; 

  // Crear un tensor de enteros
  //Tensor<int>* tensorInt = new Tensor<int>(3, 3);
  //tensorInt->set(0, 0, 1);
  //tensorInt->set(0, 1, 2);
  //tensorInt->set(0, 2, 3);
  //tensorInt->set(1, 0, 4);
  //tensorInt->set(1, 1, 5);
  //tensorInt->set(1, 2, 6);
  //tensorInt->set(2, 0, 7);
  //tensorInt->set(2, 1, 8);
  //tensorInt->set(2, 2, 9);
  //cout << "Tensor de enteros:" << endl;
  //tensorInt->print();
  //pair<int, int> shapeInt = tensorInt->shape();
  //cout << "("<<shapeInt.first<< ", "<<shapeInt.second<<")"<< endl;

  Tensor<float>* A = new Tensor<float>(2, 3);
  A->set(0, 0, 1);
  A->set(0, 1, 2);
  A->set(0, 2, 3);
  A->set(1, 0, 4);
  A->set(1, 1, 5);
  A->set(1, 2, 6);  
  Tensor<float>* B = new Tensor<float>(3, 2);
  B->set(0, 0, 7);
  B->set(0, 1, 8);
  B->set(1, 0, 9);
  B->set(1, 1, 10);
  B->set(2, 0, 11);
  B->set(2, 1, 12); 

  cout<<"A:"<<endl;
  A->print();
  cout<<"B:"<<endl;
  B->print();

  cout<<"A*B:"<<endl;
  A->dot(B);

  //OK:
  //cout<<A->get(0,1)<<endl;
  //cout<<B->get(2,1)<<endl; 

  //TODO:
  //A->cambiarTensor(B);  


  delete A;
  delete B;

  return 0;


}
