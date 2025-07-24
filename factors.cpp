#include <iostream>
using namespace std;

//all prime factors

//print all occurence
//remember the rule to find out all prime factors of any number
vector<int>AllPrimeFactorsWithOccurrence;
void allPrimeFactors(int n){
	//since 2 is the only prime number so separately check if that is a factor or not
	if(n%2==0){
		while(n%2==0){
			AllPrimeFactorsWithOccurrence.push_back(2);
			n/=2;
		}
	}
	//all other prime numbers that would could be factors are odd numbers so we start from 3 and check upto sqrt(n)

	for (int i=3;i*i<=n;i+=2){
		while(n%i==0){
			AllPrimeFactorsWithOccurrence.push_back(i);
			n/=i;
		}

	}
	//after all if n still greater than 1 that means n is now a prime number
	if(n>1){
		AllPrimeFactorsWithOccurrence.push_back(n);
	}
	return ;


}

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;
    cout << "Prime factors: ";
    primeFactors(n);
    return 0;
}

//print only once
#include <iostream>
using namespace std;

void printDistinctPrimeFactors(int n) {
    // Check divisibility by 2
    if (n % 2 == 0) {
        cout << 2 << " ";
        while (n % 2 == 0)
            n /= 2;
    }

    // Check odd numbers from 3 to sqrt(n)
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            cout << i << " ";
            while (n % i == 0)
                n /= i;
        }
    }

    // If n is still > 1, it is a prime factor itself
    if (n > 1)
        cout << n;

    cout << endl;
}




int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;
    cout << "Distinct prime factors: ";
    printDistinctPrimeFactors(n);
    return 0;
}

//all factors

#include<bits/stdc++.h>
using namespace std;
vectoraa<int>&temp;

void printAllFactors(int n){


	for (int i=1;i*i<=n;i++){
		if(n%i==0){
			temp.push_back(i);
			if(n/i!=i)temp.push_back(n/i);

		}
	}
	for (auto it: temp){
		cout<<it<<" ";
	}

}



int main(){

}



prime palindrome  
we do not have any even size prime palindrome except 11 
bcz( every even length palindrome is divisible by 11)
acc to 11 's rule of divisibility a number of digit n is divided by 11 when (sum of even index digit-sum of odd index digit)%11=0 