//
//  sequence.cpp
//  Lab3
//
//  Created by Søren Madsen on 1/24/19.
//  Copyright © 2019 SCU. All rights reserved.
//

#include "sequence.h"
#include <cassert>
#include <cmath>

using namespace coen79_lab3;

namespace coen79_lab3{
    // CONSTRUCTOR
    sequence::sequence(){
        used = 0;
        current_index = 0;
    }
    
    // MODIFICATION MEMBER FUNCTIONS
    void sequence::start(){
        current_index = 0;
    }
    
    void sequence::end(){
        current_index = size() - 1;
    }
    
    void sequence::last(){
        current_index = CAPACITY - 1;
        
    }
    
    void sequence::advance(){
        if(current_index < CAPACITY)
            current_index++;
    }
    
    void sequence::retreat(){
        if(current_index > 0)
            current_index--;
    }
    
    void sequence::insert(const value_type& entry){
        assert(size() < CAPACITY);
        
        current_index = (current_index < size()) ? current_index : 0;
        for (size_type i = used; i > current_index; i--){
            data[i] = data[i - 1];
        }
        data[current_index] = entry;
        used++;
    }
    
    void sequence::insert_front(const value_type& entry){
        assert(size() < CAPACITY);
        
        for (size_type i = size(); i > 0; i--){
            data[i] = data[i - 1];
        }
        data[0] = entry;
        used++;
    }
    
    void sequence::attach(const value_type& entry){
        assert(size() < CAPACITY);
        
        current_index = (current_index + 1 < size()) ? current_index + 1 : size();
        for (size_type i = used; i > current_index; i--){
            data[i] = data[i - 1];
        }
        data[current_index] = entry;
        
        used++;
    }
    
    void sequence::attach_back(const value_type& entry){
        assert(size() < CAPACITY);
        
        data[used] = entry;
        current_index = size();
        used++;
    }
    
    void sequence::remove_current(){
        assert(is_item());
        for (size_type i = current_index; i < size() - 1; i++){
            data[i] = data[i + 1];
        }
        used--;
    }
    
    void sequence::remove_front(){
        assert(is_item());
        for (size_type i = 0; i < size() - 1; i++){
            data[i] = data[i + 1];
        }
        used--;
    }
    
    // CONSTANT MEMBER FUNCTINOS
    sequence::size_type sequence::size() const{
        return used;
    }
    
    bool sequence::is_item() const{
        return current_index < size();
    }
    
    sequence::value_type sequence::current() const{
        return data[current_index];
    }
    
    // Subscript operator
    sequence::value_type sequence::operator[](int index) const{
        return *(data + index);
    }
    
    
    // Homework Question Functions
    double sequence::mean() const{
        double temp = 0;
        for(size_type i = 0; i < size(); i++){
            temp += data[i];
        }
        return temp/size();
    }
    
    double sequence::standardDeviation() const{
        value_type dev_sum = 0;
        value_type mean = sequence::mean();
        for (size_type i = 0; i < size(); i++){
            dev_sum += pow((data[i] - mean),2);
        }
        return sqrt(dev_sum/size());
    }
    
    // NON-MEMBER functions for the sequence class
    sequence operator+(sequence& lhs, sequence& rhs){
        assert(lhs.size() + rhs.size() < sequence::CAPACITY);
        sequence temp = lhs;
        rhs.start();
        for(sequence::size_type i = 0; i < rhs.size(); i++){
            temp.attach(rhs.current());
            rhs.advance();
        }
        
        return temp;
    }
    
    sequence operator+=(sequence& lhs, sequence& rhs){
        assert(lhs.size() + rhs.size() < sequence::CAPACITY);
        lhs.end();
        rhs.start();
        for(sequence::size_type i = 0; i < rhs.size(); i++){
            lhs.attach(rhs.current());
            rhs.advance();
        }
        return lhs;
    }
    
    
    // Homework Question Functions
    sequence::value_type summation(const sequence &s){
        sequence temp = s;
        sequence::value_type sum = 0;
        temp.start();
        for(sequence::size_type i = 0; i < temp.size(); i++){
            sum += temp.current();
            temp.advance();
        }
        return sum;
    }
    
}
    


