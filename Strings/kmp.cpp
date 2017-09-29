/*
Sphere Online Judge: Pattern Find
http://www.spoj.com/problems/NAJPF/

Yudhistira Erlandinata
*/

#include <bits/stdc++.h>

using namespace std;

char needle[1000000];
char haystack[1000000];
int failureFunction[1000000];

//KMP Failure function precomputation
void precomputeFailureFunction(){
    failureFunction[0] = -1;
    for(int i = 1; i < strlen(needle); i++){
        int j = failureFunction[i - 1] + 1;
        while(true){
            if (needle[i] == needle[j]) {
                failureFunction[i] = j;
                break;
            } else if (j == 0){
                failureFunction[i] = -1;
                break;
            } else j = failureFunction[j - 1] + 1;
        }
    } 
}

int ans[1000000];

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // auto t1 = chrono::high_resolution_clock::now();

    int t;
    cin >> t;

    int count;

    for(int ii = 0; ii < t; ii++){
        cin >> haystack >> needle;

        if (strlen(needle) > strlen(haystack)){
            cout << "Not Found\n";
            if(ii != t - 1) cout << endl;
            continue;
        }

        precomputeFailureFunction();

        count = 0;

        //KMP Matching Algorithm Begin
        int i = 0;
        int j = 0;

        while(i + strlen(needle) - j <= strlen(haystack)){

            if (haystack[i] == needle[j]){
                i++;
                j++;
            } else if (j == 0){
                i++;
            } else{
                j = failureFunction[j - 1] + 1;
            }

            if (j == strlen(needle)){ //match
                ans[count++] = i - j;
                j = failureFunction[j - 1] + 1;
            }

        }
        //KMP Matching Algorithm End

        if (count == 0) cout << "Not Found\n";
        else{
            cout << count << endl;
            for(int i = 0; i < count; i++) cout << ans[i] + 1 << ' ';
            cout << endl;
        }
        if (ii != t - 1) cout << endl;
    }

    // auto t2 = chrono::high_resolution_clock::now();
    // chrono::duration<int64_t,nano> elapsed = t2 - t1;
    // cout << "Elapsed time: " << elapsed.count() / 1000000.0 << " ms\n";
    return 0;
}