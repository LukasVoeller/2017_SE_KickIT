/*
 * Test.hpp
 *
 *  Created on: 24.08.2017
 *      Author: student
 */

#ifndef UTIL_TEST_HPP_
#define UTIL_TEST_HPP_

#include <vector>
#include <string>

static void machWas(std::vector<void*>* params){
	std::string s = *((std::string*)params->at(0));
	std::cout << "machwas: " << s << std::endl;
}

static void machWasAnderes(std::vector<void*>* params){
	std::string s = *((std::string*)params->at(0));
	std::cout << "machWasAnders: " << s << std::endl;
}

#endif /* UTIL_TEST_HPP_ */
