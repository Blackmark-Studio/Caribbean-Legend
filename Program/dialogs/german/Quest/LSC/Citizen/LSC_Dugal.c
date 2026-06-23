// Дугал Эббот - дворянин
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
				dialog.text = "Grüß dich, Herr. Lassen Sie mich mich vorstellen - Dougall Abbot. Es ist gut, hier einen ehrenwerten Mann zu sehen. Ich bin müde von den örtlichen Bauern. Ich hätte mir nie vorstellen können, dass ich den Rest meines Lebens unter gewöhnlichen Leuten verbringen muss.";
				link.l1 = TimeGreeting()+". Mein Name ist "+GetFullName(pchar)+". Es ist gut, dich zu treffen. Und warum magst du die Einheimischen nicht?";
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
			dialog.text = "Du kennst sie nicht gut. Bist du gerade hier angekommen? Ich erinnere mich allerdings an kein kürzliches Schiffswrack...";
			link.l1 = "Ich kam hier auf einer kleinen Bark an...";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Ja, es passiert oft - Schiffe sinken und nur einige Überlebende kommen mit ihren Rettungsbooten hierher. Manchmal leben Leute monatelang hier und man trifft sie nie.";
			link.l1 = "Ich verstehe. Es war gut, Sie kennenzulernen, Herr Abt. Auf Wiedersehen!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Gibt es Neuigkeiten auf der Insel?","Wirst du mir die neuesten Klatsch und Tratsch erzählen?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Ich möchte Ihnen ein paar Fragen zur Insel stellen.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ich höre zu.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Und wie bist du hierher gekommen?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Was können Sie mir über die Einheimischen erzählen?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Was kannst du mir über Clans erzählen?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Und wie steht's mit dem Wetter? Gibt es hier oft Stürme?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Keine Fragen. Entschuldigung...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Es war vor fünf Jahren, aber ich erinnere mich perfekt, als ob es gestern war. An einem unglücklichen Tag hatte ich beschlossen, mit meiner Flöte von Port Royal nach Belize zu segeln, die Ladung war zu wertvoll, um anderen den Handel zu überlassen\nAm nächsten Tag begannen meine Missgeschicke, erst wurde unser Bootsmann betrunken und fiel über Bord, dann wären wir fast auf die Riffe aufgelaufen und am Ende machte unser Navigator einen Fehler, so dass wir in die falsche Richtung segelten\nDann wurden wir von einer Brigg und einer Galeone verfolgt. Wir versuchten zu flüchten, aber sie waren hartnäckig. Die Galeone blieb zurück, aber die Brigg hatte uns schließlich eingeholt\nDie Galeone war zu weit weg, also enterten wir die Brigg ohne zu schießen. Diese spanischen Hunde rechneten nicht damit und wir gewannen, aber die meisten meiner Crew waren tot\nEinige Stunden später erwischte uns ein Sturm, wir konnten das Wetter mit so wenig Besatzung nicht bekämpfen und jetzt sehen Sie das Ergebnis. Meine Flöte ist irgendwo am äußeren Ring, ich und die anderen drei Überlebenden haben es hierher geschafft.";
			link.l1 = "Habs verstanden...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Abschaum. Alle von ihnen. Niedrigste Lebensformen aller Art. Richard Shambon ist ein Verbrecher, es steht einfach auf seinem Gesicht geschrieben. Kassel? Für ihn ist das Töten von Menschen so natürlich wie das Atmen. Jasper Pratt ist ein Sträfling. Musket ist ein Säufer. Soll ich noch weitermachen?\nJosef Loderdale ist der einzige anständige Mensch hier, außer dir, er ist ein ehemaliger Militär der englischen Marine. Es gibt hier zwei Adlige - Antonio Betancourt und Lorenzo Solderra, verdammter spanischer Abschaum, ich werde nicht einmal mit ihm am selben Tisch sitzen.";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Eine Bande von Bastarden und Abschaum. Sie tun uns jedoch keinen Schaden. Sie sind mehr daran interessiert, sich gegenseitig zu erstechen und zu erschießen. Sie können ohne es nicht leben. Ich mag Piraten auch nicht, aber ich muss zugeben, dass sie die Insel friedlicher gemacht haben, als sie hier ankamen.";
			link.l1 = "Interessant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Sie tun es nie. Stürme passieren oft um die Insel herum, aber dieser Ort ist immer ruhig und still, vielleicht ist es eine Art Magie oder Gottes Wille, ich weiß es nicht. Ein starker Wind kann manchmal diesen Ort erreichen und das war's. Regen kann auch keinen Schaden anrichten.";
			link.l1 = "Interessant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Was machst du da, ah? Dieb!","Schau dir das an! Kaum habe ich mich in Gedanken verloren, hast du beschlossen, meine Truhe zu überprüfen!","Du hast also beschlossen, meine Truhen zu überprüfen? Das wirst du nicht ungestraft davonkommen!");
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
			dialog.text = LinkRandPhrase("Hör zu, du solltest besser deine Waffe weglegen. Es macht mich nervös.","Weißt du, hier ist es nicht erlaubt, mit einer Klinge herumzulaufen. Nimm sie weg.","Hör zu, spiel nicht den mittelalterlichen Ritter, der mit einem Schwert herumläuft. Leg es weg, es steht dir nicht...");
			link.l1 = LinkRandPhrase("Gut.","Gut.","Wie du sagst...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin ein Bürger der Stadt und ich bitte dich, dein Schwert niederzulegen.","Hör zu, ich bin ein Bürger der Stadt und ich bitte dich, dein Schwert niederzulegen.");
				link.l1 = LinkRandPhrase("Gut.","Wie auch immer dann.","Wie du sagst...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sei vorsichtig, Kumpel, beim Laufen mit einer Waffe. Ich kann nervös werden...","Ich mag es nicht, wenn Männer mit gezogener Waffe vor mir herlaufen. Das macht mir Angst...");
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
