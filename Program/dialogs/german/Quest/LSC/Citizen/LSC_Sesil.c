// Сесил Галард - бабулька
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
				dialog.text = "Brauchst du etwas, junger Mann?";
				link.l1 = TimeGreeting()+". Lass mich mich vorstellen - "+GetFullName(pchar)+". Ich bin ein Neuling.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Willst du etwas?";
				link.l1 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Gibt es Neuigkeiten auf der Insel?","Wirst du mir die neuesten Klatsch und Tratsch erzählen?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Ich möchte Ihnen einige Fragen zu der Insel stellen.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Wollte nur wissen, wie es dir geht. Bis dann!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "A-ah, also lernen Sie unsere Insel und ihre Bewohner kennen, habe ich recht?";
			link.l1 = "Genau, Frau?..";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Halard. Cecille Halard.";
			link.l1 = "Freut mich, Sie kennenzulernen, Frau Halard! Es ist mir eine Freude.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "So ist es bei mir... Und wie bist du hier gelandet, junger Mann? Ich erinnere mich nicht an irgendein kürzliches Schiffswrack...";
			link.l1 = "Ich wurde vom Main auf einer Barke hierher getrieben... aber sie ist direkt vor den Küsten der Insel gesunken. So blieb ich ohne Schiff.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Eine Bark? Ich finde es schwer zu glauben... In diesem Fall hast du wirklich Glück gehabt, dass du auf so einem Kahn bis zur Insel gesegelt bist und nicht in einen Sturm geraten bist. Stürme sind selten im Inneren der Insel, aber außerhalb sind sie eine Bedrohung, eine sehr plötzliche Bedrohung. \nAlso betrachte dich als glücklich und gewöhne dich an die hiesige Lebensweise! Ich möchte dich nicht verärgern, aber hierher zu kommen ist einfach, die Insel jedoch zu verlassen ist fast unmöglich. Denk nicht, dass ich meckere, niemand hat es geschafft, die Insel in den letzten zehn Jahren lebend zu verlassen.";
			link.l1 = "Und dennoch werde ich versuchen, ein wenig optimistischer zu sein. Schön, dich zu treffen und dich herum zu sehen!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ja, junger Mann?";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Und wie sind Sie hierher gekommen, Frau?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Du lebst schon lange hier, oder?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Was können Sie mir über die Einheimischen erzählen?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Können Sie mir von interessanten Leuten erzählen, die hier leben?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Keine Fragen. Entschuldigung...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Es war vor so langer Zeit, deshalb erinnere ich mich wirklich nicht, wie es passiert ist. Schiffbruch und das war's...";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Manchmal denke ich, dass ich hier geboren wurde... Aber das ist natürlich nicht wahr. Ich habe hier die zweite Hälfte meines Lebens verbracht. Und es war lang. Und ich werde hier sterben, weil ich nicht vorhabe, diesen Ort zu verlassen.";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Und es gibt nicht viel, was ich sagen kann, junger Mann... sie sind alle verschieden. Wir haben hier alle - Weiße, Schwarze, Indianer, ehemalige Sklaven und Adlige, Staatsverbrecher und Soldaten. Und früher waren es mehr. Jeder hat seine eigene Geschichte und seine eigenen Gewohnheiten. Einigen ist es egal, aber andere sind immer noch begierig darauf, zurückzukehren. So leben wir...";
			link.l1 = "Interessant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Die interessantesten Leute hier sind: der Narwal-Mechaniker-Erfinder, Herr Schmidt - Narwal-Waffenschmied, Sancho Carpentero - der einheimische Barkeeper. Und jetzt haben wir auch noch den Admiral mit seinem Stellvertreter.";
			link.l1 = "Ich werde darüber nachdenken...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Was machst du da, ah? Dieb!","Schau dir das an! Kaum habe ich in Gedanken versunken, hast du beschlossen, meine Truhe zu überprüfen!","Entschlossen, meine Truhen zu überprüfen? Das wirst du nicht ungestraft davonkommen!");
			link.l1 = "Verdammt!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Was?! Hast du dich entschieden, meine Truhen zu kontrollieren? Du kommst nicht ungeschoren davon!";
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
			dialog.text = LinkRandPhrase("Hör zu, du solltest besser deine Waffe weglegen. Es macht mich nervös.","Weißt du, hier wird es nicht toleriert, mit einer Klinge herumzulaufen. Nimm sie weg.","Hör zu, spiel nicht den mittelalterlichen Ritter, der mit einem Schwert herumläuft. Leg es weg, es steht dir nicht...");
			link.l1 = LinkRandPhrase("Gut.","Sicher.","Wie du sagst...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin Bürger dieser Stadt und ich bitte dich, deine Klinge niederzuhalten.","Hör zu, ich bin Bürger der Stadt und würde dich bitten, dein Schwert niederzulegen.");
				link.l1 = LinkRandPhrase("Gut.","Sicher.","Wie du sagst...");
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
