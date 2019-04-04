//
//  keyed_bag.cpp
//  Keyed Bag
//
//  Created by soren j madsen on 1/31/19.
//  Copyright © 2019 SCU. All rights reserved.
//

#include "keyed_bag.h"
#include <cassert>

using namespace coen79_lab4;

namespace coen79_lab4 {
    // CONSTRUCTOR
    keyed_bag::keyed_bag(){
        used = 0;
    }
    
    // MODIFICATION MEMBER FUNCTIONS:
    void keyed_bag::erase(){
        used = 0;
    }
    bool keyed_bag::erase(const key_type& key){
        for(size_type i = 0; i < used; i++){
            if (has_key(key)){
                data[i] = data[used - 1];
                keys[i] = keys[used - 1];
                used--;
                return true;
            }
        }
        return false;
    }
    void keyed_bag::insert(const value_type& entry, const key_type& key){
        assert(used < CAPACITY);
        data[used] = entry;
        keys[used] = key;
        used++;
    }
    void keyed_bag::operator +=(const keyed_bag& addend){
        assert(!hasDuplicateKey(addend));
        assert(used + addend.used < CAPACITY);
        for(size_type i = 0; i < addend.used; i++){
            data[used + i] = addend.data[i];
            keys[used + i] = addend.keys[i];
        }
        used += addend.used;
    }
    
    // CONSTANT MEMBER FUNCTIONS:
    bool keyed_bag::has_key(const key_type& key) const{
        for(size_type i = 0; i < used; i++){
            if(keys[i] == key) return true;
        }
        return false;
    }
    keyed_bag::value_type keyed_bag::get(const key_type& key) const{
        assert(has_key(key));
        size_type idx = 0;
        for(size_type i = 0; i < used; i++){
            if (key == keys[i]){
                idx = i;
            }
        }
        return data[idx];
    }
    keyed_bag::size_type keyed_bag::size( ) const{
        return used;
    }
    keyed_bag::size_type keyed_bag::count(const value_type& target) const{
        size_type count = 0;
        for (size_type i = 0; i < used; i++){
            if(data[i] == target) count++;
        }
        return count;
    }
    bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const{
        for(size_type i = 0; i < otherBag.used; i++){
            if(has_key(otherBag.keys[i])) return true;
        }
        return false;
    }
    keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2){
        keyed_bag temp;
        temp += b1;
        temp += b2;
        return temp;
    }
}
