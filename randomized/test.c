#include "rAlgo.h"

char **selfSet;

int getDetector(int r1, int rc)
{
	char temp[STR_LENGTH+1];
	int r;
	while(1)
	{
		generateRandStr(temp);
		//printf("%s\t", temp);
		r=rAlgo(temp, selfSet, r1, rc+1-r1);
		//printf("%d\n", r);
		if(r!=rc+1)
			return r;
	}
}

int main()
{
	int i;
	selfSet=(char **)malloc(sizeof(char *)*LINE_NUM);
	for(i=0; i<LINE_NUM; i++)
		selfSet[i]=(char *)malloc(sizeof(char)*STR_LENGTH);
	loadSelfSet("D:/workspace/rAdjust/randomized/sample", selfSet);

	for(i=0; i<200; i++)
	{
		printf("%d\n", getDetector(22, 29));
		fflush(stdout);
	}
	return 0;
}
