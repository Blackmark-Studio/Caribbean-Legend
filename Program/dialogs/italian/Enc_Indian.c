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
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Viso pallido","Bianca squaw")+" vuole parlare?","Di nuovo tu, "+GetSexPhrase("viso pallido","squaw bianca")+".",""+GetSexPhrase("Viso Pallido ama parlare. Sembra una squaw.","La squaw bianca ama parlare.")+"","Gli spiriti mi hanno portato il viso pallido "+GetSexPhrase("fratello.","sorella")+".","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sì.","Sì, sono ancora io.","Molto poetico.","Sono anche felice di vederti.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Salve, fratello bianco. Vuoi parlare con l'indiano?";
				link.l1 = "Saluti, figlio della giungla. Sono lieto di incontrarti, ma devo continuare il mio viaggio.";
				link.l1.go = "exit";
				link.l2 = "Sì. Ho sentito dire che vendi cose interessanti. Hai qualcosa in vendita?";
				link.l2.go = "select_trade";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "select_trade": //индейская торговля
			switch (hrand(7))
			{
				case 0: // торговля через интерфейс
					dialog.text = "Sei fortunato, fratello bianco. "+npchar.name+" ha alcune cose in vendita. Guarda qui.";
					link.l1 = "Mostra le tue merci...";
					link.l1.go = "torg";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Aspetta. Ho qualcosa in vendita. È una pianta chiamata Mangarosa. Ho sentito dire che sei un amante di queste cose...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 1: // не торгует
					dialog.text = "No, fratello bianco. "+npchar.name+" non commercia. "+npchar.name+"  è un guerriero.";
					link.l1 = "Capisco. Bene, addio, fratello dalla pelle rossa.";
					link.l1.go = "exit";
				break;
				
				case 2: // жемчуг большой
					npchar.quest.item.qty = 25+hrand(25);
					npchar.quest.item.price = 30+hrand(10);
					dialog.text = ""+npchar.name+" ha le lacrime degli dei. Grandi, fratello bianco. Nella quantità di "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Vuoi comprarli? Io vendo per "+FindRussianMoneyString(sti(npchar.quest.item.price))+"per uno.";
					link.l1 = "No, non sono interessato.";
					link.l1.go = "exit";
					link.l2 = "Certo! Li comprerò volentieri a un tale prezzo.";
					link.l2.go = "big_pearl";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Aspetta un attimo. Ho qualcosa in vendita. È una pianta chiamata Manga Rosa. Ho sentito dire che sei appassionato di queste cose...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 3: // жемчуг малый
					npchar.quest.item.qty = 40+hrand(40);
					npchar.quest.item.price = 10+hrand(5);
					dialog.text = ""+npchar.name+" ha le lacrime degli dei. Piccole, fratello bianco. Nella quantità di "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Vuoi comprarli? Io vendo per "+FindRussianMoneyString(sti(npchar.quest.item.price))+"per uno.";
					link.l1 = "No, non sono interessato.";
					link.l1.go = "exit";
					link.l2 = "Certo! Li comprerò volentieri a questo prezzo.";
					link.l2.go = "small_pearl";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Aspetta. Ho qualcosa in vendita. È una pianta chiamata Manga Rosa. Ho sentito dire che sei appassionato di queste cose...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 4: //золотые самородки
					npchar.quest.item.qty = 20+hrand(20);
					npchar.quest.item.price = 90+hrand(20);
					dialog.text = ""+npchar.name+" ha del metallo giallo che voi visi pallidi amate tanto. Nella quantità di "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Vendo solo per "+FindRussianMoneyString(sti(npchar.quest.item.price))+" per uno.";
					link.l1 = "No, non sono interessato.";
					link.l1.go = "exit";
					link.l2 = "Certo! Li comprerò volentieri per un prezzo del genere.";
					link.l2.go = "gold";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Aspetta. Ho qualcosa in vendita. È una pianta chiamata Manga Rosa. Ho sentito dire che ti piace questa roba...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 5: // серебряные самородки
					npchar.quest.item.qty = 40+hrand(40);
					npchar.quest.item.price = 40+hrand(10);
					dialog.text = ""+npchar.name+" ha del metallo bianco che voi visi pallidi amate molto. Nella quantità di "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Vendo solo per "+FindRussianMoneyString(sti(npchar.quest.item.price))+" per uno.";
					link.l1 = "No, non sono interessato.";
					link.l1.go = "exit";
					link.l2 = "Certo! Li comprerò volentieri per un tale prezzo.";
					link.l2.go = "silver";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Aspetta. Ho qualcosa in vendita. È una pianta chiamata Manga Rosa. Ho sentito dire che sei un amante di queste cose...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 6: // повтор через интерфейс
					dialog.text = "Sei in fortuna, fratello bianco. "+npchar.name+" ha qualche roba in vendita. Guarda qui.";
					link.l1 = "Mostra le tue merci...";
					link.l1.go = "torg";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Aspetta. Ho qualcosa in vendita. È una pianta chiamata Manga Rosa. Ho sentito dire che sei appassionato di queste cose...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 7: // повтор не торгует
					dialog.text = "No, fratello bianco."+npchar.name+"  non commercia. "+npchar.name+" -  è un guerriero.";
					link.l1 = "Capisco. Bene, addio, fratello dalla pelle rossa.";
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
			dialog.text = "Quante lacrime vuoi comprare?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "big_pearl_qty";
		break;
		
		case "big_pearl_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Scherzi, viso pallido? Non hai bisogno delle lacrime degli dei? Allora addio.";
				link.l1 = "Mmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Ti ho detto quante lacrime ho. Scherzi con l'indiano, viso pallido? Allora arrivederci.";
				link.l1 = "Uhm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" lacrime? Va bene. Mi dai "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", fratello bianco.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Ecco i tuoi soldi, fratello dalla pelle rossa.";
				link.l1.go = "big_pearl_1";
			}
			link.l2 = "Non ho abbastanza soldi al momento. Mi dispiace, non posso comprare le tue perle.";
			link.l2.go = "exit";
		break;
		
		case "big_pearl_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry52", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Prendili, fratello bianco. Ora sono tuoi.";
			link.l1 = "Grazie!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// малый жемчуг
		case "small_pearl":
			dialog.text = "Quante lacrime vuoi comprare?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "small_pearl_qty";
		break;
		
		case "small_pearl_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Scherzi, viso pallido? Non hai bisogno delle lacrime degli dei? Allora, addio.";
				link.l1 = "Mmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Ti ho detto quante lacrime ho. Scherzi con l'indiano, viso pallido? Allora addio.";
				link.l1 = "Mmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" lacrime? Va bene. Mi dai "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", fratello bianco.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Ecco i tuoi soldi, fratello dalla pelle rossa.";
				link.l1.go = "small_pearl_1";
			}
			link.l2 = "Non ho abbastanza soldi al momento. Mi dispiace, non posso comprare le tue perle.";
			link.l2.go = "exit";
		break;
		
		case "small_pearl_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry53", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Prendili, fratello bianco. Sono tuoi ora.";
			link.l1 = "Grazie!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// золотые самородки
		case "gold":
			dialog.text = "Quanti ne vuoi comprare?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "gold_qty";
		break;
		
		case "gold_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Scherzi, viso pallido? Non hai bisogno di metallo? Allora arrivederci.";
				link.l1 = "Mmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Ti ho detto quanti ne ho. Scherzi con l'indiano, viso pallido? Allora addio.";
				link.l1 = "Mmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" pezzi? Beh, da te "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", fratello bianco.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Ecco i tuoi soldi, fratello dalla pelle rossa.";
				link.l1.go = "gold_1";
			}
			link.l2 = "Non ho abbastanza soldi ora. Mi dispiace, non posso comprare il tuo oro.";
			link.l2.go = "exit";
		break;
		
		case "gold_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry5", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Prendili, fratello bianco. Ora sono tuoi.";
			link.l1 = "Grazie!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// серебряные самородки
		case "silver":
			dialog.text = "Quanti ne vuoi comprare?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "silver_qty";
		break;
		
		case "silver_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Scherzi, viso pallido? Non hai bisogno di metallo? Allora addio.";
				link.l1 = "Mmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Ti ho detto quanti ne ho. Scherzi con l'indiano, viso pallido? Allora addio.";
				link.l1 = "Mmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" pezzi? Beh, da te "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", fratello bianco.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Ecco i tuoi soldi, fratello dalla pelle rossa.";
				link.l1.go = "silver_1";
			}
			link.l2 = "Non ho abbastanza soldi al momento. Mi dispiace, non posso comprare il tuo argento.";
			link.l2.go = "exit";
		break;
		
		case "silver_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry6", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Prendili, fratello bianco. Ora sono tuoi.";
			link.l1 = "Grazie!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// мангароса
		case "mangarosa":
			dialog.text = "Mangarosa? Voglio vederla.";
			link.l1 = "Ecco, dai un'occhiata...";
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			npchar.quest.mangarosa = "indian_"+(hrand(10)+1);
			dialog.text = "Sì. Questo è uno dei nomi che ha - Manga Rosa. Ti do un amuleto per questo. Un ottimo amuleto, ha un nome - "+XI_ConvertString(npchar.quest.mangarosa)+". Fai commercio?";
			link.l1 = "Ascolta, fratello dalla pelle rossa, vorrei saperne di più su questa pianta. Mi dirai perché ne hai tanto bisogno?";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			dialog.text = ""+npchar.name+" non capire. Se vuoi commerciare, ti do l'amuleto per Manga Rrosa. Se no, allora me ne vado.";
			link.l1 = "Oh, va bene. Facciamo uno scambio.";
			link.l1.go = "mangarosa_3";
			link.l2 = "No. Non darò via questa pianta per un amuleto.";
			link.l2.go = "exit";
		break;
		
		case "mangarosa_3":
			Log_Info("You have received an amulet");
			GiveItem2Character(pchar, npchar.quest.mangarosa);
			RemoveItems(pchar, "cannabis7", 1);
			dialog.text = "Prendi il tuo "+XI_ConvertString(npchar.quest.mangarosa)+". Potrebbe essere utile.";
			link.l1 = "Non c'è dubbio. Buona fortuna a te, amico dalla pelle rossa.";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Non tentare il destino, viso pallido! Metti via la tua spada!","Ascolta pallido, nascondi la tua arma e parliamo, non ho bisogno di problemi.");
			link.l1 = LinkRandPhrase("Bene.","Bene.","Come dici tu...");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
