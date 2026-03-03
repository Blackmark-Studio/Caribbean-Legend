// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있소?","무엇을 도와드릴까요, "+GetAddress_Form(NPChar)+"?"),"얼마 전에 나한테 뭔가 물어보려고 했었지, "+GetAddress_Form(NPChar)+"...","오늘 하루 동안, 그 질문을 벌써 세 번째 꺼내는군...",
			"또 질문이 있나?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없어."),"으음, 내 기억이 다 어디로 갔지...","그래, 정말로 이번이 세 번째야...",
			"아니, 무슨 질문이야?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";			
			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "이봐, 프랑수아 곤티에라는 이름의 사략선을 본 적 있나? 최근에 네 마을에 왔다고 하던데.";
                link.l1.go = "Portobello_rat_1";
            }			
			// карибские нравы
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && !CheckAttribute(npchar, "quest.trial"))
            {
                link.l1 = "이봐, 혹시 하이메 실리시오라는 상인을 어디서 찾을 수 있는지 알려줄 수 있겠나? 그가 당신을 만나러 오기로 했었다고 들었는데...";
                link.l1.go = "trial";
            }
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_portobello" && !CheckAttribute(npchar, "quest.FMQG"))
            {
                link.l1 = "이봐, 나 베르트랑 피네트라는 남자를 찾고 있는데, 들어본 적 있어? 얼마 전에 포르토벨로에 도착했어. 곱슬가발을 쓴 위압적인 신사야. 상인이기도 하고. 여기 왔을지도 모르지...";
                link.l1.go = "FMQG";
            }
			//--> Письмо от покойника
			if (CheckAttribute(pchar, "questTemp.LFD_Tavern_1"))
            {
                link.l1 = "마리사 칼데라를 어디서 찾을 수 있는지 말해줄 수 있나?";
                link.l1.go = "LFD_Tavern_1_1";
            }
			//<-- Письмо от покойника
		break;
		
		case "Portobello_rat_1":
			dialog.text = NPCStringReactionRepeat("아니, 나는 몰라. 그가 선술집에 들르지도 않았고, 마을에서도 못 봤어.","그건 이미 물어봤고 내가 대답도 했잖아.","내가 말했잖아, '그 공티에에 대해서는 이미 물어봤다고.'","이봐, 꺼져서 그만 귀찮게 해! 완전히 미쳤냐?","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("그렇다면, 계속 찾아보지.","흠, 그렇겠지...","그래, 맞아, 내가 그렇게 부탁했지...","미안해, "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;		

		case "trial":
			DelLandQuestMark(npchar);
			npchar.quest.trial = true;
			
			dialog.text = "용서하시오, 나리, 하지만 그런 이야기를 낯선 이와 나눌 자는 배신자나 주정뱅이뿐이오. 나는 문제를 일으키고 싶지 않소.";
			link.l1 = "술주정뱅이라고? 곧 보자, 친구.";
			link.l1.go = "exit";
		break;
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "그런 놈은 들어본 적 없어, 친구.";
			link.l1 = "그는 돈 카를로스 데 밀리아르의 지인이야. 정말 그 사람에 대해 들어본 적 없어?";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "그래, 나다. 그가 드 미리야르의 친구라면, 총독에게 가서 카를로스 나리를 찾아봐. 그분이 네 상인에 대해 말해줄 거다.";
			link.l1 = "그러지. 조언 고마워!";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			DialogExit();
			AddQuestRecord("FMQ_Guadeloupe", "9");
			npchar.quest.FMQG = true;
		break;
		
		//--> Письмо от покойника
		case "LFD_Tavern_1_1":
			dialog.text = "마리사? 흠... 한동안 못 봤어. 남편이 죽었다는 소식을 들은 뒤로는 마을에 전혀 나타나지 않더라.";
			link.l1 = "그럼 그녀는 과부란 말이야?";
			link.l1.go = "LFD_Tavern_1_2";
			DelLandQuestMark(npchar);
		break;

		case "LFD_Tavern_1_2":
			dialog.text = "그래. 그녀의 남편은 무역 핀네스 '웨이브리버'의 선장이었지. 네덜란드 서인도 회사의 허가 덕분에 군도 내 거의 모든 항구가 그에게 열려 있었어. 소문에 따르면, 그는 벨리즈에서 캡스터빌로 가던 중 해적의 습격을 살아남지 못했다고 하더군. 이런 일은 이 근방에서 드문 일이 아니지만, 그녀에게는 정말 큰 충격이었지.";
			link.l1 = "그래서 그녀가 그냥 사라졌다는 거야?";
			link.l1.go = "LFD_Tavern_1_3";
		break;

		case "LFD_Tavern_1_3":
			dialog.text = "글쎄, '사라졌다'는 말은 좀 과한 것 같소. 하지만 그 이후로 그녀가 마을에서 거의 보이지 않는 건 사실이오. 이상한 건... 가끔씩 다른 남자들이 그녀에 대해 묻는다는 거요. 선장님처럼 말이오. 만약 그녀가 그렇게 독실하지 않았다면, 난 그녀가 숨어 지내면서 어떻게든 살아가고 있다고 생각했을 거요. 하지만 마리사는 남편이 죽기 전엔 미사를 한 번도 빠진 적이 없었지요 – 거의 교회에서 살다시피 했으니 – 그래서 그럴 리는 없다고 생각하오.";
			link.l1 = "그게 다야? 더 아는 거 없어?";
			link.l1.go = "LFD_Tavern_1_4";
		break;

		case "LFD_Tavern_1_4":
			dialog.text = "내가 아는 건 모두 이미 말씀드렸소, 선장님.";
			link.l1 = "...";
			link.l1.go = "LFD_Tavern_1_5";
		break;

		case "LFD_Tavern_1_5":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Tavern_1");
		break;
		//<-- Письмо от покойника
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}