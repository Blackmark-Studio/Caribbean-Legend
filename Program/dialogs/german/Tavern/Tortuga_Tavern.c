// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Alle Gerüchte von "+GetCityName(npchar.city)+" zu Ihren Diensten. Was möchten Sie erfahren?","Wir haben gerade darüber gesprochen. Du musst es vergessen haben...","Das ist das dritte Mal heute, dass du von irgendeiner Frage sprichst...","Du wiederholst alles wie ein Papagei...","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Du weißt, "+NPChar.name+", vielleicht nächstes Mal.","Stimmt, ich habe aus irgendeinem Grund vergessen...","Ja, es ist wirklich das dritte Mal...","Jawohl...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatTortuga") // работорговец
            {
                link.l1 = "Hör zu, wo kann ich Francois Gontier finden? Er sollte bereits in Tortuga angekommen sein.";
                link.l1.go = "Tortuga_ratT_1";
            }
			// суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga" && !CheckAttribute(pchar, "questTemp.Tonzag.TerrapinBlock"))
			{
				link.l1 = "Ich suche nach Henri Thibaut. Wo kann ich ihn finden?";
				link.l1.go = "terrapin";
			}
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga1" && !CheckAttribute(pchar, "questTemp.Tonzag.TerrapinBlock"))
			{
				link.l1 = "Ich suche nach Henri Thibaut. Wo kann ich ihn finden?";
				link.l1.go = "terrapin_2";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga")
			{
				link.l1 = "Sag mal, hat ein Galeon namens 'Santa Margarita' kürzlich in deiner Kolonie Halt gemacht? Vielleicht als Prise eines Freibeuters?";
                link.l1.go = "guardoftruth";
			}
			// Addon 2016-1 Jason Пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Jeweller"))
			{
				link.l1 = "Schau mal, Kumpel, ich suche Gaspard Parmentier. Wo kann ich ihn finden?";
                link.l1.go = "mtraxx_jew";
			}
			// Rebbebion, "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && !CheckAttribute(npchar, "quest.PZ.Ask.Block"))
			{
				link.l1 = "Könntest du mir ein wenig helfen, Kumpel? Ich suche einen Mann namens Joep van der Vink. Kennst du ihn?";
				link.l1.go = "PZ_1";
			}
        break;
        
		case "Tortuga_ratT_1":
			dialog.text = "Francois Gontier? Wer ist das? Ich kenne keinen Mann mit diesem Namen.";
			link.l1 = "Er ist der Kapitän der Korvette '"+pchar.questTemp.Slavetrader.ShipName+"'.";
			link.l1.go = "Tortuga_ratT_2";
        break;
		
		case "Tortuga_ratT_2":
			dialog.text = "Ich habe nicht den leisesten Schimmer, Kamerad. Und ich kann sicher sagen, dass keine Korvette mit diesem Namen in unserem Hafen angelegt hat.";
			link.l1 = "Gut dann, haben Sie in letzter Zeit irgendwelche Fremden in der Stadt gesehen?";
			link.l1.go = "Tortuga_ratT_3";
        break;
		
		case "Tortuga_ratT_3":
			dialog.text = "Gute Frage! Dies ist eine Hafenstadt, kein Dorf. Fremde kommen jeden Tag durch. Obwohl ich von fünf eigenartigen Burschen gehört habe, bleiben sie immer eng beisammen und haben ihre Klingen bereit\nDie Patrouille hat sogar ohne Ergebnis nach ihnen gefragt. Aber ich bin sicher, dass sie nicht auf einer Korvette hierher gekommen sind, kein solches Schiff wurde hier gesehen, kapiert?";
			link.l1 = "Hm... Also gut, ich verstehe. Danke, "+npchar.name+".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_8");
			pchar.questTemp.Slavetrader = "wait1";//затычка
        break;
		
		// суп из черепахи
		case "terrapin":
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Herr Thibaut ist ein berühmter Mann auf Tortuga. Sein Herrenhaus liegt in der Nähe der Hafenbehörde. Wenn Sie die Taverne verlassen, gehen Sie direkt zum Hafen. Nähern Sie sich dem Bogen, der zum Hafen führt, biegen Sie an der Kreuzung links ab und gehen Sie bis zum Ende der Straße, wo Sie auf ein zweistöckiges Steinhaus mit rotem Dach stoßen. Das ist das Herrenhaus von Monsieur Thibaut.";
			link.l1 = "Danke! Ich werde ihn besuchen gehen...";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			DialogExit();
			pchar.questTemp.Terrapin = "house";
			sld = characterFromId("Tibo");
			ChangeCharacterAddressGroup(sld, "Tortuga_houseS2", "barmen", "stay");
			LAi_SetOwnerType(sld);
		break;
		
		case "terrapin_2":
			dialog.text = "Herr Thibaut ist heute sehr gefragt, ein Bote vom Gouverneur ist gerade hierher gerannt. Er war auch interessiert. Ist es so schwer, ihn zu finden? Er mietet schon seit geraumer Zeit ein Zimmer bei mir im zweiten Stock, obwohl er ein ganzes Herrenhaus zum Wohnen hat. Ich weiß nicht, wofür er es braucht, aber er kommt viel öfter rein, als er rausgeht. Und er ist nur abends da.";
			link.l1 = "Vielleicht ist er gerade jetzt hier.";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			if (stf(environment.time) < 20.0 && stf(environment.time) > 8.0)
			{
				dialog.text = "Nein. Er sagte, er wäre erst um acht Uhr abends heute zurück. Sie könnten versuchen, ihn zu Hause in seiner Villa zu suchen, aber ich glaube nicht, dass Sie ihn dort finden werden. Ich sah ihn auf einer Patrouillen-Lugger auf See segeln.";
				link.l1 = "Danke! Ich werde später vorbeischauen, um ihn zu sehen.";
				link.l1.go = "terrapin_4";
			}
			else
			{
				dialog.text = "Ja. Wenn du willst, kannst du hochkommen.";
				link.l1 = "Danke! Ich werde ihn besuchen gehen...";
				link.l1.go = "terrapin_4";
			}
		break;
		
		case "terrapin_4":
			DialogExit();
			pchar.questTemp.Terrapin = "tavern";
			sld = characterFromId("Tibo");
			sld.dialog.currentnode = "tibo_9";
			LAi_SetLoginTime(sld, 20.0, 8.0);
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern_upstairs", "goto", "goto1");
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", false); // откроем комнату
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], true);//запретить драться
			LAi_SetStayType(sld);
			// Addon 2016-1 Jason Пиратская линейка
			if (GetCharacterIndex("Mary") != -1)
			{
				sld = characterFromId("Mary");
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && !IsOfficer(sld))
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
			if (GetCharacterIndex("Helena") != -1)
			{
				sld = characterFromId("Helena");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && !IsOfficer(sld))
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Keine Ahnung vom Schiffsnamen, war es 'Santa Margarita' oder 'Kastilische Hure', aber sie brachten hier eine gefangene spanische Galeone. Erobert von einer Schaluppe, nichts weniger! Das ist ein verdammt gutes Segeln! Gaius Marchais, ihr Kapitän, hat zwei Tage lang in einer Taverne geprahlt - seine erste Reise und so ein Preis!\n Aye, sehr heroische Tat, eine Galeone voll mit Kirchenratten ohne Soldaten zu entern. Es scheint, dass diese päpstlichen Bastarde vergessen haben, was sie über die sagen, die sich selbst helfen...";
			link.l1 = "Ja, Gott hilft dem, der sich selbst hilft, das ist sicher ein Hugenotten-Spruch. Wie bekomme ich einen Blick auf diesen glücklichen Kapitän? Ist er hier, auf Tortuga?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Ach, wer zum Teufel weiß das schon. Ich habe ihn schon lange nicht mehr in meiner Taverne gesehen. Sobald er nüchtern wurde, kaufte er mit dem Preisgeld ein glänzendes neues Schiff und rannte wie ein Wahnsinniger über das Deck. Ich habe keine Ahnung, wo Marchais jetzt ist. Vielleicht ist er auf Tortuga oder vielleicht auf See.";
			link.l1 = "Also gut. Danke für die Geschichte, Kumpel!";
			link.l1.go = "guardoftruth_2";			
		break;
		
		case "guardoftruth_2":
			dialog.text = "Jederzeit, Monsieur. Ich helfe unserem geliebten Kapitän immer gerne "+pchar.name+", Retter von St. Pierre! Kommen Sie später vorbei!";
			link.l1 = "...";
			link.l1.go = "exit";	
			AddQuestRecord("Guardoftruth", "8");
			pchar.questTemp.Guardoftruth = "tortuga1";
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx_jew":
            dialog.text = "Scheint, als würde Gaspard bei Eurer Art immer beliebter. Sein Haus liegt an der Mauer. Geh links von der Taverne und geh zum Hafen, aber geh nicht dorthin, biege wieder links ab, geh geradeaus und dann rechts. Ein zweistöckiges Haus.";
			link.l1 = "Danke!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekJewellerHouse");
		break;
		
		case "PZ_1":
			dialog.text = "Noch nie von ihm gehört.";
			link.l1 = "Vielleicht ist er unter einem anderen Namen bekannt. Haben Sie vielleicht von ihm als dem Kapitän der Brigg 'Banten' gehört?";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_2":
			dialog.text = "Noch nie von dieser Brigg gehört.";
			link.l1 = "Ich habe gehört, er war kürzlich hier. Vielleicht wird ein wenig Silber Ihre Erinnerung auffrischen?";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			npchar.quest.PZ.Ask.Block = true;
			
			dialog.text = "Nun, frag, wo du das gehört hast. Ich habe nichts dagegen, dein Silber zu nehmen.";
			link.l1 = "Kein Silber dieses Mal, also. Auf Wiedersehen.";
			link.l1.go = "Exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
