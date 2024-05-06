#include <iostream>
#include <ctime>
#include <cstdlib>

class LinkedList
{
    public :
        class Node
        {
            public :
                Node() : next(nullptr), data(0) {}
                Node(int d) : next(nullptr), data(d) {}
                Node(Node *n) : next(n), data(0) {}
                Node(Node *n, int d) : next(n), data(d) {}
                int data ;
                Node *next ;

		int &getData() { return data; };
		Node *&getNext() { return next; };

		friend std::ostream &operator<<( std::ostream &out, Node *n )
		{
			out << n->getData();
			return out;
		};
        };

        LinkedList() : head (nullptr) {};

	Node *&getHead() { return head; };
	
        ~LinkedList() 
	{
		if ( head != nullptr )
		{
			Node *pTraverse = head;
			while ( pTraverse->next != nullptr )
			{
				head = pTraverse->next;
				delete pTraverse;
				pTraverse = head;
			}
			
			delete head;
		}
	};

        bool addFromHead(int d) 
	{
		Node *newNode = new Node(d);
		newNode->next = head;
		head = newNode;

		return true;
	};
	
        bool addFromTail(int d) 
	{
		Node *newNode = new Node(d);
		if ( head == nullptr )
		{
			head = newNode;
			return true;
		}

		// First find the tail
		Node *pTraverse = head;
		while( pTraverse->next != nullptr )
			pTraverse = pTraverse->next;

		pTraverse->next = newNode;

		return true;
	};

        bool removeFromHead() 
	{
		if ( head == nullptr ) return false;
		Node *temp = head;
		head = head->next;
		delete temp;

		return true;
	};

        bool removeFromTail() 
	{
		if ( head == nullptr ) 
			return false;

		if ( head->next == nullptr ) 
		{
			delete head; 
			head = nullptr;
			return true;
		}

		Node *pTraverse = head;

		while( pTraverse->next->next != nullptr ) 
			pTraverse = pTraverse->next;

		delete pTraverse->next;
		pTraverse->next = nullptr;

		return true;
	};

        friend std::ostream &operator<<( std::ostream &out, LinkedList *l) 
	{
		out << "{";
		if ( l->getHead() != nullptr ) 
		{
			Node *pTraverse = l->getHead();
			while ( pTraverse->next != nullptr )
			{
				out << pTraverse << ", ";
				pTraverse = pTraverse->next;
			}
			out << pTraverse;
		}

		out << "}" << std::endl;

		return out;
	};

        size_t getSize() const 
	{
		size_t size = 0;
		if ( head == nullptr ) return size;

		Node *pTraverse = head;
		while ( pTraverse->next != nullptr )
		{
			pTraverse = pTraverse->next;
			size++;
		}

		return ++size;
	};

    protected :
        Node *head ;
} ;

int main() 
{
	LinkedList *l = new LinkedList();
	srand( time(0) );
	
	std::cout << "List Size: " << l->getSize() << std::endl;

	for( size_t i = 0; i < 10; ++i )
	{
		if( i % 2 ) l->addFromHead( rand() % 100 );
		else l->addFromTail( rand() % 100 - 100 ); 
		std::cout << l;
	}

	std::cout << l << std::endl;
	std::cout << "List Size: " << l->getSize() << std::endl;

	l->removeFromHead();
	std::cout << l << std::endl;

	l->removeFromTail();
	std::cout << l << std::endl;

	std::cout << "List Size: " << l->getSize() << std::endl;

	delete l;

	return 0;
	
}
