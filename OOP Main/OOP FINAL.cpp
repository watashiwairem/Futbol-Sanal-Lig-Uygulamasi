﻿#include <iostream>
#include <fstream> //dosya okumak için
#include <string>
#include <locale.h> //turkce
#include <iterator> //std::mt19937; shuffle()'i kullanmak için
#include <random> //random sayi olusturmak için
#include <vector>
#include <algorithm> //shuffle için
#include <clocale> //
#include <iomanip> //sutun görünümü olusturmak icin..
using namespace std;

string ToStr(char c) {
	//char'i stringe donusturmek icin
	return string(1, c);
}


int sumOfDigits(int x) {
	//hanelerin toplami
	int s = 0;
	while (x != 0) {
		s = s + x % 10;
		x = x / 10;
	}return s;
}

string process(std::string const& s) {
	//Takimlar.txt'den yalnýzca takimlari almak icin.
	string::size_type pos = s.find('-');
	if (pos != string::npos) {
		return s.substr(0, pos);
	}
	else {
		return s;
	}
}

string extract(const std::string& str, char beg, char end) {
	//Takimlar.txt'den yalnizca direktorleri almak icin.
	size_t begPos;
	if ((begPos = str.find(beg)) != std::string::npos) {
		std::size_t endPos;
		if ((endPos = str.find(end, begPos)) != std::string::npos && endPos != begPos + 1)
			return str.substr(begPos + 1, endPos - begPos - 1);
	}

	return std::string();
}

vector<pair<string, string>> combine(vector<string>& groupA, vector<string>& groupB) {
	//iki vektoru tek bir vektore sigdirmak icin
	vector<pair<string, string>> total(groupA.size());
	for (int i = 0; i < total.size(); ++i) {
		total[i] = make_pair(groupA[i], groupB[i]);
	}
	return total;
}


class dosyaOku {
public:
	vector<string> getTakimlar();
	vector<string> getDirektorler();
	vector<string> getIsimler(int);
	vector<string> getSoyisimler(int);
	bool takimOku(string);//veriler .txt dosyasindan okundu
	bool direktorOku(string);
	bool isimOku(string);
	bool soyisimOku(string);

private:
	vector<string> takimlar;
	vector<string> direktorler;
	vector<string> isimler;
	vector<string> soyisimler;
	string satir;
	ifstream txt;
	friend void menu();
};


class takmaIsim {
public:
	void takmaIsimOlustur(string);//takma isim olusturuldu
	vector<string> getTakmaIsimler();
private:
	vector<string> takmaIsimler;//takma isimlerin depolandigi vector
};

class isimEslestir {
public:
	isimEslestir(vector<string>, vector<string>);//isim ve soyisimler karistirildi
	void merge();//isim ve soyisimler birlestirildi
	vector<string>getFutbolcular();
private:
	vector<string> futbolcular;
	vector<string> isimler;
	vector<string> soyisimler;
};

class oyuncuOzellikleri {
public:
	void formaNoOlustur(int);
	void yasOlustur(int);
	void ortPerformansOlustur(int);
	void formasyonOlustur(string);
	void displayTakim(vector<string>, vector<string>, vector<string>, vector<string>, vector<string>, string);
	void perfDegis(vector<string>, vector<string>, vector<string>);
	vector<int>getFormaNo();
	vector<int>getYas();
	vector<int>getOrtPerformans();
	vector<int> getTakimOrtYas();
	vector<int> getTakimOrtPerformans();
	vector<string> getFormasyon();
private:
	vector<int> formaNo;
	vector<int> yas;//oyuncularin yaslari
	vector<int> ortPerformans;//oyuncularin performanslari
	vector<int> takimOrtYas;//takimlarin ortalama yaslari
	vector<int> takimOrtPerformans;//takimlarin ortalama performanslari
	vector<string> formasyon;
};

class fikstur {
public:
	void fiksturOlustur(vector<string>);//takim eslesmeleri olusturma
	void mevkiOrtOlustur(vector<string>, vector<int>, int);//mevki ortalamasi olusturma
	void skorOlustur(vector<string>, vector<int>);
	vector<pair<string, string>> getFikstur();//fiksturu maine gönderme
	vector<int> getMacID();//macID'yi fiksture gönderme
	void macBilgisiGoster(int, vector<string>, vector<int>, vector<string>, vector<int>, vector<string>);
	void displayFikstur(vector<string>);
	void displayTakimByTakmaAd(string, vector<string>, vector<string>);
	vector<int>getDefansOrtPerformans();
	vector<int>getOrtasahaOrtPerformans();
	vector<int>getForvetOrtPerformans();
	vector<int>getPuanDurumu();
	vector<int>getGalibiyet();
	vector<int>getBeraberlik();
	vector<int>getMaglubiyet();
	vector<int>getAtilanGol();
	vector<int>getYenilenGol();
	vector<int>getAveraj();
	vector<int>getOynananMac();
	void displayPuan(vector<string>, vector<int>, vector<int>);
	//vector<pair<int, int>> getScores();
private:
	vector<pair<string, string>> eslesmeler;
	vector<int> macID;
	vector<int> defansOrtPerformanslar;
	vector<int> ortasahaOrtPerformanslar;
	vector<int> forvetOrtPerformanslar;
	vector<pair<int, int>> scores;
	vector<int>oynananMac;
	vector<int>galibiyet;
	vector<int>beraberlik;
	vector<int>maglubiyet;
	vector<int>atilanGol;
	vector<int>yenilenGol;
	vector<int>averaj;
	vector<int>puanDurumu;
	friend void menu();
};

void bubbleSort(vector<int>& puanDurumu, vector<string>& takimlar, vector<int>& galibiyet, vector<int>& beraberlik,
	vector<int>& maglubiyet, vector<int>& atilanGol, vector<int>& yenilenGol, vector<int>& averaj);
void bubbleSort2(vector<int>& puanDurumu, vector<string>& takimlar, vector<int>& galibiyet, vector<int>& beraberlik,
	vector<int>& maglubiyet, vector<int>& atilanGol, vector<int>& yenilenGol, vector<int>& averaj);


void menu() {
	srand((unsigned int)time(NULL));//gercek random sayilar elde etmek icin
	setlocale(LC_ALL, "Turkish");

	vector<string> takimlar;
	vector<string> direktorler;
	dosyaOku takim;
	if (takim.takimOku("takimlar.txt") == true) //takimlar vectorun içine alindi
		takimlar = takim.getTakimlar();
	dosyaOku direktor;
	if (direktor.direktorOku("takimlar.txt") == true)//direktorler vectorun içine alindi
		direktorler = direktor.getDirektorler();

	vector<string> takmaIsimler;
	takmaIsim kisaltma;
	for (const auto& i : takimlar) {
		kisaltma.takmaIsimOlustur(i);
	}
	takmaIsimler = kisaltma.getTakmaIsimler();

	vector<string> isimler;
	vector<string> soyisimler;
	int takimSize = takimlar.size();
	dosyaOku isim;
	if (isim.isimOku("isimler.txt") == true)//isimler vectorün içine alindi
		isimler = isim.getIsimler(takimSize);
	dosyaOku soyisim;
	if (soyisim.soyisimOku("soyisimler.txt") == true)//soyisimler vectorün içine alindi
		soyisimler = soyisim.getSoyisimler(takimSize);

	vector<string> futbolcular;
	isimEslestir futbolcu(isimler, soyisimler);//isimler ve soyisimler karistirildi
	futbolcu.merge();//karistirilan isim ve soyisimler birlestirildi
	futbolcular = futbolcu.getFutbolcular();//olusan futbolcu listesi vectore tanimlandi

	int z = 0;
	int oyuncuSayisi = ((takimlar.size()) * 11);//takim sayisina gore gereken oyuncu sayisi
	if (takimlar.size() < 18) {//eger 18den az takim varsa gereksiz oyunculari siliyoruz
		while (true) {
			futbolcular.erase(next(futbolcular.begin(), oyuncuSayisi));
			if (oyuncuSayisi == futbolcular.size())
				break;
		}
	}

	vector<int> formaNo;
	vector<int> yaslar;
	vector<int> ortPerformanslar;
	vector<int> takimOrtYaslar;
	vector<int> takimOrtPerformanslar;

	oyuncuOzellikleri lig;
	lig.formaNoOlustur(takimlar.size());
	formaNo = lig.getFormaNo();

	lig.yasOlustur(takimlar.size());
	yaslar = lig.getYas();
	takimOrtYaslar = lig.getTakimOrtYas();

	lig.ortPerformansOlustur(takimlar.size());
	ortPerformanslar = lig.getOrtPerformans();
	takimOrtPerformanslar = lig.getTakimOrtPerformans();

	vector<pair<string, string>> fiksturler;
	vector<int> macID;
	fikstur fiksturOlustur;
	fiksturOlustur.fiksturOlustur(takimlar);
	fiksturler = fiksturOlustur.getFikstur();
	macID = fiksturOlustur.getMacID();
	fikstur ligDurumu;

	vector<int>puanlarr;
	puanlarr = fiksturOlustur.getPuanDurumu();
	vector<int>wins;
	wins = fiksturOlustur.getGalibiyet();

	vector<string> formasyon;
	while (true) {//Formasyon olusturma menüsü
		string formSecim; cout << "Formasyon bilgisi girmek ister misiniz?(y/n)\n"; cin >> formSecim;
		if (formSecim == "y" or formSecim == "Y") {//eger formasyon olusturulmak isteniyorsa
			for (int zp = 0; zp < takimlar.size(); zp++) {
				string formTipi; cout << takimlar[zp] << " takiminin formasyon bilgisi giriniz(Örnek giris sekli: 442): "; cin >> formTipi;
				if (formTipi.size() == 3 and sumOfDigits(stoi(formTipi)) == 10 and formTipi.find_first_of("0") == string::npos) {
					lig.formasyonOlustur(formTipi);//gelen formasyon bilgisi ile 1 takimi oluþturuyoruz
				}
				else { cout << "Hatali giris, tekrar deneyiniz.\n\n"; zp -= 1; continue; } //eger girilen formasyon bilgisi tutarsizsa iptal
				if (takimlar.size() - 1 == zp) { formasyon = lig.getFormasyon(); }//olusan formasyon bilgisini alyoruz
			}
			break;
		}//eger formasyon olusturulmak istenmiyorsa:
		else if (formSecim == "n" or formSecim == "N") {
			for (int zp = 0; zp < takimlar.size(); zp++) { lig.formasyonOlustur("442"); }//formasyon bilgisi girilmemisse
			formasyon = lig.getFormasyon();  break;
		}											//bütün takimlari 442 yapiyoruz
		else { cout << "Uygunsuz bir cevap girdiniz. Tekrar deneyiniz.\n\n"; }
	}

	vector<int> DefansOrtPerformanslar, OrtasahaOrtPerformanslar, ForvetOrtPerformanslar;
	fiksturOlustur.mevkiOrtOlustur(formasyon, ortPerformanslar, futbolcular.size());
	DefansOrtPerformanslar = fiksturOlustur.getDefansOrtPerformans();
	OrtasahaOrtPerformanslar = fiksturOlustur.getOrtasahaOrtPerformans();
	ForvetOrtPerformanslar = fiksturOlustur.getForvetOrtPerformans();

	fiksturOlustur.skorOlustur(takimlar, takimOrtPerformanslar);
	int j = 0;
	while (true) {//ana menu
		cout << "\n(1)-Takimlari Listele" << "\n"
			<< "(2)-Oyuncu Performansi Degistir(Değişimden sonra fikstür yeniden oluşturulacaktır)" << "\n"
			<< "(3)-Takim Bilgisi Goster" << "\n"
			<< "(4)-Fiksturu Listele" << "\n"
			<< "(5)-Bir Takimin Maclarini Listele" << "\n"
			<< "(6)-MacID Ile Mac Bilgilerini Goster" << "\n"
			<< "(7)-Puan Durumunu Goster(Once Fikstur Olusturmalisiniz!!!)" << "\n"
			<< "(8)-Cikis\n";
		int secim;
		cout << "Seciminiz: "; cin >> secim;
		if (!cin) {
			cout << "Yanlis deger, tekrar deneyin."; cin.clear();
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		}
		if (secim == 1) {
			cout << "\n|-------------------------|-------------------------|----------|";
			cout << "\n|         TAKIM ADI       |    TEKNIK DIREKTOR ADI  | TAKMA AD |";
			cout << "\n|-------------------------|-------------------------|----------|\n";
			for (int i = 0; i < takimlar.size(); i++) {
				cout << "|" << left << setw(25) << takimlar[i] << "|" << left << setw(25) << direktorler[i] << "|" << left << setw(10) << takmaIsimler[i] << "|" << endl;
			}
		}
		else if (secim == 2) {//Bir oyuncunun performans degerini deðiþtir
			lig.perfDegis(futbolcular, takimlar, takmaIsimler);
			ortPerformanslar = lig.getOrtPerformans();
			takimOrtPerformanslar = lig.getTakimOrtPerformans();
			fiksturOlustur.skorOlustur(takimlar, takimOrtPerformanslar);//performanslar degistigi için skorlari bastan olusturuyoruz.
		}
		else if (secim == 3) {//Bir takimin bilgilerini goster
			string bilgiSecim;
			cout << "Bilgilerini görmek istediginiz takimin takma adini yaziniz: "; cin >> bilgiSecim;
			transform(bilgiSecim.begin(), bilgiSecim.end(), bilgiSecim.begin(), toupper);//girilen veriyi ust karakter yap
			lig.displayTakim(futbolcular, formasyon, takimlar, direktorler, takmaIsimler, bilgiSecim);
		}
		else if (secim == 4) {//Lig fiksturunu ve skorlari goster
			fiksturOlustur.displayFikstur(takimlar);
		}
		else if (secim == 5) {//Sadece bir takima ait maclari goster
			string fiksturSecim;
			cout << "Maclarini gormek istediginiz takimin takma adini giriniz: "; cin >> fiksturSecim;
			transform(fiksturSecim.begin(), fiksturSecim.end(), fiksturSecim.begin(), toupper);//girilen veriyi ust karakter yap
			fiksturOlustur.displayTakimByTakmaAd(fiksturSecim, takmaIsimler, takimlar);
		}
		else if (secim == 6) {//MacID ile bir mac sec ve mactaki takimlarin ozelliklerini goster.
			int macSecim;
			cout << "Bilgilerini gormek istediginiz maçin MacID'sini giriniz: "; cin >> macSecim;
			fiksturOlustur.macBilgisiGoster(macSecim, takimlar, takimOrtPerformanslar, futbolcular, ortPerformanslar, formasyon);
		}
		else if (secim == 7) {
			fiksturOlustur.displayPuan(takimlar, puanlarr, wins);
		}
		else if (secim == 8) {
			cout << "\n\n\t\tGORUSURUZ\n\n";
			break;
		}
	}
}

int main() {
	menu();
	return 0;
}

//##########################ISIM-SOYISIM-TAKIM-DIREKTOR DOSYADAN OKUMA#####################################
bool dosyaOku::takimOku(string txtName) {
	ifstream txt;
	string satir;
	setlocale(LC_ALL, "Turkish");

	txt.open(txtName.c_str());

	if (!txt.is_open()) {
		cerr << "Error while opening the file.\n";
		return false;
	}
	while (getline(txt, satir))
		takimlar.push_back(process(satir));
	return true;
}
vector<string> dosyaOku::getTakimlar() {
	return takimlar;
}

bool dosyaOku::direktorOku(string txtName) {
	ifstream txt;
	string satir;

	txt.open(txtName.c_str());

	if (!txt.is_open()) {
		cerr << "Error while opening the file.\n";
		return false;
	}
	while (getline(txt, satir))
		direktorler.push_back(extract(satir, '-', '+'));
	return true;
}
vector<string> dosyaOku::getDirektorler() {
	return direktorler;
}


bool dosyaOku::isimOku(string txtName) {
	ifstream txt;
	string satir;

	txt.open(txtName.c_str());

	if (!txt.is_open()) {
		cerr << "Error while opening the file.\n";
		return false;
	}
	while (getline(txt, satir))
		isimler.push_back(satir);

	return true;

}
vector<string> dosyaOku::getIsimler(int tSize) {
	int isimSize = isimler.size();
	if (isimler.size() >= tSize * 11) {
		isimler.resize(isimler.size() - (isimSize - tSize * 11));
	}
	return isimler;
}

bool dosyaOku::soyisimOku(string txtName) {
	ifstream txt;
	string satir;

	txt.open(txtName.c_str());

	if (!txt.is_open()) {
		cerr << "Error while opening the file.\n";
		return false;
	}
	while (getline(txt, satir))
		soyisimler.push_back(satir);

	return true;

}
vector<string> dosyaOku::getSoyisimler(int tSize) {
	int soyisimSize = soyisimler.size();
	if (soyisimler.size() >= tSize * 11) {
		soyisimler.resize(soyisimler.size() - (soyisimSize - tSize * 11));
	}
	return soyisimler;
}

//##########################TAKMA ISIM OLUSTURMA#####################################
void takmaIsim::takmaIsimOlustur(string takim) {
	//takim iki kelimeliyse buradan
	if ((takim.find(" ")) != string::npos) {
		char firstLetter = takim.at(0); //ilk kelime
		char secondLetter = (takim.substr(takim.find(" ") + 1)).at(0); //ikinci kelime
		string takmaIsim = ToStr(firstLetter) + ToStr(secondLetter);
		if ((takmaIsimler.empty()) != 1) {//liste bos degilse iceri gir
			for (const auto& h : takmaIsimler) {//eger takma ad daha onceden alindiysa degistirelim
				if (h == takmaIsim) {
					char middleLetter = takim.at(1);
					takmaIsim = ToStr(firstLetter) + ToStr(toupper(middleLetter)) + ToStr(secondLetter);//toupper->küçük harfi büyük yap
				}
			}
			takmaIsimler.push_back(takmaIsim);
		}
		else {//liste bossa ekle
			takmaIsimler.push_back(takmaIsim);
		}
	}
	else {
		char firstLetter = takim.at(0);
		char secondLetter = takim.at(1);
		string takmaIsim = ToStr(firstLetter) + ToStr(toupper(secondLetter));//toupper->kucuk harfi buyuk yap
		if ((takmaIsimler.empty()) != 1) {//liste bos degilse iceri gir
			for (const auto& h : takmaIsimler) {//eger takma ad daha onceden alindiysa degistirelim
				if (h == takmaIsim) {
					char middleLetter = takim.at(1);
					char secondLetter = takim.at(2);
					takmaIsim = ToStr(firstLetter) + ToStr(toupper(middleLetter)) + ToStr(toupper(secondLetter));//toupper->kucuk harfi buyuk yap
					break;
				}
			}
			takmaIsimler.push_back(takmaIsim);
		}
		else {//liste bossa ekle
			takmaIsimler.push_back(takmaIsim);
		}
	}
}
vector<string> takmaIsim::getTakmaIsimler() {
	return takmaIsimler;
}

//##########################ISIM OLUSTURMA#####################################
isimEslestir::isimEslestir(vector<string> names, vector<string> surnames) {//iki vectoru karistiriyoruz
	isimler = names;//isimleri vectore aliyoruz
	soyisimler = surnames;//soyisimleri vectore aliyoruz
	shuffle(begin(isimler), end(isimler),//isimleri kariþtiriyoruz
		mt19937{ random_device{}() });
	shuffle(begin(soyisimler), end(soyisimler),//soyisimleri kariþtiriyoruz
		mt19937{ random_device{}() });
}

void isimEslestir::merge() {//isimler ve soyisimleri birlestiriyoruz
	int z = 0;
	for (const auto& i : isimler) {
		futbolcular.push_back(isimler[z] + " " + soyisimler[z]);
		z++;
	}
}

vector<string> isimEslestir::getFutbolcular() {
	return futbolcular;
}

//##########################OYUNCU ÖZELLIKLERI#####################################

void oyuncuOzellikleri::formaNoOlustur(int l) {
	int i;
	int f = 0;
	int randomNum;
	int counter = 0;
	vector<int> nolar;

	for (f = 0; f < l; f++) {
		nolar.clear();//kullanmadan once gecici vectoru temizliyoruz
		for (i = 1; i <= 11; i++) {//1 takimin 11 futbolcusu icin 11 kere donuyoruz
			randomNum = 1 + (rand() % 99);//random sayi olusturuldu
			nolar.push_back(randomNum);//vector içine atildi
			for (const auto& p : nolar) {//ayni takimda ayni numara var mi yok mu kontrolunu yapiyoruz
				if ((counter != 0) && ((nolar.size()) - 1 != counter) && (p == randomNum)) {//eger sayilar ayniysa temizleyip bastan basliyoruz
					nolar.clear();
					i = 0;
					break;
				}
				counter++;
			}
			counter = 0;
		}

		for (const auto& g : nolar) {
			formaNo.insert(formaNo.end(), { g });
		}
	}
}

vector<int> oyuncuOzellikleri::getFormaNo() {
	return formaNo;
}

void oyuncuOzellikleri::yasOlustur(int l) {
	int i;
	int f = 0;
	int randomNum;
	int total = 0;
	vector<int> yaslar;

	for (f = 0; f < l; f++) {
		yaslar.clear();//kullanmadan once gecici vectoru temizliyoruz
		for (i = 1; i <= 11; i++) {//1 takimin 11 futbolcusu için 11 kere dönüyoruz
			randomNum = (18 + (rand() % 19));//random sayi olusturuldu
			yaslar.push_back(randomNum);//vector içine atildi
		}
		for (const auto& b : yaslar) {//toplam deger olusturuyoruz
			total += b;
		}
		if ((25 > (total / 11)) or ((total / 11) > 32)) {//eger ortalama yas 25 den dusuk ya da 32 den yuksekse takimi bastan olusturuyoruz
			total = 0;
			f -= 1;
			continue;
		}

		takimOrtYas.push_back(total / 11);//daha sonra kullanmak üzere ortalama takim performansini aliyoruz
		for (const auto& g : yaslar) {//çikan oyuncu performanslarini vectore atiyoruz
			yas.insert(yas.end(), { g });
		}
		total = 0;
	}
}
vector<int> oyuncuOzellikleri::getYas() {
	return yas;
}
vector<int> oyuncuOzellikleri::getTakimOrtYas() {
	return takimOrtYas;
}

void oyuncuOzellikleri::ortPerformansOlustur(int l) {
	int i;
	int f = 0;
	int randomNum;
	int total = 0;
	vector<int> ortPerformanslar;

	for (f = 0; f < l; f++) {
		ortPerformanslar.clear();//kullanmadan once gecici vectoru temizliyoruz
		for (i = 1; i <= 11; i++) {//1 takimin 11 futbolcusu icin 11 kere donuyoruz
			randomNum = (30 + (rand() % 71));//random sayi olusturuldu
			ortPerformanslar.push_back(randomNum);//vector icine atildi
		}
		for (const auto& b : ortPerformanslar) {//toplam ort performans olusturuyoruz
			total += b;
		}
		if (total / 11 < 60) {//eger takim ortalamasi 60'tan dusukse bastan yapiyoruz
			total = 0;
			f -= 1;
			continue;
		}

		takimOrtPerformans.push_back(total / 11);//daha sonra kullanmak üzere ortalama takim performansini aliyoruz
		for (const auto& g : ortPerformanslar) {//çikan oyuncu performanslarini vectore atiyoruz
			ortPerformans.insert(ortPerformans.end(), { g });
		}
		total = 0;
	}
}
vector<int> oyuncuOzellikleri::getOrtPerformans() {
	return ortPerformans;
}
vector<int> oyuncuOzellikleri::getTakimOrtPerformans() {
	return takimOrtPerformans;
}

void oyuncuOzellikleri::formasyonOlustur(string formTipi) {
	string mevki_sablon[4] = { "D","O","F","K" };//DEFANS, ORTA SAHA, FORVET, KALECI
	int i;
	{//her takim için bir kere donuyoruz
		for (i = 0; i < stoi(ToStr(formTipi.at(0))); i++) { formasyon.push_back("D"); }//defans atamasi
		for (i = 0; i < stoi(ToStr(formTipi.at(1))); i++) { formasyon.push_back("O"); }//orta saha atamasi
		for (i = 0; i < stoi(ToStr(formTipi.at(2))); i++) { formasyon.push_back("F"); }//forvet atamasi
		formasyon.push_back("K");//kaleci atamasi (1 tane)
	}
}
vector<string> oyuncuOzellikleri::getFormasyon() {
	return formasyon;
}

void oyuncuOzellikleri::displayTakim(vector<string> futbolcular, vector<string> formasyon,
	vector<string> takimlar, vector<string> direktorler, vector<string> takmaIsimler, string bilgiSecim) {//ekrana takim bilgisi bastirmak
	int j = 0, k = 0, takýmPerformansi = 0;
	for (; k < takimlar.size(); k++) {
		if (takmaIsimler[k] == bilgiSecim) {
			cout << left << setw(30) << "Isim – Soyisim" << left << setw(10) << "Yas" <<
				left << setw(20) << "Forma numarasi" << left << setw(20) << "Performans" <<
				left << setw(20) << "Formasyon" << endl;
			cout << left << setw(30) << "---------------" << left << setw(10) << "------" <<
				left << setw(20) << "--------------" << left << setw(20) << "-----------" <<
				left << setw(30) << "---------" << endl;
			j += (k * 11);
			for (int d = 0; d < 11; d++) {//oyuncularin ve bilgilerinin basimi
				cout << left << setw(30) << futbolcular[j] << setprecision(2) << fixed << setw(10) << yas[j] <<
					setprecision(2) << fixed << setw(20) << formaNo[j] << setprecision(2) << fixed << setw(20) <<
					ortPerformans[j] << setprecision(2) << fixed << setw(30) << formasyon[j] << endl;
				j++;
			}
			cout << "\nTakim adi: " << takimlar[k] << "\n" << "Teknik direktoru: " << direktorler[k] << "\n"//takimlarin basimi
				<< "Takim ortalama performansi: " << takimOrtPerformans[k] << "\n" << "Takim ortalama yasi: " << takimOrtYas[k];
		}
	}
}

void oyuncuOzellikleri::perfDegis(vector<string> futbolcular, vector<string> takimlar, vector<string> takmaIsimler) {
	int j;
	for (j = 0; j < futbolcular.size(); j++) {//performansi degistirilecek oyuncuyu secmek için gosterim
		if (j % 11 == 0) {
			cout << "\n\n" << takimlar[j / 11] << " - " << takmaIsimler[j / 11] << "\n";
		}
		cout << j + 1 << " " << futbolcular[j] << "- Ortalama performansi:" << ortPerformans[j] << "\n";
	}
	int ortSecim, ortIndex, ort;
	cout << "\n\nKaç oyuncunun performansini degistirmek istiyorsunuz: ";
	cin >> ortIndex;
	for (j = 0; j < ortIndex; j++) {//kaç degisim yapilacaksa o kadar dongu
		cout << "Performansini degistirmek istediginiz oyuncunun kodunu giriniz: ";
		cin >> ortSecim;//hangi kodlu oyuncunun degistirilecegi secimi
		cout << "Ortalama performansi: ";
		cin >> ort;
		int backup = ortPerformans[ortSecim - 1];
		ortPerformans[ortSecim - 1] = ort;
		int c = ((ortSecim - 1) / 11);
		c *= 11;
		int toplam = 0;
		for (; c < (((ortSecim - 1) / 11) * 11) + 11; c++) {
			toplam += ortPerformans[c];
		}
		if (toplam / 11 < 60) {
			cout << "Lutfen oyuncuya takim ortalama performansini 60 üzerinde tutacak bir deger giriniz.\n\n";
			j -= 1;
			ortPerformans[ortSecim - 1] = backup;
			continue;
		}
		takimOrtPerformans[((ortSecim - 1) / 11)] = toplam / 11;
	}
}

//##########################FIKSTUR OLUSTUR#####################################
void fikstur::fiksturOlustur(vector<string> takimlar) {//round-robin tournament scheduler algoritmasi(https://stackoverflow.com/a/6649732/16002501)
	int half = ceil(takimlar.size() / 2);//takimlarin yarini aliyoruz. tek deger girilme olasiligina karsi yuvarliyoruz
	int j = half;
	vector<string> groupA;
	vector<string> groupB;
	vector<pair<string, string>> temp;
	for (int i = 0; i < half; i++) {//takimlari iki gruba boluyoruz
		groupA.insert(groupA.end(), { takimlar[i] });
		groupB.insert(groupB.end(), { takimlar[j] });
		j++;
	}
	reverse(groupB.begin(), groupB.end());//B'yi tersine ceviriyoruz
	eslesmeler = combine(groupA, groupB);//Olusturulan ters dizilimi ikili halde baska bir vectore aktariyoruz.

	for (int i = 1; i < takimlar.size() - 1; i++) {//eslestirmelerin olusturulma sekansi. ((katilimci sayisi)-1) seklinde eslesme olacagi icin n-1 kadar donuyoruz
		auto pos = groupA.begin() + 1;    //ikinci vektorden ilk vektore
		groupA.insert(pos, { groupB[0] });//aktarim yapip ikinci vektoru
		groupB.erase(groupB.begin());    //tekrar yapmamasi icin siliyoruz////
		groupB.push_back(groupA[(groupA.size()) - 1]); //benzer sekilde ilk vektorden ikinci vektore son indexi
		groupA.pop_back();							  //aktarip tekrar yapmamasi icin ilk vektoru siliyoruz./////////
		temp = combine(groupA, groupB);
		eslesmeler.insert(eslesmeler.end(), temp.begin(), temp.end());//çikan yeni dizilimi vektore yolluyoruz
	}

	//maçID olusturulmasi
	for (int i = 0; i < eslesmeler.size(); i++) {
		macID.push_back(i);
	}

}
vector<pair<string, string>> fikstur::getFikstur() {
	return eslesmeler;
}
vector<int> fikstur::getMacID() {
	return macID;
}

void fikstur::mevkiOrtOlustur(vector<string> formasyonlar, vector<int> ortPerformans, int futbolcuSayisi) {
	int i = 0, j = 0, toplamD = 0, toplamO = 0, toplamF = 0, d = 0, o = 0, f = 0;
	for (; i < futbolcuSayisi; i++) {//DEFANSLARI PERFORMANSLARINI TOPLUYORUZ
		if (formasyonlar[i] == "D") {
			toplamD += ortPerformans[i];
			d++;
		}
		else if (formasyonlar[i] == "O") {//ORTA SAHALARIN PERFORMANSLARINI TOPLUYORUZ
			toplamO += ortPerformans[i];
			o++;
		}
		else if (formasyonlar[i] == "F") {//FORVETLERIN PERFORMANSLARINI TOPLUYORUZ
			toplamF += ortPerformans[i];
			f++;
		}

		j++;
		if (j == 11) {//HER TAKIMIN ORT PERFORMANSLARINI NOT ALIYORUZ
			defansOrtPerformanslar.push_back(toplamD / d);
			ortasahaOrtPerformanslar.push_back(toplamO / o);
			forvetOrtPerformanslar.push_back(toplamF / f);
			j = 0, d = 0, o = 0, f = 0, toplamD = 0, toplamO = 0, toplamF = 0;//bastan baslamak için parametreleri sifirliyoruz
		}
	}
}
vector<int> fikstur::getDefansOrtPerformans() {
	return defansOrtPerformanslar;
}
vector<int> fikstur::getOrtasahaOrtPerformans() {
	return ortasahaOrtPerformanslar;
}
vector<int> fikstur::getForvetOrtPerformans() {
	return forvetOrtPerformanslar;
}

void fikstur::skorOlustur(vector<string>takimlar, vector<int> takimOrtPerformanslar) {//score olusturma
	for (const auto& g : eslesmeler) {//her takim için zar atip skorlarini vectore atiyoruz
		scores.push_back(make_pair(1 + (rand() % 5), 1 + (rand() % 5)));
	}

	int i = 0, teamSize = takimlar.size(), c = 0;//parametreler

	for (; c < eslesmeler.size(); c++) {//mevki performanslarina gore skor olusturma
		for (int ab = 0; ab < teamSize; ab++) {//////////////////her iki takimin da indexini alip bu indexler vasitasi ile mevki performanslarimi karsilastiriyoruz
			if (eslesmeler[c].first == takimlar[ab]) {//ilk takimin indexini çekiyoruz
				for (int cb = 0; cb < teamSize; cb++) {
					if (eslesmeler[c].second == takimlar[cb]) {//ikinci takimin indexini cekiyoruz //ve mevki performanslarina göre skoru olusturuyoruz
						if (defansOrtPerformanslar[ab] > defansOrtPerformanslar[cb]) {
							scores[c].second--;
							if (scores[c].second < 0) {
								scores[c].second = 0;
							}
						}
						else {
							scores[c].first--;
							if (scores[c].first < 0) {
								scores[c].first = 0;
							}
						}
						if (ortasahaOrtPerformanslar[ab] > ortasahaOrtPerformanslar[cb]) {
							scores[c].first++;
							scores[c].second--;
							if (scores[c].second < 0) {
								scores[c].second = 0;
							}
						}
						else {
							scores[c].first--;
							scores[c].second++;
							if (scores[c].first < 0) {
								scores[c].first = 0;
							}
						}
						if (forvetOrtPerformanslar[ab] > forvetOrtPerformanslar[cb]) {
							scores[c].first++;
						}
						else {
							scores[c].second++;
						}
						if (takimOrtPerformanslar[ab] > takimOrtPerformanslar[cb]) {
							int a = 0 + (rand() % 1);
							if (a == 0) { scores[c].first++; }
							else {
								scores[c].second--;
								if (scores[c].second < 0) {
									scores[c].second = 0;
								}
							}
						}
						else {
							int a = 0 + (rand() % 1);
							if (a == 0) { scores[c].second++; }
							else {
								scores[c].first--;
								if (scores[c].first < 0) {
									scores[c].first = 0;
								}
							}
						}
					}

				}
			}
		}
	}
}

void fikstur::displayFikstur(vector<string> teams) {
	int j = 1, hafta = 2, in = 0;
	galibiyet.clear();
	maglubiyet.clear();
	beraberlik.clear();
	atilanGol.clear();
	yenilenGol.clear();
	averaj.clear();
	oynananMac.clear();
	puanDurumu.clear();
	for (int i = 0; i < teams.size(); i++) {
		galibiyet.push_back(0);
		maglubiyet.push_back(0);
		atilanGol.push_back(0);
		yenilenGol.push_back(0);
		averaj.push_back(0);
		oynananMac.push_back(0);
		beraberlik.push_back(0);
		puanDurumu.push_back(0);
	}
	cout << "\n1. Hafta\n";


	for (; in < eslesmeler.size(); in++) {

		cout << "MacID: " << macID[j - 1] << " " << eslesmeler[in].first << " " << scores[in].first << " - " << scores[in].second << " " << eslesmeler[in].second << "\n";
		string takim1 = eslesmeler[in].first;
		string takim2 = eslesmeler[in].second;
		int temp;
		int gol1 = scores[in].first;
		int gol2 = scores[in].second;
		for (int i = 0; i < (teams.size()); i++) {
			if (takim1 == teams.at(i)) {
				if (gol1 > gol2) {
					temp = galibiyet[i];
					temp++;
					galibiyet[i] = temp;
					temp = atilanGol[i];
					temp += gol1;
					atilanGol[i] = temp;
					temp = yenilenGol[i];
					temp += gol2;
					yenilenGol[i] = temp;
					temp = averaj[i];
					temp += gol1 - gol2;
					averaj[i] = temp;
					temp = puanDurumu[i];
					temp = temp + 3;
					puanDurumu[i] = temp;
					temp = oynananMac[i];
					temp++;
					oynananMac[i] = temp;
				}
				else if (gol1 < gol2) {
					temp = maglubiyet[i];
					temp++;
					maglubiyet[i] = temp;
					temp = atilanGol[i];
					temp += gol1;
					atilanGol[i] = temp;
					temp = yenilenGol[i];
					temp += gol2;
					yenilenGol[i] = temp;
					temp = averaj[i];
					temp += gol1 - gol2;
					averaj[i] = temp;
					temp = oynananMac[i];
					temp++;
					oynananMac[i] = temp;
				}
				else if (gol1 == gol2) {
					temp = beraberlik[i];
					temp++;
					beraberlik[i] = temp;
					temp = atilanGol[i];
					temp += gol1;
					atilanGol[i] = temp;
					temp = yenilenGol[i];
					temp += gol2;
					yenilenGol[i] = temp;
					temp = averaj[i];
					temp += gol1 - gol2;
					averaj[i] = temp;
					temp = puanDurumu[i];
					temp = temp + 1;
					puanDurumu[i] = temp;
					temp = oynananMac[i];
					temp++;
					oynananMac[i] = temp;
				}
			}
			if (takim2 == teams.at(i)) {
				if (gol1 > gol2) {
					temp = galibiyet[i];
					temp++;
					galibiyet[i] = temp;
					temp = atilanGol[i];
					temp += gol1;
					atilanGol[i] = temp;
					temp = yenilenGol[i];
					temp += gol2;
					yenilenGol[i] = temp;
					temp = averaj[i];
					temp += gol1 - gol2;
					averaj[i] = temp;
					temp = puanDurumu[i];
					temp = temp + 3;
					puanDurumu[i] = temp;
					temp = oynananMac[i];
					temp++;
					oynananMac[i] = temp;
				}
				else if (gol1 < gol2) {
					temp = maglubiyet[i];
					temp++;
					maglubiyet[i] = temp;
					temp = atilanGol[i];
					temp += gol1;
					atilanGol[i] = temp;
					temp = yenilenGol[i];
					temp += gol2;
					yenilenGol[i] = temp;
					temp = averaj[i];
					temp += gol1 - gol2;
					averaj[i] = temp;
					temp = oynananMac[i];
					temp++;
					oynananMac[i] = temp;
				}
				else if (gol1 = gol2) {
					temp = beraberlik[i];
					temp++;
					beraberlik[i] = temp;
					temp = atilanGol[i];
					temp += gol1;
					atilanGol[i] = temp;
					temp = yenilenGol[i];
					temp += gol2;
					yenilenGol[i] = temp;
					temp = averaj[i];
					temp += gol1 - gol2;
					averaj[i] = temp;
					temp = puanDurumu[i];
					temp = temp + 1;
					puanDurumu[i] = temp;
					temp = oynananMac[i];
					temp++;
					oynananMac[i] = temp;
				}
			}
		}

		if (j % (teams.size() / 2) == 0 && hafta < teams.size() + 1) {
			cout << "\n" << hafta << ". Hafta\n";
			hafta++;
		}
		j++;
	}
}
vector<int> fikstur::getPuanDurumu() {
	return puanDurumu;
}
vector<int> fikstur::getGalibiyet() {
	return  galibiyet;
}
vector<int> fikstur::getBeraberlik() {
	return beraberlik;
}
vector<int> fikstur::getMaglubiyet() {
	return maglubiyet;
}
vector<int> fikstur::getAtilanGol() {
	return atilanGol;
}
vector<int> fikstur::getYenilenGol() {
	return yenilenGol;
}
vector<int> fikstur::getAveraj() {
	return averaj;
}
vector<int> fikstur::getOynananMac() {
	return oynananMac;
}

void bubbleSort(vector<int>& puanDurumu, vector<string>& takimlar, vector<int>& galibiyet, vector<int>& beraberlik, vector<int>& maglubiyet,
	vector<int>& atilanGol, vector<int>& yenilenGol, vector<int>& averaj) {
	bool swapp = true;
	while (swapp) {
		swapp = false;
		for (size_t i = 0; i < puanDurumu.size() - 1; i++) {
			if (puanDurumu[i] < puanDurumu[i + 1]) {
				puanDurumu.at(i) += puanDurumu.at(i + 1);
				swap(takimlar.at(i), takimlar.at(i + 1));
				swap(galibiyet.at(i), galibiyet.at(i + 1));
				swap(beraberlik.at(i), beraberlik.at(i + 1));
				swap(maglubiyet.at(i), maglubiyet.at(i + 1));
				swap(atilanGol.at(i), atilanGol.at(i + 1));
				swap(yenilenGol.at(i), yenilenGol.at(i + 1));
				swap(averaj.at(i), averaj.at(i + 1));
				puanDurumu.at(i + 1) = puanDurumu.at(i) - puanDurumu.at(i + 1);
				puanDurumu.at(i) -= puanDurumu.at(i + 1);
				swapp = true;
			}

		}
	}
}
void bubbleSort2(vector<int>& puanDurumu, vector<string>& takimlar, vector<int>& galibiyet, vector<int>& beraberlik,
	vector<int>& maglubiyet, vector<int>& atilanGol, vector<int>& yenilenGol, vector<int>& averaj) {
	bool swappp = true;
	while (swappp) {
		swappp = false;
		for (size_t i = 0; i < puanDurumu.size() - 1; i++) {
			if (puanDurumu[i] == puanDurumu[i + 1]) {
				if (averaj[i] < averaj[i + 1]) {
					swap(averaj.at(i), averaj.at(i + 1));
					swap(takimlar.at(i), takimlar.at(i + 1));
					swap(galibiyet.at(i), galibiyet.at(i + 1));
					swap(beraberlik.at(i), beraberlik.at(i + 1));
					swap(maglubiyet.at(i), maglubiyet.at(i + 1));
					swap(atilanGol.at(i), atilanGol.at(i + 1));
					swap(yenilenGol.at(i), yenilenGol.at(i + 1));
					swappp = true;
				}
			}
		}
	}
}

void fikstur::displayPuan(vector<string>takimlarr, vector<int>puans, vector<int>winler) {
	bubbleSort(puanDurumu, takimlarr, galibiyet, beraberlik, maglubiyet, atilanGol, yenilenGol, averaj);
	bubbleSort2(puanDurumu, takimlarr, galibiyet, beraberlik, maglubiyet, atilanGol, yenilenGol, averaj);

	cout << "\n|-------------------------------------------------------------------|";
	cout << "\n|SIRA NO|        TAKIM ADI        |OM |GS |BS |MS |AG |YG |AV |PUAN |";
	cout << "\n|-------------------------------------------------------------------|\n";
	for (int i = 0; i < takimlarr.size(); i++) {
		//cout << takimlarr.at(i) << " Puan: " << puanDurumu[i] <<" Kazanilan Maclar: "<< galibiyet[i] << endl;
		cout << "|" << left << setw(7) << i + 1 << "|" << left << setw(25) << takimlarr.at(i) << "|" << left << setw(3) << oynananMac[i] << "|" << left << setw(3) << galibiyet[i] << "|"
			<< left << setw(3) << beraberlik[i] << "|" << left << setw(3) << maglubiyet[i] << "|" << left << setw(3) << atilanGol[i] << "|"
			<< left << setw(3) << yenilenGol[i] << "|" << left << setw(3) << averaj[i] << "|" << left << setw(5) << puanDurumu[i] << "|"
			<< endl;
		cout << "____________________________________________________________________|" << endl;
	}
	cout << "\n(Puan Durumunu Yeniden Listelemek Icin Fikstur Yeniden Olusturulmalidir)\n";
}

void fikstur::macBilgisiGoster(int talepMacID, vector<string> takimlar, vector<int> takimOrtPerformans,
	vector<string> futbolcular, vector<int> performanslar, vector<string> formasyon) {//tablo görünümünde mac basimi
	int a = 0, b = 0;
	for (const auto& takimA : takimlar) {
		if (takimA == eslesmeler[talepMacID].first) {//ilk takimi cekiyoruz
			for (const auto& takimB : takimlar) {
				if (takimB == eslesmeler[talepMacID].second) {//ikinci takimi cekiyoruz
					a *= 11; b *= 11; int tempMaxA = a + 11, tempMaxB = b + 11; ////tabloyu bastiriyoruz
					cout << left << "          " << setw(80) << eslesmeler[talepMacID].first << eslesmeler[talepMacID].second << endl;
					cout << left << setw(30) << "Isim – Soyisim" << left << setw(20) << "Oynadigi Bolge" <<
						left << setw(40) << "Performans" << left << setw(20) << "Performans" <<
						left << setw(30) << "Oynadigi Bolge" << "Isim – Soyisim" << endl;
					cout << left << setw(30) << "---------------" << left << setw(20) << "--------------" <<
						left << setw(40) << "-----------" << left << setw(20) << "-----------" <<
						left << setw(30) << "--------------" << "---------------" << endl;
					for (; a < tempMaxA and b < tempMaxB; a++, b++) {//futbolculari bastiriyoruz
						cout << left << setw(30) << futbolcular[a] << setprecision(2) << fixed << setw(20) << formasyon[a] <<
							setprecision(2) << fixed << setw(40) << performanslar[a] << setprecision(2) << fixed << setw(20) <<
							performanslar[b] << setprecision(2) << fixed << setw(30) << formasyon[b] << setprecision(2) <<
							fixed << futbolcular[b] << endl;
					}
					tempMaxA = (tempMaxA - 11) / 11; tempMaxB = (tempMaxB - 11) / 11;//kazanma olasiligini olusturup bastiriyoruz
					int total = takimOrtPerformans[tempMaxA] + takimOrtPerformans[tempMaxB];
					int winPosA = ((takimOrtPerformans[tempMaxA] * 100.0) / total);
					int winPosB = ((takimOrtPerformans[tempMaxB] * 100.0) / total);
					cout << "\n" << eslesmeler[talepMacID].first << " takimin takim ortalama perforansi: " <<
						takimOrtPerformans[tempMaxA] << "  Kazanma olasiligi: %" << ceil(winPosA);
					cout << "\n" << eslesmeler[talepMacID].second << " takiminin takim ortalama perforansi: " <<
						takimOrtPerformans[tempMaxB] << "  Kazanma olasiligi: %" << ceil(winPosB);
				}
				b++;
			}
		}
		a++;
	}
}

void fikstur::displayTakimByTakmaAd(string fiksturSecim, vector<string> takmaIsimler, vector<string> takimlar) {
	int k = 0;
	for (; k < takimlar.size(); k++) {
		if (takmaIsimler[k] == fiksturSecim) {
			int j = 1; int hafta = 2;
			cout << "\n1. Hafta\n";
			for (const auto& b : eslesmeler) {
				if (takimlar[k] == b.first or takimlar[k] == b.second) {
					cout << "MacID: " << macID[j - 1] << " (" << b.first << "," << b.second << ")\n";
				}
				if (j % 9 == 0 and hafta < 18) {
					cout << "\n" << hafta << ". Hafta\n";
					hafta++;
				}
				j++;
			}
		}
	}
}
