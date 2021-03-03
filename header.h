#include <stdio.h>
#include <stdbool.h>
#include <string.h>


 typedef enum {
     IF_TOKEN,ELSEIF_TOKEN,ELSE_TOKEN,REPEAT_TOKEN,UNTIL_TOKEN,WHILE_TOKEN,TIMES_TOKEN,END_TOKEN,
     INF_TOKEN,SUP_TOKEN,NOT_TOKEN,BOOL_TOKEN,STRING_TOKEN,NUM_TOKEN,INT_TOKEN,INPUT_TOKEN,OUTPUT_TOKEN,
     MIN_TOKEN,MAX_TOKEN,COM_TOKEN,MOD_TOKEN,TRUE_TOKEN,FALSE_TOKEN,AND_TOKEN,CODE_TOKEN,ENDCODE_TOKEN,COMPUTE_TOKEN, ENDCOMPUTE_TOKEN, PLUS_TOKEN,MOINS_TOKEN,
     MULT_TOKEN,DIV_TOKEN,EGAL_TOKEN,INFEG_TOKEN,SUPEG_TOKEN,QUOTE_TOKEN,FIN_TOKEN,ID_TOKEN,NUMBER_TOKEN,
     INTEGER_TOKEN,TEXT_TOKEN,ERREUR_TOKEN,

    }CODES_LEX ;

char* mot_cle[]={
    "if","elseif","else","repeat","until","while","times","end","lt","gt","not","bool",
    "string","num","int","input","output","min","max","com","mod","true","false","and",
    "code", "endcode", "compute", "endcompute"
    };

char* Token[]={
    "IF_TOKEN","ELSEIF_TOKEN","ELSE_TOKEN","REPEAT_TOKEN","UNTIL_TOKEN","WHILE_TOKEN","TIMES_TOKEN",
    "END_TOKEN","INF_TOKEN","SUP_TOKEN","NOT_TOKEN","BOOL_TOKEN","STRING_TOKEN","NUM_TOKEN","INT_TOKEN",
    "INPUT_TOKEN","OUTPUT_TOKEN","MIN_TOKEN","MAX_TOKEN","COM_TOKEN","MOD_TOKEN","TRUE_TOKEN","FALSE_TOKEN",
    "AND_TOKEN","CODE_TOKEN","ENDCODE_TOKEN","COMPUTE_TOKEN", "ENDCOMPUTE_TOKEN","PLUS_TOKEN","MOINS_TOKEN","MULT_TOKEN","DIV_TOKEN","EGAL_TOKEN","INFEG_TOKEN","SUPEG_TOKEN",
    "QUOTE_TOKEN","FIN_TOKEN","ID_TOKEN","NUMBER_TOKEN","INTEGER_TOKEN","TEXT_TOKEN","ERREUR_TOKEN"
};

typedef struct { 
    CODES_LEX CODE;
    char NOM[100]; 
    } TSym_Cour;

//==================== Gestion des erreurs =========================
typedef enum{
    IF_ERR, REPEAT_ERR, TIMES_ERR, END_ERR, INF_ERR, SUP_ERR, NOT_ERR, BOOL_ERR, STRING_ERR, INT_ERR, NUM_ERR, INPUT_ERR, OUTPUT_ERR,
    MIN_ERR, MAX_ERR, MOD_ERR, TRUE_ERR, FALSE_ERR, AND_ERR, CODE_ERR,ENDCODE_ERR,COMPUTE_ERR, ENDCOMPUTE_ERR, PLUS_ERR, MOINS_ERR, MULT_ERR, DIV_ERR, EGAL_ERR, 
    INFEG_ERR, SUPEG_ERR, QUOTE_ERR, FIN_ERR, ID_ERR, NUMBER_ERR, INTEGER_ERR, TEXT_ERR,
    ERR_FICH_VID, ERR_ID_INV
}Erreurs_t;

typedef struct  {
    Erreurs_t CODE_ERR;
    char mes[40];
} Erreurs;

Erreurs MES_ERR[] = {
    {IF_ERR, "IF_ERR"},
    {REPEAT_ERR, "REPEAT_ERR"},
    {TIMES_ERR, "TIMES_ERR"},
    {END_ERR, "END_ERR"},
    {INF_ERR, "INF_ERR"},
    {SUP_ERR, "SUP_ERR"},
    {NOT_ERR, "NOT_ERR"},
    {BOOL_ERR, "BOOL_ERR"},
    {STRING_ERR, "STRING_ERR"},
    {INT_ERR, "INT_ERR"},
    {NUM_ERR, "NUM_ERR"},
    {MIN_ERR, "MIN_ERR"},
    {MAX_ERR, "MAX_ERR"},
    {MOD_ERR, "MOD_ERR"},
    {TRUE_ERR, "TRUE_ERR"},
    {FALSE_ERR, "FALSE_ERR"},
    {AND_ERR, "AND_ERR"},
    {CODE_ERR, "CODE_ERR"},
    {ENDCODE_ERR, "ENDCODE_ERR"},
    {COMPUTE_ERR, "COMPUTE_ERR"},
    {ENDCOMPUTE_ERR, "ENDCOMPUTE_ERR"},
    {PLUS_ERR, "PLUS_ERR"},
    {MOINS_ERR, "MOINS_ERR"},
    {MULT_ERR, "MULT_ERR"},
    {INFEG_ERR, "INFEG_ERR"},
    {SUPEG_ERR, "SUPEG_ERR"},
    {QUOTE_ERR, "QUOTE_ERR"},
    {FIN_ERR, "FIN_ERR"},
    {ID_ERR, "MOD_ERR"},
    {NUMBER_ERR, "NUM_ERR"},
    {INTEGER_ERR, "INTEGER_ERR"},
    {TEXT_ERR, "TEXT_ERR"},
    {ERR_FICH_VID, "Le fichier est vide"},
    {ERR_ID_INV, "ID non valide "}
};
int tailleERR = sizeof MES_ERR / sizeof MES_ERR[0];

//================= Gestion des erreurs =============================
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

void Test_Symbole (CODES_LEX cl, Erreurs_t COD_ERR);