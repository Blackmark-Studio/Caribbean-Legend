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
			dialog.text = "Ein Fehler. Informiert die Entwickler.";
			link.l1 = "Ich werde!";
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
			dialog.text = "Welch ein Glück! Kapitän, ich brauche ganz dringend eine Eskorte nach Philipsburg...";
			link.l1 = "Bist du Balthazar Ridderbock?";
			link.l1.go = "Baltazar_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Baltazar_1":
			dialog.text = "Was zur Hölle, ich bin schon berühmter als der Vizekönig! Wer bist du? Was willst du?";
			link.l1 = "Ich bin Kapitän "+GetFullName(pchar)+". Ich wurde von Lucas Rodenburg zu Ihnen geschickt. Ich bin befugt, Sie und Ihr Schiff unter meinen Schutz zu nehmen.";
			link.l1.go = "Baltazar_2";			
		break;
		
		case "Baltazar_2":
			dialog.text = "Oh, Mynheer Rodenburg muss meine Bitten um Hilfe gehört haben! Sie sehen, es gibt einen Freibeuter...";
			link.l1 = "Lassen wir die Details Ihrer Geschichte aus, ich kenne sie bereits.";
			link.l1.go = "Baltazar_3";			
		break;
		
		case "Baltazar_3":
			dialog.text = "Natürlich! Ich habe schon zu viel Zeit verloren... Ich muss spätestens in zwei Wochen in Philipsburg ankommen.";
			link.l1 = "Dann geh zu deinem Schiff und bereite dich auf das Segeln vor. Wir setzen sofort Segel!";
			link.l1.go = "Baltazar_4";			
		break;
		
		case "Baltazar_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 4);
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, int(npchar.index));
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
			dialog.text = "Vielen Dank für Ihre Hilfe, Kapitän! Ihre Schutzmaßnahmen hätten nicht zu einem besseren Zeitpunkt kommen können, bitte nehmen Sie meinen Dank und diese 5 000 Pesos an.";
			link.l1 = "Hmm... Das ist nicht gerade eine großzügige Belohnung für das Retten eines Lebens...";
			link.l1.go = "Baltazar_6";			
		break;
		
		case "Baltazar_6":
			dialog.text = "Darüber hinaus werde ich, wenn ich die Gelegenheit habe, einen Brief an den Herrn Rodenburg schicken - mit der höchstmöglichen Wertschätzung für Ihre Handlungen. Ich muss jetzt gehen.";
			link.l1 = "Nun, leb wohl dann, Balthazar.";
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
			dialog.text = "Herr! Warten Sie... es sieht so aus, als hätten Sie etwas fallen gelassen...";
			link.l1 = "Was? Ah?!";
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
			dialog.text = "Entschuldigung, mein Freund - Ich musste dich leicht schlagen, damit du keinen Ärger verursachst. Ich weiß, dass dein Kopf wahrscheinlich schmerzt, aber was auch immer, du wirst überleben. Wenn es dafür Zeit gibt...";
			link.l1 = "Wer bist du, verdammt, und was geht hier vor?";
			link.l1.go = "Santiago_Trip_3";
		break;
		
		case "Santiago_Trip_3":
			dialog.text = "Ruhig, ruhig, mein Freund - sonst muss ich Sie noch einmal beruhigen. Wir wollen nicht, dass diese Pedanten hereinstürmen und mit ihren rostigen Schwertern klappern, oder? Wir müssen in Ruhe reden.";
			link.l1 = "Gib mir mein Schwert zurück, du Ficker, und wir werden ein nettes Gespräch führen, ich schwöre es!";
			link.l1.go = "Santiago_Trip_4";
		break;
		
		case "Santiago_Trip_4":
			dialog.text = "Du bist ein flinker kleiner Mann, nicht wahr? Keine Notwendigkeit jetzt Stahl zu benutzen. Sag mir, was ich wissen will und vielleicht wirst du diesen Ort heil verlassen. Bin ich klar? Lass uns also ein bisschen plaudern.\nSchweigst du? Gut, dann haben wir einen Deal. Was hast du von Rodenburg zum Bankier gebracht?";
			link.l1 = "Ein Brief.";
			link.l1.go = "Santiago_Trip_5";
		break;
		
		case "Santiago_Trip_5":
			dialog.text = "Schlau. Ich weiß, dass es kein Strauß Gänseblümchen war. Was stand in diesem Brief, Junge?";
			link.l1 = "Wie soll ich das wissen? Ich habe nicht die Gewohnheit, mir anvertraute Korrespondenz zu lesen. Vielleicht war es eine Liebesbotschaft. Sie wissen, was man über mächtige Leute sagt...";
			link.l1.go = "Santiago_Trip_6";
		break;
		
		case "Santiago_Trip_6":
			dialog.text = "...Ein ehrlicher Kapitän ist in diesen elenden Zeiten eine Seltenheit. Nun, das sind schlechte Nachrichten für dich. Was hat dieser verfluchte Bankier gesagt, als er das Paket erhalten hat? Welche Geschäfte hat er mit den Holländern?";
			link.l1 = "Sie handeln mit geschmuggeltem Parfüm aus Frankreich... oder bayerischem Kuhdreck, denke ich.";
			link.l1.go = "Santiago_Trip_7";
			link.l2 = "Die Frage ging um eine Entschädigung für etwas. Das ist alles, was ich weiß.";
			link.l2.go = "Santiago_Trip_8";
		break;
		
		case "Santiago_Trip_7":
			dialog.text = "Du bist ein tapferer Kerl... Und mit Sinn für Humor auch noch. Es wäre schade, dich zu töten. Gaston hätte dich gemocht. Obwohl... bleib vorerst hier. Ich muss etwas überprüfen, und Miguel wird sich um dich kümmern, während ich weg bin.";
			link.l1 = "Ich schwöre, 'mein Freund' - das wirst du bereuen! ";
			link.l1.go = "Santiago_Trip_9";
		break;
		
		case "Santiago_Trip_8":
			dialog.text = "Da geht der Hochmut... Wenn die Dinge düster aussehen, zeigt unser tapferer Kapitän Vernunft. Du hättest es viel früher tun können und hättest uns Zeit und Ärger erspart. Nun, ich muss etwas überprüfen, aber dann komme ich zurück und wir werden reden, falls es noch notwendig ist. Bleib vorerst hier. Miguel wird sich um dich kümmern, während ich weg bin.";
			link.l1 = "Ich schwöre, 'mein Freund' - du wirst das bereuen! ";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_9":
			dialog.text = "Aber natürlich. Halte dich still, 'Held' - vielleicht wird alles noch gut.";
			link.l1 = "...";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_10":
			dialog.text = "Bleibe hier und hoffe, dass sich deine Flexibilität rechtfertigen wird.";
			link.l1 = "...";
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
			dialog.text = "Was zum Teufel?!";
			link.l1 = "Mach dich bereit zu sterben, du Schurke!";
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
			dialog.text = "Was für ein Durcheinander! Ich habe mich gewundert, was dieser Lärm sollte. Meine Glückwünsche - du bist ein schlauer Kerl!";
			link.l1 = "Schlauer als du denkst... Mal sehen, was du gegen einen bewaffneten Gegner tun kannst!";
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
			dialog.text = "Herr Lucas Rodenburg möchte Sie sofort sehen. Kommen Sie sofort zu ihm.";
			link.l1 = "Auf meinem Weg.";
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
			dialog.text = "Was willst du von mir?";
			link.l1 = "Dein Kopf!";
			link.l1.go = "Fernando_fight";
			link.l2 = "Nichts, vergiss es.";
			link.l2.go = "exit";	
			NextDiag.TempNode = "Fernando_repeat";
		break;
		
		case "Fernando_repeat":
			dialog.text = "Bist du es schon wieder? Was willst du von mir?! Erkläre dich!";
			link.l1 = "Dein Kopf!";
			link.l1.go = "Fernando_fight";
			link.l2 = "Nichts, vergiss es.";
			link.l2.go = "exit";	
			NextDiag.TempNode = "Fernando_repeat";		
		break;
		
		case "Fernando_fight":
			chrDisableReloadToLocation = true;//выходы закроем
			LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "SPAIN_CITIZENS");
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(int(npchar.nation), RELATION_ENEMY);
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
			dialog.text = "Bist du schon wieder da? Warum schnüffelst du hier herum? Das gefällt mir überhaupt nicht. Gut, ich werde dich festnehmen und zur Untersuchung ins Kommandantenbüro schicken. Jungs, schnappt euch diesen Kerl!";
			link.l1 = "Aber ich wollte nur...";
			link.l1.go = "Fleetwood_soldier_4";	
			}
			else
			{
			dialog.text = "Wer bist du und was willst du? Erkläre dich!";
			link.l1 = "Es tut mir leid, Herr, es scheint, dass ich zum falschen Haus gekommen bin. Ich bitte um Verzeihung.";
			link.l1.go = "Fleetwood_soldier_1";	
			link.l2 = "Ich würde gerne Richard Fleetwood sehen.";
			link.l2.go = "Fleetwood_soldier_2";		
			}
		break;
		
		case "Fleetwood_soldier_1":
			dialog.text = "Das ist richtig. Sie sprechen mit dem falschen Mann. Seien Sie so nett und gehen Sie sofort!";
			link.l1 = "Ja. Sicher.";
			link.l1.go = "Fleetwood_soldier_3";			
		break;
		
		case "Fleetwood_soldier_2":
			dialog.text = "Wirklich? Wer hat Ihnen gesagt, dass er hier wohnt? Das kommt mir verdächtig vor... Gut, ich werde Sie festnehmen und zur Untersuchung ins Kommandantenbüro bringen. Jungs, schnappt euch diesen Kerl!";
			link.l1 = "Aber ich wollte nur Richard sehen...";
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
			dialog.text = "Ach! Diebe? Spione? Halte jetzt deinen Hut fest!";
			link.l1 = "Hoppla!";
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
			dialog.text = "Ach! Was macht dieser Kerl hier? Jungs, wir haben hier einen Spion! Zu den Waffen!";
			link.l1 = "Hoppla!";
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
			dialog.text = "Kapitän, wir haben diesen Schurken befragt, wie Sie es uns gesagt haben. Wir mussten ihn ein bisschen kauterisieren... Er hatte diesen Brief bei sich. Versuchte ihn zu essen, aber wir haben es ihm nicht erlaubt. Genau wie wir dachten, sollte er irgendein Mädchen in Willemstad holen und sie zu seinem Boss bringen.";
			link.l1 = "Ein Brief? Lassen Sie uns ihn ansehen. Dann werde ich selbst mit ihm sprechen.";
			link.l1.go = "Sailor_deck_1";			
		break;
		
		case "Sailor_deck_1":
			DialogExit();
			AddLandQuestMark(characterFromId("KnippelClone"), "questmarkmain");
			GiveItem2Character(pchar, "NPC_Letter");
			AddQuestRecordInfo("LetterToAbi", "1");
		break;
		
		case "Sailor_deck_2":
			dialog.text = "Welche Befehle haben Sie, Kapitän?";
			link.l1 = "Werft die Leiche über Bord. Und macht euch bereit, an Land zu gehen!";
			link.l1.go = "Sailor_deck_3";			
			// belamour legendary edition -->
			link.l2 = "Bestattet ihn auf See mit vollen militärischen Ehren. Der alte Mann hat bis zum allerletzten tapfer gekämpft. Er hat sogar diese Kanone geladen und gezielt, nachdem sie von ihrer Lafette gekippt war. Eine wahre Schande. In einer anderen Welt hätten wir Kameraden sein können...";
			link.l2.go = "Sailor_deck_3a";
		break;
		
		case "Sailor_deck_3a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			dialog.text = "Ja, Kapitän!";
			link.l1 = "..., Freund.";
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
			dialog.text = "Aye-aye, Kapitän!";
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
			dialog.text = "Wir haben den Chinesen zur Befragung vorbereitet, genau wie Sie es befohlen haben, Kapitän. Er hatte nichts bei sich, keine Papiere. Ein Kohlebecken wurde vorbereitet und wir erhitzen gerade die Handschellen und Zangen glühend heiß.";
			link.l1 = "Gute Arbeit, Alonso. Aber bevor du anfängst, möchte ich versuchen, mit ihm zu reden. Vielleicht entscheidet er sich freiwillig zur Zusammenarbeit?";
			link.l1.go = "Sailor_deck_6";			
		break;
		
		case "Sailor_deck_6":
			dialog.text = "Wie Sie sagen, Kapitän.";
			link.l1 = "...";
			link.l1.go = "exit";	
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
		break;
		
		case "Sailor_deck_7":
			dialog.text = "Ja, Kapitän?";
			link.l1 = "Legt ihm Handschellen an und behaltet ihn jederzeit im Auge, bis wir Guadeloupe erreichen. Ihr drei müsst immer hier sein. Ihr antwortet mit eurem Leben für ihn.";
			link.l1.go = "Sailor_deck_8";			
		break;
		
		case "Sailor_deck_8":
			dialog.text = "Jawohl, Kapitän!";
			link.l1 = "";
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
			dialog.text = "H-ic! Guten Abend, Herr! Was möchten Sie? Vielleicht können Sie einem alten Säufer ein Getränk kaufen? Und ich würde...";
			link.l1 = "Hör zu, alter Trunkenbold... Bist du Jack Harrison?";
			link.l1.go = "Drunkard_1";			
		break;
		
		case "Drunkard_1":
			dialog.text = "Oh! Ja, das bin ich. Wer könnte es sonst sein? Warum? Wa-a-s soll-en wir ma-ach-en mi-it ei-in-em betrunkenen Seemann...";
			link.l1 = "Oh mein Herr, gib mir Geduld! Welcher Seemann? Auf deinem Gesicht steht geschrieben, dass du ein Landratte bist... Willst du etwas Geld verdienen?";
			link.l1.go = "Drunkard_2";			
		break;
		
		case "Drunkard_2":
			dialog.text = "Ich will immer Geld verdienen. Was soll ich tun? Aber ich werde niemanden töten. Und auch nichts stehlen. Und du bist nicht mein Typ.";
			link.l1 = "Du musst niemanden töten, und ich bezweifle, dass du dazu überhaupt fähig bist. Du bist zu ungeschickt. Jetzt. Hier ist ein Brief. Nimm ihn und liefere ihn im Haus links von der Residenz des Gouverneurs ab. Er ist für Richard Fleetwood bestimmt.";
			link.l1.go = "Drunkard_3";			
		break;
		
		case "Drunkard_3":
			dialog.text = "Für Richard Fleetwood? Nein... Ich werde auf der Stelle verhaftet werden.";
			link.l1 = "Schweig und hör zu. Niemand wird dich festnehmen. Du wirst sagen, dass du von Charlie Knippel wegen Abigail gekommen bist. Man wird dich reinlassen. Wiederhole, was ich gesagt habe.";
			link.l1.go = "Drunkard_4";			
		break;
		
		case "Drunkard_4":
			dialog.text = "Wer ist Abigail? Ich kenne Knippel...";
			link.l1 = "Das geht dich nichts an. Je weniger du weißt, desto länger lebst du. Nun, ich warte. Wiederhole.";
			link.l1.go = "Drunkard_5";			
		break;
		
		case "Drunkard_5":
			dialog.text = "Ich komme von Charlie Knippel wegen eurer..... Abigail. Genau das. ";
			link.l1 = "Gut gemacht. Sie bekommen 5000 Pesos für den Job.";
			link.l1.go = "Drunkard_6";			
		break;
		
		case "Drunkard_6":
			if (int(Pchar.money) >= 5000)
			{
				dialog.text = "5000 Pesos? Oh.... Nur für die Zustellung eines Briefes?";
				link.l1 = "Nein. Du bekommst einen anderen Brief. Du kommst damit in die Taverne und setzt dich hier hin. Ich nehme ihn dir ab. Mach keinen Unsinn und hab keine Angst - ich werde dich beobachten und in der Nähe bleiben. Nimm diese Summe als Vorschuss, damit du dich leichter fühlst.";
				link.l1.go = "Drunkard_7";	
			}
			else
			{
				dialog.text = "Fünftausend? Hast du überhaupt so viel Geld?";
				link.l1 = "Ha! Natürlich habe ich. Ich bringe es jetzt.";
				link.l1.go = "Drunkard_no_money";	
				NextDiag.CurrentNode = "Drunkard_no_money";
			}
		break;
		
		case "Drunkard_no_money":
			dialog.text = "Haben Sie die fünftausend mitgebracht?";
			if (int(Pchar.money) >= 5000)
			{
				link.l1 = "Ja. Hier bist du. Mach dir keine Sorgen.";
				link.l1.go = "Drunkard_7";
			}
			else
			{
				link.l1 = "Nein. Warte. Ich werde bald zurück sein.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Drunkard_no_money";
			}
		break;
		
		case "Drunkard_7":
			AddMoneyToCharacter(pchar, -5000);
			RemoveItems(PChar, "MC_Letter", 1);
			dialog.text = "Hmm... Soll ich jetzt gehen, Herr?";
			link.l1 = "Nein, am Donnerstagmorgen... Natürlich, genau jetzt, du Tölpel! Jetzt beende deinen Rum und geh!";
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
			dialog.text = "Ach, da bist du ja, Herr... Ich hätte das besser nicht tun sollen. Richard wurde wütend, als er fertig gelesen hatte. Ich dachte, er würde mich töten.";
			link.l1 = "Aber hier bist du! Mach dir keine Sorgen - er würde es nicht wagen, dies zu tun - du warst ihm in diesem Moment sehr wertvoll ha-ha! Du kannst dir gar nicht vorstellen, wie sehr...";
			link.l1.go = "Drunkard_10";			
		break;
		
		case "Drunkard_10":
			dialog.text = "Ich muss etwas trinken... Hier ist seine Antwort für dich.";
			link.l1 = "Gib es mir! Und halt die Klappe!";
			link.l1.go = "Drunkard_11";			
		break;
		
		case "Drunkard_11":
			GiveItem2Character(pchar, "MC_Letter");
			ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter1");
			AddQuestRecordInfo("FleetwoodAnswer", "1");
			dialog.text = "Es wird für mich schwierig sein, in den nächsten Tagen zu sprechen... Auf Wiedersehen... Ich hoffe, dich nie wieder zu sehen.";
			link.l1 = "Nimm es leicht, alter Trunkenbold, ha-ha-ha! W-a-s sollen wir-r mit einem betr-u-nkenen Seema-nn machen... Trink und entspanne dich - jetzt ist alles vorbei!";
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
			dialog.text = "Warum zum Teufel hast du mein Schiff angegriffen? Ich habe weder Wertsachen noch Geld - nur Papiere, die dir sowieso nichts nützen!";
			link.l1 = "Schweig. Du hast verloren, also wirst du mir jetzt zuhören. Ich brauche weder dein Schiff, noch deine Papiere. Ich brauche dich, um diese Nachricht an deinen Chef, diese dreckige Ratte Lucas Rodenburg, zu überbringen. Sag ihm, dass Kapitän Fleetwood seine Grüße sendet.";
			link.l1.go = "Cureer_abordage_1";			
		break;
		
		case "Cureer_abordage_1":
			dialog.text = "Kapitän Fleetwood? Aber...";
			link.l1 = "Werden Sie diesen Brief Ihrem Chef übergeben - oder soll ich Sie durchbohren? Ich kann auch nach einem anderen Kandidaten für die Lieferung suchen. Ich raube jedes Wochenende aus Langeweile Schiffe Ihrer schmutzigen Firma aus, nur damit Sie es wissen.";
			link.l1.go = "Cureer_abordage_2";			
		break;
		
		case "Cureer_abordage_2":
			dialog.text = "In Ordnung, Herr Fleetwood. Ich werde es liefern.";
			link.l1 = "Das ist großartig. Jetzt können wir uns verabschieden, Mynheer. Sie können sich heute als sehr glücklich betrachten. Und vergessen Sie nicht, bei Ihrer Ankunft eine Kirche zu besuchen!";
			link.l1.go = "Cureer_abordage_3";			
		break;
		
		case "Cureer_abordage_3":
			DialogExit();
			sld = &Characters[int(pchar.GenQuest.QuestAboardCabinDialogIdx)];
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
			dialog.text = "Ich wurde illegal verhaftet! Ich habe keine Verbindung zu den Engländern! Das sind alles Rodenburg's Intrigen. Egal. Peter Stuyvesant wird bald kommen - er wird alles klären!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "MatiasBek";
		break;
		
		//стражник у входа в резиденцию
		case "QuestGuard":
			dialog.text = "Herr Lucas Rodenburg möchte zurzeit niemanden sehen. Seien Sie so freundlich, die Residenz sofort zu verlassen.";
			link.l1 = "Hm. Ich verstehe. Ich werde versuchen, in einer Woche vorbeizuschauen...";
			link.l1.go = "exit";
			NextDiag.TempNode = "QuestGuard";		
		break;
		
		//Питер Стайвесант
		case "Stivesant":
			dialog.text = "Wir gehen zur Residenz, Kapitän. Ich habe meine Leute bereits zur Festung geschickt, um Informationen über Matthias Beck zu erhalten. Wenn er tatsächlich gerade im Gefängnis ist, muss er bereits freigelassen und in die Stadt begleitet worden sein. Folgen Sie mir!";
			link.l1 = "Ja, Mynheer Stuyvesant.";
			link.l1.go = "Stivesant_1";			
		break;
		
		case "Stivesant_1":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "Villemstad_townhall", "goto", "goto2", "OpenVillemstadResidence", -1);
		break;
		
		case "ArestLucas_1":
			dialog.text = "Lucas! Was geht hier vor? Wo ist Matthias Beck? Ist es wahr, dass du ihn ins Gefängnis geschickt hast?";
			link.l1 = "";
			link.l1.go = "ArestLucas_2";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_2":
			StartInstantDialog("Lucas", "ArestLucas_3", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_3":
			dialog.text = "Hallo, Mynheer Stuyvesant. Ich habe Beweise für seine Verbindung zur britischen Geheimdienst und direkt zum Kapitän Fleetwood. Er hat den verdammten Briten gewarnt, unseren Kurierbrigantine anzugreifen, um in den Besitz der vertraulichen Korrespondenz der Gesellschaft zu gelangen.";
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
			dialog.text = "Woher haben Sie diese Informationen?";
			link.l1 = "";
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
			dialog.text = "Mynheer, der Kurier hat auch andere wichtige Unternehmensdokumente transportiert - nicht nur die üblichen Berichte. Und jetzt sind sie alle in den Händen der Briten. Deshalb habe ich mich entschieden, Beck unter Arrest zu stellen.";
			link.l1 = "";
			link.l1.go = "ArestLucas_12";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));			
		break;
		
		case "ArestLucas_12":
			StartInstantDialog("Stivesant", "ArestLucas_13", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_13":
			dialog.text = "Verdammt! Das ist eine echte Machtübernahme! Hast du eigentlich realisiert, was du getan hast, Lucas? Wo ist der Kapitän der Kurierbrigantine?";
			link.l1 = "";
			link.l1.go = "ArestLucas_14";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 4.5);
		break;
		
		case "ArestLucas_14":
			StartInstantDialog("Lucas", "ArestLucas_15", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_15":
			dialog.text = "Er ist nach Philipsburg gegangen, Mynheer.";
			link.l1 = "";
			link.l1.go = "ArestLucas_16";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));	
		break;
		
		case "ArestLucas_16":
			StartInstantDialog("Stivesant", "ArestLucas_17", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_17":
			dialog.text = "Gut, dann. Ich habe angeordnet, Beck freizulassen. Er wird hierher gebracht und dann werden wir drei ein Gespräch führen.";
			link.l1 = "";
			link.l1.go = "ArestLucas_18";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_18":
			StartInstantDialog("Lucas", "ArestLucas_19", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_19":
			dialog.text = "In Ordnung, es macht mir nichts aus. Zu dritt - gut. Lass uns reden.";
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
			dialog.text = "Sie werden für Ihre Gesetzlosigkeit bezahlen, Rodenburg! Ihre Anschuldigungen sind absurd. Sie haben mir nicht einmal erlaubt, den Kapitän der Brigantine zu sehen! Sie haben keine Beweise vorgelegt, alle Anschuldigungen kamen persönlich von Ihnen.\nIch schwöre beim Herrn, ich bin unschuldig! Ich hatte und habe keinen Kontakt mit den Briten!";
			link.l1 = "";
			link.l1.go = "ArestLucas_41";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_41":
			StartInstantDialog("Lucas", "ArestLucas_42", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_42":
			dialog.text = "Ach wirklich? Dann wie hat Fleetwood von unserer Brigantine erfahren und dass sie nicht nur die üblichen Dokumente an Bord hatte?";
			link.l1 = "";
			link.l1.go = "ArestLucas_43";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Villemstad_Mayor"));
		break;
		
		case "ArestLucas_43":
			dialog.text = "...";
			link.l1 = "Rodenburg lügt. Richard Fleetwood könnte die Kurierebrigantine nicht angegriffen haben.";
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
			dialog.text = "Und wer sind Sie, Mynheer? Auf welcher Grundlage machen Sie solche Aussagen?";
			link.l1 = "Mein Name ist "+GetFullName(pchar)+". Ich persönlich habe Kapitän Fleetwood beseitigt, indem ich ihn in eine Falle gelockt habe. Seine Leiche wird von Möwen an den Ufern von Turks gefressen. Die Beamten konnten uns, die niederländischen Händler, nicht vor seiner Aggression schützen, also habe ich ihn selbst erledigt. Und das geschah, bevor die Kuriere-Brigg geplündert wurde...";
			link.l1.go = "ArestLucas_46";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "ArestLucas_46":
			dialog.text = "";
			link.l1 = "Fleetwood konnte es einfach nicht getan haben, er war bereits tot. Ich habe von den Einheimischen in der Taverne erfahren, dass Mathias Beck verhaftet wurde, also habe ich beschlossen, der Sache nachzugehen, weil ich immer glaubte, dass Mynheer Beck ein Mann von kristallklarem Ruf ist...";
			link.l1.go = "ArestLucas_47";			
		break;
		
		case "ArestLucas_47":
			dialog.text = "";
			link.l1 = "Leute im Hafen haben mir erzählt, dass Sie Ihre Xebec mit allen Arten von Verbrechern und Söldnern beladen haben, die Wachen der Kompanie blieben an Land. Ich verfolgte Ihr Schiff und kaperte es, tötete jeden Schlächter, den Sie eingestellt haben. Ich verhörte Kapitän Longway, im Austausch für seine Freiheit erzählte er mir alles, Mynheer Rodenburg...";
			link.l1.go = "ArestLucas_48";			
		break;
		
		case "ArestLucas_48":
			dialog.text = "";
			link.l1 = "Sie planten, die Macht über Curacao zu übernehmen und befahlen Longway, die Galeone von Mynheer Stuyvesant zu versenken. Ihre Methoden kennend, bin ich sicher, dass der arme Kapitän der Brigantine tot ist. Sie müssen einen Angriff auf das Kurierschiff organisiert haben, um einen Präzedenzfall zu schaffen, habe ich recht? Und diese Tat wurde von Ihrem Attentäter, namens Jacob van Berg, durchgeführt? Longway hat mir viel über diesen Mann erzählt.";
			link.l1.go = "ArestLucas_49";			
		break;
		
		case "ArestLucas_49":
			dialog.text = "Das ... das ist eine offensichtliche Lüge! Wovon sprechen Sie, Mynheer? Wer zum Teufel sind Sie?";
			link.l1 = "Ich bin ein unabhängiger Kapitän, der das Meer und das Land von diesem Schurken Fleetwood befreien wollte und der in Ihre politischen Intrigen verwickelt wurde! Ich habe meinen Herrn Stuyvesant vor der Gefahr gewarnt, in der er sich befand. Und ich bin hier, um Ihren Verheerungen auf Curacao ein Ende zu setzen - zusammen mit den gesetzlichen Behörden!";
			link.l1.go = "ArestLucas_50";			
		break;
		
		case "ArestLucas_50":
			dialog.text = "Welche Unverschämtheit! Sie werden für Ihre Worte antworten, Mynheer 'unabhängiger Kapitän'! Sie...";
			link.l1 = "";
			link.l1.go = "ArestLucas_51";
		break;
		
		case "ArestLucas_51":
			StartInstantDialog("Stivesant", "ArestLucas_52", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_52":
			dialog.text = "Genug, Lucas. Du wirst für deine Verbrechen bezahlen! Ich habe genug gehört und gesehen. Lucas Rodenburg, ich verhafte dich wegen eines Attentats auf den Direktor der Gesellschaft, wegen des Versuchs, die Macht gewaltsam an sich zu reißen und wegen des Verdachts, den Kapitän des Kurierschiffs ermordet zu haben.\nAußerdem bin ich sicher, dass wir während der offiziellen Untersuchung noch mehr über die interessanten Teile deiner Biographie herausfinden werden. Du wirst in Gewahrsam genommen und nach Amsterdam gebracht, wo gegen dich Anklage erhoben wird. Nehmt ihn mit!";
			link.l1 = "";
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
			dialog.text = "Aber...";
			link.l1 = "";
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
			dialog.text = "Kapitän "+GetFullName(pchar)+"! Im Namen der Kolonialverwaltung von Willemstad bitte ich Sie, unseren aufrichtigen Dank für Ihre Taten zu akzeptieren, die uns geholfen haben, diesen gefährlichen Verbrecher festzunehmen. Ich möchte Ihnen auch persönlich danken, da ich Ihnen wahrscheinlich mein Leben schulde.";
			link.l1 = "Ich habe zum Wohl aller niederländischen Kolonien gehandelt, Mynheer.";
			link.l1.go = "Stivesant_11";			
		break;
		
		case "Stivesant_11":
			dialog.text = "Ihre Bescheidenheit gebietet Respekt, mein Freund. Nun würde ich gerne einige Formalitäten klären: Da Sie die Meifeng nur zu guten Zwecken und in Notlagen erobert haben, kann es keine Ansprüche geben. Aber dieses Schiff gehört der Firma und ich bitte Sie freundlich, es zurückzugeben.";
			link.l1 = "Gewiss, Mynheer.";
			link.l1.go = "Stivesant_12";			
		break;
		
		case "Stivesant_12":
		//удаляем Мейфенг
		DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//удаляем атрибут квестового корабля
		if(int(RealShips[int(pchar.ship.type)].basetype) == SHIP_MAYFANG)
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
				if(int(RealShips[int(sld.ship.type)].basetype) == SHIP_MAYFANG)
					{
						pchar.questTemp.HWIC.Self.CompanionIndex = sld.Index;
						sld = GetCharacter(int(pchar.questTemp.HWIC.Self.CompanionIndex));
						RemoveCharacterCompanion(PChar, sld);
						AddPassenger(PChar, sld, false);
					}
				}
			}
		}
			dialog.text = "Bitte kommen Sie morgen zu meiner Residenz - Sie werden im Namen der Republik der Freien Provinzen für Ihre Taten in ihrem besten Interesse ausgezeichnet. Ich bitte Sie freundlich, die Stadt nicht zu verlassen.";
			link.l1 = "In Ordnung, Mynheer. Ich komme morgen vorbei.";
			link.l1.go = "Stivesant_13";			
		break;
		
		case "Stivesant_13":
			DialogExit();
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.dialog.currentnode = "Bek_2";
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "Bek_2":
			dialog.text = "Ich möchte Ihnen auch persönlich danken, Kapitän, für Ihren Unternehmergeist und Ihre rechtzeitige Hilfe. Vergessen Sie nicht, morgen hierher zu kommen, ich werde ein wertvolles Geschenk für Sie vorbereiten.";
			link.l1 = "Danke, Mynheer Beck. Ich werde da sein!";
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
			dialog.text = ""+GetFullName(pchar)+", im Namen der Republik der Freien Provinzen werden Ihnen eine persönliche Waffe und Geld in Höhe von 100.000 Pesos für die Initiative zur Liquidation des Feindes aller Holländer, des Staatskriminellen Richard Fleetwood, verliehen. Herzlichen Glückwunsch!";
			link.l1 = "Danke, Mynheer Styuvesant!";
			link.l1.go = "Stivesant_15";			
		break;
		
		case "Stivesant_15":
			dialog.text = "Außerdem, für beispiellosen Mut, für die Aufdeckung einer verräterischen Verschwörung innerhalb der Gesellschaft und für die riskante Operation der Ergreifung des ehemaligen Vizepräsidenten der Gesellschaft, werden Sie mit 150 000 Pesos ausgezeichnet. Sie dürfen auch Verträge mit der Niederländischen Westindien-Kompanie abschließen\nIch bin sicher, dass unser neuer Vizedirektor eine gut bezahlte Arbeit für einen so tapferen Kapitän wie Sie finden wird.";
			link.l1 = "Danke! Das werde ich im Gedächtnis behalten.";
			link.l1.go = "Stivesant_16";			
		break;
		
		case "Stivesant_16":
			AddMoneyToCharacter(pchar, 250000);
			GiveItem2Character(pchar, GetGeneratedItem("blade_16")); // belamour legendary edition используем GetGeneratedItem иначе пачка одинаковых клинков из первой части массива
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			dialog.text = "Seien Sie sich bewusst, dass Sie immer auf meine Unterstützung bei allen Geschäften zählen können, solange Sie auf der Seite und im Interesse Hollands handeln. Jetzt hören wir, was der Gouverneur von Willemstad, Matthias Beck, zu sagen hat.";
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
			dialog.text = "Ich drücke meine aufrichtige Dankbarkeit aus, Kapitän, für Ihren Mut und Ihre Einsicht, eine Verschwörung gegen den Staat zu entdecken. Ich möchte Ihnen dieses wertvolle Navigationsinstrument vorstellen, das für jeden Kriegsschiffsmann von unschätzbarem Wert ist.";
			link.l1 = "Danke, Mynheer Beck";
			link.l1.go = "Bek_5";			
		break;
		
		case "Bek_5":
			GiveItem2Character(pchar, "bussol");
			dialog.text = "Ich möchte, dass du weißt: Du bist jetzt mein Freund, und das bedeutet viel. Du wirst immer ein willkommener Gast in meiner Residenz sein. Komm jederzeit und aus jedem Grund vorbei - ich werde mich freuen, dir jede Hilfe zu bieten, die du brauchen könntest.";
			link.l1 = "Es freut mich, das zu hören, Mynheer!";
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
			dialog.text = "Holland ist stolz auf Sie, Mynheer. Kapitäne wie Sie sind das Rückgrat der niederländischen Flotte in der Karibik. Hier sind Sie, bitte nehmen Sie Ihre Belohnung entgegen.";
			link.l1 = "Danke, Mynheer. Es ist mir eine Ehre, Holland zu dienen!";
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
			dialog.text = "Ich freue mich, dich zu sehen. Wie geht es dir?";
			link.l1 = "Ich bin gut. Ich bin nur vorbeigekommen, um dich zu sehen.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Stivesant_18";
		break;
		
		// Jason НСО
		case "Stivesant_19":
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
			{
				dialog.text = "Schau mal einer an! Es ist "+GetFullName(pchar)+". Wir haben kürzlich unsere Kopfgeldjäger geschickt, die Sie hierher bringen sollten. Und dieser Dienst hat viel gekostet.";
				link.l1 = "Ähm... Ich sollte gehen...";
				link.l1.go = "arest";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (pchar.questTemp.Patria == "epizode_4" && IsUniformEquip())
			{
				dialog.text = "Bist du ein Kapitän der französischen Marine? Gut, ich habe wenig Zeit, aber ich werde mir anhören, was du zu sagen hast. Was bringt dich hierher?";
				link.l1 = "Mynheer Stuyvesant, ich komme von Saint Christopher mit einer Nachricht vom Generalgouverneur der französischen Kolonien, Chevalier de Poincy.";
				link.l1.go = "Stivesant_20";
			}
			else
			{
				dialog.text = "Entschuldigen Sie, Kapitän, aber ich bin gerade extrem beschäftigt und kann Ihnen nicht genug Zeit widmen. Sprechen Sie mit meinem Herrn Mathias Beck, lassen Sie ihn hören, was Sie zu sagen haben.";
				link.l1 = "Hmm ...";
				link.l1.go = "Stivesant_19_1";
			}
		break;
		
		case "Stivesant_19_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_19";
		break;
		
		case "Stivesant_20":
			sld = characterFromId("Patria_FlautCap");
			dialog.text = "Von Chevalier de Poincy? Habe definitiv nicht erwartet, dass es so wenig brauchen würde... ähem... wie geht es Chevalier?";
			link.l1 = "Alles ist in Ordnung, Mynheer. Monsieur de Poincy hat mir befohlen, Ihnen diesen Brief zu übergeben. Meine andere Aufgabe war es, '"+sld.ship.name+"' mit Fracht für Ihre Gesellschaft zum Hafen von Willemstad. Das Schiff liegt im Dock und die Ladung wurde nicht beschädigt.";
			link.l1.go = "Stivesant_21";
		break;
		
		case "Stivesant_21":
			dialog.text = "Eine Flotte mit Fracht für unsere Firma? Interessant... Und der Brief, Kapitän?";
			link.l1 = "Hier. Bitte, nimm es.";
			link.l1.go = "Stivesant_22";
		break;
		
		case "Stivesant_22":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Hmmm... (liest). Eine Inspektion vom Mutterland... Ähem... Huh, nun... das ist interessant, he-he... Übrigens, Kapitän, habe ich gehört, dass Frankreich in der Karibik Krieg mit Spanien führt? Die Belagerung und Plünderung des Forts San Jose, die Vernichtung der spanischen Kriegsflotte vor der Ostküste Kubas...";
			link.l1 = "Vor der westlichen Küste von Hispaniola bei Port-au-Prince, Mynheer. Und das einzige Ziel der Belagerung von San Jose war es, finanzielle Entschädigung von den Spaniern für ihren Angriff auf Saint-Pierre zu erhalten. Wir sind schon seit geraumer Zeit auf schlechten Fuß mit Spanien... Wann soll ich zurückkehren, um die Antwort abzuholen?";
			link.l1.go = "Stivesant_23";
		break;
		
		case "Stivesant_23":
			dialog.text = "Ich werde Sie nicht aufhalten, Kapitän, Sie sind ein Militärmann, Sie haben sicherlich viele Angelegenheiten und ich bin sicher, dass Chevalier sehnsüchtig auf Ihre Rückkehr wartet. Seien Sie so nett und warten Sie hier im Wohnzimmer zwei Stunden, bis ich eine Antwort auf diesen Brief verfasse. Nehmen Sie Platz und ruhen Sie sich aus, Ihnen wird Wein oder Rum serviert, wenn Sie möchten...";
			link.l1 = "Mein Dank, Mynheer, ich würde lieber ein Glas guten Weins bevorzugen...";
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
			dialog.text = "Die Antwort für Monsieur de Poincy ist fertig. Hier, bitte, nehmen Sie sie... Viel Glück, Kapitän.";
			link.l1 = "Danke, Mynheer. Leb wohl!";
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
				dialog.text = "Schau mal wer da ist! Es ist "+GetFullName(pchar)+". Wir haben kürzlich unsere Kopfjäger geschickt, die dich hierher bringen sollten. Und dieser Dienst hat viel gekostet.";
				link.l1 = "Ähm... Ich sollte gehen..";
				link.l1.go = "arest";
				break;
			}
			if (pchar.questTemp.Patria == "epizode_6" && IsUniformEquip())
			{
				dialog.text = "Du bist wieder mit einer Nachricht von Generalgouverneur Philippe de Poincy gekommen, nicht wahr?";
				link.l1 = "Ja, Mynheer Stuyvesant. Am Ufer von Sint Maarten gab es ein unangenehmes Missverständnis - ein Schiff, das den Inspektor aus Paris, Baron Noel Forget, transportierte, wurde von der Festung von Philipsburg beschossen, und...";
				link.l1.go = "Stivesant_28";
			}
			else
			{
				dialog.text = "Entschuldigen Sie mich, Kapitän, aber ich bin gerade extrem beschäftigt und kann Ihnen nicht genug Zeit widmen. Sprechen Sie mit Mynheer Mathias Beck, lassen Sie ihn hören, was Sie zu sagen haben.";
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
				dialog.text = "Und genau deshalb sind Sie hier, Kapitän. Ich werde keine diplomatischen Diskussionen führen: Sagen Sie Chevalier, dass er nicht mehr für Sint Maarten verantwortlich ist. Genug von ihm. Und was die Inspektion des Mutterlandes betrifft - er soll sich etwas einfallen lassen, es war für de Poincy nie schwierig, alles auf den Kopf zu stellen.";
				link.l1 = "Ist das genau das, was ich ihm sagen soll?";
				link.l1.go = "Stivesant_29";
			}
			else
			{
				dialog.text = "Und deshalb sind Sie hier, Kapitän. Ich werde keine diplomatischen Diskussionen führen: Ihr Lehnsherr war in letzter Zeit viel zu gierig auf Sint Maarten, daher ist es an der Zeit, seinen unersättlichen Hunger zu zügeln. Und ich glaube, dass er das perfekt versteht. Ihnen, Kapitän Charles de Maure, haben wir auch Fragen zu den jüngsten Ereignissen in Zusammenhang mit dem britischen Banditen namens Richard Fleetwood, also werden Sie hier eine Weile bleiben müssen.\nSergeant! Nehmen Sie die Waffen des Kapitäns und bringen Sie ihn ins Kommandantenbüro!";
				link.l1 = "Einen französischen Offizier in Dienst zu verzögern, ist inakzeptabel!";
				link.l1.go = "Stivesant_31";
			}
		break;
		
		case "Stivesant_29":
			dialog.text = "Hätte es selbst nicht besser ausdrücken können, Kapitän. Ihr Kommandant wird alles verstehen, aber Sie müssen nicht darauf eingehen, das wird nichts ändern. Wünsche Ihnen alles Gute. Sergeant, führen Sie Monsieur Charles de Maure zum Ausgang!";
			link.l1 = "...";
			link.l1.go = "Stivesant_30";
		break;
		
		case "Stivesant_30":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload3", "Patria_DiplomatGetOut");
		break;
		
		case "Stivesant_31":
			dialog.text = "Leider bin ich anderer Meinung. Sergeant! Bei Widerstand, Gewalt anwenden!";
			link.l1 = "Sie wissen einfach noch nicht, mit wem Sie es zu tun haben, Mynheer ...";
			link.l1.go = "Stivesant_32";
		break;
		
		case "Stivesant_32":
			DialogExit();
			Patria_DiplomatFight();
		break;
		
		case "Stivesant_33":
			dialog.text = "Es ist etwas seltsam, Sie, Kapitän Charles de Maure, in dieser Rolle zu sehen... Ich hoffe, Sie können Immunität für diejenigen garantieren, die zu Ihnen zu Verhandlungen kommen..";
			link.l1 = "Sie können sich dessen sicher sein, Mynheer Stuyvesant.";
			link.l1.go = "Stivesant_34";
		break;
		
		case "Stivesant_34":
			dialog.text = "Also, können Sie mir die Möglichkeit geben, die Vereinbarung zu lesen, die Sie vorbereitet haben? Wie ich verstehe, enthält sie Inhalte aus dem Brief?";
			link.l1 = "Genau, Mynheer, nur in offizieller Form. Von Frankreichs Seite aus - Wiederherstellung der Beziehungen auf neutrale, Ablehnung jeglicher Ansprüche auf die Insel Sint Maarten. Von Englands Seite - das Ende des Handelskrieges. Die Details sind alle hier beschrieben... Und natürlich finanzielle Entschädigung für den Schaden, den wir durch die von Ihnen eingeleiteten militärischen Aktionen erlitten haben.";
			link.l1.go = "Stivesant_35";
		break;
		
		case "Stivesant_35":
			dialog.text = "Seien Sie so nett und geben Sie mir das Dokument.";
			link.l1 = "Natürlich.";
			link.l1.go = "Stivesant_36";
		break;
		
		case "Stivesant_36":
			dialog.text = "...(liest)...";
			link.l1 = "...";
			link.l1.go = "Stivesant_37";
		break;
		
		case "Stivesant_37":
			LAi_Fade("", "");
			dialog.text = "Da Sie mir keine Wahl gelassen haben, werde ich diese Vereinbarung unterschreiben. Aber für mich hat der Schutz von Willemstad und seinen Bewohnern höchste Priorität";
			link.l1 = "Dann werden wir alle drei Kopien mit Unterschriften validieren. Ich bin von Generalgouverneur Philippe de Poincy ermächtigt, das Dokument für die Seite Frankreichs zu billigen, Oberst Doily wird es für England unterschreiben.";
			link.l1.go = "Stivesant_38";
		break;
		
		case "Stivesant_38":
			dialog.text = "...(unterzeichnend)...";
			link.l1 = "Perfekt! Jetzt sollten wir das unterschreiben...";
			link.l1.go = "Stivesant_39";
		break;
		
		case "Stivesant_39":
			LAi_Fade("", "");
			dialog.text = "Also, ich glaube, Sie werden die Belagerung jetzt abbrechen?";
			link.l1 = "Ohne Zweifel. Ich hoffe, dass alle Bedingungen der Vereinbarung von der holländischen Seite ohne Verstöße eingehalten werden.";
			link.l1.go = "Stivesant_40";
		break;
		
		case "Stivesant_40":
			dialog.text = "Wenn es keine Verstöße von England oder Frankreich gibt, dann werden wir uns an die Bedingungen des Vertrages halten, mach dir keine Sorgen.";
			link.l1 = "Es ist immer besser zu handeln als zu kämpfen, Mynheer Stuyvesant. Und nun können Sie sicher nach Willemstad zurückkehren. Die Belagerung wird aufgehoben und unsere Staffel wird bald die Gewässer von Curacao verlassen.";
			link.l1.go = "Stivesant_41";
		break;
		
		case "Stivesant_41":
			DialogExit(); // Стайвесант уходит, подходит д'Ойли
			Patria_CuracaoStivesantGo();
		break;
		
		case "Stivesant_42":
			dialog.text = "Also, sind Sie Baron Noel Forget? Hm, und Sie müssen Monsieur Charles de Maure selbst sein! Grüße, Vizeadmiral! Es gibt einen Grund, warum Sie als der gerissenste Verschwörer des Archipels bekannt sind - man weiß nie, auf welcher Seite Sie gerade stehen...";
			link.l1 = "Der Vizeadmiral steht im Moment auf der Seite des Königs und Ihrer, seines berechtigten Vertreters, aufrichtig.";
			link.l1.go = "Stivesant_43";
		break;
		
		case "Stivesant_43":
			dialog.text = "Der König ist weit weg von hier, und auch Frankreich, Baron, aber Saint Christopher und Chevalier de Poincy sind nah. Er ist der wahre Besitzer der französischen Kolonien. De facto ... Sind Sie jedoch hier, um etwas zu bekommen, das de Poincy in den Augen des Finanzministers kompromittiert?";
			link.l1 = "Genau, Mynheer.";
			link.l1.go = "Stivesant_44";
		break;
		
		case "Stivesant_44":
			dialog.text = "Ich habe solche Dokumente. Das ist ein ganzes Hauptbuch mit meinen und de Poincys Konten für die Mine und einige andere Angelegenheiten. Darin finden Sie auch einen ganzen Haufen Papiere, die mit diesem Geschäft zusammenhängen, mit der persönlichen Unterschrift von Philippe de Poincy. Ich garantiere Ihnen, dass der Inhalt dieser Papiere in den Händen einer interessierten Person den Chevalier tiefer als den Grund der Karibischen See versenken wird.";
			link.l1 = "Was wollen Sie für dieses Hauptbuch?";
			link.l1.go = "Stivesant_45";
		break;
		
		case "Stivesant_45":
			dialog.text = "Ich verkaufe es für ein Lied. Nur eine Million Pesos in Silber.";
			link.l1 = "Eine Million Peso?!!";
			link.l1.go = "Stivesant_46";
		break;
		
		case "Stivesant_46":
			dialog.text = "Das ist richtig, Baron. Dieser Betrag wird zumindest teilweise die Verluste ausgleichen, die durch den jüngsten Krieg verursacht wurden. Ich gebe Ihnen einen Rat: wenden Sie sich an Monsieur Charles de Maure. Während seiner Dienstzeit für de Poincy und äh... andere Leute, hat er wahrscheinlich ein riesiges Vermögen gemacht, und eine Million zu bekommen, wird für ihn kein Problem sein. Ich bin fast sicher.\nIch gebe Ihnen eine Frist - einen Monat. Nach dieser Zeit, wenn Sie den angegebenen Betrag nicht bringen, werde ich einen Brief an den Chevalier senden, in dem ich die Einzelheiten Ihres Besuchs bei mir beschreiben werde. Sie können sich vorstellen, was als nächstes passiert.";
			link.l1 = "Sie erpressen mich! Sie müssen verstehen, dass ich unmöglich eine Million in den Kolonien haben kann!";
			link.l1.go = "Stivesant_47";
		break;
		
		case "Stivesant_47":
			dialog.text = "Natürlich verstehe ich. Deshalb habe ich Ihnen sofort die Person gezeigt, die diese Million hat. Wenn Monsieur de Maure ablehnt, ist es für Sie, Baron, am besten, nach Europa zu segeln, bevor der Chevalier meinen Brief erhält, sonst riskieren Sie, hier für immer zu bleiben. Was Monsieur de Maure betrifft... natürlich wird er seinen Admiralstitel verlieren, aber er wird herauskommen... und vielleicht sogar mit seinen Methoden de Poincy loswerden, damit habe ich überhaupt kein Problem.\nNun, meine Herren, Sie haben mich gehört. Ich werde in einem Monat mit einer Million in meiner Residenz auf Sie warten. Freier Ein- und Ausgang garantiert.";
			link.l1 = "...";
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
			if (int(pchar.money) >= 1000000)
			{
				dialog.text = "Ich habe nicht einmal gezweifelt, Vizeadmiral Charles de Maure, dass Sie mir dieses Geld bringen würden. Vielleicht habe ich sogar zu wenig von Ihnen verlangt, aber na ja ... Der Baron ist nur eine Figur in Ihrem nächsten Spiel, nicht wahr? Der Rang und das Geld reichen Ihnen nicht, jetzt wollen Sie den Platz von de Poincy einnehmen, habe ich recht? Sie müssen zugeben, eine Million ist eine kleine Summe für den Posten des Generalgouverneurs der französischen Kolonien! Sie werden dieses Geld in wenigen Monaten zurückbekommen, angesichts Ihrer eisernen Hand.";
				link.l1 = "Nehmen Sie Ihre Million, Mynheer. Ich möchte mein versprochenes Hauptbuch erhalten.";
				link.l1.go = "Stivesant_50";
			}
			else
			{
				dialog.text = "Sie sollten sich besser darauf konzentrieren, die Million zu sammeln, Monsieur, anstatt Ihre Zeit mit sinnlosen Besuchen zu verschwenden.";
				link.l1 = "..., Freund.";
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
			dialog.text = "Natürlich, Vizeadmiral. Und runzeln Sie nicht die Stirn: Wenn Sie Generalgouverneur werden, werden Sie sehen, dass die Niederländische Westindien Handelsgesellschaft ein profitablerer Geschäftspartner ist als die gierigen und kriegstreibenden Briten. Wissen Sie nicht, dass wenn man einem Briten den kleinen Finger gibt, er die ganze Hand nimmt? Wenn nicht, werden Sie es auf die harte Tour lernen. Also verabschiede ich mich noch nicht von Ihnen. Behalten Sie Ihre Papiere. Ich hoffe, Ihr Baron ist kompetent genug, um den Chevalier zu besiegen.";
			link.l1 = "Mein Dank. Auf Wiedersehen, Mynheer Stuvesant.";
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
			dialog.text = "Ha-ha-ha! Schau dir das an! Jacob hatte wie immer recht - dieser Fuchs ist aus gutem Grund auf die Insel gegangen. Es scheint, dass in der Truhe ein ziemlicher Haufen Gold ist. Sehr unvorsichtig von dir, alleine hierher zu kommen, Kumpel. Aber dann wieder, es macht unsere Arbeit umso einfacher!";
			link.l1 = "Diese Abschaum hat mich aufgespürt! Ich habe es nicht kommen sehen... Aber ich werde nicht leichtes Opfer sein!";
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
			dialog.text = "Suchen Sie jemanden?";
			link.l1 = "Ja, das bin ich. Wo sind Solomon und Abigail Shneur?";
			link.l1.go = "Abihouselady_1";			
		break;
		
		case "Abihouselady_1":
			dialog.text = "Sie leben hier nicht mehr. Sie konnten sich den Ort einfach nicht leisten. Abigail, das arme Mädchen, arbeitet als eine der Bediensteten des Gouverneurs. Sie arbeitet jeden Tag hart, um für sie und ihren Vater zu sorgen. Solomon trinkt jeden Tag in der Taverne, er kann das, was ihnen passiert ist, nicht ertragen. Sie leben jetzt in einer kleinen Hütte nicht weit vom Meer...";
			link.l1 = "Oh... Gut, danke für die Information. Ich muss gehen.";
			link.l1.go = "Abihouselady_2";
		break;
		
		case "Abihouselady_2":
			DialogExit();
			NextDiag.CurrentNode = "Abihouselady_3";
		break;
		
		case "Abihouselady_3":
			dialog.text = "Was möchten Sie sonst noch wissen, Mynheer?";
			link.l1 = "Nichts, vergiss es.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abihouselady_3";
		break;
		
		//удаление Мейфенг при провале квеста
		case "TempOffGuard":
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//удаляем атрибут квестового корабля
			if(int(RealShips[int(pchar.ship.type)].basetype) == SHIP_MAYFANG)
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
						if(int(RealShips[int(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							pchar.questTemp.HWIC.Self.CompanionIndex = sld.Index;
							sld = GetCharacter(int(pchar.questTemp.HWIC.Self.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			dialog.text = "Kapitän, Sie haben ein Schiff der Niederländischen Westindien-Kompanie widerrechtlich angeeignet. Ich bin berechtigt, es zu konfiszieren und im Falle von Widerstand Gewalt anzuwenden. Dies ist ein Befehl von Peter Stuyvesant.";
			link.l1 = "Nun, wenn es ein Befehl von Peter Stuyvesant selbst ist... Ich werde nicht wegen eines Schiffes mit Holland in den Krieg ziehen. Nimm es.";
			link.l1.go = "TempOffGuard_1";			
		break;
		
		case "TempOffGuard_1":
			dialog.text = "Gut für dich, Vernunft zu zeigen.";
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
			dialog.text = "Natürlich ist es Zeit zu gehen, Sie werden sogar begleitet. Wachen! Holt ihn!";
		    link.l1 = "Mach mich!";
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
			dialog.text = NPCharSexPhrase(NPChar,"He, hör zu! Als Bürger dieser Stadt bitte ich dich freundlich, nicht mit gezogenem Schwert herumzulaufen.","Weißt du, als Bürger dieser Stadt, bitte ich dich freundlich, nicht mit einer gezogenen Klinge herumzulaufen.");
			link.l1 = LinkRandPhrase("Gut.","In Ordnung.","Wie du sagst...");
			link.l1.go = "exit";
		break;
	}
}
