import os
import re
import argparse

def delete_input_files(directory, confirm=True):
    """
    Borra archivos del tipo input01.txt, input02.txt, etc.
    """

    pattern = re.compile(r'^input\d{2}\.txt$')
    
    input_files = []
    
    for filename in os.listdir(directory):
        file_path = os.path.join(directory, filename)
        
        if os.path.isfile(file_path) and pattern.match(filename):
            input_files.append(filename)
    
    input_files.sort(key=lambda x: int(re.search(r'\d+', x).group()))
    
    if not input_files:
        print("No se encontraron archivos inputXX.txt en el directorio.")
        return
    
    print(f"\nTotal: {len(input_files)} archivos")
    
    if confirm:
        user_input = input(f"\n¿Estás seguro de que quieres borrar estos archivos? (escribe 'BORRAR' para confirmar): ")
        if user_input != "BORRAR":
            print("Operación cancelada.")
            return
    
    deleted_count = 0
    for filename in input_files:
        file_path = os.path.join(directory, filename)
        try:
            os.remove(file_path)
            print(f"✓ Borrado: {filename}")
            deleted_count += 1
        except Exception as e:
            print(f"✗ Error borrando {filename}: {e}")
    
    print(f"\n¡Proceso completado! {deleted_count} archivos inputXX.txt borrados.")

def main():
    directorio = "."
    confirm = False

    print("BORRA TODOS LOS INPUTS")
    print("="*50)

    respuesta = input("¿Quieres ejecutar este paso? (s/n): ").strip().lower()
    if respuesta in ['s', 'si', 'sí', 'y', 'yes']:
        confirm = True
    
    if not os.path.isdir(directorio):
        print(f"Error: El directorio '{args.directory}' no existe.")
        return
    
    delete_input_files(directorio, confirm)

if __name__ == "__main__":
    main()