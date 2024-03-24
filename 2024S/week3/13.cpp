#include <iostream>
#include <string>
using namespace std;

#define SIZE 100

class Matrix {
  int arr[SIZE][SIZE];
  int dim;
public:
  Matrix () : dim(0) {};
  Matrix (int (*arr)[SIZE], int d) {
    this->setMatrix(arr, d);
  }

  Matrix operator=(Matrix& b) {
    this->setMatrix(b.arr, b.getDim());
    return *this;
  }

  void setMatrix(int (*a)[SIZE], int d) {
    int i = 0, j = 0;
    dim = d;
    for (i = 0; i < dim; i++) 
      for (j = 0; j < dim; j++)
        arr[i][j] = a[i][j];
  }

  int getDim() {return dim;}

  void setDim(int d) {dim = d;}
  
  void rotate(string direction) {
    int i = 0, j = 0; 
    int temp[SIZE][SIZE];

    if (dim) {
      if (direction == "right") {
        // Make the rows become columns starting from the bottom
        i = dim;
        while(--i >= 0) {
          for (j = 0; j < dim; j++)
            temp[j][dim - i - 1] = this->arr[i][j];
        }
      } else {
        // Make the columns become rows starting from the left
        j = dim;
        while(--j >= 0) {
          for (i = 0; i < dim; i++)
            temp[dim - j - 1][i] = this->arr[i][j];
        }
      }
      this->setMatrix(temp, dim);
    } else {
      cout << "No element in matrix can be rotated." << endl;
    }
  }

  void print() {
    int i, j;
    if (dim) {
      for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++)
          cout << arr[i][j] << " ";
        cout << endl;
      }
      cout << endl;
    } else {
      cout << "No element in matrix can be printed." << endl;
    }
  }
};

int scan(int (*arr)[SIZE], int* dim) {
  int i , j; 
  cin >> *dim;
  if (*dim > SIZE) return -1;

  for (i = 0; i < *dim; i++) 
    for (j = 0; j < *dim; j++)
      cin >> arr[i][j];

  return 0;
}

int main() {
  int dim;
  string in = "";
  int arr[SIZE][SIZE] = {};
  Matrix m;

  while (in != "stop") {
    cin >> in;
    if (in == "stop") break;

    if(in == "scan") {
      scan(arr, &dim);
      m.setMatrix(arr, dim);
    } else if (in == "rotate") {
        cin >> in;
        if (in == "left") 
            m.rotate("left");
        else
            m.rotate("right");
    }
    else if (in == "print")
      m.print(); 
    else 
      cout << "unknown" << endl;
  }

  return 0;
}
