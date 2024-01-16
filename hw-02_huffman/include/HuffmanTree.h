#ifndef HUFFMAN_HUFFMANTREE_H
#define HUFFMAN_HUFFMANTREE_H

#include <memory>
#include <map>
#include <queue>

struct HuffmanNode {
    using NodePtr = std::shared_ptr<HuffmanNode>;
    HuffmanNode(char ch, int freq, const NodePtr & left = nullptr, const NodePtr & right = nullptr);

    char _character;
    int _freq;
    std::shared_ptr<HuffmanNode> _left;
    std::shared_ptr<HuffmanNode> _right;
};

class HuffmanTree {

public:

    using Node = HuffmanNode;
    using NodePtr = Node::NodePtr;
    using Nodes = std::vector<NodePtr>;

    HuffmanTree(const std::map<unsigned char, int>& freqMap);

    NodePtr Root() const;

private:

    struct Comp
    {
        bool operator()(const NodePtr& l, const NodePtr& r);
    };

    void buildTree(const std::map<unsigned char, int>& freqMap);

private:
    NodePtr _root;
};

#endif //HUFFMAN_HUFFMANTREE_H
