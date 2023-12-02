#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int main() {

    std::string calibrationFileName;
    std::string calibrationLine;
    std::string digits;
    std::string code;
    std::vector<int> positions;
    int result = 0;

    std::cout << "Enter the calibration file name: " ;
    std::cin >> calibrationFileName;
    std::ifstream calibrationFile (calibrationFileName);

    std::string numbers[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};


    if (calibrationFile.is_open()) {
        while(getline(calibrationFile, calibrationLine)) {

            for (int i = 0; i < 9; i++) {
                size_t pos = calibrationLine.find(numbers[i]);

                while (pos != std::string::npos) {
                    positions.push_back(static_cast<int>(pos));
                    positions.push_back(i+1);

                    pos = calibrationLine.find(numbers[i], pos + numbers[i].size());
                }

            }

            if (!positions.empty()) {
                for (int i = 0; i < (positions.size() - 1); i+=2) {
                    calibrationLine.replace(positions.at(i), 1, std::to_string(positions.at(i+1)));
                }
            }


            for (char ch : calibrationLine) {
                if (isdigit(ch)) {
                    digits.push_back(ch);
                }
            }

            if (digits.length() <= 1) {
                code.push_back(digits[0]);
                code.push_back(digits[0]);
            } else {
                code.push_back(digits[0]);
                code.push_back(digits.back());
            }

            int codeInt = std::stoi(code);
            result += codeInt;

            digits.clear();
            code.clear();
            positions.clear();  
        }
     
    }
    std::cout << "Result: " << result;
    return 0;
};
