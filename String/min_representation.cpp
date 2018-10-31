#include <cstring>
#include <cstdio>
using namespace std;
int minRepresentation(char* str)
{
    int i=0,j=1,k=0;
    int len=strlen(str);
    while (j<len && k<len){
		int t=str[(i+k)%len]-str[(j+k)%len];
        if (!t) ++k;
        else {
            if (t<0) j+=k+1;
            else {i+=k+1; j=i+1;}
            k=0;
        }
    }
    return i;
}
int main()
{
    int T;
    char str[10000];
    scanf("%d",&T);
    while (T--){
        scanf("%s",str);
        printf("%d\n",minRepresentation(str)+1);
    }
    return 0;
}