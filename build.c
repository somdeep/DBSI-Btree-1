#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
	if(argc<4)
	{
		printf("\nArguments format : keys probes fanout");
		exit(0);
	}

	int k=atoi(argv[1]);
	int p=atoi(argv[2]);
	
	int levels=argc-3;
	int i=0;
	int fanout[levels];

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


	int numkey=levels-1;

	printf("Passed k:%d p:%d levels:%d\n",k,p,levels);

	int *levelArray[levels];
	int arraySize[levels];
	int prev=1;

	//now building array of arrays
	for(i=0;i<levels;i++)
	{
		arraySize[i]=prev*(fanout[i]-1);
		
		prev=arraySize[i]+arraySize[i]/(fanout[i]-1);
		
		printf("%d\n",arraySize[i]);
	}


	return(0);
       
}
