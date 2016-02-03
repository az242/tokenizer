/*
 * tokenizer.c
 */
#include <stdio.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
  char* token;
  int type;
  int index;
  //type is based on strings 
  /*1.WORD
   *2.DECIMAL
   *3.OCTAL
   *4.HEXA
   *5.FLOAT
   *6.COP (C operator)
   *-1.ERROR
   */
};

typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 * 
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate( char * ts ) {
  TokenizerT *temp = (TokenizerT*) malloc(sizeof(TokenizerT));
  temp->token = ts;
  temp->type = -1;
  temp->index = 0;
  return temp;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {
  tp->index = NULL;
  tk->token = NULL;
  tk->type = NULL;
  free(tk);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken( TokenizerT * tk ) {
  //Here we will set type value  as well as manipulate the string in TokenizerT Struct
  //TODO
  int stop = 0;
  tk->type = 0;
  while(stop!=1){
    if(tk->token[tk->index].
    if(tk->token[tk->index]=='0' && tk->token[tk->index+1]=='x'){
      tk->type=4;
    }
  }
  return NULL;
}

/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {
  if(argc!=2){
    printf("Error! More then one input!");
    return 0;
  }
  char* outputStream;
  TokenizerT* token = TKCreate(argv[1]);
  while((outputStream = TKGetNextToken(token))!='0'){
    //while outputStream (which is set to the val of TKGetNextToken) is not 0 THEN
    switch(token->type){
      //switch case based on type of token set inside call of TKGetNextToken
    case 1:
      printf("Word \"%s\"",outputStream);
      //word
      break;
    case 2:
      //deciaml
      printf("decimal integer \"%s\"",outputStream);
      break;
    case 3:
      //octal
      printf("octal integer \"%s\"",outputStream);
      break;
    case 4:
      //Hexa
      printf("hexadeciaml integer \"%s\"",outputStream;
      break;
    case 5:
      //Float
      printf("float point \"%s\"",outputStream);
      break;
    case 6:
      //COP (C Operator)
	     //TODO
      break;
    case -1:
      //Error!
      printf("something happened that wasn't suppose to happen!\n");
      break;
    }
  }
  return 0;
}
