#include <math.h>
#include <iostream>

#ifndef __ANNUITY__
#define __ANNUITY__

namespace liv1 {

    #define PI (3.1415926535897932384626433832795028841971693994L )
    
    #define E (2.7182818284590452353602874713526624977572470937L )

    /* Gompertz-Makeham parameters */

    #define MALE_DEATH_ALPHA 0.0005               
    #define MALE_DEATH_BETA 0.00007586
    #define MALE_DEATH_GAMMA log(1.09144)

    #define MALE_DISABILITY_ALPHA 0.0004               
    #define MALE_DISABILITY_BETA 0.00003467
    #define MALE_DISABILITY_GAMMA log(1.14815)  

    /* 4.5 % interest */

    #define R log(1.045)
    
    /* Afterward - Continuous payment
     * First payment is at year 1
     * Last payment at year n, gets no interest.
     *
     * Forward - Continuous payment
     * First payment is at year 0
     * Last payment is at year n - 1
     *
     * Normal - Single payment
     */
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

    /* Calcualtes the interest over n years with interest i */ 
    double interest(
        Value v,
        Cashflow cf,
        double interest, 
        int termin_year, 
        int accural_of_interest=1
    );

    /* Calculates the accumulated value
     * How much is your savings after n years with an interest i and a payment k0
     */    
    double accumulated( // s
        Cashflow cf, 
        double k0, 
        double interest, 
        int termin_year,
        int accural_of_interest=1
    ); 

    /* Calculates the retrospective value
     * How much should you be saving, if you after n years with an interest i and want a payment kn
     */
    double retrospective( // a
        Cashflow cf, 
        double kn,
        double interest, 
        int termin_year,
        int accural_of_interest=1
    );

    /* Gompertz-Makeham
     * Mortality intensity
     */
    double mortality(
        int age
    );   

    /* Gompertz-Makeham
     * Disability intensity
     */
    double disability(
        int age
    );   
};

#endif