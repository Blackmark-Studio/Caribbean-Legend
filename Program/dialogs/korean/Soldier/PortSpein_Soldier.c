// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("병사에게 무슨 질문이 있소?","병사는 평생 계획이 정해져 있지 - 경비 서고, 이리저리 뛰고... 내가 뭘 도와주면 되나, "+GetAddress_Form(NPChar)+"?"),"군인한테 쓸데없는 질문으로 귀찮게 하지 마라, "+GetAddress_Form(NPChar)+"...","오늘만 벌써 세 번째로 나한테 질문하려고 하는군...","군인의 운명도 쉽지 않은데, 이제 너희 같은 놈들이 나를 미치게 만드는구나...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없어."),"알겠어...","그래, 네 말이 맞아, 벌써 세 번째야...","미안...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "말해 봐, 후안이라는 이름이 너한테 의미가 있나?";
				link.l1.go = "Consumption";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "아니. 그게 다야?";
			link.l1 = "그래. 귀찮게 해서 미안하네, 병사...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
