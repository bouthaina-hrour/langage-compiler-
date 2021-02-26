#include <stdio.h>
#include <stdbool.h>
#include <string.h>


 typedef enum {IF_TOKEN,ELSEIF_TOKEN,ELSE_TOKEN,REPEAT_TOKEN,UNTIL_TOKEN,WHILE_TOKEN,TIMES_TOKEN,END_TOKEN,INF_TOKEN,
SUP_TOKEN,NOT_TOKEN,BOOL_TOKEN,STRING_TOKEN,NUM_TOKEN,INT_TOKEN,INPUT_TOKEN,OUTPUT_TOKEN,MIN_TOKEN,MAX_TOKEN,COM_TOKEN,
MOD_TOKEN,TRUE_TOKEN,FALSE_TOKEN,AND_TOKEN,PLUS_TOKEN,MOINS_TOKEN,MULT_TOKEN,DIV_TOKEN,EGAL_TOKEN,INFEG_TOKEN,SUPEG_TOKEN,
QUOTE_TOKEN,FIN_TOKEN,ID_TOKEN,NUMBER_TOKEN,INTEGER_TOKEN,ERREUR_TOKEN }CODES_LEX ;
char* mot_cle[]={"if","elseif","else","repeat","until","while","times","end","lt","gt","not","bool","string","num","int","input","output","min",
"max","com","mod","true","false","and"};

char* Token[]={"IF_TOKEN","ELSEIF_TOKEN","ELSE_TOKEN","REPEAT_TOKEN","UNTIL_TOKEN","WHILE_TOKEN","TIMES_TOKEN","END_TOKEN","INF_TOKEN",
"SUP_TOKEN","NOT_TOKEN","BOOL_TOKEN","STRING_TOKEN","NUM_TOKEN","INT_TOKEN","INPUT_TOKEN","OUTPUT_TOKEN","MIN_TOKEN","MAX_TOKEN","COM_TOKEN",
"MOD_TOKEN","TRUE_TOKEN","FALSE_TOKEN","AND_TOKEN","PLUS_TOKEN","MOINS_TOKEN","MULT_TOKEN","DIV_TOKEN","EGAL_TOKEN","INFEG_TOKEN","SUPEG_TOKEN",
"QUOTE_TOKEN","FIN_TOKEN","ID_TOKEN","NUMBER_TOKEN","INTEGER_TOKEN","ERREUR_TOKEN"};
typedef struct { CODES_LEX CODE; char NOM[100]; } TSym_Cour;
TSym_Cour TABLES[1000];
char Car_Cour;
FILE *Fichier;
TSym_Cour sym_cour;
void Sym_Suiv();
void lire_mot();
char lire_Car();
void lire_nombre();
void lire_string();
void lire_commnentaire();
void AfficherToken(TSym_Cour sym_cour);

