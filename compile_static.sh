#!/bin/bash

echo "--- Compilazione Libreria Statica ---"

# 1. Crea la directory per i file oggetto
mkdir -p obj/static

# 2. Compila i sorgenti in file oggetto con -c
#    Nota: i file .o vengono creati nella directory corrente
g++ -c aaplus/*.cpp -I./aaplus -std=c++17

# 3. Sposta i file oggetto nella loro cartella
mv *.o obj/static/

# 4. Crea la libreria statica con 'ar'
ar rcs libaastro.a obj/static/*.o

# 5. Compila il programma principale linkando la libreria statica
g++ main.cpp -I./aaplus -L. -laastro -static -o calcolatore_static -std=c++17

echo "--- Compilazione Statica Completata ---"
echo "Eseguibile: ./calcolatore_static"
