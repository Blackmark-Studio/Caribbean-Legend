// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Welche Fragen haben Sie für einen Soldaten?","Der Soldat hat sein ganzes Leben geplant - Wache halten, schuften... Wie kann ich Ihnen helfen, "+GetAddress_Form(NPChar)+""),"Sie sollten einen Soldaten nicht mit dummen Fragen belästigen, "+GetAddress_Form(NPChar)+"...","Das ist das dritte Mal heute, dass du versuchst, mir eine Frage zu stellen...","Das Schicksal eines Soldaten ist nicht leicht, und jetzt treibst du, Abschaum, mich in den Wahnsinn...","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert...","Ich habe im Moment nichts zu besprechen."),"Habs verstanden...","Ja, du hast recht, schon das dritte Mal...","Entschuldigung...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
