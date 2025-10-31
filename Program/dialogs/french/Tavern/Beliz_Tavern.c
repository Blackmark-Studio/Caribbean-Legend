// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Tous les rumeurs de "+GetCityName(npchar.city)+" à votre service. Que souhaitez-vous savoir ?","Nous en parlions justement. Tu as dû oublier...","C'est la troisième fois aujourd'hui que tu me le demandes...","Tu répètes tout comme un perroquet...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tu sais, "+NPChar.name+", peut-être la prochaine fois.","D'accord, j'ai oublié pour une raison quelconque...","Oui, c'est vraiment la troisième fois...","Ouais...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Écoutez, est-ce qu'un alchimiste est arrivé ici dans cette ville, un médecin? Il est italien, environ trente ans, il s'appelle Gino Gvineili?";
				link.l1.go = "guardoftruth";
			}
			// Калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && !CheckAttribute(npchar, "quest.Caleuche"))
			{
				link.l1 = "Écoutez, j'ai besoin d'un chasseur nommé Fergus Hooper. On m'a dit qu'il vit ici. Où puis-je le trouver ?";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
			//--> Дикая Роза
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz"))
			{
				link.l1 = "Il y a environ un mois et demi, un certain Jérôme Sauvergne est arrivé dans votre ville. Ça vous dit quelque chose ?";
				link.l1.go = "WildRose_Tavern_1";
			}
			//<-- Дикая Роза
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Non, je n'ai pas entendu parler de cela. Nous avons des herboristes et des médecins, mais aucun d'eux ne porte un tel nom.","C'est la première fois que j'entends un nom aussi étrange. Non, nous n'avons jamais eu de visite de l'homme dont vous parlez.","Nous n'avons aucun type d'alchimistes. Nous avons des médecins, mais aucun avec un nom comme ça.");
			link.l1 = "Je vois. C'est dommage. Je continuerai à chercher!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
		
		// Калеуче
		case "caleuche":
			dialog.text = "Fergus ? Il fréquente souvent mon établissement. Mais il est dans la selva depuis hier. Ne vous inquiétez pas, il sera de retour dans une semaine, buvant du rhum et se vantant de ses aventures maritimes. Cependant, je l'admets, c'est un sacré bon chasseur. Je ne connais personne qui puisse attraper des serpents aussi bien que lui.";
			link.l1 = "Des serpents ? Hum. Quand devrais-je revenir ici pour le trouver ?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Au moins trois jours. Sachez qu'il vient toujours ici pas avant six heures du soir et part pas plus tard que dix heures.";
			link.l1 = "Comment est-il ? Jamais vu auparavant.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Barbu, d'âge moyen, porte un manteau marron, un chapeau et de longues bottes.";
			link.l1 = "Merci! Tu m'as beaucoup aidé, camarade. À la prochaine!";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "8");
			int iTerms = sti(pchar.questTemp.Caleuche.Belizterms);
			SetFunctionTimerCondition("Caleuche_FergusCome", 0, 0, iTerms, false);
			npchar.quest.Caleuche = "true";
		break;
		
		//--> Дикая Роза
		case "WildRose_Tavern_1":
			dialog.text = "Euh... oui, je crois bien. Oui, je me souviens de ce gentleman. Pas habillé comme un seigneur, mais il avait de l'argent.";
			link.l1 = "Il a été blessé lors d’une bagarre dans votre taverne.";
			link.l1.go = "WildRose_Tavern_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Tavern_2":
			dialog.text = "Et alors ? Des bagarres, y’en a tous les deux jours ici. Les marins s’enivrent, un mot en entraîne un autre — et voilà. Vous avez l’air d’un homme aguerri — ça vous surprend vraiment ?";
			link.l1 = "Pas le moins du monde. Mais cet homme est une vieille connaissance. On devait se retrouver ici, mais j’ai eu du retard. Vous sauriez où je peux le trouver ?";
			link.l1.go = "WildRose_Tavern_3";
		break;

		case "WildRose_Tavern_3":
			dialog.text = "Pourquoi pas, monsieur ? Comme je vous l’ai dit, il avait de quoi payer — alors il a loué une petite maison près de l’administration portuaire. Facile à repérer, avec un toit rouge. Il y reste presque tout le temps, à soigner sa jambe. De temps en temps, il passe ici boire un verre. Mais c’est aléatoire — parfois il vient, parfois non.";
			link.l1 = "Eh bien, j’irai le voir chez lui, alors. Merci pour l’info. Bonne journée.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_3_tavern");
		break;
		//<-- Дикая Роза
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
