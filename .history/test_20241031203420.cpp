#include <bits/stdc++.h>



int main(){
    char s[104];
    int t;
    scanf("%d", &t);
    while(t--){
        scanf("%s", s);
        int n = strlen(s);
        for(int i = 0; i < n; i++){
            if(s[i] >= '0' && s[i] <= '9'){
                printf("%c", s[i]);
            }
        }
    }
    return 0;
}