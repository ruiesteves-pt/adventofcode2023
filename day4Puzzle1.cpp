#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <cmath>

int main () {

    std::set<int> winningNumbers;
    std::set<int> elfNumbers;
    std::set<int> intersection;
    std::string digits;

    int result = 0;

    std::string scratchFileName;
    std::string scratchLine;

    std::cout << "Enter the scratchcard file name: ";
    std::cin >> scratchFileName;
    std::ifstream scratchFile (scratchFileName);

    if (scratchFile.is_open()) {
        while(getline(scratchFile,scratchLine)) {
            
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

            /*
            for (auto j : winningNumbers) {
                std::cout << j << ' ';
            }

            std::cout << " | ";

            for (auto j : elfNumbers) {
                std::cout << j << ' ';
            }
            
            std::cout << std::endl;
            */

            std::set_intersection(winningNumbers.begin(), winningNumbers.end(), elfNumbers.begin(), elfNumbers.end(),std::inserter(intersection, intersection.begin()));

            if (!intersection.empty()) {
                size_t counterResult = intersection.size();
                //std::cout << "Intersection size = " << counterResult-1 << std::endl;
                result += pow(2,counterResult-1);
                //std::cout << result << std::endl;;
            }
            winningNumbers.clear();
            elfNumbers.clear();
            intersection.clear();
        }
    }
    std::cout << result << std::endl;;
}