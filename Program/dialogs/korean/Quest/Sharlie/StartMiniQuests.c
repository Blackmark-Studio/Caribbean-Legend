void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "뭘 원하지?";
			link.l1 = "지금은 아무것도 없소.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//Найти помощника в магазин
		case "Storehelper":
			DelLandQuestMark(npchar);
			dialog.text = "필요한 것이라도 있으십니까, 나리?";
			link.l1 = "당신이 그랄람 라부아 맞습니까?";
			link.l1.go = "Storehelper_1";
		break;
		
		case "Storehelper_1":
			dialog.text = "누가 묻는 거지? 럼주 마시는 중이니 귀찮게 하지 마, 나리. 지금은 대화할 기분 아니야.";
			link.l1 = "많은 시간을 뺏지 않겠소. 나는 생피에르의 상인에게서 파견되어 왔소. 당신은 그의 예전 직원이었다 하더군. 그가 당신을 찾고 있고...";
			link.l1.go = "Storehelper_2";
		break;
		
		case "Storehelper_2":
			dialog.text = "하, 그 자가 나를 찾는다고!? 그 구두쇠 주제에 웃기는군! 내가 평생 그런 쥐꼬리만 한 월급 받고 일할 줄 알았나? 카리브에서 그만큼 욕심 많은 구두쇠도 없을걸! 내가 그놈 밑에서 5년이나 뼈 빠지게 일했지만, 한 푼도 더 주지 않더라고! 쳇, 술 한 잔 살 돈도 안 됐지!\n이제는 자기가 직접 물건 세어보라고 해, 난 그만뒀으니까. 생피에르에서 그 구두쇠 밑에서 일할 사람은 아무도 없어, 그건 확실해. 그 인간은 오직 자기 배 채우는 것밖에 관심 없어, 남들 월급은 줄이고 말이야.";
			link.l1 = "그 사람 밑에서 다시 일할 생각은 없는 거지?";
			link.l1.go = "Storehelper_3";
		break;
		
		case "Storehelper_3":
			dialog.text = "아니오, 맹세코 그런 일은 없었소! 나는 그냥 여기 르 프랑수아에서 어떤 배가 오기를 기다릴 거요. 받아만 준다면 사무장으로 일하겠소. 그것도 안 되면 그냥 평범한 선원으로라도 일할 거요. 그 돈만 밝히는 인간 꼴은 다시는 보고 싶지도 않소. 어차피 가난하게 살 거라면 차라리 자유로운 사람이 되겠소...";
			link.l1 = "알겠소, 그것만 알면 되었소. 행운을 빌겠소, 그랄람!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_4":
			DelLandQuestMark(npchar);
			dialog.text = "나리, 비켜 주십시오. 길을 막고 계십니다!";
			link.l1 = "질문 하나만 더 하겠습니다, 나리. 그람 라부아이이십니까?";
			link.l1.go = "Storehelper_5";
		break;
		
		case "Storehelper_5":
			dialog.text = "하! 그래, 나다. 뭐 원하는 거야?";
			link.l1 = "생피에르에서 온 상인이 널 찾고 있어. 예전에 그 밑에서 일했었지?";
			link.l1.go = "Storehelper_6";
		break;
		
		case "Storehelper_6":
			dialog.text = "하하! 정말 웃기는군! 그리고 폐하께서 나한테 뭘 원하신다는 거지? 지난 이 주 동안 밀린 임금을 주시기로 결심이라도 하신 건가? 아니면 술통 개수 세면서 손님들 속이느라 애라도 먹고 계신 건가, 응? 하하하!";
			link.l1 = "그가 나에게 당신을 찾아서 왜 더 이상 그의 가게에 일하러 오지 않는지 이유를 알아봐 달라고 했어요.";
			link.l1.go = "Storehelper_7";
		break;
		
		case "Storehelper_7":
			dialog.text = "왜냐고? 그 자식은 피도 눈물도 없는 구두쇠에다가 형편없는 고용주니까! 이제 나는 코스트의 형제단 소속이야, 더 이상 노예가 아닌 자유인이지! 주위를 봐, 진짜 즐기고 있다고!\n곧 나는 항해를 떠나 바나나 상자 대신 스페인 놈들에게서 빼앗은 페소와 두블론을 세게 될 거야! 그리고 그 구두쇠 자식은—나 대신 일할 사람을 못 구할 걸. 생피에르에는 그 자식 밑에서 일할 만큼 어리석은 녀석이 없어, 우리가 섬의 모든 견습생들에게 그 인간 평판을 다 퍼뜨렸거든, 하하!";
			link.l1 = "알겠소. 그거면 충분하오. 행운을 빌겠소, 그라람!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_8":
			DelLandQuestMark(npchar);
			dialog.text = "무엇을 도와드릴까요?";
			link.l1 = "안녕하십니까. 그랄람 라부아이, 맞으신가요?";
			link.l1.go = "Storehelper_9";
		break;
		
		case "Storehelper_9":
			dialog.text = "그래. 무엇을 원하시오, 나리?";
			link.l1 = "생피에르에서 온 상인이 너를 찾고 있어. 예전에 그 밑에서 일했었지?";
			link.l1.go = "Storehelper_10";
		break;
		
		case "Storehelper_10":
			dialog.text = "그래, 계속 찾아다니게 놔둬. 내가 그놈한테 빚진 건 없어. 오히려 그놈이 내 임금 이주일치나 떼먹었지. 하지만 그 돈 받으려고 애쓸 생각도 없어. 지 동전에 목이나 막혀 죽었으면 좋겠군.";
			link.l1 = "흠. 그러면 이제 그를 완전히 떠난 거로군?";
			link.l1.go = "Storehelper_11";
		break;
		
		case "Storehelper_11":
			dialog.text = "다 맞췄군, 이봐. 내 예전 고용주는 보기 드문 구두쇠야, 진짜 성경에 나올 만한 인물이거든. 이제 나는 카리브 해적단의 일원이 되었고, 내 재능은 새로운 동료들에게 높이 평가받고 있지. 지금은 두 배로 받고, 보너스도 따로 있어\n우리 친애하는 친구가 나를 대신할 사람을 찾을 수 있을지 의심스럽군. 그의 탐욕은 생피에르 사람들에게 이미 소문이 자자해서, 거기선 아무도 그 바보 같은 조건으로 일하려 들지 않을 거야.";
			link.l1 = "알겠소. 그게 내가 알아야 할 전부였소. 행운을 빌겠소, 그라람!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_12":
			DialogExit();
			npchar.lifeday = 0;
			AddQuestRecord("SharlieA", "2");
			pchar.questTemp.Sharlie.Storehelper = "return";
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.StorehelperOver.over = "yes"; //снять таймер
			
			pchar.quest.Sharlie_JungleBandos.win_condition.l1 = "location";
			pchar.quest.Sharlie_JungleBandos.win_condition.l1.location = "Martinique_Jungle_01";
			pchar.quest.Sharlie_JungleBandos.function = "SharlieJungleBandos";
			
			QuestPointerToLoc("lefransua_town", "reload", "gate_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload6_back");
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			QuestPointerDelLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload3_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload1_back");
		break;
		
		case "Newstorehelper_1":
			dialog.text = "안녕하십니까, 나리. 너무 앞서 나가는 것 같진 않길 바라지만, 제가 제안하신 그 자리에 꽤 잘 어울릴 후보라고 생각합니다.";
			link.l1 = "좋은 오후입니다. 그런데 왜 그렇게 생각하십니까?";
			link.l1.go = "Newstorehelper_1_1";
		break;
		
		case "Newstorehelper_2":
			dialog.text = "안녕하십니까, 나리! 제 소개를 잠시 드려도 되겠습니까?";
			link.l1 = "잘 듣고 있네.";
			link.l1.go = "Newstorehelper_2_1";
		break;
		
		case "Newstorehelper_3":
			dialog.text = "건강하시길 빕니다, 나리. 상인 자리를 제안하시는 겁니까?";
			link.l1 = "그래, 맞아. 자네에 대해 뭐 좀 말해줄 수 있나?";
			link.l1.go = "Newstorehelper_3_1";
		break;
		
		case "Newstorehelper_1_1":
			dialog.text = "나는 프랑시스 뒤부아 선장 직속으로 분대장 일을 했소. 선장께서 내 솜씨를 무척 마음에 들어 하셨지만, 전투 중에 부상을 입어 회복을 위해 휴가를 받아야 했지. 지금은 몸이 완전히 회복되어 아무 문제 없소. 하지만 이제는 출렁이는 파도만 생각해도 속이 뒤집혀. 아니, 이제 내 유일한 바람은 땅 위에 머무는 것뿐이오\n(속삭이며) 그리고 나를 선택해 주신다면, 오백 페소와 황금 두블룬 스물다섯 개를 추가로 드리겠소.";
			link.l1 = "알겠소. 생각해 보겠소.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_1_2";
		break;
		
		case "Newstorehelper_2_1":
			dialog.text = "나는 원래 행상이었지만, 빚쟁이들을 피해 도망치다가 상선의 경리로 바다에 나서게 되었소. 운명이 나를 이 마을로 이끌었지. 어차피 선원 생활은 별로 내키지 않았으니, 당신의 제안을 기꺼이 받아들이겠소\n(속삭이며) 그리고 나를 선택한다면, 오백 페소뿐만 아니라 이 무거운 호박 꾸러미도 드리겠소.";
			link.l1 = "알겠소. 생각해 보겠소.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_2_2";
		break;
		
		case "Newstorehelper_3_1":
			dialog.text = "나는 글래스고 항구 창고 중 한 곳에서 사무원이었소. 부를 찾아 카리브로 왔고, 노후를 품위 있게 보낼 만큼의 돈을 벌었지. 하지만 이제는 바다 생활에 지쳐서, 육지에서 조용히 살고 싶소\n(속삭이며) 그리고 나를 선택해 주신다면, 오백 페소에 추가로 이천오백 페소를 보너스로 드리겠소.";
			link.l1 = "알겠소. 생각해 보겠소.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_3_2";
		break;
		
		case "Newstorehelper_1_2":
			dialog.text = "나리, 올바른 선택을 하십시오. 그리고 두블룬도 잊지 마시고요...";
			link.l1 = "그대에게 유리하게 결정했소. 정신 차리시오. 우리 생피에르로 간다.";
			link.l1.go = "Newstorehelper_1_3";
			link.l2 = "아직 결정하지 못했어...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_1_2";
		break;
		
		case "Newstorehelper_2_2":
			dialog.text = "저를 선택해 주시길 바랍니다, 나리. 그리고 호박도 꽤 값지고 쓸모 있는 물건이지요...";
			link.l1 = "자네에게 유리하게 결정했네. 정신 차리게. 우리 생피에르로 간다.";
			link.l1.go = "Newstorehelper_2_3";
			link.l2 = "아직 결정을 못 했어...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_2_2";
		break;
		
		case "Newstorehelper_3_2":
			dialog.text = "상인은 내 일에 실망하지 않을 거요. 그리고 보너스도 잊지 마시오.";
			link.l1 = "자네에게 유리하게 결정했네. 정신 차리게. 우리 생피에르로 간다.";
			link.l1.go = "Newstorehelper_3_3";
			link.l2 = "아직 결정하지 못했어...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_3_2";
		break;
		
		case "Newstorehelper_1_3":
			dialog.text = "내 물건들만 챙기게! 선술집 입구에서 기다리고 있을게.";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 0;
		break;
		
		case "Newstorehelper_2_3":
			dialog.text = "금방 가겠소, 나리! 선술집 입구에서 기다리고 있겠소.";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 1;
		break;
		
		case "Newstorehelper_3_3":
			dialog.text = "내 오래된 여행가방을 챙겨서 선술집 입구에서 기다리겠소, 나리!";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 2;
		break;
		
		case "Newstorehelper_exit":
			DialogExit();
			pchar.questTemp.Sharlie.Storehelper.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay")
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("Newstorehelper_"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
			pchar.quest.storehelper4.win_condition.l1 = "location";
			pchar.quest.storehelper4.win_condition.l1.location = "FortFrance_store";
			pchar.quest.storehelper4.function = "NewstorehelperRegard";
			AddQuestRecord("SharlieA", "4");
			pchar.questTemp.Sharlie.Storehelper = "choise";
			pchar.quest.storehelper.over = "yes"; //снять прерывание
			
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			
			SetLaunchFrameFormParam("Back to Saint-Pierre...", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("FortFrance_store", "reload", "reload1", "");
			LaunchFrameForm();
		break;
		
		case "Newstorehelper_regard":
			dialog.text = "음, 이제부터 여기서 일하게 되는 건가요? 저를 선택해 주셔서 감사합니다, 나리. 약속하신 대로 오백 페소와 보너스까지 여기 있습니다.";
			link.l1 = "감사합니다... 당신의 고용주를 소개해 드리겠습니다.";
			link.l1.go = "Newstorehelper_regard_1";
		break;
		
		case "Newstorehelper_regard_1":
			DialogExit();
			npchar.lifeday = 0;
			switch (sti(pchar.questTemp.Sharlie.Storehelper.Quality))
			{
				case 0:
					AddMoneyToCharacter(pchar, 500);
					TakeNItems(pchar, "gold_dublon", 25);
				break;
				
				case 1:
					AddMoneyToCharacter(pchar, 500);
					TakeNItems(pchar, "jewelry8", 10);
					TakeNItems(pchar, "jewelry7", 1);
				break;
				
				case 2:
					AddMoneyToCharacter(pchar, 3000);
				break;
			}
		break;
		
		//контрабанда рома
		case "Rum_Cap_Over":
			dialog.text = "나리, 즉시 제 배에서 내려주셔야 하오. 우리는 닻을 올리고 출항할 것이오!";
			link.l1 = "좋아...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rum_Cap_Over";
			chrDisableReloadToLocation = false;
			npchar.DontDeskTalk = true;
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
		break;
		
		case "Rum_Cap":
			pchar.quest.Sharlie_rum2.over = "yes"; //снять таймер
			chrDisableReloadToLocation = false; // patch-4
			dialog.text = "그래서? 넌 누구냐?";
			//link.l1.edit = 1;			
			link.l1 = ""+pchar.questTemp.Sharlie.Rum.Pass+"!";
			link.l1.go = "Rum_Cap_1";
		break;
		
		case "Rum_Cap_1":
			dialog.text = "럼 한잔 해라, 선원! 하하! 내 러거에 탄 걸 환영한다. 물건 가지러 온 거냐?";
			link.l1 = "그래. 내가 여기 왜 있겠어?";
			link.l1.go = "Rum_Cap_2";
			/* if(GetStrSmallRegister(pchar.questTemp.Sharlie.Rum.Pass) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "럼 한잔 해라, 선원! 하하! 내 루거에 탄 걸 환영한다. 물건 가지러 온 거냐?";
				link.l1 = "그래. 내가 여기 왜 있겠어?";
				link.l1.go = "Rum_Cap_2";
			}
			else
			{
				dialog.text = "이런, 이런, 이거 완전 풋내기구나! 얘들아, 이 녀석 완전 신참처럼 보이지 않냐? 바다에 던져버리자!";
				link.l1 = "얍!";
				link.l1.go = "Rum_Cap_getout";
			} */
		break;
		
		case "Rum_Cap_getout":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			setCharacterShipLocation(pchar, "Shore38"));
			setWDMPointXZ("Shore38");
			DoQuestReloadToLocation("Shore38", "goto", "goto1", "Rum_RemoveBarkas");
		break;
		
		case "Rum_Cap_2":
			dialog.text = "이봐, 녀석들! 상자들을 보트에 실어라!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Rum_CarrierEnter");
		break;
		
		case "Rum_Cap_3":
			dialog.text = "럼 상자들은 전부 당신의 단정에 실려 있어. 포르 르 프랑수아는 여기서 바로 남쪽이야. 서둘러, 나도 이제 닻을 올릴 시간이거든!";
			link.l1 = "시간 낭비하지 맙시다, 여러분! 행운을 빕니다!";
			link.l1.go = "Rum_Cap_4";
		break;
		
		case "Rum_Cap_4":
			dialog.text = "너도 마찬가지야, 친구...";
			link.l1 = "...";
			link.l1.go = "Rum_Cap_5";
		break;
		
		case "Rum_Cap_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			npchar.DontDeskTalk = true;
			NextDiag.CurrentNode = "Rum_Cap_Over";
			pchar.quest.Sharlie_rum4.win_condition.l1 = "Ship_location";
			pchar.quest.Sharlie_rum4.win_condition.l1.location = "LeFransua_town";
			pchar.quest.Sharlie_rum4.function = "Rum_RemoveRum";
			AddQuestRecord("SharlieB", "4");
			i = FindIsland("Martinique");
			Islands[i].EffectRadius = 3000;
			
			DoQuestFunctionDelay("MessageRum1", 1.0);
			//NewGameTip("Transport the rum to Le Francois. Keep sailing around the island.");
			pchar.questTemp.Rum.Tip2.Reload = "l4";
			
			Weather.Wind.Speed = 16.0;
			pchar.wind.speed = Weather.Wind.Speed;
			fWeatherSpeed = stf(Weather.Wind.Speed);//халява первого выхода
			
			Weather.Wind.Angle = PId2;
			pchar.wind.angle = Weather.Wind.Angle;
			fWeatherAngle = stf(Weather.Wind.Angle);//халява первого выхода
			
			pchar.quest.MessageRum2.win_condition.l1 = "ExitFromLocation";
			pchar.quest.MessageRum2.win_condition.l1.location = pchar.location;
			pchar.quest.MessageRum2.function = "MessageRum2";
		break;
		
		case "Rum_Carrier":
			dialog.text = "기다리고 있었습니다, 나리. 모든 일은 잘 처리하셨습니까? 상자들은 가지고 오셨나요?";
			link.l1 = "모든 게 훌륭하게 끝났어. 럼 상자들은 보트에 실려 있어.";
			link.l1.go = "Rum_Carrier_1";
		break;
		
		case "Rum_Carrier_1":
			dialog.text = "좋아. 이제부터는 우리가 맡을 테니. 너는 생피에르로 가서, 선술집에서 보수를 받아라. 밤에 정글에서는 항상 경계하고 조심해라.";
			link.l1 = "행운을 빕니다, 신사 여러분.";
			link.l1.go = "Rum_Carrier_2";
		break;
		
		case "Rum_Carrier_2":
			DialogExit();
			for (i=1; i<=3; i++)
			{
				
				sld = characterFromId("Rum_Carrier2_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			}
			pchar.questTemp.Sharlie.Rum = "regard";
			i = FindLocation("Fortfrance_town");
			setCharacterShipLocation(pchar, GetCityFrom_Sea(locations[i].fastreload));
		    setWDMPointXZ(GetCityFrom_Sea(locations[i].fastreload));
			SetCurrentTime(23, 0);
			Sharlie_removeLocks("");
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("lefransua_town", "reload", "gate_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			if(CheckAttribute(pchar, "questTemp.Sharlie.Gigolo")) QuestPointerToLocTime("fortfrance_town", "reload", "reload9_back", 23.0, 24.0);
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
		break;
		
		//доставить девочку из борделя
		case "GigoloMan":
			DelLandQuestMark(npchar);
			dialog.text = "안녕하십니까, 나리! 말씀드리자면, 보통 우리 식민지에 어슬렁거리는 그 누더기 악당들과는 전혀 다르게 보이시는군요. 옷차림을 보아하니 먼 길을 오신 듯합니다... 유럽에서 오셨습니까?";
			link.l1 = "정확합니다, 나리. "+GetFullName(pchar)+", 당신을 위해 대기 중이오. 무엇이 필요하시오?";
			link.l1.go = "GigoloMan_1";
		break;
		
		case "GigoloMan_1":
			dialog.text = "자기소개를 하겠습니다 - "+GetFullName(npchar)+". 나는 몇 해 전 프랑스에서 이 끔찍한 곳에 도착했소. 하지만 그건 지금 중요한 게 아니오. 그대에게 아주 민감한 부탁이 있소\n부디 이해해 주시오. 내가 그대가 신사임을 확신하지 않았다면, 이런 부탁을 절대 하지 않았을 것이오.";
			link.l1 = "부디, 원하시는 바를 말씀해 주십시오, 나리. 제 능력 안에 있다면, 물론 도와드리겠습니다.";
			link.l1.go = "GigoloMan_2";
		break;
		
		case "GigoloMan_2":
			dialog.text = "그 말을 들으니 기쁘군요, 드 모르 나리. 자, 이걸 어떻게 조심스럽게 말해야 할지... 이 마을에 사창가가 하나 있소. 최근에 거기에 새로운 아가씨가 들어왔는데, 젊고, 창백하며, 금발에, 정말 눈부시게 아름답소! 내가 몇 주째 그녀를 지켜봤는데... 사적으로 그녀와 시간을 보내고 싶은 욕망이 아주 강하게 들더군요\n하지만 내 신분과 지위 때문에 그런 곳을 방문하는 건... 곤란하오. 소문이 퍼진다고 생각해 보시오!\n그래서 당신에게 부탁하는 것이오. 솔직히 말해, 당신은 우리 섬에 막 온 신참이고, 사람들은 당신을 잘 모르니 뭘 해도 신경 쓰지 않을 거요... 아직은 말이오. 그러니 큰 은혜를 베풀 수 있지 않겠소, 드 모르 나리.";
			link.l1 = "무슨 말을 하려는지 알 것 같군.";
			link.l1.go = "GigoloMan_3";
		break;
		
		case "GigoloMan_3":
			dialog.text = "신중함에 감사하오, 나리. 내가 그 아가씨에게 갈 수 없으니, 아가씨가 내게 와야 하오. 내 집으로 말이오. 그러니 당신이 사창가에 가서 마담과 협의하여, 금발 아가씨가 하룻밤 내 집에 '출장'을 오도록 허락받아 주시오.\n오로라는 거절하지 않을 것이오. 그녀는 이런 서비스를 자주 제공하는 것으로 유명하니, 다만 비용이 조금 더 들 뿐이오. 그 다음엔 아가씨를 내 집으로 데려오시오. 보수로 당신에게 육천 페소를 주겠소. 오로라는 보통 집에서 하룻밤을 보내면 삼천에서 삼천오백 페소를 받지. 남는 돈은 수고비로 가져도 되오.";
			link.l1 = "별로 복잡해 보이지 않네. 내가 할 수 있겠어.";
			link.l1.go = "GigoloMan_4";
			link.l2 = "나리, 저 역시 신사로서의 명예를 당신만큼이나 소중히 여깁니다. 부디 용서해 주시길, 하지만 당신의 부탁을 들어드릴 수 없습니다. 거절해야겠군요. 아마도 선술집에 가서 주점 주인이 일거리가 있는지 확인해 봐야 할 것 같습니다.";
			link.l2.go = "GigoloMan_exit";
		break;
		
		case "GigoloMan_exit":
			DialogExit();
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", false);// бордель open
			LocatorReloadEnterDisable("Fortfrance_town", "reload9", false);// бордель
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", false);// таверна
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			chrDisableReloadToLocation = false;
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			SetCurrentTime(17, 30);
		break;
		
		case "GigoloMan_4":
			dialog.text = "정말 듣기 좋군. 이제 잘 들어, 그 아가씨 이름은 루실이야. 아무도 눈치채지 않게 밤 열한 시 이후에 내 집으로 그녀를 데려다 주길 바라네. 문을 두드리면 내가 열어주지.\n내 집은 총독 관저에서 왼쪽, 관저를 등지고 있는 붉은 지붕의 2층 저택이야. 쉽게 찾을 수 있을 거고, 근처에 상점도 있네. 사실 지금 바로 집으로 가는 길이니, 따라와서 집이 어떻게 생겼고 어디 있는지 직접 보고 가도 좋네. 그래야 밤에 길을 잃지 않을 테니.\n그리고 본론으로 들어가서, 여기 6,000페소를 가져가게. 약속한 시간에 꼭 오게!";
			link.l1 = "거래 성사됐어. 네 금발 루실이 오늘 밤 네 집 문 앞에 있을 거야.";
			link.l1.go = "GigoloMan_5";
		break;
		
		case "GigoloMan_5":
			DialogExit();
			AddMoneyToCharacter(pchar, 6000);
			AddQuestRecord("SharlieC", "1");
			AddQuestUserData("SharlieC", "sName", GetFullName(npchar));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "", -1);
			LocatorReloadEnterDisable("Fortfrance_town", "houseSp1", true);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie.Gigolo = "start";
			pchar.questTemp.Sharlie.Gigolo.Rand1 = rand(1);
			pchar.questTemp.Sharlie.Gigolo.Rand2 = rand(1);
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", false);// бордель open
			LocatorReloadEnterDisable("Fortfrance_town", "reload91", false);// бордель
			AddLandQuestMark(characterFromId("Fortfrance_hostess"), "questmarkmain");
			QuestPointerToLoc("fortfrance_town", "reload", "reload9_back");
			QuestPointerToLoc("fortfrance_brothel", "reload", "reload3");
			chrDisableReloadToLocation = false;
		break;
		
		case "GigoloGirl":
			if (npchar.quest.meeting == "0")
			{
				DelLandQuestMark(npchar);
				QuestPointerDelLoc("fortfrance_town", "reload", "reload9_back");
				dialog.text = "안녕하세요, 나리. 어머, 오늘 밤 저를 고용하신 분이 바로 당신인가요? 세상에, 이렇게 잘생기고 깔끔한 신사라니, 저는 정말 운이 좋은 여자네요. 부두에서 타르와 땀 냄새를 풍기며 올라오는 난폭한 놈들과는 전혀 다르시군요...";
				link.l1 = "미안하지만, 오늘 밤은 안 되겠소, 루실. 나는 내 좋은 친구를 대신해 여기 왔소. 그 친구는 여러 가지 아주 복잡한 이유로 집을 떠날 수 없으니, 내가 당신을 그에게 데려갈 것이오. 자, 너무 속상해하지 마시오. 그는 온화한 사람이고 당신을 무척 좋아하오. 결국엔 당신도 만족할 거라 생각하오.";
				link.l1.go = "GigoloGirl_1";
				// belamour legendary edition -->
				link.l2 = "음... 네 말이 맞아, 자기야. 갈까?";
				link.l2.go = "GigoloGirl_1a";
				// <-- legendary edition
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "나리, 제가 밤에 그냥 당신과 거닐 수 없다는 걸 이해하시길 바랍니다. 빨리 당신 친구의 집으로 데려가 주지 않으면 저는 곧장 마담에게 돌아갈 것이고, 당신 돈만 허비하게 될 거예요.";
				link.l1 = "알겠소. 나를 따라오시오!";
				link.l1.go = "GigoloGirl_2";
			}
		break;
		// belamour legendary edition -->
		case "GigoloGirl_1a":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			chrDisableReloadToLocation = true; //закрыть локацию
			DoQuestReloadToLocation(pchar.location+"_room", "goto", "goto2", "GigoloGirl_Sex");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_room", "goto", "goto1");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Rum"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		
		case "GigoloGirl_1":
			AddCharacterExpToSkill(pchar, "Fortune", 40);
		// <-- legendary edition
			dialog.text = "안타깝군요... 나는 처음부터 당신이 마음에 들었어요, 나리. 당신과 하룻밤을 보내고 싶었는데... 아마 다음 기회에. 갈까요?";
			link.l1 = "그래. 따라와!";
			link.l1.go = "GigoloGirl_2";
		break;
		
		case "GigoloGirl_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_Gigolo.win_condition.l1 = "locator";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.locator_group = "reload";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.locator = "houseSp1";
			pchar.quest.Sharlie_Gigolo.function = "Sharlie_GiveGigoloGirl";
			pchar.quest.Sharlie_Gigolo1.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.hour  = sti(GetTime() + 2);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.function = "Sharlie_GigoloGirlOver";
			QuestPointerToLoc("fortfrance_town", "reload", "houseSp1");
		break;
		
		case "GigoloGirl_3":
			dialog.text = "정말 웅장한 저택이군. 여기가 그곳인가?";
			link.l1 = "그래. 들어오게. 두려워 말게, 내 친구는 좋은 사람이네.";
			link.l1.go = "GigoloGirl_4";
		break;
		
		case "GigoloGirl_4":
			dialog.text = "나를 얕보는군, 나는 두렵지 않소, 나리. 나는 내 몸 하나쯤은 알아서 챙길 줄 알지. 그런데, 혹시 나중에 마담에게 내 하룻밤 값을 지불해 줄 수 있겠소? 분명 당신 인생 최고의 밤이 될 거라고 약속하오!";
			link.l1 = "뭐든 가능하지, 루실. 어쩌면 또 만날지도 모르지. 잘 있어!";
			link.l1.go = "GigoloGirl_5";
		break;
		
		case "GigoloGirl_5":
			pchar.quest.Sharlie_Gigolo1.over = "yes";
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "GigoloGirl_Remove", 5.0);
			QuestPointerDelLoc("fortfrance_town", "reload", "houseSp1");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Rum"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		
		//пираты с пленным испанцем
		case "CaptivePirate":
			pchar.quest.Captive_CreatePiratesOver.over = "yes";//снять таймер
			pchar.quest.Captive_CreatePiratesOver2.over = "yes";//снять таймер
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_03", "reload", "reload2_back");
			dialog.text = "이게 뭐야!? 너 누구야? 여기서 뭐 하려는 거지? 어서, 당장 꺼져라!";
			link.l1 = "예의가 별로 없구나, 이놈.";
			link.l1.go = "CaptivePirate_1";
		break;
		
		case "CaptivePirate_1":
			dialog.text = "잘 들어, 꼬마야. 난 예의 차리라고 키워진 적도 없고, 글 읽고 쓰는 법도 배운 적 없어. 하지만 네 머리통을 커틀라스로 쪼개는 건 창녀가 뒤로 자빠지는 것만큼이나 쉬운 일이야. 그리고 내 눈알을 걸고 맹세하는데, 당장 여기서 나가지 않으면 넌 들려서 나가게 될 거다. 알겠어?";
			link.l1 = "아니, 이봐 이 자식아, 내 말 좀 들어. 네 수작은 이미 다 들통났어. 나는 저 자식이 살아 있어야 해. 그러니까 무기를 버리고 도망쳐. 내 바로 뒤 정글에 프랑스 군인들이 대기 중이야. 빨리 도망치면 네 보잘것없는 목숨이라도 건질 수 있을지 모르지.";
			link.l1.go = "CaptivePirate_3";
			link.l2 = "알았어, 알았어, 진정해. 나 간다.";
			link.l2.go = "CaptivePirate_2";
		break;
		
		case "CaptivePirate_2":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			n = makeint(MOD_SKILL_ENEMY_RATE/2);
			if (n <= 1) n = 2;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("CaptivePirate_"+i);
				LAi_CharacterDisableDialog(sld);
				LAi_SetImmortal(sld, true);
				sld.lifeday = 0;
			}
			sld = characterFromId("CaptiveSpain");
			LAi_SetImmortal(sld, true);
			sld.lifeday = 0;
			pchar.quest.Sharlie_captive1.over = "yes";
			pchar.quest.Sharlie_captive2.over = "yes";//снять прерывание
			AddQuestRecord("SharlieD", "5");
			CloseQuestHeader("SharlieD");
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "CaptivePirate_3":
			dialog.text = "뭐, 뭐라고? 허풍 치는 거잖아, 이 친구야! 얘들아, 저놈을 쓰러뜨려! 무기 들어!\n";
			link.l1 = "그럼 네가 책임져야지, 각오해라!";
			link.l1.go = "CaptivePirate_4";
		break;
		
		case "CaptivePirate_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			int n = makeint(MOD_SKILL_ENEMY_RATE/2);
			if (n <= 1) n = 2;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("CaptivePirate_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Captive_PiratesDead");
			AddDialogExitQuest("MainHeroFightModeOn");	
			sld = characterFromId("CaptiveSpain");
			LAi_SetCitizenType(sld);
			DoQuestFunctionDelay("Ngt_CaptiveEng", 0.5);
		break;
		
		//пленный испанец
		case "CaptiveSpain":
			dialog.text = "신께 감사하네! 아, 자네 프랑스인인가? 젠장, 그 악당들을 멋지게 물리쳤군. 하지만 내가 순순히 항복할 거라 생각하지 마라, 진짜 스페인 놈이 어떻게 싸우는지 보여주지! 산티아고!";
			link.l1 = "안 돼, 잠깐만, 제발!";
			link.l1.go = "CaptiveSpain_1";
		break;
		
		case "CaptiveSpain_1":
			dialog.text = "나는 프랑스 놈들에게 잡히느니 차라리 죽겠다. 네가 싸우는 동안 죽은 자들 중 하나에게서 커틀러스를 챙겼지... 이제 네놈을 스페인식 콰드릴 춤추게 해주마!";
			link.l1 = "너희 스페인 놈들은 노새처럼 고집이 세구나!";
			link.l1.go = "CaptiveSpain_2";
		break;
		
		case "CaptiveSpain_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			NextDiag.currentnode = "CaptiveSpain_3";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "CaptiveSpain_capture");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "CaptiveSpain_3":
			dialog.text = "젠장... 네가 이겼다. 항복한다, 젠장할 프랑스 놈. 이제 네 손에 달렸다.";
			link.l1 = "칼을 집어넣고 내 말 좀 들어, 고집 센 카스티야 놈아! 나는 네가 죽는 것도 원치 않고, 감옥에 보내려는 것도 아니야!";
			link.l1.go = "CaptiveSpain_4";
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
		break;
		
		case "CaptiveSpain_4":
			dialog.text = "그럼 지금 뭐 하고 있는 거요? 왜 해적들을 죽였소? 그리고 당신 병사들은 어디 있소?";
			link.l1 = "병사들은 없어. 그 악당들을 속이려고 했지만, 우리 주변을 보면 알겠지만 실패했지. 나는 네 옛 친구의 부탁으로 여기 혼자 왔다네. 그의 이름은\n "+pchar.questTemp.Sharlie.Captive.Name+", 그는 생피에르의 은행가야.";
			link.l1.go = "CaptiveSpain_5";
		break;
		
		case "CaptiveSpain_5":
			dialog.text = ""+pchar.questTemp.Sharlie.Captive.Name+"? 그 이름은 처음 듣는데...";
			link.l1 = "나는 그대나 그대가 포로로 잡혀 있었다는 사실에 대해서도 전혀 알지 못했소. 그대가 영국 배로 옮겨졌다는 것도 그에게서 들었소. 내 임무는 그대에게 그를 만나게 해주는 것이며, 반드시 그 약속을 지키겠다고 맹세했소! 자, 살고 싶다면 나를 따라오시오.";
			link.l1.go = "CaptiveSpain_6";
		break;
		
		case "CaptiveSpain_6":
			dialog.text = "어차피 선택권도 없으니... 네가 말한 그 은행원도 영국놈들이랑 그 끔찍한 요리보단 나을 거야...";
			link.l1 = "드디어 현명한 결정을 내리는군. 이제 말은 그만하고, 생피에르로 간다. 내 곁에서 떨어지지 말고 따라와. 도망치면 또 잡아서 혼쭐을 내줄 테니 각오해라.";
			link.l1.go = "CaptiveSpain_7";
		break;
		
		case "CaptiveSpain_7":
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.Notsearchbody"); // 170712
			DialogExit();
			AddQuestRecord("SharlieD", "6");
			LAi_group_Register("TempFriends");
			LAi_group_SetRelation("TempFriends", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "TempFriends");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
			pchar.quest.Sharlie_captive3.win_condition.l1 = "locator";
			pchar.quest.Sharlie_captive3.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_captive3.win_condition.l1.locator_group = "reload";
			pchar.quest.Sharlie_captive3.win_condition.l1.locator = "reload8_back";
			pchar.quest.Sharlie_captive3.win_condition.l2 = "Night";
			pchar.quest.Sharlie_captive3.win_condition.l3 = "Alarm";
			pchar.quest.Sharlie_captive3.win_condition.l3.value = 0;
			pchar.quest.Sharlie_captive3.win_condition.l3.operation = "=";
			pchar.quest.Sharlie_captive3.function = "CaptiveSpain_reload";//вход ночью
			pchar.questTemp.Sharlie = "bankskipercaptive";
			SetFunctionLocationCondition("CaptiveSpain_removeGuard", "fortfrance_town", 0);
			SetFunctionLocationCondition("CaptiveSpain_saveTip", "fortfrance_exittown", 0);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_town")], false);
			// Rebbebion, новые марки до места назначения. belamour поправил - были не в ту сторону
			QuestPointerToLoc("shore39", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_03", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload8_back");
			AddLandQuestMark(characterFromId("FortFrance_Usurer"), "questmarkmain");
		break;
		
		//горожанин с пропавшей дочерью
		case "Prosper":
			DelLandQuestMark(npchar);
			pchar.quest.Sharlie_RescueDaughter.over = "yes"; //снять прерывание
			dialog.text = "무슨 일이십니까, 나리? 나는 대화할 시간이 없으니, 간단히 말씀하시지요.";
			link.l1 = "당신이 프로스페르 트루발 맞지?";
			link.l1.go = "Prosper_1";
		break;
		
		case "Prosper_1":
			dialog.text = "그래, 그게 나요. 하지만 당신이 나보다 유리한 입장이군. 누구신지, 그리고 도대체 무슨 용건인지 알려주시오.";
			link.l1 = "내 이름은 "+GetFullName(pchar)+". 나는 당신에게 보내졌소 "+GetFullName(characterFromId("Fortfrance_portman"))+", 항만 관리자요. 당신이 긴급한 도움이 필요하다고 말했소...";
			link.l1.go = "Prosper_2";
		break;
		
		case "Prosper_2":
			dialog.text = "맙소사, 맞아! 그 사악한 사령관 놈은 내 불평을 들으려 하지도 않았어! 너무 게으르거나 겁이 많아서 도와줄 생각이 없는 거지. 정말로 날 도우러 온 거야? 그렇다면, 널 그냥 보내진 않을 거야!";
			link.l1 = "그래, 프로스페르. 무슨 일이 있었는지, 내가 도울 수 있는 일이 무엇인지 말해보게. 따님이 사라졌다는 소문을 들었네...";
			link.l1.go = "Prosper_3";
		break;
		
		case "Prosper_3":
			dialog.text = "그래, 내 사랑하는 딸 셀린이 이틀째 실종됐네. 여기서 멀지 않은 요새로 산책을 나갔지. 그런데 돌아오지 않아서 내가 직접 요새에 가보았더니, 병사들은 그녀가 거기에 온 적이 없다고 하더군!\n그런데 돌아오는 길에 야만적인 인디언 두 명에게 습격을 당했네! 그놈들이 곤봉을 들고 달려들어 나를 때리려 했지.\n하지만 내가 만만한 고양이가 아니지, 놈들 중 하나의 얼굴을 주먹으로 갈겨 시간을 벌고, 그 사이 권총을 뽑아 쐈네. 빗나갔지만 놈들은 겁을 먹고 달아났지. 나는 겨우 시 성문까지 도착해서 경비병들에게 습격당한 일을 알렸네. 그들이 정글로 달려갔지만, 야만인들은 이미 오래 전에 사라진 뒤였어.\n나는 그놈들이 셀린의 실종과 관련 있다고 확신하네. 게다가 지난주에도 두 사람이 더 사라졌어 - 세자르 블랑셰와 질베르 쿠르시! 한 명은 만으로, 다른 한 명은 르 프랑수아로 향했지. 둘 다 돌아오지 않았네.";
			link.l1 = "인디언들이 도시 문 바로 앞에서 시민들을 공격했다고? 그거 정말 대담하군...";
			link.l1.go = "Prosper_4";
		break;
		
		case "Prosper_4":
			dialog.text = "그동안 나는 직접 정글로 나가 그녀를 찾아봤고, 도시 북쪽에서 동굴을 발견했네. 그 안에 그 자식들이 쭈그리고 앉아 있더군. 입구에서 인디언 몇 명을 봤지만, 일부는 분명 안에도 있을 거야\n여자애가 비명을 지르는 소리를 들었어... 내 셀렌이었네, 틀림없어, 그녀 목소리였어! 그 자리에서 바로 뛰어들고 싶은 걸 간신히 참았지 - 상황이 불리해서 들어갔다간 난 도륙당했을 거야. 내가 죽으면 그녀에게 아무런 도움이 안 되지.";
			link.l1 = "도대체 왜 저들이 공격하고 마을 사람들을 포로로 잡아가는 거지?";
			link.l1.go = "Prosper_5";
		break;
		
		case "Prosper_5":
			dialog.text = "모르겠어... 해적이나 노예상인한테 팔려고 그러는 걸지도? 아니면 그냥 산 채로 잡아먹을지도 몰라, 어차피 그놈들은 야만인들이니까.";
			link.l1 = "하늘에 계신 하느님, 저들이 식인종이란 말인가? 난 그런 건 유럽에서 아이들 겁주려고 하는 이야기인 줄 알았는데...";
			link.l1.go = "Prosper_6";
		break;
		
		case "Prosper_6":
			dialog.text = "이야기냐고? 너처럼 생각한 남자들이 있었지. 그러다 카리브족에게 불에 구워져 먹혀버렸어... 그래서 나는 곧장 사령관에게 달려가 내 셀렌을 구하기 위해 징벌대를 요청했지. 그런데 거절당했어! 여자애들이 사라지면 인디언이 아니라 남자랑 눈 맞아 도망간 거라고 하더군. 마을 헛간이나 뒤져보라고 했지\n그리고 나머지 두 명 실종에 대해서는... 한 명은 밀수 혐의가 있었고, 다른 한 명은 르 프랑수아 술집에서 술에 절어 죽어가고 있을 거라고 하더군. 결국 나는 아무것도 얻지 못했고, 직접 나서기로 결심했지.";
			link.l1 = "무엇을 할 생각이오?";
			link.l1.go = "Prosper_7";
		break;
		
		case "Prosper_7":
			dialog.text = "내가 거기로 가서 그 붉은 놈들 전부 죽여버릴 거야. 셀렌이 아직 살아 있길 바랄 뿐이지. 보다시피, 나는 머스킷을 샀어 - 그리고 쏘는 법도 알아. 돈은 많이 들었지만 신경 안 써\n네가 같이 가주면 내 임무가 훨씬 쉬워질 거야. 내가 재장전할 때 네가 뒤를 봐준다면, 함께라면 저 야만인들을 손쉽게 끝장낼 수 있어. 내 딸을 구하러 같이 가줄 수 있겠나?";
			link.l1 = "물론이지! 이건 명예의 문제야! 내가 어찌 야만인의 칼에 처녀가 죽게 내버려둘 수 있겠어.";
			link.l1.go = "Prosper_8";
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") {
				link.l1.go = "Prosper_noweapon";
			}
			link.l2 = "흠. 있잖아, 나는 사령관의 말이 일리가 있다고 생각해. 우리 먼저 그의 조언을 따르는 게 좋지 않을까?";
			link.l2.go = "Prosper_exit";
		break;
		
		case "Prosper_noweapon":
			dialog.text = "나리, 검은 어디 있소?";
			link.l1 = "내가 그것을 어디에 뒀는지 잊어버린 것 같군.";
			link.l1.go = "Prosper_noweapon_1";
		break;
		
		case "Prosper_noweapon_1":
			dialog.text = "그렇게는 안 되오. 나는 저녁까지 기다리겠소; 우리 총독 나리의 발밑에 엎드려 도움을 간청하는 것이 좋을 것이오.";
			link.l1 = "그의 발밑에 엎드리라고? 뭐, 네가 원한다면...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prosper_getweapon";
			SetFunctionTimerConditionParam("RescueDaughter_Over", 0, 0, 0, 22, false);
		break;
		
		case "Prosper_getweapon":
			dialog.text = "그래, 나리? 무기는 챙겼소?";
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") {
				link.l1 = "아직 아니오, 조금만 더 기다려 주십시오...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Prosper_getweapon";
			} else {
				link.l1 = "알겠소. 도와드릴 준비가 되었소!";
				link.l1.go = "Prosper_8";
				DeleteQuestCondition("RescueDaughter_Over");
			}
		break;

		case "Prosper_exit":
			dialog.text = "세상에, 도망치는 거냐? 아니! 당장 꺼져라! 겁쟁이!";
			link.l1 = "이봐-이봐, 진정해라, 이 멍청아! 내가 나가서 생피에르 거리에 귀족들이 도움이 필요한지 봐야겠군.";
			link.l1.go = "Prosper_exit_1";
			pchar.questTemp.Sharlie.GigoloMan.SamPodbezhit = true;
		break;
		
		case "Prosper_exit_1":
			DialogExit();
			npchar.lifeday = 0;
			//AddTimeToCurrent(2,0);
			SetCurrentTime(17,30);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "gate_back", "none", "", "", "", 10.0);
			CloseQuestHeader("SharlieF");
			chrDisableReloadToLocation = true;
			
			//Подбегает дворянин с квестом "девочка по вызову"
			sld = GetCharacter(NPC_GenerateCharacter("GigoloMan", "Guide_2", "man", "man", 25, FRANCE, 5, true, "soldier"));
			SetFantomParamFromRank(sld, 25, true);
			sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
			sld.dialog.currentnode = "GigoloMan";
			sld.greeting = "noble_male";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetLoginTime(sld, 6.0, 21.0);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Prosper_8":
			dialog.text = "이 마을에 적어도 한 명은 용감한 사내가 있어서 다행이오. 자, 이 세 개의 약병을 가져가시오.\n이건 몸에 좋은 약초들이오. 우리 약초상에게서 샀소. 전투에서 큰 도움이 될 것이오.";
			link.l1 = "너는 어때?";
			link.l1.go = "Prosper_9";
		break;
		
		case "Prosper_9":
			TakeNItems(pchar, "potion1", 3);
			PlaySound("interface\important_item.wav");
			dialog.text = "걱정 마, 아직 더 있어. 준비됐어?";
			link.l1 = "그래, 시간 낭비하지 말자. 앞으로!";
			link.l1.go = "Prosper_10";
		break;
		
		case "Prosper_10":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "fortfrance_exittown", "reload", "reload3", "OpenTheDoors", 10.0);
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition.l1 = "location";
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition.l1.location = "FortFrance_ExitTown";
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition = "RescueDaughter_ProsperGateOutReload";
			AddQuestRecord("SharlieF", "3");
			pchar.quest.Sharlie_RescueDaughter1.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter1.win_condition.l1.location = "Martinique_jungle_04";
			pchar.quest.Sharlie_RescueDaughter1.function = "RescueDaughter_NearCave";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.hour  = sti(GetTime()+2);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CaveOver";
			NextDiag.CurrentNode = "Prosper_11";
			pchar.questTemp.Sharlie.RescueDaughter = "true";
			LocatorReloadEnterDisable("Fortfrance_exittown", "reload2_back", true);//форт
			LocatorReloadEnterDisable("Martinique_Jungle_01", "reload1_back", true);//джунгли
			LocatorReloadEnterDisable("Martinique_Jungle_04", "reload1_back", true);//джунгли
		break;
		
		case "Prosper_11":
			dialog.text = "거의 자리에 다 왔어, "+pchar.name+". 이 굽이 너머가 동굴 입구야. 가까이 오면 우리 계획을 말해주지.";
			link.l1 = "듣고 있네, 프로스페르.";
			link.l1.go = "Prosper_12";
		break;
		
		case "Prosper_12":
			dialog.text = "이 무거운 화승총으로 제대로 조준하려면 시간이 좀 필요해. 네가 시간을 벌어주면 절대 빗나가지 않을 거야. 만약 내가 백병전에 휘말리면 사격 지원은 기대하지 마. 총신으로 몽둥이질이나 하며 적을 막아내는 게 전부일 테니까. 이번 싸움은 네 검 솜씨에 달려 있어.";
			link.l1 = "무슨 말을 하려는 거지?";
			link.l1.go = "Prosper_13";
		break;
		
		case "Prosper_13":
			dialog.text = "네가 해야 할 일은 놈들의 시선을 끄는 거야. 그래야 내가 전부 쏴버릴 수 있지. 나는 움직이면서 쏠 수 없으니 한 자리에 붙어 있을 거다. 동굴 입구 근처에 놈 셋이 있다. 칼을 들고 최대한 빠르게 놈들에게 달려들어야 해\n놈 하나를 공격해서 네게 달려들게 만들어. 놈들을 나에게서 멀리 유인해. 셋 다 네게 집중하면, 네가 막고 피하는 동안 나는 새처럼 놈들을 쏴버릴 수 있어. 하지만 그 야만인들이 나한테 달려들면 우린 끝장이야. 준비됐나?";
			link.l1 = "내가 칼을 다루는 게 이번이 처음은 아니지. 이런 야만인들은 아무 위협도 안 돼.";
			link.l1.go = "Prosper_14";
			// belamour legendary edition -->
			link.l2 = "하! 나 걱정하지 마. 르망에서 사냥하는 거랑 똑같아! 실수로 내 등만 쏘지 마라!";
			link.l2.go = "Prosper_14a";
		break;
		
		case "Prosper_14a":
			AddCharacterExpToSkill(pchar, "FencingL", 10);
			AddCharacterExpToSkill(pchar, "FencingS", 10);
			AddCharacterExpToSkill(pchar, "FencingH", 10);
			AddCharacterExpToSkill(pchar, "Pistol", 10);
			dialog.text = "먼저 가, 나는 바로 뒤에 있을게. \n기억해! 놈들이 내게 가까이 오게 두면 안 돼!";
			link.l1 = "기억나, 가자. 앞으로!";
			link.l1.go = "Prosper_15";
		break;
		
		case "Prosper_14":
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			// <-- legendary edition
			dialog.text = "그럼 준비해. 먼저 가, 내가 바로 뒤따라갈 테니. 명심해라: 놈들이 내게 너무 가까이 오게 두면 안 돼!";
			link.l1 = "기억하고 있네. 내가 할 수 있는 건 다 해보겠네. 앞으로 나아가자!";
			link.l1.go = "Prosper_15";
		break;
		
		case "Prosper_15":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LocatorReloadEnterDisable("Martinique_jungle_04", "reload2_back", false);
			NextDiag.CurrentNode = "Prosper_16";
			NewGameTip("A challenging fight awaits ahead. (F6) for quick save.");
		break;
		
		case "Prosper_16":
			dialog.text = "잘했네, "+pchar.name+"! 이제 이 이교도 야만인들은 더 이상 살인을 저지르지 못할 거다. 이제 본격적인 일이 남았군 - 동굴이다. 안에 세 명이나 네 명쯤 있을 것 같지만 확실치는 않다. 자, 잘 들어라\n나는 10년 전에 거기 있었지. 동굴 안에는 좁은 통로가 있다. 그 통로를 따라가면 가운데에 구멍이 뚫린 벽으로 나뉜 작은 동굴방이 나온다. 전에 했던 대로 계획을 반복하자. 나는 입구 근처에 서 있을 테니, 너는 안으로 뛰어들어라\n녀석들을 도발하되, 한꺼번에 다 상대하려 하지 말고, 내가 공격당하지 않게만 막아라. 내가 말한 그 통로에 자리를 잡아라. 거긴 좁아서 한두 명만 너와 동시에 싸울 수 있을 거다\n나는 네 어깨 너머로 녀석들에게 총을 쏠 테니. 준비됐나?";
			link.l1 = "전진하자! 이 야만인 소굴을 끝장내자!";
			link.l1.go = "Prosper_17";
		break;
		
		case "Prosper_17":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LocatorReloadEnterDisable("Martinique_CaveEntrance", "reload1_back", false);
			AddComplexSelfExpToScill(20, 20, 20, 20);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.location = "Martinique_Grot";
			pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CreateIndiansGrot";
			NextDiag.CurrentNode = "Prosper_18";
		break;
		
		case "Prosper_18":
			dialog.text = "내 딸이 살아 있구나! 신께 감사하네! 우리가 제때 도착했어. "+pchar.name+". 당신께 신세를 졌습니다, 나리. 용감하고 훌륭한 전사이십니다!";
			link.l1 = "행복한 결말이어서 다행이네, 프로스페르. 인디언들을 모두 해치우는 건 정말 피비린내 나는 일이었지.";
			link.l1.go = "Prosper_19";
		break;
		
		case "Prosper_19":
			DialogExit();
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
		break;
		
		case "Prosper_20":
			dialog.text = "다시 한 번 깊이 감사드립니다, "+pchar.name+"! 이제 마을로 돌아갑시다. 내 딸의 생명은 그 어떤 돈으로도 값을 매길 수 없지만, 남은 저축을 드림으로써 감사의 뜻을 전하고 싶소. 생피에르에 도착하는 대로 기꺼이 드리겠소. 거절할 생각은 하지도 마시오!";
			link.l1 = "거절하지 않겠네, 프로스페르. 내가 자네를 도운 이유가 돈 때문은 아니었지만.";
			link.l1.go = "Prosper_21";
		break;
		
		case "Prosper_21":
			dialog.text = "그대는 진정한 기독교 기사이오, "+pchar.name+"! 이제 여기서 머뭇거리지 말고, 어서 집으로 돌아가세!";
			link.l1 = "...";
			link.l1.go = "Prosper_22";
		break;
		
		case "Prosper_22":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.Tutorial_Amulet.over = "yes";
			SetLaunchFrameFormParam("Back to the town...", "Reload_To_Location", 0, 3.0);
			SetLaunchFrameReloadLocationParam("FortFrance_town", "reload", "gate_back", "");
			LaunchFrameForm();
		break;
		
		case "Prosper_23":
			SelectPresentAmulet();
			dialog.text = "여기까지 왔군, 샤를. 다시 한 번 도와줘서 고맙네, 그리고 내 진심을 담아 이 소박한 페소와 금 두블론을 함께 전하네. 두블론은 함부로 쓰지 말고 특별한 때를 위해 아껴두게. 자네가 내게 베푼 큰 은혜에 비하면 이 돈이 많지 않다는 걸 알지만, 내 진심임을 알아주게. 그리고 이 부적도 받아주게,\n "+pchar.questTemp.SMQ.Text+"";
			link.l1 = "감사합니다! 안녕히 계십시오, 프로스페르. 당신과 사랑스러운 따님께 행복이 깃들길 바랍니다!";
			link.l1.go = "Prosper_24";
		break;
		
		case "Prosper_24":
			LocatorReloadEnterDisable("Fortfrance_exittown", "reload2_back", false);//форт
			LocatorReloadEnterDisable("Martinique_Jungle_01", "reload1_back", false);//джунгли
			LocatorReloadEnterDisable("Martinique_Jungle_04", "reload1_back", false);//джунгли
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(pchar, "gold_dublon", 15);
			TakeNItems(pchar, pchar.questTemp.SMQ.Amulet, 1);
			Log_Info("You've received 15 doubloons");
			Log_Info("You've received an amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "아, 너 같은 사내라면 그 여자에게 딱이겠지. 저 여자는 맨날 다리만 가늘고 턱도 없는 한량들한테 쫓겨 다니기만 하거든. 그런데 그놈들이 하나같이 어디론가 다 사라져 버렸으니, 잘된 일이야. 행운을 빌어, 샤를!";
			link.l1 = "...";
			link.l1.go = "Prosper_25";
		break;
		
		case "Prosper_25":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload10_back", "none", "", "", "", 10.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar,"authority", 2);
			AddCharacterExpToSkill(pchar, "Leadership", 120);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 70);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 70);//скрытность
			AddQuestRecord("SharlieF", "7");
			CloseQuestHeader("SharlieF");
			DeleteAttribute(pchar, "questTemp.SMQ");
			pchar.questTemp.Prosper_fmql = "true"; // Addon-2016 Jason, французские миниквесты (ФМК)
			pchar.questTemp.ZsI_Cannibals = true;	//Sinistra Требуется для квеста "Знакомство с индейцами"
			pchar.quest.Sharlie_JungleNative.win_condition.l1 = "location";
			pchar.quest.Sharlie_JungleNative.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.Sharlie_JungleNative.function = "SharlieJungleNative";
			SetCurrentTime(17,30);
			//AddTimeToCurrent(2,0);
			//QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Selina":
			dialog.text = "아! 신이시여, 도와주소서! (울음) 당신은... 당신은 여기서 무슨 끔찍한 일이 벌어지고 있는지 상상도 못 할 거요! 이... 이 인디언들이 우리를 여기로 끌고 와서 죽이고 잡아먹으려 했소! 세자르 블랑셰도 여기 있었는데... 야만인들이 그를 데려갔소... 무슨 끔찍하고 사악한 의식을 치르더니... 주여, 차마 입에 담을 수도 없소! 다음 차례가 나였소! 내일이면 나를 죽일 생각이었단 말이오!";
			link.l1 = "진정해, 셀린. 이제 다 끝났어. 그 놈들은 마땅한 벌을 받았으니 더 이상 아무도 해치지 못할 거야.";
			link.l1.go = "Selina_1";
		break;
		
		case "Selina_1":
			dialog.text = "질베르 쿠르시도 여기 있어. 저기... 그는, 어... 아직 회복하지 못했어. 그와 얘기해 봐... 그럼 얼른 여기서 나가자!";
			link.l1 = "자, 자. 괜찮아, 아가야. 이제 그만 울어. 다 잘 될 거야. 네 아버지는 정말 훌륭한 분이시니, 아무도 널 해치지 못하게 하실 거야... 밖에 나가 있어, 내가... 어... 질베르를 여기서 데리고 나갈 테니, 나중에 따라갈게.";
			link.l1.go = "Selina_2";
		break;
		
		case "Selina_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
			sld = characterFromId("RD_Prosper");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_1", "", 5.0);
			AddQuestRecord("SharlieF", "5");
			sld = characterFromId("RD_Jilberte");
			LAi_SetStayType(sld);
		break;
		
		case "Selina_3":
			dialog.text = "하느님과 성모님께서 내 기도를 들으셨군요! 우리를 구하러 오셨습니까?";
			link.l1 = "너... 네 이름이 셀린 맞지?";
			link.l1.go = "Selina_4";
		break;
		
		case "Selina_4":
			dialog.text = "그래... (울음) 너... 너는 여기서 무슨 끔찍한 일이 벌어지고 있는지 상상도 못 할 거야! 이... 이 인디언들이 우리를 여기로 끌고 와서 죽이고 잡아먹으려고 해! 세자르 블랑셰도 여기 있었어... 그를 데려갔지... 무슨 악마 같은 의식을 치르더니... 주여, 말도 못 하겠어! 다음은 나래! 내일 나를 죽이려고 했어...";
			link.l1 = "진정해, 꼬마 아가씨... 미안하지만, 나쁜 소식을 전하러 왔어. 나는 네 아버지와 함께 여기 왔지. 네 아버지는 바로 밖에서 우리가 너에게 가려고 싸우는 중에 그 붉은 피부의 야만인들에게 살해당했어. 널 구하려고 자신의 목숨을 바치셨다.";
			link.l1.go = "Selina_5";
		break;
		
		case "Selina_5":
			dialog.text = "뭐라고?! 우리 아버지가... 오, 맙소사! 나... 나... (흐느낌)";
			link.l1 = "애도를 표합니다, 셀린. 여기 당신과 함께 있는 다른 사람이 있지요?";
			link.l1.go = "Selina_6";
		break;
		
		case "Selina_6":
			dialog.text = "(눈물을 흘리며) 그래... 질베르 쿠르시. 저 안에 있어... 아직 회복하지 못했어. 가서 그와 이야기해 봐... 그다음 얼른 여기서 나가자!";
			link.l1 = "네, 물론이지. 여기서 한순간도 허비할 수 없어.";
			link.l1.go = "Selina_7";
		break;
		
		case "Selina_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
			AddQuestRecord("SharlieF", "6");
			sld = characterFromId("RD_Jilberte");
			LAi_SetStayType(sld);
			AddComplexSelfExpToScill(20, 20, 20, 20);
		break;
		
		case "Selina_8":
			dialog.text = "아버지... 불쌍하고 소중한 우리 아버지! 아, 나리, 저를 구해주신 것에 대해 아직 감사 인사도 못 드렸네요...";
			link.l1 = "셀리나, 너와 길버트가 그 동굴에서 살아나와서 정말 다행이야. 네 아버지의 영웅적인 죽음은 헛되지 않았어.";
			link.l1.go = "Selina_9";
		break;
		
		case "Selina_9":
			dialog.text = "(울면서) 제발요, 나리, 우리를 마을까지 데려가 주세요. 군인들을 불러 아버지의 시신을 모셔가게 해야 해요, 그래야 아버지께서 제대로 된 그리스도교식 장례를 치르실 수 있으니까요...";
			link.l1 = "물론이지, Celine. 나를 따라와!";
			link.l1.go = "Selina_10";
		break;
		
		case "Selina_10":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Selina_11":
			dialog.text = "감사합니다, 나리, 저희 불쌍한 아버지를 함께해 주셔서... 저를 확실한 죽음에서 구해주셔서 정말 감사합니다. 저... 저... 여기, 이 두블룬 자루를 받아주세요. 집에서 아버지의 궤짝에서 찾은 거예요. 제발, 거절할 생각은 하지도 마세요!";
			link.l1 = "고마워, 셀린. 우리가 너를 구할 수 있어서 다행이야. 그리고 아버지를 잃은 것에 진심으로 애도를 표해.";
			link.l1.go = "Selina_12";
		break;
		
		case "Selina_12":
			TakeNItems(pchar, "gold_dublon", 15);
			PlaySound("interface\important_item.wav");
			dialog.text = "당신은 고귀한 분이십니다, 나리. 결코 잊지 않겠소. 안녕히 가십시오!";
			link.l1 = "잘 가요, 셀린.";
			link.l1.go = "Selina_13";
		break;
		
		case "Selina_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar,"authority", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			AddQuestRecord("SharlieF", "8");
			CloseQuestHeader("SharlieF");
			pchar.questTemp.ZsI_Cannibals = true;	//Sinistra Требуется для квеста "Знакомство с индейцами"
			
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Jilberte":
			PlaySound("Voice\English\other\robinzons-08.wav");
			dialog.text = "오, 주님, 정말 모든 일이 끝난 건가요? 도무지 믿기지가 않아요... 당신이 나와 셀린 둘 다를 구해줬어요. 만약 당신이 아니었다면, 불쌍한 세자르에게 닥쳤던 운명이 내일은 셀린에게 닥쳤을 것이고, 며칠 뒤에는 나에게도 같은 운명이 기다리고 있었을 거예요.";
			link.l1 = "이 인디언들, 정말 식인종이란 말이야?!";
			link.l1.go = "Jilberte_1";
		break;
		
		case "Jilberte_1":
			dialog.text = "의심하나? 배짱이 있다면 저놈들 취사장 불더미 속을 들여다보시지. 불쌍한 세자르 영감이 거기 있을 거야. 이제는 그냥 갉아먹힌 뼈만 남았지...\n";
			link.l1 = "성체성사라... 아니, 나는 사양하겠소. 나는 유럽에서 막 도착했을 뿐인데, 이 세상에 아직도 이렇게 사악하고 악마 같은 일이 벌어지고 있다는 건 상상도 못 했소.";
			link.l1.go = "Jilberte_2";
		break;
		
		case "Jilberte_2":
			dialog.text = "카리브 해에서는 별의별 기이한 일들이 일어나지. 구세계에서는 소문으로만 들었던 일들 말이야... 인디언 주술사, 마법, 샤먼, 그리고 비밀 의식들. 여기 오래 머물면 온갖 마귀 짓을 직접 보게 될 거야. 하지만 용서하게, 아직 자네가 날 구해준 데 대해 감사를 못 했군—아직도 충격에서 벗어나지 못해서 그래\n자네가 내 목숨을 구했으니, 말뿐만 아니라 금으로도 고마움을 표하겠네. 셀린과 나를 도시까지 호위해 주게. 그곳에서야말로 자네가 마땅히 받아야 할 대로 감사를 표할 수 있을 것이네, 나리.";
			link.l1 = "좋아. 밖으로 나가. 나는 먼저 여기 좀 둘러볼 거야.";
			link.l1.go = "Jilberte_3";
		break;
		
		case "Jilberte_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_3", "OpenTheDoors", 10.0);
			pchar.quest.Sharlie_RescueDaughter5.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter5.win_condition.l1.location = "Martinique_CaveEntrance";
			pchar.quest.Sharlie_RescueDaughter5.function = "RescueDaughter_GoHome";
		break;
		
		case "Jilberte_4":
			dialog.text = "저를 구해주신 데 대해 다시 한 번 깊은 감사를 표합니다, 나리! 약속드린 대로, 말뿐 아니라 은 페소와 금 두블룬으로도 감사의 뜻을 전합니다.";
			link.l1 = "모든 일이 잘 풀려서 기쁘네, Gilbert.";
			link.l1.go = "Jilberte_5";
		break;
		
		case "Jilberte_5":
			AddMoneyToCharacter(pchar, 3000);
			TakeNItems(pchar, "gold_dublon", 20);
			Log_Info("You've received 20 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "이 일이 얼마나 기쁜지 상상도 못하실 겁니다! 다시 한 번 감사드리며, 이제 물러가겠습니다, 나리.";
			link.l1 = "행운을 빌어, 질베르! 그런데 혹시 생피에르에 다른 도움이 필요한 사람이 있는지 아나?";
			link.l1.go = "Jilberte_6a";
		break;
		
		case "Jilberte_6a":
			dialog.text = "모르겠소만... 거리의 시민들에게 물어보시오, 나리. 평범한 주민들이나 좀 사는 사람들은 별 쓸모 있는 정보를 주지 않을 테지만, 부유한 귀족들은... 그들이라면 자네에게 줄 일이 있을지도 모르지.";
			link.l1 = "알겠소, Gilbert, 고맙소. 또 봅시다!";
			link.l1.go = "Jilberte_6";
		break;
		
		case "Jilberte_6":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.Sharlie.RescueDaughter");
			
			//Подбегает дворянин с квестом "девочка по вызову"
			sld = GetCharacter(NPC_GenerateCharacter("GigoloMan", "Guide_2", "man", "man", 25, FRANCE, 5, true, "soldier"));
			SetFantomParamFromRank(sld, 25, true);
			sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
			sld.dialog.currentnode = "GigoloMan";
			sld.greeting = "noble_male";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetLoginTime(sld, 6.0, 21.0);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto1");
			sld.talker = 9;
			LAi_SetCitizenType(sld);
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"이봐, 나는 이 도시의 법을 지키는 시민이오. 강도처럼 칼을 드러내고 다니지 말아 주시오.","나리, 제발이오, 법은 명확하오: 성벽 안에서는 남자들이 무기를 뽑은 채 다닐 수 없소.");
			link.l1 = LinkRandPhrase("좋아.","좋소.","원하시는 대로...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (npchar.id == "GigoloMan") NextDiag.TempNode = "GigoloMan";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

void SelectPresentAmulet()
{
	switch (pchar.HeroParam.HeroType)
	{        
		case "HeroType_1":
			pchar.questTemp.SMQ.Amulet = "indian_7";
			pchar.questTemp.SMQ.Text = "it adds endurance and gives a second wind.";
		break;
		
		case "HeroType_2":
			pchar.questTemp.SMQ.Amulet = "amulet_7";
			pchar.questTemp.SMQ.Text = "it heightens resilience to battle wounds.";
		break;
		
		case "HeroType_3":
			pchar.questTemp.SMQ.Amulet = "indian_4";
			pchar.questTemp.SMQ.Text = "it raises the attack strength of your weapons.";
		break;
		
		case "HeroType_4":
			pchar.questTemp.SMQ.Amulet = "indian_1";
			pchar.questTemp.SMQ.Text = "it makes fire weaponry much more lethal.";
		break;
	}
}
