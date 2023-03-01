#pragma once
#include <cstdio>
#include <cstdlib>
#include <string>
#include <memory>
#include <functional>
#include <algorithm>
#include "model.h"
#include "boost.h"

// poll select in main loop
// read after poll
//
struct Size
{
    int width;
    int height;
};

enum class KeyCode
{
    Left,
    Right,
    Up,
    Down,
};

class View
{
  public:
    static View* get( const std::string& name = "");

  public:
    virtual void drawStatic() = 0;
    virtual void drawDynamic( const Model& model) = 0;
    virtual void clear() = 0;

    using KeyHandler = void (KeyCode key);
    virtual void setOnKey( const std::function<KeyHandler>& action);

    virtual Size getWindowSize() const = 0;
    virtual ~View() {}

  private:
    virtual void setWindowSize( const Size& size) = 0;
};

class GraphicsView
  : public View
{
  public:
    virtual void drawStatic() override;
    virtual Size getWindowSize() const override {};

  private:
    virtual void setWindowSize( const Size&) override {};
};

template <typename THandler, typename Args>
class Event
{
  public:
    using Function = std::function<THandler>;

    void subscribe( Function func) { subscribers_.push_back( func); }
    void invoke( Args arg)
    {
        for ( auto&& sub : subscribers_ )
        {
            sub( arg);
        }
    };

  private:
    std::vector<Function> subscribers_;
};

class TextView final
  : public View
{
  using ascii_t = char;

  public:
    TextView();
    ~TextView();

    virtual void drawStatic() override;
    virtual void drawDynamic( const Model& model) override;
    virtual void clear() override;

    virtual void setOnKey( const std::function<KeyHandler>& action) override;

    void home();
    void drawCell( const Cell& cell, const char* utf);
    void clearCell( const Cell& cell);

    void drawHorizontalLine( const Cell& start, int length, const char* utf);
    void drawVerticalLine(   const Cell& start, int length, const char* utf);

  private:
    Size window_size_;
    Event<KeyHandler, int> key_event_;

  public:
    virtual Size getWindowSize() const override;
  private:
    virtual void setWindowSize( const Size& size) override;
    friend void tui_ResizeHandler( int);
};


