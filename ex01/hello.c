#include <stdio.h>
void input(char a[]) 
{
	scanf("%s",a);
}
int main() 
{
	char s[1000];
	input(s);
    printf("%s",s);
    return 0;
}
