import os

def clear_files_keep_first_line(directory):
    """
    Borra todo el contenido de los archivos excepto la primera línea
    """

    print("BORRA CONTENIDO DE PROBLEMAS MENOS PRIMERA LINEA")
    print("="*50)

    respuesta = input("¿Quieres ejecutar este paso? (s/n): ").strip().lower()
    
    if respuesta in ['s', 'si', 'sí', 'y', 'yes']:
        current_script = os.path.basename(__file__)
        for filename in os.listdir(directory):
            file_path = os.path.join(directory, filename)
            
            # Solo procesar archivos (no directorios)
            if os.path.isfile(file_path) and filename != current_script:
                try:
                    # Leer el contenido del archivo
                    with open(file_path, 'r', encoding='utf-8') as file:
                        lines = file.readlines()
                    
                    # Mantener solo la primera línea si existe
                    if lines:
                        first_line = lines[0]
                        # Escribir solo la primera línea
                        with open(file_path, 'w', encoding='utf-8') as file:
                            file.write(first_line.rstrip('\n') + '\n')
                        print(f"Archivo procesado: {filename} (mantenida 1 línea)")
                    else:
                        print(f"Archivo vacío: {filename}")
                        
                except Exception as e:
                    print(f"Error procesando {filename}: {e}")
                    
        print("¡Proceso completado!")

# Uso
directory = "."
clear_files_keep_first_line(directory)