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

  // async는 future로 받지 않을 경우 sequential이라 생각하고 순서대로 진행이 된다.
  for (size_t i = 0; i < 2000; i++)
  {
    // launch::async 옵션을 주면 바로 그 자리에서 쓰레드를 생성해서 실행
    // launch::deferred 옵션을 주면, future 의 get 을 하였을 때 비로소 (동기적으로) 실행
    v_async.emplace_back(std::async(std::launch::async, _My_for_print, i));
  }
  for (size_t i = 0; i < 2000; i++)
  {
    v_async[i].wait();
  }
}

} /* namespace my */

#endif /* XGRID_MANAGER_H_ */
