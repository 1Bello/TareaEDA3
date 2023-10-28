#include <bits/stdc++.h>
#include "abb.hpp"
using namespace std;

int impo(char c) {
    if (c == '^')
        return 3;
    if (c == '*' || c == '/')
        return 2;
    if (c == '+' || c == '-')
        return 1;
    else
        return 0;
}

int isop(char c){
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') return 1;
    else return 0;
}

int isnum(string s){
    for(const char& c : s){
        if (!isdigit(c)) return 0;
    }
    return 1;
}

int isvar(string s){
    for(const char& c : s){
        if (!isalpha(c)) return 0;
    }
    return 1;
}

int ans;
void InfixtoPostfix(string s, vector<string>& postfix) {
    stack<char> stck;
    string num;

    for (int i = 0; i < s.length(); i++) {
        char c = s[i];

        if (c == ' ') {
            continue;
        }

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || isdigit(c)) {
            num += c; 
        } else {
            if (!num.empty()) {
                postfix.push_back(num);
                num.clear();
            }

            if (c == '(')
                stck.push(c);
            else if (c == ')') {
                while (stck.top() != '(') {
                    postfix.push_back(string(1, stck.top()));
                    stck.pop();
                }
                stck.pop();
            } else {
                while (!stck.empty() && impo(s[i]) <= impo(stck.top())) {
                    postfix.push_back(string(1, stck.top()));
                    stck.pop();
                }
                stck.push(c);
            }
        }
    }

    if (!num.empty()) {
        postfix.push_back(num);
    }

    while (!stck.empty()) {
        postfix.push_back(string(1, stck.top()));
        stck.pop();
    }

    num.clear();
}

float evaluatePostfix(const vector<string>& postfix, map<string, float>& variables) {
    stack<float> st;
    
    for (const string& token : postfix) {
        if (isnum(token)) { // fue util lo que encontramos en: https://cplusplus.com/reference/cctype/isdigit/
            st.push(stof(token));  // Si es un número, apílalo
        } else if (isvar(token)) { // fue util lo que encontramos en: https://cplusplus.com/reference/cctype/isalpha/
            // Es una variable, obtén su valor del mapa y apílalo
            st.push(variables[token]);
        } else if (isop(token[0])){
            
            float operand2 = st.top(); st.pop();
            float operand1 = st.top(); st.pop();

            if (token == "+") {
                st.push(operand1 + operand2);
            } else if (token == "-") {
                st.push(operand1 - operand2);
            } else if (token == "*") {
                st.push(operand1 * operand2);
            } else if (token == "/") {
                st.push(operand1 / operand2);
            } else if (token == "^") {
                st.push(pow(operand1, operand2));
            }
        }
    }

    return st.top();  // El resultado final estará en el tope de la pila
}

void Generate_tree(const vector<string>& tree){
    stack<trees::ABBNode*> sttree;
    int n = 0;
    for (const string& token : tree) {
        if (isnum(token)) { 
            sttree.push(new trees::ABBNode(token));

        } else if (isvar(token)) {
            sttree.push(new trees::ABBNode(token));

        } else if (isop(token[0])) {
            trees::ABBNode* root = new trees::ABBNode(token);
            root->setLeft(sttree.top());
            sttree.pop();
            root->setRight(sttree.top());
            sttree.pop();
            sttree.push(root);
        }
    }
    trees::ABB ftree(sttree.top());
    ftree.updateSize();
    ftree.traverse();
}

int main() {
    map<string, float> variables; // Para almacenar las variables
    vector<string> tree;
    string input;

    while (true) {
        cout << "Ingrese una expresión (o 'FIN' para salir): ";
        getline(cin, input);

        if (input == "FIN") break;

        if (input == "tree"){
            Generate_tree(tree);
            continue;
        }

        if (input.find('=') != string::npos) {
            // Procesar la asignación de variable
            vector<string> postfix;
            string var;
            for(char c : input){
                if (c != ' ') var += c;
            }
            size_t pos = var.find('=');
            string var_name = var.substr(0, pos);
            string var_value_str = var.substr(pos+1);
            InfixtoPostfix(var_value_str, postfix);
            float result = evaluatePostfix(postfix, variables);
            variables[var_name] = result;
        } else {
            string pfix;
            vector<string> postfix;
            InfixtoPostfix(input, postfix);
            tree = postfix;
            float result = evaluatePostfix(postfix, variables);
            variables["ans"] = result;
            cout << "Resultado: " << result << endl;
        }
        
    }
    return 0;
}