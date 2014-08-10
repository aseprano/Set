//
//  main.cpp
//  Set
//
//  Created by Antonio Seprano on 10/08/14.
//  Copyright (c) 2014 Antonio Seprano. All rights reserved.
//

#include <iostream>
#include <sstream>
#include "Set.hpp"

using std::string;

template<class T>
std::string toString(const T& t) {
	std::stringstream ss;
	ss << t;
	return ss.str();
}

template<class T>
std::string toString(const Set<T>& s) {
	std::stringstream ss;
	bool fFirstItem{true};
	
	ss << "{";
	
	for (const auto& value : s) {
		if (!fFirstItem) {
			ss << ",";
		}
		else {
			fFirstItem = false;
		}
		
		ss << toString(value);
	}
	
	return ss.str() + "}";
}

int main(int argc, const char * argv[]) {
	Set<int> s1{1,2,3}, s2{1,2,4}, s3 = (s1-s2)+(s2-s1);
	auto n = (s1+s2).count(1);
	std::cout << n << std::endl;
	
	return 0;
}

