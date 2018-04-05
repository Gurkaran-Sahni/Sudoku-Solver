#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define N 9
#define ORDER 9
#define UNASSIGNED 0
using namespace std;
//first backtracking 
bool FindUnassignedLocation(int grid[N][N], int &row, int &col);

bool isSafe(int grid[N][N], int row, int col, int num);

 

/* assign values to all unassigned locations for Sudoku solution  

 */
bool SolveSudoku(int grid[N][N])

{

    int row, col;

    if (!FindUnassignedLocation(grid, row, col))

       return true;

    for (int num = 1; num <= 9; num++)

    {

        if (isSafe(grid, row, col, num))

        {

            grid[row][col] = num;

            if (SolveSudoku(grid))

                return true;

            grid[row][col] = UNASSIGNED;

        }

    }

    return false;

}

/* Searches the grid to find an entry that is still unassigned. */

bool FindUnassignedLocation(int grid[N][N], int &row, int &col)

{

    for (row = 0; row < N; row++)

        for (col = 0; col < N; col++)

            if (grid[row][col] == UNASSIGNED)

                return true;

    return false;

}

/* Returns whether any assigned entry n the specified row matches 

   the given number. */

bool UsedInRow(int grid[N][N], int row, int num)

{

    for (int col = 0; col < N; col++)

        if (grid[row][col] == num)

            return true;

    return false;

}

/* Returns whether any assigned entry in the specified column matches 

   the given number. */

bool UsedInCol(int grid[N][N], int col, int num)

{

    for (int row = 0; row < N; row++)

        if (grid[row][col] == num)

            return true;

    return false;

}

/* Returns whether any assigned entry within the specified 3x3 box matches 

   the given number. */

bool UsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num)

{

    for (int row = 0; row < 3; row++)

        for (int col = 0; col < 3; col++)

            if (grid[row+boxStartRow][col+boxStartCol] == num)

                return true;

    return false;

}

/* Returns whether it will be legal to assign num to the given row,col location. 

 */

bool isSafe(int grid[N][N], int row, int col, int num)

{

    return !UsedInRow(grid, row, num) && !UsedInCol(grid, col, num) &&

           !UsedInBox(grid, row - row % 3 , col - col % 3, num);

}

/* print grid  */

void printGrid(int grid[N][N])

{

    for (int row = 0; row < N; row++)

    {

        for (int col = 0; col < N; col++)

            cout<<grid[row][col]<<"  ";

        cout<<endl;

    }

}

void main_backtrack()

{

    int grid[N][N];
    cout<<"\nSolving using Backtrack algorithm. \n";
    cout<<"\nEnter the 81 elements of the Sudoku row-major wise.\n";
    cout<<"--(Considering 0 is entered for unknown elements)--\n";
    for(int i=0;i<9;i++)
    for(int j=0;j<9;j++)
    {
    cin>>grid[i][j];
    if(grid[i][j]<0 && grid[i][j]>9)
    grid[i][j]=UNASSIGNED;}

    float startTime = (float)clock()/CLOCKS_PER_SEC;
    if (SolveSudoku(grid) == true)

          printGrid(grid);

    else

        cout<<"No solution exists"<<endl;
	float endTime = (float)clock()/CLOCKS_PER_SEC;
	float timeElapsed = endTime - startTime;
	printf("\nTime taken= %f seconds.\n",timeElapsed);

}

//now using brute-force approach


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
      cout << matrix[i][j] << "  ";
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


void main_bruteforce()
{
  
   
  
 
    cout <<"\nSolving using Brute-Force algorithm.\n";
    cout<<"\nEnter the 81 elements of the Sudoku row-major wise.\n";
	cout<<"--(Considering 0 is entered for unknown elements)--\n";
    for ( int row = 0; row < ORDER; row++) {
      for ( int column = 0; column < ORDER; column++) {
	cin >> sudoku[row][column];
	if (sudoku[row][column] !=0)
	  isClueGiven[row][column] = 1;
      }
    }
  float startTime = (float)clock()/CLOCKS_PER_SEC;
    storePositions();
    solveSudoku();
    
    print(sudoku); 
    float endTime = (float)clock()/CLOCKS_PER_SEC;
float timeElapsed = endTime - startTime;
printf("\nTime taken= %f seconds.\n\n",timeElapsed);
    
}

int main()
{
	int ch;char ch1;
	do
	{
	cout<<"---------------------------------------------------------------\n";
	cout<<"|Sudoku solving using BackTracking and Brute Force algorithms.|\n";
	cout<<"|\t\t\t\t\t\t\t      |";
	cout<<"\n|Enter your choice type:\t\t\t\t      |\n";
	cout<<"|\t\t\t\t\t\t\t      |\n";
	cout<<"|1 - Solve using Backtracking algorithm.\t\t      |\n";
	cout<<"|2 - Solve using Brute-Force algorithm.\t\t\t      |\n";
	cout<<"|3 - To exit the terminal screen.\t\t\t      |\n";
	cout<<"---------------------------------------------------------------\n";
	cout<<"Choice: ";
	cin>>ch;
	if(ch==1)
	main_backtrack();
	else if(ch==2)
	main_bruteforce();
	else if(ch==3)
	{
	system("cls");
	cout<<"Program Terminated by the user.\n";
	}
	}while(ch!=3);
	
	return 0;
}


