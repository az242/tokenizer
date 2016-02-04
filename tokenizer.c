/*
 * tokenizer.c
 */
#include <stdio.h>
#include "string.h"
/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */
const int WORD= 1;
const int DECIMAL=2;
const int OCTAL = 3;
const int HEXA = 4;
const int FLOAT =5;
const int COP =6;
const int ERROR=-1; 
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
  temp->type =ERROR;
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
  tk->type = 0;
  int beginning = tk->index;
  //check order
  if(tk->token[tk->index]=='0' && tk->token[tk->index+1]=='x'){
    //Hexa
    while((tk->token[tk->index]>='A' && tk->token[tk->index]<='F')||(tk->token[tk->index]>='0' && tk->token[tk->index]<='9')){
      //while still a hexa
      tk->index++;
    }
    tk->type=HEXA;
    char temp[(tk->index-beginning)+1];
    memcpy(temp, tk[beginning],tk->index-beginning);
    char temp[tk->index-beginning]='\0';
    return temp;
  }else if((tk->token[tk->index]>='A' && tk->token[tk->index]<='Z')||(tk->token[tk->index]>='a' && tk->token[tk->index]<='z')){
    //word
    while((tk->token[tk->index]>='A' && tk->token[tk->index]<='Z')||(tk->token[tk->index]>='a' && tk->token[tk->index]<'z')){
      //while still a word
      tk->index++;
    }
    char temp[(tk->index-beginning)+1];
    memcpy(temp,tk[beginning],tk->index-beginning);
    char temp[tk->index-beginning]='\0';
    tk->type=WORD;
    return temp;
  }else if(tk->token[tk->index]>='0' && tk->token[tk->index]<='9'){
    //Octal Decimal or Integer Decimal or FLOAT
    //TODO
    int beginning = tk->index;
    int foundE=0;
    tk->type = DECIMAL;
    if(tk->token[tk->index]=='0'){
      tk->type = OCTAL;
    }else if(tk->token[tk->index]=='.'){
      tk->type = FLOAT;
      tk->index++;
    }
    while((tk->token[tk->index]>='0' && tk->token[tk->index]<='9')||tk->token[tk->index]=='.'){
      if(tk->type==DECIMAL){
	if(tk->token[tk->index]=='.'){
	  tk->type = FLOAT;
	}
      }else if(tk->type==FLOAT){
	if(tk->token[tk->index]=='.'){
	  //we hit 2 periods. most likely will end token here
	  break;
	}else if(tk->token[tk->index+1]=='e'){
	  if(foundE==0){
	    foundE=1;
	  }else{
	    break;
	  }
	  if(tk->token[tk->index+2]=='-'){
	    tk->index++;
	  }
	  tk->index++;
	}
      }else if(tk->type == OCTAL){
	if(tk->token[tk->index]>'7' && tk->token[tk->index]<='9'){
	  //end Octal token here
	  break;
	}else if(tk->token[tk->index]=='.'){
	  //end token here
	  break;
	}
      }
      tk->index++;
    }
    char temp[(tk->index-beginning)+1];
    memcpy(temp,tk[beginning],tk->index-beginning);
    char temp[tk->index-beginning]='\0';
    return temp;
  }else if(tk->token[tk->index]<'0' || (tk->token[tk->index]>'9' && tk->token[tk-index]<'A') || (tk->token[tk->index]>'Z' && tk->token[tk->index]<'a') || tk->token[tk->index]>'z'){
    //COP
    //TODO
    tk->type = 6;
    switch(tk->token[tk->index]){//Switch START
    case '=':
      if(tk->token[tk->index+1]){
	//+
	tk->index++;
	return "=+";
      }else if(tk->token[tk->index+1]){
	//-
	tk->index++;
	return "=-";
      }else if(tk->token[tk->index+1]){
	//<
	tk->index++;
	return "=<";
      }else if(tk->token[tk->index+1]){
	//>
	tk->index++;
	return "=>";
      }
      break;
    case '<':
      return "<";
      break;
    }//SWITCH END
  }
  //TEST CODE- this is for spaces, or any other deliminator
  tk->index++;
  //if this line of code executes it means
  //that it did not find a valid token
  //and is incrementing by 1 until we do
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
      printf("hexadeciaml integer \"%s\"",outputStream);
      break;
    case 5:
      //Float
      printf("float point \"%s\"",outputStream);
      break;
    case 6:
      //COP 
      printf("%s",outputStream);
      break;
    case -1:
      //Error!
      printf("something happened that wasn't suppose to happen!\n");
      break;
    }
  }
  return 0;
}
