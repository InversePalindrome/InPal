//
//  inpalprime.cpp
//  InPal 
//
//  Created by Bryan Triana on 6/21/16.
//  Copyright © 2016 Inverse Palindrome. All rights reserved.
//


#include "inpalprime.hpp"
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>


std::size_t inpal::max_prime(std::size_t n)
{
    auto primes = prime_sieve(n);
    auto it = std::find(primes.rbegin(), primes.rend(), true);
    
    return primes.size()-std::distance(primes.rbegin(), it)-1;
}


std::size_t inpal::count_primes(std::size_t n)
{
    auto primes = prime_sieve(n);
    
    return std::count(primes.begin(), primes.end(), true);
}


double inpal::prime_density(double h)
{
    return count_primes(h)/h;
}


bool inpal::prime_test(std::size_t p)
{
    return p == max_prime(p);
}


bool inpal::twin_test(std::size_t p)
{
    auto primes = prime_sieve(p+2);
    
    return p!=2 && primes[primes.size()-3] && (primes[primes.size()-1] || primes[primes.size()-5]);
}


bool inpal::cousin_test(std::size_t p)
{
    auto primes = prime_sieve(p+4);
    
    return  p!=2 && primes[primes.size()-5] && (primes[primes.size()-1] || primes[primes.size()-9]);
}


bool inpal::sexy_test(std::size_t p)
{
    auto primes = prime_sieve(p+6);
    
    return (p!=2 && p!=3) && primes[primes.size()-7] && (primes[primes.size()-1] || primes[primes.size()-13]);
}


std::size_t inpal::max_palprime(std::size_t n)
{
    auto primes = prime_sieve(n);
        
    for(std::size_t i=n; i>=2; --i) if(primes[i] && pal_test(i)) return i;
        
    return 2;
}


std::size_t inpal::max_factor(std::size_t f)
{
    return factorizer(f).back();
}


std::size_t inpal::count_factors(std::size_t f)
{
    return factorizer(f).size();
}


std::vector<bool> inpal::prime_sieve(std::size_t m)
{
    std::vector<bool> p_test(m+1, false);
    
    //defines square root of m
    std::size_t root = ceil(sqrt(m));
    
    //sieve axioms
    for(std::size_t x=1; x<=root; x++)
    {
        for(std::size_t y=1; y<=root; y++)
        {
            std::size_t i= (4*x*x)+(y*y);
            if (i<=m && (i%12==1 || i%12==5))
            {
                p_test[i].flip();
            }
            
            i=(3*x*x)+(y*y);
            if(i<=m && i%12==7)
            {
                p_test[i].flip();
            }
            
            i=(3*x*x)-(y*y);
            if(x>y && i<=m && i%12==11)
            {
                p_test[i].flip();
            }
        }
    }
    
    //marks 2,3,5 and 7 as prime numbers
    p_test[2]=p_test[3]=p_test[5]=p_test[7]=true;
    
    //marks all multiples of primes as non primes
    for(std::size_t r=5; r<=root; r++)
    {
        if((p_test[r]))
        {
            for(std::size_t j=r*r; j<=m; j+=r*r)
            {
                p_test[j]=false;
            }
        }
    }
    
    return p_test;
}


std::vector<std::size_t> inpal::factorizer(std::size_t f)
{
    std::vector<std::size_t> p_fac;
    std::size_t p = 2;
    
    //trial division
    while(p<=f)
    {
        while(f%p==0)
        {
            p_fac.push_back(p);
            f=f/p;
        }
        p+= p==2 ? 1 : 2;
    }
    
    return p_fac;
}


bool inpal::pal_test(std::size_t n)
{
    //converts n to a string
    std::string rev = std::to_string(n);
    
    //checks if the reverse of rev is equal to rev
    if(std::equal(rev.begin(), rev.begin()+rev.size()/2, rev.rbegin()))
    {
        return true;
    }
    
    return false;
}
