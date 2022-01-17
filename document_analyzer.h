#ifndef DOCUMENT_ANALYZER_H
#define DOCUMENT_ANALYZER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE (1)
#define FALSE (0)

int load_document(const char* document);

void dispose(void);

size_t get_total_word_count(void);

size_t get_total_sentence_count(void);

size_t get_total_paragraph_count(void);

const char*** get_paragraph_or_null(const size_t paragraph_index);

size_t get_paragraph_word_count(const char*** paragraph);

size_t get_paragraph_sentence_count(const char*** paragraph);

const char** get_sentence_or_null(const size_t paragraph_index, const size_t sentence_index);

size_t get_sentence_word_count(const char** sentence);

int print_as_tree(const char* filename);

/*added by shik*/
char** tokenize_malloc(const char* str, const char* delim, size_t* out_count);
#endif /* DOCUMENT_ANALYZER_H */
