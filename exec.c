#include "exec.h"
#include "error.h"
#include <stdio.h>
/**
 * \file exec.c
 * \brief Exécution d'une instruction
 * \version 0.1
 * \date 11 Juin 2014
 * 
 */


/**
 * \fn int is_in_immediate_mode(Instruction instr)
 * \brief Fonction qui test si l'instruction est donnée en mode immédiat
 * \author Etienne Strobbe
 * \param instr l'instruction à tester
 * \return renvoi true si vrai et false dans le cas contraire
 */
int is_in_immediate_mode(Instruction instr){
	return (instr.instr_generic._immediate);
}
/**
 * \fn int is_in_indexed_mode(Instruction instr)
 * \brief Fonction qui test si l'instruction est donnée en mode d'adressage indexé
 * \author Etienne Strobbe
 * \param instr l'instruction à tester
 * \return renvoi true si vrai et false dans le cas contraire
 */
int is_in_indexed_mode(Instruction instr){
	return (instr.instr_generic._indexed);
}

/**
 * \fn bool check_condition(Machine *pmach, Instruction instr)
 * \brief Fonction qui test si la condition de l'instruction est validée
 * \author Etienne Strobbe
 * \param pmach la machine qui execute l'instruction
 * \param instr l'instruction qui contient la condition
 * \return true si la condition est validée et false sinon
 */
bool check_condition(Machine *pmach,Instruction instr){
	if(instr.instr_generic._regcond > 6 || instr.instr_generic._regcond < 0) error(ERR_CONDITION,(pmach->_pc)-1);
	switch(instr.instr_generic._regcond){
		case NC:return true;
		case EQ:return ((pmach->_cc) == CC_Z);
		case NE:return ((pmach->_cc) != CC_Z);
		case GT:return ((pmach->_cc) == CC_P);
		case GE:return ((pmach->_cc) == CC_P || (pmach->_cc) == CC_Z);
		case LT:return ((pmach->_cc) == CC_N);
		case LE:return ((pmach->_cc) == CC_N || (pmach->_cc) == CC_Z);
		default:error(ERR_CONDITION,(pmach->_pc)-1);
	}
	return false;	
}
/**
 * \fn void check_adresse_data(Machine *pmach, int adresse)
 * \brief Test si l'adresse en paramètre est une adresse mémoire bien définie
 * \author Etienne Strobbe
 * \param pmach la machine qui execute les instruction
 * \param adresse l'adresse à tester
 */
void check_adresse_data(Machine *pmach, int adresse){
	if (adresse < 0 || adresse > (pmach -> _datasize))error(ERR_SEGDATA,(pmach ->_pc-1));
}
/**
 * \fn void check_adresse_text(Machine *pmach, int adresse)
 * \brief Test si l'adresse en paramètre est une adresse d'instruction bien définie
 * \author Etienne Strobbe
 * \param pmach la machine qui execute les instruction
 * \param adresse l'adresse à tester
 */
void check_adresse_text(Machine *pmach, int adresse){
	if (adresse < 0 || adresse > (pmach -> _textsize))error(ERR_SEGTEXT,(pmach ->_pc-1));
}

/**
 * \fn get_addr(Machine *pmach, Instruction instr)
 * \brief Fonction qui renvoi la bonne adresse en fonction du mode d'adressage (indexé ou non)
 * \author Etienne Strobbe
 * \param pmach la machine qui execute les instructions
 * \param instr l'instruction qui contient l'adresse et le mode d'adressage
 * \return l'adresse voulue
 */
int get_addr(Machine *pmach,Instruction instr){
	return (is_in_indexed_mode(instr))?(pmach->_registers[instr.instr_indexed._rindex])+instr.instr_indexed._offset:instr.instr_absolute._address;
}
/**
 * \fn update_condition(Machine *pmach, unsigned int condition)
 * \brief Fonction qui met à jour l'attribut CC de la machine
 * \author Etienne Strobbe
 * \param pmach la machine qui execute les instructions
 * \param condition la nouvelle condition
 */
void update_condition(Machine *pmach, unsigned int condition) {
	(pmach->_cc) = (condition == 0)?CC_Z:(condition>0)?CC_P:CC_N;
}

/**
 * \fn exec_illop(Machine *pmach, Instruction instr)
 * \brief Fonction qui execute l'instruction ILLOP
 * \author Rémy Dupanloup
 * \param pmach la machine qui execute les instructions
 * \param instr l'instruction à executer
 */
void exec_illop(Machine *pmach, Instruction instr){
	error(ERR_ILLEGAL, (pmach->_pc -1)); 
}

/**
 * \fn exec_load(Machine *pmach, Instruction instr)
 * \brief Fonction qui execute l'instruction LOAD
 * \author Rémy Dupanloup
 * \param pmach la machine qui execute les instructions
 * \param instr l'instruction à executer
 */
void exec_load(Machine *pmach, Instruction instr){
	// Mode immediat
	int reg = instr.instr_generic._regcond;
	if (is_in_immediate_mode(instr)){
		int val = instr.instr_immediate._value;
		(pmach->_registers[reg])=val;
	}
	// Mode addresse
	else{
		int adresse = get_addr(pmach, instr);
		check_adresse_data(pmach, adresse);
		(pmach->_registers[reg])=(pmach->_data[adresse]);
	}
	update_condition(pmach,(pmach->_registers)[reg]);
}

/**
 * \fn exec_store(Machine *pmach, Instruction instr)
 * \brief Fonction qui execute l'instruction STORE
 * \author Rémy Dupanloup
 * \param pmach la machine qui execute les instructions
 * \param instr l'instruction à executer
 */
void exec_store(Machine *pmach, Instruction instr){
	// Mode Immediat
	if (is_in_immediate_mode(instr)){
		error(ERR_IMMEDIATE, ((pmach -> _pc) -1));
	}
	// Mode addresse
	else{
		int adresse = get_addr(pmach, instr);
		int reg = instr.instr_generic._regcond;
		check_adresse_data(pmach, adresse);
		(pmach -> _data[adresse]) = (pmach -> _registers[reg]);

	}
}

/**
 * \fn exec_add(Machine *pmach, Instruction instr)
 * \brief Fonction qui execute l'instruction ADD
 * \author Etienne Strobbe
 * \param pmach la machine qui execute les instructions
 * \param instr l'instruction à executer
 */
void exec_add(Machine *pmach,Instruction instr){
	int reg = instr.instr_generic._regcond;
	// mode immediat -> traiter le cas signe
	if(is_in_immediate_mode(instr)){
		int val = instr.instr_immediate._value;
		(pmach->_registers[reg])+=val;
	}
	// mode addresse
	else{
		int adresse = get_addr(pmach,instr);
		check_adresse_data(pmach,adresse);		
		(pmach->_registers[reg])+=(pmach->_data[adresse]);
	}
	update_condition(pmach,(pmach->_registers)[reg]);
}

/**
 * \fn exec_branch(Machine *pmach, Instruction instr)
 * \brief Fonction qui execute l'instruction BRANCH
 * \author Etienne Strobbe
 * \param pmach la machine qui execute les instructions
 * \param instr l'instruction à executer
 */
void exec_branch(Machine *pmach,Instruction instr){
	if(is_in_immediate_mode(instr)) error(ERR_IMMEDIATE,(pmach->_pc)-1);
	check_condition(pmach,instr);
	if(check_condition(pmach,instr)){
		int adresse = get_addr(pmach,instr);
		check_adresse_text(pmach,adresse);
		pmach->_pc = adresse;	
	}
}

/**
 * \fn exec_sub(Machine *pmach, Instruction instr)
 * \brief Fonction qui execute l'instruction SUB
 * \author Rémy Dupanloup
 * \param pmach la machine qui execute les instructions
 * \param instr l'instruction à executer
 */
void exec_sub(Machine *pmach, Instruction instr){
	int reg = instr.instr_generic._regcond;
	// mode immediat
	if (is_in_immediate_mode(instr)){
		int val = instr.instr_immediate._value;
		(pmach->_registers[reg])-=val;		
	}
	// mode addresse
	else{
		int adresse = get_addr(pmach,instr);
		check_adresse_data(pmach,adresse);
		(pmach -> _registers[reg])-=(pmach -> _data[adresse]);
	}
	update_condition(pmach,(pmach->_registers)[reg]);
}

/**
 * \fn exec_call(Machine *pmach, Instruction instr)
 * \brief Fonction qui execute l'instruction CALL
 * \author Etienne Strobbe
 * \param pmach la machine qui execute les instructions
 * \param instr l'instruction à executer
 */
void exec_call(Machine *pmach,Instruction instr){
	if(is_in_immediate_mode(instr))error(ERR_IMMEDIATE,(pmach->_pc)-1);
	check_condition(pmach,instr);
	if(check_condition(pmach,instr)){
		pmach->_data[(pmach->_sp)--] = pmach->_pc;
		int adresse = get_addr(pmach,instr);
		check_adresse_text(pmach,adresse);
		pmach->_pc = adresse;
	}	
}

/**
 * \fn exec_ret(Machine *pmach, Instruction instr)
 * \brief Fonction qui execute l'instruction RET
 * \author Etienne Strobbe
 * \param pmach la machine qui execute les instructions
 * \param instr l'instruction à executer
 */
void exec_ret(Machine *pmach,Instruction instr){
	check_adresse_text(pmach,++(pmach->_sp));
	pmach->_pc = pmach->_data[(pmach->_sp)];
}

/**
 * \fn exec_push(Machine *pmach, Instruction instr)
 * \brief Fonction qui execute l'instruction PUSH
 * \author Etienne Strobbe
 * \param pmach la machine qui execute les instructions
 * \param instr l'instruction à executer
 */
void exec_push(Machine *pmach, Instruction instr){
	int val;
	if(is_in_immediate_mode(instr))val = instr.instr_immediate._value;
	else{
		int addr = get_addr(pmach,instr);
		check_adresse_data(pmach,addr);
		val = pmach->_data[addr];
	}
	if(pmach->_sp == 0)error(ERR_SEGSTACK,(pmach->_pc)-1);
	pmach->_data[(pmach->_sp)--] = val;	
}

/**
 * \fn exec_pop(Machine *pmach, Instruction instr)
 * \brief Fonction qui execute l'instruction POP
 * \author Etienne Strobbe
 * \param pmach la machine qui execute les instructions
 * \param instr l'instruction à executer
 */
void exec_pop(Machine *pmach, Instruction instr){
	if(is_in_immediate_mode(instr))error(ERR_IMMEDIATE,(pmach->_pc)-1);
	int adresse = get_addr(pmach,instr);
	check_adresse_data(pmach,adresse);
	if(pmach->_sp == (pmach->_datasize)-1)error(ERR_SEGSTACK,(pmach->_pc)-1);
	pmach->_data[adresse] = pmach->_data[++(pmach->_sp)];
}

/**
 * \fn exec_halt(Machine *pmach, Instruction instr)
 * \brief Fonction qui execute l'instruction HALT
 * \author Rémy Dupanloup
 * \param pmach la machine qui execute les instructions
 * \param instr l'instruction à executer
 */
void exec_halt(Machine *pmach, Instruction instr){
	warning(WARN_HALT,(pmach->_pc)-1);
}
	



//! Décodage et exécution d'une instruction
/*!
 * \author Etienne Strobbe
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
		case LOAD:exec_load(pmach, instr);break;
		case STORE:exec_store(pmach, instr);break;
		case ADD:exec_add(pmach,instr);break;
		case SUB:exec_sub(pmach,instr);break;
		case BRANCH:exec_branch(pmach,instr);break;
		case CALL:exec_call(pmach,instr);break;
		case RET:exec_ret(pmach,instr);break;
		case PUSH:exec_push(pmach,instr);break;
		case POP:exec_pop(pmach,instr);break;
		case HALT:exec_halt(pmach,instr);return false;
		default:break;
	}	
	return true;	
}

//! Trace de l'exécution
/*!
 * \brief On écrit l'adresse et l'instruction sous forme lisible.
 * \author Etienne Strobbe
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
