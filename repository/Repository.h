#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "Connection.h"


class Repository
{
private:
    Repository() = default;
    
public:
    Repository(Repository const &) = delete;

    Repository operator=(Repository const &) = delete;

    static Repository& instance();

    ~Repository() = default;
    
};

#endif // REPOSITORY_H
