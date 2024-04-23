#include "HuffmanCoding.h"

HuffmanCoding::Node::Node() :
    m_symbols(Set()), m_frequency(0),
    m_left(nullptr), m_right(nullptr) {}

HuffmanCoding::Node::Node(unsigned char symbol, int frequency) :
    m_symbols(Set(symbol)), m_frequency(frequency),
    m_left(nullptr), m_right(nullptr) {}

HuffmanCoding::Node::Node(HuffmanCoding::Node* left, HuffmanCoding::Node* right) :
    m_symbols(left->m_symbols | right->m_symbols),
    m_frequency(left->m_frequency + right->m_frequency),
    m_left(left), m_right(right) {}

Set HuffmanCoding::Node::GetSymbols() {
    return m_symbols;
}

int HuffmanCoding::Node::GetFrequency() {
    return m_frequency;
}

HuffmanCoding::Node* HuffmanCoding::Node::GetLeft() const {
    return m_left;
}

HuffmanCoding::Node* HuffmanCoding::Node::GetRight() const {
    return m_right;
}

HuffmanCoding::HuffmanCoding() : m_root(nullptr) {}

HuffmanCoding::~HuffmanCoding() {
    DeleteRoot(m_root);
}

void HuffmanCoding::BuildHuffmanTree(const std::string& inputFile) {
    DeleteRoot(m_root);

    std::ifstream text(inputFile);
    if (!text) {
        std::cerr << "Error opening files." << std::endl;
    }

    int frequencies[256];
    for (int i = 0; i < 256; i++) {
        frequencies[i] = 0;
    }

    char huffmanChar;
    while (text.get(huffmanChar)) {
        frequencies[(unsigned char)huffmanChar]++;
    }

    text.close();

    std::vector<Node*> nodes;

    for (int i = 0; i < 256; i++) {
        if (frequencies[i] != 0) {
            Node* temp = new Node((unsigned char)i, frequencies[i]);

            nodes.push_back(temp);
        }
    }

    std::sort(nodes.begin(), nodes.end(), [](Node* leftNode, Node* rightNode) {
        return leftNode->GetFrequency() < rightNode->GetFrequency();
        });

    while (nodes.size() > 1) {
        Node* temp = new Node(nodes[0], nodes[1]);

        nodes.erase(nodes.begin());
        nodes.erase(nodes.begin());
        nodes.push_back(temp);

        std::sort(nodes.begin(), nodes.end(), [](Node* leftNode, Node* rightNode) {
            return leftNode->GetFrequency() < rightNode->GetFrequency();
            });
    }

    m_root = nodes[0];
}

double HuffmanCoding::EncodeHuffmanTree(const std::string& inputFile, const std::string& outputFile) {
    BuildHuffmanTree(inputFile);

    std::ifstream input(inputFile);
    std::ofstream output(outputFile);

    if (!input || !output) {
        std::cerr << "Error opening files." << std::endl;

        return -1;
    }

    if (m_root == nullptr) {
        return 0;
    }

    int result_count_of_bits = 0;
    int input_count_of_bits = 0;

    char huffmanChar;
    while (input.get(huffmanChar)) {
        Node* temp = m_root;

        while (temp->GetLeft() != nullptr && temp->GetRight() != nullptr) {
            if (temp->GetLeft()->GetSymbols().ContainsSymbol(huffmanChar)) {
                temp = temp->GetLeft();

                output << '0';
            } else {
                temp = temp->GetRight();

                output << '1';
            }

            result_count_of_bits++;
        }

        input_count_of_bits++;
    }

    if (m_root->GetLeft() == nullptr && m_root->GetRight() == nullptr) {
        for (int i = 0; i < input_count_of_bits; i++) {
            output << '1';
        }

        result_count_of_bits = input_count_of_bits;
    }

    input.close();
    output.close();

    return (double) result_count_of_bits / ((double) input_count_of_bits * 8);
}

bool HuffmanCoding::DecodeHuffmanTree(const std::string& inputFile, const std::string& outputFile) {
    if (m_root == nullptr) {
        return false;
    }

    std::ifstream input(inputFile);
    std::ofstream output(outputFile);

    if (!input || !output) {
        std::cerr << "Error opening files." << std::endl;

        return false;
    }

    char huffmanChar;
    Node* temp = m_root;

    while (input.get(huffmanChar)) {
        switch (huffmanChar) {
        case '0':
            if (temp->GetLeft() != nullptr) {
                temp = temp->GetLeft();
            }

            break;

        case '1':
            if (temp->GetRight() != nullptr) {
                temp = temp->GetRight();
            }

            break;

        default:
            return false;
        }

        if (temp->GetLeft() == nullptr && temp->GetRight() == nullptr) {
            output << temp->GetSymbols();
            temp = m_root;
        }
    }

    input.close();
    output.close();

    return true;
}

void HuffmanCoding::DeleteRoot(HuffmanCoding::Node* root) {
    if (root != nullptr) {
        DeleteRoot(root->GetLeft());
        DeleteRoot(root->GetRight());

        delete root;
    }
}