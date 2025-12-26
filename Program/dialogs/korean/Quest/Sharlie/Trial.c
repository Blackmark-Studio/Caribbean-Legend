// диалоги НПС по квесту 'Карибские нравы'
void ProcessDialogEvent()
{
	ref NPChar, sld, rColony;
	aref Link, NextDiag;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "뭘 원하지?";
			link.l1 = "아니, 아무것도 없어.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// Жерар Лекруа
		case "lecrua":
			pchar.quest.Trial_LineOver.over = "yes"; //снять таймер
			dialog.text = "안녕하십니까. 당신이 분명 "+GetFullName(pchar)+"?";
			link.l1 = "맞습니다, LeCroix 나리. 선장 "+GetFullName(pchar)+" 항상 대기 중입니다. 모스크바인 파데이가 당신을 추천했소...";
			link.l1.go = "lecrua_1";
			DelLandQuestMark(npchar);
		break;
		
		case "lecrua_1":
			iTemp = FindColony("Baster");
			rColony = GetColonyByIndex(iTemp);
			bOk = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			dialog.text = "그래, 그래. 내 친애하는 친구 파데이가 자네와 자네 처지에 대해 자세히 설명해 주었지. 문간에서 자네를 보자마자 바로 알았네. 말해보게, 선장, 어떤 배를 가지고 있나?";
			if(sti(pchar.ship.type) == SHIP_NOTUSED || !bOk)
			{
				link.l1 = "아... 지금은 배가 없소, 나리...";
				link.l1.go = "lecrua_noship";
			}
			else
			{
				link.l1 = "나는 가지고 있네 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype),"Name")))+", 그녀의 이름은 "+pchar.ship.name+".";
				if (6-sti(RealShips[sti(pchar.ship.type)].Class) < 0) link.l1.go = "lecrua_badship";
				else link.l1.go = "lecrua_2";
			}
		break;
		
		case "lecrua_noship":
			dialog.text = "하! 그런데 배도 없는 선장이 무슨 선장이오? 미안하오, 나리, 그런 경우라면 드릴 일이 없소. 행운을 빌겠소, 파데이에게 안부 전해주시오!";
			link.l1 = "흠...";
			link.l1.go = "lecrua_exit";
			sTotalTemp = "I don't have a ship at the moment";
		break;
		
		case "lecrua_badship":
			dialog.text = "글쎄, 그건 도저히 안 되겠군. 저건 배가 아니라 그냥 보트요, 나리! 유감이오, 나리, 당신은 그 역할에 어울리지 않소. 파데이에게 안부 전해 주시오, 좋은 하루 되시오!";
			link.l1 = "흠...";
			link.l1.go = "lecrua_exit";
			sTotalTemp = "My ship wasn't big enough for him";
		break;
		
		case "lecrua_exit":
			DialogExit();
			npchar.lifeday = 0;
			NextDiag.CurrentNode = "lecrua_repeat";
			AddQuestRecord("Trial", "3");
			AddQuestUserData("Trial", "sText", sTotalTemp);
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "lecrua_repeat":
			dialog.text = "우리는 이미 모든 것을 이야기했지요, 나리. 그렇지 않소?";
			link.l1 = "예, LeCroix 나리... 지금 가고 있습니다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "lecrua_repeat";
		break;
		
		case "lecrua_2":
			dialog.text = "훌륭하군. 그렇다면, 너는 내게 딱 맞는 인재로구나. 바로 바다로 나갈 준비가 되었나?";
			link.l1 = "예, 나리, 준비됐습니다. 무엇을 해야 합니까?";
			link.l1.go = "lecrua_3";
		break;
		
		case "lecrua_3":
			sld = characterFromId("BasTer_trader");
			dialog.text = "프랑스령 히스파니올라의 포르토프랭스에 소량의 화약과 폭탄을 전달해야 하오. 사령관이 한동안 기다리고 있으니, 시간 낭비하지 말고 서두르시오. 남은 시간은 약 열흘이오\n존경하는 "+GetFullName(sld)+" 그걸 당신 배에 실어 전달하는 일은 내가 맡겠소. 지휘관이 이 일에 대해 당신에게 5,000 에이트를 지불할 것이오.";
			link.l1 = "그게 전부인 일이오?";
			link.l1.go = "lecrua_4";
		break;
		
		case "lecrua_4":
			dialog.text = "오, 전혀 아닙니다, 나리. 탄약을 가져오면 사령관께서 진짜 임무를 설명해 주실 겁니다.\n이 화물은 앞으로 하게 될 일의 작은 전채 요리일 뿐이죠.\n하지만 두려워 마십시오, 일을 잘 해내면 큰돈을 벌 수 있을 테니.";
			link.l1 = "온전히 경청하겠습니다, 나리. 제 배는 화물을 실을 준비가 되어 있습니다.";
			link.l1.go = "lecrua_5";
		break;
		
		case "lecrua_5":
			dialog.text = "그럼 시간 낭비하지 맙시다, 선장님! 어서 배로 가서 출항 준비를 하십시오.";
			link.l1 = "간다!";
			link.l1.go = "lecrua_6";
		break;
		
		case "lecrua_6":
			DialogExit();
			NextDiag.CurrentNode = "lecrua_repeat";
			AddQuestRecord("Trial", "4");
			pchar.questTemp.Trial = "fraht";
			AddMapQuestMarkCity("PortPax", false);
			// belamour legendary edition халява по чекбоксу
			if(!bImCasual) SetFunctionTimerCondition("Trial_FrahtFail", 0, 0, 17, false); // таймер
			else NewGameTip("Exploration mode: timer is disabled.");
			SetFunctionTimerCondition("Trial_LecruaHide", 0, 0, 1, false); // таймер
			// груз
			SetCharacterGoods(pchar, GOOD_BOMBS, GetCargoGoods(pchar, GOOD_BOMBS)+2500);
			SetCharacterGoods(pchar, GOOD_POWDER, GetCargoGoods(pchar, GOOD_POWDER)+2500);
			// Sinistra Пасхалка с Диего
			pchar.quest.VsD_DiegoNachalo.win_condition.l1 = "Ship_location";
			pchar.quest.VsD_DiegoNachalo.win_condition.l1.location = "PortPax_town";
			PChar.quest.VsD_DiegoNachalo.win_condition = "VsD_DiegoNachalo";
			
			// отключить все враждебные энкаунтеры на глобальной карте
			pchar.worldmapencountersoff = "1";
			SetFunctionTimerCondition("DelNavigatorNoShow", 0, 0, 180, false);
			pchar.systeminfo.tutorial.navigatorTrial = true;
		break;
		
		// Флориан Шоке
		case "florian_deck":
			if(!bImCasual) pchar.quest.Trial_CannonFail.over = "yes"; // belamour legendary edition снять таймер
			DelMapQuestMarkShore("shore47");
			DelLandQuestMark(npchar);
			sld = CharacterFromID("PortRoyal_shipyarder");
			if(CheckAttribute(sld, "TrialDelQuestMark"))
			{
				DeleteAttribute(sld, "TrialDelQuestMark");
				DelLandQuestMark(sld);
				DelMapQuestMarkCity("PortRoyal");
			}
			dialog.text = "무엇을 도와드릴까요, 나리?";
			link.l1 = "안녕하십니까, 선장님. 당신이 플로리앙 쇼크 맞으시죠?";
			link.l1.go = "florian_deck_1";
		break;
		
		case "florian_deck_1":
			dialog.text = "그렇소. 그리고 자네는 포르토프랭스에서 온 우편선이 맞지 않소?";
			link.l1 = "그래, 자네를 위해 대포 열다섯 문을 준비했지. 기한이 정말 아슬아슬했어, 간신히 맞췄다네...";
			link.l1.go = "florian_deck_2";
		break;
		
		case "florian_deck_2":
			if (GetSquadronGoods(pchar, GOOD_CANNON_24) < 15)
			{
				dialog.text = "흠. 유머 감각이 독특하군, 나리! 그런데 이상하게도, 자네 배에서 대포 열다섯 문이 내리는 건 안 보이는데...";
				link.l1 = "저기, 말이야, 우리 배에 물이 새서 화물 일부를 바다에 던질 수밖에 없었어...";
				link.l1.go = "florian_deck_fail";
			}
			else
			{
				dialog.text = "반갑소, 선장님?..";
				link.l1 = ""+GetFullName(pchar)+". 선장 "+GetFullName(pchar)+".";
				link.l1.go = "florian_deck_3";
			}
		break;
		
		case "florian_deck_3":
			dialog.text = "만나서 반갑소. 시간 낭비 말고 이 대포들을 배에 실자고. 쉽지 않을 테니, 자네 부하들의 도움이 필요하겠군.";
			link.l1 = "우리가 알아서 할 테니. 이봐, 거기! 야드암에 블록과 타클 설치해!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Trial_TakeCannons");
		break;
		
		case "florian_deck_fail":
			dialog.text = "이 멍청한 놈아! 이런 간단한 일도 못 해내면, 다음 폭풍에 네 배는 틀림없이 가라앉을 거다. 네 배로 돌아가, 선장. 그리고 귀족 아가씨들한테 꽃이나 배달하는 네가 더 잘하는 일이나 해라. 아니면 차라리 유럽으로 돌아가서 신세계는 진짜 사내들에게 맡기라고. 좋은 하루 보내시오, 나리!";
			link.l1 = "하지만...";
			link.l1.go = "florian_deck_fail_1";
		break;
		
		case "florian_deck_fail_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			RemoveCharacterGoods(pchar, GOOD_CANNON_24, GetCargoGoods(pchar, GOOD_CANNON_24));
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			AddQuestRecord("Trial", "10");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
			ChangeCharacterNationReputation(pchar, FRANCE, -3);
		break;
		
		case "florian_deck_4":
			dialog.text = "휴, 정말 목이 타는 일이었군! 수고했소, 선장님! 보상으로 이백 두블룬을 받으시오.";
			link.l1 = "감사합니다!";
			link.l1.go = "florian_deck_5";
		break;
		
		case "florian_deck_5":
			TakeNItems(pchar, "gold_dublon", 200);
			dialog.text = "하지만 그게 전부가 아니오, 선장. 황금 더블 에스쿠도 75개를 더 벌고 싶으시오?";
			link.l1 = "그거 기대가 되긴 하지만, 나리께서 저에게 뭘 시키실지에 따라 다르겠군요.";
			link.l1.go = "florian_deck_6";
		break;
		
		case "florian_deck_6":
			dialog.text = "거짓말은 안 하겠소, 위험하오. 이미 알다시피, 나는 귀중한 화물을 실은 스페인 대형 갤리온을 노리고 숨어 있소. 그 배는 수리를 위해 조선소에 들어갔었지. 내 정보에 따르면, 어제 출항할 예정이었으나 출항하지 않았소\n게다가, 포르토벨로에 있는 내 첩자가 약속 장소에 나타나 내가 기다리던 소식을 전해주지 못했소. 스페인 놈들이 그를 체포한 게 아닌가 의심되오. 자네가 포르토벨로에 몰래 들어가 두 가지를 알아오면 돈을 주겠소. 왜 갤리온이 아직도 거기 있는지, 그리고 내 첩자에게 무슨 일이 생겼는지 말이오. 할 생각 있나?";
			link.l1 = "이런 작전에는 내가 제대로 된 훈련이 부족하오. 나는 신사이지, 첩자가 아니오. 오히려 내가 곤란에 처할 수도 있고, 그러면 당신을 도울 수도 없을 것이오.";
			link.l1.go = "florian_deck_bye";
			link.l2 = "위험해 보이지만, 이익이 될 것 같군. 감수하지. 네 사람 이름이 뭐고, 그 갈레온 이름은 뭐지?";
			link.l2.go = "florian_deck_7";
		break;
		
		case "florian_deck_bye":
			dialog.text = "거 참, 당당하시군. 무슨 말인지 알겠소. 그럼 이만, 선장님. 그리고 다시 한 번 도와주셔서 감사합니다!";
			link.l1 = "행운을 빕니다, Shoke 나리.";
			link.l1.go = "florian_deck_bye_1";
		break;
		
		case "florian_deck_bye_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			AddQuestRecord("Trial", "11");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "florian_deck_7":
			dialog.text = "그래, 잘 들어라. 내 부하 이름은 실반 라포레지만, 포르토벨로에서는 하이메 실리시오라는 상인으로 통하지. 갤리온 이름은 '알칸타라'다. 내 조언은, 밤에 정문이 아니라 정글을 통해 도시로 들어가라는 거다. 요즘 포르토벨로 경비병들은 몹시 의심이 많으니 말이지. 게다가 실반이 사라진 건 그가 무사하다는 징조도 아니고. 내가 여기서 빠져나가기 전, 스페인 순찰대가 우리를 찾기 전에, 네게는 이틀밖에 없어. 행운을 빌지, 나리!";
			link.l1 = "곧 다시 뵙겠소, Shoke 나리...";
			link.l1.go = "florian_deck_8";
		break;
		
		case "florian_deck_8":
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true; // доступно ожидание и sailto
			DialogExit();
			npchar.DeckDialogNode = "florian_deck_repeat";
			NextDiag.CurrentNode = "florian_deck_repeat";
			pchar.questTemp.Trial = "spy";
			AddQuestRecord("Trial", "12");
			// belamour legendary edition -->
			if(!bImCasual) 
			{
				pchar.quest.trial_spy_over.win_condition.l1 = "Timer";
				pchar.quest.trial_spy_over.win_condition.l1.date.hour  = sti(GetTime() + 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
				pchar.quest.trial_spy_over.function = "Trial_SpyTimeOver";
			}
			else NewGameTip("Exploration mode: timer is disabled.");
			// <-- legendary edition
			//Log_Info("You have received amulet 'Gypsy's fan'");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "obereg_4");
			pchar.quest.NewGameTip5.win_condition.l1 = "location";
			pchar.quest.NewGameTip5.win_condition.l1.location = "PortoBello_town";
			pchar.quest.NewGameTip5.function = "ShowNewGameTip";
			pchar.quest.NewGameTip5.text = "Guards are less suspicious when you walk at slow pace!";
			
			pchar.quest.Trial_CreatHabitue.win_condition.l1 = "location";
			pchar.quest.Trial_CreatHabitue.win_condition.l1.location = "PortoBello_tavern";
			pchar.quest.Trial_CreatHabitue.function = "Trial_CreatHabitue";
			
			pchar.quest.Tutorial_stealth.win_condition.l1 = "location";
			pchar.quest.Tutorial_stealth.win_condition.l1.location = "PortoBello_ExitTown";
			pchar.quest.Tutorial_stealth.function = "Tutorial_stealth";
			
			QuestPointerToLoc("shore47", "reload", "reload1_back");
			QuestPointerToLoc("PortoBello_Jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("PortoBello_Jungle_01", "reload", "reload3_back");
			QuestPointerToLoc("PortoBello_ExitTown", "reload", "reload4");
			QuestPointerToLoc("PortoBello_Town", "reload", "reload41_back");
			QuestPointerToLoc("PortoBello_Town", "reload", "reload4_back");
		break;
		
		case "florian_deck_repeat":
			dialog.text = "우린 모든 걸 다 얘기했지, 선장, 안 그런가?";
			link.l1 = "그래. 가는 중이야.";
			link.l1.go = "exit";
			NextDiag.TempNode = "florian_deck_repeat";
		break;
		
		case "florian_failspy":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "일이 어떻게 되어가고 있소, 선장? 뭘 알아냈소?";
			link.l1 = "상황이 좋지 않소, Shoke 나리. 나는 첩자 체질이 아니라서 금방 들통나고 말았소. 경비병들과 싸운 끝에 겨우 도시에서 도망쳤지. 내가 알아낸 유일한 소식은 당신 사람 Sylvan Laforet가 체포되어 감옥에 갇혀 있다는 것이오.";
			link.l1.go = "florian_failspy_1";
		break;
		
		case "florian_failspy_1":
			dialog.text = "제기랄! 이거 큰일이군... 갈레온에 대해 뭐 알아낸 거 있어?";
			link.l1 = "아니, 안 했어.";
			link.l1.go = "florian_failspy_2";
		break;
		
		case "florian_failspy_2":
			dialog.text = "젠장. 정말 그 일에 대한 정보가 필요하단 말이오. 하지만 이건 너무 큰 먹잇감이라 포기할 수 없지! 아무튼, 정찰병을 한 명 더 보내보겠소... 선장, 지금은 나를 떠나지 말아주시오. 자네 도움이 필요할 수도 있겠군. 내가 알라칸타라에 대한 정보를 캐내는 동안 하루만 더 기다려줄 수 있겠소?";
			link.l1 = "물론이지, 기다릴게! 그 실패를 반드시 만회하고 싶어.";
			link.l1.go = "florian_9";
			link.l2 = "그럴 생각 없어. 이런 게임엔 내가 영 소질이 없는 것 같군. 집에 갈 거야.";
			link.l2.go = "florian_failspy_3";
		break;
		
		case "florian_failspy_3":
			dialog.text = "글쎄, 그건 당신 선택이오. 행운을 빕니다, 선장.";
			link.l1 = "안녕히 가십시오, Shoke 나리.";
			link.l1.go = "florian_failspy_4";
		break;
		
		case "florian_failspy_4":
			DialogExit();
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "florian_failspy_5":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "일이 어떻게 되어가고 있소, 선장? 뭘 알아냈소?";
			link.l1 = "상황이 좋지 않소, Shoke 나리. 나는 첩자 노릇을 잘하지 못해서, 금방 들켜버렸소. 내가 알아낸 거라곤 당신 사람인 Sylvain Laforet가 체포되어 어딘가에 감금되어 있다는 것뿐이오.";
			link.l1.go = "florian_failspy_1";
		break;
		
		case "florian_9":
			dialog.text = "그럼 이제 배로 가시오, 선장. 내일 이맘때쯤이나 조금 늦게 나를 다시 찾아오시오. 그때쯤이면 뭔가 알아냈을지도 모르니. 육지에 내리지 말고, 배에서 나를 기다리시오!";
			link.l1 = "알겠소. 그렇게 하겠소.";
			link.l1.go = "florian_10";
		break;
		
		case "florian_10":
			dialog.text = "그리고 선장, 이 돈주머니를 받아두시오. 자네의 노력이 완전히 헛된 건 아니었으니. 적어도 불쌍한 실반 영감에게 무슨 일이 있었는지는 알게 되었잖소...";
			link.l1 = "...";
			link.l1.go = "florian_11";
		break;
		
		case "florian_11":
			DialogExit();
			Island_SetReloadEnableGlobal("Portobello", false);//закрыть остров	
			npchar.DeckDialogNode = "florian_deck_wait";
			NextDiag.CurrentNode = "florian_deck_wait";
			pchar.questTemp.Trial = "spy_wait";
			pchar.quest.Trial_spyfail_wait.win_condition.l1 = "Timer";
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.hour  = sti(GetTime()+rand(12));
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.function = "Trial_Spyfail_NextStage";
			TakeNItems(pchar, "purse2", 1);
			Log_Info("You've received a purse of doubloons");
		break;
		
		case "florian_deck_wait":
			dialog.text = "선장님, 지금은 아무 소식도 없습니다. 아직 기다리고 있습니다...";
			link.l1 = "좋아...";
			link.l1.go = "exit";
			NextDiag.TempNode = "florian_deck_wait";
		break;
		
		case "florian_12":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "일이 어떻게 되어가고 있소, 선장? 뭘 알아냈소?";
			link.l1 = "끝났소. 자네 부하 실뱅 라포레는 체포되어 감옥에 갇혀 있소. 이제 그 자는 끝장이오.";
			link.l1.go = "florian_13";
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("PortoBello_Town", "reload", "gate_back");
			QuestPointerDelLoc("PortoBello_ExitTown", "reload", "reload1_back");
			QuestPointerDelLoc("PortoBello_Jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("PortoBello_Jungle_02", "reload", "reload3_back");
			QuestPointerDelLoc("shore47", "reload", "boat");
		break;
		
		case "florian_13":
			dialog.text = "젠장! 끔찍하군... 갈레온에 대해 뭐 알아낸 거 있어?";
			link.l1 = "예. 그녀는 이미 한동안 출항 준비를 하고 있었지만, 포르토벨로의 총독이 그녀를 부두에 묶어두려 하고 있소. 지금 그는 카르타헤나에서 '푸에블라'라는 바르크엔틴이 '알칸타라'에 실을 화약을 싣고 오기를 기다리고 있소. 갤리온의 한 선원 말로는 화약이 충분하지 않아서 총독이 해적을 두려워한다고 하더군.";
			link.l1.go = "florian_14";
		break;
		
		case "florian_14":
			dialog.text = "정말 흥미롭군!";
			link.l1 = "하지만 푸에블라가 사흘 안에 도착하지 않으면, 알라칸타라는 더 이상 기다리지 않고 출항할 거요.";
			link.l1.go = "florian_15";
		break;
		
		case "florian_15":
			dialog.text = "훌륭한 일이오, 선장 "+GetFullName(pchar)+"! 아주 기쁘구나! 자, 보상이다. 정말로 받을 자격이 있네!";
			link.l1 = "감사합니다! 저에게 다른 임무가 있습니까?";
			link.l1.go = "florian_16";
		break;
		
		case "florian_16":
			TakeNItems(pchar, "gold_dublon", 75);
			dialog.text = "내 마음을 읽고 있군, "+GetFullName(pchar)+"! 그래, 젠장! 알라칸타라에 화약이 부족하니, 내가 그녀를 공해로 유인해서 해전으로 끌고 가면, 우리보다 먼저 화약이 떨어질 거야, 하하!\n보급 바크엔틴 푸에블라가 절대 포르토벨로에 도착하지 못하게 해야 해. 나는 해안 가까이 갈 수 없어; 순찰대가 내 프리깃을 금방 발견하고 알라칸타라를 가로채기도 전에 쫓아낼 테니까\n푸에블라는 네가 직접 처리해라. 찾아서 없애버려. 침몰시키든 노획하든 상관없다. 여기로 오지 못하게만 해!\n성공하면 과들루프로 가서 제라르 르크루아를 만나. 이미 알고 있겠지, 안 그런가? 그가 네가 받을 돈을 줄 거다.";
			link.l1 = "거래 성사! 이제 푸에블라를 가로막으러 출발하지!";
			link.l1.go = "florian_19";
			link.l2 = "잠시만요, 쇼케 나리. 사실 저는 아직... 뭐랄까, 해전에는 그다지 익숙하지가 않습니다. 그리고 나리께서는 프리깃함의 선장이시니, 분명 해전을 여러 번 치르셨겠지요. 폐가 되지 않는다면, 혹시... 뭐라고 말씀드려야 할지...\n";
			link.l2.go = "florian_guide_01";
		break;
		
		case "florian_17":
			dialog.text = "와 주셔서 반갑소, 선장. 방금 내 첩자로부터 정보를 받았는데, 당신에게 중요한 임무가 있소.";
			link.l1 = "잘 듣고 있네.";
			link.l1.go = "florian_18";
		break;
		
		case "florian_18":
			dialog.text = "알라칸타라는 출항할 준비가 되어 있지만, 갤리온의 선장은 카르타헤나에서 탄약을 가득 실은 바르크엔틴 '푸에블라'가 도착하기를 기다리고 있소. 알라칸타라에 화약이 충분하지 않은 모양이니, 스페인 놈들은 아직 출항할 준비가 안 된 거요. 하지만 선장의 인내심도 한계가 있으니, 푸에블라가 사흘 안에 오지 않으면 갤리온은 그녀 없이 포르토벨로를 떠날 것이오.\n알라칸타라는 화약이 부족하니, 그녀가 공해로 나가게 한 뒤 장기 해전으로 끌고 가면 저놈들 화약이 우리보다 먼저 떨어질 거요. 자네 임무는 푸에블라를 가로채서 파괴하는 거요. 침몰시키든 노획하든 상관없소. 그 보급 바르크엔틴이 여기 도착하지 못하게만 하시오!\n성공하면 과달루프로 가서 제라르 르크루아를 만나게. 자네도 이미 그를 알고 있지 않소? 그가 자네가 받을 만한 보수를 줄 것이오.";
			link.l1 = "거래 성사! 이제 푸에블라로 가서 길을 막겠소!";
			link.l1.go = "florian_19";
			link.l2 = "잠시만 기다리시오, Choquet 나리. 사실 저는 아직... 뭐랄까, 해전에는 별로 익숙하지 않소. 그리고 그대는 프리깃함의 선장이니, 분명 해전 경험이 한두 번이 아니겠지. 폐가 되지 않는다면, 혹시... 뭐라고 해야 할지...";
			link.l2.go = "florian_guide_01";
		break;
		
		case "florian_19":
			DialogExit();
			Island_SetReloadEnableGlobal("Portobello", true); // открыть остров
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			Trial_CreatePueblaBarqueInWorld();
			pchar.questTemp.Trial = "puebla";
			AddQuestRecord("Trial", "19");
		break;
		// belamour legendary edition дополнительное обучение -->
		case "florian_guide_01":
			dialog.text = "해전 전술에 대해 강의를 해달라고? 기꺼이 해드리지, 선장님! 특히 내게도 이득이니까. 당신이 '푸에블라'를 반드시 성공적으로 가로챌 수 있길 바라거든.";
			link.l1 = "아니, 그런 뜻이 아니었어. 좋아, 됐다. 바르크엔틴 한 척쯤 가로채는 건 아무 문제 없을 테니까.";
			link.l1.go = "florian_19";
			link.l2 = "그래, 바로 그 말이오. 새로운 지식이 내게 해가 될 일은 없을 것이오.";
			link.l2.go = "florian_guide_02";
		break;
		
		case "florian_guide_02":
			dialog.text = "그러니 가장 먼저 기억해야 할 것은, 전투의 절반은 시작도 하기 전에 이미 승패가 갈린다는 점이오. 당신과 배가 얼마나 준비되어 있느냐에 많은 것이 달려 있소.";
			link.l1 = "...";
			link.l1.go = "florian_guide_03";
		break;
		
		case "florian_guide_03":
			dialog.text = "우선, 네 배를 수리하는 것이 먼저다. 선체에 구멍이 나 있다면, 적이 널 바다 밑으로 보내는 건 그리 어렵지 않을 거다. 그리고 돛 대신 누더기가 달려 있다면, 움직임이 크게 제한될 테지. 전력 균형이 불리하면 적이 쉽게 도망칠 수도 있고, 더 나쁘게는 널 따라잡아 불리한 전투를 강요하거나, 심지어 바로 배에 올라탈 수도 있다. 게다가 돛이 찢어져 있으면, 바람을 잡아 적보다 유리한 위치에 오르기 힘들 거다 – 즉, 상대방의 바람 위쪽으로 올라가는 게 중요한데, 그걸 하기가 어렵다는 말이지.";
			link.l1 = "풍상권, 알겠어. 또 뭐 있어?";
			link.l1.go = "florian_guide_04";
		break;
		
		case "florian_guide_04":
			dialog.text = "사람이 충분한지 꼭 확인하게. 아무리 강력한 42파운드 대포를 가진 배라도, 포수 한 명이 대포 세 개를 번갈아 재장전하고 돛을 다룰 사람이 없다면 쓸모없어지지. 내 생각엔, 그런 배라면 그냥 바로 올라타서 접수해 버릴 거야.";
			link.l1 = "사람은 충분해, 알겠어.";
			link.l1.go = "florian_guide_05";
		break;
		
		case "florian_guide_05":
			dialog.text = "또한, 대포도 잘 살펴야 하오. 시간이 지나면 마모되어 폭발할 수 있소. 포신의 상태가 점점 나빠지는데, 전투 중에 대포가 터지기 시작하면 정말 끔찍한 결과를 맞이할 수 있소. 나는 정말 운이 없었지. 내가 타고 온 대포들 중 몇몇은 주조 결함이 있었소. 자네가 제때 예비품을 가져오지 않았다면, 나는 그냥 작전을 포기했을 것이오. 전투력에서 밀리턴트가 알칸타라보다 훨씬 뒤처질 테니까. 도구는 제때 교체해야 하오.";
			link.l1 = "이제야 왜 그게 그렇게 중요했는지 알겠어!";
			link.l1.go = "florian_guide_06";
		break;
		
		case "florian_guide_06":
			dialog.text = "대포뿐만 아니라 탄약의 양도 신경 써야 한다. 알칸타라는 이 점 때문에 내 손에 떨어질 거다. 만약 저쪽이 화약이 부족하다면, 오래 싸울 수 없으니 곧장 근접전을 벌여야 할 것이다. 나는 이걸 이용할 거다. 내 프리깃은 더 빠르니, 무거운 갤리언은 도망칠 수 없다. 하지만 나 역시 굳이 가까이 갈 필요는 없다. 멀리서 포격전을 강요하다가, 알칸타라의 화약이 다 떨어지면 접근해서 산탄으로 쓸어버리고, 바로 승선할 것이다.";
			link.l1 = "절박한 상황이군...";
			link.l1.go = "florian_guide_07";
		break;
		
		case "florian_guide_07":
			dialog.text = "정확하네. 화약과 탄약을 잘 챙기게. 철탄이 떨어지면 적선을 침몰시키기 어려울 것이고, 산탄이 없으면 수적으로 밀릴 때 백병전을 기대할 수 없지. 체인샷이나 니플탄이 없으면 적이 더 빠를 때 따라잡거나 도망칠 수도 없네. 모든 종류의 탄약이 다 중요하네.";
			link.l1 = "유익하군요, 감사합니다.";
			link.l1.go = "florian_guide_08";
		break;
		
		case "florian_guide_08":
			dialog.text = "그리고 마지막으로, 자신의 배와 적선의 종류와 크기에 따라 적절한 전술을 사용하시오. 바다에서는 화력과 속도 사이에 항상 균형이 필요하오. 크고 느린 배를 타고 있다면, 브리그나 코르벳을 추격해서 승선하려 해도 소용없소 – 우선 쇄탄으로 충분히 약화시키지 않으면 따라잡을 수 없으니 말이오. 이런 경우에는 멀리서 포격해 산산조각 내고, 난파선에서 전리품을 챙기는 것이 더 현명하오. 그래도 그런 배에 승선해야 한다면, 빠르고 기동성 좋은 배를 사용하는 것이 바람직하오.";
			link.l1 = "...";
			link.l1.go = "florian_guide_09";
		break;
		
		case "florian_guide_09":
			dialog.text = "동시에, 브리그로 전열함과 정면 승부를 벌이지는 마라. 그런 괴물의 일제 사격 한 번이면 작은 배들은 선체가 산산조각 나버린다. 네가 가진 속도와 기동성의 이점을 살려, 상대의 돛대와 장비를 무너뜨리고, 만약 승선을 해야 한다면 가까이 붙어서 산탄으로 갑판을 쓸어버려라. 만약 그 배를 침몰시켜야 한다면... 쉽지 않은 일이지만 불가능하지는 않다. 승선해서 화약고에 불을 지르는 방법도 있지만, 도망치는 것이 결코 부끄러운 일은 아니다. 훌륭한 선장은 과도한 영웅심에 빠지기보다 배와 선원들을 확실한 죽음에서 구하는 법이지. 명심해라, 신중함과 사려 깊음이 용기보다 더 나은 경우가 많다는 것을.";
			link.l1 = "정말 감사합니다, Choquet 나리!";
			link.l1.go = "florian_guide_10";
		break;
		
		case "florian_guide_10":
			AddCharacterSkillDontClearExp(pchar, SKILL_CANNONS, 1);
			AddCharacterSkillDontClearExp(pchar, SKILL_ACCURACY, 1);
			//Log_info(XI_ConvertString("Experience Bonus")+": +1 "+XI_ConvertString(SKILL_CANNONS));
			notification(XI_ConvertString("Experience Bonus")+": +1 ", SKILL_CANNONS);
			//Log_info(XI_ConvertString("Experience Bonus")+": +1 "+XI_ConvertString(SKILL_ACCURACY));
			notification(XI_ConvertString("Experience Bonus")+": +1 ",SKILL_ACCURACY);
			dialog.text = "도움이 되어 기쁩니다, 선장님. 이 지식이 앞으로 도움이 되길 바랍니다.";
			link.l1 = "도움이 될 거라 확신해. 우리는 이제 '푸에블라'를 가로막으러 간다!";
			link.l1.go = "florian_19";
		break;
		// <-- legendary edition дополнительное обучение

		// испанский офицер в таверне
		case "tavern_officer":
			dialog.text = "거 참 특이한 억양이군, 나리. 아니면 '나리'라고 불러야 하나? 하이메 실리시오를 만나고 싶나? 어쩌면 같은 감방을 쓰게 될지도 모르지. 데려가라, 얘들아!";
			link.l1 = "글쎄, 내 억양이 마음에 안 든다면 프랑스식 검술을 보여줄 수도 있겠군!";
			link.l1.go = "tavern_officer_1";
		break;
		
		case "tavern_officer_1":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "Trial_AfterTavernFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
