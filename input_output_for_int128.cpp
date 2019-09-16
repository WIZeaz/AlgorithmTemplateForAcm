//__int128_t only usable in Linux
#include <bits/stdc++.h>
using namespace std;
inline __int128_t read()
{
   int X=0,w=0; char ch=0;
   while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
   while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
   return w?-X:X;
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