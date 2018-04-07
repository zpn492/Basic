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
        //double q = pow(1 + interest*accural_of_interest/accural_of_interest, accural_of_interest);
        double q, termin; 
        if(accural_of_interest == 1)
            {
            q = (1 + interest);
            termin = termin_year;
            }
        else
            {
            interest = pow((1+interest ), 1.0/accural_of_interest ) - 1;
            q = 1 + interest;
            termin = termin_year * accural_of_interest;
            }    

        switch(cf)
            {
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
                        return (pow(q, termin ) - 1) / interest;
                        }
                    break;
                    case RETROSPECTIVE:  // a
                        {
                        return ( 1 - pow( q, -termin) ) / interest;
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
                        return (pow(q, termin+1 ) - q ) / interest;
                        }
                    break;
                    case RETROSPECTIVE:  // a
                        {
                        return (( 1 - pow(q, -termin ) ) / interest ) * q;
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

