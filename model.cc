#include <list>
#include <cassert>
#include "model.h"

void
Model::update()
{
    Cell shift{};

    switch ( snake_direction )
    {
      case MoveDir::Up:
        shift = {  0,  1 };
        break;
      case MoveDir::Down:
        shift = {  0, -1 };
        break;
      case MoveDir::Left:
        shift = { -1,  0 };
        break;
      case MoveDir::Right:
        shift = {  1,  0 };
        break;
      default:
        assert( 0 && "Default statement failure");
        break;
    }

    for ( auto&& cell : snake_ )
    {
        cell += shift;
    }
}

void
Model::respawnSnake( const Cell& head_cell,
                     int init_length)
{
    snake_.clear();
    for ( int i = 0; i != init_length; ++i )
    {
        snake_.push_back( { head_cell.col - i, head_cell.row});
    }

    snake_direction = MoveDir::Right;
}

