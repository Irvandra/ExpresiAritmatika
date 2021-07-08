#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

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
