#ifndef BASEERROR_H
#define BASEERROR_H

#include <exception>
#include <string>

class BaseException : public std::exception
{
protected:
    std::string errormsg;

public:
    BaseException(std::string filename, std::string classname, int line,
                  std::string info = "Error")
    {
        errormsg = "Имя файла: " + filename
                 + "\nНазвание класса: " + classname
                 + "\nНомер строки: " + std::to_string(line)
                 + "\nИнформация: " + info
                 + "\n";
    }

    virtual ~BaseException() { }

    virtual const char *what() const noexcept override
    {
        return errormsg.c_str();
    }
};

#endif // BASEERROR_H
