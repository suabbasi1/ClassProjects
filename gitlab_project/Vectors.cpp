#include "Vectors.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

vector<vector<char> >RegionVect;
vector<vector<int> >NewRegion;
vector<vector<int> >PollutionRegion;
int time_Limit = 0;
int refresh_Rate = 0;
int goods = 0;
int workers = 0;
int pollution = 0;
int IndPopulationCount = 0;

ifstream in_s;
//function to open config file if it exsists
void ConfigFileFunction(const string &inputConfig)
{
    in_s.open(inputConfig);
    if(in_s.fail())
        {
            	cout << "Unable to open file " << inputConfig << endl;
		        exit(EXIT_FAILURE);
        }
    string tempLine;
    string RegionLayout;
    while(!in_s.eof())
    {
        getline(in_s, tempLine);
            if(tempLine.find("Region Layout:") != string :: npos) {
                RegionLayout = tempLine.substr(tempLine.find(":")+1); //prints region layout
            }
            else if(tempLine.find("Time Limit:") != string :: npos) {
                time_Limit = stoi(tempLine.substr(tempLine.find(":")+1)); //prints time limit
            }
            else if(tempLine.find("Refresh Rate:") != string :: npos){
                refresh_Rate = stoi(tempLine.substr(tempLine.find(":")+1)); //prints refresh rate
            }
        }
    in_s.close();

    cout<<"Region Layout :" << RegionLayout <<endl;
    cout<<"Time Limit :" << time_Limit<<endl;
    cout<<"Refresh Rate :"<< refresh_Rate<<endl;
    OpenRegionLayout(RegionLayout);
}
//creates a new region based on the already existing one
void InitilizeNewRegion(){
    if(!RegionVect.empty()){
        NewRegion.resize(RegionVect.size(), vector<int> (RegionVect[0].size(),0));
    }

}
//opens the layout provided 
void OpenRegionLayout(const string& RegionLayout)
{
    in_s.open(RegionLayout);

    if(in_s.fail())
        {
            	cout << "Unable to open file " << RegionLayout << endl;
		        exit(EXIT_FAILURE);
        }
    string tLine;
    while(getline(in_s, tLine)){
        vector<char>R;
        for(size_t i = 0; i < tLine.size(); ++i){
            if(tLine[i] != ','){
                R.push_back(tLine[i]);
                }
            }
        RegionVect.push_back(R); //adds the chars into the regionvect
    }
    in_s.close();
}

void PrintR() //This prints the original region layout
{
    for (size_t row = 0; row < NewRegion.size(); ++row) {
        for (size_t col = 0; col < NewRegion[row].size(); ++col) {
            if(NewRegion[row][col] == 0){
                cout << RegionVect[row][col]; 
            }
            else{
                cout<< NewRegion[row][col];
            }
            if(col != NewRegion[row].size()-1){
                cout<< " ";
            }
        }
        cout << endl; 
    }
    cout<<"Available workers: "<<workers<<endl;
    cout<<"Available goods: "<< goods <<endl;
}
void SpreadPollution()
{
   vector<vector<int> >PollutionTemp(NewRegion.size(), vector<int>(NewRegion[0].size(), 0));
   
    for (size_t row = 0; row < NewRegion.size(); ++row) {
        for (size_t col = 0; col < NewRegion[0].size(); ++col) {
            int indusPopulation = NewRegion[row][col];
            
            // Checks if industrial zone and the population is more then 0
            if (RegionVect[row][col] == 'I' && indusPopulation > 0) {
                PollutionTemp[row][col] += indusPopulation;
                pollution++; // Increase total pollution counter

                // Spread pollution to adj. cells
                for (int a = -1; a <= 1; ++a) {
                    for (int b = -1; b <= 1; ++b) {
                        if (a == 0 && b == 0) continue;
                        int adjRow = row + a;
                        int adjCol = col + b;

                        // Check that adj. cell is within bounds
                        if (adjRow >= 0 && adjRow < NewRegion.size() && adjCol >= 0 && adjCol < NewRegion[0].size()) {
                            // Reduce pollution by 1 for adj. cells
                            PollutionTemp[adjRow][adjCol] += max(0, indusPopulation - 1);
                        }
                    }
                }
            }
        }
    }
    PollutionRegion = PollutionTemp; //asigns to print where the pollution is in the pollution region.
}
//check for change
bool Checker(const vector<vector<int> >&NewRegion, const vector<vector<int> >&PreviousRegion){
    for(size_t i =0;i<NewRegion.size();++i){
        for(size_t j=0;j<NewRegion[i].size();++j){
            if(NewRegion[i][j] != PreviousRegion[i][j]){
                return false;
            }
        }
    }
    return true;
}
void PrintPollution(){
    cout << "This is the pollution region: " << endl;
    for (int i = 0; i < PollutionRegion.size(); ++i) {
        for (int j = 0; j < PollutionRegion[0].size(); ++j) {
            if (PollutionRegion[i][j] == 0) {
                cout << RegionVect[i][j] << " "; 
            } else {
                // Check if the current char is not 'I' and blank space
                if (RegionVect[i][j] != 'I' && RegionVect[i][j] != ' ') {
                    cout << RegionVect[i][j] << "(" << PollutionRegion[i][j] << ") ";  // Print char with pollution value
                } else {
                    cout << PollutionRegion[i][j] << " ";  // Display pollution value for industrial zones
                }
            }
        }
        cout<<endl;
    }
        cout<<"This is the pollution number: "<<pollution<<endl; //total pollution 
        cout << endl;
}
//function for calculating the zones populations 
void CalcZPopulations(){
    int ResPopulationCount = 0; //inilitize all to zero
    //int IndPopulationCount = 0;
    int ComPopulationCount = 0;

    for (size_t row = 0; row < NewRegion.size(); ++row) {
        for (size_t col = 0; col < NewRegion[0].size(); ++col) {
            int population = NewRegion[row][col];
            // Check zone type and add population to the correct zones pop.
            if (RegionVect[row][col] == 'R') {
                ResPopulationCount += population;
            } else if (RegionVect[row][col] == 'I') {
                IndPopulationCount += population;
            } else if (RegionVect[row][col] == 'C') {
                ComPopulationCount += population;
            }
        }
    }
    //Outputs the population totals
    cout << "Final Residential Population: " << ResPopulationCount << endl;
    cout << "Final Industrial Population: " << IndPopulationCount << endl;
    cout << "Final Commercial Population: " << ComPopulationCount << endl;
    cout << "Final Regional Population: " << (ResPopulationCount + IndPopulationCount + ComPopulationCount) << endl;
}
