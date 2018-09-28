ROOTCFLAGS    = $(shell root-config --cflags)                                                                                                                     
ROOTLIBS      = $(shell root-config --libs)

CXX           = g++                                                                                                                     
CXXFLAGS  = -lcdk -lncurses -lpanel -pthread  -std=c++11 `root-config --cflags --libs`

MULTI-DAQ:
	$(CXX) $(ROOTCFLAGS) $(ROOTLIBS) -o MULTI-DAQ src/main.cpp src/Histograms.cpp src/Menu.cpp src/DataLy.cpp src/MuonReader.cpp $(CXXFLAGS)
