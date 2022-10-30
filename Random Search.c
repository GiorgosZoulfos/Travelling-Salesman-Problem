#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10000
#define square(x) ((x)*(x))
#define numLoops 100000000

float X[N], Y[N]; 			// coordiantes of the cities
int route[N+1]; 	   			// shows the order that the cities appear in the route
float distance[N];  			// contains the distance between current city and next city of the route
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

void createRandomRoute(){
	
	route[0] = 0;
	for (int i=1; i<N; i++) {
		route[i] = i;
		distance[i-1] = calculateDistance(i, i-1);
		totalDistance += distance[i-1];
	}
	route[N] = 0;
	distance[N-1] = calculateDistance(0, N-1);
	totalDistance += distance[N-1];

}

void printRoute(){
	
	for (int i=0; i<N+1; i++){
		printf("%d\t", route[i]);
	}
	printf("\n");
}

void printDistance(){
	
	for (int i=0; i<N; i++){
		printf("%f\t", distance[i]);
	}
	printf("\n");
}

void printCities(){
	
	for (int i=0; i<N; i++){
		printf("%f %f \n", X[i], Y[i]);
	}
	printf("\n");
}

void newRoute(){
	
	int city1 = rand()%(N-1) + 1;
	int city2 = rand()%(N-1) + 1;
	
	float oldDist , newDist1, newDist2, newDist3, newDist4;
	
	oldDist = distance[city1-1] + distance[city1] + distance[city2-1] + distance[city2];
	if (abs(city1-city2) != 1) {
		newDist1 = calculateDistance(route[city2], route[city1-1]);
		newDist2 = calculateDistance(route[city2], route[city1+1]);
		newDist3 = calculateDistance(route[city1], route[city2-1]); 
		newDist4 = calculateDistance(route[city1], route[city2+1]);
	} else if ((city2 - city1) == 1) {
		newDist1 = calculateDistance(route[city2], route[city1-1]);
		newDist2 = calculateDistance(route[city2], route[city1]);
		newDist3 = calculateDistance(route[city1], route[city2]); 
		newDist4 = calculateDistance(route[city1], route[city2+1]);
	} else{
		newDist1 = calculateDistance(route[city2], route[city1]);
		newDist2 = calculateDistance(route[city2], route[city1+1]);
		newDist3 = calculateDistance(route[city1], route[city2-1]); 
		newDist4 = calculateDistance(route[city1], route[city2]);
	}		
	// printf("%d %d %f %f %f %f  \n",city1, city2,newDist1,newDist2,newDist3,newDist4);
	// printf("%d %d %f %f  %f \n",city1, city2, oldDist, (newDist1+newDist2+newDist3+newDist4), totalDistance );
	
	if ((newDist1+newDist2+newDist3+newDist4) < oldDist) {
		int temp = route[city1];
		route[city1] = route[city2];
		route[city2] = temp;
		
		distance[city1-1] = newDist1;
		distance[city1] = newDist2;
		distance[city2-1] = newDist3;
		distance[city2] = newDist4;
		
		totalDistance += (newDist1+newDist2+newDist3+newDist4) - oldDist;
		
	}
	
}

int main(){
	
	makeCities();
	createRandomRoute();
	
	printf("%f \n", totalDistance);
	
	for (int i=0; i<numLoops; i++){
		newRoute();
	}

	printf("%f \n", totalDistance);
	
	return 0;
	
}

