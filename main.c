#include "parser.c"
//MAIN
int main(){
    Fichier = fopen("test2.txt","r");
    if(Fichier == NULL){
        printf("Fichier non trouv� \n");
        exit(EXIT_FAILURE);
    }

    Car_Cour = lire_Car();
    if (Car_Cour == EOF){
        detecter_erreur(ERR_FICH_VID);
    }

    //LEXER
    printf("******************** Analyseur lexical *********************\n");
    while (Car_Cour != EOF){
       Sym_Suiv();
       AfficherToken(sym_cour);
    }
    printf("******************** Analyseur lexical *********************\n");
    fclose(Fichier);
    numLigne=1;
    Fichier = fopen("test2.txt","r");
    if(Fichier == NULL){
        printf("Fichier non trouv� \n");
        exit(EXIT_FAILURE);
    }

    Car_Cour = lire_Car();
    if (Car_Cour == EOF){
        detecter_erreur(ERR_FICH_VID);
    }
    //PARSER
    printf("******************** Analyseur syntaxique et semantique *********************\n");
    Sym_Suiv();
    prog();
    if(sym_cour.CODE==FIN_TOKEN){
       printf("\n bravo le programme est syntaxiquement et sémantiquement correcte\n ");

   }else{
      printf("\n pas bravo:le programme est syntaxiquement erronee!!!\n ");}}
