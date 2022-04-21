#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <stdexcept>
# include "vector_iterator.hpp"
# include "reverse_iterator.hpp"
# include "lexicographical_compare.hpp"
# include "equal.hpp"
# include "enable_if.hpp"
# include "is_integral.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef vector_iterator<pointer>					iterator;
			typedef vector_iterator<const_pointer>				const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef std::ptrdiff_t								difference_type;
			typedef size_t										size_type;

		private:
			size_t	_size;
			size_t	_capacity;
			Alloc	_alloc;
			T*		_array;

		public:

		/////////////////////////     Constructors      /////////////////////////////////

			explicit vector(const allocator_type& alloc = allocator_type())	:
				_size(0),
				_capacity(0),
				_alloc(alloc),
				_array(NULL)
			{}

			explicit vector(size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type())	:
				_size(n),
				_capacity(n),
				_alloc(alloc),
				_array(NULL)
			{
				this->_array = this->_alloc.allocate(this->_capacity);
				for (size_t i = 0; i < this->_size; i++)
					this->_alloc.construct(this->_array + i, val);
			}

			template <class InputIterator>
			vector(typename ft::enable_if< !ft::is_integral< InputIterator >::value, InputIterator >::type first,
				InputIterator last, const allocator_type& alloc = allocator_type())	:
				_size(0),
				_capacity(0),
				_alloc(alloc),
				_array(NULL)
			{
				for (; first != last; first++)
				this->push_back(*first);
			}

			vector(const vector& x)	:
				_size(0),
				_capacity(0),
				_array(NULL)
			{
				*this = x;
			}

		/////////////////////////////     Destructor      /////////////////////////////

			~vector()
			{
				if (this->_capacity != 0)
				{
					for (size_t i = 0; i < this->_size; i++)
						this->_alloc.destroy(this->_array + i);
					this->_alloc.deallocate(this->_array, this->_capacity);
				}
			}

		/////////////////////     Operator= overload      /////////////////////////

			vector& operator= (const vector& x)
			{
				if (this != &x)
				{
					this->~vector();
					this->_size = x._size;
					this->_capacity = x._capacity;
					this->_alloc = x._alloc;
					if (this->_capacity != 0)
						this->_array = this->_alloc.allocate(this->_capacity);
					for (size_t i = 0; i < this->_size; i++)
						this->_alloc.construct(this->_array + i, x._array[i]);
				}
				return (*this);
			}

		/////////////////////////     Iterators      /////////////////////////////////

			iterator begin()
			{
				return iterator(this->_array);
			}

			const_iterator begin() const
			{
				return const_iterator(this->_array);
			}

			iterator end()
			{
				return iterator(this->_array + this->_size);
			}

			const_iterator end() const
			{
				return const_iterator(this->_array + this->_size);
			}

			reverse_iterator rbegin()
			{
				return reverse_iterator(this->end());
			}

			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(this->end());
			}

			reverse_iterator rend()
			{
				return reverse_iterator(this->begin());
			}

			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(this->begin());
			}


		/////////////////////////     Capacity      /////////////////////////////////

			size_type size() const
			{
				return (this->_size);
			}

			size_type max_size() const
			{
				return (this->_alloc.max_size());
			}

			void resize(size_type n, value_type val = value_type())
			{
				if (n > this->_size)
				{
					redimension(n);
					for (size_t i = this->_size; i < n; i++)
						push_back(val);
				}
				else if (n < this->_size)
					for (size_t i = this->_size - n; i > 0; i--)
						pop_back();
			}

			size_type capacity() const
			{
				return (this->_capacity);
			}

			bool empty() const
			{
				return (this->_size == 0);
			}

			void reserve (size_type n)
			{
				if (n > this->_capacity)
				{
					if (n > this->max_size())
						throw std::length_error("vector::reserve");
					redimension(n);
				}
			}

		//////////////////////     Element access      ///////////////////////////

			reference operator[] (size_type n)
			{
				return (this->_array[n]);
			}

			const_reference operator[] (size_type n) const
			{
				return (this->_array[n]);
			}

			reference at(size_type n)
			{
				if (n >= this->_size)
					throw std::out_of_range("Index out of vector bounds!");
				return (this->_array[n]);
			}

			const_reference	at (size_type n) const
			{
				if (n >= this->_size)
					throw std::out_of_range("Index out of vector bounds!");
				return (this->_array[n]);
			}

			reference front()
			{
				return (this->_array[0]);
			}

			const_reference front() const
			{
				return (this->_array[0]);
			}

			reference back()
			{
				return (this->_array[this->_size - 1]);
			}

			const_reference back() const
			{
				return (this->_array[this->_size - 1]);
			}


		/////////////////////////     Modifiers      /////////////////////////////////

			void assign(size_type n, const value_type& val)
			{
				this->clear();
				for (size_type i = 0; i < n; i++)
					this->push_back(val);
			}

			template <class InputIterator>
			void assign(typename ft::enable_if<!is_integral<InputIterator>::value,
				InputIterator>::type first, InputIterator last)
			{
				size_t	i = last - first;
				this->clear();

				if (this->_capacity < i)
					this->reserve(i);
				while (first != last)
				{
					this->push_back(*first);
					first++;
				}
			}

			void push_back(const value_type& val)
			{
				if (!this->_capacity)
				{
					this->_array = this->_alloc.allocate(1);
					this->_capacity++;
				}
				else if (this->_size == this->_capacity)
					redimension(this->_capacity * 2);
				this->_alloc.construct(this->_array + this->_size, val);
				this->_size++;
			}

			void pop_back()
			{
				if (!this->empty())
				{
					this->_alloc.destroy(this->_array + (this->_size - 1));
					this->_size --;
				}
			}

			iterator insert(iterator position, const value_type& val)
			{
				if (this->_capacity == this->max_size())
					return (NULL);
				if (this->_capacity == 0)
				{
					this->push_back(val);
					return (position);
				}

				if (this->_capacity == this->_size)
				{
					std::ptrdiff_t pos = position - this->begin();
					this->redimension(2 * this->_capacity);
					position = this->begin() + pos;
				}

				vector tmp(position, this->end());
				for (size_t i = 0; i < tmp.size(); i++)
					this->pop_back();
				this->push_back(val);
				for (iterator it = tmp.begin(); it != tmp.end(); it++)
					this->push_back(*it);

				return (position);
			}

			void insert(iterator position, size_type n, const value_type& val)
			{
				if (this->_size + n > this->_capacity)
				{
					std::ptrdiff_t pos = position - this->begin();
					if (this->_capacity == this->_size)
					{
						this->redimension(std::max(2 * this->_capacity, this->_size + n));
						position = this->begin() + pos;
					}
					else
					{
						if (this->_size + n <= this->_capacity + 2)
							this->redimension(this->_capacity + 2);
						else
							this->redimension(this->_size + n);
					}
					position = this->begin() + pos;
				}
				for (size_type i = 0; i < n; i++)
				{
					this->insert(position, val);
					position++;
				}
			}

			template <class InputIterator>
			void insert(iterator position, typename enable_if<!is_integral<InputIterator>::value,
				InputIterator>::type first, InputIterator last)
			{
				std::ptrdiff_t count = last - first;
				std::ptrdiff_t pos = position - this->begin();

				while (this->_capacity < this->_size + count)
					this->reserve(this->_capacity == 0 ? 1 : this->_capacity * 2);
				for (std::ptrdiff_t i = this->_size; i > pos; i--)
					this->_alloc.construct(_array + i - 1 + count, this->_array[i - 1]);
				std::ptrdiff_t	former_size = this->_size;
				this->_size += count;
				while (count--)
				{
					last--;
					if (pos + count < former_size)
						this->_alloc.destroy(this->_array + pos + count);
					this->_alloc.construct(this->_array + pos + count, *last);
				}
			}

			iterator erase(iterator position)
			{
				if (this->empty() == true || position > this->end())
					return (NULL);

				vector tmp(position + 1, this->end());

				for (size_t i = 0; i <= tmp.size(); i++)
					this->pop_back();
				for (iterator it = tmp.begin(); it != tmp.end(); it++)
					this->push_back(*it);
				return position;
			}

			iterator erase(iterator first, iterator last)
			{
				if (this->empty() == true || last > this->end() || first > this->end())
					return (NULL);
				iterator tmp = first;
				while (tmp != last)
				{
					erase(first);
					tmp++;
				}
				return (first);
			}

			void swap(vector& x)
			{
				allocator_type tmp_alloc = x._alloc;
				size_type tmp_size = x._size;
				size_type tmp_capacity = x._capacity;
				pointer tmp_array = x._array;

				x._alloc = this->_alloc;
				this->_alloc = tmp_alloc;
				x._size = this->_size;
				this->_size = tmp_size;
				x._capacity = this->_capacity;
				this->_capacity = tmp_capacity;
				x._array = this->_array;
				this->_array = tmp_array;
			}

			void clear()
			{
				for (size_t i = 0; i < this->_size; i++)
					this->_alloc.destroy(this->_array + i);
				this->_size = 0;
			}

		/////////////////////////     Allocator      /////////////////////////////////

			allocator_type get_allocator() const
			{
				return (this->_alloc);
			}

		private:

			void redimension(size_type n)
			{
				pointer new_alloc = this->_alloc.allocate(n);
				for (size_type i = 0; i < this->_size; i++)
				{
					this->_alloc.construct(new_alloc + i, this->_array[i]);
					this->_alloc.destroy(this->_array + i);
				}
				if (this->_capacity != 0)
					this->_alloc.deallocate(this->_array, this->_capacity);
				this->_array = new_alloc;
				this->_capacity = n;
			}
	};


	///////////////////////     Non-member function overloads      ////////////////////////

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}
}

#endif
