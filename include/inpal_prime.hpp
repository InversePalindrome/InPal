//
//  inpal_prime.hpp
//  Inverse Palindrome Library
//
//  Created by Bryan Triana on 7/21/16.
//  Copyright © 2016 Inverse Palindrome. All rights reserved.
//


#ifndef inpal_prime_hpp
#define inpal_prime_hpp
#include <vector>
#include <string>


namespace inpal
{
    namespace prime
    {
        //general purpose functions
        std::vector<std::size_t> prime_list(std::size_t range);
        std::vector<bool> prime_sieve(std::size_t range);
        std::vector<std::size_t> factor_list(std::size_t num);
        //special purpose functions
        std::size_t prime_locate(std::size_t pos);
        std::size_t max_prime(std::size_t range);
        std::size_t prime_count(std::size_t range);
        double prime_density(double range);
        bool prime_test(std::size_t num);
        bool twin_test(std::size_t num);
        bool cousin_test(std::size_t num);
        bool sexy_test(std::size_t num);
        std::size_t max_palprime(std::size_t range);
        std::size_t max_factor(std::size_t num);
        std::size_t factor_count(std::size_t num);
    }
}


#endif /* inpal_prime_hpp */
