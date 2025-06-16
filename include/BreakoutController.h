#ifndef BREAKOUT_CONTROLLER_H
#define BREAKOUT_CONTROLLER_H

#include <vector>
#include <chrono>
#include <thread>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include <cstdio>
#include "BreakoutGameObject.h"
#include "view.h"
#include "BrickGameObject.h"

static struct termios orig_termios;

inline void configure_terminal() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

inline void reset_terminal() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

inline int read_input() {
    int c = -1;
    struct timeval tv = {0L, 0L}; 
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    if (select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0) {
        c = getchar();

        while (select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0) {
            getchar(); 
        }
    }
    return c;
}

// === Game controller ===
struct endGame : public std::exception {};

class BreakoutController {
public:
    explicit BreakoutController(View& view);
    void run();

private:
    void handleInput(int keyInput);
    void update();
    void initializeGame();
    void checkGameOver();

    View& _view;
    std::vector<GameObject*> _objs;
    GameObject* _player = nullptr; // Player-controlled paddle
    GameObject* _ball   = nullptr; // The single ball

    int score = 0;
    bool gameOver = false;
    bool paused   = false;

    const std::chrono::milliseconds frameDuration{16}; // target ~60fps
};

#endif // BREAKOUT_CONTROLLER_H
