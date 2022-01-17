#include "document_analyzer.h"

static size_t s_total_word_count = 0;
static size_t s_total_sentence_count = 0;
static size_t s_total_paragraph_count = 0;
static char**** s_document_p = NULL;

int load_document(const char* document)
{
    char* buffer_malloc;
    int document_size = 0;
    size_t temp_sentence_count = 0;
    size_t temp_word_count = 0;
    size_t temp_paragraph_count = 0;
    char** temp_paragraph_arr;
    char** temp_sentence_arr;
    char** temp_word_arr; 
    size_t i;
    size_t j;
    size_t k;
    size_t word_len;

    FILE* fp = fopen(document, "r");
    if (fp == NULL) {
        perror("File open error");
        return FALSE;
    }

    dispose();
    
    fseek(fp, 0, SEEK_END);
    document_size = ftell(fp);
    buffer_malloc = malloc(document_size + 1);
    memset(buffer_malloc, 0, document_size + 1);
    fseek(fp, 0, SEEK_SET); 
    fread(buffer_malloc, document_size, 1, fp);
    if (document_size == 0) {
        goto free_and_exit;
    }    

    /* paragraph */
    temp_paragraph_arr = tokenize_malloc(buffer_malloc, "\n", &temp_paragraph_count);
    s_total_paragraph_count += temp_paragraph_count;
    s_document_p = malloc((temp_paragraph_count + 1) * sizeof(char***));
    s_document_p[temp_paragraph_count] = NULL;

    /* sentence */
    for (i = 0; i < temp_paragraph_count; ++i) {
        temp_sentence_arr = tokenize_malloc(temp_paragraph_arr[i], ".!?", &temp_sentence_count);
        s_total_sentence_count += temp_sentence_count;
        s_document_p[i] = malloc((temp_sentence_count + 1) * sizeof(char**));
        s_document_p[i][temp_sentence_count] = NULL;
        for (j = 0; j < temp_sentence_count; ++j) {
            temp_word_arr = tokenize_malloc(temp_sentence_arr[j], " ,", &temp_word_count);
            s_total_word_count += temp_word_count;
            s_document_p[i][j] = malloc((temp_word_count + 1) * sizeof(char*));
            s_document_p[i][j][temp_word_count] = NULL;
            for (k = 0; k < temp_word_count; ++k) {
                word_len = strlen(temp_word_arr[k]);
                s_document_p[i][j][k] = malloc((word_len + 1) * sizeof(char));
                strcpy(s_document_p[i][j][k], temp_word_arr[k]);
            }
            for (k = 0; k < temp_word_count; ++k) {
                free(temp_word_arr[k]);
                temp_word_arr[k] = NULL;
            }
            free(temp_word_arr);
            temp_word_arr = NULL;
        }
        for (j = 0; j < temp_sentence_count; ++j) {
            free(temp_sentence_arr[j]);
            temp_sentence_arr[j] = NULL;
        }
        free(temp_sentence_arr);
        temp_sentence_arr = NULL;
    }
    
    for (i = 0; i < temp_paragraph_count; ++i) {
        free(temp_paragraph_arr[i]);
        temp_paragraph_arr[i] = NULL;
    }
    free(temp_paragraph_arr);
    temp_paragraph_arr = NULL;

free_and_exit: 
    /* free memory */
    if (fclose(fp) == EOF) {
        perror("File close error");
        return FALSE;
    }
    free(buffer_malloc);
    buffer_malloc = NULL;
    return TRUE;
}

void dispose(void)
{
    size_t i;
    size_t j;
    size_t k;

    if (s_document_p == NULL) {
        return;
    }
    
    for (i = 0; s_document_p[i] != NULL; ++i) {
        for (j = 0; s_document_p[i][j] != NULL; ++j) {
            for (k = 0; s_document_p[i][j][k] != NULL; ++k) {
                free(s_document_p[i][j][k]);
                s_document_p[i][j][k] = NULL;
            }
            free(s_document_p[i][j]);
            s_document_p[i][j] = NULL;
        }
        free(s_document_p[i]);
        s_document_p[i] = NULL;
    }
    free(s_document_p);
    s_document_p = NULL;

    s_total_word_count = 0;
    s_total_sentence_count = 0;
    s_total_paragraph_count = 0;
}

size_t get_total_word_count(void)
{
    return s_total_word_count;
}

size_t get_total_sentence_count(void)
{
    return s_total_sentence_count;
}

size_t get_total_paragraph_count(void)
{
    return s_total_paragraph_count;
}

const char*** get_paragraph_or_null(const size_t paragraph_index)
{
    if (paragraph_index > s_total_paragraph_count - 1 || s_document_p == NULL) {
        return NULL;
    }
    return (const char***)s_document_p[paragraph_index];
}

size_t get_paragraph_word_count(const char*** paragraph)
{
    size_t ret = 0;
    size_t sentence_idx;
    size_t word_idx;

    if (paragraph == NULL) {
        goto exit;
    }

    for (sentence_idx = 0; paragraph[sentence_idx] != NULL; ++sentence_idx) {
        for (word_idx = 0; paragraph[sentence_idx][word_idx] != NULL; ++word_idx) {
            ret++;
        }
    }
exit:
    return ret;
}

size_t get_paragraph_sentence_count(const char*** paragraph)
{
    size_t ret = 0;
    size_t sentence_idx;
    
    if (paragraph == NULL) {
        goto exit;
    }
    
    for (sentence_idx = 0; paragraph[sentence_idx] != NULL; ++sentence_idx) {
        ret++;
    }

exit:
    return ret;
}

const char** get_sentence_or_null(const size_t paragraph_index, const size_t sentence_index)
{
    const char*** paragraph = NULL;
    size_t sentence_count = 0;    
    paragraph = get_paragraph_or_null(paragraph_index);
    if (paragraph == NULL) {
        return NULL;
    }

    sentence_count = get_paragraph_sentence_count(paragraph);
    if (sentence_index > sentence_count - 1) {
        return NULL;
    }
    
    return (const char**)s_document_p[paragraph_index][sentence_index];
}

size_t get_sentence_word_count(const char** sentence)
{
    size_t ret = 0;
    size_t word_idx;
    if (s_document_p == NULL) {
        goto exit;
    }    
    
    for (word_idx = 0; sentence[word_idx] != NULL; ++word_idx) {
        ret++;
    }

exit:
    return ret; 
}

int print_as_tree(const char* filename)
{
    FILE* fp;
    size_t paragraph_idx = 0;
    size_t sentence_idx = 0;
    size_t word_idx = 0;

    if (s_document_p == NULL || s_total_word_count == 0) {
        return FALSE;
    }

    fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("error opening file");
        return FALSE;
    }

    for (paragraph_idx = 0; paragraph_idx < s_total_paragraph_count; ++paragraph_idx) {
        if (paragraph_idx != 0) {
            fprintf(fp, "\n\n");
        }
        fprintf(fp, "Paragraph %u:", paragraph_idx);
        for (sentence_idx = 0; s_document_p[paragraph_idx][sentence_idx] != NULL; ++sentence_idx) {
            fprintf(fp, "\n    Sentence %u:", sentence_idx);
            for (word_idx = 0; s_document_p[paragraph_idx][sentence_idx][word_idx] != NULL; ++word_idx) {
                fprintf(fp, "\n        %s", s_document_p[paragraph_idx][sentence_idx][word_idx]);
            }
        }
    }
    
    if (fclose(fp) == EOF) {
        perror("error closing file");
        return FALSE;
    }
    
    return TRUE;
}

char** tokenize_malloc(const char* str, const char* delim, size_t* out_count)
{
    char* temp_str;
    char* token;
    size_t str_length = strlen(str);
    size_t word_count = 0;
    size_t ret_size = 5;
    size_t word_length = 0;
    char** ret;
    void* temp = NULL;
     
    temp_str = malloc((str_length + 1) * sizeof(char));
    strcpy(temp_str, str);
    
    ret = malloc(ret_size * sizeof(char*));

    token = strtok(temp_str, delim);
    if (token == NULL) {
        temp = realloc(ret, 1 * sizeof(char*));
        ret[0] = NULL;
        goto free_and_exit;
    }
   
    while (token != NULL) {
        word_count++;
        word_length = strlen(token);
        
        if (word_count == ret_size - 1) {
            ret_size += 5;
            temp = realloc(ret, ret_size * sizeof(char*));
            if (temp != NULL) {
                ret = temp;
            }
        }
        ret[word_count - 1] = malloc((word_length + 1) * sizeof(char));
        strcpy(ret[word_count - 1], token);
        
        token = strtok(NULL, delim);
    }

    ret[word_count] = NULL;  
    *out_count = word_count;
free_and_exit:
    free(temp_str);
    temp_str = NULL;
    return ret;    
}
