// FILE: node.cpp
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
#include <iostream>

using namespace std;

namespace coen79_lab6
{
    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
	const node *cursor;
	size_t answer;

	answer = 0;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	    ++answer;

	return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
    	head_ptr = new node(entry, head_ptr);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
    	node *insert_ptr;

    	insert_ptr = new node(entry, previous_ptr->link( ));
    	previous_ptr->set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	const node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	const node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    void list_head_remove(node*& head_ptr)
    {
        
    	node *remove_ptr;
    	remove_ptr = head_ptr;
    	head_ptr = head_ptr->link( );
    	delete remove_ptr;
    }

    void list_remove(node* previous_ptr)
    {
    	node *remove_ptr;
    	remove_ptr = previous_ptr->link( );
    	previous_ptr->set_link( remove_ptr->link( ) );
    	delete remove_ptr;
    }

    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
        while (head_ptr != NULL)
            list_head_remove(head_ptr);
        
    }

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
    	head_ptr = NULL;
    	tail_ptr = NULL;

    	// Handle the case of the empty list.
    	if (source_ptr == NULL)
    	    return;

    	// Make the head node for the newly created list, and put data in it.
    	list_head_insert(head_ptr, source_ptr->data( ));
    	tail_ptr = head_ptr;

    	// Copy the rest of the nodes one at a time, adding at the tail of new list.
    	source_ptr = source_ptr->link( );
    	while (source_ptr != NULL)
    	{
    	    list_insert(tail_ptr, source_ptr->data( ));
    	    tail_ptr = tail_ptr->link( );
    	    source_ptr = source_ptr->link( );
    	}
    }
    
    void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr){
        if((start_ptr != end_ptr && start_ptr != NULL)){
            head_ptr = new node(start_ptr->data(), start_ptr->link());
            node *new_track = head_ptr;
            node *temp = start_ptr;
            while((temp->link() != end_ptr) && temp != end_ptr){
                node *new_node = new node(temp->link()->data());
                new_track->set_link(new_node);
                new_track = new_track->link();
                temp = temp->link();
                tail_ptr = new_track;
            }
        }
    }
    size_t list_occurrences(node* head_ptr, const node::value_type& target){
        if(head_ptr == NULL) return 0;
        node * temp_ptr = head_ptr;
        size_t count = 0;
        while (temp_ptr != NULL) {
            if(temp_ptr->data() == target) ++count;
            temp_ptr = temp_ptr->link();
        }
        return count;
    }
    void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position){
        assert(position > 0);
        assert(position <= list_length(head_ptr) + 1);
        node * temp = head_ptr;
        if (position == 1){
            node * toInsert = new node(entry, temp);
            head_ptr = toInsert;
        }
        else {
            for (size_t i = 1; i < position - 1; ++i){
                temp = temp->link();
            }
            node * toInsert = new node(entry, temp->link());
            temp->set_link(toInsert);
        }
    }
    node::value_type list_remove_at(node*& head_ptr, size_t position){
        assert(position > 0);
        assert(position <= list_length(head_ptr));
        node::value_type val;
        node * temp = head_ptr;
        if(position == 1){
            val = head_ptr->data();
            head_ptr = temp->link();
            delete temp;
            return val;
        }
        else{
            for (size_t i = 1; i < position - 1; ++i){
                temp = temp->link();
            }
            node * toDelete = temp->link();
            temp->set_link(toDelete->link());
            val = toDelete->data();
            delete toDelete;
            return val;
        }
    }
    node* list_copy_segment(node* head_ptr, size_t start, size_t finish){
        assert(start >= 1);
        assert(finish <= list_length(head_ptr));
        assert(start <= finish);
        node * temp = head_ptr;
        for (size_t i = 1; i < start; i++){
            temp = temp->link();
        }
        node * newList = new node(temp->data());
        node * list_head = newList;
        for (size_t i = start; i < finish; ++i){
            temp = temp->link();
            newList->set_link(new node(temp->data()));
            newList = newList->link();
        }
        return list_head;
    }
    void list_print (const node* head_ptr){
        if(head_ptr != NULL){
            node const * temp = head_ptr;
            for(size_t i = 0; i < list_length(head_ptr); ++i){
                if(temp != NULL){
                    cout << temp->data() << (i == list_length(head_ptr) - 1 ? "" : ", ") ;
                    temp = temp->link();
                }
                else{
                    temp = temp->link();
                }
            }
        }
        cout << endl;
    }
    void list_remove_dups(node* head_ptr){
        if(head_ptr != NULL){
            node* temp = head_ptr;
            node* list_tracker;
            node* removed;
            while (temp->link() != NULL){
                list_tracker = temp;
                while(list_tracker->link() != NULL){
                    if(temp->data() == list_tracker->link()->data()){
                        removed = list_tracker->link();
                        list_tracker->set_link(removed->link());
                        delete removed;
                    }
                    else if(temp->data() != list_tracker->link()->data()){
                        list_tracker = list_tracker->link();
                    }
                    
                }
            }
        }
    }
    node* list_detect_loop (node* head_ptr){
         // Pseudo code for detecting loops.
         // Floyd’s cycle-finding algorithm
         // 1. Declare two pointers slow_runner and fast_runner, where both point to the head of the linked list
         // 2. while (fast_runner != NULL && fast_runner -> link() != NULL)
         // • slow_runner moves one step at a time, and fast_runner moves two steps at a time
         // • Break the loop if slow_runner == fast_runner
         // 3. Return NULL if the two pointers did not meet (i.e.,
         // fast_runner == NULL || fast_runner - > link() == NULL)
         // 4. while (slow_runner != fast_runner)
         // • Both pointers move one step at a time.
        
        node * fast_runner = head_ptr->link()->link();
        node * slow_runner = head_ptr;
        while (fast_runner != NULL && fast_runner->link() != NULL && slow_runner != fast_runner){
            slow_runner = slow_runner->link();
            fast_runner = fast_runner->link()->link();
        }
        if (fast_runner == NULL || fast_runner->link() == NULL)
            return NULL;
        
        while (slow_runner != fast_runner){
            fast_runner = fast_runner->link();
            slow_runner = slow_runner->link();
        }
        return fast_runner;
    }

    
    
}
