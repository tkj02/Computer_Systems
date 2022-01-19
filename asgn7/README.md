Assignment 7 - The Great Firewall of Santa Cruz

Purpose: The purpose of this assignment is to read in text and output a corresponding message, making use of bit vectors, nodes, binary search trees, hash tables, and bloom filters to do so. The necessary functions for these implementations are contained in bv.c, node.c, bst.c, ht.c, and bf.c respectively. Nodes are used in binary search trees, which are then used in hash tables, and bit vectors are used in bloom filters. The main test harness is contained in banhammer.c, which uses a hash table and a bloom filter to identify “badspeak” terms as well as “oldspeak” with their “newspeak” translations. User text is then compared to the contents of the bloom filter (and hash table if necessary) to determine which terms were used and which message should be printed. banhammer.c can take on four combinations of command line arguments (h, s, t, and f) as described below. 

Build and Run: To compile the main test harness banhammer.c and create the executable file banhammer, run `$ make` or `$ make all`. Next, run `$ ./banhammer` with any combination of the command line arguments h, s, t, and f. The last two options can take on values from the user to be the sizes of the hash table and bloom filter respectively.

Files:
- node.h specifies the interface for the node ADT
- node.c contains the implementation of the node ADT
- bv.h specifies the interface for the bit vector ADT
- bv.c contains the implementation of the bit vector ADT
- bst.h specifies the interface for the binary search tree ADT
- bst.c contains the implementation of the binary search tree ADT
- ht.h specifies the interface for the hash table ADT
- ht.c contains the implementation of the hash table ADT
- bf.h specifies the interface for the bloom filter ADT
- bf.c contains the implementation of for the bloom filter ADT
- parser.h specifies the interface for the regex parsing module
- parser.c contains the implementation of the regex parsing module
- speck.h defines the interface for the hash function using SPECK cipher
- speck.c contains the implementation of the hash function using SPECK cipher
- banhammer.c contains the implementation of the main function and my own helper functions
- messages.h defines the mixspeak, badspeak, and goodspeak messages that are used in banhammer.c
- salts.h defines the primary, secondary, and tertiary salts to be used in bf.c and defines the salt used by the hash table in ht.c.
- badspeak.txt specifies the list of badspeak terms
- newspeak.txt specifies the list of oldspeak terms with their newspeak translations
- Makefile contains information for compiling, formatting, and removing object files and executables
- README.md describes program and Makefile

Command Line Arguments (for banhammer):
- -h : displays program synopsis and usage
- -s: enables statistics output (prints the average binary search tree size, average binary search tree height, average branch traversal, hash table load, and bloom filter load)
- -t: specifies size of hash table (default: 2^16)
- -f: specifies size of bloom filter (default: 2^20)

Assistance:
- Watched both of TA Eugene’s recorded sections on YuJa multiple times (learned about the assignment overall/what we are expected to do, how the parsing module works, what the bloom filter and hash table should do, got ideas on what the regex pattern should look like, what average branches traversed is, how to scan in the different character formats, how to approach the WRITEUP questions, and followed some of his pseudocode (described in more detail below))
- Attended TA Brian’s office hours (cleared up a question I had on salt array indices and setting up ht_create() and bf_create())
- Referred to class discussions on ED (especially on what ht_delete() should do, which regex words are valid, and how to print the correct statistics)
- Referred to lecture slides #18 and #26 on binary search trees and regular expression respectively (described in more detail below)
- Referred to this website https://user-web.icecube.wisc.edu/~dglo/c_class/stdio.html like I did in the previous assignment to read about fgets()
- Read about command line operations, especially on how to end reading text with control+D at https://tldp.org/LDP/GNU-Linux-Tools-Summary/html/x1877.htm
- Referred to my node implementation in as assignment five (specifically node.c) for completing this node.c
- Referred to my bit vector implementation in assignment five (specifically code.c) for completing bv.c
- Referred to my assignment five and six files, especially for reading/writing files and setting default files

Citations:
- Assignment Document: I followed the pseudocode provided on the assignment document for the following portions of my code:
    - Bloom filter structure (page 3)
    - Bit vector structure (page 5)
    - Hash table structure (page 7)
    - Node structure (page 8)
    - node_print() format (page 8)
    - Example parsing module (page 11)
- Lecture Slides #18 - Trees and BST: I followed the example code provided on these slides for the following portions of my code:
    - Inorder traversal printing (pages 22-34)
    - Finding maximum node (page 53)
    - Finding tree height (page 55)
    - Finding a node with specific key (page 57)
    - Inserting a node with specific key (page 62)
    - Postorder traversal deletion (page 76-85)
- Lecture Slides #26 - Regex: I got ideas from:
    - Basic regex syntax (pages 3-5)
- Eugene’s Lab Section 11/30/21: I followed his pseudocode for the following portions of my code:
    - bf_insert()
    - ht_insert()
    - ht_find()

There are no known bugs/errors according to scan-build. 

