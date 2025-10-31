// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué quieres? Pregunta lo que sea.", "Te escucho, ¿cuál es la pregunta?"), "Esta es la segunda vez que intentas preguntar...", "Esta es la tercera vez que intentas preguntar...", "¿Cuándo va a terminar esto?! ¡Soy un hombre ocupado, trabajando en asuntos de la colonia y aún me estás molestando!", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No ahora. Lugar y momento equivocados."), "Verdad... Pero después, no ahora...", "Preguntaré... Pero un poco más tarde...", "Lo siento, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";

		if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
		{
			if (CheckAttribute(pchar, "GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "Quiero hablar sobre tu prisionero.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar, "GenQuest.CaptainComission.toMayor");
			}
			if (CheckAttribute(pchar, "GenQuest.CaptainComission.PirateShips"))
			{
				link.l1 = "Hola " + NPChar.name + ", estoy aquí por tu prisionero.";
				link.l1.go = "CapComission3";
			}
			if (CheckAttribute(pchar, "GenQuest.CaptainComission.RepeatSpeak"))
			{
				link.l1 = "Quiero hablar sobre tu prisionero.";
				link.l1.go = "CapComission6";
			}
		}
		if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
		{
			link.l1 = "He oído que estás involucrado en un negocio relacionado con prisioneros...";
			link.l1.go = "Marginpassenger";
		}
		break;

	case "CapComission1":
		dialog.text = "Ja, ja. ¿Crees que solo tengo un prisionero aquí? Nómbralo.";
		link.l1 = pchar.GenQuest.CaptainComission.SlaveName + ". ¿Está aquí?";
		link.l1.go = "CapComission2";
		break;

	case "CapComission2":
		if (CheckAttribute(pchar, "GenQuest.CaptainComission.DaysLeft"))
		{
			dialog.text = "Lo era. Lo he vendido a ese dueño de plantación de Barbados, el coronel Bishop, cuando estaba aquí hace una semana.";
			link.l1 = "Maldita sea...";
			link.l1.go = "CapComission2_1";
		}
		else
		{
			pchar.quest.CaptainComission_SellSlave.over = "yes";
			dialog.text = "Ah, al fin. Estaba pensando en venderlo a ese dueño de plantación de Barbados, estará aquí en una semana o dos... ¿Tienes un rescate?" + GetSexPhrase("", "") + "?";
			link.l1 = "Mira, " + NPChar.name + " , hay un pequeño problema... En realidad, no tengo tanto dinero. Pero estoy listo para trabajar.";
			link.l1.go = "CapComission2_2";
			if (makeint(pchar.money) > 150000)
			{
				link.l2 = "Es bueno que no lo hayas vendido. Aquí están tus monedas - 150.000 pesos. ¿Dónde puedo conseguirlo?" link.l2.go = "CapComission2_3";
			}
		}
		break;

	case "CapComission2_1":
		dialog.text = "Fuiste demasiado lento... ¿Y por qué te importa él? Solo he estado negociando con sus parientes.";
		link.l1 = "Me han pedido que venga aquí.";
		link.l1.go = "CapComission2_11";
		break;

	case "CapComission2_11":
		dialog.text = "Bueno, llegas tarde. No puedo hacer nada.";
		link.l1 = "Escucha, ¿por cuánto lo has vendido, si no es un secreto?";
		link.l1.go = "CapComission2_12";
		break;

	case "CapComission2_12":
		dialog.text = "Eh, no es así. Pero no te lo diré... Te reirás si lo hago. ¡Ja-ja-ja-ja! Adiós.";
		link.l1 = "Nos vemos.";
		link.l1.go = "exit";
		AddQuestRecord("CaptainComission1", "10");
		AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
		CaptainComission_GenerateManager();
		break;

	case "CapComission2_2":
		if (rand(1) == 0)
		{
			dialog.text = "Bueno, bueno... Tengo un asunto... Ni siquiera sé por dónde empezar. Necesito hundir a un pirata que se pasó de la raya.";
			link.l1 = "¿No se le puede simplemente matar en la jungla?";
			link.l1.go = "CapComission2_2_1";
		}
		else
		{
			dialog.text = "Bueno, " + pchar.name + ", sabes, no funciona así. Vuelve con el dinero y conseguirás a tu debilucho, ja-ja.";
			link.l1 = "Bien, adiós entonces.";
			link.l1.go = "exit";
			if (!CheckAttribute(pchar, "GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			}
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;
		}
		break;

	case "CapComission2_2_1":
		dialog.text = "No es así como funcionan los negocios, ¿sabes...? No necesito su muerte, necesito enseñar a algunos a no tomar mi parte del botín. Pero si termina alimentando a los tiburones, no me voy a molestar.";
		link.l1 = "¿Por qué no envías a tus propios hombres tras él?";
		link.l1.go = "CapComission2_2_2";
		break;

	case "CapComission2_2_2":
		CaptainComission_GetRandomShore();
		pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
		pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
		pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
		dialog.text = "Mm.. Bueno " + GetName(NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.UnknownPirateName, NAME_NOM) + " ha convencido a algunos piratas de que su parte del botín se guardará en nuestro escondite no lejos de " + XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Gen") + ". Sus dos barcos '" + pchar.GenQuest.CaptainComission.ShipName1 + "' y '" + pchar.GenQuest.CaptainComission.ShipName2 + " izó anclas no hace mucho y zarpó hacia " + XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Abl") + "¿Ahora ves por qué no puedo confiar en mis hombres para hacer ese trabajo?";
		link.l1 = "Ya veo. ¿Cuánto tiempo tengo?";
		link.l1.go = "CapComission2_2_3";
		break;

	case "CapComission2_2_3":
		dialog.text = "12 a 15 días, no más. Es importante para mí que no lleguen al escondite, sería una locura hundirlos con carga valiosa. En ese caso, sería mejor que lo trajeran aquí...";
		link.l1 = "Está bien, estoy dentro. Intentaré atraparlos.";
		link.l1.go = "exit";
		AddQuestRecord("CaptainComission1", "24");
		AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
		AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
		AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
		AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Abl"));
		AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Dat"));
		pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
		pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
		pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips";
		SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
		pchar.GenQuest.CaptainComission.PirateShips = "goaway";
		break;

	case "CapComission2_3":
		dialog.text = "No te preocupes. Mis hombres lo llevarán a tu barco. ¿Y por qué te importa él?";
		link.l1 = "No lo hago. Sus parientes me pidieron que lo entregara.";
		link.l1.go = "CapComission2_31";
		break;

	case "CapComission2_31":
		dialog.text = "Ah, está bien. Casi me arrepentí de ofrecer un precio tan bajo por tu hombre. Ja-ja-ja-ja. Adiós.";
		link.l1 = "Nos vemos.";
		link.l1.go = "exit";
		AddQuestRecord("CaptainComission1", "9");
		AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
		AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
		addMoneyToCharacter(pchar, -150000);
		AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;

	case "CapComission3":
		dialog.text = "Bueno, " + GetFullName(pchar) + ", ¿hundiste a mi compañero? Ja-ja-ja...";
		if (pchar.GenQuest.CaptainComission.PirateShips == "goaway")
		{
			link.l1 = "No. No logré atraparlos. Y no los encontré al regresar.";
			link.l1.go = "CapComission4";
		}
		else
		{
			if (pchar.GenQuest.CaptainComission.PirateShips == "died")
			{
				link.l1 = "Lo hice. Los envié a alimentar a los tiburones.";
				link.l1.go = "CapComission5";
			}
		}
		DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
		break;

	case "CapComission4":
		dialog.text = "¡Maldita sea! ¡No importa ahora! ¿Cuál será tu próxima sugerencia?";
		link.l1 = "¿Tal vez tienes un trabajo más fácil para mí?";
		link.l1.go = "CapComission4_1";
		link.l2 = "Escucha, " + NPChar.name + ", baja el precio por el prisionero...";
		link.l2.go = "CapComission4_2";
		break;

	case "CapComission4_1":
		dialog.text = "No.";
		link.l1 = "Adiós entonces...";
		link.l1.go = "exit";
		ChangeCharacterComplexReputation(pchar, "nobility", -2);
		AddQuestRecord("CaptainComission1", "27");
		AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
		AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
		AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
		DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
		break;

	case "CapComission4_2":
		dialog.text = "¿Bajar el precio?! ¡Acabo de perder mi alijo por tu incompetencia! ¡Ahora puedo subir el precio! Puedes llevártelo por 200.000 pesos si quieres, o puedes largarte al diablo de aquí.";
		link.l1 = "Es demasiado caro... Adiós...";
		link.l1.go = "CapComission4_4";
		if (sti(pchar.money) >= 200000)
		{
			link.l2 = "Maldita sea, está bien, toma tu moneda.";
			link.l2.go = "CapComission4_5";
		}
		break;

	case "CapComission4_4":
		ChangeCharacterComplexReputation(pchar, "nobility", -2);
		AddQuestRecord("CaptainComission1", "28");
		AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
		AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
		AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
		DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
		DialogExit();
		break;

	case "CapComission4_5":
		dialog.text = "Puedes llevarte a este debilucho...";
		link.l1 = "Adiós.";
		link.l1.go = "exit";
		addMoneyToCharacter(pchar, -200000);
		AddQuestRecord("CaptainComission1", "29");
		AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
		AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
		AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
		DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
		pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
		AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;

	case "CapComission5":
		dialog.text = "¡Ja, ja! ¡Bien hecho! Toma a tu debilucho y buena suerte.";
		link.l1 = "Gracias. Adiós.";
		link.l1.go = "exit";
		AddQuestRecord("CaptainComission1", "34");
		AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
		AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
		AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
		DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
		AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;

	case "CapComission6":
		dialog.text = "¿Has traído el dinero, Charles? No estaba bromeando sobre vender a ese hombre a la plantación.";
		link.l1 = "Escucha, " + NPChar.name + ", hay un problema... No tengo tanto dinero. Pero estoy listo para trabajar.";
		link.l1.go = "CapComission2_2";
		if (makeint(pchar.money) > 150000)
		{
			link.l2 = "Es bueno que no lo hayas vendido. Aquí están tus monedas - 150.000 pesos. ¿Dónde puedo conseguirlo?" link.l2.go = "CapComission2_3";
		}
		break;

	// Захват пассажиров
	case "Marginpassenger":
		dialog.text = "¿Y por qué te importa lo que hago? Sabes, será mejor que te largues...";
		link.l1 = "Tshh, cálmate. Tengo una propuesta de negocios para ti. Se trata de tu prisionero.";
		link.l1.go = "Marginpassenger_1";
		break;

	case "Marginpassenger_1":
		dialog.text = "Ah, bien. ¿A quién quieres rescatar?";
		link.l1 = "Espera. No estoy aquí para comprar la libertad, estoy aquí para ofrecerte que compres a un prisionero. Bueno, y tendrás la oportunidad de obtener un rescate por él.";
		link.l1.go = "Marginpassenger_2";
		break;

	case "Marginpassenger_2":
		dialog.text = "Hum. ¿Y por qué necesitas mi intervención? ¿No quieres conseguir el dinero directamente para ti?";
		link.l1 = "Es bastante arriesgado para mí. Puedo tener problemas con las autoridades.";
		link.l1.go = "Marginpassenger_3";
		break;

	case "Marginpassenger_3":
		dialog.text = "Ja-já... está bien entonces. Vamos a echar un vistazo. ¿Quién es tu prisionero?";
		link.l1 = "Esto es " + pchar.GenQuest.Marginpassenger.Text + " " + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.City + "Gen") + ".";
		link.l1.go = "Marginpassenger_4";
		break;

	case "Marginpassenger_4":
		int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon) * 2 * stf(pchar.GenQuest.Marginpassenger.Chance)) * 100;
		dialog.text = "Ya veo. Sería un buen negocio si no estás mintiendo. Supongo que puedo pagarte por este hombre, " + iTemp + " pesos, o darte alguna información interesante en su lugar. Es tu elección.";
		link.l1 = "Mejor me llevo la moneda. Ya tuve bastante de este asunto...";
		link.l1.go = "Marginpassenger_money";
		link.l2 = "¡Ja! Cuéntame más. Estoy seguro de que me darás algo interesante.";
		link.l2.go = "Marginpassenger_offer";
		break;

	case "Marginpassenger_money":
		dialog.text = "Dinero entonces. Llévatelos. Ahora, no es tu problema. Entrega el objeto de venta aquí.";
		link.l1 = "Ya debe estar cerca de las puertas de la ciudad. ¡Gracias! Realmente me has ayudado.";
		link.l1.go = "Marginpassenger_money_1";
		break;

	case "Marginpassenger_money_1":
		iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon) * 2 * stf(pchar.GenQuest.Marginpassenger.Chance)) * 100;
		dialog.text = "De nada, tráeme más... ¡Nos vemos!";
		link.l1 = "Buena suerte...";
		link.l1.go = "exit";
		AddMoneyToCharacter(pchar, iTemp);
		ref sld = characterFromId("MarginPass");
		RemovePassenger(Pchar, sld);
		sld.lifeday = 0;
		AddQuestRecord("Marginpassenger", "12");
		AddQuestUserData("Marginpassenger", "sSum", iTemp);
		CloseQuestHeader("Marginpassenger");
		DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;

	case "Marginpassenger_offer":
		pchar.GenQuest.Marginpassenger.Goods = GetRandomGood(FLAG_GOODS_TYPE_EXPORT + FLAG_GOODS_TYPE_UNIQUE, FLAG_GOODS_VALUABLE_WOOD);
		pchar.GenQuest.Marginpassenger.GoodsQty = 200 + rand(10) * 10;
		switch (hrand(1))
		{
		case 0: // бухта на южном мейне
			SelectSouthshore();
			while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore))
				SelectSouthshore();
			dialog.text = "Es bueno hacer negocios con un hombre inteligente. Ahora escucha: en unos días para " + XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore + "Dat") + " una expedición española llegará desde el continente, cargada de mercancías valiosas. Estarán esperando un barco que supuestamente llevará la carga. Si llegas allí en una semana, tendrás la oportunidad de llevarte la carga.\nSi yo fuera tú, ya estaría moviéndome hacia mi barco. Y trae al prisionero aquí.";
			link.l1 = "¡Gracias! Las mercancías serán una buena compensación por mis problemas. Y mi pasajero ya debe estar cerca de las puertas de la ciudad. Será traído a ti.";
			link.l1.go = "Marginpassenger_offer_1";
			break;

		case 1: // просто кораблик
			SelectSouthcity();
			pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
			dialog.text = "Es bueno hacer negocios con un hombre inteligente. Ahora escucha: en aproximadamente una semana un bergantín español '" + pchar.GenQuest.Marginpassenger.ShipName1 + "' cargado con mercancías valiosas zarpará desde " + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity + "Gen") + " a " + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity1 + "Gen") + " Si te das prisa, lo atraparás fácilmente.\n¿Todavía estás aquí? Si fuera tú, ya estaría moviéndome a mi barco. Y trae al prisionero aquí.";
			link.l1 = "¡Gracias! Las mercancías serán una buena compensación por mis problemas. Y mi pasajero debe estar cerca de las puertas de la ciudad. Será llevado a ti.";
			link.l1.go = "Marginpassenger_offer_2";
			break;
		}
		sld = characterFromId("MarginPass");
		RemovePassenger(Pchar, sld);
		sld.lifeday = 0;
		pchar.GenQuest.Marginpassenger = "final";
		break;

	case "Marginpassenger_offer_1":
		DialogExit();
		AddQuestRecord("Marginpassenger", "13");
		AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore + "Dat"));
		SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
		pchar.quest.Marginpassenger.win_condition.l1 = "location";
		pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
		pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;

	case "Marginpassenger_offer_2":
		DialogExit();
		AddQuestRecord("Marginpassenger", "16");
		AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity + "Gen"));
		AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity1 + "Gen"));
		AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
		SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5 + rand(2), false);
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

void SelectSouthshore()
{
	switch (rand(6))
	{
	case 0:
		pchar.GenQuest.Marginpassenger.Shore = "shore37";
		break;
	case 1:
		pchar.GenQuest.Marginpassenger.Shore = "shore47";
		break;
	case 2:
		pchar.GenQuest.Marginpassenger.Shore = "shore48";
		break;
	case 3:
		pchar.GenQuest.Marginpassenger.Shore = "shore25";
		break;
	case 4:
		pchar.GenQuest.Marginpassenger.Shore = "shore21";
		break;
	case 5:
		pchar.GenQuest.Marginpassenger.Shore = "shore20";
		break;
	case 6:
		pchar.GenQuest.Marginpassenger.Shore = "shore19";
		break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
	case 0:
		pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
		pchar.GenQuest.Marginpassenger.Southcity1 = "Havana";
		break;

	case 1:
		pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
		pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago";
		break;

	case 2:
		pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
		pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo";
		break;
	}
}
