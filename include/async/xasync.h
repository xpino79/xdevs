#ifndef XASYNC_H_
#define XASYNC_H_

namespace my {
  
#include <iostream>
#include <vector>
#include <future>
#include <cstdio>

// https://www.slideshare.net/SangHeonLee9/ndc2016-tera-modern-c
// https://www.slideshare.net/sangkikim9/ndc2016-64837136
  
void _My_for_print(int num) {
  for (int i = 0; i < 100; i++)
    printf("%d번 Thread : %d\n", num, i);
}

  // 분산작업 예제
void _My_async()
{
  std::vector<std::future<void>> futures;
  futures.reserve(2000);

  // async는 future로 받지 않을 경우 sequential이라 생각하고 순서대로 진행이 된다.
  for (size_t i = 0; i < 2000; i++)
  {
    // launch::async 옵션을 주면 바로 그 자리에서 쓰레드를 생성해서 실행
    // launch::deferred 옵션을 주면, future 의 get 을 하였을 때 비로소 (동기적으로) 실행
    futures.emplace_back(std::async(std::launch::async, _My_for_print, i));
  }
  for (size_t i = 0; i < 2000; i++)
  {
    futures[i].wait();
  }
}

/*
void _My_async_1()
{
  bool retval = true;
  
  // original
  for(auto &elem : jobs)
  {
    if (false == elem.execute())
    {
      retval = false;
    }
  }
  
  // distribution
  std::vector<std::future<bool>> futures;
  for(auto &elem : jobs)
  {
    futures.push_back(
      std::async(
        std::launch::async, 
        [&]
        {
          elem.execute();
        }
      ));
  }
  for(const auto & elem : futures)
  {
    if (false == elem.get())
    {
      retval = false;
    }
  }
}
*/
  
} /* namespace my */

#endif /* XGRID_MANAGER_H_ */
