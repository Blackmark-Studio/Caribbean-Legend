// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Welche Art von Fragen?","Was willst du, "+GetAddress_Form(NPChar)+"?"),"Du hast schon versucht, mir eine Frage zu stellen "+GetAddress_Form(NPChar)+"...","Sie sprechen heute zum dritten Mal über eine Frage...","Schau, wenn du mir nichts über die Angelegenheiten des Hafens zu berichten hast, dann belästige mich nicht mit deinen Fragen.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert.","Ich habe nichts zu besprechen."),"Macht nichts.","Ja, bereits das dritte Mal...","Entschuldigung, aber ich bin momentan nicht an den Angelegenheiten des Hafens interessiert.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
