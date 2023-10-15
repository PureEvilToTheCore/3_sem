#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h >

struct words {
    int len;
    char* word;
    struct words* next;
};
struct words* AddWord(char* curword, int length){
    struct words* word = malloc(sizeof(struct words));
    word->len = length;
    word->word = malloc(word->len + 1);
    strncpy(word->word, curword, word->len);
    word->word[word->len] = '\0';
    word->next = NULL;
    return word;
}

struct words* Sort(struct words* word, struct words* head) {
    
    if (head == NULL) {
        head = word;
        return head;
    }
    else {
        struct words* Current = head;
        struct words* Prev = NULL;
        while (Current) {
            if ((word->len < Current->len) || ((word->len == Current->len) && strcmp(word->word, Current->word) < 0)) {
                if (Prev == NULL) {
                    word->next = head;
                    head = word;
                    return head;
                }
                else {
                    word->next = Current;
                    Prev->next = word;
                    return head;
                }
            }
            Prev = Current;
            Current = Current->next;
        }
        struct words* Check = head;
        while (Check) {
            if (Check->next == NULL) {
                Check->next = word;
                break;
            }
            Check = Check->next;
        }
        return head;
    }
}

struct words* SortFromText() {
    char buff[100];
    char* curword;
    int CurrentSymb = 0;
    FILE* f = fopen("file.txt", "r");
    struct words* Header = NULL;
    curword = malloc(100);
    while (fgets(buff, 100, f)) {
        CurrentSymb = 0;
        for (int i = 0; i < 100; i++) {
            curword[i - CurrentSymb] = buff[i];
            if ((buff[i] == ' ' || buff[i] == '\n' || buff[i] == '\0') && ((i - CurrentSymb)>0)) {
                struct words* Word = AddWord(curword, i - CurrentSymb);
                CurrentSymb = i + 1;
                Header = Sort(Word, Header);
            }
            if (buff[i] == '\n') break;
        }
    }
    free(curword);
    fclose(f);
    return Header;
}

void SortByNumber(int Numb) {
    struct words* list = SortFromText();
    while (list != NULL) {
        if (list->len >= Numb) printf("%s\n", list->word);
        list = list->next;
    }
}

void SortForLen() {
    bool WordAdd = false;
    int Numb;
    int Choose;
    scanf("%d", &Numb);
    struct words* list = SortFromText();
    struct words* head = list;
    while (list != NULL) {
        if (list->len == Numb) {
            printf("%s\n", "Слова введённой длины есть, если хотите их вывести напишите 1");
            WordAdd = true;
            break;
        }
        list = list->next;
    }
    if(!WordAdd) printf("%s\n", "Слов такой длины в файле нет");
    scanf("%d", &Choose);
    if(Choose == 1) {
        while (head != NULL) {
            if (head->len == Numb) printf("%s\n", head->word);
            head = head->next;
        }
    }
}


int main() {
    char* locale = setlocale(LC_ALL, "");
    int Number = 6;
    SortByNumber(Number);
    SortForLen();
    return 0; 
}