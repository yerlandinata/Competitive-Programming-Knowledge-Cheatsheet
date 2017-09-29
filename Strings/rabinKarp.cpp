/*
Sphere Online Judge: Pattern Find
http://www.spoj.com/problems/NAJPF/

Yudhistira Erlandinata
*/

#include <bits/stdc++.h>

using namespace std;


const unsigned long long B = 41;
unsigned long long powersOf41[1000010];

void precomputePowers(){
    powersOf41[0] = 1;
    for(int i = 1; i < 1000010; i++){
        powersOf41[i] = B * powersOf41[i - 1];
    }
}


//base is B and modulus is 2^64
//remember; keyword 'hash' is taken!
unsigned long long hashFunction(string s, int start, int end){
    unsigned long long res = 0;
    for(int i = start; i <= end; i++){
        res += (unsigned long long)((s[i] - '0') * powersOf41[(unsigned long long)(end - i)]);
    }
    return res;
}

unsigned long long hashFunction(char c){
    return (unsigned long long)(c - '0');
}

int ans[1000000];

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    precomputePowers();
    string haystack, needle;
    unsigned long long needleHash, currentHash, needleSize;
    for(int ii = 0; ii < t; ii++){
        cin >> haystack >> needle;

        int count = 0;
        needleSize = needle.size();
        if (needleSize > haystack.size()){
            cout << "Not Found\n\n";
            continue;
        }

        //Rolling hash begin
        needleHash = hashFunction(needle, 0, needleSize - 1);
        currentHash = hashFunction(haystack, 0, needleSize- 1);
        if (needleHash == currentHash) ans[count++] = 0;
        for(int i = 1; i + needleSize <= haystack.size(); i++){
            currentHash -= (hashFunction(haystack[i - 1]) * powersOf41[needleSize - 1]);
            currentHash *= B;
            currentHash += (hashFunction(haystack[i + needleSize - 1]));
            if (currentHash == needleHash) ans[count++] = i;
        }
        //Rolling hash end

        if (count == 0) cout << "Not Found\n\n";
        else {
            cout << count << endl;
            for(int i = 0; i < count; i++){
                cout << ans[i] + 1 << ' ';
            }
            cout << "\n\n";
        }




    }
    return 0;
}