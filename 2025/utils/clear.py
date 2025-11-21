import re
import argparse

def update_year_in_days_h(file_path, new_year):
    """
    Actualiza el año en todas las estructuras DEFINE_PROBLEM del archivo days.h
    """

    try:
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()
        
        pattern = r'(DEFINE_PROBLEM\()(\d{2}),\s*(\d{4})(\))'
        
        def replace_year(match):
            day = match.group(2)  # Número del día
            old_year = match.group(3)  # Año antiguo
            return f"DEFINE_PROBLEM({day}, {new_year})"
        
        new_content = re.sub(pattern, replace_year, content)
        
        changes = len(re.findall(pattern, content))
        
        if changes > 0:
            with open(file_path, 'w', encoding='utf-8') as file:
                file.write(new_content)
            
            print(f"✅ Año actualizado a {new_year} en {changes} estructuras DEFINE_PROBLEM")
            return True
        else:
            print("❌ No se encontraron estructuras DEFINE_PROBLEM para modificar")
            return False
            
    except Exception as e:
        print(f"❌ Error procesando el archivo: {e}")
        return False

def main():
    print("CAMBIAR AÑO EN ARCHIVO days.h")
    print("="*50)

    respuesta = input("¿Quieres ejecutar este paso? (s/n): ").strip().lower()

    if respuesta in ['s', 'si', 'sí', 'y', 'yes']:
        archivo = "days.h"
        año = input("Introduce el nuevo año: ").strip()
        update_year_in_days_h(archivo, año)

if __name__ == "__main__":
    main()