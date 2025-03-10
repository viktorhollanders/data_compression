# Data commpressor T-403-FORC

## Author

Viktor Hollanders <viktorhollanders@hey.com>

## About

This is a compression tool. It can compress and decompress files, although it can only do so with text files and is intended to demonstrate how Huffman encoding works. It is part A of an assignment for the course T-403-FORC at Reykjavik University. The project uses the C++11 standard. When building the project, I followed this article: https://yuriygeorgiev.com/2024/02/03/lossless-compression-huffman-coding-rle/, and I highly recommend it if you are interested in learning more about how the Huffman algorithm works.

## Building

To build the project, run:

```sh
  make
```

To create a debug version, run:

```sh
  make debug
```

To clean the project, run:

```sh
  make clean
```

## Runing the project

The project can be run in three modes.
Demo Mode: Simply shows that the tool works.

```sh
  ./encoder
```

Encode Mode: Encodes a file. This mode takes three arguments: the mode -e, the file to encode, and the encoded file to write to.

```sh
  ./encoder -e name_of_input_file.txt name_of_encoded_file.txt
```

Decode Mode: Decodes a file. This mode takes three arguments: the mode -d, the encoded file, and the output file.

```sh
  ./encoder -d name_of_encoded_file.txt name_of_output_file.txt
```

The `output` directory in the project can be used to store the files if needed.



