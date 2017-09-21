#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

#define COL_DISTANCE	0.0000001

#define OUTPUT_INTERVAL	1
#define SLACK_INTERVAL	20
#define OUTPUT_DIR	"out/"
#define DEFAULT_RADIUS	pow(10, 5);

#define EULAR
//#define LEAP_FROG

int DIM		= 2;
int nP		= 2;
double DT	= 0.000001;
double endtime	= 100.0;
const double G	= 6674.28;	//gravity 

double *Acc, *Vel, *Pos;
double *Vel_half;
double *Mass, *Rad;

void init();
void CalcAcc();
void step();
void save(int num, double time);

int main(int argc, char **argv){
	double time = 0.0;
	
	init();
	
	// とりあえず、質量は地球を100,速度はkm/sで設定(単位はあとでまとめて揃える)
	
	// PosはAUで設定
	
	// 太陽
	Mass[0]		= 33294600.0;
	Pos[0*3  ]	= 0.0;
	Pos[0*3+1]	= 0.0;
	Pos[0*3+2]	= 0.0;
	Vel[0*3  ]	= 0.0;
	Vel[0*3+1]	= 0.0;
	Vel[0*3+2]	= 0.0;
/*	
	// 水星
	Mass[1]		= 5.527;
	Pos[1*3  ]	= 0.3871;
	Pos[1*3+1]	= 0.0;
	Pos[1*3+2]	= 0.0;
	Vel[1*3  ]	= 0.0;
	Vel[1*3+1]	= -47.36;
	Vel[1*3+2]	= 0.0;
	
	// 金星
	Mass[2]		= 81.50;
	Pos[2*3  ]	= 0.7233;
	Pos[2*3+1]	= 0.0;
	Pos[2*3+2]	= 0.0;
	Vel[2*3  ]	= 0.0;
	Vel[2*3+1]	= -35.02;
	Vel[2*3+2]	= 0.0;
	
	// 地球
	Mass[3]		= 100;
	Pos[3*3  ]	= 1.0;
	Pos[3*3+1]	= 0.0;
	Pos[3*3+2]	= 0.0;
	Vel[3*3  ]	= 0.0;
	Vel[3*3+1]	= -29.78;
	Vel[3*3+2]	= 0.0;
	
	// 火星
	Mass[4]		= 10.74;
	Pos[4*3  ]	= 1.5237;
	Pos[4*3+1]	= 0.0;
	Pos[4*3+2]	= 0.0;
	Vel[4*3  ]	= 0.0;
	Vel[4*3+1]	= -24.08;
	Vel[4*3+2]	= 0.0;
*/	
	// 木星
	Mass[1]		= 31783.00;
	Pos[1*3  ]	= 5.2026;
//	Pos[1*3+1]	= 0.01;
//	Pos[1*3+2]	= -0.01;
	Vel[1*3  ]	= 0.0;
	Vel[1*3+1]	= -13.06;
	Vel[1*3+2]	= 0.0;
/*	
	// 土星
	Mass[6]		= 9516.00;
	Pos[6*3]	= 9.5549;
//	Pos[6*3+1]	= 0.001;
//	Pos[6*3+2]	= 0.001;
	Vel[6*3  ]	= 0.0;
	Vel[6*3+1]	= -9.65;
	Vel[6*3+2]	= 0.0;
	
	// 天王星
	Mass[7]		= 1451.00;
	Pos[7*3]	= 19.2184;
//	Pos[7*3+1]	= 0.01;
//	Pos[7*3+2]	= 0.01;
	Vel[7*3  ]	= 0.0;
	Vel[7*3+1]	= -6.81;
	Vel[7*3+2]	= 0.0;
	
	// 海王星
	Mass[8]		= 1715.00;
	Pos[8*3]	= 30.1104;
//	Pos[8*3+1]	= 0.0001;
//	Pos[8*3+2]	= 0.0001;
	Vel[8*3  ]	= 0.0;
	Vel[8*3+1]	= -5.44;
	Vel[8*3+2]	= 0.0;
*/	
	int i=0, j=0;
	for(i=0;i<nP;i++){
		Mass[i] = Mass[i] * 59720 * 0.01;
		Pos[i*3] = Pos[i*3] * 14959.78707;
		Vel[i*3+1] *= 1000;
		
		cout<<"Mass:"<<Mass[i]<<" Pos:"<<Pos[i*3]<<endl;
	}
	getchar();

	i = 0;
	j = 0;
	
	while(1){
		if(time >= endtime) break;
//		cout<<"time:"<<time<<endl;
		if(i%OUTPUT_INTERVAL == 0){
			save(j, time);
			if(j%SLACK_INTERVAL){
				char str[256];
//				sprintf(str, "nohup ~/python/slack/sksat_bot/post.py simulation \"time:%lf save:%d\" &", time, j);
//				system(str);
			}
			j++;
		}
		step();
		
		time += DT;
		i++;
	}
	
	cout<<"simulation end."<<endl;
	
	delete[] Acc;
	delete[] Vel;
	delete[] Vel_half;
	delete[] Pos;
	delete[] Mass;
	delete[] Rad;
}

void init(){
	Acc = new double[nP*3];
	Vel = new double[nP*3];
	Vel_half = new double[nP*3];
	Pos = new double[nP*3];
	
	Mass= new double[nP];
	Rad = new double[nP];
	
	for(int i=0;i<nP;i++){
		Mass[i] = 0.0;
		Rad[i]	= DEFAULT_RADIUS;
		for(int j=0;j<3;j++){
			Acc[i*3+j]	= 0.0;
			Vel[i*3+j]	= 0.0;
			Pos[i*3+j]	= 0.0;
		}
	}
}

void CalcAcc(){
	double p[3];
	double a[3];
	double dp[3], dp2[3];
	double m;
	double r,r2;
	double c[3];
	
	for(int i=0;i<nP;i++){
		p[0] = Pos[i*3  ];
		p[1] = Pos[i*3+1];
		p[2] = Pos[i*3+2];
		
		a[0] = 0.0;
		a[1] = 0.0;
		a[2] = 0.0;
		
		for(int j=0;j<nP;j++){
			if(i==j) continue;
			m  = Mass[j];
			if(m==0.0) continue;
			r2 = 0.0;
			for(int k=0;k<3;k++){
				dp[k] = Pos[j*3+k] - p[k];
				dp2[k]= pow(dp[k],2);
				r2   += dp2[k];
				if(dp[k] < 0.0){
					c[k] = -1;
				}else{
					c[k] = 1;
				}
				
			}
			r  = sqrt(r2);
			
			bool xcol=0, ycol=0, zcol=0;
			xcol = (dp2[0] < COL_DISTANCE);
			ycol = (dp2[1] < COL_DISTANCE);
			zcol = (dp2[2] < COL_DISTANCE);
			
			if(xcol && ycol && zcol){	// x & y & z
				cout<<"衝突:"<<i<<","<<j<<endl;
			}else if(xcol){
				if(ycol){	// x & y
					a[2] += m * c[2] / dp2[2];
				}else if(zcol){	// x & z
					a[1] += m * c[1] / dp2[1];
				}else{
					a[1] += m * c[1] / dp2[1];
					a[2] += m * c[2] / dp2[2];
				}
			}else if(ycol){
				if(zcol){	// y & z
					a[0] += m * c[0] / dp2[0];
				}else{
					a[0] += m * c[0] / dp2[0];
					a[2] += m * c[2] / dp2[2];
				}
			}else if(zcol){
				a[0] += m * c[0] / dp2[0];
				a[1] += m * c[1] / dp2[1];
			}else{
				double aa = (m / r2) / r;
				for(int k=0;k<3;k++){
					a[k] += aa * dp[k];
				}
			}
			
		}
		
		for(int k=0;k<3;k++){
			a[k] = a[k] * G;
			Acc[i*3+k] = a[k];
			cout<<a[k]<<endl;
		}
		
	}
}

int step_num = 0;

void step(){
//	if(step_num == 0) CalcAcc();
	step_num++;
	for(int i=0;i<nP;i++){
#ifdef EULAR
		Vel[i*3  ] += Acc[i*3  ] * DT;
		Vel[i*3+1] += Acc[i*3+1] * DT;
		Vel[i*3+2] += Acc[i*3+2] * DT;

		Pos[i*3  ] += Vel[i*3  ] * DT;
		Pos[i*3+1] += Vel[i*3+1] * DT;
		Pos[i*3+2] += Vel[i*3+2] * DT;
		
		CalcAcc();
#endif

#ifdef LEAP_FROG

		double vh[3];
		for(int j=0;j<3;j++){
			if(step_num == 1){
				vh[j] = Vel[i*3+j] + (Acc[i*3+j] * 0.5);
			}else{
				vh[j]   = Vel_half[i*3+j] + (Acc[i*3+j] * DT);
			}
			Pos[i*3+j] += vh[j] * DT;
			Vel_half[i*3+j] = vh[j];
		}
	}
	CalcAcc();
	for(int i=0;i<nP;i++){
		for(int j=0;j<3;j++){
			Vel[i*3+j]  = Vel_half[i*3+j] + (Acc[i*3+j] * DT * 0.5);
		}
#endif
	}
}

void save(int num, double time){
	FILE *fp;
//	ofstream ofs;
	stringstream fname;
	fname<<OUTPUT_DIR<<"out"<<setw(5)<<setfill('0')<<num<<".prof";
	
	cout<<"out: "<<fname.str()<<endl;
	
	fp = fopen(fname.str().c_str(), "w");
//	ofs.open(fname.str().c_str(), std::ios::out);
	
//	ofs<<time<<endl;
//	ofs<<nP<<endl;
	
	fprintf(fp, "%f\n", time);
	fprintf(fp, "%d\n", nP);
	
	for(int i=0;i<nP;i++){
//		cout<< (float)Pos[i*3] << Pos[i*3+1] << Pos[i*3+2]<<endl;
//		if(ofs.fail())	cout<<"fail!"<<endl;
		fprintf(fp, "%f %f %f ", (float)Pos[i*3], (float)Pos[i*3+1], (float)Pos[i*3+2]);
		fprintf(fp, "%f %f %f ", (float)Vel[i*3], (float)Vel[i*3+1], (float)Vel[i*3+2]);
		fprintf(fp, "%lf ", Rad[i]);	//radius
		fprintf(fp, "%d ", i);	//id
		fprintf(fp, "%d ", 1);	//type
		fprintf(fp, "%f\n", 1.0);//val
	}
	
	fclose(fp);
	
}


