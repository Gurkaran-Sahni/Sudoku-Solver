#include <iostream>
#include <fstream>
#include<time.h>
#define ORDER 9
using namespace std;

int checkRow(int row, int num); 
int checkColumn(int column, int num);
int checkSquare(int row, int column, int num);
int checkSolution() ;

extern int sudoku[ORDER][ORDER];
int checkRow(int row, int num) 
{
  int foundnum = 0;
  for (int i = 0; i < 9; i++) {
    if (sudoku[row][i] == num) {
      foundnum = 1;
      break;
    }
  }
  if (foundnum == 1)
    return 0;
  else
    return 1;
}

int checkColumn(int column, int num) 
{
  int foundnum = 0;
  for (int i = 0; i < 9; i++) {
    if (sudoku[i][column] == num) {
      foundnum = 1;
      break;
    }
  }
  if (foundnum == 1)
    return 0;
  else
    return 1;
}

int checkSquare(int row, int column, int num) 
{
  int foundnum = 0;
  int startIndexRow = (row-row%3);
  int startIndexColumn = (column-column%3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (sudoku[startIndexRow + i][startIndexColumn + j] == num ){
        foundnum = 1;
        break;
      }
    }
  }
  if (foundnum == 1)
    return 0;
  else
    return 1; 
}

extern int sudoku[ORDER][ORDER];
int check (int y[]);
int temp[ORDER];


// All the *check functions read the respective elements to a linear array and 
//pass it to the check() function. Check function searches for multiple
//occurences of numbers, starting from the first element.

//Checks for duplications in each row 
int rowCheck ( int x[ORDER][ORDER]) {
  for (int i=0; i<ORDER; i++) {
    for (int j= 0; j<ORDER; j++)
      temp[j] = x[i][j];
			
    if ( check (temp) == 0 )
      return 0;
  }
  return 1;
}

//Main Check function								
int check (int y[ORDER]) {
  int lineartemp;
  for (int i=0; i<ORDER; i++) {
    lineartemp = y[i];
    for (int j=i+1; j<ORDER; j++) { //searches for duplications
      if (y[j] ==  lineartemp)
	return 0;
	  }
  }
  return 1;
}

//Checks for duplications in each column
int columnCheck ( int x[ORDER][ORDER]) {
  for (int i=0; i<ORDER; i++) {
    for (int j= 0; j<ORDER; j++)
      temp[j] = x[j][i];
		
    if ( check (temp) == 0 )
      return 0;
  }
  return 1;
}			

//Checks for duplaication in all 9 subsquares
int SquaresCheck (int x[ORDER][ORDER]) {
  //column and row loops set the starting index for each subsquare.
  //ie (since I put column loop first),
  //[0][0], [3][0], [6][0], [0][3], [3][3], [6][3], [0][6],[3][6], [6][6]
  // i and j  are usual iterators to create the linear array,
  // and k iterates index of linear array (temp).   

  int i;
  int j;
  int column;
  int row;
  int k;
	
  for (column=0; column <= 6; column += 3) {
    for (row=0; row <= 6; row += 3) {
      for (k=0, i=0; i<3; i++) {
	for (j=0; j<3; j++)
	  temp[k++] = x[row+i][column+j];
      }
      if (check(temp) ==0)
	return 0;		
    }
  }
	
  return 1;
}

int checkSolution() 
{
  if ( !rowCheck(sudoku) || !columnCheck(sudoku) || !SquaresCheck(sudoku) )
     return 0;
  else
     return 1;
}

int sudoku[ORDER][ORDER] = {0};
int isClueGiven[ORDER][ORDER] = {0};
int prevPosition[ORDER][ORDER][2];
int placeNum(int row, int column);


void print(int matrix[ORDER][ORDER])
{
  for (int i = 0; i < ORDER; i++) {
    for (int j = 0; j < ORDER; j++)
      cout << matrix[i][j] << " ";
    cout << endl;
  }
    
  cout << endl;
  return;
}


void storePositions()
{
  int temprow, tempcolumn;
  temprow = -1;
  tempcolumn = -1;
    
  for (int row = 0; row < 9; row++) {
    for (int column = 0; column < 9; column++) {
      if (isClueGiven[row][column] == 0) {
	prevPosition[row][column][0] = temprow;
	prevPosition[row][column][1] = tempcolumn;
	temprow = row;
	tempcolumn = column;
      }
    }
  }
}


int goBack(int &row, int &column)
{
  int trow, tcolumn;
  
  if (row == 0 && column == 0)
    return 0;
  sudoku[row][column] = 0;
    
  trow = prevPosition[row][column][0];
  tcolumn = prevPosition[row][column][1];
  tcolumn -= 1;
    
  row = trow;
  column = tcolumn;
    
  return 1;
}


int placeNum(int row, int column)
{
  if(isClueGiven[row][column] == 1)
    return 1;
    
  for (int num = sudoku[row][column] + 1; num <= 9; num++) {
    if (checkRow(row,num) && checkColumn(column, num) && checkSquare(row,column,num) ) {
      sudoku[row][column] = num;
      return 1;
    }
  }
    
  sudoku[row][column] = 0;
    
  return 0;
}


int solveSudoku()
{
  for (int row = 0; row < 9; row++) {
    for (int column = 0; column < 9; column++) {
      if (!placeNum(row, column)) {
	sudoku[row][column] = 0;
	if (!goBack(row, column))
	  return 0;
      }
    }
  }
    
  return 1;
}


int main(int argc, char* argv[])
{
  
   
  
 
    cout <<"Enter 81  elements (0s for cells without clues) :" << endl;

    for ( int row = 0; row < ORDER; row++) {
      for ( int column = 0; column < ORDER; column++) {
	cin >> sudoku[row][column];
	if (sudoku[row][column] !=0)
	  isClueGiven[row][column] = 1;
      }
    }

    print (sudoku);
  float startTime = (float)clock()/CLOCKS_PER_SEC;
    storePositions();
    solveSudoku();
    
    print(sudoku); 
    float endTime = (float)clock()/CLOCKS_PER_SEC;
float timeElapsed = endTime - startTime;
printf("\nTime taken= %f \n",timeElapsed);
     return 0;
}

