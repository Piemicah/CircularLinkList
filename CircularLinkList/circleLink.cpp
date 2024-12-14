#include<iostream>

using namespace std;

class Node
{
public:
	Node(int v, Node* n)
	{
		value = v;
		next = n;
	}

	void setNext(Node* n)
	{
		next = n;
	}

	Node* getNext()
	{
		return next;
	}

	int getValue()
	{
		return value;
	}
private:
	int value;
	Node* next;
};

class CircleList
{
public:
	CircleList()
	{
		head = tail = nullptr;
	}
	~CircleList();
	void addBack(int v);
	void addFront(int v);
	void print();
	void clear();
	int size();
	bool empty()
	{
		return (head == nullptr);
	}

	void removeFront();
	void removeBack();
	int kill();
private:

	Node* head, * tail;
};

CircleList::~CircleList() {
	while (head != tail) {
		Node* node = head->getNext();
		delete head;
		head = node;
	}
	
}

void CircleList::addBack(int v)
{
	if (tail != nullptr)
	{
		Node* n = new Node(v, head);
		tail->setNext(n);
		tail = n;
	}

	else
	{
		head = tail = new Node(v, nullptr);
	}

}

void CircleList::addFront(int v) {
	
	if (head != nullptr)
	{
		//create new node
		Node* newHead = new Node(v, head);
		tail->setNext(newHead);
		head = newHead;
	}
	else
	{
		head = tail = new Node(v, nullptr);
	}
}

void CircleList::print()
{
	if (empty()) { cout << "" << endl; return; }
	Node* n = head;
	do
	{
		cout << n->getValue() << "==>";
		n = n->getNext();
	} while (n != head);
}



int CircleList::size() {
	if (empty()) return 0;

	int s = 1;
	Node* n = head;
	while (n->getNext() != head) {
		n = n->getNext();
		s++;
	}

	return s;
}

void CircleList::clear() {
	while (!empty()) {
		removeFront();
	}
}

void CircleList::removeFront()
{
	if (empty()) return;
	if (head->getNext() != head)
	{
		Node* second = head->getNext();
		delete head;
		head = second;
		tail->setNext(head);
	}
	else {
		
		head = tail = nullptr;
	}

}

void CircleList::removeBack() {
	if (empty()) return;


	if (size() == 1)
	{
		head = tail = nullptr;
		return;
	}

	//create node before the last node
	Node* secondToTheLast = head;

	for (int i = 0; i < size() - 2; i++)
	{
		secondToTheLast = secondToTheLast->getNext();
	}

	//second to the last points to head
	secondToTheLast->setNext(head);

	delete tail;
	tail = secondToTheLast;

}

int CircleList::kill()
{ 
	Node* live;
	Node* dead;

	while (head->getNext()!=head)
	{
		dead = head->getNext();
		live= head->getNext()->getNext();
		delete dead;
		head->setNext(live);
		head = live;
	}
	return head->getValue();
}

void main()
{
	
	cout << "\nOriginal List:\n";
	CircleList list;
	for (int i = 1; i <= 10; i++) list.addBack( i);
	list.print();
	cout << "\nSize = " << list.size() << endl;

	/*/cout << "\nAfter kill():  ";
	cout <<"Survivor = "<< list.kill() << endl;
	cout << "\nSize = " << list.size() << endl;*/


	cout << "\nafter calling removeFront twice:\n";
	list.removeFront();
	list.removeFront();
	list.print();
	cout << "\nSize = " << list.size() << endl;

	cout << "\nafter calling removeBack twice:\n";
	list.removeBack();
	list.removeBack();
	list.print();
	cout << "\nSize = " << list.size() << endl;

	cout << "\nAfter calling clear():\n";
	list.clear();
	list.print();
	cout << "\nSize = " << list.size() << endl;


	cout << "\nafter calling addBack twice:\n";
	list.addBack(8);
	list.addBack(9);
	list.print();
	cout << "\nSize = " << list.size() << endl;


	cout << "\nafter calling addFront twice:\n";
	list.addFront(12);
	list.addFront(29);
	list.print();
	cout << "\nSize = " << list.size() << endl;
}

