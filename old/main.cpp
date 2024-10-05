#include <iostream>
#include <Accelerate/Accelerate.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

template <typename T>
void printv(vector<T> v){
    cout<<"[";
    for(int i = 0; i < v.size(); i++){
        cout<<" "<<v[i];
    }

    cout<<" ]"<<endl;
}

template <typename T>
void print2v(vector<vector<T>> v) {
    for (const auto& row : v) {
        for (const auto& val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

vector<vector<double>>scalarm(const vector<vector<double>>& matrix, double scalar){
    int numRows = matrix.size();
    int numCols = matrix[0].size();
    vector<vector<double>> resultMatrix = matrix;

    for (int i = 0; i < numRows; ++i) {
        cblas_dscal(numCols, scalar, resultMatrix[i].data(), 1);
    }

    return resultMatrix;

}

template <typename T>
vector<double>minMaxNormalization(const vector<T>& matrix){
   
    vector<double> resultMatrix;
    auto min_iter = min_element(matrix.begin(), matrix.end());
    double min_value = *min_iter;
    
    auto max_iter = max_element(matrix.begin(), matrix.end());
    double max_value = *max_iter;

    int matrix_size = matrix.size(); //for simple list, check for RL
    for(int i = 0; i < matrix_size; i++){
        double normalized_value = (matrix[i] - min_value) / (max_value - min_value);
        resultMatrix.push_back(normalized_value);

        }

    return resultMatrix;

}





class LinearRegression{

    private:
        vector<vector<double>> X;  
        vector<double> y;               
        vector<double> weights; 

    public:
     LinearRegression(const vector<vector<double>>& features, const vector<double>& labels) {
          X = features;
          y = labels;
      }   

    void fit(){
        



    }


    void predict(){



    }




};




class ReadCSV{

    private:
        string filename;
        vector<vector<int>> data; 
        vector<vector<int>> columns;

    public:
        ReadCSV(const string path) {filename = path;}


   vector<vector<int>> getRows()  {
    
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error al abrir el archivo CSV: " << filename << endl;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        vector<int> tokens;  
        string token; 
        int tokenI; 
        while (getline(iss, token, ',')) {
            tokenI = stoi(token);                         
            tokens.push_back(tokenI);
        }

        data.push_back(tokens);

        if (columns.size() < tokens.size()) {
            columns.resize(tokens.size());
        }
        for (size_t i = 0; i < tokens.size(); ++i) {
            columns[i].push_back(tokens[i]);
        }
    }

    file.close();
        return data;
    }

   vector<vector<int>> getColumns() {
        return columns;
    }
   
};





int main(){
    
    //read file csv
    //const string filename = "datasets/readme.csv";
    const string filename = "datasets/house_price_data.csv";
    ReadCSV data(filename);
    
    //get rows
    vector<vector<int>> filas = data.getRows();  
   
    cout<<"-----template:-------"<<endl;
    print2v(filas);
    cout<<"-----end template------"<<endl;
    cout<<"indice especifico: filas[0][1]: "<<filas[0][1]<<endl; // 3 

    //get columns
    vector<vector<int>> columnas = data.getColumns();  
    cout<<"columnas[0]: "<<endl;
    printv(columnas[0]); 
    cout<<"columnas[0][1]: "<<columnas[0][1]<<endl; //1600
    
    //check typeid
    cout<<"typeid(columnas[0][1]): "<< typeid(columnas[0][1]).name()<<endl; //i
   
    //suma
    int sumaCol = 0; 
    for(int i = 0; i < columnas[0].size(); i++){
            sumaCol = sumaCol + columnas[0][i];
        }
    cout<<"suma de enteros columnas[0]: "<<sumaCol<<endl;

    //normalization
    vector<double> normalized_col = minMaxNormalization(columnas[0]);
    cout<<"normalizer_col"<<endl;
    printv(normalized_col);


    return 0;
}


