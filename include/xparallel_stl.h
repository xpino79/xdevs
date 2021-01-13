/* rhel8 gcc10 -std=c++17 -lstdc++ */

#include <execution>
#include <algorithm>
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

}
