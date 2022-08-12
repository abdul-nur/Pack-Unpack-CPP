// CSC237 Project2: Text Packing / Unpacking Operations
// Student: Abdullahi Nur
// Due Date: 07/14/22
// Description:
// This program reads a text document, “packs” the ASCII characters
// from that document into unsigned int variables, and outputs those variables
// to another text file, formatted as hexadecimal numbers.
// This program also reverses the process, converting the unsigned int numbers
// back into a copy of the original text document.
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;


void hCommand(){
    /*
    Help Command - prints out user options
    No paramaeters
    */
    cout << "p      Build Packed Data File." << endl;
    cout << "u      Create unpacked (text) data from packed data." << endl;
    cout << "h      Print this help text." << endl;
    cout << "q      Quit (exit) the program." << endl;
    cout << "v      Set or Clear verboseMode (debug aid)." << endl;

}

bool qCommand(){
    /*
    Quit Command - Closes program
    No paramaeters
    */
    char userResponse;
    cout << "Are you sure that you want to exit the program? ";
    cin >> userResponse;
    if (userResponse == 'y'){
        cout << "Exit the program." << endl;
        return true;
    }
    return false;
}

void pCommand(){
    /*
    Pack Command - Packs groups of 4 characters into a unsigned int
    No paramaeters
    */
    unsigned int pack1 = 0;
    
    string inputFileName, outputFileName;
    cout << "Enter the input filename: ";
    cin >> inputFileName;
    cout << "Enter the output filename: ";
    cin >> outputFileName;

    ifstream inputFile; // Input file stream object
    inputFile.open(inputFileName);

    ofstream outputFile; // Output file stream object
    outputFile.open(outputFileName);
    

    const int values_SIZE = 50;
    string values[values_SIZE];
   
    string fullLineFromFile;
    int count = 0;    //amt of lines in input file
    while (count < values_SIZE && getline(inputFile,values[count])) {
        fullLineFromFile = values[count];
        fullLineFromFile = fullLineFromFile + "\n";

        //Gets length of each line in the file
        cout << "Input text (length " << fullLineFromFile.length() - 1 << "): " << fullLineFromFile << endl;
        int charCount = 0;

        //counts in intervals of 4 until each line is separated into groups of 4
        while(charCount < fullLineFromFile.length()){

            //substring of current 4 characters
            string currentFourChars = fullLineFromFile.substr(charCount, 4);

            if(currentFourChars.length() < 4){
                currentFourChars += '\0';
            }
            //cout << "(line " << __LINE__ << "): length=" << currentFourChars.length() << " currentFourChars = [" << currentFourChars << "] "<< endl;   // pmorgan
            pack1 |= ((unsigned char) currentFourChars[0] << 24 );
            pack1 |= ((unsigned char)currentFourChars[1] << 16 );
            pack1 |= ((unsigned char)currentFourChars[2] <<  8 );
            pack1 |= ((unsigned char)currentFourChars[3]);

            outputFile << hex << pack1 << endl;
            pack1 = 0;
            charCount +=4;
        }
        count++; //iterates to next line in output file
    }
    inputFile.close();

    pack1 = 0;

}

void uCommand(){
    /*
    Unpack Command - unpacks unsigned ints into groups of 4 characters
    No paramaeters
    */
    string inputFileName, outputFileName;
    cout << "Enter the input filename: ";
    cin >> inputFileName;
    cout << "Enter the output filename: ";
    cin >> outputFileName;

    ifstream inputFile; // Input file stream object
    inputFile.open(inputFileName);

    ofstream outputFile; // Output file stream object
    outputFile.open(outputFileName);


    //Defines array size
    const int values_SIZE = 50;
    string values[values_SIZE];


    //feeds input file content into array
    int count = 0;
    while (count < values_SIZE && getline(inputFile, values[count])) {
        //char letter1 = (values[count] & 0xFF000000) >> 24;
        std::string s = values[count];
 
        //turns hex number into int string
        unsigned int sum;
        std::istringstream ssObject(s);
        ssObject >> std::hex >> sum;
    
        //std::cout << sum << std::endl;    // 1000

        //shifts bits of int back into original characters
        char firstChar = (sum & 0xFF000000) >> 24;
        char secondChar = (sum & 0x00FF0000) >> 16;
        char thirdChar = (sum & 0x0000FF00) >> 8;
        char fourthChar = (sum & 0x000000FF);
        if (firstChar != 0) outputFile<<firstChar;
        if (secondChar != 0) outputFile<<secondChar;
        if (thirdChar != 0) outputFile<<thirdChar;
        if (fourthChar != 0) outputFile<<fourthChar;


        //cout << values[count] << endl;

    }
}

int main(){
    /*Main Function*/

    bool keepRunning = true; //always true so function will always repeat until quit command is run
    while (keepRunning){
        char userCommandInput;
        cout << "Command: ";
        cin >> userCommandInput;

        if (userCommandInput == 'h'){
            hCommand();
        }else if( userCommandInput == 'q' && qCommand()){
            break;

        }else if( userCommandInput == 'p'){
            pCommand();

        }else if( userCommandInput == 'u'){
            uCommand();

        }
       

    }

    return 0;
}

