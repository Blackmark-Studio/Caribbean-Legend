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
				dialog.text = "Que veux-tu? Ah-ha, tu es le participant de la régate! Ai-je raison?";
				link.l1 = "Exactement, monsieur. J'ai besoin de m'enregistrer ici selon les règles.";
				link.l1.go = "Regata_check";
				break;
			}
			//регата
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quel genre de questions ?","Que veux-tu, "+GetAddress_Form(NPChar)+"?"),"Vous avez déjà essayé de me poser une question "+GetAddress_Form(NPChar)+"...","Vous parlez de cette question pour la troisième fois aujourd'hui...","Écoutez, si vous n'avez rien à me dire au sujet des affaires du port, alors ne me dérangez pas avec vos questions.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis.","Je n'ai rien à dire."),"Peu importe.","En effet, la troisième fois déjà...","Désolé, mais je ne suis pas intéressé par les affaires du port pour l'instant.",npchar,Dialog.CurrentNode);
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
		if(int(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			bool bRegLugger = int(RealShips[int(pchar.ship.type)].basetype) == SHIP_LUGGER || int(RealShips[int(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Beliz") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
			dialog.text = "Monseigneur ! Vous avez enfreint les règles de la régate et je dois vous disqualifier. Je suis désolé. Vous ne participez pas au prochain voyage. J'ai déjà préparé une dépêche pour Port-Royal.";
			link.l1 = "Eh... quel dommage ! Mais je ne peux rien y faire, tu étais trop vigilant. Adieu !";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Regata");
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
			AddQuestRecord("Regata", "45");
			CloseQuestHeader("Regata");
			}
			else
			{
			pchar.questTemp.Regata.SecondTransitionTime = GetPastTime("hour", int(pchar.questTemp.Regata.StartYear), int(pchar.questTemp.Regata.StartMonth), int(pchar.questTemp.Regata.StartDay), float(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//истратил ГГ в часах на 1+2 переход
			dialog.text = "Allons vous enregistrer : Capitaine "+GetFullName(pchar)+", le navire est "+pchar.Ship.Name+"... Temps de régate en heures est "+int(pchar.questTemp.Regata.SecondTransitionTime)+". C'est fait, votre résultat est enregistré, vous pouvez continuer votre chemin.";
			link.l1 = "Dis-moi mon rang.";
			link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = "Vous êtes ici mais je ne vois pas votre navire. Où est-il ?";
			link.l1 = "Je suis désolé, monsieur. Je vais transférer mon navire au port immédiatement.";
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
				if (pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp) < int(pchar.questTemp.Regata.SecondTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);//имя ближайшего противника
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);//его корабль
					pchar.questTemp.Regata.ContraIndex = sTemp;
				}
			}
			if (n==1)
			{
			dialog.text = "Vous êtes en tête. Félicitations! Continuez comme ça!";
			link.l1 = "Merci !";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "10");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "Vous êtes le dernier. Vous devriez vous dépêcher.";
				link.l1 = "Je suis en route!";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "15");
				}
				else
				{
					if (n==2)
					{
					dialog.text = "Vous êtes le second. Le chef est "+sName+" sur le navire "+sShip+"Je suppose que tu peux encore le distancer.";
					link.l1 = "Merci ! J'essaierai !";
					link.l1.go = "exit";
					AddQuestRecord("Regata", "11");
					}
					else
					{
					dialog.text = "Votre rang est "+n+". Votre adversaire le plus proche est "+sName+" sur le navire "+sShip+".";
					link.l1 = "Merci !";
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
