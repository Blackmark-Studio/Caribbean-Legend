// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Quel genre de questions ?","Que voulez-vous ?");
			link.l1 = RandPhraseSimple("J'ai changé d'avis.","Je n'ai rien à dire maintenant.");
		    link.l1.go = "exit";
			// Rebbebion, квест "Путеводная звезда" ==>
			if (CheckAttribute(pchar, "questTemp.Beliz.AskForLatterAndSotta") && !CheckAttribute(npchar, "questTemp.Sotta") && !CheckAttribute(npchar, "questTemp.Lutter"))
			{
				if (rand(1) == 0)
				{
					link.l1 = "Avez-vous, par hasard, croisé le capitaine Edgardo Sotta ? Pouvez-vous nous parler de lui ? Il semble être un homme à connaître.";
					link.l1.go = "Sotta1";
					link.l2 = "N'allez vous pas voir l'exécution du Moulin à paroles ?";
					link.l2.go = "Lutter1";
				}
				else
				{
					link.l1 = "Dites moi, avez vous vu le héros du jour, Capitaine Edgardo Sotta ? Je l'ai manqué, malheureusement. Comment est-il ? Je ne peux pas croire qu'un marchand ait attrapé l'infâme Matt le Moulin à paroles !";
					link.l1.go = "Sotta1_1";
					link.l2 = "Je vois que toute la ville fête la capture de Lutter, même ceux qui ne prennent jamais la mer."
					link.l2.go ="Lutter1_1";
				}
			}
			// <== квест "Путеводная звезда"
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
		
		// Квест "Путеводная звезда" ==>
		case "Sotta1":
			dialog.text = "Je n'ai pas eu l'occasion de lui parler, mais j'ai vu son navire - un galion lourd. C'est dangereux de naviguer seul dans ces eaux, mais Sotta le fait sans escorte.";
			link.l1 = "Probablement à la recherche de la moindre pièce d'or et en réduisant les coûts partout où il le peut. Eh bien, je ne vais pas vous retenir. Bonne journée.";
			link.l1.go = "Exit";
			
			npchar.questTemp.Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Sotta1_1":
			dialog.text = "Oui, c'est difficile à croire ! Mais ne vous fiez pas à tout ce que vous entendez, monsieur. Je l'ai vu, aussi clairement que je vous vois maintenant. C'est bien qu'il ait attrapé Lutter, mais pourquoi toute cette comédie marchande ? Il se comporte comme un soldat. Je peux toujours le dire - un de mes proches a servi pendant des années.";
			link.l1 = "Intéressant. Eh bien, chacun a ses secrets. Je ferais mieux d'y aller. Merci pour l'éclaircissement.";
			link.l1.go = "Exit";
			
			npchar.questTemp.Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1":
			dialog.text = "J'ai déjà vu cet homme. Il est difficile de croire qu'il s'agit du même pirate qui a terrorisé nos marchands pendant des années. Comment a-t-il pu obtenir son propre commandement en premier lieu ? J'ai vu les soldats l'escorter - criant, pleurant, riant. Un fou.";
			link.l1 = "Peut-être que la défaite et la réalité de sa mort imminente ont été trop fortes pour lui. Mais peu importe. Au revoir !";
			link.l1.go = "Exit";
			
			npchar.questTemp.Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1_1":
			dialog.text = "Oui, et je fête ça aussi - bon nombre de mes compatriotes sont morts de ses mains. Les malchanceux ont perdu un père, un frère, un fils - vous voyez le tableau. Cette barbarie a duré trop longtemps ! Matt devait être l'un des pirates les plus chanceux de ces dernières années, si vous voulez mon avis.";
			link.l1 = "La chance finit toujours par tourner. À la prochaine.";
			link.l1.go = "Exit";
			
			npchar.questTemp.Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		// <== Квест "Путеводная звезда"
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
