# Muon-Experiment-reader
Data Acquisition program for the Muon Lifetime 

## Requisites

>* [cdk] (https://invisible-island.net/cdk/#download)
>* [Ncurses] (https://askubuntu.com/questions/270381/how-do-i-install-ncurses-header-files)
>* [ROOT] (https://root.cern.ch/building-root)

## Compile

``` shell
g++ main.cpp Histograms.cpp Menu.cpp DataLy.cpp MuonReader.cpp -lcdk -lncurses -lpanel -pthread  -std=c++11 `root-config --cflags --libs`
```
