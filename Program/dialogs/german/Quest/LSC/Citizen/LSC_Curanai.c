// Куранай - индеец
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

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
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Was will der weiße Bruder?";
				link.l1 = TimeGreeting()+". Weißer Bruder? Sag mir, warum ihr uns Indianer entweder Weiße Brüder oder bleiche Hunde nennt, huh?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Willst du etwas?";
				link.l1 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Gibt es Neuigkeiten auf der Insel?","Wirst du mir die neuesten Klatschereien erzählen?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Ich möchte Ihnen ein paar Fragen über die Insel stellen.";
				link.l2.go = "int_quests"; //информационный блок
				if (CheckAttribute(npchar, "quest.answer_2"))
				{
					link.l3 = "Zeig mir, was du gefunden hast. Vielleicht kaufe ich etwas...";
					link.l3.go = "trade";
				}
				link.l5 = "Wollte nur wissen, wie es dir geht. Bis dann!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Wir leben alle in Frieden hier, weißer Bruder. Curanai nennt weißen Bruder nicht den bleichgesichtigen Hund. Nicht alle Bleichgesichter - Hunde. Ich kann viele Indianer den Rothäutigen Hund nennen.";
			link.l1 = "Hm. Ich nehme an, dass du ein Philosoph bist...";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Curanai versteht dich nicht, weißer Bruder. Was bedeutet Philosoph?";
			link.l1 = "Es ist egal, Rothaut Bruder. Mir gefällt einfach, wie du denkst. Du sagst, dein Name ist Curanai? Mein Name ist "+GetFullName(pchar)+". Freut mich, dich zu treffen.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Curanai freut sich, den Namen des weißen Bruders zu erfahren.";
			link.l1 = "Gut. Wir sehen uns!";
			link.l1.go = "exit";
			link.l3 = "Ich möchte Ihnen einige Fragen über die Insel stellen.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 4)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Frag, bleichgesichtiger Bruder, Curanai antwortet.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Wie bist du hierher gekommen?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Was machst du auf der Insel?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Willst du nach Hause kommen?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Lebst du friedlich auf der Insel? Kommt es hier zu Kämpfen oder Streitigkeiten?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Keine Fragen. Entschuldigung...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Ich und mehrere Krieger meines Stammes beschlossen, zu einer kleinen Insel nahe unserem Land zu segeln, die an klaren Tagen sichtbar ist. Wir bauten ein Floß aus Bambus und segelten los. Aber ein Sturm überraschte uns plötzlich und trieb uns aufs offene Meer. Wir merkten nicht, wie schnell unser Land und die Insel verschwanden\nWir segelten viele, viele Nächte und Tage auf dem Meer. Alle meine Brüder starben an Durst und Hunger. Ich blieb alleine zurück - die Geister hatten Mitleid mit Curanai und brachten ein Floß zu dieser Insel. Ich überlebte.";
			link.l1 = "Ja... Traurige Geschichte.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Curanai fischt. Curanai trifft Fisch mit Harpune. Selten-selten trifft er großen Krebs. Dann ist Curanai glücklich - Krebs ist lecker, sehr lecker. Eine Schere reicht für ein paar Tage. Und Curanai taucht auch unten zu einem Ort. Keine großen Krebse dort. Curanai sammelt gelben Stein, blauen Stein, schwarzen Stein und Perle. Groß und klein. Dann verkauft Curanai sie an den Bleichgesichter.";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Curanai will nach Hause gehen. Aber wo ist mein Zuhause? Curanai weiß nicht, wo sein Dorf ist und wie man dorthin kommt.";
			link.l1 = "Hm. Was kann ich sagen...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Narwal und Rivados kämpfen oft gegeneinander. Wir leben in Frieden und verletzen niemanden. Manchmal trinken die Bleichgesichter Feuerwasser und fluchen, aber niemand tötet. Es gibt zwei Offizierskrieger, einer hasst den anderen. Eines Tages wird einer den anderen töten. Curanai weiß.";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Was machst du da, ah? Dieb!","Schau dir das an! Kaum war ich in Gedanken versunken, hast du dich entschlossen, meine Truhe zu überprüfen!","Hast du beschlossen, meine Kisten zu durchsuchen? Das wirst du nicht ungestraft davonkommen!");
			link.l1 = "Scheiße!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Was?! Du hast dich entschieden, meine Truhen zu überprüfen? Das wirst du nicht ungestraft davonkommen!";
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
			dialog.text = LinkRandPhrase("Hör zu, du solltest besser deine Waffe weglegen. Es macht mich nervös.","Weißt du, hier wird es nicht geduldet, mit einer Klinge herumzulaufen. Nimm sie weg.","Hör zu, spiel nicht den mittelalterlichen Ritter, der mit einem Schwert herumläuft. Leg es weg, es steht dir nicht...");
			link.l1 = LinkRandPhrase("Gut.","Sicher.","Wie du sagst...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin ein Bürger der Stadt und ich würde dich bitten, dein Schwert zu senken.","Hör zu, ich bin ein Bürger dieser Stadt und ich bitte dich, dein Schwert niederzulegen.");
				link.l1 = LinkRandPhrase("Gut.","Wie auch immer.","Wie du sagst...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sei vorsichtig, Kumpel, beim Laufen mit einer Waffe. Ich kann nervös werden...","Ich mag es nicht, wenn Männer vor mir herlaufen mit ihrer Waffe bereit. Es macht mir Angst...");
				link.l1 = RandPhraseSimple("Habs verstanden.","Ich nehme es weg.");
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
