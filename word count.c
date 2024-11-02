//This counts the number of occurences of each word in the file "cruel summer.txt"
//It then sorts them using bubble sort and prints them to the screen

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int inList(char* list[], int len, char* str){
  for (int i = 0; i < len; i++){
    if (!strcmp(list[i], str)){
      return i;
    }
  }
  return -1;
}

int main(void) {

  FILE *fp;
  fp = fopen("cruel summer.txt", "r");

  char* words[1000];
  char word[100];
  int letter = 0;
  int index = 0;
  char c;
  while (fscanf(fp, "%c", &c) != EOF){
    if (c == ' ' || c == '\n' || c == EOF){ 
      word[letter] = '\0';
      words[index] = (char*)malloc((letter+1)*sizeof(char)); //allocate memory here
      strcpy(words[index], word);
      letter = 0;
      index++;
    } else {
      word[letter] = c;
      letter++;
    }
  }
  
  char* word_index[1000];
  int occur[1000];


  printf("Words in Cruel Summer by Taylor Swift sorted by occurances\n\n");
  
  int size = 0;
  fclose(fp);
  for (int i = 0; i < index - 1; i++){

    int il = inList(word_index, size, words[i]);
    if (il == -1) {
      word_index[size] = (char*)malloc((strlen(words[i])+1)*sizeof(char));
      strcpy(word_index[size], words[i]);
      occur[size] = 1;
      size++;
    } else{
      occur[il]++;
    }
    free(words[i]);
  }

  printf("\n\n");

  int holdint;
  char* holdstr;
  for (int i = 0; i < size; i++){
    for (int j = 0; j < i; j++){
      if (occur[i] > occur[j]){
        holdint = occur[i];
        holdstr = (char*)malloc((strlen(word_index[i])+1)*sizeof(char));
        strcpy(holdstr, word_index[i]);
        occur[i] = occur[j];
        strcpy(word_index[i], word_index[j]);
        occur[j] = holdint;
        strcpy(word_index[j], holdstr);
      }
    }
  }

  free(holdstr);

  for (int i = 0; i < size; i++){
    printf("%s: %d\n", word_index[i], occur[i]);
    free(word_index[i]);
  }
  return 0;
}