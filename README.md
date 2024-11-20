# Documentación general de Fly

## Autores
Franco Aguilar, Milton Hernandez, Ivan Mansilla, Ayrton Morrison

## Ejecución del programa
Para ejecutar el programa, se deben seguir los siguientes pasos:
1. Clonar el repositorio
2. Generar las carpetas necesarias con el comando `make folders`
3. Compilar el programa con el comando `make`
4. Entrar al directorio `build` y ejecutar el programa con el comando `./fly -d [ruta / directorio]` (`fly` se encuentra dentro de build)
5. Para utilizar el generador de archivos formateados`doc_generator.py` ,debe contar con `python3` junto a las siguientes bibliotecas:
- `requests`
- `time`
- `os`
- `random`

> ⚠️ Advertencia
> El API utilizado dentro del generador, tiene un maximo de 500 request por hora (por IP), por lo que se recomienda discrecion en su uso

### Otros comandos
- `make clean`: Borra los archivos generados por el programa
- `make doc` Generará una documentación con [Doxygen](https://www.doxygen.nl/), que se presentará en la carpeta `docs/doxygen`, se recomienda abrir el archivo `docs/doxygen/html/index.html` para visualizar la documentación completa del programa.
  - Alternativamente puede ejecutar `make` dentro de `docs/doxygen/latex/` para obtener un `refman.pdf` correspondiente a la documentación del proyecto en formato PDF.

## Manejo de errores
Dentro del archivo [errors.c](src/errors.c) se encuentra la función `print_error` que se encarga de manejar los errores que puedan ocurrir en el programa. Los códigos de error que se manejan son los siguientes:
| Código de error | Descripción |
| --- | --- |
| 100 | No se pudo leer el archivo |
| 200 | No hay memoria disponible |
| 201 | No se pudo acceder al sistema |
| 202 | Cantidad invalida, la cantidad ingresada debe ser mayor a 0 |
| 203 | Acceso a puntero nulo |
| 204 | No se pudo leer la palabra |
| 300 | Lista vacía |
| 301 | Nodo no encontrado |
| 302 | Tabla hash no existe |
| 303 | No se encontro el enlace |
| 304 | No se encontro el archivo |
| 305 | No se pudo abrir el directorio |
| 306 | No se ingreso ninguna palabra |
| 307 | Debe ingresar una palabra única |

Donde:
- 100 - 199 corresponden a errores comunes
- 200 - 299 corresponden a errores fatales
- 300 - 399 corresponden a advertencias


