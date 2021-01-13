#include <execution>
#include <algorithm>

void _My_for_each()
{
  int num[] = {1, 2, 3};
  std::vector a = { 4, 5, 6 };
  std::mutex m;
 
  std::for_each(std::execution::par, std::begin(num), std::end(num),
    [&](auto v) {
	std::lock_guard lock(m);
	a.push_back(v + 1); // OK
  });
}
