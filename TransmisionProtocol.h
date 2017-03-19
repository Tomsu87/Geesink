/*

#########################################################################################################################################################
##
##						Transmision protocol settings.

		Transmision encryption : XOR.
		XOR encryption key : piwo
				
		ramka komunikacji : polecenie 2 bajty, parametr 2 bajty.
		ramka powrotna    : odpowied� 2 bajty, parametr 2 bajty.
		KA�DA RAMKA ZAKONCZONA NIESZYFROWANYM ZNAKIEM NOWEJ LINII! k13 .
			
		Polecenia :
		
		ctXX - comm test xx, test komunikacji, zwraca odwr�con� waro�� XX - ct01 zwr�ci re10
		onXX - za��cz wyj�cie nr xx. Zwrotnie okXX.
		ofXX - wy��cz wyj�cie nr xx. Zwrotnie okXX.
		csXX - check system XX - sprawdza system nr XX. Nr 00 wykonuje pe�en self-test.
		spXY - set parameter X-parametr, Y-warto��.
		gpX0 - get parameter X0 wywo�uje warto�� parametru X, zwrotnie reXY X-parametr Y-warto��.
		gi00 - get inputs status, zwrotnie reXY - warto�� wej��.
		go00 - get outputs status, zwrotnie reXY - warto�� ustawionych wyj��.
		erxx - info o b��dzie + nr.
		stop - zablokowanie sterownika. Polecenie stop.
		strt - odblokowanie sterownika. Polecenie start.
				
		Informacja zwrotna : 
		
		reXX - odpowied� XX-warot�� odpowiedzi.
		okXX - potwierdzenie wykonania polecenia, XX warto�� potwierdzenia.
		
		
		gcc a xor b   = a^b.

*/