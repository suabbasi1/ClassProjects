#ifndef RESIDENTIAL_H
#define RESIDENTIAL_H
#include <vector>
//Declares teh function for growing the industrial zones
class Residential{
public:
    Residential();
    void UpdateRes();
    void InitilizeResidential();
    void GrowResidential(int row,int col);
    int countAdjacentPop(int row, int col, int minPopulation);
    bool isAdjacentToPowerline(int row, int col);
 
private:
    vector<pair<int, int> > residentialZones; //vector to gold 2 integer pairs
};


#endif
