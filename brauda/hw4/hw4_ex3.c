#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */

#define MIN_CAPITAL_VAL 'A'
#define MAX_CAPITAL_VAL 'Z'
#define MIN_REG_VAL 'a'
#define MAX_REG_VAL 'z'

/* API functions */
int Similar (char *st, char *word, int n);
void Find_Similar(char *st, char * word, int n);

/* Service functions */
char* Get_Next_Word(char* text, int *starting_index, int text_length);
int Get_String_Length(char *st);
int Is_Letter(char l);
void Copy_Sub_String(char *dest, char *src, int start, int end);

int main()
{
    char* word = "table\0";
    char* ok = "tables\0";
    char* longer = "tabless\0";
    char* shorter = "tabl\0";
    char* st = "This is a table that is black. We are looking for a person able to find taable,\n" \
                "tables and takble. The program will not print taables\0";

    printf("st - %d \n", Similar(st, word, 1));
    printf("ok - %d \n", Similar(ok, word, 1));
    printf("longer - %d \n", Similar(longer, word, 1));
    printf("sorter - %d \n", Similar(shorter, word, 1));
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

    st_length = Get_String_Length(st);
    word_length = Get_String_Length(word);

    if(0 == st_length || 0 == word_length || st_length < word_length || st_length > word_length + n)
        return 0;
    
    st_trace = (char *)malloc(st_length);
    
    if(NULL == st_trace)
    {
        printf("memory allocation failure. exit.");
        return 0;
    }

    for(i = 0; i < st_length; ++i) /* init trace */
        st_trace[i] = 0;

    extra_letters_counter = st_length;
    for(i = 0, j = 0; i < word_length; ++i, j = 0)
    {
        while(j < st_length && (word[i] != st[j] || st_trace[j]))
            ++j;

        if(j == st_length) /* letter from word doesn't exist in st */
        {
            free(st_trace);
            return 0;
        }
        else
        {
            --extra_letters_counter;
                st_trace[j] = 1;
        }
    }

    if(extra_letters_counter > n) /* st has more than n letters that differ from word */
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
    int st_index = 0;
    int st_length = 0;

    st_length = Get_String_Length(st);
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
    int next_word_length = 1; /* at least one letter */

    if(*starting_index < 0)
        return NULL;

    /* skip everything that is not a letter */
    while(*starting_index < text_length && !Is_Letter(text[*starting_index]))
        ++*starting_index;

    if(*starting_index == text_length)
        return NULL;
    
    /* get word length */
    while(*starting_index + next_word_length < text_length && Is_Letter(text[*starting_index + next_word_length]))
        ++next_word_length;

    next_word = (char*) malloc(next_word_length + 1); /* add '\0' */

    if(next_word)
    {
        Copy_Sub_String(next_word, text, *starting_index, *starting_index + next_word_length);
        next_word[next_word_length] = '\0';
        *starting_index += next_word_length;
    }

    return next_word;
}

int Is_Letter(char l)
{
    return (l >= MIN_CAPITAL_VAL && l <= MAX_CAPITAL_VAL) || (l >= MIN_REG_VAL && l <= MAX_REG_VAL);
}

int Get_String_Length(char *st)
{
    int length = 0;

    while('\0' != st[length])
        ++length;

    return length;
}

/* from start index until end, not included */
void Copy_Sub_String(char *dest, char *src, int start, int end)
{
    int i = 0;

    for(i = 0; i < end - start; ++i)
    {
        dest[i] = src[start + i];
    }
}