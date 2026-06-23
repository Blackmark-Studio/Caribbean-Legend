// Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
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
		
		case "girl":
			DelMapQuestMarkCity("Tortuga");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			FMQT_FillChest();
			PlaySound("Voice\English\Girls_1.wav");
			dialog.text = "Oh, hallo Monsieur! Willkommen in Tortuga! So edle Kapitäne wie Sie sind hier selten Gäste...";
			link.l1 = "Grüße, Mademoiselle. Danke für den herzlichen Empfang. Aber wie kommt's? Ich dachte, dass ein so wichtiger Hafen immer ein Ort von Interesse für Glücksritter viel edler als ich wäre.";
			link.l1.go = "girl_1";
		break;
		
		case "girl_1":
			dialog.text = "Ach, Monsieur... Sie sind offensichtlich ein Neuling, habe ich recht? Sie werden es selbst sehen. Sie haben keine Ahnung, wie schwer es ist, würdige Männer für eine Tanzparty im Gouverneurspalast zu finden. Vielleicht könnten Sie mich begleiten...?";
			link.l1 = "Wie kann ich einer so schönen Frau behilflich sein?";
			link.l1.go = "girl_2";
		break;
		
		case "girl_2":
			dialog.text = "Ach du meine Güte, solche Galanterie! (kichert) Vielleicht könnten Sie uns um sechs Uhr heute Abend besuchen? Die Frau unseres Gouverneurs veranstaltet regelmäßig informelle Partys in den Dienerschaftswohnungen des Palastes. Es ist eine seltene Gelegenheit für uns, interessante Gesellschaft für solche Veranstaltungen zu haben. Werden Sie uns besuchen? Bitte kommen Sie, wir würden uns sehr freuen.";
			link.l1 = "Es wäre mir eine Ehre, Mademoiselle. Ich werde Sie heute Abend besuchen.";
			link.l1.go = "girl_3";
			link.l2 = "Verzeihen Sie mir, Mademoiselle, aber ich habe dringende Geschäfte zu erledigen. Vielleicht ein anderes Mal?";
			link.l2.go = "girl_exit";
		break;
		
		case "girl_exit":
			dialog.text = "Schade. Ich muss jemand anderen finden, der mich und meine Freundinnen... Gesellschaft leistet. Auf Wiedersehen.";
			link.l1 = "Auf Wiedersehen.";
			link.l1.go = "girl_exit_1";
		break;
		
		case "girl_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			FMQT_ClearChest();
		break;
		
		case "girl_3":
			dialog.text = "Danke! Ich verspreche Ihnen, das wird eine Nacht, die Sie nie vergessen werden, Herr! Auf Wiedersehen!";
			link.l1 = "Bis dann...";
			link.l1.go = "girl_4";
		break;
		
		case "girl_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "begin_serveroom";
			FMQT_Begin();
			AddQuestRecord("FMQ_Tortuga", "1");
		break;
		
		case "girl_5":
			DelMapQuestMarkCity("Tortuga");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			FMQT_FillChest();
			PlaySound("Voice\English\Girls_1.wav");
			dialog.text = "Hallo dort Seemann! Welcher glückliche Wind hat dich heute hierher geweht? Wir sehen selten solch feine Männer in Tortuga.";
			link.l1 = "Hallo auch Ihnen, Mademoiselle, Sie sind in der Lage, mich mit Ihren Komplimenten erröten zu lassen. Ich bin Kapitän meines eigenen Schiffes und ein beschäftigter Mann, aber ich bin sicher, dass diese Insel genug zu bieten hat, um einen wilden Streuner wie mich zu unterhalten.";
			link.l1.go = "girl_6";
		break;
		
		case "girl_6":
			dialog.text = "(kichern) Oh ja, Herr, ich bin sicher, wir können dabei helfen! Tortuga hat immer etwas zu bieten. Wie ich auch...Warum, ich bin geneigt, fast *alles* zu tun, nachdem ich eine gute Seegeschichte gehört habe. Ich liebe sie so sehr! Ein Kapitän erzählte mir einmal eine unglaubliche Geschichte darüber, wie er es geschafft hat, dem Marooning auf einer Wüsteninsel zu entkommen, indem er ein Floß aus Meeresschildkröten gemacht hat. Was für ein Galant! Könntest du?";
			link.l1 = "Könnte ich was?";
			link.l1.go = "girl_7";
		break;
		
		case "girl_7":
			dialog.text = "(kichern) Könntest du ein Floß aus Meeresschildkröten machen?";
			link.l1 = "Ich mache es sogar besser. Einmal habe ich mit einem ausgebüxten Lehrling das schnellste Schiff der englischen Marine nur mit einer Axt erobert. Ich kann auch zehn Minuten lang die Luft anhalten. Willst du es sehen?";
			link.l1.go = "girl_8";
		break;
		
		case "girl_8":
			dialog.text = "Vielleicht später. Ich arbeite als Diener in unserem Gouverneurspalast. Komm dort bis sechs Uhr heute Abend und finde mich und meinen Freund im Laubengang. Du kannst uns dann all deine Abenteuer erzählen...";
			link.l1 = "Hört sich an wie eine Einladung zu einer Vorführung, die ich nicht ablehnen kann. Bis heute Abend um sechs.";
			link.l1.go = "girl_9";
			link.l2 = "Sich ins Gouverneurspalast schleichen? Klingt ein bisschen zu hoch für meinen Geschmack. Ich passe, Liebes. Finde mich in der Taverne, wenn du die Gesellschaft eines echten Mannes möchtest. Yo ho ho!";
			link.l2.go = "girl_exit_2";
		break;
		
		case "girl_exit_2":
			dialog.text = "Pff. Was auch immer, ich werde einen besseren und größeren Mann als dich finden. Dein Beutel sieht sowieso zu klein aus. Auf Nimmerwiedersehen.";
			link.l1 = "Sogar ein Schlachtschiff würde klein aussehen, wenn es durch deine Windward Passage segelt.";
			link.l1.go = "girl_exit_1";
		break;
		
		case "girl_9":
			dialog.text = "Freue mich darauf!";
			link.l1 = "...";
			link.l1.go = "girl_10";
		break;
		
		case "girl_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "begin_bedroom";
			FMQT_Begin();
			AddQuestRecord("FMQ_Tortuga", "2");
		break;
		
		case "wife":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_01.wav");
			dialog.text = "Ach, da bist du ja! Kapitän "+GetFullName(pchar)+"! Ich bin so froh, Sie zu treffen, es ist eine Weile her, seit ich von einem solchen Besucher von solcher Adel und Statur begnadigt wurde!";
			link.l1 = "Es ist mir eine große Ehre und Freude, in Ihrer Gesellschaft zu sein, Madame. Aber was ist mit den resten Gästen? Bin ich zu früh?";
			link.l1.go = "wife_1";
		break;
		
		case "wife_1":
			dialog.text = "Oh, sie sind verhindert und können nicht kommen. Aber denken wir nicht an sie, lass uns Wein trinken und plaudern... Ah, wenn du nur wüsstest, wie langweilig und einsam ich mich hier fühle! Tortuga ist eine schäbige Höhle voller Abschaum, Schurken und Piraten! Piraten! Und endlich ein würdiger Herr in meinem Haus! Ich wünschte, mein Mann würde mehr Geschäfte mit Männern deiner Klasse und deines Talents machen! Aber nein, nichts als Piraten, überall Piraten! Hast du von dieser neuen Mode gehört, die am königlichen Hof Seiner Majestät in Paris immer beliebter wird? Was hältst du davon?";
			link.l1 = "Es tut mir leid, meine Meinung über was genau? Piraten? Oder Mode?";
			link.l1.go = "wife_2";
		break;
		
		case "wife_2":
			dialog.text = "Oh Herr, Sie verstehen mich so gut! Ich kann es kaum glauben. Mein Mann gibt mir Pfennige, während er MILLIONEN mit seinen Piraten verdient, stellen Sie sich das vor! Piraten! Ich muss Kleider hierher in dieses schmutzige Loch bestellen, aber wenn sie hier ankommen, sind sie bereits sechs Monate altmodisch! Wie kann eine Frau meines Standes solche Lumpen tragen? Oh, ich möchte so sehr die Mode von Paris sehen und tragen! Glauben Sie, ich würde darin bezaubernd aussehen?";
			link.l1 = "Madame, Sie sehen ganz bezaubernd aus. Sie brauchen dafür keine Mode aus Paris, das ist jedem Mann auf dieser schönen Insel bereits offensichtlich.";
			link.l1.go = "wife_3";
		break;
		
		case "wife_3":
			dialog.text = "Sie sind zu freundlich zu mir... Kapitän, ich muss gestehen, ich stecke in großen Schwierigkeiten. Aber Sie werden einer armen Frau helfen, nicht wahr?";
			link.l1 = "Sicher, Madame. Alles, was Sie wünschen.";
			link.l1.go = "wife_4";
		break;
		
		case "wife_4":
			dialog.text = "Sei vorsichtig, Monsieur Kapitän, oder ich verliere meinen Kopf! (kokettes Kichern) Mein Mann gibt mir in letzter Zeit keinen einzigen Centime. Dieses Ungeheuer bringt gewöhnliche Huren mit nach Hause und beachtet mich überhaupt nicht!\nIch weiß, wo er einen Teil seiner unrechtmäßig erworbenen Schätze aufbewahrt, sie sind in einer Truhe in seinem Büro. Dies ist mein Geld durch das Recht einer Ehefrau und einer Frau. Hilf mir, das zu bekommen, was er mir schuldet, und du wirst belohnt... Mit Gold und... anderen erfreulichen Dingen.";
			link.l1 = "Das ist ein faszinierendes Angebot. Sehr gut, Madame, ich werde Ihnen helfen. Wo ist diese Truhe und wie öffne ich sie?";
			link.l1.go = "wife_5";
			link.l2 = "Sehr gut, Madame, ich werde Ihnen den Inhalt der Truhe besorgen. Wir werden das Geld bekommen und danach ein sehr angenehmes 'Gespräch' führen. Welcher Mann könnte ein solches Angebot ablehnen? Wo ist diese Truhe und wie öffnet man sie?";
			link.l2.go = "wife_6";
			link.l3 = "Madame, Sie versuchen, mich zu verführen. Es tut mir leid, aber meine Ehre erfordert, dass ich Ihr Angebot ablehne. Sie haben mein Mitgefühl, Sie verdienen Besseres, aber Sie müssen sich einen anderen Schauspieler für Ihr Spiel suchen.";
			link.l3.go = "wife_exit";
		break;
		
		case "wife_exit":
			dialog.text = "Schade. Dann haben wir nichts mehr zu besprechen, Monsieur. Geh und erinnere dich: wenn du meinem Mann ein Wort über dies sagst, wirst du es bereuen!";
			link.l1 = "Auf Wiedersehen.";
			link.l1.go = "wife_exit_1";
		break;
		
		case "wife_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.FMQT.Common");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "huber";
			pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late1.win_condition.l1.date.hour  = 18.0;
			pchar.quest.FMQT_late1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
			AddQuestRecord("FMQ_Tortuga", "4");
		break;
		
		case "wife_5":
			pchar.questTemp.FMQT.Honour = "true"; // вар 1
			dialog.text = "Ich habe das nicht von dir erwartet... Die Truhe... Lass sie für später, zuerst müssen wir den Duplikatschlüssel finden, der von einem schmutzigen Piraten gestohlen wurde. Er ist gerade in einer örtlichen Spelunke am Saufen, trinkt wie ein Schwein. Mach schnell und bring den Duplikatschlüssel zu mir zurück. Ich werde auf dich warten.";
			link.l1 = "Dann verschwenden wir keine Zeit!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_6":
			pchar.questTemp.FMQT.Bed = "true"; // вар 2 
			dialog.text = "Sie werden dies nicht bereuen, Kapitän. Zuerst müssen wir den Duplikatschlüssel finden, der von einem dreckigen Piraten gestohlen wurde. Er ist gerade in einer örtlichen Spelunke am Saufen, trinkt wie ein Schwein. Machen Sie schnell und bringen Sie den Duplikatschlüssel zu mir zurück. Ich werde auf Sie warten.";
			link.l1 = "Keine Zeit verschwenden dann!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_PirateInTavern", 10.0);
			pchar.quest.FMQT_late2.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late2.win_condition.l1.date.hour  = 0.0;
			pchar.quest.FMQT_late2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late2.function = "FMQT_TavernTime";
			AddQuestRecord("FMQ_Tortuga", "6");
		break;
		
		case "wife_8":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_01.wav");
			dialog.text = "Kapitän "+GetFullName(pchar)+"! Ach du meine Güte! Was für ein Mann in meinen privaten Gemächern! Bist du überrascht? Du bist heute Abend der einzige Gast hier. (kichern)";
			link.l1 = "Ich bin überrascht, Madame. Aber es macht mir nichts aus. Geht es hier um Geschäft oder Vergnügen?";
			link.l1.go = "wife_9";
		break;
		
		case "wife_9":
			dialog.text = "Was für ein direkter Ansatz! Ich mag Männer wie dich. Ich habe einen Geschäftsvorschlag für dich, Kapitän. Ich werde einen Weg finden, deine Bemühungen zu belohnen, wenn du erfolgreich bist.";
			link.l1 = "Los geht's.";
			link.l1.go = "wife_10";
		break;
		
		case "wife_10":
			dialog.text = "Ach... Mein Mann hat eine Kiste voller Geld und Schmuck. Ich hasse ihn und ich will eine größere Zuwendung für meine Mühen.";
			link.l1 = "Madame, Sie sehen bezaubernd aus. Sie benötigen keine weiteren Juwelen oder Mode aus Paris dafür, das ist für jeden Mann auf Hispaniola bereits offensichtlich.";
			link.l1.go = "wife_11";
		break;
		
		case "wife_11":
			dialog.text = "Sie sind zu gütig zu mir... Kapitän, ich muss gestehen, ich bin in großer Not. Würden Sie einer Frau in Not helfen??";
			link.l1 = "Natürlich, Madame. Die Ehre verlangt es. Was immer Sie wünschen.";
			link.l1.go = "wife_12";
		break;
		
		case "wife_12":
			dialog.text = "Seien Sie vorsichtig, Monsieur Kapitän, oder ich verliere meinen Kopf! (kokettes Kichern) Mein Mann gibt mir in letzter Zeit keinen einzigen Centime. Diese Bestie bringt gemeine Dirnen in unser Haus und beachtet mich überhaupt nicht!\nIch weiß, wo er einen Teil seiner unehrlich erworbenen Schätze aufbewahrt, sie sind in einer Kiste in seinem Büro. Dies ist mein Geld nach dem Recht einer Ehefrau und einer Frau. Helfen Sie mir, das zu bekommen, was er mir schuldet, und Sie werden belohnt... Mit Gold und... anderen erfreulichen Dingen.";
			link.l1 = "Fein. Ich werde es tun. Wo ist diese Kiste und wie öffne ich sie?";
			link.l1.go = "wife_13";
			link.l2 = "Ha! Keine Fragen, das kann ich für eine solche Frau wie dich tun. Du wirst es nicht bereuen, meine Liebe. Wir werden das Geld bekommen und eine sehr angenehme Zeit zusammen verbringen. Wo ist diese Truhe und wie öffne ich sie?";
			link.l2.go = "wife_14";
			link.l3 = "Nicht ich, Madame. Ich bin kein Gentleman, der einen Mann in einer Nacht sowohl betrügt als auch beraubt. Zumindest nicht auf diese Weise. Suchen Sie sich einen anderen Darsteller für dieses Stück.";
			link.l3.go = "wife_exit_2";
		break;
		
		case "wife_13":
			pchar.questTemp.FMQT.Honour = "true"; // вар 1
			dialog.text = "Oh... Ich mag dich immer mehr... Zuerst sollten wir einen Duplikatschlüssel zurückholen, der von einem dreckigen Piraten gestohlen wurde. Er ist in einer örtlichen Spelunke am Saufen wie ein Schwein. Mach schnell und bring mir das Duplikat. Ich werde warten.";
			link.l1 = "Keine Zeit verschwenden dann!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_14":
			pchar.questTemp.FMQT.Bed = "true"; // вар 2 
			dialog.text = "Bewahren Sie Ihre Ruhe, Monsieur, dafür ist später noch genug Zeit. (kichert) Zuerst sollten wir einen Duplikatschlüssel zurückholen, der von einem schmutzigen Piraten gestohlen wurde. Er treibt sich in einer örtlichen Spelunke herum, trinkt wie ein Schwein. Machen Sie sich schnell auf den Weg und bringen Sie mir das Duplikat. Ich werde auf Sie warten. Sind Sie sicher, dass Sie das schaffen können?";
			link.l1 = "Zweifle nicht an mir, ich bin bereits auf dem Weg.";
			link.l1.go = "wife_7";
		break;
		
		case "wife_exit_2":
			dialog.text = "Prüder Bastard! Verschwinde aus meinen Augen! Und denk nicht einmal daran, meinem Mann davon zu erzählen, sonst wirst du es bereuen!";
			link.l1 = "Tschüss, Liebling.";
			link.l1.go = "wife_exit_1";
		break;
		
		case "wife_15":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_late3.over = "yes";
			dialog.text = "Kapitän! Haben Sie den Schlüssel bekommen?";
			link.l1 = "Ja, ich habe es. Wo ist die Truhe?";
			link.l1.go = "wife_16";
		break;
		
		case "wife_16":
			dialog.text = "Oh! Bekommt mein abscheulicher Ehemann endlich, was er verdient? Sie sind ein unglaublicher Mann, Kapitän! Sie haben eine große Zukunft vor sich, wissen Sie das? Vergessen Sie die Truhe. Ich mache es selbst. Kommen Sie morgen vorbei, um Ihre Belohnung zu erhalten. Sie werden es nicht bereuen, Kapitän...";
			link.l1 = "Gut. Mach es auf deine Weise. Ich freue mich darauf, dich morgen zu sehen.";
			link.l1.go = "wife_17";
			link.l2 = "Nein, ich bin ein beschäftigter Mann und ich will keine Zeit mit Warten verschwenden. Warum warten? Sag mir, was getan werden muss und ich werde es tun. Ich kann es nicht zulassen, dass eine so schöne Frau ihre hübschen kleinen Hände mit einem Schloss und Schlüssel verdirbt.";
			link.l2.go = "wife_18";
		break;
		
		case "wife_17":
			RemoveItems(pchar, "kaleuche_key", 1);
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key");
			dialog.text = "Kommen Sie um sechs Uhr zu mir, mein tapferer Ritter...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_Deceive");
		break;
		
		case "wife_18":
			dialog.text = "Sind Sie sicher? Es könnte gefährlich für Sie sein. Warum wollen Sie Ihr Leben aufs Spiel setzen, Kapitän?";
			link.l1 = "Gut. Mach es auf deine Weise. Ich freue mich darauf, dich morgen zu sehen.";
			link.l1.go = "wife_17";
			link.l2 = "Ich habe meine Entscheidung bereits getroffen. Was soll ich genau tun?";
			link.l2.go = "wife_19";
		break;
		
		case "wife_19":
			dialog.text = "Ein Löwenherz!... Gehe zu dem Büro meines Mannes, dort findest du die Truhe. Benutze den Duplikatschlüssel. Zu dieser Nachtzeit ist niemand dort oben, also nimm dir Zeit. Es gibt.. Diamanten in dieser Truhe. Eine große Anzahl von ihnen. Nimm sie alle und komme zu mir zurück. Ich werde warten. Verrate mein Vertrauen nicht...bitte.";
			link.l1 = "Ich komme bald zurück.";
			link.l1.go = "wife_20";
		break;
		
		case "wife_20":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("FMQ_Tortuga", "11");
			sld = &Locations[FindLocation("Tortuga_townhallRoom")];
			sld.private2.key = "kaleuche_key"; // допуск к сундуку
			pchar.questTemp.FMQT = "chest";
		break;
		
		case "wife_21":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_GemsTimeOver.over = "yes";
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_02.wav");
			dialog.text = "Oh, Kapitän! Ich...Du... Ist es getan? Oh und wer ist das?! A-ah!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_MercenAttackRoom");
		break;
		
		case "wife_22":
			dialog.text = "Oh mein Gott! Kapitän, Sie haben mich gerettet! Du... du bist mein Held! Es war der Schläger meines Mannes, er wollte dich töten! Ich habe ihn angefleht, es nicht zu tun! Sind Sie verletzt? Haben Sie die Diamanten mitgebracht?";
			link.l1 = "Ha. Wirklich? Dein Mann ist ein eifersüchtiger Mann... Was auch immer. Zum Teufel mit ihm, ich habe die Steine.";
			link.l1.go = "wife_23";
		break;
		
		case "wife_21x":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_GemsTimeOver.over = "yes";
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_02.wav");
			dialog.text = "Oh Kapitän! Ich... Du... Ist es erledigt?";
			link.l1 = "Es gab eine kleine Komplikation, aber das ist jetzt geklärt. Warum sind Sie so blass, Madame? Geht es Ihnen gut? Ich habe die Juwelen, das sollte Sie aufheitern, habe ich recht?";
			link.l1.go = "wife_23";
		break;
		
		case "wife_23":
			dialog.text = "Gott sei Dank! Ich bin gerächt! Mein Ritter! Wie viele Diamanten waren da?";
			if (GetCharacterItem(pchar, "jewelry2") >= 100)
			{
				link.l1 = "Dein Ritter ist von seinem Abenteuer zurück mit einem vollen Sack voller Beute. Er wird die Hälfte davon seiner Dame überlassen, damit sie sich die allerbesten Moden aus Paris kaufen kann. Ich habe mein Versprechen an dich gehalten.";
				if (CheckAttribute(pchar, "questTemp.FMQT.Honour")) link.l1.go = "wife_25";
				else link.l1.go = "wife_26";
			}
			else
			{
				link.l1 = "Oh, es gab genug Diamanten, aber du wirst nichts bekommen. Du hast einen Mörder angeheuert, um mich zu töten, du Hure! Glaubst du wirklich, dass ich nach all dem mit dir teilen würde? Öffne deinen Mund über das und dein Mann wird von deinem Plan erfahren, ihn zu berauben und zu betrügen. Also halt's Maul.";
				link.l1.go = "wife_24";
			}
		break;
		
		case "wife_24":
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_03.wav");
			dialog.text = "Schurke! Bastard! Du wirst damit nicht davonkommen!";
			link.l1 = "Ja, das habe ich schon mal gehört.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_FinalNoJewelry");
		break;
		
		case "wife_25":
			RemoveItems(pchar, "jewelry2", 100);
			Log_Info("You have given diamonds");
			PlaySound("interface\important_item.wav");
			dialog.text = "Du bist nicht wie... die anderen. Du bekommst, was du willst. Du hast eine strahlende Zukunft vor dir. Ich weiß, du bist ein beschäftigter Mann, aber... Wirst du ein bisschen bei mir bleiben? Niemand wird uns stören, das verspreche ich.";
			link.l1 = "Ich habe immer Zeit für eine schöne Frau wie Sie. Soll ich eine Flasche Wein Ihres Ehemannes öffnen?";
			link.l1.go = "wife_sex";
		break;
		
		case "wife_sex":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.HorseQty = int(pchar.questTemp.HorseQty) + 1;
			DoQuestCheckDelay("PlaySex_1", 1.0);
			
			// Rebbebion, для "Путеводной звезды"
			pchar.questTemp.FMQT.GiveDiamonds = true;
			pchar.questTemp.FMQT.Marceline = "Fuck"; 
		break;
		
		case "wife_26":
			RemoveItems(pchar, "jewelry2", 100);
			Log_Info("You have given diamonds");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ich glaube, ich kann ohne sie leben. Es gibt hier viele Möglichkeiten, Geld auszugeben. So viele gutaussehende und würdige Männer auf Tortuga... Danke für alles, Kapitän. Nur damit Sie es wissen, bitte schweigen Sie über diese Affäre, sonst wird mein Ehemann Sie am Galgen aufhängen sehen. Er ist kein guter Mann. Lebewohl.";
			link.l1 = "Genau so? Das war eine lehrreiche Erfahrung. Auf Wiedersehen, Madame, ich schlage vor, Sie schweigen auch darüber, ich bin auch kein guter Mensch. Aber das wissen Sie bereits, oder?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_FinalNoSex");
			
			// Rebbebion, для "Путеводной звезды"
			pchar.questTemp.FMQT.GiveDiamonds = true;
			pchar.questTemp.FMQT.Marceline = "NoFuck"; 
		break;
		
		case "wife_27":
			PlaySound("Voice\English\Girls_2.wav");
			dialog.text = "Wer bist du und was machst du hier?";
			link.l1 = "Was hast du vor? Wir hatten eine Abmachung...";
			link.l1.go = "wife_28";
		break;
		
		case "wife_28":
			dialog.text = "Welcher Deal, Monsieur? Ich bin eine verheiratete Frau, ich mache keine Geschäfte mit anderen Männern! Verlassen Sie jetzt meine Gemächer oder ich rufe meinen Ehemann und seine Wachen!";
			link.l1 = "So einfach, hm? Sehr gut, ich glaube, ich werde in diesem Fall deinen guten Ehemann aufklären!";
			link.l1.go = "wife_29";
		break;
		
		case "wife_29":
			dialog.text = "Verlasse jetzt diesen Ort, du unverschämter Kerl, oder meine Männer werfen dich in das Verlies von Fort La Roche! Deine Drohungen sind mir egal! Raus hier!";
			link.l1 = "...";
			link.l1.go = "wife_30";
		break;
		
		case "wife_30":
			DialogExit();
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "FMQT_FinalFail");
			pchar.questTemp.FMQT.Marceline = "Deception"; // Rebbebion, для "Путеводной звезды"
		break;
		
		case "pirate":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\tavern\Pyanici-03.wav");
			pchar.quest.FMQT_late2.over = "yes";
			FreeSitLocator("Tortuga_tavern", "sit_base2");
			dialog.text = "Wer bist du? Ach, egal. Vertraue Frauen nicht, Kumpel. Es ist wie die Bibel sagt... selbst die dümmste Dirne kann dich mit ihren Männerspielchen in die tiefsten Abgründe der Hölle ziehen. Nimm Platz, Kumpel, trink einen Schluck!";
			link.l1 = "Mit Vergnügen!";
			link.l1.go = "pirate_1x";
		break;
		
		case "pirate_1x":
			DialogExit();
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "sit", "sit_base2");
			LAi_SetSitType(pchar);
			npchar.Dialog.currentnode = "pirate_1";
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 2.0);
		break;
		
		case "pirate_1":
			PlaySound("Voice\English\tavern\Pyanici-05.wav");
			dialog.text = "Worauf starrst du? Schenk ein!!";
			link.l1 = "Auf dich!.. Hey Freund, ich werde hier keine Zeit verschwenden. Ich brauche diesen Duplikatschlüssel, den du hast, du weißt, wovon ich spreche. Gib ihn mir und wir werden getrennte Wege gehen: du wirst weiter trinken und ich werde weiterhin Damen in Not helfen.";
			link.l1.go = "pirate_2";
		break;
		
		case "pirate_2":
			dialog.text = "Ach Kumpel! Hast du überhaupt zugehört, was ich gerade gesagt habe! Du musst schlauer aussehen, als du wirklich bist...arbeitest für diese Hure. Weißt du, wer ihr Mann ist? Erst kürzlich hat Gouverneur Levasseur seinen treuen Neger Kampacho geschickt, um mit einem lokalen und hoch angesehenen Händler 'zu reden'. Der Schwarze hat den armen Bastard in seinem eigenen Laden zu Tode geprügelt! Dieser Händler hatte auf einem Ball oder so etwas eine Art geringfügige Missachtung gegenüber der Frau des Gouverneurs gezeigt. Und dieselbe Schlampe hat mich mit ihrem Aussehen und seinen Dublonen verführt. Der Duplikatschlüssel existiert. Ich war früher in Frankreich ein anständiger Safeknacker, also war es ein Kinderspiel. Wenn es nicht die Tochter des Kommandanten von Lyon gewesen wäre... Ich wäre nie Pirat geworden. Bah! Verdammt noch mal!";
			link.l1 = "Das ist alles sehr traurig, aber reden wir über Geschäft. Wo ist der Schlüssel?";
			link.l1.go = "pirate_3";
		break;
		
		case "pirate_3":
			dialog.text = "Hörst du zu? Ich bin raus aus dem Spiel, Kumpel! Ich war klug genug zu sehen, was kommt! Ich verlasse diesen Ort für immer, sobald mein Schiff bereit zum Auslaufen ist. Du willst den Schlüssel, bezahl dafür. Sei hier nicht gierig, ich glaube, du wirst bald kein Geld mehr brauchen.";
			link.l1 = "Weißt du, du hast recht. Ich will kein Spielzeug für eine Frau sein. Danke für den Rat und sei sicher auf See!";
			link.l1.go = "pirate_4";
			link.l2 = "Dafür bezahlen? An dich? Du bist ein erbärmlicher Dieb und ein Feigling. Du hättest in diesem Dreckloch Lyons bleiben sollen. Wer weiß, vielleicht hätte der örtliche Kommandant Mitleid mit dir gehabt und einen entarteten Dieb als Schwiegersohn zugelassen. Ich werde sicher kein Mitleid mit dir haben. Du kannst mir den Schlüssel auf die leichte oder die harte Tour geben, die Wahl liegt bei dir.";
			link.l2.go = "pirate_5";
			link.l3 = "(Seufz) Wie viel?";
			link.l3.go = "pirate_6";
		break;
		
		case "pirate_4":
			dialog.text = "Schlauer Bursche, das ist die richtige Entscheidung, Kumpel. Viel Glück. Hoffentlich findest du eines Tages eine wahre und liebevolle Frau. Vorzugsweise eine Rothaarige oder eine Blondine, nicht wahr?";
			link.l1 = "Auf Wiedersehen Kumpel...";
			link.l1.go = "pirate_exit";
		break;
		
		case "pirate_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
			pchar.questTemp.FMQT = "huber";
			pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late1.win_condition.l1.date.hour  = 18.0;
			pchar.quest.FMQT_late1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
			AddQuestRecord("FMQ_Tortuga", "9");
		break;
		
		case "pirate_5":
			dialog.text = "Du beleidigst mich! Zieh Stahl, du Bastard!";
			link.l1 = "Lass uns mal sehen, wie gut du Tresore knacken kannst ohne Arme!";
			link.l1.go = "pirate_duel";
		break;
		
		case "pirate_duel":
			DialogExit();
			LAi_SetSitType(npchar);
			// ключ квестовый от Калеуче - вернуть назад
			GiveItem2Character(npchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
			i = int(MOD_SKILL_ENEMY_RATE/4);
			pchar.questTemp.FMQT = "duel";
			PChar.questTemp.duel.enemy = NPChar.id;
			if (MOD_SKILL_ENEMY_RATE > 2) PChar.questTemp.duel.enemyQty = i;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
		break;
		
		case "pirate_6":
			dialog.text = "Sie sind ein Geschäftsmann, das gebe ich zu. Sie könnten es tatsächlich schaffen. Fünfzig Dublonen. Auf den Tisch.";
			link.l1 = "Fünfzig Goldstücke? Für ein Stück Zinn? Kielholen Sie mich. Legen Sie den Schlüssel auf den Tisch. Jetzt.";
			link.l1.go = "pirate_7";
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "Ein ziemlicher Preis... Gut. Nimm sie.";
				link.l2.go = "pirate_8";
			}
			else
			{
				link.l2 = "Ein ganz schöner Preis... In Ordnung. Ich werde sie bald bringen. Bleib hier.";
				link.l2.go = "pirate_wait";
			}
		break;
		
		case "pirate_wait":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_SetSitType(npchar);
			npchar.Dialog.currentnode = "pirate_dublon";
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
		break;
		
		case "pirate_dublon":
			NextDiag.TempNode = "pirate_dublon"; // mitrokosta правка явного бага
			dialog.text = "Hast du fünfzig Dublonen mitgebracht?";
			link.l1 = "Sie wissen, ich glaube, dass Sie ohne sie leben können. Der Schlüssel. Auf dem Tisch.";
			link.l1.go = "pirate_7";
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "Ja. Nimm sie.";
				link.l2.go = "pirate_8";
			}
			else
			{
				link.l2 = "Ich bekomme sie immer noch.";
				link.l2.go = "exit";
			}
		break;
		
		case "pirate_7":
			dialog.text = "Wollen wir tanzen?";
			link.l1 = "Ich werde führen.";
			link.l1.go = "pirate_duel";
		break;
		
		case "pirate_8":
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(50);
			Log_Info("You have given 50 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Gut. Benutze deinen Kopf und du könntest aus dieser Sache mit einigen Silberstücken und deinem Kopf herauskommen. Nimm den Schlüssel und hör meinen Rat. Kostenlos. Levasseurs Frau ist dumm wie ein Fisch, aber sie glaubt, sie wäre schlau. Vertrau ihr nicht. Halt deinen Schwanz in der Hose und pass auf deine Taschen auf. Sie ist nicht viel von einem Gegner, sei einfach vorsichtig und vermeide es, ihren Mann in diese Sache zu bringen\nNoch eine letzte Sache - es gibt eine Truhe in ihrer Laube, in der sie ihre Schnickschnack aufbewahrt, leicht zu knacken. Sie wird dort ihren Anteil hineinlegen. Du hast mich gehört. Sei sicher auf See, Bruder. Denk daran, Brüder vor Huren.";
			link.l1 = "Gottes Geschwindigkeit, Kamerad...";
			link.l1.go = "pirate_9";
		break;
		
		case "pirate_9":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
			pchar.questTemp.FMQT = "key";
			pchar.questTemp.FMQT.Caution = "true";
			FMQT_KeyNextDay();
			pchar.quest.FMQT_late3.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late3.win_condition.l1.date.hour  = int(GetTime());
			pchar.quest.FMQT_late3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late3.function = "FMQT_KeyTime";
			AddQuestRecord("FMQ_Tortuga", "10");
			// ключ квестовый от Калеуче - вернуть назад
			GiveItem2Character(pchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
		break;
		
		case "mercen":
			PlaySound("Voice\English\EvilPirates10.wav");
			dialog.text = "Verdammt! Ich habe nicht erwartet... zur Hölle mit dieser Frau! Mein Meister hat mir gesagt, ich soll ihre Art meiden. Aber Arbeit ist Arbeit. Ich kriege dich trotzdem.";
			link.l1 = "Nun, Kumpel... Sieht so aus, als ob sie uns beide betrügen wollte, kann nicht sagen, dass ich überrascht bin. Warum sollten wir weiter kämpfen? Brauchst du einen Job? Ich habe einen. Du hast Geschick, ich brauche Männer wie dich in meiner Mannschaft. Mahlzeit, Koje, regelmäßiger Lohn, Rum und ein fairer Anteil an jeder Beute. Ich gebe dir mein Ehrenwort darauf. Was sagst du?";
			//if(CheckCharacterPerk(pchar, "IronWill") || CheckCharacterPerk(pchar, "HT2") || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34 || GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 20) link.l1.go = "mercen_1";
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34) link.l1.go = "mercen_1";
			else link.l1.go = "mercen_4";
		break;
		
		case "mercen_1":
			//if(CheckCharacterPerk(pchar, "IronWill")) notification("Iron Will", "IronWill");
			//if(CheckCharacterPerk(pchar, "HT2")) notification("Mimicry", "Mimicry");
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34) notification("Skill Check Passed", SKILL_LEADERSHIP);
			//if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 20) notification("Skill Check Passed", SKILL_FORTUNE);
			dialog.text = "Sie haben eine silberne Zunge und Ihr Ruhm eilt Ihnen voraus, Käpt'n, das gebe ich Ihnen. Ja, ich bin dabei. Wie heißt Ihr Schiff?";
			link.l1 = "'"+pchar.ship.name+"'. Sprich mit dem Bootsmann, er wird dir eine Koje finden. Willkommen an Bord!";
			link.l1.go = "mercen_2";
		break;
		
		case "mercen_2":
			dialog.text = "Ha! Ich steige auf in der Welt. Gib dieser Schlampe einen Tritt für mich.";
			link.l1 = "...";
			link.l1.go = "mercen_3";
		break;
		
		case "mercen_3":
			DialogExit();
			LAi_group_Delete("EnemyFight");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_MercenHire", 10.0);
			AddQuestRecord("FMQ_Tortuga", "17");
		break;
		
		case "mercen_4":
			//if(!CheckCharacterPerk(pchar, "IronWill")) notification("Perk check failed", "IronWill");
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35) notification("Skill Check Failed (35)", SKILL_LEADERSHIP);
			//if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) < 21) notification("Skill Check Failed (21)", SKILL_FORTUNE);
			dialog.text = "Du redest süß. Aber nicht süß genug, wenn du echte Profis in deinen Reihen haben willst. Behalte das in Zukunft im Hinterkopf. Wenn du eine hast.";
			link.l1 = "Gib es einen Versuch. Sei schnell, ich habe eine Verabredung mit einer Dame.";
			link.l1.go = "mercen_5";
			link.l2 = "Keine zweite Chance heute. Ich bin ein beschäftigter Mann, also verschmutzen wir nicht den Teppich. Du wirst nicht genug bezahlt, um für irgendeine kleine Dirne zu sterben. Wenn sie dich überhaupt bezahlt haben.";
			link.l2.go = "mercen_6";
		break;
		
		case "mercen_5":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQT_MercenDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "mercen_6":
			dialog.text = "Du hast recht. Niemand hat mich... noch bezahlt. Ich werde das sofort klären. Mach, was du willst...";
			link.l1 = "...";
			link.l1.go = "mercen_7";
		break;
		
		case "mercen_7":
			DialogExit();
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_Delete("EnemyFight");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			AddQuestRecord("FMQ_Tortuga", "18");
			pchar.questTemp.FMQT.Roomfight = "true";
			FMQT_WifeFinalTalk();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
