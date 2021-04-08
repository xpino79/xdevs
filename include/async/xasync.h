#ifndef XASYNC_H_
#define XASYNC_H_

namespace my {
  
#include <iostream>
#include <vector>
#include <future>
#include <cstdio>

void _My_for_print(int num) {
  for (int i = 0; i < 100; i++)
    printf("%d번 Thread : %d\n", num, i);
}

void _My_async()
{
  std::vector<std::future<void>> v_async;
  v_async.reserve(2000);

  for (size_t i = 0; i < 2000; i++)
  {
    v_async.emplace_back(std::async(std::launch::async, _My_for_print, i));
  }
  for (size_t i = 0; i < 2000; i++)
  {
    v_async[i].wait();
  }
}

} /* namespace my */

#endif /* XGRID_MANAGER_H_ */
