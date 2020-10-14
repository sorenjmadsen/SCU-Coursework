// FILE: sequence1.h
//  Sequence Class
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
// TYPEDEF and MEMBER CONSTANTS for the sequence class:
//   static const size_t CAPACITY = ____
//     sequence::CAPACITY is the maximum number of items that a sequence can hold.
//
//   typedef ____ value_type
//     sequence::value_type is the data type of the items in the sequence. It may be any of
//     the C++ built-in types (int, char, etc.), or a class with a default
//     constructor, an assignment operator, and a copy constructor.
//
//
// CONSTRUCTOR for the sequence class:
//   sequence( )
//     Postcondition: The sequence has been initialized as an empty sequence.
//
//
//
// MODIFICATION MEMBER FUNCTIONS for the sequence class:
//
//  void start();
//      Poscondition: The iterator is reset to position 0;
//
//  void end();
//      Poscondition: The iterator points to the last item in the sequence;
//
//  void last();
//      Poscondition: The iterator is reset to CAPACITY - 1, regardless of the numebr of items in the sequence;
//
// void advance();
//      Precondtion: isitem() returns true
//      Postcondition: The iterator's value is increased by 1, unless it is already at the end of the sequence.
//
// void retreat();
//      Postcondition: The iterator's value is reduced by 1, unless it is already at the beginning of the sequence.
//
//
// void insert(const value_type& entry);
//      Precondition: size() < CAPACITY
//      Postcondition: A new copy of entry has been inserted in the sequence
//      before the current item. If there was no current item, the new entry
//      has been inserted at the front. In either case, the new item is now the
//      current item of the sequence.
//
//  void attach(const value_type& entry);
//      Precondition: size() < CAPACITY
//      Postcondition: A new copy of entry has been inserted in the sequence
//      after the current item. If there was no current item, the new entry
//      has been attached to the end. In either case, the new item is now the
//      current item of the sequence.
//
// void remove_current();
//      Precondtion: isitem() returns true
//      Postcondition: The current item has been removed from the sequence,
//      and the item after this (if there is one) is now the current item.
//
//
// void insert_front(const value_type& entry);
//      Precondition: size() < CAPACITY
//      Postcondition: A new copy of entry has been inserted in the sequence
//      at the front. The new item is now the current item of the sequence.
//
// void attach_back(const value_type& entry);
//      Precondition: size() < CAPACITY
//      Postcondition: A new copy of entry has been inserted in the sequence
//      at the back. The new item is now the current item of the sequence.
//
// void remove_front();
//      Precondtion: isitem() returns true
//      Postcondition: The item at the front of the sequence has been removed from the sequence,
//      and the current item points at the front of the sequence.
//
//   void operator +=(const sequence& rhs)
//     Postcondition: Adds the items of rhs to the lhs. Also returns a copy of lhs.
//
//
// CONSTANT MEMBER FUNCTIONS for the sequence class:
//
//  size_type size() const;
//      Postcondition: The return value is the number of items in the ssequence.
//
//   bool is_item( ) const
//     Postcondition: A true return value indicates that there is a valid
//     "current" item that may be retrieved by activating the current
//     member function (listed below). A false return value indicates that
//     there is no valid current item.
//
//   value_type current() const;
//      Precondtion: isitem() returns true
//      Poscondition: Returns the item in the sequence at the current position of the iterator.
//
//   value_type operator[](int index) const
//     Precondition: index < used
//     Postcondition: The item returned is the item stored at "index"
//
//   double mean() const
//     Postcondition: The value returned is the mean of the values stored in the sequence.
//
//   double standardDeviation() const
//     Postcondition: The value returned is the stadard deviation of the values stored in the sequence.
//
//
//
//
// NON-MEMBER functions for the statistician class:
//
//   sequence operator +(const sequence& lhs, const sequence& rhs)
//     Postcondition: The sequence that is returned contains all the
//     numbers of the sequences of lsh and rhs.
//
//
//   value_type summation(const sequence &s)
//     Postcondition: The value returned is the summation of the values stored in the sequence s.
//
//
// VALUE SEMANTICS for the sequence class:
//    Assignments and the copy constructor may be used with sequence objects.
//
//


#ifndef COEN79_SEQUENCE1_H
#define COEN79_SEQUENCE1_H

#include <iostream>

namespace coen79_lab3 {
    
    class sequence {
        
    public:
        // TYPEDEF and MEMBER CONSTANTS
        typedef double value_type;
        typedef std::size_t size_type;
        static const size_type CAPACITY = 30;
        
        // CONSTRUCTOR
        sequence();
        
        // MODIFICATION MEMBER FUNCTIONS
        void start();
        void end();    // Added by me.
        void last();     // Added by me.
        void advance();
        void retreat(); // Added by me.
        void insert(const value_type& entry);
        void insert_front(const value_type& entry);
        void attach(const value_type& entry);
        void attach_back(const value_type& entry);
        void remove_current();
        void remove_front();
        
        // CONSTANT MEMBER FUNCTINOS
        size_type size() const;
        bool is_item() const;
        value_type current() const;
        size_type index() const { return current_index; }
        
        // Subscript operator
        value_type operator[](int index) const;
        
        
        // Homework Question Functions
        double mean() const;
        double standardDeviation() const;
        
    private:
        value_type data[CAPACITY];
        size_type used;
        size_type current_index;
    };
    
    // NON-MEMBER functions for the sequence class
    sequence operator+(sequence& lhs, sequence& rhs);
    sequence operator+=(sequence& lhs, sequence& rhs);
    
    
    // Homework Question Functions
    sequence::value_type summation(const sequence &s);
}

#endif
