/**
 * @File: units/topology.h
 * @Author: Jaffe2718
 * @Create: 2024/4/11
 * @Description: The game logic of the Block Transform game. The matrix data of the current game is stored in an array, and a directed graph is defined in a hash table to define the rules for block substitution. And encapsulated functions transform the game's matrix data based on rules and detect whether the player wins.
 * */

#ifndef XBLOCK_TOPOLOGY_H
#define XBLOCK_TOPOLOGY_H

#include <bits/stdc++.h>

namespace xblock {

    /**
     * @brief Generate a random matrix data.
     * @param n The size of the matrix.
     * @return A random matrix data.
     * */
    std::vector<int> gen_data(int n);

    /**
     * @brief Generate a random rule for the matrix data.
     * @param n The size of the matrix.
     * @return A random rule for the matrix data.
     * */
    std::unordered_map<int, int> gen_rule(int n);

    /**
     * @brief Transform the matrix data based on the rule.
     * @param data The matrix data.
     * @param rule The rule for the matrix data.
     * @param pos The position of the block to be transformed.
     * */
    void transform(std::vector<int> &data, std::unordered_map<int, int> &rule, int pos);

    /**
     * @brief Check whether the player wins.
     * @param data The matrix data.
     * @return Whether the player wins.
     * */
    bool check_win(std::vector<int> &data);
}

#endif //XBLOCK_TOPOLOGY_H