# CircularBitShifter
Bruteforce decryption circular bit shift cipher

## Comment ça marche ?
- Le script applique un bruteforce de décalage circulaire de bits sur une valeur hexadécimale en argument  
- Les décalages circulaires de bits sont appliqués à des blocs de bits de tailles allant de 2 à 32, et des décalages de 1 à la taille du bloc
- Les résultats sont affichés en ASCII et permettent d'identifier les paramètres utilisés lors du chiffrement par décalage circulaire (nombre de blocs et nombre de décalage de bits)
- Des options permettent également d'afficher les valeurs hexadécimales décimales et/ou binaires pour voir les détails
- Certains caractères sont remplacés pour éviter de flood le résultat (tab, saut de ligne, retour chariot...)
- Si la taille du bloc est supérieur aux nombres de bits le script s'arrête

## Compilation Mingw32 11.2.0
`g++ CircularBitShifter.cpp -o CircularBitShifter.exe`

## Utilisation
`CircularBitShifter.exe <valeur_hex> [-b] [-h] [-d]`


## Exemple d'utilisations
- Affichage simple  
`CircularBitShifter.exe 36F65736F657`  
![image](https://github.com/teddyfresnes/CircularBitShifter/assets/80900011/0b725bb1-bcc8-42e9-a569-75856fb68a58)  
- Affichage avec détails hexadécimal  
`CircularBitShifter.exe 36F65736F657 -h`  
![image](https://github.com/teddyfresnes/CircularBitShifter/assets/80900011/71b81c8f-f58e-4c66-8b2f-005a7eccb941)  
- Affichage avec détails binaire et décimal  
`CircularBitShifter.exe 36F65736F657 -b -d`  
![image](https://github.com/teddyfresnes/CircularBitShifter/assets/80900011/ebd2530b-8c5f-46e1-9710-f666127cdfd3)

## 
![image](https://github.com/teddyfresnes/CircularBitShifter/assets/80900011/5f6753a1-fac1-433a-bab0-e98c34a196c6)


