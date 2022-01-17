#include <assert.h>
#include <string.h>
#include "document_analyzer.h"

int main(void)
{
    const char** sentence = NULL;
    const char*** paragraph = NULL;
    size_t i = 0U;
    size_t j = 0U;

    assert(load_document("doesntexist.txt") == FALSE);
    assert(load_document("./test_input/input.txt") == TRUE);


    assert(get_total_word_count() == 58U);
    assert(get_total_sentence_count() == 9U);
    assert(get_total_paragraph_count() == 3U);

    assert(get_paragraph_or_null(3) == NULL);
    paragraph = get_paragraph_or_null(1);
    assert(paragraph != NULL);
    assert(get_paragraph_word_count(paragraph) == 14);
    assert(get_paragraph_sentence_count(paragraph) == 2);

    assert(strcmp(paragraph[i][j++], "This") == 0);
    assert(strcmp(paragraph[i][j++], "is") == 0);
    assert(strcmp(paragraph[i][j++], "the") == 0);
    assert(strcmp(paragraph[i][j++], "second") == 0);
    assert(strcmp(paragraph[i++][j++], "paragraph") == 0);

    j = 0U;

    assert(strcmp(paragraph[i][j++], "I") == 0);
    assert(strcmp(paragraph[i][j++], "wonder") == 0);
    assert(strcmp(paragraph[i][j++], "how") == 0);
    assert(strcmp(paragraph[i][j++], "many") == 0);
    assert(strcmp(paragraph[i][j++], "sentences") == 0);
    assert(strcmp(paragraph[i][j++], "you") == 0);
    assert(strcmp(paragraph[i][j++], "will") == 0);
    assert(strcmp(paragraph[i][j++], "see") == 0);
    assert(strcmp(paragraph[i][j++], "here") == 0);

    assert(get_sentence_or_null(0, 10) == NULL);

    sentence = get_sentence_or_null(0, 2);
    assert(sentence != NULL);
    assert(get_sentence_word_count(sentence) == 4);

    i = 0U;

    assert(strcmp(sentence[i++], "Is") == 0);
    assert(strcmp(sentence[i++], "this") == 0);
    assert(strcmp(sentence[i++], "too") == 0);
    assert(strcmp(sentence[i++], "easy") == 0);

    assert(print_as_tree("./test_output/output.txt") == TRUE);
    dispose();
    printf("TEST COMPLETE!!\n");
    return 0;
}
