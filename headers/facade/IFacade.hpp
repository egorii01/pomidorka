#ifndef IFACADE_HPP
#define IFACADE_HPP

#include "IMainWindowFacade.hpp"
#include "ISettingsWindowFacade.hpp"
#include "IConfigManagerFacade.hpp"
#include "../data/SettingsData.hpp"

class IFacade : 
public IMainWindowFacade, 
public ISettingsWindowFacade,
public IConfigManagerFacade {

};

#endif