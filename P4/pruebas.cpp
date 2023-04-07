#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void writeToFile(const char** arr, int size, const char* fileName){
    ofstream file(fileName, ios::out | ios::binary);
    file.write((char*) &size, sizeof(size));
    file.write((char*) arr, sizeof(char*) * size);
    file.close();
}

void readFromFile(char**& arr, int& size, const char* fileName){
    ifstream file(fileName, ios::in | ios::binary);
    file.read((char*) &size, sizeof(size));
    arr = new char*[size];
    file.read((char*) arr, sizeof(char*) * size);
    file.close();
}

int main(){
    int a = 589;
    int b = 10;
    float c = 3.14;

    string cad0 = to_string(a);
    const char* str5 = cad0.c_str();

    const char* str1 = "hola";
    const char* str2 = "mundo";
    const char* str3 = "c++";
    const char* arr[4] = {str1, str2, str3};
    arr[3] = str5;
    int size = sizeof(arr) / sizeof(*arr);

    writeToFile(arr, size, "data.bin");

    char** newArr;
    int newSize;
    readFromFile(newArr, newSize, "data.bin");

    for(int i=0; i<newSize; i++){
        cout << newArr[i] << endl;
    }

    return 0;
}
