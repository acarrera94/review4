/********************************************
*** PLEASE PUT YOUR NAME IN THE SPACE BELOW:
*** Andre Carrera
***   
***
********************************************/

// You may modify any part of this file, but you must not change the name of the
// class or any of the method declarations.  If you do, your project will not
// compile.

#pragma once

#include <stdexcept>

namespace cs235
{
	template <typename type>
	class Stack
	{
	private:
		// Put all your private declarations here.  You'll need some kind of 
		// private node class, a start-pointer, and a count.
        /*class Node {
            type data;
            Node *next;
  Node(type value)
            {
                data = value;
                next = NULL;
            }
};*/
        struct Node {
            type data;
            Node *next;
            
            Node(type value)
            {
                data = value;
                next = NULL;
            }
            
        };
        
        
        Node *start;
        int count;
        const int NONE = 0;
        
	public:
		// This is your constructor.  You need to initialize all your fields.
		// Please use member initializer lists, as this is good practice.
		Stack()
		{
            count = 0;
            start = nullptr;
            
		}

		// This is your destructor.  Make sure you delete all the nodes in the
		// list.
		~Stack()
		{
            while (true)
            {
                Node*temp = start;
                if(!temp){
                    break;
                }
                start = start-> next;
                delete temp;
            }
            
		}

		// This method should return a count of items in the stack.  You should
		// keep the count in a private field, and not iterate through the stack
		// every time.
		size_t Count()
		{
            return count;
		}

		// This pushes a new item to the top of the stack.
		void Push(type item)//got rid of reference here, needed?
        
		{
            Node*newNode = new Node(item);//create a new instance
            newNode-> next = start;// the new node is next pointer is pointing to the last node
            start = newNode;//the start is pointing to the new node
            count++;
		}

		// This removes an item from the top of the stack.  You do not have to
		// return anything.  If the count is zero, you should throw an 
		// out_of_range exception.
		void Pop()
		{
            if (count == NONE){
                throw std::out_of_range ("Index out of bounds.");;//check back to this
                
            }
            type data = start->data;
            Node *temp = start;
            start = start->next;
            delete temp;
            count--;
		}

		// This returns the value of the item that is at the top of the stack.  
		// If the stack is empty, this method should throw an out_of_range 
		// exception.
		type& Peek()
		{
            if (start == nullptr){
                throw std::out_of_range ("Index out of bounds.");
            }
            return start-> data;
		}

		// This will peek at the nth item down the stack.  The count should be
		// zero-based.  If the stack is empty, or if pos is >= to the count of
		// items in the stack, then throw an out_of_range exception.
		type& PeekAt(size_t pos)
		{
            if (start == nullptr|| pos >= count){
                throw std::out_of_range ("Index out of bounds.");
            }
            //figure out how to loop into the right one.
             Node* current = start;
            int count = 0; /* the index of the node we're currently
                            looking at */
            while (current != NULL)
            {
                if (count == pos)
                    return(current->data);
                count++;
                current = current->next;
            }

                return current->data;
		}

		// This will insert a value in the middle of the stack.  The item should
		// be inserted BEFORE the item indicated by pos.  If pos is equal to the
		// current count of items, then this method will append to the end of
		// the stack.  If pos is zero, then this method will essentially do the
		// same thing as Push().
		void InsertAt(type item, size_t pos)//removed reference to item because it didn't compile?
		{
            if ( pos > count){
                throw std::out_of_range ("Index out of bounds.");
            }
            else if (pos == NONE){//this will add it to the start of the stack, the head
                Push(item);
            }//make one to add to tail and one to add anywhere?
            else{
                
                
                    Node* current = start;
                    int counter = 0; /* the index of the node we're currently
                                    looking at */
                    while (current != NULL)
                    {
                        if (counter == pos-1)
                            break;
                        counter++;
                        current = current->next;
                    }
                    Node*newNode = new Node(item);
                    newNode-> next = current->next;
                    current->next = newNode;
                    
                
                count++;
            }
            
		}

		// This will clear all items in the stack, and reset the count to zero.
		void Clear()
		{
            while (true)
            {
                Node*temp = start;
                if(!temp){
                    break;
                }
                start = start-> next;
                delete temp;
            }
            count = NONE;
        }
    
    };
}
