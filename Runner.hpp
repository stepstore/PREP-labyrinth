//
// Created by tsv on 09.05.16.
//

#ifndef LABYRINTH_RUNNER_HPP
#define LABYRINTH_RUNNER_HPP

#include <vector>
#include "RunnerBase.hpp"

using namespace std;


class Runner : public RunnerBase {
    bool firstDone=false;

    void generatrInitial();

    Direction last;

    Direction generateDown();

    Direction generateUp();

    Direction generateLeft();

    Direction generateRight();

public:
    Direction step();

    void set_current_status(const Status& new_status);
};


#endif //LABYRINTH_RUNNER_HPP
