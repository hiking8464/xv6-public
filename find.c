#include "types.h"

#include "stat.h"
#include "user.h"
#include "fs.h"

int verify(char *str)
{

    if(strcmp(str,"-name")==0 || strcmp(str,"-type")==0 || strcmp(str,"-inum")==0 || strcmp(str,"-printi")==0)
        return 0;
    else
        return 1;
}

void cus_print(char* buf,int printi_bool,int inum)
{
    if(printi_bool)
    {
        printf(1,"%d \t %s\n",inum,buf);
    }
    else
    {
        printf(1,"%s\n",buf);
    }
}

void
find(char *path,char *name, char *type,char *inum,int printi_bool)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    printf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    printf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }


  switch(st.type){
  case T_FILE:
        printf(1, "%s\n", path);
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf(1, "ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de))
    {
        if(de.inum == 0 || (de.name[0]=='.'))
            continue;
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if(stat(buf, &st) < 0){
            printf(1, "ls: cannot stat %s\n", buf);
            continue;
        }

        if(strlen(name)==0 && strlen(type)==0 && strlen(inum)==0)
        {
            cus_print(buf,printi_bool,st.ino);
            if(st.type==T_DIR)
            {
                find(buf,name,type,inum,printi_bool);
            }
        }
        else if(strlen(name)!=0 && strlen(type)==0 && strlen(inum)==0)
        {
            if(strcmp(de.name,name)==0)
            {
                cus_print(buf,printi_bool,st.ino);
            }
            if(st.type==T_DIR)
            {
                find(buf,name,type,inum,printi_bool);
            }
        }
        else if(strlen(name)==0 && strlen(type)!=0 && strlen(inum)==0)
        {
            if(st.type==T_FILE && strcmp(type,"f")==0)
            {
                cus_print(buf,printi_bool,st.ino);
            }
            else if(st.type==T_DIR && strcmp(type,"d")==0)
            {
                cus_print(buf,printi_bool,st.ino);
            }
            if(st.type==T_DIR)
            {
                find(buf,name,type,inum,printi_bool);
            }
        }
        else if(strlen(name)==0 && strlen(type)==0 && strlen(inum)!=0)
        {
            if(st.ino == atoi(inum))
            {
                cus_print(buf,printi_bool,st.ino);
            }
            if(st.type==T_DIR)
            {
                find(buf,name,type,inum,printi_bool);
            }
        }
        else if(strlen(name)!=0 && strlen(type)!=0 && strlen(inum)==0)
        {
            if(strcmp(de.name,name)==0 && st.type==T_FILE && strcmp(type,"f")==0)
            {
                cus_print(buf,printi_bool,st.ino);
            }
            else if(strcmp(de.name,name)==0 && st.type==T_DIR && strcmp(type,"d")==0)
            {
                cus_print(buf,printi_bool,st.ino);
            }
            if(st.type==T_DIR)
            {
                find(buf,name,type,inum,printi_bool);
            }
        }
        else if(strlen(name)!=0 && strlen(type)==0 && strlen(inum)!=0)
        {
            if(strcmp(de.name,name)==0 && st.ino == atoi(inum))
            {
                cus_print(buf,printi_bool,st.ino);
            }
            if(strcmp(de.name,name)==0 && st.type==T_DIR)
            {
                find(buf,name,type,inum,printi_bool);
            }
        }
        else if(strlen(name)==0 && strlen(type)!=0 && strlen(inum)!=0)
        {
            if(st.type==T_FILE && strcmp(type,"f")==0 && st.ino == atoi(inum))
            {
                cus_print(buf,printi_bool,st.ino);
            }
            else if(st.type==T_DIR && strcmp(type,"d")==0 && st.ino == atoi(inum))
            {
                cus_print(buf,printi_bool,st.ino);
            }
            if(st.type==T_DIR)
            {
                find(buf,name,type,inum,printi_bool);
            }
        }
        else
        {
            if(strcmp(de.name,name)==0 && st.type==T_FILE && strcmp(type,"f")==0 && st.ino == atoi(inum))
            {
                cus_print(buf,printi_bool,st.ino);
            }
            else if(strcmp(de.name,name)==0 && st.type==T_DIR && strcmp(type,"d")==0 && st.ino == atoi(inum))
            {
                cus_print(buf,printi_bool,st.ino);
            }
            if(st.type==T_DIR)
            {
                find(buf,name,type,inum,printi_bool);
            }
        }
    }
    break;

  }
  close(fd);
}

int
main(int argc, char *argv[])
{

  char *name = "";
  char *type = "";
  char *inum = "";
  int printi_bool=0;

  char *folder=".";

  if(argc < 2)
  {
    find(folder,name,type,inum,printi_bool);
    exit();
  }
  else
  {
    int i=1;
    if(verify(argv[1]))
    {
        folder = argv[1];
        i=2;

    }
    //printf(1,"%s %d",folder,argc);
    while(i<argc)
    {
        if(!strcmp("-name",argv[i]))
        {
            name=argv[i+1];
            i++;
        }
        else if(!strcmp("-type",argv[i]))
        {
            type=argv[i+1];
            i++;
        }
        else if(!strcmp("-inum",argv[i]))
        {
            inum=argv[i+1];
            i++;
        }
        else if(!strcmp("-printi",argv[i]))
        {
            printi_bool=1;
        }
        else
        {
            printf(1,"Error!!\n Usage : find <foldername> -name <name> -type <f/d> -inum <inode number> -printi\n");
        }
        i++;
    }
    //printf(1,"===== %s %s %s %d\n",name,type,inum,printi_bool);
    find(folder,name,type,inum,printi_bool);

  }
  exit();
}
