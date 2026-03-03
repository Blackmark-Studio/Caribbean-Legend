// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있소?","무엇을 도와드릴까요, "+GetAddress_Form(NPChar)+"?"),"얼마 전에 나한테 뭔가 물어보려고 했지, "+GetAddress_Form(NPChar)+"...","오늘 하루 종일, 그 질문을 벌써 세 번째 꺼내는군...","또 질문이 있나 보군?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없어."),"음, 내 기억이 다 어디로 갔지...","그래, 이번이 정말 세 번째야...","아니, 무슨 질문이 있다고?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason Долго и счастливо
			if (CheckAttribute(pchar, "questTemp.LongHappy.Santiago"))
			{
				link.l1 = "프랑스 식민지에서 온 성직자들이 어떤 사절단과 함께 여기 도착했다고 들었어, 뭔가 협상을 하려고 온 건가? 아마 마르티니크에서 그 피비린내 나는 학살 이후에 포로 교환하려는 거겠지?";
				link.l1.go = "LH_tavern";
			}
		break;
		
		// Jason Долго и счастливо
		case "LH_tavern":
			dialog.text = "아니, 나리, 그 이야기는 오래전에 성직자들 없이 끝난 일이오. 보아하니 야자수 아래서 사는 모양이군, 교황 인노첸시오 10세와 마자랭 추기경이 결국 합의했다는 소식도 못 들었으니 말이오. 유럽의 전쟁은 그렇다 쳐도, 모든 그리스도인들은 세상 끝의 이교도 어둠에 맞서 힘을 합쳐야 하지 않겠소. 그리고 그래, 개구리 먹는 놈들이 우리한테 오긴 왔지. 하지만 아무것도 합의된 건 없었소—우리 귀한 손님들은 총독 저택에서 경비 아래 커피나 마시며 자리만 데우고 있지. 벌써 한 달이 다 되어 가오! 사람들은 수군대고, 오래 떠들다가 이제 익숙해졌지—봐, 프랑스 신부가 저녁마다 교회에서 기도회를 여는데, 거의 구경거리라니까, 아하하!\n";
			link.l1 = "흥미롭군! 저 프랑스 놈이나 한번 봐야겠다. 적어도 잔만 멍하니 보는 것보단 재밌으니까.";
			link.l1.go = "LH_tavern_1";
		break;
		
		case "LH_tavern_1":
			DialogExit();
			LongHappy_SantiagoBenua();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
