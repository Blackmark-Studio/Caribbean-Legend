// Джиллиан Стайнер - просто девушка
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
				dialog.text = "Oh... hallo! Du hast mich erschreckt. Du bist so leise aufgetaucht... Was möchtest du?";
				link.l1 = TimeGreeting()+". Mein Name ist "+GetFullName(pchar)+". Ich bin ein Neuankömmling hier und ich lerne die Einheimischen kennen und habe mich endlich entschieden, mit einer so hübschen Dame wie Ihnen zu sprechen. Wie ist Ihr Name?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Willst du etwas?";
				link.l1 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Gibt es Neuigkeiten auf der Insel?","Wirst du mir die letzten Klatschgeschichten erzählen?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Ich möchte Ihnen ein paar Fragen zur Insel stellen.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Wollte nur wissen, wie es dir geht. Bis dann!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Sie bringen mich zum Erröten, Herr, aber es ist mir trotzdem eine Freude. Danke für das Kompliment. Mein Name ist Jillian, Jillian Steiner. Freut mich, Sie kennenzulernen.";
			link.l1 = "Auch ich, Jillian.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Bist du neu hier? Und wie bist du hierher gekommen, erzähl mir? Hast du den Schiffbruch überlebt?";
			link.l1 = "Nun... so etwas Ähnliches. Ich segelte hier auf einer Bark und kam fast durch das Riff, stieß aber leider auf Schiffsreste und mein Boot sank. Und ich schwamm hierher alleine.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Oh! Also bist du aus freiem Willen hierher gekommen? Unglaublich!";
			link.l1 = "Ja, ich bin so verrückt. Ich habe beschlossen, diese Insel der Gerechtigkeit zu finden und ich habe sie endlich gefunden. Aber jetzt weiß ich nicht, wie ich von ihr wegkommen soll.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Du bist sehr mutig oder rücksichtslos. Hier auf einer Barke zu segeln... Jetzt wirst du mit uns hier leben, weil niemand in der Lage war, diesen Ort im letzten Jahrzehnt zu verlassen.";
			link.l1 = "Ich habe immer noch Hoffnung. Gut, Jillian, ich werde dich nicht belästigen. Wir sehen uns!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ja, sicher, "+pchar.name+". Ich höre zu.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Wie bist du hierher gekommen?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Möchten Sie die Insel verlassen?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Und wie verläuft dein Tag? Was machst du?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Du sagst, du bist nicht verheiratet... Hat so ein hübsches Mädchen hier keine Verehrer?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Keine Fragen. Entschuldigung...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Ich segelte mit meinen Eltern von England aus. Wir wollten ein neues Leben beginnen und... ich habe hier ein neues Leben begonnen. Die Eltern starben und ich habe kaum überlebt. Ich erreichte ein Schiff vom äußeren Ring und lag dort einen Tag lang bewusstlos, bis mich ein Einheimischer dort fand. Ich wäre dort gestorben, wenn er mich nicht gefunden hätte.";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Und wohin? Wer braucht mich und wo? Ich habe kein Zuhause, keinen Ehemann und kein Geld. Ich war noch nie woanders als auf dieser Insel und im Londoner Slum. Es scheint, dass es mein Schicksal ist, hier zu leben...";
			link.l1 = "Bist du dir da sicher?";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Ich helfe hauptsächlich Bruder Julian in der Kirche. Ich mache auch einige leichte Arbeit in Axels Laden. So verdiene ich meine Münzen. Ich bin ein Mädchen und ich kann nicht auf den Schiffstrümmern am äußeren Ring herumklettern.";
			link.l1 = "Sicher...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Tee-hee... es gibt Bewunderer, ja, aber es gibt keinen Wert. Ich mag keinen von ihnen und ich möchte nicht mit einem Mann leben, den ich nicht mag. Die Männer, die ich mag, nehmen mich nicht wahr. Nun, ich bin nur ein gewöhnliches armes Mädchen...";
			link.l1 = "Es ist nur der Anfang eines neuen Lebens für dich...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Was machst du da, ah? Dieb!","Schau dir das an! Kaum war ich in Gedanken versunken, hast du beschlossen, meine Truhe zu überprüfen!","Du hast dich entschieden, meine Truhen zu überprüfen? Das wirst du nicht ungestraft davonkommen!");
			link.l1 = "Scheiße!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Was?! Hast du dich entschieden, meine Truhen zu überprüfen? Das wirst du nicht ungestraft lassen!";
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
			dialog.text = LinkRandPhrase("Hör zu, du solltest besser deine Waffe weglegen. Es macht mich nervös.","Du weißt, hier wird es nicht geduldet, mit einer Klinge herumzulaufen. Nimm sie weg.","Hör zu, spiel nicht den mittelalterlichen Ritter, der mit einem Schwert herumläuft. Leg es weg, es steht dir nicht...");
			link.l1 = LinkRandPhrase("Gut.","Gut.","Wie du sagst...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin ein Bürger der Stadt und ich bitte dich, dein Schwert niederzulegen.","Hör zu, ich bin Bürger dieser Stadt und ich bitte dich, deine Klinge niederzuhalten.");
				link.l1 = LinkRandPhrase("Gut.","Wie auch immer.","Wie du sagst...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sei vorsichtig, Kumpel, wenn du mit einer Waffe herumläufst. Ich kann nervös werden...","Ich mag es nicht, wenn Männer mit gezogener Waffe vor mir herlaufen. Es macht mir Angst...");
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
