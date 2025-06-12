#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <termios.h>
#include <vector>
#include "view.h"
#include "gameObject.h"
#include "RPSGameObject.h"
struct end {};
class Controller{

public:
       
    Controller(View&);
    void run();
private:
    bool conti = 1;
    void PCO();
    void handleInput(int);
    void update();

    // Model
    std::vector<GameObject*> _objs;
    GameObject* _player = nullptr;

    // View
    View& _view; 
};

static struct termios old_termios, new_termios;
void reset_terminal();
void configure_terminal();
int read_input();

#endif
