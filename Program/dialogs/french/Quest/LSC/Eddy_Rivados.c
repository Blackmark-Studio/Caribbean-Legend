// лидер клана ривадос - Чёрный Эдди
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Que fais-tu sur le territoire des Rivados, homme blanc ?";
			link.l1 = "Je fais juste connaissance avec les habitants. Désolé si je vous ai dérangé.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Friend":
			dialog.text = "Je suis heureux d'accueillir un ami des Rivados et un homme bon également ! Chimiset m'a raconté ce que vous avez fait pour lui. Tous les Rivados, y compris moi, vous sont redevables maintenant. Permettez-moi de me présenter - Edward Black, aussi connu sous le nom de Black Eddie, le chef de la bande des Rivados.";
			link.l1 = " "+GetFullName(pchar)+". Bien que je pense que Chimiset vous a déjà parlé de moi. Il a promis de vous le dire...";
			link.l1.go = "Friend_1";
		break;
		
		case "Friend_1":
			dialog.text = "Et il l'a fait. Maintenant, vous pouvez visiter nos navires librement. Les gardes ne vous arrêteront pas et nous serons ravis de vous voir. Faites attention avec les Narvals, ils doivent déjà avoir découvert que vous avez sauvé Chimiset, et ils n'apprécieront pas, puisque nous sommes ennemis.";
			link.l1 = "Je vais y réfléchir. Merci pour l'accueil chaleureux, Eddie ! Maintenant, permets-moi de parler avec Chimiset.";
			link.l1.go = "Friend_2";
		break;
		
		case "Friend_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "LSC_EddyStay", -1);
			AddSimpleRumourCityTip("They say that you are a close friend of Black Eddie, the head of Rivados. How did you do this?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("Rivados claim you as their friend. How'd you do it?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that the Narwhals have a price on your head. Are you scared?", "LostShipsCity", 10, 1, "LSC", "");
		break;
		
		// --> информационный блок
		case "Total_info": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Frère blanc ? Vivant ? Je suis heureux ! Alors, les Narvals ont menti en disant à tout le monde que tu t'étais noyé...";
				link.l1 = "Je suis aussi heureux de te voir, Eddie. Les rumeurs de ma mort ont été grandement exagérées.";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "Ravi de te voir, "+pchar.name+"Des nouvelles?";
			if (!CheckAttribute(npchar, "quest.natan"))
			{
				link.l1 = "Eddie, connais-tu un homme du nom de Nathaniel Hawk? Il doit être ici, autant que je sache.";
				link.l1.go = "natan";
			}
			if (!CheckAttribute(npchar, "quest.rivados"))
			{
				link.l2 = "Parle-moi davantage de la bande des Rivados.";
				link.l2.go = "rivados";
			}
			link.l9 = "Rien de spécial, vraiment. Je voulais juste dire bonjour.";
			link.l9.go = "exit";
		break;
		
		case "natan":
			dialog.text = "Nathaniel Hawk ? Non, je ne connais pas cet homme. Il n'est ni sur les navires des Rivados, ni sur le territoire neutre. Je ne peux pas en dire autant de la bande des Narvals, nous ne les visitons pas.";
			link.l1 = "Je vois...";
			link.l1.go = "exit";
			npchar.quest.natan = "true";
			NextDiag.TempNode = "Total_info";
		break;
		
		case "rivados":
			dialog.text = "Le gang des Rivados a été fondé il y a de nombreuses années. C'était le tout premier clan dans cette Ville des Navires Abandonnés. Il y a plus de cinquante ans, l'expédition de l'amiral Betancourt a navigué ici depuis l'Afrique de l'Ouest avec plusieurs grands navires négriers. Les cales du Tartarus étaient remplies de centaines d'esclaves noirs destinés aux plantations des Caraïbes. Parmi ces esclaves se trouvait un homme nommé Pedro Rivados, quelques prêtres portugais lui avaient appris à lire et à écrire. Il a réussi à libérer quelques dizaines d'esclaves de leurs chaînes et a déclenché une mutinerie. Hélas, le reste des esclaves n'a pas réussi à le rejoindre. La révolte a été réprimée. Les négriers ont attaché Rivados main et pied et l'ont laissé dans la cale du navire pour périr de faim et de soif. Quelques jours plus tard, le temps s'est gâté et l'escadron de Betancourt a été balayé par une puissante tempête. Quelques jours plus tard, après avoir combattu les éléments, le 'San Augustine' et le 'Tartarus', les seuls deux navires encore intacts, se sont retrouvés coincés au milieu de cette Île. Beaucoup d'hommes sont morts pendant ces événements, noirs et blancs, mais beaucoup d'autres ont réussi à survivre. Les anciens esclaves ont commencé une nouvelle vie ensemble et se sont appelés les Rivados en l'honneur de Pedro Rivados, le libérateur.";
			link.l1 = "Une histoire très intéressante... Merci !";
			link.l1.go = "exit";
			npchar.quest.rivados = "true";
			NextDiag.TempNode = "Total_info";
		break;
		// <-- информационный блок
		
		case "capper":
			dialog.text = "Que cherches-tu sur les territoires des Rivados, homme blanc ?";
			link.l1 = "Mon nom est "+GetFullName(pchar)+" et je suis ici sur ordre de l'Amiral Dodson. Je dois parler à Eddie le Noir. Si je comprends bien, c'est vous.";
			link.l1.go = "capper_1";
		break;
		
		case "capper_1":
			dialog.text = "Oui, je suis Edward Black, aussi connu sous le nom de Black Eddie. Dis-moi, que veut l'amiral de moi ?";
			link.l1 = "Il y a un homme sur le 'Tartarus' nommé Chimiset. L'amiral est prêt à le libérer.";
			link.l1.go = "capper_2";
		break;
		
		case "capper_2":
			dialog.text = "C'est une très bonne nouvelle. Chimiset est notre guide spirituel, et tous les Rivados le regrettent. Mais je comprends que l'amiral veut quelque chose en échange de sa liberté, n'est-ce pas ?";
			link.l1 = "Rien. Il veut simplement le libérer en signe de bonne volonté. Mais il y a un problème...";
			link.l1.go = "capper_3";
		break;
		
		case "capper_3":
			dialog.text = "Continuez, homme blanc.";
			link.l1 = "L'ancien maître d'équipage de l'amiral, l'actuel geôlier Chad Kapper, a rejoint les Narvals, est devenu renégat et échappe maintenant au contrôle de l'amiral. Nous savons que Chad prévoit de tuer Chimiset. L'amiral ne veut pas que cela arrive. Nous vous proposons une opération conjointe pour éliminer le traître et libérer votre homme.";
			link.l1.go = "capper_4";
		break;
		
		case "capper_4":
			dialog.text = "Tes paroles sonnent un peu étranges, mais continue. Chimiset est-il en difficulté ?";
			link.l1 = "Oui. Chad prévoit de le tuer. Kapper va utiliser les Narvals pour prendre le contrôle de la Ville. Nous devons agir rapidement si nous voulons sauver Chimiset, car Chad ne soupçonne rien pour l'instant. L'Amiral a retiré tous les gardes du 'Tartarus', le passage est libre. Voici la clé qui ouvre la porte de la prison. Prenez-la.";
			link.l1.go = "capper_5";
		break;
		
		case "capper_5":
			RemoveItems(pchar, "key_capper", 1);
			dialog.text = "Bonjour, mon ami.";
			link.l1 = "Rassemble tes hommes, va au Tartarus et libère Chimiset. Toutes les cartes sont à toi.";
			link.l1.go = "capper_6";
		break;
		
		case "capper_6":
			dialog.text = "Ça sent le piège... Et s'il y a une embuscade ? Et si l'amiral a décidé d'abattre les Rivados ? Pourquoi ne s'occupe-t-il pas de Kapper lui-même ?";
			link.l1 = "Dodson a dit que tu te soucies de la vie de Chimiset... Il en a fait assez : voici la clé et les gardes sont partis. Tu n'as qu'à entrer, t'occuper de Chad et libérer ton homme. Tu as ma parole qu'il n'y a pas de piège. Oui, et une dernière chose : l'amiral veut la tête de Chad en échange de la vie et de la liberté de Chimiset. Avons-nous un accord ?";
			link.l1.go = "capper_7";
		break;
		
		case "capper_7":
			dialog.text = "La vie de Chimiset est d'une valeur inestimable pour les Rivados. Nous nous rendrons immédiatement sur le 'Tartarus'. Mais vous resterez ici comme notre otage. Et s'il y a une embuscade, vous affronterez la rage des Rivados !\nZikomo ! Reste près de la porte et surveille notre invité. Ne le laisse pas sortir. Je mènerai moi-même l'attaque sur le 'Tartarus' !";
			link.l1 = "Bonne chance, Eddie. Et souviens-toi : j'ai besoin de la tête de Chad Kapper !";
			link.l1.go = "capper_8";
		break;
		
		case "capper_8":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LSC_ZikomoNearDoor", 10.0);
			NextDiag.CurrentNode = "chimiset";
		break;
		
		case "chimiset":
			dialog.text = "Chimiset est libre ! Tu ne mentais pas, homme blanc, je suis prêt à te considérer comme un ami des Rivados !";
			link.l1 = "Je suis content. Est-ce que Chad Kapper est mort ?";
			link.l1.go = "chimiset_1";
		break;
		
		case "chimiset_1":
			dialog.text = "Je dois te demander pardon, ami blanc : tu as fait tout ce que tu pouvais pour nous, mais nous t'avons trahi... Je t'ai trahi ! Ce maudit Kapper s'est échappé. Il y avait deux Narvals avec lui. Nous les avons tués, mais le sale geôlier s'est enfui par la porte inférieure vers les territoires des Narvals.";
			link.l1 = "Merde... Tu ne savais pas qu'il y avait deux sorties du 'Tartare' ?";
			link.l1.go = "chimiset_2";
		break;
		
		case "chimiset_2":
			dialog.text = "Nous n'y avons pas pensé. Nous avons attaqué par l'entrée principale...";
			link.l1 = "Pitié. Je comptais sur sa tête. Dommage. Maintenant, il continuera à agir contre nous.";
			link.l1.go = "chimiset_3";
		break;
		
		case "chimiset_3":
			dialog.text = "J'admets ma culpabilité. Mais nous ne pouvions pas le suivre jusqu'aux navires hostiles. Vous aurez notre amitié et notre respect au lieu de la tête de Chad. Dorénavant, vous êtes autorisé à visiter notre territoire librement. La sagesse de Chimiset vous sera également bénéfique, parlez-lui si vous avez besoin de quoi que ce soit. Parlez-lui si vous avez besoin. Dites aussi à l'amiral mes assurances que j'ai apprécié son action.";
			link.l1 = "D'accord.";
			link.l1.go = "chimiset_4";
		break;
		
		case "chimiset_4":
			dialog.text = "Attends ! Nous avons perdu Chad, mais j'ai trouvé quelques papiers sur son bureau qu'il étudiait quand nous sommes arrivés. Les voici. Tu pourrais les trouver utiles, frère blanc.";
			link.l1 = "Ha ! Peut-être... Chad met une grande confiance dans le papier...";
			link.l1.go = "chimiset_5";
		break;
		
		case "chimiset_5":
			dialog.text = "Tu es toujours un invité bienvenu ici, ami blanc. Tous les Rivados en seront informés. Bonne chance !";
			link.l1 = "Toi aussi, Eddie...";
			link.l1.go = "chimiset_6";
		break;
		
		case "chimiset_6":
			DialogExit();
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "LSC_EddyStay", -1);
			sld = CharacterFromID("Zikomo");
            LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_warrior_DialogEnable(sld, true);
			GiveItem2Character(pchar, "letter_chad");
			ChangeItemDescribe("letter_chad", "itmdescr_letter_aeva");
			GiveItem2Character(pchar, "letter_chad_1");
			ChangeItemDescribe("letter_chad_1", "itmdescr_letter_axel");
			pchar.questTemp.LSC.rvd_friend = "true"; //флаг на проход по кораблям ривадос
			// // ривадосы не будут останавливать где просят пароль
			pchar.questTemp.Saga.SharkHunt = "dodson_whiskey"; // к Акуле
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "Chad_escape"; // ноду Акуле
			AddQuestRecord("SharkHunt", "33");
			LocatorReloadEnterDisable("LostShipsCity_town", "reload48", true); // закрыть вход к Дональду Гринспи
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
			AddSimpleRumourCityTip("Have you heard the latest news? The Rivados' insolence is out of control, they have attacked the admiral's prison and released their wizard!", "LostShipsCity", 3, 2, "LSC", "");
			AddSimpleRumourCityTip("Just think about it - those uppity Rivados dared to attack the 'Tartarus'! They say that the jailer, Chad Kapper, has escaped to the Narwhals...", "LostShipsCity", 3, 2, "LSC", "");
			AddSimpleRumourCityTip("This is the height of impudence, isn't it? Attacking a military facility of the admiral! Aye, looks like Black Eddie is getting stronger...", "LostShipsCity", 3, 2, "LSC", "");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
