#ifndef TETRIS_FSM_H_
#define TETRIS_FSM_H_

#include "../defines.h"
#include "../objects.h"
#include "tetris_backend.h"

/*!
    \brief Состояния конечного автомата
 */
typedef enum {
  START = 0,
  SPAWN,
  MOVING,
  ROTATE,
  SHIFTING,
  COLLIDE,
  GAMEOVER,
  EXIT_STATE,
  PAUSE
} tetris_state;

/*!

    \brief Сигналы которые принимает игра

 */
typedef enum {
  MOVE_DOWN = 0,
  MOVE_RIGHT,
  MOVE_LEFT,
  ESCAPE_BTN,
  ENTER_BTN,
  NOSIG
} signals;

/*!

    \brief Установка или получение переменной с использованием локальной
   статической переменной

    \param gameInfo Рабочая структура
    \return Возвращает ссылку на соответсвующую структуру
 */
GameInfo_t *get_gameInfo(GameInfo_t *gameInfo);

/*!

    \brief Установка или получение переменной с использованием локальной
   статической переменной

    \param sig Рабочая перменная
    \return Возвращает ссылку на соответсвующую переменную
 */
UserAction_t *get_UserAction_t(UserAction_t *sig);

/*!

    \brief Установка или получение переменной с использованием локальной
   статической переменной

    \param fallTime Рабочая перменная
    \return Возвращает ссылку на соответсвующую переменную
 */
bool *get_fallTime(bool *fallTime);

/*!

    \brief Установка или получение переменной с использованием локальной
   статической переменной

    \param state Рабочая перменная
    \return Возвращает ссылку на соответсвующую переменную
 */
tetris_state *get_state(tetris_state *state);

/*!

    \brief Установка или получение переменной с использованием локальной
   статической переменной

    \param current Рабочая перменная
    \return Возвращает ссылку на соответсвующую переменную
 */
Tetramino *get_current(Tetramino *current);

/*!

    \brief Установка или получение переменной с использованием локальной
   статической переменной

    \param nextBlock Рабочая перменная
    \return Возвращает ссылку на соответсвующую переменную
 */
block *get_nextBlock(block *nextBlock);

/*!

    \brief Функция из спецификации. Вводим только код сигнала. Идет обработка
   всех нужных переменных на статической уровне и происходит игровой шаг

    \param action Код нажатой кнопки в нужном формате
    \param hold Заглушка, понадобится в следующих играх
 */
void userInput(UserAction_t action, bool hold);

/*!

    \brief Сам конечный автомат состояний и переключений между состояниями

    \param sig Поступивший сигнал
    \param fallTime Время ли сейчас сдвигать фигуру вниз
    \param state Текущее состояние машины
    \param gameInfo Главная структура с полем
    \param current Текущие координаты фигуры
    \param nextBlock Следующая фигура
 */
void sigact(UserAction_t *sig, const bool *fallTime, tetris_state *state,
            GameInfo_t *gameInfo, Tetramino *current, block *nextBlock);

/*!

    \brief Состояние спавна новой фигуры и проверки можно ли
   заспавнить новую фигуру

    \param gameInfo Структура с игровым полем
    \param current Координаты фигуры
    \param nextBlock Следующая фигура
    \param state Стостояние машины
*/
void spawn_state(GameInfo_t *gameInfo, Tetramino *current, block *nextBlock,
                 tetris_state *state);

/*!

    \brief Состояние движения фигуры, принимает на вход сигнал нажатия для
   определения направления движеия фигуры

    \param sig Сигнал нажатия
    \param gameInfo Структура с игровым полем
    \param current Координаты фигуры
    \param state Стостояние машины
*/
void move_state(UserAction_t *sig, GameInfo_t *gameInfo, Tetramino *current,
                tetris_state *state);

/*!

    \brief Состояние паузы. Проверка на нажатие паузы или выхода из игры

    \param sig Сигнал нажатия
    \param gameInfo Структура с игровым полем
    \param state Стостояние машины
*/
void pause_state(UserAction_t *sig, GameInfo_t *gameInfo, tetris_state *state);

/*!

    \brief Проверка на возможность движения фигуры вниз. Движение фигуры вниз

    \param current Координаты текущей фигуры
    \param gameInfo Структура с игровым полем
    \return Упала ли фигура на что-то твёрдое 1 иначе 0
*/
int movedown(Tetramino *current, GameInfo_t *gameInfo);

/*!

    \brief Проверка на возможность движения фигуры вправо. Движение фигуры
   вправо

    \param current Координаты текущей фигуры
    \param gameInfo Структура с игровым полем
*/
void moveright(Tetramino *current, GameInfo_t *gameInfo);

/*!

    \brief Проверка на возможность движения фигуры влево. Движение фигуры влево

    \param current Координаты текущей фигуры
    \param gameInfo Структура с игровым полем
*/
void moveleft(Tetramino *current, GameInfo_t *gameInfo);

/*!

    \brief Проверка на возможность движения фигуры вниз. Движение фигуры вниз
   после определенного таймера

    \param current Координаты текущей фигуры
    \param gameInfo Структура с игровым полем
    \param state Текущее стостояние машины
*/
void movedown_clock_check(GameInfo_t *gameInfo, Tetramino *current,
                          tetris_state *state);

/*!

    \brief Функция определяющая поворот фигуры согласно её типу

    \param current Тип фигуры
    \param gameInfo Структура с игровым полем
*/
int rotate(Tetramino *current, GameInfo_t *gameInfo);

/*!

    \brief Расчёт поворота для фигуры I

    \param current Координаты фигуры
    \param gameInfo Структура с игровым полем
*/
void rotate_I(Tetramino *current, GameInfo_t *gameInfo);

/*!

    \brief Расчёт поворота для фигуры J. Первые две формы

    \param current Координаты фигуры
    \param gameInfo Структура с игровым полем
    \return Был ли произведен поворот из второго положения в третье
*/
int rotate_J_first(Tetramino *current, GameInfo_t *gameInfo);

/*!

    \brief Расчёт поворота для фигуры J. Вторые две формы

    \param current Координаты фигуры
    \param gameInfo Структура с игровым полем

*/
void rotate_J_second(Tetramino *current, GameInfo_t *gameInfo);

/*!

    \brief Расчёт поворота для фигуры J

    \param current Координаты фигуры
    \param gameInfo Структура с игровым полем
*/
void rotate_J(Tetramino *current, GameInfo_t *gameInfo);

/*!

    \brief Расчёт поворота для фигуры L. Первые две формы

    \param current Координаты фигуры
    \param gameInfo Структура с игровым полем
    \return Был ли произведен поворот из второго положения в третье
*/
int rotate_L_first(Tetramino *current, GameInfo_t *gameInfo);

/*!

    \brief Расчёт поворота для фигуры L. Вторые две формы

    \param current Координаты фигуры
    \param gameInfo Структура с игровым полем
*/
void rotate_L_second(Tetramino *current, GameInfo_t *gameInfo);

/*!

    \brief Расчёт поворота для фигуры L

    \param current Координаты фигуры
    \param gameInfo Структура с игровым полем
*/
void rotate_L(Tetramino *current, GameInfo_t *gameInfo);

/*!

    \brief Расчёт поворота для фигуры S

    \param current Координаты фигуры
    \param gameInfo Структура с игровым полем
*/
void rotate_S(Tetramino *current, GameInfo_t *gameInfo);

/*!

    \brief Расчёт поворота для фигуры T. Первые две формы

    \param current Координаты фигуры
    \param gameInfo Структура с игровым полем
    \return Был ли произведен поворот из второго положения в третье
*/
int rotate_T_first(Tetramino *current, GameInfo_t *gameInfo);

/*!

    \brief Расчёт поворота для фигуры T. Вторые две формы

    \param current Координаты фигуры
    \param gameInfo Структура с игровым полем
*/
void rotate_T_second(Tetramino *current, GameInfo_t *gameInfo);

/*!

    \brief Расчёт поворота для фигуры T

    \param current Координаты фигуры
    \param gameInfo Структура с игровым полем
*/
void rotate_T(Tetramino *current, GameInfo_t *gameInfo);

/*!

    \brief Расчёт поворота для фигуры Z

    \param current Координаты фигуры
    \param gameInfo Структура с игровым полем
*/
void rotate_Z(Tetramino *current, GameInfo_t *gameInfo);

/*!

    \brief Очистка поля от старого положения фигуры

    \param current Координаты текущей фигуры
    \param gameInfo Структура с игровым полем
*/
void clear_backpos(Tetramino *current, GameInfo_t *gameInfo);

#endif  // TETRIS_FSM_H_