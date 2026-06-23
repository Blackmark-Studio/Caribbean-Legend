// Таннеке Эверс - просто девушка
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
				dialog.text = "Bonne journée ! Vous ai-je déjà vu ? Je ne vous ai jamais vu auparavant, c'est certain...";
				link.l1 = TimeGreeting()+" . C'est vrai, je suis un nouveau... visiteur ici. Mon nom est "+GetFullName(pchar)+" et je suis capitaine.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"Voulez-vous quelque chose ?";
				link.l1 = LinkRandPhrase("As-tu quelque chose d'intéressant à dire ?","A-t-il  eu quelque chose de nouveau sur l'île ?","Voulez-vous me raconter les derniers potins ?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Je veux te poser quelques questions sur l'île.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Je voulais juste savoir comment tu vas. À bientôt !";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "As-tu été capitaine ?";
			link.l1 = "Pourquoi ai-je été ? Je suis encore capitaine... Ah-ah, je comprends ! Vous pensez que mon navire est coulé ou détruit par les récifs. Non. Elle est près des côtes du Main occidental. Et je suis arrivé ici sur une barque, mais cela s'est mal terminé, la barque a eu une voie d'eau et a coulé.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Es-tu arrivé ici sur une barque? Et comment as-tu réussi à survivre à la tempête?";
			link.l1 = "Quelle tempête ? Je ne me souviens d'aucune tempête...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Mais comment est-ce possible? Il y a toujours une tempête autour de l'Île. Tout le monde le dit.";
			link.l1 = "Eh bien, ce n'est pas le cas ou j'ai eu la chance de l'éviter. La mer était absolument calme... excusez-moi, puis-je connaître le nom d'une si jolie dame ?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Oh ! Je suis désolé, j'ai oublié de me présenter... Je m'appelle Tanneke. Enchanté de faire votre connaissance.";
			link.l1 = "Enchanté de vous rencontrer également, Tanneke... C'est mon plaisir.";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Et pourquoi as-tu décidé de rejoindre notre Île sur une barque ? A-ah, je comprends - tu as été amené ici par le courant. Personne ne connaît l'Île et les gens y arrivent toujours par hasard.";
			link.l1 = "Ce n'est pas correct. Il y a des rumeurs assez vraies à propos de l'Île, y compris son emplacement. J'ai donc décidé de la voir de mes propres yeux...";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Maintenant je vois. Vous êtes comme Adolf Barbier, avez trop lu du capitaine Alvarado et avez décidé de chercher l'or de l'amiral de Betancourt. Hélas, capitaine, si un coquin aussi rusé que Barbier n'a pas réussi à le trouver, alors je doute que vous y parveniez non plus\nEt je pense vraiment qu'il n'y a pas d'or d'amiral, Antonio a dû simplement l'inventer pour nous montrer quel homme important était son grand-père... Eh bien, vous resterez donc avec nous. Arriver ici était facile, mais partir doit être impossible. Partir d'ici en un seul morceau, je veux dire.";
			link.l1 = "Ce n'est rien. Je pense que je pourrai m'en occuper, je ne parle pas de l'or de Betancourt dont tu as parlé - c'est la première fois que j'en entends parler, je parle de quitter l'Île. Vivant. Ce fut un plaisir de parler avec toi, Tanneke. À bientôt!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Demandez ce que vous voulez, capitaine...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Comment es-tu arrivé ici ?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Avez-vous déjà essayé de quitter l'Île ?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Comment vivez-vous ici ?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Les filles doivent-elles acheter de la nourriture à l'amiral ou l'obtiennent-elles gratuitement ?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Aucune question. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Je suis hollandaise, mais nous vivions à Santiago. Mes parents m'ont envoyée travailler comme servante pour la famille du banquier Geraldi. En avez-vous entendu parler? Il y a trois ans, l'un d'eux a navigué vers la Nouvelle-Espagne sur un lougre courrier. On m'a dit de l'accompagner. Le deuxième jour de notre voyage, nous avons été capturés par une brigantine sous pavillon espagnol\nLeur officier est monté à bord de notre navire et a eu une conversation avec notre capitaine, le capitaine s'est mis en colère et a chassé l'officier. Nous avons été attaqués dès que l'invité a rejoint son navire. Nous avons essayé de fuir, mais ils ont réussi à nous aborder. Autant que j'ai compris, ils avaient besoin de mon maître Geraldi, car ils se sont précipités à l'intérieur d'une cabine, l'ont capturé et emmené. Moi et les marins avons été emmenés dans la cale et laissés là.\n Je pensais qu'ils allaient nous couler mais ils ont simplement pris la mer. Les marins ont réussi à sortir de la cale, mais notre capitaine a été tué au combat et aucun des survivants ne savait comment naviguer sur le bon cap. Nous naviguions quelque part pendant un certain temps jusqu'à ce qu'un fort coup de vent nous emporte\n Quelques heures plus tard, notre lougre a été jeté sur l'anneau extérieur. Il y est toujours. J'ai eu la chance de survivre au chaos, après l'aube, moi et quelques autres personnes 'chanceuses' avons atteint l'Île.";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Non. Et comment l'imaginez-vous ? Il n'y a aucun navire prêt à prendre la mer ici et utiliser une chaloupe revient à signer soi-même sa propre condamnation à mort. Comme je l'ai dit, les tempêtes sont fréquentes ici. Je ne me souviens que d'une seule tentative de quitter cet endroit - cinq citoyens avaient construit une chaloupe décente avec des voiles et des rames.\nIls ont combattu le courant pendant plusieurs heures avant de finalement atteindre le large. Quelques jours plus tard, l'un d'eux est revenu à l'anneau extérieur... attaché à l'épave d'un mât et mort. Cela a tué le désir des autres de faire de telles choses audacieuses.";
			link.l1 = "Compris...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "C'est bien. Ce n'est pas pire que d'être le serviteur de cette arrogante famille d'usuriers. Il suffit de s'habituer à cet endroit et après cela, vous pourriez même l'aimer. D'ailleurs, je ne suis pas le seul à penser ainsi. Et les clans... ils ne me dérangent pas.";
			link.l1 = "Intéressant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Bien sûr, nous achetons. Oh, capitaine, il y a assez de travail pour une fille : nettoyage, cuisine, aider les autres... nous ne restons pas les bras croisés, mais personne ne se casse le dos ici. Les pirates vendent la nourriture à bas prix pour les citoyens ordinaires, contrairement aux clans. Alors nous ne mourons pas de faim.\nJ'aide Gillian et Natalie et elles m'aident si j'en ai besoin. Nous sommes amies. Il y a une autre fille sur l'Île, l'Espagnole. Elle s'appelle Ramona mais elle est souvent seule et nous ne sommes pas vraiment pressées de devenir amies avec elle.";
			link.l1 = "Et pourquoi donc ?";
			link.l1.go = "ansewer_4_1";
		break;
		
		case "ansewer_4_1":
			dialog.text = "Eh bien... disons que nous avons des points de vue différents sur la vie. Parle-lui et tu comprendras.";
			link.l1 = "Intéressant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Que fais-tu là, hein? Voleur!","Regarde-moi ça ! Dès que je me suis perdu dans mes pensées, tu as décidé d'examiner mon coffre !","Tu as décidé de fouiller mes coffres ? Tu ne t'en sortiras pas comme ça !");
			link.l1 = "Merde!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Quoi ?! Tu as décidé de fouiller mes coffres ? Tu ne t'en tireras pas comme ça !";
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
			dialog.text = LinkRandPhrase("Écoute, tu ferais mieux de ranger ton arme. Ça me rend nerveux.","Vous savez, courir avec une lame n'est pas toléré ici. Rangez-la.","Ecoute, ne fais pas le chevalier médiéval courant avec une épée. Range-la, ça ne te convient pas...");
			link.l1 = LinkRandPhrase("D'accord.","Comme vous le souhaitez...","Comme vous dites...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ecoutez, je suis citoyen de la ville et je vous demanderais de rengainer votre lame.","Ecoutez, je suis citoyen de la ville et je vous demanderais de ranger votre lame.");
				link.l1 = LinkRandPhrase("D'accord.","Comme tu le souhaites...","Comme vous dites...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sois prudent, mon ami, en courant avec une arme. Je pourrais m'énerver...","Je n'aime pas quand des hommes marchent devant moi avec leur arme prête. Cela me fait peur...");
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
