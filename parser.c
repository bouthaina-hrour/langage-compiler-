#include "lexer.c"
#include  "interpreter.c"


//parser

void Test_Symbole (CODES_LEX cl, Erreurs_t COD_ERR){
    if (sym_cour.CODE == cl){
        Sym_Suiv();
    }
    else{
        detecter_erreur(COD_ERR);
    }
}

int detecter_erreur(Erreurs_t er){
    int i = 0;
    for(; i < tailleERR, er != MES_ERR[i].CODE_ERR; i++);
    printf("erreur %s à la ligne %d\n", MES_ERR[i].mes,numLigne);
    exit(EXIT_FAILURE);
}

void prog(){
    Test_Symbole(CODE_TOKEN, CODE_ERR);
    insts();
    Test_Symbole(ENDCODE_TOKEN, ENDCODE_ERR);
}

void insts(){

    while (sym_cour.CODE == IF_TOKEN || sym_cour.CODE == REPEAT_TOKEN ||
           sym_cour.CODE == OUTPUT_TOKEN || sym_cour.CODE == COM_TOKEN ||
           sym_cour.CODE == NUM_TOKEN || sym_cour.CODE == INT_TOKEN ||
           sym_cour.CODE == BOOL_TOKEN || sym_cour.CODE == STRING_TOKEN ||
           sym_cour.CODE == ID_TOKEN)
    {
        if(sym_cour.CODE != COM_TOKEN) {
            inst();
        }else {
            Sym_Suiv();
        }

    }

}

inst(){

    switch (sym_cour.CODE){
        case IF_TOKEN:
            si();
            break;
        case REPEAT_TOKEN:
            repeter();
            break;
        case OUTPUT_TOKEN:
            ecrire();
            break;
        // case INPUT_TOKEN:
        //     lire();
        //     break;
        case NUM_TOKEN:
        case INT_TOKEN:
        case BOOL_TOKEN:
        case STRING_TOKEN:
            declare();
            break;
        case ID_TOKEN:
            affec();
            break;
        default:
            break;
    }
}

void si(){
    Test_Symbole(IF_TOKEN, IF_ERR);
    cond();
    insts();
    if(sym_cour.CODE == ELSEIF_TOKEN){
        Sym_Suiv();
        cond();
        insts();
    }
    if(sym_cour.CODE == ELSE_TOKEN){
        Sym_Suiv();
        insts();
    }
    Test_Symbole(END_TOKEN, END_ERR);
}

void cond(){
    verifierTypePrec();
    expr();
    if(sym_cour.CODE == EGAL_TOKEN || sym_cour.CODE == NOT_TOKEN ||
       sym_cour.CODE == INF_TOKEN || sym_cour.CODE == INFEG_TOKEN ||
       sym_cour.CODE == SUP_TOKEN || sym_cour.CODE == SUPEG_TOKEN){
           Sym_Suiv();
           verifierTypeSuiv();
          if (type_id_suiv!=type_id_prec && (type_id_prec == TSTRING || type_id_suiv ==TSTRING || type_id_suiv ==TBOOL || type_id_prec == TBOOL) ) erreurCompatibilites();
           expr();
          }
    else {

        detecter_erreur(IF_ERR);
    }
}

void expr(){
    switch (sym_cour.CODE)
    {
    case TEXT_TOKEN:
        concat();
        break;
    case ID_TOKEN:
         indice_id_prec=verifierSym(sym_cour.NOM);
         if(indice_id_prec ==-1){
        erreurNonDeclare();
    }
          arith();
          break;
    case INTEGER_TOKEN:
    case NUMBER_TOKEN:
        arith();
        break;
    default:
        printf("erreur dans la regle expr \n"); exit(EXIT_FAILURE);
    }
}

void arith(){
    verifierTypePrec();
    term();
    if(sym_cour.CODE == PLUS_TOKEN || sym_cour.CODE == MOINS_TOKEN){
        if(sym_cour.CODE == MOINS_TOKEN && type_id_prec==TSTRING){
            erreurCompatibilites();
        }
        else{
        Sym_Suiv();
        verifierTypeSuiv();
         if (type_id_suiv!=type_id_prec && (type_id_prec==TSTRING || type_id_suiv==TSTRING ) ) erreurCompatibilites();
        term();
        }

    }
}

void term(){
     verifierTypePrec();
    fact();
    if(sym_cour.CODE == MULT_TOKEN || sym_cour.CODE == DIV_TOKEN || sym_cour.CODE == MOD_TOKEN){
        Sym_Suiv();
        verifierTypeSuiv();
         if (type_id_prec==TSTRING || type_id_suiv==TSTRING  ) erreurCompatibilites();
        fact();
    }
}

void fact(){
    switch (sym_cour.CODE){
        case ID_TOKEN:
            indice_id_prec=verifierSym(sym_cour.NOM);
         if(indice_id_prec ==-1){
        erreurNonDeclare();}
            Sym_Suiv();
            break;
        case INTEGER_TOKEN:
        case NUMBER_TOKEN:
            Sym_Suiv();
            break;
        case COMPUTE_TOKEN:
            arith();
            Test_Symbole(ENDCOMPUTE_TOKEN, ENDCOMPUTE_ERR);
            break;
        default :
            printf("Erreur dans la regle fact \n"); exit(EXIT_FAILURE);
    }

}

void repeter(){
    Test_Symbole(REPEAT_TOKEN, REPEAT_ERR);
    switch (sym_cour.CODE){
        case WHILE_TOKEN:
            Sym_Suiv();
            cond();
            insts();
            break;
        case UNTIL_TOKEN:
            Sym_Suiv();
            cond();
            insts();
            break;
        case ID_TOKEN:
            indice_id_prec=verifierSym(sym_cour.NOM);
             if(indice_id_prec ==-1){
               erreurNonDeclare();
            }else if(TAB_IDFS[indice_id_prec].TIDF != TINT) {
                 erreurCompatibilites();
            }else{
                arith();
                Test_Symbole(TIMES_TOKEN, TIMES_ERR);
                  insts();
                 break;}
        case INTEGER_TOKEN:
        case COMPUTE_TOKEN:
            arith();
            if(TAB_IDFS[indice_id_prec].TIDF == TNUM) erreurCompatibilites();
            Test_Symbole(TIMES_TOKEN, TIMES_ERR);
            insts();
            break;
    }

    Test_Symbole(END_TOKEN, END_ERR);
}

void ecrire(){
    Test_Symbole(OUTPUT_TOKEN, OUTPUT_ERR);
    switch (sym_cour.CODE){
        case BOOL_TOKEN:
            Test_Symbole(BOOL_TOKEN, BOOL_ERR);
            break;
        case TEXT_TOKEN:
            concat();
            break;

        case ID_TOKEN:
        indice_id_prec=verifierSym(sym_cour.NOM);
        if(indice_id_prec ==-1){
        erreurNonDeclare();
        }
        case INTEGER_TOKEN:
        case NUMBER_TOKEN:
            fact();
            break;}
}

void lire(){
    Test_Symbole(INPUT_TOKEN, INPUT_ERR);
    //Test_Symbole(TEXT_TOKEN, TEXT_ERR);
    concat();
}

void affec(){
    Test_Symbole(ID_TOKEN, ID_ERR);
    indice_id_prec=verifierSym(sym_cour.NOM);
    if(indice_id_prec !=-1){
        type_id_prec=TAB_IDFS[indice_id_prec].TIDF;
    }
    else erreurNonDeclare();
    Test_Symbole(EGAL_TOKEN, EGAL_ERR);
    switch (sym_cour.CODE){
        case INPUT_TOKEN:

            lire();
            break;
        case MIN_TOKEN:
        case MAX_TOKEN:
            if(type_id_prec==TSTRING || type_id_prec==TBOOL ){
                erreurCompatibilites();
            }
            fct();break;
        case ID_TOKEN:  indice_id_suiv=verifierSym(sym_cour.NOM);
                        if(indice_id_suiv !=-1){
                          type_id_suiv=TAB_IDFS[indice_id_suiv].TIDF;
                         }else erreurNonDeclare();
                      if(type_id_prec!=type_id_suiv) erreurCompatibilites();
                      arith();break;
        case INTEGER_TOKEN: if(type_id_prec!=TINT)   erreurCompatibilites();
                             arith();break;
        case NUMBER_TOKEN: if(type_id_prec!=TNUM)   erreurCompatibilites();
            arith();
            break;
         case FALSE_TOKEN:
         case TRUE_TOKEN:  if(type_id_prec!=TBOOL)  erreurCompatibilites();
         Sym_Suiv();
         break;

        case TEXT_TOKEN:if(type_id_prec!=TSTRING)  erreurCompatibilites();
            concat();
            break;
        default:
            printf("Erreur d'affectation à la ligne %d\n",numLigne); exit(EXIT_FAILURE);
    }
}

void fct(){
    switch (sym_cour.CODE){
        case MIN_TOKEN:
        case MAX_TOKEN:
            Sym_Suiv();
            verifierTypePrec();
            arith();
            Test_Symbole(AND_TOKEN, AND_ERR);
            verifierTypeSuiv();
            if (type_id_suiv!=type_id_prec && (type_id_prec == TSTRING || type_id_suiv ==TSTRING ||
              type_id_suiv ==TBOOL || type_id_prec == TBOOL) ) erreurCompatibilites();
            arith();
            break;
        default:
            break;
    }
}

void concat(){

    Test_Symbole(TEXT_TOKEN, TEXT_ERR);
    while(sym_cour.CODE == PLUS_TOKEN){
        Sym_Suiv();
        switch (sym_cour.CODE){
            case TEXT_TOKEN:
            case ID_TOKEN:
            indice_id_prec=verifierSym(sym_cour.NOM);
             if(indice_id_prec ==-1){
               erreurNonDeclare();
            }else if(TAB_IDFS[indice_id_prec].TIDF != TSTRING) {
                 erreurCompatibilites();
            }else{

                Sym_Suiv();
                break;}

            default:
                printf("Erreur de concaténation avec int ou num ... à la ligne %d\n",numLigne); exit(EXIT_FAILURE);
        }
    }
}

void declare(){
    switch (sym_cour.CODE){

        case STRING_TOKEN:type_id_prec=TSTRING;
          Sym_Suiv();
          strcpy(dernier_id,sym_cour.NOM);
          Test_Symbole(ID_TOKEN, ID_ERR);
            if (sym_cour.CODE==EGAL_TOKEN){
                Sym_Suiv(sym_cour.CODE);
                switch (sym_cour.CODE){
                     case INPUT_TOKEN:
                         lire();
                    break;
                    case TEXT_TOKEN:if(type_id_prec!=TSTRING)  erreurCompatibilites();
                        concat();
                        break;
                    case FALSE_TOKEN:
                    case TRUE_TOKEN:  if(type_id_prec!=TBOOL)  erreurCompatibilites();
                        Sym_Suiv();
                        break;
                    case ID_TOKEN: indice_id_suiv=verifierSym(sym_cour.NOM);
                                   if(indice_id_suiv!=-1){
                                       type_id_suiv=TAB_IDFS[indice_id_suiv].TIDF;
                                    }else erreurNonDeclare();
                                    if(type_id_prec!=type_id_suiv) erreurCompatibilites(); arith();
                        break;

                    case INTEGER_TOKEN: if(type_id_prec!=TINT)   erreurCompatibilites(); arith();
                        break;

                    case NUMBER_TOKEN: if(type_id_prec!=TNUM)   erreurCompatibilites();
                        arith();
                        break;
                   case MIN_TOKEN:
                   case MAX_TOKEN:
                           if(type_id_prec==TSTRING || type_id_prec==TBOOL ){
                              erreurCompatibilites();
                                 }
                  fct();break;
                     default:
                printf("Erreur de déclaration à la ligne %d\n",numLigne); exit(EXIT_FAILURE);
                }
            }
        ajouterSym(dernier_id,type_id_prec);

            break;
        case INT_TOKEN:type_id_prec=TINT;
          Sym_Suiv();
           strcpy(dernier_id,sym_cour.NOM);
            Test_Symbole(ID_TOKEN, ID_ERR);
            if (sym_cour.CODE==EGAL_TOKEN){
                Sym_Suiv(sym_cour.CODE);
                switch (sym_cour.CODE){
                     case INPUT_TOKEN:
                         lire();
                    break;
                    case TEXT_TOKEN:if(type_id_prec!=TSTRING)  erreurCompatibilites();
                        concat();
                        break;
                    case FALSE_TOKEN:
                    case TRUE_TOKEN:  if(type_id_prec!=TBOOL)  erreurCompatibilites();
                        Sym_Suiv();
                        break;
                    case ID_TOKEN: indice_id_suiv=verifierSym(sym_cour.NOM);
                                   if(indice_id_suiv!=-1){
                                       type_id_suiv=TAB_IDFS[indice_id_suiv].TIDF;
                                    }else erreurNonDeclare();
                                    if(type_id_prec!=type_id_suiv) erreurCompatibilites();arith();  break;

                    case INTEGER_TOKEN: if(type_id_prec!=TINT)   erreurCompatibilites();arith();  break;

                    case NUMBER_TOKEN: if(type_id_prec!=TNUM)   erreurCompatibilites();arith();  break;
                   case MIN_TOKEN:
                   case MAX_TOKEN:
                           if(type_id_prec==TSTRING || type_id_prec==TBOOL ){
                              erreurCompatibilites();
                                 }
                  fct();break;
                     default:
                printf("Erreur de déclaration à la ligne %d\n",numLigne); exit(EXIT_FAILURE);
                }
            }
           ajouterSym(dernier_id,type_id_prec);


            break;
        case NUM_TOKEN:type_id_prec=TNUM;

          Sym_Suiv();
            strcpy(dernier_id,sym_cour.NOM);
            Test_Symbole(ID_TOKEN, ID_ERR);
            if (sym_cour.CODE==EGAL_TOKEN){
                Sym_Suiv(sym_cour.CODE);
                switch (sym_cour.CODE){
                     case INPUT_TOKEN:
                         lire();
                    break;
                    case TEXT_TOKEN:if(type_id_prec!=TSTRING)  erreurCompatibilites();
                        concat();
                        break;
                    case FALSE_TOKEN:
                    case TRUE_TOKEN:  if(type_id_prec!=TBOOL)  erreurCompatibilites();
                        Sym_Suiv();
                        break;
                    case ID_TOKEN: indice_id_suiv=verifierSym(sym_cour.NOM);
                                   if(indice_id_suiv!=-1){
                                       type_id_suiv=TAB_IDFS[indice_id_suiv].TIDF;
                                    }else erreurNonDeclare();
                                    if(type_id_prec!=type_id_suiv) erreurCompatibilites(); arith();
                        break;

                    case INTEGER_TOKEN: if(type_id_prec!=TINT)   erreurCompatibilites(); arith();
                        break;

                    case NUMBER_TOKEN: if(type_id_prec!=TNUM)   erreurCompatibilites();
                        arith();
                        break;
                   case MIN_TOKEN:
                   case MAX_TOKEN:
                           if(type_id_prec==TSTRING || type_id_prec==TBOOL ){
                              erreurCompatibilites();
                                 }
                  fct();break;
                     default:
                printf("Erreur de déclaration à la ligne %d\n",numLigne); exit(EXIT_FAILURE);
                }
            }
           ajouterSym(dernier_id,type_id_prec);


            break;
        case BOOL_TOKEN:type_id_prec=TBOOL;

            Sym_Suiv();
             strcpy(dernier_id,sym_cour.NOM);
            Test_Symbole(ID_TOKEN, ID_ERR);
            if (sym_cour.CODE==EGAL_TOKEN){
                Sym_Suiv(sym_cour.CODE);
                switch (sym_cour.CODE){
                     case INPUT_TOKEN:
                         lire();
                    break;
                    case TEXT_TOKEN:if(type_id_prec!=TSTRING)  erreurCompatibilites();
                        concat();
                        break;
                    case FALSE_TOKEN:
                    case TRUE_TOKEN:  if(type_id_prec!=TBOOL)  erreurCompatibilites();
                        Sym_Suiv();
                        break;
                    case ID_TOKEN: indice_id_suiv=verifierSym(sym_cour.NOM);
                                   if(indice_id_suiv!=-1){
                                       type_id_suiv=TAB_IDFS[indice_id_suiv].TIDF;
                                    }else erreurNonDeclare();
                                    if(type_id_prec!=type_id_suiv) erreurCompatibilites(); arith();
                        break;

                    case INTEGER_TOKEN: if(type_id_prec!=TINT)   erreurCompatibilites(); arith();
                        break;

                    case NUMBER_TOKEN: if(type_id_prec!=TNUM)   erreurCompatibilites();
                        arith();
                        break;
                   case MIN_TOKEN:
                   case MAX_TOKEN:
                           if(type_id_prec==TSTRING || type_id_prec==TBOOL ){
                              erreurCompatibilites();
                                 }
                  fct();break;
                     default:
                printf("Erreur de déclaration à la ligne %d\n",numLigne); exit(EXIT_FAILURE);
                }
            }
            ajouterSym(dernier_id,type_id_prec);
            break;

        default:
            break;
    }
}







