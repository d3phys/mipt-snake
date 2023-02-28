#include <cstdio>
#include <unistd.h>
#include <getopt.h>
#include <iostream>
#include <sys/ioctl.h>
#include "view.h"
#include <signal.h>

struct Options
{
    std::string view_name;
};

Options parse_options( int argc, char* argv[]);

int
main( int argc,
      char* argv[])
{
    try
    {
        Options options = parse_options( argc, argv);
        View* view = View::get( options.view_name);

        view->clear();
        view->drawStatic();

        Model model{};
        model.respawnSnake( {10, 5}, 10);

        for ( ;; )
        {
            model.update();
            view->drawDynamic( model);
            __asm__ volatile( "nop");
            usleep(500000);
        }

    } catch ( const std::exception& ex )
    {
        std::fprintf( stderr, "Game crash: %s", ex.what());
    }

    return 0;
}

Options
parse_options( int argc,
              char* argv[])
{
    /**
     * Redirect long options straight to the short options handlers
     * Note: the last element has to be filled with zeroes.
     */
    static struct option options[] = {
        {"view",     required_argument, NULL, 'v'},
        { 0,         0,                 0,     0 },
    };

    Options opts{};
    int opt{};
    while ( (opt = getopt_long( argc, argv, "v:", options, NULL)) != -1 )
    {
        switch(opt)
        {
          case 'v':
            opts.view_name = optarg;
            break;
          default:
            break;
        }
    }

    return opts;
}


