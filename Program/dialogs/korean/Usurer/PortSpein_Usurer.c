// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있으십니까?","무엇을 도와드릴까요?"),"얼마 전에 그 질문을 나에게 하려고 했었지...","그래, 맞춰볼까... 또 빙빙 돌고 있는 거지?","이봐, 여기서 재정은 내가 맡고 있어, 질문에는 답하지 않아...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없소."),"음, 내 기억이 다 어디로 갔지...","맞췄군, 미안하네...","알겠습니다...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "이봐, 'Juan'이라는 이름이 너한테 의미가 있나?";
				link.l1.go = "Consumption";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "모르겠소. 그리고 알고 싶지도 않소. 자네가 알아보는 것도 권하지 않겠네. 이제, 미안하지만 나는 다시 돌아가야 할 일이 있소. 자네도 아마 처리해야 할 일이 있을 테지? 그러니 가서 할 일이나 하시오.";
			link.l1 = "좋아, 알겠어. 귀찮게 해서 미안해...";
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
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
