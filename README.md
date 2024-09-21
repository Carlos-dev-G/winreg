# `baat_winreg.hpp`

`baat_winreg.hpp` es una biblioteca de C++ diseñada para ofrecer una interfaz sencilla y eficiente para interactuar con el registro de Windows. Facilita la creación, eliminación y manipulación de claves del registro, lo que permite a los desarrolladores gestionar configuraciones de aplicaciones de manera efectiva.

## Características

- **Crear claves del registro:** Genera nuevas entradas en el registro.
- **Borrar claves del registro:** Elimina claves y sus valores asociados.
- **Guardar y obtener valores:** Almacena y recupera datos de las claves del registro.
- **Opciones de depuración:** Mensajes útiles durante la ejecución para facilitar la identificación de problemas.

## Uso

### Requisitos

- **Sistema operativo:** Windows
- **Compilador:** Compatible con C++ (como TDM-GCC)

### Inclusión de la biblioteca

Asegúrate de incluir el archivo `baat_winreg.hpp` en tu proyecto para utilizar la biblioteca.

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

Para compilar tu programa, usa el siguiente comando en TDM-GCC:

```bash
g++ -o mi_programa mi_programa.cpp
```

### Notas Adicionales
- **Depuración:** La opción de depuración (`debug`) está habilitada por defecto. Utiliza `gdb` para depurar si es necesario.

## Licencia

Este proyecto está bajo la licencia MIT. Consulta el archivo LICENSE para más detalles.
