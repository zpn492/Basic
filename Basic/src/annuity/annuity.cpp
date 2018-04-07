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
            case CONTINUES:
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
                        return (pow(E, delta * (termin+1) ) - q) / interest;
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

    
};

