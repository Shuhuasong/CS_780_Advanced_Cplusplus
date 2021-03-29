#include<iostream>
#include<cstdlib>
#include<cassert>
#include<vector>
using namespace std;

template <class T>
class SA{
private:
    int low, high;
    T* p;
public:
    // default constructor
    //allows for writing things like SA a;
    SA(){
        low = 0; high = -1; p = nullptr;
    }
    //2 parametr constructor lets us write
    //SA x(10, 20)
    SA(int l, int h){
        if(h-l+1<=0){
            cout << "constructor error in bounds definition" << endl;
            exit(1);
        }
        low = l;
        high = h;
        p = new T[h-l+1];
    }

    //single parameter constructor let us create a SA almost like a "standard" one by writing
    //SA x(10); and getting an array x indexed from 0 to 9
    SA(int i){
       // cout << "single parameter constructor--test" << endl;
        low = 0;
        high = i - 1;
        p = new T[i];
       //cout << p[i] << "--test2" << endl;
    }

    //copy constructor for pass by value and initialization
    SA(const SA &s){
       int size = s.high - s.low + 1;
       p = new T[size];
       for(int i=0; i<size; i++){
           p[i] = s.p[i];
       }
       low = s.low;
       high = s.high;
    }

    //destructor
    ~SA(){
        delete[] p ;
    }

    //overload[], let us write SA x(10, 20); x[15] = 100;
    T& operator[](int i){
        if(i<low || i>high){
            cout << "index " << i << " out of range" << endl;
            exit(1);
        }
        return p[i-low];
    }

    //overload assignment lets us assign one SA to another
    SA &operator=(const SA &s){
        if(this==&s){ return *this; }
        delete []p;
        int size = s.high - s.low + 1;
        p = new T[size];
        for(int i=0; i<size; i++){
            p[i] = s.p[i];
        }
        low = s.low;
        high = s.high;
        return *this;
    }
    //overloads << so we can directly print SAs
    friend ostream&  operator<<(ostream& os, const SA<T>& s){
        int size = s.high - s.low + 1;
        for(int i=0; i<size; i++){
            cout << s.p[i] << " ";
        }
        return os;
    }
};



template <class T>
class Matrix{
private:

    int low1, high1; // for row direction
    int low2, high2; //for column direction

public:
    SA<SA<T>*> *matrix;
    Matrix(){
        low1 = 0, high1 = -1;
        low2 = 0, high2 = -1;
        matrix = nullptr;
    }

   /* Matrix(int l, int h){
        if(h-l+1<=0){
            cout << "Constructor Error in Bound Definition!" << endl;
            exit(0);
        }
        low = l;
        high = h;
        matrix = new SA<T>[high-low+1];
    } */

    const int getRows(){
        return high1-low1+1;
    }
    const int getCols(){
        return high2-low2+1;
    }


    Matrix(int rows, int cols){
        low1 = 0, high1 = rows-1;
        low2 = 0, high2 = cols-1;
        matrix = new SA<SA<T>*>(rows);
        for(int i=0; i<rows; i++){
            (*matrix)[i] = new SA<T>(cols);
        }
    }
    Matrix(int r1, int c1, int r2, int c2){
        if(r2-r1+1<=0){
            cout << "Constructor Error in Bound of Row Definition!" << endl;
            exit(1);
        }
        if(c2-c1+1<=0){
            cout << "Constructor Error in Bound of Row Definition!" << endl;
            exit(1);
        }
        low1 = r1; high1 = r2;
        low2 = c1; high2 = c2;
        int rows = r2-r1+1;
        int cols = c2-c1+1;
        matrix = new SA<SA<T>*>(rows);
        for(int i=r1; i<=r2; i++){
            (*matrix)[i] = new SA<T>(cols);
        }
    }


    ~Matrix(){
        int rows = high1-low1+1;
        int cols = high2-low2+1;
        for(int i=0; i<rows; i++){
            delete (*matrix)[i];
        }
        delete matrix;
    }
    /*  Matrix(const Matrix &m){
        int numRows = m.high1 - m.low1 + 1;
        int numCols = m.high2 - m.low2 + 1;
        for(int i=0; i<numRows; i++){
            for(int j=0; j<numCols; j++){
                matrix[i][j] = m->matrix[i][j];
            }
        }
        low1 = m.low1; high1 = m.high1;
        low2 = m.low2; high2 = m.high2;
    } */

    SA<T>& operator[](int r){
        int rows = high1 - low1 + 1;
        if(r<0 || r>=rows){
            exit(1);
        }
        return *((*matrix)[r]);
    }

  /*  const int& operator()(int x, int y){
        return matrix[x][y];
    }  */

    friend ostream& operator<<(ostream& os, Matrix & m){
        os << endl;
        for(int i=0; i<m.getRows(); i++){
            for(int j=0; j<m.getCols(); j++){
                os << (*(*m.matrix)[i])[j] << " ";
            }
            os << endl;
        }
        return os;
    }

 /*   SA &operator=(const SA &s){
        if(this==&s){ return *this; }
        delete []p;
        int size = s.high - s.low + 1;
        p = new T[size];
        for(int i=0; i<size; i++){
            p[i] = s.p[i];
        }
        low = s.low;
        high = s.high;
        return *this;
    }

    Matrix<T>& operator=(const Matrix &m){
        if(this==&m){
            return *this;
        }
        for(int i=0; i<this->getRows(); i++){
            this->matrix[i].~SA();
        }
        this->matrix.~SA();
        int rows = m.high1-m.low1+1;
        int cols = m.high2-m.low2+1;
        this->matrix = SA<SA<T>>(0, rows-1);
        for(int i=0; i<rows; i++){
            this->matrix[i] = SA<T>(0, cols-1);
            for(int j=0; j<cols; j++){
               matrix[i] = m.matrix[i];
            }
        }
    } */

    Matrix<T>* operator*(Matrix& a){
        if(this->getRows()!= a.getCols()){
            cout << "Error! the row of 1st matrix is not the same with the column of 2nd matrix!" << endl;
            exit(1);
        }
        cout << "The result for Multiplying these two matrix is : " << endl;
        int rows = this->getRows();
        int cols = a.getCols();
        Matrix<T> *results = new Matrix<T>(rows, cols);
        for(int i=0; i<rows; i++){
            for(int j=0; j<cols; j++){
                //int repeat = a.getRows();
                int repeat = this->getCols();
                T  totalValue = 0;
                for(int k=0; k<repeat; k++){
                    totalValue = totalValue + (*this)[i][k] * a[k][j];
                    //results->matrix[i][j] += (*this)[i][j] * a[i][j];
                }
                (*results)[i][j] = totalValue;
               cout << "data: " << (*results)[i][j] << endl;
            }
        }
     /*   cout << "In Class Result: " << endl;
        for(int i=0; i<rows; i++){
            for(int j=0; j<cols; j++){
                cout << " " << results->matrix[i][j];
            }
            cout << endl;
        } */

       return results;
    }
};

  int main(){

      Matrix<int> a(2, 3), b(3, 2);
      vector<int> nums1 = {3, -2, 5, 3, 0, 4};
      vector<int> nums2 = {2, 3, -9, 0, 0, 4};
      //int r1 = 2, c1 = 3, r2 = 3, c2 = 2;
    /*  int r1 = a.getRows();
      int c1 = a.getCols();
      int r2 = b.getRows();
      int c2 = b.getCols(); */
      //cout << r1 << " " << c1 << " " << r2 << " " << c2 << endl;
      a[0][0] = 3; a[0][1] = -1; a[0][2] = 5;
      a[1][0] = 3; a[1][1] = 0; a[1][2] = 4;

      b[0][0] = 2; b[0][1] = 3;
      b[1][0] = -9; b[1][1] = 0;
      b[2][0] = 0; b[2][1] = 4;
      /*      int k = 0;
            for(int i=0; i<r1; i++){
                for(int j=0; j<c1; j++){
                   // cout << "Enter element a" << i << j << ": ";

                    a[i][j] = nums1[k++];
                }
            }
            cout << endl;
           // cout << "Please enter elements for 2nd matrix: " << endl;
           k = 0;
            for(int i=0; i<r2; i++) {
                for (int j = 0; j < c2; j++) {
                    //cout << "Enter element b" << i << j << ": ";
                    b[i][j]= nums2[k++];
                }
            } */
      cout << a;
      cout << b;

      Matrix<int>* results =  a * b;

      cout <<  " Results:  " << results->getRows() << " " << results->getCols() << endl;
      cout << (*results) << endl;
      //Initialize the result of matrix
      /* for(int i=0; i<r1; i++){
          for(int j=0; j<c2; j++){
              cout << " " << results.matrix[i][j];
          }
          cout << endl;
      }*/
      return 0;

  }





/*
 3 https://www.programiz.com/cpp-programming/examples/matrix-multiplication
 https://www.daniweb.com/programming/software-development/threads/128460/safe-array-within-a-safe-array-implementation


 Enter rows and column for first matrix: 2
3
Enter rows and column for second matrix: 3
2

Enter elements of matrix 1:
Enter elements a11: 3
Enter elements a12: -2
Enter elements a13: 5
Enter elements a21: 3
Enter elements a22: 0
Enter elements a23: 4

Enter elements of matrix 2:
Enter elements b11: 2
Enter elements b12: 3
Enter elements b21: -9
Enter elements b22: 0
Enter elements b31: 0
Enter elements b32: 4
 */