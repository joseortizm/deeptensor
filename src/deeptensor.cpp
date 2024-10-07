#include "deeptensor.hpp"
#include <iostream>
#include <vector>
#include <Accelerate/Accelerate.h>


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
  //todo: atributos:
  //this->tensor = data;
  //int row_ = 0;
  //int col_ = 0;

  public:

    // Constructor
    Tensor(int rows, int cols) {
        data.resize(rows, vector<T>(cols)); // init matrix 
    }
    // Destructor
    ~Tensor() {}

    void set(int row, int col, T value) {
        if (row < 0 || row >= data.size() || col < 0 || col >= data[row].size()) {
            throw out_of_range("Índice fuera de rango");
        }
        data[row][col] = value; 
    }

    T get(int row, int col) const {
        if (row < 0 || row >= data.size() || col < 0 || col >= data[row].size()) {
            throw out_of_range("Índice fuera de rango");
        }
        return data[row][col]; 
    }

    void print() const {
        for (size_t i = 0; i < data.size(); ++i) { 
            for (size_t j = 0; j < data[i].size(); ++j) { 
                cout << data[i][j] << " "; 
            }
            cout << endl;
        }
    }

    pair<int, int> shape() const { 
      //this->row_ = data.size();todo
      //this->col_ = data[0].size();todo
      return make_pair(data.size(), data.empty() ? 0 : data[0].size());
    }

    // TODO cambiarTensor
  void cambiarTensor(Tensor<float>* tensor) {
      // Modifica el tensor, por ejemplo, estableciendo un valor
      // Ejemplo usando el tensor A y B. Para el caso de modificar valor probablemente sea solo A->cambiarTensor() y/o A->cambiarTensor(XXXX)
      tensor->set(0, 0, 1.5f);
      tensor->set(1, 0, 2.5f);
      tensor->set(2, 0, 3.5f);
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
      int m = data.size();    // rows of X 
      int n = other->data[0].size(); // col of Y
      int k = data[0].size(); // col of X (or rows of Y)
      //cout<<"m | n | k | other[0] = "<<m<<" | "<<n<<" | "<<k<<" | "<<other->data[0][0]<<endl;
      
      // flatten for cblas_dgemm
      vector<double> flatX(m*k);
      vector<double> flatY(k*n);
      for(int i = 0; i < m; ++i) {
        for(int j = 0; j < k; ++j) {
            flatX[i * k + j] = data[i][j];
        }
      }  
      for(int i = 0; i < k; ++i) {
        for(int j = 0; j < n; ++j) {
            flatY[i * n + j] = other->data[i][j];
        }
      } 

     //create result(2x2)
    vector<double> result(m * n, 0.0);
    // operation
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                m, n, k,
                1.0, flatX.data(), k, 
                flatY.data(), n,      
                0.0, result.data(), n);

    //print output
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            cout << result[i * n + j] << " ";
        }
        cout <<endl;
      }
       
    }
    

};

