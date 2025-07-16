//Jason диалог индейцев в джунглях
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int iQty;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Bleichgesicht","Weiße Squaw")+" möchte sprechen?","Du schon wieder, "+GetSexPhrase("bleichgesicht","weiße Squaw")+".",""+GetSexPhrase("Bleichgesicht mag es zu reden. Er sieht aus wie eine Squaw.","Die weiße Squaw redet gern.")+"","Geister haben mir Bleichgesicht gebracht "+GetSexPhrase("Bruder.","Schwester")+".","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ja.","Ja, ich schon wieder.","Sehr poetisch.","Ich bin auch froh, dich zu sehen.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Sei gegrüßt, weißer Bruder. Du willst mit Indianer sprechen?";
				link.l1 = "Grüße, Sohn des Dschungels. Ich freue mich, dich zu treffen, aber ich muss meine Reise fortsetzen.";
				link.l1.go = "exit";
				link.l2 = "Ja. Ich habe gehört, dass Sie interessante Dinge verkaufen. Haben Sie etwas zum Verkauf?";
				link.l2.go = "select_trade";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "select_trade": //индейская торговля
			switch (hrand(7))
			{
				case 0: // торговля через интерфейс
					dialog.text = "Du hast Glück, weißer Bruder. "+npchar.name+" hat einiges zum Verkauf. Schau mal hier.";
					link.l1 = "Zeig deine Waren...";
					link.l1.go = "torg";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Halt. Ich habe etwas zu verkaufen. Es ist eine Pflanze namens Mangarosa. Ich habe gehört, dass du ein Fan von diesem Zeug bist...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 1: // не торгует
					dialog.text = "Nein, weißer Bruder. "+npchar.name+" handelt nicht. "+npchar.name+"  ist ein Krieger.";
					link.l1 = "Ich verstehe. Nun, lebewohl, rot-häutiger Bruder.";
					link.l1.go = "exit";
				break;
				
				case 2: // жемчуг большой
					npchar.quest.item.qty = 25+hrand(25);
					npchar.quest.item.price = 30+hrand(10);
					dialog.text = ""+npchar.name+" hat Tränen der Götter. Große, weißer Bruder. In der Menge von "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Wollen Sie sie kaufen? Ich verkaufe für "+FindRussianMoneyString(sti(npchar.quest.item.price))+" für einen.";
					link.l1 = "Nein, ich bin nicht interessiert.";
					link.l1.go = "exit";
					link.l2 = "Natürlich! Ich kaufe sie gerne zu diesem Preis.";
					link.l2.go = "big_pearl";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Halt ein. Ich habe etwas zum Verkauf. Es ist eine Pflanze namens Manga Rosa. Ich habe gehört, dass du ein Fan von diesem Zeug bist...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 3: // жемчуг малый
					npchar.quest.item.qty = 40+hrand(40);
					npchar.quest.item.price = 10+hrand(5);
					dialog.text = ""+npchar.name+" hat Tränen der Götter. Kleine, weißer Bruder. In der Menge von "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Wollen Sie sie kaufen? Ich verkaufe für "+FindRussianMoneyString(sti(npchar.quest.item.price))+" für einen.";
					link.l1 = "Nein, ich bin nicht interessiert.";
					link.l1.go = "exit";
					link.l2 = "Natürlich! Ich kaufe sie gerne für diesen Preis.";
					link.l2.go = "small_pearl";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Halt ein. Ich habe etwas zum Verkauf. Es ist eine Pflanze namens Manga Rosa. Ich habe gehört, dass du ein Fan von diesem Zeug bist...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 4: //золотые самородки
					npchar.quest.item.qty = 20+hrand(20);
					npchar.quest.item.price = 90+hrand(20);
					dialog.text = ""+npchar.name+" hat gelbes Metall, das ihr Bleichgesichter sehr liebt. In der Menge von "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Ich verkaufe nur für "+FindRussianMoneyString(sti(npchar.quest.item.price))+" für einen.";
					link.l1 = "Nein, ich bin nicht interessiert.";
					link.l1.go = "exit";
					link.l2 = "Natürlich! Ich kaufe sie gerne zu einem solchen Preis.";
					link.l2.go = "gold";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Halt ein. Ich habe etwas zum Verkauf. Es ist eine Pflanze namens Manga Rosa. Ich habe gehört, dass du diese Sachen magst...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 5: // серебряные самородки
					npchar.quest.item.qty = 40+hrand(40);
					npchar.quest.item.price = 40+hrand(10);
					dialog.text = ""+npchar.name+" hat weißes Metall, das ihr Bleichgesichter sehr liebt. In der Menge von "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Ich verkaufe nur für "+FindRussianMoneyString(sti(npchar.quest.item.price))+" für einen.";
					link.l1 = "Nein, ich bin nicht interessiert.";
					link.l1.go = "exit";
					link.l2 = "Natürlich! Ich kaufe sie gerne zu diesem Preis.";
					link.l2.go = "silver";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Halt ein. Ich habe etwas zum Verkauf. Es ist eine Pflanze namens Manga Rosa. Ich habe gehört, dass du ein Fan von diesem Zeug bist...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 6: // повтор через интерфейс
					dialog.text = "Du hast Glück, weißer Bruder. "+npchar.name+" hat einige Sachen zum Verkauf. Schau mal hier.";
					link.l1 = "Zeig deine Waren...";
					link.l1.go = "torg";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Halt ein. Ich habe etwas zum Verkauf. Es ist eine Pflanze namens Manga Rosa. Ich habe gehört, dass du ein Fan von diesem Zeug bist...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 7: // повтор не торгует
					dialog.text = "Nein, weißer Bruder. "+npchar.name+"  handelt nicht. "+npchar.name+" -  ist ein Krieger.";
					link.l1 = "Ich verstehe. Nun, leb wohl, rothäutiger Bruder.";
					link.l1.go = "exit";
				break;
			}
		break;
		
		case "torg":
			DialogExit();
			if (CheckNPCQuestDate(npchar, "Torg_date"))
			{
                SetNPCQuestDate(npchar, "Torg_date");
				GiveItemToTrader(npchar);
			}
			NextDiag.CurrentNode = "First time";
			LaunchItemsTrade(NPChar, 0);
			ChangeIndianRelation(1.00);
		break;
		
		// большой жемчуг
		case "big_pearl":
			dialog.text = "Wie viele Tränen möchten Sie kaufen?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "big_pearl_qty";
		break;
		
		case "big_pearl_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Du scherzt, Bleichgesicht? Du brauchst keine Tränen der Götter? Dann Tschüss.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Ich habe dir gesagt, wie viele Tränen ich habe. Du machst Witze mit dem Indianer, Bleichgesicht? Dann auf Wiedersehen.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" Tränen? In Ordnung. Du gibst mir "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", weißer Bruder.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Hier ist dein Geld, rothäutiger Bruder.";
				link.l1.go = "big_pearl_1";
			}
			link.l2 = "Ich habe gerade nicht genug Geld. Es tut mir leid, ich kann deine Perlen nicht kaufen.";
			link.l2.go = "exit";
		break;
		
		case "big_pearl_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry52", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Nimm sie, weißer Bruder. Sie gehören jetzt dir.";
			link.l1 = "Danke!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// малый жемчуг
		case "small_pearl":
			dialog.text = "Wie viele Tränen wollen Sie kaufen?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "small_pearl_qty";
		break;
		
		case "small_pearl_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Du scherzt, Bleichgesicht? Du brauchst keine Tränen der Götter? Dann auf Wiedersehen.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Ich habe dir gesagt, wie viele Tränen ich habe. Du machst Witze mit dem Indianer, Bleichgesicht? Dann Tschüss.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" Tränen? In Ordnung. Du gibst mir "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", weißer Bruder.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Hier ist dein Geld, rothäutiger Bruder.";
				link.l1.go = "small_pearl_1";
			}
			link.l2 = "Ich habe im Moment nicht genug Geld. Es tut mir leid, ich kann deine Perlen nicht kaufen.";
			link.l2.go = "exit";
		break;
		
		case "small_pearl_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry53", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Nimm sie, weißer Bruder. Sie gehören jetzt dir.";
			link.l1 = "Danke!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// золотые самородки
		case "gold":
			dialog.text = "Wie viele möchten Sie kaufen?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "gold_qty";
		break;
		
		case "gold_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Du scherzt, Bleichgesicht? Du brauchst kein Metall? Dann tschüss.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Ich habe dir gesagt, wie viele ich habe. Du machst Witze mit dem Indianer, Bleichgesicht? Dann auf Wiedersehen.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" Brocken? Nun, von dir "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", weißer Bruder.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Hier ist dein Geld, rothäutiger Bruder.";
				link.l1.go = "gold_1";
			}
			link.l2 = "Ich habe im Moment nicht genug Geld. Es tut mir leid, ich kann dein Gold nicht kaufen.";
			link.l2.go = "exit";
		break;
		
		case "gold_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry5", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Nimm sie, weißer Bruder. Sie gehören jetzt dir.";
			link.l1 = "Danke!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// серебряные самородки
		case "silver":
			dialog.text = "Wie viele wollen Sie kaufen?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "silver_qty";
		break;
		
		case "silver_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Du scherzest, Bleichgesicht? Du brauchst kein Metall? Dann auf Wiedersehen.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Ich habe dir gesagt, wie viele ich habe. Du scherzt mit Indianer, Bleichgesicht? Dann auf Wiedersehen.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" Stücke? Nun, von dir "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", weißer Bruder.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Hier ist dein Geld, rot-häutiger Bruder.";
				link.l1.go = "silver_1";
			}
			link.l2 = "Ich habe gerade nicht genug Geld. Es tut mir leid, ich kann dein Silber nicht kaufen.";
			link.l2.go = "exit";
		break;
		
		case "silver_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry6", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Nimm sie, weißer Bruder. Sie gehören jetzt dir.";
			link.l1 = "Danke!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// мангароса
		case "mangarosa":
			dialog.text = "Mangarosa? Ich will es sehen.";
			link.l1 = "Hier, schau mal...";
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			npchar.quest.mangarosa = "indian_"+(hrand(10)+1);
			dialog.text = "Ja. Das ist ein Name, den es hat - Manga Rosa. Ich gebe dir ein Amulett dafür. Sehr gutes Amulett, es hat einen Namen - "+XI_ConvertString(npchar.quest.mangarosa)+". Handelst du?";
			link.l1 = "Hör zu, rothäutiger Bruder, ich würde gerne mehr über diese Pflanze erfahren. Kannst du mir sagen, warum du sie so dringend brauchst?";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			dialog.text = ""+npchar.name+" nicht verstehen. Wenn du handeln willst, gebe ich dir Amulett für Manga Rrosa. Wenn nicht, dann gehe ich.";
			link.l1 = "Oh, na gut. Lass uns handeln.";
			link.l1.go = "mangarosa_3";
			link.l2 = "Nein. Ich werde diese Pflanze nicht für ein Amulett hergeben.";
			link.l2.go = "exit";
		break;
		
		case "mangarosa_3":
			Log_Info("You have received an amulet");
			GiveItem2Character(pchar, npchar.quest.mangarosa);
			RemoveItems(pchar, "cannabis7", 1);
			dialog.text = "Nimm dein "+XI_ConvertString(npchar.quest.mangarosa)+". Es könnte nützlich sein.";
			link.l1 = "Kein Zweifel daran. Viel Glück für dich, rothäutiger Freund.";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Versuch nicht dein Glück, Bleichgesicht! Steck dein Schwert weg!","Hör zu, Bleichgesicht, versteck deine Waffe und lass uns reden, ich brauche keine Probleme.");
			link.l1 = LinkRandPhrase("Gut.","Gut.","Wie du sagst...");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
