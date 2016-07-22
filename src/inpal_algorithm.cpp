//
//  inpal_algorithm.cpp
//  Inverse Palindrome Library
//
//  Created by Bryan Triana on 7/22/16.
//  Copyright © 2016 Inverse Palindrome. All rights reserved.
//


#include "inpal_algorithm.hpp"
#include <string>


std::size_t inpal::algorithm::modulo(std::size_t a, std::size_t b, std::size_t c)
{
    std::size_t x = 1;
    
    while(b>0)
    {
        if(b%2==1) x=(x*a%c);
        a=(a*a)%c;
        b/=2;
    }
    
    return x%c;
}


std::size_t inpal::algorithm::mulmod(std::size_t a, std::size_t b, std::size_t c)
{
    std::size_t x = 0;
    std::size_t y = a%c;
    
    while(b>0)
    {
        if(b%2==1) x=(x+y)%c;
        y=(y*2)%c;
        b/=2;
    }
    
    return x%c;
}


bool inpal::algorithm::pal_test(std::size_t num)
{
    std::string rev = std::to_string(num);
    
    //checks if half the reverse of rev is equal to the other half of rev
    if(std::equal(rev.begin(), rev.begin()+rev.size()/2, rev.rbegin()))
    {
        return true;
    }
    
    return false;
}


