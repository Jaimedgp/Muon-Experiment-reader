# Muon-Experiment-reader
Data Acquisition program for the Muon Lifetime 

## Compulation

``` shell
g++ main.cpp Histograms.cpp Menu.cpp DataLy.cpp MuonReader.cpp -lcdk -lncurses -lpanel -pthread  -std=c++11 `root-config --cflags --libs`
```
