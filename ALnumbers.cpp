/*
Code is solution for: "anti-Lychrel Numbers".
_______________________________________________________________________________
Anti-Lychrel Numbers

An anti-Lychrel number is a number that forms a palindrome through the
iterative process of repeatedly reversing its digits and adding the
resulting numbers. For example, 56 becomes palindromic after one iteration:
56+65=121. If the number doesn't become palindromic after 30 iterations, then
it is not an anti-Lychrel number.

Examples:
Input: 12
Output: true (12 + 21 = 33, a palindrome)

Input: 57
Output: true (57 + 75 = 132, 132 + 231 = 363, a palindrome)

Input: 10911
Output: false (10911 takes 55 iterations to reach a palindrome)

Write a program to check if the user input is an anti-Lychrel number or not.

Bonus: Print all the anti-Lychrell numbers in a given range. 
_______________________________________________________________________________

Input instructions.

For getting code work you should:

1) Enter int number and press SUBMIT for single mode research.

2) Or enter first number in the range, space - ' ' and last number in the range
and then SUBMIT for range mode research.
_______________________________________________________________________________

EXAMPLE #1:

For input:
1 10

You will get on the screen:

All anti-Lychrel numbers in the given range [1, 10] are:

[
10      9       8       7       6       5       4
3       2       1
].

Quantity of anti-Lychrel numbers: 10.

Time spend on calculations: 0.005 seconds.

That's all for now, run again.
_______________________________________________________________________________

EXAMPLE #2:

For input:

87

You will get on the screen:

You enter an anti-Lychrel number.

Time spend on calculations: 0.001 seconds.

That's all for now, run again.
_______________________________________________________________________________

Report me if you find any bugs.

Good luck!
*/
#include <iostream>
#include <vector>
#include <algorithm> 
#include <vector>
#include <string>
#include <time.h>

// 
template <typename T>
void pOL(T word){
	std::cout << word;
}
// 
template <typename T, typename... Args>
void pOL(T first, Args... args){
	std::cout << first;
	pOL(args...);
}

class storage{

    //
    private:
    //
	std::string modeHeader = "\nEnter number or range here: ";
    std::string incorrect = "\nThis input is incorrect.\n";
    std::string comeAgain = "\nThat's all for now, run again.\n";
    //
	std::string answer;

	// Main program need this containers and methods
	public:
	// true - for number, false - for range
	bool mode = true;
	// approved = true - correct input, false - incorrect input
	bool approved = true;
	//
	unsigned long long int number;
	//
	unsigned long long int rRange;

	// Method that show to user options of the program
	void openDialog(){
		pOL(modeHeader);
		// read mode from user
		std::getline (std::cin, answer);
	}
    
    // Method print corresponding message about "correct" or "incorrect" input
	void validateDialog(){
		int i = 0;
		int j = 0;
		//
		while ( answer[j] != '\0' ){
			// increment when find every space
			if ((int)answer[j]==32){
				mode=false;
				i++;
			}
			// more than 1 space
			if (i > 1) approved=false;
			//
			if (i == 0)
				if (((int)answer[j]>=48)
				    && ((int)answer[j]<=57))
					number = number*10+((int)answer[j]-48);
				else if ((int)answer[j]!=32) approved=false;
			//
			if (i == 1)
				if (((int)answer[j]>=48)
				    && ((int)answer[j]<=57))
					rRange = rRange*10+((int)answer[j]-48);
				else if ((int)answer[j]!=32) approved=false;
			// jump to next character
			j++;
		}
		// Immidiately send error message in case wrong input
		if (!approved) pOL(incorrect);
	}
	
	// Destructor simply send message to user asking run program again 
	~storage(){
		pOL(comeAgain);
	}
};

class numberResearcher : public storage
{
    //
    private:
    // messages represent as strings for number research dialogs
    std::string AL = "\nYou enter an anti-Lychrel number.\n";
    std::string notAL = "\nYou enter not anti-Lychrel number.\n";
    std::string timeNumberLimit = "\nResearch for given number produce time limit failure.";
	//
	unsigned long long int number;
    clock_t time_new;
    clock_t start_operate;
	bool time_n_failure = false;

	//
	protected:
	//
	std::string timeCalc = "\nTime spend on calculations: ";
	std::string timeSec = " seconds.\n";
	//
	std::vector<unsigned long long int> ALvec;
	//
	unsigned long long int reverse(unsigned long long int y){
		
		unsigned long long int sum = 0;
		
		while (y > 0){
			sum = sum*10 + y % 10;
			y /= 10;
		}
		return sum;
	}
	//
	bool checkPalindrome(unsigned long long int x){
		return x == reverse(x);
	}
	//
	bool iterations(unsigned long long int research){
			int count = 0;
			start_operate = clock();
			std::vector<unsigned long long int>::iterator alit;
			research += reverse(research);

			while ( count++ < 30 ){
					alit = find (ALvec.begin(), ALvec.end(), research);
					if ( checkPalindrome(research) || alit != ALvec.end() )
						return true;		
					else research += reverse(research);
						time_new = clock() - start_operate;
			
				time_new = clock() - start_operate;
				if ( time_new*1.0/CLOCKS_PER_SEC > 3 )
					time_n_failure = true;	
			}
			return false;
	}

	//
	public:
	//
	void setNumber(unsigned long long int x){
		number = x;
	}
	//
	void closeDialog(clock_t start_calc){
		//
		if (time_n_failure) pOL(timeNumberLimit);
		else 
			//
			if ( iterations(number) ) pOL(AL);
			else pOL(notAL);

		time_new = clock() - start_calc;
		pOL(timeCalc,time_new*1.0/CLOCKS_PER_SEC,timeSec);
	}
};

class rangeResearcher : public numberResearcher {
	
	private:
    std::string ALRange = "\nAll anti-Lychrel numbers in the given range [";
    std::string timeLimit = "\nResearch for given range produce time limit failure.";
    std::string ALCorre = "\n\nAll anti-Lychrel numbers in the corrected range [";
    std::string back = "] are:\n\n[\n";
    std::string notALRange = "\nNot a single anti-Lychrel number in the given range: ";
    std::string ALQun = "].\n\nQuantity of anti-Lychrel numbers: ";

	unsigned long long int lRange;
	unsigned long long int rRange;
    clock_t time_new;
    clock_t start_operate;
	bool time_failure = false;

	//
	void operate(unsigned long long int start, unsigned long long int end){
		
		int count;
		start_operate = clock();

		for (unsigned long long int next = end; ( next >= start && !time_failure ); next--){
			count = 0;

			if ( iterations(next) ) ALvec.push_back(next);
			
			time_new = clock() - start_operate;
			
			if ( time_new*1.0/CLOCKS_PER_SEC > 3 ){
				start = next+1;
				time_failure = true;	
			}
		}
	}

	public:
	//
	void setRange(unsigned long long int x, unsigned long long int y){
		lRange = x;
		rRange = y;
	}
	//
	void closeDialog(clock_t start_calc){
		int i = 0;
		//
		operate(lRange, rRange);
			
		if (time_failure)
			pOL(timeLimit, ALCorre, lRange, ", ", rRange, back);
		else pOL(ALRange, lRange, ", ", rRange, back);
			
		for (std::vector<unsigned long long int>::iterator
		     it = ALvec.begin(); it!=ALvec.end(); it++){
			pOL(*it, '\t');
			if(++i==7){
				pOL('\n');
				i=0;
			}
		}

		if (i) pOL('\n');
		pOL(ALQun, ALvec.size(), ".\n");

		time_new = clock() - start_calc;
		pOL(timeCalc,time_new*1.0/CLOCKS_PER_SEC,timeSec);
	}
};

int main() {

	clock_t calc_t;

	storage *entry = new storage;

	entry -> openDialog();

	entry -> validateDialog();

	if ( (entry -> approved) && (entry -> mode) )
	{
		numberResearcher *check = new numberResearcher;

		check -> setNumber(entry -> number);

		calc_t = clock();

		check -> closeDialog(calc_t);
	}

	if ( (entry -> approved) && !(entry -> mode) )
	{
		rangeResearcher *check = new rangeResearcher;

		check -> setRange(entry -> number, entry -> rRange);

		calc_t = clock();

		check -> closeDialog(calc_t);
	}

	delete entry;

    return 0;
}