#include <bits/stdc++.h>

 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

 

int main(){
    char s[104];
    int t;
    scanf("%d", &t);
    while(t--){

        std::function<void(int)> f = [&](int x){
            printf("%d\n", x);
        };
        scanf("%s", s);
        int n = strlen(s);
        int a = 0;
        for(int i = 0; i < n; i++){
            if(s[i] >= '0' && s[i] <= '9'){
                // printf("%c", s[i]);
                a = a * 10 + (s[i] - '0');
                // printf("%d %s\n", a, s[i]);
            }
            else break;
        }
        int b = sqrt(a);
        int ans = b * b;
        if(ans == a) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}