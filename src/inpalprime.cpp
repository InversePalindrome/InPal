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
    //finds the highest possible prime under n
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
    //count the number of primes under n
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
   //density of primes from 1 to  h
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
    //finds the highest palindromic prime equal or less than n
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



unsigned long long inpalprime::n_maxfac(unsigned long long m)
{
    unsigned long long p=3;
    //removing factors of 2
    while(m%2==0)
    {
        maxfac=2;
        m=m/2;
    }
    
    //finding possible prime factors
    while(m!=1)
    {
        while(m%p==0)
        {
            maxfac=p;
            m=m/p;
        }
        p+=2;
    }
    
    
    return maxfac;
}



std::vector<bool> inpalprime::atkinsieve(unsigned long long m)
{
    std::vector<bool> p_test(m+1, false);
    
    //defines square root of n
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



bool inpalprime::pal_test(unsigned long long m)
{
    //converting m to a string
    ull=std::to_string(m);
    
    //checking if the reverse of ull is equal to ull
    if(ull!=std::string(ull.rbegin(), ull.rend()))
       {
           return false;
       }
    
    
    return true;
}

