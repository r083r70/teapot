#include "core/application.h"

int main(void)
{
    Teapot::Application app("Test", 800, 400);
    app.Run();
    
    return 0;
}