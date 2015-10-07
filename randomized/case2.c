#include "rAlgo.h"

#define DET_NUM 500

char **selfSet;
int *matrix, ma;

void initMat()
{
	int i, j;
	matrix=(int *)malloc(sizeof(int)*ma);
	for(i=0; i<ma; i++)
		matrix[i]=0;
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
	int i, r, tag;
	FILE *fout;

	srand((unsigned)time(NULL));

	selfSet=(char **)malloc(sizeof(char *)*LINE_NUM);
	for(i=0; i<LINE_NUM; i++)
		selfSet[i]=(char *)malloc(sizeof(char)*(STR_LENGTH+1));

	loadSelfSet("D:/workspace/rAdjust/randomized/sample", selfSet);
	ma=rcmax-r1min+1;

	initMat();

	for(i=0; i<DET_NUM; i++)
	{
		if(i%10==0)
		{
			printf("%d\n", i);
			fflush(stdout);
		}
		tag=getDetector(r1min, rcmax);
		matrix[tag-r1min]+=1;
	}

	fout=fopen("D:/workspace/rAdjust/randomized/case2.out","w");
	for(r=r1min; r<=rcmax; r++)
		printf("r=%d      %d\n", r, matrix[r-r1min]);
	for(r=r1min; r<=rcmax; r++)
		fprintf(fout, "r=%d      %d\n", r, matrix[r-r1min]);
	fflush(fout);
	fclose(fout);

	return 0;
}
