#pragma once
#include <vector>
#include <queue>

template<typename T> using min_heap = std::priority_queue<T, std::vector<T>, std::greater<>>;
