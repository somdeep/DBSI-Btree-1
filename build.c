#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "random.c"


int main(int argc, char* argv[])
{
	if(argc<4)
	{
		printf("\nArguments format : keys probes fanout");
		exit(0);
	}

	int32_t keys=atoi(argv[1]);
	int32_t probes=atoi(argv[2]);
	
	int32_t levels=argc-3;
	int32_t i=0;
	int32_t j=0;
	int32_t fanout[levels];
	int32_t lookfor = 10;
	int32_t foundindex;


	
	while(i<levels)
	{
		fanout[i]=atoi(argv[i+3]);	
		if(fanout[i]>17 || fanout[i]<2)
		{
			printf("Fanout values must be between 2 and 17\n");
			exit(0);
		}
		printf("%d\n",fanout[i] );
		i++;

	}


	int32_t numkey=levels-1;

	printf("Passed k:%d p:%d levels:%d\n",keys,probes,levels);

	int32_t *levelArray[levels];
	int32_t arraySize[levels];
	int32_t prev=1;
	int32_t treesize=0;
	int32_t current[levels];//points to most recently filled entry in each level
	int32_t nodesize[levels];
	int32_t nodecount[levels];//store number of nodes at each level
	//at any point of time, only one node is being filled on each level, this stores the extent to which that node is filled
	void* memorypt;

	//now building array of arrays
	for(i=0;i<levels;i++)
	{
		arraySize[i]=prev*(fanout[i]-1);
		treesize+=arraySize[i];
		//allocate size
		posix_memalign(&memorypt,16,sizeof(int32_t)*arraySize[i]);
		levelArray[i]=(int32_t *)memorypt;
		current[i]=0;
		nodesize[i]=0;
		nodecount[i]=
		prev=arraySize[i]+arraySize[i]/(fanout[i]-1);
		printf("Level %d maximum size : %d\n",i,arraySize[i]);
	}

	if(keys>treesize)
	{	
		printf("Too many keys\n");
		exit(1);
	}


	//calling in functions from program for obtaining random numbers
	rand32_t *gen = rand32_init(time(NULL));
	size_t n = keys;
	int32_t *a = generate_sorted_unique(n, gen);



	int32_t* value;
	//check for insert
	for (i = 0; i <levels ; i++)
	{
		value=levelArray[i];
		for (j = 0; j < arraySize[i]; j++)
		{
			*value=INT32_MAX;
			value++;
		}
	}


	printf("Total (maximum) number of keys possible : %d\n",treesize);
	printf("\n\nInserting and then printing tree\n\n");



	//insertion : building index

	int l=levels-1;//this holds the current level, always starts with the last level
	printf("levels : %d\n",levels );
	for (i = 0; i < keys; ++i)
	{	
		l=levels-1;//at the start of each iteration, we begin from the last level, and attempt to fill any available spaces
		while((fanout[l]-1) <= nodesize[l])
		{
			nodesize[l]=0;
			l--;
			if(l<0)
			{
				printf("\nToo many keys in insertion");
				exit(0);
			}
		}

		value=levelArray[l];
		value=value+(current[l]);

		*value=*a;
		a++;
		printf("%d  %d\n",value,*value);
		current[l]++;
		nodesize[l]++;		
	}


	for (i = 0; i<levels; ++i)
	{
		value=levelArray[i];
		printf("Level %d -----> ",i);
		for (j = 0; j < arraySize[i]; ++j)
		{
			printf(" %d ", *value);
			value++;
		}
		printf("\n\n");
	}

	if(*levelArray[0] == INT32_MAX)
	{
		printf("Too few keys, empty root\n");
		exit(0);
	}

	free(gen);

	return(0);
       
}
