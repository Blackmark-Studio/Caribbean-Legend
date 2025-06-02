void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ref chr, sld, rShip, rItm, rItem;
    float  fTemp;
    bool bOk;
	int i, iTemp;
	string sAttr, sGun, sBullet, attrL;
	aref rType;
    
	// генератор ИДХ по кейсу -->
	sAttr = Dialog.CurrentNode;
  	if (findsubstr(sAttr, "CabinCompanionTalk_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.CabinCompanionNum = strcut(sAttr, i+1, strlen(sAttr)-1); // индекс в конце
 	    Dialog.CurrentNode = "Cabin_Companion_Talk";
 	}
	
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	if (findsubstr(sAttr, "tonzag_jail_" , 0) != -1) {
	 	pchar.questTemp.Tonzag.JailDialog.ID = strcut(sAttr, strlen("tonzag_jail_"), strlen(sAttr) - 1);
		DeleteAttribute(pchar, "questTemp.TonzagQuest.JailDialog." + pchar.questTemp.Tonzag.JailDialog.ID);
		AddDialogExitQuestFunction("Tonzag_InJailDialog");
 	    Dialog.CurrentNode = "exit";
 	}
 	// генератор ИДХ по кейсу <--

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		
		case "First time":
	      	NextDiag.TempNode = "First time";

	        Dialog.Text = "Wenn du diese Zeile liest, ist es ein Fehler im Code";
			Link.l1 = "Schließen";
			Link.l1.go = "exit";
			
			//--> Вступительный туториал на палубе корабля за Шарля
		if (CheckAttribute(pchar, "questTemp.SharlieTutorial_TrumDialogSamSoboi_1"))
		{
			dialog.text = "Verdammt aufregend! Ein echtes Seegefecht!\nSchade nur, dass ich die Schlacht von hier aus nicht sehen kann... Na gut. Ich kenne mich inzwischen gut genug mit dem Seemannshandwerk aus, um mir den Ablauf gut vorstellen zu können\nWahrscheinlich fünf Piratenschiffe... Ein großes, ein paar mittlere und kleinere. Genau richtig für unsere Pinasse. Das gibt eine großartige Geschichte — Lulu wird begeistert sein!";
			link.l1 = "...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.SharlieTutorial_TrumDialogSamSoboi_1");
			pchar.wind.speed = 18.0;
			fWeatherSpeed = stf(18.0);
			//AddDialogExitQuestFunction("SharlieTutorial_StartShip");
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_3");
		}
		/*if (CheckAttribute(pchar, "questTemp.SharlieTutorial_TrumDialogSamSoboi_2"))
		{
			dialog.text = "Sieht so aus, als wären wir geentert worden...";
			link.l1 = "...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.SharlieTutorial_TrumDialogSamSoboi_2");
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva");
		}*/
		//<-- Вступительный туториал на палубе корабля за Шарля

			//--> Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC_FindIsland"))
    		{
    		    dialog.text = "Also, wir haben diesen Ort auf der Karte gefunden. Ich sollte ihn markieren, und wir können mit der Suche beginnen.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuestFunction("SearchingForIslandOnMap");
    		}
			if (CheckAttribute(pchar, "questTemp.HWICMC") && pchar.questTemp.HWICMC == "Fleetwood")
    		{
    		    dialog.text = "Also gut, wir sind hier. Ich sollte mein Schiff in der südlichen Bucht verstecken, dann zu Fuß durch den Dschungel zurückkommen und Fleetwood eine böse Überraschung bereiten.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				pchar.quest.Fleetwood_repeatShore.win_condition.l1 = "ExitFromLocation";
				pchar.quest.Fleetwood_repeatShore.win_condition.l1.location = pchar.location;
				pchar.quest.Fleetwood_repeatShore.function = "Fleetwood_repeatShore";
    		}
			//<-- Голландский гамбит
			
			//--> Ложный след
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "TalkCabinWoman" && PChar.location == Get_My_Cabin()) 
	        {
				dialog.text = "Hm... Diesem Schurken zu vertrauen ist gefährlich, obwohl seine Geschichte echt zu sein scheint. Vielleicht lügt er diesmal nicht. Aber trotzdem, ich sollte mit seiner Frau sprechen... Bootsmann! Bring mir diese gefangene Frau!";
    			link.l1 = "Aye Aye, Kapitän!";
	    		Link.l1.go = "exit";
				chr = characterFromId("FalseTraceWife");
				chr.dialog.currentnode = "FalseTrace_wife_6";
				pchar.questTemp.FalseTrace.CharID = "FalseTraceWife";
				AddDialogExitQuest("SetFalseTraceCharToCabin");
	    	}
			//<-- Ложный след
			
			//--> Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "DigGems")
    		{
    		    dialog.text = "Das scheint der Ort zu sein. Es ist der einzige saftlose Baum in der Nähe. Ich sollte hier graben.";
    			link.l1 = "(grabe den Schatz aus)";
    			link.l1.go = "exit";
				AddDialogExitQuest("FindPortugalGems");
    		}
			//<-- Португалец
			// Сага
			if (CheckAttribute(pchar, "questTemp.Saga.JessSoul"))
    		{
    		    dialog.text = "Was geht hier vor? Wo bin ich?! Was ist das für ein Ort?";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuest("Saga_JessikaSoul_2");
    		}
            //--> приколы со стуком в дверь Диффиндура, LSC
			if (CheckAttribute(pchar, "questTemp.LSC.DiffIndoor"))
    		{
    		    dialog.text = "Das ist die Tür, die zu den inneren Räumlichkeiten des Schiffes führt. Sie ist verschlossen... Hawk muss hier sein. Was hat Ole nochmal erwähnt? Ich sollte ein geheimes Klopfzeichen verwenden.";
    			link.l1 = "Klopf zweimal.";
    			link.l1.go = "knock_2";
				link.l2 = "Klopfe dreimal.";
    			link.l2.go = "knock_3";
				link.l3 = "Klopf einmal, Pause, klopf dreimal.";
    			link.l3.go = "knock_1_3";
				link.l4 = "Klopf zweimal, Pause, klopf zweimal.";
    			link.l4.go = "knock_2_2";
				link.l5 = "Dreimal klopfen, Pause, einmal klopfen.";
    			link.l5.go = "knock_3_1";
    		}
			//<-- приколы со стуком в дверь Диффиндура, LSC
			
			//--> напялили водолазный скафандр, для перехода в режим шага
			if (pchar.model == "protocusto")
    		{
    		    dialog.text = "Wahnsinn! Das Ding ist wirklich schwer!";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			//<-- водолазный скафандр
			// отказ от телепортации
			if (IsCharacterInLocator(pchar, "item", "dolly1") || IsCharacterInLocator(pchar, "item", "dolly2") || IsCharacterInLocator(pchar, "item", "dolly3"))
    		{
    		    dialog.text = "Nein-nein-nein! Auf keinen Fall! Drei Mal waren mehr als genug!";
    			link.l1 = "...";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "roof")
    		{
    		    dialog.text = "Es ist vollbracht. Levasseur ist tot. Es stellte sich als viel einfacher heraus, als ich erwartet hatte... Aber etwas stimmt nicht. Thibaut hat nicht einmal mit Martene gesprochen! Das bedeutet, dass entweder Robert mich verraten hat oder es einen Unfall gab\nAber wohin könnte dieser Bastard Thibaut laufen? Er muss Catherine jagen. Ich muss schnell handeln, wenn ich das Mädchen lebend vor seiner Nase wegnehmen will...";
    			link.l1 = "";
    			link.l1.go = "terrapin";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
    		{
    		    dialog.text = "Schätze, Schätze... eine indische Stadt... Ich glaube nicht an solche Zufälle... Ich wette, dass mein Bruder etwas mit dem Verschwinden der Fregatte von Dichoso zu tun hatte. Er hat wahrscheinlich dafür gesorgt, dass Dichoso nie wieder sein Maul aufmacht\nOder vielleicht hat er mit ihm zusammengearbeitet, die Spanier müssen Gründe gehabt haben zu glauben, dass Dichoso irgendwo hier in der Nähe ist. Das ergibt keinen Sinn. Aber ich bin sicher, dass das indische Gold, welches Michel an de Poincy liefern sollte, sowie das Gold von Miguel Dichoso das gleiche Gold ist. Die Geschichte des Gefangenen stimmt mit dem überein, was der Offizier mir über die Abenteuer meines Bruders erzählt hat\nKomisch, Michel hat es nicht geschafft, das Gold zu liefern, und Miguel auch nicht! Und wo sind dann jetzt die Schätze? Vielleicht waren sie der Grund, warum mein Bruder so in Eile war\nAlso, das Gold zu finden würde bedeuten, zwei Fliegen mit einer Klappe zu schlagen: Ich werde meinem frechen Bruder wieder in die Augen sehen und... ja, Gold ist immer gut. Aber wie zur Hölle finde ich es? Es scheint, dass es Zeit ist, den Spaniern richtig nahe zu kommen\nDon Ramona Mendoza ist nicht mehr im Spiel, ich bezweifle, dass ich mit ihm fertig werde, aber der heilige Vater Vincento, der schlimmste Feind eines Barons... er wird es tun. Seine Art ist nicht skrupellos, aber liebt Geld und üble Mittel\nDichoso, Dichoso... Ich habe diesen Nachnamen schon einmal gehört... oder habe ich nicht? Was auch immer, zur Hölle damit. Ich sollte zum Offizier gehen und den spanischen Gefangenen fordern. Dann kann ich jederzeit nach Santiago aufbrechen.";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore")
    		{
    		    dialog.text = "Vanille wurde schon lange auf die Karracke geladen und ihre Segel sind schon lange am Horizont verschwunden - und dieses verdammte Galeon ist statt auf hoher See wieder im Hafen aufgetaucht. Ich darf mit meinem Schiff nicht im Hafen auftauchen - es ist am besten, wenn sie denken, dass ich Guadeloupe verlassen habe... Ich denke, ich werde durch den Dschungel in die Stadt gehen und nach meinem lieben Marchais fragen...";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "galeon")
    		{
    		    dialog.text = "Es gibt nur wenige Wachen auf dem Oberdeck, alle ziemlich schläfrig. Ich denke, ich könnte sie alle nacheinander ausschalten, wenn ich leise von hinten komme und sie mit einem Schlagring auf den Hinterkopf schlage... ";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth_room"))
    		{
    		    dialog.text = "Ein unverschlossenes leeres Haus mit einem gemütlichen Zimmer im zweiten Stock, und in der Nähe von Calhouns Wohnungen... Das ist geradezu eine Antwort auf das Gebet eines Mädchens... Wenn ich aus dem Fenster steige und auf dem Lampenschirm des Daches laufe, schleiche ich mit Leichtigkeit in Archies Zimmer. Aber das muss nachts geschehen, damit ich nicht erwischt werde...";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("GuardOT_FindWayToRoom");
    		}
			// Поиски Ксочитэма
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "half_pearl")
    		{
    		    dialog.text = "Endlich! Ich habe den Ort gefunden, der von der 'Manifestation' angezeigt wurde: Es ist ein indianisches Idol. Wenn man in der Nähe ist, hört der 'Pfeil des Weges' auf zu oszillieren und zeigt in eine Richtung. Nun, das scheint logisch - indische Magie und ein indianisches Idol. Jetzt sollte ich den vom 'Pfeil des Weges' angegebenen Ort auf der Karte markieren, und dann werde ich nach Dominica gehen.";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindFirstWay");
    		}
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "half_dominica")
    		{
    		    dialog.text = "Endlich! Ich habe den Ort gefunden, der durch die 'Manifestation' angezeigt wird: Es ist ein Indianeridol. In der Nähe hört der 'Pfeil des Weges' auf zu schwingen und zeigt in eine Richtung. Nun, es scheint logisch - Indianische Magie und ein Indianeridol. Jetzt sollte ich den vom 'Pfeil des Weges' angezeigten Ort auf der Karte markieren, und dann werde ich zur Hauptstadt gehen.";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindSecondWay");
    		}
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "full")
    		{
    		    dialog.text = "Beide Erscheinungen wurden gefunden! Nun muss ich die zweite Richtung auf der Karte markieren. Die Kreuzung dieser beiden Richtungen wird mir die Lage der Insel Ksocheatem zeigen.";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindFullWay");
    		}
			// рассуждения по Тайясалю
			if (CheckAttribute(pchar, "questTemp.Tieyasal_CabinTalk"))
    		{
				if (pchar.questTemp.Tieyasal_CabinTalk == "calendar")
				{
					dialog.text = "Alonso de Maldonado sagte, dass es einen Weg nach Tayasal gibt, der nördlich von Yucatan beginnt. Das bedeutet, dass ich tief in den Dschungel der Gegend gehen sollte. Aber Gino sagte, die Teleportationsstatuen sollten ursprünglich Menschen nach Tayasal bringen\nUnd der Miskito-Schamane Schlange Auge erzählte mir, die Idole seien dazu bestimmt, die 'Verschlungenen' an den Ort zu schicken. Aber warum sind diese Portale dann kaputt? Hm. Außerdem zeigt die Karte der Zwei Manifestationen einen seltsamen Kreis in der Nähe der Miskito-Statue\nWas zum Teufel bedeutet das? Ein weiterer magischer Ort? Oder zeigt es, dass die Statue dort einige zusätzliche Funktionen hat? Ich vermute, ich sollte dem Schamanen einen Besuch abstatten. Oder ich kann nach Nordwesten von Main gehen und dort nach dem Weg suchen, in einer der lokalen Buchten.";
					link.l1 = "";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Alonso de Maldonado sagte, dass es einen anderen Weg nach Tayasal vom nördlichen Teil der Halbinsel Yucatan gibt. Das bedeutet, ich muss einen Weg in die Tiefen des Dschungels suchen. Wahrscheinlich beginnt der Weg, den ich brauche, an einer der Buchten im nordwestlichen Haupt.";
					link.l1 = "";
					link.l1.go = "exit";
				}
				AddDialogExitQuest("Tieyasal_AfterCabinTalk");
    		}
			// решаем - титры или фриплей 010912
			if (CheckAttribute(pchar, "questTemp.Tieyasal_final"))
    		{
				dialog.text = "Es ist vollbracht. Das Ende meiner langen Reise. Ich hätte mir niemals vorstellen können, dass die Rettung meines Bruders aus dem Gefängnis bedeutete, mich auf den finalen Kampf gegen ihn vorzubereiten! Dass ich unsere Welt fast zum Untergang verurteilt hätte. Gott sei Dank, es ist vorbei\nNichts hält mich länger in der Karibik. Zeit, nach Hause, nach Frankreich, zurückzukehren. Aber... möchte ich das wirklich?";
				link.l1 = "Ja, ich kehre nach Europa zurück.";
				link.l1.go = "final_1";
				link.l2 = "Nein, ich bleibe hier in der Karibik.";
				link.l2.go = "final_2";
    		}
			// фэйловый финал 040912
			if (CheckAttribute(pchar, "questTemp.Europe"))
    		{
				PlaySound("Voice\English\military02.wav");
				dialog.text = "Hast du den Oberst gehört? Die Rebellen verstecken sich dort! Durchsuche alles, kehre das Haus auf den Kopf und ergreife jeden, den du dort findest! Mach dich an die Arbeit!";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuest("Europe_SharlieFinal_2");
    		}
			// Addon-2016 Jason, французские миниквесты (ФМК) Гваделупа
			/*if (CheckAttribute(pchar, "questTemp.FMQG.Info") && pchar.location == "Bridgetown_Plantation")
    		{
    		    dialog.text = "Dies ist der beste Ort für einen Hinterhalt. Ich sollte hier auf Pinettes Ankunft warten.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuest("FMQG_KidnappingInfo");
    		}*/
			// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN.Choose") && pchar.location == "shore40")
    		{
				dialog.text = "Hm. Diese Geschichte fühlt sich nicht richtig an. Ich glaube, dass dieser Schoner aus St. Jones nie existieren sollte. Der Leutnant zieht mich in seine militärische Operation. Warum brauche ich das? Ich bin nicht im Krieg mit den Niederländern... Was soll ich tun? Soll ich gehen und den Briten ihren Spaß alleine lassen? Oder soll ich bleiben?";
				link.l1 = "Geh weg.";
				link.l1.go = "FMQN_1";
				link.l2 = "Bleib.";
				link.l2.go = "FMQN_2";
    		}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Chest") && pchar.location == "shore37")
    		{
    		    dialog.text = "Also, die Truhe ist vorbereitet. Ich könnte versuchen, all das benötigte Material selbst zu finden, aber ich würde lieber zu Fadey gehen. Er scheint mir ein Mann zu sein, der alles beschaffen kann.";
    			link.l1 = "*NUTZEN SIE DIE OPTION LAUT ZU DENKEN, UM DIE SAMMLUNG VON MUNITION ABZUSCHLIESSEN*";
    			link.l1.go = "exit";
				AddDialogExitQuest("Mtraxx_PlantChestReadyExit");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Boats") && pchar.location == "Maracaibo_river")
    		{
    		    dialog.text = "Also, wir müssen sechs Langboote bauen. Dafür brauche ich einen Zimmermann, 20 Bretter und 10 Lederpakete";
    			link.l1 = "*NUTZT DIE LAUT NACHDENKENDE OPTION, UM LANGBOOTE ZU BAUEN*";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Boats");
				AddQuestRecord("Roger_5", "11");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Powder") && pchar.location == "shore10")
    		{
    		    dialog.text = "Also, ich beabsichtige, diesen Haufen alter Bäume einfach in die Luft zu jagen. Alles, was ich dazu brauche, sind 300 Einheiten Schießpulver, nur um sicher zu gehen.";
    			link.l1 = "*benutze eine Option für lautes Denken, um eine Schießpulverplatzierung zu befehlen*";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.Powder");
				pchar.questTemp.Mtraxx.Retribution = "powder";
				chrDisableReloadToLocation = false;
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.ExitClosed") && pchar.location == "Judgement_dungeon_01")
    		{
    		    dialog.text = RandSwear()+" Der Ausgang ist versiegelt! Es scheint, sie haben die Tür mit etwas Schwerem blockiert! "+RandSwear()+"\nRuhe... Was zur Hölle?";
    			link.l1 = "";
    			link.l1.go = "mtraxx_dungeon";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.ExitClosed");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Bead") && pchar.location == "Judgement_church")
    		{
    		    dialog.text = "Das ist es... Endstation\n Es sieht so aus, als ob Don Enrico es ernst meinte: es gibt keinen Ausweg aus diesen Verliesen. Ich hatte einen Moment der Hoffnung, als ich eine zweite Tür auf Wasserniveau fand, aber jetzt... Ich habe die Zeit aus den Augen verloren - wie lange habe ich schon in diesen dunklen Tunneln gelauert? Ein halber Tag, der ganze Tag? Dieser Ort ist so still und beängstigend wie ein Sarg\nSie hatten hier einmal eine Kirche, genau hier. Was für ein perfekter Ort, um meine Gebete zu sprechen. Ich habe viel zu viel gesündigt... Ich werde hier beten und schlafen, meine Wunden und meine Erschöpfung bringen mich um. Wenn ich Glück habe, werde ich nie wieder aufstehen...";
    			link.l1 = "";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.Bead");
				AddDialogExitQuestFunction("Mtraxx_RetributionBead");
    		}
			// belamour legendary edition -->
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice") && pchar.questTemp.Mtraxx.Retribution.Choice == "to_choice")
			{
				dialog.text = "";
    			link.l1 = "Ich, Charles de Maure, französischer Kapitän und Adliger, schwöre mir selbst und meinem Gewissen, dass ich mit meiner Piratenvergangenheit ein für alle Mal fertig bin!";
    			link.l1.go = "Good_Choice";
				link.l2 = "Ja! Ja! Ah ha ha!! Ich habe es geschafft, ich habe überlebt! Friss das, Zorro! Fahr zur Hölle, Marcus! Jetzt bin ich auf mich allein gestellt! Charlie Prince mag gestorben sein, aber Charles de Maure wird niemand jemals töten!";
    			link.l2.go = "Bad_Choice";
			}
			// <-- legendary edition
			
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog")) {
				dialog.text = "Was sollen wir tun?";
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.FirstTime")) {
					DeleteAttribute(pchar, "questTemp.TonzagQuest.JailDialog.FirstTime");
					dialog.text = "...natürlich, Levasseur ist kein Narr. Sonst, warum müssten sie uns gerade in diesem Moment verhaften?\nUnd sie haben kein Wort gesagt!\n"+dialog.text;
				}
				
				DeleteAttribute(link, "l1");
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Helena")) {
					link.l1 = "Helen, warum bist du so still?";
					link.l1.go = "tonzag_jail_helena";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Mary")) {
					link.l2 = "Mary, warum siehst du so glücklich aus?!";
					link.l2.go = "tonzag_jail_mary";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Tichingitu")) {
					link.l3 = "Tichingitu? Sag etwas Passendes für die Situation.";
					link.l3.go = "tonzag_jail_tichingitu";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Tonzag")) {
					link.l4 = "Hercule, kannst du mich hören? Was werden wir tun?";
					link.l4.go = "tonzag_jail_tonzag";
				}
				
				link.l5 = "Nichts zu machen. Ich schätze, ich werde eine Weile Michels Schuhe tragen.";
				link.l5.go = "tonzag_exit";
			}
			
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailPanic")) {
				dialog.text = "";
				link.l1 = "Oh mein Gott, sie haben Hercule getötet!";
				link.l1.go = "exit";
				link.l2 = "Ihr Bastarde!";
				link.l2.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.TonzagQuest.JailPanic");
				AddDialogExitQuestFunction("Tonzag_GFAfterShot");
			}
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.RefusedGame")) {
				dialog.text = "Was für ein Abend! Warum habe ich ihr zugehört? Bruder hatte recht - die Mädchen hier sind völlig anders. Vielleicht fügen sie etwas zum Rum hinzu?";
				link.l1 = "Zeit zu schlafen, und dann - nach Cartagena!";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.RefusedGame");

				AddDialogExitQuestFunction("HelenDrinking_LightsOut1");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_OsmatrivaemSunduk")) {
				dialog.text = "Nichts wurde gestohlen, obwohl alles herumliegt. Sogar die Wertsachen sind unberührt. ";
				link.l1 = "Sie wollten mich nicht ausrauben - sie suchten nach etwas Bestimmtem. Aber was? Und noch wichtiger, wer...?";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_OsmatrivaemSunduk");

				AddDialogExitQuest("PZ_OsmatrivaemSunduk_3");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_GotovimShlupki")) {
				dialog.text = "Lassen wir bis zum Einbruch der Nacht warten und dann angreifen!";
				link.l1 = "Wir werden in der Zwischenzeit damit beginnen, die Langboote vorzubereiten.";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_GotovimShlupki");

				AddDialogExitQuest("PZ_ShturmZvezdy");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_TiboUkralDevu")) {
				dialog.text = "Oh mein Gott... Nein, nein, nein... ";
				link.l1 = "";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_TiboUkralDevu");
				
				LAi_SetActorType(pchar);
				LAi_ActorAnimation(pchar, "kneeling", "1", 7.5);
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_DevaMertva")) {
				dialog.text = "Oh Gott, oh Gott, oh Gott... Warum? Oh Gott, warum... aber ich habe alles getan, was ich konnte...";
				link.l1 = "Es ist alles meine Schuld, nur meine. Ich bin nicht rechtzeitig hier angekommen. Es tut mir so leid... Bitte, bitte verzeih mir.";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_DevaMertva");

				AddDialogExitQuest("PZ_TortureRoom_Levasser_DevushkaMertva8");
			}
		break;
		
		// boal -->
		case "TalkSelf_Main":
	   		NextDiag.TempNode = "First time";
//navy --> after duel in tavern
			if (CheckAttribute(pchar, "questTemp.LocationClone"))
			{
				Dialog.Text = RandPhraseSimple("Das war ein verdammt guter Kampf... Jetzt können wir diese Feiglinge, die weggelaufen sind, so auch nennen...","Ha! Das war einfach. Und diese Landratten haben sich einfach verstreut!");
				link.l1 = "...";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.LocationClone");
				break;
			}
//navy <--
	        Dialog.Text = RandPhraseSimple("Hmm... Also, was sollte ich jetzt tun?","Was jetzt zu tun?");
	        if (!bDisableMapEnter && pchar.location == Get_My_Cabin())
	        {
				//navy --> 13.02.08
				if (!bDisableMapEnter && GetCompanionQuantity(PChar) > 1)
				{
    				link.l3 = "Ruf nach einem Kameraden.";
    				link.l3.go = "Cabin_CompanionSelect";
				}
				//navy <--
			}
			else 
			{   //исп.линейка, квест №6, возможность переночевать в оплаченной комнате
				if (CheckAttribute(pchar, "questTemp.State.Open") && pchar.location == "Tortuga_tavern_upstairs")
				{
					if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 10.0)
	    			{
	    				link.l1 = "Ruhe bis zum Morgen.";
	    				link.l1.go = "TalkSelf_room_day";
	    			}
	    			else
	    			{
	    				link.l1 = "Ruhe bis zur Nacht.";
	    				link.l1.go = "TalkSelf_room_night";
	    				link.l2 = "Ruhe bis zum nächsten Morgen.";
						link.l2.go = "TalkSelf_room_day";
	    			}
				}
			}
	        if (!bDisableMapEnter)//боя в море нет
	        {
	            if (GetCargoGoods(pchar, GOOD_SLAVES) > 0)
	            {
	                Link.l5 = "Nehmt die Sklaven in die Mannschaft auf.";
	        		Link.l5.go = "TalkSelf_SlavesToCrew";
	    		}
	        }
	        // захват города
	        if (GetCharIDXForTownAttack(pchar.location) != -1 && !CheckAttribute(Pchar, "GenQuestFort.StartAttack") && !CheckAttribute(Pchar, "questTemp.Sharlie.DefendSP"))
	        {
	            Link.l6 = "Beginne mit der Eroberung der nächstgelegenen Stadt.";
	    		Link.l6.go = "TalkSelf_TownAttack";
	        }
	        
			bool bSeaBattle = (bDisableMapEnter) && (bSeaActive) && (!CheckAttribute(pchar, "GenQuest.MapClosedNoBattle"));
	        if(!bSeaBattle && PChar.location != "Deck_Near_Ship" && findsubstr(PChar.location, "_shipyard" , 0) == -1 && PChar.location != "CommonPackhouse_2" && !CheckAttribute(pchar, "GenQuest.CannotWait") && !CheckAttribute(loadedLocation, "CannotWait")) 
	        {
	        	Link.l7 = "Ich sollte mich ausruhen...";
	    		Link.l7.go = "TalkSelf_StartWait";
	    	}
			
			if(CheckAttribute(pchar, "equip.gun"))
			{
				if(CheckAttribute(pchar, "chr_ai.gun.bulletNum") && sti(pchar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l8 = "Ich möchte die Munition für die Feuerwaffen wechseln.";
					Link.l8.go = "SetGunBullets";
				}	
			}
			
			if(CheckAttribute(pchar, "equip.musket"))
			{
				if(CheckAttribute(pchar, "chr_ai.musket.bulletNum") && sti(pchar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l9 = "Ich möchte die Munition für die Muskete wechseln.";
					Link.l9.go = "SetMusketBullets";
				}
					Link.l10 = "Ich möchte eine Prioritätswaffe für den Kampf auswählen.";
					Link.l10.go = "SetPriorityMode";
			}
			
			Link.l19 = "Ich möchte einen Trank zur ständigen Verwendung auswählen.";
			Link.l19.go = "ChoosePotion";
			
			//--> Голландский гамбит
			if(CheckAttribute(pchar, "questTemp.HWIC_Coordinates") && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l11 = "Versuche, die Insel anhand der Koordinaten auf der Karte zu finden.";
	    		Link.l11.go = "Seek_AbyIsland";
	    	}
			//<-- Голландский гамбит
			
			//--> Ложный след
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "TalkCabin" && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l13 = "Rufe Adam Rayner herbei.";
	    		Link.l13.go = "FalseTrace_Cabin";
	    	}
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "CatchAdam" && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l13 = "Nimm Adam Rayner gefangen.";
	    		Link.l13.go = "FalseTrace_Cabin";
	    	}
			//<-- Ложный след
			// Addon 2016-1 Jason Пиратская линейка
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Ammo") && PChar.location == "Shore37") // прогон 3
	        {
	        	Link.l17 = "Zähle den Inhalt der Truhe zusammen und entscheide, die Munitionssammlung für Picard abzuschließen.";
	    		Link.l17.go = "mtraxx_ammo";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Mutiny") && pchar.location == "Maracaibo_Plantation" && stf(environment.time) >= 3.00 && stf(environment.time) < 4.00) 
	        {
	        	Link.l17 = "Gib den Befehl, die Plantage in Maracaibo anzugreifen.";
	    		Link.l17.go = "mtraxx_mutiny";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "merida_boats" && pchar.location == "Maracaibo_river") 
	        {
	        	Link.l17 = "Gib einen Auftrag zum Bau von Langbooten.";
	    		Link.l17.go = "mtraxx_boats";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "powder" && pchar.location == "shore10") 
	        {
	        	Link.l17 = "Befehl, das Schießpulver zur toten Schanze zu liefern.";
	    		Link.l17.go = "mtraxx_powder";
	    	}
			// Jason Долго и счастливо
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "letter") 
	        {
	        	Link.l18 = "Denk an eine Hochzeit.";
	    		Link.l18.go = "LH_marry";
	    	}
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "marry_offer" && LongHappy_CheckShore()) // 28-03-20
	        {
	        	Link.l18 = "Mach einen Heiratsantrag.";
	    		Link.l18.go = "LH_marry_3";
	    	}
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "toIslaTesoro" && pchar.location == "Pirates_town") 
	        {
	        	Link.l18 = "Bereitet die Feier vor.";
	    		Link.l18.go = "LH_marry_4";
	    	}
			// -->Авторемонт			
			if(Pchar.Location == Pchar.location.from_sea && CheckOfficersPerk(pchar, "SelfRepair") && CheckSelfRepairConditions()) 
			{
				Link.l14 = "Beginne mit der Reparatur der Schiffe";
				Link.l14.go = "StartSelfRepair";
			}			
			// <--Авторемонт
			//--> завершение игры
			if(CheckAttribute(pchar, "questTemp.Tieyasal_WinEnd")) // patch-9
	        {
	        	Link.l15 = "Beende das Geschäft in der Karibik und segel nach Europa.";
	    		Link.l15.go = "final_1";
	    	}
			//<-- завершение игры
			Link.l20 = RandPhraseSimple("Nicht jetzt. Es gibt keine Zeit.","Keine Zeit dafür, zu viel zu tun.");
			Link.l20.go = "exit";
		break;
		
		case "tonzag_exit":
			DialogExit_Self();
			AddDialogExitQuestFunction("Tonzag_CreateKiller");
		break;
		
		case "StartSelfRepair":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			LaunchRepair(pchar);
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Wähle den Munitionstyp:";
			sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(pchar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;
		
		case "SetGunBullets2":
			i = sti(PChar.GenQuest.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(pchar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar,"GenQuest.SetGunBullets");
			DialogExit_Self();
		break;
		
		case "SetMusketBullets":
			Dialog.Text = "Wähle den Munitionstyp:";
			sGun = GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(pchar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
				Link.(attrL).go = "SetMusketBullets1_" + i;
			}
		break;
		
		case "SetMusketBullets2":
			i = sti(PChar.GenQuest.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(pchar, "musket", sBullet);
			LAi_GunSetUnload(pchar, "musket");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar,"GenQuest.SetMusketBullets");
			DialogExit_Self();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "Zu Beginn des Kampfes benutze ich:";
			Link.l1 = "Klinge";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Muskete";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			pchar.PriorityMode = 1;
			DialogExit_Self();
		break;
		
		case "MusketPriorityMode":
			pchar.PriorityMode = 2;
			DialogExit_Self();
		break;
		
		case "ChoosePotion":
			Dialog.Text = "Wähle Trank:";
	    	Link.l1 = "Heiltrank.";
	    	Link.l1.go = "ChoosePotion1";
			Link.l2 = "Elixier.";
	    	Link.l2.go = "ChoosePotion2";
			Link.l3 = "Mischung.";
	    	Link.l3.go = "ChoosePotion3";
			Link.l4 = "Ingwerwurzel.";
	    	Link.l4.go = "ChoosePotion4";
			Link.l5 = "Rum.";
	    	Link.l5.go = "ChoosePotion5";
			Link.l6 = "Wein.";
	    	Link.l6.go = "ChoosePotion6";
			if (CheckAttribute(pchar, "GenQuest.Potion_choice"))
			{
				Link.l7 = "Ich möchte Tränke automatisch auswählen.";
				Link.l7.go = "ChoosePotion7";
			}
			Link.l8 = "Warte, ich habe meine Meinung geändert..";
	    	Link.l8.go = "ChoosePotion8";
		break;
		
		case "ChoosePotion1":
			log_info("Heiltrank als Standard ausgewählt.");
			pchar.GenQuest.Potion_choice = "potion1";
			DialogExit_Self();
		break;
		
		case "ChoosePotion2":
			log_info("Elixier als Standard ausgewählt.");
			pchar.GenQuest.Potion_choice = "potion2";
			DialogExit_Self();
		break;
		
		case "ChoosePotion3":
			log_info("Mischung als Standard ausgewählt.");
			pchar.GenQuest.Potion_choice = "potion4";
			DialogExit_Self();
		break;
		
		case "ChoosePotion4":
			log_info("Ingwerwurzel als Standard ausgewählt.");
			pchar.GenQuest.Potion_choice = "potion5";
			DialogExit_Self();
		break;
		
		case "ChoosePotion5":
			log_info("Rum als Standard ausgewählt.");
			pchar.GenQuest.Potion_choice = "potionrum";
			DialogExit_Self();
		break;
		
		case "ChoosePotion6":
			log_info("Wein als Standard ausgewählt.");
			pchar.GenQuest.Potion_choice = "potionwine";
			DialogExit_Self();
		break;
		
		case "ChoosePotion7":
			log_info("Tränke werden automatisch ausgewählt.");
			DeleteAttribute(pchar, "GenQuest.Potion_choice");
			DialogExit_Self();
		break;
		
		case "ChoosePotion8":
			DialogExit_Self();
		break;
		
		case "TalkSelf_StartWait":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			PChar.GenQuest.CallFunctionParam = "LaunchTavernWaitScreen";
			DoQuestCheckDelay("CallFunctionParam", 0.1); // Нужно с задержкой, иначе - ГГ начинает крутиться
		break;
		
		case "TalkSelf_room_night":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Night");
			TavernWaitDate("wait_night");
			DialogExit_Self();
		break;

		case "TalkSelf_room_day":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Day");
			TavernWaitDate("wait_day");
			DialogExit_Self();
		break;
		//  захват города
		case "TalkSelf_TownAttack":
            int needCrew = 500;
			if(CheckOfficersPerk(pchar, "Troopers")) needCrew = 300;
            bOk = (GetPartyCrewQuantity(Pchar, true) >= needCrew) || bBettaTestMode;
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk)
	        {
	            chr = GetCharacter(GetCharIDXForTownAttack(pchar.location));
	            if (chr.from_sea == Pchar.location.from_sea)
	            {
					Dialog.Text = "Wir könnten anfangen, die Stadt einzunehmen, aber das Schiff würde die Salven der Festungskanonen nicht lange aushalten, und wir könnten keine Landungspartei schicken.";
	    			Link.l1 = "...";
	    			Link.l1.go = "exit";
	            }
	            else
	            {
					if (pchar.location == "Panama_ExitTown" || pchar.location == "Tortuga_ExitTown" || pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_ExitTown") // patch-5
					{
						Dialog.Text = "Nein, ich bin noch nicht so verrückt..";
	    				Link.l1 = "...";
	    				Link.l1.go = "exit";
					}
					else
					{
						if (pchar.location == "LosTeques_ExitTown")
						{
							Dialog.Text = "Es hat keinen Sinn, diese Mine anzugreifen, ohne zuerst Informationen über das dort abgebaute Gold und Silber zu sammeln. Andernfalls schicke ich meine Männer umsonst in den Tod.";
							Link.l1 = "...";
							Link.l1.go = "exit";
						}
						else
						{
							Dialog.Text = "Angriff "+GetCityName(chr.City)+".";
							if (CheckAttribute(pchar, "questTemp.Patria.SanJoseAttack") && pchar.location == "PortSpein_ExitTown") // Jason НСО
							{
								Link.l1 = "Hör auf herumzualbern! Halt!";
								Link.l1.go = "exit";
								break;
							}
							if (CheckAttribute(pchar, "questTemp.Patria")) // Jason НСО
							{
								if (pchar.questTemp.Patria != "fail" || pchar.questTemp.Patria != "complete")
								{
									if (pchar.location == "Marigo_ExitTown" || pchar.location == "Villemstad_ExitTown")
									{
										Link.l1 = "Hör auf herumzualbern! Halt!";
										Link.l1.go = "exit";
										break;
									}
								}
							}
							Link.l1 = "Zu den Waffen!";
							Link.l1.go = "TalkSelf_TownAttack_Start";
		    			Link.l2 = "Halt!";
							Link.l2.go = "exit";
						}
	    		}
	        }
	        }
	        else
	        {
				if(!CheckAttribute(Pchar, "GenQuestFort.StartAttack"))
				{
					Dialog.Text = "Heh! Es gibt nicht genug Leute in der Crew; Wir brauchen mindestens "+needCrew+" Männer.";
					Link.l1 = "...";
					Link.l1.go = "exit";
				}
				else
				{
					Dialog.Text = "Zerstreut euch nicht! Macht mit dem Angriff weiter!";
					Link.l2 = "..., Freund.";
					Link.l2.go = "exit";				
				}			
			}
	    break;

		case "TalkSelf_TownAttack_Start":
	        NextDiag.CurrentNode = NextDiag.TempNode;

			Pchar.GenQuestFort.StartAttack = true;
		    Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
		    DeleteQuestAttribute("Union_with_Escadra");
	        chr = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
			if (isCityHasFort(chr.City))
			{
	        	SetLocationCapturedState(chr.from_sea, true);
	        }
	        else
	        {
	            SetLocationCapturedState(chr.Default, true); // для сухопутных
	        }
	        AddDialogExitQuest("Capture_Forts");
	        Ship_NationAgressive(chr, chr);
	        DialogExit_Self();
	    break;
	    // Зачислить рабов в команду  -->
		case "TalkSelf_SlavesToCrew":
	        if (GetCurCrewEscadr() >= GetMaxCrewAble())
	        {
	            Dialog.Text = "Keiner der Sklaven ist bereit, sich der Besatzung anzuschließen.";
	            Link.l1 = "Zur Hölle mit ihnen!";
	    		Link.l1.go = "exit";
	        }
	        else
	        {
	            if (GetCrewQuantity(pchar) >= GetMaxCrewQuantity(pchar))
	            {
	                Dialog.Text = "Es gibt keinen freien Platz auf dem Schiff für neue Matrosen.";
	                Link.l1 = "Heh! Ich muss einen Teil der Mannschaft auf ein anderes Schiff verlegen.";
	        		Link.l1.go = "exit";
	            }
	            else
	            {
	                if (GetFreeCrewQuantity(pchar) <= GetCargoGoods(pchar, GOOD_SLAVES))
	                {
	                    pchar.GenQuest.SlavesToCrew = GetFreeCrewQuantity(pchar);
	                }
	                else
	                {
	                    pchar.GenQuest.SlavesToCrew = GetCargoGoods(pchar, GOOD_SLAVES);
	                }
	                Dialog.Text = "Deine Crew kann aufgefüllt werden mit "+pchar.GenQuest.SlavesToCrew+" Sklaven, die unter Ihnen dienen wollen. Möchten Sie akzeptieren?";
	                Link.l1 = "Ja";
	        		Link.l1.go = "TalkSelf_SlavesToCrew_1";
	        		Link.l2 = "Nein";
	        		Link.l2.go = "exit";
	    		}
			}
		break;

		case "TalkSelf_SlavesToCrew_1":
			// belamour legendary edition перк получил время работы, старый метод не подходит
	        if (GetOfficersPerkUsing(pchar, "IronWill"))
	        {
	            AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 5.0))
	        }
	        else
	        {
	            AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 3.0))
	        }
			ChangeCharacterComplexReputation(pchar,"authority", -0.5);
	        // падение опыта -->
	        fTemp =  stf(GetCrewQuantity(pchar) + sti(pchar.GenQuest.SlavesToCrew));
	        pchar.Ship.Crew.Exp.Sailors   = (stf(pchar.Ship.Crew.Exp.Sailors)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Sailors)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Cannoners   = (stf(pchar.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Cannoners)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Soldiers   = (stf(pchar.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Soldiers)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			// падение опыта <-- 
			pchar.Ship.Crew.Quantity = sti(pchar.Ship.Crew.Quantity) + sti(pchar.GenQuest.SlavesToCrew); 
	        RemoveCharacterGoodsSelf(pchar, GOOD_SLAVES, sti(pchar.GenQuest.SlavesToCrew));       
			                            
	        NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		// Зачислить рабов в команду  <--
		// boal <--

//navy CONTRABAND METRO -->
		case "GenTravel_Main":
			NextDiag.TempNode = "First time";
			dialog.Text = "Dieses süße Schiff gehört jetzt mir, und ich bin der Kapitän hier! Es ist schade allerdings, dass ich die gesamte Besatzung töten musste.";
			Link.l1 = "Es ist Zeit, an Land zu kommen...";
			Link.l1.go = "exit";

			chr = CharacterFromID("Abracham_Gray");
			chr.location = "none";
			SeaExchangeCharactersShips(PChar, chr, false, false);
			SetCrewQuantity(PChar, 0);

			//грузим ГГ куда нужно...
			SetAnyReloadToLocation(pchar.GenQuest.contraTravel.destination.loc, pchar.GenQuest.contraTravel.destination.group, pchar.GenQuest.contraTravel.destination.locator, "", 0, 0, 0, 0);
			AddDialogExitQuest("AnyReloadToLocation");
            chrDisableReloadToLocation = false;
            
			CloseQuestHeader("Gen_ContrabandTravel");
			setCharacterShipLocation(PChar, pchar.GenQuest.contraTravel.destination.loc);
			setWDMPointXZ(pchar.GenQuest.contraTravel.destination.loc);

			//трем аттрибуты
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			break;
//navy CONTRABAND METRO <--

//navy --> 13.02.08
		case "Cabin_CompanionSelect":
			Dialog.Text = "Welcher Begleiter soll hergeholt werden?";
			for (i = 1; i < GetCompanionQuantity(PChar); i++)
			{
				chr = GetCharacter(GetCompanionIndex(PChar, i));
				if (!CheckAttribute(chr, "Tasks.Clone") && sti(chr.Payment) == true)
				{
					sAttr = "l" + i;
					rShip = GetRealShip(sti(chr.Ship.Type));
					link.(sAttr) = GetFullName(chr) + " - " + xiStr(rShip.BaseName) + " '" + chr.Ship.Name + "'.";
					link.(sAttr).go = "CabinCompanionTalk_" + i;
				}
			}
			link.l9 = "Ein andermal.";
			link.l9.go = "exit";
			break;

		case "Cabin_Companion_Talk":
			i = sti(PChar.GenQuest.CabinCompanionNum);
			PlaceCompanionCloneNearMChr(i, false);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			break;
//navy <--

		//--> Голландский гамбит
		case "Seek_AbyIsland":
			bOk = CheckCharacterItem(pchar, "bussol") && CheckCharacterItem(pchar, "clock2");
			bool bOk1 = CheckCharacterItem(pchar, "sextant2");
			if (bOk || bOk1)
			{
				DialogExit();
				DeleteAttribute(pchar, "questTemp.HWIC_Coordinates");
				pchar.questTemp.HWIC_FindIsland = "true";
				AddDialogExitQuestFunction("PrepareSearchingFor");
			}
			else
			{
				dialog.text = "Schade, dass ich nicht die notwendigen Navigationsinstrumente habe, um die Breite und Länge zu bestimmen. Ich muss zu einem anderen Zeitpunkt nach der Insel suchen. ";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		//<-- Голландский гамбит
		
		//--> Ложный след
		case "FalseTrace_Cabin":
			dialog.text = "Bosun! Bring Adam Rayner sofort zu mir!";
			link.l1 = "Aye aye, Kapitän!";
			link.l1.go = "exit";
			chr = characterFromId("Mugger");
			if (pchar.questTemp.FalseTrace == "CatchAdam") chr.dialog.currentnode = "FalseTrace_17";
			else chr.dialog.currentnode = "FalseTrace_7";
			pchar.questTemp.FalseTrace.CharID = "Mugger";
			AddDialogExitQuest("SetFalseTraceCharToCabin");
		break;
		
		case "FalseTrace_Woman":
			DialogExit();
			chr = characterFromId("FalseTraceWife");
			chr.dialog.currentnode = "FalseTrace_wife_6";
			pchar.questTemp.FalseTrace.CharID = "FalseTraceWife";
			AddDialogExitQuest("SetFalseTraceCharToCabin");
		break;
		//<-- Ложный след
		
		//--> LSC, приколы со стуком в дверь
		case "knock_2":
			PlaySound("interface\knock_2.wav");
			dialog.text = "Also, ich habe geklopft, jetzt warte ich auf die Antwort...";
			link.l1 = "(warte)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_3":
			PlaySound("interface\knock.wav");
			dialog.text = "Also, ich habe geklopft, jetzt warte ich auf die Antwort...";
			link.l1 = "(warte)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_3_1":
			PlaySound("interface\knock_3_1.wav");
			dialog.text = "Also, ich habe geklopft, jetzt warte ich auf die Antwort...";
			link.l1 = "(warte)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_1_3":
			PlaySound("interface\knock_1_3.wav");
			dialog.text = "Also, ich habe geklopft, jetzt warte ich auf die Antwort...";
			link.l1 = "(warte)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_2_2":
			PlaySound("interface\knock_2_2.wav");
			dialog.text = "Also, ich habe geklopft, jetzt warte ich auf die Antwort...";
			link.l1 = "(warte)";
			link.l1.go = "knock_right";
		break;
		
		case "knock_wrong":
			dialog.text = "Er öffnet die Tür nicht... Ich vermute, ich habe den falschen Geheimknock verwendet. Gut, ich komme morgen wieder und probiere es erneut. Heute wird er die Tür sicher nicht öffnen.";
			link.l1 = "(gehen)";
			link.l1.go = "exit";
		break;
		
		case "knock_right":
			PlaySound("interface\key.wav");
			PlaySound("Voice\English\YouFace.wav");
			dialog.text = "Wow! Er hat geantwortet und die Tür geöffnet! Ich kann jetzt eintreten...";
			link.l1 = "(betreten)";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.DiffIndoor");
			LocatorReloadEnterDisable("LostShipsCity_town", "reload74", false);
		break;
		//<-- LSC, приколы со стуком в дверь
		
		// суп из черепахи
		case "terrapin":
			PlaySound("Interface\Door_Kick.wav");
			PlaySound("Voice\English\EvilPirates02.wav");
			dialog.text = "Verdammt! Also das ist die verspätete Verstärkung für Levasseur... Keine Chance, dass ich durch die Tür gehen kann... Gut, ich folge Thibauts Spuren - durch das Fenster! Immerhin hat dieser Schurke es irgendwie geschafft zu entkommen!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Terrapin_GoWindow");
		break;
		
		// защита Сен-Пьера
		case "SP_defend":
			PlaySound("Voice\English\military02.wav");
			dialog.text = "Also, unsere Mission besteht darin, einen Angriff der verfluchten Spanier abzuwehren und Saint Pierre zu retten. Das Fort ist erobert und auf den Straßen wird gekämpft. Es gibt eine mächtige Eskadron in der Bucht von Saint Pierre und sie haben ein Linienschiff als Flaggschiff. Ein Angriff jetzt wäre sinnlos, das Fort und die Stadt sind unter feindlicher Kontrolle, sie werden uns also nicht im Hafen landen lassen\nDaher habe ich beschlossen, durch den Dschungel zu gehen und sie von hinten durch die Stadttore zu schlagen. Sobald das Fort und die Stadt von den Spaniern befreit sind, werden wir uns um die Eskadron kümmern. Ohne die Feuerunterstützung des Forts wird sie viel anfälliger\nDas wird nicht einfach sein, deshalb habe ich den Befehl gegeben, zusätzliche hunderttausend Pesos zu zahlen, die zusätzlich zum normalen Gehalt unter der Besatzung verteilt werden sollen. Auf geht's!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("DefendSP_GoJungle");
		break;
		
		// финал игры
		case "final_1": // Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor")) // генерал-губернатор никуда не уедет
			{
				dialog.text = "Halt, wohin gehe ich? Ich kann die Position des Generalgouverneurs nicht ohne Erlaubnis aus Paris verlassen! Sonst werde ich bei meiner Rückkehr nach Frankreich definitiv wegen der unbefugten Verlassung der anvertrauten Kolonien festgenommen. Paris, ich werde dich vermissen ...";
				link.l1 = "";
				link.l1.go = "exit";
				EndQuestMovie();
			}
			else
			{
				dialog.text = "Dann verschwenden wir keine Zeit mehr! Ich vermisse die Felder meiner lieben Gascogne so sehr! Setzt die Segel!";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("Final_ReturnToEurope");
			}
		break;
		
		case "final_2":
			dialog.text = "Ich glaube, das ist die richtige Entscheidung! Was bleibt mir in gutem alten Europa, wenn ich mich hier gefunden habe? Außerdem kann ich jederzeit nach Frankreich zurückkehren, wenn ich will!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Final_StayInCarribean"); // 010912
			DeleteAttribute(pchar, "questTemp.Tieyasal_final");
		break;
		
		// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
		case "FMQN_1":
			dialog.text = "Das ist der beste Weg. Ich sollte an Bord gehen und hier raussegeln.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ChooseExit");
		break;
		
		case "FMQN_2":
			dialog.text = "Nein, auf keinen Fall, ich bleibe. Aber zur Hölle, ich werde hier nicht auf Gott weiß was warten. Ich sollte zum Hafen von Philipsburg segeln und die Situation untersuchen. Mir gefällt die Vorstellung nicht, ein Werkzeug in den Händen eines verfluchten lügenden Engländers zu sein.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ChooseContinue");
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx_ammo":
			Mtraxx_PlantCheckShoreBox(); // анализируем содержимое сундука
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.Blade") && !CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.NoBlade")) // собрали 30 сабель
			{
				dialog.text = "Dreißig Stücke kalten Stahls sind in der Truhe! Soll ich jetzt aufhören, oder sollte ich mehr Feuerwaffen, Ladungen und Tränke sammeln?";
				link.l1 = "Das ist genug!";
				link.l1.go = "mtraxx_ammo_1";
				link.l2 = "Nein, ich sollte diese Truhe weiter füllen.";
				link.l2.go = "exit";
				// belamour legendary edition
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Full")
				{
					link.l3 = "Füllt es mit dem Inhalt von Fadeys Kiste und nehmt den Überschuss."; 
					link.l3.go = "mtraxx_ammo_1";
				}
			}
			else
			{
				dialog.text = "Dreißig Stücke kalten Stahls sind noch nicht gesammelt! Ich sollte mehr bringen.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_ammo_1":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(characterFromId("Fadey"));
            dialog.text = "Die Truhe verschließen und einen Plan schmieden, um sie zur Plantage zu schleichen.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantShoreBoxComplete");
		break;
		
		case "mtraxx_mutiny":
            dialog.text = "Los, Angriff! Huurah!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantMutiny");
		break;
		
		case "mtraxx_boats":
            if (GetSquadronGoods(pchar, GOOD_PLANKS) >= 20 && GetSquadronGoods(pchar, GOOD_LEATHER) >= 10) // наличие материалов
			{
				if (Mtraxx_MeridaCheckCarpenter()) // наличие плотника
				{
					dialog.text = "Alle erforderlichen Materialien sind vorbereitet, wir sollten sofort mit dem Bau der Langboote beginnen.";
					link.l1 = "";
					link.l1.go = "exit";
					AddDialogExitQuestFunction("Mtraxx_MeridaBuildBoats");
				}
				else
				{
					dialog.text = "Ich habe keinen erfahrenen Zimmermann, der die Arbeit erledigen könnte. Ich sollte einen Offizier für diese Position einsetzen.";
					link.l1 = "";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Nicht genug Material, wir benötigen mindestens 20 Ladungen Bretter und 10 Ballen Leder.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_powder":
            if (GetSquadronGoods(pchar, GOOD_POWDER) >= 300) // наличие пороха
			{
				if (GetCrewQuantity(pchar) >= 20) // наличие команды
				{
					dialog.text = "Alles ist bereit für eine Sprengung!";
					link.l1 = "";
					link.l1.go = "exit";
					AddDialogExitQuestFunction("Mtraxx_RetributionBarrels");
				}
				else
				{
					dialog.text = "Ich brauche mindestens 20 Männer, um das Schießpulver zu liefern.";
					link.l1 = "";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Nicht genug Schießpulver, mindestens 300 wird benötigt.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_dungeon":
			PlaySound("ambient\jail\jail_door2.wav");
            dialog.text = "War es eine Tür?";
			link.l1 = "";
			link.l1.go = "mtraxx_dungeon_1";
		break;
		
		case "mtraxx_dungeon_1":
			PlaySound("ambient\jail\jail_door1.wav");
            dialog.text = "Richtig! Wir haben Besucher... Jan?..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionRunToEnrico");
		break;
		// belamour legendary edition -->
		case "Good_Choice":
			pchar.questTemp.Mtraxx.Retribution.Choice = "good";
			DoQuestCheckDelay("Mtraxx_RetributionFreedom", 0.5); 
			DialogExit_Self();
		break;
		
		case "Bad_Choice":
			pchar.questTemp.Mtraxx.Retribution.Choice = "bad";
			Achievment_Set("ach_CL_97");
			bNoEatNoRats = false;
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Roger_10", "18");
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			pchar.quest.mtraxx_line_complete.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_line_complete.function = "Mtraxx_RetributionComplete";
			DialogExit_Self();
		break;
		// <-- legendary edition
		
		// Jason Долго и счастливо
		case "LH_marry":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			string sTemp = sld.name;
			dialog.text = "Ich und "+sTemp+" sind schon lange zusammen und unser Bund ist stärker als jedes Kirchengebot, aber ich möchte, dass wir beide uns an diesen Moment erinnern. Daher muss ich entscheiden, wo ich ihr den Antrag machen soll:";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "Isla Tessoro - diese Insel bedeutet viel in unserer Geschichte. Ich vermute, es gibt keinen besseren Ort - Sabu Matila Bucht ist bezaubernd bei Sonnenuntergang!";
				link.l1.go = "LH_marry_1_1";
			}
			link.l2 = "Tortuga - ein Symbol der Freiheit unserer Zeit, und der Blick vom Leuchtturm auf die Tortu-Meerenge ist einer jeden Malerhand würdig!";
			link.l2.go = "LH_marry_1_2";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l3 = "Jamaika - da steckt so viel drin! Und den Sonnenaufgang in der Portland Bucht zu bewundern, stelle ich mir als das Paradies auf Erden vor.";
				link.l3.go = "LH_marry_1_3";
			}
		break;
		
		case "LH_marry_1_1":
			pchar.questTemp.LongHappy.Shore = "Shore_ship1";
			AddQuestRecord("LongHappy", "2_1");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "Aber wir können dies nicht ohne die Feierlichkeit der Kirche tun - alles sollte nach allen Kanonien sein, damit mein Vater gezwungen wäre, meine Wahl zu akzeptieren. Also, ich werde einen Priester brauchen, und ich sehe niemanden, der dieser Position würdig ist, außer Abt Benoit. Er ist ein alter Freund meines Vaters und mit ihm begannen meine Abenteuer in der Neuen Welt. Ich denke, er wird einverstanden sein, mir die Ehre zu erweisen.";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_1_2":
			pchar.questTemp.LongHappy.Shore = "Mayak6";
			AddQuestRecord("LongHappy", "2_2");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "Aber wir können das nicht ohne die Feierlichkeit der Kirche tun - alles sollte nach allen Kanonen sein, damit mein Vater gezwungen wäre, meine Wahl zu akzeptieren. Also, ich werde einen Priester brauchen, und ich sehe niemanden, der dieser Position würdig ist, außer Abt Benoit. Er ist ein alter Freund meines Vaters und mit ihm begannen meine Abenteuer in der Neuen Welt. Ich glaube, er wird einverstanden sein, mir die Ehre zu erweisen.";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_1_3":
			pchar.questTemp.LongHappy.Shore = "Shore36";
			AddQuestRecord("LongHappy", "2_3");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "Aber wir können dies nicht ohne die Feierlichkeit der Kirche tun - alles sollte nach allen Kanonen sein, damit mein Vater gezwungen wäre, meine Wahl zu akzeptieren. Also, ich werde einen Priester brauchen, und ich sehe niemanden, der dieser Position würdig ist, außer Abt Benoit. Er ist ein alter Freund meines Vaters und von ihm begannen meine Abenteuer in der Neuen Welt. Ich denke, er wird zustimmen, mir die Ehre zu erweisen.";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_2":
			AddQuestRecord("LongHappy", "3");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "Nun, das kann auch ohne die Feierlichkeit der Menschheit geschehen. Obwohl ich dies lieber diskutieren würde mit "+sTemp+" ein wenig später.";
			link.l1 = "";
			link.l1.go = "exit";
			pchar.questTemp.LongHappy = "choose";
		break;
		
		case "LH_marry_3":
			dialog.text = "Nun, ich bin bereit!";
			link.l1 = "";
			link.l1.go = "exit";
			LongHappy_MarryOffer();
		break;
		
		case "LH_marry_4":
			if (LongHappy_CheckGoods())
			{
				dialog.text = "Alles ist vorbereitet!";
				link.l1 = "";
				link.l1.go = "exit";
				LongHappy_OnIslaTesoro();
			}
			else
			{
				dialog.text = "Die notwendigen Waren und Münzen sind noch nicht gesammelt worden!";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
	}
}

void  DialogExit_Self()
{
    DialogExit();
	locCameraSleep(false); //boal
}
