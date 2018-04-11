/* WIN - HTTP server */
#include "lib/http/http.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <exception>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <conio.h> /* getch() */

/* filehandler */
#include "lib/filehandler/filehandler.h"
#include "lib/logger/logger.h"

/* linalg */
#include "lib/matrix/matrix.hpp"
#include "lib/calculator/calculator.hpp"

/* Cashflow, Interest, Mortality */
#include "src/annuity/annuity.hpp"

void HTTPServer()
    {
    HTTP http; http.start(80, "127.0.0.1", "data/public_html");
    };

using namespace linalg;
using namespace liv1;

int main(int argc, char *args[])
    {   
    return 0;
    };