#include <bits/stdc++.h>
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

void InfixtoPostfix(string s, vector<string>& postfix) {
    stack<char> stck;
    string num;

    for (int i = 0; i < s.length(); i++) {
        char c = s[i];

        if (c == ' ') {
            num.clear();
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
}
int evaluatePostfix(const vector<string>& postfix, map<string, int>& variables) {
    stack<int> st;
    
    for (const string& token : postfix) {
        if (isdigit(token[0])) {
            st.push(stoi(token));  // Si es un número, apílalo
        } else if (isalpha(token[0])) {
            // Es una variable, obtén su valor del mapa y apílalo
            st.push(variables[token]);
        } else {
            int operand2 = st.top(); st.pop();
            int operand1 = st.top(); st.pop();

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

int main() {
    map<string, int> variables; // Para almacenar las variables
    string input;

    while (true) {
        cout << "Ingrese una expresión (o 'FIN' para salir): ";
        getline(cin, input);

        if (input == "FIN") break;

        if (input.find('=') != string::npos) {
            // Procesar la asignación de variable
            size_t pos = input.find('=');
            string var_name = input.substr(0, pos);
            string var_value_str = input.substr(pos + 1);
            int var_value = stoi(var_value_str);
            variables[var_name] = var_value;
        } else {
            vector<string> postfix;
            InfixtoPostfix(input, postfix);
            int result = evaluatePostfix(postfix, variables);
            variables["ans"] = result;
            cout << "Resultado: " << result << endl;
        }
    }
    return 0;
}