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


    if (gameFile.is_open()) {
        
        while(getline(gameFile, gameLine)) {
            bool gameProcessed = false;
            int ch = 0;
            int red = 1;
            int green = 1;
            int blue = 1;
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
                                    if (tempColor > red) {
                                        red = tempColor;
                                    }
                                    ch += 3;
                                    break;
                                case 1:
                                    if (tempColor > green) {
                                        green = tempColor;
                                    }
                                    ch += 5; // advance length of green
                                    break;
                                case 2:
                                    if (tempColor > blue) {
                                        blue = tempColor;
                                    }
                                    ch += 4; // advance length of blue
                                    break;
                            }
                        }
                    }

                    ch += 2;
                }
            }
            result += (red*green*blue);
        }
    }
    std::cout << result;
    return 0;
}