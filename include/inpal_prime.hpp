//
//  inpal_prime.hpp
//  InversePalindrome
//
//  Created by Bryan Triana on 7/13/16.
//  Copyright © 2016 Inverse Palindrome. All rights reserved.
//


#ifndef inpal_prime_hpp
#define inpal_prime_hpp

#include <vector>
#include <string>


namespace inpal
{
    class prime
    {
    public:
        //general purpose functions
        static std::vector<std::size_t> prime_list(std::size_t range);
        static std::vector<std::size_t> factor_list(std::size_t num);
        //special purpose functions
        static std::size_t max_prime(std::size_t range);
        static std::size_t prime_count(std::size_t range);
        static double prime_density(double range);
        static bool prime_test(std::size_t num);
        static bool twin_test(std::size_t num);
        static bool cousin_test(std::size_t num);
        static bool sexy_test(std::size_t num);
        static std::size_t max_palprime(std::size_t range);
        static std::size_t max_factor(std::size_t num);
        static std::size_t factor_count(std::size_t num);
    private:
        //utility algorithms
        static std::vector<bool> prime_sieve(std::size_t range);
        static bool pal_test(std::size_t num);
    };
}


#endif /* inpal_prime_hpp */
