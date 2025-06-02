// городские тюрьмы
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld, location;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool  ok;
	// belamour для ночного приключения -->
	int i;
	int SoldQty = 0;
	int SoldNum[10];
	// <--

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		//---------------- Начальник тюрьмы ------------------
		case "First_officer":
			dialog.text = RandPhraseSimple("Sono il direttore del carcere. Di cosa hai bisogno qui?","Di che cosa hai bisogno? Perché sei venuto in prigione?");
			NextDiag.TempNode = "First_officer";
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_prison" && !CheckAttribute(pchar, "questTemp.HelenSCprison"))
			{
				dialog.text = "Signorina MacArthur? Sorpreso di vederti. Non abbiamo arrestato nessuno del tuo equipaggio o del capitano Swenson, per quanto ne sappia.";
				link.l1 = "Sono solo qui, signore. Non è permesso? Non stavo chiacchierando con i prigionieri alle tue spalle.";
				link.l1.go = "Helen_meeting";
				pchar.questTemp.HelenSCprison = true;
				break;
			}
			// --> Sinistra Длинные тени старых грехов
			if(CheckAttribute(pchar,"questTemp.DTSG_AntiguaTrevoga") && npchar.city == "SentJons")
			{
				dialog.text = "Ah, Charles de Maure... Dovresti essere arrestato e unito al tuo ufficiale, ma... l'incidente in banca è stato considerato un deplorevole malinteso.";
				link.l1 = "Mi piace come hai iniziato questa conversazione, Sig. "+GetFullName(NPChar)+". Posso spiegare tutto.";
				link.l1.go = "DTSG_AntiguaTrevoga_2";
				break;
			}
			// <-- Длинные тени старых грехов
			
			//--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "jailskiper")
			{
				link.l1 = "Ufficiale, ho sentito dire che c'è un uomo di nome Folke Deluc nella vostra prigione. C'è qualcosa che posso fare per liberarlo?";
                link.l1.go = "Sharlie";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "freeskiper")
			{
				link.l1 = "Ufficiale, sono io di nuovo riguardo al prigioniero Folke Deluc. Ho acquistato i diritti sul suo debito e voglio che quest'uomo sia rilasciato e consegnato a me. Ecco i suoi documenti di debito, dai un'occhiata.";
                link.l1.go = "Sharlie_3";
				break;
			}	
			//<-- Бремя гасконца
			
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// Офицер с патентом
			if(IsOfficerFullEquip())
			{
				dialog.text = "Saluti, capitano. Cosa ti porta qui?";
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Saluti, Vice Ammiraglio! Come posso aiutarla?";
			}
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Vostra Eccellenza, Governatore Generale! Avete qualche ordine?";
			}
			// <-- legendary edition
			link.l1 = "Oh, niente di speciale, sai, solo un giro per la città, quindi sono capitato qui per caso.";
			link.l1.go = "exit";
			link.l2 = "Volevo parlare di un po' di affari.";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakFort"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "F_ShipLetters_1";
				}
				else
				{
					link.l2.go = "quests";
				}		
			}
			else
			{
				if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
				{
					link.l2.go = "ReasonToFast_Prison1";
				}
				else
				{
					link.l2.go = "quests";
				}	
			}
			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = "Voglio entrare nella prigione.";
				link.l4.go = "ForGoodMove";		
			}
			if (CheckAttribute(pchar, "questTemp.jailCanMove.City") && npchar.city == pchar.questTemp.jailCanMove.City)
			{
				link.l5 = "Ehi, potresti dirmi quale crimine ha commesso il condannato di nome "+GetFullName(characterFromId(pchar.questTemp.jailCanMove.prisonerId))+"sta scontando la pena per?";
				link.l5.go = "KnowAboutPrisoner";	
			}
			
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
			{
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
				{
					bool zMsm = (CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour")) && (!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"));
					if(pchar.GenQuest.CaptainComission == "MayorTalkBad" || zMsm) //говорил с губером и отказался или узнал слухи, но не говорил с губером
					{
						link.l6 = "Ho sentito dire che l'ex capitano di una pattuglia "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" è detenuto qui in custodia. Posso parlargli?";
						link.l6.go = "CapComission_PrisonBad1";
					}
					if(pchar.GenQuest.CaptainComission == "MayorTalkGood")
					{
						link.l6 = "Io "+GetFullName(pchar)+", agendo per conto e su ordine del governatore "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+"devo parlare con l'ex capitano "+pchar.GenQuest.CaptainComission.Name+".";
						link.l6.go = "CapComission_PrisonGood1";
					}
				}	
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "fort_keeper"  && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "Si tratta di tua figlia...";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "begin" && NPChar.location == pchar.GenQuest.Marginpassenger.City + "_prison")
			{
				link.l12 = "Devo parlare con te, ufficiale. Credo che ti interesserebbe poiché è collegato ai tuoi doveri.";
				link.l12.go = "Marginpassenger";
			}
			
			// Warship, 16.05.11. Генер "Justice for sale".
			if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_prison")
			{
				link.l13 = "Voglio parlarti di un certo uomo - "+PChar.GenQuest.JusticeOnSale.SmugglerName+". È il tuo prigioniero, se non mi sbaglio.";
				link.l13.go = "JusticeOnSale_1";
			}
			
			// --> belamour ночной приключенец
			if(CheckAttribute(pchar,"GenQuest.NightAdventureToJail"))
			{
				link.l14 = "Salve ufficiale. Per quanto ne so, qualche tempo fa, un cittadino ubriaco è stato arrestato dopo aver tentato di lottare con una guardia per le strade."; 
				link.l14.go = "NightAdventure_CitizenHomie";
			}
			
			if(CheckAttribute(pchar,"GenQuest.NightAdventureToPrisoner"))
			{
				link.l14 = "Ufficiale, ho parlato con la sentinella, ed ha ritirato le sue accuse. Ecco un voucher da lui."; 
				link.l14.go = "NightAdventure_HomieToPrisoner";
			}
			// <-- приключенец
			NextDiag.TempNode = "First_officer";
		break;
		
		// --> Jason Похититель
		case "Marginpassenger":
			dialog.text = "Sì? Cosa è che sei disposto a dirmi?";
			link.l1 = "Di recente, sono stato fermato per strada da "+pchar.GenQuest.Marginpassenger.Name+" chi mi ha proposto di organizzare un'azione sporca: la cattura e poi il riscatto di una persona di nome "+pchar.GenQuest.Marginpassenger.q1Name+". È "+pchar.GenQuest.Marginpassenger.Text+"...";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Mmm... È molto intrigante - per favore continua!";
			link.l1 = "Sapeva il nome della nave, su cui "+pchar.GenQuest.Marginpassenger.q1Name+" stava pianificando di navigare. È "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Name")))+" chiamato '"+pchar.GenQuest.Marginpassenger.ShipName+"'. Inoltre, mi ha detto l'ora in cui quella nave dovrebbe salpare.";
			link.l1.go = "Marginpassenger_2";
		break;
	
		case "Marginpassenger_2":
			dialog.text = "E lui ha suggerito di catturare il passeggero e poi chiedere un riscatto per lui?";
			link.l1 = "Esattamente. Per riscuotere il riscatto, andrei a "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity)+", a una certa persona di nome "+pchar.GenQuest.Marginpassenger.q2Name+". Ho pagato per queste informazioni, ma ovviamente, non avevo intenzione di rapire quella persona.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Allora hai deciso di venire a trovarmi e farmelo sapere?";
			link.l1 = "Esattamente. Sono certo che le azioni di quel mascalzone stanno minacciando i cittadini della tua città, e spero che prenderai misure adeguate.";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			dialog.text = "Hai fatto bene a venire da me, "+GetAddress_Form(NPChar)+"! Questo mascalzone, "+pchar.GenQuest.Marginpassenger.Name+", è da tempo sotto la nostra osservazione. Farò delle indagini e, se tutto ciò che hai detto sarà confermato, getteremo quel bastardo dietro le sbarre per mezzo anno. Questo gli insegnerà a non ordire complotti contro cittadini rispettabili!\nBeh, per la tua onestà e la tua disponibilità a servire una buona causa, certamente farò rapporto al nostro governatore sulla tua azione, che, ovviamente, influenzerà il suo atteggiamento nei tuoi confronti... sai, in modo positivo. Grazie per il tuo aiuto, capitano!";
			link.l1 = "Mmm... Prego, è stato un piacere aiutare. Addio!";
			link.l1.go = "Marginpassenger_5";
		break;
		
		case "Marginpassenger_5":
			DialogExit();
			NextDiag.CurrentNode = "First_officer";
			AddQuestRecord("Marginpassenger", "20");
			AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
			CloseQuestHeader("Marginpassenger");
			pchar.quest.Marginpassenger_InWorld.over = "yes"; //снять таймер
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			ChangeContrabandRelation(pchar, -25);
			if (GetCharacterIndex("MarginCap") != -1)
			{
				sld = characterFromId("MarginCap");
				sld.lifeday = 0;
				Map_ReleaseQuestEncounter(sld.id);
				Group_DeleteGroup("Sea_MarginCap1");
			}
		break;
		//<-- Похититель

		case "EncGirl_1":
			dialog.text = "Sono tutto orecchie.";
			link.l1 = "Ho portato il tuo fuggitivo.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Oh, capitano, grazie mille! Come sta? È ferita? Perché è scappata? Perché?\nNon capisce? Lo sposo è un uomo ricco e importante! La gioventù è ingenua e stupida... anche crudele. Ricordatelo!";
			link.l1 = "Ebbene, tu sei suo padre e la decisione finale è tua, ma io non mi sbrigherei con il matrimonio...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "Cosa sai? Hai dei figli tuoi? No? Quando ne avrai uno, vieni a trovarmi e ne parleremo.\nHo promesso una ricompensa a chiunque la riportasse alla sua famiglia.";
			link.l1 = "Grazie. Dovresti tenerla d'occhio. Ho il presentimento che non si fermerà a questo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		case "ReasonToFast_Prison1":
			pchar.questTemp.ReasonToFast.SpeakOther = true;
			dialog.text = "Sono tutto orecchie, capitano.";
			link.l1 = "Voglio parlarti di una collusione criminale tra un ufficiale della tua guarnigione e i pirati (spiega la questione).";
			if(makeint(pchar.reputation.nobility) < 41)
			{
				link.l1.go = "ReasonToFast_Prison_BadRep";			
			}
			else
			{
				link.l1.go = "ReasonToFast_Prison_GoodRep";	
			}
		break;
		case "ReasonToFast_Prison_GoodRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "Grazie,"+GetSexPhrase("signore","signorina")+"! Darò immediatamente l'ordine di arrestare il malfattore.\nTuttavia, hai sostenuto dei costi e le casse comunali, ahimè, sono vuote...";
				link.l1 = "Signore! Non l'ho fatto per i soldi...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_11";
				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Grazie, "+GetSexPhrase("signore","signorina")+"! Darò immediatamente l'ordine di arrestare il mascalzone.\nPensa un po'! Volevamo ricompensarlo con un'arma personale per l'eccellente servizio. Come è bello che tutto sia chiarito, e io non ho nulla di cui vergognarmi!";
				link.l1 = "Sempre felice di servire la giustizia.";
				link.l1.go = "ReasonToFast_Prison_GoodRep_21";			
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Mi"+GetSexPhrase("ster","ss")+"! Da tempo sospettavamo quell'ufficiale e la sua feccia di ragazzi per loschi affari, ma credo che tu abbia agito troppo impulsivamente quando hai affrontato loro senza testimoni.";
				link.l1 = "Signore! Ma dovevo difendermi...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_31";	
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;	
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";	
			}
		break;
		
		case "ReasonToFast_Prison_BadRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "Capitano, ti rendi conto di quello che hai fatto?! Abbiamo cercato di preparare questa trappola per più di un mese! E ora, solo per il tuo divertimento, hai rovinato l'incontro della nostra pattuglia con il messaggero "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_GEN)+" e ora vieni qui a vantarti?! Forse, ora puoi dirmi come dovrei spiegare tutte le spese e i costi di questa operazione?!";
				link.l1 = "Vostra Grazia! Vi rifiutate solo di vedere il punto...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Lasciami guardare questa mappa...\nStai scherzando? Questo pezzo di pergamena logoro è una prova?";
				link.l1 = "Vostra Grazia! State proprio rifiutando di vedere il punto...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				TakeItemFromCharacter(pchar, "mapQuest");	
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";	
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Ecco una giustificazione originale della distruzione dell'intero gruppo di pattuglia. Beh, almeno venendo qui ci hai risparmiato la necessità di cercare l'assassino.";
				link.l1 = "Vostra Grazia! State solo rifiutando di vedere il punto...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";			
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}		
		break;
		
		case "ReasonToFast_Prison_GoodRep_11":
			dialog.text = "Nonetheless, I think that your efforts should still be rewarded. Here, take this map; it was found in the belongings of a pirate who has recently gone to the gallows. God willing, perhaps you will actually find that treasure, although I find it quite unlikely...";
			link.l1 = "Grazie, sei molto generoso!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "15");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			pchar.questTemp.ReasonToFast.state = "chain_A"; // вилка_А, наводки не генерим
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_21":
			dialog.text = "La tua zelo è lodevole. Per favore, accetta questa lama come ricompensa - è il minimo che posso fare per te. Oh, e puoi tenere questa mappa per te. Sono certo che ci sono un sacco di tali falsi sull'Arcipelago.";
			link.l1 = "Grazie, è molto generoso da parte tua!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_31":
			dialog.text = "Potrebbe essere, potrebbe essere... Beh, diciamo solo che questo accordo è stato deciso dalla giustizia divina e dalla volontà del nostro Signore.";
			link.l1 = "Grazie, è molto generoso da parte tua!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"ReasonToFast");			
		break;
		
		case "ReasonToFast_Prison_BadRep1":
			dialog.text = "Non osare fare la morale a me! È ovvio che tu stia collaborando con questi mascalzoni! Guardie, arrestate questo 'benefattore'!";
			link.l1 = "Assolutamente no!";
			link.l1.go = "fight";
			
			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1			= "EnterToSea";           	
            pchar.quest.ReasonToFast_ExitFromTown.function    				= "ReasonToFast_ExitFromTownFight";
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;			
			pchar.TownEscape = true;
			Flag_PIRATE();
		break;
		// ------------------------- Повод для спешки -----------------------------
		
		// -------------------------- Операция 'Галеон' ----------------------------
		case "CapComission_PrisonBad1":
			dialog.text = "E quale affare hai con lui?";
			link.l1 = "Ho diverse questioni private da discutere.";
			link.l1.go = "CapComission_PrisonBad2";
		break;
		
		case "CapComission_PrisonBad2":
			dialog.text = "Capitano, ho un ordine diretto di detenere e inviare alla residenza chiunque chieda informazioni su "+pchar.GenQuest.CaptainComission.Name+"per ulteriori interrogatori.";
			link.l1 = "Bella organizzazione che avete qui! Avere prigionieri che vengono da soli da voi per farsi arrestare!";
			link.l1.go = "CapComission_PrisonBad3";
		break;
		
		case "CapComission_PrisonBad3":
			dialog.text = "E tuttavia vorrei chiederti di consegnare le tue armi!";
			link.l1 = "Vaffanculo! Allora prendilo con la forza!";
			link.l1.go = "fight";
			CaptainComission_GenerateCaptainInPrison(); // данила . на всякий случай ,чтобы сгенерился нормально.
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;
		
		case "CapComission_PrisonGood1":
			dialog.text = "Sì, naturalmente. Ho ordini dal governatore di fornirti assistenza in questa faccenda. Ora puoi visitare il prigioniero.";
			link.l1 = "Grazie...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;
		
		case "CapComission_PrisonFree1":
		if(CheckAttribute(pchar,"GenQuest.CaptainComission"))// лесник . разделение диалога если кеп убит или нет
		{
			dialog.text = "Ehm, capitano, non ho l'autorità per scarcerare questo prigioniero. Devi richiedere il permesso al governatore.";
			link.l1 = "Ufficiale, sto agendo per il bene dell'inchiesta. Il prigioniero ha accettato di cooperare con le autorità e rivelare la cache. Il tempo è essenziale - i contrabbandieri possono trovare il prezioso carico, e poi sarà perduto per la popolazione.";
			link.l1.go = "CapComission_PrisonFree2";
		}
         else
		 {
         	dialog.text = "Non avresti dovuto ucciderlo, capitano... A me non importa però. Dovremo giustiziare te al posto suo. Guardie! Prendetelo!";
            link.l2 = "Hai scelto la persona sbagliata con cui metterti nei guai!...";
             link.l2.go = "fight";
			 NextDiag.TempNode = "First_officer";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			AddDialogExitQuest("OpenTheDoors");
		 }			 
		break;
		
		case "CapComission_PrisonFree2":
			dialog.text = "Ma potrei assegnargli una scorta.";
			link.l1 = "Non c'è bisogno - ho abbastanza guardie. Inoltre, non vorrei che la posizione della cache diventasse pubblica.";
			link.l1.go = "CapComission_PrisonFree3";
		break;
		
		case "CapComission_PrisonFree3":
			dialog.text = "Mmm... vabbè. Ma risponderai per lui con la tua testa.";
			link.l1 = "Certo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			AddDialogExitQuest("OpenTheDoors");
		break;
		// -------------------------- Операция 'Галеон' ----------------------------
		
		case "F_ShipLetters_1":
			dialog.text = "Parla ora, sto ascoltando.";
			link.l1 = "Ho con me alcuni documenti di nave. Il suo proprietario deve averli persi, e credo che potrebbero interessarti.";
			link.l1.go = "F_ShipLetters_2";
			pchar.questTemp.different.GiveShipLetters.speakFort = true;
		break;
		
		case "F_ShipLetters_2":			
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Cazzate! Non distogliermi dal mio lavoro! Vai dalle autorità portuali, se ti interessa!";
				link.l1 = "Beh, grazie, immagino...";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "Sì, è il proprietario locale. Forse, un premio di "+sti(pchar.questTemp.different.GiveShipLetters.price2)+" pesos serviranno come ricompensa adeguata per la tua vigilanza, capitano.";
					link.l1 = "Forse no.";
					link.l1.go = "F_ShipLetters_3";	
					link.l2 = "Un'offerta generosa. I documenti sono tuoi, allora!";
					link.l2.go = "F_ShipLetters_4";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "Oh, ora questo è davvero interessante! Credo che il tesoro della città ti pagherà volentieri "+sti(pchar.questTemp.different.GiveShipLetters.price4)+" pesos per il tuo contributo nella lotta contro il commercio illegale.";
						link.l1 = "Forse no.";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "Un'offerta generosa. I documenti sono tuoi, allora!";
						link.l2.go = "F_ShipLetters_4";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "Oh Signore! Che buona fortuna che tu sia venuto da me. Immagino che il mio sfortunato collega ti pagherà volentieri "+sti(pchar.questTemp.different.GiveShipLetters.price3)+" pesos per evitare la pubblicità di questo affare.";
						link.l1 = "Forse no.";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "Un'offerta generosa. I documenti sono tuoi, allora!";
						link.l2.go = "F_ShipLetters_4";
					}
				}
			}
		break;
		
		case "F_ShipLetters_3":
			dialog.text = "Questa è la mia città, capitano.";
			link.l1 = "Me ne ricorderò.";
			link.l1.go = "exit";
		break;
		
		case "F_ShipLetters_4":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price4)); 
				}
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price3)); 
				}
			}
						
			if((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{	
				ChangeCharacterComplexReputation(pchar,"nobility", -1); 
				OfficersReaction("bad"); 
			}	
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "8");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		
        case "ForGoodMove":
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Certo, puoi vedere tutto - qui ho un ordine completo!";
				link.l1 = "Bene, andiamo a controllare, tenente.";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Certo, Vostra Eccellenza. Potete passare.";
				link.l1 = "Grazie ufficiale.";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// Офицер с патентом
			if(IsOfficerFullEquip() && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Bene, non vedo alcun motivo per rifiutarti - dopotutto, sei il capitano della nave al servizio di "+NationNameGenitive(sti(npchar.nation))+". Entra pure."; 
				link.l1 = "Grazie ufficiale.";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// <-- legendary edition
			dialog.text = NPCStringReactionRepeat("Ma perché ne hai bisogno? Credimi, non c'è nulla di interessante, tranne per i ladri e i banditi.","Avevamo già discusso di quel tuo desiderio.","Di nuovo? Ne abbiamo già parlato due volte!","Mmm, di nuovo...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tuttavia, mi piacerebbe unirmi al tuo tour delle casematte. Sono molto interessato!","Sì, esattamente. Ma volevo parlarne.","Beh, forse la terza volta...","La speranza di vedere i tuoi prigionieri non mi abbandona.",npchar,Dialog.CurrentNode);
			link.l1.go = "ForGoodMove_1";
		break;
		
        case "ForGoodMove_1":
			pchar.questTemp.jailCanMove.money = 20+hrand(3)*10;
			if (sti(colonies[FindColony(npchar.city)].jail))
			{
				dialog.text = "Beh, non vedo motivo di rifiutare. "+FindRussianDublonString(sti(pchar.questTemp.jailCanMove.money))+" - e fino a quando non lascerai la prigione, puoi camminare liberamente lungo i corridoi e persino conversare con i detenuti.";
				if (PCharDublonsTotal() >= sti(sti(pchar.questTemp.jailCanMove.money)))
				{
					link.l1 = "Sono d'accordo, ecco le tue monete!";
					link.l1.go = "ForGoodMove_agree";
				}
				link.l2 = "Non funzionerà. È troppo per vagare senza scopo per i corridoi.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple("No, è severamente proibito dal regolamento. Cosa? Credi che abbiamo un circo qui? Vattene e non distogliermi dai miei doveri.","Non posso permettere a estranei di girare per la mia prigione. Per favore, smetti di infastidirmi!");
				link.l1 = "Va bene, come dici tu...";
				link.l1.go = "exit";
			}
		break;
		
        case "ForGoodMove_agree":
            dialog.text = "Bene, puoi iniziare la tua escursione ora...";
			link.l1 = "Grazie, ufficiale.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			RemoveDublonsFromPCharTotal(sti(pchar.questTemp.jailCanMove.money)));
		break;
		
        case "KnowAboutPrisoner":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "For murder."; break;
				case "1": sTemp = "He is accused of piracy."; break;
				case "2": sTemp = "For banditry and robbery."; break;
				case "3": sTemp = "He was caught stealing."; break;
				case "4": sTemp = "For petty theft."; break;
				case "5": sTemp = "For cheating."; break;
				case "6": sTemp = "For vagrancy and begging."; break;
			}
			dialog.text = sTemp;
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				link.l1 = "Capisco... Dammi questo prigioniero, ufficiale, e poi deciderò io stesso il suo destino.";
				link.l1.go = "KnowAboutPrisoner_gengov";
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				link.l1 = "Capisco... Consegna a me questo prigioniero, ufficiale, poi deciderò io stesso il suo destino.";
				link.l1.go = "KnowAboutPrisoner_admiral";
				DeleteAttribute(pchar, "questTemp.jailCanMove.City");
				break;
			}
			link.l1 = "Capisco... E c'è la possibilità di un riscatto, cauzione... o di liberarlo in qualche altro modo?";
			link.l1.go = "KnowAboutPrisoner_" + pchar.questTemp.jailCanMove.ownerPrison;
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		break;
		
        case "KnowAboutPrisoner_0":
			dialog.text = "Certo che no. Quel malfattore andrà dritto all'inferno. Il governatore tiene il suo caso sotto controllo speciale!";
			link.l1 = "Eh, capisco...";
			link.l1.go = "notFree_exit";
		break;	
		
		case "KnowAboutPrisoner_1":
			dialog.text = "Stai scherzando? Dev'essere andato al patibolo molto tempo fa! Sicuramente presto sposerà una corda. Dimenticalo.";
			link.l1 = "Capito. E già dimenticato...";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_2":
			dialog.text = "Non credo proprio. Ha causato un sacco di guai alla nostra gente. Quindi non chiedertelo.";
			link.l1 = "Mmm, capisco.";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_3":
			dialog.text = "Probabilmente no. È un ladro, e un ladro deve rimanere in prigione.";
			link.l1 = "Oh! Ben detto, tenente!";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_4":
			dialog.text = "Non lo so, davvero. Ha rubato solo una cosa di poco conto. Non posso liberarlo, ma lasciarlo marcire in prigione certamente non è giusto.";
			link.l1 = "Ebbene, allora dammelo, tenente. Pagherò la cauzione per lui - un importo ragionevole, naturalmente.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
        case "KnowAboutPrisoner_5":
			dialog.text = "Rilasciare? Sembra probabile. Secondo me, non ha senso detenere qui quel piccolo delinquente.";
			link.l1 = "Ebbene, allora dammelo, tenente. Pagherò la sua cauzione - un importo ragionevole, ovviamente.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
		case "KnowAboutPrisoner_6":
			dialog.text = "Hmm... C'è ragione nelle tue parole. Questo vagabondo non appartiene qui - sta solo diffondendo sporcizia e malattie...";
			link.l1 = "Ebbene, allora dammelo, tenente. Pagherò la cauzione per lui - una somma ragionevole, ovviamente.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
        case "KnowAboutPrisoner_free":
			pchar.questTemp.jailCanMove.ownerPrison.money = 50+hrand(10)*10;
			dialog.text = "Bene, abbiamo un accordo. "+FindRussianDublonString(sti(pchar.questTemp.jailCanMove.ownerPrison.money))+" sul chiodo, e puoi portarlo via subito.";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.jailCanMove.ownerPrison.money))
			{
				link.l1 = LinkRandPhrase("Eccellente! Sono d'accordo!","Hai un affare, ufficiale!","Eccellente. Sono pronto a pagare quel contributo.");
				link.l1.go = "KnowAboutPrisoner_agree";
			}
			link.l2 = "No, è troppo costoso. Credo che passo.";
			link.l2.go = "KnowAboutPrisoner_exit";
		break;
		
        case "KnowAboutPrisoner_agree":
			dialog.text = "Bene, puoi procedere alla sua cella e portare con te quel monello.";
			link.l1 = "Grazie.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			RemoveDublonsFromPCharTotal(sti(pchar.questTemp.jailCanMove.ownerPrison.money));
			Log_Info("You have given " + FindRussianDublonString(sti(pchar.questTemp.jailCanMove.ownerPrison.money)) + "");
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		
        case "KnowAboutPrisoner_exit":
			dialog.text = "Bene, è la tua scelta. Non ti darò un'altra opportunità...";
			link.l1 = "Non c'è bisogno.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_expansive";
		break;
		
        case "notFree_exit":
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_notFree";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		// belamour legendary edition -->
		// генерал-губернатор
		case "KnowAboutPrisoner_gengov":
			dialog.text = "Certo, vostra Eccellenza, se lo desiderate, prendete questo sfortunato. Ma attenzione, rimane ancora un criminale...";
			link.l1 = "È fantastico. Non preoccuparti tenente, so cosa sto facendo.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		// вице-адмирал
		case "KnowAboutPrisoner_admiral":
			dialog.text = "Beh... Non so nemmeno... In realtà, non posso semplicemente lasciar andare i prigionieri. Ma tu sei ancora un vice ammiraglio, quindi probabilmente hai il diritto di prendere questo criminale.";
			link.l1 = "È fantastico. Non preoccuparti tenente, so cosa sto facendo.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		// <-- legendary edition
		//---------------- Протектор ------------------
        case "First_protector":
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Governatore Generale, Vostra Eccellenza! Entrate, ma fate attenzione: da questi criminali ci si può aspettare di tutto...";
				link.l1 = "Non preoccuparti, soldato, me ne occuperò se succede qualcosa.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First_protector";
				break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Saluti, Vice Ammiraglio! Sono di servizio qui: mi assicuro che nessuno entri o esca senza permesso. Ma tu, naturalmente, hai il diritto di passare liberamente qui.";
				link.l1 = "Ecco, questo è meraviglioso.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First_protector";
				break;
			}
			if (sti(pchar.questTemp.jailCanMove))
			{
				dialog.text = RandPhraseSimple("Puoi passare, il guardiano ha dato il suo permesso.","Ho ricevuto un ordine dal direttore del carcere. Puoi passare liberamente.");
				link.l1 = "Molto bene.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison.money");
			}
			else
			{
				dialog.text = RandPhraseSimple("Non potrai andare oltre senza il permesso specifico del direttore del carcere!","Rispondo solo al carceriere! Se provi ad andare oltre senza il suo permesso, sei spacciato!");
				link.l1 = RandPhraseSimple("Vedo","Bene")+", soldato.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First_protector";
		break;
		//---------------- Солдаты ------------------
        case "First_soldier":
            dialog.text = RandPhraseSimple("Sono in servizio, non disturbarmi.","Vai avanti, non mi è permesso parlare con te.");
			link.l1 = "Bene, soldato.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_soldier";
		break;
		//---------------- Заключенные ------------------
        case "First_prisoner": 
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) == RELATION_ENEMY)
			{
				dialog.text = LinkRandPhrase("Oho, non è un gran bel tempo!","Tagliali, "+GetSexPhrase("compagno","ragazza")+", taglio!!!","Oh, dannazione! Ho perso ogni speranza di vedere il cadavere del mio carceriere!");
				link.l1 = RandPhraseSimple("Eh!","Arrgh!");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "GenQuest.PrisonQuestLock") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.DeliverToBander")) // Addon 2016-1 Jason пиратская линейка
				{
					dialog.text = RandPhraseSimple("Aspetta, "+GetSexPhrase("compagno","ragazza")+"!! Liberami!","Ascolta, "+GetSexPhrase("compagno","ragazza")+", per favore, apri la cella.");
					link.l1 = "Per quale motivo?";
					link.l1.go = "Prisoner_1"; // на квест освобождения заключённого
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Sono accusato di furto, ma non sono colpevole!","Arrgh, tu bello spazzolato... Ti piacerebbe sederti un po' nella mia cella?! Kheh-heh-heh...","Non sono colpevole!");
				link.l1 = RandPhraseSimple("Taci!","Non me ne frega un cazzo di te...");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "GenQuest.PrisonQuestLock") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.DeliverToBander") && !sti(colonies[FindColony(npchar.city)].HeroOwn)) // Addon 2016-1 Jason пиратская линейка
				{
					dialog.text = RandPhraseSimple("Aspetta, "+GetSexPhrase("compagno","ragazza")+", non passare così veloce!","Non affrettarti, "+GetSexPhrase("compagno","ragazza")+", parliamo.");
					link.l1 = "Per quale motivo?";
					if (rand(1))
					{
						link.l1.go = "Prisoner_1"; // на квест освобождения заключённого
					}
					else
					{
						link.l1.go = "Deliver_1"; // на квест передачу весточки
					}
				}
			}
		break;
		// -------------------- освобождение заключённого --------------------
        case "Prisoner_1":
            dialog.text = "Ascoltami, compagno. Non pensare che non sto bene e roba del genere. Ho solo bisogno di uscire da qui...";
			link.l1 = "Cosa?!";
			link.l1.go = "Prisoner_2";
			GetChestPlaceName();
			pchar.questTemp.jailCanMove.prisonerId = npchar.id; //запомним Id
			pchar.questTemp.jailCanMove.IsTrue = rand(4); //вид клада
			pchar.questTemp.jailCanMove.Item1 = GenQuestPrison_GenerateArtefact();
			pchar.questTemp.jailCanMove.Item2 = GenQuestPrison_GenerateBlade();
			pchar.questTemp.jailCanMove.Name = GetFullName(npchar); //имя перца
			npchar.nation = PIRATE;
		break;
        case "Prisoner_2":
            dialog.text = "Ciò che hai sentito! Aiutami, e sarò in grado di ripagare...";
			link.l1 = "Ecco che è interessante. Chi sei e cosa puoi offrirmi?";
			link.l1.go = "Prisoner_3";
		break;
        case "Prisoner_3":
            dialog.text = "Il mio nome è "+GetFullName(npchar)+". Ho delle cose nascoste in un posto sicuro. Basta tirarmi fuori da qui e portami a "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Acc")+". Lì, in una grotta, ho il tesoro. Lo prenderemo e lo divideremo!";
			link.l1 = "E cosa hai nel tuo nascondiglio? E come posso sapere che stai dicendo la verità?";
			link.l1.go = "Prisoner_4";
		break;
        case "Prisoner_4":
            dialog.text = "Giuro che sto dicendo la verità! Per quanto riguarda il nascondiglio - c'è un tesoro e dei soldi...";
			link.l1 = "No, compagno. Non rischio la mia pelle per un bottino discutibile. Mi dispiace...";
			link.l1.go = "Prisoner_5";
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) != RELATION_ENEMY)
			{			
				// belamour legendary edition адмирал и губернатор может договориться без денег
				bool bAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
				bool bGenGov = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == GetBaseHeroNation());
				if(!bAdmiral && !bGenGov)
				{
				link.l2 = "Ebbene, potrebbe valere la pena di correre un rischio... Suggerisco quanto segue: posso eliminare le guardie nella prigione e portarti sulla mia nave. Se tutto va bene, voglio che tu rimanga al mio fianco tutto il tempo fino a quando arriviamo alla grotta su  "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc")+". Affare?"; // belamour gen
				link.l2.go = "Prisoner_agree"; //силовой способ вызволения
				}
				link.l3 = "Bene, cercherò di aiutarti. Parlerò con il direttore del carcere. Forse, riuscirò a farti uscire su cauzione.";
				link.l3.go = "ToPrisonHead_agree"; //мирный способ вызволения
			}
			else
			{
				link.l2 = "Bene, ti crederò e aprirò la tua cella. Voglio che tu stia al mio fianco tutto il tempo fino a quando non arriviamo alla grotta su "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc")+". Affare?";
				link.l2.go = "Prisoner_agree_3"; //силовой способ вызволения, когда тюремщики убиты
			}
		break;
        case "Prisoner_5":
            dialog.text = RandPhraseSimple("Maledetto te, furfante!","Maledetto, mi hai fregato, feccia...");
			link.l1 = RandPhraseSimple("E tutto il meglio anche a te. Addio...","La luna non ha bisogno dell'abbaiare dei cani...");
			link.l1.go = "NoMoreTalkExit";
		break;
        case "Prisoner_agree":
            dialog.text = "Bene. Non sono nella posizione di fare il difficile.";
			link.l1 = "Bene. Ora romperò la tua serratura per liberarti, e noi sfonderemo. Sei pronto?";
			link.l1.go = "Prisoner_agree_1";
		break;
        case "Prisoner_agree_1":
            dialog.text = "Sì, "+GetSexPhrase("compagno","ragazza")+", sono pronto!";
			link.l1 = "Allora, mettiamoci al lavoro!";
			link.l1.go = "Prisoner_agree_2";
		break;
        case "Prisoner_agree_2":
			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";			
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

        case "Prisoner_agree_3":
            dialog.text = "Bene. Non sono in posizione di fare il difficile.";
			link.l1 = "Bene. Seguimi il più velocemente possibile - dobbiamo ancora raggiungere la mia nave. Non indugiare!";
			link.l1.go = "Prisoner_agree_4";
		break;
        case "Prisoner_agree_4":
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_agree":
            dialog.text = "Ebbene, puoi provare. Speriamo di farcela! Ma non perdere tempo - tra un paio di giorni me ne andrò da qui...";
			link.l1 = "Aspetta qui, sistemo tutto io.";
			link.l1.go = "NoMoreTalkExit";
			pchar.questTemp.jailCanMove.City = npchar.City; //город
			pchar.questTemp.jailCanMove.ownerPrison = rand(6); //характер преступления
			SetTimerCondition("GivePrisonFree_Over", 0, 0, 2, false);
			AddQuestRecord("GivePrisonFree", "5");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
		break;

        case "ToPrisonHead_canMove":
            dialog.text = "Allora, cosa dici, "+GetSexPhrase("compagno","ragazza")+"?";
			link.l1 = "Tutto è stato organizzato, e posso portarti via da qui.";
			link.l1.go = "ToPrisonHead_canMove_1";
		break;
        case "ToPrisonHead_canMove_1":
            dialog.text = "Allora andiamo via da qui! Oh, Signore, quanto sono felice!";
			link.l1 = "Ricapitoliamo. Voglio che tu stia al mio fianco tutto il tempo fino a quando non arriviamo alla grotta su "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Dat")+", non resterai più indietro di un solo passo. Giusto per precauzione. Sei d'accordo?";
			link.l1.go = "ToPrisonHead_canMove_2";
		break;
        case "ToPrisonHead_canMove_2":
            dialog.text = "Certo, sono d'accordo! Ancora di più che non sono in posizione di scegliere.";
			link.l1 = "Allora sei libero.";
			link.l1.go = "ToPrisonHead_canMove_exit";
		break;
        case "ToPrisonHead_canMove_exit":
			pchar.quest.GivePrisonFree_Over.over = "yes";
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";			
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_notFree":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "murder"; break;
				case "1": sTemp = "piracy"; break;
				case "2": sTemp = "brigandry"; break;
				case "3": sTemp = "thievery"; break;
			}
            dialog.text = "Allora, cosa dici, "+GetSexPhrase("compagno","ragazza")+"?";
			link.l1 = "Non sono riuscito a organizzare la tua liberazione. Sei accusato di "+sTemp+", quindi non puoi essere liberato.";
			link.l1.go = "ToPrisonHead_notFree_1";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
		break;
		
        case "ToPrisonHead_notFree_1":
            dialog.text = "Ma sono stato diffamato! Oh diavolo! E cosa farò ora? Marcirò qui vivo!";
			link.l1 = "Mi dispiace, compagno, ma non c'è niente che io possa fare per te.";
			link.l1.go = "ToPrisonHead_notFree_2";
			link.l2 = "C'è solo una possibilità rimasta - liberarti con la forza. Ora spezzerò il tuo lucchetto per tirarti fuori, e ci faremo strada. Sei pronto?";
			link.l2.go = "Prisoner_agree_1";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		
        case "ToPrisonHead_notFree_2":
            dialog.text = RandPhraseSimple("Maledizione a te!","Maledetta, mi hai fregato, stronza...");
			link.l1 = "E tutto il meglio anche a te. Addio...";
			link.l1.go = "NoMoreTalkExit";
			AddQuestRecord("GivePrisonFree", "7");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
		break;

        case "ToPrisonHead_expansive":
			dialog.text = "Allora, qualche buona notizia, "+GetSexPhrase("compagno","ragazza")+"?";
			link.l1 = "La cauzione per la tua liberazione è troppo alta, non ho così tanti soldi. Devo smettere di aiutarti.";
			link.l1.go = "ToPrisonHead_notFree_2";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		//==> в месте, где клад припрятан
        case "PrisonerInPlace":
			switch (sti(pchar.questTemp.jailCanMove.IsTrue))
			{
				case 0:
					dialog.text = "Ascolta, ho controllato tutto, ma non ho trovato alcun tesoro. Peccato che sia andata così. Qualcuno deve averlo scavato prima di noi.";
					link.l1 = "E come può essere?!";
					link.l1.go = "PrisonerInPlace_1";
				break;
				case 1:
					dialog.text = "L'ho trovato! Il tesoro è ancora dove l'ho lasciato.";
					link.l1 = "Eccellente. Allora, andiamo, sì?";
					link.l1.go = "Node_1";
				break;
				case 2:
					dialog.text = "Ebbene, eccolo qui, il mio nascondiglio. Non è molto, ma è tutto quello che ho. Come abbiamo concordato, metà è tua.";
					link.l1 = "Sì, il tesoro è modesto, davvero. Beh, comunque meglio di niente.";
					link.l1.go = "Node_2";
				break;
				case 3:
					dialog.text = "Capitano, mi dispiace, ma... Non c'è tesoro.";
					link.l1 = "Cosa?! Mi hai ingannato, mascalzone! Ti ho portato su quell'isola - e per cosa? Non te la caverai così facilmente!";
					link.l1.go = "Node_3";
				break;
				case 4:
                    ok = GetCharacterItem(pchar, "map_full") == 0 && GetCharacterItem(PChar, "map_part2") == 0;
                    if(GetCharacterItem(PChar, "map_part1") > 0 && !ok) // Первая половинка есть, но вторую дать нельзя
                    {
                        dialog.text = "Ascolta, ho controllato tutto, ma non ho trovato alcun tesoro. Peccato che sia andata così. Qualcuno deve averlo scavato prima di noi.";
                        link.l1 = "E come può essere?!";
                        link.l1.go = "PrisonerInPlace_1";
                    }
                    else
                    {
                        dialog.text = "Maledizione... Come può essere? Non può essere!";
                        link.l1 = "Cosa succede, amico? Dove è il tesoro? Non dirmi che non c'è!";
                        link.l1.go = "Node_4";
                    }
				break;
			}
		break;
			
		case "Node_1":
			dialog.text = "Certo, come era stato concordato. Metà del tesoro è tuo.";
			link.l1 = "Santo Signore, ora c'è sicuramente un sacco di roba preziosa!";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You have received your share of the treasure");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+hrand(1));
			TakeNItems(pchar, "chest", 4+hrand(4));
			TakeNItems(pchar, "jewelry1", 70+rand(15));
			TakeNItems(pchar, "jewelry2", 50+rand(15));
			TakeNItems(pchar, "jewelry3", 60+rand(15));
			TakeNItems(pchar, "jewelry4", 40+rand(10));
			TakeNItems(pchar, "jewelry5", 10+rand(10));
			TakeNItems(pchar, "jewelry46", 60+rand(20));
			TakeNItems(pchar, "jewelry47", 40+rand(15));
			TakeNItems(pchar, "jewelry40", 60+rand(20));
			AddQuestRecord("GivePrisonFree", "3_1");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_2":
			dialog.text = "Capitano, c'è anche quel pezzo indiano tra le altre cose. Puoi averlo in aggiunta alla tua quota.";
			link.l1 = "Beh, almeno qualcosa di prezioso per la tua liberazione! Dammi.";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You have received your share of the treasure");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item1;
			TakeNItems(pchar, sTemp, 1);
			TakeNItems(pchar, "jewelry5", 40+rand(10));
			TakeNItems(pchar, "jewelry6", 20+rand(20));
			TakeNItems(pchar, "jewelry17", 80+rand(20));
			TakeNItems(pchar, "jewelry13", 10+rand(10));
			TakeNItems(pchar, "jewelry10", 20+rand(20));
			TakeNItems(pchar, "jewelry12", 50+rand(20));
			TakeNItems(pchar, "jewelry11", rand(2)+1);
			AddQuestRecord("GivePrisonFree", "3_2");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_3":
			dialog.text = "Aspetta, Capitano, non agitarti, lasciami parlare. Anche io sono un marinaio, proprio come te. Sono stato gettato in prigione per errore, lo giuro. Eri la mia unica possibilità di fuga, e ho dovuto mentirti sul tesoro.\nNon c'è tesoro, ma ho nascosto una cosa buona lì. Prendila, e lasciami andare in pace. Forse, un giorno in battaglia, ti aiuterà a sopravvivere.";
			link.l1 = "Bene, non mi aspettavo molto da te comunque. Grazie a Dio che non porto rancore.";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You have received equipment");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item2;
			TakeNItems(pchar, sTemp, 1);
			AddQuestRecord("GivePrisonFree", "3_3");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_4":
			dialog.text = "No!!! Non è lì! Dannata roba... Capitano, ero assolutamente sicuro di trovarlo qui! Ma, a quanto pare, mi sbagliavo! Qualcosa su quel pezzo di carta era davvero poco chiaro...";
			link.l1 = "Beh, che dire... Sei nei guai fino al collo, amico. Ma vorrei comunque ascoltare la tua spiegazione.";
			link.l1.go = "Node_4_1";
		break;
			
		case "Node_4_1":
			dialog.text = "Avevo un pezzo della mappa. Era una vera mappa, lo giuro! Ma è molto difficile dire, quale isola fosse mostrata su di essa... Pensavo fosse qui... Ma, come vedi ora, mi sbagliavo.";
			link.l1 = "Che pezzo di carta? Dammi subito!";
			link.l1.go = "Node_4_2";
		break;
			
		case "Node_4_2":
			AddMapPart();
			dialog.text = "Certo, prendilo. Capitano, liberami... per favore? Credevo davvero che il tesoro fosse lì. Forse, capirai dove si trova, e lo prenderai per te. Ti prego.";
			link.l1 = "Capisco... Effettivamente, è difficile capire qualcosa da quel brandello. È necessaria la seconda metà della mappa. Va bene, sparisci. Ora vedo che non è stata colpa tua.";
			link.l1.go = "PrisonerInPlace_4";
		break;
			
		case "PrisonerInPlace_1":
			dialog.text = "Molto semplice, "+GetSexPhrase("compagno","ragazza")+". Tutto nella vita succede.\nBeh, sei qui - se vuoi: rimani, cerca di più. Beh, devo andare!\nAddio, "+GetSexPhrase("il mio amico","ragazza")+", grazie per aver salvato la mia vita. Ti ricorderò sempre!";
			link.l1 = "Birbante! Pensi che ti lascerei cavartela così?! Ehi! Aspetta, codardo!";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "4");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
        case "PrisonerInPlace_2":
			LAi_group_Delete("EnemyFight");
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
			chrDisableReloadToLocation = false;
			LAi_LocationDisableMonstersGen(pchar.location, false);
			npchar.lifeDay = 0;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", -1);
			DialogExit();

            Pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
            Pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup";
		break;
		
        case "PrisonerInPlace_3":
			dialog.text = "Eccoti. Grazie!";
			link.l1 = "Addio...";
			link.l1.go = "PrisonerInPlace_2";
		break;
		
        case "PrisonerInPlace_4":
			dialog.text = "Grazie, capitano! Prego per te fino alla fine dei miei giorni!";
			link.l1 = "Oh, smettila! Va' in pace...";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "3_4");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
        
		// -------------------- освобождение заключённого --------------------
		// ------------------------ передать маляву --------------------------
        case "Deliver_1":
			dialog.text = "Mi chiamano "+GetFullName(npchar)+". Ho una richiesta per te, he-he...";
			link.l1 = "Come va?";
			link.l1.go = "Deliver_2";
		break;
        case "Deliver_2":
			dialog.text = "Ho bisogno che un messaggio venga inviato fuori dal carcere. Lo farai?";
			link.l1 = "E cosa ci guadagno io?";
			link.l1.go = "Deliver_3";
		break;
        case "Deliver_3":
			dialog.text = "Le amicizie non ti deluderanno, prometto... Allora? Sei dentro?";
			link.l1 = "No, non sono interessato.";
			link.l1.go = "Prisoner_5";
			link.l2 = "Beh, se non richiede troppo sforzo da parte mia, posso farlo.";
			link.l2.go = "Deliver_agree";
		break;
        case "Deliver_agree":
			dialog.text = "Bene. Ora ascoltami attentamente. Due amici stanno aspettando il mio messaggio in una casa, così non verranno catturati durante una retata. Ma non ho idea di quale casa si tratti esattamente. Dovrai cercare.";
			link.l1 = "Cosa intendi - cercare?";
			link.l1.go = "Deliver_4";
		break;
        case "Deliver_4":
			dialog.text = "Cerca come nel cercare. Girerai per la città, sbircerai nelle case. Quando arriverai al posto giusto, non ti lasceranno andare senza una chiacchierata. Ma tieni presente che rimarrei lì al massimo per altri due giorni. Quindi non indugiare.";
			link.l1 = "Capisco. Bene, consegnami la tua lettera, allora.";
			link.l1.go = "Deliver_5";
		break;
        case "Deliver_5":
			pchar.questTemp.jailCanMove.Deliver.locationId = GetBanderLocation(npchar); //Id коммона
			if (pchar.questTemp.jailCanMove.Deliver.locationId == "none")
			{
				dialog.text = "Mmm, sai, semplicemente non mi piaci. Ho cambiato idea. Vieni, non stare lì!";
				link.l1 = "Guardati! Beh, come vuoi tu...";
				link.l1.go = "NoMoreTalkExit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
			}
			else
			{
				dialog.text = "Ecco. Grazie, "+GetSexPhrase("compagno","ragazza")+"!";
				link.l1 = "Per niente.";
				link.l1.go = "NoMoreTalkExit";
				GiveItem2Character(Pchar, "Malyava");
				pchar.questTemp.jailCanMove.Deliver.Id = npchar.id; //Id зэка
				pchar.questTemp.jailCanMove.Deliver.name = GetFullName(npchar); //имя зэка
				pchar.questTemp.jailCanMove.Deliver.City = npchar.city; //город (Id колонии)
				pchar.questTemp.jailCanMove.Deliver.good = rand(3); //опрокинут или нет
				pchar.questTemp.jailCanMove.Deliver.price = rand(6)*500+500; //цена услуги
				pchar.quest.DeliverToBander.win_condition.l1 = "location";
				pchar.quest.DeliverToBander.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.locationId;
				pchar.quest.DeliverToBander.win_condition = "DeliverToBander";
				pchar.quest.DeliverToBander.again = true; 
				SetTimerCondition("DeliverToBander_over", 0, 0, 2, false);
				ReOpenQuestHeader("GivePrisonFree");
				AddQuestRecord("GivePrisonFree", "8");
				AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
				AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Deliver.name);
			}
		break;
		
		// Warship, 16.05.11. Генер "Justice for sale".
		case "JusticeOnSale_1":
			dialog.text = "Sì, è stato arrestato con l'accusa di contrabbando. Ma perché ti importa di quel pezzo di corda per impiccare, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "La sua banda sta pianificando di organizzare la sua fuga e continuare le loro sporche azioni.";
			link.l1.go = "JusticeOnSale_2";
			link.l2 = "Ho sentito dire che non era colpevole.";
			link.l2.go = "JusticeOnSale_3";
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");
		break;
		
		case "JusticeOnSale_2":
			dialog.text = "Dovete avvisare il governatore, "+GetAddress_Form(NPChar)+", questi mascalzoni devono essere tutti catturati!";
			link.l1 = "Farò proprio così.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
		break;
		
		case "JusticeOnSale_3":
			dialog.text = "Ascolta, "+GetFullName(PChar)+", quel tizio è stato arrestato mentre cercava di vendere merci proibite, proprio in città! Come puoi affermare che non è colpevole?";
			link.l1 = "Ho sentito dire che l'accusa era infondata e non hai prove, non è vero? Non puoi semplicemente detenere un uomo che è stato ingiustamente accusato.";
			link.l1.go = "JusticeOnSale_4";
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "Non abbiamo né testimoni né merci, ma questo non cambia nulla, capitano "+GetFullName(PChar)+"! Quella persona è decisamente colpevole - e forse non solo di commercio illegale. In ogni caso - perché dovresti preoccuparti del prigioniero?";
			link.l1 = "Forse, la mia parola può essere la cauzione per quel prigioniero sfortunato?";
			link.l1.go = "JusticeOnSale_5_WithoutMoney";
			
			if(sti(PChar.money) >= 5000)
			{
				link.l2 = "Forse, questi 5000 pesos potrebbero essere la cauzione per quel prigioniero sfortunato?";
				link.l2.go = "JusticeOnSale_5";
			}
		break;
		
		case "JusticeOnSale_5_WithoutMoney":
			if(GetCharacterSkill(PChar, SKILL_LEADERSHIP) > hrand(100) || sti(PChar.money) < 5000)
			{
				dialog.text = "Bene, "+GetAddress_Form(NPChar)+", prendi quel furfante e vai, prima che cambi idea.";
				link.l1 = "È bello vedere trionfare la giustizia, non credi?";
				link.l1.go = "JusticeOnSale_6";
			}
			else
			{
				dialog.text = "No, "+GetAddress_Form(NPChar)+", quello non andrà bene.";
				link.l1 = "Allora, forse, questi 5000 pesos possono essere l'argomento più convincente?";
				link.l1.go = "JusticeOnSale_5";
			}
		break;
		
		case "JusticeOnSale_5":
			dialog.text = "Bene, "+GetAddress_Form(NPChar)+", prendi quel furfante e vattene, prima che cambi idea.";
			link.l1 = "È bello vedere il trionfo della giustizia, non credi?";
			link.l1.go = "JusticeOnSale_6";
			AddMoneyToCharacter(PChar, -5000);
			PChar.GenQuest.JusticeOnSale.PrisonMoney = true;
		break;
		
		case "JusticeOnSale_6":
			DialogExit();
			sld = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_Smuggler", "mercen_"+(rand(9)+1), "man", "man", sti(PChar.rank)+5, PIRATE, -1, true, "marginal"));
			SetFantomParamFromRank(sld, sti(PChar.rank)+5, true);
			sld.name = PChar.GenQuest.JusticeOnSale.SmugglerName;
			sld.lastName = "";
			sld.dialog.filename = "GenQuests_Dialog.c";
			sld.dialog.currentnode = "First time";
			sld.greeting = "Enc_Raiders"; 
			AddPassenger(PChar, sld, false);
			SetCharacterRemovable(sld, false);
			PChar.GenQuest.JusticeOnSale.SmugglerModel = sld.model;
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
			sld = &Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)];
			sld.DisableEncounters = true;
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.win_condition.l1  = "location";
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.win_condition.l1.location = PChar.GenQuest.JusticeOnSale.ShoreId;
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.function = "JusticeOnSale_ShoreEnterWithSmuggler";
			Log_Info("Smuggler's captain on a board");
			PlaySound("interface\notebook.wav");
			LAi_Fade("", "");
			WaitDate("",0,0,0,0,60); // 280313 // лесник. прокрутка времени было так WaitDate("",0,0,0,2,5);
		break;
		// --> belamour ночной приключенец
		case "NightAdventure_CitizenHomie":
			dialog.text = "Sì, c'era un tale violento. È stato maleducato con una sentinella, e poi è finito in una rissa. Niente di più: resterà dietro le sbarre per qualche giorno - si riprenderà. Perché ti importa di lui? Sembri essere un capitano, e questo ubriacone non sembra un marinaio.";
			link.l1 = "Sì, è vero, sono un capitano. La questione è che questo ubriacone è un vecchio conoscente di mio. Per favore, non dire a nessuno di questo. Se ho capito bene, non ha nemmeno preso un'arma. Forse lo libererai questa volta su mia richiesta?";
			link.l1.go = "NightAdventure_CitizenHomie_1";
		break;
		
		case "NightAdventure_CitizenHomie_1":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomie") // отпустил под честное слово
			{
				dialog.text = "Sì, un buon amico mio. Non preoccuparti, non dirò a nessuno. Infatti, non è riuscito nemmeno a colpire correttamente, è stato solo un tentativo - ecco perché l'hanno messo in prigione. Dato che me lo chiedi, per rispetto verso di te, lo libererò. Avvertilo solo di controllarsi la prossima volta. O meglio ancora, fagli bere di meno.";
				link.l1 = "Grazie ufficiale.";
				link.l1.go = "NightAdventure_CitizenHomieOK";
			}
			
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderNM" || pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderGM") // поговорить с солдатом
			{
				dialog.text = "Sì, buon amico. Non preoccuparti, non dirò a nessuno. L'unica cosa è che è riuscito a colpire il sentinella in faccia prima che lo legassero. Quindi non posso liberarlo. A meno che, naturalmente, il sentinella non accetti di ritirare le sue accuse. Puoi parlarci tu stesso, oggi è in pattuglia in giro per la città.";
				link.l1 = "No, temo che se ha colpito la guardia, allora non posso aiutarlo. Dovrà restare seduto per un paio di giorni. Mi dispiace disturbarla, ufficiale.";
				link.l1.go = "CitizenHomieEnd";
				link.l2 = "Ok, andrò a cercare di negoziare con la sentinella.";
				link.l2.go = "NightAdventure_CitizenHomieSolder";
			}
			
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieOfficer") // выплата офицеру
			{
				dialog.text = "Sì, buon amico. Non preoccuparti, non dirò a nessuno. Il fatto è che attaccare un membro delle forze armate mentre è in servizio è un crimine. Posso venirti incontro e rilasciarlo, ma solo su cauzione.";
				link.l1 = "E quanto devo pagare per questo?";
				link.l1.go = "NightAdventure_CitizenHomieOfficer";
			}
		break;
		
		case "NightAdventure_CitizenHomieOK":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
		break;
		
		case "NightAdventure_CitizenHomieEnd":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_CitizenHomieSolder":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			for(i=0; i<MAX_CHARACTERS; i++)
			{
				if(Characters[i].location != npchar.City+"_town") continue;
				if(Characters[i].chr_ai.type != "patrol") continue;
				while(SoldQty < 10) // на всякий случай, чтобы не было выхода за границы массива
				{                   // генерируется 7 солдат + 3 мушкетера
					SoldNum[SoldQty] = Characters[i].index;
					SoldQty++;
				}
			}
			iTemp = rand(SoldQty);
			pchar.GenQuest.NightAdventureSolNum = SoldNum[iTemp];
		break;
		
		case "NightAdventure_HomieToPrisoner":
			DeleteAttribute(pchar,"GenQuest.NightAdventureToPrisoner");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
			dialog.text = "*legge* Allora... allora... Beh, dato che la sentinella non ha lamentele, nemmeno io ne ho. Puoi portare via il tuo amico. Solo avvisalo di controllarsi la prossima volta. Meglio ancora, fagli bere di meno.";
			link.l1 = "Grazie ufficiale.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_CitizenHomieOfficer":
			dialog.text = "Beh, considerato che non ha preso un'arma, sono solo 1500 pesos.";
			link.l1 = "Temerei che non sono pronto a dare tanto. Beh, considerando che lui è qui solo per qualche giorno, suppongo che non gli farà male. Forse berrà di meno.";
			link.l1.go = "NightAdventure_CitizenHomieEnd";
			if(sti(pchar.money) >= 1500)
			{
				link.l2 = "Bene, sono pronto a pagare la cauzione.";
				link.l2.go = "NightAdventure_CitizenHomieOfficer_1";
			}
		break;
		
		case "NightAdventure_CitizenHomieOfficer_1":
			AddMoneyToCharacter(pchar, -1500);
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
			dialog.text = "Puoi prendere il tuo amico. Basta avvertirlo di controllarsi la prossima volta. O meglio ancora, fagli bere di meno.";
			link.l1 = "Grazie ufficiale.";
			link.l1.go = "exit";
		break;
		// <-- ночной приключенец
		
		// --> Sinistra Путеводная звезда
		case "PZ_BasTer_ComendantDialog":
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerOpozdal"))
			{
				dialog.text = "Grazie per aver accettato di venire invece di iniziare un massacro. Almeno qualcuno è ragionevole in questi giorni.";
				link.l1 = "Allora, a cosa devo questa attenzione, Signor Ufficiale? Ha qualcosa a che fare con il fatto che sto cercando un uomo cinese?";
				link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_1";
			}
			else
			{
				dialog.text = "È una buona cosa che tu sia venuto da noi volontariamente. Abbiamo avuto abbastanza teppisti ultimamente.";
				link.l1 = "Ebbene, come potete vedere, non sono uno di quelli violenti. Tuttavia... perché sono qui, ufficiale? Ho già chiesto ai vostri uomini, ma non ho ricevuto una risposta - è perché sto cercando un certo uomo cinese in città?";
				link.l1.go = "PZ_BasTer_ComendantDialog_1";
			}
			DeleteQuestCondition("PZ_BasTerPeshera");
			npchar.Dialog.Filename = "Common_Prison.c";
			npchar.Dialog.CurrentNode = "First_officer";
		break;
		// <-- Путеводная звезда
		case "Helen_meeting":
			dialog.text = "Ma, certo che no! Per favore, entra. Sei sempre benvenuto nelle nostre segrete. Ehm, intendo dire in senso buono, ovviamente. Allora, di cosa hai bisogno qui?";
			link.l1 = "Oh, niente di speciale, sai, solo un giro per la città, quindi mi sono capitato qui per caso.";
			link.l1.go = "exit";
			link.l2 = "Volevo parlare di un po' di affari.";
			link.l2.go = "quests";
			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = "Voglio entrare nella prigione.";
				link.l4.go = "ForGoodMove";		
			}
			NextDiag.TempNode = "First_officer";
		break;
	}
}

void GetChestPlaceName()
{
	string islandId;
	int iTemp = rand(3);
	switch (iTemp)
	{
		case 0: 
			pchar.questTemp.jailCanMove.islandId = "Bermudes";
			pchar.questTemp.jailCanMove.placeId = "Bermudes_Cavern";
		break;
		case 1: 
			pchar.questTemp.jailCanMove.islandId = "Caiman";
			pchar.questTemp.jailCanMove.placeId = "Caiman_Grot";
		break;
		case 2: 
			pchar.questTemp.jailCanMove.islandId = "Dominica";
			pchar.questTemp.jailCanMove.placeId = "Dominica_Grot";
		break;
		case 3: 
			pchar.questTemp.jailCanMove.islandId = "Terks";
			pchar.questTemp.jailCanMove.placeId = "Terks_Grot";
		break;
	}
}

string GetBanderLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "GenQuest.SeekSpy.Location")) //если взят квест мэра по поиску шпиона
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[rand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}

string GenQuestPrison_GenerateArtefact() // артефакты
{
	string itemID;
	switch(rand(7))
	{
		case 0:
			itemID = "indian_5";
		break;
		case 1:
			itemID = "indian_7"; 
		break;
		case 2:
			itemID = "indian_8"; 
		break;
		case 3:
			itemID = "indian_9"; 
		break;
		case 4:
			itemID = "indian_10"; 
		break;
		case 5:
			itemID = "indian_11"; 
		break;
		case 6:
			itemID = "indian_3"; 
		break;
		case 7:
			itemID = "indian_6"; 
		break;
	}
	return itemID;
}

string GenQuestPrison_GenerateBlade() // клинки и другое
{
	string itemID;
	switch(rand(8))
	{
		case 0:
			itemID = GetGeneratedItem("blade_16");
		break;
		case 1:
			itemID = GetGeneratedItem("blade_15"); 
		break;
		case 2:
			itemID = GetGeneratedItem("blade_13"); 
		break;
		case 3:
			itemID = "cirass2"; 
		break;
		case 4:
			itemID = GetGeneratedItem("blade_10"); 
		break;
		case 5:
			itemID = "spyglass3"; 
		break;
		case 6:
			itemID = "cirass6"; 
		break;
		case 7:
			itemID = "cirass7"; 
		break;
		case 8:
			itemID = "cirass1"; 
		break;	
		
	}
	return itemID;
}
