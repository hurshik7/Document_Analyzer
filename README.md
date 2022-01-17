## Document_Analyzer

* [General info](#general-info)
* [Technologies](#technologies)
* [Contents](#content)

## General Info
Document Analyzer project is a personal project and a document analyzer implemented with C. This was created as an online software academy project. 

If you want to analyze the text in a file more closely, we need a more complex structure than an array of characters. Think of it as analyzing a multi-paragraph document, such as a report. We will want to know information such as the number of words, sentences, and paragraphs in the document. For this, I think it would be good to tokenize each word and store it in a nested structure like Tree.

A paragraph is formed by several sentences, and a document is formed by combining several paragraphs. It can be expressed using C pointers as follows:
* a word: char*
* a sentence: char**
* a paragraph: char***
* a document: char****

So, Document Analyzer is to read a document and store each word in it in the structure.

## Technologies
Technologies used for this project:
* C89
* clang (I used clang to test all of functions)
* Vim
	
## Content
Content of the project folder:

```
 Top level of project folder: 
├── .gitignore                      # Git ignore file
├── README.md                       # README file
├── document_analyzer.c             # Source file
├── document_analyzer.h             # Header file
└── main.c                          # main.c file for testing

It has the following subfolders and files:
├── .git                            # Folder for git repo
├── test_input                      # Folder for input files
    └── input.txt                   # input document
└── test_output                     # Folder for output files
    ├── expected_output.txt         # expected output file 
    └── output.txt                  # output file
```

## Resources
- POCU Academy COMP2200 C unmanaged programming course (https://pocu.academy/)

## Contact
* Shik Hur - hurshik7@gmail.com
