#include <stdio.h>
#include <string.h>

#include <iostream>
#include <string>
using namespace std;

void usage();
void LoadProf(FILE *fp);
void prof2pov(FILE *fp, char *fmt, int num);
void Malloc(int nP);
void Free();

char* fformat;
int fnum = 0;

//prof
int nP;
float SimTime;
float *Pos, *Vel, *Rad, *Val;
int *Id, *Typ;

namespace CAM {
	float pos[3];
	float look[3];
	float angle;
};

void init(){
	using namespace CAM;
	pos[0] = 1000.0;
	pos[1] = 100.0;
	pos[2] = 100.0;
	look[0]= 0.0;
	look[1]= 0.0;
	look[2]= 0.0;
	angle = 45;
}

int main(int argc, char **argv){
	init();
	
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
		
		LoadProf(fp);
		
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
		
		Free();
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
	
	//include files
	fprintf(fp, "#include \"setting.inc\"\n");
	
	//settings
	fprintf(fp, "CAM(<%f,%f,%f>,<%f,%f,%f>,%f)\n", CAM::pos[0], CAM::pos[1], CAM::pos[2], CAM::look[0], CAM::look[1], CAM::look[2], CAM::angle);
	
	//output data
	for(int i=0;i<nP;i++){
		fprintf(fp, "SP(<%f,%f,%f>,%f)\n", Pos[i*3], Pos[i*3+1], Pos[i*3+2], Rad[i]);
	}
	
	fclose(fp);
}

void LoadProf(FILE *fp){
	fscanf(fp, "%f", &SimTime);
	fscanf(fp, "%d", &nP);
	
	Malloc(nP);
	
	for(int i=0;i<nP;i++){
		fscanf(fp, "%f %f %f %f %f %f %f %d %d %f", &Pos[i*3], &Pos[i*3+1], &Pos[i*3+2], &Vel[i*3], &Vel[i*3+1], &Vel[i*3+2], &Rad[i], &Id[i], &Typ[i], &Vel[i]);
	}
}

void Malloc(int nP){
	Pos = new float[nP*3];
	Vel = new float[nP*3];
	Rad = new float[nP];
	Val = new float[nP];
	
	Id  = new int[nP];
	Typ = new int[nP];
}

void Free(){
	delete Pos;
	delete Vel;
	delete Rad;
	delete Val;
	delete Id;
	delete Typ;
}


