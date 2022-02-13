GTK = `pkg-config --cflags --libs gtkmm-3.0`

all:
	if [ ! -d objects ]; then mkdir objects; fi
	make pomidorka

pomidorka: main.o GUI.o SettingsWindow.o MainWindow.o AbstractWindow.o ConfigManager.o AppModel.o \
CycleCounter.o Cycle.o ObservableCycle.o Timer.o ObservableTimer.o AudioModule.o
	g++ -pthread -o pomidorka objects/main.o objects/GUI.o objects/AudioModule.o \
	objects/SettingsWindow.o objects/MainWindow.o \
	objects/AbstractWindow.o objects/ConfigManager.o objects/AppModel.o objects/CycleCounter.o \
	objects/Cycle.o objects/ObservableCycle.o objects/Timer.o objects/ObservableTimer.o -lopenal -lalut $(GTK)

main.o: main.cpp GUI.hpp
	g++ -c -o objects/$@ $< $(GTK)

GUI.o: src/gui/GUI.cpp GUI.hpp
	g++ -c -o objects/$@ $< $(GTK)

SettingsWindow.o: src/gui/window/SettingsWindow.cpp SettingsWindow.hpp
	g++ -c -o objects/$@ $< $(GTK)

MainWindow.o: src/gui/window/MainWindow.cpp MainWindow.hpp
	g++ -c -o objects/$@ $< $(GTK)

AbstractWindow.o: src/gui/window/AbstractWindow.cpp AbstractWindow.hpp
	g++ -c -o objects/$@ $< $(GTK)

AudioModule.o: src/audio/AudioModule.cpp AudioModule.hpp
	g++ -c -o objects/$@ $< -lopenal -lalut

ConfigManager.o: src/configManager/ConfigManager.cpp ConfigManager.hpp
	g++ -c -o objects/$@ $<

AppModel.o: src/model/AppModel.cpp AppModel.hpp
	g++ -c -o objects/$@ $<

CycleCounter.o: src/cyclecounter/CycleCounter.cpp CycleCounter.hpp
	g++ -c -o objects/$@ $<

Cycle.o: src/cycle/Cycle.cpp Cycle.hpp
	g++ -c -o objects/$@ $<

ObservableCycle.o: src/cycle/ObservableCycle.cpp ObservableCycle.hpp
	g++ -c -o objects/$@ $<

Timer.o: src/timer/Timer.cpp Timer.hpp
	g++ -c -pthread -o objects/$@ $<

ObservableTimer.o: src/timer/ObservableTimer.cpp ObservableTimer.hpp
	g++ -c -o objects/$@ $<

AudioModule.hpp: headers/audio/AudioModule.hpp

IAudioModule.hpp: headers/audio/IAudioModule.hpp

ConfigManager.hpp: headers/configManager/ConfigManager.hpp

IConfigManager.hpp: headers/configManager/IConfigManager.hpp

Controller.hpp: headers/controller/Controller.hpp

Cycle.hpp: headers/cycle/Cycle.hpp

CycleState.hpp: headers/cycle/CycleState.hpp

ICycle.hpp: headers/cycle/ICycle.hpp

ICycleState.hpp: headers/cycle/ICycleState.hpp

ObservableCycle.hpp: headers/cycle/ObservableCycle.hpp

CycleCounter.hpp: headers/cyclecounter/CycleCounter.hpp

ICounter.hpp: headers/cyclecounter/ICounter.hpp

ICycleGetter.hpp: headers/cyclecounter/ICycleGetter.hpp

ICycleSetter.hpp: headers/cyclecounter/ICycleSetter.hpp

SettingsData.hpp: headers/data/SettingsData.hpp

IConfigManagerFacade.hpp: headers/facade/IConfigManagerFacade.hpp

IFacade.hpp: headers/facade/IFacade.hpp

IMainWindowFacade.hpp: headers/facade/IMainWindowFacade.hpp

ISettingsWindowFacade.hpp: headers/facade/ISettingsWindowFacade.hpp

GUI.hpp: headers/gui/GUI.hpp

AbstractWindow.hpp: headers/gui/window/AbstractWindow.hpp

MainWindow.hpp: headers/gui/window/MainWindow.hpp

SettingsWindow.hpp: headers/gui/window/SettingsWindow.hpp

AppModel.hpp: headers/model/AppModel.hpp

IConfigGetter.hpp: headers/model/IConfigGetter.hpp

IModel.hpp: headers/model/IModel.hpp

IWindowUpdater.hpp: headers/model/IWindowUpdater.hpp

Notification.hpp: headers/observers/Notification.hpp

Observable.hpp: headers/observers/Observable.hpp

Observer.hpp: headers/observers/Observer.hpp

ITimer.hpp: headers/timer/ITimer.hpp

ObservableTimer.hpp: headers/timer/ObservableTimer.hpp

Timer.hpp: headers/timer/Timer.hpp

clear:
	if [ -d objects ]; then rm -r objects; fi