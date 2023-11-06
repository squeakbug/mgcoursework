#include "application.h"

Application::Application()
{

}

std::shared_ptr<Application> Application::instance()
{
    static std::shared_ptr<Application> app(new Application);

    return app;
}

void Application::execute(BaseCommand &command)
{
    command.execute();
}
