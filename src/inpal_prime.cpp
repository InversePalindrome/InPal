//
//  inpal_prime.cpp
//  Inverse Palindrome Library
//
//  Created by Bryan Triana on 7/21/16.
//  Copyright © 2016 Inverse Palindrome. All rights reserved.
//


#include "inpal_prime.hpp"
#include "inpal_algorithm.hpp"


std::vector<std::size_t> inpal::prime::prime_list(std::size_t range)
{
    const auto primes = prime_sieve(range);
    std::vector<std::size_t> p_list;
    
    for(std::size_t i=2; i<=range; i++) if(primes[i]) p_list.push_back(i);
    
    return p_list;
}


std::vector<bool> inpal::prime::prime_sieve(std::size_t range)
{
    std::vector<bool> p_test(range+1, false);
    
    //defines square root of range for future usage
    const std::size_t root = ceil(sqrt(range));
    
    //sieve axioms
    for(std::size_t x=1; x<=root; x++)
        for(std::size_t y=1; y<=root; y++)
        {
            std::size_t i = (4*x*x)+(y*y);
            if(i<=range && (i%12==1 || i%12==5)) p_test[i].flip();
            
            i = (3*x*x)+(y*y);
            if(i<=range && i%12==7) p_test[i].flip();
            
            i = (3*x*x)-(y*y);
            if(x>y && i<=range && i%12==11) p_test[i].flip();
        }
    
    //marks 2, 3 and 5 as prime numbers to ignore these numbers in the next process
    p_test[2]=p_test[3]=p_test[5]=true;
    
    //marks all multiples of primes as non primes
    for(std::size_t r=5; r<=root; r++)
    {
       if(p_test[r])
        {
            for(std::size_t j=r*r; j<=range; j+=r*r) p_test[j]=false;
        }
    }
    
    return p_test;
}


std::vector<std::size_t> inpal::prime::factor_list(std::size_t num)
{
    std::vector<std::size_t> factors;
    std::vector<std::size_t> primes;
    
    std::size_t factor = algorithm::pollard_rho(num);
    factors.push_back(num/factor);
    factors.push_back(factor);
    
    do
    {
        std::size_t m = factors.back();
        factors.pop_back();
        
        if(m==1) continue;
        if(prime_test(m))
        {
            primes.push_back(m);
            
            //decomposes the factors into primes
            for(std::size_t i=0; i<factors.size(); i++)
            {
                std::size_t k = factors[i];
                if(k%m==0)
                {
                    do k/=m;
                    while(k%m==0);
                    
                    factors[i]=k;
                }
            }
        }
        else
        {
            factor=algorithm::pollard_rho(m);
            factors.push_back(m/factor);
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
    //index starts at 1 instead of 0, eg 1st prime is 2
    pos = pos-1;
    
    //return values for input less or equal to 10
    const auto small_primes = prime_list(29);
    if(pos<10) return small_primes[pos];
    
    //denotes the limit of the sieve
    std::size_t limit = pos*log(pos)+pos*log(log(pos));
    const auto primes = prime_list(limit);
    
    return primes[pos];
}


std::size_t inpal::prime::max_prime(std::size_t range)
{
    for(std::size_t i=range; i>0; i--) if(prime_test(i)) return i;

    return 2;
}


std::size_t inpal::prime::prime_count(std::size_t range)
{
    const auto primes = prime_sieve(range);
    
    return std::count(primes.begin(), primes.end(), true);
}


double inpal::prime::prime_density(double range)
{
    return prime_count(range)/range;
}


bool inpal::prime::prime_test(std::size_t num)
{
    if(num!=2 && num%2==0) return false;
    
    //iterations will occur 20 times to ensure that the margin of error is less than 4^-20
    const std::size_t cycle = 20;
    std::size_t s = num-1;
    while(s%2==0) s/=2;
    
    for(std::size_t i=0; i<cycle; i++)
    {
        std::size_t a = rand()%(num-1)+1;
        std::size_t b = s;
        std::size_t mod = algorithm::modulo(a,b,num);
        
        while(b!=num-1 && mod!=1 && mod!=num-1)
        {
            mod=algorithm::mulmod(mod,mod,num);
            b*=2;
        }
        if(mod!=num-1 && b%2==0) return false;
    }
    
    return true;
}


bool inpal::prime::twin_test(std::size_t num)
{
    return prime_test(num) && (prime_test(num-2) || prime_test(num+2));
}


bool inpal::prime::cousin_test(std::size_t num)
{
    return  prime_test(num) && (prime_test(num-4) || prime_test(num+4));
}


bool inpal::prime::sexy_test(std::size_t num)
{
    return num!=3 && prime_test(num) && (prime_test(num-6) || prime_test(num+6));
}


std::size_t inpal::prime::max_palprime(std::size_t range)
{
    for(std::size_t i=range; i>2; --i) if(algorithm::pal_test(i) && prime_test(i)) return i;
    
    return 2;
}


std::size_t inpal::prime::max_factor(std::size_t num)
{
    return factor_list(num).back();
}


std::size_t inpal::prime::factor_count(std::size_t num)
{
    return factor_list(num).size();
}


