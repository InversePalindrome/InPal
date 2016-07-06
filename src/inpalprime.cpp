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


template <class T> T  inpal::prime<T>::max_prime(T range)
{
    auto primes = prime_sieve(range);
    auto it = std::find(primes.rbegin(), primes.rend(), true);
    
    return primes.size()-std::distance(primes.rbegin(), it)-1;
}


template <class T> T inpal::prime<T>::count_primes(T range)
{
    auto primes = prime_sieve(range);
    
    return std::count(primes.begin(), primes.end(), true);
}


template <class T> double inpal::prime<T>::prime_density(double range)
{
    return count_primes(range)/range;
}


template <class T> bool inpal::prime<T>::prime_test(T p)
{
    return p == max_prime(p);
}


template <class T> bool inpal::prime<T>::twin_test(T num)
{
    auto primes = prime_sieve(num+2);
    
    return num!=2 && primes[primes.size()-3] && (primes[primes.size()-1] || primes[primes.size()-5]);
}


template <class T> bool inpal::prime<T>::cousin_test(T num)
{
    auto primes = prime_sieve(num+4);
    
    return  num!=2 && primes[primes.size()-5] && (primes[primes.size()-1] || primes[primes.size()-9]);
}


template <class T> bool inpal::prime<T>::sexy_test(T num)
{
    auto primes = prime_sieve(num+6);
    
    return (num!=2 && num!=3) && primes[primes.size()-7] && (primes[primes.size()-1] || primes[primes.size()-13]);
}


template <class T> T inpal::prime<T>::max_palprime(T range)
{
    auto primes = prime_sieve(range);
    
    for(std::size_t i=range; i>=2; --i) if(primes[i] && pal_test(i)) return i;
    
    return 2;
}


template <class T> T inpal::prime<T>::max_factor(T num)
{
    return factorizer(num).back();
}


template <class T> T inpal::prime<T>::count_factors(T num)
{
    return factorizer(num).size();
}


template <class T> std::vector<bool> inpal::prime<T>::prime_sieve(T range)
{
    std::vector<bool> p_test(range+1, false);
    
    //defines square root of m
    T root = ceil(sqrt(range));
    
    //sieve axioms
    for(std::size_t x=1; x<=root; x++)
    {
        for(std::size_t y=1; y<=root; y++)
        {
            std::size_t  i = (4*x*x)+(y*y);
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
    }
    
    //marks 2,3,5 and 7 as prime numbers
    p_test[2]=p_test[3]=p_test[5]=p_test[7]=true;
    
    //marks all multiples of primes as non primes
    for(std::size_t r=5; r<=root; r++)
    {
        if(p_test[r])
        {
            for(std::size_t j=r*r; j<=range; j+=r*r)
            {
                p_test[j]=false;
            }
        }
    }
    
    return p_test;
}


template <class T> std::vector<T> inpal::prime<T>::factorizer(T num)
{
    std::vector<T> p_fac;
    T p = 2;
    
    //trial division
    while(p<=num)
    {
        while(num%p==0)
        {
            p_fac.push_back(p);
            num=num/p;
        }
        p += p==2 ? 1 : 2;
    }
    
    return p_fac;
}


template <class T> bool inpal::prime<T>::pal_test(T num)
{
    //converts n to a string
    std::string rev = std::to_string(num);
    
    //checks if the reverse of rev is equal to rev
    if(std::equal(rev.begin(), rev.begin()+rev.size()/2, rev.rbegin()))
    {
        return true;
    }
    
    return false;
}

//explicit instantiation
template class inpal::prime<unsigned long>;
template class inpal::prime<unsigned long long>;
template class inpal::prime<long>;
template class inpal::prime<long long>;
