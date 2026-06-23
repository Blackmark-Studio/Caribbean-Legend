// Джозеф Лодердэйл - английский военный офицер
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
				dialog.text = "Ich möchte nicht mit dir reden. Du greifst friedliche Zivilisten ohne Grund an und provozierst sie zum Kampf. Verzieh dich!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Guten Tag, Herr. Es freut mich, hier einen edlen Mann zu treffen.";
				link.l1 = TimeGreeting()+". Tatsächlich war ich während meiner Zeit im Archipel so nah bei den einfachen Leuten, dass ich angefangen habe, meinen Adel zu vergessen...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = TimeGreeting()+", "+GetFullName(pchar)+"! Freut mich, dich zu treffen! Was wirst du sagen?";
				link.l1 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Gibt es Neuigkeiten auf der Insel?","Wirst du mir die letzten Klatschereien erzählen?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Ich möchte Ihnen ein paar Fragen zur Insel stellen.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Wollte nur wissen, wie es dir geht. Bis dann!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Oh, und du bist sogar bescheiden! Ein wahrer Gentleman! Ich glaube, wir werden Freunde sein, du bist nicht wie dieser aufgeblasene Abt... Darf ich mich vorstellen - Josef Loderdale, der ehemalige Kapitän der englischen Marineflotte.";
			link.l1 = "Freut mich, dich zu treffen. "+GetFullName(pchar)+" zu Ihren Diensten!";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Es ist ziemlich langweilig hier zu leben, also besuche abends die Taverne, wir können ein Glas Wein trinken und ein interessantes Gespräch führen...";
			link.l1 = "Ich werde das im Gedächtnis behalten, Herr. Auf Wiedersehen!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Ist auf der Insel etwas Neues passiert?","Wirst du mir die letzten Klatschgeschichten erzählen?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Ich möchte Ihnen ein paar Fragen zur Insel stellen.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Es wäre mir eine Freude, Ihre Fragen zu beantworten, Herr...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Wie bist du hierher gekommen?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Welche Art von Dienstleistung kann ich hier bekommen?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Als Militäroffizier, was denken Sie über die Dominanz der Piraten hier?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Ich habe hier auf der Insel viele verschlossene Kisten gesehen. Die Leute vertrauen sich gegenseitig nicht, oder?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Keine Fragen. Entschuldigung...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Meine militärischen Pflichten erfüllend. Ich kämpfte gegen eine spanische Kriegsschaluppe, wir glaubten, dass sie das Schiff war, das für das Plündern englischer Händler verantwortlich war. Der Kampf war lang, wir hatten sie fast, aber ein plötzlicher Sturm verdarb das Spiel. Als Ergebnis strandeten beide Schiffe in der Nähe der äußeren Ringe\nDas Glück hat einen Sinn für Humor, ich und der spanische Kapitän überlebten. Vielleicht hast du ihn hier schon getroffen. Sein Name ist Lorenzo Solderra, ein seltenes Stück Abschaum. Sei vorsichtig mit ihm.";
			link.l1 = "Verstanden. Ich werde deine Warnung berücksichtigen...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Wenn du dich ausruhen musst - besuche Sanchos Taverne. Er wird dir immer Essen, Getränke und ein Bett zur Verfügung stellen. Wenn du Pulver, Munition, Waffen und andere Dinge brauchst - gehe zu Axel Yost, er besitzt den örtlichen Laden. Medikamente kannst du bei Bruder Julian kaufen, er verkauft auch heilige Gegenstände in seiner Kirche\nDie Narwale haben einen sehr talentierten Schmied namens Schmidt. Man sagt, dass er ausgezeichnete Klingen herstellt. Unter den Narwalen gibt es auch einen anderen talentierten Handwerker, aber ich habe es versäumt, mehr über ihn zu erfahren\nUnd wenn du Probleme mit Piraten oder Clans hast, dann sieh Giuseppe Fazio, er ist der richtige Spezialist für solche Geschäfte.";
			link.l1 = "Danke für die Information!";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Ich kann nicht sagen, dass ich es mag, aber es gibt nichts, was ich dagegen tun kann. Ich gebe zu, es hat nur ein paar Tage gedauert, bis die Piraten Frieden geschlossen und Ordnung auf der Insel hergestellt haben. Bevor die Piraten ankamen, bekämpften sich die Clans regelmäßig und die gewöhnlichen Leute litten am meisten\nAußerdem verkaufen sie sehr ordentlich und fair Essen - die Bürger bekommen es zu einem sehr kleinen Preis, das kann man von den Clans nicht sagen, die Piraten ziehen sie bei lebendigem Leibe aus als Rache für den Beginn eines Krieges\nIch kenne einen sehr klugen Mann unter den Piraten, sein Name ist Layton Dexter. Er ist derjenige, der den Handel betreibt. Ich hatte einmal ein Gespräch mit ihm, ich frage mich, wie so ein talentierter und gut ausgebildeter Mann, der Taktik, Kartographie und Handel kennt, sich den Piraten angeschlossen hat\nEs dauerte nur ein paar Tage, bis er eine ausgezeichnete Karte der Insel erstellt hatte. Ich habe sie gesehen, sie hat fast alles. Ich glaube, er hat sie für einen möglichen Krieg gegen die Clans gemacht...";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
			sld = characterFromId("Dexter");
			sld.quest.map = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Das ist das Richtige zu tun. Sie sagen, dass lange vorher, Diebstahl auf der Insel normal war, bis alle Kisten neue Schlösser bekamen. Und doch gibt es immer noch jemanden, der Kisten knacken kann. Aber er stiehlt nur Rum und billigen Schmuck, hat nie Gold oder Geld genommen\nAlle Schlösser sind einzigartig, es gibt keine gleichen Schlüssel - Jurgen Schmidt hat dafür gesorgt. Er fertigt nicht nur Klingen, sondern auch Schlösser und Schlüssel. Mir wurde gesagt, dass äußere Kisten keine Wertsachen enthalten, ernsthafte Gegenstände werden immer in den Schiffen aufbewahrt.";
			link.l1 = "Interessant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Was machst du da, ah? Dieb!","Schau dir das an! Kaum war ich in Gedanken versunken, hast du beschlossen, meine Truhe zu überprüfen!","Hast du beschlossen, meine Truhen zu überprüfen? Damit wirst du nicht davonkommen!");
			link.l1 = "Scheiße!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Was?! Hast du beschlossen, meine Truhen zu überprüfen? Damit kommst du nicht durch!";
			link.l1 = "Torichte Mädchen!";
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
			dialog.text = LinkRandPhrase("Hör zu, du solltest besser deine Waffe weglegen. Es macht mich nervös.","Weißt du, hier wird es nicht toleriert, mit einer Klinge herumzulaufen. Leg sie weg.","Hör zu, spiel nicht den mittelalterlichen Ritter, der mit einem Schwert herumläuft. Leg es weg, es steht dir nicht...");
			link.l1 = LinkRandPhrase("Gut.","Wie du wünschst...","Wie du sagst...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin Bürger dieser Stadt und ich würde dich bitten, deine Klinge niederzuhalten.","Hör zu, ich bin Bürger der Stadt und ich bitte dich, dein Schwert niederzulegen.");
				link.l1 = LinkRandPhrase("Gut.","Wie du wünschst...","Wie du sagst...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sei vorsichtig, Kumpel, beim Laufen mit einer Waffe. Ich kann nervös werden...","Ich mag es nicht, wenn Männer vor mir herlaufen, mit ihrer Waffe bereit. Es macht mir Angst...");
				link.l1 = RandPhraseSimple("Verstanden.","Ich nehme es weg.");
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
