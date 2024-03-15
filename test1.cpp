#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>

//

//创建线程私有变量
struct sub_sum
{
	char padding[56];
	double val;

};
sub_sum* sum;

void* cal(void* arg);

typedef struct {
	double rad;
	long long max_n;
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
	long long n = atoi(argv[2]);
	int thread_num = atoi(argv[3]);

	sum = new sub_sum[thread_num];
	args* arg = new args;
	//创建线程
	//线程编号
	pthread_t* pid = new pthread_t[thread_num];
	for (int i = 0; i < thread_num; i++)
	{
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
		sum_thread += sum[i].val;
	}
	delete[]pid;
	return 0;
}
void* cal(void* farg)
{
	args* arg = (args*)farg;

	sum[arg->begin].val = 0.0;
	for (int i = arg->begin; i <= arg->max_n; i += arg->step) {
		double tmp = 1.0;
		for (int j = 1; j <= 2 * i + 1; j++) {
			tmp *= arg->rad / j;
		}
		if (i % 2 > 0) {
			sum[arg->begin].val -= tmp;
		}
		else {
			sum[arg->begin].val += tmp;
		}
	}
	return NULL;
}
