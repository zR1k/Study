#include <bits/stdc++.h>



int main(){
    char s[104];
    int t;
    scanf("%d", &t);
    while(t--){
        scanf("%s", s);
        int n = strlen(s);
        int a = 0;
        for(int i = 0; i < n; i++){
            if(s[i] >= '0' && s[i] <= '9'){
                // printf("%c", s[i]);
                a = a * 10 + (s[i] - '0');
            }
            else break;
        }
        
    }
    return 0;
}