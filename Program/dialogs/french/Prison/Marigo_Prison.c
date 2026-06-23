// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Parle, j'écoute";
			link.l1 = "Je me suis trompé. Adieu.";
			link.l1.go = "Exit";
			//искушение барбазона
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison"))
            { 
                link.l1 = "Vous avez Simon Morelle en détention ici. C'est un contrebandier dont la goélette a été coulée par une patrouille il n'y a pas longtemps. Puis-je le voir ?";
                link.l1.go = "BarbTemptation";
				DeleteAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison");
            }
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div")
			{
				link.l1 = "Officier, j'ai été envoyé ici par monsieur le gouverneur de Philipsburg. Il m'a demandé de faire une descente sur l'île et ses eaux à la recherche d'espions anglais. Son Excellence m'a également dit que vous pourriez me fournir des informations utiles.";
				link.l1.go = "FMQN";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div_2")
			{
				link.l1 = "Officier, j'ai retrouvé la patrouille disparue. J'ai aussi découvert les espions britanniques. Ils sont ici sur l'île.";
				link.l1.go = "FMQN_3";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_peace_rew")
			{
				link.l1 = "Encore moi, officier. Avez-vous arrêté les espions ?";
				link.l1.go = "FMQN_8";
			}
		break;
		
		//искушение барбазона
		case "BarbTemptation":
			dialog.text = "Et pourquoi avez-vous besoin de lui, monsieur ?";
			link.l1 = "Je veux lui dire qu'il est un foutu salaud et un vaurien. J'espère que cela l'aidera à tenir sur la potence.";
			link.l1.go = "BarbTemptation_1";
		break;
		
		case "BarbTemptation_1":
			dialog.text = "Ha-ha ! Tu as de l'humour, monsieur... Eh bien, deux mille pesos et tu peux passer ton chemin.";
			if(int(Pchar.money) >= 2000)
			{
				link.l1 = "Prenez-le, officier. Merci !";
				link.l1.go = "BarbTemptation_2";
			}
			link.l2 = "Hm... Vous savez, j'ai changé d'avis. Je ferais mieux de dépenser mon argent à la taverne.";
			link.l2.go = "BarbTemptation_4";
		break;
		
		case "BarbTemptation_2":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "De rien... Circulez !";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "BarbTemptation_4":
			dialog.text = "Comme vous voulez, vous ne recevrez pas une telle proposition la prochaine fois.";
			link.l1 = "Je n'en ai pas besoin de toute façon. À plus tard, officier !";
			link.l1.go = "exit";
		break;
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "Utile? Ha! En y réfléchissant, attendez. J'ai quelque chose d'utile à vous dire. Une de nos patrouilles a disparu dans la jungle. Ils devaient être de retour à la caserne, mais il semble qu'ils préfèrent la compagnie des perroquets. Ou bien il s'est vraiment passé quelque chose. Si vous les trouvez lors de vos recherches, s'il vous plaît, dites-leur de trouver une excuse valable pour leur retard, sinon ils n'aimeront pas les conséquences... Le commandant de la patrouille s'appelle Jannes Hoffman.";
			link.l1 = "Est-ce tout, officier ?";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "Oui, bon sang. Je suis désolé mais je n'ai rien d'autre à te dire. Bonne chance, capitaine.";
			link.l1 = "Merci...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			DialogExit();
			pchar.questTemp.FMQN = "way_div_1";
			AddQuestRecord("FMQ_Nevis", "10");
			FMQN_SetSoldiersInCave();
		break;
		
		case "FMQN_3":
			DelLandQuestMark(npchar);
			dialog.text = "Quoi ?! J'espère que tu ne plaisantes pas ? Fais-moi un rapport !";
			link.l1 = "J'ai rencontré une patrouille près d'une grotte dans la jungle. Ils m'ont arrêté et demandé où j'allais et pourquoi, puis m'ont laissé partir. Que le diable m'emporte, si ce n'étaient pas les Brits déguisés en uniformes hollandais ! J'ai aussi vu quelque chose de curieux dans la jungle qui ressemblait exactement à un groupe d'hommes nus cachés dans les buissons. Je suppose que le groupe de raideurs britanniques avait désarmé votre patrouille et pris leurs uniformes.";
			link.l1.go = "FMQN_4";
		break;
		
		case "FMQN_4":
			dialog.text = "...";
			link.l1 = "Comme vous le comprenez, je n'ai pas pris le risque de me battre contre une escouade de manteaux rouges entraînés et donc je me suis précipité vers vous avec un rapport à la place.";
			link.l1.go = "FMQN_5";
		break;
		
		case "FMQN_5":
			dialog.text = "Eh bien, eh bien... Une grotte, dites-vous ? Combien en avez-vous compté ??";
			link.l1 = "Cinq hommes. Et oui, je pense qu'ils sont entrés dans cette grotte.";
			link.l1.go = "FMQN_6";
		break;
		
		case "FMQN_6":
			dialog.text = "J'envoie immédiatement une escouade à la caverne ! Capitaine, si les hommes que vous avez rencontrés sont vraiment des espions britanniques, vous recevrez une récompense bien méritée. Vous êtes libre de rejoindre l'escouade si vous souhaitez aider les autorités à arrêter ces salauds et recevoir une récompense supplémentaire, ce sont après tout les ordres du gouverneur. Alors, venez-vous avec ?";
			link.l1 = "Non officier, poursuivre les espions est votre travail. Assurez-vous d'envoyer une escouade bien armée, ces crapules sont trop dangereuses...";
			link.l1.go = "FMQN_7";
			link.l2 = "Je pense que je peux faire cela. Vos hommes trouveront les espions plus rapidement avec mon aide.";
			link.l2.go = "FMQN_10";
		break;
		
		case "FMQN_7":
			dialog.text = "Ton choix, capitaine, je tiendrai compte de ton conseil. Viens me voir demain pour connaître les résultats de notre opération.";
			link.l1 = "À demain.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandPeace");
		break;
		
		case "FMQN_8":
			DelLandQuestMark(npchar);
			dialog.text = "Vos informations étaient correctes, capitaine. Nous avons trouvé ces salauds à l'intérieur de la grotte. Ils n'avaient aucune intention de se rendre et ont engagé le combat. En conséquence, nous les avons tous éliminés... Nous avons également retrouvé la patrouille disparue. Ils vont bien et sont vivants, bien que quelque peu amochés... Merci, capitaine, au nom de tous les bons citoyens de Philipsburg. Votre vigilance sera récompensée comme promis. Prenez ceci.";
			link.l1 = "Merci !";
			link.l1.go = "FMQN_9";
		break;
		
		case "FMQN_9":
			AddMoneyToCharacter(pchar, 10000);
			dialog.text = "Vous êtes toujours un invité bienvenu à Sint-Maarten. Maintenant, veuillez m'excuser, j'ai d'autres affaires à régler.";
			link.l1 = "Moi aussi. Adieu.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandPeaceComplete");
		break;
		
		case "FMQN_10":
			dialog.text = "Très bien. Votre aide est des plus appréciées. Allez aux portes de la ville, l'escouade punitive sera rassemblée là-bas dans une heure.";
			link.l1 = "Un petit conseil, vous devriez envoyer les meilleurs soldats que vous avez pour cette mission. Ces espions sont dangereux.";
			link.l1.go = "FMQN_11";
		break;
		
		case "FMQN_11":
			dialog.text = "Ne vous inquiétez pas. J'envoie nos soldats les plus expérimentés sous le commandement d'un officier, Hans Shulte - le maître d'armes de Philipsburg.";
			link.l1 = "Super ! Ne perdons pas de temps alors.";
			link.l1.go = "exit";
			WaitDate("",0,0,0,1,5);
			AddDialogExitQuestFunction("FMQN_HollandBattle");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
