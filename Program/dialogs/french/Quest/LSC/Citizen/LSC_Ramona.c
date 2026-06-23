// Рамона Лоцано - горячая испанская сеньорита
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
				dialog.text = "Je n'ai pas envie de te parler. Tu attaques des civils paisibles sans raison et les provoques à se battre. Dégage !";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Bonjour, bonjour ! Nouveau venu ? Ou étais-tu caché dans les cales, car c'est la première fois que je vois ton visage par ici ?";
				link.l1 = TimeGreeting()+"Se cacher dans les cales n'est pas mon genre. Je préfère la place du capitaine... Oui, je suis un nouveau venu ici.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+pchar.name+"! "+TimeGreeting()+" ! Je suis ravi de te voir ! Que dis-tu";
				link.l1 = LinkRandPhrase("As-tu quelque chose d'intéressant à dire ?","A-t-il   eu   du   nouveau   sur   l'île ?","Pourriez-vous me raconter les derniers potins ?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Je veux te poser quelques questions sur l'île.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Je voulais juste savoir comment tu vas. À bientôt !";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Eh bien, faisons connaissance alors... capitaine. Je suis Ramona Lozano, mais n'essaie même pas de m'appeler senora Lozano, je déteste ça. Quel est ton nom ?";
			link.l1 = "Bonjour, mon ami."+GetFullName(pchar)+"Enchanté de faire votre connaissance, Ramona.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Es-tu vraiment content ou fais-tu juste preuve de politesse, "+GetFullName(pchar)+" ? Dites-moi, êtes-vous vraiment un capitaine ou plaisantiez-vous ? ";
			link.l1 = "Oho, tant de questions à la fois ! Puis-je y répondre dans l'ordre ? Premièrement, je suis vraiment ravi, je ne rencontre pas de jolies filles tous les jours, deuxièmement, je suis capitaine, c'est vrai. Mais mon navire est près des côtes du Main occidental à présent...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Drôle ! Et comment cela se fait-il, capitaine ? Vous êtes ici, mais votre navire est près des côtes du continent. N'avez-vous pas peur que votre équipage ne se disperse et que votre vaisseau ne vous soit enlevé ?";
			link.l1 = "J'ai navigué ici sur une barque pour... l'exploration, mais tout a mal tourné et je me suis retrouvé sur votre Île. Puis nous avons heurté des débris dans l'obscurité, chaviré et voilà ! Me voici. Mon navire m'attendra aussi longtemps que je le désire. Dannie Hawk pourra contrôler mes hommes.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Dannie Hawk ? La Danielle Hawk ? Veux-tu dire que tu navigues avec elle ?";
			link.l1 = "Merde flotte, Dannie me sert comme mon officier. Elle a été laissée au commandement pendant que je suis absent... Comment la connaissez-vous ?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Ha ! Tout le monde dans les colonies espagnoles connaît la pirate Danielle Hawk et son mari, Nathaniel. Oui, vous, señor "+GetFullName(pchar)+", doit être un dur à cuire... Es-tu alors un pirate? Ne t'inquiète pas, je m'entends très bien avec les gens de ton acabit. J'aime les durs à cuire.";
			link.l1 = "Eh bien, je ne suis pas vraiment un pirate... Je travaille juste en ce moment avec Jan Svenson et je cherche le mari de Dannie, Nathaniel.";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Et vas-tu me dire maintenant que tu n'es pas un pirate? Travaillant pour le Diable des Forêts, ton premier lieutenant est Dannie Hawk et tu cherches Nathan Hawk... et je suis sûr que tu es venu ici pour l'amiral. N'est-ce pas?";
			link.l1 = "Ramona, tu peux m'appeler pirate si tu veux, ça ne me dérange pas. Tu peux même m'appeler une ancre, mais ne me jette pas à l'eau...";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "Il semble que vous êtes l'un des gars vraiment sérieux, "+pchar.name+"Très bien, il faut que j'y aille. À bientôt ! J'ai le sentiment que nous pourrions devenir amis... des amis très proches.";
			link.l1 = "Pourquoi pas ? Bonne chance !";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Oh, vraiment ? Eh bien, demandez, je répondrai si je peux...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Comment es-tu arrivé ici ?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Assurément, tu n'as jamais essayé de t'enfuir d'ici...";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Comment vivez-vous ici ?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Que faites-vous ici? Je suppose que la nourriture n'est pas gratuite, n'est-ce pas?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Pas de questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "C'est une longue histoire... Mon beau-père est à blâmer. Il y a quatre ans, je vivais à La Havane et je ne pouvais même pas imaginer comment les choses tourneraient pour moi. Ma mère est morte et j'étais héritier légal. Nous n'étions pas riches, mais nous avions assez d'argent, plus qu'il n'en faut pour vivre décemment. Mon beau-père n'aimait pas cela et il a décidé de se débarrasser de moi\nBien sûr, je l'ai découvert seulement après que deux brutes à gages m'ont attaqué juste derrière les portes de la ville. Ces imbéciles m'ont eux-mêmes dit qui les avait engagés pour me tuer et pourquoi. Heureusement, ils n'étaient pas des professionnels, je serais allongé dans les buissons avec la gorge tranchée si c'était le cas. Les idiots ont décidé de s'amuser un peu d'abord\nLe destin m'a sauvé ce jour-là, un capitaine comme vous passait par les portes. Il a vu le spectacle et a tué la vermine immédiatement. Ils n'avaient aucune chance. Je lui ai raconté ce qui m'était arrivé et pourquoi. J'ai pleuré un peu... Il savait que je n'avais nulle part où aller, alors il m'a pris sur son navire pour vivre. D'abord temporairement, puis\nJe crois que je serais resté avec lui, mais deux mois plus tard, il a combattu une patrouille, a perdu un mât, a été pris par un fort coup de vent et a trouvé la paix au fond de l'anneau extérieur. J'ai survécu malgré tout et j'ai rejoint la communauté de l'Île.";
			link.l1 = "Triste histoire, je n'ai rien à dire...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Bien sûr que non. Parce que c'est impossible. J'ai vu un homme qui a essayé de quitter cet endroit sur une chaloupe... il est revenu deux jours plus tard. Attaché à une épave de mât pour se sauver de la noyade. Il était bleu et absolument mort\nAlors dis-moi, "+pchar.name+", que suis-je censé faire dès que je m'en vais d'ici? La Havane est trop dangereuse pour moi, le beau-père essaiera de me tuer à nouveau. Je n'ai ni maison, ni argent. Où devrais-je aller? Au bordel?";
			link.l1 = "Tout de même, veux-tu retourner à l'archipel ?";
			link.l1.go = "ansewer_2_1";
		break;
		
		case "ansewer_2_1":
			dialog.text = "Et que penses-tu ? Bien sûr, je le veux. Mais c'est impossible et je viens de te dire pourquoi. Eh, si seulement quelqu'un pouvait s'occuper de mon beau-père... avec l'acier tranchant ou une balle, alors il y aurait une chance pour moi de retourner à une vie normale. Mais qui oserait faire cela si mon beau-père est le meilleur ami de l'alcalde de La Havane ? Et pourquoi parlons-nous de cela ? Il n'y a pas d'issue ici...";
			link.l1 = "Nous verrons. Le moment viendra...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			// сюда направление на квест
		break;
		
		case "ansewer_3":
			dialog.text = "Je vis tant bien que mal. Il n'y a pas d'autre option. Mes amis sont surtout des hommes car deux de nos beautés à marier - Gillian et Tanneke - ne m'aiment pas à cause de mon caractère et j'en ai assez de leur décence de façade. Natalie était une fille bien jusqu'à ce qu'elle commence à passer beaucoup de temps avec ces abrutis, la stupidité est contagieuse.";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Je travaille comme les autres filles. Notre principal objectif est d'aider les hommes. Il y a beaucoup de travail pour les femmes sur L'Île Justice, donc je suis assez occupée. Et je reçois souvent des cadeaux, c'est une chose courante ici. Mais ne vous méprenez pas sur moi, je ne suis pas une dévergondée. J'ai été bien éduquée dans une famille respectable. Je ne fais simplement pas semblant d'être une sainte comme d'autres le font.";
			link.l1 = "Je ne pensais rien de mal à votre sujet...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Qu'est-ce que tu fais là, hein ? Voleur !","Regarde-moi ça ! Aussitôt que je me suis perdu dans la contemplation, tu as décidé de fouiller ma malle !","Décidé à fouiller mes coffres ? Tu ne t'en sortiras pas !");
			link.l1 = "Merde !";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Quoi ?! Décidé de fouiller dans mes coffres ? Tu ne t'en tireras pas comme ça !";
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
			dialog.text = LinkRandPhrase("Écoute, tu ferais mieux de ranger ton arme. Ça me rend nerveux.","Vous savez, courir avec une lame n'est pas toléré ici. Rangez-la.","Écoute, ne joue pas au chevalier médiéval courant avec une épée. Range-la, ça ne te va pas...");
			link.l1 = LinkRandPhrase("Bien.","Bien sûr.","Comme tu dis...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Écoute, je suis citoyen de la ville et je te demande de rengainer ton épée.","Écoutez, je suis citoyen de la ville et je vous demande de ranger votre lame.");
				link.l1 = LinkRandPhrase("Très bien.","D'accord.","Comme vous dites...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sois prudent, l'ami, en courant avec une arme. Je pourrais m'énerver...","Je n'aime pas quand des hommes marchent devant moi avec leur arme prête. Cela me fait peur...");
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
