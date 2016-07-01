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


long long inpalprime::max_prime(long long n)
{
    auto primes = prime_sieve(n);
    auto it = std::find(primes.rbegin(), primes.rend(), true);
    
    return primes.size()-std::distance(primes.rbegin(), it)-1;
}


long long inpalprime::count_primes(long long n)
{
    auto primes = prime_sieve(n);
    
    return std::count(primes.begin(), primes.end(), true);
}


long double inpalprime::prime_density(long double h)
{
    return count_primes(h)/h;
}


bool inpalprime::prime_test(long long p)
{
    return p == max_prime(p);
}


bool inpalprime::twin_test(long long p)
{
    auto primes = prime_sieve(p+2);
    
    return p!=2 && primes[primes.size()-3] && (primes[primes.size()-1] || primes[primes.size()-5]);
}


bool inpalprime::cousin_test(long long p)
{
    auto primes = prime_sieve(p+4);
    
    return  p!=2 && primes[primes.size()-5] && (primes[primes.size()-1] || primes[primes.size()-9]);
}


bool inpalprime::sexy_test(long long p)
{
    auto primes = prime_sieve(p+6);
    
    return (p!=2 && p!=3) && primes[primes.size()-7] && (primes[primes.size()-1] || primes[primes.size()-13]);
}



long long inpalprime::max_palprime(long long n)
{
    auto primes = prime_sieve(n);
   
    for(std::vector<bool>::size_type it=primes.size()-1; it!=1; it--)
    {
        if(primes[it] && pal_test(it))
        {
            return it;
        }
    }
    
    return 0;
}

                           

long long inpalprime::max_factor(long long f)
{
    return factorizer(f).back();
}
                                                            
                                                            
long long inpalprime::count_factors(long long f)
{
    return factorizer(f).size();
}
      

std::vector<bool> inpalprime::prime_sieve(long long m)
{
    std::vector<bool> p_test(m+1, false);
    
    //defines square root of m
    unsigned long long root = ceil(sqrt(m));
    
    //sieve axioms
    for(unsigned long long x=1; x<=root; x++)
    {
        for(long long y=1; y<=root; y++)
        {
            long long i=(4*x*x)+(y*y);
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
    for(long long r=5; r<=root; r++)
    {
        if((p_test[r]))
        {
            for(long long j=r*r; j<=m; j+=r*r)
            {
                p_test[j]=false;
            }
        }
    }
    
    return p_test;
}


std::vector<long long> inpalprime::factorizer(long long f)
{
    std::vector<long long> p_fac;
    long long p = 3;
    
    //removes factors of 2
    while(f%2==0)
    {
        p_fac.push_back(2);
        f=f/2;
    }
    
    //finds prime factors of f
    while(f!=1)
    {
        while(f%p==0)
        {
            p_fac.push_back(p);
            f=f/p;
        }
        p+=2;
    }
    
    return p_fac;
}



bool inpalprime::pal_test(long long n)
{
    //converts n to a string
    std::string rev = std::to_string(n);
    
    //checks if the reverse of rev is equal to rev
    for(int i=0; i<rev.size()/2; i++)
    {
        if(rev[i]!=rev[rev.size()-1-i])
        {
            return false;
        }
    }
    
    return true;
}
