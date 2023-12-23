#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

bool match(string text){
    return text.size() == 3;
}

int countStrings(vector<string>& texts, bool (*pMatch)(string)){
    int count{0};
    for(auto text: texts){
        if(pMatch(text)){
            count++;
        }
    }
    return count;
}

int main(){
    vector<string> texts;
    texts.push_back("one");
    texts.push_back("two");
    texts.push_back("three");
    texts.push_back("four");
    texts.push_back("one");
    texts.push_back("two");
    texts.push_back("three");
    texts.push_back("one");

    cout << count_if(texts.begin(), texts.end(), match) << endl;
    cout << countStrings(texts, match) << endl;

    return 0;
}