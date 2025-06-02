// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakiego rodzaju pytania?","Czego chcesz, "+GetAddress_Form(NPChar)+"?"),"Znowu pytania, "+GetAddress_Form(NPChar)+"...","Pytania, pytania... Może byśmy się wymienili, "+GetAddress_Form(NPChar)+"co?","Słuchaj, jak długo planujesz rozmawiać?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Na razie bez pytań...","Przepraszam, nie mam teraz nic do powiedzenia..."),"Jeszcze raz, przepraszam...","Może faktycznie nadszedł czas na handel...","Przepraszam, handlujmy...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
