// Лайонел Маскетт - мещанин
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
				dialog.text = "Grüß dich, "+GetAddress_Form(NPChar)+"Bist du ein Neuling hier?";
				link.l1 = TimeGreeting()+". Mein Name ist "+GetFullName(pchar)+". Ja, das bin ich.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Willst du etwas?";
				link.l1 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Gibt es Neuigkeiten auf der Insel?","Wirst du mir die letzten Klatschereien erzählen?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Ich möchte Ihnen ein paar Fragen über die Insel stellen.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Wollte nur wissen, wie es dir geht. Wir sehen uns!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Mein Name ist Lionell. Schön, dich zu treffen. Wie bist du hierher gekommen?";
			link.l1 = "Auf einer Bark... Ich hörte, dass es eine Schmugglerbasis gibt und beschloss, sie zu erkunden... Erkundet. Die Bark ist gesunken und ich bin hier.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Betrachten sie die Insel wirklich als Schmugglerbasis?";
			link.l1 = "Nun, offiziell nicht. Die Mehrheit glaubt nicht einmal an deine Existenz.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Ernsthaft... Und warum sollten sie das tun? Wir existieren eigentlich gar nicht. Man kann diesen Ort nicht verlassen. Obwohl sie sagen, es hätte eine Verbindung nach Kuba gegeben... Aber ich erinnere mich nicht daran und ich lebe seit fast acht Jahren hier.";
			link.l1 = "Ich verstehe. Es war mir eine Freude, mit dir zu sprechen. Bis dann!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Gibt es Neuigkeiten auf der Insel?","Wirst du mir die neuesten Klatsch und Tratsch erzählen?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Ich möchte Ihnen ein paar Fragen über die Insel stellen.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ich höre zu.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Wie bist du hierher gekommen?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Möchten Sie zum Festland zurückkehren?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Und was machen die Leute hier, auf der Insel der Gerechtigkeit?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Und woher bekommt ihr all die Sachen hier? Essen, Kleidung, Getränke?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Keine Fragen. Entschuldigung...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Das ist eine seltsame Geschichte. Diese Insel ist der einzige Ort, den ich in der gesamten Karibik gesehen habe. Als es mir schlecht ging, segelte ich auf einem Handelsschiff aus dem alten England. Ich wollte in Belize einen Job finden, ein Hafenbüroangestellter werden. Aber wir haben es nie nach Belize geschafft\nIch bin kein Seemann, also kenne ich die Details nicht. Ein Sturm kam auf und am nächsten Tag wurde unser Schiff von Riffen zerstört. Ich werde diesen schrecklichen Aufprall, das Schreien, nie vergessen\nJemand schrie, dass es ein Loch im Rumpf gab, die Leute begannen, von Bord zu springen. Ich... ich kann nicht schwimmen. Also blieb ich. Ironischerweise hat das mein Leben gerettet. Das Schiff überlebte und der Sturm beruhigte sich bei Tagesanbruch\nIch traf die einzige richtige Entscheidung, bevor ich das Schiff verließ. Ich nahm etwas Essen, baute ein Floß und segelte durch ein ruhiges Meer zum äußeren Ring. So habe ich überlebt, als einziger der gesamten Besatzung.";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Es war mein einziger Traum in den ersten zwei Jahren hier. Aber jetzt... Was macht die Insel schlimmer als jeden anderen Ort auf der Welt? Ja, es gibt keine grünen Felder mit Schafen, aber es gibt ein herrliches Meer und einen Nachthimmel voller schöner Sterne. Ich bin gut ernährt, ich trage anständige Kleidung, die ich mir in England nicht leisten konnte. Ich habe viele Freunde\n Nein, mein Herr, ich möchte diesen Ort nicht verlassen. Was erwartet mich da draußen? Ein Schreibtischjob unter einem lärmenden Chef für dreihundert Pesos pro Woche? Auf keinen Fall! Ich habe hier alles gefunden, was ich gesucht habe, ich brauche nichts anderes.";
			link.l1 = "Verstanden. Freut mich für dich!";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Was sie am meisten mögen. Clans spielen im Krieg, Piraten verkaufen Vorräte, Axel Yost kauft und verkauft Dinge, Sancho Carpentero serviert Getränke und unterhält die Leute, Bruder Julian betet, hält die Messe und verkauft Medikamente. Loderdale und Solderra intrigieren gegeneinander, Abt mag es, aufgeblasen zu sein, Jillian und Tanneke träumen von wahrer Liebe...";
			link.l1 = "Interessant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Von den Schiffen, mein Freund, von den Schiffen. Die Lieblingsbeschäftigung der meisten ist es, Schiffe aus dem äußeren Ring zu erkunden und Sachen von ihnen zu bekommen. Dort kann man alles finden, Waffen, Medikamente, Gewürze und Rum. Viele Schiffe sind noch unerforscht. Die Meeresströmung bringt oft hier ein weiteres Opfer...";
			link.l1 = "Interessant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Was machst du da, ah? Dieb!","Schau nur! Kaum war ich in Gedanken versunken, hast du dich entschieden, meine Truhe zu überprüfen!","Hast du beschlossen, meine Truhen zu überprüfen? Damit wirst du nicht davonkommen!");
			link.l1 = "Verdammt!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Was?! Hast du beschlossen, meine Truhen zu überprüfen? Das wirst du nicht ungestraft davonkommen!";
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
			dialog.text = LinkRandPhrase("Hör zu, du solltest besser deine Waffe weglegen. Es macht mich nervös.","Du weißt, hier wird nicht geduldet, mit einer Klinge zu rennen. Nimm sie weg.","Hör zu, spiel nicht den mittelalterlichen Ritter, der mit einem Schwert herumläuft. Leg es weg, es steht dir nicht...");
			link.l1 = LinkRandPhrase("Gut.","In Ordnung.","Wie du sagst...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin Bürger der Stadt und ich würde dich bitten, deine Klinge niederzuhalten.","Hör zu, ich bin ein Bürger der Stadt und ich bitte dich, deine Klinge niederzulegen.");
				link.l1 = LinkRandPhrase("Gut.","In Ordnung.","Wie du sagst...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sei vorsichtig, Kumpel, beim Laufen mit einer Waffe. Ich kann nervös werden...","Ich mag es nicht, wenn Männer mit gezogener Waffe vor mir herlaufen. Es macht mir Angst...");
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
