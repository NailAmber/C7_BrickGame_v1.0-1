#ifndef BRICK_GAME_FRONTEND_H_
#define BRICK_GAME_FRONTEND_H_

#include <ncurses.h>
#include <string.h>

#include "../../brick_game/defines.h"
#include "../../brick_game/objects.h"

/*!

    \brief Перевод сигнала в код UserAction_t

    \param user_input код сигнала нажатия кнопки
 */
UserAction_t get_signal(int user_input);

/*!

    \brief Рисует основной интерфейс для игры
 */
void print_overlay(void);

/*!

    \brief Рисует прямоугольник по заданным координатам

    \param top_y Верхняя граница  прямоугольника
    \param bottom_y Нижняя граница  прямоугольника
    \param left_x Левая граница  прямоугольника
    \param right_x Правая граница  прямоугольника
 */
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);

/*!

    \brief Выводит статы в правом блоке интерфейса

    \param stats Структура с статами
 */
void print_stats(GameInfo_t *stats);

/*!

    \brief Выводит статы в правом блоке интерфейса

    \param stats Структура с статами
 */
void print_board(GameInfo_t *board);

/*!

    \brief Выводит баннер поражения

    \param stats Структура с статами для вывода конечных статов
 */
void print_banner(GameInfo_t *stats);

/*!

    \brief Рисует фигуру в блоке следующей фигуры тетриса

    \param stats Структура с матрицей, содержащей следующую фигуру
 */
void print_next_section(GameInfo_t *stats);

/*!

    \brief Выводит надпись Игра остановлена
 */
void print_pause();

/*!

    \brief Рисует меню выбора игры в консольном режиме интерфейса

    \param selectedGame Номер выбранной игры, 0 - Тетрис
 */
void select_game(int selectedGame);

/*!

    \brief Очистка экрана выбора игры
 */
void clear_select_game_screen();

/*!

    \brief Получаем или задаём в статическую переменную структуру GameInfo_t

    \param gameInfo Структура GameInfo_t
 */
GameInfo_t *change_GameInfo_t(GameInfo_t *gameInfo);

/*!

    \brief Основная функция отрисовки всего интерфеса
 */
GameInfo_t updateCurrentState();

#endif  // TETRIS_FRONTEND_H_