#include<iostream>
#include<vector>
using namespace std;

void hanoi(int, vector<int>*, vector<int>*, vector<int>*);

int main(){
    int num;
    cin >> num;
    vector<int> first(0), second(0), third(0);
    for (int i = 0; i < num; ++i)
        first.push_back(num -i);
    hanoi(num, &first, &second, &third);
    for (int i = 0; i < num; ++i)
        cout << third.at(i) << " ";
    cout << endl;
    return 0;
}

void hanoi(int n, vector<int> *first, vector<int> *second, vector<int> *third){
    if(n == 1){
        third->push_back(*(first->end()-1));
        first->erase(first->end()-1);
    }else{
        hanoi(n-1, first, third, second);
        hanoi(1, first, second, third);
        hanoi(n-1, second, first, third);
    }
}
