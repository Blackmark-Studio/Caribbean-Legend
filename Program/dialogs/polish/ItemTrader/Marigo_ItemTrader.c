// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie pytania?","Czego chcesz, "+GetAddress_Form(NPChar)+"?"),"Znowu pytania, "+GetAddress_Form(NPChar)+"...","Pytania, pytania... Może byśmy się wymienili, "+GetAddress_Form(NPChar)+"A co?","Słuchaj, jak długo zamierzasz gadać?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Na razie nie ma pytań...","Przepraszam, teraz nie mam nic do powiedzenia..."),"Jeszcze raz, przepraszam...","Może rzeczywiście nadszedł czas na handel...","Przepraszam, handlujmy...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
