// диалоги прочих НПС
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
			dialog.text = "Un bogue. Informez les développeurs.";
			link.l1 = "Je le ferai !";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			if (npchar.id == "HWICFernando") NextDiag.CurrentNode = "Fernando";
			DialogExit();
		break;
	
//---------------------------------------за Голландию--------------------------------------------------
		//сопроводить торговца
		case "Baltazar":
			pchar.quest.Create_BaltazarOver.over = "yes";//снять прерывание
			dialog.text = "Quelle aubaine ! Capitaine, il se trouve justement que j'ai besoin d'une escorte pour Philipsburg très urgemment...";
			link.l1 = "Êtes-vous Balthazar Ridderbock ?";
			link.l1.go = "Baltazar_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Baltazar_1":
			dialog.text = "Que diable, je suis déjà plus célèbre que le vice-roi ! Qui es-tu ? Que veux-tu ?";
			link.l1 = "Je suis le capitaine "+GetFullName(pchar)+"Je suis envoyé par Lucas Rodenburg. Je suis autorisé à vous prendre, vous et votre navire, sous ma protection.";
			link.l1.go = "Baltazar_2";			
		break;
		
		case "Baltazar_2":
			dialog.text = "Oh, monsieur Rodenburg a dû entendre mes supplications pour de l'aide ! Vous voyez, il y a un corsaire...";
			link.l1 = "Passons les détails de votre histoire, je les connais déjà.";
			link.l1.go = "Baltazar_3";			
		break;
		
		case "Baltazar_3":
			dialog.text = "Bien sûr ! J'ai déjà perdu trop de temps... Je dois arriver à Philipsburg dans deux semaines au plus tard.";
			link.l1 = "Alors, rends-toi à ton navire et prépare-toi pour appareiller. Nous mettons les voiles sur-le-champ !";
			link.l1.go = "Baltazar_4";			
		break;
		
		case "Baltazar_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 4);
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			AddQuestRecord("Holl_Gambit", "1-3");
			AddMapQuestMarkCity("Marigo", true);
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Baltazar_ConvoyOver", 0, 0, 28, false);
			}
			else SetFunctionTimerCondition("Baltazar_ConvoyOver", 0, 0, 14, false); //таймер
			pchar.quest.BaltazarConvoy_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
			pchar.quest.BaltazarConvoy_fail.win_condition.l1.character = "Baltazar";
			pchar.quest.BaltazarConvoy_fail.function = "Baltazar_fail";
			pchar.quest.BaltazarConvoy_complete.win_condition.l1 = "location";//прерывание на выполнение
			pchar.quest.BaltazarConvoy_complete.win_condition.l1.location = "Marigo_town";
			pchar.quest.BaltazarConvoy_complete.function = "Baltazar_complete";
			if (rand(1) == 0)
			{
				BaltazarPirateGlobalCreate();
			}
			else
			{
				pchar.questTemp.HWIC.Holl.BaltazarAttack = "true";
				pchar.quest.BaltazarConvoy_Attack.win_condition.l1 = "location";//прерывание на выполнение
				pchar.quest.BaltazarConvoy_Attack.win_condition.l1.location = "SentMartin";
				pchar.quest.BaltazarConvoy_Attack.function = "BaltazarPirateSeaCreate";
			}
		break;
		
		case "Baltazar_5":
			dialog.text = "Merci pour votre aide, Capitaine ! Votre protection ne pouvait pas arriver à un meilleur moment, je vous prie d'accepter mes remerciements et ces 5 000 pesos.";
			link.l1 = "Hmm... Ce n'est pas une récompense très généreuse pour avoir sauvé une vie...";
			link.l1.go = "Baltazar_6";			
		break;
		
		case "Baltazar_6":
			dialog.text = "De plus, j'enverrai une lettre à monsieur Rodenburg dès que j'en aurai l'occasion - avec la plus haute évaluation possible de vos actions. Je dois y aller maintenant.";
			link.l1 = "Eh bien, adieu alors, Balthazar.";
			link.l1.go = "Baltazar_7";			
		break;
		
		case "Baltazar_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 3.0);
			AddQuestRecord("Holl_Gambit", "1-6");
			AddMoneyToCharacter(pchar, 5000);
			ChangeCharacterComplexReputation(pchar,"nobility", 2); 
			ChangeCharacterNationReputation(pchar, HOLLAND, 1);
			ChangeOfficersLoyality("good_all", 1);
			pchar.questTemp.HWIC.Holl = "BaltazarCom";
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		//командировка в Сантьяго
		case "Santiago_Trip":
			dialog.text = "Sénor ! Attendez... on dirait que vous avez laissé tomber quelque chose...";
			link.l1 = "Quoi ? Ah ?!";
			link.l1.go = "Santiago_Trip_1";
		break;
		
		case "Santiago_Trip_1":
			DialogExit();
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("You were knocked unconscious from behind", "", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 15, 10); //крутим время
			RecalculateJumpTable();
			DoQuestFunctionDelay("SantiagoTripInHouse", 4.0);
		break;
		
		case "Santiago_Trip_2":
			dialog.text = "Désolé, mon ami - j'ai dû te frapper légèrement pour que tu ne causes pas de problème. Je me rends compte que tu as probablement mal à la tête, mais quoi qu'il en soit, tu survivras. Si le temps le permet...";
			link.l1 = "Qui diable es-tu, et que se passe-t-il ici ?";
			link.l1.go = "Santiago_Trip_3";
		break;
		
		case "Santiago_Trip_3":
			dialog.text = "Doucement, doucement, mon ami - sinon je devrai te calmer à nouveau. Nous ne voulons pas que ces martinets débarquent, faisant cliqueter leurs épées rouillées, n'est-ce pas ? Nous devons parler calmement.";
			link.l1 = "Rends-moi mon épée, salaud, et nous aurons une belle conversation, je le jure !";
			link.l1.go = "Santiago_Trip_4";
		break;
		
		case "Santiago_Trip_4":
			dialog.text = "Tu es un petit homme rapide, n'est-ce pas? Pas besoin d'utiliser l'acier pour l'instant. Dis-moi ce que je veux savoir et, peut-être, tu quitteras cet endroit en un seul morceau. Suis-je clair? Alors, discutons un peu.\nTu restes silencieux? Bien, nous avons donc un accord. Qu'as-tu transporté de Rodenburg au banquier?";
			link.l1 = "Une lettre.";
			link.l1.go = "Santiago_Trip_5";
		break;
		
		case "Santiago_Trip_5":
			dialog.text = "Astucieux. Je sais que ce n'était pas un bouquet de marguerites. Qu'est-ce qu'il y avait dans cette lettre, garçon ?";
			link.l1 = "Comment puis-je le savoir ? Je n'ai pas l'habitude de lire la correspondance qui m'est confiée. Peut-être était-ce un message d'amour. Vous savez ce qu'on dit des gens de pouvoir...";
			link.l1.go = "Santiago_Trip_6";
		break;
		
		case "Santiago_Trip_6":
			dialog.text = "...Un capitaine honnête est une chose bien rare à voir en ces temps misérables. Eh bien, c'est une mauvaise nouvelle pour toi. Que diable a dit ce foutu banquier, quand il a reçu le paquet ? Quelle affaire a-t-il avec les Hollandais ?";
			link.l1 = "Ils trafiquent du parfum de contrebande de France... ou de la bouse de vache bavaroise, je pense.";
			link.l1.go = "Santiago_Trip_7";
			link.l2 = "La question portait sur une compensation pour quelque chose. C'est tout ce que je sais.";
			link.l2.go = "Santiago_Trip_8";
		break;
		
		case "Santiago_Trip_7":
			dialog.text = "Tu es un brave gars... Et avec un sens de l'humour, en plus. Ce serait dommage de te tuer. Gaston t'aurait apprécié. Cependant... reste ici pour l'instant. Je dois aller vérifier quelque chose, et Miguel veillera sur toi pendant mon absence.";
			link.l1 = "Je jure, 'mon ami' - tu le regretteras! ";
			link.l1.go = "Santiago_Trip_9";
		break;
		
		case "Santiago_Trip_8":
			dialog.text = "Là va l'arrogance... Quand les choses semblent sombres, notre brave capitaine montre de la raison. Vous auriez pu le faire bien plus tôt et nous aurions gagné du temps et des ennuis. Eh bien, je dois aller vérifier quelque chose, mais ensuite je reviendrai et nous parlerons, si c'est encore nécessaire, c'est-à-dire. Restez ici pour le moment. Miguel veillera sur vous pendant mon absence.";
			link.l1 = "Je te jure, 'mon ami' - tu vas le regretter! ";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_9":
			dialog.text = "Mais bien sûr. Tais-toi, 'héros' - peut-être que tout ira encore bien.";
			link.l1 = "... ";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_10":
			dialog.text = "Reste ici et espère que ta flexibilité se justifiera.";
			link.l1 = "...де старшего брата, Мишеля де Монпе, давно нет вестей. Шарль бы и не парился, но если у старшего брата проблемы, то имя семьи может быть очернено, да отец в случае отказа лишить пособия. По прибытию выясняется, что брат Мишель сидит в тюрьме за провал важного задания своего босса - генерал-губернатора Пуанси, который в наказание ещё и повесил огромный долг на Мишеля. В начале Шарль ведёт себя как изнеженный дворянчик и нарцисс, но быстро встраивается в карибскую жизнь, обзаводится кораблем, знакомствами и выплачивает долг брата. В этих текстах Шарль, стремясь заработать денег для залога, а также, чтобы обзавестись полезными знакомствами, работает на одну из трех сторон конфликта: Голландскую Вест-Индскую Компанию под руководством Роденбурга, английскую разведку под руководством Флитвуда или на силовой блок Компании, которой руководит Мердок. В конце выживет только один, а Шарль не только разбогатеет и получит союзника, но и сможет привлечь на свою сторону одного из квестовых офицеров: китайца Лонгвея, англичанина Чарли Книппеля, или головореза-француза Эркюля Тонзага. ";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_11":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-44");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Santiago_HouseSp2", "goto", "goto4", "", -1);
			pchar.quest.Santiago_Trip1.win_condition.l1 = "item";
			pchar.quest.Santiago_Trip1.win_condition.l1.item = "slave_01";
			pchar.quest.Santiago_Trip1.function = "SantiagoTrip_wait";
		break;
		
		case "Santiago_Trip_12":
			dialog.text = "Que diable?!";
			link.l1 = "Prépare-toi à mourir, canaille !";
			link.l1.go = "Santiago_Trip_13";
		break;
		
		case "Santiago_Trip_13":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "SantiagoTripExitFromRoom");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Santiago_Trip_14":
			dialog.text = "Quel gâchis ! Je me demandais d'où venait tout ce vacarme. Mes félicitations - tu es un gars intelligent !";
			link.l1 = "Plus malin que tu ne le penses... Voyons maintenant ce que tu peux faire contre un adversaire armé !";
			link.l1.go = "Santiago_Trip_15";
		break;
		
		case "Santiago_Trip_15":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "SantiagoTripExitHouse");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		//офицер-посланник по 5 заданию
		case "HollQuest_Officer":
			dialog.text = "Monsieur Lucas Rodenburg veut vous voir immédiatement. Allez le voir tout de suite.";
			link.l1 = "En chemin.";
			link.l1.go = "HollQuest_Officer_exit";			
		break;
		
		case "HollQuest_Officer_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			pchar.questTemp.HWIC.Holl = "MerdokStart";
			AddQuestRecord("Holl_Gambit", "1-36");
		break;
		
//---------------------------------------------против всех----------------------------------------------
		//убрать испанского идальго
		case "Fernando":
			dialog.text = "Que veux-tu de moi ?";
			link.l1 = "Ta tête !";
			link.l1.go = "Fernando_fight";
			link.l2 = "Rien, laissez tomber.";
			link.l2.go = "exit";	
			NextDiag.TempNode = "Fernando_repeat";
		break;
		
		case "Fernando_repeat":
			dialog.text = "C'est encore toi ? Que veux-tu de moi ?! Explique-toi !";
			link.l1 = "Ta tête !";
			link.l1.go = "Fernando_fight";
			link.l2 = "Rien, peu importe.";
			link.l2.go = "exit";	
			NextDiag.TempNode = "Fernando_repeat";		
		break;
		
		case "Fernando_fight":
			chrDisableReloadToLocation = true;//выходы закроем
			LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "SPAIN_CITIZENS");
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
			pchar.quest.HWIC_Fernando.win_condition.l1 = "NPC_Death";
			pchar.quest.HWIC_Fernando.win_condition.l1.character = "HWICFernando";
			pchar.quest.HWIC_Fernando.function = "Fernando_died";
		break;
		
		//в доме Флитвуда
		case "Fleetwood_soldier"://для любителей сунуть нос куда не надо
			if (CheckAttribute(npchar, "quest.talked"))
			{
			dialog.text = "C'est encore toi ? Pourquoi tu rôdes ici ? Ça ne me plaît pas du tout. Bon, je vais t'arrêter et t'envoyer au bureau du commandant pour enquête. Les gars, attrapez ce type !";
			link.l1 = "Mais je voulais juste...";
			link.l1.go = "Fleetwood_soldier_4";	
			}
			else
			{
			dialog.text = "Qui êtes-vous et que voulez-vous ? Expliquez-vous !";
			link.l1 = "Je suis désolé, monsieur, il semble que je sois venu à la mauvaise maison. Je vous prie de m'excuser.";
			link.l1.go = "Fleetwood_soldier_1";	
			link.l2 = "Je voudrais voir Richard Fleetwood.";
			link.l2.go = "Fleetwood_soldier_2";		
			}
		break;
		
		case "Fleetwood_soldier_1":
			dialog.text = "C'est exact. Vous vous adressez à la mauvaise personne. Ayez l'amabilité de partir sur-le-champ !";
			link.l1 = "Oui. Bien sûr.";
			link.l1.go = "Fleetwood_soldier_3";			
		break;
		
		case "Fleetwood_soldier_2":
			dialog.text = "Vraiment ? Qui t'a dit qu'il vivait ici ? Cela semble suspect... Très bien, je vais t'arrêter et t'envoyer au bureau du commandant pour enquête. Les gars, attrapez ce type !";
			link.l1 = "Mais je voulais juste voir Richard...";
			link.l1.go = "Fleetwood_soldier_4";	
		break;
		
		case "Fleetwood_soldier_3":
			DialogExit();
			npchar.quest.talked = "true";
			DoQuestReloadToLocation("SentJons_town", "reload", "houseSP3", "");
			pchar.quest.Fleetwood_Soldier.win_condition.l1 = "location";
			pchar.quest.Fleetwood_Soldier.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Fleetwood_Soldier.function = "Fleetwood_Soldier";//для настырных
		break;
		
		case "Fleetwood_soldier_4":
			DialogExit();
			GoToPrison("SentJons", 1000, 10);			
		break;
		
		case "Theft_soldier":
			dialog.text = "Ah ! Voleurs ? Espions ? Accrochez-vous à votre chapeau maintenant !";
			link.l1 = "Haut!";
			link.l1.go = "Attack_Theft_soldier";			
		break;
		
		case "Attack_Theft_soldier":
			LAi_group_Delete("EnemyFight");
			LAi_SetHP(npchar, 500, 500);
			LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Attack_soldier":
			dialog.text = "Ah ! Que fait ce type ici ? Les gars, on a un espion ici ! Aux armes !";
			link.l1 = "Ho!";
			link.l1.go = "Attack_soldier_fight";			
		break;
		
		case "Attack_soldier_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//снять запрет драки
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=4; i++)
			{
			sld = characterFromId("Attack_sold_"+i);	
			LAi_SetWarriorType(sld);
            LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PrepareToStreetFight");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		//Книппель-пленник в трюме
		case "Sailor_deck":
			chrDisableReloadToLocation = true;
			dialog.text = "Capitaine, nous avons interrogé ce vaurien, comme vous nous l'avez ordonné. Nous avons dû le cautériser un peu... Il avait cette lettre sur lui. Il a essayé de la manger, mais nous ne l'avons pas laissé faire. Comme nous le pensions, il devait prendre une fille à Willemstad et l'amener à son patron.";
			link.l1 = "Une lettre ? Voyons cela. Ensuite, je lui parlerai moi-même.";
			link.l1.go = "Sailor_deck_1";			
		break;
		
		case "Sailor_deck_1":
			DialogExit();
			AddLandQuestMark(characterFromId("KnippelClone"), "questmarkmain");
			GiveItem2Character(pchar, "NPC_Letter");
			AddQuestRecordInfo("LetterToAbi", "1");
		break;
		
		case "Sailor_deck_2":
			dialog.text = "Quels sont vos ordres, Capitaine ?";
			link.l1 = "Jetez le cadavre par-dessus bord. Et préparez-vous à débarquer !";
			link.l1.go = "Sailor_deck_3";			
			// belamour legendary edition -->
			link.l2 = "Enterrez-le en mer avec tous les honneurs militaires. Ce vieil homme s'est battu vaillamment jusqu'à la fin. Il a même chargé et visé ce canon après qu'il ait été renversé de son affût. C'est bien dommage. Dans un autre monde, nous aurions pu être camarades...";
			link.l2.go = "Sailor_deck_3a";
		break;
		
		case "Sailor_deck_3a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			dialog.text = "Oui, Capitaine !";
			link.l1 = "...";
			link.l1.go = "Sailor_deck_4";			
		break;
		
		case "Sailor_deck_3":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 120);
			AddCharacterExpToSkill(pchar, "FencingL", 30);
			AddCharacterExpToSkill(pchar, "FencingS", 30);
			AddCharacterExpToSkill(pchar, "FencingH", 30);
			AddCharacterExpToSkill(pchar, "Pistol", 30);
			// <-- legendary edition
			dialog.text = "Aye-aye, Capitaine!";
			link.l1 = "...";
			link.l1.go = "Sailor_deck_4";			
		break;
		
		case "Sailor_deck_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			AddQuestRecord("Holl_Gambit", "3-21");
			LAi_SetActorType(pchar);
			sld = characterFromId("KnippelClone");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("Sailor_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "ReturnMCPlayer", 3);
			}
			pchar.questTemp.HWIC.Self = "toVillemstad";
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Villemstad", false);
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			LocatorReloadEnterDisable("Villemstad_houseSP2", "reload2", true);//закроем комнату Аби
		break;
		
		//Лонгвэй-пленник в трюме
		case "Sailor_deck_5":
			chrDisableReloadToLocation = true;
			dialog.text = "Nous avons préparé le Chinois pour l'interrogatoire, comme vous l'avez ordonné, Capitaine. Il n'avait rien sur lui, pas de papiers. Un brasier a été préparé, et nous chauffons les menottes et les pinces à rouge vif en ce moment.";
			link.l1 = "Bon travail, Alonso. Mais avant que tu ne commences, j'aimerais essayer de raisonner avec lui. Peut-être qu'il décidera de coopérer de son plein gré ?";
			link.l1.go = "Sailor_deck_6";			
		break;
		
		case "Sailor_deck_6":
			dialog.text = "Comme vous dites, Capitaine.";
			link.l1 = "...";
			link.l1.go = "exit";	
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
		break;
		
		case "Sailor_deck_7":
			dialog.text = "Oui, Capitaine ?";
			link.l1 = "Mettez-lui des fers aux poignets et gardez un oeil sur lui en tout temps jusqu'à ce que nous atteignions la Guadeloupe. Vous trois devez toujours être ici. Vous répondez de votre vie pour lui.";
			link.l1.go = "Sailor_deck_8";			
		break;
		
		case "Sailor_deck_8":
			dialog.text = "Aye-aye, Capitaine !";
			link.l1 = " ";
			link.l1.go = "Sailor_deck_9";			
		break;
		
		case "Sailor_deck_9":
			chrDisableReloadToLocation = false;
			AddQuestRecord("Holl_Gambit", "3-48");
			sld = characterFromId("LongwayClone");
			LAi_SetActorType(sld);
			LAi_SetGroundSitType(sld);
			DialogExit();
			pchar.quest.Longway_Shore.win_condition.l1 = "location";
			pchar.quest.Longway_Shore.win_condition.l1.location = "Shore31";
			pchar.quest.Longway_Shore.function = "LongwayInShore";
			AddMapQuestMarkShore("Shore31", true);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		//пьяница - передача письма Флитвуду
		case "Drunkard":
			DelLandQuestMark(npchar);
			dialog.text = "H-ic ! Bonsoir, monsieur ! Que désirez-vous ? Peut-être pourriez-vous offrir un verre à un vieux soûlard ? Et je...";
			link.l1 = "Ecoute ici, vieux soûlard... Es-tu Jack Harrison ?";
			link.l1.go = "Drunkard_1";			
		break;
		
		case "Drunkard_1":
			dialog.text = "Ah ! Oui, c'est moi. Qui d'autre cela pourrait-il être ? Pourquoi ? Qu'a-al-lo-ons nous f-a-a-ire d'un ma-a-rin ivr-e-e...";
			link.l1 = "Oh mon Seigneur, donne-moi de la patience ! Quel marin ? Ça se lit sur ton visage que tu es un pied-tendre... Veux-tu gagner un peu d'argent ?";
			link.l1.go = "Drunkard_2";			
		break;
		
		case "Drunkard_2":
			dialog.text = "Je veux toujours gagner de l'argent. Que devrais-je faire ? Mais je ne tuerai personne. Et je ne volerai rien non plus. Et tu n'es pas mon genre.";
			link.l1 = "Tu n'auras pas à tuer qui que ce soit, et je doute que tu en sois vraiment capable. Tu es trop empoté. Maintenant. Voici une lettre. Prends-la et livre-la à la maison à gauche de la résidence du gouverneur. Elle est destinée à Richard Fleetwood.";
			link.l1.go = "Drunkard_3";			
		break;
		
		case "Drunkard_3":
			dialog.text = "Pour Richard Fleetwood ? Non... Je serai arrêté à vue.";
			link.l1 = "Tais-toi et écoute. Personne ne va t'arrêter. Tu diras que tu viens de la part de Charlie Knippel au sujet d'Abigail. On te laissera entrer. Répète ce que j'ai dit.";
			link.l1.go = "Drunkard_4";			
		break;
		
		case "Drunkard_4":
			dialog.text = "Qui est Abigail ? Je connais Knippel...";
			link.l1 = "Ce ne sont pas tes affaires. Moins tu en sais, plus longtemps tu vivras. Eh bien, j'attends. Répète.";
			link.l1.go = "Drunkard_5";			
		break;
		
		case "Drunkard_5":
			dialog.text = "Je viens de la part de Charlie Knippel concernant euh..... Abigail. Voilà.";
			link.l1 = "Bien joué. Vous recevrez 5000 pesos pour le travail.";
			link.l1.go = "Drunkard_6";			
		break;
		
		case "Drunkard_6":
			if (makeint(Pchar.money) >= 5000)
			{
				dialog.text = "5000 pesos? Oh.... Seulement pour livrer une lettre?";
				link.l1 = "Non. On vous remettra une autre lettre. Vous viendrez avec elle à la taverne et vous vous assiérez ici. Je la prendrai de vous. Ne faites rien de stupide et n'ayez pas peur - je vous surveillerai et resterai proche. Prenez cette somme comme avance pour vous sentir plus à l'aise.";
				link.l1.go = "Drunkard_7";	
			}
			else
			{
				dialog.text = "Cinq mille ? As-tu même une telle somme ?";
				link.l1 = "Ha ! Bien sûr que j'en ai. Je vais l'apporter maintenant.";
				link.l1.go = "Drunkard_no_money";	
				NextDiag.CurrentNode = "Drunkard_no_money";
			}
		break;
		
		case "Drunkard_no_money":
			dialog.text = "As-tu apporté les cinq mille ?";
			if (makeint(Pchar.money) >= 5000)
			{
				link.l1 = "Oui. Vous voilà. Ne vous inquiétez pas.";
				link.l1.go = "Drunkard_7";
			}
			else
			{
				link.l1 = "Non. Attends. Je reviendrai bientôt.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Drunkard_no_money";
			}
		break;
		
		case "Drunkard_7":
			AddMoneyToCharacter(pchar, -5000);
			RemoveItems(PChar, "MC_Letter", 1);
			dialog.text = "Hmm... Dois-je y aller maintenant, monsieur ?";
			link.l1 = "Non, jeudi matin... Bien sûr, tout de suite, espèce d'idiot ! Maintenant, finis ton rhum et va-t'en !";
			link.l1.go = "Drunkard_8";			
		break;
		
		case "Drunkard_8":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-26");
			LAi_SetStayType(npchar);
			LAi_RemoveLoginTime(npchar);//удалить время загрузки
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "sentjons_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "sentjons_town", "reload", "reload4_back", "DrunkardGoTown", -1);
			chrDisableReloadToLocation = true;//закрыть локацию
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", true);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", true);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", true);//чтобы не сбежал
		break;
		
		case "Drunkard_9":
			DelLandQuestMark(npchar);
			dialog.text = "Ah, vous voilà, monsieur... J'aurais mieux fait de ne pas faire cela. Richard est devenu furieux quand il a fini de lire. J'ai cru qu'il allait me tuer.";
			link.l1 = "Mais te voilà ! Ne t'inquiète pas - il n'oserait pas faire ça - tu étais très précieux pour lui à ce moment-là ha-ha ! Tu ne peux même pas imaginer à quel point...";
			link.l1.go = "Drunkard_10";			
		break;
		
		case "Drunkard_10":
			dialog.text = "J'ai besoin de boire un coup... Voici sa réponse pour toi.";
			link.l1 = "Donne-le-moi! Et ferme ta gueule!";
			link.l1.go = "Drunkard_11";			
		break;
		
		case "Drunkard_11":
			GiveItem2Character(pchar, "MC_Letter");
			ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter1");
			AddQuestRecordInfo("FleetwoodAnswer", "1");
			dialog.text = "Il me sera difficile de parler dans les prochains jours... Adieu... Je souhaite ne jamais te revoir.";
			link.l1 = "Du calme, vieux soûlard, ha-ha-ha! Qu'est-ce qu'on fai-it d'un matelot ivre... Bois et détends-toi - tout est fini maintenant !";
			link.l1.go = "Drunkard_12";			
		break;
		
		case "Drunkard_12":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Holl_Gambit", "3-27");
			pchar.questTemp.HWIC.Self = "FleetwoodAgree";
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		//кэп курьерского судна
		case "Cureer_abordage":
			dialog.text = "Pourquoi diable avez-vous attaqué mon navire ? Je n'ai ni objets de valeur ni argent - juste des papiers, qui ne vous sont de toute façon d'aucune utilité !";
			link.l1 = "Tais-toi. Tu as perdu, alors maintenant tu vas m'écouter. Je n'ai besoin ni de ton navire, ni de tes papiers. J'ai besoin que tu transmettes ce message à ton patron, ce sale rat de Lucas Rodenburg. Dis-lui que le capitaine Fleetwood lui envoie ses salutations.";
			link.l1.go = "Cureer_abordage_1";			
		break;
		
		case "Cureer_abordage_1":
			dialog.text = "Capitaine Fleetwood ? Mais...";
			link.l1 = "Tu vas remettre cette lettre à ton chef - ou dois-je te transpercer ? Je peux aussi chercher un autre candidat pour la livraison. Je pille les navires de ta sale Compagnie tous les week-ends par ennui, juste pour que tu le saches.";
			link.l1.go = "Cureer_abordage_2";			
		break;
		
		case "Cureer_abordage_2":
			dialog.text = "D'accord, monsieur Fleetwood. Je le livrerai.";
			link.l1 = "C'est formidable. Maintenant, nous pouvons nous dire adieu, Monsieur. Vous pouvez vous considérer très chanceux aujourd'hui. Et n'oubliez pas de visiter une église à votre arrivée !";
			link.l1.go = "Cureer_abordage_3";			
		break;
		
		case "Cureer_abordage_3":
			DialogExit();
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			sld.ShipEnemyDisable  = true;
			pchar.quest.HWICCureer_AfterBattle.over = "yes";
			pchar.quest.HWICCureerOnMapOver.over = "yes";
			AddQuestRecord("Holl_Gambit", "3-39");
			Log_TestInfo("THE LETTER HAS BEEN DELIVERED!");
			RemoveItems(PChar, "MC_Letter", 1);
			pchar.questTemp.HWIC.Self = "LetterToLucasSent";
			pchar.quest.Curacao_exploring.win_condition.l1 = "location";
			pchar.quest.Curacao_exploring.win_condition.l1.location = "Curacao";
			pchar.quest.Curacao_exploring.function = "CuracaoExploring";
			DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
			AddComplexSeaExpToScill(50, 50, 50, 100, 50, 50, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
			AddMapQuestMarkIsland("Curacao", true);
		break;
		
		//Матиас Бек в тюрьме
		case "MatiasBek"://на случай если геймер захочет пообщаться
			dialog.text = "J'ai été arrêté illégalement ! Je n'ai aucun lien avec les Anglais ! Ce sont toutes des intrigues de Rodenburg. Peu importe. Peter Stuyvesant arrivera bientôt - il mettra de l'ordre dans tout ça !";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "MatiasBek";
		break;
		
		//стражник у входа в резиденцию
		case "QuestGuard":
			dialog.text = "Le sieur Lucas Rodenburg ne souhaite voir personne en ce moment. Ayez l'amabilité de quitter la résidence sur-le-champ.";
			link.l1 = "Hm. Je vois. J'essaierai de passer dans une semaine...";
			link.l1.go = "exit";
			NextDiag.TempNode = "QuestGuard";		
		break;
		
		//Питер Стайвесант
		case "Stivesant":
			dialog.text = "Nous allons à la résidence, Capitaine. J'ai déjà envoyé mes hommes au fort pour obtenir des informations sur Matthias Beck. S'il est effectivement en prison en ce moment, il doit déjà avoir été libéré et accompagné en ville. Suivez-moi !";
			link.l1 = "Oui, Monseigneur Stuyvesant.";
			link.l1.go = "Stivesant_1";			
		break;
		
		case "Stivesant_1":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "Villemstad_townhall", "goto", "goto2", "OpenVillemstadResidence", -1);
		break;
		
		case "ArestLucas_1":
			dialog.text = "Lucas ! Que se passe-t-il ici ? Où est Matthias Beck ? Est-il vrai que vous l'avez envoyé en prison ?";
			link.l1 = "Bonjour, monami.";
			link.l1.go = "ArestLucas_2";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_2":
			StartInstantDialog("Lucas", "ArestLucas_3", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_3":
			dialog.text = "Bonjour, Mynheer Stuyvesant. J'ai des preuves de sa connexion avec les services de renseignement britanniques et directement avec le capitaine Fleetwood. Il a informé ce fichu Britannique d'attaquer notre brigantin courrier pour s'emparer de la correspondance confidentielle de la Compagnie.";
			link.l1 = "";
			link.l1.go = "ArestLucas_4";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 4.5);
		break;
		
		case "ArestLucas_4":
			StartInstantDialog("Stivesant", "ArestLucas_5", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_5":
			dialog.text = "Où as-tu obtenu cette information ?";
			link.l1 = "Bonjour, mon ami.";
			link.l1.go = "ArestLucas_6";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_6":
			StartInstantDialog("Lucas", "ArestLucas_7", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_7":
			dialog.text = "It was claimed by the captain of the courier brigantine. Richard Fleetwood boarded his ship and took away his papers; then the ship was set free. Nobody except me, you and Matthias Beck had any information about either the route or the schedule.";
			link.l1 = "";
			link.l1.go = "ArestLucas_8";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));
		break;
		
		case "ArestLucas_8":
			StartInstantDialog("Stivesant", "ArestLucas_9", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_9":
			dialog.text = "And that's why you have decided that Beck tipped off Fleetwood to attack the brigantine? What rubbish! Fleetwood is an ordinary pirate; he only attacks merchant ships. Why would he need the papers, which, by the way, only contained bookkeeping information?";
			link.l1 = "";
			link.l1.go = "ArestLucas_10";		
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_10":
			StartInstantDialog("Lucas", "ArestLucas_11", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_11":
			dialog.text = "Monsieur, le courrier transportait également d'autres documents importants de la Compagnie - pas seulement les rapports habituels. Et maintenant, ils sont tous entre les mains des Britanniques. C'est pourquoi j'ai décidé de mettre Beck en état d'arrestation.";
			link.l1 = "";
			link.l1.go = "ArestLucas_12";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));			
		break;
		
		case "ArestLucas_12":
			StartInstantDialog("Stivesant", "ArestLucas_13", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_13":
			dialog.text = "Merde ! C'est une véritable usurpation de pouvoir ! As-tu vraiment compris ce que tu fais, Lucas ? Où est le capitaine de la brigantine courrier ?";
			link.l1 = " ";
			link.l1.go = "ArestLucas_14";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 4.5);
		break;
		
		case "ArestLucas_14":
			StartInstantDialog("Lucas", "ArestLucas_15", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_15":
			dialog.text = "Il est parti pour Philipsburg, Monsieur.";
			link.l1 = "Bonjour, mon ami.";
			link.l1.go = "ArestLucas_16";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));	
		break;
		
		case "ArestLucas_16":
			StartInstantDialog("Stivesant", "ArestLucas_17", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_17":
			dialog.text = "D'accord, alors. J'ai donné l'ordre de libérer Beck. Il sera amené ici et ensuite, nous discuterons tous les trois.";
			link.l1 = "";
			link.l1.go = "ArestLucas_18";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_18":
			StartInstantDialog("Lucas", "ArestLucas_19", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_19":
			dialog.text = "D'accord, ça ne me dérange pas. Nous trois - très bien. Parlons.";
			link.l1 = "";
			link.l1.go = "ArestLucas_20";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));	
		break;
		
		case "ArestLucas_20":
			DialogExit();
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "governor1", "DoubleTalkWithLucas", -1.0);
			locCameraFromToPos(4.70, 2.92, -4.19, false, 3.60, -0.70, 5.00);
			DoQuestCheckDelay("PiterTalkWithLucas_2", 4.5);
		break;
		
		case "ArestLucas_40":
			dialog.text = "Tu paieras pour ton anarchie, Rodenburg ! Tes accusations sont absurdes. Tu ne m'as même pas laissé voir le capitaine de la brigantine ! Tu n'as présenté aucune preuve, toutes les accusations viennent de toi personnellement.\nJe jure devant le Seigneur, je suis innocent ! Je n'ai pas et n'ai jamais eu de contact avec les Britanniques !";
			link.l1 = "";
			link.l1.go = "ArestLucas_41";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_41":
			StartInstantDialog("Lucas", "ArestLucas_42", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_42":
			dialog.text = "Ah, vraiment ? Alors comment Fleetwood a-t-il découvert notre brigantin et qu'elle n'avait pas seulement les documents habituels à bord ?";
			link.l1 = "";
			link.l1.go = "ArestLucas_43";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Villemstad_Mayor"));
		break;
		
		case "ArestLucas_43":
			dialog.text = "...";
			link.l1 = "Rodenburg ment. Richard Fleetwood n'aurait pas pu attaquer le brigantin courrier.";
			link.l1.go = "ArestLucas_44";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			sld = characterFromId("Stivesant");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			sld = characterFromId("Villemstad_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "ArestLucas_44":
			dialog.text = "Et qui êtes-vous donc, monsieur ? Sur quelles bases faites-vous de telles déclarations ?";
			link.l1 = "Mon nom est "+GetFullName(pchar)+"J'ai personnellement éliminé le capitaine Fleetwood en l'attirant dans un piège. Sa carcasse est dévorée par les mouettes sur les côtes des Turks. Les autorités n'ont pas su nous protéger, nous les marchands hollandais, de son agression, alors je l'ai achevé moi-même. Et cela s'est produit avant que le brigantin courrier ne soit pillé...";
			link.l1.go = "ArestLucas_46";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "ArestLucas_46":
			dialog.text = "";
			link.l1 = "Fleetwood n'aurait tout simplement pas pu le faire, il était déjà mort. J'ai appris des gens du coin à la taverne que Mathias Beck avait été arrêté, alors j'ai décidé d'enquêter sur l'affaire, car j'ai toujours cru que monsieur Beck est un homme de réputation cristalline...";
			link.l1.go = "ArestLucas_47";			
		break;
		
		case "ArestLucas_47":
			dialog.text = "";
			link.l1 = "Les gens du port m'ont dit que vous aviez chargé votre chébec avec toutes sortes de criminels et de mercenaires, les gardes de la Compagnie sont restés à terre. J'ai suivi votre navire et je l'ai capturé, tuant tous les bandits que vous aviez engagés. J'ai interrogé le capitaine Longway, en échange de sa liberté, il m'a tout raconté, Mynheer Rodenburg...";
			link.l1.go = "ArestLucas_48";			
		break;
		
		case "ArestLucas_48":
			dialog.text = "";
			link.l1 = "Vous projetiez de prendre le pouvoir sur Curaçao et avez ordonné à Longway de couler le galion de mynheer Stuyvesant. Connaissant vos méthodes, je suis sûr que le pauvre capitaine de la brigantine est mort. Vous devez avoir organisé une attaque contre le navire de messagerie pour créer un précédent, ai-je raison? Et cet acte a été mené par votre assassin, appelé Jacob van Berg? Longway m'a beaucoup parlé de cet homme.";
			link.l1.go = "ArestLucas_49";			
		break;
		
		case "ArestLucas_49":
			dialog.text = "Ça ... c'est un mensonge éhonté ! De quoi parlez-vous, Monsieur ? Qui diable êtes-vous ?";
			link.l1 = "Je suis un capitaine indépendant qui voulait nettoyer la mer et la terre de ce gredin de Fleetwood et qui s'est engagé dans vos intrigues politiques ! J'ai averti monsieur Stuyvesant du danger qu'il courait. Et je suis ici pour mettre fin à vos déprédations sur Curaçao - avec les autorités légales !";
			link.l1.go = "ArestLucas_50";			
		break;
		
		case "ArestLucas_50":
			dialog.text = "Quelle insolence ! Vous répondrez de vos paroles, Mynheer 'capitaine indépendant' ! Vous...";
			link.l1 = "";
			link.l1.go = "ArestLucas_51";
		break;
		
		case "ArestLucas_51":
			StartInstantDialog("Stivesant", "ArestLucas_52", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_52":
			dialog.text = "Assez, Lucas. Tu paieras pour tes crimes! J'ai assez entendu et vu. Lucas Rodenburg, je vous arrête pour une tentative de meurtre sur la vie du directeur de la Compagnie, pour une tentative de prise de pouvoir par la force et pour le soupçon de meurtre du capitaine du navire courrier.\nDe plus, je suis sûr que nous découvrirons plus sur les parties intéressantes de votre biographie lors de l'enquête officielle. Vous serez mis en détention et livré à Amsterdam où vous serez poursuivi. Emmenez-le!";
			link.l1 = "Bonjour, mon ami.";
			link.l1.go = "ArestLucas_53";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
			sld = characterFromId("Lucas");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromID("Stivesant"));					
		break;
		
		case "ArestLucas_53":
			StartInstantDialog("Lucas", "ArestLucas_54", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_54":
			dialog.text = "Mais...";
			link.l1 = " ";
			link.l1.go = "ArestLucas_55";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));			
		break;
		
		case "ArestLucas_55":
			DialogExit();
			LAi_ActorTurnToCharacter(pchar, characterFromID("Lucas"));
			sld = characterFromId("Lucas");
			LAi_SetImmortal(sld, true);//защита от хитреца
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "goto", "goto6");
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "LucasGoToPrison", -1);
			for (i=3; i<=5; i++)
			{
			sld = characterFromId("StivesantGuard_"+i);
			LAi_ActorFollow(sld, characterFromID("Lucas"), "", -1);
			}
			LAi_SetActorType(PChar);
			locCameraFromToPos(4.70, 2.92, -4.19, false, -4.60, -1.70, 5.50);
			DoQuestFunctionDelay("SecondDayInVillemstad", 6.0);
		break;
		
		case "Stivesant_10":
			dialog.text = "Capitaine "+GetFullName(pchar)+"Au nom de l'administration de la colonie de Willemstad, je vous demande aimablement d'accepter notre sincère gratitude pour vos actions, qui nous ont aidés à mettre cet dangereux criminel sous les verrous. Je tiens également à vous remercier personnellement, car je vous dois probablement la vie.";
			link.l1 = "J'ai agi pour le bien de toutes les colonies hollandaises, Monsieur.";
			link.l1.go = "Stivesant_11";			
		break;
		
		case "Stivesant_11":
			dialog.text = "Votre modestie impose le respect, mon ami. Maintenant, je voudrais régler quelques formalités : puisque vous avez capturé le Meifeng uniquement pour de bonnes intentions et en cas de nécessité absolue, il ne peut y avoir aucune réclamation. Mais ce navire appartient à la Compagnie et je vous prie de bien vouloir le retourner.";
			link.l1 = "Certainement, Monsieur.";
			link.l1.go = "Stivesant_12";			
		break;
		
		case "Stivesant_12":
		//удаляем Мейфенг
		DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//удаляем атрибут квестового корабля
		if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
		{
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "A boat";
			SetBaseShipData(pchar);
			SetCrewQuantityOverMax(PChar, 0);//сажаем на тартану
		}
		else
		{
			for(i = 1; i < COMPANION_MAX; i++)
			{
			int iTemp = GetCompanionIndex(PChar, i);
			if(iTemp > 0)
				{
				sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
					{
						pchar.questTemp.HWIC.Self.CompanionIndex = sld.Index;
						sld = GetCharacter(sti(pchar.questTemp.HWIC.Self.CompanionIndex));
						RemoveCharacterCompanion(PChar, sld);
						AddPassenger(PChar, sld, false);
					}
				}
			}
		}
			dialog.text = "Je vous prie de venir à ma résidence demain - vous serez récompensé au nom de la République des Provinces Libres pour vos actions dans son meilleur intérêt. Je vous prie instamment de ne pas quitter la ville.";
			link.l1 = "D'accord, Mynheer. Je passerai demain.";
			link.l1.go = "Stivesant_13";			
		break;
		
		case "Stivesant_13":
			DialogExit();
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.dialog.currentnode = "Bek_2";
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "Bek_2":
			dialog.text = "Je tiens aussi à vous remercier personnellement, Capitaine, pour votre esprit d'entreprise et votre assistance opportune. N'oubliez pas de revenir ici demain, je vous préparerai un cadeau précieux.";
			link.l1 = "Merci, Monsieur Beck. J'y serai !";
			link.l1.go = "Bek_3";			
		break;
		
		case "Bek_3":
			DialogExit();
			pchar.quest.Award_FromPiter.win_condition.l1 = "Timer";
			pchar.quest.Award_FromPiter.win_condition.l1.date.hour  = 9.0;
			pchar.quest.Award_FromPiter.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Award_FromPiter.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Award_FromPiter.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Award_FromPiter.function = "OpenResidenceDoor";
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Villemstad_town", "reload5_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload10_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload3_back", true);//закрыть вход в резиденцию
			LocatorReloadEnterDisable("Villemstad_town", "reloadR2", true);//закрыть боковой вход в резиденцию
			AddQuestRecord("Holl_Gambit", "3-53");
			DoQuestReloadToLocation("Villemstad_prison", "goto", "goto23", "TalkWithLucasPrisoner");
			for (i=4; i<=5; i++)
			{
				sld = characterFromId("StivesantGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
		break;
		
		case "Stivesant_14":
			dialog.text = ""+GetFullName(pchar)+", au nom de la République des Provinces Libres, vous recevez par la présente une arme personnelle et la somme de 100 000 pesos pour l'initiative prise dans la liquidation de l'ennemi de tous les Néerlandais, le criminel d'État Richard Fleetwood. Félicitations !";
			link.l1 = "Merci, Monsieur Styuvesant !";
			link.l1.go = "Stivesant_15";			
		break;
		
		case "Stivesant_15":
			dialog.text = "Aussi, pour un courage sans précédent, pour avoir déjoué un complot traître au sein de la Compagnie et pour l'opération risquée de capture de l'ancien vice-président de la Compagnie, vous êtes récompensé de 150 000 pesos. Vous aurez également la permission de signer des contrats avec la Compagnie néerlandaise des Indes occidentales\nJe suis sûr que notre nouveau vice-directeur trouvera un emploi bien rémunéré pour un capitaine aussi brave que vous.";
			link.l1 = "Merci ! Je garderai cela à l'esprit.";
			link.l1.go = "Stivesant_16";			
		break;
		
		case "Stivesant_16":
			AddMoneyToCharacter(pchar, 250000);
			GiveItem2Character(pchar, GetGeneratedItem("blade_16")); // belamour legendary edition используем GetGeneratedItem иначе пачка одинаковых клинков из первой части массива
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			dialog.text = "Sachez que vous pouvez toujours compter sur mon assistance dans toutes vos affaires tant que vous agissez du côté et dans l'intérêt de la Hollande. Maintenant, écoutons ce que le gouverneur de Willemstad, Matthias Beck, a à dire.";
			link.l1 = "";
			link.l1.go = "Stivesant_17";			
		break;
		
		case "Stivesant_17":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "Bek_4";
			LAi_ActorDialog(sld, pchar, "", -1, 0);		
		break;
		
		case "Bek_4":
			dialog.text = "J'exprime ma sincère gratitude, Capitaine, pour votre courage et votre perspicacité à découvrir un complot contre l'État. Je voudrais vous offrir cet instrument de navigation précieux, qui est inestimable pour tout homme de guerre.";
			link.l1 = "Merci, Monsieur Beck";
			link.l1.go = "Bek_5";			
		break;
		
		case "Bek_5":
			GiveItem2Character(pchar, "bussol");
			dialog.text = "Je voudrais que tu saches : tu es mon ami maintenant, et cela signifie beaucoup. Tu seras toujours un invité bienvenu dans ma résidence. Passe quand tu veux et pour n'importe quelle raison - je serai heureux de t'apporter toute l'aide dont tu pourrais avoir besoin.";
			link.l1 = "Je suis heureux d'entendre cela, Monsieur!";
			link.l1.go = "Bek_6";			
		break;
		
		case "Bek_6"://наведем порядок в городе
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-54");
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetHuberStayType(sld);
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("StivesantGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
			sld = characterFromId("Stivesant");
			LAi_ActorGoToLocator(sld, "goto", "goto6", "StivesantSitDown", -1);
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			DelMapQuestMarkCity("Villemstad");
		break;
		
		case "Bek_7":
			dialog.text = "Hollande est fière de vous, Monsieur. Des capitaines comme vous sont la colonne vertébrale de la flotte néerlandaise dans les Caraïbes. Voici pour vous, veuillez accepter votre récompense.";
			link.l1 = "Merci, Monsieur. Je suis honoré de servir la Hollande !";
			link.l1.go = "Bek_8";
		break;
		
		case "Bek_8":
			TakeNItems(pchar, "gold_dublon", 1000);
			ChangeCharacterComplexReputation(pchar,"authority", 5);
			ChangeCharacterNationReputation(pchar, HOLLAND, 20);
			DialogExit();
			sld = characterFromId("Lucas");
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "LucasAward_2";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Stivesant_18":
			dialog.text = "Je suis heureux de te voir. Comment vas-tu ?";
			link.l1 = "Je vais bien. Je suis juste passé te voir.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Stivesant_18";
		break;
		
		// Jason НСО
		case "Stivesant_19":
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
			{
				dialog.text = "Regardez qui voilà ! C'est "+GetFullName(pchar)+"Nous avons récemment envoyé nos chasseurs de têtes, qui devaient vous amener ici. Et ce service nous a coûté cher.";
				link.l1 = "Hum... Je devrais y aller...";
				link.l1.go = "arest";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (pchar.questTemp.Patria == "epizode_4" && IsUniformEquip())
			{
				dialog.text = "Êtes-vous capitaine de la Marine française ? Bien, je suis à court de temps, mais je vais écouter ce que vous avez à dire. Qu'est-ce qui vous amène ici ?";
				link.l1 = "Monsieur Stuyvesant, je viens de Saint-Christophe avec un message du gouverneur général des colonies françaises, le Chevalier de Poincy.";
				link.l1.go = "Stivesant_20";
			}
			else
			{
				dialog.text = "Excusez-moi, Capitaine, mais je suis extrêmement occupé en ce moment et je ne peux pas vous consacrer assez de temps. Parlez à mynheer Mathias Beck, laissez-le entendre ce que vous avez à dire.";
				link.l1 = "Hmm...";
				link.l1.go = "Stivesant_19_1";
			}
		break;
		
		case "Stivesant_19_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_19";
		break;
		
		case "Stivesant_20":
			sld = characterFromId("Patria_FlautCap");
			dialog.text = "Du chevalier de Poincy ? Je ne m'attendais pas à ce que cela prenne si peu... euh... comment va le chevalier ?";
			link.l1 = "Tout va bien, Monsieur. Monsieur de Poincy m'a ordonné de vous livrer cette lettre. Mon autre tâche était d'escorter '"+sld.ship.name+"avec une cargaison pour votre compagnie au port de Willemstad. Le navire est à quai et la cargaison n'a pas été endommagée.";
			link.l1.go = "Stivesant_21";
		break;
		
		case "Stivesant_21":
			dialog.text = "Une flotte avec une cargaison pour notre compagnie ? Intriguant... Et la lettre, Capitaine ?";
			link.l1 = "  Tenez. Je vous en prie, prenez-le. ";
			link.l1.go = "Stivesant_22";
		break;
		
		case "Stivesant_22":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Hmmm... (lisant). Une inspection de la mère patrie... Ahem... Hein, eh bien... c'est intéressant, hé-hé... Au fait, Capitaine, j'ai entendu dire que la France est en guerre avec l'Espagne dans les Caraïbes ? Le siège et le pillage du fort de San Jose, la destruction de l'escadre de guerre espagnole au large de la côte est de Cuba...";
			link.l1 = "Au large de la côte ouest d'Hispaniola près de Port-au-Prince, Monsieur. Et le seul but du siège de San Jose était d'obtenir une compensation financière des Espagnols pour leur attaque sur Saint-Pierre. Nous sommes en mauvais termes avec l'Espagne depuis un certain temps... Quand devrais-je revenir pour recueillir la réponse ?";
			link.l1.go = "Stivesant_23";
		break;
		
		case "Stivesant_23":
			dialog.text = "Je ne vous retiendrai pas, Capitaine, vous êtes un homme de guerre, vous avez probablement beaucoup d'affaires et je suis sûr que le Chevalier attend impatiemment votre retour. Soyez si aimable et attendez ici, dans le salon, pendant deux heures, le temps que je rédige une réponse à cette lettre. Asseyez-vous et reposez-vous ici, on vous servira du vin ou du rhum, si vous le souhaitez...";
			link.l1 = "Ma gratitude, Monsieur, je préférerais un verre de bon vin...";
			link.l1.go = "Stivesant_24";
		break;
		
		case "Stivesant_24":
			chrDisableReloadToLocation = true;//закрыть локацию
			pchar.quest.Patria_CureerTimeOver.over = "yes"; //снять таймер
			pchar.quest.Patria_CureerFail.over = "yes"; //снять прерывание
			sld = characterFromId("Patria_FlautCap");
			RemoveCharacterCompanion(pchar, sld);
			sld.lifeday = 0;
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_25";
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "Villemstad_townhall", "goto", "goto6");
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "Patria_StivesantWait", -1);
			pchar.questTemp.Patria = "epizode_4_return";
		break;
		
		case "Stivesant_25":
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_2");
			dialog.text = "La réponse pour monsieur de Poincy est prête. Voici, veuillez la prendre... Bonne chance, Capitaine.";
			link.l1 = "Merci, Monsieur. Adieu !";
			link.l1.go = "Stivesant_26";
		break;
		
		case "Stivesant_26":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_19";
			chrDisableReloadToLocation = false;
			AddQuestRecord("Patria", "23");
			SetFunctionTimerCondition("Patria_CureerBackOver", 0, 0, 31, false);
		break;
		
		case "Stivesant_27":
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
			{
				dialog.text = "Regardez qui voilà ! C'est "+GetFullName(pchar)+". Nous avons récemment envoyé nos chasseurs de têtes, qui devaient vous amener ici. Et ce service a coûté cher.";
				link.l1 = "Hum... Je devrais y aller...";
				link.l1.go = "arest";
				break;
			}
			if (pchar.questTemp.Patria == "epizode_6" && IsUniformEquip())
			{
				dialog.text = "Tu es encore venu avec un message du gouverneur général Philippe de Poincy, n'est-ce pas ?";
				link.l1 = "Oui, Monsieur Stuyvesant. Sur les rives de Saint-Martin, il y a eu un malentendu désagréable - un navire transportant l'inspecteur de Paris, le Baron Noel Forget, a été tiré par le fort de Philipsburg, et...";
				link.l1.go = "Stivesant_28";
			}
			else
			{
				dialog.text = "Excusez-moi, Capitaine, mais je suis extrêmement occupé en ce moment et je ne peux pas vous consacrer suffisamment de temps. Parlez à mynheer Mathias Beck, laissez-le entendre ce que vous avez à dire.";
				link.l1 = "Hmm...";
				link.l1.go = "Stivesant_27_1";
			}
		break;
		
		case "Stivesant_27_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_27";
		break;
		
		case "Stivesant_28":
			if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "self_win")
			{
				dialog.text = "Et c'est pourquoi vous êtes ici, Capitaine. Je ne vais pas engager de discussions diplomatiques : dites au Chevalier qu'il n'est plus responsable de Sint Maarten. Assez de lui. Et en ce qui concerne l'inspection de l'État parent - qu'il trouve quelque chose, ce n'était jamais difficile pour de Poincy de tout bouleverser.";
				link.l1 = "Est-ce exactement ce que je devrais lui dire?";
				link.l1.go = "Stivesant_29";
			}
			else
			{
				dialog.text = "Et c'est pourquoi vous êtes ici, Capitaine. Je ne vais pas entrer dans des discussions diplomatiques : votre suzerain a été bien trop gourmand sur Sint Maarten ces derniers temps, alors il est temps de tempérer sa faim insatiable. Et je crois qu'il le comprend parfaitement. Quant à vous, Capitaine Charles de Maure, nous avons également des questions sur les événements récents liés au bandit britannique du nom de Richard Fleetwood, donc vous devrez rester ici un moment.\nSergent ! Prenez les armes du capitaine et amenez-le au bureau du commandant !";
				link.l1 = "Retarder un officier français en service est inacceptable !";
				link.l1.go = "Stivesant_31";
			}
		break;
		
		case "Stivesant_29":
			dialog.text = "Je n'aurais pas pu mieux dire, Capitaine. Votre commandant comprendra tout, mais vous n'avez pas besoin d'entrer dans les détails, cela ne changera rien. Je vous souhaite tout le meilleur. Sergent, conduisez Monsieur Charles de Maure vers la sortie !";
			link.l1 = "... ";
			link.l1.go = "Stivesant_30";
		break;
		
		case "Stivesant_30":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload3", "Patria_DiplomatGetOut");
		break;
		
		case "Stivesant_31":
			dialog.text = "Malheureusement, j'ai une opinion différente. Sergent ! En cas de résistance, utilisez la force !";
			link.l1 = "Tu ne sais simplement pas encore à qui tu as affaire, Mynheer ...";
			link.l1.go = "Stivesant_32";
		break;
		
		case "Stivesant_32":
			DialogExit();
			Patria_DiplomatFight();
		break;
		
		case "Stivesant_33":
			dialog.text = "C'est un peu étrange de vous voir, Capitaine Charles de Maure, dans ce rôle ... J'espère que vous pouvez garantir l'immunité à ceux qui viennent à vous pour des négociations..";
			link.l1 = "Vous pouvez en être sûr, Monsieur Stuyvesant.";
			link.l1.go = "Stivesant_34";
		break;
		
		case "Stivesant_34":
			dialog.text = "Alors, pouvez-vous me donner l'opportunité de lire l'accord que vous avez préparé ? Si je comprends bien, il contient le contenu de la lettre ?";
			link.l1 = "Précisément, monsieur, mais sous une forme officielle. Du côté de la France - restauration des relations à un niveau neutre, renonciation à toute revendication sur l'île de Saint-Martin. Du côté de l'Angleterre - la fin de la guerre commerciale. Tous les détails sont décrits ici ... Et, bien sûr, une compensation financière pour les dommages que nous avons subis en raison des actions militaires que vous avez initiées.";
			link.l1.go = "Stivesant_35";
		break;
		
		case "Stivesant_35":
			dialog.text = "S'il vous plaît, ayez la gentillesse de me donner le document.";
			link.l1 = "Bien sûr.";
			link.l1.go = "Stivesant_36";
		break;
		
		case "Stivesant_36":
			dialog.text = "...(lecture)...";
			link.l1 = "... ";
			link.l1.go = "Stivesant_37";
		break;
		
		case "Stivesant_37":
			LAi_Fade("", "");
			dialog.text = "Puisque vous ne m'avez pas laissé le choix, je signerai cet accord. Mais pour moi, la protection de Willemstad et de ses habitants est de la plus haute importance";
			link.l1 = "Ensuite, nous validerons les trois exemplaires par des signatures. Je suis autorisé par le gouverneur général Philippe de Poincy à approuver le document pour le côté français, le colonel Doily le signera pour l'Angleterre.";
			link.l1.go = "Stivesant_38";
		break;
		
		case "Stivesant_38":
			dialog.text = "...(signe)...";
			link.l1 = "Parfait ! Maintenant, nous devrions signer ceci...";
			link.l1.go = "Stivesant_39";
		break;
		
		case "Stivesant_39":
			LAi_Fade("", "");
			dialog.text = "Alors, je crois que vous lèverez le siège maintenant ?";
			link.l1 = "Sans aucun doute. J'espère que toutes les conditions de l'accord seront respectées par la partie néerlandaise sans violations.";
			link.l1.go = "Stivesant_40";
		break;
		
		case "Stivesant_40":
			dialog.text = "S'il n'y a pas de violations de la part de l'Angleterre ou de la France, alors nous respecterons les termes du contrat, ne vous inquiétez pas.";
			link.l1 = "Il vaut toujours mieux échanger que se battre, Monsieur Stuyvesant. Et maintenant, vous pouvez retourner à Willemstad en toute sécurité. Le siège sera levé et notre escadron quittera bientôt les eaux de Curaçao.";
			link.l1.go = "Stivesant_41";
		break;
		
		case "Stivesant_41":
			DialogExit(); // Стайвесант уходит, подходит д'Ойли
			Patria_CuracaoStivesantGo();
		break;
		
		case "Stivesant_42":
			dialog.text = "Alors, êtes-vous le Baron Noel Forget? Hein, et vous devez être Monsieur Charles de Maure en personne ! Salutations, Vice-amiral ! Il y a une raison pour laquelle vous êtes connu comme le plus rusé intrigant de l'archipel - on ne sait jamais de quel côté vous êtes à ce moment-là...";
			link.l1 = "Le vice-amiral est du côté du roi et du vôtre sincèrement, son représentant légitime, en ce moment.";
			link.l1.go = "Stivesant_43";
		break;
		
		case "Stivesant_43":
			dialog.text = "Le Roi est loin d'ici, et la France aussi, Baron, mais Saint-Christophe et le Chevalier de Poincy sont proches. Il est le véritable maître des colonies françaises. De facto... Cependant, êtes-vous ici pour obtenir quelque chose qui compromet de Poincy aux yeux du ministre des finances ?";
			link.l1 = "Précisément, Monseigneur.";
			link.l1.go = "Stivesant_44";
		break;
		
		case "Stivesant_44":
			dialog.text = "J'ai de tels documents. C'est tout un registre avec mes comptes et ceux de de Poincy pour la mine et d'autres affaires. Vous y trouverez également tout un tas de papiers liés à cette affaire, avec la signature personnelle de Philippe de Poincy. Je vous garantis que le contenu de ces papiers, entre les mains d'une personne intéressée, fera couler le Chevalier plus profondément que le fond de la mer des Caraïbes.";
			link.l1 = "Que veux-tu pour ce registre ?";
			link.l1.go = "Stivesant_45";
		break;
		
		case "Stivesant_45":
			dialog.text = "Je le vends pour une chanson. Seulement un million de pesos en argent.";
			link.l1 = "Un million de pesos?!!";
			link.l1.go = "Stivesant_46";
		break;
		
		case "Stivesant_46":
			dialog.text = "C'est exact, Baron. Cette somme couvrira au moins partiellement les pertes causées par la guerre récente. Je vais vous donner un conseil : tournez-vous vers Monsieur Charles de Maure. Pendant son service pour de Poincy et euh... d'autres personnes, il a probablement amassé une énorme fortune, et obtenir un million ne sera pas un problème pour lui. J'en suis presque sûr.\nJe vous accorde un délai - un mois. Après ce temps, si vous n'apportez pas la somme indiquée, j'enverrai une lettre au Chevalier, dans laquelle je décrirai les détails de votre visite chez moi. Vous pouvez deviner ce qui se passera ensuite.";
			link.l1 = "Vous me faites chanter! Vous devez comprendre que je ne peux pas avoir un million dans les colonies!";
			link.l1.go = "Stivesant_47";
		break;
		
		case "Stivesant_47":
			dialog.text = "Bien sûr, je comprends. Par conséquent, je vous ai immédiatement indiqué la personne qui possède ce million. Si Monsieur de Maure refuse, il vaut mieux pour vous, Baron, de prendre la mer vers l'Europe avant que le Chevalier ne reçoive ma lettre, sinon vous risquez de rester ici pour toujours. Quant à Monsieur de Maure... bien sûr, il perdra son grade d'amiral, mais il s'en sortira... et peut-être même se débarrassera-t-il de de Poincy avec ses méthodes, cela me convient parfaitement.\nEh bien, messieurs, vous m'avez entendu. Je vous attendrai avec le million dans un mois à ma résidence. Entrée et sortie libres garanties.";
			link.l1 = "... ";
			link.l1.go = "Stivesant_48";
		break;
		
		case "Stivesant_48":
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			locCameraTarget(pchar);
			locCameraFollow();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = true;
			bDisableCharacterMenu = false;
			sld = CharacterFromID("Noel");
			sld.dialog.currentnode = "noel_84";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			sld = CharacterFromID("Stivesant");
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Patria_CondotierStivesantInHall", 12.0);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("Stivesant_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			}
		break;
		
		case "Stivesant_49":
			if (sti(pchar.money) >= 1000000)
			{
				dialog.text = "Je n'en doutais même pas, Vice-Amiral Charles de Maure, que vous m'apporteriez cet argent. Peut-être même que je vous ai demandé trop peu, mais tant pis... Le Baron n'est qu'un pion dans votre prochain jeu, n'est-ce pas ? Le grade et l'argent ne vous suffisent pas, maintenant vous voulez prendre la place de de Poincy, ai-je raison ? Vous devez admettre qu'un million est une petite somme pour le poste de Gouverneur Général des colonies françaises ! Vous récupérerez cet argent en quelques mois, vu votre poigne de fer.";
				link.l1 = "Prenez votre million, Mynheer. J'aimerais recevoir mon livre de comptes promis.";
				link.l1.go = "Stivesant_50";
			}
			else
			{
				dialog.text = "Vous feriez mieux de vous concentrer sur la collecte du million, Monsieur, au lieu de perdre votre temps en visites inutiles.";
				link.l1 = "...";
				link.l1.go = "Stivesant_49_1";
			}
		break;
		
		case "Stivesant_49_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_49";
		break;
		
		case "Stivesant_50":
			pchar.quest.Patria_CondotierStivesantTimeOver.over = "yes"; // снять таймер
			AddMoneyToCharacter(pchar, -1000000);
			GiveItem2Character(pchar, "Reserve_item_01");
			ref itm = ItemsFromID("Reserve_item_01");
			itm.picIndex = 15;
			itm.picTexture = "ITEMS_26";
			itm.price = 0;
			itm.Weight = 2.0;
			itm.name = "itmname_Reserve_item_01_1";
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_4");
			dialog.text = "Bien sûr, Vice-Amiral. Et ne froncez pas les sourcils : quand vous deviendrez Gouverneur Général, vous verrez que la Compagnie néerlandaise des Indes occidentales est un partenaire commercial plus rentable que les Britanniques cupides et belliqueux. Ne savez-vous pas que si vous donnez un doigt à un Britannique, il prendra toute la main ? Sinon, vous l'apprendrez à vos dépens. Donc je ne vous dis pas encore adieu. Gardez vos papiers. J'espère que votre baron est assez compétent pour vaincre le Chevalier.";
			link.l1 = "Je vous remercie. Adieu, Mynheer Stuvesant.";
			link.l1.go = "Stivesant_51";
		break;
		
		case "Stivesant_51":
			DialogExit();
			AddQuestRecord("Patria", "84");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
			pchar.quest.Patria_CondotierCabin.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierCabin.win_condition.l1.location = "Curacao";
			pchar.quest.Patria_CondotierCabin.function = "Patria_CondotierCabin";
		break;
		
		case "vanberg_sold":
			dialog.text = "Ha-ha-ha ! Regarde ça ! Jacob avait raison, comme toujours - ce renard est allé sur l'île pour une bonne raison. Il semble qu'il y ait tout un tas d'or dans le coffre. Très imprudent de ta part de venir ici seul, camarade. Mais encore une fois, cela rend notre travail bien plus facile !";
			link.l1 = "Ces salopards m'ont retrouvé ! Je ne l'avais pas vu venir... Mais je ne serai pas une proie facile !";
			link.l1.go = "vanberg_sold_1";			
		break;
		
		case "vanberg_sold_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("vanberg_sold_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PrepareMassakraInShore");
			AddDialogExitQuest("MainHeroFightModeOn");			
		break;
		
		case "Abihouselady":
			dialog.text = "Vous cherchez quelqu'un?";
			link.l1 = "Oui, c'est moi. Où sont Solomon et Abigail Shneur ?";
			link.l1.go = "Abihouselady_1";			
		break;
		
		case "Abihouselady_1":
			dialog.text = "Ils ne vivent plus ici. Ils ne pouvaient tout simplement pas se permettre cet endroit. Abigail, pauvre fille, travaille comme une des servantes du gouverneur. Elle travaille dur chaque jour pour gagner sa vie et celle de son père. Solomon boit à la taverne chaque jour, il ne peut supporter ce qui leur est arrivé. Ils vivent maintenant dans une petite cabane non loin de la mer...";
			link.l1 = "Oh... D'accord, merci pour l'information. Je dois y aller.";
			link.l1.go = "Abihouselady_2";
		break;
		
		case "Abihouselady_2":
			DialogExit();
			NextDiag.CurrentNode = "Abihouselady_3";
		break;
		
		case "Abihouselady_3":
			dialog.text = "Que souhaiteriez-vous savoir d'autre, Mynheer ?";
			link.l1 = "Rien, peu importe.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abihouselady_3";
		break;
		
		//удаление Мейфенг при провале квеста
		case "TempOffGuard":
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//удаляем атрибут квестового корабля
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
				pchar.Ship.name = "A boat";
				SetBaseShipData(pchar);
				SetCrewQuantityOverMax(PChar, 0);//сажаем на тартану
			}
			else
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
						iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							pchar.questTemp.HWIC.Self.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Self.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			dialog.text = "Capitaine, vous avez détourné un navire de la Compagnie néerlandaise des Indes occidentales. Je suis autorisé à le confisquer et à user de la force en cas de résistance. C'est un ordre de Peter Stuyvesant.";
			link.l1 = "Eh bien, si c'est un ordre de Peter Stuyvesant lui-même... Je ne ferai pas la guerre à la Hollande pour un navire. Prenez-le.";
			link.l1.go = "TempOffGuard_1";			
		break;
		
		case "TempOffGuard_1":
			dialog.text = "Bien pour vous de montrer de la raison.";
			link.l1 = "...";
			link.l1.go = "TempOffGuard_2";
		break;
		
		case "TempOffGuard_2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");
		break;
		
		// Jason НСО
		case "arest":
			dialog.text = "Bien sûr, il est temps de partir, vous serez même accompagné. Gardes ! Attrapez-le !";
		    link.l1 = "Fais-moi !";
		    link.l1.go = "fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Eh, écoutez-moi bien ! En tant que citoyen de cette ville, je vous demande aimablement de ne pas vous promener avec une lame dégainée.","Vous savez, en tant que citoyen de cette ville, je vous prie de ne pas vous promener avec une lame dégainée.");
			link.l1 = LinkRandPhrase("D'accord.","D'accord.","Comme vous dites...");
			link.l1.go = "exit";
		break;
	}
}
