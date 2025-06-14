void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Was willst du?";
			link.l1 = "Im Moment nichts.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//Найти помощника в магазин
		case "Storehelper":
			DelLandQuestMark(npchar);
			dialog.text = "Gibt es etwas, was Sie brauchen, Monsieur?";
			link.l1 = "Sie sind Gralam Lavoie, korrekt?";
			link.l1.go = "Storehelper_1";
		break;
		
		case "Storehelper_1":
			dialog.text = "Wer fragt? Stören Sie mich nicht, während ich Rum trinke, Herr. Ich bin nicht in der Stimmung zu plaudern.";
			link.l1 = "Ich werde nicht viel Ihrer Zeit in Anspruch nehmen. Ich wurde von einem Kaufmann aus Saint-Pierre hierher geschickt. Sie waren sein ehemaliger Angestellter. Er sucht Sie und...";
			link.l1.go = "Storehelper_2";
		break;
		
		case "Storehelper_2":
			dialog.text = "Ha, er sucht nach mir!? Das ist reich von diesem verfluchten Geizkragen! Hat er wirklich gedacht, dass ich mein ganzes Leben für solch lächerliche Löhne arbeiten würde? Er ist der geizigste Pfennigfuchser in der Karibik! Ich habe fünf Jahre für ihn geschuftet und er hat mir keinen Pfennig mehr bezahlt, als er konnte! Bah, nicht einmal genug, um ein Getränk zu kaufen!\nEr kann nun seine eigenen Waren zählen, ich kündige. Niemand in Saint-Pierre wird für diesen Geizkragen arbeiten, das ist sicher. Er hat nur eine Sorge - mehr für sich selbst zu verdienen und seinen Leuten weniger zu bezahlen.";
			link.l1 = "Ich nehme an, du wirst nicht mehr für ihn arbeiten?";
			link.l1.go = "Storehelper_3";
		break;
		
		case "Storehelper_3":
			dialog.text = "Nein, Gott soll mich totschlagen, wenn ich das getan habe! Ich werde einfach hier in Le Francois warten, bis ein Schiff ankommt und ich werde mich als Zahlmeister anmelden, wenn sie mich nehmen. Und wenn das nicht klappt, dann werde ich es als gewöhnlicher Matrose versuchen. Ich kann es nicht einmal ertragen, diesen Geldgierigen anzusehen. Wenn ich schon arm sein soll, dann lieber als freier Mann...";
			link.l1 = "Ich verstehe, das ist alles, was ich wissen musste. Viel Glück, Gralam!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_4":
			DelLandQuestMark(npchar);
			dialog.text = "Herr, treten Sie zur Seite. Sie stehen mir im Weg!";
			link.l1 = "Nur eine Frage, Monsieur. Sind Sie Gralam Lavoie?";
			link.l1.go = "Storehelper_5";
		break;
		
		case "Storehelper_5":
			dialog.text = "Ha! Ja, das bin ich. Was willst du?";
			link.l1 = "Ein Kaufmann aus St. Pierre sucht dich. Du hast früher für ihn gearbeitet, oder?";
			link.l1.go = "Storehelper_6";
		break;
		
		case "Storehelper_6":
			dialog.text = "Ha-ha! Was für ein Witz! Und was benötigt seine königliche Majestät von mir? Hat er sich entschieden, mir mein fehlendes Gehalt für meine letzten zwei Arbeitswochen zu zahlen? Oder hat er Probleme, seine Fässer zu zählen und gleichzeitig seine Kunden zu täuschen, eh? Ha-ha-ha!";
			link.l1 = "Er hat mich gebeten, nach dir zu suchen und zu klären, warum du nicht mehr in seinem Laden arbeiten kommst.";
			link.l1.go = "Storehelper_7";
		break;
		
		case "Storehelper_7":
			dialog.text = "Warum? Weil er ein verdammter Geizhals und ein schrecklicher Arbeitgeber ist! Ich bin jetzt ein Teil der Bruderschaft der Küste, ein freier Mann und kein Sklave mehr! Sieh dich um, ich genieße mich wirklich!\nBald werde ich in See stechen und Pesos und Dublonen zählen, die den Spaniern abgenommen wurden, anstatt Bananenkisten! Und über diesen Geizkragen - ich bezweifle, dass er jemanden finden wird, der mich ersetzt. Niemand in Saint-Pierre ist dumm genug, für ihn zu arbeiten, wir haben seine Reputation allen Lehrlingen auf der Insel bekannt gemacht, ha-ha!";
			link.l1 = "Ich verstehe. Das ist alles, was ich wissen musste. Viel Glück, Gralam!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_8":
			DelLandQuestMark(npchar);
			dialog.text = "Wie kann ich Ihnen helfen?";
			link.l1 = "Guten Tag. Sie sind wohl Gralam Lavoie, nehme ich an?";
			link.l1.go = "Storehelper_9";
		break;
		
		case "Storehelper_9":
			dialog.text = "Ja. Was möchten Sie, Monsieur?";
			link.l1 = "Ein Händler aus Saint-Pierre sucht nach dir. Du hast früher für ihn gearbeitet, oder?";
			link.l1.go = "Storehelper_10";
		break;
		
		case "Storehelper_10":
			dialog.text = "Nun, er soll weiter suchen. Ich schulde ihm nichts. Er schuldet mir noch zwei Wochen Lohn, aber ich werde nicht einmal versuchen, mein Geld von ihm zu bekommen. Ich hoffe, er würgt an seinen eigenen Kupfern.";
			link.l1 = "Hm. Also hast du ihn für immer verlassen, nehme ich an?";
			link.l1.go = "Storehelper_11";
		break;
		
		case "Storehelper_11":
			dialog.text = "Sie haben alles richtig verstanden, Herr. Mein Ex-Arbeitgeber ist ein seltenes Exemplar eines Geizhalses, wahrhaft biblischen Ausmaßes. Ich bin jetzt ein Bruder der Küste und meine Talente werden von meinen neuen Kameraden hoch geschätzt. Ich bekomme das Doppelte, plus Boni\nIch bezweifle, dass unser lieber Freund jemanden finden wird, der mich ersetzt. Seine Gier ist den Leuten von Saint-Pierre gut bekannt, niemand dort ist dumm genug, für ihn zu arbeiten.";
			link.l1 = "Ich habe es verstanden. Das ist alles, was ich wissen musste. Viel Glück, Gralam!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_12":
			DialogExit();
			npchar.lifeday = 0;
			AddQuestRecord("SharlieA", "2");
			pchar.questTemp.Sharlie.Storehelper = "return";
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.StorehelperOver.over = "yes"; //снять таймер
			
			pchar.quest.Sharlie_JungleBandos.win_condition.l1 = "location";
			pchar.quest.Sharlie_JungleBandos.win_condition.l1.location = "Martinique_Jungle_01";
			pchar.quest.Sharlie_JungleBandos.function = "SharlieJungleBandos";
			
			QuestPointerToLoc("lefransua_town", "reload", "gate_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload6_back");
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			QuestPointerDelLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload3_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload1_back");
		break;
		
		case "Newstorehelper_1":
			dialog.text = "Hallo, Monsieur. Ich möchte nicht zu aufdringlich sein, aber ich glaube, dass meine Kandidatur ganz gut zu der Position passt, die Sie anbieten.";
			link.l1 = "Guten Tag. Und warum vermutest du das?";
			link.l1.go = "Newstorehelper_1_1";
		break;
		
		case "Newstorehelper_2":
			dialog.text = "Grüße, mein Herr! Erlauben Sie mir, Ihnen ein wenig über mich selbst zu erzählen.";
			link.l1 = "Ich bin ganz Ohr.";
			link.l1.go = "Newstorehelper_2_1";
		break;
		
		case "Newstorehelper_3":
			dialog.text = "Gute Gesundheit wünsche ich Ihnen, lieber Herr. Bieten Sie eine Kaufmannsstelle an?";
			link.l1 = "Ja, das bin ich. Was können Sie mir über sich selbst erzählen?";
			link.l1.go = "Newstorehelper_3_1";
		break;
		
		case "Newstorehelper_1_1":
			dialog.text = "Ich diente als Quartiermeister unter dem Kommando von Kapitän Francis Dubois selbst. Er war recht zufrieden mit meinen Fähigkeiten, aber ich wurde im Kampf verletzt und musste mich zur Behandlung beurlauben. Ich bin jetzt in Ordnung, völlig gesund, aber der Gedanke an die rollenden Wellen macht mir Übelkeit. Nein, mein einziger Wunsch ist es jetzt, auf festem Boden zu bleiben\n(leise) Und wenn Sie mich auswählen, werde ich fünfhundert Pesos und fünfundzwanzig goldene Dublonen extra zahlen.";
			link.l1 = "Ich verstehe. Ich werde darüber nachdenken.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_1_2";
		break;
		
		case "Newstorehelper_2_1":
			dialog.text = "Ich war früher ein Händler, musste aber vor einigen Schuldnern fliehen und ging als Zahlmeister auf ein Handelsschiff zur See. Das Schicksal hat mich in dieses Dorf gebracht. Das Seemannsleben hat mir sowieso nicht besonders gefallen, und ich würde dein Angebot gerne annehmen\n(Flüstern) Und wenn du mich auswählst, gebe ich dir nicht nur fünfhundert Pesos, sondern auch dieses schwere Paket mit Bernstein.";
			link.l1 = "Ich verstehe. Ich werde darüber nachdenken.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_2_2";
		break;
		
		case "Newstorehelper_3_1":
			dialog.text = "Ich war ein Angestellter in einem der Hafenspeicher von Glasgow. Ich kam in die Karibik auf der Suche nach Reichtum und schaffte es, genug Geld zu verdienen, um mein Alter mit Würde zu leben. Aber ich bin müde von Seereisen und möchte ruhig am Ufer leben\n(flüsternd) Und wenn Sie mich wählen, gebe ich Ihnen fünfhundert Pesos plus zusätzliche zweitausendfünfhundert Pesos als Extra.";
			link.l1 = "Ich verstehe. Ich werde darüber nachdenken.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_3_2";
		break;
		
		case "Newstorehelper_1_2":
			dialog.text = "Herr, treffen Sie die richtige Wahl. Und vergessen Sie die Dublonen nicht...";
			link.l1 = "Ich habe mich zu deinen Gunsten entschieden. Reiß dich zusammen. Wir gehen nach Saint-Pierre.";
			link.l1.go = "Newstorehelper_1_3";
			link.l2 = "Ich habe mich noch nicht entschieden...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_1_2";
		break;
		
		case "Newstorehelper_2_2":
			dialog.text = "Ich hoffe, Sie wählen mich, Monsieur. Und Bernstein ist auch eine sehr wertvolle, nützliche Sache...";
			link.l1 = "Ich habe mich zu Ihren Gunsten entschieden. Reiß dich zusammen. Wir gehen nach Saint-Pierre.";
			link.l1.go = "Newstorehelper_2_3";
			link.l2 = "Ich habe mich immer noch nicht entschieden...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_2_2";
		break;
		
		case "Newstorehelper_3_2":
			dialog.text = "Der Kaufmann wird von meiner Arbeit nicht enttäuscht sein. Und vergiss nicht deinen Bonus.";
			link.l1 = "Ich habe mich zu Ihren Gunsten entschieden. Reiß dich zusammen. Wir gehen nach Saint-Pierre.";
			link.l1.go = "Newstorehelper_3_3";
			link.l2 = "Ich habe mich immer noch nicht entschieden...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_3_2";
		break;
		
		case "Newstorehelper_1_3":
			dialog.text = "Lass mich nur meine Sachen zusammenpacken! Ich warte auf dich am Eingang der Taverne.";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 0;
		break;
		
		case "Newstorehelper_2_3":
			dialog.text = "Ich werde gleich da sein, Monsieur! Ich werde Sie am Eingang der Taverne erwarten.";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 1;
		break;
		
		case "Newstorehelper_3_3":
			dialog.text = "Ich hole meinen alten Koffer und werde am Eingang zur Taverne auf Sie warten, Herr!";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 2;
		break;
		
		case "Newstorehelper_exit":
			DialogExit();
			pchar.questTemp.Sharlie.Storehelper.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay")
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("Newstorehelper_"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
			pchar.quest.storehelper4.win_condition.l1 = "location";
			pchar.quest.storehelper4.win_condition.l1.location = "FortFrance_store";
			pchar.quest.storehelper4.function = "NewstorehelperRegard";
			AddQuestRecord("SharlieA", "4");
			pchar.questTemp.Sharlie.Storehelper = "choise";
			pchar.quest.storehelper.over = "yes"; //снять прерывание
			
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			
			SetLaunchFrameFormParam("Zurück nach Saint-Pierre...", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("FortFrance_store", "reload", "reload1", "");
			LaunchFrameForm();
		break;
		
		case "Newstorehelper_regard":
			dialog.text = "Nun, ich nehme an, dies ist ab jetzt mein Arbeitsplatz? Danke, Monsieur, dass Sie mich ausgewählt haben. Hier sind Ihre fünfhundert Pesos und der versprochene Bonus obendrauf.";
			link.l1 = "Meine Dankbarkeit... Lassen Sie mich Ihnen Ihren Arbeitgeber vorstellen.";
			link.l1.go = "Newstorehelper_regard_1";
		break;
		
		case "Newstorehelper_regard_1":
			DialogExit();
			npchar.lifeday = 0;
			switch (sti(pchar.questTemp.Sharlie.Storehelper.Quality))
			{
				case 0:
					AddMoneyToCharacter(pchar, 500);
					TakeNItems(pchar, "gold_dublon", 25);
				break;
				
				case 1:
					AddMoneyToCharacter(pchar, 500);
					TakeNItems(pchar, "jewelry8", 10);
					TakeNItems(pchar, "jewelry7", 1);
				break;
				
				case 2:
					AddMoneyToCharacter(pchar, 3000);
				break;
			}
		break;
		
		//контрабанда рома
		case "Rum_Cap_Over":
			dialog.text = "Herr, ich muss Sie bitten, mein Schiff sofort zu verlassen. Wir lichten den Anker und legen ab!";
			link.l1 = "In Ordnung...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rum_Cap_Over";
			chrDisableReloadToLocation = false;
			npchar.DontDeskTalk = true;
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
		break;
		
		case "Rum_Cap":
			pchar.quest.Sharlie_rum2.over = "yes"; //снять таймер
			chrDisableReloadToLocation = false; // patch-4
			dialog.text = "Nun? Wer bist du, Kumpel?";
			//link.l1.edit = 1;			
			link.l1 = ""+pchar.questTemp.Sharlie.Rum.Pass+"!";
			link.l1.go = "Rum_Cap_1";
		break;
		
		case "Rum_Cap_1":
			dialog.text = "Hab einen Schluck Rum, Seemann! Ha-ha! Willkommen an Bord meiner Schaluppe. Du bist wegen der Ware gekommen?";
			link.l1 = "Ja. Wofür sollte ich sonst hier sein?";
			link.l1.go = "Rum_Cap_2";
			/* if(GetStrSmallRegister(pchar.questTemp.Sharlie.Rum.Pass) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Habe einen Schluck Rum, Seemann! Ha-ha! Willkommen an Bord meiner Ketsch. Du bist wegen der Ware gekommen?";
				link.l1 = "Ja. Wofür sollte ich sonst hier sein?";
				link.l1.go = "Rum_Cap_2";
			}
			else
			{
				dialog.text = "Meine, meine, was für ein grüner Hurensohn! Jungs, dieser hier sieht aus wie ein frischer Rekrut! Lasst uns ihn über Bord werfen!";
				link.l1 = "Hoppla!";
				link.l1.go = "Rum_Cap_getout";
			} */
		break;
		
		case "Rum_Cap_getout":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			setCharacterShipLocation(pchar, "Shore38"));
			setWDMPointXZ("Shore38");
			DoQuestReloadToLocation("Shore38", "goto", "goto1", "Rum_RemoveBarkas");
		break;
		
		case "Rum_Cap_2":
			dialog.text = "Jungs! Ladet die Kisten auf das Beiboot!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Rum_CarrierEnter");
		break;
		
		case "Rum_Cap_3":
			dialog.text = "Alle Rumkisten sind auf deinem Beiboot. Port Le Francois liegt genau südlich von hier. Mach schnell, es ist auch Zeit für mich, den Anker zu lichten!";
			link.l1 = "Lassen wir keine Zeit verschwenden, meine Herren! Viel Glück!";
			link.l1.go = "Rum_Cap_4";
		break;
		
		case "Rum_Cap_4":
			dialog.text = "Gleichfalls, Kumpel...";
			link.l1 = "...";
			link.l1.go = "Rum_Cap_5";
		break;
		
		case "Rum_Cap_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			npchar.DontDeskTalk = true;
			NextDiag.CurrentNode = "Rum_Cap_Over";
			pchar.quest.Sharlie_rum4.win_condition.l1 = "Ship_location";
			pchar.quest.Sharlie_rum4.win_condition.l1.location = "LeFransua_town";
			pchar.quest.Sharlie_rum4.function = "Rum_RemoveRum";
			AddQuestRecord("SharlieB", "4");
			i = FindIsland("Martinique");
			Islands[i].EffectRadius = 3000;
			
			DoQuestFunctionDelay("MessageRum1", 1.0);
			//NewGameTip("Transport the rum to Le Francois. Keep sailing around the island.");
			pchar.questTemp.Rum.Tip2.Reload = "l4";
			
			Weather.Wind.Speed = 16.0;
			pchar.wind.speed = Weather.Wind.Speed;
			fWeatherSpeed = stf(Weather.Wind.Speed);//халява первого выхода
			
			Weather.Wind.Angle = PId2;
			pchar.wind.angle = Weather.Wind.Angle;
			fWeatherAngle = stf(Weather.Wind.Angle);//халява первого выхода
			
			pchar.quest.MessageRum2.win_condition.l1 = "ExitFromLocation";
			pchar.quest.MessageRum2.win_condition.l1.location = pchar.location;
			pchar.quest.MessageRum2.function = "MessageRum2";
		break;
		
		case "Rum_Carrier":
			dialog.text = "Wir haben auf Sie gewartet, Monsieur. Wie ist alles gelaufen? Haben Sie die Kisten?";
			link.l1 = "Alles lief spektakulär. Die Rumkisten sind auf dem Beiboot.";
			link.l1.go = "Rum_Carrier_1";
		break;
		
		case "Rum_Carrier_1":
			dialog.text = "Großartig. Wir kümmern uns von hier aus darum. Du machst dich auf den Weg nach St. Pierre zur Taverne für die Bezahlung. Sei aufmerksam und vorsichtig in den nächtlichen Dschungeln.";
			link.l1 = "Alles Gute, Herren.";
			link.l1.go = "Rum_Carrier_2";
		break;
		
		case "Rum_Carrier_2":
			DialogExit();
			for (i=1; i<=3; i++)
			{
				
				sld = characterFromId("Rum_Carrier2_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			}
			pchar.questTemp.Sharlie.Rum = "regard";
			i = FindLocation("Fortfrance_town");
			setCharacterShipLocation(pchar, GetCityFrom_Sea(locations[i].fastreload));
		    setWDMPointXZ(GetCityFrom_Sea(locations[i].fastreload));
			SetCurrentTime(23, 0);
			Sharlie_removeLocks("");
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("lefransua_town", "reload", "gate_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			if(CheckAttribute(pchar, "questTemp.Sharlie.Gigolo")) QuestPointerToLocTime("fortfrance_town", "reload", "reload9_back", 23.0, 24.0);
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
		break;
		
		//доставить девочку из борделя
		case "GigoloMan":
			DelLandQuestMark(npchar);
			dialog.text = "Guten Nachmittag, Monsieur! Sie sehen nicht aus wie die üblichen Schurken, die sich normalerweise in unserer Kolonie herumtreiben. Nach Ihrer Kleidung zu urteilen, müssen Sie einen weiten Weg zurückgelegt haben... Sind Sie aus Europa angekommen?";
			link.l1 = "Genau, Monsieur. "+GetFullName(pchar)+", zu Ihren Diensten. Was benötigen Sie?";
			link.l1.go = "GigoloMan_1";
		break;
		
		case "GigoloMan_1":
			dialog.text = "Erlauben Sie mir, mich vorzustellen - "+GetFullName(npchar)+". Ich bin vor einigen Jahren aus Frankreich an diesen schrecklichen Ort gekommen. Aber das ist weder hier noch dort. Ich habe eine sehr heikle Angelegenheit für Sie\nBitte verstehen Sie, dass ich Sie nie um einen solchen Gefallen bitten würde, wenn ich nicht sicher wäre, dass Sie ein Gentleman sind.";
			link.l1 = "Bitte, nennen Sie Ihre Anfrage, Monsieur. Wenn es in meinen Fähigkeiten liegt, dann werde ich natürlich versuchen zu helfen.";
			link.l1.go = "GigoloMan_2";
		break;
		
		case "GigoloMan_2":
			dialog.text = "Es freut mich, diese Worte von Ihnen zu hören, Monsieur de Mor. Also folgendes. In diesem Nest gibt es ein Bordell. Vor kurzem kam dort ein neues Mädchen an, vermutlich aus Europa, jung, weißhäutig, blond. Ich beobachte sie seit Wochen und… habe einen ungeheuren Wunsch, allein mit ihr zu sein.\nDoch meine gesellschaftliche Stellung und mein Status erlauben es mir nicht, dieses Haus der Sünde zu betreten. Nein, wie Sie sich denken können, mein Freund, habe ich nichts dagegen — aber ein guter Ruf kostet viel.\nDeshalb wende ich mich an Sie. Sie sind neu hier, niemand kennt Sie, und im Moment interessiert sich niemand für Sie. Sie würden mir einen großen Dienst erweisen, Monsieur…";
			link.l1 = "Und wie kann ich Ihnen helfen, mein Herr?";
			link.l1.go = "GigoloMan_3";
		break;
		
		case "GigoloMan_3":
			dialog.text = "Ich schätze Ihre Diskretion, Monsieur. Ich kann nicht zu dem Mädchen gehen, also muss das Mädchen zu mir kommen. In meinem Haus. Ich bitte Sie, ins Bordell zu gehen und einen Deal mit der Madame zu arrangieren, damit sie Ihnen erlaubt, einen 'Hausbesuch' des blonden Mädchens für eine Nacht zu arrangieren\nAurora wird nicht ablehnen, sie ist dafür bekannt, solche Lieferdienste zu leisten, obwohl es immer ein bisschen mehr kostet. Danach sollen Sie das Mädchen zu meinem Haus bringen. Als Bezahlung gebe ich Ihnen sechstausend Pesos. Aurora verlangt normalerweise dreitausend oder dreieinhalb für eine Nacht mit dem Mädchen im Haus. Sie können den Überschuss als Entschädigung für Ihre Mühen behalten.";
			link.l1 = "Hört sich nicht zu kompliziert an. Das kann ich machen.";
			link.l1.go = "GigoloMan_4";
			link.l2 = "Herr, ich nehme meinen Ruf als Gentleman genauso ernst wie Sie. Bitte verzeihen Sie mir, aber ich kann Ihrer Bitte nicht nachkommen. Ich muss ablehnen. Ich sollte wohl zur Taverne gehen und prüfen, ob der Wirt eine Arbeit für mich hat.";
			link.l2.go = "GigoloMan_exit";
		break;
		
		case "GigoloMan_exit":
			DialogExit();
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", false);// бордель open
			LocatorReloadEnterDisable("Fortfrance_town", "reload9", false);// бордель
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", false);// таверна
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			chrDisableReloadToLocation = false;
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			SetCurrentTime(17, 30);
		break;
		
		case "GigoloMan_4":
			dialog.text = "Ich bin sehr erfreut. Hören Sie genau: Das Mädchen, das ich brauche, heißt Lucille. Ich bitte Sie, sie mich nachts zu mir zu bringen, nicht vor elf Uhr, damit niemand uns sieht. Klopfen Sie an die Tür, und ich werde Ihnen öffnen\nMein Haus befindet sich links neben der Gouverneursresidenz, wenn Sie ihm den Rücken zuwenden – ein zweistöckiges Herrenhaus mit rotem Dach. Sie werden es leicht finden, dort ist übrigens auch ein Geschäft in der Nähe. Zudem gehe ich gerade zu meinem Haus, Sie können mir folgen, um zu sehen, wie es genau aussieht und wo es sich befindet, damit Sie sich nachts nicht verirren\nHier, nehmen Sie sechstausend Pesos. Und ich freue mich, Sie zur vereinbarten Zeit zu sehen!";
			link.l1 = "In Ordnung, Monsieur, abgemacht. Bis zur Nacht wird Ihre Blonde an Ihrer Tür sein.";
			link.l1.go = "GigoloMan_5";
		break;
		
		case "GigoloMan_5":
			DialogExit();
			AddMoneyToCharacter(pchar, 6000);
			AddQuestRecord("SharlieC", "1");
			AddQuestUserData("SharlieC", "sName", GetFullName(npchar));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "", -1);
			LocatorReloadEnterDisable("Fortfrance_town", "houseSp1", true);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie.Gigolo = "start";
			pchar.questTemp.Sharlie.Gigolo.Rand1 = rand(1);
			pchar.questTemp.Sharlie.Gigolo.Rand2 = rand(1);
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", false);// бордель open
			LocatorReloadEnterDisable("Fortfrance_town", "reload91", false);// бордель
			AddLandQuestMark(characterFromId("Fortfrance_hostess"), "questmarkmain");
			QuestPointerToLoc("fortfrance_town", "reload", "reload9_back");
			QuestPointerToLoc("fortfrance_brothel", "reload", "reload3");
			chrDisableReloadToLocation = false;
		break;
		
		case "GigoloGirl":
			if (npchar.quest.meeting == "0")
			{
				DelLandQuestMark(npchar);
				QuestPointerDelLoc("fortfrance_town", "reload", "reload9_back");
				dialog.text = "Guten Tag, Monsieur. Sind Sie etwa der Mann, der mich heute Abend angestellt hat? Mein mein, ich muss sagen, ich bin ein glückliches Mädchen, einen so gutaussehenden und gepflegten Gentleman zu ergattern, nichts wie die Bruten, die stinkend nach Teer und Schweiß von den Docks kommen...";
				link.l1 = "Meine Entschuldigung, aber nicht heute Abend, Lucille. Ich bin hier im Namen meines guten Freundes, der aus einer Vielzahl sehr komplizierter Gründe sein Haus nicht verlassen kann, also werde ich dich zu ihm bringen. Jetzt sei nicht verärgert, er ist ein sanfter Mann und hat dich sehr gern. Ich denke, du wirst am Ende glücklich sein.";
				link.l1.go = "GigoloGirl_1";
				// belamour legendary edition -->
				link.l2 = "Ähm... Du hast völlig recht, Liebste. Sollen wir?";
				link.l2.go = "GigoloGirl_1a";
				// <-- legendary edition
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Herr, ich hoffe, Sie verstehen, dass ich nicht einfach mit Ihnen bei Nacht spazieren gehen kann. Sie müssen mich schnell zum Haus Ihres Freundes bringen, oder ich gehe direkt zurück zur Madame und Sie werden Ihr Geld verschwenden.";
				link.l1 = "In Ordnung, ich verstehe. Folge mir!";
				link.l1.go = "GigoloGirl_2";
			}
		break;
		// belamour legendary edition -->
		case "GigoloGirl_1a":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			chrDisableReloadToLocation = true; //закрыть локацию
			DoQuestReloadToLocation(pchar.location+"_room", "goto", "goto2", "GigoloGirl_Sex");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_room", "goto", "goto1");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Rum"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		
		case "GigoloGirl_1":
			AddCharacterExpToSkill(pchar, "Fortune", 40);
		// <-- legendary edition
			dialog.text = "Das ist schade... Sie haben mir sofort gefallen, Monsieur. Ich hätte gerne die Nacht mit Ihnen verbracht... vielleicht beim nächsten Mal. Sollen wir gehen?";
			link.l1 = "Ja. Folge mir!";
			link.l1.go = "GigoloGirl_2";
		break;
		
		case "GigoloGirl_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_Gigolo.win_condition.l1 = "locator";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.locator_group = "reload";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.locator = "houseSp1";
			pchar.quest.Sharlie_Gigolo.function = "Sharlie_GiveGigoloGirl";
			pchar.quest.Sharlie_Gigolo1.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.hour  = sti(GetTime() + 2);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.function = "Sharlie_GigoloGirlOver";
			QuestPointerToLoc("fortfrance_town", "reload", "houseSp1");
		break;
		
		case "GigoloGirl_3":
			dialog.text = "Wie ein prächtiges Haus. Ist das der Ort?";
			link.l1 = "Ja. Komm rein. Hab keine Angst, mein Freund ist ein guter Mann.";
			link.l1.go = "GigoloGirl_4";
		break;
		
		case "GigoloGirl_4":
			dialog.text = "Sie unterschätzen mich, ich habe keine Angst, Monsieur. Ich weiß, wie ich mich behaupten kann. Vielleicht könnten Sie später Madame dafür bezahlen, eine Nacht mit mir zu verbringen? Ich verspreche, es wird die beste Nacht Ihres Lebens sein!";
			link.l1 = "Alles ist möglich, Lucille. Vielleicht treffen wir uns wieder. Auf Wiedersehen!";
			link.l1.go = "GigoloGirl_5";
		break;
		
		case "GigoloGirl_5":
			pchar.quest.Sharlie_Gigolo1.over = "yes";
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "GigoloGirl_Remove", 5.0);
			QuestPointerDelLoc("fortfrance_town", "reload", "houseSp1");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Rum"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		
		//пираты с пленным испанцем
		case "CaptivePirate":
			pchar.quest.Captive_CreatePiratesOver.over = "yes";//снять таймер
			pchar.quest.Captive_CreatePiratesOver2.over = "yes";//снять таймер
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_03", "reload", "reload2_back");
			dialog.text = "Was ist das!? Wer sind Sie? Was wollen Sie hier? Los, hauen Sie ab!";
			link.l1 = "Sie sind nicht sehr höflich, Bürschchen.";
			link.l1.go = "CaptivePirate_1";
		break;
		
		case "CaptivePirate_1":
			dialog.text = "Hör gut zu, Bursche, ich wurde nicht dazu erzogen, höflich zu sein, genauso wie ich nicht gelernt habe zu lesen und zu schreiben, aber deinen Schädel mit einem Entermesser zu spalten ist für mich so einfach wie eine Hure, die rückwärts fällt. Und ich schwöre bei meinen toten Lichtern, dass du hier in dieser Minute herausgehst, sonst wirst du hinausgetragen. Hast du das verstanden?";
			link.l1 = "Nein, hör mir zu, du Schurke. Dein Plan ist aufgeflogen. Ich brauche diesen Mann lebend, also leg deine Waffen nieder und lauf. Eine Gruppe französischer Soldaten befindet sich direkt hinter mir im Dschungel. Wenn du schnell genug rennst, schaffst du es vielleicht, dein erbärmliches Leben zu retten.";
			link.l1.go = "CaptivePirate_3";
			link.l2 = "In Ordnung, in Ordnung, beruhige dich. Ich gehe jetzt.";
			link.l2.go = "CaptivePirate_2";
		break;
		
		case "CaptivePirate_2":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			n = makeint(MOD_SKILL_ENEMY_RATE/2);
			if (n <= 1) n = 2;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("CaptivePirate_"+i);
				LAi_CharacterDisableDialog(sld);
				LAi_SetImmortal(sld, true);
				sld.lifeday = 0;
			}
			sld = characterFromId("CaptiveSpain");
			LAi_SetImmortal(sld, true);
			sld.lifeday = 0;
			pchar.quest.Sharlie_captive1.over = "yes";
			pchar.quest.Sharlie_captive2.over = "yes";//снять прерывание
			AddQuestRecord("SharlieD", "5");
			CloseQuestHeader("SharlieD");
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "CaptivePirate_3":
			dialog.text = "Wa-as? Du bluffst, Kumpel! Nehmt ihn runter, Jungs, zu den Waffen!";
			link.l1 = "Dann sei es auf deinem eigenen Kopf, en garde!";
			link.l1.go = "CaptivePirate_4";
		break;
		
		case "CaptivePirate_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			int n = makeint(MOD_SKILL_ENEMY_RATE/2);
			if (n <= 1) n = 2;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("CaptivePirate_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Captive_PiratesDead");
			AddDialogExitQuest("MainHeroFightModeOn");	
			sld = characterFromId("CaptiveSpain");
			LAi_SetCitizenType(sld);
			DoQuestFunctionDelay("Ngt_CaptiveEng", 0.5);
		break;
		
		//пленный испанец
		case "CaptiveSpain":
			dialog.text = "Dank Gott! Ah, du bist Franzose? Scheiße, du hast diese Banditen mit Stil abgewehrt. Aber denke nicht, dass ich einfach aufgeben und mich ergeben werde, ich werde dir zeigen, wie ein Spanier kämpft! Santiago!";
			link.l1 = "Nein warte, bitte!";
			link.l1.go = "CaptiveSpain_1";
		break;
		
		case "CaptiveSpain_1":
			dialog.text = "Ich würde eher sterben als von den Franzosen gefangen genommen zu werden. Ich habe ein Entermesser von einer der toten Leichen genommen, während du gekämpft hast... jetzt werde ich dich nach einer spanischen Quadrille tanzen lassen!";
			link.l1 = "Ihr Spanier seid so stur wie Maultiere!";
			link.l1.go = "CaptiveSpain_2";
		break;
		
		case "CaptiveSpain_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			NextDiag.currentnode = "CaptiveSpain_3";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "CaptiveSpain_capture");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "CaptiveSpain_3":
			dialog.text = "Verdammter... Du hast gewonnen. Ich gebe auf, verdammt Franzose. Ich bin auf deine Gnade angewiesen.";
			link.l1 = "Steck deine Klinge weg und lass mich sprechen, du sturer Kastilier! Ich will nicht, dass du stirbst, und ich schicke dich auch nicht ins Gefängnis!";
			link.l1.go = "CaptiveSpain_4";
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
		break;
		
		case "CaptiveSpain_4":
			dialog.text = "Dann was machst du? Warum hast du die Piraten getötet? Und wo sind deine Soldaten?";
			link.l1 = "Es gibt keine Soldaten. Ich habe versucht, die Schurken zu täuschen, aber wie du siehst, hat es nicht funktioniert. Ich bin hier ganz allein, auf Anfrage deines alten Freundes. Sein Name ist "+pchar.questTemp.Sharlie.Captive.Name+", er ist ein Bankier in St. Pierre.";
			link.l1.go = "CaptiveSpain_5";
		break;
		
		case "CaptiveSpain_5":
			dialog.text = ""+pchar.questTemp.Sharlie.Captive.Name+"? Ich kenne niemanden mit diesem Namen...";
			link.l1 = "Noch wusste ich nichts über dich oder deine Gefangenschaft. Ich erfuhr von deiner Verlegung auf ein englisches Schiff von ihm. Meine Aufgabe ist es, dich zu ihm zu bringen und ich habe geschworen, dass ich das erfüllen würde! Nun denn, komm mit mir, wenn du leben willst.";
			link.l1.go = "CaptiveSpain_6";
		break;
		
		case "CaptiveSpain_6":
			dialog.text = "Ich habe sowieso keine Wahl ... Dieser Bankier von Ihnen kann nicht schlimmer sein als die Engländer und ihr abscheuliches Kochen ...";
			link.l1 = "Du triffst endlich eine kluge Entscheidung. Das reicht jetzt mit dem Gerede, wir steuern auf St. Pierre zu. Bleib dicht bei mir und weiche nicht ab. Wenn du rennst, werde ich dich fangen und dich wieder bis auf einen Zoll deines Lebens prügeln.";
			link.l1.go = "CaptiveSpain_7";
		break;
		
		case "CaptiveSpain_7":
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.Notsearchbody"); // 170712
			DialogExit();
			AddQuestRecord("SharlieD", "6");
			LAi_group_Register("TempFriends");
			LAi_group_SetRelation("TempFriends", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "TempFriends");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
			pchar.quest.Sharlie_captive3.win_condition.l1 = "locator";
			pchar.quest.Sharlie_captive3.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_captive3.win_condition.l1.locator_group = "reload";
			pchar.quest.Sharlie_captive3.win_condition.l1.locator = "reload8_back";
			pchar.quest.Sharlie_captive3.win_condition.l2 = "Night";
			pchar.quest.Sharlie_captive3.win_condition.l3 = "Alarm";
			pchar.quest.Sharlie_captive3.win_condition.l3.value = 0;
			pchar.quest.Sharlie_captive3.win_condition.l3.operation = "=";
			pchar.quest.Sharlie_captive3.function = "CaptiveSpain_reload";//вход ночью
			pchar.questTemp.Sharlie = "bankskipercaptive";
			SetFunctionLocationCondition("CaptiveSpain_removeGuard", "fortfrance_town", 0);
			SetFunctionLocationCondition("CaptiveSpain_saveTip", "fortfrance_exittown", 0);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_town")], false);
			// Rebbebion, новые марки до места назначения. belamour поправил - были не в ту сторону
			QuestPointerToLoc("shore39", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_03", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload8_back");
			AddLandQuestMark(characterFromId("FortFrance_Usurer"), "questmarkmain");
		break;
		
		//горожанин с пропавшей дочерью
		case "Prosper":
			DelLandQuestMark(npchar);
			pchar.quest.Sharlie_RescueDaughter.over = "yes"; //снять прерывание
			dialog.text = "Was brauchen Sie, Monsieur? Ich habe keine Zeit zum Plaudern, also fassen Sie sich kurz.";
			link.l1 = "Du bist doch Prosper Trubal, oder?";
			link.l1.go = "Prosper_1";
		break;
		
		case "Prosper_1":
			dialog.text = "Ja, das bin ich. Aber Sie haben einen Vorteil gegenüber mir. Bitte teilen Sie mir mit, wer Sie sind und was zum Teufel Sie wollen.";
			link.l1 = "Mein Name ist "+GetFullName(pchar)+". Ich wurde von Ihnen geschickt "+GetFullName(characterFromId("Fortfrance_Hafenmeister"))+", der Hafenmeister. Er sagte, dass du dringend Hilfe brauchst...";
			link.l1.go = "Prosper_2";
		break;
		
		case "Prosper_2":
			dialog.text = "Mein Gott ja! Dieser Schuft von einem Kommandanten hat meine Beschwerde nicht einmal gehört! Er ist entweder zu faul oder zu feige, um zu helfen. Bist du wirklich hier, um mir zu helfen? Wenn es so ist, werde ich dich nicht unbelohnt lassen!";
			link.l1 = "Ja, Prosper. Erzähl mir, was passiert ist und was ich tun muss, um zu helfen. Ich habe gehört, dass deine Tochter verschwunden ist...";
			link.l1.go = "Prosper_3";
		break;
		
		case "Prosper_3":
			dialog.text = "Ja, meine liebe Tochter Celene ist seit zwei Tagen verschwunden. Sie ging zu der nicht weit von hier entfernten Festung spazieren. Aber sie kehrte nicht zurück, also ging ich selbst zur Festung und die Soldaten sagten mir, sie sei nie dort gewesen!\nAber dann wurde ich auf dem Rückweg von zwei wilden Indianern angegriffen! Sie sprangen mit Keulen auf mich zu und versuchten mich zu schlagen\nAber ich bin kein Kätzchen, also habe ich einem ins Gesicht geschlagen, mir genug Zeit gekauft, um meine Pistole zu ziehen und zu schießen. Ich habe verfehlt, aber sie weggeschreckt. Ich schaffte es, die Stadttore zu erreichen und die Wachen über den Angriff zu informieren. Sie rannten in den Dschungel, aber die Wilden waren schon längst verschwunden\nIch bin sicher, dass sie für Celenes Verschwinden verantwortlich sind. Außerdem sind in der letzten Woche noch zwei weitere Personen verschwunden - Cesar Blanchet und Gilbert Courcy! Einer war auf dem Weg zur Bucht und der andere nach Le Francois. Sie sind nie zurückgekehrt.";
			link.l1 = "Also haben die Indianer die Stadtbewohner direkt an den Stadttoren angegriffen? Das ist unglaublich kühn...";
			link.l1.go = "Prosper_4";
		break;
		
		case "Prosper_4":
			dialog.text = "In der Zwischenzeit bin ich selbst in den Dschungel gegangen, um nach ihr zu suchen und fand eine Höhle nördlich der Stadt. Ich fand die Bastarde, die dort hocken. Ich sah einige Indianer am Eingang, aber einige von ihnen müssen auch drinnen sein\nIch hörte ein Mädchen schreien... Es war meine Celene, ich bin mir sicher, es war ihre Stimme! Es hat all meine Zurückhaltung gebraucht, um nicht gleich dort hinein zu rennen - die Chancen standen nicht zu meinen Gunsten und sie hätten mich abgeschlachtet. Tot bin ich ihr keine Hilfe.";
			link.l1 = "Aber warum zum Teufel greifen sie an und nehmen die Stadtbewohner als Gefangene?";
			link.l1.go = "Prosper_5";
		break;
		
		case "Prosper_5":
			dialog.text = "Ich weiß nicht... Vielleicht um sie an Piraten oder Sklavenhändler zu verkaufen? Vielleicht fressen sie sie einfach lebendig, sie sind schließlich Wilde.";
			link.l1 = "Lieber Gott im Himmel, sind sie Kannibalen? Ich dachte, das wären nur Geschichten, um Kinder in Europa zu erschrecken...";
			link.l1.go = "Prosper_6";
		break;
		
		case "Prosper_6":
			dialog.text = "Geschichten? Nun, einige Männer wie du dachten das Gleiche, bis die Kariben sie am Feuer gekocht und gefressen hatten... Also ging ich sofort zum Kommandanten und forderte einen Strafzug, um meine Celene zu retten. Er lehnte ab! Er sagte, wenn Mädchen verschwinden, sind sie wahrscheinlich mit einem Jungen durchgebrannt, nicht mit Indianern. Er schlug vor, ich solle sie in den örtlichen Heuschobern suchen. Und was die beiden anderen Vermissten betrifft... er sagte, einer von ihnen stehe unter Schmuggelverdacht, und der andere trinke wahrscheinlich in der Taverne von Le Francois zu Tode. Zusammenfassend habe ich nichts erreicht und beschlossen, auf eigene Faust zu handeln.";
			link.l1 = "Was hast du vor zu tun?";
			link.l1.go = "Prosper_7";
		break;
		
		case "Prosper_7":
			dialog.text = "Ich werde dort hingehen und jeden verdammten dieser Roten töten. Ich hoffe nur, dass Celene noch lebt. Wie du sehen kannst, habe ich ein Musket gekauft - und ich weiß, wie man damit schießt. Habe eine Menge Münzen dafür ausgegeben, aber das ist mir egal.\nMeine Mission wird viel einfacher sein, wenn du mich begleitest. Zusammen können wir die Wilden ohne viel Mühe erledigen, wenn du mir den Rücken deckst, während ich nachlade. Wirst du mit mir gehen, um meine Tochter zu retten?";
			link.l1 = "Natürlich! Es ist eine Frage der Ehre! Ich kann nicht zulassen, dass ein Mädchen durch das Messer eines Wilden stirbt.";
			link.l1.go = "Prosper_8";
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") {
				link.l1.go = "Prosper_noweapon";
			}
			link.l2 = "Hm. Weißt du, ich denke, die Worte des Kommandanten haben Sinn. Vielleicht sollten wir seinem Rat zuerst folgen?";
			link.l2.go = "Prosper_exit";
		break;
		
		case "Prosper_noweapon":
			dialog.text = "Herr, wo ist Ihre Klinge?";
			link.l1 = "Ich scheine es verlegt zu haben.";
			link.l1.go = "Prosper_noweapon_1";
		break;
		
		case "Prosper_noweapon_1":
			dialog.text = "Das wird einfach nicht reichen. Ich werde auf dich bis zum Abend warten, ich rate dir, zu den Füßen unseres Gouverneurs zu kriechen und um seine Hilfe zu betteln.";
			link.l1 = "An seinen Füßen kriechen, hm? Nun, wie du wünschst...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prosper_getweapon";
			SetFunctionTimerConditionParam("RescueDaughter_Over", 0, 0, 0, 22, false);
		break;
		
		case "Prosper_getweapon":
			dialog.text = "Nun, Monsieur? Haben Sie sich eine Waffe besorgt?";
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") {
				link.l1 = "Noch nicht, bitte warten Sie noch ein bisschen...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Prosper_getweapon";
			} else {
				link.l1 = "Verstanden. Ich bin bereit, Ihnen zu helfen!";
				link.l1.go = "Prosper_8";
				DeleteQuestCondition("RescueDaughter_Over");
			}
		break;

		case "Prosper_exit":
			dialog.text = "Mein Gott, fliehst du? Nein! Verdammt noch mal, hau ab! Feigling!";
			link.l1 = "He-he, ganz ruhig, du Tölpel! Ich sollte besser rausgehen und sehen, ob irgendwelche Adligen auf den Straßen von Saint-Pierre Hilfe brauchen.";
			link.l1.go = "Prosper_exit_1";
			pchar.questTemp.Sharlie.GigoloMan.SamPodbezhit = true;
		break;
		
		case "Prosper_exit_1":
			DialogExit();
			npchar.lifeday = 0;
			//AddTimeToCurrent(2,0);
			SetCurrentTime(17,30);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "gate_back", "none", "", "", "", 10.0);
			CloseQuestHeader("SharlieF");
			chrDisableReloadToLocation = true;
			
			//Подбегает дворянин с квестом "девочка по вызову"
			sld = GetCharacter(NPC_GenerateCharacter("GigoloMan", "Guide_2", "man", "man", 25, FRANCE, 5, true, "soldier"));
			SetFantomParamFromRank(sld, 25, true);
			sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
			sld.dialog.currentnode = "GigoloMan";
			sld.greeting = "noble_male";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetLoginTime(sld, 6.0, 21.0);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Prosper_8":
			dialog.text = "Ich bin froh, dass es in dieser Stadt wenigstens einen mutigen Mann gibt. Hier, nimm diese drei Fläschchen. Das sind gesundheitsfördernde Kräuter, die ich von unserem Kräuterkenner gekauft habe. Sie können dir im Kampf erheblich helfen.";
			link.l1 = "Was ist mit dir?";
			link.l1.go = "Prosper_9";
		break;
		
		case "Prosper_9":
			TakeNItems(pchar, "potion1", 3);
			PlaySound("interface\important_item.wav");
			dialog.text = "Mach dir keine Sorgen, ich habe noch mehr. Bist du bereit?";
			link.l1 = "Ja, verschwenden wir keine Zeit. Vorwärts!";
			link.l1.go = "Prosper_10";
		break;
		
		case "Prosper_10":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "fortfrance_exittown", "reload", "reload3", "OpenTheDoors", 10.0);
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition.l1 = "location";
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition.l1.location = "FortFrance_ExitTown";
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition = "RescueDaughter_ProsperGateOutReload";
			AddQuestRecord("SharlieF", "3");
			pchar.quest.Sharlie_RescueDaughter1.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter1.win_condition.l1.location = "Martinique_jungle_04";
			pchar.quest.Sharlie_RescueDaughter1.function = "RescueDaughter_NearCave";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.hour  = sti(GetTime()+2);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CaveOver";
			NextDiag.CurrentNode = "Prosper_11";
			pchar.questTemp.Sharlie.RescueDaughter = "true";
			LocatorReloadEnterDisable("Fortfrance_exittown", "reload2_back", true);//форт
			LocatorReloadEnterDisable("Martinique_Jungle_01", "reload1_back", true);//джунгли
			LocatorReloadEnterDisable("Martinique_Jungle_04", "reload1_back", true);//джунгли
		break;
		
		case "Prosper_11":
			dialog.text = "Wir sind fast in Position, "+pchar.name+". Jenseits dieser Kurve ist der Eingang zur Höhle. Komm näher und ich erzähle dir unseren Plan.";
			link.l1 = "Ich bin ganz Ohr, Prosper.";
			link.l1.go = "Prosper_12";
		break;
		
		case "Prosper_12":
			dialog.text = "Ich muss mit dieser schweren Flinte ein sicheres Ziel finden, aber wenn du mir Zeit kaufen kannst, werde ich nicht verfehlen. Wenn ich mich im Nahkampf engagieren muss, vergiss jede Feuerunterstützung, ich kann nur Leute mit meinem Lauf als Knüppel abwehren. Dieser Kampf wird von deiner Fechtkunst abhängen.";
			link.l1 = "Was willst du damit sagen?";
			link.l1.go = "Prosper_13";
		break;
		
		case "Prosper_13":
			dialog.text = "Alles, was du tun musst, ist ihre Aufmerksamkeit abzulenken, damit ich sie alle abschießen kann. Ich kann mich nicht bewegen und schießen, also bleibe ich an einem Ort. Es sind drei Bastarde nahe dem Höhleneingang. Du solltest so schnell wie möglich mit gezogenem Schwert auf sie zustürmen. Triff einen von ihnen und lass sie dich verfolgen. Lock sie weg von mir. Wenn alle drei sich auf dich konzentrieren, kann ich sie wie Vögel abschießen, während du parierst und ausweichst. Aber wenn diese Wilden auf mich stürzen, sind wir verloren. Bist du bereit?";
			link.l1 = "Das wird nicht das erste Mal sein, dass ich ein Schwert führe, diese Wilden sind keine Bedrohung.";
			link.l1.go = "Prosper_14";
			// belamour legendary edition -->
			link.l2 = "Ha! Mach dir keine Sorgen um mich. Es ist wie die Jagd in Le Mans! Schieß mir nur nicht aus Versehen in den Rücken!";
			link.l2.go = "Prosper_14a";
		break;
		
		case "Prosper_14a":
			AddCharacterExpToSkill(pchar, "FencingL", 10);
			AddCharacterExpToSkill(pchar, "FencingS", 10);
			AddCharacterExpToSkill(pchar, "FencingH", 10);
			AddCharacterExpToSkill(pchar, "Pistol", 10);
			dialog.text = "Geh zuerst, ich bin hinter dir. Denke daran: du darfst nicht zulassen, dass sie mir nahe kommen!";
			link.l1 = "Ich erinnere mich, los geht's. Vorwärts!";
			link.l1.go = "Prosper_15";
		break;
		
		case "Prosper_14":
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			// <-- legendary edition
			dialog.text = "Dann bereite dich auf die Aktion vor. Geh zuerst, ich werde hinter dir sein. Denk daran: du darfst nicht zulassen, dass sie mir zu nahe kommen!";
			link.l1 = "Ich erinnere mich. Ich werde alles tun, was ich kann. Vorwärts!";
			link.l1.go = "Prosper_15";
		break;
		
		case "Prosper_15":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LocatorReloadEnterDisable("Martinique_jungle_04", "reload2_back", false);
			NextDiag.CurrentNode = "Prosper_16";
			NewGameTip("A challenging fight awaits ahead. (F6) for quick save.");
		break;
		
		case "Prosper_16":
			dialog.text = "Gut gemacht, "+pchar.name+"! Diese heidnischen Wilden werden nicht länger morden. Jetzt zum Hauptereignis - die Höhle. Ich glaube, dass drei oder vier von ihnen drinnen sind, aber ich kann nicht sicher sein. Jetzt hör zu\nIch war vor zehn Jahren dort. Es gibt einen schmalen Tunnel in der Höhle. Er führt zu einer kleinen Grotte, geteilt durch eine Wand mit einem Loch in der Mitte. Wiederholen wir unseren Plan von vorher. Ich stehe still in der Nähe des Eingangs und du stürzt hinein\nProvokiere sie, versuche nicht, alle auf einmal zu bekämpfen, hindere sie einfach daran, mich anzugreifen. Nimm am von mir erwähnten Tunnel Stellung, er ist eng, sodass nur einer oder zwei von ihnen gleichzeitig gegen dich kämpfen können\nIch werde über deine Schulter auf sie schießen. Bereit?";
			link.l1 = "Weiter! Lasst uns dieses Nest von Wilden ausrotten!";
			link.l1.go = "Prosper_17";
		break;
		
		case "Prosper_17":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LocatorReloadEnterDisable("Martinique_CaveEntrance", "reload1_back", false);
			AddComplexSelfExpToScill(20, 20, 20, 20);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.location = "Martinique_Grot";
			pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CreateIndiansGrot";
			NextDiag.CurrentNode = "Prosper_18";
		break;
		
		case "Prosper_18":
			dialog.text = "Meine Tochter lebt! Gott sei Dank! Wir sind rechtzeitig hier angekommen, "+pchar.name+". Ich bin Ihnen zu Dank verpflichtet, Herr. Sie sind ein tapferer Mann und ein guter Kämpfer!";
			link.l1 = "Ich bin froh, dass es ein glückliches Ende gibt, Prosper. Das war eine ziemlich blutige Arbeit, all diese Indianer auszuschalten.";
			link.l1.go = "Prosper_19";
		break;
		
		case "Prosper_19":
			DialogExit();
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
		break;
		
		case "Prosper_20":
			dialog.text = "Mein tiefster Dank noch einmal, "+pchar.name+"! Nun lasst uns zurück in die Stadt machen. Das Leben meiner Tochter ist unbezahlbar, mit keinem Geldbetrag messbar, aber ich möchte dir danken, indem ich dir das gebe, was von meinen Ersparnissen übrig ist. Sobald wir in Saint-Pierre ankommen, werde ich sie dir gerne geben. Und denke nicht einmal daran, abzulehnen!";
			link.l1 = "Ich werde nicht ablehnen, Prosper. Obwohl Geld nicht mein Ziel war, als ich Ihnen half.";
			link.l1.go = "Prosper_21";
		break;
		
		case "Prosper_21":
			dialog.text = "Du bist ein wahrer christlicher Ritter, "+pchar.name+"! Lasst uns hier nicht herumlungern. Auf nach Hause, und zwar postwendend!";
			link.l1 = "...";
			link.l1.go = "Prosper_22";
		break;
		
		case "Prosper_22":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.Tutorial_Amulet.over = "yes";
			SetLaunchFrameFormParam("Back to the town...", "Reload_To_Location", 0, 3.0);
			SetLaunchFrameReloadLocationParam("FortFrance_town", "reload", "gate_back", "");
			LaunchFrameForm();
		break;
		
		case "Prosper_23":
			SelectPresentAmulet();
			dialog.text = "Hier sind wir, Charles. Ich danke dir noch einmal für deine Hilfe und verbinde diese bescheidene Summe an Pesos und Gold-Dublonen mit meinen Worten. Ich schlage vor, du verschwendest nicht die Dublonen und behältst sie für besondere Anlässe. Ich weiß, das ist nicht viel Geld für so einen Dienst, den du mir gewährt hast, aber es kommt von Herzen. Nimm auch dieses Amulett, "+pchar.questTemp.SMQ.Text+"";
			link.l1 = "Danke! Leb wohl Prosper, ich wünsche dir und deiner lieben Tochter Glück!";
			link.l1.go = "Prosper_24";
		break;
		
		case "Prosper_24":
			LocatorReloadEnterDisable("Fortfrance_exittown", "reload2_back", false);//форт
			LocatorReloadEnterDisable("Martinique_Jungle_01", "reload1_back", false);//джунгли
			LocatorReloadEnterDisable("Martinique_Jungle_04", "reload1_back", false);//джунгли
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(pchar, "gold_dublon", 15);
			TakeNItems(pchar, pchar.questTemp.SMQ.Amulet, 1);
			Log_Info("You've received 15 doubloons");
			Log_Info("You've received an amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ach, ein Ehemann wie du würde ihr gut tun. Sie wird nur von einer Bande dünnbeiniger, kinnloser Gecken durch die Stadt gejagt. Es ist so verdammt schade, dass jeder einzelne von ihnen irgendwo verschwunden ist... Gott sei Dank sind sie weg. Viel Glück, Charles!";
			link.l1 = "...";
			link.l1.go = "Prosper_25";
		break;
		
		case "Prosper_25":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload10_back", "none", "", "", "", 10.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar,"authority", 2);
			AddCharacterExpToSkill(pchar, "Leadership", 120);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 70);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 70);//скрытность
			AddQuestRecord("SharlieF", "7");
			CloseQuestHeader("SharlieF");
			DeleteAttribute(pchar, "questTemp.SMQ");
			pchar.questTemp.Prosper_fmql = "true"; // Addon-2016 Jason, французские миниквесты (ФМК)
			pchar.questTemp.ZsI_Cannibals = true;	//Sinistra Требуется для квеста "Знакомство с индейцами"
			pchar.quest.Sharlie_JungleNative.win_condition.l1 = "location";
			pchar.quest.Sharlie_JungleNative.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.Sharlie_JungleNative.function = "SharlieJungleNative";
			SetCurrentTime(17,30);
			//AddTimeToCurrent(2,0);
			//QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Selina":
			dialog.text = "Ach! Gott hilf mir! (weinend) Du...du kannst dir den Horror, der hier vor sich geht, nicht einmal vorstellen! Diese... diese Indianer haben uns hierher geschleppt, um uns zu töten und zu essen! Cesar Blanchet war hier... Die Wilden haben ihn genommen... Sie haben irgendein schreckliches teuflisches Ritual durchgeführt und dann... Herr, ich kann es nicht einmal aussprechen! Ich sollte der Nächste sein! Sie wollten mich... morgen schlachten!";
			link.l1 = "Beruhige dich, Celine. Es ist alles vorbei. Diese Bastarde haben bekommen, was sie verdienen und sie werden niemandem mehr wehtun.";
			link.l1.go = "Selina_1";
		break;
		
		case "Selina_1":
			dialog.text = "Gilbert Coursie ist auch hier. Dort drüben... er äh...er hat sich noch nicht erholt. Sprich mit ihm... Dann lass uns schnell hier raus!";
			link.l1 = "Da, da. Alles ist gut, Mädchen. Genug mit dem Weinen. Alles ist in Ordnung. Du hast einen wunderbaren Vater. Er würde niemandem erlauben, dir etwas anzutun... Geh nach draußen, ich helfe... äh... Gilbert hier raus und ich komme später zu dir.";
			link.l1.go = "Selina_2";
		break;
		
		case "Selina_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
			sld = characterFromId("RD_Prosper");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_1", "", 5.0);
			AddQuestRecord("SharlieF", "5");
			sld = characterFromId("RD_Jilberte");
			LAi_SetStayType(sld);
		break;
		
		case "Selina_3":
			dialog.text = "Gott und die Heilige Mutter haben meine Gebete erhört! Bist du gekommen, um uns zu retten?";
			link.l1 = "Du... Dein Name ist Celine, nicht wahr?";
			link.l1.go = "Selina_4";
		break;
		
		case "Selina_4":
			dialog.text = "Ja... (weint) Du...du kannst dir nicht vorstellen, welcher Horror hier vor sich geht! Diese... diese Indianer haben uns hierher geschleppt, um uns zu töten und zu essen! Cesar Blanchet war hier... Sie haben ihn genommen... Sie haben irgendein teuflisches Ritual durchgeführt und dann... Herr, ich kann nicht einmal darüber sprechen! Ich sollte der Nächste sein! Sie wollten mich morgen schlachten!";
			link.l1 = "Beruhige dich, kleines Mädchen... Es tut mir leid, aber ich bringe dir schlechte Nachrichten. Ich bin hier mit deinem Vater. Er wurde gerade draußen von diesen rothäutigen Wilden getötet, als wir kämpften, um zu dir zu kommen. Er gab sein Leben, um dich zu retten.";
			link.l1.go = "Selina_5";
		break;
		
		case "Selina_5":
			dialog.text = "Was?! Mein Vater... Oh Gott! Ich... Ich...(schluchzt)";
			link.l1 = "Mein Beileid, Celine. Es gibt einen anderen hier bei dir, habe ich recht?";
			link.l1.go = "Selina_6";
		break;
		
		case "Selina_6":
			dialog.text = "(unter Tränen) Ja... Gilbert Coursie. Er ist dort drin... Er hat sich noch nicht erholt. Geh und sprich mit ihm... Dann lass uns hier schnell raus!";
			link.l1 = "Ja, natürlich. Wir können keine Minute hier herumstehen verschwenden.";
			link.l1.go = "Selina_7";
		break;
		
		case "Selina_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
			AddQuestRecord("SharlieF", "6");
			sld = characterFromId("RD_Jilberte");
			LAi_SetStayType(sld);
			AddComplexSelfExpToScill(20, 20, 20, 20);
		break;
		
		case "Selina_8":
			dialog.text = "Mein Vater... Mein armer, lieber Vater! Ah, Monsieur, ich habe Ihnen noch nicht einmal für meine Rettung gedankt...";
			link.l1 = "Selina, ich bin einfach nur froh, dass du und Gilbert lebend aus dieser Höhle herausgekommen seid. Der heldenhafte Tod deines Vaters war nicht umsonst.";
			link.l1.go = "Selina_9";
		break;
		
		case "Selina_9":
			dialog.text = "(weinend) Bitte, Monsieur, nehmen Sie uns mit in die Stadt. Wir müssen die Soldaten holen lassen, um den Körper meines Vaters zu holen, damit er ein ordentliches christliches Begräbnis bekommt...";
			link.l1 = "Natürlich, Celine. Folge mir!";
			link.l1.go = "Selina_10";
		break;
		
		case "Selina_10":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Selina_11":
			dialog.text = "Danke, Monsieur, dass Sie meinen armen Vater begleitet haben... Danke, dass Sie mich vor einem sicheren Tod gerettet haben. Ich... Ich... Hier, nehmen Sie diesen Beutel mit Dublonen. Ich habe ihn zu Hause in der Truhe meines Vaters gefunden. Bitte, wagen Sie es nicht einmal, ihn abzulehnen!";
			link.l1 = "Danke, Celine. Ich bin froh, dass wir dich retten konnten. Und mein aufrichtiges Beileid zum Verlust deines Vaters.";
			link.l1.go = "Selina_12";
		break;
		
		case "Selina_12":
			TakeNItems(pchar, "gold_dublon", 15);
			PlaySound("interface\important_item.wav");
			dialog.text = "Sie sind ein edler Mann, Monsieur. Ich werde Sie nie vergessen. Lebewohl!";
			link.l1 = "Auf Wiedersehen, Celine.";
			link.l1.go = "Selina_13";
		break;
		
		case "Selina_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar,"authority", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			AddQuestRecord("SharlieF", "8");
			CloseQuestHeader("SharlieF");
			pchar.questTemp.ZsI_Cannibals = true;	//Sinistra Требуется для квеста "Знакомство с индейцами"
			
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Jilberte":
			PlaySound("Voice\English\other\robinzons-08.wav");
			dialog.text = "Oh Herr, ist es wirklich alles hinter uns? Ich kann es kaum glauben... Du hast sowohl mich als auch Celine gerettet. Wäre es nicht für dich gewesen, wäre das gleiche Schicksal, das den unglücklichen Cesar ereilt hat, morgen über sie gekommen und das gleiche wäre in ein paar Tagen für mich vorbereitet.";
			link.l1 = "Diese Indianer, sind sie wirklich Kannibalen?!";
			link.l1.go = "Jilberte_1";
		break;
		
		case "Jilberte_1":
			dialog.text = "Du zweifelst daran? Wenn du einen starken Magen hast, schau in die Asche ihres Kochfeuers. Dort findest du den armen alten Cesar. Jetzt sind es nur noch angeknabberte Knochen...";
			link.l1 = "Gesegnetes Sakrament... Nein, ich verzichte. Ich bin erst kürzlich aus Europa hierher gekommen und konnte mir nicht einmal vorstellen, dass solche abscheulichen teuflischen Dinge noch auf der Erde stattfinden.";
			link.l1.go = "Jilberte_2";
		break;
		
		case "Jilberte_2":
			dialog.text = "Viele seltsame Dinge geschehen in der Karibik, Dinge, von denen du in der Alten Welt nur Flüstern gehört hast... Indianische Medizinmänner, Magie, Schamanen und geheime Rituale. Bleibe hier länger und du wirst allerlei Teufelei bezeugen. Aber verzeih mir, ich habe dir noch nicht für deine Rettung gedankt - ich bin immer noch geschockt\nDu hast mein Leben gerettet und ich werde meine Dankbarkeit nicht nur in Worten, sondern auch in Gold ausdrücken. Begleite Celine und mich in die Stadt. Dort werde ich dir danken können, wie du es verdienst, Monsieur.";
			link.l1 = "In Ordnung. Tritt hinaus. Ich werde zuerst hier ein wenig umsehen.";
			link.l1.go = "Jilberte_3";
		break;
		
		case "Jilberte_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_3", "OpenTheDoors", 10.0);
			pchar.quest.Sharlie_RescueDaughter5.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter5.win_condition.l1.location = "Martinique_CaveEntrance";
			pchar.quest.Sharlie_RescueDaughter5.function = "RescueDaughter_GoHome";
		break;
		
		case "Jilberte_4":
			dialog.text = "Lassen Sie mich Ihnen noch einmal meinen tiefsten Dank für Ihre Rettung ausdrücken, Monsieur! Wie versprochen, füge ich zu meinem mündlichen Dank materiellen Dank in Form von Silberpesos und Gold-Doubloon hinzu.";
			link.l1 = "Ich bin froh, dass alles zum Besten gewendet hat, Gilbert.";
			link.l1.go = "Jilberte_5";
		break;
		
		case "Jilberte_5":
			AddMoneyToCharacter(pchar, 3000);
			TakeNItems(pchar, "gold_dublon", 20);
			Log_Info("You've received 20 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Sie können sich gar nicht vorstellen, wie glücklich ich darüber bin! Nochmals vielen Dank und gestatten Sie mir, mich zu verabschieden, Monsieur.";
			link.l1 = "Viel Glück, Gilbert! Übrigens, weißt du zufällig, ob sonst noch jemand in Saint-Pierre Hilfe braucht?";
			link.l1.go = "Jilberte_6a";
		break;
		
		case "Jilberte_6a":
			dialog.text = "Ich weiß nicht, aber... Sie können die Bürger auf den Straßen fragen, Monsieur. Gewöhnliche Stadtbewohner und sogar die wohlhabenden sind unwahrscheinlich, dass sie etwas Würdiges anbieten, aber die reichen Adligen... sie könnten eine Aufgabe für Sie haben.";
			link.l1 = "Verstanden, Gilbert, danke. Wir sehen uns!";
			link.l1.go = "Jilberte_6";
		break;
		
		case "Jilberte_6":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.Sharlie.RescueDaughter");
			
			//Подбегает дворянин с квестом "девочка по вызову"
			sld = GetCharacter(NPC_GenerateCharacter("GigoloMan", "Guide_2", "man", "man", 25, FRANCE, 5, true, "soldier"));
			SetFantomParamFromRank(sld, 25, true);
			sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
			sld.dialog.currentnode = "GigoloMan";
			sld.greeting = "noble_male";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetLoginTime(sld, 6.0, 21.0);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto1");
			sld.talker = 9;
			LAi_SetCitizenType(sld);
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin ein gesetzestreuer Bürger dieser Stadt. Ich muss dich bitten, nicht mit gezogenem Schwert wie ein Räuber herumzulaufen.","Herr, bitte, es ist gesetzlich festgelegt, dass Männer innerhalb der Stadtmauern nicht mit gezogenen Waffen umhergehen dürfen.");
			link.l1 = LinkRandPhrase("In Ordnung.","Sehr gut.","Wie du wünschst...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (npchar.id == "GigoloMan") NextDiag.TempNode = "GigoloMan";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

void SelectPresentAmulet()
{
	switch (pchar.HeroParam.HeroType)
	{        
		case "HeroType_1":
			pchar.questTemp.SMQ.Amulet = "indian_7";
			pchar.questTemp.SMQ.Text = "it adds endurance and gives a second wind.";
		break;
		
		case "HeroType_2":
			pchar.questTemp.SMQ.Amulet = "amulet_7";
			pchar.questTemp.SMQ.Text = "it heightens resilience to battle wounds.";
		break;
		
		case "HeroType_3":
			pchar.questTemp.SMQ.Amulet = "indian_4";
			pchar.questTemp.SMQ.Text = "it raises the attack strength of your weapons.";
		break;
		
		case "HeroType_4":
			pchar.questTemp.SMQ.Amulet = "indian_1";
			pchar.questTemp.SMQ.Text = "it makes fire weaponry much more lethal.";
		break;
	}
}
