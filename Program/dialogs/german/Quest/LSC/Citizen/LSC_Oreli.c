// Орели Бертин - просто жительница
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
				dialog.text = "Guten Tag, Herr. Was werden Sie sagen?";
				link.l1 = TimeGreeting()+". Mein Name ist "+GetFullName(pchar)+", ich bin hier neu, also lerne ich die Einheimischen kennen.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Willst du etwas?";
				link.l1 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Gibt es Neuigkeiten auf der Insel?","Wirst du mir die neuesten Klatsch und Tratsch erzählen?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Ich möchte Ihnen einige Fragen zur Insel stellen.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Wollte nur wissen, wie es dir geht. Bis dann!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ich verstehe. Mein Name ist Orelie Bertine. Wie bist du hierher gekommen?";
			link.l1 = "Sagen wir einfach, ich wollte nur die mystische Insel der Gerechtigkeit sehen.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Also musst du einer von diesen Verrückten sein, die aus freiem Willen hierher kommen... Nun, jetzt wirst du genug Zeit haben, die Insel zu sehen und viel von ihrer 'Gerechtigkeit' zu kosten.";
			link.l1 = "Und gibt es laut deinem Sarkasmus Probleme mit der Gerechtigkeit?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Nein, alles ist in Ordnung. Aber aus irgendeinem Grund müssen wir Piraten für unser Essen bezahlen, das vor nicht allzu langer Zeit noch für alle kostenlos war. Und wenn die Clans auf unserem Teil der Insel zu kämpfen beginnen, sollen wir in den Schiffen sitzen, um nicht erschossen oder abgeschlachtet zu werden.\nIch meine, dass sie auf unserem Gebiet tun und lassen können, was sie wollen, aber wir können das Gleiche auf ihrem nicht tun. Aber es ist in Ordnung, keine weiteren Probleme...";
			link.l1 = "Ich verstehe. Gut, ich freue mich, dich zu treffen. Bis dann!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ich höre zu.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Bist du schon lange hier?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Gibt es etwas Interessantes auf der Insel?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Wie denkst du über Clans?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Stören Piraten Sie?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Keine Fragen. Entschuldigung...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Sehr lange schon. Ich habe den Überblick verloren. Es müssen siebzehn Jahre sein... nein, vielleicht achtzehn... oder sind es zwanzig? Was ist das aktuelle Jahr?";
			link.l1 = "Ich verstehe... Bist du also ein Alter Hase hier?";
			link.l1.go = "ansewer_1_1";
		break;
		
		case "ansewer_1_1":
			dialog.text = "Relativ. Ich erinnere mich noch an Zeiten, als Freibeuter mit uns handelten und die kühnsten und klügsten Narwale zum Festland segelten, um Proviant gegen Waren aus den Schiffsladeräumen zu tauschen. Aber es gibt viele Menschen, die nie andere Orte gesehen haben, sondern nur die Insel, weil sie hier geboren wurden. Sie sind hier nicht nur Alteingesessene, sondern Einheimische.";
			link.l1 = "Interessant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Ja, das ist es. Alles ist interessant hier. Lauf herum und sieh selbst. Schwimm um den zentralen Teil der Insel. Besuche eine Taverne, einen Laden und eine Kirche. Das Problem ist, dass das Interesse in einer Woche nachlassen wird, das kann ich dir versprechen.";
			link.l1 = "Hab's verstanden...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Und was sollen wir von diesen Banditen halten? Ich versuche, mich von ihnen fernzuhalten, das ist alles. Zumindest tun die Narwale der Insel der Gerechtigkeit etwas Gutes, sie haben sehr talentierte Handwerker unter ihnen, aber die Rivados sind nur Wilde und Heiden\nSie leben immer noch nach ihren afrikanischen Gesetzen wie vor hunderten von Jahren. Tiere. Das Einzige, was sie gelernt haben, ist der Umgang mit Schusswaffen. Man sagt, sie vollziehen Kannibalismusrituale!";
			link.l1 = "Was für ein Albtraum...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Der Teil, bei dem sie uns unser eigenes Essen verkaufen, stört ein wenig, aber sie tun den Bürgern keinen Schaden. Eigentlich im Gegenteil, sie haben die Clans in Ordnung gebracht und verhindern jegliche Gewalt\nEs gab einen Bürger, der Probleme machte und mit seinem Säbel winkte. Er verletzte sogar zwei andere Einheimische. Die Piraten brachten ihn für ein paar Wochen nach Tartarus. Jetzt ist der Mann ganz und friedlich. Wir sehen ihn nicht oft, der äußere Ring ist sein neues Zuhause...";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Was machst du da, ah? Dieb!","Schau dir das an! Kaum war ich in Gedanken versunken, hast du beschlossen, meine Truhe zu überprüfen!","Beschlossen, meine Truhen zu überprüfen? Damit kommst du nicht davon!");
			link.l1 = "Verdammt!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Was?! Hast du beschlossen, meine Truhen zu überprüfen? Das wirst du nicht ungestraft davonkommen!";
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
			dialog.text = LinkRandPhrase("Hör zu, du solltest besser deine Waffe weglegen. Es macht mich nervös.","Weißt du, hier wird nicht geduldet, mit gezückter Klinge herumzulaufen. Leg sie weg.","Hör zu, spiel nicht den mittelalterlichen Ritter, der mit einem Schwert herumläuft. Nimm es weg, es steht dir nicht...");
			link.l1 = LinkRandPhrase("Gut.","Gut.","Wie du sagst...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin Bürger dieser Stadt und ich bitte dich, dein Schwert niederzulegen.","Hör zu, ich bin Bürger der Stadt und ich würde dich bitten, deine Klinge niederzuhalten.");
				link.l1 = LinkRandPhrase("Gut.","Gut.","Wie du sagst...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sei vorsichtig, Kumpel, wenn du mit einer Waffe herumläufst. Ich kann nervös werden...","Ich mag es nicht, wenn Männer vor mir gehen und ihre Waffe bereithalten. Es macht mir Angst...");
				link.l1 = RandPhraseSimple("Habe es verstanden.","Ich nehme es weg.");
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
