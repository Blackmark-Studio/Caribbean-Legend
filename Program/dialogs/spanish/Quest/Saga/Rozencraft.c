// Михаэль Розенкрафт - голландский капитан, квестовый покупатель бакаута
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "¿Quieres algo?";
		link.l1 = "No, es nada.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "rozencraft":
		if (pchar.questTemp.Saga.Oyster == "cantalk")
		{
			dialog.text = "Mm... ¿Y dónde está Molligan? ¿No quería verme él mismo?";
			link.l1 = "Nuestro pobre Paul tiene fiebre. No está de humor para comerciar. Estoy aquí en su lugar.";
			link.l1.go = "rozencraft_1";
		}
		else
		{
			dialog.text = "¿Qué quieres, señor?";
			link.l1 = "¿Tengo entendido que estás esperando comprar algo de sándalo?";
			link.l1.go = "rozencraft_no";
		}
		break;

	case "rozencraft_no":
		dialog.text = "¿Quién le dijo esa tontería, señor? No estoy esperando a nadie ni a nada. Mi nave está patrullando la zona por orden del gobernador de Willemstad. Así que, ¿sería tan amable de dejar mi barco? Debe estar equivocado.";
		link.l1 = "Hum... Ya veo. Lamento molestarte.";
		link.l1.go = "rozencraft_no_1";
		break;

	case "rozencraft_no_1":
		DialogExit();
		AddQuestRecord("Testament", "8");
		NextDiag.CurrentNode = "rozencraft_no_repeat";
		break;

	case "rozencraft_no_repeat":
		dialog.text = "¿No hemos tenido ya esta charla, señor?";
		link.l1 = "Sí, sí. Ya me estoy yendo y embarcando en mi barco.";
		link.l1.go = "exit";
		NextDiag.TempNode = "rozencraft_no_repeat";
		break;

	case "rozencraft_1":
		dialog.text = "¿Y quién eres tú?";
		link.l1 = "¿No te importa con quién comercias? He traído sándalo para vender. ¿Cuánto?";
		link.l1.go = "rozencraft_2";
		break;

	case "rozencraft_2":
		dialog.text = "Según el acuerdo, cuarenta doblones por pieza.";
		link.l1 = "Mm...";
		link.l1.go = "rozencraft_3";
		break;

	case "rozencraft_3":
		npchar.quest.bakaut = GetSquadronGoods(pchar, GOOD_SANDAL);
		dialog.text = "Amigo, teníamos un trato con Molligan. Este es un buen precio, no encontrarás uno mejor. Así que no te comportes como un campesino en la tienda. ¿Cuánto sándalo tienes?";
		link.l1 = "" + FindRussianQtyString(sti(npchar.quest.bakaut)) + ".";
		link.l1.go = "rozencraft_4";
		break;

	case "rozencraft_4":
		iTemp = sti(npchar.quest.bakaut);
		if (iTemp >= 90)
		{
			dialog.text = "Espléndido. Eso es más de lo que esperaba. Aquí, toma el oro. Si consigues más sándalo, ve a la taberna en San Martín y habla con... ya sabes quién. Él organizará una reunión para nosotros. Veo que eres un socio mucho mejor que ese idiota de Molligan.";
			link.l1 = "Está bien. Es un trato.";
			link.l1.go = "rozencraft_5";
			pchar.GenQuest.Bakaut = "true"; // генератор сбыта бакаута
			break;
		}
		if (iTemp >= 70 && iTemp < 90)
		{
			dialog.text = "Bien. Aquí, toma el oro. Si consigues más sándalo, ve a la taberna en Philipsburg y habla con... ya sabes quién. Él se pondrá en contacto conmigo. Veo que podemos hacer negocios contigo no peor que con ese idiota de Molligan.";
			link.l1 = "Está bien. Es un trato.";
			link.l1.go = "rozencraft_5";
			pchar.GenQuest.Bakaut = "true"; // генератор сбыта бакаута
			break;
		}
		if (iTemp >= 40 && iTemp < 70)
		{
			dialog.text = "Hmm... Esperaba más. Está bien. Aquí, toma el oro. Y dile a Molligan que la próxima vez debe traer un lote no menor de cien piezas.";
			link.l1 = "Está bien. Se lo diré.";
			link.l1.go = "rozencraft_5";
			break;
		}
		dialog.text = "¿Me estás tomando el pelo? ¡Teníamos un trato con Molligan, el lote no debe ser menor de cincuenta piezas! Lárgate y no regreses hasta que tengas suficiente.";
		link.l1 = "Está bien, está bien, cálmate.";
		link.l1.go = "rozencraft_5";
		break;

	case "rozencraft_5":
		DialogExit();
		npchar.DontDeskTalk = true; // чтоб не доставал, в генераторе - снимаем
		iTemp = sti(npchar.quest.bakaut);
		if (iTemp < 40)
			DeleteAttribute(npchar, "quest.bakaut");
		else
		{
			TakeNItems(pchar, "gold_dublon", iTemp * 40);
			RemoveCharacterGoods(pchar, GOOD_SANDAL, iTemp);
			// считаем, сколько мы должны Свенсону
			int ibak = makeint((iTemp * 40 - 2000) / 2);
			sld = characterFromId("Svenson");
			sld.quest.bakaut_sum = ibak; // доля Яна
			AddQuestRecord("Testament", "9");
			AddQuestUserData("Testament", "sSum", iTemp * 40);
			AddQuestUserData("Testament", "sSum1", ibak);
			if (CheckAttribute(pchar, "GenQuest.Bakaut"))
				AddQuestUserData("Testament", "sText", "Además, si consigo sándalo, podré vendérsela a Michael Rosencraft concertando una cita con su hombre en la taberna de Philipsburg.");
			pchar.questTemp.Saga = "removebakaut";
			// корабль Розенкрафта сохраняем, в АИ на него будет стоять проверка на попадание
			pchar.quest.Saga_Rozencraft_GetOut.over = "yes";	  // снять прерывание
			pchar.quest.Saga_Rozencraft_AfterBattle.over = "yes"; // снять прерывание
			// ставим новое прерывание на потопление Розенкрафта
			pchar.quest.Bakaut_Rozencraft_Die.win_condition.l1 = "Group_Death";
			pchar.quest.Bakaut_Rozencraft_Die.win_condition.l1.group = "Rozencraft_Group";
			pchar.quest.Bakaut_Rozencraft_Die.function = "Bakaut_RozencraftDie";
			pchar.quest.Bakaut_Rozencraft_Remove.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Remove.function = "Bakaut_RozencraftRemove";
		}
		NextDiag.CurrentNode = "rozencraft_no_repeat";
		break;

		// ------------------------------------генератор сбыта бакаута-----------------------------------------------
	case "bakaut":
		dialog.text = "¡Oh, mi viejo amigo! ¿Tienes algún palo de hierro para vender?";
		link.l1 = "Exactamente, Michel. Hagamos un trato.";
		link.l1.go = "bakaut_0";
		break;

	case "bakaut_0":
		dialog.text = "¿Cuánto tienes? Necesito un lote no menor que " + FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)) + ".";
		if (GetSquadronGoods(pchar, GOOD_SANDAL) >= sti(pchar.GenQuest.Bakaut.Value))
		{
			link.l1 = "Lo sé. Tengo " + FindRussianQtyString(GetSquadronGoods(pchar, GOOD_SANDAL)) + "  de sándalo que estás tan ansioso por conseguir.";
			link.l1.go = "bakaut_1";
		}
		else
		{
			link.l1 = "Hum. Desafortunadamente no tengo tanto.";
			link.l1.go = "bakaut_no";
		}
		break;

	case "bakaut_no":
		if (!CheckAttribute(npchar, "quest.bakaut_angry"))
		{
			dialog.text = "¡Maldita sea, no te advirtieron? ¿O las ratas se han comido la madera? Necesito " + FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)) + "y ni una pieza menos. La próxima vez tráeme tanta madera como te diga mi agente. Espero que no me decepciones de nuevo o tendré que rechazar tus servicios.";
			link.l1 = "Está bien, señor, seré más atento en el futuro.";
			link.l1.go = "bakaut_no_1";
		}
		else
		{
			if (sti(npchar.quest.bakaut_angry) == 1)
			{
				dialog.text = "Me estás fastidiando por segunda vez. No me gusta. Sepa que esta es la última advertencia, la próxima vez rechazaré sus servicios.";
				link.l1 = "¡Malditas ratas dañaron mis mercancías! Te prometo, Michael, que esta fue la última vez.";
				link.l1.go = "bakaut_no_1";
			}
			else
			{
				dialog.text = "¡Y ahora se me ha agotado la paciencia! No quiero hacer negocios contigo nunca más. Lárgate y olvídate de mí.";
				link.l1 = "Pero Mynheer...";
				link.l1.go = "bakaut_no_2";
			}
		}
		npchar.DontDeskTalk = true;
		pchar.quest.Bakaut_Rozencraft_Find.over = "yes"; // снять прерывание
		break;

	case "bakaut_no_1":
		DialogExit();
		NextDiag.CurrentNode = "rozencraft_no_repeat";
		if (!CheckAttribute(npchar, "quest.bakaut_angry"))
			npchar.quest.bakaut_angry = 1;
		else
			npchar.quest.bakaut_angry = sti(npchar.quest.bakaut_angry) + 1;
		pchar.quest.Bakaut_Rozencraft_Reset.win_condition.l1 = "MapEnter";
		pchar.quest.Bakaut_Rozencraft_Reset.function = "Bakaut_RozencraftRemove";
		AddQuestRecord("Bakaut", "3");
		CloseQuestHeader("Bakaut");
		break;

	case "bakaut_no_2":
		DialogExit();
		NextDiag.CurrentNode = "rozencraft_no_repeat";
		pchar.quest.Bakaut_Rozencraft_Fail.win_condition.l1 = "MapEnter";
		pchar.quest.Bakaut_Rozencraft_Fail.function = "Bakaut_RozencraftDie";
		AddQuestRecord("Bakaut", "4");
		CloseQuestHeader("Bakaut");
		break;

	case "bakaut_1":
		iTemp = GetSquadronGoods(pchar, GOOD_SANDAL);
		if (iTemp > sti(pchar.GenQuest.Bakaut.Value) + 20)
		{ // перебор
			dialog.text = "¡Vaya! Lo siento, amigo, pero solo puedo comprar " + FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value) + 20) + ", no tengo dinero para toda tu carga. Estaba esperando un lote de " + FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)) + " piezas por cuarenta doblones cada una...";
			link.l1 = "Bien. Toma " + FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value) + 20) + " ahora y te venderé el resto la próxima vez.";
			link.l1.go = "bakaut_2";
			npchar.quest.bakaut = sti(pchar.GenQuest.Bakaut.Value) + 20;
		}
		else
		{
			dialog.text = "Muy bien. El precio es el de siempre, cuarenta doblones por cada pieza.";
			link.l1 = "Funciona para mí. Toma tu lote.";
			link.l1.go = "bakaut_2";
			npchar.quest.bakaut = iTemp;
		}
		break;

	case "bakaut_2":
		LAi_Fade("", "");
		WaitDate("", 0, 0, 0, 1, 10);
		dialog.text = "Un placer hacer negocios contigo. Vuelve a verme si quieres vender más sándalo.";
		link.l1 = "Nos vemos de nuevo, señor. Nuestra colaboración es muy lucrativa para mí. ¡Adiós!";
		link.l1.go = "bakaut_3";
		break;

	case "bakaut_3":
		DialogExit();
		iTemp = sti(npchar.quest.bakaut);
		TakeNItems(pchar, "gold_dublon", iTemp * 40);
		RemoveCharacterGoods(pchar, GOOD_SANDAL, iTemp);
		npchar.DontDeskTalk = true;
		pchar.quest.Bakaut_Rozencraft_Find.over = "yes"; // снять прерывание
		pchar.quest.Bakaut_Rozencraft_Reset.win_condition.l1 = "MapEnter";
		pchar.quest.Bakaut_Rozencraft_Reset.function = "Bakaut_RozencraftRemove";
		NextDiag.CurrentNode = "rozencraft_no_repeat";
		AddQuestRecord("Bakaut", "2");
		AddQuestUserData("Bakaut", "sQty", iTemp);
		AddQuestUserData("Bakaut", "sDublon", iTemp * 40);
		AddQuestUserData("Bakaut", "sDublon1", iTemp * 40 - iTemp * 30);
		CloseQuestHeader("Bakaut");
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
