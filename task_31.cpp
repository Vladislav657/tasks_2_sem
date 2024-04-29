#include <iostream>

using namespace std;

class Sequence{
public:
    int *numbers;
    int size;

    Sequence(int *numbers, int size){
        this->numbers = new int [size];
        this->size = size;
        for (int i = 0; i < this->size; ++i) this->numbers[i] = numbers[i];
    }

    int digitsSum(int i) const{
        if (i < 0 || i >= this->size) throw range_error("Incorrect index");
        int n = abs(this->numbers[i]), result = 0;
        while (n > 0){
            result += n % 10;
            n /= 10;
        }
        return result;
    }

    int maxDigitsSumNumber() const{
        int currentNumber = this->numbers[0], currentSum = 0;
        for (int i = 0; i < this->size; ++i) {
            int sum = digitsSum(i);
            if (sum > currentSum || sum == currentSum && this->numbers[i] > currentNumber) {
                currentSum = sum;
                currentNumber = this->numbers[i];
            }
        }
        return currentNumber;
    }

    ~Sequence(){
        delete[] this->numbers;
    }
};

int main(){
    int n;
    cin >> n;
    int *input = new int [n];
    for (int i = 0; i < n; ++i) cin >> input[i];

    Sequence sequence = Sequence(input, n);
    cout << sequence.maxDigitsSumNumber();

    delete[] input;
    return 0;
}
