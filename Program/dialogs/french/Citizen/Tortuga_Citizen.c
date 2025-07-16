// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Quel genre de questions ?","Que voulez-vous ?");
			link.l1 = RandPhraseSimple("J'ai changé d'avis.","Je n'ai rien à dire maintenant.");
		    link.l1.go = "exit";
			
			// Rebbebion, "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && npchar.sex == "man")
			{
				link.l1 = "Vous ne connaîtriez pas un certain Joep van der Vink, par hasard ?";
				link.l1.go = "PZ1";
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
		
		case "PZ1":
			dialog.text = "Eh bien, je ne le connais pas personnellement, mais je le vois ici de temps en temps. Pourquoi demandez-vous ?";
			link.l1 = "J'ai été chargé de lui remettre un paquet en mains propres. Mais personne ne veut parler de lui, et je ne sais pas pourquoi. Et vous ? Est-ce un homme mauvais ? J'apprécierais votre opinion sincère.";
			link.l1.go = "PZ2";
		break;
		
		case "PZ2":
			dialog.text = "Encore une fois, nous ne nous connaissons pas personnellement, donc je ne sais presque rien. Mais il a un ami proche en ville, et on les voit souvent ensemble. Allez le voir, il décidera de vous en dire plus ou non. Son copain s'appelle Rober Martene.";
			link.l1 = "Rober Martene, dites-vous... Et qui est-il ? Où puis-je le trouver ?";
			link.l1.go = "PZ3";
		break;
		
		case "PZ3":
			dialog.text = "Différents endroits, mais en ce moment, il est à notre phare, en train de réparer son galion après une terrible tempête. Il s'agit du 'Voltigeur'.";
			link.l1 = "Merci beaucoup ! Vous n'avez pas idée à quel point vous m'avez aidé.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_CreateRobertMartin");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
