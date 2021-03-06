# Huffman Custom Compression System

This repository is about a first-application-project, inspired by a class project of EFREI PARIS during the second year, and its [project guideline](https://docs.google.com/document/d/1-OwioEHwlS8xMncAjhKpWuEQuIQI_XdPzkiuomAsaJA/edit).

This project has as the main goal to be able to compress any files by using huffman's tree and C language.


## Table of contents
[Technologies](#Technologies)

[Content](#Content)

[Specifications](#Specifications)

[Project-Status](#Project-Status)

[Change-Log](#Change-Log)

[Sources](#Sources)


### Technologies
Language : C

Environement : Visual Studio Code


### Content


#### basic_proto.h
 - Create and free functions for each structures
 - Secure size function for the char SLL
 - Copy function for the char SLL


#### options_proto.h
 - read_option_file getting the option from an option file path
 - free function of the option struct
 - get_compress_path and get_free_path to combin the folder path and name of the compress or the tree file


#### error_proto.h
 - error function containing the error id, file weight, file id and specific error id


#### tree_proto.h
 - Balance function for the dictionary when all its node are sorted at the left


#### dictionnary_proto.h
 - Register function of a dictionary in a file
 - Register function of a tree in a file
 - Compute function of a dictionnary generated with a file


#### encrypt_proto.h
 - Encrypt function of a file, making a dictionnary and a compressed file
 - Encrypt function of a file, making a dictionnary and a binary sequence file


#### decrypt_proto.h
 - Decrypt function of a file depending on a dictionary file, making a decompress file


### Specifications
Be free, be happy (A day will come when you will not be able to)


### Project-Status
[Version](#Change-Log) - 0.2.0

Size - 237 Ko

Current Dev - [@lLouu](https://github.com/lLouu)


Done Tasks -

Basics | by [@lLouu](https://github.com/lLouu)

Debug of Basics | by [@lLouu](https://github.com/lLouu)

Structure Optimisation | by [@lLouu](https://github.com/lLouu)

Functions compatibility | by [@lLouu](https://github.com/lLouu)

Functions Debug | by [@lLouu](https://github.com/lLouu)

Basics Doccumentations | by [@lLouu](https://github.com/lLouu)

Errors and safety | by [@lLouu](https://github.com/lLouu)

Optimisation | by [@lLouu](https://github.com/lLouu)

Main cmd program | by [@lLouu](https://github.com/lLouu)



### Change-Log


#### V-0.2.0
 - definition of main function in main.c
 - definition of OPTION_PATH in .main.h


#### V-0.1.11
 - creation of option_stuct.h
 - creation of option structure in option_struct.h
 - creation of options.c, options.h, options_proto.h
 - creation of function in option.c
   - s_copy
   - read_option_file (log in options_proto.h)
   - free_option (log in options_proto.h)
   - get_compress_path (log in options_proto.h)
   - get_tree_path (log in options_proto.h)
 - creation of option.txt
 - definition of INCOMPLETE_OPTION in header.h and INCOMPLETE_OPTION_MESSAGE in error.h


#### V-0.1.10
 - deletion of all functions in tree.c
 - creation of functions in tree.c
   - lenght
   - mid_of
   - balance_BST_all_left (log in tree_proto.h)
 - usage of balance_BST_all_left instead of trees_balance_BST
 - Creation of function register_tree in dictionnary.c
 - usage of register_tree instead of register_dico
 - Creation of read_tree in decrypt.c
 - Usage of read_tree instead of read_dico
 - Optimisation of iscircular function in basic.c
 - Optimisation in decrypt.c of
   - getcode
   - dico_to_tree
   - translate
   - decrypt
 - Optimisation in dictionnary.c of
   - register_tree
   - tree_to_dico
   - compute_dico
 - Optimisation in encrypt.c of
   - compress
   - encrypt
   - put
   - encrypt_without_compression


#### V-0.1.9
 - unlog of unsecurized function size from basic_proto.h
 - creation of function in basic_functions.c
   - iscircular
   - secure_size (log in basic_proto.h)
 - replacement of size function usage by secure_size function in encrypt.c and decrypt.c
 - usage of error function in dicitonnary.c, encrypt.c and decrypt.c
 - explicitation of constants in each file
 - update of the change log in the README file


#### V-0.1.8
 - Creation of error.c ; error.h ; error_proto.h
 - definition of FILE_WEIGHT and FILE_ID two constant depending on the file used
 - definition of SLL_LOOP_ERROR, FILE_NOT_FOUND, CORRUPTION ERROR, INVALID_INPUT as common error ids
 - definition of <weight>_<id> in error.h as the ensemble of all file depending on their weight and id
 - definition of SLL_LOOP_MESSAGE, FILE_NOT_FOUND_MESSAGE, CORRUPTION_MESSAGE, and INVALID_INPUT_MESSAGE in error.h as information message for each corresponding errors.
 - definition of UNKNOWN_FILE and UNKNOWN_ERROR in error.h as return for an undeclared file or error.
 - creation of functions in error.c :
   - location
   - info
   - error (log in error_proto.h)


#### V-0.1.7
 - Documentation of logged functions in basic_proto.h
    - create_occ
    - create_tree
    - create_list
    - create_char
    - create_dico
    - size
    - copy
    - free_occ
    - free_tree
    - free_list
    - free_char
    - free_dico
 - in tree_proto.h
    - trees_balance_BST
 - in dictionary_proto.h
    - register_dico
    - compute_dico
 - in encrypt_proto.h
    - encrypt
    - encrypt_without_compression
 - in decrypt_proto.h
    - decrypt
 - Documentation of the structures
    - occurence_tree
    - Huffman_tree
    - node_list
    - char_SLL
    - dico
 - Documentation of CODE_BASE
 - Documentation of the README.md file


#### V-0.1.6
 - Deletion of duplicata function in encrypt.c
 - Move of copy and size functions from dictionary.c and encrypt.c to basic.c
 - log of copy and size in basic_proto.h
 - Deletion of <sting.h>
 - Move of <math.h> from header.h to encrypt.h


#### V-0.1.5
 - Creation of decrypt.c ; decrypt.h ; decrypt_proto.h
 - Creation of functions in decrypt.c
    - getcode
    - read_dico
    - dico_to_tree
    - translate
    - decrypt (log in decrypt_proto.h)
 - Creation of the CODE_BASE constant
 - Debug file decrypt-tests.c


#### V-0.1.4
 - line modification in dictionary.c (debug balance of dictionary)
 - Add a free_char in encrypt.c
 - Create functions in encrypt.c
    - put
    - encrypt_without_compression (log in encrypt_proto.h)


#### V-0.1.3
 - Add of <math.h>
 - Creation of encrypt.c ; encrypt.h ; encrypt_proto.h
 - Creation of functions in encrypt.c
    - duplicata
    - get_code
    - char_add
    - size
    - compress
    - encrypt (log in encrypt_proto.h)
 - Debug file encrypt-tests.c


#### V-0.1.2
 - Creation of dicitonary.c ; dicitonary.h ; dicitonary_proto.h
 - Creation of functions in dicitonary.c
    - add_to_occ
    - read_occ
    - occ_to_node
    - compute_tree
    - occ_to_tree
    - display
    - copy
    - merge
    - tree_to_dico
    - register_dico (log in dicitonary_proto.h)
    - compute_dico (log in dicitonary_proto.h)
 - Creation of tree.c ; tree.h ; tree_proto.h
 - Creation of functions in tree.c
    - depth
    - bf
    - right_rotation
    - left_rotation
    - balance
    - trees_balance_BST (log in tree_proto.h)
 - Creation of .file.h
 - Debug file dico-tests.c


#### V-0.1.1
 - Add structure to struct.h
    - occurence_tree
    - Huffman_tree
    - node_list
    - char_SLL
    - dico
 - Create basic_functions.c ; basic.h ; basic_proto.h
 - Create functions in basic.c
    - create_occ
    - create_tree
    - create_list
    - create_char
    - create_dico
    - free_occ
    - free_tree
    - free_list
    - free_char
    - free_dico


#### V-0.1.0
 - Move of all V-0.0.* to 'old'
 - Recreate
    - main.c ; main.h
    - header.h
    - struct.h


#### V-0.0.7
 - New functions in question.c
    - recover_tree
    - decrypt
 - Debug file Part-2-5.c


#### V-0.0.6
 - Name modification of create_dico function to register_dico function
 - new structures in struct.h
    - char_SLL
    - dico
 - new functions in question.c
    - create_char()
    - create_dico()
    - read_dico
    - put
    - encrypt
    - free_char
    - free_dico
    - compact_bin_file
 - Debug file Part 2-4.c


#### V-0.0.5
 - Add of <string.h>
 - Creation of create_dico function in question.c
 - Debug file part-2-3.c


#### V-0.0.4
 - Creation of new structures in struct.h
    - Huffman_tree
    - node_list
 - Deletion of sort_occ function in question.c
 - Creation of new functions
    - sort_node
    - create_tree
    - create_list
    - occ_to_node
    - sort_node
    - compute_tree
    - occ_to_tree
    - free_tree
    - display
 - Modification of Debug file Part-2-1.c
 - Debug file Part-2-2.c


#### V-0.0.3
 - Creation of new structures in struct.h
    - occurence_list
 - Creation of new functions in question.c
    - new_occ
    - add_to_occ
    - read_occ
    - sort_occ
    - free_occ
 - Debug file Part-2-1.c


#### V-0.0.2
 - Creation of new functions in question.c
    - translate_to_bin
    - count
 - Debug file Part-1.c


#### V-0.0.1
 - Creation of the files
    - .gitatributes
    - README.md
    - .gitignore
    - tuturu.txt
    - tree.txt
    - other_target.txt
    - file.h
    - header.h
    - struct.h
    - main.c ; .main.h
    - question.c ; question_prototype.h ; question.h


### Sources


[project guideline](https://docs.google.com/document/d/1-OwioEHwlS8xMncAjhKpWuEQuIQI_XdPzkiuomAsaJA/edit)

[huffman tree](https://en.wikipedia.org/wiki/Huffman_coding)
