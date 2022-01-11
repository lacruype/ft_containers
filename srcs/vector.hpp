#ifndef ARRAY_HPP
#define ARRAY_HPP
#pragma once

#include <iostream>
#include <exception>

namespace ft 
{
    template< class T, class Allocator = std::allocator<T> >
    class Vector
    {
        private:
            T					value_type;
            Allocator			allocator_type;
			std::size_t			size_type;
			std::ptrdiff_t		difference_type;
			value_type&			reference;
			Allocator::pointer	pointer;
			Allocator::const pointer pointer;
        public:
            Vector();
            Vector(const Array &copy);
            virtual ~Vector();
            Vector<T> &operator=(Vector<T> const &other);
        
    };
}


#endif