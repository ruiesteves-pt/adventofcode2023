#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <vector>
#include <numeric>

int main () {

    std::set<int> winningNumbers;
    std::set<int> elfNumbers;
    std::set<int> intersection;
    std::string digits;

    int result;

    std::string scratchFileName;
    std::string scratchLine;

    std::cout << "Enter the scratchcard file name: ";
    std::cin >> scratchFileName;
    std::ifstream scratchFile (scratchFileName);

    int lineCount = 0;

    if (scratchFile.is_open()) {
        while(getline(scratchFile,scratchLine)) {
            lineCount++;
        }

        
        scratchFile.close(); // Close the file
        scratchFile.open(scratchFileName); // Reopen the file

        std::vector<int> cardPlayed(lineCount,0);

        for (int l = 0; l < lineCount; l++) {
            std::getline(scratchFile,scratchLine);

            cardPlayed[l] += 1;
            int i = 0;
            bool winningSwitch = false;
            bool startSwitch = false;

            while (i < scratchLine.length()) {
                if (scratchLine[i] == ':') {
                    startSwitch = true;
                }
                
                if (startSwitch) {
                    // Form and add digits together
                    while (isdigit(scratchLine[i])) {
                        digits.push_back(scratchLine[i]);
                        i += 1;
                    }

                    // Turn digits to an int value and add it to the correct set
                    if (!digits.empty() && !winningSwitch) {
                        winningNumbers.insert(std::stoi(digits));
                        digits.clear();
                    } else if (!digits.empty()) {
                        elfNumbers.insert(std::stoi(digits));
                        digits.clear();
                    }

                    // Flip the number switch
                    if (scratchLine[i] == '|') {
                        winningSwitch = !winningSwitch;
                    }
                    i += 1;
                } else {
                    i += 1;
                }
            }

            std::set_intersection(winningNumbers.begin(), winningNumbers.end(), elfNumbers.begin(), elfNumbers.end(),std::inserter(intersection, intersection.begin()));
            if (!intersection.empty()) {
                size_t counterResult = intersection.size();
                for (int k = 0; k < counterResult; k++) {
                    cardPlayed[l+k+1] += cardPlayed[l];
                }
            }
            winningNumbers.clear();
            elfNumbers.clear();
            intersection.clear();
        }

        result = std::accumulate(cardPlayed.begin(), cardPlayed.end(), 0);
        std::cout << result << std::endl;;
    }
    
}