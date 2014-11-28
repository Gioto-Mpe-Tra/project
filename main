#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "Item.h"
#include "Lsh.h"
#include "Clustering.h"

#include <cstdlib>

using namespace std;


// -d inputfile -c configfile -o output file

int main(int argc, char** argv) {
    int k = 4;
    int L = 5;
    int c = 4;  
	char temp[200];   
    int number_of_clusters;
int number_of_hash_functions;
int number_of_hash_tables;
int clarans_set_fraction;
int clarans_iterations;
    //char inputfile[] = "DataHamming.txt";
	
 	
    if (argc != 7) {
        cout << " Syntax error: dwse swsta tis times se parakalw \n" << endl;
    } else {
        for (int i = 1; i < argc; i=i+2) {
            if ((strcmp(argv[i], "-d") != 0) && (strcmp(argv[i], "-c") != 0) &&  (strcmp(argv[i], "-o") != 0)) {
                cout << "Syntax error \n" << endl;
                return -1;
            }
        }
        
        for (int i = 1; i < argc; i = i + 2) {
            if (strcmp(argv[i], "-d") == 0)
                strcpy(clustering.inputfile, argv[i + 1]);
            if (strcmp(argv[i], "-c") == 0)
                strcpy(clustering.configfile, argv[i + 1;
            if (strcmp(argv[i], "-o") == 0)
                strcpy(clustering.outputfile, argv[i + 1]);
        }

	ifstream ifs(clustering.configfile);
	 if (!ifs) {
        cout << "File " << clustering.configfile << " is missing ... \n";
        return;
    } else
	{	
		while(!ifs.eof()){
			ifs>>temp
			if (strcmp(temp, "number_of_clusters") == 0 )
				{ifs>> temp;
				number_of_clusters = atoi (temp);}
			if (strcmp(temp, "number_of_hash_functions") == 0 )
				{ifs>> temp;
				number_of_hash_functions = atoi (temp);}
			if (strcmp(temp, "number_of_hash_tables") == 0 )
				{ifs>> temp;
				number_of_hash_tables = atoi (temp);}
			if (strcmp(temp, "clarans_set_fraction") == 0 )
				{ifs>> temp;
				clarans_set_fraction = atoi (temp);}		}
			if (strcmp(temp, "clarans_iterations") == 0 )
				{ifs>> temp;
				clarans_iterations = atoi (temp);}
}         

    double t1, t2, cpu_time;
    struct tms tb1, tb2;
    double ticspersec;
    int i, sum = 0;
    
    ticspersec = (double) sysconf(_SC_CLK_TCK);
    t1 = (double) times(&tb1);
    
    for (i = 0; i < 100000000; i++)
        sum += i;
    
    
    t2 = (double) times(&tb2);
    cpu_time = (double) ((tb2.tms_utime + tb2.tms_stime) - (tb1.tms_utime + tb1.tms_stime));
    printf("Run time was %lf sec (REAL time) although we used the CPU for %lf sec (CPU time).\n", t2 - t1) / ticspersec, cpu_time / ticspersec);






    
    Clustering clustering;
    clustering.createClusteringProblem(k, L, c);
    clustering.readFromFile(inputfile);
    clustering.solve();

    clustering.destroy();
    
    return 0;
}

