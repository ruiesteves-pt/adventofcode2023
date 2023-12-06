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


    // Parse the schematic text file and build a matrix with code integers
    if (schemFile.is_open()) {
        while(getline(schemFile,schemLine)) {
            vectorLine.resize(schemLine.length());
            for (int i = 0; i < schemLine.length(); i++) {
                if (isdigit(schemLine[i])) {
                    vectorLine[i] = schemLine[i] - '0';
                } else if(schemLine[i] == '.') {
                    vectorLine[i] = -1;
                } else {
                    vectorLine[i] = -2;
                }
                //std::cout << vectorLine[i] << ' ';
            }
            //std::cout << std::endl;

            schemMatrix.push_back(vectorLine);
            vectorLine.clear();
        }
    }

    // Process the matrix and find the part numbers
    std::string partString;

    // Get 2D schematic matrix dimensions
    int n = schemMatrix.size();
    int m = schemMatrix[0].size();

    for (int i = 0; i < n; i++) {
        int j = 0;
        while (j < m) {
            bool partFlag = false;
            if (schemMatrix[i][j] > -1) {
                while (schemMatrix[i][j] > -1 && j < m) {
                    std::string tempDigit = std::to_string(schemMatrix[i][j]);

                    // Check adjacent elements in schematic matrix
                    if (isValid(i-1, j-1, n, m)) {
                        if (schemMatrix[i-1][j-1] == -2) {
                            partFlag = true;
                        }
                    }

                    if (isValid(i-1, j, n, m) && !partFlag) {
                        if (schemMatrix[i-1][j] == -2) {
                            partFlag = true;
                        }
                    }

                    if (isValid(i-1, j+1, n, m) && !partFlag) {
                        if (schemMatrix[i-1][j+1] == -2) {
                            partFlag = true;
                        }
                    }

                    if (isValid(i, j-1, n, m) && !partFlag) {
                        if (schemMatrix[i][j-1] == -2) {
                            partFlag = true;
                        }
                    }               

                    if (isValid(i, j+1, n, m) && !partFlag) {
                        if (schemMatrix[i][j+1] == -2) {
                            partFlag = true;
                        }
                    }

                    if (isValid(i+1, j-1, n, m) && !partFlag) {
                        if (schemMatrix[i+1][j-1] == -2) {
                            partFlag = true;
                        }
                    }

                    if (isValid(i+1, j, n, m) && !partFlag) {
                        if (schemMatrix[i+1][j] == -2) {
                            partFlag = true;
                        }
                    }

                    if (isValid(i+1, j+1, n, m) && !partFlag) {
                        if (schemMatrix[i+1][j+1] == -2) {
                            partFlag = true;
                        }
                    }
                    partString += tempDigit;
                    j += 1;
                }          

                if (partFlag) {
                    result += stoi(partString);
                }
                partString.clear();
            } else {
                j += 1;
            }
       
        }
    }
    std::cout << result << std::endl;
    return 0;
}