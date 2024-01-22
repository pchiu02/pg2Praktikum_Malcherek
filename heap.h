/* 
 * File:   heap.h
 * Author: arnim
 *
 * Created on 13. Dezember 2013, 07:51
 */

#ifndef HEAP_H
#define	HEAP_H
#include <stdexcept>

class Heap {
public:
    // Erstelle einen Heap aus dem Array a[] mit size Elementen
    Heap(int a[], unsigned int size);
    ~Heap();
    int pop();
    
private:
    void heapify(unsigned int start);
    int* data;
    unsigned int pointer;
};
#endif	/* HEAP_H */

