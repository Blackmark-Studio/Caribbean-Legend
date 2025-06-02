// Jason диалог индейцев в джунглях
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int iQty;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = NPCStringReactionRepeat("" + GetSexPhrase("Cara pálida", "Mujer blanca") + "¿quiere hablar?", "Tú de nuevo, " + GetSexPhrase("cara pálida", "squaw blanca") + ".", "" + GetSexPhrase("Cara pálida gusta hablar. Parece una squaw.", "Al squaw blanco le gusta hablar.") + "", "Los espíritus me trajeron cara pálida " + GetSexPhrase("hermano.", "hermana") + ".", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Sí.", "Sí, yo de nuevo.", "Muy poético.", "También me alegra verte.", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";

		if (npchar.quest.meeting == "0")
		{
			dialog.text = "Saludos, hermano blanco. ¿Deseas hablar con indio?";
			link.l1 = "Saludos, hijo de la selva. Me alegra conocerte, pero debo continuar mi viaje.";
			link.l1.go = "exit";
			link.l2 = "Sí. He oído que vendes cosas interesantes. ¿Tienes algo en venta?";
			link.l2.go = "select_trade";
			npchar.quest.meeting = "1";
		}
		NextDiag.TempNode = "First time";
		break;

	case "select_trade": // индейская торговля
		switch (hrand(7))
		{
		case 0: // торговля через интерфейс
			dialog.text = "Tienes suerte, hermano blanco." + npchar.name + " tiene algunas cosas a la venta. Mira aquí.";
			link.l1 = "Muestra tus bienes...";
			link.l1.go = "torg";
			if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
			{
				if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
				{
					link.l9 = "Espera. Tengo algo para vender. Es una planta llamada Mangarosa. Escuché que eres aficionado a estas cosas...";
					link.l9.go = "mangarosa";
				}
			}
			break;

		case 1: // не торгует
			dialog.text = "No, hermano blanco. " + npchar.name + " no comercia. " + npchar.name + "  es un guerrero.";
			link.l1 = "Entiendo. Bien, adiós, hermano de piel roja.";
			link.l1.go = "exit";
			break;

		case 2: // жемчуг большой
			npchar.quest.item.qty = 25 + hrand(25);
			npchar.quest.item.price = 30 + hrand(10);
			dialog.text = "" + npchar.name + " tiene lágrimas de dioses. Grandes, hermano blanco. En la cantidad de " + FindRussianQtyString(sti(npchar.quest.item.qty)) + ". ¿Quieres comprarlos? Los vendo por " + FindRussianMoneyString(sti(npchar.quest.item.price)) + "para uno.";
			link.l1 = "No, no estoy interesado.";
			link.l1.go = "exit";
			link.l2 = "¡Por supuesto! Los compraré con gusto por ese precio.";
			link.l2.go = "big_pearl";
			if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
			{
				if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
				{
					link.l9 = "Espera. Tengo algo para vender. Es una planta llamada Manga Rosa. Escuché que eres aficionado a esto...";
					link.l9.go = "mangarosa";
				}
			}
			break;

		case 3: // жемчуг малый
			npchar.quest.item.qty = 40 + hrand(40);
			npchar.quest.item.price = 10 + hrand(5);
			dialog.text = "" + npchar.name + " tiene lágrimas de dioses. Pequeñas, hermano blanco. En la cantidad de " + FindRussianQtyString(sti(npchar.quest.item.qty)) + ". ¿Quieres comprarlos? Los vendo por " + FindRussianMoneyString(sti(npchar.quest.item.price)) + " para uno.";
			link.l1 = "No, no estoy interesado.";
			link.l1.go = "exit";
			link.l2 = "¡Por supuesto! Con gusto los compraré por ese precio.";
			link.l2.go = "small_pearl";
			if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
			{
				if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
				{
					link.l9 = "Espera. Tengo algo en venta. Es una planta llamada Manga Rosa. Oí que eres aficionado a estas cosas...";
					link.l9.go = "mangarosa";
				}
			}
			break;

		case 4: // золотые самородки
			npchar.quest.item.qty = 20 + hrand(20);
			npchar.quest.item.price = 90 + hrand(20);
			dialog.text = "" + npchar.name + " tiene metal amarillo que vosotros carapálidas amáis mucho. En la cantidad de " + FindRussianQtyString(sti(npchar.quest.item.qty)) + ". Vendo solo por " + FindRussianMoneyString(sti(npchar.quest.item.price)) + " para uno.";
			link.l1 = "No, no estoy interesado.";
			link.l1.go = "exit";
			link.l2 = "¡Por supuesto! Los compraré con gusto por ese precio.";
			link.l2.go = "gold";
			if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
			{
				if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
				{
					link.l9 = "Espera. Tengo algo para vender. Es una planta llamada Manga Rosa. Escuché que eres aficionado a esta cosa...";
					link.l9.go = "mangarosa";
				}
			}
			break;

		case 5: // серебряные самородки
			npchar.quest.item.qty = 40 + hrand(40);
			npchar.quest.item.price = 40 + hrand(10);
			dialog.text = "" + npchar.name + " tiene metal blanco que a vosotros, caras pálidas, os gusta mucho. En la cantidad de " + FindRussianQtyString(sti(npchar.quest.item.qty)) + ". Solo vendo por " + FindRussianMoneyString(sti(npchar.quest.item.price)) + "para uno.";
			link.l1 = "No, no estoy interesado.";
			link.l1.go = "exit";
			link.l2 = "¡Por supuesto! Con gusto los compraré por tal precio.";
			link.l2.go = "silver";
			if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
			{
				if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
				{
					link.l9 = "Espera. Tengo algo en venta. Es una planta llamada Manga Rosa. Oí que te gusta este tipo de cosas...";
					link.l9.go = "mangarosa";
				}
			}
			break;

		case 6: // повтор через интерфейс
			dialog.text = "Estás de suerte, hermano blanco. " + npchar.name + " tiene algunas cosas a la venta. Mira aquí.";
			link.l1 = "Muestra tus bienes...";
			link.l1.go = "torg";
			if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
			{
				if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
				{
					link.l9 = "Espera. Tengo algo para vender. Es una planta llamada Manga Rosa. Escuché que eres aficionado a estas cosas...";
					link.l9.go = "mangarosa";
				}
			}
			break;

		case 7: // повтор не торгует
			dialog.text = "No, hermano blanco. " + npchar.name + "  no comercia. " + npchar.name + ",  es un guerrero.";
			link.l1 = "Ya veo. Bueno, adiós, hermano de piel roja.";
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
		dialog.text = "¿Cuántas lágrimas quieres comprar?";
		link.l1 = "";
		Link.l1.edit = 4;
		link.l1.go = "big_pearl_qty";
		break;

	case "big_pearl_qty":
		iQty = sti(dialogEditStrings[4]);
		npchar.quest.item.Byeqty = iQty;
		if (iQty < 1)
		{
			dialog.text = "¿Bromeas, cara pálida? ¿No necesitas las lágrimas de los dioses? Entonces adiós.";
			link.l1 = "Hmm...";
			link.l1.go = "exit";
			break;
		}
		if (iQty > sti(npchar.quest.item.qty))
		{
			dialog.text = "Te dije cuántas lágrimas tengo. ¿Bromeas con el indio, cara pálida? Entonces adiós.";
			link.l1 = "Hmm...";
			link.l1.go = "exit";
			break;
		}
		npchar.quest.item.Summ = iQty * sti(npchar.quest.item.price);
		dialog.text = "" + iQty + " ¿lágrimas? Está bien. Me das " + FindRussianMoneyString(sti(npchar.quest.item.Summ)) + ", hermano blanco.";
		if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
		{
			link.l1 = "Aquí está tu dinero, hermano de piel roja.";
			link.l1.go = "big_pearl_1";
		}
		link.l2 = "No tengo suficiente dinero ahora mismo. Lo siento, no puedo comprar tus perlas.";
		link.l2.go = "exit";
		break;

	case "big_pearl_1":
		AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
		TakeNItems(pchar, "jewelry52", sti(npchar.quest.item.Byeqty));
		PlaySound("interface\important_item.wav");
		dialog.text = "Tómalos, hermano blanco. Ahora son tuyos.";
		link.l1 = "¡Gracias!";
		link.l1.go = "exit";
		ChangeIndianRelation(1.00);
		break;

	// малый жемчуг
	case "small_pearl":
		dialog.text = "¿Cuántas lágrimas quieres comprar?";
		link.l1 = "";
		Link.l1.edit = 4;
		link.l1.go = "small_pearl_qty";
		break;

	case "small_pearl_qty":
		iQty = sti(dialogEditStrings[4]);
		npchar.quest.item.Byeqty = iQty;
		if (iQty < 1)
		{
			dialog.text = "¿Bromeas, rostro pálido? ¿No necesitas las lágrimas de los dioses? Entonces adiós.";
			link.l1 = "Hmm...";
			link.l1.go = "exit";
			break;
		}
		if (iQty > sti(npchar.quest.item.qty))
		{
			dialog.text = "Te conté cuántas lágrimas tengo. ¿Bromeas con el indio, cara pálida? Entonces adiós.";
			link.l1 = "Mmm...";
			link.l1.go = "exit";
			break;
		}
		npchar.quest.item.Summ = iQty * sti(npchar.quest.item.price);
		dialog.text = "" + iQty + " ¿lágrimas? Está bien. Me das " + FindRussianMoneyString(sti(npchar.quest.item.Summ)) + ", hermano blanco.";
		if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
		{
			link.l1 = "Aquí está tu dinero, hermano de piel roja.";
			link.l1.go = "small_pearl_1";
		}
		link.l2 = "No tengo suficiente dinero ahora mismo. Lo siento, no puedo comprar tus perlas.";
		link.l2.go = "exit";
		break;

	case "small_pearl_1":
		AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
		TakeNItems(pchar, "jewelry53", sti(npchar.quest.item.Byeqty));
		PlaySound("interface\important_item.wav");
		dialog.text = "Tómalos, hermano blanco. Ahora son tuyos.";
		link.l1 = "¡Gracias!";
		link.l1.go = "exit";
		ChangeIndianRelation(1.00);
		break;

	// золотые самородки
	case "gold":
		dialog.text = "¿Cuántos quieres comprar?";
		link.l1 = "";
		Link.l1.edit = 4;
		link.l1.go = "gold_qty";
		break;

	case "gold_qty":
		iQty = sti(dialogEditStrings[4]);
		npchar.quest.item.Byeqty = iQty;
		if (iQty < 1)
		{
			dialog.text = "¿Bromeas, carapálida? ¿No necesitas metal? Entonces adiós.";
			link.l1 = "Hmm...";
			link.l1.go = "exit";
			break;
		}
		if (iQty > sti(npchar.quest.item.qty))
		{
			dialog.text = "Te dije cuántos tengo. ¿Bromeas con el indio, cara pálida? Entonces adiós.";
			link.l1 = "¿Mmm...?";
			link.l1.go = "exit";
			break;
		}
		npchar.quest.item.Summ = iQty * sti(npchar.quest.item.price);
		dialog.text = "" + iQty + " ¿trozos? Bueno, de ti " + FindRussianMoneyString(sti(npchar.quest.item.Summ)) + ", hermano blanco.";
		if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
		{
			link.l1 = "Aquí está tu dinero, hermano de piel roja.";
			link.l1.go = "gold_1";
		}
		link.l2 = "No tengo suficiente dinero ahora mismo. Lo siento, no puedo comprar tu oro.";
		link.l2.go = "exit";
		break;

	case "gold_1":
		AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
		TakeNItems(pchar, "jewelry5", sti(npchar.quest.item.Byeqty));
		PlaySound("interface\important_item.wav");
		dialog.text = "Tómalos, hermano blanco. Son tuyos ahora.";
		link.l1 = "¡Gracias!";
		link.l1.go = "exit";
		ChangeIndianRelation(1.00);
		break;

	// серебряные самородки
	case "silver":
		dialog.text = "¿Cuántos quieres comprar?";
		link.l1 = "";
		Link.l1.edit = 4;
		link.l1.go = "silver_qty";
		break;

	case "silver_qty":
		iQty = sti(dialogEditStrings[4]);
		npchar.quest.item.Byeqty = iQty;
		if (iQty < 1)
		{
			dialog.text = "¿Bromeas, cara pálida? ¿No necesitas metal? Entonces adiós.";
			link.l1 = "¿Hmm...?";
			link.l1.go = "exit";
			break;
		}
		if (iQty > sti(npchar.quest.item.qty))
		{
			dialog.text = "Te conté cuántos tengo. ¿Bromeas con el indio, cara pálida? Entonces adiós.";
			link.l1 = "Hmm...";
			link.l1.go = "exit";
			break;
		}
		npchar.quest.item.Summ = iQty * sti(npchar.quest.item.price);
		dialog.text = "" + iQty + " ¿trozos? Bueno, de ti " + FindRussianMoneyString(sti(npchar.quest.item.Summ)) + ", hermano blanco.";
		if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
		{
			link.l1 = "Aquí está tu dinero, hermano de piel roja.";
			link.l1.go = "silver_1";
		}
		link.l2 = "No tengo suficiente dinero ahora mismo. Lo siento, no puedo comprar tu plata.";
		link.l2.go = "exit";
		break;

	case "silver_1":
		AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
		TakeNItems(pchar, "jewelry6", sti(npchar.quest.item.Byeqty));
		PlaySound("interface\important_item.wav");
		dialog.text = "Tómalos, hermano blanco. Ahora son tuyos.";
		link.l1 = "¡Gracias!";
		link.l1.go = "exit";
		ChangeIndianRelation(1.00);
		break;

	// мангароса
	case "mangarosa":
		dialog.text = "¿Mangarosa? Quiero verla.";
		link.l1 = "Aquí, echa un vistazo...";
		link.l1.go = "mangarosa_1";
		break;

	case "mangarosa_1":
		npchar.quest.mangarosa = "indian_" + (hrand(10) + 1);
		dialog.text = "Sí. Ese es uno de los nombres que tiene, Manga Rosa. Te doy un amuleto por ello. Muy buen amuleto, tiene nombre, " + XI_ConvertString(npchar.quest.mangarosa) + "¿Haces comercio?";
		link.l1 = "Escucha, hermano de piel roja, me gustaría aprender más sobre esta planta. ¿Me dirás por qué la necesitas tanto?";
		link.l1.go = "mangarosa_2";
		break;

	case "mangarosa_2":
		dialog.text = "" + npchar.name + " no entender. Si quieres comerciar, te doy amuleto por Manga Rrosa. Si no, entonces me voy.";
		link.l1 = "Oh, bueno. Vamos a comerciar.";
		link.l1.go = "mangarosa_3";
		link.l2 = "No. No daré esta planta a cambio de un amuleto.";
		link.l2.go = "exit";
		break;

	case "mangarosa_3":
		Log_Info("Has recibido un amuleto");
		GiveItem2Character(pchar, npchar.quest.mangarosa);
		RemoveItems(pchar, "cannabis7", 1);
		dialog.text = "Lleva tu " + XI_ConvertString(npchar.quest.mangarosa) + ". Sería útil.";
		link.l1 = "Sin duda alguna. Buena suerte para ti, amigo de piel roja.";
		link.l1.go = "exit";
		ChangeIndianRelation(1.00);
		break;

	// замечание по обнажённому оружию от персонажей типа citizen
	case "CitizenNotBlade":
		dialog.text = NPCharSexPhrase(NPChar, "¡No tentéis al destino, cara pálida! ¡Guarda tu espada!", "Escucha, carapálida, esconde tu arma y hablemos, no necesito problemas.");
		link.l1 = LinkRandPhrase("Bien.", "Bien.", "Como usted diga...");
		link.l1.go = "exit";
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
