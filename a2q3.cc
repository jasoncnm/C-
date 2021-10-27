// You need not use this starter code if you do not want to
// Your code might be marked for style
// Note that while global variables are typically considered
// poor style, this question explicitly allows them

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

const int maxStudents = 20;
const int maxAssignments = 10;

//array to store student userids
string students[maxStudents];

//array to store student final marks
int marks[maxStudents];

/* 
 * Add additional arrays or globals here
 * if needed e.g. to store assignment and exam 
 * max marks, weights etc
 */
int TasksMaxMarks[maxAssignments + 2];
int TasksWeights[maxAssignments + 2];
int ValidStudentCount = 0;

/*
  Required: same length
*/
void CopyArray(int Src[], int Dest[], const int &Length)
{
  for (int x = 0; x < Length; x++)
  {
    Dest[x] = Src[x];
  }
}

//
//Requires: the student is valid
int CalculateMarks(int Scores[], const int &Length)
{
  int *TempTasksWeights = new int [Length];
  CopyArray(TasksWeights, TempTasksWeights, Length);
  int Marks = 0;
  int NumAssignment = Length - 2;
  for (int TaskIndex = 0; TaskIndex < Length; TaskIndex++)
  {
    int MarkAssignment = Scores[TaskIndex];
    if (MarkAssignment == -1)
    {
      int ACCWeights = TempTasksWeights[TaskIndex];
      int WeightsIncreaseNumber = (NumAssignment - TaskIndex - 1);
      if (WeightsIncreaseNumber != 0)
      {
        int WeigthsIncrease = ACCWeights / WeightsIncreaseNumber;
        int WeigthsIncreaseLast = ACCWeights % WeightsIncreaseNumber;
        for (int i = TaskIndex + 1; i < NumAssignment; i++)
        {
          if (i == (NumAssignment - 1))
          {
            TempTasksWeights[i] += WeigthsIncrease + WeigthsIncreaseLast;
          }
          else 
          {
            TempTasksWeights[i] += WeigthsIncrease;
          }
        }
      }
      else 
      {
        TempTasksWeights[Length - 1] += ACCWeights;
      }
    }
    else
    {
      int MaxAssignmentMarks = TasksMaxMarks[TaskIndex];
      int WeightAssignment = TempTasksWeights[TaskIndex]; 
      int WeightedAssignment = (MarkAssignment * WeightAssignment) / MaxAssignmentMarks;
      Marks += WeightedAssignment;
    }
  }
  delete[] TempTasksWeights;
  return Marks;
}

/*
 * Reads from standard input the course description
 * Stores this information in some global variables
 */
void readCourseInfo(const int &AssignmentNumber)
{
  for (int x = 0; x < (AssignmentNumber + 2); x++)
  {
    string Input;
    cin >> Input;
    istringstream MaxMarks{Input};
    MaxMarks >> TasksMaxMarks[x];
    cin >> Input;
    istringstream Weights{Input};
    Weights >> TasksWeights[x];
  }
}

/*
 * Reads from standard input student records.
 * If a student record is invalid, produces desired output
 * If student record is valid, computes and stores student's
 * final mark in the course
 */
void readStudentRecords(const int &AssignmentNumber)
{
  const int AmountofTasks = AssignmentNumber + 2;
  string Line;
  ValidStudentCount = 0;
  while (getline(cin, Line))
  {
    string id;
    istringstream Record{Line};
    if (Record >> id)
    {
      int TasksCount = 0;
      int *Array = new int [AmountofTasks];
      bool IsValid = true;
      string MaybeACC;
      while (Record >> MaybeACC)
      {
        
        if (MaybeACC == "ACC")
        {
          TasksCount++;
          if (TasksCount > AssignmentNumber)
          {
            IsValid = false;
            break;
          }
          Array[TasksCount - 1] = -1;
        }
        else 
        {
          int Mark = 0;
          istringstream NotACC{MaybeACC};
          if (NotACC >> Mark)
          {
            TasksCount++;
            if ((0 <= Mark)  && (Mark <= TasksMaxMarks[TasksCount - 1]))
            {
              Array[TasksCount - 1] = Mark;
            }
            else 
            {
              IsValid = false;
              break;
            }
          }
          else
          {
            IsValid = false;
            break;
          }
        }
      }

      if (IsValid && (TasksCount == AmountofTasks))
      {
        students[ValidStudentCount] = id;
        marks[ValidStudentCount] = CalculateMarks(Array, AmountofTasks);
        ValidStudentCount++;
      }
      else
      {
        cout << id << " " << "invalid" << endl;
      }
      delete[] Array;
    }
  }
}

/*
 * Prints the desired output for student's with valid records
 */
void printResults()
{
  int SumMarks = 0;
  cout << "Valid records: " << ValidStudentCount << endl;
  for (int x = 0; x < ValidStudentCount; x++)
  {
    cout << students[x] << " " << marks[x] << endl;
    SumMarks += marks[x];
  } 
  int Average = 0;
  if (ValidStudentCount != 0)
  { 
    Average = SumMarks / ValidStudentCount;
  }
  cout << "Average: " << Average << endl;
}

int main(int argc, char *argv[]) {
  
  //TODO: handle program command line arguments first
  string Course = argv[1];
  int AssignmentNumber = 0;
  if (argc < 3)
  {
    AssignmentNumber = 5;
  }
  else 
  {
    istringstream Arg{argv[2]};
    Arg >> AssignmentNumber;
  }
  cout << Course << endl;
  readCourseInfo(AssignmentNumber);
  readStudentRecords(AssignmentNumber);
  printResults();
  return 0;
}
