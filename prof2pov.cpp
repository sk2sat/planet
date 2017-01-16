#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>

#include <lua.hpp>

#define POVRAY_INC_FILE	"stdpov.inc"

using namespace std;

void usage();
void LoadProf(FILE *fp);
void prof2pov(FILE *fp, char *fmt, int num);
void Malloc(int nP);
void Free();

lua_State *lua = NULL;
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
	case 3:	// lua無し
		break;
	case 4: // lua有り
//		lua = lua_open();
		lua = luaL_newstate();
		luaL_openlibs(lua);
		if(luaL_loadfile(lua, argv[3])){
			fprintf(stderr, "can't load lua file:%s\n", argv[3]);
			return -1;
		}
		
		break;
	default:
		usage();
		return -1;
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
	printf("usage> ./prof2pov fileformat filenumber [Lua_file] \n");
}

void prof2pov(FILE *fp, char *fmt, int num){
	char fname[256];
	
	sprintf(fname, fmt, num);
	cout<<"writing: "<<fname<<endl;
	
	fp = fopen(fname, "w");
	
	//include files
	fprintf(fp, "#include \"%s\"\n", POVRAY_INC_FILE);
	
	//load settings
	if(lua != NULL){
		lua_getglobal(lua, "setCamPos");
		lua_pushnumber(lua, num);
		if(lua_pcall(lua, 1, 3, 0)){
			fprintf(stderr, "can't exec setCamPos(): %s\n", lua_tostring(lua, -1));
			getchar();
		}
		
		float x,y,z;
		x = y = z = 0.0;
		
		if(lua_isnumber(lua, -1)){
			x = lua_tonumber(lua, -1);
		}
		lua_pop(lua, 1);
		if(lua_isnumber(lua, -1)){
			y = lua_tonumber(lua, -1);
		}
		lua_pop(lua, 1);
		if(lua_isnumber(lua, -1)){
			z = lua_tonumber(lua, -1);
		}
		lua_pop(lua, 1);
	}
	
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


