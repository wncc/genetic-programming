import java.util.List;
public class Gamegenetic{
	static Gametheory genetic_experiment;

	static public void main(String args[])
	{
		int generations = 2000;
		int numofruns = 10;
		double bestfitness=0;
		Object Allele[] = {"C","D"};
		genetic_experiment = new Gametheory(6,50,0.8,0.01,Allele,"not_ordered");
		Chromosome beststrategy = new Chromosome(genetic_experiment.numGenesPerChromosome);
		for(int i=0;i<numofruns;i++)
		{
			for(int j=0;j<generations;j++)
			{
				genetic_experiment.evolve();
			}
			if(bestfitness<genetic_experiment.highFitness)
			{
				bestfitness=genetic_experiment.highFitness;
				genetic_experiment.copy(genetic_experiment.HFChromosome,beststrategy);
			}
			genetic_experiment = new Gametheory(6,50,0.8,0.01,Allele,"not_ordered");
		}
		for(int j=2;j<6;j++)
		{
			System.out.println(beststrategy.getObject(j));
		}
	}
}
		
	


class Gametheory extends Genetic2{

	Gametheory(int num_g,int num_c,double crossover_fraction,double mutation_fraction, Object Alleles[],String type_of_genes)
	{
		super(num_g,num_c,crossover_fraction,mutation_fraction,Alleles,type_of_genes);
	}

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
			for(int j=0;j<10;j++)
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

	
