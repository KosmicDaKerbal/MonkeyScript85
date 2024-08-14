# MonkeyScript85
A Simple Code Translator made in C++ that translates 8085 Assembly code into a human-understandable "MonkeyScript", primarily designed to be used for the 8085 Programming Kit.

# Usage
Simply Download the .exe file from the releases tab, and open it (you may get a smartscreen warning, but just run anyways). You will see a Monkey Logo and a pseudo terminal is opened, called MonkeyScript85 Terminal.<br><br>
To view the list of all commands, type HELP.<br>
Note: Only Block letter commands are accepted by the terminal, it is by design.
<br>
The MonkeyScript85 Terminal has a catalog of (almost) every single 8085 Instruction and its variant.<br>
To get the MonkeyScript for an 8085 Instruction, simply type in the instruction in the pseudoterminal. For example: LXI B, 5356<br><br>
The Output would be a small description of the instruction and its MonkeyScript.
<br><br>
To Convert Batch of Instructions:
<br>
- Create a file and write down the assembly instructions with one newline gap in between each instruction.<br>
- Make sure that this file is in the same directory as the .exe file.<br>
- Type CONVERT in the pseudo terminal, and it will ask for the input file. Enter the file name with the extension.<br>
- The terminal will then prompt the start address of the code. This specifies at what memory location the code starts.<br>
- The Code then produces an output file which contains human-readable instructions to program the 8085 Programming Kit.

# Troubleshooting
As of v1.0, The output file does not show any errors in the assembly input file. However, the pseudo terminal shows a verbose log of all the parsed instructions in the input file. If there are any errors detected by the pseudoterminal parser, the output script is incomplete and will lead to problematic code while programming the kit.

---
<br>
<h3>Project made in Dev C++ | compiled with MSVC | Compressed with upx</h3><br>
This was a fun project to make, it makes a lot of use for string manipulation and command parsing. It wasn't the most efficient or fastest implementation to a method, but I am happy with what I have created.
