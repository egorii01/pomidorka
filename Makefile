GTK_OPTION = `pkg-config --cflags --libs gtkmm-3.0`
AL_OPTION = -lalut
CFLAGS = -pthread

all:
	g++ $(CFLAGS) -o pomidorka main.cpp \
	src/configManager/ConfigManager.cpp src/cycle/Cycle.cpp src/cycle/ObservableCycle.cpp \
	src/cyclecounter/CycleCounter.cpp src/gui/GUI.cpp src/gui/window/AbstractWindow.cpp \
	src/gui/window/MainWindow.cpp src/gui/window/SettingsWindow.cpp src/model/AppModel.cpp \
	src/timer/ObservableTimer.cpp src/timer/Timer.cpp src/audio/AudioModule.cpp $(AL_OPTION) $(GTK_OPTION)