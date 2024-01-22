#include "heap.h"
#include <iostream>
#include <cmath>
using namespace std;

Heap::Heap(int a[], unsigned int size){
    data = new int[size + 1];
    for (unsigned int i = 0; i < size; i++){
        data[i+1] = a[i];
    }
    pointer = size;
    
    //Heap-Ordnung herstellen, indem fur den letzten Knoten, der kein Blatt ist,
    //heapify augerufen wird:
    for (unsigned int i = size/2; i>= 1; i--)
        heapify(i);
}

void Heap::heapify(unsigned int start){
    int new_start;
    
    if (2 * start > this->pointer){
        return;  //Schon auf Blattebene angekommen
    }
    if (2 * start + 1 <= this->pointer  //Es gibt auch rechtes Kind
            && data[2*start+1] > data[2*start]){
        new_start = 2 * start + 1; //rechtes Kind als Vergleichsfeld nehmen
    } else {
        new_start = 2 * start;   //linkes Kind als Vergleichsfeld nehmen
    }
    if (data[start] < data[new_start]){
        int tmp = data[start];
        data[start] = data[new_start];
        data[new_start] = tmp;
        heapify(new_start);
    }
}

Heap::~Heap(){
    delete[] data;
}

int Heap::pop(){
    if (pointer < 1)
        throw underflow_error("Heap ist leer");
    int res = data[1];
    data[1] = data[pointer];
    pointer--;
    heapify(1);
    return res;
}
