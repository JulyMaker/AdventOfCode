import re
import os

def cambiar_año_cmake(archivo_cmake, nuevo_año):
    """
    Cambia el año en un archivo CMakeLists.txt
    
    Args:
        archivo_cmake (str): Ruta al archivo CMakeLists.txt
        nuevo_año (str/int): Nuevo año a establecer
    """
    
    if not os.path.exists(archivo_cmake):
        print(f"Error: El archivo {archivo_cmake} no existe")
        return False
    
    with open(archivo_cmake, 'r', encoding='utf-8') as f:
        contenido = f.read()
    
    patrones_reemplazo = [
        (r'adventOfCode\d{4}', f'adventOfCode{nuevo_año}'),
        (r'advOCode\d{4}', f'advOCode{nuevo_año}')
    ]
    
    cambios_realizados = 0
    nuevo_contenido = contenido
    
    for patron, reemplazo in patrones_reemplazo:
        nuevo_contenido, num_cambios = re.subn(patron, reemplazo, nuevo_contenido)
        cambios_realizados += num_cambios
    
    if cambios_realizados > 0:
        with open(archivo_cmake, 'w', encoding='utf-8') as f:
            f.write(nuevo_contenido)
        print(f"✓ Año cambiado a {nuevo_año} en {cambios_realizados} lugares")
        return True
    else:
        print("✗ No se encontraron patrones para cambiar")
        return False

if __name__ == "__main__":
    
    print("CAMBIAR AÑO EN ARCHIVO CMakeLists")
    print("="*50)

    respuesta = input("¿Quieres ejecutar este paso? (s/n): ").strip().lower()

    if respuesta in ['s', 'si', 'sí', 'y', 'yes']:
        archivo = "CMakeLists.txt"
        año = input("Introduce el nuevo año: ").strip()
        if año.isdigit() and len(año) == 4:
            cambiar_año_cmake(archivo, año)
        else:
            print("Error: El año debe ser un número de 4 dígitos")