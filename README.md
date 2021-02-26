# langage-compiler-
                 Grammar rules :
PROG: INSTS

INSTS: INST {INST}

INST : INSTS | SI | REPETER | ECRIRE | DECLARE | LIRE | COMMENT 

SI :  if COND INST SI’ end 

SI’ :{elseif COND INST}|Ielse INST |eps

COND : EXPR OPCOMP  EXPR

EXPR : TERM { ADDOP TERM }

TERM :FACT {MULOP FACT}

OPCOMP : = | not= | lt |gt |lt=|gt=

ADDOP: +| -

MULOP : *|/|mod 

FACT: FACT’ | EXPR

FACT’: FACT” |TEXT|BOOLEAN

FACT’’: ID | INTEGER | NUMBER

ID : lettre {lettre|chiffre}

REPETER : repeat REPETER’ end 

REPETER’ : REPETER” INST 

REPETER”:EXPR times |while COND |until COND 

ECRRIRE : output FACT

Lire : input TEXT

AFFEC : ID = AFFEC’

AFFEC’ : ID |NUMBER |TEXT|INTEGER|BOOLEAN |EXPR|LIRE|COND|FCT

FCT : MIN|MAX

MIN: min FACT’’ and FACT’’

MAX : max FACT” and FACT’’

DECLARE : TYPE AFFEC

COMMENT : com TEXT’  \n



BOOLEAN : true | false 

INTEGER : CHIFFRE { CHIFFRE } 

NUMBER: = INTEGER {INTEGER}.INTEGER{INTEGER}

CHIFFRE : 0|...|9

LETTRE : a|...|z|A|...|Z

TEXT: “ TEXT’ “

TEXT’ : {LETTTRE {LETTTRE | CHIFFRE} | CHIFFRE {LETTTRE | CHIFFRE}}

TYPE : num|int|bool|string  
