//
//  inpal_prime.cpp
//  Inverse Palindrome Library
//
//  Created by Bryan Triana
//  Copyright © 2016 Inverse Palindrome. All rights reserved.
//


#include "inpal_prime.hpp"
#include "inpal_algorithm.hpp"


std::vector<std::size_t> inpal::prime::prime_list(std::size_t range)
{
    const auto& primes = prime_sieve(range);
    std::vector<std::size_t> p_list;
    if(range < 2) return p_list;
    
    p_list.push_back(2);
    
    for(std::size_t i = 3; i <= range; i += 2) if(primes[i]) p_list.push_back(i);
    
    return p_list;
}


std::vector<bool> inpal::prime::prime_sieve(std::size_t range)
{
    std::vector<bool> p_test(range + 1, false);
    
    //sieve axioms
    for(std::size_t x = 1; x <= std::sqrt(range); ++x)
        for(std::size_t y = 1; y <= std::sqrt(range); ++y)
        {
            std::size_t i = (4 * x * x) + (y * y);
            if(i <= range && (i % 12 == 1 || i % 12 == 5)) p_test[i].flip();
            
            i = (3 * x * x) + (y * y);
            if(i <= range && i %12 == 7) p_test[i].flip();
            
            i = (3 * x * x) - (y * y);
            if(x > y && i <= range && i % 12 == 11) p_test[i].flip();
        }
    
    //marks 2, 3 and 5 as prime numbers
    p_test[2] = p_test[3] = p_test[5] = true;
    
    //marks all multiples of primes as non primes
    for(std::size_t r = 5; r <= std::sqrt(range); ++r)
    {
        if(p_test[r])
        {
            for(std::size_t j = r * r; j <= range; j += r * r) p_test[j] = false;
        }
    }
    
    return p_test;
}


std::vector<std::size_t> inpal::prime::factor_list(std::size_t num)
{
    std::vector<std::size_t> factors;
    std::vector<std::size_t> primes;
    
    if(num < 2) return primes;
    
    std::size_t factor = algorithm::pollard_rho(num);
    factors.push_back(num / factor);
    factors.push_back(factor);
    
    do
    {
        std::size_t m = factors.back();
        factors.pop_back();
        
        if(m == 1) continue;
        if(prime_test(m))
        {
            primes.push_back(m);
            
            //decomposes the factors into primes
            for(auto& i : factors)
            {
                std::size_t k = i;
                if(k % m == 0)
                {
                    do k /= m;
                    while(k % m == 0);
                    
                    i = k;
                }
            }
        }
        else
        {
            factor = algorithm::pollard_rho(m);
            factors.push_back(m / factor);
            factors.push_back(factor);
        }
    }
    while(factors.size());
    
    //prime factors found by pollard rho arent always ordered
    std::sort(primes.begin(), primes.end());
    
    return primes;
}


std::size_t inpal::prime::prime_locate(std::size_t pos)
{
    //prime number position located at sieve[index - 1]
    pos -= 1;
        
    //return values for input less or equal to 13
    if(pos < 14) return prime_list(43)[pos];
    
    //limits the size of the sieve
    const std::size_t limit = ceil(pos * log(pos) + pos * log(log(pos)));
    
    return prime_list(limit)[pos];
}


std::size_t inpal::prime::max_prime(std::size_t range)
{
    if(range < 2) throw std::invalid_argument("There are no prime numbers less than 2");
    
    for(std::size_t i = range; i > 0; --i) if(prime_test(i)) return i;
    
    return 2;
}


std::size_t inpal::prime::prime_count(std::size_t range)
{
    if(range < 2) return 0;
    if(range == 2) return 1;
    
    std::vector<bool> p_count(range / 2 + 1, true);
    
    //modified sieve of eratosthenes
    for(std::size_t i = 1; i <= std::sqrt(range / 2 + 1); ++i)
    {
        if(p_count[i])
        {
            for(std::size_t j = 2 * i * (i + 1); j < range / 2 + 1; j += 2 * i + 1) p_count[j] = false;
        }
    }
    
    return std::count(p_count.begin(), p_count.end(), true);
}


bool inpal::prime::prime_test(std::size_t num)
{
    if(num < 2 || (num != 2 && num % 2 == 0)) return false;
    
    //iterations will occur 20 times to ensure that the margin of error is less than 4^-20
    const std::size_t cycle = 20;
    std::size_t s = num - 1;
    while(s % 2 == 0) s /= 2;
    
    for(std::size_t i = 0; i < cycle; ++i)
    {
        std::size_t a = rand() % (num - 1) + 1;
        std::size_t b = s;
        std::size_t mod = algorithm::modulo(a, b, num);
        
        while(b != num - 1 && mod != 1 && mod != num - 1)
        {
            mod = algorithm::mulmod(mod, mod, num);
            b *= 2;
        }
        if(mod != num - 1 && b % 2 == 0) return false;
    }
    
    return true;
}


bool inpal::prime::twin_prime_test(std::size_t num)
{
    return prime_test(num) && (prime_test(num - 2) || prime_test(num + 2));
}


bool inpal::prime::cousin_prime_test(std::size_t num)
{
    return  prime_test(num) && (prime_test(num - 4) || prime_test(num + 4));
}


bool inpal::prime::sexy_prime_test(std::size_t num)
{
    return num != 3 && prime_test(num) && (prime_test(num - 6) || prime_test(num + 6));
}


std::size_t inpal::prime::max_palindromic_prime(std::size_t range)
{
    if(range < 2) throw std::invalid_argument("There are no palindromic prime numbers less than 2");
    
    for(std::size_t i = range; i >= 2; --i) if(prime_test(i) && algorithm::pal_test(i)) return i;
    
    return 2;
}


std::size_t inpal::prime::max_factor(std::size_t num)
{
    if(num < 2) throw std::invalid_argument("There are no prime factors less than 2");
    
    return factor_list(num).back();
}


std::size_t inpal::prime::factor_count(std::size_t num)
{
    return factor_list(num).size();
}
