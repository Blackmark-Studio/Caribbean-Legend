// Адольф Барбье - авантюрист
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && int(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Je ne veux pas te parler. Tu attaques des civils pacifiques sans raison et les provoques à se battre. Déguerpis !";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Bonjour, Bonjour... Je ne vous ai pas vu auparavant. Récemment ?";
				link.l1 = "Vous voulez dire récemment sur l'Île? Oui, vous avez raison. Mon nom est "+GetFullName(pchar)+", un marin et un aventurier.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"Veux-tu quelque chose?";
				link.l1 = LinkRandPhrase("As-tu quelque chose d'intéressant à dire ?","A-t-il  quelque chose de nouveau s'est passé sur l'île ?","Me raconteras-tu les derniers potins ?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Je veux vous poser quelques questions sur l'île.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Je voulais juste savoir comment tu allais. À plus tard !";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ha, tout comme moi. Je ne suis pas marin, mais ma passion pour les aventures m'a conduit ici. Maintenant, je dois pourrir dans ce cimetière de navires comme les autres. Au fait, je m'appelle Adolf Barbier.";
			link.l1 = "Ce fut un plaisir de vous rencontrer, Adolf. À bientôt.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("As-tu quelque chose d'intéressant à raconter ?","Quelque chose de nouveau s'est-il passé sur l'île ?","Me raconteras-tu les derniers potins ?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Je veux te poser quelques questions sur l'île.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		//----------------------------------Адольф Барбье----------------------------------------
		case "Adolf":
			dialog.text = "Pourquoi diable as-tu envahi mon logis sans ma permission ?";
			link.l1 = "Tu fais preuve de mauvaises manières envers ton invité, Adolf. Et j'ai une affaire à te proposer.";
			link.l1.go = "Adolf_1";
		break;
		
		case "Adolf_1":
			dialog.text = "Je ne fais pas affaire avec des gens que je ne connais pas ! Sors d'ici !";
			link.l1 = "Comme ça ? Alors tu fais affaire avec les Narvals, mais tu ne veux pas en faire avec moi ? Quelle honte...";
			link.l1.go = "Adolf_2";
		break;
		
		case "Adolf_2":
			dialog.text = "De quoi parles-tu, bouffon? Quelle affaire avec les Narvals? C'est ta dernière chance de déguerpir d'ici ou je devrai te jeter par-dessus bord moi-même!";
			link.l1 = "Tu n'as pas les tripes pour faire ça, 'maître du lancer'... Écoute-moi bien. Où est le stutzen que tu vas utiliser pour tirer sur l'amiral ? Vas-tu me le dire toi-même ou dois-je devenir plus persuasif ?";
			link.l1.go = "Adolf_3";
		break;
		
		case "Adolf_3":
			dialog.text = "Quoi ? Quel stutzen ? Quel amiral ? Es-tu fou, camarade ? J'ai vendu mon stutzen et je ne l'ai plus. Et ça ne te regarde pas à qui je l'ai vendu. Je m'en fous de ce qu'ils en feront. Et je ne vais tirer sur personne - ni amiraux, ni généraux. Tu me comprends, connard ?";
			link.l1 = "Je ne comprends qu'une chose : tu es un menteur et un meurtrier, Adolf. Je sais que tu ne l'as pas vendu mais racheté. Je sais aussi que tu as reçu une somme énorme pour rembourser tes dettes et acheter cette cabine...";
			link.l1.go = "Adolf_4";
		break;
		
		case "Adolf_4":
			dialog.text = "C'est mon argent, crétin ! Je l'ai gagné ! Et j'ai vendu mon stutzen !";
			link.l1 = "Tu mens, Adolf. Les Narvals t'ont embauché pour abattre l'amiral. Ils t'ont donné l'argent pour racheter ton stutzen. Ils ont aussi payé pour cet endroit. Tu sais mieux que moi que le beaupré derrière cette porte est le seul endroit sur l'île d'où l'on peut tirer sur le balcon arrière de la résidence du Requin.";
			link.l1.go = "Adolf_5";
		break;
		
		case "Adolf_5":
			dialog.text = "Tu es fou, salaud ! Tu dois être isolé immédiatement ! J'ai attendu cette cabine pendant six mois avant que Sessile ne parte d'ici...";
			link.l1 = "Assez. Je vais te fouiller ainsi que ta cabine, je trouverai le stutzen et quelques autres preuves, j'en suis sûr. Et puis nous irons ensemble voir le Requin. Il sera ravi de te regarder dans les yeux.";
			link.l1.go = "Adolf_6";
		break;
		
		case "Adolf_6":
			dialog.text = "Ah, tu es un salaud malade ! Je préférerais mourir que de laisser quelque racaille folle toucher à mes affaires !";
			link.l1 = "Alors je les toucherai sans votre permission...";
			link.l1.go = "Adolf_7";
		break;
		
		case "Adolf_7":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "barmen", "stay");
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_AdolfDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
	case "int_quests":
			dialog.text = "Eh bien, parlons. Que veux-tu savoir ?";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Comment es-tu arrivé ici ?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Que pouvez-vous me dire sur les clans locaux ?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "As-tu exploré l'anneau extérieur des navires ?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "L'île a-t-elle des liens avec Cuba ou le continent ?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Aucune question. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "J'avais trouvé un manuscrit d'un marin - Alvarado, il était espagnol. Il décrivait L'Île avec beaucoup de détails. Il mentionnait quelques navires intéressants - San Augustine, San Geronimo et Tartarus. Tous faisaient partie de l'escadre de Betancourt, disparue il y a plus de cinquante ans\nJ'ai fait des recherches sur cette expédition. Il s'est avéré qu'il y avait un quatrième navire nommé St. Anna qui transportait le trésor de l'escadre - un tas de doublons ! En outre, les navires avaient du minerai d'or dans leurs cales. J'ai décidé de trouver L'Île\nJ'ai conclu un marché avec un capitaine que je connaissais et nous avons navigué sur sa goélette. Il est clair comment l'histoire s'est terminée, je suppose. Nous avons trouvé L'Île, les navires de Betancourt, même sa descendance - il vit ici, il s'appelle Antonio de Betancourt. Mais je n'ai pas réussi à quitter cet endroit\nLa goélette a été brisée par les récifs, mon compagnon est mort et moi, parmi d'autres survivants, j'ai réussi à arriver ici. Le pire, c'est que je n'ai pas trouvé ce que je cherchais - ni le trésor de St. Anna, ni le minerai d'or.";
			link.l1 = "J'ai aussi lu les notes d'Alvarado. Une histoire intrigante.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Les Rivados sont de fichus païens. Ce sont les descendants d'esclaves noirs, amenés ici par de Betancourt depuis l'Afrique. Bien qu'ils aient appris à manier les lames et les mousquets des blancs, ils restent des sauvages.\nLes Narvals sont de bonnes gens, intelligents et d'honnêtes combattants. Ils comptent parmi eux des artisans exceptionnels. J'en connais beaucoup d'entre eux. Peut-être qu'un jour, je rejoindrai leur clan.\nLes pirates sont une plaie, qu'ils aillent au diable. Nous ne les avons pas appelés, mais ils sont arrivés, ont capturé nos provisions et ont osé nous vendre notre propre nourriture ! Fichus salauds, hein ? Dommage que nous ne puissions pas les chasser et que nous devions vivre avec leur présence.";
			link.l1 = "Intéressant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Bien sûr. Il faut bien que l'homme gagne sa croûte. Ces maudits pirates exigent de l'or, des pesos ou d'autres objets de valeur pour la nourriture. Ils la vendent bien moins cher à des locaux comme moi qu'aux clans, mais ce n'est tout de même pas de la charité. Dieu merci, il y a assez de navires dans l'anneau extérieur à piller, beaucoup restent encore intacts depuis leur naufrage.\nUne activité intéressante, mais dangereuse : on peut tomber dans la cale inondée, se briser les os, se coincer dans les cordages, se faire écraser par des morceaux de bois ou rencontrer des crabes géants - ils visitent souvent les cales là-bas.";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Hélas, ce n'est pas le cas. On dit que les boucaniers et les contrebandiers de Cuba visitaient cet endroit il y a longtemps - ils échangeaient des provisions contre de l'or et des marchandises. Même les Narvals visitaient les colonies. Mais c'est de l'histoire maintenant. Personne n'oserait naviguer sur des bateaux fragiles et petits. Les tempêtes détruisent les petites embarcations en un instant et nous n'avons pas de meilleurs navires ici.";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Que fais-tu là, hein? Voleur!","Regarde-moi ça ! À peine perdu dans mes pensées, tu as décidé de fouiller dans ma malle !","Tu as décidé de fouiller mes coffres ? Tu ne t'en sortiras pas comme ça !");
			link.l1 = "Merde !";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Quoi?! Décidé de fouiller mes coffres ? Tu ne t'en tireras pas comme ça !";
			link.l1 = "Folle fille !";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Ecoute, tu ferais mieux de ranger ton arme. Ça me rend nerveux.","Tu sais, ici, courir avec une lame n'est pas toléré. Range-la.","Ecoute, ne fais pas le chevalier médiéval courant avec une épée. Range-la, ça ne te va pas...");
			link.l1 = LinkRandPhrase("Bien.","D'accord.","Comme vous dites...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Écoute, je suis citoyen de la ville et je te demande de baisser ta lame.","Ecoutez, je suis citoyen de la ville et je vous demanderais de ranger votre lame.");
				link.l1 = LinkRandPhrase("Très bien.","Très bien.","Comme vous dites...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sois prudent, camarade, en courant avec une arme. Je pourrais devenir nerveux...","Je n'aime pas quand des hommes marchent devant moi avec leur arme prête. Cela me fait peur...");
				link.l1 = RandPhraseSimple("Compris.","Je l'emporte.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
