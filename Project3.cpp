/*
Project 3 CSCE 1030 Computer Science I

Authors: 
Kayden Plemons, krp0190, kaydenplemons@my.unt.edu
Hansley Omonzane, heo0024, hansleyomonzane@my.unt.edu
Micheal Egboh, mce0100, michealegboh@my.unt.edu
Sunita Abbasi, sunitaabbasi@my.unt.edu
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <iomanip>
#include <fstream>
using namespace std;

const int NUMTEST=5; //constant global varible for thenumber of tests
enum menu{Add=1, Remove=2, Display=3, Search=4, Results=5, Exit=6}; //gobal enum vaules for menu choices and switch case. 

struct Student
{
	string name;
	int id;
	int tests;
	int* score;
	double average;
};

void add_Student() //Function to add a student to the data
{
    Student newStudent; // Prompt user for information
	cout << "Enter student name (first,last): ";
    cin.ignore();
    getline(cin, newStudent.name);

	cout << "Enter your student ID number: ";
	cin >> newStudent.id;

	cout << "Enter the number of test you've taken: ";
	cin >> newStudent.tests;

	newStudent.score = new int[newStudent.tests];  // Allocate memory for test scores

	
	for(int i=0; i< newStudent.tests; ++i)
		{
			cout << "Enter test score #" << (i+1) << ":";
			cin >> newStudent.score[i];
		}
	
		
	ofstream fout("student.dat", ios::app); // Open student.dat and write the data of the student
	if (!fout.is_open())
    {
        cout << "Error opening file for reading." << endl;
		return;
    }
	
	fout<<endl; // Write the student data to the file
	fout << newStudent.name << "," << newStudent.id << "," << newStudent.tests << ",";
        
	for (int i = 0; i < newStudent.tests; ++i) 
	{
            fout << newStudent.score[i]<<",";
    }
      
    cout << "Student record added successfully." << endl;
	
	fout.close();
   
    delete [] newStudent.score; 
}

int getNumber() //Function to get the number of students in file
{
    ifstream fin("student.dat");
    if (!fin.is_open())
    {
        cout << "Error opening file for reading." << endl;
        return 0;
    }

    int count=0;
	string record;
	while(!fin.eof())
	{
		getline(fin, record);
		++count;
	}
	fin.close();
	return count;
}

void remove_student(int studentID) //Function to remove a student using there ID
{
    int numStudents = getNumber();

    if (numStudents == 0)
    {
        cout << "No student records found." << endl;
        return;
    }

    Student *students = new Student[numStudents];
	
    ifstream fin("student.dat");
    if (!fin.is_open())
    {
        cout << "Error opening file for reading." << endl;
        delete[] students;
        return;
    }

    bool foundMatch = false;

	string first[20];
	string last[20];
	
    for (int i = 0; i < numStudents; ++i) // Read data from the file into the dynamic array
    {
        getline(fin, first[i], ',');
		getline(fin, last[i], ',');
		students[i].name= first[i]+ " " + last[i];
        fin >> students[i].id;
        fin.ignore();
        fin >> students[i].tests; 
        fin.ignore();
		
		 
		
		students[i].score = new int[students[i].tests];
        for (int j = 0; j < students[i].tests; ++j)
        {
            fin >> students[i].score[j];
            if (j < students[i].tests - 1)
            {
                fin.ignore();
            }
        }

        fin.ignore();
		
        if (students[i].id == studentID) // Check if the student ID being read matches the student ID to be removed
        {
            foundMatch = true;
        }
    
    }

    fin.close();

   
    if (foundMatch) // If a match was found while reading
    {
      
        ofstream fout("student.dat", ofstream::trunc); // Open student.dat file for writing
        if (!fout.is_open())
        {
            cout << "Error opening file for writing." << endl;
            delete[] students;
            return;
        }

        
        for (int i = 0; i < numStudents; ++i) // Write the contents of the dynamic array to the file, excluding the student to be removed
        {
            if (students[i].id != studentID)
            {
                fout << first[i] << "," << last[i] << "," << students[i].id << "," << students[i].tests << ",";
                for (int j = 0; j <students[i].tests; ++j)
                {
                    fout << students[i].score[j] <<",";
                   
				}
            }
        }

        fout.close();

        cout << "Student record removed successfully." << endl;
    }
    else
    {
        cout << "Student with ID " << studentID << " not found." << endl;
    }

   
    for (int i = 0; i < numStudents; ++i) // Deallocate memory
    {
        delete[] students[i].score;
    }
    delete[] students;
}

void display() //Function to display student data
{
	cout<<endl;
    ifstream fin("student.dat"); // Open the data file for reading
    if (!fin.is_open())
    {
        cout << "Error opening file for reading." << endl;
        return;
    }

    int numStudents = getNumber();

    if (numStudents == 0) // Check if there are no students in the file
    {
        cout << "No student records found." << endl;
        fin.close();
        return;
    }

	string first;
	string last;
	
    Student *students = new Student[numStudents]; // Create a dynamic array of Student structures

    for (int i = 0; i < numStudents; ++i) // Read data from the file into the dynamic array
    {
        getline(fin, first, ',');
		getline(fin, last, ',');
		students[i].name= first+ " " + last;
        fin >> students[i].id;
        fin.ignore();
        fin >> students[i].tests; 
        fin.ignore();
		
		 
		
		students[i].score = new int[students[i].tests];
        for (int j = 0; j < students[i].tests; ++j)
        {
            fin >> students[i].score[j];
            if (j < students[i].tests - 1)
            {
                fin.ignore();
            }
        }

        fin.ignore();
    }

    fin.close();

    cout << "-------------------------------------------------------------------" << endl;
	cout << left << setw(30) << "NAME"<< setw(15) << "STUDENT ID" << setw(5) << "TEST SCORES" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	
	
    for (int i = 0; i < numStudents; ++i) // Display student records
    {
        cout << setw(30) << students[i].name << setw(15) << students[i].id;

        for (int j = 0; j < students[i].tests; ++j)
        {
            cout << setw(5) << students[i].score[j];
        }

    }
	
	
	cout<<endl; 
	cout << "-------------------------------------------------------------------" << endl;

    for (int i = 0; i < numStudents; ++i)
    {
        delete [] students[i].score;
    }
    delete [] students;
}


void search(int searchID) //Function to search for student using ID then display results
{
    ifstream fin("student.dat");
    if (!fin.is_open())
    {
        cout << "Error opening file for reading." << endl;
        return;
    }

    bool found = false;
    Student* student = new Student;  //Use a pointer

    string first;
    string last;
    string line;
    int count = getNumber();

for (int i = 0; i < count; ++i)
{	
	while (getline(fin, line) && !found)  //Helps move through each line of the file
	{
    
        getline(fin, first, ',');
        getline(fin, last, ',');
        student->name = first + " " + last;
        fin >> student->id;
        fin.ignore();
        fin >> student->tests;
        fin.ignore();

        student->score = new int[student->tests];
        for (int j = 0; j < student->tests; ++j)
        {
            fin >> student->score[j];
            if (j < student->tests - 1)
            {
                fin.ignore();
            }
        }

        if (student->id == searchID)  //Display the matched student
        {
            found = true;
            cout << endl;
            cout << "-------------------------------------------------------------------" << endl;
            cout << setw(30) << "NAME" << setw(15) << "STUDENT ID" << setw(5) << "TEST SCORES" << endl;
            cout << "-------------------------------------------------------------------" << endl;
            cout << setw(30) << student->name << setw(15) << student->id;

            for (int j = 0; j < student->tests; ++j)
            {
                cout << setw(5) << student->score[j];
            }
            cout << endl;
            cout << "-------------------------------------------------------------------" << endl;
        }
    
	}
}

    fin.close();

    if (!found) 
    {
        cout << "Student with ID " << searchID << " not found." << endl;
    }

    delete[] student->score;  //Deallocate memory for the scores
    delete student;  //Deallocate memory for the single instance
}



double findMinimum (int* scores, int size) //Function to find the minimum test score for each student
{
	if(size < 5) 
	{
        
        return 0; // If a student has taken less than 5 tests, the minimum score is 0
    } 
	else 
	{
        
        int minimum = scores[0]; // If a student has taken all 5 tests, find the minimum of the 5 scores
        for (int i = 1; i < size; ++i) 
		{
            if (scores[i] < minimum) 
			{
                minimum = scores[i];
            }
        }
        return minimum;
    }
}

void exportResults() //Function to export tests averages to another file
{
    ofstream fout("averages.dat");
    if (!fout.is_open()) 
	{
        cout << "Error opening file for writing." << endl;
        return;
    }

    
    ifstream fin("student.dat"); // Open student.dat file for reading
    if (!fin.is_open()) 
	{
        cout << "Error opening file for reading." << endl;
        fout.close();
        return;
    }

   
    int numStudents = getNumber();  // Get the number of students from the file using the getNumber function

    if (numStudents == 0)
    {
        cout << "No student records found." << endl;
        fin.close();
        return;
    }

	string first;
	string last;
	
    Student *students = new Student[numStudents];

    for (int i = 0; i < numStudents; ++i)
    {
        getline(fin, first, ',');
		getline(fin, last, ',');
		students[i].name= first+ " " + last;
        fin >> students[i].id;
        fin.ignore();
        fin >> students[i].tests; 
        fin.ignore();
		
		 
		
		students[i].score = new int[students[i].tests];
        for (int j = 0; j < students[i].tests; ++j)
        {
            fin >> students[i].score[j];
            if (j < students[i].tests - 1)
            {
                fin.ignore();
            }
        }

        fin.ignore();
    }

    fin.close();

    
    for (int i = 0; i <= numStudents-1; ++i) // Process each student to compute the average and write to averages.dat
	{
        int minScore = findMinimum(students[i].score, students[i].tests);
        int sum = 0;

       
        for (int j = 0; j < students[i].tests; ++j)  // Sum the test scores, excluding the minimum score
		{
            sum += students[i].score[j];
        }
        sum -= minScore;

		double average;
        if (minScore==0)
		{
        average = static_cast<double>(sum) / (students[i].tests); // Compute the average
		}
		else 
		{
		average = static_cast<double>(sum) / (students[i].tests-1);
		}
        
        fout << students[i].id << ',' << fixed << setprecision(1) << average << endl; // Write student ID and average to averages.dat

      
        delete[] students[i].score;  // Deallocate memory
    }
	
	cout<<"Results exported to file."<<endl;
    
    fout.close(); // Close the output file
	
    delete[] students;  // Deallocate memory for the dynamic array
}

int main ()
{
	cout<<endl;
	cout<<"\t"<<"\t"<<"Computer Science and Engineering"<<endl;
	cout<<"\t"<<"\t"<<"CSCE 1030 - Computer Science I"<<endl;
	cout<<"\t"<<"Sunita Abbasi, sunnitaabbasi@my.unt.edu"<<endl;
	cout<<endl;
	
	
	int choice = 0;
    while (choice != Exit) //while loop with switc case to display menu options until exit 
    {
		cout<<endl;
        cout << "Menu Options:" << endl;
        cout << "1. Add a new student." << endl;
        cout << "2. Remove student record." << endl;
        cout << "3. Display all records." << endl;
        cout << "4. Search for student." << endl;
        cout << "5. Export to file." << endl;
        cout << "6. Exit" << endl;

        cout << "Enter your choice: ";
        char input[15];
        cin >> input;
        choice = atoi(input);

        switch (choice)
        {
        case Add:
            add_Student();
            break;

        case Remove:
            cout << "Enter Student ID: ";
            int removeID;
            cin >> removeID;
            remove_student(removeID);
            break;

        case Display:
            display();
            break;

        case Search:
            cout << "Enter Student ID to search: ";
            int searchID;
            cin >> searchID;
            search(searchID);
            break;

        case Results:
            exportResults();
            break;

        case Exit:
            cout << "Goodbye!" << endl;
			cout<<endl;
            break;

        default:
            cout << "Invalid choice. Please choose a valid option from the menu." << endl;
            break;
        }
    }
	
	return 0;
}
