#ifndef LOGICERROR_H
#define LOGICERROR_H

#include "baseexception.h"

class LogicException : public BaseException
{
public:
    LogicException() = default;
    LogicException(std::string filename, std::string classname, int line,
                   std::string info = "Logic exception") :
        BaseException(filename, classname, line, info) { }

    virtual const char *what() const noexcept override
    {
        return errormsg.c_str();
    }
};

class NoSceneCameraException : public LogicException
{
public:
    NoSceneCameraException() = default;
    NoSceneCameraException(std::string filename, std::string classname, int line,
                   std::string info = "There isn't any camera in scene") :
        LogicException(filename, classname, line, info) { }

    virtual const char *what() const noexcept override
    {
        return errormsg.c_str();
    }
};

class BadLightSourceArgument : public LogicException
{
public:
    BadLightSourceArgument() = default;
    BadLightSourceArgument(std::string filename, std::string classname, int line,
                   std::string info = "Bad argument setting attempt") :
        LogicException(filename, classname, line, info) { }

    virtual const char *what() const noexcept override
    {
        return errormsg.c_str();
    }
};

class BadMaterialPropertyArgument : public LogicException
{
public:
    BadMaterialPropertyArgument() = default;
    BadMaterialPropertyArgument(std::string filename, std::string classname, int line,
                   std::string info = "Bad argument setting attempt") :
        LogicException(filename, classname, line, info) { }

    virtual const char *what() const noexcept override
    {
        return errormsg.c_str();
    }
};

class NoSuchVertexException : public LogicException
{
public:
    NoSuchVertexException() = default;
    NoSuchVertexException(std::string filename, std::string classname, int line,
                   std::string info = "Attempt to add index for not existing vertex") :
        LogicException(filename, classname, line, info) { }

    virtual const char *what() const noexcept override
    {
        return errormsg.c_str();
    }
};

class NoFragmentShaderException : public LogicException
{
public:
    NoFragmentShaderException() = default;
    NoFragmentShaderException(std::string filename, std::string classname, int line,
                   std::string info = "Bad args") :
        LogicException(filename, classname, line, info) { }

    virtual const char *what() const noexcept override
    {
        return errormsg.c_str();
    }
};

class NotImplementedException : public LogicException
{
public:
    NotImplementedException() = default;
    NotImplementedException(std::string filename, std::string classname, int line,
                   std::string info = "Not implemented") :
        LogicException(filename, classname, line, info) { }

    virtual const char *what() const noexcept override
    {
        return errormsg.c_str();
    }
};

class NoDrawerException : public LogicException
{
public:
    NoDrawerException() = default;
    NoDrawerException(std::string filename, std::string classname, int line,
                   std::string info = "Drawer is still not set") :
        LogicException(filename, classname, line, info) { }

    virtual const char *what() const noexcept override
    {
        return errormsg.c_str();
    }
};

#endif // LOGICERROR_H
