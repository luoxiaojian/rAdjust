#include "rAlgo.h"

#define DET_NUM 200

char **selfSet;

int **matrix, ma;

void initMat()
{
	int i, j;
	matrix=(int **)malloc(sizeof(int *)*ma);
	for(i=0; i<ma; i++)
		matrix[i]=(int *)malloc(sizeof(int)*ma);
	for(i=0; i<ma; i++)
		for(j=0; j<ma; j++)
			matrix[i][j]=0;
}

int getDetector(int r1, int rc)
{
	char temp[STR_LENGTH+1];
	int r;
	while(1)
	{
		generateRandStr(temp);
		r=rAlgo(temp, selfSet, r1, rc+1-r1);
		if(r!=rc+1)
			return r;
	}
}

int main()
{
	int i, j, rc, r1, count, r;

	FILE *fout;

	selfSet=(char **)malloc(sizeof(char *)*LINE_NUM);
	for(i=0; i<LINE_NUM; i++)
		selfSet[i]=(char *)malloc(sizeof(char)*(STR_LENGTH+1));

	loadSelfSet("D:/workspace/rAdjust/randomized/sample", selfSet);
	ma=rcmax-r1min+1;

	initMat();

	printf("init matrix over.\n");
	fflush(stdout);

	matrix[0][0]=DET_NUM;

	for(rc=r1min+1; rc<=rcmax; rc++)
	{
		printf("rc=%d\n", rc);
		fflush(stdout);
		r1=r1min;
		count=0;
		while(count!=DET_NUM)
		{
			r=getDetector(r1, rc);
			matrix[r-r1min][rc-r1min]+=1;
			count+=1;
			if(count%10==0)
			{
				printf("\t%d of %d\n", count, DET_NUM);
				fflush(stdout);
			}
		}
	}

	fout=fopen("D:/workspace/rAdjust/randomized/case1.out","w");
	for(rc=r1min; rc<=rcmax; rc++)
		for(r=r1min; r<=rc; r++)
			printf("r=%d, rc=%d      %d\n", r, rc, matrix[r-r1min][rc-r1min]);
	for(rc=r1min; rc<=rcmax; rc++)
		for(r=r1min; r<=rc; r++)
			fprintf(fout, "r=%d, rc=%d      %d\n", r, rc, matrix[r-r1min][r-r1min]);
	fflush(fout);
	fclose(fout);

	return 0;
}
