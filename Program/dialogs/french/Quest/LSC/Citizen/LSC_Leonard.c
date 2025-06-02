// Леонард Маскетт - пьяница
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iPeso, iDubl;
	string sPeso, sDubl;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Je ne veux pas te parler. Tu attaques des civils pacifiques sans raison et les provoques à se battre. Déguerpis !";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			// --> пей до дна
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_3") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.facio"))
			{
				dialog.text = "Ami, tu arrives juste à temps... Je veux te parler... d'une affaire. Une affaire importante.";
				link.l1 = "Vraiment? On dirait que tu n'es pas ivre. Est-ce que quelque chose s'est passé? C'est inhabituel de te voir sobre.";
				link.l1.go = "facio";
				break;
			}
			// <-- пей до дна
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "A-a... hic! Salut, l'ami...";
				link.l1 = TimeGreeting()+" On dirait que tu en as déjà assez, l'ami.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+" ! Hic ! Que veux-tu ? ";
				link.l1 = LinkRandPhrase("As-tu quelque chose d'intéressant à raconter ?","Y a-t-il quelque chose de nouveau qui s'est passé sur l'île ?","Me raconteras-tu les derniers potins ?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Je veux te poser quelques questions sur l'île.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Je voulais juste savoir comment tu vas. À bientôt!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ouais! Assez? N-non! Je suis un ivrogne fou, hi-hic! Oui, Leonard Musket est saoul et c'est une bonne chose!";
			link.l1 = "Amateur de boissons, hein ? Oui, mon nom est "+GetFullName(pchar)+"Enchanté de faire votre connaissance.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Si vous le dites. Nous tous ici... hic, nous rencontrons les uns les autres.";
			link.l1 = "D'accord, on dirait que tu n'es pas d'humeur à parler. À bientôt !";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Tu as quelque chose d'intéressant à raconter ?","Y a-t-il eu du nouveau sur l'île ?","Me raconterez-vous les derniers potins ?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Je veux te poser quelques questions sur l'île.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		// --> пей до дна
		case "facio":
			dialog.text = "Oui, camarade, je suis presque à jeun. Et c'est parce que j'ai une affaire pour toi, une affaire importante. Et il semble que tu puisses t'en occuper...";
			link.l1 = "Quoi ? Qu'as-tu en tête ? Parle et ne gaspille pas mon temps pour rien !";
			link.l1.go = "facio_1";
			npchar.quest.facio = "true";
		break;
		
		case "facio_1":
			dialog.text = "Mon gars, veux-tu gagner de l'argent? Des pesos d'argent, des doublons d'or? Je vais te dire comment. Mais tu devras partager avec moi - nous travaillerons ensemble.";
			link.l1 = "Je le veux toujours. Mais tout dépend de ta proposition : je ne fais aucun travail, même très lucratif.";
			link.l1.go = "facio_2";
		break;
		
		case "facio_2":
			dialog.text = "Le commerce n'est pas vraiment légal, c'est sûr, mais il est rentable... et nous pourrons punir un homme qui est devenu trop exigeant. Il ne finira pas pauvre, il a trop d'argent. Tout le monde partage avec lui, alors c'est à son tour de faire de même maintenant. Dis-moi, peux-tu tenir le rhum ? Combien es-tu capable de boire avant de finir sous la table ?";
			link.l1 = "Ça dépend. Je ne suis pas sûr d'avoir l'habitude des beuveries folles... Vas-tu enfin me raconter les détails ?";
			link.l1.go = "facio_3";
		break;
		
		case "facio_3":
			dialog.text = "J'en viens au fait, tu ne le vois juste pas encore. Bien. Je vais être précis. Il y a un gros salaud moche sur l'Île - Giuseppe Fazio. Une ordure rare. Il écorche vifs les Narvals, les Rivados et les habitants. Je l'ai observé pendant un moment et enfin j'ai quelque chose. \nIl y a deux coffres dans sa cabine en Caroline : le premier contient des papiers, le second contient de l'or et de l'argent. Ils sont tous deux verrouillés avec des clés différentes. Le gros homme garde toujours les clés sur lui.";
			link.l1 = "Eh bien, il semble que tu vas voler Fazio ? Je ne participerai pas à cela. Et tu devrais être heureux que je ne le dise à personne. Si tu veux fouiller dans le coffre du gros, tu devrais trouver un autre partenaire.";
			link.l1.go = "facio_exit";
			link.l2 = "Ha ! Intéressant ! Continue...";
			link.l2.go = "facio_4";
		break;
		
		case "facio_exit":
			dialog.text = "Hélas, vraiment hélas... Il y a beaucoup d'or, assez pour nous deux. Bon, à la prochaine...";
			link.l1 = "Adieu.";
			link.l1.go = "exit";
		break;
		
		case "facio_4":
			dialog.text = "Deux portes mènent à sa cabine. L'une d'elles est toujours verrouillée. Mais la clé qui ouvre le coffre avec l'or ouvre aussi la porte. Je ne sais pas quel est le but de tout cela, mais c'est un fait. Il ne vous faut qu'une clé pour ouvrir la cabine et obtenir l'or. Une question logique s'ensuit - comment acquérir la clé ? Alors, j'ai un plan\nUn plan excellent, si tout se passe bien, Fazio ne réalisera jamais ce qui s'est passé ni à qui en vouloir. Ils penseront que c'était le mystérieux voleur. Le problème, c'est que j'ai besoin d'un partenaire avec une tête de fer pour mener à bien l'affaire. Suivez-vous ?";
			link.l1 = "Je t'écoute. Continue.";
			link.l1.go = "facio_5";
		break;
		
		case "facio_5":
			dialog.text = "Fazio aime s'asseoir chez Sancho et boire un bon coup, mais sa corpulence est trop lourde pour que le rhum fasse son effet. Alors, il a inventé un jeu à boire - un jeu où les gens essaient de le surpasser en beuverie. Si tu lui proposes de jouer à ce jeu, il acceptera sans aucun doute\nEt c'est là que ça devient amusant. Tu fais un pari avec lui, tu vas à la taverne, tu prends du rhum et tu bois jusqu'à ce que l'un d'entre vous embrasse la table. Si tu échoues, alors tout le plan est fichu, je ne pourrai pas le faire seul\nC'est pourquoi je te demandais à propos de ta résistance à l'alcool. Si tu fais couiner et grogner Fazio comme un cochon, alors considère que c'est fait. Je serai dans les parages tout le temps. Quand il aura fini, je prendrai ses clés\nEnsuite, nous déplacerons le gros homme vers un lit à l'étage et nous nous faufilerons dans sa cabine pendant qu'il dort. Je remettrai la clé juste après avoir pillé son coffre, il ne se rendra même pas compte qu'il a été volé\nJe m'occuperai de récupérer et de rendre la clé, ta mission est de saouler Fazio et de te faufiler dans sa propriété. Je resterai en garde au cas où quelqu'un apparaîtrait, donc tu auras assez de temps pour t'enfuir par la porte de derrière\nNous partagerons le contenu du coffre moitié-moitié, ce serait juste. Alors, tu es partant ?";
			link.l1 = "Beau plan ! Bien sûr, essayons !";
			link.l1.go = "facio_6";
			link.l2 = "Non, l'ami. Je passe. Je crains de ne pas pouvoir boire assez pour rester debout et surpasser Fazio. Trouve un autre partenaire, un peu plus fort que moi.";
			link.l2.go = "facio_exit";
		break;
		
		case "facio_6":
			dialog.text = "Je suis heureux d'avoir eu raison à ton sujet. Maintenant, va voir Fazio et organise une rencontre à la taverne ce soir après neuf heures. J'espère que tu feras boire ce cochon. Bonne chance et à ce soir !";
			link.l1 = "Je vais essayer... Adieu !";
			link.l1.go = "facio_7";
		break;
		
		case "facio_7":
			DialogExit();
			NextDiag.CurrentNode = "facio_wait";
			pchar.questTemp.LSC.Drink = "begin";
			pchar.questTemp.LSC.Drink.Chance = hrand(100); // итог бухалова
			if (CheckAttribute(pchar, "questTemp.CanDrink")) pchar.questTemp.LSC.Drink.Chance = sti(pchar.questTemp.LSC.Drink.Chance)+50;
			SetFunctionTimerCondition("LSC_DrinkOver", 0, 0, 3, false); // 3 дня
			AddQuestRecord("LSC_Drink", "1");
		break;
		
		case "facio_wait":
			dialog.text = "Mon ami, je compte sur toi. Fais boire à ce gros homme...";
			link.l1 = "Bien sûr...";
			link.l1.go = "exit";
			NextDiag.TempNode = "facio_wait";
		break;
		
		case "result_0":
			dialog.text = "C'est fait, ce gros porc dort à l'étage. J'ai la clé. Tu t'en sors bien, tu sembles assez sobre !";
			link.l1 = "Est-ce vrai ? Il y a longtemps que je ne me suis pas saoulé à ce point. Je me sens un peu étourdi... Allons-y ?";
			link.l1.go = "result_win";
		break;
		
		case "result_1":
			dialog.text = "C'est fait, ce gros cochon dort à l'étage. J'ai la clé. Tu t'en sors bien, tu as vraiment réussi à abreuver ce cochon...";
			link.l1 = "Je l'ai fait, mais cela fait longtemps que je n'ai pas été aussi ivre. Ma tête tourne... Allons-y alors ?";
			link.l1.go = "result_win";
		break;
		
		case "result_2":
			dialog.text = "Eh, l'ami, tu n'as pas réussi à boire plus que le gros homme... Dommage. Eh bien, au moins nous avons essayé...";
			link.l1 = "Sa-satané, il est comme un... tonneau s-s-sans fond. Argh, j'ai besoin de r-repos... C'est fini, p-partez! Hips!..";
			link.l1.go = "result_fail";
		break;
		
		case "result_win":
			dialog.text = "Oui. Allons-y ! Suivez-moi jusqu'à 'Carolina' ! Et ne traînez pas, nous n'avons pas beaucoup de temps !";
			link.l1 = "Allons-y !";
			link.l1.go = "result_win_1";
		break;
		
		case "result_win_1":
			DialogExit();
			NextDiag.CurrentNode = "result_win_2";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload6", "LostShipsCity_town", "reload", "reload39", "LSC_DrinkGotoCarolina", -1);
			AddQuestRecord("LSC_Drink", "3");
		break;
		
		case "result_win_2":
			pchar.quest.LSC_Drink1.over = "yes"; //снять таймер
			dialog.text = "Tiens. Prends la clé. Le coffre dont tu as besoin est à gauche de l'entrée. Prends autant que tu peux rapidement. N'oublie pas de le verrouiller à nouveau. Si je vois quelque chose, je frapperai trois fois à la porte. Dans ce cas, fuis par la galerie arrière.";
			link.l1 = "Soit. Restez sur vos gardes !";
			link.l1.go = "result_win_3";
		break;
		
		case "result_win_3":
			DialogExit();
			GiveItem2Character(pchar, "key_facioQ");
			NextDiag.CurrentNode = "result_grabbing";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload25", "LSC_DrinkGotoCarolina_3", -1);
		break;
		
		case "result_grabbing":
			// считаем деньги и дублоны взятые из сундука
			iPeso = sti(pchar.money)-sti(pchar.questTemp.LSC.Drink.Money);
			iDubl = GetCharacterItem(pchar, "gold_dublon")-sti(pchar.questTemp.LSC.Drink.Dublon);
			if (iPeso <= 0) sPeso = "not a single peso";
			else sPeso = ""+FindRussianMoneyString(iPeso)+"";
			if (iDubl <= 0) sDubl = "not a single doubloon";
			else sDubl = ""+iDubl+" doubloons";
			if (iPeso <= 10000 && iDubl <= 10) sTotalTemp = "What a miserable loot... And were we risking for it? Eh... Fine, let's share what we have got.";
			else
			{
				if (iPeso <= 50000 && iDubl <= 100) sTotalTemp = "I thought that there will be much more... Risk wasn't worth it. Eh... Fine, let's share what we have got.";
				else
				{
					if (iPeso <= 100000 && iDubl <= 300) sTotalTemp = "Hm. Not bad. But I thought that we will get more. Fine, let's share it.";
					else 
					{
						if (iPeso <= 150000 && iDubl <= 500) sTotalTemp = "Excellent! We have done well, partner! This is a whole lot of coins! Let's share!";
						else
						{
							sTotalTemp = "Wow! I haven't ever thought that the fat man's stash is so huge. Well done, partner! Let's share!";
						}
					}
				}
			}
			dialog.text = "Enfin ! Qu'as-tu réussi à prendre du coffre de ce scélérat ? Montre-moi, j'attends avec impatience !";
			if (iPeso <= 0 && iDubl <= 0)
			{
				link.l1 = "Il n'y avait rien du tout. Juste quelques morceaux, des amulettes et ce genre de choses.";
				link.l1.go = "grabbing_0";
			}
			else
			{
				link.l1 = "J'ai pris du coffre "+sPeso+" et "+sDubl+"Bonjour, monami.";
				link.l1.go = "grabbing_1";
			}
		break;
		
		case "grabbing_0":
			dialog.text = "Impossible ! Il semble que tout cela n'était pour rien... Peut-être que ce salaud a mis son magot dans un autre coffre. Eh ! Très bien, donne-moi la clé et je la rendrai à son propriétaire avant qu'il ne s'en aperçoive. Adieu, l'ami...";
			link.l1 = "...";
			link.l1.go = "grabbing_exit";
			AddQuestRecord("LSC_Drink", "6");
		break;
		
		case "grabbing_1":
			dialog.text = sTotalTemp;
			link.l1 = "Partageons...";
			link.l1.go = "grabbing_part";
		break;
		
		case "grabbing_part":
			iPeso = makeint((sti(pchar.money)-sti(pchar.questTemp.LSC.Drink.Money))/2);
			iDubl = makeint((GetCharacterItem(pchar, "gold_dublon")-sti(pchar.questTemp.LSC.Drink.Dublon))/2);
			AddMoneyToCharacter(pchar, -iPeso);
			RemoveItems(pchar, "gold_dublon", iDubl);
			Log_Info("You have given "+iDubl+" doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Très bien, donne-moi la clé et je la rendrai à son propriétaire avant qu'il ne s'en aperçoive. Adieu, camarade...";
			link.l1 = "Bonne chance, l'ami...";
			link.l1.go = "grabbing_exit";
			AddSimpleRumourCityTip("Fazio was complaining that someone has cleaned out his chest. It seems that the mysterious thief did that.", "LostShipsCity", 3, 1, "LSC", "");
			AddSimpleRumourCityTip("Have you heard? Fazio was robbed! He was robbed while being drunk after having a game with you.", "LostShipsCity", 3, 1, "LSC", "");
			AddSimpleRumourCityTip("You have a strong head! To drink so much rum and stay on your own feet! That 's something...", "LostShipsCity", 3, 2, "LSC", "");
			AddQuestRecord("LSC_Drink", "5");
		break;
		
		case "grabbing_exit":
			DialogExit();
			RemoveItems(pchar, "key_facioQ", 1);
			int n = Findlocation("CarolineBank");
			locations[n].private2.QuestClosed = true; // запираем сундук
			LocatorReloadEnterDisable("CarolineBank", "reload1", false); // на галерею
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload38", "FleuronTavern", "goto", "goto2", "OpenTheDoors", 15.0);
			pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink4.win_condition.l1.date.hour  = sti(GetTime()+5);
			pchar.quest.LSC_Drink4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
		break;
		
		case "result_fail":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "LostShipsCity_town", "goto", "goto05_2", "", 10);
			chrDisableReloadToLocation = false;//открыть локацию
			n = Findlocation("CarolineBank");
			locations[n].private2.QuestClosed = true; // запираем сундук
			pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink4.win_condition.l1.date.hour  = sti(GetTime()+5);
			pchar.quest.LSC_Drink4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
			AddQuestRecord("LSC_Drink", "4");
		break;
		// <-- пей до дна
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Vraiment?... hic! J'écoute...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Comment as-tu fini ici ?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Tu bois toujours ? Et où trouves-tu des pièces pour te payer des coups ?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Que pouvez-vous me dire sur les habitants?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Voudriez-vous quitter cet endroit et rejoindre le continent ?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Pas de questions. Pardonnez-moi...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Eh bien ! Je jure, je ne me souviens pas. Oui, oui, je ne me souviens pas ! C'était il y a longtemps. Je naviguais quelque part d'une manière ou d'une autre et j'ai finalement échoué ici. Hic !";
			link.l1 = "Hm... Très bien, très bien.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Oui, je suis un ivrogne... Je bois, bon sang, parce que je n'ai plus rien à faire... Tu vois, mon ami, j'en ai fini. La bouteille de rhum est la seule chose que je désire. Alors je continuerai à boire. Et l'argent... hé-hé, le rhum ne coûte pas cher. De toute façon, je n'ai même pas besoin de l'acheter. \nIl y a un endroit rempli de rhum, mais il faut nager pour l'obtenir, c'est pourquoi je n'achète du rhum que quand je suis trop saoul pour nager... hic ! Jizjezezejizeze, non, je ne te dirai pas où nager, hé-hé, ne demande même pas...";
			link.l1 = "Merveilleux.";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Que puis-je dire, hic... à leur sujet ? De bonnes personnes pour parler et boire. Giuseppe Fazio est un homme si important, un grand ponte local, ses coffres sont remplis d'or... et pourtant il respecte le vieux Leo, lui offre des boissons à la taverne. Bien qu'il demande parfois quelque chose en retour, mais ce n'est rien, hic !\nHeh, ne sais-tu pas combien de doublons Fazio possède, aha-ha-ha ! Assez pour passer le reste de ta vie dans la meilleure maison de tout les Caraïbes, sans travailler et en buvant le meilleur rhum du monde. Mais il reste ici, sur l'Île. Il semble que ce n'est toujours pas assez d'argent pour lui...";
			link.l1 = "Compris...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
			SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;
		
		case "ansewer_4":
			dialog.text = "Partir ? Hic ! Pourquoi ? Non, je ne veux aller ni sur le continent ni sur l'île misérable. Y a-t-il du rhum gratuit ? Non ! Il n'y a pas de rhum gratuit, hic ! Et cela signifie qu'il n'y a rien à faire pour moi là-bas... Pote, je me sens bien ici. Je vais te dire plus - demande aux gens s'ils veulent quitter cet endroit. Personne ne le veut, sauf deux ou trois, hic !";
			link.l1 = "Intéressant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Que fais-tu là, hein? Voleur!","Regarde-moi ça ! Dès que j'étais perdu dans mes pensées, tu as décidé de fouiller dans mon coffre !","Tu as décidé de fouiller mes coffres ? Tu ne t'en sortiras pas comme ça !");
			link.l1 = "Merde !";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Quoi?! Tu as décidé de fouiller dans mes coffres ? Tu ne t'en sortiras pas comme ça !";
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
			link.l1 = LinkRandPhrase("D'accord.","D'accord.","Comme tu dis...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Écoutez, je suis citoyen de la ville et je vous demanderais de rengainer votre épée.","Écoutez, je suis citoyen de la ville et je vous demanderais de ranger votre lame.");
				link.l1 = LinkRandPhrase("Très bien.","D'accord.","Comme vous dites...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sois prudent, mon gars, en courant avec une arme. Je pourrais m'agiter...","Je n'aime pas quand des hommes marchent devant moi, arme à la main. Ça me fait peur...");
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
