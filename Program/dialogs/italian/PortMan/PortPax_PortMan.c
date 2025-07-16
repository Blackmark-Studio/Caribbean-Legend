// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool ok;
    int iTest;
    ref rColony, sld;
    string sFrom_sea = "";
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//регата
			if (CheckAttribute(pchar, "questTemp.Regata.Go") && !CheckAttribute(npchar, "quest.regatatalk"))
			{
				dialog.text = "Cosa vuoi? A-ha, sei il partecipante alla regata! Ho ragione?";
				link.l1 = "Esattamente, signore. Devo registrarmi qui secondo le regole.";
				link.l1.go = "Regata_check";
				break;
			}
			//регата
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Che tipo di domande?","Cosa vuoi, "+GetAddress_Form(NPChar)+"?"),"Hai già provato a farmi una domanda "+GetAddress_Form(NPChar)+"...","Stai parlando della stessa domanda per la terza volta oggi...","Guarda, se non hai nulla da dirmi riguardo agli affari del porto, allora non disturbarmi con le tue domande.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea.","Non ho nulla di cui parlare."),"Non importa.","Infatti, già la terza volta...","Mi dispiace, ma per ora non mi interessano le questioni del porto.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
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
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Beliz") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
			dialog.text = "Signore! Avete infranto le regole della regata e devo squalificarvi. Mi dispiace. Non parteciperete al prossimo viaggio. Ho già preparato un dispaccio per Port-Royal.";
			link.l1 = "Eh... che peccato! Ma non posso fare nulla qui, sei stato troppo vigile. Addio!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Regata");
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
			AddQuestRecord("Regata", "45");
			CloseQuestHeader("Regata");
			}
			else
			{
			pchar.questTemp.Regata.SecondTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//истратил ГГ в часах на 1+2 переход
			dialog.text = "Facciamoci registrare: Capitano "+GetFullName(pchar)+", la nave è "+pchar.Ship.Name+"... Il tempo della regata in ore è "+sti(pchar.questTemp.Regata.SecondTransitionTime)+". Fatto, il tuo risultato è registrato, puoi continuare la tua strada.";
			link.l1 = "Ditemi il mio grado.";
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
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp)));
				if (pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.SecondTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);//имя ближайшего противника
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);//его корабль
					pchar.questTemp.Regata.ContraIndex = sTemp;
				}
			}
			if (n==1)
			{
			dialog.text = "Sei in testa. Congratulazioni! Continua così!";
			link.l1 = "Grazie!";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "10");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "Sei l'ultimo. Dovresti sbrigarti.";
				link.l1 = "Sono sulla mia strada!";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "15");
				}
				else
				{
					if (n==2)
					{
					dialog.text = "Sei il secondo. Il leader è "+sName+" sulla nave "+sShip+". Suppongo che tu possa ancora seminargli.";
					link.l1 = "Grazie! Ci proverò!";
					link.l1.go = "exit";
					AddQuestRecord("Regata", "11");
					}
					else
					{
					dialog.text = "Il tuo rango è "+n+". Il tuo avversario più vicino è "+sName+" sulla nave "+sShip+".";
					link.l1 = "Grazie!";
					link.l1.go = "exit";
					if (n==3) AddQuestRecord("Regata", "12");
					if (n==4) AddQuestRecord("Regata", "13");
					if (n==5) AddQuestRecord("Regata", "14");
					}
				}
			}
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 30);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 30);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 30);//скрытность
			npchar.quest.regatatalk = "true";
			pchar.questTemp.Regata.Portpax = "true";//отметка Порт Принса
			pchar.quest.Regata_Check1.win_condition.l1 = "location";
			pchar.quest.Regata_Check1.win_condition.l1.location = "Hispaniola1";
			pchar.quest.Regata_Check1.function = "RegataCheck";//проверка 1
			pchar.quest.Regata_Check2.win_condition.l1 = "location";
			pchar.quest.Regata_Check2.win_condition.l1.location = "PuertoRico";
			pchar.quest.Regata_Check2.function = "RegataCheck";//проверка 2
			pchar.quest.Regata_Check3.win_condition.l1 = "location";
			pchar.quest.Regata_Check3.win_condition.l1.location = "Nevis";
			pchar.quest.Regata_Check3.function = "RegataCheck";//проверка 3
			pchar.quest.Regata_Check.win_condition.l1 = "location";
			pchar.quest.Regata_Check.win_condition.l1.location = "Antigua";
			pchar.quest.Regata_Check.function = "RegataCheck";//проверка 4
			pchar.questTemp.Regata.AttackIsland = "PuertoRico";
			pchar.questTemp.Regata.AttackNation = SPAIN;
			pchar.quest.Regata_Attack.win_condition.l1 = "location";
			pchar.quest.Regata_Attack.win_condition.l1.location = "PuertoRico";
			pchar.quest.Regata_Attack.function = "RegataAttack_Lugger";
			pchar.quest.Regata_Attack1.win_condition.l1 = "location";
			pchar.quest.Regata_Attack1.win_condition.l1.location = "PuertoRico";
			pchar.quest.Regata_Attack1.function = "RegataAttack_Corvette";//вторая засада
			pchar.quest.Regata_Hunter.win_condition.l1 = "location";
			pchar.quest.Regata_Hunter.win_condition.l1.location = "Nevis";
			pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";//ДУ у Невиса
			pchar.questTemp.Regata.Town = "Sentjons";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Sentjons_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//вход в ПУ ночью
			//ситуации
			log_info(pchar.questTemp.Regata.ContraIndex);
			pchar.questTemp.Regata.Index = n;
			pchar.quest.Regata_Contra.win_condition.l1 = "location";
			pchar.quest.Regata_Contra.win_condition.l1.location = "Portpax_town";
			pchar.quest.Regata_Contra.function = "Contra_Regata";//контрики с пушками
			pchar.quest.Regata_Padre.win_condition.l1 = "location";
			pchar.quest.Regata_Padre.win_condition.l1.location = "Sentjons_town";
			pchar.quest.Regata_Padre.function = "Padre_Regata";//падре в Сент Джонсе
			sld = characterFromId("SentJons_Priest");
			LAi_RemoveLoginTime(sld);
		break;
		//регата

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
