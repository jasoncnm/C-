#include <iostream>
#include <sstream>
#include <string>
using namespace std;

struct IntArray {
  int size; //number of elements the array currently holds
  int capacity; //number of elements the array could hold,
                //given current memory allocation to contents
  int *contents; //the integer array
};

// NOTE: ALLOCATED MEMORY
int * NewArray(int * OldArray, int Fill, int NewLength)
{
  int * NewArray = new int [NewLength];
  for (int Index = 0; Index < Fill; Index++)
  {
    NewArray[Index] = OldArray[Index];
  }
  return NewArray;
}

IntArray readIntArray()
{
  IntArray * Array = new IntArray{0,0,0};
  string Input;
  int Integer;
  string String;
  while (cin >> Input)
  {
    istringstream I{Input};
    if (I >> Integer)
    {
      if (Array->size == 0)
      {
        Array->size += 1;
        Array->capacity = 5;
        Array->contents = new int [5];
      }
      else if (Array->size == Array->capacity)
      {
        int * OldArray = Array->contents;
        int OldLength = Array->size;
        Array->size += 1;
        Array->capacity *= 2;
        Array->contents = NewArray(OldArray, OldLength, Array->capacity);
        delete[] OldArray;
      }
      else 
      {
        Array->size += 1;
      }
      Array->contents[Array->size - 1] = Integer;
      if (I >> String)
      {
        break;
      }
    }
    else
    {
      cin.ignore();
      break;
    }
  }
  IntArray a = *Array;
  delete Array;
  return a;
}

void addToIntArray(IntArray& Array) 
{
  string Input;
  string String;
  int Integer;
  while (cin >> Input)
  {
    istringstream I{Input};
    if (I >> Integer)
    {
      if (Array.size == 0)
      {
        Array.size += 1;
        Array.capacity = 5;
        Array.contents = new int [5];
      }
      else if (Array.size == Array.capacity)
      {
        int * OldArray = Array.contents;
        int OldLength = Array.size;
        Array.size += 1;
        Array.capacity *= 2;
        Array.contents = NewArray(OldArray, OldLength, Array.capacity);
        delete[] OldArray;
      }
      else 
      {
        Array.size += 1;
      }
      Array.contents[Array.size - 1] = Integer;
      if (I >> String)
      {
        break;
      }
    }
    else 
    {
      cin.ignore();
      break;
    }
  }
}

void printIntArray(const IntArray& Array) 
{
  for (int i = 0; i < Array.size; i++)
  {
    if (i == (Array.size - 1))
    {
      cout << Array.contents[i];
    }
    else 
    {
      cout << Array.contents[i] << " ";
    }
  }
  cout << endl;
}


// Do not change this function!

int main() 
{  // Test harness for IntArray functions.
  bool done = false;
  IntArray a[4];
  a[0].contents = a[1].contents = a[2].contents = a[3].contents = nullptr;

  while(!done) {
    char c;
    char which;

    // Note:  prompt prints to stderr, so it should not occur in .out files
    cerr << "Command?" << endl;  // Valid commands:  ra, rb, rc, rd,
                                 //                  +a, +b, +c, +d,
                                 //                  pa, pb, pc, pd, 
                                 //                  q
    cin >> c;  // Reads r, +, p, or q
    if (cin.eof()) break;
    switch(c) { 
      case 'r':
        cin >> which;  // Reads a, b, c, or d
        delete [] a[which-'a'].contents;
        a[which-'a'].contents = nullptr;
        a[which-'a'] = readIntArray();
        break;
      case '+':
        cin >> which;  // Reads a, b, c, or d
        addToIntArray(a[which-'a']);
        break;
      case 'p':
        cin >> which;  // Reads a, b, c, or d
        printIntArray(a[which-'a']);
        cout << "Capacity: " << a[which-'a'].capacity << endl;
        break;
      case 'q':
        done = true;
    }
  }

  for (int i = 0; i < 4; ++i) delete [] a[i].contents;
}
