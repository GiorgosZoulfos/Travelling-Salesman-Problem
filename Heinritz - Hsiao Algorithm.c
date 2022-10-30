#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10000
#define square(x) ((x)*(x))
#define numLoops 100000000

float X[N], Y[N]; 			// coordiantes of the cities
int route[N+1]; 	   			// shows the order that the cities appear in the route
float Distance[N][N];  	// contains the distance between all cities
float totalDistance = 0; 	// contains the total distance of the route

void makeCities(){

	for(int i=0; i<N; i++){
		X[i] = ((float)rand()/(float)(RAND_MAX)) * 1000;
		Y[i] = ((float)rand()/(float)(RAND_MAX)) * 1000;
	}
	
}

float calculateDistance(int c1, int c2){
	
	return sqrt(square(X[c1] - X[c2]) + square(Y[c1] - Y[c2]));
	
}

void printRoute(){
	
	for (int i=0; i<N+1; i++){
		printf("%d\t", route[i]);
	}
	printf("\n");
	
}


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
			printf("%f\t", Distance[i][j]);
		}
		printf("\n");
	}
}

int findNearestCity(int city){
	
	int ind = 0;
	int min = 1415;

	for (int i=1; i<N; i++) {
		if ((Distance[city][i] < min) && (i != city)) {
			ind = i;
			min = Distance[city][i];
		}
	}
	
	return ind;
	
}


int main(){
	
	int currentCity = 0;
	int nextCity;
	
	makeCities();
	computeDistanceMatrix();
	
	//printDist();
	
	route[0] = currentCity;
	
	for (int i=1; i<N; i++) {
		
		nextCity = findNearestCity(currentCity);
		route[i] = nextCity;
		totalDistance += Distance[currentCity][nextCity];
		//printf("%d %d %d\n", currentCity, nextCity, i);
		
		for (int j=0; j<N; j++){
			
			Distance[currentCity][j] = 1415;
			Distance[j][currentCity] = 1415;
			
		}
		
		currentCity = nextCity;
		
	}
	
	totalDistance += Distance[currentCity][0];
	printf("Total distance: %f\n", totalDistance);
	//printRoute();
	//printDist();
	
	return 0;
	
}



	
	
	