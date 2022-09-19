#include <iostream>
#include <vector>
#include <numeric>
#include "root.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::accumulate;

int main(){
	int N, M;
	int rootN = 0, rootM = 0;
	bool Comparison_key = false;	/*N��M�ȏ�ł��邱�Ƃ̊m�F*/

	while (!Comparison_key){		/*N��M���Ⴉ������J��Ԃ��B*/
		N = 10001, M = 10001;		/*���͂��ĂȂ���ԂŎ��ɐi�߂��邱�Ƃ�����邽��*/
		bool Enter_key = false;		/*���͂��ꂽ�l��10,000�ȉ��̎��R�����̊m�F*/

		cout << "Please Enter M&N.\n0 <= M&N <= 10,000, M <=N" << endl;
		while (!Enter_key) {
			cout << "M : ";
			cin >> M;
			if(M <= 10000)			/*unsigned�ł��邽�߁AM��0��菬�����S�z�͂Ȃ��A10,000�ȉ��ł��邱�Ƃ����m�F�B*/
				Enter_key = true;
			else
				cout << "Please Enter M value of 10,000 or less" << endl;
		}
		Enter_key = false;
		while (!Enter_key) {
			cout << "N : ";
			cin >> N;
			if(N <= 10000)
				Enter_key = true;
			else
				cout << "Please Enter N value of 10,000 or less" << endl;
		}
		if (M <= N)
			Comparison_key = true;
		else
			cout << "M > N.\nPlease Enter value M <= N" << endl;
	}
	rootM = root(M, 0);				/*M�̕�������M�������_�������Ă����1�𑫂������R���ŕ\��*/
	rootN = root(N, 1);				/*N�̕�������N�������_�������Ă���΁A�����_�͎̂ĂĂ��玩�R���ŕ\��*/
	/** �����ŁAM��N�̕������Ŏ��R���̕������������ArootM�������_�����Ƃ�rootM > rootN�ɂȂ�B**/

	//cout << "rootM : " << rootM << "\nrootN : " << rootN << endl;
	int x = rootM;
	//cout << "x : " << x << endl;
	if(x > rootN){					/*x > rootN => rootM > rootN�ł��邽�߁ArootM�ȏ�rootN�ȉ��̎��R���͑��݂��Ȃ��B*/
		cout << "-1" << endl;
		return 0;
	}

	vector<int> x_list;
	for (;x <= rootN; x++){
		x_list.push_back(x*x);
	}

	/*Output */
	if(!x_list.empty()){
		if(*x_list.begin() != 0)
			cout << "Min : " << *x_list.begin()  << endl;
		else
			cout << "Min : " << *x_list.begin() + 1 << endl;
		cout << "Sum : " << accumulate(x_list.begin(), x_list.end(), 0) << endl;
		return 0;
	}
	else{
		cout << "-1" << endl;
		return 0;
	}
}
