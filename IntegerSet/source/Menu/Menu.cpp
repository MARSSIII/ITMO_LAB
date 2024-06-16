#include "Menu.hpp"

#include <iostream>
#include <vector>

size_t Menu::GetNumberOfSet() const { return (this->m_NumberOfSet); }

void Menu::m_Separation() { std::cout << "\n-------------\n" << std::endl; }

std::string Menu::m_lower(std::string str) {

  for (char &i : str) {
    i += 32;
  }

  return str;
}

void Menu::initDialog(size_t NumberSet) {

  bool flagSet = true;
  int answerSet;
  std::vector<int> VnumbersSets;

  std::string strAnswer;

  while (flagSet) {
    std::cout << "Enter command : " << std::endl;

    std::cout << "1. Insert new value" << std::endl;
    std::cout << "2. Erase value" << std::endl;
    std::cout << "3. Find in set" << std::endl;
    std::cout << "4. Union with sets" << std::endl;
    std::cout << "5. Intersection with sets" << std::endl;
    std::cout << "6. Difference with sets" << std::endl;

    std::cout << "\n7. Show set" << std::endl;

    std::cout << "\n0. Exit to Menu" << std::endl;

    std::cout << "\nEnter : ";
    std::cin >> answerSet;

    while (-1 > answerSet || answerSet > 8) {
      std::cout << "Write correct command pls" << std::endl;
      std::cin >> answerSet;
    }

    Menu::m_Separation();

    switch (answerSet) {
    case COMMAND::INSERT:

      std::cout << "What value do you want to add?" << std::endl;
      std::cout << "\nEnter : ";
      std::cin >> answerSet;

      if (!this->Insert(answerSet, NumberSet)) {
        std::cout << "Set is full" << std::endl;

      } else {
        std::cout << "\nAdded completed" << std::endl;
      }

      Menu::m_Separation();
      break;

    case COMMAND::ERASE:

      this->Print(NumberSet);

      std::cout << "What value do you want to erase?" << std::endl;
      std::cout << "\nEnter : ";
      std::cin >> answerSet;

      this->Erase(answerSet, NumberSet);

      std::cout << "\nErase completed" << std::endl;

      Menu::m_Separation();
      break;

    case COMMAND::FIND:

      std::cout << "What value do you want to find in the Set?" << std::endl;
      std::cout << "\nEnter : ";
      std::cin >> answerSet;

      if (this->Contains(answerSet, NumberSet)) {
        std::cout << "it's true" << std::endl;

      } else {
        std::cout << "it's false" << std::endl;
      }

      Menu::m_Separation();
      break;

    case COMMAND::UNION:

      if (this->GetNumberOfSet() < 2) {
        std::cout << "Add new Set pls" << std::endl;

        Menu::m_Separation();
        break;
      }

      this->PrintAllSet(NumberSet);

      std::cout << "\nWhich sets do you want to Union?" << std::endl;

      VnumbersSets.push_back(NumberSet);

      std::cout << "\nEnter Set: ";
      std::cin >> answerSet;
      VnumbersSets.push_back(answerSet - 1);

      if (this->GetNumberOfSet() > 2) {
        std::cout << "More? (yes or no)" << std::endl;
        std::cin >> strAnswer;

        if (Menu::m_lower(strAnswer) == "yes") {

          std::cout << "How many sets (number " << this->GetNumberOfSet() - 2
                    << ") ?" << std::endl;
          std::cin >> answerSet;

          while (answerSet < 1 and answerSet > this->GetNumberOfSet() - 2) {
            std::cout << "Write correct number pls" << std::endl;
            std::cin >> answerSet;
          }

          for (int i = 0; i < answerSet; ++i) {
            std::cout << "Enter set" << std::endl;
            std::cin >> answerSet;
            VnumbersSets.push_back(answerSet - 1);
          }
        }
      }

      this->Union(VnumbersSets);

      VnumbersSets.clear();

      std::cout << "Union completed" << std::endl;

      Menu::m_Separation();
      break;

    case COMMAND::INTERSECTION:

      if (this->GetNumberOfSet() < 2) {
        std::cout << "Add new Set pls" << std::endl;

        Menu::m_Separation();
        break;
      }

      this->PrintAllSet(NumberSet);

      std::cout << "Which sets do you want to Intersection?" << std::endl;

      VnumbersSets.push_back(NumberSet);

      std::cout << "\nEnter Set: ";
      std::cin >> answerSet;
      VnumbersSets.push_back(answerSet);

      if ((this->GetNumberOfSet() - 2) > 0) {

        std::cout << "More? (yes or no)" << std::endl;

        std::cin >> strAnswer;

        if (Menu::m_lower(strAnswer) == "yes") {
          std::cout << "How many sets (number " << this->GetNumberOfSet() - 2
                    << ") ? " << std::endl;
          std::cin >> answerSet;

          while (answerSet < 1 and answerSet > this->GetNumberOfSet() - 2) {
            std::cout << "Write correct number pls" << std::endl;
            std::cin >> answerSet;
          }

          for (int i = 0; i < answerSet; ++i) {
            std::cout << "Enter Set" << std::endl;
            std::cin >> answerSet;
            VnumbersSets.push_back(answerSet - 1);
          }
        }
      }

      this->Intersection(VnumbersSets);

      VnumbersSets.clear();

      std::cout << "Intersection completed" << std::endl;

      Menu::m_Separation();
      break;

    case COMMAND::DEFFERENCE:

      if (this->GetNumberOfSet() < 2) {
        std::cout << "Add new Set pls" << std::endl;

        Menu::m_Separation();
        break;
      }

      this->PrintAllSet(NumberSet);

      std::cout << "Which sets do you want to Difference?" << std::endl;

      VnumbersSets.push_back(NumberSet);

      std::cout << "\nEnter Set: ";
      std::cin >> answerSet;

      VnumbersSets.push_back(answerSet - 1);

      if ((this->GetNumberOfSet() - 2) > 0) {

        std::cout << "More? (yes or no)" << std::endl;
        std::cin >> strAnswer;

        if (Menu::m_lower(strAnswer) == "yes") {

          std::cout << "How many sets (number " << this->GetNumberOfSet() - 2
                    << ") ?" << std::endl;
          std::cin >> answerSet;

          while (answerSet < 1 and answerSet > this->GetNumberOfSet() - 2) {
            std::cout << "Write correct number pls" << std::endl;
            std::cin >> answerSet;
          }

          for (int i = 0; i < answerSet; ++i) {
            std::cout << "Enter Set" << std::endl;
            std::cin >> answerSet;

            VnumbersSets.push_back(answerSet - 1);
          }
        }
      }

      this->Difference(VnumbersSets);

      VnumbersSets.clear();

      std::cout << "Difference completed" << std::endl;

      Menu::m_Separation();
      break;

    case COMMAND::SHOW:
      this->Print(NumberSet);

      Menu::m_Separation();
      break;

    case COMMAND::EXIT:
      flagSet = false;
      break;

    default:
      break;
    }
  }
}

void Menu::Print(size_t NumberSet) {

  std::cout << "{ ";
  this->m_VSet[NumberSet].PrintSet();
  std::cout << " }" << std::endl;
}

void Menu::DeleteSet(size_t NumberSet) {

  std::swap(m_VSet[NumberSet], m_VSet[(this->m_NumberOfSet) - 1]);
  m_VSet.pop_back();

  --m_NumberOfSet;
}

void Menu::CreateNewSet(size_t MaxSizeSet) {

  m_VSet.emplace_back(MaxSizeSet);

  ++m_NumberOfSet;
}

void Menu::PrintAllSet() {

  for (int i = 0; i < (this->m_NumberOfSet); ++i) {

    std::cout << "Set " << i + 1 << " { ";
    this->m_VSet[i].PrintSet();
    std::cout << " }" << std::endl;
  }
}

void Menu::PrintAllSet(size_t number) {

  for (int i = 0; i < (this->m_NumberOfSet); ++i) {

    std::cout << "Set " << i + 1 << " { ";
    this->m_VSet[i].PrintSet();
    std::cout << " }" << std::endl;

    if (i == number) {
      std::cout << " USED NOW " << std::endl;
    }
  }
}

bool Menu::Insert(int value, size_t NumberSet) {

  if (NumberSet >= (this->m_NumberOfSet)) {
    return false;
  }

  return this->m_VSet[NumberSet].Insert(value);
}

void Menu::Erase(int value, size_t NumberSet) {

  std::cout << "erase " << value << std::endl;

  if (NumberSet >= (this->m_NumberOfSet)) {

    std::cout << "problem" << std::endl;
    return;
  }

  this->m_VSet[NumberSet].Delete(value);
}

void Menu::Union(const std::vector<int> &NumberesSets) {

  IntegerSet NewSet(0);
  for (int NumberesSet : NumberesSets) {

    NewSet.ChangeCapacity(m_VSet[NumberesSet].GetCapacitySet());

    for (int el : m_VSet[NumberesSet].GetElementOfSet()) {
      NewSet.Insert(el);
    }
  }

  ++(this->m_NumberOfSet);
  this->m_VSet.push_back(NewSet);
}

bool Menu::Contains(int value, size_t NumberSet) {

  return (this->m_VSet[NumberSet].FindValue(value));
}

void Menu::Intersection(const std::vector<int> &NumbersSets) {

  IntegerSet NewSet(0);

  std::list<int> resultV = (this->m_VSet)[0].GetElementOfSet();

  std::list<int> tmpV;
  for (int i = 1; i < NumbersSets.size(); ++i) {

    for (int ElV : resultV) {
      if ((this->m_VSet)[i].FindValue(ElV)) {
        tmpV.push_back(ElV);
      }
    }

    resultV = tmpV;
    tmpV.clear();
  }

  NewSet.ChangeCapacity(resultV.size());

  for (int el : resultV) {
    NewSet.Insert(el);
  }

  ++(this->m_NumberOfSet);
  (this->m_VSet).push_back(NewSet);
}

void Menu::Difference(const std::vector<int> &NumbersSets) {

  IntegerSet NewSet(0);

  std::list<int> resultV = (this->m_VSet[NumbersSets[0]].GetElementOfSet());

  std::list<int> tmp;

  for (int i = 1; i < NumbersSets.size(); ++i) {

    for (int el : resultV) {

      if ((this->m_VSet)[NumbersSets[i]].FindValue(el)) {

        tmp.push_back(el);
      }
    }

    tmp.clear();
  }

  NewSet.ChangeCapacity(resultV.size());

  for (int el : resultV) {
    NewSet.Insert(el);
  }

  ++(this->m_NumberOfSet);
  (this->m_VSet).push_back(NewSet);
}
