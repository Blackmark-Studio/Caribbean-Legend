void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;
	ref rColony;
	
	int iTest;
	
	bool  ok; // лесник . спецпеременная.

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	iTest = FindColony(NPChar.City);
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_GoOut":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //закрываем вход в дом
					break;
    			}
    		}
			DoQuestFunctionDelay("HouseEnc_TimerGoUot", 10.0);
			pchar.questTemp.HouseEncTimer = pchar.location;
			pchar.questTemp.HouseEncTimer.Id = npchar.id;
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_close":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //закрываем вход в дом
					break;
    			}
    		}
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//--------------------------------- мужик ---------------------------------
		case "HouseMan":
			NextDiag.TempNode = "HouseMan";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("L'allarme è stato dato in città. A quanto pare, è ora anche per me di prendere le armi...","Non è che per caso ci sono delle guardie cittadine che ti stanno dando la caccia?","Non troverai rifugio qui, ma potresti benissimo trovare diverse pollici di freddo acciaio tra le tue costole!"),LinkRandPhrase("Di cosa hai bisogno,"+GetSexPhrase("birbante","birbante")+"?! Le guardie della città hanno già trovato il tuo odore, non andrai lontano, "+GetSexPhrase("sporco pirata","tu pirata sgualdrina")+"!","Sporco assassino! Guardie!!!","Non ho paura di te, "+GetSexPhrase("verme","sgualdrina")+"! Presto sarai impiccato nel nostro forte, non andrai lontano..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Vedo che sei stanco di vivere...","Sembra così, non c'è vita pacifica per i cittadini di "+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("Vai all'inferno!","Eh, saranno gli ultimi secondi della tua vita..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "Ti ho avvertito. E poi puoi decidere da solo, se vuoi cacciarti nei guai.";
					link.l1 = "Ehi!";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Cosa vuoi nella mia casa, mascalzone?! Hai dieci secondi per uscire da qui!";
					link.l1 = LinkRandPhrase("Eh, sembra che mi conoscano anche qui!","La mia fama mi ha appena preceduto...","Mmm, capisco.");
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("Sono lieto di darvi il benvenuto nella mia casa. Avete affari con me?","Cosa posso fare per te?","Mmm... Cosa posso fare per te?","Mi dispiace, ma se non hai affari con me, per favore non disturbarmi...","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("No, solo guardandomi intorno, conoscendo nuove persone...","No, niente in particolare...","Niente...","Bene, come dici tu.",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseMan_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("Mi dispiace, ma la notte non è il momento migliore per le visite, quindi ti pregherei di lasciare immediatamente la mia casa!","Ti ho già detto, è tardi. Per favore, vai via.","Non voglio sembrare maleducato, ma insisto che tu lasci immediatamente la mia casa!","Maledizione, cosa sta succedendo?! Guardie! Ladri!","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Bene, capisco...","Sì, solo un momento...","Bene, solo non farti così eccitato.","Che ladri?! Taci!",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "fight", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseMan_1":
			dialog.text = "Oh, permettimi di presentarmi - "+GetFullName(npchar)+". Siamo molto felici di averti come nostro ospite. In questa città, le leggi dell'ospitalità sono onorate.";
			link.l1 = GetFullName(pchar)+", se ti fa piacere...";
			link.l1.go = "exit_setOwner";
		break;
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Sei "+GetSexPhrase("un ladro, vedo! Guardie, prendetelo","un ladro, vedo! Guardie, afferratela")+"!!!","Non posso crederci! Mi sono girato per un secondo - e tu stai frugando nelle mie cose! Fermate il ladro!!!","Guardie! Rapina! Fermate il ladro!!!");
			link.l1 = "Aaaah, diavolo!!!";
			link.l1.go = "fight";
		break;
		// --------------------------------- баба ---------------------------------
		case "HouseWoman":
			NextDiag.TempNode = "HouseWoman";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("Ti avverto che mio marito ritornerà presto! Sarebbe meglio se lasciassi subito la mia casa!","Non credo che tu riesca a scappare! E sappi che mio marito tornerà a casa presto!","Mio marito sarà a casa presto! Devi andartene subito!"),LinkRandPhrase("Peccato che mio marito non sia a casa... Vattene! Subito!!!","Sporko assassino, esci subito dalla mia casa! Guardie!",""+GetSexPhrase("Che mascalzone","Che sudiciume")+"... Presto mio marito tornerà, e vedrà di che colore è il tuo sangue!"));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Oh, tuo marito... oooooh... Sto tremando...","Eh... Sai, ragazza, tuo marito è solo un uomo... non vorrai mica che muoia ai tuoi piedi, vero?"),RandPhraseSimple("Taci, sgualdrina, prima che ti squarti...","Resterò qui per tutto il tempo che voglio. E faresti meglio a tenere la bocca chiusa se sai cosa ti conviene..."));
				link.l1.go = "exit_setOwner";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "Ti ho avvertito. Vattene o te ne pentirai!";
					link.l1 = "Che stupida sgualdrina...";
					link.l1.go = "exit";
				}
				else
				{					
					dialog.text = "Cosa stai facendo nella mia casa, "+GetSexPhrase("birbone","birbante")+"?! Se non te ne vai in dieci secondi, chiamo le guardie!";
					link.l1 = "Che stupida femmina...";
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("Sono lieto di vederti nella nostra casa. Il mio nome è "+GetFullName(npchar)+". Cosa posso fare per te?","Sei ancora qui?","Ehm, scusami, ma non credi che sia ora per te di andare via?","Ti pregherei gentilmente di non abusare della nostra ospitalità.","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat(GetFullName(pchar)+" al vostro servizio. Sono venuto qui senza un motivo particolare, solo per fare conoscenza.","Ancora qui.","Beh, non lo so...","Bene.",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseWoman_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("Oh cielo, perché stai irrompendo in casa mia a quest'ora! Mi hai davvero spaventato... Per favore, vieni a trovarci domani!","Per favore, lascia la nostra casa!"+GetSexPhrase("","Sono una donna sposata!")+"","Ti sto chiedendo di lasciare la nostra casa per l'ultima volta!","Ma cosa sta succedendo qui?!","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Non avere paura, non ti farò del male.","Va bene, solo non agitarti così tanto.","Me ne sto andando.","Come va?",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "HouseWoman_2", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseWoman_1":
			dialog.text = "Siamo sempre felici di avere ospiti. Ma non restare qui troppo a lungo,"+GetSexPhrase(", dato che sono una donna sposata..."," visto che ho molto da fare...")+"";
			link.l1 = "Oh, sì, certo...";
			link.l1.go = "exit_setOwner";
		break;
		case "Woman_FackYou":
			dialog.text = "Allora è così? Ti ho accolto come mio ospite, e tu stai rovistando nei nostri bauli?! Guardie!";
			link.l1 = "Taci, puttana!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		case "HouseWoman_2":
			dialog.text = "Ti ho chiesto di lasciare la nostra casa in modo amichevole, ma proprio non volevi ascoltare! Basta! Aiuto! Guardie!";
			link.l1 = "Taci, donna sciocca! Sei impazzita?!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break; 
		//--------------------------------- завсклад ---------------------------------		
		case "SkladMan":
			NextDiag.TempNode = "SkladMan1";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("L'allarme è stato dato in città. A quanto pare, è ora anche per me di prendere le armi...","Non è che per caso le guardie della città ti stanno inseguendo?","Non troverai riparo qui, ma potresti trovare diversi pollici di freddo acciaio tra le tue costole!"),LinkRandPhrase("Di cosa hai bisogno,"+GetSexPhrase("birbante","birbante")+"?! Le guardie della città hanno già trovato il tuo odore, non andrai lontano, "+GetSexPhrase("sporco pirata","sgualdrina")+"!","Assassino sudicio! Guardie!!!","Non ho paura di te, "+GetSexPhrase("verme","sgualdrina")+"! Presto sarai impiccato nel nostro forte, non andrai lontano..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Vedo che sei stanco di vivere...","Allora sembra, non c'è vita pacifica per i cittadini di "+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("Vai all'inferno!","Eh, saranno gli ultimi secondi della tua vita..."));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
				dialog.text = NPCStringReactionRepeat("Benvenuto! Il mio nome è "+GetFullName(npchar)+". Qui, sono io il capo, quindi nemmeno pensare di portare via qualcosa con te...","Comportati decentemente e tieni presente che ti tengo d'occhio.","Finché non dai un'occhiata ai bauli, puoi restare qui. Tanto, mi annoio da solo...",RandPhraseSimple("Oh mio, sono così annoiato!","Maledizione, cosa fare? Stare qui è così noioso!"),"block",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Va bene, non preoccuparti.","Certo!","Vedo...","Sì, sembra proprio un problema.",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);				
		break;
		
		case "SkladMan1":
			NextDiag.TempNode = "SkladMan1";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Allarme nella città. Sembra che sia giunto il momento anche per me di impugnare le armi...","Non è che per caso stanno cercando di catturarti le guardie della città?","Qui non troverai riparo, ma potresti benissimo trovare diverse pollici di freddo acciaio tra le tue costole!"),LinkRandPhrase("Di cosa hai bisogno,"+GetSexPhrase("birbante","birbante")+"?! Le guardie della città hanno già trovato il tuo odore, non andrai lontano, "+GetSexPhrase("sporco pirata","sgualdrina")+"!",""+GetSexPhrase("Sporco","Sporco")+" assassino! Guardie!!!","Non ho paura di te, "+GetSexPhrase("verme","sgualdrina")+"! Presto sarai impiccato nel nostro forte, non andrai lontano..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Vedo che sei stanco di vivere...","Allora sembra, non c'è vita pacifica per i cittadini di "+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("Vai all'inferno!","Eh, saranno gli ultimi secondi della tua vita..."));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			dialog.text = NPCStringReactionRepeat("Qui, io sono il capo, quindi non pensare nemmeno di portare via qualcosa...","Comportati decentemente e tieni a mente che ti tengo d'occhio.","Finché non sbirci nei bauli, puoi restare qui. Tanto, mi annoio da solo...",RandPhraseSimple("Oh mio, sono così annoiato!","Cazzo, cosa fare? Stare qui è così noioso!"),"block",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Va bene, non preoccuparti.","Certo!","Capisco...","Sì, sembra un problema.",npchar,Dialog.CurrentNode);	
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);				
			//открывание двери верфи по квесту промышленного шпионажа
			if (CheckAttribute(pchar, "questTemp.different.ShipyardsMap") && pchar.questTemp.different.ShipyardsMap == "toTarget" && npchar.city == pchar.questTemp.different.ShipyardsMap.city && locations[reload_cur_location_index].type == "shipyard")
			{
				link.l2 = "Ascolta, compagno, voglio parlarti apertamente.";
				link.l2.go = "ShipyardsMap_1";
				pchar.questTemp.different.ShipyardsMap = "toResult";					
			}
			// ugeen --> склад товаров для ГГ				
			if(CheckAttribute(NPChar,"Storage"))
			{
				if(!CheckAttribute(NPChar, "Storage.Speak"))
				{
					dialog.text = "Ho un'offerta allettante per te. Forse, potrebbe interessarti.";
					link.l7 = "Davvero? Va bene, sto ascoltando.";
					link.l7.go = "storage_rent";
				}
				else
				{
					if(CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = "Portami al magazzino. Voglio vedere in che condizioni si trova.";
						link.l7.go = "storage_0";
						link.l8 = "Ho deciso di liberare il magazzino. Non ne ho più bisogno.";
						link.l8.go = "storage_04";
					}
					else
					{
						if(!CheckAttribute(NPChar,"Storage.NoActivate"))
						{
							link.l7 = "Hai menzionato un magazzino. È ancora vuoto?";
							link.l7.go = "storage_01";
						}						
					}
				}		
			// <-- ugeen
			}		
		break;
		
		//--------------------------------- Аренда склада ---------------------------------
		case "storage_rent":
			NPChar.Storage.Speak = true;
			dialog.text = "Abbiamo una zona adatta come magazzino. Vorresti affittarlo per un prezzo ragionevole? Pensa solo, avresti il tuo magazzino per conservare preziose merci...";
			link.l1 = "Un magazzino, dici? Sì, tentatore, infatti... È abbastanza grande? E quanto mi farai pagare per l'affitto?";
			link.l1.go = "storage_rent1";
		break;
		
		case "storage_rent1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "È abbastanza spazioso anche per un magazzino portuale, può contenere vediamo ... 50000 quintali di carico. Per "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+"  al mese posso garantire la custodia delle tue merci. "+"Questo include la protezione con i miei uomini, la protezione dall'umidità, e la lotta contro i ratti. Cosa ne dici? Ah, e ovviamente la riservatezza, non c'è bisogno di dirlo.";
			link.l1 = "Certo. Posso darci un'occhiata?";	
			link.l1.go = "storage_rent2";
			link.l2 = "È troppo. E scommetto che è allagato e infestato da ratti.";
			link.l2.go = "storage_rent3";		
		break;
		
		case "storage_rent2":
			dialog.text = "Certo, certo. Ma... Avrò bisogno di un mese di pagamento anticipato. ";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Sei... decisamente mercantile, devo dire. Ecco i tuoi soldi ... affitterò questo capanno.";
				link.l1.go = "storage_11";
			}
			else
			{	
				link.l1 = "Sei... decisamente mercantile, devo dire. Va bene, prenderò i soldi.";
				link.l1.go = "exit";
			}	
		break;
		
		case "storage_rent3":
			dialog.text = "Come desideri. Se cambi idea, fammelo sapere. E ricorda, un magazzino così bello difficilmente rimarrà vuoto per molto tempo...";
			link.l1 = "Nessun problema. Ti farò sapere se ne ho bisogno.";
			link.l1.go = "exit";
		break;
		
		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 
			{
				dialog.text = "E per l'affitto, mi devi ancora  "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = "Bene, pagherò l'affitto ora.";
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = "Torno più tardi.";
					link.l1.go = "exit";
				}
			}		
			else
			{ // лесник . если забыл с собой корабль то никак.
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		        if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{	
				dialog.text = "Vai avanti.";
				link.l1 = "Grazie.";
				link.l1.go = "storage_2";
				}
				else
				{
                dialog.text = RandPhraseSimple("Capitano, dov'è la tua nave? Come prevedi di spostare il carico?","Non vedo la tua nave attraccata al porto. Come pensi di caricarla esattamente?");
                link.l1 = RandPhraseSimple("Oh.. Ho totalmente dimenticato a riguardo!","Maledizione, è vero!");
			    link.l1.go = "exit";
				break;
                }			
			}
			link.l2 = "No, ho cambiato idea.";
			link.l2.go = "exit"; 						
		break;
		
		case "storage_01":
			dialog.text = "No, "+GetSexPhrase("signore","signora")+", ancora vuota e in attesa di te. Sapevo che alla fine non avresti rifiutato la mia offerta.";
			link.l1 = "Molto bene. Lo affitterò.";
			link.l1.go = "storage_1";
			link.l2 = "No, mi è venuto in mente così...";
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Come dovresti ricordare, ho bisogno del pagamento di un mese in anticipo.";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Certo, mi ricordo. Ecco a te.";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "Maledizione. Va bene, andrò a prendere i soldi.";
				link.l1.go = "exit";
			}
		break;
		
		case "storage_11":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForStorage)); 
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			NPChar.Storage.Activate = true;
			Achievment_Set("ach_67"); // ugeen 2016
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
				
		case "storage_2":			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
		
		case "storage_3":			
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;		

		case "storage_04":
			dialog.text = "Te ne vai già? Che peccato, è davvero un posto eccellente a ottime condizioni. Ti assicuro che non troverai un affare come questo da nessuna parte nei Caraibi.";
			link.l1 = "Ho detto, lo sto lasciando. O mi proponi di pagare per immagazzinare aria? Puoi cercare un altro titolare.";
			link.l1.go = "storage_4";
			link.l2 = "Nessun posto nei Caraibi, dici? Va bene, lo terrò per un po', allora. Ma il costo dell'affitto, devo dire, è un po' troppo alto.";
			link.l2.go = "exit";
		break;
		
		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 			
			{
				dialog.text = "E per l'affitto, mi devi ancora "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))			
				{
					link.l1 = "Bene.";
					link.l1.go = "storage_5";
				}
			}
			else
			{ // лесник . если нет корабля то и товар не забрать
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		        if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{	
				dialog.text = "Raccogli le tue merci, e chiuderò il magazzino.";
				link.l1 = "Bene.";
				link.l1.go = "storage_6";
				}
				else
				{
                dialog.text = RandPhraseSimple("Capitano, dove si trova la tua nave? Come prevedi di trasportare il carico?","Non vedo la tua nave attraccata nel porto. Come pensi di caricarla esattamente?");
                link.l1 = RandPhraseSimple("Oh.. Ho completamente dimenticato di quello!","Maledizione, è vero!");
			    link.l1.go = "exit";
				break;
                }				
			}
		break;
		
		case "storage_5":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.Storage.NoActivate = true;
			DeleteAttribute(NPChar,"Storage.Activate");
			DialogExit();
		break;
		
		case "storage_6":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			DeleteAttribute(NPChar,"Storage.Activate");
			NPChar.Storage.NoActivate = true;
			DialogExit();
		break;		

		//--------------------------------- Аренда склада ---------------------------------
		
		case "ShipyardsMap_1":
			dialog.text = "Eh! Va bene, parliamo.";
			link.l1 = "Ho bisogno di arrivare al cantiere navale di notte, quando non c'è nessuno in giro.";
			link.l1.go = "ShipyardsMap_2";
		break;
		case "ShipyardsMap_2":
			if (sti(pchar.questTemp.different.ShipyardsMap.skladFight))
			{
				dialog.text = "Guardatevi! Ehi, guardie, abbiamo un ladro qui!!!";
				link.l1 = "Che ladro? Volevo solo parlare!";
				link.l1.go = "fight";
				AddCharacterExpToSkill(pchar, "FencingL", 5);
				AddCharacterExpToSkill(pchar, "FencingS", 5);
				AddCharacterExpToSkill(pchar, "FencingH", 5);
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
			}
			else
			{
				dialog.text = "Caspita! Guarda te, "+GetSexPhrase("compagno","ragazza")+". Venire all'arsenale con una tale richiesta!";
				link.l1 = "Devo arrivare al cantiere navale. Non potrebbe importarmi meno del tuo magazzino.";
				link.l1.go = "ShipyardsMap_3";
				AddCharacterExpToSkill(pchar, "Fortune", 10);
			}
		break;
		case "ShipyardsMap_3":
			dialog.text = "Ma perché ne hai bisogno?";
			link.l1 = "C'è un bisogno. E sono disposto a pagare per esso...";
			link.l1.go = "ShipyardsMap_4";
		break;
		case "ShipyardsMap_4":
			dialog.text = "Mmm, meglio così... Bene! Passami "+FindRussianMoneyString(sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000)+", e lascerò la porta del cantiere navale aperta durante il giorno seguente.";
			link.l1 = "È troppo caro. Dovrò farne a meno, allora...";
			link.l1.go = "exit";
			if (sti(pchar.money) >= (sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000))
			{
				link.l2 = "Bene, sono d'accordo. Prendi i tuoi soldi e fai come abbiamo concordato.";
				link.l2.go = "ShipyardsMap_5";
			}
		break;
		case "ShipyardsMap_5":
			dialog.text = "Non preoccuparti, sarà fatto.";
			link.l1 = "Spero proprio...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000);
			AddQuestRecord("ShipyardsMap", "5");
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			//снимаем close_for_night
			string  sName;
			int location_index = FindLocation(npchar.city + "_town");
    		makearef(arRld, Locations[location_index].reload);
    		Qty = GetAttributesNum(arRld);
    		for (int a=0; a<Qty; a++)
    		{
    			arDis = GetAttributeN(arRld, a);
				sName = arDis.go;
    			if (findsubstr(sName, "_shipyard" , 0) != -1)
    			{
					DeleteAttribute(arDis, "close_for_night");
					break;
    			}
    		}
			LocatorReloadEnterDisable(npchar.city + "_shipyard", "reload2", true);
			//ставим таймер на возврат close_for_night
			SetTimerFunction("ShipyardsMap_returnCFN", 0, 0, 2);
		break;

	}
}
