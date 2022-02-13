#include<iostream>
using namespace std;
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
void operate(char *str);
void compare(char *file1,char *file2);
void cat(char *file);
void wc(char *file,char *mode);
void man(char *mode);
void copyfile(char *file1,char *file2);
void copydir(char *dir1,char *dir2);
bool ifdir(char *path);
bool iffile(char *path);
char *correct(char *old);
void shellit(char *file);
