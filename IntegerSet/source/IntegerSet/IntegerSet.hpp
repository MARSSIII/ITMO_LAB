#pragma once

#include <list>

class IntegerSet {
public:
  explicit IntegerSet(size_t MaxSize)
      : m_Capacity(MaxSize), m_SizeSet(0), m_root(nullptr) {}

  ~IntegerSet() { m_deleteSet(this->m_root); }

  IntegerSet(const IntegerSet &other) {

    if (this == &other) {
      return;
    }

    this->m_deleteSet(m_root);

    if (!other.m_root) {
      this->m_root = nullptr;
      return;
    }

    this->m_root = new Node(other.m_root->Data);

    this->m_root->left = m_copyNode(other.m_root->left);
    this->m_root->right = m_copyNode(other.m_root->right);

    this->m_SizeSet = other.m_SizeSet;
    this->m_Capacity = other.m_Capacity;
  }

  IntegerSet &operator=(const IntegerSet &other);

  IntegerSet &operator=(IntegerSet &&other);

  size_t GetMaxSize() const;

  size_t GetRealSize() const;

  size_t GetCapacitySet() const;

  std::list<int> GetElementOfSet() const;

  // Print all elements of a set
  void PrintSet();

  // Adding an element to a set
  bool Insert(int value);

  // Changes Size in Set
  void ChangeSize(size_t PlusSize);

  // Changes Capacity in Set
  void ChangeCapacity(size_t PlusCap);

  // Removing an element from a set`
  void Delete(int value);

  // Finding an element in a set
  bool FindValue(int value);

  // Empty or not
  bool IsEmpty();

private:
  struct Node {
    int Data;
    int Height;

    Node *left;
    Node *right;

    explicit Node(int value)
        : Data(value), Height(1), left(nullptr), right(nullptr) {}

    Node(const Node &other) = default;

    ~Node() {
      left = nullptr;
      right = nullptr;

      delete left;
      delete right;
    }
  };

  size_t m_Capacity;
  size_t m_SizeSet;
  Node *m_root;

  Node *m_FindMin(Node *Current);

  Node *m_copyNode(Node *&Current);

  void m_deleteSet(Node *&Current);

  void m_GetElement(std::list<int> &Vi, Node *Current) const;

  void m_ChangeSize(size_t PlusSize);

  void m_ChangeCapacity(size_t PlusSize);

  void m_InOrder(Node *Current, int MaxValue);

  void m_Delete(int value, Node *&Current);

  void m_Insert(int value, Node *&Current);

  bool m_FindValue(int value, Node *Current);

  void m_Balance(Node *&Current);

  void m_RotateLeft(Node *&Current);

  void m_RotateRight(Node *&Current);

  int m_Height(Node *&Current);

  int m_BalanceFactor(Node *Current);

  void m_FixHeight(Node *&Current);

  Node *&m_FindMax(Node *&Current);
};
