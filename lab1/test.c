int f(int a){
   int x;
   if(a==1||a==2) return 1;
   else return f(a-1) + f(a-2) ;
}

int main(){
  int i;
  int cnt;
  cnt = read();
  for(i=1;i<=cnt;i=i+1){
     write(f(i));
  }
  return 0;
}