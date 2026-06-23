// Гхерад Смиитс - матрос
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
				dialog.text = "Ich möchte nicht mit dir reden. Du greifst friedliche Zivilisten ohne Grund an und provozierst sie zum Kampf. Verschwinde!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Guten Tag, Kamerad, ha-ha! Was machst du hier?";
				link.l1 = TimeGreeting()+". Kenne ich dich?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Willst du etwas?";
				link.l1 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Gibt es Neuigkeiten auf der Insel?","Wirst du mir die letzten Klatschgeschichten erzählen?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Ich möchte Ihnen einige Fragen zur Insel stellen.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Wollte nur wissen, wie es dir geht. Bis später!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Sicher, du tust es nicht, aber das lässt sich leicht beheben, oder? Ich bin Gerard Smeets, Seemann aus Rotterdam. Und du siehst aus wie ein Quartiermeister, nicht weniger...";
			link.l1 = "So etwas. Mein Name ist "+GetFullName(pchar)+". Freut mich, dich zu treffen.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Sie sehen eher aus wie ein Schiffseigner oder Zahlmeister... Sie sind zweifellos ein gebildeter Mann. Freut mich, Sie kennenzulernen. Wie sind Sie hierher gekommen?";
			link.l1 = "Ich habe mich entschieden, ein unbekanntes Gebiet zu erkunden. Freibeuter aus Kuba erzählten mir, dass es in dieser Gegend etwas gibt und ich beschloss, es zu überprüfen...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Bist du der einzige Überlebende? Wo ist dein Schiff gesunken? In der Nähe des Rings?";
			link.l1 = "Ich bin der Einzige. Und meine Tartane liegt auf dem Meeresgrund, sie hat es nicht mal bis zum Ring geschafft.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Ich verstehe. Nun, du bist hier für eine Weile fest. Besuche Sancho, um etwas Rum zu bekommen, es ist eine gute Tat...";
			link.l1 = "Ich werde. Bis dann!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Gibt es Neuigkeiten auf der Insel?","Wirst du mir die neuesten Klatsch und Tratsch erzählen?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Ich möchte Ihnen ein paar Fragen über die Insel stellen.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Sicher, Freund. Ich höre zu.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Sag mal, wie bist du hierher gekommen?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Möchten Sie die Insel verlassen und zu Ihrem normalen Leben zurückkehren?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Stören dich die Clans nicht?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Wie hat sich die Insel gebildet, hast du irgendwelche Ideen dazu?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Keine Fragen. Entschuldigung...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Ich bin hier mit diesem aufgeblasenen Hahn namens Abbot gelandet. Ich diente auf seinem Schiff. Weißt du was? Leute wie er sollten niemals einen Fuß auf das Schiffsdeck setzen, denn sie bringen Unglück. Der Teufel muss ihn dazu gebracht haben, mit uns zu segeln.\nWir mussten nur von Jamaika nach Belize segeln, ein Kinderspiel. Aber das Unglück verfolgte uns: unser Bootsmann fiel über Bord, ein Navigator machte einen Fehler, blutige Spanier und am Ende ein Sturm. Und hier sind wir.";
			link.l1 = "Interessant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Ich wünschte, ich wüsste es, Kumpel. Ich wusste es früher, aber jetzt nicht mehr. Das Leben hier ist gut, viel Rum und Wein, gutes Essen, nicht viel, aber auf jeden Fall besser als der Scheiß, den ich auf Schiffen gegessen habe\nHier auf der Insel leben auch gute Leute. Es gibt Leute, mit denen man entweder trinken oder reden kann. Ich mag es hier. Also bin ich mir nicht mal sicher... Nein, ich glaube nicht, dass ich gehen will. Ich war früher wütend und hungrig, schau dir jetzt meinen Bauch an, ha-ha!";
			link.l1 = "Großartig! Ich freue mich für dich.";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Nein, tun sie nicht. Streite einfach nicht mit ihnen und besuche ihre Territorien nicht ohne Erlaubnis. Sie mögen das wirklich nicht. Narwale sind gute Kerle, die meisten von ihnen wurden hier geboren und haben kein anderes Leben gesehen. Viele von ihnen sind sehr geschickt, zum Beispiel Jurgen Schmidt. Er ist ein Gott der Schmiedekunst!";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "So einfach wie Kuchen. Untiefe und Riffe. Der äußere Ring besteht von oben bis unten aus Schiffen. Schiffe geraten in einen Sturm, treffen auf die Riffe oder den äußeren Ring selbst. So wächst die Insel. Obwohl ich keine Ahnung habe, warum die inneren Schiffe über Wasser bleiben.";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Was machst du da, ah? Dieb!","Nur schau! Kaum war ich in Gedanken versunken, hast du beschlossen, meine Truhe zu überprüfen!","Entschieden, meine Kisten zu überprüfen? Du kommst damit nicht davon!");
			link.l1 = "Verdammt!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Was?! Hast du dich entschieden, meine Truhen zu überprüfen? Damit kommst du nicht davon!";
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
			dialog.text = LinkRandPhrase("Hör zu, du solltest besser deine Waffe weglegen. Es macht mich nervös.","Weißt du, hier wird es nicht toleriert, mit einer Klinge herumzulaufen. Nimm sie weg.","Hör zu, spiel nicht den mittelalterlichen Ritter, der mit einem Schwert herumläuft. Leg es weg, es steht dir nicht...");
			link.l1 = LinkRandPhrase("Gut.","Wie du wünschst...","Wie du sagst...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin ein Bürger der Stadt und ich bitte dich, dein Schwert niederzulegen.","Hör zu, ich bin der Bürger der Stadt und ich bitte dich, deine Klinge niederzulegen.");
				link.l1 = LinkRandPhrase("Gut.","Wie auch immer dann.","Wie du sagst...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sei vorsichtig, Kumpel, wenn du mit einer Waffe herumläufst. Ich kann nervös werden...","Ich mag es nicht, wenn Männer vor mir herlaufen, mit gezückter Waffe. Es macht mir Angst...");
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
