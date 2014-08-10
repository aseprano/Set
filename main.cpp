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
	Set<int> s1{1,2,3}, s2{1,2,4};
	auto s3 = s1*s2;
	
	std::cout << "s1: " << toString(s1) << std::endl;
	std::cout << "s2: " << toString(s2) << std::endl;
	std::cout << "s3: " << toString(s3) << std::endl;
	
	return 0;
}

