#include "monkeyart.h"
#include <fstream>
#include <time.h>
string output = "";
const char acceptable[16] = {'0','1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
const char registers [8] = {'A', 'B', 'C', 'D', 'E', 'H', 'L', 'M'};
const char regPair [3] = {'B', 'D', 'H'};
const char adcop[8] = {'F', '8', '9', 'A', 'B', 'C', 'D', 'E'};
const char addop[8] = {'7', '0', '1', '2', '3', '4', '5', '6'};
const char dadop[8] = {'0', '1', '2'};
const char popop[8] = {'C', 'D', 'E'};
const char dcrop[8] = {'3', '0', '0', '1', '1', '2', '2', '3'};
const char movbuilder [8] = {'7', '4', '4', '5', '5', '6', '6', '7'};
const char rst [8] = {'C', 'C', 'D', 'D', 'E', 'E', 'F', 'F'};
const string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d, %X", &tstruct);

    return buf;
}
bool checkVal (string chk, int letters, bool args){
	//args = 0 -> 2 args; 1 -> 1 arg
	int confirm = 0;
			for (int c = (letters + 1); c <= ((6 + (letters - 2)) - (args * 2)); c++){
				char d = chk.at(c);
			for (int e = 0; e <=15;e++){
				if (d == acceptable[e]){
					confirm++;
				}
			}
		}
		if ((chk.at(7 + (letters - 2)) == 32 && args == 0) || (chk.at(5 + (letters - 2)) == 32 && args == 1)){
				confirm++;
			}
	if ((confirm == 5 && args == 0) || (confirm == 3 && args == 1)){
				return true;
			}
			else {
				return false;
			}
}
string getString (char in){
	string s(1,in);
	return s;
}
void genScript (string pass, char op1, char op2, int args, int letters, int log, bool write){
	pass.append("       ");
	//2-> 2 letters; 3-> 3 letters ;4 -> 4 letters
	switch (args){
		case 0:
			if (log >= 1){
				cout << "\nMonkeyScript85 for this Instruction:\nTYPE " << op1 << op2 << "\nPRESS INR";
				if (write == 1){
					string buf = "\nTYPE " + getString(op1) + getString(op2) + "\nPRESS INR";
					output.append(buf);
				}		
			}
			break;
		case 1:
			if (checkVal(pass, letters, 1) == true){
			string arg = pass.substr((letters + 1),2);
			if (log >= 1){cout << "\nMonkeyScript85 for this Instruction:\nTYPE " << op1 << op2 << "\nPRESS INR\nTYPE "<<arg<<"\nPRESS INR";}
			if (write == 1){
					string buf = "\nTYPE " + getString(op1) + getString(op2) + "\nPRESS INR\nTYPE " + arg + "\nPRESS INR";
					output.append(buf);
				}
		} else {
			cout << "\nCannot Generate MonkeyScript85: Invalid Data Values Provided.";
		}
			break;
		case 2:
			if (checkVal(pass, letters, 0) == true){	
			string arg1 = pass.substr((letters + 1),2);
			string arg2 = pass.substr((letters + 3),2);
			if (log >= 1){cout << "\nMonkeyScript85 for this Instruction:\nTYPE " << op1 << op2 << "\nPRESS INR\nTYPE "<<arg2<<"\nPRESS INR\nTYPE "<<arg1<<"\nPRESS INR";}
			if (write == 1){
					string buf = "\nTYPE " + getString(op1) + getString(op2) + "\nPRESS INR\nTYPE " + arg2 + "\nPRESS INR\nTYPE " + arg1 + "\nPRESS INR";
					output.append(buf);
				}
			} else {
				cout << "\nCannot Generate MonkeyScript85: Invalid Data Values Provided.";
			}
			break;
	}
	
}
void info2LI (string in, int place, int log, bool write){
	switch (place){
		case 0:
			if (log == 2){cout << "Instruction name: Call on Carry\nConditional Call which executes the call function when Carry Flag is Set.\n";}
			genScript (in, 'D', 'C', 2, 2, log, write);
			break;
		case 1:
			if (log == 2){cout << "Instruction name: Call on Minus\nConditional Call which executes the call function when Sign Flag is Set.\n";}
			genScript (in, 'F', 'C', 2, 2, log, write);
			break;
		case 2:
			if (log == 2){cout << "Instruction name: Call on Positive\nConditional Call which executes the call function when Carry Flag = 0.\n";}
			genScript (in, 'F', '4', 2, 2, log, write);
			break;
		case 3:
			if (log == 2){cout << "Instruction name: Call on Zero\nConditional Call which executes the call function when Zero Flag is Set.\n";}
			genScript (in, 'C', 'C', 2, 2, log, write);
			break;
		case 4:
			if (log == 2){cout << "Instruction name: Enable Interrupt\nThis is a single byte instruction. On execution interrupt enable flip flop is set and all interrupts are enabled. No flags are affected.\n";}
			genScript (in, 'F', 'B', 0, 2, log, write);
			break;
		case 5:
			if (log == 2){cout << "Instruction name: Input 8 Bit Data from an input port to Accumulator\nThis is the instruction which is included in the I/O instruction group.\n";}
			genScript (in, 'D', 'B', 1, 2, log, write);
			break;
		case 6:
			if (log == 2){cout << "Instruction name: Jump on Carry\nJump to Address Executed when Carry Flag is Set.\n";}
			genScript (in, 'D', 'A', 2, 2, log, write);
			break;
		case 7:
			if (log == 2){cout << "Instruction name: Jump on Minus\nJump to Address Executed when Sign Flag = 0\n";}
			genScript (in, 'F', 'A', 2, 2, log, write);
			break;
		case 8:
			if (log == 2){cout << "Instruction name: Jump on Positive\nJump to Address Executed when Sign Flag is Set.\n";}
			genScript (in, 'F', '2', 2, 2, log, write);
			break;
		case 9:
			if (log == 2){cout << "Instruction name: Jump on Zero\nJump to Address Executed when Zero Flag is Set.\n";}
			genScript (in, 'C', 'A', 2, 2, log, write);
			break;
		case 10:
			if (log == 2){cout << "Instruction name: Return on Carry\nEnd of Subroutine Instruction Executed when Carry Flag is Set.\n";}
			genScript (in, 'D', '8', 0, 2, log, write);
			break;
		case 11:
			if (log == 2){cout << "Instruction name: Return on Minus\nEnd of Subroutine Instruction Executed when Sign Flag is set.\n";}
			genScript (in, 'F', '8', 0, 2, log, write);
			break;
		case 12:
			if (log == 2){cout << "Instruction name: Return on Positive\nEnd of Subroutine Instruction Executed when Sign Flag = 0.\n";}
			genScript (in, 'F', '0', 0, 2, log, write);
			break;
		case 13:
			if (log == 2){cout << "Instruction name: Return on Zero\nEnd of Subroutine Instruction Executed when Zero Flag is Set.\n";}
			genScript (in, 'C', '8', 0, 2, log, write);
			break;
	}
}
char dcr (int chk) {
if (chk % 2 == 0){
	return 'D';
} else {
	return '5';
}
}
char inr (int chk) {
if (chk % 2 == 0){
	return 'C';
} else {
	return '4';
}
}
char mov (int chk, int reg){
if (chk % 2 == 0){
	return adcop[reg];
} else {
	return addop[reg];
}	
}
char mvi (int chk){
if (chk % 2 == 0){
	return 'E';
} else {
	return '6';
}	
}
char rstinst (int chk){
if (chk % 2 == 0){
	return '7';
} else {
	return 'F';
}	
}
void info3LI (string in, int place, int log, bool write){
	if (log == 2){cout << "Instruction Name: ";}
	bool option = false;
	switch (place){
	case 0:
		if (log == 2){cout << "Add with Carry Immediate to Accumulator\n8-bit data is added along with carry to accumulator contents and the result is stored in accumulator.\n";}
		genScript (in, 'C','E', 1, 3, log, write);
		break;
	case 1:
		if (log == 2){cout << "Add with Carry Indirect to Accumulator\nThe operand, which is placed along with opcode in the code byte, can be either a register or the memory location pointed by HL, pair\n";}
		//Register Variant
		for (int chk=0; chk <= 7; chk++){
		if (in.at(4) == registers[chk] && in.at(3) == 32 && in.at (5) == 32){
		genScript (in, '8',adcop[chk], 0, 5, log, write);
		option = true;
		break;
			} 
		}
	if (option == false) {
		cout << "\nInvalid Variant of Instruction.\nCannot Generate MonkeyScript85.\n";
		}
		break;
	case 2:
		if (log == 2){cout << "Add Register to Accumulator\nThis is a single byte instruction with operand placed along with opcode in the code byte. The operand can be a register or a memory location pointed HL register pair.\n";}
		for (int chk=0; chk <= 7; chk++){
		if (in.at(4) == registers[chk] && in.at(3) == 32 && in.at (5) == 32){
		genScript (in, '8',addop[chk], 0, 5, log, write);
		option = true;
		break;
			} 
		}
	if (option == false) {
			cout << "\nInvalid Variant of Instruction.\nCannot Generate MonkeyScript85.\n";
		}
		break;
	case 3:
		if (log == 2){cout << "Add Immediate to Accumulator\nThis immediate data is added to accumulator contents. Result is stored in the accumulator and all flags are modified. This type of addressing mode is termed as an immediate addressing\n";}
		genScript (in, 'C','6', 1, 3, log, write);
		break;
	case 4:
		if (log == 2){cout << "Logical AND-With Accumulator\nThis is a single byte instruction, which carries out logical ANDing of the contents of operand with the contents of Accumulator. The result is stored in accumulator itself.\n";}
		for (int chk=0; chk <= 7; chk++){
		if (in.at(4) == registers[chk] && in.at(3) == 32 && in.at (5) == 32){
		genScript (in, 'A',addop[chk], 0, 5, log, write);
		option = true;
		break;
			} 
		}
	if (option == false) {
			cout << "\nInvalid Variant of Instruction.\nCannot Generate MonkeyScript85.\n";
		}
		break;
	case 5:
		if (log == 2){cout << "AND Immediate With Accumulator\nIt uses immediate addressing mode. The second byte acts as 8-bit immediate data. It is logically ANDed with the contents of accumulator.\n";}
		genScript (in, 'E','6', 1, 3, log, write);
		break;
	case 6:
		if (log == 2){cout << "Complement Accumulator\nWhen executed this instruction complements the accumulator contents. The result is stored in accumulator itself. No flags are affected.\n";}
		genScript (in, '2','F', 0, 3, log, write);
		break;
	case 7:
		if (log == 2){cout << "Complement Carry\nWhen executed it complements the carry flag\n";}
		genScript (in, '3','F', 0, 3, log, write);
		break;
	case 8:
		if (log == 2){cout << "Compare with Accumulator\nThis instruction compares the contents of the operand (reg/memory) with the contents of accumulator.\n";}
		for (int chk=0; chk <= 7; chk++){
		if (in.at(4) == registers[chk] && in.at(3) == 32 && in.at (5) == 32){
		genScript (in, 'B',adcop[chk], 0, 5, log, write);
		option = true;
		break;
			} 
		}
	if (option == false) {
			cout << "\nInvalid Variant of Instruction.\nCannot Generate MonkeyScript85.\n";
		}
		break;
	case 9:
		if (log == 2){cout << "Call on No Carry\nConditional Call which executes the call function when Carry Flag = 0.\n";}
		genScript (in, 'D','4', 1, 3, log, write);
		break;
	case 10:
		if (log == 2){cout << "Call on No Zero\nConditional Call which executes the call function when Zero Flag = 0.\n";}
		genScript (in, 'C','4', 2, 3, log, write);
		break;
	case 11:
		if (log == 2){cout << "Call on Even Parity\nConditional Call which executes the call function when Parity Flag = 1.\n";}
		genScript (in, 'E','C', 2, 3, log, write);
		break;
	case 12:
		if (log == 2){cout << "Compare Immediate with Accumulator.\nThis instruction is a two byte instruction utilizing immediate addressing mode. The execution of this instruction is very much similar to CMP instruction. The only difference being that in CPI instruction the immediate data is compared with accumulator.\n";}
		genScript (in, 'F','E', 1, 3, log, write);
		break;
	case 13:
		if (log == 2){cout << "Call on Odd Parity\nConditional Call which executes the call function when Parity Flag = 0.\n";}
		genScript (in, 'E','4', 2, 3, log, write);
		break;
	case 14:
		if (log == 2){cout << "Decimal Adjust Accumulator\nThis is a special arithmetic instruction. It adjusts binary contents of accumulator to two 4-bit BCD digits.\nThis is the only instruction which uses Auxiliary carry (AC) flag for code adjustment. The CPU uses the flag internally. All flags are modified to reflect the result of execution. \nThe adjustment process is as follows:\nThe important condition is that this instruction must always follow an addition instruction for two BCD numbers. Thus it adjusts the sum of two BCD numbers to BCD and does not convert a binary number to BCD. Also it cannot be used to adjust results after subtraction.\n1) Carry out BCD Addition using DAD.\n2) If only lower nibble of accumulator is greater than 9 or if AC flag is set add 06 to lower nibble.\n3) If only higher nibble of accumulator is greater than 9 or if C flag is set add 06 to lower nibble\n4) If both upper and lower nibbles are greater than 9 or AC and C flags are set respectively then add 66 to the accumulator contents.\n";}
		genScript (in, '2','7', 0, 3, log, write);
		break;
	case 15:
		if (log == 2){cout << "Add Register Pair to H-L Register Pair\nIt adds 16-bit contents of specified operand to 16-bit contents of H and L register pair. The result is stored in H and L register pair.\n";}
		//Stack Pointer + Register Pair Variant
		for (int chk=0; chk <= 2; chk++){
		if (in.at(4) == regPair[chk] && in.at(3) == 32 && in.at (5) == 32){
		genScript (in, dadop[chk],'9', 0, 5, log, write);
		option = true;
		break;
			} 
		}
		if (in.substr(4,2) == "SP" && in.at(3) == 32 && in.at (6) == 32){
			genScript (in, '3', '9', 0, 5, log, write);
		} else if (option == false) {
			cout << "\nInvalid Variant of Instruction.\nCannot Generate MonkeyScript85.\n";
		}
		break;
	case 16:
		if (log == 2){cout << "Decrement Source by 1\nWhen executed, it will decrement the contents of source by l .All flags except carry are modified. The source can be any register or memory pointed by HL pair.\n";}
		for (int chk=0; chk <= 7; chk++){
		if (in.at(4) == registers[chk] && in.at(3) == 32 && in.at (5) == 32){
		genScript (in, dcrop[chk], dcr(chk), 0, 5, log, write);
		option = true;
		break;
			} 
		}
	if (option == false) {
			cout << "\nInvalid Variant of Instruction.\nCannot Generate MonkeyScript85.\n";
		}
		break;
	case 17:
		if (log == 2){cout << "Decrement Register Pair by 1\nThis also is a single byte extended decrement register. It decrements the contents of operand (16-bit) quantity by 1.\n";}
		for (int chk=0; chk <= 2; chk++){
		if (in.at(4) == regPair[chk] && in.at(3) == 32 && in.at (5) == 32){
		genScript (in, dadop[chk],'B', 0, 5, log, write);
		option = true;
		break;
			} 
		}
		if (in.substr(4,2) == "SP" && in.at(3) == 32 && in.at (6) == 32){
			genScript (in, '3', 'B', 0, 5, log, write);
		} else if (option == false) {
			cout << "\nInvalid Variant of Instruction.\nCannot Generate MonkeyScript85.\n";
		}
		break;
	case 18:
		if (log == 2){cout << "Halt and Enter Wait State\nAfter completing its execution CPU goes to a state halt halting further execution. Wait states are inserted in every During clock cycle. Halt CPU maintains register contents.\n";}
		genScript (in, '7','6', 0, 3, log, write);
		break;
	case 19:
		if (log == 2){cout << "Increment Contents of Register/Memory by 1\nThis is a single byte instruction when executed the contents of operand are incremented by 1.\n";}
		for (int chk=0; chk <= 7; chk++){
		if (in.at(4) == registers[chk] && in.at(3) == 32 && in.at (5) == 32){
		genScript (in, dcrop[chk], inr(chk), 0, 5, log, write);
		option = true;
		break;
			} 
		}
	if (option == false) {
			cout << "\nInvalid Variant of Instruction.\nCannot Generate MonkeyScript85.\n";
		}
		break;
	case 20:
		if (log == 2){cout << "Increment Register Pair by 1\nWhich when executed increments the 16-bit Contents of operand register pair by 1\n";}
		for (int chk=0; chk <= 2; chk++){
		if (in.at(4) == regPair[chk] && in.at(3) == 32 && in.at (5) == 32){
		genScript (in, dadop[chk],'3', 0, 5, log, write);
		option = true;
		break;
			} 
		}
		if (in.substr(4,2) == "SP" && in.at(3) == 32 && in.at (6) == 32){
			genScript (in, '3', '3', 0, 5, log, write);
		} else if (option == false) {
			cout << "\nInvalid Variant of Instruction.\nCannot Generate MonkeyScript85.\n";
		}
		break;
	case 21:
		if (log == 2){cout << "Unconditional Jump\nThis instruction is a three-byte instruction. First byte is opcode, second byte is lower order address for branching and the third byte gives higher order address byte for branching. When this instruction is executed the program control is unconditionally transferred to the branch address given in instruction.\n";}
		genScript (in, 'C','3', 2, 3, log, write);
		break;
	case 22:
		if (log == 2){cout << "Jump on No Carry\nExecutes Jump Instruction when CY Flag = 0\n";}
		genScript (in, 'D','2', 2, 3, log, write);
		break;
	case 23:
		if (log == 2){cout << "Jump on No Zero\nExecutes Jump Instruction when Z Flag = 0\n";}
		genScript (in, 'C','2', 2, 3, log, write);
		break;
	case 24:
		if (log == 2){cout << "Jump on Even Parity\nExecutes Jump Instruction when P Flag = 1\n";}
		genScript (in, 'E','A', 2, 3, log, write);
		break;
	case 25:
		if (log == 2){cout << "Jump on Odd Parity\nExecutes Jump Instruction when P Flag = 0\n";}
		genScript (in, 'E','2', 2, 3, log, write);
		break;
	case 26:
		if (log == 2){cout << "Load Accumulator Direct\nThis instruction when executed copies contents of the memory location pointed by address given in instruction to the accumulator. Contents of source are not altered.\n";}
		genScript (in, '3','A', 2, 3, log, write);
		break;
	case 27:
		if (log == 2){cout << "Load Register pair Immediate\nOn execution this 16-bit data is copied into the designated register pair.\n";}
		for (int chk=0; chk <= 2; chk++){
		if (in.at(4) == regPair[chk] && in.at(3) == 32 && in.at (5) == 44 && in.at(6) == 32){
		genScript (in, dadop[chk],'1', 2, 6, log, write);
		option = true;
		break;
			} 
		}
		if (option == false) {
			cout << "\nInvalid Variant of Instruction.\nCannot Generate MonkeyScript85.\n";
		}
		break;
	case 28:
		in.append ("  ");
		if (log == 2){cout << "Move-Copy to Register\nOn execution this 16-bit data is copied into the designated register pair.\n";}
		for (int reg1 = 0; reg1 <= 7 ; reg1 ++){
			for (int reg2 = 0; reg2 <= 7; reg2++){
			if (in.at(6) == registers[reg2] && in.at(4) == registers[reg1] && in.at(7) == 32 && in.at (5) == 44){
				if (registers[reg1] == 'M' && registers[reg2] == 'M'){
					option = false;
				} else {
					genScript (in, movbuilder[reg1],mov(reg1, reg2), 0, 7, log, write);
					option = true;
				}
				break;
			}
		}
	}
		if (option == false) {
			cout << "\nInvalid Variant of Instruction.\nCannot Generate MonkeyScript85.\n";
		}
		break;
	case 29:
		if (log == 2){cout << "Move-Copy Immediate\nThis 2-byte instruction is used to store the 8-bit data, given in instruction itself, into the destination, which may be a register or memory location. The first byte of instruction gives the destination and second byte is the 8-bit data. No flags are affected.\n";}
		for (int chk=0; chk <= 7; chk++){
		if (in.at(4) == registers[chk] && in.at(3) == 32 && in.at (5) == 44 && in.at(6) == 32){
		genScript (in, dcrop[chk],mvi(chk), 1, 6, log, write);
		option = true;
		break;
			} 
		}
		if (option == false) {
			cout << "\nInvalid Variant of Instruction.\nCannot Generate MonkeyScript85.\n";
		}
		break;
	case 30:
		if (log == 2){cout << "No-Operation\nThis is a single byte instruction. On execution no operation is performed only instruction is fetched and decoded. No flags are affected. It can be create time delays using loops.\n";}
		genScript (in, '0','0', 0, 3, log, write);
		break;
	case 31:
		if (log == 2){cout << "Logical OR with Accumulator\nThis single byte instruction carries out logical ORing of the contents of operand and contents of accumulator. The result is stored in accumulator itself.\n";}
		for (int chk=0; chk <= 7; chk++){
		if (in.at(4) == registers[chk] && in.at(3) == 32 && in.at (5) == 32){
		genScript (in, 'B',addop[chk], 0, 5, log, write);
		option = true;
		break;
			} 
		}
	if (option == false) {
			cout << "\nInvalid Variant of Instruction.\nCannot Generate MonkeyScript85.\n";
		}
		break;
	case 32:
		if (log == 2){cout << "Logical OR Immediate with Accumulator\nThis data is logically ORed with the contents of the accumulator. The result is stored in the accumulator itself.\n ";}
		genScript (in, 'F','6', 1, 3, log, write);
		break;
	case 33:
		if (log == 2){cout << "Output 8-Bit Data from Accumulator to an Output Port\nIn other words the 8-bit data in accumulator is output on to the output port. As in the case of IN instruction the first byte signifies opcode and the second one informs the 8-bit output port address.\n";}
		genScript (in, 'D','3', 1, 3, log, write);
		break;
	case 34:
		if (log == 2){cout << "Pop-off Stack to Register Pair\nOn execution copies two top bytes on stack to designated register pair in operand. The execution follows the sequence given below.\na) Contents of top most location of stack called stack top are copied into lower register (such as C in BC etc) of the pair. The SP is incremented by 1.\nb) Contents of the stack location pointed by SP are copied into higher register of the pair. The stack pointer SP is incremented by 1\n";}
		for (int chk=0; chk <= 2; chk++){
		if (in.at(4) == regPair[chk] && in.at(3) == 32 && in.at (5) == 32){
		genScript (in, popop[chk],'1', 0, 5, log, write);
		option = true;
		break;
			} 
		}
		if (in.substr(4,3) == "PSW" && in.at(3) == 32 && in.at (7) == 32){
			genScript (in, 'F', '1', 0, 6, log, write);
		} else if (option == false) {
			cout << "\nInvalid Variant of Instruction.\nCannot Generate MonkeyScript85.\n";
		}
		break;
	case 35:
		if (log == 2){cout << "Rotate Accumulator Left through carry\nIt rotates each binary bit of accumulator left by one bit position through carry flag. No other flags are modified. D7 is moved to carry and carry is moved to D0.\n";}
		genScript (in, '1','7', 0, 3, log, write);
		break;
	case 36:
		if (log == 2){cout << "Rotate Accumulator Right Through Carry\nThis is an instruction, which rotates the accumulator contents to 1 bit position right the carry i.e. D0 goes to carry and carry goes to D0. No other flags are affected.\n";}
		genScript (in, '1','F', 0, 3, log, write);
		break;
	case 37:
		if (log == 2){cout << "Unconditional Return\nA return instruction indicates end of subroutine and transfers Lne control back to main program. This is a single byte instruction. On execution it loads two bytes from stack i.e. address of instruction next to CALL into PC and Increments SP by two.\n";}
		genScript (in, 'C','9', 0, 3, log, write);
		break;
	case 38:
		if (log == 2){cout << "Read Interrupt Mask\nThis also is a single byte instruction, which is used for reading interrupt masking information as well as serial data input. It utilizes accumulator contents for that purpose.\n";}
		genScript (in, '2','0', 0, 3, log, write);
		break;
	case 39:
		if (log == 2){cout << "Rotate Accumulator Left\nIt is used to rotate each binary bit in accumulator to left by one position. Bit D7, is placed in bit position D0 as well as in the carry flag.\n";}
		genScript (in, '0','7', 0, 3, log, write);
		break;
	case 40:
		if (log == 2){cout << "Return on No Carry\nReturn Instruction Executed when CY Flag = 0\n";}
		genScript (in, 'D','0', 0, 3, log, write);
		break;
	case 41:
		if (log == 2){cout << "Return on No Zero\nReturn Instruction Executed when Z Flag = 0\n";}
		genScript (in, 'C','0', 0, 3, log, write);
		break;
	case 42:
		if (log == 2){cout << "Return on Even Parity\nReturn Instruction Executed when P Flag = 1\n";}
		genScript (in, 'E','8', 0, 3, log, write);
		break;
	case 43:
		if (log == 2){cout << "Return on Odd Parity\nReturn Instruction Executed when P Flag = 0\n";}
		genScript (in, 'E','0', 0, 3, log, write);
		break;
	case 44:
		if (log == 2){cout << "Rotate Accumulator Right\nIt is used to rotate each binary bit in accumulator to right by 1 position. Bit D0 is placed in bit position D7, as well as in carry flag.";}
		genScript (in, '0','F', 0, 3, log, write);
		break;
	case 45:
		if (log == 2){cout << "Restart Instruction\nWe have seen the use and functioning of interrupts. We know that on giving the 8085 an interruption the pin\nINTR (Pin No.10) the microprocessor fetches the Interrupt service Routine (ISR) branch address from data bus. For this we should externally provide the instruction.\nRST instructions are one of the instructions, which can be used to transfer the control to ISR.\nThese are 8 different RST instructions RSTO to RST7. These are all one byte instruction.\nIn execution they are similar to call instruction with a predefined subroutine address obtained from the number associated with RST.\nAs a rule if n is the number associated with RST then the subroutine or ISR address is 8n. No flags are affected.\nThese instructions can be used in software to generate interrupts thus these are also called software interrupts.\n";}
		for (int chk=0; chk <= 7; chk++){
		if (in.at(4) == chk + 48 && in.at(3) == 32 && in.at (5) == 32){
		genScript (in, rst[chk],rstinst(chk), 0, 5, log, write);
		option = true;
		break;
			} 
		}
	if (option == false) {
			cout << "\nInvalid Variant of Instruction.\nCannot Generate MonkeyScript85.\n";
		}
		break;
	case 46:
		if (log == 2){cout << "Subtract Source and Borrow from Accumulator\nIt subtracts contents of source and borrow from the accumulator contents. It is a 2's complement subtraction. Result is stored in accumulator.\n";}
		for (int chk=0; chk <= 7; chk++){
		if (in.at(4) == registers[chk] && in.at(3) == 32 && in.at (5) == 32){
		genScript (in, '9',adcop[chk], 0, 5, log, write);
		option = true;
		break;
			} 
		}
	if (option == false) {
			cout << "\nInvalid Variant of Instruction.\nCannot Generate MonkeyScript85.\n";
		}
		break;
	case 47:
		if (log == 2){cout << "Subtract Immediate with Borrow\nThis is a two-byte instruction using immediate addressing mode. The first byte is opcode and second byte is 8-bit immediate data. The immediate data and borrow is Subtracted from accumulator contents. It is a 2's complement subtraction. The result is stored in accumulator.\n";}
		genScript (in, 'D','E', 1, 3, log, write);
		break;
	case 48:
		if (log == 2){cout << "Set Interrupt Mask\nThis is a single byte multipurpose instruction it allows setting of masking of interrupts and serial output. It uses accumulator contents for this purpose.\n";}
		genScript (in, '3','0', 0, 3, log, write);
		break;
	case 49:
		if (log == 2){cout << "Store Accumulator Direct\nThis instruction when executed copies the contents of the accumulator into the pointed memory location. Accumulator contents are not destroyed.\n";}
		genScript (in, '3','2', 2, 3, log, write);
		break;
	case 50:
		if (log == 2){cout << "Set Carry\nWhen executed it sets the carry flag to 1. No other flags are affected.\n";}
		genScript (in, '3','7', 0, 3, log, write);
		break;
	case 51:
		if (log == 2){cout << "Subtract Register or memory from Accumulator\nMemory or register contents are subtracted from accumulator and the contents of source are unaltered. All flags are modified to reflect result of subtraction. CY flag is complemented after subtraction.\n";		}
		for (int chk=0; chk <= 7; chk++){
		if (in.at(4) == registers[chk] && in.at(3) == 32 && in.at (5) == 32){
		genScript (in, '9',addop[chk], 0, 5, log, write);
		option = true;
		break;
			} 
		}
	if (option == false) {
			cout << "\nInvalid Variant of Instruction.\nCannot Generate MonkeyScript85.\n";
		}
		break;
	case 52:
		if (log == 2){cout << "Subtract Immediate from Accumumlator\nIt uses the immediate addressing mode. The first byte gives opcode and second byte gives immediate data. The immediate data is subtracted from the contents of accumulator and the result is stored in accumulator. All flags are modified according to the result.\nThe subtraction is a 2's complement subtraction and the significant of result is same as that for the SUB instruction.\n";}
		genScript (in, 'D','E', 1, 3, log, write);
		break;
	case 53:
		if (log == 2){cout << "Logical Exclusive-OR with Accumulator\nThis is a one-byte instruction. It makes EX-Oring the operand contents with Accumulator.\n";}
		for (int chk=0; chk <= 7; chk++){
		if (in.at(4) == registers[chk] && in.at(3) == 32 && in.at (5) == 32){
		genScript (in, 'A',adcop[chk], 0, 5, log, write);
		option = true;
		break;
			} 
		}
	if (option == false) {
			cout << "\nInvalid Variant of Instruction.\nCannot Generate MonkeyScript85.\n";
		}
		break;
	case 54:
		if (log == 2){cout << "Logical XOR-Immediate with Accummulator\nThis is a 2-byte instruction using immediate addressing mode. The second byte which is immediate data is XORed with accumulator contents and result is stored in accumulator itself.\n";}
		genScript (in, 'E','E', 1, 3, log, write);
		break;
	}
}
void info4LI (string in, int place, int log, bool write){
	if (log == 2){cout << "Instruction Name: ";}
	bool option = false;
	switch (place){
		case 0:
			if (log == 2){cout << "Unconditional Call\nOn execution the address of the instruction following CALL is stored in stack. It decrements SP by two. It then jumps unconditionally to the subroutine address. This instruction is accompanied by a return type instruction at the end of subroutine.\n";}
			genScript (in, 'C','D', 2, 4, log, write);
			break;
		case 1:
			if (log == 2){cout << "Load Accumulator Indirect\nOne of the operands is implicit and is accumulator. The other operand is a register pair. It is designated in instruction itself. The contents of the designated register pair point to a memory location. This instruction copies the contents of that memory location into the accumulator. The contents of either the register pair or the memory location are not altered.\n";}
			for (int chk=0; chk <= 1; chk++){
		if (in.at(5) == regPair[chk] && in.at(4) == 32 && in.at (6) == 32){
		genScript (in, dadop[chk],'A', 0, 6, log, write);
		option = true;
		break;
			} 
		}
		if (option == false) {
			cout << "\nInvalid Variant of Instruction.\nCannot Generate MonkeyScript85.\n";
		}
			break;
		case 2:
			if (log == 2){cout << "Load H and L Register Direct\nOn execution the contents of memory location pointed by the specified address are copied into L register. The contents of the memory location next to specified location is copied into H register: Contents of these memory locations are not altered.\n";}
			genScript (in, '2','A', 2, 4, log, write);
			break;
		case 3:
			if (log == 2){cout << "Load Program Counter with H/L Register Pair Contents\nIt copies contents of HL pair into PC. The result is equivalent is to 1-byte unconditional jump with address stored in HL pair.\n";}
			genScript (in, 'E','9', 0, 4, log, write);
			break;
		case 4:
			if (log == 2){cout << "Push Register Pair on Stack\nThe contents of the register pair specified in the operand are copied into the stack in the following sequence:\na) The stack pointer is decremented and the contents of higher order register in pair (such as B in BC pair, D in DE pair) are copied on stack.\nb) The stack pointer is decremented again and contents of lower order register are copied on the stack. No flags are modified Contents of register pair are unchanged.\n";}
			for (int chk=0; chk <= 2; chk++){
		if (in.at(5) == regPair[chk] && in.at(4) == 32 && in.at (6) == 32){
		genScript (in, popop[chk],'5', 0, 5, log, write);
		option = true;
		break;
			} 
		}
		if (in.substr(5,3) == "PSW" && in.at(4) == 32 && in.at (8) == 32){
			genScript (in, 'F', '1', 0, 6, log, write);
		} else if (option == false) {
			cout << "\nInvalid Variant of Instruction.\nCannot Generate MonkeyScript85.\n";
		}
			break;
		case 5:
			if (log == 2){cout << "Store H/L Register Direct\nThe contents of the register pair specified in the operand are copied intothe stack in the following sequence.\na) The stack pointer is decremented and the contents of higher order register in pair (such as B in BC pair, D in DE pair) are copied on stack.\nb) The stack pointer is decremented again and contents of lower order register are copied on the stack. No flags are modified Contents of register pair are unchanged.\n";}
			genScript (in, '2','2', 2, 4, log, write);
			break;
		case 6:
			if (log == 2){cout << "Copy H/L Register to Stack Pointer\nThis is a single byte instruction which copies contents of L register into lower byte of SP and contents of H register into higher byte of SP. The contents of H and L registers are unaffected.\n";}
			genScript (in, 'F','9', 0, 4, log, write);
			break;
		case 7:
			if (log == 2){cout << "Store Accumulator Indirect\nThe contents of the designated register pair point to a memory location. This instruction copies the contents of the accumulator into the memory location pointed by register pair. The contents of either register pair of the accumulator are not altered.\n";}
			for (int chk=0; chk <= 1; chk++){
		if (in.at(5) == regPair[chk] && in.at(4) == 32 && in.at (6) == 32){
		genScript (in, dadop[chk],'2', 0, 6, log, write);
		option = true;
		break;
			} 
		}
		if (option == false) {
			cout << "\nInvalid Variant of Instruction.\nCannot Generate MonkeyScript85.\n";
		}
			break;
		case 8:
			if (log == 2){cout << "Exchange H/L Register Pair with D/E Register Pair\nOn execution of this instruction contents of H register are exchanged with contents of D register and contents of L register are exchanged with contents of B register.\n";}
			genScript (in, 'E','B', 0, 4, log, write);
			break;
	}
}
