#include "Vectors.h"
#include "commercial.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
//functions very similiar to industrial/residential
Commercial::Commercial(){}

void Commercial::InitilizeCommercial(){
    int numRows = RegionVect.size();
    int numCols = RegionVect[0].size();

    for(int i=0;i<numRows; ++i){
        for(int j=0;j<numCols;++j){
            if(RegionVect[i][j] == 'C'){
                commercialZones.push_back(make_pair(i, j)); //adds the location of C into the commercial zone
            }
        }
    }
}
void Commercial::UpdateCom(){
    for (size_t i = 0; i < commercialZones.size(); ++i) {
        int row = commercialZones[i].first;
        int col = commercialZones[i].second;
        GrowCommercial(row, col);
    }
}
void Commercial::GrowCommercial(int row, int col) {
    int currentPop = NewRegion[row][col];
    if(goods < 1 || workers < 1){
        return;
    }
    else if (currentPop == 0 && isAdjacentToPowerlineCommercial(row, col)){
            NewRegion[row][col]++;
            workers--;
            goods--;
            return;
        }
    else if (currentPop == 0 && countAdjacentPopCommercial(row, col, 1)){
            NewRegion[row][col]++;
            workers--;
            goods--; 
            return;
        }
    else if (currentPop == 1 && countAdjacentPopCommercial(row, col, 1)){
            NewRegion[row][col]++; 
            workers--;
            goods--;    
            return;
        }
}


int Commercial::countAdjacentPopCommercial(int row, int col, int minPopulation){
    int count = 0;
    int numRows = RegionVect.size();
    int numCols = RegionVect[0].size();

    int directions[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}}; //8 possible corners 

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
bool Commercial::isAdjacentToPowerlineCommercial(int row, int col){
    int numRows = RegionVect.size();
    int numCols = RegionVect[0].size();

    int directions[8][2] = 
    {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

    for (int i = 0; i < 8; ++i) {
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];

        if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols) {
            if (RegionVect[newRow][newCol] == 'P' || RegionVect[newRow][newCol] == 'T' || RegionVect[newRow][newCol] == '#') {
                return true;
            }
        }
    }
    return false;
}