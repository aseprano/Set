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
	Set<int,SetCompare<int>> s1{1,2,3,5}, s2{1,2,4,5}, s3 = s1.intersection(s2);
	
	if (s3.empty()) {
		std::cout << "s3 is empty" << std::endl;
	}
	else {
		std::cout << "s3: " << std::endl;
		for (const auto& v : s3) {
			std::cout << v << std::endl;
		}
	}
	
	return 0;
}

