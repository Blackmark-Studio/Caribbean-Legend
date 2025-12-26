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
				link.l1 = "그렇습니다, 나리. 규정에 따라 여기에서 등록해야 합니다.";
				link.l1.go = "Regata_check";
				break;
			}
			//регата
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문인데?","무엇을 원하시오, "+GetAddress_Form(NPChar)+"?"),"이미 나에게 질문을 하려고 했잖아 "+GetAddress_Form(NPChar)+"...","오늘만 세 번째로 이 질문을 꺼내는군...","봐라, 항구 일에 대해 할 말이 없으면 쓸데없는 질문으로 나를 귀찮게 하지 마라.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었소.","나랑 할 얘기는 없어."),"신경 쓰지 마시오.","정말, 벌써 세 번째군...","미안하지만, 지금은 항구 일에 관심이 없어.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "나는 블루웰드로 항해해서 파프리카를 팔 생각이오. 그런데, 이봐, 혹시 블루웰드로 가는 승객이 있나? 아니면 최소한 포트 로얄로 가는 사람이라도. 승객한테서 돈 좀 받으면 선원들 월급 주는 데 도움이 될 텐데. 이미 월급을 최소로 줄였는데도 이 게으른 놈들은 여전히 돈 달라고 징징거린다니까...\n";
                link.l1.go = "PortofficeDone";
            }
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "barbados")
			{
				link.l1 = "필립스버그에서 가이우스 마르셰 선장이 지휘하는 'Admirable'이라는 갤리온이 화물을 실었습니다. 그가 이곳으로 파프리카를 실어오기로 되어 있었지요. 이 선장을 찾는 데 도와주실 수 있습니까?";
                link.l1.go = "guardoftruth";
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && !CheckAttribute(npchar, "quest.garpiya"))
			{
				if (CheckAttribute(npchar, "questTemp.caleuche"))
				{
					link.l1 = "이상한 이름을 가진 제벡에 대해 묻고 싶었소.";
					link.l1.go = "caleuche_2";
				}
				else
				{
					link.l1 = "잭 선장... 아니면 잭슨 선장 소유의 제벡이 자주 이 항구를 찾는다고 들었습니다. 그를 어디서 찾을 수 있는지 알려주실 수 있습니까?";
					link.l1.go = "caleuche";
				}
			}
		break;

		//Голландский гамбит
		case "PortofficeDone":
			dialog.text = "안타깝게도 블루웰드나 포트로얄로 가는 승객이 없습니다. 내일이나 모레 다시 오십시오.";
			link.l1 = "안타깝군. 그럼 이만.";
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
				dialog.text = "흠... 자네가 레가타의 규칙을 어겼으니 내가 실격 처리할 수밖에 없네. 유감이오. 다음 항해에는 참가할 수 없을 것이네. 나는 이미 포트 로얄로 보고서를 준비해 두었네.";
				link.l1 = "에이... 아쉽군! 하지만 내가 여기서 할 수 있는 건 없어, 네가 너무 경계했으니. 잘 가라!";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Regata");
				AddQuestRecord("Regata", "45");
				CloseQuestHeader("Regata");
			}
			else
			{
				pchar.questTemp.Regata.FourthTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//истратил ГГ в часах на 1+2+3+4 переход
				dialog.text = "선장님도 눈치채셨겠지만, 지금 도시가 포위당했습니다. 언제든 스페인군이 공격해올 수 있어 우리 병력을 동원하고 있습니다. 하지만 레가타는 여전히 진행됩니다\n등록합시다, 선장님 "+GetFullName(pchar)+", 배는 - "+pchar.Ship.Name+"... 레가타 시간(단위: 시간)은 "+sti(pchar.questTemp.Regata.FourthTransitionTime)+". 완료되었습니다, 결과가 기록되었으니 계속 가셔도 됩니다.";
				link.l1 = "내 계급을 말해 주시오.";
				link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = "여기 와 있긴 한데 네 배가 안 보여. 어디 있지?";
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
				if (pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FourthTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);//имя ближайшего противника
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);//его корабль
				}
			}
			if (n==1)
			{
			dialog.text = "아, 그렇군... 미안하오, 내가 너무 바빠서 그랬소. 당신이 첫 번째요.";
			link.l1 = "알겠소. 정보 주어서 고맙소.";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "22");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "아, 그래... 미안하오, 나는 그 일로 너무 바쁘오. 당신이 마지막이오.";
				link.l1 = "알겠소. 정보 고맙소.";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "27");
				}
				else
				{
					if (n==2)
					{
						dialog.text = "아, 그렇군... 미안하오, 나는 그 일로 너무 바쁘오. 그대는 두 번째요. 그대 앞에는 선장이 한 명 더 있소. 그의 이름은 "+sName+" 배 위에서 "+sShip+".";
						link.l1 = "알겠소. 정보 고맙소.";
						link.l1.go = "exit";
						AddQuestRecord("Regata", "23");
					}
					else
					{
						dialog.text = "아, 그래... 미안하지만, 나는 그럴 시간이 없네. 자네의 계급은 "+n+" . 당신의 가장 가까운 상대는 "+sName+" 배 위에서 "+sShip+".";
						link.l1 = "알겠소. 정보 고맙소.";
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
			dialog.text = "그래, 이 갤리온이 여기 있었고, 화물을 내려놓은 뒤 우리 항구를 떠났지. 목적지에 대한 정보는... 흠... 없어, 아무것도 없네. 미안하지만 내가 해줄 수 있는 게 없어.";
			link.l1 = "알겠소. 안타깝군... 계속 찾아보겠소.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			DialogExit();
			AddQuestRecord("Guardoftruth", "13");
			pchar.questTemp.Guardoftruth = "barbados1";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "나리, 배의 정확한 이름이 필요합니다. 우리 항구에는 잭과 잭슨이 워낙 많아서요. 그래서, 배 이름이 무엇입니까?";
			link.l1 = "";
			Link.l1.edit = 2;
			link.l1.go = "caleuche_name";
			link.l2 = "문제는, 그 녀석의 낡은 배 이름을 내가 모른다는 거야. 이상하게도, 어떤 여자 이름이었는데, 태어난...";
			link.l2.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "이봐, 네 얘기랑 수수께끼는 선술집에 가서나 해라. 여긴 점잖은 곳이야. 그 제벡의 이름을 말하든가, 아니면 내 일 방해하지 말고 꺼져.";
			link.l1 = "좋아, 알아보도록 하지.";
			link.l1.go = "exit";
			npchar.questTemp.caleuche = "true";
		break;
		
		case "caleuche_2":
			dialog.text = "그래서? 배 이름을 알고 있나? 듣고 있네.";
			link.l1 = "";
			Link.l1.edit = 2;
			link.l1.go = "caleuche_name";
		break;
		
		case "caleuche_name":
			if (GetStrSmallRegister(dialogEditStrings[2]) == "harpy")
			{
				dialog.text = "'Harpy'? 물론이지, 그 제벡을 알아. 선장은 레지널드 잭슨이야. 하지만 그가 브리지타운에 온 지는 오래되지 않았어. 지금은 네덜란드 서인도 회사에서 일한다는 소문을 들었지. 그러니 빌렘스타트에서 그를 찾아보는 게 좋겠어.";
				link.l1 = "정말 감사합니다! 큰 도움을 주셨습니다.";
				link.l1.go = "caleuche_3";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "죄송하지만, 기억나는 바가 없소. 정말로 당신네 선장이 이 브리지타운에 온 적이 있소?";
				link.l1 = "확실합니다. 좋아요, 어쩌면 뭔가 생각해낼 수도 있겠군 ...";
				link.l1.go = "exit";
			}
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "18");
			pchar.questTemp.Caleuche.Garpiya = "gwik"; 
			npchar.quest.garpiya = "true";
			AddLandQuestMarkToPhantom("GVIK", "HWIC_headclerk");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
