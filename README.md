# OTF2 to CTF converter

## Informations
This project allows to convert OTF2 traces into CTF traces using the OTF2 C API and barectf.  
Several threads are used to optimize the conversion speed. Several locations are assigned to each thread and local event readersare used to read the OTF2 traces concurrently.  
For each OTF2 location, one CTF stream is created.  
A CTF stream containing global definitions (in the form of CTF events at the OTF2 global offset timestamp) is also created.

## Usage
To use the converter you have to :  
- set the following environment variable OTF2_CONVERTER : ```export OTF2_CONVERTER=<path to the project directory>```  
- use the following command : ```./otf2_converter --njobs <expected number of threads> --output <output directory> <OTF2 trace to convert>```  

## Installation
 

