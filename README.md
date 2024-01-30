# CircularBitShifter
Bruteforce decryption circular bit shift cipher


## Description
#### Décalage circulaire
Le décalage circulaire est souvent utilisé en cryptographie pour décaler tous les bits de l'opérande considéré. Il y a deux paramètres à prendre en compte :  
- Décalage : nombre de bits décalés  
- Blocs : groupes de bits sur laquelle on applique un décalage circulaire
  
Si vous faîtes un décalage circulaire à gauche sur le nombre 1101 0010 avec des blocs de 4 bits et des décalages de 2 bits, ça donnera 0111 1000.  
#### CircularBitShifter
Le script applique un bruteforce de décalage circulaire de bits sur une valeur hexadécimale en argument  
Les décalages circulaires de bits sont appliqués à des blocs de bits de tailles allant de 2 à 32, et des décalages de 1 à la taille du bloc  
Les résultats sont affichés en ASCII et permettent d'identifier les paramètres utilisés lors du chiffrement par décalage circulaire (nombre de blocs [] et nombre de décalage de bits)  

## Fonctionnalités
- Certains caractères sont remplacés pour éviter de flood le résultat (tab, saut de ligne, retour chariot...)
- Si la taille du bloc est supérieur aux nombres de bits le script s'arrête
- Des options permettent de rentrer une valeur dans le format souhaité, d'effectuer le décalage circulaire puis d'afficher les valeurs hexadécimales décimales et/ou binaires pour voir les détails, compter le nombre de caractères alphanumériques, permet de controler l'affichage lors du calcul des blocs, exporter sous un fichier output.txt


## Utilisation
`g++ CircularBitShifter.cpp -o CircularBitShifter.exe` Compilé avec Mingw32 11.2.0  
`CircularBitShifter.exe <valeur> [--format=<ascii|hex|bin>] [-b] [-h] [-d] [-i] [-e] [-m1 | -m2 | -m3]`  


## Options
    --format=<ascii|hex|bin> : Spécifie le format de sortie (par défaut : ascii)
    -b : Affiche la valeur en binaire
    -h : Affiche la valeur en hexadécimal
    -d : Affiche la valeur en décimal
    -i : Affiche le compte alphanumérique de la valeur
    -e : Exporte les résultats dans un fichier 'output.txt'
    -m1 : Affiche jusqu'à 32 blocs lors du décalage circulaire (par défaut)
    -m2 : Affiche jusqu'à 512 blocs lors du décalage circulaire
    -m3 : Affiche jusqu'à 4096 blocs lors du décalage circulaire


## Exemples
- Affichage simple en format d'entrée hexadécimal   
`CircularBitShifter.exe 36F65736F657 --format=hex`  
- Affichage avec détails de calcul hexadécimal et décimal  
`CircularBitShifter.exe test -h -d`  
- Affichage avec compteurs de caractères alphanumériques, exportation sous output.txt et calcul de tout les blocs possibles (m3)  
`CircularBitShifter.exe 36F65736F65736F65736F65736F65736F65736F65736F65736F65736F65736F65736F657 --format=hex -i -e -m3`  


