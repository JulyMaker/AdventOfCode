import re
import os
import argparse

def update_test_file(file_path, new_year):
    """
    Actualiza el archivo de tests con el nuevo año y resetea los valores EXPECT_EQ
    """
    try:
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()
        
        # 1. Detectar y cambiar el año en el nombre del archivo si es necesario
        filename = os.path.basename(file_path)
        old_year_match = re.search(r'adventOfCode(\d{4})_test\.cpp', filename)
        
        if old_year_match:
            old_year = old_year_match.group(1)
            new_filename = filename.replace(old_year, str(new_year))
            new_file_path = os.path.join(os.path.dirname(file_path), new_filename)
        else:
            # Si no encuentra patrón, crear nuevo nombre
            new_filename = f"adventOfCode{new_year}_test.cpp"
            new_file_path = os.path.join(os.path.dirname(file_path), new_filename)
        
        # 2. Cambiar el año en el string const std::string year = "2024";
        year_pattern = r'(const std::string year\s*=\s*")[\d]+(";)'
        content = re.sub(year_pattern, rf'\g<1>{new_year}\2', content)
        
        # 3. Cambiar el año en TEST(AdventOfCode2024,
        test_pattern = r'(TEST\()AdventOfCode\d+'
        content = re.sub(test_pattern, rf'\1AdventOfCode{new_year}', content)
        
        # 4. Cambiar todos los valores en EXPECT_EQ(numero, ...) por 0
        expect_pattern = r'(EXPECT_EQ\()\d+'
        content = re.sub(expect_pattern, r'\g<1>0', content)
        
        # Determinar si hay que renombrar el archivo
        if file_path != new_file_path:
            # Si el nombre cambia, escribir en nuevo archivo y eliminar el antiguo
            with open(new_file_path, 'w', encoding='utf-8') as file:
                file.write(content)
            os.remove(file_path)
            print(f"✅ Archivo renombrado: {filename} -> {new_filename}")
        else:
            # Si el nombre no cambia, solo modificar el contenido
            with open(file_path, 'w', encoding='utf-8') as file:
                file.write(content)
            print(f"✅ Archivo actualizado: {filename}")
        
        print(f"🔧 Cambios realizados:")
        print(f"   - Año actualizado a: {new_year}")
        print(f"   - Valores EXPECT_EQ reseteados a 0")
        
        return True
        
    except Exception as e:
        print(f"❌ Error procesando el archivo: {e}")
        return False

def main():
    
    print("CAMBIAR AÑO EN ARCHIVO adventOfCode2024_test.cpp Y VALORES 0")
    print("="*50)

    respuesta = input("¿Quieres ejecutar este paso? (s/n): ").strip().lower()

    if respuesta in ['s', 'si', 'sí', 'y', 'yes']:
        archivo = "adventOfCode2024_test.cpp"
        año = input("Introduce el nuevo año: ").strip()
        
        if not os.path.exists(archivo):
            print(f"❌ Error: El archivo '{file_path}' no existe")
            return
            
        if año.isdigit() and len(año) == 4:
            update_test_file(archivo, año)
        else:
            print("Error: El año debe ser un número de 4 dígitos")
        

if __name__ == "__main__":
    main()