//
//  Set.h
//  Set
//
//  Created by Antonio Seprano on 10/08/14.
//  Copyright (c) 2014 Antonio Seprano. All rights reserved.
//

#include <vector>
#include <functional>
#include <utility>
#include <algorithm>

#ifndef _SET_HPP
#define _SET_HPP

template<class _T, class _Compare = std::less<_T>, class _Allocator = std::allocator<_T>>
class Set {
public:
	typedef _T				  value_type;
	typedef _Allocator	allocator_type;
	typedef _Compare    value_compare;
	
private:
	typedef Set<value_type,value_compare,allocator_type> _SET;
	
public:
	typedef typename std::vector<value_type,allocator_type>::iterator				iterator;
	typedef typename std::vector<value_type,allocator_type>::const_iterator	const_iterator;
	
	// Empty set
	Set() {};
	
	// Set with initializer list
	Set(const std::initializer_list<value_type>& l) {
		_set.reserve(l.size());
		
		for (const auto& value : l) {
			insert(value);
		}
	}
	
	Set(std::initializer_list<value_type>&& l) {
		_set.reserve(l.size());
		
		for (auto& value : l) {
			insert(std::move(value));
		}
	}
	
	// Copy constructor
	Set(const _SET& s) {
		_set = s._set;
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
	
	iterator begin() noexcept {
		return _set.begin();
	}
	
	const_iterator begin() const noexcept {
		return _set.begin();
	}
	
	iterator end() noexcept {
		return _set.end();
	};
	
	const_iterator end() const noexcept {
		return _set.end();
	}
	
	size_t size() const noexcept {
		return _set.size();
	}
	
	bool empty() const noexcept {
		return _set.empty();
	}
	
	void clear() noexcept {
		_set.clear();
	}
	
	iterator find(const value_type& value) noexcept {
		for (auto it = _set.begin(); it != _set.end(); it++) {
			if (!value_compare()(*it,value) && !value_compare()(value,*it)) {
				return it;
			}
		}
		
		return _set.end();
	}
	
	const_iterator find(const value_type& value) const noexcept {
		return (const_iterator)find(value);
	}
	
	size_t count(const value_type& value) const noexcept {
		size_t ret{};
		
		for (const auto& v : _set) {
			if (!value_compare()(v,value) && !value_compare()(value,v)) {
				ret++;
			}
		}
		
		return ret;
	}
	
	bool operator==(const _SET& s) const noexcept {
		return this->contains(s, false) && s.contains(*this, false);
	}
	
	bool operator!=(const _SET& s) const noexcept {
		return !(*this == s);
	};
	
	bool operator<(const _SET& s) const noexcept {
		if (size() != s.size()) {
			return size() < s.size();
		}
		
		auto it1=begin(), it2=s.begin();
		
		while (it1 != end() && it2 != s.end()) {
			if (*it1 < *it2) {
				return true;
			}
			else if (*it1 > *it2) {
				return false;
			}
			
			it1++;
			it2++;
		};
		
		return false;
	}
	
	
	// Insert new value
	// unique = true => values must be unique (no duplicate values allowed)
	_SET& insert(const value_type& value, bool unique = false) noexcept {
		if (!unique || this->find(value) == _set.end()) {
			auto it = begin();
			
			while (it != end() && value_compare()(*it, value)) {
				it++;
			}
			
			_set.insert(it, value);
		}
		
		return *this;
	}
	
	_SET& insert(value_type&& value, bool unique = false) noexcept {
		if (!unique || find(value) == _set.end()) {
			auto it = begin();
			
			while (it != end() && value_compare()(*it, value)) {
				it++;
			}
			
			_set.insert(it, std::move(value));
		}
		
		return *this;
	}
	
	
	_SET operator+(const value_type& value) const noexcept {
		return _SET{*this}+_SET{value};
	}
	
	_SET operator+(value_type&& value) const noexcept {
		return _SET{*this}+_SET{std::move(value)};
	}
	
	_SET operator+(const _SET& s) const noexcept {
		_SET ret{*this};
		
		for (const auto& value : s) {
			ret.insert(value);
		}
		
		return ret;
	}
	
	_SET operator+(_SET&& s) const noexcept {
		_SET ret{*this};
		
		for (auto& value : s) {
			ret.insert(std::move(value));
		}
		
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
		for (const auto& value : s) {
			insert(value);
		}
		
		return *this;
	}
	
	_SET& operator+=(_SET&& s) noexcept {
		for (auto& value : s) {
			insert(std::move(value));
		}
		
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
	
	
	Set<_SET> operator*(const _SET& other) noexcept {
		Set<_SET> ret;
		
		if (!this->empty() && !other.empty()) {
			for (const auto& v1 : _set) {
				for (const auto& v2 : other) {
					ret.insert(_SET{v1,v2});
				}
			}
		}
		
		return ret;
	}
	
	
	_SET intersectionWith(const _SET& s) noexcept {
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
	
	bool contains(const value_type& value) const noexcept {
		return contains(_SET{value});
	}
	
	bool contains(const _SET& s, bool strict = false) const noexcept {
		for (const auto& value : s) {
			bool found{false};
			
			for (const auto& v : _set) {
				if (!value_compare()(value, v) && !value_compare()(v, value)) {
					found = true;
					break;
				}
			}
			
			if (!found) {
				return false;
			}
		}
		
		return strict ? (s.size() != size()) : true;
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
	
	iterator erase(const_iterator first, const_iterator last) {
		return _set.erase(first,last);
	}
	
	size_t erase(const value_type& value, bool all = false) {
		size_t ret{};
		
		if (!all) {
			auto it = find(value);
			
			if (it != end()) {
				erase(it);
				ret++;
			}
			
			return ret;
		}
		
		for (auto it = _set.begin(); it != _set.end(); it++) {
			if (*it == value) {
				_set.erase(it);
				++ret;
			}
		}
		
		return ret;
	}
	
	_SET& unique() noexcept {
		for (auto i = begin(); i != end(); i++) {
			auto j = i+1;
			
			while (j != end()) {
				if (!value_compare()(*i, *j) && !value_compare()(*j, *j)) {
					_set.erase(j);
				}
				else {
					j++;
				}
			}
		}
		
		return *this;
	}
	
private:
	std::vector<value_type,allocator_type> _set;
};

#endif /* defined(_SET_HPP) */
