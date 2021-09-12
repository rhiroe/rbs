#ifndef RBS__LEXER_H
#define RBS__LEXER_H

enum TokenType {
  NullType,         /* (Nothing) */
  pEOF,             /* EOF */
  ErrorToken,       /* Error */

  pLPAREN,          /* ( */
  pRPAREN,          /* ) */
  pCOLON,           /* : */
  pCOLON2,          /* :: */
  pLBRACKET,        /* [ */
  pRBRACKET,        /* ] */
  pLBRACE,          /* { */
  pRBRACE,          /* } */
  pHAT,             /* ^ */
  pARROW,           /* -> */
  pFATARROW,        /* => */
  pCOMMA,           /* , */
  pBAR,             /* | */
  pAMP,             /* & */
  pSTAR,            /* * */
  pSTAR2,           /* ** */
  pDOT,             /* . */
  pDOT3,            /* ... */
  pBANG,            /* ! */
  pQUESTION,        /* ? */
  pLT,              /* < */
  pEQ,              /* = */

  kBOOL,            /* bool */
  kBOT,             /* bot */
  kCLASS,           /* class */
  kFALSE,           /* false */
  kINSTANCE,        /* instance */
  kINTERFACE,       /* interface */
  kNIL,             /* nil */
  kSELF,            /* self */
  kSINGLETON,       /* singleton */
  kTOP,             /* top */
  kTRUE,            /* true */
  kVOID,            /* void */
  kTYPE,            /* type */
  kUNCHECKED,       /* unchecked */
  kIN,              /* in */
  kOUT,             /* out */
  kEND,             /* end */
  kDEF,             /* def */
  kINCLUDE,         /* include */
  kEXTEND,          /* extend */
  kPREPEND,         /* prepend */
  kALIAS,           /* alias */
  kMODULE,          /* module */
  kATTRREADER,      /* attr_reader */
  kATTRWRITER,      /* attr_writer */
  kATTRACCESSOR,    /* attr_accessor */
  kPUBLIC,          /* public */
  kPRIVATE,         /* private */
  kUNTYPED,         /* untyped */

  tLIDENT,          /* Identifiers starting with lower case */
  tUIDENT,          /* Identifiers starting with upper case */
  tULIDENT,         /* Identifiers starting with `_` followed by upper case */
  tULLIDENT,        /* Identifiers starting with `_` followed by lower case */
  tGIDENT,          /* Identifiers starting with `$` */
  tAIDENT,          /* Identifiers starting with `@` */
  tA2IDENT,         /* Identifiers starting with `@@` */
  tBANGIDENT,       /* Identifiers ending with `!` */
  tEQIDENT,         /* Identifiers ending with `=` */
  tQIDENT,          /* Quoted identifier */
  tOPERATOR,         /* Operator identifier */

  tCOMMENT,         /* Comment */
  tLINECOMMENT,     /* Comment of all line */

  tDQSTRING,        /* Double quoted string */
  tSQSTRING,        /* Single quoted string */
  tINTEGER,         /* Integer */
  tSYMBOL,          /* Symbol */
  tDQSYMBOL,        /* Double quoted symbol */
  tSQSYMBOL,        /* Single quoted symbol */
  tANNOTATION,      /* Annotation */
};

/**
 * The `byte_pos` (or `char_pos`) is the primary data.
 * The rest are cache.
 *
 * They can be computed from `byte_pos` (or `char_pos`), but it needs full scan from the beginning of the string (depending on the encoding).
 * */
typedef struct {
  int byte_pos;
  int char_pos;
  int line;
  int column;
} position;

typedef struct {
  position start;
  position end;
} range;

typedef struct {
  enum TokenType type;
  range range;
} token;

/**
 * The lexer state is the curren token.
 *
 * ```
 * ... "a string token"
 *    ^                      start position
 *          ^                current position
 *     ~~~~~~                Token => "a str
 * ```
 * */
typedef struct {
  VALUE string;
  position current;               /* The current position */
  position start;                 /* The start position of the current token */
  bool first_token_of_line;       /* This flag is used for tLINECOMMENT */
} lexstate;

extern token NullToken;
extern position NullPosition;
extern range NULL_RANGE;

token rbsparser_next_token(lexstate *state);

char *peek_token(lexstate *state, token tok);
int token_chars(token tok);
int token_bytes(token tok);

#define null_position_p(pos) (pos.byte_pos == -1)
#define null_range_p(range) (range.start.byte_pos == -1)
#define nonnull_pos_or(pos1, pos2) (null_position_p(pos1) ? pos2 : pos1)
#define RANGE_BYTES(range) (range.end.byte_pos - range.start.byte_pos)

const char *token_type_str(enum TokenType type);

void print_token(token tok);

#endif
