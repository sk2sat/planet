#include <stdio.h>
#include <string.h>

#include <iostream>
#include <string>
using namespace std;

void usage();
void prof2pov(FILE *fp, char *fmt, int num);

char* fformat;
int fnum = 0;

int main(int argc, char **argv){
	switch(argc){
	case 1:
	case 2:
		usage();
		return -1;
	default:
//		usage();
		break;
	}
	
	fformat = argv[1];
	fnum = atoi(argv[2]);
	
	char fname[256];
	FILE *fp;
	
	for(int i=0;i<fnum;i++){
		sprintf(fname, fformat, i);
		cout<<"loading: "<<fname<<endl;
		fp = fopen(fname, "r");
		
		if(fp == NULL){
			cout<<"error: can't open file."<<endl;
			break;
		}
		
		char tmp[256];
		strcpy(tmp, fformat);
		char *p = tmp;
		for(;;){ p++; if(*p == '.') break; }
		p++; *p='p';
		p++; *p='o';
		p++; *p='v';
		p++; *p='\0';
		prof2pov(fp, tmp, i);
		
		fclose(fp);
	}
}

void usage(){
	printf("usage> ./prof2pov fileformat filenumber \n");
}

void prof2pov(FILE *fp, char *fmt, int num){
	char fname[256];
	
	sprintf(fname, fmt, num);
	cout<<"writing: "<<fname<<endl;
	
	fp = fopen(fname, "w");
	
	
	
	fclose(fp);
}


