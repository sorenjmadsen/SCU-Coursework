// FILE: company.h
// PROVIDES: A class for storing a company's products' information including
// its name, as well as pointers to a linked list that store
// products information of the company
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
//  CONSTRUCTOR for the company class:
//
//  company();
//   Postcondition: The company object is initialized with empty company name
//
//  company(const std::string& company_name);
//   Precondition: company_name is a non-empty string
//   Postcondition: The company object is initialized with "company_name"
//
//
//  NOTE:
//   Some of the functions have a return value which is a pointer to a node.
//   Each of these  functions comes in two versions: a non-const version (where
//   the return value is node*) and a const version (where the return value
//   is const node*).
//
//
//
// MEMBER FUNCTIONS for the company class:
//
// node *get_head();
//      Postcondition: returns the NON CONST version of the head of linked list
//
// const node *get_head() const;
//      Postcondition: returns the CONST version of the head of linked list
//
// node *get_tail();
//      Postcondition: returns the NON CONST version of the tail of linked list
//
// const node *get_tail() const;
//      Postcondition: returns the CONST version of the tail of linked list
//
// std::string get_name() const;
//      Postcondition: returns the name of company
//
// void print_items();
//      Postcondition:  Prints the products of the company (prints the items in the linkes list)
//      Format for each item is "- <Name of item> where the price is $<price of item>
//
// bool insert(const std::string& name, const float &price);
//      Precondition: product_name is a non-empty string
//      Postcondition: Creates and inserts a new node (product) to the back of the linked list.
//      Returns true if successfully inserted, and returns false if there is a duplicate
//
// bool erase(const std::string& product_name)
//      Postcondition:  Erases the product that its name matches product_name. Returns true if the
//      product has been found and deleted, returns false otherwise


#ifndef COMPANY_H
#define COMPANY_H

#include "node.h"

namespace coen79_lab7
{
    class company {
        
    public:
        
        //CONSTRUCTORS AND DESTRUCTOR
        company();
        company(const std::string& company_name);
        company(const company& src);
        ~company();
        
        // Modification member functions
        node* get_head();
        node* get_tail();
        bool insert(const std::string& product_name, const float& price);
        bool erase(const std::string& product_name);
        company& operator= (const company& src);
        
        // Constant member functions
        const node* get_head() const;
        const node* get_tail() const;
        std::string get_name() const;
        void print_items();
        
    private:
        std::string company_name; // Name of company
        node* head_ptr; // Head of the linked list including company's products
        node* tail_ptr; // Tail of the linked list including company's products
    };
}

#endif
