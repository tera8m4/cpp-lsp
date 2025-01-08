#pragma once
#include <queue>
#include <condition_variable>
#include <mutex>
#include <type_traits>

template<typename T>
class thread_safe_queue {
public:
  explicit thread_safe_queue(std::size_t in_max_capacity) : max_capacity{in_max_capacity} {}
  thread_safe_queue(const thread_safe_queue&) = delete;
  thread_safe_queue& operator=(const thread_safe_queue&) = delete;

  template<typename U> requires std::is_same_v<std::decay_t<U>, T>
  void enqueue(U&& item)
  {
    std::unique_lock<std::mutex> lock(mutex);
    cv_not_full.wait(lock, [&] { return queue.size() < max_capacity; });
    queue.push(std::forward<U>(item));
    cv_not_empty.notify_one();
  }

  T dequeue()
  {
    std::unique_lock<std::mutex> lock(mutex);
    cv_not_empty.wait(lock, [&] { return !queue.empty(); });
    T item = std::move(queue.front());
    queue.pop();
    cv_not_full.notify_one();

    return item;
  }

  std::size_t size() const
  {
    std::lock_guard<std::mutex> lock(mutex);
    return queue.size();
  }

  bool is_empty() const {
    return size() == 0;
  }

private:
  mutable std::mutex mutex;
  std::condition_variable cv_not_empty;
  std::condition_variable cv_not_full;
  std::queue<T> queue;
  std::size_t max_capacity = 1;
};
