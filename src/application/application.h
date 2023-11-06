#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

#include "commands/basecommand.h"

class Application
{
public:
    static std::shared_ptr<Application> instance();

    void execute(BaseCommand &command);

private:
    Application();
    Application(const Application &other) = delete;
    Application &operator=(const Application &other) = delete;
};

#endif // APPLICATION_H
