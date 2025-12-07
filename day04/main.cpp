#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void part1(std::vector<std::string> grid)
{
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1},  {1, 0},  {1, 1}
    };

    int accessible_rolls = 0;
    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid.size(); x++) {
            if (grid[y][x] != '@') {
                continue;
            }

            int neighboring_rolls = 0;
            for (int i = 0; i < 8; i++) {
                int nx = x + directions[i][0];
                int ny = y + directions[i][1];
                if (nx != -1 && nx != grid[0].size() && ny != -1 && ny != grid.size() && grid[ny][nx] == '@') {
                    neighboring_rolls++;
                }
            }

            if (neighboring_rolls < 4) {
                accessible_rolls++;
            }
        }
    }
    
    std::cout << "PART ONE: " << accessible_rolls << std::endl;
}

struct Roll {
    int x;
    int y;
};

void part2(std::vector<std::string> grid)
{
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1},  {1, 0},  {1, 1}
    };

    int rolls_removed = 0;
    std::vector<Roll> removable_rolls;
    do {
        removable_rolls.clear();

        for (int y = 0; y < grid.size(); y++) {
            for (int x = 0; x < grid.size(); x++) {
                if (grid[y][x] != '@') {
                    continue;
                }

                int neighboring_rolls = 0;
                for (int i = 0; i < 8; i++) {
                    int nx = x + directions[i][0];
                    int ny = y + directions[i][1];
                    if (nx != -1 && nx != grid[0].size() && ny != -1 && ny != grid.size() && grid[ny][nx] == '@') {
                        neighboring_rolls++;
                    }
                }

                if (neighboring_rolls < 4) {
                    removable_rolls.push_back(Roll{x, y});
                }
            }
        }

        rolls_removed += removable_rolls.size();
        for (Roll roll: removable_rolls) {
            grid[roll.y][roll.x] = '.';
        }
    } while (removable_rolls.size() > 0);

    std::cout << "PART TWO: " << rolls_removed << std::endl;
}

int main(int argc, char* argv[])
{
    std::vector<std::string> grid;

    std::string row;
    std::ifstream inputFile((argc == 2) ? argv[1] : "input.txt");
    while (std::getline(inputFile, row)) {
        if (row.back() == '\r') {
            row.pop_back();
        }
        
        grid.push_back(row);
    }

    part1(grid);
    part2(grid);

    return 0;
}
