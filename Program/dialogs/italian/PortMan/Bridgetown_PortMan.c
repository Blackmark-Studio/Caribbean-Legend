// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//регата
			if (CheckAttribute(pchar, "questTemp.Regata.Go") && !CheckAttribute(npchar, "quest.regatatalk"))
			{
				dialog.text = "Cosa desideri? Ah-ah, partecipi alla regata! Ho ragione?";
				link.l1 = "Esattamente, signore. Devo registrarmi qui secondo le regole.";
				link.l1.go = "Regata_check";
				break;
			}
			//регата
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Che tipo di domande?","Cosa vuoi, "+GetAddress_Form(NPChar)+"?"),"Hai già provato a farmi una domanda "+GetAddress_Form(NPChar)+"...","Hai parlato di qualche questione per la terza volta oggi...","Guarda, se non hai nulla da dirmi riguardo agli affari del porto, non disturbarmi con le tue domande.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea.","Non ho nulla di cui parlare."),"Non importa.","Infatti, già la terza volta...","Mi dispiace, ma per ora non mi interessano le questioni del porto.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Sto navigando verso Blueweld per vendere della paprika. Dimmi, signore, hai dei passeggeri che si dirigono verso Blueweld? O almeno a Port-Royal. Sarebbe bello guadagnare qualcosa da un passeggero, potrebbe aiutare a pagare il salario dell'equipaggio. L'ho già ridotto al minimo, ma questi bastardi pigri continuano a chiedere soldi...";
                link.l1.go = "PortofficeDone";
            }
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "barbados")
			{
				link.l1 = "C'era un galeone chiamato 'Admirable' carico a Philipsburg sotto il comando di Gaius Marchais. Doveva consegnare qui un carico di paprika. Puoi aiutarmi a trovare questo capitano?";
                link.l1.go = "guardoftruth";
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && !CheckAttribute(npchar, "quest.garpiya"))
			{
				if (CheckAttribute(npchar, "questTemp.caleuche"))
				{
					link.l1 = "Volevo chiedere di un xebec con un nome strano.";
					link.l1.go = "caleuche_2";
				}
				else
				{
					link.l1 = "Sentii dire che una xebec appartiene a un Capitano Jack... o Jackson visita spesso il vostro porto. Potrebbe dirmi dove cercarlo?";
					link.l1.go = "caleuche";
				}
			}
		break;

		//Голландский гамбит
		case "PortofficeDone":
			dialog.text = "Sfortunatamente, non ci sono passeggeri per Blueweld né per Port-Royal. Torna domani o dopodomani.";
			link.l1 = "Peccato. Arrivederci allora.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-9");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				DelMapQuestMarkCity("Bridgetown");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;

		//регата
		case "Regata_check":
		iTest = FindColony(npchar.city); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Sentjons") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
				dialog.text = "Mh... Hai infranto le regole della regata e devo squalificarti. Mi dispiace. Non parteciperai al prossimo viaggio. Ho già preparato una spedizione per Port-Royal.";
				link.l1 = "Eh... che peccato! Ma non posso fare nulla qui, sei stato troppo vigilante. Addio!";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Regata");
				AddQuestRecord("Regata", "45");
				CloseQuestHeader("Regata");
			}
			else
			{
				pchar.questTemp.Regata.FourthTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//истратил ГГ в часах на 1+2+3+4 переход
				dialog.text = "Potresti aver notato, capitano, che la città è sotto assedio. Ci aspettiamo che gli spagnoli ci attacchino da un momento all'altro e stiamo mobilitando le nostre forze. Ma la regata continua\nIscriviamoci: capitano "+GetFullName(pchar)+", la nave è - "+pchar.Ship.Name+"... Il tempo della regata in ore è "+sti(pchar.questTemp.Regata.FourthTransitionTime)+". Fatto, il tuo risultato è registrato, puoi continuare la tua strada.";
				link.l1 = "Dimmi il mio grado.";
				link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = "Sei qui ma non vedo la tua nave. Dove si trova?";
			link.l1 = "Mi dispiace, signore. Trasferirò immediatamente la mia nave al porto.";
			link.l1.go = "exit";
		}
		break;
		
		case "Regata_info":
			int n=1;
			string sTemp, sName, sShip;
			for (int i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				if (pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FourthTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);//имя ближайшего противника
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);//его корабль
				}
			}
			if (n==1)
			{
			dialog.text = "Ah, sì... Mi dispiace, ero troppo occupato per quello. Sei il primo.";
			link.l1 = "Capisco. Grazie per le tue informazioni.";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "22");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "Ah, sì... Mi dispiace, sono troppo impegnato per questo. Sei l'ultimo.";
				link.l1 = "Capisco. Grazie per le tue informazioni.";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "27");
				}
				else
				{
					if (n==2)
					{
						dialog.text = "Ah, sì... Mi dispiace, sono troppo occupato per questo. Sei il secondo. C'è solo un capitano che ti supera. Il suo nome è "+sName+" sulla nave "+sShip+".";
						link.l1 = "Capisco. Grazie per le tue informazioni.";
						link.l1.go = "exit";
						AddQuestRecord("Regata", "23");
					}
					else
					{
						dialog.text = "Ah, sì... Mi dispiace, sono troppo occupato per questo. Il tuo grado è "+n+" . Il tuo avversario più vicino è "+sName+" sulla nave "+sShip+".";
						link.l1 = "Capisco. Grazie per le tue informazioni.";
						link.l1.go = "exit";
						if (n==3) AddQuestRecord("Regata", "24");
						if (n==4) AddQuestRecord("Regata", "25");
						if (n==5) AddQuestRecord("Regata", "26");
					}
				}
			}
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 30);//защита
			AddCharacterExpToSkill(pchar, "Repair", 30);//починка
			AddCharacterExpToSkill(pchar, "Fortune", 30);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 30);//скрытность
			npchar.quest.regatatalk = "true";
			pchar.questTemp.Regata.Bridgetown = "true";//отметка Бриджтауна
			pchar.quest.Regata_Check1.win_condition.l1 = "location";
			pchar.quest.Regata_Check1.win_condition.l1.location = "Curacao";
			pchar.quest.Regata_Check1.function = "RegataCheck";//проверка 1
			pchar.quest.Regata_Check2.win_condition.l1 = "location";
			pchar.quest.Regata_Check2.win_condition.l1.location = "Caracas";
			pchar.quest.Regata_Check2.function = "RegataCheck";//проверка 2
			pchar.quest.Regata_Check3.win_condition.l1 = "location";
			pchar.quest.Regata_Check3.win_condition.l1.location = "PortoBello";
			pchar.quest.Regata_Check3.function = "RegataCheck";//проверка 3
			pchar.quest.Regata_Check.win_condition.l1 = "location";
			pchar.quest.Regata_Check.win_condition.l1.location = "Jamaica";
			pchar.quest.Regata_Check.function = "RegataCheck";//проверка 4
			pchar.questTemp.Regata.AttackIsland = "Curacao";
			pchar.questTemp.Regata.AttackNation = HOLLAND;
			pchar.quest.Regata_Attack.win_condition.l1 = "location";
			pchar.quest.Regata_Attack.win_condition.l1.location = "Curacao";
			pchar.quest.Regata_Attack.function = "RegataAttack_Brigantine";
			pchar.quest.Regata_Attack1.win_condition.l1 = "location";
			pchar.quest.Regata_Attack1.win_condition.l1.location = "Curacao";
			pchar.quest.Regata_Attack1.function = "RegataAttack_Corvette";//третья засада
			pchar.quest.Regata_Hunter.win_condition.l1 = "location";
			pchar.quest.Regata_Hunter.win_condition.l1.location = "Barbados";
			pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";//ДУ у Барбадоса
			pchar.quest.Regata_Finish.win_condition.l1 = "location";
			pchar.quest.Regata_Finish.win_condition.l1.location = "Jamaica";
			pchar.quest.Regata_Finish.function = "RegataFinishSea";
			pchar.quest.Regata_Finish1.win_condition.l1 = "location";
			pchar.quest.Regata_Finish1.win_condition.l1.location = "Portroyal_town";
			pchar.quest.Regata_Finish1.function = "RegataFinishTown";//финиш регаты
			//ситуации
			pchar.quest.Regata_Siege.win_condition.l1 = "location";
			pchar.quest.Regata_Siege.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.Regata_Siege.function = "RegataSiegeOfficer";//на квест по вывозу жителей
		break;
		//регата
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = "Sì, questo galeone era qui, si è liberato delle sue merci ed è partito dal nostro porto più tardi. Informazioni sulla sua destinazione... mh... nessuna, non c'è nulla. Mi dispiace, ma non c'è nulla che io possa fare.";
			link.l1 = "Capisco. Peccato... Continuerò a cercarlo.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			DialogExit();
			AddQuestRecord("Guardoftruth", "13");
			pchar.questTemp.Guardoftruth = "barbados1";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Signore, ho bisogno del nome esatto della nave. Abbiamo tonnellate di Jack e Jackson che passano attraverso il nostro porto. Quindi, qual è il nome?";
			link.l1 = "";
			Link.l1.edit = 2;
			link.l1.go = "caleuche_name";
			link.l2 = "Il problema è che non conosco il nome della sua vecchia tinozza. È strano, una donna uccello, nata...";
			link.l2.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Signore, vai a raccontare le tue storie e indovinelli alla taverna, qui abbiamo un'istituzione seria. O mi dici il nome di quella xebec, o smetti di disturbarmi dal mio lavoro.";
			link.l1 = "Bene, cercherò di scoprirlo.";
			link.l1.go = "exit";
			npchar.questTemp.caleuche = "true";
		break;
		
		case "caleuche_2":
			dialog.text = "Allora? Hai il nome della nave? Sto ascoltando.";
			link.l1 = "";
			Link.l1.edit = 2;
			link.l1.go = "caleuche_name";
		break;
		
		case "caleuche_name":
			if (GetStrSmallRegister(dialogEditStrings[2]) == "harpy")
			{
				dialog.text = "'Harpy'? Certo, conosco quella xebec. Il suo capitano è Reginald Jackson. Ma non è stato a Bridgetown per molto tempo. Ho sentito dire che ora lavora per la Compagnia Olandese delle Indie Occidentali. Quindi dovresti cercarlo a Willemstad.";
				link.l1 = "Grazie mille! Mi hai aiutato molto.";
				link.l1.go = "caleuche_3";
			}
			else
			{
				dialog.text = "Mi dispiace, ma non mi suona familiare. Sei sicuro che il tuo capitano sia mai stato qui, a Bridgetown?";
				link.l1 = "Sono sicuro. Va bene, forse troverò qualcosa ...";
				link.l1.go = "exit";
			}
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "18");
			pchar.questTemp.Caleuche.Garpiya = "gwik"; 
			npchar.quest.garpiya = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
