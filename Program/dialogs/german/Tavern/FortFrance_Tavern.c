// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Welche Fragen haben Sie?","Wie kann ich Ihnen helfen, "+GetAddress_Form(NPChar)+"?"),"Du hast versucht, mir vor kurzem eine Frage zu stellen, "+GetAddress_Form(NPChar)+"...","Den ganzen Tag über ist dies das dritte Mal, dass du von irgendeiner Frage sprichst...","Noch mehr Fragen, nehme ich an?","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert...","Ich habe im Moment nichts zu besprechen."),"Hmm, wo ist mein Gedächtnis hin...","Ja, es ist wirklich das dritte Mal...","Nein, welche Fragen?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Jason, Бремя гасконца
			if (!CheckAttribute(npchar, "quest.Rum") && CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.questTemp.Sharlie == "ship" && int(environment.time) > 5.0 && int(environment.time) < 19.0)
			{
				link.l1 = "Herr, ich suche Arbeit. Haben Sie irgendwelche Jobs?";
                link.l1.go = "Sharlie_rum";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") && pchar.questTemp.Sharlie.Rum == "regard")
			{
				link.l1 = "Ich habe Ihren Auftrag erfüllt. Das Langboot mit dem Rum wurde zur Bucht von Le Francois geliefert und Ihren Leuten übergeben.";
                link.l1.go = "Sharlie_rum_5";
			}	
			//<-- Бремя гасконца */
			
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToMartinique" && !CheckAttribute(npchar, "quest.Portugal"))
			{
				link.l1 = "Ich muss eines Ihrer Zimmer für zwei oder drei Tage mieten. Ich habe einen verletzten Mann an Bord. Er muss sich ausruhen und erholen.";
				link.l1.go = "Portugal";
			}
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernorEnd")
			{
				link.l1 = "Erzähl mir. Mein Freund, für den ich ein Zimmer gemietet habe, ist er gegangen? Er versprach auf mich zu warten, aber das Zimmer ist leer.";
				link.l1.go = "Portugal_2";
			}
			//Португалец
			// Jason Долго и счастливо
			if (!CheckAttribute(npchar, "quest.LongHappy") && CheckAttribute(PChar, "questTemp.LongHappy.MarryRum") && LongHappy_CheckTavernGoods())
			{
				link.l1 = "Ich werde eine Party für meine Männer organisieren. Ich nehme an, du weißt bereits davon?";
				link.l1.go = "LH_tavern_SP";
			}
			if (CheckAttribute(npchar, "quest.LongHappy.Nomoney") && LongHappy_CheckTavernGoods() && int(Pchar.money) >= 100000+int(pchar.questTemp.LongHappy.MarryMoney))
			{
				link.l1 = "Ich habe alles für unsere Feier mitgebracht.";
				link.l1.go = "LH_tavern_SP_3";
			}
		break;
		
		//--> Jason, Бремя гасконца
		case "Sharlie_rum":
			DelLandQuestMark(npchar);
			dialog.text = "Eine Aufgabe? Hm... Du siehst aus, als hättest du ein bisschen Verstand, Junge. Ich könnte etwas für dich haben\nDiese Arbeit mag einfach klingen, erfordert aber Verantwortung und Verstand. Ich kann diesen Idioten nicht trauen, Geschäfte zu machen, sie werden es sicherlich ruinieren...";
			link.l1 = "Hör zu, könntest du mir bitte einfach sagen, was zum Teufel du mir auftragen willst? Ich schwöre, ich werde dich nicht enttäuschen oder zumindest werde ich mein Bestes geben.";
			link.l1.go = "Sharlie_rum_1";
		break;
		
		case "Sharlie_rum_1":
			switch(rand(4))
			{
				case 0:
					pchar.questTemp.Sharlie.Rum.Pass = "Old Thomas has grown tired of waiting for the beer";
				break;
				case 1:
					pchar.questTemp.Sharlie.Rum.Pass = "The boards and the oakum will be here in the morning";
				break;
				case 2:
					pchar.questTemp.Sharlie.Rum.Pass = "Don't wait for the south wind";
				break;
				case 3:
					pchar.questTemp.Sharlie.Rum.Pass = "The bay is ready for disembarkation";
				break;
				case 4:
					pchar.questTemp.Sharlie.Rum.Pass = "The camels are going north";
				break;
			}
			dialog.text = "Gut. Ich brauche jemanden, der mehrere Kisten feinen Jamaica-Rum in meine Taverne liefert. Hier ist das Ding, Importzölle schmälern meine Gewinnspanne und meine besten Kunden sind durstig, also müssen wir klug handeln, um die Zollbeamten zu vermeiden. Die Schaluppe 'Ghost' wird heute Nacht vor Martinique ankommen\nSie wird nicht weit von der Lamanten Bucht vor Anker gehen. Du musst dieses Schiff finden und an Bord gehen. Ich werde dir ein Ruderboot und fünf Matrosen zur Verfügung stellen, sie werden deinen Befehlen folgen\nSobald du an Bord bist, wird dich ein Mann ansprechen. Du wirst ihm ein Passwort sagen müssen: '"+pchar.questTemp.Sharlie.Rum.Pass+"'\nDie Antwort wird sein 'Warum nicht einen Rum, Seemann?'. Du hast nur einen Versuch, also schreib es dir auf und mache keinen Fehler, sonst ist der Handel abgeblasen. Deshalb kann ich es diesen hirnlosen Idioten, die mit dir segeln werden, nicht anvertrauen. Wiederhole das Passwort.";
			link.l1 = "'Hallo, Freund.'"+pchar.questTemp.Sharlie.Rum.Pass+"'.";
			link.l1.go = "Sharlie_rum_2";
		break;
		
		case "Sharlie_rum_2":
			dialog.text = "Großartig. Wiederhole es dir ein paar Mal mehr, oder besser noch, schreibe es irgendwo auf. Nachdem du das Passwort dem Kapitän des Luggers genannt hast, werden die Kisten mit Rumflaschen auf das Longboat geladen, das du dann zur Bucht der Piratensiedlung Le Francois segeln musst - dort wird man dich begrüßen.\nDas ist die ganze Aufgabe. Du kannst zu Fuß von der Bucht Le Francois nach Saint Pierre kommen - das Longboat bleibt in der Bucht. Ich werde fünftausend Dublonen zahlen, sobald es erledigt ist.";
			link.l1 = "Schmuggeln klingt sowohl spannend als auch lukrativ. Ich werde tun, was du mir gesagt hast. Wo ist das Beiboot?";
			link.l1.go = "Sharlie_rum_3";
			link.l2 = "Also, du schlägst vor, dass ich mit Schmuggel anfange? Hm... Weißt du, ich kann meinen Namen nicht riskieren. Du wirst mir verzeihen müssen, wir tun einfach so, als hätte ich nichts gehört.";
			link.l2.go = "Sharlie_rum_exit";
		break;
		
		case "Sharlie_rum_exit":
			dialog.text = "Wie Sie wünschen, Monsieur. Ich habe keine anderen Jobs.";
			link.l1 = "Ich verstehe. Dann alles Gute, "+npchar.name+".";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
			SetCurrentTime(23, 0);
			Sharlie_removeLocks("");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload4_back");
		break;
		
		case "Sharlie_rum_3":
			dialog.text = "Das Beiboot wird um sieben Uhr abends am Pier sein. Die Besatzung auf dem Beiboot ist geschickt, daher solltest du schnell zum Schoner gelangen. Die ganze Aufgabe sollte nicht mehr als vier Stunden dauern - ich bin sicher, du wirst bis elf Uhr abends zurück in Saint Pierre sein. Nimm dieses Fernglas, es ist ein Stück Schrott, aber besser als nichts. Der Lamanten Strand befindet sich im nördlichen Teil der Insel, also halte den Kurs gen Norden, wenn du den Hafen verlässt. Viel Glück!";
			link.l1 = "In Ordnung, verstanden. Bis bald, "+npchar.name+"!";
			link.l1.go = "Sharlie_rum_4";
		break;
		
		case "Sharlie_rum_4":
			DialogExit();
			AddQuestRecord("SharlieB", "1");
			AddQuestUserData("SharlieB", "sPassword", pchar.questTemp.Sharlie.Rum.Pass);
			GiveItem2Character(pchar, "spyglass1"); 
			Log_Info("You've received a spyglass");
			PlaySound("interface\important_item.wav");
			if(CheckAttribute(pchar, "questTemp.Sharlie.FastStart"))
			{
				GiveItem2Character(pchar, "map_martiniqua");
				Log_Info("You have received a map of Martinique");
				RefreshEquippedMaps(GetMainCharacter());
			}
			/* pchar.quest.Sharlie_rum.win_condition.l1 = "location";
			pchar.quest.Sharlie_rum.win_condition.l1.location = "Fortfrance_town"; */
			//pchar.quest.Sharlie_rum.win_condition.l1.locator_group = "rld";
			//pchar.quest.Sharlie_rum.win_condition.l1.locator = "loc0";
			pchar.quest.Sharlie_rum.win_condition.l1 = "HardHour";
			pchar.quest.Sharlie_rum.win_condition.l1.hour = 19.00;
			pchar.quest.Sharlie_rum.function = "Rum_CreateBarkas";
			SetFunctionTimerCondition("Rum_CreateBarkasOver", 0, 0, 1, false);
			pchar.questTemp.Sharlie.Rum = "true";
			npchar.quest.Rum = "true";
			NewGameTip("Open your inventory (F1) and equip the spyglass.");
			pchar.quest.NgtBarkas.win_condition.l1 = "location";
			pchar.quest.NgtBarkas.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.NgtBarkas.win_condition.l2 = "HardHour";
			pchar.quest.NgtBarkas.win_condition.l2.hour = 19.00;
			pchar.quest.NgtBarkas.function = "NgtBarkas";
			AddTimeToCurrent(1,30);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload4_back");
			QuestPointerToLoc("fortfrance_town", "reload", "reload1_back");
		break;
		
		case "Sharlie_rum_5":
			dialog.text = "Wunderbar! Ich wusste, dass ich mich auf dich verlassen kann. War es schwer?";
			link.l1 = "Nun, das hängt davon ab, wie du hart definierst...";
			link.l1.go = "Sharlie_rum_6";
		break;
		
		case "Sharlie_rum_6":
			dialog.text = "Nun, hier ist deine Belohnung: fünftausend Pesos. Du kannst das Fernglas behalten. Und außerdem, ein weiteres kleines Geschenk, bitte, nimm diese drei Flaschen Rum. Nachdem du es probiert hast, wirst du verstehen, warum es so sehr nachgefragt wird.";
			link.l1 = "Danke! Es war schön, mit Ihnen zu arbeiten! Bis später!";
			link.l1.go = "Sharlie_rum_7";
		break;
		
		case "Sharlie_rum_7":
			DialogExit();
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(pchar, "potionrum", 3);
			AddQuestRecord("SharlieB", "5");
			CloseQuestHeader("SharlieB");
			DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload4_back");
			DelLandQuestMark(npchar);
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		//<-- Бремя гасконца
		
		//Португалец
		case "Portugal":
			dialog.text = "Kein Problem, ich habe ein Zimmer. Für 50 Pesos gehört es dir für drei Tage.";
			if (int(pchar.money) >= 50)
			{
				link.l1 = "Hier, bitte.";
				link.l1.go = "Portugal_1";
			}
			else
			{
				link.l1 = "Ich werde das Geld vom Schatzmeister holen und komme zurück.";
				link.l1.go = "exit";
			}
		break;
		
		case "Portugal_1":
			ref sld;
			DialogExit();
			AddMoneyToCharacter(pchar, -50);
			npchar.quest.Portugal = "true";
			LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", false);
			pchar.quest.Portugal_Ill3.over = "yes";
			LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("Fortfrance_town", "gate_back", true);//закрыть выходы из города
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto3");
			sld = characterFromId("PortugalDoctor");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto1");
			pchar.quest.Portugal_tavernroom.win_condition.l1 = "location";
			pchar.quest.Portugal_tavernroom.win_condition.l1.location = "FortFrance_tavern_upstairs";
			pchar.quest.Portugal_tavernroom.function = "PortugalInTavernRoom";
		break;
		
		case "Portugal_2":
			dialog.text = "Ich würde nicht sagen, dass er von selbst aufgestanden und aus dem Raum gegangen ist, Monsieur. Gestern sind hier einige Leute vorbeigekommen. Einer von ihnen war ein einäugiger großer hagerer Mann - ein offensichtlicher Bandit, wie er aussieht, und ein lispelnder Mann auch, sah aus wie ein Kastilier. Ich war nur überrascht, aber dieser Lispeler hat mich angesehen ... genau wie eine Laus vor einer Prügelstrafe. Und so haben sie nach deinem Freund gefragt ... und ich habe ihnen erzählt. Was sollte ich sonst tun?";
			link.l1 = "Ich weiß, "+npchar.name+", du bist kein Held, das stimmt. Was hast du noch gesehen? Wohin sind sie gegangen?";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "Das ist alles... warte, nein! Halt, der einäugige Mann hat etwas von einem Wagen gesagt. Ich schätze, sie haben einen Wagen genommen und deinen Freund klar auf die andere Seite der Insel geschleppt. Das ist alles, Monsieur, ich schwöre... Ich würde die Wache rufen, aber dieser Lispeler hat mir gesagt, ich hätte eine schöne Frau, bevor er ging... Siehst du? Wenn sie herausfinden, dass ich dir all das erzählt habe, werden sie...";
			if (pchar.money >= 1000)
			{
				link.l1 = "Hab keine Angst, sie werden nichts von mir hören außer Kugeln. Du hast mir wirklich geholfen, danke. Hier, nimm 1000 Pesos als Belohnung.";
				link.l1.go = "Portugal_4";
			}
			link.l2 = "Es ist nicht viel, aber danke trotzdem. Rufe das nächste Mal die Wache und sei nicht so ein Tölpel.";
			link.l2.go = "Portugal_5";
		break;
		
		case "Portugal_4":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Danke, Monsieur. Ich kann Ihnen mein Wort geben, dass Ihr Freund sich fast erholt hat. Er konnte zumindest alleine gehen. Und der eine Mann, dieser stille Holländer, er kam in diesem Moment von draußen herein, sah das ganze Durcheinander und sprang zurück nach draußen, verschwand einfach danach.";
			link.l1 = "Ich würde sagen, er ist bereits mit dem ersten Schiff abgereist, das er nehmen konnte. Danke für die Information, es ist Zeit für mich zu gehen.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_5":
			dialog.text = "Nicht jeder Mann kann ein Held sein mit gezogenem Schwert, Kapitän.";
			link.l1 = "Nun... das ist die Wahl des Mannes.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			DialogExit();
			sld = characterFromId("Avendel");
			sld.dialog.currentnode = "Avendel_seapatrol_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		//Португалец
		
		// Jason Долго и счастливо
		case "LH_tavern_SP":
			npchar.quest.LongHappy = "true";
			dialog.text = "Ja, Ihre Assistentin kam vorbei, aber ich habe ihr und werde es Ihnen wiederholen - ich habe mich an die Massen von betrunkenen Seeleuten gewöhnt, aber ich weiß, wie Ihre Parteien ablaufen. Was übrig bleibt, wird aussehen wie Antwerpen nach dem Besuch der spanischen Tercios. Ich wäre froh, wenn die Wände noch stehen würden. Also, wenn Sie die Massen prügeln wollen, werde ich eine nicht erstattungsfähige Anzahlung über das hinaus benötigen, was Sie bereits gebracht haben. Im Falle von Konsequenzen, sozusagen.";
			link.l1 = "Du schlauer Fuchs! Ich trinke selbst seit vielen Jahren mit Seehunden, ich war in verschiedenen... Einrichtungen, und ich weiß, dass wir für das Geld, das ich mitgebracht habe, deine Taverne von Grund auf neu aufbauen könnten! Nutzt die Gelegenheit, hm? Gut, ich habe eine Hochzeit und habe keine Lust, mich mit solchen Kleinigkeiten zu belästigen - wie viel willst du?";
			link.l1.go = "LH_tavern_SP_1";
		break;
		
		case "LH_tavern_SP_1":
			dialog.text = "Noch 100.000 Acht-Reales-Stücke sollten ausreichen und mach dir keine Sorgen - Ich mache alles auf bestmögliche Weise. Deine Jungs werden sich noch lange an diese Party erinnern, merk dir meine Worte!";
			if (int(Pchar.money) >= 100000+int(pchar.questTemp.LongHappy.MarryMoney))
			{
				link.l1 = "Sie müssen es wirklich versuchen - das ist ein besonderer Anlass, verstehen Sie. Und ja, nach der Feier kommen Sie nicht zu mir mit Beschwerden, selbst wenn Ihre Taverne abbrennt.";
				link.l1.go = "LH_tavern_SP_4";
			}
			else
			{
				link.l1 = "Es scheint schon, als würde ich eine königliche Hochzeit organisieren! Warte, ich bin gleich wieder da.";
				link.l1.go = "LH_tavern_SP_2";
			}
		break;
		
		case "LH_tavern_SP_2":
			DialogExit();
			npchar.quest.LongHappy.Nomoney = "true";
		break;
		
		case "LH_tavern_SP_3":
			dialog.text = "Deine Jungs werden sich lange an diese Party erinnern, merk dir meine Worte!";
			link.l1 = "Sie müssen es wirklich versuchen - dies ist ein besonderer Anlass, verstehen Sie. Kommen Sie nicht zu mir weinen, wenn meine Jungs Ihre Taverne versehentlich niederbrennen.";
			link.l1.go = "LH_tavern_SP_4";
		break;
		
		case "LH_tavern_SP_4":
			DialogExit();
			RemoveCharacterGoods(pchar, GOOD_RUM, int(pchar.questTemp.LongHappy.MarryRum));
			AddMoneyToCharacter(pchar, -int(pchar.questTemp.LongHappy.MarryMoney));
			AddMoneyToCharacter(pchar, -100000);
			DeleteAttribute(npchar, "quest.LongHappy.Nomoney");
			pchar.questTemp.LongHappy.DrinkReady = "true";
			pchar.questTemp.LongHappy.MarrySP = "true";
			DeleteAttribute(pchar, "questTemp.LongHappy.MarryMoney");
			DeleteAttribute(pchar, "questTemp.LongHappy.MarryRum");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
