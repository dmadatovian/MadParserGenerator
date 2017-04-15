/*
    MadParserGenerator - This program generates a parser from a context
    free grammar and tokens defined by the user.

    Copyright (C) 2017  Daniel Gabriel Madatovian

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include "ReadFSAFromFile.h"
#include <stdlib.h>
#include <string.h>

/** This function parses a finite state automata from an input file.
blah blah blah more description.
*/
FiniteStateAutomata* parseFSAFromFile(char *filename){
	FILE *file = fopen(filename,"r");
	int **stateTable;
	int stateCount = countStates(file);
	stateTable=initializeStateTable(stateCount,10);
	rewind(file);
	if(stateTable != NULL) readStateTransitions(file,stateTable);
	fclose(file);
	FiniteStateAutomata *toReturn = (FiniteStateAutomata*)malloc(sizeof(FiniteStateAutomata));
	toReturn->stateTable=stateTable;
	toReturn->currentState=0;
	toReturn->finalStates=NULL;
	return toReturn;
}

int** initializeStateTable(int stateCount,int inputCount){
	if(stateCount == 0) return NULL;
	int **stateTable = (int**)malloc((stateCount)*(sizeof(int*)));
	for(int i =0; i < stateCount;++i){
		stateTable[i]=(int*)malloc(inputCount*sizeof(int));
		for(int j = 0; j < inputCount;++j){
			stateTable[i][j] = -1;
		}	
	}
	return stateTable;
}

int countStates(FILE *file){
	int count=0;
	char buffer[20];
	int *sourceState=(int*)malloc(sizeof(int));
	int *input=(int*)malloc(sizeof(int));
	int *targetState=(int*)malloc(sizeof(int));
	char *states = (char*)malloc(255*sizeof(char));
	while(fscanf(file,"%s",buffer)!=EOF) {
		printf("buffer:%s\n",buffer);
		if(strncmp(buffer,"-",1)==0){
			count=0;
			break;
		}
		printf("TEST3, %d\n",count);
		fscanf(file,"%d %d,%d",sourceState,input,targetState);
		printf("%d %d,%d\n",*sourceState,*input,*targetState);
		if(states[*sourceState]==0){
			states[*sourceState]=1;
			++count;
			printf("%d - %d\n",*sourceState,count);	
		}
	}
	printf("Counting Loop Finished\n");
	free(sourceState);
	free(input);
	free(targetState);
	free(states);
	return count;
}

void readStateTransitions(FILE *file,int **stateTable){
	int *sourceState = (int*)malloc(sizeof(int));
	int *input = (int*)malloc(sizeof(int));
	int *targetState = (int*)malloc(sizeof(int));
	while(fscanf(file,"%d %d,%d",sourceState,input,targetState)!=EOF){
		stateTable[*sourceState][*input]=(*targetState);	
	}
	free(sourceState);
	free(input);
	free(targetState);
}
