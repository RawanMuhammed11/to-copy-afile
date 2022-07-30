//to copy content of file to another

#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>

#define BSIZE 16000

int main()
{
int fin,fout;
char buf[BSIZE];
int count;

if( (fin=open("foo",O_RDONLY)) <0)
 { 
   perror("there is an error in foo file");
   exit(1);
 }
if( (fout=open("boo",O_WRONLY|O_CREAT,0644))<0 )
 {
   perror("there is an error in boo file"); 
   exit(2); 
 }
//to copy content of foo file into boo

while( (count=read(fin,buf,BSIZE))>0 )
 { 
   write(fout,buf,count);   
 }
close(fin);
close(fout);

 
}
