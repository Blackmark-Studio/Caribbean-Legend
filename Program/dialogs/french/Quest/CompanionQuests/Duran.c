void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
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
			dialog.text = "Que voulez-vous?";
			link.l1 = "Rien.";
			link.l1.go = "exit";
		break;
		
		case "SKD_DomAnri":
			dialog.text = "Bienvenue chez moi, messieurs. Que puis-je faire pour vous ?";
			link.l1 = "Levasseur vous envoie ses salutations, monsieur.";
			link.l1.go = "SKD_DomAnri_2";
			StartQuestMovie(true, false, true);
		break;
		
		case "SKD_DomAnri_2":
			dialog.text = "Alors c'est comme ça... Alicia ! Laissez-nous, s'il vous plaît. Ces messieurs ont des affaires avec moi.";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_2_1";
			CharacterTurnToLoc(npchar, "goto", "goto1");
		break;
		case "SKD_DomAnri_2_1":
			StartInstantDialog("SKD_Alisia", "SKD_DomAnri_3", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_3":
			dialog.text = "Mais...";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_3_1";
			CharacterTurnToLoc(npchar, "barmen", "stay");
		break;
		case "SKD_DomAnri_3_1":
			StartInstantDialog("SKD_Anri", "SKD_DomAnri_4", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_4":
			dialog.text = "Je t'adore, chérie. Alors vas-y !";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_5";
			CharacterTurnToLoc(npchar, "goto", "goto1");
		break;
		
		case "SKD_DomAnri_5":
			DialogExit();
			locCameraFromToPos(3.47, 2.41, 0.10, false, -1.05, 0.20, -0.07);
			
			sld = CharacterFromID("SKD_Anri");
			CharacterTurnByLoc(sld, "barmen", "stay");
			
			sld = CharacterFromID("SKD_Alisia");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "", "", "", "", -1);
			sld.location = "None";
			sld.lifeday = 0;
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("SKD_DomAnri_2", 4.0);
		break;
		
		case "SKD_DomAnri_6":
			dialog.text = "Œuvres merveilleuses, ô Seigneur ! Cela valait la peine de tout perdre pour trouver l'amour de votre vie au bout du monde ! Messieurs, je suis tout à vous. Je ne suppose pas que nous pourrons conclure un marché ?";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_6_1";
		break;
		case "SKD_DomAnri_6_1":
			StartInstantDialog("Duran", "SKD_DomAnri_7", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_7":
			dialog.text = "Non, et ne tentez pas de demander grâce non plus.";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_7_1";
			CharacterTurnToLoc(npchar, "barmen", "stay");
			locCameraFromToPos(-0.52, 1.47, 0.76, false, -2.52, 0.20, 0.99);
		break;
		case "SKD_DomAnri_7_1":
			StartInstantDialog("SKD_Anri", "SKD_DomAnri_8", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_8":
			dialog.text = "Il ne convient pas à un Chevalier de l'Ordre de demander grâce.";
			link.l1 = "Un ancien chevalier, cependant.";
			link.l1.go = "SKD_DomAnri_9";
		break;
		
		case "SKD_DomAnri_9":
			dialog.text = "Les bureaucrates n'auraient pas assez d'encre dans le monde pour me retirer ce titre.";
			link.l1 = "Dans ce cas, prouve-le.  Mais d'abord, satisfait ma curiosité : Es-tu un traître à la Couronne ? Sinon, je ne comprends pas pourquoi Levasseur tenait tant à ta vie.";
			link.l1.go = "SKD_DomAnri_10";
		break;
		
		case "SKD_DomAnri_10":
			dialog.text = "Je suis fidèle à mon serment, monsieur, alors ne m'en veuillez pas pour cela. Je dirai seulement qu'un traître à la Couronne m'a envoyé pour éliminer un autre traître. Et il le fera encore et encore jusqu'à ce qu'un Frère plus capable que moi réussisse. Assez parlé. Messieurs, à la bataille !";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_11";
		break;
		
		case "SKD_DomAnri_11":
			DialogExit();
			EndQuestMovie();
			
			sld = CharacterFromID("Duran");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "SKD_DomAnri_6");
		break;
		
		case "SKD_DomAnri_12":
			dialog.text = "Ah-ah! Oh, merci, Capitaine. C'était un sacré diable. Jamais je n'aurais pu le battre tout seul.";
			link.l1 = "D'une certaine manière, je ne me sens pas très heureux de cette victoire. Je suppose que nous en avons fini ici ?";
			link.l1.go = "SKD_DomAnri_13";
		break;
		
		case "SKD_DomAnri_13":
			dialog.text = "Pas tout à fait, d'abord nous devons nettoyer et éliminer la fille qui s'est enfuie si vite au deuxième étage.";
			link.l1 = "Quoi ?! Calmez-vous ! Avez-vous perdu la tête, Claude ? Je ne suis pas un boucher !";
			link.l1.go = "SKD_DomAnri_14";
		break;
		
		case "SKD_DomAnri_14":
			dialog.text = "Vous n'avez rien à faire, Capitaine. D'ailleurs, c'est de votre faute : vous n'auriez pas dû lui parler de Levasseur.";
			link.l1 = "C'est des balivernes et tu le sais bien. Et si tu oses encore me faire un reproche inarticulé, tu ne t'en sortiras pas comme ça.";
			link.l1.go = "SKD_DomAnri_15";
		break;
		
		case "SKD_DomAnri_15":
			dialog.text = "Heh! Ma faute, Capitaine. C'est vrai, les ordres de Levasseur disaient clairement de ne pas seulement éliminer le chevalier mais tous ses compagnons. Tous, vous comprenez ? Il ne faut pas plaisanter avec ces gens-là et leurs exigences doivent être prises au sérieux. Ne m'empêchez pas de faire mon travail, Cap. Un dernier sale boulot et ensuite je suis avec vous jusqu'à la fin, je le jure !";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				notification("Reputation Check Passed", "None");
				notification("Trustworthy", "Trustworthy");
				link.l1 = " (Digne de confiance) (Honneur) Vous avez dit un jour que j'étais destiné à voler haut, et vous étiez heureux d'y contribuer.";
				link.l1.go = "SKD_DomAnri_VD";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(71))+")", "None");
				notification("Perk Check Failed", "Trustworthy");
			}
			link.l2 = "Que le diable t'emporte ! Fais ton sale boulot. J'accepte ton serment, et tu ferais mieux de le prendre très au sérieux. Nous sommes bien d'accord ?";
			link.l2.go = "SKD_DomAnri_DuranDruzhba";
			link.l3 = "Pas à ce prix-là, Claude. Je ne te laisserai pas tuer cette fille.";
			link.l3.go = "SKD_DomAnri_DuranDraka";
		break;
		
		case "SKD_DomAnri_DuranDraka":
			dialog.text = "Héhé ! Je suppose que nous étions destinés à nous entre-tuer, hein, Capitaine ?";
			link.l1 = "Je suppose que oui. Reprenons où nous en étions à Tortuga, voulez-vous ?";
			link.l1.go = "SKD_DomAnri_DuranDraka_2";
		break;
		
		case "SKD_DomAnri_DuranDraka_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			
			RemovePassenger(pchar, npchar);
			npchar.SaveItemsForDead = true;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "SKD_DomAnri_DuranDraka");
		break;
		
		case "SKD_DomAnri_DuranDruzhba":
			dialog.text = "Oui, oui, Capitaine !";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_2";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_2":
			DialogExit();
			
			LocatorReloadEnterDisable("PortRoyal_houseSp1", "reload2", true);
			sld = CharacterFromID("Duran");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("PortRoyal_town", true);
			
			PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition.l1 = "location";
			PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition.l1.location = "PortRoyal_town";
			PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition = "SKD_DomAnri_DuranDruzhba";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_3":
			dialog.text = "C'est fait, Cap. Elle m'a bien surpris...";
			link.l1 = "Je ne veux pas en entendre parler. J'ai tenu parole. Maintenant c'est à ton tour.";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_4";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_4":
			dialog.text = "L'or est une chose, mais risquer sa propre peau pour un simple mercenaire vaut bien plus. Je suis avec vous jusqu'à la fin, Capitaine.";
			link.l1 = "Dans ce cas, nous en avons fini ici.";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_5";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_5":
			dialog.text = "Oui, oui.";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_6";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_6":
			DialogExit();
			
			EndQuestMovie();
			locCameraTarget(PChar);
			locCameraFollow();
			LAi_LocationDisableOfficersGen("PortRoyal_town", false);
			chrDisableReloadToLocation = false;
			AddQuestRecord("TheFormerKnight", "3");
			CloseQuestHeader("TheFormerKnight");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			
			sld = CharacterFromID("Duran");	//Клод Дюран становится постоянным офицером
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.Dialog.CurrentNode = "hired";
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			
			pchar.questTemp.SKD_DuranDruzhba = true;
			pchar.questTemp.SKD_DevushkaUbita = true;
			sld.reputation = sti(sld.reputation) - 15;
			OfficersFollow();
		break;
		
		case "SKD_DomAnri_VD":
			dialog.text = "Je l'ai fait. Où veux-tu en venir, Capitaine ?";
			link.l1 = "Montre-moi que ces mots n'étaient pas que du vent. Tu veux gagner ta place dans mon équipage ? Une part des futurs butins ? Suis mes ordres. Ne touche pas à la fille. Pourquoi ? Parce que si tu ne le fais pas, tu resteras un boucher pour toujours, et je n'ai pas de place pour des gens comme ça.";
			link.l1.go = "SKD_DomAnri_VD_2";
		break;
		
		case "SKD_DomAnri_VD_2":
			dialog.text = "C'est la deuxième fois que toi et moi allons nous battre jusqu'à la mort, Cap\nEt encore une fois, tu gagnes grâce à ton don pour gratter ta langue ! Ha ha ! Tu l'as dit ! Eh bien, au diable la fille. Je suis un animal après tout. Permission de rejoindre l'équipage ?";
			link.l1 = "Bienvenue, Claude. Pour de bon cette fois.";
			link.l1.go = "SKD_DomAnri_VD_3";
		break;
		
		case "SKD_DomAnri_VD_3":
			dialog.text = "Oui, oui, Capitaine !";
			link.l1 = "... ";
			link.l1.go = "SKD_DomAnri_VD_4";
		break;
		
		case "SKD_DomAnri_VD_4":
			DialogExit();
			AddQuestRecord("TheFormerKnight", "2");
			CloseQuestHeader("TheFormerKnight");
			chrDisableReloadToLocation = false;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			
			sld = CharacterFromID("Duran");	//Клод Дюран становится постоянным офицером
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.Dialog.CurrentNode = "hired";
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			
			pchar.questTemp.SKD_DuranDruzhba = true;
			sld.reputation = 60;
			OfficersFollow();
		break;
		
		case "SKD_KlodDuran":
			dialog.text = "Il y a un souci, Cap.";
			Link.l1 = "Permettez-moi de deviner : vous allez encore menacer de démissionner et exiger une augmentation ?";
			Link.l1.go = "SKD_KlodDuran_1";
		break;
		
		case "SKD_KlodDuran_1":
			dialog.text = "Heh ! Pas cette fois... Ne vous inquiétez pas, Capitaine, tant que vous payez, je suis tout à vous... dans la mesure du raisonnable, bien sûr. C'est la seule façon pour nous autres mercenaires de survivre. Et même les meilleurs d'entre nous sont payés une misère.";
			link.l1 = "Pourquoi ne pas simplement passer aux choses sérieuses ?";
			link.l1.go = "SKD_KlodDuran_2";
		break;
		
		case "SKD_KlodDuran_2":
			dialog.text = "Tu te souviens de cette garce de Tortuga ?";
			link.l1 = "Marceline ? La femme du gouverneur ? On n'oublie pas une femme comme ça.";
			link.l1.go = "SKD_KlodDuran_3";
		break;
		
		case "SKD_KlodDuran_3":
			dialog.text = "Je ne suis pas venu chez Levasseur par hasard. J'avais des affaires avec ce vaurien et hérétique.";
			link.l1 = "C'est plutôt étrange de ta part de parler si dédaigneusement des puissants, Claude.";
			link.l1.go = "SKD_KlodDuran_4";
		break;
		
		case "SKD_KlodDuran_4":
			dialog.text = "Hein ? Heh ! Levasseur est le diable ! Il est bien pire que même les pirates qui se nourrissent de lui !";
			link.l1 = "Vous-même avez dit que vous faisiez affaire avec lui. N'est-ce pas un peu hypocrite de votre part ?";
			link.l1.go = "SKD_KlodDuran_5";
		break;
		
		case "SKD_KlodDuran_5":
			dialog.text = "Je ne suis pas un ange, Cap, et je gagne ma vie en tuant ceux qu'on me dit de tuer. C'est pour ça que tu m'apprécies tant, n'est-ce pas ? Mais même des hommes comme moi frissonnent en entendant des rumeurs sur ce qu'ils font aux femmes à la Tortue dans les repaires de Levasseur !";
			link.l1 = "Les rumeurs ne m'intéressent pas. Cet homme est un noble et un serviteur du Roi, et il mérite le respect.";
			link.l1.go = "SKD_KlodDuran_6";
		break;
		
		case "SKD_KlodDuran_6":
			dialog.text = "Alors tu as volé le serviteur de ce roi et baisé sa femme ? Hé ! Fais comme bon te semble, Cap. Allons droit au but. Son Excellence m'a ordonné de trouver et tuer un homme. Une tâche assez routinière, même si cela ne vient pas souvent d'une personne si haut placée, et encore moins en personne.";
			link.l1 = "Et que veux-tu ? Te libérer pour que tu puisses tenir ta parole et tuer cet homme ?";
			link.l1.go = "SKD_KlodDuran_7";
		break;
		
		case "SKD_KlodDuran_7":
			dialog.text = "Je veux que tu m'aides à le faire, Cap. Quand les choses ont mal tourné pour moi à Tortuga, j'ai accepté de rejoindre ton service, mais je ne me reposerai pas tant que je n'aurai pas terminé le travail. Levasseur me tuerait s'il l'apprenait. En plus, ce n'est pas professionnel de laisser un travail inachevé.";
			link.l1 = "Est-ce professionnel d'avoir des liaisons avec la femme d'un client ? C'est très étrange d'entendre une telle demande de votre part, surtout si l'on se souvient du début de notre conversation, où vous avez décrit assez précisément l'essence de notre relation. Du sang pour de l'or, hein ?";
			link.l1.go = "SKD_KlodDuran_8";
		break;
		
		case "SKD_KlodDuran_8":
			dialog.text = "Si vous m'aidez, vous n'aurez pas seulement mon épée, vous aurez ma loyauté. Je vois tout de suite que vous êtes destiné à voler haut, Capitaine. Je serais heureux de contribuer à cela.";
			link.l1 = "J'admets que je préfèrerais avoir un homme de vos capacités pour surveiller mes arrières. Où pouvons-nous trouver cette cible à vous?";
			link.l1.go = "SKD_KlodDuran_10";
			link.l2 = "Votre sabre suffira pour l'instant. Je ne suis pas un assassin. À l'aise, officier !";
			link.l2.go = "SKD_KlodDuran_9";
		break;
		
		case "SKD_KlodDuran_9":
			dialog.text = "Aye, aye, Cap. Cela valait la peine de demander de toute façon.";
			link.l1 = "...";
			link.l1.go = "SKD_KlodDuran_9_1";
		break;
		
		case "SKD_KlodDuran_9_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.loyality = makeint(npchar.loyality) + 10;
			Return_DurandOfficer();
		break;
		
		case "SKD_KlodDuran_10":
			dialog.text = "Eh bien ! C'est ça le problème, Capitaine. Tout ce que je sais, c'est qu'il est un ancien chevalier de l'Ordre de Malte en fuite quelque part en territoire anglais. Un homme de noble naissance, donc il ne vivra pas dans une masure.";
			link.l1 = "Chevalier de l'Ordre ?";
			link.l1.go = "SKD_KlodDuran_11";
		break;
		
		case "SKD_KlodDuran_11":
			dialog.text = "Un ancien chevalier. Oui, et j'ai déjà regretté d'avoir pris ce boulot mille fois. Les chevaliers se battent comme des diables, alors je te garantis une épreuve sérieuse pour tes compétences à l'épée.";
			link.l1 = "Je n'aime pas ça, mais essayons. Alors : pas un pauvre homme, un noble et caché chez les Anglais ? Levasseur n'a pas dit pourquoi il devait être éliminé ?";
			link.l1.go = "SKD_KlodDuran_12";
		break;
		
		case "SKD_KlodDuran_12":
			dialog.text = "Bien sûr qu'il ne le fera pas ! Mais c'est évidemment politique, sinon il aurait envoyé des soldats.";
			link.l1 = "Je vais essayer, mais je ne peux rien promettre.";
			link.l1.go = "SKD_KlodDuran_13";
		break;
		
		case "SKD_KlodDuran_13":
			dialog.text = "Merci, Cap.";
			link.l1 = "...";
			link.l1.go = "SKD_KlodDuran_14";
		break;
		
		case "SKD_KlodDuran_14":
			DialogExit();
			SetQuestHeader("TheFormerKnight");
			AddQuestRecord("TheFormerKnight", "1");
			chrDisableReloadToLocation = false;
			npchar.loyality = makeint(npchar.loyality) + 15;
			Return_DurandOfficer();
			PChar.quest.SKD_DomAnri.win_condition.l1 = "location";
			PChar.quest.SKD_DomAnri.win_condition.l1.location = "PortRoyal_houseSp1";
			PChar.quest.SKD_DomAnri.win_condition = "SKD_DomAnri";
			pchar.GenQuestBox.PortRoyal_houseSp1.box1.items.chest = 1;
		break;
		
	}
} 
