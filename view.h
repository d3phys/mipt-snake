#pragma once
#include <cstdio>
#include <cstdlib>
#include <string>
#include "boost.h"

struct Point
{
  public:
    int x, y;

    Point(const Point&) = default;
    Point& operator=(const Point&) = default;
};

class View
{
  public:
    static View* get( const std::string& name = "");

  public:
    virtual void drawStatic() = 0;
    virtual void drawDynamic() = 0;
    virtual void clear() = 0;
    virtual void home() = 0;
    virtual void drawPoint( const Point& point) = 0;
    virtual void drawHorizontalLine( const Point& start, int length) = 0;
    virtual void drawVerticalLine(   const Point& start, int length) = 0;

    virtual std::pair<int, int> getWindowSize() const = 0;
    virtual ~View() {}

  private:
    virtual void setWindowSize( const std::pair<int, int>& size) = 0;
};

class GraphicsView
  : public View
{
  public:
    virtual void drawStatic() override;
    virtual std::pair<int, int> getWindowSize() const override {};

  private:
    virtual void setWindowSize( const std::pair<int, int>& size) override {};
};

class TextView
  : public View
{
  using ascii_t = char;

  public:
    TextView();
    ~TextView();

    virtual void drawStatic() override;
    virtual void drawDynamic() override;
    virtual void clear() override;
    virtual void home() override;
    virtual void drawPoint( const Point& point) override;
    virtual void drawHorizontalLine( const Point& start, int length) override;
    virtual void drawVerticalLine(   const Point& start, int length) override;

  private:
    std::pair<int, int> window_size_;

  public:
    virtual std::pair<int, int> getWindowSize() const override;
  private:
    virtual void setWindowSize( const std::pair<int, int>& size) override;
    friend void tui_ResizeHandler( int);
};


