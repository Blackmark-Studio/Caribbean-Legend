// Оеларт Котеел - канонир
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
				dialog.text = "Guten Tag, mein Herr! Gefällt Ihnen das Wetter?";
				link.l1 = TimeGreeting()+". Mir macht jedes Wetter nichts aus, außer Stürmen auf offenem Meer...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Willst du etwas?";
				link.l1 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Ist auf der Insel etwas Neues passiert?","Wirst du mir die letzten Klatschgeschichten erzählen?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Ich möchte Ihnen ein paar Fragen über die Insel stellen.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Wollte nur wissen, wie es dir geht. Bis dann!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Vertrau mir, ich fühle das Gleiche. Ich habe dich noch nie zuvor gesehen... mein Name ist Oelart Koteel und ich war ein Kanonenmeister auf dem holländischen Kriegsschiff.";
			link.l1 = ""+GetFullName(pchar)+". Ja, ich bin ein Neuling hier. Tatsächlich bin ich gerade erst angekommen.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Ich bin auch ein Neuling, ich bin seit weniger als einem Jahr hier. Und ich hoffe wirklich, dass ich nicht zu lange hier bleiben muss, obwohl jeder versucht, mich vom Gegenteil zu überzeugen. Schön, dich zu treffen!";
			link.l1 = "Auch nett, dich zu treffen, "+npchar.name+"...";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Ist auf der Insel etwas Neues passiert?","Wirst du mir die letzten Klatsch und Tratsch erzählen?");
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
				link.l2 = "Wollen Sie die Insel der Gerechtigkeit verlassen?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Haben Sie jemals darüber nachgedacht, wie die Insel entstanden ist?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Waren Sie schon einmal auf den Schiffen des Clans?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Keine Fragen. Entschuldigung...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Ziemlich banal. Wir haben gegen eine englische Schoner gekämpft und hätten fast gewonnen. Sie sind geflohen, also haben wir sie verfolgt. Ein Tag verging, wir waren kurz davor, sie zu fangen, aber sie haben unseren Hauptmast abgeschossen und sind natürlich entkommen. Was uns betrifft, wir wären fast von einem starken Sturm versenkt worden, dann wurden wir von einer Strömung getrieben und am Ende wurde unser Schiff auf ein Riff in der Nähe des äußeren Rings geworfen. Nur sehr wenige haben überlebt...";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Das ist mein Traum. Du kannst dir nicht vorstellen, wie sehr ich diesen Ort satt habe. Aber wie kann ich ihn verlassen? Ich habe keine Ahnung. Hier gibt es keine Schiffe und es gibt keine Möglichkeit, ein neues zu bauen. Es wäre Selbstmord, in einem kleinen Boot zu segeln.";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Nach den Schiffen zu urteilen, ist es etwa hundert Jahre alt. Aber es könnte älter sein, wegen des äußeren Rings. Er besteht von oben bis unten aus Schiffen, vielleicht liegen die älteren Schiffe tief unter Wasser\nWas die Entstehung der Insel betrifft... Ich glaube, dass Strömungen und Stürme sterbende Schiffe hierher gebracht haben, so dass das künstliche Riff entstanden ist. Der äußere Ring wurde darauf gebaut\nDie inneren Schiffe, auf denen wir leben... entweder waren sie die allerersten oder sie haben es irgendwie geschafft, durch den äußeren Ring zu kommen. Es ist durchaus möglich, schließlich sind der Admiral und seine Piraten mit ihrer Brigg zu uns gekommen.";
			link.l1 = "Interessant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Ich habe Rivados besucht. Black Eddy brauchte einmal eine Beratung über Schiffskanonen und ich habe keine Ahnung warum. Also hat einer der schwarzen Kerle mich gefunden und mir das Passwort gegeben. Ich habe ihren 'Beschützer' und 'Velasco' besucht. Die Wachen sind hart, also versuche nicht, sie ohne Passwort zu umgehen.";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Was machst du da, ah? Dieb!","Schau dir das an! Kaum war ich in Gedanken versunken, hast du dich entschlossen, meine Truhe zu überprüfen!","Habt Ihr beschlossen, meine Kisten zu überprüfen? Das werdet Ihr nicht ungestraft tun!");
			link.l1 = "Scheiße!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Was?! Hast du vor, meine Kisten zu durchsuchen? Das wirst du nicht ungestraft davonkommen!";
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
			dialog.text = LinkRandPhrase("Hör zu, du solltest besser deine Waffe weglegen. Das macht mich nervös.","Weißt du, hier wird es nicht toleriert, mit der Klinge herumzulaufen. Nimm sie weg.","Hör zu, spiel nicht den mittelalterlichen Ritter, der mit einem Schwert herumläuft. Nimm es weg, es steht dir nicht...");
			link.l1 = LinkRandPhrase("Gut.","In Ordnung.","Wie du meinst...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin Bürger der Stadt und ich bitte dich, dein Schwert niederzulegen.","Hör zu, ich bin Bürger der Stadt und ich bitte dich, deine Klinge niederzulegen.");
				link.l1 = LinkRandPhrase("Gut.","In Ordnung.","Wie du sagst...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sei vorsichtig, Kumpel, beim Laufen mit einer Waffe. Ich kann nervös werden...","Ich mag es nicht, wenn Männer mit gezogener Waffe vor mir herlaufen. Es erschreckt mich...");
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
