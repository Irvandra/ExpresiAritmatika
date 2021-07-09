#include <iostream>
#include <vector>
#include <cstring>
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

void Separating(string _input){
    vector<char> sprtd;
    string data;

    char cNum[] = "0123456789";
    char cSym[] = "+-/%*";
    char cSpc[] = "()";
    char chr[1];
    

    for(int i = 0; i < strlen(_input.c_str()); i++){
        chr[0] = _input[i];

        if(strspn(chr, cSym) || strspn(chr, cNum) || strspn(chr, cSpc)){
            sprtd.push_back(_input[i]);
        }
    }
    
    for (int i = 0; i != sprtd.size(); i++){    
        chr[0] = sprtd[i];

        if((strspn(chr, cSym) || sprtd[i] == ')') && sprtd[i] != '(' && i > 0){
            data += " ";
        }
        
        if(strspn(chr, cNum)){
            data += sprtd[i];
        }else{
            data += sprtd[i];

            if(i > 0){
                chr[0] = sprtd[i - 1];

                if(sprtd[i] != '(' && strspn(chr, cSym)){
                    data += "1 * ";
                }else if(sprtd[i] != ')'){
                    chr[0] = sprtd[i + 1];

                    if(!strspn(chr, cSym)){
                        data += " ";
                    }
                }
            }else if(sprtd[i + 1] == '('){
                data += "1 * ";                
            }
        }
    }

    cout << data << endl;
}

int main(){
    string input;

    getline(cin, input);
 
    
    Separating(input);
}
