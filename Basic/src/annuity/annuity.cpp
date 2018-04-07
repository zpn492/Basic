#include "annuity.hpp"

namespace liv1 {
    double interest(
        Value v,
        Cashflow cf, 
        double interest, 
        int termin_year, 
        int accural_of_interest
    )
        {
        double q, termin, delta; 

        if(accural_of_interest == 1)
            {
            termin = termin_year;
            }
        else
            {
            interest = pow((1+interest ), 1.0/accural_of_interest ) - 1;
            termin = termin_year * accural_of_interest;
            }    

        q = 1 + interest;
        delta = log(1.0 + interest);

        switch(cf)
            {
            case CONTINUOUS:
                {
                switch(v)
                    {
                    case ACCUMULATED:
                        return (pow(E, delta * termin ) - 1 ) / delta;
                    break;
                    case RETROSPECTIVE:
                        return (1 - pow(E, -delta * termin ) - 1 ) / delta;
                    break;
                    }
                }
            break;
            case NORMAL:
                {
                switch(v)
                    {
                    case ACCUMULATED:
                        return pow( q, termin );
                    break;
                    case RETROSPECTIVE:
                        return pow ( q, -termin );
                    break;
                    }
                }
            break;
            case AFTERWARD: 
                {
                switch(v)
                    {
                    case ACCUMULATED: // s
                        {
                        return (pow(E, delta * termin) - 1) / interest;
                        //return (pow(q, termin ) - 1) / interest;
                        }
                    break;
                    case RETROSPECTIVE:  // a
                        {
                        return (1 - pow(E, -delta * termin) ) / interest;
                        //return ( 1 - pow( q, -termin) ) / interest;
                        }
                    break;
                    }
                }
            break;
            case FORWARD: 
                {
                switch(v)
                    {
                    case ACCUMULATED: // s
                        {
                        return (pow(E, delta * (termin+accural_of_interest) ) - q) / interest;
                        //return (pow(q, termin+1 ) - q ) / interest;
                        }
                    break;
                    case RETROSPECTIVE:  // a
                        {
                        return q * (1 - pow(E, -delta * termin) ) / interest;
                        //return (( 1 - pow(q, -termin ) ) / interest ) * q;
                        }
                    break;
                    }
                }
            break;
            }
        return 0;
        };

    double discounting(
        double interest,
        int termin_year
    )
        {
        return pow(E, -interest * termin_year);
        };
    
    double accumulated(
        Cashflow cf, 
        double k0, 
        double interest, 
        int termin_year,
        int accural_of_interest
    )
        {
        return k0 * liv1::interest(ACCUMULATED, cf, interest, termin_year, accural_of_interest);
        };

    double retrospective( 
        Cashflow cf, 
        double kn,
        double interest, 
        int termin_year,
        int accural_of_interest
    )
        {
        return kn * liv1::interest(RETROSPECTIVE, cf, interest, termin_year, accural_of_interest);
        };

    double mortality(
        int age
    )
        {
        return MALE_DEATH_ALPHA + MALE_DEATH_BETA * pow(E, MALE_DEATH_GAMMA*age);
        };

    double disability(
        int age
    )
        {
        return MALE_DISABILITY_ALPHA + MALE_DISABILITY_BETA * pow(E, MALE_DISABILITY_GAMMA*age);
        };
    
    double lx(
        int age
    )
        {
        // exp(-alpha * t - beta * (exp(gamma * t) - 1.0) / gamma)
        return pow(E, -MALE_DEATH_ALPHA * age - MALE_DEATH_BETA * (pow(E, MALE_DEATH_GAMMA*age) - 1.0 ) / MALE_DEATH_GAMMA );
        };
    
    double npx(
        int termin_year,
        int age
    )
        {
        return lx(age + termin_year) / lx(age);
        };

    double nqx(
        int termin_year,
        int age
    )
        {
        return 1 - npx(termin_year, age);
        };
    
    double nex(
        double interest,
        int termin_year,
        int age
    )
        {
        return discounting(termin_year, interest) * npx(termin_year, age);
        };   

    double vt(
        int t,
        double interest,
        int termin_year,
        int age
    )
        {
        return nex(interest, termin_year - t, age + t);
        };

    double passiv(
        double k,
        double interest,
        int termin_year,
        int age
    )
        {
        return nex(interest, termin_year, age) * retrospective(liv1::NORMAL, k, interest, termin_year);
        };
};

