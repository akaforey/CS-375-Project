#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

int main(int argc, char *argv[])
{

    unordered_map<char, int> text;
    char letter;
    unsigned long long num_letters = 0;

    //Usage: ./huffman <input file name>
    ifstream in_file(argv[1]);
    if (!in_file.is_open()) {
        exit(1);
    }

    while (in_file.get(letter)) {
        text[letter]++;
        num_letters++;
    }
    for (const auto &i : text) {
        cout << i.first << " " << i.second << endl;
    }

    //Min heap and Queue code would go here:


    in_file.close();
    return 0;
}