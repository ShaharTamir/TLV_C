#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_CAPITAL_VAL 'A'
#define MAX_CAPITAL_VAL 'Z'
#define MIN_REG_VAL 'a'
#define MAX_REG_VAL 'z'

/* API functions */
int Similar (char *st, char *word, int n);
void Find_Similar(char *st, char * word, int n);

char* Get_Next_Word(char* text, int *starting_index, int text_length);
int isLetter(char l);

int main()
{
    char* word = "table\0";
    char* st = "This is a table that is black. We are looking for a person able to find taable,\n" \
                "tables and takble. The program will not print taables\0";

    printf("%d \n", Similar(st, word, 1));
    Find_Similar(st, word, 1);

    return 0;
}

int Similar(char *st, char *word, int n)
{
    char *st_trace = NULL;
    int st_length = 0;
    int word_length = 0;
    int extra_letters_counter = 0;
    int i = 0;
    int j = 0;

    while('\0' != st[st_length])
        ++st_length;

    while('\0' != word[word_length])
        ++word_length;

    if(st_length < word_length || st_length > word_length + n)
        return 0;
    
    st_trace = (char *)malloc(st_length);
    
    if(NULL == st_trace)
    {
        printf("memory allocation failure. exit.");
        return 0;
    }

    for(i = 0; i < st_length; ++i)
        st_trace[i] = 0;

    extra_letters_counter = st_length;
    for(i = 0; i < word_length; ++ i)
    {
        for(j = 0; j < st_length; ++j)
        {
            if(word[i] == st[j] && 0 == st_trace[j])
            {
                --extra_letters_counter;
                st_trace[j] = 1;
                break;
            }
        }

        if(j == st_length)
        {
            free(st_trace);
            return 0;
        }
    }

    if(extra_letters_counter > n)
    {
        free(st_trace);
        return 0;
    }

    return 1;
}

void Find_Similar(char *st, char *word, int n)
{
    /* assuming word is actually a word with no spaces or other ascii chars */
    char* next_word = NULL;
    int next_word_length = 0;
    int st_index = 0;
    int st_length = 0;

    while('\0' != st[st_index])
    {
        ++st_index;
    }

    st_length = st_index;
    st_index = 0;

    next_word = Get_Next_Word(st, &st_index, st_length);

    while(NULL != next_word) 
    {
        if(Similar(next_word, word, n))
        {
            printf("%s\n", next_word);
        }

        free(next_word);
        next_word = NULL;

        next_word = Get_Next_Word(st, &st_index, st_length);
    }
}

char* Get_Next_Word(char *text, int *starting_index, int text_length)
{
    char *next_word = NULL;
    int next_word_length = 1;

    if(*starting_index < 0)
        return NULL;

    while(*starting_index < text_length && !isLetter(text[*starting_index]))
    {
        ++*starting_index;
    }

    if(*starting_index == text_length)
        return NULL;
    
    
    while(*starting_index + next_word_length < text_length && isLetter(text[*starting_index + next_word_length]))
    {
        ++next_word_length;
    }

    next_word = (char*) malloc(next_word_length + 1);

    if(next_word)
    {
        int i = 0;

        for(i = 0; i < next_word_length; ++i)
        {
            next_word[i] = text[*starting_index + i];
        }

        next_word[next_word_length] = '\0';
        *starting_index += next_word_length;
    }

    return next_word;
}

int isLetter(char l)
{
    return (l >= MIN_CAPITAL_VAL && l <= MAX_CAPITAL_VAL) || (l >= MIN_REG_VAL && l <= MAX_REG_VAL);
}