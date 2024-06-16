#include "Menu/Menu.hpp"

#include <iostream>

#define Separation std::cout << "\n-----------------\n" << std::endl; 

enum commandMenu { EXIT, CREATE, DELETE, ENTER };

int main() {
  Menu menu;

  int answerMenu;
  int NumberSet;

  int SizeSet;

  bool flagMenu = true;
  bool flagEmpty = true;

  while (flagMenu) {

    std::cout << "\t----M e n u----\n" << std::endl;
    std::cout << "1. Create new Integer Set " << std::endl;

    if (menu.GetNumberOfSet()) {
      std::cout << "2. Delete IntegerSet" << std::endl;
      std::cout << "3. Enter IntegerSet" << std::endl;

      flagEmpty = false;
    }

    std::cout << "\n0. Exit\n" << std::endl;

    std::cout << "Enter : ";

    std::cin >> answerMenu;

    while (!(-1 < answerMenu && answerMenu < (flagEmpty ? 2 : 4))) {
      std::cout << "write correct command pls" << std::endl;

      std::cout << "Enter: ";
      std::cin >> answerMenu;
    }

    Separation

    switch (answerMenu) {

    case commandMenu::CREATE:

      std::cout << "What will be the max size for Set?" << std::endl;

      std::cout << "\nEnter : ";
      std::cin >> SizeSet;

      menu.CreateNewSet(SizeSet);

      Separation
      break;

    case commandMenu::DELETE:

      menu.PrintAllSet();
      std::cout << "Enter Set (delete) : " << std::endl;
      std::cin >> NumberSet;
      --NumberSet;

      if (NumberSet < 0 && menu.GetNumberOfSet() < NumberSet) {
        std::cout << "Write correct number Set pls" << std::endl;
        break;
      }

      menu.DeleteSet(NumberSet);

      std::cout << "Delete completed" << std::endl;

      Separation
      break;

    case commandMenu::ENTER:

      menu.PrintAllSet();
      std::cout << "\nEnter Set : ";

      std::cin >> NumberSet;
      --NumberSet;

      if (NumberSet < 0 && menu.GetNumberOfSet() < NumberSet) {
        std::cout << "Write correct number Set pls" << std::endl;
        Separation
        break;
      }

      Separation

      menu.initDialog(NumberSet);
      break;

    case commandMenu::EXIT:
      flagMenu = false;
      break;

    default:
      break;
    }
  }
  return 0;
}

