#pragma once

#include "window.hpp"

class Events {
public:
  // массив клавиатуры и мыши
  static bool *_keys;

  // массив сожержащий последние изменения состояния клавиш и не только
  static unsigned int *_frames;

  // текущий кадр (текущие нажатие)
  static unsigned int _currentFrame;

  // изменение курсора
  static float deltaX, deltaY;
  // текущии координаты курсора
  static float X, Y;

  // блокировка курсора
  static bool cursorLocked;
  static bool cursorStarted;

  // Инициализация ивентов
  static int initialize();
  static void pullEvents();

  // Нажатие клавиши
  static bool isPressed(int keyCode);
  // Удержание клавиши
  static bool justPressed(int keyCode);

  // Нажатие мыши
  static bool clicked(int button);
  // Удержание мыши
  static bool justClicked(int button);

  // Смена работы курсора
  static void toogleCursor();
};
