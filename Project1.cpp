/*
Project 1 CSCE 1030 Computer Science I
A game that involves guessing a number between two randomly generated numbers, with gaining and losing points while playing.

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
#include <cmath>
#include <cctype>
using namespace std;



int main()
{
	cout<<endl;
	cout<<"\t"<<"\t"<<"Computer Science and Engineering"<<endl;
	cout<<"\t"<<"\t"<<"CSCE 1030 - Computer Science I"<<endl;
	cout<<"\t"<<"Sunita Abbasi, SunitaAbbasi@my.unt.edu@my.unt.edu"<<endl;
	cout<<endl;
	
	
	int playerpoints=100; //Declare and initialize the player's points
	enum menu{displayLeft=1, displayRight=2, Guess=3, Change=4, Exit=5}; //Declare an enumeration constant for the menu options
	string playername; //Declare variables for player's name and character validation
	char ch;
	bool test;
	
	//Ask for and validate player's name
	do{
		cout<< "Enter your name: ";
		getline(cin,playername); //Gets the entire string from prompt and inputs it into playername variable 
			for (int i=0;i<playername.length();++i)
		{
			ch=playername.at(i); 
			if (isalpha(ch) || isspace(ch)) // Checks if characters are alphabents or whitespace
			{
			test = false;
			}	
			else 
			{
				test = true;
				cout << "This name is invalid, please enter a new name below!"<< endl; //Display an error message for invalid characters 
				break;
			}
		}
	} while (test);
	cout<<endl;
	
	char letter;  //Converts other initals in string to uppercase
	for (int j=0;j<playername.length();++j)
	{
		letter=playername.at(j);
		if (isspace(letter))
		{
		letter=playername.at(j+1);
		letter=toupper(letter);
		playername.at(j+1)=letter;
		}
	}

	char letter2;  //Convert the player's name to inital uppercase 
	letter2=playername.at(0);
	letter2=toupper(letter2);
	playername.at(0)=letter2;
	
	
	cout << "Welcome " << playername <<"!"<<endl;
	
	
	bool test2;
	srand(time(NULL));
	
	int rand1; 
	int rand2;
	while (true) //Generate two random number with the first being less than the second
	{
		 rand1 = rand()%101 + 100;
		 rand2 = rand()%101 + 100;
		if (rand1 < rand2)
		{
			test2 = true;
			break;
		}
		else
		{
			test2 = false;
		}
	}
	//Generate two random number with the first being less than the second
	int intNum1 = -1;
	int intNum2 = -1;
	
	cout << intNum1 << "\t \t" << intNum2 << endl; //Display starting  values for integers
	
	
	
	
	
	
	int run=1; //checks if numbers have been displayed before
	
     //Main loop for the game 
	while (choice != Exit && playerpoints >= 0)
	{
			// Display Menu Options 
			cout << "1. Display Left Number" << endl;
			cout << "2. Display Right Number" << endl;
			cout << "3. Guess a number in between" << endl;
			cout << "4. Change numbers" << endl;
			cout << "5. Exit" << endl;
			cout << "What do you want to do? " << endl;
			char input[15];
			cin>>input; 
			choice=atoi(input);
			cout<<endl;
		
		switch(choice)
		{
			case displayLeft:
				if (run == 1) //Display left number if it hasn't been display yet
				{
					intNum1 = rand1;
					run=2;
					cout << "A correct guess will only earn 1 point and an incorrect guess will lose 10 points in the game." << endl; //Display game rule
					cout << intNum1 << "\t \t" << intNum2 << endl;
				}
				else 
				{
					cout << "You have already displayed the right boundary, you cannot display both." << endl;
					cout << intNum1 << "\t \t" << intNum2 << endl;
				}
			break;
			
			case displayRight:
				if (run ==1) //Display right number if it hasn't been displayed already
				{
					intNum2 = rand2;
					run=3;
					cout << "A correct guess will only earn 1 point and an incorrect guess will lose 10 points in the game." << endl; //Display game rule
					cout << intNum1 << "\t \t" << intNum2 << endl;
				}
				else 
				{
					cout << "You have already displayed the left boundary, you cannot display both." << endl;
					cout << intNum1 << "\t \t" << intNum2 << endl;
				}
			break;
			
			case Guess:
			int guess;
			cout << "Enter your Guess:";
			cin >> guess;
			cout << endl;
			if (run == 2 || run == 3)
			{
				if (guess > rand1 && guess < rand2) //Checks if guess is within the bounds and alter points accordingly 
				{
					cout << "You guessed correctly!"<<endl;
					playerpoints = playerpoints + 1;
					cout<< "Your remaining points=" << playerpoints << endl;
				}
				else
				{
					cout << "You Guessed incorrectly" << endl;
					playerpoints = playerpoints - 10;
					cout<< "Your remaining points=" << playerpoints << endl;
				}
				
			}
			else
			{
				if (guess > rand1 && guess < rand2)
				{
					cout << "You guessed correctly!"<< endl;
					playerpoints = playerpoints + 5;
					cout << "Your remaining points=" << playerpoints << endl;
				}
				else
				{
					cout << "You Guessed incorrectly" << endl;
					playerpoints = playerpoints - 5;
					cout <<"Your remaining points=" << playerpoints << endl;
				}
			}
			cout << intNum1 << "\t \t" << intNum2 << endl;
			break;
			
			case Change:
			playerpoints = playerpoints - 1; //Remove a point for changing the random numbers 
			if (choice ==4 )
			{				
				while (true)
				{
					rand1 = rand()%101 + 100;
					rand2 = rand()%101 + 100;
						if (rand1 < rand2)
					{
						test2 = true;
						break;
					}
					else
						{
							test2 = false;
						}
				}
	
			intNum1 = -1;
			intNum2 = -1;
			run=1;
			}
			cout << "Your remaining points=" << playerpoints << endl;
			cout << "Generating new boundaries." << endl;
			cout << intNum1 << "\t \t" << intNum2 << endl;
			break;
			
			case Exit:
			cout << "Thanks for playing " << playername << "!" << endl; //Display the final message and points 
			cout << "Final points=" << playerpoints << endl;
			break;
			
			default:
			cout << "Please select a valid input from menu." << endl; //Display an error message for invalid output
			break;
		
		}
		
	} 
	
	cout << endl;
	
	return 0;
}