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
			if (CheckAttribute(pchar, "questTemp.Saga"))
			{
				link.l1 = "나는 Jan Svenson에 대해 더 알고 싶어.";
				link.l1.go = "svenson";
			}
			link.l2 = "화제를 바꿔보자...";
			link.l2.go = "new question";
		break;
		
		case "town":
			dialog.text = LinkRandPhrase("어디로 가고 싶어?","뭘 찾고 있지?","정확히 무엇이 필요한가?");
			if (CheckAttribute(pchar, "questTemp.Saga"))
			{
				link.l1 = "얀 스벤손의 집이 어디야?";
				link.l1.go = "svenson_house";
			}
			link.l2 = "화제를 바꾸자...";
			link.l2.go = "new question";
		break;
		
		case "svenson":
			dialog.text = RandPhraseSimple("오, 우리 얀 스벤손은 정말 대단한 인물이야. 예전엔 서인도에서 가장 멋진 해적이었고, 지금도 녹슬 기미가 전혀 없어, 하하! 하지만 그 시절은 끝났지, 예전만큼 활발하진 않아. 지금은 대저택을 소유하고 젊은 아내와 함께 살고 있어. 그리고 항상 총독 관저에 환영받는 손님이기도 하지. 얀에게는 손님이 많이 찾아오는데, 대부분 해적들이야.","얀 스벤손은 서인도에서 전설 같은 인물이야! 숲의 악마, 스페인 놈들이 그를 쫓아낼 때 그렇게 불렀지. 한때는 유명한 커세어였지만, 이제는 우리 식민지의 존경받는 시민이야.\n요즘도 가끔 '일'을 벌이긴 하지만, 이제는 직접 나서진 않아. 젊은 미녀와 결혼한 뒤로는 집을 거의 나서지 않거든.");
			link.l1 = "감사하오.";
			link.l1.go = "exit";
		break;
		
		case "svenson_house":
			dialog.text = RandPhraseSimple("부두에서 곧장 가면 광장에 도착할 거야, 분수 근처 오른쪽에 있는 집이 스벤손의 저택이야.","총독 관저에서 광장을 지나 부두로 가면, 분수 근처 왼쪽에 있는 집이 스벤손의 저택이야.");
			link.l1 = "감사하오.";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
