/* dnf install gcc-toolset-10 */
/* gcc -std=c++17 -lstdc++ */

#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>
#include <execution>
#include <iostream>
#include <chrono>
#include <mutex>

void _My_parallel_stl_for_each()
{
  int sum = 0;
  std::vector<int> v = { 1, 2, 3 };
  std::mutex m;
 
  std::for_each(std::execution::par, std::begin(v), std::end(v),
    [&](auto i) {
	std::lock_guard lock(m);
	sum += i;
  });
	
  std::map<int, int> m{{1, 2}, {3, 4}, {5, 6}, {7, 8}};
  std::for_each(std::execution::par, std::begin(m), std::end(m), [](const auto &pair) {
    std::cout << "first " << pair.first << " second " << pair.second << std::endl;
  });

}
