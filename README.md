# MULTI-DAQ: Muon Life TIme Data AcQuisition program 
Data Acquisition program for the Muon Lifetime measurement developed by Jaime Díez González-Pardo during summer external practices in the _Instituto de Fisica de Cantabria (IFCA)_ with the collaboration of Pablo Martínez Ruiz del Árbol as supervisor.

![alt text](./docs/Screenshots/Main.png "Figure 1")

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

MULTI-DAQ is a data acquisition program for the experiment (Measurement of the muon lifetime) for the use of the TeachSpin [Muon Physics](http://www.teachspin.com/muon-physics.html) device. In this experiment, the life time of the muon is determined from the time of the muons decays inside the detector, using atmospheric muons as a source.

<img align="right" width="350" height="200" src="./docs/Screenshots/Scheme.png">

The program read, from a serial port connected to the electric readout box of the experiment, the signal of the detector with the information of the decay's time by means of the number of 50MHz clocks completed between both signals in hexadecimal system. The program must translate the signal from hexadecimal to decimal and multiply by 20 in order to obtain the muon decay time in nanoseconds (nanoseconds instead microsecond in order to treat it as integer without decimals). A 20000ns signal corresponds a muon signal without decay but interesting signals are those <20000ns wich means that a decay has occured. These signals are plotted in the main histogram (muonDcyHist) where the number of events are represented as function of their muon decay time in bins of 1&mu;s. The muon without decay's signals are plotted in other histogram as the number of muons per minute in the last minutes.
