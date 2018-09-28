# MULTI-DAQ: Muon Life TIme Data AdQuisition program 
Data Acquisition program for the Muon Lifetime measurement

![alt text](/docs/Screenshots/Main.png "Figure 1")

## Requisites

>* [cdk](https://invisible-island.net/cdk/#download)
>* [Ncurses](https://askubuntu.com/questions/270381/how-do-i-install-ncurses-header-files)
>* [ROOT](https://root.cern.ch/building-root)

## Installation

Once you have installed all the software listed under "Requisites" you can now begin the installation process:

1) Get the source

``` shell
git clone https://github.com/Jaimedgp/Muon-Experiment-reader
``` 
2) Compile

``` shell
g++ -o MULTI-DAQ main.cpp Histograms.cpp Menu.cpp DataLy.cpp MuonReader.cpp -lcdk -lncurses -lpanel -pthread  -std=c++11 `root-config --cflags --libs`
```

or 

``` shell
make MULTI-DAQ 
```
	
3) Run
	
``` shell
sudo ./MULTI-DAQ 
```

## Brief Introduction

