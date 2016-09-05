//
//  inpal_algorithm.hpp
//  Inverse Palindrome Library
//
//  Created by Bryan Triana 
//  Copyright © 2016 Inverse Palindrome. All rights reserved.
//


#ifndef inpal_algorithm_hpp
#define inpal_algorithm_hpp

#include <cstdlib>
#include <string>


namespace inpal
{
    namespace algorithm
    {
        std::size_t gcd(std::size_t a, std::size_t b);
        std::size_t lcm(std::size_t a, std::size_t b);
        std::size_t modulo(std::size_t a, std::size_t b, std::size_t c);
        std::size_t mulmod(std::size_t a, std::size_t b, std::size_t c);
        std::size_t pollard_rho(std::size_t num);
        bool palindrome_test(std::size_t num);
    }
}


#endif /* inpal_algorithm_hpp */
