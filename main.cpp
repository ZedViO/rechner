#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

int get_prio(const string &str) {
    map<string, int> prio = {{"(", 1},
                             {"+", 2},
                             {"-", 2},
                             {"*", 3},
                             {"/", 3}};
    for (const auto &el: prio) {
        if (el.first == str) {
            return el.second;
        }
    }
    return -1;
}

bool pred(const string &str1) {
    return get_prio(str1) != -1;
}

int main() {
    cout << "Hallo! Dieser Rechner kann: +, -, *, /, sinx, cosx, tanx, cotx, exp, x" << endl;
    cout << "Z.B, tippen Sie \"4+5*3-(23-6)\" und dann sehen Sie die Magie" << endl;
    string expr;
    cin >> expr;
    //An diesem Moment haben wir eine Linie von Text

    vector<string> arrExpr;
    string wort;
    for (auto el: expr) {
        if (el != '+' && el != '(' && el != '-' && el != '*' && el != '/' && el != ')') {
            wort += el;
        } else {
            if (!wort.empty()) {
                arrExpr.push_back(wort);
                wort = "";
            }
            string elem;
            elem += el;
            arrExpr.push_back(elem);
            elem = "";
        }
    }
    if (!wort.empty()) {
        arrExpr.push_back(wort);
        wort = "";
    }
    //Dies lasst uns eine Sammlung der Elemente zu haben. Zum B. "34-(5*(5-334)-4)" -> {34, -, (, 5, ... , 4, )};

    vector<string> out;
    vector<string> stack;

    for (const auto &el: arrExpr) {
        if (el == ")") {
            while (stack[stack.size() - 1] != "(") {
                out.push_back(stack[stack.size() - 1]);
                stack.pop_back();
            }
            stack.pop_back();
        } else if (get_prio(el) == -1) {
            out.push_back(el);
        } else if (get_prio(el) != -1) {
            if (stack.empty() || get_prio(stack[stack.size() - 1]) < get_prio(el) || el == "(") {
                stack.push_back(el);
            } else if (get_prio(stack[stack.size() - 1]) >= get_prio(el)) {
                while (get_prio(stack[stack.size() - 1]) >= get_prio(el)) {
                    out.push_back(stack[stack.size() - 1]);
                    stack.pop_back();
                }
                stack.push_back(el);
            }
        }
    }

    while (!stack.empty()) {
        out.push_back(stack[stack.size() - 1]);
        stack.pop_back();
    }
    //Derzeit haben wir eine polnische Linie

    for (auto &el: out) {
        if (el.find("sin") != string::npos) {
            string arg;
            for (size_t it = 3; it < el.size(); ++it) {
                arg += el[it];
            }
            el = to_string(sin(stod(arg)));
        } else if (el.find("cos") != string::npos) {
            string arg;
            for (size_t it = 3; it < el.size(); ++it) {
                arg += el[it];
            }
            el = to_string(cos(stod(arg)));
        } else if (el.find("tan") != string::npos) {
            string arg;
            for (size_t it = 3; it < el.size(); ++it) {
                arg += el[it];
            }
            el = to_string(tan(stod(arg)));
        } else if (el.find("cot") != string::npos) {
            string arg;
            for (size_t it = 3; it < el.size(); ++it) {
                arg += el[it];
            }
            el = to_string(1/tan(stod(arg)));
        } else if (el.find("exp") != string::npos) {
            string arg;
            for (size_t it = 3; it < el.size(); ++it) {
                arg += el[it];
            }
            el = to_string(exp(stod(arg)));
        }
    }
    //Berechnen die Trigonomische Funktionen

    while (find_if(out.begin(), out.end(), pred) != out.end()) {
        auto pos = find_if(out.begin(), out.end(), pred);
        if (*pos == "+") {
            *(pos - 2) = to_string(stold(*(pos - 2)) + stold(*(pos - 1)));
            out.erase(pos - 1);
            out.erase(pos - 1);
        } else if (*pos == "-") {
            *(pos - 2) = to_string(stold(*(pos - 2)) - stold(*(pos - 1)));
            out.erase(pos - 1);
            out.erase(pos - 1);
        } else if (*pos == "*") {
            *(pos - 2) = to_string(stold(*(pos - 2)) * stold(*(pos - 1)));
            out.erase(pos - 1);
            out.erase(pos - 1);
        } else if (*pos == "/") {
            *(pos - 2) = to_string(stold(*(pos - 2)) / stold(*(pos - 1)));
            out.erase(pos - 1);
            out.erase(pos - 1);
        }
    }
    long double res = stold(out[0]);
    //Hier berechnen wir die Aufgabe

    cout << ("%g\n", res);
    //Sehr gut!

}