#ifndef GK_APPLICATION
#define GK_APPLICATION

class Application
{
public:
    virtual ~Application() {}
    virtual void Run() = 0;
    static Application *Create();
};

#endif
