#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t pool_size) {
  for (size_t i = 0; i < pool_size; ++i) {
    pool_.emplace_back(std::thread(std::bind(&ThreadPool::RunTask, this)));
  }
}

void ThreadPool::RunTask() {
  while (true) {
    std::function<void()> task;
    {
      std::unique_lock<std::mutex> locker(mutex_);
      while (!task_ready_ && !stop_all_) {
        notifier_.wait(locker);
      }
      if (stop_all_) {
        return;
      }
      if (!queue_.empty()) {
        task = queue_.front();
        queue_.pop();
      }
      task_ready_ = false;
    }
    task();
  }
}

ThreadPool::~ThreadPool() {
  stop_all_ = true;
  notifier_.notify_all();
  for (std::thread& thread : pool_) {
    thread.join();
  }
}