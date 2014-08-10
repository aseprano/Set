//
//  main.cpp
//  Set
//
//  Created by Antonio Seprano on 10/08/14.
//  Copyright (c) 2014 Antonio Seprano. All rights reserved.
//

#include <iostream>
#include "Set.hpp"

template<class K>
class SetCompare {
public:
	bool operator()(const K& v1, const K& v2) const noexcept {
		return v1 > v2;
	}
};

int main(int argc, const char * argv[]) {
	// insert code here...
	Set<int> s1{1,2,3,5}, s2{1,2,4,5}, s3 = s1+s2;
	
	auto it = s1.find(90);
	
	if (it != s1.end()) {
		std::cout << "Found value: " << *it << std::endl;
	}
	else {
		std::cout << "Value not found" << std::endl;
	}
	
	return 0;
}

