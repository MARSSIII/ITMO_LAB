#include "Cubes.hpp"

#define Icolor1(index) index + 3
#define Icolor2(index) index + 4
#define Icolor3(index) index + 5

#include <fstream>
#include <iostream>
#include <ostream>

#define log(x)

Cubes::Cubes() {
  ACubes = new Cube *[27];

  for (int index = 0; index < 27; ++index) {
    ACubes[index] = new Cube();
  }

  // ACubes[0] - главный куб (в центре)

  //   F
  // A B C D
  //   E

  // X
  // Y Z
  //
  // 0 Level    1 Level     2 Level
  //
  // 1 2 3      11 22 17     10 15 16
  // 4 5 6      23 $$ 25     12 26 18
  // 7 8 9      14 24 21     13 19 20

  //
  //        10 15 16
  //        11 W 17
  //        1 2 3
  //
  // 10 11 1  1 2 3  3 17 16  16 15 10
  // 12 O 4   4 G 6  6 R 18   18 B 12
  // 13 14 7  7 8 9  9 21 20  20 19 13
  //
  //        7 8 9
  //        14 Y 21
  //        13 19 20

  ACubes[1]->SetColor(color::WHITE, site::F);
  ACubes[1]->SetColor(color::ORANGE, site::A);
  ACubes[1]->SetColor(color::GREEN, site::B);

  ACubes[1]->CountColor = 3;

  ACubes[1]->ShiftXYZ(2.2, -2.2, -2.2);

  ACubes[2]->SetColor(color::WHITE, site::F);
  ACubes[2]->SetColor(color::GREEN, site::B);

  ACubes[2]->CountColor = 2;

  ACubes[2]->ShiftXYZ(2.2, -2.2, 0.);

  ACubes[3]->SetColor(color::WHITE, site::F);
  ACubes[3]->SetColor(color::RED, site::C);
  ACubes[3]->SetColor(color::GREEN, site::B);
  ACubes[3]->CountColor = 3;

  ACubes[3]->ShiftXYZ(2.2, -2.2, 2.2);

  ACubes[4]->SetColor(color::ORANGE, site::A);
  ACubes[4]->SetColor(color::GREEN, site::B);
  ACubes[4]->CountColor = 2;

  ACubes[4]->ShiftXYZ(0., -2.2, -2.2);

  ACubes[5]->SetColor(color::GREEN, site::B);
  ACubes[5]->CountColor = 1;

  ACubes[5]->ShiftXYZ(0., -2.2, 0.);

  ACubes[6]->SetColor(color::GREEN, site::B);
  ACubes[6]->SetColor(color::RED, site::C);
  ACubes[6]->CountColor = 2;

  ACubes[6]->ShiftXYZ(0., -2.2, 2.2);

  ACubes[7]->SetColor(color::GREEN, site::B);
  ACubes[7]->SetColor(color::ORANGE, site::A);
  ACubes[7]->SetColor(color::YELLOW, site::E);
  ACubes[7]->CountColor = 3;

  ACubes[7]->ShiftXYZ(-2.2, -2.2, -2.2);

  ACubes[8]->SetColor(color::GREEN, site::B);
  ACubes[8]->SetColor(color::YELLOW, site::E);
  ACubes[8]->CountColor = 2;

  ACubes[8]->ShiftXYZ(-2.2, -2.2, 0.);

  ACubes[9]->SetColor(color::GREEN, site::B);
  ACubes[9]->SetColor(color::YELLOW, site::E);
  ACubes[9]->SetColor(color::RED, site::C);
  ACubes[9]->CountColor = 3;

  ACubes[9]->ShiftXYZ(-2.2, -2.2, 2.2);

  ACubes[10]->SetColor(color::ORANGE, site::A);
  ACubes[10]->SetColor(color::WHITE, site::F);
  ACubes[10]->SetColor(color::BLUE, site::D);
  ACubes[10]->CountColor = 3;

  ACubes[10]->ShiftXYZ(2.2, 2.2, -2.2);

  ACubes[11]->SetColor(color::ORANGE, site::A);
  ACubes[11]->SetColor(color::WHITE, site::F);
  ACubes[11]->CountColor = 2;

  ACubes[11]->ShiftXYZ(2.2, 0., -2.2);

  ACubes[12]->SetColor(color::ORANGE, site::A);
  ACubes[12]->SetColor(color::BLUE, site::D);
  ACubes[12]->CountColor = 2;

  ACubes[12]->ShiftXYZ(0., 2.2, -2.2);

  ACubes[13]->SetColor(color::ORANGE, site::A);
  ACubes[13]->SetColor(color::BLUE, site::D);
  ACubes[13]->SetColor(color::YELLOW, site::E);
  ACubes[13]->CountColor = 3;

  ACubes[13]->ShiftXYZ(-2.2, 2.2, -2.2);

  ACubes[14]->SetColor(color::ORANGE, site::A);
  ACubes[14]->SetColor(color::YELLOW, site::E);
  ACubes[14]->CountColor = 2;

  ACubes[14]->ShiftXYZ(-2.2, 0., -2.2);

  ACubes[15]->SetColor(color::WHITE, site::F);
  ACubes[15]->SetColor(color::BLUE, site::D);
  ACubes[15]->CountColor = 2;

  ACubes[15]->ShiftXYZ(2.2, 2.2, 0.);

  ACubes[16]->SetColor(color::WHITE, site::F);
  ACubes[16]->SetColor(color::RED, site::C);
  ACubes[16]->SetColor(color::BLUE, site::D);
  ACubes[16]->CountColor = 3;

  ACubes[16]->ShiftXYZ(2.2, 2.2, 2.2);

  ACubes[17]->SetColor(color::WHITE, site::F);
  ACubes[17]->SetColor(color::RED, site::C);
  ACubes[17]->CountColor = 2;

  ACubes[17]->ShiftXYZ(2.2, 0., 2.2);

  ACubes[18]->SetColor(color::RED, site::C);
  ACubes[18]->SetColor(color::BLUE, site::D);
  ACubes[18]->CountColor = 2;

  ACubes[18]->ShiftXYZ(0., 2.2, 2.2);

  ACubes[19]->SetColor(color::BLUE, site::D);
  ACubes[19]->SetColor(color::YELLOW, site::E);
  ACubes[19]->CountColor = 2;

  ACubes[19]->ShiftXYZ(-2.2, 2.2, 0.);

  ACubes[20]->SetColor(color::RED, site::C);
  ACubes[20]->SetColor(color::BLUE, site::D);
  ACubes[20]->SetColor(color::YELLOW, site::E);

  ACubes[20]->CountColor = 3;

  ACubes[20]->ShiftXYZ(-2.2, 2.2, 2.2);

  ACubes[21]->SetColor(color::RED, site::C);
  ACubes[21]->SetColor(color::YELLOW, site::E);

  ACubes[21]->CountColor = 2;

  ACubes[21]->ShiftXYZ(-2.2, 0., 2.2);

  ACubes[22]->SetColor(color::WHITE, site::F);
  ACubes[22]->CountColor = 1;

  ACubes[22]->ShiftXYZ(2.2, 0., 0.);

  ACubes[23]->SetColor(color::ORANGE, site::A);
  ACubes[23]->CountColor = 1;

  ACubes[23]->ShiftXYZ(0., 0., -2.2);

  ACubes[24]->SetColor(color::YELLOW, site::E);
  ACubes[24]->CountColor = 1;

  ACubes[24]->ShiftXYZ(-2.2, 0., 0.);

  ACubes[25]->SetColor(color::RED, site::C);
  ACubes[25]->CountColor = 1;

  ACubes[25]->ShiftXYZ(0., 0., 2.2);

  ACubes[26]->SetColor(color::BLUE, site::D);
  ACubes[26]->CountColor = 1;

  ACubes[26]->ShiftXYZ(0., 2.2, 0.);
}

Cubes::~Cubes() {
  for (int index = 0; index < 27; ++index) {
    delete ACubes[index];
  }

  delete[] ACubes;
}

void Cubes::Draw() {
  for (int index = 0; index < 27; ++index) {
    ACubes[index]->draw();
  }
}

void Cubes::MoveUpX(bool Direction) {

  if (Direction) {

    m_Swap(ACubes[12], ACubes[15]);
    m_Swap(ACubes[12], ACubes[19]);
    m_Swap(ACubes[19], ACubes[18]);

    m_Swap(ACubes[10], ACubes[16]);
    m_Swap(ACubes[13], ACubes[10]);
    m_Swap(ACubes[13], ACubes[20]);

  } else {

    m_Swap(ACubes[12], ACubes[19]);
    m_Swap(ACubes[12], ACubes[15]);
    m_Swap(ACubes[15], ACubes[18]);

    m_Swap(ACubes[10], ACubes[13]);
    m_Swap(ACubes[10], ACubes[16]);
    m_Swap(ACubes[16], ACubes[20]);
  }

  ACubes[10]->RotateColorX(Direction);
  ACubes[15]->RotateColorX(Direction);
  ACubes[16]->RotateColorX(Direction);
  ACubes[18]->RotateColorX(Direction);
  ACubes[20]->RotateColorX(Direction);
  ACubes[19]->RotateColorX(Direction);
  ACubes[13]->RotateColorX(Direction);
  ACubes[12]->RotateColorX(Direction);

  ACubes[10]->m_UpdateCube();
  ACubes[15]->m_UpdateCube();
  ACubes[16]->m_UpdateCube();
  ACubes[12]->m_UpdateCube();
  ACubes[26]->m_UpdateCube();
  ACubes[18]->m_UpdateCube();
  ACubes[13]->m_UpdateCube();
  ACubes[19]->m_UpdateCube();
  ACubes[20]->m_UpdateCube();
}

void Cubes::MoveDownX(bool Direction) {

  if (Direction) {

    m_Swap(ACubes[4], ACubes[2]);
    m_Swap(ACubes[4], ACubes[8]);
    m_Swap(ACubes[8], ACubes[6]);

    m_Swap(ACubes[1], ACubes[3]);
    m_Swap(ACubes[1], ACubes[7]);
    m_Swap(ACubes[7], ACubes[9]);

  } else {

    m_Swap(ACubes[4], ACubes[8]);
    m_Swap(ACubes[4], ACubes[2]);
    m_Swap(ACubes[2], ACubes[6]);

    m_Swap(ACubes[7], ACubes[9]);
    m_Swap(ACubes[7], ACubes[1]);
    m_Swap(ACubes[1], ACubes[3]);
  }

  ACubes[1]->RotateColorX(Direction);
  ACubes[2]->RotateColorX(Direction);
  ACubes[3]->RotateColorX(Direction);
  ACubes[4]->RotateColorX(Direction);
  ACubes[9]->RotateColorX(Direction);
  ACubes[6]->RotateColorX(Direction);
  ACubes[7]->RotateColorX(Direction);
  ACubes[8]->RotateColorX(Direction);

  ACubes[1]->m_UpdateCube();
  ACubes[2]->m_UpdateCube();
  ACubes[3]->m_UpdateCube();
  ACubes[4]->m_UpdateCube();
  ACubes[9]->m_UpdateCube();
  ACubes[6]->m_UpdateCube();
  ACubes[7]->m_UpdateCube();
  ACubes[8]->m_UpdateCube();
}

void Cubes::MoveUpY(bool Direction) {

  if (Direction) {

    m_Swap(ACubes[21], ACubes[6]);
    m_Swap(ACubes[21], ACubes[18]);
    m_Swap(ACubes[18], ACubes[17]);

    m_Swap(ACubes[9], ACubes[3]);
    m_Swap(ACubes[9], ACubes[20]);
    m_Swap(ACubes[20], ACubes[16]);

  } else {

    m_Swap(ACubes[6], ACubes[21]);
    m_Swap(ACubes[6], ACubes[17]);
    m_Swap(ACubes[17], ACubes[18]);

    m_Swap(ACubes[9], ACubes[20]);
    m_Swap(ACubes[9], ACubes[3]);
    m_Swap(ACubes[3], ACubes[16]);
  }

  ACubes[3]->RotateColorY(Direction);
  ACubes[6]->RotateColorY(Direction);
  ACubes[9]->RotateColorY(Direction);
  ACubes[21]->RotateColorY(Direction);
  ACubes[17]->RotateColorY(Direction);
  ACubes[18]->RotateColorY(Direction);
  ACubes[16]->RotateColorY(Direction);
  ACubes[20]->RotateColorY(Direction);

  ACubes[3]->m_UpdateCube();
  ACubes[6]->m_UpdateCube();
  ACubes[9]->m_UpdateCube();
  ACubes[21]->m_UpdateCube();
  ACubes[17]->m_UpdateCube();
  ACubes[18]->m_UpdateCube();
  ACubes[16]->m_UpdateCube();
  ACubes[20]->m_UpdateCube();
}

void Cubes::MoveDownY(bool Direction) {

  if (Direction) {

    m_Swap(ACubes[14], ACubes[4]);
    m_Swap(ACubes[14], ACubes[12]);
    m_Swap(ACubes[12], ACubes[11]);

    m_Swap(ACubes[7], ACubes[1]);
    m_Swap(ACubes[7], ACubes[13]);
    m_Swap(ACubes[13], ACubes[10]);

  } else {

    m_Swap(ACubes[4], ACubes[14]);
    m_Swap(ACubes[4], ACubes[11]);
    m_Swap(ACubes[11], ACubes[12]);

    m_Swap(ACubes[7], ACubes[13]);
    m_Swap(ACubes[7], ACubes[1]);
    m_Swap(ACubes[1], ACubes[10]);
  }

  ACubes[1]->RotateColorY(Direction);
  ACubes[4]->RotateColorY(Direction);
  ACubes[7]->RotateColorY(Direction);
  ACubes[11]->RotateColorY(Direction);
  ACubes[10]->RotateColorY(Direction);
  ACubes[12]->RotateColorY(Direction);
  ACubes[13]->RotateColorY(Direction);
  ACubes[14]->RotateColorY(Direction);

  ACubes[1]->m_UpdateCube();
  ACubes[4]->m_UpdateCube();
  ACubes[7]->m_UpdateCube();
  ACubes[11]->m_UpdateCube();
  ACubes[10]->m_UpdateCube();
  ACubes[12]->m_UpdateCube();
  ACubes[13]->m_UpdateCube();
  ACubes[14]->m_UpdateCube();
}

void Cubes::MoveUpZ(bool Direction) {

  if (Direction) {

    m_Swap(ACubes[8], ACubes[14]);
    m_Swap(ACubes[8], ACubes[21]);
    m_Swap(ACubes[21], ACubes[19]);

    m_Swap(ACubes[7], ACubes[13]);
    m_Swap(ACubes[7], ACubes[9]);
    m_Swap(ACubes[9], ACubes[20]);

  } else {

    m_Swap(ACubes[14], ACubes[8]);
    m_Swap(ACubes[14], ACubes[19]);
    m_Swap(ACubes[19], ACubes[21]);

    m_Swap(ACubes[13], ACubes[7]);
    m_Swap(ACubes[13], ACubes[20]);
    m_Swap(ACubes[20], ACubes[9]);
  }

  ACubes[7]->RotateColorZ(Direction);
  ACubes[8]->RotateColorZ(Direction);
  ACubes[9]->RotateColorZ(Direction);
  ACubes[14]->RotateColorZ(Direction);
  ACubes[13]->RotateColorZ(Direction);
  ACubes[19]->RotateColorZ(Direction);
  ACubes[20]->RotateColorZ(Direction);
  ACubes[21]->RotateColorZ(Direction);

  ACubes[7]->m_UpdateCube();
  ACubes[8]->m_UpdateCube();
  ACubes[9]->m_UpdateCube();
  ACubes[14]->m_UpdateCube();
  ACubes[13]->m_UpdateCube();
  ACubes[19]->m_UpdateCube();
  ACubes[20]->m_UpdateCube();
  ACubes[21]->m_UpdateCube();
}

void Cubes::MoveDownZ(bool Direction) {
  if (Direction) {

    m_Swap(ACubes[2], ACubes[11]);
    m_Swap(ACubes[2], ACubes[17]);
    m_Swap(ACubes[17], ACubes[15]);

    m_Swap(ACubes[1], ACubes[10]);
    m_Swap(ACubes[1], ACubes[3]);
    m_Swap(ACubes[3], ACubes[16]);

  } else {

    m_Swap(ACubes[11], ACubes[2]);
    m_Swap(ACubes[11], ACubes[15]);
    m_Swap(ACubes[15], ACubes[17]);

    m_Swap(ACubes[10], ACubes[1]);
    m_Swap(ACubes[10], ACubes[16]);
    m_Swap(ACubes[16], ACubes[3]);
  }

  ACubes[1]->RotateColorZ(Direction);
  ACubes[2]->RotateColorZ(Direction);
  ACubes[3]->RotateColorZ(Direction);
  ACubes[11]->RotateColorZ(Direction);
  ACubes[17]->RotateColorZ(Direction);
  ACubes[10]->RotateColorZ(Direction);
  ACubes[15]->RotateColorZ(Direction);
  ACubes[16]->RotateColorZ(Direction);

  ACubes[1]->m_UpdateCube();
  ACubes[2]->m_UpdateCube();
  ACubes[3]->m_UpdateCube();
  ACubes[11]->m_UpdateCube();
  ACubes[17]->m_UpdateCube();
  ACubes[10]->m_UpdateCube();
  ACubes[15]->m_UpdateCube();
  ACubes[16]->m_UpdateCube();
}

void Cubes::RandowMove() {
  for (size_t i = 0; i < (rand() % 100) + 100; ++i) {
    MoveDownZ(true);
    MoveUpX(true);
    MoveUpY(false);
    MoveUpZ(true);
    MoveUpY(true);
    MoveDownZ(true);
    MoveUpX(false);
    MoveDownX(true);
    MoveDownY(true);
    MoveUpY(true);
    MoveDownZ(false);
    MoveDownX(false);
    MoveUpZ(false);
  }
}

void Cubes::AutomaticMove() {

  color tmp;

  while (!m_IsCross()) {

    for (size_t index = 0; index < 27; ++index) {
      if (ACubes[index]->CountColor == 2 && m_IsWhite(index)) {

        if (index == 11) {

          if (ACubes[index]->SiteF != color::WHITE) {
            MoveDownZ(true);
            MoveUpX(false);
            MoveDownY(false);
          }

        } else if (index == 2) {
          if (ACubes[index]->SiteF != color::WHITE) {
            MoveDownZ(false);
            MoveUpY(false);
            MoveDownX(false);
          }
        } else if (index == 17) {
          if (ACubes[index]->SiteF != color::WHITE) {
            MoveUpY(true);
            MoveUpX(true);
            MoveDownZ(true);
          }
        } else if (index == 15) {
          if (ACubes[index]->SiteF != color::WHITE) {
            MoveUpX(true);
            MoveUpY(false);
            MoveDownZ(false);
          }
        } else if (index == 4) {
          if (ACubes[index]->SiteB == color::WHITE) {

            while (ACubes[11]->SiteF == color::WHITE) {
              MoveDownZ(true);
            }

            MoveDownY(true);

          } else {

            while (ACubes[2]->SiteF == color::WHITE) {
              MoveDownZ(true);
            }

            MoveDownX(true);
          }
        } else if (index == 6) {
          if (ACubes[index]->SiteB == color::WHITE) {

            while (ACubes[17]->SiteF == color::WHITE) {
              MoveDownZ(true);
            }

            MoveUpY(true);

          } else {

            while (ACubes[2]->SiteF == color::WHITE) {
              MoveDownZ(true);
            }

            MoveDownX(false);
          }
        } else if (index == 8) {

          if (ACubes[index]->SiteB == color::WHITE) {

            MoveDownX(true);

            while (ACubes[11]->SiteF == color::WHITE) {
              MoveDownZ(true);
            }

            MoveDownY(true);
          } else {

            while (ACubes[2]->SiteF == color::WHITE) {
              MoveDownZ(true);
            }
            MoveDownY(true);
            MoveDownY(true);
          }
        } else if (index == 12) {

          if (ACubes[index]->SiteD == color::WHITE) {

            while (ACubes[11]->SiteF == color::WHITE) {
              MoveDownZ(true);
            }

            MoveDownY(false);
          } else {

            while (ACubes[15]->SiteF == color::WHITE) {
              MoveDownZ(true);
            }

            MoveUpX(true);
          }
        } else if (index == 19) {

          if (ACubes[index]->SiteD == color::WHITE) {

            MoveUpX(true);

            while (ACubes[11]->SiteF == color::WHITE) {
              MoveDownZ(true);
            }

            MoveDownY(false);
          } else {

            while (ACubes[15]->SiteF == color::WHITE) {
              MoveDownZ(true);
            }
            MoveUpX(true);
            MoveUpX(true);
          }
        } else if (index == 18) {

          if (ACubes[index]->SiteD == color::WHITE) {

            while (ACubes[17]->SiteF == color::WHITE) {
              MoveDownZ(true);
            }

            MoveUpY(false);
          } else {

            while (ACubes[15]->SiteF == color::WHITE) {
              MoveDownZ(true);
            }

            MoveUpX(false);
          }
        } else if (index == 14) {

          if (ACubes[index]->SiteE == color::WHITE) {

            while (ACubes[11]->SiteF == color::WHITE) {
              MoveDownZ(true);
            }

            MoveDownY(false);
            MoveDownY(false);
          } else {

            MoveDownY(false);

            while (ACubes[15]->SiteF == color::WHITE) {
              MoveDownZ(true);
            }

            MoveUpX(true);
          }
        } else if (index == 21) {

          if (ACubes[index]->SiteE == color::WHITE) {

            while (ACubes[17]->SiteF == color::WHITE) {
              MoveDownZ(true);
            }

            MoveUpY(false);
            MoveUpY(false);
          } else {

            MoveUpY(false);

            while (ACubes[15]->SiteF == color::WHITE) {
              MoveDownZ(true);
            }

            MoveUpX(false);
          }
        }
      }
    }
  }
  while (!m_IsTwoSite()) {

    while (ACubes[11]->SiteA != color::GREEN) {
      MoveDownZ(true);
    }

    if (ACubes[17]->SiteC == color::BLUE &&
        ACubes[15]->SiteD == color::ORANGE) {
      MoveDownZ(false);
      break;
    }

    if (ACubes[17]->SiteC != color::BLUE) {

      MoveDownY(true);

      if (ACubes[15]->SiteD == color::BLUE) {
        MoveDownZ(true);
        MoveDownY(false);
        MoveDownZ(false);
      } else {
        MoveDownZ(false);
        MoveDownY(false);
        MoveDownZ(true);
      }
    }

    while (ACubes[11]->SiteA != color::GREEN) {
      MoveDownZ(true);
    }

    if (ACubes[15]->SiteD != color::ORANGE) {
      MoveDownZ(false);
      MoveDownY(true);
      MoveDownZ(false);
      MoveDownZ(false);
      MoveDownY(false);
      MoveDownZ(false);
      MoveDownZ(false);
      MoveDownY(true);
    } else {
      MoveDownZ(false);
    }

    while (ACubes[11]->SiteA != color::ORANGE) {
      MoveDownZ(false);
    }
  }
}

color Cubes::m_GiveColor(size_t index) {
  if (ACubes[index]->SiteA != color::WHITE &&
      ACubes[index]->SiteA != color::BLACK) {
    return ACubes[index]->SiteA;

  } else if (ACubes[index]->SiteB != color::WHITE &&
             ACubes[index]->SiteB != color::BLACK) {
    return ACubes[index]->SiteB;
  } else if (ACubes[index]->SiteC != color::WHITE &&
             ACubes[index]->SiteC != color::BLACK) {
    return ACubes[index]->SiteC;
  } else if (ACubes[index]->SiteD != color::WHITE &&
             ACubes[index]->SiteD != color::BLACK) {
    return ACubes[index]->SiteD;
  } else if (ACubes[index]->SiteE != color::WHITE &&
             ACubes[index]->SiteE != color::BLACK) {
    return ACubes[index]->SiteE;
  }

  return ACubes[index]->SiteF;
}

bool Cubes::m_IsWhite(size_t index) {
  if (ACubes[index]->SiteA == color::WHITE) {
    return true;
  } else if (ACubes[index]->SiteB == color::WHITE) {
    return true;
  } else if (ACubes[index]->SiteC == color::WHITE) {
    return true;
  } else if (ACubes[index]->SiteD == color::WHITE) {
    return true;
  } else if (ACubes[index]->SiteE == color::WHITE) {
    return true;
  } else if (ACubes[index]->SiteF == color::WHITE) {
    return true;
  }

  return false;
}

bool Cubes::m_IsCross() {
  if (!(ACubes[11]->SiteF == color::WHITE &&
        ACubes[15]->SiteF == color::WHITE &&
        ACubes[17]->SiteF == color::WHITE &&
        ACubes[2]->SiteF == color::WHITE)) {
    return false;
  }
  return true;
}

bool Cubes::m_IsTwoSite() {
  return (ACubes[11]->SiteA == color::ORANGE &&
          ACubes[2]->SiteB == color::GREEN && ACubes[17]->SiteC == color::RED &&
          ACubes[15]->SiteD == color::BLUE);
}

bool Cubes::m_IsWhiteSide() {
  return (ACubes[10]->SiteF == color::WHITE &&
          ACubes[16]->SiteF == color::WHITE &&
          ACubes[1]->SiteF == color::WHITE && ACubes[3]->SiteF == color::WHITE);
}

bool Cubes::SaveCube(const char *Filename) {

  std::ofstream output(Filename, std::ios::binary);

  if (!output.is_open()) {
    std::cerr << "Error open file" << std::endl;
    output.close();
    return false;
  }

  for (size_t i = 0; i < 27; ++i) {
    output.write(reinterpret_cast<char *>(ACubes[i]->vertices),
                 sizeof(ACubes[i]->vertices));
  }

  output.close();

  return true;
}

bool Cubes::LoadCube(const char *Filename) {
  std::ifstream input(Filename, std::ios::binary);

  if (!input.is_open()) {

    std::cerr << "Error open file" << std::endl;
    input.close();
    return false;
  }

  for (size_t i = 0; i < 27; ++i) {
    input.read(reinterpret_cast<char *>(ACubes[i]->vertices),
               sizeof(ACubes[i]->vertices));

    ACubes[i]->m_UpdateCube();
  }

  input.close();

  return true;
}

void Cubes::m_Swap(Cube *&A, Cube *&B) {
  for (int index = 0, count = 0; count < 36; index += 6, ++count) {

    std::swap(A->vertices[Icolor1(index)], B->vertices[Icolor1(index)]);
    std::swap(A->vertices[Icolor2(index)], B->vertices[Icolor2(index)]);
    std::swap(A->vertices[Icolor3(index)], B->vertices[Icolor3(index)]);
  }

  std::swap(A->SiteA, B->SiteA);
  std::swap(A->SiteB, B->SiteB);
  std::swap(A->SiteC, B->SiteC);
  std::swap(A->SiteD, B->SiteD);
  std::swap(A->SiteE, B->SiteE);
  std::swap(A->SiteF, B->SiteF);
}
