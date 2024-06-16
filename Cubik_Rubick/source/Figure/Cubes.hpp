#pragma once

#include "Cube.hpp"
#include <algorithm>

class Cubes {
public:
  Cubes();
  ~Cubes();

  void Draw();

  // Move

  // Y
  void MoveUpY(bool Direction);
  void MoveDownY(bool Direction);

  // X
  void MoveUpX(bool Direction);
  void MoveDownX(bool Direction);

  // Z
  void MoveUpZ(bool Direction);
  void MoveDownZ(bool Direction);

  void RandowMove();

  void AutomaticMove();

  bool SaveCube(const char *Filename);
  bool LoadCube(const char *Filename);

  Cube **ACubes;

private:
  void m_Swap(Cube *&A, Cube *&B);

  bool m_IsCross();
  bool m_IsTwoSite();
  bool m_IsWhiteSide();

  bool m_IsWhite(size_t index);
  color m_GiveColor(size_t index);
};
