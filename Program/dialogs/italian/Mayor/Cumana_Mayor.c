// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Cosa vuoi? Chiedi pure.","Sto ascoltando, qual è la domanda?"),"Questa è la seconda volta che provi a chiedere...","Questa è la terza volta che provi a chiedere...","Quando finirà tutto questo?! Sono un uomo impegnato, lavoro sugli affari della colonia e tu continui a darmi fastidio!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea, mi dispiace.","Non ora. Posto e tempo sbagliati."),"È vero, non ho nulla da dire ora, mi dispiace.","Chiederò, dopo.","Mi dispiace, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("Hai già preso tutto. Cosa vuoi ancora?","C'è qualcosa che non hai preso?");
            link.l1 = RandPhraseSimple("Solo dando un'occhiata in giro...","Solo un controllo, potrei aver dimenticato di prendere qualcosa...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
