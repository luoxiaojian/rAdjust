#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SELFSET_SIZE 150
#define STR_LENGTH 22
#define TOTAL_NUM (1<<STR_LENGTH)
#define R1 8
#define C 5
#define START 0
#define END TOTAL_NUM
int selfSet[SELFSET_SIZE];


int matchint(int num1, int num2, int r)
{
	int tester=(1<<r)-1;
	int key1, key2;
	int i, j;
	for(i=0; i<=STR_LENGTH-r; i++)
	{
		key1=num1>>i;
		key1=key1&tester;
		for(j=0; j<=STR_LENGTH-r; j++)
		{
			key2=num2>>j;
			key2=key2&tester;
			if(key1==key2)
			{
				return 1;
			}
		}
	}
	return 0;
}
int transferInput(char *str)
{
	int i=0;
	int num=0, bit;
	for(;i<STR_LENGTH; i++)
	{
		bit=(int)(str[i]-'0');
		num=num<<1;
		num=num|bit;
	}
	return num;
}

void loadSelfSet(char *filename)
{
	int i;
	char temp[STR_LENGTH+1];
	FILE *fin=fopen(filename, "r");
	for(i=0; i<SELFSET_SIZE; i++)
	{
		fscanf(fin, "%s", temp);
		selfSet[i]=transferInput(temp);
	}
}

int inSelfSet(int num)
{
	int i;
	for(i=0; i<SELFSET_SIZE; i++)
	{
		if(num==selfSet[i])
			return 1;
	}
	return 0;
}

void rAlgo()
{
	char filename[32];
	FILE *fout, *fNS;
	int i, r, flag, j, count=0;
	sprintf(filename, "./deterministic/output_%d_%d.dat", START, END);
	fout=fopen(filename, "w");
	fNS=fopen("./determinstic/nonSelf", "w");
	for(i=START; i<END; i++)
	{
		if(i%10000==0)
			printf("%d of %d\n", i, TOTAL_NUM);
		flag=1;
		r=R1;
		if(inSelfSet(i))
			continue;
		while((r<R1+C)&&flag)
		{
			flag=0;
			for(j=0; j<SELFSET_SIZE; j++)
			{
				if(matchint(i, selfSet[j], r))
				{
					r=r+1;
					flag=1;
					break;
				}
			}
			if(flag==0)
			{
				count=count+1;
				if(count==1024)
				{
					count=0;
					printf("======================>flush\n");
					fflush(stdout);
					fflush(fout);
				}
				fprintf(fout, "%d\t%d\n", r, i);
				break;
			}
		}
		if(flag==1)
			fprintf(fNS, "%d\n", i);
	}
	fflush(fNS);
	fclose(fNS);
}

int main()
{
	char *filename="./deterministic/sample";
	loadSelfSet(filename);
	rAlgo();
	return 0;
}
