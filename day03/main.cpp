#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void part1(std::vector<std::vector<int>> battery_banks)
{
    int max_joltage = 0;
    for (std::vector<int> battery_bank: battery_banks) {
        int tens = battery_bank[0];
        int ones = battery_bank[1];
        for (size_t i = 2; i < battery_bank.size(); i++) {
            if (ones > tens) {
                tens = ones;
                ones = battery_bank[i];
            } else if (battery_bank[i] > ones) {
                ones = battery_bank[i];
            }
        }
        max_joltage += tens*10 + ones;
    }
    
    std::cout << "PART ONE: " << max_joltage << std::endl;
}

void part2(std::vector<std::vector<int>> battery_banks)
{
    long max_joltage = 0;
    for (std::vector<int> battery_bank: battery_banks) {
        std::vector<int> batteries;
        for (int i = 0; i < 12; i++) {
            batteries.push_back(battery_bank[i]);
        }

        for (int i = 12; i < battery_bank.size(); i++) {
            for (int j = 0; j < 11; j++) {
                if (batteries[j] < batteries[j+1]) {
                    batteries.erase(batteries.begin() + j);
                    batteries.push_back(battery_bank[i]);
                    break;
                }
            }

            if (battery_bank[i] > batteries[11]) {
                batteries[11] = battery_bank[i];
            }
        }

        long joltage = 0;
        for (int i = 0; i < 12; i++) {
            joltage += batteries[i] * pow(10, 11-i);
        }
        max_joltage += joltage;
    }
    
    std::cout << "PART TWO: " << max_joltage << std::endl;
}

int main(int argc, char* argv[])
{
    std::vector<std::vector<int>> battery_banks;

    std::string line;
    std::ifstream inputFile((argc == 2) ? argv[1] : "input.txt");
    while (std::getline(inputFile, line)) {
        std::vector<int> battery_bank;
        if (line.back() == '\r') line.pop_back();
        for (char battery: line) {
            battery_bank.push_back(int(battery - '0'));
        }
        battery_banks.push_back(battery_bank);
    }

    part1(battery_banks);
    part2(battery_banks);

    return 0;
}