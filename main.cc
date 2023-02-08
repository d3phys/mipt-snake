#include <cstdio>
#include <unistd.h>
#include <getopt.h>
#include "view.h"

struct Options
{
    bool enable_gui = false;
    bool verbose = false;
};

Options parse_options(int argc, char* argv[]);

int
main(int argc,
     char* argv[])
{
    Options options = parse_options(argc, argv);

    View* view {};
    if (options.enable_gui)
        view = new GraphicsView {};
    else
        view = new TextView {};

    view->draw();
    delete view;
    return 0;
}

Options
parse_options(int argc,
              char* argv[])
{
    /**
     * Redirect long options straight to the short options handlers
     * Note: the last element has to be filled with zeroes.
     */
    static struct option options[] = {
        {"gui",     no_argument, NULL, 'g'},
        {"verbose", no_argument, NULL, 'v'},
        { 0,        0,           0,     0 },
    };

    Options opts {};
    int opt = 0;
    while ((opt = getopt_long(argc, argv, "gv", options, NULL)) != -1) {
        switch(opt) {
        case 'v':
                opts.verbose = true;
                break;
        case 'g':
                opts.enable_gui = true;
                break;
        default:
                break;
        }
    }

    return opts;
}


