/*
 * Modules.hpp
 *
 *  Created on: 24.08.2017
 *      Author: student
 */

#ifndef UTIL_MODULES_HPP_
#define UTIL_MODULES_HPP_

#include <vector>
#include <map>
#include <string>
#include <exception>
#include "ConfigReader.hpp"

typedef void (*fp)(std::vector<void*>*);

class FunctionNotFoundException: public std::exception {
public:
	FunctionNotFoundException(const char* name):n(name){
		std::cout << n << " function not registered!" << std::endl;
	}
protected:
    std::string n;
};

class FunctionAllreadyRegistered: public std::exception {
public:
	FunctionAllreadyRegistered(const char* name):n(name){
		std::cout << n << " function allready registered!" << std::endl;
	}
protected:
    std::string n;
};

class Modules {
protected:
	std::map<std::string, fp> functions;
	ConfigReader cr;
public:
	Modules():cr("configuration/Algorithm.txt"){

	}

	void registerFunction(const char* name, fp function){
		std::string name_string(name);
		if(functions.insert(std::pair<std::string, fp>(name_string, function)).second == false){
			throw new FunctionAllreadyRegistered(name);
		}
	}

	void execute(const char* algo, std::vector<void*>* params){
		//find out which function is referenced by config-file
		std::string functionNameFromConfigFile = cr.getStringValue(algo);
		//look up if that function has been registered
		std::map<std::string, fp>::iterator it = functions.find(functionNameFromConfigFile);
		if(it == functions.end()){
			throw new FunctionNotFoundException(functionNameFromConfigFile.c_str());
		}
		it->second(params);
	}

	virtual ~Modules(){}
};

#endif /* UTIL_MODULES_HPP_ */
