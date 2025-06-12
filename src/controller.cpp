#include <iostream>
#include <ctime>
#include <thread>
#include <unistd.h>
#include <termios.h>

#include "environment.h"
#include "controller.h"
#include "gameObjectFactory.h"
#include "RPSGameObject.h"
#include "iconFactory.h"
#include <random>

Controller::Controller(View& view) : _view(view){
}

void Controller::run() {
    // initial setup
    std::cin.tie(0);
    std::ios::sync_with_stdio(0);
    configure_terminal();
    srand(time(0));
    // init state
    int input = -1;
    clock_t start, end;
    int numObjs=7;
    for(int i=0;i<numObjs;i++){
        int width=1, height=1;
        for(RPSType x : { ROCK, PAPER, SCISSORS }) {
            _objs.push_back(GameObjectFactory::createGameObject(Position{rand()%GAME_WINDOW_HEIGHT, rand()%GAME_WINDOW_WIDTH}, x).release());
        }
    }
    _player = _objs.front(); // last object is the player
    _player->setplayer(true); // set player type to ROCK
    _player->update();
    // Main loop
    while (true) {
        start = clock();
        // game loop goes here
        input = read_input();
        // ESC to exit program
        if(input==27)break;
        this->handleInput(input);
        if(conti==0) continue;
        update();
        _view.resetLatest();
        
        for(GameObject* obj : _objs) 
        {

            obj->update();
            _view.updateGameObject(obj);

        }

        _view.render();


        end = clock();

        // frame rate normalization
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        if (time_taken > SPF) continue;
        int frameDelay = int((SPF - time_taken) * 400); // 0.01 seconds
        if(frameDelay > 0) std::this_thread::sleep_for(std::chrono::milliseconds(frameDelay)); // frame delay
    }

}



void Controller::handleInput(int keyInput){

    // If there is no input, do nothing.
    if(keyInput==-1)return;
    if(conti==0 && (keyInput!='p') && (keyInput!='P'))  return;
    switch(keyInput) {
        case 'p': case 'P': // ESC key
            conti ^=1;
            break;
        case 9:
            PCO();
            break;
        case 'w': case 'W':
            _player->move(0, -1);
            break;
        case 's': case 'S':
            _player->move(0, 1);
            break;
        case 'a': case 'A':
            _player->move(-1, 0);
            break;
        case 'd': case 'D':
            _player->move(1, 0);
            break;
    }
    
    // TODO 
    // handle key events.
}

void Controller::PCO(){

    int num=0;
    for(auto& a : _objs) {
        RPSGameObject* obj = dynamic_cast<RPSGameObject*>(a);
        if(obj->getType() == ROCK&&obj!=_player) num++;
    }
    _player->setplayer(false);
    if(num==0) return;
    int change = rand()%num+1;
     // reset player
    for(auto& a:_objs) {
        RPSGameObject* obj = dynamic_cast<RPSGameObject*>(a);
        if(obj->getType() == ROCK && change>0) {
            if(obj!=_player) change--;
            if(change==0){
                _player=a;
                _player->setplayer(true); // set player to ROCK
            }
        }
    }

}
void Controller::update(){
    int pnum=0, snum=0, rnum=0;
    for(int i=0; i<_objs.size(); ++i){
        for(int j=i+1; j<_objs.size(); ++j){
            auto collider1 = _objs[i]->getCollider();
            auto collider2 = _objs[j]->getCollider();
            if(collider1 && collider2 && collider1->intersect(collider2)) {
                if(collider1->onCollision(collider2)) PCO();
                if(collider2->onCollision(collider1)) PCO();
            }
        }
    }
    for(auto& obj : _objs) {
        RPSGameObject* rpsObj = dynamic_cast<RPSGameObject*>(obj);
        switch (rpsObj->getType()) {
            case ROCK: rnum++; break;
            case PAPER: pnum++; break;
            case SCISSORS: snum++; break;
        }
        if(obj!=_player) obj->move(rand()%3-1, rand()%3-1);
    }
    if(pnum==0){
        std::cout<<"Game Over! Scissors win!"<<std::endl;
        throw end{};
    }
    if(snum==0){
        std::cout<<"Game Over! Rock win!"<<std::endl;
        throw end{};
    }
    if(rnum==0){
        std::cout<<"Game Over! Paper win!"<<std::endl;
        throw end{};
    }
}
void reset_terminal() {
    printf("\e[m"); // reset color changes
    printf("\e[?25h"); // show cursor
    fflush(stdout);
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}

// terminal initial configuration setup
void configure_terminal() {
    tcgetattr(STDIN_FILENO, &old_termios);
	new_termios = old_termios; // save it to be able to reset on exit
    
    new_termios.c_lflag &= ~(ICANON | ECHO); // turn off echo + non-canonical mode
    new_termios.c_cc[VMIN] = 0;
    new_termios.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    printf("\e[?25l"); // hide cursor
    std::atexit(reset_terminal);
}


int read_input() {
    fflush(stdout);
   	char buf[4096]; // maximum input buffer
	int n = read(STDIN_FILENO, buf, sizeof(buf));
    return n > 0 ? buf[n - 1] : -1;
}

