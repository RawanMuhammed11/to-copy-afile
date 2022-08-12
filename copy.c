//to copy content of file to another

#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>

#define BSIZE 16000

int main(int argc , char *argv[])
{
int fin,fout;
char buf[BSIZE];
int count;


if(argc<3)
{
  printf("you must add 3 argument -> copy + srcfile + dstfile\n" );

}
else
{


  if(( (fin=open(argv[1],O_RDONLY)) <0))
     
   printf("there is an error in this file : %s\n ",argv[1]);
  
 else
   {
  if( ((fout=open(argv[2],O_WRONLY|O_CREAT,0644))<0) )
     
   printf("there is an error in this file: %s\n ",argv[2]); 
 
   }

//to copy content of foo file into boo

while( (count=read(fin,buf,BSIZE))>0 )
 { 
 write(fout,buf,count);   
 }
close(fin);
close(fout);

} 
}
