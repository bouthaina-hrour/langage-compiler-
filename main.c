#include "parser.c"

int main(){
    Fichier = fopen("programme_pascal.txt","r");
    if(Fichier == NULL){
        printf("Fichier non trouvé \n");
        exit(EXIT_FAILURE);
    }

    Car_Cour = lire_Car();
    if (Car_Cour == EOF){
        detecter_erreur(ERR_FICH_VID);
    }
    
    // while (Car_Cour != EOF)
    // {
       Sym_Suiv();
       AfficherToken(sym_cour);
       prog();
    // }
    
    // if(sym_cour.CODE==FIN_TOKEN){
    //     printf("bravo le programme est correct");

    // }else{
    //     printf("pas bravo:le programme est incorrect!!!");
    // }
}


// int main()
// {
// Fichier=NULL;
//  Fichier=fopen("test00.txt","r");


// if(Fichier!=NULL){

//   Car_Cour=lire_Car();
//   while(Car_Cour!=EOF){
//       Sym_Suiv();
//      AfficherToken(sym_cour);

// }
//     return 1;

// }

// }