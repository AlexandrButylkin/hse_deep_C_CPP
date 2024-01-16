#include "Archiver.h"
#include <iostream>

Request::Request(std::istream& is, std::ostream& os) :
    _is(is),
    _os(os)
{}

size_t Request::SizeEncoded() const {
    return _encodedData.Size() / 8;
}

size_t Request::SizeDecoded() const {
    return _decodedData.size();
}

size_t Request::SizeAdditional() const {
    return sizeof(int) + sizeof(unsigned char) + _info.freqMap.size() * (sizeof(unsigned char) + sizeof(int));
}

EncodeRequest::EncodeRequest(std::istream& is, std::ostream& os) :
    Request(is, os)
{}

void EncodeRequest::Read() {
    if(_is){
        std::copy(std::istreambuf_iterator<char>(_is), std::istreambuf_iterator<char>(),std::back_inserter(_decodedData));
    }
    initFreqMap();
}

void EncodeRequest::Write() const {
    if(_os) {

        char byte;

        int mapSize = _info.count;
        _os.write(reinterpret_cast<char*>(&mapSize), sizeof(int));
        for(auto pair : _info.freqMap){
            byte = pair.first;
            _os.write(&byte, sizeof(char));
            _os.write(reinterpret_cast<char*>(&pair.second), sizeof(int));
        }
        byte = static_cast<char>(_info.excessBytes);
        _os.write(&byte, sizeof(char));

        auto iter = _encodedData.cbegin();
        while(iter != _encodedData.cend()){
            auto res = _encodedData.GetByte(iter);
            _os << res.first;
            iter = res.second;
        }
    }
}

void EncodeRequest::Process() {
    if(!_decodedData.empty()) {
        HuffmanTree tree(_info.freqMap);

        std::map<unsigned char, Bitset> codeMap;
        encode(tree.Root(), Bitset(), codeMap);

        for(auto ch : _decodedData){
            Bitset bs = codeMap[ch];
            _encodedData.Push(bs.begin(), bs.end());
        }
        _info.excessBytes = _encodedData.Size() % 8 == 0 ? 0 : 8 - _encodedData.Size() % 8;
    }
}

void EncodeRequest::PrintMetadata() const {
    std::cout << SizeDecoded() << std::endl;
    std::cout << SizeEncoded() << std::endl;
    std::cout << SizeAdditional() << std::endl;
}

void EncodeRequest::initFreqMap() {
    for(auto ch : _decodedData){
        _info.freqMap[ch]++;
    }
    _info.count = static_cast<int>(_info.freqMap.size());
}

void EncodeRequest::encode(const NodePtr& root, Bitset code, std::map<unsigned char, Bitset> &codeMap){
    if(!root)
        return;

    if (!root->_left && !root->_right) {
        codeMap[root->_character] = code.Empty() ? code + false : code;
    }

    encode(root->_left, code + false, codeMap);
    encode(root->_right, code + true, codeMap);
}

DecodeRequest::DecodeRequest(std::istream& is, std::ostream& os) :
    Request(is, os)
{}

void DecodeRequest::Read() {
    if(_is) {

        char byte;

        int mapSize = 0;
        _is.read(reinterpret_cast<char*>(&mapSize), sizeof(int));
        _info.count = mapSize;

        long long elemSize = sizeof(char) + sizeof(int);
        long long size = _info.count * elemSize;
        char* bytes = new char[size];

        _is.read(bytes, size);
        for (int i = 0; i < _info.count; ++i) {
            auto ch = static_cast<unsigned char>(*(bytes + elemSize * i));
            auto freq = *reinterpret_cast<int*>(bytes + elemSize * i + 1);
            _info.freqMap[ch] = freq;
        }

        delete[] bytes;

        _is.read(&byte, sizeof(char));
        _info.excessBytes = static_cast<unsigned char>(byte);

        std::string str;
        std::copy(std::istreambuf_iterator<char>(_is), std::istreambuf_iterator<char>(),std::back_inserter(str));
        for(auto ch : str)
            _encodedData.Push(Bitset(ch));
    }
}

void DecodeRequest::Process() {
    if(!_encodedData.Empty()) {
        HuffmanTree tree(_info.freqMap);

        int index = -1;
        while(index < _encodedData.Size() - (1 + _info.excessBytes))
            decode(tree.Root(), index, _encodedData, _decodedData);
    }
};

void DecodeRequest::Write() const {
    if(_os)
        _os << _decodedData;
}

void DecodeRequest::PrintMetadata() const {
    std::cout << SizeEncoded() << std::endl;
    std::cout << SizeDecoded() << std::endl;
    std::cout << SizeAdditional() << std::endl;
}

void DecodeRequest::decode(NodePtr root, int &index, const Bitset& code, std::string& str) {
    if (!root)
        return;

    if (!root->_left && !root->_right)
    {
        str.push_back(root->_character);
        if(_info.freqMap.size() == 1)
            ++index;
        return;
    }
    else {
        ++index;
    }

    if (code[index] == 1)
        decode(root->_right, index, code, str);
    else
        decode(root->_left, index, code, str);
}