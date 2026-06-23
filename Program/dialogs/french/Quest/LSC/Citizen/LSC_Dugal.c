// Дугал Эббот - дворянин
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
				dialog.text = "Salutations, monsieur. Permettez-moi de me présenter - Dougall Abbot. Cela fait plaisir de voir un homme noble ici. Je suis las des paysans locaux. Je n'aurais jamais imaginé devoir passer le reste de ma vie parmi des gens du commun.";
				link.l1 = TimeGreeting()+". Mon nom est "+GetFullName(pchar)+"Enchanté de vous rencontrer. Et pourquoi n'aimez-vous pas les habitants ?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+" ! Tu veux quelque chose ? ";
				link.l1 = LinkRandPhrase("As-tu quelque chose d'intéressant à dire ?","Quelque chose de nouveau s'est-il passé sur l'île ?","Voulez-vous me raconter les derniers potins ?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Je voudrais vous poser quelques questions sur l'île.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Je voulais juste savoir comment tu vas. À bientôt !";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Tu ne les connais pas bien. Es-tu juste arrivé ici ? Je ne me souviens pas de naufrages récents pourtant...";
			link.l1 = "Je suis venu ici sur une petite barque...";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Oui, cela arrive souvent - les navires coulent et seuls quelques survivants arrivent ici sur les chaloupes de leurs navires. Parfois, des gens vivent ici pendant des mois sans que vous ne les rencontriez jamais.";
			link.l1 = "Je vois. Ce fut un plaisir de vous rencontrer, monsieur Abbot. À bientôt !";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("As-tu quelque chose d'intéressant à dire ?","Quelque chose de nouveau s'est-il passé sur l'île ?","Pourriez-vous me raconter les derniers potins ?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Je voudrais vous poser quelques questions sur l'île.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Je vous écoute.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Et comment es-tu arrivé ici ?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Que pouvez-vous me dire sur les habitants ?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Que peux-tu me dire sur les clans ?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Et au sujet du temps ? Les tempêtes sont-elles fréquentes ici ?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Pas de questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Il y a cinq ans, mais je m'en souviens parfaitement comme si c'était hier. Un jour funeste, j'avais décidé de naviguer sur ma flûte de Port Royal à Belize, il y avait une cargaison trop précieuse pour faire confiance à d'autres pour l'affaire\nLe lendemain, mes mésaventures ont commencé, d'abord, notre maître d'équipage s'est saoulé et est tombé par-dessus bord, puis nous avons failli heurter les récifs et à la fin notre navigateur a fait une erreur, donc nous avons navigué dans la mauvaise direction\nEnsuite, nous avons été poursuivis par un brigantin et un galion. Nous avons essayé de fuir, mais ils étaient insistants. Le galion a été laissé derrière mais le brigantin nous a finalement rattrapés\nLe galion était trop loin de là, alors nous avons abordé le brigantin sans tirer. Ces chiens espagnols ne s'y attendaient pas et nous avons gagné, mais la plupart de mon équipage était mort\nQuelques heures plus tard, la tempête nous a pris, nous ne pouvions pas combattre le temps avec si peu d'équipage et maintenant tu vois le résultat. Ma flûte est quelque part sur l'anneau extérieur, moi et les trois autres survivants sommes arrivés ici.";
			link.l1 = "Compris...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Racaille. Tous autant qu'ils sont. Des vauriens de toute sorte. Richard Shambon est un criminel, ça se lit sur son visage. Kassel ? Tuer des gens pour lui, c'est aussi naturel que respirer. Jasper Pratt est un bagnard. Musket est un ivrogne. Dois-je vraiment continuer ?\nJosef Loderdale est le seul homme décent ici, à part vous, c'est un ancien militaire de la marine anglaise. Il y a deux nobles ici - Antonio Betancourt et Lorenzo Solderra, fichue racaille espagnole, je ne m'assoirai même pas à la même table que lui.";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Une bande de salauds et de racaille. Ils ne nous font pas de mal cependant. Ils sont plus intéressés à se poignarder et se tirer dessus entre eux. Ils ne peuvent pas vivre sans cela. Je n'aime pas non plus les pirates, mais je dois admettre qu'ils ont rendu l'Île un endroit plus paisible en arrivant ici.";
			link.l1 = "Intéressant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Ils ne le font jamais. Des tempêtes surviennent souvent autour de l'Île, mais cet endroit est toujours calme et tranquille, c'est peut-être une sorte de magie ou la volonté de Dieu, je ne sais pas. Un vent fort peut parfois atteindre cet endroit et c'est tout. Les pluies ne peuvent causer aucun dégât non plus.";
			link.l1 = "Intéressant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Que fais-tu là, hein ? Voleur !","Regardez-moi ça ! A peine avais-je perdu dans mes pensées que vous avez décidé de fouiller mon coffre !","Décidé à fouiller mes coffres ? Tu ne t'en sortiras pas ainsi !");
			link.l1 = "Merde !";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Quoi?! Tu as décidé de fouiller dans mes coffres ? Tu ne t'en tireras pas comme ça !";
			link.l1 = "Fille insensée!";
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
			dialog.text = LinkRandPhrase("Ecoute, tu ferais mieux de ranger ton arme. Cela me rend nerveux.","Tu sais, courir avec une lame n'est pas toléré ici. Range-la.","Ecoute, ne joue pas au chevalier médiéval courant avec une épée. Range-la, cela ne te sied point...");
			link.l1 = LinkRandPhrase("D'accord.","Très bien.","Comme vous dites...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"« Écoutez, je suis citoyen de la ville et je vous demanderais de rengainer votre lame. »","Écoutez, je suis citoyen de la ville et je vous demanderais de rengainer votre lame.");
				link.l1 = LinkRandPhrase("D'accord.","Peu importe alors.","Comme vous dites...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sois prudent, mon gars, en courant avec une arme. Je pourrais devenir nerveux...","Je n'aime pas quand des hommes marchent devant moi avec leur arme prête. Ça me fait peur...");
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
