// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있으십니까?","무엇을 도와드릴까요?"),"얼마 전에 그 질문을 나에게 하려고 했었지...","그래, 맞지... 또 빙빙 도는 거냐?","이봐, 여기서 재정은 내가 맡고 있어, 질문엔 대답 안 해...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("생각이 바뀌었소...","지금은 할 이야기가 없소."),"으음, 내 기억이 다 어디로 갔지...","맞췄군, 미안하네...","알겠습니다...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = "이 귀걸이들을 한번 보시지요, 나리. 정글에서 산적의 주머니에서 발견했습니다. 분명히 훌륭한 보석세공인의 작품인데, 이 황야 출신은 아닌 듯합니다. 어떻게 생각하십니까?";
                link.l1.go = "Sharlie_junglejew";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskiper")
			{
				link.l1 = "나는 당신에게 Folke Deluc라는 채무자가 있다는 것을 알고 있소. 그의... 연체가 얼마나 심각한지 말해 주시오?";
                link.l1.go = "Sharlie";
			}	
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipermoney")
			{
				link.l1 = "Folke Deluc의 빚 때문에 왔소.";
                link.l1.go = "Sharlie_repeat";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipercaptive")
			{
				link.l1 = "당신의 부탁을 끝냈습니다, 나리. 여기 당신의... 스페인 친구가 있습니다.";
                link.l1.go = "Sharlie_14";
			}
			//<-- Бремя гасконца */
			
			//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
			if (CheckAttribute(pchar, "questTemp.Del_Rostovshik"))
			{
				link.l1 = "...에 관해서 왔소...";
                link.l1.go = "Del_Deluck";
			}
			if (CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat"))
			{
				dialog.text = "40두블론 가져왔소?";
				if (PCharDublonsTotal() >= 40)
				{
					link.l1 = "내 장교를 위한 돈이오...";
					link.l1.go = "Del_Deluck_5";
				}
				link.l2 = "아니, 아직 생각 중이오.";
				link.l2.go = "exit";
			}
			//<-- Миниквест "Делюк"
		break;
		
		case "Sharlie":
			DelLandQuestMark(npchar);
			dialog.text = "그게 왜 신경 쓰이시는지 여쭤봐도 되겠습니까?";
			link.l1 = "나는 이 사람이 감옥에 있는 것이 아니라 자유롭게 있기를 원하오. 내가 들은 바로는, 이 빚이 당신에게 갚아지기 전까지는 그가 풀려나지 않는다 하더군. 나는 이 빚을 갚는 데 관심이 있소.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "아하, 그럼 이야기가 달라지는군요. 저도 제 돈을 돌려받는 데 관심이 있습니다... 이 폴크 들루크라는 자는 참 이상한 인물입니다. 비교적 적은 금액, 오천 페소를 빌려 갔지요. 그런데 그냥 갚기를 거부하고 숨어버렸습니다. 결국 이자가 원금만큼 불어나더니, 그는 감옥 신세를 지게 되었지요.";
			link.l1 = "그렇다면 그의 빚이 현재 만까지 쌓였다는 말이오?";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "정확히 만사백오십 페소입니다, 나리. 그러니 그의 자유는 이 금액으로 매겨졌습니다. 저에게 이 돈을 지불하실 생각이십니까? 조금 놀랐군요...";
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = "놀라지 마시오. 여기 돈이 있소.";
				link.l1.go = "Sharlie_3";
			}
			link.l2 = "흠... 정말 만만치 않은 금액이군요. 들어보시지요, 나리, 혹시 우리 서로 거래를 해볼 수 있지 않겠습니까? 예를 들어, 나리께서 제가 처리할 만한 무언가를 가지고 계시고, 저의 호의를 이 만오백에 평가해 주실 수도 있겠지요...";
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart")) link.l2.go = "Sharlie_5x";
			else link.l2.go = "Sharlie_5"; // Addon 2016-1 Jason пиратскаЯ линейка 1
		break;
		
		case "Sharlie_3":
			AddMoneyToCharacter(pchar, -10450);
			dialog.text = "그래, 당신이 그 선원을 위해 그렇게 많은 돈을 내겠다고 하니 정말로 그가 필요하신 모양이군요. 어쨌든 그건 내 알 바 아니지요, 나리?\n여기 그의 채무증서가 있습니다. 이제부터 당신이 그의 빚을 넘겨받았으니, 그에게 돈을 요구할 권리가 있습니다.\n그리고 물론, 그의 감옥 석방 청원서도 함께 드리죠.";
			link.l1 = "딱 내가 원하던 거였소. 안녕히 가시오, "+npchar.name+"!";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			DialogExit();
			Log_Info("You have received a bill of debt");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
			pchar.questTemp.Sharlie = "freeskiper";
			AddLandQuestMark(characterFromId("FortFranceJailOff"), "questmarkmain");
		break;
		
		case "Sharlie_5x": // Addon 2016-1 Jason пиратскаЯ линейка 1
			dialog.text = "호의라고? 유감이지만, 나는 너에게 아무런 호의도 필요 없네. 적어도 지금은 말이야.";
			link.l1 = "안타깝군. 그럼 돈을 Folke에게 가져가야겠어. 잘 있어!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_5":
			dialog.text = "부탁이라... 흠... 있지, 나리, 자네가 어제 왔다면 거절했을 거야. 하지만 지금은... 그래, 처리해야 할 일이 하나 있네. 하지만 미리 경고하지, 꽤 위험한 일이야.";
			link.l1 = "뭐가 위험하다는 거지?";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = "당신의 소중한 목숨을 위해서지, 물론. 그러니 동의하기 전에 잘 생각해 보고, 그런 일을 할 각오가 되어 있는지 결정하시오.";
			link.l1 = "나리, 위험쯤이야 저에게 낯선 것이 아닙니다. 이미 수차례나 위험한 상황을 겪어봤지요. 그러니 이제 본론으로 들어갑시다. 요새 전체 주둔군을 혼자서 상대하는 일이 아니라면, 나리께서 그토록 은근히 암시하는 일을 어쩌면 해낼 수 있을지도 모르겠군요.";
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			dialog.text = "좋아. 그럼 들어보게. 오늘 밤, 몇몇 해적들과 포로 한 명이 르 프랑수아의 해적 소굴을 떠나 르 마랭 만으로 걸어갈 걸세. 그 포로는 스페인 장교이자 요새 공학에 아주 능한 전문가라네. 영국 놈들은 그를 자기들 목적에 이용하려고, 전함을 보내 만에서 그를 데려갈 생각이지.\n그 장교는 내 오랜 친구라, 그가 영국 포로가 되는 걸 원치 않네. 우리가 스페인과 전쟁 중이라 현지 당국에 도움을 청할 수도 없고. 시간이 더 있었다면, 스페인 놈... 아니, 내 친구를 되찾을 만한 사람들을 고용했겠지만, 아쉽게도 시간이 없네!\n이 일은 자네만이 믿고 맡길 수 있네. 자네가 르 마랭 만으로 가서... 해적들을 설득해 포로를 넘기게 해야 하네. 그들이 순순히 협조할 것 같진 않으니, 어떻게 할지는 자네에게 달렸네.";
			link.l1 = "호송대에 해적이 몇 명이나 있을까요?";
			link.l1.go = "Sharlie_8";
		break;
		
		case "Sharlie_8":
			dialog.text = "모르겠소. 아마 두 사람, 아니면 세 명이나 네 명일 수도 있지. 그래서, 자네 생각은 어떤가?";
			link.l1 = "나는 이미 '위험 따위는 내게 낯설지 않다'고 말했지. 그리고 칼을 어떻게 쥐어야 하는지도 안다네.";
			link.l1.go = "Sharlie_10";
			link.l2 = "흠. 네 말이 맞아, 위험하지. 나 혼자 해적으로 가득한 선원들을 공격하지는 않을 거야.";
			link.l2.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = "그건 당신의 결정이오. 이 일이 자신 없다고 생각된다면, 지금 당장 거절하는 게 좋겠소. 그러면 나는 델루크의 빚돈을 기다리겠소.";
			link.l1 = "알겠소. 그에게 돈을 가져다주겠소. 나중에 봅시다!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_10":
			dialog.text = "좋소. 그 말을 들으니 기쁘군. 그럼 르 마랭 만으로 가시오, 해적들은 저녁 7시부터 새벽 4시까지 거기 있을 것이오. 놓치지 마시오! 그리고 배를 쓸 생각은 하지도 마시오! 그런 행동은 놈들을 도망치게 할 테니, 반드시 정글을 걸어서 가시오!\n죄수를 찾으면 나에게 데려오시오, 문은 열어두겠소. 도시로 돌아가기 전에 새벽 1시까지 기다리는 걸 추천하오, 경비병들의 눈을 피해야 하니까. 조심하고 행운을 빌겠소!";
			link.l1 = "감사합니다! 정말 행운이 꼭 필요하겠군요...";
			if (CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE)) link.l1.go = "Sharlie_13";
			else link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = "잠깐만! 보니까 총도 없잖아. 내 총 하나 가져가. 탄환도 몇 개 줄게. 분명 쓸모가 있을 거야.";
			link.l1 = "네, 이건 분명히 도움이 될 겁니다. 감사합니다, 나리.";
			link.l1.go = "Sharlie_12";
		break;
		
		case "Sharlie_12":
			Log_Info("You have received a combat pistol");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol1");
			TakeNItems(pchar, "bullet", 20);
			TakeNItems(pchar, "gunpowder", 20);
			dialog.text = "이제 가시오, 신의 가호가 함께하길!";
			link.l1 = "...";
			link.l1.go = "Sharlie_13";
		break;
		
		case "Sharlie_13":
			DialogExit();
			pchar.quest.Sharlie_captive_Tut.win_condition.l1 = "location";
			pchar.quest.Sharlie_captive_Tut.win_condition.l1.location = "Shore39";
			pchar.quest.Sharlie_captive_Tut.function = "Tutorial_Rest_Delay";
			pchar.quest.Sharlie_captive.win_condition.l1 = "HardHour";
			pchar.quest.Sharlie_captive.win_condition.l1.hour = 19.00;
			pchar.quest.Sharlie_captive.function = "Captive_Timer";
			SetFunctionTimerCondition("Captive_CreatePiratesOver", 0, 0, 1, false);
			AddQuestRecord("SharlieD", "1");
			pchar.questTemp.Sharlie = "bankskiperfight";
			pchar.questTemp.Sharlie.Captive = "true";
			pchar.questTemp.Sharlie.Captive.Name = GetFullName(npchar);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_03", "reload", "reload2_back");
		break;
		
		case "Sharlie_14":
			pchar.quest.Sharlie_captive1.over = "yes";
			pchar.quest.Sharlie_captive2.over = "yes";
			pchar.quest.Sharlie_captive3.over = "yes";
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("shore39", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_03", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload8_back");
			DelLandQuestMark(npchar);
			ref sld = characterFromId("CaptiveSpain");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", 5.0);
			sld.lifeday = 0;
			SetNationRelation2MainCharacter(FRANCE, RELATION_FRIEND);
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
			dialog.text = "훌륭하군요! 당신이 그 일을 성공적으로 처리해서 매우 기쁩니다. 작전의 세부 사항까지 알 필요는 없겠지요? 자, 이제 내 사랑하는 스페인 손님도 내 집에서 안심할 수 있겠군요...";
			link.l1 = "Folke Deluc의 빚은 어떻게 할까요?";
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = "물론이지. 그의 채무증서를 받아가게. 이제 그 빚은 자네 것이니, 그에게 돈을 요구할 권리가 있네. 그리고 물론, 그의 감옥 석방 청원도 하게. 내가 약속한 대로 모두 처리했는가?";
			link.l1 = "예, 나리. 모든 것이 계약대로 엄격히 진행되고 있습니다. 이제 물러가 보겠습니다.";
			link.l1.go = "Sharlie_4";
			AddQuestRecord("SharlieD", "7");
			CloseQuestHeader("SharlieD");
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
		break;
		
		case "Sharlie_repeat":
			dialog.text = "그럼, 그의 빚을 갚을 준비가 되었소?";
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = "예. 여기 돈이오.";
				link.l1.go = "Sharlie_3";
			}
			link.l2 = "안타깝게도, 아직 필요한 금액을 모으지 못했습니다...";
			link.l2.go = "exit";
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "흠. 네 말이 맞군, 이건 값비싼 귀걸이들이고 분명 구세계에서 만들어진 것이야... 뭐라 할까? 내가 서른... 아니, 서른다섯 금 더블룬을 주겠네. 돈을 받아가게, 이보다 더 좋은 값은 못 받을 걸세.";
			link.l1 = "삼십오 두블룬? 나쁘지 않은 가격이군. 동의하네. 자, 여기 있소.";
			link.l1.go = "Sharlie_junglejew_1";
			link.l2 = "아니. 이 귀걸이는 내가 가지겠소.";
			link.l2.go = "exit";
			npchar.quest.junglejew = "true";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info("You've given the earrings");
			RemoveItems(pchar, "jewelry25", 1);
			TakeNItems(pchar, "gold_dublon", 35);
			AddQuestRecord("SharlieE", "3");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
		break;
		
		//--> Миниквест "Делюк"
		case "Del_Deluck":
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik");
			dialog.text = "알고 있습니다, 알고 있습니다, 선장님. 당신의 항해사가 거의 모든 프랑스 식민지에서 빚을 진 모양이더군요. 사실, 저는 오래전부터 그 사실을 알고 있었지요. 동료들에게도 확인해 보았습니다, 표준 절차이니까요...";
			link.l1 = "그리고 지난번 거래 때 나에게 알릴 만큼 중요한 일이라고는 생각하지 않았다는 말입니까?";
			link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			dialog.text = "왜냐고요? 그 당시 나는 주로 델루크가 나에게 진 빚에 신경을 쓰고 있었소. 참고로, 그 빚이 가장 컸지요. 당신이 그 빚을 갚자마자 나는 즉시 동료들에게 알렸소... 우리는 전문 배달원들로 이루어진 거대한 조직을 가지고 있으니, 내 책상 위에 델루크의 어음이 쌓이는 데 오래 걸리지 않았소.";
			link.l1 = "그렇군... 내가 그에게 중대한 관심이 있고 지불할 능력도 있다는 걸 알면서 그걸 샀다는 말이오... 이건 협박이오, 몬시뇰.";
			link.l1.go = "Del_Deluck_3";
		break;
		
		case "Del_Deluck_3":
			dialog.text = "제 일일 뿐입니다, 선장님! 오늘 기준으로 당신의 항해사가 진 총 빚은 40두블룬이며, 참고로 이자도 계속 붙고 있습니다... 지불하시겠습니까?";
			link.l1 = "아직 답할 준비가 안 됐지만, 고려해 보겠소. 안녕히 가시오!";
			link.l1.go = "Del_Deluck_4";
		break;
		
		case "Del_Deluck_4":
			DialogExit();
			
			pchar.questTemp.Del_Rostovshik_repeat = true;
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.dialog.currentnode = "Del_Deluck";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
		break;
		
		case "Del_Deluck_5":
			dialog.text = "훌륭합니다! 다음에 무엇을 해야 할지 알고 계시겠지요 - 지난번과 똑같이 하면 됩니다.\n여기 서류가 있습니다 - 감옥 사령관에게 제출하십시오.\n함께 거래할 수 있어 즐거웠습니다, 선장님.";
			link.l1 = "이 상황에서 즐길 만한 게 별로 없군. 안녕히 가시오.";
			link.l1.go = "exit";
			RemoveDublonsFromPCharTotal(40);
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik_repeat");
			Log_Info("You have received a bill of debt");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
			pchar.questTemp.Del_DeluckSvoboda = true;
			AddLandQuestMark(characterFromId("FortFranceJailOff"), "questmarkmain");
			DelLandQuestMark(npchar);
		break;
		//<-- Миниквест "Делюк"
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
