//FILE: sequence.cpp
//CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
//INVARIANT for the sequence class
//  1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//  2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//      and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//      sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//      stored in the rest of the data.
//
//  3. If there is a current item, then it lies in *cursor; if there is no
//     current item, then cursor* equals NULL.
//
//  4. If there is a previous item, then it lies in precursor*.  If there is no previous
//       item, then precursor equals NULL.


#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; //For copy function

namespace coen79_lab6
{
    // Default private member variable initialization function.
    void sequence::init()
    {
        //Initializing pointers to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        //Initializiing many_nodes (or our counter) to 0
        many_nodes = 0;
    }

    //CONSTRUCTOR IMPLEMENTATION for default constructor
    sequence :: sequence ()
    {
        init();
    }

    //Copy Constructor
    sequence :: sequence(const sequence& source)
    {
        init();
        *this = source;
    }
    
    //Destructor
    sequence::~sequence(){
        list_clear(head_ptr);
        many_nodes = 0;
    }
    
    // MODIFICATION MEMBER FUNCTIONS
    void sequence::start( ){
        this->cursor = head_ptr;
        this->precursor = head_ptr;
    }
    void sequence::end(){
        while(precursor->link() != tail_ptr){
            precursor = precursor->link();
        }
        cursor = tail_ptr;
    }
    void sequence::advance( ){
        if(is_item()){
            if(cursor == tail_ptr){
                precursor = tail_ptr;
                cursor = NULL;
            }
            else {
                precursor = cursor;
                cursor = cursor->link();
            }
        }
    }
    void sequence::insert(const node::value_type& entry){
        // Empty insert
        if (!is_item()){
            // Only two reasons cursor is NULL
            // 1. The sequence is empty
            // 2. Cursor is after tail_ptr
            // 3. There is no current value, put it at the front
            if (head_ptr == NULL) {
                list_head_insert(head_ptr, entry);
                tail_ptr = head_ptr;
                cursor = head_ptr;
                precursor = NULL;
            }
            else if (precursor == tail_ptr){
                // Place it at the front
                list_head_insert(head_ptr, entry);
                cursor = head_ptr;
                precursor = NULL;
            }
        }
        
        // Cursor is a non-NULL node
        else {
            // Only two scenarios for cursor being non-NULL
            // 1. At the beginning of the sequence (precursor == NULL)
            // 2. Somewhere between the beginning at the end (precursor != NULL)
            if (precursor == NULL){
                list_head_insert(head_ptr, entry);
                cursor = head_ptr;
            }
            else {
                list_insert(precursor, entry);
                cursor = precursor->link();
            }
        }
        ++many_nodes;
    }
    void sequence::attach(const node::value_type& entry){
        // Empty attach
        if (!is_item()){
            // Only two reasons cursor is NULL
            // 1. The sequence is empty
            // 2. Cursor is after tail_ptr
            // 3. There is no current, place it at the end
            if (head_ptr == NULL) {
                list_head_insert(head_ptr, entry);
                tail_ptr = head_ptr;
                cursor = head_ptr;
                precursor = NULL;
            }
            // 2 and 3 both mean appending it to the end of the sequence
            else {
                list_insert(tail_ptr, entry);
                
                // Leave precursor where it is
                // Cursor is no longer null
                cursor = tail_ptr;
                tail_ptr = tail_ptr->link();
            }
        }
        
        // Cursor is a non-NULL node
        else {
            // Only three scenarios for cursor being non-NULL
            // 1. At the beginning of the sequence (precursor == NULL)
            // 2. Somewhere between the beginning at the end (precursor != NULL)
            // Doesn't matter since it will always be inserted after cursor, precursor (if null, will become not null)
            // and cursor becomes the element
            // 3. head_ptr == tail_ptr
            list_insert(cursor, entry);
            if (cursor == tail_ptr)
                tail_ptr = cursor->link();
            precursor = cursor;
            cursor = cursor->link();
        }
        ++many_nodes;
    }
    void sequence::operator =(const sequence& source){
        if (head_ptr != NULL){
            node * temp = head_ptr;
            node * temp2 = head_ptr->link();
            while (temp != NULL) {
                delete temp;
                temp = temp2;
                if (temp2 != NULL)
                    temp2 = temp2->link();
            }
            delete temp;
            head_ptr = NULL;
            tail_ptr = NULL;
            cursor = NULL;
            precursor = NULL;
            many_nodes = 0;
        }
        if (source.head_ptr != NULL){
            node * track = source.head_ptr;
            node * new_track = NULL;
            while (track != NULL){
                if (new_track == NULL){
                    new_track = new node(source.head_ptr->data());
                    head_ptr = new_track;
                }
                else {
                    new_track->set_link(new node(track->data()));
                    new_track = new_track->link();
                }
                if(track == source.cursor)
                    cursor = new_track;
                else if (track == source.precursor)
                    precursor = new_track;
                track = track->link();
            }
            tail_ptr = new_track;
            many_nodes = source.many_nodes;
        }
    }
    void sequence::remove_current( ){
        assert(is_item());
        if (cursor == head_ptr){
            precursor = head_ptr->link();
            list_head_remove(head_ptr);
            cursor = head_ptr;
        }
        else {
            
            if (cursor == tail_ptr){
                tail_ptr = precursor;
                cursor = NULL;
            }
            else {
                cursor = cursor->link();
            }
            list_remove(precursor);
            
        }
        many_nodes--;
    }
    
    // CONSTANT MEMBER FUNCTIONS
    sequence::size_type sequence::size( ) const{
        return many_nodes;
    }
    bool sequence::is_item( ) const{
        if(cursor != NULL){
            return true;
        }
        else{
            return false;
        }
    }
    node::value_type sequence::current( ) const{
        if(is_item()){
            return cursor->data();
        }
        return 0;
    }
    

    
}
