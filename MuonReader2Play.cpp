/**
 * Play re-writting the MounReader script of Pablo Martinez Ruiz del Arbol
 *
 * @author Jaimedgp
 */

#include <iostream>
#include <stdio.h>
#include <fstream> // write and read package
#include <string.h> // for std::string variables
#include <getopt.h> // for getOptions function
#include <stdlib.h> // to use atoi (convert char >> int)

//-------------------------------------------//
//           DECLARE FUNCTIONS               //
//-------------------------------------------//

bool getOptions(int, char **, std::string &, std::string &, std::string &, int &, std::string &, int &);

//------------------------------------------//
//------------------------------------------//


int main (int argc, char **argv) {

    std::string nameOfDevice;
    std::string nameOfOutputFile;
    std::string nameOfAllOutputFile;
    std::string nameOfLayerConfig;

}

//---------------------------------------------------------------------//
// This method will put the command line input in the variables        //
//     set the nameOfDevice    , nameOfLayerConfig                     //
//             nameOfOutputFile, nameOfAlloutputFile  GNU values       //
//  the arguments are the pointers of these variables &nameOfDevice... //
//---------------------------------------------------------------------//
bool getOptions(int argc, char **argv, std::string &nameOfDevice, std::string &nameOfOutputFile, std::string &nameOfAllOutputFile, int &numberOfEvents, std::string &nameOfLayerConfig, int &seconds) {

    int option_iterator; // return of getopt_long, -1 if no more options to handle
    int option_counter = 0;
    bool moreoptions = true; // to run or break the while loop

    while (moreoptions) {

        /**
         * describes a single long option name for the sake of getopt_long
         */
        static struct option long_options[] = { // these options set a flag
            //{char, int, int *, int}
            {"device",     required_argument, 0, 'd'},
            {"output",     required_argument, 0, 'o'},
            {"outputall",  required_argument, 0, 'a'},
            {"conf",       required_argument, 0, 'l'},
            {"number",     required_argument, 0, 'n'},
            {"time",       required_argument, 0, 't'},
            {0,0,0,0} // required for (getopt) long option
        };

        int option_index = 0; // start from element 0

        option_iterator = getopt_long(argc, argv, "d:", long_options, &option_index);

        if (option_iterator == -1) {
            moreoptions = false; // break the loop when no more options to handle
        } else {
            option_counter++;

            switch (option_iterator) {
                case 0:
                    if (long_options[option_index].flag != 0) break;
                    if (optarg) break;
                case 'd':
                    nameOfDevice = (std::string) optarg; // get the optarg value obtained
                    break;
                case 'o':
                    nameOfOutputFile = (std::string) optarg;
                case 'a':
                    nameOfAllOutputFile = (std::string) optarg; // get the optarg value obtained
                    break;
                case 'l':
                    nameOfLayerConfig = (std::string) optarg; // get the optarg value obtained
                    break;
                case 'n':
                    numberOfEvents = (int) atoi(optarg); // atoi to convert char >> int 
                    break;
                case 't':
                    seconds = (int) atoi(optarg); // atoi to convert char >> int 
                    break;
                case '?':
                    return false; // quit the function
                    break;
                default:
                    return false; // quit the function
            }
        }
    }

    if (option_counter == 0) {
        return false; // no option found
    }

    return true;
}

