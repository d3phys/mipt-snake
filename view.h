#pragma once
#include <cstdio>
#include <cstdlib>
#include <string>

class View
{
  public:

    static View* get(const std::string& name);
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


