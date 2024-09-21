`baat_winreg.hpp` es una biblioteca de C++ que proporciona una interfaz simple para interactuar con el registro de Windows. Permite crear, eliminar y manipular claves del registro de manera eficiente.

## Características

- Crear claves del registro.
- Borrar claves del registro.
- Guardar y obtener valores de claves del registro.
- Opciones de depuración.

## Uso

### Requisitos

- Windows
- Compilador compatible con C++ (como TDM-GCC)

### Inclusión de la biblioteca

Para utilizar la biblioteca, asegúrate de incluir el archivo `baat_winreg.hpp` en tu proyecto.

### Ejemplo de código

```cpp
#include <iostream>
#include "baat_winreg.hpp"

int main() {
    // Crear un objeto de registro
    registro_windows registro("Ejemplo", "STRING", "Software\\MiAplicacion", true);

    // Crear una clave del registro
    if (registro.crear_registro()) {
        std::cout << "Clave del registro creada exitosamente." << std::endl;

        // Guardar un valor en la clave
        if (registro.guardar_valor("MiValor", "Hola Mundo")) {
            std::cout << "Valor guardado exitosamente." << std::endl;
        }

        // Obtener el valor guardado
        char buffer[256];
        DWORD bufferSize = sizeof(buffer);
        if (registro.obtener_valor("MiValor", buffer, bufferSize)) {
            std::cout << "Valor obtenido del registro: " << buffer << std::endl;
        }

        // Borrar la clave del registro
        if (registro.borrar_registro()) {
            std::cout << "Clave del registro borrada exitosamente." << std::endl;
        }
    } else {
        std::cout << "Error al crear la clave del registro." << std::endl;
    }

    return 0;
}
```

### Compilación

Para compilar tu programa, puedes usar el siguiente comando en TDM-GCC:

```bash
g++ -o mi_programa mi_programa.cpp
```

**Autor:** Carlos-dev-G


- Asegúrate de ejecutar tu programa con los permisos adecuados, ya que manipular el registro puede requerir privilegios elevados.
- La opción de depuración (`debug`) está habilitada por defecto, lo que permite ver mensajes útiles durante la ejecución.

## Licencia

Este proyecto está bajo la licencia MIT. Consulta el archivo LICENSE para más detalles.
