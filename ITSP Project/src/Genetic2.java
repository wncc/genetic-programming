import java.util.*;

abstract public class Genetic2 {

	protected int numGenesPerChromosome;
	protected int numChromosomes;
	List<Chromosome> chromosomes;
	protected double crossoverFraction;
	protected double mutationFraction;
	protected int[] rouletteWheel;
	protected int rouletteWheelSize;
	protected Object Alleles[];
	protected String typeofgenes;
	protected double Fitness[];
	protected double highFitness;
	protected double lowFitness;
	protected Chromosome HFChromosome;
	protected Chromosome LFChromosome;
	public Genetic2(int num_genes_per_chromosome, int num_chromosomes, Object Alleles_[], String type_of_genes) {
		this(num_genes_per_chromosome, num_chromosomes, 0.8, 0.01,Alleles_,type_of_genes);
	}

	public Genetic2(int num_genes_per_chromosome, int num_chromosomes,double crossover_fraction, double mutation_fraction, Object Alleles_[],String type_of_genes){
		numGenesPerChromosome = num_genes_per_chromosome;
		numChromosomes = num_chromosomes;
		crossoverFraction = crossover_fraction;
		mutationFraction = mutation_fraction;
		highFitness=0;
		lowFitness=10000000;
		Alleles = new Object[Alleles_.length];
		for(int i = 0; i< Alleles_.length; i++){
			Alleles[i]=Alleles_[i];
		}
		
		typeofgenes=type_of_genes;
		
		chromosomes = new ArrayList<Chromosome>(numChromosomes);
		for (int i = 0; i < numChromosomes; i++) {
			chromosomes.add(new Chromosome(numGenesPerChromosome));
			if(typeofgenes.equals("ordered")){
				permute_ordered(chromosomes.get(i).chromosome);
			}
			else if(typeofgenes.equals("not_ordered")){
				permute_not_ordered(chromosomes.get(i).chromosome);
			}
			else System.out.println("type_of_genes must either be 'ordered' or 'not_ordered'");
		}
		
		
		rouletteWheelSize = 0;
		HFChromosome=new Chromosome(numGenesPerChromosome);
		LFChromosome=new Chromosome(numGenesPerChromosome);
		Fitness= new double[numChromosomes];
		for (int i=0; i< numChromosomes; i++){
			Fitness[i] = calcFitness(chromosomes.get(i));
			if(highFitness<Fitness[i]){
				highFitness = Fitness[i];
				copy(chromosomes.get(i),HFChromosome);
			}
			if(lowFitness>Fitness[i]){
				lowFitness=Fitness[i];
				copy(chromosomes.get(i),LFChromosome);
			}
		}
		for(int k=0;k<numChromosomes;k++)
		{
			rouletteWheelSize += (int)Fitness[k];
		}
		rouletteWheel = new int[rouletteWheelSize];
		int rouletteWheelSize2 =0;
		for (int i=0;i<numChromosomes; i++){
			for (int j =0; j<(int)Fitness[i];j++){
				
				rouletteWheel[rouletteWheelSize2 + j]=i;
			}
			rouletteWheelSize2 += (int)Fitness[i];
		}
	}

	public Object getGene(int chromosome, int gene) {
		return chromosomes.get(chromosome).getObject(gene);
	}

	public void setGene(int chromosome, int gene, Object value) {
		chromosomes.get(chromosome).setObject(gene, value);
	}

	void evolve_ordered() {
		doCrossovers_ordered();
		doMutations_ordered();
	}

	void evolve_not_ordered() {
		doCrossovers_not_ordered();
		doMutations_not_ordered();
	}
	
	public void evolve(){
		if(typeofgenes.equals("ordered")){
			evolve_ordered();
		}
		else if(typeofgenes.equals("not_ordered")){
			evolve_not_ordered();
		}
		else System.out.println("type_of_genes must either be 'ordered' or 'not_ordered'");
	}
	
	public void doCrossovers_not_ordered(){
		int num = (int) (numChromosomes * crossoverFraction);
		Random random = new Random();
		for(int i=0; i<num;i++){
			int c1 = random.nextInt(rouletteWheelSize);
			int c2 = random.nextInt(rouletteWheelSize);
			c1 = rouletteWheel[c1];
			c2 = rouletteWheel[c2];
			if (c1 != c2){
				int locus = random.nextInt(numGenesPerChromosome);
				for (int j=locus;j<numGenesPerChromosome;j++){
					Object dupe = getGene(c1, j);
					setGene(c1, j, getGene(c2, j));
					setGene(c2, j, dupe);
				}
			}
		}
		rouletteWheelSize = 0;
		double Fitness[]= new double[numChromosomes];
		for (int i=0; i< numChromosomes; i++){
			Fitness[i] = calcFitness(chromosomes.get(i));
			if(highFitness<Fitness[i]){
				highFitness = Fitness[i];
				copy(chromosomes.get(i),HFChromosome);
			}
			else if(lowFitness>Fitness[i]){
				lowFitness=Fitness[i];
				copy(chromosomes.get(i),LFChromosome);
			}
			rouletteWheelSize += (int)Fitness[i];
		}
		rouletteWheel = new int[rouletteWheelSize];
		int rouletteWheelSize2 =0;
		for (int i=0;i<numChromosomes; i++){
			for (int j =0; j<(int)Fitness[i];j++){
				rouletteWheel[rouletteWheelSize2 + j]=i;
			}
			rouletteWheelSize2 += (int)Fitness[i];
		}
	}
			
			
public void doCrossovers_ordered(){
		int num = (int) (numChromosomes * crossoverFraction);
		Random random = new Random();
		for(int m=0; m<num;m++){
			int c1 = random.nextInt(rouletteWheelSize);
			int c2 = random.nextInt(rouletteWheelSize);
			c1 = rouletteWheel[c1];
			c2 = rouletteWheel[c2];
			if(c1!=c2)
			{
				int locus1 = random.nextInt(numGenesPerChromosome);
				int locus2 = random.nextInt(numGenesPerChromosome);
				while(locus2==locus1) locus2=random.nextInt(numGenesPerChromosome);
				if(locus2<locus1)
				{
					int x = locus1;
					locus1 = locus2;
					locus2 = x;
				}
				Object loop1[]=new Object[locus2-locus1+1];
				Object loop2[]=new Object[locus2-locus1+1];
				for(int j=locus1;j<=locus2;j++)
				{
					loop1[j-locus1]=chromosomes.get(c1).getObject(j);
					loop2[j-locus1]=chromosomes.get(c2).getObject(j);
				}
				Chromosome dupe1 = new Chromosome(numGenesPerChromosome);
				copy(chromosomes.get(c1),dupe1);
				Chromosome dupe2 = new Chromosome(numGenesPerChromosome);
				copy(chromosomes.get(c2),dupe2);
				int i=0,j=0;
				while(i<numGenesPerChromosome)
				{
					if(i>=locus1&&i<=locus2)
					{
						setGene(c1,i,loop1[i-locus1]);
						i++;
					}

					else
					{
						boolean val = check(dupe2.getObject(j),loop1);
						if(!val)
						{
							setGene(c1,i,dupe2.getObject(j));
							i++;
							j++;
						}
						else
						{
							j++;
						}
						
					}
				}
				i=0;
				j=0;
				while(i<numGenesPerChromosome)
				{
					if(i>=locus1&&i<=locus2)
					{
						setGene(c2,i,loop2[i-locus1]);
						i++;
					}

					else
					{
						boolean val2 = check(dupe1.getObject(j),loop2);
						if(!val2)
						{
							setGene(c2,i,dupe1.getObject(j));
							i++;
							j++;
						}
						else
						{
							j++;
						}
						
					}
				}	
			}
		}
		}	
		
	public void doMutations_not_ordered(){
		int num = (int)(numChromosomes * mutationFraction);
		Random random = new Random();
		for(int i=0;i<num;i++){
			int c = random.nextInt(numChromosomes);
			int g= random.nextInt(numGenesPerChromosome);
			Object k = random.nextInt(Alleles.length);
			setGene(c, g, k);
		}
		rouletteWheelSize = 0;
		double Fitness[]= new double[numChromosomes];
		for (int i=0; i< numChromosomes; i++){
			Fitness[i] = calcFitness(chromosomes.get(i));
			if(highFitness<Fitness[i]){
				highFitness = Fitness[i];
				copy(chromosomes.get(i),HFChromosome);
			}
			else if(lowFitness>Fitness[i]){
				lowFitness=Fitness[i];
				copy(chromosomes.get(i),LFChromosome);
			}
			rouletteWheelSize += (int)Fitness[i];
		}
		rouletteWheel = new int[rouletteWheelSize];
		int rouletteWheelSize2 =0;
		for (int i=0;i<numChromosomes; i++){
			for (int j =0; j<(int)Fitness[i];j++){
				rouletteWheel[rouletteWheelSize2 + j]=i;
			}
			rouletteWheelSize2 += (int)Fitness[i];
		}
	}
	
	public void doMutations_ordered(){
		int num = (int)(numChromosomes * mutationFraction);
		Random random = new Random();
		for(int i=0;i<num;i++){
			int c = random.nextInt(numChromosomes);
			int g1= random.nextInt(numGenesPerChromosome);
			int g2= random.nextInt(numGenesPerChromosome);
			Object dupe = getGene(c,g1);
			setGene(c,g1, getGene(c, g2));
			setGene(c, g2, dupe);
		}
		rouletteWheelSize = 0;
		double Fitness[]= new double[numChromosomes];
		for (int i=0; i< numChromosomes; i++){
			Fitness[i] = calcFitness(chromosomes.get(i));
			if(highFitness<Fitness[i]){
				highFitness = Fitness[i];
				copy(chromosomes.get(i),HFChromosome);
			}
			else if(lowFitness>Fitness[i]){
				lowFitness=Fitness[i];
				copy(chromosomes.get(i),LFChromosome);
			}
			rouletteWheelSize += (int)Fitness[i];
		}
		rouletteWheel = new int[rouletteWheelSize];
		int rouletteWheelSize2 =0;
		for (int i=0;i<numChromosomes; i++){
			for (int j =0; j<(int)Fitness[i];j++){
				rouletteWheel[rouletteWheelSize2 + j]=i;
			}
			rouletteWheelSize2 += (int)Fitness[i];
		}
	}	

	abstract public double calcFitness(Chromosome chromosome);
	
	void permute_not_ordered(Object rand[]){
		Random random = new Random();
		for(int i=0;i<numGenesPerChromosome;i++){
			rand[i]=Alleles[random.nextInt(Alleles.length)];
		}
	}
	
	void permute_ordered(Object rand[]){
		Random random = new Random();
		for(int i=0;i < numGenesPerChromosome; i++){
			rand[i]=0;
		}
		int rand1[]=new int[numGenesPerChromosome];
		rand1[0] =1+ random.nextInt(numGenesPerChromosome);
		for(int i=0; i<(numGenesPerChromosome - 1);i ++){
			nextrandom(rand1);
		}
		for(int i=0; i<numGenesPerChromosome; i++){
			rand[i]=Alleles[rand1[i]-1];
		}
	}
	
	void nextrandom(int array[]){
		int dupe[] = new int[numGenesPerChromosome];
		Random random = new Random();
		for(int i=0; i<numGenesPerChromosome; i++){
			dupe[i]=i+1;
		}
		int i=0;
		while(i != numGenesPerChromosome && array[i]!=0){
			dupe[array[i]-1]=0;
			i++;
		}
		int k =1+ random.nextInt(numGenesPerChromosome-i);
		int start =0;
		int end = 0;
		int num_of_zeros = 0;
		int flag = 0;
		for(int j=0;j<numGenesPerChromosome;j++){
			if(dupe[j]==0 && flag ==0){
				start=j;
				num_of_zeros++;
			}
			if(dupe[j]==k + num_of_zeros)flag =1;
			if(dupe[j]==0 && flag == 1){
				end=j;
				break;
			}
			if(j==(numGenesPerChromosome - 1))end = numGenesPerChromosome;
		}
		int nextrand;
		if(end-start == 1){
			nextrand=-1;
		}
		else nextrand = random.nextInt(end- start-1);
		array[i]=start + nextrand +2;
	}
	
	public void copy(Chromosome ch1,Chromosome ch2){
		for(int i=0;i<numGenesPerChromosome;i++){
			ch2.setObject(i,ch1.getObject(i));
		}
	}
	
	public boolean check(Object Gene,Object[] array){
		for(Object x : array){
			if(x == Gene)return true;
		}
		return false;
	}
}

 
class Chromosome{
	public Object chromosome[];
	double fitness;
	Chromosome(int num_genes){ chromosome = new Object[num_genes];}
	
	public Object getObject(int index){
		return chromosome[index];
	}
	
	public void setObject(int index, Object value){
		chromosome[index] = value;
	}
	
	public double getFitness(){
		return fitness;
	}
	
	public void setFitness(double value){
		fitness = value;
	}

	public void incFitness(double value){
		fitness = fitness+value;
	}
}
