// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("어서 말해라, 무엇을 원하는가?","바로 그 얘기를 하고 있었소. 당신이 잊은 모양이군...","오늘만 세 번째로 뭔가를 또 물어보시는군요...","이봐, 여긴 상점이야. 사람들은 여기서 물건을 사 간다고. 방해하지 마!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("있잖아, "+NPChar.name+", 다음 기회에 하도록 하지.","맞아요, 무슨 이유에선지 내가 잊고 있었군요...","그래, 정말로 이번이 세 번째야...","흠, 나는 안 하겠어...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
			{
				Link.l1 = "이봐, 나리, 일거리를 좀 찾고 있소. 정규직이나 화물을 나르는 일 말고, 심부름 같은 걸 말이오. 혹시 도움이 필요하시오?";
				Link.l1.go = "Sharlie_storehelper";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
			{
				Link.l1 = "당신이 시킨 일을 끝냈소. 그라람 라부아를 찾았소.";
				Link.l1.go = "Sharlie_storehelper_2";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
			{
				Link.l1 = "새 조수를 맞이하십시오, 나리.";
				Link.l1.go = "Sharlie_storehelper_11";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
			{
				Link.l1 = "또 저입니다, 나리. 보상을 받으러 왔습니다.";
				Link.l1.go = "Sharlie_storehelper_13";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = "이 귀걸이들을 한번 보시지요, 나리. 정글에서 죽은 산적의 시체에서 발견한 것입니다. 분명히 훌륭한 보석세공사의 작품으로, 이 근방 출신은 아닌 듯합니다. 이 귀걸이에 대해 아시는 바가 있습니까?";
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Бремя гасконца */
		break;
		
		//--> Бремя гасконца
		case "Sharlie_storehelper":
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") 
			{
				dialog.text = "실례합니다, 나리, 그런데 검은 어디에 두셨습니까? 칼 없이 마을을 나서는 건 위험합니다. 정글에서 무슨 일이 일어날지 아무도 모릅니다!";
				link.l1 = "젠장, 완전히 잊고 있었어! 전부 다 빼앗겼잖아!";
				link.l1.go = "Store_noweapon";
				break;
			}
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("Fortfrance_town", "reload", "reload6_back");
			dialog.text = "일거리? 흠. 자네가 관심 있을 만한 일이 하나 있지. 내 조수가 사라졌네; 원래 내 창고에서 일하던 녀석이야. 벌써 일주일째 소식이 없어서 아주 성가셔. 내가 그 녀석 일을 대신해야 하니 시간도 없고 말이야.\n제발, 그 바보 좀 찾아서 도대체 왜 일을 내팽개치고 사라졌는지 알아봐 주게. 아니, 더 좋게는 녀석을 내게 데려오게. 그러면 자네에게 1,000피스의 에잇을 주겠네.";
			link.l1 = "좋아, 알겠소. 그의 이름이랑 생김새를 말해 주시오. 어디서 그를 찾아야 할지 짐작가는 곳이라도 있소?";
			link.l1.go = "Sharlie_storehelper_1";
			link.l2 = "고작 천 때문에 신만이 아는 곳에서 사람을 찾으라고? 농담하는 거지!";
			link.l2.go = "Sharlie_storehelper_exit";
			npchar.quest.storehelper = "true";
		break;
		
		case "Sharlie_storehelper_exit":
			AddTimeToCurrent(2,0);
			LocatorReloadEnterDisable("Fortfrance_town", "reload10_back", false);// пу откр
			dialog.text = "이봐, 나리. 일자리를 찾는 건 당신이오, 내가 아니오? 하고 싶지 않으면 억지로 시키진 않겠소. 좋은 하루 되시오.";
			link.l1 = "흠... 항만청에 가서 확인해 봐야겠군. 거기서 더 실질적인 제안을 받을 수도 있지.";
			link.l1.go = "exit";
		break;
		
		case "Sharlie_storehelper_1":
			dialog.text = "이름은 그랄람 라부아. 생김새? 서른다섯 살쯤, 수염과 콧수염, 긴 갈색 코트에 흰 셔츠를 입었지. 아, 그리고 항상 그 우스꽝스러운 삼각모를 쓰고 다녀. 마치 자기 엉덩이에 닻을 꽂은 제독인 척하지.\n생피에르에는 없어. 내가 마을 전체를 다 뒤져봤거든. 분명히 정글이나 레 프랑수아에 숨어 있는 해적들과 함께 있을 거야.\n다시 생각해보면, 아마 우리 섬 동쪽에 있는 해적 정착지인 르 프랑수아에 있을 가능성이 높아. 거기서 해적들과 수다를 떨고 있거나, 선술집에서 시간을 보내거나, 아니면 가게에서 현지 상인과 말다툼을 하고 있을지도 몰라.\n르 프랑수아로 가는 길? 도시 성문을 나가 정글로 들어가. 갈림길에서 왼쪽 길로 가고, 길을 따라가다가 오른쪽으로 꺾은 다음, 바위 사이 왼쪽 통로로 들어가면 르 프랑수아가 나올 거야. 길을 잃을 일은 없을 거라 생각해.";
			link.l1 = "좋소. 바로 수색을 시작하겠소. 무언가 발견되는 대로 즉시 알려드리겠소.";
			link.l1.go = "exit";
			AddQuestRecord("SharlieA", "1");
			pchar.questTemp.Sharlie.Storehelper = "true";
			pchar.questTemp.Sharlie.Storehelper.Chance = rand(2);
			AddDialogExitQuestFunction("Sharlie_CreateStorehelper");
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload3_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload1_back");
		break;
		
		case "Sharlie_storehelper_2":
			DelLandQuestMark(npchar);
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload6_back");
			dialog.text = "아 그래? 그럼 그는 어디에 있지?";
			link.l1 = "르 프랑수아에서 그를 찾았소. 이제 더 이상 당신 밑에서 일하지 않을 거요.\n당신에 대해 꽤 거친 말도 많이 하더군요... 들어보고 싶으시오?";
			link.l1.go = "Sharlie_storehelper_3";
		break;
		
		case "Sharlie_storehelper_3":
			dialog.text = "아니오. 자세한 얘기는 듣고 싶지 않소... 안타깝군! 이제 조수 없이 내가 뭘 해야 한단 말이오?";
			link.l1 = "다른 사람을 고용하시오. 아니면 그라람이 말한 것처럼 정말 그렇게 큰 문제요?";
			link.l1.go = "Sharlie_storehelper_4";
		break;
		
		case "Sharlie_storehelper_4":
			dialog.text = "정말 운이 지독하군. 그런데 그 게으름뱅이가 뭐라고 했지?";
			link.l1 = "음, 우선 그는 분명히 빈둥거리며 시간을 보내고 있지는 않더군, 허허. 그가 말하길 생피에르 전체에서 아무도 당신 밑에서 일하려 하지 않는 이유가... 당신이 일꾼들에게 임금을 너무 적게 준다고 하더군. 맞아, 그런데 말이야, "+npchar.name+", 약속한 대로 천 페소를 빚졌소.";
			link.l1.go = "Sharlie_storehelper_5";
		break;
		
		case "Sharlie_storehelper_5":
			AddMoneyToCharacter(pchar, 1000);
			dialog.text = "자, 돈을 가져가시오. 하! 이걸로는 절대 부족하지! 물론, 아무도 나를 위해 일하려 하지 않지. 그 자식이 온갖 더러운 소문을 퍼뜨리려고 애썼거든. 내가 뭘 할 수 있겠소? 혼자서 다 할 수는 없잖소!\n난 짐 하나하나 다 세어볼 때까지 잠도 못 자오, 저 빌어먹을 일꾼들이 항상 뭔가를 훔쳐가니까. 지난번 하역 이후로 럼주 다섯 통이 없어졌소. 분명히 일꾼들이 ‘실수로’ 가져간 게 틀림없지...";
			link.l1 = "글쎄, 뭐라고 조언해야 할지 모르겠군. 좋아, 행운을 빌지. 이제 나는 가봐야겠어.";
			link.l1.go = "Sharlie_storehelper_6";
		break;
		
		case "Sharlie_storehelper_6":
			dialog.text = "잠깐! 자네가 나를 도와줄 수 있을 것 같군. 그 자식의 행방을 추적할 수 있었다면, 아마도 자네라면...";
			link.l1 = "이 마을에서 아무도 당신을 믿지 않는다면, 내가 대체 뭘 할 수 있겠소? 나는 여기 처음 온 사람인데...";
			link.l1.go = "Sharlie_storehelper_7";
		break;
		
		case "Sharlie_storehelper_7":
			dialog.text = "끝까지 말씀드리게 해주십시오, 나리. 당신은 르 프랑수아에 다녀온 적이 있지요. 다시 한 번 그곳에 가서 제게 일할 사람을 찾아주셨으면 합니다. 아마 그라람이 그 해적 소굴에서 제 평판을 완전히 망치진 않았을 테니까요\n일은 간단합니다. 화물을 세고 항구 노동자들이 도둑질하지 않게 감시하는 것이지요. 가끔은 제가 자리를 비울 때 저 대신 여기서 제 일을 해주시면 됩니다. 물론 추가 수당도 드릴 겁니다\n그들에게 상점에 머물 방을 제공하고, 주당 오백 피스의 보수를 준다고 전해주십시오. 나리, 저는 사업을 확장할 계획이고, 드디어 일이 잘 풀리고 있습니다. 조수가 꼭 필요합니다!\n참, 일꾼을 찾으려면 현지 선술집 주인 체사레 크레이그에게 도움을 요청하는 게 가장 좋습니다. 그 악당이 돈을 좀 받아먹긴 하겠지만, 제게 일할 만한 사람을 분명히 찾아줄 겁니다.";
			link.l1 = "흠. 해볼 수는 있겠지만, 확신은 없소... 이 일에 얼마를 주실 생각이오?";
			link.l1.go = "Sharlie_storehelper_8";
		break;
		
		case "Sharlie_storehelper_8":
			dialog.text = "그건 당신이 어떤 일꾼을 고용하느냐에 달렸소. 일꾼이 뛰어날수록 당신의 수고에 더 많은 돈을 지불하겠소. 공정하지 않소?";
			link.l1 = "내가 눈 감고 일하라고 강요하는 거 아니오? 내가 어떻게 당신이 일꾼을 어떻게 평가할지 알 수 있겠소? 아무나 나쁘다고 낙인찍을 수도 있지 않소, 아니면...";
			link.l1.go = "Sharlie_storehelper_9";
		break;
		
		case "Sharlie_storehelper_9":
			dialog.text = "나리! 저를 좀 인색하다고 부르는 건 맞을지 몰라도, 저를 부정직하다고 할 사람은 아무도 없소! 결과에 따라 보수를 드리겠다고 말씀드렸으면, 그건 진심이오. 제 입장에서도 한번 생각해 보시지요. 당신이 게으른 집시 하나를 데려와서, 일은커녕 빈둥거리다 밤에 저를 털지도 모르는 일 아니겠소!";
			link.l1 = "좋소. 동의하오. 당신 말을 믿겠소, "+npchar.name+". 집시들은 절대 데려오지 않겠습니다.";
			link.l1.go = "Sharlie_storehelper_10";
		break;
		
		case "Sharlie_storehelper_10":
			DialogExit();
			SetLaunchFrameFormParam("Back to Le Francois...", "Reload_To_Location", 0, 3.0);
			SetLaunchFrameReloadLocationParam("LeFransua_tavern", "reload", "reload1", "SharlieA_TeleportLF");
			LaunchFrameForm();
		break;
		
		case "Sharlie_storehelper_11":
			dialog.text = "일꾼을 찾아주셨습니까? 훌륭하군요. 그와 잠시 얘기 좀 나누겠습니다, 한 시간 후에 보상 받으러 오십시오.";
			link.l1 = "알겠소. 한 시간 후에 다시 오겠소.";
			link.l1.go = "Sharlie_storehelper_12";
			DelLandQuestMark(npchar);
		break;
		
		case "Sharlie_storehelper_12":
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Sharlie.Storehelper = "final";
			DialogExit();
			SetLaunchFrameFormParam("One hour passed...", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0); //крутим время
			RecalculateJumpTable();
			AddQuestRecord("SharlieA", "5");
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "Sharlie_storehelper_13":
			switch (sti(pchar.questTemp.Sharlie.Storehelper.Quality))
			{
				case 0:
					AddMoneyToCharacter(pchar, 3000);
					dialog.text = "그대가 찾아준 일꾼이 제법 마음에 드오. 말은 번지르르한데 행동은 좀 부족하긴 하지만, 걱정 마시오. 시간이 지나면 수다도 고쳐 놓을 테니. 보상으로 3,000 에잇을 주겠소. 여기 있소.";
					link.l1 = "감사합니다! 그런데, 나리, 혹시 이 마을에 중요한 일로 도움이 필요한 사람이 또 있는지 아십니까?";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
				
				case 1:
					AddMoneyToCharacter(pchar, 5000);
					dialog.text = "정말 귀한 일꾼을 찾아내셨군요! 그 악당 그라람보다도 훨씬 낫습니다. 매우, 매우 만족스럽습니다, 나리. 자, 보상으로 오천 에잇을 받으십시오.";
					link.l1 = "감사합니다! 그런데, 나리, 혹시 이 마을에 중요한 일로 도움이 필요한 사람이 또 있는지 아십니까?";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
				
				case 2:
					AddMoneyToCharacter(pchar, 4000);
					dialog.text = "좋은 일꾼을 찾으셨군요. 아직 장사의 모든 요령을 아는 건 아니지만, 곧 잘 익힐 거라 확신합니다. 나는 당신이 마음에 드오, 나리. 자, 보상으로 4,000에이트를 받으시오.";
					link.l1 = "감사합니다! 그런데, 나리, 혹시 이 마을에 중요한 일로 도움이 필요한 사람이 또 있는지 아십니까?";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
			}
		break;
		
		case "Sharlie_storehelper_14a":
			LocatorReloadEnterDisable("Fortfrance_town", "reload10_back", false);// пу откр
			dialog.text = "흠... 방금 전에 항구장 나리가 분명히 화가 난 채로 항만청으로 가는 걸 봤소. 그에게 가서 확인해 보시오; 무슨 일이 있었는지 누가 알겠소.";
			link.l1 = "그렇게 하겠습니다. 감사합니다, 나리.";
			link.l1.go = "Sharlie_storehelper_14";
			DelLandQuestMark(npchar);
		break;
		
		case "Sharlie_storehelper_14":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
			CloseQuestHeader("SharlieA");
			
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload6_back");
			
			QuestPointerToLoc("fortfrance_town", "reload", "reload10_back");
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "음, 뭐라고 해야 할까, 정말 훌륭한 귀걸이군. 내가 줄 수 있는 건... 어디 보자... 4,000에이트 동전이네. 이보다 더 많이 줄 사람은 없을 거라 생각하오. 거래하시겠소?";
			link.l1 = "거래 성사! 이제 당신 것이오.";
			link.l1.go = "Sharlie_junglejew_1";
			link.l2 = "아니. 이 보석들은 내가 가지겠소.";
			link.l2.go = "exit";
			npchar.quest.junglejew = "true";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info("You've given the earrings");
			RemoveItems(pchar, "jewelry25", 1);
			AddMoneyToCharacter(pchar, 4000);
			AddQuestRecord("SharlieE", "4");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
		break;
		
		case "Store_noweapon":
			dialog.text = "그렇게는 안 되오. 우리 총독께 가서 도움을 청해 보시지요.";
			link.l1 = "조언 고맙소. 그렇게 할 생각이오.";
			link.l1.go = "exit";
		break;
		//<-- Бремя гасконца
	}
	UnloadSegment(NPChar.FileDialog2);
}
