// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문인데?","무슨 일이오, "+GetAddress_Form(NPChar)+"?"),"이미 나에게 질문을 하려고 했잖아 "+GetAddress_Form(NPChar)+"...","오늘만 세 번째로 이 질문을 하셨군요...","이봐, 항구 일에 대해 할 말이 없으면 쓸데없는 질문으로 귀찮게 하지 마라.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었소.","나한테 할 말 없어."),"신경 쓰지 마시오.","정말, 벌써 세 번째군...","미안하지만, 지금은 항구 일에 관심 없어.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "maarten1")
			{
				link.l1 = "프랑스 국기 아래 'Admirable'이라는 갤리온을 찾고 있습니다. 선장 이름은 가이우스 마르셰였지요. 그가 다음에 어디로 항해했는지 알 수 있을까요? 혹시 이곳에 입항 등록을 했는지도요?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "흠, '어드미러블'? 갤리온 말인가? 기억나지. 어디 보자... 우리가 그 배를 바베이도스의 브리지타운으로 파프리카를 운송하라고 임대했었지. 무슨 일이라도 있었나?";
			link.l1 = "아니오, 하지만 가이우스는 내 친구라서 그를 만나는 것이 기대돼.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "그럼 바베이도스로 항해하시오. 하지만 그를 거기서 찾을 수 있을지 의문이오, 오래전 일이니까. 최소한 현지 항만 관리자에게 도움을 청할 수는 있을 것이오.";
			link.l1 = "또 다시 가야겠군.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "12");
			pchar.questTemp.Guardoftruth = "barbados";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
