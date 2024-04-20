#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "Cell.h"

class Node 
{
  Cell data;
  Node *previous;
  Node *next;
public:
  Node() : previous(nullptr), next(nullptr) {};
  Node(Cell &c) 
    : previous(nullptr), next(nullptr) 
  {
    data = Cell(c);
  };

  ~Node() {};

  void setData( const Cell &c ) { data = c; }
  void setPrevious(Node *n) { previous = n; };
  void setNext( Node *n ) { next = n; };

  Cell& getData() { return data; }
  Node* getPrevious() { return previous; };
  Node* getNext() { return next; };

  Node &operator=( const Node& other )
  {
    data = other.data;
    previous = other.previous;
    next = other.next;
    
    return *this;
  } 

  friend std::ostream &operator<<( std::ostream &out, const Node& n )
  {
    out << n.data;
    return out;
  }
};

class Stack 
{
  Node *top;
public:
  Stack() : top(nullptr) {};

  ~Stack()
  {
    // Delete each node of the Stack 
    Node *temp = nullptr;
    while(top != nullptr)
    {
      temp = top->getPrevious();
      delete top;
      top = temp;
    }
  }

  Node &getTop() { 
    if ( top == nullptr )
      throw std::logic_error("Stack is empty");
    return *top; 
  };

  bool isEmpty() { return top == nullptr; }
  int size( Node n ) 
  {
    return (n.getPrevious() == nullptr ) 
      ? 1 : size(*(n.getPrevious())) + 1;
  }

  void push( Node &n )
  {
    Node *newNode = new Node;
    newNode->setData(n.getData());
    newNode->setPrevious(top);

    if (top)
    {
      top->setNext(newNode);
      top = newNode;
    } else {
      top = newNode;  
    }
  }

  void pop() 
  {
    if(top != nullptr)
    {
      Node *temp = top->getPrevious();
      delete top;
      top = temp;
    }
  }

  void flip(int index) 
  {
    // Flip the stack at a specified index
    // EXAMPLE:(1,1) (1,2) (2,2) (3,2) (3,3)
    // Flip at index 2 will give
    // => (1,1) (3,3) (3,2) (2,2) (1,2)
    int stackSize = size( getTop() );
    if ( index > 0 && index < stackSize) 
    {
      Stack temp;
      Node *head;
      while (stackSize >= index)
      {
        temp.push(getTop());
        pop();

        if (temp.size(temp.getTop()) == 1) 
          head = &temp.getTop();
        
        stackSize--;
      }

      // Pushing the removed elements in reverse order
      add(*head);
    }
    else 
      throw std::out_of_range("Flip index out of range");

  }

  int add( Node n )
  {
    if ( n.getNext() == nullptr )
    {
      push(n);
      return 0;
    }
    
    push(n);
    return add( *(n.getNext()) );
  }

  friend std::ostream &operator<<( std::ostream &out, const Stack& s)
  {
    Node* ptr = s.top;
    size_t i = 0;
    while (ptr != nullptr) {
      out << ptr->getData();
      ptr = ptr->getPrevious();
      if ((i + 1) % 5 == 0) out << std::endl; 
      if (ptr) out << " -> ";
      ++i;
    }
    
    return out;
  }

};

#endif 
