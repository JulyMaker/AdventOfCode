import os

def clear_all_files(directory):
    """
    Borra el contenido de todos los archivos en el directorio
    """

    print("BORRA CONTENIDO DE EJEMPLOS")
    print("="*50)

    respuesta = input("¿Quieres ejecutar este paso? (s/n): ").strip().lower()
    
    if respuesta in ['s', 'si', 'sí', 'y', 'yes']:
        current_script = os.path.basename(__file__)

        for filename in os.listdir(directory):
            file_path = os.path.join(directory, filename)
            
            if os.path.isfile(file_path) and filename != current_script:
                with open(file_path, 'w', encoding='utf-8') as file:
                    file.write('')  # Escribir string vacío
                print(f"Contenido borrado: {filename}")
                
        print("¡Contenido de todos los archivos borrado!")

# Uso
directory = "." 
clear_all_files(directory)