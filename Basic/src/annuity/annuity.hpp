#include <math.h>
#include <iostream>

#ifndef __ANNUITY__
#define __ANNUITY__

namespace liv1 {

    #define PI (3.1415926535897932384626433832795028841971693994L )
    #define E (2.7182818284590452353602874713526624977572470937L )
    
    enum Cashflow 
        {
        AFTERWARD, //   s, a
        FORWARD,   // ¨ s, a
        CONTINUES, // - s, a
        NORMAL
        };
    
    enum Value
        {
        ACCUMULATED,
        RETROSPECTIVE
        };

     double interest(
        Value v,
        Cashflow cf,
        double interest, 
        int termin_year, 
        int accural_of_interest=1
    );

    double accumulated( // s
        Cashflow cf, 
        double k0, 
        double interest, 
        int termin_year,
        int accural_of_interest=1
    ); 

    double retrospective( // a
        Cashflow cf, 
        double kn,
        double interest, 
        int termin_year,
        int accural_of_interest=1
    );

   
};

#endif