#include <cctype>
#include "huffmanNode.h"
#include "huffmanUtil.h"

static void printHuffmanNode(ostream& out, const HuffmanNode& node, bool showAddress = false);

HuffmanNode::HuffmanNode(int character, int count, HuffmanNode* zero, HuffmanNode* one) {
    this->character = character;
    this->count = count;
    this->zero = zero;
    this->one = one;
}

//Copy constructor
HuffmanNode::HuffmanNode(const HuffmanNode& other):zero(NULL), one(NULL), character(other.character), count(other.count) {
    if(other.zero != NULL) {
	zero = new HuffmanNode(other.zero);
    }
    if(other.one != NULL) {
        one = new HuffmanNode(other.one);
    }
}

//Overloading assignment operator
HuffmanNode& HuffmanNode::operator=(HuffmanNode other) {
    other.swap(*this);
    return *this;
}

//Destructor
Huffman::~HuffmanNode() {
    delete zero;
    delete one;
}

bool HuffmanNode::isLeaf() const {
    return zero == NULL && one == NULL;
}

string HuffmanNode::toString() const {
    ostringstream out;
    out << *this;
    return out.str();
}

void printSideways(HuffmanNode* node, bool showAddresses, string indent) {
    if (node != NULL) {
        printSideways(node->one, showAddresses, indent + "  ");
        cout << indent;
        printHuffmanNode(cout, *node, showAddresses);
        cout << endl;
        printSideways(node->zero, showAddresses, indent + "  ");
    }
}

ostream& operator <<(ostream& out, const HuffmanNode& node) {
    printHuffmanNode(out, node, false);
    return out;
}

static void printHuffmanNode(ostream& out, const HuffmanNode& node, bool showAddress) {
    if (showAddress) {
        out << "@" << &node;
    }
    out << "{";

    if (node.character == NOT_A_CHAR) {
        out << "NOT, ";
    } else {
        out << toPrintableChar(node.character)
            << " (" << node.character << "), ";
    }
    out << "count=" << node.count;

    if (showAddress) {
        if (node.zero == NULL) {
            out << ", zero=NULL";
        } else {
            out << ", zero=" << node.zero;
        }
        if (node.one == NULL) {
            out << ", one=NULL";
        } else {
            out << ", one=" << node.one;
        }
    }
    out << "}";
}
