//
//  inpal_algorithm.cpp
//  Inverse Palindrome Library
//
//  Created by Bryan Triana
//  Copyright © 2016 Inverse Palindrome. All rights reserved.
//


#include "inpal_algorithm.hpp"


std::size_t inpal::algorithm::gcd(std::size_t a, std::size_t b)
{
    while(b != 0)
    {
        std::size_t r = a % b;
        a = b;
        b = r;
    }
    
    return a;
}


std::size_t inpal::algorithm::lcm(std::size_t a, std::size_t b)
{
    if(a == 0 || b == 0) throw std::invalid_argument("Least Common Multiple of 0 is not defined");
    
    return (a * b) / gcd(a, b);
}


std::size_t inpal::algorithm::modulo(std::size_t a, std::size_t b, std::size_t m)
{
    if(m == 0) throw std::invalid_argument("Third parameter 'm' cannot be equal to 0, division by 0 is invalid");
    
    std::size_t x = 1;
    
    while(b > 0)
    {
        if(b % 2 == 1) x = (x * a % m);
        a = (a * a) % m;
        b /= 2 ;
    }
    
    return x % m;
}


std::size_t inpal::algorithm::mulmod(std::size_t a, std::size_t b, std::size_t m)
{
    if(m == 0) throw std::invalid_argument("Third parameter 'm' cannot be equal to 0, division by 0 is invalid");
    
    std::size_t x = 0;
    std::size_t y = a % m;
    
    while(b > 0)
    {
        if(b % 2 == 1) x = (x + y) % m;
        y = (y * 2) % m;
        b /= 2;
    }
    
    return x % m;
}


std::size_t inpal::algorithm::pollard_rho(std::size_t num)
{
    if(num < 2) return num;
    
    const std::size_t m = 1000;
    std::size_t a, x, ys;
    
    do a = rand() % num;
    while(a == 0 || a == num - 2);
    
    std::size_t y = rand() % num;
    std::size_t d = 1;
    std::size_t q = 1;
    std::size_t r = 1;
    
    do
    {
        x = y;
        for(std::size_t i = 0; i <= r; ++i) y = mulmod(y, a, num);
        
        std::size_t j = 0;
        do
        {
            ys = y;
            for(std::size_t i = 0; i <= std::min(m, r - j); ++i)
            {
                y = mulmod(y, a, num);
                q *= (std::max(x, y) - std::min(x, y)) % num;
            }
            d = gcd(q, num);
            j += m;
        }
        while(j < r && d == 1);
        r *= 2;
    }
    while(d == 1);
    
    if(d == num)
    {
        do
        {
            ys = mulmod(ys, a, num);
            d = gcd(std::max(x, ys) - std::min(x, ys), num);
        }
        while(d == 1);
    }
    
    return d;
}


bool inpal::algorithm::palindrome_test(std::size_t num)
{
    std::string rev = std::to_string(num);
    
    //check if half the reverse of rev is equal to the other half of rev
    if(std::equal(rev.begin(), rev.begin() + rev.size() / 2, rev.rbegin())) return true;
    
    return false;
}
