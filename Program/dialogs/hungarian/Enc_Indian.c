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
			dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("Sápadtarcú","Fehér squaw") +" akar beszélgetni?", 
				"Már megint te, "+ GetSexPhrase("sápadtarcú","fehér squaw") +".", 
				""+ GetSexPhrase("Paleface szeret beszélgetni. Úgy néz ki, mint squaw.","fehér squaw szeret beszélni.") +"",
                "Szellemek hozták nekem sápadtarcú "+ GetSexPhrase("testvért.","nôvér") +".", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Igen.", 
				"Igen, megint én.",
                "Nagyon költôi.", 
				"Én is örülök, hogy látlak.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Üdvözlégy, fehér testvér. Akarsz beszélni az indiánnal?";
				link.l1 = "Üdvözletem, a dzsungel fia. Örülök, hogy találkoztunk, de folytatnom kell az utamat.";
				link.l1.go = "exit";
				link.l2 = "Igen. Hallottam, hogy érdekes dolgokat árulsz. Van valamid eladásra?";
				link.l2.go = "select_trade";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "select_trade": //индейская торговля
			switch (hrand(7))
			{
				case 0: // торговля через интерфейс
					dialog.text = "Szerencséd van, fehér testvér. "+npchar.name+" van néhány eladó cucc. Nézd meg itt.";
					link.l1 = "Mutasd az árudat...";
					link.l1.go = "torg";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Várjatok. Van valami eladó. Ez egy Mangarosa nevû növény. Hallottam, hogy szereted ezt a növényt...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 1: // не торгует
					dialog.text = "Nem, fehér testvér. "+npchar.name+" nem kereskedik. "+npchar.name+"  egy harcos.";
					link.l1 = "Értem. Rendben, viszlát, vörös bôrû testvér.";
					link.l1.go = "exit";
				break;
				
				case 2: // жемчуг большой
					npchar.quest.item.qty = 25+hrand(25);
					npchar.quest.item.price = 30+hrand(10);
					dialog.text = ""+npchar.name+" az istenek könnyei. Nagyok, fehér testvér. Az összeg "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Meg akarod venni ôket? Eladom "+FindRussianMoneyString(sti(npchar.quest.item.price))+" egyért.";
					link.l1 = "Nem, nem érdekel.";
					link.l1.go = "exit";
					link.l2 = "Hát persze! Szívesen megveszem ôket ennyiért.";
					link.l2.go = "big_pearl";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Várj egy kicsit. Van valami eladó. Ez egy Manga Rosa nevû növény. Úgy hallottam, hogy szereted ezt a növényt...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 3: // жемчуг малый
					npchar.quest.item.qty = 40+hrand(40);
					npchar.quest.item.price = 10+hrand(5);
					dialog.text = ""+npchar.name+" az istenek könnyei. Kicsik, fehér testvér. Az összeg "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Meg akarod venni ôket? Eladom "+FindRussianMoneyString(sti(npchar.quest.item.price))+" egyért.";
					link.l1 = "Nem, nem érdekel.";
					link.l1.go = "exit";
					link.l2 = "Hát persze! Szívesen megveszem ôket ennyiért.";
					link.l2.go = "small_pearl";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Várj egy kicsit. Van valami eladó. Ez egy Manga Rosa nevû növény. Úgy hallottam, hogy szereted ezt a növényt...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 4: //золотые самородки
					npchar.quest.item.qty = 20+hrand(20);
					npchar.quest.item.price = 90+hrand(20);
					dialog.text = ""+npchar.name+" van sárga fém, amit ti sápadtarcúak nagyon szerettek. Az összeg "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Eladom csak "+FindRussianMoneyString(sti(npchar.quest.item.price))+" egyért.";
					link.l1 = "Nem, nem érdekel.";
					link.l1.go = "exit";
					link.l2 = "Hát persze! Szívesen megveszem ôket ennyiért.";
					link.l2.go = "gold";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Várj egy kicsit. Van valami eladó. Ez egy Manga Rosa nevû növény. Úgy hallottam, hogy szereted ezt a növényt...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 5: // серебряные самородки
					npchar.quest.item.qty = 40+hrand(40);
					npchar.quest.item.price = 40+hrand(10);
					dialog.text = ""+npchar.name+" fehér fém, amit ti sápadtarcúak nagyon szerettek. Az összeg "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Eladom csak "+FindRussianMoneyString(sti(npchar.quest.item.price))+" egyért.";
					link.l1 = "Nem, nem érdekel.";
					link.l1.go = "exit";
					link.l2 = "Hát persze! Szívesen megveszem ôket ennyiért.";
					link.l2.go = "silver";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Várj egy kicsit. Van valami eladó. Ez egy Manga Rosa nevû növény. Úgy hallottam, hogy szereted ezt a növényt...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 6: // повтор через интерфейс
					dialog.text = "Szerencséd van, fehér testvér. "+npchar.name+" van néhány eladó cucc. Nézd meg itt.";
					link.l1 = "Mutasd az árudat...";
					link.l1.go = "torg";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Várj egy kicsit. Van valami eladó. Ez egy Manga Rosa nevû növény. Úgy hallottam, hogy szereted ezt a növényt...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 7: // повтор не торгует
					dialog.text = "Nem, fehér testvér. "+npchar.name+"  nem kereskedik. "+npchar.name+" - egy harcos.";
					link.l1 = "Értem. Rendben, viszlát, vörös bôrû testvér.";
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
			dialog.text = "Hány könnyet akarsz venni?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "big_pearl_qty";
		break;
		
		case "big_pearl_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Viccelsz, sápadtarcú? Nincs szükséged istenek könnyeire? Akkor viszlát.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Mondtam, hogy hány könnyem van. Indiánokkal viccelsz, sápadtarcú? Akkor viszlát.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" könnyek? Rendben, rendben. Adj nekem " + FindRussianMoneyString(sti(npchar.quest.item.Summ)) + ", fehér testvér.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Itt a pénzed, vörös bôrû testvér.";
				link.l1.go = "big_pearl_1";
			}
			link.l2 = "Most nincs elég pénzem. Sajnálom, nem tudom megvenni a gyöngyeidet.";
			link.l2.go = "exit";
		break;
		
		case "big_pearl_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry52", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Vedd el, fehér testvér. Most már a tiéd.";
			link.l1 = "Köszönjük!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// малый жемчуг
		case "small_pearl":
			dialog.text = "Hány könnyet akarsz venni?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "small_pearl_qty";
		break;
		
		case "small_pearl_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Viccelsz, sápadtarcú? Nincs szükséged istenek könnyeire? Akkor viszlát.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Mondtam, hogy hány könnyem van. Indiánokkal viccelsz, sápadtarcú? Akkor viszlát.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" könnyek? Rendben, rendben. Adj nekem " + FindRussianMoneyString(sti(npchar.quest.item.Summ)) + ", fehér testvér.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Itt a pénzed, vörös bôrû testvér.";
				link.l1.go = "small_pearl_1";
			}
			link.l2 = "Most nincs elég pénzem. Sajnálom, nem tudom megvenni a gyöngyeidet.";
			link.l2.go = "exit";
		break;
		
		case "small_pearl_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry53", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Vedd el, fehér testvér. Most már a tiéd.";
			link.l1 = "Köszönjük!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// золотые самородки
		case "gold":
			dialog.text = "Mennyit akarsz venni?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "gold_qty";
		break;
		
		case "gold_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Viccelsz, sápadtarcú? Nincs szükséged fémre? Akkor viszlát.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Mondtam, hogy mennyi van. Indiánnal viccelsz, sápadtarcú? Akkor viszlát.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" darabokat? Nos, tôled " + FindRussianMoneyString(sti(npchar.quest.item.Summ)) + ", fehér testvér.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Itt a pénzed, vörös bôrû testvér.";
				link.l1.go = "gold_1";
			}
			link.l2 = "Most nincs elég pénzem. Sajnálom, nem tudom megvenni az aranyadat.";
			link.l2.go = "exit";
		break;
		
		case "gold_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry5", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Vedd el, fehér testvér. Most már a tiéd.";
			link.l1 = "Köszönjük!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// серебряные самородки
		case "silver":
			dialog.text = "Mennyit akarsz venni?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "silver_qty";
		break;
		
		case "silver_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Viccelsz, sápadtarcú? Nincs szükséged fémre? Akkor viszlát.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Mondtam, hogy mennyi van. Indiánnal viccelsz, sápadtarcú? Akkor viszlát.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" darabokat? Nos, tôled " + FindRussianMoneyString(sti(npchar.quest.item.Summ)) + ", fehér testvér.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Itt a pénzed, vörös bôrû testvér.";
				link.l1.go = "silver_1";
			}
			link.l2 = "Most nincs elég pénzem. Sajnálom, nem tudom megvenni az ezüstötöket.";
			link.l2.go = "exit";
		break;
		
		case "silver_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry6", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Vedd el, fehér testvér. Most már a tiéd.";
			link.l1 = "Köszönjük!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// мангароса
		case "mangarosa":
			dialog.text = "Mangarosa? Látni akarom.";
			link.l1 = "Tessék, nézze meg...";
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			npchar.quest.mangarosa = "indian_"+(hrand(10)+1);
			dialog.text = "Igen, ez az egyik neve - Rózsaszín Mangó. Adok neked egy amulettet érte. Nagyon jó amulett, a neve - "+XI_ConvertString(npchar.quest.mangarosa)+". Eladod?";
			link.l1 = "Figyelj, vörösbôrû testvér, szeretnék többet megtudni errôl a növényrôl. Elmondanád, hogy miért van rá szükséged?";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			dialog.text = ""+npchar.name+" Nem értem. Ha cserélni akarsz, adok neked egy amulettet Manga Rrosa-ért. Ha nem, akkor elmegyek.";
			link.l1 = "Ó, hát akkor... Akkor cseréljünk.";
			link.l1.go = "mangarosa_3";
			link.l2 = "Nem. Nem adom oda ezt a növényt egy amulettért.";
			link.l2.go = "exit";
		break;
		
		case "mangarosa_3":
			Log_Info("Kaptál egy amulettet");
			GiveItem2Character(pchar, npchar.quest.mangarosa);
			RemoveItems(pchar, "cannabis7", 1);
			dialog.text = "Vegye a "+XI_ConvertString(npchar.quest.mangarosa)+". Hasznos lehet.";
			link.l1 = "Semmi kétség. Sok szerencsét neked, vörös bôrû barátom.";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Ne kísértsd a sorsot, sápadtarcú! Tedd el a kardod!", "Figyelj, sápadtarcú, rejtsd el a fegyvered, és hagyj minket beszélgetni, nem kell semmi gond.");
			link.l1 = LinkRandPhrase("Jól van.", "Rendben.", "Ahogy mondod...");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
