ROOTCFLAGS    = $(shell root-config --cflags)                                                                                                                     
ROOTLIBS      = $(shell root-config --libs)

CXX           = g++                                                                                                                     
CXXFLAGS  = -lcdk -lncurses -lpanel -pthread  -std=c++11 `root-config --cflags --libs`

MuLTim-Daq:
	$(CXX) $(ROOTCFLAGS) $(ROOTLIBS) -o MULTI-DAQ main.cpp Histograms.cpp Menu.cpp DataLy.cpp MuonReader.cpp $(CXXFLAGS)
