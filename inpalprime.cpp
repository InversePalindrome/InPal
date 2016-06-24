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


unsigned long long inpalprime::pn_find(unsigned long long n)
{
    //defines square root of n
    unsigned long long root=ceil(sqrt(n));
    
    //return values to deal with values of n less than 7
   switch(n)
    {
        case 2:return 2;
        case 3:return 3;
        case 5:return 5;
        case 7:return 7;
    }
    //stores boolean values for primality testing, 1: prime, 0: not prime
    std::vector<bool> p_test (n+1, false);
    
    //sieve of atkin
    for(unsigned long long x=1; x<=root; x++)
    {
        for(unsigned long long y=1; y<=root; y++)
        {
            unsigned long long i=(4*x*x)+(y*y);
            if (i<=n && (i%12==1 || i%12==5))
            {
                p_test[i].flip();
            }
            i=(3*x*x)+(y*y);
            if(i<=n && i%12==7)
            {
                p_test[i].flip();
            }
            i=(3*x*x)-(y*y);
            if(x>y && i<=n && i%12==11)
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
            for(unsigned long long j=r*r; j<=n; j+=r*r)
            {
                p_test[j]=false;
            }
        }
    }
    
    //finds the highest possible prime under n
    for(std::vector<bool>::size_type a=p_test.size()-1; a!=1; a--)
    {
        if((p_test[a]))
           {
               maxprime=a;
               break;
           }
    }

    
    return maxprime;
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



unsigned long long inpalprime::pn_count(unsigned long long l)
{
    
    //defines square root of n
    unsigned long long root=ceil(sqrt(l));
    
    //return values to deal with values of l less than 7
    switch(l)
    {
        case 2:return 1;
        case 3:return 2;
        case 5:return 3;
        case 7:return 4;
    }
    //stores boolean values for primality testing, 1: prime, 0: not prime
    std::vector<bool> p_test (l+1, false);
    
    //sieve of atkin
    for(unsigned long long x=1; x<=root; x++)
    {
        for(unsigned long long y=1; y<=root; y++)
        {
            unsigned long long i=(4*x*x)+(y*y);
            if (i<=l && (i%12==1 || i%12==5))
            {
                p_test[i].flip();
            }
            i=(3*x*x)+(y*y);
            if(i<=l && i%12==7)
            {
                p_test[i].flip();
            }
            i=(3*x*x)-(y*y);
            if(x>y && i<=l && i%12==11)
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
            for(unsigned long long j=r*r; j<=l; j+=r*r)
            {
                p_test[j]=false;
            }
        }
    }
    
    //count the number of primes under l+1
    for(std::vector<bool>::size_type it=p_test.size()-1; it!=1; it--)
    {
        if((p_test[it]))
        {
            primecount++;
        }
    }

    
    
    return primecount;
}

long double inpalprime::pn_den(long double h)
{
    primeden=(pn_count(h)/h)*0.5;
    
    return primeden;
}



bool inpalprime::pn_test(unsigned long long k)
{
    if(k!=pn_find(k))
    {
        return false;
    }
    
    
    return true;
}






