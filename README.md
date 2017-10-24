# OpenQCD to QDP

## Running

```
openqcd-to-qdp [input_config] [output_config]
 - [input_config]  the openqcd configuration file created by the OpenQCD program
 - [output_config] name of the output file stored in the SciDAC (.lime) format
```

Converts a configuration created by the
[openQCD](http://luscher.web.cern.ch/luscher/openQCD/) program to a SciDAC
configuration (also known as [lime](https://github.com/usqcd-software/c-lime)).

The program only runs in serial, and running it in parallel will cause the
program to abort.

## Building

Simply type `make` to create the executable, which will be created in
`bin/openqcd-to-qdp`. The program requires a compiled version of
[qdpxx](https://github.com/usqcd-software/qdpxx) as well as an implementation of
MPI and the source files of openQCD.

The following environment variables will help the compilation:

 - `CXX`: the C++ compiler
 - `CC`: the C compiler
 - `QDP_DIR`: location where QDP is compiled
 - `OPENQCD_DIR`: location of OpenQCD source files
 - `MPI_DIR`: location of MPI header files
