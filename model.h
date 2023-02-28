#pragma once
#include <list>

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

class Model
{
  private:
    std::list<Cell> rabbits_;
    std::list<Cell> snake_;

    enum MoveDir
    {
        Up,
        Down,
        Left,
        Right
    } snake_direction;

  public:
    Model()
    {}

    void update();

    void respawnSnake( const Cell& head_cell, int init_length);

    const auto& getRabbits() const { return rabbits_; }
    const auto& getSnake() const { return snake_; }
};


