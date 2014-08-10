//
//  main.cpp
//  Set
//
//  Created by Antonio Seprano on 10/08/14.
//  Copyright (c) 2014 Antonio Seprano. All rights reserved.
//

#include <iostream>
#include "Set.hpp"

int main(int argc, const char * argv[]) {
	// insert code here...
	Set s1{1,2,3,5}, s2{1,2,4,5}, s3 = s1.intersection(s2);
	
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

