#ifndef SCOPEDPOINTER_H
#define SCOPEDPOINTER_H

#include <utility>

template <typename T>
class DeepCopyScopedPointer {
  T* pointer;

 public:
  DeepCopyScopedPointer(T* raw) : pointer(raw) {}

  DeepCopyScopedPointer(const DeepCopyScopedPointer& other)
      : pointer(other.pointer ? new T(*other.pointer) : nullptr) {}

  DeepCopyScopedPointer(DeepCopyScopedPointer&& other)
      : pointer(other.pointer) {
    other.pointer = nullptr;
  }

  DeepCopyScopedPointer& operator=(DeepCopyScopedPointer other) {
    std::swap(pointer, other.pointer);
    return *this;
  }

  T& operator*() { return *pointer; }
  const T& operator*() const { return *pointer; }

  T* operator->() { return pointer; }
  const T* operator->() const { return pointer; }

  ~DeepCopyScopedPointer() { delete pointer; }
};

template <typename T>
class MoveScopedPointer {
  T* pointer;

 public:
  MoveScopedPointer(T* raw) : pointer(raw) {}

  MoveScopedPointer(const MoveScopedPointer& other) = delete;

  MoveScopedPointer(MoveScopedPointer&& other) : pointer(other.pointer) {
    other.pointer = nullptr;
  }

  MoveScopedPointer& operator=(MoveScopedPointer other) {
    std::swap(pointer, other.pointer);
    return *this;
  }

  T& operator*() { return *pointer; }
  const T& operator*() const { return *pointer; }

  T* operator->() { return pointer; }
  const T* operator->() const { return pointer; }

  ~MoveScopedPointer() { delete pointer; }
};

#endif