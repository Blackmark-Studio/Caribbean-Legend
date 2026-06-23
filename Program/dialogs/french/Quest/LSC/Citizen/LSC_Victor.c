// Виктор Кассель - бандит
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
				dialog.text = "Je ne veux pas te parler. Tu attaques des civils pacifiques sans raison et les provoques à se battre. Dégage !";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hm... Que veux-tu, camarade ? Si tu veux parler, je dois te décevoir. Je n'ai aucune envie de parler.";
				link.l1 = "Dommage... Je voulais parler. Je suis nouveau ici et je fais juste connaissance avec les gens...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+" ! Que veux-tu ?";
				link.l1 = LinkRandPhrase("As-tu quelque chose d'intéressant à raconter ?","A-t-il eu du nouveau sur l'île ?","Me raconterez-vous les derniers potins ?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Je veux te poser quelques questions sur l'île.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Je voulais juste savoir comment tu vas. À bientôt !";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Un nouveau venu ? Hm. Bien, alors. Je suis Victor Cassel et tu ferais mieux d'éviter de me mettre en colère quand je suis de mauvaise humeur. Et quand je suis de bonne humeur aussi. Je ne perds pas de temps en bavardages, je frappe les gens immédiatement s'ils sont trop insistants.";
			link.l1 = "Eh bien et moi je suis "+GetFullName(pchar)+"Au fait, je peux facilement rendre les coups. Mais j'espère qu'il n'y aura pas de raison de le faire. Je ne te dérangerai pas si tu es si insociable. Adieu.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Tu as quelque chose d'intéressant à dire?","Quelque chose de nouveau s'est-il passé sur l'île ?","Voulez-vous me raconter les derniers potins ?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Je veux te poser quelques questions sur l'île.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ouais ? Et que puis-je te dire ?";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Comment es-tu arrivé ici ?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Comment se passe la vie ici ?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Qui est la personne la plus... importante ici ?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Et où puis-je obtenir des pièces à L'Île Justice ?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Pas de questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Je suis désolé, ami, mais quelle est votre préoccupation ? Je viens d'arriver ici. Je ne veux pas parler de cette histoire, surtout avec un homme que je ne connais pas.";
			link.l1 = "Eh bien, je suis désolé...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Ça semble ennuyeux. Fastidieux, monotone et insensé. Je vais rejoindre les pirates du Requin, ces gars-là en valent la peine. Je rejoindrai l'équipage avec grand plaisir, je dois juste... explorer un peu. Je suis sûr qu'ils trouveront un moyen de quitter l'Île.";
			link.l1 = "Vraiment ? Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Amiral, c'est sûr ! Les pirates tiennent les Narvals et les Rivados dans son poing et les clans n'osent rien dire. Ensuite viennent les chefs des clans, Donald Greenspy des Narvals et Black Eddy des Rivados. Axel Yost - un marchand des Narvals est un homme important aussi. Et bien sûr Sancho Carpentero, c'est un bon gars...";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Coffres. Bien sûr, il faut d'abord les ouvrir, ici les gens ne se font pas confiance, alors tous les coffres sont verrouillés. Laisse-moi te dire une chose, mon pote, les meilleurs bibelots sont gardés à l'intérieur des navires sous la surveillance de leurs propriétaires.\nTu peux aussi explorer l'anneau extérieur mais prie de ne pas tomber à travers le bois pourri. Ou bien tu peux chasser des crabes géants, tu peux obtenir un bon prix pour la viande de leurs pinces.";
			link.l1 = "Compris...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Que fais-tu là, hein? Voleur!","Regarde-moi ça ! Dès que je m'abandonne à la contemplation, tu décides de fouiller dans mon coffre !","Décidé de fouiller mes coffres ? Tu ne t'en tireras pas comme ça !");
			link.l1 = "Merde !";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Quoi?! Tu as décidé de fouiller dans mes coffres? Tu ne t'en tireras pas comme ça!";
			link.l1 = "Fille insensée !";
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
			dialog.text = LinkRandPhrase("Écoute, tu ferais mieux de ranger ton arme. Ça me met mal à l'aise.","Tu sais, courir avec une lame n'est pas toléré ici. Range-la.","Écoute, ne joue pas au chevalier médiéval courant avec une épée partout. Range-la, ça ne te va pas...");
			link.l1 = LinkRandPhrase("Très bien.","D'accord.","Comme tu dis...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Écoute, je suis citoyen de la ville et je te demanderais de ranger ta lame.","Écoute, je suis citoyen de la ville et je te demanderais de baisser ton épée.");
				link.l1 = LinkRandPhrase("Très bien.","D'accord.","Comme vous dites...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sois prudent, l'ami, en courant avec une arme. Je pourrais m'énerver...","Je n'aime pas quand des hommes marchent devant moi avec leur arme prête. Ça me fait peur...");
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
