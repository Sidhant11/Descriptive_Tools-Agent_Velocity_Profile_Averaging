//y and z are reversed
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>
# define cy 201   //Total time in the time-series
# define g 500   //Number of agents/particles
# define s cy*g
# define pi 3.14
# define rad_1 1.0  //Particle size 1


float dist(float **V)
{
    int i, j, k, gamma_dot = 1;
    float rad_2 = 1.4;  //Particle size 2
    float xm=17.6389;  // x-maximum dimension
    float ym=17.6389;  // y-maximum dimension
    float zm=17.6389;  // z-maximum dimension
    int ymm, ypos; 
    ymm = ceil(ym);    
    printf("\n %d \n",ymm);
    int init_cycle= 10, end_cycle=11, n_cy = end_cycle - init_cycle; //start_time and end_time for time-series averaging
    FILE *outfile_ptr;
    
    float **V_big, **V_big_avg;
    int *nb, *ns;
    float *nb_avg, *V_y_bavg, *V_z_bavg, *V_y_big_tavg, *V_z_big_tavg, *V_x_bavg, *V_x_big_tavg;

    V_big = (float **) calloc(ymm, sizeof(float *));
    for (i = 0; i < ymm; i++)
        V_big[i] = (float *)calloc(3, sizeof(float));

   V_big_avg = (float **) calloc(ymm, sizeof(float *));
    for (i = 0; i < ymm; i++)
        V_big_avg[i] = (float *)calloc(3, sizeof(float));

    nb = (int *) calloc(ymm, sizeof(int));
    nb_avg = (float *) calloc(ymm, sizeof(float));
    V_y_bavg = (float *) calloc(ymm, sizeof(float));
    V_z_bavg = (float *) calloc(ymm, sizeof(float));
    V_x_big_tavg = (float *) calloc(ymm, sizeof(float));
    V_y_big_tavg = (float *) calloc(ymm, sizeof(float));
    V_z_big_tavg = (float *) calloc(ymm, sizeof(float));

    outfile_ptr = fopen("Avg_Velocity.txt","w");
    if (outfile_ptr == NULL)
    {
        printf("\n Cannot open file PartPos.txt");
        exit(1);
    }
   for(i = init_cycle;i<end_cycle;i++)
   { 
      for(j=0;j<g;j++)
        {
              ypos = floor(V[j+i*g][4]);
              V_y_bavg[ypos] = V_y_bavg[ypos] + V[j+i*g][7];
	      V_z_bavg[ypos] = V_z_bavg[ypos] + V[j+i*g][6];
              V_x_bavg[ypos] = V_x_bavg[ypos] + V[j+i*g][5];
              nb[ypos]++;
           }
          
	for(k = 0; k < ymm; k++)
        {
		if(nb[k]!=0)
		{
			V_y_bavg[k] = V_y_bavg[k]/nb[k];
			V_z_bavg[k] = V_z_bavg[k]/nb[k];
			
		}
	      	 V_y_big_tavg[k] = V_y_big_tavg[k] + V_y_bavg[k];
                 V_x_big_tavg[k] = V_x_big_tavg[k] + V_x_bavg[k]; 
	     	 V_z_big_tavg[k] = V_z_big_tavg[k] + V_z_bavg[k];
       }

	for(k = 0; k < ymm; k++)
	{
         nb_avg[k] = nb_avg[k] + nb[k];
       	 V_big_avg[k][0] = V_big_avg[k][0] + V_big[k][0];
       	 V_big_avg[k][1] = V_big_avg[k][1] + V_big[k][1];
       	 V_big_avg[k][2] = V_big_avg[k][2] + V_big[k][2];
	 nb[k] = 0; 
	 V_big[k][0]=0.00; V_big[k][1]=0.00; V_big[k][2]=0.00;
	 V_y_bavg[k] = 0; 
	 V_z_bavg[k] = 0;
	}
}
	for(k = 0; k < ymm; k++)
        {
	   fprintf(outfile_ptr,"%d %.2f %f %f %f \n", k, nb_avg[k]/(n_cy),V_x_big_tavg[k]/n_cy, V_y_big_tavg[k]/n_cy,V_z_big_tavg[k]/n_cy);
    	}

	fclose(outfile_ptr);

    fclose(outfile_ptr);
    return 1;
    
}
int main()
{
    int i;
    float elapsed;
    float distance =0.0;
    clock_t start, end;
    FILE *infile_ptr1;
    FILE *infile_ptr2;
    
    float **V;
    start = clock();
    V = (float **) calloc(s, sizeof(float *));
    for (i = 0; i < s; i++)
        V[i] = (float *)calloc(11, sizeof(float));
   
    infile_ptr1 = fopen("T.txt","r");
    if (infile_ptr1 == NULL)
    {
        printf("\n can not open T.txt");
        exit(1);
    }
    
    for (i = 0; i < s; i++)
    {
        fscanf(infile_ptr1, "%e %e %e %e %e %e %e %e %e %e %e \n", &V[i][0], &V[i][1], &V[i][2], &V[i][3], &V[i][4], &V[i][5], &V[i][6], &V[i][7], &V[i][8], &V[i][9], &V[i][10]);
        
    }
    fclose(infile_ptr1);
    
    distance = dist(V);
    end = clock();
    elapsed = ((double) (end - start))/ CLOCKS_PER_SEC;
    printf("\n the elapsed time is: %-1.12f", elapsed);
}   
