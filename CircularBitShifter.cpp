#include <iostream>
#include <iomanip>
#include <sstream>
#include <bitset>
#include <algorithm>
#include <fstream>



enum Format {
    ASCII,
    HEX,
    BIN
};



// décalage circulaire vers la gauche sur chaque bloc de bits
std::string circularShift(const std::string& binaryValue, int blockSize, int shift, bool shiftRight)
{
	const int bitSize = 8 * sizeof(unsigned long long);
    std::string result;
    for (size_t i = 0; i < binaryValue.length(); i+=blockSize)
	{
        std::bitset<4096> block(binaryValue.substr(i, blockSize));
        if (shiftRight) {
            block = (block >> shift) | (block << (blockSize - shift));
        } else { // decalage a gauche par defaut
            block = (block << shift) | (block >> (blockSize - shift));
        }
        result += block.to_string().substr(4096-blockSize);
    }
	result.erase(result.find_last_not_of('0') + 1); // efface les 0 en trop a la fin
    return result;
}



 // compte le nb de caracteres pour avoir une approximation
int countAlphanumeric(const std::string& asciiValue)
{
    int count = 0;
    for (char c : asciiValue)
        {if (std::isalnum(c))
			{count++;}}
    return count;
}




// fonction de conversion
std::string stringToHex(const std::string& input) {
    std::stringstream hexStream;
    for (unsigned char c : input) {
        hexStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
    }
    return hexStream.str();
}
std::string hexToString(const std::string& hexInput) {
    if (hexInput.length() % 2 != 0) {
        throw std::invalid_argument("La longueur de la chaîne hexadécimale doit être paire.");
    }
    std::stringstream asciiStream;
    for (size_t i = 0; i < hexInput.length(); i += 2) {
        std::string byteStr = hexInput.substr(i, 2);
        char byte = static_cast<char>(std::stoi(byteStr, nullptr, 16));
        asciiStream << byte;
    }
    return asciiStream.str();
}
std::string binaryToHex(const std::string& binaryValue) {
    // check si on a bien des octets
    if (binaryValue.length() % 8 != 0) {
        throw std::invalid_argument("La longueur de l'argument binaire doit etre un multiple de 8");
    }
    std::bitset<8> bits;
    std::stringstream hexStream;
    for (size_t i = 0; i < binaryValue.length(); i += 8) {
        bits = std::bitset<8>(binaryValue.substr(i, 8));
        hexStream << std::hex << bits.to_ulong();
    }
    return hexStream.str();
}
std::string hexToBinary(const std::string& hexValue) {
    std::stringstream binaryStream;
    for (char c : hexValue) {
        std::string hexChar(1, c);
        int intValue;
        std::istringstream(hexChar) >> std::hex >> intValue;
        binaryStream << std::bitset<4>(intValue).to_string();
    }
    return binaryStream.str();
}



/* MAIN */
int main(int argc, char* argv[])
{
	Format outputFormat = ASCII;
	
	
    if (argc < 2)
	{
		std::cerr << "Utilisation: " << argv[0] << " <valeur> [--format=<ascii|hex|bin>] [-b] [-h] [-d] [-i] [-e] [-m1 | -m2 | -m3]" << std::endl;
		std::cerr << "Options :" << std::endl;
		std::cerr << "  --format=<ascii|hex|bin> : Format de de la valeur d'entree (par defaut : ascii)" << std::endl;
		std::cerr << "  --shift=<left|right> : Sens du decalage circulaire (par defaut : left)" << std::endl;
		std::cerr << "  -b : Affiche la valeur en binaire" << std::endl;
		std::cerr << "  -h : Affiche la valeur en hexadecimal" << std::endl;
		std::cerr << "  -d : Affiche la valeur en decimal" << std::endl;
		std::cerr << "  -i : Affiche le compte alphanumerique de la valeur" << std::endl;
		std::cerr << "  -e : Exporte les résultats dans un fichier 'output.txt'" << std::endl;
		std::cerr << "  -m1 : Affiche jusqu'a 32 blocs lors du decalage circulaire (par defaut)" << std::endl;
		std::cerr << "  -m2 : Affiche jusqu'a 512 blocs lors du decalage circulaire" << std::endl;
		std::cerr << "  -m3 : Affiche jusqu'a 4096 blocs lors du decalage circulaire (utile pour grandes valeurs)" << std::endl;
        return 1;
    }


    bool displayBinary = false;
    bool displayHex = false;
    bool displayDecimal = false;
	bool exportToFile = false;
	std::ofstream outputFile;
	bool shiftRight = false;
	bool displayAlphanumericCount = false;
	int maxAlphanumericCount = 0;
	int maxBlockSize = 32;



    /* GESTION DES ARGUMENTS */
    for (int i=2; i<argc; ++i)
	{
        if (std::string(argv[i]) == "-b")
		{
            displayBinary = true;
        }
		else if (std::string(argv[i]) == "-h")
		{
            displayHex = true;
        }
		else if (std::string(argv[i]) == "-d")
		{
            displayDecimal = true;
        }
        else if (std::string(argv[i]) == "-i")
        {
            displayAlphanumericCount = true;
        }
		else if (std::string(argv[i]) == "-e")
		{
			exportToFile = true;
			outputFile.open("output.txt", std::ios::out); // writing
			if (!outputFile.is_open())
			{
				std::cerr << "Erreur lors de l'ouverture du fichier output.txt" << std::endl;
				return 1;
			}
		}
		else if (std::string(argv[i]) == "-m1")
		{
			maxBlockSize = 32;
		}
		else if (std::string(argv[i]) == "-m2")
		{
			maxBlockSize = 512;
		}
		else if (std::string(argv[i]) == "-m3")
		{
			maxBlockSize = 4096;
		}
        else if (std::string(argv[i]) == "--shift=right")
        {
            shiftRight = true;
        }
        else if (std::string(argv[i]) == "--shift=left")
        {
            shiftRight = false;
        }
		else if (std::string(argv[i]) == "--format=ascii")
		{
			outputFormat = ASCII;
		}
		else if (std::string(argv[i]) == "--format=hex")
		{
			outputFormat = HEX;
		}
		else if (std::string(argv[i]) == "--format=bin")
		{
			outputFormat = BIN;
		}
        else if (std::string(argv[i]).find("--format=") == 0)
        {
            // prend le texte après "--format="
            std::string formatOption = std::string(argv[i]).substr(9);
            if (formatOption == "ascii")
            {
                outputFormat = ASCII;
            }
            else if (formatOption == "hex")
            {
                outputFormat = HEX;
            }
            else if (formatOption == "bin")
            {
                outputFormat = BIN;
            }
            else
            {
                std::cerr << "Format non valide. Utilisez --format=ascii, --format=hex ou --format=bin." << std::endl;
                return 1;
            }
        }
    }
	
	
	
	
	// recuperation valeur en argument
	std::string valeur(argv[1]);
	std::string hexValueStr; // la valeur universel est hexadecimal
	switch (outputFormat)
    {
        case ASCII:
            hexValueStr = stringToHex(valeur);
			break;
        case HEX:
            hexValueStr = valeur;
			break;
        case BIN:
			hexValueStr = binaryToHex(valeur);
			break;
        default:
            hexValueStr = stringToHex(valeur);
    }
	std::string binaryValue = hexToBinary(hexValueStr);


    // affichage menu
	std::cout << "------------------------------------------------------------------------------------\n" << std::endl;
	std::cout << "     ######    ####   ########   ######  ##     ## ##          ###    ########      \n"
				 "    ##    ##    ##    ##     ## ##    ## ##     ## ##         ## ##   ##     ##     \n"
				 "    ##          ##    ##     ## ##       ##     ## ##        ##   ##  ##     ##     \n"
				 "    ##          ##    ########  ##       ##     ## ##       ##     ## ########      \n"
				 "    ##          ##    ##   ##   ##       ##     ## ##       ######### ##   ##       \n"
				 "    ##    ##    ##    ##    ##  ##    ## ##     ## ##       ##     ## ##    ##      \n"
				 "     ######    ####   ##     ##  ######   #######  ######## ##     ## ##     ##     \n"
				 "                                                                                  \n\n"
				 "########  #### ########   ######  ##    ## #### ####### ######## ######## ########  \n"
				 "##     ##  ##     ##     ##    ## ##    ##  ##  ##         ##    ##       ##     ## \n"
				 "##     ##  ##     ##     ##       ##    ##  ##  ##         ##    ##       ##     ## \n"
				 "########   ##     ##      ######  ########  ##  #####      ##    ######   ########  \n"
				 "##     ##  ##     ##           ## ##    ##  ##  ##         ##    ##       ##   ##   \n"
				 "##     ##  ##     ##     ##    ## ##    ##  ##  ##         ##    ##       ##    ##  \n"
				 "########  ####    ##      ######  ##    ## #### ##         ##    ######## ##     ## \n";
	std::cout << "\nBy teddyfresnes\n\n" << std::endl;
    std::cout << "Bienvenue dans le script Circular Bit Shifter" << std::endl;
    std::cout << "Value hex : " << hexValueStr << std::endl;
	std::cout << "Value ascii : " << hexToString(hexValueStr) << std::endl;
    std::cout << "Value binary : " << binaryValue << std::endl;
	std::cout << "------------------------------------------------------------------------------------\n" << std::endl;
	if (exportToFile)
		{std::cout << "\nExport option active, resultat dans output.txt\n\n" << std::endl;}
				

    // operation de decalage circulaire sur tout les blocs et tout les shifts possibles (Bruteforce 2≤B≤256, 1≤N<B)
    for (int blockSize=2; blockSize<=maxBlockSize; ++blockSize)
	{
		// si la taille du blocs depasse le nb de bits, on arrete
		if (blockSize > binaryValue.length())
		{
			std::cerr << "La taille du bloc binaire est superieur a la taille de la valeur binaire !" << std::endl;
			break;
		}
		
		
        for (int shift=1; shift<blockSize; ++shift)
		{
			// decalage vers la gauche à chaque occurence
			std::string shiftedBinaryValue = circularShift(binaryValue, blockSize, shift, shiftRight);
			// suppression des caractères NUL parasites
			size_t nullPos = shiftedBinaryValue.find("00000000");
			while (nullPos != std::string::npos) {
				shiftedBinaryValue.erase(nullPos, 8);
				nullPos = shiftedBinaryValue.find("00000000");
			}
			
			std::string shiftedAsciiValue;
			// parcoure les blocs de 8 bits
			for (size_t i=0; i<shiftedBinaryValue.length(); i+=8)
			{
				// extraction du bloc conversion et concatenation en ascii
				std::bitset<8> block(shiftedBinaryValue.substr(i, 8));
				shiftedAsciiValue += static_cast<char>(block.to_ulong());
			}

            // remplacement des sauts de ligne retour chariot et tabs par des espaces pour un affichage propre
			std::replace(shiftedAsciiValue.begin(), shiftedAsciiValue.end(), '\n', ' ');
			std::replace(shiftedAsciiValue.begin(), shiftedAsciiValue.end(), '\r', ' ');
			std::replace(shiftedAsciiValue.begin(), shiftedAsciiValue.end(), '\t', ' ');
			std::replace(shiftedAsciiValue.begin(), shiftedAsciiValue.end(), '\f', ' ');

            /* AFFICHAGE RESULTAT OCCURENCE */
			if (exportToFile)
			{

				// affichage ASCII
				outputFile << "[" << blockSize << "]+" << shift << " :    " << shiftedAsciiValue;

				if (displayHex) // affichage hex avec -h
				{
					outputFile << "    (" << stringToHex(shiftedAsciiValue) << ")";
				}
				if (displayDecimal) // affichage décimal avec -d
				{
					outputFile << "    (" << static_cast<int>(shiftedAsciiValue[0]) << ")";
				}
				if (displayBinary) // affichage binaire avec -b
				{
					outputFile << "\n" << shiftedBinaryValue;
				}
                if (displayAlphanumericCount) // affichage nb alphanumeric avec -i
                {
                    int alphanumericCount = countAlphanumeric(shiftedAsciiValue);
					outputFile << "    {" << alphanumericCount << " alphanumeric}";
                    maxAlphanumericCount = std::max(maxAlphanumericCount, alphanumericCount);

                }
				outputFile << std::endl;
			}
			else
			{
				// affichage ASCII
				std::cout << "[" << blockSize << "]+" << shift << " :    " << shiftedAsciiValue;

				if (displayHex) // affichage hex avec -h
				{
					std::cout << "    (" << stringToHex(shiftedAsciiValue) << ")";
				}
				if (displayDecimal) // affichage décimal avec -d
				{
					std::cout << "    (" << static_cast<int>(shiftedAsciiValue[0]) << ")";
				}
				if (displayBinary) // affichage binaire avec -b
				{
					std::cout << "\n" << shiftedBinaryValue;
				}
                if (displayAlphanumericCount) // affichage nb alphanumeric avec -i
                {
                    int alphanumericCount = countAlphanumeric(shiftedAsciiValue);
                    std::cout << "    {" << alphanumericCount << " alphanumeric}";
                    maxAlphanumericCount = std::max(maxAlphanumericCount, alphanumericCount);
                }
				std::cout << std::endl;
			}
        }
    }
	
    if (displayAlphanumericCount)
    {
        std::cout << "Maximum de char alphanumerique decouvert sur une occurence: " << maxAlphanumericCount << std::endl;
    }
	if (exportToFile)
	{
		outputFile.close();
	}
	std::cout << "END !" << std::endl;
	
    return 0;
}
