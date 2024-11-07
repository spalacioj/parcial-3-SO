
# Compresion y encriptacion de archivos

Este proyecto implementa el algoritmo de compresión LZ78 y el algoritmo de encriptacion chacha20 en C++ para para comprimir y encriptar archivos y asi demostrar si es mas rapido comprimir y encriptar un archivo o viceversa.

## Descripción del Algoritmo LZ78

El algoritmo LZ78 es un método de compresión sin pérdida que trabaja con un diccionario de subcadenas. Cada subcadena se asocia con un índice único en el diccionario. A medida que se lee el archivo, se crea un par `(índice, símbolo)` para cada nueva subcadena, donde:
- **Índice**: Representa la posición de la subcadena previa en el diccionario.
- **Símbolo**: El siguiente carácter que completa la subcadena.

Al final, el diccionario contiene todas las combinaciones posibles de subcadenas encontradas en el archivo. La compresión se logra al referenciar cada subcadena mediante su índice en lugar de almacenarla completamente.

## Descripcion de la encriptacion chacha20

Chacha20 se basa en la idea de generar una secuencia de números pseudoaleatorios llamada “flujo de cifrado” y luego combinarla con los datos que se desean cifrar mediante una operación XOR, para ello utiliza bloques de 512 bits, donde cada bloque consta de 16 palabras de 32 bits. Estos bloques se utilizan como base para generar el flujo de cifrado. El proceso implica aplicar 20 rondas de operaciones al bloque para mezclar y ocultar su contenido.

## Estructura del Proyecto

- **LZ78Compressor.h**: Archivo de cabecera que define la clase `LZ78Compressor` con métodos de compresión y descompresión.
- **LZ78Compressor.cpp**: Implementación de los métodos de compresión y descompresión, junto con la función para mostrar la tabla de códigos.
- **main.cpp**: Programa principal que maneja los argumentos de la línea de comandos para preguntar que archivo usar y si comprimir o encriptar primero o viceversa y de la misma manera hacer lo inverso y por ultimo calcualr tiempo de ejecucion
- **Makefile**: Archivo para compilar el proyecto en Linux.
- **chacha20Encryptor.h**: Archivo de cabecera que define la clase `Chacha20Encryptor` con sus respectivos metodos y atributos
- **chacha20Encryptor.h**: Implementacion de los metodos de encriptar y desencriptar definidos en la clase cabecera
- **.gitignore**: aqui para evitar subir archivos de prueba al repo


## Uso del Programa

Para usar el programa, el programa acepta los siguientes argumentos en la línea de comandos:

```bash
./parcial3 # el programa pregunta las opciones a usar
```

## Pseudocódigos de las Funciones

### Función de Compresión

La función `compress` toma un archivo de entrada y genera un archivo comprimido utilizando el algoritmo LZ78.

#### Pseudocódigo

```
function compress(inputFilePath, outputFilePath):
    abrir archivo de entrada en modo binario
    si archivo de entrada no está abierto:
        mostrar error y terminar

    abrir archivo de salida en modo binario
    si archivo de salida no está abierto:
        mostrar error y terminar

    inicializar dictionary como mapa vacío
    inicializar buffer como cadena vacía
    inicializar dictIndex en 1

    mientras leer símbolo del archivo de entrada:
        combined = buffer + símbolo

        si combined no está en dictionary:
            si buffer está vacío:
                index = 0
            si no:
                index = dictionary[buffer]
            
            escribir index en archivo de salida
            escribir símbolo en archivo de salida
            
            agregar combined a dictionary con dictIndex como índice
            incrementar dictIndex
            limpiar buffer
        si no:
            buffer = combined

    si buffer no está vacío:
        escribir dictionary[buffer] en archivo de salida
        escribir un 0 como indicador de fin de buffer

    cerrar archivo de entrada
    cerrar archivo de salida
```

### Función de Descompresión

La función `decompress` toma un archivo comprimido y lo descomprime utilizando el algoritmo LZ78.

#### Pseudocódigo

```
function decompress(inputFilePath, outputFilePath):
    abrir archivo de entrada en modo binario
    si archivo de entrada no está abierto:
        mostrar error y terminar

    abrir archivo de salida en modo binario
    si archivo de salida no está abierto:
        mostrar error y terminar

    inicializar dictionary con una entrada vacía para índice 0

    mientras leer (index, símbolo) del archivo de entrada:
        entrada = dictionary[index] + símbolo
        escribir entrada en archivo de salida
        agregar entrada a dictionary

    cerrar archivo de entrada
    cerrar archivo de salida
```

## Tabla de Códigos de Palabras (Word Code Table)

Durante el proceso de compresión, se genera una tabla de códigos de palabras, que muestra cada subcadena junto con su índice en el diccionario en formato de tupla `(índice, subcadena)`. Esta tabla ayuda a visualizar el proceso de compresión y el contenido del diccionario en cada paso.

### Ejemplo de Salida de la Tabla de Códigos

```
Tabla de Códigos de Palabras (Word Code Table) en formato de tupla:
(1, A)
(2, AB)
(3, BA)
(4, B)
(5, BC)
```

## Compilación y Ejecución

Para compilar el programa en Linux, usa el archivo `Makefile` proporcionado:

```bash
make  # Compila el proyecto
make clean  # Limpia los archivos compilados
```

Ejecuta el programa usando los comandos indicados en la sección "Uso del Programa".

## Notas Importantes

- El archivo comprimido generado incluye los índices y símbolos en binario, por lo que no es directamente legible sin descompresión.
- El archivo encriptado tampoco puede ser legible hasta que sea desencriptado
- El codigo genera archivos temporales para la encriptacion y compresion que quedan guardados en la estructura del proyecto

## Referencias

- [Wikipedia - LZ78](https://en.wikipedia.org/wiki/LZ78): Explicación detallada del algoritmo LZ78 y su implementación.
- [Medium - Algoritmo de cifrado chacha20](https://medium.com/@parejaemi/algoritmo-de-cifrado-chacha20-119a6d7c19a7): Explicacion de funcionamiento algoritmo chacha20