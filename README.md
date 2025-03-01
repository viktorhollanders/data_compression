# Data commpressor T-403-FORC

## Author

Viktor Hollanders <viktorhollanders@hey.com>

## About

This is a project written in c++ 11 standard for the course T-403-FORC at Reykjavik university. It compleets the A part of the assignment.

## Building

The project contains a make file for building, cleaning and debbuging

To build the project run:
```sh
  make
```

To encode a file run:
```sh
  ./encoder -e name_of_input_file.txt name_of_encoded_file.txt
```

To decode a file run:
```sh
  ./encoder -d name_of_encoded_file.txt name_of_output_file.txt
```

The encode will then store the output in the output folder in the project.

## Make file comands
The project contains a make file, here are the commands and their explenation.

To build the project run:
```sh
  make
```
Run make debug to make make a debug version
```sh
  make debug
```

Run make clean to macleanke the project
```sh
  make clean
```