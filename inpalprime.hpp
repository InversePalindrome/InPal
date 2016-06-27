//
//  inpalprime.hpp
//  InPal 
//
//  Created by Bryan Triana on 6/21/16.
//  Copyright © 2016 Inverse Palindrome. All rights reserved.
//


#ifndef inpalprime_hpp
#define inpalprime_hpp

#include<vector>
#include<string>


class inpalprime
{

public:
    unsigned long long pn_find(unsigned long long n);
    unsigned long long pn_count(unsigned long long n);
    long double pn_den(long double h);
    bool pn_test(unsigned long long a);
    bool pn_twin(unsigned long long a);
    bool pn_cousin(unsigned long long a);
    bool pn_sexy(unsigned long long a);
    unsigned long long pn_pal(unsigned long long n);
    unsigned long long n_maxfac(unsigned long long m);

private:
    std::vector<bool> atkinsieve(unsigned long long m);
    bool pal_test(unsigned long long m);
    unsigned long long maxprime=0;
    unsigned long long primecount=0;
    long double primeden;
    std::string ull;
    unsigned long long maxfac=0;
    
};


#endif /* inpalprime_hpp */
