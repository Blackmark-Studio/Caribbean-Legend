// диалог начальника шахты
void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		location = &Locations[FindLocation(pchar.location)];
	case "First time":
		if (LAi_grp_playeralarm > 0)
		{
			dialog.text = NPCharRepPhrase(pchar, LinkRandPhrase("¿Te atreves a mostrar tu rostro aquí? No sé si eres valiente o estúpido...", "¿Cómo dejaron estos holgazanes que un enemigo irrumpiera en mi residencia? Esto me supera...", "Ciertamente, mis guardias no valen un cobre, si tales bastardos, andan sueltos por aquí..."), LinkRandPhrase("¿Qué necesitas," + GetSexPhrase("granuja", "apestosa") + "? ¡Mis soldados ya han sido enviados tras tus huellas, " + GetSexPhrase("pirata asqueroso", "sucia pirata") + "!", "¡Sucio asesino, deja mi residencia inmediatamente! ¡Guardias!", "No tengo miedo de ti, " + GetSexPhrase("rata", "zorra") + ". ¡Pronto serás colgado en nuestro fuerte, y no llegarás lejos después de eso..."));
			link.l1 = NPCharRepPhrase(pchar, RandPhraseSimple("Estos soldados no valen ni un solo peso...", "Jamás me atraparán."), RandPhraseSimple("Cierra tu pico, " + GetWorkTypeOfMan(npchar, "") + ", o arrancaré esa lengua sucia tuya!", "Te sugeriría que te sientes tranquilamente, y quizás, salgas de esta vivo..."));
			link.l1.go = "fight";
			break;
		}
		if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
		{
			dialog.text = "¡Enemigo en la mina! ¡Alarma!";
			link.l1 = "¡Aaah, diablo!";
			link.l1.go = "fight";
			break;
		}
		dialog.text = LinkRandPhrase("" + TimeGreeting() + ", señor. Yo soy " + GetFullName(npchar) + ", el ingeniero de minas de la mina Los-Teques. ¿Qué es lo que necesitas aquí?", "Hola, señor. ¿Qué deseabas?", "¿Hmm... querías algo de mí, señor? Estoy escuchando.");
		if (!CheckAttribute(location, "quest.info"))
		{
			link.l9 = "Soy nuevo aquí, y me gustaría aprender más sobre esta mina...";
			link.l9.go = "info";
		}
		if (GetSquadronGoods(pchar, GOOD_SLAVES) > 4)
		{
			link.l2 = "Tengo una carga en mi bodega que podría interesarte. Esclavos para tu mina, para ser exacto. ¿Quieres regatear?";
			if (!CheckAttribute(location, "quest.slaves"))
				link.l2.go = "slaves_0";
			else
				link.l2.go = "slaves";
		}
		link.l1 = "Acabo de entrar para saludar, y ya me voy.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "info":
		dialog.text = "La mina de Los-Teques extrae oro para la Corona Española. Todo lo que extraemos pertenece a España. Aquí encontramos no solo oro, sino también pepitas de plata y valiosas piedras preciosas. No vendemos oro aquí, todo lo que extraemos se entrega al Viejo Mundo bajo un convoy reforzado\nPero tenemos dos excepciones para las pepitas de oro y plata. Primero, puedes comprar una cierta cantidad de ellas en nuestra tienda de un intendente. A veces, el salario no llega a tiempo, por lo que tenemos que mantener algunos ahorros de monedas aquí para tales casos, por eso se permite el comercio\nSegundo, constantemente experimentamos una necesidad de mano de obra, por lo que intercambiamos pepitas por esclavos. Por tanto, habla conmigo si tienes algo que ofrecer, haremos negocios\nCreo que las reglas de conducta de la mina son obvias: no robes, no distraigas a los convictos y no molestes a los soldados, de lo contrario, las consecuencias no te gustarán.";
		link.l1 = "¡Bien, gracias!";
		link.l1.go = "exit";
		location.quest.info = "true";
		break;

	// генератор купли-продажи рабов
	case "slaves_0":
		location.quest.slaves.qty = 200; // стартовая потребность
		dialog.text = "¡Por supuesto, señor! ¿Cuántos tienes?";
		link.l1 = "Yo tengo " + FindRussianQtyString(GetSquadronGoods(pchar, GOOD_SLAVES)) + ".";
		link.l1.go = "slaves_1";
		break;

	case "slaves":
		location.quest.slaves.qty = sti(location.quest.slaves.qty) + GetNpcQuestPastDayParam(location, "slave_date"); // каждый день даёт +1 потребности
		if (sti(location.quest.slaves.qty) > 350)
			location.quest.slaves.qty = 350; // максимум потребности
		if (sti(location.quest.slaves.qty) < 5)
		{
			dialog.text = "Señor, desafortunadamente, ahora mismo no necesitamos más esclavos. Pero la situación puede cambiar en cualquier momento, así que vuelva en unas semanas o en otro momento.";
			link.l1 = "Está bien, señor, entiendo. No los necesitas ahora, pero podrías necesitarlos en algún momento.";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "¡Por supuesto, señor! ¿Cuántos tienes?";
			link.l1 = "Yo tengo " + FindRussianQtyString(GetSquadronGoods(pchar, GOOD_SLAVES)) + ".";
			link.l1.go = "slaves_1";
		}
		break;

	case "slaves_1":
		dialog.text = "Por cada esclavo, estoy dispuesto a pagarte ya sea un lingote de oro o dos lingotes de plata. ¿Qué eliges?";
		link.l1 = "Lingotes de oro.";
		link.l1.go = "slaves_g";
		link.l2 = "Lingotes de plata.";
		link.l2.go = "slaves_s";
		link.l3 = "Lo siento, señor, pero acabo de cambiar de opinión. En otra ocasión.";
		link.l3.go = "slaves_exit";
		break;

	case "slaves_g":
		location.quest.slaves.type = "gold";
		dialog.text = "Bien. ¿Cuántos esclavos vas a venderme?";
		link.l1 = "";
		link.l1.edit = 6;
		link.l1.go = "slaves_trade";
		break;

	case "slaves_s":
		location.quest.slaves.type = "silver";
		dialog.text = "Bien. ¿Cuántos esclavos vas a venderme?";
		link.l1 = "";
		link.l1.edit = 6;
		link.l1.go = "slaves_trade";
		break;

	case "slaves_trade":
		iTotalTemp = sti(dialogEditStrings[6]);
		if (iTotalTemp < 1)
		{
			dialog.text = "Señor, no tengo tiempo para bromas estúpidas. Si estás de humor para bromear, ¡ve a la taberna!";
			link.l1 = "Hmm...";
			link.l1.go = "slaves_exit";
			break;
		}
		if (iTotalTemp > GetSquadronGoods(pchar, GOOD_SLAVES))
		{
			dialog.text = "Señor, creo que necesita descansar. Quizás esté muy cansado o haya sufrido una insolación. Vaya a la taberna, descanse bien, y luego podemos continuar con nuestro regateo.";
			link.l1 = "Hmm...";
			link.l1.go = "slaves_exit";
			break;
		}
		if (iTotalTemp > sti(location.quest.slaves.qty))
		{
			dialog.text = "Lamentablemente, señor, en este momento no necesitamos tantos esclavos. La mina actualmente requiere " + FindRussianQtyString(sti(location.quest.slaves.qty)) + ". ¿Vas a vender tantos?";
			link.l1 = "¡Sí, por supuesto!";
			link.l1.go = "slaves_max";
			link.l2 = "Hmm... Supongo que no.";
			link.l2.go = "slaves_exit";
			break;
		}
		dialog.text = "¿" + FindRussianQtyString(iTotalTemp) + "? Excelente. Ordena que los lleven a las puertas de la ciudad. Enviaré a mis hombres.";
		link.l1 = "No se preocupe, señor. Sus esclavos serán entregados a tiempo. Emitiré todas las órdenes relevantes de inmediato.";
		link.l1.go = "slaves_calk";
		break;

	case "slaves_max":
		iTotalTemp = sti(location.quest.slaves.qty);
		dialog.text = "Excelente. Por favor, ordena que los lleven a las puertas de la ciudad. Enviaré a mis hombres a por ellos.";
		link.l1 = "No se preocupe, señor. Sus esclavos le serán entregados a tiempo. Emitiré todas las órdenes pertinentes de inmediato.";
		link.l1.go = "slaves_calk";
		break;

	case "slaves_calk":
		DialogExit();
		Log_Info("Se ha completado el intercambio de esclavos por lingotes");
		PlaySound("interface\important_item.wav");
		LAi_Fade("", "");
		WaitDate("", 0, 0, 0, 5, 10);
		RemoveCharacterGoods(pchar, GOOD_SLAVES, iTotalTemp);
		if (location.quest.slaves.type == "gold")
			TakeNItems(pchar, "jewelry5", iTotalTemp);
		else
			TakeNItems(pchar, "jewelry6", iTotalTemp * 2);
		DeleteAttribute(location, "slave_date");
		SaveCurrentNpcQuestDateParam(location, "slave_date");
		location.quest.slaves.qty = sti(location.quest.slaves.qty) - iTotalTemp;
		break;

	case "slaves_exit":
		DialogExit();
		DeleteAttribute(location, "slave_date");
		SaveCurrentNpcQuestDateParam(location, "slave_date");
		break;

	case "":
		dialog.text = "";
		link.l1 = "";
		link.l1.go = "";
		break;

	case "fight":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		LAi_group_Attack(NPChar, Pchar);
		i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
		if (i != -1)
		{
			LAi_group_Attack(&Characters[i], Pchar);
		}
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
