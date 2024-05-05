CC = gcc
CFLAGS=-Wall -Werror -Wextra -std=c11 -I brick_game/tetris -I gui/cli -Wpedantic
#CFLAGS=-Wall -Werror -Wextra -O2 -pedantic -std=c11 -Wshadow -Wlogical-op -Wshift-overflow=2 \
			-Wduplicated-cond -Wcast-align -Wfloat-equal -Wconversion -Wcast-qual -D_GLIBCXX_DEBUG \
			-D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined \
			-fno-sanitize-recover -fstack-protector -fanalyzer

POSIX=-D_POSIX_C_SOURCE=200809L

TESTS=$(wildcard ./unit_tests/*.c)
OBJ_FSM := tetris.o tetris_fsm.o tetris_backend.o
OBJ_CLI := brick_game_frontend.o

INSTALL_DIR = /usr/local/bin

VERSION = 1.0
TARGET = tetris
DIST_DIR = $(TARGET)-$(VERSION)
DIST_SOURCES = ./Makefile ./unit_tests ./gui ./brick_game

all: clean tetris

install: clean tetris
	cp tetris $(INSTALL_DIR)

unistall:
	rm -f $(INSTALL_DIR)/tetris

dist: clean 
	mkdir -p $(DIST_DIR)
	cp -r $(DIST_SOURCES) $(DIST_DIR)
	tar -czf $(DIST_DIR).tar.gz $(DIST_DIR)
	rm -rf $(DIST_DIR)

dvi: clean
	doxygen

clean:
	rm -rf *.a *.o *.gcno *.gcda unit_test *.css *.html *.gcov tetris *.txt ./doxygen

rebuild: clean all

tetris: tetris.a $(OBJ_CLI) main.o
	$(CC) $(CFLAGS) $(POSIX) $^ -o $@ tetris.a -lncurses

%.o: brick_game/tetris/%.c
	$(CC) $(CFLAGS) $(POSIX) -c $< -o $@

%.o: brick_game/%.c
	$(CC) $(CFLAGS) $(POSIX) -c $< -o $@

%.o: gui/cli/%.c
	$(CC) $(CFLAGS) $(POSIX) -c $< -o $@

%.o: brick_game/%.c
	$(CC) $(CFLAGS) $(POSIX) -c $< -o $@

tetris.a: $(OBJ_FSM)
	ar rc tetris.a $(OBJ_FSM)
	ranlib tetris.a

test: clean
	$(CC) $(CFLAGS) $(POSIX) $(TESTS) -c 
	$(CC) $(CFLAGS) $(POSIX) -o unit_test *.o ./brick_game/tetris/*.c --coverage -lcheck -lsubunit -lm
	chmod +x unit_test
	./unit_test

gcov_report: clean test
	gcov *.gcda
	gcovr
	gcovr --html-details -o report.html -g

format:
	clang-format -n ./brick_game/tetris/*.h ./brick_game/tetris/*.c ./gui/cli/*.c ./gui/cli/*.h ./unit_tests/*.h ./unit_tests/*.c ./brick_game/*.c ./brick_game/*.h

formati:
	clang-format -i ./brick_game/tetris/*.h ./brick_game/tetris/*.c ./gui/cli/*.c ./gui/cli/*.h ./unit_tests/*.h ./unit_tests/*.c ./brick_game/*.c ./brick_game/*.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --std=c11 ./brick_game/tetris/*.h ./brick_game/tetris/*.c ./gui/cli/*.c ./gui/cli/*.h ./unit_tests/*.h ./unit_tests/*.c ./brick_game/*.c ./brick_game/*.h

valgrind:
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s  ./unit_test