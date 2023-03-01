#include "view.h"
#include <csignal>
#include <sys/ioctl.h>
#include <exception>
#include <system_error>
#include <algorithm>

static Size
tui_GetWindowSize()
{
    struct winsize winsz{};
    int error = ioctl( 1, TIOCGWINSZ, &winsz);
    if ( error == -1 )
        return perror( "ioctl failure"), Size{};

    return Size{ winsz.ws_col, winsz.ws_row};
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

Size
TextView::getWindowSize() const
{
    return window_size_;
}

void
TextView::setWindowSize( const Size& size)
{
    window_size_ = size;
}

void
TextView::drawDynamic( const Model& model)
{
    static std::deque<Cell> old_snake {};
    const auto& new_snake = model.getSnake().getCells();

    std::deque<Cell> intersect {};
    std::set_intersection( old_snake.begin(), old_snake.end(),
                           new_snake.begin(), new_snake.end(),
                           std::back_inserter( intersect));

    std::deque<Cell> to_clear {};
    std::set_difference( old_snake.begin(), old_snake.end(),
                         intersect.begin(), intersect.end(),
                         std::back_inserter( to_clear));

    for ( auto&& cell : to_clear )
    {
        clearCell( cell);
    }

    std::set_difference( new_snake.begin(), new_snake.end(),
                         intersect.begin(), intersect.end(),
                         old_snake.begin());

    const auto& snake = old_snake;

    for ( auto&& cell : snake )
    {
        drawCell( cell, "%");
    }

    for ( auto&& cell : model.getRabbits() )
    {
        drawCell( cell, "🐇");
    }

    home();
    std::fflush( stdout);

    old_snake = new_snake;
}

void
TextView::drawStatic()
{
    Size size = getWindowSize();

    drawHorizontalLine( {2, 1}, size.width, "═");
    drawHorizontalLine( {2, size.height - 1}, size.width, "═");
    drawVerticalLine( {1, 2}, size.height, "║");
    drawVerticalLine( {size.width, 1}, size.height, "║");

    drawCell( {1, 1}, "╔");
    drawCell( {size.width, 1}, "╗");
    drawCell( {1, size.height - 1}, "╚");
    drawCell( {size.width, size.height - 1}, "╝");

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
TextView::drawCell( const Cell& cell,
                    const char* utf)
{
    std::printf( "\e[%d;%d;H", cell.row, cell.col);
    std::printf( "%s", utf);
}

void
TextView::clearCell( const Cell& cell)
{
    std::printf( "\e[%d;%d;H", cell.row, cell.col);
    std::printf( " ");
}

void
TextView::drawHorizontalLine( const Cell& start,
                              int length,
                              const char* utf)
{
    for (int x = start.col; x < length && x <= getWindowSize().width; x++)
    {
        drawCell( {x, start.row}, utf);
    }
}

void
TextView::drawVerticalLine( const Cell& start,
                            int length,
                            const char* utf)
{
    for (int y = start.row; y < length && y <= getWindowSize().height; y++)
    {
        drawCell( {start.col, y}, utf);
    }
}

void
TextView::setOnKey( const std::function<KeyHandler>& action)
{
    key_event_.subscribe( action);
}






