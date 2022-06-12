#include <iostream>
#include <time.h>
#include <windows.h>
using namespace std;

void sortowanieBombelkowe(int *tab, int n) {//dajemy *tab aby dzialac na oryginalnej tablicy 
	int pom;
	for (int j = 0; j < n; j++) {//wykonuje n razy bo tyle maksymalnie trzeba uruchomic petle; po pierwszym obrocie najmniejsza liczba jest napewno na swoim miejscu itd.
		for (int i = n - 1; i > 0; i--) {//ide od ostatniego elementu do drugiego elementu bo pierwszy element nie mam z czym zamienic
			if (tab[i] < tab[i - 1]) {
				pom = tab[i];
				tab[i] = tab[i - 1];
				tab[i - 1] = pom;
			}
		}
	}
}

void wypiszLiczby(int *tablica, int n) {
	for (int i = 0; i < n; i++) {
		cout << tablica[i] << " ";
	}
	cout << endl<<endl;
}

void quicksort(int* tab, int p, int q) {
	//p to pierwszy element i q to ostatni element ciagu który ustawiamy
	//27 54 10 86 94 21 39 95 24

	int pom, n, granica;
	granica = p;

	//jakbym zrobi³ nizej pêtle, ¿e i=q zamiast u¿ywaæ q to wtedy bym tych zmiennych poni¿ej nie musia³ robiæ
	int stare_p = p;
	int stare_q = q;
	n = (q - p)+1;//tyle mamy elemnetow to posortowania

	while (p < q) {
		for (q; q > p; q--) {
			if (tab[q] < tab[granica]) {
				pom = tab[q];
				tab[q] = tab[granica];
				tab[granica] = pom;
				granica = q;
				break;
			}
		}
		for (p; p<q; p++) {
			if (tab[p] > tab[granica]) {
				pom = tab[p];
				tab[p] = tab[granica];
				tab[granica] = pom;
				granica = p;
				break;
			}
		}
	}
	if (n <= 2) return;//jeœli sortowaliœmy mniej ni¿ 2 elementy to napewno ju¿ s¹ u³o¿one

	//cout << "Wywoluje funkcje ponizej z parametrami:" << "P: " << stare_p << " Q: " << granica - 1 << " oraz z P: "<<granica+1<<" i Q:"<<stare_q<<endl;

	//teraz p = q i to jest nasza granica czyli nowe tablice do sortowanie to jest od zera do p i od p do koñca
	quicksort(tab, stare_p, granica - 1);
	quicksort(tab, granica + 1, stare_q);
}




//drugi sposób na quicksorta

int partition(int *tab, int p, int q) {
	//p to pierwszy element ktory sortujemy a q ostatni;
	int pivot, i, j;
	i = p;
	j = q;
	pivot = tab[p];
	while (i < j) {
		while (tab[i] <= pivot) {
			i++;
		}

		while (tab[j] > pivot) {
			j--;
		}
		if (i < j) {
			swap(tab[i], tab[j]);
		}
	}
	swap(tab[p], tab[j]);
	return j;
}

void quicksort2(int *tab, int p, int q) {

	if (p < q) {
		int granica;
		granica = partition(tab, p, q);
		quicksort2(tab, p, granica-1);
		quicksort2(tab, granica + 1, q);
	}

}

void swap(int &a, int &b) {//dzialamy na oryginalnych zmiennych
	int pom = b;
	b = a;
	a = pom;
}

int main() {
	//generowanie losowych liczb do posortowania
	int n;
	cout << "Ile losowych liczb chcesz wygenerowac?"<<endl;
	cin >> n;
	srand(time(NULL));
	int* tablica = new int[n];
	int* tablica2 = new int[n];
	int* tablica3 = new int[n];
	for (int i = 0; i < n; i++) {
		tablica[i] = rand() % 100000 + 1;
		tablica2[i] = tablica[i];
		tablica3[i] = tablica[i];
	}



	//cout << "WYGENEROWANE LICZBY:";
	//wypiszLiczby(tablica, n);


	clock_t start_1, start_2, start_3, stop_1, stop_2, stop_3;
	double czas_1, czas_2, czas_3;

	//sortowanie bombelkowe
	start_1 = clock();
	sortowanieBombelkowe(tablica, n);//przesy³amy do funckji tablice oraz ilosc elementow w tablicy (to dobra praktyka aby przeslac ilosc elementow w tablicy)
	stop_1 = clock();

	czas_1 = (double)(stop_1 - start_1) / CLOCKS_PER_SEC;

	//quicksort napisany przezemnie
	start_2 = clock();
	quicksort(tablica2, 0, n-1);
	stop_2 = clock();
	czas_2 = (double)(stop_2 - start_2) / CLOCKS_PER_SEC;


	//quicksort drugi sposob
	start_3 = clock();
	quicksort2(tablica3, 0, n-1);
	stop_3 = clock();
	czas_3 = (double)(stop_3 - start_3) / CLOCKS_PER_SEC;


	
	cout << "Czas sortowania bombelkowego: "<<czas_1<<endl;
	cout << "Czas quicksort (wlasny kod): " << czas_2<<endl;
	cout << "Czas quciksort (kod z internetu): " << czas_3<<endl;
	

	//cout << endl << "Posortowane liczby: " << endl;
	//wypiszLiczby(tablica, n);








	delete[] tablica;
	delete[] tablica2;
	delete[] tablica3;
	return 0;
}