#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int main() {

    std::string gameFileName;
    std::string gameLine;

    int result = 0;

    std::cout << "Enter the game file name: ";
    std::cin >> gameFileName;
    std::ifstream gameFile (gameFileName);
    int gameNumber;
    int tempColor;
    std::vector<size_t> posColors(3);

    int totalRed = 12;
    int totalGreen = 13;
    int totalBlue = 14;

    if (gameFile.is_open()) {
        
        while(getline(gameFile, gameLine)) {
            bool gameProcessed = false;
            int ch = 0;
            bool gameFlag = true;
            int red = 0;
            int green = 0;
            int blue = 0;
            while (ch < gameLine.length()) {

                // Check if the game number has been processed, if not, process it.
                if (!(gameProcessed)) {
                    int counterGame = 0;
                    ch = 5;
                    while (gameLine[ch+counterGame] != ':') {
                      counterGame += 1;
                    }
                    gameNumber = std::stoi(gameLine.substr(ch,counterGame+1));
                    gameProcessed = true;
                    ch += counterGame + 2; // After the ':', there is a space and only then appears a digit.
                } else {
                    // Get the first digit and temporarly store it.
                    int counterColor = 0;
                    if (isdigit(gameLine[ch])) {
                        while (gameLine[ch+counterColor] != ' ') {
                          counterColor += 1;
                        }
                        tempColor = std::stoi(gameLine.substr(ch,counterColor+1));
                    }
                    ch += counterColor + 1;

                    posColors[0] = gameLine.find("red",static_cast<size_t>(ch));
                    posColors[1] = gameLine.find("green",static_cast<size_t>(ch));
                    posColors[2] = gameLine.find("blue",static_cast<size_t>(ch));

                    for (int i = 0; i < 3; i++) {
                        if (posColors[i] == ch) {
                            switch (i) {
                                case 0:
                                    red = tempColor;
                                    ch += 3;
                                    break;
                                case 1:
                                    green = tempColor;
                                    ch += 5; // advance length of green
                                    break;
                                case 2:
                                    blue = tempColor;
                                    ch += 4; // advance length of blue
                                    break;
                            }
                        }
                    }

                    if (gameLine[ch] == ',') {
                        ch += 2;
                    } else {
                        // Set is over
                        if (red > totalRed || green > totalGreen || blue > totalBlue) {
                            ch = gameLine.length() + 1;
                            gameFlag = false;
                        } else {
                            ch += 2;
                        }
                    }
                }
            }
            if (gameFlag) {
                result += gameNumber;
            }
        }
    }
    std::cout << result;
    return 0;
}