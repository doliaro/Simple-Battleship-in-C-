//Dominic Oliaro
//Final Project
//Battleship Game

//------------------------
//Requirement #26: Extra Credit
//------------------------  
/************************************************* 
This is a 1 player battleship game against 
a computer that randomly generates enemies.
**************************************************/


//----------------------------------------
//Requirement #09: Errors
//Syntax: These errors come from not following grammatical rules. i.e. not declaring and identifier , or not terminating a statement with a semicolon.
//Logic: This would be something that would not come up as an error when compiled, but something like an infinite loop is good example.
//Runtime: Dividing by 0, or overflow are good examples of this type of error.
//----------------------------------------

#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <cstdlib>
#include <iomanip>
using namespace std;

//------------------------
//Requirement #21: Struct
//------------------------  
struct tools
{
    int pos1;
    int pos2;
};
//--------------------------
//Requirement #22: Class 
//with object called welcome
//--------------------------
class greeting
{
    public:
        string get_welcome();
        void set_welcome(string);
    private:
        //------------------------
        //Requirement #16: String
        //------------------------ 
        string welcome;
};

string greeting :: get_welcome(){
    return welcome;
}
void greeting :: set_welcome(string x){
    welcome = x;
}

const int rows = 9;
const int columns = 9;
const float ships = 5;

//------------------------------
//Requirement #03: Type casting
//------------------------------
int maxCompShips = static_cast<int>(ships);

//----------------------------------------
//Requirement #18: Multi-Dimensional Array
//----------------------------------------
char hidden_board[rows][columns];
char display_board[rows][columns];

//------------------------------------
//Requirement #23: Pointer to an array
//------------------------------------
char (*pnt_hidden_board)[rows][columns] = &hidden_board;

//-----------------------------------------
//Requirement #12: Functional Decomposition
//I generally built everything in a 
//function to make the main look cleaner
//-----------------------------------------

/******************************************************************************
                            Game Setup Functions
*******************************************************************************/
void ClearBoard(); //initializes and empty gameboard
void UpdateBoard(); //updates the board with 'O' or 'X' for hits and misses
void GenerateShip(int angle); // generates the computer ships to be guessed. they are generated randomly and they will either all be verticl or horizontal
/******************************************************************************
                            Gameplay Functions
*******************************************************************************/
int NumOfShips(int fires_made); // counts the amount of ships and hits on ships
bool PlayerAttack(char x, char y); //checks for a ?(ship) on the hidden_board and puts an X(hit) if true
void endGame(int &bombs, int &fires_made); //checks if player is out of bombs or if all ships have been sunk
/******************************************************************************
                            Miscellaneous Functions
*******************************************************************************/  
int numCheck(int, int); //error checking for number input
void HiddenBoard(); // used to see the hidden_board for debugging
void RecursiveTitle(int); // prints stars 1 to 5
void RecursiveTitle(double); // prints stars 5 to 1


int main(int argc, char *argv[]){

    //-------------------------------------------------
    //Requirement #06: Bitwise operator
    //---------------------------------
    int bit_example = 1;
    //bit is equal to 1
    bit_example = bit_example << 1;
    //bit is now equal to 2
    bit_example = bit_example << 2;
    //bit is now equal to 8
    //-------------------------------------------------


    int bombs;
    //-------------------------------------
    //Requirement #20: Command Line Argument
    //This command line argument accepts a different amount of bombs rather than the set 20 limit
    //-------------------------------------
    if(argc == 1){
        bombs = 25;
    }
    else{
        bombs = atof(argv[1]);
        cout << "You have " << argv[1] << " bombs";
    }
        greeting introduce;
        //-------------------------------------
        //Requirement #25: Pointer to an object
        //-------------------------------------
        greeting *intro_pointer = &introduce;

        tools set_1;
        //------------------------------------
        //Requirement #24: Pointer to a struct
        //------------------------------------
        tools *set1_pointer;

        srand(time(0));
        int angle = rand() % 2; 
        int fires_made = 0;
        
        introduce.set_welcome("*******   WELCOME TO THE ULTIMATE BATTLESHIP GAME\n");
        //-------------------------
        //Requirement #16: C-String
        //-------------------------
        //-----------------------------
        //Requirement #19: Dynamic Array
        //-----------------------------
        char *hit= new char[5]; 
        hit[0] = 'H';
        hit[1] = 'I';
        hit[2] = 'T';
        hit[3] = '!';
        hit[4] = '\0';

            RecursiveTitle(7);
            //------------------------------
            //Requirement #01: Simple output
            //------------------------------
            cout << introduce.get_welcome();
            RecursiveTitle(6.0);
            cout << "Below is the playing board. You have " << bombs << " bombs to try and sink 5 opponent ships.\n";
            cout << "The orientation of the ships are randomized (verticle or horizontal)." << endl << "Enter attack coordinates in a grid fashion...\n" <<  "For example, if you want to hit the top right corner - enter \"1 9\"\n" << endl;
            ClearBoard();
            for (int k = 1; k <= ships; k++)
            {  
                GenerateShip(angle);
            }   
            UpdateBoard();
            //HiddenBoard();
            cout << endl ;
            
        while(1)
        {
            cout << "Number of fires made: " << NumOfShips(fires_made) << "/15" << endl;
            cout << "Number of bombs left: " << bombs  << endl;  
            //cout << "fires made: " << NumOfShips(fires_made) << endl;
            cout << endl << "Please enter attack coordinates: "; 
            //------------------------------
            //Requirement #02: Simple input
            //------------------------------
            cin >> set_1.pos1 >> set_1.pos2;
            numCheck(set_1.pos1, set_1.pos2);
            bombs--;
            if(PlayerAttack(set_1.pos1, set_1.pos2))
            {
                cout << endl << "                    " << "(" << set_1.pos1 << ", " << set_1.pos2 << ")" << endl << "                     " << hit << endl << endl;
            } 
                else
                {
                    cout << endl << "                     " << "(" << set_1.pos1 << ", " << set_1.pos2 << ")" << endl << "       Sorry, no ship at that coordinate!" << endl << endl;
                }   
            UpdateBoard();   
            endGame(bombs, fires_made);   
        }//end while 
    delete[] hit;    
    return 0;
}// END MAIN

/*****************************************************************************************************************************
                                                    Game Setup Functions
******************************************************************************************************************************/
//--------------------------
//Requirement #11: Function
//--------------------------
void ClearBoard(){
    //----------------------
    //Requirement #07: Loop
    //----------------------
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            hidden_board[i][j] = '-';
            display_board[i][j] = '-';
        }
    }
}    

void UpdateBoard(){

cout << "            1  2  3  4  5  6  7  8  9 \n";
cout << "         ----------------------------\n";

    for(int i=0; i<9; i++)
    {

        cout << "       " <<  i +1 << " | ";
        for(int j=0; j<9; j++){
            cout << ' ' << display_board[i][j] << ' ';
        }
        cout << endl;
    }
}

void GenerateShip(int angle){  
    
int iStart;
int jStart;

Begin:  
    do{  
    //-----------------------------
    //Requirement #08: Random Number
    //-----------------------------
        iStart = rand() % 9;
        jStart = rand() % 9; 
    }while(hidden_board[iStart][jStart] == '?');
         
        //horizontal ships    
        if (angle == 0){
            //make sure ship wont go off board
            while (jStart + 3 >= columns){
                jStart = rand()%columns;
            }
                //check for other ships in the way        
                for (int j = jStart; j < jStart + 5; j++){
                    if (hidden_board[iStart][j] == '?')
                    goto Begin;    
                }
                //if no problems, generate the ship
                for (int j = jStart; j <jStart + 3; j++){
                    hidden_board[iStart][j] = '?';
                }
        }   
        //vertical ships
        if (angle == 1 ){
            while (iStart + 3 >= rows){
                iStart = rand()%rows;
            }
                for (int i = iStart; i < iStart + 5; i++){
                    if (hidden_board[i][jStart] == '?')
                    goto Begin;    
                }
                for (int i = iStart; i< iStart + 3; i++){
                    hidden_board[i][jStart] = '?';
                }
        } 
}   

/*****************************************************************************************************************************
                                                    Gameplay Functions
******************************************************************************************************************************/

int NumOfShips(int fires_made){
    
    //------------------------------
    //Requirement #13: Scope
    //the variable i is used many time in this program but because of 
    //the scope of these functions they dont interfere with each other.
    //------------------------------
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {   //----------------------------------
            //Requirement #05: Logical operators
            //----------------------------------
            if(hidden_board[i][j] == '?')
            {
                fires_made++;
            }
            if(display_board[i][j] == 'X')
            {
                fires_made--;
            } 
        }  
    }
    return (15 - fires_made); 
}//end function

bool PlayerAttack(char x, char y){
    //------------------------------
    //Requirement #04: Condindional
    //------------------------------
    if (hidden_board[x-1][y-1] == '?' ){
        display_board[x-1][y-1] = 'X';
    
            for (int i = 0; i < rows; i++){
                //checks if a verticel ship has been hit in 3 places
                if((display_board[i-1][y-1] == 'X' && display_board[i][y-1] && display_board[i+1][y-1] == 'X') || (display_board[i-1][y-1] == 'X' && display_board[i-2][y-1] && display_board[i-3][y-1] == 'X')){
                        cout << endl << "YOU HAVE SUNK A VERTICLE SHIP!" << endl;
                        break;
                    }
            }        
            for (int j = 0; j < columns; j++){   
                //checks if a horizontal ship has been hit in 3 places
                if((display_board[x-1][j-1] == 'X' && display_board[x-1][j] == 'X' && display_board[x-1][j+1] == 'X') || (display_board[x-1][j-1] == 'X' && display_board[x-1][j-2] == 'X' && display_board[x-1][j-3] == 'X')){
                    cout << endl << "YOU HAVE SUNK A HORIZONTAL SHIP!" << endl;
                    break;
                }  
            }      
    return true;
    }
    else {
        display_board[x-1][y-1] = 'O';
        return false;
    }
}

//-----------------------------------
//Requirement #14: Passing Mechanisms
//-----------------------------------
void endGame(int &bombs, int &fires_made){

char stop;    

    while (bombs == 0 || NumOfShips(fires_made) == 15){
        if(bombs == 0){
            cout << "You are out of bombs, do you want to surrender...(y/n)?" << endl;
            cin >> stop;
            if(stop == 'y' || stop == 'Y'){
            exit(0);
            }
                else {
                    cout << endl << "I'm only giving you 5 more bombs, drop them wisely. "<< endl << endl;
                    bombs = 5;
                }
        }        
                 
        if (NumOfShips(fires_made) == 15){
            cout << "Great job! You have sunk all the enemy ships!" << endl;
            exit(0);
        }
    }//end while
}//end function    

/*****************************************************************************************************************************
                                                    Miscellaneous Functions
******************************************************************************************************************************/    

//------------------------------
//Requirement #10: Debugging - numCheck -
//
// numCheck checks to make sure user input is a number.
// This helps to reduce the program from crashing when
// anything other than a number is entered
//------------------------------
int numCheck(int x, int y){

    while(!cin){   //enter loop if cin is not an int
       cin.clear();   //clear the cin error state
       cin.ignore(100000000, '\n');   //discard characters in stream
       cout << "Please enter a single digit number: " << endl;
       cin >> x >> y;
    }
  

    if(x == 0 || y == 0){
        cin.clear();   //clear the cin error state
        cin.ignore(10000000, '\n');   //discard characters in stream
        cout << "Please enter a number between 1 and 9 only:";
        cin >> x >> y;
    }  
    return x && y;  
}
//------------------------------
//Requirement #10: Debugging - HiddenBoard -
//
// I used this function throughout the whole process 
// to test how the hidden_board array was working. It
// was very useful. Ive left the commented out function
// in the main so that it can be seen how it was used.
//------------------------------
void HiddenBoard(){

cout << "            1  2  3  4  5  6  7  8  9 \n";
cout << "         ----------------------------\n";

    for(int i=0; i<9; i++)
    {

        cout << "       " <<  i +1<< " | ";
        for(int j=0; j<9; j++){
            cout << ' ' << hidden_board[i][j] << ' ';
        }
        cout << endl;
    }
}
//--------------------------
//Requirement #17: Recursion
//--------------------------
void RecursiveTitle(int x){
    if (x <= 1) {
        return;
    }
    else{
        RecursiveTitle(x-1);
        while(x >1){
            cout << "*";
            x--;
        }
        cout << endl;
    } 
}
//-------------------------------------
//Requirement #15: Function overloading with "RecursiveTitle"
//-------------------------------------
void RecursiveTitle(double y){
    if (y <= 0){
        return;
    }
    else{
       for (int i = 0; i < y; i++ ){
        cout << "*";
       }
    cout << endl;
    RecursiveTitle(y -1); 
    } 
}




