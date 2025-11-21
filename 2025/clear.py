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

def clean_answers_file(file_path, new_year):
    """
    Limpia el archivo Answers.md borrando respuestas y actualizando el año
    """
    try:
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()
        
        # 1. Actualizar el año en el título
        title_pattern = r'# AdventOfCode\d+Solutions'
        new_title = f"# AdventOfCode{new_year}Solutions"
        content = re.sub(title_pattern, new_title, content)
        
        # 2. Borrar todo lo que aparece después de "was" hasta <br> o fin de línea
        # Patrón para "was" seguido de cualquier cosa hasta <br> o fin de línea
        answer_pattern = r'(Your puzzle answer was).*?(?=<br>|\.\s*$|$)'
        
        def clean_answer(match):
            return f"{match.group(1)}."
        
        content = re.sub(answer_pattern, clean_answer, content, flags=re.MULTILINE | re.DOTALL)
        
        # 3. Escribir el contenido modificado
        with open(file_path, 'w', encoding='utf-8') as file:
            file.write(content)
        
        print(f"✅ Archivo limpiado exitosamente:")
        print(f"   - Año actualizado a: {new_year}")
        print(f"   - Respuestas borradas")
        
        return True
        
    except Exception as e:
        print(f"❌ Error procesando el archivo: {e}")
        return False

if __name__ == "__main__":
    
    print("CAMBIAR AÑO EN ARCHIVO CMakeLists Y RESPUESTAS ANSWERS.md")
    print("="*50)

    respuesta = input("¿Quieres ejecutar este paso? (s/n): ").strip().lower()

    if respuesta in ['s', 'si', 'sí', 'y', 'yes']:
        archivo = "CMakeLists.txt"
        archivo2 = "Answers.md"
        año = input("Introduce el nuevo año: ").strip()
        if año.isdigit() and len(año) == 4:
            cambiar_año_cmake(archivo, año)
            clean_answers_file(archivo2, año)
        else:
            print("Error: El año debe ser un número de 4 dígitos")