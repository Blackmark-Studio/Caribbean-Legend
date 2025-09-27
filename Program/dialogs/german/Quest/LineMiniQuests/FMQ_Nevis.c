// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ein offensichtlicher Fehler. Sag es den Entwicklern.";
			link.l1 = "Oh, ich werde es tun.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "seafox":
			DelMapQuestMarkCity("Charles");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			PlaySound("Voice\English\LE\SeaFox\SeaFox_01.wav");
			dialog.text = TimeGreeting()+", Kapitän. (grüßt) Darf ich mich vorstellen - Leutnant "+GetFullName(npchar)+", Antigua Maritimes Fußregiment, stationiert in St. Johns. Ich habe eine Bitte.";
			link.l1 = "Grüße Leutnant Gretton. Mein Name ist "+GetFullName(pchar)+". Was für einen Gefallen?";
			link.l1.go = "seafox_1";
		break;
		
		case "seafox_1":
			dialog.text = "Lassen Sie mich die Situation kurz erläutern. Vier meiner Männer und ich segelten von St. Johns nach Sint-Maarten, als ein Sturm unser Schiff traf. Das schlechte Wetter dauerte nicht lange, aber es reichte aus, damit unsere alte Badewanne ein Leck bekam. Wir mussten den Kurs ändern und hier für Reparaturen anlegen. Das nimmt uns wertvolle Zeit, die wir nicht haben\nWir müssen dringend nach Sint-Maarten, genauer gesagt zum Grand Case Beach. Helfen Sie mir, Kapitän, und es wird sich für Sie sehr lohnen. Zwei Tage Reise für großzügige Bezahlung!";
			link.l1 = "Es sollte in der Tat eine großzügige Bezahlung sein, Leutnant, wenn Sie möchten, dass ich heimlich englische Marines auf einer holländischen Insel einsetze.";
			link.l1.go = "seafox_2";
		break;
		
		case "seafox_2":
			dialog.text = ""+UpperFirst(GetAddress_Form(PChar))+", das sollte Sie nicht beunruhigen. Sie sind nicht in Gefahr. Bringen Sie uns einfach in die Bucht, das ist alles. Na, einverstanden?";
			link.l1 = "Gut, ich bin dabei. Es ist nicht weit von hier. Lass uns über die Bezahlung sprechen.";
			link.l1.go = "seafox_3";
			link.l2 = "Es tut mir leid, aber ich habe dringende Geschäfte in einer anderen Richtung und ich möchte die Holländer lieber nicht verärgern.";
			link.l2.go = "seafox_exit";
		break;
		
		case "seafox_exit":
			dialog.text = "Wie Sie sagen, Kapitän. Ich werde dann weiter suchen. Lebewohl und Gottes Segen!";
			link.l1 = "Auf Wiedersehen, Leutnant.";
			link.l1.go = "seafox_exit_1";
		break;
		
		case "seafox_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
		break;
		
		case "seafox_3":
			GiveItem2Character(pchar, "purse2"); 
			Log_Info("You have received a purse of doubloons");
			dialog.text = "Zehntausend Dublonen. Hier ist eine Anzahlung.";
			link.l1 = "Gut. Bring deine Männer an Bord, wir wollen keine Zeit verschwenden.";
			link.l1.go = "seafox_4";
		break;
		
		case "seafox_4":
			dialog.text = "Aye aye, Kapitän!";
			link.l1 = "..., Freund.";
			link.l1.go = "seafox_5";
		break;
		
		case "seafox_5":
			DialogExit();
			AddQuestRecord("FMQ_Nevis", "1");
			pchar.questTemp.FMQN = "begin";
			
			chrDisableReloadToLocation = false;
			sld = CharacterFromID("FMQN_seafox_1");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", "", "", "", "", 10.0); // англичане на борт
			sld.location = "None";
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.FMQN_sailing.win_condition.l1 = "location";
			pchar.quest.FMQN_sailing.win_condition.l1.location = "Shore40";
			pchar.quest.FMQN_sailing.win_condition.l2 = "Ship_location";
			pchar.quest.FMQN_sailing.win_condition.l2.location = "Shore40";
			pchar.quest.FMQN_sailing.function = "FMQN_ArriveMaarten";
			if(bImCasual)
			{
				NewGameTip(StringFromKey("FMQ_69"));
			}
			else SetFunctionTimerCondition("FMQN_SailingLate", 0, 0, 10, false);
			for(i = 0; i < MAX_LOCATIONS; i++)
			{	
				sld = &Locations[i];
				if (CheckAttribute(sld, "islandId") && sld.islandId == "SentMartin")
				{
					sld.DisableEncounters = true;	
				}
			}
			sld = &Locations[FindLocation("Shore40")];
			sld.QuestlockWeather = "23 Hour";
			AddMapQuestMarkShore("Shore40", true);
		break;
		
		case "seafox_6":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "Vielen Dank für die reibungslose Fahrt, Kapitän! Es tut mir sehr leid, aber ich kann Ihnen in diesem Moment nicht bezahlen ... es sollte in dieser Gegend eine unserer Schaluppen sein, aber sie ist nicht da. Wie Sie deutlich sehen können. Ich muss Sie noch einmal um Ihre Hilfe bitten. Könnten Sie zwei oder drei Tage in dieser Bucht warten? Wir müssen uns umsehen. Sobald wir zurückkommen, bringen Sie uns nach Antigua. Oberst Fox wird Sie großzügig belohnen.";
			link.l1 = "Hm... Das ist nicht ganz das, was wir vereinbart hatten...";
			link.l1.go = "seafox_7";
		break;
		
		case "seafox_7":
			dialog.text = "Bitte seien Sie nicht frustriert, Kapitän. Ich weiß, wie Sie sich fühlen müssen, aber leider: Ich habe überhaupt kein Geld. Ich kann Ihnen versprechen, dass Sie eine Entschädigung für beide Reisen und für das Warten auf uns hier erhalten werden. Sowie den Dank von Oberst Fox persönlich!";
			link.l1 = "Ich kann Sie nicht gerade im Stich lassen... Also gut, Lieutenant Gretton. Ich werde drei Tage warten, aber nicht länger.";
			link.l1.go = "seafox_8";
		break;
		
		case "seafox_8":
			dialog.text = "Danke, "+GetAddress_Form(NPChar)+"! Wir gehen ins Landesinnere. Ich schwöre, wir werden in 72 Stunden zurück sein, nicht eine Minute länger.";
			link.l1 = "Gottes Segen, Leutnant. Lassen Sie sich nicht erwischen.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglishmanGo");
		break;
		
		case "seafox_9":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "Welch ein Zufallstreffen! Ich dachte, Sie würden am Grand Case Strand auf uns warten, Kapitän "+pchar.lastname+"!";
			link.l1 = "Hallo Leutnant, die Überraschung ist gegenseitig. Ich hätte nicht erwartet, dich in einer holländischen Soldatenuniform zu sehen.";
			link.l1.go = "seafox_10";
		break;
		
		case "seafox_10":
			dialog.text = "Es ist unsere Tarnung... Warum seid Ihr hier draußen, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Das ist eine gefährliche Verkleidung, Kamerad. Spione können ohne Prozess hingerichtet werden. Und wenn wir schon von Hinrichtung sprechen, wenn du deine vermeiden willst, hörst du besser zu.";
			link.l1.go = "seafox_11";
		break;
		
		case "seafox_11":
			dialog.text = "Sie haben meine ungeteilte Aufmerksamkeit.";
			link.l1 = "Ich bin nach Philipsburg gesegelt und habe mit den Einheimischen gesprochen, nachdem du von Bord gegangen bist. Die Holländer haben Wind von dir bekommen. Sie wissen von deiner Mission, die gefangenen hochrangigen englischen Offiziere zu retten.";
			link.l1.go = "seafox_12";
		break;
		
		case "seafox_12":
			dialog.text = "Verdammt und zugenäht! Wie zur Hölle haben sie davon erfahren?";
			link.l1 = "Einer der gefangenen englischen Offiziere. Im Austausch für seine Freiheit hat er den Niederländern alles erzählt, was er über die Rettungsaktion wusste. Ganz Philipsburg ist bereit für dich und deine Männer, um zu versuchen, die Stadt zu betreten. Um die Sache noch schlimmer zu machen, patrouilliert eine niederländische Korvette das Meer um Sint-Maartin. Es ist eine Falle, Leutnant.";
			link.l1.go = "seafox_13";
		break;
		
		case "seafox_13":
			dialog.text = RandSwear()+"Dieser unehrenhafte Schurke! Ich werde herausfinden, wer dieser Verräter ist und ihn vor dem Parlament anprangern!";
			link.l1 = "Das muss warten, Herr Gretton. Kehren Sie heute Nacht zurück zum Grand Case Beach und kommen Sie auf mein Schiff, bevor sie Sie erwischen.";
			link.l1.go = "seafox_14";
		break;
		
		case "seafox_14":
			dialog.text = "Und englische Gentlemen in einem holländischen Gefängnis zurücklassen? Ich würde lieber sterben, Herr. Ich werde Oberst Fox nicht im Stich lassen.";
			link.l1 = "Hm, glaubst du, die Holländer lassen dich wählen zwischen dem Galgen und einem Erschießungskommando, nachdem sie dich gefangen genommen haben?";
			link.l1.go = "seafox_15";
		break;
		
		case "seafox_15":
			dialog.text = "Denken Sie nicht, dass sie Sie einfach so segeln lassen, Kapitän de Maure. Wir stecken beide bis zum Hals drin.";
			link.l1 = "Verdammt, du hast wahrscheinlich recht. Diese Korvette wird uns überfallen, sobald wir den Anker lichten...";
			link.l1.go = "seafox_16";
		break;
		
		case "seafox_16":
			dialog.text = "Die Holländer wissen vielleicht, dass wir kommen, aber sie wissen nicht *wie* wir kommen. Wir haben uns bereits um die Verkleidung gekümmert - schau dir diese Uniform an. Schön, oder? Hätte unser Plan nicht verraten worden, wären wir einfach ins örtliche Gefängnis gegangen, hätten sie überrascht und jeden darin getötet. Aber sie lauern sicherlich dort auf uns. Also improvisieren wir\nKapitän, geh zur Kirche von Philipsburg und finde dort einen Prediger namens Filippe Jacobsen. Er sollte von sechs bis zehn Uhr morgens dort sein. Filippe ist einer unserer Männer von innen\nSag ihm dieses Passwort: 'Wie lange ist es her, dass die gefangenen Seeleute gestanden haben?'. Danach erzähle ihm von der Situation und fordere seine Unterstützung im Namen von Colonel Fox. Dann bringst du seine Antwort zu mir. Einfach und kein Risiko für dich.";
			link.l1 = "Hört sich ziemlich verdammt riskant an, in einer niederländischen calvinistischen Kirche nach Beichte zu fragen, Leutnant. Der Pastor wird versuchen, mich als Papisten zu hängen. Gut, erzähl mir von diesen Uniformen... hast du das von einer niederländischen Patrouille genommen?";
			link.l1.go = "seafox_17";
		break;
		
		case "seafox_17":
			dialog.text = "Ja, Herr.";
			link.l1 = "Und wo sind sie jetzt?";
			link.l1.go = "seafox_18";
		break;
		
		case "seafox_18":
			dialog.text = "Gefangen gehalten als Geiseln im Gebüsch nicht weit entfernt von dieser Höhle.";
			link.l1 = "Verstanden. Halte sie sicher, ich gehe in die Stadt. Warte hier auf mich und halte dich bedeckt - die Holländer durchkämmen sowohl den Dschungel als auch die Meere auf der Suche nach dir.";
			link.l1.go = "seafox_19";
		break;
		
		case "seafox_19":
			dialog.text = "Wir werden still sein wie Kirchenmäuse, Kapitän. Bitte beeilen Sie sich!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ToChurch");
		break;
		
		case "seafox_20":
			PlaySound("Voice\English\soldier_common_4.wav");
			DelLandQuestMark(npchar);
			dialog.text = "Du bist zurück? Kapitän, was machst du hier? Geh in die Stadt, du lenkst Aufmerksamkeit auf unser Versteck!";
			link.l1 = "Ich bin zurück aus der Stadt. Welche Art von Spielen spielt ihr Engländer?";
			link.l1.go = "seafox_21";
		break;
		
		case "seafox_21":
			dialog.text = "Entschuldigung?";
			link.l1 = "Ich ging zur Kirche. Großes Gebäude, schön und schlicht, genau so wie es diese niederländischen Bilderstürmer mögen. Rate mal, Leutnant? Es gibt keinen Prediger namens Filippe Jacobsen.";
			link.l1.go = "seafox_22";
		break;
		
		case "seafox_22":
			dialog.text = "Das ist unmöglich, er besucht den Ort jeden Morgen-";
			link.l1 = "Halt die Klappe und hör zu! Wenn dein Jacobsen überhaupt existiert, dann geht er nicht in die Kirche! Sie haben ihn nie gesehen! Weder morgens noch abends! Gott verdammt noch mal! Warum habe ich überhaupt diesem verdammten Job zugestimmt?! Geführt von einem dämlichen Hurensohn Grünschnabel Idiot nass hinter den Ohren Leutnant-";
			link.l1.go = "seafox_23";
		break;
		
		case "seafox_23":
			dialog.text = "Herr, ich verlange Genugtuung für diese Beleidigung. Sobald wir hier raus sind, werden wir uns nach den Bräuchen duellieren-";
			link.l1 = ""+RandSwear()+"";
			link.l1.go = "seafox_24";
		break;
		
		case "seafox_24":
			PlaySound("Ambient\Jail\chain.wav");
			PlaySound("Ambient\Land\door_001.wav");
			dialog.text = "Schweigt endlich alle!!! ... Ich habe gerade etwas gehört.";
			link.l1 = "";
			link.l1.go = "seafox_25";
		break;
		
		case "seafox_25":
			if (pchar.sex == "man") {PlaySound("VOICE\English\LE\SeaFox\SeaFox_04.wav");}
			dialog.text = "Potztausend, jemand ist draußen! Du! Du hast die Holländer hierher gebracht, du Schurke!";
			link.l1 = ""+RandSwear()+"!!!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleFight");
		break;
		
		case "seafox_26":
			DelLandQuestMark(npchar);
			pchar.quest.FMQN_fail1.over = "yes";
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "Freut mich, Sie zu sehen, Sir, welche Neuigkeiten?";
			link.l1 = "Ich habe Ihren Mann getroffen. Heute Abend wird er etwas 'gewürzten' Wein an die Gefängnisgarnison liefern. Er hat einen Trank von einer Zigeunerin bekommen, nicht tödlich, aber sie werden schlafen wie die Toten. Ihr müsst heute Nacht dort reinkommen und Eure gefangenen Herren rausholen. Übrigens hat mich diese Weinlieferung fünfundzwanzig Dublonen gekostet. Vergiss nicht, das im Bericht zu erwähnen.";
			link.l1.go = "seafox_27";
		break;
		
		case "seafox_27":
			dialog.text = "Mach dir keine Sorgen um das Geld. Kapitän, ich würde dich bitten, uns bei dieser Operation zu unterstützen und uns den Weg zum Gefängnis zu zeigen. Du warst schon in Philipsburg, also kennst du die Stadt besser als wir. Du musst nicht mit uns ins Gefängnis gehen, wir werden den Ausbruch selbst durchführen. Bring uns einfach zur Tür.";
			link.l1 = "Verdammt noch mal Mr. Gretton, diese Arbeit wird immer besser und besser. Die Bezahlung sollte dementsprechend steigen.";
			link.l1.go = "seafox_28";
		break;
		
		case "seafox_28":
			dialog.text = "Das ist es ganz sicher, Kapitän. Sie werden es nicht bereuen, uns zu helfen. Ist Ihr Schiff am Grand Case Beach?";
			if (pchar.location.from_sea == "Shore40")
			{
				link.l1 = "Jawohl.";
				link.l1.go = "seafox_29";
			}
			else
			{
				link.l1 = "Nein.";
				link.l1.go = "seafox_29x";
			}
		break;
		
		case "seafox_29":
			dialog.text = "Gut. Dann mach dich bereit und triff uns um elf Uhr abends am Stadttor.";
			link.l1 = "Bis dort.";
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_29x":
			dialog.text = "Sei sicher, sie dorthin zu bewegen, denn wir müssen unsere Männer durch den Dschungel hinausbringen. Eine Abfahrt vom Hafen oder der Simpson Bay ist wegen der Festung unmöglich. Mach alles fertig und triff uns um elf Uhr abends am Stadttor.";
			link.l1 = "Bis dort.";
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_30":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("FMQN_EnglandPrepare");
		break;
		
		case "seafox_31":
			PlaySound("Voice\English\Gr_hovernor01.wav");
			dialog.text = "Bereit, Kapitän?";
			link.l1 = "Ja.";
			link.l1.go = "seafox_32";
		break;
		
		case "seafox_32":
			dialog.text = "Lass uns dann loslegen.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglandReload");
		break;
		
		case "seafox_33":
			dialog.text = "Huschhh... Kapitän! Es ist erledigt, lass uns zum Teufel hier raus!..";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToJungle");
		break;
		
		case "seafox_34":
			dialog.text = "Ich weiß nicht, wie wir das geschafft haben, aber wir haben es getan! Ohne Ihre Hilfe, "+GetAddress_Form(NPChar)+", wäre nichts davon möglich gewesen. Jetzt zum vergleichsweise einfachen Teil - wir müssen lebend und in einem Stück von Sint-Maartin wegkommen. Auf nach Grand Case Beach!";
			link.l1 = "Lass uns losgehen!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToShore");
		break;
		
		case "seafox_35":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_05.wav");
			dialog.text = "Kapitän "+pchar.lastname+"... "+GetAddress_Form(NPChar)+", danke für Ihre Hilfe! Ich bitte Sie, verlassen Sie den Hafen nicht sofort, sondern bleiben Sie noch einen Tag hier, während ich Colonel Fox Bericht erstatte. Besuchen Sie ihn morgen, sein Büro befindet sich im Gouverneurspalast.";
			link.l1 = "Sehr gut, Leutnant Gretton. Bitte sorgen Sie dafür, dass es sich lohnt. Es wird viel Zeit kosten, meinen Ruf bei den Holländern wegen Ihrer Eskapade zu reparieren.";
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_35x":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_05.wav");
			dialog.text = "Danke für deine Hilfe, Kapitän! Ihr "+GetSexPhrase("habt euch wie ein wahrer Held verhalten","seid ein sehr tapferes Fräulein")+", "+GetAddress_Form(NPChar)+"! Es ist eine Tragödie, dass Leutnant Gretton es nicht geschafft hat. Er starb als wahrer Gentleman und Sohn Englands. Ich bitte darum, hier noch einen weiteren Tag zu bleiben, während ich Oberst Fox Bericht erstatten. Besuche ihn morgen, sein Büro befindet sich im Gouverneurspalast.";
			link.l1 = "Sehr gut. Bitte sorge dafür, dass es sich für mich lohnt. Es wird lange dauern, meinen Ruf bei den Holländern wegen deiner Eskapade zu reparieren.";
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_36":
			dialog.text = "Machen Sie sich keine Sorgen, "+GetAddress_Form(NPChar)+". Ich werde Ihnen in meinem Bericht das höchstmögliche Lob aussprechen. (salutiert) Es war mir ein Vergnügen, "+GetAddress_Form(NPChar)+"!";
			link.l1 = "...";
			link.l1.go = "seafox_37";
		break;
		
		case "seafox_37":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", -1);
			pchar.quest.FMQN_eng_reward.win_condition.l1 = "Timer";
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_eng_reward.function = "FMQN_EnglandReward";
			AddQuestRecord("FMQ_Nevis", "28");
		break;
		
		case "soldier":
			PlaySound("Voice\English\soldier_common_2.wav");
			dialog.text = "Kapitän "+GetFullName(pchar)+"?";
			link.l1 = "Hm... Ja, was kann ich für Sie tun?";
			link.l1.go = "soldier_1";
		break;
		
		case "soldier_1":
			dialog.text = "Das Hafenamt hat uns über die kürzliche Ankunft Ihres Schiffes informiert. Seine Exzellenz Mynheer Martin Thomas, der Gouverneur von Philipsburg, wünscht Sie zu sehen.";
			link.l1 = "Wofür? Bin ich verhaftet?";
			link.l1.go = "soldier_2";
		break;
		
		case "soldier_2":
			AddLandQuestMark(characterFromId("Marigo_Mayor"), "questmarkmain");
			dialog.text = "Ach nein, nein, "+GetAddress_Form(NPChar)+" Kapitän, Sie sind nicht festgenommen. Der Gouverneur hat befohlen, jeden neu angekommenen Kapitän in seinen Palast zum Kaffee und zur Vorstellung einzuladen. Folgen Sie mir!";
			link.l1 = "Hört sich an wie ein Angebot, das ich nicht ablehnen kann. Führen Sie den Weg.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ReloadToGovernor");
		break;
		
		case "hol_officer":
			PlaySound("Voice\English\hol_gov_complete.wav");
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", zeigen Sie uns, wo Sie diese englischen Soldaten gesehen haben.";
			link.l1 = "Sie verstecken sich in einer Höhle im Dschungel, wie gewöhnliche Banditen.";
			link.l1.go = "hol_officer_1";
		break;
		
		case "hol_officer_1":
			dialog.text = "Führe uns an, wir folgen dir!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleMarch");
		break;
		
		case "hol_officer_2":
			PlaySound("Voice\English\hol_gov_quest.wav");
			dialog.text = "Warte Kapitän! Du hast erwähnt, dass du die Spione dort getroffen hast - in der Nähe des Höhleneingangs?";
			link.l1 = "Ja. Ich habe sie kurz gesehen, wie sie hineingingen, nachdem sie mit mir gesprochen hatten.";
			link.l1.go = "hol_officer_3";
		break;
		
		case "hol_officer_3":
			dialog.text = "Höchstwahrscheinlich sind sie immer noch da drin. Wenn wir alle auf einmal angreifen, werden sie sich in die Höhle zurückziehen. Es wird ein Albtraum sein, sie von dort herauszuholen... Lassen Sie uns klug vorgehen. Kapitän, Sie gehen alleine dorthin und lenken sie ab. Meine Männer und ich werden zu diesem trockenen Brunnen um die Ecke gehen. Er führt direkt in die Höhle. Die Bastarde werden uns nicht von hinten kommen sehen\nSie gehen hinein und wenn die Spione noch dort sind, sprechen Sie mit ihnen, stellen Sie ihnen dumme Fragen und halten Sie sie beschäftigt. Sobald Sie ihre volle Aufmerksamkeit haben - fluchen Sie so obszön wie Sie können. Sie sind ein Seemann, also sollte Ihnen das natürlich kommen. Das wird unser Signal sein. Zwei meiner Männer werden den Haupteingang bewachen, um ihre Flucht auf diesem Weg zu verhindern. Wir werden sie kriegen.";
			link.l1 = "Dein Plan klingt äußerst gefährlich für meine Gesundheit. So wie ich das sehe, werden sie einfach versuchen, mich zuerst zu töten.";
			link.l1.go = "hol_officer_4";
		break;
		
		case "hol_officer_4":
			dialog.text = "Mach dir keine Sorgen, Kapitän. Deine Aufgabe ist es, so laut wie möglich zu schreien, sobald du die feindliche Plünderungspartei siehst. Wenn sie dich angreifen - dann renne und schreie weiter. Meine Männer sind gut ausgebildet, also mach dir keine Sorgen, sie werden diese Spione erledigen, bevor du verletzt wirst.";
			link.l1 = "Sie sollten besser. Ich gehe da rein.";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattlePosition");
		break;
		
		case "hol_officer_5":
			PlaySound("Voice\English\hol_gov_common.wav");
			dialog.text = "Zähe Bastarde waren sie... Gut gemacht, Kapitän, die englischen Hunde sind ausgelöscht. Die Saboteure wurden beseitigt, der Kommandant und der Gouverneur werden zufrieden sein.";
			link.l1 = "Sie haben sich Ihre süße Zeit genommen, Mynheer...";
			link.l1.go = "hol_officer_6";
		break;
		
		case "hol_officer_6":
			dialog.text = "Verflucht sei das Seil, es hatte einen Eimer am Ende, der einen unglaublichen Lärm machte. Wir mussten vorsichtig sein.";
			link.l1 = "Ja...das Seil. Was auch immer. Eine eurer fehlenden Patrouillen ist dort drüben in den Büschen gefesselt. Sie sollten noch am Leben sein.";
			link.l1.go = "hol_officer_7";
		break;
		
		case "hol_officer_7":
			dialog.text = "Ich werde mich um sie kümmern. Du solltest in die Stadt gehen und dich etwas ausruhen. Besuche morgen unseren Gouverneur, er wird dann meinen Bericht mit einer glänzenden Empfehlung für dich haben.";
			link.l1 = "Ich werde das tun. Gott beschütze Sie, Mynheer.";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleRest");
		break;
		
		case "monk":
			DelLandQuestMark(npchar);
			DelLandQuestMarkToPhantom();
			if (GetCharacterIndex("marigojailoff") != -1)
			{
				DelLandQuestMark(characterFromId("marigojailoff"));
			}
			pchar.questTemp.FMQN = "way_eng_2";
			dialog.text = "Was kann ich für dich tun, mein Sohn?";
			link.l1 = "Hallo Pastor, aus reiner Neugier, wie lange ist es her, dass die gefangenen Matrosen gestanden haben?";
			link.l1.go = "monk_1";
		break;
		
		case "monk_1":
			dialog.text = "Gestern Abend, mein Sohn... (flüstert) Ich nehme an, du weißt, dass der Plan verraten wurde?";
			link.l1 = "Ich würde sonst nicht hier stehen. Leutnant Casper Gratton und seine Männer sind gerade im Dschungel. Sie sind alle wie holländische Soldaten gekleidet, aber wir brauchen zusätzliche Unterstützung, da die Gefängniswärter auf sie warten.";
			link.l1.go = "monk_2";
		break;
		
		case "monk_2":
			dialog.text = "(laut) Ich betete jeden Tag, um seine anglikanische Seele vor der Verdammnis zu retten! (flüstert) Ich habe einen Plan, aber ich brauche zwei Dutzend goldene Dublonen, um alles zu bekommen, was ich brauche.";
			link.l1 = "Teurer Plan. Wofür ist das Geld?";
			link.l1.go = "monk_3";
		break;
		
		case "monk_3":
			dialog.text = "Als Gefängniswächter zu dienen, ist eine langweilige Pflicht. Um die Moral zu stärken, bestellt der verantwortliche Offizier jeden Abend etwas Wein zum Abendessen. Der Wein wird aus einem Lagerhaus gebracht, zu dem ich Zugang habe. Es gibt eine Zigeunerin in der Stadt, die mir verpflichtet ist, sie wird uns einen Schlaftrunk herstellen. Alles, was ich tun muss, ist ein paar Flaschen guten Wein zu kaufen, den Trank hinzufügen und die Flaschen im Lagerhaus austauschen. Deshalb brauche ich das Gold.";
			if (PCharDublonsTotal() >= 24)
			{
				link.l1 = "Ich habe die Dublonen. Nimm sie.";
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = "Lass mich zurück zu meinem Schiff gehen und etwas für dich holen.";
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_wait":
			DialogExit();
			npchar.dialog.currentnode = "monk_repeat";
		break;
		
		case "monk_repeat":
			dialog.text = "Ach mein Sohn, hast du die 'Spende', über die wir gesprochen haben?";
			if (PCharDublonsTotal() >= 24)
			{
				link.l1 = "Ja, hier.";
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = "Ich werde es bald genug bekommen...";
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_4":
			RemoveDublonsFromPCharTotal(24);
			dialog.text = "Prächtig. Komm morgen zur gleichen Zeit zu mir - Ich werde dir die Ergebnisse mitteilen.";
			link.l1 = "Sehr gut...";
			link.l1.go = "monk_5";
		break;
		
		case "monk_5":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("FMQ_Nevis", "18");
			pchar.quest.FMQN_monk.win_condition.l1 = "Timer";
			pchar.quest.FMQN_monk.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_monk.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_monk.function = "FMQN_EnglandMonkPlan";
			pchar.quest.FMQN_fail.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail.win_condition.l1.date.hour  = 11.0;
			pchar.quest.FMQN_fail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_fail.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_3";
		break;
		
		case "monk_6":
			DelLandQuestMark(npchar);
			pchar.quest.FMQN_fail.over = "yes";
			dialog.text = "Grüße, mein Sohn.";
			link.l1 = "Gleichfalls, Pastor. Irgendwelche Neuigkeiten?";
			link.l1.go = "monk_6x";
		break;
		
		case "monk_6x":
			dialog.text = "Ja. Es ist erledigt. Der Wein wurde 'gewürzt' und die Wachen bekommen heute Abend eine besondere Leckerei. Sie essen um neun Uhr abends, sie schlafen alle um Mitternacht. Das ist deine einzige Chance, die Arbeit zu erledigen, keine zweiten Chancen. Sei vorsichtig, du kannst dich nicht vollständig auf deine niederländische Tarnung verlassen.";
			link.l1 = "Hab's. Lassen wir keine Zeit verschwenden. Lebewohl.";
			link.l1.go = "monk_7";
		break;
		
		case "monk_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("FMQ_Nevis", "20");
			sld = CharacterFromID("FMQN_seafox_1");
			sld.dialog.currentnode = "seafox_26";
			LAi_CharacterEnableDialog(sld);
			sld.talker = 9;
			AddLandQuestMark(sld, "questmarkmain");
			pchar.quest.FMQN_fail1.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail1.win_condition.l1.date.hour  = 20.0;
			pchar.quest.FMQN_fail1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.FMQN_fail1.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_4";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
