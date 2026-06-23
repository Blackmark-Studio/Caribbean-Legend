// Ришард Шамбон - контрабандист
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

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
				dialog.text = "Je ne veux pas te parler. Tu attaques des civils paisibles sans raison et les provoques pour qu'ils se battent. Va-t'en !";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			// --> кольцо
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_2") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.ring"))
			{
				dialog.text = "Oh ! Te voilà, l'ami. Et je pensais te trouver moi-même. J'ai besoin de toi, camarade.";
				link.l1 = "Tu es étrangement amical aujourd'hui, Richard. Eh bien, je t'écoute.";
				link.l1.go = "ring";
				break;
			}
			// <-- кольцо
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Que voulez-vous ? Pour être honnête, je ne suis pas de bonne humeur aujourd'hui. En fait, j'ai oublié quand j'étais de bonne humeur pour la dernière fois.";
				link.l1 = "Est-ce vraiment si mauvais, mon pote ?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"Tu veux quelque chose ?";
				link.l1 = LinkRandPhrase("As-tu quelque chose d'intéressant à dire ?","Y a-t-il eu des nouveautés sur l'île ?","Voudrais-tu me raconter les derniers potins ?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Je veux te poser quelques questions sur l'île.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Je voulais juste savoir comment tu vas. À bientôt !";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Mauvais? Non, ce n'est pas mauvais. Je ne suis simplement pas d'humeur. Alors, que voulais-tu?";
			link.l1 = "Je voulais juste vous connaître. Je suis un nouveau venu ici, alors je me promène sur l'Île et fais connaissance avec les gens.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Vraiment? Très bien alors. Je suis Richard Shambon. Il y a longtemps, j'ai échangé des biens précieux et certains étaient illégaux, mais cela fait neuf ans que je récupère les épaves de navires, cherchant des débris pour les échanger contre de la nourriture et de l'or.";
			link.l1 = "Et je suis "+GetFullName(pchar)+", un capitaine...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Tu veux dire l'ex-capitaine, ha-ha ?";
			link.l1 = "Eh bien, en fait, mon navire est à Blueweld maintenant. Et j'ai navigué ici sur une tartane.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Vraiment ? Impossible ! Et où est ta tartane maintenant ?";
			link.l1 = "Hm... au fond.";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "A-ah... Et je pensais... Peu importe, l'ami, je ferais mieux de boire un peu de rhum...";
			link.l1 = "Bonne chance avec ça. C'était agréable de parler avec vous. À bientôt !";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("As-tu quelque chose d'intéressant à dire ?","Y a-t-il du nouveau sur l'île ?","Me raconterez-vous les derniers potins ?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Je veux te poser quelques questions sur l'île.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		// Кольцо
		case "ring":
			dialog.text = "Et étais-je différent avant? Allons, j'ai eu de mauvais jours, tout le monde en a parfois! Dis-moi, il y a des rumeurs sur l'Île que tu es un excellent combattant. Est-ce vrai?";
			link.l1 = "Je ne sais pas ce qu'ils disent, mais je sais manier une épée si c'est ce que tu demandes.";
			link.l1.go = "ring_1";
			npchar.quest.ring = "true";
		break;
		
		case "ring_1":
			dialog.text = "Je vois que ces rumeurs étaient vraies... Écoute, "+pchar.name+", vous vous souvenez que je vous parlais de l'anneau extérieur ? Et des objets précieux que vous pouvez y trouver ?";
			link.l1 = "Vous aimez tous parler de cette bague... Et vous dites tous la même chose.";
			link.l1.go = "ring_2";
		break;
		
		case "ring_2":
			dialog.text = "Que dire de plus, ha-ha ! Bien. J'en viens au fait. (abaissant la voix) J'ai trouvé un navire intact à l'anneau extérieur, il est en bon état, ce qui est assez rare\nLe navire est grand, une pinasse. Elle a été amenée ici il n'y a pas longtemps, environ deux mois ou même moins. Les autres ne l'ont pas encore trouvée, donc il y a une chance de gagner de l'argent en pillant ses cales et ses cabines.";
			link.l1 = "Bien, je suis content pour toi. Mais en quoi cela me concerne-t-il ? Veux-tu me demander de t'accompagner ?";
			link.l1.go = "ring_3";
		break;
		
		case "ring_3":
			dialog.text = "Exactement ! Ecoute. La proue de la pinasse est endommagée. Ces maudits crabes ont utilisé un trou pour entrer et ils ont construit un fichu nid à l'intérieur. Se faufiler à l'intérieur pendant qu'ils sont là n'est pas une option et je n'ai aucune idée de comment grimper jusqu'au pont supérieur. Je n'ai jamais été un bon combattant et je n'ai pas touché à une lame depuis des années, donc je ne pourrai pas tuer ces créatures tout seul. C'est pourquoi je suis venu te voir.";
			link.l1 = "Alors tu me proposes de tuer tous les crabes à l'intérieur de ce navire, n'est-ce pas ?";
			link.l1.go = "ring_4";
		break;
		
		case "ring_4":
			dialog.text = "Oui. Nous aurons un accord. Je te montrerai le chemin vers le navire et tu élimineras les crabes. Nous partagerons tout le butin que nous y trouverons. C'est un marché équitable - j'ai trouvé le navire et tu le nettoieras.";
			link.l1 = "Non, mon gars, cela ne m'intéresse pas. Ce n'est pas mon genre de me battre avec des crabes à l'intérieur d'un navire à moitié coulé pour des trophées douteux. Trouve-toi un autre gaillard téméraire qui ira te chercher des marrons du feu.";
			link.l1.go = "ring_exit";
			link.l2 = "Intéressant... Cela fait longtemps que je pensais à inspecter l'anneau extérieur. Marché conclu ! Je tuerai des crabes.";
			link.l2.go = "ring_5";
		break;
		
		case "ring_exit":
			dialog.text = "Dommage... Vous avez fait une erreur. Il y a beaucoup de choses juteuses dans les navires de l'anneau extérieur... Et personne n'a été sur ce navire auparavant. Bien, c'est votre souhait. Adieu...";
			link.l1 = "Adieu, l'ami...";
			link.l1.go = "exit";
		break;
		
		case "ring_5":
			dialog.text = "Je suis heureux d'avoir eu raison à votre sujet, ami. J'ai le pressentiment que nous trouverons beaucoup de choses intéressantes à l'intérieur d'elle...";
			link.l1 = "Nous verrons. Sais-tu combien de crabes y a-t-il ?";
			link.l1.go = "ring_6";
		break;
		
		case "ring_6":
			dialog.text = "Je pense à quatre ou cinq d'entre eux... Eh bien, en moyenne.";
			link.l1 = "Ça me convient. Quand partirons-nous?";
			link.l1.go = "ring_7";
		break;
		
		case "ring_7":
			dialog.text = "Allons-y demain, nous devons nous préparer. Obtiens des antidotes du frère Julian, les mâchoires de crabe sont venimeuses. La prudence est de mise. Rendez-vous demain à huit heures du matin sur le 'pont oblique'. Sais-tu où c'est ?";
			link.l1 = "Je ne comprends pas. Expliquez-vous.";
			link.l1.go = "ring_8";
		break;
		
		case "ring_8":
			dialog.text = "Il y a l'épave d'un vieux navire derrière le 'San Augustine'. Sa proue est sous l'eau et son arrière est levé haut. C'est pourquoi elle est appelée le 'pont oblique'. On ne peut y aller qu'en nageant. Il suffit de commencer à nager depuis l'endroit sous le pont et de faire demi-tour de n'importe quel côté du 'San Augustine'. Nous y nagerons ensemble à partir de là.";
			link.l1 = "D'accord. À demain !";
			link.l1.go = "ring_9";
		break;
		
		case "ring_repeat":
			dialog.text = "8 heures, 'pont oblique'...";
			link.l1 = "Oui, oui, je me souviens de cela...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_repeat";
		break;
		
		case "ring_9":
			DialogExit();
			NextDiag.CurrentNode = "ring_repeat";
			pchar.quest.LSC_Ring_Start.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.hour  = 7.0;
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Start.function = "LSC_RingStart"; // готовы
			pchar.quest.LSC_Ring_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.hour  = 10.0;
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Over.function = "LSC_RingOver"; // опоздание
			AddQuestRecord("LSC_Ring", "1");
		break;
		
		case "ring_10":
			dialog.text = "Aha, te voilà, l'ami. Prêt à préparer une salade de crabe ?";
			link.l1 = "Bien sûr !";
			link.l1.go = "ring_11";
		break;
		
		case "ring_11":
			dialog.text = "Très bien. Maintenant, tourne la tête vers l'anneau extérieur et regarde. Vois-tu là deux épaves de navires émerger de l'eau ?";
			link.l1 = "Hm... Oui, je le fais.";
			link.l1.go = "ring_12";
		break;
		
		case "ring_12":
			dialog.text = "Maintenant, regarde entre eux vers l'anneau extérieur. Vois-tu le galion avec l'étrave relevée ? Il est juste vers nous. Regarde attentivement.";
			link.l1 = "... ";
			link.l1.go = "ring_look";
		break;
		
		case "ring_look":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_ring");
			DoQuestCheckDelay("LSC_RingTalkLook", 6.0);
		break;
		
		case "ring_13":
			dialog.text = "";
			link.l1 = "Je crois que je le vois... Oui !";
			link.l1.go = "ring_13a";
		break;
		
		case "ring_13a":
			dialog.text = "C'est notre cible. Nage droit et ne tourne pas. Je te montrerai le chemin du retour quand nous atteindrons l'anneau extérieur. L'entrée de la cale est le trou dans la proue du navire. Sache que je n'y entrerai pas tant que tu n'auras pas tué tous les crabes.";
			link.l1 = " Oui, nous avions un accord hier, je m'en souviens. Tu montreras le navire et moi, je tuerai les crabes. Allons nager ?";
			link.l1.go = "ring_14";
		break;
		
		case "ring_14":
			dialog.text = "Bien sûr! Je te suivrai.";
			link.l1 = "...";
			link.l1.go = "ring_swim";
		break;
		
		case "ring_swim":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetImmortal(npchar, true);
			pchar.quest.LSC_Ring_enter.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_enter.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator = "reload_ring";
			pchar.quest.LSC_Ring_enter.function = "LSC_RingEnter";
			LSC_RingSetItems(); // раскладка итемзов
			AddQuestRecord("LSC_Ring", "3");
		break;
		
		case "ring_15":
			dialog.text = "Heh, bien joué ! Tu as tué toute cette racaille !";
			link.l1 = "Je me souviens que quelqu'un m'a parlé de 'quatre ou cinq' crabes... Rappelle-moi, qui a dit cela ?";
			link.l1.go = "ring_16";
		break;
		
		case "ring_16":
			dialog.text = "Mon ami, je ne suis jamais entré dans la cale pour les compter correctement. J'ai juste regardé par le trou. Je n'avais pas l'intention de te mentir.";
			link.l1 = "Quoi que ce soit. Allons vérifier la cale...";
			link.l1.go = "ring_17";
		break;
		
		case "ring_17":
			dialog.text = "Bien sûr ! C'est pour cela que nous sommes ici, n'est-ce pas ?";
			link.l1 = "Exactement ! Ne perdons pas notre temps...";
			link.l1.go = "ring_18";
		break;
		
		case "ring_18":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 60.0); // 1 минуту на пошариться
			npchar.quest.diagnode = "ring_19";
			AddQuestRecord("LSC_Ring", "4");
		break;
		
		case "ring_wait":
			dialog.text = "Attends un peu, camarade, je n'ai pas encore vérifié tous les endroits que je voulais. Cherche mieux, peut-être que tu trouveras plus de trésors.";
			link.l1 = "D'accord...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_wait";
		break;
		
		case "ring_19":
			dialog.text = "Rien de spécial. C'est dommage qu'il n'y ait pas de marchandises précieuses ici. Il y a des provisions dans les barils et du coprah dans les caisses. J'ai aussi trouvé une caisse avec du vin coûteux cependant. Et qu'as-tu trouvé ?";
			link.l1 = "Rien d'intéressant non plus. Quelques caisses sont assez précieuses, mais le reste c'est du corned-beef et du coprah comme vous l'avez dit.";
			link.l1.go = "ring_20";
		break;
		
		case "ring_20":
			dialog.text = "Pas assez... Allons en haut pour vérifier le pont supérieur et les cabines.";
			link.l1 = "Allons-y.";
			link.l1.go = "ring_21";
		break;
		
		case "ring_21":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Ring_deck.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_Ring_deck.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_Ring_deck.win_condition = "LSC_RingEnterDeck";
			for (i=1; i<=3; i++)
			{
				sld = ItemsFromID("purse"+i);
				sld.shown = true;
				sld.startLocation = "ExternalRingDeck";
				sld.startLocator = "item"+i;
			}
		break;
		
		case "ring_22":
			dialog.text = "Sacré nom d'un chien! Regarde-moi ça! Ces satanées saloperies de crabes ont envahi le pont! Et comment ont-ils réussi un tel tour?!";
			link.l1 = "Ne sois pas un lâche ! Reste ici, ne bouge pas et n'attire pas leur attention. Je vais m'occuper de ces créatures tout de suite...";
			link.l1.go = "ring_23";
		break;
		
		case "ring_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocator(npchar, "reload", "reload1", "", -1);
		break;
		
		case "ring_24":
			dialog.text = "Eh bien! Donc, les récits de votre talent à l'escrime étaient vrais! Si j'étais seul ici, je sauterais par-dessus bord...";
			link.l1 = "Écoute, et comment es-tu devenu un contrebandier autrefois, hein ? Ou tu fuyais tout le monde ?";
			link.l1.go = "ring_25";
		break;
		
		case "ring_25":
			dialog.text = "Compagnon, d'abord, j'étais plus jeune, plus fort et plus téméraire. Ensuite, je ne suis pas un mercenaire pour mener des guerres - je suis un contrebandier et nous essayons toujours d'éviter une effusion de sang. Troisièmement, j'ai toujours préféré les voiles et le gouvernail, pas les lames et les pistolets. Et enfin, des années à vivre ici m'ont adouci.   Alors ne m'en veux pas. Allons vérifier le pont supérieur. Il semble que le navire ait été dans un combat sérieux - regarde les dégâts...";
			link.l1 = "Tu as raison. Le navire était certainement sous un feu nourri. Très bien, cherchons quelque chose d'intéressant.";
			link.l1.go = "ring_26";
		break;
		
		case "ring_26":
			dialog.text = "Ouais. Et nous devons trouver les entrées des pièces intérieures.";
			link.l1 = "Marché conclu, ne perdons pas de temps. Appelle-moi si tu vois un crabe.";
			link.l1.go = "ring_27";
		break;
		
		case "ring_27":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 80.0); // 1.3 минуты на пошариться
			npchar.quest.diagnode = "ring_28";
			AddQuestRecord("LSC_Ring", "5");
		break;
		
		case "ring_28":
			dialog.text = "Rien de précieux encore... J'ai trouvé quelques petites choses intéressantes et c'est tout. Mais ce n'est pas grave, il n'y a généralement pas de trésors précieux sur les ponts. Les meilleurs doivent être dans les cabines. Il y a une entrée aux quartiers du capitaine là-bas. Allons voir.";
			link.l1 = "Sois prudent, qui sait ce qui nous attend là-bas. Peut-être devrais-je entrer le premier ?";
			link.l1.go = "ring_29";
		break;
		
		case "ring_29":
			dialog.text = "Allons-y, "+pchar.name+"Je ne me cacherai plus derrière ton dos. C'est une honte, c'est sûr...";
			link.l1 = "Va donc...";
			link.l1.go = "ring_30";
		break;
		
		case "ring_30":
			DialogExit();
			chrDisableReloadToLocation = true;
			LocatorReloadEnterDisable("ExternalRingDeck", "reload2", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "ExternalRingCabin1", "reload", "reload1", "OpenTheDoors", -1);
			pchar.quest.LSC_Ring_cabin.win_condition.l1 = "location";
			pchar.quest.LSC_Ring_cabin.win_condition.l1.location = "ExternalRingCabin1";
			pchar.quest.LSC_Ring_cabin.win_condition = "LSC_RingEnterCabin";
			sld = ItemsFromID("RingCapBook"); // кладем журнал 'Санта-Люсии'
			sld.shown = true;
			sld.startLocation = "ExternalRingCabin1";
			sld.startLocator = "item1";
		break;
		
		case "ring_31":
			dialog.text = "On dirait que j'ai eu de la chance - ni crabes ni autre saleté ici. Et maintenant, nous allons retourner cette cabine sens dessus dessous, bon sang, je jure que je commence à me fâcher. Je n'ai trouvé que deux putain de douzaines de doublons et quelques bricoles !";
			link.l1 = "Calme-toi. Tu avais raison, tous les objets de valeur sont toujours cachés dans la cabine du capitaine. Voyons ce que nous avons !";
			link.l1.go = "ring_32";
		break;
		
		case "ring_32":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "LSC_RingSetToBarman", -1);
			DoQuestCheckDelay("LSC_RingDialog", 30.0); // 30 сек на пошариться
			npchar.quest.diagnode = "ring_33";
		break;
		
		case "ring_33":
			dialog.text = "Ha-ha ! Comme je le pensais ! Je connais les habitudes des marchands, ils aiment faire des caches secrètes et y dissimuler le trésor du navire ! Le capitaine de cette pinasse était un gredin rusé, mais on ne me trompera pas si facilement ! Regarde ce que j'ai trouvé ! Tu n'aurais jamais pu le trouver sans moi !";
			link.l1 = "Montre-moi !";
			link.l1.go = "ring_34";
		break;
		
		case "ring_34":
			dialog.text = "Quarante mille pesos, deux coffres remplis de doublons, un paquet d'emeraudes et un tas de bijoux ! Le proprietaire etait assez riche... Bon, au moins cela remboursera nos efforts, bien que je comptais obtenir plus de choses. Partageons-le equitablement.";
			link.l1 = "Excellent, Richard. Au moins, nous avons gagné un peu d'argent !";
			link.l1.go = "ring_35";
		break;
		
		case "ring_35":
			TakeNItems(pchar, "jewelry4", 25);
			TakeNItems(pchar, "chest", 1);
			TakeNItems(pchar, "icollection", 1);
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("You have received a chest with doubloons");
			Log_Info("You have received 25 emeralds");
			Log_Info("You have received  a collection of jewels");
			PlaySound("interface\important_item.wav");
			dialog.text = "Eh bien, gardons ce que chacun de nous a trouvé sur les ponts pour nous-mêmes. Cela vous convient-il ? Avez-vous trouvé quelque chose d'utile dans les coffres et les armoires ?";
			link.l1 = "Quelques objets indiens, amulettes, papiers et ainsi de suite.";
			link.l1.go = "ring_36";
		break;
		
		case "ring_36":
			dialog.text = "Garde-le pour toi. Après tout, tu as fait le travail le plus risqué.";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
			{
				link.l1 = "D'accord. Et j'ai trouvé autre chose qui pourrait être utile pour un chasseur de trésors comme toi. Ici, il y avait un journal de bord du capitaine sur le bureau. L'histoire qui y est écrite est très triste... mais elle nous concerne d'une certaine manière. Il y a une boîte cachée dans la cale et elle est remplie d'or ! Lis-le !";
				link.l1.go = "ring_41";
			}
			else
			{
				if (CheckCharacterItem(pchar, "RingCapBook")) // взял журнал
				{
					link.l1 = "Très bien. Mais j'ai trouvé une chose de plus - le journal du capitaine.";
					link.l1.go = "ring_38";
				}
				else
				{
					link.l1 = "Bien, j'accepte ces conditions, ha-ha. Alors quoi, est-il temps de retourner ?";
					link.l1.go = "ring_37";
				}
			}
		break;
		
		case "ring_37":
			dialog.text = "Oui. Ne dis à personne d'autre pour le navire, ce sera notre secret. Certes, nous n'avons pas besoin de coprah, mais des provisions nous seront utiles. Nous n'aurons plus à les acheter de l'amiral.";
			link.l1 = "D'accord, je suis d'accord. J'espère que les autres ne trouveront pas le navire de sitôt. Allons-y !";
			link.l1.go = "ring_cabin_exit";
		break;
		
		case "ring_38":
			dialog.text = "As-tu lu ça ?";
			link.l1 = "Pas encore...";
			link.l1.go = "ring_39";
		break;
		
		case "ring_39":
			dialog.text = "Alors, lisons-le ! Nous pouvons en apprendre une information importante. Ce sera aussi intéressant de savoir comment elle a fini ici. Lis-le !";
			link.l1 = "Hm. Très bien, je vais le lire maintenant...";
			link.l1.go = "ring_40";
		break;
		
		case "ring_40":
			DialogExit();
			NextDiag.CurrentNode = "book_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
		break;
		
		case "book_wait":
			dialog.text = "As-tu lu cela ? Qu'y a-t-il ?";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
			{
				link.l1 = "Eh bien, écoute alors... L'histoire est très triste... mais elle nous concerne d'une certaine manière. Tes talents de chasseur de trésors pourraient nous être utiles. Il y a une boîte cachée remplie d'or dans la cale ! Lis-le !";
				link.l1.go = "ring_41";
			}
			else
			{
				link.l1 = "Attends une seconde. Je vais lire et te dire...";
				link.l1.go = "exit";
				NextDiag.TempNode = "book_wait";
			}
		break;
		
		case "ring_41":
			dialog.text = "Vraiment ? "+pchar.name+", je suis... eh bien, je ne lis pas très bien. Dis-moi ce qui est écrit là en détail, hein?";
			link.l1 = "Version courte : cette pinasse traversait la mer des Caraïbes du Sud Main à la Nouvelle-Espagne. Le capitaine s'est marié avec la princesse indienne d'une tribu du bas Orénoque. Elle lui a dit où son peuple faisait des sacrifices...";
			link.l1.go = "ring_42";
		break;
		
		case "ring_42":
			dialog.text = "";
			link.l1 = "Les pépites d'or étaient leurs sacrifices. Bien sûr, notre vaillant capitaine a pillé ce trésor d'or avec l'aide de son second et de son quartier-maître. Ils l'ont mis dans la cale, dans une des caisses et l'ont recouvert de coprah...";
			link.l1.go = "ring_43";
		break;
		
		case "ring_43":
			dialog.text = "";
			link.l1 = "Mais il semble que le vol de l'endroit sacré indien ait été puni. Le navire s'est retrouvé en pleine pétole, les réserves d'eau s'amenuisaient, une épidémie de fièvre a commencé et les pirates ont attaqué le navire. Les marins ont blâmé la jeune fille indienne, la femme du capitaine, et ont exigé de la jeter par-dessus bord. Bien sûr, le capitaine a refusé et l'équipage a commencé à se mutiner...";
			link.l1.go = "ring_44";
		break;
		
		case "ring_44":
			dialog.text = "";
			link.l1 = "Le capitaine a perdu ce combat. Selon les dernières notes - il s'est enfermé avec une fille indienne dans la cabine et a tenté de tirer sur les marins enragés qui enfonçaient la porte. Et une tempête arrivait sur eux... il semble qu'elle ait amené le navire ici. La fin de l'histoire est claire : la fille a été abattue et le capitaine a sûrement été tué par les rebelles.";
			link.l1.go = "ring_45";
		break;
		
		case "ring_45":
			dialog.text = "Hm. C'est vraiment une histoire triste. Mais tu te moques de moi ? Y a-t-il une caisse d'or dans la cale ? Je n'en crois pas mes oreilles ! Laquelle ? Allons-y ! Je vais vérifier chaque balle, chaque tonneau !";
			link.l1 = "Allons-y. Je suis aussi impatient de commencer les recherches.";
			link.l1.go = "ring_seek_gold";
		break;
		
		case "ring_cabin_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // открываем выход
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход // patch-2
			DoQuestReloadToLocation("ExternalRingDeck", "reload", "reload2", "LSC_RingFinalStage");
			sld = ItemsFromID("RingCapBook");
			sld.shown = false; // убираем журнал
			AddQuestRecord("LSC_Ring", "6");
		break;
		
		case "ring_seek_gold":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			// ставим прерывание на локатор
			pchar.quest.LSC_Ring_gold.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_gold.win_condition.l1.location = "ExternalRingInside";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator_group = "quest";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator = "gold";
			pchar.quest.LSC_Ring_gold.win_condition = "LSC_RingFindGold";
			// подменяем состав бокса
			pchar.GenQuestBox.ExternalRingInside = true;
			pchar.GenQuestBox.ExternalRingInside.box1.items.jewelry5 = 2522;
			AddQuestRecord("LSC_Ring", "7");
		break;
		
		case "ring_46":
			dialog.text = "Ha-ha ! Nous l'avons trouvé ! Il existe vraiment ! Regarde-moi ce tas énorme ! La boîte entière ! Il y a cinq mille pépites, pas moins ! Je n'ai jamais vu autant d'or !";
			link.l1 = "Félicitations, partenaire. Il semble que notre entreprise ait réussi... Que ferons-nous de tout cet or ?";
			link.l1.go = "ring_47";
		break;
		
		case "ring_47":
			dialog.text = "Que veux-tu dire ? Nous allons partager en deux !";
			link.l1 = "Bien sûr que nous le ferons. Où voulez-vous le garder ? Allez-vous le laisser ici ?";
			link.l1.go = "ring_48";
		break;
		
		case "ring_48":
			dialog.text = "Ha ! Sûrement, je cacherai l'or dans mes cachettes et personne ne les trouvera jamais. Cacher est ce que je sais bien faire ! Déplaçons la moitié de l'or dans ce tonneau, ce sera ma part. Je l'emporterai avant le coucher du soleil.\nTu peux faire ce que tu veux de ta part. Mais tu ferais mieux de l'amener dans tes propres cachettes aussi. Ne m'accuse pas si tu trouves ton or disparu. Je suis un honnête homme, à ma manière d'honnêteté et je n'oserai pas prendre ta part. Mais d'autres, ceux qui viendront ici plus tard... ils pourraient le trouver.";
			link.l1 = "Très bien. Je déciderai quoi faire de mon or. Mettons ta part dans un tonneau...";
			link.l1.go = "ring_49";
		break;
		
		case "ring_49":
			DialogExit();
			SetLaunchFrameFormParam("Two hours later..."+ NewStr() +"The gold was shared!", "", 0, 5);//табличка
			WaitDate("", 0, 0, 0, 2, 10);
			LaunchFrameForm();
			RecalculateJumpTable();
			sld = characterFromId("LSC_Rishard");
			sld.quest.diagnode = "ring_50";
			DoQuestCheckDelay("LSC_RingDialog", 5.0);
		break;
		
		case "ring_50":
			dialog.text = "Fait... Merci, "+pchar.name+", pour être venu avec moi. Je n'aurais pas pu faire cela sans toi. Maintenant, je devrais envisager de construire un tartan... pour m'enfuir d'ici... Ah, peu importe. J'y penserai plus tard\nJ'ai du travail à faire - déplacer l'or vers des endroits sûrs. Adieu, ami, je te souhaite d'utiliser ta part sagement !";
			link.l1 = "Adieu, Richard. Ce fut une journée glorieuse aujourd'hui. À bientôt !";
			link.l1.go = "ring_51";
		break;
		
		case "ring_51":
			DialogExit();
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // открываем выход
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход
			DoQuestCheckDelay("LSC_RingFinalStage", 0.5);
			DeleteAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook");
			AddQuestRecord("LSC_Ring", "8");
		break;
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Des questions ? Oh, très bien, si tu en as vraiment besoin...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Comment es-tu arrivé ici ?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Veux-tu quitter l'Île ?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "As-tu déjà envisagé de rejoindre l'un des clans ? Les Narvals par exemple ?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Est-il vrai que l'on peut trouver beaucoup de choses intéressantes dans l'anneau extérieur ?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Aucune question. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Pendant dix ans, mes camarades et moi avons navigué de Cuba à l'Île sur une tartane bien équipée. Nous gardions l'emplacement de l'Île secret - nous transportions des carcasses de taureaux et vendions de la viande fraîche pour des marchandises et de l'or provenant des cales des navires locaux\nDes bons moments ! Les provisions étaient toujours un problème ici, principalement du pain et du bœuf salé, alors ils nous payaient pour de la viande juteuse avec des épices, qui coûtent une fortune en Europe ! Chaque voyage me rapportait assez d'argent pour acheter toutes les catins de la Tortue\nMais tout a une fin, tout comme notre vie satisfaite. Le temps a mal tourné - les tempêtes sont devenues plus fortes, donc naviguer vers l'Île est devenu beaucoup plus dangereux. Certains de mes compagnons ont quitté le métier, mais pas moi et une douzaine d'hommes courageux\nFinalement, nous avons été jetés sur un récif à deux milles de l'Île. Je ne sais toujours pas comment j'ai réussi à nager à travers la mer déchaînée. C'est ainsi que je suis devenu l'un de ceux avec qui je faisais du commerce autrefois.";
			link.l1 = "Histoire intéressante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Ha ! Je vais m'en sortir d'ici, bon sang ! Mais plus tard. Que ferais-je à Cuba ? Je n'ai plus d'amis et ma bourse est vide. Je commencerai à construire un bateau dès que je trouverai un navire avec une cargaison précieuse à l'anneau extérieur ou une pile de doublons.";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;
		
		case "ansewer_3":
			dialog.text = "Et pourquoi devrais-je ? Monter la garde comme un idiot tous les trois jours et empêcher les gens de monter à bord du San Gabriel ? Et ils n'aiment pas embaucher de nouvelles personnes. Ce sont des indigènes locaux... Et les Noirs, c'est pareil. Non, je ferais mieux d'être seul.";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Bien sûr ! C'est ce qui fait vivre l'Île et ses habitants. Sais-tu quand ont lieu les fêtes ici ? Quand un nouveau navire arrive. Mais de toute façon, il y a beaucoup de navires intacts remplis d'or et de marchandises dans l'anneau extérieur\nLe problème est que l'anneau extérieur est presque impossible à explorer, tout est en désordre là-bas, si tu t'emmêles, glisses ou tombes mal - tu risques de te retrouver dans un trou dont tu ne pourras pas sortir par toi-même. Alors tu es fini. Beaucoup de gens sont morts de cette manière.";
			link.l1 = "Hm... Intéressant.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Que fais-tu là, hein ? Voleur !","Regardez-moi ça ! À peine étais-je perdu dans mes pensées que vous avez décidé de fouiller dans mon coffre !","Tu as décidé de fouiller dans mes coffres ? Tu ne t'en sortiras pas comme ça !");
			link.l1 = "Bon sang !";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Quoi ?! Décidé de fouiller mes coffres ? Tu ne t'en tireras pas comme ça !";
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
			dialog.text = LinkRandPhrase("Écoute, tu ferais mieux de ranger ton arme. Elle me rend nerveux.","Tu sais, courir avec une lame n'est pas toléré ici. Ranges-la.","Écoute, ne fais pas le chevalier médiéval courant avec une épée. Range-la, ça ne te va pas...");
			link.l1 = LinkRandPhrase("Bien.","D'accord.","Comme vous dites...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Écoute, je suis citoyen de la ville et je te demande de rengainer ton épée.","Écoutez, je suis citoyen de la ville et je vous demanderais de rengainer votre épée.");
				link.l1 = LinkRandPhrase("D'accord.","D'accord.","Comme vous dites...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sois prudent, l'ami, en courant avec une arme. Je pourrais devenir nerveux...","Je n'aime pas quand des hommes marchent devant moi avec leur arme prête. Ça me fait peur...");
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
