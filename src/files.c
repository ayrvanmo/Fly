#include "files.h"

/**
 * @brief Consigue los archivos de un directorio
 *
 * @param directory Directorio donde comienza la busqueda
 * @param list Lista de archivos
 * @return Lista de archivos
 */
FileList get_files_from_directory(char *directory, FileList list)
{
    DIR *Dir;
    struct dirent *Entry;

    Dir = opendir(directory);

    if(Dir == NULL){
        print_error(305,directory,NULL);
        return NULL;
    }

    if (list == NULL) {
        list = make_empty_fileList(NULL);
    }

    while ((Entry = readdir(Dir)) != NULL) {
        if (strcmp(Entry->d_name, ".") == 0 || strcmp(Entry->d_name, "..") == 0){
            continue;
        }

        if (Entry->d_type == 8) { // archivo
            fileInfo NewFile;

            size_t routeLength = strlen(directory) + strlen(Entry->d_name) + 2;
            NewFile.filePath = malloc(routeLength);
            if (NewFile.filePath == NULL) {
                print_error(200,NULL,NULL);
                continue;
            }

            snprintf(NewFile.filePath, routeLength, "%s/%s", directory, Entry->d_name);
            NewFile.id = Entry->d_ino;
            NewFile.name = get_only_fileName(NewFile.filePath);
            insert_fileList_file(NewFile, list, list);
        }

        if (Entry->d_type == 4) {  // subdirectorio
            size_t Length = strlen(directory) + strlen(Entry->d_name) + 2;
            char *SubDir = malloc(Length);

            if (SubDir == NULL) {
                print_error(200,NULL,NULL);
                continue;
            }

            snprintf(SubDir, Length, "%s/%s", directory, Entry->d_name);
            get_files_from_directory(SubDir, list);
            free(SubDir);
        }
    }
    closedir(Dir);
    return list;
}

/**
 * @brief Inserta un archivo en la lista de archivos
 *
 * @param X Archivo a insertar
 * @param L Lista de archivos
 * @param P Posicion donde se inserta el archivo
 * @return Posicion donde se inserto el archivo
 */
FilePosition insert_fileList_file(fileInfo X, FileList L, FilePosition P)
{
    FilePosition TmpCell;
    TmpCell = malloc(sizeof(struct Node));

    if (TmpCell == NULL){
        print_error(200,NULL,NULL);
    }

    TmpCell->Element = X;
    TmpCell->Next = P->Next;
    P->Next = TmpCell;
    L->fileCount++;
    return TmpCell;
}

/**
 * @brief imprime la lista de archivos
 *
 * @param L Lista de archivos
 */
void print_fileList(FileList L)
{
    FilePosition P = L->Next;
    printf("Lista de archivos:\n");

    while (P != NULL) {
        printf("Archivo: %s, Inodo(ID): %lu, Nombre: %s\n", P->Element.filePath, P->Element.id, P->Element.name);
        P = P->Next;
    }
    printf("Numero de archivos: %d\n", count_filesList(L));
}

/**
 * @brief Elimina la lista de archivos
 *
 * @param L Lista de archivos
 */
void delete_fileList(FileList L)
{
    FilePosition P = L->Next;
    FilePosition Tmp;
    L->Next = NULL;

    while (P != NULL) {
        Tmp = P->Next;
        free(P->Element.filePath);
        free(P->Element.name);
        free(P);
        P = Tmp;
    }
    free(L);
}

/**
 * @brief Crea una lista de archivos vacia
 *
 * @param L Lista de archivos
 */
FileList make_empty_fileList(FileList L)
{
    if (L != NULL){
        delete_fileList(L);
    }
    L = malloc(sizeof(struct Node));
    if (L == NULL) {
        print_error(200,NULL,NULL);
    }
    L->Next = NULL;
    L->fileCount = 0;
    return L;
}

/**
 * @brief numero de archivos en la lista de archivos
 *
 * @param L Lista de archivos
 *
 * @return numero de archivos
 */
int count_filesList(FileList L)
{
    return L->fileCount;
}

/**
 * @brief Elimina un archivo de la lista de archivos
 *
 * @param L Lista de archivos
 * @param fileName Nombre del archivo a eliminar
 */
void delete_fileList_file(FileList L, char *fileName)
{
    fileName = get_only_fileName(fileName);
    FilePosition P = L->Next;
    FilePosition Tmp = L;

    while (P != NULL) {
        if (strcmp(P->Element.name, fileName) == 0) {
            free(P->Element.filePath);
            free(P->Element.name);
            Tmp->Next = P->Next;
            free(P);
            free(fileName);
            L->fileCount--;
            return;
        }
        Tmp = P;
        P = P->Next;
    }
    print_error(304,fileName,NULL);
}

/**
 * @brief Encuentra un archivo en la lista de archivos
 *
 * @param L Lista de archivos
 * @param fileName Nombre del archivo a buscar
 */
/*FilePosition find_fileList_file(FileList L, char* fileName)
{
    FilePosition P = L->Next;

    while (P != NULL && strcmp(P->Element.name, fileName) != 0) {
            P = P->Next;
        }

    return P;
}*/

/**
 * @brief Procesa un archivo para incluirlo en el sistema de busqueda
 *
 * @param fileInfo Puntero a la estructura que contiene información sobre el archivo
 * @param graph Puntero al grafo en el que se desea insertar el archivo
 * @param index Puntero al indice invertido donde se almacenan las palabras del archivo
 * @param stopWords Puntero al diccionario de stop words
*/
void process_file(FilePosition fileInfo, Graph graph, ReverseIndexTable index, StopWordsTable stopWords)
{
    FILE* file = fopen(fileInfo->Element.filePath, "r");
    GraphPosition P = insert_graphNode(fileInfo, graph);

    char word[50];
    while(fscanf(file, "%s", word) != EOF){
        to_low_case(word);
        remove_punctuation(word);

        if(!is_stopWord(word, stopWords)){
            printf("%s\n", word);
            insert_file_to_index(index, P, word);
        }
    }
    fclose(file);
}