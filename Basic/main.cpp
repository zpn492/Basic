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

/* markov model */
#include "src/markov/markov.hpp"

/* Cashflow, Interest, Mortality */
#include "src/annuity/annuity.hpp"

void HTTPServer()
    {
    HTTP http; http.start(80, "127.0.0.1", "data/public_html");
    };

void Markov()
    {
    liv1::Markov markov("data/readings.txt");
    markov.chart("data/public_html/tempo.js");
    markov.graph("");
    };

using namespace linalg;

int main(int argc, char *args[])
    {
    return 0;
    };