#include "listNode.h"

#ifndef DOUBLYLIST_H
#define DOUBLYLIST_H

template <typename T>
class DoublyList
{
	public:
        int overTen();
		DoublyList();
		~DoublyList();
		void addFront(T d);
		void addBack(T d);
		T removeFront();
		T removeBack();
		T peak();
		bool isEmpty();
		int getSize();
		void printList();
		void sortList();
        void addToData();
        T getFront();
        T getBack();
        int getMedian();
        double getMean();

	private:
		ListNode<T> *front;
		ListNode<T> *back;
		int numOfElements;
};
template <typename T>
T DoublyList<T>::getFront(){
    return front->data;
}
template <typename T>
T DoublyList<T>::getBack(){
    return back->data;
}

template <typename T>
DoublyList<T>::DoublyList(){
	front = NULL;
	back = NULL;
	numOfElements = 0;
}
template <typename T>
DoublyList<T>::~DoublyList(){

	if(numOfElements!=0){

		ListNode<T> *current;
	    current = front;
	    while (current != back)
	    {
	        ListNode<T> *temp = current;
	        current = current->next;
	        temp->next = NULL;
	        temp->prev = NULL;
	        delete temp;
	        numOfElements--;
	    }
	    //at this point current = back, now delete it
	    current->next = NULL;
	    current->prev = NULL;
	    delete current;
	    numOfElements--;
	}
}
template <typename T>
void DoublyList<T>::addFront(T d)
{
    ListNode<T> *node = new ListNode<T>();
    node->data = d;
    if (isEmpty()){
        back = node;
    }
    else{
        front->prev = node;
    }
    node->next = front;
    front = node;
    ++numOfElements;
}
template <typename T>
T DoublyList<T>::removeFront()
{
    if (isEmpty()){
        return T();
    }
    else
    {
        ListNode<T>* temp = front;
        if (front->next == 0){
			back = 0;
		}
        else
        {
			front->next->prev = 0;
		}
        front = front->next;
        temp->next = 0;
        T theData = temp->data;
        delete temp;
        --numOfElements;
        return theData;
    }
}
template <typename T>
void DoublyList<T>::addBack(T d)
{
    ListNode<T> *node = new ListNode<T>();
    node->data = d;
    if (isEmpty()){
        front = node;
    }
    else{
        back->next = node;
    }
    node->prev = back;
    back = node;
    ++numOfElements;
}
template <typename T>
T DoublyList<T>::removeBack()
{
    if (isEmpty()) {
        return T();
    }
    else
    {
        ListNode<T>* temp;
        temp = back;
        if (back->prev == 0){
            front = 0;
        }
        else{
            back->prev->next = 0;
        }
        back = back->prev;
        temp->prev = 0;    
        T theData = temp->data;
        delete temp;
        --numOfElements;
        return theData;
    }
}
template <typename T>
T DoublyList<T>::peak()
{
    if (isEmpty()) {
        return T();
    }
    return front->data;
}
template <typename T>
int DoublyList<T>::getSize(){
	return numOfElements;
}
template <typename T>
bool DoublyList<T>::isEmpty(){
	if(numOfElements == 0){
		return true;
	}
	else{
		return false;
	}
}
template <typename T>
void DoublyList<T>::addToData(){
    if(numOfElements != 0){
        ListNode<T> *current = front;
        while(current!=back){
            current->data+=1;
            current = current->next;
        }
        back->data+=1;
    }
    else{
        //cout<<"list is empty"<<endl;
    }
}

template <typename T>
void DoublyList<T>::printList(){
	if(numOfElements!=0){
		ListNode<T> *current = front;
		while(current!=back)
		{
			cout<<current->data<<endl;
			current = current->next;
		}
		cout<<back->data<<endl;
	}
	else{
		//cout<<"list is empty"<<endl;
	}
}
template <typename T>
double DoublyList<T>::getMean(){
    double temp=0;

    if(numOfElements!=0){
        ListNode<T> *current = front;
        while(current!=back)
        {
            temp+=current->data;
            current = current->next;
        }
        temp+=back->data;
        
        return temp/getSize();
    }
    else{
        //cout<<"list is empty"<<endl;
        return 0;
    }
}

template <typename T>
int DoublyList<T>::getMedian(){
    if(numOfElements!=0){
        ListNode<T> *current = front;
        for(int i = 0; i < getSize()/2; ++i){
            current = current->next;
        }
        return current->data;
    }
    else{
        //cout<<"list is empty"<<endl;
        return 0;
    }
}

template <typename T>
int DoublyList<T>::overTen(){ //Calc over ten
    int temp = 0;
    if(numOfElements!=0){
        ListNode<T> *current = front;
        while(current!=back)
        {
            if(current->data >= 10){
                temp += 1;
            }
            current = current->next;
        }
        if(back->data >= 10){
            temp += 1;
        }
    }
    else{
        //cout<<"list is empty"<<endl;
    }
    return temp;
}


template <typename T>
void DoublyList<T>::sortList(){
    int size = getSize();
    ListNode<T> *current=front;
    T dummy; //temp variable for swap

    if (current == NULL) return;
    if (current->next == NULL) return;

    int swapped = 1;
    while (swapped){
        current = front;
        swapped = 0; //last pass unless there is a swap
        while (current->next != NULL){
            if (current->data > current->next->data){
                swapped = 1; //swap, will need to re-enter while loop
                //actual number swap
                dummy = current->data;
                current->data = current->next->data;
                current->next->data = dummy;
            }
            current = current->next;
        }
    }
}

#endif

