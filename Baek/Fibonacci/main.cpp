#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::printf;

int main(){
	bool Enter_check = false;
	unsigned int num = 91;
	vector<unsigned long int>Fn = {0, 1};
	cout << "Enter the number less than 90" << endl;
	while (!Enter_check){
		cout << "n : ";
		cin >> num;
		if (num <= 90)
			Enter_check = true;
		else
			cout << "Please Enter the number of 90 or less" << endl;
	}

	printf("F(%d) : ", num);

	if(num == 0) {
		cout << 0 << endl;
		return 0;
	}
	else if (num == 1){
		cout << 1 << endl;
		return 0;
	}

	for(unsigned int i = 2; i <= num; i++){
		Fn.push_back(*(Fn.end() - 2) + *(Fn.end() - 1));
		Fn.erase(Fn.begin());
	}
	cout << *(Fn.end()-1) << endl;
}
