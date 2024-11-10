#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "reverse_index.h"
#include "stop_words.h"
#include "graph.h"
#include "utilities.h"

int main(){
    char word[25];

    StopWordsTable stopWords = read_stopWord_file("./spanish.txt", NULL);

    printf("exit para salir\n");
    while(1)
    {
        printf("Ingrese una palabra: ");
        scanf("%s", word);
        if(strcmp(word, "exit") == 0){
            break;
        }
        if(is_stopWord(word, stopWords)){
            printf("Palabra %s es un stop word\n", word);
        }
        else{
            printf("Palabra %s no es un stop word\n", word);
        }
    }

    delete_stopWordsTable(stopWords);
    return 0;
}