#include "tacs.h"

int astToTacMap[300] = {
    [AST_ADD] = TAC_ADD,
    [AST_SUB] = TAC_SUB,
    [AST_DIV] = TAC_DIV,
    [AST_MULT] = TAC_MULT,
    [AST_LESS] = TAC_LESS,
    [AST_GREATER] = TAC_GREATER,
    [AST_GE] = TAC_GE,
    [AST_LE] = TAC_LE,
    [AST_EQ] = TAC_EQ,
    [AST_DIF] = TAC_DIF};

TAC *tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2)
{
  TAC *newTac = 0;
  newTac = (TAC *)calloc(1, sizeof(TAC));
  newTac->type = type;
  newTac->res = res;
  newTac->op1 = op1;
  newTac->op2 = op2;
  newTac->prev = 0;
  newTac->next = 0;
  return newTac;
}
void tacPrint(TAC *tac)
{
  if (!tac || tac->type == TAC_SYMBOL)
    return;
  fprintf(stderr, "TAC(");
  switch (tac->type)
  {
  case TAC_COPY:
    fprintf(stderr, "TAC_COPY");
    break;
  case TAC_ADD:
    fprintf(stderr, "TAC_ADD");
    break;
  case TAC_SUB:
    fprintf(stderr, "TAC_SUB");
    break;
  case TAC_DIV:
    fprintf(stderr, "TAC_DIV");
    break;
  case TAC_MULT:
    fprintf(stderr, "TAC_MULT");
    break;
  case TAC_LESS:
    fprintf(stderr, "TAC_LESS");
    break;
  case TAC_GREATER:
    fprintf(stderr, "TAC_GREATER");
    break;
  case TAC_GE:
    fprintf(stderr, "TAC_GE");
    break;
  case TAC_LE:
    fprintf(stderr, "TAC_LE");
    break;
  case TAC_EQ:
    fprintf(stderr, "TAC_EQ");
    break;
  case TAC_DIF:
    fprintf(stderr, "TAC_DIF");
    break;
  case TAC_SYMBOL:
    fprintf(stderr, "TAC_SYMBOL");
    break;
  case TAC_COPY_VEC:
    fprintf(stderr, "TAC_COPY_VEC");
    break;
  case TAC_JMP:
    fprintf(stderr, "TAC_JMP");
    break;
  case TAC_JMP_FALSE:
    fprintf(stderr, "TAC_JMP_FALSE");
    break;
  case TAC_LABEL:
    fprintf(stderr, "TAC_LABEL");
    break;
  case TAC_PRINT:
    fprintf(stderr, "TAC_PRINT");
    break;
  case TAC_RETURN:
    fprintf(stderr, "TAC_RETURN");
    break;
  case TAC_READ:
    fprintf(stderr, "TAC_READ");
    break;
  case TAC_WHILE:
    fprintf(stderr, "TAC_WHILE");
    break;
  case TAC_BEGINFUN:
    fprintf(stderr, "TAC_BEGINFUN");
    break;
  case TAC_ENDFUN:
    fprintf(stderr, "TAC_ENDFUN");
    break;
  case TAC_VEC_ACCESS:
    fprintf(stderr, "TAC_VEC_ACCESS");
    break;
  case TAC_FUNCALL:
    printf("TAC_FUNCALL");
    break;
  case TAC_FUNC_ARG:
    printf("TAC_FUNC_ARG");
    break;
  default:
    fprintf(stderr, "TAC_UNDEFINED");
    break;
  }
  fprintf(stderr, ",%s", (tac->res) ? tac->res->text : "0");
  fprintf(stderr, ",%s", (tac->op1) ? tac->op1->text : "0");
  fprintf(stderr, ",%s", (tac->op2) ? tac->op2->text : "0");
  fprintf(stderr, ");\n");
}
void tacPrintRecursive(TAC *tac)
{
  if (!tac)
    return;
  else
  {
    tacPrintRecursive(tac->prev);
    tacPrint(tac);
  }
}

TAC *tacJoin(TAC *l1, TAC *l2)
{
  TAC *point;
  if (!l1)
    return l2;
  if (!l2)
    return l1;
  for (point = l2; point->prev != 0; point = point->prev)
    ;
  point->prev = l1;
  return l2;
}

// FUNCTIONS TO HELP DURING CODE GENERATION

TAC *createFunc(HASH_NODE *symbol, TAC *code_expr)
{
  return tacJoin(
      tacJoin(
          tacCreate(TAC_BEGINFUN, symbol, 0, 0),
          code_expr),
      tacCreate(TAC_ENDFUN, symbol, 0, 0));
}

TAC *createIf(TAC *code0, TAC *code1)
{
  TAC *jmp_tac = 0;
  TAC *label_tac = 0;
  HASH_NODE *new_label = 0;
  new_label = makeLabel();

  jmp_tac = tacCreate(TAC_JMP_FALSE, new_label, code0->res, 0);
  jmp_tac->prev = code0;

  label_tac = tacCreate(TAC_LABEL, new_label, 0, 0);
  label_tac->prev = code1;

  return tacJoin(jmp_tac, label_tac);
}

TAC *createWhile(TAC *code0, TAC *code1)
{
  TAC *jmp_begin_tac = 0;
  TAC *jmp_false_tac = 0;

  TAC *label_begin_tac = 0;
  TAC *label_end_tac = 0;

  HASH_NODE *beggining_label = 0;
  beggining_label = makeLabel();

  HASH_NODE *end_label = 0;
  end_label = makeLabel();

  label_begin_tac = tacCreate(TAC_LABEL, beggining_label, 0, 0);

  jmp_false_tac = tacCreate(TAC_JMP_FALSE, end_label, code0->res, 0);
  jmp_false_tac->prev = code0;

  jmp_begin_tac = tacCreate(TAC_JMP, beggining_label, 0, 0);
  jmp_begin_tac->prev = code1;

  label_end_tac = tacCreate(TAC_LABEL, end_label, 0, 0);
  label_end_tac->prev = jmp_begin_tac;

  return tacJoin(label_begin_tac, tacJoin(jmp_false_tac, label_end_tac));
}

TAC *createIfElse(TAC *code0, TAC *code1, TAC *code2)
{
  TAC *jmp_false_tac = 0;
  TAC *jmp_end_tac = 0;
  TAC *label_false_tac = 0;
  TAC *label_end_else_tac = 0;

  HASH_NODE *else_label = 0;
  else_label = makeLabel();

  HASH_NODE *end_else_label = 0;
  end_else_label = makeLabel();

  jmp_false_tac = tacCreate(TAC_JMP_FALSE, else_label, code0->res, 0);
  jmp_false_tac->prev = code0;

  jmp_end_tac = tacCreate(TAC_JMP, end_else_label, 0, 0);
  jmp_end_tac->prev = code1;

  label_false_tac = tacCreate(TAC_LABEL, else_label, 0, 0);
  label_false_tac->prev = jmp_end_tac;

  label_end_else_tac = tacCreate(TAC_LABEL, end_else_label, 0, 0);
  label_end_else_tac->prev = code2;

  return tacJoin(jmp_false_tac, tacJoin(label_false_tac, label_end_else_tac));
}

// CODE GENERATION

TAC *generateCode(AST *node)
{
  TAC *result = 0;
  TAC *code[MAX_SONS];

  if (!node)
    return 0;

  // PROCESS CHILDREN
  for (int i = 0; i < MAX_SONS; i++)
  {
    code[i] = generateCode(node->son[i]);
  }
  // PROCESS THIS CODE
  switch (node->type)
  {
  case AST_SYMBOL:
    result = tacCreate(TAC_SYMBOL, node->symbol, 0, 0);
    break;
  case AST_ADD:
  case AST_SUB:
  case AST_DIV:
  case AST_MULT:
  case AST_LESS:
  case AST_GREATER:
  case AST_GE:
  case AST_LE:
  case AST_EQ:
  case AST_DIF:
    result = tacJoin(tacJoin(code[0], code[1]), tacCreate(astToTacMap[node->type], makeTemp(), code[0] ? code[0]->res : 0, code[1] ? code[1]->res : 0));
    break;
  case AST_ATRIBUTION:
    result = tacJoin(code[1], tacCreate(TAC_COPY, node->son[0]->symbol ? node->son[0]->symbol : makeTemp(), code[1] ? code[1]->res : 0, code[2] ? code[2]->res : 0));
    break;
  case AST_VEC_ATRIBUTION:
    result = tacJoin(code[1], tacJoin(code[2], tacCreate(TAC_COPY_VEC, node->son[0]->symbol, code[1]->res, code[2]->res)));
    break;
  case AST_DEC_FUNCTION_INT:
  case AST_DEC_FUNCTION_FLOAT:
  case AST_DEC_FUNCTION_CHAR:
    result = createFunc(node->son[0]->symbol, code[1]);
    break;
  case AST_DEC_FUNCTION_INT_PARAM:
  case AST_DEC_FUNCTION_FLOAT_PARAM:
  case AST_DEC_FUNCTION_CHAR_PARAM:
    result = createFunc(node->son[0]->symbol, code[2]);
    break;
  case AST_IF_THEN:
    result = createIf(code[0], code[1]);
    break;
  case AST_IF_THEN_ELSE:
    result = createIfElse(code[0], code[1], code[2]);
    break;
  case AST_PRINT:
  case AST_PRINT_VALUES:
    result = tacJoin(tacJoin(code[0], tacCreate(TAC_PRINT, code[0] ? code[0]->res : 0, 0, 0)), code[1]);
    break;
  case AST_READ:
    result = tacCreate(TAC_READ, makeTemp(), 0, 0);
    break;
  case AST_RETURN:
    result = tacJoin(code[0], tacCreate(TAC_RETURN, code[0] ? code[0]->res : 0, 0, 0));
    break;
  
  /*case AST_WHILE:
    result = createWhile(code[0], code[1]);
    break;*/
  // case AST_GOTO:
  // case AST_ARRAY_ELEMENT:
  // case AST_FUNCTION_ARGUMENTS:
  // case AST_PARENTHESIS:
  // case AST_LIST_EXPR:

  //   break;
  // return the union of code for all subtrees
  default:
    result = tacJoin(code[0], tacJoin(code[1], tacJoin(code[2], code[3])));
    break;
  }

  return result;
}