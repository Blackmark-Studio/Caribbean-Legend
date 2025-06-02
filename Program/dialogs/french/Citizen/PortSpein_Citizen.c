// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Quel genre de questions ?","Que voulez-vous ?");
			link.l1 = RandPhraseSimple("J'ai changé d'avis.","Je n'ai rien à dire maintenant.");
		    link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Dites-moi, le nom 'Juan' vous dit-il quelque chose ?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Écoutez camarade, une frégate sous le commandement de Miguel Dichoso s'est amarrée au port ici, en avril 1654. Il a disparu ce jour-là. Écoutez camarade, une frégate sous le commandement de Miguel Dichoso s'est amarrée au port ici, en avril 1654. Il a disparu ce jour-là. Vous souvenez-vous de quelque chose à ce sujet ?";
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
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Vous vous moquez de moi ? Il y a deux fois une douzaine de Juans dans chaque colonie !";
			link.l1 = "Je vois. Je m'excuse de vous avoir dérangé...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Allons, capitaine ! Pensez-vous que je me souvienne de telles choses ?","Pardonnez-moi Señor, je ne peux pas vous aider pour cela.","Señor, pensez-vous vraiment que je me souvienne de telles bêtises ? J'ai déjà assez de problèmes.");
			link.l1 = LinkRandPhrase("Je vois. Je m'excuse de vous avoir dérangé...","Quel dommage, Adieu.","D'accord, adieu...");
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
