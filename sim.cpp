#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

#define OUTPUT_INTERVAL	10

int DIM		= 2;
int nP		= 6;
double DT	= 0.1;
double endtime	= 10000.0;

double *Acc, *Vel, *Pos;
double *Mass;

void init();
void CalcAcc();
void step();
void save(int num, double time);

int main(int argc, char **argv){
	double time = 0.0;
	
	init();
	
	Mass[0]		= 100000.0;
	Pos[0*3  ]	= 0.0;
	Pos[0*3+1]	= 0.0;
	Pos[0*3+2]	= 0.0;
	Vel[0*3+1]	= 0.0;
	
	Pos[1*3  ]	= 500.0;
	Pos[1*3+1]	= -750.0;
	Pos[1*3+2]	= 0.0;
	Vel[1*3  ]	= -10.0;
	Vel[1*3+1]	= 2.0;
	Mass[1]		= 0.001;
	
	Pos[2*3  ]	= 200.0;
	Pos[2*3+1]	= 250.0;
	Vel[2*3  ]	= -6;
	Mass[2]		= 5;
	
	Pos[3*3  ]	= 300;
	Pos[3*3+1]	= 400;
	Vel[3*3  ]	= -5;
	Mass[3]		= 5;
	
	Pos[4*3  ]	= -500;
	Pos[4*3+1]	= 0;
	Vel[4*3+1]	= -10;
	Mass[4]		= 200;
	
	Pos[5*3  ]	= 250;
	Pos[5*3+1]	= 0.0;
	Vel[5*3+1]	= -10;
	Mass[5]		= 500;	
	
	int i=0, j=0;
	
	while(1){
		if(time >= endtime) break;
//		cout<<"time:"<<time<<endl;
		if(i%OUTPUT_INTERVAL == 0){
			save(j, time);
			j++;
		}
		step();
		
		time += DT;
		i++;
	}
	
	cout<<"simulation end."<<endl;
	
	delete Acc;
	delete Vel;
	delete Pos;
	delete Mass;
}

void init(){
	Acc = new double[nP*3];
	Vel = new double[nP*3];
	Pos = new double[nP*3];
	
	Mass= new double[nP];
	
	for(int i=0;i<nP;i++){
		Mass[i] = 0.0;
		for(int j=0;j<3;j++){
			Acc[i*3+j]	= 0.0;
			Vel[i*3+j]	= 0.0;
			Pos[i*3+j]	= 300.7;
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
				dp[k] = Pos[j*3+k] - p[k];//	cout<<dp[k]<<":"<<Pos[j*3+k]<<","<<p[k]<<":"<<k<<endl;
				dp2[k]= pow(dp[k],2);
				r2   += dp2[k];
				if(dp[k] < 0.0){
					c[k] = -1;
				}else{
					c[k] = 1;
				}
				
			}
			r  = sqrt(r2);
			if(dp2[0] < 0.000001){
				if(dp2[1] < 0.000001){
//					if(dp2[2] < 0.000001){
						cout<<"衝突:"<<i<<","<<j<<endl;
//					}
					
				}
				a[1] += m * c[1] / dp2[1];
		//		a[2] += m * c[2] / dp2[2];
			}else if(dp2[1] < 0.000001){
				a[0] += m * c[0] / dp2[0];
		//		a[2] += m * c[2] / dp2[2];
//			}else if(dp2[2] < 0.000001){
//				a[0] += m * c[0] / dp2[0];
		//		a[1] += m * c[1] / dp2[1];
			}else{
				double aa = (m / r2) / r;
				for(int k=0;k<3;k++){
					a[k] += aa * dp[k];
				}
			}
			
		}
		
		for(int k=0;k<3;k++){
			Acc[i*3+k] = a[k];
//			cout<<a[k];
		}
		
	}
}

void step(){
	for(int i=0;i<nP;i++){
		CalcAcc();
		
		Vel[i*3  ] += Acc[i*3  ] * DT;
		Vel[i*3+1] += Acc[i*3+1] * DT;
		Vel[i*3+2] += Acc[i*3+2] * DT;
		
		Pos[i*3  ] += Vel[i*3  ] * DT;
		Pos[i*3+1] += Vel[i*3+1] * DT;
		Pos[i*3+2] += Vel[i*3+2] * DT;
	}
}

void save(int num, double time){
	FILE *fp;
//	ofstream ofs;
	stringstream fname;
	fname<<"out"<<setw(5)<<setfill('0')<<num<<".prof";
	
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
		fprintf(fp, "%f %f %f ", Pos[i*3], (float)Pos[i*3+1], (float)Pos[i*3+2]);
		fprintf(fp, "%f %f %f ", (float)Vel[i*3], (float)Vel[i*3+1], (float)Vel[i*3+2]);
		fprintf(fp, "%f ", 1.0);	//radius
		fprintf(fp, "%d ", i);	//id
		fprintf(fp, "%d ", 1);	//type
		fprintf(fp, "%f\n", 1.0);//val
	}
	
	fclose(fp);
	
}


