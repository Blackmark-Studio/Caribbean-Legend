// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문인데?","무엇을 원하시오, "+GetAddress_Form(NPChar)+"?"),"또 질문이군, "+GetAddress_Form(NPChar)+"...","질문이 많군... 거래나 하지,  "+GetAddress_Form(NPChar)+"응?","이봐, 얼마나 오래 이야기할 생각이야?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("지금은 질문이 없소...","미안하지만, 지금은 할 말이 없소..."),"다시 한 번, 미안하오...","정말 이제 거래할 때가 된 걸까...","죄송합니다, 거래합시다...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "이봐, 'Juan'이라는 이름 들어본 적 있어?";
				link.l1.go = "Consumption";
			}			
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "아니, 그렇지 않아... 이제 제발 귀찮게 하지 마시오, 나는 지금 꽤 바쁘오... 정말 어이없는 질문이군...";
			link.l1 = "알겠소. 시간 뺏어서 미안하오...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
