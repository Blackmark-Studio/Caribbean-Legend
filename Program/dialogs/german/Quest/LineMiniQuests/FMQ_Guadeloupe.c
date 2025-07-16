// Addon-2016 Jason, французские миниквесты (ФМК) Гваделупа
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ein offensichtlicher Fehler. Informiere die Entwickler darüber.";
			link.l1 = "Oh, ich werde es tun.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестодатель
		case "citizen":
			DelMapQuestMarkCity("Baster");
			LAi_SetImmortal(npchar, false);
			LAi_RemoveLoginTime(npchar);
			dialog.text = "Grüße, Kapitän! Ich habe ein Geschäftsvorschlag, den Sie sehr interessant finden werden.";
			link.l1 = "Mach weiter, Monsieur.";
			link.l1.go = "citizen_1";
			DelLandQuestMark(npchar);
		break;
		
		case "citizen_1":
			dialog.text = "Ich möchte Ihr Schiff für einen Transportauftrag von Guadeloupe nach Spanisch-Haupt anheuern.";
			link.l1 = "Möchten Sie dort als Passagier segeln?";
			link.l1.go = "citizen_2";
			link.l2 = "Spanisches Haupt? Ich werde passieren. Wir sind nicht wirklich Freunde mit den Spaniern. Ich schlage vor, du suchst einen anderen Narren.";
			link.l2.go = "citizen_no";
		break;
		
		case "citizen_no":
			dialog.text = "Wie Sie sagen, Kapitän, obwohl es keine hochriskante Reise ist. Lebewohl.";
			link.l1 = "Auf Wiedersehen.";
			link.l1.go = "citizen_exit";
		break;
		
		case "citizen_no_1":
			dialog.text = "Wie du wünschst, Kapitän. Auf Wiedersehen!";
			link.l1 = "Auf Wiedersehen.";
			link.l1.go = "citizen_exit";
		break;
		
		case "citizen_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
		break;
		
		case "citizen_2":
			dialog.text = "Nicht ganz so, Monsieur. Ein Passagier ist ein Mann, der vom Willen eines Kapitäns abhängig ist. Ich möchte Sie, Ihre Mannschaft und Ihr Schiff anheuern, um mich zusammen mit zwei meiner Freunden nach Panama zu bringen.";
			link.l1 = "Nach Panama? Wie? Du willst um den ganzen Kontinent segeln?";
			link.l1.go = "citizen_3";
		break;
		
		case "citizen_3":
			dialog.text = "Ha-ha-ha! Guter Witz, Kapitän. Natürlich nicht. Alles was du tun musst, ist uns zur Moskitobucht zu bringen, die nicht weit von Portobello entfernt ist. Wir machen unseren Weg nach Panama auf eigene Faust, es wird nicht unsere erste Tour durch den Dschungel sein.";
			link.l1 = "Wie steht's mit der Bezahlung?";
			link.l1.go = "citizen_4";
		break;
		
		case "citizen_4":
			dialog.text = "Zwei Truhen voller Dublonen. Dreihundert Stück. Du bekommst eine im Voraus, sobald wir an Bord sind. Die zweite Truhe wird dir gehören, sobald wir unser Ziel erreichen.";
			link.l1 = "Ein ernsthafter Lohn für so eine leichte Arbeit. Wo ist der Haken, mein guter Mann?";
			link.l1.go = "citizen_5";
		break;
		
		case "citizen_5":
			dialog.text = "Kapitän, Zeit ist Geld, meine Freunde und ich haben es nicht. Wir müssen von hier aus heute Nacht segeln und wir müssen in zehn Tagen dort sein. Dies wird unsere zweite Amtszeit sein. Also, bist du dabei?";
			link.l1 = "Abgemacht!";
			link.l1.go = "citizen_6";
			link.l2 = "Es tut mir leid, Monsieur, aber Ihr Vorschlag klingt für mich allzu verdächtig. Suchen Sie sich einen anderen Narren.";
			link.l2.go = "citizen_no_1";
		break;
		
		case "citizen_6":
			dialog.text = "Prächtig. Meine Freunde sind gerade im Dschungel, ich werde sie über unsere Vereinbarung informieren. Du wirst uns heute Abend um zehn Uhr am Capster Strand finden. Sei nicht zu spät, Kapitän!";
			link.l1 = "Gut. Capster Strand, heute Nacht, zehn Uhr.";
			link.l1.go = "citizen_7";
		break;
		
		case "citizen_7":
			dialog.text = "Einen Moment, Kapitän, wir haben uns noch nicht einmal vorgestellt. Mein Name ist Bertrand Pinette. Und du bist...";
			link.l1 = ""+GetFullName(pchar)+". Kapitän "+GetFullName(pchar)+". Wir sehen uns, Monsieur Pinette.";
			link.l1.go = "citizen_8";
		break;
		
		case "citizen_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "OpenTheDoors", 20.0);
			npchar.location = "None";
			AddQuestRecord("FMQ_Guadeloupe", "1");
			pchar.quest.FMQG_Capster.win_condition.l1 = "Hour";
			pchar.quest.FMQG_Capster.win_condition.l1.start.hour = 22.00;
			pchar.quest.FMQG_Capster.win_condition.l1.finish.hour = 23.99;
			pchar.quest.FMQG_Capster.win_condition.l2 = "Ship_location";
			pchar.quest.FMQG_Capster.win_condition.l2.location = "Shore29";
			pchar.quest.FMQG_Capster.win_condition.l3 = "location";
			pchar.quest.FMQG_Capster.win_condition.l3.location = "Shore29";
			pchar.quest.FMQG_Capster.function = "FMQG_CapsterBeach";
			SetFunctionTimerCondition("FMQG_StartLate", 0, 0, 1, false);
			pchar.questTemp.FMQG = "begin";
			pchar.GenQuest.SmugglersBlock = "baster_tavern";
		break;
		
		case "citizen_9":
			DelLandQuestMark(npchar);
			dialog.text = "Kapitän "+GetFullName(pchar)+", da bist du ja. Können wir loslegen?";
			link.l1 = "Ja. Willkommen an Bord.";
			link.l1.go = "citizen_10";
		break;
		
		case "citizen_10":
			dialog.text = "Sehr gut. Nimm deine Anzahlung - eine Kiste voller Dublonen. Und denk daran - du hast nur zehn Tage Zeit, um uns an unser Ziel zu bringen. Keinen Tag länger!";
			link.l1 = "Ich erinnere mich an die Bedingungen. Keine Sorge, wir werden es rechtzeitig schaffen. Nehmt eure Plätze ein.";
			link.l1.go = "citizen_11";
		break;
		
		case "citizen_11":
			DialogExit();
			GiveItem2Character(pchar, "chest");
			log_info("You have received a chest full of doubloons");
			PlaySound("interface\important_item.wav");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "officers", "sea_1", "none", "", "", "FMQG_OnBoard", 20.0);
			for (i=2; i<=3; i++)
			{
				sld = characterFromId("FMQG_pass_"+i);
				LAi_ActorRunToLocation(sld, "officers", "sea_"+i, "none", "", "", "", 10.0);
			}
			pchar.quest.FMQG_SailStart.win_condition.l1 = "location";
			pchar.quest.FMQG_SailStart.win_condition.l1.location = "Guadeloupe";
			pchar.quest.FMQG_SailStart.function = "FMQG_SailingStart";
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("FMQG_SailingLate", 0, 0, 20, false);
				SetFunctionTimerCondition("FMQG_MutiniActivate", 0, 0, 40, false);
			}
			else
			{
				SetFunctionTimerCondition("FMQG_SailingLate", 0, 0, 10, false);
				SetFunctionTimerCondition("FMQG_MutiniActivate", 0, 0, 20, false);
			}
			pchar.questTemp.FMQG = "sail";
			DeleteAttribute(pchar, "GenQuest.SmugglersBlock");
		break;
		
		case "citizen_12":
			dialog.text = "Also, Kapitän, Sie haben Ihren Teil des Handels vollständig erfüllt. Jetzt bin ich dran. Nehmen Sie diese Truhe, zusammen mit unserer tiefsten Dankbarkeit.";
			link.l1 = "Freut mich, Geschäfte mit Ihnen zu machen, Monsieur.";
			link.l1.go = "citizen_13";
		break;
		
		case "citizen_13":
			GiveItem2Character(pchar, "chest");
			log_info("You have received a chest full of doubloons");
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Sailing", 200);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			dialog.text = "Ebenso. Lebewohl, Kapitän "+GetFullName(pchar)+".";
			link.l1 = "Auf Wiedersehen!";
			link.l1.go = "citizen_14";
		break;
		
		case "citizen_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 20.0);
			for (i=2; i<=3; i++)
			{
				sld = characterFromId("FMQG_pass_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
				sld.lifeday = 0;
			}
			AddQuestRecord("FMQ_Guadeloupe", "6");
			CloseQuestHeader("FMQ_Guadeloupe");
			pchar.questTemp.FMQG = "pause";
			pchar.quest.FMQG_Continue.win_condition.l1 = "Ship_location";
			pchar.quest.FMQG_Continue.win_condition.l1.location = "Baster_town";
			pchar.quest.FMQG_Continue.win_condition.l2 = "location";
			pchar.quest.FMQG_Continue.win_condition.l2.location = "Baster_town";
			pchar.quest.FMQG_Continue.function = "FMQG_BasterContinue";
			/* pchar.quest.FMQG_Block1.win_condition.l1 = "Rank";
			pchar.quest.FMQG_Block1.win_condition.l1.value = 13;
			pchar.quest.FMQG_Block1.win_condition.l1.operation = ">=";
			pchar.quest.FMQG_Block1.function = "FMQG_Block"; */
			//SetFunctionTimerCondition("FMQG_Block", 0, 0, 90, false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);	// лесник - открыть оружие снова.
			AddMapQuestMarkCity("baster", false);
		break;
		
		case "citizen_12a":
			dialog.text = "Also, Kapitän, hier sind wir. Sie haben nur die Hälfte Ihres Teils des Handels erfüllt, daher werde ich dasselbe tun. Behalten Sie Ihre Anzahlung als volle Bezahlung. Ich hoffe, Sie haben nichts dagegen, es war schließlich Ihr Fehler.";
			link.l1 = "Kann nicht sagen, dass mir das gefällt, aber ich gebe zu, dass du recht hast. Lass uns jetzt unsere Wege trennen.";
			link.l1.go = "citizen_13a";
		break;
		
		case "citizen_13a":
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			dialog.text = "Jedenfalls, danke für den Dienst, Kapitän "+GetFullName(pchar)+". Lebewohl!";
			link.l1 = "Auf Wiedersehen.";
			link.l1.go = "citizen_14";
		break;
		
		case "citizen_15":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("bridgetown");
			dialog.text = "Oh! Was für ein Treffen! "+TimeGreeting()+", "+GetFullName(pchar)+"! Aber wie?";
			link.l1 = TimeGreeting()+", Herr Pinette. Es war nicht leicht, Sie zu finden.";
			link.l1.go = "citizen_16";
		break;
		
		case "citizen_16":
			sld = characterFromId("Baster_usurer");
			dialog.text = "Und was ist der Grund, Kapitän?";
			link.l1 = "Mein guter Herr, es gibt einen Mann namens "+GetFullName(sld)+" und er ist sehr gespannt, Sie zu sehen. Ich nehme an, Sie wissen warum.";
			link.l1.go = "citizen_17";
		break;
		
		case "citizen_17":
			sld = characterFromId("Baster_usurer");
			dialog.text = "Natürlich tue ich das, aber Sie, mein lieber Kapitän, müssen auch wissen, dass ich nicht darauf brenne, Monsieur zu sehen "+GetFullName(sld)+" überhaupt nicht. Bist du sein Kopfgeldjäger? Ich verstehe es einfach nicht.";
			link.l1 = "Ach, aber das bin ich im Moment und ich bin nicht glücklich darüber. Ich habe einen Fehler gemacht und jetzt monsieur "+GetFullName(sld)+", verdammt sei er, hat mir eine Wahl gestellt. Entweder deine glorreiche Rückkehr nach Guadeloupe oder mein Hintern als Komplize in deinem kleinen Unterfangen, don Carlos de Milyar zu befreien. Das wird mir wehtun, das weißt du.";
			link.l1.go = "citizen_18";
		break;
		
		case "citizen_18":
			sld = characterFromId("Baster_usurer");
			dialog.text = "Ach, dieser Bastard! Das ist eine sehr sündige Art, Leute zu erpressen!.. Also, Kapitän, was wird es sein, wirst du eine Wahl treffen oder wirst du jemandem wie ihm erlauben, dich zu erpressen?";
			link.l1 = "Und was denkst du? Ich glaube, du kommst mit mir nach Basse-Terre.";
			link.l1.go = "citizen_19";
			link.l2 = "Habe ich hier eine Wahl?";
			link.l2.go = "citizen_25";
		break;
		
		case "citizen_19":
			dialog.text = "Oh, ich muss Sie enttäuschen, Kapitän. Ich habe keine Lust, an Bord Ihres wunderschönen Schiffes zu gehen. Sie werden hier mit Gewalt nichts erreichen, der Ort ist von Wachen umgeben und ich werde um Hilfe schreien, falls Sie irgendwelche gewalttätigen Absichten zeigen. Sicher, Sie könnten versuchen, mich zu erstechen, aber unser guter Freund wird keine Münzen von einer kalten Leiche bekommen. Also, der klügste Weg für Sie in diesem Moment - ist, mich in Ruhe zu lassen. Ich werde Ihnen erlauben, unverletzt zu gehen.";
			link.l1 = "Glaubst du wirklich, dass ich einfach weggehen werde, nach allem, was passiert ist? Du hast mich in dieses Chaos hineingezogen, du Bastard, es ist Zeit zu zahlen!";
			link.l1.go = "citizen_20";
			link.l2 = "Du hast recht, nehme ich an. Ich mag die Idee, dich zu erstechen, aber es ist sinnlos. Versuche nicht einmal zu hoffen, dass dies das Ende ist. Ich gehe jetzt nach Basse-Terre, wo ich unserem guten Freund von deinem Aufenthaltsort erzählen werde. Und dann wird er maskierte Männer hinter dir herschicken.";
			link.l2.go = "citizen_21";
		break;
		
		case "citizen_20":
			dialog.text = "A-ah! Soldaten! Hilfe!!!";
			link.l1 = "...";
			link.l1.go = "citizen_fight";
		break;
		
		case "citizen_21":
			dialog.text = "Aber natürlich. Sag deinem Chef, er soll seine maskierten Männer im Zaum halten - ich werde heutzutage sehr beliebt. Leb wohl, Kapitän.";
			link.l1 = "...";
			link.l1.go = "citizen_22";
		break;
		
		case "citizen_22":
			DialogExit();
			LAi_SetActorType(npchar);
			AddQuestRecord("FMQ_Guadeloupe", "19");
			pchar.quest.FMQG_Mayak.win_condition.l1 = "location";
			pchar.quest.FMQG_Mayak.win_condition.l1.location = "Mayak2";
			pchar.quest.FMQG_Mayak.function = "FMQG_Lighthouse";
		break;
		
		case "citizen_23":
			DelLandQuestMark(npchar);
			dialog.text = "Warte! Ich ergebe mich! Ich ergebe mich!";
			link.l1 = "Genau so! Jetzt leg deine Waffe ab und marschiere zum Schiff!";
			link.l1.go = "citizen_24";
		break;
		
		case "citizen_24":
			DialogExit();
			chrDisableReloadToLocation = false;
			RemoveAllCharacterItems(npchar, true);
			DoQuestReloadToLocation("Mayak2", "goto", "goto1", "FMQG_OnLighthouse");
		break;
		
		case "citizen_25":
			dialog.text = "Es gibt immer eine Wahl, Kapitän. Soweit ich verstehe, würden Sie mich nicht jagen, wenn es keine Bedrohungen von diesem Bankier gäbe?";
			link.l1 = "Genau.";
			link.l1.go = "citizen_26";
		break;
		
		case "citizen_26":
			dialog.text = "Gut. Dann werde ich Ihnen einen soliden Weg organisieren, um ihm das Maul zu stopfen. Lassen Sie uns einen Brief schreiben, den Sie zu Ihrem Arbeitgeber bringen werden. Sagen Sie ihm, dass, wenn er jemals anfängt zu reden, der Gouverneur von Guadeloupe über den Mann erfahren wird, der das Verschwinden der Courage - eines Kurier-Luggers auf einer Mission, eine große Menge Diamanten zu transportieren - geplant und investiert hat.";
			link.l1 = "Hm. Ich glaube, ich beginne zu folgen, Monsieur Pinette.";
			link.l1.go = "citizen_27";
		break;
		
		case "citizen_27":
			dialog.text = "Froh, dass Sie so schlau sind, Kapitän. De Lion wird persönlich den Kopf des schlauen Geizhalses an die Stadttore nageln, wenn er die Wahrheit hinter dem Verschwinden der Courage erfährt. In diesem Brief, den ich schreiben werde, finden Sie Beweise, die den Erpresser beruhigen werden. Geben Sie mir eine Minute, um meinen Stift zu holen.";
			link.l1 = "In Ordnung...";
			link.l1.go = "citizen_28";
		break;
		
		case "citizen_28":
			LAi_Fade("", "");
			GiveItem2Character(pchar, "letter_baker");
			ChangeItemDescribe("letter_baker", "itmdescr_letter_pinett");
			dialog.text = "(schreibend) Hier, nimm es. Es gibt zwei ähnliche Briefe in diesem Paket. Gib einen an den Bankier, lass ihn sich daran erfreuen. Behalte den anderen für dich und verstecke ihn.";
			link.l1 = " Ist die Information vertrauenswürdig?";
			link.l1.go = "citizen_29";
		break;
		
		case "citizen_29":
			sld = characterFromId("Baster_usurer");
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Baster", false);
			dialog.text = "Ich kann es schwören, du hast mir geholfen und jetzt werde ich dir helfen. Seien Sie versichert, der Erpresser wird Sie in Ruhe lassen, sobald er dieses Testament liest. Ah, ja... Noch eine Sache, Kapitän. Da wir das friedlich geregelt haben... Ich habe ein Versteck und ich werde dir sagen, wo du es finden kannst, wenn du mir versprichst, in Zukunft meine Operationen zu meiden. Sie werden mich sowieso nie wieder einen Fuß auf Guadeloupe setzen lassen.";
			link.l1 = "Wenn der Brief wie beabsichtigt funktioniert, dann kann ich Ihnen das durchaus versprechen.";
			link.l1.go = "citizen_30";
		break;
		
		case "citizen_30":
			dialog.text = "Es ist also ein Abkommen. Suchen Sie zwischen den Felsen in der Höhle von Guadeloupe. Es soll Ihnen als bescheidene Entschädigung für Ihre Mühen dienen. Gott beschütze dich, Kapitän.";
			link.l1 = "Gleichfalls, Monsieur Pinette.";
			link.l1.go = "citizen_31";
		break;
		
		case "citizen_31":
			DialogExit();
			pchar.questTemp.FMQG = "letter";
			AddQuestRecord("FMQ_Guadeloupe", "24");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 1;
		break;
		
		case "citizen_fight":
			chrDisableReloadToLocation = true;
			LAi_group_Delete("EnemyFight");
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			DoQuestFunctionDelay("FMQG_PlantationGuards", 3.0);
			pchar.questTemp.FMQG = "fail";
			AddQuestRecord("FMQ_Guadeloupe", "18");
			CloseQuestHeader("FMQ_Guadeloupe");
		break;
		
		// вестовой к ростовщику
		case "cureer":
			DelMapQuestMarkCity("baster");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			npchar.lifeday = 0;
			dialog.text = "Grüße, Herr! Sie sind Kapitän "+GetFullName(pchar)+", stimmt's?";
			link.l1 = "Richtig. Was kann ich für dich tun?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			sld = characterFromId("BasTer_usurer");
			dialog.text = "Herr "+GetFullName(pchar)+", der Bankbesitzer von Basse-Terre bittet Sie, ihn so bald wie möglich zu besuchen. Er hat mich beauftragt, unser Hafenbüro jeden Tag zu überprüfen, um sicherzustellen, dass Ihre Ankunft nicht übersehen wird.";
			link.l1 = "Interessant, und warum wäre er so begierig darauf, mich zu sehen?";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			dialog.text = "Herr "+GetFullName(sld)+" wird Ihnen persönlich sagen warum. Ich hoffe, dass Sie seine Einladung nicht ablehnen werden.";
			link.l1 = "Hm.. Gut. Diese Bankiers sind ein mächtiges Volk und sie verschwenden nie Zeit mit kleinen Fischen. Ich werde den Mann so bald wie möglich sehen.";
			link.l1.go = "cureer_3";
		break;
		
		case "cureer_3":
			dialog.text = "Danke dir, Kapitän. Lebewohl!";
			link.l1 = "Auf Wiedersehen.";
			link.l1.go = "cureer_4";
		break;
		
		case "cureer_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Baster_town", "reload1_back", true);
			LocatorReloadEnterDisable("Baster_town", "reload2_back", true);
			LocatorReloadEnterDisable("Baster_town", "gate_back", true);//закрыть выходы из города
			pchar.questTemp.FMQG = "continue";
			pchar.quest.FMQG_Block.over = "yes";
			pchar.quest.FMQG_Block1.over = "yes";
			AddLandQuestMark(characterFromId("Baster_usurer"), "questmarkmain");
		break;
		
		// Жан Дено
		case "Juan":
			dialog.text = "Argh! Du Abschaum! Keine Chance, dass das ein Zufallstreffen ist...";
			link.l1 = "Wahrlich, Jean... entschuldigung, ich meinte Juan. Ich habe dich aufgespürt. Würdest du nun so freundlich sein, dich in meinen Frachtraum zu bewegen? Lass etwas Dampf ab und wir werden reden.";
			link.l1.go = "Juan_1";			
		break;
		
		case "Juan_1":
			DialogExit();
			Lai_SetPlayerType(pchar);
			DeleteAttribute(npchar, "DontRansackCaptain");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			pchar.questTemp.FMQG.Prisoner = GetFullName(npchar);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			AddQuestRecord("FMQ_Guadeloupe", "14");
			pchar.questTemp.FMQG = "juan_capture";
			DoQuestCheckDelay("LAi_ReloadBoarding", 3.5);
		break;
		
		case "Juan_2":
			dialog.text = "";
			link.l1 = "Ich habe meinen Teil der Abmachung erfüllt. Jetzt bist du dran. Schieß los und denke an die Konsequenzen des Lügens.";
			link.l1.go = "Juan_3";
		break;
		
		case "Juan_3":
			dialog.text = "Sie finden Bertrand Pinette auf Barbados, genauer gesagt auf der Hauptplantage. Er wollte dort seine Operationen fortsetzen. Der Aufseher der Plantage ist ein Freund von ihm.";
			link.l1 = "Welche Art von Operationen?";
			link.l1.go = "Juan_4";
		break;
		
		case "Juan_4":
			dialog.text = "Das Gleiche, was er auf Guadeloupe hatte. Halblegaler Handel, Schmuggel, Sklaven. Ich denke, er plant, Sklavenhandel und Zuckerhandel zu betreiben, warum sollte er sonst auf eine Plantage gezogen sein?";
			link.l1 = "Ich verstehe. Hat er irgendwelche Gönner unter den englischen Behörden?";
			link.l1.go = "Juan_5";
		break;
		
		case "Juan_5":
			dialog.text = "Ich vermute. Ein neugieriger Charakter, er ist. Hat immer Freunde überall.";
			link.l1 = "Sonst noch etwas?";
			link.l1.go = "Juan_6";
		break;
		
		case "Juan_6":
			dialog.text = "Wie was? Schlau und klug, weiß immer Dinge, hat immer ein Ass in der Hand. Ich hatte nicht viel Zeit, mehr über ihn zu erfahren.";
			link.l1 = "Verstanden. Gut, muss nach Bridgetown segeln. Sie sind frei zu gehen, Don Juan. Denken Sie nicht einmal daran, Pinette zu warnen. Wenn ich ihn dort nicht finde, ist es wieder Ihr Hintern, der auf dem Spiel steht.";
			link.l1.go = "Juan_7";
		break;
		
		case "Juan_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.questTemp.FMQG = "headhunter_pinett";
			AddQuestRecord("FMQ_Guadeloupe", "17");
			// Пинетта - в Бриджтаун
			sld = characterFromId("FMQG_pass_1");
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation_F2", "goto", "goto1");
			sld.Dialog.currentnode = "citizen_15";
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("bridgetown", false);
		break;
		
		case "killer":
			dialog.text = "Es tut mir leid, Kumpel. Nichts Persönliches. Du weißt zu viel, das ist dein Problem.";
			link.l1 = "...";
			link.l1.go = "killer_1";
		break;
		
		case "killer_1":
			DialogExit();
			AddLandQuestMark(characterFromId("Baster_usurer"), "questmarkmain");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // правки релиза								  
			LAi_group_Delete("EnemyFight");
			int n = 2;
			if (MOD_SKILL_ENEMY_RATE > 6) n = 3;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("FMQG_killer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQG_KillersDestroy");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
