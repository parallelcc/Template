//int/ll 使用方法：  
//a = Scan();    
int Scan() {		//输入外挂 
    int res = 0, flag = 0;  
    char ch;  
    if((ch = getchar()) == '-') flag = 1;  
    else if(ch >= '0' && ch <= '9') res = ch - '0';  
    while((ch = getchar()) >= '0' && ch <= '9')  
        res = res * 10 + (ch - '0');  
    return flag ? -res : res;  
    return res ;  
} 
void Out(int a) {    //输出外挂  
    if(a < 0) { putchar('-'); a = -a; }  
    if(a >= 10) Out(a / 10);  
    putchar(a % 10 + '0');  
}  
//字符串 使用样例：  
//scanf_(&a);  
void scanf_(int *p)  
{  
    char in;  
    while((in=getchar())>57||in<48);  
    *p=in-48;  
    while(in=getchar(),in>=48&&in<=57)  
    *p*=10,*p+=in-48;  
}  
//double
int re(double *ret){  
    int sgn;  
    double bit=0.1;  
    char c;  
    c=getchar();  
    if(c==EOF)return true;  
    while(c!='-'&&c!='.'&&(c<'0'||c>'9'))c=getchar();  
    sgn=(c=='-')?-1:1;  
    *ret=(c=='-')?0:(c-'0');  
    while((c=getchar())>='0'&&c<='9')*ret=*ret*10+(c-'0');  
    if(c==' '||c=='\n'){*ret*=sgn;return true;}  
    while((c=getchar())>='0'&&c<='9')*ret+=(c-'0')*bit,bit/=10;  
    *ret*=sgn;  
    return false;  
}   

