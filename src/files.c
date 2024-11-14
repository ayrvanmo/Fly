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
            unsigned long entryId;
            char* entryPath;
            char* entryName;

            size_t routeLength = strlen(directory) + strlen(Entry->d_name) + 2;
            entryPath = malloc(routeLength);
            if (entryPath == NULL) {
                print_error(200,NULL,NULL);
                continue;
            }

            snprintf(entryPath, routeLength, "%s/%s", directory, Entry->d_name);
            entryId = Entry->d_ino;
            entryName = get_only_fileName(entryPath);
            insert_fileList_file(list, list, entryPath, entryName, entryId);
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
 * @param L Lista en la que se desea insertar el archivo
 * @param Prev Nodo previo al que se desea insertar el archivo
 * @param filePath Ruta del archivo
 * @param name Nombre del archivo
 * @param id Identificador del archivo
 * @return Puntero al archivo creado
*/
FilePosition insert_fileList_file(FileList L, FilePosition Prev, char* filePath, char* name, unsigned long id)
{
    FilePosition TmpCell;
    TmpCell = malloc(sizeof(struct _fileNode));

    if (TmpCell == NULL){
        print_error(200,NULL,NULL);
    }

    TmpCell->filePath = filePath;
    TmpCell->name = name;
    TmpCell->id = id;
    TmpCell->Next = Prev->Next;
    Prev->Next = TmpCell;
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
        printf("Archivo: %s, Inodo(ID): %lu, Nombre: %s\n", P->filePath, P->id, P->name);
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

    while (P != NULL) {
        delete_fileList_file(L, P);
        P = L->Next;
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
    L = malloc(sizeof(struct _fileNode));
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
void delete_fileList_file(FileList L, FilePosition file)
{
    if(file == NULL){
        print_error(203, NULL, NULL);
    }
    FilePosition prevNode = find_fileList_prev_file(L, file);
    if(prevNode == NULL){
        print_error(301, NULL, NULL);
        return;
    }
    free(file->name);
    free(file->filePath);
    prevNode->Next = file->Next;
    free(file);
}

/**
 * @brief Encuentra un archivo en la lista de archivos
 *
 * @param L Lista de archivos
 * @param fileName Nombre del archivo a buscar
 */
FilePosition find_fileList_file(FileList L, char* fileName)
{
    FilePosition P = L->Next;
    while (P != NULL && strcmp(P->name, fileName) != 0) {
            P = P->Next;
    }
    return P;
}

/**
 * @brief Encontrar el archivo anterior a @p File en @p L
 *
 * @param L Lista de archivos
 * @param File Puntero a la estructura que contiene información sobre el archivo
 * @return Puntero a la estructura que contiene información sobre el archivo
*/
FilePosition find_fileList_prev_file(FileList L, FilePosition File)
{
    FilePosition aux = L;
    while (aux != NULL && aux->Next != File)
    {
        aux = aux->Next;
    }
    return aux;
}

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
    FILE* file = fopen(fileInfo->filePath, "r");
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