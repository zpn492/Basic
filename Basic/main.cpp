#include "src/sock/sock.h"

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

#include "src/http/http.hpp"

/* markov model */
#include "src/markov/markov.hpp"

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

void Annuity()
    {
    
    std::cout << liv1::accumulated(liv1::NORMAL, 10000, 0.08, 10) << std::endl;

    std::cout << liv1::retrospective(liv1::NORMAL, 1, 0.045, 30) << std::endl;

    std::cout << liv1::accumulated(liv1::AFTERWARD, 10000, 0.08, 10) << std::endl;

    std::cout << liv1::retrospective(liv1::AFTERWARD, 10000, 0.08, 10) << std::endl;

    std::cout << liv1::accumulated(liv1::FORWARD, 10000, 0.08, 10) << std::endl;

    std::cout << liv1::retrospective(liv1::FORWARD, 10000, 0.08, 10) << std::endl;

    std::cout << liv1::retrospective(liv1::AFTERWARD, 1000, 0.1, 10, 12) << std::endl;
    
    std::cout << liv1::accumulated(liv1::CONTINUES, 100, 0.1, 1) << std::endl;
    
    };

using namespace linalg;

int main(int argc, char *args[])
    {
    Annuity();
    return 0;
    };