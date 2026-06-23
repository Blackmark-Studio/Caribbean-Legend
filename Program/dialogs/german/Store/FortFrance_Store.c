// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Mach weiter, was willst du?","Wir haben gerade darüber gesprochen. Du musst es vergessen haben...","Das ist das dritte Mal heute, dass du von irgendeiner Frage sprichst...","Hör zu, das ist ein Laden. Leute kaufen hier Sachen. Stör mich nicht!","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Weißt du, "+NPChar.name+", vielleicht nächstes Mal.","Richtig, ich habe aus irgendeinem Grund vergessen...","Ja, es ist wirklich das dritte Mal...","Hm, ich werde nicht...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
			{
				Link.l1 = "Hören Sie, Monsieur, ich suche eine Arbeit. Nicht so eine Vollzeitbeschäftigung oder das Schleppen von Frachttaschen, sondern eher so etwas wie Botengänge, sozusagen. Brauchen Sie zufällig Hilfe?";
				Link.l1.go = "Sharlie_storehelper";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
			{
				Link.l1 = "Ich habe Ihren Auftrag erledigt. Ich habe Gralam Lavoie gefunden.";
				Link.l1.go = "Sharlie_storehelper_2";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
			{
				Link.l1 = "Treffen Sie Ihren neuen Assistenten, Monsieur.";
				Link.l1.go = "Sharlie_storehelper_11";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
			{
				Link.l1 = "Es bin wieder ich, Monsieur. Ich bin wegen meiner Belohnung gekommen.";
				Link.l1.go = "Sharlie_storehelper_13";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = "Nehmen Sie einen Blick auf diese Ohrringe, Herr. Ich habe sie auf dem Körper eines Banditen gefunden, der im Dschungel getötet wurde. Dies ist eindeutig das Werk eines feinen Juweliers, der, wie ich sicher bin, nicht von hier stammt. Können Sie etwas über diese Ohrringe sagen?";
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Бремя гасконца */
		break;
		
		//--> Бремя гасконца
		case "Sharlie_storehelper":
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") 
			{
				dialog.text = "Entschuldigen Sie mich, Herr, aber wo ist Ihr Schwert? Es ist nicht sicher, die Stadt ohne eine Klingenwaffe zu verlassen. Man weiß nie, was im Dschungel passieren könnte!";
				link.l1 = "Verdammt, ich habe es völlig vergessen! Alles wurde weggenommen!";
				link.l1.go = "Store_noweapon";
				break;
			}
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("Fortfrance_town", "reload", "reload6_back");
			dialog.text = "Eine Arbeit? Hm. Ich denke, ich habe eine Arbeit, die du vielleicht willst. Mein Assistent ist verschwunden, er hat in meinem Lager gearbeitet. Er ist schon eine Woche lang weg und das ist verdammt ärgerlich, weil ich gezwungen bin, seine Pflichten zu erfüllen und ich habe keine Zeit\nBitte, finde diesen Idioten und finde heraus, warum zum Teufel er seine Arbeit aufgegeben hat. Oder noch besser - bringe ihn zurück zu mir. Ich werde dir tausend Stücke von Acht bezahlen.";
			link.l1 = "Gut, ich bin dabei. Sag mir seinen Namen und beschreib mir sein Aussehen. Hast du eine Idee, wo ich ihn suchen könnte?";
			link.l1.go = "Sharlie_storehelper_1";
			link.l2 = "Suche nach einem Mann, Gott weiß wo, für lächerliche tausend? Du machst wohl Witze!";
			link.l2.go = "Sharlie_storehelper_exit";
			npchar.quest.storehelper = "true";
		break;
		
		case "Sharlie_storehelper_exit":
			AddTimeToCurrent(2,0);
			LocatorReloadEnterDisable("Fortfrance_town", "reload10_back", false);// пу откр
			dialog.text = "He, Monsieur. Wer sucht hier einen Job, du oder ich? Wenn du nicht willst, zwing ich dich nicht. Schönen Tag noch.";
			link.l1 = "Hm... Think I'll go check the port authority; perhaps they'll offer something more substantial there.";
			link.l1.go = "exit";
		break;
		
		case "Sharlie_storehelper_1":
			dialog.text = "Der Name ist Gralam Lavois. Sein Aussehen? Fünfunddreißig Jahre alt, Bart und Schnurrbart, langer brauner Mantel, weißes Hemd. Oh, und er trägt immer diesen albernen Dreispitz, tut so als wäre er ein Admiral mit einem Anker im Arsch\nEr ist nicht in St. Pierre, ich habe die ganze Stadt durchsucht. Er muss im Dschungel sein oder bei Les Francois, wo er sich mit den Piraten, die dort herumlungern, versteckt.\nAndererseits, Er ist wahrscheinlich in der Piratensiedlung Le Francois, die im östlichen Teil unserer Insel liegt. Vielleicht plaudert er dort mit den Piraten, verbringt Zeit in der Taverne oder streitet sich mit dem örtlichen Händler im Laden.\nWie man nach Le Francois kommt? Verlassen Sie die Stadt durch die Stadttore in den Dschungel, an der Kreuzung nehmen Sie den linken Weg, dann folgen Sie der Straße bis Sie rechts abbiegen, und dann nehmen Sie den linken Durchgang zwischen den Felsen, und Sie werden Le Francois finden. Ich glaube nicht, dass Sie sich verlaufen werden.";
			link.l1 = "Gut. Ich werde anfangen zu suchen. Sobald etwas auftaucht, werde ich Sie sofort informieren.";
			link.l1.go = "exit";
			AddQuestRecord("SharlieA", "1");
			pchar.questTemp.Sharlie.Storehelper = "true";
			pchar.questTemp.Sharlie.Storehelper.Chance = rand(2);
			AddDialogExitQuestFunction("Sharlie_CreateStorehelper");
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload3_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload1_back");
		break;
		
		case "Sharlie_storehelper_2":
			DelLandQuestMark(npchar);
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload6_back");
			dialog.text = "Ach ja? Und wo ist er?";
			link.l1 = "Ich habe ihn in Le Francois gefunden. Er wird nicht mehr für dich arbeiten. Er hat auch eine Menge ziemlich salzige Dinge über dich gesagt... Möchtest du das hören?";
			link.l1.go = "Sharlie_storehelper_3";
		break;
		
		case "Sharlie_storehelper_3":
			dialog.text = "Nein. Erspar mir die Details... Was für ein Pech! Was mache ich jetzt ohne einen Assistenten?";
			link.l1 = "Mieten Sie jemand anderen. Oder ist das Problem wirklich so groß, wie Gralam es gesagt hat?";
			link.l1.go = "Sharlie_storehelper_4";
		break;
		
		case "Sharlie_storehelper_4":
			dialog.text = "Verdammtes Pech, in der Tat. Und was hat dieser Taugenichts gesagt?";
			link.l1 = "Nun, zum Anfang, er vergeudet offensichtlich nicht seine Zeit, he-he. Er sagte, dass niemand in ganz Saint Pierre sich bei Ihnen melden würde, weil... Sie Ihren Arbeitern nicht genug zahlen. Ja, übrigens, "+npchar.name+", du schuldest wie versprochen tausend Pesos.";
			link.l1.go = "Sharlie_storehelper_5";
		break;
		
		case "Sharlie_storehelper_5":
			AddMoneyToCharacter(pchar, 1000);
			dialog.text = "Bitte, nehmen Sie Ihr Geld. Ha! Zahlen nicht genug! Natürlich will niemand für mich arbeiten. Der Bastard hat sein Bestes getan, um schmutzige Gespräche zu verbreiten. Was kann ich tun? Ich kann nicht alles alleine machen!\nIch kann nicht schlafen gehen, bis ich jedes Stück Fracht gezählt habe, weil diese verdammt Arbeiter immer etwas stehlen. Nach der letzten Beladung fehlen mir fünf Fässer Rum. Ich bin sicher, dass die Arbeiter sie 'versehentlich' gegriffen haben...";
			link.l1 = "Nun, ich weiß nicht, was ich raten soll. Also gut, alles Gute. Es ist Zeit für mich zu gehen.";
			link.l1.go = "Sharlie_storehelper_6";
		break;
		
		case "Sharlie_storehelper_6":
			dialog.text = "Warte! Ich glaube, du kannst mir helfen. Wenn du in der Lage warst, diesen Bastard zu suchen, könntest du vielleicht auch...";
			link.l1 = "Und was könnte ich wohl tun, wenn niemand in dieser Stadt Ihnen glaubt? Ich bin neu hier und...";
			link.l1.go = "Sharlie_storehelper_7";
		break;
		
		case "Sharlie_storehelper_7":
			dialog.text = "Lassen Sie mich ausreden, Herr. Sie waren bereits in Le Francois. Ich möchte, dass Sie erneut dorthin gehen und versuchen, einen Mitarbeiter für mich zu finden. Vielleicht hat Gralam meinen Ruf in dieser Piratenhölle noch nicht vollständig ruiniert. Die Arbeit ist einfach - Fracht zählen und auf die Hafenarbeiter achten, um Diebstahl zu verhindern. Manchmal meine Arbeit hier statt mir zu erledigen, während ich weg bin, natürlich gegen eine zusätzliche Gebühr. Sagen Sie ihnen, dass ich ein Zimmer im Laden zum Wohnen und fünfhundert Stücke von acht pro Woche anbiete. Monsieur, ich wollte mein Geschäft erweitern und es läuft endlich gut, ich brauche einen Assistenten! Übrigens, es ist am besten, den örtlichen Wirt, Cesare Craig, um Hilfe bei der Suche nach einem Arbeiter zu bitten. Dieser Schurke wird Ihnen sicherlich helfen, wenn auch nicht kostenlos, Personen zu finden, die daran interessiert wären, für mich zu arbeiten.";
			link.l1 = "Hm. Ich kann es versuchen, obwohl ich mir nicht sicher bin... Wie viel wirst du mir für die Arbeit bezahlen?";
			link.l1.go = "Sharlie_storehelper_8";
		break;
		
		case "Sharlie_storehelper_8":
			dialog.text = "Das wird davon abhängen, welchen Arbeiter Sie einstellen können. Je besser er sich herausstellt, desto mehr werde ich Ihnen für Ihre Bemühungen zahlen. Das ist fair, oder?";
			link.l1 = "Glauben Sie nicht, dass Sie mich dazu zwingen, blind zu fahren? Wie soll ich wissen, wie Sie einen Arbeiter bewerten? Sie könnten jeden als schlecht einstufen oder...";
			link.l1.go = "Sharlie_storehelper_9";
		break;
		
		case "Sharlie_storehelper_9":
			dialog.text = "Herr! Es mag durchaus richtig sein, mich ein wenig geizig zu nennen, aber niemand könnte mich unehrlich nennen! Wenn ich Ihnen sage, ich werde für Ihre Bemühungen bezahlen, je nachdem, wie es ausgeht, dann meine ich das auch. Sehen Sie es auch aus meiner Sicht. Sie könnten mir hier vielleicht einen faulen Zigeuner bringen, der nicht nur herumlungern und nichts tun würde, sondern mich möglicherweise sogar nachts ausrauben!";
			link.l1 = "In Ordnung. Ich stimme zu. Ich nehme Ihr Wort, "+npchar.name+". Ich werde sicher keine Zigeuner mitbringen.";
			link.l1.go = "Sharlie_storehelper_10";
		break;
		
		case "Sharlie_storehelper_10":
			DialogExit();
			SetLaunchFrameFormParam("Back to Le Francois...", "Reload_To_Location", 0, 3.0);
			SetLaunchFrameReloadLocationParam("LeFransua_tavern", "reload", "reload1", "SharlieA_TeleportLF");
			LaunchFrameForm();
		break;
		
		case "Sharlie_storehelper_11":
			dialog.text = "Haben Sie einen Arbeiter für mich gefunden? Wunderbar. Lassen Sie mich mit ihm sprechen, kommen Sie in einer Stunde zurück für Ihre Belohnung.";
			link.l1 = "In Ordnung. Ich komme in einer Stunde zurück.";
			link.l1.go = "Sharlie_storehelper_12";
			DelLandQuestMark(npchar);
		break;
		
		case "Sharlie_storehelper_12":
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Sharlie.Storehelper = "final";
			DialogExit();
			SetLaunchFrameFormParam("One hour passed...", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0); //крутим время
			RecalculateJumpTable();
			AddQuestRecord("SharlieA", "5");
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "Sharlie_storehelper_13":
			switch (int(pchar.questTemp.Sharlie.Storehelper.Quality))
			{
				case 0:
					AddMoneyToCharacter(pchar, 3000);
					dialog.text = "Ich bin ziemlich zufrieden mit dem Arbeiter, den du für mich gefunden hast, obwohl er mehr redet als handelt, aber mach dir keine Sorgen, ich werde ihm sein Geschwätz schon austreiben. Deine Belohnung sind dreitausend Achtstücke. Hier, nimm.";
					link.l1 = "Danke! Sagen Sie mir, Monsieur, wissen Sie, ob jemand anderes in der Stadt vielleicht Hilfe bei einer wichtigen Angelegenheit benötigen könnte?";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
				
				case 1:
					AddMoneyToCharacter(pchar, 5000);
					dialog.text = "Sie haben es geschafft, einen wirklich wertvollen Arbeiter zu finden! Er ist sogar besser als dieser Schurke Gralam. Ich bin sehr, sehr zufrieden, Herr. Hier, nehmen Sie Ihre Belohnung - fünftausend Achtstücke.";
					link.l1 = "Danke! Sagen Sie mir, Monsieur, wissen Sie, ob jemand anderes in der Stadt vielleicht Hilfe bei einer wichtigen Angelegenheit braucht?";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
				
				case 2:
					AddMoneyToCharacter(pchar, 4000);
					dialog.text = "Sie haben einen guten Arbeiter gefunden. Und obwohl er nicht alle Tricks des Handels kennt, bin ich sicher, dass er sie ohne große Schwierigkeiten meistern wird. Ich bin zufrieden mit Ihnen, Herr. Hier, nehmen Sie Ihre Belohnung - vier tausend Stücke von Acht.";
					link.l1 = "Danke! Sagen Sie, Monsieur, wissen Sie, ob sonst noch jemand in der Stadt Hilfe bei einer wichtigen Angelegenheit benötigen könnte?";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
			}
		break;
		
		case "Sharlie_storehelper_14a":
			LocatorReloadEnterDisable("Fortfrance_town", "reload10_back", false);// пу откр
			dialog.text = "Hmm... Vor kurzem habe ich den Hafenmeister gesehen, der ganz aufgebracht zur Hafenbehörde ging. Schau bei ihm vorbei, wer weiß, was passiert sein könnte.";
			link.l1 = "Ich werde genau das tun. Danke, Monsieur.";
			link.l1.go = "Sharlie_storehelper_14";
			DelLandQuestMark(npchar);
		break;
		
		case "Sharlie_storehelper_14":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
			CloseQuestHeader("SharlieA");
			
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload6_back");
			
			QuestPointerToLoc("fortfrance_town", "reload", "reload10_back");
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Nun, was soll ich sagen, prächtige Ohrringe. Ich kann Ihnen... mal sehen... vier tausend Achtstücke dafür geben. Ich bezweifle, dass Ihnen jemand mehr anbieten wird. Haben wir einen Deal?";
			link.l1 = "Abgemacht! Sie gehören dir.";
			link.l1.go = "Sharlie_junglejew_1";
			link.l2 = "Nein. Ich denke, ich werde diese Juwelen für mich behalten.";
			link.l2.go = "exit";
			npchar.quest.junglejew = "true";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info("You've given the earrings");
			RemoveItems(pchar, "jewelry25", 1);
			AddMoneyToCharacter(pchar, 4000);
			AddQuestRecord("SharlieE", "4");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
		break;
		
		case "Store_noweapon":
			dialog.text = "Das wird nicht ausreichen. Ich schlage vor, Sie suchen unseren Gouverneur auf und bitten um seine Hilfe.";
			link.l1 = "Danke für den Rat. Das ist es, was ich vorhabe zu tun.";
			link.l1.go = "exit";
		break;
		//<-- Бремя гасконца
	}
	UnloadSegment(NPChar.FileDialog2);
}
