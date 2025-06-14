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
			dialog.text = "Was wollen Sie?";
			link.l1 = "Nichts.";
			link.l1.go = "exit";
		break;
		
		// Квест "Длинные тени старых грехов"
		case "DTSG_Knippel_1":
			dialog.text = "Oh, was für eine Hitze heute. Man könnte genauso gut eine Kettenkugel ums Bein binden und ins Meer springen, nur um dieser Schwüle zu entkommen!";
			link.l1 = "Ha-ha, Charlie!.. Das sind ziemlich extreme Maßnahmen, wenn du mich fragst. Aber ich hätte nichts dagegen, meinen Schnabel zu nass zu machen - es ist wirklich zu heiß heute. Bist du dabei?";
			link.l1.go = "DTSG_Knippel_2";
		break;
		
		case "DTSG_Knippel_2":
			dialog.text = "Haben Sie ein oder zwei Drinks mit Ihnen, Kapitän? Immer!";
			link.l1 = "Das höre ich gerne. Los geht's!";
			link.l1.go = "DTSG_Knippel_3";
		break;
		
		case "DTSG_Knippel_3":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "", "", "", "DTSG_BasTerTavern", -1);
			FreeSitLocator("BasTer_tavern", "sit_base2");
			FreeSitLocator("BasTer_tavern", "sit_front2");
		break;
		
		case "DTSG_Ohotnik_1":
			dialog.text = "He, Seemann, du siehst aus, als hättest du alles gesehen! Lass uns einen trinken und einige Geschichten austauschen? Ich gebe einen aus!";
			link.l1 = "";
			link.l1.go = "DTSG_Ohotnik_1_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
			
		break;
		
		case "DTSG_Ohotnik_1_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_2":
			dialog.text = "Äh, nein danke, Kumpel. Ich bin hier mit meinem Kapitän. Such dir jemand anderen.";
			link.l1 = "";
			link.l1.go = "DTSG_Ohotnik_2_Animation";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
			locCameraFromToPos(5.57, 2.39, -4.63, true, 8.53, 2.07, 1.84);
		break;
		
		case "DTSG_Ohotnik_2_Animation":
			StartInstantDialog("DTSG_Ohotnik", "DTSG_Ohotnik_3", "Quest\CompanionQuests\Knippel.c");
			locCameraSleep(true);
		break;
		
		case "DTSG_Ohotnik_3":
			dialog.text = "Ha, ein Lump wie du hat so hohe Meinungen, trinkt nur mit Kapitänen?";
			link.l1 = "";
			link.l1.go = "DTSG_Ohotnik_3_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
		break;
		
		case "DTSG_Ohotnik_3_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_4", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_4":
			dialog.text = "Hohe Meinungen?! Ich habe jahrzehntelang in der königlichen Marine gedient! Und ich habe nicht für die Herren gekämpft, sondern für normale Leute wie dich und mich, um überall Recht und Ordnung zu gewährleisten!..";
			link.l1 = "";
			link.l1.go = "DTSG_Ohotnik_4_Animation";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		
		case "DTSG_Ohotnik_4_Animation":
			StartInstantDialog("DTSG_Ohotnik", "DTSG_Ohotnik_5", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_5":
			dialog.text = "Du redest groß, aber trinkst nur mit Kapitänen und Adligen! Sieht so aus, als hätte die Marine dir doch beigebracht, wie man die Kanonen richtig putzt, ha!";
			link.l1 = "";
			link.l1.go = "DTSG_Ohotnik_5_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
		break;
		
		case "DTSG_Ohotnik_5_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_6":
			dialog.text = "Ich schiebe dir einen Kettenkugel in den Hals, du Grünschnabel!";
			link.l1 = "Charlie, reg dich nicht so auf, es ist es nicht wert.";
			link.l1.go = "DTSG_Ohotnik_7";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		
		case "DTSG_Ohotnik_7":
			dialog.text = "Lassen Sie mich das regeln, Kapitän. Die Ehre der Marine steht auf dem Spiel, ich muss sie selbst verteidigen und mich nicht hinter jemandem verstecken...";
			link.l1 = "";
			link.l1.go = "DTSG_Ohotnik_8";
		break;
		
		case "DTSG_Ohotnik_8":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			sld = CharacterFromID("Blaze");
			LAi_SetImmortal(sld, true);
			LAi_CharacterDisableDialog(sld);
			LAi_SetSitType(sld);
			sld = CharacterFromID("Baster_Smuggler");
			LAi_SetImmortal(sld, true);
			SetMainCharacterIndex(GetCharacterIndex("Knippel"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			sld = CharacterFromID("DTSG_Ohotnik");
			ChangeCharacterAddressGroup(sld, "BasTer_tavern", "tables", "stay7");
			DoQuestReloadToLocation("BasTer_tavern", "tables", "stay6", "DTSG_BasTerTavern_7");
		break;
		
		case "DTSG_Knippel_l0":
			dialog.text = "Danke, dass Sie gewartet haben, Kapitän. Ich hoffe, ich habe nicht zu lange gebraucht.";
			link.l1 = "Mach dir keine Sorgen. Bist du nicht verletzt? Dieser Schurke war ziemlich gut.";
			link.l1.go = "DTSG_Knippel_l1";
		break;
		
		case "DTSG_Knippel_l1":
			dialog.text = "Machen Sie sich keine Sorgen, Kapitän. Das Wichtigste ist, dass er bekommen hat, was er verdient hat. Ich habe irgendeinen Schlüssel von seinem Körper aufgehoben...";
			link.l1 = "";
			link.l1.go = "DTSG_Knippel_l2";
		break;
		
		case "DTSG_Knippel_l2":
			dialog.text = "Ich habe irgendeinen Schlüssel von seinem Körper aufgehoben... Ich frage mich, wofür er sein könnte?";
			link.l1 = "Grundlegend, Charlie... Für eine Tür oder eine Truhe, ha-ha. Wir sollten mit dem Wirt über diesen Schurken sprechen, es könnte nützlich sein.";
			link.l1.go = "DTSG_Knippel_l3";
			AddItems(pchar, "Key1", 1);
			Log_info("Charlie gave you the key.");
			PlaySound("interface\important_item.wav");
		break;
		
		case "DTSG_Knippel_l3":
			DialogExit();
			
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			sld.location = "None";
			pchar.questTemp.DTSG_BasTerTavern = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
		break;
		
		case "DTSG_Knippel_20":
			dialog.text = "Unglaublich...";
			link.l1 = "Bist du am Denken, was ich denke, Charlie?";
			link.l1.go = "DTSG_Knippel_21";
		break;
		
		case "DTSG_Knippel_21":
			dialog.text = "Ich weiß nicht, wie es Ihnen geht, Herr, aber ich bin überrascht, wie viel Geld hier ist - er sah aus wie ein gewöhnlicher Mann, nicht wie ein Händler oder ein Adliger.";
			link.l1 = "Es ist nicht wirklich viel, aber du hast recht. Was mich überrascht, ist dieser merkwürdige verbrannte Brief.";
			link.l1.go = "DTSG_Knippel_22";
		break;
		
		case "DTSG_Knippel_22":
			dialog.text = "Ja, das war nicht sehr klug von ihm - es ist, als würde man Kettenschuss auf einen robusten Rumpf abfeuern. Er hätte den Brief vollständig vernichten sollen.";
			link.l1 = "Stimmt. Aber es hilft uns nicht - wir wissen nicht, wer er war oder mit wem er korrespondierte. Los geht's, Charlie, hier gibt es nichts mehr für uns.";
			link.l1.go = "DTSG_Knippel_23";
		break;
		
		case "DTSG_Knippel_23":			//КОНЕЦ ЭТАПА 1
			DialogExit();
			Return_KnippelOfficer();

			AddQuestRecord("DTSG", "2");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.questTemp.DTSG_Nastoroje1 = true;
		break;
		
		case "DTSG_Ohotnik_10":
			dialog.text = "So viel zu Ihrer gepriesenen königlichen Marine, pfft!";
			link.l1 = "Charlie war ein guter, anständiger Mann. Und er war Kanonier, kein Marine.";
			link.l1.go = "DTSG_Ohotnik_11";
		break;
		
		case "DTSG_Ohotnik_11":
			dialog.text = "Ein Kanonier?! Also, genau wie ich gesagt habe, ha-ha-ha! Und starre nicht so - du hättest wissen müssen, wen du in deine Crew nimmst.";
			link.l1 = "Du hättest wissen sollen, mit wem du dich anlegst.";
			link.l1.go = "DTSG_Ohotnik_Agressia_1";
			link.l2 = "Du lebst nur noch, weil du fair gewonnen hast, also halt deine verdammte Zunge und verschwinde hier.";
			link.l2.go = "DTSG_Ohotnik_Otpustil_1";
		break;
		
		case "DTSG_Ohotnik_Otpustil_1":
			dialog.text = "Nun, ich dachte, ich müsste als nächstes gegen dich kämpfen. Es ist schön zu hören, dass Ehre für dich etwas bedeutet.";
			link.l1 = "Es waren nicht nur leere Worte für Charlie. Aber was dich angeht, habe ich meine Zweifel. Wie auch immer, jetzt spielt es keine Rolle mehr.";
			link.l1.go = "DTSG_Ohotnik_Otpustil_2";
		break;
		
		case "DTSG_Ohotnik_Otpustil_2":			//ПРОВАЛ ЭТАПА 1
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			LAi_LocationDisableOfficersGen("BasTer_tavern", false);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", -3);
			ChangeCharacterComplexReputation(pchar, "fame", -3);	
		break;
		
		case "DTSG_Ohotnik_Agressia_1":
			dialog.text = "Und mit wem habe ich mich angelegt, einem verwöhnten Schwächling?! Hast du überhaupt schon mal deinen eigenen dünnen Schnurrbart gesehen?..";
			link.l1 = "Sie wissen wirklich, wie man Knöpfe drückt... Es wird umso befriedigender sein, meinen Ärger an Ihnen auszulassen.";
			link.l1.go = "DTSG_Ohotnik_Agressia_2";
		break;
		
		case "DTSG_Ohotnik_Agressia_2":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			sld = CharacterFromID("DTSG_Ohotnik");
			DeleteAttribute(sld, "CantLoot");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Ohotnik_Agressia_3");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_PiterAdams_1":
			dialog.text = "Warte, Kapitän. Ich sehe, du bist ein würdiger und edler Mann, kannst du mir bei etwas helfen? Es ist eine Frage der Ehre.";
			link.l1 = "Vielleicht kann ich, aber was ist los? Und warum bist du zu mir gekommen? Es gibt viele edle Leute hier. Mit wem habe ich übrigens die Ehre zu sprechen?";
			link.l1.go = "DTSG_PiterAdams_2";
			InterfaceStates.Buttons.Save.enable = true;
		break;
		
		case "DTSG_PiterAdams_2":
			dialog.text = "Peter. Peter Adams. Ich sehe, dass du kein typischer verwöhnter Nachkomme einer alten Familie bist, sondern ein zuverlässiger Mann mit einer festen Hand.";
			link.l1 = "Oh, Sie hätten mich sehen sollen, als ich zum ersten Mal in die Karibik kam, Herr. Aber gehen Sie voran, bei was brauchen Sie Hilfe?";
			link.l1.go = "DTSG_PiterAdams_3";
		break;
		
		case "DTSG_PiterAdams_3":
			dialog.text = "Könnten Sie... in meinem Namen duellieren, Herr? Ein örtlicher Unruhestifter, Ralph Faggle, hat meine Frau beleidigt. Und er belästigte sie, öffentlich. Direkt vor meinen Augen. Können Sie sich das vorstellen?";
			link.l1 = "Es ist nicht sehr ehrenhaft, ein Duell herauszufordern und sich dann hinter jemand anderem zu verstecken. Besonders wenn es nicht nur um deine persönliche Ehre geht, sondern um die einer Frau, deiner Frau nicht weniger. Denkst du nicht auch so, Adams? Warum kannst du nicht selbst für deine Frau kämpfen?";
			link.l1.go = "DTSG_PiterAdams_4";
		break;
		
		case "DTSG_PiterAdams_4":
			dialog.text = "Und Sie haben recht, absolut recht. Aber ich habe kürzlich an einem schweren Fieber gelitten und kann kaum auf meinen Füßen stehen\nZugegeben, es fällt mir nicht leicht, Sie um so etwas zu bitten. Wenn er mich beleidigt hätte, hätte ich es ertragen. Aber nicht, wenn die Ehre meiner Frau auf dem Spiel steht! Ich bin kein Feigling, Herr. Ich habe einst in der königlichen Marine gedient und bin zusammen mit Robert Blake selbst auf demselben Schiff gesegelt!";
			link.l1 = "Ich...";
			link.l1.go = "DTSG_PiterAdams_5";
		break;
		
		case "DTSG_PiterAdams_5":
			StartInstantDialog("Knippel", "DTSG_PiterAdams_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_6":
			dialog.text = "Wir werden dir helfen.";
			link.l1 = "Charlie?..";
			link.l1.go = "DTSG_PiterAdams_7";
			CharacterTurnByChr(npchar, characterFromId("DTSG_PiterAdams"))
		break;
		
		case "DTSG_PiterAdams_7":
			dialog.text = "Er ist ein ehrenwerter Mann, Kapitän. Und möge ich bis in alle Ewigkeit von Kanonenkugeln verdammt werden, wenn es nicht wahr ist! Große Leute dienten bei Admiral Blake. Sie kämpften zusammen, damit niemand das gemeine Volk unterdrücken würde\nUnd dank ihm wurde Jamaika von der Tyrannei der Spanier befreit!";
			link.l1 = "Sogar wenn das der Fall ist, erlaube ich nicht, dass meine Crewmitglieder mich unterbrechen oder Entscheidungen für mich treffen. Ist das klar?";
			link.l1.go = "DTSG_PiterAdams_8";
			link.l2 = "Ich verstehe, wirklich. Allerdings hatte ich noch keine Chance zu antworten. Versuche in Zukunft nicht so voreilig zu sein und mich zu unterbrechen, in Ordnung?";
			link.l2.go = "DTSG_PiterAdams_8";
			CharacterTurnByChr(npchar, pchar)
		break;
		
		case "DTSG_PiterAdams_8":
			dialog.text = "Ich sage Ihnen dies, Kapitän - wenn Sie diesem Mann nicht helfen, wird der alte Charlie alles fallen lassen und selbst für ihn duellieren, möge ich auf der Stelle verdammt sein!";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje1"))
			{
				link.l1 = "Ruhig jetzt, ich habe nicht gesagt, dass ich mich weigere zu helfen. Nicht wahr, Herr Adams?";
				link.l1.go = "DTSG_PiterAdams_Nastoroje_1";
			}
			else
			{
				link.l1 = "Ehrlich gesagt, Charlie, du lässt mich wie einen Feigling aussehen. Und ich bin noch nie einer gewesen. Das solltest du wissen.";
				link.l1.go = "DTSG_PiterAdams_NN_1";
			}
		break;
		
		case "DTSG_PiterAdams_NN_1":
			dialog.text = "Äh, entschuldigung, Kapitän, ich habe mich hinreißen lassen.";
			link.l1 = "Es ist in Ordnung. Aber halte dich in Schach, ja?";
			link.l1.go = "DTSG_PiterAdams_NN_1_1";
		break;
		
		case "DTSG_PiterAdams_NN_1_1":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_PiterAdams_NN_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_NN_2":
			dialog.text = "";
			link.l1 = "Ich werde für Sie duellieren, Herr Adams.";
			link.l1.go = "DTSG_PiterAdams_NN_3";
		break;
		
		case "DTSG_PiterAdams_NN_3":
			dialog.text = "Danke, Herr! Gott segne Sie!";
			link.l1 = "Und segne auch den Lord Protector, nicht wahr, Herr Adams? Mach dir keine Sorgen, Charles de Maure lässt einen ehrlichen Mann nie in Schwierigkeiten.";
			link.l1.go = "DTSG_PiterAdams_NN_4";
		break;
		
		case "DTSG_PiterAdams_NN_4":
			dialog.text = "Wir schätzen es, Herr de Maure, Sir! Möchten Sie zu uns kommen und mit Jane und mir zu Abend essen?";
			link.l1 = "Nun, ich...";
			link.l1.go = "DTSG_PiterAdams_NN_5";
		break;
		
		case "DTSG_PiterAdams_NN_5":
			dialog.text = "Ich bestehe darauf!";
			link.l1 = "Nun, nur wenn du darauf bestehst. Danke, Peter. Führ den Weg.";
			link.l1.go = "DTSG_PiterAdams_IdemKDomu";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_1":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_PiterAdams_Nastoroje_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_Nastoroje_2":
			dialog.text = "Natürlich ist es wahr, Herr! Möchten Sie mit Jane vorbeikommen und sich nach Ihrer Reise ausruhen?";
			link.l1 = "Danke, aber ist es richtig, Ihre Gastfreundschaft auszunutzen?";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_3";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_3":
			dialog.text = "Oh, im Gegenteil, Kapitän, wir wären beleidigt, wenn Sie nicht vorbeikommen würden.";
			link.l1 = "Wie könnte ich dann ablehnen? Nach dir, Peter!";
			link.l1.go = "DTSG_PiterAdams_IdemKDomu";
		break;
		
		case "DTSG_PiterAdams_IdemKDomu":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "houseF1", "DTSG_PiterAdams_VDom", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_1":
			dialog.text = "Das sind wir! Bitte, komm rein.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje1"))
			{
				link.l1 = "Danke. Darf ich mit Jane sprechen? Frag sie, wie es passiert ist - ich brauche alle Details.";
				link.l1.go = "DTSG_PiterAdamsRyadomSDomom_2";
			}
			link.l2 = "Es tut mir aufrichtig leid, aber nach reiflicher Überlegung muss ich ablehnen. Ich muss mich auf ein Duell vorbereiten. Übrigens, wann und wo findet es statt?";
			link.l2.go = "DTSG_PiterAdamsRyadomSDomom_4";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_2":
			dialog.text = "Nun, natürlich, Herr. Wir werden beide gerne mit Ihnen sprechen und alle Ihre Fragen beantworten. Bitte folgen Sie mir.";
			link.l1 = "Danke dir, Peter.";
			link.l1.go = "DTSG_PiterAdamsRyadomSDomom_3";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_3":
			DoQuestReloadToLocation("PortPax_houseF1", "reload", "reload1", "DTSG_PiterAdams_VDom_2");
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_4":
			dialog.text = "Wie schade! Aber Sie haben recht, Sie sollten sich natürlich gründlich vorbereiten. Zwei Stunden. Gleich außerhalb der Stadtmauern.";
			link.l1 = "Verstanden, danke. Ich komme gerne vorbei, wenn es vorbei ist. Bis dann!";
			link.l1.go = "DTSG_PiterAdamsRyadomSDomom_5";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_5":
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false; 
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "", -1);
			npchar.location = "None";
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			sld.Dialog.CurrentNode = "Knippel_officer";
			sld.location = "None";
			
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1 = "Timer";
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.hour = sti(GetTime() + 2);
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			PChar.quest.DTSG_PoP_DuelTime.win_condition = "DTSG_PoP_DuelTime";
			
			PChar.quest.DTSG_PoP_Duel.win_condition.l1 = "location";
			PChar.quest.DTSG_PoP_Duel.win_condition.l1.location = "PortPax_ExitTown";
			PChar.quest.DTSG_PoP_Duel.win_condition = "DTSG_PoP_Duel";
			
			AddQuestRecord("DTSG", "3");
		break;
		
		case "DTSG_JeinAdams_1":
			dialog.text = "Willkommen! Lieber, du hast mir nicht gesagt, dass du Gäste mitbringst - Ich hätte mich ordentlich vorbereiten können.";
			link.l1 = "Danke, gnädige Frau, wir werden nicht lange brauchen. Charles de Maure, zu Ihren Diensten. Ich habe zugestimmt, Ihre Geschichte mit Ihrem Ehemann zu hören. Erzählen Sie mir, wie es passiert ist.";
			link.l1.go = "DTSG_JeinAdams_2";
		break;
		
		case "DTSG_JeinAdams_2":
			dialog.text = "Oh, es war furchtbar! Ralph war völlig betrunken. Er hat mich vor den Nachbarn belästigt, sogar vor Peter, und obszöne Dinge gesagt...";
			link.l1 = "Was hat er genau zu dir gesagt?";
			link.l1.go = "DTSG_JeinAdams_3";
		break;
		
		case "DTSG_JeinAdams_3":
			dialog.text = "Ich schäme mich zu sehr, darüber zu sprechen. Dann wurde er nüchtern, und...";
			link.l1 = "Entschuldigte sich und bat darum, das Duell abzusagen, vielleicht?";
			link.l1.go = "DTSG_JeinAdams_4";
		break;
		
		case "DTSG_JeinAdams_4":
			dialog.text = "Nicht ein einziges Mal.";
			link.l1 = "Es tut mir Leid für Sie. Ich würde gerne noch eine Sache wissen, wenn Sie erlauben, Madame.";
			link.l1.go = "DTSG_JeinAdams_5";
		break;
		
		case "DTSG_JeinAdams_5":
			dialog.text = "Und was ist das, Herr?";
			link.l1 = "Welche Lebensumstände und Prüfungen zwangen Sie und Ihren Ehemann, hier zu leben? In jeder englischen Stadt, angesichts der Verdienste Ihres Ehemannes, hätten Sie Ralph längst auf seinen Platz gesetzt.";
			link.l1.go = "DTSG_JeinAdams_6";
		break;
		
		case "DTSG_JeinAdams_6":
			StartInstantDialog("Knippel", "DTSG_JeinAdams_7", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_JeinAdams_7":
			dialog.text = "Ich bitte um Verzeihung, Herr, aber wie können Sie es wagen?! Wenn Sie nicht mein Kapitän wären, würde ich eine Kettenkugel greifen und Ihnen einen ordentlichen Dresche geben!\nSie misstrauen nicht nur so einem ehrenwerten Mann wie Herrn Adams, sondern verspotten auch eine Dame in Not...";
			link.l1 = "Hast du mich eine Dame verspotten hören? Nein? Dann verleumde mich nicht. Unser Leute hätten ihnen helfen können, deshalb habe ich gefragt.";
			link.l1.go = "DTSG_JeinAdams_8a";
			link.l1 = "Beruhige dich, Charlie! Wie konntest du nur... Ich wollte nur mehr über die Schwierigkeiten von Jane und Peter erfahren und mit ihnen sympathisieren. In den englischen Kolonien hätten sie sicherlich schon Hilfe erhalten.";
			link.l1.go = "DTSG_JeinAdams_8b";
		break;
		
		case "DTSG_JeinAdams_8a":
			dialog.text = "Das Leben kann viele Wendungen nehmen... Schiffbruch. Oder jemandes Verleumdung, die manchmal sogar solch ehrliche Menschen dazu zwingt, sich in Schande zu verstecken\nWenn du so misstrauisch und argwöhnisch bist - du kannst mit den Nachbarn sprechen. Ich bin sicher, sie werden jedes Wort bestätigen. Aber der alte Charlie würde sich nicht dazu herablassen, über die Leiden der Menschen hinter ihrem Rücken zu diskutieren!";
			link.l1 = "Hast du mich nicht gehört? Ich sagte, ich würde diesen Leuten helfen.";
			link.l1.go = "DTSG_JeinAdams_9";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
		break;
		
		case "DTSG_JeinAdams_8b":
			dialog.text = "Das Leben kann sich auf viele Arten entwickeln... Ein Schiffbruch. Oder jemandes Verleumdung, die manchmal selbst solche ehrlichen Menschen dazu zwingt, in Schande zu verstecken\nWenn du so misstrauisch und verdächtig bist - du kannst mit den Nachbarn sprechen. Ich bin sicher, sie werden jedes Wort bestätigen. Aber der alte Charlie würde sich nicht dazu herablassen, hinter dem Rücken über die Trauer der Menschen zu sprechen!";
			link.l1 = "Hast du mich nicht gehört? Ich sagte, ich würde diesen Leuten helfen.";
			link.l1.go = "DTSG_JeinAdams_9";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", -2);
		break;
		
		case "DTSG_JeinAdams_9":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_JeinAdams_10", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_JeinAdams_10":
			dialog.text = "Wir danken Ihnen von Herzen. Wir werden Sie in unseren Gebeten in Erinnerung behalten.";
			link.l1 = "Das ist gut. Übrigens, zu unserer Angelegenheit. Wo und wann haben Sie das Duell arrangiert, Herr Adams?";
			link.l1.go = "DTSG_JeinAdams_11";
		break;
		
		case "DTSG_JeinAdams_11":
			dialog.text = "Außerhalb der Stadtmauern, Herr. In zwei Stunden.";
			link.l1 = "Ich schaffe das. Erwarte mich mit guten Nachrichten. Und denk nicht daran, eine Kerze für meine Ruhe im Voraus anzuzünden!";
			link.l1.go = "DTSG_JeinAdams_13";
		break;
		
		case "DTSG_JeinAdams_13":
			DoQuestReloadToLocation("PortPax_town", "reload", "houseF1", "DTSG_PiterAdams_IsDoma");
		break;
		
		case "DTSG_Knippel_30":
			dialog.text = "Ist etwas, das Sie stört, Kapitän? Sie sehen sehr nachdenklich aus.";
			link.l1 = "Sie wissen, ja. Etwas in Adams' Geschichte ergibt keinen Sinn, und...";
			link.l1.go = "DTSG_Knippel_31";
		break;
		
		case "DTSG_Knippel_31":
			dialog.text = "Wie lange geht das noch so weiter, Herr?! Reagieren Sie jedes Mal so, wenn jemand Hilfe braucht?";
			link.l1 = "Um Gottes willen, sprich leise. Du würdest es der ganzen Straße zurufen. Ich sagte, ich würde zum Duell gehen. Ist das nicht genug für dich? Jetzt hör mir gut zu.";
			link.l1.go = "DTSG_Knippel_32";
		break;
		
		case "DTSG_Knippel_32":
			dialog.text = "Hmm, in Ordnung, Kapitän. Entschuldigen Sie meinen Ausbruch - Ich mache mir Sorgen um das Schicksal derjenigen, die in der Royal Navy gedient haben. Viele von uns waren anständige Kerle, die ein besseres Schicksal verdient hätten, als die meisten bekommen haben.";
			link.l1 = "Ich verstehe dich, Charlie. Jetzt denk daran, was zu tun ist. Ich möchte, dass du einige der Crew-Mitglieder zu den Stadttoren schickst. Wenn die Zeit für das Duell näher rückt, sollen sie sich leise versammeln und auf mein Signal warten.";
			link.l1.go = "DTSG_Knippel_33";
		break;
		
		case "DTSG_Knippel_33":
			dialog.text = "Haben Sie vor, aus einem ehrlichen Duell einen Mord zu machen?";
			link.l1 = "Ich vermute, es wird nicht völlig ehrlich sein. Ich werde nur signalisieren, wenn es notwendig ist. Wenn alles wirklich über Bord ist, werde ich mich freuen, falsch zu liegen. Verstehst du jetzt? Erinnerst du dich an das, was vor einem Monat passiert ist?";
			link.l1.go = "DTSG_Knippel_34";
		break;
		
		case "DTSG_Knippel_34":
			dialog.text = "Verstanden, Herr. Ehrlich gesagt, bin ich darüber nicht allzu glücklich, aber ich werde tun, was notwendig ist. Machen Sie sich keine Sorgen.";
			link.l1 = "Das ist es, was ich hören wollte.";
			link.l1.go = "DTSG_Knippel_35";
		break;
		
		case "DTSG_Knippel_35":
			DialogExit();
			
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.location = "None";
			AddDialogExitQuestFunction("DTSG_Knippel_36");
		break;
		
		case "DTSG_RalfFaggl":
			LAi_LocationDisableOfficersGen("PortPax_ExitTown", false);
			PChar.quest.DTSG_PoP_DuelTime.over = "yes";
			PChar.quest.DTSG_PoP_Duel.over = "yes";
			dialog.text = "Also, de Maure. Du bist früh dran. Und wir sind immer noch in der Stadt. Obwohl es keine Rolle spielt. Schade, dass du diesen alten Narren nicht mitgebracht hast. Aber keine Sorge, wir werden ihn schließlich erwischen.";
			link.l1 = "Zu Ihren Diensten, jederzeit. Söldner, seid ihr? Wen habe ich gekreuzt?";
			link.l1.go = "DTSG_RalfFaggl_2";
		break;
		
		case "DTSG_RalfFaggl_2":
			dialog.text = "Genau das ist es, niemand. Wir sind hinter diesem alten Knacker, Charlie, her und es ist einfacher, ihn durch dich zu finden, da wir erfahren haben, dass er jetzt auf deinem Schiff ist. Das hier ist kein Dschungel, also müssen wir schnell handeln, um keine Menschenmenge anzuziehen. Aber hier wirst du zumindest nicht entkommen.";
			link.l1 = "Ich vermute, dieses ganze Duell war eine Falle?";
			link.l1.go = "DTSG_RalfFaggl_3";
		break;
		
		case "DTSG_RalfFaggl_3":
			dialog.text = "Ein bisschen spät, um das zu erkennen, Freund. Wir hätten sowieso gekämpft - ich bin Ralph Faggle, zu Diensten.";
			link.l1 = "Eigentlich habe ich so etwas schon vermutet, also habe ich beschlossen, mit den Nachbarn zu reden. Übrigens, ist Adams auch daran beteiligt? Und was ist mit Jane? Könnte sie vielleicht...";
			link.l1.go = "DTSG_RalfFaggl_4";
		break;
		
		case "DTSG_RalfFaggl_4":
			dialog.text = "Neugier hat die Katze getötet, hast du das nicht gehört? Du wurdest aufgefordert zum Duell zu erscheinen, nicht herumzuschnüffeln. Du hättest eine Chance haben können, dieses Durcheinander zu überleben\nNatürlich. Den alten Dienstmann provozieren und seinen Kommandanten zum Duell zwingen - ein perfekter Plan, den wir mit Peter ausgedacht haben, denke ich. Und Jane hat ihren Teil auch gut gemacht.";
			link.l1 = "Sag mir, wer wollte Charlie loswerden?";
			link.l1.go = "DTSG_RalfFaggl_5";
		break;
		
		case "DTSG_RalfFaggl_5":
			dialog.text = "Ha, als ob ich es dir sagen würde? Verteidige dich.";
			link.l1 = "Schade. Dann werde ich später Peter fragen.";
			link.l1.go = "DTSG_RalfFaggl_6";
		break;
		
		case "DTSG_RalfFaggl_6":
			DialogExit();
			
			sld = CharacterFromID("DTSG_FrederikStouks");
			LAi_SetCheckMinHP(sld, 1, true, "DTSG_FrederikStouks_ranen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_RalfFaggl");
			LAi_SetCheckMinHP(sld, 1, false, "DTSG_RalfFaggl_ubit");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_PiterAdams_11":
			dialog.text = "Oh, ich sehe, dass Sie meine Geschichte zu Herzen genommen und Ralph bereits bestraft haben, Kapitän.";
			link.l1 = "Natürlich, denn wie du bemerkt hast, bin ich ein würdiger und edler Mann. Und jetzt muss ich dich für diese verräterische Falle bestrafen.";
			link.l1.go = "DTSG_PiterAdams_12";
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			GiveItem2Character(npchar, "letter_1");
			ChangeItemName("letter_1", "itmname_specialletter");
			ChangeItemDescribe("letter_1", "itmdescr_DTSG_letter2");
		break;
		
		case "DTSG_PiterAdams_12":
			dialog.text = "Sie können es gerne versuchen, Kapitän - sicherlich sind Sie bereits erschöpft und verwundet.";
			link.l1 = "Dann machen wir eine Pause. Sag mir in der Zwischenzeit, für wen arbeitest du?";
			link.l1.go = "DTSG_PiterAdams_13";
		break;
		
		case "DTSG_PiterAdams_13":
			dialog.text = "Entschuldigung, aber mein Patron würde das nicht mögen, selbst wenn ich danach erfolgreich mit dir umgehen könnte. Was übrigens jetzt passieren wird.";
			link.l1 = "Verdammt!..";
			link.l1.go = "DTSG_PiterAdams_14";
		break;
		
		case "DTSG_PiterAdams_14":
			DialogExit();
			
			if (MOD_SKILL_ENEMY_RATE > 4)
			{
				sld = CharacterFromID("DTSG_FrederikStouks");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, GetCharacterBaseHPValue(sld)/2, GetCharacterBaseHPValue(sld));
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			else
			{
				sld = CharacterFromID("DTSG_FrederikStouks");
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
				LAi_KillCharacter(sld);
			}
			
			sld = CharacterFromID("Knippel");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("DTSG_PiterAdams");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Sosedi_Pobeda");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_Knippel_40":
			dialog.text = "Ich kann es nicht fassen, diese... diese Schurken haben uns nicht nur getäuscht, sondern auch über die königliche Marine gelogen! Wie wagen sie es! Wenn sie nicht tot wären, würde ich sie ein paar Kettenschüsse für solchen Verrat schlucken lassen!..";
			link.l1 = "Leute lügen über alle möglichen Dinge, Charlie. Ich dachte, du wüsstest das gut. Aber was du sicherlich weißt, ist wer sie geschickt hat. Dies ist nicht die erste Falle, die in letzter Zeit für dich gestellt wurde. Sie hatten einen Brief mit einer detaillierten Beschreibung von dir. Wen hast du so sehr verärgert?";
			link.l1.go = "DTSG_Knippel_41";
		break;
		
		case "DTSG_Knippel_41":
			dialog.text = "Nun, ich... Vielleicht finden wir noch etwas anderes im Haus der Adams, Herr?";
			link.l1 = "Ausweichen der Frage? Aber du hast recht, ich hatte sowieso vor, es gründlich zu durchsuchen. Lass uns gehen.";
			link.l1.go = "DTSG_Knippel_42";
		break;
		
		case "DTSG_Knippel_42":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition.l1 = "ExitFromLocation";
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition.l1.location = PChar.location;
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition = "DTSG_PoP_ProverimSunduk";
		break;
		
		case "DTSG_Knippel_50":
			dialog.text = "Heilige Kanonenkugeln, so viel Gold!";
			link.l1 = "Schade, dass hier sonst nichts ist. 'Jane' ist auch nirgendwo zu finden. Glaubst du, sie lebt noch?";
			link.l1.go = "DTSG_Knippel_51";
		break;
		
		case "DTSG_Knippel_51":
			dialog.text = "Ich weiß nicht, Herr, solche Schurken sind zu allem fähig...";
			link.l1 = "Das ist wahr, aber es scheint mir, dass du mehr weißt, als du sagst. Dies ist nicht das erste Mal, dass sie dich jagen. Und jedes Mal finden wir einen Haufen Geld bei ihnen.";
			link.l1.go = "DTSG_Knippel_52";
		break;
		
		case "DTSG_Knippel_52":
			dialog.text = "Ich bin mir nicht sicher, Kapitän, aber vielleicht war es ein Geldverleiher aus St. John's.";
			link.l1 = "Wie hast du ihn übers Ohr gehauen?";
			link.l1.go = "DTSG_Knippel_53";
		break;
		
		case "DTSG_Knippel_53":
			dialog.text = "Nun... vor einiger Zeit habe ich von ihm Geld geliehen, um all meine anderen Schulden zu begleichen. Richard versprach, dafür zu bezahlen, aber...";
			link.l1 = "Glaubst du, er hat es nicht getan?";
			link.l1.go = "DTSG_Knippel_54";
		break;
		
		case "DTSG_Knippel_54":
			dialog.text = "Ich hätte es vorher nicht geglaubt, aber nachdem, was er Ihnen angetan hat und hastig mit Abi die Karibik verlassen hat... Vielleicht hat er die Schuld vergessen. Oder er hat es nicht getan, ist aber trotzdem gegangen... Richard hat sich wie ein echter Arsch benommen, Herr. Ich würde mich nicht wundern, aber immer noch enttäuscht sein, wenn es sich wieder als wahr herausstellt.";
			link.l1 = "Sei nicht so voreilig kategorisch, Charlie. Also, St. John's ist es.";
			link.l1.go = "DTSG_Knippel_55";
		break;
		
		case "DTSG_Knippel_55":			//КОНЕЦ ЭТАПА 2
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.location = "None";
			
			n = Findlocation("PortPax_town");
			locations[n].reload.l31.name = "houseF1";
			locations[n].reload.l31.go = "CommonRoom_MH9";
			locations[n].reload.l31.emerge = "reload1";
			locations[n].reload.l31.autoreload = "0";
			locations[n].reload.l31.label = "House";
			
			BackItemName("letter_1");
			BackItemDescribe("letter_1");
			TakeItemFromCharacter(pchar, "letter_1");
			AddQuestRecord("DTSG", "5");
			QuestOpenSeaExit()
			
			AddMapQuestMarkCity("SentJons", true);
			PChar.quest.DTSG_Etap3_Start.win_condition.l1 = "location";
			PChar.quest.DTSG_Etap3_Start.win_condition.l1.location = "Antigua";
			PChar.quest.DTSG_Etap3_Start.win_condition = "DTSG_Etap3_Start";
		break;
		
		case "DTSG_PiterAdams_20":
			if (CheckAttribute(pchar, "questTemp.DTSG_ZovemMatrosov"))
			{
				dialog.text = "Ach, da bist du ja, Herr - es scheint, alle haben sich entschieden, früh zu kommen. Nach deinem Aussehen zu urteilen, scheinst du ziemlich unbeschwert zu sein, bist du so überzeugt von deinen Fähigkeiten?";
				link.l1 = "Natürlich ist dies bei weitem nicht mein erstes Duell.";
				link.l1.go = "DTSG_PiterAdams_Nastoroje_21";
				ChangeCharacterComplexReputation(pchar, "authority", 1);
			}
			else
			{
				dialog.text = "Ich hatte Angst, Sie würden nicht kommen, Herr. Die anderen sind bereits hier.";
				link.l1 = "Ein wahrer Edelmann kann nur zu seinem Tod zu spät kommen.";
				link.l1.go = "DTSG_PiterAdams_NN_21";
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
			}
		break;
		
		case "DTSG_PiterAdams_NN_21":
			dialog.text = "Wunderbare Worte, Herr! Treffen Sie unseren Gegner, Ralph Faggle. Und das ist unser Zweiter, Frederick Stokes.";
			link.l1 = "";
			link.l1.go = "DTSG_PiterAdams_NN_22";
		break;
		
		case "DTSG_PiterAdams_NN_22":
			dialog.text = "Treffen...";
			link.l1 = "";
			link.l1.go = "DTSG_PiterAdams_NN_23";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_23":
			dialog.text = "Unser Gegner, Ralph Faggle.";
			link.l1 = "";
			link.l1.go = "DTSG_PiterAdams_NN_24";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_24":
			dialog.text = "Und das ist unser Zweiter, Frederick Stokes.";
			link.l1 = "";
			link.l1.go = "DTSG_PiterAdams_NN_25";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_FrederikStouks"));
		break;
		
		case "DTSG_PiterAdams_NN_25":
			dialog.text = "...";
			link.l1 = "Also das ist Ralph? Er sieht nicht aus wie ein typischer betrunkener Nachbar.";
			link.l1.go = "DTSG_PiterAdams_NN_26";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_26":
			dialog.text = "Sie wissen nie, wer Ihr Nachbar sein könnte, haben Sie darüber nachgedacht, Herr de Maure? Heh-heh-heh.";
			link.l1 = "Also, das ist eine Falle... Ich sehe, du hast sogar aufgehört zu zittern. Müde vom Spielen des Fieberkranken?";
			link.l1.go = "DTSG_PiterAdams_NN_27";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_NN_27":
			dialog.text = "Das einzige, was ich jetzt schütteln könnte, ist das Lachen über deine Naivität.";
			link.l1 = "Nun, nun. Es tut mir nur leid, dass Charlie mitgekommen ist - es wäre einfacher und ruhiger gewesen, mit dir ganz alleine fertig zu werden...";
			link.l1.go = "DTSG_PiterAdams_BitvaDuel";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_21":
			dialog.text = "Nun, das ist wunderbar!";
			link.l1 = "";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_22";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_22":
			dialog.text = "Erlauben Sie mir, mich vorzustellen...";
			link.l1 = "";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_23";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_23":
			dialog.text = "Herr Stokes, unser Zweiter.";
			link.l1 = "";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_24";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_FrederikStouks"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_24":
			dialog.text = "Und das ist Ralph Faggle.";
			link.l1 = "Also das ist Ralph? Ich muss zugeben, ich habe ihn mir anders vorgestellt. Aber egal, ich habe schon mit Schlimmerem zu tun gehabt.";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_25";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_25":
			dialog.text = "Hmm, ich frage mich, bist du naiv, verstehst du nichts? Oder so übermütig?";
			link.l1 = "Und was verstehe ich nicht, Herr Adams? Komm schon, überrasche mich.";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_26";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_Nastoroje_26":
			dialog.text = "Normalerweise sind die Leute in solchen Situationen überrascht oder verängstigt, aber Sie scheinen ein anderer Typ zu sein. Es wird umso angenehmer sein, dieses selbstgefällige Grinsen von Ihrem Gesicht zu wischen, Herr de Maure.";
			link.l1 = "Welche Drohungen! Sind wir nicht auf der gleichen Seite, Peter?";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_27";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_27":
			dialog.text = "Erzähl mir nicht, dass du hoffst, uns alle mit diesem alten Mann zu besiegen. Du bist in der Unterzahl, mein lieber Herr.";
			link.l1 = "Wie ich schon sagte, DU bist derjenige, der es nicht versteht. Charlie hat ein bisschen gemurrt, aber ich habe ihm trotzdem gesagt, er soll die Jungs hierher bringen, nur für den Fall. Wie es sich herausstellt, nicht umsonst. JUNGS, KOMMT HIERHER!!!";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_28";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_28":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			locCameraFromToPos(0.34, 0.51, 34.93, true, -5.63, -1.20, 57.46);
			DoQuestCheckDelay("DTSG_PoP_Duel_Podkreplenie", 3.0);
			
			int DTSG_PoP_MK;
			if (MOD_SKILL_ENEMY_RATE == 2) DTSG_PoP_MK = 5;
			if (MOD_SKILL_ENEMY_RATE == 4) DTSG_PoP_MK = 5;
			if (MOD_SKILL_ENEMY_RATE == 6) DTSG_PoP_MK = 4;
			if (MOD_SKILL_ENEMY_RATE == 8) DTSG_PoP_MK = 4;
			if (MOD_SKILL_ENEMY_RATE == 10) DTSG_PoP_MK = 3;
			
			for (i=1; i<=DTSG_PoP_MK; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DTSG_PoP_Matrosy_"+i, "citiz_3"+i, "man", "man", sti(pchar.rank)-5, sti(pchar.nation), -1, false, "quest"));
				GiveItem2Character(sld, "blade_11");
				sld.equip.blade = "blade_11";
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.lifeday = 0;
				LAi_SetHP(sld, 120.0, 120.0);
			}
		break;
		
		case "DTSG_PiterAdams_Nastoroje_29":
			dialog.text = "Was?..";
			link.l1 = "Überrascht und verängstigt, Herr Adams? Gut zu wissen.";
			link.l1.go = "DTSG_PiterAdams_BitvaDuel";
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_BitvaDuel":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_ExitTown")], false);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=5; i++)
			{
				if (GetCharacterIndex("DTSG_PoP_Matrosy_"+i) != -1)
				{
					sld = CharacterFromID("DTSG_PoP_Matrosy_"+i);
					LAi_SetWarriorType(sld);
					LAi_CharacterDisableDialog(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			
			sld = CharacterFromID("Knippel");
			LAi_SetWarriorType(sld);
			LAi_SetCheckMinHP(sld, 10, true, "KnippelRanen");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("DTSG_PiterAdams");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_FrederikStouks");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_RalfFaggl2");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_PiterAdams_Duel_Pobeda");
		break;
		
		case "DTSG_Knippel_60":
			dialog.text = "So sollte man mit solchen lügenden Schurken umgehen. Ich kann immer noch nicht glauben, dass sie es gewagt haben, über die königliche Marine zu lügen! Ich würde sie mit einer Kettenkugel erdrosseln!..";
			link.l1 = "Bis jetzt solltest du wissen, dass manchen Menschen Skrupel fehlen, Charlie. Ich habe gesagt, ich würde mich darum kümmern, du hättest auf dem Schiff bleiben können. Wolltest du sichergehen, dass ich diesen 'würdigen Leuten' helfe? Und wer hatte wieder recht, dass es nicht so einfach war, wie du dachtest?";
			link.l1.go = "DTSG_Knippel_61";
		break;
		
		case "DTSG_Knippel_61":
			dialog.text = "Sie, Herr...";
			link.l1 = "Genau. Aber sag mir, warum sollte jemand dich jagen wollen? Es ist nicht das erste Mal.";
			link.l1.go = "DTSG_Knippel_62";
		break;
		
		case "DTSG_Knippel_62":
			dialog.text = "Ich weiß nicht, Kapitän. Der alte Charlie ist nur ein einfacher Kanonier.";
			link.l1 = "Hmm, nun, nun. Na gut, da unsere armen Duellanten nichts Nützliches bei sich hatten... Nein, lass uns sehen, ob wir etwas im Haus von Adams finden können.";
			link.l1.go = "DTSG_Knippel_63";
		break;
		
		case "DTSG_Knippel_63":
			DialogExit();
			
			LAi_RemoveCheckMinHP(npchar);
			LAi_SetImmortal(npchar, false);
			AddDialogExitQuestFunction("DTSG_Knippel_64");
		break;
		
		case "DTSG_Knippel_70":
			dialog.text = "Also, diese Frau ist auch verschwunden... Vielleicht bereiteten sie sich darauf vor, die Stadt gleich nach diesem 'Duell' zu fliehen? Und in Eile - so viel Gold hier!";
			link.l1 = "Du hast recht, denn Gold ist nicht das einzige, was sie zurückgelassen haben. Noch ein Brief. Sie hatten so viel Eile, dass sie vergaßen, ihn zu verbrennen. Schau, der Inhalt wird dir gefallen.";
			link.l1.go = "DTSG_Knippel_71";
		break;
		
		case "DTSG_Knippel_71":
			TakeItemFromCharacter(pchar, "letter_1");
			dialog.text = "(liest) Nun, ich würde über 'alt' streiten.";
			link.l1 = "Das ist jetzt nicht der Punkt. Das ist das zweite Mal, dass sie Söldner nach dir geschickt und sie mit Geld und Informationen versorgt haben. Und sie wollen speziell dich. Sag mir, du einfacher Kanonier, wen könntest du so sehr verärgert haben?";
			link.l1.go = "DTSG_Knippel_72";
		break;
		
		case "DTSG_Knippel_72":
			dialog.text = "Ich habe nur eine Vermutung, Herr, nur eine, und ich möchte wirklich nicht, dass sie wahr ist.";
			link.l1 = "Also, es ist wahrscheinlich wahr. Sprich.";
			link.l1.go = "DTSG_Knippel_73";
		break;
		
		case "DTSG_Knippel_73":
			dialog.text = "Ich hatte einst Schulden bei verschiedenen Leuten in St. John's, und...";
			link.l1 = "... und jetzt denkst du, sie jagen dich? Wie viele können sich Söldner und solche Summen leisten?";
			link.l1.go = "DTSG_Knippel_74";
		break;
		
		case "DTSG_Knippel_74":
			dialog.text = "Sie denken richtig, Herr. Am Ende habe ich fast alle meine Schulden durch einen Kredit bei einem Geldverleiher abbezahlt. Er kann sich das natürlich leisten. Aber...";
			link.l1 = "Aber was? Wir werden deine Schulden bezahlen, und das war's. Was beunruhigt dich?";
			link.l1.go = "DTSG_Knippel_75";
		break;
		
		case "DTSG_Knippel_75":
			dialog.text = "Sie sehen, Kapitän, Richard hat mir versprochen, dass er es für mich abbezahlen würde.";
			link.l1 = "Glaubst du, er hat es nicht getan?";
			link.l1.go = "DTSG_Knippel_76";
		break;
		
		case "DTSG_Knippel_76":
			dialog.text = "Ich weiß nicht mehr, was ich denken soll, Herr. Die ganze Zeit, die wir uns kannten, kannte ich ihn als ein vorbildliches Gentleman. Aber nachdem er Sie verlassen hat und mit Abigail geflohen ist... Ich wäre nicht überrascht. Deshalb habe ich gesagt, ich würde es nicht wollen, dass es wahr ist.";
			link.l1 = "Vermutungen müssen zuerst überprüft werden, dann kannst du dich aufregen, Charlie. Los geht's, du wirst St. John's wieder besuchen.";
			link.l1.go = "DTSG_Knippel_77";
		break;
		
		case "DTSG_Knippel_77":			//КОНЕЦ ЭТАПА 2
			DialogExit();
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			
			n = Findlocation("PortPax_town");
			locations[n].reload.l31.name = "houseF1";
			locations[n].reload.l31.go = "CommonRoom_MH9";
			locations[n].reload.l31.emerge = "reload1";
			locations[n].reload.l31.autoreload = "0";
			locations[n].reload.l31.label = "House";
			
			BackItemName("letter_1");
			BackItemDescribe("letter_1");
			AddQuestRecord("DTSG", "6");
			QuestOpenSeaExit()
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_LocationDisableOfficersGen("PortPax_ExitTown", false);
			
			AddMapQuestMarkCity("SentJons", true);
			PChar.quest.DTSG_Etap3_Start.win_condition.l1 = "location";
			PChar.quest.DTSG_Etap3_Start.win_condition.l1.location = "Antigua";
			PChar.quest.DTSG_Etap3_Start.win_condition = "DTSG_Etap3_Start";
		break;
		
		case "DTSG_Knippel_PoPDuelTime":
			dialog.text = "Kapitän!!!";
			link.l1 = "Was ist los, Charlie, was ist passiert?";
			link.l1.go = "DTSG_Knippel_PoPDuelTime_2";
		break;
		
		case "DTSG_Knippel_PoPDuelTime_2":
			dialog.text = "Passiert?! Erzählen Sie mir nicht, dass Sie das Duell vergessen haben, Sir! Adams könnte schon in Stücke gehackt sein, während Sie hier herumlungern!";
			link.l1 = "Richtig!.. Ich werde sofort die Stadt verlassen.";
			link.l1.go = "DTSG_Knippel_PoPDuelTime_3";
		break;
		
		case "DTSG_Knippel_PoPDuelTime_3":
			DialogExit();
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			DoQuestReloadToLocation("PortPax_ExitTown", "reload", "reload3", "");
		break;
		
		case "DTSG_AntiguaArest":
			dialog.text = "Kapitän Charles de Maure? Ist das Charlie Knippel bei dir?";
			link.l1 = "Nein, das...";
			link.l1.go = "DTSG_AntiguaArest_2";
		break;
		
		case "DTSG_AntiguaArest_2":
			dialog.text = "Bestreiten Sie es nicht, Herr - jeder in dieser Kolonie kennt Charlie.";
			link.l1 = "Dann warum fragen? Wie kann ich helfen?";
			link.l1.go = "DTSG_AntiguaArest_3";
		break;
		
		case "DTSG_AntiguaArest_3":
			dialog.text = "Du kannst nicht. Bitte leiste keinen Widerstand - Charlie wird hier gesucht. Wir müssen ihn in Gewahrsam nehmen.";
			link.l1 = "Darf ich wissen, welche Vorwürfe gegen meinen Mann erhoben werden? Ist es wegen seiner Schulden? Ich kann sie für ihn bezahlen. Gehen wir gleich zum Bankier, in Ihrer Anwesenheit.";
			link.l1.go = "DTSG_AntiguaArest_4";
		break;
		
		case "DTSG_AntiguaArest_4":
			dialog.text = "Eine Schuld? Das höre ich zum ersten Mal. Ich kenne die Einzelheiten nicht, aber bitte, verkompliziere die Dinge nicht - Ich folge nur den Befehlen.";
			link.l1 = "Oh, das ist einfach großartig...";
			link.l1.go = "DTSG_AntiguaArest_5";
		break;
		
		case "DTSG_AntiguaArest_5":
			StartInstantDialog("Knippel", "DTSG_AntiguaArest_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_AntiguaArest_6":
			dialog.text = "Kapitän...";
			link.l1 = "Charlie, wenn wir jetzt fliehen, wird das Kopfgeld auf uns noch höher sein. Und wir können uns nicht durchkämpfen? Ich werde versuchen, dich rauszuholen, mach nur nichts Dummes!";
			link.l1.go = "DTSG_AntiguaArest_7";
		break;
		
		case "DTSG_AntiguaArest_7":
			DialogExit();
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			AddQuestRecord("DTSG", "8");
			pchar.questTemp.DTSG_KnippelDolg = true;
			
			sld = CharacterFromID("Knippel");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload_jail", "", "", "", "", -1);
			sld.location = "None";
			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("DTSG_AntiguaSold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload_jail", "", "", "", "", -1);
				sld.location = "None";
			}
		break;
		
		case "DTSG_AntiguaStrazhBank":
			dialog.text = "Hören Sie sofort auf, Lärm zu machen und diesen Mann zu bedrohen, Herr. Geben Sie Ihre Waffen ab und folgen Sie mir auf der Stelle!";
			link.l1 = "Ich habe niemanden bedroht, es gab einen Fehler. Das ist eine Geschäftsangelegenheit, kein versuchter Mord.";
			link.l1.go = "DTSG_AntiguaStrazhBank_2";
		break;
		
		case "DTSG_AntiguaStrazhBank_2":
			dialog.text = "Sieht für mich nicht danach aus. Du wirst dich vor dem Gesetz verantworten müssen.";
			link.l1 = "Was ist, wenn ich mich entschuldige und gehe?";
			link.l1.go = "DTSG_AntiguaStrazhBank_3";
		break;
		
		case "DTSG_AntiguaStrazhBank_3":
			dialog.text = "So können Sie sich wieder einschleichen und beenden, was ich unterbrochen habe? Denken Sie, ich bin dumm?";
			link.l1 = "Du musst es sein, wenn du das nicht friedlich regeln willst. Gott weiß, ich wollte nicht, dass es dazu kommt...";
			link.l1.go = "DTSG_AntiguaStrazhBank_4";
		break;
		
		case "DTSG_AntiguaStrazhBank_4":
			DialogExit();
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_bank")], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_AntiguaStrazhBank_Ubili");
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki":
			dialog.text = "Du hast ihn getötet!..";
			link.l1 = "Betrachten Sie es als von Ihren eigenen Händen getan, Herr. Sie hätten einfach meine Fragen beantworten können, anstatt hysterisch zu sein. Ich schwöre, noch ein Schrei und ich puste dir das Gehirn raus.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_V1";
			link.l2 = "Ja, ich habe ihn getötet. Er hat mich dazu gezwungen. Aber du bist nicht so hirnlos wie er und wirst seinem Beispiel nicht folgen, oder?";
			link.l2.go = "DTSG_AntiguaUsurer_PosleDraki_V2";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_V1":
			dialog.text = "Was willst du?!";
			link.l1 = "Vor einiger Zeit hat Charlie Knippel Geld von Ihnen geliehen. Sein Freund versprach, seine Schulden zu begleichen, hat es aber anscheinend nicht getan. Ich fordere Sie auf, sofort aufzuhören, Söldner auf uns zu hetzen. Ich bin bereit, Charlies Schuld jetzt sofort zu begleichen, wenn ich es mir leisten kann.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_3";
			AddComplexLandExpToScill(100, 0, 0);
			AddComplexSeaExpToScill(0, 0, 0, 0, 0, 0, 100);
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_V2":
			dialog.text = "Was willst du?!";
			link.l1 = "Vor einiger Zeit hat Charlie Knippel Geld von Ihnen geliehen. Sein Freund versprach, seine Schulden zu begleichen, hat es aber anscheinend nicht getan. Ich verlange, dass Sie sofort aufhören, Söldner hinter uns her zu schicken. Ich bin bereit, Charlies Schulden jetzt sofort zu begleichen, wenn ich es mir leisten kann.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_3";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_3":
			dialog.text = "Charlie?! I would never do that to him; he's a good, honest man. Besides, his debt has long been paid off. Mr. Fleetwood, the captain of the Valkyrie, settled it to the last peso.";
			link.l1 = "Wirklich? Ich weiß, wer er ist. Das hättest du gleich sagen sollen. Entschuldigung für die Unannehmlichkeiten, auf Wiedersehen.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_4";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_4":
			dialog.text = "So einfach?! Du hast mich bedroht! Und einen Mann getötet!..";
			link.l1 = "Hast du vergessen, was ich gesagt habe? Noch ein Schrei und du wirst ihm folgen. Auf Wiedersehen.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_5";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_5":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_bank")], true);
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			npchar.dialog.filename = "Usurer_dialog.c";
			npchar.dialog.currentnode = "First time";
			LAi_SetOwnerType(npchar);
			
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "fame", 2);
			
			chrDisableReloadToLocation = false;
			AddQuestRecord("DTSG", "9");
			PChar.quest.DTSG_AntiguaTrevoga.win_condition.l1 = "location";
			PChar.quest.DTSG_AntiguaTrevoga.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_AntiguaTrevoga.win_condition = "DTSG_AntiguaTrevoga";
		break;
		
		case "DTSG_Killer":
			dialog.text = "Noch hier und noch nicht gehängt? Nun, beste Grüße aus Sussex, Charlie.";
			link.l1 = "Grüße an dich, wer auch immer du bist.";
			link.l1.go = "DTSG_Killer_2";
			CharacterTurnToLoc(npchar, "goto", "goto9");
		break;
		
		case "DTSG_Killer_2":
			dialog.text = "Ach, Charles de Maure. Gut von dir, den armen Charlie zu besuchen. Wir haben darauf gezählt.";
			link.l1 = "Wer sind wir?";
			link.l1.go = "DTSG_Killer_3";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "DTSG_Killer_3":
			dialog.text = "Das spielt keine Rolle. Sie haben uns erhebliche Zeit und Geld gekostet, Herr de Maure. Ich denke, es wird ihnen nichts ausmachen, wenn ich mich hier und jetzt um Charlie und Sie kümmere.";
			link.l1 = "Nun, da wir sowieso beide tot sind, könntest du uns aus Güte deines Herzens sagen, wen wir so sehr verärgert haben? Wir versprechen, es nicht noch einmal zu tun. Und wer ist Sussex?";
			link.l1.go = "DTSG_Killer_4";
		break;
		
		case "DTSG_Killer_4":
			dialog.text = "Kann nicht. Die Pflicht ruft und, im Gegensatz zu dir, bin ich ein Mann der Tat, nicht der Worte.";
			link.l1 = "Um Himmels Willen, wird mir jemals jemand erklären, was hier vor sich geht?!";
			link.l1.go = "DTSG_Killer_5";
		break;
		
		case "DTSG_Killer_5":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetImmortal(npchar, false);
			
			for (i=1; i<=12; i++)
			{
				if (GetCharacterIndex("SentJonsPrisoner_"+i) != -1)
				{
					sld = CharacterFromID("SentJonsPrisoner_"+i);
					sld.lifeday = 0;
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
			
			for (i = 0; i < MAX_CHARACTERS; i++)
			{
				sld = GetCharacter(i);
				if (sld.city == "sentjons" && sld.location == "SentJons_prison")
				{
					sld.lifeday = 0;
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
			
			sld = CharacterFromID("SentJonsJailOff");
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_SentJonsJailOff", "off_eng_1", "man", "man", 30, PIRATE, 0, true, "soldier"));
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto18");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld.rank = 30;
			SetSelfSkill(sld, 80, 80, 80, 80, 80);
			LAi_SetHP(sld, 200+MOD_SKILL_ENEMY_RATE*20, 200+MOD_SKILL_ENEMY_RATE*20);
			
			for (i=1; i<=3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DTSG_AntiguaSoldTurma_"+i, "sold_eng_"+(rand(15)+1), "man", "man", sti(pchar.rank), PIRATE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto22");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			
			for (i=4; i<=7; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DTSG_AntiguaSoldTurma_"+i, "sold_eng_"+(rand(15)+1), "man", "man", sti(pchar.rank), PIRATE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, "SentJons_prison", "reload", "reload1");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			
			/*sld = CharacterFromID("SentJons_Mayor");
			LAi_group_Attack(sld, Pchar);*/
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_TurmaDayPobeda");
		break;
		
		case "DTSG_KnippelDaySpasen":
			dialog.text = "Nun, verdammt noch mal, Kapitän, was für ein Gemetzel hast du hier angerichtet!";
			link.l1 = "Einwände? Bevorzugst du das Galgen? Oder möchtest du lieber hier auf unbestimmte Zeit verrotten?";
			link.l1.go = "DTSG_KnippelDaySpasen_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_KnippelDaySpasen_2":
			dialog.text = "Nein, Herr. Danke, dass Sie mich gerettet haben. Um ehrlich zu sein, bin ich überrascht, dass Sie gekommen sind, wenn man bedenkt, wie leicht Sie sie mich nehmen ließen. Und überrascht, wie leicht Sie mit dem Wächter umgegangen sind - er war ein See Fuchs. Ein Marine.";
			link.l1 = "Ich sagte dir, ich würde dich rausholen, du hättest nicht zweifeln sollen. Jetzt raus aus dieser Zelle, bevor die ganze Garnison hier ist.";
			link.l1.go = "DTSG_KnippelDaySpasen_3";
		break;
		
		case "DTSG_KnippelDaySpasen_3":
			dialog.text = "Jawohl, Kapitän.";
			link.l1 = "";
			link.l1.go = "DTSG_KnippelDaySpasen_4";
		break;
		
		case "DTSG_KnippelDaySpasen_4":
			DialogExit();
			
			Pchar.GenQuest.Hunter2Pause = true;
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("DTSG_TurmaDayPobeda_2", 1.0);
		break;
		
		case "DTSG_KnippelDaySpasen_5":
			dialog.text = "Scheiße, Herr, ich kann es kaum glauben...";
			link.l1 = "Apropos, sag mir, was haben sie dir vorgeworfen? Und wer ist Sussex?";
			link.l1.go = "DTSG_KnippelDaySpasen_6";
		break;
		
		case "DTSG_KnippelDaySpasen_6":
			dialog.text = "Ich weiß es nicht, Herr. Ich habe keine Ahnung, wen sie damit meinten...";
			link.l1 = "In Ordnung, wir werden es später herausfinden. Jetzt müssen wir hier raus.";
			link.l1.go = "DTSG_KnippelDaySpasen_7";
		break;
		
		case "DTSG_KnippelDaySpasen_7":
			DialogExit();
			
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			AddPassenger(pchar, npchar, false);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			AddQuestRecord("DTSG", "12");
			
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition = "DTSG_KnippelRazgovorVKaute";
		break;
		
		case "DTSG_AntiguaNightPirs":
			dialog.text = "Was sind Ihre nächsten Schritte, Herr? Diesen Blutsauger mitten am Tag zur Vernunft zu prügeln, ist ein riskantes Geschäft.";
			link.l1 = "Du hast mir gerade eine Idee gegeben. Warum sollten wir ihm bei Tageslicht einen Sinneswandel verpassen, wenn wir es jetzt, im Schutz der Nacht, tun können?";
			link.l1.go = "DTSG_AntiguaNightPirs_2";
		break;
		
		case "DTSG_AntiguaNightPirs_2":
			dialog.text = "Verdammt, das ist eine brillante Idee, Kapitän!";
			link.l1 = "Genau. Sag mal, Charlie, du hast hier eine Weile gelebt. Weißt du, wo der Geldverleiher wohnt?";
			link.l1.go = "DTSG_AntiguaNightPirs_3";
		break;
		
		case "DTSG_AntiguaNightPirs_3":
			dialog.text = "Ich wusste es früher, Herr, aber als ich das letzte Mal hier war, hat er sein Haus verkauft. Keine Ahnung, wo das neue ist.";
			link.l1 = "Nun, das ist ein Problem...";
			link.l1.go = "DTSG_AntiguaNightPirs_4";
		break;
		
		case "DTSG_AntiguaNightPirs_4":
			dialog.text = "Ich bin sicher, Sie werden etwas herausfinden, Kapitän, schließlich haben Sie den großen, furchterregenden Lucas Rodenburg besiegt!";
			link.l2 = "In Ordnung, ich kümmere mich darum. Es wäre allerdings besser, wenn du wüsstest, wo das Haus des Geldverleihers ist!";
			link.l2.go = "DTSG_AntiguaIskat_1";
			link.l1 = "Dass habe ich. Aber der Morgen ist klüger als der Abend, Charlie. Lass uns von der Reise ausruhen und am Tag gehen - wir sind schließlich nicht hier, um den Mann zu ermorden.";
			link.l1.go = "DTSG_AntiguaSpat_1";
		break;
		
		case "DTSG_AntiguaSpat_1":
			dialog.text = "Sind Sie sicher, Herr? Wir verlieren das Überraschungsmoment.";
			link.l1 = "Ich bin sicher und ich bin müde. Außerdem will ich nur reden. Erschrecke ihn ein bisschen, wenn nötig.";
			link.l1.go = "DTSG_AntiguaSpat_2";
		break;
		
		case "DTSG_AntiguaSpat_2":
			TavernWaitDate("wait_day");
			DoQuestReloadToLocation("SentJons_tavern_upstairs", "goto", "goto2", "DTSG_AntiguaSpat_3");
		break;
		
		case "DTSG_AntiguaIskat_1":
			dialog.text = "Was ich nicht weiß - ich weiß es nicht, entschuldigen Sie, Herr.";
			link.l1 = "Ach, egal, lass uns ihn suchen.";
			link.l1.go = "DTSG_AntiguaIskat_2";
		break;
		
		case "DTSG_AntiguaIskat_2":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			AddQuestRecord("DTSG", "13");
			pchar.questTemp.DTSG_NightIskat = true;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.GenQuest.CannotWait = true;
			pchar.questTemp.TimeLock = true;
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood":
			dialog.text = "Denken Sie das Gleiche wie ich, Herr?";
			link.l1 = "Es tut mir leid, Charlie. Es gibt keinen anderen berühmten Kapitän mit diesem Namen in der Karibik. Und Richard ist nach London gegangen. Also, es ist unwahrscheinlich, dass es ein Zufall ist.";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_2";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_2":
			dialog.text = "Schrecklich... Obwohl ich viele harte Worte über ihn gesagt habe, habe ich ihm nie so etwas gewünscht! Und die arme Abi!.. Sie erwartete ein Kind. Ich hoffe, sie lebt noch...";
			link.l1 = "Tatsächlich, würde es niemandem wünschen. Hoffen wir, dass es Abi gut geht. Eine Ahnung, wer Dick das antun könnte? Hat er jemals von mächtigen Feinden gesprochen?";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_3";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_3":
			dialog.text = "Sie machen wohl Witze, Kapitän. Ich weiß nicht, wie es in Europa aussieht, aber hier wollte jeder Holländer, dass Richard tot ist.";
			link.l1 = "Wahr. Vielleicht hat hier jemand groß ausgegeben und Mörder nach ihm in die Alte Welt geschickt. Könnte es sein, dass nicht dieser kleine Geldverleiher hinter den Angriffen auf dich steckt, sondern ein mysteriöser Feind von Richard?";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_4";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_4":
			dialog.text = "Ich weiß nicht, Herr. Alles ist zu diesem Zeitpunkt möglich. Aber das würde die Dinge für uns alle komplizieren...";
			link.l1 = "Ja, du hast recht, diese Möglichkeit gefällt mir auch nicht.";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_5";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_5":
			DialogExit();
			npchar.location = "None";
			
			AddQuestRecord("DTSG", "14");
			pchar.questTemp.DTSG_Nastoroje2 = true;
			chrDisableReloadToLocation = false;
			
			PChar.quest.DTSG_NightDom.win_condition.l1 = "locator";
			PChar.quest.DTSG_NightDom.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_NightDom.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_NightDom.win_condition.l1.locator = "houseSp3";
			PChar.quest.DTSG_NightDom.win_condition = "DTSG_NightDom";
		break;
		
		case "DTSG_NightRostovshik":
			dialog.text = "Was, wer... WAS?! Was passiert hier?.. Wer bist du?!..";
			link.l1 = "Ach, komm schon. Wenn ich dich töten wollte, würde ich es im Schlaf tun. Also lass uns unser Leben nicht komplizieren oder verkürzen. Nicken Sie, wenn Sie verstehen.";
			link.l1.go = "DTSG_NightRostovshik_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_NightRostovshik_2":
			dialog.text = "Mm-hmm...";
			link.l1 = "Sehr gut. Beruhige dich - Ich bin nicht hier, um zu rauben, zu entführen oder dir zu schaden.";
			link.l1.go = "DTSG_NightRostovshik_3";
		break;
		
		case "DTSG_NightRostovshik_3":
			dialog.text = "Dann... warum bist du hier? Warum konntest du nicht am Morgen kommen?";
			link.l1 = "Weil eine wohlhabende, einflussreiche Person meinen Freund jagt. Wir haben Grund zu der Annahme, dass Sie es sind, daher ist es wahrscheinlich unsicher für ihn, bei hellichtem Tag auf diesen Straßen zu laufen.";
			link.l1.go = "DTSG_NightRostovshik_4";
		break;
		
		case "DTSG_NightRostovshik_4":
			dialog.text = "Aber ich verstehe wirklich nicht, wovon Sie sprechen, Herr...";
			link.l1 = "Charlie Knippel. Jeder in der Stadt kennt ihn. Denke gut nach. Er schuldet dir Geld.";
			link.l1.go = "DTSG_NightRostovshik_5";
		break;
		
		case "DTSG_NightRostovshik_5":
			dialog.text = "Unser alter Charlie?? Das ist wahr, aber seine Schulden wurden schon vor langer Zeit beglichen, wenn auch nicht von ihm persönlich.";
			link.l1 = "Und wer war dieser Wohltäter?";
			link.l1.go = "DTSG_NightRostovshik_6";
		break;
		
		case "DTSG_NightRostovshik_6":
			dialog.text = "Sein Kapitän, Lord Richard Fleetwood. Wenn Sie mir nicht glauben, kann ich Ihnen meine Aufzeichnungen zeigen.";
			link.l1 = "Fleetwood, sagst du? Dann glaube ich dir. Also hast du keine Söldner auf Charlie angesetzt?";
			link.l1.go = "DTSG_NightRostovshik_7";
		break;
		
		case "DTSG_NightRostovshik_7":
			dialog.text = "Natürlich nicht, warum sollte ich das tun?? Und sag mir, was würde das für einen Sinn machen?";
			link.l1 = "Tatsächlich. Nun, entschuldigung für den späten Besuch. Gute Nacht.";
			link.l1.go = "DTSG_NightRostovshik_8";
		break;
		
		case "DTSG_NightRostovshik_8":
			DialogExit();
			
			PChar.quest.DTSG_NightDom_3.win_condition.l1 = "locator";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.location = "SentJons_houseSP3";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.locator = "reload1";
			PChar.quest.DTSG_NightDom_3.win_condition = "DTSG_NightDom_3";
			
			LAi_CharacterDisableDialog(npchar);
			Pchar.GenQuest.Hunter2Pause = true;
			AddQuestRecord("DTSG", "15");
		break;
		
		case "DTSG_NightKiller":
			dialog.text = "Was, Charlie, hofftest du, dich heute Abend bei deinem ehemaligen Patron zu verstecken? Er ist nicht da. Aber du wirst ihn bald genug treffen. Beste Grüße aus Sussex.";
			link.l1 = "Das wussten wir bereits. Und wer ist Sussex? Und wer sind Sie?";
			link.l1.go = "DTSG_NightKiller_2";
		break;
		
		case "DTSG_NightKiller_2":
			dialog.text = "Das geht Sie nichts an, Herr de Maure. Schade, dass Sie sich mehr in dieses Durcheinander verwickelt haben, als uns lieb wäre. Sie sind eine Belästigung.";
			link.l1 = "Ein Ärgernis für wen? Bitte sag mir nicht, dass ich mit der Frau eines sehr einflussreichen und sehr wütenden Engländers geschlafen habe.";
			link.l1.go = "DTSG_NightKiller_3";
		break;
		
		case "DTSG_NightKiller_3":
			dialog.text = "Sehr lustig. Zeit gefunden zu scherzen. Anscheinend ist das, was ich über dich gehört habe, wahr\nWas wollen wir? Charlies Kopf würde genügen. Aber wenn man bedenkt, wie viel Ärger du uns bereitet hast, betrifft es diesmal auch dich - du steckst deine Nase immer dort hinein, wo sie nicht hingehört.";
			link.l1 = "Ich nehme an, wir sind verhaftet?";
			link.l1.go = "DTSG_NightKiller_4";
		break;
		
		case "DTSG_NightKiller_4":
			dialog.text = "Verhaftung? Nein, lieber Herr, die Zeit für Halbheiten ist vorbei. Dies ist eine Hinrichtung, Kapitän de Maure.";
			link.l1 = "Einverstanden. Die einzige Frage ist, wessen.";
			link.l1.go = "DTSG_NightKiller_5";
		break;
		
		case "DTSG_NightKiller_5":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Knippel");
			LAi_SetOfficerType(sld);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DTSG_Killers_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_NightKiller_Pobeda");
		break;
		
		case "DTSG_Knippel_80":
			dialog.text = "Ich hätte nicht gedacht, dass die Seefüchse involviert wären...";
			link.l1 = "Nun, es gibt immer ein erstes Mal für alles. Sag mir, Charlie, wer ist Sussex?";
			link.l1.go = "DTSG_Knippel_81";
		break;
		
		case "DTSG_Knippel_81":
			dialog.text = "Ich...";
			link.l1 = "Kannst du nicht sehen, wie weit das hier gegangen ist? Und es scheint, wir sitzen im selben Boot, Charlie. Also habe ich ein Recht, die Details zu erfahren.";
			link.l1.go = "DTSG_Knippel_82";
		break;
		
		case "DTSG_Knippel_82":
			dialog.text = "Natürlich, Kapitän. Aber nicht hier, oder? Lassen Sie uns von der Insel kommen und auf dem Schiff sprechen.";
			link.l1 = "Du hast recht. Also, lass uns beeilen.";
			link.l1.go = "DTSG_Knippel_83";
		break;
		
		case "DTSG_Knippel_83":
			DialogExit();
			AddQuestRecord("DTSG", "16");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DeleteAttribute(pchar,"questTemp.TimeLock");
			chrDisableReloadToLocation = false;
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition = "DTSG_KnippelRazgovorVKaute";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom":
			dialog.text = "Sie riefen, Kapitän?";
			link.l1 = "Ja, Charlie. Wir müssen reden. Ich denke, du hast schon erraten, worum es geht.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_2";
			DelLandQuestMark(npchar);
			//LAi_LocationDisableOfficersGen("SentJons_town", true);
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_2":
			dialog.text = "Jawohl, Herr...";
			link.l1 = "Gut. Sag mir, warum deine Landsleute, einschließlich der Elitekräfte, dich jagen, obwohl du kein Verbrecher oder dergleichen bist.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_3";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_3":
			dialog.text = "Ich weiß wirklich nicht, Herr...";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "Das ist kein Scherz, Charlie. Wer auch immer dich jagt, kann Befehle an die Seefüchse geben. Er steckt wahrscheinlich auch hinter Richards Mord. Also wenn du irgendwelche Gedanken hast, teile sie. Was für Grüße aus Sussex, wer ist das?";
			}
			else
			{
				link.l1 = "Hör auf wegzuschauen, Charlie. Ich sehe, du weißt etwas. Als dein Kapitän befehle ich dir, mir alles zu erzählen. Wer ist Sussex?";
			}
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_4";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_4":
			dialog.text = "In Ordnung, Kapitän. Sussex ist kein Mensch. Es ist... ein Schiff.";
			link.l1 = "Grüße von einem Schiff? Das ist Unsinn.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_5";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_5":
			dialog.text = "Lassen Sie mich erklären. Darf ich mich setzen, Herr? Die Geschichte ist lang und nicht sehr angenehm.";
			link.l1 = "Natürlich, Charlie. Nur zu.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_6";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_6":
			DialogExit();
			SetCurrentTime(2, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Knippel"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			DoQuestReloadToLocation("SentJons_houseH1", "goto", "goto2", "DTSG_KnippelDoma");
		break;
		
		case "DTSG_Kurier":
			dialog.text = "Hallo, Charlie, ich komme von Kapitän Fleetwood. Er möchte dich sehen.";
			link.l1 = "Danke, Kumpel. Ist etwas passiert? Normalerweise schickt er alles sofort durch dich.";
			link.l1.go = "DTSG_Kurier_2";
		break;
		
		case "DTSG_Kurier_2":
			dialog.text = "Ich weiß nicht. Er sagt, er möchte das direkt mit Ihnen besprechen. Es ist Ihre Angelegenheit, klären Sie das selbst.";
			link.l1 = "Oh, ich habe ein schlechtes Gefühl dabei...";
			link.l1.go = "DTSG_Kurier_3";
		break;
		
		case "DTSG_Kurier_3":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.lifeday = 0;
			npchar.location = "None";
			
			PChar.quest.DTSG_KD1.win_condition.l1 = "locator";
			PChar.quest.DTSG_KD1.win_condition.l1.location = "SentJons_houseH1";
			PChar.quest.DTSG_KD1.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_KD1.win_condition.l1.locator = "reload1";
			PChar.quest.DTSG_KD1.win_condition = "DTSG_KD1";
			
			PChar.quest.DTSG_KD2.win_condition.l1 = "locator";
			PChar.quest.DTSG_KD2.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_KD2.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_KD2.win_condition.l1.locator = "houseSp3";
			PChar.quest.DTSG_KD2.win_condition = "DTSG_KD2";
			
			pchar.questTemp.Knippel.Soldiers_1 = true;
		break;
		
		case "DTSG_Cortny":
			dialog.text = "...";
			link.l1 = "Gute Nacht, Herr!";
			link.l1.go = "DTSG_Cortny_2";
		break;
		
		case "DTSG_Cortny_2":
			dialog.text = "Gute Nacht. Lassen Sie mich durch.";
			link.l1 = "Natürlich, fahren Sie fort, ich entschuldige mich, Herr.";
			link.l1.go = "DTSG_Cortny_3";
		break;
		
		case "DTSG_Cortny_3":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.lifeday = 0;
			npchar.location = "None";
			
			PChar.quest.DTSG_KD4.win_condition.l1 = "locator";
			PChar.quest.DTSG_KD4.win_condition.l1.location = "SentJons_houseSP3";
			PChar.quest.DTSG_KD4.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_KD4.win_condition.l1.locator = "reload2";
			PChar.quest.DTSG_KD4.win_condition = "DTSG_KD4";
			
			sld = CharacterFromID("Fleetwood");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseSP3_room", "goto", "goto1");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Fleetwood";
			sld.greeting = "";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "DTSG_Fleetwood":
			dialog.text = "Ach, du bist es, Charlie. Komm rein, komm rein. Schließe die Tür hinter dir.";
			link.l1 = "Gute Nacht, Kapitän. Was ist los? Und wer war dieser Mann? Ein prahlerischer Pfau...";
			link.l1.go = "DTSG_Fleetwood_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_Fleetwood_2":
			dialog.text = "Dazu kann ich nichts sagen. Auch kann ich niemanden unser Gespräch belauschen lassen. Erzähle niemandem davon, verstanden?";
			link.l1 = "Ja, Herr. Ist etwas passiert? Sie sehen ungewöhnlich besorgt aus, das ist untypisch für Sie.";
			link.l1.go = "DTSG_Fleetwood_3";
		break;
		
		case "DTSG_Fleetwood_3":
			dialog.text = "Es scheint dir so. Du siehst auch nicht gerade gut aus - es ist schließlich Nacht. Aber ich fürchte, dein Schlaf ist für heute Nacht vorbei, mein Freund - wir haben eine dringende und geheime Mission.";
			link.l1 = "Und was wird es beinhalten, Kapitän?";
			link.l1.go = "DTSG_Fleetwood_4";
		break;
		
		case "DTSG_Fleetwood_4":
			dialog.text = "Beseitigung eines Verräters. Aus unseren eigenen Reihen. Bald wird ein diplomatisches Schiff aus der Alten Welt vor der Küste von Dominica auftauchen - die Fregatte 'Sussex'. Offiziell sind sie da, um einen guten Deal mit den Holländern auszuhandeln. Aber in Wirklichkeit...";
			link.l1 = "... werden sie Informationen an unsere Feinde weitergeben, Herr?";
			link.l1.go = "DTSG_Fleetwood_5";
		break;
		
		case "DTSG_Fleetwood_5":
			dialog.text = "Noch schlimmer. Vollständig zu ihrer Seite überlaufen. Und obwohl sie nach der Überquerung des Atlantiks erschöpft sein werden, ist es am Ende eine gute Fregatte, die sicher versuchen wird zu fliehen, wenn wir mit einem schweren Schiff angreifen\nAlso müssen wir schnell und entschlossen handeln. Wir können uns nur auf die 'Walküre' verlassen - sie ist die einzige, die für eine solche Mission in der Lage ist.";
			link.l1 = "Wird die alte 'Walküre' eine Fregatte bewältigen können?..";
			link.l1.go = "DTSG_Fleetwood_6";
		break;
		
		case "DTSG_Fleetwood_6":
			dialog.text = "Ha-ha, Charlie, zweifelst du an deinem Kapitän? Außerdem, wie ich schon sagte, werden sie erschöpft sein. Wenn wir plötzlich angreifen, liegen alle Vorteile bei uns.";
			link.l1 = "Ich würde niemals! Aber ich hoffe, Sie wissen, was Sie tun, Herr...";
			link.l1.go = "DTSG_Fleetwood_7";
		break;
		
		case "DTSG_Fleetwood_7":
			dialog.text = "Ich bin mir sicher. Und noch etwas. Dieser Überläufer hat eine hohe Position im Parlament selbst, verstehst du? Er könnte Augen und Ohren überall haben - nicht nur zu Hause, sondern bereits hier, in der Karibik. Also erwähne nicht die Sussex oder irgendwelche Details unserer Mission in der Stadt.";
			link.l1 = "Sie hätten es mir nicht sagen müssen, Herr. Sie können sich immer auf den alten Charlie verlassen.";
			link.l1.go = "DTSG_Fleetwood_8";
		break;
		
		case "DTSG_Fleetwood_8":
			dialog.text = "Ich weiß. Nur sind die Einsätze diesmal höher als je zuvor. Pack deine Sachen und mach dich bereit - wir segeln bei Tagesanbruch ab.";
			link.l1 = "Aye, Herr. Gute Nacht, Herr.";
			link.l1.go = "DTSG_Fleetwood_9";
		break;
		
		case "DTSG_Fleetwood_9":
			DoQuestReloadToLocation("SentJons_town", "reload", "houseSp3", "");
			
			PChar.quest.DTSG_KD5.win_condition.l1 = "locator";
			PChar.quest.DTSG_KD5.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_KD5.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_KD5.win_condition.l1.locator = "houseH1";
			PChar.quest.DTSG_KD5.win_condition = "DTSG_KD5";
		break;
		
		case "DTSG_Knippel_SamSoboi":
			dialog.text = "Ich habe Richard noch nie so gesehen... Er war so besorgt oder sogar... ängstlich?";
			link.l1 = "Aber warum? Er hat es nicht einmal mit mir geteilt. Nun, egal. Er ist ein großartiger Kapitän, also werden wir sicherlich diese Fregatte und ihre müde Besatzung meistern.";
			link.l1.go = "DTSG_Knippel_SamSoboi_2";
			DeleteAttribute(pchar, "questTemp.lockedMusic");
		break;
		
		case "DTSG_Knippel_SamSoboi_2":
			DialogExit();
			SetLaunchFrameFormParam("August 17th, 1654"+ NewStr() +", SE of Dominica", "DTSG_ProshloeDominika", 0, 4.0);
			LaunchFrameForm();
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_1");
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_2");
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_3");
		break;
		
		case "DTSG_Fleetwood_10":
			dialog.text = "Die 'Sussex' ist am Horizont, Charlie, mach dich bereit.";
			link.l1 = "Immer bereit, Kapitän.";
			link.l1.go = "DTSG_Fleetwood_11";
		break;
		
		case "DTSG_Fleetwood_11":
			dialog.text = "Sehr gut. Ich zähle auf dich und deine Kettenkugel. Versuche, ihre Segel so schnell wie möglich zu zerschneiden, oder noch besser, einen Mast zu fällen. Es macht keinen Sinn, sich auf einen riskanten Kampf einzulassen, um sie zu versenken, also werde ich versuchen, sie zu entern\nAußerdem müssen wir sicherstellen, dass der Verräter tot ist - wenn wir sie versenken, müssen wir uns immer noch nähern und sicherstellen, dass niemand überlebt.";
			link.l1 = "Und so viele Landsleute für einen Verräter töten...";
			link.l1.go = "DTSG_Fleetwood_12";
		break;
		
		case "DTSG_Fleetwood_12":
			dialog.text = "Leider. Es schmerzt mich auch, Charlie. Aber Befehle sind Befehle. Wenigstens tun wir das nicht zum Spaß. Also lass uns das schnell hinter uns bringen.";
			link.l1 = "Ja, Herr...";
			link.l1.go = "DTSG_Fleetwood_13";
		break;
		
		case "DTSG_Fleetwood_13":
			DialogExit();
			EndQuestMovie();
			AddItems(pchar, "potion4", 10);
			AddItems(pchar, "bullet", 10);
			AddItems(pchar, "GunPowder", 10);
			AddItems(pchar, "grapeshot", 10);
			AddItems(pchar, "cartridge", 10);
			PlaySound("interface\abordage.wav");
			PlaySound("interface\abordage.wav");
			PlaySound("interface\MusketFire1.wav");
			PlaySound("interface\MusketFire1.wav");
			
			SetLaunchFrameFormParam("2 hours later..."+ NewStr() +"Boarding the 'Sussex'", "DTSG_ProshloeDominika_11", 0, 4.0);
			LaunchFrameForm();
			
			n = Findlocation("Location_reserve_06");
			DeleteAttribute(&locations[n], "IslandId");
			DeleteAttribute(&locations[n], "type");
			DeleteAttribute(&locations[n], "models");
			DeleteAttribute(&locations[n], "environment");
			DeleteAttribute(&locations[n], "Box1");
			DeleteAttribute(&locations[n], "Box2");
			DeleteAttribute(&locations[n], "Box3");
			Locations[n].id.label = "Orlop deck";
			Locations[n].filespath.models = "locations\decks\oldeck";
			Locations[n].image = "loading\Boarding_B" + rand(3) + ".tga";
			//Sound
			locations[n].type = "deck_fight";
			//Models
			//Always
			Locations[n].models.always.ODeck = "oldeck";
			Locations[n].models.always.locators = "oldeck_locators";

			//Day
			Locations[n].models.day.charactersPatch = "oldeck_patch";
			Locations[n].models.day.fonar = "oldeck_fday";
			//Night
			Locations[n].models.night.charactersPatch = "oldeck_patch";
			Locations[n].models.night.fonar = "oldeck_fnight";
			//Environment
			Locations[n].environment.sea = "true";
			Locations[n].environment.weather = "true";
		break;
		
		case "DTSG_Graf_Sheffild_1":
			StartQuestMovie(true, false, true);
			dialog.text = "Genug! Ich bin bereit, mein Schwert zu übergeben und Ihre Forderungen zu besprechen. Aber zuerst, stellen Sie sich vor! Wer sind Sie und wie wagen Sie es, uns anzugreifen?! Das ist Verrat!";
			link.l1 = "";
			link.l1.go = "DTSG_Graf_Sheffild_2";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_3":
			dialog.text = "Kapitän Richard Fleetwood. Und Sie müssen Earl Sheffield sein? Und Sie haben absolut recht, das ist Verrat.";
			link.l1 = "";
			link.l1.go = "DTSG_Graf_Sheffild_5";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_5":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_6";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_6":
			dialog.text = "Du weißt, wer ich bin? Verdammt noch mal! Ich wusste, dass so etwas passieren würde, überall Ratten, also habe ich um ein Kriegsschiff gebeten, sogar gefleht...";
			link.l1 = "";
			link.l1.go = "DTSG_Graf_Sheffild_7";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_7":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_8";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_8":
			dialog.text = "Es hätte dich nicht gerettet, nur das Unvermeidliche hinausgezögert, da ich einen anderen Ansatz gefunden hätte. Und ja, mit Verrat meine ich deinen, Earl Sheffield.";
			link.l1 = "";
			link.l1.go = "DTSG_Graf_Sheffild_9";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_9":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_10":
			dialog.text = "Dann wissen Sie nichts über mich, mein Herr! Jeder weiß, dass es keinen loyaleren Mann für England gibt als mich! Sie werden diesen Fehler bereuen, markieren Sie meine Worte.";
			link.l1 = "";
			link.l1.go = "DTSG_Graf_Sheffild_12";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_12":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_13";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_13":
			dialog.text = "Ich habe nichts zu bereuen, denn ich bin nicht derjenige, der zu den Holländern überläuft.";
			link.l1 = "";
			link.l1.go = "DTSG_Graf_Sheffild_15";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_15":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_16":
			dialog.text = "Was?! Was für einen Unsinn plapperst du da?! Du wurdest irregeführt und bist wie ein toller Hund einer falschen Spur gefolgt\nÄhem, es stimmt, ich bin auf dem Weg zu Verhandlungen mit der Niederländischen Westindien-Kompanie. Aber im Interesse unseres Englands, Kapitän. Das ist ein schrecklicher Fehler, aber wir können ihn noch korrigieren.";
			link.l1 = "";
			link.l1.go = "DTSG_Graf_Sheffild_17";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_17":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_18":
			dialog.text = "Ich fürchte, es liegt nicht an mir. Und sicherlich nicht an Ihnen. Sie haben die falsche Seite gewählt, meine Herren. Auf Wiedersehen.";
			link.l1 = "";
			link.l1.go = "DTSG_Graf_Sheffild_19";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;

		case "DTSG_Graf_Sheffild_19":
			DialogExit();
			LAi_SetActorType(pchar);
			sld = CharacterFromID("Fleetwood");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "1", 1.8);
			DoQuestCheckDelay("DTSG_Graf_Sheffild_20", 0.9);
		break;
		
		case "DTSG_Graf_Sheffild_22":
			dialog.text = "Wir sind fertig hier. Ich dachte, dieser dicke Mann würde nie aufhören zu quieken. Oh, diese Grafen, nicht wahr, Charlie?";
			link.l1 = "Ich frage mich nur, Herr, was wäre, wenn der Oberst sich geirrt hätte? Oder, Gott bewahre, uns belogen hätte, um den Grafen loszuwerden?";
			link.l1.go = "DTSG_Graf_Sheffild_23";
		break;
		
		case "DTSG_Graf_Sheffild_23":
			dialog.text = "Hör mir zu, mein Freund. Und hör gut zu. Unser Dienst ist in jeder Hinsicht sehr gefährlich und schwierig. Alles kann passieren - ein trauriger Fehler, ein lächerlicher Zufall oder ein verräterischer Verrat\nIm Dienst des Landes geht es nicht nur darum, Kanonen mit Kanonenkugeln zu laden, Charlie. Für die Machthaber geht es darum, schwierige Entscheidungen zu treffen. Und für Soldaten wie uns - diese Entscheidungen auszuführen.";
			link.l1 = "Aber was ist, wenn wir eines Tages unschuldiges Blut vergießen, Kapitän? Das wird an unseren Händen, unserem Gewissen sein.";
			link.l1.go = "DTSG_Graf_Sheffild_24";
		break;
		
		case "DTSG_Graf_Sheffild_24":
			dialog.text = "Dann wird das Blut genauso sehr an ihren Händen kleben wie an unseren, wenn nicht mehr. Lass das ein Trost für dich sein. Hauptsache, unsere Absichten waren rein - den Feind der Heimat auszuschalten\nHilf mir jetzt, Charlie, wir müssen es immer noch wie einen niederländischen Angriff aussehen lassen.";
			link.l1 = "Ja, Herr...";
			link.l1.go = "DTSG_Graf_Sheffild_25";
		break;
		
		case "DTSG_Graf_Sheffild_25":
			DialogExit();
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Kortni", "off_eng_5", "man", "man", 40, ENGLAND, -1, false, "quest"));
			sld.name = "Thomas";
			sld.lastname = "Lynch";
			sld.rank = 40;
			GiveItem2Character(sld, "blade_16");
			EquipCharacterByItem(sld, "blade_16");
			GiveItem2Character(sld, "pistol6");
			EquipCharacterByItem(sld, "pistol6");
			SetSelfSkill(sld, 100, 100, 100, 100, 100);
			LAi_SetHP(sld, 400.0, 400.0);
			FantomMakeCoolSailor(sld, SHIP_HIMERA, "Сhimera", CANNON_TYPE_CANNON_LBS20, 70, 70, 70);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "StormProfessional");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "Doctor1");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "LongRangeGrappling");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "CriticalShoot");
			SetCharacterPerk(sld, "BasicCommerce");
			SetCharacterPerk(sld, "AdvancedCommerce");
			sld.Ship.Mode = "war";
			sld.alwaysEnemy = true;
			sld.Coastal_Captain = true;
			sld.AlwaysSandbankManeuver = true;
			sld.DontRansackCaptain = true;
			
			Group_FindOrCreateGroup("DTSG_KortniAttack");
			Group_SetType("DTSG_KortniAttack", "pirate");
			Group_AddCharacter("DTSG_KortniAttack", "DTSG_Kortni");

			Group_SetGroupCommander("DTSG_KortniAttack", "DTSG_Kortni");
			Group_SetTaskAttack("DTSG_KortniAttack", PLAYER_GROUP);
			Group_SetAddress("DTSG_KortniAttack", "Antigua", "Quest_Ships", "Quest_Ship_10");
			Group_LockTask("DTSG_KortniAttack");
			
			SetLaunchFrameFormParam("Present time", "DTSG_SegodnyaVremya", 0, 4.0);
			LaunchFrameForm();
		break;
		
		case "DTSG_Knippel_101":
			dialog.text = "Also, wir haben falsche Beweise hinterlassen, um es so aussehen zu lassen, als hätten die Holländer es getan. Richard und ich haben nie wieder über diesen Tag gesprochen.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "Nun, vieles ergibt jetzt Sinn. Ich glaube, ein Verwandter oder Anhänger des Grafen steckt hinter Richards Tod. Aber warum bist du im Visier? Du bist nur ein Kanonier und hast an jenem traurigen Tag keine Entscheidungen getroffen.";
				link.l1.go = "DTSG_Knippel_ZS_102";
				AddComplexLandExpToScill(50, 50, 50);
				Log_info("Experience bonus received");
			}
			else
			{
				link.l1 = "Tatsächlich. Das sind schlechte Geschäfte und sie stinken. Vielleicht hat jemand davon erfahren und beschlossen, sich am Grafen zu rächen. Aber ist ein Kanonier solche Ausgaben wert? Geld, Söldner, die Anstellung von See-Füchsen... Auf keinen Fall, Charlie.";
				link.l1.go = "DTSG_Knippel_NS_102";
			}
		break;
		
		case "DTSG_Knippel_ZS_102":
			dialog.text = "Vielleicht jagt diese Person jeden aus Richards ehemaliger Crew. Was denken Sie, Herr?";
			link.l1 = "Ich denke, wir sollten uns von Antigua distanzieren, und je eher, desto besser.";
			link.l1.go = "DTSG_Knippel_103";
		break;
		
		case "DTSG_Knippel_NS_102":
			dialog.text = "Ich habe mir diese Frage auch gestellt, Kapitän, aber ich habe keine Antwort gefunden.";
			link.l1 = "Verdammt. Jemand kommt. Ich bat darum, nicht gestört zu werden!";
			link.l1.go = "DTSG_Knippel_103";
		break;
		
		case "DTSG_Knippel_103":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				sld = characterFromId("Helena");
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
				sld.dialog.currentnode = "DTSG_Helena_1";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", 0, 0);
				break;
			}
			if (GetCharacterIndex("Tichingitu") != -1 && CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				sld = characterFromId("Tichingitu");
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
				sld.dialog.currentnode = "DTSG_Tichingitu_1";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", 0, 0);
				break;
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("Alonso", "Alonso", "man", "man", sti(pchar.rank), pchar.nation, 0, true, "soldier"));
				sld.name 	= "Alonso";
				sld.lastname = "";
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
				sld.dialog.currentnode = "DTSG_Alonso_1";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", 0, 0);
				sld.location = "None";
			}
		break;
		
		case "DTSG_Helena_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Charles!..";
				link.l1 = "Was ist los, Helen??";
				link.l1.go = "DTSG_Helena_2";
			}
			else
			{
				dialog.text = "Charles, ich erinnere mich, dass du mich gebeten hast, niemanden hereinzulassen und dich und Charlie nicht zu stören, aber...";
				link.l1 = "... du hast dich entschieden, selbst zu kommen. Gut, es ist in Ordnung, Helen.";
				link.l1.go = "DTSG_Helena_2";
			}
		break;
		
		case "DTSG_Helena_2":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Ein englisches Kriegsschiff! Es wurde vor einiger Zeit gesichtet. Zuerst habe ich nicht darauf geachtet, aber es wird uns jeden Moment erreichen! Ich habe noch nie ein so schnelles Schiff gesehen.";
				link.l1 = "Dann danke, dass du es mir gesagt hast. Ich hoffe, wir haben Zeit uns vorzubereiten, bevor sie uns erreicht. Helen, Charlie, Gefechtsstationen!";
				link.l1.go = "DTSG_GotovimsyKBitve";
			}
			else
			{
				dialog.text = "... ihr könnt euer geheimes Treffen später fortsetzen. Ein englisches Kriegsschiff nähert sich uns. Ich dachte, es wäre wichtig.";
				link.l1 = "Nun, ich werde mal nachsehen. Danke, Helen.";
				link.l1.go = "DTSG_GotovimsyKBitve";
			}
		break;
		
		case "DTSG_Tichingitu_1":
			dialog.text = "Kapitän, ein schnelles Schiff kommt auf uns zu. Sehr schnell. Die Geister flüstern mir zu, dass ihre Absichten böse sind.";
			link.l1 = "Danke dir und den Geistern für die Warnung. Bereite dich sicherheitshalber auf die Schlacht vor. Und übermittle diese Nachricht von mir an die anderen.";
			link.l1.go = "DTSG_GotovimsyKBitve";
		break;
		
		case "DTSG_Alonso_1":
			dialog.text = "Entschuldigen Sie die Störung, Kapitän, aber es ist dringend.";
			link.l1 = "Oh, ich hoffe, es ist wirklich wichtig, Alonso. Bericht.";
			link.l1.go = "DTSG_Alonso_2";
		break;
		
		case "DTSG_Alonso_2":
			dialog.text = "Ein englisches Schiff nähert sich. Es ist... die 'Mirage', Kapitän.";
			link.l1 = "Was? Bist du dir absolut sicher? Wieder getrunken, was?";
			link.l1.go = "DTSG_Alonso_3";
		break;
		
		case "DTSG_Alonso_3":
			dialog.text = "Ich bin sicher, Kapitän - es gibt kein anderes Schiff wie dieses in der Karibik, das wissen Sie.";
			link.l1 = "Tatsächlich. Ich werde selbst einen Blick darauf werfen - mal sehen, ob dieses 'Mirage' echt ist.";
			link.l1.go = "DTSG_GotovimsyKBitve";
		break;
		
		case "DTSG_GotovimsyKBitve":
			DialogExit();
			AddQuestRecord("DTSG", "17");
			
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				sld = characterFromId("Helena");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Saga\Helena.c";
				sld.Dialog.CurrentNode = "Helena_officer";
			}
			if (GetCharacterIndex("Tichingitu") != -1 && CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				sld = characterFromId("Tichingitu");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.Dialog.CurrentNode = "Tichingitu_officer";
			}
			if (GetCharacterIndex("Knippel") != -1 && CheckPassengerInCharacter(pchar, "Knippel"))
			{
				sld = characterFromId("Knippel");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
				sld.Dialog.CurrentNode = "Knippel_officer";
			}
			
			PChar.quest.DTSG_KortniPotopil.win_condition.l1 = "Character_sink";
			PChar.quest.DTSG_KortniPotopil.win_condition.l1.character = "DTSG_Kortni";
			PChar.quest.DTSG_KortniPotopil.win_condition = "DTSG_KortniPotopil";
			
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
		break;
		
		case "DTSG_Kortni":
			dialog.text = "Oh... Aber es ist noch nicht vorbei! Brian, da bist du ja! Wo zur Hölle warst du?";
			link.l1 = "Das wird das Unvermeidliche nur verzögern.";
			link.l1.go = "DTSG_Kortni_Pikar";
		break;
		
		case "DTSG_Kortni_Pikar":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			LAi_SetWarriorType(npchar);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetCheckMinHP(npchar, 10, true, "DTSG_KortniRanen");
			LAi_SetImmortal(npchar, false);
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Mrt_Rocur", "citiz_8", "man", "man", sti(pchar.rank), ENGLAND, -1, false, "soldier"));
			sld.name = "Brian";
			sld.lastname = "Tasse";
			GiveItem2Character(sld, "blade_20");
			EquipCharacterByItem(sld, "blade_20");
			GiveItem2Character(sld, "pistol5");
			EquipCharacterByItem(sld, "pistol5");
			AddItems(sld, "purse2", 1);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetHP(sld, 300.0, 300.0);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 10, true, "DTSG_PikarRanen");
			sld.location = "None";
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "DTSG_Kortni_1":
			dialog.text = "Charles de Maure. Zu denken, wie weit du gekommen bist. Schade. Ich hoffte, dich auf diesem Schiff unvorbereitet zu erwischen.";
			link.l1 = "Sie wissen, wer ich bin? Also, Sie stecken hinter unseren jüngsten Schwierigkeiten - Sie sehen aus wie ein hochfliegender Vogel, der gezwungen ist, sein gemütliches Nest zu verlassen und persönlich herauszukommen, anstatt einen anderen Geier zu schicken.";
			link.l1.go = "DTSG_Kortni_2";
			
			Island_SetReloadEnableGlobal("Antigua", true);
			bQuestDisableMapEnter = false;
			LAi_LocationDisableOfficersGen("SentJons_town", false);
			DeleteQuestCondition("DTSG_KortniPotopil");
		break;
		
		case "DTSG_Kortni_2":
			dialog.text = "Richtig, in beiden Punkten. Ich nehme an, ein Adliger kann einen anderen aus der Ferne erkennen. Oberst Thomas Lynch. Es scheint, es ist Zeit, wie Herren zu sprechen, anstatt zu versuchen, sich gegenseitig zu zerstören. Vielleicht können wir eine für beide Seiten vorteilhafte Vereinbarung treffen.";
			link.l1 = "Ich kann nichts versprechen, aber ich gebe Ihnen mein Wort als Edelmann, dass wir zumindest wie zivilisierte Menschen sprechen werden, Oberst.";
			link.l1.go = "DTSG_Kortni_3";
		break;
		
		case "DTSG_Kortni_3":
			dialog.text = "Sehr gut. Mit Fleetwood hätte ich so ein Gespräch nicht führen können. Dennoch haben wir einen Hebel an ihm gefunden, und er wird uns nicht mehr belästigen. Schade, dass es mit dir nicht geklappt hat, aber macht nichts.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "Die ganze Karibik spricht über Richards Tod. Also, du warst es! Und ich nehme an, der Hebel, den du erwähnt hast, war Abigail? Was ist übrigens mit ihr passiert?";
				AddComplexLandExpToScill(50, 50, 50);
				Log_info("Experience bonus received");
			}
			else
			{
				link.l1 = "Nicht eine Bedrohung, sagst du?.. Also, hast du ihn getötet? Bist du ein Anhänger des Grafen?";
			}
			link.l1.go = "DTSG_Kortni_4";
		break;
		
		case "DTSG_Kortni_4":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "Abigail? Ah, die junge Jüdin, seine Verlobte. Wieder einmal hast du dich als sehr aufmerksame Person erwiesen. Sie lebt und ist wohlauf - das haben wir versprochen und eingehalten im Austausch für Fleetwoods Zusammenarbeit.";
				link.l1 = "Ganz die Zusammenarbeit, muss ich sagen. Aber warum hast du es getan? Unterstützt du den Earl?";
			}
			else
			{
				dialog.text = "Unterstützer? Oh, ganz im Gegenteil. Aber Sie sehen, einige Karten können nicht mehr gespielt werden, da sie zur Last für den Spieler werden. Leider wurde Richard zu einer von ihnen.";
				link.l1 = "Ich verstehe. Du beseitigst alle Zeugen. Was ist mit Abigail passiert? Hast du sie auch getötet?";
			}
			link.l1.go = "DTSG_Kortni_5";
		break;
		
		case "DTSG_Kortni_5":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "Überhaupt nicht. Ganz im Gegenteil. Aber Richard wusste zu viel, und indem er in die alte Welt zurückkehrte, wurde er gefährlich. Er hätte hier bleiben sollen, und wir hätten ihm das Leben nicht genommen.";
				link.l1 = "Eliminieren Sie jeden, der jemals für Sie gearbeitet hat, Oberst?";
			}
			else
			{
				dialog.text = "Wer? Ah, seine Verlobte, nehme ich an. Sie war der Hebel. Sein Leben für ihres. Sie ist in Ordnung, ich schwöre auf meine Ehre.";
				link.l1 = "Ich bezweifle, dass Sie wissen, was Ehre ist, wenn man bedenkt, was Sie getan haben, Oberst.";
			}
			link.l1.go = "DTSG_Kortni_6";
		break;
		
		case "DTSG_Kortni_6":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "Ich werde auf diese Provokation nicht antworten, Herr.";
				link.l1 = "Dann beantworte mir das - wie hast du dieses Schiff bekommen? Ist es... die 'Mirage'?";
			}
			else
			{
				dialog.text = "Ich werde diese Beleidigung übersehen, weil sie von jemandem kommt, der noch nie Macht ausüben und die Ordnung der Dinge beeinflussen musste.";
				link.l1 = "Apropos Dinge, wo haben Sie die 'Mirage' bekommen? Ist sie das?";
			}
			link.l1.go = "DTSG_Kortni_7";
		break;
		
		case "DTSG_Kortni_7":
			dialog.text = "Nicht genau. Ein prächtiges Schiff, nicht wahr? Schade, dass es seinen Zweck gegen Sie nicht erfüllt hat. Kennen Sie die Geschichte dieses Schiffes, Kapitän de Maure?";
			link.l1 = "Du meinst das Geisterschiff und die Jagd auf englische Kaufleute?";
			link.l1.go = "DTSG_Kortni_8";
		break;
		
		case "DTSG_Kortni_8":
			dialog.text = "Das? Oh, nein. Ich spreche nicht von bekannten Dingen. Ich meine Dinge, die vor dem Blick verborgen sind. Diese Ketsch wurde von Johan van Merden und Lucas Rodenburg entworfen\nDieses süße Paar erstellte eine Kette von Plänen, und das Schiff wurde schließlich von der Werft in Havanna gestartet. Wir hatten das Glück, die originalen Baupläne in die Hände zu bekommen. Und am Ende haben wir die Mirage in all ihrer Pracht nachgebildet und sogar verbessert, indem wir einige Mängel in ihrem Design korrigiert haben.";
			link.l1 = "Schade, wie Sie selbst bemerkt haben, hat es Ihnen nicht viel geholfen, Oberst.";
			link.l1.go = "DTSG_Kortni_9";
		break;
		
		case "DTSG_Kortni_9":
			dialog.text = "Bist du in Lachstimmung? Sei es nicht. Ich gebe zu, du hast mich sowohl als Kapitän als auch als Kämpfer übertroffen. Aber hier habe ich immer noch die Oberhand.";
			link.l1 = "Ist das ein sterbender Bluff? Oder nur die übliche Überheblichkeit von Leuten wie dir? Was verbirgt sich hinter diesen Worten?";
			link.l1.go = "DTSG_Kortni_10";
		break;
		
		case "DTSG_Kortni_10":
			dialog.text = "Ausgezeichnete Frage. Es scheint mir, du bist mehr als ein hurender Lebemann und Duellant, wie meine Recherchen vermuten ließen. Ich habe Vorkehrungen für alle Ausgänge dieses Treffens getroffen. Sogar für den, in dem ich durch deine Klinge, Kugel oder einen verirrten Kanonenball sterbe. Wenn ich heute sterbe, werdet ihr beide, du und Charlie, es bedauern, nicht zu Fleetwood übergelaufen zu sein.";
			link.l1 = "Noch mehr Kopfgeldjäger? Bitte. Es war unangenehm und mühsam, aber nicht tödlich. Wir haben sie damals abgewehrt - wir werden sie wieder abwehren.";
			link.l1.go = "DTSG_Kortni_11";
		break;
		
		case "DTSG_Kortni_11":
			dialog.text = "Ich habe keinen Zweifel. Jetzt sehe ich wieder den sorglosen Duellanten sprechen. Nicht nur Kopfgeldjäger. Die volle Kraft der Seefüchse und des englischen Marinegeheimdiensts wird wie eine Sturmflut auf das Boot eines Fischers auf deinen Kopf prallen.";
			link.l1 = "Was willst du von mir? Du erwartest doch nicht etwa, dass ich mich ergebe?";
			link.l1.go = "DTSG_Kortni_12";
		break;
		
		case "DTSG_Kortni_12":
			dialog.text = "Natürlich nicht. Wir haben Sie all diese Zeit gut studiert. Ich möchte Ihnen ein für beide Seiten vorteilhaftes Angebot unterbreiten. Ein Angebot, das es unklug wäre abzulehnen. Und als zwei Edelleute hoffe ich, dass wir zu einer Einigung kommen können.";
			link.l1 = "Dann wiederhole ich die Frage, Oberst, was wollen Sie? Ich nehme an, Charlie?.. Und Sie denken, Sie können mir etwas als Gegenleistung anbieten? Ich werde nicht für ein paar Goldmünzen verraten.";
			link.l1.go = "DTSG_Kortni_13";
		break;
		
		case "DTSG_Kortni_13":
			dialog.text = "Richtig wieder. Es geht nicht nur um ein paar Goldmünzen, wie du es ausdrückst, sondern um einen ganzen Berg - 10.000 Dublonen. Die Einzahlung wird auf dich bei dem Bankier in Port Royal warten, wenn wir uns einigen\nAber das wichtigste, was ich biete, ist dein Leben, Kapitän de Maure. Du hast mich gehört. Wir werden alle Verfolgung einstellen, wenn wir jetzt alle unsere Waffen niederlegen und du Charlie uns übergibst\nHast du den Ausdruck 'Mensch gegen Gesellschaft' gehört? In deinem Fall, wenn du dich weigerst, wird es 'Mensch gegen den Staat'. Entscheide, Charles. Hier und jetzt.";
			link.l1 = "Sie können leicht Ihren Titel und Einfluss nutzen, um einen Narren oder zwei einzuschüchtern. Aber ich bin kein Narr. Und ich rieche Verzweiflung meilenweit. Hau ab. Und sei froh, dass ich dich nicht getötet habe - du hast es mehr als verdient.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
			link.l2 = "Sie brauchen Charlie nicht wirklich, Oberst. Sie brauchen seine Stille.";
			link.l2.go = "DTSG_Kortni_LT_1";
			link.l3 = "Ich stimme dem zu für die Sicherheit von mir und meinen Männern, nicht aus Gier nach deinem Geld, nur damit du das weißt.";
			link.l3.go = "DTSG_Kortni_Sdat";
		break;
		
		case "DTSG_Kortni_PkCh_1":
			dialog.text = "Sie haben eine der schlimmsten Entscheidungen Ihres Lebens getroffen, Kapitän de Maure. Ich beneide Sie nicht. Wirklich. Sie werden sich selbst die Schuld geben - niemand wird Ihnen wieder ähnliche Angebote machen. Vor allem nicht ich. Auf Wiedersehen.";
			link.l1 = "Warte, Oberst.";
			link.l1.go = "DTSG_Kortni_PkCh_2";
		break;
		
		case "DTSG_Kortni_PkCh_2":
			dialog.text = "Was, hast du deine Meinung geändert? Haben meine Worte endlich Wirkung gezeigt?";
			link.l1 = "Richtig, genau das Gegenteil.";
			link.l1.go = "DTSG_Kortni_PkCh_3";
		break;
		
		case "DTSG_Kortni_PkCh_3":
			dialog.text = "Was meinst du? Erkläre dich.";
			link.l1 = "Deine Worte haben nur meinen Entschluss gegen dich gestärkt. Schau nicht so - ich werde dich nicht töten. Und wie ich schon sagte, ich werde dich sogar gehen lassen. Aber ich denke, du wirst ohne ein Boot auskommen.";
			link.l1.go = "DTSG_Kortni_PkCh_4";
		break;
		
		case "DTSG_Kortni_PkCh_4":
			dialog.text = "Ich brauche es nicht, denn ich habe ein Schiff.";
			link.l1 = "Du hast recht. Aber nur darüber, dass du es nicht brauchst. Du magst ein einflussreicher Mann sein. Aber dir fehlt ein Gespür für Maß. Und Takt. Ich werde tun, was du gewohnt bist zu tun - der Herr der Lage sein.";
			link.l1.go = "DTSG_Kortni_PkCh_5";
		break;
		
		case "DTSG_Kortni_PkCh_5":
			dialog.text = "Sie sind es nicht, Kapitän de Maure. Täuschen Sie sich nicht selbst.";
			link.l1 = "Vollständig? Vielleicht nicht. Aber du auch nicht - dein Leben liegt jetzt in meinen Händen, Oberst. Es ist egal, was später mit mir passiert - jetzt kann ich tun, was ich will. Und ich... nehme dieses Schiff. Du bist frei. Das Ufer ist nicht weit.";
			link.l1.go = "DTSG_Kortni_PkCh_6";
		break;
		
		case "DTSG_Kortni_PkCh_6":
			dialog.text = "Du würdest es nicht wagen. Aber nach deinem Aussehen zu urteilen... Genieße deinen kleinen Sieg. Du hast...";
			link.l1 = "Ja, ja, eine der schlimmsten Entscheidungen meines Lebens. Ich habe es schon gehört. Von diesem Schiff. Meinem Schiff. Wirst du selbst springen, oder sollen wir dich über Bord werfen?";
			link.l1.go = "DTSG_Kortni_PkCh_7";
		break;
		
		case "DTSG_Kortni_PkCh_7":
			DialogExit();
			
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto4", "", "", "", "DTSG_Kortni_Vyprygnul", 7);
			npchar.lifeday = 0;
			npchar.location = "None";
		break;
		
		case "DTSG_Kortni_PkCh_8":
			dialog.text = "Ich hätte nie gedacht, dass ich ihn so sehen würde - gedemütigt, aus dem Fenster springend und auf allen vieren zum Ufer schwimmend.";
			link.l1 = "Hast du einen Blick erhascht? Zufrieden? Wunderbar. Du bist der Nächste.";
			link.l1.go = "DTSG_Kortni_PkCh_9";
		break;
		
		case "DTSG_Kortni_PkCh_9":
			dialog.text = "What are you saying, sir? We're not enemies; I was just following orders!.. Can I at least ask for a boat? You'll never see me again!";
			link.l1 = "Sie würden mir nicht verschonen, wenn ich in Ihrer Situation wäre und gerade eine Schlacht gegen Sie verloren hätte. Seien Sie also froh, dass ich Sie nicht getötet habe. Raus aus dem Fenster. Jetzt. Vielleicht holen Sie Ihren Patron ein.";
			link.l1.go = "DTSG_Kortni_PkCh_10";
		break;
		
		case "DTSG_Kortni_PkCh_10":
			dialog.text = "Ich würde lieber sterben als solche Demütigung zu ertragen, Monsieur!";
			link.l1 = "Wie du wünschst.";
			link.l1.go = "DTSG_Kortni_PkCh_11";
		break;
		
		case "DTSG_Kortni_PkCh_11":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			LAi_RemoveCheckMinHP(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Kortni_Vyprygnul_3");
		break;
		
		case "DTSG_Kortni_PkCh_12":
			dialog.text = "Das war der Oberst, nicht wahr, Kapitän?";
			link.l1 = "Richtig. Schau aus dem Fenster, Charlie, du wirst es nicht bereuen.";
			link.l1.go = "DTSG_Kortni_PkCh_13";
		break;
		
		case "DTSG_Kortni_PkCh_13":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto4", "DTSG_Kortni_Vyprygnul_5", 6);
		break;
		
		case "DTSG_Kortni_PkCh_14":
			dialog.text = "Der Oberst?.. Ich hätte nie gedacht, dass ich so etwas sehen würde, Herr. Dass jemand es wagen würde, einen Mann mit einem solchen Titel wie einen gewöhnlichen Matrosen über Bord zu werfen! Richard würde das nie tun - der Respekt vor Rängen war ein grundlegender Teil von ihm.";
			link.l1 = "Es wurde ihm im Laufe der Jahre durch Übungen eingebläut. Er ist ein Militärmann, mit der entsprechenden Denkweise. Ich bin es nicht, und ich denke breiter, ohne solche... Einschränkungen.";
			link.l1.go = "DTSG_Kortni_PkCh_15";
		break;
		
		case "DTSG_Kortni_PkCh_15":
			dialog.text = "Und wir geraten nicht in Schwierigkeiten, weil wir ihm das antun?";
			link.l1 = "Heh, du gibst Richard die Schuld, denkst aber wie er. Wir haben es gewagt, uns zu widersetzen, also werden wir eine Weile gejagt werden. Aber früher oder später wird selbst die englische Marine uns aufgeben. Und für Lynch wird es eine persönliche Angelegenheit. Aber wir haben dafür gesorgt, dass er das nächste Mal keine staatlichen Ressourcen hinter sich hat.";
			link.l1.go = "DTSG_Kortni_PkCh_16";
		break;
		
		case "DTSG_Kortni_PkCh_16":
			dialog.text = "Weißt du, Kapitän, ab diesem Tag respektiere ich dich noch mehr. Ich werde es nie bereuen, nicht mit Dick auf der Walküre abgereist und stattdessen entschieden zu haben, mich dir anzuschließen.";
			link.l1 = "Danke dir, mein Freund! Mach dich bereit - der Sturm zieht auf. Aber weißt du was? Etwas sagt mir, dass wir wieder siegreich hervorgehen werden. Los geht's, es ist Zeit, zurück zum Deck zu gehen.";
			link.l1.go = "DTSG_Kortni_PkCh_17";
		break;
		
		case "DTSG_Kortni_PkCh_17":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			DoQuestCheckDelay("DTSG_Kortni_Vyprygnul_7", 3.0);
			Achievment_Set("ach_CL_114");
		break;
		
		case "DTSG_Kortni_LT_1":
			dialog.text = "Das ist nicht ganz wahr, obwohl ich persönlich mich nicht um Charlie kümmere, wenn er ab jetzt seinen Mund hält. Aber meine Kollegen würden gerne seinen Körper sehen. Und sie wissen, wie er aussieht\nDas ist das echte Leben, Charles, kein Kindermärchen oder ein ritterliches Gedicht, das uns in der Kindheit von Nannys vorgelesen wurde, und ich sehe keine Lösung, die allen gefällt.";
			link.l1 = "Aber ich mache das. Man kann immer einen ähnlichen Körper finden. Und ähnliche Kleidung kaufen. Schmiere einige Räder. Und ich werde mit Charlie sprechen. Und ich gebe dir mein Wort als Garantie.";
			link.l1.go = "DTSG_Kortni_LT_2";
		break;
		
		case "DTSG_Kortni_LT_2":
			if (sti(pchar.reputation.nobility) > 70)
			{
				notification("Reputation Check Passed", "None");
				dialog.text = "Es ist... ein großes Risiko. Und es geht nicht nur darum, ob ich deinem Wort vertrauen kann. Sondern ob meine Kollegen mir glauben werden, wenn sie einen Körper sehen, der Charlie ähnelt. Und ich werde dieses Risiko nicht eingehen... einfach so.";
				link.l1 = "Wie viel?";
				link.l1.go = "DTSG_Kortni_LT_4";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(71))+")", "None");
				dialog.text = "Das Wort eines Mannes mit Ihrem Ruf? Du machst Witze. Adliger Geburt allein reicht nicht für Vertrauen.";
				link.l1 = "Hören Sie das von einem anderen Mann mit ähnlicher Geburt und Tat, verzeihen Sie mir, Oberst.";
				link.l1.go = "DTSG_Kortni_LT_3";
			}
		break;
		
		case "DTSG_Kortni_LT_3":
			dialog.text = "Natürlich hast du Recht. Aber in diesem Fall geht es um mein Vertrauen, nicht um das von jemand anderem. Und du als Bürge passt mir nicht\nIch sage es dir ein letztes Mal. Gib mir Charlie. Wenn du natürlich nicht das Schicksal von Fleetwood teilen willst.";
			link.l1 = "Sie können leicht Ihren Titel und Einfluss nutzen, um einen Narren oder zwei einzuschüchtern. Aber ich bin kein Narr. Und ich spüre Verzweiflung meilenweit entfernt. Geh weg. Und sei froh, dass ich dich nicht getötet habe - du hast es mehr als verdient.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
		break;
		
		case "DTSG_Kortni_LT_4":
			dialog.text = "Endlich, direkt zur Sache. Eine Million Pesos. Letztes Angebot.";
			if (sti(pchar.Money) >= 1000000)
			{
				link.l1 = "Ich werde dir das Geld geben. Denk nicht, dass ich arm bin oder das Leben meiner Männer nicht schätze. Beides ist nicht wahr. Nimm es.";
				link.l1.go = "DTSG_Kortni_LT_7";
			}
			else
			{
				link.l1 = " Du hast einen guten Appetit, obwohl ich nichts anderes erwartet habe. Aber im Moment habe ich nicht so viel, und...";
				link.l1.go = "DTSG_Kortni_LT_5";
			}
		break;
		
		case "DTSG_Kortni_LT_5":
			dialog.text = "Kein Silber - kein Handel. Dachten Sie, ich würde Gnade zeigen? Sehe ich aus wie ein Heiliger, Herr?";
			link.l1 = "Aber könnten Sie vielleicht noch ein bisschen warten? Wo und wann wäre es für Sie günstig, sich wieder zu treffen? Ich könnte die Dublonen von einem Geldverleiher leihen.";
			link.l1.go = "DTSG_Kortni_LT_6";
		break;
		
		case "DTSG_Kortni_LT_6":
			dialog.text = "Dann denkst du, ich bin noch naiver als ich dachte\nIch bin kein Landmädchen, bereit, ewig auf jemanden zu warten, der einmal seinen Weg mit ihr hatte\nKein Geld? Ich habe sowieso nicht danach gefragt. Ich will nur Charlie. Trotz all der Probleme, die du verursacht hast, bist du für mich nutzlos.";
			link.l1 = "Sie können leicht Ihren Titel und Einfluss nutzen, um einen Narren oder zwei einzuschüchtern. Aber ich bin kein Narr. Und ich spüre Verzweiflung aus einer Meile Entfernung. Raus. Und seien Sie froh, dass ich Sie nicht getötet habe - Sie hätten es mehr als verdient.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
		break;
		
		case "DTSG_Kortni_LT_7":
			dialog.text = "Sind Sie wirklich so sehr an den armen Charlie gebunden? Auf jeden Fall verdient Ihre Noblesse Respekt. Stellen Sie sicher, dass Ihr Kanonier so still ist wie das Grab. Sonst landen Sie beide dort.";
			link.l1 = "Ich verspreche es. Und du hältst dein Wort und stellst alle Verfolgung ein.";
			link.l1.go = "DTSG_Kortni_LT_8";
			AddMoneyToCharacter(pchar, -1000000);
		break;
		
		case "DTSG_Kortni_LT_8":
			dialog.text = "Ich verspreche es auch. Und noch etwas. Trotz deines ehrlichen Sieges, nehme ich mein Schiff mit. Es ist ein Maßanfertigung, weißt du. Und sehr teuer.";
			link.l1 = "Was ist mit dem Recht des Siegers? Aber ich werde mein Glück nicht herausfordern. Dieses Mal.";
			link.l1.go = "DTSG_Kortni_LT_9";
		break;
		
		case "DTSG_Kortni_LT_9":
			DialogExit();
			
			LAi_Fade("DTSG_Kortni_Otkup_1", "");
		break;
		
		case "DTSG_Kortni_LT_10":
			dialog.text = "Es tut mir fast leid, das zu sagen, Brian, aber ich fürchte, unsere Zusammenarbeit endet hier.";
			link.l1 = "";
			link.l1.go = "DTSG_Kortni_LT_11";
			CharacterTurnToLoc(npchar, "rld", "aloc0");
		break;
		case "DTSG_Kortni_LT_11":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_12";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_12":
			dialog.text = "Ich... bin frei, Oberst? Werden Sie das Kopfgeld auf mich aufheben, und ich kann von vorne anfangen, als ob ich ein gesetzestreuer Mann wäre?";
			link.l1 = "";
			link.l1.go = "DTSG_Kortni_LT_13";
			CharacterTurnToLoc(npchar, "rld", "loc0");
		break;
		case "DTSG_Kortni_LT_13":
			DialogExit();
			sld = CharacterFromID("DTSG_KortniClone");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_14":
			dialog.text = "Ich würde sagen, du hast zu viel gesehen - genau wie der verstorbene Fleetwood. Ich habe im Grunde genommen gerade vor deinen Augen eine Bestechung erhalten.";
			link.l1 = "";
			link.l1.go = "DTSG_Kortni_LT_15";
			CharacterTurnToLoc(npchar, "rld", "aloc0");
		break;
		case "DTSG_Kortni_LT_15":
			DialogExit();
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_16":
			dialog.text = "Ich... Ich werde niemandem etwas sagen, ich schwöre bei Gott!";
			link.l1 = "";
			link.l1.go = "DTSG_Kortni_LT_17";
			CharacterTurnToLoc(npchar, "rld", "loc0");
		break;
		case "DTSG_Kortni_LT_17":
			DialogExit();
			sld = CharacterFromID("DTSG_KortniClone");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_18":
			dialog.text = "Natürlich wirst du nicht.";
			link.l1 = "";
			link.l1.go = "DTSG_Kortni_LT_19";
			CharacterTurnToLoc(npchar, "rld", "aloc0");
		break;
		case "DTSG_Kortni_LT_19":
			DialogExit();
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_20":
			dialog.text = "Nein!..";
			link.l1 = "";
			link.l1.go = "DTSG_Kortni_LT_21";
			CharacterTurnToLoc(npchar, "rld", "loc0");
		break;
		case "DTSG_Kortni_LT_21":
			DialogExit();
			
			sld = CharacterFromID("DTSG_KortniClone");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "1", 1.8);
			DoQuestCheckDelay("DTSG_Kortni_Otkup_3", 0.9);
			
			LAi_SetActorType(NPChar);
			LAi_ActorAttack(NPChar, sld, "");
		break;
		
		case "DTSG_Kortni_LT_22":
			dialog.text = "Schau mich nicht so an, Charles. Wenn ich ständig darüber nachdenken muss, ob Brian das Geheimnis ausplaudern wird, kann ich überhaupt nicht schlafen.";
			link.l1 = "Ich weiß nicht einmal, ob ich über das, was ich gesehen habe, überrascht sein sollte oder nicht.";
			link.l1.go = "DTSG_Kortni_LT_23";
		break;
		
		case "DTSG_Kortni_LT_23":
			dialog.text = "Du solltest nicht. Ich bin engagiert. Alles, was ich von euch beiden verlange, ist, den Mund über das, was passiert ist, zu halten. Ich werde versuchen, einen ähnlichen Körper zu finden, sein Gesicht ordentlich zu richten, das Geld gut zu verwenden und meine Kollegen zu überzeugen.";
			link.l1 = "Danke, Oberst.";
			link.l1.go = "DTSG_Kortni_LT_24";
		break;
		
		case "DTSG_Kortni_LT_24":
			dialog.text = "Es gibt noch nichts, wofür du mir danken könntest. Es besteht immer das Risiko, dass sie mir nicht glauben, und dann wird die Jagd wieder eröffnet. Für jetzt, auf Wiedersehen, Kapitän de Maure. Ich segel auf meinem Schiff davon. Keine Einwände hier - Ich habe dir und Charlie bereits einen großen Gefallen getan.";
			link.l1 = "Nun, dann leb wohl.";
			link.l1.go = "DTSG_Kortni_LT_25";
			
			pchar.GenQuest.CannotTakeShip = true;
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition.l1 = "MapEnter";
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition = "DTSG_Kortni_KechNeNash";
		break;
		
		case "DTSG_Kortni_LT_25":
			DialogExit();
			
			//sld = CharacterFromID("Knippel");
			sld = GetCharacter(CreateCharacterClone(CharacterFromID("Knippel"), 0));
			sld.id = "KnippelClone";
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_26";
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
		break;
		
		case "DTSG_Kortni_LT_26":
			dialog.text = "Wissen Sie überhaupt, mit wem Sie gesprochen haben, Kapitän? Ein Oberst! War er es, der dieses ganze Durcheinander orchestriert hat?";
			link.l1 = "Ich weiß, er hat sich vorgestellt. Und du hast recht - er war es.";
			link.l1.go = "DTSG_Kortni_LT_27";
		break;
		
		case "DTSG_Kortni_LT_27":
			dialog.text = "Es ist seltsam, Herr, denn ich kannte ihn einst als Richards Vorgesetzten. Wie ist das möglich? Und warum geht er, als wäre nichts passiert? Was wollte er überhaupt?";
			link.l1 = "Eigentlich ist daran nichts Seltsames. Diejenigen, die zwielichtige Befehle ausführen, riskieren ihr Leben oft nicht so sehr wegen der Feinde, sondern wegen ihrer Vorgesetzten. Und er wollte deinen Kopf, Charlie.";
			link.l1.go = "DTSG_Kortni_LT_28";
		break;
		
		case "DTSG_Kortni_LT_28":
			dialog.text = "Ich verstehe nicht, Kapitän. Warum geht er dann? Hat er die Niederlage akzeptiert?";
			link.l1 = "Das ist überhaupt nicht seine Art. Ich musste ihm Gold geben, ungefähr so schwer wie dein Kopf. Vielleicht ein bisschen mehr als das. Genau gesagt eine Million Pesos.";
			link.l1.go = "DTSG_Kortni_LT_29";
		break;
		
		case "DTSG_Kortni_LT_29":
			dialog.text = "Und du... hast ihm diesen riesigen Betrag bezahlt? Für mich?..";
			link.l1 = "Nun, nicht nur für dich. Auch für mich. Und für all die Jungs, auch. Aber ja, Charlie, hauptsächlich für dich. Wenn wir ihn getötet hätten, hätten wir uns auf ewig mit Strafexpeditionen konfrontiert gesehen.";
			link.l1.go = "DTSG_Kortni_LT_30";
		break;
		
		case "DTSG_Kortni_LT_30":
			dialog.text = "Ich... kann es nicht glauben, Herr. Einfach... danke. Ich dachte nicht, dass Fleetwood das an Ihrer Stelle tun würde.";
			link.l1 = "Du bist zu voreingenommen gegen ihn nach seiner Flucht. Richard wollte nur ein ruhiges und friedliches Leben mit Abigail. Es tut mir leid, dass es für ihn nicht geklappt hat. Außerdem hat er sein Wort gehalten und deine Schulden bezahlt. Heh, ich, Fleetwood - du hast wirklich Glück mit Kapitänen, was, Charlie?";
			link.l1.go = "DTSG_Kortni_LT_31";
		break;
		
		case "DTSG_Kortni_LT_31":
			dialog.text = "Kein Scherz, Kapitän. Also, ist jetzt alles vorbei?";
			link.l1 = "Ja, mein sehr teurer Freund. Zumindest für jetzt. Der Kampf ist vorbei - du kannst den Jungs sagen, sie sollen ihre Waffen verstauen. Und lass sie sich darauf vorbereiten, die Segel zu hissen.";
			link.l1.go = "DTSG_Kortni_LT_32";
		break;
		
		case "DTSG_Kortni_LT_32":
			DialogExit();
			
			InterfaceStates.Buttons.Save.enable = true;
			LAi_SetPlayerType(pchar);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			
			AddQuestRecord("DTSG", "19");
			CloseQuestHeader("DTSG");
			LAi_ReloadBoarding();
			Achievment_Set("ach_CL_114");
			sld = CharacterFromID("Knippel");
			SetCharacterPerk(sld, "Bombardier");
			notification("Bombardier Unlocked", "Knippel");
		break;
		
		case "DTSG_Kortni_Sdat":
			dialog.text = "Es ist mir völlig egal, warum du zustimmst - ob aus Gier, Angst oder Pflichtgefühl gegenüber deinen Männern. Hauptsache, du stimmst zu. Ich schicke meinen Mann mit Anweisungen für den Bankier nach Port Royal.";
			link.l1 = "Gut. Ich kann kaum glauben, dass dies endlich vorbei ist.";
			link.l1.go = "DTSG_Kortni_Dengi_1";
			link.l2 = "Weißt du was, zur Hölle mit dem Geld. Man kann immer mehr finden. Es gibt etwas anderes, was ich von dir im Austausch für Charlie möchte, Oberst.";
			link.l2.go = "DTSG_Kortni_Kech_1";
		break;
		
		case "DTSG_Kortni_Kech_1":
			dialog.text = "Oh? Ich muss zugeben, Sie überraschen mich, Kapitän de Maure. Und was, Ihrer Meinung nach, wäre gleichwertig mit dem kahlen Kopf des alten Kanoniers, wenn ein Berg von Gold Ihnen nicht passt?";
			link.l1 = "Du hast es selbst gesagt - ein prächtiges Schiff, mit korrigierten Designfehlern. Ich bin gespannt, es selbst auszuprobieren. Du hast immer noch die Baupläne. Aber es gibt nur einen Charlie. Außerdem liegt es in deinem Interesse, mich zufrieden zu stellen.";
			link.l1.go = "DTSG_Kortni_Kech_2";
		break;
		
		case "DTSG_Kortni_Kech_2":
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				dialog.text = "Sie sind ein harter Verhandlungsführer. Haben Sie eine Ahnung, wie viel es uns gekostet hat, nur eines davon zu bauen?";
				link.l1 = "(Vertrauenswürdig) (Ehre) Ich weiß das sehr wohl, deshalb frage ich. Deine Hand steckt bis zum Ellbogen in meinem Maul. Du kannst versuchen, diesen Wolf zu erschießen. Aber du wirst die Hand verlieren. Und nicht nur sie.";
			}
			else
			{
				dialog.text = "Ich fürchte, der Bau einer solchen kostet weit mehr als das Gold, das wir für dich vorbereitet haben. Aber du hast mich amüsiert, Charles. Auf eine gute Art und Weise.";
				link.l1 = "Es war einen Versuch wert.";
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Perk Check Failed", "Trustworthy");
				if (sti(pchar.reputation.nobility) < 71) notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(71))+")", "None");
			}
			link.l1.go = "DTSG_Kortni_Kech_3";
		break;
		
		case "DTSG_Kortni_Kech_3":
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				dialog.text = "Ich sehe, Sie wissen, was Sie wollen und verfolgen Ihre Ziele im Leben\nNun, in Ordnung. Der Ketsch ist Ihr. Aber vergessen Sie das Geld - der Geldverleiher wird Ihnen sagen, dass er nichts weiß.";
				link.l1 = "Das passt mir.";
				link.l1.go = "DTSG_Kortni_Kech_4";
				pchar.questTemp.DTSG_Kech = true;
			}
			else
			{
				dialog.text = "Definitiv. Mein Leben war eine Geschichte des Ergreifens von Möglichkeiten und des Schutzes vor Risiken\nAlso bring Charlie hierher, und wir werden in Frieden auseinander gehen. Danach könnt ihr sogar die Kaution nehmen. Aber ich verlasse dieses Schiff.";
				link.l1 = "Dann lass es uns klären.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
				pchar.questTemp.DTSG_depozit = true;
			}
		break;
		
		case "DTSG_Kortni_Kech_4":
			dialog.text = "Ich kann nicht sagen, dass ich vollkommen zufrieden bin. Aber ich möchte dies schnell beenden. Gib mir jetzt, was ich will.";
			link.l1 = "Nicht 'was', sondern 'wer'. Aber wie du willst.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
		break;
		
		case "DTSG_Kortni_Dengi_1":
			dialog.text = "Noch kann ich es. Ich fange an zu glauben, dass es nicht nur darum geht, was ein Mann ist, sondern mit wem er sich umgibt - ein einfacher Job, einen alten Kanonier zu fangen, wurde zu einer Kopfschmerztablette wegen seines Kapitäns, das bist du, Charles\nRuf Charlie hierher. Diese Unordnung wird endgültig aufhören - wir werden den Anker heben, und unsere Schiffe werden sich trennen.";
			link.l1 = "Teil, sagst du?";
			link.l1.go = "DTSG_Kortni_Dengi_2";
		break;
		
		case "DTSG_Kortni_Dengi_2":
			dialog.text = "Sie sehen überrascht aus? Sie müssen gedacht haben, die Ketsch wäre Ihr rechtmäßiger Preis? Wir sind keine Piraten, Kapitän de Maure. Zivilisierte Menschen leben nach anderen, viel komplexeren Regeln. Das Schiff bleibt bei mir.";
			link.l1 = "Nun denn...";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
			pchar.questTemp.DTSG_depozit = true;
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel":
			DialogExit();
			
			//sld = CharacterFromID("Knippel");
			sld = GetCharacter(CreateCharacterClone(CharacterFromID("Knippel"), 0));
			sld.id = "KnippelClone";
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_VizyvaemKnippel_2";
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_2":
			dialog.text = "Geht es Ihnen gut, Herr? Ist das... der Oberst?";
			link.l1 = "Ja, Charlie, das ist der Oberst. Du kommst gerade rechtzeitig - ich war gerade dabei, dich selbst zu holen.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_3";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_3":
			dialog.text = "Hol mich, Kapitän?.. Jetzt gerade? Warum haben Sie so lange mit diesem... Mann gesprochen? Ich dachte, Sie wären in Schwierigkeiten, also bin ich selbst hierher gekommen.";
			link.l1 = "Richtig. Trotz des Sieges sind wir immer noch in Schwierigkeiten. Und wir würden es weiterhin sein, wenn der Oberst und ich nicht eine Lösung gefunden hätten.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_4";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_4":
			dialog.text = "Haben Sie es geschafft, ihn zu überzeugen, uns in Ruhe zu lassen, Herr?";
			link.l1 = "Leider nur ich. Nicht wir. Du... wirst mit ihm gehen, Charlie.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_5";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_5":
			dialog.text = "Was?.. Aber warum?.. Wir haben gewonnen!";
			link.l1 = "Verstehst du nicht? Wir können nicht ständig gewinnen - sie werden nicht aufhören, bis sie deinen Kopf bekommen.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_6";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_6":
			dialog.text = "Ich kann nicht glauben, dass Sie das dem alten Charlie antun, Kapitän. Sie sind genau wie Dick. Beide haben mir einmal gesagt, dass Sie meine Freunde waren. Und beide haben mich und jeden, der ihnen nahe stand, verlassen.";
			link.l1 = "Das ist die Bürde eines Kapitäns, seine Verantwortung. Ich sehe, du kannst das nicht verstehen, weil alles, was du tun musstest, war, Kanonen mit Kanonenkugeln zu laden.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_7";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_7":
			dialog.text = "Kannst nicht verstehen?.. Vielleicht bin ich einfach kein Verräter wie du? Du weißt, wo du hingehen solltest?";
			link.l1 = "Zur Hölle? Vielleicht hast du recht. Wir alle verdienen es.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_8";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_8":
			dialog.text = "Mach dich vom Acker, Herr.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_9";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_9":
			DialogExit();
			
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_VizyvaemKnippel_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			
			sld = CharacterFromID("KnippelClone");
			LAi_SetActorType(sld);
			sld = CharacterFromID("Knippel");
			RemovePassenger(pchar, sld);
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_10":
			dialog.text = "Herrlich. Ich habe fast gelacht. Hast du das gehört, Brian?\nManchmal fühlt es sich an wie eine Brise und überhaupt nicht irritierend, wenn man einfache Bauern reden hört. Du hast die richtige Entscheidung getroffen, Charles. Ich verstehe, wie schwer es für dich ist. Aber tröste dich mit dem Wissen, dass weder du noch jemand anders von deinen Männern jetzt leiden wird.";
			link.l1 = "Ich hoffe, Sie halten dieses Versprechen, Oberst.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_11";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_11":
			dialog.text = "Ich bin ein Mann meines Wortes. Abigails Schicksal ist ein Beweis dafür. Schau dir auch Brian an. Ein französischer Pirat, aber er hat die richtige Entscheidung getroffen, als es an der Zeit war, sich der richtigen Seite anzuschließen. Und niemand legt Hand an ihn, solange er uns treu dient. Wie er, bewegen Sie sich, Kapitän de Maure, in die richtige Richtung.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Kech"))
			{
				link.l1 = "Da wir gerade von Bewegung sprechen. Ich möchte so schnell wie möglich hier raus. Auf diesem zweifellos schnellen Schiff, das Sie mir versprochen haben, Oberst.";
			}
			else
			{
				link.l1 = "Ich bin kein Pirat. Und ich habe nicht vor, mich so schnell der englischen Flotte anzuschließen. Aber ich beabsichtige, die versprochene Belohnung einzufordern.";
			}
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_12";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_12":
			if (CheckAttribute(pchar, "questTemp.DTSG_Kech"))
			{
				dialog.text = "I won't hide it - it feels like tearing her from my heart. I'll have to spend on a new one, but perhaps it's worth it - too long have I been troubled by the thought that Charlie might spill the beans\nIf you don't talk or commit serious crimes against England, consider that we're no longer enemies. Enjoy the new ship; she's indeed beautiful. Goodbye, Charles. Brian - prepare a boat for us. Charlie - follow me as you have no say in the matter.";
				link.l1 = "Auf Wiedersehen. Euch allen.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel_13";
			}
			else
			{
				dialog.text = "Schade, wir brauchen immer fähige Leute, unabhängig von ihrer Nationalität. Aber natürlich hast du die Belohnung immer noch verdient. Du kannst sicher nach Port Royal gehen - Ich komme dort an, bevor irgendein anderes Schiff auf dieser Ketsch ankommt.";
				link.l1 = "Ich hoffe es. Und ich hoffe, dass in Port Royal keine bewaffnete Eskorte auf mich wartet.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel_14";
			}
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_13":
			DialogExit();
			
			AddQuestRecord("DTSG", "20");
			CloseQuestHeader("DTSG");
			ChangeOfficersLoyality("bad_all", 5);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "fame", -10);
			AddCrewMorale(Pchar, -10);
			LAi_ReloadBoarding();
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_14":
			dialog.text = "Zweifelst du wieder an meinem Wort? Schande über dich. Du hast dir die Dankbarkeit der gesamten englischen Marine verdient. Wenn du jemals etwas brauchst, oder dich entscheidest, dich uns anzuschließen, kontaktiere mich, Kapitän de Maure.";
			link.l1 = "Einst versuchte ich, Unterstützung und Verbindungen zur englischen Geheimdienst zu knüpfen. Es hat nicht funktioniert. Also auf Wiedersehen, Oberst.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_15";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_15":
			DialogExit();
			
			if (CheckAttribute(pchar, "questTemp.DTSG_depozit"))
			{
				ChangeCharacterNationReputation(pchar, ENGLAND, 30);
			}
			pchar.GenQuest.CannotTakeShip = true;
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition.l1 = "MapEnter";
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition = "DTSG_Kortni_KechNeNash";
			AddQuestRecord("DTSG", "21");
			CloseQuestHeader("DTSG");
			ChangeOfficersLoyality("bad_all", 5);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "fame", -10);
			AddCrewMorale(Pchar, -10);
			LAi_ReloadBoarding();
			Achievment_Set("ach_CL_114");
		break;
		
	}
} 
