#include "Vectors.h"
#include "industrial.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

Industrial::Industrial(){}

void Industrial::InitilizeIndustrial(){
    int numRows = RegionVect.size();
    int numCols = RegionVect[0].size();

    for(int i=0;i<numRows; ++i){
        for(int j=0;j<numCols;++j){
            if(RegionVect[i][j] == 'I'){
                industrialZones.push_back(make_pair(i, j)); //adds the location of I into the industrial zone
            }
        }
    }
}
void Industrial::UpdateInd(){
    for (size_t i = 0; i < industrialZones.size(); ++i) {
        int row = industrialZones[i].first; //represents the 1 value pair ( x, )
        int col = industrialZones[i].second; //represents the 2nd value pair ( , y)
        GrowIndustrial(row, col);
    }
}
//grows the industrial zone based on the position of the cells and subtracts the workers, adds goods. 
void Industrial::GrowIndustrial(int row, int col){
    int currentPop = NewRegion[row][col];
    if (workers < 2) return;

    if (currentPop == 0 && isAdjacentToPowerlineIndustrial(row, col)) {
        NewRegion[row][col]++;
        workers -= 2;
        goods++;
        return;
    }
    if (currentPop == 0 && countAdjacentPopIndustrial(row, col, 1) >= 1) {
        NewRegion[row][col]++;
        workers -= 2;
        goods++;
        return;
    }
    if (currentPop == 1 && countAdjacentPopIndustrial(row, col, 1) >= 2) {
        NewRegion[row][col]++;
        workers -= 2;
        goods++;
        return;
    }
    if (currentPop == 2 && countAdjacentPopIndustrial(row, col, 2) >= 4) {
        NewRegion[row][col]++;
        workers -= 2;
        goods++;
        return;
    }
}
int Industrial::countAdjacentPopIndustrial(int row, int col, int minPopulation){
    int count = 0;
    int numRows = RegionVect.size();
    int numCols = RegionVect[0].size();

    int directions[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

    for (int i = 0; i < 8; ++i) {
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];

        if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols) {
            if (NewRegion[newRow][newCol] >= minPopulation) {
                count++;
            }
        }
    }
    return count;
}
bool Industrial::isAdjacentToPowerlineIndustrial(int row, int col){
    int numRows = RegionVect.size();
    int numCols = RegionVect[0].size();

    int directions[8][2] = 
    {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}}; //8 possible directions of adj. cells to check

    for (int i = 0; i < 8; ++i) {
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];

        if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols) {
            //below will check for a powerline or other for adjacency.
            if (RegionVect[newRow][newCol] == 'P' || RegionVect[newRow][newCol] == 'T' || RegionVect[newRow][newCol] == '#') {
                return true;
            }
        }
    }
    return false;
}