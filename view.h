#pragma once
#include <cstdio>

class View
{
  public:
    virtual void draw() = 0;
    virtual ~View() {}
};

class GraphicsView
  : public View
{
  public:
    virtual void draw() override
    {
        std::printf("Not implemented!\n");
    }
};

class TextView
  : public View
{
  public:
    virtual void draw() override
    {
        std::printf("Hello!\n");
    }
};


