#include "rAlgo.h"

#define NS_SIZE 1000

char **selfSet;
char **detector;
char **nSelf;
int *rvals;
int dnum[6]={200, 400, 600, 800, 1100, 1200};
int dtimes=6;

int getDetector(int r1, int rc, char *str)
{
	int r;
	while(1)
	{
		generateRandStr(str);
		r=rAlgo(str, selfSet, r1, rc+1-r1);
		if(r!=rc+1)
			return r;
	}
}

void initDet(int r1, int rc)
{
	int i, r;
	for(i=0; i<1200; i++)
	{
		r=getDetector(r1, rc, detector[i]);
		rvals[i]=r;
		if(i%10==0)
		{
			printf("%d------------------->%d\n", rc, i);
			fflush(stdout);
		}
	}
}

int calcPs(int num)
{
	int i, j, count=0, flag;
	for(i=0; i<NS_SIZE; i++)
	{
		flag=0;
		for(j=0; j<num; j++)
		{
			if(match(detector[j], nSelf[i], rvals[j]))
			{
				count+=1;
				flag=1;
				break;
			}
		}
	}
	return count;
}

int inSelf(char *str)
{
	int i, j, flag;
	for(i=0; i<LINE_NUM; i++)
	{
		flag=0;
		for(j=0; j<STR_LENGTH; j++)
		{
			if(str[j]!=selfSet[i][j])
			{
				flag=1;
				break;
			}
		}
		if(flag==0)
			return 1;
	}
	return 0;
}

void generateNS()
{
	int i;
	char *tmp;
	for(i=0; i<NS_SIZE; i++)
	{
		tmp=nSelf[i];
		generateRandStr(tmp);
		while(inSelf(tmp))
			generateRandStr(tmp);
	}
}

int main(int argc, char **argv)
{
	int i, r, tag, rc, j, tmp;
	FILE *fout;

	srand((unsigned)time(NULL));

	selfSet=(char **)malloc(sizeof(char *)*LINE_NUM);
	for(i=0; i<LINE_NUM; i++)
		selfSet[i]=(char *)malloc(sizeof(char)*(STR_LENGTH+1));
	detector=(char **)malloc(sizeof(char *)*1200);
	rvals=(int *)malloc(sizeof(int)*1200);
	for(i=0; i<1200; i++)
		detector[i]=(char *)malloc(sizeof(char)*(STR_LENGTH+1));
	nSelf=(char **)malloc(sizeof(char *)*NS_SIZE);
	for(i=0; i<NS_SIZE; i++)
		nSelf[i]=(char *)malloc(sizeof(char)*(STR_LENGTH+1));

	loadSelfSet("./randomized/sample", selfSet);

	generateNS();

	fout=fopen("./randomized/case3.out", "w");
	for(rc=r1min; rc<=rcmax; rc++)
	{
		initDet(r1min, rc);
		for(j=0; j<dtimes; j++)
		{
			tmp=calcPs(dnum[j]);
			printf("rc=%d, nr0=%d, ps=%d\n", rc, dnum[j], tmp);
			fprintf(fout, "rc=%d, nr0=%d, ps=%d\n", rc, dnum[j], tmp);
		}

	}
	fflush(fout);
	fclose(fout);
	return 0;
}
