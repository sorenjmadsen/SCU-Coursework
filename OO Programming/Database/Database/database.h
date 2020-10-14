// FILE: database.h
// PROVIDES: A class for storing names of companies and their products.
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//  CONSTANTS for the Database class
//  COMPANY_NOT_FOUND - the value that is returned when the company is not found in the databse (-1)
//
// CONSTRUCTOR for the Database class:
// database(const size_type& initial_capacity = 2);
//     Postcondition: Creates a database object where there is orginally no
//     used entries. The initial size of the dynamic array is 2.
//
//
// MEMBER FUNCTIONS for the database class:
//
//  bool insert_company(const std::string& company_name);
//      Precondition: company_name is a non-empty string
//      Postcondition: A new Company is added to the list
//
//  bool erase_company(const std::string& company_name);;
//      Precondition: company_name is a non-empty string
//      Postcondition:  A company (as well as all its products) are removed from the database.  All elements to
//      the right of the company are shifted to the left.
//      Returns false if the company was not found in the list.
//
//  bool insert_item(const std::string &company_name, const std::string& product_name, const float& price)
//      Precondition: company_name and product_name are non-empty strings
//      Postcondition: A new product is added to the list pertaining to the company
//      This function also checks to see if the company is already in the database.
//      Returns false if the compnay is already in the database, otherwise returns true.
//
//  bool erase_item(const std::string &company_name, const std::string& product_name)
//      Precondition: company_name and product_name are non-empty strings
//      Postcondition:  A product is erased from the company in the database.  Returns false if
//      the company or the item was not found.
//
//
//  bool print_items_by_company(const std::string& company_name)
//      Precondition: company_name is a non-empty string
//      Postcondition: Takes in the name of a company and then prints out the items belonging to it.
//      Return true if the company is in the database, returns false otherwise.
//
//  void print_companies();
//      Postcondition:  Prints the list of companies currently in the database
//
//  void reserve(size_type new_capacity)
//     Postcondition: The database's current capacity is changed to the
//     new_capacity (but not less than the number of items already in the
//     database). The insert_company function will work efficiently (without allocating
//     new memory) until the new capacity is reached.
//
//  size_type search_company(const std::string& company_name);
//      Precondition: company is a non-empty string
//      Postcondition:  Searches the DB for the company of the specified name.  Returns the position if found, but if
//      not found, returns COMPANY_NOT_FOUND.
//
//
//
// VALUE SEMANTICS for the database class:
//    Assignments and the copy constructor may be used with database objects.
//
// DYNAMIC MEMORY USAGE by the database:
//   If there is insufficient dynamic memory, then the following functions throw
//   bad_alloc: The constructors, reserve, insert_company, and insert_item



#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include "node.h"
#include "company.h"
#include <cassert>
#include <cmath>

#define COMPANY_NOT_FOUND  (-1)

namespace coen79_lab7
{
    class database {
        
    public:
        typedef std::size_t size_type;
        
        // Constructors
        database(const size_type& initial_capacity = 2);
        database(const database &src);
        ~database();
        
        // MODIFICATION MEMBER FUNCTIONS
        void reserve(size_type new_capacity);
        bool insert_company(const std::string& company_name);
        bool erase_company(const std::string& company_name);
        
        // Item operations
        bool insert_item(const std::string &company_name, const std::string& product_name, const float& price);
        bool erase_item(const std::string &company_name, const std::string& product_name);
        
        
        // CONSTANT MEMBER FUNCTIONS
        void print_companies();
        bool print_items_by_company(const std::string& company_name);
        
        // Assignment Operator
        database& operator=(const database &rhs);
        
    private:
        company *company_array; // A pointer to a dynamic array of company objects
        size_type aloc_slots; // Number of slots in the stindex_array array
        size_type used_slots; // Number of used slots in the stindex_array array
        
        //Helper functions
        size_type search_company(const std::string& company_name);
    };
}
#endif
