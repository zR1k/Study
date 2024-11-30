#include <bits/stdc++.h>



int main(){
    char s[104];
    int t;
    scanf("%d", &t);
    while(t--){
        scanf("%s", s);
        int n = strlen(s);
        if(n > 10){
            printf("%c%d%c\n", s[0], n-2, s[n-1]);
        }else{
            printf("%s\n", s);
        }
    }
    return 0;
}