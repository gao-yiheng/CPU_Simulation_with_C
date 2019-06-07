#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

// Instruction define
#define LOAD_VALUE 		1
#define LOAD_ADDR 		2
#define LOAD_IND_ADDR 	3
#define LOAD_IDX_X_ADDR	4
#define LOAD_IDX_Y_ADDR	5
#define LOAD_SP_X		6			
#define STORE_ADDR		7
#define GET				8
#define PUT_PORT		9
#define ADD_X			10
#define ADD_Y			11
#define SUB_X			12
#define SUB_Y			13
#define COPY_TO_X		14
#define COPY_FROM_X		15
#define COPY_TO_Y		16
#define COPY_FROM_Y		17
#define COPY_TO_SP		18
#define COPY_FROM_SP	19
#define JUMP_ADDR		20
#define JUMP_IF_EQUAL_ADDR		21
#define JUMP_IF_NOT_EQUAL_ADDR	22
#define CALL_ADDR		23
#define RET				24
#define INC_X			25
#define DEC_X			26
#define PUSH			27
#define POP				28
#define INT				29
#define I_RET			30
#define END 			50

#endif