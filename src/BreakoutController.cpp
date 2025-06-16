#include "BreakoutController.h"
#include "environment.h"
#include "gameObjectFactory.h"
#include "BreakoutGameObject.h"
#include "BrickGameObject.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>


inline int delayFactor(int score) {
    constexpr int MAX_FACTOR = 180;   
    constexpr int MIN_FACTOR = 80;    
    int factor = MAX_FACTOR - (score / 5);   
    return std::max(factor, MIN_FACTOR);
}

BreakoutController::BreakoutController(View& view) : _view(view) {}

void BreakoutController::run() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    configure_terminal();
    initializeGame();

    int  input = -1;
    using clock = std::chrono::high_resolution_clock;
    long frameCounter = 0;                    
    int tiem=0;
    while (!gameOver) {
        ++frameCounter;
        auto frameStart = clock::now();

        input = read_input();
        if (input == 27) break;
        handleInput(input);

        if (!paused) {
            for (auto* obj : _objs) {
                if (obj == _ball) {
                    if (frameCounter % 4 == 0) obj->update();
                } else {
                    obj->update();
                }
            }

            auto* ballObj = dynamic_cast<BreakoutGameObject*>(_ball);
            std::vector<GameObject*> toRemove;
            if (ballObj) {
                for (auto* obj : _objs) {
                    if (obj == _ball || obj == _player) continue;
                    if (obj->getCollider() && ballObj->getCollider()->intersect(obj->getCollider())) {
                        if (ballObj->getCollider()->onCollision(obj->getCollider())) {
                            if (auto* brick = dynamic_cast<BrickGameObject*>(obj)) {
                                score += 10;
                                toRemove.push_back(obj);
                            }
                        }
                    }
                }
            }
            for (auto* br : toRemove) {
                _objs.erase(std::remove(_objs.begin(), _objs.end(), br), _objs.end());
                delete br;
            }

            update();
            checkGameOver();
        }

        _view.resetLatest();
        for (auto* obj : _objs) _view.updateGameObject(obj);
        _view.render();

        auto frameEnd  = clock::now();
        auto frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart);
        auto target    = std::chrono::milliseconds(16);       
        auto sleepDur  = (target * delayFactor(score) / 100) - frameTime;
        if (sleepDur.count() > 0)
            std::this_thread::sleep_for(sleepDur);
    }
    if(_objs.size() == 2) std::cout << "Game Over! You Win!" << std::endl;
    else std::cout << "Game Over! You Lose!" << std::endl;
    std::cout << "Score: " << score << std::endl;
    reset_terminal();
    throw endGame();
}


void BreakoutController::handleInput(int keyInput) {
    if (keyInput == -1) return;
    if (paused && keyInput != 'p' && keyInput != 'P') return;
    switch (keyInput) {
        case 'p': case 'P': paused = !paused; break;
        case 'a': case 'A': _player->move(-2, 0); break;
        case 'd': case 'D': _player->move( 2, 0); break;
    }
}

void BreakoutController::update() {
    if (_ball->getCollider()->intersect(_player->getCollider())) {
        _ball->getCollider()->onCollision(_player->getCollider());
        score += 1;
    }

    auto* ballObj = dynamic_cast<BreakoutGameObject*>(_ball);
    if (!ballObj) return;

    int dx, dy; ballObj->getBallDirection(dx, dy);
    Position bp = ballObj->getPosition();

    if (bp.x() <= 0)                           dx = 1;
    else if (bp.x() >= GAME_WINDOW_WIDTH - 1)  dx = -1;
    if (bp.y() <= 0)                           dy = 1;

    ballObj->setDirection(dx, dy);
}

void BreakoutController::initializeGame() {
    _objs.clear();
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    _player = GameObjectFactory::createBreakoutObject(
        Position{GAME_WINDOW_HEIGHT - 2, GAME_WINDOW_WIDTH*5 / 6}, PADDLE).release();
    _player->setplayer(true);
    _objs.push_back(_player);

    _ball = GameObjectFactory::createBreakoutObject(
        Position{GAME_WINDOW_HEIGHT - 3, GAME_WINDOW_WIDTH / 2}, BALL).release();
    _objs.push_back(_ball);

    // 隨機磚塊
    for (int row = 2; row < 20; ++row) {
        for (int col = 2; col < GAME_WINDOW_WIDTH - 12; col += 2) {
            if (std::rand() % 2) {
                _objs.push_back(new BrickGameObject(Position{row, col}, false));
            }
        }
    }

    score = 0; gameOver = false; paused = false;
}

void BreakoutController::checkGameOver() {
    if (auto* ballObj = dynamic_cast<BreakoutGameObject*>(_ball))
        if (ballObj->getPosition().y() >= GAME_WINDOW_HEIGHT - 1)
            gameOver = true;
}
