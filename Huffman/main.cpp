#include"compress.h"
#include<fstream>

int main() {
	/*������ ff;
	������ yy;
	ff.Сɵ��("��ŮͼƬ.jpg", "��ŮͼƬ.huff");
	yy.�󱿵�("��ŮͼƬ.huff", "��ŮͼƬ.jpg");*/
	char buffer[256];
	std::fstream in("words.txt");
    if (!in.is_open())
        { std::cout << "Error opening file"; exit(1); }
     while (!in.eof())
      {
         in.getline(buffer, 100);
         in << "wor*";
         std::cout << "aline"<<buffer<<std::endl;
       }
     in.close();
}