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
				dialog.text = "Mit akarsz? A-ha, ön a regatta résztvevôje! Igazam van?";
				link.l1 = "Így van, uram. Itt kell regisztrálnom a szabályok szerint.";
				link.l1.go = "Regata_check";
				break;
			}
			//регата
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdések?", "Mit akarsz, " + GetAddress_Form(NPChar) + "?"), "Már próbáltál kérdezni " + GetAddress_Form(NPChar) + "...", "Ma már harmadszor beszélsz valamilyen kérdésrôl...",
                          "Nézze, ha nincs mondanivalója a kikötô ügyeirôl, akkor ne zavarjon a kérdéseivel.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam.", "Nincs mirôl beszélnem."), "Nevermind.", "Valóban, már harmadszor...", "Sajnálom, de egyelôre nem érdekelnek a kikötô ügyei.", npchar, Dialog.CurrentNode);
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
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Portpax") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
			dialog.text = "Hm... Megszegted a regatta szabályait, ezért ki kell, hogy zárjalak. Sajnálom. Nem vehetsz részt a következô hajón. Már elôkészítettem egy küldeményt Kikötô-Royalba.";
			link.l1 = "Eh... milyen kár! De itt nem tehetek semmit, túl éber voltál. Viszontlátásra!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Regata");
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
			AddQuestRecord("Regata", "45");
			CloseQuestHeader("Regata");
			}
			else
			{
			pchar.questTemp.Regata.ThirdTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//истратил ГГ в часах на 1+2+3 переход
			dialog.text = "Regisztráljunk: kapitány "+ GetFullName(pchar) +", hajó "+pchar.Ship.Name+"... A regatta ideje órákban: "+sti(pchar.questTemp.Regata.ThirdTransitionTime)+". Kész, az eredményed regisztrálva, folytathatod az utadat.";
			link.l1 = "Mondd meg a rangomat.";
			link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = "Itt vagy, de nem látom a hajódat. Hol van?";
			link.l1 = "Sajnálom, uram. Azonnal átviszem a hajómat a kikötôbe.";
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
				if (pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.ThirdTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);//имя ближайшего противника
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);//его корабль
				}
			}
			if (n==1)
			{
			dialog.text = "Te vezetsz. Gratulálok! Csak így tovább!";
			link.l1 = "Köszönjük!";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "16");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "Te vagy az utolsó ember. Sietned kell.";
				link.l1 = "Már úton vagyok!";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "21");
				}
				else
				{
					if (n==2)
					{
					dialog.text = "Te vagy a második. A vezetô "+sName+" a hajón "+sShip+". Feltételezem, hogy még mindig le tudod ôt elôzni.";
					link.l1 = "Köszi! Köszi! Megpróbálom!";
					link.l1.go = "exit";
					AddQuestRecord("Regata", "17");
					}
					else
					{
					dialog.text = "A rangod: "+n+". A legközelebbi ellenfeled "+sName+" a "+sShip+"hajón .";
					link.l1 = "Köszönjük!";
					link.l1.go = "exit";
					if (n==3) AddQuestRecord("Regata", "18");
					if (n==4) AddQuestRecord("Regata", "19");
					if (n==5) AddQuestRecord("Regata", "20");
					}
				}
			}
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 30);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 30);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 30);//скрытность
			npchar.quest.regatatalk = "true";
			pchar.questTemp.Regata.Sentjons = "true";//отметка Сент-Джонса
			pchar.quest.Regata_Check1.win_condition.l1 = "location";
			pchar.quest.Regata_Check1.win_condition.l1.location = "Guadeloupe";
			pchar.quest.Regata_Check1.function = "RegataCheck";//проверка 1
			pchar.quest.Regata_Check2.win_condition.l1 = "location";
			pchar.quest.Regata_Check2.win_condition.l1.location = "Martinique";
			pchar.quest.Regata_Check2.function = "RegataCheck";//проверка 2
			pchar.quest.Regata_Check3.win_condition.l1 = "location";
			pchar.quest.Regata_Check3.win_condition.l1.location = "Dominica";
			pchar.quest.Regata_Check3.function = "RegataCheck";//проверка 3
			pchar.quest.Regata_Check.win_condition.l1 = "location";
			pchar.quest.Regata_Check.win_condition.l1.location = "Barbados";
			pchar.quest.Regata_Check.function = "RegataCheck";//проверка 4
			pchar.questTemp.Regata.AttackIsland = "Guadeloupe";
			pchar.questTemp.Regata.AttackNation = PIRATE;
			pchar.quest.Regata_Attack.win_condition.l1 = "location";
			pchar.quest.Regata_Attack.win_condition.l1.location = "Guadeloupe";
			pchar.quest.Regata_Attack.function = "RegataAttack_Lugger";
			pchar.quest.Regata_Attack1.win_condition.l1 = "location";
			pchar.quest.Regata_Attack1.win_condition.l1.location = "Guadeloupe";
			pchar.quest.Regata_Attack1.function = "RegataAttack_Brigantine";//третья засада
			pchar.quest.Regata_Hunter.win_condition.l1 = "location";
			pchar.quest.Regata_Hunter.win_condition.l1.location = "Martinique";
			pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";//ДУ у Мартиники
			pchar.questTemp.Regata.Town = "Bridgetown";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back"; // mitrokosta фикс неправильного локатора
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//вход в ПУ ночью
			//ситуации
			pchar.quest.Regata_SpgGirl.win_condition.l1 = "location";
			pchar.quest.Regata_SpgGirl.win_condition.l1.location = "Sentjons_town";
			pchar.quest.Regata_SpgGirl.function = "RegataSpyglassGirl";//девушка с подзорной трубой
			pchar.quest.Regata_Attack2.win_condition.l1 = "location";
			pchar.quest.Regata_Attack2.win_condition.l1.location = "Antigua";
			pchar.quest.Regata_Attack2.function = "RegataAttack_Brander";//нападение брандера
			i = FindColony("Bridgetown");
			colonies[i].DontSetShipInPort = true; //не ставить корабли в порту
			pchar.quest.Regata_Siege.win_condition.l1 = "location";
			pchar.quest.Regata_Siege.win_condition.l1.location = "Barbados";
			pchar.quest.Regata_Siege.function = "RegataSiege";//на квест по вывозу жителей
		break;
		//регата
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
