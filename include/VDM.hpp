#include <SFML/Graphics.hpp>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <iostream>
#include <limits>
#include <direct.h>
#include <filesystem>
#include "D:/VS Code Vuk/C++/SFMLUI/include/UI_Button.hpp"
#include "D:/VS Code Vuk/C++/SFMLUI/include/UI_TextBox.hpp"
#include "CyberFont.hpp"

namespace vui
{
/////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Simple data manpulator class for data reading and writing.
/////////////////////////////////////////////////////////////////////////////////////////////
class DataManipulator
{
public:

    /////////////////////////////////////////////////////////////////////////////////////
    /// @brief Reads binary data form file.
    /// @param filename Path to file.
    /// @return Returns std::vector of unsigned char type, if read is successful.
    /////////////////////////////////////////////////////////////////////////////////////
    std::vector<unsigned char> readData(const std::string& filename)
    {
        // Open the file
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open())
        {
            // Failed to open the file
            // You may want to handle this error in some way
            return std::vector<unsigned char>();
        }

        // Determine the file size and resize the vector to fit the data
        file.seekg(0, std::ios::end);
        std::vector<unsigned char> data(file.tellg());
        file.seekg(0, std::ios::beg);

        // Read the data into the vector
        file.read(reinterpret_cast<char*>(data.data()), data.size());

        return data;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Transforms binary data to HexValues.
    /// @param data Vector of unsigend char type that has data info.
    /// @return Returns a vector of unsigned char type but with cruched data in form of HexValues.
    //////////////////////////////////////////////////////////////////////////////////////////////////
    std::vector<unsigned char> DataToHexValues(const std::vector<unsigned char>& data)
    {
        std::vector<unsigned char> hexValues;
        for (unsigned char c : data)
        {
            unsigned char hi = c >> 4;
            unsigned char lo = c & 0x0F;
            hexValues.push_back(hi);
            hexValues.push_back(lo);
        }
        return hexValues;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Crates a .bin file in BIN folder in programs directory.
    /// @param FileName Name that will be given to the saved file.
    /// @param data Vector of unsigned char type that contains the data to be written.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    void createBIN(std::string FileName, std::vector<unsigned char> data)
    {
        std::ofstream ofs;
        ofs.open(("BIN/" + FileName + ".bin"));
        if(ofs.is_open())
        {
            for(auto c : data)
            {
                ofs << (c);
            }
        }
        ofs.close();
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Decodes a string containing data in form of hex values.
    /// @param hexString String containing data in form of hex values.
    /// @return Retruns the vector of unsigned char type containing decoded data. 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::vector<unsigned char> decodeHexString(const std::string& hexString)
    {
        std::vector<unsigned char> data;

        if (hexString.empty())
        {
            return data;
        }

        for (std::size_t i = 0; i < hexString.size(); i += 2)
        {
            //Get the two hexadecimal characters at the current position
            char c1 = hexString[i];
            char c2 = hexString[i + 1];

            //Convert the characters to integers
            int value1 = 0, value2 = 0;
            if (std::isxdigit(c1) && std::isxdigit(c2))
            {
                if (std::isdigit(c1))
                {
                    value1 = c1 - '0';
                }
                else
                {
                    value1 = std::tolower(c1) - 'a' + 10;
                }
                if (std::isdigit(c2))
                {
                    value2 = c2 - '0';
                }
                else
                {
                    value2 = std::tolower(c2) - 'a' + 10;
                }
            }
            else
            {
                // Skip invalid characters
                continue;
            }

            // Combine the two hexadecimal characters into a single byte
            unsigned char byte = (value1 << 4) | value2;
            data.push_back(byte);
        }
        return data;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Decodes a vector of unsigned char type containing data in form of hex values.
    /// @param HexValues Vector of unsigned char type containing data in form of hex values.
    /// @return Retruns the vector of unsigned char type containing decoded data. 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::vector<unsigned char> decodeHexValues(std::vector<char> HexValues)
    {
        std::vector<unsigned char> data;

        if(HexValues.empty())
        {
            return data;
        }

        for(std::size_t i = 0; i < HexValues.size(); i += 2)
        {
            //Get the two hexadecimal characters at the current position
            char c1 = HexValues[i];
            char c2 = HexValues[i + 1];

            //Convert the characters to integers
            int value1 = 0, value2 = 0;
            if (std::isxdigit(c1) && std::isxdigit(c2))
            {
                if (std::isdigit(c1))
                {
                    value1 = c1 - '0';
                }
                else
                {
                    value1 = std::tolower(c1) - 'a' + 10;
                }
                if (std::isdigit(c2))
                {
                    value2 = c2 - '0';
                }
                else
                {
                    value2 = std::tolower(c2) - 'a' + 10;
                }
            }
            else
            {
                // Skip invalid characters
                continue;
            }

            // Combine the two hexadecimal characters into a single byte
            unsigned char byte = (value1 << 4) | value2;
            data.push_back(byte);
        }
        return data;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Decodes a single hexadecimal number to binary information.
    /// @param hexNumber Single hexadecimal number.
    /// @return Retruns a decoded info in form of a byte.
    ////////////////////////////////////////////////////////////////////////////////////////////
    unsigned char decodeHexToByte(std::string hexNumber)
    {
        char c1 = hexNumber[0];
        char c2 = hexNumber[1];

        unsigned char byte;
        
        //Convert the characters to integers
        int value1 = 0, value2 = 0;
        if (std::isxdigit(c1) && std::isxdigit(c2))
        {
            if (std::isdigit(c1))
            {
            value1 = c1 - '0';
            }
            else
            {
                    value1 = std::tolower(c1) - 'a' + 10;
            }
            if (std::isdigit(c2))
            {
                value2 = c2 - '0';
            }
            else
            {
                value2 = std::tolower(c2) - 'a' + 10;
            }
            byte = (value1 << 4) | value2;
        }
        return byte;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a header file with a created class that contains the data. The data is saved in hex value form.
    /// @param headerName Name that will be given to the class and the file.
    /// @param data Data to be written to the file.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    void createHexDataHeader(std::string headerName, std::vector<unsigned char> data)
    {
        std::fstream fs;
        std::vector<unsigned char> hexValues = DataToHexValues(data);
        int arraySize = hexValues.size();
        fs.open(("Headers/" + headerName + ".hpp"), std::ios::out);
        
        //Create the header file that contains data information
        if(fs.is_open())
        {
            fs << "#include <string>\n";
            fs << "#include <vector>\n";
            fs << '\n';
            fs << "class " << headerName << '\n';
            fs << "{\n\n";
            fs << "public:\n";
            fs << "\n";
            fs << headerName << "(){}\n\n";
            fs << '~' << headerName << "(){}\n\n";
            fs << "std::vector<unsigned char> read()\n";
            fs << "{\n";
            fs << "\tstd::vector<unsigned char> data;\n";
            fs << "\tfor(int i = 0; i < Size; i += 2)\n";
            fs << "\t{\n";
            fs << "\t\tchar c1 = hexValues[i];\n";
            fs << "\t\tchar c2 = hexValues[i + 1];\n\n";
            fs << "\t\tunsigned char byte;\n\n";
            fs << "\t\tint value1 = 0, value2 = 0;\n";
            fs << "\t\tif(std::isxdigit(c1) && std::isxdigit(c2))\n";
            fs << "\t\t{\n";
            fs << "\t\t\tif(std::isdigit(c1))\n";
            fs << "\t\t\t{\n";
            fs << "\t\t\t\tvalue1 = c1 - '0';\n";
            fs << "\t\t\t}\n";
            fs << "\t\t\telse\n";
            fs << "\t\t\t{\n";
            fs << "\t\t\t\tvalue1 = std::tolower(c1) - 'a' + 10;\n";
            fs << "\t\t\t}\n";
            fs << "\t\t\t\tif(std::isdigit(c2))\n";
            fs << "\t\t\t{\n";
            fs << "\t\t\t\tvalue2 = c2 - '0';\n";
            fs << "\t\t\t}\n";
            fs << "\t\t\telse\n";
            fs << "\t\t\t{\n";
            fs << "\t\t\t\tvalue2 = std::tolower(c2) - 'a' + 10;\n";
            fs << "\t\t\t}\n";
            fs << "\t\t\tbyte = (value1 << 4) | value2;\n";
            fs << "\t\t}\n";
            fs << "\tdata.push_back(byte);\n";
            fs << "\t}\n";
            fs << "\treturn data;\n";
            fs << "}\n\n";
            fs << "private:\n\n";
            fs << "int Size = " << arraySize << ";\n";
            fs << "char hexValues[" << arraySize << "]" << "{";
            int i = 0;
            for(auto c: hexValues)
            {
                fs << std::hex  << "\'" << (int)c << "\',";
                i++;
            }
            fs << "};\n\n};";
            fs.close();
        }
    }
};

/// @brief Data manipulator object used in program.
inline DataManipulator FDM;

}