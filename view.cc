#include <stdexcept>
#include <memory>
#include "view.h"

View*
View::get( const std::string& view_name)
{
    static std::unique_ptr<View> view{};

    if ( view )
        return view.get();

    if ( view_name == ""
         || view_name == "tui" )
    {
        view.reset( new TextView{});
    }
    /*else if ( view_name == "gui" )
    {
        view.reset( new GraphicsView{});
    } else
    */
    else {
        throw std::runtime_error{ "incorrect view name\n"};
    }

    return view.get();
}
