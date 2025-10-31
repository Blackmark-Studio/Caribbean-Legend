// колдун ривадос - Чимисет
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Tu veux quelque chose ?";
			link.l1 = "Non, peu importe.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//-------------------------------------в тюрьме на Тартарусе-----------------------------
		// вариант R
		case "KillChad":
			dialog.text = "Attends ! Arrête... Je te supplie de m'écouter avant de commettre une erreur.";
			link.l1 = "Je t'écoute... J'espère que tu as un argument raisonnable pour m'empêcher de...";
			link.l1.go = "KillChad_1";
			LAi_RemoveCheckMinHP(npchar); //убираем проверяльщик, если ещё есть
		break;
		
		case "KillChad_1":
			dialog.text = "De me tuer, n'est-ce pas ? J'ai entendu que tu parlais avec Chad à l'étage et je ne t'en veux pas - n'importe qui ferait probablement la même chose. Mais tu as tort de penser que Chad te laissera partir après m'avoir tué.";
			link.l1 = "Hum... Intéressant, et pourquoi ne le ferait-il pas ? La seule chose que je sais, c'est que je vais devoir suer sang et eau pour sortir d'ici, à moins que je ne te tue simplement.";
			link.l1.go = "KillChad_2";
		break;
		
		case "KillChad_2":
			dialog.text = "Tu n'auras aucun avenir si tu me tues. Écoute, les Narvals et Chad veulent se débarrasser de moi, mais ils ont trop peur pour le faire eux-mêmes - mon meurtrier sera maudit à jamais. Alors ils veulent que tu fasses tout le sale boulot.\nChad sait que tu n'es pas Rivados, il te manipule. Une fois que tu m'auras tué, ils te feront la même chose et utiliseront ton cadavre pour tromper le Requin.";
			link.l1 = "Requin ? Steve Dodson ? Est-il vraiment ici ? Et explique-moi enfin - qui diable sont ces Rivados ?";
			link.l1.go = "KillChad_3";
		break;
		
		case "KillChad_3":
			dialog.text = "Heh, on dirait bien que tu n'habites pas ici, en effet... Mais ce n'est pas le moment de raconter des histoires. Nous devons nous sauver. J'ai un plan.";
			link.l1 = "Tu sais quoi, sorcier, je viens juste de traverser un portail mystique et je m'en suis à peine sorti vivant, alors tes malédictions ne me font pas peur. J'en ai assez - il est temps d'en finir avec toi.";
			link.l1.go = "KillChad_fightfail";
			link.l2 = "D'accord, je te fais confiance. Quel est le plan ?";
			link.l2.go = "KillChad_4";
		break;
		
		case "KillChad_fightfail":
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "afraid", "", -1);
			LAi_SetImmortal(npchar, false);
			pchar.quest.LSC_fightfail.win_condition.l1 = "NPC_Death";
			pchar.quest.LSC_fightfail.win_condition.l1.character = "Chimiset";
			pchar.quest.LSC_fightfail.function = "LSC_Fightfail_Final";
		break;
		
		case "KillChad_4":
			dialog.text = "Il y a un coffre là-bas. Il contient des armes décentes et des potions. Il est verrouillé, mais la serrure est vieille et endommagée, alors trouve un pied-de-biche pour l'ouvrir\nPrends tout ce qui se trouve dans le coffre, arme-toi et va vers les escaliers. C'est une bonne position défensive, ils seront forcés de t'affronter un par un, fais juste attention aux mousquetaires\nJ'espère que tu te débrouilles bien avec une lame, je suis trop vieux pour t'aider à combattre. Si tu parviens à les tuer tous et à survivre dans le processus - je te garantis la protection des Rivados, ma famille...";
			link.l1 = "Bien. Priez vos dieux pour moi - le combat va être rude. Ces gaillards là-haut ont l'air vraiment sérieux.";
			link.l1.go = "KillChad_5";
		break;
		
		case "KillChad_5":
			DialogExit();
			pchar.quest.LSC_fightfail.over = "yes"; //снять прерывание
			LAi_SetImmortal(npchar, true);
			ref location = &Locations[FindLocation(pchar.location)];
			location.private1.key = "crowbar";
			location.private1.key.delItem = true;
			NextDiag.CurrentNode = "KillChad_6";
		break;
		
		case "KillChad_6":
			dialog.text = "Ne perds pas de temps ! Force la serrure rapidement...";
			link.l1 = "Oui, oui, je suis en chemin.";
			link.l1.go = "exit";
			NextDiag.TempNode = "KillChad_6";
		break;
		
		case "Chad_die":
			dialog.text = "Bien joué ! Vous êtes vraiment un maître de l'escrime. Je vous dois une fière chandelle, étranger. Dites-moi, quel est votre nom ?";
			link.l1 = "Bonjour, mon ami."+pchar.name+". "+GetFullName(pchar)+"Et quel est le vôtre ?";
			link.l1.go = "Chad_die_1";
		break;
		
		case "Chad_die_1":
			dialog.text = "Mon nom est Chimiset, je suis un chaman Rivados et conseiller de notre chef - Black Eddie. Il sera ravi de savoir que vous m'avez libéré et sauvé la vie. Vous êtes un ami de Chimiset, de Black Eddie et de tous les Rivados. Désormais, vous serez toujours un invité bienvenu sur notre Protecteur...";
			link.l1 = "Attends... Chimiset, au cas où tu n'aurais toujours pas compris, cela ne fait que quelques heures que je suis arrivé ici. Peux-tu m'expliquer où je suis, qui sont les Rivados, et où je peux trouver Requin Dodson ?";
			link.l1.go = "Chad_die_2";
		break;
		
		case "Chad_die_2":
			dialog.text = "Cet endroit s'appelle la Ville des Navires Abandonnés. Bien que cela ressemble plus à une moquerie. Ce n'est pas vraiment une ville. Cet endroit est une île formée de centaines de navires morts. Le centre est adapté pour l'habitation. Il est habité par des personnes qui ont survécu aux naufrages inexplicables causés par les tempêtes qui les ont amenés ici\nRivados est un clan, un groupe de personnes qui vivent ensemble depuis longtemps. Il y a aussi trois autres groupes vivant ici : le clan Narval, ils sont nos ennemis, les pirates de Shark Dodson et les gens du commun. Shark est essentiellement le chef de l'île, il se nomme lui-même amiral\nIl est arrivé assez récemment et a pris le pouvoir de manière violente. Il a capturé le 'San Augustine' où nous entreposions nos provisions alimentaires. Maintenant, nous devons acheter des provisions aux prix fixés par Shark. Il semble que vous ayez déjà été dans cet entrepôt\nChad Kapper était le maître d'équipage de Shark et le chef de la prison. Layton Dexter était autrefois le second de Shark, il a aussi une certaine influence. Ces trois-là et leurs pirates sont une force dominante sur l'île face à la fois aux Rivados et aux Narvals.";
			link.l1 = "Pourquoi Chad Kapper voulait-il que je te tue ?";
			link.l1.go = "Chad_die_3";
		break;
		
		case "Chad_die_3":
			dialog.text = "Chad avait établi des contacts avec les Narvals, nos ennemis. Il allait tuer Shark avec leur aide et prendre sa place. Les Narvals en veulent à l'amiral pour la mort d'Alan Milrow, leur ancien chef. Ils croient que Shark est responsable de sa mort, mais ils se trompent. Je sais qui l'a fait. C'est Chad. Je suis le seul témoin de ce crime\nC'est pourquoi Chad ne pouvait pas me laisser libre, pourtant il craignait aussi de me faire du mal. Les pirates sont intrépides au combat, mais ils sont très superstitieux. Alors il voulait vous utiliser. Chad et les Narvals auraient fait tuer Shark et accusé les Rivados.";
			link.l1 = "Est-ce vrai ? Dis-moi pourquoi...";
			link.l1.go = "Chad_die_4";
		break;
		
		case "Chad_die_4":
			dialog.text = "Bonjour, ami."+pchar.name+", mon ami, parlons plus tard. Nous devons nous dépêcher, avant que les pirates de Requin n'apparaissent. Fouille le corps de Chad et prends ses clés. Mais d'abord, vérifie son bureau, il pourrait y avoir des papiers intéressants là-bas\nVa voir Requin Dodson, tu le trouveras dans le 'San Augustine', un grand navire échoué à distance des autres, il y a un pont qui y mène depuis le navire nommé 'Pluto'. Dis-lui que Chad complotait une trahison, et dis que les Narvals sont derrière tout ça, et que nous, les Rivados, n'avons rien à voir avec cela.\nJe te donnerai volontiers toutes les informations dont tu as besoin sur cette île, sur mon clan et les autres, une fois que tu seras arrivé à notre résidence dans le Protector. Sortons d'ici !";
			link.l1 = "Très bien, Chimiset. Je te retrouverai plus tard au... 'Protecteur'. Sortons d'ici !";
			link.l1.go = "Chad_die_5";
		break;
		
		case "Chad_die_5":
			dialog.text = "Encore une chose. Nos navires, y compris le 'Protecteur', sont interdits aux étrangers. Vous devez être Rivados ou connaître un mot de passe pour entrer. Je vous le dirais bien, mais il change chaque semaine et je suis ici depuis trop longtemps, donc je ne connais pas le mot de passe actuel.\n Vous devriez d'abord visiter le 'San Augustine'. Je dirai à nos gens qui vous êtes, pendant que vous parlez à Shark, ils vous attendront. Mais ne vous rendez pas au 'Protecteur' maintenant, parlez d'abord à Shark, et laissez-moi rencontrer mes gens d'abord, sinon les Rivados seront hostiles envers vous.";
			link.l1 = "Je vois. Je me dirige vers 'San Augustine'. À bientôt !";
			link.l1.go = "Chad_die_6";
		break;
		
		case "Chad_die_6":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.LSC_LetterChad.win_condition.l1 = "item";
			pchar.quest.LSC_LetterChad.win_condition.l1.item = "letter_chad";
			pchar.quest.LSC_LetterChad.function = "LSC_LetterChad_Find";
			sld = characterFromId("SharkMush_17");
			sld.lifeday = 0;
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("SharkSold_1"+(i+3));
				sld.lifeday = 0;
			}
			AddSimpleRumourCityTip("Ha, they say that you are a friend of clan Rivados. This is interesting. Congratulations...", "LostShipsCity", 5, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that you have saved the Rivados wizard Chimiset from 'Tartarus'. Now you are a welcome guest on their ships.", "LostShipsCity", 5, 1, "LSC", "");
			AddSimpleRumourCityTip("So it was you who has set Chimiset free! Interesting. Now you are a friend of Rivados but an enemy of Narwhals. I am not sure whether to congratulate you or to sympathize...", "LostShipsCity", 5, 1, "LSC", "");
		break;
		
		// вариант N
		case "prisoner":
			dialog.text = "Que veux-tu de moi, étranger ?";
			link.l1 = "Ton nom est Chimiset, n'est-ce pas ?";
			link.l1.go = "prisoner_1";
		break;
		
		case "prisoner_1":
			dialog.text = "Oui, c'est moi. Vous avez affaire avec moi ou vous voulez juste discuter ?";
			link.l1 = "J'ai quelques affaires à discuter. Je suis venu ici de la part de l'Amiral, Requin Dodson. J'ai apporté un ordre pour vous libérer, mais à une condition : vous devez répondre à plusieurs de mes questions.";
			link.l1.go = "prisoner_2";
		break;
		
		case "prisoner_2":
			dialog.text = "Est-ce que Dodson a décidé de me libérer ? Je suis ravi de l'entendre. Posez vos questions. J'espère qu'il n'y a pas de ruse là-dedans, sinon mon excitation aura été vaine.";
			link.l1 = "Aucune ruse, j'ai seulement besoin de ton aide. Dis-moi, Chimiset, y a-t-il une idole bizarre en pierre sur cette île ? Elle se transforme en or à minuit. Ne me prends pas pour un fou...";
			link.l1.go = "Friend_2";
		break;
		
		case "prisoner_3":
			dialog.text = "Encore des questions ?";
			link.l1 = "Oui. Connaissez-vous un homme appelé le Garçon Blanc ?";
			link.l1.go = "prisoner_4";
		break;
		
		case "prisoner_4":
			dialog.text = "Garçon blanc ? Bien sûr, je le connais. C'est le surnom d'Olle Christiansen, notre idiot local. Il est adulte maintenant et ne ressemble plus à un garçon, bien que son esprit soit toujours enfantin.";
			link.l1 = "Vraiment ? Dis-moi, où puis-je le trouver ?";
			link.l1.go = "prisoner_5";
		break;
		
		case "prisoner_5":
			dialog.text = "Partout dans notre ville. On le trouvait souvent dans la boutique, la taverne ou en train de marcher dans les rues. Il a les cheveux blancs, vous le reconnaîtrez.";
			link.l1 = "Excellent ! Une question de plus : avez-vous rencontré ici un homme du nom de Nathaniel Hawk ? Il a dû se montrer ici il y a quelque temps, et il pourrait être gravement malade.";
			link.l1.go = "prisoner_6";
		break;
		
		case "prisoner_6":
			dialog.text = "Je ne peux pas vous aider avec ça, étranger. Je ne connais pas d'homme portant ce nom. Je peux vous assurer qu'il n'est pas sur les navires des Rivados, et il ne devrait pas non plus être dans la zone neutre. Je ne peux pas en dire autant des territoires des Narvals, cependant, les Rivados ne les visitent pas.";
			link.l1 = "Eh bien, merci quand même... Vous m'avez beaucoup aidé, Chimiset !";
			link.l1.go = "prisoner_7";
		break;
		
		case "prisoner_7":
			dialog.text = "C'est tout ? Le Requin va-t-il me libérer maintenant ?";
			link.l1 = "Oui. Je n'ai plus rien à te demander. Chad Kapper te libérera. Eh bien, je dois partir...";
			link.l1.go = "prisoner_8";
		break;
		
		case "prisoner_8":
			dialog.text = "Arrête ! Attends... Reviens.";
			link.l1 = "As-tu d'autres choses à me dire ?";
			link.l1.go = "prisoner_9";
		break;
		
		case "prisoner_9":
			dialog.text = "Pas exactement... (abaissant la voix) Je vois que vous n'êtes pas des hommes de Kapper. Ne lui faites pas confiance. C'est une vermine infâme. Il n'y a pas longtemps, il a froidement tué l'innocent Alan Milrow avec une épée large. Il était le chef du clan des Narvals. Je ne l'ai pas vu venir, Chad s'est simplement approché de sa cellule et l'a exécuté. De plus, j'ai entendu des rumeurs selon lesquelles les propres hommes de l'Amiral prévoient de l'assassiner. Dites-le à Shark. Et dites-lui que j'en dirai plus quand nous parlerons en face à face.";
			link.l1 = "Hm. Très bien, je vais en parler à Dodson. À bientôt !";
			link.l1.go = "prisoner_10";
		break;
		
		case "prisoner_10":
			DialogExit();
			sld = characterFromId("Capper");
			sld.quest.chimiset_talk = "true"; // разговор с Чимисетом состоялся
			if (!CheckAttribute(npchar, "quest.capper_talk")) chrDisableReloadToLocation = true;//закрыть локацию
			else chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance_10"; // ноду Акуле
			LSC_SetWhiteBoy(); // поставим белого мальчика
			NextDiag.CurrentNode = "prisoner_11";
			AddQuestRecord("SharkHunt", "20");
		break;
		
		case "prisoner_11":
			dialog.text = "Va voir Requin et dis-lui tout ce que je t'ai dit. Eh, j'espère qu'ils ouvriront cette cage bientôt...";
			link.l1 = "Oui, oui. Je suis en route.";
			link.l1.go = "exit";
			NextDiag.TempNode = "prisoner_11";
		break;
		
		//------------------------беседа на Протекторе, если был старт через Тартарус-----------------
		case "Friend":
			dialog.text = "Te voilà, mon cher ami. Merci encore de m'avoir sauvé et de m'avoir fait confiance, au lieu de Kapper. Je vais te donner ces amulettes pour te récompenser. Je suis sûr qu'elles te seront utiles.";
			link.l1 = "Merci ! Je ne m'attendais pas à ça...";
			link.l1.go = "Friend_1";
		break;
		
		case "Friend_1":
			GiveItem2Character(pchar, "indian_1");
			GiveItem2Character(pchar, "indian_11");
			GiveItem2Character(pchar, "amulet_1");
			PlaySound("interface\important_item.wav");
			dialog.text = "Et maintenant je suis prêt à vous écouter. Vous vouliez me demander quelque chose, n'est-ce pas?";
			link.l1 = "Tu as raison, Chimiset. J'ai besoin de ton aide. D'abord, je dois savoir, y a-t-il une étrange idole de pierre sur cette île ? Elle se transforme en or à minuit. Ne me prends pas pour un fou...";
			link.l1.go = "Friend_2";
		break;
		
		// нода пересечения
		case "Friend_2":
			dialog.text = "Oui, je vois ce que tu veux dire, mon ami. J'ai vu cette statue des dieux indiens de mes propres yeux. Bien qu'elle ne devienne dorée que sous les rayons du soleil levant, et non de la lune... bien des fois nous avons sacrifié des Narvals malfaisants et le dieu les a tous dévorés. Mais elle n'est plus sur l'Île.";
			link.l1 = "Comment cela se fait-il?! Tu dis qu'il a disparu tout d'un coup?!";
			link.l1.go = "Friend_3";
		break;
		
		case "Friend_3":
			dialog.text = "Pas exactement comme ça. Cette statue était à l'intérieur du 'San Geronimo'. Ce navire a sombré avec la statue il y a plusieurs années.";
			link.l1 = "Quel coup du sort ! Il semble qu'il soit impossible de quitter l'île maintenant... Et où était ce navire ?";
			link.l1.go = "Friend_4";
		break;
		
		case "Friend_4":
			dialog.text = "Pas loin des territoires des Narvals, près des épaves du navire nommé 'Phoenix'. Vous pouvez voir le navire reposant sur le fond marin par beau temps.";
			link.l1 = "Ha ! Alors il est échoué au banc de sable ? Je peux nager jusqu'à lui, alors...";
			link.l1.go = "Friend_5";
		break;
		
		case "Friend_5":
			dialog.text = "You can't, my friend. First, it's too deep down there; second, there are many giant crabs. They will tear you apart before you get to the 'San Geronimo'.";
			link.l1 = "Hm.  Bon, je vais y réfléchir. Au moins, je sais que la statue existe, et c'est le plus important.";
			if (CheckAttribute(npchar, "quest.chimiset_die")) link.l1.go = "prisoner_3";
			else
			{	
				if (CheckAttribute(pchar, "questTemp.LSC.Mary")) link.l1.go = "freedom_1";
				else link.l1.go = "Friend_6";
			}
			AddQuestRecord("LSC", "4");
		break;
		// нода пересечения
		
		case "Friend_6":
			dialog.text = "Je vois que tu as plus de questions. N'hésite pas à demander, mon ami.";
			link.l1 = "Requin Dodson m'a demandé de trouver les complices de Chad dans le crime. J'ai trouvé une lettre dans le coffre de Chad. Il y a quelque chose à propos d'un tireur d'élite et d'un fusil. On dirait qu'ils veulent assassiner Requin à distance. As-tu une idée en tête ?";
			link.l1.go = "Friend_7";
		break;
		
		case "Friend_7":
			dialog.text = "Hm. Ils vont tirer sur l'amiral? Je dois réfléchir... Le problème, c'est que l'amiral ne quitte presque jamais sa résidence, et lorsqu'il le fait, il est protégé par une demi-douzaine de pirates. Mais il a une habitude, il aime se promener à l'arrière tard le soir\nIl y a deux positions pour un tireur d'élite pour tirer dans la résidence de l'amiral - la proue de la 'Santa Florentina' et un mât du 'Fury'. Mais un tireur d'élite ne pourra toujours pas tuer l'amiral de ces positions, il doit avoir l'œil d'un aigle pour faire un tel tir. De plus, il aurait besoin d'un fusil excellent. Vous devriez vous renseigner sur l'île à propos des gens qui ont accès à de telles armes à feu.";
			link.l1 = "Hé, on dirait que tu as raison, il y a quelque chose à propos d'un pistolet dans la lettre... As-tu vu quelqu'un avec un tel pistolet ?";
			link.l1.go = "Friend_8";
		break;
		
		case "Friend_8":
			dialog.text = "Non. Je n'ai même jamais vu un pistolet comme ça dans ma vie. Demandez aux gens, peut-être que quelqu'un pourra vous renseigner.";
			link.l1 = "Bien... Quoi qu'il en soit, vos informations sont précieuses, merci ! Eh bien, la dernière question maintenant, bien que je n'attende pas de réponse... Avez-vous entendu parler du Garçon Blanc ?";
			link.l1.go = "Friend_9";
		break;
		
		case "Friend_9":
			dialog.text = "Blanc-bec ? Bien sûr, je le connais. C'est le surnom d'Olle Christiansen, notre idiot local. Il est adulte maintenant et il ne ressemble plus à un garçon, bien que son esprit soit encore enfantin.";
			link.l1 = "Vraiment ? Dis-moi où puis-je le trouver ?";
			link.l1.go = "Friend_10";
		break;
		
		case "Friend_10":
			dialog.text = "Partout dans notre ville. On le trouve souvent à la boutique, à la taverne ou dans les rues. Il a les cheveux blancs - vous le reconnaîtrez sans doute.";
			link.l1 = "Superbe ! Merci, Chimiset, tu m'as beaucoup aidé !";
			link.l1.go = "Friend_11";
		break;
		
		case "Friend_11":
			dialog.text = "Je suis toujours heureux d'aider ! Venez me voir si vous avez d'autres questions.";
			link.l1 = "Bien sûr ! Je dois y aller maintenant. À bientôt !";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary")) link.l1.go = "freedom_2";
			else link.l1.go = "Friend_12";
		break;
		
		case "Friend_12":
			DialogExit();
			NextDiag.CurrentNode = "Chimiset_wait";
			LSC_SetWhiteBoy(); // ставим Белого Мальчика в магазин
			pchar.questTemp.Saga.SharkHunt = "search_mush_1"; // флаг на магазин - поиск мушкета
			AddQuestRecord("SharkHunt", "11");
		break;
		
		case "freedom":
			dialog.text = "Et voici mon cher ami à qui je dois ma liberté et peut-être même ma vie. Merci d'avoir aidé mes frères à me sauver de ce sale Kapper. Je te donnerai ces amulettes pour te récompenser. Je suis sûr que tu les trouveras utiles.";
			link.l1 = "Merci ! Je ne m'attendais pas à ça...";
			link.l1.go = "Friend_1";
		break;
		
		case "freedom_1":
			dialog.text = "As-tu autre chose à demander, ami blanc ?";
			link.l1 = "Dis-moi, Chimiset, connais-tu le Garçon Blanc ?";
			link.l1.go = "Friend_9";
		break;
		
		case "freedom_2":
			DialogExit();
			NextDiag.CurrentNode = "Chimiset_wait";
			LSC_SetWhiteBoy(); // ставим Белого Мальчика в магазин
		break;
		
		//--> информационный блок
		case "Chimiset_wait": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Oh! Mon ami blanc "+pchar.name+" ! Ne t'es-tu pas noyé ? Les esprits t'ont sauvé, je le sais...";
				link.l1 = "Je suis bien vivant, Chimiset. Des esprits ? Peut-être as-tu raison, tout cela est arrivé à cause de Kukulcan...";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "Qu'est-ce qui t'amène ici, mon bon ami ?";
			/*if (!CheckAttribute(npchar, "quest.story"))
			{
				link.l1 = "Dis-moi comment le chef des Narvals est mort. Tu étais le seul à avoir vu ça.";
				link.l1.go = "story";
			}*/
			if (!CheckAttribute(npchar, "quest.crab"))
			{
				link.l2 = "Tu as mentionné les crabes au fond près du 'San Geronimo'. Peux-tu décrire ces monstres ?";
				link.l2.go = "crab";
			}
			link.l9 = "Rien de spécial, Chimiset. Je voulais juste te voir.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		
		case "story":
			dialog.text = "Une histoire de la mort d'Alan Milrow sera écrite ici.";
			link.l1 = "Très bien !";
			link.l1.go = "exit";
			npchar.quest.story = "true";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		
		case "crab":
			dialog.text = "Personne ne sait d'où ils viennent, ni pourquoi ils ont atteint une taille si gigantesque. Nous ne savons pas grand-chose sur ces bêtes. Elles existent, beaucoup de gens les ont vues. On peut en trouver des groupes parmi les épaves de navires dans les eaux peu profondes. Ils rôdent au fond de la mer, chassant les poissons et mangeant tous les déchets que nous jetons. Ils sont une véritable menace. Leurs pinces peuvent infliger des blessures graves, et leurs mâchoires libèrent un poison dangereux, semblable à celui des poissons marins. Si empoisonné et non traité, un homme rencontrera le créateur. Heureusement, la toxine peut être neutralisée par un antidote fabriqué à partir d'herbes locales. Il y avait un chasseur de crabes parmi nous. Il avait l'habitude de rapporter leur chair, un plat sacrément délicieux. Mais le plus important : il ramenait souvent les pinces de ces monstres et des mâchoires avec du poison. Elles étaient les ingrédients principaux de certaines de mes potions. Dommage, cela fait longtemps que personne ne m'en a apporté...";
			link.l1 = "Et où est ce chasseur maintenant ?";
			link.l1.go = "crab_1";
		break;
		
		case "crab_1":
			dialog.text = "Prends l'indice. Tu dois être prêt à devenir toi-même une proie en chassant ces bêtes. Un jour, il n'est simplement pas revenu. C'est pourquoi je te préviens d'être prudent et attentif autour de ces créatures.";
			link.l1 = "Je vois...";
			link.l1.go = "exit";
			npchar.quest.crab = "true";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		//<-- информационный блок
		
		case "":
			dialog.text = "";
			link.l1 = "Bonjour, mon ami.";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "Bonjour, mon ami.";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "Bonjour, étranger.";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
