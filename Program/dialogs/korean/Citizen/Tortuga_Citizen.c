// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("무슨 질문인데?","뭐 원하는 거야?");
			link.l1 = RandPhraseSimple("내 마음이 바뀌었어.'","지금은 할 말 없어.");
		    link.l1.go = "exit";
			
			// Rebbebion, "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && npchar.sex == "man")
			{
				link.l1 = "혹시 Joep van der Vink이라는 사람을 아는 건 아니겠지?";
				link.l1.go = "PZ_1";
			}
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "내가 그 비밀 정보국에서 일한다고 생각하나 "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "음... 아니. 그럼 이만.";
			link.l1.go = "exit";
			link.l2 = "그럼, 다른 질문 있나?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "내가 수사국처럼 보여? 몰라, 아무것도 모른다니까.";

            link.l1 = "너 정말 덜렁이구나! 썩 꺼져.";
			link.l1.go = "exit";
			link.l2 = "다른 질문 있나?";
			link.l2.go = "new question";
		break;
		
		case "PZ_1":
			dialog.text = "글쎄, 내가 그 사람을 직접 알지는 않지만, 가끔 여기서 보긴 해. 왜 물어보는 거지?";
			link.l1 = "나는 그에게 직접 소포를 전달하라는 임무를 받았어. 그런데 아무도 그 사람에 대해 말하려 하지 않더라고, 왜 그런지 모르겠어. 너는 알아? 그 사람이 나쁜 놈이야? 솔직한 의견을 듣고 싶어.";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_2":
			dialog.text = "또, 우리 서로 개인적으로 아는 사이가 아니라서 나는 거의 아는 게 없어. 하지만 그 사람은 이 마을에 아주 가까운 친구가 있는데, 둘이 자주 같이 다니는 걸 봤지. 그 친구에게 가 봐 – 더 말해줄지 말지는 그가 결정할 거야. 그 친구 이름은 로베르 마르텐이야.";
			link.l1 = "로베르 마르텐이라고? 그게 누구지? 어디서 찾을 수 있지?";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "여러 곳을 돌아다니지만, 지금은 우리 등대에 있어. 끔찍한 폭풍을 맞고 갈레온을 수리 중이지. 이름은 '볼티지르'야.";
			link.l1 = "정말 고마워! 네가 얼마나 큰 도움을 줬는지 모를 거야.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_CreateRobertMartin");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
