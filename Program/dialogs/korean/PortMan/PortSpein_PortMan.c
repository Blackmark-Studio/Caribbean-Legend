// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문인데?","무슨 일이오, "+GetAddress_Form(NPChar)+"?"),"이미 나에게 질문을 하려고 했잖아 "+GetAddress_Form(NPChar)+"...","오늘만 벌써 세 번째로 그 질문을 꺼냈군...","봐라, 항구 일에 대해 할 말이 없으면 쓸데없는 질문으로 나를 귀찮게 하지 마라.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었소.","나한테 할 말 없어."),"신경 쓰지 마.","정말, 벌써 세 번째군...","미안하지만, 지금은 항구 일에 관심 없어.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "말해 보시오, 'Juan'이라는 이름이 당신에게 의미가 있소?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "나리, 1654년 4월에 미겔 디초소가 지휘하는 프리깃함이 이곳에 있었습니다. 그때 그는 사라졌지요. 혹시 기억나는 게 없습니까? 아마 디초소가 여기 와서 자신의 배를 등록했을 수도 있지요...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "후안? 그게 다요? 나리, 지금 취하셨소 아니면 나한테 바보 같은 장난을 치는 거요? 성씨나 적어도 그 자의 배 이름이라도 기억나오? 여기는 스페인 식민지요, 제발 좀. 여기서 돌아다니는 후안이 몇 명이나 되는지 아시오? 아무런 정보도 없으면 도와줄 수 없소.";
			link.l1 = "알겠소. 귀찮게 해서 미안하오...";
			link.l1.go = "exit";
			pchar.questTemp.Consumption.AskJuan = sti(pchar.questTemp.Consumption.AskJuan)+1;
			if(sti(pchar.questTemp.Consumption.AskJuan) == 3)
			{
				pchar.quest.Consumption2.win_condition.l1 = "location";
				pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
				pchar.quest.Consumption2.function = "Consumption_CreateSergio";
			}
			npchar.quest.Consumption = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "내 기록을 좀 볼까... 아하! 맞아, 미겔 디초소 선장이 1654년 4월에 여기 왔었지, 프리깃 '산타-키테리아'를 타고 말이야. 산-안드레스, 프로비던스 식민지 출신으로 등록했어. 카디스, 스페인으로 향한다고 했지. 1654년 4월 14일에 출항했어. 내가 가진 정보는 이게 전부야.";
			link.l1 = "유럽으로 항해한다고? 알겠소. 고맙소!";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
			AddQuestRecord("Guardoftruth", "39");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
