# OTF2 to CTF converter

## Informations
This project allows to convert OTF2 traces into CTF traces using the OTF2 C API and barectf.  
Several threads are used to optimize the conversion speed. Several locations are assigned to each thread and local event readersare used to read the OTF2 traces concurrently.  
For each OTF2 location, one CTF stream is created.  
A CTF stream containing global definitions (in the form of CTF events at the OTF2 global offset timestamp) is also created.

## Usage
To use the converter you have to :  
- set the following environment variable OTF2_CONVERTER : ```export OTF2_CONVERTER=<path to the project directory>```  
- use the following command : ```./otf2_converter [options] <OTF2 trace to convert>```  

Example : ```./otf2_converter --njobs=4 --output=CTF_trace traces.otf2```

## Options

- -n, --njobs Number of threads that will be used. If this number is higher than the number of locations then the effective number of threads will be the number of locations. If it is higher than the number of cores then it will be the number of cores. By default the value is -1 and the number of available cores will be used.
- -o, --output Output directory that will contains the CTF trace. By default the name will be converted_otf2_\<pid\>_\<timeofday\>


## Installation
To build the converter you will need [OTF2](http://perftools.pages.jsc.fz-juelich.de/cicd/otf2/tags/otf2-2.3/otf2-2.3.tar.gz).
You will need to set the path to the OTF2 directory : ```export OTF2_PATH=<path to OTF2 directory>''' . By default the path is ```/opt/otf2```  
Then go to the directory and run build.sh : ```./build.sh```  
It will create an executable file OTF2_converter that will be used for the conversion.
 

