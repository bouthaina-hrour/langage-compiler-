# langage-compiler-
                 Grammar rules :
PROG: code INSTS endcode

INSTS: INST {INST}

INST : SI | REPETER | ECRIRE | DECLARE | AFFEC

SI :  if COND INST SI’ end 

SI’ :{elseif COND INST}|else INST |eps

COND : EXPR OPCOMP  EXPR

EXPR : ARITH | CONCAT
ARITH : TERM { ADDOP TERM }
TERM :FACT {MULOP FACT}

OPCOMP : = | not= | lt |gt |lt=|gt=

ADDOP: +| -

MULOP : *|/|mod 

FACT: FACT’ | compute ARITH endcompute

FACT’: ID | INTEGER | NUMBER

ID : lettre {lettre|chiffre}

REPETER : repeat REPETER’ end 

REPETER’ : REPETER” INST 

REPETER”:ARITH times |while COND |until COND 

ECRIRE : output ALL
ALL : FACT | CONCAT | bool 

Lire : input TEXT

AFFEC : ID = AFFEC’

AFFEC’ : ID |NUMBER |CONCAT|INTEGER|BOOLEAN |EXPR|LIRE|COND|FCT

FCT : MIN|MAX

MIN: min ARITH and ARITH

MAX : max ARITH and ARITH

DECLARE : TYPE AFFEC

COMMENT : com TEXT’  \n



BOOLEAN : true | false 

INTEGER : CHIFFRE { CHIFFRE } 

NUMBER: = INTEGER {INTEGER}.INTEGER{INTEGER}

CHIFFRE : 0|...|9

LETTRE : a|...|z|A|...|Z

CONCAT : TEXT {+ CONCAT'}
CONCAT' : id | TEXT
TEXT: “ TEXT’ “ 

TEXT’ : {LETTTRE {LETTTRE | CHIFFRE} | CHIFFRE {LETTTRE | CHIFFRE}}

TYPE : num|int|bool|string  
