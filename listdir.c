// list directories  combine between listfile as compiled before & directories
// similar to ls

#include<fcntl.h>  
#include<stdio.h>
#include<sys/stat.h>
#include<time.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>     //because we will use function called strlen()

void listfile( char *name)
{
  struct stat sb;
  
  char *x;    //pointer because i will assgin address value to it in the row of ctime(&)


  stat(name,&sb);      // pass the name of the file not argv


  char *filetype[]= { "?", "p","c","?","d","?","b","?","-","?","-","?","l","?","s"};
  printf("%s", filetype[ (sb.st_mode >>12) & 017 ]); 
  printf("%c%c%c%c%c%c%c%c%c",
          (sb.st_mode & S_IRUSR ) ? 'r' : '-',
          (sb.st_mode & S_IWUSR ) ? 'w' : '-',
          (sb.st_mode & S_IXUSR ) ? 'x' : '-',
          (sb.st_mode & S_IRGRP ) ? 'r' : '-',
          (sb.st_mode & S_IWGRP ) ? 'w' : '-',
          (sb.st_mode & S_IWGRP ) ? 'x' : '-',
          (sb.st_mode & S_IROTH ) ? 'r' : '-',
          (sb.st_mode & S_IWOTH ) ? 'w' : '-',
          (sb.st_mode & S_IXOTH ) ? 'x' : '-' );

  printf("%8ld", sb.st_size );

//to remove \n at end from ctime()

  x=ctime(&sb.st_mtime);
  x [ strlen(x)-1 ] ='\0';

  printf("  %s  ", x);
  
  printf("%s\n",name);   //name of file

}

//now we will use directories

int main(int argc,char *argv[])
{
   DIR *d;
   struct dirent *info;

if(argc!=2)
{
  fprintf(stderr,"usage: ls + filename \n");
  exit(1);
}
  chdir(argv[1]);
  
  d=opendir(".");
  while ( (info=readdir(d)) != NULL )
    { 
        listfile(info->d_name);
     }  

 }
