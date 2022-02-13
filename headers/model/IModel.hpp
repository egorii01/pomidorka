#ifndef IMODEL_HPP
#define IMODEL_HPP

#include "../observers/Observable.hpp"
#include "IConfigGetter.hpp"
#include "IWindowUpdater.hpp"
#include "../data/SettingsData.hpp"
#include <queue>

class IModel :
public Observable,
public IConfigGetter<SettingsData>,
public IWindowUpdater {
public:
    virtual Notification get_notification() = 0;
};

#endif