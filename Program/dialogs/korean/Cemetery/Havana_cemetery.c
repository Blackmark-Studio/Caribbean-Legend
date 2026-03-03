// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("어떻게 도와드릴까요?","무엇을 도와줄까?"),"무슨 일로 고민하시오, "+GetAddress_Form(NPChar)+"?","세 번째로, "+GetAddress_Form(NPChar)+", 뭐가 필요하지?","너한테 질렸어. 꺼져!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("생각이 바뀌었어, 미안하다.","별일 아니오, 실례하오."),"용서해, 아무것도 아니야.","맞아요, 벌써 세 번째군요. 미안하오...","죄송하오.",npchar,Dialog.CurrentNode);		
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "이봐, 혹시 하바나나 그 근처에서 조아킴 메리먼이라는 남자를 본 적 있거나 만난 적 있어? 중년의 포르투갈인 나리인데, 콧수염과 염소수염이 있고 눈빛이 날카로워. 혹시 만이나 정글 어딘가에서 본 적 있나? 그를 찾고 있어.";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "아, 아냐, 선원, 절대 아니야. 여기 아래에는 방문객이 거의 없어, 그러니까, 어... 그리고 네가 말한 그런 사람은 본 적도 없고, 그래서...";
			link.l1 = "정말인가? 그런데 왜 말을 더듬고 눈을 피하는 거지? 지금 나한테 거짓말하지 마라, 진실을 알고 있잖아. 다시 말하는 게 좋을 거다 - 그 남자를 본 적 있나?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "저, 저 말하는데요, 나리, 아무도 못 봤어요! 저, 저 어릴 때부터 말을 더듬었어요...";
			link.l1 = "거짓말이야, 다 거짓말. 네 눈을 보면 알 수 있어. 그자는 어디 있지, 메리맨은 어디 있냐?! 당장 말해!";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "나는 Merriman이라는 사람 몰라! 그 이름도 처음 들어봐! 그리고 나한테 해코지하려 들지 마, 아니면 사령관이 널 요새에서 목매달아 죽일 거야! 그러니 조심해서 행동해, 이 녀석아!";
			link.l1 = "오, 그렇게 생각하나? 좋아. 이제 내 말 잘 들어라: Joachim Merriman은 흑마법사다. 성스러운 종교재판소가 그를 찾고 있어. 수년 전 유럽에서 그는 무덤을 파헤치고, 시신을 더럽히고, 마법을 썼다는 죄로 화형을 선고받았지. 그리고 확실히 아는 건, 지금 그가 어딘가 이곳 아바나 변두리에 숨어 있다는 거다...\n";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "...";
			link.l1 = "...최근에 내가 근처 동굴에서 좀비들을 처치했고, 누가 책임자인지도 알아! 분명히, 메리먼이 묘지가 아니면 어디로 가겠어! 네가 그가 어디 있는지 알고 있지. 하지만 네 방식대로 해라, 나는 너한테 손끝 하나 대지 않겠지만 산티아고의 종교재판관들을 찾아갈 거야. 빈첸토 신부가 호아킴 메리먼이 하바나 묘지에서 그 지역 관리와 함께 숨어 있다는 사실을 알면 아주 흥미로워하겠지...";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "...";
			link.l1 = "...벌써 얼굴빛이 사라졌나? 내가 귀족의 명예를 걸고 맹세하지. 내가 조사 결과를 보고한 지 하루 만에, 이 섬 전체가 스페인 병사들로 들끓게 될 거다. 그리고 넌 고문대에 묶여서, 그 마법사가 어디 숨었는지 말할 때까지 애원하고 울게 될 거야. 그보다 늦지 않게, 넌 그의 공범으로서 화형당할 거고, 나는 그 화형식을 지켜볼 거다. 그 기분이 어떨 것 같으냐?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "부, 부탁이오, 나리! 나는 이 일에 아무런 관여도 없소, 맹세하오! 나... 나는 아무것도 할 수 없었소... 내가 어찌 그 자에게 맞설 수 있었겠소?! 그는 무시무시한 인간이오, 그는... 그가 뭘 할 수 있는지 당신은 상상도 못할 거요! 제발, 자비를 베풀어 주시오!";
			link.l1 = "나를 믿어, 그가 뭘 할 수 있는지 잘 알아. 내 두 눈으로 직접 봤으니까. \n그래서? 그는 어디 있지? 말해, 그러면 이 일에 널 끌어들이지 않겠다고 약속하지.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "그... 그는 묘지 아래 동굴에 숨어 있어. 그곳에 가려면 예배당 문을 통해서만 들어갈 수 있지. 그가 밖에 나가면 나는 집에 숨어서 꼼짝도 안 해. 내가 그 공포에서 벗어나고 싶은 마음이 얼마나 큰지 너는 모를 거야!\n하지만 감히 다가갈 수도 없어. 나... 나는 그가 새 무덤을 파는 걸 봤고, 그리고... 그리고 그 뒤에 죽은 자가 일어나 달빛 아래 묘지 안을 돌아다니는 걸 봤어! 그때 거의 미쳐버릴 뻔했다니까! 하지만 메리먼이 나보고 절대 떠나지 말라고 했어. 허락 없이 반나절이라도 집을 나가면, 반드시 찾아내서 나를 그 끔찍한 것... 걷는 해골로 만들어 버리겠다고 협박했어!";
			link.l1 = "그가 자기 동굴을 얼마나 자주 나가나?";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "음, 나는 그에게 마을에서 음식이랑 치료 물약, 그리고... 그가 요구하는 다른 것들도 가져다 줘. 그는 한 달에 한두 번, 달이 꽉 찼을 때 떠나. 문 앞에 쪽지를 남기고, 필요한 걸 적어놔... 내가 그걸 전달해서 문 앞에 두면, 돌아왔을 때 가져가.";
			link.l1 = "알겠소. 그의 소굴로 가는 저 문, 잠겨 있거나 그런 건가?";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			dialog.text = "그래. 항상 잠겨 있지. 아주 튼튼하고, 자물쇠도 크고 복잡해.";
			link.l1 = "흠... 메리맨이 바보는 아니지, 분명히 유럽에 있는 집처럼 은신처에 또 다른 출구가 있을 거야. 우리가 문을 억지로 열면, 그는 슬쩍 빠져나가서 다시는 찾을 수 없게 될 거야. 흠...";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "나리, 저를 종교재판소에 넘기지 않겠다고 맹세하시겠습니까?";
			link.l1 = "내가 맹세했으니, 귀족의 맹세는 신성한 법이오. 절대로 그대를 밀고하지 않겠소.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "아, 축복을 내리소서, 나리! 내가 그 동굴로 가는 길을 알아. 열쇠가 있어, 두 번째 열쇠... 내가 가지고 있지. 메리먼은 그 자물쇠에 열쇠가 두 개 있다는 걸 몰라. 나는 감히 들어갈 수 없지만, 당신이라면...";
			link.l1 = "열쇠를 내게 넘겨. 그럼 이 악몽에서 벗어나게 해주지.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			GiveItem2Character(pchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_crypt");
			dialog.text = "여기 있습니다, 나리. 정말로 그 자의 소굴에 들어가시려는 겁니까?";
			link.l1 = "그래. 너는 집 안에 들어가서 문을 잠그고 내가 안에 들어갔다 올 때까지 기다려. 내가 돌아오지 않으면, 모든 걸 버리고 최대한 빨리 도망쳐.";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = "하지만 조심하시오, 나리. 그의 동굴에서 무서운 소리가 들렸다고 하오. 누가 그곳에 살고 있을지 생각만 해도 두렵소. 하지만 메리먼이 혼자인 건 분명 아니오.";
			link.l1 = "할 수 있는 모든 조치를 취하겠소. 안녕히 계시오.";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			DialogExit();
			AddQuestRecord("Caleuche", "30");
			pchar.questTemp.Caleuche = "merriman";
			pchar.quest.caleuche_merriman_cave.win_condition.l1 = "locator";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.location = "Havana_CryptBig2";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.locator_group = "reload";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.locator = "reload2";
			pchar.quest.caleuche_merriman_cave.function = "Caleuche_OpenMerrimanCave";
			pchar.quest.caleuche_merriman_cave1.win_condition.l1 = "location";
			pchar.quest.caleuche_merriman_cave1.win_condition.l1.location = "Havana_CryptDungeon";
			pchar.quest.caleuche_merriman_cave1.function = "Caleuche_InMerrimanCave";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Caleuche_MerrimanCaveOver", 0, 0, 3, false); // таймер
			npchar.quest.caleuche = "true";
			// логово Мерримана
			int n = Findlocation("Havana_CryptDungeon");
			locations[n].id.label = "Merrimancave";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
