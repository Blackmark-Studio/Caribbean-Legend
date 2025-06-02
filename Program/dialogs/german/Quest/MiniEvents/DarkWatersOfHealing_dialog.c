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
			dialog.text = "Was wollt Ihr?";
			link.l1 = "Nichts.";
			link.l1.go = "exit";
		break;
		
		case "Tomas":
			dialog.text = ""+TimeGreeting()+"! Was führt Euch in mein Haus?";
			link.l1 = "Ich bin Kapitän "+GetFullName(pchar)+". Ich komme auf Bitte der Zigeunerin. Sie versteht nicht, warum Ihr ihre Hilfe abgelehnt habt und möchte den Grund wissen. Seid Ihr wirklich in der Lage, jede noch so kleine Hilfe auszuschlagen?";
			link.l1.go = "Tomas_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Tomas_1":
			dialog.text = "Oh, Kapitän... Versteht mich bitte, ich musste ablehnen, aber nicht aus freien Stücken. Glaubt mir, ich würde alles geben, damit Esther gesund wird.";
			link.l1 = "Was konnte Euch dazu bringen, eine so notwendige Hilfe abzulehnen?";
			link.l1.go = "Tomas_2";
		break;
		
		case "Tomas_2":
			dialog.text = "Seht Ihr, unsere Familie war stets fromm. Nach dem Tod meiner Frau Olivia ist mir nur der Glaube geblieben. Als die Zigeunerin ihre Hilfe anbot, stimmte ich zu – um meine Tochter zu retten. Doch... unser Pastor erfuhr davon.";
			link.l1 = "Lassen Sie mich raten: Er ist gegen solche Dienste?";
			link.l1.go = "Tomas_3";
		break;
		
		case "Tomas_3":
			dialog.text = "Genau. Er überzeugte mich, dass nur Gebete und Gottes Wille meine Tochter heilen können. Sollte ich diesen Weg verlassen und Hilfe einer 'Hexe' annehmen, drohte er mit Exkommunikation. Versteht Ihr? Exkommunikation!";
			link.l1 = "Also hängt Esthers Gesundheit nur vom Wort des Pastors ab?";
			link.l1.go = "Tomas_4";
		break;
		
		case "Tomas_4":
			dialog.text = "Meine Tochter und ich leben für die Kirche. Sie ist unser Ein und Alles. Wenn die Zigeunerin scheitert, verliere ich nicht nur meine Tochter, sondern auch meinen Platz in dieser Welt. Die Leute werden sich abwenden, die Kirche wird mich verstoßen. Esther und ich wären ganz allein.";
			link.l1 = "Und wenn der Pastor zustimmen würde? Würdet Ihr dann der Zigeunerin erlauben, es zu versuchen?";
			link.l1.go = "Tomas_5";
		break;
		
		case "Tomas_5":
			dialog.text = "Ja. Wenn die Kirche ihr Handeln segnen würde... Dann würde ich ihr vertrauen. Ich bin bereit, alles zu versuchen, was helfen kann.";
			link.l1 = "Verstanden. Gut, Thomas, ich werde Euch helfen. Ich spreche mit Eurem Pastor. Vielleicht kann ich ihn überzeugen.";
			link.l1.go = "Tomas_6";
		break;
		
		case "Tomas_6":
			dialog.text = "Ihr... Ihr wollt uns wirklich helfen? Kapitän, ich werde für Euren Erfolg beten. Aber bedenkt... unser Pastor ist ein sturer und prinzipientreuer Mann, ihn umzustimmen wird schwer.";
			link.l1 = "Prinzipien lassen sich durch gute Argumente überwinden. Wartet, ich kehre bald zurück.";
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
			link.l1 = "Thomas, ich konnte den Pastor überzeugen.";
			link.l1.go = "Tomas_12";
			DelLandQuestMark(npchar);
		break;
		
		case "Tomas_12":
			dialog.text = "Wirklich? Unglaublich! Dann lasst uns die Zigeunerin schnell holen.";
			link.l1 = "Natürlich holen wir sie, aber es gibt eine Bedingung. Der Pastor hofft, dass dies Euren Glauben nicht erschüttert, und erwartet aufrichtige Reue und gute Taten von Euch. Die erste könnte darin bestehen, der Gemeinde eine neue Glocke zu stiften.";
			link.l1.go = "Tomas_13";
		break;
		
		case "Tomas_13":
			dialog.text = "Oh, Kapitän... Eine Glocke kostet viel Geld. Vielleicht muss ich mich von Schmuckstücken meiner verstorbenen Frau trennen. Aber für Esther bin ich bereit, alles zu geben – sogar noch mehr. Natürlich werde ich den Herrn um Vergebung bitten. Ich werde den Schmied aufsuchen, eine Bestellung aufgeben und die Zigeunerin finden. Und Euch bitte ich, dem Pastor auszurichten, dass die Glocke bald da sein wird. Ich werde sie selbst aus der Erde graben, wenn nötig.";
			link.l1 = "Gut, Thomas.";
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
			link.l1 = "Ich habe dem Priester eure Worte übermittelt. Er wird euch nicht länger im Wege stehen, ihr könnt also beginnen.";
			link.l1.go = "Tomas_16";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_16":
			dialog.text = "Danke, Kapitän, für eure Beteiligung! Nehmt diese fünfzig Dublonen, das ist das Mindeste, was ich euch geben kann – mehr habe ich im Moment nicht...";
			link.l1 = "Aber nein! Ich habe euch nicht des Geldes wegen geholfen. Ist nun alles bereit für die... ähm... Behandlung?";
			link.l1.go = "Tomas_16_1";
			link.l2 = "Nun, wenn ihr darauf besteht... Kann ich sonst noch irgendwie helfen?";
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
			dialog.text = "Um den Trank zuzubereiten, der dem Kind die Gesundheit zurückgeben wird, brauche ich Mangarosa – eine seltene Pflanze, die an Orten wächst, wo Menschen selten hinkommen. Ich kenne eine Höhle außerhalb der Stadt, wo sich... zwielichtige Gestalten oft herumtreiben. Sie verschwenden Mangarosa zum Rauchen, ohne ihre Kraft zu verstehen. Hilf mir, "+GetSexPhrase("Falkenlein","Täubchen")+", besorg mir Mangarosa, ohne sie klappt gar nichts.";
			if (CheckAttribute(pchar, "questTemp.Mangarosa"))
			{
				link.l1 = "Mangarosa? Diese Pflanze ist mir bekannt.";
				link.l1.go = "gypsy_VD_manga_1";
			}
			else
			{
				link.l1 = "Wie sieht diese Pflanze aus?";
				link.l1.go = "gypsy_VD_no_manga";
			}
		break;

		case "gypsy_VD_no_manga":
			dialog.text = "Es ist ein ziemlich hoher Busch mit gezackten Blättern und einem angenehmen, berauschenden Duft. Du wirst ihn mit Sicherheit mit nichts anderem verwechseln.";
			link.l1 = "Gut, ich werde diese Mangarosa finden.";
			link.l1.go = "gypsy_2";
		break;

		case "gypsy_VD_manga_1":
			dialog.text = "Mischst du sie auch unter den Tabak?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "amelia")
			{
				link.l1 = "Nein, keineswegs! Es gibt eine Heilerin namens Amelia. Sie stellt aus dieser Pflanze Tränke her, die, ohne zu übertreiben, das Bewusstsein völlig verändern können.";
				link.l1.go = "gypsy_VD_manga_1_2";
			}
			else
			{
				link.l1 = "Nein, aber ich hatte schon einmal Mangarosa in den Händen.";
				link.l1.go = "gypsy_VD_manga_2";
			}
		break;

		case "gypsy_VD_manga_1_2":
			dialog.text = "Du kennst also Amelia? Na ja, "+GetSexPhrase("Falkenlein","Täubchen")+", bald machst du mir noch Konkurrenz. Aber jetzt ist nicht die Zeit, darüber zu sprechen. Geh, bring die Mangarosa, und ich werde alles Nötige vorbereiten.";
			link.l1 = "Ich gehe schon.";
			link.l1.go = "gypsy_2";
			AddCharacterExpToSkill(pchar, "Fortune", 200);
		break;

		case "gypsy_VD_manga_2":
			dialog.text = "Ich sehe, du bist kein gewöhnlicher, "+GetSexPhrase("Falkenlein","Täubchen")+". Dein Wissen ist umfangreich, dein Verstand scharf wie ein Messer! Du fürchtest dich nicht, ins Unbekannte zu treten, du strebst danach, alles zu verstehen, was vor anderen verborgen ist. Thomas hat Glück, dass du helfen wolltest. Geh jetzt, bring mir die Mangarosa, und ich werde das Mädchen heilen.";
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
			dialog.text = "Ha-ha. Ich sage dir, Mark, er ist ein Einfaltspinsel. Er schließt nicht einmal sein Haus ab.";
			link.l1 = "Und bist du sicher, dass seine Henne nicht im Haus herumlungern wird?";
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
			dialog.text = "Sieh mal, frischer Fisch ist hereingeschwommen! Komm schon, steh nicht wie ein Pfahl da. Leere deine Taschen, und zwar schnell, solange wir noch freundlich sind.";
			link.l1 = "Ruhig, ihr Banditen. Ich bin geschäftlich hier, "+sld.name+" hat mich geschickt. Ich brauche Mangarosa.";
			link.l1.go = "Bandit_4";

			locCameraSleep(false);
			locCameraFromToPos(3.39, 1.16, -1.80, true, 3.62, -0.50, 3.63);
			sld = CharacterFromID("DWH_Bandit_2");
			CharacterTurnToLoc(sld, "goto", "goto2");
		break;

		case "Bandit_4":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = ""+sld.name+" sagst du? Gut, wir haben Mangarosa. Gib uns zehn Goldstücke und sie gehört dir.";
			if (PCharDublonsTotal() >= 10)
			{
				link.l1 = "Hier.";
				link.l1.go = "Bandit_5";
			}
			link.l2 = "Geld? Wofür braucht ihr Geld? Ich verteile keine Almosen. Aber zwei Pfund Stahl zwischen die Rippen – das kann ich tun!";
			link.l2.go = "Bandit_7";
		break;

		case "Bandit_5":
			dialog.text = "Hier. Und vergiss nicht, du hast uns nie gesehen.";
			link.l1 = "Heh. Das hättest du mir nicht extra sagen müssen.";
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
				link.l1 = "Schau, "+npchar.name+", ist das die Pflanze, die du brauchst?";
				link.l1.go = "gypsy_4";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Hast du mitgebracht, worum ich dich gebeten habe?";
				link.l1 = "Noch nicht, aber ich bin dran.";
				link.l1.go = "exit";
				NextDiag.TempNode = "gypsy_3";
			}
		break;

		case "gypsy_4":
			dialog.text = "Ja, das ist sie. Jetzt habe ich alles und kann beginnen.";
			link.l1 = "...";
			link.l1.go = "gypsy_5";
			TakeItemFromCharacter(pchar, "cannabis7");
		break;

		case "gypsy_5":
			StartInstantDialog("DWH_Tomas", "Tomas_17", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
		break;

		case "Tomas_17":
			dialog.text = "Gehen wir schnell, verlieren wir keine Zeit.";
			link.l1 = "...";
			link.l1.go = "Tomas_18";
			CharacterTurnByChr(npchar, CharacterFromID("DWH_gypsy"));
		break;

		case "Tomas_18":
			dialog.text = "Kapitän, wenn es Ihnen nichts ausmacht, sehen wir uns später. Jetzt steht uns der wichtigste Teil... der Behandlung bevor.";
			link.l1 = "Natürlich, Thomas. Ich hoffe, Ihre Tochter wird bald gesund.";
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
			link.l1 = ""+npchar.name+", Thomas hat dich nicht aus eigenem Willen fortgeschickt. Der Priester drohte ihm mit dem Kirchenbann, wenn er deine Hilfe annehmen würde.";
			link.l1.go = "gypsy_7";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_7":
			dialog.text = "Ich habe gleich gemerkt, "+GetSexPhrase("liebling","schönheit")+", dass er mir die Absage mit schwerem Herzen erteilt hat.";
			link.l1 = "Gibt es eine Möglichkeit, ihm zu helfen, ohne dass die Kirche es bemerkt?";
			link.l1.go = "gypsy_8";
		break;

		case "gypsy_8":
			dialog.text = "Ach, "+GetSexPhrase("liebling","schönheit")+", die Sache ist nicht einfach, aber die Wege kenne ich, ich weiß, was zu tun ist. Nur ohne deine Hilfe geht es nicht, das verstehst du doch.";
			link.l1 = "Natürlich kannst du auf mich zählen.";
			link.l1.go = "gypsy_10";
			link.l2 = "Es tut mir leid, Schwarzbraue, aber ich habe absolut keine Zeit, mich damit zu beschäftigen. Ich habe alles getan, was ich konnte. Jetzt muss ich mich um meine eigenen Angelegenheiten kümmern.";
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
			dialog.text = "Dann brauche ich Folgendes: einen Gegenstand, der dem Mädchen gehört, zwei Stängel Stechapfel, ein Stängel Ipecacuanha und einen Stängel Eisenkraut. Wenn du mir all das bringst, kann ich ein Heilmittel für sie zubereiten.";
			link.l1 = "Gut, ich werde alles besorgen, was nötig ist.";
			link.l1.go = "gypsy_11";
		break;

		case "gypsy_11":
			DialogExit();
			AddQuestRecord("DWH", "7");

			LAi_CharacterDisableDialog(npchar);

			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\\MiniEvents\\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_21";
			AddLandQuestMark(sld, "questmarkmain");
		break;

		case "Tomas_21":
			dialog.text = "...";
			link.l1 = "Thomas, leider hat der Priester nicht auf meine Worte gehört. Aber die Zigeunerin und ich können Ihnen helfen. Ich brauche...";
			link.l1.go = "Tomas_22";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_22":
			dialog.text = "Schlagen Sie vor, dass ich mich gegen die Kirche stelle?";
			link.l1 = "Wir werden alles still und leise machen, niemand wird etwas erfahren. Bald wird Ihre Tochter das Leben wieder genießen und frei durch die Stadt spazieren können, wie es sich für eine junge Dame gehört.";
			link.l1.go = "Tomas_23";
			link.l2 = "Verdammt noch mal, Thomas Morrison, wollen Sie, dass Ihre Tochter gesund wird, oder verstecken Sie sich nur hinter schönen Worten?";
			link.l2.go = "Tomas_24";
		break;

		case "Tomas_23":
			dialog.text = "In Ordnung, ich stimme zu. Aber bitte, handeln Sie vorsichtig. Ich möchte keine unnötigen Gerüchte und Probleme.";
			link.l1 = "Selbstverständlich. Also, ich brauche einen persönlichen Gegenstand Ihrer Tochter. Etwas, woran sie hängt.";
			link.l1.go = "Tomas_25";
			AddCharacterExpToSkill(pchar, "Sneak", 200);
		break;

		case "Tomas_24":
			dialog.text = "In Ordnung, ich stimme zu. Aber bitte, handeln Sie vorsichtig. Ich möchte keine unnötigen Gerüchte und Probleme.";
			link.l1 = "Selbstverständlich. Also, ich brauche einen persönlichen Gegenstand Ihrer Tochter. Etwas, woran sie hängt.";
			link.l1.go = "Tomas_25";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "Tomas_25":
			dialog.text = "Hmm... Ja! Ich weiß, was passen wird. Warten Sie hier, ich bin sofort zurück.";
			link.l1 = "Ich warte...";
			link.l1.go = "Tomas_26";
		break;

		case "Tomas_26":
			DialogExit();
			SetLaunchFrameFormParam("Einige Minuten später...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("DWH_TomasGovotitAgain", 0.0);
			LaunchFrameForm();
		break;

		case "Tomas_27":
			dialog.text = "Hier. Das sind Jadeperlen. Esther hat sie nie abgenommen, sie sind ihr sehr lieb.";
			link.l1 = "Ausgezeichnet. Jetzt müssen Sie nur noch warten. Bis bald, Thomas.";
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
			dialog.text = "Hast du gebracht, worum ich dich gebeten habe?";
			if (GetCharacterItem(pchar, "cannabis1") >= 2 && GetCharacterItem(pchar, "cannabis4") >= 1 && GetCharacterItem(pchar, "cannabis3") >= 1)
			{
				link.l1 = "Ich habe alles besorgt, was nötig ist.";
				link.l1.go = "gypsy_22";
			}
			link.l2 = "Erinnere mich, was ich bringen soll.";
			link.l2.go = "gypsy_napomni";
		break;

		case "gypsy_napomni":
			dialog.text = "Dann brauche ich Folgendes: einen Gegenstand, der dem Mädchen gehört, zwei Stängel Stechapfel, ein Stängel Ipecacuanha und einen Stängel Eisenkraut. Wenn du mir all das bringst, kann ich ein Heilmittel für sie zubereiten.";
			link.l1 = "Gut, ich werde alles besorgen, was nötig ist.";
			link.l1.go = "gypsy_napomni_2";
		break;

		case "gypsy_napomni_2":
			DialogExit();
			NextDiag.TempNode = "gypsy_21";
		break;

		case "gypsy_22":
			dialog.text = "Ausgezeichnet. Jetzt kann ich einen Heiltrank für das Mädchen zubereiten. Er wird frühestens morgen früh fertig sein. Du kannst mich wie üblich auf den Straßen der Stadt finden.";
			link.l1 = "Gut, bis dann.";
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
			link.l1 = "Nun, "+npchar.name+", ist dein Trank fertig?";
			link.l1.go = "gypsy_32";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_32":
			dialog.text = "Da ist es, "+GetSexPhrase("liebling","schönheit")+". Das Mädchen soll diese Perlen anlegen und den Inhalt des Fläschchens bis zum Grund austrinken. In spätestens einem Monat wird sie vollständig gesund sein.";
			link.l1 = "Ich bringe es sofort zu Thomas. Leb wohl, Schwarzbraue.";
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
				link.l1 = "Thomas, alles ist bereit. Esther soll diese Perlen anlegen und das Fläschchen mit dem Trank in einem Zug leeren.";
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
			dialog.text = "Vielen Dank, "+pchar.name+"! Bitte verzeiht mir, ich möchte keine Minute verlieren...";
			link.l1 = "Natürlich, natürlich.";
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
			dialog.text = "Seid gegrüßt, "+pchar.name+"! Meine Esther ist genesen! Sie ist vollständig gesund und jetzt in der Kirche, wo sie unserem Herrn Gott dankt, dass er uns Euch und die Zigeunerin geschickt hat!";
			link.l1 = "Thomas, ich bin erfreut, dass alles geklappt hat! Kümmern Sie sich gut um das Mädchen, sie hat jetzt ein langes und glückliches Leben vor sich.";
			link.l1.go = "Tomas_42";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_42":
			dialog.text = "Nehmt diese dreihundert Dublonen. Leider kann ich nicht mehr anbieten, da ich mich verschulden musste, um diese Summe zusammenzubringen. Aber wisst, dass keine Worte und kein Gold die Dankbarkeit ausdrücken können, die ich Euch gegenüber empfinde, Kapitän. Ihr habt mich nicht nur von der Angst um ihr Leben befreit, sondern auch unserer Familie Hoffnung für die Zukunft gegeben. Ich werde immer in Eurer Schuld stehen!";
			link.l1 = "Danke! Dreihundert Dublonen sind recht großzügig, also seien Sie unbesorgt – Sie haben mir mehr als genug gedankt!";
			link.l1.go = "Tomas_43";
			link.l2 = "Ich werde Euer Geld nicht nehmen, Thomas. Denkt nicht einmal daran, zu bestehen! Kauft der jungen Esther lieber ein schönes Kleid, sie verdient es.";
			link.l2.go = "Tomas_46";
		break;

		case "Tomas_43":
			dialog.text = ""+pchar.name+", besucht uns jederzeit. Ihr werdet in unserem Haus immer willkommen sein. Und sprecht auch mit der Zigeunerin, sie wollte Euch sehen.";
			link.l1 = "Ich betrachte es als eine Ehre! Nun muss ich mich verabschieden – die Gezeiten warten auf keinen Kapitän.";
			link.l1.go = "Tomas_44";
			AddItems(pchar, "gold_dublon", 300);
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;

		case "Tomas_44":
			dialog.text = "Natürlich, natürlich. Möge Gott mit Euch sein, "+GetFullName(pchar)+"!";
			link.l1 = "Auf Wiedersehen.";
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
			dialog.text = "Ihr seid ein äußerst edler Mensch, "+GetFullName(pchar)+"! Möge die Jungfrau Maria mit Euch sein! Besucht uns, Ihr seid in unserem Haus stets ein willkommener Gast. Und "+pchar.name+", sprecht auch mit der Zigeunerin, sie wollte Euch sehen.";
			link.l1 = "Ganz gewiss! Jetzt muss ich fort – die See ruft.";
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

			AddSimpleRumourCity("Habt Ihr gehört? "+GetFullName(pchar)+" hat für die Tochter von Thomas Morrison ein Heilmittel beschafft, das das arme Mädchen auf wundersame Weise geheilt hat!", "SentJons", 10, 1, "");
			AddSimpleRumourCity("Thomas Morrison zündet täglich eine Kerze in der Pfarrei für die Gesundheit von "+GetFullName(pchar)+" an. Man sagt, er hat seine Tochter vor einer langwierigen Krankheit gerettet.", "SentJons", 10, 1, "");
			AddSimpleRumourCity("Esther Morrison ist vor unseren Augen aufgeblüht. Als ob sie nie krank gewesen wäre. Niemand kann wirklich erklären, was die Krankheit zum Rückzug gezwungen hat.", "SentJons", 10, 1, "");
		break;

		case "gypsy_41":
			dialog.text = "Da bist du ja, "+GetSexPhrase("Falkenlein","Täubchen")+"! Ich wusste, dass du wiederkommen würdest. Dank deiner Bemühungen hat sich das Mädchen erholt und flattert nun wie eine Taube. Die ganze Stadt bewundert sie.";
			link.l1 = "Nun, Schwarzbraue, es war nicht nur mein Verdienst – gib mir nicht zu viel Anerkennung. Es war dein Sud, der ihr zur Gesundheit verholfen hat, also verleugne deinen Anteil nicht.";
			link.l1.go = "gypsy_42";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_42":
			dialog.text = "Du hast ein gutes Herz, "+GetSexPhrase("Falkenlein","Täubchen")+", und einen scharfen Verstand! Du bist für Großes bestimmt – das ist meine Prophezeiung.";
			link.l1 = "Heh... nun, danke, "+npchar.name+".";
			link.l1.go = "gypsy_43";
		break;

		case "gypsy_43":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("DWH", "9");
			CloseQuestHeader("DWH");
		break;

		case "gypsy_44":
			dialog.text = "Da bist du ja, "+GetSexPhrase("Falkenlein","Täubchen")+"! Ich wusste, dass du hier wieder auftauchen würdest. Dank deiner Bemühungen hat sich das Mädchen erholt und flattert nun wie eine Taube. Die ganze Stadt bewundert sie.";
			link.l1 = "Nun, nun, du hast das Mädchen selbst gerettet, und du willst, dass ich alle Lorbeeren ernte? So geht das nicht! Du hast den Trank zubereitet, du hast sie wieder auf die Beine gebracht, du solltest den Ruhm dafür erhalten.";
			link.l1.go = "gypsy_45";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_45":
			dialog.text = "Du hast ein gutes Herz, "+GetSexPhrase("Falkenlein","Täubchen")+", und eine edle Seele. Ich habe ein Geschenk für dich – eines, das jeder Kapitän zu schätzen wüsste. Hier. Jetzt werden die Ratten auf deinem Schiff weder Glück noch Ruhe haben!";
			link.l1 = "Ein Geschenk für mich? Bei den Sternen, wie unerwartet!";
			link.l1.go = "gypsy_46";
			GiveItem2Character(PChar, "rat_poison");
		break;
		
		case "gypsy_46":
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				dialog.text = "Deine Seele ist rein, ich sehe, dass du Mangarosa nicht für momentane Freude verbrennen wirst. Wenn du sie dringend brauchst, komm zu mir, "+GetSexPhrase("Falkenlein","Täubchen")+". Fünf Stängel kosten dich zweihundert Dublonen.\nDieses Kraut ist launisch, du weißt es selbst, nicht jeder kann es finden. Also dränge mich nicht – frage nicht öfter als einmal im Monat, ich werde es sowieso nicht früher beschaffen können.";
			}
			else
			{
				dialog.text = "Deine Seele ist hell, ich sehe, du bist nicht dumm, du verstehst dich auf Kräuter nicht schlechter als manche Heilerinnen. Du kannst vieles finden, obwohl das Glück nicht immer lächelt. Es gibt eine seltene Pflanze, die nicht jeder finden kann. Sie heißt Mangarosa. Wenn du es brauchst, komm zu mir, "+GetSexPhrase("Falkenlein","Täubchen")+". Ich werde fünf Stängel besorgen, aber ich werde sie nicht umsonst geben – zweihundert Dublonen nehme ich.\nAber dieses Kraut ist eigenwillig, also dränge mich nicht. Frage nicht öfter als einmal im Monat – selbst wenn du alle Schicksalskarten auslegst, werde ich es nicht früher beschaffen.";
			}
			link.l1 = "Nun, danke dir, "+npchar.name+".";
			link.l1.go = "gypsy_47";
		break;

		case "gypsy_47":
			DialogExit();
			NextDiag.CurrentNode = "gypsy_Mangarosa";

			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("DWH", "10");
			CloseQuestHeader("DWH");
			AddQuestRecordInfo("Useful_Acquaintances", "1");

			SetTimerFunction("DWH_Mangarosa", 0, 0, 30);
		break;

		case "Tomas_51":
			dialog.text = "Kapitän, ich denke die ganze Zeit – es muss der Herr selbst gewesen sein, der Euch zur rechten Zeit hierher geführt hat! Ihr habt meine Tochter gerettet, und ich werde das nie vergessen.";
			link.l1 = "Vielleicht, Thomas. Die Wege des Herrn sind unergründlich.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tomas_52";
			SetTimerFunction("DWH_Tomas_HelloAgain", 0, 0, 1);
		break;

		case "Tomas_52":
			dialog.text = "Möchten Sie etwas Wein, Kapitän? Ich habe etwas Besonderes für liebe Gäste.";
			link.l1 = "Danke, Thomas, aber leider muss ich gehen.";
			link.l1.go = "exit";
		break;

		case "gypsy_Mangarosa":
			dialog.text = "Was brauchst du, mein Falke?";
			if (CheckAttribute(pchar, "questTemp.DWH_Mangarosa"))
			{
				link.l1 = "Sag mir, Schwarzbraue, hättest du Mangarosa für mich?";
				link.l1.go = "gypsy_Mangarosa_1";
			}
			link.l2 = "Ich wollte nur Hallo sagen. Ich muss weiter!";
			link.l2.go = "exit";
			NextDiag.TempNode = "gypsy_Mangarosa";
		break;

		case "gypsy_Mangarosa_1":
			dialog.text = "Wer, wenn nicht ich, "+GetSexPhrase("liebling","schönheit")+", würde dir so eine Rarität besorgen? Zweihundert Dublonen – und sie gehört dir, fünf Stängel, nicht mehr, nicht weniger.";
			if (PCharDublonsTotal() >= 300)
			{
				link.l1 = "Hier, nimm deine Dublonen.";
				link.l1.go = "gypsy_Mangarosa_2";
			}
			link.l2 = "Verdammt. Ich habe nicht genug Geld. Ich komme später zurück.";
			link.l2.go = "exit";
			NextDiag.TempNode = "gypsy_Mangarosa";
		break;

		case "gypsy_Mangarosa_2":
			dialog.text = "So ist’s besser, "+GetSexPhrase("Falkenlein","Täubchen")+". Nimm sie. Und pass auf, verschwende sie nicht unnötig, du weißt selbst – Mangarosa ist kein gewöhnliches Kraut, in ihr ist eine Kraft verborgen, die nicht jeder bewältigen kann.";
			link.l1 = "Keine Sorge, Schwarzbraue, ich werde eine würdige Verwendung für ihre Kraft finden.";
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