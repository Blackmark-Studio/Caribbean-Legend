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
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Rostinho Pálido","Índia branca")+" quer conversar?","Você de novo, "+GetSexPhrase("paleface","índia branca")+".",""+GetSexPhrase("O Paleface gosta de falar. Ele parece uma índia.","Índia branca gosta de conversar.")+"","Os espíritos me trouxeram, cara-pálida "+GetSexPhrase("irmão.","irmã")+".","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sim.","Sim, sou eu de novo.","Muito poético.","Também estou feliz em te ver.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Saudações, irmão branco. Você quer falar com o índio?";
				link.l1 = "Saudações, filho da selva. Fico feliz em conhecê-lo, mas preciso continuar minha jornada.";
				link.l1.go = "exit";
				link.l2 = "Sim. Ouvi dizer que você vende coisas interessantes. Tem algo à venda?";
				link.l2.go = "select_trade";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "select_trade": //индейская торговля
			switch (hrand(7))
			{
				case 0: // торговля через интерфейс
					dialog.text = "Você está com sorte, irmão branco. "+npchar.name+" tem algumas mercadorias à venda. Dê uma olhada.";
					link.l1 = "Mostre-me o que você tem...";
					link.l1.go = "torg";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Espere. Tenho algo para vender. É uma planta chamada Mangarosa. Ouvi dizer que você gosta desse tipo de coisa...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 1: // не торгует
					dialog.text = "Não, irmão branco. "+npchar.name+" não faz comércio. "+npchar.name+"  é um guerreiro.";
					link.l1 = "Entendi. Certo, adeus, irmão de pele vermelha.";
					link.l1.go = "exit";
				break;
				
				case 2: // жемчуг большой
					npchar.quest.item.qty = 25+hrand(25);
					npchar.quest.item.price = 30+hrand(10);
					dialog.text = ""+npchar.name+" tem as lágrimas dos deuses. Grandes, irmão branco. Em quantidade de "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Você quer comprar? Eu vendo por "+FindRussianMoneyString(sti(npchar.quest.item.price))+" por um.";
					link.l1 = "Não, não estou interessado.";
					link.l1.go = "exit";
					link.l2 = "Claro! Vou comprar com prazer por esse preço.";
					link.l2.go = "big_pearl";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Espere. Tenho algo à venda. É uma planta chamada Manga Rosa. Ouvi dizer que você gosta desse tipo de coisa...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 3: // жемчуг малый
					npchar.quest.item.qty = 40+hrand(40);
					npchar.quest.item.price = 10+hrand(5);
					dialog.text = ""+npchar.name+" tem as lágrimas dos deuses. Pequenas, irmão branco. Em quantidade de "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Quer comprar? Eu vendo por "+FindRussianMoneyString(sti(npchar.quest.item.price))+" por um.";
					link.l1 = "Não, não estou interessado.";
					link.l1.go = "exit";
					link.l2 = "Claro! Vou comprar com prazer por esse preço.";
					link.l2.go = "small_pearl";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Espere. Tenho algo para vender. É uma planta chamada Manga Rosa. Ouvi dizer que você gosta desse tipo de coisa...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 4: //золотые самородки
					npchar.quest.item.qty = 20+hrand(20);
					npchar.quest.item.price = 90+hrand(20);
					dialog.text = ""+npchar.name+" tem o metal amarelo que vocês, rostos pálidos, adoram tanto. Em quantidade de "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Eu só vendo por "+FindRussianMoneyString(sti(npchar.quest.item.price))+" por uma.";
					link.l1 = "Não, não estou interessado.";
					link.l1.go = "exit";
					link.l2 = "Claro! Vou comprar com prazer por esse preço.";
					link.l2.go = "gold";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Espere. Tenho algo para vender. É uma planta chamada Manga Rosa. Ouvi dizer que você gosta desse tipo de coisa...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 5: // серебряные самородки
					npchar.quest.item.qty = 40+hrand(40);
					npchar.quest.item.price = 40+hrand(10);
					dialog.text = ""+npchar.name+" tem aquele metal branco que vocês, branquelos, tanto adoram. Em quantidade de "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Eu só vendo por "+FindRussianMoneyString(sti(npchar.quest.item.price))+" por uma.";
					link.l1 = "Não, não estou interessado.";
					link.l1.go = "exit";
					link.l2 = "Claro! Vou comprar com prazer por esse preço.";
					link.l2.go = "silver";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Espere. Tenho algo para vender. É uma planta chamada Manga Rosa. Ouvi dizer que você gosta dessas coisas...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 6: // повтор через интерфейс
					dialog.text = "Você está com sorte, irmão branco. "+npchar.name+" tem algumas mercadorias à venda. Dê uma olhada.";
					link.l1 = "Mostre-me o que você tem...";
					link.l1.go = "torg";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Espere. Tenho algo para vender. É uma planta chamada Manga Rosa. Ouvi dizer que você gosta desse tipo de coisa...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 7: // повтор не торгует
					dialog.text = "Não, irmão branco. "+npchar.name+"  não faz comércio. "+npchar.name+" -  é um guerreiro.";
					link.l1 = "Entendi. Certo, adeus, irmão de pele vermelha.";
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
			dialog.text = "Quantas lágrimas você quer comprar?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "big_pearl_qty";
		break;
		
		case "big_pearl_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Está brincando, cara-pálida? Não precisa das lágrimas dos deuses? Então, adeus.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Eu te falei quantas lágrimas eu tenho. Você está tirando sarro de índio, cara-pálida? Então adeus.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" lágrimas? Tudo bem. Você me dá "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", irmão branco.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Aqui está o seu dinheiro, irmão de pele vermelha.";
				link.l1.go = "big_pearl_1";
			}
			link.l2 = "Eu não tenho dinheiro suficiente agora. Me desculpe, não posso comprar suas pérolas.";
			link.l2.go = "exit";
		break;
		
		case "big_pearl_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry52", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Leve, irmão branco. Agora são seus.";
			link.l1 = "Obrigado!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// малый жемчуг
		case "small_pearl":
			dialog.text = "Quantas lágrimas você quer comprar?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "small_pearl_qty";
		break;
		
		case "small_pearl_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Está brincando, cara-pálida? Não precisa das lágrimas dos deuses? Então, adeus.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Eu te contei quantas lágrimas eu tenho. Você está tirando sarro de índio, cara-pálida? Então adeus.";
				link.l1 = "Hum...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" lágrimas? Tudo bem. Você me dá "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", irmão branco.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Aqui está seu dinheiro, irmão de pele vermelha.";
				link.l1.go = "small_pearl_1";
			}
			link.l2 = "Eu não tenho dinheiro suficiente agora. Desculpe, não posso comprar suas pérolas.";
			link.l2.go = "exit";
		break;
		
		case "small_pearl_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry53", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Pegue, irmão branco. Agora são seus.";
			link.l1 = "Obrigado!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// золотые самородки
		case "gold":
			dialog.text = "Quantos você quer comprar?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "gold_qty";
		break;
		
		case "gold_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Tá brincando, branquelo? Não precisa de nenhum metal? Então, até logo.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Eu já te disse quantos eu tenho. Está tirando sarro do índio, cara-pálida? Então adeus.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" pedaços? Bem, de você "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", irmão branco.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Aqui está seu dinheiro, irmão de pele vermelha.";
				link.l1.go = "gold_1";
			}
			link.l2 = "Eu não tenho dinheiro suficiente agora. Desculpe, não posso comprar seu ouro.";
			link.l2.go = "exit";
		break;
		
		case "gold_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry5", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Leve-os, irmão branco. Agora são seus.";
			link.l1 = "Obrigado!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// серебряные самородки
		case "silver":
			dialog.text = "Quantos você quer comprar?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "silver_qty";
		break;
		
		case "silver_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Está brincando, cara-pálida? Não precisa de metal? Então adeus.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Eu já te disse quantos eu tenho. Está tirando sarro do índio, cara-pálida? Então tchau.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" pedaços? Bem, de você "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", irmão branco.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Aqui está o seu dinheiro, irmão de pele vermelha.";
				link.l1.go = "silver_1";
			}
			link.l2 = "Eu não tenho dinheiro suficiente agora. Desculpe, não posso comprar sua prata.";
			link.l2.go = "exit";
		break;
		
		case "silver_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry6", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Leve, irmão branco. Agora são seus.";
			link.l1 = "Obrigado!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// мангароса
		case "mangarosa":
			dialog.text = "Mangarosa? Quero ver isso.";
			link.l1 = "Aqui, dá uma olhada...";
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			npchar.quest.mangarosa = "indian_"+(hrand(10)+1);
			dialog.text = "Sim. Este é um dos nomes dela - Manga Rosa. Eu te dou um amuleto por ela. Amuleto muito bom, ele também tem um nome - "+XI_ConvertString(npchar.quest.mangarosa)+". Você negocia?";
			link.l1 = "Escute, irmão de pele vermelha, eu gostaria de saber mais sobre essa planta. Você pode me contar por que ela é tão importante para você?";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			dialog.text = ""+npchar.name+" Eu não entendo. Se quiser negociar, eu te dou o amuleto pela Manga Rrosa. Se não, então vou embora.";
			link.l1 = "Ah, tudo bem. Vamos negociar.";
			link.l1.go = "mangarosa_3";
			link.l2 = "Não. Não vou entregar esta planta em troca de um amuleto.";
			link.l2.go = "exit";
		break;
		
		case "mangarosa_3":
			Log_Info("You have received an amulet");
			GiveItem2Character(pchar, npchar.quest.mangarosa);
			RemoveItems(pchar, "cannabis7", 1);
			dialog.text = "Pegue seu "+XI_ConvertString(npchar.quest.mangarosa)+". É útil.";
			link.l1 = "Sem dúvida. Boa sorte pra você, amigo de pele vermelha.";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Não desafie o destino, cara-pálida! Guarde sua espada!","Escuta aqui, cara-pálida, guarda essa arma e vamos conversar, não quero confusão.");
			link.l1 = LinkRandPhrase("Certo.","Certo.","Como você disser...");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
