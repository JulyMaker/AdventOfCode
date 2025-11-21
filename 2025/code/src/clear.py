import os
import re
import argparse

def rename_files(directory, year):
    """
    Renombra archivos y modifica las funciones dentro de ellos
    """

    file_pattern = re.compile(r'^(day\d+_.*\.cpp)$')
    function_pattern = re.compile(r'(uint64_t adventDay(\d+)P[12])(\d{4})\((std::ifstream& input)\)')
    
    for filename in os.listdir(directory):
        file_path = os.path.join(directory, filename)
        
        if os.path.isfile(file_path) and filename.endswith('.cpp') and file_pattern.match(filename):

            match = re.match(r'(day\d+_)', filename)
            if match:
                new_filename = match.group(1) + ".cpp"
                new_file_path = os.path.join(directory, new_filename)
                
                with open(file_path, 'r', encoding='utf-8') as file:
                    content = file.read()
                
                def replace_function(match):
                    function_start = match.group(1)  # uint64_t adventDayXXP[12]
                    day_number = match.group(2)      # número del día
                    old_year = match.group(3)        # año antiguo
                    parameters = match.group(4)      # parámetros
                    # Reemplazar con el nuevo año
                    return f"{function_start}{year}({parameters})"
                
                new_content = function_pattern.sub(replace_function, content)
                
                if filename != new_filename:
                    with open(new_file_path, 'w', encoding='utf-8') as file:
                        file.write(new_content)
                    os.remove(file_path)
                    print(f"Renombrado: {filename} -> {new_filename} y año actualizado a {year}")
                else:
                    with open(file_path, 'w', encoding='utf-8') as file:
                        file.write(new_content)
                    print(f"Archivo {filename} actualizado con año {year}")

def main():
    directorio = "."
    año = input("Introduce el nuevo año: ").strip()
    
    if not os.path.isdir(directorio):
        print(f"Error: El directorio '{args.directory}' no existe.")
        return
    
    rename_files(directorio, año)
    print("Proceso completado!")

if __name__ == "__main__":
    print("RENOMBRA CPPs Y CAMBIA AÑO")
    print("="*50)
    
    respuesta = input("¿Quieres ejecutar este paso? (s/n): ").strip().lower()
    
    if respuesta in ['s', 'si', 'sí', 'y', 'yes']:
        main()