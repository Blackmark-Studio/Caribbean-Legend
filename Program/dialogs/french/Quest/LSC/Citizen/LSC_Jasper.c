// Джаспер Пратт - каторжник
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
				dialog.text = "Je ne veux pas te parler. Tu attaques des civils paisibles sans raison et les provoques à se battre. Déguerpis !";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Bonne journée, monsieur. Vous désirez quelque chose ?";
				link.l1 = TimeGreeting()+". Mon nom est "+GetFullName(pchar)+", et quel est le vôtre ? Je suis nouveau ici...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"Veux-tu quelque chose ?";
				link.l1 = LinkRandPhrase("Tu as quelque chose d'intéressant à dire ?","Y a-t-il eu des nouveautés sur l'île ?","Veux-tu me raconter les derniers potins ?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Je voudrais vous poser quelques questions sur l'île.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Je voulais juste savoir comment tu vas. À bientôt!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Moi ? Je suis Jasper, l'ancien bagnard. C'est pour cela que les gens me regardent de travers. Ah, qu'ils aillent au diable, je m'y suis habitué...";
			link.l1 = "Je me moque de qui tu étais, qui tu es maintenant est ce qui compte.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "C'est bien dommage que tout le monde ne pense pas comme vous, monsieur.";
			link.l1 = "Eh bien, je suis connu pour mon attitude libérale...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Content pour vous. Ne vous inquiétez pas, malgré mon passé, je ne suis pas une menace pour les bourses et les coffres des habitants de L'Île Justice. Je suis heureux de pouvoir enfin vivre en paix.";
			link.l1 = "Ravi de te rencontrer, Jasper. À bientôt !"link.l1.go ="sortir";
			link.l2 = LinkRandPhrase("Tu as quelque chose d'intéressant à dire ?","Y a-t-il eu du nouveau sur l'île ?","Me raconterez-vous les derniers potins ?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Je veux te poser quelques questions sur l'île.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Oui, bien sûr. Je te répondrai si je peux. Demande.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Comment es-tu devenu habitant de l'Île Justice ?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Aimez-vous cet endroit ?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Vous avez mentionné que les gens vous regardent de travers. Est-ce à cause de votre passé ?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Cette île est assez intéressante, n'est-ce pas ?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Aucune question. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Je me suis enfui d'une plantation cubaine. Nous étions cinq et nous avons décidé qu'il valait mieux mourir que de continuer à se briser le dos pour des coups. Nous avons réussi à tromper les gardes et à disparaître dans la jungle, puis nous avons atteint la côte et construit un radeau\nNous voulions atteindre Tortuga mais le destin en a décidé autrement. Aucun de nous ne savait naviguer, alors nous nous sommes perdus. Ensuite, l'eau s'est épuisée... Je ne veux pas me souvenir de cela. Finalement, j'étais le seul à atteindre l'Île et à survivre.";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Tu sais, moi, ça me va. Après tout ce que j'ai traversé sur la plantation, cet endroit me semble être un paradis. Je n'ai pas besoin de grand-chose... Un peu de nourriture, de l'eau et un verre de rhum chaque soir. Personne ne me dérange ici et je n'ai pas l'intention de quitter cet endroit. Je mourrai ici quand mon heure viendra.";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "La chose est que l'Île est un terrain de jeu pour un mystérieux voleur. Les serrures ne sont pas un problème pour lui. Il traîne surtout autour des chambres de l'amiral. Cependant, nos coffres ne restent pas intacts non plus. Personne ne sait qui est ce voleur, alors ils soupçonnent les gens avec... hm, un passé criminel.\nLe voleur est un peu étrange cependant : d'abord, il ne prend que des bouteilles d'alcool et quelques babioles, il ne prend jamais d'objets de valeur. Drôle, n'est-ce pas ?";
			link.l1 = "Compris...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Oui, je suis d'accord. J'ai beaucoup nagé autour des navires intérieurs de L'Île Justice. Il y a très peu de sorties de l'eau. San Augustin, le pont. Gloria, le mât tombé. Si tu nages près de la plateforme Fenix et ensuite autour de Ceres Smitie, tu atteindras la cabine de Mary Casper à la proue du navire\nLa faille de Tartarus te mènera à la prison. Il y a un trou dans la proue de San Augustine, tu pourrais entrer dans la salle de stockage de l'amiral, mais c'est une action déconseillée. La porte la plus basse de Tartarus est souvent fermée, souviens-t'en\n Et bien sûr, tu peux entrer dans Fernanda, c'est la flûte solitaire et déchirée. On dit que personne n'y habite, mais je remarque souvent des lumières dans la cabine et parfois j'entends des chansons et des cris étranges et ivres.";
			link.l1 = "Intéressant... Je dois explorer davantage cet endroit.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Que fais-tu là, hein ? Voleur !","Regarde-moi ça ! Dès que je me suis perdu dans mes pensées, tu as décidé de fouiller dans mon coffre !","Décidé à fouiller mes coffres ? Tu ne t'en tireras pas comme ça !");
			link.l1 = "Merde !";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Quoi ?! Tu as décidé de fouiller dans mes coffres ? Tu ne t'en sortiras pas comme ça !";
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
			dialog.text = LinkRandPhrase("Ecoute, tu ferais mieux de ranger ton arme. Ça me rend nerveux.","Tu sais, courir avec une lame n'est pas toléré ici. Range-la.","Écoute, ne joue pas au chevalier médiéval courant avec une épée. Range-la, ça ne te va pas...");
			link.l1 = LinkRandPhrase("D'accord.","Peu importe alors.","Comme tu dis...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ecoute, je suis citoyen de la ville et je te demande de ranger ta lame.","Écoutez, je suis citoyen de la cité et je vous demanderais de rengainer votre épée.");
				link.l1 = LinkRandPhrase("D'accord.","Quoi qu'il en soit.","Comme vous dites...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sois prudent, l'ami, en courant avec une arme. Je pourrais devenir nerveux...","Je n'aime pas quand les hommes marchent devant moi avec leur arme prête. Ça me fait peur...");
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
