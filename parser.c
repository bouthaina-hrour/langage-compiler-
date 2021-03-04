#include <stdlib.h>
#include "analyseurLexical.c"


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
    printf("erreur %s\n", MES_ERR[i].mes);
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
    AfficherToken(sym_cour);

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
    expr();
    if(sym_cour.CODE == EGAL_TOKEN || sym_cour.CODE == NOT_TOKEN ||
       sym_cour.CODE == INF_TOKEN || sym_cour.CODE == INFEG_TOKEN ||
       sym_cour.CODE == SUP_TOKEN || sym_cour.CODE == SUPEG_TOKEN){
           Sym_Suiv();
           expr();
    }
    else {
        AfficherToken(sym_cour);
        detecter_erreur(IF_ERR);
    }
}

void expr(){
    printf("expr >> "); AfficherToken(sym_cour);
    switch (sym_cour.CODE){
        case TEXT_TOKEN:
            concat();
            break;
        case ID_TOKEN:
        case INTEGER_TOKEN:
        case NUMBER_TOKEN:
            arith();
            break;
        default:
            printf("erreur dans la regle expr \n"); exit(EXIT_FAILURE);
    }
}

void arith(){
    term();
    if(sym_cour.CODE == PLUS_TOKEN || sym_cour.CODE == MOINS_TOKEN){
        Sym_Suiv();
        term();
    }
}

void term(){
    fact();
    if(sym_cour.CODE == MULT_TOKEN || sym_cour.CODE == DIV_TOKEN || sym_cour.CODE == MOD_TOKEN){
        Sym_Suiv();
        fact();
    }
}

void fact(){
    switch (sym_cour.CODE){
        case ID_TOKEN:
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
        case INTEGER_TOKEN:
        case COMPUTE_TOKEN:
            arith();
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
        case INTEGER_TOKEN:
        case NUMBER_TOKEN:
            fact();
    }
}

void lire(){
    Test_Symbole(INPUT_TOKEN, INPUT_ERR);
    //Test_Symbole(TEXT_TOKEN, TEXT_ERR);
    concat();
}

void affec(){
    Test_Symbole(ID_TOKEN, ID_ERR);
    Test_Symbole(EGAL_TOKEN, EGAL_ERR);
    switch (sym_cour.CODE){
        case INPUT_TOKEN:
            lire();
            break;
        case MIN_TOKEN:
        case MAX_TOKEN:
            fct();
        case ID_TOKEN:
        case INTEGER_TOKEN:
        case NUMBER_TOKEN:
            arith();
            break;
        case BOOL_TOKEN:
            Sym_Suiv();
            break;
        case TEXT_TOKEN:
            concat();
            break;
        default:
            printf("Erreur d'affectation \n"); exit(EXIT_FAILURE);
    }
}

void fct(){
    switch (sym_cour.CODE){
        case MIN_TOKEN:
        case MAX_TOKEN:
            Sym_Suiv();
            arith();
            Test_Symbole(AND_TOKEN, AND_ERR);
            arith();
            break;
        
        default:
            break;
    }
}

void concat(){
    // printf("concat >> "); printf(sym_cour.NOM);
    Test_Symbole(TEXT_TOKEN, TEXT_ERR);
    while(sym_cour.CODE == PLUS_TOKEN){
        Sym_Suiv();
        switch (sym_cour.CODE){
            case TEXT_TOKEN:
            case ID_TOKEN:
                Sym_Suiv();
                break;
            
            default:
                printf("Erreur de concaténation avec int ou num ...\n"); exit(EXIT_FAILURE);
        }
    }
}

void declare(){
    switch (sym_cour.CODE){
        case STRING_TOKEN:
        case INT_TOKEN:
        case NUM_TOKEN:
        case BOOL_TOKEN:
            Sym_Suiv();
            Test_Symbole(ID_TOKEN, ID_ERR);
            if (sym_cour.CODE==EGAL_TOKEN){
                Sym_Suiv(sym_cour.CODE);
                switch (sym_cour.CODE){
                    case TEXT_TOKEN:
                        concat();
                        break;
                    case BOOL_TOKEN:
                        Sym_Suiv();
                        break;
                    case ID_TOKEN:
                    case INTEGER_TOKEN:
                    case NUMBER_TOKEN:
                        arith();
                        break;
                    default:
                        printf("Erreur de déclaration \n"); exit(EXIT_FAILURE);
                }
            }
            
            break;
        
        default:
            break;
    }
}