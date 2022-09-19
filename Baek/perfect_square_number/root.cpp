#include <iostream>

int root(unsigned int &value, bool NM){
	 //NM = 0 -> M
	 //NM = 1 -> N
	
	if (value == 0){
		return 0;
	}
	else if (value == 10000){
		return 100;
	}
	else if (value < 100){
		int i = 9;
		for(; i >= 0; i--){
			if(value >= i*i){
				value -= i*i;
				break;
			}
		}
		/*if M's i has demical*/
		if(NM == 0 && value != 0)
			i++;
		return i;
	}
	else {	// 100 < value < 10000
		unsigned int tmp = value/100;
		int i = 9;
		for(; i >= 0; i--){
			if(tmp>= i*i){
				break;
			}
		}
		i *= 10;
		value -= i*i;
		int a = i * 2;
		if(value == 0)
			return i;
		int j = 9;
		for(; j >= 0; j--){
			if(value >= (a + j) * j){
				value -= (a + j) * j;
				break;
			}
		}
		if(NM == 0 && value != 0)
			j++;
		return (i + j);
	}
}
