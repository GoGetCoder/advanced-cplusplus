#include<iostream>
#include<functional>
#include<vector>
#include<algorithm>

using namespace std;

bool check(string& test){
    return test.size() == 3;
}

class Check{
public:
    bool operator()(string& test){
        return test.size() == 5;
    }
}check1;

void run(function<bool(string&)> check){
    string test = "three";
    cout << check(test) << endl;
}

int main(){
    int size = 5;
    vector<string> vec{"one", "two", "three"};

    // passing 'lambda' to count_if
    auto lambda = [size](string test){ return test.size() == size;};
    cout << count_if(vec.begin(), vec.end(), lambda) << endl;

    // passing 'function pointer' to count_if
    cout << count_if(vec.begin(), vec.end(), check) << endl;

    // passing 'functor' to count_if
    cout << count_if(vec.begin(), vec.end(), check1) << endl;

    run(lambda);
    run(check1);
    run(check);
    return 0;
}
