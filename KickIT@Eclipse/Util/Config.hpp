#ifndef CONFIG_HPP_INCLUDE_GUARD
#define CONFIG_HPP_INCLUDE_GUARD

#include <string>
#include <exception>
#include <map>

class FileNotFoundException: public std::exception {
    virtual const char* what() const throw()
    {
        return "configuration-file not found!";
    }
};

class ParameterNotFoundException: public std::exception {
    virtual const char* what() const throw()
    {
        return "configuration-value not found!";
    }
};

class UnknownParameterTypeException: public std::exception {
    virtual const char* what() const throw()
    {
        return "configuration-file contains an unknown type!";
    }
};

class CannotOpenConfigFileException: public std::exception {
    virtual const char* what() const throw()
    {
        return "cannot open configuration-file!";
    }
};

class ConfigFileChangedException: public std::exception {
    virtual const char* what() const throw()
    {
        return "seems like the configuration-file has changed while KickIT was running!";
    }
};

class Config {

public:

    Config(const char* filename);

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

    int readFile();

};


#endif