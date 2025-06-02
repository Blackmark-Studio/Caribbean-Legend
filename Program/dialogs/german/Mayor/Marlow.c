// Захария Марлоу, Чёрный Пастор, Пуэрто-Принсипе, Куба
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

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
    } //<-- блок angry

	switch(Dialog.CurrentNode)
	{
		case "First time":
            dialog.text = NPCStringReactionRepeat("Hast du irgendwelche Geschäfte mit mir? Wenn nicht, dann verschwinde von hier!","Ich denke, ich habe mich klar ausgedrückt.","Obwohl ich mich klar ausgedrückt habe, belästigst du mich weiterhin!","Genau, ich habe genug von dieser Unhöflichkeit.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ich gehe schon.","Natürlich, Pastor.","Es tut mir leid, Pastor.","Ups...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Bist du wahnsinnig? Wolltest du Metzger spielen? Alle Piraten sind wütend auf dich, Junge, du solltest besser diesen Ort verlassen.","Es scheint, dass du verrückt geworden bist, Junge. Wolltest du deine Hände ein bisschen strecken? Nichts für ungut, aber du hast hier nichts zu suchen. Verzieh dich!");
				link.l1 = RandPhraseSimple("Hör zu, ich möchte die Situation klären...","Hilf mir, dieses Problem zu lösen...");
				link.l1.go = "pirate_town";
				break;
			}
			
			//--> Сага
			if(CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && !CheckAttribute(npchar, "quest.sharkbegin"))
			{
				link.l1 = "Ich versuche, Shark Dodson zu finden. Man sagt, du seist der letzte Mann, der ihn gesehen hat. Kannst du mir dabei helfen?";
				link.l1.go = "Shark";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax" && CheckCharacterItem(pchar, "witches_hammer"))
			{
				link.l1 = "Warum bist du so unhöflich? Oder bist du nicht daran interessiert, dein gewünschtes Buch von mir zu bekommen?";
				link.l1.go = "book";
			}
			//<-- Сага
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "Ich möchte über Ihren Gefangenen sprechen.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") // лесник. новая проверка. искл. возможность сразу сдать задание,минуя 15 дней.
				{
					link.l1 = "Hallo, Pastor. Ich möchte über Ihre Mission sprechen.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak") && !CheckAttribute(pchar,"GenQuest.CaptainComission.vikupzaplatil")) 
				{ // лесник . второй диалог с проверкой ,если ГГ ещё не принес деньги за выкуп.
					link.l1 = "Ich möchte über Ihren Gefangenen sprechen.";
					link.l1.go = "CapComission6";
				}
			}
		break;
		
		case "shark":
			dialog.text = "Steven Dodson? Ich weiß nicht, wie meine Geschichte dir helfen könnte, denn Shark ist seit einigen Monaten verschwunden und niemand hat ihn gesehen. Es ist jedoch keine Überraschung, er hat Blaze Sharp getötet und seinen eigenen Namen durch diese törichte Aktion in Verruf gebracht. Er hat einige mächtige Korsaren zu seinen Feinden gemacht.";
			link.l1 = "Ich habe allen Grund zu glauben, dass Shark unschuldig am Tod von Sharp ist. Ich kann es nicht beweisen, vielleicht kann Shark es selbst tun. Wirst du mir etwas über ihn erzählen?";
			link.l1.go = "shark_1";
		break;
		
		case "shark_1":
			dialog.text = "Vor ein paar Monaten kam Steven zu mir und bot einen sehr seltsamen Handel an: Er hinterließ seine Fregatte 'Fortune' für einen Monat als Pfand im Austausch für eine Brigg, die voll beladen mit Proviant war. Dann gibt er mir entweder die Brigg und das Geld für den Proviant zurück, oder ich behalte seine Fregatte. Ein Monat verging - kein Zeichen von Shark, meiner Brigg oder Geld.\nAußerdem hörte ich Gerüchte, dass Blaze ermordet wurde und Shark der Verdächtige war. Was sollte ich denken? Richtig! Ich dachte, dass Steven dem Schlimmsten entkommen war. Ich verkaufte seine Fregatte an einen Engländer namens William Patterson, er war sehr erfreut und zahlte einen großen Haufen Dublonen für das Schiff.\nDaher habe ich meine Ausgaben vollständig kompensiert und hege keinen Groll gegen ihn. Mir ist Sharps Tod egal, ich habe meine eigenen Probleme, um die ich mich sorgen muss.";
			link.l1 = "Glaubst du nicht, dass er, wenn er hätte fliehen wollen, deine Brigg nicht gebraucht hätte? Er hatte sein eigenes Schiff, hundertmal besser als jede Brigg. Es sieht so aus, als hätte Shark einen Plan gehabt, aber etwas ging schief und er kam nicht rechtzeitig zurück.";
			link.l1.go = "shark_2";
		break;
		
		case "shark_2":
			dialog.text = "Wie ich dir bereits gesagt habe, interessieren mich Dodsons Probleme nicht. Ich habe meinen Teil des Handels erfüllt. Bezüglich des Schiffes, frag ihn besser, warum er die verdammte Brigg brauchte. Ich habe ihn nicht gezwungen, sie zu nehmen.";
			link.l1 = "Gut, reden wir nicht mehr darüber. Natürlich hast du recht. Sag mal, weißt du, wohin Steven auf deiner Brigg unterwegs war?";
			link.l1.go = "shark_3";
		break;
		
		case "shark_3":
			dialog.text = "Wer weiß das schon genau. Aber ich habe einige Vermutungen. Er segelte Nordwesten Richtung Main. Also entweder die Bucht des Verderbens, die für ihre feindseligen Indianer bekannt ist, oder Neuspanien, das für seine Papisten und die Inquisition bekannt ist.\nIch bezweifle, dass er an einen dieser Orte segeln würde. Aber man sagt, es gibt einen seltsamen Ort namens 'Stadt der verlassenen Schiffe', der nordwestlich von Kuba liegt. Viele Leute halten das für einen Mythos, aber ich nicht. Nicht weil ich so ein romantischer Mensch bin, sondern weil es echte Menschen gibt, die dorthin auf ihren Langbooten segeln. Zumindest haben sie das früher getan.";
			link.l1 = "Und wer sind sie?";
			link.l1.go = "shark_4";
		break;
		
		case "shark_4":
			dialog.text = "Freibeuter aus Kuba. Sie hatten ihre Barken mit Stierkadavern beladen und segelten nordwestlich. Sie kehrten immer etwas später zurück, die Taschen voller Geld oder seltener und wertvoller Waren.";
			link.l1 = "Faszinierend! Wo kann ich diese Freibeuter finden?";
			link.l1.go = "shark_5";
		break;
		
		case "shark_5":
			dialog.text = "Warum fragst du mich? Durchsuche die Wälder Kubas. Selbst wenn du sie findest, werden sie dir nichts erzählen, warum sollten sie die Quelle ihres guten Lebens preisgeben? Verschwende also nicht deine Zeit, seit langer Zeit hat niemand gesehen, dass sie es wieder tun.\nAußerdem hörte ich von einigen Notizen, die der spanische Seemann Alvarado geschrieben hat, der die Insel selbst besucht hat. Also bin ich neugierig, vielleicht ist Steven doch dorthin gesegelt.";
			link.l1 = "Die unbekannte Insel, die nicht auf Karten ist... Nun. Das ist keine vielversprechende Information.";
			link.l1.go = "shark_6";
		break;
		
		case "shark_6":
			dialog.text = "Ich habe dir von Anfang an gesagt, dass meine Geschichte dir nicht helfen würde. Und warum brauchst du Dodson?";
			link.l1 = "Ich und der Waldteufel wollen ihn zum Anführer der Bruderschaft der Küste wählen. Wie ich dir bereits gesagt habe, gibt es einige ernsthafte Gründe zu der Annahme, dass Blaze von jemand anderem ermordet wurde.";
			link.l1.go = "shark_7";
		break;
		
		case "shark_7":
			dialog.text = "Heh! Ich nehme an, dass Jan für ihn eintritt? Nun, du kennst das Gesetz - Dodson muss eine Stimme von jedem Baron bekommen.";
			link.l1 = "Ich kenne das Gesetz. Meine zweite Frage dann. Wirst du bei der Wahl für Dodson stimmen?";
			link.l1.go = "shark_8";
		break;
		
		case "shark_8":
			dialog.text = "Nun, er sollte zuerst zurückkehren. Eigentlich ist es mir egal, wer die Bruderschaft führt, solange er seine Arbeit gut macht und mich nicht stört. Wie gesagt, ich habe meine eigenen Probleme. Weißt du, wie viele Hexen und Magier auf unserer Insel sind? Nein? Ich werde es dir sagen: eine Legion! Außerdem gibt es viele Papisten in Santiago und Havanna.\nApropos Magier. Es gibt ein Buch namens 'Hammer für die Hexen'. Ich möchte es wirklich haben, aber nur auf Englisch, ich brauche keine lateinischen, deutschen oder spanischen Übersetzungen, ich kenne diese Sprachen nicht. Bring mir das Buch und ich werde für Dodson stimmen.\nSei dir bewusst, dass Jackman mir versprochen hat, es auch zu finden, also wenn er zuerst Erfolg hat... dann gib mir nicht die Schuld.";
			link.l1 = "Gut, ich werde das berücksichtigen. Danke für deine Zeit. Bis dann.";
			link.l1.go = "shark_9";
		break;
		
		case "shark_9":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "after_marlow";
			npchar.quest.sharkbegin = "true";
			AddQuestRecord("SharkHunt", "2");
		break;
		
		case "book":
			dialog.text = "Das Buch? Ich nehme an, du redest von dem 'Hammer für die Hexen'?";
			link.l1 = "Natürlich. Ich konnte es für dich finden. Es ist auf Englisch, wie du gefragt hast.";
			link.l1.go = "book_1";
		break;
		
		case "book_1":
			dialog.text = "Ha, entschuldige für so einen rauen Empfang, Kumpel. Wird nicht wieder vorkommen... Lass mich mal dieses Wunder sehen!";
			link.l1 = "Sicher, schau mal.";
			link.l1.go = "book_2";
		break;
		
		case "book_2":
			RemoveItems(pchar, "witches_hammer", 1); // удалить трактат
			dialog.text = "Endlich! Zittert jetzt, Diener der Hölle! Ich werde euch nicht in Ruhe lassen, bis meine Hand nicht mehr zuschlagen kann...";
			link.l1 = "Ich freue mich für Sie, Pastor. Also, wie steht es um Ihre Stimme?";
			link.l1.go = "book_3";
		break;
		
		case "book_3":
			dialog.text = "Wie ich dir schon sagte 'Es ist mir egal, wer der Boss wird'. Ich bin sicher, dass Svenson keinen unwürdigen Mann wählen wird. Also nimm meine Stimme. Mach damit, was du willst. Hier ist mein Splitter.";
			link.l1 = "Danke dir, Zechariah. Wir sehen uns dort!";
			link.l1.go = "book_4";
		break;
		
		case "book_4":
			GiveItem2Character(pchar, "splinter_zm"); // дать осколок
			DialogExit();
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "27");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+", Ich bin froh, dich zu sehen! Was willst du?","Was willst du noch?","Wieder? Belästige die Leute nicht, wenn du nichts zu tun hast!","Du bist ein "+GetSexPhrase("guter Freibeuter","braves Mädchen")+", also kannst du vorerst leben. Aber ich will nicht mehr mit dir reden.","repeat",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ich zahle nur einen Besuch.","Nichts...","Gut, Pastor, es tut mir leid...","Verdammt, mein Fehler!",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Bist du verrückt? Wolltest du den Metzger spielen? Alle Piraten sind wütend auf dich, Junge, also solltest du besser diesen Ort verlassen...","Es scheint, dass du verrückt geworden bist, Junge. Wolltest du deine Hände ein bisschen strecken? Nichts für ungut, aber du hast hier nichts zu suchen. Verschwinde!");
				link.l1 = RandPhraseSimple("Hör zu, ich möchte die Situation klären...","Hilf mir, dieses Problem zu lösen...");
				link.l1.go = "pirate_town";
				break;
			}
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "Es geht um deinen Gefangenen.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}		
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "Es geht um deinen Gefangenen.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}	
			if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway")//  правка лесник,новая проверка ,исключающая тут же сдачу задания
			{
				link.l1 = "Hallo, Pastor, ich bin wegen Ihrer Mission hier.";
				link.l1.go = "CapComission3";
			}
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin" && CheckAttribute(pchar, "questTemp.LongHappy"))
			{ // лесник . похититель  ( после ДЛС ДиС ,когда барбазона уже нет)
				link.l1 = "Ich habe gehört, dass du dich mit Geschäften im Zusammenhang mit Gefangenen beschäftigst...";
				link.l1.go = "Marginpassenger";
			}
		break;
		
	//-----------------------------------Поручение капитана - Выкуп-------------------------------------------------
		case "CapComission1":
			dialog.text = "Ha-ha. Glaubst du, ich habe hier nur einen Gefangenen? Nenne ihn.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+". Ist er hier?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "Er war es. Ich habe ihn an diesen Plantagenbesitzer aus Barbados verkauft - Oberst Bishop, als er vor einer Woche hier war.";
				link.l1 = "Verdammt...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "Ach, endlich. Ich dachte schon, ihn an diesen Plantagenbesitzer aus Barbados zu verkaufen, er wird in einer Woche oder zwei hier sein... Hast du ein Lösegeld?";
				link.l1 = "Schau, es gibt ein kleines Problem ... Tatsächlich habe ich nicht so viel Geld. Aber ich bin bereit zu arbeiten.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "Es ist gut, dass du ihn nicht verkauft hast. Hier sind deine Münzen - 150.000 Pesos. Wo kann ich ihn bekommen?"link.l2.go ="CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "Du warst zu langsam... Und warum kümmert er dich? Ich habe nur mit seinen Verwandten verhandelt.";
			link.l1 = "Sie haben mich gebeten, hierher zu kommen.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "Nun, du bist spät dran. Ich kann nichts tun.";
			link.l1 = "Hör zu, für wie viel hast du ihn verkauft, wenn es kein Geheimnis ist?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Eh, das ist es nicht. Aber ich werde es dir nicht sagen ... du wirst lachen, wenn ich es tue. Ha-ha-ha-ha! Lebewohl.";
			link.l1 = "Bis dann.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");//правка лесник.  в СЖ запись ниже не работает																																				  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));																															 
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(3) == 1)
			{
				dialog.text = "Nun, "+pchar.name+", weißt du, so funktioniert das nicht. Komm zurück mit Geld und du bekommst deinen Schwächling, ha-ha.";
				link.l1 = "Gut. Bis dann.";
				link.l1.go = "CapComission2_4";
			}
			else
			{
				dialog.text = "Nun, nun.. Ich habe eine Angelegenheit... Weiß gar nicht, wo ich anfangen soll. Ich muss einen Piraten versenken, der die Linie überschritten hat.";
				link.l1 = "Kann er nicht einfach im Dschungel getötet werden?";
				link.l1.go = "CapComission2_2_1";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "Das ist nicht, wie Geschäfte laufen, weißt du... Ich brauche seinen Tod nicht, ich muss einigen Leuten beibringen, meinen Anteil an der Beute nicht zu nehmen. Aber ich werde seinen Tod nicht bedauern.";
			link.l1 = "Warum schickst du nicht deine eigenen Leute, um ihn zu holen?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Dat"); // belamour gen
			dialog.text = "Hm... Nun, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+" hat einige Piraten davon überzeugt, dass ihr Anteil an der Beute in unserem Versteck unweit von "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gen")+". Ihre beiden Schiffe '"+pchar.GenQuest.CaptainComission.ShipName1+"' und '"+pchar.GenQuest.CaptainComission.ShipName2+"' hat vor nicht langer Zeit die Anker gelichtet und ist gesegelt zu "+sLoc+". Jetzt siehst du, warum ich meinen Männern diese Arbeit nicht anvertrauen kann?";
			link.l1 = "Ich mache es. Wieviel Zeit habe ich?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12 bis 15 Tage, nicht mehr, es ist mir wichtig, dass sie nicht zum Versteck kommen, sonst wäre es Unsinn, sie mit wertvoller Fracht zu versenken. In diesem Fall wäre es besser, wenn sie es hierher brächten...";
			link.l1 = "Gut, ich bin dabei. Ich werde versuchen, sie zu fangen.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");//правка																			   
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			//pchar.GenQuest.CaptainComission.PirateShips = "sdatkwest";	// лесник - заменил проверку для сдачи сразу.
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "Mach dir keine Sorgen. Meine Männer werden ihn zu deinem Schiff bringen. Und warum kümmert er dich?";
			link.l1 = "Ich nicht. Seine Verwandten haben mich gebeten, ihn zu liefern.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Ach, das ist gut. Ich habe fast bedauert, so einen niedrigen Preis für deinen Mann gegeben zu haben. Ha-ha-ha-ha. Lebewohl.";
			link.l1 = "Bis dann.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));	// belamour gen	
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.vikupzaplatil = true; // новая проверка ,если шарль заплатил выкуп за пленника. лесник																																																			
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");		// лесник																											 
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в СЖ не работает
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "Also, , "+GetFullName(pchar)+", hast du meine Kumpels versenkt? He-he-he...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "Nein. Ich habe es nicht geschafft, sie zu fangen. Und ich habe sie bei der Rückkehr nicht getroffen.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "Ich habe es getan. Ich habe sie den Haien zum Fraß vorgeworfen.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "Verdammt! Ob du sie getroffen hast oder nicht, spielt jetzt keine Rolle mehr! Und was wird dein nächster Vorschlag sein?";
			link.l1 = "Vielleicht hast du eine einfachere Aufgabe für mich?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Hör zu, "+NPChar.name+", senke den Preis für den Gefangenen...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "Nein.";
			link.l1 = "Dann leb wohl...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "Den Preis senken?! Ich habe gerade meine Beute wegen deiner Inkompetenz verloren! Und jetzt kann ich den Preis erhöhen! Du kannst ihn für 200.000 Pesos haben, wenn du willst, oder du kannst zum Teufel hier raus.";
			link.l1 = "Es ist zu teuer... Auf Wiedersehen...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "Verdammt, nimm deine Münzen.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Marlow");		// лесник																								   
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Marlow"); // правка	// лесник																											 
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Du kannst diesen Schwächling nehmen...";
			link.l1 = "Auf Wiedersehen.";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Marlow"); // правки имени в сж лесник																										  
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в сж не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "Ho-ho! Gut gemacht! Nimm deinen Schwächling und viel Glück.";
			link.l1 = "Danke. Lebewohl.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
			/*case "CapComission6":    // ЕСЛИ В ПЕРВЫЙ РАЗ ОТКАЗАЛ В ЗАДАНИИ ,ТО ПУСТЬ БАБКИ ИЩЕТ
		     ИНАЧЕ ПОВТОРНАЯ ДАЧА ЗАДАНИЯ ПРЕВРАЩАЕТ КВЕСТ В КАШУ.. лесник
			dialog.text = "Du hast das Lösegeld gebracht"+GetSexPhrase("","ла")+"? Ich habe nicht gescherzt, als ich sagte, dass ich ihn an die Pflanzer verkaufen würde.";			
			link.l1 = "Hör zu, "+NPChar.name+", hier ist die Sache... Im Grunde habe ich nicht so viel Geld. Aber ich bin bereit"+GetSexPhrase("","а")+" abarbeiten.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Es ist gut, dass du ihn nicht verkauft hast. Hier sind deine Münzen - 150000 Pesos. Wo kann ich ihn holen?"link.l2.go ="HauptmannKommission2_3";
			}			
		break;*/
		  case "CapComission6":                        // лесник . пусть шарль бабло ищет,или забить на пленника.
			dialog.text = "Hast du das Geld mitgebracht? Ich habe nicht gescherzt, dass ich den Mann zur Plantage verkaufe.";			
			link.l1 = "Ich habe das Geld nicht, "+NPChar.name+", aber ich arbeite daran.";
			link.l1.go = "exit";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Es ist gut, dass du ihn nicht verkauft hast. Hier sind deine Münzen - 150.000 Pesos. Wo kann ich ihn bekommen?"link.l2.go ="CapComission2_3";
			}			
		break;

																																				 																																													  																																															
//--------------------------------------------Похититель------------------------------------------------------
		case "Marginpassenger":
			dialog.text = "Und warum kümmert es dich, was ich mache? Weißt du, du solltest besser gehen...";
			link.l1 = "Tshh, beruhige dich. Ich habe ein Geschäft mit dir. Es geht um deinen Gefangenen.";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Ach, gut. Wen möchtest du auslösen?";
			link.l1 = "Warte. Ich bin nicht hier, um auszukaufen, ich bin hier, um dir anzubieten, einen Gefangenen zu kaufen. Nun, und du wirst die Gelegenheit haben, Lösegeld für ihn zu bekommen.";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "Hm. Und warum brauchst du meine Agentur? Warum willst du nicht direkt Geld für dich selbst bekommen?";
			link.l1 = "Es ist ziemlich riskant für mich. Ich könnte Probleme mit den Behörden bekommen.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Ha-h... na gut. Lass uns mal sehen. Wer ist dein Gefangener?";
			link.l1 = "Das ist "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Ich sehe... es wäre ein guter Handel, wenn du nicht lügst. Ich vermute, ich könnte dich für diesen Mann bezahlen "+iTemp+" Pesos oder gib stattdessen einige interessante Informationen. Es ist deine Wahl.";
			link.l1 = "Ich nehme besser Pesos. Ich habe genug von diesem Geschäft...";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "Ha! Erzähl mir mehr. Ich bin sicher, dass du mir etwas Interessantes mitbringen wirst.";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "Geld also. Nimm sie. Jetzt ist es nicht mehr dein Problem. Bringe das Verkaufsobjekt hierher.";
			link.l1 = "Er muss schon in der Nähe des Stadttors sein. Danke! Du hast mir wirklich geholfen.";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Du bist willkommen, bring mir mehr... Bis dann!";
			link.l1 = "Viel Glück...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GOOD_EBONY + rand(makeint(GOOD_MAHOGANY - GOOD_EBONY));
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (hrand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "Es ist gut, Geschäfte mit einem klugen Mann zu machen. Jetzt höre zu: in einigen Tagen zu "+XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat")+" eine spanische Expedition wird aus Main eintreffen, beladen mit wertvollen Gütern. Sie werden auf ein Schiff warten, das die Ladung aufnehmen soll. Wenn du in einer Woche dort bist, hast du die Chance, die Ladung für dich zu nehmen.\nWenn ich du wäre, würde ich mich schon zu meinem Schiff bewegen. Und bring den Gefangenen hierher.";
					link.l1 = "Danke! Die Ware wird eine schöne Entschädigung für meine Mühen sein. Und mein Passagier muss bereits in der Nähe des Stadttors sein. Er wird zu dir gebracht.";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "Es ist gut, Geschäfte mit einem klugen Mann zu machen. Jetzt hör zu: in etwa einer Woche kommt eine spanische Brigantine '"+pchar.GenQuest.Marginpassenger.ShipName1+"' beladen mit wertvollen Gütern wird segeln von "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen")+" zu "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen")+". Wenn du dich beeilst, wirst du es leicht einholen.\nDu bist immer noch hier? Wenn ich du wäre, wäre ich schon auf dem Weg zu meinem Schiff. Und bring den Gefangenen hierher.";
					link.l1 = "Danke! Die Waren werden eine schöne Entschädigung für meine Mühen sein. Und mein Passagier muss bereits in der Nähe der Stadttore sein. Er wird zu dir gebracht.";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));//лесник - окончание в СЖ // belamour gen: Abl - это к Залив"ом", нужен дательный
			AddQuestUserData("Marginpassenger", "sName", "Zachary Marlow")); // belamour gen : как-то странно, наводку даёт Захар, а в сж Добряк дефолтом
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sName", "Zachary Marlow")); // belamour gen 
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Acc")); // лесник - окончание в СЖ
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
		
		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Raub!!! Das ist inakzeptabel! Mach dich bereit, "+GetSexPhrase("Junge","Mädchen")+"...","He, was zum Teufel machst du da?! Dachtest du könntest mich ausrauben? Du bist erledigt...","Warte, was zum Teufel? Nimm deine Hände weg! Es stellt sich heraus, dass du ein Dieb bist! Ende der Linie, Bastard...");
			link.l1 = LinkRandPhrase("Scheiße!","Verdammte Axt!!","Verdammt noch mal!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("Verschwinde ","Verschwinde")+" von hier!","Verlass mein Zuhause!");
			link.l1 = "Oh, verdammt...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Belästige mich nicht mit deinem billigen Gerede. Das nächste Mal wird dir das Ergebnis nicht gefallen...";
        			link.l1 = "Ich habe es.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("Es ist vorbei, kein Gerede.","Ich will nicht mehr mit dir reden, also wäre es besser, wenn du mich nicht belästigst.");
			link.l1 = RandPhraseSimple("Wie du wünschst...","Hm, gut dann...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Ich hoffe, dass du mehr Respekt zeigen und aufhören wirst, unhöflich zu sein?";
        			link.l1 = "Sie können sicher sein, Pastor, ich werde.";
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
            DoReloadCharacterToLocation("Puertoprincipe_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		case "pirate_town":
            dialog.text = "Das Problem lösen? Hast du eine Ahnung, was du getan hast? Wie auch immer, bring mir eine Million Pesos und ich werde die Jungs dazu überreden, deine Tat zu vergessen. Wenn dir die Idee nicht gefällt, dann kannst du zur Hölle fahren.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Gut, ich bin bereit zu zahlen.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Verstanden. Ich gehe jetzt.";
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
            dialog.text = "Gut! Betrachte dich selbst wieder als sauber. Aber ich hoffe, dass du solche widerlichen Dinge nicht noch einmal tun wirst.";
			link.l1 = "Ich werde nicht. Viel zu teuer für mich. Auf Wiedersehen...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}
