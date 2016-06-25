//
//  inpalprime.hpp
//  InPal 
//
//  Created by Bryan Triana on 6/21/16.
//  Copyright © 2016 Inverse Palindrome. All rights reserved.
//


#ifndef inpalprime_hpp
#define inpalprime_hpp


class inpalprime
{

public:
    unsigned long long pn_find(unsigned long long n);
    unsigned long long pn_count(unsigned long long l);
    long double pn_den(long double h);
    bool pn_test(unsigned long long k);
    bool pn_twin(unsigned long long a);
    bool pn_cousin(unsigned long long a);
    bool pn_sexy(unsigned long long a);
    unsigned long long n_maxfac(unsigned long long m);

private:
    unsigned long long maxprime=0;
    unsigned long long primecount=0;
    long double primeden;
    unsigned long long maxfac=0;
    
};


#endif /* inpalprime_hpp */
