#include "exec.h"
#include "error.h"
#include <stdio.h>

int is_in_immediate_mode(Instruction instr){
	return (instr.instr_generic._immediate);
}
int is_in_indexed_mode(Instruction instr){
	return (instr.instr_generic._indexed);
}

void check_condition(Machine *pmach,Instruction instr){
	if(instr.instr_generic._regcond > 6 || instr.instr_generic._regcond < 0) error(ERR_CONDITION,(pmach->_pc)-1);
}

int get_addr(Machine *pmach,Instruction instr){
	return (is_in_indexed_mode(instr))?pmach->_registers[instr.instr_indexed._rindex]+instr.instr_indexed._offset:instr.instr_absolute._address;
}

void exec_illop(Machine *pmach, Instruction instr){
	error(ERR_ILLEGAL, (pmach->_pc -1)); // Peut-être inutile
}

void exec_add(Machine *pmach,Instruction instr){
	// mode immediat -> traiter le cas signe
	if(is_in_immediate_mode(instr)){
		int val = instr.instr_immediate._value;
		int reg = instr.instr_immediate._regcond;
		(pmach->_registers[reg])+=val;
	}
	// mode addresse
	else{
		int adresse = get_addr(pmach,instr);
		int reg = instr.instr_generic._regcond;
		if(adresse<0 || adresse>(pmach->_dataend))error(ERR_SEGDATA,((pmach->_pc)-1));//TODO voir si error arrete le programme sinon le faire
		
		(pmach->_registers[reg])+=(pmach->_data[adresse]);
	}
}


void exec_branch(Machine *pmach,Instruction instr){
	if(is_in_immediate_mode(instr)) error(ERR_IMMEDIATE,(pmach->_pc)-1);
	check_condition(pmach,instr);
	if(pmach->_cc == instr.instr_generic._regcond){
		int adresse = get_addr(pmach,instr);
		if(adresse<0 || adresse>pmach->_textsize)error(ERR_SEGTEXT,(pmach->_pc)-1);
		pmach->_pc = adresse;	
	}
}

void exec_sub(Machine *pmach, Instruction instr){
	// mode immediat
	if (is_in_immediate_mode(instr)){
		int val = instr.instr_immediate._value;
		int reg = instr.instr_immediate._regcond;
		(pmach->_registers[reg])-=val;		
	}
	// mode addresse
	else{
		int adresse = get_addr(pmach,instr);
		int reg = instr.instr_generic._regcond;
		
		if (adresse < 0 || adresse > (pmach -> _dataend))error(ERR_SEGDATA,(pmach ->_pc-1));
		(pmach -> _registers[reg])-=(pmach -> _data[adresse]);
	}
}

void exec_call(Machine *pmach,Instruction instr){
	if(is_in_immediate_mode(instr))error(ERR_IMMEDIATE,(pmach->_pc)-1);
	check_condition(pmach,instr);
	if(pmach->_cc == instr.instr_generic._regcond){
		pmach->_data[(pmach->_sp)--] = pmach->_pc;
		pmach->_pc = get_addr(pmach,instr);
	}	
}


//! Décodage et exécution d'une instruction
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return faux après l'exécution de \c HALT ; vrai sinon
 */
bool decode_execute(Machine *pmach, Instruction instr){
	Code_Op cop = instr.instr_generic._cop;
	// si l'instruction n'existe pas
	if(cop < 0 || cop > LAST_COP)error(ERR_UNKNOWN,pmach->_pc);
	switch(cop){
		// TODO : arguments a venir
		case ILLOP:exec_illop(pmach, instr);break;
		case NOP: break;
		/*case LOAD:exec_load();break;
		case STORE:exec_store();break;*/
		case ADD:exec_add(pmach,instr);break;
		case SUB:exec_sub(pmach,instr);break;
		case BRANCH:exec_branch(pmach,instr);break;
		case CALL:exec_call(pmach,instr);break;
		/*case RET:exec_ret();break;
		case PUSH:exec_push();break;
		case POP:exec_pop();break;
		case HALT:exec_halt();break;*/
		default:break;
	}	
	return true;	
}

//! Trace de l'exécution
/*!
 * On écrit l'adresse et l'instruction sous forme lisible.
 *
 * \param msg le message de trace
 * \param pmach la machine en cours d'exécution
 * \param instr l'instruction à exécuter
 * \param addr son adresse
 */
void trace(const char *msg, Machine *pmach, Instruction instr, unsigned addr){
	printf("TRACE: %s: 0x%04x ",msg,addr);
	print_instruction(instr,addr);
	printf("\n");
}
