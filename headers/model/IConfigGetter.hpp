#ifndef ICONFIG_GETTER_HPP
#define ICONFIG_GETTER_HPP

template<class T>
class IConfigGetter {
public:
    virtual T get_config() = 0;
};

#endif