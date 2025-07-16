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
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Białotwarz","Biała squaw")+" chce rozmawiać?","Znowu ty, "+GetSexPhrase("blada twarz","biała squaw")+".",""+GetSexPhrase("Biały lubi gadać. Wygląda jak squaw.","Biała squaw lubi rozmawiać.")+"","Duchy przyprowadziły mi bladą twarz "+GetSexPhrase("brat.","siostra")+".","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tak.","Tak, to znowu ja.","Bardzo poetycko.","Ja również cieszę się, że cię widzę.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Cześć, biały bracie. Chcesz rozmawiać z Indianinem?";
				link.l1 = "Pozdrowienia, synu dżungli. Cieszę się z naszego spotkania, ale muszę kontynuować moją podróż.";
				link.l1.go = "exit";
				link.l2 = "Tak. Słyszałem, że sprzedajesz ciekawe rzeczy. Masz coś na sprzedaż?";
				link.l2.go = "select_trade";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "select_trade": //индейская торговля
			switch (hrand(7))
			{
				case 0: // торговля через интерфейс
					dialog.text = "Masz szczęście, biały bracie."+npchar.name+" ma trochę rzeczy na sprzedaż. Spójrz tutaj.";
					link.l1 = "Pokaż swoje towary...";
					link.l1.go = "torg";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Zaczekaj. Mam coś na sprzedaż. To roślina zwana Mangarosa. Słyszałem, że lubisz takie rzeczy...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 1: // не торгует
					dialog.text = "Nie, biały bracie."+npchar.name+" nie handluje. "+npchar.name+"  to jest wojownik.";
					link.l1 = "Rozumiem. Dobrze, na razie, bracie o czerwonej skórze.";
					link.l1.go = "exit";
				break;
				
				case 2: // жемчуг большой
					npchar.quest.item.qty = 25+hrand(25);
					npchar.quest.item.price = 30+hrand(10);
					dialog.text = ""+npchar.name+" ma łzy bogów. Duże, biały bracie. W ilości "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Chcesz je kupić? Sprzedam za "+FindRussianMoneyString(sti(npchar.quest.item.price))+" za jednego.";
					link.l1 = "Nie, nie jestem zainteresowany.";
					link.l1.go = "exit";
					link.l2 = "Oczywiście! Z przyjemnością kupię je za taką cenę.";
					link.l2.go = "big_pearl";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Zaczekaj. Mam coś na sprzedaż. To roślina zwana Manga Rosa. Słyszałem, że lubisz takie rzeczy...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 3: // жемчуг малый
					npchar.quest.item.qty = 40+hrand(40);
					npchar.quest.item.price = 10+hrand(5);
					dialog.text = ""+npchar.name+" ma łzy bogów. Małe, biały bracie. W ilości "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Chcesz je kupić? Sprzedam za "+FindRussianMoneyString(sti(npchar.quest.item.price))+"za jednego.";
					link.l1 = "Nie, nie jestem zainteresowany.";
					link.l1.go = "exit";
					link.l2 = "Oczywiście! Z przyjemnością kupię je za taką cenę.";
					link.l2.go = "small_pearl";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Zaczekaj. Mam coś na sprzedaż. To roślina zwana Manga Rosa. Słyszałem, że lubisz takie rzeczy...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 4: //золотые самородки
					npchar.quest.item.qty = 20+hrand(20);
					npchar.quest.item.price = 90+hrand(20);
					dialog.text = ""+npchar.name+" ma żółty metal, który wy, blade twarze, bardzo kochacie. W ilości "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Sprzedaję tylko za "+FindRussianMoneyString(sti(npchar.quest.item.price))+" dla jednego.";
					link.l1 = "Nie, nie jestem zainteresowany.";
					link.l1.go = "exit";
					link.l2 = "Oczywiście! Chętnie kupię je za taką cenę.";
					link.l2.go = "gold";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Zaczekaj. Mam coś na sprzedaż. To roślina zwana Manga Rosa. Słyszałem, że lubisz takie rzeczy...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 5: // серебряные самородки
					npchar.quest.item.qty = 40+hrand(40);
					npchar.quest.item.price = 40+hrand(10);
					dialog.text = ""+npchar.name+" ma biały metal, który wy bladolicie bardzo kochacie. W ilości "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Sprzedaję tylko za "+FindRussianMoneyString(sti(npchar.quest.item.price))+" dla jednego.";
					link.l1 = "Nie, nie jestem zainteresowany.";
					link.l1.go = "exit";
					link.l2 = "Oczywiście! Chętnie kupię je za taką cenę.";
					link.l2.go = "silver";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Zaczekaj. Mam coś na sprzedaż. To roślina zwana Manga Rosa. Słyszałem, że jesteś miłośnikiem tego towaru...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 6: // повтор через интерфейс
					dialog.text = "Jesteś w szczęściu, biały bracie."+npchar.name+" ma coś na sprzedaż. Spójrz tutaj.";
					link.l1 = "Pokaż swoje towary...";
					link.l1.go = "torg";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Zaczekaj. Mam coś na sprzedaż. To roślina zwana Manga Rosa. Słyszałem, że lubisz takie rzeczy...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 7: // повтор не торгует
					dialog.text = "Nie, biały bracie."+npchar.name+"  nie handluje. "+npchar.name+" -  to wojownik.";
					link.l1 = "Rozumiem. Dobrze, na razie, bracie o czerwonej skórze.";
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
			dialog.text = "Ile łez chcesz kupić?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "big_pearl_qty";
		break;
		
		case "big_pearl_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Żartujesz, bladatwarz? Nie potrzebujesz łez bogów? W takim razie do widzenia.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Powiedziałem ci, ile mam łez. Żartujesz z Indianina, bladolicy? W takim razie do widzenia.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" łzy? Dobrze. Daj mi "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", biały bracie.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Tu jest twoje pieniądze, bracie o czerwonej skórze.";
				link.l1.go = "big_pearl_1";
			}
			link.l2 = "Nie mam teraz wystarczająco dużo pieniędzy. Przykro mi, nie mogę kupić twoich pereł.";
			link.l2.go = "exit";
		break;
		
		case "big_pearl_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry52", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Weź je, biały bracie. Teraz są twoje.";
			link.l1 = "Dzięki!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// малый жемчуг
		case "small_pearl":
			dialog.text = "Ile łez chcesz kupić?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "small_pearl_qty";
		break;
		
		case "small_pearl_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Żartujesz, bladotworze? Nie potrzebujesz łez bogów? W takim razie do widzenia.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Powiedziałem ci, ile mam łez. Żartujesz z Indianina, bladotwórczy? W takim razie do widzenia.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" łzy? Dobrze. Dasz mi "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", biały bracie.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Oto twoje pieniądze, bracie o czerwonej skórze.";
				link.l1.go = "small_pearl_1";
			}
			link.l2 = "Nie mam teraz wystarczająco dużo pieniędzy. Przykro mi, nie mogę kupić twoich pereł.";
			link.l2.go = "exit";
		break;
		
		case "small_pearl_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry53", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Zabierz je, biały bracie. Teraz są twoje.";
			link.l1 = "Dzięki!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// золотые самородки
		case "gold":
			dialog.text = "Ile chcesz kupić?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "gold_qty";
		break;
		
		case "gold_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Żartujesz, bladolicy? Nie potrzebujesz metalu? W takim razie do widzenia.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Powiedziałem ci, ile mam. Żartujesz z Indianina, bladolicy? W takim razie do widzenia.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" kawałki? Cóż, od ciebie "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", biały bracie.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Tu są twoje pieniądze, bracie o czerwonej skórze.";
				link.l1.go = "gold_1";
			}
			link.l2 = "Nie mam teraz wystarczająco dużo pieniędzy. Przykro mi, nie mogę kupić twojego złota.";
			link.l2.go = "exit";
		break;
		
		case "gold_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry5", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Weź ich, biały bracie. Teraz są twoi.";
			link.l1 = "Dzięki!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// серебряные самородки
		case "silver":
			dialog.text = "Ile chcesz kupić?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "silver_qty";
		break;
		
		case "silver_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Żartujesz, bladolicy? Nie potrzebujesz metalu? W takim razie do widzenia.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Powiedziałem ci, ile mam. Żartujesz z Indianina, bladolicy? W takim razie do widzenia.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" kawałki? Cóż, od ciebie "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", biały bracie.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Oto twoje pieniądze, bracie o czerwonej skórze.";
				link.l1.go = "silver_1";
			}
			link.l2 = "Nie mam teraz wystarczająco dużo pieniędzy. Przykro mi, nie mogę kupić twojego srebra.";
			link.l2.go = "exit";
		break;
		
		case "silver_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry6", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Weź je, biały bracie. Teraz są twoje.";
			link.l1 = "Dzięki!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// мангароса
		case "mangarosa":
			dialog.text = "Mangarosa? Chcę to zobaczyć.";
			link.l1 = "Tu, rzut oka...";
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			npchar.quest.mangarosa = "indian_"+(hrand(10)+1);
			dialog.text = "Tak. To jest jedna z nazw, jaką ma - Manga Rosa. Daję ci amulet na to. Bardzo dobry amulet, ma nazwę - "+XI_ConvertString(npchar.quest.mangarosa)+". Handlujesz?";
			link.l1 = "Słuchaj, czerwonoskóry bracie, chciałbym dowiedzieć się więcej o tej roślinie. Czy powiesz mi, dlaczego tak bardzo jej potrzebujesz?";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			dialog.text = ""+npchar.name+" nie rozumieć. Jeśli chcesz handlować, dam ci amulet na Manga Rrosa. Jeśli nie, to ja idę.";
			link.l1 = "Och, dobrze. Handlujmy.";
			link.l1.go = "mangarosa_3";
			link.l2 = "Nie. Nie oddam tej rośliny za amulet.";
			link.l2.go = "exit";
		break;
		
		case "mangarosa_3":
			Log_Info("You have received an amulet");
			GiveItem2Character(pchar, npchar.quest.mangarosa);
			RemoveItems(pchar, "cannabis7", 1);
			dialog.text = "Zabierz swoje "+XI_ConvertString(npchar.quest.mangarosa)+". To jest użyteczne.";
			link.l1 = "Bez wątpienia. Powodzenia tobie, przyjacielu o czerwonej skórze.";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Nie kusisz losu, bladolicy! Odłóż swój miecz!","Słuchaj bladolicy, schowaj swoją broń i porozmawiajmy, nie potrzebuję problemów.");
			link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Jak mówisz...");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
