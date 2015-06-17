#include <iostream>
#ifndef LISTNODE_H
#define LISTNODE_H

using namespace std;
template <typename T>
class ListNode //objects in the linked list
{
	public:
		T data;//the data that we will store
		ListNode();
		ListNode(int d);
		~ListNode();
		ListNode *next;//int and ptr and the member variables
		ListNode *prev;
};
template <typename T>
ListNode<T>::ListNode(int d){
	data = d;
	next = NULL;
	prev = NULL;
}
template <typename T>
ListNode<T>::ListNode() :
    next(nullptr), 
    prev(nullptr), 
    data{}
{}

template <typename T>
ListNode<T>::~ListNode(){
	delete next;
	delete prev;
	//cout<<"deleted Node"<<endl;
}
#endif
