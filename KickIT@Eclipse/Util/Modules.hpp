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

typedef void (*fp)(std::vector<void*>*);

class Modules {
protected:
	std::map<std::string, fp> functions;
public:
	Modules(){}

	void registerFunction(std::string name, fp function){
		if(functions.insert(std::pair<std::string, fp>(name, function)).second == false){
			throw("algorithm" + name + "already registered");
		}
	}

	void execute(std::string algo, std::vector<void*>* params){
		std::map<std::string, fp>::iterator it = functions.find(algo);
		if(it == functions.end()){
			throw("algorithm: " + algo + " not registered!");
		}
		it->second(params);
	}

	virtual ~Modules(){}
};

#endif /* UTIL_MODULES_HPP_ */
