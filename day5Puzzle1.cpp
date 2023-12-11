#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

int main() {

    std::string almanacFileName;
    std::string almanacLine;
    std::cout << "Enter the almanac file name: ";
    std::cin >> almanacFileName;
    std::ifstream almanacFile (almanacFileName);

    std::vector<long long int> seeds;
    std::vector<long long int> soil;
    std::vector<long long int> fertilizer;
    std::vector<long long int> water;
    std::vector<long long int> light;
    std::vector<long long int> temperature;
    std::vector<long long int> humidity;
    std::vector<long long int> location;

    std::vector<std::string> categories = {"seed-to-soil map:","soil-to-fertilizer map:","fertilizer-to-water map:","water-to-light map:","light-to-temperature map:","temperature-to-humidity map:","humidity-to-location map:"};
    int categoryCounter = 0;
    int lineCounter = 0;
    std::string digits;

    if (almanacFile.is_open()) {
        while(getline(almanacFile,almanacLine)) {
            //std::cout << almanacLine << std::endl;
            int i = 0;
            //std::cout << lineCounter << std::endl;
            while(i < almanacLine.length()) {
                if (lineCounter == 0) {
                    while (isdigit(almanacLine[i])) {
                        digits.push_back(almanacLine[i]);
                        i += 1;
                    }
                    if (!digits.empty()) {
                        seeds.push_back(std::stoll(digits));
                        std::cout << digits << std::endl;
                        digits.clear();
                    } else {
                        i += 1;
                    }
                } else {
                    //std::cout << almanacLine[0] << std::endl;
                    if ((almanacLine.length() != 0) && !isdigit(almanacLine[0]) && i == 0) {
                        categoryCounter += 1;
                        //std::cout << "First element of line " << lineCounter << "=" << almanacLine[0] << std::endl;
                    }
                    //std::cout << categoryCounter << std::endl;
                    switch (categoryCounter) {
                    case 1:
                        while (isdigit(almanacLine[i])) {
                            digits.push_back(almanacLine[i]);
                            i += 1;
                        }
                        if (!digits.empty()) {
                            soil.push_back(std::stoll(digits));
                            digits.clear();
                        }
                        break;
                    
                    case 2:
                        while (isdigit(almanacLine[i])) {
                            digits.push_back(almanacLine[i]);
                            i += 1;
                        }
                        if (!digits.empty()) {
                            fertilizer.push_back(std::stoll(digits));
                            digits.clear();
                        }
                        break;

                    case 3:
                        while (isdigit(almanacLine[i])) {
                            digits.push_back(almanacLine[i]);
                            i += 1;
                        }
                        if (!digits.empty()) {
                            water.push_back(std::stoll(digits));
                            digits.clear();
                        }
                        break; 

                    case 4:
                        while (isdigit(almanacLine[i])) {
                            digits.push_back(almanacLine[i]);
                            i += 1;
                        }
                        if (!digits.empty()) {
                            light.push_back(std::stoll(digits));
                            digits.clear();
                        }
                        break;

                    case 5:
                        while (isdigit(almanacLine[i])) {
                            digits.push_back(almanacLine[i]);
                            i += 1;
                        }
                        if (!digits.empty()) {
                            temperature.push_back(std::stoll(digits));
                            digits.clear();
                        }
                        break;

                    case 6:
                        while (isdigit(almanacLine[i])) {
                            digits.push_back(almanacLine[i]);
                            i += 1;
                        }
                        if (!digits.empty()) {
                            humidity.push_back(std::stoll(digits));
                            digits.clear();
                        }
                        break;

                    case 7:
                        while (isdigit(almanacLine[i])) {
                            digits.push_back(almanacLine[i]);
                            i += 1;
                        }
                        if (!digits.empty()) {
                            location.push_back(std::stoll(digits));
                            digits.clear();
                        }
                        break;

                    default:
                        break;
                    }
                    i += 1;
                }
            }
            lineCounter += 1;
        }
    }

    std::vector<long long int> solutionVector(seeds.size());

    for (int i = 0; i < seeds.size(); i++) {

        int mapCodes[7] = {0,0,0,0,0,0,0};
        solutionVector[i] = seeds[i];
        for (int m = 0; m < soil.size(); m+=3) {
            if ((solutionVector[i] >= soil[m+1]) && (solutionVector[i] < soil[m+1]+soil[m+2]) && !mapCodes[0]) {
                solutionVector[i] = soil[m] + (solutionVector[i] - soil[m+1]);
                mapCodes[0] = 1;
            }
        }

        for (int m = 0; m < fertilizer.size(); m+=3) {
            if ((solutionVector[i] >= fertilizer[m+1]) && (solutionVector[i] < fertilizer[m+1]+fertilizer[m+2]) && !mapCodes[1]) {
                solutionVector[i] = fertilizer[m] + (solutionVector[i] - fertilizer[m+1]);
                mapCodes[1] = 1;
            }
        }
        //std::cout << solutionVector[i] << std::endl;

        for (int m = 0; m < water.size(); m+=3) {
            if ((solutionVector[i] >= water[m+1]) && (solutionVector[i] < (water[m+1]+water[m+2])) && !mapCodes[2]) {
                solutionVector[i] = water[m] + (solutionVector[i] - water[m+1]);
                mapCodes[2] = 1;  
            }
        }
        //std::cout << solutionVector[i] << std::endl;

        for (int m = 0; m < light.size(); m+=3) {
            if ((solutionVector[i] >= light[m+1]) && (solutionVector[i] < (light[m+1]+light[m+2])) && !mapCodes[3]) {
                solutionVector[i] = light[m] + (solutionVector[i] - light[m+1]);
                mapCodes[3] = 1;  
            }
        }
        //std::cout << solutionVector[i] << std::endl;

        for (int m = 0; m < temperature.size(); m+=3) {
            if ((solutionVector[i] >= temperature[m+1]) && (solutionVector[i] < (temperature[m+1]+temperature[m+2])) && !mapCodes[4]) {
                solutionVector[i] = temperature[m] + (solutionVector[i] - temperature[m+1]);
                mapCodes[4] = 1;  
            }
        }
        //std::cout << solutionVector[i] << std::endl;

        for (int m = 0; m < humidity.size(); m+=3) {
            if ((solutionVector[i] >= humidity[m+1]) && (solutionVector[i] < (humidity[m+1]+humidity[m+2])) && !mapCodes[5]) {
                solutionVector[i] = humidity[m] + (solutionVector[i] - humidity[m+1]);
                mapCodes[5] = 1;  
            }
        }
        //std::cout << solutionVector[i] << std::endl;

        for (int m = 0; m < location.size(); m+=3) {
            if ((solutionVector[i] >= location[m+1]) && (solutionVector[i] < (location[m+1]+location[m+2])) && !mapCodes[6]) {
                solutionVector[i] = location[m] + (solutionVector[i] - location[m+1]);
                mapCodes[6] = 1;  
            }
        }
        //std::cout << solutionVector[i] << std::endl;

    }

    auto minElement = std::min_element(solutionVector.begin(), solutionVector.end());

    if (minElement != solutionVector.end()) {
        std::cout << "The smallest location: " << *minElement << std::endl;
    } else {
        std::cout << "The vector is empty." << std::endl;
    }
    // DEBUG PRINTING
    /*
    for (int seed : seeds) {
        std::cout << seed << ' ';
    }

    std::cout << std::endl;
    for (int s : soil) {
        std::cout << s << ' ';
    }

    std::cout << std::endl;
    for (int f : fertilizer) {
        std::cout << f << ' ';
    }

    std::cout << std::endl;
    for (int w : water) {
        std::cout << w << ' ';
    }

    std::cout << std::endl;
    for (int l : light) {
        std::cout << l << ' ';
    }

    std::cout << std::endl;
    for (int l : temperature) {
        std::cout << l << ' ';
    }

    std::cout << std::endl;
    for (int l : humidity) {
        std::cout << l << ' ';
    }

    std::cout << std::endl;
    for (int l : location) {
        std::cout << l << ' ';
    }
    */

    return 0;
}