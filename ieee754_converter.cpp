/*
  Arian Molazem
  This program converts decimal numbers to IEEE754 16, 32 and 64 bits standard.   
*/

#include <iostream>
#include <conio.h>
#include <cmath>
#include <sstream>
using namespace std;

//-------------------------------------------------------------------
void line();                                     // Just for Appearance.
void menu();
//-------------------------------------------------------------------
string decimal_to_binary_int(int number);        // Main Functions.

string decimal_to_binary_fraction(double number, int exp, int bit);  

string make_exponent(int exp, int bit);
//-------------------------------------------------------------------

int main()
{
//-------------------------------------------------------------------
	double number;                               // Main variables.
	string exponent_5bit, exponent_8bit, exponent_11bit;
	char mantissa_10bit[10], mantissa_23bit[23], mantissa_52bit[52];
	char sign;
//-------------------------------------------------------------------		
	bool exit_prog = false;                      // Side variables.
	bool flag;
	int num_menu, exp, fraction_length;
	string int_binary, fraction_binary, mantissa;
//-------------------------------------------------------------------	
	while(true)                                  // Fill mantissa arrays with zeroes.
	{
		for(int i = 0; i < 10; i++)             
			mantissa_10bit[i] = '0';
	    for(int i = 0; i < 23; i++)
			mantissa_23bit[i] = '0';
		for(int i = 0; i < 52; i++)
			mantissa_52bit[i] = '0';
//-------------------------------------------------------------------		
		system("cls");                           // Menu
		menu();
		line();
		cout << "                ( IEEE754 )                   \n"
				"\n Decimal to Half-Precision   (16 bits)  [1] \n"
				"\n Decimal to Single-Precision (32 bits)  [2] \n"
				"\n Decimal to Double-Precision (64 bits)  [3] \n"
				"\n Exit                                   [0] \n";
		line();
		
		flag = true;
		while(flag)
		{
			flag = false;

			while(true)                          // Getting the menu number.
			{
				cout << "\n num: ";              
				cin >> num_menu;
				if(cin.fail())                   // Checking the validity of input.
				{
					cin.clear();
					cin.ignore();
					cout << " [Enter a number] \n";
				} else
					break;
			}			 
			
			switch(num_menu)                             
			{  				
				case 1: break;  	
				case 2: break;    				  
				case 3: break;                   
				case 0: exit_prog = true; break;
				default: flag = true;
				cout << " [Just enter one of the menu numbers] \n";
			}
		}
		
		if(exit_prog)                            
			break;
		system("cls");
		
		while(true)                              // Getting the number.
		{
			cout << "\n Enter the number: "; cin >> number;
			if(cin.fail())                       // Checking the validity of input.
			{
				cin.clear();
				cin.ignore();
				cout << " [Enter a number] \n";
			} else
				break;
		}
		
		if(number < 0)                           // Setting the sign and make number positive.
		{
			sign = '1';
			number *= -1;
		}
		else
			sign = '0';
		
		int int_part = number;                   // Separating the two sides of fixed point.
		double fraction_part = number - int_part;
		
		line();
		cout << " Sign: " << sign;
		line();
		cout << " Int_part = " << int_part << 
				"\n Fraction_part = " << fraction_part;
		
		int_binary = decimal_to_binary_int(int_part);
		line();
		cout << " " << int_part << " = " << int_binary;
		
		int_binary.erase(0, 1);
		exp = int_binary.length();               // The power of 2.
//-------------------------------------------------------------------
		cout << "\n " << fraction_part << " = ";
		switch(num_menu)                         // Converting Fraction to binary and Making exponent.
		{
			case 1:                              // 16 bit
			{
				fraction_binary = decimal_to_binary_fraction(fraction_part, exp, 16);
				exponent_5bit = make_exponent(exp, 16);
			}break;
			
			case 2:                              // 32 bit
			{
				fraction_binary = decimal_to_binary_fraction(fraction_part, exp, 32);
				exponent_8bit = make_exponent(exp, 32);
			}; break;
			
			case 3:                              // 64 bit
			{
				fraction_binary = decimal_to_binary_fraction(fraction_part, exp, 64);
				exponent_11bit = make_exponent(exp, 64);
			}; break;
		}
		
		fraction_length = fraction_binary.length();
//-------------------------------------------------------------------		
		// making the temp mantissa which may not be 52 bits.
		mantissa = int_binary + fraction_binary; 		
		
		// Placing temp mantissa into the main mantissa with 52 bits which is full of zeroes.
		line();
		cout << " Mantissa: ";
		switch(num_menu)
		{
			case 1:                              // 16 bit
			for(int i = 0; i < exp + fraction_length; i++)
			{ 
				mantissa_10bit[i] = mantissa[i];
				cout << mantissa_10bit[i];
			}; break;
			
			case 2:                              // 32 bit
			for(int i = 0; i < exp + fraction_length; i++)
			{ 
				mantissa_23bit[i] = mantissa[i];
				cout << mantissa_23bit[i];
			}; break;
			
			case 3:                              // 64 bit
			for(int i = 0; i < exp + fraction_length; i++)
			{ 
				mantissa_52bit[i] = mantissa[i];
				cout << mantissa_52bit[i];
			}; break;
		}
//------------------------------------------------------------------- 					
		line();                                  // Printing the final answer.
		cout << "\n Answer: " << sign << "|";
		switch(num_menu)
		{
			case 1:                              // 16 bit
			{
				cout << exponent_5bit << "|";
				for(int i = 0; i < 10; i++)
					cout << mantissa_10bit[i];
			}; break;
			
			case 2:                              // 32 bit
			{
				cout << exponent_8bit << "|";
				for(int i = 0; i < 23; i++)
					cout << mantissa_23bit[i];
			}; break;
			
			case 3:                              // 64 bit
			{
				cout << exponent_11bit << "|";
				for(int i = 0; i < 52; i++)
					cout << mantissa_52bit[i];
			}; break;
		}
		cout << endl;
//-------------------------------------------------------------------
		line();
		cout << " Press any key to go back to menu. ";
		getch();
	}
	system("cls");
	cout << "\n Have a nice day! \n";
	line();
	cout << " Press any key to exit ";
	getch();
	return 0;
}

string decimal_to_binary_int(int number)
{	
	long long sum = 0;
	int index = 0;
	int rem;
	
	while(number != 0)                           // Using dividing by 2 method.
	{
		rem = number % 2;
		number = number / 2;
		sum += rem * pow(10, index);
		index++;
	}
	
	stringstream a;                              // Converting int number to string.
	a << sum;
	string num;
	a >> num;
	return num;
}

string decimal_to_binary_fraction(double number, int exp, int bit)
{
	string fraction_binary;
	int fraction_length;
	 
	switch(bit)                                  // Knowing the max length of our binary string. 
	{
		case 16: fraction_length = 10 - exp; break;
		case 32: fraction_length = 23 - exp; break;
		case 64: fraction_length = 52 - exp; break; 
	}
	
	for(int i = 0; i < fraction_length; i++)     // Making the string of ones and zeroes.
	{
		number *= 2;                             // Using multiplying by 2 method.
		double temp = number;
		
		if(temp > 1)
		{
			fraction_binary += '1';
			number -= 1;                         // Removing 1 from the number for next round.
		}
		if(temp < 1)
		{
			fraction_binary += '0';
		}
		if(temp == 1)                            // This is the stop point of multiplying by 2.
		{
			fraction_binary += '1';
			break;
		}
	}
	cout << fraction_binary;
	return fraction_binary;
}

string make_exponent(int exp, int bit)
{
	string exponent;
	int bias, exp_bias;
	
	switch(bit)                                  // Getting the bias value.
	{
		case 16: bias = (pow(2, 5 - 1)) - 1; break;
		case 32: bias = (pow(2, 8 - 1)) - 1; break;	
		case 64: bias = (pow(2, 11 - 1)) - 1; break;	
	}
	
	exp_bias = bias + exp;                       // Getting the exp-biased.
	exponent = decimal_to_binary_int(exp_bias);  // Converting the exp-biased to binary.
	
	line();                                      // Printing all of the info.
	cout << " bias: (2^(exp_bits - 1)) - 1 = " << bias <<
		    "\n exp = " << exp <<
		    "\n exp_bias: " << bias << " + " << exp << " = " << exp_bias << 
		    "\n " << exp_bias << " = " << exponent <<
		    "\n Exponent = " << exponent;
	
	return exponent;
}

void line()
{
	cout << "\n ------------------------------------------\n";
}
void menu(){
	cout << "         _ __ ___   ___ _ __  _   _     \n"
			"        | '_ ` _ \\ / _ \\ '_ \\| | | | \n"
			"        | | | | | |  __/ | | | |_| |    \n"
			"        |_| |_| |_|\\___|_| |_|\\__,_|    ";
}

