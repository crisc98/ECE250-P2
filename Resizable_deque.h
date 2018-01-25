/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided  code.
 *****************************************/

#ifndef DYNAMIC_DEQUE_H
#define DYNAMIC_DEQUE_H

#include "Exception.h"

template <typename Type>
class Resizable_deque {
	public:
		Resizable_deque( int = 16 );
		Resizable_deque( Resizable_deque const & );
		Resizable_deque( Resizable_deque && );
		~Resizable_deque();

		Type front() const;
		Type back() const;
		int size() const;
		bool empty() const;
		int capacity() const;
        Type at(int) const;

		void swap( Resizable_deque & );
		Resizable_deque &operator=( Resizable_deque const& );
		Resizable_deque &operator=( Resizable_deque && );
		void push_front( Type const & );
		void push_back( Type const & );
		void pop_front();
		void pop_back();
		void clear();

	private:
		// Your member variables
        Type *array;
        int ifront;
        int iback;
        int deque_size;
        int initial_array_capacity;
        int array_capacity;
		// Any private member functions
		//   - helper functions for resizing your array?

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Resizable_deque<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                   Constructors and Destructors                      //
/////////////////////////////////////////////////////////////////////////

// Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( int n )
{
	if(n< 16){
        n=16;
    }
    initial_array_capacity = n;
    array_capacity = n;
    ifront = 0;
    iback = -1;
    deque_size = 0;
    array = new Type[n];
}

// Copy Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque const &deque )
// Your initalization list
{
	initial_array_capacity = deque.capacity();
    array_capacity = deque.capacity();
    ifront = 0;
    iback = deque.size()-1;
    deque_size = deque.size();
    array = new Type[array_capacity];
    std::copy(deque.array, deque.array+deque.size(), array);

}

// Move Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque &&deque )
// Your initalization list
{
    initial_array_capacity = 0;
    array_capacity = 0;
    ifront = 0;
    iback = -1;
    deque_size = 0;
    array = new Type[0];
    std::cout << "Moved" <<std::endl;
	swap(deque);
}

// Destructor
template <typename Type>
Resizable_deque<Type>::~Resizable_deque() {
	delete [] (array);
}

/////////////////////////////////////////////////////////////////////////
//                     Public Member Functions                         //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
int Resizable_deque<Type>::size() const {
	return deque_size;
}

template <typename Type>
int Resizable_deque<Type>::capacity() const {
	// Enter your implementation here
	return array_capacity;
}

template <typename Type>
bool Resizable_deque<Type>::empty() const {
	if(deque_size==0)
        return true;
    else
        return false;
}

template <typename  Type>
Type Resizable_deque<Type>::front() const {
	// Enter your implementation here
    if(empty()){
        throw underflow();
    }
	return array[ifront];
}

template <typename  Type>
Type Resizable_deque<Type>::back() const {
    // Enter your implementation here
    if(empty()){
        throw underflow();
    }
    return array[iback];
}

template <typename Type>
Type Resizable_deque<Type>::at(int n) const {
    return array[n];
}

//template <typename  Type>
//Type* Resizable_deque<Type>::begin() const {
//    // Enter your implementation here
//    return &array[ifront];
//}
//
//template <typename  Type>
//Type* Resizable_deque<Type>::end() const {
//    // Enter your implementation here
//    return &array[iback];
//}

template <typename Type>
void Resizable_deque<Type>::swap( Resizable_deque<Type> &deque ) {
	// Swap the member variables
    std::swap(deque_size, deque.deque_size);
    std::swap(array_capacity, deque.array_capacity);
    std::swap(initial_array_capacity, deque.initial_array_capacity);
    std::swap(iback, deque.iback);
    std::swap(ifront, deque.ifront);
    std::swap(array, deque.array);

	// Enter your implementation here
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> const &rhs ) {
	// This is done for you...
	Resizable_deque<Type> copy( rhs );
	swap( copy );

	return *this;
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> &&rhs ) {
	// This is done for you...
	swap( rhs );

	return *this;
}

template <typename Type>
void Resizable_deque<Type>::push_front( Type const &obj ) {
	if(deque_size==array_capacity) {
        array_capacity *=2;
        Type* old_array = array;
        array = new Type[array_capacity];
        for(int i =0; i<deque_size; i++){
            array[i+1]=old_array[i];
        }
        delete (old_array);
    }
    else{
        for(int i = deque_size; i >= 0; i--){
            array[i] = array[i-1];
        }
    }
    array[0] = obj;
    deque_size++;
    iback++;

}

template <typename Type>
void Resizable_deque<Type>::push_back( Type const &obj ) {
    if(deque_size==array_capacity) {
        array_capacity *=2;
        Type* old_array = array;
        array = new Type[array_capacity];
        for(int i =0; i<deque_size; i++){
            array[i]=old_array[i];
        }
        delete [] (old_array);
    }

    array[iback+1] = obj;
    deque_size++;
    iback++;
}

template <typename Type>
void Resizable_deque<Type>::pop_front() {
    if (empty()){
        throw underflow();
    }
	for(int i=1;i<deque_size;i++){
        array[i-1] = array[i];
    }
    deque_size--;
    iback--;
}

template <typename Type>
void Resizable_deque<Type>::pop_back() {
    if(empty())
        throw underflow();
	array[iback]=0;
    deque_size--;
    if(deque_size/array_capacity <= 0.25&&array_capacity>initial_array_capacity){
        array_capacity/=2;
        Type *old_array = array;
        array = new Type[array_capacity];
        for(int i = 0; i<deque_size; i++){
            array[i]=old_array[i];
        }
        delete [] old_array;
    }
    iback--;

}

template <typename Type>
void Resizable_deque<Type>::clear() {
	deque_size=0;
    ifront=0;
    iback=0;
    array_capacity = initial_array_capacity;
    array = new Type[array_capacity];

}


/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// Enter any private member functios (helper functions) here


/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Resizable_deque<T> const &list ) {
//    for(T* it = list.begin(); it !=list.end(); it++){
//        out << *it << " ";
//    }
    for(int i = 0; i< list.size(); i++){
    out << list.at(i) << " ";
    }
    out << "\n";

	return out;
}

#endif
