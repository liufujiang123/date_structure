#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>

//

//创建线程私有变量

double* sum;

void* cal(void* arg);

typedef struct {
	double rad;
	int max_n;
	int begin;
	int step;
}args;
//main接受参数
int main(int argc, char* argv[])
{
	if (argc != 4) {
		printf("Parameters error: radian N threads!\n");
		exit(1);
	}
	double rad = atof(argv[1]);
	int n = atoi(argv[2]);
	int thread_num = atoi(argv[3]);

	sum = new double[thread_num];
	for (int i = 0; i < thread_num; sum[i++] = 0);
	args* arg;
	//创建线程
	//线程编号
	pthread_t* pid = new pthread_t[thread_num];
	for (int i = 0; i < thread_num; i++)
	{
		arg = new args;
		//本线程信息
		arg->begin = i;
		arg->max_n = n;
		arg->rad = rad;
		arg->step = thread_num;
		pthread_create(&pid[i], NULL, cal, (void*)arg);
	}
	//等待所有线程结束
	for (int i = 0; i < thread_num; i++) {
		pthread_join(pid[i], NULL);
	}

	double sum_thread = 0;
	for (int i = 0; i < thread_num; i++)
	{
		sum_thread += sum[i];
	}
	delete[]arg;
	delete[]pid;
	return 0;
}
void* cal(void* farg)
{
	args* arg = (args*)farg;

	double val = 0.0;
	for (int i = arg->begin; i <= arg->max_n; i += arg->step) {
		double tmp = 1.0;
		for (int j = 1; j <= 2 * i + 1; j++) {
			tmp *= arg->rad / j;
		}
		if (i % 2 > 0) {
			val -= tmp;
		}
		else {
			val += tmp;
		}
	}

	sum[arg->begin] = val;
	return NULL;
}
