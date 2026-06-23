// Альваро Гомец - капитан
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
				dialog.text = "Oh, ein neues Gesicht! Grüße. Und wann bist du hier angekommen? Ich erinnere mich nicht an ein kürzliches Schiffswrack.";
				link.l1 = TimeGreeting()+". Mein Name ist "+GetFullName(pchar)+". Und mein Schiff ist so leise und schnell gesunken, dass es niemand bemerkt hat. Und ich bin auch schnell und leise auf die Insel gekommen. Einfach so...";
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
				link.l5 = "Wollte nur wissen, wie es dir geht. Bis dann!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ich sehe, Oh, ich habe vergessen, mich vorzustellen. Entschuldigen Sie mich, senor. Mein Name ist Alvaro Gomez und ich war einmal Kapitän meiner eigenen Brigg. Eh, jetzt liegt meine schöne Brigg ganz unten direkt hinter dem äußeren Ring... Seitdem ist viel Wasser unter die Brücke geflossen. Ach, was auch immer. Freut mich, dich kennenzulernen!";
			link.l1 = "Freut mich auch, Sie kennenzulernen, Senor Gomez.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Gibt es Neuigkeiten auf der Insel?","Wirst du mir die neuesten Klatsch und Tratsch erzählen?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Ich möchte Ihnen ein paar Fragen zu der Insel stellen.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ich höre zu, Senor.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Du hast gesagt, dass du Kapitän warst. Wie bist du auf die Insel gekommen?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Was können Sie mir über das Leben auf der Insel erzählen?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Sag mal, leben die Einheimischen hier in Frieden oder nicht? Ich rede natürlich nicht von den Clans.";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Und woher bekommen die Einheimischen ihre Vorräte?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Keine Fragen. Entschuldigung...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Genau wie alle anderen auch. Der Sturm erwischte mich, ich verlor meinen Mast und die Steuerkontrolle. Wir wurden von der Strömung erfasst und auf die Riffe geworfen. Mein Schiff hat nicht einmal den äußeren Ring erreicht und wurde zerstört. Nur wenige Männer überlebten.";
			link.l1 = "Traurige Geschichte...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Was soll ich sagen? Wir haben alles, was wir zum Leben brauchen. Obwohl es hier manchmal wirklich langweilig wird. Und diese Melancholie... Das erste Jahr war das Schlimmste, aber später habe ich mich daran gewöhnt. Ich fühle mich schlecht für meine arme Frau Sabrina, sie muss sicher sein, dass ich gestorben bin. Ich hoffe, sie hat es geschafft, wieder zu heiraten\nSei nicht verärgert, du wirst dich daran gewöhnen. Besuche die Taverne, den Laden, die Kirche, triff andere Leute. Gehe nicht zu den Narwalen oder Rivados, bis du wirklich musst, sie sind knifflige Bastarde.";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Es ist wahr, Streit und Kämpfe sind hier heimlich verboten. Wenn du jemanden ohne einen richtigen Grund schlägst oder, Gott bewahre, tötest, dann wirst du isoliert. Du könntest sogar eines Nachts über Bord geworfen werden. Es gab schon einige Schläger auf der Insel. Der erste ist einfach verschwunden, der zweite starb in einer Zelle des Tartarus nach monatelangem Aufenthalt \Sicher, das bedeutet nicht, dass du dich nicht wehren kannst. Aber die Einheimischen sind eigentlich ziemlich friedlich. Abbott ist ein Angeber, aber nicht aggressiv. Kassel ist ein echtes Scheusal, aber er hält seine Hände sauber. Pratt ist ein ehemaliger Sträfling, aber er ist harmlos \nWir haben hier zwei ehemalige Marineoffiziere - Loderdale und Solderra. Sie sind hier gelandet, während sie nicht weit entfernt eine Schlacht hatten. Ironischerweise haben beide überlebt, um weiterhin blutrünstige Pläne gegeneinander zu schmieden.";
			link.l1 = "Habs verstanden...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Von den Laderäumen natürlich. Alle Vorräte, die von anderen Schiffen gesammelt wurden, wurden in St. Augustin gelagert und zwischen allen geteilt, bis die Piraten auftauchten. Jetzt haben sie die Insel in ihrer Faust, weil sie die Vorräte besitzen\nSicher, wir haben unsere eigenen Verstecke, also ist es in Ordnung. Wir schießen auch Vögel und fischen... Aber die beste Jagd endet mit dem Töten einer riesigen Krabbe. Sie haben ein sehr leckeres und nahrhaftes Fleisch. Obwohl sie nur am äußeren Ring zu sehen sind\nTauchen, um sie zu jagen, ist zu riskant. Es gab den einen, der mutig genug war, sie unter Wasser zu jagen. Eines Tages wurde er selbst zur Beute. Seitdem will niemand mehr dort Krabben jagen.";
			link.l1 = "Interessant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Was machst du da, ah? Dieb!","Nur schau dir das an! Kaum war ich in Gedanken versunken, hast du beschlossen, meine Truhe zu überprüfen!","Du hast also beschlossen, meine Truhen zu überprüfen? Das wirst du nicht ungestraft tun!");
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
			dialog.text = LinkRandPhrase("Hör zu, du solltest besser deine Waffe weglegen. Es macht mich nervös.","Weißt du, hier wird es nicht geduldet, mit einer Klinge zu laufen. Nimm es weg.","Hör zu, spiel nicht den mittelalterlichen Ritter, der mit einem Schwert herumläuft. Nimm es weg, es steht dir nicht...");
			link.l1 = LinkRandPhrase("Gut.","Sicher.","Wie du sagst...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin ein Bürger der Stadt und ich bitte dich, deine Klinge niederzuhalten.","Hör zu, ich bin ein Bürger der Stadt und ich würde dich bitten, dein Schwert niederzulegen.");
				link.l1 = LinkRandPhrase("Gut.","Wie auch immer.","Wie du willst...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sei vorsichtig, Kumpel, wenn du mit einer Waffe läufst. Ich kann nervös werden...","Ich mag es nicht, wenn Männer mit gezogener Waffe vor mir herlaufen. Es ängstigt mich...");
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
