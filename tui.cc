#include "view.h"
#include <csignal>
#include <sys/ioctl.h>
#include <exception>
#include <system_error>

static std::pair<int, int>
tui_GetWindowSize()
{
    struct winsize winsz{};
    int error = ioctl( 1, TIOCGWINSZ, &winsz);
    if ( error == -1 )
        return perror( "ioctl failure"), std::pair<int, int>{};

    return std::pair<int, int>{ winsz.ws_row, winsz.ws_col};
}

void
tui_ResizeHandler( int)
{
    TextView* view = static_cast<TextView* >( View::get());
    view->setWindowSize( tui_GetWindowSize());
    view->clear();
    view->drawStatic();
}

TextView::TextView()
  : window_size_ {}
{
    struct sigaction sa{};
    sa.sa_handler = tui_ResizeHandler;
    if ( sigaction(SIGWINCH, &sa, NULL) != 0 )
    {
        throw std::system_error{ errno, std::system_category()};
    }

    setWindowSize( tui_GetWindowSize());
}

TextView::~TextView()
{
    signal(SIGWINCH, SIG_DFL);
}

std::pair<int, int>
TextView::getWindowSize() const
{
    return window_size_;
}

void
TextView::setWindowSize( const std::pair<int, int>& size)
{
    window_size_ = size;
}

void
TextView::drawDynamic()
{
    drawPoint( {2, 2});
    drawPoint( {3, 3});
    drawPoint( {4, 4});
    drawPoint( {5, 5});
    drawPoint( {11, 11});
    drawPoint( {12, 12});
    drawPoint( {13, 13});

    std::fflush( stdout);
}

void
TextView::drawStatic()
{
    std::pair<int, int> size = getWindowSize();
    drawHorizontalLine( {1, 1}, size.second);
    drawHorizontalLine( {1, size.first - 1}, size.second);
    drawVerticalLine( {1, 1}, size.first);
    drawVerticalLine( {size.second, 1}, size.first);

    std::fflush( stdout);
}

void
TextView::clear()
{
    std::printf( "\e[H\e[J");
}

void
TextView::home()
{
    std::printf( "\e[H");
}

void
TextView::drawPoint( const Point& point)
{
    std::printf( "\e[%d;%d;H", point.y, point.x);
    std::printf( "━");
}

void
TextView::drawHorizontalLine( const Point& start, int length)
{
    for (int x = start.x; x < length && x <= getWindowSize().second; x++)
    {
        drawPoint( {x, start.y});
    }
}

void
TextView::drawVerticalLine(   const Point& start, int length)
{
    for (int y = start.y; y < length && y <= getWindowSize().first; y++)
    {
        drawPoint( {start.x, y});
    }
}




