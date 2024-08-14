#include "info.h"
int globlog = 2;
const string twoLetterInstructions [14] = {"CC", "CM", "CP", "CZ", "EI", "IN", "JC", "JM", "JP", "JZ", "RC", "RM", "RP", "RZ"};
const string threeLetterInstructions [55] = {"ACI", "ADC", "ADD", "ADI", "ANA", "ANI", "CMA", "CMC", "CMP", "CNC", "CNZ", "CPE", "CPI", "CPO", "DAA", "DAD", "DCR", "DCX", "HLT", "INR", "INX", "JMP", "JNC", "JNZ", "JPE", "JPO", "LDA", "LXI", "MOV", "MVI", "NOP", "ORA", "ORI", "OUT", "POP", "RAL", "RAR", "RET", "RIM", "RLC", "RNC", "RNZ", "RPE", "RPO", "RRC", "RST", "SBB", "SBI", "SIM", "STA", "STC", "SUB", "SUI", "XRA", "XRI"};
const string fourLetterInstructions [9] = {"CALL", "LDAX", "LHLD", "PCHL", "PUSH", "SHLD", "SPHL", "STAX", "XCHG"};
int found; bool info=0;
void parsecmds (string work, int loglevel, bool write){
	found = -1;
	info = 0;
	work.append("  ");
	for (int twLI = 0; twLI <=13; twLI++){
		if (twoLetterInstructions[twLI] == work.substr(0,2) && work.at(2) == 32){
			found = twLI;
			info = 1;
			break;
		}
	}
	if (found != -1) {
		if (loglevel == 2){
			cout << "Found 8085 Instruction: " << twoLetterInstructions[found]<< "\n";
		}
		info2LI (work, found, loglevel, write);
	found = -1;
	} else {
		for (int twLI = 0; twLI <=54; twLI++){
		if (threeLetterInstructions[twLI] == work.substr(0,3) && work.at(3) == 32){
			found = twLI;
			info = 1;
			break;
		}
	}
	}
	if (found != -1) {
	if (loglevel == 2){
	cout << "Found 8085 Instruction: "<< threeLetterInstructions[found]<< "\n";
	}
	info3LI (work, found, loglevel, write);
	found = -1;
	}
	else {
		for (int twLI = 0; twLI <=8; twLI++){
		if (fourLetterInstructions[twLI] == work.substr(0,4) && work.at(4) == 32){
			found = twLI;
			info = 1;
			break;
			}
		}
	}
	if (found != -1) {
	if (loglevel == 2){
	cout << "Found 8085 Instruction: "<< fourLetterInstructions[found]<< "\n";
	}
	info4LI (work, found, loglevel, write);
	found = -1;
	} else if (work == "HELLO  "){
	cout << "Hello There, my Fellow Monke! Have a banan :)";
	} else if (work == "DONATE  "){
	cout << "You can donate to my Banano Wallet at ban_137xmpo7eqis7oymw9ob9b5qparzqc799jxw8o3udzm3p6rrtgj83wczwo7a . Much Thanks!";
	} else if(work == "LOG  ") {
	int choice = globlog;
	cout << "Change Log Level to: ";
	cin >> choice;
	if (choice > 2 || choice < 0){
		cout << "Error: Please Choose a Valid Log level. Type HELP to see all options.";
	} else {
		globlog = choice;
	}
	}else if (work == "HELP  ") {
		cout << "List of All MonkeyScript85 Commands:\nThis Utility contains (almost) all Instructions for the Intel 8085 Microprocessor.\nType any Instruction, For Example: LXI B, 5235\nMonkeyScript85 Terminal will generate the proper MonkeyScript85.\n\nTerminal Utilities:\nHELLO - Check your Setup by using this command. It should give you a response on STDOUT.\nDONATE - Donate to my Banano Wallet if you'd like to support me.\nCONVERT - Convert an 8085 Assembly File into MonkeyScript85\nLOG - Set the Logging Level:\n\t0 => Output Nothing Except Errors\n\t1 => Output only Monkeyscript85 Translation and Errors\n\t2 => Output Everything\n\t(Default: 2, Current: "<<globlog<<")\nEXIT - Exit the MonkeyScript85 Terminal.";
	} else if (work != "EXIT  " && info == 0 && work != "  ") {
	cout <<"*monkey noises* what is "<< work << "??";
	}
}
