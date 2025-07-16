// Джино Гвинейли - алхимик
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			// --> Страж истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino1")
			{
				dialog.text = "Oh! Guten Tag, Herr. Wie sind Sie hierher gekommen?";
				link.l1 = "Guten Tag, Gino. Lass uns einander kennenlernen. Ich bin Kapitän "+GetFullName(pchar)+" und ich bin hier mit Johns Erlaubnis. Ich werde es klarstellen - ich brauche deine Hilfe, aber ich kann dir auch helfen.";
				link.l1.go = "guardoftruth_0";
				npchar.quest.meeting = "1";
				DelLandQuestMark(npchar);
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Oh! Guten Tag, Herr. Wie sind Sie hierher gekommen? Und wo ist John?";
				link.l1 = "Nun, nun... Und das ist also, wer sich immer hinter dieser geschlossenen Tür versteckt hat! Interessant... Über John... Er ist weggegangen. Und dieses Haus gehört jetzt mir. Aber keine Sorge. Lassen Sie uns einander kennenlernen, wer sind Sie und was machen Sie hier?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
				DelLandQuestMark(npchar);
			}
			else
			{
				// --> Страж истины
				if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "threeitems")
				{
					dialog.text = "Hallo, "+pchar.name+". Dein Gesicht verrät mir, dass du etwas Wichtiges gefunden hast. Hast du alle Komponenten des Wahrheitswächters gefunden?";
					link.l1 = "Genau! Ich habe alle drei Gegenstände bei mir: den Dolch, die Karte und den Kompass!";
					link.l1.go = "guardoftruth_34";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino")
				{
					dialog.text = "Hallo, "+pchar.name+". Was ist passiert? Du hast einen merkwürdigen Ausdruck im Gesicht...";
					link.l1 = "Ich habe etwas Wichtiges mit dir zu besprechen, Gino. Es ist groß.";
					link.l1.go = "guardoftruth";
					break;
				}
				// Ксочитэм
				if (CheckAttribute(pchar, "questTemp.Ksochitam") && pchar.questTemp.Ksochitam == "begin")
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". Ja, ich erinnere mich, zwei Tage sind vergangen und du willst etwas über den Hüter der Wahrheit wissen, habe ich recht?";
					link.l1 = "Ja, das bist du! Hast du etwas ausgraben können?";
					link.l1.go = "ksochitam";
					break;
				}
				//--> Португалец
				if (CheckAttribute(pchar, "questTemp.Portugal.Nomoney"))
				{
					dialog.text = "Haben Sie 5 000 Pesos mitgebracht, "+pchar.name+"?";
					if (sti(pchar.money) >= 5000)
					{
						link.l1 = "Sicher. Hier, nimm das Geld und kaufe alles, was du brauchst.";
						link.l1.go = "Portugal_3";
						SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 1, false);
						DeleteAttribute(pchar, "questTemp.Portugal.Nomoney");
						pchar.quest.Portugal_Ill1.over = "yes";
						pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
						pchar.quest.Portugal_Ill.win_condition.l1.date.hour  = sti(GetTime());
						pchar.quest.Portugal_Ill.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
						pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
						pchar.quest.Portugal_Ill.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
						pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";
					}
					else
					{
						link.l1 = "Leider habe ich im Moment das Geld nicht bei mir.";
						link.l1.go = "Portugal_nomoney";
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal.Die"))
				{
					dialog.text = "Ach, "+pchar.name+", Es tut mir sehr leid - der Patient ist tot. Er wurde plötzlich schlechter und starb sehr schnell.";
					link.l1 = "Zu schade... Möge Gott seiner Seele gnädig sein!";
					link.l1.go = "exit";
					DeleteAttribute(pchar, "questTemp.Portugal.Die");
					pchar.quest.Remove_Avendel.win_condition.l1 = "Location_Type";
					pchar.quest.Remove_Avendel.win_condition.l1.location_type = "town";
					pchar.quest.Remove_Avendel.function = "RemoveAvendelnDoc";
					AddQuestRecord("Portugal", "6");
					CloseQuestHeader("Portugal");
					pchar.questTemp.Portugal = "end";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToAntigua")
				{
					dialog.text = "Hallo, "+pchar.name+". Ist etwas passiert? Du siehst sehr besorgt aus...";
					link.l1 = "Gino, ich habe eine ungewöhnliche Bitte an dich! Auf meinem Schiff ist ein Mann mit hohem Fieber. Er ist deliriert und bewusstlos... kannst du ihm helfen?";
					link.l1.go = "Portugal";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Portugal_wait")
				{
					dialog.text = ""+pchar.name+", Ich warte auf den Patienten. Beeilen Sie sich, je schneller Sie ihn hierher bringen, desto höher ist die Chance, dass ich ihn retten kann.";
					link.l1 = "Ja, ja, er wird sofort hierher gebracht.";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentStart")
				{
					dialog.text = "Sie haben ihn gerade rechtzeitig gebracht, "+pchar.name+". Er ist in kritischem Zustand, doch es besteht noch eine Chance.\nKapitän, mir gehen die Zutaten aus und wir haben keine Zeit, sie im Dschungel zu sammeln. Ich muss sie alle von den örtlichen Kräuterkundigen für 5 000 Pesos kaufen. Können Sie die Summe bereitstellen?";
					if (sti(pchar.money) >= 5000)
					{
					link.l1 = "Sicher. Hier, nimm das Geld und kauf alles, was du brauchst.";
					link.l1.go = "Portugal_3";
					SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 1, false);
					}
					else
					{
						link.l1 = "Leider habe ich gerade kein Geld.";
						link.l1.go = "Portugal_nomoney";
						pchar.quest.Portugal_Ill.over = "yes";
						pchar.quest.Portugal_Ill1.win_condition.l1 = "Timer";
						pchar.quest.Portugal_Ill1.win_condition.l1.date.hour  = sti(GetTime());
						pchar.quest.Portugal_Ill1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
						pchar.quest.Portugal_Ill1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
						pchar.quest.Portugal_Ill1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
						pchar.quest.Portugal_Ill1.function = "Portugal_ToAntiguaOver";//не принесёт через 1 день - Португальцу капут
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentCurrent")
				{
					dialog.text = "Ich habe jetzt nichts zu sagen, "+pchar.name+". Ich kämpfe um das Leben des Patienten. Es gibt noch etwas Hoffnung. Kommen Sie später zu mir, ich vermute, dass ich Ihnen bald etwas Konkreteres sagen kann.";
					link.l1 = "Gut, Gino, ich komme später wieder.";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentFinish")
				{
					pchar.quest.Portugal_Ill.over = "yes";
					dialog.text = "Ich habe Neuigkeiten,"+pchar.name+". Ich werde nicht sagen, dass Ihr Mann in Ordnung ist, aber er lebt. Die Krankheit weicht zurück und es gibt Fortschritte zu sehen. Ehrlich gesagt, habe ich nicht erwartet, dass meine Tränke ihm so gut helfen würden.";
					link.l1 = "Das sind großartige Nachrichten, Gino, aber sag mir, wann werde ich ihn mitnehmen können? Wir haben einen weiten Weg zu segeln und die Uhr tickt.";
					link.l1.go = "Portugal_4";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentComplete")
				{
					dialog.text = "Guten Tag, Kapitän. Schön, Sie zu sehen.";
					link.l1 = "Wie geht es unserem Patienten, Gino?";
					if (GetQuestPastDayParam("questTemp.Portugal_threedays") > 2) link.l1.go = "Portugal_9";
					else link.l1.go = "Portugal_threedays";
					break;
				}
				// <--Португалец
				dialog.text = "Guten Tag, Kapitän. Wie geht es Ihnen? Brauchen Sie meine Hilfe?";
				if (!CheckAttribute(npchar, "quest.rome"))
				{
					link.l1 = "Ja. Gino, ich nehme an, dass du ein gelehrter Mann bist und vielleicht sogar Latein verstehst...";
					link.l1.go = "rome";
				}
				if (CheckCharacterItem(pchar, "chemistry"))
				{
					link.l2 = "Ich habe etwas anderes. Ein kleines Geschenk für dich. Hier, schau dir dieses Buch an.";
					link.l2.go = "chemistry";
				}
				if (CheckAttribute(npchar, "quest.colt") && CheckCharacterItem(pchar, "pistol7"))
				{
					link.l2 = "Ja, Gino. Ich möchte dir diese Pistole zeigen. Hast du jemals so etwas gesehen?";
					link.l2.go = "colt";
				}
				if (CheckAttribute(npchar, "quest.sample") && CheckCharacterItem(pchar, "pistol7") && CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
				{
					link.l2 = "Ich habe Ihnen ein Beispiel für die Ladung meiner Pistole mitgebracht.";
					link.l2.go = "colt_1";
				}
				if (CheckAttribute(npchar, "quest.cartridge"))
				{
					link.l2 = "Was ist mit den Anklagen für die Pistole? Hast du schon irgendwelche Hinweise?";
					link.l2.go = "cartridge";
				}
				// Addon 2016-1 Jason Пиратская линейка
				if (CheckAttribute(pchar, "questTemp.Mtraxx.Gord"))
				{
					link.l3 = "Gino, ich habe das mir unbekannte Wort 'gord' in einem Kapitänslogbuch gefunden. Weißt du, was es bedeutet?";
					link.l3.go = "mtraxx";
				}
				link.l9 = "Guten Tag, Gino. Mir geht es gut, keine Hilfe ist nötig. Ich wollte nur nach dir sehen und ein bisschen plaudern.";
				link.l9.go = "exit";	
			}
			NextDiag.TempNode = "First time";
		break;

		case "meeting":
			pchar.questTemp.HWIC.Jino = "true"; // Addon 2016-1 Jason Пиратская линейка
			dialog.text = "Mein Name ist Gino. Gino Gvineili. Ich bin ein Wissenschaftler. Meine Aufgabe ist es, Pulver, Mischungen und andere Medikamente für Herrn Murdock herzustellen. Aber seit er weg ist...";
			link.l1 = "Nun, ich bin "+GetFullName(pchar)+". Ein Kapitän meines eigenen Schiffes. Also, du bist also ein Alchemist?";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Nicht nur ein Alchemist, sondern auch ein Arzt. Ich besitze ziemlich viel Wissen über Medizin. Ich kenne viele Dinge über heilende Kräuter und kann daraus Mixturen und Tränke brauen. Aber Chemie ist meine Berufung, ich experimentiere viel und einige meiner Erfindungen könnten Personen wie Ihnen helfen. \nIch kenne Latein, Französisch, Englisch und Italienisch. Meine Hilfe wird unverzichtbar sein, wenn Sie planen, eine Apotheke wie Herr Murdock zu führen...";
			link.l1 = "Ahoi! Es ist nicht jeden Tag, dass man einen so gebildeten Mann trifft. Die Apothekerei ist sicherlich fein, aber ich bin ein Seemann...hm, das klingt sogar für mich seltsam... wie auch immer, ich bin sicher, dass wir Freunde werden, Gino. Du kannst hier weiterleben und deine Wissenschaftssachen machen...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "";
			link.l1 = "Und wenn ich jemals Hilfe von einem Alchemisten, Heiler oder Wissenschaftler brauche - werde ich wissen, wen ich fragen soll... Sag mir, warum lebst du immer drinnen? Gehst du nicht manchmal raus?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Ich gehe nur nach draußen, wenn ich Zutaten oder Kräuter für meine Experimente kaufen muss. Ich lebe gerne alleine, das ist meine Art. Ich habe mein Leben der Wissenschaft gewidmet und finde kein Interesse am gewöhnlichen Leben. Bücher, Schriften, Reagenzgläser, Kolben... \nHerr Murdock hat mir diese Möglichkeit im Austausch dafür geboten, dass ich ihm helfe, Drogen herzustellen.";
			link.l1 = "Jetzt wirst du noch mehr Zeit haben, Gino. Aber du wirst etwas von der Zeit für dein Experiment aufgeben müssen, falls ich deine Hilfe brauche, einverstanden?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Sicher, Kapitän. Ich werde Sie Kapitän nennen, "+GetAddress_Form(NPChar)+", wenn es Ihnen nichts ausmacht? Ich werde all meine Forschungen hinterlassen, falls Sie meine praktischen Fähigkeiten oder theoretischen Kenntnisse benötigen.";
			link.l1 = "Prächtig. Ich bin froh, dass wir uns so schnell verstanden haben. Mach dir keine Sorgen um deine Ausgaben, ich oder mein Zahlmeister werden dir von Zeit zu Zeit angemessene Summen hinterlassen.";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Danke, Kapitän. Ich brauche nicht viel... Kapitän, ich habe eine Idee... warum lernen Sie nicht einige Alchemie-Fähigkeiten? Es könnte Ihnen wirklich nützlich sein.";
			link.l1 = "Hm. Wie mein Bruder mir einmal sagte - sei nicht zimperlich, wenn es darum geht, zu lernen, wie man Dinge mit den eigenen Händen macht. Also sicher, warum nicht. Was kannst du mir zeigen?";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "Nun, sicherlich wirst du nicht in der Lage sein, Eisen in Gold zu verwandeln, es ist unmöglich... noch, aber du kannst lernen, wie man Zutaten nach Anweisungen mischt, um Tränke oder andere nützliche Gegenstände als Ergebnis zu erhalten. Hier, nimm diese Tasche. Sie enthält alles, was der Anfänger Alchemist brauchen wird. Reagenzgläser, Flaschen, Retorten, Destillierapparate, Spatel, Glasröhren, ein Brenner und so weiter...";
			link.l1 = "Faszinierend!";
			link.l1.go = "meeting_7";
		break;
		
		case "meeting_7":
			Log_Info("You have received an alchemist's kit");
			GiveItem2Character(pchar, "alchemy_tool");
			PlaySound("interface\important_item.wav");
			dialog.text = "Sie müssen ein Rezept kennen, um einen Trank oder einen Gegenstand herzustellen. Rezepte können bei Händlern gekauft oder überall gefunden werden. Sobald Sie ein Rezept studiert haben, sollten Sie alle benötigten Zutaten sammeln und genau das tun, was dort geschrieben steht.\n Benutzen Sie Ihre Alchemiewerkzeuge, finden oder kaufen Sie Mörser und Stößel, suchen Sie einen Tiegel, ach, ich besitze keinen zusätzlichen, um ihn Ihnen zu geben. Kräuter, Geister, Tränke, Mineralien, Müll - alles ist gut, vorausgesetzt, Sie haben das richtige Rezept und die Werkzeuge.";
			link.l1 = "Ich verstehe. Ich werde versuchen, in meiner Freizeit etwas zu mixen. Danke, Gino! Kannst du mir ein einfaches Rezept geben? Etwas, um anzufangen? ";
			link.l1.go = "meeting_8";
		break;
		
		case "meeting_8":
			dialog.text = "Ich habe keine einfachen... aber hier, nimm dieses Rezept für ein Gegengift. Ich nehme an, dass du diese Aufgabe bewältigen kannst. Nimm es.";
			link.l1 = "Dankbarkeit! Ich werde es lernen. Auf Wiedersehen jetzt, Gino! Pass auf mein Haus auf, ich befürchte, dass ich diesen Ort nicht sehr oft besuchen werde, also bist du nicht nur in deinem Zimmer, sondern auch im Rest des Gebäudes willkommen.";
			link.l1.go = "meeting_9";
		break;
		
		case "meeting_9":
			DialogExit();
			GiveItem2Character(pchar, "recipe_potion4"); // belamour legendary edition
			Log_Info("You have received an antidote recipe");
			PlaySound("interface\notebook.wav");
			Log_Info("You need to have the Alchemy skill in order to craft potions, amulets and items!");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "rome":
			dialog.text = "Ja, Kapitän, ich kenne die Sprache der alten Römer. Jeder Wissenschaftler, insbesondere ein Heiler oder Alchemist, muss Latein können. Brauchen Sie meine Lateinkenntnisse?";
			link.l1 = "Ja. Gino, halte mich nicht für einen Narren, aber... nun, wie soll ich es erklären...";
			link.l1.go = "rome_1";
		break;
		
		case "rome_1":
			dialog.text = "Sprechen Sie, wie es ist, Kapitän. Seien Sie nicht schüchtern.";
			link.l1 = "Gut. Könnten Sie für mich eine Liste mit gelehrten lateinischen Aphorismen erstellen? Sehen Sie, es gibt... einen Mann, der gerne mit seiner 'Gelehrsamkeit' prahlt und manchmal verwendet er diese lateinischen Phrasen, um mir meine Unwissenheit im Vergleich zu ihm zu zeigen. Etwas wie... 'pasem-bellum'...";
			link.l1.go = "rome_2";
		break;
		
		case "rome_2":
			dialog.text = "'Si vis pacem, para bellum', meinst du das?";
			link.l1 = "Ja, ja. Ich möchte sie lernen, um meinen arroganten Br... meinen Freund zu schlagen.";
			link.l1.go = "rome_3";
		break;
		
		case "rome_3":
			AddQuestRecordInfo("Rome", "1");
			dialog.text = "Es ist nichts Seltsames oder Beschämendes an Ihrer Bitte, Kapitän. Die Aphorismen der Alten, die in die Geschichte eingegangen sind, zu kennen, macht Sie zu einem gebildeten Mann. Hier, nehmen Sie diesen Text. Es ist das, was Sie gefragt haben.";
			link.l1 = "Danke, Gino! Ich schätze es! Ich werde es in meiner Freizeit lesen...";
			link.l1.go = "exit";
			npchar.quest.rome = true;
			NextDiag.TempNode = "First time";
		break;
		
		case "chemistry":
			RemoveItems(pchar, "chemistry", 1);
			Log_Info("You have given Lavoisier's chemistry textbook");
			dialog.text = "Zeig mir... (liest) Unmöglich! Ein 'kleines Geschenk' sagst du? Dieses Buch ist unbezahlbar! Wo hast du es her?! Das ist... ein echter Schatz!";
			link.l1 = "Ich freue mich, dass es Ihnen gefällt.";
			link.l1.go = "chemistry_1";
		break;
		
		case "chemistry_1":
			dialog.text = "(Lesend) Unglaublich! Ich habe noch nie davon gehört... und das? Ich verstehe hier kein Wort... aber das werde ich, verdammt noch mal! Oh, bald wird die Arbeit in meinem Labor brodeln! "+pchar.name+", du realisierst nicht einmal, WAS du mir gegeben hast...";
			link.l1 = "Warum nicht? Ich tue es. Ein wissenschaftliches Buch für einen Wissenschaftler...";
			link.l1.go = "chemistry_2";
		break;
		
		case "chemistry_2":
			dialog.text = "Aber wer ist der Autor dieses Wunders? Antoine-Laurent de Lavoisier, Frankreich... Noch nie von ihm gehört. Aber warte! Wie ist das möglich! Das Druckjahr ist 1789? Aber wie...";
			link.l1 = "Ich weiß auch nicht, warum dieses Jahr darauf geschrieben steht. Nun, vielleicht weiß ich es doch. Aber ich rate Ihnen, nicht zu viel darüber nachzudenken. Das Buch ist nützlich und das ist alles, was zählt.";
			link.l1.go = "chemistry_3";
		break;
		
		case "chemistry_3":
			dialog.text = "Es ist vielversprechend ohne Maß und das Jahr muss ein Druckfehler sein... Was auch immer. Vielen Dank, Kapitän!";
			link.l1 = "Du bist willkommen, Gino. Es gehört alles dir.";
			link.l1.go = "exit";
			if (CheckCharacterItem(pchar, "pistol7"))
			{
				link.l1 = "Das ist nicht alles, Gino. Ich will dir diese Pistole zeigen. Hast du jemals so etwas gesehen?";
				link.l1.go = "colt";
			}
			npchar.quest.colt = true;
		break;
		
		case "colt":
			dialog.text = "Ich bin kein Büchsenmacher, aber ich werde mal schauen... nein, so etwas habe ich noch nie gesehen. Warum fragst du?";
			link.l1 = "Diese Pistole ist mächtig und zerstörerisch, aber es werden spezielle Ladungen benötigt, um sie zu benutzen. Nichts anderes würde funktionieren. Und ich habe keine Ahnung, wie man mehr Runden dafür macht. Also kam ich hierher um deinen Rat zu suchen.";
			link.l1.go = "colt_1";
		break;
		
		case "colt_1":
			dialog.text = "Haben Sie mindestens eine Runde, um sie mir als Beispiel zu zeigen? Wenn nicht, dann befürchte ich, dass ich nicht in der Lage sein werde zu helfen.";
			if (CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
			{
				link.l1 = "Ich mache es. Die Ladung besteht aus zwei Teilen: der Runde selbst mit einer Kugel und diesem Ding, das das Pulver explodiert.";
				link.l1.go = "colt_2";
			}
			else
			{
				link.l1 = "So ein Versagen! Was für eine Schande! Gut, vielleicht finde ich mehr und bringe sie dir.";
				link.l1.go = "exit";
				npchar.quest.sample = true;
			}
			DeleteAttribute(npchar, "quest.colt");
		break;
		
		case "colt_2":
			RemoveItems(pchar, "pistol7", 1);
			RemoveItems(pchar, "GunCap_colt", 1);
			RemoveItems(pchar, "shotgun_cartridge", 1);
			Log_Info("You have given a revolver's cartridge");
			Log_Info("You have given a capsule");
			PlaySound("interface\important_item.wav");
			dialog.text = "Interessant! Das sieht einfach aus, es ist Pulver drin, eine Kugel kommt von oben rein, aber es sieht ein bisschen seltsam aus. Und dieses 'Ding'... hm. Pulver explodiert nicht ohne es, richtig? Neugierig... Schau, Kapitän, überlass mir all das: die Pistole und die Ladungen. Komm in einem Monat wieder zu mir, ich brauche Zeit, um das herauszufinden.";
			link.l1 = "Großartig! Versuche zu verstehen, wie es funktioniert, ich möchte wirklich diese Pistole abfeuern.";
			link.l1.go = "colt_3";
		break;
		
		case "colt_3":
			dialog.text = "Das Hauptproblem besteht darin herauszufinden, woraus diese Substanz, die das Pulver explodieren lässt, besteht. Dieses Buch wird nützlich sein. Ich werde versuchen, dahinter zu kommen.";
			link.l1 = "Gut. Lebewohl, Gino!";
			link.l1.go = "colt_4";
		break;
		
		case "colt_4":
			DialogExit();
			DeleteAttribute(npchar, "quest.sample");
			SetFunctionTimerCondition("Colt_Timer", 0, 0, 30, false); // таймер
		break;
		
		case "cartridge":
			dialog.text = "Ja, ich habe herausgefunden, aus was die Ladungen für die Pistole bestehen. Ich muss dem Buch, das Sie mir geschenkt haben, Anerkennung zollen. Ohne dieses wäre es nicht möglich gewesen. Aber ich muss Sie warnen, Kapitän, es wird nicht einfach sein, Patronen und Kapseln für diese Waffe zu erstellen.";
			link.l1 = "Kapseln?";
			link.l1.go = "cartridge_1";
		break;
		
		case "cartridge_1":
			dialog.text = "Die Kapsel ist dieses 'Ding', das, wie du gesagt hast, das Pulver explodiert. Aber fangen wir von vorne an. Bist du bereit?";
			link.l1 = "Ja! Ich höre Ihnen sehr aufmerksam zu.";
			link.l1.go = "cartridge_2";
		break;
		
		case "cartridge_2":
			AddQuestRecordInfo("Recipe", "shotgun_bullet");
			SetAlchemyRecipeKnown("shotgun_bullet");
			dialog.text = "Also, zuerst musst du eine spezielle Kugel herstellen. Gewöhnliche Kugeln funktionieren nicht. Sie muss eine besondere konische Form haben. Du musst eine Form für solche Kugeln finden, die Kugelform, wie ich sie genannt habe. Nimm gewöhnliche Bleikugeln, schmelze sie in einem Tiegel und gieße das geschmolzene Blei in die Kugelform. Gefriere diesen Guss und nimm die fertige Kugel heraus.";
			link.l1 = "Und wo kann ich eine solche Kugelgussform finden?";
			link.l1.go = "cartridge_3";
		break;
		
		case "cartridge_3":
			dialog.text = "Ich weiß es nicht, Kapitän. Ich bin ein Alchemist, kein Schmied. Nehmen Sie diese Kugel als Beispiel, vielleicht finden Sie heraus, was zu tun ist.";
			link.l1 = "Gut. Mach weiter...";
			link.l1.go = "cartridge_4";
		break;
		
		case "cartridge_4":
			AddQuestRecordInfo("Recipe", "shotgun_cartridge");
			SetAlchemyRecipeKnown("shotgun_cartridge");
			dialog.text = "Dann musst du einen Behälter für das Pulver machen. Dort injizierst du die Kugel. Ich habe eine schöne Anleitung für dich geschrieben. Lies sie sorgfältig durch und probiere es aus.";
			link.l1 = "Gut...";
			link.l1.go = "cartridge_5";
		break;
		
		case "cartridge_5":
			AddQuestRecordInfo("Recipe", "GunCap_colt");
			SetAlchemyRecipeKnown("GunCap_colt");
			dialog.text = "Nun müssen wir die Kapseln besorgen. Du wirst ein sehr dünnes Kupferblech benötigen - fertige es selbst aus einem Kupferklumpen. Schnitze Kreise hinein, die genauso groß sind wie die Runden. Dann füge Knallsilber mit Wachs in sie ein.";
			link.l1 = "Blitzendes Silber? Was ist das?";
			link.l1.go = "cartridge_6";
		break;
		
		case "cartridge_6":
			dialog.text = "Ich wusste selbst nichts davon, ich habe das Geheimnis aus deinem Buch gelernt. Es handelt sich um ein weißes Pulver, das aus Silber, Geist und Salpetersäure hergestellt werden kann. Es explodiert leicht durch Reiben oder Schütteln, weshalb es sich gut zum Abfeuern des Schießpulvers in deinen Pistolenrunden eignet. Eine unangenehme Sache, es ist während meiner Tests zweimal explodiert, bis ich das Rezept gefunden habe.";
			link.l1 = "Ich hatte Glück, dieses Buch bei mir zu haben!";
			link.l1.go = "cartridge_7";
		break;
		
		case "cartridge_7":
			dialog.text = "Sei äußerst vorsichtig, dieses Zeug ist explosiv wie die Hölle! Ich könnte selbst etwas herstellen, aber die Lagerung von Knallsilber ist zu gefährlich, es ist lebenswichtig, dass du es direkt nach seiner Herstellung in die Kapseln gibst. Ich kann keine Kupferkapseln herstellen, ich bin kein Schmied, wie ich dir schon früher gesagt habe.";
			link.l1 = "Gut. Gib mir das Rezept, ich werde es selbst lernen.";
			link.l1.go = "cartridge_8";
		break;
		
		case "cartridge_8":
			AddQuestRecordInfo("Recipe", "OxyHydSilver");
			SetAlchemyRecipeKnown("OxyHydSilver");
			dialog.text = "Sie sind willkommen. Folgen Sie genau dem Rezept und achten Sie auf die Reihenfolge des Prozesses, sonst fliegen Sie mit Ihren Flaschen in die Luft.";
			link.l1 = "Ich werde vorsichtig sein.";
			link.l1.go = "cartridge_9";
		break;
		
		case "cartridge_9":
			dialog.text = "Auch, nehmen Sie diese zwei Flaschen. Diese hat Salpetersäure darin und diese hat Spiritus. Sie werden in der Lage sein, genug Knallsilber herzustellen, um etwa 20 Kapseln zu füllen.";
			link.l1 = "Danke dir, Gino!";
			link.l1.go = "cartridge_10";
		break;
		
		case "cartridge_10":
			GiveItem2Character(pchar, "Mineral29");
			GiveItem2Character(pchar, "Mineral28");
			Log_Info("You have received a flask of nitric acid");
			Log_Info("You have received a flask of spirit");
			PlaySound("interface\important_item.wav");
			dialog.text = "Auch nimm deine Pistole und die Beispiel Ladung. Viel Glück, Kapitän, bei der Herstellung von Ladungen. Ich hoffe, dass du am Leben bleibst und in einem Stück.";
			link.l1 = "Ich werde tun, was ich kann, um mich zu schützen. Und, Gino, habe ich dir gesagt, dass du ein Genie bist?";
			link.l1.go = "cartridge_11";
		break;
		
		case "cartridge_11":
			TakeNItems(pchar, "pistol7", 1);
			TakeNItems(pchar, "shotgun_cartridge", 3);
			TakeNItems(pchar, "GunCap_colt", 1);
			dialog.text = "Sie bringen mich zum Erröten, Kapitän, ich bin ernst...";
			link.l1 = "Fein. Auf Wiedersehen, Gino! Du bist mein bester Alchemist!";
			link.l1.go = "cartridge_12";
		break;
		
		case "cartridge_12":
			DialogExit();
			DeleteAttribute(npchar, "quest.cartridge");
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx":
            dialog.text = "Gord, Gord... Könntest du mir mehr über den Kapitän erzählen? Wo kommt er her?";
			link.l1 = "Keine Ahnung, obwohl er irgendwo im Norden geboren wurde, nannten sie ihn manchmal einen Wikinger.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Ein Wikinger! Ja-ja, ich erinnere mich, ich habe darüber in einem Geschichtsbuch gelesen. Gord ist eine befestigte Siedlung eines freien Jarls.";
			link.l1 = "Ein freier Jarl? Wer könnte das sein?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Es ist ein Prinz der Nordmänner. Freie Jarls mit ihren Kriegsbanden pflegten vor Jahrhunderten auf ihren Schiffen, Drakkars, Europa zu überfallen und zu plündern. Man könnte sie wohl Piraten nennen. Gords waren ihre Basen und Heime, Orte, an denen sie sich ausruhen, bewirtschaften und feiern konnten.";
			link.l1 = "Ich verstehe. Dieser Gord muss dann sein Piratenversteck sein... Danke, Gino!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookFourth");
		break;
		
	// ----------------------------------------- Португалец ----------------------------------------------------
		case "Portugal":
			dialog.text = "Fieber und Wahnvorstellungen, sagen Sie, das ist faszinierend. Bringen Sie ihn sofort hierher! Ich werde sehen, was ich tun kann. Aber ich kann Ihnen nichts versprechen, wenn sein Zustand zu schlecht ist... Ist er Ihr Offizier?";
			link.l1 = "Nein, Gott sei Dank, ist er nicht. Gino, hör zu, frag nicht, wer er ist, tu einfach, was du kannst, es ist mir wirklich wichtig!";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "In Ordnung, bring ihn ins Haus zu deinem Zimmer. Ich werde einige Mixturen vorbereiten... vielleicht wird diese Wurzel...";
			link.l1 = "Ich werde ihn sofort hierher bringen!";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			DialogExit();
			PChar.quest.Portugal_DoctorPodhodit.win_condition.l1 = "location";
			PChar.quest.Portugal_DoctorPodhodit.win_condition.l1.location = "SentJons_HouseF3";
			PChar.quest.Portugal_DoctorPodhodit.function = "Portugal_DoctorPodhodit";
		break;
		
		case "Portugal_nomoney":
			dialog.text = "Dann versuchen Sie es so schnell wie möglich zu finden, ohne Medikamente kann ich ihn nicht heilen und es könnte zu spät sein, wenn Sie sich nicht beeilen.";
			link.l1 = "Gut, ich werde das Geld finden.";
			link.l1.go = "exit";
			pchar.questTemp.Portugal.Nomoney = "true";
		break;
		
		case "Portugal_3":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "Prächtig, Kapitän. Jetzt werde ich mich um die Zubereitung einiger Mixturen kümmern und empfehle Ihnen, meinen Patienten zu verlassen. Kommen Sie morgen wieder hierher.";
			link.l1 = "Gut, Gino. Ich habe Vertrauen in deine Mixturen und in dein Genie.";
			link.l1.go = "exit";
			pchar.questTemp.Portugal = "TreatmentCurrent";
			//pchar.GenQuest.CannotWait = true;//запрет ожидания
		break;
		
		case "Portugal_4":
			dialog.text = "Nun, ich denke, er wird in zwei Wochen in Ordnung sein. Ich kann nicht versprechen, dass er in der Lage sein wird zu tanzen, aber zumindest wird er sicher auf seinen eigenen Füßen stehen.";
			link.l1 = "Verdammt, ich habe diese zwei Wochen nicht! Ich muss... so schnell wie möglich in See stechen!";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			dialog.text = "Kapitän, ich bin kein Magier und ich kann Ihnen versichern, dass der Mann momentan zu schwach ist. Ich bin mir nicht sicher, ob er ein paar Tage an Bord überleben wird, Sie können ihn nicht bewegen!";
			link.l1 = "Fein-fein, aber zwei Wochen, nein, sogar eine Woche ist zu viel!";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			dialog.text = "Drei Tage... ja, ich denke, in drei Tagen könntest du versuchen zu segeln, aber er wird Pflege und Medikamente brauchen und du wirst Zwischenstopps machen müssen.";
			link.l1 = "Ich habe einen Arzt, er wird sich um ihn kümmern. Ich werde in drei Tagen zurück sein und wir werden ihn mitnehmen, das ist das Meiste, was ich mir leisten kann. Wir müssen uns bewegen, auch mit Stopps... ja, und noch eine Sache - Gino, du bist ein Genie!";
			link.l1.go = "Portugal_7";
		break;
		
		case "Portugal_7":
			dialog.text = "Danke, Kapitän. Komm in drei Tagen wieder für deinen Freund, aber störe ihn bis dahin nicht. Er braucht vollständige Ruhe.";
			link.l1 = "Gut, ich habe es verstanden. Ich werde ihn in drei Tagen abholen.";
			link.l1.go = "Portugal_8";
		break;
		
		case "Portugal_8":
			DialogExit();
			SaveCurrentQuestDateParam("questTemp.Portugal_threedays");
			pchar.quest.Portugal_Ill2.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill2.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.Portugal_Ill2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.Portugal_Ill2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.Portugal_Ill2.function = "Portugal_ToAntiguaOver";//чтобы не тянул
			pchar.questTemp.Portugal = "TreatmentComplete";
			pchar.quest.Avendel_room.win_condition.l1 = "location";
			pchar.quest.Avendel_room.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Avendel_room.function = "AvendelSpeach";
		break;
		
		case "Portugal_threedays":
			dialog.text = "Er macht gute Fortschritte, aber es geht langsam voran. Er kann noch nicht genommen werden.";
			link.l1 = "Ja - ja, Gino, ich erinnere mich. Drei Tage...";
			link.l1.go = "exit";
		break;
		
		case "Portugal_9":
			pchar.quest.Portugal_Ill2.over = "yes";
			dialog.text = "Keine Verschlechterung, aber er ist auch nicht wirklich besser geworden. Er ist immer noch bewusstlos, er versteht nicht, wo er ist und warum er hier ist, obwohl es ihn nicht so sehr zu kümmern scheint. Er hat immer noch Fieber, deshalb bin ich mir nicht sicher, ob es jetzt eine gute Idee ist, ihn an Bord zu bringen.";
			link.l1 = "Ich kann nicht länger warten, wir sind schon zu lange hier. Packe deine Mixturen, die ihm auf der Reise helfen werden, und wir gehen. Ich hoffe, dass dieser Bastard stark genug ist, um lange genug zu überleben, um sein Todesurteil zu erleben...";
			link.l1.go = "Portugal_10";
		break;
		
		case "Portugal_10":
			dialog.text = "Warte, Kapitän! Habe ich die Verurteilten behandelt? Was zum Teufel? Hier wurde eine riesige Arbeit geleistet, hast du eine Ahnung, wie schwierig es ist, das Trockenpulver herzustellen...";
			link.l1 = "Gino, das musstest du nicht wissen. Mach dir keine Sorgen, er ist ein Pirat und einer der schlimmsten seiner Art. Ich muss ihn so schnell wie möglich nach Curacao bringen, um ein Treffen mit den Behörden der Kompanie zu arrangieren. Punkt.";
			link.l1.go = "Portugal_11";
		break;
		
		case "Portugal_11":
			dialog.text = "Gut, Sie wissen es besser. Pirat dann... Curacao. Was auch immer, aber hören Sie mir zu, er wird die meiste Zeit schlafen, aber das Rollen des Schiffes und die stickige Hitze können den ganzen Prozess rückgängig machen. Ich empfehle, nach ein paar Tagen Segeln einen Stopp einzulegen und Ihren... Gefangenen an Land ausruhen zu lassen. Andernfalls besteht die Gefahr, dass sie auf Curacao eine Leiche aufhängen müssen... ";
			link.l1 = "Gut, ich werde das tun. Martinique wird gut geeignet sein, es ist fast auf halbem Weg nach Curacao. Ich hoffe, dass der Wind günstig sein wird. Ich werde ihn jetzt mitnehmen und wir werden gehen. Nochmals vielen Dank, Gino.";
			link.l1.go = "Portugal_12";
		break;
		
		case "Portugal_12":
			dialog.text = "Sie sind willkommen, Kapitän. Denken Sie daran, dass Sie vier Tage haben, nun, fünf, aber nicht mehr. Und noch eine letzte Sache... Sie wissen, ich heile normalerweise Menschen nicht, weil ich will, dass sie nach meiner Behandlung gehängt werden. Der Arzt ist für seine Patienten verantwortlich, egal wer sie sind. Und ich fühle mich wirklich schlecht...";
			link.l1 = "Es tut mir leid, dass ich dich in all das hineingezogen habe, aber ohne dich hatten wir keine Chance. Wir müssen jetzt in See stechen, sonst schaffen es die Portugiesen, sich vor unserer Tür zu versammeln, um ihren Boss zu treffen.";
			link.l1.go = "Portugal_13";
		break;
		
		case "Portugal_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3_Room", "goto", "goto2", "Portugal_JinoNorm", -1);//Джино в свою комнату
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			pchar.quest.Portugal_Ill3.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill3.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.Portugal_Ill3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.Portugal_Ill3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.Portugal_Ill3.function = "Portugal_ToAntiguaOver";//5 дней до Мартиники
			pchar.questTemp.Portugal = "ToMartinique";
			pchar.quest.Avendel_room1.win_condition.l1 = "location";
			pchar.quest.Avendel_room1.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Avendel_room1.function = "AvendelSpeach";
			pchar.quest.Portugal_street.win_condition.l1 = "location";
			pchar.quest.Portugal_street.win_condition.l1.location = "SentJons_town";
			pchar.quest.Portugal_street.function = "PortugalOnStreet";
		break;
		// <-- Португалец
		case "guardoftruth_0":
			dialog.text = "Interessant... Und wie können Sie mir helfen? Ich brauche keine Hilfe und habe nicht danach gefragt...";
			link.l1 = "Aber du wirst es brauchen. Hör mir zuerst zu und ziehe dann Schlüsse.";
			link.l1.go = "guardoftruth";
		break;
		
		case "guardoftruth":
			dialog.text = "Ich bin ganz Ohr.";
			link.l1 = "Ich war kürzlich in Santiago ... zu Besuch bei Vater Vincento. Er suchte nach seinem verschwundenen Sekretär namens ... Jesus, warum bist du so blass geworden, Gino?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Du... hast den Inquisitor gesehen? Ist er...";
			link.l1 = "Mach dir keine Sorgen, Gino. Es besteht keine Chance, dass ich dich ihm ausliefere, obwohl das sein Befehl war: dich zu finden und dich zu ihm zu bringen. Ich muss einige Informationen über einen Indianer des Itza-Volkes sammeln. Erzähl mir von Tayasal, seinen Schätzen und dem 'Bösen' daran.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Ich sehe, dass Sie gut informiert sind. Hat Ihnen Vater Vincento das erzählt?";
			link.l1 = "Ich habe einige Informationen von ihm und einige andere von anderen Leuten bekommen. Aber ich würde gerne Ihre Meinung hören. Sie waren einmal sein Sekretär, daher müssen Sie ein Protokoll des Verhörs erstellt haben, liege ich richtig?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Sie können sich nicht vorstellen, was er diesem armen Inder angetan hat!.. Es lässt meine Haut kriechen, jedes Mal wenn ich dieses Verhör in meinem Kopf aufrufe.";
			link.l1 = "Dennoch, lass uns darüber reden. Wer war dieser Indianer? Wie kam er in die Hände von Vater Vincento?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Er gehörte zu den Indianern des Itza-Volkes, die aus Tayasal auf der Suche nach der Kukulcan-Maske - einem Artefakt des alten Maya-Gottes - Kukulcan reisten. Diese Indianer trafen auf eine Gruppe weißer Abenteurer, angeführt von Archibald Calhoun - einem Schatzjäger aus Schottland. Nur ein Indianer überlebte, sein Name war Ksatl Cha. Er hatte drei interessante Gegenstände bei sich, ich werde Ihnen später davon erzählen.\Calhoun hatte versucht, den Gefangenen zur Preisgabe von Schätzen zu zwingen, aber er schwieg. Also lieferte der Schotte ihn nach Santiago, zu Pater Vincento, im Austausch für die Erlaubnis, ein Jahr lang spanische Städte zu besuchen. Er wusste, dass der Inquisitor sehr an allen Arten von lokalen Mysterien und Legenden interessiert ist. Vincento brachte den Indianer zum Reden. Er fing an viel zu reden, er erzählte uns alles, was er wusste und die Informationen, die wir aus ihm herausbekamen, schockierten den Inquisitor selbst.";
			link.l1 = "Ach ja? Und was könnte Seine Gnaden zum Zittern bringen?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Ich werde dir alles der Reihe nach erzählen. Tief in den Dschungeln von Yucatan liegt eine alte Maya-Stadt namens Tayasal. Sie wird von den Nachkommen der Maya - dem Itza-Volk - bewohnt. Sie versuchen, ihr Leben nach den Regeln und Traditionen ihrer Vorfahren zu führen. Sicherlich mögen sie den Zustand der modernen Welt nicht - ich meine die Dominanz des weißen Mannes.\nSie träumen von den guten alten Zeiten. Und jetzt kommt der interessanteste Teil. Ein Haufen weißer Abenteurer kam zufällig in die Nähe von Tayasal und entführte die Tochter des obersten Häuptlings der Itza. Das geschah vor fast einem Vierteljahrhundert.\nDies war der letzte Tropfen und Kanek, der Häuptling, war außer sich vor Wut. Er beschloss, das gefährlichste und geheimste Ritual der Maya durchzuführen - die Beschwörung eines indischen Gottes, um alle Nachkommen der weißen Eroberer auszulöschen...";
			link.l1 = "Hm... Das muss der Dämon sein, von dem Vater Vincento sprach. Aber wie sollte dieser indische Gott mit den weißen Kolonisten umgehen? Zeigt er sich in Form eines Drachens und verbrennt sie alle?";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Ach, "+pchar.name+", lass diese Feuergeschichten den alten Großmüttern! Eigentlich liegst du gar nicht so falsch, aber unser Fall ist schwieriger und ernster. Selbst die Sintflut könnte Europa nicht davon abhalten, in die Neue Welt vorzudringen. Zehn weitere werden kommen, um einen toten zu ersetzen. Kanek musste die Möglichkeit der europäischen Kolonisierung selbst zerstören.";
			link.l1 = "Nun, es ist bereits passiert.";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Sie denken in die richtige Richtung, Kapitän... Der Zweck von Kaneks Ritus war nicht nur die Beschwörung des hohen Wesens, sondern auch die Schaffung eines raumzeitlichen Lochs.";
			link.l1 = "Was?";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Die Alten des Maya-Volkes besaßen ein beachtliches Wissen, Kapitän. Kanek fand die Beschreibung eines Ritus, der es ermöglicht, die Zeit zu kontrollieren.";
			link.l1 = "Wahnsinn! Unglaublich!";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Hör zu. Das ultimative Ziel des Rituals ist es, die Vergangenheit so zu verändern, dass das Erscheinen des weißen Mannes in der Neuen Welt unmöglich wird. Um so etwas zu tun, werden sie jemanden in die Vergangenheit schicken, jemanden, der Autorität, Macht und die Fähigkeit besitzt, das Schicksal der Menschen zu verändern. Aber am wichtigsten ist, dass eine solche Person modernes Wissen besitzen muss.\nDenk darüber nach, "+pchar.name+", was wäre mit Columbus passiert, wenn seine Karavellen von einer indischen Flotte von Fregatten und Galeonen mit modernen Kanonen getroffen worden wären? Und was, wenn die Hakenbüchsen der weißen Soldaten nicht Bögen und Speeren, sondern Mörsern und Muskete gegenübergestanden hätten?";
			link.l1 = "Ich vermute, dass die Amerikas überhaupt nicht entdeckt worden wären....";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Genau! Und vielleicht hätte irgendein indischer 'Columbus' Europa entdeckt...";
			link.l1 = "Interessant, und wen wird Kanek in die Vergangenheit schicken? Einen seiner nackten Krieger? Ich bezweifle, dass er seinen Vorfahren etwas beibringen kann...";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			dialog.text = "Lachen Sie nicht, Kapitän. Kanek hat keine Jahre in Maya-Tempeln verschwendet, um ihre Schriften zu lesen. Ein indischer Gott muss in menschlicher Form in die Vergangenheit geschickt werden...";
			link.l1 = "Gino, welchen Unsinn redest du? Bist du....";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			dialog.text = "Sogar der Sohn unseres Herrn, Jesus Christus, ist in menschlicher Gestalt auf unsere Erde gekommen und wurde von einer menschlichen Frau, der Heiligen Jungfrau Maria, geboren...";
			link.l1 = "Jesus, Gino... bist du ernst?";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			dialog.text = "Sicher bin ich das. Ksatl Cha war sehr überzeugend...";
			link.l1 = "Aber welchen Gott hat Kanek für eine solche 'edle' Mission gewählt?";
			link.l1.go = "guardoftruth_14";
		break;
		
		case "guardoftruth_14":
			dialog.text = "Die Zeremonie war dazu bestimmt, nur ein hohes Wesen zu rufen. Die gefiederte Schlange, Quetzalcoatl, Kukulcan...";
			if (CheckAttribute(pchar, "questTemp.Dolly")) link.l1 = "Kukulcan?! Ich hatte schon die Unvorsichtigkeit, seinem 'Geist' zu begegnen, der in Statuen lebt. Jetzt sehe ich... fahre fort!";
			else link.l1 = "Hm. Interessant. Ich habe diesen Namen bereits von Vater Vincento gehört... fahren Sie fort!";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Kanek beschloss, Kukulcan zu beschwören, da die Itza bereits ein altes Artefakt dieses Gottes hatten - die Maske von Kukulcan. Derjenige, der die Maske hat, kann durch das Portal gehen und nur er wird von den alten Maya als lebender Gott akzeptiert.\nDer Priester führte das Ritual durch, beschwor Kukulcan, um im Körper eines Sterblichen zu inkarnieren. Er schuf auch ein Zeitloch, das mehrere zufällige Personen aus der Zukunft in unsere Zeit holte.\nDas Ziel dieser Extraktion war es, Kukulcans Inkarnation nicht nur mit dem Wissen unserer Zeiten, sondern auch der Zukunft zu präsentieren. Aber etwas ging schief und all diese Menschen kamen anderswo an und nicht in Tayasal. Ich habe nie einen von ihnen getroffen.\nMehrere Portale wurden innerhalb des Archipels geschaffen, sie sollten die Besitzer von Zukunftskenntnissen und Itza-Agenten in der ganzen Gegend und nach Tayasal transportieren. Aber diese Portale haben ihren Zweck verfehlt, niemand wurde in den letzten 25 Jahren nach Tayasal geliefert...";
			if (CheckAttribute(pchar, "questTemp.Dolly"))
			{
				link.l1 = "Sicher... Weil diese Portale gefangene Menschen nur zu einander transferieren. Unglaublich!";
				link.l1.go = "guardoftruth_15a";
			}
			else
			{
				link.l1 = "Interessant...";
				link.l1.go = "guardoftruth_16";
			}
		break;
		
		case "guardoftruth_15a":
			dialog.text = "Hast du diese Portale gesehen? Sag es mir!";
			link.l1 = "Vielleicht später, Gino... Im Moment interessiert mich deine Geschichte mehr. Mach weiter!";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			dialog.text = "Vater Vincento ist sich über alles im Klaren, was ich Ihnen erzählt habe. Dies hat ihn natürlich beunruhigt. Wenn Kukulcan, in menschlicher Form inkarniert, zusammen mit der Maske und all dem Wissen, das er gesammelt hat, zum Portal gelangt... Ende der Zeiten. Apokalypse.\nWenn sich die Vergangenheit verändert - tut das die Zukunft auch. Unsere Realität wird sich ändern, sie wird verschwinden, sich auflösen. Du und ich werden vielleicht nie geboren. Oder wir werden anders sein. Sobald Kukulcan die Vergangenheit erreicht - werden wir aufhören zu existieren.";
			link.l1 = "Und wer ist Kukulcans Inkarnation?";
			link.l1.go = "guardoftruth_17";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Wer weiß. Er könnte in jedem sein, der vor einem Vierteljahrhundert geboren wurde, als das Ritual durchgeführt wurde. In dir zum Beispiel... nur ein Scherz. Aber wir haben immer noch eine Chance. Erstens, die Inkarnation von Kukulcan ist nur eine sterbliche Person, sie kann ertrinken, erstochen, erschossen werden oder an Fieber sterben. Und in einem solchen Fall wird keine Apokalypse jemals geschehen.\nZweitens, es ist unmöglich, die Vergangenheit ohne die Maske zu erreichen, Kanek hat sie sehr gut versteckt, vielleicht zu gut, wie es scheint. Es könnte sein, dass selbst der inkarnierte Kukulcan sie nicht finden wird.";
			link.l1 = "Sag mir mehr.";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "Eine Zeit nach dem Ritual erreichte eine Gruppe spanischer Eroberer fast Tayasal und kam fast bis zum Schatz. Den Itza gelang es, alle bis auf einen zu töten - einen starken Riesen von sieben Fuß Größe.\nKanek hatte Angst, dass die Maske von einem Fremden gestohlen werden könnte, also entschied er sich, die Reliquie zu schützen. Er erfand sein eigenes Ritual, mit dem Wissen der alten Maya. Er nahm drei Gegenstände, von denen er glaubte, dass sie die Macht des weißen Mannes in sich trugen. Ein Dolch, der einst Cortez selbst gehörte, und ein Kompass. Mit diesem Dolch schnitt er auch ein Stück Haut von dem Rücken des gefangenen spanischen Riesen als dritten Gegenstand ab. Der Mann selbst wurde auf dem Altar von Kukulcan geopfert. Drei Gegenstände wurden in dem Ritual verwendet.\nUnd aus diesem Ritual wurde eine neue Insel geboren, auf offenem Meer, nicht weit von Yucatan. Niemand kennt ihren Standort, aber die Maske ist dort versteckt. Um sie zu finden, muss man den Dolch, den Kompass und das Stück Haut verwenden. Außerdem sind alle Gegenstände aus dem Schatz verflucht, keiner von ihnen kann den Archipel verlassen.\nEin Versuch, dies zu tun, wird einen Sturm verursachen, der das Schiff direkt auf die Felsen der Insel bringt, wo die Maske versteckt ist. Sie wird Ksocheatem genannt. Schlau, nicht wahr?";
			link.l1 = "Vielleicht zu schlau. Darüber lässt sich nicht streiten. Aber wie um alles in der Welt war Ksatl Cha so gut informiert? Ich bezweifle, dass Kanek solches Wissen mit gewöhnlichen Kriegern teilte...";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "Die Sache ist, der aktuelle Anführer der Itza, Urakan, der Sohn von Kanek, hatte diesem Krieger alles erzählt. Er schickte Ksatl Cha mit einer Gruppe von Kriegern, um die geheime Insel und die Maske von Kukulcan zu finden. Er hatte ihm den Hüter der Wahrheit dazu gegeben, das ist der Name der drei Gegenstände zusammen - der Dolch, der Kompass und die Karte aus Menschenhaut.";
			link.l1 = "Die Karte? Und warum brauchte Urakan die Maske? Er beschloss, die Vergangenheit selbst zu ändern?";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "Die Haut hat Konturen des Archipels darauf, daher nennen sie es die Karte. Urakan wollte die Maske aus einem sehr einfachen Grund - er will die bestehende Realität nicht zerstören und sein Leben und das Leben seines Volkes für den Ruhm der Alten opfern.\nDeswegen wollte er die Maske um jeden Preis zerstören. Aber Ksatl Cha wurde von Calhoun gefangen genommen und... nun, den Rest der Geschichte kennst du. Er erreichte Ksocheatem nie.";
			link.l1 = "So ist es möglich, das Ende der Zeiten zu verhindern, indem man die Maske findet und zerstört? Und wo ist dieser... Wahrheitswächter jetzt?";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			dialog.text = "Der Dolch 'Klaue des Häuptlings' und der Kompass 'Pfeil des Weges' wurden Calhoun überlassen und die Hautkarte 'Von zwei Erscheinungen' befindet sich noch irgendwo in der Inquisition. Calhoun benutzte sie als Knebel, um dem Gefangenen das Maul zu stopfen. Er hatte keine Ahnung, wozu diese Gegenstände gut waren.";
			link.l1 = "Was hast du gerade gesagt? 'Häuptlingsklaue'? Verdammt, dieser Dolch ist jetzt bei mir! Fadey hat ihn mir als Ausgleich für seine Schulden bei meinem Bruder gegeben! Schau mal!";
			link.l1.go = "guardoftruth_22";
		break;
		
		case "guardoftruth_22":
			dialog.text = "Unglaublich... Es ist wirklich so. Ich erinnere mich daran.";
			link.l1 = "Gino, sag mir, was weiß Vater Vincento genau von deiner Geschichte?";
			link.l1.go = "guardoftruth_23";
		break;
		
		case "guardoftruth_23":
			dialog.text = "Alles, außer Informationen über den Hüter der Wahrheit und wie man ihn dazu bringt, den Ort der geheimen Insel zu zeigen, wo die Maske von Kukulcan versteckt ist. Ksatl Cha hat mir davon erzählt, als wir kurz vor meinem Giftgemisch, um sein Leiden zu beenden, alleine waren. Er starb mit einem Lächeln im Gesicht.\nSicherlich konnte ich nach dem, was ich getan hatte, nicht in Santiago bleiben. Ich hatte ernsthafte Verdachtsmomente, dass ich für den Inquisitor ein wichtiger und gefährlicher Zeuge wurde. Vater Vincento bekommt immer, was er will, egal zu welchem Preis. Ksatl Cha erzählte ihm von der Schatzkammer in Tayasal.";
			link.l1 = "Diese Schätze wurden bereits von einem Abenteurer namens Miguel Dichoso gefunden. Haben Sie von ihm gehört?";
			link.l1.go = "guardoftruth_24";
		break;
		
		case "guardoftruth_24":
			dialog.text = "Nein. Und wo ist er jetzt mit seinen Schätzen?";
			link.l1 = "Ich möchte es selbst wissen. Deshalb bin ich zu Ihnen gekommen, ich suche nach diesem indischen Gold. Dichoso hat die Schätze nach Europa gebracht und ist mit ihnen verschwunden.";
			link.l1.go = "guardoftruth_25";
		break;
		
		case "guardoftruth_25":
			dialog.text = "Ich werde dir sagen, wo die Schätze und Dichoso selbst sind.";
			link.l1 = "Gino, du überraschst mich. Wie könntest du das wissen?!";
			link.l1.go = "guardoftruth_26";
		break;
		
		case "guardoftruth_26":
			dialog.text = "Sie können dies selbst aus meiner Geschichte herausfinden, Kapitän. Die Schätze von Tayasal waren verflucht - kein einziger Gegenstand kann vom Archipel weggenommen werden. Jedes Schiff...";
			link.l1 = "... wird vom Sturm erfasst und auf die Insel geworfen, wo die Maske von Kukulcan versteckt ist! Ich war blind, aber jetzt sehe ich. Es scheint, dass ich genug weiß, um Ksocheatem, die Schätze und die Maske selbst zu finden!";
			link.l1.go = "guardoftruth_27";
		break;
		
		case "guardoftruth_27":
			dialog.text = "Möchten Sie die Welt retten, Kapitän?";
			link.l1 = "Ich möchte meinen verlorenen Bruder finden... Gino, wie kann ich den Wahrheitswächter dazu bringen, den Standort der Insel zu zeigen? Du hast gesagt, dass du weißt wie!";
			link.l1.go = "guardoftruth_28";
		break;
		
		case "guardoftruth_28":
			dialog.text = "Ich kenne die Methode, aber ich kenne die Details nicht. Ich kann Ihnen nicht helfen, bis ich alle Komponenten des Wächters habe.";
			link.l1 = "Hm. Wir haben bereits den Dolch. Es fehlen nur noch der Kompass und die Karte. Calhoun hat den Kompass und Vater Vincento hat die Karte...";
			link.l1.go = "guardoftruth_29";
		break;
		
		case "guardoftruth_29":
			dialog.text = "Gehst du zum Inquisitor zurück? Aber wie wirst du berichten über...";
			link.l1 = "Ich muss Pater Vincento davon überzeugen, dass du tot bist, Gino. Nur dann wird er seine Suche einstellen. Sagen wir, du hattest einen plötzlichen Schlaganfall, als du mich gesehen hast. Du solltest mir einen Gegenstand geben, den ich als Beweis für deinen Tod verwenden kann.";
			link.l1.go = "guardoftruth_30";
		break;
		
		case "guardoftruth_30":
			dialog.text = "Vincento wird nicht an einen Herzinfarkt glauben, aber er wird dir glauben, wenn du ihm sagst, dass ich Selbstmord begangen habe, indem ich ein Gift mit Mandelgeruch getrunken habe. Gib ihm mein Almanach, er weiß, dass ich mich nie davon trenne.";
			link.l1 = "Gut. Denn ich brauche diese Verbindung zum Inquisitor. Er weiß wahrscheinlich viel über unser Geschäft.";
			link.l1.go = "guardoftruth_31";
		break;
		
		case "guardoftruth_31":
			dialog.text = "Sei vorsichtig mit Vater Vincento. Er ist so gefährlich wie ein Tiger und er spielt sein eigenes Spiel. Er wird weder Schätze noch Ruhm mit dir teilen.";
			link.l1 = "Ich verstehe das. Gut, Gino, gib mir dein Almanach und versuche dich an das zu erinnern, was der Indianer dir über den Wächter der Wahrheit erzählt hat, denn ich möchte es zusammensetzen. Ich muss Ksocheatem finden, ich bin sicher, dass ich dort nicht nur die Maske und die Schätze, sondern auch meinen lieben Bruder finden werde.";
			link.l1.go = "guardoftruth_32";
		break;
		
		case "guardoftruth_32":
			dialog.text = "Nimm es. Viel Glück, Kapitän!";
			link.l1 = "Ich sage nicht Auf Wiedersehen, Gino...";
			link.l1.go = "guardoftruth_33";
		break;
		
		case "guardoftruth_33":
			DialogExit();
			Log_Info("You have received an almanac");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "Almanac");
			ChangeItemDescribe("Almanac", "itmdescr_jinobook");
			pchar.questTemp.Guardoftruth = "twoitems";
			AddQuestRecord("Guardoftruth", "37");
		break;
		
		case "guardoftruth_34":
			dialog.text = "War es schwer, Kapitän?";
			link.l1 = "Lassen wir das... Zu viele Menschen sind gestorben, um diese Gegenstände zu bekommen. Zu viele. Es scheint, dass ich nicht der Einzige bin, der darauf erpicht ist, den mysteriösen Ksocheatem zu finden. ";
			link.l1.go = "guardoftruth_35";
		break;
		
		case "guardoftruth_35":
			dialog.text = "Ich kann mir vorstellen... Übrigens, wie geht es Vater Vincento? Kommunizieren Sie regelmäßig mit ihm?";
			link.l1 = "Bisher habe ich das getan, aber ich glaube, dass es nicht mehr nötig ist. Ich habe alle Bestandteile des Hüters der Wahrheit, was bedeutet, dass ich den Schlüssel zum Standort von Ksocheatem besitze. Aus irgendeinem Grund habe ich keine Lust, Seiner Gnaden von meinem Erfolg zu berichten.";
			link.l1.go = "guardoftruth_36";
		break;
		
		case "guardoftruth_36":
			dialog.text = "Sei vorsichtig, "+pchar.name+". Vater Vincento hat hunderte von Augen und Händen. Sehr lange Hände...";
			link.l1 = "Ich habe in den letzten Monaten viel durchgemacht und ich habe sicherlich keine Angst, weder vor Vater Vincento noch vor seinen Augen und Händen. Was auch immer. Es ist an der Zeit, dass wir Ksocheatem mit Hilfe der Komponenten des Wächters finden. Weißt du, wie man das macht?";
			link.l1.go = "guardoftruth_37";
		break;
		
		case "guardoftruth_37":
			dialog.text = "Nicht wirklich. Ksatl Cha war ziemlich vage. Ich glaube, der Indianer wusste nicht wirklich, wie man den Wächter zum Laufen bringt. Überlassen Sie mir die Komponenten und ich werde versuchen, das herauszufinden. Besuchen Sie mich in zwei Tagen und vielleicht habe ich dieses Rätsel gelöst.";
			link.l1 = "Gut, Gino. Ich zähle auf dich. Hier, nimm sie.";
			link.l1.go = "guardoftruth_38";
		break;
		
		case "guardoftruth_38":
			dialog.text = "Sie können sicher sein, dass sie bei mir sicher und unversehrt bleiben.";
			link.l1 = "Ich zweifle nicht daran. Nun, ich werde dich jetzt nicht stören, Gino. Viel Glück mit deiner Forschung!";
			link.l1.go = "guardoftruth_39";
		break;
		
		case "guardoftruth_39":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			RemoveItems(pchar, "knife_01", 1);
			RemoveItems(pchar, "skinmap", 1);
			RemoveItems(pchar, "arrowway", 1);
			pchar.questTemp.Guardoftruth = "end";
			SetFunctionTimerCondition("Ksochitam_StartSearchIsland", 0, 0, 2, false);
			CloseQuestHeader("Guardoftruth");
			AddQuestRecord("Ksochitam", "1");
		break;
		
		case "ksochitam":
			dialog.text = "Teilweise. Ich meine, ich habe etwas, aber ich weiß nicht, wie ich es zum Laufen bringen soll. Lassen Sie uns dieses Rätsel gemeinsam lösen.";
			link.l1 = "Lass es uns versuchen! Gib mir deine Ideen.";
			link.l1.go = "ksochitam_1";
		break;
		
		case "ksochitam_1":
			dialog.text = "Ksatl Cha sagte so etwas: 'Die Klaue des Häuptlings wird die Karte sich offenbaren lassen. Der Pfeil des Weges wird die Richtung der Erscheinungen zeigen.";
			link.l1 = "Und was hast du geschafft zu tun?";
			link.l1.go = "ksochitam_2";
		break;
		
		case "ksochitam_2":
			dialog.text = "Ich habe herausgefunden, wie man die Karte 'enthüllt'. Haben Sie sich die Karte der Zwei Erscheinungen angesehen?";
			link.l1 = "Hm. Und gab es etwas Besonderes? Einige verschleierte Konturen des Archipels...";
			link.l1.go = "ksochitam_3";
		break;
		
		case "ksochitam_3":
			GiveItem2Character(pchar, "skinmap");
			dialog.text = "Nimm es und schau noch einmal genau hin. Sei aufmerksam.";
			link.l1 = "Nun, lassen wir das tun, wenn Sie darauf bestehen.";
			link.l1.go = "ksochitam_4";
		break;
		
		case "ksochitam_4":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_wait";
			pchar.questTemp.Ksochitam = "skinmap_1";
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "ksochitam_wait":
			dialog.text = "Du hast dir die Karte noch nicht angesehen, "+pchar.name+"...";
			link.l1 = "Ja-ja, ich mache es jetzt...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_wait";
		break;
		
		case "ksochitam_5":
			dialog.text = "";
			link.l1 = "Ich habe. Ich habe nichts Neues gesehen. Nur einige verschleierte Formen von Inseln und dem Main. Was soll ich dort sehen?";
			link.l1.go = "ksochitam_6";
		break;
		
		case "ksochitam_6":
			dialog.text = "Warte eine Sekunde. Jetzt musst du diese Karte zum Vorschein bringen. Nimm den Dolch und berühre die Karte sanft mit seiner Kante. Drücke nicht, wir müssen Schäden vermeiden. Nimm den Dolch. Und beobachte es genau!";
			link.l1 = "Interessant! Lass uns sehen...";
			link.l1.go = "ksochitam_7";
		break;
		
		case "ksochitam_7":
			DialogExit();
			GiveItem2Character(pchar, "knife_01");
			NextDiag.CurrentNode = "ksochitam_wait";
			pchar.questTemp.Ksochitam = "skinmap_2";
			sld = ItemsFromID("skinmap");
			sld.mark = 2;
		break;
		
		case "ksochitam_8":
			dialog.text = "Nun, siehst du jetzt irgendwelche Unterschiede?";
			link.l1 = "Ja. Wenn du die Karte mit dem Dolch berührst, erscheinen zwei Schädelmarkierungen und sie sind immer an den gleichen Stellen...";
			link.l1.go = "ksochitam_9";
		break;
		
		case "ksochitam_9":
			dialog.text = "An den ZWEI gleichen Orten, "+pchar.name+"! Deshalb wurde es die Karte der Zwei Erscheinungen genannt!";
			link.l1 = "Und was bedeutet das?";
			link.l1.go = "ksochitam_10";
		break;
		
		case "ksochitam_10":
			dialog.text = "Viel, denke ich... Aber mehr Rätsel kommen als nächstes. Ich nehme an, dass diese Schädel die Erscheinungen sind, von denen Ksatl Cha sprach. Also muss der Kompass die richtige Richtung zu Ksocheatem von ihnen anzeigen. Haben Sie den Kompass gesehen, "+pchar.name+"?";
			link.l1 = "Ja. Es sieht aus wie ein gewöhnlicher Marinekompass, aber er verhält sich merkwürdig, sein Pfeil zuckt in verschiedene Richtungen oder beginnt mit wilder Geschwindigkeit sich zu drehen.";
			link.l1.go = "ksochitam_11";
		break;
		
		case "ksochitam_11":
			dialog.text = "Ich dachte, dass das Anbringen des Kompasses auf den Schädeln seinen Zeiger stoppen und eine klare Richtung auf der Karte anzeigen würde. Um das auszuführen, habe ich ihn auf einem Schädel und dann auf dem anderen platziert, während ich die Karte mit dem Dolch berührte.";
			link.l1 = "Und?";
			link.l1.go = "ksochitam_12";
		break;
		 
		case "ksochitam_12":
			dialog.text = "Vergeblich. Der Kompass hat sein Verhalten nicht geändert. Der Pfeil dreht sich immer noch wild. Es scheint, dass ich etwas falsch mache. Oder ich habe die Worte von Ksatl Cha nicht richtig verstanden.";
			link.l1 = "Also funktionieren der Dolch und die Karte und der Kompass nicht?";
			link.l1.go = "ksochitam_13";
		break;
		
		case "ksochitam_13":
			dialog.text = "Der Pfeil des Weges muss sicherlich funktionsfähig sein, wir wissen nur noch nicht, wie man ihn zum Laufen bringt."+pchar.name+", Sie kennen die Geographie des Archipels besser als ich... Sagen Sie mir, welche Orte werden von der Karte der zwei Erscheinungen offenbart?";
			link.l1 = "Einen Moment! (schaut sich um)... Nun, nun... Die Erscheinung links ist die westliche Main. Die rechte sieht aus wie die Insel Dominica. So etwas in der Art.";
			link.l1.go = "ksochitam_14";
		break;
		
		case "ksochitam_14":
			dialog.text = "Und sag mir: Gibt es... etwas Bemerkenswertes an diesen Orten?";
			link.l1 = "Was meinst du?";
			link.l1.go = "ksochitam_15";
		break;
		
		case "ksochitam_15":
			dialog.text = "Ich bin mir selbst nicht sicher... Nun, etwas Besonderes?";
			link.l1 = "Gino, rede keine Rätsel. Erkläre es einfach.";
			link.l1.go = "ksochitam_16";
		break;
		
		case "ksochitam_16":
			dialog.text = "Ich kann nur vermuten, dass diese Schädel uns einige echte Orte zeigen. Der Pfeil des Weges funktioniert nicht, während er auf den Erscheinungen der Karte gepflanzt ist. Vielleicht wird es in der Nähe der echten geographischen Erscheinungen funktionieren, die von der Karte offenbart wurden?";
			link.l1 = "Gino, du bist ein Genie! Westliches Hauptland, Dominica? Die Schädel sind zu groß, um die genauen Standorte anzuzeigen.";
			link.l1.go = "ksochitam_17";
		break;
		
		case "ksochitam_17":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = ""+pchar.name+", lass uns folgendes tun: Bring mir eine Papiertkarte des Archipels, kombiniere sie mit der Karte der Zwei Erscheinungen und markiere die Erscheinungen mit Kreuzen. Vielleicht gibt dir das einige Vermutungen?";
			if (CheckCharacterItem(pchar, "map_bad"))
			{
				link.l1 = "Ich habe diese alte Karte des Archipels.";
				link.l1.go = "ksochitam_17_1";
			}
			if (CheckCharacterItem(pchar, "map_normal"))
			{
				link.l2 = "Ich habe diese feine Karte des Archipels.";
				link.l2.go = "ksochitam_17_2";
			}
			if (CheckCharacterItem(pchar, "Map_Best"))
			{
				link.l3 = "Ich habe diese hervorragende Karte des Archipels.";
				link.l3.go = "ksochitam_17_3";
			}
			link.l4 = "Abgemacht. Ich bringe dir eine Karte und wir setzen fort...";
			link.l4.go = "ksochitam_17_4";
		break;
		
		case "ksochitam_17_1":
			dialog.text = "Ach, komm schon, "+pchar.name+"! Dieses Pergament aus der Zeit von Kolumbus ist nicht viel besser als die Hautkarte. Ich bin sicher, dass es etwas Besseres als diesen Müll in der Welt gibt. Bring mir eine andere Karte, eine jüngere!";
			link.l1 = "Gut...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_17_2":
			dialog.text = "Prächtig! Markiere nun die Orte der Erscheinungen darauf. Es wird es einfacher machen, Vermutungen aufzustellen.";
			link.l1 = "Nur einen Moment, Gino!";
			link.l1.go = "ksochitam_18";
		break;
		
		case "ksochitam_17_3":
			dialog.text = "Wir werden eine so wunderbare Karte nicht mit unseren Markierungen ruinieren. Du wirst sie selbst brauchen, "+pchar.name+". Bring mir eine andere Karte, eine etwas bescheidenere!";
			link.l1 = "Gut...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_17_4":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_map_wait":
			dialog.text = "Haben Sie mir eine Karte des Archipels gebracht, "+pchar.name+"?";
			if (CheckCharacterItem(pchar, "map_bad"))
			{
				link.l1 = "Ich habe diese alte Karte des Archipels.";
				link.l1.go = "ksochitam_17_1";
			}
			if (CheckCharacterItem(pchar, "map_normal"))
			{
				link.l2 = "Ich habe diese feine Karte des Archipels.";
				link.l2.go = "ksochitam_17_2";
			}
			if (CheckCharacterItem(pchar, "Map_Best"))
			{
				link.l3 = "Ich habe diese ausgezeichnete Karte des Archipels.";
				link.l3.go = "ksochitam_17_3";
			}
			link.l4 = "Noch nicht, aber ich habe es bereits bestellt. Bald werde ich es haben und wir werden weitermachen...";
			link.l4.go = "ksochitam_17_4";
		break;
		
		case "ksochitam_18":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_19";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto1", "Ksochitam_SitTable", -1);
		break;
		
		case "ksochitam_19":
			dialog.text = "";
			link.l1 = "Fertig... Ich habe die Markierungen erstellt, aber die Informationen sind immer noch ungenau. Der erste Ort liegt irgendwo nordwestlich von Blueweld. Der zweite ist im Zentrum der Insel Dominica.";
			link.l1.go = "ksochitam_20";
		break;
		
		case "ksochitam_20":
			dialog.text = "Hast du irgendwelche Ideen?";
			link.l1 = "Nein. Aber ich denke, dass wir den Pfeil des Weges dorthin bringen und sein Verhalten beobachten sollten. Natürlich ist es wie die Suche nach einer Nadel im Heuhaufen, aber wir haben sowieso keine besseren Ideen.";
			link.l1.go = "ksochitam_21";
		break;
		
		case "ksochitam_21":
			dialog.text = "Ich stimme Ihnen zu, "+pchar.name+". Wirst du mich mit dir segeln lassen?";
			link.l1 = "Haben Sie Interesse, Ihre Vermutungen zu überprüfen? Es wäre eine Ehre, Sie an Bord meines Schiffes zu haben, Gino. Packen Sie Ihre Sachen!";
			link.l1.go = "ksochitam_22";
		break;
		
		case "ksochitam_22":
			dialog.text = "Es wird nicht viel Zeit in Anspruch nehmen. Ich werde in ein paar Stunden fertig sein. Hier, nimm den Pfeil des Weges.";
			link.l1 = "Willkommen an Bord!";
			link.l1.go = "ksochitam_23";
		break;
		
		case "ksochitam_23":
			LAi_SetOwnerType(npchar);
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_24";
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetPlayerType(pchar);
			GiveItem2Character(pchar, "arrowway");
			pchar.questTemp.Ksochitam = "seekway";
			sld = ItemsFromID("skinmap");
			sld.mark = 1;
			pchar.quest.Ksochitam_room.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Ksochitam_room.win_condition.l1.location = pchar.location;
			pchar.quest.Ksochitam_room.function = "Ksochitam_JinoPassenger";
			AddQuestRecord("Ksochitam", "2");
		break;
		
		case "ksochitam_24":
			dialog.text = "Ja-ja, "+pchar.name+", Ich bereite mich vor. Ich werde bald fertig sein.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_24";
		break;
		
		case "ksochitam_25":
			dialog.text = "Na und, "+pchar.name+", haben wir Glück bei unseren Suchen?";
			link.l1 = "Wir hatten recht. Das ist es. Das indische Idol ist eine der Erscheinungen.";
			link.l1.go = "ksochitam_26";
		break;
		
		case "ksochitam_26":
			dialog.text = "Oh! Es muss eines dieser Idole sein, die angeblich Menschen nach Tayasal teleportieren sollten! Ich habe dir davon erzählt, erinnerst du dich? Also, wohin zeigt der Pfeil des Weges?";
			link.l1 = "Es zeigt nach Nordwesten. Ich habe die Richtung auf einer Karte markiert. Obwohl die gezeichnete Linie fast das gesamte karibische Meer überquert. Wir müssen eine andere Erscheinung auf Dominica finden, um Ksocheatem zu finden.";
			link.l1.go = "ksochitam_27";
		break;
		
		case "ksochitam_27":
			dialog.text = "Ich bin sicher, dass wir dort ein weiteres Idol finden werden... stimmst du meiner Hypothese zu, "+pchar.name+"?";
			link.l1 = "Ich tue es, Gino. Jetzt verschwenden wir keine Zeit und beginnen mit der Suche.";
			link.l1.go = "ksochitam_28";
		break;
		
		case "ksochitam_28":
			DialogExit();
			locations[FindLocation(pchar.location)].DisableEncounters = false; //энкаутеры открыть
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
		break;
		
		case "ksochitam_29":
			dialog.text = "Na und, "+pchar.name+", haben Sie etwas Interessantes gefunden?";
			link.l1 = "Wir lagen richtig. Das ist es. Das indische Idol ist eine der Erscheinungen.";
			link.l1.go = "ksochitam_30";
		break;
		
		case "ksochitam_30":
			dialog.text = "Oh! Es muss eine dieser Idole sein, die angeblich Menschen nach Tayasal teleportieren sollten! Ich habe dir davon erzählt, erinnerst du dich? Also, wo zeigt der Pfeil des Weges hin?";
			link.l1 = "Nordwest. Ich habe die Richtung auf einer Karte markiert. Obwohl die gezeichnete Linie fast das gesamte karibische Meer überquert. Wir müssen eine andere Erscheinung am Haupt finden, um Ksocheatem zu finden.";
			link.l1.go = "ksochitam_27";
		break;
		
		case "ksochitam_31":
			dialog.text = "Na und, "+pchar.name+", hast du das zweite Idol gefunden?";
			link.l1 = "Ja. Ich habe die Richtung gezeichnet, die der Wegpfeil gezeigt hat. Jetzt kennen wir den Standort von Ksocheatem, es ist nicht der genaue Standort, aber wir wissen, wo wir suchen müssen! Ich werde das gesamte Gebiet durchsuchen, wo sich die Linien kreuzen und ich werde diese verdammte Insel finden!";
			link.l1.go = "ksochitam_32";
		break;
		
		case "ksochitam_32":
			dialog.text = "Ich freue mich, so viel Begeisterung in deiner Stimme zu hören. Aber wir müssen uns gut auf die bevorstehende Expedition vorbereiten, es ist unbekannt, was wir dort antreffen werden. Ich bezweifle, dass wir dort einen herzlichen Empfang bekommen...";
			link.l1 = "Bist du wegen etwas Bestimmtem besorgt oder äußerst du nur Bedenken?";
			link.l1.go = "ksochitam_33";
		break;
		
		case "ksochitam_33":
			dialog.text = "Denk darüber nach, "+pchar.name+".. Ksocheatem wurde durch die Maya-Magie von Kanek erschaffen. Es ist keine natürliche Formation und es hat böse und zerstörerische Kräfte darauf. Es ist unbekannt, was uns dort erwartet, ich bezweifle, dass wir dort Sonnenschein, ruhige Meere, Huren und ruhigen Wind finden werden.";
			link.l1 = "Gut, Gino. Ich werde deine Worte bedenken und mich auf die Expedition vorbereiten. Ich werde mein Schiff bereitstellen und mich um Tränke und Munition kümmern...";
			link.l1.go = "ksochitam_34";
		break;
		
		case "ksochitam_34":
			dialog.text = "Sehr kluge Entscheidung. Nun, sollen wir zum Schiff zurückkehren?";
			link.l1 = "Sicher! Lass uns gehen!";
			link.l1.go = "ksochitam_28";
		break;
		
		case "ksochitam_35":
			dialog.text = "Wir sind angekommen, "+pchar.name+"! Uh, der Wind heult!";
			link.l1 = "Ja, Gino, du hattest recht, es gibt keine Sonne, die uns begrüßt... Ich sehe auch keine Huren. Tatsächlich ist es unbekannt, was hier überhaupt auf uns wartet.";
			link.l1.go = "ksochitam_36";
		break;
		
		case "ksochitam_36":
			dialog.text = "Nun, Sie haben einen so schlechten Ort zum Landen gewählt, Kapitän! Nur Felsen und Klippen überall! Und wie wollen Sie von hier aus ins Innere der Insel gelangen?";
			link.l1 = "Ich habe wegen diesem verdammt Sturm keine andere geeignete Bucht gesehen, um auf dieser Insel zu landen! Was auch immer, das ist besser als nichts. Ich werde meinen Weg zwischen diesen Felsen finden, ich habe Schlimmeres erlebt. Keine Panik, Freund!";
			link.l1.go = "ksochitam_37";
		break;
		
		case "ksochitam_37":
			dialog.text = "Ich mag diese Insel nicht, "+pchar.name+"! Es ist gruselig. Und dieser Sturm muss an die Insel gebunden sein. Dieser Ort ist verdammt, das ist sicher!";
			link.l1 = "Ich mag diesen Ort auch nicht wirklich, Gino! Aber diese Insel existiert, was bedeutet, dass die Geschichte von Kukulcan wahr ist. Wir werden alle in Gefahr sein, wenn er es schafft, mit der Maske nach Tayasal zu gelangen...";
			link.l1.go = "ksochitam_38";
		break;
		
		case "ksochitam_38":
			dialog.text = "Suchen Sie die Maske, Kapitän! Sie ist wichtiger als alle Schätze der Welt! Sie muss irgendwo hier sein! Sobald wir sie haben, werden wir Kukulkans Pläne zerstören und ihn nicht die Vergangenheit ändern lassen!";
			link.l1 = "Und wie sieht diese Maske aus, wissen Sie das?";
			link.l1.go = "ksochitam_39";
		break;
		
		case "ksochitam_39":
			dialog.text = "Keine Ahnung! Aber ich denke, dass du es erkennen wirst, es ist ein altes indisches Artefakt, es ist schwer, es mit etwas anderem zu verwechseln!";
			link.l1 = "Ich verstehe. Ich werde meine Augen offen halten! Gut, Gino, zurück zum Schiff! Du musst nicht um die Insel herumlaufen, dein Kopf ist zu wertvoll, um ihn zu riskieren!";
			link.l1.go = "ksochitam_40";
		break;
		
		case "ksochitam_40":
			dialog.text = "Ich werde nicht lügen, Kapitän, ich bin ein miserabler Kämpfer und fühle mich an diesem Ort nicht wohl. Möchten Sie einen Rat hören? Jede Komponente des Wächters ist mit der Magie dieser Insel verbunden. Ksatl Cha erwähnte, dass der Dolch Macht über die Einheimischen hat, ich weiß allerdings nicht, was er damit meinte.\nIch werde an Bord bleiben. Suchen Sie mich dort auf, wenn Sie meine Hilfe benötigen.";
			link.l1 = "Gut. Und wünsch mir jetzt Glück, Gino!";
			link.l1.go = "ksochitam_41";
		break;
		
		case "ksochitam_41":
			dialog.text = "Viel Glück, "+pchar.name+"! Möge Gott Sie begünstigen und bewahren!";
			link.l1 = "...";
			link.l1.go = "ksochitam_42";
		break;
		
		case "ksochitam_42":
			DialogExit();
			NextDiag.CurrentNode = "adversary";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "My_Campus", "quest", "quest1", "Ksochitam_JinoStay", 10.0);
			AddQuestRecord("Ksochitam", "6");
		break;
		
		case "adversary":
			dialog.text = "Wie geht es dir, "+pchar.name+"? Brauchen Sie einen Rat?";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L1"))
			{
				link.l1 = "Diese verfluchte Insel wimmelt nur so von Untoten und diese verdammten Skelette sind erstaunlich zäh. Ich habe keine Ahnung, wie ich gegen sie kämpfen soll.";
				link.l1.go = "adversary_1";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L2"))
			{
				link.l1 = "Wenn du an der Gabelung links abbiegst, kommst du schließlich zur Höhle. Aber wohin sollte ich als nächstes gehen? Ich fürchte, die Höhle ist eine Sackgasse...";
				link.l1.go = "adversary_2";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L3"))
			{
				link.l1 = "Ich habe meinen Weg in die nasse Höhle gefunden, du kannst in ihren Unterwasserteil eintauchen. Aber ich sehe keinen Ausgang von dort...";
				link.l1.go = "adversary_3";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L4"))
			{
				link.l1 = "Wenn du an der Gabelung nach links gehst, kommst du zur Höhle. Aber wohin sollte ich als nächstes gehen? Ich befürchte, dass die Höhle eine Sackgasse ist...";
				link.l1.go = "adversary_4";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L5"))
			{
				link.l1 = "Es gibt einen Ort in der großen Höhle, wo du in den überfluteten Teil eintauchen kannst. Aber es scheint, dass es keinen Ausweg von dort gibt...";
				link.l1.go = "adversary_5";
			}
			link.l10 = "Alles ist bisher in Ordnung, Gino, mir geht es gut.";
			link.l10.go = "exit";
			NextDiag.TempNode = "adversary";
		break;
		
		case "adversary_1":
			dialog.text = "Ksatl Cha erwähnte die Klaue des Häuptlings. Versuche sie gegen die Skelette zu verwenden, der Indianer sagte, dass dieser Dolch Macht über die Bewohner von Ksocheatem hat.";
			link.l1 = "Ich werde es sicher versuchen!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L1");
		break;
		
		case "adversary_2":
			dialog.text = "Und wie sieht diese Höhle aus?";
			link.l1 = "Nun, es gibt eine kleine Höhle in einem Felsen, sie ist nass und das Wasser schwappt auf dem Boden hin und her, genau wie die Brandung...";
			link.l1.go = "adversary_2_1";
		break;
		
		case "adversary_2_1":
			dialog.text = "Wenn das Wasser schwankt, dann hat die Höhle eine Verbindung zum Meer und es kann keine Sackgasse sein. Suchen Sie nach einem Durchgang, er muss da sein.";
			link.l1 = "Auf meinem Weg...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L2");
		break;
		
		case "adversary_3":
			dialog.text = "Wenn es einen Weg zur überfluteten Höhle aus der Hauptgrotte gibt und das Wasser in der Hauptgrotte wie eine Brandung schwappt, dann hat die überflutete Höhle einen zweiten Durchgang. Sucht besser danach, aber seid vorsichtig, oder ihr werdet ertrinken.";
			link.l1 = "Ich werde tauchen...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L3");
		break;
		
		case "adversary_4":
			dialog.text = "Und wie sieht diese Höhle aus?";
			link.l1 = "Nun, es ist ziemlich groß mit ein paar Höhlen, es ist nass und es gibt ein kleines Loch mit stillstehendem Wasser...";
			link.l1.go = "adversary_4_1";
		break;
		
		case "adversary_4_1":
			dialog.text = "Wenn das Wasser still ist, dann hat die Höhle keine Verbindung zum Meer und es könnte eine Sackgasse sein.";
			link.l1 = "Ich dachte dasselbe. Ich habe dort lange gesucht und es gibt nur einen Eingang, der auch ein Ausgang ist...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L4");
		break;
		
		case "adversary_5":
			dialog.text = "Wenn das Wasser noch in der Höhle ist, dann hast du vielleicht Recht. Such noch ein bisschen, aber sei nicht traurig, wenn du nichts findest. Es ist wahrscheinlich, dass es eine Sackgasse ist.";
			link.l1 = "Ich sehe...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L5");
		break;
		
		case "adversary_6":
			dialog.text = ""+pchar.name+", Spanische Schiffe sind hinter uns her! Es ist nicht die beste Zeit zu reden!";
			link.l1 = "Ja, sicher...";
			link.l1.go = "exit";
			NextDiag.TempNode = "adversary_6";
		break;
		
		case "ksochitam_43":
			dialog.text = "Deine glücklichen Augen sagen mir, dass du gefunden hast, wonach du gesucht hast.";
			link.l1 = "Ja. Die Schätze von Miguel Dichoso und die Maske von Kukulcan. Jetzt wird seine Inkarnation die Zukunft nie ändern können!";
			link.l1.go = "ksochitam_44";
		break;
		
		case "ksochitam_44":
			dialog.text = "Unglaublich! Du bist ein Held, "+pchar.name+"...";
			link.l1 = "Gino, bist du sicher, dass dies genug ist, um Kukulcan zu stoppen?";
			link.l1.go = "ksochitam_45";
		break;
		
		case "ksochitam_45":
			dialog.text = "Laut Ksatl Cha - ja. Und er zitierte Urakan. Sein Vater Kanek war es, der dieses ganze Durcheinander startete. Irgendwelche Zweifel?";
			link.l1 = "An der Bucht wurde ich von einem Gast aus der Vergangenheit getroffen - Alonso de Maldonado. Er war in Tayasal, als Kanek das Ritual zur Erschaffung des Wahrheitswächters vollzog. Er wurde in das Raum-Zeit-Loch gezogen, doch er blieb am Leben... Bis heute.";
			link.l1.go = "ksochitam_46";
		break;
		
		case "ksochitam_46":
			dialog.text = "";
			link.l1 = "Er sagte, dass ich das Portal selbst abschalten muss, um unsere Welt endgültig zu schützen. Um das zu tun, muss ich die Maske auf einem Altar in Tayasal zerstören.";
			link.l1.go = "ksochitam_47";
		break;
		
		case "ksochitam_47":
			dialog.text = "Und du wirst nach Tayasal gehen? Das ist Wahnsinn! "+pchar.name+", du hast die Maske und die Inkarnation von Kukulcan wird nichts tun können! Und Kanek selbst ist sich dessen sicher! Deshalb hat Urakan Ksatl Cha geschickt, um Ksocheatem zu finden - um die Maske zu bekommen und sie zu zerstören.";
			link.l1 = "Und was, wenn dieser Urakan vorhatte, die Maske in Tayasal zu zerstören?";
			link.l1.go = "ksochitam_48";
		break;
		
		case "ksochitam_48":
			dialog.text = ""+pchar.name+", nur ein Mann hat es bisher geschafft, lebend aus Tayasal zu entkommen, und das war Miguel Dichoso. Auch Maldonado, aber er war eine Ausnahme. Selbst wenn die Inkarnation von Kukulcan in die Vergangenheit gelangt, wird er von den alten Maya getötet!";
			link.l1 = "Was ist, wenn sie ihn nicht töten, sondern ihn erkennen?";
			link.l1.go = "ksochitam_49";
		break;
		
		case "ksochitam_49":
			dialog.text = "Planen Sie also eine Expedition nach Tayasal?";
			link.l1 = "Ich weiß nicht, Gino. Ich weiß wirklich nicht...";
			link.l1.go = "ksochitam_50";
		break;
		
		case "ksochitam_50":
			dialog.text = "Dann denk darüber nach, warum würdest du das tun? Du hast meine Meinung gehört. Jetzt liegt es an dir..."+pchar.name+", würden Sie mich nach St. John's bringen?";
			link.l1 = "Sicher, Gino. Lassen wir so schnell wie möglich in See stechen. Ich habe genug von dieser schrecklichen Insel.";
			link.l1.go = "ksochitam_51";
		break;
		
		case "ksochitam_51":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_52";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Ksochitam", "16");
			pchar.quest.Ksochitam_gohome.win_condition.l1 = "location";
			pchar.quest.Ksochitam_gohome.win_condition.l1.location = "sentjons_town";
			pchar.quest.Ksochitam_gohome.function = "Ksochitam_ArriveHome";
			pchar.questTemp.Ksochitam = "gohome";
		break;
		
		case "ksochitam_52":
			dialog.text = "Werden wir bald zu Hause sein, "+pchar.name+"? Ich vermisse wirklich meine Fläschchen und Röhren...";
			link.l1 = "Ja-ja, Gino, bald werden wir in Antigua sein.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_52";
		break;
		
		case "ksochitam_53":
			dialog.text = "Ich bin froh, dass wir endlich zurück sind! Ich kann mir nicht vorstellen, wie ihr, Seeleute, so viel Zeit auf euren Schiffen verbringt...";
			link.l1 = "Es ist eine Frage der Gewohnheit, Gino.";
			link.l1.go = "ksochitam_54";
		break;
		
		case "ksochitam_54":
			dialog.text = "Ich werde mich mit großem Vergnügen auf mein Bett legen, das auf festem Boden steht... Ich hoffe, "+pchar.name+", dass Sie den Gedanken aufgegeben haben, Tayasal zu besuchen?";
			link.l1 = "Ich weiß es noch nicht, Gino. Um ehrlich zu sein, bin ich mir immer noch nicht sicher.";
			link.l1.go = "ksochitam_55";
		break;
		
		case "ksochitam_55":
			dialog.text = "Zerstöre die Maske von Kukulcan und lebe ohne Sorgen, Kapitän. Wenn du willst, werden wir die Maske in der stärksten Säure auflösen, die ich habe. Ich werde dir deswegen keinen Groll hegen.";
			link.l1 = "Sie wissen, ich werde eine Weile warten. Wir werden immer Zeit haben, es zu zerstören.";
			link.l1.go = "ksochitam_56";
		break;
		
		case "ksochitam_56":
			dialog.text = "Es ist Ihre Entscheidung. Wenn Sie sich entscheiden, diese Welt vor diesem Artefakt zu verschonen - kommen Sie zu mir. Dankbarkeit für eine wunderbare Reise, Kapitän!";
			link.l1 = "Jederzeit, Gino. Wir sehen uns!";
			link.l1.go = "exit";
			NextDiag.TempNode = "first time";
			AddDialogExitQuestFunction("Ksochitam_TripComplete");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Du bist ein "+GetSexPhrase("Dieb, Herr! Wachen, nehmt ihn","Dieb, Mädchen! Wachen, nehmt sie ")+"!!!","Nur schau dir das an! Kaum war ich in Gedanken versunken, hast du dich entschieden, meine Truhe zu durchsuchen! Fangt den Dieb!!!","Wachen! Raub! Ergreift den Dieb!!!");
			link.l1 = "Verdammt!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
