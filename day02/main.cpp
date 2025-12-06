#include <array>
#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <string>
#include <vector>


void part1(std::vector<std::array<std::string, 2>> ranges)
{
    long invalid_ids_sum = 0;
    for (std::array<std::string, 2> range: ranges) {
        long start = std::stol(range[0]);
        long end = std::stol(range[1]);

        long sequence;
        if (range[0].length() % 2 == 0) {
            sequence = std::stol(range[0].substr(0, range[0].length()/2));
        } else {
            sequence = std::stol("1" + std::string(range[0].length()/2, '0'));
        }

        while (true) {
            long invalid_id = std::stol(std::to_string(sequence) + std::to_string(sequence));
            if (invalid_id > end) {
                break;
            } else if (invalid_id >= start) {
                invalid_ids_sum += invalid_id;
            }
            sequence++;
        }

    }

    std::cout << "PART ONE: " << invalid_ids_sum << std::endl;
}

void part2(std::vector<std::array<std::string, 2>> ranges)
{
    long invalid_ids_sum = 0;
    for (std::array<std::string, 2> range: ranges) {
        long start = std::stol(range[0]);
        long end = std::stol(range[1]);
        std::set<long> seen;

        for (int repetitions = 2; repetitions <= range[1].length(); repetitions++) {
            long sequence;
            if (range[0].length() % repetitions == 0) {
                sequence = std::stol(range[0].substr(0, range[0].length()/repetitions));
            } else {
                sequence = std::stol("1" + std::string(range[0].length()/repetitions, '0'));
            }

            while (true) {
                std::string invalid_id_str = "";
                for (int i = 0; i < repetitions; i++) {
                    invalid_id_str.append(std::to_string(sequence));
                }

                long invalid_id = std::stol(invalid_id_str);
                if (invalid_id > end) {
                    break;
                } else if (invalid_id >= start && seen.count(invalid_id) == 0) {
                    invalid_ids_sum += invalid_id;
                    seen.insert(invalid_id);
                }

                sequence++;
            }
        }
    }

    std::cout << "PART TWO: " << invalid_ids_sum << std::endl;
}

int main(int argc, char* argv[])
{
    // read input
    std::string input;
    std::ifstream inputFile((argc == 2) ? argv[1] : "input.txt");
    std::getline(inputFile, input);

    // create vector of ranges
    std::string range;
    std::stringstream ss(input);
    std::vector<std::array<std::string, 2>> ranges;
    while(std::getline(ss, range, ',')) {
        int split = range.find('-');
        std::string left = range.substr(0, split);
        std::string right = range.substr(split + 1);
        ranges.push_back({left, right});
    }

    part1(ranges);
    part2(ranges);

    return 0;
}