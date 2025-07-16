// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Tutte le voci di "+GetCityName(npchar.city)+" al vostro servizio. Cosa vorreste scoprire?","Stavamo proprio parlando di questo. Devi aver dimenticato...","È la terza volta oggi che parli di qualche domanda...","Ripeti sempre le stesse cose come un pappagallo...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sai, "+NPChar.name+", forse la prossima volta.","Giusto, per qualche motivo ho dimenticato...","Sì, è davvero la terza volta...","Sì...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//работорговец
			if (pchar.questTemp.Slavetrader == "EscapeSlave_Villemstad")
            {
                link.l1 = "Ho sentito dire che c'è stato un bel casino sull'isola... Schiavi?";
                link.l1.go = "EscapeSlaveVillemstad_T1";
            }
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "SeekPortVillemstad")
            {
                link.l1 = "Ho sentito dire che quel maledetto furfante Bart il Portoghese ha finalmente incontrato la giustizia! È in prigione? Quando sarà la sua esecuzione, lo sai? Voglio venire a guardare, ho un conto in sospeso con quel lurido...";
                link.l1.go = "Portugal";
            }
			//--> Тайна Бетси Прайс
			if (CheckAttribute(pchar, "questTemp.TBP_Tavern"))
			{
				link.l1 = "Ascolta, "+npchar.name+", Ho sentito dire che di recente avete avuto una nuova bellissima cameriera... ed è già sparita?";
				link.l1.go = "TBP_Tavern_1";
			}
			if (CheckAttribute(pchar, "questTemp.TBP_Tavern2"))
			{
				link.l1 = "Dimmi, "+npchar.name+", la notte in cui Betsy è scomparsa, hai notato qualcuno di sospetto vicino a lei? Forse stava parlando con qualcuno?";
				link.l1.go = "TBP_Tavern2_11";
			}
			if (CheckAttribute(pchar, "questTemp.TBP_Tavern3"))
			{
				link.l1 = "Bene, "+npchar.name+", buone notizie - la tua preziosa cameriera è viva e vegeta. Dovrai rifornire il tuo rum, la gente tornerà presto.";
				link.l1.go = "TBP_Tavern3_21";
			}
			//<-- Тайна Бетси Прайс
 		break;

		//работорговец
		case "EscapeSlaveVillemstad_T1":
			dialog.text = "Sì, non c'è mai stato un tale disastro... Più di mille negri si sono ribellati. Due piantagioni sono state bruciate fino al suolo e ciascuno dei loro padroni è stato assassinato. Il comandante teme che gli schiavi possano attaccare la città, quindi ha imposto la legge marziale. E tutto è iniziato a causa di due negri, un maschio di nome Tamango e una femmina di nome Isauri...";
			link.l1 = "Sembra piuttosto drammatico. Raccontami tutta la storia, chi sono questi negri?";
			link.l1.go = "EscapeSlaveVillemstad_T2";
		break;
		
		case "EscapeSlaveVillemstad_T2":
				dialog.text = "Tamango e Izaura - schiavi nella piantagione di Blenheim, la prima piantagione a essere bruciata. Questi due negri si amavano. Ma un figlio del padrone, Leonsio, arrivato dall'Europa, si prese una cotta per la femmina. Voleva fare di Izaura la sua concubina personale. Il negro robusto Tamango non gradì l'idea e nemmeno Izaura, che amava davvero il diavolo nero\nTamango era una sorta di capo o qualcosa del genere in Africa... Un robusto gigante - più nero del peccato e mortale con un'ascia, gli altri negri lo temevano e lo rispettavano. Così questo negro guidò gli altri schiavi in una rivolta. Attaccarono le guardie di notte, uccisero tutti i bianchi fuori dalla grande casa, anche i mulatti\nPoi Izaura aprì le porte della piantagione e le scimmie selvagge assassinarono tutti all'interno. Blenburg fu bruciata fino al suolo. Poi gli schiavi fuggirono nelle giungle e sparirono...";
			link.l1 = "Ebbene, che ne pensi di questa storia, sembra la trama di un romanzo! Una vera rivolta degli schiavi, proprio come nell'Antica Roma. Come hai scoperto tutto questo, a proposito?";
			link.l1.go = "EscapeSlaveVillemstad_T3";
		break;
		
		case "EscapeSlaveVillemstad_T3":
			dialog.text = "Pettegolezzi, signore, la terra ne è piena. Il rum scioglie le lingue, tutto quello che devi fare è ascoltare...";
			link.l1 = "E come è finita tutta questa storia? Hanno trovato quei negri?";
			link.l1.go = "EscapeSlaveVillemstad_T4";
		break;
		
		case "EscapeSlaveVillemstad_T4":
				dialog.text = "Ah, nemmeno per sogno! Finché i rinforzi non sono finalmente arrivati, nessuno ha messo piede nella giungla. Poi è arrivata una nave da guerra della Compagnia con un'unità di soldati e hanno perlustrato l'isola. Non hanno trovato né pelle nera né capelli ricci di un solo negro fuggitivo.";
			link.l1 = "Allora, come mai! Mille negri sono tutti spariti nel nulla?";
			link.l1.go = "EscapeSlaveVillemstad_T5";
		break;
		
		case "EscapeSlaveVillemstad_T5":
			dialog.text = "Effettivamente nell'acqua.";
			link.l1 = "Di cosa stai parlando, "+npchar.name+"? Sai bene quanto me che i negri non sanno nuotare.";
			link.l1.go = "EscapeSlaveVillemstad_T6";
		break;
		
		case "EscapeSlaveVillemstad_T6":
			dialog.text = "Ehehe... oh no, quei neri non sono diventati pasto per gli squali così facilmente. La questione è che la notte successiva alla rivolta, una barca è scomparsa dal molo. Puoi dipingermi di nero e suonerò il banjo e danzerò per te se non fosse stato per quel cervo Tamango e i suoi negri! Ecco perché non sono più sull'isola.";
			link.l1 = "Ah, ora ho sentito di tutto, "+npchar.name+". Ti aspetti che io creda che un gruppo di negri semi-selvaggi possa gestire le vele e navigare? Mi aspetterei prima una nave di scimmie proveniente dalla Guinea.";
			link.l1.go = "EscapeSlaveVillemstad_T7";
		break;
		
		case "EscapeSlaveVillemstad_T7":
			dialog.text = "Non ci credevo neanche io, signore, ma la prova è nella nave scomparsa. Forse uno di quei negri ha servito come steward su una nave e ha appreso qualche tecnica di navigazione. Forse hanno usato la magia nera, chissà! Passa a trovarmi di nuovo, "+pchar.name+", la prossima volta avrò altre storie per te.";
			link.l1 = "Grazie! Beh, è ora per me di andare.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "22_2");
			pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_P";
		break;						

		case "Portugal":
			dialog.text = "Sì, è vero. Hanno catturato quel pirata. E riesci a credere come? È stato raccolto su una scialuppa da solo in mezzo al mare. Non ha nemmeno emesso un lamento prima di essere mandato nella stiva per i ratti. È davvero divertente, sai, un pirata così pericoloso è stato catturato come un semplice marinaio!";
			link.l1 = "E perché era tutto solo in mare?";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Probabilmente ha deciso di separarsi dai suoi scagnozzi, senza dubbio... Non riuscivano a dividere equamente il bottino. Ora è nelle mani della stessa Compagnia e quei ragazzi non tollerano gli scherzi. Dicono che si sia impadronito di una delle barche della Compagnia con qualcosa di prezioso. A quanto pare, se non è già appeso a una forca è solo perché vogliono strappargli qualche informazione.";
			link.l1 = "Allora, quando sarà la sua esecuzione, lo sai?";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Nessuno lo sa. Penso che una volta che la Compagnia scoprirà cosa vuole, gli allacceranno una cravatta di canapa al collo. Il portoghese è in prigione ora sotto una guardia affidabile\nDi recente hanno portato anche il suo nostromo qui. La sua storia era ancora più sorprendente, si è consegnato ai olandesi a Philipsburg. Così, lo hanno sistemato in una cella proprio accanto al suo ex-capitano, quindi ora sono vicini, ah-ah...";
			link.l1 = "I miracoli accadono! Va bene, starò attento alle notizie. Non voglio perdere quella impiccagione. Addio, "+npchar.name+"!";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			DialogExit();
			pchar.questTemp.Portugal = "PortugalInPrison";
			AddQuestRecord("Portugal", "32");
		break;
		
		//--> Тайна Бетси Прайс
		case "TBP_Tavern_1":
			dialog.text = "Oh, se solo l'avessi vista, Capitano! Betsy... tale grazia, tale sorriso! Gli uomini accorrevano qui solo per guardarla. E l'argento che lasciavano nella mia taverna... Ma tre giorni fa, non si è presentata al lavoro. Naturalmente ho mandato gente a casa sua, ma non c'è. Il posto è un disastro, i suoi effetti personali sono spariti\nNon so più cosa pensare. Le guardie, come sempre, hanno fatto spallucce. Hanno detto che hanno cose più importanti da fare che cercare una ragazza scomparsa. Hanno detto che probabilmente è solo uscita e tornerà presto. Capitano, forse potresti trovarla? Se la riporti qui, ti pagherò cento dobloni. Non posso semplicemente perderla, capisci? È un vero tesoro! Devo riaverla a tutti i costi!";
			link.l1 = "Vediamo cosa posso fare. Si è comportata in modo strano prima di sparire, o ha ricevuto qualche brutta notizia?";
			link.l1.go = "TBP_Tavern_2";
			link.l2 = "Cercare una ragazza che probabilmente è appena scappata? Ho cose migliori da fare. Risolvilo da solo.";
			link.l2.go = "TBP_Tavern_End";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern_End":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.TBP_Tavern");
			CloseQuestHeader("TBP");
		break;

		case "TBP_Tavern_2":
			dialog.text = "Nel suo ultimo giorno prima di scomparire, se ne andò di buon umore, addirittura felice! Nessun segno di problemi, non una parola sulla partenza. È semplicemente svanita!";
			link.l1 = "Interessante... Dove posso trovare la sua casa?";
			link.l1.go = "TBP_Tavern_3";
		break;

		case "TBP_Tavern_3":
			dialog.text = "Lei viveva più avanti per la strada, in una baracca proprio dietro la casa di fronte alla villa con il balcone blu. Non è lontano da qui.";
			link.l1 = "Ebbene, non perderò tempo. Se trovo qualcosa, ti farò sapere.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_Poorman");
		break;

		case "TBP_Tavern2_11":
			dialog.text = "Sospetto? C'erano sempre folle di pretendenti attorno a lei, e ognuno sospetto a modo suo! Era una gran seduttrice, sapeva come attirare l'attenzione.";
			link.l1 = "Questo l'ho capito"+GetSexPhrase(""," fuori")+" già. Ma c'era qualcuno che si distingueva?";
			link.l1.go = "TBP_Tavern2_12";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern2_12":
			dialog.text = "Mmm... Beh, c'era uno. Quella sera, le ha dato un ciondolo con gemme. Siedeva qui, gli occhi incollati a lei, svolazzava per tutta la notte.";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon"))
			{
				link.l1 = "Quel pendente, per caso, non sarebbe questo? (Mostra il cammeo comprato dal mendicante)";
				link.l1.go = "TBP_Tavern2_13";
			}
			else
			{
				link.l1 = "Ciondolo con gemme, dici ...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("TBP_SearchHouseWithFonar");
			}
		break;

		case "TBP_Tavern2_13":
			dialog.text = "Ecco lui! Esatto! Capitano, hai già trovato qualcosa?";
			link.l1 = "Dettagli dopo, "+npchar.name+", adesso non c'è tempo da perdere.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_SearchHouseWithFonar");
			RemoveItems(pchar, "jewelry24", 1); 
			notification("Given: Cameo pendant", "None");
		break;

		case "TBP_Tavern3_21":
			dialog.text = "È fantastico, Capitano! Stavo cominciando a pensare che non l'avrei mai più vista. Quindi cosa è successo? Voleva davvero scappare?";
			link.l1 = "Diciamo solo che ha dovuto affrontare alcuni problemi del suo passato. Ma sembra che ora sia tutto alle sue spalle, e presto tornerà al lavoro.";
			link.l1.go = "TBP_Tavern3_22_leadership";
			link.l2 = "Bene, diciamo che aveva bisogno di una piccola pausa dal guardare la tua noiosa faccia. Ah-ah! Non fare il broncio, sto scherzando. Ogni signora dovrebbe avere i suoi piccoli segreti...";
			link.l2.go = "TBP_Tavern3_22_fortune";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern3_22_leadership":
			dialog.text = "Ebbene, la cosa più importante è che tornerà al lavoro. Ti sei guadagnato la tua ricompensa, Capitano. Eccola, prendila - cento dobloni, come concordato. Inoltre, prendi questa mappa. Uno dei clienti l'ha lasciata qui e non è mai tornato. Sembra che porti a un tesoro.";
			link.l1 = "Allora, lo controllerò. Grazie.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddItems(pchar, "gold_dublon", 100);
			GiveItem2Character(PChar, "map_full");
		break;

		case "TBP_Tavern3_22_fortune":
			dialog.text = "Bene, l'importante è che tornerà al lavoro. Hai guadagnato la tua ricompensa, Capitano. Eccola - cento dobloni, come concordato. Inoltre, prendi questa mappa. Uno dei clienti l'ha lasciata qui e non è mai tornato. Sembra che porti a un tesoro.";
			link.l1 = "Allora, lo controllerò. Grazie.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddItems(pchar, "gold_dublon", 100);
			GiveItem2Character(PChar, "map_full");
		break;
		//<-- Тайна Бетси Прайс
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
