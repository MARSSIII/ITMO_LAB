#include "IntegerSet.hpp"

#include <iostream>
#include <list>

IntegerSet &IntegerSet::operator=(const IntegerSet &other) {

  if (this == &other) {
    return *this;
  }

  this->m_deleteSet(m_root);

  if (!other.m_root) {
    this->m_root = nullptr;
    return *this;
  }

  this->m_root = new Node(other.m_root->Data);

  this->m_root->left = m_copyNode(other.m_root->left);
  this->m_root->right = m_copyNode(other.m_root->right);

  this->m_SizeSet = other.m_SizeSet;
  this->m_Capacity = other.m_Capacity;

  return *this;
}

IntegerSet &IntegerSet::operator=(IntegerSet &&other) {
  std::swap(m_root, other.m_root);
  std::swap(m_Capacity, other.m_Capacity);
  std::swap(m_SizeSet, other.m_SizeSet);

  return *this;
}

IntegerSet::Node *IntegerSet::m_copyNode(Node *&Current) {
  if (!Current) {
    return nullptr;
  }

  Node *copyCurrent = new Node(Current->Data);

  copyCurrent->left = m_copyNode(Current->left);
  copyCurrent->right = m_copyNode(Current->right);

  return copyCurrent;
}

void IntegerSet::m_deleteSet(Node *&Current) {

  if (!Current) {
    return;
  }

  this->m_deleteSet(Current->left);
  this->m_deleteSet(Current->right);
}

void IntegerSet::PrintSet() {

  if (!(this->m_root)) {
    std::cout << "empty";
    return;
  }

  int MaxValue = this->m_FindMax(m_root)->Data;

  this->m_InOrder(this->m_root, MaxValue);
}

void IntegerSet::m_InOrder(Node *Current, int MaxValue) {

  if (!Current) {
    return;
  }

  this->m_InOrder(Current->left, MaxValue);

  if (MaxValue == Current->Data) {
    std::cout << Current->Data;
  } else {
    std::cout << Current->Data << ", ";
  }

  this->m_InOrder(Current->right, MaxValue);
}

bool IntegerSet::Insert(int value) {

  if (this->m_SizeSet == this->m_Capacity) {
    return false;
  }

  this->m_Insert(value, this->m_root);

  return true;
}

void IntegerSet::m_Insert(int value, Node *&Current) {

  if (!Current) {
    Current = new Node(value);
    ++m_SizeSet;
    return;
  }

  else if (value == Current->Data) {
    return;
  }

  else if (value < Current->Data) {
    this->m_Insert(value, Current->left);
  }

  else if (value > Current->Data) {
    this->m_Insert(value, Current->right);
  }

  this->m_Balance(Current);
}

void IntegerSet::Delete(int value) {

  if (!m_SizeSet) {
    return;
  }

  this->m_Delete(value, this->m_root);
}

void IntegerSet::m_Delete(int value, Node *&Current) {

  if (!Current) {
    return;
  }

  Node *trash = nullptr;

  if (value < Current->Data) {
    this->m_Delete(value, Current->left);
  }

  else if (value > Current->Data) {
    this->m_Delete(value, Current->right);
  }

  else {

    if (!(Current->left) && !(Current->right)) {
      trash = Current;
      Current = nullptr;
    }

    else if (Current->left && !(Current->right)) {
      trash = Current;
      Current = Current->left;
    }

    else if (!(Current->left) && Current->right) {
      trash = Current;
      Current = Current->right;
    }

    else {
      Node *MinNode = this->m_FindMin(Current->right);
      Current->Data = MinNode->Data;
      this->m_Delete(MinNode->Data, Current->right);
    }

    if (trash) {
      --m_SizeSet;
      delete trash;
    }

    this->m_Balance(Current);
    return;
  }

  this->m_Balance(Current);
}

IntegerSet::Node *IntegerSet::m_FindMin(Node *Current) {

  if (!Current->left) {
    return Current;
  } else {
    return (this->m_FindMin(Current->left));
  }
}

IntegerSet::Node *&IntegerSet::m_FindMax(Node *&Current) {

  if (!Current->right) {
    return Current;
  } else {
    return (this->m_FindMax(Current->right));
  }
}

bool IntegerSet::FindValue(int value) {
  return (this->m_FindValue(value, this->m_root));
}

bool IntegerSet::m_FindValue(int value, Node *Current) {

  if (!Current) {
    return false;
  }

  if (value == Current->Data) {
    return true;
  }

  if (value < Current->Data) {
    return (this->m_FindValue(value, Current->left));
  }

  else {
    return (this->m_FindValue(value, Current->right));
  }
}

bool IntegerSet::IsEmpty() { return (this->m_root); }

void IntegerSet::m_Balance(Node *&Current) {

  if (!Current) {
    return;
  }

  this->m_FixHeight(Current);

  int BalanceFactor = (this->m_BalanceFactor(Current));

  if (BalanceFactor == 2) {

    if ((this->m_BalanceFactor(Current->right)) < 0) {
      this->m_RotateRight(Current->right);
    }

    this->m_RotateLeft(Current);
  }

  else if (BalanceFactor == -2) {

    if ((this->m_BalanceFactor(Current->left)) > 0) {
      this->m_RotateLeft(Current->left);
    }

    this->m_RotateRight(Current);
  }
}

int IntegerSet::m_BalanceFactor(Node *Current) {

  if (!Current) {
    return 0;
  }

  return (this->m_Height(Current->right)) - (this->m_Height(Current->left));
}

void IntegerSet::m_FixHeight(Node *&Current) {

  int HeightLeft = this->m_Height(Current->left);
  int HeightRight = this->m_Height(Current->right);

  Current->Height = (HeightLeft > HeightRight ? HeightLeft : HeightRight) + 1;
}

int IntegerSet::m_Height(Node *&Current) {
  return (Current ? Current->Height : 0);
}

void IntegerSet::m_RotateRight(Node *&Current) {

  Node *tmp = Current->left;
  Current->left = tmp->right;
  tmp->right = Current;

  this->m_FixHeight(Current);
  this->m_FixHeight(tmp);

  Current = tmp;
}

void IntegerSet::m_RotateLeft(Node *&Current) {

  Node *tmp = Current->right;
  Current->right = tmp->left;
  tmp->left = Current;

  this->m_FixHeight(Current);
  this->m_FixHeight(tmp);

  Current = tmp;
}

size_t IntegerSet::GetMaxSize() const { return m_Capacity; }

size_t IntegerSet::GetRealSize() const { return m_SizeSet; }

size_t IntegerSet::GetCapacitySet() const { return m_Capacity; }

std::list<int> IntegerSet::GetElementOfSet() const {
  std::list<int> Vi;

  this->m_GetElement(Vi, (this->m_root));

  return Vi;
}

void IntegerSet::m_GetElement(std::list<int> &Vi, Node *Current) const {

  if (!Current) {
    return;
  }

  this->m_GetElement(Vi, Current->left);
  Vi.push_back(Current->Data);
  this->m_GetElement(Vi, Current->right);
}

void IntegerSet::ChangeSize(size_t PlusSize) {
  this->m_ChangeSize(PlusSize);
  if (this->m_Capacity < this->m_SizeSet) {
    m_ChangeCapacity(m_SizeSet - m_Capacity);
  }
}

void IntegerSet::ChangeCapacity(size_t PlusCap) { m_ChangeCapacity(PlusCap); }

void IntegerSet::m_ChangeCapacity(size_t PlusSize) { m_Capacity += PlusSize; }

void IntegerSet::m_ChangeSize(size_t PlusSize) { m_SizeSet += PlusSize; }
