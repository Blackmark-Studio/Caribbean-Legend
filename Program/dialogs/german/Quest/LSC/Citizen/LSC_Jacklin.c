// Жаклин Тьюрам - торговый капитан
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
				dialog.text = "Guten Tag, Monsieur. Sie sind neu hier, nicht wahr?";
				link.l1 = TimeGreeting()+". Ja, ich vermute, dass ich der Neueste hier bin. Mein Name ist "+GetFullName(pchar)+". Und was ist deins?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Willst du etwas?";
				link.l1 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Gibt es etwas Neues auf der Insel?","Wirst du mir die letzten Klatschgeschichten erzählen?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Ich möchte Ihnen ein paar Fragen über die Insel stellen.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Wollte nur wissen, wie es dir geht. Bis dann!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Jacqueline Turam. Vor zwei Jahren war ich ein anständiger und wohlhabender Händler, Besitzer und Kapitän meiner eigenen Flöte. Ach, jetzt bin ich so arm wie eine Kirchenmaus und ich kann nicht hoffen, dass sich meine Situation irgendwie ändert\nManche haben hier Glück - sie finden Juwelen, Gold, Schiffe voller Schätze, aber ich bin nicht einer von ihnen. Ich fand nur eine Kiste mit Dublonen und ein paar Kleinigkeiten\nZumindest reicht das, um Essen zu kaufen, damit ich nicht verhungere... Es freut mich, Sie kennenzulernen, mein Herr, ich habe nichts gegen ein Gespräch...";
			link.l1 = "Ich freue mich auch, dich zu treffen, Jacqueline. Wir sehen uns!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Ist auf der Insel etwas Neues passiert?","Wirst du mir die neuesten Gerüchte erzählen?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Ich möchte Ihnen ein paar Fragen über die Insel stellen.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ich bin ganz Ohr.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Wie bist du hierher gekommen?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Was machst du hier?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Sag mir, ich sehe, dass es Mädchen und Frauen auf der Insel gibt...";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Möchten Sie zurück in die große Welt?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Es ist nichts.";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Möchtest du meine Geschichte hören? Gut. Wie du bereits weißt, war ich ein Handelskapitän. Eines Tages segelte ich auf meiner guten alten Flöte von Tortuga nach Belize. Meine Laderäume waren gefüllt mit Schwarzholz und Kakao, ich hatte all meine Münzen für die Fracht ausgegeben\nIch hatte einen sehr lukrativen Deal mit einem Mann arrangiert, der meine Fracht zu einem extrem hohen Preis kaufen wollte. Ich könnte ein Vermögen mit diesem Deal machen. Alles lief gut, keine einzige Wolke am Himmel, mein Schiff war so schnell wie ein Vogel. Wir erwarteten keine Schwierigkeiten\nIch segelte in der Nähe von Kuba, hielt mich von spanischen Patrouillen fern, aber plötzlich wurden wir von einer Piratengaleone angegriffen. Was machten sie dort - mitten im spanischen Territorium? Wir versuchten zu fliehen, aber wir scheiterten, die Galeone war überraschend schnell\nDie Piraten jagten uns und griffen an. Ihre Kulevrinen waren mit Traubenschrot geladen, die erste Salve verletzte meine Crew schwer und demoralisierte sie. Ich wollte ihnen einen guten Kampf liefern, aber meine eigenen Crewmitglieder und Offiziere hielten mich davon ab. Wir kapitulierten\nDie Piraten nahmen schnell unsere Fracht und warfen unsere Kanonen weg. Ich dachte, es wäre das Ende. Den Verlust der Fracht war ein schwerer Schlag, aber ich konnte immer noch Geld mit Frachten verdienen und eines Tages wieder auf die Beine kommen\nAber es stellte sich anders heraus. Die verdammten Piraten eröffneten das Feuer auf meine wehrlose Flöte. Wir waren ein perfektes Schießziel\nIch kann mich noch daran erinnern, wie sie lachten... Die Galeone segelte davon und wir ruderten, hielten die Wracks fest. Dann kam ein starker Sturm mit Wellen und ich habe seitdem nie wieder jemanden von meiner Crew gesehen. Ich schaffte es, mich an einen Mastteil zu binden und über Wasser zu bleiben\nIch erspare dir weitere Details über den Haiangriff. Nach einiger ewiger Zeit wurde ich von einer Meeresströmung hierher gebracht. So habe ich überlebt.";
			link.l1 = "Ja, es ist wirklich eine traurige Geschichte.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Ich lebe wie der Rest der Einheimischen - ich lebe einfach. Ich suche Wertsachen am äußeren Ring und tausche sie gegen Essen ein. Ich träume davon, eine mit Schätzen gefüllte Truhe eines indischen Königs zu finden... Oder zumindest eine Galeone mit spanischem Gold, he-he. Beachten Sie nicht zu viel, das bin nur ich\nIch träume davon, etwas anderes zu essen als Corned Beef und Fisch. Ach, es gab hier einen Mann, der diese riesigen Krabben jagte. Ich habe fünf Dublonen für eine Klaue bezahlt und mich damit mehrere Tage lang ernährt\nSchade, dass der Jäger gestorben ist... obwohl ich nicht sagen kann, dass es nicht erwartet wurde - die Jagd auf diese Dinge ist eine sehr gefährliche Beschäftigung.";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Ich verstehe, worauf du hinauswillst. Ja, Liebe und Intrigen gibt es hier. Und warum sollten sie nicht? Der Mann ist für die Frau gemacht und so ist die Frau für den Mann gemacht. Natur. Du könntest es bei Gillian und Tanneke versuchen. Sie sind jung, hübsch und haben nichts gegen Hofmacherei\nIch habe mir eine Frau gefunden - Natalia. Sie ist Kellnerin in Sanchos Taverne. Ein tolles Mädchen, sag ich dir. Ich glaube, sie ist der einzige Grund, warum ich in den ersten Monaten hier nicht den Verstand verloren habe. Sie hat viel geholfen und jetzt sind wir zusammen.";
			link.l1 = "Hm... Ich hab's!";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Gute Frage. Natürlich würde ich das gerne. Aber wenn ich darüber nachdenke... Ich bin am Ende. Ich habe alles in die Ladung investiert und mein Schiff ist gesunken. Ich habe nichts mehr zum Leben übrig. Die einzige Möglichkeit für mich, Geld zu verdienen, ist, für die Holländische Westindien-Kompanie zu arbeiten, wenn sie mich natürlich einstellen\nWenn ich nur genug Geld hätte, um eine Schoner zu kaufen und genügend Vorräte... Also bleibe ich besser auf der Insel. Zumindest muss ich hier nicht von der Morgendämmerung bis zur Morgendämmerung für ein Stück Brot arbeiten.";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Was machst du da, ah? Dieb!","Schau nur! Kaum war ich in Gedanken versunken, hast du beschlossen, meine Truhe zu überprüfen!","Entschieden, meine Truhen zu überprüfen? Das wirst du nicht durchkommen!");
			link.l1 = "Verdammt!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Was?! Hast du dich entschlossen, meine Truhen zu überprüfen? Das wirst du nicht ungestraft lassen!";
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
			dialog.text = LinkRandPhrase("Hör zu, du solltest besser deine Waffe weglegen. Das macht mich nervös.","Weißt du, hier wird es nicht geduldet, mit einem Schwert zu rennen. Nimm es weg.","Hör zu, spiel nicht den mittelalterlichen Ritter, der mit einem Schwert herumläuft. Leg es weg, es steht dir nicht...");
			link.l1 = LinkRandPhrase("Gut.","Gut.","Wie du sagst...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin ein Bürger der Stadt und ich bitte dich, dein Schwert niederzuhalten.","Hör zu, ich bin ein Bürger der Stadt und ich bitte dich, dein Schwert niederzuhalten.");
				link.l1 = LinkRandPhrase("Gut.","Wie auch immer.","Wie du sagst...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sei vorsichtig, Kumpel, wenn du mit einer Waffe herumläufst. Ich kann nervös werden...","Ich mag es nicht, wenn Männer vor mir hergehen und ihre Waffe bereit haben. Es macht mir Angst...");
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
