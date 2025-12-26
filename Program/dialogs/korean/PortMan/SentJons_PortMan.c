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
				dialog.text = "무슨 일이오? 아, 자네가 레가타 참가자구만! 맞지?";
				link.l1 = "맞습니다, 나리. 규정에 따라 여기서 등록해야 합니다.";
				link.l1.go = "Regata_check";
				break;
			}
			//регата
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문인데?","무슨 일이오, "+GetAddress_Form(NPChar)+"?"),"이미 나에게 질문을 하려고 했잖아 "+GetAddress_Form(NPChar)+"...","오늘만 세 번째로 그 질문을 꺼내는군...","봐라, 항구 일에 대해 할 말이 없다면 쓸데없는 질문으로 나를 귀찮게 하지 마라.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었소.","나한테 할 말 없어."),"신경 쓰지 마시오.","정말, 벌써 세 번째로군...","미안하지만, 지금은 항구 일에 관심 없어.",npchar,Dialog.CurrentNode);
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
			dialog.text = "흠... 자네가 레가타 규칙을 어겼으니 내가 실격 처리해야 하네. 유감이오. 다음 항해에는 참가할 수 없네. 이미 포트 로얄로 공문을 준비해 두었네.";
			link.l1 = "에이... 아쉽군! 하지만 내가 여기서 할 수 있는 건 없어, 네가 너무 경계했으니까. 잘 가라!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Regata");
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
			AddQuestRecord("Regata", "45");
			CloseQuestHeader("Regata");
			}
			else
			{
			pchar.questTemp.Regata.ThirdTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//истратил ГГ в часах на 1+2+3 переход
			dialog.text = "등록합시다: 선장 "+GetFullName(pchar)+", 배는 "+pchar.Ship.Name+"... 레가타의 시간(단위: 시간)은 "+sti(pchar.questTemp.Regata.ThirdTransitionTime)+". 완료되었습니다, 결과가 기록되었으니 계속 가십시오.";
			link.l1 = "내 계급을 말해 줘.";
			link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = "여기 있긴 한데 네 배가 안 보여. 어디 있지?";
			link.l1 = "죄송합니다, 나리. 즉시 제 배를 항구로 옮기겠습니다.";
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
			dialog.text = "당신이 선두에 있습니다. 축하합니다! 계속 힘내세요!";
			link.l1 = "고맙소!";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "16");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "네가 마지막 사람이야. 서둘러야 해.";
				link.l1 = "가는 중이오!";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "21");
				}
				else
				{
					if (n==2)
					{
					dialog.text = "네가 둘째다. 우두머리는 "+sName+" 배에서 "+sShip+". 아직은 그를 따돌릴 수 있겠군.";
					link.l1 = "고마워! 한번 해볼게!";
					link.l1.go = "exit";
					AddQuestRecord("Regata", "17");
					}
					else
					{
					dialog.text = "당신의 계급은 "+n+". 당신의 가장 가까운 상대는 "+sName+" 배 위에서 "+sShip+".";
					link.l1 = "감사합니다!";
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
