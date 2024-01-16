#include "HuffmanTree.h"

HuffmanNode::HuffmanNode(char ch, int freq, const NodePtr & left, const NodePtr & right) :
        _character(ch),
        _freq(freq),
        _left(left),
        _right(right)
{}

HuffmanTree::HuffmanTree(const std::map<unsigned char, int>& freqMap) {
    buildTree(freqMap);
}

HuffmanTree::NodePtr HuffmanTree::Root() const {
    return _root;
}

bool HuffmanTree::Comp::operator()(const HuffmanTree::NodePtr& l, const HuffmanTree::NodePtr& r)
{
    return l->_freq > r->_freq;
}

void HuffmanTree::buildTree(const std::map<unsigned char, int>& freqMap){
    std::priority_queue<NodePtr, Nodes, Comp> tree;

    for (const auto& pair: freqMap)
        tree.emplace(std::make_shared<Node>(pair.first, pair.second, nullptr, nullptr));

    while (tree.size() != 1)
    {
        const NodePtr left = tree.top();
        tree.pop();
        const NodePtr right = tree.top();
        tree.pop();

        int sum = left->_freq + right->_freq;
        tree.emplace(std::make_shared<Node>(0, sum, left, right));
    }
    _root = tree.top();
};