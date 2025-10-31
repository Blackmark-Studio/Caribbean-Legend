// Акула: Стивен Додсон
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			// Jason НСО
			if(CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, que diable!";
				link.l1 = "Steven, il y a eu un chevauchement. Je ne pouvais ni venir ni vous informer de mon absence...";
				link.l1.go = "patria_33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Content de te voir, l'ami ! Comment puis-je t'aider ? ";
				link.l1 = "Ravi de te voir aussi. Je voulais te remercier pour le spectacle parfaitement orchestré !";
				link.l1.go = "patria_29";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Shark") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Ravi de te voir, l'ami ! Comment puis-je t'aider ?";
				link.l1 = "J'ai une proposition pour toi. Une proposition pirate, tu vois !";
				link.l1.go = "patria";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Shark") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "C'est notre client ! Le travail est fait, ton baron est assis dans un cachot bien gardé. Peut-être que tu voudrais y jeter un œil, héhé ?!";
				link.l1 = "J'aurai tout le temps pour faire ça, ha-ha. Est-il bien traité ?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = "Ravi de te voir, l'ami ! Comment puis-je t'aider ?";
				link.l1 = "Je suis revenu pour demander votre aide.";
				link.l1.go = "tieyasal";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "islatesoro")
			{
				dialog.text = "Heureux de te voir, camarade ! Comment puis-je t'aider ?";
				link.l1 = "Steven, j'ai quelque chose pour toi.";
				link.l1.go = "guardoftruth";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro")
			{
				dialog.text = "Content de te voir, l'ami ! Comment puis-je t'aider ?";
				link.l1 = "Steven, je dois te demander quelque chose. Cela pourrait ne pas te plaire, mais j'ai besoin de ton aide.";
				link.l1.go = "shadows";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro")
			{
				dialog.text = "Ah, te voilà, "+pchar.name+"Je m'attendais à votre arrivée. Le Diable des Forêts m'a parlé de vos ennuis avec Tortuga...";
				link.l1 = "Il m'a aussi dit que tu avais déjà trouvé une solution. Est-ce vrai ?";
				link.l1.go = "terrapin";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin.Catherina") && pchar.questTemp.Terrapin == "tortuga")
			{
				dialog.text = "Comment allons-nous, "+pchar.name+"?";
				link.l1 = "Des secrets partout... J'ai besoin de tes conseils, Steven.";
				link.l1.go = "terrapin_8";
				break;
			}
			// belamour legendary edition хвастовство "Фортуной"
			if(CheckShipTypeInSquadron(SHIP_FRIGATE_L) > 0 && !CheckAttribute(pchar,"questTemp.SharkFrigate"))
			{
				link.l2 = "Oui, je veux te montrer quelque chose... Voudrais-tu marcher avec moi jusqu'au quai ?";
				link.l2.go = "check_out_my_frigate";
			}
			
			// belamour legendary edition на пару с Акулой
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "toDodson")
			{
				dialog.text = "Ah, mon ami "+GetFullName(pchar)+"Entrez, c'est bon de vous voir ! Pourquoi êtes-vous venu ?";
				link.l1 = "Salut, Steven ! Eh bien, je suis venu comme promis. Ton navire est-il prêt ?";
				link.l1.go = "SharkGoldFleet";
				break;
			}
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "RUinDeal")
			{
				link.l2 = "Alors, comment vont tes affaires ? Tu n'as pas abandonné cette entreprise concernant la 'Flotte d'Or' ?";
				link.l2.go = "SharkGoldFleet_10";
			}
			dialog.text = "Ah, mon ami "+GetFullName(pchar)+"! Entrez, ça fait plaisir de vous voir ! Pourquoi êtes-vous venu ?";
			link.l1 = "Oui, j'ai visité Isla Tesoro pour affaires, et j'ai décidé de faire un saut ici un moment.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// --------------------------------------вариант R-----------------------------------------------
		case "Chad_die":
			dialog.text = "Ha ! Je suppose que tu es notre visiteur nocturne ? J'ai été informé de cet incident trop tard. J'ai vérifié tes affaires et trouvé une lettre du Démon de la Forêt. Diable, elle sentait presque la jungle de Main\nTon nom est "+GetFullName(pchar)+" ? Ne sois pas surpris, je l'ai lu dans la lettre. Mon nom est Steven Dodson. Ou simplement Requin. Le Requin. Je pense que tu as déjà entendu parler de moi. J'occupe actuellement le poste d'amiral dans cette ville ou sur cette île, peu importe\nJe m'excuse pour les actions de mes hommes la nuit dernière. C'était mon ordre de capturer tous ceux qui se faufilent dans la cale. Trop de voleurs parmi les Narvals et les Rivados\nChad t'a laissé partir, je suppose ? Étrange. J'allais justement lui envoyer un ordre pour te libérer. Où est ton navire ? J'espère qu'elle va bien ?";
			link.l1 = "Chad ? Si je comprends bien, ton maître d'équipage ne me laisserait jamais quitter la prison vivant. Je l'ai fait moi-même et j'ai aussi libéré un de ces types noirs... Rivados.";
			link.l1.go = "Chad_die_1";
		break;
		
		case "Chad_die_1":
			dialog.text = "Tu me dis des choses intéressantes, l'ami. Et comment as-tu réussi à sortir du 'Tartare' ? On dirait que je vais avoir une bonne conversation avec Chad et ses gardiens de prison...";
			link.l1 = "Tu n'auras plus jamais de conversation avec eux. J'ai bien peur qu'ils ne parlent plus jamais. Chad a menacé de me garder en cage pour toujours. Il m'a accusé d'être Rivados et il a exigé que je prouve le contraire en tuant le sorcier noir Chimiset...";
			link.l1.go = "Chad_die_2";
		break;
		
		case "Chad_die_2":
			dialog.text = "Nom d'un chien ! Quelle folie insensée ! Nous avons besoin de Chimiset vivant, et Chad le savait parfaitement ! Et pourquoi supposerait-il que vous étiez Rivados, si tous sont noirs ? Qu'est-ce qu'il manigance, que le diable l'emporte ?";
			link.l1 = "Il prépare quelque chose que tu n'aimeras sûrement pas, Steven. Chad m'a donné une machette et m'a envoyé en bas pour tuer Chimiset. Mais le vieux Black m'a dit quelque chose d'important, et j'ai réalisé que si je tue Chimiset, je serai le prochain...";
			link.l1.go = "Chad_die_3";
		break;
		
		case "Chad_die_3":
			dialog.text = "";
			link.l1 = "Au lieu de tuer le vieil homme, j'ai ouvert un coffre avec des munitions et me suis battu avec Chad et ses acolytes. Comprends-tu maintenant pourquoi tu ne peux plus leur parler ? Ils sont tous morts.";
			link.l1.go = "Chad_die_4";
		break;
		
		case "Chad_die_4":
			dialog.text = "Merde ! Les nouvelles deviennent de plus en plus terrifiantes ! Et que dois-je faire de tout ce bordel ?";
			link.l1 = "Ecoute-moi, Steve. Chimiset m'a dit que Chad avait un accord avec des Narvals - c'est l'autre clan d'après ce que je comprends. Chad prévoyait de te tuer et de prendre ta place. Les Narvals sont impatients de te voir mort, car ils sont certains que tu as tué leur chef Allen... ou Alan, je ne me souviens plus.";
			link.l1.go = "Chad_die_5";
		break;
		
		case "Chad_die_5":
			dialog.text = "C'est des conneries ! Je n'ai pas tué Alan ! Quelqu'un d'autre l'a fait, peut-être même les Narvals. Je pense que leur chef actuel - Donald Greenspen - a tué Alan !";
			link.l1 = "Non. Chad l'a assassiné. Chimiset avait été témoin du crime - c'est pourquoi ils voulaient le tuer aussi. Chad ne voulait pas le faire lui-même pour une raison quelconque - on dirait qu'il avait peur d'une malédiction quelconque. C'est pourquoi il voulait que je fasse le travail.";
			link.l1.go = "Chad_die_6";
		break;
		
		case "Chad_die_6":
			dialog.text = "Je n'arrive pas à y croire... Chad a tué Alan ? Mais pourquoi ?";
			link.l1 = "Pour te laisser la faute et te faire des ennemis parmi les Narvals. Je suppose que c'est lui qui répandait des rumeurs, car pourquoi les Narvals te blâmeraient-ils, toi seul ? Steven, ils prévoient de te tuer. Et le clan Rivados serait blâmé pour ça - je ne sais pas comment ils comptent le faire cependant. Chimiset m'en a parlé.";
			link.l1.go = "Chad_die_7";
		break;
		
		case "Chad_die_7":
			dialog.text = "Bonjour, mon ami.";
			link.l1 = "En outre, j'ai trouvé cette lettre dans le coffre de Chad. Lis-la. Cela ressemble à une preuve solide, bien que ce soit indirect.";
			link.l1.go = "Chad_die_8";
		break;
		
		case "Chad_die_8":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "...(lecture)... hé ! Je ne suis pas surpris de la trahison de Chad. Fils de pute a toujours voulu le pouvoir sur cette île. Mais les Narvals ! Croire sérieusement que c'était moi qui ai tué Alan ! Cela leur coûtera le double du prix pour les provisions\nJ'avais de toute façon prévu de libérer Chimiset, il est grand temps de faire la paix avec eux. Tu m'as choqué, camarade, pour être honnête...";
			link.l1 = "Je comprends, Steven. Ça ne me plaît pas non plus, je me suis retrouvé au milieu d'un sacré bazar politique depuis que j'ai atteint l'Île. Je suis venu ici seulement pour te trouver, toi et Nathaniel Hawk...";
			link.l1.go = "Chad_die_9";
		break;
		
		// ноды пересечения
		case "Chad_die_9":
			dialog.text = "Quoi ? Hawke ? N'est-il pas en Jamaïque ? Il est baron de la ville des Marrons, pourquoi serait-il ici ?";
			link.l1 = "Non. Jackman est aux commandes là-bas maintenant. J'ai pu découvrir que Hawk y était arrivé de la même manière que moi - par le portail de Kukulcan.";
			link.l1.go = "Chad_die_10";
		break;
		
		case "Chad_die_10":
			dialog.text = "Qu'est-ce que c'est que ces balivernes ? Quel portail ? Et tu n'as toujours pas répondu - où est ton navire ?";
			link.l1 = "Il n'y a pas de navire. Je comprends, Steve, que c'est difficile à croire, mais je suis vraiment arrivé ici par l'idole indienne du Continent... ne me regarde pas comme ça - je ne suis pas fou ! Je ne comprends moi-même pas comment c'est possible, mais ça l'est !";
			link.l1.go = "Chad_die_11";
		break;
		
		case "Chad_die_11":
			dialog.text = "";
			link.l1 = "Le chaman du village Miskito a vu comment Nathaniel Hawk, qui fuyait les poursuivants, a couru vers l'idole indienne, connue sous le nom de statue de Kukulcan, et a soudainement disparu. Ce chaman m'a dit qu'il avait lui-même été sur cette Île, et qu'il y était allé de la même manière à travers la statue...";
			link.l1.go = "Chad_die_12";
		break;
		
		case "Chad_die_12":
			dialog.text = "";
			link.l1 = "Je cherche Nathan, c'est pourquoi j'ai dû suivre ses traces. Je suis venu à la statue à minuit, tout comme le chaman me l'avait dit. Vous ne le croirez pas, mais le sommet de la statue de pierre était doré cette nuit-là, et une lumière mystérieuse brillait au-dessus !";
			link.l1.go = "Chad_die_13";
		break;
		
		case "Chad_die_13":
			dialog.text = "Bonjour, mon ami.";
			link.l1 = "Dès que j'ai touché la statue, un cercle de lumière s'est formé autour de l'idole, le feu s'est embrasé, puis j'ai été aspiré dans la statue. J'ai été projeté ici, dans la cale de votre navire, en bas près de la proue, à la brèche...";
			link.l1.go = "Chad_die_14";
		break;
		
		case "Chad_die_14":
			dialog.text = "Bonjour, monami.";
			link.l1 = "Je n'ai survécu que grâce au chaman, qui m'avait donné une potion spéciale. En fin de compte, j'ai été attaqué par une sorte de monstre - un crabe géant. J'espère que tu me fais confiance maintenant ?";
			link.l1.go = "Chad_die_15";
		break;
		
		case "Chad_die_15":
			dialog.text = "Tu parles de l'histoire du crabe ? Je te crois là-dessus. Il y a beaucoup de ces monstres autour de l'île. Nous les appâtions avec un poisson mort, donc ils gardent souvent notre porte arrière. Ça fout la frousse aux voleurs. Et ce que tu as raconté sur l'idole - je ne suis pas encore fou\nMais je ne rejette pas ton histoire non plus, les locaux bavardent sur de telles choses depuis plusieurs dizaines d'années, et puis j'ai vu des choses étranges moi-même il y a longtemps sur les navires des Rivados... peu importe.";
			link.l1 = "Je jure que tout est vérité.";
			link.l1.go = "Chad_die_16";
		break;
		
		case "Chad_die_16":
			dialog.text = "Très bien. Ainsi soit-il. Dis-moi, pourquoi me cherchais-tu, moi et Nathan ? Selon la lettre de Jan, tu voulais que je devienne le chef des Frères de la Côte ?";
			link.l1 = "Exactement. Beaucoup de choses ont changé après votre disparition et celle de Hawk. Jackman essaie de jouer le rôle central parmi les pirates. Il prévoit de devenir leur chef, et il réussira, si Jan et moi ne l'arrêtons pas.";
			link.l1.go = "Chad_die_17";
		break;
		
		case "Chad_die_17":
			dialog.text = "Bonjour, mon ami.";
			link.l1 = "Jackman est prêt pour une partie sérieuse et sanglante. Je suis sûr que c'est lui qui a organisé l'embuscade et la chasse à Nathaniel. Je pense aussi qu'il a tué Blaze. Faire de toi le chef des Frères de la Côte est le seul moyen de l'arrêter.";
			link.l1.go = "Chad_die_18";
		break;
		
		case "Chad_die_18":
			dialog.text = "Écoute, je serais ravi, mais nous devons quitter cette île d'abord. J'en ai assez. D'autant plus que je peux laisser Dexter ici, il peut gérer les affaires en mon absence. Je n'avais pas l'intention de rester ici si longtemps, mais mon navire a été brûlé dans une bataille contre les clans.\nJe ne vais pas voyager par ces portails, n'essaie même pas de me convaincre, j'ai besoin d'un navire.";
			link.l1 = "Je ne vais pas... Steven, le chaman Miskito m'a dit qu'il y avait une statue de Kukulcan ici, sur l'Île. Elle ressemble à une idole en pierre ordinaire. Sais-tu où je peux la trouver ?";
			link.l1.go = "Chad_die_19";
		break;
		
		case "Chad_die_19":
			dialog.text = "Je ne sais pas. Je n'ai jamais vu de statues comme ça. Demandez à quelqu'un d'autre.";
			link.l1 = "Tu vois, si je trouve cette statue, je pourrai quitter cette île sans bateau. Le voyage ne me fait plus peur. Et puis je reviendrais ici de manière normale et te prendrais d'ici.";
			if (pchar.questTemp.LSC == "entrance" || pchar.questTemp.LSC == "mary") link.l1.go = "entrance_4";
			else link.l1.go = "Chad_die_20";
		break;
		// ноды пересечения
		
		case "Chad_die_20":
			dialog.text = "Je comprends, mais je ne peux pas vous aider. De plus, cette histoire d'assassinat est assez troublante. Chad est mort, mais je doute que les Narvals abandonnent leur plan. Je ne veux pas vivre en m'attendant à être abattu dans le dos chaque jour. Puisque vous avez besoin de moi vivant et que vous êtes déjà impliqué dans ce bazar, je vous propose d'enquêter sur ce complot\nVous êtes un nouveau venu, c'est un avantage. Trouvez les partenaires de Chad et amenez-les-moi ou tuez-les sur place, cela m'est égal. Parlez à Chimiset, le vieux noir en sait plus qu'il ne nous l'a déjà dit\nSoyez prudent avec les Narvals, ne franchissez pas leurs frontières à moins d'avoir un mot de passe. Ils changent de mot de passe chaque semaine.\nUne fois la menace éliminée, je vous fournirai les directions de navigation et toutes les informations dont vous avez besoin\nAllez et trouvez ceux qui sont responsables. Restaurez l'ordre. Je m'assurerai qu'ils nettoient la prison après vous. Et nous avons besoin d'un nouveau geôlier. Et j'ai besoin de rhum, je ne me sens pas bien.";
			link.l1 = "Très bien, Steven. Faisons cela...";
			link.l1.go = "Chad_die_21";
		break;
		
		case "Chad_die_21":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			pchar.questTemp.LSC.rvd_friend = "true"; //флаг на проход по кораблям ривадос
			// // ривадосы не будут останавливать где просят пароль
			sld = characterFromId("Chimiset");
			sld.dialog.currentnode = "Friend"; //ноду Чимисету
			pchar.quest.LSC_Eddy.win_condition.l1 = "location";
			pchar.quest.LSC_Eddy.win_condition.l1.location = "ProtectorFisher";
			pchar.quest.LSC_Eddy.function = "LSC_EddyTalk"; //на разговор с Эдди
			AddQuestRecord("SharkHunt", "10");
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			for (i=7; i<=12; i++)
			{
				sld = CharacterFromID("RivadosSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=4; i<=8; i++)
			{
				sld = CharacterFromID("RivadosProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("Just imagine: someone has killed the admiral's jailer, Chad Kapper. Impossible! No doubt, that was the Rivados wizard's job...", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("I heard that Chad Kapper is dead. There was no official statement; his body was never found, either. Perhaps, the admiral had simply given him a secret mission?", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("I don't see our jailer Chad Kapper. Some people say that he was killed and some disagree. Anyway, no one has seen him dead.", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that the admiral has doubled provision prices for Narwhals! That pirate is truly reckless!", "LostShipsCity", 7, 3, "LSC", "");
		break;
		
			case "Mary_Die":
			dialog.text = "Eh bien, qu'as-tu, "+pchar.name+" Des nouvelles des Narvals ?";
			link.l1 = "Oui. Tu seras heureux d'apprendre, Steve, que la conspiration a été dévoilée et que les comploteurs sont morts. J'ai toutes les preuves.";
			link.l1.go = "Mary_Die_1";
		break;
		
		case "Mary_Die_1":
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack")) dialog.text = "Je m'en doutais quand j'ai entendu la fusillade... Dis-m'en plus, je t'écoute.";
			else dialog.text = "Vraiment ? Je suis vraiment heureux d'entendre cela ! Dis-m'en plus, je t'écoute.";
			link.l1 = "C'était tout planifié par votre maître d'équipage, Chad Kapper. Il a tué Alan Milrow dans la prison 'Tartarus', et il répandait des rumeurs sur votre implication. Je pense que les Narvals étaient vraiment en colère, et ce fut un coup dur pour la petite amie d'Alan, Mary la Rouge...";
			link.l1.go = "Mary_Die_2";
		break;
		
		case "Mary_Die_2":
			dialog.text = " ";
			link.l1 = "Mary était avide de vengeance et Chad Kapper l'a utilisée à ses propres fins. Ils ont conçu un plan astucieux pour attenter à votre vie. Tout le monde ici sait que vous avez l'habitude de vous promener sur la poupe du 'San Augustine' chaque soir.";
			link.l1.go = "Mary_Die_3";
		break;
		
		case "Mary_Die_3":
			dialog.text = "Heh ! Je vais reconsidérer mes habitudes... Continue.";
			link.l1 = "Ils avaient besoin d'un mousquet à longue portée et précis pour exécuter leur plan, et c'est ainsi qu'un certain Adolf Barbier le leur a fourni. Mais son stutzen avait été mis en gage à Giuseppe Fazio, alors Mary et Chad lui ont donné assez d'argent pour le racheter. Adolf l'a récupéré du gage...";
			link.l1.go = "Mary_Die_4";
		break;
		
		case "Mary_Die_4":
			dialog.text = "Bonjour, mon ami.";
			link.l1 = "Ils ont engagé Cyclope Marcello, un ancien chasseur royal, pour te tuer. Il devait recevoir le fusil et t'abattre. Ensuite, Mary l'aurait tué et utilisé son cadavre et le fusil comme preuve que les Rivados étaient responsables de l'attaque. Cyclope Marcello est un mulâtre, tu sais...";
			link.l1.go = "Mary_Die_5";
		break;
		
		case "Mary_Die_5":
			dialog.text = "Quel salaud intelligent !";
			link.l1 = "Après cela, les Narvals et les pirates attaqueraient les Rivados et les détruiraient. Chad deviendrait un amiral et Mary serait sa maîtresse. Peut-être, cependant, lui aurait-il tranché la gorge à la place, puisqu'elle en savait trop. Très probablement...";
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack")) link.l1.go = "Mary_Die_6a";
			else link.l1.go = "Mary_Die_6";
		break;
		
		case "Mary_Die_6":
			dialog.text = "Bonjour, mon ami.";
			link.l1 = "Quoi qu'il en soit, c'est terminé maintenant. Adolf n'était pas assez bavard, et j'ai dû le tuer directement dans sa cabine. J'ai également dû m'occuper de Mary et Cyclope, qui étaient venus chercher le stutzen chez Adolf. Ils ont réalisé qui j'étais immédiatement, et m'ont attaqué sur-le-champ.";
			link.l1.go = "Mary_Die_7";
		break;
		
		case "Mary_Die_7":
			dialog.text = "Ils sont donc allongés à l'intérieur du 'Santa Florentina', n'est-ce pas ?";
			link.l1 = "Oui. Tous les trois.";
			link.l1.go = "Mary_Die_8";
		break;
		
		case "Mary_Die_8":
			dialog.text = "C'est bien qu'aucun témoin n'ait été impliqué dans ce désordre. Je m'occuperai des corps. Tu as fait du bon travail, "+pchar.name+"Si tu faisais partie de mon équipage, je t'aurais certainement fait mon premier lieutenant.";
			link.l1 = "Merci pour une telle réponse enthousiaste ! Et, enfin, jetez un œil à ces lettres. Je les ai prises sur les corps du Cyclope et de la pauvre Mary...";
			link.l1.go = "Mary_Die_9";
			AddSimpleRumourCityTip("Have you heard that? Our squabbler and madcap Red Mary has disappeared. I won't be surprised if she is dead...", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that Red Mary has disappeared. Have you heard about it?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("Mary Casper has vanished. Some people say that she is still inside her cabin but I don't believe it. It's been too long since there last was light in it.", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that Red Mary was murdered. Poor girl! Yes, she had tough character, but everybody loved her. Who could have done such a terrible thing?", "LostShipsCity", 10, 1, "LSC", "");
		break;
		
		case "Mary_Die_6a":
			dialog.text = "";
			link.l1 = "Quoi qu'il en soit, c'est fini maintenant. Adolf n'était pas assez bavard, et j'ai dû le tuer dans sa cabine. J'ai aussi dû m'occuper de Mary et Cyclope, qui étaient venus chercher le stutzen d'Adolf. Ils ont compris qui j'étais immédiatement et m'ont attaqué aussitôt.";
			link.l1.go = "Mary_Die_7a";
		break;
		
		case "Mary_Die_7a":
			dialog.text = "Quel dommage que tu aies déclenché une bagarre sur 'Eva'. Maintenant, les Narvals sont au courant que tu es responsable de la mort de leurs hommes, de telles actions n'amélioreront pas ta réputation. On peut en dire autant de la mienne. Ne leur rends pas visite tant que tu n'auras pas réglé ce conflit\nEn général, tu t'en es bien sorti, "+pchar.name+" ! Si tu étais dans mon équipage, je t'aurais certainement fait mon second.";
			link.l1 = "Merci pour une telle réponse enthousiaste ! Et, enfin, jetez un œil à ces lettres. Je les ai prises sur les corps du Cyclope et de la pauvre Mary...";
			link.l1.go = "Mary_Die_9";
			AddSimpleRumourCityTip("Such a massacre you have performed here! Narwhals won't forget about it!", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I understand killing Cyclops and two Narwhal bandits... But the girl, why have you killed the girl? Poor Mary...", "LostShipsCity", 7, 5, "LSC", "");
		break;
		
		case "Mary_Die_9":
			RemoveItems(pchar, "letter_chad", 1);
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = " Pauvre Mary ? Tu ressens de la pitié pour cette catin ?";
			link.l1 = "Je le suis vraiment. Tu vois, Chad l'a trompée et s'est servi d'elle. Elle n'a pas pu résister à ses sentiments et à son tempérament fougueux... et voilà où ça l'a menée.";
			link.l1.go = "Mary_Die_10";
		break;
		
		case "Mary_Die_10":
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			dialog.text = "Eh bien, va voir frère Julian et allume une bougie... Moi, je ne le ferai pas. Bon, laissons tomber ce sujet. Je te suis reconnaissant, "+pchar.name+", pour votre aide. Vous pouvez désormais compter sur mon soutien. Je veux vous récompenser pour votre excellent travail. Tenez, prenez cinq cents doublons.";
			link.l1 = "Chouette, merci !";
			link.l1.go = "LSC_navy";
			AddSimpleRumourCityTip("They say that the admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are the admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		// ----------------------------------------вариант N---------------------------------------------------
		case "entrance":
			dialog.text = "Que veux-tu? Je ne me souviens pas de toi...";
			link.l1 = "Bien sûr que non, tu ne me connais pas - nous ne nous sommes jamais rencontrés auparavant, et je suis arrivé ici tout récemment. Bonjour, Steven. Quel coup de chance rare ! Je t'ai finalement trouvé, je te cherchais bien que je ne m'attendais pas à te trouver ici !";
			link.l1.go = "entrance_1";
		break;
		
		case "entrance_1":
			dialog.text = "Attends, l'ami, calme-toi. Tu me cherches ? Ça ne me plaît pas. Pourquoi diable me cherches-tu ?";
			link.l1 = "Je vois. Essayons encore une fois alors. Tenez, prenez la lettre. Elle a été écrite par Jan Svenson pour vous. Je suppose que tous vos soupçons seront dissipés après l'avoir lue.";
			link.l1.go = "entrance_2";
		break;
		
		case "entrance_2":
			RemoveItems(pchar, "letter_svenson", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "(lisant)... Hum. Cela explique beaucoup de choses. Et je pensais que tu allais me donner une marque noire pour la mort de Blaze. Tu sais, récemment, il y a eu beaucoup de gens impatients de le faire. As-tu laissé ton navire à l'anneau extérieur ? Et comment as-tu su que j'étais ici ?";
			link.l1 = "Je ne l'ai pas fait. C'était un coup de chance. Et à propos de Blaze... Jan et moi pensons que tu n'es pas responsable de sa mort.";
			link.l1.go = "entrance_3";
		break;
		
		case "entrance_3":
			dialog.text = "Et tu as raison. Je ne l'ai pas fait. Quelqu'un essaie de me faire porter le chapeau, c'est vrai. Mais je ne l'ai pas tué.";
			link.l1 = "C'est bien. Intéressant, je suis venu ici pour trouver Nathaniel Hawk, mais je t'ai trouvé à la place, ha-ha !";
			link.l1.go = "Chad_die_9";
		break;
		
		case "entrance_4":
			dialog.text = "Je comprends, mais je ne peux pas t'aider. Tu dois en parler avec les anciens de cette Île. Parle au sorcier Rivados, Chimiset. Le vieil homme noir en sait bien plus qu'il ne le dit.";
			link.l1 = "Et où puis-je trouver ce sorcier ?";
			if (pchar.questTemp.LSC == "mary") link.l1.go = "mary";
			else link.l1.go = "entrance_5";
		break;
		
		case "entrance_5":
			dialog.text = "Dans ma prison, sur 'Tartarus'. J'avais de toute façon l'intention de le libérer, il est temps d'améliorer nos relations avec les Rivados. Bien ! Va à la prison, dis à Chad Kapper, c'est le geôlier, que j'ai ordonné de libérer Chimiset\nDis au noir pourquoi je t'ai envoyé, dis-lui que je le libérerai s'il est assez bavard. Je suis sûr que cela le fera parler.";
			link.l1 = "Hm... Je suis un novice ici. Où est la prison ?";
			link.l1.go = "entrance_6";
		break;
		
		case "entrance_6":
			dialog.text = "N'oubliez pas ce qui suit. Quittez ma résidence, traversez le pont, tournez à gauche, passez par la frégate Carolina jusqu'au galion Gloria et vous arriverez à l'Esmeralda. Cherchez un panneau de magasin et entrez par les portes en dessous. Passez par la porte à l'avant du navire et vous atteindrez le Tartarus.\nSoyez prudent à l'Esmeralda, c'est une propriété du clan des Narvals, même si d'autres peuvent la visiter. Ne croisez pas leurs combattants et évitez tout ennui.";
			link.l1 = "Qui sont ces Rivados et Narvals ?";
			link.l1.go = "entrance_7";
		break;
		
		case "entrance_7":
			dialog.text = "Les clans vivent ici depuis très longtemps. Ils représentent les descendants des premiers colons. Les Narvals sont principalement anglais, hollandais et français, les Rivados sont tous nègres. Chaque clan a un chef, ils possèdent plusieurs navires et ne laissent personne entrer dans leur territoire\nVous devez connaître les mots de passe pour leur rendre visite. Ils changent les mots de passe chaque semaine.";
			link.l1 = "Très bien. Je m'occuperai de cela. Me laisseront-ils entrer dans la prison ?";
			link.l1.go = "entrance_8";
		break;
		
		case "entrance_8":
			dialog.text = "Ils le feront. Voici la clé, ainsi Chad saura que je vous y ai envoyé. Prenez-la.";
			link.l1 = "D'accord. Alors je vais parler avec ce... Chimiset et je reviendrai avec les résultats.";
			link.l1.go = "entrance_9";
		break;
		
		case "entrance_9":
			DialogExit();
			GiveItem2Character(pchar, "key_capper");
			NextDiag.CurrentNode = "Total_wait";
			sld = characterFromId("Chimiset");
			sld.dialog.currentnode = "prisoner"; //даем ноду Чимисету
			sld.quest.chimiset_die = "true";
			ChangeCharacterAddressGroup(sld, "Tartarusprison", "quest", "prison2"); // в закрытую клетку
			LAi_SetGroundSitTypeNoGroup(sld);
			sld = characterFromId("Capper");
			sld.dialog.currentnode = "prisoner"; //даем ноду Капперу
			LAi_LocationFightDisable(&Locations[FindLocation("Tartarusprison")], true);//запретить драться
			// прерывания на локаторы тартаруса
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1 = "locator";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.locator = "reload51";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l2 = "item";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l2.item = "key_capper";
			pchar.quest.LSC_TartarusEntrance1.function = "LSC_TartarusEntrance1_Open";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1 = "locator";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.locator = "reload52";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l2 = "item";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l2.item = "key_capper";
			pchar.quest.LSC_TartarusEntrance2.function = "LSC_TartarusEntrance2_Open";
			AddQuestRecord("SharkHunt", "19");
		break;
		
		case "entrance_10":
			dialog.text = "Alors, êtes-vous allé sur 'Tartarus' ?";
			link.l1 = "Oui. J'ai transmis vos ordres à Chad et j'ai eu une conversation avec l'homme noir.";
			link.l1.go = "entrance_11";
		break;
		
		case "entrance_11":
			dialog.text = "Le sorcier vous a-t-il dit quelque chose d'intéressant ?";
			link.l1 = "Oh, oui. Il m'a dit où trouver l'idole de téléportation de Kukulcan. Elle était sur le navire 'San Geronimo', qui avait coulé sur le banc près du territoire des Narvals.";
			link.l1.go = "entrance_12";
		break;
		
		case "entrance_12":
			dialog.text = "Ha-ha-ha, formidable ! Alors ton 'portail' est maintenant au fond ? Eh bien, mon gars, j'ai bien peur que tu sois coincé sur cette île. Alors rejoins-moi, moi et mes hommes...";
			link.l1 = " Je trouverai un moyen d'atteindre l'idole. Je trouverai le chemin. Maintenant. Chimiset m'a dit que tu ne devrais pas faire confiance à Kapper, car il a vu Chad tuer un certain Alan Milrow, le chef des Narvals, de ses propres yeux.";
			link.l1.go = "entrance_13";
		break;
		
		case "entrance_13":
			dialog.text = "Quoi ?! Chad a tué Alan ? Ce sorcier est fou ! Cela ne peut tout simplement pas être vrai !";
			link.l1 = "Tu sais, Steve, Chimiset est vraiment effrayé. Je ne pense pas qu'il m'ait menti.";
			link.l1.go = "entrance_14";
		break;
		
		case "entrance_14":
			dialog.text = "Bon sang, voilà une sacrée mauvaise nouvelle ! Le meurtre d'Alan a déjà terni ma réputation parmi les Narvals - certains ont décidé que j'en étais responsable, et maintenant il s'avère qu'un de mes officiers pourrait l'avoir fait !";
			link.l1 = "Il semble que les gens aiment vous blâmer pour des péchés qui ne sont pas les vôtres...";
			link.l1.go = "entrance_15";
		break;
		
		case "entrance_15":
			dialog.text = "Oui, c'est inquiétant...";
			link.l1 = "Et maintenant, la 'meilleure' nouvelle pour vous - le vieil homme m'a dit qu'il avait surpris plusieurs conversations et a compris que certains de vos hommes prévoyaient de vous tuer. Il ne vous en dira plus que si vous le libérez, et en privé.";
			link.l1.go = "entrance_16";
		break;
		
		case "entrance_16":
			dialog.text = "Superbe! Et tout cela à cause de toi! Sans vouloir t'offenser, je plaisante. J'ai la tête qui tourne : Chad a tué Alan, mes hommes prévoient un attentat contre moi... Le vieux noir t'a-t-il donné des détails ?";
			link.l1 = "Non. Il craint trop Chad, d'après ce que j'ai compris.";
			link.l1.go = "entrance_17";
		break;
		
		case "entrance_17":
			dialog.text = "Bien. Je dirai à Rivados que je veux rencontrer Chimiset. Nous verrons ce qu'il me dit. Et concernant l'attentat... d'accord, je serai prudent. Alors, que vas-tu faire maintenant, "+pchar.name+"?";
			link.l1 = "Rien de particulier pour l'instant. Je vais me promener sur l'Île et faire la connaissance des locaux - peut-être que j'aurai une idée pour quitter cet endroit. Et je dois d'abord trouver Nathan Hawk, c'est pour lui que je suis ici.";
			link.l1.go = "entrance_18";
		break;
		
		case "entrance_18":
			dialog.text = "Je vois. N'oublie pas de venir me voir lorsque tu trouveras un moyen de quitter cette île - je te donnerai les instructions de navigation, tu ne pourras pas revenir ici sans elles. Je te donnerai aussi quelques détails importants.";
			link.l1 = "D'accord. Je viendrai te voir, c'est sûr, Steve !";
			link.l1.go = "entrance_19";
		break;
		
		case "entrance_19":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			// прерывание на вызов к Акуле
			pchar.quest.LSC_GotoShark.win_condition.l1 = "Timer";
			pchar.quest.LSC_GotoShark.win_condition.l1.date.hour  = 9.00;
			pchar.quest.LSC_GotoShark.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l2 = "location";
			pchar.quest.LSC_GotoShark.win_condition.l2.location = "LostShipsCity_town";
			pchar.quest.LSC_GotoShark.function = "LSC_GotoShark";
			AddQuestRecord("SharkHunt", "21");
		break;
		
		case "entrance_20":
			dialog.text = "Il est bon que vous soyez venu, "+pchar.name+"Je vous attendais. Mauvaise nouvelle. Chimiset est mort, Chad Kapper a disparu sans laisser de trace.";
			link.l1 = "Merde... Je suis sûr que Chad a tué Chimiset ! Le vieux noir avait bien raison d'être effrayé.";
			link.l1.go = "entrance_21";
		break;
		
		case "entrance_21":
			dialog.text = "Je n'en doute pas. Nom d'un chien, la situation empire d'heure en heure. J'avais presque établi des contacts solides et directs avec Eddie le Noir et maintenant ça. Eh bien, nous pouvons oublier l'amitié avec les Rivados\nIls savent que tu as parlé à Chimiset avant qu'il ne meure, et ils te considèrent comme l'un de mes hommes, alors évite de les contacter.";
			link.l1 = "Oui, quel dommage...";
			link.l1.go = "entrance_22";
		break;
		
		case "entrance_22":
			dialog.text = "Je t'ai demandé de venir non seulement pour te donner des nouvelles. J'ai reçu une lettre de notre médiateur et diplomate, Giuseppe Fazio, qui m'invite à visiter sa cabine en Caroline à minuit. Il mentionne également que je dois venir seul, car ma vie est en jeu et personne ne peut être digne de confiance\nCela a du sens, Chimiset nous a avertis d'un traître proche de moi. Pourtant, cela sent trop le piège... seul, à minuit... Normalement, le gros homme vient lui-même à moi. Quoi qu'il en soit, je vais te demander de l'aide\nTechniquement, tu n'es pas l'un de mes hommes et tu es nouveau ici. Jan t'a décrit comme un homme ingénieux et courageux avec de bonnes compétences en escrime. Je veux que tu m'escortes à la rencontre à minuit...";
			link.l1 = "Tu n'as pas besoin de me le demander, Steven. Je suis partant. Je n'aime pas non plus cette invitation - ça sent le piège.";
			link.l1.go = "entrance_23";
		break;
		
		case "entrance_23":
			dialog.text = "Peut-être que je me trompe et qu'il n'y a pas de piège, mais je ferais mieux d'être prêt. Je suis content que tu aies accepté. Viens sur le pont du 'San Augustine' à minuit, et nous irons voir Fazio, sa vieille barque n'est pas loin d'ici.";
			link.l1 = "Marché conclu. Je serai sur le pont du 'San Augustine' à minuit, bien armé.";
			link.l1.go = "entrance_24";
		break;
		
		case "entrance_24":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			pchar.quest.LSC_GotoShark.win_condition.l1 = "Timer";
			SetFunctionTimerCondition("LSC_MeetingSharkAugustine", 0, 0, 1, false); // таймер
			AddQuestRecord("SharkHunt", "22");
		break;
		
		case "caroline":
			dialog.text = "Content de te voir, "+pchar.name+"Ne perdons pas de temps et voyons ce que ce gros Fazio a à dire. Suivez-moi !";
			link.l1 = "Allons-y, Steve. Garde ton arme prête...";
			link.l1.go = "caroline_1";
		break;
		
		case "caroline_1":
			DialogExit();
			sld = characterFromId("Dodson");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload25", "CarolineBank", "barmen", "bar2", "LSC_CarolineOpen", -1);
		break;
		
		case "caroline_2":
			dialog.text = "Où est donc cet enfoiré de gros lard ? Où est-il allé ? Nous sommes ses invités et il ne nous accueille pas. Le vois-tu, "+pchar.name+" ? Peut-être devrions-nous vérifier ses coffres, il pourrait y être...";
			link.l1 = "Il ne pourra de toute façon pas ouvrir de coffre dans le monde. Chut ! Steven ! Il y a du bruit dehors...";
			link.l1.go = "caroline_3";
		break;
		
		case "caroline_3":
			dialog.text = "Merde ! Tu as raison. Il semble que nous soyons dans le pétrin."+pchar.name+".";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LSC_Caroline_DlgExit_3");
		break;
		
		case "caroline_5":
			dialog.text = "Argh ! Nous l'avons fait... Pour être honnête, je pensais que nous étions fichus.";
			link.l1 = "J'ai connu des ennuis pires que celui-ci. Mais j'admets que ces salauds étaient coriaces. Chimiset avait raison de nous avertir - Chad est un traître. Qui était la fille qui les commandait ?";
			link.l1.go = "caroline_6";
		break;
		
		case "caroline_6":
			dialog.text = "Son nom est Mary Casper, également connue sous le nom de Mary la Rouge, l'ex-petite amie du défunt Alan Milrow. Je comprends pourquoi Chad est venu ici, il voulait prendre ma place, mais que faisait-elle ici ?";
			link.l1 = "C'est bien clair. Vous avez dit qu'elle était sa maîtresse, ses intentions sont claires - la vengeance. La pauvre fille ne savait pas qu'elle se battait du même côté que l'assassin de son amant.";
			link.l1.go = "caroline_7";
		break;
		
		case "caroline_7":
			dialog.text = "Ça fait sens. Eh bien, maintenant ils vont payer pour tout ! Je vais arrêter de leur vendre des provisions - qu'ils crèvent de faim. Mes hommes peuvent résister à n'importe quel siège, si les Narvals essaient de prendre d'assaut le San Augustine, nous les abattrons comme des chiens\nIls vont regretter d'avoir agi contre moi de manière si vile. Je vais clouer le gros cul de Fazio au mur derrière ma chaise !";
			link.l1 = "Attends, Steve. Il semble que ce ne soit pas si clair. Donne-moi un jour et j'essaierai de démêler ce bazar. Je suis sûr que Chad est le seul responsable. Il a tué Milrow, a répandu la rumeur que c'était toi, a utilisé la petite amie d'Alan...";
			link.l1.go = "caroline_8";
		break;
		
		case "caroline_8":
			dialog.text = "Bien. Enquêtez. Peut-être que nous n'avons pas encore trouvé tous les comploteurs. Et je vais aller boire un peu de rhum. Et, "+pchar.name+": Je te dois une fière chandelle. Tu peux compter sur moi pour tout. Tu aurais obtenu le poste de maître d'équipage si tu avais été dans mon équipage.";
			link.l1 = "D'accord pour une telle réponse enthousiaste ! Nous travaillerons ensemble lorsque tu deviendras chef des Frères de la Côte de toute façon. Va te reposer et je vais examiner cette cabine, peut-être que je trouverai quelque chose d'utile.";
			link.l1.go = "caroline_9";
		break;
		
		case "caroline_9":
			dialog.text = "Bien. J'enverrai mes hommes ici pour nettoyer avant le matin - nous ne voulons pas effrayer les gens avec des cadavres. Eh bien, les crabes auront un festin ce soir ! À bientôt !";
			link.l1 = "À bientôt...";
			link.l1.go = "caroline_10";
		break;
		
		case "caroline_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SanAugustineResidence", "sit", "sit1", "LSC_SharkReturnSit", 10.0);
			AddQuestRecord("SharkHunt", "24");
		break;
		
		case "narval":
			dialog.text = "Eh bien, "+pchar.name+", Je suppose que votre enquête a été fructueuse ?";
			link.l1 = "On peut le dire ainsi. Les Narvals ne sont pas impliqués dans la tentative contre ta vie. Sauf Mary et ces gars-là qui nous ont rencontrés sur le 'Carolina'. Je pense qu'elle les a incités à nous attaquer. Fazio a été forcé de t'envoyer l'invitation. J'ai trouvé la lettre dans sa cabine qui explique beaucoup de choses. Lis-la.";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "(lisant)... Hum. Cela ressemble à un type de Fazio. Bien sûr, que pouvait-il faire contre Chad... il sauvait sa peau grasse. Il semble que tout cela était à cause de mon maître d'équipage...";
			link.l1 = "Vous le voyez par vous-même maintenant. Les motifs sont clairs, et nous savons pourquoi Chad a tué Chimiset et Alan. Kapper voulait devenir l'amiral de l'île. J'ai rendu visite au chef des Narvals - Donald Greenspen. Il a juré que ni lui, ni aucun de ses hommes ne complotaient contre vous.";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			dialog.text = "Le fais-tu confiance ?";
			link.l1 = "Je le fais. Donald blanchira votre nom des accusations concernant la mort d'Alan. Il est prêt à vous rendre visite personnellement et à vous présenter des excuses officielles. Vous avez été accusé à tort aussi, souvenez-vous-en ?";
			link.l1.go = "narval_3";
		break;
		
		case "narval_3":
			dialog.text = "Très bien, déclarer la guerre serait un peu exagéré. Nous ne sommes pas en position de déclencher un bain de sang. De plus, il semble que seuls quelques vauriens soient responsables de cela, pas tout le clan. \nVous dites que Donald est prêt à s'excuser ? Très bien, utilisons cela pour établir des relations positives avec les Narvals, les Rivados sont de toute façon perdus pour nous.";
			link.l1 = "C'est un bon point, Steven. Maintenant c'est le moment parfait pour cela.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			dialog.text = "D'accord. Dis à Donald que je suis prêt à le voir et à faire la paix.";
			link.l1 = "Je suis en route.";
			link.l1.go = "narval_5";
		break;
		
		case "narval_5":
			dialog.text = "Attends, "+pchar.name+"Tu as bien agi et je veux te payer avec des pièces de qualité. Tiens, prends ces cinq cents doublons.";
			link.l1 = "Merci !";
			link.l1.go = "LSC_navy";
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("SharkHunt", "27");
			pchar.questTemp.Saga.SharkHunt = "find"; //флаг - покушение предотвращено
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "shark_16"; // ноду Дональду Гринспи
			SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
			AddSimpleRumourCityTip("They say that admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are the admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		// ----------------------------------------вариант M----------------------------------------------------
		case "mary":
			dialog.text = "Dans ma prison 'Tartarus'. Tu peux y aller et le voir. Je te donnerai la clé et Chad Kapper ne te mettra pas d'obstacles en travers du chemin...";
			link.l1 = "Attends, Steven. Je pense que je ne devrais pas encore aller voir Chad Kapper...";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			dialog.text = "Et pourquoi pas ? Quoi, tu ne l'apprécies pas ?";
			link.l1 = "En fait, c'est vous qu'il n'aime pas. J'ai de mauvaises nouvelles pour vous. Chad Kapper prévoit de tenter de vous assassiner.";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "Quoi ?! Explique-toi. Qui a dit ça ?";
			link.l1 = "Laisse-moi te raconter toute l'histoire. Ce serait mieux.";
			link.l1.go = "mary_3";
		break;
		
		case "mary_3":
			dialog.text = "Eh bien, dis-moi, alors...";
			link.l1 = "Après m'être retrouvé dans la cale inondée, je suis sorti par le trou et j'ai nagé parmi les épaves pour trouver un endroit sûr. Enfin, j'ai grimpé sur la vieille flûte et suis entré dans le navire. Il y avait une bagarre entre une fille en veste rouge et deux gros gaillards...";
			if (pchar.questTemp.LSC.Mary == "alive") link.l1.go = "mary_4"; // Мэри жива
			else link.l1.go = "mary_15";
		break;
		
		case "mary_4":
			dialog.text = "Hé, il semble que Mary la Rouge ait finalement énervé quelqu'un.";
			link.l1 = "Je l'ai aidée et nous avons fini ces salauds. Nous avons eu une discussion intéressante après cela... Dis-moi, Steve, qui sont ces Narvals et Rivados, elle utilisait ces mots si souvent que j'étais trop timide pour lui demander ce qu'ils signifiaient réellement.";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "Les groupes d'habitants locaux qui vivent ici depuis longtemps. Ils sont les descendants des tout premiers colons de l'Île. Les Narvals sont principalement anglais, néerlandais et français, les Rivados sont tous noirs. Ces clans ont leurs propres chefs, leurs propres navires et ils ne laissent personne pénétrer sur leurs territoires. Vous devez connaître leurs mots de passe si vous souhaitez visiter les navires des clans. Ils les changent chaque semaine.";
			link.l1 = "Je vois maintenant. Je suppose que Mary est avec les Narvals ?";
			link.l1.go = "mary_6";
		break;
		
		case "mary_6":
			dialog.text = "Oui, cette fille expressive est de leur clan. Alors, qu'est-ce qu'elle t'a dit ?";
			link.l1 = "Chad Kapper a tué Alan Milrow, son amant, qui a été capturé par vous. Après cela, il a répandu des rumeurs sur votre implication dans cette affaire. Chad a trompé Mary et a essayé d'utiliser son désir de vengeance.";
			link.l1.go = "mary_7";
		break;
		
		case "mary_7":
			dialog.text = "Sacrebleu! Il a tué Alan ? Mais pourquoi ? Pour me laisser le blâme ?";
			link.l1 = "Pour rendre les Narvals hostiles envers vous et gagner leur confiance. Le but final de Kapper est de vous éliminer et de prendre votre place. Mary a refusé de participer à son plan et de devenir sa maîtresse - c'est pourquoi il a ordonné aux Narvals de la tuer.";
			link.l1.go = "mary_8";
		break;
		
		case "mary_8":
			dialog.text = "Te l'a-t-elle dit ?";
			link.l1 = "Oui. Et elle n'avait pas l'air de mentir. De plus, elle m'a donné une lettre de Chad Kapper. Je l'ai déjà lue, alors tu devrais faire de même.";
			link.l1.go = "mary_9";
		break;
		
		case "mary_9":
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "Hm. Oui, ce sont les écrits de Chad. Je suis très familier avec son écriture paysanne (en lisant) Argh! Incroyable! Salaud! Traître! Eh bien, je vais le pendre avec ses propres tripes ! Layton ! Rassemble cinq hommes ! À la réflexion, Layton, attends, congédié !\nNous allons le faire de manière intelligente. J'ai prévu d'améliorer nos relations avec les Rivados, c'est une occasion. Leur sorcier Chimiset est détenu à Tartarus. Une prison. Nous allons laisser les Rivados libérer eux-mêmes leur homme et, dans l'action, ils tueront le traître.\nLayton ! Va à Tartarus et retire tous nos gardes de son pont supérieur ! "+pchar.name+", tu prendras également part à cela et je suis sur le point de te confier un rôle très important. Trouve le chef des Rivados, Eddie le Noir, et négocie avec lui...";
			link.l1 = "Moi ? Hm. Mais je ne connais personne ici !";
			link.l1.go = "mary_10";
		break;
		
		case "mary_10":
			dialog.text = "So you will get to know some people soon - actually you will get to know the very first man of the entire Rivados clan. You are the most suitable candidate to perform the diplomatic part of my plan. My pirates won't be able to come through Rivados territories easily; also I don't have men with decent oratory skills.";
			link.l1 = "Eh bien, soit. Je m'en occupe. Que dois-je faire ?";
			link.l1.go = "mary_11";
		break;
		
		case "mary_11":
			GiveItem2Character(pchar, "key_capper");
			Log_Info("You have received 50 doubloons");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "gold_dublon", 50);
			dialog.text = "Prends cette clé. Elle ouvre toutes les portes du 'Tartarus'. Prends aussi ces cinquante doublons. D'abord, tu devrais aller à 'Carolina', acheter un mot de passe pour accéder au territoire des Rivados. Parle à Fazio, c'est notre médiateur, un mot de passe te coûtera cinquante doublons. Ensuite, tu devrais aller au 'Protecteur'\nC'est la résidence de Black Eddie. Dis-lui que Chad Kapper est du côté des Narvals, a cessé de suivre mes ordres et prévoit de tuer Chimiset. Donne-lui la clé, dis-lui de prendre un bon nombre de ses combattants et d'attaquer 'Tartarus'\nNous attraperons deux oiseaux d'une pierre : les Rivados nous considéreront comme leurs alliés et Kapper mourra de la main des Noirs. Je ne peux pas dire que j'envie cet homme. Compris?";
			if (pchar.questTemp.LSC.Mary == "alive")// Мэри жива
			{
				link.l1 = "Je comprends - mais où trouver 'Protecteur' et 'Caroline' ?";
				link.l1.go = "mary_12";
			}
			else
			{
				link.l1 = "Écoute, Steve, dis-moi qui sont ces Rivados et Narvals. Tu parles d'eux tout le temps, mais je n'ai toujours aucune idée de qui ils sont.";
				link.l1.go = "mary_12_1";
			}
		break;
		
		case "mary_12_1":
			dialog.text = "Les Narvals et les Rivados sont les clans locaux. Les clans vivent ici depuis très longtemps. Ils représentent les descendants des premiers colons. Les Narvals sont principalement Anglais, Hollandais et Français, les Rivados sont tous Nègres. Chaque clan a un chef, ils possèdent plusieurs navires et ne laissent pas les autres pénétrer leur territoire\nVous devez connaître les mots de passe pour leur rendre visite. Ils changent de mots de passe chaque semaine.";
			link.l1 = "Maintenant, je comprends. Dis-moi - où trouver 'Protecteur' et 'Caroline'?";
			link.l1.go = "mary_12";
		break;
		
		case "mary_12":
			dialog.text = "Facile comme bonjour. Quittez ma résidence, traversez un pont et tournez à gauche. Ce sera Carolina. Trouver Protector est un peu plus délicat : après avoir traversé le pont, tournez à droite et allez vers Santa Florentina en passant par les planches\nTrouvez-y les soldats Rivados. Ils vous demanderont un mot de passe. Dites-le fort et clair. Ensuite, entrez dans Fury et accédez à Protector par la poupe.";
			link.l1 = "Eh bien, je vois maintenant. Je pense que je ne vais pas les regretter.";
			link.l1.go = "mary_13";
		break;
		
		case "mary_13":
			dialog.text = "Très bien, alors. Va-t'en, l'ami !";
			link.l1 = "À bientôt !";
			link.l1.go = "mary_14";
		break;
		
		case "mary_14":
			DialogExit();
			NextDiag.CurrentNode = "dodson_warwait";
			AddQuestRecord("SharkHunt", "32");
			sld = characterFromId("Eddy");
			sld.dialog.currentnode = "capper"; // ноду Эдди
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			pchar.questTemp.LSC = "mary_go"; //меняем флаг
		break;
		
		case "dodson_warwait":
			dialog.text = "Es-tu encore là ? Va chez les Rivados maintenant !";
			link.l1 = "Je suis en route !";
			link.l1.go = "exit";
			NextDiag.TempNode = "dodson_warwait";
		break;
		
		case "mary_15":
			dialog.text = "Hé, il semble que Mary la Rouge ait enfin énervé quelqu'un.";
			link.l1 = "Oui. Elle a fâché Chad Kapper. J'avais rejoint le combat, mais, malheureusement, je n'ai pas pu sauver la fille, un des assaillants l'a coupée avec son sabre.";
			link.l1.go = "mary_16";
		break;
		
		case "mary_16":
			dialog.text = "Je suis désolé pour elle, c'est sûr, mais c'était sans aucun doute de sa faute. Mary avait toujours cherché les ennuis. Et qu'en est-il de Chad Kapper ? C'est mon maître d'équipage, en fait.";
			link.l1 = "Votre contremaître ? Hi-hi... Tenez, lisez cette lettre. Je l'ai trouvée sur le corps de la fille. Vous verrez maintenant qui a ordonné de la tuer et pourquoi. Kapper prévoit un attentat contre votre vie.";
			link.l1.go = "mary_9";
		break;
		
		// Каппер сбежал
		case "Chad_escape":
			dialog.text = "Où as-tu été si longtemps ? On m'a dit que les Rivados avaient libéré leur sorcier...";
			link.l1 = "J'étais retenu en otage sur le 'Protector' pour garantir leur sécurité contre une embuscade. Ils ont libéré Chimiset, oui, mais Chad a réussi à s'échapper.";
			link.l1.go = "Chad_escape_1";
		break;
		
		case "Chad_escape_1":
			dialog.text = "Merde ! Ne jamais traiter avec les noirs, disent-ils... Ils n'ont même pas pu accomplir une tâche aussi simple ! Que les Rivados aillent se faire foutre !";
			link.l1 = "Chad s'est caché parmi les Narvals...";
			link.l1.go = "Chad_escape_2";
		break;
		
		case "Chad_escape_2":
			dialog.text = "Bien sûr, il l'a fait ! Il n'est pas idiot et il a réalisé que les Rivados n'auraient pas pu entrer dans le Tartare sans mon aide. Maintenant, il se cachera et attaquera depuis l'ombre. Layton ! Renforcez les postes ! Gardez les yeux ouverts en permanence ! Je paierai une fortune à celui qui se débarrassera de Kapper !";
			link.l1 = "Très bien, Steven. Je dois y réfléchir. Peut-être que je pourrai retrouver Chad. À bientôt.";
			link.l1.go = "Chad_escape_3";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Chad_escape_3":
			DialogExit();
			if (pchar.questTemp.LSC.Mary == "alive") 
			{
				pchar.questTemp.Saga.SharkHunt = "mary_whiskey"; // к Мэри
				AddQuestRecord("SharkHunt", "34");
			}
			else
			{ // не уберег Мэри - допетривай сам, куда идти
				pchar.questTemp.Saga.SharkHunt = "trader_whiskey"; // флаг на магазин - поиск виски
			}
			NextDiag.CurrentNode = "Total_wait";
			// добавим немного атмосферы - уберем Акселя до утра
			sld = characterFromId("Axel");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "goto", "goto5");
			sld = GetCharacter(NPC_GenerateCharacter("AxelHelper", "citiz_52", "man", "man", 35, PIRATE, 1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 100, 100, "blade_21", "pistol4", "bullet", 200);
			sld.dialog.Filename = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "AxelHelper";
			LAi_SetOwnerType(sld);
			ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "barmen", "stay");
			LAi_group_MoveCharacter(sld, "LSC_NARVAL");
			SetFunctionTimerCondition("LSC_AxelReturnStore", 0, 0, 1, false); // таймер на возврат Акселя
		break;
		
		case "whiskey":
			dialog.text = "Que s'est-il passé, "+pchar.name+" ? Vous avez l'air d'être poursuivi par Lucifer lui-même.";
			link.l1 = "Ils t'ont apporté un tonneau de whisky ?";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "Quel tonneau ?";
			link.l1 = "VOUS ONT-ILS APPORTÉ UN TONNEAU DE WHISKY?!";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Pourquoi cries-tu ainsi, camarade ? Non, ils ne l'ont pas fait. Quel est le problème ?";
			link.l1 = "Dieu merci, je suis arrivé à temps... Chad Kapper a acheté un tonneau de Bushmills à Axel Yost...";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "Bushmills ? C'est mon préféré ! Je n'en ai pas bu depuis des lustres !";
			link.l1 = "Oui-oui. Et Kapper le sait aussi. Il a également demandé à son ami, Marcello Cyclope, d'acheter de l'arsenic à Sancho Carpentero. Tu vois pourquoi ?";
			link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			dialog.text = "Penses-tu qu'il va m'empoisonner ?";
			link.l1 = "Sans aucun doute ! C'est pourquoi j'étais si pressé. S'ils t'apportent un tonneau de whisky - ne le bois pas. C'est empoisonné.";
			link.l1.go = "whiskey_5";
		break;
		
		case "whiskey_5":
			dialog.text = "Heh, merci pour l'avertissement ! Je ferai attention. Attends, où vas-tu maintenant ?";
			link.l1 = "Je dois trouver Kapper et Cyclope. J'ai une idée d'où les trouver. À bientôt !";
			link.l1.go = "whiskey_6";
		break;
		
		case "whiskey_6":
			DialogExit();
			pchar.questTemp.LSC.Dodson_warning = "true"; // Акула предупрежден
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "45");
		break;
		
		case "whiskey_7":
			dialog.text = "Ha ! Je suis ravi de te voir, l'ami ! On dirait que je te dois la vie.";
			link.l1 = "A-t-on apporté du whisky ?";
			link.l1.go = "whiskey_8";
		break;
		
		case "whiskey_8":
			dialog.text = "Ils en ont ! Bushmills, comme tu l'as dit. Notre cher Fazio a été si aimable... Je l'ai arrêté pour enquêter...";
			link.l1 = "A-t-il avoué ?";
			link.l1.go = "whiskey_9";
		break;
		
		case "whiskey_9":
			dialog.text = "Oui. Il dit que Kapper l'a forcé à faire ça. Il avait peur et... m'a apporté le tonneau comme cadeau des Narvals.";
			link.l1 = "Kappler est mort. Je l'ai éliminé ainsi que ses amis Narvals. Maintenant, il ne reste plus qu'un salaud - Cyclope Marcello... Je suis certain que ce gros porc sait où il se trouve. Laissez-moi le presser un peu !";
			link.l1.go = "whiskey_10";
		break;
		
		case "whiskey_10":
			dialog.text = "Bien sûr. Essayez juste de ne pas le tuer, notre pauvre Fazio est en assez mauvaise santé.";
			link.l1 = "Je serai doux... très doux, bon sang !";
			link.l1.go = "whiskey_11";
		break;
		
		case "whiskey_11":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			chrDisableReloadToLocation = true;//закрыть локацию
			sld = CharacterFromID("Facio");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "poison":
			pchar.questTemp.LSC.Dodson_poison = "true"; // разговор состоялся
			dialog.text = "Argh... "+pchar.name+", mon ami, quelque chose ne tourne pas rond chez moi...";
			link.l1 = "Steven ! As-tu bu le whisky ? Merde, l'as-tu vraiment bu ?!";
			link.l1.go = "poison_1";
		break;
		
		case "poison_1":
			dialog.text = "Oui... C'est le meilleur whiskey irlandais... Giuseppe Fazio me l'a apporté aujourd'hui. Il a dit que c'était un cadeau du chef des Narvals... un gage de paix... oh, ça fait mal... On dirait que c'est la fin pour moi.";
			link.l1 = "Satané! Le whisky était empoisonné à l'arsenic! Chad Kapper et Marcello Cyclope ont fait ça!";
			link.l1.go = "poison_2";
		break;
		
		case "poison_2":
			dialog.text = "Argh... le bosco m'a finalement eu... merde !";
			if (CheckCharacterItem(pchar, "ultimate_potion"))
			{
				link.l1 = "Tu ne vas pas mourir ! Tu m'entends ? Tu ne mourras pas ! Vite, prends cette fiole. C'est la potion de guérison la plus puissante au monde, elle guérit tout. Bois-la... maintenant !";
				link.l1.go = "poison_3";
			}
			else
			{
				link.l1 = "Steven !";
				link.l1.go = "dodson_poison";
			}
		break;
		
		case "dodson_poison": // Акула умирает
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			SetFunctionTimerCondition("LSC_SetDexterAdmiral", 0, 0, 1, false); // через день Декстера в адмиралы
			if (CheckAttribute(pchar, "questTemp.LSC.CapperDie_Aeva"))
			{
				AddQuestRecord("SharkHunt", "41");
				sld = CharacterFromID("Facio");
				sld.dialog.currentnode = "whiskey";
				sld.greeting = "facio_2";
				sld.quest.poisonnode = 1;
			}
			else AddQuestRecord("SharkHunt", "42");
			pchar.questTemp.Saga.DodsonDie = "true"; // атрибут Саге что Акула погиб
		break;
		
		case "poison_3":
			RemoveItems(pchar, "ultimate_potion", 1);
			Log_Info("Comanche potion was used");
			Log_Info("Poison was cured!");
			PlaySound("interface\notebook.wav");
			dialog.text = "Oh... "+pchar.name+", ça a vraiment aidé. Je me sens encore un peu mal, mais la douleur est presque partie...";
			link.l1 = "Cette potion neutralise même les poisons les plus mortels. Bois-la entièrement ! Oui...";
			link.l1.go = "poison_4";
		break;
		
		case "poison_4":
			LAi_SetStayType(npchar);
			dialog.text = "Un miracle... Je vais bien maintenant. Merci, ami, je ne l'oublierai jamais...";
			if (CheckAttribute(pchar, "questTemp.LSC.CapperDie_Aeva"))
			{
				link.l1 = "Tu ferais mieux de te reposer maintenant. Tu as l'air d'un homme mort. Ce salaud de Kapper ne pourra plus nous menacer - je me suis occupé de lui et de quelques Narvals aussi. Il ne reste que Marcello Cyclope. Tu as dit que Fazio t'a apporté le whisky, n'est-ce pas ?";
				link.l1.go = "poison_5";
			}
			else
			{
				link.l1 = "Tu ferais mieux de te reposer maintenant. Tu ressembles à un homme mort. Tu as dit que Fazio t'avait apporté le whisky, n'est-ce pas ?";
				link.l1.go = "poison_7";
			}
		break;
		
		case "poison_5":
			dialog.text = "Oui. J'aurais vraiment dû prêter attention à son visage pâle et ses mains tremblantes...";
			link.l1 = "Il semble qu'il ait été forcé de faire cela. Très bien, je vais rendre visite à ce gros porc et obtenir les informations de lui. Je suis sûr qu'il sait ce dont j'ai besoin. Remets-toi bien !";
			link.l1.go = "poison_6";
		break;
		
		case "poison_6":
			DialogExit();
			sld = CharacterFromID("Facio");
			sld.dialog.currentnode = "whiskey";
			sld.greeting = "facio_2";
			sld.quest.poisonnode = 1;
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "40");
		break;
		
		case "poison_7":
			dialog.text = "Oui. J'aurais vraiment dû prêter attention à son visage pâle et à ses mains tremblantes...";
			link.l1 = "Il semble qu'il ait été contraint de le faire. Soit, j'attraperai ce gros cochon un jour, mais pour l'instant je dois m'occuper de Kapper et Cyclope. Je sais où ils se cachent. Remets-toi bien !";
			link.l1.go = "poison_8";
		break;
		
		case "poison_8":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "43");
		break;
		
		case "clear":
			dialog.text = "Que dis-tu, "+pchar.name+"? Je sais déjà que tu as eu affaire à Kapper sur 'Eva'. Et tu n'as même pas nettoyé là-bas, ha-ha ! Pour être honnête, je suis admiratif ! Tuer Chad et ses hommes, n'est-ce pas quelque chose ! Oui, Jan avait raison de te louer.";
			link.l1 = "Non seulement j'ai réglé le compte de Kapper, mais j'ai aussi empêché un attentat contre ta vie. On allait t'empoisonner, Steven, mais j'ai empêché ces salauds de le faire.";
			link.l1.go = "clear_1";
		break;
		
		case "clear_1":
			dialog.text = "Pour m'empoisonner ? Mais comment ?";
			link.l1 = "Chad a acheté un tonneau de whiskey irlandais Bushmills à Axel...";
			link.l1.go = "clear_2";
		break;
		
		case "clear_2":
			dialog.text = "Bushmills ? C'est mon préféré ! Je n'en ai pas bu depuis des lustres !";
			link.l1 = "Oui-oui. Et Kapper le sait aussi. Il a également demandé à son pote, Marcello Cyclope, d'acheter de l'arsenic à Sancho Charpentier. Ensuite, lui et ses copains ont pris Fazio et sont descendus dans la soute de 'Eva'. Il allait empoisonner le whisky et forcer Fazio à te l'apporter comme un cadeau des Narvals.";
			link.l1.go = "clear_3";
		break;
		
		case "clear_3":
			dialog.text = "Ha ! Bien sûr, j'aurais bu une pinte de whisky immédiatement...";
			if (CheckCharacterItem(pchar, "cask_whisky"))
			{
				link.l1 = "Chad comptait là-dessus. Mais il a échoué - il n'a même pas eu le temps d'y mettre de l'arsenic. Oui, et j'ai pris le tonneau avec moi. Tu peux l'avoir en cadeau.";
				link.l1.go = "clear_4";
			}
			else
			{
				link.l1 = "Chad comptait là-dessus. Mais il a échoué - il n'a même pas eu le temps d'y mettre de l'arsenic.";
				link.l1.go = "clear_7";
			}
		break;
	
		case "clear_4":
			RemoveItems(pchar, "cask_whisky", 1);
			PlaySound("interface\notebook.wav");
			dialog.text = "Montre-moi... "+pchar.name+", c'est un vrai Bushmills ! Le meilleur whisky irlandais ! Argh, j'en ai rêvé pendant des années ! Toi, toi... Nom d'un chien ! Tu as éliminé Chad et tu as trouvé un si joli whisky !\nJe vais te donner un de mes meilleurs talismans. C'est le Marteau de Thor, il est éternel. Ton canonnier va l'adorer !";
			link.l1 = "Merci ! Je suis très content, moi aussi.";
			link.l1.go = "clear_5";
		break;
		
		case "clear_5":
			GiveItem2Character(pchar, "talisman3"); 
			PlaySound("interface\notebook.wav");
			Log_Info("You have received a 'Thor's hammer' amulet");
			dialog.text = "J'ai hâte de boire une pinte de ce whisky magnifique... "+pchar.name+", nous ferons la fête ce soir ! Et viens me voir demain. En attendant, je réfléchirai à tes paroles et aux actions de Chad...";
			link.l1 = "D'accord, Steven, je ne te dérangerai pas pendant... ta détente, ha-ha !";
			link.l1.go = "clear_6";
			AddQuestRecord("SharkHunt", "53");
		break;
		
		case "clear_6":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			DeleteAttribute(pchar, "questTemp.LSC.Whiskey_clear");
			if (CheckAttribute(pchar, "questTemp.LSC.CyclopDie"))
			{
				SetFunctionTimerCondition("LSC_WhiskeyStoryFinal_1", 0, 0, 1, false); // адмирал зовет
				DeleteAttribute(pchar, "questTemp.LSC.CyclopDie");
			}
		break;
		
		case "clear_7":
			dialog.text = "Vous m'avez dit quelque chose de très important. Je réfléchirai à vos paroles et aux actions de Chad... et ensuite je vous appellerai.";
			link.l1 = "D'accord, Steven. Je vais attendre !";
			link.l1.go = "clear_6";
			AddQuestRecord("SharkHunt", "54");
		break;
		
		case "whyskey_final":
			dialog.text = "Ha, te voilà, "+pchar.name+". Maintenant que tout le monde est là, nous pouvons commencer. Je vous ai convoqués, toi et Layton, pour discuter de la situation et décider quoi faire des Narvals.";
			link.l1 = "Que veux-tu dire - que faire des Narvals ?";
			link.l1.go = "whyskey_final_1";
		break;
		
		case "whyskey_final_1":
			dialog.text = "Une tentative sur ma vie a été organisée par Chad qui avait le soutien direct des Narvals. Je reconnais cela comme un acte d'agression ouvert. Considérant le fait que nous avons une alliance à court terme avec les Rivados, je propose la chose suivante\nNous formons une alliance avec les Rivados, préparons une opération et exterminons le clan Narval une fois pour toutes. J'en ai assez de leur attitude de bandits. Vous, "+pchar.name+", vont à nouveau jouer le rôle de diplomate\nParle à Black Eddie et Chimiset, convaincs-les de se joindre à nous dans la bataille contre notre ennemi commun. Je pense qu'ils t'écouteront, ils te croient être leur allié\nDexter élaborera un plan d'attaque, il connaît tout de la géographie de l'île. Layton, as-tu déjà des réflexions ?";
			link.l1 = "";
			link.l1.go = "whyskey_final_2";
		break;
		
		case "whyskey_final_2": // перекидываем ноду Декстеру
			DialogExit();
			sld = characterFromId("Dexter");
			sld.greeting = "";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "whyskey_final_3":
			dialog.text = "Une idée sage. Contraints de se retirer sur le San Gabriel, les Narvals, peut-être, ne céderont pas trop tôt à nos troupes - mais ils mourront rapidement sans aucune provision ou ils seront forcés de lancer une attaque désespérée. Que dis-tu, "+pchar.name+"?";
			link.l1 = "Que puis-je dire... Je dis que déclarer la guerre aux Narvals est une erreur politique.";
			link.l1.go = "whyskey_final_4";
		break;
		
		case "whyskey_final_4":
			dialog.text = "Et tu dis cela après avoir tué tous les hommes de Chad ? N'oublie pas qu'ils étaient tous des Narvals !";
			link.l1 = "Pas tous. L'un des premiers de ces salauds, Marcello Cyclope, n'était pas un Narval. En fait, il était fidèle aux Rivados et, peut-être, il prévoyait de les rejoindre. C'est un mulâtre, après tout. Je pense que les Narvals ne sont pas responsables de l'attentat contre ta vie - seulement quelques salauds, qui ont été recrutés par Kapper.";
			link.l1.go = "whyskey_final_5";
		break;
		
		case "whyskey_final_5":
			dialog.text = "Et que proposes-tu ? Ignorer tout cela ?";
			link.l1 = "Je suggère de me cantonner à mon rôle de diplomate - mais cette fois, je négocierai avec le chef des Narvals, Donald. De plus, laissez-moi vous donner mon point de vue concernant les conséquences possibles d'une attaque contre les Narvals.";
			link.l1.go = "whyskey_final_6";
		break;
		
		case "whyskey_final_6":
			dialog.text = "Continue.";
			link.l1 = "Tant que je vois, la paix sur l'Île Justice n'est possible que grâce à la rivalité entre deux clans qui sont presque égaux en force. Vos combattants sont la troisième puissance, et ils peuvent aider l'un ou l'autre à atteindre la victoire. Mais tant les Rivados que les Narvals sont forts et une victoire coûtera trop cher au vainqueur dans tous les cas.";
			link.l1.go = "whyskey_final_7";
		break;
		
		case "whyskey_final_7":
			dialog.text = "";
			link.l1 = "Le prix de la destruction des Narvals sera de nombreuses vies de vos hommes et de ceux des Rivados. De plus, Layton a dit que le siège de San Gabriel prendra beaucoup de temps, et nous pourrions également faire face à une agression possible des Rivados si nous perdons trop d'hommes...";
			link.l1.go = "whyskey_final_8";
		break;
		
		case "whyskey_final_8":
			dialog.text = "Bonjour, mon ami.";
			link.l1 = "N'oublie pas que les deux clans brûlent de dominer l'Île et il n'y a pas si longtemps, ils étaient tes ennemis. Donc, à mon avis, le massacre serait une véritable calamité pour les habitants ordinaires.";
			link.l1.go = "whyskey_final_9";
		break;
		
		case "whyskey_final_9":
			dialog.text = "Hm. Tes paroles semblent sages, mais tu ne m'as pas encore convaincu.";
			link.l1 = "Je dois aussi quitter l'Île d'une manière ou d'une autre, donc je dois atteindre la statue de Kukulcan au fond de la mer. Les Rivados ne peuvent pas m'aider - peut-être que les Narvals le peuvent ? Les combattre ne m'aidera pas non plus.";
			link.l1.go = "whyskey_final_10";
		break;
		
		case "whyskey_final_10":
			if (pchar.questTemp.LSC.Mary != "die") sTemp = "Ha! And I guess that there is one more reason why you don't want to make Narwhals our enemies. That red-haired girl of Ceres Smithy, right, friend? Am I right? Don't worry about her, "+pchar.name+", since you care about her this much - we will take her in the safe place before fighting starts.\n";
			else sTemp = "";
			dialog.text = "Bonjour, mon ami."+sTemp+"Mais je suis d'accord si tu es si déterminé. Va voir Donald Greenspen, le chef des Narvals. Sa résidence est à l'arrière de l'Esmeralda. Voyons ce que ce scélérat va nous dire.";
			link.l1 = "Bien. Je suis en route.";
			link.l1.go = "whyskey_final_11";
		break;
		
		case "whyskey_final_11":
			DialogExit();
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "negotiations"; // ноду Гринспи
			sld = characterFromId("Dexter");
			LAi_SetHuberType(sld);
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "negotiations_wait";
			pchar.questTemp.LSC.Donald_enter = "true";
			AddQuestRecord("SharkHunt", "55");
		break;
		
		case "negotiations_wait":
			dialog.text = "Va voir Donald, mon pote, et fais-lui lécher tes bottes, ha-ha ! Je t'attendrai.";
			link.l1 = "Je suis en route.";
			link.l1.go = "exit";
			NextDiag.TempNode = "negotiations_wait";
		break;
		
		case "peace":
			dialog.text = "Alors, as-tu parlé à Donald ? Je vois que tu l'as fait...";
			link.l1 = "Oui. Il n'a pas ordonné à ses hommes de te faire du mal. Tous les Narvals qui ont participé à la tentative ont été recrutés par Chad Kapper. Il est très contrarié et nous assure que les Narvals n'ont pas de mauvaises intentions envers toi. Il est prêt à te présenter personnellement ses excuses pour cette tentative sur ta vie et pour t'avoir suspecté du meurtre d'Alan.";
			link.l1.go = "peace_1";
		break;
		
		case "peace_1":
			dialog.text = "Est-il prêt à venir ici et dire toutes ces choses?";
			link.l1 = "Il a juré sur la Bible.";
			link.l1.go = "peace_2";
		break;
		
		case "peace_2":
			dialog.text = "Heh, peut-être que cela suffira. Il semble que le seul salaud à blâmer soit mon ancien second.";
			link.l1 = "J'en suis absolument sûr, Steven. Nous n'avons pas besoin de cette guerre. Personne n'en a besoin.";
			link.l1.go = "peace_3";
		break;
		
		case "peace_3":
			dialog.text = "D'accord ! Marché conclu. Je suis prêt à accepter Donald avec ses excuses, mais il ferait mieux de se dépêcher. Va lui dire cela.";
			link.l1 = "Tout de suite, Steven.";
			link.l1.go = "peace_4";
		break;
		
		case "peace_4":
			if (pchar.questTemp.LSC.Mary == "alive") sTemp = "Take your Mary there and live your lives together, there is plenty of free space.";
			else sTemp = "";
			dialog.text = "Attends ! "+pchar.name+", Je suis très heureux que vous soyez apparu ici, sur l'Île. Jan vous tient en haute estime, mais vous avez surpassé toutes les attentes. Si vous étiez dans mon équipage... en fait, je vous offre la position de Kapper, pendant que vous êtes ici. Vous commanderez ma garnison sur 'Tartarus'. "+sTemp+".";
			if (pchar.questTemp.LSC.Mary == "alive") link.l1 = "Non, Steven, merci beaucoup, mais je ne vais pas rester ici longtemps. Trouve quelqu'un d'autre pour ça. Et concernant Mary - nous nous débrouillons bien sur le 'Ceres Smithy'.";
			else link.l1 = "Non, Steven, merci beaucoup, mais je ne vais pas rester ici longtemps. Trouve quelqu'un d'autre pour ça.";
			link.l1.go = "peace_5";
		break;
		
		case "peace_5":
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Quoi qu'il en soit, ami. Ainsi soit-il. Je vous prie d'accepter ce présent de ma part. Je pense que vous trouverez ces cinq cents doublons utiles.";
			link.l1 = "Merci!";
			link.l1.go = "LSC_navy";
			AddQuestRecord("SharkHunt", "57");
			pchar.questTemp.Saga.SharkHunt = "find"; //флаг - покушение предотвращено
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "negotiations_17"; // ноду Дональду Гринспи
			AddSimpleRumourCityTip("They say that admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are the admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		case "LSC_navy":
			dialog.text = "Parlons de notre affaire... Prenez ces instructions de navigation. Utilisez-les pour revenir ici à bord d'un navire et en un seul morceau\nSans elles, vous ne parviendrez pas à trouver un passage ici à cause des récifs et des tempêtes autour de l'Île, donc votre navire rejoindra probablement ses sœurs ici. Rappelez-vous que vous devez utiliser un navire relativement petit pour passer les récifs. Lougre, goélette, brigantin, brick... Quatrième classe, pas plus grand\nVotre objectif est de quitter cet endroit avec ces instructions de navigation dans une poche et ensuite de revenir me chercher à bord d'un navire. Une fois que je suis de retour, je vous rejoindrai, vous et Svenson, dans votre jeu. Je n'ai aucune idée de comment vous pouvez quitter l'île, cependant. Seul vous pouvez vous aider dans cette affaire, et peut-être votre Kukulcan...";
			link.l1 = "Drôle, mais je compte en fait sur son aide. Merci pour les instructions de navigation, Steven. Je trouverai encore le moyen de quitter cette île.";
			link.l1.go = "LSC_navy_1";
		break;
		
		case "LSC_navy_1":
			GiveItem2Character(pchar, "LSC_navigation_map");
			dialog.text = "Je vous souhaite bonne chance, alors. Dépêchez-vous si vous le pouvez, mes entrepôts se vident assez vite, et bientôt il n'y aura plus de provisions du tout. Vous savez de quoi sont capables des hommes affamés et armés, n'est-ce pas ?";
			link.l1 = "Je le fais. Maintenant, je dois y aller. À bientôt !";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dodson_wait";
			AddQuestRecord("LSC", "5");
			// убираем квестовые предметы
			sld = ItemsFromID("key_capper");
			sld.price = 10;
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
		break;
		
		case "Dodson_wait":
			dialog.text = " As-tu trouvé le moyen de quitter l'île, "+pchar.name+"?";
			link.l1 = "Pas encore, Steven. J'y travaille encore.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dodson_wait";
		break;
		
		// --> информационный блок
		case "Total_wait":
			dialog.text = "Eh bien, qu'as-tu, "+pchar.name+"Avez-vous   des nouvelles   intéressantes ?";
			
			if (!CheckAttribute(npchar, "quest.items") && CheckAttribute(npchar, "quest.takeitems"))
			{
				link.l1 = "Steven, je voudrais te demander de me rendre mes affaires confisquées.";
				link.l1.go = "Items";
			}
			if (!CheckAttribute(npchar, "quest.story"))
			{
				link.l2 = "Steven, dis-moi en plus sur cette île.";
				link.l2.go = "Story_island";
			}
			if (!CheckAttribute(npchar, "quest.natan"))
			{
				link.l3 = "Es-tu sûr que Hawk n'est pas sur l'île ? Il est passé par le portail, donc il doit être ici.";
				link.l3.go = "Natan";
			}
			if (!CheckAttribute(npchar, "quest.whiteboy"))
			{
				link.l4 = "Connaissez-vous un homme surnommé le Garçon Blanc ?";
				link.l4.go = "Whiteboy";
			}
			if (!CheckAttribute(npchar, "quest.ships"))
			{
				link.l5 = "Quels territoires ici appartiennent aux Narvals et aux Rivados ?";
				link.l5.go = "ships";
			}
			if (!CheckAttribute(npchar, "quest.parol"))
			{
				link.l6 = "Comment puis-je apprendre les mots de passe pour monter à bord des navires du clan?";
				link.l6.go = "parol";
			}
			if (!CheckAttribute(npchar, "quest.map"))
			{
				link.l7 = "Écoute, y a-t-il une carte de l'Île ?";
				link.l7.go = "map";
			}
			if (!CheckAttribute(npchar, "quest.blade"))
			{
				link.l8 = "Vous avez une épée si intéressante. Je n'ai jamais rien vu de tel auparavant...";
				link.l8.go = "blade";
			}
			link.l9 = "Pas de questions pour le moment. Mais j'en aurai peut-être bientôt...";
			link.l9.go = "exit";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Items":
			dialog.text = "Ah, oui, bien sûr! J'avais complètement oublié... Tes affaires sont en haut dans le coffre. Tu peux les prendre. Layton ne t'arrêtera pas.";
			link.l1 = "Merci !";
			link.l1.go = "exit";
			npchar.quest.items = "true";
			NextDiag.TempNode = "Total_wait";
			ref location = &Locations[FindLocation(pchar.location)];
			DeleteAttribute(location, "private1.key");
			for (i=1; i<=10; i++) // можно лезть в сундук
			{
				sld = characterFromId("SharkSoldInside_"+i);
				DeleteAttribute(sld, "watchBoxes");
			}
		break;
		
		case "Story_island":
			dialog.text = "Cette île doit être très ancienne. J'ai vu de vieilles caravelles sur l'anneau extérieur, elles ont plus de cent ans. Son existence est possible grâce à de grandes eaux peu profondes et un courant fort qui amène ici des carcasses de navires. Les gens vivent ici depuis longtemps. Il y a ceux qui sont nés ici et n'ont jamais quitté.\nDes clans se sont formés juste après que l'expédition de Betancourt ait échoué ici. D'ailleurs, le San Augustine et le Tartarus faisaient partie de cette expédition. Le Tartarus avait beaucoup d'esclaves noirs dans ses cales. Ils ont fondé le clan Rivados en l'honneur de Pedro Rivados, leur chef. Il avait déclenché une révolte et tenté de capturer le Tartarus, mais ils ont échoué. L'homme a été condamné à une mort lente.\nLes esclaves ont obtenu leur liberté ici et se sont immédiatement opposés au reste des habitants. Leur demande de domination et leurs traditions africaines ont poussé la plupart des chrétiens à s'unir, formant un clan des Narvals.\nLe clan des Narvals comptait de nombreux mercenaires, soldats, officiers et aventuriers dans ses rangs, ils rassemblaient des provisions et formaient une petite armée professionnelle prête à combattre les Rivados avec leur avantage en nombres. Depuis lors, les Narvals sont devenus très sélectifs dans l'acceptation de nouveaux recrues et les Rivados ont limité leurs ambitions. Vous pouvez voir les résultats maintenant.";
			link.l1 = "Y avait-il des liens entre L'Île Justice et le monde extérieur ?";
			link.l1.go = "Story_island_1";
		break;
		
		case "Story_island_1":
			dialog.text = "Il n'y a eu aucune connexion depuis dix ans. Les habitants commerçaient un temps avec Cuba, échangeant de l'or et des biens précieux contre de la nourriture. Mais ils ne le font plus.";
			link.l1 = "Hm. Il semble donc que Svenson et le Pasteur Noir avaient tous deux raison... Et pourquoi les gens n'ont-ils pas quitté l'Île, alors qu'ils en avaient encore la possibilité ?";
			link.l1.go = "Story_island_2";
		break;
		
		case "Story_island_2":
			dialog.text = "Certaines personnes l'ont fait, mais la majorité a décidé de rester. Beaucoup ont trouvé un foyer ici, beaucoup d'autres y sont nés. Ils ne veulent pas retourner. Cet endroit semble beaucoup mieux pour eux... Certains ont trop peur de voyager à travers la zone des tempêtes sur de vieux bateaux. Quant aux Rivados - ils n'ont pas d'autre choix que de rester ici.";
			link.l1 = "Et pourquoi es-tu venu ici ? Tu as abandonné ton excellent frégate, choisissant un brick à la place...";
			link.l1.go = "Story_island_3";
		break;
		
		case "Story_island_3":
			dialog.text = "J'ai été accusé du meurtre de Blaze Sharp. Je n'ai aucune idée pourquoi. Évidemment, quelqu'un joue salement. Le nombre de mes ennemis a commencé à croître rapidement, donc j'ai dû quitter l'Isla Tesoro et attendre ici. Je connaissais cet endroit depuis très longtemps. J'ai laissé ma frégate, car elle était trop grande pour contourner les récifs locaux. \nJ'ai été attaqué par les Narvals et les Rivados dès mon arrivée ici. Ils n'ont pas apprécié mon arrivée. Ils se sont approchés de mon navire la nuit sur des chaloupes et l'ont incendié. Nous avons écrasé leurs barques avec nos canons et nos mousquets. Mais le feu a fait son œuvre - ma brigantine a été brûlée. \nNous sommes devenus furieux, avons envahi l'île, pris d'assaut le San Augustine et leur avons montré comment les corsaires se battent. Ils n'ont pas pu supporter notre pression et ont rapidement tourné le dos comme des lâches. Nous avons capturé San Augustine, il s'est avéré que ces imbéciles l'utilisaient comme entrepôt de provisions. Maintenant, ils doivent l'acheter chez moi au prix que je fixe. \nNous avons également capturé les chefs locaux : le chef des Narvals, Alan Milrow, et le leader spirituel des Rivados, Chimiset. Layton a passé les quelques jours suivants à explorer la région et nous avons attaqué le Tartarus - un point faible de leurs défenses. \nMaintenant, nous détenons deux de ces navires et les clans doivent s'habituer à notre présence. De nos jours, nous avons une sorte de paix ici. Quant aux autres locaux, ils semblent apprécier l'idée d'une troisième force.";
			link.l1 = "Maintenant je comprends. Merci pour l'histoire !";
			link.l1.go = "exit";
			npchar.quest.story = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Natan":
			dialog.text = "Je ne peux pas l'affirmer avec certitude, mais je ne l'ai pas vu ici, en tout cas. Ni dans les rues, ni à la taverne, ni sur les navires du clan. Vous êtes le premier à me dire que Hawk devrait être dans les parages. Mais comme je l'ai déjà dit - j'en doute.";
			link.l1 = "Je vois...";
			link.l1.go = "exit";
			npchar.quest.natan = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Whiteboy":
			dialog.text = "Garçon blanc ? Hm... Non, je n'en ai pas entendu parler auparavant. Mais cela ne signifie pas qu'il n'est pas ici. Je n'ai pas besoin de connaître toute la racaille locale, n'êtes-vous pas d'accord ?";
			link.l1 = "Moi aussi. Bien, je demanderais à quelqu'un d'autre.";
			link.l1.go = "exit";
			npchar.quest.whiteboy = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "ships":
			dialog.text = "L'Île est divisée entre les Narvals, les Rivados et mes hommes. Il y a aussi une zone neutre. Je contrôle San Augustine et Tartarus\nLes Rivados tiennent le Protector, qui est leur résidence, Fury - casernes, Velasco - entrepôt. Les étrangers ne peuvent pas passer, il faut dire un mot de passe spécial pour y accéder\nLes Narvals possèdent beaucoup de navires. Esmeralda est la résidence de leur chef et un magasin. Ce qu'ils appellent le 'Centre scientifique San Gabriel' et une plateforme Phoenix. Enfin, la Ceres Smithy - leur atelier. Chaque navire à l'exception d'Esmeralda est une zone restreinte, vous devez dire un mot de passe avant qu'ils vous laissent entrer\nLes autres navires sont considérés comme neutres, les citoyens locaux y vivent. La taverne de Sancho est située dans la caravelle Fleron et le frère Julian est à la tête de l'église locale dans le galion Gloria.";
			link.l1 = "Merci pour l'information !";
			link.l1.go = "exit";
			npchar.quest.ships = "true";
			NextDiag.TempNode = "Total_wait";
			AddQuestRecord("LSC", "2");
		break;
		
		case "parol":
			dialog.text = "En fait, ils les donnent aux personnes qui les intéressent eux-mêmes. Hélas, tu n'en fais pas partie. Mais ce n'est guère un problème. Va sur une vieille frégate nommée Carolinea. C'est là qu'habite un gros chien rusé nommé Giuseppe Fazio. Il est une sorte de diplomate ici. Je ne sais pas ce qu'il faisait avant d'arriver ici, mais l'homme a du talent. Il fait des affaires avec tout le monde. Les clans l'utilisent comme médiateur. Cupide. Prêt à se manger lui-même pour un seul doublon, mais il ne le montre jamais. Demande-lui le mot de passe actuel, bien que cela te coûtera.";
			link.l1 = "Merci ! Je m'en souviendrai.";
			link.l1.go = "exit";
			npchar.quest.parol = "true";
			NextDiag.TempNode = "Total_wait";
			AddQuestRecord("LSC", "3");
		break;
		
		case "map":
			dialog.text = "Dexter en possède une. Il est mon second. Il a fait une carte détaillée juste après notre arrivée. Montez et parlez-lui si vous en avez besoin.";
			link.l1 = "Compris. Merci!";
			link.l1.go = "exit";
			npchar.quest.map = "true";
			NextDiag.TempNode = "Total_wait";
			sld = characterFromId("Dexter");
			sld.quest.map = "true";
		break;
		
		case "blade":
			dialog.text = "Ha ! Une belle épée large. Une lame unique en son genre... Un trophée de Alan Milrow, chef du clan des Narvals. C'est ainsi que je l'ai nommée. Jurgen, un armurier Narval, l'a fabriquée avec un métal incroyable qu'ils ont trouvé au fond de la mer. \nElle ne rouille pas, ne s'émousse jamais et tranche tout et tout le monde d'un coup. Je suis très satisfait de cette arme et je ne compte pas la laisser derrière moi.";
			link.l1 = "Je suis curieux, si Jurgen est capable de fabriquer une autre épée large comme celle-ci ? Pour une bonne somme, bien sûr...";
			link.l1.go = "blade_1";
		break;
		
		case "blade_1":
			dialog.text = "Eh bien, il peut en faire un autre, c'est sûr. Mais il ne le fera pas. Jurgen est Narval, il est loyal à son clan et il ne fera jamais rien pour les étrangers. De plus, tu auras besoin d'un fer très spécial pour fabriquer la deuxième épée. Ce fer ne se trouve qu'au fond - et comment quelqu'un pourrait-il y aller ? Alors oublie ça.";
			link.l1 = "Je vois. Dommage.";
			link.l1.go = "exit";
			npchar.quest.blade = "true";
			NextDiag.TempNode = "Total_wait";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				sld = characterFromId("Schmidt");
				sld.quest.narval_blade = "begin"; // возможность сделать 'Нарвал' для Мэри
			}
		break;
		// <-- информационный блок
		
		case "return":
			chrDisableReloadToLocation = true;//закрыть локацию
			dialog.text = "Ha, j'ai vu vos voiles à l'horizon, "+pchar.name+"Content de te voir, ami ! Comment s'est passé le voyage ?";
			link.l1 = "C'était bien.";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "Bien. Eh bien, je suis prêt à monter sur ton navire et voguer vers Jan Svenson. Layton restera ici en tant qu'amiral, il a déjà pris la chaise, ha-ha ! On dirait qu'il ne veut pas quitter l'Île, cet endroit lui plaît.";
			link.l1 = "Tu as dit une fois qu'il se débrouillait vraiment bien.";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "Oui, il l'est certainement. Eh bien, je suis prêt. Allons-y ?";
			link.l1 = "Monte sur mon navire, Steven. Nous lèverons l'ancre dès que j'aurai terminé mes affaires ici.";
			link.l1.go = "return_3";
		break;
		
		case "return_3":
			dialog.text = "Marché conclu ! Eh, ça fait trop longtemps que je n'ai pas senti le pont d'un bon navire sous mes pieds !";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LSC_SetDodsonPassenger", -1);
		break;
		
		case "return_5":
			dialog.text = "Nous y voilà, ami. Eh bien, je vais aller voir Svenson. Vous devriez aussi aller le voir et discuter de nos plans futurs. Ha-ha ! Des jours chauds nous attendent, hein ?";
			link.l1 = "Aucun doute. À bientôt, Steven !";
			link.l1.go = "return_6";
		break;
		
		case "return_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseS1", "none", "", "", "OpenTheDoors", -1);
			sld = ItemsFromID("LSC_navigation_map");
			sld.price = 1000; // лоцию можно выкладывать 270912
			sld = ItemsFromID("keys_skel");
			sld.price = 3000; // отмычки можно выкладывать 270912 
			pchar.questTemp.LSC.Dios = "true"; // можно отдать лоцию Диосу
			CloseQuestHeader("LSC"); // 280313
		break;
		
		// Тени прошлого
		case "shadows":
			dialog.text = "Bien sûr, je ferai ce que je peux ! Continuez.";
			link.l1 = "Steve, regarde... Une dent de requin. Ne me dis pas que cela t'est inconnu !";
			link.l1.go = "shadows_1";
		break;
		
		case "shadows_1":
			RemoveItems(pchar, "shark_teeth", 1);
			dialog.text = "Ha ! Tu es malin ! Oui, c'est ma dent. Eh bien, c'est la dent d'un requin que j'ai tué pour impressionner une beauté. Depuis, on m'appelle Requin. Peu ont réussi à faire cela sous l'eau avec un simple sabre, mais j'étais jeune et fougueux, et Béatrice Sharp était la plus belle fille des Caraïbes... Comment l'as-tu obtenue ?";
			link.l1 = "Le bourreau de St. John's me l'a donné. Un homme a été massacré avec. Son nom était... Joshua Leadbeater.";
			link.l1.go = "shadows_2";
		break;
		
		case "shadows_2":
			dialog.text = "Oui, je l'ai fait. Je lui ai tranché la gorge avec cette dent. J'étais horrifié par la mort de Béatrice et je croyais que Leadbeater était le seul responsable encore en vie. J'ai lu des papiers que j'ai trouvés sur lui plus tard. Eh bien, il avait tout à fait le droit à la vengeance\nLa sœur de Blaze était simplement au mauvais endroit au mauvais moment. Le Masque n'est pas à blâmer pour sa mort, il ne le voulait pas, seul le Boucher était sa cible. Je regrette de l'avoir tué. La vérité est que cette garce de Jessica a tout manigancé.";
			link.l1 = "As-tu sauvé ces papiers ?";
			link.l1.go = "shadows_3";
		break;
		
		case "shadows_3":
			dialog.text = "Pourquoi devrais-je ? Bien sûr que non. Je n'en avais pas besoin. Mais je peux te dire pourquoi Masque poursuivait Boucher, si tu as le temps.";
			link.l1 = "Je l'ai fait. Sachez que ce n'est pas par simple curiosité, je suis vraiment intéressé. Je suis même prêt à écrire votre histoire.";
			link.l1.go = "shadows_4";
		break;
		
		case "shadows_4":
			dialog.text = "Je sais, tu ne perds jamais ton temps. Écoute donc. Joshua Leadbeater était un capitaine ordinaire de la marine britannique et il commandait la frégate 'Neptune', qui est devenue une légende par la suite...";
			link.l1 = "I'm sorry, I need the specific text in English that you want me to translate into French.";
			link.l1.go = "shadows_5";
		break;
		
		case "shadows_5":
			DialogExit();
			SetLaunchFrameFormParam("One hour later...", "Saga_FinalLedbitterStory", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shadows_6":
			AddQuestRecordInfo("Mask", "1");
			dialog.text = "... Cependant, Leadbeater a survécu et a été sauvé par un navire de passage. Ses blessures ont rendu son visage hideux, et il portait un masque depuis lors. Trouver et punir le coupable de tous ses malheurs était devenu le sens de sa vie.";
			link.l1 = "Je vois... Je l'ai noté. Je pense que je devrais le lire pour voir ce que j'ai. C'est une histoire très triste. As-tu vu cette Jessica ?";
			link.l1.go = "shadows_7";
		break;
		
		case "shadows_7":
			dialog.text = "Bien sûr ! Elle accompagnait Boucher dans tous ses voyages jusqu'à ce qu'il la largue pour Béatrice. Jess ne pouvait pas lui pardonner cela. Ils l'appelaient le talisman de Boucher, car il avait toujours de la chance quand elle était là avec lui\nCroyez-le ou non, mais dès qu'il s'est débarrassé d'elle à la Barbade, ses affaires ont mal tourné, le butin est devenu maigre et le 'Neptune' est devenu un invité fréquent au chantier naval de l'Isla Tesoro. Bien que cela puisse s'expliquer par le fait que Boucher passait le plus clair de son temps avec Béatrice dans la cabine plutôt qu'à la dunette\nBéatrice n'était pas comme Jessica, elle n'était pas accro aux aventures et à la guerre, bien que Nicolas lui ait enseigné l'escrime et la navigation. Oui, elle aimait la romance marine mais elle n'avait pas assez de fermeté de caractère. Le 'Neptune' de Boucher n'était pas le bon endroit pour elle. À la fin, elle l'a tuée.";
			link.l1 = "Et qu'en est-il de Jessica ?";
			link.l1.go = "shadows_8";
		break;
		
		case "shadows_8":
			dialog.text = "Oh, elle était quelque chose. Chaque marin du 'Neptune' obéissait à ses ordres et pas seulement parce qu'elle était la petite amie du capitaine. Jess avait maîtrisé l'escrime et la navigation, les efforts de Butcher n'étaient pas vains. Elle était coriace et téméraire, et avait aussi un bon look. Beaucoup d'hommes voulaient coucher avec elle, mais elle ne voulait que Butcher, la déranger était vraiment risqué - beaucoup ont testé les résultats sur leur propre dos littéralement, et pour les plus persistants, ses leçons d'escrime se sont avérées être les dernières de leur vie. Jess possédait une épée très spéciale, la seule de son genre dans les Caraïbes, je n'ai aucune idée d'où elle l'avait obtenue. Une épée à lame flamboyante. Personne ne peut saisir sa lame et même le moindre contact laisse une terrible blessure. Jess était une aventurière non par naissance, mais par vocation. D'ailleurs, si vous avez besoin d'en savoir plus sur elle, vous pouvez parler à une de vos connaissances. Il peut vous en dire beaucoup plus que moi.";
			link.l1 = "Vraiment ? Et qui est cet homme ?";
			link.l1.go = "shadows_9";
		break;
		
		case "shadows_9":
			dialog.text = "Jan Svenson. Le Diable des Forêts ne l'admettra jamais, mais il avait des projets concernant Jessica. C'était à l'époque où il avait déjà pris le Main occidental pour lui-même et sa renommée était enviable, alors la tigresse était à sa hauteur\nAprès que le Boucher se soit débarrassé de Jess, Jan a commencé à visiter la Barbade de manière suspecte, ébranlant la garnison anglaise. Comme vous le savez, Jessica était la fille d'un planteur de Bridgetown\nEn fin de compte, ses plans étaient bien connus dans les cercles privés, mais personne n'osait en parler, Jan peut bien se reposer sur ses lauriers à Blueweld de nos jours, mais à l'époque, un mot de travers à son encontre pouvait mal tourner\nFinalement, cela n'a pas fonctionné pour eux. Jess ne pouvait pas vivre avec la façon dont le Boucher la traitait et elle s'est vengée un an plus tard avec l'aide du Masque. Cette vengeance s'est terminée terriblement pour tout le monde : pour le Boucher, pour Béatrice, pour le Masque et pour elle-même. Ils sont tous morts.";
			link.l1 = "Pas tous. Le Boucher est encore en vie.";
			link.l1.go = "shadows_10";
		break;
		
		case "shadows_10":
			dialog.text = "Quoi ? Ai-je mal entendu ? Il est vivant ?!";
			link.l1 = "Oui. Le capitaine Butcher n'a pas été exécuté. Eh bien, il aurait dû l'être, mais il a survécu grâce à Jacob Jackman et Henry le Bourreau, qui avaient intimidé le bourreau. L'exécution était une imposture. J'ai des preuves.";
			link.l1.go = "shadows_11";
		break;
		
		case "shadows_11":
			dialog.text = "Impossible ! Et où est-il maintenant ?";
			link.l1 = "Il est connu sous le nom de Lawrence Beltrope et il vit à Port Royal. Cependant, il reste dangereux. Jackman, qui a causé tant de problèmes parmi les Frères de la Côte, agissait sous ses ordres.";
			link.l1.go = "shadows_12";
		break;
		
		case "shadows_12":
			dialog.text = "Merde ! Le quartier-maître avait retrouvé son capitaine après tant de temps ! Beltrope, dis-tu... attends ! Maintenant, je comprends pourquoi il y avait un étrange rapport d'interrogatoire parmi les papiers de Blaze... On dirait que Blaze avait aussi découvert l'affaire Boucher-Beltrope...";
			link.l1 = "De quoi parles-tu ?";
			link.l1.go = "shadows_13";
		break;
		
		case "shadows_13":
			dialog.text = "Après avoir pris cette résidence, j'ai fouillé dans les papiers du vieux Blaze. J'ai trouvé un rapport d'interrogatoire de Samuel Brooks. Il y avait beaucoup de détails sur les aventures de Thomas Beltrope, et il est connu comme un pirate et un ami proche de Nicolas Sharp. Il semble qu'il était le père de Boucher.";
			link.l1 = "Intéressant. On dirait que les enfants de Sharp et de Beltrope ont continué le métier de leurs parents...";
			link.l1.go = "shadows_14";
		break;
		
		case "shadows_14":
			dialog.text = "Il semble que oui... Mais dis-moi, ami, pourquoi t'intéresses-tu tant aux actions des défunts ? Quelle est ta préoccupation ?";
			link.l1 = "J'ai besoin de papiers qui confirmeraient qu'Helen McArthur est la fille de Beatrice Sharp et qu'elle a tous les droits sur ce nom de famille. Je me fiche qu'elle soit aussi Beltrope.";
			link.l1.go = "shadows_15";
		break;
		
		case "shadows_15":
			dialog.text = "Il n'y a rien sur Helen McArthur ni dans les papiers de Leadbeater ni dans les archives de Blaze. Il est étrange que Béatrice n'ait pas informé Blaze de la naissance de sa nièce. Cela ne lui ressemble pas.";
			link.l1 = "Écoute, peut-être y a-t-il autre chose dans les papiers de Sharp ? J'ai besoin de chaque détail !";
			link.l1.go = "shadows_16";
		break;
		
		case "shadows_16":
			dialog.text = "Hm, je suppose. D'après les notes de Blaze, il essayait de trouver l'île où sa sœur est morte. Il y a des documents concernant l'expédition punitive de Leadbeater. Rien d'intéressant, à part quelques chiffres de latitude. \nCe parallèle traverse la mer des Caraïbes dans sa partie nord. Mais il n'y a aucun signe de longitude. De toute évidence, les recherches de Blaze ont échoué, vous ne pouvez même pas imaginer combien de petites îles se trouvent à cette latitude.";
			link.l1 = "Et qu'est-ce que c'est ?";
			link.l1.go = "shadows_17";
		break;
		
		case "shadows_17":
			dialog.text = "Voyons voir... ici : latitude 21 degrés 32' Nord. Je ne sais pas comment cela peut vous aider.";
			link.l1 = "Ce sera. Bien, Steven, merci beaucoup pour ton histoire honnête. À bientôt !";
			link.l1.go = "shadows_18";
		break;
		
		case "shadows_18":
			DialogExit();
			pchar.questTemp.Saga.Shadows = "jessika";
			AddQuestRecord("Shadows", "6");
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "First time";
			sld = characterFromId("Svenson");
			sld.quest.jessika = "true";
			// рифы доступны для посещения
			i = FindIsland("RockIsland");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			// для любителей самостоятельно добавлять локаторы
			LAi_LocationDisableOfficersGen("Shore67", true);//офицеров не пускать
			// и сразу прерывание
			pchar.quest.Saga_Jess_Island.win_condition.l1 = "location";
			pchar.quest.Saga_Jess_Island.win_condition.l1.location = "Shore67";
			pchar.quest.Saga_Jess_Island.function = "Saga_JessikaIsland"; 
			// активируем квест хронометра Алекса
			pchar.questTemp.AlexClock = "dodson"; // 280912
		break;
		
		// суп из черепахи
		case "terrapin":
			dialog.text = "On pourrait dire ça. Maintenant, parlons de Tortuga\nL'île a été nommée ainsi parce qu'elle ressemble presque à une tortue. Levasseur épaississait la carapace de la tortue depuis douze ans - le fort La Roche. Une attaque frontale est suicidaire, les lourds canons du fort ne laisseront aucune chance. Donc, cuisiner une soupe de cette beauté ne sera pas facile. Les Espagnols ont essayé pendant très longtemps et n'ont jamais réussi.";
			link.l1 = "C'est pourquoi je suis allé voir Svenson. Alors, quel est ton plan ? Allez, Steven !";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "Mes hommes avaient fait du bon travail à Tortuga ces dernières semaines, et ils ont obtenu beaucoup d'informations intéressantes. J'ai donc une bonne nouvelle pour toi, camarade ! Il semble que tu n'aies pas besoin de te préoccuper des canons de La Roche, car nous ne sommes pas les seuls à en avoir assez de Levasseur. Il y a des gens parmi ses amis qui veulent aussi sa mort.";
			link.l1 = "Continue...";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "Il est connu que Levasseur a un faible pour les jeunes filles colons. Elles disparaissent après qu'il ait fini de s'amuser avec elles. Le principal fournisseur d'esclaves de Tortuga s'appelle Robert Marten du galion Voltigeur\nSon complice, le neveu de Levasseur, Henri Thibaut, choisit les plus jolies filles blanches directement au port pour son patron. Ainsi, il n'y a pas longtemps, Marten a mis la main sur une très belle fille d'un brigantin anglais. Elle s'appelle Molly Jones. Il ne l'a pas livrée à Levasseur, mais à son neveu, de nuit dans une grotte secrète à Tortuga\nL'équipage a été informé que la fille était morte d'une crise cardiaque et que son 'corps' avait été jeté par-dessus bord. On dirait que nos amis ont décidé de garder cette jolie créature pour eux. Si Levasseur apprend l'existence de Molly, ces deux-là auront des problèmes.";
			link.l1 = "Et comment pouvons-nous faire confiance à cette information ? Il est évident qu'ils comprennent tous deux qu'ils jouent avec le feu...";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			dialog.text = "Vrai. Mais chaque chaîne a un point faible. Et j'en ai trouvé un pour toi. Il y a trois jours, un ancien marin du 'Voltigeur' nommé Fernand Lucas a trop bu et a raconté beaucoup de choses intéressantes dans la taverne de Basse-Terre\nIl s'est avéré que Molly Jones lui avait demandé de demander de l'aide à son frère à St John's. Mais Lucas n'a jamais atteint son but, il a échappé à son capitaine et il reste le cul assis en Guadeloupe à noyer sa lâcheté dans le rhum\nAntigua n'est pas un endroit sûr pour les pirates français. Souviens-toi de ça ! Le colonel Fox est prêt à les pendre à chaque palmier de l'île après que sa femme ait été tuée par un corsaire français. Et ses redoutables marins feront tout ce que leur commandant ordonne.";
			link.l1 = "Je ne comprends pas encore comment cela est lié à notre affaire... Parlons de nos gars, Marten et Thibaut. Quel est le but d'un tel risque? Le charme de la femme était-il si fort ou ces esclavagistes ont-ils fait preuve de clémence?";
			link.l1.go = "terrapin_4";
		break;
		
		case "terrapin_4":
			dialog.text = "Je connais bien cette crapule de Marten. Si il prend des risques, cela signifie qu'il y a soit de l'or en jeu, soit la peur pour sa peau. Je ne sais pas ce que notre prisonnière a à voir avec ça\nPeut-être que Robert espère obtenir une énorme rançon pour elle, ce qui est peu probable, la fille ressemblait à une servante. Ou peut-être... Ha ! Je me demande qui pourrait être plus effrayant pour Marten que Levasseur !";
			link.l1 = "Et pourquoi pensez-vous que Mademoiselle Jones est toujours cachée du gouverneur ? Peut-être qu'ils ont obtenu ce qu'ils voulaient d'elle et l'ont livrée à Levasseur ? Oui, avez-vous quelque chose de précis à dire sur ce Thibaut ?";
			link.l1.go = "terrapin_5";
		break;
		
		case "terrapin_5":
			dialog.text = "Je ne connais pas grand-chose sur cet homme. Je sais seulement que l'oncle fait assez confiance à ce chiot pour en faire son héritier. Il a toujours une fille, sinon pourquoi auraient-ils besoin de toute cette conspiration? \nIl n'est pas clair où la fille est retenue ni pourquoi Thibaut permet à Marten de prendre les devants. Il y a un mystère qui peut nous aider à gagner cette partie sans prendre d'assaut Tortuga. Vous êtes français, alors je suppose que vous préféreriez cela ainsi. \nMais vous devriez vous dépêcher, les discours ivres de Lucas pourraient être entendus par les agents de Marten et Levasseur, vous pouvez imaginer les conséquences!";
			link.l1 = "Je comprends. Alors, Thibaut est l'héritier de Levasseur? Et il cache une esclave à son oncle? Nom d'un chien, je suppose que le jeune homme est pressé de voir son oncle mort au plus vite!";
			link.l1.go = "terrapin_6";
		break;
		
		case "terrapin_6":
			dialog.text = "Vrai. Selon les dires de Lucas, cette Molly est une rare beauté, notre brave Thibaut pourrait bien tomber amoureux d'elle. Tu sais ce que les gens peuvent faire par amour. Va à Basse-Terre\nTrouve cet idiot ivre et fais-le parler. De plus, tu devrais aussi apprendre tout ce que tu peux sur Molly et son frère. Tu pourrais vouloir visiter Antigua d'abord, Molly y avait envoyé Lucas dans un but précis. Mais quel est ce but ?";
			link.l1 = "Je vois. Ne perdons pas de temps. Merci, Steven.";
			link.l1.go = "terrapin_7";
		break;
		
		case "terrapin_7":
			DialogExit();
			AddMapQuestMarkCity("SentJons", true);
			AddMapQuestMarkCity("BasTer", true);
			AddQuestRecord("Terrapin", "1");
			pchar.questTemp.Terrapin = "baster";
			pchar.questTemp.Terrapin.SJ_count = 0;
			// прячем Фокса
			sld = characterFromId("Fox");	
			ChangeCharacterAddressGroup(sld, "none", "", "");
			// садим в таверну Робера Мартэна
			float fMft = MOD_SKILL_ENEMY_RATE/10;
			sld = GetCharacter(NPC_GenerateCharacter("Rober", "Marten", "man", "man", 30, FRANCE, -1, true, "quest"));
			FantomMakeCoolSailor(sld, SHIP_GALEON_L, "Voltigeur", CANNON_TYPE_CANNON_LBS20, 90, 90, 90);
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_19", "pistol5", "bullet", 150);
			sld.name = "Rober";
			sld.lastname = "Marten";
			sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
			sld.dialog.currentnode = "Rober";
			sld.greeting = "pirat_common";
			TakeNItems(sld, "potion2", 1);
			TakeNItems(sld, "potion3", 2);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "BladeDancer");
		
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "LongRangeGrappling");
			SetCharacterPerk(sld, "GrapplingProfessional");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "CriticalShoot");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "BasicBattleState");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "Doctor1");
			SetCharacterPerk(sld, "Doctor2");
			sld.MultiFighter = 1.0+fMft; // мультифайтер
			LAi_SetSitType(sld);
			UpgradeShipParameter(sld, "SpeedRate");//апгрейдить скорость
			UpgradeShipParameter(sld, "TurnRate");//манёвренность
			FreeSitLocator("Baster_tavern", "sit1");
			ChangeCharacterAddressGroup(sld, "Baster_tavern", "sit", "sit1");
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Terrapin_LateBaster", 0, 0, 20, false); // таймер
			}
			else SetFunctionTimerCondition("Terrapin_LateBaster", 0, 0, 10, false); // таймер
			
			// Квест "Погасшая Звезда" провалена, всё удаляем
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway"))
			{
				CloseQuestHeader("PZ");
				DeleteAttribute(pchar, "questTemp.PZ_Etap5_Start");
				DeleteAttribute(pchar, "questTemp.PZ_Etap4_Start");
				DeleteQuestCondition("PZ_Etap5_Start");
				DeleteQuestCondition("PZ_LongwayCapstervilleDialog");
				DeleteQuestCondition("PZ_OhotaNaZvezdu_Kapstervil");
				DeleteQuestCondition("PZ_OhotaNaZvezdu_Yamaika");
				DeleteQuestCondition("PZ_Beliz_PoterpKrushenie");
				pchar.questTemp.PZ_ProvalFinal = true;
			}
		break;
		
		case "terrapin_8":
			dialog.text = "Continue !";
			link.l1 = "J'ai trouvé le frère de Molly à Saint-Jean. C'est l'ordonnance de Fox. Mais il y a quelque chose d'étrange. Sa sœur Molly est une vieille sorcière bien connue, aussi grande que toi. Elle est la servante de la fille de Fox, Catherine, et elle était en Angleterre avec elle jusqu'à récemment...";
			link.l1.go = "terrapin_9";
		break;
		
		case "terrapin_9":
			dialog.text = "Bonjour, mon ami.";
			link.l1 = "Quant à Catherine, elle est en effet connue pour sa beauté et elle allait rendre visite à son père pour son anniversaire, mais elle a été retardée à cause du retard de l'escadron à Londres...";
			link.l1.go = "terrapin_10";
		break;
		
		case "terrapin_10":
			dialog.text = "Bonjour, mon ami.";
			link.l1 = "Son père, qui a très mal pris la mort de sa femme lors de l'attaque du corsaire français, lui a strictement interdit de quitter l'Angleterre à bord d'un navire solitaire. Donc, Molly Jones ne peut pas être la prisonnière de Thibaut. Alors, qui est-elle ?";
			link.l1.go = "terrapin_11";
		break;
		
		case "terrapin_11":
			dialog.text = "Hm... Diable si je sais. Peut-être qu'elle est une autre Molly Jones, pas celle dont vous parlez. Pourtant... il y a trop de coïncidences. Je ne crois pas que ce soit juste un hasard ! J'ai quelques soupçons flous mais... bien des choses étranges peuvent arriver !";
			link.l1 = "Que veux-tu dire? Dis-moi!";
			link.l1.go = "terrapin_12";
		break;
		
		case "terrapin_12":
			dialog.text = "Et que se passerait-il si la fille désobéissait aux ordres de son père et mettait les voiles sans escorte ? Le mois dernier a été assez orageux, l'Albatross pourrait avoir été endommagé et devenir une proie facile pour Marten. Je soupçonne que Catherine n'a pas donné son vrai nom, vous devriez comprendre pourquoi, et elle est retenue à Tortuga sous le nom de Molly\nVous savez ce qui l'attend si son vrai nom est compromis. Cela commence à avoir du sens !";
			link.l1 = "Merde ! Je n'y aurais jamais pensé ! Molly... Catherine... Mais tout coïncide !";
			link.l1.go = "terrapin_13";
		break;
		
		case "terrapin_13":
			dialog.text = "C'est de cela que je parle, mon ami. Pas sûr que nous ayons raison, mais...";
			link.l1 = "Mais cela change tout ! Peut-être devrions-nous demander le soutien des Anglais ? Laisser les baïonnettes des marines nous ouvrir la voie !";
			link.l1.go = "terrapin_14";
		break;
		
		case "terrapin_14":
			dialog.text = "Calme-toi, "+pchar.name+"! Nous avons besoin de preuves plus solides. Nous ne pouvons pas en être certains. La vraie Catherine pourrait être à Londres, attendant qu'une escadre prenne la mer. Les Britanniques ont leurs propres problèmes, ils ne risqueront pas d'attaquer La Roche. Mais si nos soupçons sont vrais et que le colonel Fox découvre ce qui est arrivé à sa fille...\n Il établira un blocus autour de l'île et attendra l'arrivée de l'escadre. Puis il attaquera la ville. Les renards de mer sont une force redoutable dans les combats rapprochés. Je suis sûr qu'il lèvera le drapeau anglais au-dessus des ruines de Tortuga en trois jours. Veux-tu vraiment cela ?";
			link.l1 = "Non, ce n'est pas notre manière. Maintenant je vois de quelle rançon Marten parle.";
			link.l1.go = "terrapin_15";
		break;
		
		case "terrapin_15":
			dialog.text = "Nous devons agir prudemment. Nous ne sommes même pas sûrs que Marten soit au courant de la véritable identité de la vraie Molly. Faire chanter le colonel Fox serait une idée suicidaire. Surtout quand l'escadre de Cromwell arrive bientôt. \nSi Catherine meurt, nous perdrons aussi. Notre Confrérie n'est pas intéressée à rendre le colonel Fox plus en colère que d'habitude. Cet homme peut causer beaucoup de problèmes. Si Catherine doit mourir après tout, nous devons nous assurer qu'elle ne meure pas de notre main et seulement après avoir joué son rôle dans notre jeu. \nMais il serait bien mieux de livrer la pauvre fille à son père. Son sauveur sera récompensé. Sinon dans ce monde, alors dans l'autre.";
			link.l1 = "Par la volonté de Dieu... Steven, tu es un génie ! Je vais à Tortuga immédiatement ! Je découvrirai qui est cette Molly Jones ! Je suis foutrement sûr qu'elle est Catie Fox !";
			link.l1.go = "terrapin_16";
		break;
		
		case "terrapin_16":
			dialog.text = "Peut-être... Ne perds pas de temps, "+pchar.name+"Et si j'avais raison - assure-toi qu'elle reste en vie.";
			link.l1 = "Je ferai ce que je peux. À bientôt !";
			link.l1.go = "terrapin_17";
		break;
		
		case "terrapin_17":
			DialogExit();
			AddQuestRecord("Terrapin", "7");
			pchar.questTemp.Terrapin = "tortuga1";
			pchar.questTemp.Terrapin.Room_close = "true": // не пускать в комнату таверны
		break;
		
		case "guardoftruth":
			dialog.text = "Ho-Ho ! Crache le morceau, ami ! Nous résoudrons n'importe quel problème, c'est certain !";
			link.l1 = "Je vais aller droit au but, alors. Connaissez-vous Miguel Dichoso ?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Je le connais. Ce don espagnol m'a vendu un grand navire - une frégate. Eh, quel vaisseau c'était, imaginez un peu...";
			link.l1 = "Laisse-moi deviner, une coque unique, seize nœuds de vitesse maximale ? 'Santa Quiteria' ?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Tu as raison à propos de sa coque et de sa vitesse, mais le nom était différent - 'San Martin'. Je lui ai payé une somme énorme en or, c'était tout ce que j'avais. Toutes mes économies sont allées directement dans les poches de ce bandit.";
			link.l1 = "Es-tu sûr que son nom était San Martin et pas Santa Quiteria? Et quand l'as-tu acheté? Et pourquoi l'appelles-tu un fripon?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Que de questions ! Je vais y répondre toutes dans l'ordre : Je suis sûr que c'était San Martin. J'ai personnellement aidé les ouvriers d'Alexus à se débarrasser d'une planche portant ce nom papiste de la poupe. Je l'ai nommée 'Fortune' - un nom beaucoup plus approprié pour une telle princesse. Je l'ai achetée peu avant que Blaze Sharp ne soit assassiné en hiver 1654. Pourquoi ai-je appelé Miguel ainsi ? Parce que ce fils de pute a réussi à voler le navire de la base militaire espagnole de Providence. Nous leur avions organisé tout un spectacle, juste devant le fort de San Juan. J'ai sacrifié deux lougres à moitié morts pour rendre le combat plus crédible. Nous avons brûlé et coulé les navires, simulant la bataille avec la frégate. Et lorsque la nuit est tombée, nous avons conduit le San Martin à Isla Tesoro. J'ai eu le navire et Dichoso a eu l'argent. Il a dit à son haut commandement que la frégate avait été coulée dans une bataille avec des pirates, le commandant de San Juan l'a vérifié.";
			link.l1 = "Alors c'est ainsi que les dons espagnols remplissent leurs poches ! Quel scélérat ! Dis-moi, cela s'est-il vraiment passé en hiver 1654 ? Peut-être au printemps ? Et la frégate a-t-elle été endommagée par les tempêtes ?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "En hiver... Bon sang, je ne suis pas totalement sûr - ça pourrait être au printemps aussi. Je ne me souviens vraiment pas. La frégate n'était pas endommagée, elle était toute neuve. Elle avait l'air d'être fraîchement construite. Quand j'y pense, j'ai juste envie de pleurer de dépit...";
			link.l1 = "Pourquoi ? Oui, et où est ta belle frégate maintenant ?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Parce qu'elle est partie, loin de moi. Ils m'ont piégé, ont mis mon talisman sur le cadavre de Blaze et ont répandu la rumeur que j'étais le meurtrier. Puis j'ai entendu que Marcus Tyrex - notre gardien du code - allait me donner une marque noire. Alors j'ai décidé de m'échapper de ce bourbier pour un temps à L'Île Justice, où tu m'as trouvé.\nJe ne pouvais pas m'y rendre sur une frégate, alors je l'ai engagée au Pasteur Noir en échange d'une brigantine remplie de provisions, je n'avais pas beaucoup de pièces après mon accord avec ce rusé Dichoso. J'espérais vendre les provisions et retourner à Isla Tesoro dans un mois ou deux... Eh bien, tu connais le reste.";
			link.l1 = "Et le Pasteur Noir ne t'a pas attendu, alors il l'a vendue";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Précisément. Elle a été achetée par un Anglais, ou pour être plus précis, par un Écossais, William Paterson. Je pourrais essayer de récupérer la fille, bien sûr, mais ce montagnard est un oiseau sérieux, un capitaine de la Royal Navy, un bon ami du colonel Fox. En plus, il faisait des affaires avec Jackman de la même manière que vous avec Svenson\nL'Écossais a une escadre... au diable, je ne reverrai plus mon navire.";
			link.l1 = "Je vois. Ne sais-tu pas où se trouve ce Dichoso maintenant ?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Je n'en ai aucune idée. Je ne l'ai jamais vu après avoir acheté ma Fortune.";
			link.l1 = "Et pourquoi Miguel n'a-t-il pas proposé de le vendre à quelqu'un d'autre ? Que diriez-vous de Tyrex, Barbazon, Sharp ? Ou Paterson ?";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Je n'en ai aucune idée. Paterson n'était pas là cette fois-là, autant que je m'en souvienne. Zachariah, Jacques et Marcus n'auraient jamais été d'accord et moi... J'aimais vraiment la frégate !";
			link.l1 = "Je comprends que... je ne comprends rien. Des énigmes partout...";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Plonge encore dans le passé ? Quelle île veux-tu prendre cette fois ? Ha-ha-ha !";
			link.l1 = "Il y a une île... Bien que je ne puisse pas encore y trouver un chemin. Très bien, Steven, merci pour ton information ! Adieu !";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Bonne chance, "+pchar.name+"!";
			link.l1 = "... ";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			DialogExit();
			AddQuestRecord("Guardoftruth", "60");
			pchar.questTemp.Guardoftruth.Archy = "guadeloupe";
			// маленькая развлекуха
			pchar.quest.GuardOT_cabinattack.win_condition.l1 = "EnterToSea";
			pchar.quest.GuardOT_cabinattack.function = "GuardOT_PrepareCreateBandosInCabin";
		break;
		
		case "tieyasal":
			dialog.text = "Et je suis heureux de vous aider, comme toujours. Que voulez-vous cette fois, "+pchar.name+"?";
			link.l1 = "C'est encore à propos de ton vieil ami Miguel Dichoso. Je sais qu'il a été vu sur l'Île au Trésor à nouveau. Ne peux-tu pas m'aider à le trouver ?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Ho, ami, je ne savais pas cela, en fait. Je ne l'ai pas vu ici. Je ne l'ai pas vu depuis que j'ai acheté 'Fortune' de lui. Et pourquoi as-tu besoin de ce don espagnol ?";
			link.l1 = "J'ai besoin de lui. Miguel connaît le chemin vers une ancienne cité indienne. J'ai vraiment hâte d'y arriver.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Hélas, comme toujours, mon ami, tu vas te fourrer dans le pétrin. Hélas, je ne peux pas t'aider. Je te conseille de te promener dans la colonie et de demander aux gens, peut-être que quelqu'un l'a vu. C'est un homme célèbre ici, tu sais.";
			link.l1 = "Eh bien, Steven, peux-tu au moins me dire à quoi il ressemble ?";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "Eh bien, il a vingt-cinq - vingt-huit ans, à peu près de votre taille, des yeux sombres, pas de perruque. Il a une cicatrice de sabre sur la joue droite.";
			link.l1 = "Hm. Vous savez, il y a beaucoup de personnes qui correspondraient à cette description.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "Il n'y a pas d'autres détails uniques à son sujet. Il est sûr de lui, insolent et très dangereux. Il y avait des ragots à son sujet...";
			link.l1 = "Je vois. Très bien, je vais me renseigner à son sujet. Bonne chance, Steven !";
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			DialogExit();
			AddQuestRecord("Tieyasal", "2");
			npchar.quest.tieyasal = "true";
		break;
		
		// Jason НСО
		case "patria":
			dialog.text = "Ho-ho ! Tu es tombé au bon endroit ! Crache le morceau !";
			link.l1 = "Il y a un type qui n'a pas peur des pirates. Il ne les prend pas au sérieux. Il a besoin qu'on lui donne une leçon de respect. Souviens-toi, ne le tue pas.";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "Tiens donc ! Mais c'est le vieux Charles ! Je parie que tu t'es encore fourré dans une affaire ! Passons aux détails, qui est la cible cette fois-ci et qu'allons-nous lui apprendre ?";
			link.l1 = "Un invité d'Europe, un inspecteur du ministère des Finances français - le baron Noel Forget. Il veut établir ici une Compagnie Française de Commerce, mais moi et un proche ami nous y opposons. Nous avons essayé de convaincre le baron que le commerce ici serait très risqué à cause des Hollandais, des Anglais et surtout des pirates depuis que Levasseur a été vaincu, mais il n'a pas écouté. Nous devons lui faire peur, pour qu'il le ressente dans sa propre chair.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			dialog.text = "Oui-oui... Un véritable baron !.. Allons-nous attaquer son navire ?";
			link.l1 = "Voici le plan : son navire partira bientôt de Port-au-Prince pour Capsterville. Tu dois intercepter le Baron après son départ et le prendre en otage. Il vaudrait mieux ne pas couler le navire et éviter de tuer l'équipage. Les Français sont nos amis, après tout. Pourras-tu gérer ça ?";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			dialog.text = "Eh bien, je ne peux rien promettre. Mais je vais essayer. Quel est le navire?";
			link.l1 = "Une brigantine appelée 'Favory'.";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "Une brigantine ne fait pas le poids face à ma frégate. Nous les gérerons facilement. Si elle se rend, je laisserai tout le monde en vie.";
			link.l1 = "Parfait. Inspirez la crainte et proposez-leur de capituler. Ensuite, envoyez le Baron dans la cale infestée de rats. Essayez de trouver l'endroit le plus immonde possible, mais ne l'y gardez pas plus d'un jour, sinon il pourrait tomber malade et mourir. Puis installez-le dans la cabine, allez à l'Isla Tesoro, et enfermez-le dans un endroit isolé. Habillez certains de vos hommes en marchands français capturés et faites-les agir comme tels. Pendant trois jours d'affilée, ils devront lui raconter tout sur la façon dont les pirates impitoyables les pourchassent, les volent, exigent des rançons, les torturent... avec tous les détails nécessaires.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "Ah-ah-ah ! Voilà bien le boulot le plus comique que j'aie accepté depuis fort longtemps ! Eh bien, je trouverai de tels acteurs, mon ami. N'aie aucun doute, après leurs récits, ton baron se fera dessus ! Ils lui montreront des cicatrices de coutelas et de baguettes chauffées... ";
			link.l1 = "Bien joué. Ensuite, tu le forceras à écrire une lettre à Poincy, demandant une rançon. Trois cent cinquante mille pour un si gros bonnet, ce n'est pas tant que ça.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			dialog.text = "Bien. Que ferons-nous ensuite?";
			link.l1 = "Et puis tu amèneras le Baron aux Turcs. Là, tu prendras la rançon, et tu me donneras le Baron. Et en plus, tu devrais mentionner que tous les Français répondront pour la Tortue et Levasseur.";
			link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			dialog.text = "Ha-ha-ha ! C'est un sacré tour ! Nous, personnellement, eh bien, tu sais ce qu'on a fait à Levasseur, et maintenant... ha-ha-ha !.. D'accord, l'ami. Ce sera fait ! Tu dis que le navire arrivera bientôt ?";
			link.l1 = "Bientôt. Nous devons rester en alerte.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_8":
			dialog.text = "Ne t'inquiète pas, je ne te laisserai pas tomber. Je m'occuperai de cela personnellement. Quand tu entendras la rumeur que ce baron a été capturé, viens me voir.";
			link.l1 = "Bien. Mes remerciements, Steven.";
			link.l1.go = "patria_9";
		break;
		
		case "patria_9":
			DialogExit();
			AddQuestRecord("Patria", "70");
			pchar.questTemp.Patria = "epizode_12_wait";
			pchar.questTemp.Patria.Condotier.Success = "true";
			LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
		break;
		
		case "patria_10":
			dialog.text = "Bien sûr, mon pote. Comme convenu. Des contes effrayants sur des pirates maléfiques, massacrant des marchands français innocents, les sons d'un fouet, des gémissements et des cris. Brasier avec charbon et menottes brûlées. Comme il se doit.";
			link.l1 = "Eh bien maintenant ! Retenez vos chevaux. J'ai besoin de lui vivant.";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "Ne t'inquiète pas, il restera en vie. Il a écrit cette lettre d'une main tremblante. La voici.";
			link.l1 = "Qu'est-ce qui est écrit là? Implore-t-il Poincy de le sortir de ce pétrin?";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "Pile dessus, l'ami ! Il supplie !";
			link.l1 = "Jette cette lettre, ou mieux - brûle-la. Nous nous retrouverons à Turks dans une semaine. Il doit sembler que nous avons besoin de temps pour rassembler la rançon.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			dialog.text = "Compris. Dans une semaine, golfe du Nord. N'oublie pas de prendre l'argent : ça doit avoir l'air joli. Ensuite, viens me voir, on réglera ça.";
			link.l1 = "Bien sûr, même un oursin l'aurait compris. À plus tard ! ";
			link.l1.go = "patria_14";
		break;
		
		case "patria_14":
			DialogExit();
			AddQuestRecord("Patria", "73");
			pchar.questTemp.Patria = "epizode_12_terks";
			SetFunctionTimerCondition("Patria_CondotierTerks", 0, 0, 7, false);
			SetFunctionTimerCondition("Patria_CondotierTerksOver", 0, 0, 14, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		case "patria_15":
			pchar.quest.Patria_CondotierTerksOver.over = "yes"; //снять таймер
			dialog.text = "Hé, mangeur de grenouilles ! Halte !";
			link.l1 = "Je ne bouge pas.";
			link.l1.go = "patria_16";
		break;
		
		case "patria_16":
			dialog.text = "Voici votre baron. Un peu usé, mais entier. Est-ce lui ?";
			link.l1 = "Oui.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "Parfait. Maintenant, remets l'argent ou il est fini ! Et n'essaie pas de nous tromper, nous t'avons dans le collimateur !";
			if (sti(pchar.money) >= 350000)
			{
				link.l1 = "Ici.";
				link.l1.go = "patria_18";
			}
			else
			{
				link.l1 = "Merde ! Je l'ai oublié sur le navire...";
				link.l1.go = "patria_22";
			}
		break;
		
		case "patria_18":
			AddMoneyToCharacter(pchar, -350000);
			dialog.text = "Ha-ha-ha ! T'es un gamin malin, frenchie. Prends ta sainteté. Et dis à Poincy qu'il devrait préparer l'argent : tous les bâtards français devront payer pour ce que vous avez fait à Levasseur et Tortuga. Et vos commerçants nous paieront avec leurs marchandises et navires. Ha-ha-ha ! N'oublie pas de nous amener d'autres barons dans l'archipel, ils nous rapportent beaucoup de profit ! Ha-ha-ha !";
			link.l1 = "Veuillez aller à mon bateau, Baron.";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			sld = CharacterFromID("Noel");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			dialog.text = "Et ne songe même pas à nous poursuivre, capitaine. Tu sais qui je suis. Je détiens plus de mangeurs de grenouilles captifs, et si je ne rentre pas chez moi à temps, mes hommes les tueront tous. Compris ?";
			link.l1 = "Le moment viendra où nous nous occuperons de vous, maudits blasphémateurs !";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "Ha-ha-ha-ha !";
			link.l1 = "... ";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Patria", "74");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_baronalive";
			pchar.questTemp.Patria.DodsonAgain = "true";
			Island_SetReloadEnableGlobal("Bermudes", false); // закрыть остров до отвоза барона
			sld = CharacterFromID("Noel");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Condotier_toPuancie.function = "Patria_CondotierEnCapstervil";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_22":
			dialog.text = "Te moques-tu de moi ?";
			link.l1 = "Une minute, je vais l'apporter...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "Patria_CondotierBaronDie", 1.0);
		break;
		
		case "patria_24":
			dialog.text = "";
			link.l1 = "Argh, Steven, qu'a fait ton imbécile !";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25":
			dialog.text = "Charles, que faisiez-vous ? Où est l'argent ? Je n'ai pas dit à mes garçons que ce n'était pas réel... et donc cet imbécile a décidé que vous vouliez les tromper...";
			link.l1 = "Quel dommage ! Le Baron est mort... Que fera Poincy maintenant ?";
			link.l1.go = "patria_26";
		break;
		
		case "patria_26":
			dialog.text = "Eh bien, mon gars, c'est de ta faute, j'espère que tu comprends cela. Peut-être que ce sera mieux pour toi.";
			link.l1 = "Quel idiot je suis ! J'ai tout gâché. Bien, j'irai à Poincy... Pardonne-moi d'être un imbécile, Steven, à bientôt.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "Tu as besoin de repos, tu perds la main. Passe me voir un de ces jours, je te trouverai du rhum et de belles demoiselles.";
			link.l1 = "Merci, je te rendrai visite quand je le pourrai.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			DialogExit();
			AddQuestRecord("Patria", "75");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_barondie";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_29":
			dialog.text = "Je t'en prie, mon pote. Pour moi, c'était le plus amusant que j'aie eu cette année ! On a tellement ri, moi et mes gars !.. Donc j'aimerais te remercier pour ça. Voici ton argent.";
			link.l1 = "Tu devrais garder une part pour toi.";
			link.l1.go = "patria_30";
		break;
		
		case "patria_30":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Laisse tomber. J'ai fait cela par amitié. La Confrérie de la Côte te doit bien plus, et pourtant tu n'as pas demandé un seul doublon.";
			link.l1 = "Prenez tout de même au moins cinquante mille pour les services et la compensation. Merci, Steven ! Je suis heureux de t'avoir rencontré autrefois sur cette étrange L'Île Justice des navires perdus.";
			link.l1.go = "patria_31";
		break;
		
		case "patria_31":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "Et moi aussi. Charles, rends-moi visite dès que tu as un peu de temps !";
			link.l1 = "Avec plaisir !";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
		break;
		
		case "patria_33":
			dialog.text = "Tu es en retard d'une semaine ! Je n'ai pas dit à mes gars que ce n'était pas réel... ! Ils ont refusé d'attendre plus longtemps et ont décidé d'en finir avec ton baron !";
			link.l1 = "Quel idiot je suis ! J'ai tout gâché ! Que vais-je dire à Poincy ?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_34":
			dialog.text = "Eh bien, l'ami, c'est ta faute, j'espère que tu comprends cela. Peut-être que ce sera tout de même mieux pour toi.";
			link.l1 = "Bien, j'irai à Poincy... Pardonne-moi d'être un imbécile, Steven, à bientôt..";
			link.l1.go = "patria_35";
		break;
		
		case "patria_35":
			dialog.text = "Tu as besoin de repos, tu perds ton coup de main. Viens me voir un de ces jours, je te trouverai du rhum et de belles demoiselles.";
			link.l1 = "Merci, je vous rendrai visite quand je le pourrai.";
			link.l1.go = "patria_36";
		break;
		
		case "patria_36":
			DialogExit();
			AddQuestRecord("Patria", "75");
			pchar.questTemp.Patria = "epizode_12_barondie";
			DeleteAttribute(pchar, "questTemp.Patria.DodsonFail");
		break;
		// belamour legendary edition хвастаемся Фортуной
		case "check_out_my_frigate":
			dialog.text = "Intéressant, intrigué. Eh bien, allons-nous promener.";
			link.l1 = "... ";
			link.l1.go = "check_out_my_frigate_01";
		break;
		
		case "check_out_my_frigate_01":
			DialogExit();
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			DoQuestReloadToLocation("pirates_town", "reload", "reload3_back", "SharkFrigateToTown");
			pchar.questTemp.SharkFrigate = true;
		break;
		
		case "check_out_my_frigate_02":
			dialog.text = "Sacré nom d'un chien! Je n'en crois pas mes yeux! Est-ce vraiment elle? Dites-moi, est-ce elle? Est-ce la 'Fortune'?!";
			link.l1 = "Oui, mon ami, tes yeux ne te trompent pas. C'est elle. Elle t'a manqué ?";
			link.l1.go = "check_out_my_frigate_03";
		break;
		
		case "check_out_my_frigate_03":
			dialog.text = "Ha ha ha, je n'en reviens pas ! Mille diables ! Mais où as-tu trouvé ça ?";
			link.l1 = "D'un certain Écossais nommé William Paterson. Oui, oui, de celui qui l'a acheté au Pasteur Noir.";
			link.l1.go = "check_out_my_frigate_04";
		break;
		
		case "check_out_my_frigate_04":
			dialog.text = "Sacrebleu... Et quoi, il vous a vendu 'Fortune'? Un si beau navire? Après que vous l'ayez acheté?";
			link.l1 = "Héhé, eh bien, presque. Disons-le ainsi : nous ne nous entendions pas très bien, et j'ai pris le navire en compensation des frais que j'ai engagés à cause de notre conflit. De toute façon, il n'a pas besoin d'un navire.";
			link.l1.go = "check_out_my_frigate_05";
		break;
		
		case "check_out_my_frigate_05":
			dialog.text = "Tu me surprends encore plus ... C'est un capitaine militaire au service de l'Angleterre. Son escadre de la colonie peut piller à volonté. Même moi, je n'ai pas pris le risque de me casser les dents sur lui. Et comment as-tu vérifié ça ? As-tu réussi à arracher la 'Fortune' de l'escadre ?";
			link.l1 = "Non, l'escadron a coulé. En fait, ce n'était pas facile. La bataille était sérieuse, mais elle s'est déroulée loin des lieux habités, et seuls mes marins et officiers étaient parmi les témoins. En général, je n'ai pas peur de la persécution par les autorités britanniques. William Paterson a simplement disparu lors d'une aventure ordinaire...";
			link.l1.go = "check_out_my_frigate_06";
		break;
		
		case "check_out_my_frigate_06":
			dialog.text = "Waouh... J'avais depuis longtemps perdu l'espoir de revoir mon hirondelle. Eh bien, j'espère que ce navire te servira fidèlement. Vraiment content pour toi, ami !";
			link.l1 = "Quoi ? Tu n'en as pas besoin ? Je voulais le rendre à son propriétaire légitime...";
			link.l1.go = "check_out_my_frigate_07";
		break;
		
		case "check_out_my_frigate_07":
			if(CheckAttribute(pchar, "questTemp.SharkGoldFleet"))
			{
				dialog.text = "Ha-ha-ha, mon ami, garde 'Fortune' pour toi. D'abord, tu en es le propriétaire légitime. Tu l'as obtenue honnêtement au combat. Il n'est pas bon d'abandonner le navire après cela. Et deuxièmement, j'ai déjà un nouveau vaisseau. Bien sûr, quand j'ai acheté 'Fortune', je ne pensais pas que je la changerais un jour pour autre chose. Mais, puisque je ne m'attendais plus à la revoir, j'ai commandé une nouvelle frégate à Alexus. Et tu sais... Il est sacrément bon. J'ai entendu dire, et dans ce cas ce n'était pas sans ta participation, ha ha !";
			}
			else
			{
				dialog.text = "Ha-ha-ha, mon ami, garde 'Fortune' pour toi. D'abord, tu en es le propriétaire légitime. Tu l'as honnêtement gagnée au combat. Il n'est pas bon d'abandonner le navire après cela. Et deuxièmement, un nouveau navire est déjà en construction pour moi. Bien sûr, quand j'ai acheté 'Fortune', je ne pensais pas que je la changerais un jour pour autre chose. Mais, comme je ne m'attendais pas à la revoir, j'ai commandé une nouvelle frégate à Alexus. Et j'ai hâte de pouvoir poser le pied sur son pont.";
			}
			link.l1 = "Eh bien, je n'ai pas d'autre choix que de garder ce magnifique navire pour moi, Steven !";
			link.l1.go = "check_out_my_frigate_08";
		break;
		
		case "check_out_my_frigate_08":
			dialog.text = "Exactement. La seule chose que je te demande, c'est de prendre soin de 'Fortune'. Crois-moi, tu ne trouveras pas un tel navire ailleurs. Il est unique. Et je l'aime comme un souvenir. Et je serais heureux de savoir que mon ami possède ce navire, et non quelque vaurien.";
			link.l1 = "Très bien, Steven. Je promets que je protégerai 'Fortune'.";
			link.l1.go = "check_out_my_frigate_09";
		break;
		
		case "check_out_my_frigate_09":
			dialog.text = "Oui, et encore une chose...";
			link.l1 = "Écoute.";
			link.l1.go = "check_out_my_frigate_10";
		break;
		
		case "check_out_my_frigate_10":
			dialog.text = "Puisque vous avez maintenant 'Fortune', je veux vous proposer une affaire.";
			link.l1 = "Je vous écoute TRÈS attentivement.";
			link.l1.go = "check_out_my_frigate_11";
		break;
		
		case "check_out_my_frigate_11":
			if(!CheckAttribute(pchar, "questTemp.SharkGoldFleet.KGBB"))
			{
				dialog.text = "Comme je l'ai dit, Alexus construit actuellement une nouvelle frégate pour moi. Il est, bien sûr, peu probable qu'il surpasse la 'Fortune' en vitesse, mais il ne cédera pas beaucoup non plus. Et juste pour une chose, j'ai besoin de quelques navires puissants mais rapides. Je pourrais peut-être le faire seul, mais deux c'est bien mieux.";
				link.l1 = "Génial. Et quel genre d'affaires est-ce?";
				link.l1.go = "check_out_my_frigate_12";
			}
			else
			{
				dialog.text = "Comme je l'ai dit, Alexus m'a récemment construit une nouvelle frégate. Il est, bien sûr, peu probable qu'il dépasse le 'Fortune' en vitesse, mais il ne cédera pas beaucoup non plus. Et justement pour une chose, j'ai besoin de quelques navires puissants, mais rapides. Je pourrais peut-être le faire seul, mais deux, c'est bien mieux.";
				link.l1 = "Parfait. Et quel genre d'affaire est-ce ?";
				link.l1.go = "check_out_my_frigate_13";
			}
		break;
		// Фрегат Акулы не построен
		case "check_out_my_frigate_12":
			dialog.text = "Il est trop tôt pour en parler, car je ne sais pas encore quand mon nouveau navire quittera le chantier. Alexus semble avoir quelques difficultés avec l'extraction des matériaux. D'ailleurs, si tu en as l'occasion, tu pourrais l'aider. Je suis sûr qu'il te paiera convenablement : je lui ai donné une avance très sérieuse. Après qu'il aura trouvé tous les matériaux, je pense que dans un mois mon navire sera prêt. Ensuite, je t'attends. Mais sois sûr de venir sur la 'Fortune' et équipe-la à l'avance, car il y aura peu de temps ! Oui, et assure-toi que les Espagnols ne veulent pas voir ta tête sur un plateau d'argent. Je te donnerai tous les détails plus tard.";
			link.l1 = "Eh bien, je demanderai à notre constructeur naval de quelle aide il pourrait avoir besoin. Et nous reprendrons notre conversation un mois après que j'aurai aidé Alexus, quand tu seras de nouveau en mer.";
			link.l1.go = "check_out_my_frigate_14";
		break;
		
		// Фрегат Акулы построен
		case "check_out_my_frigate_13":
			dialog.text = "Il est trop tôt pour en parler, car mon navire n'est même pas encore sorti des chantiers. Je dois encore l'équiper. Donc, je t'attends pas avant un mois. Mais sois sûr de venir sur la 'Fortune' et équipe-le à l'avance, alors il y aura peu de temps ! Oui, et assure-toi que les Espagnols ne veulent pas voir ta tête sur un plateau d'argent. Je te donnerai tous les détails plus tard.";
			link.l1 = "Très bien, nous reprendrons notre conversation plus tard, lorsque tu seras de nouveau sous voiles.";
			link.l1.go = "check_out_my_frigate_14";
		break;
		
		case "check_out_my_frigate_14":
			dialog.text = "Eh bien, soit. Maintenant je vais à la résidence, si cela ne te dérange pas. Les affaires, comme on dit, n'attendent pas.";
			link.l1 = "À bientôt, Requin ! Je ne dis pas adieu.";
			link.l1.go = "check_out_my_frigate_15";
		break;
		
		case "check_out_my_frigate_15":
			DialogExit();
			sld = characterFromId("Dodson");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload3_back","SharkFrigateEnd", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// belamour legendary edition на пару с Акулой
		case "SharkGoldFleet":
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = "Le mien est prêt, et le tien? Je t'ai dit de venir sur le 'Fortune'. Je ne sais pas où tu l'as laissé, mais il est trop risqué de se lancer dans un tel pari sur un autre navire. Alors je t'attends sur le navire sur lequel nous avons convenu. Et ne serre pas trop.";
				link.l1 = "Merde, j'ai complètement oublié, raclure ! Attends : je vais revenir sur le bon navire.";
				link.l1.go = "exit";
				break;
			}
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Charles, je t'avais dit de venir sans escadre. Pour l'affaire que je veux régler avec toi, des navires supplémentaires ne sont certainement pas nécessaires. Déplace ta flottille quelque part et reviens.";
				link.l1 = "Oui, j'ai complètement oublié. Attends : je reviendrai bientôt sans escadron.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Ah, te voilà, ami ! Enfin ! Et puis j'ai commencé à m'inquiéter. Mon navire est presque prêt. Maintenant je l'ai envoyé à Tirax : il doit l'équiper du calibre trente-deux, qu'il a pris du lourd galion de prix le mois dernier. Je l'ai déjà mené jusqu'aux Turcs et retour, et je dois dire qu'Alexus a fait un excellent travail. Au fait, je n'ai pas encore choisi un nom approprié pour lui, bien qu'il y ait plusieurs options. Peux-tu m'aider à choisir ?";
			link.l1 = "Bien sûr que j'aiderai ! Quel que soit le nom que tu donnes à un navire, c'est ainsi qu'il naviguera, n'est-ce pas ? Quelles sont tes options ?";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "J'ai tranché pour trois options jusqu'ici.";
			link.l1 = "...";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "La première option est 'Phantom'. La frégate est rapide et puissante, et avec ce nom, tous les avares de La Havane à Cumana trembleront rien qu'à sa mention !";
			link.l1 = "Ouais, et tu dois aussi apparaître et disparaître dans le brouillard pour que les marins commencent vraiment à se signer, ha ha ! Bon nom, ça me plaît.";
			link.l1.go = "SharkGoldFleet_03";
		break;
		
		case "SharkGoldFleet_03":
			dialog.text = "Je l'aime aussi. La deuxième option est 'Requin'. Et alors ? Pourquoi ne donnerais-je pas un surnom à mon navire ? Soyons homonymes avec lui, ha !";
			link.l1 = "Il y a un Requin sur le 'Requin'... Ironique. Mais tout le monde saura exactement à qui appartient le navire.";
			link.l1.go = "SharkGoldFleet_04";
		break;
		
		case "SharkGoldFleet_04":
			dialog.text = "Je suis à peu près pareil ici. Et la troisième option est 'Tempête'. Pour que tout le monde ait peur de s'approcher de mon navire, ha ha ha !";
			link.l1 = "Parce que tu pourrais te retrouver sous une pluie de boulets de canon de côté? Et alors, pas mal.";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			dialog.text = "Exactement ! Mais maintenant je ne peux pas me décider entre ces trois noms. Alors allez, aide-moi. Comme tu veux.";
			link.l1 = "Je suggère de le nommer 'Phantom'. Alors tous les marchands brandiront le drapeau blanc dès qu'ils te verront à l'horizon !";
			link.l1.go = "SharkGoldFleet_05f";
			link.l2 = "J'aime le nom 'Requin'. Tout le monde doit savoir que le navire n'est pas qu'un simple nouveau venu, mais la tête de la Confrérie de la Côte lui-même!";
			link.l2.go = "SharkGoldFleet_05a";
			link.l3 = "Je pense que 'Flurry' est un bon nom. Tout guerrier, corsaire ou marchand devrait savoir ce qui arrivera s'il décide de combattre ce navire.";
			link.l3.go = "SharkGoldFleet_05s";
		break;
		
		case "SharkGoldFleet_05f":
			pchar.questTemp.SharkGoldFleet.KGBB = "Phantom";
			dialog.text = "Regarde - même les militaires feront pareil, ha ! Alors, c'est décidé. Tiens la chope, ami. Buvons à mon nouveau navire. Pour 'Phantom !'";
			link.l1 = " Pour 'Phantom!'";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_05a":
			pchar.questTemp.SharkGoldFleet.KGBB = "Shark";
			dialog.text = "Et qu'ils réfléchissent à trois fois avant de croiser mon chemin ! Ainsi, c'est décidé. Tiens la chope, mon ami. Trinquons à mon nouveau navire. Pour 'Requin' !";
			link.l1 = "Pour 'Requin' !";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_05s":
			pchar.questTemp.SharkGoldFleet.KGBB = "Flurry";
			dialog.text = "Et s'il décide malgré tout, une telle rafale le couvrira que les tempêtes tropicales sembleront être une brise légère ! Alors, c'est décidé. Tiens la chope, ami. Buvons à mon nouveau navire. Pour 'Rafale!'";
			link.l1 = "Pour 'Flurry!'";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			dialog.text = "Et que ce navire serve fidèlement et ne connaisse pas l'amertume de la défaite ! Bon, maintenant, passons aux choses sérieuses.";
			link.l1 = "Je vous écoute attentivement.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "Dis-moi, Charles, sais-tu ce qu'est la 'Flotte d'Or' ?";
			link.l1 = "« Kha-kha ! .. Je me suis déjà étranglé avec du rhum. Steven, ne me dis pas que tu es sur deux frégates pour piller le convoi le plus lourdement armé des Caraïbes. »";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			dialog.text = "Eh bien, non, bien sûr, je ne suis pas suicidaire. Nous n'allons certainement pas piller tout le convoi. Mais ici, nous pouvons chaparder quelque chose de là.";
			link.l1 = "Steven, je suis désolé, bien sûr, mais je ne suis pas prêt pour cela. Oui, les Espagnols nous brûleront vifs si nous nous jetons dans leur flotte ! Allez-y sans moi.";
			link.l1.go = "SharkGoldFleet_09";
			link.l2 = "D'accord, là où nous n'avons pas disparu... Je suis prêt à participer !";
			link.l2.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_09":
			pchar.questTemp.SharkGoldFleet = "RUinDeal";
			dialog.text = "Argh ! C'est dommage. Je suis trop risqué sans toi. Bien, je ne vais pas te convaincre maintenant, mais réfléchis-y, d'accord ? Si jamais tu décides de le faire, fais-le moi savoir, je te prie.";
			link.l1 = "Si je le fais, alors bien sûr. Désolé, Steven.";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_10":
			dialog.text = "De telles entreprises n'abandonnent pas ! Eh bien, et toi ? As-tu peut-être changé d'avis ?";
			link.l1 = "Non, ami, je suis désolé, mais je passe encore.";
			link.l1.go = "exit";
			link.l2 = "D'accord, là où nous n'avons pas disparu... Je suis prêt à participer !";
			link.l2.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_11":
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = "Tu es peut-être prêt, mais ton navire ne l'est pas. Je t'ai dit de venir sur la 'Fortune'. Je ne sais pas où tu l'as laissée, mais c'est trop risqué de te lancer dans un tel pari sur un autre navire. Je t'attends donc sur le navire dont nous avons convenu. Et ne tends pas trop la corde.";
				link.l1 = "Merde, j’ai complètement oublié, empoté ! Attends : je vais revenir sur le bon navire.";
				link.l1.go = "exit";
				break;
			}
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Mais non : tu n'es pas prêt, Charles. Je t'ai dit de venir sans escadre. Dans l'affaire que je veux traiter avec toi, des navires supplémentaires ne sont certainement pas nécessaires. Déplace ta flotte ailleurs et reviens.";
				link.l1 = "Oui, j'ai complètement oublié. Attends : je reviendrai bientôt sans escadron.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = " Mille diables, c'est exactement ce que je voulais entendre ! Alors, je te propose que toi et moi volions un morceau du convoi. Beaucoup de butin...";
			link.l1 = "Piquer, tu veux dire ? Sans se faire prendre par les navires de garde ?";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			dialog.text = "Exactement. Écoutez, comme vous le savez probablement, la 'Flotte d'Or' se rassemble à Porto Bello puis se rend de là à La Havane. Après La Havane, il est déjà inutile de l'intercepter : elle traverse l'Atlantique vers l'Espagne avec une garde telle que seul un crétin complet oserait s'en approcher. Au moment de la transition de Porto Bello à La Havane, la situation n'est guère meilleure. Bien sûr, vous pouvez essayer, mais pour cela, vous devez assembler une escadre capable de briser même les forts comme des noix. Mais à Porto Bello, les navires convergent de tout le Maine, et là-bas, ils ne sont plus particulièrement protégés.";
			link.l1 = "Seulement maintenant le moment de la transition et les noms de ces navires sont strictement classifiés. Nous n'allons pas traîner autour de Porto Bello pendant un demi-an et intercepter tous les navires espagnols se rendant au port.";
			link.l1.go = "SharkGoldFleet_13";
		break;
		
		case "SharkGoldFleet_13":
			dialog.text = "Bien sûr que non. Depuis Carthagène, par exemple, les navires voguent par eux-mêmes, et, comme vous l'avez justement noté, seul Dieu sait de quels navires il s'agit et quand ils partiront. Mais de Caracas, près de laquelle il y a une mine espagnole, et qui est située assez loin de Porto Bello, les navires ne sont pas complètement seuls.";
			link.l1 = "Comment se fait-il qu'il ne soit pas complètement seul ?";
			link.l1.go = "SharkGoldFleet_14";
		break;
		
		case "SharkGoldFleet_14":
			dialog.text = "J'ai pu découvrir qu'un navire chargé de marchandises quitte Caracas seul ou avec une petite escorte, mais quelque part à la longitude du golfe de Maracaibo, des navires de guerre espagnols le rencontrent pour assurer sa sécurité ultérieure. Comment penses-tu qu'ils sachent quand et qui ils doivent y rencontrer ?";
			link.l1 = "Ils ont dû entendre quelque chose...";
			link.l1.go = "SharkGoldFleet_15";
		break;
		
		case "SharkGoldFleet_15":
			dialog.text = "D'accord. Avant que le navire principal ne parte, un navire de messagerie va de Caracas à Porto Bello, indiquant le lieu et la date de la rencontre, ainsi que le nom du navire espagnol. Ensuite, il revient et porte la confirmation que le navire sera rencontré au bon moment et au bon endroit. Ce n'est qu'après cela que notre objectif avec vous est avancé depuis Caracas.";
			link.l1 = "Mais si nous interceptons le courrier, alors le navire à Caracas ne recevra pas de confirmation et ne quittera pas le port. As-tu des idées à ce sujet? De plus, comment allons-nous attraper le courrier lui-même? Nous ne savons pas quand il partira non plus.";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_16":
			dialog.text = "Et ici, il y a un petit accroc. Les Espagnols, bien sûr, utilisent des lougres courriers à ces fins, mais c'est risqué : il y a trop de chances qu'ils soient interceptés par le premier pirate venu. Donc, vous pouvez attendre longtemps avant d'envoyer le navire. Par conséquent, s'il y a une opportunité, ils transmettent des instructions avec de bons navires puissants, mais rapides - des marchands, par exemple, ou des corsaires qui empruntent le bon itinéraire. \nTout comme un courrier scellé. De plus, c'est bien moins cher que d'envoyer un navire courrier séparé, même un lougre. Et les fonctionnaires espagnols avides aiment économiser de l'argent tout en mettant quelque chose dans leur poche, héhé.";
			link.l1 = "Je crois que je comprends ! Dois-je devenir un tel marchand ?";
			link.l1.go = "SharkGoldFleet_17";
		break;
		
		case "SharkGoldFleet_17":
			dialog.text = "Exactement ! Et nous avons eu de la chance : j'ai réussi à découvrir par une source fiable qu'à Caracas, ils cherchent actuellement un tel courrier pour l'envoyer avec une lettre dans les trois prochaines semaines. Et tu as justement un navire puissant et rapide, et même construit par les Espagnols ! Obtiens une licence GVIK, pour plus de crédibilité - pour six mois d'affilée, achète suffisamment de marchandises à Caracas pour une revente profitable à Porto Bello, puis rends-toi chez le chef local de l'autorité portuaire et demande si tu dois prendre quelque chose en chemin. \nSi l'autorité portuaire demande, présente-toi comme un Espagnol. Et oui - ne pense même pas à te traîner une escadrille avec toi. Il n'y a pas besoin d'attirer trop d'attention, sinon toute l'entreprise pourrait être compromise.";
			link.l1 = "Et des documents qu'ils me donneront, je découvrirai la date et le lieu de la rencontre du navire et du convoi ?";
			link.l1.go = "SharkGoldFleet_18";
		break;
		
		case "SharkGoldFleet_18":
			dialog.text = "Pas si simple. Je te dis : les documents sont scellés. Et tu ne peux pas les ouvrir toi-même. Ils les ouvriront à l'autorité portuaire de Porto Bello, puis ils rédigeront une réponse et, si tu es assez aimable pour dire que tu retournes à Caracas, ils te demanderont de l'y emmener. La réponse, bien sûr, sera également scellée.";
			link.l1 = "Et comment puis-je alors découvrir le lieu et la date de la réunion ?";
			link.l1.go = "SharkGoldFleet_19";
		break;
		
		case "SharkGoldFleet_19":
			dialog.text = "Il te faudra être malin et trouver un moyen de le savoir... Par exemple, au moment où les documents sont ouverts à Porto Bello et qu'ils écrivent la réponse. Ou simplement les voler lorsqu'ils te donnent une confirmation, qu'il faudra emmener à Caracas. Mais ce n'est pas une bonne option : après cela, tout peut mal tourner.";
			link.l1 = "Il est difficile, bien sûr... Mais je pense pouvoir y faire face.";
			link.l1.go = "SharkGoldFleet_20";
		break;
		
		case "SharkGoldFleet_20":
			dialog.text = "Je, à mon tour, prendrai mon navire de Marcus et t'attendrai à l'ancre au large du Cap Santa Maria à Curaçao. Quand tu auras terminé, rejoins-moi simplement. Nous intercepterons le navire aux coordonnées indiquées, puis nous nous éclipserons immédiatement d'ici. Maintenant tu comprends pourquoi il faut des navires puissants, mais rapides ? Je n'ai aucune envie de me battre contre l'escadre militaire espagnole. Il te faudra leur échapper.";
			link.l1 = "Compris. Eh bien, je pars. Rendez-vous au Cap Santa Maria !";
			link.l1.go = "SharkGoldFleet_21";
		break;
		
		case "SharkGoldFleet_21":
			dialog.text = "C'est ça, nous nous retrouverons là-bas. Eh bien, bonne chance, ami ! J'espère que notre affaire aboutira.";
			link.l1 = "Je l'espère aussi. Quoi qu'il en soit, je pars.";
			link.l1.go = "SharkGoldFleet_22";
		break;
		
		case "SharkGoldFleet_22":
			DialogExit();
			AddQuestRecord("SharkGoldFleet", "1");
			pchar.questTemp.SharkGoldFleet = "start";
			SetFunctionExitFromLocationCondition("SharkGoldFleetStart", pchar.location, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleet21", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleet30", 0, 0, 30, false);
			else NewGameTip("Exploration mode: timer is disabled.");
		break;
		// провал
		case "SharkGoldFleet_23":
			dialog.text = "Bon sang, Charles ! Je pensais ne jamais te revoir ! Où étais-tu passé ? Je t'attendais à l'endroit convenu, mais tu n'es jamais venu. Et je n'ai eu aucune nouvelle de toi.";
			link.l1 = "Désolé Steven. Je n'ai pas pu accomplir ma tâche.";
			link.l1.go = "SharkGoldFleet_24";
		break;
		
		case "SharkGoldFleet_24":
			NextDiag.CurrentNode = "First time";
			dialog.text = "Eh, ils ont raté un tel poisson... Bon, ne t'inquiète pas. Plus de chance la prochaine fois.";
			link.l1 = "J'espère bien.";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_25":
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = pchar.name+", bon sang ? Je t'ai dit de venir sans escadre ! Comprends bien : nous n'avons pas besoin de lest, sinon toute l'opération risque d'échouer ! Je ne sais pas ce qui t'a pris, mais ça ne marchera pas comme ça. Envoie d'urgence ton convoi ailleurs et reviens sur un seul navire. Je t'attends ici.";
				link.l1 = "Oui, je pensais juste que c'était plus probable... Très bien, je te comprends. Attends ici : je reviens tout de suite !";
				link.l1.go = "exit";
				NextDiag.TempNode = "SharkGoldFleet_25";
				break;
			}
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = pchar.name+", que diable? Je t'avais dit d'être sur le 'Fortune'! Comprends bien : nous avons besoin de deux navires rapides et puissants, sinon toute l'opération risque d'échouer! Je ne sais pas ce qui t'a pris, mais ça ne marchera pas comme ça. Change d'urgence ton rafiot pour le 'Fortune' et reviens. Je t'attends ici.";
				link.l1 = "Oui, je pensais juste que ce navire est meilleur... D'accord, je vous comprends. Attendez ici : je reviens tout de suite !";
				link.l1.go = "exit";
				NextDiag.TempNode = "SharkGoldFleet_25";
				break;
			} 
			dialog.text = "Et te voilà, mon ami ! Alors, comment trouves-tu mon beau ?";
			link.l1 = "Magnifique frégate, Steven ! Je ne refuserais pas cela...";
			link.l1.go = "SharkGoldFleet_26";
		break;
		
		case "SharkGoldFleet_26":
			dialog.text = "Non, tu as maintenant 'Fortune', haha ! Eh bien, raconte-moi comment ça s'est passé.";
			if(pchar.questTemp.SharkGoldFleet == "LightVarToShark")
			{
				link.l1 = "Tout s'est déroulé sans accroc : j'ai réussi à me faire passer pour un marchand honnête et fiable. J'ai amené les documents à Porto Bello, où j'ai réussi à distraire le chef local de l'autorité portuaire pendant cinq minutes et à réécrire pour moi-même la date et les coordonnées de la rencontre des navires avec la cargaison et l'escadron militaire.";
				link.l1.go = "SharkGoldFleet_27";
			}
			else
			{
				link.l1 = "Il y a eu quelques complications mineures. La lettre a été envoyée à Porto Bello par courrier. Je l'ai interceptée, livrée au destinataire et même reçu une réponse, mais le chef de l'autorité portuaire a deviné que je n'étais pas la personne censée apporter les documents. J'ai dû m'en échapper en combattant. Mais j'ai découvert la date et les coordonnées de la rencontre du navire avec la cargaison et l'escadron militaire, et j'ai livré la réponse à Caracas, donc la production nous attend !";
				link.l1.go = "SharkGoldFleet_30";
			}
		break;
		
		case "SharkGoldFleet_27":
			dialog.text = "Attends une seconde. As-tu dit 'navires' ?";
			link.l1 = "Oui, Requin ! Il y en aura deux !";
			link.l1.go = "SharkGoldFleet_28";
		break;
		
		case "SharkGoldFleet_28":
			dialog.text = "Ha-ha-ha, oui, nous allons décrocher le gros lot ! Eh bien, ma bête est prête à passer par un baptême du feu. Mais il n'a pas encore participé aux batailles, alors menons la bataille. Et pour l'instant, je rejoindrai votre escadron.";
			link.l1 = "Suis-je censé commander Steven Dodson lui-même, chef des Frères de la Côte ? En affaires !";
			link.l1.go = "SharkGoldFleet_29";
		break;
		
		case "SharkGoldFleet_29":
			NextDiag.TempNode = "SharkGoldFleet_33";
			pchar.questTemp.SharkGoldFleet.talk = true;
			AddQuestRecord("SharkGoldFleet", "22");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date);
			SGF_SharkCompanion();
			pchar.quest.SGF_SharkDelGroup1.win_condition.l1 = "ExitFromSea";
			pchar.quest.SGF_SharkDelGroup1.function = "SGF_SharkDelGroup";
			if(bImCasual)
			{
				pchar.GenQuest.SeaHunter2Pause = true;
				SeaHunter_Delete();
			}
			dialog.text = "Eh bien, ne sois pas trop arrogant : c'est seulement parce que je vais combattre sur mon navire pour la première fois. Et veille à la disponibilité d'officiers libres pour les navires-prises. Car leurs cales seront pleines, et aucun membre de mon équipage ne pourra gérer le navire seul ... Bon, assez de bavardages. Le butin nous attend !";
			link.l1 = "Exactement! Je vais à mon navire.";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_30":
			dialog.text = "Oui, tu as hérité ... Alors nous devons nous préparer au fait que l'escadron arrivera là avant la date convenue, et nous devrons nous battre avec tout le monde à la fois.";
			link.l1 = "Pourquoi dis-tu cela ?";
			link.l1.go = "SharkGoldFleet_31";
		break;
		
		case "SharkGoldFleet_31":
			dialog.text = "Et vous réfléchissez. À Porto Bello, ils savent que le navire avec la cargaison quittera certainement Caracas, car vous y avez apporté la lettre de retour. Mais comme vous vous êtes trahi, ils feront de leur mieux pour nous empêcher d'intercepter ce navire. Je pense que l'escadron y arrivera en premier. C'est ce que je ferais. Alors, préparons-nous pour un combat difficile. Retarder le retrait.";
			link.l1 = "Ne t'inquiète pas. Toi et moi sommes deux loups de mer, nous n'avons pas traversé tout ça pour rien !";
			link.l1.go = "SharkGoldFleet_32";
		break;
		
		case "SharkGoldFleet_32":
			dialog.text = "Ta vérité. Eh bien, ma bête est prête à subir un baptême de feu. Mais elle n'a pas encore participé aux batailles, alors que tu mènes la bataille. En attendant, je rejoindrai ton escadre.";
			link.l1 = "Suis-je censé ordonner à Stephen Dodson lui-même, chef de la Fraternité de la Côte ? En affaires !";
			link.l1.go = "SharkGoldFleet_29";
		break;
		
		case "SharkGoldFleet_33":
			NextDiag.TempNode = "SharkGoldFleet_33";
			dialog.text = "Pas le temps de bavarder, "+pchar.name+"En avant pour le butin !";
			link.l1 = "Et que la chance soit avec nous !";
			link.l1.go = "exit";
		break;
		// делим добычу на берегу
		case "SharkGoldFleet_34":
			if(makeint(pchar.questTemp.SharkGoldFleet) > 74)
			{
				dialog.text = "Milliers de diables ! Beau travail, Charles ! Le butin s'est révélé bien plus riche que je ne le pensais au départ ! Je crois que tout ce voyage en valait vraiment la peine.";
				link.l1 = "Je suis totalement d'accord avec toi, Steven ! Aujourd'hui est assurément notre jour !";
				link.l1.go = "SharkGoldFleet_35";
			}
			else
			{
				if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
				{
					dialog.text = "Bon travail, ami. Cependant, nous devons admettre que nous avons perdu beaucoup de proies.";
					link.l1 = "Je suis d'accord, Steven, nous pourrions faire mieux. Mais ce qui est là est aussi bon !";
					link.l1.go = "SharkGoldFleet_35";
				}
				else
				{
					dialog.text = "Merde ! C'était une si bonne idée... Et au final, les dépenses de cette campagne dépassent les profits. Charles, je t'avais effectivement donné le commandement, et tu as réussi à tout perdre !";
					link.l1 = "Ne dis rien... Je suis moi-même mauditement en colère. Combien de proies nous ont échappé !..";
					link.l1.go = "SharkGoldFleet_37";
				}
			}
		break;
		
		case "SharkGoldFleet_35":
			dialog.text = "Eh bien, nous avons tous deux fait du bon travail. J'ai conçu un plan et obtenu les informations sur le courrier, et tu as brillamment mis ce plan en action. Et nous avons tous deux combattu à armes égales pour notre proie. Par conséquent, je propose de la diviser selon les lois de la Fraternité de la Côte : également !";
			link.l1 = "Nous le ferons !";
			link.l1.go = "SharkGoldFleet_36";
		break;
		
		case "SharkGoldFleet_36":
			dialog.text = "Eh bien, je m'en vais maintenant à l'Isla Tesoro. Je dois réparer le navire et célébrer comme il se doit le premier voyage réussi sur mon nouveau navire. Bonne chance, ami ! Toujours heureux de te voir à ma résidence !";
			link.l1 = "Je suis ravi que notre affaire se soit avérée si rentable. Je viendrai vous voir un de ces jours. Bonne chance !";
			link.l1.go = "SharkGoldFleet_39";
		break;
		
		case "SharkGoldFleet_37":
			dialog.text = "Très bien, garde tout pour toi. S'il en reste quoi que ce soit. Je ne m'intéresse pas à ces petits. Après tout, c'est moi qui t'ai mêlé à toute cette affaire.";
			link.l1 = "Oui, ma faute aussi... Désolé, Steven.";
			link.l1.go = "SharkGoldFleet_38";
		break;
		
		case "SharkGoldFleet_38":
			dialog.text = "Ne t'excuse pas, je te dois toujours la vie, et je ne l'oublierai pas. Et maintenant je pars pour Isla Tesoro. Nous devons réparer le navire et le nettoyer ... Quoique, qu'est-ce qu'il y a à nettoyer ... Bonne chance, compagnon ! Toujours heureux de te voir à ma résidence !";
			link.l1 = "Bien, tout peut arriver, des défaites se produisent. L'essentiel, c'est que nous soyons vivants. Je viendrai certainement te rendre visite un de ces jours, ami ! Bonne chance !";
			link.l1.go = "SharkGoldFleet_39";
		break;
		
		case "SharkGoldFleet_39":
			if(makeint(pchar.questTemp.SharkGoldFleet) > 74)
			{
				AddQuestRecord("SharkGoldFleet", "34");	
				ChangeCharacterComplexReputation(pchar, "fame", 10);
				ChangeCharacterComplexReputation(pchar, "authority", 5);
				ChangeOfficersLoyality("good_all", 2);
				AddComplexSeaExpToScill(150, 150, 150, 150, 150, 150, 0);
				AddCharacterExpToSkill(pchar, "Leadership", 300);
				AddCharacterExpToSkill(PChar, "Fortune", 300);
				AddCharacterExpToSkill(PChar, "Sneak", 300);
			}
			else
			{
				if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
				{
					AddQuestRecord("SharkGoldFleet", "35");
					ChangeCharacterComplexReputation(pchar, "fame", 1);
					ChangeCharacterComplexReputation(pchar, "authority", 1);
					AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
					AddCharacterExpToSkill(pchar, "Leadership", 200);
					AddCharacterExpToSkill(PChar, "Fortune", 200);
					AddCharacterExpToSkill(PChar, "Sneak", 200);
				}
				else
				{
					AddQuestRecord("SharkGoldFleet", "36");
					AddCharacterExpToSkill(pchar, "Leadership", 100);
					AddCharacterExpToSkill(PChar, "Fortune", 100);
					AddCharacterExpToSkill(PChar, "Sneak", 100);
				}
			}
			if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
			{
				if(GetSquadronGoods(pchar, GOOD_GOLD)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_GOLD, sti(makeint(pchar.questTemp.SharkGoldFleet.Gold)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SILVER)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SILVER, sti(makeint(pchar.questTemp.SharkGoldFleet.Silver)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SANDAL)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SANDAL, sti(makeint(pchar.questTemp.SharkGoldFleet.Sandal)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SHIPSILK)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SHIPSILK, sti(makeint(pchar.questTemp.SharkGoldFleet.Silk)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_ROPES)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_ROPES, sti(makeint(pchar.questTemp.SharkGoldFleet.Ropes)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_OIL)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_OIL, sti(makeint(pchar.questTemp.SharkGoldFleet.Gold)/2));
				}
			}
			SGF_GoodSwimReturn();
			SGF_DelAllSubAttributes(); // убираем все лишнее, чтобы не болталось
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "SGF_SharkToIT", -1);
			CloseQuestHeader("SharkGoldFleet");
			DialogExit();
		break;
	}
}
