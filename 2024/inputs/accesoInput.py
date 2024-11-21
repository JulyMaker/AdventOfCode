import sys
import requests
from bs4 import BeautifulSoup

def input_Control():
    if len(sys.argv) < 4: # url, inputFile and cookie
        return -1
    
    # Inicia sesión en Advent of Code
    sesion = requests.Session()
    # Añade un encabezado personalizado (en este caso, Cookie)
    sesion.headers.update({'Cookie': f'session={sys.argv[3]}'})
    
    # Realiza la solicitud GET para la URL actual
    #url_adventofcode = "https://adventofcode.com/2023/day/1/input"
    url_adventofcode = sys.argv[1]
    respuesta = sesion.get(url_adventofcode)

    # Verifica si la solicitud fue exitosa (código de estado 200)
    if respuesta.status_code == 200:
        # Utiliza BeautifulSoup para analizar el contenido HTML de la página
        soup = BeautifulSoup(respuesta.text, 'html.parser')
        # Extrae y muestra el texto de la página
        texto_pagina = soup.get_text()
        
        # Guarda el texto en un archivo 
        nombre_archivo = sys.argv[2]
        with open(nombre_archivo, 'w', encoding='utf-8') as archivo:
            archivo.write(texto_pagina)
    else:
        print(f"Error al obtener la página {url_adventofcode}. Código de estado: {respuesta.status_code}")
        return -2
    
    return 0

input_Control()