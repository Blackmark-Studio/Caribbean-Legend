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
			if (CheckAttribute(pchar, "questTemp.PZ_Beliz.AskForLatterAndSotta") && !CheckAttribute(npchar, "questTemp.PZ_Sotta") && !CheckAttribute(npchar, "questTemp.PZ_Lutter"))
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
			//--> Дикая Роза
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "Il y a environ un mois et demi, un certain Jérôme Sauvernier est arrivé à Belize. Il a été blessé lors d’une rixe à la 'Œil de Verre', mais il a survécu. Pourriez-vous me dire où je pourrais le trouver ?";
				link.l1.go = "WildRose_Beliz_Citizen_1";
			}
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_2") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "Il y a environ un mois et demi, un certain gentleman est apparu à Belize. Il s’appelait Jérôme Sauvernier. Il cherchait quelqu’un — donc il a dû parler avec les habitants. Plus tard, il a été blessé dans une bagarre de taverne, mais il a eu la chance de survivre. Pourriez-vous me dire où je pourrais le trouver ?";
				link.l1.go = "WildRose_Beliz_Citizen_2";
			}
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_3") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "Je cherche un homme arrivé à Belize il y a environ deux mois. Il s’appelle Jérôme Sauvernier. Il cherchait un certain monsieur, et je suppose qu’il en a parlé aux gens du coin...";
				link.l1.go = "WildRose_Beliz_Citizen_3";
			}
			//<-- Дикая Роза
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
			
			npchar.questTemp.PZ_Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Sotta1_1":
			dialog.text = "Oui, c'est difficile à croire ! Mais ne vous fiez pas à tout ce que vous entendez, monsieur. Je l'ai vu, aussi clairement que je vous vois maintenant. C'est bien qu'il ait attrapé Lutter, mais pourquoi toute cette comédie marchande ? Il se comporte comme un soldat. Je peux toujours le dire - un de mes proches a servi pendant des années.";
			link.l1 = "Intéressant. Eh bien, chacun a ses secrets. Je ferais mieux d'y aller. Merci pour l'éclaircissement.";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1":
			dialog.text = "J'ai déjà vu cet homme. Il est difficile de croire qu'il s'agit du même pirate qui a terrorisé nos marchands pendant des années. Comment a-t-il pu obtenir son propre commandement en premier lieu ? J'ai vu les soldats l'escorter - criant, pleurant, riant. Un fou.";
			link.l1 = "Peut-être que la défaite et la réalité de sa mort imminente ont été trop fortes pour lui. Mais peu importe. Au revoir !";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1_1":
			dialog.text = "Oui, et je fête ça aussi - bon nombre de mes compatriotes sont morts de ses mains. Les malchanceux ont perdu un père, un frère, un fils - vous voyez le tableau. Cette barbarie a duré trop longtemps ! Matt devait être l'un des pirates les plus chanceux de ces dernières années, si vous voulez mon avis.";
			link.l1 = "La chance finit toujours par tourner. À la prochaine.";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		// <== Квест "Путеводная звезда"
		//--> Дикая Роза
		case "WildRose_Beliz_Citizen_1":
    		dialog.text = "Je ne connais pas cet homme, monsieur. Les bagarres à la taverne, c’est presque quotidien ici, alors se souvenir de chaque blessé... ce n’est pas évident.";
    		link.l1 = "Je vois, merci. Bonne journée.";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen");
			pchar.questTemp.WildRose_Beliz_Citizen_2 = true;
			npchar.quest.WildRose_Vopros;
 		break;

		case "WildRose_Beliz_Citizen_2":
    		dialog.text = "Sauvernier ? Un Français... Oui, bien sûr. Il m’a abordé, mais je n’avais rien pour l’aider. Je ne l’ai plus revu depuis, désolé.";
    		link.l1 = "Merci. Dans ce cas, je vais continuer mes recherches.";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_2");
			pchar.questTemp.WildRose_Beliz_Citizen_3 = true;
			npchar.quest.WildRose_Vopros;
 		break;

		case "WildRose_Beliz_Citizen_3":
			dialog.text = "Monsieur Jérôme ! Bien sûr que je m’en souviens. Il a été blessé lors d’une bagarre à la taverne. Depuis, il ne sort presque plus de chez lui — il soigne une blessure à la jambe.";
			link.l1 = "Et où se trouve sa maison ?";
    		link.l1.go = "WildRose_Beliz_Citizen_3_1";
 		break;

		case "WildRose_Beliz_Citizen_3_1":
    		dialog.text = "C’est juste ici, tout près, à côté de l’administration portuaire. Une maison au toit rouge. Vous le trouverez là.";
    		link.l1 = "Merci, vous m’avez été d’une grande aide ! Passez une excellente journée.";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_3");
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_3_citizen");
 		break;
		//<-- Дикая Роза
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
