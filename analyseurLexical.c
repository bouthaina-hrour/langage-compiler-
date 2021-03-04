
#include "header.h"

void AfficherToken(TSym_Cour sym_cour){
    printf("%s\n",Token[sym_cour.CODE]);
}

char lire_Car(){
    char car;

    if(Fichier!=NULL){

    car=fgetc(Fichier);
   }
    return car;

}

void lire_nombre(){
    int i=0;
    char* integer=(char*)malloc(sizeof(char));
    integer[i]=Car_Cour;
    do{
         i++;
         Car_Cour=lire_Car();
         integer[i]=Car_Cour;
   }while(Car_Cour>='0'&& Car_Cour<='9');

    if(Car_Cour=='.'){
        integer[i]=Car_Cour;
        do{
            i++;
            Car_Cour=lire_Car();
            integer[i]=Car_Cour;
        }while(Car_Cour>='0'&& Car_Cour<='9');
        if(Car_Cour==' '||Car_Cour=='\t' || Car_Cour=='\n' || Car_Cour=='+'||Car_Cour=='*'||Car_Cour=='-'||Car_Cour=='/'){
                ungetc(Car_Cour,Fichier);
                sym_cour.CODE=NUMBER_TOKEN;
                strcpy(sym_cour.NOM,integer); //number
        }else{
                sym_cour.CODE=ERREUR_TOKEN;
        }
    }

    else if(Car_Cour==' '||Car_Cour=='\t' || Car_Cour=='\n' || Car_Cour=='+'||Car_Cour=='*'||Car_Cour=='-'||Car_Cour=='/'){

        sym_cour.CODE=INTEGER_TOKEN;
        strcpy(sym_cour.NOM,integer); //integer
    }else{
            sym_cour.CODE=ERREUR_TOKEN;
    }

}

void lire_mot(){
    char* mot=(char*)malloc(sizeof(char));
    int mot_cle_size = sizeof(mot_cle)/sizeof(mot_cle[0]);

    int i=0;
    char car;
    mot[i]=Car_Cour;

   do{
       i++;
       Car_Cour=lire_Car();
       mot[i] =Car_Cour;

    }while('A' <= Car_Cour && Car_Cour <= 'Z' || 'a' <= Car_Cour && Car_Cour <= 'z' ||Car_Cour>='0'&& Car_Cour<='9');
    mot[i]='\0';
    ungetc(Car_Cour,Fichier);

    int j=0;
    bool est_mot_cle=false;

    while(j<mot_cle_size ) {
        if( strcmpi(mot,mot_cle[j])==0){
            est_mot_cle=true;
                if(strcmpi(mot_cle[j],"lt")==0){
                  Car_Cour=lire_Car();
                  if(Car_Cour=='=')
                    sym_cour.CODE=INFEG_TOKEN;
                  else{
                    ungetc(Car_Cour,Fichier);
                    sym_cour.CODE=j;}
                }else  if(strcmpi(mot_cle[j],"gt")==0){
                     Car_Cour=lire_Car();
                    if(Car_Cour=='=')
                        sym_cour.CODE=SUPEG_TOKEN;
                    else {
                        ungetc(Car_Cour,Fichier);
                        sym_cour.CODE=j;}
                }else if (strcmpi(mot_cle[j],"not")==0){
                        Car_Cour=lire_Car();
                    if(Car_Cour=='=')
                        sym_cour.CODE=j;
                    else {
                        ungetc(Car_Cour,Fichier);
                        sym_cour.CODE=ERREUR_TOKEN;
                        }
                }else if (strcmpi(mot_cle[j],"com")==0){

                    lire_commnentaire();
                }
                else{
                 sym_cour.CODE=j;

                }
        }
         j++;

    }


    if(!est_mot_cle){

        sym_cour.CODE=ID_TOKEN;
        strcpy(sym_cour.NOM,mot);

    }

}
void lire_commnentaire(){
  sym_cour.CODE = COM_TOKEN; //escape comments
	do{
		Car_Cour=lire_Car();
	 }while(Car_Cour!='\n');
}
void lire_string(){

   do{

         Car_Cour=lire_Car();

	}while( Car_Cour!='"' && Car_Cour!=EOF);
   if(Car_Cour=='"'){
       sym_cour.CODE=TEXT_TOKEN;
   }else{
        sym_cour.CODE=ERREUR_TOKEN;
   }
}
void Sym_Suiv(){
   while(Car_Cour=='\t' || Car_Cour==' ' || Car_Cour=='\n'){
        Car_Cour=lire_Car();
   }

   if('A' <= Car_Cour && Car_Cour <= 'Z' || 'a' <= Car_Cour && Car_Cour <= 'z'){
         lire_mot();

    }else if(Car_Cour>='0'&& Car_Cour<='9'){

        lire_nombre();

   }
   else if( Car_Cour=='{'){
          Car_Cour=lire_Car();
          if(Car_Cour=='*'){
              do{
                    Car_Cour=lire_Car();

              }while(Car_Cour!='*');
              Car_Cour=lire_Car();
              if(Car_Cour=='}'){
                  Car_Cour=lire_Car();
                  Sym_Suiv();
              }
          }else{
              sym_cour.CODE=ERREUR_TOKEN;
              ungetc(Car_Cour,Fichier);

          }
   }else if( Car_Cour=='"'){
       lire_string();
       }
   else{
       switch(Car_Cour){

           case '+':sym_cour.CODE=PLUS_TOKEN;
                    break;
           case '-' :sym_cour.CODE=MOINS_TOKEN;

                    break;
           case '*' :sym_cour.CODE=MULT_TOKEN;
                    break;
           case '/' :sym_cour.CODE=DIV_TOKEN;
                    break;
           case '=':sym_cour.CODE=EGAL_TOKEN;
                     break;
           case EOF:sym_cour.CODE=FIN_TOKEN;

                    break;
          default:  sym_cour.CODE=ERREUR_TOKEN;
       }

   }
   Car_Cour=lire_Car();
   }










