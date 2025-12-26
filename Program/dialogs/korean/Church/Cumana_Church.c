// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이오, "+GetSexPhrase("아들아","내 딸")+"?","물어봐, 듣고 있으니까..."),"듣고 있다, 어서 말해라. "+GetSexPhrase("아들아","내 딸")+"...","세 번째로, "+GetSexPhrase("아들아","내 딸")+", 필요한 것이 있으면 말하시오.","성직자는 할 일이 많으니 네가 방해하고 있구나, "+GetSexPhrase("아들아","내 딸")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("생각이 바뀌었어...","지금은 아니오, 신부님..."),"드릴 말씀이 없습니다, 죄송합니다.","나중에 여쭤보겠습니다. 용서하십시오, 신부님.","실례합니다, 신부님...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
