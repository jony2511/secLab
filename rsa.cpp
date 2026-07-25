#include<bits/stdc++.h>
using namespace std;
#define intt __int128_t

intt mymod(intt a,intt b)
{
    return a-(a/b)*b;
}

intt mygcd(intt a,intt b)
{
    if(a<b)
    swap(a,b);
    if(b==0)
    return a;

   return mygcd(b,mymod(a,b));
}

intt exgcd(intt a,intt b, intt &x, intt &y)
{
    if(b==0){
        x=1;
        y=0;
        return a;
    }
    intt x1,y1;
    intt gcd=exgcd(b,mymod(a,b),x1,y1);
    x=y1;
    y=x1-(a/b)*y1;
    return gcd;
}

intt modularInverse(intt e, intt phi){
    intt x,y;
    intt gcd=exgcd(e,phi,x,y);
    if(gcd!=1)
       return -1;
    x=mymod(x,phi);
    if(x<0)
      x+=phi;
    return x;
}

intt modPow(intt base,intt expp, intt mod){
    intt res=1;
    base=mymod(base,mod);
    while(expp>0){
        if(expp & 1)
           res=mymod(res*base,mod);
         base=mymod(base*base,mod);
         expp>>=1;
    }
    return res;
}
void print(intt num){
    if(num==0){
        cout<<0;
        return;
    }
    if(num<0){
        cout<<'-';
        num=-num;
    }

    string result;
    while(num>0){
        int x=(int)mymod(num,10);
        result.push_back(char('0'+x));
        num=num/10;
    }
    reverse(result.begin(),result.end());
    cout<<result;
}

intt read(){
    string s;
    cin>>s;
    intt num=0;
    for(char c:s)
      num=num*10+(c-'0');
    return num;
}
int main(){
    intt p=3731292319LL;
    intt q=3492564827LL;
    intt n=p*q;
    intt phi=(p-1)*(q-1);
    intt e=2;
    while(mygcd(e,phi)!=1)
      e++;

    cout<<"p: ";
    print(p);
    cout<<endl<<"q: ";
    print(q);
    cout<<endl<<"e: ";
    print(e);
    cout<<endl<<"n: ";
    print(n);
    cout<<endl<<"phi(n): ";
    print(phi);

    intt firstD=modularInverse(e,phi);
    cout<<endl<<"First three D:"<<endl;
    for(int k=0;k<3;k++){
        intt d=firstD+(intt)k*phi;
        cout<<'d'<<k+1<<": ";
        print(d);
        cout<<endl;
    }

    cout<<endl<<"Enter message: ";
    intt message=read();
    cout<<endl<<"Encrypted message: ";
    intt en=modPow(message,e,n);
    print(en);
    intt dc=modPow(en,firstD,n);
    cout<<endl<<"Decrypted message: ";
    print(dc);

    return 0;
}
