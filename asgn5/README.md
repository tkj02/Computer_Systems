Assignment 5 - Huffman Coding

Purpose: The purpose of this assignment is to implement Huffman encoders and decoders. Encoders read a file and compress it while decoders return a file to its original form. Nodes, priority queues, and stacks create these encoders and decoders, and an I/O interface reads and writes files. Both of the two test harnesses, encode.c and decode.c, will be able to take on command line arguments h, i, o, and v for printing a help message, reading an input file, writing an output file, and displaying compressing statistics respectively. Both should run together to see how the file size changes.

Build and Run: To compile the main test harnesses encode.c and decode.c and create the executable files encode and decode, run `$ make` or `$ make all`. Next, run `$ ./encode` with any combination of the command line arguments h, i, o, and/or v, and then run `$ ./decode` with any of the same arguments. Arguments i and o can take on file names provided by the user. For example, `$ ./encode -i text.txt -o compressedtext.out` runs encode with an infile called text.txt and compresses it to become compressedtext.out.

Files:
- encode.c implements the encoder
- decode.c implements the decoder
- defines.h contains macros useful to the encoder and decoder
- header.h contains the Header struct
- node.c implements the node ADT
- node.h contains the node ADT interface
- pq.c implements the pq ADT
- pq.h contains the pq ADT interface
- code.c implements the code ADT
- code.h contains the code ADT interface
- io.c implements the io ADT
- io.h contains the io ADT interface
- stack.c implements the stack ADT
- stack.h contains the stack ADT interface
- huffman.c implements the Huffman ADT
- huffman.h contains the Huffman ADT interface
- Makefile contains information for compiling, formatting, and removing .o files and executables
- README.md describes program and Makefile
- DESIGN.pdf includes design/design process, pseudocode, and explanations

Command Line Arguments (for both encode and decode):
- h: prints help message describing what it is, what the purpose is, and which the command-line options it accepts
- v: prints the statistics of the compression
    - for encode, it prints the uncompressed file size, compressed file size, and difference in size
    - for decode, it prints the compressed file size, decompressed file size, and difference in size
    - the uncompressed file size matches the decompressed file, as they are the same
- i (infile): specifies the input file to be read
    - will be uncompressed in encode and compressed in decode
- o (outfile): specifies the output file to be written
    - will be compressed in encode and decompressed in decode

Assistance:
- Watch both of Eugene’s recorded sections on YuJa (learned about the assignment overall, the process for encode.c and decode.c, and how to complete io.c functions)
- Watched part of Chrtisian’s recorded section on YuJa (got ideas on how to implement pq.c and node.c)
- Attended Brian’s section on October 29 and November 5 (learned enqueuing and dequeuing in more detail and got ideas on how to use byte and bit indices in code.c)
- Learned about reading and writing files from my dad who taught me ways that I could implement it in encode.c and decode.c (specifically using lseek(), O_RDONLY, O_RDWR, and O_CREAT)
- Referred to my assignment four files, especially for reading/writing files and completing stack.c as they were similar to what I needed to do here
- Consulted portions of chapters 6, 7, and 8 of the textbook The C Programming Language
- Consulted these websites/videos to understand concepts better
    - https://www.cs.usfca.edu/~galles/visualization/Heap.html
    - https://youtu.be/JsTptu56GM8
    - https://www.youtube.com/watch?v=co4_ahEDCho
    - https://www.tutorialspoint.com/cprogramming/c_file_io.htm
    - http://pages.cs.wisc.edu/~bart/537/valgrind.html

Citations:
- Assignment document: I followed the pseudocode provided on the assignment document for the following portions of my code:
    - build_tree (page 14)
    - build_codes (page 14)
    - dump_tree (page 15)


There are no known bugs/errors according to scan-build.
