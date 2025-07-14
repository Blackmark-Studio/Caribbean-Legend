// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Cosa vuoi? Chiedi pure.","Ti sto ascoltando, qual è la domanda?"),"Questa è la seconda volta che provi a chiedere...","Questa è la terza volta che provi a chiedere...","Quando finirà tutto questo?! Sono un uomo impegnato, lavoro su questioni coloniali e tu continui a infastidirmi!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ora. Posto e tempo sbagliati."),"Vero... Ma più tardi, non adesso...","Chiederò... Ma un po' più tardi...","Mi dispiace, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";

			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "Voglio parlare del vostro prigioniero.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.PirateShips"))
				{
					link.l1 = "Ciao "+NPChar.name+", sono qui per il vostro prigioniero.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					link.l1 = "Voglio parlare del vostro prigioniero.";
					link.l1.go = "CapComission6";
				}
			}
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "Ho sentito dire che sei coinvolto in affari legati ai prigionieri...";
				link.l1.go = "Marginpassenger";
			}
		break;
		
		
		case "CapComission1":
			dialog.text = "Ah-ah. Pensi che io abbia solo un prigioniero qui? Dammene il nome.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+". È qui?";
			link.l1.go = "CapComission2";
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "Lo era. L'ho venduto a quel proprietario di piantagioni delle Barbados - colonnello Bishop, quando era qui una settimana fa.";
				link.l1 = "Maledizione...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				pchar.quest.CaptainComission_SellSlave.over = "yes";
				dialog.text = "Ah, finalmente. Stavo pensando di venderlo a quel proprietario di piantagioni da Barbados, sarà qui tra una settimana o due... Hai un riscatto"+GetSexPhrase("","")+"?";
				link.l1 = "Guarda, "+NPChar.name+" , c'è un piccolo problema... In realtà, non ho così tanti soldi. Ma sono pronto a lavorare.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "È bene che non l'abbiate venduto. Ecco le vostre monete - 150.000 pesos. Dove posso prenderlo?"link.l2.go ="CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "Sei stato troppo lento... E perché ti preoccupi di lui? Ho trattato solo con i suoi parenti.";
			link.l1 = "Hanno chiesto a me di venire qui.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "Ebbene, sei in ritardo. Non posso fare nulla.";
			link.l1 = "Ascolta, per quanto l'hai venduto se non è un segreto?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Eh, non lo è. Ma non te lo dirò... Riderai se lo faccio. Ha-ha-ha-ha! Addio.";
			link.l1 = "Arrivederci.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(1) == 0)
			{
				dialog.text = "Beh, beh... Ho un affare... Non so nemmeno da dove cominciare. Ho bisogno di affondare un pirata che è andato troppo oltre.";
				link.l1 = "Non può semplicemente essere ucciso nella giungla?";
				link.l1.go = "CapComission2_2_1";
			}
			else
			{
				dialog.text = "Bene, "+pchar.name+", sai, non funziona così. Torna con i soldi e avrai il tuo deboluccio, ah-ah.";
				link.l1 = "Bene, addio allora.";
				link.l1.go = "exit";
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					AddQuestRecord("CaptainComission1", "31");
					AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
				}	
				pchar.GenQuest.CaptainComission.RepeatSpeak = true;
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "Non è così che funziona il business, lo sai... Non ho bisogno della sua morte, devo insegnare a certa gente a evitare di prendere la mia parte del bottino. Ma se finisce per nutrire gli squali, non mi dispiacerà.";
			link.l1 = "Perché non mandi la tua gente dietro di lui?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Mh.. Beh "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+" ha convinto alcuni pirati che la loro parte di bottino sarà tenuta nel nostro nascondiglio non lontano da "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gen")+". Le loro due navi '"+pchar.GenQuest.CaptainComission.ShipName1+"' e '"+pchar.GenQuest.CaptainComission.ShipName2+"' ha levato l'ancora poco tempo fa e navigato verso "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island+"Abl")+". Ora capisci perché non posso fidarmi dei miei uomini per fare quel lavoro?";
			link.l1 = "Capisco. Quanto tempo ho?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "Da 12 a 15 giorni, non di più. È importante per me che non arrivino al nascondiglio, sarebbe assurdo affondarli con un carico prezioso. In quel caso, sarebbe meglio se lo portassero qui...";
			link.l1 = "Bene, sono dentro. Cercherò di prenderli.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Abl"));
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Dat"));
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);	
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";	
		break;
		
		case "CapComission2_3":
			dialog.text = "Non preoccuparti. I miei uomini lo consegneranno alla tua nave. E perché ti importa di lui?";
			link.l1 = "Non lo faccio. I suoi parenti mi hanno chiesto di consegnarlo.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Ah, perfetto. Quasi mi dispiaceva dare un prezzo così basso per il tuo uomo. Ha-ha-ha-ha. Addio.";
			link.l1 = "Arrivederci.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));			
			addMoneyToCharacter(pchar, -150000);
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission3":
			dialog.text = "Bene, "+GetFullName(pchar)+", hai affondato il mio compagno? He-he-he...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "No. Non sono riuscito a prenderli. E non li ho incontrati al ritorno.";
				link.l1.go = "CapComission4";
			}
			else
			{
				if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
				{
					link.l1 = "L'ho fatto. Li ho mandati a nutrire gli squali.";
					link.l1.go = "CapComission5";
				}
			}	
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "Maledizione! Comunque, non importa ora! Qual sarà il tuo prossimo suggerimento?";
			link.l1 = "Forse hai un lavoro più facile per me?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Ascolta, "+NPChar.name+", abbassa il prezzo per il prigioniero...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "No.";
			link.l1 = "Addio allora...";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");			
		break;
		
		case "CapComission4_2":
			dialog.text = "Abbassare il prezzo?! Ho appena perso la mia merce a causa della tua incompetenza! Ora posso alzare il prezzo! Puoi prenderlo per 200.000 pesos se vuoi, o puoi andartene all'inferno da qui!";
			link.l1 = "È troppo costoso... Addio...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "Maledizione, va bene, prendi la tua moneta.";
				link.l2.go = "CapComission4_5";
			}	
		break;
				
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Potete prendere questo debole...";
			link.l1 = "Addio.";
			link.l1.go = "exit";
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
				
		case "CapComission5":
			dialog.text = "Ah-ah! Ben fatto! Prendi il tuo debole e buona fortuna.";
			link.l1 = "Grazie. Addio.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;
				
		case "CapComission6":
			dialog.text = "Hai portato i soldi, Charles? Non stavo scherzando riguardo alla vendita di quell'uomo alla piantagione";			
			link.l1 = "Ascolta, "+NPChar.name+", c'è un problema... Non ho così tanti soldi. Ma sono pronto a lavorare.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "È bene che tu non lo abbia venduto. Ecco le tue monete - 150.000 pesos. Dove posso prenderlo?"link.l2.go ="CapComission2_3";
			}			
		break;
		
		//Захват пассажиров
		case "Marginpassenger":
			dialog.text = "E perché ti importa di quello che faccio? Sai, sarebbe meglio se te ne andassi...";
			link.l1 = "Tshh, calmati. Ho una proposta d'affari per te. Riguarda il tuo prigioniero.";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Ah, va bene. Chi vuoi riscattare?";
			link.l1 = "Aspetta. Non sono qui per comprare, sono qui per offrirti di comprare un prigioniero. Beh, e avrai l'opportunità di ottenere un riscatto per lui.";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "Mh. E perché hai bisogno della mia agenzia? Non vorresti ottenere i soldi direttamente per te stesso?";
			link.l1 = "È piuttosto rischioso per me. Potrei avere problemi con le autorità.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Ah-h... va bene allora. Diamo un'occhiata. Chi è il tuo prigioniero?";
			link.l1 = "Questo è "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Capisco. Sarebbe un bel commercio se non stai mentendo. Suppongo che potrei pagarti, per quest'uomo, "+iTemp+" pesos, oppure darti alcune informazioni interessanti. La scelta è tua.";
			link.l1 = "È meglio che prenda la moneta. Ne ho avuto abbastanza di questo affare...";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "Ah! Raccontami di più. Sono sicuro che avrai qualcosa di interessante da darmi.";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "Allora soldi. Prendili. Ora, non è il tuo problema. Porta qui l'oggetto della vendita.";
			link.l1 = "Dovrebbe essere già vicino alle porte della città. Grazie! Mi hai davvero aiutato.";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Prego, portami di più... Ci vediamo!";
			link.l1 = "Buona fortuna...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			ref sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GetRandomGood(FLAG_GOODS_TYPE_EXPORT + FLAG_GOODS_TYPE_UNIQUE, FLAG_GOODS_VALUABLE_WOOD);
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (hrand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "È bello fare affari con un uomo intelligente. Ora ascolta: tra pochi giorni "+XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat")+" arriverà un' spedizione spagnola dal continente, carica di merci di valore. Saranno in attesa di una nave che dovrebbe prelevare il carico. Se arrivi lì in una settimana, avrai l'opportunità di prendere il carico per te stesso.\nSe fossi in te, sarei già in movimento verso la mia nave. E porta il prigioniero qui.";
					link.l1 = "Grazie! Le merci saranno una bella compensazione per i miei guai. E il mio passeggero dovrebbe già essere vicino alle porte della città. Sarà portato a te.";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "È buono fare affari con un uomo intelligente. Ora ascolta: tra circa una settimana una brigantina spagnola '"+pchar.GenQuest.Marginpassenger.ShipName1+"' carico di merci preziose salperà da "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen")+" a "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen")+". Se ti sbrighi, lo prenderai facilmente.\nSei ancora qui? Se fossi in te, sarei già in viaggio verso la mia nave. E porta il prigioniero qui.";
					link.l1 = "Grazie! Le merci saranno una buona compensazione per i miei guai. E il mio passeggero deve essere vicino alle porte della città. Ti sarà portato.";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen"));
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}
