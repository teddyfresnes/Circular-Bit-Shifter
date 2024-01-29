#include <iostream>
#include <iomanip>
#include <sstream>
#include <bitset>
#include <algorithm>




// décalage circulaire vers la gauche sur chaque bloc de bits
std::string circularShift(const std::string& binaryValue, int blockSize, int shift)
{
	const int bitSize = 8 * sizeof(unsigned long long);
    std::string result;
    for (size_t i = 0; i < binaryValue.length(); i+=blockSize)
	{
        std::bitset<32> block(binaryValue.substr(i, blockSize));
        block = (block<<shift) | (block>>(blockSize-shift));
        result += block.to_string().substr(32-blockSize);
    }
    return result;
}




int main(int argc, char* argv[])
{
    if (argc < 2)
	{
        std::cerr<<"Utilisation: "<<argv[0]<<" <valeur_hex> [-b] [-h] [-d]"<<std::endl;
        return 1;
    }


    bool displayBinary = false;
    bool displayHex = false;
    bool displayDecimal = false;


    // check arguments
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
    }


    // recuperation valeur en argument
    std::string hexValueStr(argv[1]);
    std::stringstream ss;
    ss << std::hex << hexValueStr;
    unsigned int hexValue;
    ss >> hexValue;


    // conversion binaire
	std::string binaryValue;
    for (size_t i=0; i<hexValueStr.length(); i+=2)
	{
        std::string byteStr = hexValueStr.substr(i, 2);
        char byte = static_cast<char>(std::stoi(byteStr, nullptr, 16));
        binaryValue += std::bitset<8>(byte).to_string();
    }


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
	std::cout << "Value ascii : " << static_cast<char>(hexValue) << std::endl;
    std::cout << "Value binary : " << binaryValue << std::endl;
	std::cout << "------------------------------------------------------------------------------------\n" << std::endl;


    // operation de decalage circulaire sur tout les blocs et tout les shifts possibles (Bruteforce 2≤B≤32, 1≤N<B)
    for (int blockSize=2; blockSize<=32; ++blockSize)
	{
		// si la taille du blocs depasse le nb de bits, on arrete
		if (blockSize > binaryValue.length())
		{
			std::cerr << "La taille du bloc binaire est supérieur à la taille de la valeur binaire !" << std::endl;
			break;
		}
		
		
        for (int shift=1; shift<blockSize; ++shift)
		{
			// decalage vers la gauche à chaque occurence
			std::string shiftedBinaryValue = circularShift(binaryValue, blockSize, shift);
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

            // affichage ASCII
            std::cout << "[" << blockSize << "]+ " << shift << " :	" << shiftedAsciiValue;

            
            if (displayHex) // affichage hex avec -h
			{
                std::cout << "    (" << hexValueStr << ")";
            }
            if (displayDecimal) // affichage décimal avec -d
			{
                std::cout << "    (" << static_cast<int>(shiftedAsciiValue[0]) << ")";
            }
            if (displayBinary) // affichage binaire avec -b
			{
                std::cout << std::endl << "" << shiftedBinaryValue;
            }
			std::cout << std::endl;
        }
    }
	
	std::cout << "END !" << std::endl;
	
    return 0;
}
