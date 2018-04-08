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

void illustrate()
    {
    std::vector<std::string> labels;
    std::vector<double> data;

    for(int i = 0; i < 10; i++)
        {
        labels.push_back(std::string("T") + filehandler::double_to_string((i+1)/100.0));
        std::cout << liv1::retrospective(liv1::NORMAL, 300000, (i+1)/100.0, 20) << std::endl;
        data.push_back(liv1::retrospective(liv1::NORMAL, 300000, (i+1)/100.0, 20));
        }
    
    filehandler::histogram("data/public_html/js/chart.js", labels, data);
    filehandler::linechart("data/public_html/js/chart.js", labels, data);
    };

using namespace linalg;
using namespace liv1;

int main(int argc, char *args[])
    {
    std::cout << "k0 = " << liv1::accumulated(liv1::NORMAL, 10000, 0.08, 10) << std::endl; 
    std::cout << "kn = " << liv1::retrospective(liv1::NORMAL, 150000, 0.08, 5) << std::endl; 
    return 0;
    };