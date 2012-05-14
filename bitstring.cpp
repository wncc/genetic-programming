//
//  main.cpp
//  geneticprogrammingforbitstrings
//
//  Created by anirudh vemula on 06/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include<iostream>
#include<stdlib.h>
#include<ctime>
using namespace std;

//Initial declarations for global variables

#define NUMBEROFORGANISMS 1000
#define NUMBEROFGENES 10
#define ALLELES 9
#define MUTATIONRATE 0.001
#define MAXIMUMFITNESSPOSSIBLE NUMBEROFGENES
#define TRUE 1
#define FALSE 0

//global variables used in all the functions below

char CURRENTGENERATION[NUMBEROFORGANISMS][NUMBEROFGENES];
char NEXTGENERATION[NUMBEROFORGANISMS][NUMBEROFGENES];
int ORGANISMFITNESS[NUMBEROFORGANISMS];
int TOTALOFFITNESSES;

//model solution required

char MODELORGANISM[NUMBEROFGENES] = {1,2,0,4,2,1,3,2,2,0};

//prototypes of all the functions used in the main function

int start(void);
void initializepopulation(void);
int evaluatepopulation(void);
void producenextgeneration(void);
int selectorganism(void);
void initrandomseed();

//main function

int main()
{
    
    initrandomseed();
    int FINALGENERATION;
    FINALGENERATION=start();
    cout<<"the final generation is  " << FINALGENERATION<<endl;
    return 0;
}

//start function

int start(void)
{
    int GENERATIONS=1;
    int PERFECTGENERATION=FALSE;
    initializepopulation();
    while(TRUE)
    {
        PERFECTGENERATION=evaluatepopulation();
        if(PERFECTGENERATION==TRUE) return GENERATIONS;
        producenextgeneration();
        GENERATIONS++;
    }
}

//initializepopulation function

void initializepopulation(void)
{
    int ORGANISM;
    int GENE;
    
    for(ORGANISM=0;ORGANISM<NUMBEROFORGANISMS;ORGANISM++)
    {
        for(GENE=0;GENE<NUMBEROFGENES;GENE++)
        {
            //initrandomseed();
            CURRENTGENERATION[ORGANISM][GENE]=rand()%ALLELES;
        }
    }
}

//evaluatepopulation function

int evaluatepopulation(void)
{
    int ORGANISM;
    int GENE;
    int CURRENTORGANISMFITNESS;
    
    TOTALOFFITNESSES=0;
    
    for(ORGANISM=0;ORGANISM<NUMBEROFORGANISMS;ORGANISM++)
    {
        CURRENTORGANISMFITNESS=0;
        for(GENE=0;GENE<NUMBEROFGENES;GENE++)
        {
            if(CURRENTGENERATION[ORGANISM][GENE]==MODELORGANISM[GENE])
            {
                CURRENTORGANISMFITNESS++;
            }
        }
        
        ORGANISMFITNESS[ORGANISM]=CURRENTORGANISMFITNESS;
        TOTALOFFITNESSES+=CURRENTORGANISMFITNESS;
        if(CURRENTORGANISMFITNESS==MAXIMUMFITNESSPOSSIBLE) return TRUE;
        
        
    }
    return FALSE;
}

//producenextgeneration function

void producenextgeneration(void)
{
    int ORGANISM;
    int GENE;
    int MALEPARENT;
    int FEMALEPARENT;
    int EXCHANGEPOINT;
    int MUTATETHISGENE;
    
    for(ORGANISM=0;ORGANISM<NUMBEROFORGANISMS;ORGANISM++)
    {
        MALEPARENT=selectorganism();
        FEMALEPARENT=selectorganism();
        //initrandomseed();
        EXCHANGEPOINT=rand()%NUMBEROFGENES;
        
        for(GENE=0;GENE<NUMBEROFGENES;GENE++)
        {
            MUTATETHISGENE=rand()%(int)(1.0/MUTATIONRATE);
            if(MUTATETHISGENE==0)
            {
                //initrandomseed();
                NEXTGENERATION[ORGANISM][GENE]=rand()%ALLELES;
            }
            else
            {
                if(GENE<EXCHANGEPOINT)
                {
                    NEXTGENERATION[ORGANISM][GENE]=CURRENTGENERATION[MALEPARENT][GENE];
                }
                else
                {
                    NEXTGENERATION[ORGANISM][GENE]=CURRENTGENERATION[FEMALEPARENT][GENE];
                
                }
                
            }
        }
    }
    
    for(ORGANISM=0;ORGANISM<NUMBEROFORGANISMS;ORGANISM++)
    {
        for(GENE=0;GENE<NUMBEROFGENES;GENE++)
        {
            CURRENTGENERATION[ORGANISM][GENE]=NEXTGENERATION[ORGANISM][GENE];
            
        }
    }
}

//selectorganism function

int selectorganism(void){
    int ORGANISM;
    int RUNNINGTOTAL;
    int RANDOMSELECTPOINT;
    
    RUNNINGTOTAL = 0;
    //initrandomseed();
    RANDOMSELECTPOINT = rand() % (TOTALOFFITNESSES + 1);
    
    for(ORGANISM=0; ORGANISM<NUMBEROFORGANISMS; ++ORGANISM){
        RUNNINGTOTAL += ORGANISMFITNESS[ORGANISM];
        if(RUNNINGTOTAL >= RANDOMSELECTPOINT) return ORGANISM;
    }
}

//initrandomseed function

void initrandomseed() {
    static bool initialized = false;
    if (!initialized) {
        srand(int(time(NULL)));
        initialized = true;
    }
}





