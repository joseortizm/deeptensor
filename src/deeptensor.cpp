#include "deeptensor.hpp"
#include <iostream>
#include <vector>
#include <Accelerate/Accelerate.h>
//#include <typeinfo>
#include <type_traits>



using namespace std;

//string hi(const string& nombre) {
//    return "Hello " + nombre;
//}

template<typename E> class ListaArreglo:public Lista<E>{
  private:
  // child class attributes
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


template<typename T> class Tensor:public Value<T>{

  private:
    vector<vector<T> > data;
    int row_;
    int col_; 

  public:

    // Constructor
    Tensor(int rows, int cols) {
        data.resize(rows, vector<T>(cols)); // init : vector T with vectors of T
        this->row_ = data.size();
        this->col_ = data[0].size();
    }
    // Destructor
    ~Tensor() {}

    //TODOs: set y get por ahora dejar asi su validacion, si se desea hacer algun cambio modificarlo a tiempo de compilacion sino dejar asi por ahora.
    void set(int row, int col, T value) {
        if (row < 0 || row >= this->row_ || col < 0 || col >= data[row].size()) {
            throw out_of_range("Índice fuera de rango"); //tiempo de ejecucion
        }
        data[row][col] = value; 
    }

    T get(int row, int col) const {
        if (row < 0 || row >= this->row_ || col < 0 || col >= data[row].size()) {
            throw out_of_range("Índice fuera de rango"); //example (en tiempo de ejec): libc++abi: terminating with uncaught exception of type std::out_of_range: Índice fuera de rango
        }
        return data[row][col]; 
    }

    void print() const {
        for (size_t i = 0; i < this->row_; ++i) { 
            for (size_t j = 0; j < this->data[i].size(); ++j) { 
                cout << this->data[i][j] << " "; 
            }
            cout << endl;
        }
    }

    pair<int, int> shape() const { 
      return make_pair(this->row_, data.empty() ? 0 : this->col_);
    }

  // TODO cambiarTensor:definir si me puede servir para algo
  void cambiarTensor(Tensor<float>* tensor) {
      // Ejemplo usando el tensor A y B. Para el caso de modificar valor probablemente sea solo A->cambiarTensor() y/o A->cambiarTensor(XXXX)
      tensor->set(0, 0, 1.5);
      tensor->set(1, 0, 2.5);
      tensor->set(2, 0, 3.5);
      cout<<"data.size() of A (row):"<<data.size()<<endl; //
      cout<<"print of cambiarTensor:"<<endl;
      tensor->print();
    }

  // TODO: return Tensor and conditional flow
  void dot(Tensor<float>* other) {
      // https://developer.apple.com/documentation/accelerate/1513282-cblas_dgemm
      // data is X; other->data is Y
      // result = X*Y 

      // input for cblas_dgemm 
      int m = this->row_;    // rows of X 
      int n = other->data[0].size(); // col of Y
      int k = this->col_; // col of X (or rows of Y)
      
      // flatten for cblas_dgemm
      vector<double> flatX(m*k);
      vector<double> flatY(k*n);
      for(size_t i = 0; i < m; ++i) {
        for(size_t j = 0; j < k; ++j) {
            flatX[i * k + j] = data[i][j];
        }
      }  
      for(size_t i = 0; i < k; ++i) {
        for(size_t j = 0; j < n; ++j) {
            flatY[i * n + j] = other->data[i][j];
        }
      } 

     //create result(example in main is 2x2)
      vector<double> result(m * n, 0.0);
      // operation
      cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                  m, n, k,
                  1.0, flatX.data(), k, 
                  flatY.data(), n,      
                  0.0, result.data(), n);

      //print output
      for(size_t i = 0; i < m; ++i) {
          for(size_t j = 0; j < n; ++j) {
              cout << result[i * n + j] << " ";
          }
          cout <<endl;
        }

    }

  void sc_mul(double other){
    //https://developer.apple.com/documentation/accelerate/1513084-cblas_dscal
    int rowxcol = this->row_ * this->col_;

    for (size_t i = 0; i < this->row_; ++i) {
      cblas_dscal(this->col_, other, data[i].data(), 1);
    }
    
    for (size_t i = 0; i < data.size(); ++i) { 
      for (size_t j = 0; j < data[i].size(); ++j) { 
        cout << data[i][j] << " "; 
      }
      cout << endl;
    }

  }

    

};

