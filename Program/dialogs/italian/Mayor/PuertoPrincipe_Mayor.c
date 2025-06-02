// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Cosa vuoi? Chiedi pure.","Sto ascoltando, qual è la domanda?"),"Questa è la seconda volta che provi a chiedere...","Questa è la terza volta che cerchi di chiedere...","Quando finirà tutto questo?! Sono un uomo occupato, lavoro su questioni della colonia e tu continui a disturbarmi!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mi sono ricreduto, mi dispiace.","Non ora. Luogo e tempo sbagliati."),"Vero, non ho nulla da dire ora, mi dispiace.","Chiederò, più tardi.","Mi dispiace, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
