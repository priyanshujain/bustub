#pragma once

#include <string>
#include <utility>
#include <vector>
#include <unordered_set>
#include <functional>

namespace bustub {

/** @brief Unique ID type. */
using uid_t = int64_t;

/** @brief The observed remove set datatype. */
template <typename T>
class ORSet {
 public:
  ORSet() = default;

  /**
   * @brief Checks if an element is in the set.
   *
   * @param elem the element to check
   * @return true if the element is in the set, and false otherwise.
   */
  auto Contains(const T &elem) const -> bool;

  /**
   * @brief Adds an element to the set.
   *
   * @param elem the element to add
   * @param uid unique token associated with the add operation.
   */
  void Add(const T &elem, uid_t uid);

  /**
   * @brief Removes an element from the set if it exists.
   *
   * @param elem the element to remove.
   */
  void Remove(const T &elem);

  /**
   * @brief Merge changes from another ORSet.
   *
   * @param other another ORSet
   */
  void Merge(const ORSet<T> &other);

  /**
   * @brief Gets all the elements in the set.
   *
   * @return all the elements in the set.
   */
  auto Elements() const -> std::vector<T>;

  /**
   * @brief Gets a string representation of the set.
   *
   * @return a string representation of the set.
   */
  auto ToString() const -> std::string;

 private:
  // Custom hash function for std::pair
  struct PairHash {
      template <class T1, class T2>
      auto operator()(const std::pair<T1, T2>& p) const -> std::size_t {
          auto hash1 = std::hash<T1>{}(p.first);
          auto hash2 = std::hash<T2>{}(p.second);
          return hash1 ^ (hash2 << 1); // or use boost::hash_combine
      }
  };

  // Define equality comparison for std::pair
  struct PairEqual {
      template <class T1, class T2>
      auto operator()(const std::pair<T1, T2>& p1, const std::pair<T1, T2>& p2) const -> bool {
          return p1.first == p2.first && p1.second == p2.second;
      }
  };

  std::unordered_set<std::pair<T, uid_t>, PairHash, PairEqual> element_set_;
  std::unordered_set<std::pair<T, uid_t>, PairHash, PairEqual> tombstone_set_;

  
};

}  // namespace bustub
