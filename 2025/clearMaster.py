import os
import subprocess
import sys

def ejecutar_clear_scripts_con_confirmacion(directorio_raiz="."):
    """
    Busca clear.py, muestra la lista y pide confirmación antes de ejecutar
    """
    scripts_encontrados = []
    
    # Buscar todos los archivos clear.py
    for root, dirs, files in os.walk(directorio_raiz):
        if "clear.py" in files:
            ruta_completa = os.path.join(root, "clear.py")
            scripts_encontrados.append(ruta_completa)
    
    if not scripts_encontrados:
        print("No se encontraron archivos clear.py")
        return
    
    print("Scripts clear.py encontrados:")
    for i, script in enumerate(scripts_encontrados, 1):
        print(f"  {i}. {script}")
    
    # Pedir confirmación
    respuesta = input(f"\n¿Ejecutar estos {len(scripts_encontrados)} scripts? (s/n): ")
    if respuesta.lower() != 's':
        print("Ejecución cancelada")
        return
    
    # Ejecutar cada script
    directorio_original = os.getcwd()
    
    for i, script in enumerate(scripts_encontrados, 1):
        print(f"\n{'='*50}")
        print(f"Ejecutando {script} ({i}/{len(scripts_encontrados)})")
        
        try:
            directorio_script = os.path.dirname(script)
            os.chdir(directorio_script)
            
            # Ejecutar interactivamente
            subprocess.run([sys.executable, "clear.py"])
            
        except Exception as e:
            print(f"Error ejecutando {script}: {e}")
        finally:
            os.chdir(directorio_original)
    
    print("\n✓ Todos los scripts han sido procesados")

if __name__ == "__main__":
    ejecutar_clear_scripts_con_confirmacion()