#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

/*!

    \brief Нумерация фигур
*/
typedef enum { I = 0, J, L, O, S, T, Z } block;

/*!

    \brief Структура для координат фигуры, типа фигуры и текущего поворота
*/
typedef struct {
  int x1;
  int y1;

  int x2;
  int y2;

  int x3;
  int y3;

  int x4;
  int y4;

  block type;
  int rotate_state;
} Tetramino;

/*!

    \brief Нумерация состояний вращения фигуры
*/
typedef enum { first = 0, second, third, fourth } rotateState;

/*!

    \brief Возможные кнопки консоли и их действия
*/
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

/*!

    \brief Структура отвечающая за все основные элементы консоли
*/
typedef struct {
  /*!

    \brief Игровое поле
*/
  int **field;
  /*!

    \brief Матрица для обозначение следующей фигуры
*/
  int **next;

  /*!

    \brief Количество очков
*/
  int score;

  /*!

    \brief Количество очков рекорда
*/
  int high_score;

  /*!

    \brief Номер уровня
*/
  int level;

  /*!

    \brief Текущая скорость игры
*/
  int speed;

  /*!

    \brief Нажата ли пауза
*/
  int pause;
} GameInfo_t;

#endif