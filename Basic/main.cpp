/* Handles all standard includes */
#include "SimpleJust.h"

/* filehandler */
#include "lib/filehandler/filehandler.h"
#include "lib/logger/logger.h"

/* WIN - HTTP server */
#include "lib/http/http.hpp"

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