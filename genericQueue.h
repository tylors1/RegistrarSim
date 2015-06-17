#include <iostream>
#include "doublyList.h"
using namespace std;

#ifndef GENERICQUEUE_H
#define GENERICQUEUE_H
template<typename T>
class GenQueue
{
	public:
		GenQueue();
		~GenQueue();

		void insert(T data);
		T remove();
		T peak();
		int isEmpty();
		int getSize();
		void printQueue();

	private:
		DoublyList<T> d;
};

template<typename T>
GenQueue<T>::GenQueue(){
	//cout<<"object created"<<endl;
}
template<typename T>
GenQueue<T>::~GenQueue(){
	
	//cout<<"deleted Queue"<<endl;
}
template<typename T>
void GenQueue<T>::insert(T data){
	d.addBack(data);
}
template<typename T>
T GenQueue<T>::remove(){
	return d.removeFront();
}
template<typename T>
T GenQueue<T>::peak(){
	return d.peak();
}
template<typename T>
int GenQueue<T>::getSize(){
	return d.getSize();
}
template<typename T>
int GenQueue<T>::isEmpty(){
	return d.isEmpty();
}
template<typename T>
void GenQueue<T>::printQueue(){
	d.printList();
}
#endif