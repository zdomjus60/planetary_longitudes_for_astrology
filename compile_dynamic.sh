#!/bin/bash

echo "--- Compilazione Libreria Dinamica ---"

# 1. Crea la directory per i file oggetto
mkdir -p obj/dynamic

# 2. Compila i sorgenti in file oggetto con -fPIC
#    Nota: i file .o vengono creati nella directory corrente
g++ -fPIC -c aaplus/*.cpp -I./aaplus -std=c++17

# 3. Sposta i file oggetto nella loro cartella
mv *.o obj/dynamic/

# 4. Crea la libreria dinamica con 'g++ -shared'
g++ -shared -o libaastro.so obj/dynamic/*.o

# 5. Compila il programma principale linkando la libreria dinamica
g++ main.cpp -I./aaplus -L. -laastro -o calcolatore_dynamic -std=c++17 -Wl,-rpath,.

echo "--- Compilazione Dinamica Completata ---"
echo "Eseguibile: ./calcolatore_dynamic"
