#include "tetris.h"

tetris_state game_loop(GameInfo_t *gameInfo, UserAction_t sig) {
  static tetris_state state;
  static Tetramino current;
  static block nextBlock;
  static bool fallTime;
  static clock_t clock1;
  if (gameInfo == NULL) {
    fallTime = 0;
    clock1 = clock();
    nextBlock = rand() % 7;
    state = SPAWN;
    current.rotate_state = 0;
    current.type = 0;
    current.x1 = 0;
    current.x2 = 0;
    current.x3 = 0;
    current.x4 = 0;
    current.y1 = 0;
    current.y2 = 0;
    current.y3 = 0;
    current.y4 = 0;
    get_state(&state);
    get_current(&current);
    get_nextBlock(&nextBlock);
    get_fallTime(&fallTime);
  } else {
    get_gameInfo(gameInfo);
    if (state == START || state == MOVING || state == GAMEOVER ||
        state == PAUSE) {
    }
    clock_t clock2 = clock();
    if (clock2 - clock1 >= 12000 - ((clock_t)gameInfo->speed * 150 + 10000)) {
      clock1 = clock2;
      fallTime = 1;
      get_fallTime(&fallTime);
    }
    userInput(sig, 1);
    fallTime = 0;
    get_fallTime(&fallTime);
  }
  return state;
}