CXX=g++
CXXFLAGS?=-O2

SRC=sense_menu.cpp
LINKS=-lncurses -lSenseHat -lRTIMULib

progname?=sense_menu

$(progname) :
	$(CXX) -o $@ $(SRC) $(LINKS)