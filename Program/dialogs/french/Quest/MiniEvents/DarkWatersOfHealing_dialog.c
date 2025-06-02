void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Que voulez-vous ?";
			link.l1 = "Rien.";
			link.l1.go = "exit";
		break;

		case "Tomas":
			dialog.text = ""+TimeGreeting()+" ! Qu'est-ce qui vous amène chez moi ?";
			link.l1 = "Je suis le capitaine "+GetFullName(pchar)+". Je viens à la demande de la gitane. Elle ne comprend pas pourquoi vous avez rejeté son aide et souhaite en connaître la raison. Êtes-vous vraiment en position de refuser la moindre chance d'aider ?";
			link.l1.go = "Tomas_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Tomas_1":
			dialog.text = "Oh, capitaine... Comprenez que j'ai dû refuser, mais ce n'était pas de mon plein gré. Croyez-moi, je donnerais tout pour qu'Esther guérisse.";
			link.l1 = "Qu'est-ce qui a bien pu vous pousser à rejeter une aide dont vous avez tant besoin ?";
			link.l1.go = "Tomas_2";
		break;

		case "Tomas_2":
			dialog.text = "Voyez-vous, notre famille a toujours été pieuse. Après la mort de ma femme, Olivia, seule la foi me maintient debout. Quand la gitane a proposé son aide, j'ai accepté – pour sauver ma fille. Mais... notre pasteur l'a appris.";
			link.l1 = "Laissez-moi deviner : il est opposé à ce genre de services ?";
			link.l1.go = "Tomas_3";
		break;

		case "Tomas_3":
			dialog.text = "Exactement. Il m’a convaincu que seule la prière et la volonté du Seigneur peuvent guérir ma fille. Et si je m’écarte de cette voie — en acceptant l’aide d’une ‘sorcière’ — il m’a menacé d’excommunication. Vous comprenez ? L’excommunication !";
			link.l1 = "Alors, la santé d’Esther dépend uniquement des paroles du pasteur ?";
			link.l1.go = "Tomas_4";
		break;

		case "Tomas_4":
			dialog.text = "Ma fille et moi vivons par et pour l’Église. C’est tout ce que nous avons. Si la gitane échoue, je perdrai non seulement ma fille, mais aussi ma place dans ce monde. Les gens se détourneront, l’Église nous rejettera. Esther et moi serons complètement seuls.";
			link.l1 = "Et si le pasteur donnait son accord ? Laisseriez-vous alors la gitane essayer ?";
			link.l1.go = "Tomas_5";
		break;

		case "Tomas_5":
			dialog.text = "Oui. Si l’Église bénissait ses actes... alors je lui ferais confiance. Je suis prêt à essayer tout ce qui peut aider.";
			link.l1 = "Je vois. Très bien, Thomas, je vais vous aider. Je parlerai à votre pasteur. Peut-être que je parviendrai à le convaincre.";
			link.l1.go = "Tomas_6";
		break;

		case "Tomas_6":
			dialog.text = "Vous... vous êtes vraiment prêt à nous aider ? Capitaine, je prierai pour votre succès. Mais sachez-le... notre pasteur est un homme obstiné et très attaché à ses principes. Le convaincre ne sera pas facile.";
			link.l1 = "Les principes peuvent céder face à des arguments convaincants. Attendez, je reviendrai bientôt.";
			link.l1.go = "Tomas_7";
		break;
		
		case "Tomas_7":
			DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("DWH", "3");
			pchar.questTemp.DWH_pastor = true;
			AddLandQuestMark(characterFromId("SentJons_Priest"), "questmarkmain");
		break;
		
		case "Tomas_11":
			dialog.text = "...";
			link.l1 = "Thomas, j'ai réussi à convaincre le pasteur.";
			link.l1.go = "Tomas_12";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_12":
			dialog.text = "Vraiment ? Incroyable ! Alors, invitons la gitane au plus vite.";
			link.l1 = "Nous le ferons, bien sûr, mais il y a un détail. Le pasteur espère que tout cela ne troublera pas votre foi, et il attend de vous un repentir sincère ainsi que de bonnes actions. La première pourrait être l'achat d'une nouvelle cloche pour la paroisse.";
			link.l1.go = "Tomas_13";
		break;

		case "Tomas_13":
			dialog.text = "Oh, capitaine... Une cloche coûte une fortune. Je devrai peut-être me séparer de certains bijoux de feu mon épouse. Mais pour Esther, je suis prêt à tout donner, même davantage. Bien sûr, je prierai le Seigneur pour son pardon. Je vais aller chez le forgeron, passer commande, et retrouver la gitane.\nJe vous prie de dire au pasteur que la cloche sera là bientôt. Je la chercherai jusqu’en enfer s’il le faut.";
			link.l1 = "Très bien, Thomas.";
			link.l1.go = "Tomas_14";
		break;

		case "Tomas_14":
			DialogExit();

			LAi_SetActorType(npchar);
			pchar.questTemp.DWH_pastor_PrinesDengi = true;
			AddLandQuestMark(characterFromId("SentJons_Priest"), "questmarkmain");
		break;

		case "Tomas_15":
			dialog.text = "...";
			link.l1 = "J’ai transmis vos paroles au pasteur. Il ne fera plus obstacle, vous pouvez commencer.";
			link.l1.go = "Tomas_16";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_16":
			dialog.text = "Merci, capitaine, pour tout ce que vous avez fait ! Prenez ces cinquante doublons. C’est peu, je le sais, mais c’est tout ce que j’ai pour le moment...";
			link.l1 = "Allons donc ! Je ne vous ai pas aidé pour de l'argent. Tout est prêt maintenant pour... hmm... le traitement ?";
			link.l1.go = "Tomas_16_1";
			link.l2 = "Bon, puisque vous insistez... Y a-t-il autre chose que je puisse faire ?";
			link.l2.go = "Tomas_16_2";
		break;
		
		case "Tomas_16_1":
			StartInstantDialog("DWH_gypsy", "gypsy_1", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.questTemp.DWH_GoodChoice = true;
		break;
		
		case "Tomas_16_2":
			StartInstantDialog("DWH_gypsy", "gypsy_1", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			AddItems(pchar, "gold_dublon", 50);
		break;
		
		case "gypsy_1":
			dialog.text = "Pour préparer la potion qui rendra la santé à l'enfant, j'ai besoin de mangarosa – une plante rare qui pousse dans des endroits où les humains mettent rarement les pieds. Je connais une grotte à l'extérieur de la ville où rôdent souvent... des individus peu recommandables. Ils gaspillent la mangarosa en la fumant, sans comprendre sa puissance. Rends-moi service, "+GetSexPhrase("Fauconnet","Petite colombe")+", trouve-moi de la mangarosa, sans elle rien ne marchera.";
			if (CheckAttribute(pchar, "questTemp.Mangarosa"))
			{
				link.l1 = "Mangarosa ? Je connais cette plante.";
				link.l1.go = "gypsy_VD_manga_1";
			}
			else
			{
				link.l1 = "À quoi ressemble cette plante ?";
				link.l1.go = "gypsy_VD_no_manga";
			}
		break;

		case "gypsy_VD_no_manga":
			dialog.text = "C'est une plante assez haute avec des feuilles dentelées et un parfum agréable et enivrant. Tu ne la confondras avec rien d'autre, c'est certain.";
			link.l1 = "Très bien, je vais trouver cette mangarosa.";
			link.l1.go = "gypsy_2";
		break;

		case "gypsy_VD_manga_1":
			dialog.text = "Tu la mélanges aussi avec du tabac ?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "amelia")
			{
				link.l1 = "Non, pas du tout ! Il y a une guérisseuse nommée Amelia. Elle prépare avec cette plante des potions qui, sans exagérer, peuvent vraiment transformer l'esprit.";
				link.l1.go = "gypsy_VD_manga_1_2";
			}
			else
			{
				link.l1 = "Non, mais il m'est arrivé de tenir de la mangarosa entre les mains.";
				link.l1.go = "gypsy_VD_manga_2";
			}
		break;

		case "gypsy_VD_manga_1_2":
			dialog.text = "Alors tu connais Amelia ? Eh bien, "+GetSexPhrase("Fauconnet","Petite colombe")+", bientôt tu me feras concurrence. Mais ce n’est pas le moment d’en parler. Va, apporte-moi la mangarosa, et je préparerai tout ce qu’il faut.";
			link.l1 = "J'y vais tout de suite.";
			link.l1.go = "gypsy_2";
			AddCharacterExpToSkill(pchar, "Fortune", 200);
		break;

		case "gypsy_VD_manga_2":
			dialog.text = "Je vois bien que tu n’es pas ordinaire, "+GetSexPhrase("Fauconnet","Petite colombe")+". Tes connaissances sont grandes, ton esprit aussi tranchant qu’un couteau ! Tu n’as pas peur d’explorer l’inconnu, tu cherches à comprendre ce qui échappe aux autres. Thomas a de la chance que tu sois là pour l’aider. Va maintenant, rapporte-moi la mangarosa, et je guérirai la petite fille.";
			link.l1 = "...";
			link.l1.go = "gypsy_2";
		break;
		
		case "gypsy_2":
			DialogExit();
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			
			AddQuestRecord("DWH", "5");
			
			// поход за мангаросой
			LAi_LocationDisableOfficersGen("Antigua_Grot", true);
			locations[FindLocation("Antigua_Grot")].DisableEncounters = true;
			PChar.quest.DWH_Grot.win_condition.l1 = "location";
			PChar.quest.DWH_Grot.win_condition.l1.location = "Antigua_Grot";
			PChar.quest.DWH_Grot.function = "DWH_Grot";
		break;
		
		case "Bandit_1":
			dialog.text = "Ha-ha. Je te dis, Marc, c’est un crétin. Il ne ferme même pas sa porte à clé.";
			link.l1 = "Et tu es sûr que sa poulette ne traîne pas à la maison ?";
			link.l1.go = "Bandit_2";

			locCameraSleep(true);
			sld = CharacterFromID("DWH_Bandit_1");
			CharacterTurnToLoc(sld, "goto", "ass4");
			sld = CharacterFromID("DWH_Bandit_2");
			CharacterTurnToLoc(sld, "goto", "ass2");
		break;

		case "Bandit_2":
			DialogExit();

			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "", -1);
			DoQuestFunctionDelay("DWH_Grot_2", 4.0);
		break;

		case "Bandit_3":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "Regardez-moi ça, du poisson frais dans nos filets ! Allez, ne reste pas planté là. Vide tes poches, et plus vite que ça, pendant qu’on est encore gentils.";
			link.l1 = "Doucement, petits bandits. Je viens pour affaires. C’est "+sld.name+" qui m’envoie. J’ai besoin de mangarosa.";
			link.l1.go = "Bandit_4";

			locCameraSleep(false);
			locCameraFromToPos(3.39, 1.16, -1.80, true, 3.62, -0.50, 3.63);
			sld = CharacterFromID("DWH_Bandit_2");
			CharacterTurnToLoc(sld, "goto", "goto2");
		break;

		case "Bandit_4":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "Tu dis "+sld.name+" ? Très bien, on a de la mangarosa. File dix doublons d’or et elle est à toi.";
			if (PCharDublonsTotal() >= 10)
			{
				link.l1 = "Tiens.";
				link.l1.go = "Bandit_5";
			}
			link.l2 = "De l’argent ? Pourquoi faire ? Je ne donne pas l’aumône. Mais je peux vous donner deux livres d’acier dans les côtes, ça oui !";
			link.l2.go = "Bandit_7";
		break;

		case "Bandit_5":
			dialog.text = "Très bien, voilà ta mangarosa. Et souviens-toi, tu ne nous as jamais vus.";
			link.l1 = "Heh. T’avais pas besoin de préciser.";
			link.l1.go = "Bandit_6";
			GiveItem2Character(PChar, "cannabis7");
			RemoveDublonsFromPCharTotal(10);
		break;
		
		case "Bandit_6":
			DialogExit();
			
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			LAi_LocationDisableOfficersGen("Antigua_Grot", false);
			locations[FindLocation("Antigua_Grot")].DisableEncounters = false;
			
			if (CheckAttribute(pchar, "questTemp.DWH_GoodChoice")) SetFunctionLocatorCondition("DWH_VorovstvoSunduk", "Antigua_Grot", "box", "box1", false)
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_3";
			AddLandQuestMark(sld, "questmarkmain");
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("DWH_Bandit_"+i);
				LAi_CharacterDisableDialog(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "DWH_Podkreplenie");
			}
		break;
		
		case "Bandit_7":
			DialogExit();
			
			chrDisableReloadToLocation = true;
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			GiveItem2Character(NPChar, "cannabis7");
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("DWH_Bandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=3; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DWH_Bandit_"+i, "citiz_48", "man", "man", sti(pchar.rank), PIRATE, 0, true, "pirate"));
				if (i==4) sld.model = "citiz_49";
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, "Antigua_Grot", "reload", "reload1");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "DWH_Grot_4");
		break;
		
		case "gypsy_3":
			if (CheckCharacterItem(PChar, "cannabis7"))
			{
				dialog.text = "...";
				link.l1 = "Regarde, "+npchar.name+", est-ce bien la plante que tu cherchais ?";
				link.l1.go = "gypsy_4";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Tu as apporté ce que j’ai demandé ?";
				link.l1 = "Pas encore, je m’en occupe.";
				link.l1.go = "exit";
				NextDiag.TempNode = "gypsy_3";
			}
		break;

		case "gypsy_4":
			dialog.text = "Oui, c’est bien elle. Maintenant j’ai tout ce qu’il faut, je peux commencer.";
			link.l1 = "...";
			link.l1.go = "gypsy_5";
			TakeItemFromCharacter(pchar, "cannabis7");
		break;

		case "gypsy_5":
			StartInstantDialog("DWH_Tomas", "Tomas_17", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
		break;

		case "Tomas_17":
			dialog.text = "Allons-y vite, ne perdons pas de temps.";
			link.l1 = "...";
			link.l1.go = "Tomas_18";
			CharacterTurnByChr(npchar, CharacterFromID("DWH_gypsy"));
		break;

		case "Tomas_18":
			dialog.text = "Capitaine, si cela ne vous dérange pas, nous nous reverrons plus tard. À présent commence la partie la plus importante... du traitement.";
			link.l1 = "Bien sûr, Thomas. J’espère que votre fille se rétablira vite.";
			link.l1.go = "Tomas_19";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Tomas_19":
			DialogExit();
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", true);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", true);
			
			AddQuestRecord("DWH", "6");
			SetTimerFunction("DWH_Vizdorovela", 0, 0, 30);
		break;
		
		case "gypsy_6":	// если не прошли проверку ВД у священника
			dialog.text = "...";
			link.l1 = ""+npchar.name+", Thomas ne t'a pas chassée de son propre gré. Le prêtre l'a menacé d'excommunication s'il acceptait ton aide.";
			link.l1.go = "gypsy_7";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_7":
			dialog.text = "J’ai tout de suite compris, "+GetSexPhrase("mon chéri","belle")+", qu’il m’a refusé cela le cœur lourd.";
			link.l1 = "Y a-t-il un moyen de l'aider sans que l'église ne le prenne comme un défi ?";
			link.l1.go = "gypsy_8";
		break;

		case "gypsy_8":
			dialog.text = "Oh, "+GetSexPhrase("mon chéri","belle")+", ce n’est pas une mince affaire, mais les chemins me sont connus, je sais quoi faire. Seulement, sans ton aide, je n’y arriverai pas, tu comprends.";
			link.l1 = "Bien sûr, tu peux compter sur moi.";
			link.l1.go = "gypsy_10";
			link.l2 = "Je suis désolé, sourcils noirs, mais je n'ai absolument pas le temps de m'occuper de ça. J'ai fait tout ce qui était en mon pouvoir. Maintenant, je dois m'occuper de mes propres affaires.";
			link.l2.go = "gypsy_9";
		break;

		case "gypsy_9":
			DialogExit();
			CloseQuestHeader("DWH");

			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;

			sld = CharacterFromID("DWH_Tomas");
			sld.lifeday = 0;
		break;

		case "gypsy_10":
			dialog.text = "Voici donc ce dont j'ai besoin : un objet qui appartient à la petite fille, deux tiges de datura, une tige d'ipécacuana, et une de verveine. Si tu m'apportes tout cela, je pourrai préparer une infusion à base de plantes pour elle.";
			link.l1 = "Très bien, je vais me procurer tout ce dont nous avons besoin.";
			link.l1.go = "gypsy_11";
		break;

		case "gypsy_11":
			DialogExit();
			AddQuestRecord("DWH", "7");

			LAi_CharacterDisableDialog(npchar);

			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_21";
			AddLandQuestMark(sld, "questmarkmain");
		break;

		case "Tomas_21":
			dialog.text = "...";
			link.l1 = "Thomas, malheureusement, le prêtre n'a pas écouté mes paroles. Mais la gitane et moi pouvons vous aider. J'ai besoin...";
			link.l1.go = "Tomas_22";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_22":
			dialog.text = "Suggérez-vous que j'aille à l'encontre de l'église ?";
			link.l1 = "Nous ferons tout discrètement, personne ne le saura. Bientôt, votre fille pourra à nouveau profiter de la vie et se promener librement dans la ville, comme il convient à une jeune demoiselle.";
			link.l1.go = "Tomas_23";
			link.l2 = "Bon sang, Thomas Morrison, voulez-vous que votre fille guérisse ou vous contentez-vous de vous cacher derrière de belles paroles ?";
			link.l2.go = "Tomas_24";
		break;

		case "Tomas_23":
			dialog.text = "Très bien, je suis d'accord. Mais s'il vous plaît, agissez avec précaution. Je ne veux pas de rumeurs inutiles ni d'ennuis.";
			link.l1 = "Absolument. Donc, j'ai besoin d'un objet personnel de votre fille. Quelque chose auquel elle est attachée.";
			link.l1.go = "Tomas_25";
			AddCharacterExpToSkill(pchar, "Sneak", 200);
		break;

		case "Tomas_24":
			dialog.text = "Très bien, je suis d'accord. Mais s'il vous plaît, agissez avec précaution. Je ne veux pas de rumeurs inutiles ni d'ennuis.";
			link.l1 = "Absolument. Donc, j'ai besoin d'un objet personnel de votre fille. Quelque chose auquel elle est attachée.";
			link.l1.go = "Tomas_25";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "Tomas_25":
			dialog.text = "Hmm... Oui ! Je sais ce qui conviendra. Attendez-moi ici, je reviens tout de suite.";
			link.l1 = "J'attends...";
			link.l1.go = "Tomas_26";
		break;
		
		case "Tomas_26":
			DialogExit();
			SetLaunchFrameFormParam("Quelques minutes plus tard...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("DWH_TomasGovotitAgain", 0.0);
			LaunchFrameForm();
		break;

		case "Tomas_27":
			dialog.text = "Voici. Ce sont des perles de jade. Esther ne les enlevait jamais, elles lui sont très chères.";
			link.l1 = "Excellent. Maintenant, vous n'avez plus qu'à attendre. À bientôt, Thomas.";
			link.l1.go = "Tomas_28";
			GiveItem2Character(PChar, "jewelry49");
		break;

		case "Tomas_28":
			DialogExit();
			AddQuestRecord("DWH", "8");

			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_21";
			AddLandQuestMark(sld, "questmarkmain");
		break;

		case "gypsy_21":
			dialog.text = "Tu m'as apporté ce que j'avais demandé ?";
			if (GetCharacterItem(pchar, "cannabis1") >= 2 && GetCharacterItem(pchar, "cannabis4") >= 1 && GetCharacterItem(pchar, "cannabis3") >= 1)
			{
				link.l1 = "J'ai tout rassemblé.";
				link.l1.go = "gypsy_22";
			}
			link.l2 = "Rappelle-moi ce qu'il faut apporter.";
			link.l2.go = "gypsy_napomni";
		break;

		case "gypsy_napomni":
			dialog.text = "Voici ce dont j'ai besoin : un objet qui appartient à la petite fille, deux tiges de datura, une tige d'ipécacuana, et une de verveine. Si tu m'apportes tout cela, je pourrai préparer une infusion à base de plantes pour elle.";
			link.l1 = "Très bien, je vais me procurer tout ce dont nous avons besoin.";
			link.l1.go = "gypsy_napomni_2";
		break;

		case "gypsy_napomni_2":
			DialogExit();
			NextDiag.TempNode = "gypsy_21";
		break;

		case "gypsy_22":
			dialog.text = "Excellent. Maintenant je peux préparer une potion de guérison pour la petite. Elle sera prête au plus tôt demain matin. Tu pourras me trouver comme d'habitude, dans les rues de la ville.";
			link.l1 = "Très bien, à bientôt.";
			link.l1.go = "gypsy_23";
			DelLandQuestMark(npchar);
			RemoveItems(pchar, "cannabis1", 2);
			RemoveItems(pchar, "cannabis4", 1);
			RemoveItems(pchar, "cannabis3", 1);
			RemoveItems(pchar, "jewelry49", 1);
		break;

		case "gypsy_23":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("DWH", "11");
			SetTimerFunction("DWH_GypsyPrigotovilaZelie", 0, 0, 1);
		break;

		case "gypsy_31":
			dialog.text = "...";
			link.l1 = "Alors, "+npchar.name+", ta potion est-elle prête ?";
			link.l1.go = "gypsy_32";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_32":
			dialog.text = "Le voilà, "+GetSexPhrase("mon chéri","belle")+". Que la petite fille mette ces perles et boive le contenu de la fiole jusqu'au fond. Dans un mois tout au plus, elle sera complètement guérie.";
			link.l1 = "Je vais l'apporter à Thomas immédiatement. Adieu, sourcils noirs.";
			link.l1.go = "gypsy_33";
			GiveItem2Character(PChar, "quest_potion");
			GiveItem2Character(PChar, "jewelry49");
		break;
		
		case "gypsy_33":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_31";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Tomas_31":
			if (CheckCharacterItem(PChar, "quest_potion"))
			{
				dialog.text = "...";
				link.l1 = "Thomas, tout est prêt. Esther doit mettre ces perles et boire la fiole d'une seule traite.";
				link.l1.go = "Tomas_32";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Tomas_31";
			}
		break;

		case "Tomas_32":
			dialog.text = "Merci, "+pchar.name+" ! Pardonnez-moi, je ne veux pas perdre une minute...";
			link.l1 = "Bien sûr, bien sûr.";
			link.l1.go = "Tomas_33";
			TakeItemFromCharacter(pchar, "quest_potion");
		break;

		case "Tomas_33":
			DialogExit();

			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);

			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", true);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", true);

			AddQuestRecord("DWH", "6");
			SetTimerFunction("DWH_Vizdorovela", 0, 0, 30);
		break;

		case "Tomas_41":
			dialog.text = "Bonjour, "+pchar.name+" ! Ma Esther est guérie ! Elle est en parfaite santé et se trouve à l'église, priant notre Seigneur Dieu, le remerciant de vous avoir envoyé, vous et la gitane !";
			link.l1 = "Thomas, je suis ravi que tout ait fonctionné ! Prenez soin de la petite, elle a maintenant une longue et heureuse vie devant elle.";
			link.l1.go = "Tomas_42";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_42":
			dialog.text = "Prenez ces trois cents doublons. Malheureusement, je ne peux pas offrir plus, car j'ai dû m'endetter pour réunir cette somme. Mais sachez qu'aucun mot et aucun or ne peuvent exprimer la gratitude que je ressens envers vous, Capitaine. Vous ne m'avez pas seulement libéré de la peur pour sa vie, mais vous avez aussi donné à notre famille une chance pour l'avenir. Je vous serai toujours reconnaissant !";
			link.l1 = "Merci ! Trois cents doublons, c’est une récompense très généreuse, alors ne vous inquiétez pas – vous m’avez remercié plus que suffisamment !";
			link.l1.go = "Tomas_43";
			link.l2 = "Je ne prendrai pas votre argent, Thomas. N'insistez pas ! J'ai voulu vous aider par bonté. Achetez plutôt une belle robe à la jeune Esther, elle le mérite.";
			link.l2.go = "Tomas_46";
		break;

		case "Tomas_43":
			dialog.text = ""+pchar.name+", venez nous rendre visite à tout moment. Vous serez toujours le bienvenu chez nous. Et aussi, parlez à la gitane, elle voulait vous voir.";
			link.l1 = "Ce sera un honneur ! Maintenant, excusez-moi, Thomas. Les affaires m'appellent.";
			link.l1.go = "Tomas_44";
			AddItems(pchar, "gold_dublon", 300);
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;

		case "Tomas_44":
			dialog.text = "Bien sûr, bien sûr. Que Dieu soit avec vous, "+GetFullName(pchar)+" !";
			link.l1 = "Au revoir.";
			link.l1.go = "Tomas_45";
		break;
		
		case "Tomas_45":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", false);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", false);
			SetFunctionExitFromLocationCondition("DWH_Vizdorovela_3", PChar.location, false);
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			NextDiag.CurrentNode = "Tomas_51";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_41";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Tomas_46":
			dialog.text = "Vous êtes une personne des plus nobles, "+GetFullName(pchar)+" ! Que la Vierge Marie soit avec vous ! Venez nous voir, vous êtes toujours un invité bienvenu dans notre maison. Et aussi, "+pchar.name+", parlez à la gitane, elle voulait vous voir.";
			link.l1 = "Très certainement ! Maintenant, excusez-moi. Les affaires m'appellent.";
			link.l1.go = "Tomas_47";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;

		case "Tomas_47":
			DialogExit();

			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", false);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", false);
			SetFunctionExitFromLocationCondition("DWH_Vizdorovela_3", PChar.location, false);

			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			NextDiag.CurrentNode = "Tomas_51";

			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\\MiniEvents\\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_44";
			AddLandQuestMark(sld, "questmarkmain");

			pchar.questTemp.DWH_QuestCompleted = true;
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1;

			AddSimpleRumourCity("Avez-vous entendu ? "+GetFullName(pchar)+" a procuré un remède pour la fille de Thomas Morrison qui a miraculeusement rétabli la santé de la pauvre enfant !", "SentJons", 10, 1, "");
			AddSimpleRumourCity("Thomas Morrison allume une bougie dans la paroisse chaque jour pour la santé de "+GetFullName(pchar)+". On dit qu’il a sauvé sa fille d’une longue maladie.", "SentJons", 10, 1, "");
			AddSimpleRumourCity("Esther Morrison s’est épanouie sous nos yeux. Comme si elle n’avait jamais été malade. Personne ne peut vraiment expliquer ce qui a fait reculer la maladie.", "SentJons", 10, 1, "");
		break;

		case "gypsy_41":
			dialog.text = "Te voilà, "+GetSexPhrase("Fauconnet","Petite colombe")+" ! Je savais que tu reviendrais. Grâce à tes efforts, la petite s'est rétablie et virevolte maintenant comme une colombe. Toute la ville s’émerveille d’elle.";
			link.l1 = "Allons, sourcils noirs, ce n’était pas uniquement grâce à moi, ne me donne pas tout le mérite. C’est ta potion qui l’a remise sur pied, alors ne minimise pas ton mérite.";
			link.l1.go = "gypsy_42";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_42":
			dialog.text = "Tu as un bon cœur, "+GetSexPhrase("Fauconnet","Petite colombe")+", et l’esprit vif ! Tu es destiné à de grandes choses – voilà ma prophétie.";
			link.l1 = "Héhé... eh bien, merci, "+npchar.name+".";
			link.l1.go = "gypsy_43";
		break;
		
		case "gypsy_43": // плохой вариант
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("DWH", "9");
			CloseQuestHeader("DWH");
		break;
		
		case "gypsy_44":
			dialog.text = "Te voilà, "+GetSexPhrase("Fauconnet","Petite colombe")+" ! Je savais que tu réapparaîtrais ici. Grâce à tes efforts, la petite s'est rétablie et volette maintenant comme une colombe. Toute la ville l'admire.";
			link.l1 = "Allons, allons, c'est toi qui as sauvé la petite, et tu veux que je prenne tout le mérite ? Ça ne marchera pas comme ça ! C'est toi qui as préparé la potion, c'est toi qui l'as remise sur pied, c'est à toi de recevoir la gloire.";
			link.l1.go = "gypsy_45";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_45":
			dialog.text = "Tu as un bon cœur, "+GetSexPhrase("Fauconnet","Petite colombe")+", et une âme noble. J'ai un cadeau pour toi - un que n'importe quel capitaine apprécierait. Tiens. Maintenant, les rats sur ton navire n'auront ni bonheur ni paix !";
			link.l1 = "Un cadeau ? C'est inattendu !";
			link.l1.go = "gypsy_46";
			GiveItem2Character(PChar, "rat_poison");
		break;

		case "gypsy_46":
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				dialog.text = "Ton âme est pure, je vois que tu ne brûleras pas la mangarosa pour un plaisir momentané. Si tu as besoin d’elle en urgence, viens me voir, "+GetSexPhrase("Fauconnet","Petite colombe")+" Cinq tiges te coûteront deux cents doublons\nCette herbe est capricieuse, tu le sais, tout le monde ne peut pas la trouver. Alors ne me presse pas - ne demande pas plus d'une fois par mois, de toute façon je ne pourrai pas l'obtenir.";
			}
			else
			{
				dialog.text = "Ton âme est lumineuse, je vois que tu n'es pas bête, tu comprends les herbes pas pire que certaines guérisseuses. Tu peux trouver beaucoup de choses, bien que la chance ne sourie pas toujours. Il y a une plante rare que tout le monde ne peut pas trouver. Elle s'appelle mangarosa. Si jamais tu en as besoin, viens me voir, "+GetSexPhrase("Fauconnet","Petite colombe")+". Je te procurerai cinq tiges, mais je ne les donnerai pas gratuitement - je prendrai deux cents doublons\nMais cette herbe est capricieuse, alors ne me presse pas. Ne demande pas plus d'une fois par mois - même si tu étales toutes les cartes du destin, je ne l'obtiendrai pas plus tôt.";
			}
			link.l1 = "Eh bien, merci, "+npchar.name+".";
			link.l1.go = "gypsy_47";
		break;
		
		case "gypsy_47": // хороший вариант
			DialogExit();
			NextDiag.CurrentNode = "gypsy_Mangarosa";
			
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("DWH", "10");
			CloseQuestHeader("DWH");
			AddQuestRecordInfo("Useful_Acquaintances", "1");
			
			SetTimerFunction("DWH_Mangarosa", 0, 0, 30);
		break;
		
		case "Tomas_51":
			dialog.text = "Capitaine, je ne cesse de penser – ce doit être le Seigneur lui-même qui vous a guidé ici au bon moment ! Vous avez sauvé ma fille, et je ne l’oublierai jamais.";
			link.l1 = "Peut-être, Thomas. Les voies du Seigneur sont impénétrables.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tomas_52";
			SetTimerFunction("DWH_Tomas_HelloAgain", 0, 0, 1);
		break;

		case "Tomas_52":
			dialog.text = "Voulez-vous du vin, Capitaine ? J’ai quelque chose de spécial pour mes invités de marque.";
			link.l1 = "Merci, Thomas, mais malheureusement, je dois partir.";
			link.l1.go = "exit";
		break;

		case "gypsy_Mangarosa":
			dialog.text = "Que veux-tu, mon faucon ?";
			if (CheckAttribute(pchar, "questTemp.DWH_Mangarosa"))
			{
				link.l1 = "Dis-moi, sourcils noirs, aurais-tu de la mangarosa pour moi ?";
				link.l1.go = "gypsy_Mangarosa_1";
			}
			link.l2 = "Je voulais juste te saluer. Je dois y aller !";
			link.l2.go = "exit";
			NextDiag.TempNode = "gypsy_Mangarosa";
		break;

		case "gypsy_Mangarosa_1":
			dialog.text = "Qui d’autre que moi, "+GetSexPhrase("mon chéri","belle")+", te procurerait une telle rareté ? Deux cents doublons – et elle est à toi, cinq tiges, pas plus, pas moins.";
			if (PCharDublonsTotal() >= 300)
			{
				link.l1 = "Tiens, prends tes doublons.";
				link.l1.go = "gypsy_Mangarosa_2";
			}
			link.l2 = "Zut. Je n’ai pas cette somme. Je reviendrai plus tard.";
			link.l2.go = "exit";
			NextDiag.TempNode = "gypsy_Mangarosa";
		break;

		case "gypsy_Mangarosa_2":
			dialog.text = "Là, c’est mieux, "+GetSexPhrase("Fauconnet","Petite colombe")+". Prends-la. Mais attention, ne la gaspille pas inutilement – tu sais bien que la mangarosa n’est pas une herbe ordinaire. Elle renferme une puissance que peu peuvent maîtriser.";
			link.l1 = "Ne t’inquiète pas, sourcils noirs, je trouverai un usage digne de sa puissance.";
			link.l1.go = "gypsy_Mangarosa_3";
			AddItems(pchar, "cannabis7", 5);
			RemoveDublonsFromPCharTotal(300);
		break;
		
		case "gypsy_Mangarosa_3":
			DialogExit();
			
			NextDiag.CurrentNode = "gypsy_Mangarosa";
			DeleteAttribute(pchar, "questTemp.DWH_Mangarosa");
			SetTimerFunction("DWH_Mangarosa", 0, 0, 30);
		break;
	}
}