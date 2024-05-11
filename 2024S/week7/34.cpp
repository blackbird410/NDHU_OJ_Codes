#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

class Container {
public:
    virtual void push(int) = 0;
    virtual void pop() = 0;
    virtual int top() const = 0;
    virtual bool empty() const = 0;
};

class Node 
{
  int data;
  Node *next;
public:
  Node() : data(0), next(nullptr) {};
  Node( int _data ) : data(_data), next(nullptr) {};
  int getData() { return data; };
  void setData( int _data )  { data = _data; };

  Node *&getNext() { return next; };
  void setNext( Node *node ) { next = node; };
  friend std::ostream &operator<<( std::ostream &out, Node* n )
  {
    out << n->data;
    return out;
  };
};

class Stack: public Container 
{
private:
  Node *head;
public:
  Stack() : head(nullptr) {};
  ~Stack() 
  {
    while( !empty() )
      pop();
  };

  virtual void push( int data ) override 
  {
    Node *newNode = new Node( data );
    if ( empty() ) 
      head = newNode;
    else 
    {
      newNode->setNext(head);
      head = newNode;
    }
  };

  virtual void pop() override 
  {
    if ( empty() ) throw std::out_of_range("List empty");

    Node *temp = head;
    head = head->getNext();
    delete temp;
  };

  virtual int top() const override 
  {
    if ( empty() ) throw std::out_of_range("List empty");

    return head->getData();
  };

  virtual bool empty() const override 
  {
    return ( head == nullptr );
  };

  virtual Node* getTop() const
  {
    return head;
  };

  void setHead( Node* newHead ) { head = newHead; };
 
  friend std::ostream &operator<<( std::ostream &out, Stack &s )
  {
    if ( !s.empty() )
    {
      Node *temp = s.getTop();
      int spaceCounter = 0;
      while( temp->getNext() != nullptr )
      {
        out << temp << " -> "; 
        temp = temp->getNext();
        spaceCounter = (spaceCounter + 1) % 10;
        if ( !spaceCounter ) out << std::endl;
      }
      out << temp << std::endl;
    }

    return out;
  }
};

class PriorityQueue: public Stack 
{
public:
  PriorityQueue() : Stack() {};
  
  virtual void push( int data ) override 
  {
    Node *head = getTop();
    Node* newNode = new Node(data);
    if ( empty() ) setHead(newNode);
    else if ( head->getNext() == nullptr ) 
    {
      if ( data < head->getData() )
        head->setNext(newNode);
      else 
      {
        newNode->setNext(head);
        setHead(newNode);
      }
    }
    else 
    {
      Node* temp = head;
      if ( data > head->getData() )
      {
        newNode->setNext(head);
        setHead(newNode);
      } 
      else 
      {
        while( temp->getNext() != nullptr ) 
        {
          // Find the next lower priority element
          if ( temp->getNext()->getData() < data ) 
            break;
          temp = temp->getNext();
        };

        // Inserting the node
        newNode->setNext(temp->getNext());
        temp->setNext(newNode);
      }
    }
  };
};

int main (int argc, char *argv[]) 
{
  srand( time(0) );
  PriorityQueue s;

  for ( size_t i = 0; i < 5; ++i )
    s.push( rand() % 10000 );

  std::cout << s;
  std::cout << "Popping elements..." << std::endl;
  s.pop();
  s.pop();
  s.pop();
  s.pop();
  std::cout << s;

  std::cout << "Top: " << s.top() << std::endl;
  
  return 0;
}
