#include <iostream>
#include <fstream>
#include <string>
#include <vector>


void part1(std::vector<int> rotations)
{
    int dial = 50; // starting point
    int password = 0;

    for (int rotation : rotations) {
        dial = (dial + rotation + 100) % 100;
        password += (dial == 0) ? 1 : 0;
    }

    std::cout << "PART ONE: " << password << std::endl;
}

void part2(std::vector<int> rotations)
{
    int dial = 50; // starting point
    int password = 0;

    for (int rotation : rotations) {
        if (rotation > 0) { // Right rotation
            password += (dial + rotation) / 100;
        } else { // Left rotation
            if ((dial + rotation) <= 0) {
                password += ((dial + rotation) / -100);
                if (dial != 0) {
                    password += 1;
                }
            }
        }

        dial = ((dial + rotation) % 100 + 100) % 100;
    }

    std::cout << "PART TWO: " << password << std::endl;
}

int main(int argc, char* argv[])
{
    std::vector<int> rotations;

    std::string input = (argc == 2) ? argv[1] : "input.txt";

    std::string line;
    std::ifstream inputFile(input);
    while (std::getline(inputFile, line)) {
        int sign = (line[0] == 'L') ? -1 : 1;
        int rotation = sign * std::stoi(line.substr(1));
        rotations.push_back(rotation);
    }

    part1(rotations);
    part2(rotations);

    return 0;
}