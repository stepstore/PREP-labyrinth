//
// Created by tsv on 09.05.16.
//

#ifndef LABYRINTH_RUNNER_HPP
#define LABYRINTH_RUNNER_HPP

//#include <vector>
#include "RunnerBase.hpp"

//using namespace std;


class Runner : public RunnerBase {
    Status last_status; // 0-UP -1-левый 1-правый повороты

    int turn_counter=0;

    bool hit=false;

    Direction last_face=Direction ::DOWN;

    Direction face=Direction ::DOWN;

    void rotate_right();

    void rotate_left();

    BlockType check_front();

    Direction go_forward();

    BlockType check_left(Status& status, Direction& target_face);

    bool rotation_posibility();

    Direction generate_step();

    bool check_exit(Direction& move);
public:
    Direction step();

    //void set_current_status(const Status& new_status);
};


#endif //LABYRINTH_RUNNER_HPP
