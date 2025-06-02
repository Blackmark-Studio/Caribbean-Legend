// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Domande, "+GetAddress_Form(NPChar)+"?","Come posso aiutarti, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("Ehm, qual è la grande idea, "+GetAddress_Form(NPChar)+"? ","Di nuovo con le strane domande? Bella, vai a bere un po' di rum o qualcosa del genere...")+"","Durante tutto il giorno, questa è la terza volta che parli di qualche domanda..."+GetSexPhrase("Questi sono alcuni segni di attenzione?","")+"","Altre domande, presumo, "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mi sono ricreduto","Non ho nulla di cui parlare al momento."),"No, no bella...","Assolutamente no, cara...","No, quali domande?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
