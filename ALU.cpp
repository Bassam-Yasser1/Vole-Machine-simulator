#include "ALU.h"

int ALU::hexToDec(const string &hexStr) {
    int decimalValue;
    stringstream ss;
    ss << hex << hexStr;
    ss >> decimalValue;
    return decimalValue;
}

string ALU::decToHex(int decimalValue) {
    stringstream ss;
    ss << hex << setw(2) << setfill('0') << decimalValue;
    return ss.str();
}

void ALU::addTwosComplement(int idxReg1, int idxReg2, int idxReg3, Register &reg) {
    int val1 = hexToDec(reg.get(idxReg2));
    int val2 = hexToDec(reg.get(idxReg3));
    int result = val1 + val2;

    if (result > 255) {
        result -= 256;
    }
    reg.set(idxReg1, decToHex(result));
}

double ALU::binaryaryToFloat (string s){
    double decimal=0;
    int sign=1;
    if(s[0]=='-'){
        s.erase(s.begin());
        sign=-1;
    }
    int Position=find(s.begin(),s.end(),'.')-s.begin();

    for ( int i = 0; i < Position; i++)   {
        decimal += (s[i] - '0') * pow(2, Position-i-1);
    }int power=-1;
    for(int i=Position+1; i < s.size(); i++){
        decimal+=(s[i]-'0')*pow(2,power);
        power--;
    }
    if(sign==-1){
        decimal*=-1;
    }

    return decimal;
}

string ALU::decimalTobinaryary1(int n){
    string binary = "";
    while (n > 0) {
        binary = to_string(n % 2) + binary;
        n /= 2;
    }
    for(int i=0;binary.size()<4;i++){
        binary="0"+binary;
    }
    return binary;
}

double ALU::HexaToFloat(string number) {
    string hx="0123456789ABCDEF";
    string binary;
    string stringnumber1=decimalTobinaryary1((find(hx.begin(), hx.end(),number[0])-hx.begin()));
    string stringnumber2=decimalTobinaryary1((find(hx.begin(), hx.end(),number[1])-hx.begin()));

    int sign=stringnumber1[0]=='1'?-1:1;

    int moves= binaryaryToFloat(stringnumber1.substr(1,3));

    moves-=4;

    if(moves>0) {
        stringnumber2.insert(moves, ".");
    }
    if(moves<0){
        for(int i=0; i>moves; i--){
            stringnumber2.insert(0, "0");
        }
    }
    if(sign==-1) {
        stringnumber2 = "-" + stringnumber2;
    }
    if(moves<=0) {
        stringnumber2 = "0." + stringnumber2;
    }
    double ans=binaryaryToFloat(stringnumber2);
    return ans;

}

string ALU::DecimalTobinaryaryFloat(double number){
    string binary;
    string stringnumber1=to_string(number);
    int sign=1;
    if(stringnumber1[0]=='-')
    {
        sign=-1;
        stringnumber1.erase(stringnumber1.begin());

    }
    for(int i=stringnumber1.size()-1; i>=0,stringnumber1[i]=='0';i--){
        stringnumber1.pop_back();
    }

    int stringnumber2=stod(stringnumber1);
    string remainder5;
    for(int i=0; i<stringnumber1.length(); i++){
        if(stringnumber1[i]=='.'){
            i++;
            for(;i<stringnumber1.length();i++){remainder5+=stringnumber1[i];

            };
        }
    }
    remainder5="0."+remainder5;
    double remainder=stod(remainder5);

    while(stringnumber2>0){
        binary=to_string(stringnumber2%2)+binary;
        stringnumber2/=2;
    }
    binary+='.';

    while(remainder>0){
        remainder*=2;
        if(remainder>=1){
            binary+="1";
            remainder-=1;
        }
        else binary+="0";
    }
    if(sign==-1){
        binary="-"+binary;}

    return binary;
}

string ALU::binaryToHex(string binary){
    string hex;
    int middle=0;
    if(binary[0]=='-'){
        hex+="1";
        binary.erase(binary.begin());
    }
    else hex+="0";
    for(int i=0;i<binary.size();i++){
        if(binary[i]=='.')break;
        middle++;
    }
    middle+=4;
    string first=decimalTobinaryary1(middle);
    for(int i=0;first.size()>3;i++){
        first.erase(first.begin());}
    hex+=first;

    string last;
    for(int i=0;i<binary.size();i++){
        if(binary[i]=='.')continue;
        last+=binary[i];

    }
    hex+=last;
    for(int i=0;8>hex.size();i++){
        hex+="0";
    }

    return hex;
}

string ALU::Ans(string binary){
    string hex1=binary.substr(0,4);
    string hex2=binary.substr(4,8);
    double hex10=binaryaryToFloat(hex1);
    double hex20=binaryaryToFloat(hex2);
    string hexastr="0123456789ABCDEF";
    string ans;
    ans+=hexastr[(int)hex10];
    ans+=hexastr[(int)hex20];

    return ans;

}

void ALU::addFloatingPoint(int idxReg1, int idxReg2, int idxReg3, Register &reg) {
    string hexaStringA = reg.get(idxReg2);
    string hexaStringB = reg.get(idxReg3);
    string hexaNew="";
    string hexaNew2="";

    for(char ch : hexaStringA){
        if(ch == 'a'|| ch=='b' || ch=='c'|| ch=='d' || ch=='e' || ch=='f' ){
            hexaNew += toupper(ch);
        }
        else{
            hexaNew += ch;
        }
    }
    for (char ch : hexaStringB) {
        if (ch == 'a' || ch == 'b' || ch == 'c' || ch == 'd' || ch == 'e' || ch == 'f') {
            hexaNew2 += toupper(ch);
        } else {
            hexaNew2 += ch;
        }
    }
    double floatA = HexaToFloat(hexaNew);
    double floatB = HexaToFloat(hexaNew2);
    double sum = floatA + floatB;
    string sumHex = Ans(binaryToHex(DecimalTobinaryaryFloat(sum)));
    cout << sumHex << endl;
    reg.set(idxReg1, sumHex);
}
