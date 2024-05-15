#ifndef _CONFIG_HPP
#define _CONFIG_HPP

#include <common.hpp>

struct self_t {
    bool godmode = false;
};

class Config {
public:
    static Config* Instance();
    void Uninitialize();
public:
    self_t self;
};

#endif