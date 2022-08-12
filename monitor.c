
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>

 
// buffer should be big to read 100 events in one read operation
#define BUFSIZ( 100* (sizeof( struct inotify_event )  + NAME_MAX +1)  )

void main()
{
  FILE * fdconfig ;
  FILE * fout  ;
  int fdinotify;
  char watchname[PATH_MAX];  //this array holds the pathnames of files
  struct stat sb;
  int wd; 

//special for read events
  int n; 
  char eventbuf[BUFSIZ];
  char *p;
  struct inotify_event *ev;

// this array holds { the name of files => NAME_MAX +1 }  had already watched -> which indexed by watch descriptor => 0:100 
  char filewatched[100][NAME_MAX+1];





//to open config file that holds all wanted to read
 
if( (fdconfig=fopen("monitor.conf","r")) == NULL )
{
  printf("that file doesn't exist ");
  exit(1);
};

// FIRST , create an instance from inotify

fdinotify= inotify_init(); 

// to read all watched files name from this configfile

while( fgets( watchname, PATH_MAX ,fdconfig ) != NULL )
{
  watchname [ strlen( watchname) -1 ] = '\0';
    
//to check on the file by using stat
   if( stat (watchname,&sb) <0)
    { 
        printf("cannot stat %s",watchname);
        continue;
    }
//after success of stat , then check if this regular file
    if (S_ISREG( sb.st_mode ) )
      { 
// SECOND , add the regular file to  be watched
         if( (wd=inotify_add_watch(fdinotify,watchname,IN_DELETE_SELF | IN_MODIFY))<0 )
            {
              printf("error adding watch to %s \n ", watchname);
            }
          else
            {
              printf("added %s to watched list on descriptor %d\n",watchname ,wd);
              //record the file descriptors of files which was watched in the filewatched array
               strcpy( filewatched[wd] ,watchname );
            }

       }
    else
       {
        // it may be a directory or anything else..
        printf("%s not a regular file ", watchname);
       }

}






//for put all watched in a file -> so must open this file first  

 fout=fopen("monitor.out","a");

// THIRD , read and process events
 while(1)
  {
    n=read( fdinotify,eventbuf ,BUFSIZ );
    
   for( p=eventbuf; p < eventbuf +n  ;  )

       {

          ev = ( struct inotify_event *) p;
          p += sizeof( struct inotify_event ) + ev->len ;  //this is step of increment
        
       //to display event
                 // we use fprintf(fout) not printf()
         if( ev->mask & IN_MODIFY )
             fprintf(fout ,"%s the file was modified",  filewatched [ ev->mask ] ) ;
         if( ev->mask & IN_DELETE_SELF )
             fprintf(fout , "%s the file was deleted" , filewatched [ ev->mask ] );
       
          fflush(fout);
    }

  }








}
