#include "types.h"
#include "stat.h"
#include "user.h"

int strncmp(char *curr_line,char *prev_line,int N){
int num=N;
if(strlen(prev_line)==0)
return 1;
if(num>strlen(curr_line))
num=strlen(curr_line);
if(num>strlen(prev_line))
num=strlen(prev_line);
for(int i=0;i<num;i++){
if(curr_line[i]!=prev_line[i])
return 1;
}
return 0;
}
void uniq(char *file_name,int cFlag,int uFlag,int wFlag){
  int fd=0;
  int n;
  char curr_line[512];
  char prev_line[512]="";
  //char wflag_line[512];
  char line[512];
  int j=0;
  int count=0;
  int num=wFlag;
  if(strcmp(file_name,"")!=0){
  if((fd=open(file_name,0))<0){
  printf(2,"cannot open %s\n",file_name);
  exit();
  }
  }
  while((n=read(fd,line,sizeof(line)))>0){
    for(int i=0;i<n;i++){
      curr_line[j++]=line[i];
  	if(line[i]=='\n'){
  	curr_line[j]='\0';
  	if(wFlag==0)
  	  {
  	  num=strlen(curr_line);
  	  }
  	  //else{
  	  if(strncmp(curr_line,prev_line,num)!=0){
  	    if(cFlag==0 && uFlag==0 && wFlag==0){
  	      printf(2,"%s",curr_line);}
  	    else if(cFlag!=0 && strcmp(prev_line,"")!=0){
  	      printf(2,"%d %s",count,prev_line);
  	      count=0;
  	    }
  	    else if(uFlag!=0){
  	    //printf(2,"Count VAlue:%d\n",count);
  	      if(strcmp(prev_line,"")!=0 && count==1)
  	      {
  	    	printf(2,"%s",prev_line);
  	    	
  	      }
  	      count=0;
  	    
  	    }
  	    else if(wFlag!=0){
  	    //count=0;
  	    //if(count==0){
  	    //strcpy(wflag_line,);
  	    printf(2,"%s",curr_line);
  	    //}
  	    
  	    //count=0;
  	    }
  	    
  	  }
  	  //}
  	  
  	  strcpy(prev_line,curr_line);
  	  j=0;
  	  count+=1;
  	
  	}
    }
  }
  if(cFlag!=0 && strcmp(prev_line,"")!=0)
  printf(2,"%d %s",count,prev_line);
  if(uFlag!=0 && strcmp(prev_line,"")!=0 && count==1)
  printf(2,"%s",prev_line);
  
}

int
main(int argc, char *argv[])
{
  int i;
  if(argc==1){
  uniq("",0,0,0);
  }
  
  /*if(argc < 2){
    printf(2, "Usage: uniq <file_name>\n");
    exit();
  }*/
  

  for(i = 1; i < argc; i++){
    if(strcmp("-c", argv[i])==0 && i+1<argc){
    uniq(argv[i+1],1,0,0);
    i+=1;
    
    }
    else if(strcmp("-u", argv[i])==0 && i+1<argc){
    uniq(argv[i+1],0,1,0);
    i+=1;
    }
    else if(strcmp("-w", argv[i])==0 && i+2<argc){
    uniq(argv[i+2],0,0,atoi(argv[i+1]));
    i+=2;
    
    }
    else if(argv[i][0]!='-'){
    uniq(argv[i],0,0,0);
    }
    
  }

  exit();
}
