#include <iostream>

#include <vector>

using namespace std;


class Graf {
	int N = 0;
	int k;
	int br;
	vector<int> cvor;
	vector<int> edge;
	vector<int> indices;

public:
	void init(int b = 0) {
		N = b; //kolko ima elem
		k = 1; //pomeraj 
		br = b;
		for (int i = 0; i < b; i++) cvor.push_back(i + 1);
		indices.assign(b + 1, -1);
		indices[b] = 0;
	}
	friend void addCvor(Graf* g) {
		if (g->N == 0) {
			cout << "Napravite graf!" << endl;
			return;

		}
		g->br++;
		g->N++;
		g->cvor.push_back(g->br);
		g->indices[g->N - 1] = -1;
		g->indices.emplace_back(g->edge.size());
	}
	friend void deleteCvor(int a, Graf* g) {
		if (g->N == 0) {
			cout << "Napravite graf!" << endl;
			return;

		}
		int c = 0;
		for (int i = 0; i < g->cvor.size(); i++) {
			if (g->cvor[i] == a) c++;
		}
		if (c == 0) {
			std::cout << "Ovaj cvor vec ne postoji!" << endl;
			return;
		}
		if (g->indices[a - g->k] == -1) {
			g->indices.erase(g->indices.begin() + a - g->k);
			for (int i = 0; i < g->cvor.size(); i++) {
				if (g->cvor[i] == a) {
					g->cvor.erase(g->cvor.begin() + i);
					break;
				}
			}
		}
		else {
			int c = g->indices[a - 1];
			int d = g->indices[a];
			int i = a;
			while (d == -1) {
				d = g->indices[i++];
			}
			g->edge.erase(g->edge.begin() + c, g->edge.begin() + d);
			g->indices[g->N] = g->indices[g->N] - (d - c);
			for (int j = a - g->k + 1; j < g->indices.size() - 1; j++) if (g->indices[j] != -1) g->indices[j] -= (d - c);
			g->indices.erase(g->indices.begin() + a - 1);
			g->N--; // u indec ima jedan manje el
			//trazi sve ostale cvorove u edgu
			for (int i = 0; i < g->edge.size(); i++) {
				if (g->edge[i] == a) {
					g->edge.erase(g->edge.begin() + i);
					int j = 0;
					for (j; j < g->indices.size(); j++) {
						if (i < j) break;
					}
					for (int l = j; l < g->indices.size(); l++)if (g->indices[l] != -1) g->indices[l]--;
					i--;
				}
			}
			for (int i = 0; i < g->cvor.size(); i++) {
				if (g->cvor[i] == a) {
					g->cvor.erase(g->cvor.begin() + i);
					break;
				}
			}
		}
		g->k++;
	}

	friend void addGrana(int a, int b, Graf* g) {
		if (g->N == 0) {
			cout << "Napravite graf!" << endl;
			return;

		}
		//dal cvorovi postoje 
		int c = 0;
		for (int i = 0; i < g->cvor.size(); i++) {
			if (g->cvor[i] == a) c++;
		}
		if (c == 0) {
			std::cout << "Prvi zadati cvor ne postoji" << endl;
			return;

		}
		c = 0;
		for (int i = 0; i < g->cvor.size(); i++) {
			if (g->cvor[i] == b) c++;
		}
		if (c == 0) {
			std::cout << "Drugi zadati cvor ne postoji" << endl;
			return;

		}
		for (int i = g->indices[a - g->k]; i < g->indices[a]; i++) {
			if (g->edge[i] == b) {
				std::cout << "Ova grana vec postoji" << endl;
				return;
			}
		}

		if (a != b && a <= g->N && b <= g->N && a > 0 && b > 0) {
			if (g->edge.empty() == true) {
				g->edge.assign(2, 0);
				if (a < b) {
					g->edge[0] = b;
					g->edge[1] = a;
					g->indices[a - 1] = 0;
					g->indices[b - 1] = 1;

				}
				else {
					g->edge[0] = a;
					g->edge[1] = b;
					g->indices[b - 1] = 0;
					g->indices[a - 1] = 1;
				}
				g->indices[g->N] = 2;
			}
			else {
				if (a == 1) {
					g->edge.emplace(g->edge.begin(), b);
					g->indices[0] = 0;
					for (int j = a; j < g->N + 1; j++) if (g->indices[j] != -1) g->indices[j]++;
				}
				else {
					int i = a;
					if (g->indices[a - g->k] == -1) {
						while (g->indices[i - g->k + 1] == -1) i++;
						g->edge.insert(g->edge.begin() + g->indices[i - g->k + 1], b);
						for (int j = a; j < g->N + 1; j++) if (g->indices[j] != -1) g->indices[j]++;
						g->indices[a - g->k] = g->indices[i - g->k + 1] - 1;
					}
					else { //vec postoji
						int c = g->indices[a - g->k];
						g->edge.insert(g->edge.begin() + c, b);
						for (int j = a; j < g->N + 1; j++) if (g->indices[j] != -1) g->indices[j]++;
					}
				}
				if (b == 1) {
					g->edge.emplace(g->edge.begin(), a);
					for (int j = b; j < g->N + 1; j++) if (g->indices[j] != -1) g->indices[j]++;
					g->indices[0] = 0;
				}
				else {
					int i = b;
					if (g->indices[b - g->k] == -1) {
						while (g->indices[i - g->k + 1] == -1) ++i;
						g->edge.insert(g->edge.begin() + g->indices[i - g->k + 1], a);
						for (int j = b; j < g->N + 1; j++) if (g->indices[j] != -1) g->indices[j]++;
						g->indices[b - g->k] = g->indices[i - g->k + 1] - 1;
					}
					else { //vec postoji
						int c = g->indices[b - g->k];
						g->edge.insert(g->edge.begin() + c, a);
						for (int j = b; j < g->N + 1; j++) if (g->indices[j] != -1) g->indices[j]++;
					}

				}

			}
		}
		else {
			if (a == b) std::cout << "Nemoguce" << endl;
			else std::cout << "Ovi cvorovi ne postoje" << endl;
		}
	}


	friend void deleteGrana(int a, int b, Graf* g) {
		if (g->N == 0) {
			cout << "Napravite graf!" << endl;
			return;

		}
		int c = 0; //provera dal Grana postoji
		for (int i = g->indices[a - g->k]; i < g->edge.size(); i++) {
			if (g->edge[i] == b) c++;
		}
		if (c == 0) {
			std::cout << "Ova grana ne postji" << endl;
		}
		c = 0;
		for (int i = g->indices[a - g->k]; i < g->edge.size(); i++) {
			if (g->edge[i] == b) break;
			c++;
		}
		g->edge.erase(g->edge.begin() + g->indices[a - g->k] + c);
		for (int j = a - g->k + 1; j < g->N + 1; j++) if (g->indices[j] != -1) g->indices[j]--;
		c = 0;
		for (int i = g->indices[b - g->k]; i < g->edge.size(); i++) {
			if (g->edge[i] == a) break;
			c++;
		}
		g->edge.erase(g->edge.begin() + g->indices[b - g->k] + c);
		for (int j = b - g->k + 1; j < g->N + 1; j++) if (g->indices[j] != -1) g->indices[j]--;


	}

	friend void ispis(Graf* g) {
		if (g->N == 0) {
			cout << "Napravite graf!" << endl;
			return;

		}
		std::cout << "Egde niz: ";
		int l = 0;
		for (int i = 0; i < g->edge.size(); i++) {
			while (g->indices[l + 1] == -1) l++;
			if (i == g->indices[l + 1]) {
				cout << " ";
				l++;
			}
			std::cout << g->edge[i];

		}
		std::cout << std::endl;
		std::cout << "Indices niz: ";
		for (int i = 0; i < g->indices.size() - 1; i++) {
			if (g->indices[i] == -1) std::cout << g->indices[g->N] + 1 << " ";
			else {
				std::cout << g->indices[i] << " ";
			}
		}
		std::cout << g->indices[g->indices.size() - 1] + 1;
		std::cout << std::endl;
	}
	friend void deleteGraf(Graf* g) {
		if (g->N == 0) {
			cout << "Napravite graf!" << endl;
			return;

		}
		g->edge.clear();
		g->indices.clear();
		g->cvor.clear();
	}


};



int main() {
	Graf g;
	while (1) {
		cout << "Unesite redni broj f-je koju zelite da izvrsite?" << endl << "1.Kreirati graf" << endl << "2.Dodati cvor" << endl << "3.Dodati granu" << endl << "4.Uklonite cvor" << endl << "5.Uklonite granu" << endl << "6.Ispisite graf" << endl << "7.Izbrisite graf" << endl << "8.Prekinite program" << endl;
		int i;
		cin >> i;
		switch (i) {
		case 1: {
			cout << "Unesite broj cvorova" << endl;
			int n;
			cin >> n;
			g.init(n);
			break;
		}
		case 2: {
			addCvor(&g);
			break;
		}
		case 3: {
			cout << "Unesite dva cvora koja zelite da budu povezana, cvorovi pocinju od broja 1" << endl;
			int a, b;
			cin >> a >> b;
			addGrana(a, b, &g);
			break;
		}
		case 4: {
			cout << "Unesite broj cvora koji zelite da bude uklonjen, cvorovi pocinju od broja 1" << endl;
			int a;
			cin >> a;
			deleteCvor(a, &g);
			break;
		}
		case 5: {
			cout << "Unesite dva cvore izmecu koji ne zelite da postoji grana, cvorovi pocinju od broja 1" << endl;
			int a, b;
			cin >> a >> b;
			deleteGrana(a, b, &g);
			break;
		}
		case 6: {
			ispis(&g);
			break;
		}
		case 7: {
			deleteGraf(&g);
			break;
		}
		case 8: {
			exit(1);
		}
		}
	}
	return 0;
}
