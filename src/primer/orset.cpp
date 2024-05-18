#include "primer/orset.h"
#include <algorithm>
#include <string>
#include <vector>
#include "common/exception.h"
#include "fmt/format.h"
#include <unordered_set>

namespace bustub { 

template <typename T>
auto ORSet<T>::Contains(const T &elem) const -> bool {
  return std::any_of(element_set_.begin(), element_set_.end(), [&](const auto &element) {
    return !tombstone_set_.count(element) && element.first == elem;
  });
}

template <typename T>
void ORSet<T>::Add(const T &elem, uid_t uid) {
  element_set_.insert({elem, uid});
}

template <typename T>
void ORSet<T>::Remove(const T &elem) {
  for (const auto &element : element_set_) {
    if (element.first == elem) {
      tombstone_set_.insert(element);
    }
  }
}

template <typename T>
void ORSet<T>::Merge(const ORSet<T> &other) {
  for (const auto &elem : other.element_set_) {
    if (!element_set_.count(elem)) {
      element_set_.insert(elem);
    }
  }
  for (const auto &elem : other.tombstone_set_) {
    if (!tombstone_set_.count(elem)) {
      tombstone_set_.insert(elem);
    }
  }
}

template <typename T>
auto ORSet<T>::Elements() const -> std::vector<T> {
  std::vector<T> elements;
  for (const auto &elem : element_set_) {
    if (!tombstone_set_.count(elem)) {
      elements.push_back(elem.first);
    }
  }
  return elements;
}

template <typename T>
auto ORSet<T>::ToString() const -> std::string {
  auto elements = Elements();
  std::sort(elements.begin(), elements.end());
  return fmt::format("{{{}}}", fmt::join(elements, ", "));
}

template class ORSet<int>;
template class ORSet<std::string>;



}  // namespace bustub
