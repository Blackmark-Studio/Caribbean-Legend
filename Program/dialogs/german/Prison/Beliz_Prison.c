// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Sprich, ich höre zu";
			link.l1 = "Ich habe mich geirrt. Leb wohl.";
			link.l1.go = "Exit";
			// Калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "start")
			{
				link.l1 = "Ich habe von einer Bande von Dieben und Räubern gehört, die in der Nähe von Belize und in der Stadt selbst operieren.";
				link.l1.go = "caleuche";
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "know" && CheckAttribute(pchar, "questTemp.Caleuche.belizbandos") && GetQuestPastDayParam("questTemp.Caleuche.belizbandos") < 3)
			{
				link.l1 = "Ich kann Ihnen Informationen über die Bande geben.";
				link.l1.go = "caleuche_3";
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche.BelizRegard"))
			{
				link.l1 = "Welche Neuigkeiten über die Bande? Habt ihr sie in der Höhle gefasst?";
				link.l1.go = "caleuche_7";
			}
			// Путеводная звезда ==>
			if (CheckAttribute(pchar, "questTemp.PZ_Beliz_Komendant"))
			{
				link.l1 = "Die ganze Stadt scheint die Gefangennahme eines Piraten zu feiern. Kannst du mir mehr darüber erzählen?";
				link.l1.go = "PZ_Beliz_Komendant_1";
				DeleteAttribute(pchar, "questTemp.PZ_Beliz_Komendant");
			}
			// <== Путеводная звезда
		break;
		
		// Путеводная звезда ==>
		case "PZ_Beliz_Komendant_1":
			dialog.text = "Gerne! Das ist nicht irgendein Pirat - es ist dieser Schurke, Matthew Lutter.";
			link.l1 = "Jedermanns Glück läuft schließlich aus.";
			link.l1.go = "PZ_Beliz_Komendant_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Beliz_Komendant_2":
			dialog.text = "Sie sind nicht Englisch, und Sie sehen nicht wie ein Händler aus, also kann ich verstehen, warum Sie nicht so begeistert sind. Lutter hat diese Gewässer jahrelang terrorisiert, sowohl uns als auch die Dons angegriffen, aber öfter uns. Er hat es immer geschafft, unseren Küstenpatrouillen zu entkommen, indem er seine Korvette, die Möwe, segelte, die einst das schnellste Schiff im Archipel war. Wie er dazu kam, ein Kriegsschiff wie dieses zu kommandieren, weiß nur Gott.";
			link.l1 = "Also ist es wahr, dass er gegen einen Händler verloren hat? Auf einer Korvette? Klingt unglaublich.";
			link.l1.go = "PZ_Beliz_Komendant_3";
		break;
		
		case "PZ_Beliz_Komendant_3":
			dialog.text = "So seltsam es auch klingt, es ist wahr. Ein Händler, und noch dazu ein Spanier! Unsere Marine könnte ein oder zwei Dinge von ihm lernen. Kapitän Sotta, der erkannte, dass es kein Entkommen gab, bereitete sich auf die Schlacht vor...";
			link.l1 = "Ziemlich ungewöhnlicher Charakter, dieser Sotta.";
			link.l1.go = "PZ_Beliz_Komendant_4";
		break;
		
		case "PZ_Beliz_Komendant_4":
			dialog.text = "Vielleicht. Er hat sein Schiff so umgerüstet, dass es so viel Fracht wie möglich transportieren konnte, was eine Flucht unmöglich machte. Wissend, dass die Piraten hinter seiner Fracht her waren, tat er so, als ob er auf der Stelle treiben würde. Und dann...";
			link.l1 = "...er hat die Segel im richtigen Moment gehisst?";
			link.l1.go = "PZ_Beliz_Komendant_5";
			if (!CharacterIsHere("Longway"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
			}
		break;
		
		case "PZ_Beliz_Komendant_5":
			dialog.text = "Ha! Nein, er feuerte eine Breitseite mit Traubenhagel auf kürzeste Entfernung ab, als Lutter sich näherte, und dann entert er den Piraten selbst! Als er herausfand, wer Lutter war, übergab er ihn uns. Ein wahrer Held, ein Mann von Ehre!";
			link.l1 = "Es war nicht nur Ehre, die ihn antrieb - es muss eine Belohnung für das Fangen des Windbeutels gegeben haben.";
			link.l1.go = "PZ_Beliz_Komendant_6";
		break;
		
		case "PZ_Beliz_Komendant_6":
			dialog.text = "Manchmal stimmen Gewinn und gute Absichten überein. Aber ja, er wurde fürstlich belohnt. Seine Gnaden belud ihn mit kostbaren Gütern als Zeichen unserer Dankbarkeit der Stadt, bevor er in See stach.";
			link.l1 = "Ich wünschte, ich hätte ihn getroffen - Ich würde gerne seine Hand schütteln. Erzähl mir...";
			link.l1.go = "PZ_Beliz_Komendant_7";
		break;
		
		case "PZ_Beliz_Komendant_7":
			StartInstantDialog("Longway", "PZ_Beliz_Komendant_8", "Quest\CompanionQuests\Longway.c");
		break;
		// <== Путеводная звезда
		
		// Калеуче
		case "caleuche":
			dialog.text = "Ihre Quelle hat die Wahrheit gesagt. Diese Banditen sind für uns zu einer echten Plage geworden. Möchten Sie uns etwas über sie erzählen?";
			link.l1 = "Abgesehen davon, dass sie mir etwas Wichtiges gestohlen haben - eigentlich nichts. Ich hatte gehofft, dass du mir etwas über sie erzählen könntest. Vielleicht wurde einer von ihnen gefangen und ist jetzt bereit auszusagen...";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Es tut mir leid, Sie zu enttäuschen, Kapitän, aber ich habe keine Informationen über sie. Ich weiß nur, dass sie sich irgendwo im Dschungel verstecken und sie haben Verbündete in der Stadt, das ist alles. Jetzt, wenn Sie etwas Neues über sie erfahren, sagen Sie mir bitte sofort Bescheid.";
			link.l1 = "In Ordnung, Offizier. Das werde ich tun.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			DialogExit();
			AddQuestRecord("Caleuche", "10");
			pchar.questTemp.Caleuche.Bandos = "seek";
		break;
		
		case "caleuche_3":
			string sTime;
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 0) sTime = "in three days";
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 1) sTime = "on the day after tomorrow";
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 2) sTime = "tomorrow";
			dialog.text = "Sind Sie ernst, Kapitän? Sprechen Sie, ich bin ganz Ohr.";
			link.l1 = "Ich habe einen ihrer Informanten in der Stadt gefunden. Er hat mir erzählt, dass ihre Bande sich darauf vorbereitet, ein Schiff anzugreifen, das in der Bucht von Chetumal ankommen soll. Die Schurken versammeln sich "+sTime+" nachts in der Nähe einer Höhle nicht weit von Belize. Um dorthin zu gelangen, muss man einfach den linken Pfad an der Gabelung im Dschungel nehmen.";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "In der Höhle? Hervorragende Nachrichten. Ich werde einen Hinterhalt für diese Schurken vorbereiten lassen. Wenn Sie richtig liegen und Ihr Informant die Wahrheit gesagt hat, werden wir diese Bastarde fangen, und dann werde ich beim Gouverneur um eine Belohnung für Sie ersuchen.";
			link.l1 = "Danke! Ich werde dich besuchen, wenn alles vorbei ist.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "In Ordnung. Das ist gut.";
			link.l1 = "Bis bald, Offizier.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			DialogExit();
			AddQuestRecord("Caleuche", "15");
			pchar.questTemp.Caleuche.Bandos = "comendant";
			pchar.questTemp.Caleuche.BelizChance = hrand(3);
			SetFunctionTimerCondition("Caleuche_BelizRegard", 0, 0, 3, false); // таймер
		break;
		
		case "caleuche_7":
			if (sti(pchar.questTemp.Caleuche.BelizChance) < 3)
			{
				dialog.text = "Wir haben den Schurken einen herzlichen Empfang bereitet, ha-ha-ha! Wenn du nur ihre Gesichter hättest sehen können! Wir haben jeden gefangen genommen, einschließlich des Rädelsführers! Einige versuchten Widerstand zu leisten, aber sie wurden von unseren tapferen Soldaten ausgeschaltet.";
				link.l1 = "Ausgezeichnete Nachrichten, Offizier! Jetzt können die Bürger von Belize endlich ruhig schlafen.";
				link.l1.go = "caleuche_12";
			}
			else
			{
				dialog.text = "Hmm... Meine Soldaten haben die ganze Nacht auf sie in der Höhle gewartet, aber niemand ist aufgetaucht. Der Sergeant war wirklich wütend. Es ist gut, dass er dich noch nicht erwischt hat.";
				link.l1 = "Verdammte Axt! Das kann einfach nicht sein! In welcher Höhle habt ihr den Hinterhalt gelegt? Es gibt zwei davon!";
				link.l1.go = "caleuche_8";
			}
		break;
		
		case "caleuche_8":
			dialog.text = "Wo du mir gesagt hast. Bei dem rechten am Gabelung...";
			link.l1 = "ES IST DER LINKS! Links von der Gabel, ihr Trottel!";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Aber ich erinnere mich ganz genau, dass Sie 'nach rechts' gesagt haben.";
			link.l1 = "Ach du lieber Gott! Nach links! Ich sagte, NACH! LINKS! Du hast sie entkommen lassen und es war deine Schuld!";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			AddQuestRecord("Caleuche", "16");
			dialog.text = "Dann müssen Sie etwas unter Ihrer Nase gemurmelt haben. Ich höre ziemlich gut, wissen Sie.";
			link.l1 = "Gut, Offizier, ich werde nicht streiten. Ich wollte Ihnen helfen, aber man kann denen nicht helfen, die sich selbst nicht helfen können. Lebewohl.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Caleuche.BelizChance");
			DeleteAttribute(pchar, "questTemp.Caleuche.BelizRegard");
		break;
		
		case "caleuche_12":
			dialog.text = "Ich habe dem Gouverneur von Ihrer Rolle bei der Auslöschung der Bande berichtet. Er schätzte Ihren Beitrag sehr hoch ein und ermächtigte mich, Ihnen eine Belohnung zu überreichen: eine Geldprämie und eine Trophäen-Arkebuse.";
			link.l1 = "Danke dir!";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			Log_Info("You have received a chest with doubloons");
			Log_Info("You have received an arquebus");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Caleuche", "17");
			GiveItem2Character(pchar, "chest"); 
			GiveItem2Character(pchar, "mushket3"); 
			dialog.text = "Danke für den Dienst, Kapitän! Wenn nur alle unsere Bürger so gewissenhaft wären wie Sie, hätten wir das Verbrechen schon lange ein für alle Mal besiegt! Viel Glück wünsche ich Ihnen!";
			link.l1 = "Auf Wiedersehen, Offizier! Viel Glück bei Ihrem Dienst!";
			link.l1.go = "caleuche_11";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			OfficersReaction("good");
			ChangeCharacterNationReputation(pchar, ENGLAND, 8);
			AddCharacterExpToSkill(pchar, "Leadership", 300);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 200);//скрытность
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
