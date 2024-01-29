# CircularBitShifter
Bruteforce decryption circular bit shift cipher

## Comment ça marche ?
- Le script applique un bruteforce de décalage circulaire de bits sur une valeur hexadécimale en argument  
- Les décalages circulaires de bits sont appliqués à des blocs de bits de tailles allant de 2 à 32, et des décalages de 1 à la taille du bloc  
- Les résultats sont affichés en ASCII et permettent d'identifier les paramètres utilisés lors du chiffrement par décalage circulaire (nombre de blocs et nombre de décalage de bits)
- Des options permettent également d'afficher les valeurs hexadécimales décimales et/ou binaires pour voir les détails

## Compilation Mingw32 11.2.0
`g++ CircularBitShifter.cpp -o CircularBitShifter.exe`

## Utilisation
`CircularBitShifter.exe <valeur_hex> [-b] [-h] [-d]`

## Exemple d'utilisations
