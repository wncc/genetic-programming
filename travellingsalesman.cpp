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
long CURRENTGENERATION[NUMBEROFORGANISMS][NUMBEROFGENES];
long NEXTGENERATION[NUMBEROFORGANISMS][NUMBEROFGENES];
long BESTGENERATION[NUMBEROFORGANISMS][NUMBEROFGENES];
double ORGANISMFITNESS[NUMBEROFORGANISMS];
double TOTALOFFITNESSES=0.0;
long BESTROUTE[NUMBEROFGENES];
double MINIMUMFITNESS=900000000000000.0;
double MINIMUMAVERAGEFITNESS=900000000000000.0;
double AVERAGEFITNESS;
long BESTORGANISMNUMBER;
long runnumber=0;
long a0[2]={10,100};
long a1[2]={8,70};
long a2[2]={100,40};
long a3[2]={30,100};
long a4[2]={20,20};
long a5[2]={100,30};
long a6[2]={0,70};
long a7[2]={35,200};
long a8[2]={40,55};
long a9[2]={63,70};
long a10[2]={14,705};
long a11[2]={32,54};
long a12[2]={14,10};
long a13[2]={50,18};
long a14[2]={90,140};
long a15[2]={26,130};
long a16[2]={180,10};
long a17[2]={70,150};
long a18[2]={303,20};
long a19[2]={0,260};
long generation=0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//function prototypes
void start(void);
void initializevariables(void);
bool checkif(long organism, long val);
bool checkif2(long organism,long val);
void initializepopulation(void);
void initializepopulation1(void);
void evaluatepopulation(void);
void producenextgeneration(void);
long selectorganism(void);
void initrandomseed();
double calcdistance(long organism);
void minimum(void);
double distancebetween(long a,long b);
bool check(long val,long b[],long h);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//main function
int main()
{
    initrandomseed();
    initializevariables();
    //long i=0;
    while(runnumber<1)
    {
        start();
        //generation=0;
        initializevariables();
        runnumber++;
        
    }
    for(long j=0;j<NUMBEROFGENES;j++)
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
    long ORGANISM;
    long GENE;
    for(ORGANISM=0;ORGANISM<NUMBEROFORGANISMS;ORGANISM++)
    {
        for(GENE=0;GENE<NUMBEROFGENES;GENE++)
        {
            CURRENTGENERATION[ORGANISM][GENE]=-1;
            NEXTGENERATION[ORGANISM][GENE]=-1;
            ORGANISMFITNESS[ORGANISM]=100000000000000.0;
        }
    }
    
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//starting of the iterative evolution process
void start(void)
{
    /*long PERFECTGENERATION=FALSE;*/
   // if(runnumber==0) 
        initializepopulation();
    /*else {
        initializepopulation1();
    }*/
    while(TRUE)
    {
        evaluatepopulation();
        if(generation==2000) return;
        if(ORGANISMFITNESS[BESTORGANISMNUMBER]<MINIMUMFITNESS)
        {
            MINIMUMFITNESS=ORGANISMFITNESS[BESTORGANISMNUMBER];
            for(long i=0;i<NUMBEROFGENES;i++)
            {
                BESTROUTE[i]=CURRENTGENERATION[BESTORGANISMNUMBER][i];
            }
        }
        if(AVERAGEFITNESS<MINIMUMAVERAGEFITNESS)
        {
            MINIMUMAVERAGEFITNESS=AVERAGEFITNESS;
            for(long organism=0;organism<NUMBEROFORGANISMS;organism++)
            {
                for(long gene=0;gene<NUMBEROFGENES;gene++)
                {
                    BESTGENERATION[organism][gene]=CURRENTGENERATION[organism][gene];
                }
            }
        }
        if(generation%100==0)
        {
            cout<<"minimum fitness of this generation "<<generation<<" is " <<ORGANISMFITNESS[BESTORGANISMNUMBER]<<endl;
            cout<<"average fitness of this generation "<<generation<<" is "<<AVERAGEFITNESS<<endl<<endl;
        }
        producenextgeneration();
        generation++;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//initializing the population before the start of run
void initializepopulation(void)
{
    long ORGANISM;
    long GENE;
    long val;
    
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
    long organism;
    long gene;
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
bool checkif(long ORGANISM,long VAL)
{
    long GENE;
    for(GENE=0;GENE<NUMBEROFGENES;GENE++)
    {
        if(CURRENTGENERATION[ORGANISM][GENE]==VAL) return false;
        
    }
    return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//checks if a value is repeated in the genes of an organism in the next generation 
bool checkif2(long ORGANISM,long VAL)
{
    long GENE;
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
    long ORGANISM;
    //long GENE;
    //long CURRENTORGANISMFITNESS;
    TOTALOFFITNESSES=0.0;
    
    for(ORGANISM=0;ORGANISM<NUMBEROFORGANISMS;ORGANISM++)
    {
        ORGANISMFITNESS[ORGANISM]=calcdistance(ORGANISM)*calcdistance(ORGANISM)*calcdistance(ORGANISM);
        TOTALOFFITNESSES=TOTALOFFITNESSES+ORGANISMFITNESS[ORGANISM];
    }
    minimum();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//caluculates the fitness of an organism 
double calcdistance(long ORGANISM)
{
    double distance=0.0;
    for(long GENE=0;GENE<NUMBEROFGENES-1;GENE++)
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
	long organism;
	long gene;
	long maleparent,femaleparent,start,end;
	long val1,val2;
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
		long mutatethisgene=rand()%(long)(1.0/MUTATIONRATE);
        long crossthisgene=rand()%(long)(1.0/CROSSOVERRATE);
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
				long k;
				k=end;
				end=start;
				start=k;
			}
			for(long y=start;y<=end;y++)
			{
				NEXTGENERATION[organism][y]=CURRENTGENERATION[maleparent][y];
			}
			long i=0;
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
long selectorganism(void){
    long ORGANISM=0;
    double RUNNINGTOTAL;
    long RANDOMSELECTPOlong;
    
    RUNNINGTOTAL = 0.0;
    //initrandomseed();
    long t=TOTALOFFITNESSES;
    RANDOMSELECTPOlong = rand()%t;
    RANDOMSELECTPOlong=0-RANDOMSELECTPOlong;
    
    for(ORGANISM=0; ORGANISM<NUMBEROFORGANISMS; ++ORGANISM){
        RUNNINGTOTAL = RUNNINGTOTAL - ORGANISMFITNESS[ORGANISM];
        if(RUNNINGTOTAL <= RANDOMSELECTPOlong) return ORGANISM;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//initializes the seed of the random function
void initrandomseed() {
    static bool initialized = false;
    if (!initialized) {
        srand(long(time(NULL)));
        initialized = true;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//checks the maximum fitness value possessing organism
void minimum(void)
{
    double min=1000000.0;
    double sum=0.0;
    for(long i=0;i<NUMBEROFORGANISMS;i++)
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
double distancebetween(long a,long b)
{
    long start[2];
    long end[2];
    switch (a) {
        case 0:
            for(long i=0;i<2;i++)
            {
                start[i]=a0[i];
            }
            break;
        case 1:
            for(long i=0;i<2;i++)
            {
                start[i]=a1[i];
            }
            break;
        case 2:
            for(long i=0;i<2;i++)
            {
                start[i]=a2[i];
            }
            break;
        case 3:
            for(long i=0;i<2;i++)
            {
                start[i]=a3[i];
            }
            break;
        case 4:
            for(long i=0;i<2;i++)
            {
                start[i]=a4[i];
            }
            break;
        case 5:
            for(long i=0;i<2;i++)
            {
                start[i]=a5[i];
            }
            break;
        case 6:
            for(long i=0;i<2;i++)
            {
                start[i]=a6[i];
            }
            break;
        case 7:
            for(long i=0;i<2;i++)
            {
                start[i]=a7[i];
            }
            break;
        case 8:
            for(long i=0;i<2;i++)
            {
                start[i]=a8[i];
            }
            break;
        case 9:
            for(long i=0;i<2;i++)
            {
                start[i]=a9[i];
            }
            break;
        case 10:
            for(long i=0;i<2;i++)
            {
                start[i]=a10[i];
            }
            break;
        case 11:
            for(long i=0;i<2;i++)
            {
                start[i]=a11[i];
            }
            break;
        case 12:
            for(long i=0;i<2;i++)
            {
                start[i]=a12[i];
            }
            break;
        case 13:
            for(long i=0;i<2;i++)
            {
                start[i]=a13[i];
            }
            break;
        case 14:
            for(long i=0;i<2;i++)
            {
                start[i]=a14[i];
            }
            break;
        case 15:
            for(long i=0;i<2;i++)
            {
                start[i]=a15[i];
            }
            break;
        case 16:
            for(long i=0;i<2;i++)
            {
                start[i]=a16[i];
            }
            break;
        case 17:
            for(long i=0;i<2;i++)
            {
                start[i]=a17[i];
            }
            break;
        case 18:
            for(long i=0;i<2;i++)
            {
                start[i]=a18[i];
            }
            break;
        case 19:
            for(long i=0;i<2;i++)
            {
                start[i]=a19[i];
            }
            break;
    }
    switch (b) {
        case 0:
            for(long i=0;i<2;i++)
            {
                end[i]=a0[i];
            }
            break;
        case 1:
            for(long i=0;i<2;i++)
            {
                end[i]=a1[i];
            }
            break;
        case 2:
            for(long i=0;i<2;i++)
            {
                end[i]=a2[i];
            }
            break;
        case 3:
            for(long i=0;i<2;i++)
            {
                end[i]=a3[i];
            }
            break;
        case 4:
            for(long i=0;i<2;i++)
            {
                end[i]=a4[i];
            }
            break;
        case 5:
            for(long i=0;i<2;i++)
            {
                end[i]=a5[i];
            }
            break;
        case 6:
            for(long i=0;i<2;i++)
            {
                end[i]=a6[i];
            }
            break;
        case 7:
            for(long i=0;i<2;i++)
            {
                end[i]=a7[i];
            }
            break;
        case 8:
            for(long i=0;i<2;i++)
            {
                end[i]=a8[i];
            }
            break;
        case 9:
            for(long i=0;i<2;i++)
            {
                end[i]=a9[i];
            }
            break;
        case 10:
            for(long i=0;i<2;i++)
            {
                end[i]=a10[i];
            }
            break;
        case 11:
            for(long i=0;i<2;i++)
            {
                end[i]=a11[i];
            }
            break;
        case 12:
            for(long i=0;i<2;i++)
            {
                end[i]=a12[i];
            }
            break;
        case 13:
            for(long i=0;i<2;i++)
            {
                end[i]=a13[i];
            }
            break;
        case 14:
            for(long i=0;i<2;i++)
            {
                end[i]=a14[i];
            }
            break;
        case 15:
            for(long i=0;i<2;i++)
            {
                end[i]=a15[i];
            }
            break;
        case 16:
            for(long i=0;i<2;i++)
            {
                end[i]=a16[i];
            }
            break;
        case 17:
            for(long i=0;i<2;i++)
            {
                end[i]=a17[i];
            }
            break;
        case 18:
            for(long i=0;i<2;i++)
            {
                end[i]=a18[i];
            }
            break;
        case 19:
            for(long i=0;i<2;i++)
            {
                end[i]=a19[i];
            }
            break;
    }
    double x = start[0]-end[0];
    if(x<0) x=-x;
    double y = start[1]-end[1];
    if(y<0) y=-y;
    double m = sqrt((x*x)+(y*y));
    //double m = ((x*x)+(y*y));
    return m;
}









