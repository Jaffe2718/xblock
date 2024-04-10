#include <random>
#include <vector>
#include <unordered_map>


std::vector<int> gen_data(int n);

std::unordered_map<int, int> gen_rule(int n);

void transform(std::vector<int> &data, std::unordered_map<int, int> &rule, int pos);

bool check_win(std::vector<int> &data);

