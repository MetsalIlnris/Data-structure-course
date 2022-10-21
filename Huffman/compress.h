#pragma once
#include<string>
#include<map>
#include"HuffmanTree.h"
#define ������ huffEncode
#define ������ huffDecode
#define Сɵ�� encode
#define �󱿵� decode

//�õ�indexλ��ֵ����indexλΪ0����GET_BYTEֵΪ�٣�����Ϊ��
#define GET_BYTE(vbyte, index) (((vbyte) & (1 << ((index) ^ 7))) != 0)
//indexλ��1
#define SET_BYTE(vbyte, index) ((vbyte) |= (1 << ((index) ^ 7)))
//indexλ��0
#define CLR_BYTE(vbyte, index) ((vbyte) &= (~(1 << ((index) ^ 7))))

using uchar = unsigned char;

struct fileHead {
    char flag[4];                //ѹ���������ļ�ͷ����־huff
    int alphaVariety;            //�ַ�������
    uchar lastValidBit;            //���һ���ֽڵ���Чλ��
    char unused[10];            //���ÿռ�
};                                //����ṹ���ܹ�ռ��16���ֽڵĿռ�

struct alphaFreq {
    uchar alpha;                //�ַ�,���ǵ��ļ����к��֣����Զ����uchar
    int freq;                    //�ַ����ֵ�Ƶ��
    alphaFreq() {}
    alphaFreq(const std::pair<char, int>& x)
        : alpha(x.first), freq(x.second) {}
};

class huffEncode {
public:
    bool encode(const char* srcFilename, const char* destFilename);
private:
    int _getLastValidBit();
    bool _getAlphaFreq(const char* filename);
    bool _encode(const char* srcFilename, const char* destFilename);
private:
    std::map<uchar, int> _afMap;
    std::map<uchar, std::string> _codeMap;
};

class huffDecode {
public:
    huffDecode() : _fileHead(nullptr), _htree(nullptr) {
        _fileHead = new fileHead();
    }
    ~huffDecode() {
        if (!_fileHead) delete _fileHead;
        if (!_htree) delete _htree;
    }
private:
    static bool _isLeaf(huffNode<uchar>* n) {
        return n->left == nullptr && n->right == nullptr;
    }//�ж��Ƿ�ΪҶ�ӽڵ�
    long _getFileSize(const char* strFileName);
    bool _getAlphaFreq(const char* filename);
    bool _decode(const char* srcFilename,
        const char* destFilename);
public:
    bool decode(const char* srcFilename, const char* destFilename);
private:
    fileHead* _fileHead;
    huffTree<uchar> * _htree;
    std::map<uchar, int> _afMap;
    std::map<uchar, std::string> _codeMap;
    std::map<std::string, uchar> _decodeMap;
};