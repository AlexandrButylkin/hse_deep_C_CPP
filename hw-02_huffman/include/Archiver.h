#ifndef HUFFMAN_ARCHIVER_H
#define HUFFMAN_ARCHIVER_H

#include <map>
#include <fstream>

#include "Bitset.h"
#include "HuffmanTree.h"

class Request {
public:
    Request(std::istream & inPath, std::ostream& outPath);

    virtual void Read() = 0;
    virtual void Write() const = 0;
    virtual void Process() = 0;
    virtual void PrintMetadata() const = 0;

    virtual ~Request() = default;

    size_t SizeEncoded() const;
    size_t SizeDecoded() const;
    size_t SizeAdditional() const;

protected:

    struct AdditionalInfo{
        int count = 0;
        std::map<unsigned char, int> freqMap;
        unsigned char excessBytes = 0;
    };

protected:
    std::istream& _is;
    std::ostream& _os;

    std::string _decodedData;
    Bitset _encodedData;

    AdditionalInfo _info;
};

class EncodeRequest : public Request {
public:
    EncodeRequest(std::istream & inPath, std::ostream& outPath);

    void Read() override;
    void Write() const override;
    void Process() override;
    void PrintMetadata() const override;
private:

    void initFreqMap();

    using Node = HuffmanNode;
    using NodePtr = std::shared_ptr<Node>;

    void encode(const NodePtr& root, Bitset code, std::map<unsigned char, Bitset> &codeMap);
};

class DecodeRequest : public Request {
public:
    DecodeRequest(std::istream & inPath, std::ostream& outPath);

    void Read() override;
    void Process() override;
    void Write() const override;
    void PrintMetadata() const override;

private:

    using Node = HuffmanNode;
    using NodePtr = std::shared_ptr<Node>;
    void decode(NodePtr root, int &index, const Bitset& code, std::string& str);
};


#endif //HUFFMAN_ARCHIVER_H
