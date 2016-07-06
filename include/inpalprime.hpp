//
//  inpalprime.hpp
//  InPal TESTS
//
//  Created by bryan triana on 6/21/16.
//  Copyright © 2016 Inverse Palindrome. All rights reserved.
//


#ifndef inpalprime_hpp
#define inpalprime_hpp

#include <vector>
#include <string>


namespace inpal
{
    template <class T> class prime
    {
    public:
     static T max_prime(T range);
     static T count_primes(T range);
     static double prime_density(double range);
     static bool prime_test(T num);
     static bool twin_test(T num);
     static bool cousin_test(T num);
     static bool sexy_test(T num);
     static T max_palprime(T range);
     static T max_factor(T num);
     static T count_factors(T num);
    private:
     static std::vector<bool> prime_sieve(T range);
     static std::vector<T> factorizer(T num);
     static bool pal_test(T num);
    };
}


#endif /* inpalprime_hpp */

