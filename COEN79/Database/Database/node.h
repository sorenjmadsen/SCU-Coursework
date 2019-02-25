// FILE: node.h
// PROVIDES: A class for a node in a linked list, and list manipulation
// Each node represents a product of a company
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
// CONSTANTS for the Node class
//
// CONSTRUCTOR for the Nodes class:
//   node(
//     const std::string& itemName = "",
//     const float& newPrice = -1,
//     node* nextNode = NULL
//        )
//     Postcondition: The node contains the specified name, price and link values.
//
//
// NOTE:
//   Some of the functions have a return value which is a pointer to a node.
//   Each of these  functions comes in two versions: a non-const version (where
//   the return value is node*) and a const version (where the return value
//   is const node*).
//
//
// MEMBER FUNCTIONS for the node class:
//
//  void setName(const string& product_name)
//      Precondition: product_name is a non-empty string
//      Postcondition:  Sets the name field of the node
//
//  void setPrice(const float& newPrice)
//      Postcondition: Sets the price field of the node
//
//  void setLink(node* newLink)
//      Postcondition: Sets the link field of the node
//
//   const node* getLink( ) const <----- const version
//   node* getLink( ) <----------------- non-const version
//   See the note (above) about the const version and non-const versions:
//     Postcondition: The return value is the link from this node.
//
//   std::string getName() const
//     Postcondition: Returns the name field of the node
//
//   std::string getPrice() const
//     Postcondition: Returns the price field of the node
//
//
// FUNCTIONS in the linked list toolkit:
//
//   void list_clear(node*& head_ptr)
//     Precondition: head_ptr is the head pointer of a linked list.
//     Postcondition: All nodes of the list have been returned to the heap,
//     and the head_ptr is now NULL.
//
//  void list_init(node*& head_ptr, node*& tail_ptr, const std::string& newName, const float& newPrice)
//      Precondition: newName is a non_empty string
//      Postcondition:  initializes an empty list (where head and tail are NULL).
//      Takes in a head and tail pointer,  creates a new node, and modifies the head
//      and tail pointer to point to the new node
//
//  void list_tail_insert(node*& tail_ptr, const std::string& newName, const float& newPrice)
//      Precondition: tail_ptr is the tail pointer of a non-empty linked list,
//      newName is a non_empty string
//      Postcondition: Adds a node to the end of the linked list.
//
//   void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
//     Precondition: source_ptr is the head pointer of a linked list.
//     Postcondition: head_ptr and tail_ptr are the head and tail pointers for
//     a new list that contains the same items as the list pointed to by
//     source_ptr. The original list is unaltered.
//
//  void list_print(node* head_ptr);
//     Precondition: head_ptr is the head pointer of a linked list.
//     Postcondition:  Prints the list.  Format is as follows:
//          Printing the items which belong to company Apple
//              - iPhone where the price is $999
//              - Macbook where the price is $2000
//
//  bool list_contains_item(node* head_ptr, const std::string& name)
//      Precondition: head_ptr is the head pointer of a linked list, and name is
//      a non-empty string
//      Postcondition:  Returns true if "name" is in the linked list,
//      returns false if the item is not in the linked list
//
//   void list_head_remove(node*& head_ptr)
//     Precondition: head_ptr is the head pointer of a linked list, with at
//     least one node.
//     Postcondition: The head node has been removed and returned to the heap;
//     head_ptr is now the head pointer of the new, shorter linked list.
//
//   node* list_search(node* head_ptr, const std::string& name);
//   const node* list_search (const node* head_ptr, const std::string& name);
//   See the note (above) about the const version and non-const versions:
//     Precondition: head_ptr is the head pointer of a linked list, and name is
//     a non_empty string
//     Postcondition: The pointer returned points to the first node containing
//     the specified target in its data member. If there is no such node, the
//     null pointer is returned.
//
//



#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>


namespace coen79_lab7
{
    class node {
        
    public:
        // Constructors
        node(const std::string& itemName = "", const float& newPrice = -1, node* nextNode = NULL);
        
        // Modification member functions
        void setName(const std::string& product_name);
        void setPrice(const float& newPrice);
        void setLink(node* newLink);
        
        // Constant member functions
        const node *getLink() const;
        node *getLink();
        std::string getName() const;
        float getPrice() const;
        
    private:
        std::string name; // Name of the product
        float price; // Price of the product
        node *link; // Link to the next product
    };
    
    
    // FUNCTIONS for the item list toolkit
    void list_clear(node*& head_ptr);
    void list_init(node*& head_ptr, node*& tail_ptr, const std::string& newName, const float& newPrice);
    void list_tail_insert(node*& tail_ptr, const std::string& newName, const float& newPrice);
    void list_copy(const node* old_head, node*& new_head, node*& new_tail);
    void list_print(node* head_ptr);
    bool list_contains_item(node* head_ptr, const std::string& name);
    void list_head_remove(node*& head_ptr);
    node* list_search(node* head_ptr, const std::string& name);
    const node* list_search (const node* head_ptr, const std::string& name);

}

#endif
