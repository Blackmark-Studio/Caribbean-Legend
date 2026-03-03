// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("무슨 질문인데?","뭘 원하지?");
			link.l1 = RandPhraseSimple("내 마음이 바뀌었어.'","지금은 할 말이 없어.");
		    link.l1.go = "exit";
		break;
		
		case "info":
			dialog.text = LinkRandPhrase("누구에 대해 궁금한가?","누구를 말하는 거지?","그래, 누구냐?");
			link.l1 = "나는 모스크바인 파데이에 대해 더 알고 싶어.";
			link.l1.go = "fadey";
			link.l2 = "아무도 아니야, 신경 쓰지 마.";
			link.l2.go = "new question";
		break;
		
		case "town":
			dialog.text = LinkRandPhrase("어디로 가고 싶어?","뭘 찾고 있지?","정확히 무엇이 필요한가?");
            link.l1 = "파데이의 집이 어디야?";
			link.l1.go = "fadey_house";
			link.l2 = "다른 얘기나 하자...";
			link.l2.go = "new question";
		break;
		
		case "fadey":
			dialog.text = RandPhraseSimple("아, 중요한 인물이야. 이 지역 공장 주인이고 바스테르 상류층과도 친해. 말투가 강하고 술을 정말 좋아하지... 그런데 절대 취하지는 않아.","그 사람은 거물이고 총독의 친구야. 파디는 이 지역 공장 주인이지. 아주 멀리 북쪽 나라에서 왔어... 나라 이름도 난 몰라. 손도 크고, 럼주 한 통을 마셔도 취하지 않는다네.");
			link.l1 = "감사하오.";
			link.l1.go = "exit";
		break;
		
		case "fadey_house":
			dialog.text = RandPhraseSimple("부두에서 곧장 가다 보면 광장에 도착하게 되는데, 왼쪽에 있는 집이 파데이의 저택이야.","총독 관저에서 광장을 지나 부두로 가면, 오른쪽에 있는 집이 파데이의 저택이오.");
			link.l1 = "감사하오.";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
