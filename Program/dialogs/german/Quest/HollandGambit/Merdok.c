// Джон Мердок, он же Йохан ван Мерден, соратник Роденбурга
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		if (!CheckAttribute(pchar, "questTemp.HWIC.Self") && LAi_grp_playeralarm > 0)
		{
			dialog.text = "Herr, Sie haben sich einen verdammt schlechten Zeitpunkt für ein Plauderstündchen ausgesucht. Die gesamte Garnison sucht nach Ihnen. Sie sollten besser ziemlich schnell abhauen...";
			link.l1 = "Mach dir keine Sorgen. Ich bleibe nicht lange.";
			link.l1.go = "exit";
			break;
		}
		// продажа алхимического набора, если провалил гамбит
		if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && !CheckAttribute(npchar, "quest.alchemy"))
		{
			bOk = (findsubstr(pchar.questTemp.HWIC.Detector, "_fail" , 0) != -1) || (pchar.questTemp.HWIC.Detector == "eng_win_half");
			if (bOk)
			{
				dialog.text = "Willkommen, Kapitän. Hätten Sie Interesse an einem faszinierenden Angebot? ";
				link.l1 = "Allerlei Leute hier scheinen solche Angebote zu haben, und ich bin ein neugieriger Mann. Was ist es? ";
				link.l1.go = "alchemy";
				break;
			}
		}
		// Страж Истины
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok1")
		{
			dialog.text = "Guten Tag. Willkommen in meiner Apotheke. Ich habe Medikamente zur Behandlung der meisten Krankheiten und Gebrechen. Was kann ich Ihnen anbieten?";
			link.l1 = "Hör zu, John, es gibt Gerüchte, dass jemand in deiner Wohnung im zweiten Stock lebt...";
			link.l1.go = "guardoftruth";
			break;
		}
//-----------------------------------------за Голландию------------------------------------------------
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.location.from_sea == "SentJons_town" && pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Guten Tag. Ich freue mich, Sie in meiner Apotheke zu sehen. Ich habe Medikamente zur Behandlung der meisten Krankheiten und Gebrechen. Was kann ich Ihnen anbieten?";
				link.l1 = "Hallo Herr Murdock. Ich bin hier im Auftrag von Lucas Rodenburg. Er hat mich zu Ihnen geschickt, um eine Angelegenheit bezüglich Richard Fleetwood zu besprechen.";
				link.l1.go = "Knippel_exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Guten Nachmittag. Welches Problem haben Sie? Ich habe sowohl Hustensaft als auch Durchfallpulver!";
				link.l1 = "Hallo, Herr Murdock. Ich bin im Auftrag von Lucas Rodenburg hier. Er hat mich zu Ihnen geschickt, um eine Sache bezüglich Richard Fleetwood zu besprechen.";
				link.l1.go = "Knippel";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "KillMerdok")
			{
				dialog.text = "Ahhh, hier ist Rodenburgs angestellter Hund... Hercule, Longway - würden Sie bitte hier rauskommen?\nTötet diesen Mann!";
				link.l1 = "Warte, ich habe ein Rezept!";
				link.l1.go = "Merdok_fight";
				break;
			}
			dialog.text = "Guten Nachmittag. Ich freue mich, Sie in meiner Apotheke zu sehen. Ich habe Medikamente gegen die meisten Krankheiten und Gebrechen. Was darf ich Ihnen anbieten?";
			link.l1 = "Im Moment nichts, danke. Ich fühle mich ziemlich gut.";
			link.l1.go = "exit";
			break;
		}
//----------------------------------------------за Англию---------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "MerdokMeeteng")
			{
			dialog.text = "Hallo, ungeladener Gast. Du bedeckst dein Gesicht nicht mit einer Maske und siehst auch nicht aus wie ein Räuber. Daher komme ich zu dem Schluss, dass du etwas anderes von einem armen Apotheker brauchst. Vielleicht etwas gegen Durchfall?";
			link.l1 = "Hallo auch, Johan van Merden. Ich bringe Grüße von Hercule Tonzag. Ich sehe, Sie kennen diesen Namen.";
			link.l1.go = "Merdok_talk";
			DelLandQuestMark(npchar);
			break;
			}
//--------------------------------------------против всех--------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "HuntFleetwood")
				{
					dialog.text = "Ach, hier bist du also. Nun, hast du Hercule getroffen? ";
					link.l1 = "Ja. Wir haben eine Vereinbarung getroffen. John, ich werde Hercule helfen und ich habe mehrere Fragen an dich bezüglich Richard Fleetwood.";
					link.l1.go = "About_Fleetwood";
					break;
				}
				if (GetQuestPastDayParam("questTemp.Wait_Fleetwood") > 6 && pchar.questTemp.HWIC.Self == "WaitFleetwood")
				{
					dialog.text = "Hallo! Ich freue mich, dich zu sehen, "+pchar.name+"!";
					link.l1 = "Hallo, John. Hast du etwas über Fleetwood herausgefunden?";
					link.l1.go = "About_Fleetwood_9";
					pchar.quest.Wait_FleetwoodOver.over = "yes"; //снять таймер
					break;
				}
				if (pchar.questTemp.HWIC.Self == "HWICSelf_fail")
				{
					dialog.text = "Du bist zu spät. Der Vogel ist aus dem Käfig geflogen. Charlie Knippel hat Willemstad besucht und ein Mädchen für Richard mitgebracht. Jetzt segeln sie in ein oder zwei Tagen mit einem Militärgeschwader nach England. Fleetwood ist weg, du wirst ihn in diesem Leben nie wieder sehen.";
					link.l1 = "Verdammt. Ich hatte Richard völlig vergessen und die Zeit aus den Augen verloren. Wir sehen uns.";
					link.l1.go = "About_Fleetwood_17";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileOnShip")
				{
					dialog.text = "Willkommen zurück, "+pchar.name+"! Nichts für dich gerade jetzt. Es gibt keine Neuigkeiten über Fleetwood, und Charlie Knippel ist noch nicht aus Curacao zurückgekehrt...";
					link.l1 = "Und er wird es auch nie tun. Weder er noch seine Brigantine.";
					link.l1.go = "Abigile";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInHouse")
				{
					dialog.text = "Ach, wir haben Gäste! Hallo, Charlie! Guten Tag, Fräulein!";
					link.l1 = "Guten Nachmittag, John! Lassen Sie mich Ihnen meine weibliche Begleiterin vorstellen, die Verlobte von Richard, die bezaubernde Abigail Shneur.";
					link.l1.go = "Abigile_7_1";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInRoom")
				{
					dialog.text = "Senken Sie Ihre Stimme... Was wirst du als nächstes tun?";
					link.l1 = "Als nächstes? Ich würde lieber etwas schlafen, aber leider gibt es dafür keine Zeit. Ich werde Fleetwood aus dem Loch ausgraben, in dem er sich versteckt, und Hercules Arbeit beenden.";
					link.l1.go = "Abigile_9";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "LetterToFleetwood")
				{
					dialog.text = "Bist du fertig mit dem Schreiben? Lass mich sehen... Mein Gott Charlie, du bist ein richtiger Wahnsinniger! Denkst du nicht, dass du das ein bisschen zu detailliert gemacht hast? Ich meine, der Teil über Miss Shneurs Finger, Ohren und Gesicht? Du hast ein krankes Talent, das steht fest. Verdammt, ich bin kurz davor, mein Mittagessen zu verlieren!";
					link.l1 = "Ich bluffe, John. Ich werde das Mädchen nicht töten. Ich könnte sie dazu bringen, ihren Finger zu verlieren... Aber nichts mehr. Sie hat ja schließlich noch neun weitere.";
					link.l1.go = "Abigile_15";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "FleetwoodAgree")
				{
					dialog.text = "Ging es gut? Ich kann es in deinen Augen sehen - du hast es geschafft!";
					link.l1 = "Ja. Fleetwood hat meine Bedingungen akzeptiert. Die Falle schnappt zu. Jetzt warten wir.";
					link.l1.go = "Abigile_23";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "FleetwoodDied")
				{
					dialog.text = "Ach, willkommen zurück, mein Freund! Was kannst du mir erzählen?";
					link.l1 = "Fleetwood ist tot. Alles lief nach Plan. Er kam auf die Insel, wo ich einen Hinterhalt am Strand organisiert hatte. Er leistete ziemlichen Widerstand, aber es half ihm nicht. Nur einer von uns ging von diesem Strand weg.";
					link.l1.go = "Abigile_27";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "MeetTonzag")
				{
					dialog.text = "In Ordnung "+pchar.name+", Ich habe ein ernsthaftes Angebot für Sie. Die Angelegenheit, über die ich sprechen werde, ist sehr gefährlich, aber angesichts der Art und Weise, wie Sie Fleetwood losgeworden sind, bin ich sicher, dass Sie es bewältigen können. Sie haben eine...seltene Gabe, schwierige Probleme zu lösen.";
					link.l1 = "Ich bin geschmeichelt. Mach weiter.";
					link.l1.go = "Lucas";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SeekAbiIsland")
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					dialog.text = "Willkommen zurück, "+pchar.name+"! Gibt es gute Nachrichten für mich?";
					link.l1 = "John, ab jetzt kannst du ohne ein Messer unter dem Kissen schlafen. Lucas ist keine Bedrohung mehr für dich. Er wurde verhaftet und eingesperrt und wird in naher Zukunft nach Holland geschickt, wo er wegen Aufstand, versuchten Mordes und anderen Vergehen vor Gericht gestellt wird.";
					link.l1.go = "Lucas_10";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "VanbergDestroyed")
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					dialog.text = "Schön dich zu sehen, "+pchar.name+"! Du lebst - und das ist gut so. Gibt es Neuigkeiten?";
					link.l1 = "Ja. Van Berg ist für immer verschwunden. Genau wie du gesagt hast, er hat mich aufgespürt und im ungünstigsten Moment angegriffen. Van Berg war eine harte Nuss, aber am Ende habe ich ihn geknackt.";
					link.l1.go = "Final";
					break;
				}
			dialog.text = "Brauchen Sie noch etwas?";
			link.l1 = "Nein, John, nichts. Ich gehe.";
			link.l1.go = "exit";
			break;
			}
			dialog.text = "Guten Nachmittag. Ich freue mich, Sie in meiner Apotheke zu sehen. Ich habe Medikamente zur Behandlung der meisten Krankheiten und Gebrechen. Was kann ich Ihnen anbieten?";
			link.l1 = "Im Moment nichts, danke. Ich fühle mich ziemlich gut.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------------за Голландию-----------------------------------------------------
		case "Knippel_exit":
			dialog.text = "Ich habe keine Ahnung, wovon Sie sprechen, Herr. Welcher Lucas Rodenburg? Ich habe keine Geschäfte mit den Holländern. Sie müssen sich geirrt haben.";
			link.l1 = "Was? Mynheer Rodenburg hat mich zu Ihnen geschickt!";
			link.l1.go = "Knippel_exit_1";
		break;
		
		case "Knippel_exit_1":
			dialog.text = "Lassen Sie mich Ihnen noch einmal sagen - Ich kenne keinen Mann namens Mynheer Rodenburg. Was die Holländer betrifft, so habe ich nichts mit ihnen zu tun. Es gibt nur zwei Dinge, die ich auf dieser Welt nicht ertragen kann: Menschen, die die Kulturen anderer Menschen nicht tolerieren, und die Holländer. Also, wenn Sie keine Medizin benötigen, bitte, lassen Sie mich meine Arbeit machen.";
			link.l1 = "Immer neugieriger und neugieriger...";
			link.l1.go = "exit";
		break;

		case "Knippel":
			dialog.text = "Nun, nun... Kommst du von Mynheer Rodenburg? In Ordnung. Ich höre dir zu.";
			link.l1 = "Ich muss ein Treffen mit Kapitän Fleetwood an einem abgelegenen Ort organisieren. Ich habe die 'Mirage' von Jacob van Berg ausgeliehen, dem niederländischen Freibeuter, den Mr. Fleetwood so sehr fangen will. Ich möchte ihm mitteilen, dass die 'Mirage' in naher Zukunft günstig vor der Küste von Dominica vor Anker liegen wird. ";
			link.l1.go = "Knippel_1";
		break;
		
		case "Knippel_1":
			dialog.text = "Hat Jacob Ihnen sein Schiff gegeben? Hm, also brauchen Sie jetzt jemanden, der Mr. Fleetwood sagt, dass die 'Mirage' bald vor der Küste von Dominica sein wird, da Sie Richard aus bestimmten Gründen nicht selbst davon erzählen können...";
			link.l1 = "Genau. Mynheer Rodenburg hat mir empfohlen, mich mit dieser Angelegenheit an Sie zu wenden.";
			link.l1.go = "Knippel_2";
		break;
		
		case "Knippel_2":
			dialog.text = "In diesem Fall ist Charlie Knippel der Mann, den Sie brauchen. Ein loyaler Freund von Fleetwood... und sein Spion. Sprechen Sie mit ihm und erwähnen Sie alles, was Sie wollen, dass Richard weiß. Seien Sie vorsichtig, Knippel mag ziemlich einfach erscheinen, aber er ist kein Narr.\nSie können ihn in einer kleinen Hütte finden, nicht weit vom Meeresufer entfernt. Er muss dort sein.";
			link.l1 = "Ich verstehe. Danke, Herr Murdock. Auf Wiedersehen!";
			link.l1.go = "Knippel_3";
		break;
		
		case "Knippel_3":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "toKnippel";
			AddQuestRecord("Holl_Gambit", "1-16");
			AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
		break;
		
		case "Merdok_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			sld = characterFromId("Tonzag");
			PlaySound("Voice\English\hambit\Ercule Tongzag-04.wav");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			//а вот и китаец нарисовался
			sld = characterFromId("Longway");
			LAi_SetWarriorType(sld);
			FantomMakeCoolFighter(sld, 18, 40, 40, "blade_08", "pistol1", "bullet", 70);
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayEnemy"))//враг
			{
				ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
				LAi_group_MoveCharacter(sld, "EnemyFight");
				PlaySound("Voice\English\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayFriend"))//друг
			{
				LAi_warrior_DialogEnable(sld, true);
				sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
				sld.dialog.currentnode = "Longway_hire";
				ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				PlaySound("Voice\English\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayNeutral")) sld.lifeday = 0;//нейтрал - просто нет
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattle");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//-------------------------------------------------за Англию-----------------------------------------------------
		case "Merdok_talk":
			dialog.text = "Wirklich? Ich dachte, dieser arme Gaston würde schon seit geraumer Zeit in der Hölle schmoren.";
			link.l1 = "Könnte gut sein, aber es gibt eindeutig niemanden wie Gaston. Ich fand seinen Kopf in einem alten Judenhort auf der geheimen Insel. Aber er schaffte es immer noch, Ihnen Grüße zu senden. Er erwähnte auch, dass wir einen gemeinsamen Feind haben: Herr Rodenburg. Tonzag sagte, dass Sie möglicherweise wichtige Papiere für Lucas haben könnten, die ihn aus seinem Versteck in Curacao locken könnten.";
			link.l1.go = "Merdok_talk_1";			
		break;
		
		case "Merdok_talk_1":
			dialog.text = "Er hatte recht. Es ist mein Archiv, das Rodenburg schlaflose Nächte bereitet. Es scheint, dass er nur deswegen noch hier ist. Die Sache ist die, dass ihm eine leichte Arbeit im Direktorenkomitee der Gesellschaft in den Vereinigten Provinzen versprochen wurde. Wenn die Informationen in diesem Archiv, das viele interessante Dinge über Lucas' Vergangenheit und Gegenwart enthält, bekannt werden, werden seine Karriereambitionen erstickt. In diesem Fall wäre das Beste, was er hoffen könnte, geköpft statt gehängt zu werden.";
			link.l1 = "Gib mir das Archiv, und ich werde mich um unseren Feind kümmern.";
			link.l1.go = "Merdok_talk_2";			
		break;
		
		case "Merdok_talk_2":
			dialog.text = "Sie müssen mich für einen Narren halten. Ich lebe nur noch, weil ich es noch bei mir habe. Wie weiß ich, dass Sie jetzt nicht für Lucas arbeiten?";
			link.l1 = "Du wirst mir mein Wort dafür nehmen müssen - oder sterben.";
			link.l1.go = "Merdok_talk_3";			
		break;
		
		case "Merdok_talk_3":
			PlaySound("Voice\English\hambit\John Mardock-07.wav");
			dialog.text = "Falsche Antwort, du wirst hier und jetzt sterben! Longway, gongji!";
			link.l1 = "Oh ho, der Chinese taucht aus den Schatten auf! Keine Sorge, ich werde aus euch beiden Chop Suey machen!";
			link.l1.go = "Merdok_fightEng";			
		break;
		
		case "Merdok_fightEng":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");	
			sld = characterFromId("Longway");
			FantomMakeCoolFighter(sld, 20, 50, 50, "blade_08", "pistol1", "bullet", 80);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
			PlaySound("Voice\English\hambit\Longway-02.wav");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattleEng");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//----------------------------------------против всех-------------------------------------------------------
		case "MC_InHouse":
			PlaySound("Voice\English\hambit\John Mardock-02.wav");
			dialog.text = "Endlich bist du wieder auf den Beinen. Ich hatte Angst, dass du nicht aufwachen würdest.";
			link.l1 = "Was...? Wer bist du? Wo zum Teufel bin ich? Wie bin ich hierher gekommen?";
			link.l1.go = "MC_InHouse_1";	
		break;
		
		case "MC_InHouse_1":
			dialog.text = "Beruhige dich, stelle nicht so viele Fragen auf einmal, es ist nicht gut für dich, zu aufgeregt zu werden. Mein Name ist John Murdock, ich bin ein Apotheker hier in St. John's. Du hast das Bewusstsein in einem Kampf mit Fleetwoods Männern verloren. Ich muss sagen, dass sie dir ziemlich zugesetzt haben... Es war Hercule, der dich hier in meine Apotheke gebracht hat, und, nun, ich habe deine Wunden mit meinen Tränken und Medikamenten geheilt.";
			link.l1 = "Hercule? Wer? Der Mann, der mir auf der Straße geholfen hat? ";
			link.l1.go = "MC_InHouse_2";			
		break;
		
		case "MC_InHouse_2":
			dialog.text = "Ja. Das ist er. Übrigens, er möchte mit dir sprechen. Du musst ihn in der Stadt treffen. Kannst du noch laufen? Gut. Geh nachts raus - benutze den geheimen Tunnel, der hinter der Tür im Erdgeschoss meines Hauses beginnt. Geh nicht raus, bis es dunkel ist - Fleetwoods Männer suchen dich.";
			link.l1 = "Ja... Wo ist mein Schiff?";
			link.l1.go = "MC_InHouse_3";			
		break;
		
		case "MC_InHouse_3":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "Ihr Schiff wurde beschlagnahmt und Ihre Mannschaft zerstreut aus Angst, von Fleetwoods Männern getötet zu werden. Es tut mir leid.";
				link.l1 = "Verdammt...";
			}
			else
			{
				dialog.text = "Sie ist im Hafen, an ihrem üblichen Platz.";
				link.l1 = "Puh...das ist gut zu hören. Ich dachte, ich hätte sie verloren.";
			}
			link.l1.go = "MC_InHouse_4";			
		break;
		
		case "MC_InHouse_4":
			dialog.text = "Du solltest Hercule treffen. Geh nachts durch den geheimen Tunnel in die Stadt. Er wird auf dich zugehen. Ruhe dich jetzt aus, und ich muss zu meiner Arbeit zurückkehren.";
			link.l1 = "In Ordnung, John. Und... danke für deine Hilfe und Heilung!";
			link.l1.go = "MC_InHouse_5";
		break;
		
		case "MC_InHouse_5":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			npchar.greeting = "merdok_2";
			AddQuestRecord("Holl_Gambit", "3-12");
			pchar.questTemp.HWIC.Self = "MainBegin";//новый флаг квеста
			sld = characterFromId("Bridgetown_tavernkeeper");
			sld.model = "barmen_3";
			sld.greeting = "barmen_1";
			sld.name = "Harry";
			sld.lastname = "Fletcher";//перерисуем бармена Бриджтауна
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", true);//закрыть выход из аптеки через дверь
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);//открыть подземелье из дома
			LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false);//открыть дом из подземелья
			pchar.quest.Tonzag_Meeting.win_condition.l1 = "location";
			pchar.quest.Tonzag_Meeting.win_condition.l1.location = "SentJons_town";
			pchar.quest.Tonzag_Meeting.win_condition.l2 = "Night";
			pchar.quest.Tonzag_Meeting.function = "TonzagMeeting";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);	
		break;
		
		case "About_Fleetwood":
			DelLandQuestMark(npchar);
			dialog.text = "Fleetwood? Was wollen Sie über ihn wissen?";
			link.l1 = "Alles. Erzähl mir alles, was du weißt. Mir scheint, es ist kein Geheimnis für dich, warum Hercule nach Antigua gekommen ist. Ich stehe auf seiner Seite.";
			link.l1.go = "About_Fleetwood_1";
		break;
		
		case "About_Fleetwood_1":
			dialog.text = "Sehr gut. Kapitän Richard Fleetwood von der Royal- ich meine Commonwealth Marine... verdammt, ich vergesse immer wieder, dass dieser Fanatiker Cromwell an der Macht ist und den Namen geändert hat. Unabhängig davon, Fleetwood ist ein guter Kämpfer und ein erfahrener Seemann. Er kommandiert eine Brigg namens 'Valkyrie' - ein hervorragendes Schiff, möchte ich erwähnen, mit einer Besatzung aus Elite-Seemännern und Marinesoldaten. Er führt einen privaten Krieg gegen die Vereinigten Provinzen im Allgemeinen und gegen die Niederländische Westindien-Kompanie im Besonderen. Er hat unzählige niederländische Handelsschiffe geplündert und die Versicherungskosten in die Höhe getrieben. Der Gouverneur von Curacao hat eine Rekordprämie auf seinen Kopf ausgesetzt.";
			link.l1 = "Hmm... Scheint ein bisschen ungewöhnlich für einen Offizier der 'Commonwealth Marine' zu piraten...";
			link.l1.go = "About_Fleetwood_2";
		break;
		
		case "About_Fleetwood_2":
			dialog.text = "Ja, tatsächlich. Er balanciert auf einem Drahtseil. Die Engländer erkennen seine Handlungen offiziell nicht an und weigern sich, irgendetwas damit zu tun zu haben, aber sie ermutigen ihn tatsächlich hinter den Kulissen. Ich habe Gründe zu vermuten, dass er irgendwie mit dem englischen Spionagering in der Karibik verbunden ist, und mit diesen Schurken ist nicht zu spaßen";
			link.l1 = "Ein ernsthafter Mann... Ist das alles? Hercule hat mir von einem seiner Assistenten erzählt... einem anderen Charlie... wie war sein Name... Dose? Kanonenkugel?";
			link.l1.go = "About_Fleetwood_3";
		break;
		
		case "About_Fleetwood_3":
			dialog.text = "Knippel? Ja, es gibt einen solchen Kerl. Charlie Knippel war einst ein Meisterkanonier in der englischen Marine, jetzt im Ruhestand. Jetzt führt er ein ruhiges Leben am Ufer. Er ist Fleetwoods Augen und Ohren in St. John's, also sei vorsichtig mit ihm und denke nicht einmal daran, ihn über Richard auszufragen - du wirst im Gefängnis landen oder schlimmer.";
			link.l1 = "Ich verstehe. Können Sie mir noch etwas anderes erwähnenswertes über Fleetwood erzählen?";
			link.l1.go = "About_Fleetwood_4";
		break;
		
		case "About_Fleetwood_4":
			dialog.text = "Ein Idol für alle Frauen auf Antigua von sechzehn bis sechzig. Scheint, das ist alles über ihn. Nun, ich denke, du weißt, was ihm jetzt passiert ist. Er bleibt im Bett und leckt seine Wunden.";
			link.l1 = "Er muss einige Schwachstellen oder Laster haben...";
			link.l1.go = "About_Fleetwood_5";
		break;
		
		case "About_Fleetwood_5":
			dialog.text = "Was meinst du?";
			link.l1 = "Nun, vielleicht spielt er gerne oder trinkt stark oder kann dem schönen Geschlecht nicht widerstehen - so etwas in der Art. Ist er verheiratet?";
			link.l1.go = "About_Fleetwood_6";
		break;
		
		case "About_Fleetwood_6":
			dialog.text = "Nein, ein Junggeselle. Was die Dinge, die Sie erwähnt haben - er ist für nichts davon bekannt.";
			link.l1 = "Ich verstehe. Aber vielleicht gibt es immer noch etwas Besonderes an ihm? Selbst eine Person wie er muss einige Schwachstellen haben!";
			link.l1.go = "About_Fleetwood_7";
		break;
		
		case "About_Fleetwood_7":
			dialog.text = "Ich weiß es nicht. Hör zu, lass es uns so machen. Komm in einer Woche zu mir, und ich werde Fleetwoods Privatleben untersuchen. Abgemacht?";
			link.l1 = "Abgemacht. Danke, John! Ich werde in einer Woche hier sein.";
			link.l1.go = "About_Fleetwood_8";
		break;
		
		case "About_Fleetwood_8":
			DialogExit();
			pchar.questTemp.HWIC.Self = "WaitFleetwood";
			SaveCurrentQuestDateParam("questTemp.Wait_Fleetwood");
			SetFunctionTimerCondition("Wait_FleetwoodQM", 0, 0, 7, false);
			SetFunctionTimerCondition("Wait_FleetwoodOver", 0, 0, 12, false);//чтобы не опаздывал
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", false);//открыть выход из аптеки
			AddQuestRecord("Holl_Gambit", "3-14");
		break;
		
		case "About_Fleetwood_9":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Ja, aber leider nicht viel. Und ich fürchte, es ist sowieso nicht viel wert.";
			link.l1 = "Spuck es aus! Jedes kleinste Detail ist sehr wichtig, wenn es etwas mit Fleetwood zu tun hat.";
			link.l1.go = "About_Fleetwood_10";
		break;
		
		case "About_Fleetwood_10":
			dialog.text = "Nicht so lange her hat Richard zwei jüdische Flüchtlinge von einer unbekannten Insel aufgesammelt - einen alten Mann und seine Tochter, die nach Willemstad segelten. Das Schiff, auf dem sie gesegelt waren, wurde von Piraten versenkt. Fleetwood brachte sie heimlich nach Curacao, riskierte seinen eigenen Hals. Seitdem sind mehrere Monate vergangen. Jetzt hat er seinen treuen Hund Charlie Knippel nach Willemstad geschickt...";
			link.l1 = "Hmm... Wie hängt das zusammen?";
			link.l1.go = "About_Fleetwood_11";
		break;
		
		case "About_Fleetwood_11":
			dialog.text = "Ich habe herausgefunden, dass Charlie den Auftrag bekommen hat, hier ein Mädchen aus Willemstad, eine Jüdin namens Abigail Shneur, zu liefern. Ja, das gleiche Mädchen von der Insel. Es sieht so aus, als ob Richard sich in sie verliebt hat, da er seinen besten Agenten für sie schickt.\nDas ist es. Ich weiß nicht, ob das überhaupt hilft.";
			link.l1 = "Oh ho ho! Hahaha! Es scheint, dass unser eingefleischter Junggeselle den schlauen Reizen der Jüdin erlegen ist. Das ist hervorragende Arbeit, John, danke! Wann wird unser Freund Knippel wohl nach Curacao aufbrechen?";
			link.l1.go = "About_Fleetwood_12";
		break;
		
		case "About_Fleetwood_12":
			dialog.text = "Er ist gestern abgereist.";
			link.l1 = "Und auf welchem Schiff?";
			link.l1.go = "About_Fleetwood_13";
		break;
		
		case "About_Fleetwood_13":
			dialog.text = "Ich wusste, dass Sie das fragen würden. Er ist auf einer Brigantine, die von der Gemeinschaft-ach zur Hölle damit, der 'Royal Navy', beauftragt wurde. Ihr Name ist 'Zeekalf'.";
			link.l1 = "'Zeekalf'? Das ist ein mächtig holländischer Name für ein englisches Schiff...ohhh, ich verstehe.";
			link.l1.go = "About_Fleetwood_14";
		break;
		
		case "About_Fleetwood_14":
			dialog.text = "Sie sind ein schneller Denker... Ihr früherer Name war 'Royal Mary', aber für diese Reise wurde sie 'Zeekalf' genannt. Und sie fährt unter der niederländischen Flagge.";
			link.l1 = "Deine Hilfe war unbezahlbar, John. Ich mache mich jetzt auf den Weg. Ich werde bald zurück sein und ich werde dein Zimmer im zweiten Stock benötigen, wo du mich untergebracht hast, während ich mich erholte.";
			link.l1.go = "About_Fleetwood_15";
		break;
		
		case "About_Fleetwood_15":
			dialog.text = "Was hast du vor?";
			link.l1 = "Ich erzähle dir alles, wenn ich zurück bin. Wünsch mir Glück, John! Auf Wiedersehen.";
			link.l1.go = "About_Fleetwood_16";
		break;
		
		case "About_Fleetwood_16":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-16");
			pchar.questTemp.HWIC.Self = "HuntKnippel";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("HuntKnippelOver", 0, 0, 10, false);
			pchar.quest.Hunt_Knippel.win_condition.l1 = "location";
			pchar.quest.Hunt_Knippel.win_condition.l1.location = "Curacao";
			pchar.quest.Hunt_Knippel.function = "CreateKnippelShip";
			LocatorReloadEnterDisable("SentJons_town", "houseH1", true);//закрыть хижину Чарли
			AddMapQuestMarkIsland("Curacao", true);
		break;
		
		case "About_Fleetwood_17":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-15");
			pchar.questTemp.HWIC.Self = "end";
			pchar.questTemp.HWIC.Detector = "self_fail";
			CloseQuestHeader("Holl_Gambit");
		break;
		
		case "Abigile":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Wirklich? Warum bist du dir so sicher?";
			link.l1 = "Weil Charlie am Meeresgrund die Fische füttert. Ich habe 'Zeekalf' geentert und Knippel zur Hölle geschickt. Natürlich habe ich ihn vorher befragt... Er hatte einen Brief bei sich, der es mir ermöglichte, mich als Knippel auszugeben, als ich mit unserer Jüdin Abigail sprach, der Liebsten unseres tapferen Richard.";
			link.l1.go = "Abigile_1";
		break;
		
		case "Abigile_1":
			dialog.text = "Hmm...Das ist klug. Also, du sagst, dass...";
			link.l1 = "Ja. Ich habe die Jüdin nach Antigua gebracht. Sie ist an Bord meines Schiffes. Jetzt habe ich einen Trumpf in meinem Kartenspiel mit Fleetwood! Er wird alles für sie tun...";
			link.l1.go = "Abigile_2";
		break;
		
		case "Abigile_2":
			dialog.text = "Bist du sicher? Es könnte sein, dass alles nicht so einfach ist, wie du es darstellst...";
			link.l1 = "Oh ja, ich bin absolut sicher. Aus dem Brief habe ich herausgefunden, dass Abigails Vater gegen ihre Ehe mit Richard wegen des Geldes war. Ich weiß, typischer jüdischer Schwiegervater. Also hat Fleetwood beschlossen, ihrem Vater eine Mitgift zu zahlen - 200000 Pesos! Sag mir jetzt, wie viele Mädchen auf der Welt sind so viel Geld wert?";
			link.l1.go = "Abigile_3";
		break;
		
		case "Abigile_3":
			dialog.text = "Heh! Sicherlich keine Jüdin! Ich habe in meinem Leben noch kein christliches Mädchen getroffen, das so viel wert ist, das ist sicher. "+pchar.name+", du bist ein gerissener Schurke. Was wirst du mit ihr machen?";
			link.l1 = "Ich werde die Jüdin hierher bringen und wir werden sie in deinem Zimmer behalten. Ich werde ihr sagen, dass Richard zur See gefahren ist und noch nicht zurückgekehrt ist, also wird sie eine Woche lang unser Gast sein. Sie denkt, ich sei Charlie Knippel.";
			link.l1.go = "Abigile_4";
		break;
		
		case "Abigile_4":
			dialog.text = "Das ist interessant. Also hast du beschlossen, das Mädchen in meinem Haus zu behalten? Hmm...";
			link.l1 = "John, sie ist eine Jüdin. Eine staatenlose Wanderin, gebracht aus einer holländischen Kolonie. Sie ist hier in St. John's niemand und niemand kennt sie. Seien Sie versichert, wir können tun, was wir wollen und sie wird es nicht wagen, ein Wort zu sagen. Sie hat keinen Pfennig oder Freund auf ihrem Namen. Und so oder so, sie wird nicht lange unser Gast sein. Ich werde Fleetwood mit ihr als Köder locken, und danach werden wir sie nicht mehr brauchen.";
			link.l1.go = "Abigile_5";
		break;
		
		case "Abigile_5":
			dialog.text = "Du fängst an, mir Angst zu machen, Charles. Du wirst dieses Mädchen doch nicht ausnutzen, oder? Oder sie zum selben Ende wie Knippel bringen?";
			link.l1 = "Nein, natürlich nicht. 'Gerissener Schurke' mag ich sein, aber ich bin kein Feind von schönen Mädchen - Jude oder Christin. Oder mit hässlichen, umso mehr. Wenn sie sich benimmt, werde ich sie nach all dem zu ihrem Vater nach Willemstad bringen. Der alte Geizkragen wird mir wahrscheinlich zu Füßen fallen und mich dafür danken, dass ich sie vor diesem perfiden Engländer gerettet habe.";
			link.l1.go = "Abigile_6";
			// belamour legendary edition -->
			link.l2 = "Sie hat eine Rolle in diesem Possenspiel zu spielen. Wenn das Spiel vorbei ist, werde ich sie nicht mehr brauchen.";
			link.l2.go = "Abigile_6a";
		break;
		
		case "Abigile_6a":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 60);
			dialog.text = "Ich verstehe, also muss ich vorerst auf sie aufpassen.";
			link.l1 = "Ich werde nicht darauf bestehen, Kumpel. Wenn du völlig dagegen bist, kann sie an Bord meines Schiffes bleiben. Aber dann muss ich sie zur Sicherheit in Eisen legen und sie im Frachtraum bei den Ratten halten, um sie vor meiner Crew zu schützen. Es ist für sie eine Neuheit, Frauen an Bord zu haben, weißt du. Es wäre eine Schande, ein so hübsches Mädchen so zu behandeln.";
			link.l1.go = "Abigile_7";
		break;
		
		case "Abigile_6":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 60);
			// <-- legendary edition
			dialog.text = "Ich verstehe, also muss ich vorerst auf sie aufpassen.";
			link.l1 = "Ich werde nicht darauf bestehen, Kumpel. Wenn du völlig dagegen bist, kann sie an Bord meines Schiffes bleiben. Aber dann muss ich sie zur Sicherheit in Eisen legen und sie im Laderaum bei den Ratten aufbewahren, um sie vor meiner Mannschaft zu schützen. Es ist für sie eine Neuheit, Frauen an Bord zu haben, weißt du. Es wäre eine Schande, ein so hübsches Mädchen so zu behandeln.";
			link.l1.go = "Abigile_7";
		break;
		
		case "Abigile_7":
			dialog.text = "Ich verstehe. Sehr gut, bring sie her. Es ist meine Pflicht, Ihnen im Kampf gegen Fleetwood zu helfen. Bring sie her und ich werde ihr 'Gästezimmer' vorbereiten.";
			link.l1 = "Danke dir, John. Ich wusste, dass ich mich auf dich verlassen könnte.";
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Self = "AbigileInCabin";
			DoQuestCheckDelay("SetAbigileToCabin", 1.0); // fix 180812
			AddQuestRecord("Holl_Gambit", "3-24");
			//поставим табурет
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "SentJons_HouseF3";
			sld.startLocator = "goto2";
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "Abigile_7_1":
			DelLandQuestMark(npchar);
			dialog.text = "Oh! Meine Freude. Ich freue mich, eine so wichtige und... eine elegante Frau zu begrüßen. Würden Sie bitte in den zweiten Stock gehen. Dort wartet Ihr Abendessen auf Sie und das Bett ist gemacht. Ich bin mir sicher, Sie werden nach einer so langen Reise gut schlafen wollen.";
			link.l1 = "Ja. Abigail ist sicherlich müde nach einer so langen Reise aus Willemstad.";
			link.l1.go = "Abigile_8";
		break;
		
		case "Abigile_8":
			DialogExit();
			sld = characterFromId("Abigile");
			sld.dialog.currentnode = "Abigile_kidnapping_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_9":
			dialog.text = "Haben Sie schon einen Plan?";
			link.l1 = "Ich mache das. Wir müssen einen Brief an Richard mit einer Lösegeldforderung für Abigail schreiben. Ein Treffen auf einer unbewohnten Insel arrangieren - wie auf den Turks. Und wenn er nicht einverstanden ist, dann werden wir, wie soll ich sagen, seine hebräische Geliebte in Stücken an ihn schicken.";
			link.l1.go = "Abigile_10";
		break;
		
		case "Abigile_10":
			dialog.text = "Was ist der Bedarf für solche Komplikationen mit einer unbewohnten Insel?";
			link.l1 = "Neutrales Gebiet. Es ist sicherer. Ich werde Abigail sowieso nicht mitbringen. Ich brauche Fleetwood. Er wird sicherlich einen Hinterhalt auf Antigua vorbereiten, aber auf den Turks wird er keinen solchen Vorteil haben.";
			link.l1.go = "Abigile_11";
		break;
		
		case "Abigile_11":
			dialog.text = "Gut genug. Wer wird den Brief übergeben? Es ist sehr gefährlich.";
			link.l1 = "Fremder. Wähle einen Trunkenbold aus der Taverne, einen, der zuverlässig aussieht. Sie sind bereit, alles zu tun, was du ihnen für etwas Rumgeld fragst. Wenn Richard ihn in einem Wutanfall tötet, schicken wir einen anderen. Und wir werden einen von Abis Fingern in den Brief einlegen. Das wird ihn viel gefügiger machen.";
			link.l1.go = "Abigile_12";
		break;
		
		case "Abigile_12":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "Mach dir keine Sorgen, John. Ich bin sicher, es wird nicht dazu kommen. Du musst nur einen Kurier finden und ich werde den Brief sofort verfassen. Hast du etwas Papier und Tinte?";
			link.l1.go = "Abigile_13";
		break;
		
		case "Abigile_13":
			dialog.text = "Ja, das tue ich. Und ich kenne auch einen passenden Säufer. Ich empfehle Jack Harrison. Er verbringt jeden Abend in der Taverne, tankt mit Rum auf. Sie werden ihn leicht genug finden.";
			link.l1 = "Gut, bring mir Feder und Tinte und ich werde das Lösegeldschreiben für Richard verfassen.";
			link.l1.go = "Abigile_14";
		break;
		
		case "Abigile_14":
			DialogExit();
			StartQuestMovie(true, false, true);
			locCameraFromToPos(0.07, 2.57, -2.46, true, -0.08, -0.38, 1.35);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "MC_writeLetter", -1);
		break;
		
		case "Abigile_15":
			dialog.text = "Wann wirst du ihm den Brief übergeben? Wirst du die Zustellung im Gange beobachten?";
			link.l1 = "Sicher. Richard ist kein Narr, aber ich bezweifle, dass er Risiken eingehen wird. Zumindest hoffe ich das. Ich will dem Mädchen nicht wehtun, aber ich werde es tun, wenn ich muss. Nun, es ist Zeit, den Säufer zu finden, den du erwähnt hast. Jack... wie war sein voller Name?";
			link.l1.go = "Abigile_20";
		break;
		
		case "Abigile_20":
			dialog.text = "Sein Name ist Jack Harrison. Er besucht normalerweise abends die Taverne. Sei vorsichtig!";
			link.l1 = "Alles wird gut. Warte auf mich.";
			link.l1.go = "Abigile_22";
		break;
		
		case "Abigile_22":
			DialogExit();
			LAi_SetOwnerType(npchar);
			pchar.questTemp.HWIC.Self = "LetterToDrunkardGo";
			AddDialogExitQuestFunction("CreateDrunckardInTavern");
			AddQuestRecord("Holl_Gambit", "3-25");
		break;
		
		case "Abigile_23":
			DelLandQuestMark(npchar);
			dialog.text = "Nun, ich würde das nicht sagen. Fleetwood ist listig und gefährlich. Darüber hinaus ist er ein Meisterschwertkämpfer und ein erfahrener Seemann. Er wird keine leichte Beute sein.";
			link.l1 = "Ich habe aufgehört, den einfachen Weg zu gehen, als ich in die Karibik kam. Nun, John, es ist Zeit für mich zu gehen. Übrigens, du hast erwähnt, dass unser tapferer Fleetwood ein gutes Schiff hat, nicht wahr?";
			link.l1.go = "Abigile_24";
		break;
		
		case "Abigile_24":
			dialog.text = "Er hat die feinste Brigg, die ich je gesehen habe. Und ich habe schon einige gesehen.";
			link.l1 = "Das ist gut. Ich mag feine Schiffe. Zeit, den Anker zu lichten!";
			link.l1.go = "Abigile_26";
		break;
		
		case "Abigile_26":
			DialogExit();
			pchar.questTemp.HWIC.Self = "FleetwoodToIsland";
			pchar.quest.Fleetwood_meetingShore.win_condition.l1 = "location";
			pchar.quest.Fleetwood_meetingShore.win_condition.l1.location = "Shore56";
			pchar.quest.Fleetwood_meetingShore.function = "InTerksShore";
			AddQuestRecord("Holl_Gambit", "3-28");
			AddMapQuestMarkShore("Shore57", false);
		break;
		
		case "Abigile_27":
			int iVal = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
				sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA) iVal = 1;
				}
			}//установили признак наличия Валькирии в эскадре.
			if (iVal != 0)
			{
				dialog.text = "Ich bin sprachlos! Eine ausgezeichnete Kombination, eine großartige Idee und meisterhafte Umsetzung! Meine Glückwünsche, "+pchar.name+"! Und es ist dir auch gelungen, seine Brigantine als Preis zu nehmen!";
				link.l1 = "Danke! Und wo ist Hercule? Ich würde ihn gerne sehen. Als wir uns zuletzt getroffen haben, hat er mir gesagt, dass ich ihn mit Ihrer Hilfe finden könnte.";
				link.l1.go = "Abigile_28";
			}
			else
			{
				dialog.text = "Eine ausgezeichnete Kombination, eine großartige Idee und meisterhafte Umsetzung! Meine Glückwünsche, "+pchar.name+"!";
				link.l1 = "Danke! Und wo ist Hercule? Ich würde ihn gerne sehen. Als wir uns zuletzt trafen, sagte er mir, dass ich ihn mit deiner Hilfe finden könnte.";
				link.l1.go = "Abigile_28";
			}
		break;
		
		case "Abigile_28":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Ich erwarte ihn jeden Moment. Er sollte hier durch den geheimen Tunnel kommen. Und du solltest dich bei Abigail erklären. Sie hat angefangen, sich über Richards Abwesenheit Sorgen zu machen.";
			link.l1 = "In Ordnung, aber sollten wir sie nicht nach Hause schicken?";
			link.l1.go = "Abigile_29";
		break;
		
		case "Abigile_29":
			dialog.text = "Noch nicht... Ich muss zuerst mit dir reden. Aber warte zuerst auf Hercule's Ankunft. Geh und tröste Abigail. Erzähl ihr eine Geschichte, erfinde etwas. Dann komm in den Keller. In Ordnung?";
			link.l1 = "Aye aye, John.";
			link.l1.go = "Abigile_30";
		break;
		
		case "Abigile_30":
			DialogExit();
			npchar.greeting = "merdok_4";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "SentJons_TownCave", "item", "berglar1", "", -1);
			pchar.questTemp.HWIC.Self = "AbigileLie";
			sld = characterFromId("Abigile");
			LAi_SetCitizenType(sld);
			AddLandQuestMark(sld, "questmarkmain");
			AddQuestRecord("Holl_Gambit", "3-34");
		break;
		
		case "Lucas":
			DelLandQuestMark(npchar);
			dialog.text = "Nun, die Zeit ist gekommen, die Karten auf den Tisch zu legen. Wie Sie bereits herausgefunden haben, bin ich nicht nur ein einfacher Apotheker. Mein richtiger Name ist Johan van Merden und bis vor kurzem war ich ein Agent für die Niederländische Westindien-Kompanie und die rechte Hand ihres Vizepräsidenten Lucas Rodenburg.";
			link.l1 = "Wirklich! Das ist interessant...";
			link.l1.go = "Lucas_1";
		break;
		
		case "Lucas_1":
			dialog.text = "Es ist jetzt anders. Lucas möchte das Spiel verlassen und in die Niederlande zurückkehren, also muss er alles und jeden begraben, der mit seiner Vergangenheit verbunden ist\nIch denke, dass ich nur noch wegen meiner Archive atme, die alle Informationen über Lucas's Verbrechen enthalten... wie die Geschichte des 'Geisterschiffs', das nur ein gewöhnliches Piratenschiff unter dem Kommando des rücksichtslosen und prinzipienlosen Abschaums Jacob van Berg ist. Rodenburg hat den Mann angeheuert, um englische Handelsschiffe zu plündern und zu versenken\nVan Berg ist auch verantwortlich für das Versenken der Fluyt mit Abigail und ihrem Vater an Bord. Abigail ist eine wichtige Figur in diesem Spiel, Rodenburg wollte auch ihre Hand und ihr Herz, genau wie Fleetwood, also war ich ziemlich überrascht, als du sie hierher gebracht hast...";
			link.l1 = "Rodenburg...das ist der Schwiegersohn, von dem Abigails exzentrischer Vater gesprochen hatte!";
			link.l1.go = "Lucas_2";
		break;
		
		case "Lucas_2":
			dialog.text = "Ja, deswegen möchte ich, dass sie hier bleibt. Sie könnte mein letztes Ass im Spiel gegen Rodenburg sein, obwohl ich sie lieber nicht weiter benutzen möchte, sie ist ein gutes Mädchen, ich möchte nicht, dass sie leidet. Ich denke, Lucas würde mein Archiv statt sie wählen, wenn die Wahl gestellt würde.\nAlso, ich schlage vor, dass du mein Verbündeter im Spiel gegen Lucas wirst... werde ihn los, benutze alle notwendigen Mittel. Die Belohnung wird beträchtlich sein.";
			link.l1 = "Hmm... Ich denke nicht, dass es schwieriger sein wird als mit Fleetwood. ";
			link.l1.go = "Lucas_3";
		break;
		
		case "Lucas_3":
			dialog.text = "Nein, du liegst falsch. Am Ende war Fleetwood ein Einzelgänger, der auf eigene Faust handelte. Rodenburg ist Vizepräsident der Gesellschaft. Er ist ein sehr einflussreicher Mann, nur der Gouverneur von Curacao hat mehr Macht. Jacob van Berg ist sein Agent, ein sehr gefährlicher Mann. Lucas sitzt auf seinem Hintern in Willemstad unter dem Schutz der Wachen der Gesellschaft, sie sind genauso gut wie Fleetwoods Männer.\nDas wird nicht einfach sein.";
			link.l1 = "Die Regeln des Spiels sind die gleichen - einen Tiger aus seiner Höhle zu locken... Ich habe bereits einen Plan. Was können Sie mir sonst noch über Lucas erzählen?";
			link.l1.go = "Lucas_4";
		break;
		
		case "Lucas_4":
			dialog.text = "Nun, ich habe Ihnen fast alles erzählt. Er besitzt ein schnelles Schiff namens 'Meifeng' - Schöner Wind. Ihr Kapitän ist ein Chinese namens Longway - Rodenburgs getreuer Mann. Er ist auch ein Feind, dem Sie nicht begegnen möchten. In Lucas' Crew gibt es keine Amateure. ";
			link.l1 = "Wir hatten von Anfang an einen Trumpf im Ärmel - dein Archiv. Wenn er sein Leben mehr schätzt als die Jüdin, wird er alles tun, um die Informationen im Archiv geheim zu halten... Aber... existiert das Archiv wirklich, John? Bluffst du?";
			link.l1.go = "Lucas_5";
		break;
		
		case "Lucas_5":
			dialog.text = "Das Archiv existiert. Und Lucas weiß davon. Haben Sie schon etwas herausgefunden?";
			link.l1 = "Ich habe. John, wenn du wirklich der Agent der Firma warst, solltest du etwas wissen.";
			link.l1.go = "Lucas_6";
		break;
		
		case "Lucas_6":
			dialog.text = "Was genau? Frag mich.";
			link.l1 = "Ich muss ein Schiff der Gesellschaft abfangen. Vorzugsweise ein unbegleitetes Schiff - ein Kurier oder so etwas. Können Sie mir diesbezüglich etwas sagen?";
			link.l1.go = "Lucas_7";
		break;
		
		case "Lucas_7":
			dialog.text = "Hm... Ich besitze solche Informationen nicht. Warte! Ich weiß sicher, dass die Kompanie einmal im Monat ein Paketschiff auf den Seewegen zwischen Philipsburg und Willemstad hat. Sie liefert Geschäftspapiere. Sie ist eine Brigantine namens 'Hoop'.\nSie wird heute oder morgen Philipsburg verlassen.";
			link.l1 = "Aye, das ist es! Alles, was ich brauche, um zu den Ufern von Saint Christopher zu gelangen. Die Seeroute nach Curacao führt direkt vorbei.";
			link.l1.go = "Lucas_8";
		break;
		
		case "Lucas_8":
			dialog.text = "Viel Glück, "+pchar.name+". Ich werde dich nicht nach den Einzelheiten deines Plans fragen. Ich werde auf deine Rückkehr warten!";
			link.l1 = "Alles wird gut, John. Kümmere dich um die Jüdin und behandle sie gut!";
			link.l1.go = "Lucas_9";
		break;
		
		case "Lucas_9":
			DialogExit();
			RemoveItems(PChar, "MC_Letter", 1);
			GiveItem2Character(pchar, "MC_Letter");
			ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter2");
			AddQuestRecordInfo("LetterToLucas", "1");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);
			pchar.questTemp.HWIC.Self = "LetterToLucas";
			sld = characterFromId("Tonzag");
			sld.dialog.currentnode = "Tonzag_hired";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddQuestRecord("Holl_Gambit", "3-36");
			//установим таймер на генерацию энкаунтера
			pchar.quest.HWIC_Cureer.win_condition.l1 = "Timer";
			pchar.quest.HWIC_Cureer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.HWIC_Cureer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.HWIC_Cureer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.HWIC_Cureer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.HWIC_Cureer.function = "CreateHWICCureerOnMap";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("HWICCureerOnMapOver", 0, 0, 16, false);//таймер
		break;
		
		case "Lucas_10":
			dialog.text = "Unglaublich! Ich kann meinen Ohren nicht trauen! Wie ist das passiert?";
			link.l1 = "Ich habe das Paketschiff erobert und im Namen von Fleetwood einen Brief an Lucas geschickt, in dem ich erklärte, dass ich in den Besitz eines bestimmten Archivs gekommen bin, das einem Apotheker aus St. John's gehörte, und dass bald die Beweise für jede seiner Missetaten von hier bis Amsterdam und London bekannt werden. Ich erwartete, dass er anfängt, mich zu jagen, aber es stellte sich anders heraus.";
			link.l1.go = "Lucas_11";
		break;
		
		case "Lucas_11":
			dialog.text = "";
			link.l1 = "Lucas beschuldigte Matthias Beck des Verrats und des Umgangs mit den Engländern, sperrte ihn ein und nahm seinen Wohnsitz im Gouverneurspalast. Wahrscheinlich hat er den Kapitän der Brigantine beseitigt. Dann befahl er seinem treuen Chinesen von der Meifeng, das Schiff mit dem Direktor der Gesellschaft, Peter Stuyvesant, an Bord zu versenken!";
			link.l1.go = "Lucas_12";
		break;
		
		case "Lucas_12":
			dialog.text = "Rodenburg ist ein rücksichtsloser Mann. Aber selbst ich hätte nicht gedacht, dass er so weit gehen könnte...";
			link.l1 = "Ich habe die Meifeng erobert und Longway befragt. Er hat mir alles erzählt. Ich fand Stuyvesant und warnte ihn vor Rodenburgs Absichten und wir segelten zusammen nach Willemstad. Stuyvesant setzte Beck frei und verhaftete Lucas. Er ist jetzt im Gefängnis.";
			link.l1.go = "Lucas_13";
		break;
		
		case "Lucas_13":
			dialog.text = "Heh! Du hast wirklich Talent, mein Freund... Du solltest eine Karriere in der Kompanie-Marine oder als Politiker in den Vereinigten Provinzen anstreben - du hast alle Chancen, Gouverneur zu werden! Und was hast du mit Longway gemacht?";
			link.l1 = "Ich habe ihn gehen lassen. Er hat sich ehrenhaft ergeben, also habe ich ihm keinen Schaden zugefügt.";
			link.l1.go = "Lucas_14";
		break;
		
		case "Lucas_14":
			dialog.text = "Das ist gut. Longway ist ein guter Mann, im Gegensatz zu seinem ehemaligen Chef. Nun, "+pchar.name+", Sie haben großartige Arbeit geleistet! Ich werde Ihre Belohnung vorbereiten, aber ich werde etwas Zeit brauchen... In der Zwischenzeit...";
			link.l1 = "John, um die Wahrheit zu sagen, gibt es einen Haken. Sowohl Longway als auch Rodenburg haben mir gesagt, dass Jacob van Berg mich jagt. Wie schlimm ist das?";
			link.l1.go = "Lucas_15";
		break;
		
		case "Lucas_15":
			dialog.text = "Jacob van Berg? Charlie, das ist ernst. Er ist ein gnadenloser Pirat, ein geschickter Seemann und Kämpfer, der Fleetwood wie eine Hauskatze aussehen lässt. Ein professioneller Jäger. Er war derjenige, der auf Befehl von Rodenburg den Schiffsbetrieb zerstörte.\nEr wird dich finden, also musst du dich vorbereiten. Ich sollte auch Vorsichtsmaßnahmen treffen.";
			link.l1 = "Wie kann ich diesen van Berg finden?";
			link.l1.go = "Lucas_16";
		break;
		
		case "Lucas_16":
			dialog.text = "Ich weiß es nicht. Lucas und Longway waren die einzigen, die wussten, wo sie ihn finden konnten. Sei also vorsichtig und bereit\nIch mache den Laden dicht. Geh durch den Geheimtunnel, wenn du mich sehen willst. Und bring die Jüdin weg, es ist zu gefährlich für sie, hier zu bleiben.";
			link.l1 = "Mach dir keine Sorgen, John. Lass ihn auftauchen und ich werde mich um ihn kümmern. Wo ist Abigail?";
			link.l1.go = "Lucas_17";
		break;
		
		case "Lucas_17":
			dialog.text = "Sie ist in die Kirche gegangen. Es tut mir leid für sie. Sie war in letzter Zeit sehr aufgeregt.";
			link.l1 = "Nun...Das ist eine angenehme Überraschung. Vielleicht erkennt sie, dass Christus der Messias ist, den ihr Volk lange erwartet hat. Nun, es ist Zeit, sie zu ihrem Vater zurückzubringen.";
			link.l1.go = "Lucas_18";
		break;
		
		case "Lucas_18":
			dialog.text = "Sie wollte dich sehen. Ich bin sicher, dass sie dich bitten wird, sie nach Hause zurückzubringen.";
			link.l1 = "Abi, was?";
			link.l1.go = "Lucas_19";
		break;
		
		case "Lucas_19":
			dialog.text = "Nun, ich muss zugeben, dass wir Freunde geworden sind. Ich bereue nicht, dass sie in meinem Haus gelebt hat, und Gott sei Dank wird sie nie erfahren, warum sie hierher gebracht wurde.";
			link.l1 = "In Ordnung, John, ich gehe zur Kirche, um Abigail zu treffen. Dann gehe ich nach Willemstad.";
			link.l1.go = "Lucas_20";
		break;
		
		case "Lucas_20":
			DialogExit();
			sld = characterFromId("Abigile");
			AddLandQuestMark(sld, "questmarkmain");
			ChangeCharacterAddressGroup(sld, "SentJons_church", "goto", "goto1");//Аби - в церковь
			AddQuestRecord("Holl_Gambit", "3-56");
			pchar.questTemp.HWIC.Self = "AbiReturnHome";
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//закрыть аптеку
		break;
		
		case "Final":
			dialog.text = "Du... hast seine Nüsse geknackt? Oh - eine Metapher. Nun, Nüsse oder keine Nüsse, du hast es geschafft! Gratulation!";
			link.l1 = "Ich würde dich nicht belügen, heh. Jetzt kannst du frei atmen, John.";
			link.l1.go = "Final_1";
		break;
		
		case "Final_1":
			dialog.text = "Endlich! Ich glaube, es ist besser, all diese politischen Spiele und Intrigen aufzugeben. Jetzt ist es an der Zeit, über Ihre Belohnung für die Arbeit zu sprechen.";
			link.l1 = "Nun, das würde ich sicherlich schätzen.";
			link.l1.go = "Final_2";
		break;
		
		case "Final_2":
			dialog.text = "Ich werde die Karibik für immer verlassen. Als Dank für deine Hilfe und dafür, dass du mich aus Rodenburg gerettet hast, übereigne ich dir die Besitzurkunden für dieses Haus und meine Apotheke. Sie gehören jetzt dir. Nimm die Schlüssel.";
			link.l1 = "Das ist großartig! Ich bin ziemlich glücklich. Sie haben ein sehr gemütliches Haus und einen behaglichen Keller...";
			link.l1.go = "Final_3";
		break;
		
		case "Final_3":
			GiveItem2Character(pchar, "Drugstore_keys");//ключ
			dialog.text = "Und bitte akzeptieren Sie auch diese bescheidene Summe von 100.000 Pesos und dieses Musket. Es hat mir einst treu gedient, und es wird Ihnen auch gut dienen.";
			link.l1 = "Ich lehne solche Geschenke nicht ab!";
			link.l1.go = "Final_4";
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", false);//открыть аптеку
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload3", false); // открыть комнату
			pchar.quest.Jino_Door.win_condition.l1 = "locator";
			pchar.quest.Jino_Door.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Jino_Door.win_condition.l1.locator_group = "reload";
			pchar.quest.Jino_Door.win_condition.l1.locator = "reload4";
			pchar.quest.Jino_Door.function = "OpenRoomDoor";//на локатор комнаты Джино
			Achievment_Set("ach_10");
		break;
		
		case "Final_4":
			AddMoneyToCharacter(pchar, 100000);
			GiveItem2Character(pchar, "mushket2");
			dialog.text = "In dem Raum oben finden Sie einen jungen Naturphilosophen. Er ist der beste Apotheker, den ich kenne. Er hat diese Mischungen hergestellt, die Ihnen geholfen haben, sich innerhalb weniger Tage zu erholen. Kümmern Sie sich um seine Bezahlung und sein Wissen wird alle Ihre Kosten mit Zinsen ausgleichen.";
			link.l1 = "Mein eigener persönlicher Bücherwurm? Sehr gut, ich werde mich um ihn kümmern.";
			link.l1.go = "Final_5";
		break;
		
		case "Final_5":
			dialog.text = "Ich muss jetzt auf Wiedersehen sagen. Ich gehe in den Keller, um meine Sachen zu packen. Morgen werde ich nicht mehr hier sein - ich segle weg von Antigua. Ich bin froh, dass ich dich getroffen habe und ich bin froh, dass du auf meiner Seite und nicht bei meinen Feinden warst.";
			link.l1 = "Ich freue mich auch, dich zu treffen, John. Vielleicht treffen wir uns wieder ...";
			link.l1.go = "Final_6";
		break;
		
		case "Final_6":
			dialog.text = "Nicht in diesem Leben, mein Freund. Ich werde packen. Auf Wiedersehen, "+pchar.name+"!";
			link.l1 = "Auf Wiedersehen, John! Viel Glück für dich!";
			link.l1.go = "Final_7";
		break;
		
		case "Final_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
			npchar.lifeday = 0;
			pchar.questTemp.HWIC.Self = "final";
			AddQuestRecord("Holl_Gambit", "3-64");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Detector = "self_win";
		break;
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = "Ach, guter Herr, hören Sie nicht auf dieses dumme Gerede. Da ist niemand. Da ist mein Labor, Mischungen werden vorbereitet, wissen Sie...";
			link.l1 = "Aller Scherz beiseite, John. Sagt dir der Name Gino Gvineili etwas?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Hmm...";
			link.l1 = "Aha! Ich kann es in deinen Augen sehen - ich habe recht... Dort lebt er und für wen er seine Kräuter vorbereitet!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Herr, ich sage Ihnen noch einmal - hier ist niemand.";
			link.l1 = "Lassen wir die Ausreden beiseite, John. Ich werde deinem Alchemisten nichts antun - aber wenn Vater Vincento aus Santiago ihn findet, kann ich nicht sicher sein. Der Inquisitor plant bereits, seine 'Domini Canes' nach Antigua zu schicken...";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Was willst du von ihm?";
			link.l1 = "Nur zum Reden. Er hat sehr wichtige Informationen für mich. Ich verspreche, dass ich ihn nicht der Inquisition übergeben und ihm in keiner Weise Schaden zufügen werde.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Gino ist ein netter Kerl. Glaube nichts, was Vater Vincento dir über ihn erzählt hat. Und denke daran - ich werde für meinen Alchemisten einstehen.";
			link.l1 = "Ich habe dir mein Wort gegeben. Ist das nicht genug für dich?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Geh dann nach oben. Die Tür ist offen. Und hoffe, dass du deinem Wort treu bleibst.";
			link.l1 = "Seien Sie versichert, ich werde.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			DialogExit();
			pchar.questTemp.Guardoftruth = "jino1";
			AddQuestRecord("Guardoftruth", "36");
			LocatorReloadEnterDisable(pchar.location, "reload4", false);
		break;
		
		// алхимический набор
		case "alchemy":
			dialog.text = "Kapitän, möchten Sie nicht mit den hermetischen Künsten vertraut werden? Dies könnte für Sie ziemlich nützlich sein.";
			link.l1 = "Es tut mir leid, aber meine Beschäftigung ist etwas anders. Ich bin es gewohnt, einen Schwertgriff in meiner Hand zu halten - keine Flaschen oder Reagenzgläser.";
			link.l1.go = "alchemy_exit";
			link.l2 = "'Es gibt mehr Dinge im Himmel und auf Erden, als in deiner Philosophie geträumt wird.' Natürlich würde ich gerne. Was wird benötigt?";
			link.l2.go = "alchemy_1";
			npchar.quest.alchemy = true;
		break;
		
		case "alchemy_exit":
			dialog.text = "Wie du wünschst. Ich habe nur angeboten...";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "alchemy_1":
			dialog.text = "Sie sollten lernen, Kräuter mit Ihren eigenen Händen zu mischen. Aber ohne ein Alchemisten-Set wird Ihnen das nicht gelingen. Schauen Sie sich diese Tasche an. Hier ist alles, was ein angehender Alchemist braucht - Reagenzgläser, Flaschen, eine Destille, Spatel, Glasröhren, ein Brenner und viel ähnliches Zeug...";
			link.l1 = "Sehr interessant! Und was kann ich damit zubereiten?";
			link.l1.go = "alchemy_2";
		break;
		
		case "alchemy_2":
			dialog.text = "Nun, Sie werden nicht in der Lage sein, Blei in Gold zu verwandeln, aber Sie werden in der Lage sein, Zutaten nach verschiedenen Rezepten zu mischen und so Tränke und andere nützliche Dinge zu erhalten.";
			link.l1 = "Rezepte?";
			link.l1.go = "alchemy_3";
		break;
		
		case "alchemy_3":
			dialog.text = "Stimmt. Du musst ein Rezept kennen, um einen Trank oder einen Gegenstand zu machen. Rezepte können von Händlern gekauft oder überall gefunden werden. Sobald du ein Rezept studiert hast, solltest du jeden benötigten Bestandteil sammeln und genau das tun, was dort geschrieben steht\n Nutze deine Alchemiewerkzeuge, finde oder kaufe Mörser und Stößel, suche nach einem Tiegel, leider habe ich keinen extra, um ihn dir zu geben. Kräuter, Spirituosen, Tränke, Mineralien, Abfall - alles wird tun, solange du das richtige Rezept und die Werkzeuge hast.";
			link.l1 = "Sehr interessant. Und wie viel verlangst du für dieses Set?";
			link.l1.go = "alchemy_4";
		break;
		
		case "alchemy_4":
			dialog.text = "Zwanzigtausend Pesos. Dies ist ein sehr gutes Set und es wird seine Kosten sehr schnell decken.";
			link.l1 = "Du machst dich über mich lustig, nicht wahr? Eine Handtasche mit Glaswaren zum Preis einer Schaluppe? Nein, ich verzichte.";
			link.l1.go = "alchemy_exit";
			if (sti(pchar.money) >= 20000)
			{
				link.l2 = "Ich stimme zu. Ich denke, es wird interessant sein, zu versuchen, etwas mit meinen eigenen Händen zu machen.";
				link.l2.go = "alchemy_5";
			}
		break;
		
		case "alchemy_5":
			AddMoneyToCharacter(pchar, -20000);
			Log_Info("You've got the alchemist's kit.");
			GiveItem2Character(pchar, "alchemy_tool");
			PlaySound("interface\important_item.wav");
			dialog.text = "Sie werden diesen Kauf nicht bereuen, da bin ich mir absolut sicher. Es ist definitiv profitabler, Tränke selbst zu machen, wenn Sie sie brauchen, anstatt die Stände der Kräuterhändler zu besuchen, um alles Stück für Stück zu kaufen. Außerdem wird es nicht immer möglich sein, alles zu kaufen, was Sie brauchen. ";
			link.l1 = "Lass uns lernen. Ich glaube, ich kann es schaffen!";
			link.l1.go = "alchemy_6";
		break;
		
		case "alchemy_6":
			DialogExit();
			PlaySound("interface\notebook.wav");
			Log_Info("In order to make your own herbs and amulets you must have the Alchemy skill!");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Du bist ein "+GetSexPhrase("Dieb, Herr! Wachen, nehmt ihn","Dieb, Mädchen! Wachen, nehmt sie")+"!!!","Schau nur! Kaum war ich in Gedanken versunken, hast du beschlossen, meine Truhe zu überprüfen! Fang den Dieb!!!","Wachen! Raub! Schnappt den Dieb!!!");
			link.l1 = "Verdammt!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
