//
// Created by tsv on 09.05.16.
//

#include "Runner.hpp"
Direction Runner::generateDown() {
    if (current_status.right != BlockType::WALL) return Direction::RIGHT;

    else if (current_status.down != BlockType::WALL) return Direction::DOWN;

    else if (current_status.left != BlockType::WALL) return Direction::LEFT;

    else if (current_status.right != BlockType::WALL) return Direction::RIGHT;
}

Direction Runner::generateUp() {
    if (current_status.left != BlockType::WALL) return Direction::LEFT;

    else if (current_status.up != BlockType::WALL) return Direction::UP;

    else if (current_status.right != BlockType::WALL) return Direction::RIGHT;

    else if (current_status.down != BlockType::WALL) return Direction::DOWN;

}

Direction Runner::generateLeft() {
    if (current_status.down != BlockType::WALL) return Direction::DOWN;

    else if (current_status.left != BlockType::WALL) return Direction::LEFT;

    else if (current_status.up != BlockType::WALL) return Direction::UP;

    else if (current_status.right != BlockType::WALL) return Direction::RIGHT;
}

Direction Runner::generateRight() {
    if (current_status.up != BlockType::WALL) return Direction::UP;

    else if (current_status.right != BlockType::WALL) return Direction::RIGHT;

    else if (current_status.down != BlockType::WALL) return Direction::DOWN;

    else if (current_status.left != BlockType::WALL) return Direction::LEFT;
}

void Runner::generatrInitial() {
    if(current_status.down==BlockType::WALL) {
        last = Direction::LEFT;
        return;
    }
    else if(current_status.left==BlockType::WALL) {
        last = Direction::UP;
        return;
    }
    else if(current_status.up==BlockType::WALL) {
        last = Direction::RIGHT;
        return;
    }
    else if(current_status.right==BlockType::WALL) {
        last = Direction::DOWN;
        return;
    }
}

void Runner::set_current_status(const Status& new_status) {
    current_status = new_status;
    if(firstDone==false) {
        generatrInitial();
        firstDone=true;
    }
}

Direction Runner::step() {
    Direction move;
    if (last == Direction::DOWN) {
        move = generateDown();
    }
    else if (last == Direction::UP) {
        move = generateUp();
    }
    else if (last == Direction::LEFT) {
        move = generateLeft();
    }
    else move = generateRight();
    last=move;
    return move;
}
