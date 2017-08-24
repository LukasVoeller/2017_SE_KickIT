#ifndef CONFIGREADER_HPP_INCLUDE_GUARD
#define CONFIGREADER_HPP_INCLUDE_GUARD

#include <string>
#include <exception>
#include <map>

class ParameterNotFoundException: public std::exception {
public:
	ParameterNotFoundException(const char* name):p(name){
		std::cout << p << " not found in config-file!" << std::endl;
	}
protected:
    std::string p;
};

class UnknownParameterTypeException: public std::exception {
public:
	UnknownParameterTypeException(const char* type):t(type){
		std::cout << t << " is an unknown type!" << std::endl;
	}
protected:
    std::string t;
};

class CannotOpenConfigFileException: public std::exception {

public:
	CannotOpenConfigFileException(const char* filename):fn(filename){
		std::cout << fn << " not found!" << std::endl;
	}
protected:
    std::string fn;
};

class ConfigFileChangedException: public std::exception {
public:
	ConfigFileChangedException(const char* filename):fn(filename){
		std::cout << fn << " seems to have changed while KickIT was running!" << std::endl;
	}
protected:
    std::string fn;
};

class ConfigReader {

public:

	ConfigReader(const char* filename);

    std::string getStringValue(const char* name);
    int getIntValue(const char* name);

    void setStringValue(const char* name, const char* value);
    void setIntValue(const char* name, const int value);

    void writeOut();

protected:
    const char* filename;
    bool valueChanged = false;

    std::map<std::string, int> values;
    std::map<std::string, std::string> strings;

    void readFile();

};


#endif
