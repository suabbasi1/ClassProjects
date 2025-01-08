#ifndef VECTORS_H
#define VECTORS_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;

extern vector<vector<char> >RegionVect; //vector to be accessed by all other files on the original region
extern vector<vector<int> >NewRegion; //vector to be accessed by all other files of the new region as it's updating
extern vector<vector<int> > PollutionRegion; //vector for the state of pollution as pollution spreads.

extern int time_Limit;
extern int refresh_Rate;
extern int goods;
extern int workers;
extern int pollution;
extern int IndPopulationCount; //making this a global variable so that Tree.cpp can update it
void ConfigFileFunction(const string& inputConfig);
void OpenRegionLayout(const string& RegionLayout); //one of the functionalities
void InitilizeNewRegion();
void PrintR();
bool Checker(const vector<vector<int> >&NewRegion, const vector<vector<int> >&PreviousRegion); //this is meant to check for changed in the region
void SpreadPollution(); //one of the functionalities
void PrintPollution();
void CalcZPopulations();


#endif
