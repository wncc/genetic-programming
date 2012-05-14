//
//  main.cpp
//  travellingsalesman
//
//  Created by anirudh vemula on 09/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include<iostream>
#include<stdlib.h>
#include<ctime>
#include<cmath>

using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//global variables
#define NUMBEROFORGANISMS 1000
#define NUMBEROFCITIES 20
#define MUTATIONRATE 0.01
#define CROSSOVERRATE 0.01
#define TRUE 1
#define FALSE 0

#define NUMBEROFGENES NUMBEROFCITIES
#define ALLELES NUMBEROFCITIES
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//global datatypes
int CURRENTGENERATION[NUMBEROFORGANISMS][NUMBEROFGENES];
int NEXTGENERATION[NUMBEROFORGANISMS][NUMBEROFGENES];
int BESTGENERATION[NUMBEROFORGANISMS][NUMBEROFGENES];
float ORGANISMFITNESS[NUMBEROFORGANISMS];
float TOTALOFFITNESSES=0.0;
int BESTROUTE[NUMBEROFGENES];
float MINIMUMFITNESS=1500000.0;
float MINIMUMAVERAGEFITNESS=1500000.0;
float AVERAGEFITNESS;
int BESTORGANISMNUMBER;
int runnumber=0;
int a0[2]={100,100};
int a1[2]={8,700};
int a2[2]={100,40};
int a3[2]={30,1000};
int a4[2]={20,200};
int a5[2]={1000,30};
int a6[2]={0,70};
int a7[2]={305,200};
int a8[2]={4077,505};
int a9[2]={603,720};
int a10[2]={164,705};
int a11[2]={320,504};
int a12[2]={14,150};
int a13[2]={50,18};
int a14[2]={90,1540};
int a15[2]={26,130};
int a16[2]={180,1980};
int a17[2]={704,150};
int a18[2]={303,20};
int a19[2]={0,260};
int generation=0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//function prototypes
void start(void);
void initializevariables(void);
bool checkif(int organism, int val);
bool checkif2(int organism,int val);
void initializepopulation(void);
void initializepopulation1(void);
void evaluatepopulation(void);
void producenextgeneration(void);
int selectorganism(void);
void initrandomseed();
float calcdistance(int organism);
void minimum(void);
float distancebetween(int a,int b);
bool check(int val,int b[],int h);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//main function
int main()
{
    initrandomseed();
    initializevariables();
    //int i=0;
    while(runnumber<10)
    {
        start();
        generation=0;
        initializevariables();
        runnumber++;
        
    }
    for(int j=0;j<NUMBEROFGENES;j++)
    {
            cout<<BESTROUTE[j]<<endl;
    }
    //cout<<"generations: "<<generation<<endl
    cout<<MINIMUMFITNESS<<endl;
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//initializing all the global variables defined before
void initializevariables(void)
{
    int ORGANISM;
    int GENE;
    for(ORGANISM=0;ORGANISM<NUMBEROFORGANISMS;ORGANISM++)
    {
        for(GENE=0;GENE<NUMBEROFGENES;GENE++)
        {
            CURRENTGENERATION[ORGANISM][GENE]=-1;
            NEXTGENERATION[ORGANISM][GENE]=-1;
            ORGANISMFITNESS[ORGANISM]=100000.0;
        }
    }
    
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//starting of the iterative evolution process
void start(void)
{
    /*int PERFECTGENERATION=FALSE;*/
   // if(runnumber==0) 
        initializepopulation();
    /*else {
        initializepopulation1();
    }*/
    while(TRUE)
    {
        evaluatepopulation();
        if(generation==500) return;
        if(ORGANISMFITNESS[BESTORGANISMNUMBER]<MINIMUMFITNESS)
        {
            MINIMUMFITNESS=ORGANISMFITNESS[BESTORGANISMNUMBER];
            for(int i=0;i<NUMBEROFGENES;i++)
            {
                BESTROUTE[i]=CURRENTGENERATION[BESTORGANISMNUMBER][i];
            }
        }
        if(AVERAGEFITNESS<MINIMUMAVERAGEFITNESS)
        {
            MINIMUMAVERAGEFITNESS=AVERAGEFITNESS;
            for(int organism=0;organism<NUMBEROFORGANISMS;organism++)
            {
                for(int gene=0;gene<NUMBEROFGENES;gene++)
                {
                    BESTGENERATION[organism][gene]=CURRENTGENERATION[organism][gene];
                }
            }
        }
            
        cout<<"minimum fitness of this generation "<<generation<<" is " <<ORGANISMFITNESS[BESTORGANISMNUMBER]<<endl;
        cout<<"average fitness of this generation "<<generation<<" is "<<AVERAGEFITNESS<<endl;
        producenextgeneration();
        generation++;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//initializing the population before the start of run
void initializepopulation(void)
{
    int ORGANISM;
    int GENE;
    int val;
    
    for(ORGANISM=0;ORGANISM<NUMBEROFORGANISMS;ORGANISM++)
    {
        for(GENE=0;GENE<NUMBEROFGENES;GENE++)
        {   
            val=rand()%ALLELES;
            while(! checkif(ORGANISM,val))
            {
                val=rand()%ALLELES;
            }
            CURRENTGENERATION[ORGANISM][GENE]=val;
        }
    }
}

void initializepopulation1(void)
{
    int organism;
    int gene;
    for(organism=0;organism<NUMBEROFORGANISMS;organism++)
    {
        for(gene=0;gene<NUMBEROFGENES;gene++)
        {
            CURRENTGENERATION[organism][gene]=BESTGENERATION[organism][gene];
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//checks if a value is repeated in the genes of an organism in current generation
bool checkif(int ORGANISM,int VAL)
{
    int GENE;
    for(GENE=0;GENE<NUMBEROFGENES;GENE++)
    {
        if(CURRENTGENERATION[ORGANISM][GENE]==VAL) return false;
        
    }
    return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//checks if a value is repeated in the genes of an organism in the next generation 
bool checkif2(int ORGANISM,int VAL)
{
    int GENE;
    for(GENE=0;GENE<NUMBEROFGENES;GENE++)
    {
        if(NEXTGENERATION[ORGANISM][GENE]==VAL) return false;
        
    }
    return true;
    
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//evaluates the population acc to fitness function at the end of each generation
void evaluatepopulation(void)
{
    int ORGANISM;
    //int GENE;
    //int CURRENTORGANISMFITNESS;
    TOTALOFFITNESSES=0.0;
    
    for(ORGANISM=0;ORGANISM<NUMBEROFORGANISMS;ORGANISM++)
    {
        ORGANISMFITNESS[ORGANISM]=calcdistance(ORGANISM);
        TOTALOFFITNESSES=TOTALOFFITNESSES+calcdistance(ORGANISM);
    }
    minimum();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//caluculates the fitness of an organism 
float calcdistance(int ORGANISM)
{
    float distance=0.0;
    for(int GENE=0;GENE<NUMBEROFGENES-1;GENE++)
    {
        distance+=distancebetween(CURRENTGENERATION[ORGANISM][GENE],CURRENTGENERATION[ORGANISM][GENE+1]);
    }
    distance+=distancebetween(CURRENTGENERATION[ORGANISM][NUMBEROFGENES-1],CURRENTGENERATION[ORGANISM][0]);
    return distance;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//produces the next generation
void producenextgeneration(void)
{
	int organism;
	int gene;
	int maleparent,femaleparent,start,end;
	int val1,val2;
	for(organism=0;organism<NUMBEROFORGANISMS;organism++)
    {
        for(gene=0;gene<NUMBEROFGENES;gene++)
        {
            NEXTGENERATION[organism][gene]=-1;
        }
    }
	for(organism=0;organism<NUMBEROFORGANISMS;organism++)
	{
		maleparent=selectorganism();
		femaleparent=selectorganism();
		int mutatethisgene=rand()%(int)(1.0/MUTATIONRATE);
        int crossthisgene=rand()%(int)(1.0/CROSSOVERRATE);
		if(mutatethisgene==0)
		{
			val1=rand()%NUMBEROFGENES;
			val2=rand()%NUMBEROFGENES;
			for(gene=0;gene<NUMBEROFGENES;gene++)
			{
				if(gene==val1) NEXTGENERATION[organism][gene]=CURRENTGENERATION[organism][val2];
				else if(gene==val2) NEXTGENERATION[organism][gene]=CURRENTGENERATION[organism][val1];
				else NEXTGENERATION[organism][gene]=CURRENTGENERATION[organism][gene];
			}
		}
		else if(crossthisgene<=85)
		{
			start=rand()%NUMBEROFGENES;
			end=rand()%NUMBEROFGENES;
			if(start>end)
			{
				int k;
				k=end;
				end=start;
				start=k;
			}
			for(int y=start;y<=end;y++)
			{
				NEXTGENERATION[organism][y]=CURRENTGENERATION[maleparent][y];
			}
			int i=0;
			for(gene=0;gene<NUMBEROFGENES;gene++)
			{
				if(gene>=start && gene<=end) continue;
				else
				{
					while(! checkif2(organism,CURRENTGENERATION[femaleparent][i]))
					{
						i++;
					}
					NEXTGENERATION[organism][gene]=CURRENTGENERATION[femaleparent][i];
					i++;
				}
			}	
		}
        else {
            for(gene=0;gene<NUMBEROFGENES;gene++)
            {
                NEXTGENERATION[organism][gene]=CURRENTGENERATION[organism][gene];
            }
        }
	}
	for(organism=0;organism<NUMBEROFORGANISMS;organism++)
    {
        for(gene=0;gene<NUMBEROFGENES;gene++)
        {
            CURRENTGENERATION[organism][gene]=NEXTGENERATION[organism][gene];
        }
    }
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//selects the organism acc to fitness using roulette wheel sampling method
int selectorganism(void){
    int ORGANISM=0;
    float RUNNINGTOTAL;
    int RANDOMSELECTPOINT;
    
    RUNNINGTOTAL = 0.0;
    //initrandomseed();
    int t=TOTALOFFITNESSES;
    RANDOMSELECTPOINT = rand()%t;
    RANDOMSELECTPOINT=0-RANDOMSELECTPOINT;
    
    for(ORGANISM=0; ORGANISM<NUMBEROFORGANISMS; ++ORGANISM){
        RUNNINGTOTAL = RUNNINGTOTAL - ORGANISMFITNESS[ORGANISM];
        if(RUNNINGTOTAL <= RANDOMSELECTPOINT) return ORGANISM;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//initializes the seed of the random function
void initrandomseed() {
    static bool initialized = false;
    if (!initialized) {
        srand(int(time(NULL)));
        initialized = true;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//checks the maximum fitness value possessing organism
void minimum(void)
{
    float min=1000000.0;
    float sum=0.0;
    for(int i=0;i<NUMBEROFORGANISMS;i++)
    {
        sum+=ORGANISMFITNESS[i];
        if(min>ORGANISMFITNESS[i])
        {
            min=ORGANISMFITNESS[i];
            BESTORGANISMNUMBER=i;
        }
    }
    AVERAGEFITNESS=sum/NUMBEROFORGANISMS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//caluculates the distance between cities
float distancebetween(int a,int b)
{
    int start[2];
    int end[2];
    switch (a) {
        case 0:
            for(int i=0;i<2;i++)
            {
                start[i]=a0[i];
            }
            break;
        case 1:
            for(int i=0;i<2;i++)
            {
                start[i]=a1[i];
            }
            break;
        case 2:
            for(int i=0;i<2;i++)
            {
                start[i]=a2[i];
            }
            break;
        case 3:
            for(int i=0;i<2;i++)
            {
                start[i]=a3[i];
            }
            break;
        case 4:
            for(int i=0;i<2;i++)
            {
                start[i]=a4[i];
            }
            break;
        case 5:
            for(int i=0;i<2;i++)
            {
                start[i]=a5[i];
            }
            break;
        case 6:
            for(int i=0;i<2;i++)
            {
                start[i]=a6[i];
            }
            break;
        case 7:
            for(int i=0;i<2;i++)
            {
                start[i]=a7[i];
            }
            break;
        case 8:
            for(int i=0;i<2;i++)
            {
                start[i]=a8[i];
            }
            break;
        case 9:
            for(int i=0;i<2;i++)
            {
                start[i]=a9[i];
            }
            break;
        case 10:
            for(int i=0;i<2;i++)
            {
                start[i]=a10[i];
            }
            break;
        case 11:
            for(int i=0;i<2;i++)
            {
                start[i]=a11[i];
            }
            break;
        case 12:
            for(int i=0;i<2;i++)
            {
                start[i]=a12[i];
            }
            break;
        case 13:
            for(int i=0;i<2;i++)
            {
                start[i]=a13[i];
            }
            break;
        case 14:
            for(int i=0;i<2;i++)
            {
                start[i]=a14[i];
            }
            break;
        case 15:
            for(int i=0;i<2;i++)
            {
                start[i]=a15[i];
            }
            break;
        case 16:
            for(int i=0;i<2;i++)
            {
                start[i]=a16[i];
            }
            break;
        case 17:
            for(int i=0;i<2;i++)
            {
                start[i]=a17[i];
            }
            break;
        case 18:
            for(int i=0;i<2;i++)
            {
                start[i]=a18[i];
            }
            break;
        case 19:
            for(int i=0;i<2;i++)
            {
                start[i]=a19[i];
            }
            break;
    }
    switch (b) {
        case 0:
            for(int i=0;i<2;i++)
            {
                end[i]=a0[i];
            }
            break;
        case 1:
            for(int i=0;i<2;i++)
            {
                end[i]=a1[i];
            }
            break;
        case 2:
            for(int i=0;i<2;i++)
            {
                end[i]=a2[i];
            }
            break;
        case 3:
            for(int i=0;i<2;i++)
            {
                end[i]=a3[i];
            }
            break;
        case 4:
            for(int i=0;i<2;i++)
            {
                end[i]=a4[i];
            }
            break;
        case 5:
            for(int i=0;i<2;i++)
            {
                end[i]=a5[i];
            }
            break;
        case 6:
            for(int i=0;i<2;i++)
            {
                end[i]=a6[i];
            }
            break;
        case 7:
            for(int i=0;i<2;i++)
            {
                end[i]=a7[i];
            }
            break;
        case 8:
            for(int i=0;i<2;i++)
            {
                end[i]=a8[i];
            }
            break;
        case 9:
            for(int i=0;i<2;i++)
            {
                end[i]=a9[i];
            }
            break;
        case 10:
            for(int i=0;i<2;i++)
            {
                end[i]=a10[i];
            }
            break;
        case 11:
            for(int i=0;i<2;i++)
            {
                end[i]=a11[i];
            }
            break;
        case 12:
            for(int i=0;i<2;i++)
            {
                end[i]=a12[i];
            }
            break;
        case 13:
            for(int i=0;i<2;i++)
            {
                end[i]=a13[i];
            }
            break;
        case 14:
            for(int i=0;i<2;i++)
            {
                end[i]=a14[i];
            }
            break;
        case 15:
            for(int i=0;i<2;i++)
            {
                end[i]=a15[i];
            }
            break;
        case 16:
            for(int i=0;i<2;i++)
            {
                end[i]=a16[i];
            }
            break;
        case 17:
            for(int i=0;i<2;i++)
            {
                end[i]=a17[i];
            }
            break;
        case 18:
            for(int i=0;i<2;i++)
            {
                end[i]=a18[i];
            }
            break;
        case 19:
            for(int i=0;i<2;i++)
            {
                end[i]=a19[i];
            }
            break;
    }
    float x = start[0]-end[0];
    if(x<0) x=-x;
    float y = start[1]-end[1];
    if(y<0) y=-y;
    float m = sqrt((x*x)+(y*y));
    //float m = ((x*x)+(y*y));
    return m;
}









