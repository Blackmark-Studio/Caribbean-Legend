// Виктор Кассель - бандит
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
				dialog.text = "Hm... Was willst du, Kumpel? Wenn du reden willst, muss ich dich enttäuschen. Ich habe keine Lust zu reden.";
				link.l1 = "Schade... Ich wollte reden. Ich bin ein Neuankömmling hier und lerne gerade die Leute kennen...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! Was willst du?";
				link.l1 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Gibt es Neuigkeiten auf der Insel?","Wirst du mir die letzten Klatsch und Tratsch erzählen?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Ich möchte Ihnen ein paar Fragen zur Insel stellen.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Wollte nur wissen, wie es dir geht. Bis dann!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ein Neuling? Hm. Gut denn. Ich bin Victor Cassel und du solltest besser vermeiden, mich zu ärgern, während ich schlecht gelaunt bin. Und auch wenn ich gut gelaunt bin. Ich verschwende keine Zeit mit Plaudereien, ich schlage Leute sofort, wenn sie zu aufdringlich sind. ";
			link.l1 = "Nun und ich bin "+GetFullName(pchar)+". Übrigens, ich kann leicht zurückschlagen. Aber ich hoffe, dass es keinen Grund dazu geben wird. Ich werde dich nicht stören, wenn du so ungesellig bist. Tschüss.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Ist auf der Insel etwas Neues passiert?","Wirst du mir die neuesten Klatsch und Tratsch erzählen?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Ich möchte Ihnen ein paar Fragen über die Insel stellen.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ja? Und was kann ich dir erzählen?";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Wie bist du hierher gekommen?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Wie sieht das Leben hier aus?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Wer ist die wichtigste... Person hier?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Und wo kann ich auf der Insel Münzen bekommen?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Keine Fragen. Entschuldigung...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Es tut mir leid, Freund, aber was beunruhigt dich? Ich bin einfach hierher gekommen. Ich möchte nicht über diese Geschichte sprechen, besonders mit einem Mann, den ich nicht kenne.";
			link.l1 = "Nun, es tut mir Leid...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Es sieht aus wie eine langweilige Sache. Mühsam, trist und sinnlos. Ich werde mich den Hai-Piraten anschließen, diese Burschen sind es wert. Ich werde mit großer Freude der Crew beitreten, ich muss nur noch ein bisschen... erkunden. Ich bin sicher, dass sie einen Weg von der Insel der Gerechtigkeit finden werden.";
			link.l1 = "Wirklich? Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Sicher ein Admiral! Piraten halten Narwale und Rivados in seiner Faust und die Clans wagen es nicht, etwas zu sagen. Als nächstes kommen die Clanführer, Donald Greenspy von Narwale und Black Eddy von Rivados. Axel Yost - ein Kaufmann der Narwale ist auch ein wichtiger Mann. Und natürlich Sancho Carpentero, er ist ein guter Junge...";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Truhen. Natürlich musst du sie zuerst öffnen, die Leute vertrauen einander hier nicht, also bekommen alle Truhen Schlösser. Lass mich dir eines sagen, Kumpel, die besten Kleinode werden unter der Aufsicht ihrer Besitzer in den Schiffen aufbewahrt.\nDu kannst auch den äußeren Ring erkunden, aber bete, dass du nicht durch das morsche Holz fällst. Oder du kannst riesige Krabben jagen, für das Fleisch an ihren Scheren kannst du einen guten Preis bekommen.";
			link.l1 = "Hab's verstanden...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Was machst du da, ah? Dieb!","Schau dir das an! Kaum war ich in Gedanken versunken, hast du beschlossen, meine Truhe zu überprüfen!","Hast du beschlossen, meine Truhen zu überprüfen? Das wirst du nicht ungestraft tun!");
			link.l1 = "Scheiße!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Was?! Hast du beschlossen, meine Truhen zu überprüfen? Du kommst nicht ungestraft davon!";
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
			dialog.text = LinkRandPhrase("Hör zu, du solltest besser deine Waffe weglegen. Es macht mich nervös.","Du weißt, hier wird nicht geduldet, mit einer Klinge herumzulaufen. Nimm sie weg.","Hör zu, spiel nicht den mittelalterlichen Ritter, der mit einem Schwert herumläuft. Leg es weg, es steht dir nicht...");
			link.l1 = LinkRandPhrase("Gut.","Gut.","Wie du sagst...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin ein Bürger der Stadt und ich würde dich bitten, deine Klinge niederzuhalten.","Hör zu, ich bin ein Bürger der Stadt und ich würde dich bitten, dein Schwert niederzuhalten.");
				link.l1 = LinkRandPhrase("Gut.","Gut.","Wie du sagst...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sei vorsichtig, Kumpel, beim Laufen mit einer Waffe. Ich kann nervös werden...","Ich mag es nicht, wenn Männer mit gezückter Waffe vor mir herlaufen. Das macht mir Angst...");
				link.l1 = RandPhraseSimple("Habe es.","Ich nehme es weg.");
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
