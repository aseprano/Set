//
//  Set.h
//  Set
//
//  Created by Antonio Seprano on 10/08/14.
//  Copyright (c) 2014 Antonio Seprano. All rights reserved.
//

#include <set>

#ifndef _SET_HPP
#define _SET_HPP

class Set {
public:
	using iterator=std::set<int>::iterator;
	using const_iterator=std::set<int>::const_iterator;
	
	Set() {};
	Set(std::initializer_list<int> l);
	Set(const Set& s);
	Set(Set&& s);
	Set& operator=(const Set& s) noexcept;
	Set& operator=(Set&& s) noexcept;
	
	bool operator==(const Set& s) const noexcept;
	bool operator!=(const Set& s) const noexcept {return !(*this == s);};
	
	Set operator+(const int& value) const noexcept;
	Set operator+(int&& value) const noexcept;
	Set operator+(const Set& s) const noexcept;
	Set operator+(Set&& s) const noexcept;
	Set& operator+=(const int& value) noexcept;
	Set& operator+=(int&& value) noexcept;
	Set& operator+=(const Set& s) noexcept;
	Set& operator+=(Set&& s) noexcept;
	
	Set operator-(const int& value) const noexcept;
	Set operator-(const Set& s) const noexcept;
	Set& operator-=(const int& value) noexcept;
	Set& operator-=(const Set& s) noexcept;
	
	Set intersection(const Set& s) noexcept;
	
	iterator begin() const noexcept {return _set.begin();};
	iterator end()   const noexcept {return _set.end();};
	
	size_t size() const noexcept {return _set.size();};
	bool empty() const noexcept {return _set.empty();};
	void clear() noexcept;
	
	bool contains(const int& v) const noexcept;
	bool contains(const Set& s) const noexcept;
	
	std::pair<iterator,bool> insert(const int& n) noexcept;
	std::pair<iterator,bool> insert(int&& n) noexcept;
	void insert(const Set& s) noexcept;
	void insert(Set&& s) noexcept;
	
	template<class InputIterator>
	void insert(InputIterator first, InputIterator last) {
		for (auto it = first; it != last; it++) {
			_set.insert(*it);
		}
	};
	
	Set::iterator erase(Set::const_iterator position);
	size_t erase(const int& value);
	iterator erase(const_iterator first, const_iterator last);
	size_t erase(const Set& s) noexcept;
	
private:
	std::set<int> _set;
};

#endif /* defined(_SET_HPP) */
