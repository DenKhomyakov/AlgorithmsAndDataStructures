#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Set.h"

class HuffmanCoding {
public:
    class Node;

    HuffmanCoding();
    ~HuffmanCoding();

    void BuildHuffmanTree(const std::string& inputFile);
    double EncodeHuffmanTree(const std::string& inputFile, const std::string& outputFile);
    bool DecodeHuffmanTree(const std::string& inputFile, const std::string& outputFile);

private:
    Node* m_root = nullptr;
    void DeleteRoot(Node* root);
};

class HuffmanCoding::Node {
public:
    Node();
    Node(unsigned char symbol, int frequency);
    Node(Node* left, Node* right);

    ~Node() = default;

    Set GetSymbols();
    int GetFrequency();

    Node* GetLeft() const;
    Node* GetRight() const;

private:
    Set m_symbols;
    int m_frequency;
    Node* m_left;
    Node* m_right;
};
