import requests
import time
import os
import random

def obtener_articulos_aleatorios(n=15):
    articulos = []
    url_random = "https://es.wikipedia.org/api/rest_v1/page/random/summary"

    for i in range(n):
        print(rf"Obteniendo documento {i+1} de {n}")
        response = requests.get(url_random)

        if response.status_code == 200:
            data = response.json()
            titulo = data.get("title")
            extracto = data.get("extract")

            # Almacenar el título y el extracto en una lista
            articulos.append((titulo, extracto))

            # Tiempo de espera para evitar sobrecargar el servidor
            time.sleep(0.1)  # Espera de 100ms
        else:
            print("No se pudo obtener un artículo en este intento.")

    return articulos

# Llamar a la función y mostrar los resultados
articulos = obtener_articulos_aleatorios(int(input("Ingrese el número de documentos a generar: ")))

# Creamos la carpeta docs si no existe
if not os.path.exists("docs"):
    os.mkdir(f"docs")

for i, (titulo, extracto) in enumerate(articulos, start=1):
    print(f"Procesando artículo {i} de {len(articulos)}")

    # Reemplazar caracteres no válidos en los nombres de archivo
    titulo_limpio = titulo.replace("/", "-").replace("\\", "-").replace(":", "-")

    # Crear y escribir en el archivo
    ruta_archivo = f"docs/{titulo_limpio}.txt"
    with open(ruta_archivo, "w", encoding="utf-8") as archivo:
        archivo.write(f"{extracto}\n\n")

        # Agregar enlaces al final del archivo
        enlaces = random.sample(articulos, k=min(10, random.randint(1, len(articulos))))
        for enlace in enlaces:
            titulo_limpio = enlace[0].replace("/", "-").replace("\\", "-").replace(":", "-")
            archivo.write(f"[[{titulo_limpio}]]\n")
