// диалог официантки
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk1, bOk2;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Waitress.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			//--> Jason Цена чахотки
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") || SandBoxMode)
			{
				bOk1 = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win") || SandBoxMode;
				if (sti(pchar.rank) > 6 && npchar.location == "PortSpein_tavern" && !CheckAttribute(npchar, "quest.Consumption")  && bOk1)
				{
					dialog.text = "Was wünschen Sie, Señor? Es tut mir leid, ich bin nur...'schluchzt'... oh... Es tut mir leid.";
					link.l1 = "Warum seid Ihr so aufgebracht, meine Dame? Tränen auf so einem schönen Gesicht? Was ist passiert?";
					link.l1.go = "Consumption";
					break;
				}
			}
			//<-- Цена чахотки
			
			// Addon-2016 Jason, французские миниквесты (”ЊЉ) Џорт Џренс
			if (npchar.location == "PortPax_tavern" && CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin")
            {
				DelMapQuestMarkCity("PortPax");
				DelLandQuestMark(npchar);
				PlaySound("Voice\English\Enc_RapersGirl_1.wav");
				dialog.text = "Herr! Herr, hilfe! Mord!";
				link.l1 = "Hä? Wen ermorden? Wo? Ist das ein Witz, meine Liebe?";
				link.l1.go = "FMQP";
				break;
			}
			
			//--> Тайна Бетси Прайс
			if (npchar.location == "Villemstad_tavern" && CheckAttribute(pchar, "questTemp.TBP_BetsiPrice") && !CheckAttribute(pchar, "questTemp.TBP_BetsiPrice_Sex"))
			{
				bOk1 = CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && IsOfficer(characterFromId("Mary"));
				bOk2 = CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && IsOfficer(characterFromId("Helena"));
				if (bOk1 || bOk2)
				{
					switch (rand(1))
					{
						case 0:
							dialog.text = ""+pchar.name+"! Wie schön, dich wiederzusehen... Danke, dass du vorbeischaust... aber jetzt ist wohl nicht der beste Zeitpunkt für ein Gespräch. Komm zurück, wenn du allein bist. Dann können wir... privatere Dinge besprechen.";
							link.l1 = "Es ist immer schön, mit dir zu plaudern, aber ich muss jetzt los. Vielleicht sehen wir uns wieder.";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = ""+pchar.name+"... Ich dachte schon, du hättest den Weg zu unserer Taverne vergessen. Schade, dass du nicht allein bist. Ich hatte gehofft, wir könnten ungestört reden.";
							link.l1 = "Ich denke, das Schicksal wird uns noch eine Gelegenheit geben, in Ruhe zu sprechen.";
							link.l1.go = "exit";
						break;
					}
				}
				else
				{
					switch (rand(1))
					{
						case 0:
							dialog.text = ""+pchar.name+"! Ich wusste, du würdest mich nicht lange schmachten lassen. Ich will keine Minute mehr verlieren. Das Zimmer oben ist frei... nur für uns beide. Du wirst mich doch nicht abweisen?";
							link.l1 = "Du weißt, wie man mich verführt... Nun, ich habe keinen Grund zu widerstehen. Gehen wir?";
							link.l1.go = "TBP_BetsiPriceSex1";
							link.l2 = "Ich fürchte, ich habe heute wirklich wichtige Dinge zu erledigen. Aber ich verspreche dir, das nächste Mal mache ich es wieder gut.";
							link.l2.go = "exit";
						break;

						case 1:
							dialog.text = ""+pchar.name+"! Ich habe schon gedacht, du findest Gefallen daran, mich schmachten zu lassen. Du willst doch nicht einfach nur hier stehen bleiben, während es so viele angenehmere Arten gibt, die Zeit zu verbringen?";
							link.l1 = "Deinem Charme kann man einfach nicht widerstehen... Keine Zeit zu verlieren – ich gehe gleich nach oben.";
							link.l1.go = "TBP_BetsiPriceSex1";
							link.l2 = "Du bist wirklich verführerisch, Betsy... Aber leider muss ich jetzt woanders sein.";
							link.l2.go = "exit";
						break;
					}
				}
				link.l9 = "Ich möchte dir ein paar Fragen stellen.";
				link.l9.go = "quests";
				break;
			}
			//<-- Тайна Бетси Прайс
            NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.different.FackWaitress"))
			{
				if (pchar.questTemp.different == "FackWaitress_toRoom" || pchar.questTemp.different == "FackWaitress_toRoomUp")
				{
					dialog.text = "Ich habe dich gebeten, nach oben zu gehen. Bleib nicht hier und ziehe Aufmerksamkeit auf dich.";
					link.l1 = "Gut, ich gehe, will dich nicht in die Pfanne hauen...";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_noMoney" || pchar.questTemp.different == "FackWaitress_fighted")
				{
					dialog.text = "Ich bin neu hier, also bitte, lenken Sie mich nicht von meiner Arbeit ab. Ich kann mich immer noch nicht daran gewöhnen...";
					link.l1 = "Und wo ist die Kellnerin, die vor Ihnen hier gearbeitet hat? "+pchar.questTemp.different.FackWaitress.Name+", wie ich mich erinnere...";
					link.l1.go = "Love_IDN";
				}
				if (pchar.questTemp.different == "FackWaitress_facking")
				{					
					dialog.text = "Komm wieder, Süße. Wir könnten wieder Spaß haben. Wenn ich mehr freie Zeit hätte...";
					link.l1 = "Sicher werde ich, du warst großartig!";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_fackNoMoney")
				{					
					dialog.text = "Ich kenne dich nicht, also belästige mich nicht...";
					link.l1 = "Wo ist mein Geld?!!";
					link.l1.go = "Love_IDN_1";
				}
				break;
			}
		    switch (Rand(4))
			{
				case 0:
					dialog.text = "Entschuldigung, "+GetSexPhrase("schön","hübscher")+", Ich bin jetzt zu beschäftigt. Es ist eine gute Zeit für die Taverne, aber nicht für Gespräche!";
					link.l1 = "...";
					link.l1.go = "exit";
				break;

				case 1:
					dialog.text = "Bitte, Kapitän, kämpfen Sie nicht hier! Es ist harte Arbeit, diesen Ort sauber zu halten.";
					link.l1 = ""+GetSexPhrase("Hm... Ich wollte nicht mal.","Sehe ich aus wie ein Trunkenbold, der einen Streit sucht? Ich bin nur ein Mädchen, genau wie du, mach dir keine Sorgen.")+"";
					link.l1.go = "exit";
				break;

				case 2:
					if (hrand(1) == 0) // Addon-2016 Jason
					{
						dialog.text = ""+GetSexPhrase("Oh, Kapitän! Möchten Sie heute ein Bett mit mir teilen? Ich prahle nicht gerne mit mir selbst, aber...","Nehmen Sie Platz, Kapitän. Es ist immer eine Freude, einen echten Seewolf wie Sie zu treffen.")+"";
						link.l1 = "Schade, dass ich jetzt in Eile bin. Bis zum nächsten Mal!";
						link.l1.go = "exit";
						bool bOk = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) || (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) || npchar.city == GetLadyBethCity(); // 291112
						if (pchar.questTemp.different == "free" && !CheckAttribute(pchar, "questTemp.different.FackWaitress") && PChar.sex != "woman" && pchar.GenQuest.EncGirl != "HorseToTavern" && !bOk)
						{
							link.l2 = "Mit großem Vergnügen, Baby!";
							link.l2.go = "Love_1";
						}
					}
					else
					{
						dialog.text = "Nehmen Sie Platz, Kapitän. Probieren Sie unseren Rum, spielen Sie eine Runde Karten oder Würfel. Fühlen Sie sich wie zu Hause! Es ist immer ein Vergnügen, einen echten Seewolf wie Sie zu treffen.";
						link.l1 = "Danke dir, hübsche.";
						link.l1.go = "exit";
					}
				break;

				case 3:
					dialog.text = "Sprechen Sie mit dem Meister, wenn Sie etwas bestellen möchten. Er steht hinter dem Tresen.";
					link.l1 = "Danke für den Rat.";
					link.l1.go = "exit";
				break;

				case 4:
					dialog.text = "Wenn du dich ausruhen und deine Gesundheit verbessern möchtest - miete dir dann ein Zimmer. Die ganze Nacht in der Halle zu bleiben wird dir nicht viel helfen.";
					link.l1 = "Mein Dank.";
					link.l1.go = "exit";
				break;
			}			
			link.l9 = "Ich möchte Ihnen ein paar Fragen stellen.";
			link.l9.go = "quests";//(перессылка в файл города)
		break;
		
        case "Love_1":
			dialog.text = "Hör gut zu. Miete hier in der Taverne ein Zimmer. Geh hin und warte auf mich. Ich werde mich dort etwas später reinschleichen...";
			link.l1 = "Ha! Ich werde es erledigen, Liebling! Ich werde auf dich warten!";
			link.l1.go = "exit";
			pchar.questTemp.different = "FackWaitress_toRoom";
			SetTimerFunction("WaitressFack_null", 0, 0, 1); //освобождаем разрешалку на миниквесты на след. день
			//Шанс, что ограбят, если рендом выпадет на 0. он же делитель сколько она вытащит из кармана
			pchar.questTemp.different.FackWaitress.Kick = hrand(2); 
			pchar.questTemp.different.FackWaitress.Name = GetFullName(npchar); //запомним имя официантки
			pchar.questTemp.different.FackWaitress.City = npchar.city;
			//делаем клона официантки
			sld = GetCharacter(NPC_GenerateCharacter("WairessQuest", npchar.model, "woman", npchar.model.animation, 5, sti(npchar.nation), 3, false, "citizen"));
			sld.name = npchar.name;
			sld.lastname = npchar.lastname;
			sld.dialog.Filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "Waitress";	
			Pchar.quest.WaitressFack_inRoom.win_condition.l1 = "location";
			Pchar.quest.WaitressFack_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			Pchar.quest.WaitressFack_inRoom.function = "WaitressFack_inRoom";
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
		break;
		
        case "Love_IDN":
			dialog.text = "Sie arbeitet nicht mehr hier, sie hat sich zur Ruhe gesetzt... Es tut mir leid, ich habe eine Arbeit zu erledigen.";
			link.l1 = "Gut...";
			link.l1.go = "exit";
		break;
		
        case "Love_IDN_1":
			dialog.text = "Hör gut zu, lüsterner Idiot. Ich weiß nicht, wo dein Geld ist! Und wenn du weiter auf mir herumhackst, dann rufe ich die Wachen und du findest dich im Gefängnis wieder!";
			link.l1 = "Gut, keine Wachen sind nötig... So ein Narr...";
			link.l1.go = "Love_IDN_2";
		break;
		
        case "Love_IDN_2":
			dialog.text = "Genau, so ein Narr. Nächstes Mal wirst du klüger und anständiger sein.";
			link.l1 = "Ich werde es versuchen... (flüstert) Verdammte Hure...";
			link.l1.go = "exit";
		break;

		case "without_money":
			NextDiag.TempNode = "first time";
			dialog.text = "Hörst du mich?";
			link.l1 = "Ughh...";
			link.l1.go = "without_money_2";
		break;

		case "without_money_2":
			dialog.text = "Fühlst du dich schlecht? Hast du Kopfschmerzen?";
			link.l1 = "Verdammt... wo bin ich?";
			link.l1.go = "without_money_3";
		break;

		case "without_money_3":
			dialog.text = "Erinnerst du dich nicht? Sie haben dich ausgeraubt.";
			link.l1 = "Was? Oh... Mein Kopf... Wer würde es wagen?!";
			link.l1.go = "without_money_4";
		break;

		case "without_money_4":
			dialog.text = "Wie sollte ich das wissen? Sie stürmten herein, drohten zu töten, durchsuchten deine Taschen und gingen wieder.";
			link.l2 = "Ich sehe... Scheiße... Ich hätte gerne etwas Wasser... Danke.";
			link.l2.go = "exit";
		break;
		
		//--> Jason Цена чахотки
		case "Consumption":
			npchar.quest.Consumption = "true";
			dialog.text = "Nein, es ist nichts, Herr... danke für Ihre Freundlichkeit, aber ich... (weint)";
			link.l1 = "Jemand hat dich beleidigt? Beruhige dich, Hübsche, erzähl mir alles.";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "Nein, nein, Senor, es ist nichts. Verzeihen Sie mir meine mangelnde Zurückhaltung, es ist nur... Es ist mein Bruder, sie sagen, dass er tot ist, aber ich glaube es nicht. Ich weiß nicht, was ich glauben soll, aber ich fühle in meinem eigenen Herzen, dass er in großen Schwierigkeiten steckt. Und ich habe niemanden außer Angelo, nachdem unsere Eltern ... (weint)";
			link.l1 = "Ich verstehe, aber ich bitte Sie, sich zu beruhigen, bitte. Was ist mit Ihrem Bruder passiert?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			dialog.text = "Herr... bitte verstehen Sie mich nicht falsch, aber warum sollte sich so ein Kapitän um ein gewöhnliches und bescheidenes Mädchen aus der Taverne kümmern? Ich habe nicht einmal etwas, das ich Ihnen für Ihre Hilfe versprechen könnte... ";
			link.l1 = "Eigentlich hast du recht. Selbstlosigkeit ist nichts für mich, also sei stark, wir verlieren alle unsere Verwandten. C'est la vie, wie wir in Frankreich sagen...";
			link.l1.go = "exit";
			link.l2 = "Eine Frau kann immer einen Weg finden, einem Mann zu danken.... Ha-ha. Jetzt hör auf zu weinen und erzähl mir von deinem Problem.";
			link.l2.go = "Consumption_3_1";
			link.l3 = "Junge Señorita, ist Ihnen nicht bekannt, dass unsere Kirche uns lehrt, einander zu helfen? Ich werde versuchen, Ihnen zu helfen, wenn ich natürlich dazu in der Lage bin.";
			link.l3.go = "Consumption_3_2";
		break;
		
		case "Consumption_3_1":
			if(sti(pchar.reputation.nobility) > 36)
			{
				dialog.text = "War es ein 'Hinweis'? Entschuldigen Sie, es war mein Fehler, mit Ihnen zu sprechen! Auf Wiedersehen 'Caballero'...";
				link.l1 = "Wie du wünschst, Süße.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Nun denn... Zumindest bist du ehrlich in deinen Wünschen. Ich verspreche, dass wenn du Angelo findest oder mir sagst, was wirklich mit ihm passiert ist, du bekommst, was du gefragt hast...";
				link.l1 = "Liebe Senorita, es ist ein Vergnügen, Geschäfte mit Ihnen zu machen... Jetzt kommen wir direkt zur Geschichte Ihres Bruders.";
				link.l1.go = "Consumption_4";
				npchar.quest.Consumption.sex = "true";
			}
		break;
		
		case "Consumption_3_2":
			dialog.text = "Willst du mich veräppeln? Willst du mir wirklich kostenlos helfen?";
			link.l1 = "Nur ein schlechter Mann würde einem weinenden Mädchen nicht helfen. Mach dir keine Sorgen, ich möchte dir wirklich helfen. Was ist genau mit Angelo passiert?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Sehr gut, Senor. Mein Bruder, er... oh, es fällt mir nicht leicht, die Tränen zurückzuhalten, es tut mir so leid... Wir waren wirklich arm wegen meiner... Bescheidenheit bei der Arbeit vielleicht... Und Angelo fing an, mit den örtlichen Schmugglern zu arbeiten. Er dachte, dass sein kleines Fischerboot mehr Geld verdienen würde, wenn es etwas an den Zollbehörden vorbeischmuggeln würde.";
			link.l1 = "Um es mit einfacheren Worten zu sagen, dein Bruder ist ein Verbrecher geworden, richtig?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "Nein, senor, Sie verstehen nicht... er ist nicht so! Er hat es für mich getan! Um mich davon zu bewahren, hier nebenbei Geld zu verdienen... Sie wissen, was ich meine. Wir waren verschuldet und er hat es für meine Ehre und meine Seele getan. Und dann... wurde er erwischt. Es war kein großes Problem, ich habe sogar noch mehr Geld geliehen, um seine Freilassung zu bezahlen... Aber sie sagten, dass er gestorben ist.";
			link.l1 = "Sie haben gesagt? Wer hat gesagt? Und warum glaubst du ihnen nicht? Er starb im Gefängnis?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			dialog.text = "Ja. Als ich Geld brachte, um seine Freilassung zu bezahlen, sagte mir der Kommandant, dass Angelo an Schwindsucht gestorben sei. Stell dir vor! Er kam dort in guter Gesundheit an und starb zwei Wochen später direkt in diesen Kammern. Sie... sie ließen mich nicht einmal die Leiche sehen. Sie sagten, sie begruben Gefangene direkt an der Bucht in der Nähe der Festung, um eine Epidemie zu vermeiden.";
			link.l1 = "Eine Epidemie? Klingt sehr wahr. Also willst du einfach nicht daran glauben oder hast du ernsthaftere Gründe?";
			link.l1.go = "Consumption_7";
		break;
		
		case "Consumption_7":
			dialog.text = "Nein... Nein! (weint) Ich weiß, es klingt dumm, aber ich bin sicher, dass ich es wissen würde, wenn er gestorben wäre. Siehst du, Angelo war immer stark - ein echter Seemann. Aber es gibt noch eine Sache\nMein Großvater starb an Schwindsucht, als ich ein Kind war, und er, ein alter Mann, hatte jahrelang dagegen gekämpft! Ich weiß, wie es funktioniert, Schwindsucht tötet Menschen nicht in Tagen, glaub mir!";
			link.l1 = "Hm... Du hast mich auch zweifeln lassen, hier stimmt etwas ganz und gar nicht. Ich kann dir nichts versprechen, aber ich werde versuchen, mehr herauszufinden.";
			link.l1.go = "Consumption_8";
		break;
		
		case "Consumption_8":
			dialog.text = "Sogar ein einfaches Versprechen ist viel mehr, als ich erwartet habe! Sie sind so freundlich, senor! Ich werde hier warten!";
			link.l1 = "Oh, Jugend! So wechselhaft in Gefühlen ... würdest du mir freundlicherweise meine Hand zurückgeben, Schönheit, ich brauche sie noch ha-ha ... Sehr gut, dann werde ich mal suchen gehen.";
			link.l1.go = "Consumption_9";
		break;
		
		case "Consumption_9":
			DialogExit();
			npchar.dialog.filename = "Quest\LineMiniQuests\Consumption.c";
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Consumption = "begin";
			AddQuestRecord("Consumption", "1");
		break;
		//<-- Цена чахотки
		
		// Addon-2016 Jason, французские миниквесты (”ЊЉ) Џорт Џренс
		case "FMQP":
			dialog.text = "Nein, keine Witze! Oben! Zwei Schläger ermorden einen edlen Herrn! Helfen Sie ihm, Kapitän, Sie sind der einzige bewaffnete Mann hier!";
			link.l1 = "Lauf draußen, ruf die Wachen! Ich gehe nach oben!";
			link.l1.go = "FMQP_1";
			link.l2 = "Mein Liebling, du musst mich für einen Wächter gehalten haben. Rufe eine Patrouille im Falle eines Mordes.";
			link.l2.go = "FMQP_exit";
		break;
		
		case "FMQP_exit":
			dialog.text = "A-ah, Wachen! Helft mir!";
			link.l1 = "..., Freund.";
			link.l1.go = "FMQP_exit_1";
		break;
		
		case "FMQP_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
			LocatorReloadEnterDisable("Portpax_town", "reload4_back", true);
			SetFunctionTimerCondition("FMQP_Remove", 0, 0, 1, false);
		break;
		
		case "FMQP_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			pchar.quest.FMQP_room.win_condition.l1 = "locator";
			pchar.quest.FMQP_room.win_condition.l1.location = "Portpax_tavern";
			pchar.quest.FMQP_room.win_condition.l1.locator_group = "reload";
			pchar.quest.FMQP_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.FMQP_room.function = "FMQP_InRoom";
		break;
	}
}
