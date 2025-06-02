#include "DIALOGS\%language%\Rumours\Common_rumours.c" //Jason
void ProcessDialogEvent()
{
 	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\ItemTrader\" + NPChar.City + "_ItemTrader.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
// ============================================================================
// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
			
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================	   
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
  		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

  		case "First time":
			dialog.text = NPCharSexPhrase(npchar,"Möchten Sie Ausrüstung für sich selbst oder für Ihre Offiziere kaufen, Kapitän? Wenn ja, dann sind Sie genau zur richtigen Person gekommen!","Oh, Kapitän, ich wusste, dass Sie auf mich zukommen würden! Ich kann Ihnen Ausrüstung für Sie und Ihre Offiziere anbieten, unter vielen anderen nützlichen Dingen.");
			link.l1 = "Zeig mir, was du hast.";
			link.l1.go = "Trade_exit";
			
   			/*link.l2 = "Ich bin wegen einer anderen Angelegenheit gekommen.";
			link.l2.go = "quests";*/
			// --> Мангароса
			if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "find" && npchar.Merchant.type == "potion" && !CheckAttribute(npchar, "quest.mangarosa"))
			{
				link.l4 = "Hallo, ich habe eine interessante Pflanze gefunden. Könntest du mir sagen, ob sie zum Brauen von Tränken oder Dekokten verwendet werden kann? Sie scheint mir einfach interessant. Kannst du mal schauen?";
				link.l4.go = "mangarosa";
			}
			// <-- Мангароса
			

			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "Sag, kannst du mir eine Flasche feinen europäischen Wein verkaufen?";
				link.l4.go = "Wine_ItemTrader";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.bottles") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "Hör zu, ich weiß, dass du europäischen Wein verkaufst. Ich brauche sechzig Flaschen.";
				link.l4.go = "Wine_Bottles";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.Repeat1") && NPChar.location == pchar.questTemp.Wine.City + "_town" && npchar.id == pchar.questTemp.Wine.ItemTraderID && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "Das bin ich wieder. Was bedeutet das alles, huh?";
				link.l4.go = "Wine_Repeat1";
			}
			// <-- мини-квест Дефицитный товар
			
			//Sinistra --> мини-квест "Знакомство с индейцами"
			if (CheckAttribute(pchar, "questTemp.ZsI_PokupaemPistolety") && npchar.Merchant.type == "armourer")
			{
   				link.l4 = "Ich brauche zwei Pistolen, zusammen mit Kugeln und Pulver für zwanzig Schüsse.";
				link.l4.go = "ZsI_PokupaemPistolety";
			}
			// <-- мини-квест "Знакомство с индейцами"
			
			// --> Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l4 = "Hör zu, sagt dir der Name 'Juan' etwas?";
				link.l4.go = "Consumption";
			}
			// <-- Цена чахотки
			
			//--> Украденное воспоминание
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
			{
				link.l4 = "Sagt mir, habt Ihr vielleicht etwas wirklich Besonderes? Keine billigen Kleinigkeiten, sondern etwas wahrhaft Raffiniertes—zum Beispiel elegante Ohrringe oder ein feines Medaillon. Ich suche ein Geschenk für eine Dame von edler Herkunft.";
				link.l4.go = "UV_Lavochniki_1";
			}
            if(CheckAttribute(pchar, "questTemp.UV_Lavochniki_2") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
            {
				link.l4 = "Habt Ihr vielleicht etwas wirklich Wertvolles? Ich suche ein Schmuckstück, das selbst den Ansprüchen der anspruchsvollsten Aristokratin gerecht würde – etwas Seltenes, Elegantes, nicht für das gewöhnliche Volk. Vielleicht ein geschmackvoller Anhänger oder ein kunstvoll gearbeiteter Armreif?";
				link.l4.go = "UV_Lavochniki_2";
			}
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki_3") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
            {
				link.l4 = "Sagt mal, kennt Ihr Euch mit Schmuck aus? Ich suche etwas ganz Besonderes als Geschenk für eine edle Dame. Ich warne Euch gleich – billiger Tand interessiert mich nicht. Ich brauche etwas Raffiniertes: vielleicht eine kunstvoll verzierte Brosche oder einen prachtvollen Ring.";
				link.l4.go = "UV_Lavochniki_3";
			}
			//<-- Украденное воспоминание
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l5 = "Hör zu, du handelst mit allerlei Waren... Hat dir gestern oder heute jemand etwas zum Verkauf angeboten  "+pchar.GenQuest.Device.Shipyarder.Type+"?";
				link.l5.go = "Device_ItemTrader";
			}
			//<-- генератор Неудачливый вор

			link.l9 = "Danke, nicht interessiert.";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Trade_exit":
            if (CheckNPCQuestDate(npchar, "Item_date"))
			{
				SetNPCQuestDate(npchar, "Item_date");
				GiveItemToTrader(npchar);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsTrade(npchar, 0);
		break;
		
		//Jason --> мини-квест Дефицитный товар
		case "Wine_ItemTrader":
			dialog.text = "Sicher. Siebenhundert Pesos pro Flasche.";
			if (makeint(Pchar.money) >= 700)
			{
				link.l1 = "Ausgezeichnet. Nimm das Geld und gib es mir.";
				link.l1.go = "Wine_ItemTrader_1";
			}
			link.l2 = "Ausgezeichnet! Ich komme zurück, wenn ich mich entscheide, etwas zu kaufen.";
			link.l2.go = "exit";
		break;
		
		case "Wine_ItemTrader_1":
			dialog.text = "Bitte, nimm deine Flasche.";
			link.l1 = "Danke dir!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -700);
			TakeNItems(pchar, "potionwine", 1);
			PlaySound("interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.Wine.bottle");
			AddQuestRecord("Wine", "1_1");
			WineTraderQMDel();
		break;
		
		case "Wine_Bottles":
			dialog.text = "Ha! Ich bin nur ein Einzelhändler, kein Großhändler. Ich würde so viele Flaschen über ein halbes Jahr verkaufen - dieser Wein ist selten und teuer, und nicht jeder kann ihn sich leisten, verstehst du. So viele habe ich nicht.";
			link.l1 = "Also gut, du hast sie nicht - kein Problem. Aber du besorgst sie dir irgendwo für dich selbst, oder? Vielleicht könntest du mir den Namen deines Lieferanten nennen, und ich würde es direkt von ihm kaufen. Oder wird dir der Wein aus Europa geliefert?";
			link.l1.go = "Wine_Bottles_1";
		break;
		
		case "Wine_Bottles_1":
			dialog.text = "Nein, das ist es nicht. Ich bekomme es hier. Aber ich werde dir meinen Lieferanten nicht einfach so nennen. Aber für tausend Peso... vielleicht würde ich...";
			if (makeint(Pchar.money) >= 1000)
            {
				link.l1 = "Gut. Hier sind deine tausend - und jetzt sag mir, wer dein Lieferant ist.";
				link.l1.go = "Wine_Bottles_2";
			}
			link.l2 = "Nun seid ihr Händler zu dreist geworden! Wäre das nicht zu gut für euch? Ich werde ohne euren Lieferanten gut auskommen, danke.";
			link.l2.go = "Wine_Bottles_fail";
		break;
		
		case "Wine_Bottles_free":
			dialog.text = "Ich schätze... na gut dann. Hier ist dein Brief, und ich hoffe, du erweist mir in der Zukunft den Gefallen.";
			link.l1 = "...";
			link.l1.go = "Wine_Bottles_free_1";
		break;
		
		case "Wine_Bottles_free_1":
			pchar.questTemp.Wine.TraderID = pchar.questTemp.Wine.City +"_trader";
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			pchar.questTemp.Wine.Name = GetFullName(sld);
			pchar.questTemp.Wine.ItemTraderID = npchar.id;
			dialog.text = "Der Name meines Weinhändlers ist "+pchar.questTemp.Wine.Name+", er besitzt den örtlichen Laden.";
			link.l1 = "Hab's! Danke!";
			link.l1.go = "exit";
			//pchar.questTemp.Wine.Trader = "true";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
		break;
		
		case "Wine_Bottles_2":
    		AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.Wine.TraderID = pchar.questTemp.Wine.City +"_trader";
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			AddLandQuestMark(sld, "questmarkmain");
			pchar.questTemp.Wine.Name = GetFullName(sld);
			pchar.questTemp.Wine.ItemTraderID = npchar.id;
			dialog.text = "Der Name meines Weinhändlers ist "+pchar.questTemp.Wine.Name+", er besitzt den örtlichen Laden.";
			link.l1 = "Habs! Danke!";
			link.l1.go = "exit";
			pchar.questTemp.Wine.Trader = "true";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			AddQuestRecord("Wine", "3");
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
			WineTraderQMDel();
		break;
		
		case "Wine_Bottles_fail":
			dialog.text = "Wie du wünschst, Kapitän. Alles Gute für dich.";
			link.l1 = "Auf Wiedersehen.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			AddQuestRecord("Wine", "4");
			WineTraderQMDel();
		break;
		
		case "Wine_Repeat1":
			DeleteAttribute(pchar, "questTemp.Wine.Repeat1");
			dialog.text = "Was meinst du damit? Erkläre dich.";
			link.l1 = "Du hast mich betrogen, du Schurke! Ich war gerade im Laden, "+pchar.questTemp.Wine.Name+" handelt nie mit Wein, wie er mir selbst gesagt hat! Gib mir mein Geld zurück!";
			link.l1.go = "Wine_Repeat1_fail";
			link.l2 = "Es gab ein Missverständnis... Ich ging zum Ladenbesitzer, und "+pchar.questTemp.Wine.Name+" behauptete, dass er noch nie mit Wein gehandelt hat. Wie können Sie das erklären?";
			link.l2.go = "Wine_Repeat1_1";
		break;
		
		case "Wine_Repeat1_1":
			dialog.text = "Heh! Er handelt mit Wein, das ist verdammt sicher. Er verkauft jedoch nicht einfach jedem Wein - wie bei einigen anderen Waren auch. Und dafür gibt es mehrere Gründe... Wenn du von ihm Wein kaufen möchtest, kann ich ihm einen Zettel schreiben. Er kennt mich und meine Handschrift, also wird er dir den Wein verkaufen, nachdem er ihn gelesen hat. Natürlich ist auch dieser Gefallen nicht kostenlos.";
			link.l1 = "Das ist ein Skandal! Du hast gerade ein Vermögen von mir genommen!";
			link.l1.go = "Wine_Repeat1_2";
		break;
		
		case "Wine_Repeat1_2":
			dialog.text = "Ich habe von dir tausend für Informationen genommen. Und für einen Brief musst du separat zweitausend Pesos bezahlen, und auf keinen Fall weniger als das.";
			if (makeint(Pchar.money) >= 2000)
			{
				link.l1 = "Oh... Ihr Händler seid so verdammt gierig. Kein Wunder, dass niemand euresgleichen mag. Na gut, hier ist euer Geld, also macht hin und schreibt den Zettel.";
				link.l1.go = "Wine_Bottles_3";
			}
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l2 = "(Vertrauenswürdig) Lasst uns einen Kompromiss schließen. Du gibst jetzt eine Empfehlung ab, kostenlos, und ich werde später mit einer Empfehlung für dich rezipieren, auch kostenlos. Dieser Weinhandel ist nur der Anfang.";
				link.l2.go = "Wine_Bottles_free";
			}
			link.l3 = "Jetzt wird's aber völlig unerhört! Ich würde das Ganze lieber aufgeben, ich werde so einen gerissenen Geizhals nicht bereichern. Und mit diesem Geizhals meine ich dich. Lebewohl.";
			link.l3.go = "Wine_Repeat1_goaway";
		break;
		case "Wine_Bottles_free":
			dialog.text = "Ich vermute... na gut dann. Hier ist Ihr Zettel, und ich hoffe, Sie erwidern den Gefallen in der Zukunft.";
			link.l1 = "...";
			link.l1.go = "Wine_Bottles_free_1";
		break;
		
		case "Wine_Bottles_free_1":
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Wine", "6_1");
			DelLandQuestMark(npchar);
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			AddLandQuestMark(sld, "questmarkmain");
			DialogExit();
		break;
		
		case "Wine_Bottles_3":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Du bist ein seltsamer Vogel, Kapitän! Sicher, ich verstehe, dass dein Zahlmeister alle Finanzangelegenheiten regelt, aber du solltest manchmal auch deinen eigenen Kopf benutzen. Du wirst die Gelegenheit haben, eine anständige Menge Wein großhandel zu kaufen, ohne meine Preisaufschläge und dabei einen erheblichen Gewinn zu erzielen. Also, lassen wir uns nicht daran hindern, Geld zu verdienen, denn jetzt siehst du gierig aus.\nRecht...(schreibt) Hier, nimm diesen Brief - "+pchar.questTemp.Wine.Name+"  wird Ihnen den Wein ohne Fragen verkaufen.";
			link.l1 = "Ich hoffe es doch... Wenn wieder etwas schief geht, komme ich zurück. Bis dann!";
			link.l1.go = "Wine_Bottles_4";
		break;
		
		case "Wine_Bottles_4":
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Wine", "6");
			DelLandQuestMark(npchar);
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			AddLandQuestMark(sld, "questmarkmain");
			DialogExit();
		break;
		
		case "Wine_Repeat1_goaway":
			dialog.text = "Wie Sie wünschen, Kapitän. Auf Wiedersehen.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "4");
			DelLandQuestMark(npchar);
		break;
		
		case "Wine_Repeat1_fail":
			dialog.text = "Oh, also bist du hierher gekommen, um mir zu drohen und unhöflich zu sein? Dann rufe ich die Wachen! Hey, Wachen! Hier drüben!";
			link.l1 = "Oh, halt die Klappe! Du hast gewonnen, ich gehe! Verfluche dich "+NPCharSexPhrase(npchar,"","")+", Kormoran, mögest du zugrunde gehen!";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "7");
			DelLandQuestMark(npchar);
		break;
		// <-- мини-квест Дефицитный товар
		
		//Sinistra --> мини-квест "Знакомство с индейцами"
		case "ZsI_PokupaemPistolety":
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				dialog.text = "Ach, ich sehe schon. Geschäfte mit den Eingeborenen? Ich habe gehört, dieser hier hat dir schon ein hübsches Sümmchen gekostet, ha ha!";
			}
			else
			{
				dialog.text = "Erwarten Sie Ärger, Kapitän? Oder planen Sie ein Dschungelabenteuer? Ha-ha!";
			}
			link.l1 = "Also, können wir einen Handel abschließen?";
			link.l1.go = "ZsI_PokupaemPistolety_1";
			DelLandQuestMark(npchar);
		break;
		
		case "ZsI_PokupaemPistolety_1":
			dialog.text = "Natürlich! Kunden sind immer willkommen. Für dreitausend Pesos erhalten Sie zuverlässige Pistolen, Kugeln und Pulver wie gewünscht.";
			if (sti(pchar.Money) > 2999)
			{
				link.l1 = "Teuer, aber in Ordnung. Ich nehme es.";
				link.l1.go = "ZsI_PokupaemPistolety_2";
			}
			if (sti(pchar.Money) > 2299)
			{
				link.l2 = "Der Preis scheint ungerecht. Wie wäre es mit einem Rabatt für einen Freund von Fadey Moskowiter?";
				link.l2.go = "ZsI_Torg";
			}
			link.l3 = "Dreitausend? Das ist Raub! Auf Wiedersehen, Monsieur!";
			link.l3.go = "ZsI_NetDeneg";
		break;
		
		case "ZsI_NetDeneg":
			DialogExit();
			
			LocatorReloadEnterDisable("BasTer_town", "gate_back", false);
			PChar.quest.ZsI_Timer.over = "yes";
			sld = CharacterFromID("ListKakao");
			sld.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
		break;
		
		case "ZsI_PokupaemPistolety_2":
			dialog.text = "Macht's gut da draußen, Kapitän!";
			link.l1 = "Auf Wiedersehen, Monsieur.";
			link.l1.go = "ZsI_PokupaemPistolety_3";
			AddMoneyToCharacter(pchar, -3000);
			Log_info("You have acquired the required pistols for Cocoa Leaf");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_PokupaemPistolety_3":
			DialogExit();
			
			LocatorReloadEnterDisable("BasTer_town", "gate_back", false);
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
			PChar.quest.ZsI_Patrul.win_condition.l1 = "location";
			PChar.quest.ZsI_Patrul.win_condition.l1.location = "BasTer_ExitTown";
			PChar.quest.ZsI_Patrul.win_condition = "ZsI_Patrul";
		break;
		
		case "ZsI_Torg":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 18)
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				dialog.text = "In der Tat, Kapitän. Fadeys Freunde sind hier immer willkommen. Zweitausenddreihundert für das ganze Los?";
				link.l1 = "Das klingt besser. Ich nehme es.";
				link.l1.go = "ZsI_Torg_2";
				AddCharacterExpToSkill(pchar, "Commerce", 30);
			}
			else
			{
				notification("Skill Check Failed (19)", SKILL_COMMERCE); 
				dialog.text = "Die Freunde von Monsieur Fadey sind immer willkommen, aber Preise haben keine Freunde. Das werden dreitausend Pesos sein, Kapitän.";
				if (sti(pchar.Money) > 2999)
				{
					link.l1 = "Teuer, aber in Ordnung. Ich nehme es.";
					link.l1.go = "ZsI_PokupaemPistolety_2";
				}
				link.l2 = "Dreitausend? Das ist Raub! Auf Wiedersehen, Monsieur!";
				link.l2.go = "ZsI_NetDeneg";
				//Log_info("Trading skill is not sufficient");
				AddCharacterExpToSkill(pchar, "Commerce", -30);
			}
		break;
		
		case "ZsI_Torg_2":
			dialog.text = "Hab einen guten draußen, Kapitän!";
			link.l1 = "Auf Wiedersehen, Monsieur.";
			link.l1.go = "ZsI_PokupaemPistolety_3";
			AddMoneyToCharacter(pchar, -2300);
			Log_info("You have acquired the required pistols for Cocoa Leaf");
			PlaySound("Interface\important_item.wav");
		break;
		// <-- мини-квест "Знакомство с индейцами"
		
		// --> Цена чахотки
		case "Consumption":
			dialog.text = "Nein, tut es nicht... Jetzt stören Sie mich bitte nicht, ich bin ziemlich beschäftigt... Was für eine idiotische Frage...";
			link.l1 = "Ich verstehe. Entschuldigung für die Zeitverschwendung...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		// <-- Цена чахотки
		//Jason --> генератор Неудачливый вор
		case "Device_ItemTrader":
			dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Noch nie davon gehört... Was ist das eigentlich? Ich habe noch nie von so etwas in meiner ganzen Zeit gehört"+NPCharSexPhrase(npchar,"","")+".";
			link.l1 = "Nun, es ist ein Schiffsbauerwerkzeug, "+pchar.GenQuest.Device.Shipyarder.Describe+". Hat dir jemand so etwas angeboten?";
			link.l1.go = "Device_ItemTrader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_ItemTrader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 0 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 4 && npchar.location.group == "merchant" && npchar.location.locator == "merchant"+sti(pchar.GenQuest.Device.Shipyarder.Chance1))
			{
				dialog.text = "Hmm... Ja, da war ein seltsamer Kerl. Aber er hat mir nicht gesagt, was das Ding war, er hat nur versucht, es mir zu verkaufen. Aber wofür würde ich es brauchen, wenn ich keine Ahnung hätte, wofür es ist? Wie könnte ich es weiterverkaufen? Also habe ich einfach abgelehnt"+NPCharSexPhrase(npchar,"","")+", und er ging weg";
				link.l1 = "Und wie sah er aus und wohin ist er gegangen? Ich brauche dieses Instrument dringend.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Nein, nichts dergleichen. Tut mir leid, ich kann Ihnen nicht helfen. Fragen Sie herum.";
				link.l1 = "Ich verstehe. Nun, es ist Zeit, sich umzuhören!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор
		
		// Мангароса
		case "mangarosa":
			// тут работает везение
			if (sti(pchar.questTemp.Mangarosa.m_count) == 5 || GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 10+hrand(30)+hrand(40, "1"))
			{
				dialog.text = "Zeig es mir... Ja, das ist eine interessante Pflanze. Und eine sehr, sehr seltene. Sie wird Manga Rosa genannt. Ich weiß nicht, wofür sie verwendet wird, aber es gab eine interessante Tatsache dazu...";
				link.l1 = "Was meinst du?";
				link.l1.go = "mangarosa_1";
			}
			else
			{
				dialog.text = LinkRandPhrase("Zeig es mir... Ja, das ist eine interessante Pflanze. Aber leider kann ich dir nicht mehr darüber sagen. Wenn sie tatsächlich für irgendeinen Zweck verwendet wird, ist es mir unbekannt.","Lassen wir mal sehen... Hmm... Es sieht aus wie eine Heilpflanze, aber ich weiß nichts darüber. Tut mir leid, ich kann dir nicht helfen.","Wo ist es? Hmm... Nein, das habe ich noch nie gesehen. Es sieht sehr interessant aus, aber ich habe keine Ahnung, wofür es verwendet wird...");
				link.l1 = "Ich verstehe. Nun, ich werde noch ein bisschen herumfragen. Entschuldigung.";
				link.l1.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_exit":
			DialogExit();
			pchar.questTemp.Mangarosa.m_count = sti(pchar.questTemp.Mangarosa.m_count)+1;
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_1":
			dialog.text = "Nomadische Zigeuner und Wilde zeigen großes Interesse an diesen Pflanzen. Ich habe einmal gesehen, wie ein Zigeuner eine Handvoll Gold für nur einen solchen Stiel bezahlt hat. Aber ich habe keine Ahnung, warum sie es brauchen würden.";
			link.l1 = "Ich verstehe... Nun, es ist zumindest etwas! Jetzt weiß ich, wo ich weiter fragen kann. Vielen Dank!";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.m_count");
			pchar.questTemp.Mangarosa = "gipsy";
			AddQuestRecord("Mangarosa", "2");
		break;
		
		//--> Украденное воспоминание
		case "UV_Lavochniki_1":
    		dialog.text = "Leider, "+GetAddress_Form(NPChar)+", habe ich schon lange keine wertvollen Stücke mehr auf Lager gehabt. Wisst Ihr, die Nachfrage ist heutzutage gering. Einfaches Volk kauft nur billigen Tand, und die feine Gesellschaft verirrt sich kaum in mein Geschäft.";
    		link.l1 = "Schon gut...";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki");
			pchar.questTemp.UV_Lavochniki_2 = true;
			npchar.quest.UV_Vopros;
 		break;
		
		case "UV_Lavochniki_2":
    		dialog.text = "Tut mir leid, Kapitän, aber mit solcher Ware handle ich schon lange nicht mehr. Wohlhabende Kunden betreten meinen Laden nur selten, und das gewöhnliche Volk kauft nur das, was es sich leisten kann.";
    		link.l1 = "Schon gut...";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki_2");
			pchar.questTemp.UV_Lavochniki_3 = true;
			npchar.quest.UV_Vopros;
 		break;
		
		case "UV_Lavochniki_3":
    		dialog.text = "Kapitän, leider kommen Sie ein wenig zu spät... Vor ein paar Stunden habe ich eine prächtige Halskette an einen wohlhabenden Kapitän verkauft. Ich bekomme manchmal Stücke, die selbst die widerspenstigste Dame bezaubern können\nKommen Sie morgen wieder vorbei, vielleicht kann Giselle... ähm... meine Lieferanten... etwas Passendes für Sie auftreiben, das das Herz jeder Dame erobern wird.";
    		link.l1 = "Ich habe keine Zeit. Ich brauche dieses Schmuckstück sofort. Sagt mir den Namen des Kapitäns, an den Ihr die Halskette verkauft habt.";
    		link.l1.go = "UV_Lavochniki_3_1";
 		break;
		
		case "UV_Lavochniki_3_1":
    		dialog.text = "Tristan Renier, Kapitän der 'Golden Seagull'. Sein Schiff liegt noch im Hafen. Doch ich bezweifle, dass er sich freiwillig von dem Schmuckstück trennen wird. Falls er ablehnt, schauen Sie morgen wieder vorbei. Ich schwöre, Kapitän, Sie werden es nicht bereuen.";
    		link.l1 = "...";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki_3");
			AddDialogExitQuestFunction("UV_GoldSeagull");
 		break;
		//<-- Украденное воспоминание
		
// ======================== блок нод angry ===============>>>>>>>>>>>>>>>

////////////////////////////////////////////////////////////////////////////////////////////////
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok")
		break;

// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
