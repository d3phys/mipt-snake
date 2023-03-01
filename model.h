#pragma once
#include <list>
#include <vector>
#include <deque>
#include <cstdio>

// std::function<int (int)>
// std::bind<>
// libevent can see

struct Cell
{
    int col;
    int row;

    Cell& operator+=( const Cell& cell)
    {
        col += cell.col;
        row += cell.row;
        return *this;
    }

    bool operator==( const Cell& cell) const
    {
        return ( col == cell.col ) && ( row == cell.row );
    }

    bool operator<(const Cell& cell) const
    {
        return ( col < cell.col ) || ( row < cell.row );
    }

    bool operator>(const Cell& cell) const
    {
        return ( col > cell.col ) || ( row > cell.row );
    }
};

class Snake
{
  public:
    enum class Direction
    {
        Up,
        Down,
        Left,
        Right
    };

  public:

    Snake( Cell head = { 15, 15}, std::size_t length = 20, Direction direction = Direction::Right)
    {
        setDirection( direction);
        cells_.push_front( head);
        for ( std::size_t i = 0; i != length - 1; ++i )
        {
            grow();
        }

        setDirection( Direction::Up);
    }

    void grow() { cells_.push_front( cells_.front() += direction_); }
    void shrink() { cells_.pop_back(); }

    const auto& getCells() const { return cells_; }
    void setDirection( Direction direction)
    {
        switch ( direction )
        {
          case Direction::Up:
            direction_ = {  0,  1 };
            break;
          case Direction::Down:
            direction_ = {  0, -1 };
            break;
          case Direction::Left:
            direction_ = { -1,  0 };
            break;
          case Direction::Right:
            direction_ = {  1,  0 };
            break;
          default:
            break;
        }
    }

    void move()
    {
        for ( auto it = cells_.rbegin();
              it != std::prev( cells_.rend());
              ++it )
        {
            *it = *std::next( it);
            std::fprintf( stderr, "cell: [%d %d]\n", it->col, it->row);
        }

        cells_.front() += direction_;
        std::fprintf(stderr, "\n\n\n\n");
    }

  private:
    Cell direction_;
    std::deque<Cell> cells_;
};

class Model
{
  private:
    std::list<Cell> rabbits_;
    Snake snake_;

  public:
    Model()
    {}

    void update();

    void respawnSnake( const Cell& head_cell, int init_length);

    const auto& getRabbits() const { return rabbits_; }
    const auto& getSnake() const { return snake_; }
};


