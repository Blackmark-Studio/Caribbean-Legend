// Ришард Шамбон - контрабандист
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && int(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Ich will nicht mit dir reden. Du greifst friedliche Zivilisten ohne Grund an und provozierst sie zum Kampf. Verschwinde!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			// --> кольцо
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_2") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.ring"))
			{
				dialog.text = "Oh! Da bist du ja, Kumpel. Und ich dachte schon, ich müsste dich selbst suchen. Ich brauche dich, Freund.";
				link.l1 = "Du bist heute verdächtig freundlich, Richard. Nun, ich höre zu.";
				link.l1.go = "ring";
				break;
			}
			// <-- кольцо
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Was willst du? Um ehrlich zu sein, bin ich heute nicht in guter Stimmung. Tatsächlich habe ich vergessen, wann ich das letzte Mal in guter Stimmung war.";
				link.l1 = "Ist es wirklich so schlimm, Kumpel?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Willst du etwas?";
				link.l1 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Gibt es Neuigkeiten auf der Insel?","Wirst du mir die neuesten Klatschgeschichten erzählen?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Ich möchte Ihnen ein paar Fragen zur Insel stellen.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Wollte nur wissen, wie es dir geht. Bis dann!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Schlecht? Nein, es ist nicht schlecht. Ich bin einfach nicht in der richtigen Stimmung. Also, was wolltest du?";
			link.l1 = "Nur um dich kennen zu lernen. Ich bin neu hier, also spaziere ich nur um die Insel herum und lerne Leute kennen.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Wirklich? Na gut. Ich bin Richard Shambon. Vor langer Zeit habe ich einige wertvolle Güter gehandelt, einige davon waren illegal, aber ich habe die letzten neun Jahre Schiffswracks durchsucht, nach Schrott gesucht und ihn gegen Lebensmittel und Gold eingetauscht.";
			link.l1 = "Und ich bin "+GetFullName(pchar)+", ein Kapitän...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Du meinst den Ex-Kapitän, ha-ha?";
			link.l1 = "Nun, eigentlich ist mein Schiff jetzt in Blueweld. Und ich bin hier auf einer Tartane gesegelt.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Wirklich? Unmöglich! Und wo ist jetzt Ihre Tartane?";
			link.l1 = "Hm... am Grund.";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "A-ah... Und ich dachte... Was auch immer, Kumpel, ich sollte besser etwas Rum trinken...";
			link.l1 = "Viel Glück dabei. Es war schön, mit dir zu sprechen. Bis dann!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Gibt es etwas Neues auf der Insel?","Wirst du mir die letzten Klatsch und Tratsch erzählen?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Ich möchte Ihnen ein paar Fragen über die Insel stellen.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		// Кольцо
		case "ring":
			dialog.text = "Und war ich vorher anders? Komm schon, ich hatte schlechte Tage, jeder hat sie manchmal! Sag mal, es gibt Gerüchte auf der Insel, dass du ein exzellenter Kämpfer bist. Ist das wahr?";
			link.l1 = "Ich weiß nicht, was sie sagen, aber ich weiß, wie man ein Schwert führt, wenn das deine Frage ist.";
			link.l1.go = "ring_1";
			npchar.quest.ring = "true";
		break;
		
		case "ring_1":
			dialog.text = "Verstanden. Ich sehe, dass diese Gerüchte wahr waren... Hör zu, "+pchar.name+", erinnerst du dich, dass ich dir von dem äußeren Ring erzählt habe? Und von den wertvollen Sachen, die du dort finden kannst?";
			link.l1 = "Ihr redet alle gerne über diesen Ring... Und ihr sagt alle das Gleiche.";
			link.l1.go = "ring_2";
		break;
		
		case "ring_2":
			dialog.text = "Was kann man sonst noch sagen, ha-ha! Gut. Ich komme zur Sache. (senkt seine Stimme) Ich habe ein unberührtes Schiff am äußeren Ring gefunden, sie ist in gutem Zustand, was ziemlich selten ist\nDas Schiff ist groß, eine Pinasse. Sie wurde hier vor nicht allzu langer Zeit angetrieben, etwa zwei Monate oder sogar weniger. Andere haben sie noch nicht gefunden, daher besteht die Chance, durch das Plündern ihrer Laderäume und Kabinen gutes Geld zu machen.";
			link.l1 = "Schön, ich freue mich für dich. Aber was geht das mich an? Willst du mich fragen, ob ich mit dir dorthin gehen soll?";
			link.l1.go = "ring_3";
		break;
		
		case "ring_3":
			dialog.text = "Genau! Hör zu. Der Bug des Beiboots ist beschädigt. Diese verfluchten Krabben haben ein Loch genutzt, um hineinzukommen, und sie haben ein verdammtes Nest darin gebaut. Hineinzuschleichen, während sie dort sind, ist keine Option und ich habe keine Ahnung, wie man auf das Oberdeck klettert\nIch war nie ein guter Kämpfer und habe seit Jahren kein Schwert mehr berührt, also werde ich die Kreaturen nicht alleine töten können. Deshalb bin ich zu dir gekommen.";
			link.l1 = "Also schlägst du mir vor, alle Krabben in diesem Schiff zu töten, richtig?";
			link.l1.go = "ring_4";
		break;
		
		case "ring_4":
			dialog.text = "Ja. Wir werden ein Geschäft machen. Ich werde den Weg zum Schiff zeigen und du wirst die Krabben beseitigen. Wir teilen alle Beute, die wir dort finden. Es ist ein fairer Handel - ich habe das Schiff gefunden und du wirst es räumen.";
			link.l1 = "Nein, Kumpel, ich bin nicht interessiert. Es ist nicht mein Stil, in einem halb versunkenen Schiff gegen Krabben zu kämpfen für einige zweifelhafte Trophäen. Such dir einen anderen risikofreudigen Kerl, der für dich die Kastanien aus dem Feuer holt.";
			link.l1.go = "ring_exit";
			link.l2 = "Interessant... Ich habe schon lange darüber nachgedacht, den äußeren Ring zu überprüfen. Abgemacht! Ich werde die Krabben töten.";
			link.l2.go = "ring_5";
		break;
		
		case "ring_exit":
			dialog.text = "Schade... Du hast einen Fehler gemacht. Es gibt viele saftige Dinge in den Schiffen des äußeren Rings... Und niemand war zuvor auf diesem Schiff. Nun, es ist dein Wunsch. Leb wohl...";
			link.l1 = "Tschüss, Kumpel...";
			link.l1.go = "exit";
		break;
		
		case "ring_5":
			dialog.text = "Ich bin froh, dass ich recht mit dir hatte, Freund. Ich habe das Gefühl, dass wir eine Menge interessanter Dinge in ihr finden werden...";
			link.l1 = "Wir werden sehen. Weißt du, wie viele Krabben es gibt?";
			link.l1.go = "ring_6";
		break;
		
		case "ring_6":
			dialog.text = "Ich denke, etwa vier oder fünf von ihnen... Nun, im Durchschnitt.";
			link.l1 = "Mir passt das. Wann gehen wir?";
			link.l1.go = "ring_7";
		break;
		
		case "ring_7":
			dialog.text = "Lass uns morgen dorthin gehen, wir müssen uns vorbereiten. Besorge einige Gegenmittel von Bruder Julian, Krabbenkiefere sind giftig. Vorsicht ist angebracht. Treffen wir uns morgen um acht Uhr morgens auf dem 'schiefen Deck'. Weißt du, wo das ist?";
			link.l1 = "Ich tue es nicht. Erkläre.";
			link.l1.go = "ring_8";
		break;
		
		case "ring_8":
			dialog.text = "Hinter dem 'San Augustine' liegt ein Wrack eines alten Schiffes. Ihr Bug ist unter Wasser und ihr Heck ist hochgehoben. Deshalb wird sie das 'schräge Deck' genannt. Man kann dorthin nur schwimmen. Beginnen Sie einfach mit dem Schwimmen von der Stelle unter der Brücke und drehen Sie sich von jeder Seite des 'San Augustine' um. Von dort aus schwimmen wir zusammen.";
			link.l1 = "Gut. Bis morgen!";
			link.l1.go = "ring_9";
		break;
		
		case "ring_repeat":
			dialog.text = "8 Uhr, 'schiefe Deck'...";
			link.l1 = "Ja, ja, ich erinnere mich daran...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_repeat";
		break;
		
		case "ring_9":
			DialogExit();
			NextDiag.CurrentNode = "ring_repeat";
			pchar.quest.LSC_Ring_Start.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.hour  = 7.0;
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Start.function = "LSC_RingStart"; // готовы
			pchar.quest.LSC_Ring_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.hour  = 10.0;
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Over.function = "LSC_RingOver"; // опоздание
			AddQuestRecord("LSC_Ring", "1");
		break;
		
		case "ring_10":
			dialog.text = "Aha, da bist du ja, Kumpel. Bist du bereit, einen Krabbensalat zu machen?";
			link.l1 = "Sicher!";
			link.l1.go = "ring_11";
		break;
		
		case "ring_11":
			dialog.text = "Sehr gut. Jetzt dreh deinen Kopf zum äußeren Ring und schau. Siehst du dort zwei Schiffswracks aus dem Wasser ragen?";
			link.l1 = "Hm... Ja, das tue ich.";
			link.l1.go = "ring_12";
		break;
		
		case "ring_12":
			dialog.text = "Schau jetzt zwischen ihnen auf den äußeren Ring. Siehst du die Galeone mit dem hochgezogenen Bug? Sie zeigt genau auf uns. Schau genau hin.";
			link.l1 = "...";
			link.l1.go = "ring_look";
		break;
		
		case "ring_look":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_ring");
			DoQuestCheckDelay("LSC_RingTalkLook", 6.0);
		break;
		
		case "ring_13":
			dialog.text = "";
			link.l1 = "Ich glaube, ich sehe es... Ja!";
			link.l1.go = "ring_13a";
		break;
		
		case "ring_13a":
			dialog.text = "Das ist unser Ziel. Schwimme geradeaus und drehe dich nicht um. Ich werde dir den Weg zurück zeigen, wenn wir den äußeren Ring erreichen. Der Eingang zum Laderaum ist das Loch im Bug des Schiffes. Wisse, dass ich nicht dorthin gehen werde, bis du alle Krabben getötet hast.";
			link.l1 = "Ja, wir hatten gestern ein Geschäft, ich erinnere mich. Du zeigst das Schiff und ich töte Krabben. Schwimmen wir?";
			link.l1.go = "ring_14";
		break;
		
		case "ring_14":
			dialog.text = "Sicher! Ich werde dir folgen.";
			link.l1 = "...";
			link.l1.go = "ring_swim";
		break;
		
		case "ring_swim":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetImmortal(npchar, true);
			pchar.quest.LSC_Ring_enter.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_enter.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator = "reload_ring";
			pchar.quest.LSC_Ring_enter.function = "LSC_RingEnter";
			LSC_RingSetItems(); // раскладка итемзов
			AddQuestRecord("LSC_Ring", "3");
		break;
		
		case "ring_15":
			dialog.text = "Heh, gut gemacht! Du hast all diesen Dreck getötet!";
			link.l1 = "Ich erinnere mich, dass mir jemand von 'vier oder fünf' Krabben erzählte... Erinnere mich daran, wer das war?";
			link.l1.go = "ring_16";
		break;
		
		case "ring_16":
			dialog.text = "Kumpel, ich bin nie in den Laderaum gegangen, um sie richtig zu zählen. Ich habe nur durch das Loch geschaut. Ich hatte nicht vor, dir zu lügen.";
			link.l1 = "Egal. Lass uns den Laderaum überprüfen...";
			link.l1.go = "ring_17";
		break;
		
		case "ring_17":
			dialog.text = "Sicher! Deshalb sind wir hier, oder?";
			link.l1 = "Genau! Verschwenden wir nicht unsere Zeit...";
			link.l1.go = "ring_18";
		break;
		
		case "ring_18":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 60.0); // 1 минуту на пошариться
			npchar.quest.diagnode = "ring_19";
			AddQuestRecord("LSC_Ring", "4");
		break;
		
		case "ring_wait":
			dialog.text = "Warte mal, Kumpel, ich habe noch nicht alle Orte überprüft, die ich wollte. Suche besser, vielleicht findest du mehr Wertsachen.";
			link.l1 = "Gut...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_wait";
		break;
		
		case "ring_19":
			dialog.text = "Nichts Besonderes. Es ist schade, dass es hier keine wertvollen Waren gibt. Es gibt Vorräte in Fässern und Kopra in Kisten. Ich habe allerdings auch eine Kiste mit teurem Wein gefunden. Und was haben Sie?";
			link.l1 = "Nichts Interessantes auch. Ein paar Kisten sind ziemlich wertvoll, aber der Rest ist gepökeltes Rindfleisch und Kopra, wie du gesagt hast.";
			link.l1.go = "ring_20";
		break;
		
		case "ring_20":
			dialog.text = "Nicht genug... Lass uns nach oben gehen und das Oberdeck und die Kabinen überprüfen.";
			link.l1 = "Lass uns gehen.";
			link.l1.go = "ring_21";
		break;
		
		case "ring_21":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Ring_deck.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_Ring_deck.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_Ring_deck.win_condition = "LSC_RingEnterDeck";
			for (i=1; i<=3; i++)
			{
				sld = ItemsFromID("purse"+i);
				sld.shown = true;
				sld.startLocation = "ExternalRingDeck";
				sld.startLocator = "item"+i;
			}
		break;
		
		case "ring_22":
			dialog.text = "Verdammt! Schau dir das an! Verdammte Krabben-Dreck hat es auf das Deck geschafft! Und wie haben sie es geschafft, so einen Trick zu machen?!";
			link.l1 = "Sei kein Feigling! Bleib hier, beweg dich nicht und zieh ihre Aufmerksamkeit nicht auf dich. Ich werde mich sofort um diese Kreaturen kümmern...";
			link.l1.go = "ring_23";
		break;
		
		case "ring_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocator(npchar, "reload", "reload1", "", -1);
		break;
		
		case "ring_24":
			dialog.text = "Huh! Also waren die Geschichten über deine Fechtkunst wahr! Wenn ich hier alleine wäre, würde ich über Bord springen...";
			link.l1 = "Hör zu, und wie bist du in der Vergangenheit ein Schmuggler geworden, hm? Oder bist du vor allen davongelaufen?";
			link.l1.go = "ring_25";
		break;
		
		case "ring_25":
			dialog.text = "Kumpel, erstens war ich jünger, stärker und ungestümer. Zweitens bin ich kein Söldner, um Kriege zu führen - ich bin ein Schmuggler und wir versuchen immer, ein Blutvergießen zu vermeiden. Drittens war ich immer für Segel und Ruder, nicht für Klingen und Pistolen. Und schließlich haben mich die Jahre des Lebens hier weich gemacht\nAlso beschuldige mich nicht. Lass uns das Oberdeck überprüfen. Es sieht so aus, als hätte das Schiff einen ernsthaften Kampf gehabt - schau dir den Schaden an...";
			link.l1 = "Du hast Recht. Das Schiff war definitiv unter schwerem Beschuss. Gut, lass uns nach etwas Interessantem suchen.";
			link.l1.go = "ring_26";
		break;
		
		case "ring_26":
			dialog.text = "Ja. Und wir müssen die Eingänge zu den inneren Räumen finden.";
			link.l1 = "Abgemacht, verschwenden wir keine Zeit. Ruf mich, wenn du eine Krabbe siehst.";
			link.l1.go = "ring_27";
		break;
		
		case "ring_27":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 80.0); // 1.3 минуты на пошариться
			npchar.quest.diagnode = "ring_28";
			AddQuestRecord("LSC_Ring", "5");
		break;
		
		case "ring_28":
			dialog.text = "Wieder nichts Wertvolles... Ich habe ein paar interessante Kleinigkeiten gefunden und das ist alles. Aber das ist in Ordnung, normalerweise gibt es keine wertvollen Leckereien auf den Decks. Das Allerbeste muss in den Kabinen sein. Dort drüben ist ein Eingang zur Kapitänskajüte. Lass uns das mal überprüfen.";
			link.l1 = "Sei vorsichtig, wer weiß, was dort auf uns wartet. Vielleicht sollte ich besser zuerst hineingehen?";
			link.l1.go = "ring_29";
		break;
		
		case "ring_29":
			dialog.text = "Auf geht's, "+pchar.name+". Ich werde mich nicht länger hinter deinem Rücken verstecken. Das ist sicher eine Schande...";
			link.l1 = "Mach schon weiter...";
			link.l1.go = "ring_30";
		break;
		
		case "ring_30":
			DialogExit();
			chrDisableReloadToLocation = true;
			LocatorReloadEnterDisable("ExternalRingDeck", "reload2", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "ExternalRingCabin1", "reload", "reload1", "OpenTheDoors", -1);
			pchar.quest.LSC_Ring_cabin.win_condition.l1 = "location";
			pchar.quest.LSC_Ring_cabin.win_condition.l1.location = "ExternalRingCabin1";
			pchar.quest.LSC_Ring_cabin.win_condition = "LSC_RingEnterCabin";
			sld = ItemsFromID("RingCapBook"); // кладем журнал 'Санта-Люсии'
			sld.shown = true;
			sld.startLocation = "ExternalRingCabin1";
			sld.startLocator = "item1";
		break;
		
		case "ring_31":
			dialog.text = "Es sieht so aus, als hätte ich Glück gehabt - weder Krabben noch anderer Abschaum hier. Und jetzt werden wir diese Kajüte auf den Kopf stellen, verdammt, ich schwöre, ich fange an, wütend zu werden. Ich habe nur zwei verdammte Dutzend Dublonen und ein paar Kleinigkeiten gefunden!";
			link.l1 = "Beruhige dich. Du hattest recht, alle Wertsachen sind immer in der Kapitänskabine verstaut. Mal sehen, was wir haben!";
			link.l1.go = "ring_32";
		break;
		
		case "ring_32":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "LSC_RingSetToBarman", -1);
			DoQuestCheckDelay("LSC_RingDialog", 30.0); // 30 сек на пошариться
			npchar.quest.diagnode = "ring_33";
		break;
		
		case "ring_33":
			dialog.text = "Ha-ha! Genau wie ich dachte! Ich kenne die Gewohnheiten der Händler, sie mögen es, geheime Verstecke zu machen und dort den Schiffsschatz zu verstecken! Der Kapitän dieser Pinasse war ein schlauer Schurke, aber ich lasse mich nicht so leicht betrügen! Schau, was ich gefunden habe! Ohne mich hättest du das niemals finden können!";
			link.l1 = "Zeig es mir!";
			link.l1.go = "ring_34";
		break;
		
		case "ring_34":
			dialog.text = "Vierzigtausend Pesos, zwei Kisten voller Dublonen, ein Paket Smaragde und ein Haufen Juwelen! Der Besitzer war ziemlich reich... Gut, zumindest wird es unsere Mühe belohnen, obwohl ich gehofft hatte, mehr zu bekommen. Lass es uns gerecht teilen.";
			link.l1 = "Ausgezeichnet, Richard. Zumindest haben wir etwas Geld verdient!";
			link.l1.go = "ring_35";
		break;
		
		case "ring_35":
			TakeNItems(pchar, "jewelry4", 25);
			TakeNItems(pchar, "chest", 1);
			TakeNItems(pchar, "icollection", 1);
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("You have received a chest with doubloons");
			Log_Info("You have received 25 emeralds");
			Log_Info("You have received  a collection of jewels");
			PlaySound("interface\important_item.wav");
			dialog.text = "Nun, und lassen wir behalten, was jeder von uns auf den Decks gefunden hat, für uns selbst. Ist das in Ordnung für dich? Hast du etwas Nützliches in Kisten und Schränken gefunden?";
			link.l1 = "Ein paar indische Dinge, Amulette, Papiere und so weiter.";
			link.l1.go = "ring_36";
		break;
		
		case "ring_36":
			dialog.text = "Behalte es für dich. Du hast schließlich den riskantesten Job gemacht.";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
			{
				link.l1 = "Gut. Und ich habe noch etwas gefunden, was ein Schatzjäger wie du nützlich finden könnte. Hier, es lag ein Kapitänstagebuch auf dem Schreibtisch. Die Geschichte, die dort geschrieben steht, ist sehr traurig... aber sie betrifft uns irgendwie. Im Laderaum ist eine Kiste versteckt und sie ist mit Gold gefüllt! Lies es!";
				link.l1.go = "ring_41";
			}
			else
			{
				if (CheckCharacterItem(pchar, "RingCapBook")) // взял журнал
				{
					link.l1 = "Gut. Aber ich habe noch etwas gefunden - das Logbuch des Kapitäns.";
					link.l1.go = "ring_38";
				}
				else
				{
					link.l1 = "Also gut, ich stimme solchen Bedingungen zu, ha-ha. Also was, ist es Zeit zurückzukehren?";
					link.l1.go = "ring_37";
				}
			}
		break;
		
		case "ring_37":
			dialog.text = "Ja. Erzähl niemandem sonst von dem Schiff, es wird unser Geheimnis sein. Sicher, wir brauchen keine Kopra, aber Proviant wird für uns nützlich sein. Wir müssen es nicht mehr vom Admiral kaufen.";
			link.l1 = "Gut, ich stimme zu. Ich hoffe, dass die anderen das Schiff nicht so bald finden. Los geht's!";
			link.l1.go = "ring_cabin_exit";
		break;
		
		case "ring_38":
			dialog.text = "Hast du es gelesen?";
			link.l1 = "Noch nicht...";
			link.l1.go = "ring_39";
		break;
		
		case "ring_39":
			dialog.text = "Also lasst uns es lesen! Wir können eine wichtige Information daraus lernen. Außerdem wäre es interessant zu wissen, wie sie hier gelandet ist. Lies es!";
			link.l1 = "Hm. Gut, ich werde es jetzt lesen...";
			link.l1.go = "ring_40";
		break;
		
		case "ring_40":
			DialogExit();
			NextDiag.CurrentNode = "book_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
		break;
		
		case "book_wait":
			dialog.text = "Hast du es gelesen? Was steht da?";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
			{
				link.l1 = "Nun, hör zu... Die Geschichte ist sehr traurig... aber sie betrifft uns jetzt in gewisser Weise. Deine Schatzsuchfähigkeiten könnten uns helfen. Es gibt eine versteckte Kiste voller Gold im Frachtraum! Lies es!";
				link.l1.go = "ring_41";
			}
			else
			{
				link.l1 = "Warte mal. Ich werde lesen und dir erzählen...";
				link.l1.go = "exit";
				NextDiag.TempNode = "book_wait";
			}
		break;
		
		case "ring_41":
			dialog.text = "Wirklich? "+pchar.name+", ich bin... nun, ich lese nicht so gut. Sag mir, was dort im Detail geschrieben steht, ja?";
			link.l1 = "Kurze Version: Diese Pinasse überquerte das Karibische Meer von Süd-Main nach Neu-Spanien. Der Kapitän heiratete die indische Prinzessin eines unteren Orinoco-Stammes. Sie erzählte ihm, wo ihr Volk Opfer brachte...";
			link.l1.go = "ring_42";
		break;
		
		case "ring_42":
			dialog.text = "";
			link.l1 = "Die Goldklumpen waren ihre Opfergaben. Sicher, unser tapferer Kapitän hat diesen Goldvorrat mit Hilfe seines Ersten Offiziers und Quartiermeisters geraubt. Sie haben es in den Laderaum, in eine der Kisten gelegt und es mit Kopra bedeckt...";
			link.l1.go = "ring_43";
		break;
		
		case "ring_43":
			dialog.text = "";
			link.l1 = "Aber es scheint, dass der Raub des heiligen indischen Ortes bestraft wurde. Das Schiff geriet in eine Flaute, die Wasservorräte gingen zur Neige, eine Fieberepidemie brach aus und Piraten griffen das Schiff an. Die Seeleute gaben dem indischen Mädchen, der Frau des Kapitäns, die Schuld und verlangten, sie über Bord zu werfen. Natürlich weigerte sich der Kapitän und die Mannschaft begann einen Aufstand...";
			link.l1.go = "ring_44";
		break;
		
		case "ring_44":
			dialog.text = "";
			link.l1 = "Der Kapitän hat diesen Kampf verloren. Laut den letzten Notizen hat er sich mit einem indischen Mädchen in der Kabine eingeschlossen und versucht, auf die wütenden Matrosen zu schießen, die die Tür aufbrachen. Und ein Sturm kam auf sie zu... es scheint, dass dieser das Schiff hierher gebracht hat. Das Ende der Geschichte ist klar: das Mädchen wurde erschossen und der Kapitän wurde sicherlich von den Rebellen getötet.";
			link.l1.go = "ring_45";
		break;
		
		case "ring_45":
			dialog.text = "Hm. Es ist wirklich eine traurige Geschichte. Aber machst du Witze? Gibt es eine Kiste mit Gold im Frachtraum? Ich glaube meinen Ohren nicht! Welche? Lass uns dorthin gehen! Ich werde jeden Ballen, jedes Fass überprüfen!";
			link.l1 = "Lass uns gehen. Ich bin auch gespannt, mit der Suche zu beginnen.";
			link.l1.go = "ring_seek_gold";
		break;
		
		case "ring_cabin_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // открываем выход
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход // patch-2
			DoQuestReloadToLocation("ExternalRingDeck", "reload", "reload2", "LSC_RingFinalStage");
			sld = ItemsFromID("RingCapBook");
			sld.shown = false; // убираем журнал
			AddQuestRecord("LSC_Ring", "6");
		break;
		
		case "ring_seek_gold":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			// ставим прерывание на локатор
			pchar.quest.LSC_Ring_gold.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_gold.win_condition.l1.location = "ExternalRingInside";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator_group = "quest";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator = "gold";
			pchar.quest.LSC_Ring_gold.win_condition = "LSC_RingFindGold";
			// подменяем состав бокса
			pchar.GenQuestBox.ExternalRingInside = true;
			pchar.GenQuestBox.ExternalRingInside.box1.items.jewelry5 = 2522;
			AddQuestRecord("LSC_Ring", "7");
		break;
		
		case "ring_46":
			dialog.text = "Ha-ha! Wir haben es gefunden! Es existiert wirklich! Schaut euch diesen riesigen Haufen an! Die ganze Kiste! Es sind fünftausend Nuggets, nicht weniger! Ich habe noch nie so viel Gold gesehen!";
			link.l1 = "Glückwunsch, Kamerad. Es scheint, dass unser Unternehmen erfolgreich beendet ist... Was werden wir mit all diesem Gold machen?";
			link.l1.go = "ring_47";
		break;
		
		case "ring_47":
			dialog.text = "Was meinst du? Wir werden uns halbieren!";
			link.l1 = "Sicher werden wir das. Wo möchtest du es aufbewahren? Lässt du es hier?";
			link.l1.go = "ring_48";
		break;
		
		case "ring_48":
			dialog.text = "Ha! Sicherlich werde ich das Gold in meinen Verstecken verstecken und niemand wird sie jemals finden. Verstecken ist das, was ich gut kann! Lass uns die Hälfte des Goldes in dieses Fass legen, das wäre mein Anteil. Ich werde es vor Sonnenuntergang wegbringen.\nDu kannst mit deinem Anteil machen, was du willst. Aber du solltest es besser auch in deine eigenen Verstecke bringen. Mach mir keine Vorwürfe, wenn du dein Gold vermisst. Ich bin ein ehrlicher Mann, auf meine Weise ehrlich und ich würde es nicht wagen, deinen Anteil zu nehmen. Aber die anderen, die später hierher kommen... sie könnten es finden.";
			link.l1 = "Gut. Ich werde entscheiden, was ich mit meinem Gold mache. Lassen wir Ihren Anteil in einem Fass...";
			link.l1.go = "ring_49";
		break;
		
		case "ring_49":
			DialogExit();
			SetLaunchFrameFormParam("Two hours later..."+ NewStr() +"The gold was shared!", "", 0, 5);//табличка
			WaitDate("", 0, 0, 0, 2, 10);
			LaunchFrameForm();
			RecalculateJumpTable();
			sld = characterFromId("LSC_Rishard");
			sld.quest.diagnode = "ring_50";
			DoQuestCheckDelay("LSC_RingDialog", 5.0);
		break;
		
		case "ring_50":
			dialog.text = "Fertig... Danke, "+pchar.name+", dass du mit mir gekommen bist. Ohne dich könnte ich das nicht tun. Jetzt sollte ich vielleicht überlegen, einen Tartan zu bauen... um von hier wegzusegeln... Ach, was auch immer. Ich denke später darüber nach\nIch habe Arbeit zu erledigen - das Gold an sichere Orte zu bringen. Lebewohl, Freund, ich hoffe, du verwendest deinen Anteil weise!";
			link.l1 = "Tschüss, Richard. Es war ein herrlicher Tag heute. Bis dann!";
			link.l1.go = "ring_51";
		break;
		
		case "ring_51":
			DialogExit();
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // открываем выход
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход
			DoQuestCheckDelay("LSC_RingFinalStage", 0.5);
			DeleteAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook");
			AddQuestRecord("LSC_Ring", "8");
		break;
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Fragen? Oh, gut, wenn du es wirklich brauchst...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Wie bist du hierher gekommen?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Wollen Sie die Insel der Gerechtigkeit verlassen?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Haben Sie jemals darüber nachgedacht, einem der Clans beizutreten? Zum Beispiel den Narwals?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Ist es wahr, dass man im äußeren Ring eine Menge interessanter Dinge finden kann?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Keine Fragen. Entschuldigung...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Seit zehn Jahren segelten ich und meine Kameraden von Kuba zur Insel auf einer gut ausgestatteten Tartane. Wir hielten den Standort der Insel geheim - wir transportierten Bullenkadaver und verkauften frisches Fleisch für Waren und Gold aus den lokalen Schiffsladungen\nGute Zeiten! Versorgung war immer ein Problem hier, Brot und gesalzenes Rindfleisch meistens, also bezahlten sie uns für saftiges Fleisch mit Gewürzen, die in Europa ein Vermögen kosten! Bei jeder einzelnen Reise verdiente ich genug Geld, um jede Hure von Tortuga zu kaufen\nAber alles hat ein Ende, so auch unser zufriedenes Leben. Das Wetter wurde schlecht - die Stürme wurden stärker, so wurde die Seereise zur Insel viel gefährlicher. Einige meiner Begleiter haben das Geschäft verlassen, aber nicht ich und ein Dutzend mutige Männer\nSchließlich wurden wir zwei Meilen von der Insel auf ein Riff geworfen. Ich verstehe immer noch nicht, wie ich es geschafft habe, durch das stürmische Meer zu schwimmen. So wurde ich zu einem von denen, mit denen ich in der Vergangenheit gehandelt habe.";
			link.l1 = "Interessante Geschichte...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Ha! Ich werde hier rauskommen, verdammt! Aber später. Was sollte ich auf Kuba? Ich habe keine Freunde mehr und meine Tasche ist leer. Ich fange an, ein Boot zu bauen, sobald ich ein Schiff mit wertvoller Fracht am Außenring oder einen Haufen Dublonen finde.";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;
		
		case "ansewer_3":
			dialog.text = "Und warum sollte ich das tun? Um alle drei Tage wie ein Idiot Wache zu stehen und die Leute von der San Gabriel fernzuhalten? Und sie stellen nicht gerne neue Leute ein. Sie sind Einheimische... Und Negros sind genauso. Nein, ich bin lieber für mich allein.";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Sicher! Das ist es, was die Insel und die Einheimischen noch am Leben hält. Weißt du, wann hier Partys stattfinden? Wenn ein neues Schiff ankommt. Aber so oder so, es gibt viele unberührte Schiffe voller Gold und Waren im äußeren Ring. \nDas Problem ist, dass der äußere Ring fast unmöglich zu erkunden ist, dort draußen ist alles chaotisch, wenn du dich verfängst, ausrutscht oder schlecht hinunterfällst - du könntest dich in einem Loch wiederfinden, aus dem du nicht alleine herauskommen kannst. Dann bist du erledigt. Viele Menschen sind auf diese Weise gestorben.";
			link.l1 = "Hm... Interessant.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Was machst du da, ah? Dieb!","Schau dir das an! Kaum bin ich in Gedanken verloren, entscheidest du, meine Truhe zu überprüfen!","Du hast also beschlossen, meine Truhen zu überprüfen? Das wirst du nicht ungestraft tun!");
			link.l1 = "Verdammt!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Was?! Hast du vor, meine Truhen zu durchsuchen? Das wirst du nicht ungestraft tun!";
			link.l1 = "Dummes Mädchen!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Hör zu, du solltest besser deine Waffe weglegen. Es macht mich nervös.","Du weißt, hier wird es nicht geduldet, mit einer Klinge herumzulaufen. Nimm sie weg.","Hör zu, spiel nicht den mittelalterlichen Ritter, der mit einem Schwert herumläuft. Leg es weg, es steht dir nicht...");
			link.l1 = LinkRandPhrase("Gut.","In Ordnung.","Wie du sagst...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin Bürger dieser Stadt und würde dich bitten, dein Schwert niederzuhalten.","Hör zu, ich bin ein Bürger der Stadt und ich bitte dich, dein Schwert niederzulegen.");
				link.l1 = LinkRandPhrase("Gut.","In Ordnung.","Wie du sagst...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sei vorsichtig, Kumpel, beim Laufen mit einer Waffe. Ich kann nervös werden...","Ich mag es nicht, wenn Männer vor mir hergehen, die Waffen bereit. Es macht mir Angst...");
				link.l1 = RandPhraseSimple("Hab's verstanden.","Ich nehme es weg.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
