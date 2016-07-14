//
//  inpal_prime.cpp
//  inpalprime
//
//  Created by bryan triana on 7/13/16.
//  Copyright © 2016 Inverse Palindrome. All rights reserved.
//

#include "inpal_prime.hpp"
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>


std::size_t inpal::prime::max_prime(std::size_t num)
{
    auto primes = prime_sieve(num);
    auto it = std::find(primes.rbegin(), primes.rend(), true);
    
    return primes.size()-std::distance(primes.rbegin(), it)-1;
}


std::size_t inpal::prime::prime_count(std::size_t num)
{
    auto primes = prime_sieve(num);
    
    return std::count(primes.begin(), primes.end(), true);
}


double inpal::prime::prime_density(double range)
{
    return prime_count(range)/range;
}


bool inpal::prime::prime_test(std::size_t num)
{
    return num == max_prime(num);
}


bool inpal::prime::twin_test(std::size_t num)
{
    auto primes = prime_sieve(num+2);
    
    return num!=2 && primes[primes.size()-3] && (primes[primes.size()-1] || primes[primes.size()-5]);
}


bool inpal::prime::cousin_test(std::size_t num)
{
    auto primes = prime_sieve(num+4);
    
    return  num!=2 && primes[primes.size()-5] && (primes[primes.size()-1] || primes[primes.size()-9]);
}


bool inpal::prime::sexy_test(std::size_t num)
{
    auto primes = prime_sieve(num+6);
    
    return (num!=2 && num!=3) && primes[primes.size()-7] && (primes[primes.size()-1] || primes[primes.size()-13]);
}


std::size_t inpal::prime::max_palprime(std::size_t num)
{
    auto primes = prime_sieve(num);
    
    for(std::size_t i=num; i>=2; --i) if(primes[i] && pal_test(i)) return i;
    
    return 2;
}


std::size_t inpal::prime::max_factor(std::size_t num)
{
    return factorizer(num).back();
}


std::size_t inpal::prime::count_factors(std::size_t num)
{
    return factorizer(num).size();
}


std::vector<bool> inpal::prime::prime_sieve(std::size_t range)
{
    std::vector<bool> p_test(range+1, false);
    
    //defines square root of range
    std::size_t root = ceil(sqrt(range));
    
    //sieve axioms
    for(std::size_t x=1; x<=root; x++)
        for(std::size_t y=1; y<=root; y++)
        {
            std::size_t i = (4*x*x)+(y*y);
            if (i<=range && (i%12==1 || i%12==5))
            {
                p_test[i].flip();
            }
            
            i = (3*x*x)+(y*y);
            if(i<=range && i%12==7)
            {
                p_test[i].flip();
            }
            
            i = (3*x*x)-(y*y);
            if(x>y && i<=range && i%12==11)
            {
                p_test[i].flip();
            }
        }
    
    //marks 2,3,5 and 7 as prime numbers
    p_test[2]=p_test[3]=p_test[5]=p_test[7]=true;
    
    //marks all multiples of primes as non primes
    for(std::size_t r=5; r<=root; r++)
    {
        if((p_test[r]))
        {
            for(std::size_t j=r*r; j<=range; j+=r*r)
            {
                p_test[j]=false;
            }
        }
    }
    
    return p_test;
}


std::vector<std::size_t> inpal::prime::factorizer(std::size_t num)
{
    std::vector<std::size_t> p_fac;
    std::size_t p = 2;
    
    //trial division
    while(p<=num)
    {
        while(num%p==0)
        {
            p_fac.push_back(num);
            num=num/p;
        }
        p += p==2 ? 1 : 2;
    }
    
    return p_fac;
}


bool inpal::prime::pal_test(std::size_t num)
{
    //converts num to a string
    std::string rev = std::to_string(num);
    
    //checks if the reverse of rev is equal to rev
    if(std::equal(rev.begin(), rev.begin()+rev.size()/2, rev.rbegin()))
    {
        return true;
    }
    
    return false;
}