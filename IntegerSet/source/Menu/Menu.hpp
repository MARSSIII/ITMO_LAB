#pragma once

#include "../IntegerSet/IntegerSet.hpp"

#include <string>
#include <vector>

class Menu {
public:
  Menu() = default;

  Menu(const Menu &other) = delete;

  void initDialog(size_t NumberSet);

  size_t GetNumberOfSet() const;

  void PrintAllSet();

  void PrintAllSet(size_t number);

  void Print(size_t NumberSet);

  void CreateNewSet(size_t SizeSet);

  void DeleteSet(size_t NumberSet);

  bool Insert(int value, size_t NumberSet);

  void Erase(int value, size_t NumberSet);

  bool Contains(int value, size_t NumberSet);

  void Union(const std::vector<int> &NumebersSets);

  void Intersection(const std::vector<int> &NumebersSets);

  void Difference(const std::vector<int> &NumebersSets);

private:
  enum COMMAND {
    EXIT,
    INSERT,
    ERASE,
    FIND,
    UNION,
    INTERSECTION,
    DEFFERENCE,
    SHOW
  };

  size_t m_NumberOfSet = 0;

  std::vector<IntegerSet> m_VSet;

  static std::string m_lower(std::string str);

  static void m_Separation();
};
