// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Cosa vuoi? Chiedi pure.","Sto ascoltando, qual è la domanda?"),"Questa è la seconda volta che stai cercando di chiedere...","Questa è la terza volta che provi a chiedere...","Quando finirà tutto questo?! Sono un uomo impegnato, lavoro su questioni coloniali e tu continui a infastidirmi!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea, mi dispiace.","Non ora. Luogo e tempo sbagliati."),"È vero, non ho nulla da dire ora, mi dispiace.","Chiederò, più tardi.","Mi dispiace, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Vostra Eccellenza, c'era una fregata sotto il comando di Miguel Dichoso nell'aprile 1654. Da allora è sparito. Vi ricordate qualcosa di lui? Forse vi ha fatto visita, ha avuto una conversazione...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Sì, ricordo quell'uomo. Ma non ricordo dettagli su di lui. È venuto qui e poi se n'è andato. Non posso aiutarti.";
			link.l1 = "Capisco. Mi scuso per il disturbo.";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
