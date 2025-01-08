#include "Vectors.h"
#include "Tree.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

vector<vector<int> >TreeRegion;
int tree = 0; //number of trees are zero to begin. 
Tree::Tree(){}

void Tree::SpreadTree(){
    vector<vector<int> >TreeTemp(NewRegion.size(), vector<int>(NewRegion[0].size(), 0));
    vector<vector<int> > PollutionTemp(NewRegion.size(), vector<int>(NewRegion[0].size(), 0));
    int treesAdded = 0; //tracks the temp trees
    for (size_t row = 0; row < NewRegion.size(); ++row) {
        for (size_t col = 0; col < NewRegion[0].size(); ++col) {
            int pollutionLevel = PollutionRegion[row][col];

        if (pollutionLevel > 0 ) {
            if (TreeTemp[row][col] == 0) {
                TreeTemp[row][col] = 1;
                treesAdded++; //start tree growth
            }
            PollutionRegion[row][col] = max(0, pollutionLevel - 1);
            pollution -= 1;
            IndPopulationCount += 1; //increases the industrial population as the pollution decreases
                
            // Spread trees to adj. cells
                for (int a = -1; a <= 1; ++a) {
                    for (int b = -1; b <= 1; ++b) {
                        if (a == 0 && b == 0) continue;
                        int adjRow = row + a;
                        int adjCol = col + b;

                        // Check bounds
                        if (adjRow >= 0 && adjRow < NewRegion.size() && adjCol >= 0 && adjCol < NewRegion[0].size()) {
                            if (TreeTemp[adjRow][adjCol] == 0){
                            TreeTemp[adjRow][adjCol] = 1;
                            treesAdded++;
                            }
                        }
                    }
                }
             }
        }
    }
    TreeRegion = TreeTemp; //storing the temp trees into the final tree region
    tree = treesAdded; // Update the total tree count
}

void Tree::PrintTree(){
    cout << "This is the Tree region: " << endl;
    for (size_t i = 0; i < TreeRegion.size(); ++i) {
        for (size_t j = 0; j < TreeRegion[0].size(); ++j) {
            if (TreeRegion[i][j] == 0) {
                cout << RegionVect[i][j] << " "; // Print initial region if no trees grew
            }
            else {
                    cout << TreeRegion[i][j] << " ";  // Display tree region
                }
            }
        cout << endl;
    }
        cout<<"This is the Tree number: "<<tree<<endl; //output total trees 
        cout << endl;
}
//this function is used to update the population to call in the main after trees are grown
void Tree::NewIndustrialPopulation(){
        cout<<"This is the Industrial Population after the growth of trees: "<< IndPopulationCount << endl;
}
