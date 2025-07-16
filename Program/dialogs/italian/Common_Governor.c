// boal 25/04/04 общий диалог Governor
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Governor\" + NationShortName(sti(NPChar.nation)) + "_Governor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    
    ref offref, sld;
    int i, cn;
    int qty;
    int iSumm;
    string attrLoc;

    /// выкуп колонии
    ref CaptGovenor, FortColony;
    int f, colony_money;

    int k = 1000;
    if (CheckAttribute(Nations[sti(NPChar.nation)], "Fort"))
    {
        k = (300 - sti(Nations[sti(NPChar.nation)].Fort)*10);
    }
	bool ok;
	
	attrLoc = Dialog.CurrentNode;
	if (findsubstr(attrLoc, "CityGive_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.quest.CityIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "ColonyGive";
 	}
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Osate mostrare il vostro volto nell'ufficio del governatore generale?! Siete davvero pazzi...","Come hanno fatto questi fannulloni a lasciare che un nemico irrompesse nella mia residenza? Questo va oltre la mia comprensione...","Certo, le mie guardie non valgono un soldo se qualche vagabondo si aggira nella mia residenza..."),LinkRandPhrase("Di cosa hai bisogno, "+GetSexPhrase("verme","puzzolente")+"?! I miei soldati sono già sulle tue tracce, "+GetSexPhrase("sporco pirata","puzzolente")+"!",""+GetSexPhrase("Sporco","Sporco")+" assassino, lascia immediatamente la mia residenza! Guardie!","Non ho paura di te, "+GetSexPhrase("farabutto","birbante")+"! Presto sarai impiccato nel nostro forte, non andrai lontano..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("I soldati non valgono un cazzo...","Non mi prenderai mai."),RandPhraseSimple("Taci, amico, o strapperò quella tua lingua fetida!","Te lo dico, compagno: siediti tranquillo o ti taglierò la testa e la lancerò attraverso quella porta ai tuoi cani da guardia..."));
				link.l1.go = "fight";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ho sentito dire che hai insistito molto per ottenere un'udienza. Il mio nome è "+GetFullName(npchar)+". Sono il governatore generale delle colonie di "+NationNameGenitive(sti(NPChar.nation))+", vice della Corona di "+NationKingsName(npchar)+" in queste acque. Ora, per favore, sareste così gentili da dirmi, qual è lo scopo della vostra visita, "+GetAddress_Form(NPChar)+".";
				link.l1 = "Mi chiamo "+GetFullName(pchar)+".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple("Oh, sei tu di nuovo? Beh, cosa vuoi dal governatore generale di "+NationNameGenitive(sti(NPChar.nation))+" questa volta?","E di nuovo, mi stai distogliendo da affari di stato importanti? Cosa vuoi, "+GetAddress_Form(NPChar)+"?");
				link.l1 = "Voglio parlare con te del lavorare nel nome della Corona di "+NationNameGenitive(sti(NPChar.nation));
				link.l1.go = "work";
				link.l2 = "Ho bisogno di parlare con te di un affare importante.";
				link.l2.go = "quests"; // файл нации
				//Jason --> Регата
				if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
				{
					link.l3 = "Sono venuto su invito a partecipare alla regata. Ecco il mio invito.";
					link.l3.go = "Regata";
				}
				//<-- Регата
				link.l10 = "Mi dispiace, ma ho degli affari da sbrigare.";
				link.l10.go = "exit";
			}
		break;
		
		case "node_1":
			dialog.text = "Allora, qual era il motivo per cui sei venuto qui a distrarmi dalle importanti questioni di stato?";
			link.l1 = "Volevo parlarti del lavoro in nome della Corona di "+NationNameGenitive(sti(NPChar.nation));
			link.l1.go = "work";
			link.l2 = "Stavo per parlarti di un affare importante.";
			link.l2.go = "quests";
			//Jason --> Регата
			if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
			{
				link.l3 = "Sono venuto qui per partecipare alla regata. Ecco il mio invito.";
				link.l3.go = "Regata";
			}
			//<-- Регата
			link.l10 = "È solo una visita di cortesia, niente di più, "+GetAddress_FormToNPC(NPChar);
			link.l10.go = "node_2";
		break;

		case "node_2":
			dialog.text = "In tal caso ti chiederei di lasciare il mio ufficio e smettere di distrarmi dal mio lavoro.";
			link.l1 = "Sì, sì, naturalmente. Scusa per il disturbo.";
			link.l1.go = "exit";
		break;
		
		case "work":
            dialog.text = "Se cerchi lavoro, parla con i governatori delle colonie. Hanno spesso bisogno di capitani intelligenti e coraggiosi.";
			link.l1 = "Lo terrò a mente. Grazie.";
			link.l1.go = "exit";
		break;
		
		//--> Jason регата
		case "Regata":
			dialog.text = "Oh, ottimo, felice di vederti, capitano! Sei arrivato proprio in tempo - la regata sta per iniziare tra pochi giorni. Hai letto le regole della regata nella lettera che ti deve essere stata consegnata dal messaggero?";
			link.l1 = "Sì, signore, l'ho fatto.";
			link.l1.go = "Regata_1";
			RemoveItems(PChar, "letter_open", 1);//уберем письмо
			TakeNationLicence(HOLLAND);//уберем лицензию
			DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
		break;
		
		case "Regata_1":
			dialog.text = "E hai preparato 50000 pesos - la tua tassa d'ingresso, che contribuirà al montepremi?";
			if (makeint(Pchar.money) >= 50000)
			{
				link.l1 = "Sì, certo. Per favore, accetta il mio compenso.";
				link.l1.go = "Regata_2";
			}
			link.l2 = "Al momento sono un po' a corto di soldi. Ma porterò sicuramente il più veloce che posso.";
			link.l2.go = "Regata_nomoney";
		break;
		
		case "Regata_2":
			dialog.text = "Molto bene. Se vinci - i tuoi soldi torneranno a te quintuplicati. Ora, dovresti sapere come non infrangere le regole della regata.\nDiscuti i dettagli con Henry Stevenson, dovrebbe essere nella stanza della residenza. Incontralo, lui ti spiegherà tutto.";
			link.l1 = "Bene. Farò come dici tu.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			pchar.quest.Regata_Guber.win_condition.l1 = "location";
			pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
			pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
			pchar.questTemp.Regata.Begin = "true";
			NextDiag.TempNode = "First time";
		break;
		
		case "Regata_nomoney":
			dialog.text = "Bene, ma per favore non impiegare troppo tempo, capitano. La regata sta per iniziare presto.";
			link.l1 = "Capisco. Cercherò di portarti i soldi prima che inizi la regata.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_1";
			pchar.questTemp.Regata.nomoney = "true";
		break;
		
		//регата-финал
		case "Regata_Final":
			dialog.text = "E qui abbiamo il vincitore della regata! Ciao, capitano "+GetFullName(pchar)+"! Permettimi di congratularmi con te per questo successo meritato! I vincitori della regata sono sempre popolari nelle colonie inglesi, meritatamente popolari.";
			link.l1 = "Grazie, signore!";
			link.l1.go = "Regata_complete";
		break;
		
		case "Regata_complete":
			dialog.text = "Ora passiamo alla parte più piacevole per te - la cerimonia di premiazione. Il primo premio in denaro è di 250000 pesos. Ecco a te!";
			link.l1 = "Grazie!";
			link.l1.go = "Regata_complete_1";
		break;
		
		case "Regata_complete_1":
			AddMoneyToCharacter(pchar, 250000);
			int iGift;
			string sItem1, sItem2, sItem3, sAdd;
			
			iGift = 3;
			switch (iGift)
			{
				case 0:
					sItem1 = "blade_10";//корд
					sItem2 = "cirass6";
					sItem3 = "bussol";
					sAdd = "cord, duelist's vest and boussole";
				break;
				
				case 1:
					sItem1 = "blade_15";//маринера
					sItem2 = "cirass2";//рейтарский панцирь
					sItem3 = "bussol";
					sAdd = "marinera, reiter's armour and boussole";
				break;
				
				case 2:
					sItem1 = "blade_17";//бретта
					sItem2 = "cirass7";//карацена
					sItem3 = "bussol";
					sAdd = "bretta, karacena and boussole";
				break;
				
				case 3://
					sItem1 = "blade_20";//мадонна
					sItem2 = "cirass2";//офицерская кираса
					sItem3 = "bussol";
					sAdd = "'Madonna', officer's cuirass and boussole";
				break;
			}
			GiveItem2Character(pchar, sItem1);
			GiveItem2Character(pchar, sItem2);
			GiveItem2Character(pchar, sItem3);
			dialog.text = "Inoltre, hai diritto a un set di premi preziosi: "+sAdd+". Ora è tutto tuo.";
			link.l1 = "Sono molto contento, signore! Davvero, non me l'aspettavo.";
			link.l1.go = "Regata_complete_2";
		break;
		
		case "Regata_complete_2":
			dialog.text = "A nome di tutte le colonie inglesi, mi fa piacere ringraziarvi per aver partecipato alla regata e ancora una volta vi congratulo per la vostra vittoria! Se avete fatto una scommessa, ora è il momento perfetto per vedere Sir Henry Stevenson e riscuotere le vostre vincite, se non lo avete già fatto. Buona fortuna a voi, capitano!";
			link.l1 = "Grazie per le vostre gentili parole, signore! A mia volta, permettetemi di ringraziarvi per avermi dato l'opportunità di partecipare a un evento così grandioso. E ora, vi prego di permettermi di salutarvi e andare.";
			link.l1.go = "Regata_complete_3";
		break;
		
		case "Regata_complete_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
		break;
		//<-- регата
	}
}
