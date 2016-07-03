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
    std::size_t max_prime(std::size_t n);
    std::size_t count_primes(std::size_t n);
    double prime_density(double h);
    bool prime_test(std::size_t p);
    bool twin_test(std::size_t p);
    bool cousin_test(std::size_t p);
    bool sexy_test(std::size_t p);
    std::size_t max_palprime(std::size_t n);
    std::size_t max_factor(std::size_t f);
    std::size_t count_factors(std::size_t f);
    
    std::vector<bool> prime_sieve(std::size_t m);
    std::vector<std::size_t> factorizer(std::size_t f);
    bool pal_test(std::size_t n);
}


#endif /* inpalprime_hpp */
