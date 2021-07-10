#include <iostream>
#include <cstring>
#include <vector>
#define MAX 20

using namespace std;

char stk[MAX];
int top = -1;

bool IsFull(){
    return top == MAX - 1;
}

bool IsEmpty(){
    return top == -1;
}

void Push(char _ch)
{
    if(!IsFull())
    {
        stk[++top] = _ch;
    }
}

char Pop()
{
    char ch;

    if(!IsEmpty())
    {
        ch = stk[top];
        stk[top] = '\0';
        top--;
        return(ch);
    }

    return 0;
}

int Priority (char _alpha)
{
    if(_alpha == '+' || _alpha =='-')
    {
        return(1);
    }
 
    if(_alpha == '*' || _alpha =='/' || _alpha == '%')
    {
        return(2);
    }

    return 0;
}

string Postfix(vector<string> _infix)
{
    vector<string> postfix;
    string postfixData, data;

    int i = 0;

    char cNum[] = "0123456789";
    char cSym[] = "()+-/%*";

    for(auto sprtd : _infix){
        char chr[strlen(sprtd.c_str())];
        strcpy(chr, sprtd.c_str());

        if(strspn(chr, cNum)){
            data += sprtd;
            postfix.push_back(data);
            data = "";
        }else if(chr[0] == '('){
            Push(chr[0]);
        }else if(chr[0] == ')'){
            while(stk[top] != '('){
                data = Pop();
                postfix.push_back(data);
                data = "";
            }

            Pop();
        }else{
            bool skip = false;

            if((unsigned)i != _infix.size() && chr[0] == '-'){
                char nextChr[strlen(_infix[i + 1].c_str())];
                strcpy(nextChr, _infix[i + 1].c_str());

                if(i > 0){
                    char prevChr[strlen(_infix[i - 1].c_str())];
                    strcpy(prevChr, _infix[i - 1].c_str());
                    
                    if(strspn(prevChr, cSym)){
                        data = sprtd;
                        skip = true;
                    }
                }else if(strspn(nextChr, cNum)){
                    data = sprtd;
                    skip = true;
                }
            }

            if(top == -1 && !skip){
                Push(chr[0]);
            }else if(Priority(chr[0]) <= Priority(stk[top]) && !skip){
                data = Pop();
                postfix.push_back(data);
            
                while(Priority(stk[top]) == Priority(chr[0])){
                    data = Pop();
                    postfix.push_back(data);

                    if(top < 0) {
                        break;
                    }
                }

                data = "";
                Push(chr[0]);
            }else if(Priority(chr[0]) > Priority(stk[top]) && !skip){
                Push(chr[0]);
            }
        }

        i++;
    }

    while(top != -1)
    {
        data = Pop();
        postfix.push_back(data);
    }

    i = 0;

    for(auto x : postfix){
        postfixData += x;
        
        if((unsigned)i != postfix.size()){
            postfixData += " ";
        }

        i++;
    }

    return postfixData;
}

vector<string> Separating(string _input){
    vector<string> sprtd;
    string data;
    bool isNumEnd = false;

    int i = 0;

    char cNum[] = "0123456789";
    char cSym[] = "(+-/%*";
    char chr[1];
    
    while(_input[i] != '\0'){
        chr[0] = _input[i];

        if(strspn(chr, cNum) && chr[0] != ' '){
            data += _input[i];
            isNumEnd = true;

            if((unsigned)i == strlen(_input.c_str()) - 1){
                sprtd.push_back(data);
            }
        }else if(chr[0] != ' '){
            if(isNumEnd){
                sprtd.push_back(data);
                isNumEnd = false;
            }

            data = _input[i];
            sprtd.push_back(data);

            data = "";

            if(i > 0){
                chr[0] = _input[i - 1];

                if(_input[i] != '(' && strspn(chr, cSym)){
                    sprtd.push_back("1");
                    sprtd.push_back("*");
                }
            }
        }

        i++;
    }
    
    return sprtd;
}

int main(){
    string input;

    getline(cin, input); 
    
    cout << Postfix(Separating(input)) << endl;
}
