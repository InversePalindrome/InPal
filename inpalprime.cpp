//
//  inpalprime.cpp
//  InPal TESTS
//
//  Created by bryan triana on 6/21/16.
//  Copyright © 2016 Inverse Palindrome. All rights reserved.
//


#include "inpalprime.hpp"
#include <cmath>
#include <vector>


long long inpalprime::p_gen(unsigned long long n)
{
    //defines square root of n
    long long root=ceil(sqrt(n));
    
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
    for(long long x=1; x<=root; x++)
    {
        for(long long y=1; y<=root; y++)
        {
            long long i=(4*x*x)+(y*y);
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
    for(long long r=5; r<=root; r++)
    {
        if((p_test[r]))
        {
            for(long long j=r*r; j<=n; j+=r*r)
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
               prime=a;
               break;
           }
    }

    
    return prime;
}
