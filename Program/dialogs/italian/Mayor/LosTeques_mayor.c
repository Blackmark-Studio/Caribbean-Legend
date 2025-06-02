void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Hai il coraggio di venire qui?! Azione audace...","Come hanno fatto quegli stupidi a lasciare che un nemico invadesse?! È oltre la mia comprensione...","Beh, le mie guardie sono inutili se qualche idiota si aggira nella mia residenza..."),LinkRandPhrase("Cosa vuoi, bastardo?! I miei soldati ti hanno già rintracciato e non scapperai"+GetSexPhrase(", sporco pirata","sporco pirata")+"!","Sporco assassino, allontanati dalla mia residenza! Guardie!!!","Non ho paura di te, bastardo! Sarai impiccato, non te la caverai..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("I soldati non costano nulla...","Non mi prenderanno mai."),RandPhraseSimple("Chiudi la bocca, "+GetWorkTypeOfMan(npchar,"")+", o ti taglio la lingua e te la infilo in gola...","Ti direi, compagno: siediti tranquillo, e potresti vedere un altro giorno..."));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
    			dialog.text = "Nemico nella mia residenza! Allarme!!!";
				link.l1 = "Cavolo!";
				link.l1.go = "fight"; 
				break;
			}			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+" Signore. Io sono "+GetFullName(npchar)+", comandante della miniera di Lost-Tekes che è di proprietà di "+NationKingsName(npchar)+". Ora, sarebbe così gentile da dirmi lo scopo della sua visita, "+GetAddress_Form(NPChar)+".";
				link.l1 = "È la mia prima volta qui e vorrei saperne di più su questo insediamento e le sue leggi...";
				link.l1.go = "info";
				link.l2 = "Solo volevo salutarti, sto già partendo.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
				break;
			}
			dialog.text = "Di nuovo tu, Signore? Cosa vuoi ancora?";
			link.l1 = "Non è niente. Sto andando via.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = "Rispetto tale disciplina. Bene, allora ti metterò al corrente, visto che sei così interessato.\nLa miniera di Los-Teques è proprietà della Corona Spagnola. Qui estraiamo argento e minerale d'oro grezzo, così come pepite d'oro e d'argento. Tutto l'oro e l'argento appartengono alla Spagna e vengono trasportati nel Vecchio Mondo.\nLa miniera è ben sorvegliata, un'unità di soldati spagnoli d'élite è sempre di stanza qui. I pirati hanno fatto diversi tentativi di depredare la nostra miniera, ma le conseguenze sono sempre state gravi... per loro.\nCome puoi vedere, è una piccola città. Abbiamo una taverna e un negozio. Puoi acquistare lingotti d'oro e d'argento a un buon prezzo. Inoltre, il nostro intendente, che è anche un mercante nel negozio, può venderti altri metalli e minerali interessanti.\nLa maggior parte dei nostri lavoratori sono prigionieri, ma abbiamo anche una piccola quantità di schiavi neri. Come puoi vedere, abbiamo sempre bisogno di nuova manodopera, ogni giorno muore almeno uno di questi maledetti prigionieri.\nQuindi, se ci porti degli schiavi, li scambieremo con pepite. Contatta il nostro ingegnere capo per queste questioni. Puoi trovarlo nel pozzo.\nComportati bene qui. Non iniziare duelli o combattimenti, non cercare di rubare nulla, soprattutto oro o argento. Non abbiamo una prigione qui, ma abbiamo un tribunale militare.\nQuesto è più o meno tutto. Segui queste semplici regole e non avrai problemi. Sei autorizzato a muoverti liberamente all'interno della miniera. Non dimenticare di visitare la taverna, offrono certi... servizi con il mio permesso. Benvenuto!";
			link.l1 = "Grazie mille!";			
			link.l1.go = "exit";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = "Rapina!!! Questo è inaccettabile! Preparati, "+GetSexPhrase("amico","ragazza")+"...";
			link.l1 = LinkRandPhrase("Cazzo!","Carramba!!","Maledizione!");
			link.l1.go = "PL_Q3_fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
	}
}
