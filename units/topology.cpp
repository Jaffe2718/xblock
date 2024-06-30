/**
 * @File: units/topology.cpp
 * @Author: Jaffe2718
 * @Create: 2024/4/11
 * @Description: The game logic of the Block Transform game. The matrix data of the current game is stored in an array, and a directed graph is defined in a hash table to define the rules for block substitution. And encapsulated functions transform the game's matrix data based on rules and detect whether the player wins.
 * */

#include "topology.h"

std::unordered_map<int, int> xblock::gen_rule(int n) {
    /**
     * Generate a rule for a n*n game.
     * @param n: the size of the game
     * @return: a rule for the game
     */
    std::unordered_map<int, int> graph;
    std::vector<int> nodes;
    for (int i = 1; i <= n; i++) {    // init nodes = [1, 2, ..., n]
        nodes.push_back(i);
    }
    std::shuffle(nodes.begin(), nodes.end(), std::mt19937(std::random_device()()));
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(2, n);

    // main loop size between [2(include), n(include)]
    int main_loop_size = dist(gen);  //= rand() % (n - 1) + 2;

    for (int i = 0; i < main_loop_size; i++) {
        graph[nodes[i]] = nodes[(i + 1) % main_loop_size];
    }
    for (int i = main_loop_size; i < n; i++) {
        dist = std::uniform_int_distribution<int>(0, main_loop_size - 1);
        graph[nodes[i]] = nodes[dist(gen)];  // nodes[rand() % main_loop_size];
        main_loop_size++;
    }
    return graph;
}


std::vector<int> xblock::gen_data(int n) {
    /**
     * Generate data for a n*n game.
     * @param n: the size of the game
     * @return: a data for the game
     */
    std::vector<int> data;
    for (int i = 1; i <= n; i++) {
        data.push_back(i);
    }
    std::shuffle(data.begin(), data.end(), std::mt19937(std::random_device()()));
    return data;
}


void xblock::transform(std::vector<int> &data, std::unordered_map<int, int> &rule, int pos) {
    /**
     * Transform the data according to the rule.
     * @param data: the data of the game
     * @param rule: the rule of the game
     * @param pos: the position of the clicked number
     * @return: the transformed data
     */
    std::swap(data[pos], data[rule[pos + 1] - 1]);
}

bool xblock::check_win(std::vector<int> &data) {
    /**
     * data = [1, 2, 3, 4, 5, 6, 7, 8, 9 ... n] -> win
     * Check if the game is win.
     * @param data: the data of the game
     * @return: if the game is win
     */
    for (int i = 0; i < data.size(); i++) {
        if (data[i] != i + 1) {
            return false;
        }
    }
    return true;
}