
#include "Runner.hpp"

//нет ли 3ки в окрестности
bool Runner::check_exit(Direction &move) {
    if (current_status.right == BlockType::EXIT) {
        move = Direction::RIGHT;
        return true;
    }
    else if (current_status.down == BlockType::EXIT) {
        move = Direction::DOWN;
        return true;
    }
    else if (current_status.left == BlockType::EXIT) {
        move = Direction::LEFT;
        return true;
    }
    else if (current_status.up == BlockType::EXIT) {
        move = Direction::UP;
        return true;
    }
    return false;
}
//
void Runner::rotate_right() {
    if (face == Direction::UP) {
        face = Direction::RIGHT;
        ++turn_counter;
        return;
    }
    else if (face == Direction::RIGHT) {
        face = Direction::DOWN;
        ++turn_counter;
        return;
    }
    else if (face == Direction::DOWN) {
        face = Direction::LEFT;
        ++turn_counter;
        return;
    }
    else if (face == Direction::LEFT) {
        face = Direction::UP;
        ++turn_counter;
        return;
    }
}
//
void Runner::rotate_left() {
    if (face == Direction::UP) {
        face = Direction::LEFT;
        --turn_counter;
        return;
    }
    else if (face == Direction::RIGHT) {
        face = Direction::UP;
        --turn_counter;
        return;
    }
    else if (face == Direction::DOWN) {
        face = Direction::RIGHT;
        --turn_counter;
        return;
    }
    else if (face == Direction::LEFT) {
        face = Direction::DOWN;
        --turn_counter;
        return;
    }
}
//
BlockType Runner::check_front() {
    if (face == Direction::UP) return current_status.up;
    else if (face == Direction::RIGHT) return current_status.right;
    else if (face == Direction::LEFT) return current_status.left;
    else if (face == Direction::DOWN) return current_status.down;
}
//
BlockType Runner::check_left(Status &status, Direction &target_face) {
    if (target_face == Direction::UP) {
        return status.left;
    }
    else if (target_face == Direction::RIGHT) {
        return status.up;
    }
    else if (target_face == Direction::LEFT) {
        return status.down;
    }
    else if (target_face == Direction::DOWN) {
        return status.right;
    }
}
//
bool Runner::rotation_posibility() {
    BlockType cur_left = check_left(current_status, face);
    BlockType last_left = check_left(last_status, last_face);

    if (cur_left != BlockType::WALL
        && last_left == BlockType::WALL) {
        return true;
    }
    else return false;
}
//
Direction Runner::go_forward() {
    if (face == Direction::UP) return Direction::UP;
    else if (face == Direction::RIGHT) return Direction::RIGHT;
    else if (face == Direction::LEFT) return Direction::LEFT;
    else if (face == Direction::DOWN) return Direction::DOWN;
}
//
Direction Runner::generate_step() {
    Direction move;
    //сымый простой кейс, мы всегда стараемся ползти вперед
    if (hit == false && current_status.up != BlockType::WALL) {
        move = go_forward();
    }
        //если уперлись в стену тупо повернем вправо
    else if (hit == false && current_status.up == BlockType::WALL) {
        hit = true;
        rotate_right();
        //если мы повернулись и стены там нет, все ок туда и идем
        /* 1
           0 0
         */

        if (check_front() != BlockType::WALL) {
            move = go_forward();
        }
            //в ином случае повернем еще направо  и поползем
            /*
             1
             0 1
             */
        else {
            rotate_right();
            move = go_forward();
        }
    }
        //тут описан обход стены в правом направлении
    else if (hit == true) {
        //тут чекнем возможность левого поворота
        //он возможен, когда на прошлом ходу по левую руку была 1ка, а сейчас по левую руку 0

        /*
         1 0
         0 0
         мы во второй строке втором нуле, о предъидущем положении мы помним
         */
        if (rotation_posibility() == true) {
            rotate_left();
            move = go_forward();
        }
            //если он невозможен
        else {
            //если спереди все чисто
            /*
              1 1
              0 0
             */
            if (check_front() != BlockType::WALL) {
                move = go_forward();
            }
            //теперь  обработаю случай с тупиком
            /*
              1 1
              1 0
             */
            if (check_front() == BlockType::WALL) {
                //повернем направо
                rotate_right();
                //если там тупика нет то все ок
                /*
                1 1
                1 0 0
               */
                if (check_front() != BlockType::WALL) {
                    move = go_forward();
                }
                    //в ином случае повернем еще направо  и поползем назад
                    /*
                     1 1
                     1 0 1
                    */
                else {
                    rotate_right();
                    move = go_forward();
                }
            }
        }
        // надо проверить, обошли ли мы преграду
        if (turn_counter == 0) {
            hit = false;
        }
    }

    last_face = face;
    last_status = current_status;
    return move;
}

Direction Runner::step() {
    Direction move;
    bool exit = check_exit(move);
    if (exit == false) {
        move = generate_step();
    }
    return move;

}