//
//  inpalprime.hpp
//  InPal 
//
//  Created by Bryan Triana on 6/21/16.
//  Copyright © 2016 Inverse Palindrome. All rights reserved.
//


#ifndef inpalprime_hpp
#define inpalprime_hpp

#include <vector>
#include <string>


class inpalprime
{
    
public:
    long long pn_find(long long n);
    long long pn_count(long long n);
    long double pn_den(long double h);
    bool pn_test(long long a);
    bool pn_twin(long long a);
    bool pn_cousin(long long a);
    bool pn_sexy(long long a);
    long long pn_pal(long long n);
    long long n_fac(long long f);
    long long n_cfac(long long f);
  
private:
    std::vector<bool> atkinsieve(long long m);
    std::vector<long long> factorizer(long long f);
    bool pal_test(long long n);
    long long maxprime=0;
    long long primecount;
    long double primeden;
    long long pal;
    std::string ull;
    long long maxfac;
    long long cfac;
    
};


#endif /* inpalprime_hpp */
