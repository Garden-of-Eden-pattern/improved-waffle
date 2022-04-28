/*
 * ft.c
 *
 *  Created on: 2022/04/27
 *      Author: dyuia
 */



#include <stdio.h>
#include <math.h>


double func_a(double, double);
double func_b(double, double);
double func_origin(double);

double func_cos(double, double, double);
double func_sin(double, double, double);

int main(void){



	double x_fake = -M_PI; //積分の際に使う見かけのx

	double y = 0;

	double x = 0;

	double n_end = 50;

	double h = 0.000001;



	/*a_0を求める*/
	do{

		y = y + func_origin(x_fake)*h;

		x_fake = x_fake + h;

	}while(x_fake <= M_PI);

	y = y/(2*M_PI);

	x_fake = -M_PI; //積分範囲の初期化


	FILE * fp = NULL;

	fopen_s(&fp, "result_of_FT.csv", "a");


	for(x=0; x <=5.0; x=x+0.001){

	for(int n = 1; n <= n_end; n++){

		double a_n = 0;

		double b_n = 0;

	/*a_nを求める+++++++++++++++++++++++++++++++++++++++++*/
	do{

		a_n = a_n + func_a(n,x_fake)*h;

		x_fake = x_fake + h;

	}while(x_fake <= M_PI);

	a_n = a_n/M_PI;
	/*++++++++++++++++++++++++++++++++++++++++++++++++++++*/



	x_fake = -M_PI;  //積分範囲の初期化



	/*b_nを求める++++++++++++++++++++++++++++++++++++++++++*/
	do{

		b_n = b_n + func_b(n,x_fake)*h;

		x_fake = x_fake + h;

	}while(x_fake <= M_PI);

	b_n = b_n/M_PI;
	/*++++++++++++++++++++++++++++++++++++++++++++++++++++*/



	y = y + func_cos(n,x,a_n) + func_sin(n,x,b_n);

	}

	fprintf(fp," %lf , %lf \n",x,y);

	}

	fclose(fp);

	return 0;

}

double func_origin(double x_fake){

	return(x_fake);  //フーリエ変換したい関数

}


double func_a(double n,double x_fake){

	return(func_origin(x_fake)*cos(n*x_fake)); // a_nを求める際の積分の中身の関数

}

double func_b(double n, double x_fake){

	return(func_origin(x_fake)*sin(n*x_fake)); // b_nを求める際の積分の中身の関数

}

double func_cos(double n, double x, double a_n){

	return(a_n*cos(n*x));

}

double func_sin(double n, double x, double b_n){

	return(b_n*sin(n*x));

}

