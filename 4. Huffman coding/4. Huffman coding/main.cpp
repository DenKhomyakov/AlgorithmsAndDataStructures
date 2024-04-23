#include "HuffmanCoding.h"

int main() {
    HuffmanCoding huffman;

    std::string inputFile = "input.txt";
    std::string encodedFile = "encoded.txt";
    std::string decodedFile = "decoded.txt";

    double compressionRatio = huffman.EncodeHuffmanTree(inputFile, encodedFile);
    std::cout << "Compression ratio: " << compressionRatio << std::endl;

    bool success = huffman.DecodeHuffmanTree(encodedFile, decodedFile);

    if (!success) {
        std::cout << "Decoding failed." << std::endl;
    }

    return 0;
}