# MULTI-DAQ: Muon Life TIme Data AcQuisition program 
Data Acquisition program for the Muon Lifetime measurement developed by Jaime Díez González-Pardo during summer intership in the _Instituto de Fisica de Cantabria (IFCA)_ with the collaboration of Pablo Martínez Ruiz del Árbol as supervisor.

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
g++ -o MULTI-DAQ src/main.cpp src/Histograms.cpp src/Menu.cpp src/DataLy.cpp src/MuonReader.cpp -lcdk -lncurses -lpanel -pthread  -std=c++11 `root-config --cflags --libs`
```

or 

``` shell
make MULTI-DAQ 
```
	
3) Run

Sudo/Su permissions are necessary in order to open and read the serial port

``` shell
sudo ./MULTI-DAQ 
```

## Brief Introduction

MULTI-DAQ is a data acquisition program for the experiment (Measurement of the Muon Lifetime) for the use of the TeachSpin apparatus  [Muon Physics](http://www.teachspin.com/muon-physics.html). In this experiment the muoon lifetime is determined from the muons' decay time occures inside the detector, using as source atmospherics muons.

<img align="right" width="450" height="300" src="/docs/Screenshots/Scheme.png">

