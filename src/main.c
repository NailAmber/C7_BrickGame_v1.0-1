#include "./brick_game/tetris/tetris.h"
#include "./gui/cli/brick_game_frontend.h"

void tetris_game();

/*!

    \brief Точка входа в игровую консоль
*/
int main() {
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  timeout(40);
  srand((unsigned int)time(NULL));
  int selectedGame = 0;
  while (1) {
    select_game(selectedGame);
    UserAction_t sig = get_signal(getch());
    if (sig == Down && selectedGame < 2) {
      selectedGame++;
    }

    if (sig == Up && selectedGame > 0) {
      selectedGame--;
    }

    if (sig == Action && selectedGame == 0) {
      break;
    }
    if (sig == Terminate) {
      selectedGame = -1;
      break;
    }
  }
  clear_select_game_screen();
  print_overlay();
  while (1) {
    UserAction_t sig = get_signal(getch());
    if (sig == Action) {
      break;
    }
  }
  if (selectedGame == 0) {
    tetris_game();
  }
  endwin();
  return 0;
}

/*!

    \brief Вход в игру Тетрис
*/
void tetris_game() {
  GameInfo_t gameInfo;
  infoInit(&gameInfo);
  change_GameInfo_t(&gameInfo);
  int state = -1;
  UserAction_t sig = -1;
  game_loop(NULL, sig);

  while (state != EXIT_STATE && state != GAMEOVER) {
    if (state == START || state == MOVING || state == PAUSE) {
      sig = get_signal(getch());
    }

    state = game_loop(&gameInfo, sig);
    updateCurrentState();
  }
  if (state == GAMEOVER) {
    print_banner(&gameInfo);
    while (1) {
      sig = get_signal(getch());
      if (sig == Terminate) {
        break;
      }
    }
  }

  infoFree(&gameInfo);
}