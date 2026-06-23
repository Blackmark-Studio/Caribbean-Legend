// Сесил Галард - бабулька
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
				dialog.text = "Je ne veux pas te parler. Tu attaques des civils paisibles sans raison et tu les provoques à se battre. Fiche le camp !";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Vous désirez quelque chose, jeune homme ?";
				link.l1 = TimeGreeting()+"Permettez-moi de me présenter - "+GetFullName(pchar)+" Je suis un nouveau venu.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"Tu veux quelque chose ?";
				link.l1 = LinkRandPhrase("As-tu quelque chose d'intéressant à raconter ?","Y a-t-il du nouveau sur l'île ?","Me diras-tu les derniers potins ?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Je veux vous poser quelques questions sur l'île.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Je voulais juste savoir comment tu vas. À bientôt !";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "A-ah, alors vous apprenez à connaître notre Île et ses habitants, n'est-ce pas ?";
			link.l1 = "Exactement, madame ?..";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Halard. Cecille Halard.";
			link.l1 = "Enchanté de faire votre connaissance, madame Halard ! C'est un plaisir pour moi.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Le mien aussi... Et comment es-tu arrivé ici, jeune homme ? Je ne me souviens d'aucun naufrage récent...";
			link.l1 = "J'ai été conduit ici depuis le continent sur une barque... mais elle a coulé juste près des rivages de l'Île. C'est ainsi que je me suis retrouvé sans navire.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Une barque ? J'ai du mal à y croire... Dans ce cas, vous avez vraiment de la chance d'avoir navigué jusqu'à l'Île sur une telle coque et de ne pas être tombé dans une tempête. Les tempêtes sont des événements rares à l'intérieur de l'île, mais à l'extérieur, elles sont une menace, une menace très soudaine. \nAlors considérez-vous chanceux et habituez-vous au mode de vie local ! Je ne veux pas vous attrister, mais venir ici est facile, quitter l'Île est presque impossible. Ne pensez pas que je me plains, personne n'a réussi à quitter l'Île vivant depuis dix ans.";
			link.l1 = "Et pourtant, je vais essayer d'être un peu plus optimiste. Ravi de vous rencontrer et de vous voir dans les parages !";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Oui, jeune homme ?";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Et comment êtes-vous arrivée ici, madame ?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Vous vivez ici depuis longtemps, n'est-ce pas ?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Que pouvez-vous me dire sur les habitants ?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Peux-tu me parler des personnes intéressantes qui vivent ici ?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Pas de questions. Pardonnez-moi...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "C'était il y a si longtemps, donc je ne me souviens pas vraiment comment cela s'est passé. Naufrage et voilà...";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Parfois, je pense que je suis né ici... Mais ce n'est pas vrai bien sûr. J'ai vécu ici toute la seconde moitié de ma vie. Et elle fut longue. Et je mourrai ici car je n'ai pas l'intention de quitter cet endroit.";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Et il n'y a pas grand-chose à dire, jeune homme... chacun est différent. Nous avons tout le monde ici - blancs, noirs, Indiens, anciens esclaves et nobles, condamnés d'État et soldats. Et il y en avait encore plus avant. Chacun a sa propre histoire et ses propres habitudes. Certains s'en fichent, mais d'autres sont toujours désireux de rentrer chez eux. Voilà comment nous vivons...";
			link.l1 = "Intéressant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Les personnes les plus intéressantes ici sont : le mécanicien-inventeur Narval, Herr Schmidt - armurier Narval, Sancho Carpentero - le barman indigène. Et maintenant, nous avons aussi l'amiral avec son second.";
			link.l1 = "Je vais considérer cela...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Que fais-tu là, hein? Voleur!","Regarde-moi ça ! Dès que je me suis perdu dans mes pensées, tu as décidé de fouiller mon coffre !","Décidé à fouiller dans mes coffres ? Tu ne t'en tireras pas comme ça !");
			link.l1 = "Satané !";
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
			dialog.text = LinkRandPhrase("Ecoute, tu ferais mieux de ranger ton arme. Ça me rend nerveux.","Tu sais, courir avec une lame n'est pas toléré ici. Range-la.","Ecoute, ne joue pas au chevalier médiéval courant avec une épée. Range-la, ce n'est pas pour toi...");
			link.l1 = LinkRandPhrase("D'accord.","D'accord.","Comme tu dis...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Écoutez, je suis citoyen de la ville et je vous demanderais de rengainer votre lame.","Écoutez, je suis citoyen de la ville et je vous demande de rengainer votre lame.");
				link.l1 = LinkRandPhrase("Très bien.","D'accord.","Comme vous le dites...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sois prudent, l'ami, quand tu cours avec une arme. Je pourrais devenir nerveux...","Je n'aime pas quand des hommes marchent devant moi avec leurs armes prêtes. Ça me fait peur...");
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
