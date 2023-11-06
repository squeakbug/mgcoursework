#ifndef RUNTIME_EXCEPTIONS_H
#define RUNTIME_EXCEPTIONS_H

#include "baseexception.h"

class RuntimeException : public BaseException
{
public:
    RuntimeException() = default;
    RuntimeException(std::string filename, std::string classname, int line,
                   std::string info = "Runtime exception") :
        BaseException(filename, classname, line, info) { }

    virtual const char *what() const noexcept override
    {
        return errormsg.c_str();
    }
};

class BadAllocException : public RuntimeException
{
public:
    BadAllocException() = default;
    BadAllocException(std::string filename, std::string classname, int line,
                   std::string info = "Bad alloc exception") :
        RuntimeException(filename, classname, line, info) { }

    virtual const char *what() const noexcept override
    {
        return errormsg.c_str();
    }
};

class BadHeightmapRectangleException : public RuntimeException
{
public:
    BadHeightmapRectangleException() = default;
    BadHeightmapRectangleException(std::string filename, std::string classname, int line,
                   std::string info = "Bad heightmap rectangle") :
        RuntimeException(filename, classname, line, info) { }

    virtual const char *what() const noexcept override
    {
        return errormsg.c_str();
    }
};

class FileSystemException : public RuntimeException
{
public:
    FileSystemException() = default;
    FileSystemException(std::string filename, std::string classname, int line,
                   std::string info = "Failure during working with file system") :
        RuntimeException(filename, classname, line, info) { }

    virtual const char *what() const noexcept override
    {
        return errormsg.c_str();
    }
};

class WritingDataException : public FileSystemException
{
public:
    WritingDataException() = default;
    WritingDataException(std::string filename, std::string classname, int line,
                   std::string info = "Failure during saving image") :
        FileSystemException(filename, classname, line, info) { }

    virtual const char *what() const noexcept override
    {
        return errormsg.c_str();
    }
};

class ReadingDataException : public FileSystemException
{
public:
    ReadingDataException() = default;
    ReadingDataException(std::string filename, std::string classname, int line,
                   std::string info = "Failure during loading image") :
        FileSystemException(filename, classname, line, info) { }

    virtual const char *what() const noexcept override
    {
        return errormsg.c_str();
    }
};


class EmptyFilenameException : public FileSystemException
{
public:
    EmptyFilenameException() = default;
    EmptyFilenameException(std::string filename, std::string classname, int line,
                   std::string info = "Couldn't save/load by path with empty filename") :
        FileSystemException(filename, classname, line, info) { }

    virtual const char *what() const noexcept override
    {
        return errormsg.c_str();
    }
};

class NoGridYetException : public RuntimeException
{
public:
    NoGridYetException() = default;
    NoGridYetException(std::string filename, std::string classname, int line,
                   std::string info = "No grid yet") :
        RuntimeException(filename, classname, line, info) { }

    virtual const char *what() const noexcept override
    {
        return errormsg.c_str();
    }
};

class BadArgsToGridGeneratorException : public RuntimeException
{
public:
    BadArgsToGridGeneratorException() = default;
    BadArgsToGridGeneratorException(std::string filename, std::string classname, int line,
                   std::string info = "Bad args") :
        RuntimeException(filename, classname, line, info) { }

    virtual const char *what() const noexcept override
    {
        return errormsg.c_str();
    }
};

#endif // RUNTIME_EXCEPTIONS_H
