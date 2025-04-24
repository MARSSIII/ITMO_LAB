#include "CircularBuffer/CircularBuffer.hpp"

#include <algorithm>
#include <iostream>

#define space_ std::cout << "\n"
#define endl std::endl
#define Separation std::cout << "\n------------\n" << endl

enum COMMAND {
  RESERVE,
  PUSH_BACK,
  POP_BACK,
  PUSH_FRONT,
  POP_FRONT,
  PUSH,
  DELETE,
  SHOWBUF,
  SHOWSIZE,
  SHOWCAP,
  INDEX,
  STDMAXELEMENT,
  EXIT,
} COMMAND;

int main() {
  size_t answerCommand;
  size_t tmpSize;

  int tmpInt;

  bool work = true;

  CircularBuffer<int> Buffer;
  do {
    std::cout << "\t---CurcularBuffer---" << endl;

    space_;
    space_;

    std::cout << "ALL command in CircularBuffer : " << endl;
    space_;

    std::cout << "0. Reserve" << endl;
    space_;

    std::cout << "1. Push_back" << endl;
    std::cout << "2. Pop_back" << endl;
    std::cout << "3. Push_front" << endl;
    std::cout << "4. Pop_front" << endl;
    std::cout << "5. Push" << endl;
    std::cout << "6. Delete" << endl;
    space_;

    std::cout << "7. Show buffer" << endl;
    space_;
    std::cout << "8. Show size" << endl;
    std::cout << "9. Show capacity" << endl;
    space_;

    std::cout << "10. Show value in index" << endl;
    space_;

    std::cout << "11. std::max_elementy " << endl;
    space_;

    std::cout << "12. Exit" << endl;
    space_;

    std::cout << "Enter: ";
    std::cin >> answerCommand;

    Separation;

    switch (answerCommand) {
    case COMMAND::RESERVE:
      std::cout << "Enter the reserve amount" << endl;
      space_;
      std::cout << "Enter : ";
      std::cin >> tmpSize;

      Buffer.reserve(tmpSize);

      Separation;
      break;
    case COMMAND::PUSH_BACK:
      std::cout << "Enter number push" << endl;
      space_;
      std::cout << "Enter : ";
      std::cin >> tmpInt;

      Buffer.PushBack(tmpInt);

      Separation;
      break;
    case COMMAND::POP_BACK:
      std::cout << "Pop completed!" << endl;

      Buffer.PopBack();

      Separation;
      break;
    case COMMAND::PUSH_FRONT:
      std::cout << "Enter number for push" << endl;
      space_;
      std::cout << "Enter : ";
      std::cin >> tmpInt;

      Buffer.PushFront(tmpInt);

      Separation;
      break;
    case COMMAND::POP_FRONT:
      std::cout << "Pop completed!" << endl;

      Buffer.PopFront();

      Separation;
      break;
    case COMMAND::PUSH:
      std::cout << "Enter number for push" << endl;

      std::cout << "Enter : ";
      std::cin >> tmpInt;

      Buffer.Push(tmpInt, Buffer.begin());

      Separation;

      break;
    case COMMAND::DELETE:

      Buffer.Delete(Buffer.begin());

      std::cout << "Delete completed!" << endl;

      Separation;
      break;
    case COMMAND::SHOWBUF:

      Buffer.ShowBuffer();

      Separation;
      break;

    case COMMAND::SHOWSIZE:

      std::cout << Buffer.Size() << endl;

      Separation;
      break;

    case COMMAND::SHOWCAP:

      std::cout << Buffer.Capacity() << endl;

      Separation;
      break;

    case COMMAND::INDEX:
      std::cout << "Enter index for get" << endl;

      std::cout << "Enter : ";
      std::cin >> tmpInt;

      --tmpInt;

      if (tmpInt < 0 && (tmpInt >= Buffer.Capacity())) {
        std::cout << "Uncorrect index " << endl;
      } else {
        std::cout << "\nvalue : " << Buffer[tmpInt] << endl;
      }

      Separation;
      break;

    case COMMAND::STDMAXELEMENT:

      std::cout << "Max element in buffer : "
                << *(std::max_element(
                       Buffer.begin(), Buffer.end(),
                       [](int a, int b) { return std::abs(a) < std::abs(b); }));

      Separation;
      break;

    case COMMAND::EXIT:
      work = false;
      break;

    default:
      std::cout << "Write correct command" << endl;
      break;
    }

  } while (work);

  return 0;
}
