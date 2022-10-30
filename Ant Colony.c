#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 10000
#define square(x) ((x)*(x))
#define ANTS 4
#define a 0.1
#define b 0.9
#define ER 0.1 
#define NUM_LOOPS 4
#define PHER 200*N

float X[N], Y[N]; 						// coordinates of the cities
int Route[ANTS][N+1]; 	   			// shows the order that the cities appear in the route for each
float Distance[N][N];  				// contains the distance between all cities
float totalDistance[ANTS] ; 		// contains the total distance of the route for each ant
int Visited[ANTS][N];					// shows which cities each ant has already visited in a loop
float Prob[ANTS][N];					// shows the probability of an ant to go to each city
float Pheromone[N][N];				// shows the pheromone between two cities


void makeCities(){

	for(int i=0; i<N; i++){
		X[i] = ((float)rand()/(float)(RAND_MAX)) * 1000;
		Y[i] = ((float)rand()/(float)(RAND_MAX)) * 1000;
	}
	
}

float calculateDistance(int c1, int c2){
	
	return sqrt(square(X[c1] - X[c2]) + square(Y[c1] - Y[c2]));
	
}

/*void printRoute(){
	
	for (int i=0; i<N+1; i++){
		printf("%d\t", Route[i]);
	}
	printf("\n");
	
}*/


void computeDistanceMatrix(){
	
	for (int i=0; i<N; i++){
		for (int j=0; j<i+1; j++){
			Distance[i][j] = calculateDistance(i, j);
			Distance[j][i] = Distance[i][j];
			//printf("%d %d\n",i,j);
		}
	}
	
}

void printDist(){
	for (int i=0; i<N; i++){
		for (int j=0; j<N; j++){
			printf("%.1f\t", Distance[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int chooseNextCity(int ant, int currentCity){
	
	float den = 0;
	for (int i = 0; i<N; i++){
		den += pow(Pheromone[currentCity][i], a)*pow(Distance[currentCity][i], b);
	}
	
	for (int i = 0; i<N; i++){
		if (i != currentCity && Visited[ant][i] != 1){
			Prob[ant][i] = pow(Pheromone[currentCity][i], a)*pow(Distance[currentCity][i], b)/den;
		} else {
			Prob[ant][i] = 0;
		}
	}
	
	float sum = 0;
	for (int i = 0; i<N; i++){
		sum += Prob[ant][i];
	}
	
	float pr = (sum*rand())/(RAND_MAX);
	float thr = 0;
	int ind;
	
	for (int i = 0; i<N; i++){
		thr += Prob[ant][i];
		if (pr >= (thr - Prob[ant][i]) && pr < thr){
			ind = i;
		}
	}
	
	return ind;
	
}

void updatePheromone(){
	
	for (int row = 0; row<N; row++){
		for (int col = 0; col<N; col++){
			Pheromone[row][col] = (1 - ER) * Pheromone[row][col]; 
		}
	}
	
	for (int ant = 0; ant<ANTS; ant++){
		for (int k = 0; k<N; k++){
			Pheromone[Route[ant][k]][Route[ant][k+1]] += PHER/Distance[Route[ant][k]][Route[ant][k+1]];
			Pheromone[Route[ant][k+1]][Route[ant][k]] = Pheromone[Route[ant][k]][Route[ant][k+1]];
		}
	}
	
}

void  initPheromone(){
	
	for (int row = 0; row<N; row++){
		for (int col = 0; col<N; col++){
			Pheromone[row][col] = 1; 
		}
	}
	
}

void printPher(){
	
	for (int row = 0; row<N; row++){
		for (int col = 0; col<N; col++){
			printf("%.1f ", Pheromone[row][col]); 
		}
		printf("\n");
	}
	printf("\n");
}

int main(){
	
	makeCities();
	computeDistanceMatrix();
	//printDist();
	initPheromone();
	//printPher();
	float minDistance = N*1415;
	
	for (int loop = 0; loop<NUM_LOOPS; loop++){
		
		for (int ant = 0; ant<ANTS; ant++){
			
			totalDistance[ant] = 0;
			for (int i=0; i<N; i++){
				Visited[ant][i] = 0;
			}
			
			Route[ant][0] = rand() % N;
			//printf("Ant %d  City %d\n",  ant, Route[ant][0]);
			Visited[ant][Route[ant][0]] = 1;
			int currentCity = Route[ant][0];
			
			for(int city = 1; city<N; city++){
				
				int nextCity = chooseNextCity(ant, currentCity);
				Visited[ant][nextCity] = 1;
				Route[ant][city] = nextCity;
				totalDistance[ant] += Distance[currentCity][nextCity];
				currentCity = nextCity;
				
			}
			
			Route[ant][N] = Route[ant][0];
			totalDistance[ant] += Distance[currentCity][Route[ant][0]];
			
			//printf("%d %f\n", ant, totalDistance[ant]);
			
			if (totalDistance[ant] < minDistance){
				minDistance = totalDistance[ant];
			}
			
		}
		
		updatePheromone();
		//printPher();
		
	}
			
	printf("Total distance: %f\n", minDistance);
	
	return 0;
	
}



	
	
	