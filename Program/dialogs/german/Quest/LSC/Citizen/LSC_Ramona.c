// Рамона Лоцано - горячая испанская сеньорита
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
				dialog.text = "Hallo, hallo! Neuling? Oder hast du dich in Frachträumen versteckt, da ich dein Gesicht zum ersten Mal hier sehe?";
				link.l1 = TimeGreeting()+". Sich in Frachträumen zu verstecken ist nicht mein Ding. Ich bevorzuge den Platz des Kapitäns... Ja, ich bin ein Neuling hier.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+pchar.name+"! "+TimeGreeting()+"! Ich freue mich, dich zu sehen! Was sagst du";
				link.l1 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Ist auf der Insel etwas Neues passiert?","Wirst du mir die neuesten Klatsch und Tratsch erzählen?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Ich möchte Ihnen ein paar Fragen über die Insel stellen.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Wollte nur wissen, wie es dir geht. Bis später!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Nun, lass uns uns dann kennenlernen... Kapitän. Ich bin Ramona Lozano, aber versuch nicht einmal, mich Senora Lozano zu nennen, ich hasse es. Wie ist dein Name?";
			link.l1 = ""+GetFullName(pchar)+". Freut mich, dich kennenzulernen, Ramona.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Bist du wirklich erfreut oder einfach nur höflich, "+GetFullName(pchar)+"? Sag mal, bist du wirklich ein Kapitän oder hast du nur gescherzt?";
			link.l1 = "Oho, so viele Fragen auf einmal! Darf ich sie der Reihe nach beantworten? Erstens, ich freue mich wirklich, ich treffe nicht jeden Tag hübsche Mädchen, zweitens, ich bin Kapitän, das stimmt. Aber mein Schiff ist jetzt in der Nähe der Küsten von Western Main...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Lustig! Und wie kommt das, Kapitän? Sie sind hier, aber Ihr Schiff ist nahe der Küsten von Main. Haben Sie keine Angst, dass Ihre Mannschaft sich zerstreut und Ihr Schiff Ihnen weggenommen wird?";
			link.l1 = "Ich bin hier auf einer Barke zum... Erkunden gesegelt, aber alles ging schief und ich habe mich auf eurer Insel wiedergefunden. Dann haben wir im Dunkeln auf einige Trümmer gestoßen, gekentert und voila! Hier bin ich. Mein Schiff wird so lange auf mich warten, wie ich möchte. Dannie Hawk wird in der Lage sein, meine Männer zu kontrollieren.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Dannie Hawk? Die Danielle Hawk? Willst du sagen, dass du mit ihr schwebst?";
			link.l1 = "Scheiße schwimmt, Dannie dient mir als mein Offizier. Sie wurde zurückgelassen, um zu kommandieren, während ich fehle... Wie kennst du sie?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Ha! Jeder in den spanischen Kolonien kennt die Piratin Danielle Hawk und ihren Ehemann, Nathaniel. Ja, Sie, Senor "+GetFullName(pchar)+", muss ein harter Kerl sein... Bist du dann ein Pirat? Mach dir keine Sorgen, ich komme mit deiner Art gut zurecht. Ich mag harte Kerle.";
			link.l1 = "Nun, ich bin eigentlich kein Pirat... Ich arbeite gerade mit Jan Svenson und suche nach Dannie's Ehemann, Nathaniel.";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Und wollen Sie mir jetzt erzählen, dass Sie kein Pirat sind? Sie arbeiten für den Waldteufel, Ihr erster Offizier ist Dannie Hawk und Sie suchen nach Nathan Hawk... und ich bin mir sicher, dass Sie wegen des Admirals hierher gekommen sind. Richtig?";
			link.l1 = "Ramona, du kannst mich Pirat nennen, wenn du willst, das ist mir egal. Du darfst mich sogar einen Anker nennen, wirf mich nur nicht ins Wasser...";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "Es scheint, dass du einer der wirklich ernsten Kerle bist, "+pchar.name+". Gut, ich muss gehen. Bis später! Ich habe das Gefühl, dass wir Freunde sein könnten... sehr enge Freunde.";
			link.l1 = "Warum nicht? Viel Glück!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ach wirklich? Nun, frag, ich werde antworten, wenn ich kann...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Wie bist du hierher gekommen?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Sicherlich hast du noch nie versucht, von hier wegzukommen...";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Wie lebt ihr hier?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Was machst du hier? Ich nehme an, das Essen ist nicht umsonst, oder?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Keine Fragen. Entschuldigung...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Das ist eine lange Geschichte... Mein Stiefvater ist der Schuldige. Vor vier Jahren lebte ich in Havanna und konnte mir nicht vorstellen, wie es für mich enden würde. Meine Mutter starb und ich war der gesetzliche Erbe. Wir waren nicht reich, aber wir hatten genug Geld, mehr als genug für ein anständiges Leben. Meinem Stiefvater gefiel das nicht und er beschloss, mich loszuwerden\nNatürlich fand ich das erst heraus, nachdem mich zwei bezahlte Schläger direkt hinter dem Stadttor angegriffen hatten. Diese Narren sagten mir selbst, wer sie beauftragt hatte, mich zu töten und warum. Glücklicherweise waren sie keine Profis, sonst hätte ich mit durchgeschnittener Kehle im Gebüsch gelegen. Die Idioten beschlossen, sich zunächst ein wenig zu amüsieren\nDas Schicksal hat mich an diesem Tag gerettet, ein Kapitän wie du war auf dem Weg zum Tor. Er sah die Show und tötete den Abschaum sofort. Sie hatten keine Chance. Ich erzählte ihm, was mir passiert war und warum. Weinte ein bisschen... Er wusste, dass ich nirgendwo hingehen konnte, also nahm er mich auf sein Schiff. Zuerst nur vorübergehend, und dann\nIch glaube, ich wäre bei ihm geblieben, aber zwei Monate später kämpfte er gegen eine Patrouille, verlor einen Mast, wurde von einem starken Sturm erfasst und fand Frieden auf dem Grund des äußeren Rings. Trotz allem überlebte ich und schloss mich der Gemeinschaft der Insel an.";
			link.l1 = "Traurige Geschichte, ich habe nichts zu sagen...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Natürlich nicht. Weil es unmöglich ist. Ich sah einen Mann, der versuchte, diesen Ort auf einem Langboot zu verlassen... er kehrte zwei Tage später zurück. Gebunden an ein Wrack eines Mastes, um sich vor dem Ertrinken zu retten. Er war blau und absolut tot\nAlso sag mir, "+pchar.name+", was soll ich tun, sobald ich von hier wegkomme? Havanna ist zu gefährlich für mich, der Stiefvater wird versuchen, mich wieder zu töten. Ich habe kein Haus, kein Geld. Wohin soll ich gehen? Zum Bordell?";
			link.l1 = "Trotzdem, willst du zurück zum Archipel?";
			link.l1.go = "ansewer_2_1";
		break;
		
		case "ansewer_2_1":
			dialog.text = "Und was denkst du? Sicher, ich will. Aber es ist unmöglich und ich habe dir gerade erzählt, warum. Eh, wenn nur jemand mit meinem Stiefvater fertig werden könnte... mit scharfem Stahl oder einer Kugel, dann hätte ich vielleicht eine Chance, in das normale Leben zurückzukehren. Aber wer würde sich das trauen, wenn mein Stiefvater der beste Freund des Alcalde von Havanna ist? Und warum sprechen wir darüber? Es gibt keinen Ausweg von hier...";
			link.l1 = "Wir werden sehen. Die Zeit wird kommen...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			// сюда направление на квест
		break;
		
		case "ansewer_3":
			dialog.text = "Ich lebe irgendwie. Es gibt keine andere Möglichkeit. Meine Freunde sind hauptsächlich die Männer, weil zwei unserer heiratsfähigen Schönheiten - Gillian und Tanneke mich wegen meines Charakters nicht mögen und ich krank werde von ihrer zur Schau gestellten Anständigkeit. Natalie war ein feines Mädchen, bis sie begonnen hat, viel Zeit mit diesen Idioten zu verbringen, Dummheit ist ansteckend.";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Ich arbeite wie andere Mädchen. Unsere Hauptaufgabe ist es, den Männern zu helfen. Es gibt viel Arbeit für Frauen auf der Insel, daher bin ich ziemlich beschäftigt. Und ich bekomme oft Geschenke, das ist hier üblich. Aber denke nicht schlecht von mir, ich bin keine Dirne. Ich wurde in einer anständigen Familie gut erzogen. Ich spiele nur nicht die Heilige, wie es manche tun.";
			link.l1 = "Ich dachte nichts Schlechtes über dich...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Was machst du da, ah? Dieb!","Schau dir das an! Kaum war ich in Gedanken versunken, hast du dich entschieden, meine Truhe zu überprüfen!","Hast du vor meine Truhen zu durchsuchen? Das wirst du nicht ungestraft tun!");
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
			dialog.text = LinkRandPhrase("Hör zu, du solltest besser deine Waffe weglegen. Es macht mich nervös.","Weißt du, hier wird nicht geduldet, dass man mit einer Klinge herumläuft. Nimm sie weg.","Hör zu, spiel keinen mittelalterlichen Ritter, der mit einem Schwert herumläuft. Leg es weg, es steht dir nicht...");
			link.l1 = LinkRandPhrase("Gut.","Sicher.","Wie du meinst...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin ein Bürger der Stadt und ich würde dich bitten, dein Schwert niederzuhalten.","Hör zu, ich bin Bürger dieser Stadt und ich bitte dich, deine Klinge niederzuhalten.");
				link.l1 = LinkRandPhrase("Gut.","Sicher.","Wie du sagst...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sei vorsichtig, Kumpel, beim Laufen mit einer Waffe. Ich kann nervös werden...","Ich mag es nicht, wenn Männer mit gezogener Waffe vor mir herlaufen. Es macht mir Angst...");
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
