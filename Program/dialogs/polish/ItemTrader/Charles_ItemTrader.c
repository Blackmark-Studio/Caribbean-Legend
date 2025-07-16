// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie to pytania?","Czego chcesz, "+GetAddress_Form(NPChar)+"?"),"Pytania znowu, "+GetAddress_Form(NPChar)+"...","Pytania, pytania... A może jednak pohandlujemy, "+GetAddress_Form(NPChar)+"co?","Słuchaj, jak długo zamierzasz rozmawiać?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Żadnych pytań na razie...","Przepraszam, teraz nie mam nic do powiedzenia..."),"Jeszcze raz, przepraszam...","Może rzeczywiście nadszedł czas, aby handlować...","Przepraszam, handlujmy...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
