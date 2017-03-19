/*

#########################################################################################################################################################
##
##						Transmision protocol settings.

		Transmision encryption : XOR.
		XOR encryption key : piwo
				
		ramka komunikacji : polecenie 2 bajty, parametr 2 bajty.
		ramka powrotna    : odpowiedŸ 2 bajty, parametr 2 bajty.
		KA¯DA RAMKA ZAKONCZONA NIESZYFROWANYM ZNAKIEM NOWEJ LINII! k13 .
			
		Polecenia :
		
		ctXX - comm test xx, test komunikacji, zwraca odwrócon¹ waroœæ XX - ct01 zwróci re10
		onXX - za³¹cz wyjœcie nr xx. Zwrotnie okXX.
		ofXX - wy³¹cz wyjœcie nr xx. Zwrotnie okXX.
		csXX - check system XX - sprawdza system nr XX. Nr 00 wykonuje pe³en self-test.
		spXY - set parameter X-parametr, Y-wartoœæ.
		gpX0 - get parameter X0 wywo³uje wartoœæ parametru X, zwrotnie reXY X-parametr Y-wartoœæ.
		gi00 - get inputs status, zwrotnie reXY - wartoœæ wejœæ.
		go00 - get outputs status, zwrotnie reXY - wartoœæ ustawionych wyjœæ.
		erxx - info o b³êdzie + nr.
		stop - zablokowanie sterownika. Polecenie stop.
		strt - odblokowanie sterownika. Polecenie start.
				
		Informacja zwrotna : 
		
		reXX - odpowiedŸ XX-warotœæ odpowiedzi.
		okXX - potwierdzenie wykonania polecenia, XX wartoœæ potwierdzenia.
		
		
		gcc a xor b   = a^b.

*/