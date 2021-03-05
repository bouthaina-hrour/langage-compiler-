#include "header.h"
void erreurCompatibilites(){
    printf("Type incompatible!!! à la ligne %d",numLigne);
    exit(0);
}
void ajouterSym(char* nom,TSYM type){

    if(verifierSym(nom)<0){
            strcpy(TAB_IDFS[indice_table_symb].NOM,nom);
            TAB_IDFS[indice_table_symb].TIDF=type;
            indice_table_symb++;

    }else{
        printf("la variable %s existe d�ja ",nom);
        exit(1);
    }

}
int verifierSym(char* nom){
    for(int i=0;i<1000;i++){
        if(strcmp(TAB_IDFS[i].NOM,nom)==0){
              return i;
        }
    }
    return -1;

}
void verifierTypePrec(){
    switch (sym_cour.CODE)
    {
    case TEXT_TOKEN:
         type_id_prec=TSTRING;
        break;
    case ID_TOKEN:
         indice_id_prec=verifierSym(sym_cour.NOM);
         if(indice_id_prec !=-1){
        type_id_prec=TAB_IDFS[indice_id_prec].TIDF;
    }
    else erreurNonDeclare();
         break;
    case INTEGER_TOKEN:
         type_id_prec=TINT;
         break;
    case NUMBER_TOKEN:
         type_id_prec=TNUM;
         break;
    default:
        break;
    }
}
void verifierTypeSuiv(){
             switch (sym_cour.CODE)
    {
    case TEXT_TOKEN:
        type_id_suiv=TSTRING;
        break;
    case ID_TOKEN:
         indice_id_suiv=verifierSym(sym_cour.NOM);
         if(indice_id_suiv !=-1){
        type_id_suiv=TAB_IDFS[indice_id_suiv].TIDF;
    }
    else erreurNonDeclare();

          break;
    case INTEGER_TOKEN:
         type_id_suiv=TINT;

         break;
    case NUMBER_TOKEN:
         type_id_suiv=TNUM;

        break;
    default:
        break;
    }
}
void erreurNonDeclare(){

        printf("%s non déclaré à la ligne %d",sym_cour.NOM,numLigne);
        exit(0);

}
