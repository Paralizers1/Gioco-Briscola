
#include <iostream>
#include <limits>
#include <vector>
using namespace std;
struct carta {
	int numero;
	string seme;
};




int NumeroCartaBriscola(int carta, bool punteggio = false) {
	//Trasformi il numero della carta in punteggio
	int punti = (punteggio ? 0 : carta); //dall'8 al 10
	switch(carta) {
	case 1:
		punti = 11;
		break;
	case 3:
		punti = 10;
		break;
	case 10:
		punti = 4;
		break;
	case 9:
		punti = 3;
		break;
	case 8:
		punti = 2;
		break;
	}
	return punti;
}

void mescolaMazzo(carta mazzo[]) {
	int posizioneCarta1,posizioneCarta2;
	for(int i=0; i<100; i++) {
		posizioneCarta1=rand()%40;
		posizioneCarta2=rand()%40;
		carta temp = mazzo[posizioneCarta1];
		mazzo[posizioneCarta1] = mazzo[posizioneCarta2];
		mazzo[posizioneCarta2] = temp;
	}
}



void rimuoviCarta(vector<carta> &c,carta n) {
	//Rimuovo una specifica carta dall'array di carte
	for(int i = 0; i<c.size(); i++) {
		//cout<<c[i].numero;
		if(c[i].numero == n.numero && c[i].seme == n.seme) {
			c.erase(c.begin()+i);
			break;
		}
	}
}








int chivince(carta cartaGiocatore, carta cartaBot, carta cartaBriscola, int primo = 0) {
	//1 se C( il giocatore 2 se C( il bot
	if(cartaBriscola.seme == cartaBot.seme && cartaBot.seme == cartaGiocatore.seme) {
		if(NumeroCartaBriscola(cartaBot.numero) > NumeroCartaBriscola(cartaGiocatore.numero)) {
			return 2;
		} else {
			return 1;
		}
	}
	else if(cartaBriscola.seme == cartaBot.seme && cartaBot.seme != cartaGiocatore.seme) {
		return 2;
	}
	else if(cartaBriscola.seme == cartaGiocatore.seme && cartaBot.seme != cartaGiocatore.seme) {
		return 1;
	}
	else if(primo) {
		if(primo == 1) {
			if(cartaGiocatore.seme == cartaBot.seme) {
				if(NumeroCartaBriscola(cartaBot.numero) > NumeroCartaBriscola(cartaGiocatore.numero)) {
					return 2;
				} else {
					return 1;
				}
			}
			else return 1;
		}
		else if(primo == 2) {
			if(cartaGiocatore.seme == cartaBot.seme) {
				if(NumeroCartaBriscola(cartaBot.numero) > NumeroCartaBriscola(cartaGiocatore.numero)) {
					return 2;
				} else {
					return 1;
				}
			}
			else return 2;
		}
	}
	return 0;
}









int mostraCarteGiocatore(vector<carta> CarteGiocatore) {
	//Funzione che stampa le carte del giocatore e lo fa giocare
	int cartaGiocata = 0;
	cout<<"Tu attualmente hai le seguenti carte: ";
	for(int i = 0; i<CarteGiocatore.size(); i++) {
		cout<<CarteGiocatore[i].numero<<" di "<<CarteGiocatore[i].seme<<"("<<(i+1)<<")"<<(i != (CarteGiocatore.size()-1) ? ", " : "");
	}
	cout<<endl;
	if(CarteGiocatore.size() > 0) {
		do {
			cout<<"Che carta vuoi giocare (1-3): ";
			cin>>cartaGiocata;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		} while(cartaGiocata == 0 || cartaGiocata < 1 || cartaGiocata > 3 || CarteGiocatore.size() < cartaGiocata);
		return cartaGiocata;
	}
	return 0;
}


int distribuisciCarte(carta mazzo[],int & carta_attuale,carta & cartaBriscola,vector<carta> & CarteGiocatore,vector<carta> & carteBot,vector<carta> & carta_giocate) {
	//Funzione per distribuire le carte ad inizio partita

	int i = 0;
	for(i; i<7; i++) {
		carta_giocate.push_back(mazzo[carta_attuale]);

		if(i>3) {
			CarteGiocatore.push_back(mazzo[carta_attuale]);
		}
		else if(i>0) {
			carteBot.push_back(mazzo[carta_attuale]);
		}
		else {
			cout << "La briscola e' "<<mazzo[carta_attuale].numero<<" di "<<mazzo[carta_attuale].seme<<endl<<endl;
			//carteTavolo.push_back(mazzo[carta_attuale]);
			cartaBriscola = mazzo[carta_attuale];
		}
		carta_attuale++;

	}
	return i;
}

void distribuisciTurno(carta mazzo[],int & carta_attuale,vector<carta> & CarteGiocatore,vector<carta> & carteBot,vector<carta> & carta_giocate, carta cartaBriscola, bool prendeBot) {
	//Funzione che distribuisce la carta ogni turno
	if(carta_attuale>40)return;
	carta_giocate.push_back(mazzo[carta_attuale]);
	(prendeBot ? carteBot : CarteGiocatore).push_back(mazzo[carta_attuale]);
	carta_attuale++;
	carta CartaBot;
	if(carta_attuale==40) {
		CartaBot = cartaBriscola;
	}
	else {
		CartaBot = mazzo[carta_attuale];
	}
	carta_giocate.push_back(CartaBot);
	(! prendeBot ? carteBot : CarteGiocatore).push_back(CartaBot);

	carta_attuale++;
}

void chigioca(vector<carta> & CarteGiocatore,vector<carta> & carteBot,vector<carta> & carta_giocate, carta & cartaGiocataBot, carta & cartaGiocataGiocatore,bool & primaBot) {
	//Funzione che controlla chi gioca
	int cartaRandom = rand()%carteBot.size();
	if(primaBot) {
		cout<<"Il bot sta giocando: "<<carteBot[cartaRandom].numero<<" di "<<carteBot[cartaRandom].seme<<endl;
		cartaGiocataBot = carteBot[cartaRandom];
		rimuoviCarta(carteBot,carteBot[cartaRandom]);
		int cartaGiocata = mostraCarteGiocatore(CarteGiocatore);
		cartaGiocata--;
		cartaGiocataGiocatore = CarteGiocatore[cartaGiocata];
		cout<<"Tu hai giocato: "<<CarteGiocatore[cartaGiocata].numero<<" di "<<CarteGiocatore[cartaGiocata].seme<<endl;
		rimuoviCarta(CarteGiocatore,CarteGiocatore[cartaGiocata]);
	}
	else {
		int cartaGiocata = mostraCarteGiocatore(CarteGiocatore);
		cartaGiocata--;
		cout<<endl<<"Tu hai giocato: "<<CarteGiocatore[cartaGiocata].numero<<" di "<<CarteGiocatore[cartaGiocata].seme<<endl;
		cartaGiocataGiocatore = CarteGiocatore[cartaGiocata];
		rimuoviCarta(CarteGiocatore,CarteGiocatore[cartaGiocata]);
		cout<<"Il bot sta giocando: "<<carteBot[cartaRandom].numero<<" di "<<carteBot[cartaRandom].seme<<endl;
		cartaGiocataBot = carteBot[cartaRandom];
		rimuoviCarta(carteBot,carteBot[cartaRandom]);
	}

	carta_giocate.push_back(cartaGiocataGiocatore);
	carta_giocate.push_back(cartaGiocataBot);
}




int main()
{
	int carta_attuale = 0;
	vector<carta> carte_giocate;
	vector<carta> CarteGiocatore;
	vector<carta> carteBot;
	vector<carta> CartePreseGiocatore;
	vector<carta> cartePreseBot;


	carta cartaBriscola;
	carta cartaGiocataBot;
	carta cartaGiocataGiocatore;
	bool primaBot = false;




	int puntiBot = 0;
	int puntiGiocatore = 0;
	int prendeBot = 0;

	srand (time(NULL));
	carta mazzo[40];
	string semi[4] = {"Denari","Bastoni","Spade","Coppe"};
	int conteggio = 0;
	for(int i = 0; i<40; i++) {
		if(i>0&&(i%10) == 0) {
			conteggio++;
		}
		mazzo[i].seme = semi[conteggio];
		mazzo[i].numero = i%10+1;
	}
	mescolaMazzo(mazzo);
	distribuisciCarte(mazzo,carta_attuale,cartaBriscola,CarteGiocatore,carteBot,carte_giocate);


	do {


		chigioca(CarteGiocatore,carteBot,carte_giocate,cartaGiocataBot,cartaGiocataGiocatore,primaBot);
		int p = chivince(cartaGiocataGiocatore, cartaGiocataBot, cartaBriscola, (primaBot ? 2 : 1));
		if(p == 1) {
			cout<< endl << "Mano vinta da te"<<endl<< endl;
			primaBot = false;
			CartePreseGiocatore.push_back(cartaGiocataGiocatore);
			CartePreseGiocatore.push_back(cartaGiocataBot);
		}
		else if(p == 2) {
			cout<< endl << "Mano vinta dal bot"<<endl<< endl;
			primaBot = true;
			cartePreseBot.push_back(cartaGiocataGiocatore);
			cartePreseBot.push_back(cartaGiocataBot);
		}
		distribuisciTurno(mazzo,carta_attuale,CarteGiocatore,carteBot,carte_giocate,cartaBriscola,primaBot);
	} while(carta_attuale <= 40||CarteGiocatore.size() > 0);



	int sizeBot= cartePreseBot.size();
	int sizeGiocatore= CartePreseGiocatore.size();
	cout<<"Il gioco e' finito:"<<endl;
	
	
	cout<<"Il Bot ha  preso le seguenti carte ("<<sizeBot<<"):";
	for(int i = 0; i<cartePreseBot.size(); i++) {
		puntiBot+=NumeroCartaBriscola(cartePreseBot[i].numero,true);
		cout << cartePreseBot[i].numero << " di "<<cartePreseBot[i].seme<<(i != sizeBot -1 ? ", " : "");
	}
	cout <<endl<<endl;
	
	
	
	cout<<"Tu hai  preso le seguenti carte ("<<sizeGiocatore<<") "<<endl;
	for(int i = 0; i<CartePreseGiocatore.size(); i++) {
		puntiGiocatore+=NumeroCartaBriscola(CartePreseGiocatore[i].numero,true);
		cout << CartePreseGiocatore[i].numero << " di "<<CartePreseGiocatore[i].seme<<(i != sizeGiocatore -1 ? ", " : "");
	}
	cout <<endl<<endl;



	cout<<endl<<"Punteggio Finale: Tu ("<<puntiGiocatore<<") , Bot("<<puntiBot<<")"<<(puntiBot > puntiGiocatore ? ", il Bot ha vinto!" : ", hai vinto!");
	cout << endl;
	return 0;
}