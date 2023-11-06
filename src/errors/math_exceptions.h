#ifndef MATH_EXCEPTIONS_H
#define MATH_EXCEPTIONS_H

#include "runtime_exceptions.h"

class MathException : public BaseException
{
public:
    MathException() = default;
    MathException(std::string filename, std::string classname, int line,
                   std::string info = "Math exception") :
        BaseException(filename, classname, line, info) { }

    virtual const char *what() const noexcept override
    {
        return errormsg.c_str();
    }
};

class ZeroAspectRatio : public MathException
{
public:
    ZeroAspectRatio() = default;
    ZeroAspectRatio(std::string filename, std::string classname, int line,
                   std::string info = "Aspect ration shouldn't be zero") :
        MathException(filename, classname, line, info) { }

    virtual const char *what() const noexcept override
    {
        return errormsg.c_str();
    }
};

#endif