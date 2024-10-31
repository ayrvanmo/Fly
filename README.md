# FlySearch
Autores: Franco Aguilar, Milton Hernandez, Ivan Mansilla, Ayrton Morrison

## Objetivo
Este proyecto tiene como objetivo la creación de un sistema avanzado de recuperación de información mediante el `Índice invertido` y el algoritmo `PageRank`.

### Desglose de objetivos
1. PageRank
    - Investigar el algoritmo y su funcionamiento
    - Investigar el concepto de `dumpingFactor` y el mejor valor para el mismo según bibliografía
    - Cómo implementar esto en C teniendo ya un grafo dirigido creado con una **lista de adyacencias**
2. Índice invertido
    - Investigar el concepto y su funcionamiento
    - PLantear opciones para su implementación
    - Implementar la estructura de datos necesaria para el índice invertido
        - Estructura de datos
        - Funciones para que se comporte como un diccionario
4. Recuperación de información
    - ¿Cómo leer un directorio, sus elementos y sus sub-directorios?
    - ¿Cómo procesar cada uno de estos elementos y guardar su información en el grafo de adyacencias y en el índice invertido?
5. Otros conceptos
    - Las `stopwords` y su importancia en el índice invertido.
        - Cómo implementar una búsqueda dentro de un grupo de "stopwords" para filtrar los archivos
        - ¿Podemos tener un archivo con "stopwords" personalizadas y leerlas de allí inicialmente?
        - Implementación de archivos temporales con "stopwords" filtradas
        - Valorar la necesidad del uso de un archivo intermedio, un archivo temporal, para almacenar los archivos filtrados
        - Posibles conflictos con tildes?
6. Otros objetivos
    - Mantener una correcta bibliografía de la información consultada
    - Documentación con comentarios de `Doxygen`

### Fases

#### Semana 1:
- [ ] Investigación del concepto de `pageRank` (Ayrton)
- [ ] Investigar el concepto de `Índice invertido` y su funcionamiento (Iván)
- [ ] Implementación de la estructura del grafo de archivos con una lista de adyacencias (Milton)
- [ ] Encontrar una manera de obtener referencias a los archivos de un directorio y sus subdirectorios mediante `dirent.h` (Franco)

## Asignación de roles
Sección Pendiente (se revisará luego de la primera semana)