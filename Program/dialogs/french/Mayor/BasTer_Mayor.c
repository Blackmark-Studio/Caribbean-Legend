// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que voulez-vous ? Demandez ce que vous voulez.","Je vous écoute, quelle est la question ?"),"C'est la deuxième fois que vous essayez de demander...","C'est la troisième fois que tu essaies encore de demander...","Quand cela va-t-il finir ?! Je suis un homme occupé, travaillant sur les affaires de la colonie et vous essayez encore de demander quelque chose !","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Pas maintenant. Mauvais endroit et moment."),"Vrai... Mais plus tard, pas maintenant...","Je demanderai... Mais un peu plus tard...","Je suis désolé, "+GetAddress_FormToNPC(NPChar)+"... ",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "J'ai une affaire délicate à vous confier. Il n'y a pas longtemps, un corsaire a offert une croix en or ornée de lazurite à la paroisse de Basse-Terre. Le problème est que la croix a été volée à la paroisse de Santiago et qu'un homme d'église a été assassiné lors du vol...";
                link.l1.go = "guardoftruth";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "Je suis arrivé sur ordre du gouverneur général Philippe de Poincy pour prendre le commandement de votre frégate armée.";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < 5)
			{
				link.l1 = "Je suis prêt à intégrer la frégate à l'escadre.";
                link.l1.go = "patria_2";
			}
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "baster")
			{
				link.l1 = "J'ai rendez-vous ici avec une personne...";
                link.l1.go = "baster_goldengirl";
			}
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_guber_1"))
			{
				link.l1 = "Monsieur, je prévois de me lancer dans une activité commerciale en ville. En particulier, je m'intéresse au commerce de spiritueux en gros et de façon régulière.";
				link.l1.go = "TPZ_guber_1";
			}
			//<-- Торговля по закону
		break;
		//************************** Квестовые штрумы ************************
		case "Cupture_after":
            dialog.text = RandPhraseSimple("Tu as déjà tout pris. Que veux-tu d'autre ?","Y a-t-il quelque chose que tu n'as pas encore pris?");
            link.l1 = RandPhraseSimple("Je regarde juste autour...","Je vérifie juste, je pourrais oublier de prendre quelque chose...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		case "guardoftruth":
			dialog.text = "Hm. C'est assez intéressant. Mais pourquoi penses-tu que je me soucie des problèmes des Espagnols ?";
			link.l1 = "Ce n'est pas une affaire espagnole, Monsieur. La religion ne divise pas les gens par nationalité. Il y a un objet couvert du sang du saint serviteur dans votre paroisse et il y a eu une profanation à la paroisse de Santiago...";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "";
			link.l1 = "Je vous demande de faire preuve de justice et d'ordonner à saint père de rendre la croix à ses propriétaires.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Et depuis quand es-tu devenu un croyant si sincère et fervent, hein, "+pchar.name+"Les Espagnols ne sont pas nos amis et je ne vois aucune raison de pousser sur le saint père dans cette affaire. La croix était un cadeau et c'est bien ainsi. Notre prêtre n'a aucun lien avec ce vol et ce meurtre, donc...";
			link.l1 = "Et vous ne pouvez pas m'aider, n'est-ce pas ?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Pour être honnête, "+pchar.name+", je ne ressens pas le besoin de le faire. Je n'ai aucun amour pour ces fanatiques papistes.";
			link.l1 = "Je vois. Désolé de vous déranger, Monsieur...";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			npchar.quest.utensil = "true";
			AddQuestRecord("Guardoftruth", "28");
		break;
		
		// Jason НСО
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "Le navire est prêt, mais vous n'avez pas de place libre pour lui dans votre escadre. Capitaine, réduisez votre escadre et revenez, alors je vous donnerai immédiatement la frégate.";
				link.l1 = "Très bien.";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "Oui, bien sûr, le navire est prêt à prendre la mer. Son capitaine est au courant et suivra toutes vos ordres.";
				link.l1 = "Alors nous partons. Adieu, Votre Grâce.";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "Excellent. Préparez-vous à saluer votre nouveau navire. Son capitaine est au courant et suivra tous vos ordres.";
			link.l1 = "Alors, nous prenons la mer. Adieu, Votre Grâce.";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateGlp(); // присоединяем фрегат
		break;
		
		// Jason Дороже золота
		case "baster_goldengirl":
			dialog.text = "Ah, Monsieur Charles de Maure, parfait timing ! Mon vieil ami est très impatient de vous rencontrer et a demandé à être informé de votre arrivée. S'il vous plaît, venez dans mon salon, je vais prévenir Angerran immédiatement. Comment vous êtes-vous connus, d'ailleurs ?";
			link.l1 = "Nous avons joué ensemble. Il a perdu, nous avons eu une petite bagarre. Je suppose que Monsieur de Chievous aimerait arranger les choses entre nous.";
			link.l1.go = "baster_goldengirl_1";
		break;
		
		case "baster_goldengirl_1":
			dialog.text = "Sans aucun doute ! J'espère que vous arrangerez les choses entre vous deux. Angerran n'est peut-être pas la personne la plus agréable à côtoyer, mais il est intelligent et honorable, tout comme vous. C'est une espèce rare.";
			link.l1 = "Vous me flattez, Excellence. Je l'attendrai dans le salon si cela ne vous dérange pas.";
			link.l1.go = "baster_goldengirl_2";
		break;
		
		case "baster_goldengirl_2":
			dialog.text = "Mais bien sûr, fais comme chez toi, mets-toi à l'aise. Peut-être devras-tu attendre un peu. Je vais ordonner qu'on apporte quelques boissons.";
			link.l1 = "Merci, Excellence, mais je vais décliner. Je vais juste m'asseoir et attendre notre... ami commun.";
			link.l1.go = "baster_goldengirl_3";
		break;
		
		case "baster_goldengirl_3":
			DialogExit();
			pchar.questTemp.GoldenGirl = "baster1";
			DoQuestReloadToLocation("CommonResidence_3", "reload", "reload1", "GoldenGirl_AngerranInResidence");
		break;
		
		//--> Торговля по закону
		case "TPZ_guber_1":
			dialog.text = "Capitaine, vous avez bien fait de venir me voir. Nous luttons activement contre le commerce illégal sur l'île, et je suis toujours heureux d'accueillir des capitaines honnêtes désireux d'agir dans les règles.";
			link.l1 = "Alors, quelles sont les conditions et les étapes nécessaires pour commencer à commercer ?";
			link.l1.go = "TPZ_guber_2";
			DelLandQuestMark(npchar);
		break;

		case "TPZ_guber_2":
			dialog.text = "C'est assez simple. Pour commercer des spiritueux, vous devrez payer une taxe mensuelle de cent doublons au trésor, tenir une comptabilité et soumettre régulièrement des rapports d'activité. Dès que vous aurez versé l'argent, vous pourrez commencer le commerce.";
			link.l1 = "Très bien. Les conditions me semblent tout à fait acceptables. Un résident local nommé Christian Deluce s'occupera de mes affaires ici. J'espère que cela ne posera aucun problème ?";
			link.l1.go = "TPZ_guber_3";
		break;

		case "TPZ_guber_3":
			dialog.text = "Comme vous le souhaitez, capitaine. Mais souvenez-vous : toute la responsabilité de votre protégé vous incombe, et en cas de faute de sa part, vous en subirez également les conséquences.";
			link.l1 = "Évidemment. Merci pour ces précisions, monsieur le gouverneur. Nous allons tout préparer, et Christian s'acquittera de la taxe.";
			link.l1.go = "TPZ_guber_4";
		break;

		case "TPZ_guber_4":
			dialog.text = "Parfait. Je suis ravi de constater une telle rigueur. Bonne chance dans votre entreprise.";
			link.l1 = "Merci. Je suis sûr que notre coopération profitera à la ville. Au revoir.";
			link.l1.go = "TPZ_guber_5";
		break;

		case "TPZ_guber_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.TPZ_guber_1");
			AddQuestRecord("TPZ", "11");

			sld = CharacterFromID("TPZ_Kristian");
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian_21";
			ChangeCharacterAddressGroup(sld, "BasTer_houseF3", "barmen", "stay");
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Торговля по закону
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
