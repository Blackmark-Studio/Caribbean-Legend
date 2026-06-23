// Таннеке Эверс - просто девушка
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
				dialog.text = "Guten Tag! Kenne ich dich? Ich habe dich noch nie gesehen, das ist sicher...";
				link.l1 = TimeGreeting()+". Es ist wahr, ich bin ein neuer... Besucher hier. Mein Name ist "+GetFullName(pchar)+" und ich bin ein Kapitän.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Willst du etwas?";
				link.l1 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Ist auf der Insel etwas Neues passiert?","Wirst du mir die letzten Klatschereien erzählen?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Ich möchte Ihnen ein paar Fragen über die Insel stellen.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Wollte nur wissen, wie es dir geht. Bis dann!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Waren Sie schon einmal Kapitän?";
			link.l1 = "Warum bin ich gewesen? Ich bin immer noch ein Kapitän...ah, ich verstehe! Du denkst, dass mein Schiff gesunken oder von den Riffen zerstört wurde. Nein. Sie liegt in der Nähe der Küsten von Western Main. Und ich habe diesen Ort auf einer Barkasse erreicht, es endete allerdings schlecht, die Barkasse bekam ein Loch in ihrem Rumpf und sank.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Bist du hier auf einer Barke angekommen? Und wie hast du es geschafft, den Sturm zu überleben?";
			link.l1 = "Welcher Sturm? Ich erinnere mich an keinen Sturm...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Aber wie ist das möglich? Es gibt immer einen Sturm um die Insel. Das sagen alle Leute.";
			link.l1 = "Nun, das ist es nicht oder ich war glücklich genug, es zu umgehen. Das Meer war absolut ruhig... entschuldigen Sie, darf ich den Namen einer so hübschen Dame erfahren?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Oh! Entschuldigung, ich habe vergessen, mich vorzustellen... Mein Name ist Tanneke. Schön, Sie kennenzulernen.";
			link.l1 = "Es ist mir auch eine Freude, Tanneke... Es ist mir ein Vergnügen.";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Und warum haben Sie sich entschieden, unsere Insel auf einer Barkasse zu erreichen? A-ah, ich verstehe - Sie wurden von der Strömung direkt dorthin getrieben. Niemand weiß von der Insel und die Leute kommen immer zufällig hierher.";
			link.l1 = "Das ist nicht korrekt. Es gibt durchaus wahre Gerüchte über die Insel, einschließlich ihrer Lage. Also habe ich beschlossen, sie mit meinen eigenen Augen zu sehen...";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Nun sehe ich. Du bist genau wie Adolf Barbier, hast zu viel von Kapitän Alvarado gelesen und beschlossen, nach dem Gold von Admiral de Betancourt zu suchen. Ach, Kapitän, wenn so ein schlauer Schurke wie Barbier es nicht geschafft hat, es zu finden, dann bezweifle ich, dass du es schaffst\nUnd ich glaube wirklich, dass es kein Admiral's Gold gibt, Antonio muss es sich nur ausgedacht haben, um uns zu zeigen, was für ein wichtiger Mann sein Großvater war... Nun, dann bleibst du bei uns. Es war einfach, hierher zu kommen, aber es muss unmöglich sein, zu gehen. Ich meine, hier in einem Stück weggehen.";
			link.l1 = "Es ist nichts. Ich glaube, ich werde damit zurechtkommen, ich meine nicht das Gold von Betancourt, von dem du gesprochen hast - das höre ich zum ersten Mal, ich meine, die Insel zu verlassen. Lebendig. Es war mir ein Vergnügen, mit dir zu sprechen, Tanneke. Auf Wiedersehen!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Frag nur, Kapitän...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Wie bist du hierher gekommen?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Haben Sie jemals versucht, die Insel zu verlassen?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Wie lebst du hier?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Müssen Mädchen Essen vom Admiral kaufen oder bekommen sie es umsonst?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Keine Fragen. Entschuldigung...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Ich bin Holländerin, aber wir haben in Santiago gelebt. Meine Eltern schickten mich, um als Dienstmädchen für die Familie des Bankiers Geraldi zu arbeiten. Haben Sie von ihnen gehört? Vor drei Jahren segelte einer von ihnen nach Neu-Spanien auf einem Kurier-Lugger. Mir wurde gesagt, ich solle ihn begleiten. Am zweiten Tag unserer Reise wurden wir von einer Brigantine unter der spanischen Flagge gefangen genommen. \nIhr Offizier kam an Bord unseres Schiffes und sprach mit unserem Kapitän, der Kapitän wurde wütend und vertrieb den Offizier. Wir wurden angegriffen, sobald der Gast sein Schiff erreichte. Wir versuchten zu fliehen, aber sie schafften es, uns zu entern. Soweit ich verstanden habe, brauchten sie meinen Herrn Geraldi, denn sie stürmten in eine Kabine, fingen ihn und nahmen ihn mit. Ich und die Seeleute wurden in den Laderaum gebracht und dort gelassen. \nIch dachte, sie würden uns versenken, aber sie segelten einfach davon. Den Seeleuten gelang es, den Laderaum zu verlassen, aber unser Kapitän wurde im Kampf getötet und keiner der Überlebenden wusste, wie man einen richtigen Kurs steuert. Wir segelten irgendwohin, bis uns ein starker Sturm erfasste. \nEinige Stunden später wurde unser Lugger an den äußeren Ring geworfen. Es ist immer noch da. Ich hatte das Glück, das Durcheinander zu überleben, nach der Morgendämmerung haben ich und ein paar andere 'glückliche' Leute die Insel erreicht.";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Nein. Und wie stellst du dir das vor? Hier sind keine schiffsbereiten Schiffe und die Benutzung eines Langbootes ist so gut wie ein Todesurteil. Wie ich schon sagte, Stürme sind hier oft. Ich erinnere mich nur an den einen Versuch, diesen Ort zu verlassen - fünf Bürger hatten ein ordentliches Langboot mit Segeln und Ruder gebaut\nSie kämpften stundenlang gegen die Strömung und erreichten schließlich das offene Meer. Ein paar Tage später kehrte einer von ihnen zum äußeren Ring zurück... gebunden an ein Wrack eines Mastes und tot. Dies tötete den Wunsch der anderen, solche mutigen Dinge zu tun.";
			link.l1 = "Hab's verstanden...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Es ist in Ordnung. Es ist nicht schlimmer als ein Diener dieser arroganten Wuchererfamilie zu sein. Man muss sich nur an diesen Ort gewöhnen und danach könnte man ihn sogar lieben. Übrigens, ich bin nicht der Einzige, der so denkt. Und die Clans... sie stören mich nicht.";
			link.l1 = "Interessant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Natürlich kaufen wir. Oh, Kapitän, es gibt genug Arbeit für ein Mädchen: putzen, kochen, anderen helfen... wir sitzen nicht untätig herum, aber niemand bricht sich hier den Rücken. Piraten verkaufen Essen billig für die gewöhnlichen Bürger, im Gegensatz zu den Clans. Also verhungern wir nicht\nIch helfe Gillian und Natalie und sie helfen mir, wenn ich es brauche. Wir sind Freunde. Es gibt ein anderes Mädchen auf der Insel, die Spanierin. Ihr Name ist Ramona, aber sie ist meistens alleine und wir sind nicht wirklich daran interessiert, mit ihr befreundet zu sein.";
			link.l1 = "Und warum ist das so?";
			link.l1.go = "ansewer_4_1";
		break;
		
		case "ansewer_4_1":
			dialog.text = "Nun... sagen wir mal, wir haben unterschiedliche Ansichten über das Leben. Sprich mit ihr und du wirst verstehen.";
			link.l1 = "Interessant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Was machst du da, ah? Dieb!","Schau dir das an! Kaum war ich in Gedanken versunken, hast du beschlossen, meine Truhe zu überprüfen!","Entschieden, meine Truhen zu überprüfen? Das wirst du nicht ungestraft tun!");
			link.l1 = "Mist!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Was?! Hast du beschlossen, meine Truhen zu durchsuchen? Das wirst du nicht ungestraft davonkommen!";
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
			dialog.text = LinkRandPhrase("Hör zu, du solltest besser deine Waffe weglegen. Es macht mich nervös.","Weißt du, hier wird es nicht toleriert, mit einer Klinge herumzulaufen. Nimm sie weg.","Hör zu, spiel nicht den mittelalterlichen Ritter, der mit einem Schwert herumläuft. Nimm es weg, es steht dir nicht...");
			link.l1 = LinkRandPhrase("Gut.","Wie du wünschst...","Wie du sagst...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin Bürger der Stadt und ich würde dich bitten, dein Schwert niederzulegen.","Hör zu, ich bin Bürger der Stadt und ich würde dich bitten, deine Klinge niederzuhalten.");
				link.l1 = LinkRandPhrase("Gut.","Wie du wünschst...","Wie du sagst...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sei vorsichtig, Kumpel, beim Laufen mit einer Waffe. Ich kann nervös werden...","Ich mag es nicht, wenn Männer mit gezückter Waffe vor mir herlaufen. Es macht mir Angst...");
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
