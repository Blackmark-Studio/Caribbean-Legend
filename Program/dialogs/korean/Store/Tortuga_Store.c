// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있으십니까?","무엇을 도와드릴까요?"),"얼마 전 나에게 무언가 물어보려 했었지...","토르투가 상점에서 그런 질문을 한 사람은 정말 오랜만이오...","질문, 또 질문, 그리고 또 질문이군...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없소."),"음, 내 기억이 다 어디로 갔지...","좋아, 오랜만이군.","질문이 또 있군...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga2")
			{
				link.l1 = "이봐, 가이우스 마르셰를 찾아야 해. 그가 사략 활동에 관여하고 있고, 스페인에서 훌륭한 갤리온을 빼앗은 뒤로 협상가로 이름을 날리고 있다고 들었어. 혹시 그가 무역을 위해 자네에게서 상품을 산 적이 있나?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "가이우스 마르셰? 아, 물론 기억하지요! 하지만 그는 아무것도 사지 않았소. 대신 자신의 배로 화물을 운송하겠다고 제안했지. 마침 넓은 적창이 있는 배가 필요했거든. 원피 대량이었소.";
			link.l1 = "하역 지점은 어디였소?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "필립스버그, 세인트마틴.";
			link.l1 = "좋아요. 감사합니다, 정말 큰 도움이 되었어요!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "언제든지 오십시오, 선장님. 원하실 때 제 가게에 들르시지요!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "10");
			pchar.questTemp.Guardoftruth = "maarten";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
