#include <iostream>

using namespace std;

class String{
public:
    char *str;
    int size;

    explicit String(string str){
        this->str = new char [str.size()];
        this->size = (int)str.size();
        for (int i = 0; i < this->size; ++i) this->str[i] = str[i];
    }

    void reverse(int i, int j){
        i = i - 1;
        j = j - 1;
        if (i > j || i < 0 || j >= this->size) throw range_error("Incorrect indices");
        int k = 0;
        char change;
        while (i + k < j - k){
            change = this->str[i + k];
            this->str[i + k] = this->str[j - k];
            this->str[j - k] = change;
            k++;
        }
    }

    friend ostream& operator << (ostream& out, String& str);

    ~String(){
        delete[] this->str;
    }
};

ostream &operator<<(ostream &out, String& str) {
    for (int i = 0; i < str.size; ++i) out << str.str[i];
    return out;
}

int main(){
    int i, j;
    string str;
    cin >> str >> i >> j;

    String s = String(str);
    s.reverse(i, j);
    cout << s;

    return 0;
}
