// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakiego rodzaju pytania?","Czego chcesz, "+GetAddress_Form(NPChar)+"?"),"Znów pytania, "+GetAddress_Form(NPChar)+"...","Pytania, pytania... A może po prostu się wymienimy, "+GetAddress_Form(NPChar)+"co?","Słuchaj, jak długo zamierzasz gadać?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Nie mam pytań na razie...","Przepraszam, nie mam teraz nic do powiedzenia..."),"Jeszcze raz, przepraszam...","Może rzeczywiście nadszedł czas na handel...","Przepraszam, handlujmy...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
