// Бесчестный конкурент
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Das ist ein Fehler. Informieren Sie die Entwickler";
			link.l1 = "Sicher!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "ShadowGuarder":
			dialog.text = "Was brauchen Sie?";
			link.l1 = "Bist du "+pchar.questTemp.Shadowtrader.Guardername+"? Der örtliche Kaufmann hat mich geschickt. Er erwartet Ihre Anwesenheit in diesem Moment ungeduldig.";
			link.l1.go = "ShadowGuarder_1";
			DelLandQuestMark(npchar);
		break;
	
		case "ShadowGuarder_1":
			dialog.text = "A-ah, aber ich habe hier auf ihn gewartet! Mir wurde gesagt, dass er in eine Taverne kommen würde! Entschuldigung, ich bin sofort auf dem Weg.";
			link.l1 = "Sehr gut!";
			link.l1.go = "ShadowGuarder_2";
		break;
	
		case "ShadowGuarder_2":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = characterFromId("ShadowGuarder");	
			LAi_SetStayType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", pchar.questTemp.Shadowtrader.City +"_store", "goto", "goto2", "OpenTheDoors", 6);
			pchar.questTemp.Shadowtrader = "begin";
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
	
		case "ShadowAgent":
			dialog.text = "Guten Abend, Kapitän. Möchten Sie einige günstige Waren, heh? Folgen Sie mir!";
			link.l1 = "Führe an.";
			link.l1.go = "ShadowAgent_1";
		break;
	
		case "ShadowAgent_1":
			DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseS4", "CommonFlamHouse", "barmen", "stay", "Shadow_inRoom", 40);
		break;
	
		case "ShadowTrader":
			dialog.text = "Guten Abend, Herr. Es ist gut, einen neuen Kunden zu treffen, ha! Lassen Sie mich mich vorstellen: Ich bin "+GetFullName(npchar)+". Ich habe die billigsten Waren in dieser Stadt, das versichere ich Ihnen.";
			link.l1 = "Endlich haben wir uns getroffen..."+npchar.name+". Ich vermute, ich werde Sie enttäuschen: Ich habe Sie nicht zum Handeln gesucht, sondern um Ihr schmutziges Geschäft zu beenden. Sie sind ein großes Ärgernis für einen wichtigen Mann gewesen. Das Ärgernis ist so groß geworden, dass er darauf brennt, Sie auszuschalten... mit allen notwendigen Mitteln.";
			link.l1.go = "ShadowTrader_1";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l2 = "Halt, du kriminelles Gesindel! Wusstest du nicht, dass du Steuern zahlen musst, um ein kommerzielles Geschäft zu betreiben? Niemand bricht das Gesetz unter meiner Aufsicht!"+GetFullName(npchar)+", Sie haben das Gesetz verletzt und Ihre gestohlenen Waren sind nun verwirkt! Draußen vor der Tür stehen bewaffnete Soldaten direkt hinter mir, also versuchen Sie nicht einmal, dumm zu spielen!";
				link.l2.go = "ShadowTrader_2";
			}
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
	
		case "ShadowTrader_1":
			dialog.text = "Wirklich? Das habe ich nicht erwartet... Wer zum Teufel bist du?! Das ist eine Falle! Ich glaube, ich weiß, wer dafür verantwortlich ist! Mit allen Mitteln... Jungs, tötet ihn!";
			link.l1 = "Lass uns tanzen, Schurke!";
			link.l1.go = "ShadowTrader_fight";
			NextDiag.currentnode = "ShadowTrader_6";
		break;
	
	case "ShadowTrader_2":
		dialog.text = "Oh Gott... Offizier, hören Sie! Lassen Sie uns einen Handel eingehen. Sie sind ein weiser und barmherziger Mann! Ich zahle Ihnen 5000 Achtelstücke und Sie lassen uns durch den zweiten Stock fliehen. Sie nehmen auch die Waren, Sie brauchen sie, richtig? Warum würden Sie mich brauchen? Ich werde die Stadt sofort verlassen und niemand wird uns jemals wiedersehen. Und Sie bekommen Ihr Geld. Was denken Sie, Offizier?";
		link.l1 = "Glaubst du wirklich, Abschaum, dass ich meine Pflicht für so eine lächerliche Summe entehren werde?";
		link.l1.go = "ShadowTrader_3";
		break;
	
	case "ShadowTrader_3":
		dialog.text = "Also gut, also gut, Offizier, nehmt alles, was ich habe - 10.000 Pesos. Es ist alles, was ich habe, ich schwöre!";
		link.l1 = "Hm... Wenn ich dich festnehme, wird all dein Geld beschlagnahmt... Sehr gut! Dieser Schmuggelposten ist geschlossen und alle Waren sind beschlagnahmt... Gib mir die Münze und verschwinde. Zeig hier nie wieder dein Gesicht!";
		link.l1.go = "ShadowTrader_4";
		break;
		
	case "ShadowTrader_4":
			dialog.text = "Danke, danke, danke Offizier! Hier ist Ihr Geld, und Sie werden mich hier nicht wiedersehen. Los geht's!";
			link.l1 = "Verschwinde oder ich werde dich verhaften müssen!";
			link.l1.go = "ShadowTrader_escape";
		break;
	
		case "ShadowTrader_fight":
			LAi_SetPlayerType(pchar);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("ShadowAgent_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				sld.nation = PIRATE;
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "ShadowTrader_afterfight");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	
		case "ShadowTrader_escape"://напугали
			AddMoneyToCharacter(pchar, 10000);
			LAi_SetPlayerType(pchar);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("ShadowAgent_"+i);	
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 7.0);
			}
			sld = characterFromID("ShadowTrader"); 
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 7.0);
			DialogExit();
			DoQuestFunctionDelay("ShadowTrader_final", 9.0);
			pchar.questTemp.Shadowtrader.End.Escape = "true";
			AddQuestRecord("Shadowtrader", "8");
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 250);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
	
		case "ShadowTrader_6":
			dialog.text = "Ach! Gnade, töte mich nicht! Ich gebe dir alles, was ich habe!";
			link.l1 = "Alle deine Waren werden von den Behörden konfisziert. Glaubst du wirklich, dass ich nach dem, was hier gerade passiert ist, Gnade mit dir habe?";
			link.l1.go = "ShadowTrader_7";
		break;
	
		case "ShadowTrader_7":
			dialog.text = "Ich... Ich gebe dir all mein Geld und meine Habseligkeiten! Lass mich einfach gehen! Ich werde die Insel heute verlassen und du wirst mich hier nie wieder sehen!";
			link.l1 = "Sehr gut. Gib mir alles, was du bei dir hast und verschwinde. Und versuche nie wieder, hier Geschäfte zu machen - das nächste Mal werde ich dein erbärmliches Leben nicht verschonen, du Brigant.";
			link.l1.go = "ShadowTrader_free";
			link.l2 = "Keine Chance, Bastard, du wirst mich nicht abkaufen. Der einzige Weg, mit deiner Sorte umzugehen, ist kalter Stahl und heißes Blei!";
			link.l2.go = "ShadowTrader_killed";
		break;
		
		case "ShadowTrader_free"://отпустили
			AddMoneyToCharacter(pchar, 20550);
			TakeNItems(pchar, "jewelry1", rand(5));
			TakeNItems(pchar, "jewelry2", rand(20));
			TakeNItems(pchar, "jewelry5", rand(20));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received items");
			LAi_SetPlayerType(pchar);
			sld = characterFromID("ShadowTrader"); 
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
			DialogExit();
			DoQuestFunctionDelay("ShadowTrader_final", 7.0);
			pchar.questTemp.Shadowtrader.End.Free = "true";
			AddQuestRecord("Shadowtrader", "9");
			ChangeCharacterComplexReputation(pchar,"nobility", 5); 
			AddComplexSelfExpToScill(70, 70, 70, 70);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		break;
	
		case "ShadowTrader_killed":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetActorType(pchar);
			//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// <-- legendary edition
			LAi_ActorAnimation(pchar, "Shot", "ShadowTrader_killed_end", 1.3);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
