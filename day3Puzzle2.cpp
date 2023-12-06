#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Function to check the validity of an adjacent position in the search for a schematic symbol
bool isValid(int i, int j, int n, int m) {
    if (i < 0 || j < 0 || i > n - 1 || j > m - 1) {
        return false;
    } else {
        return true;
    }
}


int main() {
    std::string schemFileName;
    std::string schemLine;

    int long long result = 0;

    std::cout << "Enter the schematic file name: ";
    std::cin >> schemFileName;
    std::ifstream schemFile (schemFileName);
    std::vector<std::vector<int>> schemMatrix; //2D coded matrix obtained from original schematic
    std::vector<int> vectorLine;


    // Parse the schematic text file and build a matrix with code integers - check only for gears (*)
    if (schemFile.is_open()) {
        while(getline(schemFile,schemLine)) {
            vectorLine.resize(schemLine.length());
            for (int i = 0; i < schemLine.length(); i++) {
                if (isdigit(schemLine[i])) {
                    vectorLine[i] = schemLine[i] - '0';
                } else if(schemLine[i] == '*') {
                    vectorLine[i] = -2;
                } else {
                    vectorLine[i] = -1;
                }
                //std::cout << vectorLine[i] << ' ';
            }
            //std::cout << std::endl;

            schemMatrix.push_back(vectorLine);
            vectorLine.clear();
        }
    }

    // Process the matrix and find the part numbers

    // Get 2D schematic matrix dimensions
    int n = schemMatrix.size();
    int m = schemMatrix[0].size();
    std::cout << " n, m = " << n << "," << m << std::endl;
    for (int i = 0; i < n; i++) {
        int j = 0;
        while (j < m) {

            int numAdjacent = 0;
            int adjacentCodes[8] = {0,0,0,0,0,0,0,0};
            bool upperLeft = false;
            bool upper = false;
            bool upperRight = false;
            bool left = false;
            bool right = false;
            bool lowerRight = false;
            bool lower = false;
            bool lowerLeft = false;
            std::string tempDigit1;
            std::string tempDigit2;

            if (schemMatrix[i][j] == -2) {
                    // Check adjacent elements in schematic matrix
                    if (isValid(i-1, j-1, n, m)) {
                        if (schemMatrix[i-1][j-1] > -1) {
                            upperLeft = true;
                            numAdjacent += 1;
                            adjacentCodes[0] = 1;
                        }
                    }
                    if (isValid(i-1, j, n, m)) {
                        if (schemMatrix[i-1][j] > -1) {
                            upper = true;
                            if (!upperLeft) {
                                numAdjacent += 1;
                                adjacentCodes[1] = 1;
                            }
                        }
                    }
                    if (isValid(i-1, j+1, n, m)) {
                        if (schemMatrix[i-1][j+1] > -1) {
                            upperRight = true;
                            if (!upper) {
                                numAdjacent += 1;
                                adjacentCodes[2] = 1;
                            }
                        }
                    }
                    if (isValid(i, j-1, n, m)) {
                        if (schemMatrix[i][j-1] > -1) {
                           left = true;
                           numAdjacent += 1;
                           adjacentCodes[3] = 1;
                        }
                    }               
                    if (isValid(i, j+1, n, m)) {
                        if (schemMatrix[i][j+1] > -1) {
                            right = true;
                            numAdjacent += 1;
                            adjacentCodes[4] = 1;
                        }
                    }
                    if (isValid(i+1, j-1, n, m)) {
                        if (schemMatrix[i+1][j-1] > -1) {
                            lowerLeft = true;
                            numAdjacent += 1;
                            adjacentCodes[5] = 1;
                        }
                    }
                    if (isValid(i+1, j, n, m)) {
                        if (schemMatrix[i+1][j] > -1) {
                            lower = true;
                            if (!lowerLeft) {
                                numAdjacent += 1;
                                adjacentCodes[6] = 1;
                            }
                        }
                    }
                    if (isValid(i+1, j+1, n, m)) {
                        if (schemMatrix[i+1][j+1] > -1) {
                            lowerRight = true;
                            if (!lower) {
                                numAdjacent += 1;
                                adjacentCodes[7] = 1;
                            }
                        }
                    }

                if (numAdjacent == 2) {
                    bool leftCheck;
                    bool rightCheck;
                    for (int k = 0; k < 8; k++) {
                        if (adjacentCodes[k] == 1) {
                            switch (k) {
                                case 0:
                                    leftCheck = false;
                                    rightCheck = false;
                                    tempDigit1 = std::to_string(schemMatrix[i-1][j-1]);
                                    //std::cout << tempDigit1 << std::endl;
                                    if (upper) {
                                        tempDigit1 += std::to_string(schemMatrix[i-1][j]);
                                        if (upperRight) {
                                            tempDigit1 += std::to_string(schemMatrix[i-1][j+1]);
                                            int tempJ = j;
                                            while (schemMatrix[i-1][tempJ+2] > -1 && (tempJ+2) < m) {
                                                tempDigit1 += std::to_string(schemMatrix[i-1][tempJ+2]);
                                                tempJ += 1;
                                                rightCheck = true;
                                            }    
                                        } else {
                                            int tempJ = j;
                                            while (schemMatrix[i-1][tempJ-2] > -1 && (tempJ-2) >= 0) {
                                                tempDigit1.insert(0,std::to_string(schemMatrix[i-1][tempJ-2]));
                                                tempJ -= 1;
                                                leftCheck = true;
                                            }       
                                        }
                                    } else {
                                        if (!leftCheck) {
                                            int tempJ = j;
                                            while (schemMatrix[i-1][tempJ-2] > -1 && (tempJ-2) >= 0) {
                                                tempDigit1.insert(0,std::to_string(schemMatrix[i-1][tempJ-2]));
                                                //std::cout << tempDigit1 << std::endl;
                                                tempJ -= 1;
                                                leftCheck = true;
                                            }
                                        }
                                    }
                                    break;

                                case 1:
                                    leftCheck = false;
                                    rightCheck = false;
                                    if (tempDigit1.empty()) {
                                        tempDigit1 = std::to_string(schemMatrix[i-1][j]);
                                        if (upperRight) {
                                            tempDigit1 += std::to_string(schemMatrix[i-1][j+1]);
                                            int tempJ = j;
                                            while (schemMatrix[i-1][tempJ+2] > -1 && (tempJ+2) < m) {
                                                tempDigit1 += std::to_string(schemMatrix[i-1][tempJ+2]);
                                                tempJ += 1;
                                                rightCheck = true;
                                            }                                          
                                        }
                                    } else {
                                        tempDigit2 = std::to_string(schemMatrix[i-1][j]);
                                        if (upperRight) {
                                            tempDigit2 += std::to_string(schemMatrix[i-1][j+1]);
                                            int tempJ = j;
                                            while (schemMatrix[i-1][tempJ+2] > -1 && (tempJ+2) < m) {
                                                tempDigit2 += std::to_string(schemMatrix[i-1][tempJ+2]);
                                                tempJ += 1;
                                                rightCheck = true;
                                            }
                                        }    
                                    }

                                    
                                    break;

                                case 2:
                                    leftCheck = false;
                                    rightCheck = false;
                                    if (tempDigit1.empty()) {
                                        tempDigit1 = std::to_string(schemMatrix[i-1][j+1]);
                                        int tempJ = j;
                                        while (schemMatrix[i-1][tempJ+2] > -1 && (tempJ+2) < m) {
                                                tempDigit1 += std::to_string(schemMatrix[i-1][tempJ+2]);
                                                tempJ += 1;
                                                rightCheck = true;
                                        }    
                                    } else {
                                        tempDigit2 = std::to_string(schemMatrix[i-1][j+1]);
                                        std::cout << tempDigit2 << std::endl;
                                        int tempJ = j;
                                        while (schemMatrix[i-1][tempJ+2] > -1 && (tempJ+2) < m) {
                                                tempDigit2 += std::to_string(schemMatrix[i-1][tempJ+2]);
                                                std::cout << tempDigit2 << std::endl;
                                                tempJ += 1;
                                                rightCheck = true;
                                        }  
                                    }
                                    break;
                                
                                case 3:
                                    leftCheck = false;
                                    rightCheck = false;
                                    if (tempDigit1.empty()) {
                                        tempDigit1 = std::to_string(schemMatrix[i][j-1]);
                                        int tempJ = j;
                                        while (schemMatrix[i][tempJ-2] > -1 && (tempJ-2) >= 0) {
                                                tempDigit1.insert(0,std::to_string(schemMatrix[i][tempJ-2]));
                                                tempJ -= 1;
                                                leftCheck = true;
                                        }    
                                    } else {
                                        tempDigit2 = std::to_string(schemMatrix[i][j-1]);
                                        int tempJ = j;
                                        while (schemMatrix[i][tempJ-2] > -1 && (tempJ-2) >= 0) {
                                                tempDigit2.insert(0,std::to_string(schemMatrix[i][tempJ-2]));
                                                tempJ -= 1;
                                                leftCheck = true;
                                        }    
                                    }
                                    break;

                                case 4:
                                    leftCheck = false;
                                    rightCheck = false;
                                    if (tempDigit1.empty()) {
                                        tempDigit1 = std::to_string(schemMatrix[i][j+1]);
                                        int tempJ = j;
                                        while (schemMatrix[i][tempJ+2] > -1 && (tempJ+2) < m) {
                                                tempDigit1 += std::to_string(schemMatrix[i][tempJ+2]);
                                                tempJ += 1;
                                                rightCheck = true;
                                        }    
                                    } else {
                                        tempDigit2 = std::to_string(schemMatrix[i][j+1]);
                                        int tempJ = j;
                                        while (schemMatrix[i][tempJ+2] > -1 && (tempJ+2) < m) {
                                                tempDigit2 += std::to_string(schemMatrix[i][tempJ+2]);
                                                tempJ += 1;
                                                rightCheck = true;
                                        }  
                                    }
                                    break;

                                case 5:
                                    leftCheck = false;
                                    rightCheck = false;
                                    if (tempDigit1.empty()) {
                                        tempDigit1 = std::to_string(schemMatrix[i+1][j-1]);
                                        if (lower) {
                                            tempDigit1 += std::to_string(schemMatrix[i+1][j]);
                                            if (lowerRight) {
                                                tempDigit1 += std::to_string(schemMatrix[i+1][j+1]);
                                                int tempJ = j;
                                                while (schemMatrix[i+1][tempJ+2] > -1 && (tempJ+2) < m) {
                                                    tempDigit1 += std::to_string(schemMatrix[i+1][tempJ+2]);
                                                    tempJ += 1;
                                                    rightCheck = true;
                                                }    
                                            } else {
                                                int tempJ = j;
                                                while (schemMatrix[i+1][tempJ-2] > -1 && (tempJ-2) >= 0) {
                                                    tempDigit1.insert(0,std::to_string(schemMatrix[i+1][tempJ-2]));
                                                    tempJ -= 1;
                                                    leftCheck = true;
                                                }
                                            }
                                        } else {
                                            int tempJ = j;
                                            while (schemMatrix[i+1][tempJ-2] > -1 && (tempJ-2) >= 0) {
                                                tempDigit1.insert(0,std::to_string(schemMatrix[i+1][tempJ-2]));
                                                tempJ -= 1;
                                                leftCheck = true;
                                            }

                                        } 

                                    } else {
                                        tempDigit2 = std::to_string(schemMatrix[i+1][j-1]);
                                        if (lower) {
                                            tempDigit2 += std::to_string(schemMatrix[i+1][j]);
                                            if (lowerRight) {
                                                tempDigit2 += std::to_string(schemMatrix[i+1][j+1]);
                                                int tempJ = j;
                                                while (schemMatrix[i+1][tempJ+2] > -1 && (tempJ+2) < m) {
                                                    tempDigit2 += std::to_string(schemMatrix[i+1][tempJ+2]);
                                                    tempJ += 1;
                                                    rightCheck = true;
                                                }    
                                            } else {
                                                int tempJ = j;
                                                while (schemMatrix[i+1][tempJ-2] > -1 && (tempJ-2) >= 0) {
                                                    tempDigit2.insert(0,std::to_string(schemMatrix[i+1][tempJ-2]));
                                                    tempJ -= 1;
                                                    leftCheck = true;
                                                }
                                            }
                                        } else {
                                            int tempJ = j;
                                            while (schemMatrix[i+1][tempJ-2] > -1 && (tempJ-2) >= 0) {
                                                tempDigit2.insert(0,std::to_string(schemMatrix[i+1][tempJ-2]));
                                                tempJ -= 1;
                                                leftCheck = true;
                                            }

                                        } 

                                        
                                    }
                                    break;
                                
                                case 6:
                                    leftCheck = false;
                                    rightCheck = false;
                                    if (tempDigit1.empty()) {
                                        tempDigit1 = std::to_string(schemMatrix[i+1][j]);
                                        if (lowerRight) {
                                            tempDigit1 += std::to_string(schemMatrix[i+1][j+1]);
                                            int tempJ = j;
                                            while (schemMatrix[i+1][tempJ+2] > -1 && (tempJ+2) < m) {
                                                tempDigit1 += std::to_string(schemMatrix[i+1][tempJ+2]);
                                                tempJ += 1;
                                                rightCheck = true;
                                            }
                                        }
                                    } else {
                                        tempDigit2 = std::to_string(schemMatrix[i+1][j]);
                                        if (lowerRight) {
                                            tempDigit2 += std::to_string(schemMatrix[i+1][j+1]);
                                            int tempJ = j;
                                            while (schemMatrix[i+1][tempJ+2] > -1 && (tempJ+2) < m) {
                                                tempDigit2 += std::to_string(schemMatrix[i+1][tempJ+2]);
                                                tempJ += 1;
                                                rightCheck = true;
                                            }
                                        }   
                                    }
                                    break;

                                case 7:
                                    leftCheck = false;
                                    rightCheck = false;
                                    if (tempDigit1.empty()) {
                                        tempDigit1 = std::to_string(schemMatrix[i+1][j+1]);
                                        int tempJ = j;
                                        while (schemMatrix[i+1][tempJ+2] > -1 && (tempJ+2) < m) {
                                                tempDigit1 += std::to_string(schemMatrix[i+1][tempJ+2]);
                                                tempJ += 1;
                                                rightCheck = true;
                                        }    
                                    } else {
                                        tempDigit2 = std::to_string(schemMatrix[i+1][j+1]);
                                        int tempJ = j;
                                        while (schemMatrix[i+1][tempJ+2] > -1 && (tempJ+2) < m) {
                                                tempDigit2 += std::to_string(schemMatrix[i+1][tempJ+2]);
                                                tempJ += 1;
                                                rightCheck = true;
                                        }  
                                    }
                                    break;

                            }
                        }
                    }
                    std::cout << tempDigit1 << " , " << tempDigit2 << std::endl;
                    result += (std::stoi(tempDigit1) * std::stoi(tempDigit2));
                    numAdjacent = 0;
                    std::cout << result << std::endl;
                }
                
                tempDigit1.clear();
                tempDigit2.clear();               
                j += 1;
            } else {
                j += 1;
            }
       
        }
    }
    std::cout << result << std::endl;
    return 0;
}