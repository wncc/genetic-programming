import java.util.List;
public class Gamegenetic{
	static Gametheory genetic_experiment;

	static public void main(String args[])
	{
		
		int NUM_CYCLES = 10000;
		for(int j=0;j<10;j++)
		{
			genetic_experiment = new Gametheory(6,20,0.8f,0.2f);
			/*for (Chromosome ll  : genetic_experiment.chromosomes) {
          		System.out.println(ll.chromosome);
        		}*/
			for(int i=0;i<NUM_CYCLES;i++)
			{
				genetic_experiment.evolve();
            		if (i==NUM_CYCLES-1) {
            		    //System.out.println("Generation " + i);
            		    /*for (Chromosome ll  : genetic_experiment.chromosomes) {
          		System.out.println(ll.chromosome);
        		}*/
            		    genetic_experiment.print();
            		}
        		}
    		}
	}
}	


class Gametheory extends Genetic{

	Gametheory(int num_g,int num_c,float crossover_fraction,float mutation_fraction)
	{
		super(num_g,num_c,crossover_fraction,mutation_fraction);
	}

	private int fitness(int chromosomeindex)
	{
		boolean memory[]= new boolean[2];
		int score1=0;
		memory[0]= getGene(chromosomeindex,0);
		memory[1]= getGene(chromosomeindex,1);
		for(int i=0;i<numChromosomes;i++)
		{
			int score2 = 0;
			boolean memory2[] = new boolean[2];
			memory2[0]= getGene(i,0);
			memory2[1]= getGene(i,1);
			for(int j=0;j<100;j++)
			{
				int casenumber1 = retrievecasenumber(memory[0],memory[1]);
				int casenumber2 = retrievecasenumber(memory2[0],memory2[1]);
				boolean play1 = getGene(chromosomeindex,casenumber1+1);
				boolean play2 = getGene(i,casenumber2+1);
				score1= score1 + retrievescore1(play1,play2);
				score2= score2 + retrievescore1(play2,play1);
				memory[0]=play1;
				memory[1]=play2;
				memory2[0]=play2;
				memory2[1]=play1;
			}
			chromosomes.get(i).incFitness(score2);
		}
		return score1;
	}

	public int retrievecasenumber(boolean i,boolean j)
	{
		if(i==true&&j==true)
		{
			return 1;
		}
		else
		{
			if(i==true&&j==false)
			{
				return 2;
			}
			else
			{
				if(i==false&&j==false)
				{
					return 3;
				}
				else
				{
					//if(i==false&j==true)
					//{
						return 4;
					//}
				}
			}
		}
		//return 0;
	}

	public int retrievescore1(boolean i,boolean j)
	{
		if(i==true&&j==true)
		{
			return 6;
		}
		else
		{
			if(i==true&&j==false)
			{
				return -12;
			}
			else
			{
				if(i==false&&j==false)
				{
					return -6;
				}
				else
				{
					//if(i==false&j==true)
					//{
						return 18;
					//}
				}
			}
		}
		//return 0;
	}

	public void calcFitness()
	{
		for(int i=0;i<numChromosomes;i++)
		{
			chromosomes.get(i).incFitness(fitness(i));
		}
	}

	public void print()
	{
		int sum = 0;
		for(int i=0;i<numChromosomes;i++)
		{
			sum+= chromosomes.get(i).getFitness();
		}

		sum/=numChromosomes;
		//System.out.println("The best strategy is  " );
		sort();
		for(int i=2;i<6;i++)
		{
			if(getGene(0,i)== true)
			{
				System.out.print("C ");
			}
			else
			{
				System.out.print("D ");
			}
		}
		System.out.println("");
		System.out.println("");
	}
}		

	