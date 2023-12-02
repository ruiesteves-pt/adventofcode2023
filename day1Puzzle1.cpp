#include <iostream>
#include <string>
#include <fstream>

int main() {

    std::string calibrationFileName;
    std::string calibrationLine;
    std::string digits;
    std::string code;
    int result = 0;

    std::cout << "Enter the calibration file name: " ;
    std::cin >> calibrationFileName;
    std::ifstream calibrationFile (calibrationFileName);

    if (calibrationFile.is_open()) {
        while(getline(calibrationFile, calibrationLine)) {
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

            //std::cout << code << std::endl;
            int codeInt = std::stoi(code);
            result += codeInt;

            digits.clear();
            code.clear();  
        }
     
    }
    std::cout << "Result: " << result;
    return 0;
};
