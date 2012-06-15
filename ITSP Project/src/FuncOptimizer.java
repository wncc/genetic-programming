//To find the maximium of the function:
// f(x)=sin(x)*sin(0.4x)*sin(3x)
import java.util.List;
public class FuncOptimizer {
    static public void main(String args[]) {
        MyGenetic genetic_experiment;
        int Generations = 1000;
		int numofruns = 10;
		int bestnum[] = new int[10];
		double bestfitness =0;
		//the chromosome consists of genes whose values will be only 0 and 1
		Object allele[] = {0,1};
		MyGenetic max= new MyGenetic(10, 20, 0.85, 0.2, allele,"not_ordered");
		//each population consists of 20 chromosomes with 10 number of genes in it
		//crossover fraction is 0.85
		//mutation fraction is 0.2
		//the genes in the chromosome can be non-distinct
		Chromosome bfnum=new Chromosome(max.numGenesPerChromosome);
		for (int i=0;i<numofruns;i++){
			for (int j=0;j<Generations;j++){
				max.evolve();
			}
			if(bestfitness<max.highFitness){
				bestfitness=max.highFitness;
				max.copy(max.HFChromosome,bfnum);
			}
			max= new MyGenetic(10, 20, 0.85, 0.2, allele,"not_ordered");
		}
		System.out.println("Best Fitness :" + (bestfitness-1000)/1000);
		System.out.println(max.genetodouble(bfnum));
		System.out.println();
	}		
}

class MyGenetic extends Genetic {
    MyGenetic(int num_genes_per_chromosome, int num_chromosomes,double crossover_fraction, double mutation_fraction, Object Alleles_[],String type_of_genes) {
        super(num_genes_per_chromosome, num_chromosomes, crossover_fraction, mutation_fraction, Alleles_, type_of_genes);
    }
    //the function gene to double converts the chromosome which can be considered as a binary number into its corresponding value in decimal
    public double genetodouble(Chromosome chromosome){
    	int num=1;
    	double x=0;
   		for(int i=0;i<numGenesPerChromosome;i++){
   			if(Integer.parseInt(chromosome.getObject(i).toString())==1) x+=num;
   			num*=2;
   		}
   		//the maximum value of x possible is 1024.0 in decimal as the number of genes is 10
   		//the function is periodic with periodicity 2*pi/0.4
   		//so we divide x by such a value so as to check the values between 0 and 2*pi/0.4 only thus checking for all the values by the periodic nature  
   		//of the function
   		x = x/65.0;
   		return x;
   	}
    
    public double calcFitness(Chromosome chromosome){
    	double x = genetodouble(chromosome);
    	//the function to be defined here
    	double fitness = (Math.sin(x) * Math.sin(0.4f * x) * Math.sin(3.0f * x));
    	return (1000+fitness*1000);
    }

}
