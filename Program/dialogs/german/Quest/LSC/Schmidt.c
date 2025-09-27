// Юрген Шмидт - оружейник
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, iRem;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = "Hör zu, Herr, warum hast du deine Fäuste kämpfen lassen, hm? Du hast in meiner Werkstatt nichts zu suchen, bis du unser Feind bist. Raus!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // стал другом нарвалов
				{
					dialog.text = "Ach, "+GetFullName(pchar)+"! Ich habe von deinen Taten gehört. Es ist gut, dass du ein Freund von Donald geworden bist und unser Verbündeter. Narwale können Freundschaft schätzen, das kann ich dir sicher sagen.";
					link.l1 = "Ich hoffe es. Kann ich jetzt auf Ihre Dienste zählen?";
					link.l1.go = "friend";
				}
				else
				{
					dialog.text = "So? Was willst du?";
					link.l1 = TimeGreeting()+". Mein Name ist "+GetFullName(pchar)+". Und ich laufe nur herum, lerne Leute kennen. Störe ich dich?";
				link.l1.go = "meeting";
				}
				npchar.quest.meeting = "1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // стал другом нарвалов
				{
					dialog.text = "Ach, "+GetFullName(pchar)+"! Ich habe von deinen Taten gehört. Es ist gut, dass du ein Freund von Donald geworden bist und unser Verbündeter. Die Narwale können Freundschaft schätzen, das kann ich dir sicher sagen.";
					link.l1 = "Ich hoffe es. Kann ich jetzt auf deine Dienste zählen?";
					link.l1.go = "friend";
				}
				else
				{
					dialog.text = "Ach, "+GetFullName(pchar)+"! Wieder reden wollen? Ich muss dich enttäuschen, ich habe dafür weder Zeit noch Lust.";
					link.l1 = "Gut, ich werde dich nicht belästigen.";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Genau! Sie stören mich, mein Herr. Ich bin Jürgen Schmidt, Büchsenmacher und Schmied des Narwal-Klans. Ich versorge unser Volk mit Waffen. Aber es braucht Zeit, um eine gute Klinge, einen Schlüssel, ein Schloss zu machen oder den Mechanismus eines Turmmousqueton zu reparieren. Es braucht viel Zeit, Geduld und Aufmerksamkeit. Deshalb mag ich es nicht, wenn Leute mich stören.";
			link.l1 = "Stellen Sie Waffen her? Kann ich bei Ihnen etwas bestellen?";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Nein. Ich stelle Waffen nur für Mitglieder des Narwal-Klans her. Das ist mein Prinzip und ich werde es beibehalten. Also hoffen Sie nicht einmal, Herr. Treten Sie unserem Klan bei oder werden Sie zumindest unser Verbündeter und in diesem Fall werden wir ein Gespräch führen.";
			link.l1 = "Gut. Dann verlasse ich dich. Entschuldigung für die Unannehmlichkeiten!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "friend":
			dialog.text = "Du kannst. Ein Freund der Narwale ist auch mein Freund, also höre ich dir zu.";
			link.l1 = "Ich möchte ein Schwert bestellen.";
			link.l1.go = "blade";
			if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l2 = "Ich habe gehört, dass du eine besondere Klinge für den verstorbenen Alan Milrow angefertigt hast. Ich habe dieses Breitschwert gesehen, es ist eine großartige Waffe. Kann ich so etwas bestellen?";
				link.l2.go = "narval";
			}
			link.l3 = "Ich habe noch keine Ideen. Ich werde darüber nachdenken und dann zurückkommen!";
			link.l3.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		case "Jurgen":
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Ha, "+GetFullName(pchar)+"! Also bist du nicht ertrunken? Ist das nicht etwas! Bist du wirklich am Leben?";
				link.l1 = "Mach dir keine Sorgen, Jurgen. Ich lebe! Ich war nicht vor, zu ertrinken...";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				NextDiag.TempNode = "Jurgen";
				break;
			}
			dialog.text = "Ach, "+GetFullName(pchar)+"! Was willst du?";
			if (CheckAttribute(npchar, "quest.narval_blade") && npchar.quest.narval_blade == "ferrum")
			{
				if (GetCharacterItem(pchar, "jewelry11") >= 3)
				{
					link.l4 = "Ich habe die drei Stücke des besonderen Eisens gebracht, wie Sie gefragt haben. Schauen Sie mal, ist es das, was Sie wollen?";
					link.l4.go = "narval_7";
				}
				if (CheckCharacterItem(pchar, "meteorite"))
				{
					link.l5 = "Werf mal einen Blick drauf, Jurgen. Ich habe am Boden einen interessanten Eisenerzklumpen gefunden, aber er wiegt viel mehr als du gefragt hast. Nicht weniger als fünf Pfund.";
					link.l5.go = "narval_7_1";
				}
			}
			if (!CheckAttribute(npchar, "quest.blade_done"))
			{
				link.l1 = "Ich möchte ein Schwert bestellen.";
				if (!CheckAttribute(npchar, "quest.blade_rules")) link.l1.go = "blade";
				else link.l1.go = "blade_4";
			}
			if (CheckAttribute(npchar, "quest.blade_payseek"))
			{
				link.l1 = "Ich habe dir weitere Dublonen als Bezahlung für die Klinge gebracht.";
				link.l1.go = "blade_3";
			}
			if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive" && npchar.quest.narval_blade == "begin" && pchar.questTemp.LSC != "return") // patch-9
			{
				link.l2 = "Ich habe gehört, dass Sie ein besonderes Schwert für den verstorbenen Alan Milrow angefertigt haben. Ich habe dieses Breitschwert gesehen, es ist eine großartige Waffe. Kann ich so etwas bestellen?";
				link.l2.go = "narval";
			}
			if (CheckAttribute(npchar, "blade_date") && GetNpcQuestPastDayParam(npchar, "blade_date") >= 20)
			{
				link.l1 = "Ich bin hier wegen meiner Bestellung. Sie muss bereits fertig sein, habe ich recht?";
				link.l1.go = "blade_done_2";
			}
			link.l3 = "Nein, es ist nichts, wollte dich nur grüßen.";
			link.l3.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		// --> заказ клинков
		case "blade":
			dialog.text = "Gut. Aber ich habe einige besondere Anforderungen für jede Bestellung, also hör zuerst genau zu.";
			link.l1 = "Ich bin ganz Ohr.";
			link.l1.go = "blade_1";
		break;
		
		case "blade_1":
			dialog.text = "Du darfst bei mir nur eine Klinge und nur einmal bestellen. Ich mache keine spezifische Waffe, du darfst nur den Typ nennen - Rapier, Säbel oder Breitschwert. Denke weise, bevor du eine Wahl triffst, die endgültigen Eigenschaften und Qualität der Klinge hängen von den Materialien ab, die ich gerade habe\nJetzt. Es wird zwanzig Tage dauern, deine Bestellung anzufertigen. Ich akzeptiere nur Dublonen. Tausend Münzen. Geld im Voraus.";
			link.l1 = "Wirklich! Teuer...";
			link.l1.go = "blade_2";
		break;
		
		case "blade_2":
			dialog.text = "Es ist teuer. Aber ich mache ausgezeichnete Klingen, also ist der Preis fair genug. Es ist sowieso Ihre Entscheidung, kein Druck.";
			link.l1 = "Ich habe es verstanden, Jurgen. Ja, ich möchte eine Bestellung aufgeben.";
			link.l1.go = "blade_3";
			link.l2 = "Hm. Ich brauche Zeit zum Nachdenken, bevor ich etwas von dir bestelle. Wir werden später darüber sprechen!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Jurgen";
			npchar.quest.blade_rules = "true";
			npchar.quest.blade_dublon = 1000;
			AddQuestRecord("LSC", "17");
		break;
		
		case "blade_3":
			dialog.text = "Sehr gut. Gib mir dann deine Dublonen.";
			if (PCharDublonsTotal() > 0)
			{
				npchar.quest.blade_pay = PCharDublonsTotal();
				link.l1 = "Hier, bitte. Ich habe "+FindRussianQtyString(sti(npchar.quest.blade_pay))+".";
				link.l1.go = "blade_pay";
			}
			link.l2 = "Hm. Leider habe ich jetzt keine bei mir. Aber ich werde sie dir sicherlich bringen und wir werden unser Gespräch fortsetzen.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		case "blade_4":
			dialog.text = "Ist es also Ihre endgültige Entscheidung? Sind Sie sicher?";
			link.l1 = "Ja, das bin ich.";
			link.l1.go = "blade_3";
		break;
		
		case "blade_pay": // оплата
			if (sti(npchar.quest.blade_dublon) < sti(npchar.quest.blade_pay)) // полная сумма
			{
				npchar.quest.blade_pay = sti(npchar.quest.blade_dublon);
				iTemp = 0;
			}
			else iTemp = sti(npchar.quest.blade_dublon)-sti(npchar.quest.blade_pay);
			npchar.quest.blade_dublon = iTemp; // запоминаем остаток
			RemoveDublonsFromPCharTotal(sti(npchar.quest.blade_pay));
			Log_Info("You have given "+sti(npchar.quest.blade_pay)+" doubloons");
			PlaySound("interface\important_item.wav");
			if (iTemp == 0)
			{
				dialog.text = "Prächtig. Sie haben mich für meine Arbeit und Materialien bezahlt, also kann ich jetzt anfangen.";
				link.l1 = "Kann ich eine Bestellung aufgeben?";
				link.l1.go = "blade_done";
			}
			else
			{
				dialog.text = "Gut. Ich akzeptiere deine Dublonen. Du musst mir bringen "+FindRussianQtyString(sti(npchar.quest.blade_dublon))+" mehr.";
				link.l1 = "Ich werde sie dir bringen, wenn ich sie habe.";
				link.l1.go = "exit";
				npchar.quest.blade_payseek = "true";
			}
		break;
		
		case "blade_done":
			DeleteAttribute(npchar, "quest.blade_payseek");
			dialog.text = "Sicher! Welche Art magst du am meisten? Degen, Säbel oder Breitschwerter?";
			link.l1 = "Degen. Ich mag elegante und leichte Waffen.";
			link.l1.go = "rapier";
			link.l2 = "Säbel. Sie sind meiner Meinung nach optimal.";
			link.l2.go = "sabre";
			link.l3 = "Sicher Breitschwerter! Schneiden und hacken!";
			link.l3.go = "palash";
		break;
		
		case "rapier":
			npchar.quest.blade_done = SelectJurgenBladeDone("rapier");
			dialog.text = "Wie Sie wünschen. Kommen Sie in zwanzig Tagen zurück, nicht früher.";
			link.l1 = "Danke! Wir sehen uns in zwanzig Tagen. Auf Wiedersehen, Jurgen.";
			link.l1.go = "blade_done_1";
		break;
		
		case "sabre":
			npchar.quest.blade_done = SelectJurgenBladeDone("sabre");
			dialog.text = "Wie du wünschst. Komm in zwanzig Tagen zurück, nicht früher.";
			link.l1 = "Danke! Wir sehen uns in zwanzig Tagen. Auf Wiedersehen, Jurgen.";
			link.l1.go = "blade_done_1";
		break;
		
		case "palash":
			npchar.quest.blade_done = SelectJurgenBladeDone("palash");
			dialog.text = "Wie du wünschst. Komm in zwanzig Tagen zurück, nicht früher.";
			link.l1 = "Danke! Wir sehen uns in zwanzig Tagen. Auf Wiedersehen, Jurgen.";
			link.l1.go = "blade_done_1";
		break;
		
		case "blade_done_1":
			DialogExit();
			SaveCurrentNpcQuestDateParam(npchar, "blade_date");
			NextDiag.CurrentNode = "Jurgen";
			AddQuestRecord("LSC", "18");
		break;
		
		case "blade_done_2":
			dialog.text = "Ja. Dein Schwert ist bereit. Bitte, nimm es und benutze es. Du wirst verstehen, dass es seinen Preis wert ist, sobald du es nur berührst.";
			link.l1 = "Danke, Jurgen.";
			link.l1.go = "blade_done_3";
		break;
		
		case "blade_done_3":
			DialogExit();
			NextDiag.CurrentNode = "Jurgen";
			GiveItem2Character(pchar, npchar.quest.blade_done);
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "blade_date");
		break;
		
		// заказ палаша Нарвал для Мэри
		case "narval":
			dialog.text = "Ach, mein Freund, ich muss aus zwei Gründen ablehnen. Erstens, ich würde ein solches Breitschwert nur für ein Mitglied des Narwal-Clans und nur für jemand Besonderes herstellen. Zweitens, ich habe nicht die Materialien dafür.";
			link.l1 = "Und was ist das besondere Eisen, das du brauchst? Ich habe gehört, dass sie es vom Grund bekommen haben...";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			dialog.text = "Genau. Es gibt Stücke von diesem Metall, die überall in unserer Untiefe verstreut sind. Ich weiß nicht, wie sie dorthin gekommen sind. Aber das Eisen ist einzigartig, es wird nie rostig und die Klingen, die daraus gemacht werden, werden nie stumpf. Also, wenn du es schaffen würdest, das Eisen zu bekommen, dann könnten wir die Angelegenheit vielleicht lösen. Aber es gibt noch ein Problem, du bist kein Narwal...";
			link.l1 = "Hm. Macht es wirklich einen Unterschied?";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			dialog.text = "Ja. Sie können das als meine Laune betrachten, aber ich werde ein solches Breitschwert nur für Narwal herstellen.";
			link.l1 = "Nun... Gut, das akzeptiere ich. Aber ich habe eine Idee. Kann ich dieses Schwert für das Mitglied des Narwal-Clans bestellen?";
			link.l1.go = "narval_3";
		break;
		
		case "narval_3":
			dialog.text = "Hm. Ich nehme an, das kannst du, wenn du mir das Eisen bringst. Es wird meine Prinzipien nicht verletzen... Und für wen soll ich das Breitschwert machen?";
			link.l1 = "Für die Rote Mary. Sie ist aus dem Narwal Clan und sie verdient es, eine so ausgezeichnete Waffe zu besitzen.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			dialog.text = "Ha! Das hätte ich mir auch denken können. Ich werde zu alt... Nun, ich stimme zu. Mary wird sich sicherlich sehr über ein solches Geschenk freuen... Bringe mir das Eisen und ich werde das Breitschwert herstellen. Ich werde für die Klinge... ach, was auch immer, ich mache es umsonst. Es wird ein Geschenk nicht nur von dir, sondern von uns beiden sein.";
			link.l1 = "Danke! Wie viel Eisen brauchst du?";
			link.l1.go = "narval_5";
		break;
		
		case "narval_5":
			dialog.text = "Diese Stücke, die wir am Grund gefunden haben, waren ganz gleich - ein Pfund pro Stück. Ich brauche drei solche Stücke.";
			link.l1 = "Gut. Ich werde versuchen, sie zu finden. Und wir werden wieder sprechen.";
			link.l1.go = "narval_6";
		break;
		
		case "narval_6":
			DialogExit();
			npchar.quest.narval_blade = "ferrum";
			NextDiag.CurrentNode = "Jurgen";
			// кладем гигантский кусок метеорита на дно
			sld = ItemsFromID("meteorite");
			sld.shown = true;
			sld.startLocation = "underwater";
			sld.startLocator = "item"+(rand(7)+1);
			Log_TestInfo("Meteorite in the locator " + sld.startLocator);
			pchar.quest.LSC_narval_ferrum.win_condition.l1 = "item";
			pchar.quest.LSC_narval_ferrum.win_condition.l1.item = "meteorite";
			pchar.quest.LSC_narval_ferrum.function = "LSC_NarvalFerrum";
			AddQuestRecord("LSC", "19");
		break;
		
		case "narval_7":
			RemoveItems(pchar, "jewelry11", 3);
			PlaySound("interface\important_item.wav");
			dialog.text = "Lass mich sehen... Ja, es ist! War es schwierig, solche kleinen Stücke am Boden zu finden?";
			link.l1 = "Nun, was kann ich sagen... Mary ist solche Mühen wert, nicht wahr?";
			link.l1.go = "narval_8";
			pchar.quest.LSC_narval_ferrum.over = "yes"; //снять прерывание
		break;
		
		case "narval_7_1":
			RemoveItems(pchar, "meteorite", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Lass mich sehen... Ist das nicht etwas! Ja, das ist das Grundmetall, aber ich habe noch nie solche großen Stücke gesehen. Dieses wird ausreichen, um das Breitschwert herzustellen. War es schwierig, es zu finden?";
			link.l1 = "Nun, was kann ich sagen... Mary ist solche Mühen wert, oder nicht?";
			link.l1.go = "narval_8";
		break;
		
		case "narval_8":
			dialog.text = "Ich mag dich immer mehr, "+pchar.name+"... Sehr gut dann. Jetzt ist es meine Aufgabe, im Namen unserer schönen Amazone zu arbeiten. Es wird zwei Tage dauern, das Breitschwert zu machen, ich lege andere Bestellungen beiseite\nBring mir Mary übermorgen. Sag es ihr nicht, es ist eine Überraschung. Sie wird glücklich sein wie ein Kind.";
			link.l1 = "Gut, Jurgen. Abgemacht! Wir sehen uns übermorgen!";
			link.l1.go = "narval_9";
		break;
		
		case "narval_9":
			DialogExit();
			npchar.quest.narval_blade = "work";
			NextDiag.CurrentNode = "narval_10";
			SetFunctionTimerCondition("LSC_NarvalBladeForMary", 0, 0, 2, false); // таймер
			AddQuestRecord("LSC", "21");
		break;
		
		case "narval_10":
			dialog.text = ""+pchar.name+", stör mich nicht. Du willst doch, dass ich das Breitschwert rechtzeitig fertigstelle, oder?";
			link.l1 = "Ja, sicher. Ich gehe jetzt.";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_10";
		break;
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Was machst du da, ah? Dieb!","Schau dir das an! Kaum war ich in Gedanken verloren, hast du beschlossen, meine Truhe zu überprüfen!","Entschlossen, meine Truhen zu durchsuchen? Das wirst du nicht ungestraft tun!");
			link.l1 = "Verdammt!";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Hör zu, du solltest besser deine Waffe weglegen. Es macht mich nervös.","Weißt du, hier wird es nicht geduldet, mit einer Klinge herumzulaufen. Nimm sie weg.","Hör zu, spiel keinen mittelalterlichen Ritter, der mit einem Schwert herumläuft. Leg es weg, es steht dir nicht...");
			link.l1 = LinkRandPhrase("Gut.","Gut.","Wie du sagst...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin ein Bürger der Stadt und ich bitte dich, dein Schwert niederzulegen.","Hör zu, ich bin Bürger der Stadt und ich bitte dich, deine Klinge zu senken.");
				link.l1 = LinkRandPhrase("Gut.","Gut.","Wie du sagst...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sei vorsichtig, Kumpel, wenn du mit einer Waffe herumläufst. Ich kann nervös werden...","Ich mag es nicht, wenn Männer mit gezogener Waffe vor mir hergehen. Das ängstigt mich...");
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

string SelectJurgenBladeDone(string _sType)
{
	string sBlade;
	switch (_sType)
	{
		case "rapier":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_18"; 
			else sBlade = "q_blade_16";
		break;
		
		case "sabre":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_19"; 
			else sBlade = "q_blade_10";
		break;
		
		case "palash":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_21"; 
			else sBlade = "q_blade_13";
		break;
	}
	return sBlade;
}
