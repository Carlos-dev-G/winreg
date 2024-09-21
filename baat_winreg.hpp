// baat_winreg.hpp
// AUTOR: Carlos-dev-G
#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

class registro_windows
{
private:
    string nombre;
    string tipo;
    string path_registro;
    bool debug;

public:
    registro_windows(string nombre, string tipo, string path_registro, bool debug = false)
        : nombre(nombre), tipo(tipo), path_registro(path_registro), debug(debug) {}

    string obtener_nombre() const { return nombre; }
    string obtener_tipo() const { return tipo; }
    string obtener_path_registro() const { return path_registro; }

    void establecer_nombre(const string &nuevo_nombre) { nombre = nuevo_nombre; }
    void establecer_tipo(const string &nuevo_tipo) { tipo = nuevo_tipo; }
    void establecer_path_registro(const string &nuevo_path) { path_registro = nuevo_path; }

    bool crear_registro()
    {
        HKEY hKey;
        LONG estado = RegCreateKeyExA(
            HKEY_CURRENT_USER,
            path_registro.c_str(),
            0, NULL,
            REG_OPTION_NON_VOLATILE,
            KEY_ALL_ACCESS, NULL, &hKey, NULL);

        if (estado == ERROR_SUCCESS)
        {
            if (debug)
                OutputDebugStringA("Registro creado exitosamente");
            RegCloseKey(hKey);
            return true;
        }
        else
        {
            if (debug)
                OutputDebugStringA("Error al crear el registro");
            return false;
        }
    }

    bool borrar_registro()
    {
        LONG estado = RegDeleteKeyExA(HKEY_CURRENT_USER, path_registro.c_str(), 0, 0);
        if (estado == ERROR_SUCCESS)
        {
            if (debug)
                OutputDebugStringA("Borrado exitosamente");
            return true;
        }
        else
        {
            if (debug)
                OutputDebugStringA("Error al borrar el registro");
            return false;
        }
    }

    bool guardar_valor(const string &nombre_valor, const string &valor)
    {
        HKEY hKey;
        LONG estado = RegOpenKeyEx(
            HKEY_CURRENT_USER,
            path_registro.c_str(),
            0,
            KEY_SET_VALUE,
            &hKey);

        if (estado != ERROR_SUCCESS)
        {
            if (debug)
                OutputDebugStringA("Error al abrir el registro");
            return false;
        }

        LONG estado_nuevo = RegSetValueEx(
            hKey, nombre_valor.c_str(), 0, REG_SZ,
            reinterpret_cast<const BYTE *>(valor.c_str()),
            static_cast<DWORD>((valor.length() + 1) * sizeof(char)));

        RegCloseKey(hKey);

        if (estado_nuevo == ERROR_SUCCESS)
        {
            if (debug)
                OutputDebugStringA("Datos guardados correctamente");
            return true;
        }
        else
        {
            if (debug)
                OutputDebugStringA("Error al guardar los datos en la clave");
            return false;
        }
    }

    bool obtener_valor(const string &nombre_valor, char *buffer, DWORD &bufferSize)
    {
        HKEY hKey;
        LONG estado = RegOpenKeyEx(
            HKEY_CURRENT_USER,
            path_registro.c_str(),
            0,
            KEY_QUERY_VALUE,
            &hKey);

        if (estado != ERROR_SUCCESS)
        {
            if (debug)
                OutputDebugStringA("Error al abrir el registro");
            return false;
        }

        DWORD tipo_valor;
        LONG estado_valores = RegQueryValueEx(
            hKey,
            nombre_valor.c_str(),
            NULL,
            &tipo_valor,
            reinterpret_cast<BYTE *>(buffer),
            &bufferSize);
        RegCloseKey(hKey);

        if (estado_valores == ERROR_SUCCESS && tipo_valor == REG_SZ)
        {
            if (debug)
                OutputDebugStringA("Dato obtenido correctamente del registro");
            return true;
        }
        else
        {
            if (debug)
                OutputDebugStringA("No se pudo obtener el dato");
            return false;
        }
    }
};
