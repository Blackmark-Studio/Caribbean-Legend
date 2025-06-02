#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	switch(Dialog.CurrentNode)
	{
		case "First time":
			// --> калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.SeekAmulet") && hrand(1) == 0 && sti(Pchar.money) >= 2000) 
			{
				dialog.text = "Guarda, signore, non vuoi comprare una piccola cosa divertente? È economica, solo qualche migliaio di pesos ...";
				link.l1 = "Mmm. Probabilmente hai rubato questa 'cosetta', e ora stai cercando di disfartene?";
				link.l1.go = "caleuche";
				break;
			}
			// <-- калеуче
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("Ciao. Il mio nome è "+GetFullName(npchar)+". Non immagino che tu sia contento di incontrarmi, ma, forse, almeno ricorderai il mio nome...","Saluti, "+GetAddress_Form(NPChar)+". Il mio nome è "+GetFullName(npchar)+".","Il mio nome è "+GetFullName(npchar)+", "+GetAddress_Form(NPChar)+". Piacere di conoscerti.");
				link.l1 = RandPhraseSimple("Saluti.","Ciao.");
				link.l1.go = "First time";
				// карибские нравы
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					link.l2 = "Ehi, ascolta, vorresti guadagnare un paio di migliaia di pesos invece di queste patetiche elemosine?";
					link.l2.go = "trial";
				}
				// --> Тайна Бетси Прайс
				if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon3") && pchar.location == "Villemstad_town")
				{
					link.l2 = "Quel pendente con un cammeo... Dove l'hai trovato?";
					link.l2.go = "TBP_Kulon_1";
				}
				// <-- Тайна Бетси Прайс
				npchar.quest.meeting = "1";
			}			
			else
			{
				dialog.text = NPCStringReactionRepeat("Guarda quanto sono caduto in basso...","Vivere di elemosina non è facile...","Darei tutto per sfuggire a questa povertà!","Di nuovo tu?..","block",1,npchar,Dialog.CurrentNode);

				link.l1 = HeroStringReactionRepeat("Capisco. Beh, non è un grande problema.","Certo. Beh, sai, il più grande uomo della storia era il più povero.","Allora dovresti iniziare a fare qualcosa, non stare seduto qui tutto il giorno.","Ah-ha. Ti sto già infastidendo?",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "pester", npchar, Dialog.CurrentNode);
				link.l2 = RandPhraseSimple("Di cosa hai bisogno?","Cosa vuoi?");
				link.l2.go = "Whants";
				// карибские нравы
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					DelLandQuestMark(npchar);
					link.l2 = "Ehi, ascolta, vorresti guadagnare un paio di migliaia di pesos invece di queste patetiche elemosine?";
					link.l2.go = "trial";
				}
				// --> Тайна Бетси Прайс
				if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon3") && pchar.location == "Villemstad_town")
				{
					link.l2 = "Quel ciondolo con gemme... Dove l'hai trovato?";
					link.l2.go = "TBP_Kulon_1";
				}
				// <-- Тайна Бетси Прайс
				link.l3 = LinkRandPhrase("Potresti dirmi qualcosa di interessante?","Cosa c'è di nuovo in città?","Oh, mi piacerebbe sentire gli ultimi pettegolezzi...");
				link.l3.go = "rumours_poor";
			}
			NextDiag.TempNode = "First time";
		break;
		case "pester":
			dialog.text = RandPhraseSimple("No, perché, già infastidito? Non sono particolarmente occupato, come puoi vedere...","Mi rende solo stanco. Sebbene povero, sono ancora un uomo.");
			link.l1 = "Eh, capisco...";
			link.l1.go = "exit";
		break;
		//выходы
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//милостыня
		case "Whants":
			if (!CheckAttribute(npchar, "wants_date") || GetNpcQuestPastDayParam(npchar, "wants_date") >= 1 || bBettaTestMode)
    		{
				dialog.text = PCharRepPhrase("Mmm, "+GetAddress_Form(NPChar)+", la gente dice un sacco di brutte cose su di te. Ma io continuo a credere nelle persone - anche in quelle come te. Per favore, dammi l'elemosina per il pane e l'acqua, abbi pietà di me.","Ti prego, "+GetAddress_Form(NPChar)+"! Per favore, non voltarti via da un povero uomo, fai l'elemosina per un pasto...");
				link.l1 = RandPhraseSimple("Non ti darò nulla.","Ce la farai senza soldi.");
				link.l1.go = "exit";
				Link.l2 = "Bene, e di quanto hai bisogno?";
				Link.l2.go = "Whants_1";
			}
			else
			{
				dialog.text = PCharRepPhrase("Da te? Niente.","Non ho bisogno di nulla, "+GetAddress_Form(NPChar)+", grazie.");
				link.l1 = RandPhraseSimple("Mmm, va bene.","Sembra che la tua vita non sia poi così male, compagno.");
				link.l1.go = "exit";
			}
		break;
		case "Whants_1":
			dialog.text = "Non rifiuterei nemmeno un misero rame, "+GetAddress_Form(NPChar)+". Quanto la tua borsa e la tua misericordia possono dare...";
			Link.l1.edit = 2;			
			link.l1 = "";
			link.l1.go = "Whants_2";
		break;
		case "Whants_2":
			SaveCurrentNpcQuestDateParam(npchar, "wants_date");
			int iTemp = sti(dialogEditStrings[2]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "Prendersi gioco dei deboli e stanchi è un peccato...";
				link.l1 = "Ah-ah-ah! Hai pensato per un momento che ti avrei dato dei soldi, te mendicante pazzo?!";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", -2);
				break;
			}
			if (iTemp > 0 && iTemp <= 100)
			{
				dialog.text = "Grazie per "+FindRussianMoneyString(iTemp)+", "+GetAddress_Form(NPChar)+". Ora posso comprare del pane con quei soldi...";
				link.l1 = "Eccoti, vagabondo - vai a rinvigorirti un po'.";
				link.l1.go = "exit";
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 100 && iTemp <= 500)
			{
				dialog.text = "Grazie, "+GetAddress_Form(NPChar)+". Ora posso vivere una settimana con quei soldi!";
				link.l1 = "È stato un piacere aiutare.";
				link.l1.go = "exit";
				OfficersReaction("good");
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 500 && iTemp <= 1000)
			{
				dialog.text = "Grazie, "+GetAddress_Form(NPChar)+". Racconterò a tutti della tua gentilezza!";
				link.l1 = "Non è davvero necessario.";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", iTemp/2000.0+0.5);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 1000 && iTemp <= 5000)
			{
				dialog.text = "Grazie, rispettato "+GetSexPhrase("signore","signora")+" "+GetAddress_Form(NPChar)+". Che il Signore vegli su di te...";
				link.l1 = "Sì, la Sua protezione di certo non farebbe male!";
				link.l1.go = "exit";
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), iTemp/10000.0+0.5);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 5000 && iTemp <= 10000)
			{
				dialog.text = "Grazie, "+GetSexPhrase("signore molto stimato","signora molto stimata")+" "+GetAddress_Form(NPChar)+". Ti auguro tutto il meglio!";
				link.l1 = "Grazie, compagno.";
				link.l1.go = "exit";
				AddCharacterExpToSkill(pchar, "Leadership", iTemp/5000.0);
				AddCharacterExpToSkill(pchar, "Fortune", iTemp/5000.0);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
                 if (iTemp > 10000 && iTemp < 25000)
			{
				dialog.text = "Ascolta, "+GetAddress_Form(NPChar)+", sei pazzo o cosa? Mi stai dando "+FindRussianMoneyString(iTemp)+"! Non posso accettare tali soldi, sicuramente c'è un tranello... Lasciami stare!";
				link.l1 = "Beh, come desideri...";
				link.l1.go = "exit";
			}
                 if (iTemp == 25000)
			{
				dialog.text = "Venticinquemila accettati ... Questi soldi saranno sufficienti per Lelya ed io per un intero anno!";
				link.l1 = "Vivi prima quest'anno...";
				link.l1.go = "exit";
			}
			if (iTemp > 25000)
			{
				dialog.text = "Ascolta, "+GetAddress_Form(NPChar)+", sei pazzo o cosa? Mi stai dando "+FindRussianMoneyString(iTemp)+"! Non posso accettare tali soldi, sicuramente c'è un tranello... Lasciami stare!";
				link.l1 = "Bene, come vuoi tu...";
				link.l1.go = "exit";
			}
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			dialog.text = "Una domanda sciocca, signore! Ovviamente, lo farei! Ma... cosa dovrò fare? Certamente non mi darai quei soldi solo per il mio bel sorriso.";
			link.l1 = "Certo che no. Ascolta ora. Sto agendo per conto del governatore stesso. Sua Grazia sospetta che qualcuno nel cantiere navale stia sabotando deliberatamente il lancio dell''Alacantara', la sua galea. E i suoi sospetti sono diventati più forti dopo che recentemente è stato catturato una spia francese...";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "";
			link.l1 = "Sua Grazia ha già sentito le scuse del costruttore navale, ma non è sicuro che stesse dicendo la verità. Dobbiamo scoprire chi sta sabotando il lavoro e perché. Vai ai moli, dai un'occhiata in giro e chiedi ai lavoratori, perché diavolo 'Alacantara' non è ancora pronta per salpare...";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "";
			link.l1 = "Nessuno ti sospetterà, potresti anche metter le mani su una pila di tabacco. Per quanto mi riguarda, nessuno mi dirà nulla. Tutti sapranno per chi sto lavorando. Se riesci a scoprire qualcosa di degno, riceverai tremila pesos. Abbastanza per abbandonare il tuo 'lavoro' per almeno un mese.";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			dialog.text = "Tre mila pesos? Ma, stimato signore...";
			link.l1 = "Stai contrattando con me o cosa? Ah, e se scopri chi è dietro a tutto questo indugio, riceverai altri duemila. Affare?";
			link.l1.go = "trial_4";
		break;
		
		case "trial_4":
			dialog.text = "Va bene, signore. Non dovrebbe essere troppo difficile - molti dei miei vecchi amici lavorano ai moli in questi giorni. Ehi, ero anche io un marinaio molto tempo fa. Tipo, dieci anni fa...";
			link.l1 = "Potrai raccontarmi la tua storia più tardi. Incontrami sul molo di notte dopo le undici. Ora vai.";
			link.l1.go = "trial_5";
		break;
		
		case "trial_5":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.Trial = "spy_poorman";
			pchar.quest.trial_spy_poorman.win_condition.l1 = "Timer";
			pchar.quest.trial_spy_poorman.win_condition.l1.date.hour  = 22.00;
			pchar.quest.trial_spy_poorman.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.trial_spy_poorman.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.trial_spy_poorman.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.trial_spy_poorman.function = "Trial_SetPoormanInPort";
			pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1 = "Timer";
			pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1.date.hour  = 6.00;
			pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Trial_ReturnPoormanNorm.win_condition = "Trial_ReturnPoormanNorm";
			//SetTimerCondition("Trial_ReturnPoormanNorm", 0, 0, 1, false);
			AddQuestRecord("Trial", "15");
		break;
		
		case "trial_6":
			dialog.text = "Buonasera, signore...";
			link.l1 = "Allora? Hai scoperto qualcosa?";
			link.l1.go = "trial_7";
			DelLandQuestMark(npchar);
		break;
		
		case "trial_7":
			dialog.text = "L'ho fatto, signore, l'ho fatto. Non sono sicuro di come si concili tutto con quello che mi hai detto... Hai portato i soldi? Cinquemila pesos.";
			if (sti(pchar.money) >= 5000)
			{
				link.l1 = "Non preoccuparti. Ecco i tuoi soldi. Ora sputalo fuori.";
				link.l1.go = "trial_8";
			}
			else
			{
				link.l1 = "Prima le informazioni, poi i soldi. Andiamo, non perdere il mio tempo!";
				link.l1.go = "trial_fail";
			}
		break;
		
		case "trial_fail":
			dialog.text = "Stai cercando di imbrogliarmi, signore! Se non intendi pagare, vai a chiedere a qualcun altro. E non pensare nemmeno di sfoderare la tua spada o chiamerò le guardie!";
			link.l1 = "...";
			link.l1.go = "trial_fail_1";
		break;
		
		case "trial_fail_1":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.Trial = "spy_fail";
			AddQuestRecord("Trial", "16");
			sld = characterFromId("Florian");
			sld.DeckDialogNode = "florian_failspy_5";
		break;
		
		case "trial_8":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "Ecco come stanno le cose: 'Alcantara' è pronta a salpare da tempo, ma non è stata caricata intenzionalmente, e per ordine del governatore stesso. Beh, così mi è stato detto. E ora i carpentieri stanno facendo ogni tipo di lavoro minore, che non influisce sulla partenza della nave.\nTutti stanno aspettando l'arrivo di una qualche barca da Cartagena. Il fatto è che 'Alcantara' ha, secondo il capitano, una riserva di polvere da sparo insufficiente. Quindi, la nave è rimasta qui ad aspettare per interi giorni fino a quando 'Puebla' porta la polvere da sparo.\nMa tutti pensano che tutta questa attesa sia solo una perdita di tempo, quindi se 'Puebla' non arriva in tre giorni, 'Alcantara' alzerà l'ancora senza la polvere da sparo...";
			link.l1 = "È così? E chi te l'ha detto? Nome?";
			link.l1.go = "trial_9";
		break;
		
		case "trial_9":
			dialog.text = "Uno dei marinai dell''Alacantara' - Felipe Dabinho... Ma in realtà non è affatto un segreto, e lo stesso Sua Grazia il governatore aveva ordinato...";
			link.l1 = "Capisco. È quello che mi aspettavo. Spie francesi sono in città, ma questi idioti stanno chiacchierando come ragazze di mercato, incredibile! Qualsiasi arrivato può scoprire tutto ciò che vuole sui piani di Sua Grazia. Oh, quel Felipe Dabinho è nei guai seri ora! E anche il nostromo dell''Alacantara'! È colpa sua se il suo equipaggio non sa nulla sulla disciplina!";
			link.l1.go = "trial_10";
			QuestPointerToLoc("PortoBello_Town", "reload", "gate_back");
			QuestPointerToLoc("PortoBello_ExitTown", "reload", "reload1_back");
			QuestPointerToLoc("PortoBello_Jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("PortoBello_Jungle_02", "reload", "reload3_back");
			QuestPointerToLoc("shore47", "reload", "boat");
		break;
		
		case "trial_10":
			dialog.text = "Oh... Quindi, lo sapevi fin dall'inizio? Ma perché... Non è colpa mia! Mi hai detto di farlo!";
			link.l1 = "Non è stata colpa tua, non dovresti preoccuparti, nessuno ti punirà. Ora sappiamo che l'equipaggio dell' 'Alacantara' può sparare qualsiasi informazione al nemico - anche ciò che dovrebbe essere tenuto segreto. Va bene, ora puoi andare. Grazie per il tuo aiuto. Vai a spendere i tuoi soldi.";
			link.l1.go = "trial_11";
			// belamour legendary edition -->
			link.l2 = "Addio. (Uccidilo)";
			link.l2.go = "trial_11a";
		break;
		
		case "trial_11a":
			DialogExit();
			AddMoneyToCharacter(npchar, 5000);
			npchar.SaveItemsForDead  = true; 
			LAi_SetActorType(pchar);
			// если не надет пистоль или мушкет, то выдадим строевой 
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE) || !CheckAttribute(pchar,"equip."+MUSKET_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			LAi_ActorAnimation(pchar, "Shot", "RIP_Bomzh", 1.0); 
		break;
		
		case "trial_11":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 50);
			// <-- legendary edition
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.Trial = "spy_win";
			AddQuestRecord("Trial", "17");
			sld = characterFromId("Florian");
			sld.DeckDialogNode = "florian_12";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		// --> калеуче
		case "Caleuche":
			dialog.text = "Mi scusi, buon signore... L'ho vinto in un gioco di dadi contro un estraneo, pensavo fosse un amuleto di guarigione incantato, ma mi sbagliavo... Non cura le malattie, e i commercianti del mercato non sono interessati. Ecco a voi - un marinaio, un capitano, un uomo istruito. Guardatelo, potrebbe trovarlo utile.\nPer te questa coppia di migliaia è una somma piccola, ma per me è un pezzo di pane e un sorso di rum per un mese. Guarda, signore...";
			link.l1 = "Bene, mostra...";
			link.l1.go = "Caleuche_1";
		break;
		
		case "Caleuche_1":
			Log_Info("You got a strange amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Eccolo...";
			link.l1 = "Così così... Cosa interessante, sono d'accordo. Sono sicuro che è stato rubato dalle colonie indiane. Va bene, lo prenderò. Ecco i tuoi soldi.";
			link.l1.go = "Caleuche_2";
		break;
		
		case "Caleuche_2":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Grazie, signore! Spero che questa cosa ti porti fortuna! Che il Signore ti protegga!";
			link.l1 = "Buona fortuna, compagno. Non spendere tutti i soldi in una volta sola nella taverna.";
			link.l1.go = "Caleuche_3";
		break;
		
		case "Caleuche_3":
			DialogExit();
			GiveItem2Character(pchar, "kaleuche_amulet1"); 
		break;
		// <-- калеуче
		
		// --> Тайна Бетси Прайс
		case "TBP_Kulon_1":
			dialog.text = "Eh, "+GetAddress_Form(NPChar)+", cosa te ne importa di un vecchio gingillo?";
			link.l1 = "Quando colpirò la tua stupida testa con il mio stivale, capirai subito perché mi importa.";
			link.l1.go = "TBP_Kulon_TO";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon2"))
			{
				link.l2 = "Questo pendente apparteneva a Betsy Price. Quindi, dove l'hai trovato?";
				link.l2.go = "TBP_Kulon_leadership";
			}
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon3");
		break;

		case "TBP_Kulon_TO":
			dialog.text = "Era disteso vicino alla casa con la lanterna, "+GetAddress_Form(NPChar)+". Calpestata nel fango da uno stivale d'uomo rozzo. Ma nessuno ha vissuto in quella casa per molto tempo, quindi ho deciso che era senza proprietario...";
			link.l1 = "Mmm...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "FencingH", 100);
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon2");
		break;

		case "TBP_Kulon_leadership":
			dialog.text = "Era distesa vicino alla casa con la lanterna, "+GetAddress_Form(NPChar)+". Calpestato nel fango da uno stivale d'uomo rozzo. Ma nessuno ha vissuto in quella casa per molto tempo, quindi ho deciso che era senza proprietario...";
			link.l1 = "Mmm...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon2");
		break;
		// <-- Тайна Бетси Прайс
	}
}
