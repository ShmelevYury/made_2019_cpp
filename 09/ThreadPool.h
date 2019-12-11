#pragma once

#include <cstddef>
#include <thread>
#include <vector>
#include <functional>
#include <future>
#include <queue>

class Functor;

class ThreadPool {
 public:
  explicit ThreadPool(size_t pool_size);

  template <class Func, class... ArgsT>
  auto exec(Func func, ArgsT... args);

  ~ThreadPool();

 private:
  void RunTask();

  std::vector<std::thread> pool_;
  std::queue<std::function<void ()>> queue_;
  std::condition_variable notifier_;
  bool task_ready_ = false;
  bool stop_all_ = false;

  std::mutex mutex_;
};

template <class Func, class... ArgsT>
auto ThreadPool::exec(Func func, ArgsT... args) {
  using return_type = decltype(func(args...));
  auto task = std::make_shared<std::packaged_task<return_type()> >(
      std::bind(std::move(func), std::move(args)...));
  auto future = task->get_future();
  {
    std::unique_lock<std::mutex> locker(mutex_);
    queue_.emplace([task]() { (*task)(); });
    task_ready_ = true;
  }
  notifier_.notify_one();

  return future;
}
