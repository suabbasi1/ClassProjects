#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Vectors.h"
#include "residential.h"
#include "industrial.h"
#include "commercial.h"
#include "Tree.h"
using namespace std;

int main()
{
    //this file is openng config1 and region1 and printing it to the screen
    string inputConfig;
    cout<<"Enter config file name: ";
    cin>> inputConfig;
    ConfigFileFunction(inputConfig);
    cout<<endl;

    //Here i am passing the functions in my main
    InitilizeNewRegion();
    Residential residential;
    residential.InitilizeResidential();
    Industrial industrial;
    industrial.InitilizeIndustrial();
    Commercial commercial;
    commercial.InitilizeCommercial();
    Tree tree;
    bool checkChange = true;
    int countChange = 0;
    //for loop that will print the correct regions.
    for(int i =0; i <= time_Limit && countChange < 2; i++){
        vector<vector<int> > PreviousRegion = NewRegion;
        if(i==0){
            cout<<"Original Region Layout: "<<endl;
            PrintR();
            cout<<endl;
        }
        //checks if i is a multiple of the refresh rate. if is important so that the code itirates ever ith time.
        else if(i % refresh_Rate == 0){
            cout<<"Time Step #"<<i<<":"<<endl;
            residential.UpdateRes(); //updates after the zones grow 
            commercial.UpdateCom();
            industrial.UpdateInd();
            SpreadPollution();
            checkChange = !Checker(NewRegion, PreviousRegion); //checks for change in the region
            if(!checkChange){
                countChange++;
            }
            else{
                countChange = 0;
            }
            PrintR();
            cout << endl;
        }
    }
    CalcZPopulations(); //calculations and prints the final zone populations.
    //prints before trees grow
    PrintPollution();
    cout << endl;
    tree.SpreadTree();
    tree.PrintTree();
    cout << "Updated Pollution Region:" << endl;
    PrintPollution(); //prints after the trees grow
    tree.NewIndustrialPopulation(); //prints the new industrial population after trees are grown
   
    return 0;

    
}