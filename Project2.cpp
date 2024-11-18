/*
Project 2 CSCE 1030 Computer Science I
A game that involves guessing numbers between randomly generated boundaries within a hidden matrix using functions
and with gaining and losing points while playing.

Authors: 
Kayden Plemons, krp0190, kaydenplemons@my.unt.edu
Hansley Omonzane, heo0024, hansleyomonzane@my.unt.edu
Micheal Egboh, mce0100, michealegboh@my.unt.edu
Sunita Abbasi, sqa0009, sunnitaabbasi@my.unt.edu
*/
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cctype>
using namespace std;

//gobal enum vaules for menu choices and switch case. 
enum menu{displayLeft=1, displayRight=2, Guess=3, Change=4, Exit=5}; 

// function to ask the name of the user
string getName() 
{
    while (true) 
	{
        string playername;
        cout << "Enter your name: ";
        getline(cin, playername);

        bool valid = true;
        for (char c : playername)
		{
            if (!isalpha(c) && c != ' ') 
			{
                valid = false;
                break;
            }
        }

        if (valid)
		{
            for (int i = 0; i < playername.length(); i++) 
			{
                if (i == 0 || playername[i - 1] == ' ') 
				{
                    playername[i] = toupper(playername[i]);
                } 
				else 
				{
                    playername[i] = tolower(playername[i]);
                }
            }
            return playername;
        } 
		else 
		{
            cout << "Invalid characters detected in the name, Please try again." << endl;
        }
    }
}

// Function to generate The matrix
void genShowMatrix(int visible[][5]) 
{
    for (int i = 0; i < 5; i++) 
	{
        for (int j = 0; j < 5; j++) 
		{
            visible[i][j] = -1;
        }
    }
}

// Function to generate The hidden matrix
void genHideMatrix(int hidden[][5], int lowerBound, int upperBound) 
{
    srand(time(NULL));
    for (int i = 0; i < 5; i++) 
	{
        for (int j = 0; j < 5; j++) 
		{
            hidden[i][j] = rand() % (upperBound - lowerBound + 1) + lowerBound;  
        }
    }
}

// Function to show The matrix
void showMatrix(int arr[][5]) 
{
    for (int i = 0; i < 5; i++) 
	{
        for (int j = 0; j < 5; j++) 
		{
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
}

//Function To display the left number and game message. 
void setdisplayLeft(int lowerBound, int& intNum1, int& run) 
{
	if (run == 1 || run==2) 
	{
		run=2;
		intNum1 = lowerBound;
		cout << "A correct guess will earn 1 point, and an incorrect guess will lose 10 points." << endl;
		cout<<endl;
	}
	else 
	{
		cout << "You have already displayed the right boundary, you cannot display both." << endl;
		cout<<endl;
	}	
}

//Function To display the right number
void setdisplayRight(int upperBound, int& intNum2, int& run) 
{
    if (run ==1 || run==3) 
	{
		run=3;
		intNum2= upperBound;
		cout << "A correct guess will earn 1 point, and an incorrect guess will lose 10 points." << endl;
		cout<<endl;
	}
	else 
	{
		cout << "You have already displayed the left boundary, you cannot display both." << endl;
		cout<<endl;
	}
	
}

//Functions to elimante Guessed number in the visible matrix and hidden matrix. 
void eliminate(int row, int col, int visible[][5], int hidden[][5])  
{
    for (int i = 0; i < 5; i++) 
	{
        visible[row][i] = 0;
        visible[i][col] = 0;
        hidden[row][i] = 0;
        hidden[i][col] = 0;
    }
}

//function to check if user has won the game/matrix is all zeros
bool allZeros(int visible[][5]) 
{
    for (int i = 0; i < 5; i++)
	{
        for (int j = 0; j < 5; j++) 
		{
            if (visible[i][j] != 0) 
			{
                return false;
            }
        }
    }
    return true;
}

//Function for the player to guess numbers in hidden matrix.
void guess(int &playerpoints, int visible[][5], int hidden[][5], int intNum1, int intNum2, int run) 
{
    int guess;
    int row, col;

    cout << "Enter your guess: ";
    cin >> guess;
	cout<<endl;

    bool found = false;

    for (int i = 0; i < 5; i++) 
	{
        for (int j = 0; j < 5; j++) 
		{
            if (hidden[i][j] == guess) 
			{
                row = i;
                col = j;
                found = true;
                break;
            }
        }
        if (found) 
		{
            break;
        }
    }

    if (found && run==1) 
		{
			eliminate(row, col, visible, hidden);
			cout << "Correct guess! You earned 5 points." << endl;
			playerpoints += 5;
			showMatrix(visible);
			cout << "Your remaining points: " << playerpoints << endl;
			
		}
	else if (!found && run==1)
		{
			cout << "Incorrect guess! You lost 5 points."<< endl;
			playerpoints -= 5;
			showMatrix(visible);
			cout << "Your remaining points: " << playerpoints << endl;
			
		}
	else if (found && run!=1)
		{
			eliminate(row, col, visible, hidden);
			cout << "Correct guess! You earned 1 point." << endl;
			playerpoints += 1;
			showMatrix(visible);
			cout << "Your remaining points: " << playerpoints << endl;
			
		}
    else 
		{
			playerpoints -= 10;
			cout << "Incorrect guess! You lost 10 points." << endl;
			showMatrix(visible);
			cout << "Your remaining points: " << playerpoints << endl;
		}
    cout<<endl;
}


// Function to initialize the game
void initialize(int playerpoints, int visible[][5], int hidden[][5], int& lowerBound, int& upperBound, int& run) 
{
    srand(time(NULL));
    lowerBound = rand() % 100 + 100;
    upperBound = rand() % 100 + 200;
    genShowMatrix(visible);
    genHideMatrix(hidden, lowerBound, upperBound);
    run=1;
}

int main() 
{
    cout<<endl;
	cout<<"\t"<<"Sunita Abbasi, sunnitaabbasi@my.unt.edu"<<endl;
	cout<<endl;

	//setting the game varibles
	int playerpoints=100;
    int visible[5][5];
    int hidden[5][5];
    int lowerBound;
    int upperBound;
    int run;

    string playername = getName();
    cout<<endl;
	cout << "Welcome, " << playername << "!" << endl;
	initialize(playerpoints, visible, hidden, lowerBound, upperBound, run);


    int choice;
    int intNum1 = -1;
	int intNum2 = -1;
  
	//while loop to check if player points are below zero or choice is exit. 
    while (choice != Exit && playerpoints >= 0)  
	{
     
        cout << intNum1 << "\t \t" << intNum2 << endl;
		cout << "Menu Options:" << endl;
        cout << "1. Display Left Bound" << endl;
        cout << "2. Display Right Bound" << endl;
        cout << "3. Guess a number in between" << endl;
        cout << "4. Change numbers" << endl;
        cout << "5. Exit" << endl;

        cout << "Enter your choice: ";
		char input[15];
		cin>>input; 
		choice=atoi(input);

        switch (choice) {
            case displayLeft:
				setdisplayLeft(lowerBound, intNum1, run);
                break;

            case displayRight:
				setdisplayRight(upperBound, intNum2, run);
                break;

            case Guess:
                showMatrix(visible);
				guess(playerpoints, visible, hidden, intNum1, intNum2, run);
				if (playerpoints >= 0) 
				{
					if (allZeros(visible)) 
					{
						cout << "Congratulations! You have won the game." << endl;
						char playAgain;
						cout << "Do you want to play another game? (Y/N): ";
						cin >> playAgain;
						if (playAgain == 'Y' || playAgain == 'y') 
							{
						initialize(playerpoints, visible, hidden, lowerBound, upperBound, run);
							} 
						else 
							{
						cout << "Goodbye, " << playername << "!" << endl;
						cout << "Final points: " << playerpoints << endl;
						return 0;
							}
					}
				}			 
				else
				{
					cout << "Game over! Your points have fallen below zero." << endl;
					cout << "Goodbye, " << playername << "!" << endl;
					cout << "Final points: " << playerpoints << endl;
				}
                break;

            case Change:
                playerpoints -= 1;
                intNum1=-1;
                intNum2=-1;
                initialize(playerpoints, visible, hidden, lowerBound, upperBound, run);
				cout<<endl;
                cout << "Your remaining points: " << playerpoints << endl;
                break;

            case Exit:
                cout << "Goodbye, " << playername << "!" << endl;
                cout << "Final points: " << playerpoints << endl;
                break;

            default:
                cout << "Invalid choice. Please choose a valid option from the menu." << endl;
                break;   
        }
	} 

    return 0;
}
