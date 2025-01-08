#include "Vectors.h"
#include "residential.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

//all functions for residential zones
Residential::Residential() {}

void Residential::InitilizeResidential(){
    int numRows = RegionVect.size();
    int numCols = RegionVect[0].size();

    for(int i=0;i<numRows; ++i){
        for(int j=0;j<numCols;++j){
            if(RegionVect[i][j] == 'R'){
                residentialZones.push_back(make_pair(i, j)); //adds the location of R into the residential zone
            }
        }
    }
}

void Residential::UpdateRes() {
    for (size_t i = 0; i < residentialZones.size(); ++i) {
        int row = residentialZones[i].first;
        int col = residentialZones[i].second;
        GrowResidential(row, col);  // this passes pairs (in other words the corrdinates)
    }
}

void Residential::GrowResidential(int row, int col) {
            int currentPop = NewRegion[row][col];
            if (currentPop == 0 && isAdjacentToPowerline(row, col)){
                    NewRegion[row][col]++; // Update to population 1
                    workers++;
                    return;
                
            }
            else if (currentPop == 0 && countAdjacentPop(row, col, 1) >= 1) {
                    NewRegion[row][col]++;
                    workers++;
                    return;
                }
            else if (currentPop == 1 && countAdjacentPop(row, col, 1) >= 2) {
                    NewRegion[row][col]++;
                    workers++;
                    return;
                }
            else if (currentPop == 2 && countAdjacentPop(row, col, 2) >= 4) {
                    NewRegion[row][col]++;
                    workers++;
                    return;
                }
            else if (currentPop == 3 && countAdjacentPop(row, col, 3) >= 6) {
                    NewRegion[row][col]++;
                    workers++;
                    return;
                }
            else if (currentPop == 4 && countAdjacentPop(row, col, 4) >= 8) {
                    NewRegion[row][col]++;
                    workers++;
                    return;
                }
}
//check to see if min populaion is met
int Residential::countAdjacentPop(int row, int col, int minPopulation) {
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
//checks if the pair is ajd. to powerline in order to return true and grow.
bool Residential::isAdjacentToPowerline(int row, int col) {
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

