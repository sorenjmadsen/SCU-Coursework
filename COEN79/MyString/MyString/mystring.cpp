//
//  mystring.cpp
//  MyString
//
//  Created by Søren Madsen on 2/7/19.
//  Copyright © 2019 SCU. All rights reserved.
//

#include <stdio.h>
#include "mystring.h"
#include <cstring>
#include <cassert>

namespace coen79_lab5 {
    string::string(const char str[ ]){
        size_t size_of_str = strlen(str);
        characters = new char[size_of_str + 1];
        std::copy(str, str + size_of_str, characters);
        allocated = size_of_str + 1;
        current_length = size_of_str;
        characters[current_length] = '\0';
    }
    string::string(char c){
        characters = new char[2];
        characters[0] = c;
        allocated = 1;
        current_length = 1;
        characters[current_length] = '\0';
    }
    string::string(const string& source){
        characters = new char[source.allocated];
        strncpy(characters, source.characters, source.allocated);
        current_length = source.current_length;
        allocated = source.allocated;
    }
    string::~string( ){
        delete [] characters;
    }
    
    // MODIFICATION MEMBER FUNCTIONS
    void string::operator +=(const string& addend){
        if(current_length + addend.length() > allocated)
            reserve(current_length + addend.length());
        strncat(characters, addend.characters, addend.length());
        current_length += addend.length();
    }
    void string::operator +=(const char addend[ ]){
        if(current_length + strlen(addend) > allocated)
            reserve(current_length + strlen(addend));
        strncat(characters, addend, strlen(addend));
        current_length += strlen(addend);
    }
    void string::operator +=(char addend){
        if(current_length + 2 > allocated)
            reserve(allocated + 1);
        characters[current_length] = addend;
        current_length++;
        characters[current_length] = '\0';
    }
    void string::reserve(size_t n){
        char * temp = new char[n];
        for (size_t i = 0; i < allocated; i++){
            temp[i] = characters[i];
        }
        delete [] characters;
        characters = temp;
        allocated = n;
    }
    
    string& string::operator =(const string& source){
        reserve(source.allocated);
        strncpy(characters, source.characters, source.allocated);
        current_length = source.length();
        return * this;
    }
    void string::insert(const string& source, unsigned int position){
        assert(position <= current_length);
        char * temp = new char[current_length + 1 + source.length()];
        strncat(temp, characters, position);
        strncat(temp, source.characters, source.length());
        strncat(temp, characters + position, allocated);
        delete [] characters;
        characters = temp;
        current_length++;
        
    }
    void string::dlt(unsigned int position, unsigned int num){
        assert(position + num <= current_length);
        strncpy(characters + position, characters + position + num, allocated);
        current_length -= num;
    }
    void string::replace(char c, unsigned int position){
        assert(position <= current_length);
        characters[position] = c;
    }
    void string::replace(const string& source, unsigned int position){
        assert(position + source.length() <= current_length);
        char * temp = new char[allocated];
        strncat(temp, characters, position);
        strncat(temp, source.characters, source.length());
        strncat(temp, characters + position + source.length(), allocated);
    }
    
    // CONSTANT MEMBER FUNCTIONS
    char string::operator [ ](size_t position) const{
        assert(position < current_length);
        return characters[position];
    }
    int string::search(char c) const{
        int idx = -1;
        for (size_t i = 0; i < current_length; i++){
            if (characters[i] == c){
                idx = i;
                break;
            }
        }
        return idx;
    }
    int string::search(const string& substring) const{
        for(size_t i = 0; i < current_length; i++){
            if(strncmp(characters + i, substring.characters, substring.length()) == 0) return i;
        }
        return -1;
    }
    unsigned int string::count(char c) const{
        unsigned int count = 0;
        for (size_t i = 0; i < current_length; i++){
            if (characters[i] == c) count++;
        }
        return count;
    }
    
    // FRIEND FUNCTIONS
    std::ostream& operator <<(std::ostream& outs, const string& source){
        size_t i = 0;
        while (source.characters[i] != '\0'){
            outs << source.characters[i];
            i++;
        }
        return outs;
    }
    bool operator ==(const string& s1, const string& s2){
        if(s1.length() != s2.length()) return false;
        for (size_t i = 0; i < s1.length(); i++){
            if(s1.characters[i] != s2.characters[i]) return false;
        }
        return true;
    }
    bool operator !=(const string& s1, const string& s2){
        if(s1.length() != s2.length()) return true;
        for (size_t i = 0; i < s1.length(); i++){
            if(s1.characters[i] == s2.characters[i]) return false;
        }
        return true;
    }
    bool operator > (const string& s1, const string& s2){
        int test = strncmp(s1.characters, s2.characters, (s1.length() < s2.length() ? s1.length() : s2.length()));
        return test > 0;
    }
    bool operator < (const string& s1, const string& s2){
        int test = strncmp(s1.characters, s2.characters, (s1.length() < s2.length() ? s1.length() : s2.length()));
        return test < 0;
    }
    bool operator >=(const string& s1, const string& s2){
        int test = strncmp(s1.characters, s2.characters, (s1.length() < s2.length() ? s1.length() : s2.length()));
        return test >= 0;
    }
    bool operator <=(const string& s1, const string& s2){
        int test = strncmp(s1.characters, s2.characters, (s1.length() < s2.length() ? s1.length() : s2.length()));
        return test <= 0;
    }
    // NON-MEMBER FUNCTIONS for the string class
    string operator +(const string& s1, const string& s2){
        string temp(s1);
        temp += s2;
        return temp;
    }
    string operator +(const string& s1, const char addend[ ]){
        string temp(s1);
        temp += addend;
        return temp;
    }
    std::istream& operator >> (std::istream& ins, string& target){
        char c;
        while (ins && isspace(ins.peek()))
            ins.ignore();
        
        target = "";
        while(!ins.eof() && !isspace(ins.peek())){
            ins >> c;
            target += c;
        }
        return ins;
    }
}
