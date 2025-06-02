// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie pytania?","Czego chcesz, "+GetAddress_Form(NPChar)+"?"),"Znów pytania, "+GetAddress_Form(NPChar)+"...","Pytania, pytania... A może wymienimy się towarem, "+GetAddress_Form(NPChar)+"co?","Słuchaj, jak długo zamierzasz rozmawiać?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Na razie nie mam pytań...","Przepraszam, nie mam teraz nic do powiedzenia..."),"Jeszcze raz, przepraszam...","Może rzeczywiście nadszedł czas na handel...","Przykro mi, handlujmy...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
