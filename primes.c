//This code will take in 1 integer argument N, and it will then calculate the first N prime numbers.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void find_primes(int num_primes, int **pointer){ //takes a pointer to a pointer

  
  *pointer = (int*) malloc(num_primes * sizeof(int)); //allocate n * int bytes to memory. Have pointer point to it.

  int primes_found = 0;
  int is_prime;
  for (int num = 2; primes_found < num_primes; num++){
    is_prime = 1;
    for (int div = 2; div <= sqrt(num); div++) {
      if (num % div == 0){
        is_prime = 0;
      }
    }
    if (is_prime || num == 2){
      (*pointer)[primes_found] = num;
      //the address "pointer" is pointing to is a pointer to the first item of the array
      primes_found++;
    }
  }
}


int main(int argc, char *argv[]) {

  int number;
  //fefault to 10 if no arguments provided
  
  if (argc ==1){
    number = 10;
  } else {
    //convert string argument to integer
    number = atoi(argv[1]);
  }

  //create a pointer to an int
  int *pointer;

  //find (number) primes and store them at the address that the pointer is stored at
  find_primes(number, &pointer);

  printf("Displaying the fist %d prime numbers:\n", number);
  for (int i = 0; i < number; i++){
    printf("%d\n", pointer[i]);
  }

  free(pointer);
  return 0;
}