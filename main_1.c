#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct words {
    int len;
    char* word;
    struct words* next;
};

struct words* SortFromText() {
    char buff[100];
    char* curword;
    bool wordAded = false;
    int CurrentSymb = 0;
    FILE* f = fopen("file1.txt", "r");
    struct words* Header = NULL;
    curword = malloc(100);
    while (fgets(buff, 100, f)) {
        CurrentSymb = 0;
        for (int i = 0; i < 100; i++) {
            wordAded = false;
            curword[i - CurrentSymb] = buff[i];
            if ((buff[i] == ' ' || buff[i]=='\n' || buff[i]=='\0') && (curword[0] != '\0')) {
                struct words* word = malloc(sizeof(struct words));
                word->len = i - CurrentSymb;
                word->word = malloc(word->len + 1);
                strncpy(word->word, curword, word->len);
                word->word[word->len] = '\0';
                word->next = NULL;
                CurrentSymb = i + 1;
                if (Header == NULL) {
                    Header = word;
                }
                else {
                    struct words* Current = Header;
                    struct words* Prev = NULL;
                    while (Current) {
                        if (word->len < Current->len) {
                            if (Prev == NULL) {
                                word->next = Header;
                                Header = word;
                            }
                            else {
                                word->next = Current;
                                Prev->next = word;
                            }
                            wordAded = true;
                            break;
                        }
                        else if ((word->len == Current->len) && strcmp(word->word, Current->word) < 0) {
                            if (Prev == NULL) {
                                word->next = Header;
                                Header = word;
                            }
                            else {
                                word->next = Current;
                                Prev->next = word;
                            }
                            wordAded = true;
                            break;
                        }
                        Prev = Current;
                        Current = Current->next;
                    }
                    if (!wordAded) {
                        struct words* Check = Header;
                        while (Check) {
                            if (Check->next == NULL) {
                                Check->next = word;
                                break;
                            }
                            Check = Check->next;
                        }
                    }
                    wordAded = false;
                }
            }
            if (buff[i] == '\n') break;
        }
    }
    free(curword);
    fclose(f);
    return Header; 
}


int main() {
    int Number;
    struct words* test1 = SortFromText();
    struct words* test2 = SortFromText();
    int N = 1;
    while (test1 != NULL) {
        if(test1->len>= N) printf("%s\n", test1->word);
        test1 = test1->next;
    }
    scanf("%d", &Number);
    while (test2 != NULL) {
        if (test2->len == Number) printf("%s\n", test2->word);
        test2 = test2->next;
    }
    return 0;
}
