# MULTIM: Muon Life TIMe data adquisition program
Data Acquisition program for the Muon Lifetime 

![alt text](/docs/Screenshots/Main.png "Figure 1")

## Requisites

>* [cdk](https://invisible-island.net/cdk/#download)
>* [Ncurses](https://askubuntu.com/questions/270381/how-do-i-install-ncurses-header-files)
>* [ROOT](https://root.cern.ch/building-root)

## Compile

``` shell
g++ main.cpp Histograms.cpp Menu.cpp DataLy.cpp MuonReader.cpp -lcdk -lncurses -lpanel -pthread  -std=c++11 `root-config --cflags --libs`
```
or 

``` shell
make MuLTim-Daq
```
