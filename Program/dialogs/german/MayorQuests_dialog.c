void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		//----------------- уничтожение банды ----------------------
		case "DestroyGang_begin":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //боевке можно
			DeleteAttribute(&locations[FindLocation(pchar.GenQuest.DestroyGang.Location)], "DisableEncounters"); //энкаунтеры можно 
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.DestroyGang.MayorId)]);
			dialog.text = LinkRandPhrase("Bargeld auf dem Fass "+GetSexPhrase("Kumpel","Fräulein")+"! Mein Name ist "+GetFullName(npchar)+", und ich bin nicht gewohnt, Einwände zu hören...","Jetzt zeig mir deine Geldbörse, "+GetSexPhrase("Kumpel","Fräulein")+", und mach schnell! Mein Name ist  "+GetFullName(npchar)+", und ich hoffe, du hast von mir gehört...","Gib mir alles Wertvolle, was du hast, mitsamt den Inhalt deines Geldbeutels. Und beeile dich, Geduld ist nicht meine Stärke. Kann ich von meinem Blutdurst nicht behaupten!");
			Link.l1 = LinkRandPhrase("Heh, also bist du dieser berühmte Bandit "+GetFullName(npchar)+", über den der örtliche Gouverneur "+sTemp+" nie aufhört zu sprechen?","Oh, also bist du dieser Bandit, der vom örtlichen Gouverneur "+sTemp+" gejagt wird was?!","Bin froh"+GetSexPhrase("","")+", dich zu sehen, "+GetFullName(npchar)+". Der örtliche Gouverneur, "+sTemp+" spricht nur über dich.");
			Link.l1.go = "DestroyGang_1";
		break;		
		case "DestroyGang_1":
			dialog.text = LinkRandPhrase("Jawohl, ich bin in diesen Landen bekannt, he-he... Warte mal, bist du nicht "+GetSexPhrase("ein anderer dreckiger Hund","eine andere dreckige Hündin")+" des Gouverneurs, den er geschickt hat, um mich aufzuspüren?","Der Gouverneur ist mein guter Freund, das ist wahr. Und bist du nicht zufällig, "+GetSexPhrase("ein weiterer Held","eine weitere Heldin")+" gesandt von ihm für meinen Kopf?","Der Gouverneur ist mein bester Kumpel, das ist kein Geheimnis, he-he. Aber woher weißt du das? Vielleicht hat er dich hinter mich geschickt?");
			Link.l1 = LinkRandPhrase("Genau, Schurke. Bereite dich auf den Tod vor!","Du bist ja ein ganz scharfsinniges Kerlchen! Also gut, Zeit, mit der Liquidation fortzufahren. Genug geredet.","Ja, das bin ich. Zieh deine Waffe, Kumpel! Lass uns mal sehen, welche Farbe dein Blut hat.");
			Link.l1.go = "DestroyGang_ExitFight";	
			Link.l2 = LinkRandPhrase("Ach, vergiss es! Ich brauche solche Probleme überhaupt nicht...","Nein, nein, ich bin kein Held, auf keinen Fall...","Nein, nein, würde ich niemals! Ich brauche keine Schwierigkeiten...");
			Link.l2.go = "DestroyGang_2";	
		break;
		case "DestroyGang_2":
			dialog.text = LinkRandPhrase("Das ist besser, "+GetSexPhrase("Kumpel","Fräulein")+"...Und jetzt verschwinde!","Und das ist eine richtige Entscheidung. Wüsstest du nur, wie viele Helden ich in eine andere Welt geschickt habe... Gut, weniger Worte. Verschwinde, "+GetSexPhrase("du Stück Scheiße","du Schlampe")+"!","Gut"+GetSexPhrase("er Junge","es Mädchen")+"! Eine sehr weise Entscheidung - sich nicht in die Angelegenheiten anderer einzumischen... Also, verschwinde schon, "+GetSexPhrase("Kumpel","Fräulein")+".");
			Link.l1 = "Auf Wiedersehen und viel Glück für dich...";
			Link.l1.go = "DestroyGang_ExitAfraid";	
		break;

		case "DestroyGang_ExitAfraid":
			pchar.GenQuest.DestroyGang = "Found"; //флаг нашёл, но струсил
			npchar.money = AddMoneyToCharacter(npchar, sti(pchar.money));
			pchar.money = 0;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, LAi_GetCharacterHP(npchar)-1, false, "DestroyGang_SuddenAttack");
			for(i = 1; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;	
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
				LAi_SetImmortal(sld, true);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "DestroyGang_SuddenAttack");
			}
			DialogExit();
		break;

		case "DestroyGang_ExitFight":
			for(i = 0; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "DestroyGang_Afrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		// ОЗГ - пассажир
		case "ContraPass_abordage":
			dialog.text = "Arghh, du Schurke! Wie konntest du es wagen, mein Schiff anzugreifen?! Dafür wirst du bezahlen!";
			link.l1 = "Im Gegenteil, ich werde tatsächlich dafür bezahlt. Sie haben einen bestimmten Mann an Bord, namens "+pchar.GenQuest.TakePassenger.Name+". Er ist derjenige, den ich brauche.";
			link.l1.go = "ContraPass_abordage_1";
		break;
		
		case "ContraPass_abordage_1":
			dialog.text = "Ich wusste, dass dieser Gauner Ärger bringen würde... Aber du wirst mich nicht so leicht bekommen! Verteidige dich, dreckiger Pirat!";
			link.l1 = "Du bist derjenige, der an Verteidigung denken muss, du Hundsfott.";
			link.l1.go = "ContraPass_abordage_2";
		break;
		
		case "ContraPass_abordage_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "ContraPass_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Tempsailor":
			dialog.text = "Kapitän, wir haben die Kabinen und den Laderaum durchsucht, wie Sie es befohlen haben. Dieser Schurke versuchte sich zu verstecken, aber wir haben ihn gefunden.";
			link.l1 = "Ausgezeichnet! Wo ist er jetzt?";
			link.l1.go = "Tempsailor_1";
		break;
		
		case "Tempsailor_1":
			dialog.text = "Er ist im Laderaum, wie Sie uns befohlen haben.";
			link.l1 = "Ausgezeichnet! Jetzt lass uns von diesem alten Kahn loskommen. Es ist Zeit zurückzukehren.";
			link.l1.go = "Tempsailor_2";
		break;
		
		case "Tempsailor_2":
			dialog.text = "Sofort, Kapitän!";
			link.l1 = "...";
			link.l1.go = "Tempsailor_3";
		break;
		
		case "Tempsailor_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			sld = GetCharacter(NPC_GenerateCharacter("ContraPass", "citiz_"+(rand(9)+11), "man", "man", 10, sti(pchar.GenQuest.TakePassenger.Nation), -1, true, "quest"));
			sld.name = pchar.GenQuest.TakePassenger.Name;
			sld.lastname = "";
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(sld);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.GenQuest.TakePassenger.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
		break;
		
		case "Fugitive_city": // ходит по городу
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "Was wünschen Sie, Herr?";
			link.l1 = "Nun-nun... Also du bist "+pchar.GenQuest.FindFugitive.Name+", nicht wahr? Ich freue mich sehr, dich zu sehen...";
			link.l1.go = "Fugitive_city_1";
		break;
		
		case "Fugitive_city_1":
			dialog.text = "Nun, das bin ich in der Tat, obwohl ich mich frage, warum du dich freust, mich zu sehen? Scheint mir seltsam, da ich dich noch nie zuvor gesehen habe... Würdest du dich erklären?";
			link.l1 = "Aber natürlich. Ich komme aus "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity+"Gen")+", auf Befehl des örtlichen Gouverneurs. Sie sind verhaftet und ich muss Sie in eben diese Stadt bringen... Oh, und Hände weg von Ihrem Säbel! Versuchen Sie nichts Dummes, guter Mann, sonst wird es schlecht für Sie ausgehen!";
			link.l1.go = "Fugitive_city_2";
		break;
		
		case "Fugitive_city_2":
			dialog.text = "So, Sie haben mich also doch gefunden..., hören Sie mir zu und vielleicht ändern Sie Ihre Meinung. Ja, ich habe die Garnison verlassen. Aber ich konnte die Degradierung unseres Heeres nicht mit ansehen!\nIch wollte ein friedliches Leben und habe dieses Leben hier in diesem Dorf gefunden... Lassen Sie mich in Ruhe, sagen Sie ihnen, dass Sie mich nicht gefunden haben oder dass ich mit Piraten in die offene See geflohen bin. Im Gegenzug gebe ich Ihnen diesen Beutel mit Bernstein. Ein sehr wertvoller Gegenstand, muss ich sagen...";
			link.l1 = "Denken Sie nicht einmal daran, mich zu bestechen! Übergeben Sie Ihre Waffe und folgen Sie mir!";
			link.l1.go = "Fugitive_city_fight";
			link.l2 = "Hmm... Degradierung? Ruhiges und friedliches Leben? Nun, ich denke, ich kann deinen Wunsch erfüllen. Wo ist dein Bernstein?";
			link.l2.go = "Fugitive_city_gift";
		break;
		
		case "Fugitive_city_fight":
			dialog.text = "Dann zieh dein Schwert, Söldner! Du wirst mich nicht so leicht bekommen!";
			link.l1 = "Also gut, lasst uns euren Wert sehen!";
			link.l1.go = "Fugitive_fight_1";
		break;
		
		case "Fugitive_city_gift":
			TakeNItems(pchar, "jewelry8", 50+hrand(25));
			TakeNItems(pchar, "jewelry7", 2+hrand(5));
			PlaySound("interface\important_item.wav");
			Log_Info("Du hast Bernstein erhalten");
			dialog.text = "Hier... Und ich hoffe wirklich, dass ich weder dich noch andere 'Gesandte' jemals wiedersehen werde.";
			link.l1 = "Ich versichere Ihnen, dass Sie es nicht werden. Auf Wiedersehen!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_gift_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.FindFugitive = "Found"; //флаг провалил
			AddQuestRecord("MayorsQuestsList", "12-4");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity));
		break;
		
		case "Fugitive_fight_1":// в городе и бухте
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			Diag.currentnode = "Fugitive_afterfight";
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Fugitive_afterfight":
			dialog.text = "Arrgh! Du hast gewonnen, fick dich! Ich ergebe mich...";
			link.l1 = "Haltet eure Zunge im Zaum! Und nun, gebt mir bitte euer Säbel... Folgt mir, und ohne dummheiten!";
			link.l1.go = "Fugitive_afterfight_1";
		break;
		
		case "Fugitive_afterfight_1":
			DialogExit();
			RemoveAllCharacterItems(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			//DeleteAttribute(npchar, "LifeDay");
			npchar.lifeday = 0;
			LAi_SetImmortal(npchar, true);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.GenQuest.FindFugitive.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
			pchar.GenQuest.FindFugitive = "Execute"; //флаг выполнил успешно
			pchar.quest.FindFugitive1.win_condition.l1 = "location";
			pchar.quest.FindFugitive1.win_condition.l1.location = pchar.GenQuest.FindFugitive.Startcity+"_townhall";
			pchar.quest.FindFugitive1.function = "FindFugitive_inResidence";
			SetFunctionTimerCondition("FindFugitive_Over", 0, 0, 30, false);
		break;
		
		case "Fugitive_shore": // в бухте
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "Herr, ich bin nicht in der Stimmung, mit Ihnen zu sprechen, also...";
			link.l1 = "Trotzdem wirst du mit mir reden müssen. Du bist "+pchar.GenQuest.FindFugitive.Name+", nicht wahr? Ich denke, du solltest es nicht leugnen.";
			link.l1.go = "Fugitive_shore_1";
		break;
		
		case "Fugitive_shore_1":
			dialog.text = "Und ich werde es nicht leugnen, das bin ich. Aber was willst du?";
			link.l1 = "Ich muss dich nach "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+" bringen, der örtliche Gouverneur stirbt vor Verlangen, Sie zu sehen. Keine dummen Streiche, bitte! Geben Sie Ihre Waffe ab und folgen Sie mir!";
			link.l1.go = "Fugitive_shore_2";
		break;
		
		case "Fugitive_shore_2":
			dialog.text = "Ich verstehe... Herr, bevor Sie vorschnell handeln, lassen Sie mich Ihnen etwas sagen. Ja, ich habe die Garnison verlassen. Aber ich hatte Gründe dafür. Ich kann nicht im Dienst bleiben, es ist mehr als ich ertragen kann! Verstehen Sie mich? Ich kann nicht!\nIch möchte ein friedliches Leben und ich habe ein solches Leben hier in diesem Dorf gefunden... Lassen Sie mich in Ruhe, sagen Sie ihnen, dass Sie mich nicht finden konnten oder dass ich mit Piraten in die offene See entkommen bin. Im Gegenzug gebe ich Ihnen meinen wöchentlichen Perlenertrag. Das ist alles, was ich habe.";
			link.l1 = "Denken Sie nicht einmal daran, mich zu bestechen! Übergeben Sie Ihre Waffe und folgen Sie mir!";
			link.l1.go = "Fugitive_city_fight";
			link.l2 = "Hmm... Du hast genug vom Militärdienst? Möchtest ein friedliches Leben? Nun, ich denke, ich kann deinen Wunsch wahr machen. Wo sind deine Perlen?";
			link.l2.go = "Fugitive_shore_gift";
		break;
		
		case "Fugitive_shore_gift":
			TakeNItems(pchar, "jewelry52", 100+hrand(40));
			TakeNItems(pchar, "jewelry53", 400+hrand(100));
			PlaySound("interface\important_item.wav");
			Log_Info("Du hast Perlen erhalten");
			dialog.text = "Hier... Und ich hoffe, dass ich weder Sie noch andere 'Gesandte' jemals wiedersehen werde.";
			link.l1 = "Ich versichere Ihnen, dass Sie es nicht werden. Auf Wiedersehen!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_tavern": // в таверне
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "Ehhh... hic! Herr, ich suche nicht nach Gesellschaft - besonders nicht nach Ihrer. Verschwinden Sie!";
			link.l1 = "Aber ich SUCHE deine Gesellschaft, "+pchar.GenQuest.FindFugitive.Name+"! Und du wirst meine Gesellschaft im Laderaum meines Schiffes dulden. Wir gehen zu  "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+", zum Stadtoberhaupt. Er kann es kaum erwarten, dich zu sehen.";
			link.l1.go = "Fugitive_tavern_1";
		break;
		
		case "Fugitive_tavern_1":
			dialog.text = "H-Hicks!"+RandSwear()+" Also hat er mich doch eingeholt! Hör zu, Kumpel, du weißt nicht, was passiert ist, du warst nicht da! Ich konnte nicht im Dienst bleiben, ich konnte einfach nicht! Ich betrinke mich immer noch jeden Abend, um das zu vergessen\nSchau, lass uns einen Deal machen. Sag ihm, dass du mich nicht finden konntest oder dass ich mit Piraten aufs offene Meer entkommen bin. Im Gegenzug gebe ich dir alle Nuggets, die ich in der örtlichen Höhle gefunden habe. Das ist alles, was ich habe, siehst du, ich gebe dir alles, nur um ihn nie wieder zu sehen "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+"...";
			link.l1 = "Denken Sie nicht einmal daran, mich zu bestechen! Übergeben Sie Ihre Waffe und folgen Sie mir!";
			link.l1.go = "Fugitive_tavern_fight";
			link.l2 = "Hmm... Eine unangenehme Geschichte? Quälen dich Albträume oder ein schuldiges Gewissen? Nun, ich denke, ich kann dich damit allein lassen. Wo sind deine Nuggets?";
			link.l2.go = "Fugitive_tavern_gift";
		break;
		
		case "Fugitive_tavern_gift":
			TakeNItems(pchar, "jewelry5", 50+hrand(30));
			TakeNItems(pchar, "jewelry6", 100+hrand(50));
			PlaySound("interface\important_item.wav");
			Log_Info("Du hast Nuggets erhalten");
			dialog.text = "Hier... Und ich hoffe wirklich, dass ich weder dich noch andere 'Gesandte' jemals wiedersehen werde.";
			link.l1 = "Ich versichere Ihnen, dass Sie es nicht werden. Auf Wiedersehen!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_tavern_fight":
			dialog.text = "Dann zieh dein Schwert, Söldner! Du wirst mich nicht so leicht bekommen!";
			link.l1 = "Gut, lass uns sehen, was du wert bist!";
			link.l1.go = "Fugitive_fight_2";
		break;
		
		case "Fugitive_fight_2":// в таверне
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetImmortal(npchar, false);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			Diag.currentnode = "Fugitive_afterfight";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
	}
}
