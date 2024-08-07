#ifndef JERROR_H_
#define JERROR_H_

#include <exception>

class JError : public std::exception
{
public:
    JError() {}
    JError(const char* msg) : std::exception(msg) {}
};

#endif //JERROR_H_
