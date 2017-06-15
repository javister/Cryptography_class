#include "imports.h"
Foper file;
Foper outfile;
int main()
{
    EntropyCounter ec;
    std::cout << "plaintext:\n";
    ec.count("file.txt",1);
    ec.count("file.txt",2);
    ec.count("file.txt",4);
    ec.count("file.txt",8);
    std::cout << "ciphertext (rsa, random public key):\n";
    RSAclass rsac;
    rsac.Encrypt("file.txt", "Cfile.txt", "public.pem");
    ec.count("Cfile.txt", 1);
    ec.count("Cfile.txt", 2);
    ec.count("Cfile.txt", 4);
    ec.count("Cfile.txt", 8);
    std::cout << "hash file (md5):\n";//hashed separately
    md5class instance;
    if (!file.open((string)"file.txt"))return 1;
    std::vector<unsigned char> hash = instance.Hash(file.GetData(), 32, 32);
    outfile.GetData() = hash;
    outfile.write((string)"Hfile.txt");
    ec.count("Hfile.txt", 1);
    ec.count("Hfile.txt", 2);
    ec.count("Hfile.txt", 4);
    ec.count("Hfile.txt", 8);
    std::cout << "hash file (RH hash function):\n";
    string input = "file.txt";
    if (!file.open(input))return 1;
    string output= "hafile.txt";
    setBlockLength(32);
    setOutputSize(32);
    hash = Hash(file.GetData());
    outfile.GetData() = hash;
    outfile.write(output);
    ec.count("hafile.txt", 1);
    ec.count("hafile.txt", 2);
    ec.count("hafile.txt", 4);
    ec.count("hafile.txt", 8);
    system("pause");
    return 0;
}