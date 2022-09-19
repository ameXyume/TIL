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
	bool Comparison_key = false;	/*NがM以上であることの確認*/

	while (!Comparison_key){		/*NがMより低かったら繰り返す。*/
		N = 10001, M = 10001;		/*入力してない状態で次に進められることを避けるため*/
		bool Enter_key = false;		/*入力された値が10,000以下の自然数かの確認*/

		cout << "Please Enter M&N.\n0 <= M&N <= 10,000, M <=N" << endl;
		while (!Enter_key) {
			cout << "M : ";
			cin >> M;
			if(M <= 10000)			/*unsignedであるため、Mが0より小さい心配はなく、10,000以下であることだけ確認。*/
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
	rootM = root(M, 0);				/*Mの平方根でMが小数点を持っていれば1を足した自然数で表現*/
	rootN = root(N, 1);				/*Nの平方根でNが小数点を持っていれば、小数点は捨ててから自然数で表現*/
	/** ここで、MとNの平方根で自然数の部分が等しく、rootMが小数点を持つときrootM > rootNになる。**/

	//cout << "rootM : " << rootM << "\nrootN : " << rootN << endl;
	int x = rootM;
	//cout << "x : " << x << endl;
	if(x > rootN){					/*x > rootN => rootM > rootNであるため、rootM以上rootN以下の自然数は存在しない。*/
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
