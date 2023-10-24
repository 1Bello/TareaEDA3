#include <bits/stdc++.h>
#include<string>
using namespace std;

int impo(char c){
    if(c == '^')
        return 3;
    if(c == '*' || c == '/')
        return 2;
    if (c == '+' || c == '-')
        return 1;
    else 
        return 0;
}

void InfixtoPostfix(string s){
    stack<char> stck;
    string result;

    for (int i = 0; i < s.length(); i++){
        char c = s[i];

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
            result += c;
        else if (c == '(')
            stck.push(c);
        else if (c == ')'){
            while(stck.top() != '('){
                result += stck.top();
                stck.pop();
            }
            stck.pop();
        }
        else{
            while(!stck.empty() && impo(s[i]) <= impo(stck.top())){
                result += stck.top();
                stck.pop();
            }
            stck.push(c);
        }

    }

    while(!stck.empty()){
        result += stck.top();
        stck.pop();
    }
    cout << result << endl;
}

int main(){

    string ec = "";

    InfixtoPostfix(ec);

    return 0;
}