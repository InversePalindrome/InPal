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


namespace inpal
{
    long long max_prime(long long n);
    long long count_primes(long long n);
    long double prime_density(long double h);
    bool prime_test(long long p);
    bool twin_test(long long p);
    bool cousin_test(long long p);
    bool sexy_test(long long p);
    long long max_palprime(long long n);
    long long max_factor(long long f);
    long long count_factors(long long f);
    
    std::vector<bool> prime_sieve(long long m);
    std::vector<long long> factorizer(long long f);
    bool pal_test(long long n);
}



#endif /* inpalprime_hpp */
