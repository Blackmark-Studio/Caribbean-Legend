// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문인데, "+GetSexPhrase("아들아","내 딸")+"?","물어봐, 듣고 있으니까..."),"듣고 있다, 이제 말해라. "+GetSexPhrase("아들아","내 딸")+"...","세 번째로, "+GetSexPhrase("아들아","내 딸")+", 필요한 것이 있으면 말하시오.","성직자는 할 일이 많소, 그런데 자네가 나를 방해하고 있군. "+GetSexPhrase("아들아","내 딸")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 아니오, 신부님..."),"드릴 말씀이 없습니다, 사과드립니다.","나중에 여쭤보겠소. 용서하시오, 신부님.","실례합니다, 신부님...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "말씀해 주십시오, 신부님, '후안'이라는 이름이 익숙하신가요?";
				link.l1.go = "Consumption";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "그렇다, 아들아. 이 마을에는 후안이라는 이름을 가진 신자들이 많다.";
			link.l1 = "알겠습니다. 폐를 끼쳐 죄송합니다, 신부님...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
