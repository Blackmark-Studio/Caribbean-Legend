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
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Visage pâle","Femme blanche")+" veut parler ?","Vous encore, "+GetSexPhrase("visage pâle","femme blanche")+".",""+GetSexPhrase("Visage pâle aime parler. Il ressemble à une squaw.","La squaw blanche aime parler.")+"","Les esprits m'ont amené visage pâle "+GetSexPhrase("frère.","sœur")+".","bloc",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Oui.","Oui, c'est encore moi.","Très poétique.","Je suis également ravi de vous voir.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Salut, frère blanc. Tu veux parler avec l'Indien?";
				link.l1 = "Salutations, fils de la jungle. Je suis heureux de te rencontrer, mais je dois continuer mon voyage.";
				link.l1.go = "exit";
				link.l2 = "Oui. J'ai entendu dire que vous vendez des choses intéressantes. Avez-vous quelque chose à vendre?";
				link.l2.go = "select_trade";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "select_trade": //индейская торговля
			switch (hrand(7))
			{
				case 0: // торговля через интерфейс
					dialog.text = "Tu as de la chance, frère blanc. "+npchar.name+" a des choses à vendre. Regarde ici.";
					link.l1 = "Montrez vos marchandises...";
					link.l1.go = "torg";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Attends. J'ai quelque chose à vendre. C'est une plante appelée Mangarosa. J'ai entendu dire que tu es friand de ce truc...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 1: // не торгует
					dialog.text = "Non, frère blanc."+npchar.name+" ne fait pas de commerce. "+npchar.name+"  est un guerrier.";
					link.l1 = "Je vois. Très bien, adieu, frère à la peau rouge.";
					link.l1.go = "exit";
				break;
				
				case 2: // жемчуг большой
					npchar.quest.item.qty = 25+hrand(25);
					npchar.quest.item.price = 30+hrand(10);
					dialog.text = ""+npchar.name+" a des larmes de dieux. De grosses, frère blanc. Dans la quantité de "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Vous voulez les acheter? Je vends pour "+FindRussianMoneyString(sti(npchar.quest.item.price))+"pour un.";
					link.l1 = "Non, je ne suis pas intéressé.";
					link.l1.go = "exit";
					link.l2 = "Bien sûr! Je les achèterai volontiers à un tel prix.";
					link.l2.go = "big_pearl";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Attends. J'ai quelque chose à vendre. C'est une plante appelée Manga Rosa. J'ai entendu dire que tu aimes ce truc...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 3: // жемчуг малый
					npchar.quest.item.qty = 40+hrand(40);
					npchar.quest.item.price = 10+hrand(5);
					dialog.text = ""+npchar.name+" a des larmes des dieux. Petits, frère blanc. Au nombre de "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Vous voulez les acheter? Je vends pour "+FindRussianMoneyString(sti(npchar.quest.item.price))+"pour un.";
					link.l1 = "Non, je ne suis pas intéressé.";
					link.l1.go = "exit";
					link.l2 = "Bien sûr! Je les achèterai volontiers pour un tel prix.";
					link.l2.go = "small_pearl";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Attends. J'ai quelque chose à vendre. C'est une plante appelée Manga Rosa. J'ai entendu dire que tu raffoles de ce truc...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 4: //золотые самородки
					npchar.quest.item.qty = 20+hrand(20);
					npchar.quest.item.price = 90+hrand(20);
					dialog.text = ""+npchar.name+" a du métal jaune que vous les visages pâles aimez beaucoup. En la quantité de "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Je vends juste pour "+FindRussianMoneyString(sti(npchar.quest.item.price))+"pour un.";
					link.l1 = "Non, je ne suis pas intéressé.";
					link.l1.go = "exit";
					link.l2 = "Bien sûr! Je les achèterai volontiers à ce prix.";
					link.l2.go = "gold";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Attends. J'ai quelque chose à vendre. C'est une plante appelée Manga Rosa. J'ai entendu dire que tu es friand de ce truc...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 5: // серебряные самородки
					npchar.quest.item.qty = 40+hrand(40);
					npchar.quest.item.price = 40+hrand(10);
					dialog.text = ""+npchar.name+" a du métal blanc que vous les visages pâles aimez beaucoup. En quantité de "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Je vends juste pour "+FindRussianMoneyString(sti(npchar.quest.item.price))+" pour un.";
					link.l1 = "Non, je ne suis pas intéressé.";
					link.l1.go = "exit";
					link.l2 = "Bien sûr ! Je les achèterai volontiers à ce prix.";
					link.l2.go = "silver";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Attends. J'ai quelque chose à vendre. C'est une plante appelée Manga Rosa. J'ai entendu dire que tu es friand de ce truc...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 6: // повтор через интерфейс
					dialog.text = "Tu as de la chance, frère blanc. "+npchar.name+" a des choses à vendre. Regardez ici.";
					link.l1 = "Montre tes marchandises...";
					link.l1.go = "torg";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Attendez. J'ai quelque chose à vendre. C'est une plante appelée Manga Rosa. J'ai entendu dire que vous aimez ce truc...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 7: // повтор не торгует
					dialog.text = "Non, frère blanc. "+npchar.name+"  ne commerce pas. "+npchar.name+" -  est un guerrier.";
					link.l1 = "Je vois. Très bien, adieu, frère à la peau rouge.";
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
			dialog.text = "Combien de larmes voulez-vous acheter?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "big_pearl_qty";
		break;
		
		case "big_pearl_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Tu plaisantes, visage pâle? Tu n'as pas besoin des larmes des dieux? Alors, au revoir.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Je t'ai dit combien de larmes j'ai. Tu te moques de l'Indien, visage pâle? Alors au revoir.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" des larmes? D'accord. Tu me donnes "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", frère blanc.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Voici ton argent, frère à la peau rouge.";
				link.l1.go = "big_pearl_1";
			}
			link.l2 = "Je n'ai pas assez d'argent en ce moment. Je suis désolé, je ne peux pas acheter tes perles.";
			link.l2.go = "exit";
		break;
		
		case "big_pearl_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry52", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Prenez-les, frère blanc. Ils sont à vous maintenant.";
			link.l1 = "Merci!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// малый жемчуг
		case "small_pearl":
			dialog.text = "Combien de larmes voulez-vous acheter?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "small_pearl_qty";
		break;
		
		case "small_pearl_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Tu plaisantes, visage pâle? Tu n'as pas besoin des larmes des dieux? Alors, au revoir.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Je t'ai dit combien de larmes j'ai. Tu plaisantes avec l'Indien, visage pâle? Alors au revoir.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" des larmes? D'accord. Tu me donnes "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", frère blanc.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Voici ton argent, frère à la peau rouge.";
				link.l1.go = "small_pearl_1";
			}
			link.l2 = "Je n'ai pas assez d'argent en ce moment. Je suis désolé, je ne peux pas acheter vos perles.";
			link.l2.go = "exit";
		break;
		
		case "small_pearl_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry53", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Prends-les, frère blanc. Ils sont à toi maintenant.";
			link.l1 = "Merci!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// золотые самородки
		case "gold":
			dialog.text = "Combien tu veux acheter?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "gold_qty";
		break;
		
		case "gold_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Tu plaisantes, visage pâle? Tu n'as pas besoin de métal? Alors au revoir.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Je t'ai dit combien j'en ai. Tu plaisantes avec l'Indien, visage pâle ? Alors au revoir.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" des morceaux? Eh bien, de toi "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", frère blanc.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Voici ton argent, frère à la peau rouge.";
				link.l1.go = "gold_1";
			}
			link.l2 = "Je n'ai pas assez d'argent en ce moment. Je suis désolé, je ne peux pas acheter votre or.";
			link.l2.go = "exit";
		break;
		
		case "gold_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry5", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Prenez-les, frère blanc. Ils sont à toi maintenant.";
			link.l1 = "Merci !";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// серебряные самородки
		case "silver":
			dialog.text = "Combien voulez-vous en acheter?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "silver_qty";
		break;
		
		case "silver_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Tu plaisantes, visage pâle? Tu n'as pas besoin de métal? Alors, au revoir.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Je t'ai dit combien j'en ai. Tu plaisantes avec l'Indien, visage pâle ? Alors au revoir.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" des morceaux ? Eh bien, de toi "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", frère blanc.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Voici ton argent, frère à la peau rouge.";
				link.l1.go = "silver_1";
			}
			link.l2 = "Je n'ai pas assez d'argent en ce moment. Je suis désolé, je ne peux pas acheter votre argent.";
			link.l2.go = "exit";
		break;
		
		case "silver_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry6", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Prenez-les, frère blanc. Ils sont à toi maintenant.";
			link.l1 = "Merci!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// мангароса
		case "mangarosa":
			dialog.text = "Mangarosa? Je veux la voir.";
			link.l1 = "Voici, jetez un oeil...";
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			npchar.quest.mangarosa = "indian_"+(hrand(10)+1);
			dialog.text = "Oui. C'est l'un de ses noms - Manga Rosa. Je te donne un amulette pour ça. Très bonne amulette, elle a un nom - "+XI_ConvertString(npchar.quest.mangarosa)+". Vous faites du commerce ?";
			link.l1 = "Écoute, frère à la peau rouge, je voudrais en savoir plus sur cette plante. Pourrais-tu me dire pourquoi tu en as tant besoin?";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			dialog.text = ""+npchar.name+" ne comprends pas. Si tu veux faire du commerce, je te donne l'amulette pour Manga Rrosa. Si non, alors je pars.";
			link.l1 = "Oh, bon. Faisons du commerce.";
			link.l1.go = "mangarosa_3";
			link.l2 = "Non. Je ne donnerai pas cette plante pour un amulette.";
			link.l2.go = "exit";
		break;
		
		case "mangarosa_3":
			Log_Info("You have received an amulet");
			GiveItem2Character(pchar, npchar.quest.mangarosa);
			RemoveItems(pchar, "cannabis7", 1);
			dialog.text = "Prends ton "+XI_ConvertString(npchar.quest.mangarosa)+". Ce serait utile.";
			link.l1 = "Aucun doute à ce sujet. Bonne chance à toi, ami à la peau rouge.";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Ne tente pas le destin, visage pâle ! Range ton épée !","Ecoute visage pale, cache ton arme et parlons, je n'ai pas besoin de problemes.");
			link.l1 = LinkRandPhrase("D'accord.","D'accord.","Comme vous dites...");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
