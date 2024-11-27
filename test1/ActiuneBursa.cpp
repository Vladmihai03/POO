#include <iostream>
using namespace std;


class ActiuneBursa {

private:
	string denumire;
	int nrZile;
	float* valoriZilnice;
	const int idActiune;
	static string denumireBursa;

public:

	ActiuneBursa(): idActiune(0) {
		valoriZilnice = nullptr;
		nrZile = 0;
		denumire = "N/A";
	}

	ActiuneBursa(int idActiune, const  string& denumire): idActiune(idActiune) {
		this->denumire = denumire;
		nrZile = 1;
		this->valoriZilnice = new float[1];
		valoriZilnice[0] = 0;
	}

	int getNrZile() const {
		return nrZile;
	}

	float* getValoriZilnice() const {
		if (valoriZilnice == nullptr || nrZile == 0) {
			return nullptr;
		}

		float* copie = new float[nrZile];
		for (int i = 0;i < nrZile;i++) {
			copie[i] = valoriZilnice[i];
		}
		return copie;
	}

	void setValoriZilnice(float* nou, int n) {
		
		if (valoriZilnice != nullptr) {
			delete[] valoriZilnice;
		}

		nrZile = n;
		valoriZilnice = new float[nrZile];
		for (int i = 0;i < nrZile;i++) {
			valoriZilnice[i] = nou[i];
		}
	}

	ActiuneBursa(const ActiuneBursa& other) : idActiune(other.idActiune) {
		denumire = other.denumire;
		nrZile = other.nrZile;

		if (other.nrZile > 0 && other.valoriZilnice != nullptr) {
			valoriZilnice = new float[nrZile];
			for (int i = 0;i < nrZile;i++) {
				valoriZilnice[i] = other.valoriZilnice[i];
			}
		}
		else {
			valoriZilnice = nullptr;
		}
	}

	~ActiuneBursa() {
		if (valoriZilnice) {
			delete[] valoriZilnice;
		}
	}

	ActiuneBursa& operator=(const ActiuneBursa& other) {
		if (this != &other) {
			denumire = other.denumire;
			nrZile = other.nrZile;

			if (valoriZilnice != nullptr) {
				delete[] valoriZilnice;
			}

			if (other.valoriZilnice != nullptr) {
				valoriZilnice = new float[nrZile];
				for (int i = 0;i < nrZile;i++) {
					valoriZilnice[i] = other.valoriZilnice[i];
				}
			}
			else {
				valoriZilnice = nullptr;
			}
		}
		return *this;
	}

	ActiuneBursa operator+(const ActiuneBursa& other) const {
		int zileMin = min(nrZile, other.nrZile);
		ActiuneBursa rezultat(0, "Rezultat");
		rezultat.nrZile = zileMin;

		if (zileMin > 0) {
			rezultat.valoriZilnice = new float[zileMin];
			for (int i = 0;i < zileMin;i++) {
				rezultat.valoriZilnice[i] = valoriZilnice[i] + other.valoriZilnice[i];
			}
		}
		return rezultat;

	}

	friend ostream& operator<<(ostream& out, const ActiuneBursa& actiune);
};

string ActiuneBursa::denumireBursa = "BVB";

ostream& operator<<(ostream& out, const ActiuneBursa& actiune) {
	out << "ID Actiune: " << actiune.idActiune << "\n";
	out << "Denumire: " << actiune.denumire << "\n";
	out << "Numar zile: " << actiune.nrZile << "\n";
	out << "Valori zilnice: ";
	if (actiune.nrZile > 0 || actiune.valoriZilnice != nullptr) {
		for (int i = 0;i < actiune.nrZile;i++) {
			out << actiune.valoriZilnice[i] << " ";
		}
	}
	else {
		out << "N/A";
	}
	out << endl;
	return out;
}

int main() {

	ActiuneBursa actiune1(1, "Actiune1");
	float valori1[] = { 10.5, 20.3, 30.2 };
	actiune1.setValoriZilnice(valori1, 3);

	ActiuneBursa actiune2(2, "Actiune2");
	float valori2[] = { 5.5, 10.7, 15.6 };
	actiune2.setValoriZilnice(valori2, 3);

	// Supraincarcare operator +
	ActiuneBursa actiune3 = actiune1 + actiune2;

	// Supraincarcare operator =
	ActiuneBursa actiune4;
	actiune4 = actiune1;

	// Afisare rezultate
	cout << "Actiune1:\n" << actiune1;
	cout << "Actiune2:\n" << actiune2;
	cout << "Actiune3 (suma):\n" << actiune3;
	cout << "Actiune4 (copie):\n" << actiune4;

	return 0;
}