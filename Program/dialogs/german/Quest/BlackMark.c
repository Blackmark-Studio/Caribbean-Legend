void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, n;
	string sTemp, sStr, sStr2, sGun, sBullet, attrL;
	
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
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Was wollen Sie?";
			link.l1 = "Nichts.";
			link.l1.go = "exit";
		break;
		
		case "BM_Contra_1":
			dialog.text = "Wer bist du und was zum Teufel machst du hier?!";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "Ruhig, Kamerad. Ich gehe nur vorbei. Ich werde mich nicht in eure... was auch immer das ist, einmischen.";
			}
			else
			{
				link.l1 = "Eh? Ist dieser Leuchtturm Ihrer? Beim nächsten Mal, hängen Sie ein Schild mit Ihrem Namen an eine der Palmen oder bauen verdammt nochmal einen Zaun.";
			}
			link.l1.go = "BM_Contra_2";
			DelLandQuestMark(npchar);
		break;
		
		case "BM_Contra_2":
			if (sti(pchar.reputation.nobility) >= 40)
			{
				dialog.text = "Verschwinde hier! Wenn du den Deal vermasselst, indem du einen Kunden verjagst, ich...";
			}
			else
			{
				dialog.text = "Hör zu, Bursche, zwing uns nicht, dich herauszufordern, um zu sehen, ob deine Klinge so scharf ist wie deine Zunge. Verschwinde einfach und...";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_BarbadosPatrolPribegaet");
		break;
		
		case "BM_Contra_3":
			dialog.text = "Nun, Frankie, welcher ist es?";
			link.l1 = "...";
			link.l1.go = "BM_Contra_3_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay12", "1", 1.9);
		break;
		case "BM_Contra_3_1":
			StartInstantDialog("BM_PatrolZhitel", "BM_Contra_4", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_4":
			dialog.text = "Nein... Verdammt, aber ich erkenne keines dieser Gesichter.";
			link.l1 = "...";
			link.l1.go = "BM_Contra_4_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay15", "1", 1.9);
		break;
		case "BM_Contra_4_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_5", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_5":
			dialog.text = "Was?! Bist du sicher?";
			link.l1 = "...";
			link.l1.go = "BM_Contra_5_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolZhitel"));
		break;
		case "BM_Contra_5_1":
			StartInstantDialog("BM_PatrolZhitel", "BM_Contra_6", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_6":
			dialog.text = "Denkst du, ich bin blind?! Ich sage dir, wha...";
			link.l1 = "...";
			link.l1.go = "exit";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
			CharacterTurnByChr(CharacterFromID("BM_PatrolOff"), CharacterFromID("BM_PatrolZhitel"));
			AddDialogExitQuest("BM_BarbadosMayakVystrel");
		break;
		
		case "BM_Contra_7":
			dialog.text = "Was zum Teufel?!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_7_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay9", "1", 1.9);
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_7_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_8", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_8":
			dialog.text = "Wer hat geschossen?!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_8_1";
			locCameraFromToPos(-84.11, 6.33, -62.68, true, -78.07, 3.20, -66.67);
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 1.9);
		break;
		
		case "BM_Contra_8_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_9", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_9":
			dialog.text = "Hältst du uns für Narren, Abschaum? Legt eure Waffen auf den Boden, alle von euch! Und du auch!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_9_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_9_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_10", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_10":
			dialog.text = "Halte doch deinen Zorn zurück, Offizier. Wir sind es nicht, siehst du nicht? Unsere Kanonen sind genau da, wo sie waren. Und fass deine bloß nicht an!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_10_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
		break;
		case "BM_Contra_10_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_11", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_11":
			dialog.text = "Du gibst mir Befehle, du Bastard?! Verhaftet sie alle, sofort!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_11_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_11_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_12", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_12":
			dialog.text = "Zum Teufel mit dir! Das wird nicht passieren. Jungs, zu den Waffen!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_BarbadosMayakBoinya");
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
		break;
		
		case "BM_Irons_1":
			dialog.text = "He, he, pass auf! Jemand könnte getötet werden, wenn du dieses Eisen so wild herumschwingst.";
			link.l1 = "Ha, wer?";
			link.l1.go = "BM_Irons_2";
			LAi_SetCurHPMax(npchar);
			SetOfficerToMushketer(npchar, "mushket1", true);
		break;
		
		case "BM_Irons_2":
			dialog.text = "Ich, natürlich.";
			link.l1 = "Was zum...? Wer zur Hölle bist du?";
			link.l1.go = "BM_Irons_4";
			link.l2 = "Das ist genau das, was ich versuche zu tun. Sollen wir?";
			link.l2.go = "BM_Irons_3";
		break;
		
		case "BM_Irons_3":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			npchar.MusketerDistance = 10;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "BM_Irons_4":
			if (startHeroType == 4)
			{
				dialog.text = "Ich bin Tommy! Tommy Irons. Ich denke. Wer bist du? Du bist eine tapfere Frau, sag ich dir, so herumzulaufen, hehehe.";
				link.l1 = "Mutig, in der Tat. Und ich habe keine Angst, dir den Mund zu stopfen, wenn ich muss. Es ist ein heißer Ort, also kleide ich mich leicht - nicht um dir oder deinesgleichen zu gefallen. Mein Name ist Helen MacArthur. Meine Freunde nennen mich vielleicht Rumba, aber du bist sicherlich nicht einer von ihnen. Und was sollte dieses 'Ich nehme an'?";
				link.l1.go = "BM_Irons_5";
			}
			else
			{
				dialog.text = "Ich bin Tommy! Tommy Irons. Ich denke. Und du?";
				link.l1 = ""+GetFullName(pchar)+". Und was genau bedeutet dieses 'Ich denke'?";
				link.l1.go = "BM_Irons_5";
			}
			LAi_SetCurHPMax(pchar);
		break;
		
		case "BM_Irons_5":
			dialog.text = "Das bedeutet genau das, was es bedeutet. Ich habe mein Gedächtnis verloren - wurde ziemlich übel in der Schlacht geschlagen. Du weißt, manchmal verlierst du alles. Ich habe Glück, allerdings. Ich habe nur meinen Namen vergessen. Glücklicherweise habe ich diesen Anhänger um meinen Hals, auf dem 'Thomas' steht. Aber ich bevorzuge Tommy. Und Irons. Ich habe für Cromwell in den Ironsides gekämpft, erinnere dich daran. Aber 'Ironsides' ist zu sperrig. Irons ist viel besser.";
			link.l1 = "Ich sehe, was mit dir los ist, Tommy. Also, sag mir - was war es? Hast du auf jemanden Bestimmtes gezielt? Hast du dein Ziel getroffen? Oder hast du nur zum Spaß geschossen? Ich wäre nicht überrascht.";
			link.l1.go = "BM_Irons_6";
		break;
		
		case "BM_Irons_6":
			dialog.text = "Ich habe zugeschlagen, und das heftig! In jeder Hinsicht. Erinnerst du dich an diesen feinen Pinkel? Er hat meine Spur verfolgt und Soldaten mitgebracht. Eine ganze Truppe, nur weil ich mit seiner Frau geschlafen habe.";
			link.l1 = "Du hast es wirklich getroffen, heh. Ich nehme an, er hat euch beide dabei erwischt?";
			link.l1.go = "BM_Irons_7";
		break;
		
		case "BM_Irons_7":
			dialog.text = "Ha! Du würdest es nicht glauben - nein. Die Dirne hat es später gestanden. Schuldgefühle, oder vielleicht hat es ihr nicht so viel Spaß gemacht wie mir, hehe. Wer weiß, was in den Köpfen von Frauen vorgeht? Es interessiert mich wirklich nicht, ha-ha-ha!";
			link.l1 = ""+GetSexPhrase("Hmm, sie ist eine seltsame.","Männer... Eines Augenblicks versucht ihr herauszufinden, was in unseren Köpfen vor sich geht, im nächsten sagt ihr, es wäre euch egal. Aber bei einer Sache habt ihr recht - was sie getan hat, war seltsam. Sie hätte einfach gehen und es wie einen schlechten Traum vergessen sollen. Das ist genau das, was ich tun würde, wenn es darauf ankommen würde.")+"";
			link.l1.go = "BM_Irons_8";
		break;
		
		case "BM_Irons_8":
			dialog.text = "Genau! Die Leute sagen, es stimmt etwas nicht mit mir. Ich bedauere die Soldaten, die gestorben sind. Ich weiß es, ich war selbst einmal nur ein Fußsoldat. Habe ich dir das nicht gesagt?";
			link.l1 = "Ja, das hast du. Von den Ironsides. Cromwell.";
			link.l1.go = "BM_Irons_9";
		break;
		
		case "BM_Irons_9":
			dialog.text = "Ach ja? Ich erinnere mich nicht, ob ich das getan habe oder nicht. Weißt du, wie ich in die Neue Welt gekommen bin? Soll ich es dir erzählen?";
			link.l1 = "Nein, und es würde mich nicht interessieren, Tommy.";
			link.l1.go = "BM_Irons_10";
		break;
		
		case "BM_Irons_10":
			dialog.text = "Es würde, es würde. Ich werde es dir sagen.";
			link.l1 = "In Ordnung, zur Hölle damit, schieß einfach. Ich meine, mach weiter.";
			link.l1.go = "BM_Irons_11";
		break;
		
		case "BM_Irons_11":
			dialog.text = "Unterbrich mich nicht, dann! Wo war ich? Richtig, also ich war verwundet, verstehst du? Habe meine offizielle Entlassung bekommen, weil ich auf der Gewinnerseite war. Aber du hättest die Gesichter dieser Schreibtisch-Ratten sehen sollen! Sie dachten, ich würde es vortäuschen, so tun als würde ich mein Gedächtnis verlieren. Sie fragten ständig nach meiner Familie.";
			link.l1 = "Nun, was hast du ihnen gesagt?";
			link.l1.go = "BM_Irons_12";
		break;
		
		case "BM_Irons_12":
			dialog.text = "Was habe ich ihnen gesagt? Ich habe ihnen gesagt, ich erinnere mich nicht. Und ich habe nicht gelogen - ich habe meine Leute nie gekannt. Ich wurde von den Straßen, von Arbeitern und Dienern in den Slums großgezogen. Ich habe mich der Revolution um ihretwillen angeschlossen. Obwohl die Undankbarkeit der Menschen erstaunlich ist - hätte ich einen Arm oder ein Bein verloren, wären sie gezwungen gewesen, einem Helden wie mir sofortige Pensionierung zu gewähren. Und nebenbei, ich habe fast meinen Kopf verloren, wörtlich!";
			link.l1 = "Nun, wie bist du in die Neue Welt gekommen, Kriegsheld?";
			link.l1.go = "BM_Irons_13";
		break;
		
		case "BM_Irons_13":
			dialog.text = "Zweifelst du daran? Für das einfache Volk zu kämpfen - was ist daran nicht heroisch? Ich hoffe, eines Tages werden Memmen wie du wissen, was wahre Freiheit ist!";
			link.l1 = "Obwohl Freiheit eine gute Sache ist, hast du es irgendwie wie eine Drohung klingen lassen. Also gut, Tommy, mach weiter.";
			link.l1.go = "BM_Irons_14";
		break;
		
		case "BM_Irons_14":
			dialog.text = "Ja. Nach dem Gewinn der Revolution erhielt ich meine Entlassung und stellte dann fest, dass ich nichts anderes konnte als schießen und Leuten ins Gesicht schlagen. Und man kann nicht wieder zur Armee zurückkehren - sie würden dich auslachen, besonders nachdem ich so hart für meine Entlassung gekämpft habe. Heh, es scheint mir, dass selbst wenn ich wirklich einen Arm oder ein Bein verloren hätte, die Schreibtischratten immer noch denken würden, ich würde sie irgendwo verstecken, um sie später wieder anzunähen, sobald ich meine Austrittspapiere bekommen hätte, ha-ha-ha!";
			link.l1 = "Das ist lustig. Aber du hast mir immer noch nicht erzählt, wie du hier gelandet bist.";
			link.l1.go = "BM_Irons_15";
		break;
		
		case "BM_Irons_15":
			dialog.text = "Ach, du bist so langweilig. Haben sie dir keine Geduld beigebracht, "+GetSexPhrase("Jüngling","mein Mädchen")+"? Ich hatte zu Hause nichts zu tun, außer Enten und Rehe zu schießen, also bin ich in die Neue Welt gegangen. Ich segelte für eine Weile zum Spaß mit Piraten, und als ich die Gesetzlosigkeit satt hatte, wurde ich Söldner.";
			link.l1 = "Nicht gerade eine originelle Geschichte.";
			link.l1.go = "BM_Irons_16";
		break;
		
		case "BM_Irons_16":
			dialog.text = "Vielleicht hast du einen besseren? Brauchst du zufällig einen Leibwächter? Denn du siehst... schwach aus. Ich befürchte, du wirst es nicht weit schaffen, hehe. Denk dran, es ist das Gefolge, das Könige macht. Und ein schlechtes Gefolge kann sie zu Fall bringen.";
			link.l1 = "Und welche Art von "+GetSexPhrase("König","Königin")+" würde ich mit einem Gefolge wie dir sein? "+GetSexPhrase("König","Königin")+" des Misthaufens?";
			link.l1.go = "BM_Irons_17";
		break;
		
		case "BM_Irons_17":
			dialog.text = "Nein, nein! Ich mache dir ein echtes Angebot, und du...";
			link.l1 = "Ich habe noch kein Angebot erhalten. Wie viel verlangst du für deine Dienste, Tommy?";
			link.l1.go = "BM_Irons_18";
		break;
		
		case "BM_Irons_18":
			dialog.text = "Zweihundertfünfzig Dublonen im Voraus! Damit ich weiß, dass du es ernst meinst und nicht nur ein Versager bist. Und danach eine monatliche Gebühr. Ich denke, wir können einen Deal machen.";
			link.l1 = "Und du tust nicht...";
			link.l1.go = "BM_Irons_19";
		break;
		
		case "BM_Irons_19":
			dialog.text = "... glaubst du, du hast den Mut? Heh, ich werde nicht einmal mit dir streiten - hast du gesehen, wie ich diesen Hahnrei vom Leuchtturm geschossen habe? Erster Schuss! Und auch kein Handeln, wenn das ist, was du denkst. Du musst zeigen, dass du dir einen Profi wie mich leisten kannst.";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Ja, das kann ich! Zweihundertfünfzig Goldstücke. Hier, nimm sie.";
				link.l1.go = "BM_Irons_Hire1";
			}
			link.l2 = "Du hattest Glück mit diesem Schuss. Und jetzt versuchst du, deinen Wert durch Prahlerei zu steigern. Ich kann auf einen Profi wie dich verzichten. Es ist zu viel Ehre und zu viel Geld.";
			link.l2.go = "BM_Irons_NoHire1";
			link.l3 = "Ich kann es mir gerade nicht leisten, da ich nicht so viel in meinen Taschen habe. Bleib hier und geh nirgendwo hin - Ich hole das Gold vom Schiff und komme zurück.";
			link.l3.go = "BM_Irons_Wait1";
		break;
		
		case "BM_Irons_Hire1":
			RemoveDublonsFromPCharTotal(250);
			
			dialog.text = "Du bist nicht so schlimm wie ich dachte! Aber du solltest besser dafür sorgen, dass ich mich nicht langweile. Es wäre eine Verschwendung meines Talents, nicht wahr? Tommy und "+pchar.name+"! Lasst uns die Karibik aufmischen!";
			link.l1 = "Lerne die Befehlskette zu respektieren, Tommy. Und zweitens, ich bin der Kapitän für dich. Verstanden?";
			link.l1.go = "BM_Irons_Hire2";
		break;
		
		case "BM_Irons_Hire2":
			dialog.text = "Heh, das tue ich, Kapitän Langweilig, "+GetSexPhrase("Herr","Fräulein")+".";
			link.l1 = "Oh, ich fange schon an, das zu bereuen...";
			link.l1.go = "Irons_hire";
		break;
		
		case "Irons_Hire":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			DeleteAttribute(npchar, "LifeDay");
			LAi_SetImmortal(npchar, false);
			npchar.quest.OfficerPrice = 15000;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			npchar.CanTakeMushket = true;
			pchar.questTemp.IronsItemsBlock = true;
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Irons_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			LAi_SetHP(npchar, 170.0, 170.0);
			
			// Костыли, нужно украсить интерфейс офицера ==>
			//RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			//TakeItemFromCharacter(npchar, "unarmed");
			//GiveItem2Character(npchar, "blade_42");
			//EquipCharacterByItem(npchar, "blade_42");
			//EquipCharacterByItem(npchar, "mushket1");
			//EquipCharacterByItem(npchar, "indian_2");
			// <== Костыли, нужно украсить интерфейс офицера
			
			if (CheckAttribute(pchar, "questTemp.BM_hireInGrot"))
			{
				AddQuestRecord("BlackMark", "4");
			}
			else
			{
				AddQuestRecord("BlackMark", "1");
			}
			
			// Продолжение через месяц в джунглях
			SetTimerCondition("BM_FirstJungle_Time", 0, 0, 14, false);
		break;
		
		case "BM_Irons_NoHire1":
			dialog.text = "Nun, du bist ein Idiot, junger "+GetSexPhrase("Mann","Frau")+"! Und völlig ohne Urteilsvermögen. Ich schlage vor, dass Sie das beheben, sonst werden Sie nicht lange durchhalten. Vor allem auf dem Archipel.";
			link.l1 = "Ich komme ohne dich klar, Tommy. Auf Wiedersehen.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsGoodbye");
		break;
		
		case "BM_Irons_Wait1":
			dialog.text = "Bist du ernsthaft? Hier ist gerade eine Gruppe Soldaten gestorben, Genie! Sie werden wahrscheinlich bald ein weiteres Bataillon schicken. Nein, ich könnte die Tür des Leuchtturms abschließen und eine Verteidigung organisieren, aber will ich das? Nein.";
			link.l1 = "Also, was schlagen Sie vor?";
			link.l1.go = "BM_Irons_Wait2";
		break;
		
		case "BM_Irons_Wait2":
			dialog.text = "Treffen Sie mich in einer Höhle im Dschungel. Ich gebe Ihnen ein paar Tage, um genug zu verdienen, um meine Dienstleistungen zu bezahlen - Sie wissen, wie man eine Klinge hält, vielleicht schaffen Sie es.";
			link.l1 = "Bist du ernst? Du wirst dort wie eine in die Ecke gedrängte Ratte sein.";
			link.l1.go = "BM_Irons_Wait3";
		break;
		
		case "BM_Irons_Wait3":
			dialog.text = "Nur wenn sie speziell nach mir suchen, mit einer großen Abteilung. Also denke ich, ich werde in Ordnung sein. Und jetzt muss ich gehen - sie werden bald hier sein. Bis später.";
			link.l1 = "Ja, ich muss auch gehen, nur für den Fall.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsToCave");
		break;
		
		case "BM_Irons_WaitInCave1":
			dialog.text = "Aye, da bist du ja! Ich fing schon an zu denken, du hättest es nicht in dir, Geld zu verdienen. Manchmal denke ich, Leute wie du werden damit geboren. Und wenn nicht, sterben sie in Armut, ohne jemals wie ehrliche Leute zu arbeiten.";
			link.l1 = "Nun, nun, Tommy. Wenn du meiner Crew nicht beitreten möchtest, dann tu es nicht. Ich sehe, du nistest gerne in diesem Loch.";
			link.l1.go = "BM_Irons_WaitInCave2";
			DelLandQuestMark(npchar);
		break;
		
		case "BM_Irons_WaitInCave2":
			dialog.text = "Offensichtlich hast du noch nicht in Gruben während der Regenzeit in Irland versteckt, "+GetSexPhrase("Jüngling","mein Mädchen")+"! Aber mit dir zu gehen ist besser als hier zu verstecken. Nun, über dieses Gold...";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Hier ist dein Gold.";
				link.l1.go = "BM_Irons_HireInCave1";
			}
			link.l2 = "Ich habe es noch nicht. Ich dachte, ich schaue nach, ob du irgendwo anders hingelaufen bist.";
			link.l2.go = "BM_Irons_NoHireInCave1";
		break;
		
		case "BM_Irons_HireInCave1":
			RemoveDublonsFromPCharTotal(250);
			pchar.quest.BM_IronsTimeOver.over = "yes";
			pchar.questTemp.BM_hireInGrot = true;
			
			dialog.text = "Jetzt reden wir! Was machen wir als nächstes... Kapitän?";
			link.l1 = "Zuerst einmal, lass uns aus diesem feuchten Ort herauskommen, oder ich fange an zu niesen.";
			link.l1.go = "BM_Irons_HireInCave2";
		break;
		
		case "BM_Irons_HireInCave2":
			dialog.text = "Oh, du solltest Krieg versuchen. Ich fühle mich fast wie zu Hause an Orten wie diesem.";
			link.l1 = "Ich sehe, also hast du deine Entlassung bekommen und hast den Respekt und die Unterordnung vergessen, eh, Tommy? Mach dir keine Sorgen, ich werde nicht zögern, dir erneut zu unterrichten, wenn ich muss. Jetzt gehen wir.";
			link.l1.go = "Irons_hire";
		break;
		
		case "BM_Irons_NoHireInCave1":
			NextDiag.TempNode = "BM_Irons_WaitInCave3";
			
			dialog.text = "Heh, Tommy Irons läuft nie davon! Er hält sein Wort. Wirst du deins halten?";
			link.l1 = "Darbeitend darauf.";
			link.l1.go = "Exit";
		break;
		
		case "BM_Irons_WaitInCave3":
			dialog.text = "Hast du das Gold mitgebracht?";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Hier ist dein Gold.";
				link.l1.go = "BM_Irons_HireInCave1";
			}
			link.l2 = "Ich habe es noch nicht. Ich dachte, ich überprüfe, ob du irgendwo anders hingelaufen bist.";
			link.l2.go = "BM_Irons_NoHireInCave1";
		break;
		
		case "BM_IronsJungleUhodit":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			
			sld = characterFromID("Irons");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			sld.lifeday = 0;
			LAi_CharacterDisableDialog(sld);
			GiveItem2Character(sld, "blade_42");
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			//LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			AddQuestRecord("BlackMark", "5");
			AddQuestUserData("BlackMark", "sSex1", GetSexPhrase("","а"));
			CloseQuestHeader("BlackMark");
		break;
		
		case "BM_IronsFirstJungle_1":
			dialog.text = "Hör zu, Kapitän...";
			link.l1 = "Was ist los, Tommy?";
			link.l1.go = "BM_IronsFirstJungle_2";
		break;
		
		case "BM_IronsFirstJungle_2":
			dialog.text = "Hätten Sie nicht eine zusätzliche Runde Munition bei sich? Nicht nur eine Kugel, sondern eine vollwertige, in Papier gewickelte Patrone.";
			link.l1 = "Ist das wieder einer deiner Witze? Ich gebe dir regelmäßig Kugeln und Patronen, was auch immer du brauchst. Und warum genau eine Patrone, nicht eine Handvoll?";
			link.l1.go = "BM_IronsFirstJungle_3";
		break;
		
		case "BM_IronsFirstJungle_3":
			dialog.text = "Warum nimmst du meinen Wunsch so übel? Ich frage nicht nach verfluchten Perlen, nur nach einer Patrone. Ich habe sogar gewartet, bis wir im Dschungel waren, um dich nicht von den Geschäften in der Stadt abzulenken. Also, hast du eine Patrone?";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
				link.l1 = "Ja, ich habe eine Runde. Hier, nimm sie. Mach nur keinen dummen Scherz mit dieser Kugel. Verstehst du, Tommy?";
				link.l1.go = "BM_IronsFirstJungle_7";
			}
			link.l2 = "Nicht im Moment, nein. Es ist nicht so, dass ich eine einzelne Patrone in meiner Tasche trage, und mich frage, was wäre, wenn Tommy danach fragt...?";
			link.l2.go = "BM_IronsFirstJungle_4";
		break;
		
		case "BM_IronsFirstJungle_4":
			dialog.text = "Nun, das ist ein guter Punkt, und du bist schnell im Begreifen, hehe. Aber ich fürchte, das ist der Punkt, an dem wir uns dann trennen.";
			link.l1 = "Bist du ernst? Du bist beleidigt über eine Kugel? Los, gehen wir zum Schiff und holen dort eine. Wenn du sie so dringend brauchst, besorge ich dir eine, zehn, so viele du brauchst.";
			link.l1.go = "BM_IronsFirstJungle_5";
		break;
		
		case "BM_IronsFirstJungle_5":
			dialog.text = "Nein. Du bist doch nichts Besonderes. Ein guter Kapitän kann seiner Mannschaft immer alles bieten, was sie braucht. Also gehe ich.";
			link.l1 = "Und wenn wir auf See wären, der Rum ausgegangen ist und du mehr willst? Würdest du das Beiboot losmachen und davonsegeln? Oder ins Wasser springen?";
			link.l1.go = "BM_IronsFirstJungle_6";
		break;
		
		case "BM_IronsFirstJungle_6":
			dialog.text = "Ha-ha-ha! Ich lachte, aber in diesem traurigen Moment wird selbst ein guter Witz nicht helfen. Auf Wiedersehen, Kapitän Langweilig.";
			link.l1 = "Nun, zur Hölle mit dir, Tommy. Auf Wiedersehen.";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsFirstJungle_7":
			dialog.text = "Kann nichts versprechen, heh-heh. Ein guter Witz hält die Stimmung aufrecht. Aber danke, natürlich.";
			link.l1 = "In Ordnung, los geht's, du Spaßvogel.";
			link.l1.go = "BM_IronsFirstJungle_8";
			TakeItemFromCharacter(pchar, "cartridge");
		break;
		
		case "BM_IronsFirstJungle_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			Return_IronsOfficer();
			SetTimerCondition("BM_SecondJungle_Time", 0, 0, 14, false);
		break;
		
		case "BM_IronsSecondJungle_1":
			dialog.text = "Hallo, Kapitän!";
			link.l1 = "Ja, Tommy?";
			link.l1.go = "BM_IronsSecondJungle_2";
		break;
		
		case "BM_IronsSecondJungle_2":
			dialog.text = "Hast du noch eine Papierpatrone?";
			link.l1 = "Was ist mit dem letzten passiert? Und was war der Witz mit der Patrone? Ich habe zwei Wochen auf irgendeinen dummen Witz von dir gewartet, aber nichts.";
			link.l1.go = "BM_IronsSecondJungle_3";
		break;
		
		case "BM_IronsSecondJungle_3":
			dialog.text = "Oh, es wird ein Killerwitz, vertrau mir. Du wirst es lieben, hehe. Hab's nur noch nicht ganz zusammen. Und was ist mit der Patrone?";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
				link.l1 = "Hier hast du. Ich hoffe, ich genieße wirklich deinen kommenden Streich. Und wo hast du die letzte Runde hingelegt? Ich gebe dir viele davon. Oder bewahrst du Munition für den Kampf an einem Ort und Scherze an einem anderen auf?";
				link.l1.go = "BM_IronsSecondJungle_7";
			}
			link.l2 = "Ich habe keine Munition für deine dummen Witze, Tommy! Du hättest vor zwei Wochen nach einer ganzen Ladung statt nur einer Patrone fragen können!";
			link.l2.go = "BM_IronsSecondJungle_4";
		break;
		
		case "BM_IronsSecondJungle_4":
			dialog.text = "Ich habe es getan! Ich dachte, dass wer sich auch immer als mein Kapitän bezeichnet, immer das behält, was seine Mannschaft benötigt.";
			link.l1 = "Ich gebe nichts vor, Tommy. Ich habe mich vor langer Zeit entschieden, ich selbst zu sein. Wer mit mir zurechtkommt, gut. Wenn nicht, auch gut.";
			link.l1.go = "BM_IronsSecondJungle_5";
		break;
		
		case "BM_IronsSecondJungle_5":
			dialog.text = "Heh, du und ich sind in dieser Hinsicht gleich. Aber ich habe gewisse Anforderungen an meinen Kapitän. Und du erfüllst sie nicht mehr, junger Mann. Hier trennen sich unsere Wege.";
			link.l1 = "Bist du ernst? Weil ich keine verdammte Papierpatrone hatte?";
			link.l1.go = "BM_IronsSecondJungle_6";
		break;
		
		case "BM_IronsSecondJungle_6":
			dialog.text = "Das kommt nicht in Frage. Normalerweise rate ich den Leuten, das zu tun, was sie mögen, und aus dem Leben zu nehmen, was sie wollen. Ich würde dir raten, in Zukunft mehr an deine Leute zu denken. Auf Wiedersehen.";
			link.l1 = "Und ich würde dir raten, auf deinen Kopf aufzupassen - sie haben mehr Schaden angerichtet als du denkst. Auf Wiedersehen, Tommy.";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsSecondJungle_7":
			dialog.text = "Du wirst es herausfinden. Alles zu seiner Zeit, hehe.";
			link.l1 = "Oh, ich habe ein schlechtes Gefühl bei dieser Sache, Tommy...";
			link.l1.go = "BM_IronsSecondJungle_8";
			TakeItemFromCharacter(pchar, "cartridge");
		break;
		
		case "BM_IronsSecondJungle_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			Return_IronsOfficer();
			SetTimerCondition("BM_ThirdJungle_Time", 0, 0, 14, false);
		break;
		
		case "BM_IronsThirdJungle_1":
			dialog.text = "Ich habe eine Frage an Sie, Kapitän.";
			link.l1 = "Aye, Tommy, was ist los?";
			link.l1.go = "BM_IronsThirdJungle_2";
		break;
		
		case "BM_IronsThirdJungle_2":
			dialog.text = "Du hast nicht geraten? Raten ist eine nützliche Fähigkeit, hehe. Du, ich, der Dschungel... Vor etwa zwei Wochen hatten wir dieses Gespräch. Ich brauche eine weitere Papierpatrone.";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
				link.l1 = "Das wird langsam zu einer lustigen Tradition, nicht wahr? Es sind zwei Wochen vergangen - Tommy bittet um eine Patrone. Bitte sehr. Wie viele mehr brauchst du für deinen Witz?";
				link.l1.go = "BM_IronsThirdJungle_5";
			}
			link.l2 = "Wie viel länger noch, Tommy?! Wie lange wird das noch so weitergehen? Bekommt ihr Eisenflanken vor jeder Schlacht nur eine Patrone?! Ich muss nicht ständig eine Runde bei mir haben für deine Macken, das weißt du!";
			link.l2.go = "BM_IronsThirdJungle_3";
		break;
		
		case "BM_IronsThirdJungle_3":
			dialog.text = "Eigentlich ist es als mein Kapitän deine Pflicht, mir alles zu liefern, was ich für Schlachten und mehr brauche.";
			link.l1 = "Du bist verwirrt, Tommy. Es ist deine Pflicht, den Befehlen deines Kapitäns zu gehorchen. Ich versorge euch immer mit allem - Medizin, Munition, Rum. Die Tatsache, dass du nicht rechtzeitig nimmst, was du brauchst, und dann wie ein Bettler handelst, ist allein deine Schuld!";
			link.l1.go = "BM_IronsThirdJungle_4";
		break;
		
		case "BM_IronsThirdJungle_4":
			dialog.text = "Du bist so klug - warum hast du hier bisher nichts bemerkenswertes erreicht? Ich sage dir warum. Weil du nicht vorausdenkst und nie auf irgendetwas vorbereitet bist. Du weißt nicht, was du tust, du Langweiler. Eine solche Person werde ich nicht als meinen Kommandanten anerkennen, also auf Wiedersehen.";
			link.l1 = "Und du benutzt überhaupt nicht deinen Kopf! Gott sei Dank, du verdammt großer Narr!";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsThirdJungle_5":
			dialog.text = "Das wird tun, hehe.";
			link.l1 = "Du hast es endlich zusammen, ja? Aber für was?";
			link.l1.go = "BM_IronsThirdJungle_6";
			TakeItemFromCharacter(pchar, "cartridge");
		break;
		
		case "BM_IronsThirdJungle_6":
			dialog.text = "Ich habe nur einen Scherz mit dir gemacht, um zu sehen, ob du wieder zu deinem mürrischen Selbst zurückkehrst. Hehe. Aber danke für die Patrone.";
			link.l1 = "Deine Witze sind seltsam, Tommy.";
			link.l1.go = "BM_IronsThirdJungle_7";
		break;
		
		case "BM_IronsThirdJungle_7":
			dialog.text = "That was a joke too. I wasn't collecting them; I was selecting them. Needed a cartridge that was close to perfect. This one will do. Yeah, with this round, the bullet will go far and true. Just like when I blew old Reasley's head off, ha-ha-ha!";
			link.l1 = "Alter Reasley, hast du gesagt... Frankie der Gehörnte, war es nicht? Der, den du am Leuchtturm erschossen hast? Also, ihr kennt einander schon lange, nicht wahr?";
			link.l1.go = "BM_IronsThirdJungle_8";
		break;
		
		case "BM_IronsThirdJungle_8":
			dialog.text = "Was? Oh, verdammt, das ist mir rausgerutscht. Aber das ist mir egal - Ich war noch nie gut im Lügen oder Geheimnisse bewahren.";
			link.l1 = "Ich nehme an, die zweite Kugel war für jemand Bestimmtes bestimmt, nicht wahr, Tommy?";
			link.l1.go = "BM_IronsThirdJungle_9";
		break;
		
		case "BM_IronsThirdJungle_9":
			dialog.text = "Richtig, Genie. Nun, ich kenne mich und meine Ziele, und ich schäme mich nicht. Deshalb ist es mir egal, was du denkst - ich erzähle dir die ganze Geschichte, warum zum Teufel nicht.";
			link.l1 = "Nun, erzähl mir dann. Es schadet nicht zu wissen, was du vorhast.";
			link.l1.go = "BM_IronsThirdJungle_10";
		break;
		
		case "BM_IronsThirdJungle_10":
			dialog.text = "Nun, unterbrich mich nicht, wie du es normalerweise tust. Es waren zwei Bastarde in der Kompanie mit mir - Francis Reasley und Gabriel Callow. Echte Ratten! Noch schlimmer als diese Schreibtisch-Ratten, die mir meinen Rücktritt nicht geben wollten, was, wie du weißt, nicht einfach zu bekommen war.";
			link.l1 = "Und was haben sie getan? Besonders der zweite, Callow. Hast du auch mit seiner Frau geschlafen? Und er hat auch Soldaten hinter dir hergeschickt?";
			link.l1.go = "BM_IronsThirdJungle_11";
		break;
		
		case "BM_IronsThirdJungle_11":
			dialog.text = "Halte deinen Mund, oder? Obwohl... ich würde es nicht übel nehmen, hehe. Aber nein. Die Royalisten haben uns an diesem Tag angegriffen. Auch Kavallerie. Es gab viel mehr von ihnen. Gabe und Frankie liefen wie geängstigte Hasen davon. Aber ich blieb bei den Jungs. Ich war der einzige, der überlebte. Ich habe vieles aus meiner Kindheit und Jugend vergessen, aber nicht das.";
			link.l1 = "Und du willst Rache, weil sie geflohen sind? Nicht jeder kämpft für eine Idee. Jeder will überleben. Oder fast jeder. Selbst wenn jemand für die Revolution kämpft, könnte er versehentlich beigetreten sein und es bereut haben.";
			link.l1.go = "BM_IronsThirdJungle_12";
		break;
		
		case "BM_IronsThirdJungle_12":
			dialog.text = "Ha, wenn ich jeden Feigling jagen würde, müsste ich die ganze Welt erschießen. Feiglinge, zur Hölle mit ihnen. Aber sie haben mich verraten. Sie haben allen erzählt, ich hätte die Revolution verraten und unsere ganze Kompanie auf Befehl der Anhänger des Königs abgeschlachtet. Ich habe dir etwas vorgelogen, Kapitän.";
			link.l1 = "Was ist los? Abgesehen davon, dass du gelogen hast, dass Frankie nur wegen dem, was du mit seiner Frau gemacht hast, auf dich Jagd macht?";
			link.l1.go = "BM_IronsThirdJungle_13";
		break;
		
		case "BM_IronsThirdJungle_13":
			dialog.text = "Nein, nein! Ich habe dich nicht angelogen, ich habe dir nur nicht alles erzählt. Da ist ein Unterschied. Wobei ich gelogen habe, war die Kündigung. Es gab keine Kündigung. Es gab ein Tribunal. Und der glückliche alte Tommy - sie entschieden, ihn nicht zu hängen, sondern ihn zu den Steinbrüchen in den südlichen Kolonien zu schicken. Genauer gesagt nach Barbados.";
			link.l1 = "Ja, das war Glück. Wie viele Jahre hast du dort gearbeitet?";
			link.l1.go = "BM_IronsThirdJungle_14";
		break;
		
		case "BM_IronsThirdJungle_14":
			dialog.text = "Keine. Seitdem das irdische Gericht mich wegen dieser Ratten verurteilt hat, hat das himmlische Oben beschlossen, mich zu retten. Sobald wir in den Archipel eingedrungen waren, spürten wir seine Atmosphäre - unser Schiff wurde von Piraten geentert.";
			link.l1 = "Also anstelle der Steinbrüche und Plantagen von Barbados wurdest du von Piraten in die Sklaverei verkauft? Aber du hast gesagt, du hast nie in den Steinbrüchen gearbeitet.";
			link.l1.go = "BM_IronsThirdJungle_15";
		break;
		
		case "BM_IronsThirdJungle_15":
			dialog.text = "Das habe ich gesagt - jemand da oben hat sich entschieden, mich zu retten. Was für eine Rettung es war, hehe! Du hast es richtig verstanden - die Piraten haben über diejenigen gesiegt, die es mögen, gefesselte und gekettete Männer zu missbrauchen. Aber es war immer noch ein heißer Kampf, so heiß wie die Sonne hier. Und unsere Retter erlitten einige Verluste. Deshalb boten sie jedem, der es wünschte, an, sich ihnen anzuschließen.";
			link.l1 = "Und bist du ihnen beigetreten? Du sagtest, du bist mit Piraten gesegelt.";
			link.l1.go = "BM_IronsThirdJungle_16";
		break;
		
		case "BM_IronsThirdJungle_16":
			dialog.text = "Verdammt ja! Die besten Jahre meines Lebens. Jack Mills war ein Kapitän mit einem großen K - Ich hoffe, du wirst eines Tages wie er sein. Ich segelte etwa zwei Jahre lang auf seiner 'Crane', bis...";
			link.l1 = "... bis du die Gesetzlosigkeit satt hattest, wie du gesagt hast? Warum sagst du, dass das die besten Jahre deines Lebens waren?";
			link.l1.go = "BM_IronsThirdJungle_17";
		break;
		
		case "BM_IronsThirdJungle_17":
			dialog.text = "Eh... bis ich von den beiden Verrätern hörte, die auch im Archipel gelandet sind. Ja, ich weiß, ich habe dir gesagt, dass ich die Piraterie auf hoher See und all das satt habe. Und ich habe dir schon gesagt, dass es mir egal ist, was du denkst. Das ist immer noch wahr, aber ich kannte dich nicht gut, als wir uns das erste Mal trafen. Wusste nicht, wie du reagieren würdest. Deshalb habe ich andere Dinge gesagt.";
			link.l1 = "Du bist ein Lügner, Tommy! Aber gut, warum hast du die 'Kran' verlassen?";
			link.l1.go = "BM_IronsThirdJungle_18";
		break;
		
		case "BM_IronsThirdJungle_18":
			dialog.text = "Weil Jack ein echter Anführer war, sagte er, er würde keinen Umweg für einen Mann machen, auf ihn warten, Rache spielen und sich mit hochrangigen Offizieren der britischen Marine anlegen, anstatt fette Handelsschiffe anzugreifen.";
			link.l1 = "Hochrangige Offiziere? Frank war ein Zivilist, denke ich.";
			link.l1.go = "BM_IronsThirdJungle_19";
		break;
		
		case "BM_IronsThirdJungle_19":
			dialog.text = "Eh, er war nicht immer einer. Er war immer irgendwie, weißt du, trüb. Und als er versuchte, jemanden reinzulegen, wurde er in Schande vertrieben. Er versuchte, auf einem Handelsschiff zu segeln, aber ehrliche Arbeit war nicht sein Ding. Er hat sich schließlich hier niedergelassen.";
			link.l1 = "Dennoch würde ich ihn nicht als herausragenden Offizier bezeichnen.";
			link.l1.go = "BM_IronsThirdJungle_20";
		break;
		
		case "BM_IronsThirdJungle_20":
			dialog.text = "Vergiss Gabe nicht. Er wurde zu Hause zum Leutnant befördert. Und er bekam hier in Port Royal seine Kommission als Kapitän des Schiffes, der 'Principio'.";
			link.l1 = "Hört sich nicht sehr Englisch an.";
			link.l1.go = "BM_IronsThirdJungle_21";
		break;
		
		case "BM_IronsThirdJungle_21":
			dialog.text = "Guter Punkt! Das Schiff wechselte die Besitzer wie eine Hafenmaid, also hat es allerlei Dinge gesehen. Aber sie ist immer noch seetüchtig. Und Gabe ist ein geschickter Kapitän, verdammt noch mal.";
			link.l1 = "Und Jack hatte Angst, mit ihm zu verhandeln? Ist er so gut, wie du sagst, dass er ist?";
			link.l1.go = "BM_IronsThirdJungle_22";
		break;
		
		case "BM_IronsThirdJungle_22":
			dialog.text = "Na schön, na schön! Mehr so, als ob er keine Zeit für mich verschwenden wollte. Apropos Jack, ein paar Traditionen, die ich zum ersten Mal von ihm gesehen habe, gefielen mir - das Planken und das Austeilen von schwarzen Marken. Das brachte mich damals auf eine lustige Idee.";
			link.l1 = "Schwarze... Markierungen? Du meinst einen schwarzen Fleck, oder? Und was war es, Tommy? Ich glaube nicht, dass er wüsste, was zu tun ist, wenn du ihm einen schwarzen Fleck übergeben hättest. Ist das passiert? Du wolltest ihn übergeben, und er griff dich an, sobald er dich sah, also ranntest du zum Leuchtturm, und er nahm eine Truppe von Soldaten mit, erzählte ihnen, du wärst ein Pirat?";
			link.l1.go = "BM_IronsThirdJungle_23";
		break;
		
		case "BM_IronsThirdJungle_23":
			dialog.text = "Ich nenne es lieber einen schwarzen Fleck. Das klingt einfach besser. Ein einfacher schwarzer Fleck hätte ihn nichts begreifen lassen. Aber ein schwarzer Fleck aus unserem Seidentaschentuch, das ein markantes Merkmal unserer Firma war - das würde er verstehen. Ich steckte es ihm diskret in die Tasche. Dann sorgte ich dafür, dass er mich zum Leuchtturm gehen sah. Den Rest kennen Sie.";
			link.l1 = "Und die Schmuggler?";
			link.l1.go = "BM_IronsThirdJungle_24";
		break;
		
		case "BM_IronsThirdJungle_24":
			dialog.text = "Falscher Ort, falsche Zeit. Ich hatte sogar ein wenig Mitleid mit ihnen. Aber nur ein wenig, hehe.";
			link.l1 = "Und für Frankie?";
			link.l1.go = "BM_IronsThirdJungle_25";
		break;
		
		case "BM_IronsThirdJungle_25":
			dialog.text = "Wen kümmert das jetzt? Wir haben größere Fische zu braten. Das lässt Gabe übrig. Das wird knifflig. Wir müssen...";
			link.l1 = "Wir?";
			link.l1.go = "BM_IronsThirdJungle_26";
		break;
		
		case "BM_IronsThirdJungle_26":
			dialog.text = "Nun, eine interessante Geschichte zu lernen ist das eine, eine eigene zu kreieren das andere! Also hier ist der Plan. Wir müssen Gabe noch eine weitere spezielle schwarze Markierung hinterlassen - ich habe bereits eine gemacht. Dann werden wir seiner Spur zur Portland Bucht folgen, wo wir uns um ihn kümmern, ohne eine Spur zu hinterlassen.";
			link.l1 = "Und wo sollen wir es pflanzen?";
			link.l1.go = "BM_IronsThirdJungle_27";
		break;
		
		case "BM_IronsThirdJungle_27":
			dialog.text = "Ha ha ha, das ist es, was ich meinte, als ich sagte, ich wünschte, du wärst mehr wie Jack, Kapitän. Komm schon, sei kein Langweiler, ich kann sehen, wie deine Augen brennen!";
			link.l1 = "Eher war ich tatsächlich etwas an Ihrer Geschichte interessiert.";
			link.l1.go = "BM_IronsThirdJungle_28";
		break;
		
		case "BM_IronsThirdJungle_28":
			dialog.text = "Natürlich in seinem Haus! Was ist das für eine Frage? Er hat sich in Port Royal niedergelassen. Also werden du und ich in der Bucht anlegen, damit wir die Insel verlassen können, falls etwas schief geht.";
			link.l1 = "Weißt du, wo sein Haus ist?";
			link.l1.go = "BM_IronsThirdJungle_29";
		break;
		
		case "BM_IronsThirdJungle_29":
			dialog.text = "Nein. Aber es ist nicht schwer herauszufinden. Wir werden die Betrunkenen fragen - sie würden ihre Mutter verkaufen, wenn man ihnen ein oder zwei Drinks spendiert. Nun, was hältst du von meinem Plan?";
			if (GetSummonSkillFromName(pchar, SKILL_ACCURACY) > 24 && GetSummonSkillFromName(pchar, SKILL_GRAPPLING) > 24 && GetSummonSkillFromName(pchar, SKILL_SAILING) > 24)
			{
				link.l1 = "Wenn er der Kapitän eines nach Jamaika gebundenen Schiffes ist, patrouilliert er ständig in den Gewässern der Insel. Unter falscher Flagge anzugreifen ist besser, als in der Stadt irgendetwas zu versuchen.";
				link.l1.go = "BM_IronsThirdJungle_Sea1";	// Морской вариант
				notification("Skill Check Passed", SKILL_SAILING);
				notification("Skill Check Passed", SKILL_ACCURACY);
				notification("Skill Check Passed", SKILL_GRAPPLING);
			}
			else
			{
				if (GetSummonSkillFromName(pchar, SKILL_SAILING) < 25) notification("Skill Check Failed (25)", SKILL_SAILING);
				if (GetSummonSkillFromName(pchar, SKILL_ACCURACY) < 25) notification("Skill Check Failed (25)", SKILL_ACCURACY);
				if (GetSummonSkillFromName(pchar, SKILL_GRAPPLING) < 25) notification("Skill Check Failed (25)", SKILL_GRAPPLING);
			}
			link.l2 = "Es ist nicht ohne Fehler, und du überlässt viel dem Glück. Aber insgesamt ist es machbar. Ich bin bei dir, Tommy. Du hast einen losgeworden, du kannst den anderen nicht gehen lassen, oder?";
			link.l2.go = "BM_IronsThirdJungle_Land1";	// Сухопутный вариант
			link.l3 = "Ich werde mich nicht in deine Rache einmischen und mein Verhältnis zu England für dieses Abenteuer riskieren, bei dem so viel vom Zufall abhängt, Tommy.";
			link.l3.go = "BM_IronsThirdJungle_Otkaz1";	// Отказ
		break;
		
		case "BM_IronsThirdJungle_Sea1":
			dialog.text = "Du bist ein riskanter, Kapitän! Ich fange an, dich zu mögen. Aber Gabe auf der alten 'Principio' ist keine leichte Beute - er ist viel gefährlicher als andere Kapitäne auf einem Schiff wie diesem.";
			link.l1 = "Was denkst du, wer ich bin, ein Feigling, Tommy? Wir werden ihn selbst entern, und du kannst ein Herz-zu-Herz-Gespräch mit ihm führen. Gib ihm den schwarzen Fleck, kurz bevor er abgesetzt wird.";
			link.l1.go = "BM_IronsThirdJungle_Sea2";
		break;
		
		case "BM_IronsThirdJungle_Sea2":
			dialog.text = "Heh, du bist vielleicht kein Feigling, aber er ist es, obwohl er ein schlauer ist. Er greift keinen Soldaten oder sogar einen Piraten an, der größer ist als sein Schiff. Wenn er so etwas am Horizont sieht, versteckt er sich unter dem Flügel des Forts.";
			link.l1 = "Hmm, was ist mit Handelsschiffen?";
			link.l1.go = "BM_IronsThirdJungle_Sea3";
		break;
		
		case "BM_IronsThirdJungle_Sea3":
			dialog.text = "Ja, das könnte funktionieren! Aber wieder, nichts Größeres als eine Bark oder Barkentina! Gabe ist nicht nur ein Feigling - er war nie gierig genug, um das seine Vorsicht überwiegen zu lassen.";
			link.l1 = "Lass uns hoffen, dass es funktioniert, Tommy. Also, eine fünftklassige Bark oder Barkentina unter spanischer oder niederländischer Flagge. Mach dich bereit, deinen alten Kriegskameraden zu treffen!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_SeaVariant");
		break;
		
		case "BM_IronsThirdJungle_Land1":
			dialog.text = "Ich wusste, dass ich auf dich zählen kann! Du könntest eines Tages sogar ein besserer Kapitän als Jack sein. Und was mein Glück betrifft... Es hat mich so weit gebracht, also werde ich mich wieder darauf verlassen. Sollen wir dann gehen?";
			link.l1 = "Ja, lass uns das nicht zu lange hinauszögern. Je eher es vorbei ist, desto besser.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_LandVariant");
		break;
		
		case "BM_IronsThirdJungle_Otkaz1":
			dialog.text = "Heh, ich hoffte anders, aber ich erwartete dies - du hast nicht den Mut für so etwas, "+GetSexPhrase("Jüngling","mein Mädchen")+". Jeder echte Kapitän hat schon mindestens ein paar solcher Fälle gehabt, in denen er diskret mit Ratten umgegangen ist. Manchmal sogar mit ihren eigenen Ratten.";
			link.l1 = "Ich nehme an, ich soll auf diese Provokation hereinfallen und sagen, dass ich meine Meinung geändert habe und beweisen werde, dass ich ein echter Kapitän bin, ja, Tommy? Aber ich verstehe deinen Wunsch nach Rache. Ich werde dich nicht zwingen, die Mannschaft zu verlassen, wie Jack es getan hat. Wie viel Zeit brauchst du dafür? Bis dahin werde ich in Jamaika sein.";
			link.l1.go = "BM_IronsThirdJungle_Otkaz2";
		break;
		
		case "BM_IronsThirdJungle_Otkaz2":
			dialog.text = "Ha ha ha, du wirst erwachsen. Ich respektiere dich fast dafür, dass du nicht darauf reingefallen bist. Aber du brauchst nicht zu warten und mich danach abzuholen - ich werde das selbst beenden. Immerhin, alles, was ich je wollte, ist jemand, der als mein Kapitän etwas für mich tun würde. Also auf Wiedersehen. Kümmere dich um England, ha-ha.";
			link.l1 = "Du bist wirklich merkwürdig. Aber wie du willst. Auf Wiedersehen! Und viel Glück mit deiner Rache, Tommy.";
			link.l1.go = "BM_IronsThirdJungle_Otkaz3";
		break;
		
		case "BM_IronsThirdJungle_Otkaz3":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			
			sld = characterFromID("Irons");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			AddQuestRecord("BlackMark", "6");
			AddQuestUserData("BlackMark", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("BlackMark", "sSex1", GetSexPhrase("к","чка"));
			CloseQuestHeader("BlackMark");
		break;
		
		case "BM_IronsJamaicaShore1":
			dialog.text = "Großartig, wir können uns von hier aus schnell zurückziehen, wenn die Notwendigkeit entsteht. Nimm das - gib Gabe den Hinweis und eine schwarze Marke, sobald du herausfindest, wo er lebt und wann er zu Hause ist.";
			link.l1 = "Oh, also rufst du jetzt die Schüsse, Tommy. Aber denk daran, ich bin immer noch dein Kapitän. Was hast du vor zu tun, während ich in der Stadt bin?";
			link.l1.go = "BM_IronsJamaicaShore2";
		break;
		
		case "BM_IronsJamaicaShore2":
			dialog.text = "Heh, wie könnte ich das vergessen, Kapitän Langweilig? Wenn Gabe mich auf den Straßen bemerkt, wird er entweder Alarm schlagen oder von der Insel flüchten, dieser verfluchte Feigling. Mach dir keine Sorgen, ich werde hier einen Hinterhalt einrichten, hehehe.";
			link.l1 = "Einen Hinterhalt, sagst du. Na gut, Tommy. Lassen wir deinem alten Kriegskameraden ein ordentliches Wiedersehen zuteilwerden, ha ha ha ha!";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsJamaicaGo");
		break;
		
		case "BM_Pyanitsa_0":
			dialog.text = "Hicks! Das ist guter Rum! Hicks... Prost!";
				link.l1 = "Hör zu, Kumpel, was geht in der Stadt über Kapitän Gabriel Callow um?";
			link.l1.go = "BM_Pyanitsa_1";
			DelLandQuestMark(npchar);	//Удаляем квестмарку
		break;
		
		case "BM_Pyanitsa_1":
			dialog.text = "Alter Gabe?! Nur gute Dinge! Warum, hic, was ist das?";
			link.l1 = "Ach, wirklich? Freut mich zu hören. Nun, es gibt Ärger mit einem Piraten. Der Kommandant kümmert sich hauptsächlich um Landangelegenheiten, und ich möchte Seine Lordschaft nicht belästigen.";
			link.l1.go = "BM_Pyanitsa_2";
		break;
		
		case "BM_Pyanitsa_2":
			dialog.text = "Dann geh direkt zu Gabe, sag ich dir! Es gibt keinen ehrlicheren oder mutigeren Kapitän in der Stadt als Gabe. Sogar Oberst Doyley hält viel von ihm. Er segelt ein Schiff, das einmal Nicolas Sharp selbst gehörte, kannst du das glauben?";
			link.l1 = " Ich bin noch nicht betrunken genug, um das schon zu glauben, Kumpel.";
			link.l1.go = "BM_Pyanitsa_3";
		break;
		
		case "BM_Pyanitsa_3":
			dialog.text = "A-Aye, aber das bist du! Es ist das Principio! Klingelt da etwas, hm?";
			link.l1 = "Ein spanisches Trophäenschiff, ist es? Warum?";
			link.l1.go = "BM_Pyanitsa_4";
		break;
		
		case "BM_Pyanitsa_4":
			dialog.text = "Wann hast du das letzte Mal ein Pink mit eigenen Augen gesehen, hm? Ich weiß, was ich sage, eek!";
			link.l1 = "Nun, ich weiß nicht, ob das Design des Schiffes so ungewöhnlich ist.";
			link.l1.go = "BM_Pyanitsa_5";
		break;
		
		case "BM_Pyanitsa_5":
			dialog.text = "Aber das ist es! Niemand würde jetzt so einen Schrott befehlen, bei all den neuen Entwürfen, die es gibt! Sie haben vor fast d...dreißig Jahren aufgehört, sie in Werften zu bauen! Nic hat sie selbst gesegelt, sag ich dir.";
			link.l1 = "In Ordnung, ich kaufe es. Also, sie ist das Schiff. Wie ist dieses Wrack noch nicht auseinandergefallen?";
			link.l1.go = "BM_Pyanitsa_6";
		break;
		
		case "BM_Pyanitsa_6":
			if (sti(pchar.basenation) == ENGLAND) sStr = "our";
			else sStr = "your";
			dialog.text = "Nun, sie ist nicht mehr so schnell wie in ihren besten Jahren - wie ich nach einem weiteren Drink, ha-ha-ha! Aber ein guter Kapitän kann immer noch etwas aus dieser alten Dame herausholen. Gabe versucht auch, sie nicht in die Schusslinie zu bringen.";
			link.l1 = "Also warum wurde das Schiff nicht umbenannt? Seine Majestät Schiff Prügel, vielleicht, unter "+sStr+" altes Regime?";
			link.l1.go = "BM_Pyanitsa_7";
		break;
		
		case "BM_Pyanitsa_7":
			dialog.text = "Trad... Trad-trad-tradition, igitt! Nic selbst hat sie nie umbenannt, nachdem er von einer spanischen Plantage auf Kuba geflohen ist. Er wollte die Erfahrung nie vergessen - und die Spanier auch nicht! Lass mich dir sagen, diese Schlacht nahe der Küste von Tendales...";
			if (startHeroType == 4)
			{
				link.l1 = "Tendales, richtig? Huh, das letzte Mal, dass ich diesen Namen hörte, war als ich noch ein Kind war. Ich dachte nicht, dass noch jemand diese nun verlassenen Felsen kennt und sich daran erinnert.";
				link.l1.go = "BM_Pyanitsa_8";
			}
			else
			{
				link.l1 = "Tendales? Wo ist das?";
				link.l1.go = "BM_Pyanitsa_8";
			}
		break;
		
		case "BM_Pyanitsa_8":
			dialog.text = "Oder war es, eek, Hochfels? N-nein, definitiv nicht dort... Wie auch immer, das spielt keine Rolle! Nic kämpfte und siegte in diesem Rosa, ein unglaublicher Sieg gegen die Brigg Tintenfisch, die von Desmond Ray Beltrop, Piratenbaron, nach ihm geschickt wurde. Sie vergossen eine lange Zeit gegenseitig ihr Blut bis Nic Desmond selbst niederstreckte.";
			if (startHeroType == 4)
			{
				link.l1 = "Wahnsinn, das ist beeindruckend! Obwohl, man würde nichts anderes von Nicholas erwarten. Eh, die Sharps und die Beltrops sind immer zusammen, dann wieder auseinander - anscheinend wiederholt sich die Geschichte wirklich ab und zu.";
				link.l1.go = "BM_Pyanitsa_9";
			}
			else
			{
				link.l1 = "Beeindruckend. Also, wie hat Sharp das Schiff losgeworden? Verkauft auf der Werft?";
				link.l1.go = "BM_Pyanitsa_9";
			}
		break;
		
		case "BM_Pyanitsa_9":
			dialog.text = "Nein. Nach dem Entern begann sie zu lecken, also hat Nic sie aufgegeben. Dann hat die große Flut die Pinke direkt in die Nähe der Stadt gespült.";
			link.l1 = "Als ob jemand an diesem Wrack interessiert wäre.";
			link.l1.go = "BM_Pyanitsa_10";
		break;
		
		case "BM_Pyanitsa_10":
			dialog.text = "Oh, aber die Marine war interessiert! Praktische Kerle. Sie sahen ein Schiff unter der englischen Flagge, aber mit einem spanischen Namen und wurden interessiert. Nic starb ein paar Jahre später, aber sein Schiff fuhr weiter, wechselte die Besitzer, immer auf blutige Weise.";
			link.l1 = "Das ist nur eine weitere Geisterschiffgeschichte, während Gabes Kapitänsamt sehr real ist. Also, ich denke, ich werde ihn besuchen. Weißt du, wo er wohnt?";
			link.l1.go = "BM_Pyanitsa_11";
		break;
		
		case "BM_Pyanitsa_11":
			dialog.text = "Ha ha, natürlich weiß ich das, kieks! Das weiß doch jeder. Alter Gabe wohnt buchstäblich gleich nebenan - du verlässt die Taverne und gehst rechts. Triffst sofort auf sein Haus.";
			link.l1 = "Wann ist er zu Hause? Klingt, als wäre er ein beschäftigter Mann.";
			link.l1.go = "BM_Pyanitsa_12";
		break;
		
		case "BM_Pyanitsa_12":
			dialog.text = "Genau, Kumpel! Er hat viel zu tun. Er ist nur abends zu Hause, ab zehn Uhr. Und er steht jeden Tag pünktlich um sechs Uhr auf, ganz alleine. Eiserne Disziplin!";
			link.l1 = "Vielen Dank! Ich habe genug von diesen Piratengeschichten für jetzt.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_SearchGabeHouse");
		break;
		
		case "BM_Callow1":
			if (startHeroType == 4) 
			{
				dialog.text = "Bist du wirklich... Rumba? Ich habe von dir gehört... aber du hast dich noch nie gegen deine eigenen gewendet!";
				link.l1 = "Und das habe ich nicht. Mein Streit ist nicht mit meinem Land. Er ist mit dir, Gabe.";
				link.l1.go = "BM_Callow_Helena1";
			}
			else
			{
				dialog.text = "Du bist kein Händler...";
				link.l1 = "Überraschung, Gabe! Mir wurde gesagt, du wärst vorsichtig und sogar feige. Die Gier hat dein Urteilsvermögen getrübt, nicht wahr? Kein Kaufmann würde eine Enterung suchen, wie ich es getan habe.";
				link.l1.go = "BM_Callow2";
			}
		break;
		
		case "BM_Callow_Helena1":
			dialog.text = "Mit mir? Was ist das Problem? Wir könnten eine ordentliche Diskussion bei mir oder sogar bei dir führen. Wie Kapitäne, und... Was machst DU hier?!";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CabinDialog");
		break;
		
		case "BM_Callow2":
			dialog.text = "Gewiss. Also wer bist du? Nein, zum Teufel mit dir, allerdings. Wer ist das...";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CabinDialog");
		break;
		
		case "BM_IronsClone1":
			dialog.text = "Thomas, bist du das...?";
			link.l1 = "Oh ja, Gabe. Und ich bin gekommen, um dich für das zu bestrafen, was du mir an jenem Tag angetan hast.";
			link.l1.go = "BM_IronsClone2";
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			CharacterTurnByChr(sld, CharacterFromID("IronsClone"));
			sld = CharacterFromID("IronsClone");
			CharacterTurnByChr(sld, &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)]);
		break;
		
		case "BM_IronsClone2":
			dialog.text = "Strafe mich?! Hüte deine Zunge, Thomas! Wenn einer von uns Strafe verdient, dann du! Du sagtest, du würdest Verstärkung bringen! Und wir warteten, starben unter den Kugeln und Schwertern der Königs-Kavallerie!";
			link.l1 = "Ich habe verdammt hart gerannt, um Hilfe zu holen! Aber ich wurde von einer anderen verdammten Kraft überholt! Charles' blutige Anhänger waren überall! Sie hatten mich festgenagelt, ich wäre fast gestorben! Gut, dass sie dachten, ich sei tot. Aber weißt du was ich gesehen habe, Gabe?!";
			link.l1.go = "BM_IronsClone3";
		break;
		
		case "BM_IronsClone3":
			dialog.text = "Was ist los, Tom? Bist du bereit, jede Geschichte zu erfinden, um diesen Mann glauben zu lassen?!";
			link.l1 = "Heh, dieser Mann wird mich sowieso nicht verraten. Er ist keine Ratte wie manche Leute.";
			link.l1.go = "BM_IronsClone4";
		break;
		
		case "BM_IronsClone4":
			dialog.text = "Er hat keine Wahl! Ein Schiff der englischen Marine anzugreifen!";
			link.l1 = "Oh, er hatte von Anfang an eine Wahl. Und er hat sich entschieden, mir zu helfen. Du und Frankie hattet auch eine Wahl. Ihr habt euch entschieden wegzulaufen, damit ihr nicht sterben müsst. Und dann seid ihr zurückgekommen und habt mich halb tot gefunden. Und ihr habt eure abscheulichen Lügen beim Tribunal erzählt. Ihr wusstet, dass niemand mir zuhören würde, weil ich am Kopf getroffen wurde und mein Gedächtnis verloren habe!";
			link.l1.go = "BM_IronsClone5";
		break;
		
		case "BM_IronsClone5":
			dialog.text = "Niemand hätte dir sowieso zugehört. Du warst schon immer ein... ramponierter, Thomas.";
			link.l1 = "Oh, also versteckst du nicht, was du an dem Tag getan hast. Ich habe etwas für dich, Gabe. Ein schwarzer Fleck. Aber was bringt es dir jetzt, wo das Schiff geentert wurde und wir kurz davor sind, deine Eingeweide zu verschütten, hee hee hee hee hee hee...";
			link.l1.go = "BM_IronsClone6"; // здесь переход на кейс с боёвкой
		break;
		
		case "BM_IronsClone6":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			locCameraTarget(PChar);
			locCameraFollow();
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			
			sld = CharacterFromID("IronsClone");
			LAi_SetCheckMinHP(sld, 1, true, "");
			LAi_SetCurHPMax(sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "reload", "reload1", "BM_IronsCloneMushket", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			LAi_SetImmortal(sld, false);
			LAi_SetCurHPMax(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "BM_CabinDialog4");
		break;
		
		case "BM_IronsClone8":
			dialog.text = "Nun, Gabe ist abgesetzt, hehehe. Wollte das schon lange sagen. Schade, dass du es nicht mehr hören kannst, Kumpel. Oh warte! Vielleicht kannst du es - aus der Hölle.";
			link.l1 = "Komm schon, Tommy. Selbst wenn er es nicht gehört hat, er hat es gesehen und wusste, dass dies genau dein Plan und deine Rache war. Und er konnte nichts dagegen tun.";
			link.l1.go = "BM_IronsClone9";
		break;
		
		case "BM_IronsClone9":
			if (startHeroType == 4) 
			{
				dialog.text = "Heh, du hast recht! Verdammt recht! Danke, dass du mir bei dieser Sache geholfen hast. Weißt du, ich dachte, du wärst nur irgendein verwöhntes Mädchen in schicker Kleidung, das ein Schiff für eine Vergnügungsfahrt bekommen hat. Aber du bist ein verdammt guter Kapitän! Ich wette, du würdest Jack das Wasser reichen können.";
			}
			else
			{
				dialog.text = "Heh, du hast recht! Verdammt richtig! Danke, dass du mir bei dieser Sache geholfen hast. Weißt du, ich denke, du bist so guter Kapitän wie Jack. Oder sogar besser!";
			}
			link.l1 = "Oh, jetzt schmeichelst du mir. Danke. Ich nehme an.";
			link.l1.go = "BM_IronsClone10";
		break;
		
		case "BM_IronsClone10":
			dialog.text = "Ganz und gar nicht. Kein Schmeicheln. Wie Sie vielleicht bemerkt haben, lobe ich selten jemanden so. Also halt verdammt noch mal die Klappe und sei froh, dass ich so hoch von dir denke";
			link.l1 = "Ich würde nicht sagen, dass mir gefällt, wie du es darstellst, auch wenn ich froh bin, dass du mich allgemein als einen guten Kapitän siehst. Aber... die Befehlskette, Tommy, die Befehlskette.";
			link.l1.go = "BM_IronsClone11";
		break;
		
		case "BM_IronsClone11":
			if (startHeroType == 4) 
			{
				dialog.text = "Oh, komm schon! Ich habe das Gefühl, dass alles, was wir durchgemacht haben, uns näher gebracht hat, Ellie. Wir könnten mehr sein als nur Kapitän und Offizier. Gib es zu - auch wenn nur für dich selbst, du fühlst es auch.";
				link.l1 = "Nur in deinen wildesten Träumen, Tommy. Und es ist Helen, nicht Ellie. Aber ich nehme an, du kannst mich jetzt Rumba nennen.";
				link.l1.go = "BM_IronsClone12";
			}
			else
			{
				dialog.text = "Ach, komm schon, du Langweiler! Es scheint mir, dass wir nicht mehr nur ein Kapitän und sein Offizier sind, sondern die wahrhaftigsten Freunde. Findest du nicht auch?!";
				link.l1 = "Heh. Vielleicht. Es ist besser, dein Freund als dein Feind zu sein. Und da Etikette offensichtlich nicht dein Ding ist, werde ich mich wohl daran gewöhnen müssen.";
				link.l1.go = "BM_IronsClone12";
			}
		break;
		
		case "BM_IronsClone12":
			dialog.text = "Ich habe ein... Geschenk für Sie, Kapitän.";
			link.l1 = "Woah, schau dir das an! Ein schwarzer Fleck? Du willst also auch, dass ich abgesetzt werde, hm, Tommy? Du willst selbst Kapitän sein? Ha-ha-ha-ha! Ich dachte, du hast gesagt, wir wären Kumpel.";
			link.l1.go = "BM_IronsClone13";
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_IronsClone13":
			dialog.text = "Es ist ein schwarzes ZEICHEN, du Dummkopf. Weißt du, ich fange an zu denken, dass sobald ich den Totenkopf und die Knochen auf diesen Schal gestickt habe, er mir Glück gebracht hat. Ich kann es nicht erklären. Nimm es. Und... wenn du willst, kannst du immer mein treues Schwert und Rüstung ausleihen... was davon übrig ist, ha-ha! Es wird dir nützlich sein! Du wirst weit kommen. Und ich möchte es erleben. Ich möchte nicht, dass du von einer verirrten Kugel getötet wirst.";
			link.l1 = "Danke, Kumpel! Ich werde mein Bestes geben. Und du - schau zu und bewundere, ha-ha-ha!";
			link.l1.go = "BM_IronsClone14";
		break;
		
		case "BM_IronsClone14":
			dialog.text = "Bewundern, sicher, ha-ha-ha. Aye. Also, was hast du beschlossen mit diesem Schiff zu tun? Auf der einen Seite, es ist nicht mehr viel wert. Auf der anderen Seite, es gibt keine mehr wie es. Ich glaube nicht, dass es jemals wieder welche geben wird.";
			if (startHeroType == 4) 
			{
				link.l1 = "Ich habe noch nicht entschieden... Weißt du, Tommy, ich fühle eine Art Verbindung zu diesem Schiff. Ich kann es nicht erklären. Also, lasst uns zuerst diese stinkende Leiche hier rausholen. Wenn es im Laderaum keine Lecks gibt, werde ich dieses Mädchen wahrscheinlich für mich nehmen.";
			}
			else
			{
				link.l1 = "Ich weiß nicht, Tommy. Ich habe mich noch nicht entschieden. In der Zwischenzeit, lasst uns Gabe's Leiche loswerden. Nur für den Fall, dass wir das Schiff behalten.";
			}
			link.l1.go = "BM_IronsClone15";
		break;
		
		case "BM_IronsClone15":
			DialogExit();
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		
		case "BM_IronsPinkPotopil1":
			dialog.text = "Nun, Sie haben einen ziemlich guten Job mit diesem alten Schiff gemacht, Kapitän! Und obwohl ich Gabe mit meinen eigenen Händen erledigen wollte, werde ich den Schöpfer nicht verärgern, indem ich diesen Sieg schmälere.";
			link.l1 = "Das wäre unnötig, Tommy. Ich hoffe, deine Seele ist jetzt in Frieden.";
			link.l1.go = "BM_IronsPinkPotopil2";
		break;
		
		case "BM_IronsPinkPotopil2":
			if (startHeroType == 4) 
			{
				dialog.text = "Ich habe das Gefühl, dass alles, was wir durchgemacht haben, uns näher gebracht hat, Ellie. Wir könnten mehr sein als nur Kapitän und Offizier. Gib es zu - auch wenn nur für dich selbst, du fühlst es auch.";
				link.l1 = "Nur in deinen wildesten Träumen, Tommy. Und es ist Helen, nicht Ellie. Aber ich nehme an, du kannst mich jetzt Rumba nennen, wenn du mit diesem Schmeicheleien aufhörst.";
			}
			else
			{
				dialog.text = "Ich war noch nie so glücklich in meinem Leben! Danke, dass du mir dabei geholfen hast. Weißt du, ich glaube, du bist genauso gut wie Jack als Kapitän. Oder sogar besser!";
				link.l1 = "Oh, du schmeichelst mir. Danke auch für den Vergleich, schätze ich.";
			}
			link.l1.go = "BM_IronsPinkPotopil3";
		break;
		
		case "BM_IronsPinkPotopil3":
			if (startHeroType == 4) 
			{
				dialog.text = "Ganz und gar nicht. Kein Schmeicheln. Wie du vielleicht schon bemerkt hast, lobe ich selten jemanden so. Also halt die Klappe und sei froh, dass ich so hoch von dir denke.";
				link.l1 = "Ich würde nicht sagen, dass mir gefällt, wie du es ausdrückst, aber ich bin froh, dass du mich im Allgemeinen als guten Kapitän siehst. Aber... die Befehlskette, Tommy, die Befehlskette.";
			}
			else
			{
				dialog.text = "Ganz und gar nicht. Kein Schmeicheln. Wie du vielleicht schon bemerkt hast, lobe ich selten jemanden so. Also halt den Mund und sei froh, dass ich so hoch von dir denke.";
				link.l1 = "Ich würde nicht sagen, dass mir gefällt, wie du es ausdrückst, aber ich bin froh, dass du mich im Allgemeinen als guten Kapitän siehst. Aber... die Befehlskette, Tommy, die Befehlskette.";
			}
			link.l1.go = "BM_IronsPinkPotopil4";
		break;
		
		case "BM_IronsPinkPotopil4":
			if (startHeroType == 4) 
			{
				dialog.text = "Ach, komm schon, du Langweiler! Mir scheint, dass du und ich nicht mehr nur ein Kapitän und sein Offizier sind, sondern die wahrhaftigsten Freunde. Denkst du nicht auch so?!";
				link.l1 = "Heh. Vielleicht. Es ist besser, dein Freund als dein Feind zu sein. Und da Etikette offensichtlich nicht dein Ding ist, werde ich mich wohl daran gewöhnen müssen.";
			}
			else
			{
				dialog.text = "Ach komm schon, du Langweiler! Mir scheint, du und ich sind nicht mehr nur ein Kapitän und sein Offizier, sondern die allerbesten Freunde. Meinst du nicht auch?!";
				link.l1 = "Heh. Vielleicht. Es ist besser, dein Freund zu sein als dein Feind. Und da Etikette offensichtlich nicht deine Sache ist, werde ich mich wohl daran gewöhnen müssen.";
			}
			link.l1.go = "BM_IronsPinkPotopil5";
		break;
		
		case "BM_IronsPinkPotopil5":
			if (startHeroType == 4) 
			{
				dialog.text = "Ich habe ein... Geschenk für Sie, Kapitän.";
			}
			else
			{
				dialog.text = "Ich habe ein... Geschenk für dich, Kapitän.";
			}
			link.l1 = "Woah, schau dir das an! Ein schwarzer Fleck? Du willst also auch, dass ich abgesetzt werde, hm, Tommy? Du willst selbst Kapitän sein? Ha-ha-ha-ha! Ich dachte, du sagtest, wir wären Kumpel.";
			link.l1.go = "BM_IronsPinkPotopil6";
		break;
		
		case "BM_IronsPinkPotopil6":
			dialog.text = "Es ist ein schwarzes MAL, du Dummkopf. Weißt du, ich fange an zu denken, dass sobald ich den Totenkopf und die Knochen auf diesen Schal gestickt habe, er mir Glück gebracht hat. Ich kann es nicht erklären. Nimm es. Auch... wenn du willst, kannst du immer mein treues Schwert und Rüstung ausleihen... was davon übrig ist, ha-ha! Es wird nützlich sein! Du wirst weit kommen. Und ich möchte es miterleben. Ich will nicht, dass du von einer verirrten Kugel getötet wirst.";
			link.l1 = "Danke, Kumpel! Ich werde mein Bestes geben. Und du - schau zu und bewundere, ha-ha-ha!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_PinkPotopil_4");
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_GabeHouseGood1":
			notification("Reputation Check Passed", "None");
			if (startHeroType == 4)
			{
				dialog.text = "Wer muss an so etwas glauben... Es tut mir leid, Fräulein. "+TimeGreeting()+". Wie kann ich Ihnen helfen? Sie sehen sehr besorgt aus.";
			}
			else
			{
				dialog.text = "Was? Wer kommt um diese späte Stunde vorbei? Sie sehen ziemlich besorgt aus, Herr. Was kann ich für Sie tun?";
			}
			link.l1 = "Es tut mir leid, dass ich Ihre Ruhe störe, Kapitän Callow. Mein Name ist "+GetFullName(pchar)+", und ich komme im Auftrag eines deiner alten Kriegskameraden.";
			link.l1.go = "BM_GabeHouseGood2";
		break;
		
		case "BM_GabeHouseGood2":
			dialog.text = "Welcher Kamerad? Ich hatte viele, sowohl in der Alten Welt als auch in der Neuen.";
			link.l1 = "Zuerst wollte ich nur etwas in einer deiner Truhen hinterlassen. Oder vielleicht auf dem Tisch, damit du es schneller bemerkst. Es betrifft einen Mann aus deiner Vergangenheit. Hier, schau es dir an und lies es selbst.";
			link.l1.go = "BM_GabeHouseGood3";
		break;
		
		case "BM_GabeHouseGood3":
			dialog.text = "Ein schwarzer Fleck? Ich erinnere mich nicht an Piraten unter meinen Kameraden. Oder sind einige der Jungs in dieses Leben geraten? Schwarze Seide? Wirklich... Oh, Thomas. Es überrascht mich, dass ein Mann wie du mit diesem Schurken zu tun hat.";
			link.l1 = "Es tut mir leid, aber es steht dir nicht zu, ihn einen Schurken zu nennen. Du bist vom Schlachtfeld geflohen und hast Tom verleumdet. Vielleicht hast du dich später bereut und bist hier im Archipel ein vorbildlicher Offizier geworden, aber das ändert nichts an der Vergangenheit.";
			link.l1.go = "BM_GabeHouseGood4";
		break;
		
		case "BM_GabeHouseGood4":
			dialog.text = "Er hat dir das erzählt? Keine Überraschung - er wusste immer, wie man den richtigen Mann findet, um seine Geschichten zu erzählen. Thomas hatte eine silberne Zunge. Du kennst ihn nicht, noch die wahre Geschichte, noch weißt du, worauf du dich einlässt. Ich kann es dir erzählen - da ich jetzt sowieso nicht schlafen werde.";
			link.l1 = "Es ist nie eine schlechte Idee zuzuhören. Fahren Sie fort, Kapitän Callow.";
			link.l1.go = "BM_GabeHouseGood5";
		break;
		
		case "BM_GabeHouseGood5":
			dialog.text = "Also, Thomas behauptet, ich sei geflohen und hätte ihn dann verleumdet? Nun, du solltest wissen, dass es genau umgekehrt war! Als die Kavallerie des Königs näher kam, sagte Tom, er hole Verstärkung. Also zogen wir uns nicht zurück - wir warteten. Unsere ganze Kompanie wurde getötet! Wenn wir nicht auf die Verstärkung gewartet hätten, die er versprochen hatte, hätten wir uns zurückziehen und überleben können! Am Ende waren nur noch ich, Frankie und der verdammt Thomas am Leben.";
			link.l1 = "Also was du sagst ist...";
			link.l1.go = "BM_GabeHouseGood6";
		break;
		
		case "BM_GabeHouseGood6":
			dialog.text = "Ich sage, das Blut unserer Jungs ist genauso auf Toms Händen wie auf den der Royalisten. Er hat Glück, dass er zu Zwangsarbeit und nicht zum Hängen verurteilt wurde! Und jetzt hat er die Frechheit, Groll zu hegen und mich zu einem Duell herauszufordern! Er ist es nicht wert!";
			link.l1 = "Also gehst du nicht? Dir ist klar, was das bedeutet. Die Gesetze der Ehre gelten für jeden.";
			link.l1.go = "BM_GabeHouseGood7";
		break;
		
		case "BM_GabeHouseGood7":
			dialog.text = "Ich tue es natürlich. Und genau deshalb gehe ich. Wir müssen beenden, was unser republikanisches Gericht aufgrund von Toms früheren militärischen Ehren nicht konnte. Und du... du scheinst eine anständige Art zu sein. Ich rate dir, deine Bekanntschaften klüger zu wählen. Lass dich nicht mit Tom und seiner Art ein.";
			link.l1 = "Aber Thomas ist jetzt mein Untergebener, ein Offizier auf meinem Schiff. "+GetSexPhrase("Ich werde ein Auge auf ihn haben und ihn nicht weiter entehren lassen, wenn er seine Begegnung mit dir überlebt.","")+"";
			link.l1.go = "BM_GabeHouseGood_Tommi1";
			link.l2 = "Und was würden Sie an meiner Stelle tun, Kapitän Callow?";
			link.l2.go = "BM_GabeHouseGood_Gabe1";
		break;
		
		case "BM_GabeHouseGood_Tommi1":
			dialog.text = "Eh, wenn Tom dich von seiner Geschichte überzeugen konnte, wird er keine Probleme haben, es noch einmal zu tun.";
			link.l1 = ""+GetSexPhrase("Aber nach den Gesetzen der Ehre, kann ich ihn nicht verraten. Ich bin","Ich bin")+" verantwortlich für meine Männer.. Ich werde nicht wie er sein. Und ich werde vorsichtiger und kritischer mit ihm umgehen, wenn er überlebt.";
			link.l1.go = "BM_GabeHouseGood_Tommi2";
		break;
		
		case "BM_GabeHouseGood_Tommi2":
			dialog.text = "Es ist eine schwere Entscheidung. Aber ich werde nicht versuchen, deine Meinung zu ändern. Nun, auf Wiedersehen, "+GetSexPhrase("Herr","Fräulein")+" - Ich muss mich noch auf das Treffen mit Tom vorbereiten.";
			link.l1 = "Auf Wiedersehen, Kapitän Callow.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_TommiPlan");
		break;
		
		case "BM_GabeHouseGood_Gabe1":
			dialog.text = "Lass Gerechtigkeit walten! Hilf mir, Thomas zu stürzen, "+pchar.lastname+". Er ist ein seltener Schurke und ein Feigling, aber ein großartiger Schütze - es wird nicht einfach sein. Aber zusammen...";
			link.l1 = "Hmm, dir helfen, Thomas zu besiegen? Gibt es viel Ehre in solch einem Duell? Ihr könnt das selbst regeln, und ich bleibe aus dem Weg.";
			link.l1.go = "BM_GabeHouseGood_Gabe2";
		break;
		
		case "BM_GabeHouseGood_Gabe2":
			dialog.text = "Ihn kennend, bezweifle ich, dass ich einen fairen Zweikampf bekomme. Indem du neutral bleibst, billigst du nur Ungerechtigkeit. Habe ich recht?";
			link.l1 = "Es scheint, du kennst Tom besser als ich und weißt, wie er wirklich ist. Du hast recht - er bereitet bereits einen Hinterhalt in der Portland-Bucht vor und rechnet mit meiner Hilfe - genau wie du jetzt.";
			link.l1.go = "BM_GabeHouseGood_Gabe3";
		break;
		
		case "BM_GabeHouseGood_Gabe3":
			dialog.text = "Dann ist es kein Duell, sondern eine Schlägerei. Aber ich schlage nicht vor, dass wir Thomas selbst töten. Wir werden ihn verhaften! Ich bringe Soldaten mit und wir beenden das, was wir in der Alten Welt nicht konnten. Wenn sie versuchen, ihn erneut zu entlasten, werde ich an den Oberst schreiben oder ihn sogar hier für den Prozess bringen. Wenn Thomas seine Waffen nicht niederlegt, ist es seine eigene Schuld.";
			link.l1 = "Das klingt viel besser.";
			link.l1.go = "BM_GabeHouseGood_Gabe4";
		break;
		
		case "BM_GabeHouseGood_Gabe4":
			dialog.text = "Froh, es zu hören, "+pchar.lastname+"! Ich verstehe, dass es für Sie vielleicht nicht einfach ist, eine solche Entscheidung zu treffen, aber ich versichere Ihnen, Sie haben die richtige Wahl getroffen. Und um das zu gewährleisten, werde ich Ihnen bei etwas anderem helfen.";
			link.l1 = "Was ist los, Kapitän Callow?";
			link.l1.go = "BM_GabeHouseGood_Gabe5";
		break;
		
		case "BM_GabeHouseGood_Gabe5":
			dialog.text = "Hier, nimm das. Kein Geschenk, sondern ein Darlehen - Thomas, wie ich sagte, ist ein sehr guter Kämpfer, und es ist besser, ihm mit einer ordentlichen Waffe gegenüberzutreten, nicht mit einem rostigen Eisenstück. Oberst Doyley selbst hat mir diese Schönheit gegeben, aber für einen echten Kampf würde ich immer ein Breitschwert wählen.";
			link.l1 = "Tatsächlich, es ist ein prächtiger Degen. Danke.";
			link.l1.go = "BM_GabeHouseGood_Gabe6";
			GiveItem2Character(PChar, "blade_40");
		break;
		
		case "BM_GabeHouseGood_Gabe6":
			dialog.text = "Mach mir keinen Dank - Ich leihe es dir nur aus, schenk es dir nicht, erinnerst du dich? Jetzt geh zur Bucht und spiel deine Rolle bei unserem lieben Tom, während ich Verstärkungen sammle. Wir sehen uns dort.";
			link.l1 = "Bis dort, Kapitän Callow.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_GabePlan");
		break;
		
		case "BM_GabeHouseNeutral1":
			notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(71))+")", "None");
			if (startHeroType == 4)
			{
				dialog.text = "Wer sind Sie, Fräulein? Sie müssen sich in der Adresse geirrt haben. Ich habe, äh, keine Übernachtdienste bestellt.";
				link.l1 = "Helen MacArthur. Und halten Sie Ihre Begierden im Zaum, Herr Callow. Ich bin ein anständiges Mädchen. Unser Klima lässt mich selbst nachts heiß fühlen. Hatten Sie keine Scham, das einem fremden Mädchen zu sagen? Man hat mir von Ihnen als einem vorbildlichen Offizier erzählt.";
				link.l1.go = "BM_GabeHouseNeutral2";
			}
			else
			{
				dialog.text = "Wer sind Sie und was wollen Sie? Mir gefällt Ihr Grinsen nicht, Herr.";
				link.l1 = ""+GetFullName(pchar)+". Und Sie sind nicht sehr gastfreundlich, Herr Callow.";
				link.l1.go = "BM_GabeHouseNeutral2";
			}
		break;
		
		case "BM_GabeHouseNeutral2":
			dialog.text = "Grüßt ihr Fremde zu dieser Stunde anders?";
			link.l1 = "Ich habe gehört, Sie sind zu anderen Zeiten nicht zu Hause.";
			link.l1.go = "BM_GabeHouseNeutral3";
		break;
		
		case "BM_GabeHouseNeutral3":
			dialog.text = "Natürlich bin ich das nicht - ich habe Dienst, Pflicht und ehrliche Arbeit, Worte, die dir nach deinem Aussehen unbekannt zu sein scheinen.";
			link.l1 = "Solch ein Selbstvertrauen! Aber dann hättest du Oberst Doyley und die anderen nicht von deiner Ehrlichkeit überzeugt. Ich brauche nichts von dir, Gabe, aber ein alter Bekannter von dir tut es. Hier, bitte.";
			link.l1.go = "BM_GabeHouseNeutral4";
		break;
		
		case "BM_GabeHouseNeutral4":
			dialog.text = "Überzeugt? Gabe? Ich sage! Ein schwarzer Fleck? Also bist du ein Pirat? Warte mal... schwarze Seide... könnte das sein... Oh, ich verstehe. Thomas, du verdammter Bastard, immer noch wütend auf mich und Frank, weil wir dich gemeldet haben, ha ha ha ha!";
			link.l1 = "Ich sage! Tom ist ein Offizier auf meinem Schiff und verdient Respekt. Er ist einer der besten Schützen des Archipels.";
			link.l1.go = "BM_GabeHouseNeutral5";
		break;
		
		case "BM_GabeHouseNeutral5":
			dialog.text = "Ich habe nicht gesagt, dass er schlecht schießt. Aber du kennst Thomas anscheinend nicht sehr gut. Er ist derjenige, der uns alle verraten hat. Aber ich sehe, es hat keinen Sinn, mit dir zu streiten - ihr passt offensichtlich perfekt zueinander.";
			link.l1 = "Ich kümmere mich nicht darum. Behalte deine Geschichten für Doyley und all diese naiven Einfaltspinsel. Wenn du so mutig und ehrenhaft bist, wie sie sagen, wirst du die Herausforderung annehmen und jetzt kommen. Also, akzeptierst du es?";
			link.l1.go = "BM_GabeHouseNeutral6";
		break;
		
		case "BM_GabeHouseNeutral6":
			dialog.text = "Ich tue es, ich tue es. Jetzt raus aus meinem Haus, bevor ich die Wachen rufe.";
			link.l1 = "Es wird mir ein Vergnügen sein, Gabe.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_TommiPlan");
		break;
		
		case "BM_IronsJamaicaJungle1":
			if (CheckAttribute(pchar, "questTemp.BM_GabePlan"))
			{
				dialog.text = "Warum bist du so nervös? Hast du Angst oder was?";
				link.l1 = "Jeder würde nervös werden, wenn er einen Mann mit einem Musketen auf sich zulaufen sieht - Ich habe dich erst nicht erkannt. Was machst du hier, Tommy?";
				link.l1.go = "BM_IronsJamaicaJungle_GabePlan_2";
			}
			else
			{
				dialog.text = "Wie ist es gelaufen? Hey, hey, warum schaust du mich so an? Du hast mir einen Schrecken eingejagt, hehehe.";
				link.l1 = "Wer erschreckt wen! Wer rennt so weg?! Wir haben vereinbart, die Gäste in der Bucht zu treffen!";
				link.l1.go = "BM_IronsJamaicaJungle2";
			}
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_2":
			dialog.text = "Heh, nun, vielleicht. Ich wurde müde zu warten - auf unsere lieben Gäste und auf dich. Und ich dachte, dieser Ort wäre besser für einen guten Hinterhalt geeignet. Schließlich bin ich ein Jäger, kein Duellant.";
			link.l1 = "Ich sehe.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_3";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_3":
			dialog.text = "Aye. Also, hast du mein Geschenk bei Gabes Haus gelassen? Hat ja lange genug gedauert. Ich wäre viel schneller, wenn ich in die Stadt kommen könnte. Was lässt deine Augen laufen, Kapitän? Was ist los?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				link.l1 = "(Vertrauenswürdig) Ich bin nervös. Gabe ist ein Feigling, aber er ist nicht dumm. Was ist, wenn statt ihm ein ganzes Platoon Soldaten hierher kommt? Oder sie nähern sich der Bucht und versenken unser Schiff zuerst?";
				link.l1.go = "BM_IronsJamaicaJungle_GabePlan_VD1";
				notification("Trustworthy", "Trustworthy");
			}
			else
			{
				link.l2 = "Gabe hat mich gesehen. Ich musste weglaufen.";
				link.l2.go = "BM_IronsJamaicaJungle_GabePlan_4";
				notification("Perk Check Failed", "Trustworthy");
			}
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_VD1":
			dialog.text = "Heh, ich verstehe - ich bin mir selbst nicht ganz sicher, ob es funktionieren wird. Das ist das erste Mal, dass dir so etwas Großes passiert, nicht wahr? Das ist in Ordnung, das passiert. Ich habe alles durchdacht. Wenn die Soldaten ohne Gabe kommen, gehen wir einfach. Wenn sie mit Gabe kommen, lege ich eine Kugel zwischen seine Augen, und wieder gehen wir einfach. Und wenn ein Schiff in die Bucht kommt, laufen wir nach Maroon Town - sie würden es nicht wagen, dorthin zu gehen, und dann entscheiden wir, was wir als nächstes tun.";
			link.l1 = "Ich sehe, du hast wirklich an alles gedacht, Tommy.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_VD2";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_VD2":
			dialog.text = "Natürlich habe ich. Jetzt warten wir auf unseren Gast...";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_GazgovorTommiAndGabe");
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_4":
			dialog.text = "Ha ha, du bist genauso gut ein Dieb wie ich ein Royalist. Aber warum schaust du mir nicht in die Augen... Kapitän? Du hast mit Gabe gesprochen, nicht wahr?";
			link.l1 = "Nein, wovon redest du? Warum sollte ich überhaupt mit ihm reden?";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_5";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_5":
			dialog.text = "Weil ihr alle große Redner seid. Ihr tut nichts als reden. Also, was hat unser lieber Gabe euch erzählt?";
			link.l1 = "Macht es einen Unterschied, Tommy?";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_6";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_6":
			dialog.text = "Ehrlich gesagt, nein. Das tut es, wenn du mich nicht in den Rücken stichst. Aber es sieht so aus, als hättest du es bereits getan. Er hat dich dazu gebracht, seine Seite zu ergreifen, oder?";
			link.l1 = "Nein. Nicht genau. Leg die Pistole nieder, Tommy. Ich verspreche dir, es muss nichts Unwiederbringliches passieren. Vielleicht arbeitest du in den Steinbrüchen, vielleicht. Ich werde Gabe bitten, Gnade zu zeigen. Ich werde sogar Colonel Doyley fragen, wenn ich muss.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_7";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_7":
			dialog.text = "Was für ein guter Samariter du bist. Zeigst Gnade, damit ich nach Jahren im Steinbruch meine Lungen auskotzen kann? Ich gehe nicht zurück zu den Gefängnisschiffen. Nie wieder. Und du... Ich hätte wissen sollen, dass du nur eine weitere Ratte bist. Da ist etwas in deinem Blick. Ich werde mich zuerst um dich kümmern, damit Gabe später leichter fällt.";
			link.l1 = "Du lässt uns keine Wahl!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaSTommi");
		break;
		
		case "BM_GabePlan_TommiMertv":
			dialog.text = "Nun, ich sehe, du hast es bereits getan, "+GetSexPhrase("Herr","Fräulein")+". Und ich versammelte eine Mannschaft, in der Hoffnung, dass die zahlenmäßige Überlegenheit Tom dazu bringen würde, zweimal nachzudenken und die Waffen niederzulegen.";
			link.l1 = "Und Sie haben sich Zeit gelassen, Kapitän Callow.";
			link.l1.go = "BM_GabePlan_TommiMertv2";
		break;
		
		case "BM_GabePlan_TommiMertv2":
			dialog.text = "Ich habe dir gesagt, ich sammle Männer. Das Beste aus unserer Garnison. Tom ist schließlich ein erfahrener Soldat. Aber wem erzähle ich das? Gut gemacht, "+GetSexPhrase("Herr","Fräulein")+" "+pchar.lastname+". "+GetSexPhrase("Ich bin stolz auf dich, junger Mann","Ich muss zugeben, Sie besitzen gleiche Teile Schönheit, Intelligenz und Geschick, junge Dame")+". Wie ich Ihnen bei unserer ersten Begegnung sagte, haben Sie die richtige Entscheidung getroffen. Jetzt ist Gerechtigkeit geübt worden.";
			link.l1 = "Es hat so gut für dich geklappt. Fühlst du dich stolz?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict";
			link.l2 = "Nun, ich bin kein erfahrener Soldat, aber ich kann kämpfen, wie Sie vielleicht gerade bemerkt haben. Aber danke, Herr. Gerechtigkeit ist für mich kein leeres Wort.";
			link.l2.go = "BM_GabePlan_TommiMertv_Mir";
		break;
		
		case "BM_GabePlan_TommiMertv_Mir":
			dialog.text = "Und das ist lobenswert, "+GetSexPhrase("junger Mann","junge Dame")+". Es gibt jedoch noch eine Sache, die wir an diesem feinen Tag erledigen müssen.";
			link.l1 = "Hmm, und was ist das? Tom ist schließlich schon besiegt.";
			link.l1.go = "BM_GabePlan_TommiMertv_Mir2";
		break;
		
		case "BM_GabePlan_TommiMertv_Mir2":
			dialog.text = "Du hast etwas, das mir gehört. Gib mir bitte meinen schönen italienischen Degen zurück. Es ist schließlich nicht nur ein Zahnstocher, sondern eine Erinnerung - ein Geschenk von Oberst Doyley selbst.";
			if (!CheckCharacterItem(PChar, "blade_40"))
			{
				link.l1 = "Eh... Hier ist die Sache, Kapitän Callow... das Rapier ist weg. Ich habe es verloren. Es tut mir leid.";
				link.l1.go = "BM_GabePlan_TommiMertv_Poteryal";			//Потеряли Рапиру
				break;
			}
			if (CheckCharacterItem(PChar, "blade_40"))
			{
				link.l2 = "Ach, natürlich. Bitte. Ich hatte nicht vor, es zu stehlen. Ich werde nicht lügen - ich würde es gerne behalten. Aber hier sind Sie, Kapitän Callow.";
				link.l2.go = "BM_GabePlan_TommiMertv_Soglasen";			//Согласен
			}
			if (CheckCharacterItem(PChar, "blade_42"))
			{
				link.l3 = "Ich habe ein besseres Angebot für Sie, Kapitän.";
				link.l3.go = "BM_GabePlan_TommiMertv_Obmen";			//Обмен
			}
			link.l4 = "Aber du hast es gerade einen Zahnstocher genannt. Außerdem hast du gesagt, dass du Rapiere überhaupt nicht magst. Ich hingegen verdiene eine Belohnung.";
			link.l4.go = "BM_GabePlan_TommiMertv_Otkaz";				//Отказ
		break;
		
		case "BM_GabePlan_TommiMertv_Soglasen":
			dialog.text = "Jeder hätte diese Schönheit behalten wollen! Danke, dass du sie mir zurückgegeben hast. Viele Leute wären an deiner Stelle stur gewesen.";
			link.l1 = "Es gehört dir. Ich nehme an, wir sind hier fertig?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok";
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "blade_40");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			ChangeCharacterNationReputation(pchar, ENGLAND, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen":
			dialog.text = "Ich bin nicht interessiert. Gib einfach den Degen zurück, und wir gehen im Guten auseinander, "+GetSexPhrase("Herr","Fräulein")+" "+pchar.lastname+".";
			link.l1 = "Ich nehme an, dieses Rapier ist Ihnen lieb, weil Sie Waffen mit Geschichte mögen, habe ich recht? Ich habe ein genau solches und dieses hier ist das, was Sie gerne tragen würden, anstatt es in einer Schublade aufzubewahren.";
			link.l1.go = "BM_GabePlan_TommiMertv_Obmen2";
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen2":
			dialog.text = "Ist das so? Nun, ich kann nicht versprechen, dass wir uns einigen werden, aber ich höre zu. Ich bin tatsächlich an Waffen mit Geschichte interessiert. Aber dieser Degen war ein Geschenk vom Oberst. Deshalb ist er mir so kostbar.";
			link.l1 = "Du hast erwähnt, dass du Breitschwerter magst. Hier. Es gehörte unserem lieben Tommy. Stell dir vor, was diese Waffe im Laufe der Jahre durchgemacht hat. Und was sie mit dir weiterhin durchmachen wird.";
			link.l1.go = "BM_GabePlan_TommiMertv_Obmen3";
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen3":
			dialog.text = "Du bist sehr überzeugend, junger Mann! Thomas' Schwert zu schwingen... wie ironisch. Nun, nimm den Degen. Ich gebe ihn nicht leichtfertig her, das versichere ich dir.";
			link.l1 = "Ich bin froh, dass wir uns einigen konnten. Ich denke, das ist ein Abschied, Kapitän Callow?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok";
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "blade_42");
			AddCharacterExpToSkill(pchar, "Leadership", 250);
			AddCharacterExpToSkill(pchar, "Commerce", 500);
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal":
			dialog.text = "WAS?! Wie konntest du... Wie konntest du ein ganzes verdammtes Rapier verlieren?! Du bist ein Idiot!";
			link.l1 = "Beruhige dich! Es ist nur ein Degen. Du würdest ihn sowieso nie benutzen. Tom ist tot - ist das jetzt nicht das Einzige, was zählt?";
			link.l1.go = "BM_GabePlan_TommiMertv_Poteryal2";
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal2":
			dialog.text = "Nur ein Degen?! Es war mein Schatz! Ein Geschenk von Oberst Doyley selbst! Es ist mir egal, ob ich es nicht benutzt habe!";
			link.l1 = "Dann hättest du es mir nicht geben sollen, oder?";
			link.l1.go = "BM_GabePlan_TommiMertv_Poteryal3";
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal3":
			dialog.text = "Du solltest jetzt deinen Mund halten, "+GetSexPhrase("Herr","Fräulein")+" "+pchar.lastname+". Wir hätten uns friedlich trennen können. Aber jetzt... jetzt möchte ich dir eine Lektion erteilen, "+GetSexPhrase("junger Mann","junge Miss")+".";
			link.l1 = "Friedhöfe sind gefüllt mit Lehrern wie dir.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Rapira = true;
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz":
			dialog.text = "Du tust es natürlich. Aber du kannst doch nicht einfach die persönliche Waffe eines Offiziers nehmen, weil du ihm geholfen hast, oder?";
			link.l1 = "Ich würde zustimmen, aber du benutzt es sowieso nicht. Es wird nur an einem Nagel in deinem Zimmer hängen. Bei mir hingegen wird es einen würdigen Gebrauch finden. Oberst Doyley wird doch nicht nachsehen, ob du es verlegt hast, oder?";
			link.l1.go = "BM_GabePlan_TommiMertv_Otkaz2";
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz2":
			dialog.text = "Dies ist nicht zur Diskussion, junger Mann. Ich habe es dir von Anfang an gesagt, es ist kein Geschenk. Gib mir den Degen. Jetzt.";
			link.l1 = ""+GetSexPhrase("Ich bin nicht einer deiner Spielzeugsoldaten","Ich bin nicht eine deiner Hafen-Huren")+", Befehle von dir entgegenzunehmen. Ich bin ein Schiffskapitän, genau wie du. Der Degen bleibt bei mir, ob es dir gefällt oder nicht.";
			link.l1.go = "BM_GabePlan_TommiMertv_Otkaz3";
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz3":
			dialog.text = "Sieht so aus, als hätte Thomas einen großen Einfluss auf dich gehabt. Dann stirb dafür, wenn du es so sehr willst.";
			link.l1 = "Genau meine Gedanken!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Rapira = true;
		break;
		
		case "BM_GabePlan_TommiMertv_Platok":
			dialog.text = "Hier, nimm das. Ich brauche es überhaupt nicht. Es wird deine Erinnerung an den Tag sein. Versuche in Zukunft ein wenig weniger leichtgläubig zu sein. Und lass dich nicht von Schurken wie Thomas in ihre schmutzigen Geschäfte verwickeln.";
			link.l1 = "Heh, gibst du mir einen schwarzen Fleck, Kapitän Callow?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok2";
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_GabePlan_TommiMertv_Platok2":
			dialog.text = "Nun, keiner von uns beiden ist Pirat, oder?"+pchar.name+"? Lass es eine Erinnerung sein. Pass auf, das Archipel braucht Männer wie dich. "+GetSexPhrase("Vielleicht würde ich vorschlagen, der Marine beizutreten und eine Empfehlung an Oberst Doyley zu schreiben...","")+"";
			link.l1 = "Ich bedaure, dass ich Ihr Angebot nicht annehmen kann, Kapitän.";
			if (startHeroType == 3)
			{
				link.l1 = "Hm. Ich werde es mir überlegen. Einen wirklich guten Gedanken.";
			}
			if (startHeroType == 4)
			{
				link.l1 = "Auf Wiedersehen, Herr.";
				link.l1.go = "exit";
				AddDialogExitQuest("BM_GabePlan_CallowDruzhba");
				break;
			}
			link.l1.go = "BM_GabePlan_TommiMertv_Platok3";
		break;
		
		case "BM_GabePlan_TommiMertv_Platok3":
			dialog.text = "Wie du willst. Nun, auf Wiedersehen, "+GetSexPhrase("Herr.","Fräulein")+" "+pchar.lastname+". Du verdienst es, das zu tragen, was von den Ironsides übrig ist. Lebwohl.";
			link.l1 = "Auf Wiedersehen, Herr.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_CallowDruzhba");
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict":
			dialog.text = "Ich mag deinen Ton nicht, "+GetSexPhrase("Herr","Fräulein")+". Was ist dein Punkt?";
			link.l1 = "Sie haben absichtlich Zeit verschwendet und Ihre 'besten Männer' zusammengetrommelt. Wofür? Um einen einzigen Mann zu verhaften? Sie hätten ein paar patrouillierende Soldaten ergreifen und mir sofort zu Hilfe kommen sollen!";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict2";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict2":
			dialog.text = "Kanonenfutter mitbringen?! Tom war nicht nur ein Stadtwächter wie sie. Er hatte eine völlig andere Ausbildung und Erfahrung - er ist ein verdammt', Eisenharter, genau wie ich! Wie kannst du das nicht begreifen?";
			link.l1 = "Oh, im Gegenteil, ich erkenne es durchaus. Deshalb waren du und ich hier - um mit Tom die Klingen zu kreuzen, damit die Jungs ihn lebend fangen können. Außerdem bist du auch Eisenpanzer. Sogar die gleiche Gesellschaft. Hattest du so viel Angst, ihn persönlich zu bekämpfen?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict3";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict3":
			dialog.text = "Wie kannst du es wagen, mich der Feigheit zu beschuldigen, Junge "+GetSexPhrase("Mann","Fräulein")+"! Frag jeden, und sie werden dir im Detail erzählen, welche Heldentaten ich für diese Stadt vollbracht habe.";
			link.l1 = "Ich bin noch nicht fertig. Ich fange an zu zweifeln, ob diese 'Heldentaten' von deinen eigenen Händen getan wurden. Du wolltest, dass Tom und ich uns gegenseitig umbringen, damit du den ganzen Ruhm einheimsen kannst. Das hast du schon einmal gemacht, oder?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict4";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict4":
			dialog.text = "Ich habe genug von deinen Anschuldigungen, "+GetSexPhrase("Herr.","Fräulein")+" "+pchar.lastname+". Du willst Konflikt? Du wirst ihn bekommen. Jetzt sofort.";
			link.l1 = "Wahrheit tut weh, nicht wahr, Gabe?";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Conflict = true;
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_1":
			dialog.text = "";
			link.l1 = "Gabe! Es ist so lange her, so viele trostlose Winter! Und schau dich an - du hast immer noch diesen selbstgefälligen Blick, verdammt!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_2";
			CharacterTurnByChr(npchar, characterFromID("Irons"));
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_2":
			dialog.text = "Thomas! Ich sollte mich freuen, denn heute werde ich endlich mit meinen eigenen Händen das vollbringen, was unser Justizsystem seit Jahren nicht geschafft hat. Und da ich guter Laune bin, erlaube ich dir, deine Waffen niederzulegen und uns zu folgen. Du könntest sogar zur Zwangsarbeit zurückgeschickt werden. In diesem Fall bringe ich dich persönlich dorthin.";
			link.l1 = "Heh, zwing mich! Du denkst, ein paar Kerle neben dir würden mich aufhalten!!!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_3";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_3":
			dialog.text = "Wer sagt, dass sie die Einzigen sind, die bei mir sind? Ich spreche von der Person, die gerade neben Ihnen steht.";
			link.l1 = "Was?";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_4";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_4":
			dialog.text = "Thomas, Thomas, Thomas... du bist, wie immer, allein in dieser Welt. Ich habe fast Mitleid mit dir!";
			link.l1 = "Verdammte Ratten! Bastarde!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_5";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_5":
			StartInstantDialog("Irons", "BM_GabePlan_GazgovorTommiAndGabe_6", "Quest\BlackMark.c");
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_6":
			dialog.text = "Was bedeutet das?! Was hat er damit gemeint?!";
			link.l1 = "Tommy, hör zu...";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_7";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_7":
			dialog.text = "Das ist genau das, was ich mache! Sag mir, er lügt!";
			link.l1 = "Leider hat er recht. Legt eure Waffen nieder. Und heute muss niemand sterben. Ich werde selbst ein gutes Wort für euch einlegen, damit ihr nicht gehängt werdet. Ihr könntet sogar eines Tages zu einem ehrlichen Leben zurückkehren.";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_8";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_8":
			dialog.text = "Das ist nicht deine Entscheidung! Und sicherlich nicht deine! Wer braucht Feinde mit einem solchen Kommandeur! Noch eine verdammte Ratte.";
			link.l1 = "Komm schon, Tommy. Für Leute wie dich gibt es keine sauberen Fluchten.";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_9";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_9":
			dialog.text = " Ein Platz in deiner Mannschaft, auf deinem Schiff wäre ein Anfang, wenn du nur bereit wärst, für deine Männer einzustehen! Aber das spielt jetzt keine Rolle mehr. Verdammt seid ihr, alle miteinander! Ich werde eure feigen Eingeweide ausweiden, du kleine Ratte. Und du, Gabe, ich werde versuchen, dich mit mir zu nehmen...";
			link.l1 = "Warte, Tommy, nein!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_GazgovorTommiAndGabe_Fight");
		break;
		
		case "BM_GabePlan_GabeWin_1":
			dialog.text = "Herzlichen Glückwunsch, "+GetSexPhrase("junger Mann","junges Fräulein")+"! Ich bin beeindruckt, dass es dir gelungen ist, Thomas das Gefühl zu geben, dass alles nach seinem Plan verläuft - er hatte eine Nase für Verrat.";
			link.l1 = "Ach, danke, natürlich, Kapitän Callow.";
			link.l1.go = "BM_GabePlan_GabeWin_2";
		break;
		
		case "BM_GabePlan_GabeWin_2":
			dialog.text = "Macht dir etwas Sorgen, "+GetSexPhrase("Herr","Fräulein")+""+pchar.lastname+"?";
			link.l1 = "Tom... er war nicht nur wütend, dass ich auf deiner Seite stand. In seiner Stimme lag echte Verzweiflung und Unverständnis, als ob...";
			link.l1.go = "BM_GabePlan_GabeWin_3";
		break;
		
		case "BM_GabePlan_GabeWin_3":
			dialog.text = "...als wäre er hier das verletzte Opfer. Es war zu erwarten. Denke daran, Charles, ein Monster kann Schmerz empfinden. Aber es hört nicht auf, ein Monster zu sein. Viele Verbrecher sind oft aufrichtig von ihrer Richtigkeit und Unschuld überzeugt.";
			link.l1 = "Ich werde versuchen, das im Hinterkopf zu behalten. Ich denke, wir sind hier fertig, nicht wahr, Kapitän?";
			link.l1.go = "BM_GabePlan_GabeWin_4";
		break;
		
		case "BM_GabePlan_GabeWin_4":
			dialog.text = "Im Allgemeinen ja, aber es bleibt noch eine Sache zu tun, um diesen schönen Tag abzuschließen.";
			link.l1 = "Oh? Was ist es?";
			link.l1.go = "BM_GabePlan_TommiMertv_Mir2";
		break;
		
		case "BM_IronsJamaicaJungle2":
			dialog.text = "Du hast ja lange genug gebraucht. Also dachte ich, ich erkunde ein bisschen. Jedenfalls denke ich, es ist besser, sie hier zu überfallen, anstatt am Strand wie feine Duellanten zu spielen. Ich hoffe, du konntest Gabes Haus finden und hast alles offen gelassen?";
			link.l1 = "Natürlich habe ich, was hältst du mich für einen Idioten? Ich bin tatsächlich dein Kapitän, Tommy. Was würde das aus dir machen, wenn du einem Idioten dienen würdest?";
			link.l1.go = "BM_IronsJamaicaJungle3";
		break;
		
		case "BM_IronsJamaicaJungle3":
			dialog.text = "Ha-ha-ha-ha, du würdest nicht glauben, wie oft ich mit so einem Scheiß im Dienst umgehen musste! Aber in unserem Fall, zum Glück, ist das nicht der Fall. Also gut. Wir erwarten Gesellschaft. Bereit?";
			link.l1 = "Nun, es sei denn, die gesamte Flotte oder die Garnison von Port Royal taucht hier auf, bin ich bereit.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CreateGabeInJungle");
		break;
		
		case "BM_GabeJungle1":
			dialog.text = "Thomas? Bist du es wirklich nach all dem...";
			link.l1 = "Natürlich bin ich es wirklich, oder hast du jemand anderen erwartet, Gabe? Heh, du siehst blass aus, als hättest du einen Geist gesehen. Du bist auch dicker als in Old England.";
			link.l1.go = "BM_GabeJungle2";
			CharacterTurnByChr(npchar, characterFromID("Irons"));
		break;
		
		case "BM_GabeJungle2":
			dialog.text = "Jetzt bin ich endlich überzeugt, dass du es wirklich bist. Unhöflich wie immer. Aber das ist in Ordnung, ich werde dein dreckiges Maul bald für immer stopfen, du Bastard.";
			link.l1 = "Ha-ha-ha, jetzt reden wir! Weißt du, du hast mich tatsächlich enttäuscht, Gabe. Schon wieder! Du hättest offensichtlich mehr Männer mitbringen müssen, um es selbst mit mir alleine aufzunehmen. Und wir sind zu zweit! Oder war das alles, was sie dir übrig lassen konnten, du Feigling?";
			link.l1.go = "BM_GabeJungle3";
		break;
		
		case "BM_GabeJungle3":
			dialog.text = "Genug! Ich sehe keinen Sinn mehr darin, dass wir weiter reden.";
			link.l1 = "Ich stimme Ihnen in diesem Punkt zu! "+pchar.name+"! Zum Kampf, Kapitän!";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GabeJungleFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "BM_IronsJamaicaJungle4":
			dialog.text = "Heh, da hast du's! Ruhe in Frieden, du Bastard.";
			link.l1 = "Nun, bist du zufrieden, Tommy? Du weißt, viele Leute werden nur schlechter, nachdem sie ihre Rache bekommen haben.";
			link.l1.go = "BM_IronsJamaicaJungle5";
		break;
		
		case "BM_IronsJamaicaJungle5":
			dialog.text = "Ha, hast du das irgendwo nachgelesen? Ich habe solche Weicheier nie verstanden. Bah! Bin ich zufrieden? Ich bin so glücklich, dass ich mich fast anpisse! Diese Bastarde waren die Wurzeln meiner größten Unglücke!";
			link.l1 = "Ich freue mich für dich. Gibt es sonst noch jemanden, an dem du dich rächen musst? Darf ich weitere Witzbolde von dir erwarten?";
			link.l1.go = "BM_IronsJamaicaJungle6";
		break;
		
		case "BM_IronsJamaicaJungle6":
			dialog.text = "Beruhige dich, Gabe war der Letzte. Und was die Witze betrifft - keine Sorge, es wird keine mehr geben, zumindest nicht, was dich betrifft.";
			link.l1 = "Sollen wir dann zurück zum Schiff gehen?";
			link.l1.go = "BM_IronsJamaicaJungle7";
		break;
		
		case "BM_IronsJamaicaJungle7":
			dialog.text = "Wir würden sowieso zu ihr zurückkehren, ob ich noch jemanden habe, an dem ich mich rächen kann oder nicht. Warte aber einen Moment...";
			link.l1 = "Ach, also ist es noch nicht vorbei...";
			link.l1.go = "BM_IronsJamaicaJungle8";
		break;
		
		case "BM_IronsJamaicaJungle8":
			dialog.text = "Das ist es, das ist es. Es gibt etwas, das ich dir sagen möchte. Es ist etwas, das ich nur sehr wenigen Menschen sage. Und ich werde es nicht noch einmal sagen. Wenn du über mich lachst, werde ich sehr böse auf dich sein.";
			link.l1 = "Ich verspreche, nicht zu lachen. Wie auch immer, ich finde deine Witze mehr angespannt als lustig.";
			link.l1.go = "BM_IronsJamaicaJungle9";
		break;
		
		case "BM_IronsJamaicaJungle9":
			dialog.text = "Gut. Also. Ich bin sehr dankbar, dass du dich entschieden hast, mir zu helfen, anstatt das zu tun, was Jack getan hat. Du bist ein wahrer Freund, Kapitän. Danke. Außerdem... wenn du willst, kannst du mein vertrautes Schwert und meine Rüstung ausleihen... Was davon übrig ist, ha-ha!";
			link.l1 = "Nun, danke für deine Worte. Es ist nicht jeden Tag, dass man so etwas von seinen Offizieren hört. Komm schon, Kamerad.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_FinalInJungleWithTommy");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Irons_officer":
			dialog.text = "Aaaaye-aye, Kapitän?";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "Also, Rumba, auf wessen Knochen sollen wir heute Nacht tanzen?";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "Ja, Ellie?";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Ich höre, Kapitän.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = ""+pchar.name+"?";
			}
			//////
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal") && !CheckAttribute(pchar, "questTemp.BM_TommiTieyasalOtkaz"))
			{
				Link.l4 = "Tommy, ich möchte dich etwas sehr Ernstes fragen. Es gibt einen... einen Steingötzen der Rothäute. Und ich werde Hilfe brauchen. Ich kann nur meine engsten Freunde darum bitten, wie du. Neulinge oder diejenigen, denen ich noch nicht zu sehr vertraue, werden nicht ausreichen.";
				Link.l4.go = "tieyasal_1";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Tommy, hör auf, die Möwen zu zählen. Hast du die ganze Ladung gezählt? Gib mir einen vollständigen Bericht mit einer Prognose.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Tommy, ab heute brauche ich dich, um bestimmte Waren in den Häfen zu kaufen.";
				Link.l12.go = "QMASTER_2";
				
				if (startHeroType == 4)
				{
					Link.l11 = "Tommy, könntest du bitte alles über das Schiff berichten?";
					Link.l12 = "Tommy, ich werde ziemlich müde. Könntest du an jedem Hafen bestimmte Waren aufstocken?";
				}
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l11 = "Bereite mir einen Bericht über den Zustand des Schiffes und alles darauf vor, Tommy.";
					Link.l12 = "Könnten Sie während unserer Hafenanrufe bestimmte Waren aufstocken?";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l11 = "Zähle alles, was ich auf dem Schiff habe, und berichte über den allgemeinen Zustand.";
					Link.l12 = "Ich brauche dich, um diese Waren zu kaufen, während unserer Anrufe in jedem Hafen.";
				}
			}
			//////
			Link.l1 = "Hör genau auf meinen Befehl!";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "Jemand ist sicher. Aber jetzt hör auf meine Befehle.";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "Hör auf meinen Befehl... Tommy. ";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "Das ist gut, denn ich habe einen neuen Auftrag für dich, Tommy.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "Hör auf meinen Befehl, Tom.";
			}
			Link.l1.go = "stay_follow";
			//////
			link.l2 = "Nichts, Tommy. Ganz entspannt.";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "Wir werden sehen, wie es läuft, Tommy.";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "Nein, Tom, nichts.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "Nein, nichts.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "Nichts, alles ist in Ordnung.";
			}
			link.l2.go = "exit";
			NextDiag.TempNode = "Irons_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Ich habe noch nicht einmal mit dem Inventar angefangen. Du solltest dankbar sein, dass ich überhaupt unsere Gewinne und Verluste zähle, geschweige denn mit diesen gierigen Händlern feilsche. Inventur ist nicht mein Geschäft, musste es in der Armee nie tun, und ich fange jetzt nicht damit an.";
			Link.l1 = "Das ist nicht die Armee, Tommy. Aber gut, ich verstehe, ich werde dich nicht zwingen.";
			if (startHeroType == 4)
			{
				dialog.Text = "Ich bin kein Schreiber, Ellie. Ich kannte mal einen Kerl, Daniel Crimson, der immer behauptete, ein Schreiber zu sein, aber er hatte das Schlachtfeld kaum gesehen. Trotzdem war der Mann ein Biest im Kampf. Das bin ich aber nicht, und ich werde nicht darüber lügen. Inventar ist einfach nicht mein Ding. Ich mache schon unsere Abrechnungen für dich. Dräng mich nicht.";
				Link.l1 = "In Ordnung, Tommy, ich werde nicht.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Schau, ich bin kein Schreiber. Niemand hat das jemals von gewöhnlichen Soldaten wie mir verlangt, selbst nicht in der Armee. Lasst uns diese Regel nicht ändern.";
				Link.l1 = "Okay, lass es uns nicht tun.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Das Einzige, was ich zählen kann, ist, wie viele unserer Feinde ich erschossen habe, ha-ha-ha. Und selbst dann verliere ich den Überblick. Ich bin ein einfacher Soldat, weißt du. Wer zur Hölle weiß etwas über das Schiff - ich war den größten Teil meines Lebens ein Landratte.";
				Link.l1 = "Sieht so aus, als müsste ich es selbst machen.";
			}
			Link.l1.go = "exit";
		break;

		case "QMASTER_2":
			dialog.text = "Wofür hältst du mich, einen Hinterhofquartiermeister? Wir hatten nichts als Verachtung für diese weichschwänzigen Feiglinge daheim. Ich mag zwar kein Adel sein, aber meinen Stolz habe ich immer noch.";
			link.l1 = "Also gut, also gut, wenn du nicht willst, dann willst du nicht.";
			link.l1.go = "exit";
			if (startHeroType == 4)
			{
				dialog.Text = "Hör zu, ich war ein einfacher, ehrlicher Soldat, kein Versorgungsoffizier, mein Mädchen. Ich weiß nicht viel darüber und möchte nicht anfangen zu lernen. Es ist, als würdest du mich bitten, ein Musketen rechtzeitig zusammenzubauen und wieder auseinanderzunehmen.";
				Link.l1 = "Nun, ich könnte jeden Teil der stehenden und laufenden Takelage auf diesem Schiff auswendig benennen. Aber wie du willst, Tom. Die Sache ist erledigt.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Nein, das konnte ich nicht. Vielleicht hast du das vergessen oder weißt es überhaupt nicht, also werde ich es erklären. Für dich wäre das eine Routineaufgabe, aber in unserer Armee behandeln wir Versorgungs- und Hintergrunddienste nicht sehr gut. Bitte zähle mich nicht dazu.";
				Link.l1 = "Ha-ha, gut, gut.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Schau, ich respektiere dich natürlich, aber ich werde mich nicht über mich selbst hinwegsetzen und etwas tun, was ich nicht kann und nicht ertragen kann. Ich habe damals kaum gelernt zu zählen, und du willst, dass ich ein echter Lieferant bin. Übrigens, wir mochten sie nicht - sie sparen an Munition, Wasser, Essen und dessen Frische.";
				Link.l1 = "Hm, okay, lassen wir das.";
			}
		break;
		
		case "stay_follow":
            dialog.Text = ""+GetSexPhrase("Oh, ein Befehl, hm? Du magst die Disziplin und all das Armeezeug, nicht wahr? Ich würde es vorziehen, wenn du mir einfach sagst, was zu tun ist.","Sie sind wie ein Sergeant oder so etwas. Es passt nicht zu Ihnen - Sie sind zu schön dafür. Sie hätten keinen Tag in der Armee überlebt. Aber ich höre zu.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Anscheinend bist du wirklich ein großer Fan von Uniformen, Übungen und all dem. Aber gut, mach weiter.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Welcher?";
			}
			
            Link.l1 = ""+GetSexPhrase("Geh nirgendwohin und tu nichts - beobachte nur, verstehst du? Ich kenne dich.","Bleib genau da, wo du bist, verstehst du mich?")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "Einfach hier stehen bleiben, nirgendwohin gehen und nichts anfassen.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "Bleib hier und lass niemanden durch.";
			}
			Link.l1.go = "Boal_Stay";
            Link.l2 = ""+GetSexPhrase("Folge mir und lass dich durch nichts ablenken - einschließlich herumstreunender Ehefrauen oder plötzlich auftauchender alter Kriegskameraden.","Bleib nah dran, klar? Ich möchte, dass mein Rücken gedeckt ist.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "Folge mir. Ich sehe, du bist in Gedanken verloren.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "Folge mir, sonst bist du aus irgendeinem Grund stehen geblieben.";
			}
			Link.l2.go = "Boal_Follow";
			
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Ich brauche, dass du diesmal etwas anderes schießt.";
					Link.l3.go = "SetGunBullets";
					if (pchar.sex == "man" && pchar.rank >= 15)
					{
						Link.l3 = "Ich brauche, dass du in der kommenden Schlacht verschiedene Munition abfeuerst.";
					}
					if (pchar.sex == "man" && pchar.rank >= 25)
					{
						Link.l3 = "Du wirst in der nächsten Schlacht verschiedene Munition verwenden.";
					}
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Ändere die Art der Munition für dein Musket.";
					Link.l4.go = "SetMusketBullets";
				}
				Link.l5 = "Wechsle deine Prioritätswaffe für den Kampf.";
				Link.l5.go = "SetPriorityMode";
				Link.l6 = "Ich möchte, dass Sie einen gewissen Abstand zwischen Ihnen und Ihren Feinden halten.";
				Link.l6.go = "TargetDistance";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l6 = "Ich möchte, dass du einen gewissen Abstand zum Feind hältst, Tommy.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l6 = "Halte einen bestimmten Abstand zwischen dir und dem Feind, Tommy.";
				}
			}
		break;
		
		case "SetGunBullets":
			Dialog.Text = ""+GetSexPhrase("Welche Art von Geschossen? Ich hoffe, du hast jedes einzelne sorgfältig hergestellt, denn wer weiß, wo sie landen werden, hehe.","Ich schieße für dich auf alles. Was auch immer es ist, aber niemals Platzpatronen, hehe. ")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Ich spüre, dass etwas Interessantes im Gange ist! Okay, welche Art?";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Wieder kämpfen... Okay, welche Art?";
			}
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
            dialog.Text = ""+GetSexPhrase("Sogar wenn du dort verprügelt wirst, hehe? Verstanden, ich werde einfach nur zusehen.","Willst du mich zu einem Wächter machen? Was ist, wenn du verprügelt wirst oder so?")+"";
            Link.l1 = ""+GetSexPhrase("He, pass auf! Wir werden etwas herausfinden, wenn es dazu kommt.","Nun, du wirst doch nicht nur zuschauen, oder? Wenn du denkst, dass dein Kapitän so wunderbar ist, wie du sagst, dann wirst du etwas dagegen tun.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Sogar um den Kopf zu treffen? Okay, okay, schau mich nicht so an, ich verstehe es.";
				Link.l1 = "Ich hoffe es.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Hab keine Angst, niemand wird vorbeikommen.";
				Link.l1 = "Wenn du natürlich niemanden vermisst. Aber gut.";
			}
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = ""+GetSexPhrase("Sehr witzig. Aber ich verstehe, was du meinst.","Oh, mach dir keine Sorgen, dein Rücken ist immer unter meiner wachsamen Augen, hehe.")+"";
            Link.l1 = ""+GetSexPhrase("Gut.","Gott, du bist unausstehlich, Tom.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Nun, ich versuche mich an etwas sehr Wichtiges zu erinnern. Und dann wird mir klar, dass ich nicht einmal weiß, was es ist, da ich damals mein Gedächtnis verloren habe, also wird nichts daraus. Okay, lass uns gehen.";
				Link.l1 = "Scharfsinnig, muss ich sagen.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Nun, ich stehe hier, weil Sie mich früher selbst dazu aufgefordert haben. Ich komme, ich komme.";
				Link.l1 = "Hm-m, okay, okay.";
			}
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = ""+GetSexPhrase("Welche Art von Entfernung? Bedenken Sie, dass ich über zwanzig Meter hinaus nicht genau zielen kann. Es sei denn, natürlich, Sie brauchen mich nicht wirklich, um etwas zu treffen, hehe.","Als ob ich mich stinkenden Männern nähern wollen würde, nachdem ich bei dir war. Also, wie weit ist die Entfernung? Aber denk dran, ich kann mein Feuer nicht wirklich zielen, über zwanzig Yards hinaus, das kann niemand.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "In Ordnung, welche Entfernung? Aber lass mich dich daran erinnern, dass ich im Eifer des Gefechts nicht mehr als zwanzig Meter genau und langsam schießen kann.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Okay. Was? Erinnere dich daran, dass weiter als... nun, wir sind nicht mehr klein, du und ich wissen das.";
			}
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = ""+GetSexPhrase("Du solltest es nicht mit Humor versuchen.","Du hast noch viel von mir über Humor zu lernen, mein Mädchen. Aber du machst Fortschritte!")+"";
				link.l1 = ""+GetSexPhrase("That's odd; I've always been told the opposite.","Very funny, Tommy.")+"";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Nicht dein schlechtester Witz. Vielleicht hörst du eines Tages sogar auf, ein Miesepeter zu sein, heh-heh.";
					Link.l1 = "Ach, na ja.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Ha-ha-ha, guter Witz.";
					Link.l1 = "Eigentlich, ich nur... okay.";
				}
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Nun, dann werde ich einfach stillstehen und meine Position halten. Wenn du sie aus zu großer Entfernung bekämpfst, bist du derjenige, der seinen Arsch riskiert, hehe.";
				link.l1 = "Don't be sarcastic; holding your ground is exactly what I want you to do from now.";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Heh, du hättest mir einfach sagen können, die Linie zu halten, und nicht über Entfernungen und Zahlen reden.";
					Link.l1 = "Nun, das Wichtigste ist, dass du mich verstanden hast.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Verstanden, ich halte hier die Stellung. Dann bring sie näher zu mir, damit ich schießen kann.";
					Link.l1 = "Sicherlich.";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Schau, ich weiß, du möchtest, dass jeder Schuss, den ich abgebe, wie der am Leuchtturm ist, aber das wird nicht passieren. Dort war es eine gute Position. Ruhig und stabil. Das kann man in der Hitze des Gefechts nicht nachahmen.";
				link.l1 = "Hmm. Dann bleib zwanzig Yards entfernt.";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Ich weiß, dass du das mögen würdest, alle Kerle würden das mögen, aber wie damals, im Leuchtturm, wird es nicht mehr funktionieren. Ich brauche einen guten Standpunkt und niemand darf zu mir gelangen, sonst werden meine Nerven nachgeben.";
					Link.l1 = "Hm-m, okay.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Ich habe meine Fähigkeiten seitdem sicherlich geschärft, aber das Unmögliche bleibt unmöglich - im hitzigen Kampf könnte ich niemals diesen Schuss vom Leuchtturm wiederholen. Selbst mit einem Radschlossgewehr.";
					Link.l1 = "Und das Unmögliche ist möglich, Tommy. Aber okay, nein heißt nein.";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = RandPhraseSimple("Sehr gut. Ich werde genau diesen Abstand halten, aber wenn wir in einer Taverne oder Höhle kämpfen, gehe ich nach draußen, um ihn zu halten, hehe.","Ich werde es versuchen. Aber Decks und beengte Räume könnten ihre eigenen Bedingungen diktieren.");
			link.l1 = ""+GetSexPhrase("Nicht lustig, Tommy. Verhalte dich der Situation entsprechend, aber keine Witze oder deine dummen Streiche.","Ich weiß das, Thomas, ich bin nicht dumm.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Ich werde versuchen, mich zu erinnern.";
				Link.l1 = "Okay, ich zähle auf dich.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Ja, Kapitän.";
				Link.l1 = "Ruhig, Tommy.";
			}
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal_1":
			dialog.text = "Hilfe bei was, es zu stehlen? Aber warum? Ich bin natürlich geschmeichelt, aber du hättest schon vor langer Zeit alles sagen können. Los, spuck's aus.";
			link.l1 = "Achte auf deinen Mund, ja? Verdammt noch mal - es ist mir wirklich egal, wie du dich ausdrückst, solange du auf meiner Seite bist. Also, dieses Idol. Durch es kannst du... magisch an einen anderen Ort gelangen. Schau mich nicht so an - ich weiß, wie das klingt. Aber ich habe das schon durchgemacht und alles mit eigenen Augen gesehen. Es ist... sicher, wenn du einen Elixier trinkst.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Ich sehe, du hast schon ein paar Drinks gehabt. Obwohl nein, du scheinst nüchtern zu sein. Und sie sagen über mich, dass ich immer Unsinn rede...";
			link.l1 = "Kommst du mit mir oder nicht? Das Idol soll uns zu einer alten Mayastadt führen, und wer weiß, was uns dort erwartet? Du bist einer von denen, auf die ich in einem schwierigen Moment glaube, mich verlassen zu können. Und jetzt ist gerade ein solcher Moment gekommen.";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "Ich habe ein schlechtes Gefühl bei all dem. Wärst du nicht mein Kapitän, würde ich sagen, du gehörst in eine Irrenanstalt. Als nächstes erzählst du mir noch, dass Gott existiert.";
			link.l1 = "Er tut es, Tommy. Und, wie ich zu meiner Überraschung auf diesem Archipel festgestellt habe, nicht nur unsere. Du könntest all das Teufelszeug, das hier vor sich geht, selbst sehen. Und du hast wahrscheinlich den Einfluss von gesegneten oder verfluchten Krimskrams bemerkt.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "Teufelei existiert auch zu Hause. Und sie hatte immer eine normale Erklärung. Entschuldigung, Kapitän, aber ich werde nicht um Steingötzen mit Ihnen tanzen. Feinde schießen - gerne. Ich habe vielleicht mein Gedächtnis verloren, aber nicht meinen Verstand. Zumindest, denke ich das.";
			link.l1 = "Nun, ich kann dich nicht zwingen. Also... wie du willst, Tommy.";
			link.l1.go = "tieyasal_5";
			link.l2 = "Ich bezweifle, dass du den Mut hast, auf sie zu schießen, du Wagemutiger, wenn du Angst hast, dich dem Idol zu nähern.";
			link.l2.go = "tieyasal_6";
		break;
		
		case "tieyasal_5":
			dialog.text = "Oh, na na, mach kein langes Gesicht. Okay, wenn du zurückkommst, nachdem du um dieses Idol getanzt hast, dann werde ich das nächste Mal darüber nachdenken.";
			link.l1 = "Es gibt vielleicht kein nächstes Mal. Geh zurück zum Schiff, Tom.";
			link.l1.go = "exit";
			pchar.questTemp.BM_TommiTieyasalOtkaz = true;
		break;
		
		case "tieyasal_6":
			dialog.text = "Ich habe keine Angst, versteh mich nicht falsch. Aber ich bin es gewohnt, auf mein Bauchgefühl zu hören, es hat mich im Laufe der Jahre nie im Stich gelassen. Und jetzt sagt es mir, dass nichts Gutes daraus entstehen wird. Und sowieso... Ach, du wirst beleidigt sein.";
			link.l1 = "Geh voran und sag es mir.";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "Nun, wenn das der Fall ist! Ich habe zugestimmt, Seite an Seite mit dir zu kämpfen. Aber was ist, wenn, lass uns mal annehmen, dieses Ding wirklich funktioniert? Was ist, wenn es verflucht ist? Ich werde für niemanden sterben, tut mir leid.";
			link.l1 = "Nun hast du dich bewiesen, Tommy. Ich brauchte jetzt die loyalsten Leute. Und jetzt sehe ich, dass du nicht einer von ihnen bist. Ich gehe dorthin. Und du... mach was du willst.";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "Schau ihn dir an. Er ist doch beleidigt.";
			link.l1 = "Halt dein Maul. Wenn du uns so widerlich findest, musst du nicht zum Schiff zurückkehren.";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "Woah! Meint Ihr das ernst? Nun, vielleicht ist es zum Besten. Ich möchte nicht mit Weicheiern zusammen sein, die nicht mal Witze verstehen. In diesem Fall... Auf Wiedersehen, Eure Exzellenz.";
			link.l1 = "Leb wohl, Tommy. Und fahr zur Hölle.";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			DialogExit();
			RemovePassenger(pchar, npchar);
			DeleteAttribute(npchar, "OfficerImmortal");
			npchar.lifeday = 0;
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
	}
} 