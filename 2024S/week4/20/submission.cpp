#include <iostream>
#include <string>
#include <cstdlib>

#define MAXSIZE 40
#define PATH " "
#define V_WALL "|"
#define H_WALL "_"
#define CONNECTED true
#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3

class Cell
{
  int p, q;
  bool neighbor[4];
  bool isVisited;
public:
  Cell() : isVisited(false) {};
  Cell(Cell &c) 
  {
    setP(c.getP());
    setQ(c.getQ());
    for( size_t i = 0; i < 4; ++i)
      neighbor[i] = c.getNeighbor(i);
    isVisited = c.getVisitedStatus();
  }

  Cell(int _p, int _q) : isVisited(false) 
  {
    setP(_p);
    setQ(_q);
    for( size_t i = 0; i < 4; ++i)
      neighbor[i] = false;
  }

  void setP(int _p) 
  { 
    p = ( _p > 0 ) ? _p : throw std::invalid_argument("Invalid argument");
  };

  void setQ(int _q) 
  { 
    q = ( _q > 0 ) ? _q : throw std::invalid_argument("Invalid argument"); 
  };

  void setVisitedStatus(bool status) { isVisited = status; };

  int getP() { return p; };
  int getQ() { return q; };
  bool getVisitedStatus() { return isVisited; };
  bool getNeighbor(int index)
  {
    // Returns whether or not a neighbor has been visited
    return ((index >= 0 && index < 4) 
            ? neighbor[index] 
            : throw std::invalid_argument("Invalid argument")); 
  }

  void setNeighbor(int index, bool status)
  {
    neighbor[index] = (index >= 0 && index < 4) 
      ? status 
      : throw std::invalid_argument("Invalid argument");;
  }

  Cell &operator=( const Cell& c )
  {
    // Avoids self-assignment
    if ( this != &c )
    {
      setP(c.p);
      setQ(c.q);
      for ( size_t i = 0; i < 4; ++i )
        neighbor[i] = c.neighbor[i];
      isVisited = c.isVisited;
    }
    return *this;
  }

  bool operator==( const Cell& other )
  {
    if (p != other.p || q != other.q )
      return false;
    for ( size_t i = 0; i < 4; ++i )
      if ( neighbor[i] != other.neighbor[i] )
        return false;

    return true;
  }

  bool operator!=( const Cell& other )
  {
    return !( *this == other );
  }
  
  friend std::ostream &operator<<( std::ostream &out, const Cell& c)
  {
    out << "(" << c.p << ", " << c.q << ")";
    return out;
  }
};

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

  bool contains( Node n, Cell &c)
  {
    if (n.getData() == c) 
      return true;
    else if ( n.getPrevious() == nullptr ) 
      return false;
    else 
      return contains( *(n.getPrevious()), c); 
  }

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
    int stackSize = size( getTop() );
    if ( index > 0 && index < stackSize) 
    {
      Stack temp;
      Node *head;
      for (size_t i = 0; i < stackSize - index + 1; ++i)
      {
        temp.push(getTop());
        pop();

        if (temp.size(temp.getTop()) == 1) 
          head = &temp.getTop();
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


typedef struct Coord {
  int p, q;
  Coord () {};
  Coord(int _p, int _q) : p(_p), q(_q) {};
  friend std::ostream &operator<<( std::ostream &out, const Coord& c)
  {
    out << "(" << c.p << ", " << c.q << ")";
    return out;
  }
} Coord;

class Grid 
{
private:
  int row, col;
  Coord position;
  Stack visited;
  Cell *board;
public:
  explicit Grid(int m, int n) 
    : row((m > 0 && m < MAXSIZE) 
          ? m : throw std::out_of_range("Row out of range.")), 
    col((n > 0 && n < MAXSIZE) 
        ? n : throw std::out_of_range("Row out of range.")), 
    board( new Cell[ row * col ])
  {
    size_t i = 0, j = 0;
    for ( i = 0; i < row; ++i ) 
      for ( j = 0; j < col; ++j )
        board[i * col + j] = Cell(row - i, j + 1);
  };

  ~Grid() 
  {
    delete[] board;
  }

  void setPosition( int p, int q )
  {
    position.p  = (p >= 0 && p <= row ) 
    ? p : throw std::invalid_argument("Invalid p coordinate for cell position.");
    position.q = (q >= 0 && q <= col) 
      ? q : throw std::invalid_argument("Invalid q coordinate for cell position.");
    updateVisited();
  };

  bool hasUnvisitedNeighbor(Cell &c) 
  {
    Coord pos(c.getP(), c.getQ());
    int index =  0;
    bool visited = false;

    if (pos.p < row) 
    {
      index = getArrayIndex(pos.p + 1, pos.q);
      visited = board[index].getVisitedStatus();
      if (!visited) return true; 
    }
    
    if (pos.p > 1) 
    {
      index = getArrayIndex(pos.p - 1, pos.q);
      visited = board[index].getVisitedStatus();
      if (!visited) return true; 
    }

    if (pos.q > 1) 
    {
      index = getArrayIndex(pos.p, pos.q - 1);
      visited = board[index].getVisitedStatus();
      if (!visited) return true; 
    }
    
    if (pos.q < col) 
    {
      index = getArrayIndex(pos.p, pos.q + 1);
      visited = board[index].getVisitedStatus();
      if (!visited) return true; 
    }

    // Checking UP, DOWN, LEFT and RIGHT in the specified order
    // return ((p.y < row && !(board[  ].getVisitedStatus())) 
    //   || (p.y > 1  && !(board[  ].getVisitedStatus())) 
    //   || ( p.x > 1 && !(board[ (row - p.y) * col + p.x - 2 ].getVisitedStatus())) 
    //   || ( p.x < col && !(board[ ( row - p.y) * col + p.x ].getVisitedStatus())));
    return false;
  }

  int getArrayIndex(Coord &p) { return ( row - p.p) * col + p.q - 1; };
  int getArrayIndex(int p, int q) { return ( row - p) * col + q - 1; };

  void updateVisited()
  {
    // Push the current position to the visited Stack
    int index = getArrayIndex(position);
    if (!(board[index].getVisitedStatus())) {
      board[index].setVisitedStatus(true);
      Node n(board[index]);
      visited.push(n);
    }
  }

  Coord &getPosition(){ return position; }; 

  int getRow() { return row; };
  int getCol() { return col; };
  Stack &getStack() { return visited; };

  void move(int direction) 
  {
    switch (direction) 
    {
      case UP:
        if (position.p < row)
        {
          // Creates a path between the two cells
          board[getArrayIndex(position)].setNeighbor(UP, CONNECTED);
          position.p += 1;
          board[getArrayIndex(position)].setNeighbor(DOWN, CONNECTED);
        }
        break;
      case DOWN:
        if (position.p > 1)
        {
          board[getArrayIndex(position)].setNeighbor(DOWN, CONNECTED);
          position.p -= 1;
          board[getArrayIndex(position)].setNeighbor(UP, CONNECTED);
        }
        break;
      case LEFT:
        if (position.q > 1)
        {
          board[getArrayIndex(position)].setNeighbor(LEFT, CONNECTED);
          position.q -= 1;
          board[getArrayIndex(position)].setNeighbor(RIGHT, CONNECTED);
        }
        break;
      case RIGHT:
        if (position.q < col)
        {
          board[getArrayIndex(position)].setNeighbor(RIGHT, CONNECTED);
          position.q += 1;
          board[getArrayIndex(position)].setNeighbor(LEFT, CONNECTED);
        }
        break;
      default:
        break;
    }
    // Add the new cell visited to the Stack
    updateVisited();
  }

  void processCommand(std::string c) 
  {
    if (c.at(0) == 'F')
    {
      int flipIndex = 0;
      size_t i = 1;
      while (++i < c.length()) 
      {
        flipIndex += ( c[i] >= '0' && c[i] <= '9' ) 
          ? c[i] - '0' 
          : throw std::invalid_argument("Invalid command.");
      }

      // Flip the stack of the visited cells
      visited.flip(flipIndex);
      // std::cout << "Stack flipped =>" << visited << std::endl;
    }
    else 
    {
       switch(c[0]) 
      {
        case 'U':
          move(UP);
          break;
        case 'L':
          move(LEFT);
          break;
        case 'D':
          move(DOWN);
          break;
        case 'R':
          move(RIGHT);
          break;
        default:
          break;
      }
    }
  };

  friend std::ostream &operator<<( std::ostream &out, const Grid& g)
  {
    size_t i = 0, j = 0;

    // First display the top border
    for ( j = 0; j < g.col; ++j )
      out << " " << H_WALL;
    out << std::endl;

    for ( i = 0; i < g.row; ++i )
    {
      for ( j = 0; j < g.col; ++j )
      {
        if ( j == 0 ) out << V_WALL;
        out << (( g.board[ i * g.col + j ].getNeighbor(DOWN) ) ? PATH : H_WALL);
        out << (( g.board[ i * g.col + j ].getNeighbor(RIGHT) ) ? PATH : V_WALL);
      }
      out << std::endl;
    }

    return out;
  }

};

int main() 
{
  int testCases = 0;
  std::cin >> testCases;
  testCases++;

  while(--testCases) 
  {
    int m, n, xi, yi;
    std::string command;
    std::cin >> m >> n >> xi >> yi;
    Grid maze(m, n);
    maze.setPosition(xi, yi);
    while(!(getchar()));
    while (!(maze.getStack().isEmpty())) 
    {
      if (!(maze.hasUnvisitedNeighbor(maze.getStack().getTop().getData())))
         maze.getStack().pop();
      else 
      {
        Cell newPosition = maze.getStack().getTop().getData();
        maze.setPosition(newPosition.getP(), newPosition.getQ());
        
        std::getline(std::cin, command);
        maze.processCommand(command);
        //std::cout << maze << std::endl;
      }
    }

    std::cout << maze << std::endl;

  }

  return 0;
}
