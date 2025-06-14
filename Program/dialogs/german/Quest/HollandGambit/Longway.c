// китаец Лонгвэй, подручный Роденбурга
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Kapitän. Mein Name ist Longway. Longway übergibt sein Schiff unter dein Kommando. Longway steht auch unter deinem Befehl. Befehl von Herr Rodenburg.";
			link.l1 = "Grüße, Longway. Charles de Maure, zu Ihren Diensten. Haben Sie irgendwelche Hinweise auf die Operation zur Eliminierung von Jacob van Berg?";
			link.l1.go = "Longway_friend";
			link.l2 = "Gut dich zu sehen, Longway. Mein Name ist Charles de Maure. Keine Zeit zu verschwenden - Mynheer Rodenburg schätzt schnelle und hochwertige Arbeit. Wo versteckt sich Jacob van Berg jetzt?";
			link.l2.go = "Longway_neutral";
			link.l3 = "Nun, und meiner ist Charles de Maure! Zu hoffen, dass unsere gut zusammenarbeiten werden! Also, mein Herr Longway, sagen Sie mir bitte, wo sollten unsere nach Jacob van Berg suchen?";
			link.l3.go = "Longway_enemy";
			NextDiag.TempNode = "First time";
			pchar.questTemp.HWIC.Holl.JacobCity = SelectJacobCity();
		break;
		
//-----------------------------------------------за Голландию-----------------------------------------------
		case "Longway_neutral":
			dialog.text = "Longway ist sich sicher, dass wir gut zusammenarbeiten werden, chuanzhang. Jacob van Berg ist derzeit bei "+XI_ConvertString("Kolonie"+pchar.questTemp.HWIC.Holl.JacobCity+"Gen")+". Ich habe ein Treffen mit ihm in der örtlichen Taverne arrangiert. Er wird dort sein.";
			link.l1 = "Lass uns in See stechen!";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayNeutral = "true";//признак враждебности китайца
		break;
		
		case "Longway_enemy":
			dialog.text = "Befehl von Herrn Rodenburg Gesetz für Longway... Jacob van Berg derzeit bei "+XI_ConvertString("Kolonie"+pchar.questTemp.HWIC.Holl.JacobCity+"Gen")+". Ich habe ein Treffen mit ihm in der örtlichen Taverne arrangiert. Er wird dort sein.";
			link.l1 = "Lass uns in See stechen!";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayEnemy = "true";//признак враждебности китайца
			notification("Longway disapproves", "Longway");
		break;
		
		case "Longway_friend":
			dialog.text = "Longway wird alles tun, was er kann, Kapitän. Und Jacob van Berg ist derzeit bei "+XI_ConvertString("Kolonie"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat")+". Ich habe ein Treffen mit ihm in der örtlichen Taverne arrangiert. Er wird dort sein.";
			link.l1 = "Lass uns in See stechen!";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayFriend = "true";//признак враждебности китайца
			notification("Longway approves", "Longway");
		break;
		
		case "Longway_JacobGo":
			//Лонгвэя - в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;//полубессмертен
			npchar.loyality = 18;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", -1);
			AddQuestRecord("Holl_Gambit", "1-8");
			AddQuestUserData("Holl_Gambit", "sCity", XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat"));
			AddMapQuestMarkCity(pchar.questTemp.HWIC.Holl.JacobCity, true);
			AddLandQuestMark(characterFromId(""+pchar.questTemp.HWIC.Holl.JacobCity+"_tavernkeeper"), "questmarkmain");
			pchar.questTemp.HWIC.Holl = "JacobOnMain";
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("JacobOnMainOver", 0, 0, 30, false);
			}
			else SetFunctionTimerCondition("JacobOnMainOver", 0, 0, 15, false);
		break;
		
		case "hired":
			dialog.text = "Was kann Longway tun, chuanzhang?";
			link.l1 = "Nichts für jetzt.";
			link.l1.go = "exit";
			NextDiag.TempNode = "hired";
		break;
		
		case "MC_GoAway":
			PlaySound("Voice\English\hambit\Longway-02.wav");
			if (pchar.questTemp.HWIC.Holl == "MirageFail")
			{
				dialog.text = "Du dummkopf Mongole, chuanzhang! Wir hatten eine einfache Aufgabe - 'Mirage' fangen ohne 'Meifeng' zu verlieren. Sie war ein leichtes Ziel ohne ihren chuanzhang, doch du hast es versäumt, die Aufgabe zu erfüllen\nLongway wird dir weder dienen, noch dich mehr sehen. Longway ist sich sicher, dass Mynheer Rodenburg seine Entscheidung gutheißen wird.";
				link.l1 = "Zum Teufel mit dir und deinem Meister!";
				link.l1.go = "exit";
				AddQuestRecord("Holl_Gambit", "1-10");
			}
			if (pchar.questTemp.HWIC.Holl == "JacobOnMain" || pchar.questTemp.HWIC.Holl == "JacobInRoom")
			{
				dialog.text = "Du Idiot Mongole, chuanzhang! Wir haben zu viel Zeit damit verschwendet, deine eigenen Angelegenheiten zu klären, anstatt Jacob van Berg zu treffen. Er ist bereits weg von "+XI_ConvertString("Kolonie"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat")+"\nSie haben versagt, die Aufgabe zu erfüllen. Longway wünscht weder Ihnen zu dienen, noch Sie jemals wieder zu sehen. Longway ist sicher, dass Mynheer Rodenburg seine Entscheidung gutheißen wird.";
				link.l1 = "Zum Teufel mit dir und deinem Herrn!";
				link.l1.go = "exit";
				AddQuestRecord("Holl_Gambit", "1-9");
			}
			if (pchar.questTemp.HWIC.Holl == "lateVillemstad")
			{
				dialog.text = "Kapitän, Sie haben zu viel Zeit ohne Ergebnis verschwendet. Dies ist nicht Ihr Schiff und Longway ist nicht Ihr Kuli. Longway kehrt nach Willemstad zurück\nLongway wird weder Ihnen dienen, noch Sie mehr sehen. Longway ist sicher, dass Mynheer Rodenburg seine Entscheidung billigen wird.";
				link.l1 = "Zum Teufel mit dir und deinem Meister!";
				link.l1.go = "exit";
			}
			PChar.quest.Munity = "Deads";
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)//если сам на Мейфенг
			{
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "Boat";
			SetBaseShipData(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			}
			else
			{
				for(i=1; i < COMPANION_MAX; i++)
				{
					int iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Holl.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Detector = "holl_fail";
		break;
		
		case "Longway_hire":
			PlaySound("Voice\English\hambit\Longway-03.wav");
			dialog.text = "Kapitän, Longway hat Mynheer Rodenburg verlassen. Longway wird niemals zu ihm zurückkehren. Sie waren freundlich zu Longway und Sie sind ein mutiger Kapitän. Longway möchte sich Ihrer Mannschaft als Ihr Diener anschließen, Herr Kapitän.";
			link.l1 = "Nicht als Diener, sondern als Offizier! Willkommen an Bord, Freund!";
			link.l1.go = "Longway_hire_1";	
			link.l2 = "Nein danke, Longway. Du bist ein freier Mann. Ich brauche deine Dienste nicht.";
			link.l2.go = "Longway_exit";	
		break;
		
		case "Longway_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 30.0);
			AddQuestRecord("Holl_Gambit", "1-37");
		break;
		
		case "Longway_hire_1"://нанимаем китайца
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "HalfImmortal");
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			npchar.CanTakeMushket = true;
			npchar.Payment = true;
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Longway_officer";
			npchar.quest.meeting = true;
			npchar.HoldEquip = true;
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 200, 200);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			AddQuestRecord("Holl_Gambit", "1-38");
			
			//Sinistra - квест Лонгвэя "Путеводная звезда"
			PChar.quest.PZ_Start.win_condition.l1 = "location";
			PChar.quest.PZ_Start.win_condition.l1.location = "Curacao";
			PChar.quest.PZ_Start.win_condition = "PZ_Start";
		break;
		
//---------------------------------------------против всех-------------------------------------------------
		case "Longway_abordage":
			PlaySound("Voice\English\hambit\Longway-02.wav");
			dialog.text = "Warum hörst du auf? Töte. Longway ist müde, Longway möchte sterben. Xing... vergib mir.";
			link.l1 = "Nicht so schnell, Chinese. Ich werde dich töten, wenn ich will, aber zuerst muss ich mit dir sprechen. Dein Schicksal hängt von deinen zukünftigen Handlungen ab. Willkommen in meinem Laderaum fürs Erste!";
			link.l1.go = "Longway_abordage_1";			
		break;
		
		case "Longway_abordage_1":
			AddQuestRecord("Holl_Gambit", "3-45");
		    DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
            DialogExit();
			LAi_SetPlayerType(pchar);
			pchar.questTemp.HWIC.Self = "LongwayPrisoner";
			npchar.lifeday = 0;
			SetFunctionTimerCondition("RemoveLongwayOver", 0, 0, 1, false);//таймер до конца суток, ибо нефиг
		break;
		
		case "Longway_prisoner":
			DelLandQuestMark(npchar);
			dialog.text = "";
			link.l1 = "Nun können wir reden, ohne dass das Klirren von Stahl meine Ohren zerrüttet. Hör zu, Longway, ich brauche Informationen und ich habe keinen Zweifel, dass du weißt, was ich wissen muss. Die Frage ist: Wirst du es mir auf die leichte oder die harte Weise sagen?";
			link.l1.go = "Longway_prisoner_1";			
		break;
		
		case "Longway_prisoner_1":
			dialog.text = "";
			link.l1 = "Schweigen? Gut. Ich biete dir einen Deal an. Ich werde dein Leben verschonen und dich am nächsten Ufer absetzen. Im Gegenzug wirst du mir sagen, wo und warum Lucas Rodenburg dich geschickt hat. Deal?";
			link.l1.go = "Longway_prisoner_2";			
		break;
		
		case "Longway_prisoner_2":
			dialog.text = "";
			link.l1 = "Ich weiß, dass Sie Englisch, Holländisch und Französisch verstehen. Sie sind auch ein guter Zuhörer. Jetzt ist es an der Zeit zu sprechen. Sie werden mir schließlich alles erzählen, was Sie wissen. Ich weiß, ihr Chinesen seid stolz auf eure Folterkunst, aber wir Männer des Okzidents haben in dieser alten Wissenschaft unsere eigenen Fortschritte gemacht. Alonso hier ist ein Meister darin, die Zungen der Leute zu lösen. Er war ein Befrager für die Heilige Inquisition in Santiago, bevor er auf mein Schiff kam. Er kennt alle möglichen Tricks, die er von den heiligen Vätern gelernt hat, die die Kunst perfektioniert haben, die Leute zum Geständnis zu bringen...man muss nicht einmal ein Protestant sein!";
			link.l1.go = "Longway_prisoner_3";			
		break;
		
		case "Longway_prisoner_3":
			dialog.text = "";
			link.l1 = "Mein Witz ist an dir verschwendet. Du wirst mir alles erzählen, mein schlitzaugiger Freund... Alles... Aber du wirst nicht lange danach leben, nein, das wirst du nicht. Dein Körper wird sehr leiden, nachdem er Alonso getroffen hat/. Also die Wahl liegt bei dir. Entweder du sagst mir die ganze Wahrheit und lebst, oder du sagst mir die ganze Wahrheit und stirbst in Qualen auf der Streckbank. Gequält vor Schmerz auf der Streckbank. Verstehst du? Mach dir keine Sorgen, ich werde sicher einen Priester dabei haben, um dich als Christen zu taufen, um deine heidnische Seele vor den ewigen Feuern der Hölle zu bewahren.";
			link.l1.go = "Longway_prisoner_4";
		break;
		
		case "Longway_prisoner_4":
			dialog.text = "";
			link.l1 = "Ich sehe Zweifel in deinen schwarzen Augen wachsen. Warum solltest du für die Sünden deines Meisters sterben? Ist er das wert? Ist Rodenburg es wirklich wert, dass deine Seele aus deinem leidenden Körper gerissen wird?";
			link.l1.go = "Longway_prisoner_5";			
		break;
		
		case "Longway_prisoner_5":
			dialog.text = "Longway spricht. Aber zuerst möchte Longway sicher sein, dass du dein Wort hältst, Chuanzhang.";
			link.l1 = "Ha! Kluge Worte! Ich gebe dir mein Wort, Junge.";
			link.l1.go = "Longway_prisoner_6";			
		break;
		
		case "Longway_prisoner_6":
			dialog.text = "Entschuldigung, Kapitän, dein Wort reicht nicht aus. Du bekommst Informationen und tötest Longway danach! Longway will Garantien.";
			link.l1 = "Du handelst wie ein Jude. Welche Garantien möchtest du?";
			link.l1.go = "Longway_prisoner_7";			
		break;
		
		case "Longway_prisoner_7":
			dialog.text = "Es gibt eine kleine Insel südlich von Guadeloupe. Kap Unzugänglich. Lande dort und gebe Longway die Waffe. Nur dann wird Longway dir alles erzählen, was er über Lucas Rodenburg weiß.";
			link.l1 = "Du bist in keiner Position, um mit mir zu verhandeln, Chinese.";
			link.l1.go = "Longway_prisoner_8";			
		break;
		
		case "Longway_prisoner_8":
			dialog.text = "Sie würden dasselbe tun, wenn Sie Longway wären, chuanzhang. Es wird nicht leicht für Ihren Mann sein, Worte von mir zu bekommen, auch nicht mit Folter. Longway ist kein schwacher weißer Mann.";
			link.l1 = "Gut. Abgemacht. Aber ich warne dich - versuche nicht, mich zu hintergehen, oder ich werde dich persönlich in tausend Stücke schneiden. Langsam... genau wie deine Kaiser es tun. Alonso!";
			link.l1.go = "Longway_prisoner_9";
			// belamour legendary edition -->
			link.l2 = "Du sprichst die Wahrheit. Aber behalte im Kopf - Ich bin zu weit gekommen, als dass du das hier vermasseln könntest. Wenn du versuchst, mich aufzuhalten, werde ich dein Leben beenden, als wäre es ein Insekt, auf das ich trete.";
			link.l2.go = "Longway_prisoner_9a";
		break;
		
		case "Longway_prisoner_9a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			DialogExit();
			NextDiag.Currentnode = "Longway_prisoner_0";
			npchar.greeting = "longway";
			sld = characterFromId("Sailor_3");
			sld.dialog.currentnode = "Sailor_deck_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
			pchar.quest.RemoveLongwayOver.over = "yes";//снять таймер
			pchar.quest.RemoveLongwayTimer.win_condition.l1 = "Timer";
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.function = "RemoveLongwayOver";
			pchar.questTemp.HWIC.Self = "GotoGuadeloupe";
		break;
		
		case "Longway_prisoner_9":
			ChangeCharacterComplexReputation(pchar, "nobility",-5);
			AddCharacterExpToSkill(pchar, "FencingL", 30);
			AddCharacterExpToSkill(pchar, "FencingS", 30);
			AddCharacterExpToSkill(pchar, "FencingH", 30);
			AddCharacterExpToSkill(pchar, "Pistol", 30);
			// <-- legendary edition
			DialogExit();
			NextDiag.Currentnode = "Longway_prisoner_0";
			npchar.greeting = "longway";
			sld = characterFromId("Sailor_3");
			sld.dialog.currentnode = "Sailor_deck_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
			pchar.quest.RemoveLongwayOver.over = "yes";//снять таймер
			pchar.quest.RemoveLongwayTimer.win_condition.l1 = "Timer";
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.function = "RemoveLongwayOver";
			pchar.questTemp.HWIC.Self = "GotoGuadeloupe";
		break;
		
		case "Longway_prisoner_0":
			dialog.text = "Sind wir auf Guadeloupe angekommen, Kapitän?";
			link.l1 = "Beruhige dich, wir werden bald da sein.";
			link.l1.go = "exit";
			NextDiag.Tempnode = "Longway_prisoner_0";
		break;
		
		case "Longway_prisoner_10":
			dialog.text = "Sie haben Ihr Wort gehalten, Kapitän. So wird auch Longway handeln. Wollten Sie etwas über Longways Mission erfahren?";
			link.l1 = "Ja. Aber erlauben Sie mir, Sie an Ihr eigenes Versprechen an mich zu erinnern: Sie werden mir *alles* erzählen, was Sie wissen.";
			link.l1.go = "Longway_prisoner_11";			
		break;
		
		case "Longway_prisoner_11":
			dialog.text = "Longway erinnert sich. Er wird alles beantworten, was Sie über Rodenburg, Chuanzhang, fragen.";
			link.l1 = "Fang an zu reden.";
			link.l1.go = "Longway_prisoner_12";			
		break;
		
		case "Longway_prisoner_12":
			dialog.text = "'Meifeng' segelte vom Hafen von Willemstad gen Norden zu den Küsten von St. Christopher. In fünf Tagen würde dort eine Galeone unter dem Kommando von Peter Stuyvesant sein. Longways Befehl war, dieses Schiff mit seinem Kapitän an Bord zu versenken.";
			link.l1 = "Gott im Himmel! Rodenburg hat dir befohlen, Stuyvesant zu töten? Das ist Wahnsinn!";
			link.l1.go = "Longway_prisoner_13";			
		break;
		
		case "Longway_prisoner_13":
			dialog.text = "Longway spricht die Wahrheit, Kapitän. Das war der Befehl des Mynheer Rodenburg. Longway mochte es nicht, aber Longway hinterfragt keine Befehle.";
			link.l1 = "Wie sehr ähnlich einem Chinesen. Welches Spiel treibt dein Herr?";
			link.l1.go = "Longway_prisoner_14";			
		break;
		
		case "Longway_prisoner_14":
			dialog.text = "Nicht mehr mein Meister, Chuanzhang. Longway wird nicht zu Mynheer Rodenburg zurückkehren. Rodenburg hat die Macht in Curacao an sich gerissen. Mathias Beck war ein leichtes Opfer, Rodenburgs Autorität und Verbindungen mit dem Kommandanten reichten aus, um den Gouverneur ins Gefängnis zu stecken\nDas einzige verbleibende Hindernis ist der Direktor der Westindischen Kompanie, Mynheer Stuyvesant. Sobald Stuyvesant beseitigt ist, wird Rodenburg jede Machtstelle in den niederländischen Kolonien innehaben.";
			link.l1 = "Sag mir, Longway, was hat einen angesehenen und mächtigen Mann wie Rodenburg dazu gebracht, solch radikale Maßnahmen gegen seine Firma und Republik zu ergreifen? Und erzähl mir nicht, es sei von der Hitze der Sonne oder einem Ausbruch von Wahnsinn.";
			link.l1.go = "Longway_prisoner_15";			
		break;
		
		case "Longway_prisoner_15":
			dialog.text = "Longway wollte selbst von dir wissen, Chuanzhang. Du hast das Postschiff der Kompanie gefangen genommen und den Brief nach Rodenburg gebracht, richtig? Der Grund in diesem Brief.";
			link.l1 = "Ich sehe jetzt... Scheint, dass es viele wunderbare Dinge im Archiv von John Murdock gibt, die Rodenburg genug Angst machen, um eine Rebellion gegen sein eigenes Land zu starten.";
			link.l1.go = "Longway_prisoner_16";			
		break;
		
		case "Longway_prisoner_16":
			dialog.text = "Möchten Sie sonst noch etwas wissen, Kapitän?";
			link.l1 = "Ja. Was hat Rodenburg sonst noch getan?";
			link.l1.go = "Longway_prisoner_17";			
		break;
		
		case "Longway_prisoner_17":
			dialog.text = "Herr Rodenburg hat den Befehl gegeben, dich zu töten. Longway war vor der Jagd auf Stuyvesant in Caracas und hatte ein Treffen mit Chuanzhang Jacob und gab ihm Befehle.";
			link.l1 = "Kapitän Jacob van Berg?";
			link.l1.go = "Longway_prisoner_18";			
		break;
		
		case "Longway_prisoner_18":
			dialog.text = "Sie sind gut informiert. Ja. Chuanzhang Jacob van Berg jagt Sie, Kapitän. Er wird Sie schließlich finden. Niemand kann sich lange vor van Berg verstecken.";
			link.l1 = "Wenn er blutet, kann ich ihn töten. Ich werde mich um van Berg und sein gepriesenes Geisterschiff kümmern.";
			link.l1.go = "Longway_prisoner_19";			
		break;
		
		case "Longway_prisoner_19":
			dialog.text = "Sie wissen viel, Chuanzhang. Longway hat nichts hinzuzufügen. Fragen Sie, wenn Sie noch etwas fragen möchten.";
			link.l1 = "Wird Stuyvesant in der Nähe der Küsten von St. Christopher sein?";
			link.l1.go = "Longway_prisoner_20";			
		break;
		
		case "Longway_prisoner_20":
			dialog.text = "Ja, Kapitän. Sie werden in der Lage sein, seine Galeone in etwa einer Woche in der Nähe der Küste dieser Insel zu finden.";
			link.l1 = "Fein! Fangen wir diesen Fuchs in seiner eigenen Falle... Ich habe keine weiteren Fragen. Ich weiß alles, was ich wissen wollte.";
			link.l1.go = "Longway_prisoner_21";			
		break;
		
		case "Longway_prisoner_21":
			dialog.text = "Einen letzten Rat, Chuanzhang. Sie müssen 'Meifeng' nehmen, wenn Sie sich dem Galeonen nähern wollen, ohne angegriffen zu werden.";
			link.l1 = "Verstanden. Danke für Ihre Informationen.";
			link.l1.go = "Longway_prisoner_22";			
		break;
		
		case "Longway_prisoner_22":
			dialog.text = "Longway verlässt jetzt. Lebewohl, Chuanzhang.";
			link.l1 = "Gott mit dir, mein orientalischer Gefährte.";
			link.l1.go = "Longway_prisoner_23";			
		break;
		
		case "Longway_prisoner_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "ReturnShoreToNormal", -1);
			npchar.lifeday = 0;
			AddQuestRecord("Holl_Gambit", "3-49");
			pchar.questTemp.HWIC.Self = "MeetingStivesant";
			pchar.quest.Seek_Piter.win_condition.l1 = "location";
			pchar.quest.Seek_Piter.win_condition.l1.location = "Nevis";
			pchar.quest.Seek_Piter.function = "CreatePiterHalleon";
			pchar.quest.RemoveLongwayTimer.over = "yes";//снять прерывание
			SetFunctionTimerCondition("QuestShipsTerms_Over", 0, 0, 8, false); // таймер
			AddMapQuestMarkIsland("Nevis", true);
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Longway_officer":
			dialog.text = "Lange lauschen, Kapitän.";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Longway, ich gehe in die alte indische Stadt Tayasal. Ich werde klar sein, das wird eine wirklich gefährliche Reise und es ist auch eine mystische - wir werden dort durch das Teleport-Idol gelangen. Wirst du... mich begleiten?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Longway, gib mir einen vollständigen Schiffsbericht.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Ich möchte, dass du bestimmte Waren kaufst, jedes Mal wenn wir angedockt sind.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Ich bin auf Ihren Befehl angekommen, Kapitän.";
				Link.l2 = "Ich muss Ihnen mehrere Anweisungen geben.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "Longway_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "Hör auf meinen Befehl!";
            Link.l1.go = "stay_follow";
			link.l2 = "Nichts. Entlassen!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Longway_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Longway war noch nie Zahlmeister, Chuanzhang. Longway kann Ihnen sagen, wie Sie von Trinidad nach Havanna navigieren und wie lange es dauern wird. Aber Longway hat noch nie Ladung, Verkauf und Handel gezählt.";
			Link.l1 = "Ich denke, du hast recht. Es wäre eine Schande, einen so guten Navigator zu verschwenden.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Longway handelt nicht mit gwailo, chuanzhang. Longway stand immer am Steuer, nicht im Laden, wo alte Hakennase bis zum letzten Achtel feilscht.";
			link.l1 = "Hm, du hast recht. Du würdest wahrscheinlich die Händler erschrecken.";
			link.l1.go = "exit";
		break;

		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Ich höre zu.";
			Link.l1 = "Lassen wir über Enterung sprechen.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Lassen Sie uns über Ihr Schiff sprechen.";
			Link.l2.go = "Companion_TaskChange";
			if (bBettaTestMode) // Только при бета-тесте
			{
				Link.l3 = "Ich möchte, dass du für eine Weile meine Staffel verlässt und alleine dein Glück suchst.";
				Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "Bisher nichts.";
			Link.l8.go = "exit";
		break;

		case "Companion_TaskBoarding":
			dialog.Text = "Was ist dein Wunsch.";
			Link.l1 = "Entern Sie keine feindlichen Schiffe. Kümmern Sie sich um sich selbst und die Mannschaft.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Ich möchte, dass Sie feindliche Schiffe aggressiv entern.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;

		case "Companion_TaskChange":
			dialog.Text = "Was ist dein Wunsch.";
			Link.l1 = "Tausche dein Schiff nicht gegen ein anderes aus, nachdem du es betreten hast. Es ist zu wertvoll.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Wenn du feindliche Schiffe kapern, kannst du sie für dich selbst nehmen, falls sie zufällig anständig sind.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "Jawohl.";
			Link.l1 = "Ruhig.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "Es wird gemacht.";
			Link.l1 = "Ruhig.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;

		case "Companion_TaskChangeNo":
			dialog.Text = "Jawohl.";
			Link.l1 = "Es wird erledigt sein.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

		case "Companion_TaskChangeYes":
			dialog.Text = "Es wird erledigt werden.";
			Link.l1 = "Ruhig.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========////////////////////////////////////////
		case "stay_follow":
            dialog.Text = "Befehle, Kapitän?";
            Link.l1 = "Haltet stand!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Folge mir und halte mit!";
            Link.l2.go = "Boal_Follow";
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Ändere die Art der Munition für deine Feuerwaffen.";
					Link.l3.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Ändere die Art der Munition für dein Musket.";
					Link.l4.go = "SetMusketBullets";
				}
					Link.l5 = "Wechseln Sie Ihre Prioritätswaffe für den Kampf.";
					Link.l5.go = "SetPriorityMode";
					Link.l6 = "Ich möchte, dass du die Feinde aus einer bestimmten Entfernung beschießt, Lonway.";
					Link.l6.go = "TargetDistance";
			}	
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Wähle die Art der Munition:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;

		case "SetMusketBullets":
			Dialog.Text = "Wählen Sie den Munitionstyp:";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "Zu Beginn des Kampfes wirst du verwenden:";
			Link.l1 = "Klinge";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Muskete";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Es gibt eine Änderung der Gesinnung!";
            Link.l1 = "Abgewiesen.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Es gibt eine Änderung der Gesinnung!";
            Link.l1 = "Abgetreten.";
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = "Und welche Entfernung wäre das? Denken Sie daran, Herr Kapitän, Sie können mit einer Muskete nichts über zwanzig Meter treffen.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Was meinen Sie, Herr Kapitän?";
				link.l1 = "Entschuldigung, manchmal vergesse ich, dass du nicht gut mit Witzen umgehen kannst.";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Ich halte meine Position, schieße aber auf jeden Feind, der zu nahe kommt. Ist das was du willst?";
				link.l1 = "Ja, genau, Lonway.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Das ist zu weit, Herr Kapitän. Sie könnten in eine Menge treffen, aber auf ein einzelnes Ziel zu zielen - keine Chance.";
				link.l1 = "Es wäre einen Versuch wert, aber gut.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Ich verstehe, Herr Kapitän.";
			link.l1 = "Ausgezeichnet.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Longway verfolgt dich schon seit langer Zeit. Longway wird dir wie immer folgen. Longway verlässt seinen Chuanzhang nicht.";
			link.l1 = "Danke, Longway! Ich bin froh, dass ich recht hatte mit dir.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Wann werden wir anfangen?";
			link.l1 = "Etwas später. Wir müssen uns darauf vorbereiten.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "24");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string SelectJacobCity()
{
	string sTemp;
	switch (hrand(4))
	{
		case 0: sTemp = "Cumana" break;
		case 1: sTemp = "Caracas" break;
		case 2: sTemp = "Maracaibo" break;
		case 3: sTemp = "Cartahena" break;
		case 4: sTemp = "Portobello" break;
	}
	return sTemp;
}
