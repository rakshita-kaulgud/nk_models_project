#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


#define randfloat() ((float)rand() / (float)RAND_MAX)

				/* GLOBAL VARIABLES */

float pi = 3.141592654;
int firms=20;				/* number of potential firms  - maximum number of firms*/
int players=20;				/* number of firms in industry */
int N=20;					/* number of tasks */
int K=20;					/* number of interactions */
float rule_pram;			/* rule parameter = percent firms innovating */

float tech_param;           /* tech parameter = percent firms adopting new technology (renewable) */

float a[2000000][2000000];		/* vector of marginal cost coefficients */
float alpha=1.0;			/* demand parameter */
float beta=1.0;				/* demand parameter */
int b[21][21];				/* vector of substring members */
float fixed_cost=0.0;		/* fixed cost parameter */
float output;				/* total industry output */
float mutation=0.10;		/* likelihood of mutation */
float enter_rule=5;			/* likelihood of entry parameter */
float exit_rule=0.00;		/* threshold for exit */
//int iterate=100;			/* number of system iterations */
int leader=1;				/* designates the market leader */
float total_cost = 0.0;		/* sum of marginal costs across all entrants */
float total_profit = 0.01;	/* sum of earnings across all entrants */
float global=0;				/* lowest marginal cost possible */

float a2[2000000][2000000];
int b2[21][21];
float fudge_factor = 0.0;


typedef struct {
     int task[100]; 
     float price;
     float quantity;
     float mcost;
     float cost;
     float profit;
     float rule;
     int entrant;
     int tech; // 0 - yes, 1 - no
     // int renewable -> 0 -yes 1 -no
} orgs;

orgs firm[100];

//orgs firm[firms];

int number_of_runs = 100;
int number_of_time_periods = 100;
/* RANGE PARAMETERS */
float alphaStart;
float alphaEnd;
float betaStart;
float betaEnd;
float mutationStart;
float mutationEnd;
float enterRuleStart;
float enterRuleEnd;
float exitRuleStart;
float exitRuleEnd;

float fudgeFactorStart;
float fudgeFactorEnd;
float likelihoodNewTechStart;
float likelihoodNewTechEnd;

int numFirmsStart;
int numFirmsEnd;
int numTasksStart; //N
int numTasksEnd; //N
int numInteractionsStart; //K
int numInteractionsEnd; //K



/* ---------------- */

/* FUNCTIONS */

float cost(int task[100]) /* calculate firm costs */
{	
    // calc marginal cost
    int i,j,value;
	float running_cost = 0.0;
	for (i = 1; i <= N; i++)
	{
        value = 1 + task[i]; 
		for (j = 1; j <= (K-1); j++)
		{
            if (firm[i].tech == 1) {
                value = value + (pow(2,j) * task[b2[i][j]]);
            } else {
                value = value + (pow(2,j) * task[b[i][j]]); // if renewable use b2 else use b1
            }
            
		};
        if (firm[i].tech == 1){
            running_cost = running_cost + (a2[i][value]); // if renewable use a1 else use a2
        } else {
            running_cost = running_cost + (a[i][value]); // if renewable use a1 else use a2
        }
	};
    
	running_cost = running_cost/N;
	return(running_cost);
}


void profits() /* calculate firm profits */
{	int i,j;
	float output = 0.0;
	total_cost = 0.0;
	total_profit = 0.0;
    // for each firm that has entered (firm[i].entrant == 1), calculate the marginal cost
    // Add all marginal costs to calculate total cost
  	for(i = 1; i <= firms; i++)
  	{
  	    if (firm[i].entrant==1)
        {
            firm[i].mcost = cost(firm[i].task);
            firm[i].mcost = (-1*((global/firm[i].mcost)-1))+0.1;  /*standardized to global*/
            total_cost = total_cost + firm[i].mcost;
		};
    };
  	for(i = 1; i <= firms; i++)
  	{
  	    if (firm[i].entrant==1)
        {
            firm[i].quantity = ((alpha + total_cost)/(players+1))-firm[i].mcost;
            if (firm[i].quantity<=0.0)
                firm[i].quantity=0.0;
            firm[i].cost = firm[i].mcost*firm[i].quantity + fixed_cost;
		    output = output + firm[i].quantity;
		};
	};
    for(j = 1; j <= firms; j++)
  	{
  	    if (firm[j].entrant==1)
       	{
       	    firm[j].price = alpha - (beta*output);
		    firm[j].profit = (firm[j].price * firm[j].quantity) - firm[j].cost;
		    total_profit = total_profit + firm[j].profit;
		};
	};
	total_profit = total_profit/(players+1); // does this give total profit per player? why players + 1?
}

float random_float( float min,  float max)
{
    //printf("\n in random float where min is %f and max is %f \n", min, max);
    if (max == min) {
        return roundf(100*min)/100;
    }

    else if (min < max) {
        float val = (max - min) * ((float)rand() / RAND_MAX) + min;
        //printf("%f", roundf(100*val)/100);
        return roundf(100*val)/100 ;
    }

    // return 0 if min > max
    return 0;
}

void setParams(){
    printf("\n in set params");
    N = (rand() % (numTasksStart - numTasksEnd + 1)) + numTasksStart;
    K = (rand() % (numInteractionsStart - numInteractionsEnd + 1)) + numInteractionsStart;
    if (K>N) K=N;
    firms = (rand() % (numFirmsStart - numFirmsEnd + 1)) + numFirmsStart;
    mutation = random_float(mutationStart, mutationEnd);
    enter_rule = random_float(enterRuleStart, enterRuleEnd);
    exit_rule = random_float(exitRuleStart, exitRuleEnd);
    alpha = random_float(alphaStart, alphaEnd);
    beta = random_float(betaStart, betaEnd);
    fudge_factor = random_float(fudgeFactorStart, fudgeFactorEnd);
    tech_param = random_float(likelihoodNewTechStart, likelihoodNewTechEnd);
}

void parameterize()
{
    firms = 20; /*(int) (1+(10*randfloat()));*/
	mutation = randfloat();
	N = 20; /*(int) (2+((max-1)*randfloat()));*/
	K = (int) (1+(N*randfloat()));
	//rule_pram = randfloat();
	setParams();
	//printf("\n Rule param = %f \n", rule_pram);
 	if (K>N) K=N;
}

// have another version of samee method for a2 b2
void seed_landscape()
{
    // initialize landscape. Call this twice. 
    // will a1 a2 b1 b2 - 2 landscapes
    int i,j,h,temp,stack[100];
	int combos = pow(2,K);
    // stack 
  	for(i = 1; i <= N; i++)
    {
          for(j = 1; j <= combos; j++)
          {
          	a[i][j] = randfloat();
          };
	  	  for(j = 1; j < i; j++)
          {
            stack[j] = j;
          };
	  	  for(j = (i+1); j <= N; j++)
          {
            stack[(j-1)] = j;
          };
          for(j = 1; j <= K; j++)
          {
            temp = (1 + ((int) ((N-j)*randfloat())));
          	b[i][j] = stack[temp];
		  	for (h = temp;  h <= (N-j-1); h++)
			{
			    stack[h] = stack[h+1];
         	 };
          };
     };
}

void seed_landscape_new_tech()
{
    // initialize landscape. Call this twice. 
    // will a1 a2 b1 b2 - 2 landscapes
    int i,j,h,temp,stack[100];
	int combos = pow(2,K);
    // stack 
  	for(i = 1; i <= N; i++)
    {
          for(j = 1; j <= combos; j++)
          {
          	a2[i][j] = randfloat(); // a & b -> cofficients for the equation. each decision is 0/1. 
          };
	  	  for(j = 1; j < i; j++)
          {
            stack[j] = j;
          };
	  	  for(j = (i+1); j <= N; j++)
          {
            stack[(j-1)] = j;
          };
          for(j = 1; j <= K; j++)
          {
            temp = (1 + ((int) ((N-j)*randfloat())));
          	b2[i][j] = stack[temp];
		  	for (h = temp;  h <= (N-j-1); h++)
			{
			    stack[h] = stack[h+1];
         	 };
          };
     };
}


/* give each firm a different initial task set*/
void initialize_firms(int runner)
{
    int i,j; float tmp;
	for(i = 1; i <= firms; i++)
    {
          firm[i].entrant = 0;
          firm[i].profit = 0;
          tmp = randfloat();
          //  tech_param - > likelihood of adopting new tech. 
          /*
                tech_param = a random float between 'likelihoodNewTechStart' and 'likelihoodNewTechEnd'. 
          */
          if (tmp > tech_param){
              firm[i].tech = 0; // old tech
          } else {
              firm[i].tech = 1; // new tech
          }
          tmp = randfloat();
          if (tmp > rule_pram)
         	 	 firm[i].rule = 1;
          else
         	  	 firm[i].rule = 0;
          for(j = 1; j <= N; j++)
          {
            firm[i].task[j] = (int) (2*randfloat());
          };
    };
}

void find_global()
{
    // finding the global
    int i,j,bins,stopper;
	int position[100];
    bins = pow(2, N);
    for(i = 1; i <= N; i++)
    {
       position[i] = 0;
    };
    global = cost(position);
	for(i = 1; i <= bins; i++)
    {
        j = 1; stopper = 0;
       	while (stopper == 0)
 	    {
 	        if (position[j] == 0)
         	{
         	 	position[j] = 1;
         	  	stopper = 1;
         	}
            else
         	  	position[j] = 0;
 	      	j++;
 	      	if (j > N) stopper=1;
   	    };
   	   	if (cost(position)<global) // low cost -> best position
   	   	    global=cost(position);
    };
}

void determine_entrants() /* determine if an entrant to industry */
{
    int i,j;
	int change = 1;
	int converge = 0;
	int worst = 1;
	players = 0; //defined at the top
	if (total_profit==0) total_profit=0.01;
	for(i = 1; i <= firms; i++)
    {
        if ((firm[i].entrant==0) && (randfloat()<(enter_rule*total_profit)))
            firm[i].entrant=1;
        if (firm[i].entrant==1)
            players=players+1;  // player = number of entrants?
    };
	while (converge<1)
 	{
 	    profits();
 	 	worst = 0;
 	 	firm[0].mcost = 0;
      	change = 0;
		for (i = 1; i <= firms; i++)
   		{
   		    if ((firm[i].mcost>firm[worst].mcost)&&(firm[i].entrant==1)) worst=i;
  		};
        if ((worst!=0) && (firm[worst].profit<=exit_rule))
        {
            change = 1;
			firm[worst].entrant=0;
			players=players-1;
        	firm[worst].quantity=0;
        	firm[worst].profit=0;
        	firm[worst].price=0;
         	for(j = 1; j <= N; j++) {
         	    firm[worst].task[j] = (int) (2*randfloat());
         	};
         };
        if (change == 0) converge=1;
    };
    profits();
}

void update() /* update tasks according to algorithm . mutation - review and change underlying task*/
{
    int i,j,j2,new_task[100],rule;
	float new_quantity,new_price,new_cost,new_profits;
  	for(i = 1; i <= firms; i++)
  	{
        if (firm[i].entrant==1)
        {   
            for(j = 1; j <= N; j++)
         	{
                new_task[j] = firm[i].task[j];};
                for(j = 1; j <= N; j++)
         	    {
         	    if (randfloat() < mutation)
         	 	{
                    new_task[j] = abs(new_task[j]-1);
         	 	    new_cost = cost(new_task);
         	 	    new_cost = (-1*((global/new_cost)-1))+0.1;  /*standardized to global*/ // 0.1 added to prevent new_cost getting to 0 and blowing things up
                    if (firm[i].tech == 1){ // tech = 0 - old tech,  tech = 1 - new tech
                        new_cost = (-1 *((global * (1 - (fudge_factor))/new_cost) - 1) ) + 0.1;
                    }
                      /*
                      line 329 - modify to include
                      if tech 1, keep standardization same
                      if tech2, global * (1 - some fudge factor) fudge factor -> /% val eg. 0.2 
                      fudge factor - vary btween -0.9 to 0.9 - 
                      */
         	 	    new_quantity = ((alpha + total_cost + (new_cost-firm[i].mcost))/(players+1))-new_cost;
         	 	    if (new_quantity<0.0) new_quantity=0.0;
         	 	    new_price = firm[i].price - (new_quantity-firm[i].quantity);
          	 	    new_profits = (new_price*new_quantity) - (new_cost*new_quantity) - fixed_cost;

			        if (randfloat() < firm[i].rule) 					/* assign rule */
         	 	 	    rule = 1;
         	 	    else
         	 	 	    rule = 0;

         	 	    if (rule == 0)									/* rule based on profitability */
        	 	    {
                        if (new_profits > firm[i].profit)
         	 	 	        firm[i].task[j] = new_task[j];
         	 	        else
         	 	 	        new_task[j] = firm[i].task[j];
                    };

         	 	    if (rule == 1)									/* rule based on best practice */
 			 	    {
                        for(j2 = 1; j2 <= firms; j2++)
  	  				    {
                            if ((firm[j2].profit * firm[j2].entrant) > (firm[leader].entrant * firm[leader].profit)) leader=j2;
				        };
 			 	    if (new_task[j] == firm[leader].task[j])
         	 	 	    firm[i].task[j] = new_task[j];
         	 	    else
         	 	 	    new_task[j] = firm[i].task[j];};

         	 	    if (rule == 2)									/* rule based on productivity */
 				    {
                        if ((new_cost/new_quantity) < (firm[i].mcost/firm[i].quantity))
         	 	 	        firm[i].task[j] = new_task[j];
         	 	    else
         	 	 	    new_task[j] = firm[i].task[j];};

         	 	    if (rule == 3)									/* rule based on marginal cost */
 			 	    {
                        if (new_cost < firm[i].mcost)
         	 	 	        firm[i].task[j] = new_task[j];
         	 	        else
         	 	 	        new_task[j] = firm[i].task[j];};
        	 	};
         	};
        };
    };
}

void parseInput(char input[]){
    printf("Enter parseinput\n");
    //printf("Entered input string : %s\n", input);
    char * inputs = strtok(input, ",");
    char data[100][100];
    int i = 0;
    while (inputs != NULL){
        //printf( "inputs: %s\n", inputs ); //printing each input
        strcpy(data[i], inputs);
        //printf("data[%i] = %s\n", i+1, data[i]);
        i++;
        inputs = strtok(NULL, ",");
    }

    for(int i = 0; i < 23; i++){
        char buffer[strlen(data[i])];
        strcpy(buffer, data[i]);

        char * inp_buffer = strtok(buffer, ":");
        char * key;
        char * value;
        int k = 0;
        char data2[2][100];
        while(inp_buffer != NULL){
            strcpy(data2[k], inp_buffer);
            k++;
            inp_buffer = strtok(NULL, ":");

        }
        if (strstr(data2[0], "numTimePeriods") != NULL){
                //printf("\nnum_time_periods = %s", data2[1]);
                number_of_time_periods = atoi(data2[1]);
        }
        if (strstr(data2[0], "numRuns") != NULL){
                //printf("\nnum_of_runs = %s", data2[1]);
                number_of_runs = atoi(data2[1]);
        }
        if (strstr(data2[0], "alphaStart") != NULL){
                //printf("\nalphaStart = %s", data2[1]);
                alphaStart = atof(data2[1]);
        }
        if (strstr(data2[0], "alphaEnd") != NULL){
                //printf("\nalphaEnd = %s", data2[1]);
                alphaEnd = atof(data2[1]);
        }
        if (strstr(data2[0], "betaStart") != NULL){
                //printf("\nbetaStart = %s", data2[1]);
                betaStart = atof(data2[1]);
                //printf("\n now betaStart = %.2f", betaStart);
        }
        if (strstr(data2[0], "betaEnd") != NULL){
                //printf("\nbetaEnd = %s", data2[1]);
                betaEnd = atof(data2[1]);
        }
        if (strstr(data2[0], "enterRuleStart") != NULL){
                //printf("\nenterRuleStart = %s", data2[1]);
                if (data2[1][0] != '\0'){
                    enterRuleStart = atof(data2[1]);
                    //printf("\n new enterRuleStart = %f", enterRuleStart);
                }
        }
        if (strstr(data2[0], "enterRuleEnd") != NULL){
                //printf("\nenterRuleEnd = %s", data2[1]);
                if (data2[1][0] != '\0'){
                    enterRuleEnd = atof(data2[1]);
                    //printf("\n new enterRuleEnd = %f", enterRuleEnd);
                }
        }
        if (strstr(data2[0], "exitRuleStart") != NULL){
                //printf("\nexitRuleStart = %s", data2[1]);
                if (data2[1][0] != '\0'){
                    exitRuleStart = atof(data2[1]);
                    //printf("\n exitRuleStart = %lf", exitRuleStart);
                }
        }
        if (strstr(data2[0], "exitRuleEnd") != NULL){
                //printf("\nexitRuleEnd = %s", data2[1]);
                if (data2[1][0] != '\0'){
                    exitRuleEnd = atof(data2[1]);
                    //printf("\n exitRuleEnd = %lf", exitRuleEnd);
                }
        }
        if (strstr(data2[0], "numTasksStart") != NULL){
                //printf("\nnumTasksStart = %s", data2[1]);
                if (data2[1][0] != '\0'){
                    numTasksStart = atoi(data2[1]);
                }
        }
        if (strstr(data2[0], "numTasksEnd") != NULL){
                //printf("\nnumTasksEnd = %s", data2[1]);
                if (data2[1][0] != '\0'){
                    numTasksEnd = atoi(data2[1]);
                }
        }
        if (strstr(data2[0], "numInteractionsStart") != NULL){
                //printf("\nnumInteractionsStart = %s", data2[1]);
                if (data2[1][0] != '\0'){
                    numInteractionsStart = atoi(data2[1]);
                }
        }
        if (strstr(data2[0], "numInteractionsEnd") != NULL){
                //printf("\nnumInteractionsEnd = %s", data2[1]);
                if (data2[1][0] != '\0'){
                    numInteractionsEnd = atoi(data2[1]);
                }
        }
        if (strstr(data2[0], "numFirmsStart") != NULL){
                //printf("\nnumFirmsStart = %s", data2[1]);
                if (data2[1][0] != '\0'){
                    numFirmsStart = atoi(data2[1]);
                }
        }
        if (strstr(data2[0], "numFirmsEnd") != NULL){
                //printf("\nnumFirmsEnd = %s", data2[1]);
                if (data2[1][0] != '\0'){
                    numFirmsEnd = atoi(data2[1]);
                }
        }
        if (strstr(data2[0], "mutationStart") != NULL){
                //printf("\nmutationStart = %s", data2[1]);
                if (data2[1][0] != '\0'){
                    mutationStart = atof(data2[1]);
                    //printf("\nmutationStart after = %f\n", mutationStart);
                }
        }
        if (strstr(data2[0], "mutationEnd") != NULL){
                //printf("\nmutationEnd = %s", data2[1]);
                if (data2[1][0] != '\0'){
                    mutationEnd = atof(data2[1]);
                    //printf("\nmutationEnd after = %f\n", mutationEnd);
                }
        }
        if (strstr(data2[0], "ruleParams") != NULL){
                //printf("\nruleParams = %s", data2[1]);
                if (data2[1][0] != '\0'){
                    rule_pram = atof(data2[1]);
                    //printf("\nruleParams after = %f\n", rule_pram);
                }
        }
        if (strstr(data2[0], "likelihoodNewTechStart") != NULL){
                //printf("\ntechParams = %s", data2[1]);
                if (data2[1][0] != '\0'){
                    likelihoodNewTechStart = atof(data2[1]);
                    //printf("\nruleParams after = %f\n", rule_pram);
                }
        }
        if (strstr(data2[0], "likelihoodNewTechEnd") != NULL){
                //printf("\ntechParams = %s", data2[1]);
                if (data2[1][0] != '\0'){
                    likelihoodNewTechEnd = atof(data2[1]);
                    //printf("\nruleParams after = %f\n", rule_pram);
                }
        }
        if (strstr(data2[0], "fudgeFactorStart") != NULL){
                if (data2[1][0] != '\0'){
                    fudgeFactorStart = atof(data2[1]);
                }
        }
        if (strstr(data2[0], "fudgeFactorEnd") != NULL){
                if (data2[1][0] != '\0'){
                    fudgeFactorEnd = atof(data2[1]);
                }
        }
    }
    printf("\nExit parseInput\n");
}

int main(int argc, char *argv[])
{
    printf("In main method:\n");

    /* parsing the input */
    char input_str[strlen(argv[1])];
    char temp_input[strlen(argv[1])];
    strcpy(temp_input, argv[1]);
    strcpy(input_str, argv[1]);

    parseInput(input_str);

    int timer=1;
    int batch=1;
    int runs=1;
    int i,j;
    FILE *stream, *stream2;
    printf("\nDone with parsing input\n");

    srand(121);

    /* Rule = random mix */
    setParams();
    printf("\n-------DONE SETTING PARAMS----------\n");

    stream = fopen("output1.txt","w");
    stream2 = fopen("stats.txt", "w");
    //new_tech_likelihood - tech_param
    //percentage_improvement_new_tech - fudge_factor
    fprintf(stream,"run	time	firm	entrant   technology	price	output	mcosts	profits	rule	N	K	firms	theta	global	rule_pram   new_tech_likelihood  percentage_improvement_new_tech   \n");
    fprintf(stream2, "run   time   Entrants   Price   Total_Output   Avg_Output   Min_Output   Max_Output   Avg_MCosts   Min_MCosts   Max_MCosts   Avg_Profits   Min_Profits   Max_Profits   Avg_Rule   Perc_New_Tech\n");
    while (runs <= number_of_runs)
    {
        parseInput(input_str);
	    parameterize();								/* gather parameter values */
	    seed_landscape();							/* initialize landscape */
        seed_landscape_new_tech();                 /* initialize landscape with respect to new tech */
	    find_global();								/* find global optima */
	    initialize_firms(runs);				/* assign tasks and rules to firms */
	    total_profit = 0.01;
        printf("\nRun %d\n", runs);
	    timer = 1;
        float price_per_time = 0;
	    float total_output = 0;
	    float min_output = 0;
	    float max_output = 0;
	    float avg_mcost = 0;
	    float min_mcost = 0;
	    float max_mcost = 0;
	    float avg_profit = 0;
	    float min_profit = 0;
	    float max_profit = 0;
	    float avg_rule;
        int num_new_tech = 0;
        int num_entrants = 0; 
        float new_tech_perc = 0.0;
	    // iterate - number of time periods
        
	    while (timer <= number_of_time_periods)
 	    {
            printf("\nTime period : %d\n", timer );
            price_per_time = 0;
	        total_output = 0;
	        min_output = 0;
	        max_output = 0;
	        avg_mcost = 0;
	        min_mcost = 0;
	        max_mcost = 0;
	        avg_profit = 0;
	        min_profit = 0;
	        max_profit = 0;
	        avg_rule = 0;
            num_new_tech = 0;
            num_entrants = 0; 
            new_tech_perc = 0.0;
 	        determine_entrants();					/* determine players and profits */
            //printf("\nnumber of firms = %d\n", firms);
		    for(i = 1; i <= firms; i++)
		    {
		        fprintf(stream,"%d	%d	%d	%d	%d %4.3f	%4.3f	%4.3f	%4.3f	%3.2f	%d	%d	%d	%3.2f	%4.3f	%4.3f %4.3f %4.3f\n",runs,timer,i,firm[i].entrant,firm[i].tech,firm[i].price,firm[i].quantity,firm[i].mcost,firm[i].profit,firm[i].rule,N,K,firms,mutation,global,rule_pram, tech_param, fudge_factor);
		        if (firm[i].entrant == 1){
                    num_entrants++;
                    if (firm[i].tech == 1){
                        num_new_tech++;
                    }
		            total_output = total_output + firm[i].quantity;
                    price_per_time = firm[i].entrant * firm[i].price; // entrant = 1 -> 1 * price. price is the same for all throughout the time

                    //fprintf(stream2, "\n firm[i].quantity = %4.3f\n", firm[i].quantity);
                    if (min_output == 0 && firm[i].quantity > 0){
                        min_output = firm[i].quantity;
                    }
                    if (firm[i].quantity !=0 && firm[i].quantity < min_output){
		                min_output = firm[i].quantity;
                    }
		            if (firm[i].quantity > max_output){
		                max_output = firm[i].quantity;
		            }

		            avg_mcost = avg_mcost + firm[i].mcost;
                    if (min_mcost == 0 && firm[i].mcost > 0){
                        min_mcost = firm[i].mcost;
                    }
		            if (firm[i].mcost != 0 && firm[i].mcost < min_mcost){
		                min_mcost = firm[i].mcost;
                    }
                    if (firm[i].mcost > max_mcost){
		                max_mcost = firm[i].mcost;
		            }

		            avg_profit = avg_profit + firm[i].profit;
                    if (min_profit == 0 && firm[i].profit > 0){
		                min_profit = firm[i].profit;
                    }
                    if (firm[i].profit != 0 && firm[i].profit < min_profit){
		                min_profit = firm[i].profit;
                    }
		            if (firm[i].profit > max_profit){
		                max_profit = firm[i].profit;
		            }
		            

		            avg_rule = (avg_rule + (firm[i].entrant * firm[i].rule)); // divide by number of players - average at each itersation
		        };
            }
            new_tech_perc = ((num_new_tech * 1.0 )/num_entrants);
            printf("new_tech_perc = %4.3f", new_tech_perc);
		    update();	/* update players positions */

            // "run   time   Entrants   Price   Total_Output   Avg_Output   Min_Output   Max_Output   Avg_MCosts   Min_MCosts   Max_MCosts   Avg_Profits   Min_Profits   Max_Profits   Avg_Rule" (price_per_time/players)
            if (players == 0){
                fprintf(stream2,"%d   %d   %d   %4.3f  %4.3f   %4.3f   %4.3f   %4.3f   %4.3f   %4.3f   %4.3f   %4.3f   %4.3f   %4.3f   %4.3f %4.3f\n" ,runs,timer,players,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0, 0.0);
            } else {
                fprintf(stream2,"%d   %d   %d   %4.3f  %4.3f   %4.3f   %4.3f   %4.3f   %4.3f   %4.3f   %4.3f   %4.3f   %4.3f   %4.3f   %4.3f %4.3f\n" ,runs,timer,players,(price_per_time/players),total_output,(total_output/players),min_output,max_output,(avg_mcost/players),min_mcost,max_mcost,(avg_profit/players),min_profit,max_profit,avg_rule/players, new_tech_perc);
            }
            timer++;
   	    };
        runs++;
    };
    fclose(stream2);
    fclose(stream);
    printf("\n Done!\n");
    
}
