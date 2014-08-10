//
//  Set.h
//  Set
//
//  Created by Antonio Seprano on 10/08/14.
//  Copyright (c) 2014 Antonio Seprano. All rights reserved.
//

#include <set>
#include <functional>
#include <utility>
#include <algorithm>

#ifndef _SET_HPP
#define _SET_HPP

template<class _T, class _Compare=std::less<_T>, class _Allocator = std::allocator<_T> >
class Set {
public:
	typedef _T				  value_type;
	typedef _Compare		value_compare;
	typedef _Allocator	allocator_type;
	
private:
	typedef Set<value_type,value_compare,allocator_type> _SET;
	
public:
	typedef typename std::set<value_type,value_compare,allocator_type>::iterator				iterator;
	typedef typename std::set<value_type,value_compare,allocator_type>::const_iterator	const_iterator;
	
	// Empty set
	Set() {};
	
	// Set with initializer list
	Set(std::initializer_list<value_type> l) {
		_set.insert(l);
	}
	
	// Copy constructor
	Set(const _SET& s) {
		_set.insert(s._set.begin(), s._set.end());
	}
	
	// Move constructor
	Set(_SET&& s) {
		_set = std::move(s._set);
	}
	
	// Copy assignment
	_SET& operator=(const _SET& s) noexcept {
		_set = s._set;
		return *this;
	}
	
	// Move assignment
	_SET& operator=(_SET&& s) noexcept {
		_set = std::move(s._set);
		return *this;
	}
	
	bool operator==(const _SET& s) const noexcept {
		return this->size() == s.size() && this->contains(s);
	}
	
	bool operator!=(const _SET& s) const noexcept {
		return !(*this == s);
	};
	
	_SET operator+(const value_type& value) const noexcept {
		return _SET{*this}+_SET{value};
	}
	
	_SET operator+(value_type&& value) const noexcept {
		return _SET{*this}+_SET{std::move(value)};
	}
	
	_SET operator+(const _SET& s) const noexcept {
		_SET ret{*this};
		ret.insert(s);
		return ret;
	}
	
	_SET operator+(_SET&& s) const noexcept {
		_SET ret{*this};
		ret.insert(std::move(s));
		return ret;
	}
	
	_SET& operator+=(const value_type& value) noexcept {
		insert(value);
		return *this;
	}
	
	_SET& operator+=(value_type&& value) noexcept {
		insert(std::move(value));
		return *this;
	}
	
	_SET& operator+=(const _SET& s) noexcept {
		insert(s);
		return *this;
	}
	
	_SET& operator+=(_SET&& s) noexcept {
		insert(std::move(s));
		return *this;
	}
	
	_SET operator-(const value_type& value) const noexcept {
		_SET ret{*this};
		ret.erase(value);
		return ret;
	}
	
	_SET operator-(const _SET& s) const noexcept {
		_SET ret{*this};
		for (const auto& v : s) {
			ret.erase(v);
		}
		return ret;
	}
	
	_SET& operator-=(const value_type& value) noexcept {
		_set.erase(value);
		return *this;
	}
	
	_SET& operator-=(const _SET& s) noexcept {
		for (const auto& value : s) {
			_set.erase(value);
		}
		return *this;
	}
	
	_SET intersection(const _SET& s) noexcept {
		_SET s1, s2;
		
		if (s.size() <= size()) {
			s1 = s;
			s2 = *this;
		}
		else {
			s1 = *this;
			s2 = s;
		}
		
		for (const auto &v : s1) {
			if (!s2.contains(v)) s1.erase(v);
		}
		
		return s1;
	}
	
	iterator begin() const noexcept {
		return _set.begin();
	};
	
	iterator end() const noexcept {
		return _set.end();
	};
	
	size_t size() const noexcept {
		return _set.size();
	};
	
	bool empty() const noexcept {
		return _set.empty();
	};
	
	void clear() noexcept {
		_set.clear();
	}
	
	bool contains(const value_type& value) const noexcept {
		return contains(_SET{value});
	}
	
	bool contains(const _SET& s) const noexcept {
		for (const auto& value : s) {
			if (_set.find(value) == _set.end()) return false;
		}
		
		return true;
	}
	
	std::pair<iterator,bool> insert(const value_type& value) noexcept {
		return _set.insert(value);
	}
	
	std::pair<iterator,bool> insert(value_type&& value) noexcept {
		return _set.insert(std::move(value));
	}
	
	void insert(const _SET& s) noexcept {
		for (const auto& value : s) {
			_set.insert(value);
		}
	}
	
	void insert(_SET&& s) noexcept {
		for (auto& value : s) {
			_set.insert(std::move(value));
		}
	}
	
	template<class InputIterator>
	void insert(InputIterator first, InputIterator last) {
		for (auto it = first; it != last; it++) {
			_set.insert(*it);
		}
	};
	
	iterator erase(const_iterator position) {
		return _set.erase(position);
	}
	
	size_t erase(const value_type& value) {
		return _set.erase(value);
	}
	
	iterator erase(const_iterator first, const_iterator last) {
		return _set.erase(first,last);
	}
	
	size_t erase(const _SET& s) noexcept {
		size_t ret{};
		
		for (const auto& value : s) {
			ret += erase(value);
		}
		
		return ret;
	}
	
	iterator find(const value_type& value) noexcept {
		return _set.find(value);
	}
	
	const_iterator find(const value_type& value) const noexcept {
		return _set.find(value);
	}
	
private:
	std::set<value_type,value_compare,allocator_type> _set;
};

#endif /* defined(_SET_HPP) */
