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


long long inpalprime::pn_find(long long n)
{
    auto p_find=atkinsieve(n);
    
    //finds the highest possible prime less or equal to n
    for(std::vector<bool>::size_type it=p_find.size(); it!=1; it--)
    {
        if(p_find[it])
        {
            maxprime=it;
            break;
        }
    }
    
    
    return maxprime;
}



long long inpalprime::pn_count(long long n)
{
    auto p_count=atkinsieve(n);
    
    //counts the number of primes less or equal to n
    primecount=std::count(p_count.begin(), p_count.end(), true);
    
    
    return primecount;
}



long double inpalprime::pn_den(long double h)
{
    //calculates density of primes from 1 to  h
    primeden=(pn_count(h)/h);
    
    
    return primeden;
}



bool inpalprime::pn_test(long long a)
{
    //primality test based on the sieve of atkin
    if(a!=pn_find(a))
    {
        return false;
    }
    
    
    return true;
}



bool inpalprime::pn_twin(long long a)
{
    auto p_tw=atkinsieve(a+2);
    
    if(a==2)
    {
        return false;
    }
    
    //checks if a+2 or a-2 is also prime
    else if(p_tw[p_tw.size()-3] && (p_tw[p_tw.size()-1] || p_tw[p_tw.size()-5]))
    {
        return true;
    }

    
    return false;
}



bool inpalprime::pn_cousin(long long a)
{
   auto p_co=atkinsieve(a+4);
    
    if(a==2)
    {
        return false;
    }
    
    //checks if a+4 or a-4 is also prime
    else if(p_co[p_co.size()-5] && (p_co[p_co.size()-1] || p_co[p_co.size()-9]))
    {
        return true;
    }

    
    return false;
}



bool inpalprime::pn_sexy(long long a)
{
    auto p_se=atkinsieve(a+6);
    
    if(a==2 || a==3)
    {
        return false;
    }
    
    //checks if a+6 or a-6 is also prime
    else if(p_se[p_se.size()-7] && (p_se[p_se.size()-1] || p_se[p_se.size()-13]))
    {
        return true;
    }

    
    return false;
}



long long inpalprime::pn_pal(long long n)
{
    auto p_pal=atkinsieve(n);
    
    //finds the highest palindromic prime less or equal to n
    for(std::vector<bool>::size_type it=p_pal.size(); it!=1; it--)
    {
        if(p_pal[it] && pal_test(it))
        {
            pal=it;
            break;
        }
    }
    
    
    return pal;
}



long long inpalprime::n_fac(long long f)
{
    //finds the highest prime factor less or equal to f
    maxfac=factorizer(f).back();
    
    
    return maxfac;
}



long long inpalprime::n_cfac(long long f)
{
    //counts the number of prime factors that compose f, if f is prime the returned value is 1
    cfac=factorizer(f).size();
    
    
    return cfac;
}



std::vector<bool> inpalprime::atkinsieve(long long m)
{
    std::vector<bool> p_test(m+1, false);
    
    //defines square root of m
    unsigned long long root=ceil(sqrt(m));
    
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
    long long p=3;
    
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
    rev=std::to_string(n);
    
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
