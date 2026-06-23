// Жаклин Тьюрам - торговый капитан
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
				dialog.text = "Je ne veux pas te parler. Tu attaques des civils paisibles sans raison et tu les provoques à se battre. Déguerpis !";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Bonne journée, monsieur. Vous êtes nouveau ici, n'est-ce pas ?";
				link.l1 = TimeGreeting()+"Oui, je suppose que je suis le plus nouveau ici. Mon nom est "+GetFullName(pchar)+"Et quel est le vôtre ?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"Voulez-vous quelque chose ?";
				link.l1 = LinkRandPhrase("As-tu quelque chose d'intéressant à dire ?","A-t-il  quelque chose de nouveau qui s'est passé sur l'île ?","Voudrez-vous me raconter les derniers potins ?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Je veux vous poser quelques questions sur l'île.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Je voulais juste savoir comment tu vas. À bientôt !";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Jacqueline Turam. Il y a deux ans, j'étais une marchande décente et riche, propriétaire et capitaine de ma propre flute. Hélas, maintenant je suis pauvre comme Job et je ne peux espérer que ma situation change d'une manière ou d'une autre\nCertains ont de la chance ici - ils trouvent des bijoux, de l'or, des navires remplis de trésors, mais je ne suis pas de ceux-là. J'ai trouvé seulement un coffre avec des doublons et quelques babioles\nAu moins c'est suffisant pour acheter de la nourriture, donc je ne meurs pas de faim... Enchantée de vous rencontrer, monsieur, je ne suis pas contre bavarder...";
			link.l1 = "Je suis heureux de te rencontrer aussi, Jacqueline. À bientôt !";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("As-tu quelque chose d'intéressant à dire ?","Est-ce qu'il s'est passé quelque chose de nouveau sur l'île ?","Veux-tu me raconter les derniers potins ?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Je veux vous poser quelques questions sur l'île.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Je suis tout ouïe.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Comment es-tu arrivé ici ?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Que fais-tu ici ?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Dis-moi, je vois qu'il y a des filles et des femmes sur l'Île...";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Souhaitez-vous retourner dans le vaste monde ?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Ce n'est rien.";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Veux-tu entendre mon histoire ? Très bien. Comme tu le sais déjà, j'étais capitaine de commerce. Un jour, je naviguais de Tortuga à Belize sur ma bonne vieille flûte. Mes cales étaient remplies de bois noir et de cacao, j'avais dépensé toutes mes pièces sur la cargaison\nJ'avais arrangé une affaire très profitable avec un homme, il voulait acheter ma cargaison à un prix extrêmement élevé. Je pouvais faire fortune avec cet accord. Tout allait bien, pas un nuage à l'horizon, mon navire était rapide comme l'oiseau. Nous ne nous attendions pas à des ennuis\nJe naviguais près de Cuba, évitant les patrouilles espagnoles, mais soudain nous avons été attaqués par une galéon pirate. Que faisaient-ils là - en plein territoire espagnol ? Nous avons essayé de fuir, mais nous avons échoué, le galéon était étonnamment rapide\nLes pirates nous ont poursuivis et attaqués. Leurs couleuvrines étaient chargées de mitraille, la première salve a gravement endommagé mon équipage et l'a démoralisé. Je voulais leur donner un bon combat, mais mes propres marins et officiers m'ont arrêté. Nous nous sommes rendus\nLes pirates ont rapidement pris notre cargaison et jeté nos canons par-dessus bord. Je pensais que c'était la fin. Perdre la cargaison était un coup dur, mais je pouvais encore gagner de l'argent sur les frets et un jour retrouver ma situation\nMais il en fut autrement. Les bâtards de pirates ont ouvert le feu sur ma flûte sans défense. Nous étions une cible parfaite\nJe me souviens encore d'eux riant... Le galéon s'est éloigné et nous étions en train de patauger, tenant les épaves. Puis une forte tempête avec des vagues est arrivée et je n'ai jamais revu aucun membre de mon équipage depuis lors. J'ai réussi à m'attacher à une partie du mât et à rester à flot\nJe vous épargnerai les détails supplémentaires de l'attaque de requin. Après une période de temps éternelle, j'ai été amené ici par un courant marin. C'est ainsi que j'ai survécu.";
			link.l1 = "Oui, c'est vraiment une triste histoire.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Je vis comme le reste des locaux - je vis simplement. Je cherche des objets de valeur sur l'anneau extérieur et les échange contre de la nourriture. Je rêve de trouver un coffre de roi indien rempli de trésors... Ou au moins un galion avec de l'or espagnol, héhé. Ne fais pas trop attention, c'est juste moi\nJe rêve de manger quelque chose d'autre que du bœuf salé et du poisson. Eh, il y avait un homme ici, il chassait ces crabes géants. J'avais l'habitude de payer cinq doublons pour une pince et de m'en nourrir pendant plusieurs jours\nDommage que le chasseur soit mort... bien que je ne puisse pas dire que ce n'était pas prévisible - chasser ces créatures est une activité très dangereuse.";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Je vois ce que tu insinues. Oui, l'amour et les intrigues existent ici. Et pourquoi ne le feraient-ils pas ? L'homme est fait pour la femme et la femme est faite pour l'homme. La nature. Tu pourrais essayer avec Gillian et Tanneke. Elles sont jeunes, jolies et ne rechignent pas à courtiser\nJe me suis trouvé une femme - Natalia. Elle est serveuse à la taverne de Sancho. Une fille formidable, je te dis. Je crois qu'elle est la seule raison pour laquelle je n'ai pas perdu la tête durant les premiers mois ici. Elle a beaucoup aidé et maintenant nous sommes ensemble.";
			link.l1 = "Hm... J'ai compris !";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Bonne question. J'aimerais cela, bien sûr. Mais en y réfléchissant... je suis brisé. J'ai tout investi dans la cargaison et mon navire a sombré. Il ne me reste plus rien pour vivre. La seule façon de gagner de l'argent pour moi est de travailler pour la Compagnie néerlandaise des Indes occidentales, s'ils m'engagent bien sûr.\nSi seulement j'avais assez d'argent pour acheter une goélette et assez de provisions... Donc je ferais mieux de rester sur l'île. Au moins ici, je n'ai pas à travailler de l'aube à l'aube pour un morceau de pain.";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Que fais-tu là, hein? Voleur!","Regarde-moi ça ! Dès que je me suis perdu dans mes pensées, tu as décidé de fouiller dans mon coffre !","Tu as décidé de fouiller dans mes coffres ? Tu ne t'en sortiras pas comme ça !");
			link.l1 = "Merde !";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Quoi ?! Vous avez décidé de fouiller mes coffres ? Vous ne vous en sortirez pas comme ça !";
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
			dialog.text = LinkRandPhrase("Ecoute, tu ferais mieux de ranger ton arme. Elle me rend nerveux.","Tu sais, courir avec une lame n'est pas toléré ici. Range-la.","Ecoute, ne fais pas le chevalier médiéval courant avec une épée partout. Range-la, cela ne te va pas...");
			link.l1 = LinkRandPhrase("Très bien.","D'accord.","Comme vous dites...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Écoute, je suis citoyen de la ville et je te demande de rengainer ton épée.","Écoutez, je suis citoyen de la ville et je vous demanderais de ranger votre lame.");
				link.l1 = LinkRandPhrase("Très bien.","Qu'importe alors.","Comme tu dis...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sois prudent, l'ami, en courant avec une arme. Je peux devenir nerveux...","Je n'aime pas quand des hommes marchent devant moi avec leur arme prête. Ça me fait peur...");
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
