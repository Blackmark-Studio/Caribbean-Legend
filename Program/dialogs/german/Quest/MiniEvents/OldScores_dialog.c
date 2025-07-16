void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk1, bOk2;
	
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

		case "OS_Matros_sluh":
			bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
			bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
			if (bOk1 || bOk2)
			{
				dialog.text = "Man sagt, gestern gab es eine Schlägerei in der Taverne... Aber wer gekämpft hat — keine Ahnung. Mein Gesicht ist zumindest noch heil. Glaube ich.";
				link.l1 = "Sieht aus, als hätte es hier eine ordentliche Sauforgie gegeben?";
				link.l1.go = "OS_Matros_sluh_2";
				
			}
			else
			{
				switch (rand(2))
				{
					case 0:
						dialog.text = "He, "+GetSexPhrase("Kumpel","Mädel")+", hast du irgendwo meinen Stiefel gesehen? Ein räudiger Dieb ist damit abgehauen, während ich unter dem Tavernen-Tisch bewusstlos war.";
						link.l1 = "Halt besser die Augen offen, sonst folgt der andere demselben Weg.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;

					case 1:
						dialog.text = "Man sagt, es gab gestern eine Schlägerei in der Taverne... Obwohl, wer kämpfte, ist schwer zu sagen. Mein Gesicht scheint intakt zu sein. Glaube ich.";
						link.l1 = "Vielleicht dachten sie, dass dein Gesicht bereits genug Schaden erlitten hatte.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;

					case 2:
						dialog.text = "Bei allen Teufeln der Tiefe, ich hatte gestern einen Beutel voller Gold! Wo zum Teufel ist er jetzt?!";
						link.l1 = "Für einen wahren Piraten ist Gold nicht der wichtigste Preis. Freiheit hat einen viel größeren Wert.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;
				}
			}
		break;
		
		case "OS_Matros_sluh_2":
			dialog.text = "Und ob! Der Wirt hatte ordentlich zu tun... hicks... Und dann... hat man ihm auch noch den Gin geklaut! Nicht nur eine Flasche, nein, ein ganzes Fass! Und so ein besonderes, dass man in der ganzen Karibik kein zweites findet! Man sagt, es wurde direkt aus Europa gebracht. Für wen der alte Schlitzohr es aufbewahrte, sagt er nicht, aber eines ist klar: Wenn das Fass nicht bald gefunden wird, wird der arme Kerl vom Teufel höchstpersönlich geholt!";
			link.l1 = "Interessant. Na dann, mach’s gut, alter Säufer.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OS_Matros_sluh";
			
			SetQuestHeader("OS");
			AddQuestRecord("OS", "1");
			pchar.questTemp.OS_Start = true;
			pchar.questTemp.OS_Tavern_1 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_tavernkeeper"), "questmarkmain");
		break;

		case "OS_Matros_again":
			switch (rand(2))
			{
				case 0:
					dialog.text = "Was willst du noch? Siehst du nicht, mein Schädel platzt gleich?! Verschwinde.";
					link.l1 = "Weniger saufen, dann siehst du vielleicht wieder wie ein Mensch aus.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "Lass mich in Ruhe... Mein Kopf platzt gleich!";
					link.l1 = "Erstaunlich, dass er überhaupt noch auf deinen Schultern sitzt.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 2:
					dialog.text = "Verflucht noch mal... Lass mich in Ruhe, siehst du nicht, dass ich keine Zeit für dich habe!";
					link.l1 = "...";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
		break;
		
		case "OS_Matros":
			dialog.text = "Lass mich in Ruhe! Siehst du nicht, dass ich am Limit bin? Meine Fäuste jucken schon, jemandem eins aufs Maul zu geben.";
			link.l1 = "Nur ruhig, Freundchen. Ich will nur wissen, was gestern in der Taverne los war.";
			link.l1.go = "OS_Matros_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Matros_2":
			dialog.text = "Caramba! Bist du etwa "+GetSexPhrase("noch so ein Liebhaber","eine Verwandte")+" von dieser verrückten Kellnerin? Was willst du, etwa vom Sturm hinweggefegt werden? Fordere mich zum Duell? Oder ziehst du gleich die Klinge?";
			if (pchar.sex == "woman")
			{
				link.l1 = "Verwandte? Wohl kaum. Aber du scheinst kein besonders hohes Bild von ihr zu haben, was?";
				link.l1.go = "OS_Matros_3_scrit";
			}
			else
			{
				link.l1 = "Liebhaber? Kaum. Sie scheint eher auf Quantität als auf Qualität zu setzen, was?";
				link.l1.go = "OS_Matros_3_scrit";
				link.l2 = "Mich interessieren ihre Eskapaden nicht. Sag einfach, was passiert ist, und ich bin weg. Du hast sie doch in Rage versetzt, oder?";
				link.l2.go = "OS_Matros_3_fortuna";
			}
		break;

		case "OS_Matros_3_scrit":
			dialog.text = "Diese Furie hat die Auswahl eines ausgehungerten Matrosen – nimm, was gerade da ist! Den ganzen Abend hat sie mir schöne Augen gemacht und geflirtet wie eine Katze am Kombüsenfenster. Aber kaum bin ich näher herangeschlichen – hat sie so geschrien, dass die Fische in der Bucht abgetaucht sind!";
			link.l1 = "Vielleicht hattest du zu viel getrunken und warst ein bisschen zu aufdringlich?";
			link.l1.go = "OS_Matros_4";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "OS_Matros_3_fortuna":
			dialog.text = "Diese Furie hat die Auswahl eines ausgehungerten Matrosen – nimm, was gerade da ist! Den ganzen Abend hat sie mir schöne Augen gemacht und geflirtet wie eine Katze am Kombüsenfenster. Aber kaum bin ich näher herangeschlichen – hat sie so geschrien, dass die Fische in der Bucht abgetaucht sind!";
			link.l1 = "Vielleicht hattest du zu viel getrunken und warst ein bisschen zu aufdringlich?";
			link.l1.go = "OS_Matros_4";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "OS_Matros_4":
			dialog.text = "Ich war vielleicht betrunken, aber ich erinnere mich ganz genau an alles. Ich war nicht hinter ihr her – sie ist auf mich losgegangen wie ein Hai auf ein Stück Fleisch. Den ganzen Tag ist sie um mich herumgeschlichen!";
			if (pchar.sex == "woman")
			{
				link.l1 = "Und wegen so einer Kleinigkeit willst du gleich den Erstbesten verprügeln? Oder ist an dem Abend noch etwas passiert?";
			}
			else
			{
				link.l1 = "Hör mal, du hast 'noch so ein Liebhaber' gesagt. Weißt du etwas über ihre anderen Beziehungen?";
			}
			link.l1.go = "OS_Matros_5";
		break;
		
		case "OS_Matros_5":
			dialog.text = "Nachdem ihr Geschrei abgeklungen war, meinten die Jungs aus meiner Crew, dass ich besser nicht versucht hätte, in ihrer Bucht den Anker zu werfen. Anscheinend hat sie einen Verehrer in der Stadt, der mit unserem Käpt’n unter einer Decke steckt.";
			link.l1 = "Interessant. Ist dir sonst nichts Verdächtiges aufgefallen? Hat sich vielleicht jemand dem Tresen genähert während des Streits?";
			link.l1.go = "OS_Matros_6";
		break;

		case "OS_Matros_6":
			dialog.text = "Zum Teufel... Mein Schädel platzt gleich, und du kommst mit deinen Fragen. Ich habe nichts gesehen und nichts gehört. Gib mir lieber ein paar Pesos, als mich mit deinem Verhör zu quälen, Seewolf hin oder her.";
			if (sti(pchar.Money) >= 100)
			{
				link.l1 = "Hier, nimm hundert Pesos. Aber sauf dich nicht gleich wieder so zu, dass du der Kellnerin erneut ins Netz gehst, heh.";
				link.l1.go = "OS_Matros_7_harizma";
			}
			link.l2 = "Vergiss es. Sonst besäufst du dich wieder und hängst der Kellnerin erneut an den Fersen.";
			link.l2.go = "OS_Matros_7_fortuna";
		break;
		
		case "OS_Matros_7_harizma":
			DialogExit();
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddQuestRecord("OS", "3");
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.OS_Tavern_2 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_waitress"), "questmarkmain");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
					sld.dialog.currentnode = "OS_Matros_again";
				}
			}
		break;
		
		case "OS_Matros_7_fortuna":
			DialogExit();
			
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddQuestRecord("OS", "3");
			pchar.questTemp.OS_Tavern_2 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_waitress"), "questmarkmain");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
					sld.dialog.currentnode = "OS_Matros_again";
				}
			}
		break;
		
		case "OS_Dialog_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "He, Jack! Du hast dir da eine Hafennutte angelacht! Ha-ha! Schau sie dir an – ganz schön scharf, das Luder! Ich frag mich, hat sie schon alle Truhen durchsucht, oder haben wir sie mitten im besten Moment erwischt?";
				link.l1 = "...";
			}
			else
			{
				dialog.text = "He, Jack! Da ist ’ne Ratte bei dir! Ha-ha! Sieh ihn dir an, dieser Halunke! Hat sich wohl schon durch unsere Kisten gewühlt, was, du Gauner?";
				link.l1 = "...";
			}
			link.l1.go = "OS_Dialog_2";
		break;

		case "OS_Dialog_2":
			StartInstantDialog("OS_Jack", "OS_Dialog_3", "Quest\MiniEvents\OldScores_dialog.c");
		break;

		case "OS_Dialog_3":
			if (pchar.sex == "woman")
			{
				dialog.text = "Mutiges kleines Ding. Ins Versteck von Jack Veils zu schleichen – darauf muss man erst mal kommen. Also, was willst du hier, Süße? Willst du uns etwa unterhalten?";
				link.l1 = "Unterhalten? Ha! Ihr seid ja richtige Träumer, meine Herren. Ich bin hier, um mir zurückzuholen, was ihr gestohlen habt. Oder dachtet ihr ernsthaft, dass euer armseliges Theater unbemerkt bleibt?";
			}
			else
			{
				dialog.text = "Mutiger Wurm. In das Haus von Jack Veils einzubrechen – das machen nicht viele. Was willst du hier?";
				link.l1 = "Sagen wir einfach, ich hole zurück, was gestohlen wurde. Oder dachtet ihr wirklich, euer lächerliches Schauspiel würde unentdeckt bleiben?";
			}
			link.l1.go = "OS_Dialog_4";
		break;

		case "OS_Dialog_4":
			StartInstantDialog("OS_capWolf", "OS_Dialog_5", "Quest\MiniEvents\OldScores_dialog.c");
		break;

		case "OS_Dialog_5":
			if (pchar.sex == "woman")
			{
				dialog.text = "Armseliges Theater?! Bei allen Teufeln, ich werde dir die Haut abziehen und sie als Segel benutzen! Ha-ha! Oder vielleicht sollten wir vorher noch ein wenig... spielen?";
				link.l1 = "Ich sehe, ihr seid begierig, in die Hölle zu fahren? Gut, ich will euch nicht länger warten lassen – auf zum Kampf, ihr dreckigen Bastarde!";
			}
			else
			{
				dialog.text = "Lächerliche Show? Möge ich in der Hölle brennen, ich zieh dir gleich die Haut ab und mach ein Segel daraus! Genug geredet – jetzt ist Schluss, du Mistkerl!";
				link.l1 = "Wenn ihr es so wollt – dann los, ihr Halunken!";
			}
			link.l1.go = "OS_Dialog_bitva";
		break;
		
		case "OS_Dialog_bitva":
			DialogExit();
			
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("OS_Jack");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("OS_capWolf");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "OS_VernuliBochonok");
		break;
		
		case "Zaharia_1":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = ""+sld.name+", wo ist mein Gin?! Wenn du ihn nicht hast, werde ich dich eigenhändig zu den Fischen schicken!";
			link.l1 = "...";
			link.l1.go = "Zaharia_2";
			CharacterTurnByChr(npchar, sld);
			//locCameraFromToPos(-2.53, 2.00, 1.26, false, 0.03, 0.00, -1.11);
		break;

		case "Zaharia_2":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = "...";
			link.l1 = "Ich habe ihn gerade selbst geliefert"+GetSexPhrase("","e")+". Hier ist er.";
			link.l1.go = "Zaharia_3";
			CharacterTurnByChr(npchar, pchar);
			TakeItemFromCharacter(pchar, "cask_gin");
			notification("Ihr habt das Fass Gin abgegeben", "NONE");
		break;

		case "Zaharia_3":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = "Gut, dass ich mich in dir nicht getäuscht habe, "+sld.name+". Komm morgen zu mir – dann bekommst du deine Dublonen.";
			link.l1 = "...";
			link.l1.go = "Zaharia_4";
			CharacterTurnByChr(npchar, sld);
		break;

		case "Zaharia_4":
			DialogExit();

			//ChangeShowIntarface();
			LAi_SetStayType(pchar);

			sld = CharacterFromID("OS_Zaharia");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.lifeday = 0;
			sld.location = "None";

			DoQuestFunctionDelay("OS_RazgovorTavern", 1.5);
		break;

		case "Tavern_1":
			dialog.text = "Kapitän, wegen der Plakette...";
			link.l1 = "Welche Plakette? Ah, die da... Ich denke, ich brauche keine solchen Ehren. Bemüht euch nicht, ich komme auch ohne klar.";
			link.l1.go = "Tavern_2";
		break;

		case "Tavern_2":
			dialog.text = "Ich kann Euch etwas Besseres anbieten! Ab sofort habt Ihr in meiner Taverne stets ein freies Bett und Getränke aufs Haus! Ein Mensch wie Ihr verdient das auf jeden Fall!";
			link.l1 = "Jetzt sprechen wir die gleiche Sprache! Solche Privilegien gefallen mir! Bis bald, "+npchar.name+".";
			link.l1.go = "Tavern_3";
		break;
		
		case "Tavern_3":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			AddQuestRecord("OS", "5");
			AddQuestUserData("OS", "sSex", GetSexPhrase("","а"));
			pchar.questTemp.OS_Tavern_FreeBuhlo = true;
			ChangeShowIntarface();
			
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			sld.dialog.filename = "Common_Tavern.c";
			sld.dialog.currentnode = "First Time";
			LAi_SetBarmanType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.lifeday = 0;
				}
			}
			
			PChar.quest.OS_AttackSea.win_condition.l1 = "location";
			PChar.quest.OS_AttackSea.win_condition.l1.location = "Cuba1";
			PChar.quest.OS_AttackSea.function = "OS_AttackSea";
			
			// вражеский корабль атакует в море
			sld = CharacterFromID("OS_Pirate");
			DeleteAttribute(sld, "AlwaysFriend");
			DeleteAttribute(sld, "ShipEnemyDisable");
			sld.AlwaysEnemy = true;
			LAi_SetImmortal(sld, false);
			
			PChar.quest.TPZ_Potopil.win_condition.l1 = "NPC_Death";
			PChar.quest.TPZ_Potopil.win_condition.l1.character = "OS_Pirate";
			PChar.quest.TPZ_Potopil.function = "OS_Pobeda";
		break;
		
		
		
		
		
		
		
	}
}