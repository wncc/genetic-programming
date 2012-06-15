class travelguide extends Genetic{

	travelguide(int num_genes_per_chromosome, int num_chromosomes,double crossover_fraction, double mutation_fraction, Object Alleles_[],String type_of_genes){
		super(num_genes_per_chromosome, num_chromosomes, crossover_fraction, mutation_fraction, Alleles_, type_of_genes);
	}
	
	public double distancebetween(int a, int b,int[][] point){
		double f =  Math.sqrt(Math.pow((point[a][0]-point[b][0]),2)+Math.pow((point[a][1]-point[b][1]),2));
		return f;
	}
	
	public double calcFitness(Chromosome chromosome){	
		double Fitness=0;
		int[][] point={{10,100},{8,70},{100,40},{30,100},{20,20},{100,30},{0,70},{35,200},{40,55},{63,70},{14,705},{32,54},{14,10},{50,18},{90,140},{26,130},{180,10},{70,150},{303,20},{0,260}};
		double distances[][]=new double[20][20];
		for(int i=0; i<20;i++){
			distances[i][i]=0;
			for(int j =i+1;j<20;j++){
				distances[i][j]=distancebetween(i,j,point);
				distances[j][i]=distances[i][j];
			}
		}
		
		for(int i=0;i<20;i++){
			Fitness += distances[Integer.parseInt(chromosome.getObject(i%20).toString())][Integer.parseInt(chromosome.getObject((i+1)%20).toString())];
		}
		
		return (10000-Fitness);
	}		
}

class travellingsalesman{

	static travelguide travelman;
	
	public static void main(String args[]){
		int Generations = 1000;
		int numofruns = 5;
		int bestpath[] = new int[20];
		double bestfitness =0;
		Object allele[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
		travelman = new travelguide(20, 1000, 0.8, 0.01, allele,"ordered");
		Chromosome bfpath=new Chromosome(travelman.numGenesPerChromosome);
		for (int i=0;i<numofruns;i++){
			for (int j=0;j<Generations;j++){
				travelman.evolve();
			}
			if(bestfitness<travelman.highFitness){
				bestfitness=travelman.highFitness;
				travelman.copy(travelman.HFChromosome,bfpath);
			}
			travelman = new travelguide(20, 100, 0.8, 0.01, allele,"ordered");
		}
		System.out.println("Best Fitness :" + (10000-bestfitness));
		for(int i=0;i<travelman.numGenesPerChromosome;i++){
			System.out.print(bfpath.getObject(i) + " ");
		}
		System.out.println();
	}		
}
