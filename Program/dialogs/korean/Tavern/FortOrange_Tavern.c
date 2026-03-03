// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있소?","무엇을 도와드릴까요, "+GetAddress_Form(NPChar)+"?"),"얼마 전에 나한테 뭔가 물어보려고 했지, "+GetAddress_Form(NPChar)+"...","오늘 하루 동안만 벌써 세 번째로 그 질문을 꺼내는군...","질문이 더 있나 보군?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없어."),"으음, 내 기억이 다 어디로 갔지...","그래, 진짜로 이번이 세 번째야...","아니, 무슨 질문이야?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "프랑수아 곤티에라는 남자가 이 마을에 들른 적 있나? 내가 정말 그 사람을 찾아야 해.";
                link.l1.go = "Jamaica_ratF_1";
            }
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_4")
            {
                link.l1 = "이봐 친구, 포트 로얄에서 온 배가 조선소용 비단을 좀 사고 있다더군... 아주 특별한 비단이라 들었을 텐데. 그런 비단을 파는 자가 이 정착지 어딘가에 머무르고 있다더라. 그 자를 어떻게 찾을 수 있을지 단서라도 있나? 내가 그 사람에게 할 사업 제안이 있거든.";
                link.l1.go = "mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_5" && (PCharDublonsTotal() >= 50))
            {
                link.l1 = "나한테 두블론 50개 있다. 받아서 말해 봐.";
                link.l1.go = "mtraxx_4_1";
			}
		break;

		case "Jamaica_ratF_1":
			dialog.text = "그랬지. 며칠 동안 방을 빌리고 있었어. 그렇게 유쾌한 녀석은 아니었지, 내가 말해두겠네. 게다가 누가 자기를 찾는다고 집착적으로 두려워했어. 항상 겁에 질려서 주위를 두리번거렸지. 혹시 그가 그렇게 두려워하던 사람이 자네인가?";
			link.l1 = "아니, 나 아니야. 알다시피, 사략선들은 적이 많지. 그런데, 그를 어디서 찾을 수 있지? 나랑 그가 합의를 보기로 했는데, 마치 땅이 그를 삼켜버린 것 같아.";
			link.l1.go = "Jamaica_ratF_2";
		break;
		
		case "Jamaica_ratF_2":
			dialog.text = "자기 배를 타고 바다로 떠났어. 어디로 갔는지는 나도 몰라. 그 부분은 나한테 말 안 해줬거든.";
			link.l1 = "아, 안타깝군! 이제 어디서 그를 찾아야 하지?";
			link.l1.go = "Jamaica_ratF_3";
		break;
		
		case "Jamaica_ratF_3":
			dialog.text = "모르겠어, 친구. 알았다면 말해줬지.";
			link.l1 = "알겠어. 다른 사람한테 가서 물어볼게...";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_4");
			pchar.questTemp.Slavetrader = "FindRatJamaica_H";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
            dialog.text = "흥, 우리 상인, 가게를 지키는 그 사람을 의심한다면 내가 말해주지. 그 사람은 아니야, 비단 돛천 같은 건 취급하지 않아. 밀수꾼들도 여기엔 안 와, 세관이 없으니 올 필요도 없지. 게다가 여기서 거래하는 건 우리 상인 말고는 아무도 없어. 둘러봐, 우린 그런 부류가 아니야, 하하!\n";
			link.l1 = "하지만 누군가가 포트 로열에 비단을 공급하고 있어 - 그건 부정할 수 없는 사실이지. 공급자가 누군지 짐작가는 사람이라도 있나?";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "포트 로얄에서 온 밀수꾼들일지도? 아니면 떠돌이 해적들인가? 분명 어딘가 숨겨진 만에서 전리품을 내리고 있겠지... 하! 친구, 내게 생각이 있네. 이 바다에서 벌어지는 일은 다 아는 동네 사람이 하나 있어. 그가 의심하지 않는다면, 비단 상인 따위는 없는 거야.";
			link.l1 = "훌륭하군! 그 녀석 이름이 뭐지?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "흠... 이름이 생각나려고 하는데, 이상하게도 도무지 떠오르질 않는군...";
			link.l1 = "기억을 돕기 위해 동전 몇 개 어때?";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "그게 도움이 될지도 모르지... 금화 50더블룬이면 이 늙은 머리가 분명히 밝아질 거야.";
			if (PCharDublonsTotal() >= 50) // Rebbebion, учёт количества дублонов из рундука
			{
				link.l1 = "알겠소. 자, 이 동전들을 가져가시오.";
				link.l1.go = "mtraxx_4_1";
			}
			else
			{
				link.l1 = "알겠어. 곧 돌아올게...";
				link.l1.go = "mtraxx_4_2";
			}
		break;
		
		case "mtraxx_4_1":
			RemoveDublonsFromPCharTotal(50);
			PlaySound("interface\important_item.wav");
            dialog.text = "허스키 빌리가 바로 네가 찾는 사람이야. 자메이카에서 오래 살아서 거리의 개 한 마리까지 다 알지. 예전엔 해적이었고 영국놈들 엉덩이에 가시 같은 존재였는데, 한 3년 전쯤 다친 뒤로는 주로 낚시하고 상어 사냥하고 자메이카 만에서 호박을 줍고 다녀. 오래된 롱보트를 떠나는 건 럼주랑 크래커를 더 사러 갈 때뿐이지\n자메이카 근처 바다에서 그를 찾아봐. 북쪽에서 동쪽 끝까지 항해한다는 소문이 있어. 하지만 롱보트 쫓는 건 바보 짓이야; 남서쪽 구석에서 잠복하는 게 낫지—일주일에 한 번쯤 네그릴 곶 근처에서 목격됐다고들 하거든. 그의 작은 배 이름은 '플라이 피쉬'야.";
			link.l1 = "고맙다, 친구. 네 금은 네가 벌었지.";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
            dialog.text = "행운을 빌어, 친구! 찾고 있는 걸 꼭 찾길 바란다!";
			link.l1 = "...";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_4_2":
            DialogExit();
			AddQuestRecord("Roger_2", "6");
			pchar.questTemp.Mtraxx = "silk_5";
		break;
		
		case "mtraxx_6":
            DialogExit();
			AddQuestRecord("Roger_2", "7");
			pchar.questTemp.Mtraxx = "silk_6";
			/*pchar.quest.mtr_negril.win_condition.l1 = "Timer";
			pchar.quest.mtr_negril.win_condition.l1.date.hour  = 12+rand(12);
			pchar.quest.mtr_negril.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2+rand(3));
			pchar.quest.mtr_negril.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2+rand(3));
			pchar.quest.mtr_negril.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2+rand(3));*/
			PChar.quest.mtr_negril.win_condition.l1 = "ExitFromLocation";
			PChar.quest.mtr_negril.win_condition.l1.location = PChar.location;
			pchar.quest.mtr_negril.function = "Mtraxx_CreateBilly";
			SetFunctionTimerCondition("Mtraxx_BillySeaTimeOver", 0, 0, 7, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
