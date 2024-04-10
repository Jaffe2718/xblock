#pragma once
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <algorithm>
#include <random>
#include <vector>
#include <unordered_map>

#include "graph.hpp"

std::unordered_map<int, int> gen_rule(int n) {
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
    // main loop size between [2, n]
    int main_loop_size = rand() % (n - 1) + 2;
    for (int i = 0; i < main_loop_size; i++) {
        graph[nodes[i]] = nodes[(i + 1) % main_loop_size];
    }
    for (int i = main_loop_size; i < n; i++) {
        graph[nodes[i]] = nodes[rand() % main_loop_size];
        main_loop_size++;
    }
    return graph;
}


std::vector<int> gen_data(int n) {
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


void transform(std::vector<int> &data, std::unordered_map<int, int> &rule, int pos) {
    /**
     * Transform the data according to the rule.
     * @param data: the data of the game
     * @param rule: the rule of the game
     * @param pos: the position of the clicked number
     * @return: the transformed data
     */
    int m = data[pos];
    int n = data[rule[pos + 1] - 1];
    std::swap(data[pos], data[rule[pos + 1] - 1]);
}

bool check_win(std::vector<int> &data) {
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

#endif