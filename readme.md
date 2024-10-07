# deepTensor

deepTensor is a C++ tool designed for matrix operations using Apple’s Accelerate framework, which optimizes performance on the CPU. If you want to maximize your CPU's potential in your project, choose deepTensor.


## Examples
### Matrix Multiplication
```
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
```

## Compile
```
g++ -o test src/main.cpp -I include -lcblas 
```







