//
//  Set.cpp
//  Set
//
//  Created by Antonio Seprano on 10/08/14.
//  Copyright (c) 2014 Antonio Seprano. All rights reserved.
//

#include "Set.hpp"
#include <algorithm>

Set::Set(std::initializer_list<int> l) {
	_set.insert(l);
}

Set::Set(const Set& s) {
	_set.insert(s._set.begin(), s._set.end());
}

Set::Set(Set&& s) {
	_set = std::move(s._set);
}

Set& Set::operator=(const Set &s) noexcept {
	_set = s._set;
	return *this;
}

Set& Set::operator=(Set &&s) noexcept {
	_set = std::move(s._set);
	return *this;
}

bool Set::operator==(const Set &s) const noexcept {
	return this->size() == s.size() && this->contains(s);
}

Set Set::operator+(const int& value) const noexcept {
	return Set{*this}+Set{value};
}

Set Set::operator+(int&& value) const noexcept {
	return Set{*this}+Set{std::move(value)};
}

Set Set::operator+(const Set &s) const noexcept {
	Set ret{*this};
	ret.insert(s);
	return ret;
}

Set Set::operator+(Set&& s) const noexcept {
	Set ret{*this};
	ret.insert(std::move(s));
	return ret;
}

Set& Set::operator+=(const int& value) noexcept {
	insert(value);
	return *this;
}

Set& Set::operator+=(int&& value) noexcept {
	insert(std::move(value));
	return *this;
}

Set& Set::operator+=(const Set &s) noexcept {
	insert(s);
	return *this;
}

Set& Set::operator+=(Set &&s) noexcept {
	insert(std::move(s));
	return *this;
}

Set Set::operator-(const int& value) const noexcept {
	Set ret{*this};
	ret.erase(value);
	return ret;
}

Set Set::operator-(const Set& s) const noexcept {
	Set ret{*this};
	for (const auto& v : s) {
		ret.erase(v);
	}
	return ret;
}

Set& Set::operator-=(const int &value) noexcept {
	erase(value);
	return *this;
}

Set& Set::operator-=(const Set& s) noexcept {
	erase(s);
	return *this;
}

Set Set::intersection(const Set &s) noexcept {
	Set s1, s2;
	
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

void Set::clear() noexcept {
	_set.clear();
}

bool Set::contains(const int &v) const noexcept {
	return contains(Set{v});
}

bool Set::contains(const Set &s) const noexcept {
	for (const auto& v : s) {
		if (_set.find(v) == _set.end()) return false;
	}
	
	return true;
}

std::pair<Set::iterator,bool> Set::insert(const int& value) noexcept {
	return _set.insert(value);
}

std::pair<Set::iterator,bool> Set::insert(int&& value) noexcept {
	return _set.insert(std::move(value));
}

void Set::insert(const Set& s) noexcept {
	for (const auto& v : s) {
		_set.insert(v);
	}
}

void Set::insert(Set &&s) noexcept {
	for (auto& v : s) {
		_set.insert(std::move(v));
	}
}

Set::iterator Set::erase(Set::const_iterator position) {
	return _set.erase(position);
}

size_t Set::erase(const int& value) {
	return _set.erase(value);
}

Set::iterator Set::erase(const_iterator first, const_iterator last) {
	return _set.erase(first, last);
}

size_t Set::erase(const Set &s) noexcept {
	size_t ret{};
	
	for (const auto& v : s) {
		ret += erase(v);
	}
	
	return ret;
}

