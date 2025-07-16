// Jason общий диалог смотрителей кладбищ
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Cemetery\" + NPChar.City + "_cemetery.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
    int iTemp;
	string sTemp;
	bool ok;
    
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("La ville est en alerte. On dirait que c'est le moment pour moi aussi de prendre les armes...","N'êtes-vous pas poursuivis par toute la garde de la ville ?. À moi, soldats!!!","Vous ne trouverez pas d'abri ici. Mais vous trouverez quelques centimètres d'acier froid sous une côte !"),
					LinkRandPhrase("Que voulez-vous, scélérat ?! Un garde de la ville a déjà repéré votre trace, vous ne vous échapperez pas bien loin, "+GetSexPhrase("sale pirate !","canaille")+"!","Arrêtez ! "+GetSexPhrase("Sale tueur ! Garde !!!","Je n'ai pas peur de vous ! Bientôt vous serez pendu dans notre fort, il n'y a nulle part où se cacher...")));
				link.l1 = PCharRepPhrase(RandPhraseSimple("On dirait que vous en avez marre de vivre...","Et pourquoi ne voulez-vous pas vivre calmement, citoyens..."+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),
					RandPhraseSimple("Allez en enfer !","Il ne vous reste que quelques secondes à vivre dans ce monde..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if(!CheckAttribute(pchar, "questTemp.Lantern"))
			{
				dialog.text = "A-a-ah ! Ah, c'est vous... Qui êtes-vous ? Pourquoi êtes-vous venu au cimetière ?";
				link.l1 = "Mon nom est "+GetFullName(pchar)+". Qui êtes-vous et que faites-vous ici ? Et pourquoi avez-vous si peur ?";
				link.l1.go = "Lantern_01";
				npchar.quest.meeting = "1";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Lantern") && pchar.questTemp.Lantern == "ToCrypt")
			{
				dialog.text = "Alors, comment ça s'est passé ? Vous avez vérifié ? Vous me croyez maintenant ?";
				link.l1 = "Non, je ne suis pas encore descendu dans la crypte. Attendez encore un peu, je vais tout vérifier.";
				link.l1.go = "exit";
				break;
			}
			
			if(CheckAttribute(pchar, "questTemp.Lantern") && pchar.questTemp.Lantern == "ToKeeper")
			{
				dialog.text = "Alors ? Avez-vous jeté un coup d'oeil ? L'avez-vous vu ?";
				link.l1 = "Oui, bien sûr ! Vous aviez raison !";
				link.l1.go = "Lantern_10";
				link.l2 = "Ce n'était pas tout à fait ce que vous pensiez.";
				link.l2.go = "Lantern_14";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("Bonjour, matelot ! Je m'appelle "+GetFullName(npchar)+", et je suis la seule âme vivante ici. En fait, nous allons quand même tous mourir, ha-ha-ha !  Pourquoi êtes-vous venu ?","Bonjour ! Je n'ai pas vu d'homme vivant depuis longtemps... Permettez-moi de me présenter - "+GetFullName(npchar)+", et ce cimetière est mon dernier refuge. Apparemment, je serai enterré ici. Comment puis-je vous aider ?");
				link.l1 = "Bonjour, "+npchar.name+"! Mon nom est "+GetFullName(pchar)+", et je suis un capitaine. J'ai traversé la jungle et suis arrivé ici. J'ai pensé jeter un coup d'oeil à l'intérieur de cette maison confortable, pour voir qui n'a pas peur d'y vivre...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, mon vieil ami, capitaine "+GetFullName(pchar)+"! Entrez, entrez !";
				link.l1 = "Bonjour, mon ami ! Très heureux de vous voir. Ne voyez-vous pas des squelettes dansants la nuit et des morts avec des pièces de cuivre sur les yeux dans vos rêves ?";
				link.l1.go = "talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Et pourquoi devrais-je avoir peur, capitaine ? Il faut craindre les vivants, les morts ne mordent pas. Eh ! J'avais une vie bien différente autrefois, et maintenant je suis le gardien de ce cimetière. Je m'occupe des tombes. Et parfois je fais aussi du commerce de quelques babioles...";
			link.l1 = "Et quels sont les objets que vous vendez, dites-moi, s'il vous plaît ?";
			link.l1.go = "trade_info";
		break;
		
		case "talk":
			dialog.text = "Qu'est-ce qui vous amène à moi cette fois ?";
			link.l1 = "Montrez-moi ce que vous avez à vendre aujourd'hui.";
			link.l1.go = "trade";
			link.l2 = "Je voudrais vous poser une question...";
			link.l2.go = "quests";
			link.l3 = "Rien de particulier. Je suis simplement venu vous saluer.";
			link.l3.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = "J'ai beaucoup de temps libre, c'est pourquoi j'aime me promener dans la jungle pour ramasser des plantes utiles et des pierres précieuses. Ensuite, je les vends en ville. Elles ne coûtent pas bien cher, mais - c'est mieux que rien. Et je reçois une variété de choses de mes amis...";
			link.l1 = "Des amis ? Vous voulez dire que vous revendez ce que d'autres vous apportent ?";
			link.l1.go = "trade_info_1";
		break;
		
		case "trade_info_1":
			dialog.text = "O-ho-ho... Non, ils me donnent tout gratuitement. Qui peuvent être les amis d'un gardien de cimetière, si ce n'est les morts ?";
			link.l1 = "Hein... Vous dépouillez les cadavres ?";
			link.l1.go = "trade_info_2";
		break;
		
		case "trade_info_2":
			dialog.text = "Je ne vole pas; Je ne fais que prendre des objets à ceux qui n'en ont plus besoin. Beaucoup de personnes différentes sont enterrées ici, certaines inconnues et non originaires de nos terres. Le commandant apporte un cadavre de la ville et dit : 'Ceci est pour vous, "+npchar.name+", envoyez-le vers son dernier voyage.' Sans-abri, pirates pendus, bandits tués par des gardes, tous sont enterrés ici. Et le vieux "+npchar.name+" enterre leurs corps selon la coutume chrétienne.";
			link.l1 = "Je vois. Eh bien, l'argent c'est de l'argent, montrez-moi ce que vous avez.";
			link.l1.go = "trade";
			link.l2 = "Compris. Je dois y aller. J'ai été ravi de vous rencontrer.";
			link.l2.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
			NextDiag.TempNode = "First time";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Man_FackYou"://реакция на попытку залезть в сундук
			dialog.text = LinkRandPhrase("Et vous, "+GetFullName(pchar)+", êtes un voleur ! Gardes !!!","Qu'est-ce que c'est que ce bordel ! J'ai détourné le regard un instant et vous essayez déjà de voler ce qui m'appartient ! Attrapez le voleur !!!","Garde ! Au voleur !!! Attrapez le voleur !!!");
			link.l1 = "Oh merde !!!";
			link.l1.go = "fight";
		break;
		//belamour квест на получение фонаря -->
		case "Lantern_01":
			dialog.text = "Ouf, vous n'êtes donc qu'un simple voyageur... Je m'appelle "+GetFullName(npchar)+", je suis le gardien de cet endroit abandonné par Dieu.";
			link.l1 = "Pourquoi ce sentiment à l'égard du cimetière ? Au contraire, c'est de là que notre Seigneur emmène les justes après l'enterrement.";
			link.l1.go = "Lantern_02";
		break;
		
		case "Lantern_02":
			dialog.text = "Mais les iniques, apparemment, restent ici après l'enterrement ! Depuis quelques nuits, il y a du bruit qui vient de la crypte. Et les gémissements sont si glaçants que ça me donne des frissons... Il semble qu'une âme perdue ne peut pas trouver la paix ! Maintenant, je ne dors que pendant la journée - la nuit, je ne peux pas quitter mon poste ou fermer l'oeil...";
			link.l1 = "Des bruits ? Des gémissements ? Mais il n'y a personne là-bas sauf les défunts.";
			link.l1.go = "Lantern_03";
		break;
		
		case "Lantern_03":
			dialog.text = "C'est ce que je dis, vous savez ? Vous feriez mieux de partir d'ici avant que le fantôme ne vous sente... Sinon, vous ne pourrez pas dormir, comme moi.";
			link.l1 = "Hm, ouais, je pense qu'il vaut mieux que je quitte cet endroit.";
			link.l1.go = "Lantern_04";
			link.l2 = "Je peux peut-être vous aider ? Laissez-moi vérifier ces bruits étranges ce soir.";
			link.l2.go = "Lantern_05";
		break;
		
		case "Lantern_04":
			pchar.questTemp.Lantern = "NoLantern";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_05":
			dialog.text = "Vous avez perdu la tête ?! Je vois que vous avez une arme, mais comment comptez-vous combattre les morts-vivants avec ? Et si vous finissez par vous faire tuer là-bas, que se passera-t-il ? Le fantôme se promènera librement, et il pourrait même vous ressusciter en tant que serviteur !";
			link.l1 = "Eh bien, ce n'est que superstition...";
			link.l1.go = "Lantern_06";
		break;
		
		case "Lantern_06":
			dialog.text = "Quelle superstition ? Ce n'est pas la terre pieuse de l'Europe, bon sang... Les indigènes, ces gens au visage rouge, ils peuvent invoquer n'importe quoi - et maintenant nous devons vivre ici !";
			link.l1 = "Tout de même, laissez-moi essayer. J'attendrai la tombée de la nuit et je descendrai dans la crypte.";
			link.l1.go = "Lantern_07";
		break;
		
		case "Lantern_07":
			dialog.text = "Très bien, faites ce que vous voulez. Mais si vous ne revenez pas au lever du soleil, je fermerai tout, je barricaderai et je partirai d'ici moi-même ! Que ce soit en lavant le pont en tant que marin ou en transportant des caisses en tant que docker - Je ne reviendrai pas ici de toute façon !";
			link.l1 = "Calmez-vous... Tout ira bien.";
			link.l1.go = "Lantern_08";
		break;
		
		case "Lantern_08":
			dialog.text = "Attendez... Prenez cette lanterne. J'en ai une de rechange. Vous en aurez besoin là-bas. Il fait nuit noire !";
			link.l1 = "Merci, une lanterne sera en effet utile dans un endroit comme celui-là.";
			link.l1.go = "Lantern_09";
		break;
		
		case "Lantern_09":
			GiveItem2Character(pchar, "lantern_belt");
			Log_Info("'Lantern' received");
			PlaySound("interface\important_item.wav");
			if(npchar.city == "Charles") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Charles_CryptBig2", true);
			if(npchar.city == "Havana") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Havana_CryptBig2", true);
			if(npchar.city == "Villemstad" || npchar.city == "PortRoyal") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Common_CryptBig2", true);
			pchar.quest.NoiseCemetery_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NoiseCemetery_SeaExit.function = "NoiseCemetery_SeaExit";
			pchar.questTemp.Lantern = "ToCrypt";
			pchar.questTemp.Lantern.nation = npchar.nation;
			AddQuestRecord("NoiseCemetery", "1");
			AddQuestUserData("NoiseCemetery", "sCity", XI_ConvertString(loadedlocation.islandId)); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_10":
			dialog.text = "C'est vrai ? Qu'est-ce qu'il y avait ? Dites-moi !";
			link.l1 = "Il y avait l'esprit tourmenté d'une femme ! Heureusement, le prêtre local a béni ma lame pour châtier les malfaisants, et tout s'est arrangé. Cet esprit ne vous dérangera plus.";
			link.l1.go = "Lantern_11";
		break;
		
		case "Lantern_11":
			dialog.text = "Oh Seigneur, sauve nos âmes pécheresses ! Je vous avais prévenu ! Et vous ne m'avez pas cru !";
			link.l1 = "Oui, et je le regrette sincèrement. Mais maintenant tout va bien - j'ai aspergé cet endroit d'eau bénite, et aucun esprit n'osera sortir de sa tombe. Vous pouvez dormir tranquille.";
			link.l1.go = "Lantern_12";
		break;
		
		case "Lantern_12":
			dialog.text = "Merci beaucoup ! Vous n'avez pas idée de ce que cela signifie pour moi ! Tenez, prenez ceci. Ce n'est pas grand-chose, mais je ne peux pas vous laisser partir sans récompense.";
			link.l1 = "Merci, je ne peux pas refuser. Bonne chance à vous !";
			link.l1.go = "Lantern_13";
		break;
		
		case "Lantern_13":
			pchar.quest.NoiseCemetery_SeaExit.over = "yes";
			AddMoneyToCharacter(PChar, 1000);
			pchar.questTemp.Lantern = "Done";
			AddQuestRecord("NoiseCemetery", "3");
			CloseQuestHeader("NoiseCemetery");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_14":
			dialog.text = "Non ? Alors que diable... Je veux dire, pour l'amour de Dieu, que s'est-il passé ?";
			link.l1 = "Il n'y avait aucun fantôme. Un jeune couple a choisi cette crypte comme lieu pour leurs rendez-vous. Leurs parents sont contre cette union, alors ils cherchaient un endroit pour être seuls.";
			link.l1.go = "Lantern_15";
		break;
		
		case "Lantern_15":
			dialog.text = "Seuls ?.. Ah ces jeunes ! Qu'ils essaient seulement de revenir ici ! Je les chasserai tous les deux avec un fouet ou je les enfermerai dans la crypte pour qu'ils y restent !!!";
			link.l1 = "Ils ne reviendront plus ici. Je leur ai dit que leurs petites escapades avaient vraiment effrayé le gardien local. Ils ont l'intention de partir. Et d'ailleurs, la serrure de la porte est de toute façon cassée.";
			link.l1.go = "Lantern_16";
		break;
		
		case "Lantern_16":
			dialog.text = "Aucun problème, je la remplacerai. Mais si jamais je les attrape...";
			link.l1 = "Ne soyez pas si en colère. Nous avons tous eu cet âge. Ils ne sont pas venus ici parce que c'était le meilleur endroit pour faire des rencontres.";
			link.l1.go = "Lantern_17";
		break;
		
		case "Lantern_17":
			dialog.text = "C'est juste... Eh bien, que le Seigneur soit avec eux. Merci de ne pas avoir laissé un vieil homme en difficulté. Tenez, prenez ceci. Ce n'est pas grand-chose, mais je ne peux pas vous laisser partir sans récompense.";
			link.l1 = "Merci, je ne peux pas refuser. Bonne chance à vous !";
			link.l1.go = "Lantern_18";
		break;
		
		case "Lantern_18":
			DialogExit();
			pchar.quest.NoiseCemetery_SeaExit.over = "yes";
			AddMoneyToCharacter(PChar, 1000);
			pchar.questTemp.Lantern = "Done";
			AddQuestRecord("NoiseCemetery", "4");
			CloseQuestHeader("NoiseCemetery");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		// <-- квест на получение фонаря 
	}
}
