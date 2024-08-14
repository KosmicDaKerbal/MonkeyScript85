#include <iostream>
#include <string> 
using namespace std;
void block (char type, int times){
	for (times; times >= 1; times--){
	std::cout << type;
}
}
void monkey (){
cout << "                                                           \n                       ";
block (-78, 10);
cout << "\n                     ";
block (-78, 14);
cout <<"\n                   ";
block (-78, 18);
cout <<"\n                 ";
block (-78, 22);
cout << "\n                 ";
block (-78, 4);
block (-79, 6);
block (-78, 2);
block (-79, 6);
block (-78, 4);
cout << "\n              ";
block (-80, 4);
block (-78, 2);
block (-79, 16);
block (-78, 2);
block (-80, 4);
cout << "\n              ";
block (-80, 4);
block (-78, 2);
block (-79, 2);
cout << "  ";
block (-37, 1);
block (-79, 6);
cout << "  ";
block (-37, 1);
block (-79, 2);
block (-78, 2);
block (-80, 4);
cout << "\n                ";
block (-80, 2);
block (-78, 2);
block (-79, 2);
block (-37, 3);
block (-79, 6);
block (-37, 3);
block (-79, 2);
block (-78, 2);
block (-80, 2);
cout << "\n                  ";
block (-78, 2);
block (-79, 16);
block (-78, 2);
cout << "\n                   ";
block (-78, 2);
block (-79, 14);
block (-78, 2);
cout << "\n                     ";
block (-78, 4);
block (-79, 6);
block (-78, 4);
cout << "\n                         ";
block (-78, 6);
cout << "        ";
block (-80, 2);
cout << "\n                       ";
block (-78, 10);
cout << "      ";
block (-78, 2);
cout << "\n                       ";
block (-78, 10);
cout << "    ";
block (-78, 4);
cout << "\n                     ";
block (-78, 18);
cout << "\n                     ";
block (-78, 4);
block (-79, 2);
block (-78, 2);
block (-79, 2);
block (-78, 4);
}
