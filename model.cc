#include <list>
#include <cassert>
#include "model.h"


// Line discipline
// Must be off line_discipline = off
// termios interface
// tcgetattr(fd, &struct)
// tcsetattr(fd, &struct) -- must disable bufferization and disable Ctrl-C
// 0 - int
// terminal window
// clmakeraw save attributes
// arrows: \e[A|B|C|D

void
Model::update()
{
    snake_.move();
}

void
Model::respawnSnake( const Cell& head_cell,
                     int init_length)
{
}

