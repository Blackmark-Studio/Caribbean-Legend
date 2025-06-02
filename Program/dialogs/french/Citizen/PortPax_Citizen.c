// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Quel genre de questions ?","Que voulez-vous ?");
			link.l1 = RandPhraseSimple("J'ai changé d'avis.","Je n'ai rien à dire maintenant.");
		    link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "portprince" && !CheckAttribute(npchar, "quest.Guardoftruth"))
			{
				link.l1 = "Dites-moi, "+GetAddress_FormToNPC(NPChar)+", le galion 'Santa Margarita' était-il ici il y a peu ? Comme prise d'un corsaire peut-être ?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Pensez-vous que je travaille pour le service secret de "+NationNameGenitive(sti(NPChar.nation))+" ?";
			link.l1 = "Eh bien... non. Adieu alors.";
			link.l1.go = "exit";
			link.l2 = "Une autre question, alors ?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Ai-je l'air du bureau d'investigation ? Je ne sais pas, je ne sais rien.";

            link.l1 = "Vous êtes une vraie tête de noeud ! Allez-vous en.";
			link.l1.go = "exit";
			link.l2 = "Une autre question, alors ?";
			link.l2.go = "new question";
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Non, je ne me souviens d'aucun galion avec ce nom. Nous voyons rarement des navires aussi grands ici.","Quoi ? Un galion ? Ici ? Je n'en ai aucune idée.","Non Monsieur, ce navire n'a pas accosté ici dernièrement, du moins je ne me souviens pas que cela soit arrivé.");
			link.l1 = LinkRandPhrase("D'accord...","Très bien...","Je vois, dommage...");
			link.l1.go = "exit";
			npchar.quest.Guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
