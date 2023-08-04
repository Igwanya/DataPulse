#include "Repository.h"


Repository &Repository::instance()
{
    static Repository sInstance;
    new Connection();

    return sInstance;
}


