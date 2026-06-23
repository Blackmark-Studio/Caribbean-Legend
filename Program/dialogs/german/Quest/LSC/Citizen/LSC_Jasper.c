// Джаспер Пратт - каторжник
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
				dialog.text = "Guten Tag, Herr. Wünschen Sie etwas?";
				link.l1 = TimeGreeting()+". Mein Name ist "+GetFullName(pchar)+", und was ist mit dir? Ich bin neu hier...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
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
			dialog.text = "Ich? Ich bin Jasper, der ehemalige Staatssträfling. Deshalb schauen die Menschen mich schief an. Ach, zur Hölle mit ihnen, ich habe mich daran gewöhnt...";
			link.l1 = "Es ist mir egal, wer du warst, wer du jetzt bist, ist das, was zählt.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Es ist schade, dass nicht jeder wie Sie denkt, Herr.";
			link.l1 = "Nun, ich bin bekannt für meine liberale Einstellung...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Freut mich für dich. Mach dir keine Sorgen, trotz meiner Vergangenheit bin ich keine Bedrohung für die Geldbörsen und Truhen der Inselbewohner. Ich bin froh, dass ich endlich in Frieden leben kann.";
			link.l1 = "Freut mich, dich zu treffen, Jasper. Auf Wiedersehen!"link.l1.go ="Ausgang";
			link.l2 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Gibt es Neuigkeiten auf der Insel?","Wirst du mir die letzten Klatsch und Tratsch erzählen?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Ich möchte Ihnen ein paar Fragen zu der Insel stellen.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ja, sicher. Ich werde dir antworten, wenn ich kann. Frag.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Wie bist du Bewohner der Insel geworden?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Gefällt Ihnen dieser Ort?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Du hast erwähnt, dass die Leute dich schief anschauen. Ist das wegen deiner Vergangenheit?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Diese Insel ist ziemlich interessant, findest du nicht?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Keine Fragen. Entschuldigung...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Ich bin von der Kubanischen Plantage weggelaufen. Wir waren zu fünft und haben beschlossen, dass es vorzuziehen ist zu sterben, als weiterhin für Schläge unseren Rücken zu brechen. Wir haben es geschafft, die Wachen auszutricksen und in den Dschungel zu verschwinden, dann haben wir das Ufer erreicht und ein Floß gebaut\nWir wollten nach Tortuga, aber das Schicksal hat anders entschieden. Keiner von uns wusste, wie man navigiert, also haben wir uns verlaufen. Dann ging das Wasser aus... Ich will mich nicht daran erinnern. Als Ergebnis war ich derjenige, der die Insel der Gerechtigkeit erreicht und überlebt hat.";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Weißt du, ich bin damit zufrieden. Nach allem, was ich auf der Plantage durchgemacht habe, fühlt sich dieser Ort für mich wie der Himmel an. Ich brauche nicht viel... Ein bisschen Essen, Wasser und jeden Abend ein Glas Rum. Niemand stört mich hier und ich habe nicht vor, diesen Ort zu verlassen. Ich werde hier sterben, wenn meine Zeit kommt.";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Die Sache ist, dass die Insel ein Spielplatz für einen geheimnisvollen Dieb ist. Schlösser sind für ihn kein Problem. Meistens hält er sich in den Kammern des Admirals auf. Aber auch unsere Truhen bleiben nicht unversehrt. Niemand weiß, wer dieser Dieb ist, also verdächtigen sie Leute mit... hm, krimineller Vergangenheit. Der Dieb ist allerdings etwas seltsam: erstens, er nimmt nur Flaschen mit Spirituosen und einige Schnickschnack, er nimmt nie wertvolle Gegenstände. Lustig, nicht wahr?";
			link.l1 = "Habs verstanden...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Ja, ich stimme zu. Ich bin viel um die inneren Schiffe der Insel der Gerechtigkeit geschwommen. Es gibt sehr wenige Ausgänge aus dem Wasser. San Augustin, der Brückenplatz. Gloria, der gefallene Mast. Wenn du nahe an der Fenix-Plattform schwimmst und dann um die Ceres Schmiede herum, erreichst du Mary Caspers Kabine am Bug des Schiffes\n Der Riss im Tartarus führt dich zum Gefängnis. Es gibt ein Loch im Bug von San Augustine, du könntest in den Lagerraum des Admirals gelangen, aber das ist ein unratsamer Kurs. Die unterste Tür des Tartarus ist oft verschlossen, denk daran\n Und natürlich kannst du in die Fernanda gelangen, es ist die einsame und zerrissene Flöte. Sie sagen, dass dort niemand lebt, aber ich bemerke oft Lichter in der Kabine und manchmal höre ich seltsame betrunkene Lieder und Schreie.";
			link.l1 = "Interessant... Ich muss diesen Ort noch mehr erkunden.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Was machst du da, ah? Dieb!","Schau dir das an! Kaum war ich in Gedanken versunken, hast du beschlossen, meine Truhe zu überprüfen!","Du willst meine Truhen kontrollieren? Das wirst du nicht ungestraft tun!");
			link.l1 = "Mist!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Was?! Hast du dich entschieden, meine Truhen zu durchsuchen? Das wirst du nicht ungestraft davonkommen!";
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
			dialog.text = LinkRandPhrase("Hör zu, du solltest besser deine Waffe weglegen. Es macht mich nervös.","Weißt du, hier wird nicht geduldet, mit einer Klinge herumzulaufen. Nimm sie weg.","Hör zu, spiel nicht den mittelalterlichen Ritter, der mit einem Schwert herumläuft. Leg es weg, es passt nicht zu dir...");
			link.l1 = LinkRandPhrase("Gut.","Wie auch immer dann.","Wie du sagst...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin ein Bürger dieser Stadt und ich bitte dich, deine Klinge niederzuhalten.","Hör zu, ich bin ein Bürger der Stadt und ich würde dich bitten, deine Klinge niederzuhalten.");
				link.l1 = LinkRandPhrase("Gut.","Wie auch immer dann.","Wie du sagst...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sei vorsichtig, Kumpel, wenn du mit einer Waffe herumläufst. Ich kann nervös werden...","Ich mag es nicht, wenn Männer mit gezogener Waffe vor mir herlaufen. Es ängstigt mich...");
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
