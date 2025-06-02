// Маркус Тиракс, барон Ла Веги
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc, sTemp;
	int i;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ------------------------------------------блок angry-----------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
// ------------------------------------------блок angry-----------------------------------------------

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
			// Addon 2016-1 Jason пиратская линейка патч 17/1
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && !CheckAttribute(npchar, "quest.mtraxx_complete")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
				{
					dialog.text = "Ach Prinz, du bist endlich hier. Zumindest einer von euch hat sich die Mühe gemacht aufzutauchen! Arbeit wartet und ihr alle seid verschwunden! Wo zur Hölle sind alle?";
					link.l1 = "Keine Ahnung... Marcus, ich bin raus. Ich habe genug. Tote Männer kommen in meinen Träumen zu mir und Luzifer selbst haucht mir in den Nacken. In letzter Zeit wurde zu viel Blut vergossen.";
					link.l1.go = "mtraxx_113";
					break;
				}
			}
			// Jason НСО
			// если Сага завалена, то у Маркуса ноды в двух местах и оплата вперед
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Hast du irgendwelche 'Angelegenheiten' für mich?";
				link.l1 = "Grüße, Marcus. Ja, ich habe eine 'Angelegenheit'. Profitabel und praktisch.";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "Hast du das Geld mitgebracht?";
				link.l1 = "Ich habe es getan.";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "Das ist unser Kunde! Die Arbeit ist erledigt, Euer Baron sitzt in einem gut bewachten Verlies. Vielleicht möchtet Ihr mal einen Blick darauf werfen, he-he?!";
				link.l1 = "Ich werde genug Zeit dafür haben, ha-ha. Wird er gut behandelt?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, was zur Hölle?!";
				link.l1 = "Marcus, alles ist schief gelaufen. Ich konnte weder kommen noch dich informieren...";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Hier ist unser Puppenspieler!";
				link.l1 = "Ha-ha! Das Schauspiel war perfekt!";
				link.l1.go = "patria_x29";
				break;
			}
            dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Hast du mir etwas zu sagen? Nein? Dann lass mich in Ruhe!","Ha, "+pchar.name+"! Hast du irgendwelche Geschäfte mit mir? Nein? Dann stör mich nicht.")+"","Ich dachte, ich habe mich klar ausgedrückt... Ich habe dir gesagt, dass du gehen sollst, aber du nervst mich immer noch!","Also gut, ich habe genug von dieser Unhöflichkeit.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ich gehe schon.","Sicher, Marcus...","Entschuldigung, Marcus...","Ups...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Bist du wahnsinnig? Wolltest du Metzger spielen, hm? Alle Piraten sind wütend auf dich, Junge, du solltest besser diesen Ort verlassen...","Es scheint, du bist zu einem tollwütigen Hund geworden, Junge. Wolltest du deine Hände ein wenig strecken? Nichts für ungut, aber hier gibt es nichts für dich. Verschwinde!");
				link.l1 = RandPhraseSimple("Hör zu, ich möchte die Situation klären.","Hilf mir bitte, dieses Problem zu lösen...");
				link.l1.go = "pirate_town";
				break;
			}
			// Сага - завершаем искушение барбазона
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
			{
				// Addon 2016-1 Jason пиратская линейка патч 17/1
				if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
				{
					link.l1 = "Marcus, wirst du jemals aufhören, auf mich sauer zu sein? Ich habe deinen Freund, Vincent, gerettet, der mit uns Cartagena überfallen hat, und ich habe auch deinen Arsch gerettet! Oder hat dir Bernard das nicht einmal erzählt?";
					link.l1.go = "Temptation_13";
				}
				else
				{
					link.l1 = "Warum bist du so unhöflich, Marcus? Hat Bernard nichts über mich gesagt?";
					link.l1.go = "Temptation";
				}
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "to_lavega")
			{
				link.l2 = "Ich suche nach Arbeit... Haben Sie etwas Profitables im Sinn?";
				link.l2.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Ich habe Seide zu verkaufen.";
				link.l2.go = "Mtraxx_silktrade";
			}
			if (pchar.questTemp.Mtraxx == "silk_14")
			{
				link.l1 = "Ich habe einen Käufer für dich gefunden. Es ist ein Schiffsbauer aus Port Royal. Er braucht Schiffsseide für seine Produktion und er wird in der Lage sein, jeden Monat Chargen von hundert Rollen für 25 Dublonen pro Rolle zu kaufen. Seine Männer werden die Ware vom 10. bis 15. nachts in Empfang nehmen, der Ort ist das Negril-Kap. Das Passwort - 'Ein Kaufmann aus Lyon'. Der kahlköpfige Geffrey hat die erste Lieferung bereits nach Jamaika gebracht.";
				link.l1.go = "mtraxx_13";
			}
			if (pchar.questTemp.Mtraxx == "silk_15")
			{
				link.l1 = "Ich habe einen Käufer für dich gefunden. Es ist ein Schiffsbauer aus Port Royal. Er benötigt Schiffsseide für seine Produktion und er wird in der Lage sein, jeden Monat Partien von hundert Rollen für 25 Dublonen pro Rolle zu kaufen. Seine Männer werden die Waren vom 10. bis zum 15. in der Nacht entgegennehmen, der Ort ist das Negril Kap. Das Passwort - 'Ein Kaufmann aus Lyon'. Es hat mich mehr als zwei Monate gekostet, einen solchen Käufer zu finden, Geffrey muss die Seide bereits an Schmuggler verkauft haben. Es tut mir leid, Marcus.";
				link.l1.go = "mtraxx_15";
			}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Bist du wahnsinnig? Wolltest du den Schlachter spielen? Alle Piraten sind wütend auf dich, Junge, du solltest diesen Ort besser verlassen...","Es scheint, du bist zu einem tollwütigen Hund geworden, Junge. Wolltest ein bisschen deine Hände ausstrecken? Nichts für ungut, aber hier ist kein Platz für dich. Verschwinde!");
				link.l1 = RandPhraseSimple("Hör zu, ich möchte die Situation klären...","Hilf mir bitte, dieses Problem zu lösen...");
				link.l1.go = "pirate_town";
				break;
			}
			// Jason НСО
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, was zur Hölle?!";
				link.l1 = "Marcus, alles ging schief. Ich konnte weder kommen noch dich informieren...";
				link.l1.go = "patria_33";
				break;
			}
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Froh dich zu sehen, Freund!";
				link.l1 = "Froh dich auch zu sehen. Danke für das erstaunliche Schauspiel!";
				link.l1.go = "patria_29";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Freut mich, dich zu sehen, Junge! Wie kann ich dir helfen?";
				link.l1 = "Ich habe einen Vorschlag für dich. Passend für einen Piraten, weißt du!";
				link.l1.go = "patria";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "Das ist unser Kunde! Die Arbeit ist erledigt, euer Baron sitzt in einem gut bewachten Kerker. Vielleicht möchtet ihr einen Blick darauf werfen, he-he?!";
				link.l1 = "Ich werde genügend Zeit dafür haben, ha-ha. Wird er gut behandelt?";
				link.l1.go = "patria_10";
				break;
			}
			// если Сага завалена, то у Маркуса ноды в двух местах и оплата вперед
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Hast du irgendwelche Aufgaben für mich?";
				link.l1 = "Grüße, Marcus. Ja, eine Angelegenheit. Profitabel und piratisch.";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "Hast du das Geld mitgebracht?";
				link.l1 = "Ich habe es getan.";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "Das ist unser Kunde! Die Arbeit ist erledigt, euer Baron sitzt in einem gut bewachten Kerker. Vielleicht möchtet ihr einen Blick darauf werfen, he-he?!";
				link.l1 = "Ich werde genug Zeit dafür haben, ha-ha. Wird er gut behandelt?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, was zur Hölle?!";
				link.l1 = "Marcus, alles ist schief gelaufen. Ich konnte weder kommen noch dich informieren...";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Hier ist unser Puppenspieler!";
				link.l1 = "Ha-ha! Das Schauspiel war perfekt!";
				link.l1.go = "patria_x29";
				break;
			}
			// Тени прошлого
			if(CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "Freut mich, dich zu sehen, Junge! Wie kann ich dir helfen?";
				link.l1 = "Marcus, ich muss mit dir reden. Ich bin nicht sicher, ob es dir gefallen wird, aber ich brauche trotzdem deine Hilfe.";
				link.l1.go = "shadows";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "Ha, hier bist du, "+pchar.name+". Ich habe auf deine Ankunft gewartet. Der Waldteufel hat mich mit deinem Problem über Tortuga verwirrt...";
				link.l1 = "Er hat mir gesagt, dass du eine Lösung gefunden hast. Liege ich richtig?";
				link.l1.go = "terrapin";
				break;
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Ich habe Seide zu verkaufen.";
				link.l2.go = "Mtraxx_silktrade";
			}
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+", froh dich zu sehen! Was brauchst du diesmal, Kumpel?","Was willst du?","Wieder? Belästige die Leute nicht, wenn du nichts zu tun hast!","Du bist ein "+GetSexPhrase("guter Freibeuter","braves Mädchen")+", also kannst du vorerst leben. Aber ich will nicht mehr mit dir reden.","repeat",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Wollte dich nur sehen.","Nichts.","Gut, Marcus, es tut mir leid.","Verdammt, es tut mir wirklich leid, Marcus!",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Raub!!! Das ist inakzeptabel! Bereite dich darauf vor zu sterben, Ratte...","He, was machst du da?! Dachtest, du könntest mich ausrauben? Du bist erledigt...","Warte, was zum Teufel?! Es stellt sich heraus, dass du ein Dieb bist! Ende der Fahnenstange, Bastard...");
			link.l1 = LinkRandPhrase("Scheiße!","Verdammt!","Ach, verdammt noch mal!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("Geh weg","Verzieh dich")+" von hier!","Verlass mein Zuhause!");
			link.l1 = "Ups...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Lass mich mit deinem wertlosen Gerede nicht von meiner Arbeit ablenken. Das nächste Mal wird es für dich nicht so gut enden...";
        			link.l1 = "Verstanden, Marcus.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("Ich habe genug von dir.","Ich will nicht mit dir reden, also halte dich besser von mir fern.");
			link.l1 = RandPhraseSimple("Nun...","Hm, gut dann...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Ich hoffe, du wirst mich nicht mehr mit deinem leeren Geschwätz belästigen, oder ich werde gezwungen sein, dich zu töten. Ich sage, dass ich das nicht gerne tun würde.";
        			link.l1 = "Du kannst dir sicher sein, Marcus, ich werde nicht...";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Lavega_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		
//--> -----------------------------Сага - Искушение Барбазона завершающие этапы---------------------------
		case "Temptation":
			dialog.text = "Ha! Der Held von Turks? Entschuldige die grobe Begrüßung, Junge. Bernard hat mir bereits von deinem wunderbaren Mitwirken erzählt und etwas von einer Falle für mich erwähnt. Ich würde gern die Details hören...";
			link.l1 = "Es war tatsächlich eine Falle. Sie haben auf dich gejagt, nicht auf Bernard. Er war nur der Köder";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_1":
			dialog.text = "";
			link.l1 = "Der Plan war einfach. Du solltest deinen Freund retten und wärst der Erste an Bord der 'Separator' gewesen. Und genau in diesem Moment hätten sie das Schiff beschossen und es in Stücke gesprengt. Die Brigantine war geladen mit Schießpulver wie die Hölle mit Schwefel.";
			link.l1.go = "Temptation_2";
		break;
		
		case "Temptation_2":
			dialog.text = "Verdammt! Wessen Idee war dieser Wahnsinn?! Und wie könnte ich herausfinden, wo sie Bernard versteckt haben?!";
			link.l1 = "Die Urheber dieses Plans waren Jackman und sein Bruder David. Ein Bote hätte Sie informiert, dass der 'Separator' auf Ihre Hilfe in der Südbucht der Turks wartet. Sie haben mich als diesen Boten ausgewählt und das war ihr Fehler.";
			link.l1.go = "Temptation_3";
		break;
		
		case "Temptation_3":
			dialog.text = "Ich verstehe es nicht! Was ist deine Rolle in all dem?";
			link.l1 = "Ich habe diesen Bastard Jackman schon lange im Auge. Ich arbeite mit Jan Svenson zusammen, falls du es nicht weißt. Ich und der Waldteufel haben beschlossen, ihn zu entlarven. Jan ist sicher, dass er derjenige ist, der für Blazes Tod verantwortlich ist und Steven wurde grundlos beschuldigt.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end") link.l1.go = "Temptation_14";
			else link.l1.go = "Temptation_4"; //патч 17/1
		break;
		
		case "Temptation_4":
			dialog.text = "Heh! Aber ein Haifischzahn mit seinen Initialen wurde auf Blazes Körper mit seinen Initialen - S.D. - gefunden. Dieses Ding gehört Steven, das weiß jeder...";
			link.l1 = "Es war geplant. Jackman hat hoch gepokert. Er hat Nathaniel Hawk losgeworden und hat seinen Platz in Maroon Town eingenommen, dann hat er Sharp ermordet und Shark für den Mord verantwortlich gemacht. Ich habe genug Beweise für seine Verbrechen. Ich habe sie in Jacobs Truhe gefunden. Dort waren der zweite Teil von Sharps Karte und Hawks Splitter.";
			link.l1.go = "Temptation_5";
		break;
		
		case "Temptation_5":
			dialog.text = "Verdammt! Also ist Steven unschuldig? Und warum hat Jacob das alles getan?";
			link.l1 = "Er erwartete, der Anführer der Brüder zu werden und erwartete etwas in Bezug auf Isla Tesoro. Er konnte deine und Svensons Unterstützung nicht bekommen, also beschloss er, euch beide loszuwerden. Du warst der erste auf der Liste. Jan als der gefährlichste war der zweite.";
			link.l1.go = "Temptation_6";
		break;
		
		case "Temptation_6":
			dialog.text = "Wo ist dieser Bastard?! Ich werde ihn in Stücke reißen!";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				link.l1 = "Jackman und sein Bruder sind tot, ebenso wie der Rest seiner Jäger. Ich habe mich persönlich um sie gekümmert. Dieser Bastard wird niemandem mehr schaden. Marcus, würdest du für Steven Dodson stimmen? Das ist mir ein persönlicher Gefallen.";
				link.l1.go = "Temptation_7";
			}
			else
			{
				link.l1 = "Jackman und sein Bruder sind tot, ebenso wie der Rest der Jäger. Ich habe mich persönlich um sie gekümmert. Dieser Bastard wird niemandem mehr schaden. Leider wurde Steven getötet...";
				link.l1.go = "Temptation_10";
			}
		break;
		
		case "Temptation_7":
			dialog.text = "Sicher, ich werde abstimmen! Ich habe Shark immer als den würdigsten von uns nach Blaze betrachtet. Und ich habe fast an seine Schuld geglaubt. Wir alle haben! Hier, nimm mein Splitter.";
			link.l1 = "Sehr gut! Jetzt kannst du frei atmen.";
			link.l1.go = "Temptation_8";
		break;
		
		case "Temptation_8":
			GiveItem2Character(pchar, "splinter_mt"); // дать осколок
			dialog.text = "Wahr... Wie ich verstehe, vertrittst du die Interessen des Hais?";
			link.l1 = "Ja. Ich und Jan Svenson. Gut, Marcus, wir sehen uns!";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_10":
			dialog.text = "Tot?! Wie? Jackmans Werk auch?";
			link.l1 = "Nein. Sein eigener Bootsmann hat es getan, Chad Kapper war sein Name. Er hat bereits bekommen, was er verdient hat... Marcus, Svenson glaubt, dass du der Würdigste bist, um der neue Anführer der Bruderschaft zu sein. Die restlichen Barone werden diese Entscheidung unterstützen. Akzeptierst du das?";
			link.l1.go = "Temptation_11";
		break;
		
		case "Temptation_11":
			dialog.text = "Heh! Du musst mich nicht zweimal fragen. Es ist eine große Ehre, der Anführer der Bruderschaft zu sein! Denk nicht mal daran, dass ich nicht zustimme.";
			link.l1 = "Großartig. Ich bin froh, dass du das angenommen hast.";
			link.l1.go = "Temptation_12";
		break;
		
		case "Temptation_12":
			GiveItem2Character(pchar, "splinter_mt"); // дать осколок
			dialog.text = "Hier, nimm meinen Splitter. Bring ihn zu Svenson. Ich nehme an, er ist der Anführer?";
			link.l1 = "Ja, das ist er. Gut, Marcus, wir sehen uns!";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_9":
			dialog.text = "Ja, und ich möchte dir dafür danken, dass du meinen Freund Bernard gerettet hast. Hier, nimm diesen Beutel voll Gold.";
			link.l1 = "Danke! Auf Wiedersehen!";
			link.l1.go = "Temptation_exit";
		break;
		
		case "Temptation_exit":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 300);
			Log_Info("You have received 300 doubloons");
			PlaySound("interface\important_item.wav");
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "25");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "Temptation_13":
			dialog.text = "Ja, er hat mir von der großartigen Ankunft von Charlie Prince auf Turks erzählt... Hat meinen Arsch gerettet, sagst du? Wie? Bernard hat mir etwas von einer Falle erzählt...";
			link.l1 = "Ja, es war eine Falle. Du warst das Ziel, Bernard war nur der Köder...";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_14":
			dialog.text = "Ha-ha-ha, du arbeitest also für den Waldteufel, was, Prinz? Verdienst du bei ihm mehr als bei mir? Sag mir ehrlich!";
			link.l1 = "Marcus, lass uns die Vergangenheit endgültig beiseite legen. Wir haben jetzt ein gemeinsames Ziel und das ist wichtiger als das Plündern von Karawanen. Verdammt! Es ist jetzt das Wichtigste! Die Zukunft der Bruderschaft steht auf dem Spiel!";
			link.l1.go = "Temptation_15";
		break;
		
		case "Temptation_15":
			dialog.text = "Feiner Prinz, ich habe es kapiert! Du bist schließlich ein freier Freibeuter, für den Waldteufel zu arbeiten war deine Entscheidung, und du hast eine gute Entscheidung getroffen... Steven also... Du hast gesagt, er wurde verleumdet, stimmt's?";
			link.l1 = "Absolut richtig.";
			link.l1.go = "Temptation_4";
		break;
		
		// Тени прошлого
		case "shadows":
			dialog.text = "Sicher, ich werde mein Bestes tun, um dir zu helfen! Mach weiter.";
			link.l1 = "Schau mal, Marcus... Hier ist ein Haifischzahn. Was kannst du mir darüber erzählen?";
			link.l1.go = "shadows_1";
		break;
		
		case "shadows_1":
			RemoveItems(pchar, "shark_teeth", 1);
			dialog.text = "Ha! Es ist der Zahn eines weißen Hais, der von Steven Dodson getötet wurde, er hoffte, ein Mädchen zu beeindrucken. Die Leute haben ihn seitdem Hai genannt. Nur wenige könnten das unter Wasser mit einem einfachen Säbel tun. Aber er war jung und dumm und Beatrice Sharp war das schönste Mädchen in der Karibik... Also, wie hast du es bekommen?";
			link.l1 = "Es wurde mir vom ehemaligen Henker von Saint John's gegeben. Dieser Zahn wurde verwendet, um einen Mann zu töten. Sein Name war... Joshua Leadbeater.";
			link.l1.go = "shadows_2";
		break;
		
		case "shadows_2":
			dialog.text = "Das ist eine alte Geschichte. Steven hat diesen Mann getötet. Er war schockiert über den Tod von Beatrice und dachte, dass Leadbeater der einzige lebende Mensch ist, der für ihren Tod verantwortlich ist. Aber später fand er einige Papiere auf Joshuas Leiche, studierte sie und bereute seine Tat.\nDie Maske war nicht an Beatrices Tod schuld, sie brauchte nur den Metzger. Die eifersüchtige Ex-Freundin des Metzgers, Jessica, hatte das alles eingefädelt.";
			link.l1 = "Hast du diese Papiere gelesen?";
			link.l1.go = "shadows_3";
		break;
		
		case "shadows_3":
			dialog.text = "Warum sollte ich? Natürlich nicht. Sie haben mich nicht interessiert. Aber ich kann dir erzählen, warum die Maske den Schlächter verfolgt hat, wenn du etwas Zeit hast. Der betrunkene Steven hat mir diese Geschichte viele Male erzählt.";
			link.l1 = "Ich habe Zeit. Vertrau mir, mein Interesse hat einen Zweck. Ich kann sogar diese Geschichte schreiben.";
			link.l1.go = "shadows_4";
		break;
		
		case "shadows_4":
			dialog.text = "Ich weiß, dass du deine Zeit nie verschwendest. Hör zu dann. Joshua Leadbeater war der englische Marinekapitän und das legendäre 'Neptune' stand unter seinem Befehl...";
			link.l1 = "...";
			link.l1.go = "shadows_5";
		break;
		
		case "shadows_5":
			DialogExit();
			SetLaunchFrameFormParam("One hour later", "Saga_FinalLedbitterStory", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shadows_6":
			AddQuestRecordInfo("Mask", "1");
			dialog.text = "... aber Leadbeater überlebte und wurde von einem Schiff aufgesammelt. Seine Verletzung hat ihn entstellt und seitdem trug er eine Maske. Nach einiger Zeit begannen die Leute, ihn die Maske zu nennen. Rache an dem Mann, der ihn für das Leben gezeichnet hatte, wurde sein Lebensziel.";
			link.l1 = "Ich verstehe... Ich habe alles aufgeschrieben. Ich glaube, ich muss es nochmal durchlesen und es mit all den Informationen, die ich bereits habe, vergleichen. Wirklich eine traurige Geschichte. Hast du jemals Jessica gesehen?";
			link.l1.go = "shadows_7";
		break;
		
		case "shadows_7":
			dialog.text = "Sicher! Sie begleitete den Metzger auf all seinen Reisen, bis er sie für Beatrice verließ. Jess konnte ihm das nicht verzeihen. Die Leute nannten sie das Talisman des Metzgers, weil er immer Glück hatte, solange sie bei ihm war.\nGlaube es oder nicht, aber sobald er sie auf Barbados loswurde, lief sein Geschäft schlecht, die Beute wurde arm und die 'Neptune' war oft zu Gast in der Werft von Isla Tesoro. Aber das kann dadurch erklärt werden, dass der Metzger die meiste Zeit mit Beatrice in der Kabine verbrachte anstatt auf dem Achterdeck.\nBeatrice war nicht wie Jessica, sie war nicht süchtig nach Abenteuern und Krieg, obwohl Nicholas ihr das Fechten und Segeln beibrachte. Ja, sie liebte Seeromane, aber sie hatte nicht genug Härte in sich. Der 'Neptune' des Metzgers war nicht der richtige Ort für sie. Am Ende hat es sie getötet.";
			link.l1 = "Und was ist mit Jessica?";
			link.l1.go = "shadows_8";
		break;
		
		case "shadows_8":
			dialog.text = "Oh, sie war schon etwas Besonderes... Jeder Seemann der 'Neptune' gehorchte ihren Befehlen und nicht nur, weil sie die Freundin des Kapitäns war. Jess war eine Meisterin im Fechten und Segeln, die Mühen des Schlachters waren nicht umsonst. Sie war hart und rücksichtslos, und sie war so schön.\nViele Männer wollten das Bett mit ihr teilen, aber sie wollte nur den Schlachter, sie zu belästigen war wirklich riskant, viele spürten die Folgen buchstäblich auf ihrer eigenen Haut, und für die Hartnäckigsten wurden ihre Fechtstunden die letzten in ihrem Leben.\nJess besaß ein ganz besonderes Schwert, das einzige seiner Art in der Karibik, ich habe keine Ahnung, wo sie es herhatte. Flammenklingenschwert. Die Klinge konnte nicht mit der Hand ergriffen werden und schon die kleinste Berührung hinterließ eine schreckliche Wunde.\nJess war keine Abenteurerin von Geburt an, sondern von Berufung. Übrigens, wenn du mehr über sie erfahren willst, kannst du mit einem Bekannten von dir sprechen. Er kann dir viel mehr über sie erzählen, als ich es kann.";
			link.l1 = "Wirklich? Und wer ist dieser Mann?";
			link.l1.go = "shadows_9";
		break;
		
		case "shadows_9":
			dialog.text = "Jan Svenson. Der Waldteufel wird es nie zugeben, aber er hatte Pläne mit Jessica. Das war die Zeit, als er bereits das Westliche Hauptland für sich genommen hatte und sein Ruhm etwas zum Neid war, also war die Tigerin gut für ihn.\nNachdem der Metzger Jess losgeworden war, begann Jan auffällig oft Barbados zu besuchen, ließ die Garnison vor Angst zittern, er. Wie du weißt, war Jessica die Tochter des Plantagenbesitzers von Bridgetown.\nAlles in allem waren seine Pläne in privaten Kreisen gut bekannt, doch niemand wagte es, seine Meinung dazu zu äußern. Jan mag heutzutage in Blueweld auf seinem Hintern sitzen, aber damals konnte jedes falsche Wort in seiner Adresse schlecht enden.\nAm Ende hat es für sie nicht geklappt. Jess konnte den Schmerz, den Verrats des Metzgers verursacht hatte, nicht ertragen, und sie rächte sich ein Jahr später mit Hilfe der Maske. Diese Rache endete für alle schrecklich: für den Metzger, für Beatrice, für die Maske und für sie selbst. Sie alle starben.";
			link.l1 = "Nein. Der Metzger lebt noch.";
			link.l1.go = "shadows_10";
		break;
		
		case "shadows_10":
			dialog.text = "Was?! Habe ich dich falsch gehört?! Er lebt?!";
			link.l1 = "Ja. Kapitän Schlächter wurde nicht gehängt. Hm, eigentlich wurde er es, aber dank Jakob Jackman und Heinrich dem Henker, die den Henker eingeschüchtert hatten, hat er es lebend geschafft. Die Hinrichtung war nur eine Inszenierung. Ich habe Beweise.";
			link.l1.go = "shadows_11";
		break;
		
		case "shadows_11":
			dialog.text = "Unglaublich! Und wo ist er jetzt?";
			link.l1 = "Er ist bekannt als Lawrence Beltrop und er lebt in Port-Royal. Aber es sieht so aus, als ob er sich nicht verändert hat und immer noch gefährlich ist. Jackman, der viel Aufsehen unter den Brüdern erregt hat, folgte seinen Befehlen.";
			link.l1.go = "shadows_12";
		break;
		
		case "shadows_12":
			dialog.text = "Verdammt! Der Quartiermeister hat seinen Kapitän also doch gefunden! Nach so vielen Jahren... Beltrop sagst du... warte! Jetzt verstehe ich, warum in Blazes Papieren dieses seltsame Protokoll der Vernehmung war... Es scheint, dass Blaze etwas Interessantes über Metzger-Beltrop herausgefunden hat...";
			link.l1 = "Wovon redest du?";
			link.l1.go = "shadows_13";
		break;
		
		case "shadows_13":
			dialog.text = "Als ich diese Residenz eingenommen habe, habe ich mir etwas Zeit genommen, um einen Blick auf Blaze's Papiere zu werfen. Ich habe ein Verhörprotokoll von jemandem namens Samuel Brooks gefunden. Es gab viele Details über die Abenteuer von Thomas Beltrope, einem berühmten Piraten und dem engsten Freund von Nicolas Sharp. Es scheint, dass er der Vater von Schlächter ist.";
			link.l1 = "Interessant. Sieht so aus, als hätten Beltrops und Sharps Kinder die Arbeit ihrer Väter fortgesetzt...";
			link.l1.go = "shadows_14";
		break;
		
		case "shadows_14":
			dialog.text = "Es scheint so... Sag mir, Freund, warum bist du so interessiert an der Vergangenheit von Menschen, die schon lange tot sind? Was soll das alles?";
			link.l1 = "Ich brauche Papiere, die beweisen könnten, dass Ellen McArthur die Tochter von Beatrice Sharp und die Enkelin von Nicolas Sharp ist und alle Rechte hat, diesen Nachnamen zu tragen. Mir ist egal, dass ihr Nachname Beltrop sein könnte.";
			link.l1.go = "shadows_15";
		break;
		
		case "shadows_15":
			dialog.text = "Ich habe nichts über Ellen McArthur in Blazes Archiven gefunden. Es ist seltsam, dass Beatrice Blaze nichts über die Geburt seiner Nichte erzählt hat. Es ist nicht ihr Stil.";
			link.l1 = "Hör zu, vielleicht steht noch etwas mehr in Sharps Papieren über diese Geschichte? Ich brauche jedes Detail, das ich kriegen kann!";
			link.l1.go = "shadows_16";
		break;
		
		case "shadows_16":
			dialog.text = "Hm... Vielleicht. Laut Blazes Notizen versuchte er, die Insel zu finden, auf der seine Schwester gestorben war. Es gibt Kopien von Archivpapieren über Leadbeaters Strafexpedition. Nichts Interessantes, außer ein paar Breitengradzahlen.\nDieser Breitengrad durchquert das karibische Meer in seinem nördlichen Teil. Aber es gibt keine Anzeichen von Längengrad. Offensichtlich scheiterten Blazes Suchen, du kannst dir gar nicht vorstellen, wie viele kleine Inseln auf diesem Breitengrad liegen.";
			link.l1 = "Und was ist die Breitengrad?";
			link.l1.go = "shadows_17";
		break;
		
		case "shadows_17":
			dialog.text = "Lass uns sehen... Hier: 21 32' Nord. Ich weiß nicht, wie es dir helfen kann.";
			link.l1 = "Es kann. Vielen Dank, Marcus, für deine ehrliche Geschichte. Auf Wiedersehen!";
			link.l1.go = "shadows_18";
		break;
		
		case "shadows_18":
			DialogExit();
			pchar.questTemp.Saga.Shadows = "jessika";
			AddQuestRecord("Shadows", "6");
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "I_know_you_good";
			sld = characterFromId("Svenson");
			sld.quest.jessika = "true";
			// рифы доступны для посещения
			i = FindIsland("RockIsland");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			// для любителей самостоятельно добавлять локаторы
			LAi_LocationDisableOfficersGen("Shore67", true);//офицеров не пускать
			// и сразу прерывание
			pchar.quest.Saga_Jess_Island.win_condition.l1 = "location";
			pchar.quest.Saga_Jess_Island.win_condition.l1.location = "Shore67";
			pchar.quest.Saga_Jess_Island.function = "Saga_JessikaIsland"; 
			// активируем квест хронометра Алекса
			pchar.questTemp.AlexClock = "terrax"; // 280912
		break;		
		
		// суп из черепахи
		case "terrapin":
			dialog.text = "Nun, ich kann etwas für dich tun. Wie du weißt, wird die Sicherheit von Tortuga nicht nur durch das Fort La Roche, sondern auch durch eine ständige Piratenschwadron gewährleistet, die die Küsten der Insel bewacht. Der Hafen von Tortuga ist sicher, diese Burschen kennen ihr Geschäft und sie haben mächtige Schiffe. Levasseur lockt diese Kapitäne schon lange.\nSie sind in der Lage, sogar gegen eine Linienschwadron zu kämpfen und sie werden ernsthafte Gegner sein. Also, als Hüter des Kodex und auch als Anführer der Bruderschaft der Küste kann ich diese Wachhunde dazu bringen, die Küsten von Tortuga zu verlassen.";
			link.l1 = "Und das ist alles?";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "Ist das nicht genug? Ich kann dir sowieso nicht mehr helfen. Du musst das Fort zerstören, aber zumindest musst du nicht gegen diese Wachschiffe kämpfen. Glaub mir, sie sind gefährlicher als das Fort, also wird meine Hilfe alles einfacher machen.";
			link.l1 = "Nun, wenn ich sowieso angreifen muss, wird das Verlassen der Piratenstaffel wirklich helfen. Danke, Marcus! Wann kann ich Tortuga angreifen?";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "Wann immer du willst. Die Wachschiffe werden auf mein Signal hin ablegen.";
			link.l1 = "Gut. Dann muss ich gehen, um mich vorzubereiten.";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			DialogExit();
			// Левассера - к барьеру!
			sld = characterFromId("Tortuga_Mayor");
			LAi_LoginInCaptureTown(sld, true);
			pchar.questTemp.Sharlie.Hardcore_Tortuga = "true";
			pchar.questTemp.Terrapin = "hardcore";
			pchar.questTemp.Sharlie.DelTerGuard = "true"; // убираем пиратскую эскадру
		break;
		
		case "pirate_town":
            dialog.text = "Das Problem gelöst? Hast du eine Ahnung, was du angerichtet hast? Wie auch immer, bring mir eine Million Pesos und ich werde die Jungs überreden, deine Tat zu vergessen. Wenn dir die Idee nicht gefällt, kannst du zur Hölle fahren.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Gut, ich bin bereit zu zahlen.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Auf Wiedersehen...";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Gut! Betrachte dich selbst wieder als sauber. Aber ich hoffe, dass du solche ekelhaften Dinge nicht noch einmal tun wirst.";
			link.l1 = "Ich werde nicht. Viel zu teuer für mich. Lebewohl...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		// Addon 2016-1 Jason ------------------------- пиратская линейка --------------------------
		case "Mtraxx":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "Besorg dir erst ein Schiff, dann frag nach Arbeit. Ein Landschubber hat hier nichts zu suchen. Verschwinde!";
				link.l1 = "Hmm... Ich verstehe.";
				link.l1.go = "exit";
				break;
			}
			if(ChangeCharacterHunterScore(Pchar, "spahunter", 0) > 10)
			{
				dialog.text = "Bist du völlig von Sinnen? Die halbe spanische Welt läuft dir hinterher. Du wirst mehr Schaden anrichten als Gutes. Löse deine Probleme, dann bewirb dich. Das ist alles, was ich sagen wollte! Hau ab!";
				link.l1 = "Hmm... Ich verstehe.";
				link.l1.go = "exit";
				break;
			}
            dialog.text = "Hast du Lust auf Action, hm? Ha-ha! Gut... Aber ich warne dich, Junge, bei mir wirst du keine Ruhe finden. Wenn du Angst vor dem Geruch von Schießpulver hast oder kein Blut vergießen kannst - die Tür ist hinter dir. Ich kann Memmen nicht ausstehen. Auch wirst du bei mir nicht lange durchhalten, wenn du ein Spitzel oder eine Ratte bist, die es liebt, den Anteil eines Partners an der Beute zu stehlen. Also was? Bist du dabei?";
			link.l1 = "Ich bin dabei, Marcus. Ich habe keine Angst zu kämpfen und es gibt keinen Hund, der mich als Feigling oder Ratte beschimpfen kann.";
			link.l1.go = "Mtraxx_1";
			link.l2 = "Whoa, das ist zu hart für mich! Entschuldigung, Marcus, aber ich sollte besser meinen Abschied nehmen...";
			link.l2.go = "Mtraxx_exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("LaVega");
		break;
		
		case "Mtraxx_exit":
            DialogExit();
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_wait":
            dialog.text = "Was, bist du immer noch hier?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Ich habe Seide zu verkaufen.";
				link.l2.go = "Mtraxx_silktrade";
				link.l1 = "Ich gehe schon.";
				link.l1.go = "exit";
				break;
			}
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "Mtraxx_1":
            dialog.text = "Ha-ha, na na, mein tapferer kleiner Pirat, dann lass uns Geschäfte besprechen. Mein Informant in Santo Domingo hat mir von einem spanischen Kapitän erzählt, der so reich an blauem Bernstein ist, dass er ihn den Huren schenkt. Hast du schon mal von blauem Bernstein gehört?";
			link.l1 = "Ich habe. Einen seltenen und wertvollen Stein.";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Genau. Sogar hier zahlen Bankiers und Juweliere gutes Geld dafür, und im alten guten Europa kannst du dafür zehnmal mehr bekommen. Bernstein ist kein seltener Stein in der Karibik, aber der blaue ist eine Seltenheit. Und jetzt haben wir irgendeinen schlauen kastilischen Hund, der prahlt, dass er mehr blauen Bernstein hat, als die Bankiers von Kuba und Hispaniola zusammen gelben Bernstein haben.";
			link.l1 = "Kann man den Geschichten eines betrunkenen Spaniers trauen? Hat drei Dublonen gefunden und erzählt allen, dass er El Dorado gefunden hat";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Ich hätte es nicht getan, aber er hat tatsächlich blauen Bernstein an Huren verschenkt. Etwas an seinem Prahlerei muss glaubwürdig sein. Geh nach Santo Domingo und untersuche. Wenn du das Vorkommen von blauem Bernstein findest, wäre das noch besser. Tue dies und ich kann dir eine Belohnung und Respekt in La Vega garantieren.";
			link.l1 = "Was ist, wenn deine Informationen wertlos sind?";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
            dialog.text = "Dann beweise mir, dass dieser Kastilier ein Lügner ist.";
			link.l1 = "Sehr gut. Wer ist deine Quelle in Santo Domingo?";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
			// belamour legendary edition даем флаг и лизензию ГВИК если отсутствует -->
			bOk = IsCharacterPerkOn(pchar,"FlagSpa") || IsCharacterPerkOn(pchar,"FlagHol");
			if(CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 60 && bOk) sTemp = ".";
			else 
			{
				if(bOk) 
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence") || GetDaysContinueNationLicence(HOLLAND) < 60) 
					{
						sTemp = ". Wait a minute, take a trading license for 60 days."; 
						GiveNationLicence(HOLLAND, 60);
					}
				}
				else // нет флага
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence")) 
					{
						sTemp = ". Wait a minute, take a 60-day trade license and a Spanish flag to land in Santo Domingo. From now on, I recommend getting your own, it will help to fool the simpleton in the trading pelvis. This one will be returned to me.";
						GiveNationLicence(HOLLAND, 60);
						SetCharacterPerk(pchar, "FlagSpa");
						log_info("You have received spanish flag");
						pchar.questTemp.GiveMeSpaFlag = true;
					}
					else // есть лицензия
					{	
						if(GetDaysContinueNationLicence(HOLLAND) < 60) 
						{
							sTemp = ". Wait, how are you going to trade without having the right flag?! Here you go, a 60-day trading license, longer than yours. As well as the Spanish flag for landing in Santo Domingo. From now on, I recommend getting your own, it will help to fool the simpleton in the trading pelvis. This one will be returned to me.";
							GiveNationLicence(HOLLAND, 60);
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
						else 
						{
							sTemp = ". Wait, how are you going to trade without having the right flag?! Here, take the Spanish flag for the Santo Domingo landings. From now on, I recommend getting your own, it will help to fool the simpleton in the trading pelvis. This one will be returned to me.";
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
					}
				}
			}
			// <-- legendary edition
            dialog.text = "Du brauchst ein Freudenmädchen namens Gabriela Chapado. Sag meinen Namen und das Passwort - 'Bernsteinkette'. Sie wird dir die Einzelheiten geben. Und verschwende keine Zeit - die Informationen sind noch frisch, aber in ein oder zwei Tagen könnten sie veraltet sein"+sTemp;
			link.l1 = "Verstanden, Marcus. Ich mache mich auf den Weg nach Santo Domingo.";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_1";
			pchar.questTemp.Mtraxx.AffairOfHonor = "true"; // конфликт с делом чести
			pchar.questTemp.ZA.Block = true;			// конфликт с квестом "Заносчивый аристократ"
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_1", "1");
			Mtraxx_JewelryBegin();
			AddMapQuestMarkCity("SantoDomingo", false);
		break;
		
		case "mtraxx_7":
			i = GetCharacterItem(pchar, "jewelry7");
            dialog.text = "Ich bin bereits über deine Ankunft informiert worden. Gib mir einen Bericht!";
			link.l1 = "Ich habe mit diesem blauen Bernstein-Liebhaber fertig gemacht, obwohl es nicht einfach war. Ich habe es geschafft, seine Lager zu finden und sie zu plündern. Ich habe dir gebracht "+FindRussianQtyString(i)+" Stücke von blauem Bernstein.";
			link.l1.go = "mtraxx_8";
			DelLandQuestMark(characterFromId("Terrax"));
			DelMapQuestMarkCity("LaVega");
		break;
		
		case "mtraxx_8":
			if (sti(pchar.questTemp.Mtraxx.JewQty) > GetCharacterItem(pchar, "jewelry7"))
			{
				PlaySound("interface\important_item.wav");
				Log_Info("You have given "+FindRussianQtyString(GetCharacterItem(pchar, "jewelry7"))+" pieces of blue amber");
				RemoveItems(pchar, "jewelry7", GetCharacterItem(pchar, "jewelry7"));
				dialog.text = "Nun, nun... Sohn, erinnerst du dich an meine Warnung vor den Gefahren, eine Ratte zu sein? Was hast du mir damals gesagt? Kein Hund kann dir das vorwerfen? Du denkst, ich bin dumm, Junge? Ich weiß genau, dass du geplündert hast "+FindRussianQtyString(sti(pchar.questTemp.Mtraxx.JewQty))+" Stücke von blauem Bernstein an der Moskitoküste. Jetzt lauf, kleine Ratte, lauf und bete, dass wir uns nie wieder treffen!";
				link.l1 = "Verdammt!";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.Dialog.currentnode = "First time";
				CloseQuestHeader("Roger_1");
				// belamour legendary edition забрать флаг обратно
				if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
				{
					DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
					DeleteAttribute(pchar,"perks.list.FlagSpa"); 
					log_info("You have given spanish flag");
				}
			}
			else
			{
				PlaySound("interface\important_item.wav");
				Log_Info("You have given "+FindRussianQtyString(GetCharacterItem(pchar, "jewelry7"))+" pieces of blue amber");
				RemoveItems(pchar, "jewelry7", sti(pchar.questTemp.Mtraxx.JewQty));
				dialog.text = "Gut gemacht, Junge! Du hast dich von deiner besten Seite gezeigt: eine schwierige Angelegenheit erledigt und alles, was du geplündert hast, mitgebracht. Gute Arbeit! Ich bin froh, dass ich mich in dir nicht getäuscht habe.";
				link.l1 = "Was ist mit meinem Anteil, Marcus?";
				link.l1.go = "mtraxx_9";
			}
		break;
		
		case "mtraxx_9":
			i = sti(pchar.questTemp.Mtraxx.JewQty)/2;
			PlaySound("interface\important_item.wav");
			Log_Info("You have received "+FindRussianQtyString(i)+" pieces of blue amber");
			TakeNItems(pchar, "jewelry7", i);
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("You have given spanish flag");
			}
            dialog.text = "Gesprochen wie ein wahrer Pirat, ha-ha-ha! Die Hälfte der Beute gehört dir. Nimm sie.";
			link.l1 = "Danke, Käpt'n. Hast du noch etwas für mich?";
			link.l1.go = "mtraxx_10";
			DeleteAttribute(pchar, "questTemp.Mtraxx.JewQty");
			CloseQuestHeader("Roger_1");
			Achievment_Set("ach_57");
		break;
		
		case "mtraxx_10":
            dialog.text = "Ich habe immer Aufgaben für fähige Burschen. Es gibt eine heikle Angelegenheit, die ich möchte, dass du dich darum kümmerst. Es gibt ein Schiff in Capsterville, genannt die 'Schlange', unter dem Kommando von Geffrey Brooke, auch bekannt als Kahlkopf Geffrey. Er arbeitet für mich. Ein ausgezeichneter Kämpfer, weiß alles über Kanonen und Klingen, aber in jedem anderen Aspekt des Lebens ein kompletter Idiot. Aber seien wir nicht hart zu Kahlkopf, niemand ist perfekt, ha-ha!\nAlso. Dieser harte Kerl hat einen holländischen Konvoi nördlich von Saint Martin angegriffen und eine Barkasse voller Weizensäcke erbeutet. Das Ding ist, er hat unter den Säcken versteckte Schiffsseide gefunden. Eine wirklich große Ladung. Diese Ware ist extrem wertvoll und selten, die Holländer bringen sie nur für die Bedürfnisse ihres Militärs aus Europa. Diese Seide wird für spezielle Segel verwendet, die die Geschwindigkeit und die Fähigkeit des Schiffes erhöhen, gegen den Wind zu segeln.\nEs ist fast unmöglich zu kaufen, es zu verkaufen ist kein Problem, aber es ist schwer, den richtigen Preis zu finden. Diese verdammten Händler reduzieren immer den Preis! Mir ist bewusst, dass es Leute in der Karibik gibt, die bereit sind, einen guten Preis in Dublonen für diese Seide zu bezahlen, und deine Aufgabe ist es, solche Leute zu finden.\nWas? Jeder Narr kann Karawanen plündern, aber Handel ist nur für Leute mit mindestens einem Anzeichen von Gehirnexistenz im Schädel. Ich plane, Schiffsseide auf monatlicher Basis zu verkaufen, also ist dein Ziel, einen regelmäßigen Käufer zu finden, der mindestens zwanzig goldene Dublonen für eine Rolle zahlen wird. Du hast zwei Monate Zeit dafür, ich kann Kahlkopf Geffrey nicht ewig in Capsterville halten.\nDas ist alles. Setz die Segel nach Capsterville und sprich mit Geffrey, bevor er die Ladung für einen Pfennig an Schmuggler verkauft. Ich habe dir schon gesagt, dass er ein bisschen 'einfach' ist.";
			link.l1 = "Hm... Verstanden. Ich bin schon unterwegs.";
			link.l1.go = "mtraxx_11";
		break;
		
		case "mtraxx_11":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_1";
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_2", "1");
			Mtraxx_SilkBegin();
		break;
		
		case "mtraxx_12":
            dialog.text = "Ha! Hier ist der mutige Kapitän "+GetFullName(pchar)+"! Was ist mit dem Käufer?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				link.l1 = "Ich habe einen Käufer für dich gefunden. Es ist ein Schiffsbauer aus Port Royal. Er benötigt Schiffsseide für seine Produktion und kann monatlich Chargen von hundert Rollen für 25 Dublonen pro Rolle kaufen. Seine Männer werden die Waren vom 10. bis 15. nachts, am Standort Negril Cape, entgegennehmen. Das Passwort - 'Ein Kaufmann aus Lyon'. Es hat mich mehr als zwei Monate gekostet, einen solchen Käufer zu finden, Geffrey muss die Seide bereits an Schmuggler verkauft haben. Es tut mir leid, Marcus.";
				link.l1.go = "mtraxx_15";
			}
			else
			{
				link.l1 = "Ich habe einen Käufer für dich gefunden. Es ist ein Schiffsbauer aus Port Royal. Er benötigt Schiffsseide für seine Produktion und kann jeden Monat Partien von hundert Rollen für 25 Dublonen pro Rolle kaufen. Seine Männer werden die Ware vom 10. bis zum 15. nachts in Empfang nehmen, der Ort ist Negril Kap. Das Passwort - 'Ein Händler aus Lyon'. Kahlkopf Geffrey hat die erste Lieferung bereits nach Jamaika gebracht.";
				link.l1.go = "mtraxx_13";
			}
		break;
		
		case "mtraxx_13":
            dialog.text = "Das ist großartig, mein Freund! Gut gemacht. Es ist schwer, einen Mann zu finden, der sowohl Hände als auch Kopf benutzen kann. Sieh mich in 20 Tagen an, um deine Belohnung abzuholen. Der kahle Geffrey wird bis dahin das Geld von der ersten Transaktion gebracht haben."; // правки прогона 3
			link.l1 = "Sehr gut, Marcus. Bis bald. Ich hoffe, du hast noch einen Job für mich.";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_14":
            dialog.text = "Ich werde. Bis später.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 30, false);
				//SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 40, false);
				AddQuestRecord("Roger_2", "23");
			}
			else
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 20, false); // правки прогона 3
				//SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 30, false);
				AddQuestRecord("Roger_2", "24");
			}
		break;
		
		case "mtraxx_15":
			pchar.quest.Mtraxx_SilkTimeLateAll.over = "yes";
            dialog.text = "Schade, aber trotzdem ein großer Erfolg. Du hast gute Arbeit geleistet! Du wirst deinen Anteil von Geffreys Ladung nicht bekommen, aber du verdienst trotzdem eine Belohnung. Sieh mich in einem Monat an, bis dahin werde ich die erste Ladung an deinen Käufer verkauft haben, dann werden wir sprechen.";
			link.l1 = "Sehr gut, Marcus. Bis bald. Hoffentlich hast du einen weiteren Job für mich.";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_16":
			//pchar.quest.Mtraxx_SilkPayLate.over = "yes";
            dialog.text = "Da bist du ja, "+pchar.name+". Lass uns über deine Belohnung sprechen.";
			link.l1 = "Ich mag solche Gespräche, ha-ha-ha! Ich bin ganz Ohr.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate")) link.l1.go = "mtraxx_19";
			else link.l1.go = "mtraxx_17";
		break;
		
		case "mtraxx_17":
            dialog.text = "Der kahle Geffrey hat deinem Käufer die erste Ladung von 105 Rollen Schiffsseide verkauft. Da ich erwartet habe, sie für zwanzig Dublonen pro Rolle zu verkaufen, denke ich, es wäre fair, dir die Differenz zu geben. Das ist meine Entscheidung. Dein Anteil sind 525 Dublonen plus ein Bonus - eine Dublone pro Rolle. Das macht insgesamt 630 Dublonen. Hier, nimm sie.";
			link.l1 = "Dankbarkeit, Marcus!";
			link.l1.go = "mtraxx_18";
		break;
		
		case "mtraxx_18":
			TakeNItems(pchar, "gold_dublon", 630);
			Log_Info("You have received 630 doubloons");
			PlaySound("interface\important_item.wav");
            dialog.text = "Noch eine Sache. Du kannst aus diesem einen zusätzlichen Gewinn ziehen.";
			link.l1 = "Interessant... Mach weiter.";
			link.l1.go = "mtraxx_19";
		break;
		
		case "mtraxx_19":
            dialog.text = "Dein Käufer will mehr als 100 Rollen Seide für die nächsten zwei Monate geliefert haben. Wenn du welche hast, bring mir 20 bis 100 Rollen zum Preis von 24 Dublonen. Das Angebot gilt für zwei Monate.";
			link.l1 = "Gut! Ich bringe mehr, wenn ich welche habe.";
			link.l1.go = "mtraxx_20";
			pchar.questTemp.Mtraxx.SilkTrade = "true";
			SetFunctionTimerCondition("Mtraxx_SilkTradeOver", 0, 0, 60, false);
		break;
		
		// торговля шелком
		case "mtraxx_silktrade":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "Wie viel hast du?";
			link.l1 = ""+FindRussianQtyString(iTotalTemp)+".";
			if (iTotalTemp > 100) link.l1.go = "mtraxx_silktrade_2";
			else link.l1.go = "mtraxx_silktrade_1";
		break;
		
		case "mtraxx_silktrade_1":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iTotalTemp);
			TakeNItems(pchar, "gold_dublon", iTotalTemp*24);
            dialog.text = "Sehr gut. Nimm das Gold - 24 Dublonen für eine Rolle, wie wir vereinbart haben.";
			link.l1 = "Dankbarkeit!";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_2":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 100);
			TakeNItems(pchar, "gold_dublon", 2400);
            dialog.text = "Ich nehme hundert Rollen. Nimm das Gold - 24 Dublonen für eine Rolle, wie wir vereinbart haben.";
			link.l1 = "Dankbarkeit!";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_3":
            DialogExit();
			npchar.dialog.currentnode = "First time";
			DeleteAttribute(pchar, "questTemp.Mtraxx.SilkTrade");
		break;
		
		case "mtraxx_20":
            dialog.text = "Lass uns über etwas Dringenderes sprechen, willst du dich mit etwas Gefährlichem befassen?";
			link.l1 = "Sicher! Ich und meine Männer sind bereit, sofort in See zu stechen.";
			link.l1.go = "mtraxx_24";
		break;
		
		case "mtraxx_22":
            dialog.text = "Verdammt nochmal, "+pchar.name+", wo zum Teufel warst du? Erinnerst du dich, als ich dir sagte, dass du mich besuchen sollst? Ich hatte einen Job für dich und jetzt ist es dank deinem hervorragenden Timing verschwendet. Du hast mich wirklich wütend gemacht, Junge. Verschwinde, ich arbeite nicht mit Leuten zusammen, auf die ich mich nicht verlassen kann.";
			link.l1 = "Nun, Scheiße...";
			link.l1.go = "mtraxx_23";
		break;
		
		case "mtraxx_23":
			DialogExit();
            npchar.dialog.currentnode = "First time";
			CloseQuestHeader("Roger_2");
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_24":
			// belamour legendary edition даем флаг и лизензию ГВИК если отсутствует -->
			bOk = IsCharacterPerkOn(pchar,"FlagSpa") || IsCharacterPerkOn(pchar,"FlagHol");
			if(CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 40 && bOk) sTemp = ".";
			else 
			{
				if(bOk) 
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence") || GetDaysContinueNationLicence(HOLLAND) < 40) 
					{
						sTemp = ", as well as a trade license for 40 days."; 
						GiveNationLicence(HOLLAND, 40);
					}
				}
				else // нет флага
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence")) 
					{
						sTemp = ", as well as a trade license for 40 days. Besides, how are you going to fool the bungler in the fort?! You will let me down one day with such sloppiness... Here you go... You will return it back upon arrival. The new generation, pah...";
						GiveNationLicence(HOLLAND, 40);
						SetCharacterPerk(pchar, "FlagSpa");
						log_info("You have received spanish flag");
						pchar.questTemp.GiveMeSpaFlag = true;
					}
					else // есть лицензия
					{	
						if(GetDaysContinueNationLicence(HOLLAND) < 40) 
						{
							sTemp = ". Tell me, how are you going to fool the bungler in the fort?! Your paper won't help you without the right flag. I feel that you will let me down one day with such sloppiness... Here, a trading license for 40 days, more than yours. As well as the Spanish flag for landing in Maracaibo. You will return it upon arrival. The new generation, pah...";
							GiveNationLicence(HOLLAND, 40);
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
						else 
						{
							sTemp = ". Tell me, how are you going to fool the bungler in the fort?! Your paper won't help you without the right flag. I feel that you will let me down one day with such sloppiness... Here you go... You will return it back upon arrival. The new generation, pah...";
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
					}
				}
			}
			// <-- legendary edition
            dialog.text = "Then listen closely. Two months ago I had an appointment with a captain by the name of Jean Picard, also known as Jean the Handsome. He didn't show up to the meeting and since I was going to discuss serious matters with him, I did some investigation regarding his whereabouts. Turned out our good brave privateer and his brigantine had managed to engage in a fight with a Spanish heavy galleon under command of don Eduardo de Losad and he is a tough son of a bitch. As a result, Jean and what's left of his crew was taken to Maracaibo and sold to a local plantation. This is where he is, busy with honest labor, at the moment.\nYour tasks are: firstsly - investigate the details of his misfortunes, secondly - get him out from plantation alive and bring him here; I really need details of his story. I am assigning a captain of a barquentine called 'Moray' to assist you in this. Captain's name is Paul Chant also known as Pelly the Cutlass. Remember Geffrey? He is almost as dumb as him, but good at fighting too.\nHe will be waiting for you at cape Ragget Point, on Barbados. Find him and his 'Moray' and sail to Maracaibo. Cutlass will follow your orders without asking stupid questions. Actually, he won't be asking questions at all. Just do your job and come back here, I'll be waiting for you. Here is ten thousand pesos for future expenses"+sTemp+". Any questions?";
			link.l1 = "Nein. Alles ist klar. Auf nach Barbados.";
			link.l1.go = "mtraxx_25";
		break;
		
		case "mtraxx_25":
			AddMoneyToCharacter(pchar, 10000);
            dialog.text = "Ich wünsche dir dann Glück. Sei schnell, lass Cutlass und den armen Jean nicht warten.";
			link.l1 = "Sicher, Boss! Ich bin unterwegs.";
			link.l1.go = "mtraxx_26";
		break;
		
		case "mtraxx_26":
            DialogExit();
			CloseQuestHeader("Roger_2");
			npchar.dialog.currentnode = "mtraxx_wait";
			// belamour legendary edition по пути могут заскочить к Московиту, если рабов нет
			pchar.questTemp.Mtraxx.GiveMeSlaves = "Baster";
			AddQuestRecord("Roger_3", "1");
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddMapQuestMarkCity("baster", false);
			Mtraxx_PlantBegin();
		break;
		
		case "mtraxx_27":
			pchar.quest.Mtraxx_PlantGoHomeOver.over = "yes"; 
            dialog.text = "Willkommen zurück, mein tapferer Korsar, ha-ha! Hast du eine spanische Staffel erledigt? Picard hat es mir bereits erzählt. Gut gemacht!";
			link.l1 = "Ja, meine Jungs haben sie hart getreten, als wir von Maracaibo wegsegelten.";
			link.l1.go = "mtraxx_28";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup3"))
			{
				dialog.text = "Willkommen zurück, mein tapferer Korsar, ha-ha! Picard hat es mir schon erzählt. Gut gemacht!";
				link.l1 = "...";
				link.l1.go = "mtraxx_28";
			}
		break;
		
		case "mtraxx_28":
            dialog.text = "Ich kann in deinen Augen sehen, dass du auf deine Belohnung wartest. Fair genug. Jean wird dich bezahlen, schließlich war es sein Leben, das wir dort zu retten versuchten. Schick ihm später eine Rechnung - der Junge hat keine Crew und kein Schiff. Er ist ein schlauer Kerl, genau wie du, daher wird sein jetziger Zustand nicht lange anhalten.";
			link.l1 = "Hm... Nun... Ich werde meine Zeit abwarten. Gibt es Arbeit für mich, Marcus? Ohne jemanden zu retten oder zu suchen?";
			link.l1.go = "mtraxx_29";
		break;
		
		case "mtraxx_29":
            dialog.text = "Müde davon, die hellste Kerze zu sein? Muss dich enttäuschen: Ich habe genug hirnlose Brut wie Cutlass, deine Talente werde ich entsprechend nutzen. In einem Monat habe ich eine Aufgabe für dich, jetzt solltest du nach Isla Tesoro segeln und Pasquale Lavoisier sehen, er ist ein Händler aus Sharptown.\nEr bat darum, ihm so schnell wie möglich einen harten Piraten für ein ernstes Geschäft zu schicken - wahrscheinlich genau das, was du willst: weniger denken und mehr schießen. Du hast eine Woche Zeit, dich ihm zu zeigen, also verschwende keine Zeit oder du wirst diese Mission verlieren. Und sei höflich, versuche nicht, ihn zu täuschen, dieser Mann wird unter den Brüdern respektiert. Jetzt geh und sieh mich in einem Monat. Sei nicht zu spät!";
			link.l1 = "Gut Marcus. Wir sehen uns!";
			link.l1.go = "mtraxx_30";
		break;
		
		case "mtraxx_30":
            DialogExit();
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("You have given spanish flag");
			}
			CloseQuestHeader("Roger_3");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_4", "1");
			pchar.questTemp.Mtraxx = "pasq_start";
			Mtraxx_PasqualeBegin();
			SetFunctionTimerCondition("Mtraxx_PlantFithTaskTimer", 0, 0, 35, false);
			SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
		
		case "mtraxx_31":
            dialog.text = "Woah! Ein Toter ist zurückgekehrt! Wir haben dich schon begraben, Junge! Aber es scheint, du bist immer noch am Leben";
			link.l1 = "Wie du sehen kannst, Marcus...";
			link.l1.go = "mtraxx_32";
		break;
		
		case "mtraxx_32":
            dialog.text = "Dann warum hat es so lange gedauert, von Maracaibo nach Hispaniola zu kommen? Du bist jetzt aus meiner Organisation raus, Junge. Ich bin wirklich froh, dich lebend zu sehen, aber hier gibt es keine Jobs mehr für dich.";
			link.l1 = "Eh!.. Was für eine Schande...";
			link.l1.go = "mtraxx_33";
		break;
		
		case "mtraxx_33":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_34x":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_34";
		break;
		
		case "mtraxx_34":
			/*if (GetNpcQuestPastDayParam(npchar, "task_date") >= 35 && !bImCasual) // опоздал
			{
				dialog.text = "Verdammt "+pchar.name+", wo warst du?! Ich habe dir gesagt, du sollst mich in einem Monat sehen! Das hier ist zwar nicht das Militär, aber etwas verdammte Disziplin wird erwartet! Verpiss dich, ich werde nicht mehr mit dir arbeiten!";
				link.l1 = "Wie du wünschst...";
				link.l1.go = "mtraxx_33";
				break;
			}*/
			if (GetNpcQuestPastDayParam(npchar, "task_date") < 28) // рано пришёл
			{
				dialog.text = ""+pchar.name+", Ich habe dir gesagt 'sieh mich in einem Monat'. Ich habe jetzt keine Zeit für dich übrig.";
				link.l1 = "Gut...";
				link.l1.go = "mtraxx_34x";
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_angry")
			{
				dialog.text = "Ein Agent von Lavoisier hat mir erzählt, dass du ihn mit seinem schwarzen Holz gefickt hast. Ich habe dich gewarnt, keine Ratte zu sein und fair zu Pasquale zu sein. Du hast beide meine Regeln gebrochen. Du bist ein schlauer Kerl, aber das ist inakzeptabel. Verpiss dich hier raus und vergiss den Weg zu diesem Ort.";
				link.l1 = "Scheiße...";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_fail")
			{
				dialog.text = "Ein Agent von Lavoisier hat mir erzählt, dass du ihn mit seinem schwarzen Holz gefickt hast - hast nicht die ganze Ladung gebracht. Wenn es ein hirnloser Säbel oder Glatzkopf gewesen wäre, hätte ich vielleicht geglaubt, dass sie die ganze Ladung wirklich nicht erbeutet hatten, aber so ein cleverer Kerl wie du... Hast du beschlossen, Pasquale zu täuschen? Ich habe dir gesagt 'täusche ihn nicht'! Ich habe kein Vertrauen mehr in dich, und ich habe auch keine Geschäfte mehr mit dir. Verpiss dich von hier und vergiss den Weg zu diesem Ort!";
				link.l1 = "Dein Lavoisier ist selbst eine Ratte!";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_late" || pchar.questTemp.Mtraxx == "pasq_sink" || pchar.questTemp.Mtraxx == "pasq_esc")
			{
				pchar.questTemp.Mtraxx.CharleePrince = "true"; // атрибут - ГГ известный пират // правки прогона 3
				dialog.text = "Ha! Charlie Prince, ein tapferer Kapitän! Das ist dein neuer Name in La Vega, falls du es noch nicht wusstest. Hast du es also genossen, ein Schläger zu sein? Nein? Hat Dame Glück dir diesmal den Rücken gekehrt? So leben meine hirnlosen Agenten wie Cutlass: heute feiert er in einem Bordell und verschwendet alles, was er verdient hat, in einer Woche steht er vor meiner Tür und bettelt um ein paar tausend, um seine mit Idioten gefüllte Crew zu bezahlen, genau wie er. Was auch immer. Sollen wir über Geschäftliches sprechen?";
				link.l1 = "Sicher!";
				link.l1.go = "mtraxx_36";
				break;
			}
            dialog.text = "Ha! Charlie Prince, ein tapferer Kapitän! Ha-ha! Ein Agent von Lavoisier hat mir erzählt, dass du gut abgeschnitten hast. Ich bin froh, dass du es geschafft hast, unserem Profiteur etwas Respekt zu zeigen.";
			link.l1 = "Es würde ihm nicht schaden, großzügiger zu sein...";
			link.l1.go = "mtraxx_35";
		break;
		
		case "mtraxx_35":
			pchar.questTemp.Mtraxx.Pasquale.Continue = "true"; // правки прогона 3
            dialog.text = "Erinnerst du dich an das, was ich über hirnlose Brutalos und Käufer von gestohlener Ware gesagt habe? Richtig. Übernimm in Zukunft nie einen Job wie diesen. Überlass das Cutlass und solchen Leuten. Egal. Sollen wir über Geschäfte reden?";
			link.l1 = "Sicher!";
			link.l1.go = "mtraxx_36";
		break;
		
		case "mtraxx_36":
            dialog.text = "Großartig! Jean Picard kommt hierher, er wird dir mehr erzählen. Du und Jean werdet bei dieser Mission zusammenarbeiten. Außerdem ist es seine Chance, seine Schulden bei dir zu begleichen... Da ist er ja!";
			link.l1 = "...";
			link.l1.go = "mtraxx_37";
		break;
		
		case "mtraxx_37":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_38";
			chrDisableReloadToLocation = true;
			// преобразуем Пикара
			sld = characterFromId("Mrt_Rocur");
			sld.model = "Jan_Pikar";
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "GunProfessional");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
			GiveItem2Character(sld, "blade_17");
			EquipCharacterbyItem(sld, "blade_17");
			GiveItem2Character(sld, "pistol6");
			EquipCharacterbyItem(sld, "pistol6");
			TakeNItems(sld, "cartridge", 40);
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "cartridge");
			GiveItem2Character(sld, "cirass7");
			EquipCharacterbyItem(sld, "cirass7");
			sld.dialog.currentnode = "rocur_29";
			sld.greeting = "Rocur_03";
			Characters_RefreshModel(sld);
			LAi_SetCheckMinHP(sld, 10, true, "");
			TakeNItems(sld, "potion2", 7);
			TakeNItems(sld, "potion3", 7);
			TakeNItems(sld, "potion4", 7);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "mtraxx_38":
            dialog.text = "Mein Kerl wird sich eurem Überfall anschließen. Er heißt Luka Bayard, meistens bekannt als Luke Leprechaun. Er und seine Männer sind Freibeuter - Jäger, die den größten Teil ihres Lebens im Dschungel von Hispaniola verbracht haben. Sie sind Meister darin, durch den Dschungel zu wandern, fügt ihnen eure Kämpfer hinzu und betrachtet Merida als eures. Ihr bekommt den dritten Teil der Beute. Den Rest nimmt Jean. \nJean, du wirst deine Schulden bei diesem tapferen Kapitän aus deinem Anteil begleichen und dann das, was übrig bleibt, zu mir bringen. Wir werden das dann unter uns klären. Fragen? Wunderbar! Leprechaun wird in unserem Hafen auf euch warten. Viel Glück, Korsaren, ha-ha!";
			link.l1 = "...";
			link.l1.go = "mtraxx_39";
		break;
		
		case "mtraxx_39":
            DialogExit();
			CloseQuestHeader("Roger_4");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_5", "1");
			pchar.questTemp.Mtraxx = "merida_start";
			Mtraxx_MeridaBegin();
			LAi_SetHuberType(npchar);
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "Mtraxx_MeridaAddPicar", 5.0);
			pchar.GenQuest.HunterLongPause = true;
		break;
		
		case "mtraxx_40":
            dialog.text = "Willkommen zurück, mein tapferer Halsabschneider! Gerüchte über deinen Überfall haben uns bereits erreicht.";
			link.l1 = "Kann nicht sagen, dass ich es gern höre. Solche Dinge sollten besser unbekannt bleiben...";
			link.l1.go = "mtraxx_41";
		break;
		
		case "mtraxx_41":
            dialog.text = "Vertrau mir, sie sind es nie, mein Freund. Was auch immer. Hat Picard seine Schuld bei dir beglichen?";
			link.l1 = "Ja.";
			link.l1.go = "mtraxx_42";
		break;
		
		case "mtraxx_42":
            dialog.text = "Sehr gut. Hat Luke Leprechaun einen guten Eindruck auf dich gemacht?";
			link.l1 = "Er hat es getan.";
			link.l1.go = "mtraxx_43";
		break;
		
		case "mtraxx_43":
            dialog.text = "Perfekt dann. Jeder ist glücklich, jeder wird bezahlt.";
			link.l1 = "Hast du einen Job für mich, Marcus?";
			link.l1.go = "mtraxx_44";
			// belamour legendary edition отказ после событий Мериды
			link.l2 = "Du weißt, Marcus, ich habe alles abgewogen und dieser Job ist nichts für mich. Es tut mir leid, aber ich habe meine Entscheidung bereits getroffen.";
			link.l2.go = "mtraxx_44a";
		break;
		
		case "mtraxx_44":
            dialog.text = "Noch keine richtige Arbeit. Aber ich hätte einen persönlichen Gefallen zu bitten. Interessiert?";
			link.l1 = "Sicher Chef. Was für einen Gefallen?";
			link.l1.go = "mtraxx_45";
		break;
		
		case "mtraxx_45":
            dialog.text = "Es liegt eine Pinasse namens 'Kittie' in der Nähe der Küste von La Vega. Sie wartet seit Tagen auf eine Eskorte nach Bridgetown. Auf keinen Fall lasse ich sie aus offensichtlichen Gründen alleine dorthin segeln. Wärst du so freundlich, sie zu begleiten? Wenn du zurückkommst, habe ich eine richtige Aufgabe für dich. Und natürlich Geld, um dich für diese Eskorte zu bezahlen.";
			link.l1 = "Abgemacht.";
			link.l1.go = "mtraxx_46";
		break;
		
		case "mtraxx_46":
            dialog.text = "Schön! Gute Fahrt.";
			link.l1 = "Danke!";
			link.l1.go = "mtraxx_47";
		break;
		
		case "mtraxx_47":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			RemovePassenger(pchar, sld);
			sld = characterFromId("Lepricon");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			CloseQuestHeader("Roger_5");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_6", "1");
			pchar.questTemp.Mtraxx = "ignasio_start";
			sld = characterFromId("Mtr_KittyCap");
			DeleteAttribute(sld, "DontDeskTalk");
			LocatorReloadEnterDisable("LaVega_port", "boat", false);
		break;
		// belamour legendary edition -->
		case "mtraxx_44a":
            dialog.text = "Was?! Ich habe dich von der Straße geholt, deine Taschen mit Bernstein und Edelsteinen gefüllt! So dankst du mir?";
			link.l1 = "Merida hat mir gezeigt, dass ich nicht herzlos genug für diesen Job bin. Nicht so herzlos wie du und deine Leute. Sei nicht böse.";
			link.l1.go = "mtraxx_45a";
		break;
		
		case "mtraxx_45a":
            dialog.text = "Schwächling! Na los, verschwinde! Geh und schindere dich mit Fracht oder, noch besser, saufe dich zu Tode wie der Rest der Verlierer!";
			link.l1 = "...";
			link.l1.go = "mtraxx_46a";
		break;
		
		case "mtraxx_46a":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			RemovePassenger(pchar, sld);
			sld = characterFromId("Lepricon");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			CloseQuestHeader("Roger_5");
			npchar.dialog.currentnode = "First time";
			Group_DelCharacter("Mtr_Kitty", "Mtr_KittyCap");
			sld = characterFromId("Mtr_KittyCap");
			sld.lifeday = 0;
			LocatorReloadEnterDisable("LaVega_port", "boat", false);
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.questTemp.Mtraxx = "fail";
			if(CheckAttribute(pchar, "GenQuest.HunterLongPause")) DeleteAttribute(pchar, "GenQuest.HunterLongPause");
			DoQuestReloadToLocation("LaVega_town", "reload", "reload6", ""); // выставим за дверь
		break;
		// <--- legendary edition
		case "mtraxx_48":
			AddMoneyToCharacter(pchar, 10000);
            dialog.text = "Ach, da bist du ja... Ich habe schon auf dich gewartet. Hier sind 10.000 für die Eskorte von 'Kittie'.";
			link.l1 = "Danke... Ich habe etwas mit dir zu besprechen, Marcus.";
			link.l1.go = "mtraxx_49";
		break;
		
		case "mtraxx_49":
            dialog.text = "Tust du?! Ha-ha! Schieß!..";
			link.l1 = "Erinnerst du dich, wie Jean Picard versklavt wurde? Erst plünderte er einen holländischen Karawanen zusammen mit einem britischen Freibeuter und dann wurde ihm das Gleiche von einer spanischen schweren Galeone angetan.";
			link.l1.go = "mtraxx_50";
		break;
		
		case "mtraxx_50":
            dialog.text = "Erinnere dich. Und?";
			link.l1 = "Ich wurde in Bridgetown von Ignacio Marco angesprochen. Der gleiche portugiesische Freibeuter, der England dient. Er bot mir an, eine holländische Karawane in der Nähe der Küsten einer unbewohnten Insel zwischen Curacao und Trinidad zu plündern.";
			link.l1.go = "mtraxx_51";
		break;
		
		case "mtraxx_51":
            dialog.text = "So-so... Hast du zugestimmt?";
			link.l1 = "Ich habe. Erstens, es war ein gutes Geschäft. Zweitens, ich erinnerte mich an Picards Geschichte und beschloss zu untersuchen...";
			link.l1.go = "mtraxx_52";
		break;
		
		case "mtraxx_52":
            dialog.text = "Ich wette, du hast es getan.";
			link.l1 = "Ja. Es gab eine Karawane, wir haben den Job schön und sauber erledigt. Dann haben wir die Beute an Land verteilt, aber zuerst habe ich heimlich einen Wachmann mit einem Fernglas auf einen Hügel geschickt. Und es hat sich ausgezahlt, da kurz darauf eine spanische Staffel unter Führung einer schweren Galeone auftauchte.";
			link.l1.go = "mtraxx_53";
		break;
		
		case "mtraxx_53":
            dialog.text = "Dein Partner ist sicherlich geflohen, damit die Spanier dich jagen?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.LosadaSink")) 
			{
				link.l1 = "Genau. Sie haben ihm nicht einmal Beachtung geschenkt. Schade für sie: wir haben so hart gegen die Spanier gekämpft, dass sie es nie vergessen werden. Diese Kastilier waren gute Kämpfer, aber wir haben es geschafft, das ganze Geschwader zu besiegen.";
				link.l1.go = "mtraxx_53x";
			}
			else
			{
				link.l1 = "Genau. Sie haben ihm überhaupt keine Aufmerksamkeit geschenkt. Obwohl es mir gelungen ist zu fliehen. Dank meinem Wachmann...";
				link.l1.go = "mtraxx_53y";
			}
		break;
		
		case "mtraxx_53x":
			DeleteAttribute(pchar, "questTemp.Mtraxx.LosadaSink");
            dialog.text = "Heh! Eine Staffel von Eduardo de Losad zu Fall bringen! Du bist ein Seeteufel, Prinz! Ich wette, die Spanier haben bereits Jäger auf deinen Arsch angesetzt.";
			link.l1 = "Schlecht für sie... Trotzdem sollten wir mit diesem Abschaum Ignacio umgehen. Wenn du verstehst, was ich meine.";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_53y":
            dialog.text = "Heh! Ich kann mir nur vorstellen, was für einen Sturm der Entrüstung es gab, als die Kastilier merkten, dass du ihnen entwischt bist! Gut gemacht!";
			link.l1 = "Ihr Problem, nicht meines. Trotzdem sollten wir uns um diesen Abschaum Ignacio kümmern. Wenn Sie verstehen, was ich meine.";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_54":
            dialog.text = "Ich werde mich darum kümmern. Wir sollten mehr über diesen Ignacio Marco erfahren. Er könnte für jemanden arbeiten. Sein 'Interesse' an meinen Männern ist verdächtig. Welches Schiff gehört ihm?";
			link.l1 = "Ein Polacke, der 'Torero'. Ein einzigartiges Schiff, muss ein Originaldesign sein.";
			link.l1.go = "mtraxx_55";
		break;
		
		case "mtraxx_55":
            dialog.text = "Gut, dann ist es einfacher, sie zu verfolgen... Ich habe es verstanden. Und für dich, Prinz, habe ich eine Arbeit. Bist du bereit dafür?";
			link.l1 = RandSwear()+"Auf jeden Fall, Chef!";
			link.l1.go = "mtraxx_56";
		break;
		
		case "mtraxx_56":
            dialog.text = "Hör gut zu. Vor einiger Zeit hatten wir einen neugierigen Piraten in unserer Region. Sein Name war Wulfric Iogansen, auch bekannt als Roter Wolf. Ein sehr farbenfroher Charakter. Er kam vor ein paar Jahren aus dem Norden Europas hierher. Dieser Wikinger zahlte Levasseur keine Schutzgebühr, machte keine Freunde und blieb für sich. Ein sehr verschlossener Typ, niemand hat jemals seine Crew lebend verlassen. Es gab Gerüchte, dass er persönlich denjenigen in seiner Crew die Zungen abschnitt, deren Zungen sich in Tavernen über ihre Raubzüge lösten...\nIm Gegensatz zu den meisten unserer Art verschwendete Wulfric nie Geld für Huren oder Getränke. Hatte nie seine Beute für Pfennige verkauft. Vertraute nie Bankern und wechselte nie die Schiffe. Er hatte eine feine Korvette, die 'Freyja' und eine loyale Crew, die er gut für den Dienst und für das Schweigen bezahlte. Ich glaube, er plante, so viel Gold wie möglich zu horten und dann nach Europa zurückzukehren und dort wie ein König zu leben.\nDank der spanischen Jäger hat es für ihn nicht geklappt. Dieser Mann hatte Spanien gewaltige Schäden und Verluste zugefügt, so dass Strafexpeditionen ihn in den Gewässern von Hispaniola aufspürten und die 'Freyja' versenkten und die ganze Crew zusammen mit dem Wolf töteten. Eingekreist in seichtem Wasser von den spanischen Schiffen traf der Rote Wolf seinen Tod.\nDie Sache ist, jeder in La Vega wusste von Wolfs Schätzen und fand sogar eine gesunkene 'Freyja', aber weder lokale noch indianische Taucher fanden irgendwelche Schätze. Er war kein Narr und muss irgendwo in dieser Gegend einen riesigen Vorrat gehabt haben, von dem nur er und seine Crew wussten, aber wir können sie aus... offensichtlichen Gründen nicht danach fragen. Aber jetzt kommt der interessante Teil: Ich habe sein unbeschädigtes Schiffstagebuch, das in der verschlossenen Truhe auf seinem Schiff versteckt war. Es hat keine offensichtlichen Hinweise auf den Schatz, aber du kannst versuchen, sie zwischen den Worten zu finden. Lies das Logbuch, finde heraus, wo der Wikinger seine Schätze nach zwei Jahren Raub in der Karibik versteckt hat und finde sie. Wenn es dir gelingt - zwei Drittel gehören dir. Bist du dabei?";
			link.l1 = "Hm... klingt, als würde man eine schwarze Katze in einem dunklen Raum suchen. Wo ist das Logbuch?";
			link.l1.go = "mtraxx_57";
		break;
		
		case "mtraxx_57":
            dialog.text = "Hier, nimm es. Viel Glück!";
			link.l1 = "Danke, das werde ich brauchen...";
			link.l1.go = "mtraxx_58";
		break;
		
		case "mtraxx_58":
            DialogExit();
			CloseQuestHeader("Roger_6");
			npchar.dialog.currentnode = "mtraxx_wait";
			GiveItem2Character(pchar, "wolfreeks_book");
			AddQuestRecord("Roger_7", "1");
			pchar.questTemp.Mtraxx = "wolfreek_start";
			pchar.questTemp.Mtraxx.Logbook.CanRead = "true";
			pchar.questTemp.Mtraxx.Logbook.Page1 = "true";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
		break;
		
		case "mtraxx_59":
            dialog.text = "Ach, da ist unser tapferer Kapitän. Was ist mit den Schätzen des Roten Wolfs?";
			link.l1 = "Ich arbeite daran. Ich brauche deine Hilfe dabei.";
			link.l1.go = "mtraxx_60";
		break;
		
		case "mtraxx_60":
            dialog.text = "Ich bin ganz Ohr.";
			link.l1 = "Es gibt ein mir unbekanntes Wort, das mehrmals in Wulfrics Logbuch 'Gord' geschrieben steht. Ich muss seine Bedeutung kennen, um in meiner Untersuchung voranzukommen.";
			link.l1.go = "mtraxx_61";
		break;
		
		case "mtraxx_61":
            dialog.text = "Hm... Gord sagst du... Hab ich auch noch nie gehört. Sehr gut, sieh mich in einer Woche an: Ich werde mich mit einigen klugen Köpfen beraten, die als Zahlmeister auf Schiffen dienen. Sie wissen zumindest, wie man zählt und liest. Sie könnten uns eine Idee geben.";
			link.l1 = "Gut Marcus. Wir sehen uns dann in einer Woche.";
			link.l1.go = "mtraxx_62";
		break;
		
		case "mtraxx_62":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			SetFunctionTimerCondition("Mtraxx_WolfreekTimer", 0, 0, 7, false);
		break;
		
		case "mtraxx_63":
            dialog.text = "Ich habe eine Antwort für dich. Ein Klugscheißer hat mich aufgeklärt. Gord ist eine befestigte Siedlung eines freien Jarls.";
			link.l1 = "Ein freier Jarl? Wer ist das?";
			link.l1.go = "mtraxx_64";
		break;
		
		case "mtraxx_64":
            dialog.text = "Eine Art Piratenadmiral der Wikinger. Zum Beispiel, ich bin ein freier Jarl und La Vega ist mein Gord. Sieht so aus, als ob Roter Wolf die Geschichte seiner Vorfahren genossen hat, ha-ha! Hat dir diese Information geholfen?";
			link.l1 = "Weiß noch nicht. Ich sollte zuerst die Notizen vergleichen. Gord bedeutet dann Siedlung... Danke Marcus!";
			link.l1.go = "mtraxx_65";
		break;
		
		case "mtraxx_65":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			Mtraxx_WolfreekReadLogbookFourth();
		break;
		
		case "mtraxx_66":
            dialog.text = "So? Dein selbstgefälliges Gesicht sagt mir, dass du Erfolg hattest.";
			link.l1 = "Ja. Der Schatz des Roten Wolfs wurde gefunden! Es war allerdings nicht einfach.";
			link.l1.go = "mtraxx_67";
		break;
		
		case "mtraxx_67":
            dialog.text = "Wie viel hat unser Wikinger versteckt?";
			link.l1 = "750.000 Pesos und 900 Dublonen.";
			link.l1.go = "mtraxx_68";
		break;
		
		case "mtraxx_68":
            dialog.text = "Ho-ho! Du hast gut gemacht, Prinz. Was ist mit meinem Anteil?";
			if (sti(pchar.money) >= 250000 && PCharDublonsTotal() >= 300) // belamour legendary edition
			{
				link.l1 = "Hier, nimm das. Gemäß unserer Vereinbarung: 250.000 Pesos und 300 Dublonen.";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "Alle Pesos und Dublonen sind in meiner Kabine. Gib mir eine Minute, um sie hierher zu bringen!";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_68_1":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_68_2";
		break;
		
		case "mtraxx_68_2":
            dialog.text = "Hast du meinen Anteil mitgebracht?";
			if (sti(pchar.money) >= 250000 && PCharDublonsTotal() >= 300) // belamour legendary edition
			{
				link.l1 = "Hier, nimm das. Gemäß unserer Vereinbarung: 250 000 Pesos und 300 Dublonen.";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "Ja-ja, ich bin auf dem Weg!";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_69":
			AddMoneyToCharacter(pchar, -250000);
			RemoveDublonsFromPCharTotal(300); // belamour legendary edition
			PlaySound("interface\important_item.wav");
            dialog.text = "Sehr gut. Du hast wieder hervorragend gearbeitet. Gut gemacht!";
			link.l1 = "Marcus, hast du etwas über Ignacio Marco herausgefunden?";
			link.l1.go = "mtraxx_70";
			// mitrokosta возможность отстройки исламоны
			pchar.questTemp.IslaMona = "start";
		break;
		
		case "mtraxx_70":
            dialog.text = "Ja, aber ich muss es zuerst überprüfen...";
			link.l1 = "Was?";
			link.l1.go = "mtraxx_71";
		break;
		
		case "mtraxx_71":
            dialog.text = "Ich habe den Verdacht, dass Marco mit jemandem in Verbindung steht... Und ich brauche dich, um das herauszufinden. Segel nach Martinique. Lass dein Schiff in Saint Pierre und geh durch den Dschungel nach Le Francois. Mir wurde gesagt, dass unser Mann dort gesehen wurde. Frag nicht die Piraten herum, schau einfach zu und beobachte. Sobald du den Kerl findest, folge ihm und sieh, wohin er geht oder mit wem er sich trifft. Greif ihn oder sein Schiff nicht an, denn damit würdest du einen Plan zerstören, den ich gerade vorbereite! Ich habe dich gewarnt!\nFolge ihm und beobachte ihn, komm zurück zu mir, sobald du genug weißt. Ich verstehe, dass deine Hände darauf brennen, das Arschloch zu erwürgen, aber behalte einen klaren Kopf. Jetzt geh. Du hast drei Wochen. Viel Glück.";
			link.l1 = "Auf meinem Weg, Boss.";
			link.l1.go = "mtraxx_72";
		break;
		
		case "mtraxx_72":
            DialogExit();
			CloseQuestHeader("Roger_7");
			RemoveItems(pchar, "wolfreeks_book", 1);
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_8", "1");
			pchar.questTemp.Mtraxx = "corrida_start";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1.location = "Martinique";
			pchar.quest.mtraxx_corrida_martinique.function = "Mtraxx_CorridaStart";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1.location = "LaVega_exittown";
			pchar.quest.mtraxx_pasq_continue.function = "Mtraxx_PasqualeJan";
			bDisableFastReload = true;
			//SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
			
		case "mtraxx_73":
			/*if (GetNpcQuestPastDayParam(npchar, "task_date") >= 22) // опоздал
			{
				dialog.text = "Verdammt noch mal, Prinz! Du könntest Rache haben und eine höllische Summe Geld, wenn du nicht so langsam wärst! Habe das nicht von dir erwartet, aber da du ein guter Kerl bist, verzeihe ich dir. Du wirst in einem Monat die Chance haben, deinen Ruf in meinen Augen wiederherzustellen. Ich versammle alle für einen Überfall!\nKomm in einem Monat auf einem einzigen, aber mächtigen Schiff zu mir. Luke, Cutlass, Geffrey und Jean werden auch daran teilnehmen. Verspäte dich nicht, auch nicht um einen Tag!";
				link.l1 = "Ich verstehe, Marcus. Das passiert nicht noch einmal!";
				link.l1.go = "mtraxx_73x";
				break;
			}*/
			dialog.text = "Gute Zeitwahl! Berichte mir jetzt.";
			link.l1 = "Ich habe meinen Schuldner in Le Francois aufgespürt. Seine Polacre war Teil eines Geschwaders, bestehend aus einer Korvette und einer Fregatte. Marco selbst hat Barbaszon einen Besuch abgestattet, sie hatten ein zweistündiges Treffen in seinem Haus, andere Besucher wurden von seinen Wachen weggeschickt. Dann verließ er das Haus mit zwei düsteren Kerlen: der eine war ein rotbärtiger Mann in einer Reiterkürass, der andere hatte einen Schnurrbart und trug eine schwere Schützengrabenrüstung. Alle gingen zum Hafen und segelten weg, bevor ich Saint Pierre erreichte.";
			link.l1.go = "mtraxx_74";
		break;
		
		/*case "mtraxx_73x":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "5");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 1, false); // belamour legendary edition увеличим таймер 
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 1, false);
			SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 92, false);
		break;*/
		
		case "mtraxx_74":
            dialog.text = "Das ist gut. Jetzt sehe ich das ganze Bild. Diese beiden Bastarde, die du gesehen hast, arbeiten entweder für Barbazon oder für Jackman. Sie sind fast genauso wie mein Kahlkopf und Entermesser, aber sie kämpfen besser. Der rothaarige heißt Prowler, er ist Kapitän der 'Cuttlefish', einer Korvette, und der Mann mit dem Schnurrbart ist Ghoul, er segelt die 'Merciless', eine Fregatte. Was unseren Freund Ignacio betrifft - er arbeitet nicht nur für die Briten und den spanischen Don Losad, sondern auch für Barbazon. Deshalb versuchte er, dich und Picard zu verleumden.";
			link.l1 = "Warum?";
			link.l1.go = "mtraxx_75";
		break;
		
		case "mtraxx_75":
            dialog.text = "Barbazons Befehl. Du wusstest es nicht, aber Jacques verpasst nie eine Chance, mir in den Brei zu pissen. Er würde mich aus offensichtlichen Gründen niemals offen gegenüberstehen, also hintergeht er mich heimlich. Er wusste, dass Picard und du meine Männer seid. Einen Söldner nach dir zu schicken war ganz sein Stil und er hat keinen Idioten geschickt, wie du dich versichert hast.";
			link.l1 = "Ich werde Barbazon einen Besuch abstatten, sobald ich mich um Marco gekümmert habe...";
			link.l1.go = "mtraxx_76";
		break;
		
		case "mtraxx_76":
            dialog.text = "Hol dir diesen Scheiß aus dem Kopf! Du hast keine Chance gegen Barbazon im offenen Konflikt. Er wird dich leicht ficken. Wir werden ihm mit seiner eigenen Trickkiste antworten - indem wir seine Verbündeten treffen. Bist du bereit dazu? Es ist ein schmutziges Geschäft.";
			link.l1 = "Hört sich nach meiner Art von Geschäft an!";
			link.l1.go = "mtraxx_77";
		break;
		
		case "mtraxx_77":
            dialog.text = "Ignacio Marco, Prowler, Goul und ein anderer Kerl von Barbazon namens Joker Jim haben einen Plan, eines der spanischen Schiffe der Goldenen Flotte zu kapern. Die ganze Operation wurde von Barbazon selbst entworfen und ich habe es geschafft, die Details von meinen Spionen herauszufinden. Ein schwerer Galeone der goldenen Flotte verweilte in Havanna auf der Werft, während die gesamte Staffel nach Spanien aufbrach. Der Galeone wurde repariert und wird bald nach Europa aufbrechen, zusammen mit zwei weiteren Schiffen. Die Staffel wird von Kuba aus nach Nordosten fahren, aber ich weiß nicht, welche Route sie einschlägt.\nMir wurde mitgeteilt, dass die spanischen Schiffe nach Santo Domingo segeln wollten, dann entlang der Küsten von Puerto Rico und direkt in den Ozean. Barbazon weiß das auch. Da Hispaniola jedoch nicht nur von Süden, sondern auch von Norden umrundet werden kann, indem man die Route ändert und über die Turks oder die Isla-Tesoro in den Ozean hinausfährt, ohne Santo Domingo zu betreten, hat Jacques beschlossen, auf Nummer sicher zu gehen und den schlauen Fuchs Ignacio nach Kuba zu schicken.\nMarco hat die Aufgabe, einen Fahrplan des spanischen Galeonen zu erhalten, der von Kuba aus segeln wird und später den Rest der Flotte einholen soll. Er hat Verbindungen innerhalb der Spanier, so dass diese Aufgabe für ihn kein Problem sein wird. Der Rest von Barbazons Bande wartet auf Marco bei Saint Martin, was ein optimaler Ort ist, um mit der Jagd auf diesen Preis zu beginnen. Da Marco und die Niederländer nicht die besten Freunde sind, wird er es nicht schaffen, in die Gewässer von Saint Martin zu gelangen, also wird er seinen Kumpels eine Nachricht aus der Ferne senden müssen...";
			link.l1 = "Ich vermute, ich weiß, was ich hier tun soll...";
			link.l1.go = "mtraxx_78";
		break;
		
		case "mtraxx_78":
            dialog.text = "Es ist mir aufgefallen, dass du so klug bist, aber ich bin noch nicht fertig. Ich habe diesen Plan mit Hilfe von Gabriela Chapada gestört. Du kennst sie. Gemeinsam haben wir den Spaniern mitgeteilt, dass der Piratenhinterhalt nicht weit von Puerto Rico gelegt wird. So wird die Galeone nicht durch dieses Gebiet segeln, stattdessen haben sie heimlich eine Staffel von Piratenjägern dort hingeschickt. Du hast eine Reihe von Aufgaben. Die erste wird sein, den 'Torero' zu finden und zu fangen. Ich denke, du weißt, was du mit ihrem Kapitän anfangen sollst.";
			link.l1 = "Natürlich...";
			link.l1.go = "mtraxx_79";
		break;
		
		case "mtraxx_79":
            dialog.text = "Zweitens, du musst den wahren Kurs der spanischen goldenen Galeone herausfinden. Marco muss ihren Zeitplan haben. Hol es und schick es mir.";
			link.l1 = "Wie?";
			link.l1.go = "mtraxx_80";
		break;
		
		case "mtraxx_80":
			GiveItem2Character(pchar, "Dove"); 
            dialog.text = "Durch die Luft. Nimm einen Käfig... Das ist Spyke, eine Posttaube, die hier in La Vega geboren und aufgewachsen ist. Er wird immer den Weg hierher finden, sogar von Trinidad. Sobald du den Fahrplan hast, schreibe eine Notiz, befestige sie an seinem Bein und lass ihn frei. Spyke wird in ein paar Stunden zu mir fliegen. Pass auf ihn auf, Prinz!";
			link.l1 = "Natürlich, Boss!";
			link.l1.go = "mtraxx_81";
		break;
		
		case "mtraxx_81":
            dialog.text = "Drittens, segeln Sie nach Saint Martin auf der 'Torero'. Nur auf ihr allein! Sonst werden sie zu früh misstrauisch. Senden Sie ihnen ein Signal, nach Puerto Rico zu segeln, wo die Spanier warten. Ihre Signalcodes müssen in Marcos Papieren sein. Oder Sie können sie von ihm persönlich lernen.";
			link.l1 = "Ich verstehe. Ein kluger Schachzug, Barbazons Männer zu den Spaniern zu schicken, ha-ha!";
			link.l1.go = "mtraxx_82";
		break;
		
		case "mtraxx_82":
            dialog.text = "Genau! Ich werde ihm einen Schlag aus dem Schatten verpassen. Genau wie er es getan hat. Und noch eine letzte Sache: Sobald du ihnen ein Signal gibst, segel sofort ab, um die spanische Galeone und ihre Eskorte abzufangen. Es wird keine Zeit mehr zum Verschwenden übrig sein.";
			link.l1 = "Auf einer Polacre? Gegen eine schwere Galeone und zwei weitere Schiffe, und sicherlich keine Schoner? Sie werden mich in Stücke reißen!";
			link.l1.go = "mtraxx_83";
		break;
		
		case "mtraxx_83":
            dialog.text = "Hör auf zu heulen wie ein kleines Mädchen! Warum denkst du, dass du mir Spyke schicken wirst? Du wirst nicht ohne Verstärkung gelassen. Lass nur die Karawane nicht fliehen, lass sie nicht zum Meer kommen. Kapiert?";
			link.l1 = "Ja, Boss.";
			link.l1.go = "mtraxx_84";
		break;
		
		case "mtraxx_84":
            dialog.text = "Deine Belohnung wird eine schwere Ladung Gold plus Marcos Polacre sein. Die Leute sagen, sie sei ein verdammt gutes Schiff. Irgendwelche Fragen? Verstehst du deine Mission?";
			link.l1 = "Ich bin nicht Cutlass, ich weiß, was zu tun ist. Wo soll ich die 'Torero' abfangen?";
			link.l1.go = "mtraxx_85";
		break;
		
		case "mtraxx_85":
            dialog.text = "Während wir uns unterhalten, segelt das Schiff rasch von Kuba nach Philipsburg. Es muss jetzt um Tortuga herum sein oder etwas östlich davon. Also lichtet die Anker und segelt nach Saint Martin, fangt den 'Torero' nicht weit von der Insel, lasst nur nicht Barbazons Männer den Kampf sehen, sonst ist mein Plan ruiniert.";
			link.l1 = "Sofort!";
			// belamour legendary edition испанский флаг к выдаче -->
			if(IsCharacterPerkOn(pchar,"FlagSpa")) link.l1.go = "mtraxx_86";
			else link.l1.go = "mtraxx_85f";
		break;
		
		case "mtraxx_85f":
			SetCharacterPerk(pchar, "FlagSpa");
			log_info("You have received a spanish flag");
			pchar.questTemp.GiveMeSpaFlag = true;
            dialog.text = "Was zum Teufel? Das würde dich mit einem Schürhaken vom Kamin knacken, Prinz. Ich dachte nicht, dass ich über elementare Dinge sprechen müsste. Halt die spanische Flagge hoch, sonst versaust du das ganze Ding, ohne überhaupt anzufangen. Gib sie mir zurück. Jetzt verschwinde hier!";
			link.l1 = "Ich bin bereits auf See, Boss";
			link.l1.go = "mtraxx_86";
		break;
		// <-- legendary edition
		case "mtraxx_86":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			AddQuestRecord("Roger_8", "6");
			pchar.questTemp.Mtraxx = "corrida_marko";
			/*pchar.quest.mtraxx_corrida_landtimer.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.function = "Mtraxx_CorridaLandTimer";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_corrida_checktime.function = "Mtraxx_CorridaCheckTime";*/
			pchar.quest.mtraxx_corrida_torero.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.hour  = sti(GetTime()+12);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.function = "Mtraxx_CorridaToreroOnMap";
			SetFunctionTimerCondition("Mtraxx_CorridaTimeFindTorero", 0, 0, 7, false); // время на перехват Тореро, снимать при потоплении или захвате
		break;
		
		case "mtraxx_87":
            dialog.text = "Also Prinz, du vermasselst alles, Huh?";
			link.l1 = "Ich habe es getan. Diese Mission war eine viel größere Herausforderung als ich dachte. Du kannst mir eine wütende Rede halten und mir die Tür zeigen.";
			link.l1.go = "mtraxx_88";
		break;
		
		case "mtraxx_88": // belamour legendary edition увеличиваем срок
            dialog.text = "Komm schon, lass es. Es passiert. Du bist ein guter Korsar und wir scheitern alle manchmal. Schade, dass wir das Gold nicht bekommen haben... aber wenn wir es nicht an einem Ort bekommen, sollten wir es von einem anderen, ha-ha! Du wirst die Chance haben, deinen Ruf wiederherzustellen: Komm in drei Wochen zu mir, und vorzugsweise auf einem stärkeren Schiff, aber nur auf einem - wir werden eine ganze Staffel sein. Ich versammle alle für einen Überfall!\nKomm in drei Wochen auf einem einzigen, aber mächtigen Schiff zu mir. Luke, Entermesser, Geffrey und Jean werden auch daran teilnehmen. Komm nicht zu spät!";
			link.l1 = "Ich werde nicht befehlen!";
			link.l1.go = "mtraxx_89";
		break;
		
		case "mtraxx_89":
            DialogExit();
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("You have given a spanish flag");
			}
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "22");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 1, false); // belamour legendary edition увеличим таймер 
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 1, false);
			//SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 92, false);
			if (CheckCharacterItem(pchar, "Dove")) RemoveItems(pchar, "Dove", 1);
		break;
		
		case "mtraxx_board":
            dialog.text = "Ho-ho, Ahoy, Junge! Du hast nicht erwartet mich hier zu sehen, richtig? Ha-ha-ha! Wir haben die spanische Karawane schließlich gefunden...";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Gold")) // был абордаж
			{
				link.l1 = "Ja Chef, wir haben, obwohl es nicht einfach war.";
				link.l1.go = "mtraxx_board_1";
			}
			else
			{
				link.l1 = "Ja, aber die goldene Galeone wurde mit all ihrem Gold versenkt.";
				link.l1.go = "mtraxx_board_7";
			}
		break;
		
		case "mtraxx_board_1":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_GOLD);
            dialog.text = "Wie viel Gold haben wir bekommen, Prinz?";
			if (iTotalTemp < 1) link.l1 = "Eh... Nichts.";
			else link.l1 = "Heh... "+iTotalTemp+"insgesamt!";
			link.l1.go = "mtraxx_board_2";
		break;
		
		case "mtraxx_board_2":
			if (iTotalTemp < 20)
			{
				dialog.text = "Verdammt! Die Spanier müssen es ins Meer geworfen haben, damit wir es nicht bekommen. Zumindest haben sie dafür bezahlt. Und auch Barbazons Männer, was ebenfalls ein Sieg ist...";
				link.l1 = "Entschuldigung wegen des Goldes... Was nun, Marcus? Gehen wir nach La Vega?";
				link.l1.go = "mtraxx_board_4";
				AddQuestRecord("Roger_8", "18");
				break;
			}
			if (iTotalTemp >= 20 && iTotalTemp < 300)
			{
				dialog.text = "Erbärmlich. Das entschädigt nicht einmal meine Tour hier. Die Spanier müssen es ins Meer geworfen haben, damit wir es nicht bekommen. Zumindest haben sie dafür bezahlt. So wie auch Barbazons Männer, was ebenfalls ein Sieg ist...";
				link.l1 = "Entschuldigung wegen des Goldes... Teilen wir es trotzdem.";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				break;
			}
			if (iTotalTemp >= 300 && iTotalTemp < 700)
			{
				dialog.text = "Das ist ein schlechter Preis. Gerade genug, um die Unkosten zu decken. Die Spanier müssen einen Teil davon ins Meer geworfen haben, damit wir ihn nicht bekommen. Zumindest haben sie dafür bezahlt. So wie Barbazons Männer, was auch ein Sieg ist...";
				link.l1 = "Entschuldigung wegen des Goldes... Teilen wir es trotzdem.";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				AddCharacterExpToSkill(pchar, "Fortune", 100);
				break;
			}
			if (iTotalTemp >= 700 && iTotalTemp < 1000)
			{
				dialog.text = "Nicht schlecht, obwohl ich Besseres erwartet hatte. Die Spanier müssen einen Teil davon ins Meer geworfen haben, damit wir ihn nicht bekommen. Zumindest haben sie dafür bezahlt. Genau wie Barbazons Männer, was auch ein Sieg ist...";
				link.l1 = "Lass uns den Preis teilen!";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "20");
				AddCharacterExpToSkill(pchar, "Fortune", 200);
				break;
			}
			dialog.text = "Prächtig! Wir haben einen guten Preis erzielt, mein Freund! Und Barbazons Männer haben bekommen, was sie verdienen, ha-ha!";
			link.l1 = "Heh, das ist eine Menge Gold! Teilen wir es!";
			link.l1.go = "mtraxx_board_3";
			AddQuestRecord("Roger_8", "21");
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "mtraxx_board_3":
			RemoveCharacterGoods(pchar, GOOD_GOLD, makeint(iTotalTemp/2));
			WaitDate("", 0, 0, 0, 3, 10);
			LAi_Fade("", "");
            dialog.text = "... wie wir es immer bei den Brüdern tun - ein fairer Anteil für jeden. Du kannst die 'Torero' behalten, sie ist dein Preis.";
			link.l1 = "Was kommt als nächstes, Marcus? Gehen wir nach La Vega?";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_board_4": // belamour legendary edition увеличиваем срок до 3х месяцев
            dialog.text = "Ich werde definitiv in La Vega sein, dort werde ich drei Wochen auf dich warten. Komm, wenn du bereit bist. Vorzugsweise auf einem stärkeren Schiff, aber nur auf einem - wir werden ein ganzes Geschwader sein. Ich bringe all meine Leute in Marsch. Du wirst unter meinem Kommando gehen, Jean Handsome, Bald Geoffrey, Cleaver Pelly und Luke Leprechaun ebenso. Mach dich bereit. Wir erwarten eine ernsthafte Expedition und eine ziemlich große Beute. Alle Details erfährst du später.";
			link.l1 = "Feiner Boss! Wir sehen uns in La Vega in drei Wochen.";
			link.l1.go = "mtraxx_board_5";
		break;
		
		case "mtraxx_board_5":
            dialog.text = "Auf Wiedersehen, Kehlenschlitzer! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "mtraxx_board_6";
		break;
		
		case "mtraxx_board_6":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Ship_SetTaskRunAway(SECONDARY_TASK, sti(npchar.index), sti(pchar.index));
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_corrida_complete.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_corrida_complete.function = "Mtraxx_CorridaComplete";
			RemoveItems(pchar, "wolfreeks_book", 1);
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("You have given spanish flag");
			}
		break;
		
		case "mtraxx_board_6x":
            dialog.text = "Noch etwas?";
			link.l1 = "Nein, ich glaube nicht. Ich gehe schon zu meinem Schiff.";
			link.l1.go = "mtraxx_board_6y";
		break;
		
		case "mtraxx_board_6y":
            DialogExit();
			npchar.DeckDialogNode = "mtraxx_board_6x";
		break;
		
		case "mtraxx_board_7":
            dialog.text = "Heh! Und wessen Schuld ist das, Prinz? War es deine?";
			link.l1 = "Es tut mir leid, Chef, aber wir waren beide gut genug... Du hast auch hervorragend geschossen. Übrigens schöne Zielausrichtung...";
			link.l1.go = "mtraxx_board_8";
		break;
		
		case "mtraxx_board_8":
            dialog.text = "Egal. Die Schuld liegt bei uns beiden. Wir sind jedoch nicht mit leeren Händen - Barbazons Männer haben das bekommen, was wir für sie hatten, ein Sieg an sich...";
			link.l1 = "Es tut mir leid wegen dem Gold... Was kommt als nächstes, Marcus? Gehen wir nach La Vega?";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_90x":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_90";
		break;
		
		case "mtraxx_90":
			pchar.quest.Mtraxx_CartahenaLate.over = "yes";
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Prinz, bist du hirnlos geworden? Ich habe dir gesagt, du sollst nur ein Schiff mitbringen! Geh und werde das Extra los und komm so schnell wie möglich zurück! Jetzt!";
				link.l1 = "In Ordnung, in Ordnung!";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (RealShips[sti(pchar.Ship.Type)].Type.Merchant) // торговые
			{
				dialog.text = "Prinz, hast du beschlossen, mein zweiter Entermesser zu sein? Warum hast du mir ein Handelsschiff gebracht? Ich habe auf dich gezählt! Geh und bring ein anständiges Kriegsschiff! Jetzt!";
				link.l1 = "In Ordnung, in Ordnung!";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) > 3)
			{
				dialog.text = "Prinz, du hast mich überrascht. Ich habe dir gesagt, du sollst ein Kriegsschiff mitbringen! Wie willst du mir auf diesem Kahn helfen? Komm zurück hierher auf einem Schiff der dritten oder zweiten Rang, nicht weniger und nicht höher! Jetzt! Ich werde auf niemanden warten.";
				link.l1 = "In Ordnung, in Ordnung!";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = "Prinz, warum bringst du hier die Sovereign of the Seas? Als ich dir sagte, du sollst ein Kriegsschiff mitbringen, meinte ich nicht, ein verfluchtes Linienschiff zu bringen! Komm zurück hier auf einem Schiff dritten oder zweiten Ranges! Jetzt! Ich werde auf niemanden warten.";
				link.l1 = "In Ordnung, in Ordnung!";
				link.l1.go = "mtraxx_90x";
				break;
			}
            dialog.text = "Gute Zeit, Freibeuter! Froh, dich in einem Stück zu sehen! Bereit für eine Reise?";
			link.l1 = "Sicher, Chef. Immer bereit.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon")) link.l1.go = "mtraxx_91";
			else link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_91":
            dialog.text = "Übrigens, willst du etwas über Barbazon's Geschwader wissen, das du nach Puerto-Rico geschickt hast?";
			link.l1 = "Sie sind mir völlig entfallen. Sicher will ich. Haben sie ihr Verderben gefunden?";
			link.l1.go = "mtraxx_92";
		break;
		
		case "mtraxx_92":
            dialog.text = "Verdammt noch mal, das haben sie! Das Flaggschiff - Joker Jims Fregatte 'Eule', bis auf den Grund abgebrannt. Joker Jim selbst ist spurlos verschwunden. Der Landstreicher und der Ghul wurden hart getroffen, aber sie schafften es zu fliehen: der Landstreicher - nach Tortuga, unter dem Schutz der Kanonen von La Rocha, der Ghul - nach Isla Tesoro. Pasquale hat mir erzählt, dass der Ghul sein Schiff auch auf die Riffe in der Nähe von Sharptown gesetzt hat und kaum davon herunterkam. Meister Alexus hat jetzt viel Arbeit vor sich, hehe. Im Allgemeinen haben mich die Spanier ein wenig verärgert. Ich dachte, sie würden jeden umbringen.";
			link.l1 = "Heh. Was auch immer, wir haben immer noch in Barbazons Stiefel gepisst. Haben ihm eine Nachricht hinterlassen.";
			link.l1.go = "mtraxx_93";
		break;
		
		case "mtraxx_93":
            dialog.text = "Stimmt. Lass uns über Geschäfte sprechen.";
			link.l1 = "Ich bin ganz Ohr.";
			link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_94":
            dialog.text = "Mein Geheimdienst in Form meines guten Freundes Bernard Vensan berichtete von einem riesigen Haufen Goldbarren, den die Spanier in Cartagena gelagert haben. Um genauer zu sein, unter seiner Festung. Normalerweise wäre es der Goldenen Flotte Spaniens zugeschrieben worden, aber dieses Mal gehört es uns. Wir steuern auf Südmain zu, um Cartagena zu stürmen.";
			link.l1 = "Argh! Habe ich das richtig gehört? Werden wir eine ganze Kolonie plündern, mit einer verdammten Festung?";
			link.l1.go = "mtraxx_95";
			// belamour legendary edition отказ от великого похода
			link.l2 = "Ich gehe nicht mit dir nach Cartagena, Marcus. Eine ganze Stadt niederzubrennen ist nicht meine Geschichte.";
			link.l2.go = "mtraxx_94a";
		break;
		
		case "mtraxx_95":
            dialog.text = "Du hast richtig gehört. Genau das werden wir tun. Mein Kriegsschiff wird sich um das Fort kümmern, natürlich mit deiner Hilfe. Der kühne Jeffrey wird die Bodentruppen mit seinem neuen Ostindischen, den er den Holländern gestohlen hat, transportieren. Pelly hat endlich seine zerlumpten Briggantine los und hat eine ordentliche Korvette bekommen, natürlich nicht ohne meine finanzielle Hilfe. Paul Chant und du seid für die Ausschaltung der Patrouillenflotte verantwortlich, auch eure Besatzungen nehmen am Sturm teil, und du, Charles, so ein guter Kämpfer und Kapitän, wirst mir helfen, das Fort zu zerstören.\nJean Picard ist nicht aufgetaucht, was seltsam ist, da seine Korvette in Port Royal gesehen wurde. Nun, wenn er kein Interesse an spanischem Gold hat, dann ist das sein Problem, also fick ihn. An seiner Stelle wird mein Freund Bernard Vensan dem Überfall beitreten. Außerdem wird der Leprechaun mit seinen Freibeutern unsere Truppen unterstützen. Wir werden das Gold aus dem Fort und das Lösegeld aus der Stadt nehmen. Das werden sie nicht vergessen, ha-ha!\n Jetzt geh und ruh dich aus. Und komm heute Abend zu mir und den anderen Kapitänen in die Taverne! Wir sollten auf unsere Sache trinken! Ich werde den Barkeeper beauftragen, alle lokalen Alkoholiker rauszuwerfen, so dass nur noch sechs von uns und einige charmante Mädchen in der Taverne sein werden. Du trinkst heute Abend mit deinen Kameraden, und morgen früh wirst du das Geschwader anführen, du wirst den Kurs ebnen. Und versuche, uns so schnell wie möglich nach Cartagena zu bringen. Alles klar?";
			link.l1 = "Jawohl, jawohl, Chef!";
			link.l1.go = "mtraxx_96";
		break;
		
		case "mtraxx_96":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			chrDisableReloadToLocation = true;
			CloseQuestHeader("Roger_8");
			pchar.questTemp.Mtraxx = "cartahena";
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "LaVega_townhall", "goto", "goto3");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaReloadInTavern", 10.0);
			pchar.worldmapencountersoff = "1"; // уберем враждебные энкаунтеры
		break;
		// belamour legendary edition -->
		case "mtraxx_94a":
            dialog.text = "Du... du... verrückter Prinz! Legst du mich rein?! Weißt du was, zum Teufel mit dir! Du hattest die Chance, in die Bruderschaft einzutreten, du hattest die Chance, aus den Reihen all dieses nutzlosen Viehs zu entkommen. Und du hast diese Chance feige verpasst. Verzieh dich mit deinem Gejammer! Schwächling! Noch einmal wirst du sehen - ich werde die Hunde loslassen!";
			link.l1 = "...";
			link.l1.go = "mtraxx_95a";
		break;
		
		case "mtraxx_95a":
            DialogExit();
			QuestSetCurrentNode("Terrax", "First time");
			CloseQuestHeader("Roger_8");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Corrida");
			DeleteAttribute(pchar, "questTemp.Mtraxx.InTavern");
			LocatorReloadEnterDisable("LaVega_town", "reload6", true); // закрыть на месяц
			SetFunctionTimerCondition("Mtraxx_CartahenaLateOpen", 0, 0, 30, false);
			Mtraxx_TerraxReset(8);
			DoQuestReloadToLocation("LaVega_town", "reload", "reload6", ""); // выставим за дверь
		break;
		// <-- legendary edition
		case "mtraxx_97":
            dialog.text = "Prinz, wo zum Teufel warst du? Setz dich! Schon? Gut gemacht. Lass uns anfangen! \nMeine tapferen Korsaren, heute Nacht gehören euch der beste Rum und die besten Frauen! Das Gold von Cartagena wartet auf uns, und ich schwöre meinen Freunden, ihr werdet es bekommen! Also lasst uns auf unseren gemeinsamen Erfolg trinken! Bis zum letzten Tropfen!";
			link.l1 = "";
			link.l1.go = "mtraxx_98";
		break;
		
		case "mtraxx_98":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			LAi_SetSitType(npchar);
			DoQuestCheckDelay("Mtraxx_CartahenaTavernSong", 1.0);
		break;
		
		case "mtraxx_99":
            dialog.text = "Zeit, ihnen zu zeigen, wer wir sind, Korsaren. Kobold! Nimm deine Männer und übernimm die Kontrolle über die Stadttore. Wir wollen nicht, dass sie Verstärkungen zum Fort schicken! Schlage sie hart in den Rücken, wenn wir durch die Soldaten des Forts stürmen!";
			link.l1 = "";
			link.l1.go = "mtraxx_100";
		break;
		
		case "mtraxx_100":
            dialog.text = "Prinz und Paul! Ihr habt das Militärgeschwader mit den drei Schiffen gesehen, macht sie fertig. Haltet euch von der Festung fern und entert nicht ihre Schiffe. Wir haben weder Zeit noch Position, um uns mit Beute zu beschäftigen. Ist alles klar?! Prinz, ich rede besonders mit dir, ich weiß von deiner Sucht nach Heldentum, du wirst später Gelegenheit dazu haben!\nKommt nicht zu nahe an die Festung, macht diese Schiffe fertig und kommt zurück! Wir werden hier auf euch warten. Ist alles klar? Großartig, ha-ha-ha-ha! Angriff!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaSquadronAttack");
		break;
		
		case "mtraxx_101":
            dialog.text = "Also, die spanische Staffel ist endgültig weg. Jetzt ist es Zeit für den 'Roten Drachen', seine Rolle zu spielen. Wir werden das Fort von Cartagena in einen Schutthaufen verwandeln. Bist du bei mir?";
			link.l1 = "Sicher!";
			link.l1.go = "mtraxx_102";
		break;
		
		case "mtraxx_102":
            dialog.text = "Die 'Rote Drache' ist ein sehr robustes Schiff mit einer mächtigen Artillerie, deines kann ihr nicht das Wasser reichen. Also sei vorsichtig, spiel nicht den Helden und halt dich fern von meinen Kanonen!";
			link.l1 = "...";
			link.l1.go = "mtraxx_103";
		break;
		
		case "mtraxx_103":
            DialogExit();
			
			Weather.Wind.Speed = 16.0;
			pchar.wind.speed = Weather.Wind.Speed;
			fWeatherSpeed = stf(Weather.Wind.Speed);//халява первого выхода
	
			Weather.Wind.Angle = 0.0;
			pchar.wind.angle = Weather.Wind.Angle;
			fWeatherAngle = stf(Weather.Wind.Angle);//халява первого выхода
			
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Group_FindOrCreateGroup("Terrax_SeaGroup2");
			Group_DelCharacter("Terrax_SeaGroup", "Jeffry");
			Group_DelCharacter("Terrax_SeaGroup", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Jeffry");
			Group_AddCharacter("Terrax_SeaGroup2", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Pelly");
			Group_SetGroupCommander("Terrax_SeaGroup2", "Jeffry");
			Group_SetTaskNone("Terrax_SeaGroup2");
			Group_LockTask("Terrax_SeaGroup2");
			sld = CharacterFromID("Cartahena Fort Commander");
			LAi_SetImmortal(sld, false);
			Ship_SetTaskAttack(SECONDARY_TASK, sti(npchar.index), sti(sld.index));
			AddQuestRecord("Roger_9", "5");
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.questTemp.Mtraxx.Cartahena.Fort = "true";
			SetFunctionExitFromLocationCondition("Mtrxtofort", pchar.location, false);
		break;
		
		case "mtraxx_104":
            dialog.text = RandSwear()+"Verdammt gute Schlacht! Das ist es, meine tapferen Korsaren! Cartagena gehört uns! Der Widerstand ist gebrochen! Mutig, Kobold! Komm mit mir zur Festung - Bernie muss das Gold schon gefunden haben. Prinz, nimm den Entermesser und verhandle mit dem Gouverneur, um uns ein Lösegeld von 250.000 Pesos zu zahlen! Sie haben das Geld, also sei hartnäckig. Ich weiß, du kannst es.";
			link.l1 = "Heh! Mit Vergnügen, Boss!";
			link.l1.go = "mtraxx_105";
		break;
		
		case "mtraxx_105":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "Cartahena_fort", "goto", "goto10", "", 5.0);
			sld = CharacterFromID("Jeffry");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto11", "", 5.0);
			sld = CharacterFromID("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto12", "", 5.0);
			sld = CharacterFromID("Pelly");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			AddQuestRecord("Roger_9", "6");
			// запрещаем драки в городе, резиденции, форте
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_fort")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_town")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_townhall")], true);
			LAi_LocationDisableOfficersGen("Cartahena_townhall", true);
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1 = "locator";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.location = "Cartahena_town";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator = "reload3_back";
			pchar.quest.mtraxx_cartahena_townhall.function = "Mtraxx_CartahenaToResidence";
		break;
		
		case "mtraxx_106":
            dialog.text = "Wie geht es Ihnen, Prinz?";
			link.l1 = "Alles ist prächtig. Ich habe die Reichen von Cartagena gezwungen, 350.000 Pesos zu zahlen.";
			link.l1.go = "mtraxx_107";
		break;
		
		case "mtraxx_107":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "Ho-ho, das ist mein Junge! Aber wo ist das Geld?";
				link.l1 = RandSwear()+"Ich bringe es in einem Moment!";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "Ho-ho, das ist mein Junge! Du und der Entermesser könnt jeweils 50.000 als Bonus für Schnelligkeit und Einfallsreichtum behalten. Der Rest wird später unter uns allen aufgeteilt.";
				link.l1 = "Hier hast du es!";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_107x":
           DialogExit();
		   npchar.dialog.currentnode = "mtraxx_108";
		break;
		
		case "mtraxx_108":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "So? Hör auf zu spielen und bring die Münzen hierher!";
				link.l1 = "Auf meinem Weg!";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "Großartig! Du und der Entersäbel dürft jeweils 50.000 als Bonus für Schnelligkeit und Einfallsreichtum behalten. Der Rest wird später unter uns allen aufgeteilt.";
				link.l1 = "Hier hast du es!";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_109":
			AddMoneyToCharacter(pchar, -300000);
            dialog.text = "Du musst dich um unser Gold sorgen? Es wurde gefunden - 5.000 Einheiten und es wird bereits zu unseren Schiffen transportiert. Die Aufteilung ist bereits erfolgt, die Männer haben zugestimmt, wir hoffen, dass Cutlass und du auch nicht widersprechen werden.";
			link.l1 = "Wie groß ist mein Anteil?";
			link.l1.go = "mtraxx_110";
		break;
		
		case "mtraxx_110":
            dialog.text = "Da die ganze Operation von mir geplant wurde, plus der 'Rote Drache' hat die härteste Arbeit geleistet, die Festung zu bekämpfen, werden ich und meine Männer die Hälfte der Beute erhalten. Die andere Hälfte wird zwischen den Kapitänen der anderen vier Schiffe entsprechend der Anzahl ihrer Besatzungsmitglieder aufgeteilt. Du hast "+GetCrewQuantity(pchar)+" Männer zur Verfügung, dein Anteil ist "+sti(pchar.questTemp.Mtraxx.Cartahena.Gold)+" Einheiten Gold und "+sti(pchar.questTemp.Mtraxx.Cartahena.Money)+" Pesos.";
			link.l1 = "Nun, wenn alle damit einverstanden sind, dann bin ich es auch!";
			link.l1.go = "mtraxx_111";
		break;
		
		case "mtraxx_111":
            dialog.text = "Prächtig. Herzlichen Glückwunsch zu dieser erfolgreichen Reise, Korsaren! Hier bleibt nichts für uns übrig, Zeit nach Hause zu gehen. Wir alle, einschließlich mir, erhalten einen Monatsurlaub. Nicht du, Prinz, ich habe eine andere Aufgabe für dich. Siehst du, Janette, eine Madame des Bordells von Tortuga, hat sich über dich beschwert: sie sagte, dass Charlie Prinz ihrer Einrichtung nicht viel Aufmerksamkeit und Liebe schenkt. Deshalb befehle ich dir, nach Tortuga zu segeln, zu Janette zu gehen und dort deine Boni zu verschwenden. Du hast es verdient. Mach die Madame und ihre Mädchen glücklich. Ich will dich nicht sehen, bevor du dich auf Tortuga ausgeruht hast, ha-ha-ha!";
			link.l1 = "Habe verstanden, Boss. Das ist der angenehmste Auftrag, den ich je erhalten habe. Wird erledigt!";
			link.l1.go = "mtraxx_112";
		break;
		
		case "mtraxx_112":
            dialog.text = "Auf Wiedersehen, Herren! Geht auf eure Schiffe und setzt die Segel! Wir sehen uns alle in La Vega!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaFinal");
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "mtraxx_113":
            dialog.text = "Was?! Jean ist jetzt eine Hure der Engländer, Bold und Cutlass sind verschwunden, Leprechaun und seine Männer sind nirgendwo zu finden! Und jetzt du?!";
			link.l1 = "Marcus, ich habe meine Entscheidung getroffen. Ich habe gutes Geld verdient, du hast auch ein ziemliches Vermögen an mir verdient. Aber ich bin fertig. Ich gehe.";
			link.l1.go = "mtraxx_114";
		break;
		
		case "mtraxx_114":
            dialog.text = "Du, genau wie Picard, denkst, dass du alleine besser verdienen kannst? Ja? Denkst, du kommst ohne mich aus? Ha-ha-ha! Verpiss dich, Prinz, ich halte dich nicht fest. Bald, sehr bald wirst du sehen, wie falsch du lagst und dann wirst du zurückkommen und mich anflehen, deinen elenden Arsch zurückzunehmen. Und weißt du was? Ich werde es nicht tun! Ha-ha! Verschwinde aus meinen Augen!";
			link.l1 = "...";
			link.l1.go = "mtraxx_115";
		break;
		
		case "mtraxx_115":
            DialogExit();
		    npchar.quest.mtraxx_complete = "true";
		break;
		
		// Jason НСО
		case "patria":
			dialog.text = "Ho-ho! Du bist am richtigen Ort! Spuck es aus!";
			link.l1 = "Es gibt einen Burschen, der keine Angst vor Piraten hat. Er nimmt sie nicht ernst. Ihm muss eine Lektion in Respekt erteilt werden. Denk daran, töte ihn nicht.";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "Huh! Wenn das nicht der alte Mann Charles ist! Ich wette, du hast dich wieder in eine Affäre verwickelt! Lass uns zu den Details kommen, wer ist diesmal das Ziel und was sollen wir ihm beibringen?";
			link.l1 = "Ein Gast aus Europa, ein Inspektor des französischen Finanzministeriums - Baron Noel Forget. Er möchte hier eine französische Handelsgesellschaft gründen, aber ich und ein enger Freund von mir sind dagegen. Wir haben versucht, den Baron zu überzeugen, dass der Handel hier wegen der Holländer, Engländer und insbesondere der Piraten nach der Niederlage von Levasseur sehr riskant wäre, aber er hörte nicht zu. Wir müssen ihm Angst einjagen, damit er es auf seiner eigenen Haut spürt.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_x":
			dialog.text = "Ho-ho! Du bist am richtigen Ort! Spuck es aus!";
			link.l1 = "Es gibt einen Kerl, der keine Angst vor Piraten hat. Er nimmt sie nicht ernst. Ihm muss eine Lektion in Respekt erteilt werden. Denk daran, töte ihn nicht.";
			link.l1.go = "patria_x1";
		break;
		
		case "patria_x1":
			dialog.text = "Huh! Warum hast du dich plötzlich entschieden, Piraten anzuspannen? Gut, mir ist es egal, solange du mich bezahlst. Kommen wir zu den Details, wer ist diesmal das Ziel und was sollen wir ihm beibringen";
			link.l1 = "Ein Gast aus Europa, ein Inspektor des französischen Finanzministeriums - Baron Noel Forget. Er möchte hier eine französische Handelsgesellschaft gründen, aber ich und ein enger Freund von mir sind dagegen. Wir haben versucht, den Baron davon zu überzeugen, dass der Handel hier wegen der Niederländer, Engländer und insbesondere der Piraten nach der Niederlage von Levasseur sehr riskant wäre, aber er hat nicht zugehört. Wir müssen ihm Angst einjagen, damit er es auf seiner eigenen Haut spürt.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			dialog.text = "Ja-ja... Ein echter Baron! Sollten wir sein Schiff angreifen?";
			link.l1 = "Hier ist der Plan: Sein Schiff wird bald von Port-au-Prince nach Capsterville abfahren. Du musst den Baron in der Nähe von Saint Kitts abfangen und ihn als Geisel nehmen. Es wäre besser, wenn du das Schiff nicht versenkst und das Töten von Männern vermeidest. Die Franzosen sind schließlich unsere Freunde. Wirst du damit umgehen können?";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			dialog.text = "Nun, ich kann nichts versprechen. Aber ich werde es versuchen. Welches Schiff ist es?";
			link.l1 = "Eine Brigg namens 'Favory'.";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "Eine Brigg ist kein Gegner für meinen 'Roten Drachen'. Wir werden leicht mit ihnen fertig. Wenn sie sich ergeben, lasse ich jeden am Leben.";
			link.l1 = "Perfekt. Jagt ihnen Angst ein und bietet ihnen an, sich zu ergeben. Schickt danach den Baron ins rattenverseuchte Unterdeck. Versucht, den schmutzigsten Ort zu finden, den ihr könnt, aber behaltet ihn dort nicht länger als einen Tag, sonst könnte er krank werden und sterben. Dann bringt ihn in die Kabine, findet und sperrt ihn an einem abgelegenen Ort ein. Verkleidet einige eurer Männer als gefangene französische Kaufleute und lasst sie sich so verhalten. Drei Tage lang sollten sie ihm erzählen, wie die rücksichtslosen Piraten sie jagen, ausrauben, Lösegeld fordern, sie foltern... mit allen erforderlichen Details.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "Ha-ha-ha! Das muss der lustigste Job sein, den ich seit sehr langer Zeit angenommen habe! Nun, ich werde solche Schauspieler finden, Bursche. Zweifle nicht daran, nach ihren Geschichten wird dein Baron in die Hosen scheißen! Sie werden ihm Narben von Säbeln und erhitzten Ladestöcken zeigen...";
			link.l1 = "Perfekt! Dann wirst du ihn zwingen, einen Brief an de Poincy zu schreiben, in dem er um Lösegeld bittet. Dreieinhalb Millionen für so einen großen Fisch sind nicht viel.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			dialog.text = "Gut. Was machen wir als nächstes?";
			link.l1 = "Und dann bringst du den Baron zu den Turks. Dort nimmst du das Lösegeld entgegen und übergibst mir den Baron. Und zusätzlich solltest du ihm sagen, dass alle Franzosen für Tortuga und Levasseur büßen werden und das nicht nur einmal.";
			if (CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax")) link.l1.go = "patria_x7";
			else link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			dialog.text = "Ha-ha-ha! Das ist ein verdammt guter Trick! Wir persönlich, nun, du weißt, was wir mit Levasseur gemacht haben, und jetzt... ha-ha-ha!.. Gut, Junge. Es wird gemacht! Also sagst du, dass das Schiff bald ankommen wird?";
			link.l1 = "Bald. Wir müssen auf der Hut sein.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_x7":
			dialog.text = "Ha-ha-ha! Das ist ein verdammt guter Trick! Wie viel sollte ich dir für diese Farce berechnen? Gut, hunderttausend werden den Deal besiegeln. Gib mir das Geld.";
			if (sti(pchar.money) >= 100000) 
			{
				link.l1 = "Nimm es.";
				link.l1.go = "patria_x8";
			}
			else
			{
				link.l1 = "In Ordnung, ich bringe es.";
				link.l1.go = "patria_xwait";
			}
		break;
		
		case "patria_xwait":
			DialogExit();
			pchar.questTemp.Patria.Condotier.NeedMoney = "true";
		break;
		
		case "patria_x8":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = "Perfekt! Sagst du, dass das Schiff bald ankommen wird?";
			link.l1 = "Bald. Wir müssen auf der Hut sein.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_8":
			dialog.text = "Mach dir keine Sorgen, ich werde dich nicht im Stich lassen. Ich werde das persönlich regeln. Wenn du ein Gerücht hörst, dass der Baron gefangen genommen wurde, komm zu mir.";
			link.l1 = "Gut. Meinen Dank, Marcus.";
			link.l1.go = "patria_9";
		break;
		
		case "patria_9":
			DialogExit();
			AddQuestRecord("Patria", "71");
			pchar.questTemp.Patria = "epizode_12_wait";
			pchar.questTemp.Patria.Condotier.Success = "true";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
			else LocatorReloadEnterDisable("Lavega_town", "reload6", true);
		break;
		
		case "patria_10":
			dialog.text = "Natürlich, Junge. Wie vereinbart. Schreckliche Geschichten über böse Piraten, die unschuldige französische Kaufleute abschlachten, das Geräusch einer Peitsche, Stöhnen und Schreien. Kohlenbecken und versengte Handschellen. So wie es sein sollte.";
			link.l1 = "Woah woah! Halt deine Pferde! Ich brauche ihn lebendig";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "Mach dir keine Sorgen, er wird leben. Er hat diesen Brief mit zitternder Hand geschrieben. Hier ist er.";
			link.l1 = "Was steht da? Er fleht Poincy an, ihn hier rauszuholen?";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "Stimmt, Bursche! Er bettelt, ha!";
			link.l1 = "Werf diesen Brief weg, oder besser - verbrenn ihn. Wir treffen uns in einer Woche auf Turks. Es muss so aussehen, als ob wir Zeit brauchen, um das Lösegeld zu sammeln.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			dialog.text = "Verstanden. In einer Woche, nördlicher Golf auf Turks. Vergiss nicht, das Geld mitzunehmen: es muss gut aussehen. Nach all dem komm zu mir, wir werden es besprechen.";
			link.l1 = "Natürlich, bis später, Marcus!";
			link.l1.go = "patria_14";
		break;
		
		case "patria_14":
			DialogExit();
			AddQuestRecord("Patria", "73");
			pchar.questTemp.Patria = "epizode_12_terks";
			SetFunctionTimerCondition("Patria_CondotierTerks", 0, 0, 7, false);
			SetFunctionTimerCondition("Patria_CondotierTerksOver", 0, 0, 14, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		case "patria_15":
			pchar.quest.Patria_CondotierTerksOver.over = "yes"; //снять таймер
			dialog.text = "He, Froschfresser! Halt!";
			link.l1 = "Ich bewege mich nicht.";
			link.l1.go = "patria_16";
		break;
		
		case "patria_16":
			dialog.text = "Hier ist dein Baron. Ein bisschen abgenutzt, heh, aber in einem Stück. Er ist noch erkennbar? Ha-ha-ha!";
			link.l1 = "Ja... irgendwie.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "Perfekt. Jetzt gib das Geld her oder er ist erledigt! Und versuche nicht, uns zu täuschen, wir haben dich im Visier!";
			if (sti(pchar.money) >= 350000)
			{
				link.l1 = "Hier, nimm es.";
				link.l1.go = "patria_18";
			}
			else
			{
				link.l1 = "Verdammt! Ich habe es auf dem Schiff vergessen...";
				link.l1.go = "patria_22";
			}
		break;
		
		case "patria_18":
			AddMoneyToCharacter(pchar, -350000);
			dialog.text = "Ha-ha-ha! Du bist ein schlauer Bursche, Franzos. Nimm deine 'Eminenz'. Und sag Poincy, er solle das Geld bereitstellen: du wirst für das bezahlen müssen, was du Levasseur und Tortuga angetan hast. Und deine Feilscher werden uns mit ihren Waren und Schiffen bezahlen. Ha-ha-ha! Vergiss nicht, uns noch mehr Barone zum Archipel zu bringen, sie bringen uns viel Profit! Ha-ha-ha!";
			link.l1 = "Bitte, geh zu meinem Boot, Baron.";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			sld = CharacterFromID("Noel");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			dialog.text = "Und denken Sie nicht einmal daran, uns zu verfolgen, Kapitän. Sie wissen, wer ich bin. Ich halte mehr Froschfresser gefangen, und wenn ich nicht rechtzeitig nach Hause komme, werden sie alle hingerichtet. Verstanden?";
			link.l1 = "Die Zeit wird kommen und wir werden uns mit euch verfluchten Gotteslästerern befassen!";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "Ha-ha-ha-ha! Sicher wirst du das!";
			link.l1 = "...";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Patria", "74");
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax"))
			{
				LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
				Island_SetReloadEnableGlobal("Bermudes", false); // закрыть остров до отвоза барона
			}
			else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_baronalive";
			pchar.questTemp.Patria.DodsonAgain = "true";
			sld = CharacterFromID("Noel");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Condotier_toPuancie.function = "Patria_CondotierEnCapstervil";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_22":
			dialog.text = "Machst du Witze?! Ist das irgendein Trick?!";
			link.l1 = "Einen Moment, ich bringe es...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "Patria_CondotierBaronDie", 1.0);
		break;
		
		case "patria_24":
			dialog.text = "";
			link.l1 = "Argh, Marcus, was hat dein Dummkopf getan!";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) link.l1.go = "patria_25";
			else link.l1.go = "patria_x25";
		break;
		
		case "patria_25":
			dialog.text = "Charles, was hast du getan? Wo ist das Geld? Ich habe meinen Jungs nicht gesagt, dass das nicht echt war... und so hat dieser Idiot entschieden, dass du uns reinlegen wolltest...";
			link.l1 = "Es ist eine Katastrophe! Der Baron ist tot... Was wird de Poincy jetzt tun?";
			link.l1.go = "patria_26";
		break;
		
		case "patria_x25":
			dialog.text = "Charles, was hast du getan? Wo ist das Geld? Ich habe meinen Jungs nicht gesagt, dass das nicht echt war... und so hat dieser Idiot entschieden, dass du sie hereinlegen wolltest...";
			link.l1 = "Es ist eine Katastrophe! Der Baron ist tot... Was wird de Poincy jetzt tun?";
			link.l1.go = "patria_x26";
		break;
		
		case "patria_x26":
			dialog.text = "Nun, Junge, das ist dein Fehler, ich hoffe, du verstehst das. Vielleicht ist es zum Besten, ein toter Mann kann keinen Schaden anrichten.";
			link.l1 = "Was für ein Idiot ich bin! Alles versaut. Gut, ich gehe zu Poincy... Verzeih mir, dass ich ein Narr bin, Marcus, wir sehen uns.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_26":
			dialog.text = "Nun, Junge, es ist deine Schuld, ich hoffe, du verstehst das. Vielleicht ist es zum Besten so.";
			link.l1 = "Wie ein Idiot bin ich! Alles vermasselt. Gut, ich gehe zu Poincy... Verzeih mir, dass ich ein Narr bin, Marcus, bis dann.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "Du musst dich ausruhen, du verlierst deinen Biss. Komm mal zu mir, ich besorge dir etwas Rum und feine Damen.";
			link.l1 = "Danke, ich werde dich besuchen, wenn ich kann.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			DialogExit();
			AddQuestRecord("Patria", "75");
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_barondie";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_29":
			dialog.text = "Du bist willkommen, Junge. Für mich war das der größte Spaß, den ich dieses Jahr hatte! Wir haben so viel gelacht, meine Jungs und ich! Also möchte ich dir dafür danken. Hier ist dein Geld.";
			link.l1 = "Du solltest einen Teil davon für deine Leistung behalten.";
			link.l1.go = "patria_30";
		break;
		
		case "patria_x29":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Nimm dein Geld, 'Verschwörer'. Ha-ha! Das war lustig.";
			link.l1 = "Danke für deine Hilfe, Marcus. Viel Glück!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_30":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Vergiss es. Ich habe das für unsere Freundschaft getan. Die Bruderschaft der Küste schuldet dir viel mehr, und doch hast du nicht einen einzigen Dublon verlangt.";
			link.l1 = "Nimm trotzdem mindestens fünfzigtausend für die Dienste und Entschädigung. Danke, Marcus!";
			link.l1.go = "patria_31";
		break;
		
		case "patria_31":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "Bitte schön. Charles, besuche mich, wann immer du etwas Zeit hast!";
			link.l1 = "Mit Vergnügen!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
		break;
		
		case "patria_33":
			dialog.text = "Du bist eine Woche zu spät! Ich habe meinen Jungs nicht gesagt, dass das nicht echt war... Sie wollten nicht länger warten und beschlossen, deinen Baron zu beenden!";
			link.l1 = "Was für ein Idiot ich doch bin! Alles versaut! Was soll ich Poincy erzählen?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_x33":
			dialog.text = "Du bist eine Woche zu spät! Ich habe meinen Jungs nicht gesagt, dass das nicht echt war... Sie wollten nicht länger warten und beschlossen, deinen Baron zu töten!";
			link.l1 = "Wie ein Idiot bin ich! Alles vermasselt! Was soll ich Poincy erzählen?";
			link.l1.go = "patria_x34";
		break;
		
		case "patria_34":
			dialog.text = "Nun, Junge, es ist deine Schuld, ich hoffe, du verstehst das. Vielleicht wird es für dich umso besser sein.";
			link.l1 = "Gut, ich werde nach Poincy gehen... Verzeih mir, dass ich ein Narr bin, Marcus, wir sehen uns..";
			link.l1.go = "patria_35";
		break;
		
		case "patria_x34":
			dialog.text = "Du hast dich selbst in dieses Durcheinander gebracht, es ist deine Schuld.";
			link.l1 = "Bis später, nehme ich an...";
			link.l1.go = "patria_36";
		break;
		
		case "patria_35":
			dialog.text = "Du musst dich ausruhen, du verlierst deine Fähigkeiten. Komm ab und zu zu mir, ich besorge dir etwas Rum und feine Mägde.";
			link.l1 = "Danke, ich werde dich besuchen, wenn ich kann.";
			link.l1.go = "patria_36";
		break;
		
		case "patria_36":
			DialogExit();
			AddQuestRecord("Patria", "75");
			pchar.questTemp.Patria = "epizode_12_barondie";
			DeleteAttribute(pchar, "questTemp.Patria.DodsonFail");
		break;
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ1":
			DelLandQuestMark(npchar);
			
			if (pchar.questTemp.Mtraxx == "full_complete")
			{
				dialog.text = "Ist eine Weile her, Prinz.";
				link.l1 = "Ich bin mir nicht sicher, ob dieser Name mir etwas anderes als Unglück gebracht hat, Marcus.";
				link.l1.go = "PZ_Prince1";
			}
			else
			{
				dialog.text = "De Maure! Was bringt dich hierher?";
				link.l1 = "Ahoi, Marcus. Ich wollte dich etwas fragen.";
				link.l1.go = "PZ_DeMaure1";
			}
		break;
		
		case "PZ_Prince1":
			dialog.text = "Ich sehe, es ist das Gegenteil. Was bringt dich hierher?";
			link.l1 = "Hast du von dem neuen Bordell in Tortuga gehört?";
			link.l1.go = "PZ2";
		break;
		
		case "PZ_DeMaure1":
			dialog.text = "Dann frag doch endlich. Du weißt, dass ich Formalitäten nicht mag, also komm zum Punkt.";
			link.l1 = "Hast du von dem neuen Bordell in Tortuga gehört?";
			link.l1.go = "PZ2";
		break;
		
		case "PZ2":
			dialog.text = "Bist du betrunken? Was für eine Frage ist das? Verschwende meine Zeit nicht, wenn das das ist, worüber du wirklich reden wolltest.";
			link.l1 = "Ich nehme an, du hast es nicht gehört? Dort hat kürzlich ein neues Bordell eröffnet - ein sehr teures, in dem nur die schönsten, gesündesten und am besten gekleideten Mädchen arbeiten.";
			link.l1.go = "PZ3";
		break;
		
		case "PZ3":
			dialog.text = "Oh, das! Natürlich habe ich gehört - wer hat das nicht?";
			link.l1 = "Nun, ich habe erst neulich davon erfahren.";
			link.l1.go = "PZ4";
		break;
		
		case "PZ4":
			dialog.text = "Ha-ha-ha-ha, du Schurke, verdammt nochmal! Aber warum diskutierst du das mit mir? Warum versuchst du es nicht zuerst bei Hawks? He he. Obwohl... hast du dort schon etwas Spaß gehabt?";
			if (CheckAttribute(pchar, "questTemp.PZ.EliteWhoreFucked"))
			{
				link.l1 = "Ich habe. Übrigens, sie akzeptieren nur Dublonen.";
				link.l1.go = "PZ_Fucked1";
			}
			else
			{
				link.l1 = "Ich habe den Ort besucht, aber ich habe die Dienste nicht in Anspruch genommen. Allerdings...";
				link.l1.go = "PZ_NoFucked1";
			}
		break;
		
		case "PZ_Fucked1":
			dialog.text = "Also bist du gekommen, um anzugeben! Ha, was für ein Schelm.";
			link.l1 = "Eigentlich nicht. Ich wollte dich wirklich etwas fragen, Marcus.";
			link.l1.go = "PZ5";
		break;
		
		case "PZ_NoFucked1":
			dialog.text = "Du hast nicht?! Du bist ein Idiot, De Maure. Wenn ich du wäre...";
			link.l1 = "Du hättest einen ordentlichen Exzess begonnen, das weiß ich. Aber genau das wollte ich nicht mit dir besprechen.";
			link.l1.go = "PZ5";
		break;
		
		case "PZ5":
			dialog.text = "Was ist los? Na los, halte mich nicht in Spannung.";
			link.l1 = "Ich suche die Besitzerin dieses Ortes. Mir wurde gesagt, sie wolle Sie treffen und eine Investitionsmöglichkeit in ihrem Handel anbieten. Sie können sie nicht verfehlen - sie ist Chinesin.";
			link.l1.go = "PZ6";
		break;
		
		case "PZ6":
			dialog.text = "Ho ho. Nein, ich hatte in letzter Zeit nicht das Vergnügen, chinesische Frauen zu treffen. Aber ich hätte nichts dagegen, sie zu treffen und in ihr Geschäft zu investieren. Schließlich kann man nicht einfach in Levasseurs Gebiet spazieren gehen, und als Untertan Ihres Königs würde er gezwungen sein, seine Küstenschiffe auf meinen 'Drachen' zu feuern, sobald er ihn sieht.";
			link.l1 = "Scheint, als würde sie zuerst Port-au-Prince in Betracht ziehen...";
			link.l1.go = "PZ7";
		break;
		
		case "PZ7":
			dialog.text = "Du denkst also? Das ist ein Fehler. Selbst wenn de Mussac mehr Geld hat als ich, was ich bezweifle, kann er sich nicht leisten, einen Teil des Stadtbudgets für ein Bordell zu verwenden, egal wie viel Gold es einbringt.";
			link.l1 = "Guter Punkt. Sie hat offensichtlich nicht über diesen Ehrgeiz von ihr nachgedacht.";
			link.l1.go = "PZ8";
		break;
		
		case "PZ8":
			dialog.text = "Sie wissen, ich habe mich immer gefragt, wie andere Bordelle über Wasser bleiben. Es ist nicht die Fähigkeit einer Frau zu denken und vor allem zu herrschen - merken Sie sich meine Worte.";
			link.l1 = "Nun, da liegst du falsch. Danke für deine Zeit, Marcus! Wenn ich sie zuerst treffe, werde ich ihr sagen, dass du dich freuen würdest, sie zu sehen.";
			link.l1.go = "Exit";
			
			AddQuestRecord("PZ", "32");
			
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1 = "location";
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1.location = "Hispaniola1";
			pchar.quest.PZ_SetHeavyFrigate.win_condition = "PZ_SetHeavyFrigate";
			DelMapQuestMarkCity("LaVega");
			AddMapQuestMarkCity("PortPax", false);
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", true);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", true);
		break;
	}
}