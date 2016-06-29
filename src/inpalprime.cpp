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


unsigned long long inpalprime::pn_find(unsigned long long n)
{
    //finds the highest possible prime less or equal to n
    for(std::vector<bool>::size_type it=atkinsieve(n).size()-1; it!=1; it--)
    {
        if(atkinsieve(n)[it])
        {
            maxprime=it;
            break;
        }
    }
    
    
    return maxprime;
}



unsigned long long inpalprime::pn_count(unsigned long long n)
{
    //counts the number of primes less or equal to n
    for(std::vector<bool>::size_type it=atkinsieve(n).size()-1; it!=1; it--)
    {
        if(atkinsieve(n)[it])
        {
            primecount++;
        }
    }
    
    
    return primecount;
}



long double inpalprime::pn_den(long double h)
{
   //calculates density of primes from 1 to  h
    primeden=(pn_count(h)/h);
    
    
    return primeden;
}



bool inpalprime::pn_test(unsigned long long a)
{
    //primality test based on the sieve of atkin
    if(a!=pn_find(a))
    {
        return false;
    }
    
    
    return true;
}



bool inpalprime::pn_twin(unsigned long long a)
{
    if(a==2)
    {
        return false;
    }
    
    else if(pn_test(a) && (pn_test(a+2) || pn_test(a-2)))
    {
        return true;
    }
    
    
    return false;
}



bool inpalprime::pn_cousin(unsigned long long a)
{
    if(a==2)
    {
        return false;
    }
    
    else if(pn_test(a) && (pn_test(a+4) || pn_test(a-4)))
    {
        return true;
    }
            
    
    return false;
}



bool inpalprime::pn_sexy(unsigned long long a)
{
    if(a==2 || a==3)
    {
        return false;
    }
    
    else if(pn_test(a) && (pn_test(a+6) || pn_test(a-6)))
    {
        return true;
    }
    
    
    return false;
}



unsigned long long inpalprime::pn_pal(unsigned long long n)
{
    //finds the highest palindromic prime less or equal to n
    for(std::vector<bool>::size_type it=atkinsieve(n).size()-1; it!=1; it--)
    {
        if(atkinsieve(n)[it] && pal_test(it))
      {
          pal=it;
          break;
      }
    }
   
   
    return pal;
}



unsigned long long inpalprime::n_fac(unsigned long long f)
{
    //finds the highest prime factor less or equal to f
    maxfac=factorizer(f).back();
    
    
    return maxfac;
}



unsigned long long inpalprime::n_cfac(unsigned long long f)
{
    //counts the number of prime factors that compose f, if f is prime the returned value is 1
    cfac=factorizer(f).size();
    
    
    return cfac;
}



std::vector<bool> inpalprime::atkinsieve(unsigned long long m)
{
    std::vector<bool> p_test(m+1, false);
    
    //defines square root of m
    unsigned long long root=ceil(sqrt(m));
    
    //sieve axioms
    for(unsigned long long x=1; x<=root; x++)
    {
        for(unsigned long long y=1; y<=root; y++)
        {
            unsigned long long i=(4*x*x)+(y*y);
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
    for(unsigned long long r=5; r<=root; r++)
    {
        if((p_test[r]))
        {
            for(unsigned long long j=r*r; j<=m; j+=r*r)
            {
                p_test[j]=false;
            }
        }
    }
    
    
    return p_test;
}


std::vector<unsigned long long> inpalprime::factorizer(unsigned long long f)
{
    std::vector<unsigned long long> p_fac;
    unsigned long long p=3;
    
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



bool inpalprime::pal_test(unsigned long long n)
{
    //converts m to a string
    ull=std::to_string(n);
    
    //checking if the reverse of ull is equal to ull
    if(ull!=std::string(ull.rbegin(), ull.rend()))
       {
           return false;
       }
    
    
    return true;
}

