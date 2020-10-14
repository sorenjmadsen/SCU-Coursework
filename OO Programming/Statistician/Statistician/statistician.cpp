///Users/sorenmadsen/Documents/Programs/COEN79/Statistician/Statistician/statistician.h
//  statistician.cpp
//  Statistician
//
//  Created by Søren Madsen on 1/17/19.
//  Copyright © 2019 SCU. All rights reserved.
//
#include <iostream>
#include <cassert>
#include "statistician.h"

using namespace coen79_lab2;

namespace coen79_lab2
{
    statistician::statistician( )
    {
        count = 0;
        total = 0;
        tiniest = NULL;
        largest = NULL;
    }
    void statistician::next(double r)
    {
        total += r;
        if (count == 0){
            tiniest = r;
            largest = r;
        }
        count++;
        tiniest = (r < tiniest) ? r : tiniest;
        largest = (r > largest) ? r : largest;
    
    }
    void statistician::reset( )
    {
        count = 0;
        total = 0;
        tiniest = NULL;
        largest = NULL;
    }
    
    double statistician::mean( ) const
    {
        assert(count > 0);
        return total/count;
    }
    double statistician::minimum( ) const
    {
        assert(count > 0);
        return tiniest;
    }
    double statistician::maximum( ) const
    {
        assert(count > 0);
        return largest;
    }
    statistician operator + (const statistician& s1, const statistician& s2)
    {
        statistician temp;
        temp.total = s1.sum() + s2.sum();
        temp.count = s1.length() + s2.length();
        temp.tiniest = (s1.minimum() > s2.minimum() ? s1.minimum() : s2.minimum());
        temp.largest = (s1.maximum() > s2.maximum() ? s1.maximum() : s1.maximum());
        return temp;
        
    }
    statistician operator * (double scale, const statistician& s)
    {
        statistician temp;
        temp.count = s.length();
        temp.total = s.sum() * scale;
        temp.tiniest = (scale < 0) ? s.maximum() * scale : s.minimum() * scale;
        temp.largest = (scale < 0 ) ? s.minimum() * scale : s.maximum() * scale;
        return temp;
    }
    bool operator == (const statistician& s1, const statistician& s2){
        if (s1.length() + s2.length() == 0) return true;
        if (s1.length() == s2.length()){
            if ((s1.maximum() == s2.maximum()) && (s1.minimum() == s2.minimum()) && (s1.mean() == s2.mean()) && (s1.sum() == s2.sum())) return true;
        }
        return false;
    }
}
