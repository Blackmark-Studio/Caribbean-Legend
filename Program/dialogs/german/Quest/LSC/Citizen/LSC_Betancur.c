// Антонио Бетанкур - потомок Франциско Бетанкура
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
				dialog.text = "Hallo, Hallo... Was möchtest du, Freund?";
				link.l1 = TimeGreeting()+". Mein Name ist "+GetFullName(pchar)+". Und ich wollte nur wissen, wer du bist. Siehst du, ich bin neu angekommen, spaziere durch die Stadt und unterhalte mich mit Leuten.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Was willst du diesmal?";
				if(CheckAttribute(pchar, "questTemp.LSC.Betancur"))
				{
					link.l4 = "Antonio, man sagt, du kennst die Geschichte der Insel gut. Ich habe eine Frage dazu an dich.";
					link.l4.go = "dolly";
				}
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Willst du etwas?";
				link.l1 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Gibt es Neuigkeiten auf der Insel?","Wirst du mir die neuesten Klatsch und Tratsch erzählen?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Ich möchte Ihnen ein paar Fragen über die Insel stellen.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Wollte nur wissen, wie es dir geht. Bis dann!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Herrlich. Und du wirst dich gut einleben, denn wir sind hier alle eine große Familie. Bis auf die Narwale und die verdammten Rivados natürlich. Mein Name ist Antonio, Antonio Betancourt. Ich bin der Enkel von Francisco Betancourt, falls dir dieser Name etwas sagt.";
			link.l1 = "Francisco Betancourt? Ich habe diesen Namen schon einmal gehört... Ah, sicher! Dios erzählte mir von ihm und ich las über ihn in den Notizen von Alvarado...";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Ich habe keine Ahnung, wer dieser Dios von euch ist, aber Kapitän Alvarado hat uns vor langer Zeit besucht. Ich habe ihn persönlich gesehen, als ich noch ein Kind war. Er segelte von der Insel weg und schrieb darüber in seinen Manuskripten. Und Francisco Betancourt war ein spanischer Admiral, ein Kommandant der Militärschwadron. Die Geschichte dieses Ortes begann mit der Tatsache, dass alle Rivados Nachkommen von schwarzen Sklaven aus Tartarus, dem Flaggschiff der Schwadron, sind. Die Narwale sind Kinder der ersten weißen Siedler, Besatzungsmitglieder von Tartarus, San Augustine und San Geronimo.";
			link.l1 = "Unglaublich! Also bist du hier geboren?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Genau. Ich bin ein direkter Nachkomme eines Mannes, der im Grunde die Insel der Gerechtigkeit besetzt hat.";
			link.l1 = "Ich verstehe. Freut mich, dich kennenzulernen, Antonio. Wir sehen uns.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестовая часть
		case "dolly":
			dialog.text = "Hm... Sicher, Freund, frag mich. Ich werde deine Fragen natürlich beantworten, aber nur wenn ich die Antworten kenne.";
			link.l1 = "Sag mir, erinnerst du dich an die Zeit, als die Galeone San Geronimo noch hier war?";
			link.l1.go = "dolly_1";
		break;
		
		case "dolly_1":
			dialog.text = "Sicher, das tue ich. Es war ein sehr besonderes Schiff. Dort war eine interessante indische Statue und diese schmutzigen heidnischen Rivados führten Opfergaben durch.";
			link.l1 = "Und wie haben sie das gemacht? Haben sie den Menschen das Herz rausgerissen wie die Maya? Oder haben sie Köpfe abgeschlagen?";
			link.l1.go = "dolly_2";
		break;
		
		case "dolly_2":
			dialog.text = "Nein... Es war eine sehr besondere Statue - sie zog Opfer in sich hinein und sie verschwanden für immer. Das Werkzeug des Teufels... Gott sei Dank ist sie mit dem Schiff gesunken und wird nie wieder Schaden anrichten. Es ist ziemlich interessant, dass Opfer immer zur gleichen Zeit am Morgen gebracht wurden. Die Statue verwandelte sich im Licht der aufgehenden Sonne in Gold\nDas war, als die Wilden Opfer brachten, meistens die Narwale, die sie gefangen hatten.";
			link.l1 = "Interessant! Und hat schon mal jemand versucht zu erforschen, wie die Statue funktioniert?";
			link.l1.go = "dolly_3";
		break;
		
		case "dolly_3":
			dialog.text = "Natürlich nicht! Erstens, die Rivados lassen niemanden außer ihren eigenen in die Nähe von San Geronimo und zweitens, ein ehrlicher Katholik muss sich von Teufelsaktionen fernhalten.";
			link.l1 = "Verstanden. Ich sehe, dass du Rivados nicht magst. Liege ich richtig?";
			link.l1.go = "dolly_4";
		break;
		
		case "dolly_4":
			dialog.text = "Tue ich das? Ich hasse diese schmutzigen Heiden! Falls du es nicht weißt, mein Großvater war Kapitän des Schiffes, auf dem die Negros mit ihrem Anführer Rivados meuterten. Ihren sogenannten Anführer im Laderaum verrotten zu lassen, war das Richtige. Ich hatte auch einen wunderschönen Schlüssel zur Schatzkammer von St. Anna\nNiemand weiß, wo die Schatzkammer zu finden ist, vielleicht liegt sie mit Krabben drum herum auf dem Meeresgrund, aber der Schlüssel war für mich eine süße Erinnerung und dennoch wurde er gestohlen! Ich bin mir sicher, dass die Schwarzen es getan haben. Sie müssen versuchen, die Schatzkammer zu finden. Ich bezweifle, dass sie Erfolg haben werden, es ist schon zu lange her, ha-ha! Abschaum...";
			link.l1 = "Ich verstehe. Danke für deine interessante Geschichte!";
			link.l1.go = "dolly_5";
		break;
		
		case "dolly_5":
			dialog.text = "Sie sind willkommen, ich freue mich immer zu plaudern!";
			link.l1 = "Auf Wiedersehen!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.Betancur");
			AddQuestRecord("LSC", "16");
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ich höre zu, Kumpel.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Hast du in deinem Leben nichts anderes als die Insel gesehen?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Du wurdest hier geboren... Und warum bist du kein Mitglied des Narwal-Klans? Ich dachte, alle einheimischen Weißen wären Narwale...";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Und was machst du auf der Insel?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Sag mal, wolltest du schon mal die Insel für eine Weile verlassen? Um die Welt zu sehen...";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Keine Fragen. Entschuldigung...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Scheint so, ja. Aber denke nicht, dass ich ein Idiot oder engstirnig bin. Ich habe eine feine Bibliothek von meinem Großvater geerbt und mein Vater hat mir eine ausgezeichnete Ausbildung ermöglicht. Ich kenne die antike Geschichte, Geographie, Astronomie, ich kann Englisch, Französisch, Spanisch und sogar Latein\nViele Seeleute, die überall waren, wissen weniger als ich. Obwohl ich nichts anderes gesehen habe als diese Schiffswracks, habe ich geistig Europa, China und Indien besucht...";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Es ist nicht wahr, obwohl du zu neunzig Prozent richtig liegst. Aber ich bin kein Narwal und ich möchte nicht einer von ihnen werden. Zu welchem Zweck? Um stundenlang wie ein Narr Wache zu halten oder gegen Rivados zu kämpfen? Keine Chance, verschone mich damit. Ich bin anders. Ich lebe lieber unabhängig und lese Bücher.";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Vater hat mir ein anständiges Erbe hinterlassen und ich gebe es sorgfältig aus. Also muss ich nicht um alte Schiffswracks herumschleichen, um einige Juwelen zu finden, die ich gegen Essen tauschen kann. Ich glaube nicht an große Schätze in alten Schiffen\nDer einzige Schatz, den ich kenne, ist die Schatzkammer von St. Anna. Es ist eine große Eisenkiste. Aber niemand hat es bisher geschafft, sie zu finden\nAußerdem werde ich eine detaillierte Geschichte der Insel auf Grundlage der örtlichen Geschichten schreiben. Wie denkst du - sollte ich es versuchen?";
			link.l1 = "Ich bin mir sicher. Ich kenne mindestens einen Mann im Archipel, der für ein solches Buch viel Gold bezahlen würde. Also ist es deine Chance...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Manchmal denke ich darüber nach. Vielleicht, wenn ein Schiff, das mit der Strömung umgehen und Stürme überleben könnte, hierher gekommen wäre, würde ich ein Risiko eingehen. Ich bin wirklich begierig darauf, die Dinge zu sehen, die in meinen Büchern so interessant beschrieben sind! Aber das sind vorerst nur Träume...";
			link.l1 = "Träume werden wahr. Glaube einfach an sie...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Was machst du da, ah? Dieb!","Schau dir das an! Kaum war ich in Gedanken versunken, hast du dich entschieden, meine Truhe zu überprüfen!","Hast du beschlossen, meine Truhen zu überprüfen? Das wirst du nicht ungestraft davonkommen!");
			link.l1 = "Scheiße!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Was?! Hast du beschlossen, meine Truhen zu überprüfen? Du kommst damit nicht durch!";
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
			dialog.text = LinkRandPhrase("Hör zu, du solltest besser deine Waffe weglegen. Es macht mich nervös.","Weißt du, hier wird es nicht geduldet, mit einer Klinge herumzulaufen. Nimm es weg.","Hör zu, spiel nicht den mittelalterlichen Ritter, der mit einem Schwert herumläuft. Nimm es weg, es steht dir nicht...");
			link.l1 = LinkRandPhrase("Gut.","Wie du wünschst...","Wie du sagst...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin ein Bürger der Stadt und ich bitte dich, dein Schwert niederzulegen.","Hör zu, ich bin Bürger dieser Stadt und ich bitte dich, dein Schwert niederzuhalten.");
				link.l1 = LinkRandPhrase("Gut.","Wie du wünschst...","Wie du meinst...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sei vorsichtig, Kumpel, wenn du mit einer Waffe herumläufst. Ich kann nervös werden...","Ich mag es nicht, wenn Männer mit gezogener Waffe vor mir gehen. Es macht mir Angst...");
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
