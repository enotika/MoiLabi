#pragma once
#include <cassert>
#include <iostream>
#include <vector>

template<class T>
class PriorityQueue {
 public:
  struct Node;
  enum class Priority {
    high = 1,
    medium = 2,
    low = 3
  };

 public:
  PriorityQueue() = default;
  PriorityQueue(const PriorityQueue<T>& queue);
  PriorityQueue(PriorityQueue<T>&& queue) noexcept;
  PriorityQueue<T>& operator=(const PriorityQueue<T>& queue);
  PriorityQueue<T>& operator=(PriorityQueue<T>&& queue) noexcept;
  ~PriorityQueue();

 public:
  [[nodiscard]] int Size() const;
  T GetValueOfHead() const;
  Priority GetPriorityOfHead() const;
  [[nodiscard]] int GetCountOfHighPriority() const;
  [[nodiscard]] int GetCountOfMediumPriority() const;
  [[nodiscard]] int GetCountOfLowPriority() const;
  [[nodiscard]] bool IsEmpty() const;
  void Push(const T& value, Priority priority);
  void Push(T&& value, Priority priority);
  void Pop();
  void Clear();

 private:
  Node* head_{nullptr};
  size_t size_{0};
  int count_of_high_priority{0};
  int count_of_medium_priority{0};
  int count_of_low_priority{0};
};

template<class T>
struct PriorityQueue<T>::Node {
 public:
  T value;
  friend class PriorityQueue;

 private:
  Node* next_{nullptr};
  Priority priority_{3};

  Node(const T& value, Node* next_, Priority priority) :
      value(value), next_(next_), priority_(priority) {}
  Node(T&& value, Node* previous, Node* next_, Priority priority) :
      value(std::move(value)), next_(next_), priority_(priority) {}
  Node() = default;
};

template<class T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue<T>& queue) {
  Node* current = queue.head_;
  while (current != nullptr) {
    Push(current->value, current->priority);
    current = current->next_;
  }
  head_ = queue.head_;
  count_of_high_priority = queue.count_of_high_priority;
  count_of_medium_priority = queue.count_of_medium_priority;
  count_of_low_priority = queue.count_of_low_priority;
  size_ = queue.size_;
}

template<class T>
PriorityQueue<T>::PriorityQueue(PriorityQueue<T>&& queue) noexcept
    : head_(queue.head_),
      count_of_high_priority(queue.count_of_high_priority),
      count_of_medium_priority(queue.count_of_medium_priority),
      count_of_low_priority(queue.count_of_low_priority), size_(queue.size_) {
  queue.head_ = nullptr;
  queue.size_ = 0;
  queue.count_of_high_priority = 0;
  queue.count_of_medium_priority = 0;
  queue.count_of_low_priority = 0;
}

template<class T>
PriorityQueue<T>& PriorityQueue<T>::operator=(
    const PriorityQueue<T>& queue) {
  if (this == &queue) {
    return *this;
  }
  Clear();
  Node* current = queue.head_;
  while (current != nullptr) {
    Push(current->value, current->priority);
    current = current->next_;
  }
  return *this;
}

template<class T>
PriorityQueue<T>& PriorityQueue<T>::operator=(
    PriorityQueue<T>&& queue) noexcept {
  if (this == &queue) {
    return *this;
  }
  Clear();
  size_ = queue.size_;
  head_ = queue.head_;
  count_of_high_priority = queue.count_of_high_priority;
  count_of_medium_priority = queue.count_of_medium_priority;
  count_of_low_priority = queue.count_of_low_priority;
  queue.size_ = 0;
  queue.head_ = nullptr;
  queue.count_of_high_priority = 0;
  queue.count_of_medium_priority = 0;
  queue.count_of_low_priority = 0;
  return *this;
}

template<class T>
int PriorityQueue<T>::Size() const {
  return size_;
}

template<class T>
bool PriorityQueue<T>::IsEmpty() const {
  return size_ == 0;
}

template<class T>
void PriorityQueue<T>::Push(const T& value, Priority priority) {
  if (IsEmpty() || (count_of_high_priority == 0 &&
      (priority == Priority::high || (count_of_medium_priority == 0 && priority == Priority::medium)))) {
    Node* new_element = new Node(value, head_, priority);
    head_ = new_element;
    switch (priority) {
      case Priority::high : {
        ++count_of_high_priority;
        break;
      }
      case Priority::medium : {
        ++count_of_medium_priority;
        break;
      }
      case Priority::low : {
        ++count_of_low_priority;
        break;
      }
    }
    ++size_;
    return;
  }
  Node* new_element = new Node(value, head_, priority);
  switch (priority) {
    case Priority::high : {
      for (int i = 0; i < count_of_high_priority - 1; ++i) {
        new_element->next_ = new_element->next_->next_;
      }
      Node* ptr = new_element->next_->next_;
      new_element->next_->next_ = new_element;
      new_element->next_ = ptr;
      ++count_of_high_priority;
      ++size_;
      break;
    }
    case Priority::medium : {
      for (int i = 0;
           i < count_of_high_priority + count_of_medium_priority - 1; ++i) {
        new_element->next_ = new_element->next_->next_;
      }
      Node* ptr = new_element->next_->next_;
      new_element->next_->next_ = new_element;
      new_element->next_ = ptr;
      ++count_of_medium_priority;
      ++size_;
      break;
    }
    case Priority::low : {
      for (int i = 0; i < size_ - 1; ++i) {
        new_element->next_ = new_element->next_->next_;
      }
      Node* ptr = new_element->next_->next_;
      new_element->next_->next_ = new_element;
      new_element->next_ = ptr;
      ++count_of_low_priority;
      ++size_;
      break;
    }
  }
}

template<class T>
void PriorityQueue<T>::Pop() {
  assert(!IsEmpty());
  --size_;
  switch (head_->priority_) {
    case Priority::high : {
      --count_of_high_priority;
      break;
    }
    case Priority::medium : {
      --count_of_medium_priority;
    }
    case Priority::low : {
      --count_of_low_priority;
    }
  }
  Node* ptr = head_;
  head_ = head_->next_;
  delete ptr;
}

template<class T>
T PriorityQueue<T>::GetValueOfHead() const {
  assert(!IsEmpty());
  return head_->value;
}

template<class T>
typename PriorityQueue<T>::Priority PriorityQueue<T>::GetPriorityOfHead() const {
  assert(!IsEmpty());
  return head_->priority_;
}

template<class T>
void PriorityQueue<T>::Push(T&& value, Priority priority) {
  if (IsEmpty() || (count_of_high_priority == 0 &&
      (priority == Priority::high || (count_of_medium_priority == 0 &&
          (priority == Priority::medium || count_of_low_priority == 0))))) {
    Node* new_element = new Node(std::move(value), nullptr, priority);
    head_ = new_element;
    switch (priority) {
      case Priority::high : {
        ++count_of_high_priority;
        break;
      }
      case Priority::medium : {
        ++count_of_medium_priority;
      }
      case Priority::low : {
        ++count_of_low_priority;
      }
    }
    ++size_;
    return;
  }
  Node* new_element = new Node(std::move(value), head_, priority);
  switch (priority) {
    case Priority::high : {
      for (int i = 0; i < count_of_high_priority - 1; ++i) {
        new_element->next_ = new_element->next_->next_;
      }
      Node* ptr = new_element->next_->next_;
      new_element->next_->next_ = new_element;
      new_element->next_ = ptr;
      ++count_of_high_priority;
      ++size_;
      break;
    }
    case Priority::medium : {
      for (int i = 0; i < count_of_high_priority + count_of_medium_priority - 1;
           ++i) {
        new_element->next_ = new_element->next_->next_;
      }
      Node* ptr = new_element->next_->next_;
      new_element->next_->next_ = new_element;
      new_element->next_ = ptr;
      ++count_of_medium_priority;
      ++size_;
      break;
    }
    case Priority::low : {
      for (int i = 0; i < size_ - 1; ++i) {
        new_element->next_ = new_element->next_->next_;
      }
      Node* ptr = new_element->next_->next_;
      new_element->next_->next_ = new_element;
      new_element->next_ = ptr;
      ++count_of_low_priority;
      ++size_;
      break;
    }
  }
}

template<class T>
PriorityQueue<T>::~PriorityQueue() {
  Clear();
}

template<class T>
void PriorityQueue<T>::Clear() {
  while (size_ > 0) {
    Pop();
  }
}

template<class T>
int PriorityQueue<T>::GetCountOfHighPriority() const {
  return count_of_high_priority;
}

template<class T>
int PriorityQueue<T>::GetCountOfMediumPriority() const {
  return count_of_medium_priority;
}

template<class T>
int PriorityQueue<T>::GetCountOfLowPriority() const {
  return count_of_low_priority;
}

