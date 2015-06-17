#include <iostream>
using namespace std;
class ListNode
{
	public:
	
		int data;//the data that we will store
		ListNode();
		ListNode(int d);
		~ListNode();
		ListNode *next;//int and ptr and the member variables
};

ListNode::ListNode(int d){
	data = d;
	next = NULL;
	prev = NULL;
}



/////////////above goes in header file///////////////
ListNode::ListNode(){}
ListNode::~ListNode(){
	delete next;
	delete prev;
	cout<<"deleted"<<endl;
}


//must include listNode in naiveList.h file
class NaiveList{
	private:
		ListNode *front;
		ListNode *back;
	public:
		unsigned int size;
		NaiveList();
		~NaiveList();
		void insertFront(int data);
		void removeFront();
		int removeAt(int pos);
		int isEmpty();
		void printList();
		unsigned int getSize();
		int find(int d);

		void insertBack(int data);
		int removeBack();
		void insertAfter(int index, int data);
};

NaiveList::NaiveList(){
	size = 0;
	front = NULL;
	back = NULL:
	
}
NaiveList::~NaiveList(){
	delete front;
	
	cout<<"deleted"<<endl;
}

unsigned int NaiveList::getSize(){
	return size;
}
void NaiveList::insertFront(int data){
	
	ListNode *node = new ListNode(data);
	if(size== 0){
		back = node;
	}
	else{
		front->prev = node;
		node->next = front; //the dot operator in java | 2 member variables, data and next
		
	}
	front = node;
	++size;


}
bool NaiveList::insertAfter(int key, int data){
	ListNode *current = front;
	while(current->data != key)//traverse List
	{
		current = current->next;
		if(current == NULL){
			return false;
		}

	}
	ListNode *newNode = new ListNode(20);
	if(current == back){
		newNode->next = NULL;
		back = newNode;

	}
	else{
		newNode->next = current->next;
		current->next->prev = newNode;
	}
	newNode->prev = current;
	current->next = newNode;
	size++;
	return true;

}
int NaiveList::removeBack(){
	--size;
	ListNode *temp = back;
	//error checking
	back->prev->next = NULL;
	back = back->prev;
	int val = temp -> data;
	delete temp;
	return val;
}
int NaiveList::removeFront(){

	--size;
	//int temp = front->data; for normal linked list
	ListNode *temp = front;
	front->next->prev = NULL;
	//error checking
	front = front->next;
	int val = temp->data;
	delete temp;
	return val;
	/*
	normal linkedlist

	ListNode *ft = front;//& only works for primative types
	front = front->next;
	ft->next = NULL;
	delete ft;
	return temp;*/

}

void NaiveList::printList(){
	ListNode *current = front;

	while(current){
		cout << current->data <<endl;
		current = current->next;
	}

}
int NaiveList::removeAt(int pos)//O(n)
{
	int idx = 0;
	ListNode *current = front;
	ListNode *prev = front;

	while(idx != pos){
		prev = current;
		current = current->next;
		++idx;
	}

	prev->next = current->next;
	current->next = NULL;
	int temp = current->data;
	delete current;
	--size;
	return temp;
}

int NaiveList::find(int d){
	int idx = 0;
	ListNode *current = front;
	while(current != NULL){
		
		if(current->data==d){
			break;
		}
		else{
			current = current->next;
		}
		++idx;
	}
	if(current==NULL){
		idx = -1;
	}
	return idx;
}





//delte
/*
node deleteANode(){
	while(current != )
remove front, back, at 
}





