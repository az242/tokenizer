/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
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
const int BAD_TOKEN= 0;
const int QUOTE = 7;
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
  if(tk->token[tk->index]=='\0'){
    return NULL;
  }
  tk->type = 0;
  while(tk->token[tk->index]=='\n' || tk->token[tk->index]=='\t' || tk->token[tk->index]==' ' || tk->token[tk->index]=='\v' || tk->token[tk->index]=='\f' || tk->token[tk->index]=='\r'){
    tk->index++;
  }
  int beginning = tk->index;
  //check order
  if(tk->token[tk->index]=='0' && tk->token[tk->index+1]=='x'){
    //Hexa
    tk->index++;tk->index++;
    while((tk->token[tk->index]>='A' && tk->token[tk->index]<='F')||(tk->token[tk->index]>='0' && tk->token[tk->index]<='9')||(tk->token[tk->index]>='a' && tk->token[tk->index]<='f')){
      //while still a hexa
      tk->index++;
    }
    tk->type=HEXA;
    if(tk->index-beginning==2){
      tk->type = 0;
      return "0x";
    }
    char *temp= (char*) malloc(sizeof(char)*((tk->index-beginning)+1));
    memcpy(temp, tk->token+beginning,(tk->index)-beginning);
    temp[tk->index-beginning]='\0';
    return temp;
  }else if((tk->token[tk->index]>='A' && tk->token[tk->index]<='Z')||(tk->token[tk->index]>='a' && tk->token[tk->index]<='z')){
    //word
    if(strncmp("if",tk->token+beginning,2)==0){
      //if
      tk->index=tk->index+2;
      tk->type = COP;
      return "C Key Word \"if\"";
    }else if(strncmp("sizeof",tk->token+beginning,6)==0){
      //sizeof
      tk->index=tk->index+6;
      tk->type = COP;
      return "C Key Word \"sizeof\"";
    }else if(strncmp("while",tk->token+beginning,5)==0){
      //while
      tk->index=tk->index+5;
      tk->type = COP;
      return "C Key Word \"while\"";
    }else if(strncmp("for",tk->token+beginning,3)==0){
      //for
      tk->index=tk->index+3;
      tk->type = COP;
      return "C Key Word \"for\"";
    }else if(strncmp("else",tk->token+beginning,4)==0){
      //else
      tk->index=tk->index+4;
      tk->type = COP;
      return "C Key Word \"else\"";
    }else if(strncmp("return",tk->token+beginning,6)==0){
      //return
      tk->index=tk->index+6;
      tk->type = COP;
      return "C Key Word \"return\"";
    }else if(strncmp("switch",tk->token+beginning,6)==0){
      //switch
      tk->index=tk->index+6;
      tk->type = COP;
      return "C Key Word \"switch\"";
    }else if(strncmp("case",tk->token+beginning,4)==0){
      //case
      tk->index=tk->index+4;
      tk->type = COP;
      return "C Key Word \"case\"";
    }else if(strncmp("int",tk->token+beginning,3)==0){
      //int
      tk->index=tk->index+3;
      tk->type = COP;
      return "C Key Word \"int\"";
    }else if(strncmp("char",tk->token+beginning,4)==0){
      //char
      tk->index=tk->index+4;
      tk->type = COP;
      return "C Key Word \"char\"";
    }else if(strncmp("double",tk->token+beginning,6)==0){
      //double
      tk->index=tk->index+6;
      tk->type = COP;
      return "C Key Word \"double\"";
    }else if(strncmp("float",tk->token+beginning,5)==0){
      //float
      tk->index=tk->index+5;
      tk->type = COP;
      return "C Key Word \"float\"";
    }else if(strncmp("short",tk->token+beginning,5)==0){
      //short
      tk->index=tk->index+5;
      tk->type = COP;
      return "C Key Word \"short\"";
    }else if(strncmp("static",tk->token+beginning,6)==0){
      //static
      tk->index=tk->index+6;
      tk->type = COP;
      return "C Key Word \"static\"";
    }else if(strncmp("struct",tk->token+beginning,6)==0){
      //struct
      tk->index=tk->index+6;
      tk->type = COP;
      return "C Key Word \"struct\"";
    }else if(strncmp("union",tk->token+beginning,5)==0){
      //union
      tk->index=tk->index+5;
      tk->type = COP;
      return "C Key Word \"union\"";
    }else if(strncmp("enum",tk->token+beginning,4)==0){
      //enum
      tk->index=tk->index+4;
      tk->type = COP;
      return "C Key Word \"enum\"";
    }else if(strncmp("do",tk->token+beginning,2)==0){
      //do
      tk->index=tk->index+2;
      tk->type = COP;
      return "C Key Word \"do\"";
    }else if(strncmp("continue",tk->token+beginning,8)==0){
      //continue
      tk->index=tk->index+8;
      tk->type = COP;
      return "C Key Word \"continue\"";
    }else if(strncmp("default",tk->token+beginning,7)==0){
      //default
      tk->index=tk->index+7;
      tk->type = COP;
      return "C Key Word \"default\"";
    }else if(strncmp("extern",tk->token+beginning,6)==0){
      //extern
      tk->index=tk->index+6;
      tk->type = COP;
      return "C Key Word \"extern\"";
    }else if(strncmp("break",tk->token+beginning,5)==0){
      //break
      tk->index=tk->index+5;
      tk->type = COP;
      return "C Key Word \"break\"";
    }else if(strncmp("goto",tk->token+beginning,4)==0){
      
      tk->index=tk->index+4;
      tk->type = COP;
      return "C Key Word \"goto\"";
    }else if(strncmp("void",tk->token+beginning,4)==0){
      tk->index=tk->index+4;
      tk->type = COP;
      return "C Key Word \"void\"";
    }else if(strncmp("const",tk->token+beginning,5)==0){
      tk->index=tk->index+5;
      tk->type = COP;
      return "C Key Word \"const\"";
    }else if(strncmp("signed",tk->token+beginning,6)==0){
      tk->index=tk->index+6;
      tk->type = COP;
      return "C Key Word \"signed\"";
    }else if(strncmp("volatile",tk->token+beginning,8)==0){
      tk->index=tk->index+8;
      tk->type = COP;
      return "C Key Word \"volatile\"";
    }else if(strncmp("auto",tk->token+beginning,4)==0){
      tk->index=tk->index+4;
      tk->type = COP;
      return "C Key Word \"auto\"";
    }else if(strncmp("long",tk->token+beginning,4)==0){
      tk->index=tk->index+4;
      tk->type = COP;
      return "C Key Word \"long\"";
    }else if(strncmp("typedef",tk->token+beginning,7)==0){
      tk->index=tk->index+7;
      tk->type = COP;
      return "C Key Word \"typedef\"";
    }else if(strncmp("unsigned",tk->token+beginning,8)==0){
      tk->index=tk->index+8;
      tk->type = COP;
      return "C Key Word \"unsigned\"";
    }
    while((tk->token[tk->index]>='A' && tk->token[tk->index]<='Z')||(tk->token[tk->index]>='a' && tk->token[tk->index]<='z')||(tk->token[tk->index]>='0' && tk->token[tk->index]<='9')){
      //while still a word
      tk->index++;
    }
    char *temp = (char*) malloc(sizeof(char)*((tk->index-beginning)+1));
    memcpy(temp,tk->token+beginning,tk->index-beginning);
    temp[tk->index-beginning]='\0';
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
	  //found exponent
	  if(foundE==0){
	    foundE=1;
	  }else{
	    break;
	  }
	  if(tk->token[tk->index+2]=='-'){
	    //found negative sign
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
    char *temp = (char*) malloc(sizeof(char)*((tk->index-beginning)+1));
    memcpy(temp,tk->token+beginning,tk->index-beginning);
    temp[tk->index-beginning]='\0';
    return temp;
  }else if(tk->token[tk->index]<'0' || (tk->token[tk->index]>'9' && tk->token[tk->index]<'A') || (tk->token[tk->index]>'Z' && tk->token[tk->index]<'a') || tk->token[tk->index]>'z'){
    //COP
    //TODO
    tk->type = COP;
    switch(tk->token[tk->index]){//Switch START
    case '=':
      tk->index++;
      if(tk->token[tk->index]=='='){
	//+
	tk->index++;
	return "equal to \"==\"";
      }else{
	return "basic assignment \"=\"";
      }
      break;
    case '<':
      tk->index++;
      if(tk->token[tk->index]=='='){
	tk->index++;
	return "less than or equal to \"<=\"";
      }else if(tk->token[tk->index]=='<'){
	tk->index++;
	if(tk->token[tk->index]=='='){
	  tk->index++;
	  return "bitwise left shift assignment \"<<=\"";
	}else{
	  return "bitwise left shift \"<<\"";
	}
      }else{
	return "less than \"<\"";
      }
      break;
    case '>':
      tk->index++;
      if(tk->token[tk->index]=='='){
	tk->index++;
	return "greater than or equal to \">=\"";
      }else if(tk->token[tk->index]=='>'){
	tk->index++;
	if(tk->token[tk->index]=='='){
	  tk->index++;
	  return "bitwise right shift assignment \">>=\"";
	}else{
	  return "bitwise right shift \">>\"";
	}
      }else{
	return "greater than \">\"";
      }
      break;
    case '+':
      tk->index++;
      if(tk->token[tk->index]=='+'){
	tk->index++;
	return "increment \"++\"";
      }else if(tk->token[tk->index]=='='){
	tk->index++;
	return "addition assignment \"+=\"";
      }else{
	return "addition \"+\"";
      }
      break;
    case '-':
      tk->index++;
      if(tk->token[tk->index]=='-'){
	tk->index++;
	return "decrement \"--\"";
      }else if(tk->token[tk->index]=='='){
	tk->index++;
	return "subtraction assignment \"-=\"";
      }else if(tk->token[tk->index]=='>'){
	
      }else{
	return "subtraction \"-\"";
      }
      break;
    case '*':
      tk->index++;
      if(tk->token[tk->index]=='='){
	tk->index++;
	return "multiplication assignment \"*=\"";
      }else{
	return "multiplication \"*\"";
      }
      break;
    case '/':
      tk->index++;
      if(tk->token[tk->index]=='/'){
	tk->index++;
	//single line comments
	while(tk->token[tk->index]!='\n' && tk->token[tk->index]!='\0'){
	  tk->index++;
	}
	return TKGetNextToken(tk);
	//comments
      }else if(tk->token[tk->index]=='*'){
	//block comment
	tk->index++;
	while(tk->token[tk->index]!='\0'){
	  if(tk->token[tk->index]=='*' && tk->token[tk->index+1]=='/'){
	    tk->index = tk->index+2;
	    break;
	  }
	  tk->index++;
	}
	return TKGetNextToken(tk);
      }else{
	return "division \"/\"";
      }
      break;
    case '%':
      tk->index++;
      if(tk->token[tk->index]=='='){
	tk->index++;
	return "modulo assignment \"%=\"";
      }else{
	return "modulo %";
      }
      break;
    case '!':
      tk->index++;
      if(tk->token[tk->index]=='='){
	tk->index++;
	return "not equal to \"!=\"";
      }else{
	return "logical NOT \"!\"";
      }
      break;
    case '&':
      tk->index++;
      if(tk->token[tk->index]=='&'){
	tk->index++;
	return "logical AND \"&&\"";
      }else if(tk->token[tk->index]=='='){
      	tk->index++;
      	return "bitwise AND assignment \"&=\"";
      }else{
	return "bitwise AND \"&\"";
      }
      break;
    case '|':
      tk->index++;
      if(tk->token[tk->index]=='|'){
	tk->index++;
	return "logical OR \"||\"";
      }else if(tk->token[tk->index]=='='){
	tk->index++;
	return "bitwise OR assignment \"|=\"";
      }else{
	return "bitwise OR \"|\"";
      }
      break;
    case '~':
      tk->index++;
      return "bitwise NOT \"~\"";
      break;
    case '[':
      tk->index++;
      return "left brace \"[\"";
      break;
    case ']':
      tk->index++;
      return "right brace \"]\"";
      break;
    case '(':
      tk->index++;
      return "left parentheses \"(\"";
      break;
    case ')':
      tk->index++;
      return "right parentheses \")\"";
      break;
    case ',':
      tk->index++;
      return "comma \",\"";
      break;
    case '?':
      tk->index++;
      if(tk->token[tk->index+1]==':'){
        tk->index++;
        return "ternary conditional \"?:\"";
      }else{		//Have to check if the '?' is followed by an ':'
      	tk->index++; 	//I'm not sure if this needs to be done again, will check later
      	tk->type = BAD_TOKEN;
      	return tk->token+beginning;
      }
      break;
    case '^':
      tk->index++;
      if(tk->token[tk->index+1]=='='){
      	tk->index++;
      	return "bitwise XOR assignment \"^=\"";
      }
      else{
        return "bitwise XOR \"^\"";
      }
      break;
    case '"':{
      beginning = tk->index;
      tk->index++;
      int foundQuotes=0;
      while(tk->token[tk->index]!='"' && tk->token[tk->index]!='\0'){
	tk->index++;
	if(tk->token[tk->index]=='"'){
	  foundQuotes=1;
	}
      }
      if(foundQuotes==1){
	tk->index++;
	tk->type = QUOTE;
	char *temp = (char*) malloc(sizeof(char)*((tk->index-beginning)+1));
	memcpy(temp,tk->token+beginning,tk->index-beginning);
	temp[tk->index-beginning]='\0';
	return temp;
      }else{
	tk->index=beginning+1;
	return "Quote \"\"\"";
      }
      break;
    }
    case '\'':{
      beginning = tk->index;
      tk->index++;
      int foundQ = 0;
      while(tk->token[tk->index]!='\'' && tk->token[tk->index]!='\0'){
	tk->index++;
	if(tk->token[tk->index]=='\''){
	  foundQ=1;
	}
      }
      if(foundQ==1){
	tk->index++;
	tk->type = QUOTE;
	char *temp = (char*) malloc(sizeof(char)*((tk->index-beginning)+1));
	memcpy(temp, tk->token+beginning, tk->index-beginning);
	temp[tk->index-beginning]='\0';
	return temp;
      }else{
	tk->index=beginning+1;
	return "Single Quote \"\'\"";
      }
      break;
    }
    }//SWITCH END
    tk->index++;
    tk->type = BAD_TOKEN;
    return tk->token+beginning;
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
  while((outputStream = TKGetNextToken(token))!=NULL){
    //while outputStream (which is set to the val of TKGetNextToken) is not 0 THEN
    switch(token->type){
      //switch case based on type of token set inside call of TKGetNextToken
    case 1:
      printf("word \"%s\"\n",outputStream);
      free(outputStream);
      //word
      break;
    case 2:
      //deciaml
      printf("decimal integer \"%s\"\n",outputStream);
      free(outputStream);
      break;
    case 3:
      //octal
      printf("octal integer \"%s\"\n",outputStream);
      free(outputStream);
      break;
    case 4:
      //Hexa
      printf("hexadecimal integer \"%s\"\n",outputStream);
      free(outputStream);
      break;
    case 5:
      //Float
      printf("float point \"%s\"\n",outputStream);
      free(outputStream);
      break;
    case 6:
      //COP 
      printf("%s\n",outputStream);
      break;
    case 7:
      //quote
      printf("String %s\n",outputStream);
      free(outputStream);
      break;
    case 0:
      printf("Bad token %c\n",outputStream);
      break;
    case -1:
      //Error!
      printf("something happened that wasn't suppose to happen!\n");
      break;
    }
  }
  return 0;
}
