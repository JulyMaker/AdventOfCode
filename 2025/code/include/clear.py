import os
import re

def cambiar_año_archivos(carpeta, año_nuevo, año_viejo="2024"):
    """
    Cambia el año en todos los archivos day*.h de la carpeta
    """
    
    resultado = {
        'archivos_modificados': 0,
        'archivos_procesados': 0,
        'errores': [],
        'carpeta': carpeta,
        'año_nuevo': año_nuevo,
        'año_viejo': año_viejo
    }
    
    if not os.path.isdir(carpeta):
        resultado['errores'].append(f"La carpeta '{carpeta}' no existe")
        resultado['exitoso'] = False
        return resultado
    
    patron_archivo = re.compile(r'day\d+_.*\.h$')
    
    try:
        for nombre_archivo in os.listdir(carpeta):
            if patron_archivo.match(nombre_archivo):
                resultado['archivos_procesados'] += 1
                ruta_archivo = os.path.join(carpeta, nombre_archivo)
                
                try:
                    with open(ruta_archivo, 'r', encoding='utf-8') as archivo:
                        contenido = archivo.read()
                    
                    contenido_nuevo = contenido.replace(año_viejo, año_nuevo)
                    
                    if contenido_nuevo != contenido:
                        with open(ruta_archivo, 'w', encoding='utf-8') as archivo:
                            archivo.write(contenido_nuevo)
                        resultado['archivos_modificados'] += 1
                        print(f"✓ Año cambiado en: {nombre_archivo}")
                    
                except Exception as e:
                    error_msg = f"Error en {nombre_archivo}: {e}"
                    resultado['errores'].append(error_msg)
                    print(f"✗ {error_msg}")
        
        resultado['exitoso'] = True
        print(f"\n✅ Cambio de año completado: {resultado['archivos_modificados']}/{resultado['archivos_procesados']} archivos modificados")
        
    except Exception as e:
        resultado['errores'].append(f"Error general: {e}")
        resultado['exitoso'] = False
    
    return resultado


def preguntar_ejecutar_paso():
    print("CAMBIAR AÑO EN ARCHIVOS DAY*.H")
    print("="*50)
    
    respuesta = input("¿Quieres ejecutar este paso? (s/n/saltar): ").strip().lower()
    
    if respuesta in ['s', 'si', 'sí', 'y', 'yes']:
        carpeta = "."
        año_viejo = input("Introduce el año viejo (ej: 2025): ").strip()
        año_nuevo = input("Introduce el nuevo año (ej: 2025): ").strip()
        
        if not año_nuevo.isdigit() or len(año_nuevo) != 4:
            print("❌ Año inválido. Usando 2025 por defecto.")
            año_nuevo = "2025"
        
        return cambiar_año_archivos(carpeta, año_nuevo, año_viejo)
    
    elif respuesta in ['saltar', 'skip', 'omitir']:
        print("⏭️  Paso saltado")
        return {'exitoso': True, 'saltado': True}
    
    else:
        return

if __name__ == "__main__":
    resultado = preguntar_ejecutar_paso()
    print(f"\nResultado: {resultado}")