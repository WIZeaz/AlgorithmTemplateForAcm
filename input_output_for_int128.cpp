//__int128_t only usable in Linux
#include <bits/stdc++.h>
using namespace std;
inline __int128_t read()
{
   __int128_t rnt=0;
   int sign=0; 
   char ch=0;
   while(!isdigit(ch)) {sign|=ch=='-';ch=getchar();}
   while(isdigit(ch)) rnt=(rnt<<3)+(rnt<<1)+(ch^48),ch=getchar();
   return sign?-rnt:rnt;
}
inline void print(__int128_t x)
{    
   if(x<0){putchar('-');x=-x;}
   if(x>9) print(x/10);
   putchar(x%10+'0');
}
int main()
{
    __int128_t a,b;
    a=read(); b=read();
    print(a+b);
}