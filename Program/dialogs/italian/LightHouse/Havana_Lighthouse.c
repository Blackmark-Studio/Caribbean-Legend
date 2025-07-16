// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Cosa vuoi?","Cosa vorresti sapere?"),"Cosa ti serve, "+GetAddress_Form(NPChar)+"?","È la terza volta che cerchi di chiedermi...","Ne ho abbastanza di te, sparisci!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Scusa, ho cambiato idea.","Non è niente, scuse."),"Ho dimenticato, le mie scuse...","La terza volta è quella buona, eh? Scusami...","Scusa, scusa! Allora me ne vado...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Ascolta - è passato di qui un uomo di nome Joachim Merriman? È un signore portoghese di mezza età, con i baffi, una barba imperiale e gli occhi penetranti? Forse è sbarcato in una caletta o vicino al faro? Hai visto qualcuno del genere?";
				link.l1.go = "merriman";
			}
		break;
		
		// калеуче
		case "merriman":
			dialog.text = "No, amico, non ho visto nessuno come lui. Me ne sarei accorto, eh.";
			link.l1 = "Capisco, che peccato. Grazie per il tuo tempo, continuerò la mia ricerca allora.";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
