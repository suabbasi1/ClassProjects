#ifndef INDUSTRIAL_H
#define INDUSTRIAL_H
#include <vector>

//Declares teh function for growing the industrial zones
class Industrial{
public:
    Industrial();
    void UpdateInd();
    void InitilizeIndustrial();
    void GrowIndustrial(int row,int col);
    int countAdjacentPopIndustrial(int row, int col, int minPopulation);
    bool isAdjacentToPowerlineIndustrial(int row, int col);
 
private:
    vector<pair<int, int> > industrialZones; //vector to store 2 int pairs
};

#endif