import java.util.List;
public class Strategyevolver{
	static Gametheory genetic_experiment;

	static public void main(String args[])
	{
		int generations = 10000;
		int numofruns = 1;
		double bestfitness=0;
		//the chromosome consists of only "C" (for cooperate) and "D" (for defect). so Allele must contain "C" and "D"
		Object Allele[] = {"C","D"};
		genetic_experiment = new Gametheory(6,50,0.8,0.01,Allele,"not_ordered");
		//"not_ordered" implies that in the chromosome the elements can be non-distinct also
		//the chromosome consists of 6 genes, each population consists of 50 chromosomes, with crossover-fraction 0.8 
		//and mutation fraction 0.01
		Chromosome beststrategy = new Chromosome(genetic_experiment.numGenesPerChromosome);
		for(int i=0;i<numofruns;i++)
		{
			for(int j=0;j<generations;j++)
			{
				genetic_experiment.evolve();
			}
			for(int l=0;l<genetic_experiment.numChromosomes;l++)
			{
				if(bestfitness<genetic_experiment.Fitness[l])
				{
					bestfitness=genetic_experiment.Fitness[l];
					genetic_experiment.copy(genetic_experiment.chromosomes.get(l),beststrategy);
				}
			}
			//the whole setup is initialized again at the end of a run
			genetic_experiment = new Gametheory(6,50,0.8,0.01,Allele,"not_ordered");
		}
		for(int j=2;j<6;j++)
		{
			//printing out the best organism/strategy
			System.out.println(beststrategy.getObject(j));
		}
	}
}




class Gametheory extends Genetic{

	Gametheory(int num_g,int num_c,double crossover_fraction,double mutation_fraction, Object Alleles[],String type_of_genes)
	{
		super(num_g,num_c,crossover_fraction,mutation_fraction,Alleles,type_of_genes);
	}
	
	

	//the chromosome is represented as an array of strings in this case of length 6. the first two elements in the 
	//array represent the imaginary game played so that the first move of the chromosome is decided through the first
	//2 elements
	// Case1: CC
	// Case2: CD
	// Case3: DD
	// Case4: DC
	// so the chromosome for example is CDCDDC then using the first two elements the chromosome checks the case number
	//which is equivalent to it and plays that. I mean since it is CD and it corresponds to case2 it will play the 
	// 2+2=4th element of the chromosome that is D. From then on it remembers it's previous play and decides its next
	//move in a similar way

	public double calcFitness(Chromosome chromosome)
	{
		Object memory[]= new Object[2];
		double score1=0;
		memory[0]= chromosome.getObject(0);
		memory[1]= chromosome.getObject(1);
		for(int i=0;i<numChromosomes;i++)
		{
			int score2 = 0;
			Object memory2[] = new Object[2];
			memory2[0]= chromosomes.get(i).getObject(0);
			memory2[1]= chromosomes.get(i).getObject(1);
			for(int j=0;j<20;j++)
			{
				int casenumber1 = retrievecasenumber(memory[0],memory[1]);
				int casenumber2 = retrievecasenumber(memory2[0],memory2[1]);
				Object play1 = chromosome.getObject(casenumber1+1);
				Object play2 = chromosome.getObject(casenumber2+1);
				score1= score1 + retrievescore1(play1,play2);
				score2= score2 + retrievescore1(play2,play1);
				memory[0]=play1;
				memory[1]=play2;
				memory2[0]=play2;
				memory2[1]=play1;
			}
			Fitness[i]+=score2;
		}
		return score1;
	}

	public int retrievecasenumber(Object i,Object j)
	{
		if(i.equals("C")&&j.equals("C"))
		{
			return 1;
		}
		else
		{
			if(i.equals("C")&&j.equals("D"))
			{
				return 2;
			}
			else
			{
				if(i.equals("D")&&j.equals("D"))
				{
					return 3;
				}
				else
				{
						return 4;
				}
			}
		}
	}
	
	

	//the scores defined as such are:
	// if player1 cooperates and player2 cooperates player1 gets 3 and player2 gets 3
	// if player1 cooperates and player2 defects player1 gets 0 and player2 gets 5
	// if player1 defects and player2 defects player1 gets 1 and player2 gets 1
	// if player1 defects and player2 cooperates player1 gets 5 and player2 gets 0

	public int retrievescore1(Object i,Object j)
	{
		if(i.equals("C")&&j.equals("C"))
		{
			return 3;
		}
		else
		{
			if(i.equals("C")&&j.equals("D"))
			{
				return 0;
			}
			else
			{
				if(i.equals("D")&&j.equals("D"))
				{
					return 1;
				}
				else
				{

						return 5;
				}
			}
		}
	}

}
