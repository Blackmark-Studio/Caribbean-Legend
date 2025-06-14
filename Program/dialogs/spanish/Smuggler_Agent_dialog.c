void ProcessDialogEvent()
{
	ref NPChar, her;
	aref Link, NextDiag;
	bool bOk = false;
	bool bOk2;

	int Sum, nRel, nDay, iChurchQuest2_Summ;
	ref sld;

	// Церковный квест № 2 -->
	if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra"))
	{
		iChurchQuest2_Summ = sti(PChar.rank) * 100 + (rand(3) + 1) * 100;
		PChar.GenQuest.ChurchQuest_2.Summ_To_Contra = sti(iChurchQuest2_Summ);
	}
	// <-- Церковный квест № 2

	string sColony;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	// belamour legendary edition
	bool MCGovernon = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
	bool MCAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);

	if (!CheckAttribute(npchar, "quest.trade_date"))
	{
		npchar.quest.trade_date = "";
	}

	// тереть нафиг аттрибут при прошествии дней (navy fix)
	if (CheckAttribute(pchar, "GenQuest.contraTravel.days") && GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
	{
		DeleteAttribute(pchar, "GenQuest.contraTravel");
		CloseQuestHeader("Gen_ContrabandTravel");
	}

	switch (Dialog.CurrentNode)
	{
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "Smuggling_exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		PlaceSmugglersOnShore(Pchar.quest.contraband.CurrentPlace);
		Pchar.quest.Contraband.active = true;
		pchar.GenQuest.Contraband.GuardNation = npchar.nation;
		pchar.GenQuest.Contraband.SmugglerId = npchar.id;
		SetAllContraGoods(&Stores[sti(Pchar.GenQuest.Contraband.StoreIdx)], npchar);
		ReOpenQuestHeader("Gen_Contraband");
		if (GetIslandByCityName(npchar.city) == "Mein")
		{
			AddQuestRecord("Gen_Contraband", "t1_1");
		}
		else
		{
			AddQuestRecord("Gen_Contraband", "t1");
			AddQuestUserData("Gen_Contraband", "sIsland", XI_ConvertString(GetIslandByCityName(npchar.city)));
		}
		AddQuestUserData("Gen_Contraband", "sLoc", GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt"));

		DialogExit();
		break;

	case "First time":
		//--> Jason если идёт первая часть квеста Шарля
		if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
		{
			dialog.text = "Señor, abandone este lugar. Dudo que tengamos algo de qué hablar.";
			link.l1 = "¿Oh, de verdad? ¿No te gusta mi cara? Está bien, me voy...";
			link.l1.go = "exit";
			break;
		}
		//<-- идёт первая часть квеста Шарля
		//--> Addon-2016 Jason блокировка контры во избежание конфликтов с квестами
		if (CheckAttribute(pchar, "GenQuest.SmugglersBlock") && pchar.GenQuest.SmugglersBlock == npchar.location)
		{
			dialog.text = "No hay negocio hoy.";
			link.l1 = "Lo veo.";
			link.l1.go = "exit";
			break;
		}
		//--> прибыла инспекция на Святом Милосердии
		if (CheckAttribute(npchar, "quest.SantaMisericordia"))
		{
			dialog.text = "Mis amigos y yo estamos extremadamente ocupados hoy.";
			link.l1 = "Pero yo necesito...";
			link.l1.go = "SantaMisericordia_1";
			break;
		}
		//<-- прибыла инспекция на Святом Милосердии
		//--> Jason Цена чахотки
		if (CheckAttribute(pchar, "questTemp.Consumption.Contra"))
		{
			dialog.text = "¿Qué quieres, capitán?";
			link.l1 = "¿Podemos hablar un poco?";
			link.l1.go = "Consumption";
			break;
		}
		//<-- Цена чахотки

		if (NPChar.quest.meeting == "0")
		{
			Dialog.Text = "¿Qué quieres, capitán? No conozco tu nombre y no puedo decirte el mío.";
			Link.l1 = "Soy el capitán " + GetFullName(pchar) + ".";
			Link.l1.go = "meeting";
			NPChar.quest.meeting = "1";
		}
		else
		{
			if (CheckAttribute(pchar, "GenQuest.CaptainComission.GetRumour") && GetQuestPastDayParam("GenQuest.CaptainComission.GetRumour") < 1)
			{
				if (!CheckAttribute(pchar, "GenQuest.CaptainComission.SpeakContra"))
				{
					pchar.GenQuest.CaptainComission.SpeakContra = true;
					dialog.text = "No hay negocios hoy. Hay patrullas en cada bahía, nuestro gobernador está buscando una carga que fue confiscada por algún capitán de" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " y fue escondido por él en algún lugar.";
					link.l1 = "¿Y dónde está este capitán?" + pchar.GenQuest.CaptainComission.Name + "?";
					link.l1.go = "CapComission_1";
					break;
				}
				else
				{
					dialog.text = "Sin negocios hoy.";
					link.l1 = "Lo veo.";
					link.l1.go = "exit";
					break;
				}
			}

			if (pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
			{
				dialog.text = "No hay negocio hoy.";
				link.l1 = "Lo veo.";
				link.l1.go = "exit";
				break;
			}

			if (npchar.id == "Bridgetown_Smuggler" && CheckAttribute(pchar, "questTemp.BM_BlockSmuggler"))
			{
				dialog.text = "Sin negocios hoy.";
				link.l1 = "Lo veo.";
				link.l1.go = "exit";
				break;
			}

			Dialog.Text = "¿Qué quieres, capitán?";
			if (LAi_group_GetPlayerAlarm() > 0)
			{
				Dialog.Text = RandPhraseSimple("Sé veloz, " + GetSexPhrase("colega", "chica") + ", ¿qué quieres? ¡Te están persiguiendo!", "Habla tu negocio y hazlo rápido! Los soldados te persiguen y no tenemos mucho tiempo...");
			}
			// belamour legendary edition
			bOk2 = MCGovernon || MCAdmiral;
			if (FindContrabandGoods(PChar) != -1 && !bOk2)
			{
				Link.l1 = "Quisiera comprar o vender algo.";
				Link.l1.go = "Meeting_3";
			}

			if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
				Link.l2 = "Sobre el viaje...";
			else
				Link.l2 = "Necesito llegar a un lugar.";
			Link.l2.go = "Travel";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakSmuggler"))
			{
				if ((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l3 = "Tengo algo 'especial' y creo que te podría interesar. ¡Échale un vistazo!";
					link.l3.go = "SM_ShipLetters_1";
				}
			}

			// Jason --> мини-квест Бесчестный конкурент
			if (CheckAttribute(PChar, "questTemp.Shadowtrader.seeksmugglers") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_tavern")
			{
				Link.l8 = "Tengo un negocio inusual para ti.";
				Link.l8.go = "Shadowtrader_smugglers";
			}
			// <-- мини-квест Бесчестный конкурент
			
			//--> Торговля по закону
			if(CheckAttribute(PChar, "questTemp.TPZ_ContraInfo") && NPChar.location == "BasTer_tavern")
			{
				Link.l8 = "Escucha, amigo, necesito un cargamento de vino y ron. Grande y rápido.";
				Link.l8.go = "TPZ_smugglers_1";
			}
			// <-- Торговля по закону

			// Jason --> генератор сбыта бакаута
			if (NPChar.location == "Marigo_tavern" && CheckAttribute(PChar, "GenQuest.Bakaut") && !CheckAttribute(PChar, "GenQuest.Bakaut.Info"))
			{
				Link.l9 = "Necesito reunirme con Michael Rosenkraft. Tengo la carga que le resultará interesante.";
				Link.l9.go = "bakaut";
			}
			// <-- генератор сбыта бакаута

			// Церковный генератор №2 -->
			if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
			{
				Link.l4 = "Necesito averiguar algo, amigo.";
				Link.l4.go = "Contra_GenQuest_Church_2_1";
			}

			if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
			{
				Link.l5 = "Un colega tuyo y mi buen amigo de  " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + " me contaron que estás al tanto de algunos negocios.";
				Link.l5.go = "Contra_GenQuest_Church_2_Contra2_1";
			}
			// <-- Церковный генератор №2

			Link.l7 = "Nada. Nos vemos.";
			Link.l7.go = "Exit";
		}
		break;

	case "CapComission_1":
		if (pchar.GenQuest.CaptainComission.variant == "A2")
		{
			dialog.text = "¿Dónde sino en el sótano del fuerte? Ese capitán puede revelar el escondite a las autoridades en cualquier momento y no nos quedará nada. No pienses en ningún negocio hasta que termine este alboroto.";
			link.l1 = "Escucha, tú conoces cada rincón de esta isla. ¿De verdad no tienes idea de dónde está el capitán " + pchar.GenQuest.CaptainComission.Name + "¿dónde está el escondite?";
			link.l1.go = "CapComission_4";
		}
		if (pchar.GenQuest.CaptainComission.variant == "A3")
		{
			dialog.text = "Supongo que al cielo. Fue ahorcado con su tripulación. Pero no mencionaron en la sentencia de muerte que era un barco pirata.";
			link.l1 = "¿Y por qué estás tan seguro de que el barco era uno pirata?";
			link.l1.go = "CapComission_2";
		}
		break;

	case "CapComission_2":
		dialog.text = "Habíamos estado observando la pelea desde el acantilado. Con el catalejo vimos que el barco tenía la Jolly Roger. Luego, como cinco horas después, vimos un destello en la oscuridad, como si el polvorín hubiera explotado. Eso es tiempo suficiente para mover la carga a la orilla.";
		link.l1 = "¿No sabes dónde está el escondite del capitán " + pchar.GenQuest.CaptainComission.Name + "? Conoces cada piedra de esta isla.";
		link.l1.go = "CapComission_3";
		break;

	case "CapComission_3":
		dialog.text = "No. Y también lo estamos buscando, pero no para el entretenimiento del gobernador...";
		link.l1 = "Veo.... Que tengas un buen día.";
		link.l1.go = "exit";
		AddQuestRecord("CaptainComission2", "38");
		AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")));
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim), "Name") + "Gen")));
		break;

	case "CapComission_4":
		dialog.text = "No. Y también lo estamos buscando, pero no para el divertimento del gobernador... je-je";
		link.l1 = "Ya veo... Que tengas un buen día.";
		link.l1.go = "exit";
		AddQuestRecord("CaptainComission2", "19");
		AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Gen"))); // belamour gen
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		break;

	case "SM_ShipLetters_1":
		pchar.questTemp.different.GiveShipLetters.speakSmuggler = true;
		if (sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
		{
			dialog.text = "¿Por qué decidiste eso? Soy un costero honesto. Ve y busca otro comprador.";
			link.l1 = "Gracias...";
			link.l1.go = "exit";
		}
		else
		{
			if (!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
			{
				dialog.text = "¿Por qué no? Quizás encuentre un uso para tu 'carga'. Toma " + sti(pchar.questTemp.different.GiveShipLetters.price2) + " monedas y olvídate de ello.";
				link.l1 = "No, gracias.";
				link.l1.go = "SM_ShipLetters_2";
				link.l2 = "¡Y has adivinado correctamente, estoy empezando a olvidar eso!";
				link.l2.go = "SM_ShipLetters_3";
			}
			else
			{
				if (sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
				{
					dialog.text = "¡Exactamente! Ahora estoy realmente curioso. Supongo que si te pago " + sti(pchar.questTemp.different.GiveShipLetters.price3) + " monedas y no te importarán en absoluto esos papeles.";
					link.l1 = "No, gracias.";
					link.l1.go = "SM_ShipLetters_2";
					link.l2 = "Y tienes razón. Ya los he olvidado.";
					link.l2.go = "SM_ShipLetters_3";
				}
				if (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
				{
					dialog.text = "¡Ahora, esa es una oportunidad para atrapar a ese insolente! Estoy realmente, realmente curioso. Mira, te pagaré " + sti(pchar.questTemp.different.GiveShipLetters.price4) + " en oro y ¿completamente olvidarás los documentos sobre la mesa?";
					link.l1 = "No lo haré.";
					link.l1.go = "SM_ShipLetters_2";
					link.l2 = "¡Bien, trato hecho!";
					link.l2.go = "SM_ShipLetters_3";
				}
			}
		}
		break;

	case "SM_ShipLetters_2":
		dialog.text = "Está bien, está bien, pero deja de hacer más enemigos.";
		link.l1 = "¡Igual a ti!";
		link.l1.go = "exit";
		break;

	case "SM_ShipLetters_3":
		TakeItemFromCharacter(pchar, "CaptainBook");
		if (sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
		{
			if (!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
			{
				addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2));
			}
			else
			{
				addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price3));
			}
		}
		if (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
		{
			if (!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
			{
				addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2));
			}
			else
			{
				addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price4));
			}
		}

		if ((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
		{
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			OfficersReaction("bad");
		}
		pchar.questTemp.different = "free";
		pchar.quest.GiveShipLetters_null.over = "yes"; // снимаем таймер
		AddQuestRecord("GiveShipLetters", "7");
		CloseQuestHeader("GiveShipLetters");
		DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "Meeting":
		if (CheckAttribute(pchar, "GenQuest.CaptainComission.GetRumour") && GetQuestPastDayParam("GenQuest.CaptainComission.GetRumour") < 2)
		{
			if (!CheckAttribute(pchar, "GenQuest.CaptainComission.SpeakContra"))
			{
				pchar.GenQuest.CaptainComission.SpeakContra = true;
				dialog.text = "Sin negocios hoy. Hay patrullas en cada bahía, nuestro gobernador está buscando un cargamento que fue confiscado por algún capitán de" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " y fue escondido por él en algún lugar.";
				link.l1 = "¿Y dónde está este capitán?" + pchar.GenQuest.CaptainComission.Name + "?";
				link.l1.go = "CapComission_1";
				break;
			}
			else
			{
				dialog.text = "Sin negocios hoy.";
				link.l1 = "Lo veo.";
				link.l1.go = "exit";
				break;
			}
		}

		if (pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
		{
			dialog.text = "Sin negocios hoy.";
			link.l1 = "Lo veo.";
			link.l1.go = "exit";
			break;
		}

		if (npchar.id == "Bridgetown_Smuggler" && CheckAttribute(pchar, "questTemp.BM_BlockSmuggler"))
		{
			dialog.text = "No hay negocio hoy.";
			link.l1 = "Lo veo.";
			link.l1.go = "exit";
			break;
		}

		Dialog.Text = "¿Cómo puedo ayudarte, capitán?";

		bOk2 = MCGovernon || MCAdmiral;
		if (FindContrabandGoods(PChar) != -1 && !bOk2)
		{
			Link.l1 = "Quiero comprar o vender cosas.";
			Link.l1.go = "Meeting_1";
		}

		Link.l2 = "Necesito llegar a un lugar.";
		Link.l2.go = "Travel";

		// Jason --> мини-квест Бесчестный конкурент
		if (CheckAttribute(PChar, "questTemp.Shadowtrader.seeksmugglers") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_tavern")
		{
			Link.l8 = "Tengo un negocio bastante inusual para ti.";
			Link.l8.go = "Shadowtrader_smugglers";
		}
		// <-- мини-квест Бесчестный конкурент
		
		//--> Торговля по закону
		if(CheckAttribute(PChar, "questTemp.TPZ_ContraInfo") && NPChar.location == "BasTer_tavern")
		{
			Link.l8 = "Escucha, amigo, necesito un cargamento de vino y ron. Grande y rápido.";
			Link.l8.go = "TPZ_smugglers_1";
		}
		// <-- Торговля по закону

		// Jason --> генератор сбыта бакаута
		if (NPChar.location == "Marigo_tavern" && CheckAttribute(PChar, "GenQuest.Bakaut") && !CheckAttribute(PChar, "GenQuest.Bakaut.Info"))
		{
			Link.l9 = "Necesito reunirme con Michael Rosenkraft. Tengo la carga que será interesante para él.";
			Link.l9.go = "bakaut";
		}
		// <-- генератор сбыта бакаута

		// Церковный генератор №2 -->
		if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
		{
			Link.l3 = "Necesito averiguar algo, amigo.";
			Link.l3.go = "Contra_GenQuest_Church_2_1";
		}

		if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
		{
			Link.l3 = "Un colega tuyo y mi buen amigo desde  " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + " dijo que estás al tanto de algunos negocios.";
			Link.l3.go = "Contra_GenQuest_Church_2_Contra2_1";
		}
		// <-- Церковный генератор №2

		Link.l5 = "Nada. Nos vemos.";
		Link.l5.go = "Exit";
		break;

	// Церковный генератор №2 -->
	case "Contra_GenQuest_Church_2_1":
		iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
		dialog.text = "No soy un camarada para ti. Y te puede costar.";
		link.l1 = "Hm. Necesito saber algo que no cueste más de " + FindRussianMoneyString(iChurchQuest2_Summ) + ".";
		link.l1.go = "Contra_GenQuest_Church_2_2";
		break;

	case "Contra_GenQuest_Church_2_2":
		iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
		if (sti(PChar.money) >= iChurchQuest2_Summ)
		{
			dialog.text = "Dame tus monedas. Y ten en cuenta que no obtendrás mucho por una suma como esta.";
			link.l1 = "Mira, extrañé a mis amigos. Llegué tarde a una reunión, y no me esperaron...";
			link.l1.go = "Contra_GenQuest_Church_2_3";
			AddMOneyToCharacter(PChar, -iChurchQuest2_Summ);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1");
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra");
		}
		else
		{
			dialog.text = "¡Ja, no tienes una moneda! Ven cuando consigas algo de dinero.";
			link.l1 = "De hecho, en ello.";
			link.l1.go = "exit";
		}
		break;

	case "Contra_GenQuest_Church_2_3":
		dialog.text = "¿Y por qué me necesitas?";
		link.l1 = "No están en la ciudad y no tienen un barco. Por eso pensé: ¿tal vez algunos de tus socios comerciales les hicieron un favor?";
		link.l1.go = "Contra_GenQuest_Church_2_4";
		break;

	case "Contra_GenQuest_Church_2_4":
		sColony = QuestGetColony(PChar.GenQuest.ChurchQuest_2.QuestTown);
		dialog.text = "Ya veo... Conocí a unos tipos, dijeron que necesitaban salir de la isla y no les importaba adónde. En tales casos, no preguntamos razones, solo sobre el pago. Teníamos un viaje a " + XI_ConvertString("Colony" + sColony + "Acc") + " , " + XI_ConvertString(locations[FindLocation(sColony + "_Pueblo")].IslandID + "Dat") + " . Podemos llevarte allí, si acordamos en dinero.";
		link.l1 = "Gracias, pero tengo mi propio barco.";
		link.l1.go = "exit";
		sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
		AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "8");
		AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", ""));
		AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + sColony + "Acc"));
		AddQuestUserData(sQuestTitle, "sIsland", XI_ConvertString(locations[FindLocation(sColony + "_Town")].IslandID + "Voc"));
		PChar.GenQuest.ChurchQuest_2.AskContra_2 = true;
		PChar.GenQuest.ChurchQuest_2.Contra_Colony = sColony;
		break;

	case "Contra_GenQuest_Church_2_Contra2_1":
		dialog.text = "Nunca he hecho negocios contigo.";
		link.l1 = "Podemos arreglarlo. Trajiste a mis amigos aquí hace poco. Me perdí una reunión con " + GetSexPhrase("ellos", "ellos") + ".";
		link.l1.go = "Contra_GenQuest_Church_2_Contra2_2";
		break;

	case "Contra_GenQuest_Church_2_Contra2_2":
		string sGenLocation = IslandGetLocationFromType(locations[FindLocation(PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_Town")].IslandID, "Shore");
		PChar.GenQuest.ChurchQuest_2.QuestGangShore = sGenLocation;
		PChar.GenQuest.ChurchQuest_2.BanditsInShore = true;
		dialog.text = "Mm, los dejamos en tierra en " + XI_ConvertString(sGenLocation + "Gen") + "... Como puedes imaginar, sería mejor que fueran tus amigos, de lo contrario no te aconsejo que los molestes en otro caso.";
		link.l1 = "Gracias por tu preocupación, pero estoy bien armado y soy muy encantador.";
		link.l1.go = "exit";
		SetFunctionLocationCondition("Church_GenQuest2_GenerateBandits", sGenLocation, false);
		sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
		AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "9");
		AddQuestUserData(sQuestTitle, "sShore", XI_ConvertString(sGenLocation + "Gen")); // belamour gen
		locations[FindLocation(sGenLocation)].DisableEncounters = true;
		SetFunctionTimerCondition("Church_GenQuest2_TimeIsLeft", 0, 0, 1, false);
		DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2");
		break;
		// <-- Церковный генератор №2

	case "Meeting_1":
		Dialog.Text = "Hm... ¿y cómo me afecta a mí? Probablemente te has perdido, capitán. Ve a la tienda y vende o compra allí lo que desees.";
		Link.l1 = "No, te necesito.";
		Link.l1.go = "Meeting_2";
		Link.l2 = "Gracias por tu consejo. Que tengas un buen día.";
		Link.l2.go = "exit";
		break;

	case "Meeting_2":
		Dialog.Text = "¿Para qué?";
		Link.l1 = "Quizás, ¿estarás interesado en algunas mercancías especiales? O quizás, ¿tienes algo que ofrecerme a cambio?";
		Link.l1.go = "Meeting_3";
		break;

	case "Meeting_3":
		int iTmp = false;
		int iChIdx, i;

		// поиск мин.  те старшего класса
		for (i = 0; i < COMPANION_MAX; i++)
		{
			iChIdx = GetCompanionIndex(GetMainCharacter(), i);
			if (iChIdx >= 0)
			{
				sld = GetCharacter(iChIdx);
				if (GetCharacterShipClass(sld) < ((MOD_SKILL_ENEMY_RATE / 5.0) + 1.5))
					iTmp = true;
			}
		}

		if (iTmp)
		{
			dialog.text = NPCStringReactionRepeat("¿Por qué no tomas un hombre de guerra real la próxima vez?. Tu barco puede ser avistado desde el fuerte fácilmente. No arriesgaremos nuestras cabezas. Ven en un solo barco pequeño la próxima vez.", "¿Debería repetirme? Encuentra un barco más pequeño y luego hablaremos.", "¿Realmente eres tan idiota? Consíguete una goleta o un bergantín. Solo en ese caso tendremos negocios.", "Oh, tal idiota...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Bien, te entendí.", "Lo entiendo, solo quería especificar algo.", "No, no un idiota, solo un tacaño. Pensé que algo había cambiado. Tomaría unos cuantos pinazas más...", "Mira al espejo...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			break;
		}
		bOk = CheckAttribute(pchar, "GenQuest.contraTravel.active") && (sti(pchar.GenQuest.contraTravel.active) == true);
		bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
		bool bOk3 = CheckAttribute(Pchar, "questTemp.pirateStartQuest") && (Pchar.questTemp.pirateStartQuest == "3");
		if (bOk)
		{
			if (GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
			{ // просрочка
				DeleteAttribute(PChar, "GenQuest.contraTravel");
				CloseQuestHeader("Gen_ContrabandTravel");
				bOk = false;
			}
		}

		// navy --> PGG
		if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
		{
			Dialog.Text = "Lo siento, " + GetSexPhrase("colega", "chica") + ", ya estamos ocupados. Vuelve en unos días.";
			Link.l1 = "Demasiado mal...";
			Link.l1.go = "Exit";
			break;
		}
		// navy <--

		if (bOk || bOk2 || bOk3)
		{
			Dialog.Text = "¿Qué tal si terminamos nuestros asuntos actuales primero?";
			Link.l1 = "Supongo que tienes razón.";
			Link.l1.go = "Exit";
		}
		else
		{
			if (npchar.quest.trade_date != lastspeak_date)
			{
				npchar.quest.trade_date = lastspeak_date;

				if (ChangeContrabandRelation(pchar, 0) > 5)
				{
					Pchar.quest.contraband.CurrentPlace = SelectSmugglingLocation();
					Pchar.quest.contraband.City = NPChar.city;
					if (Pchar.quest.contraband.CurrentPlace != "None") // boal fix
					{
						if (ChangeContrabandRelation(pchar, 0) >= 70)
						{
							Dialog.Text = "Sé que podemos hacer negocios contigo. Te estaremos esperando en " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
						}
						else
						{
							Dialog.Text = "Hm... Quizás, podemos encontrarle un comprador. Te estaremos esperando en " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
						}
						Link.l1 = "Está bien. Nos vemos allí.";
						Link.l1.go = "Smuggling_exit";
					}
					else
					{ // boal fix
						Dialog.Text = "No hay negocio hoy. Ven aquí mañana.";
						Link.l1 = "Bien.";
						Link.l1.go = "Exit";
					}
				}
				else
				{
					Dialog.Text = "¿Realmente crees que alguien querrá trabajar contigo después de todo eso? Deberías alegrarte de que no enviamos a los cazadores de recompensas detrás de ti.";
					Link.l1 = "Qué lástima. No tengo oportunidad de convertirme en un contrabandista.";
					Link.l1.go = "Exit";
				}
			}
			else
			{
				Dialog.Text = "No hay negocio hoy. Ven aquí mañana.";
				Link.l1 = "Bien.";
				Link.l1.go = "Exit";
			}
		}
		break;
		////////////////////////////////////////////////////////////////////////////////
		//	Корсарское метро
		////////////////////////////////////////////////////////////////////////////////
	case "Travel":
		// navy --> PGG
		if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
		{
			Dialog.Text = "Lo siento, " + GetSexPhrase("colega", "chica") + ", ya estamos ocupados. Vuelve en unos días.";
			Link.l1 = "Demasiado malo.";
			Link.l1.go = "Exit";
			break;
		}
		// navy <--
		// если нет корабля у ГГ и нет компаньонов все ок
		if (sti(pchar.ship.type) == SHIP_NOTUSED && GetCompanionQuantity(pchar) == 1 && GetPassengersQuantity(pchar) == 0)
		{
			// случай если уже была инфа
			if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
			{
				// платил уже
				if (CheckAttribute(pchar, "GenQuest.contraTravel.payed") && sti(pchar.GenQuest.contraTravel.payed) == true)
				{
					Dialog.Text = "¿Pensé que ya habíamos acordado el trato?";
					Link.l2 = "¡En efecto!";
				}
				// не платил, значит можно запалатить пока не вышел срок.
				else
				{
					if (GetQuestPastDayParam("contraTravel") == sti(PChar.GenQuest.contraTravel.days))
					{
						Dialog.Text = "¿Has traído el dinero?";
						Link.l1 = "Sí.";
						Link.l1.go = "Travel_pay";
						Link.l3 = "He cambiado de opinión...";
						Link.l3.go = "Travel_abort";
						Link.l2 = "Aún no.";
					}
					else
					{
						if (GetQuestPastDayParam("contraTravel") < sti(PChar.GenQuest.contraTravel.days))
						{
							Dialog.Text = "Ya te he contado todo.";
							Link.l2 = "Exactamente.";
							Link.l1 = "He cambiado de opinión...";
							Link.l1.go = "Travel_abort";
						}
						else // просрочка
						{
							Dialog.Text = "No puedo ayudarte hoy. Ven en dos días y tal vez tendremos algo para ti.";
							Link.l2 = "Demasiado mal.";
							DeleteAttribute(PChar, "GenQuest.contraTravel");
							CloseQuestHeader("Gen_ContrabandTravel");
						}
					}
				}
			}
			// если не было договора, обговариваем условия
			else
			{
				nRel = ChangeContrabandRelation(pchar, 0);
				// если нормальные отношения и количество подстав меньше 20, работаем....
				if (nRel > 0 && Statistic_AddValue(PChar, "contr_TravelKill", 0) < 20)
				{
					// бухта...
					pchar.GenQuest.contraTravel.CurrentPlace = SelectSmugglingLocation();
					aref arTmp;
					makearef(arTmp, pchar.GenQuest.contraTravel);
					SetSmugglersTravelDestination(arTmp);
					// за сколько доставят
					pchar.GenQuest.contraTravel.price = (sti(PChar.rank) * 250 + (100 - nRel) * 10 + rand(30) * 20) + sti(arTmp.destination.days) * 100;

					// если метро активно, и нет пассажиров у ГГ, и ещё сегодня не виделись, есть доступная бухта, и ранд ...
					bOk = !bPauseContrabandMetro && CheckNPCQuestDate(npchar, "Travel_Talk") &&
						  Pchar.GenQuest.contraTravel.CurrentPlace != "None" && rand(50) < nRel;
					bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
					if (bOk && !bOk2)
					{
						nDay = 1 + rand(3);
						SetNPCQuestDate(npchar, "Travel_Talk");
						SaveCurrentQuestDateParam("contraTravel");

						Dialog.Text = "Bueno, podemos llevarte a " + GetConvertStr(locations[FindLocation(pchar.GenQuest.contraTravel.destination.loc)].id, "LocLables.txt") + " cerca " + XI_ConvertString("Colony" + pchar.GenQuest.contraTravel.destination + "Gen") + " para " + pchar.GenQuest.contraTravel.price + " oro. Trae el dinero en " + FindRussianDaysString(nDay) + ". El barco te estará esperando en " + GetConvertStr(locations[FindLocation(Pchar.GenQuest.contraTravel.CurrentPlace)].id, "LocLables.txt") + "exactamente 24 horas.";

						pchar.GenQuest.contraTravel.days = nDay;
						Link.l1 = "Me funciona.";
						Link.l1.go = "Travel_agree";
						Link.l2 = "No, gracias.";
					}
					else
					{
						Dialog.Text = "No puedo ayudarte hoy. Ven en dos días y quizás tendremos algo para ti.";
						Link.l2 = "Demasiado mal.";
					}
				}
				// нет, посылаем в сад
				else
				{
					Dialog.Text = "¿Realmente crees que alguien querrá trabajar contigo después de todo eso? Mejor agradece que no enviamos a los cazadores de recompensas tras de ti. ¡Lárgate!";
					Link.l2 = "Vaya, sin suerte de nuevo.";
				}
			}
		}
		// корабль есть, посылаем в сад...
		else
		{
			if (GetPassengersQuantity(pchar) != 0)
			{
				Dialog.Text = "No, no os llevaremos a todos. Solo a uno de vosotros.";
				Link.l2 = RandSwear() + "¡No lo necesito de todas formas!";
			}
			else
			{
				Dialog.Text = "¿Por qué no usas tu propio barco? No, no te llevaremos.";
				Link.l2 = "Bien, como desees.";
			}
		}
		Link.l2.go = "Exit";
		break;

	// отмена
	case "Travel_abort":
		ChangeContrabandRelation(pchar, -2);
		DeleteAttribute(PChar, "GenQuest.contraTravel");
		CloseQuestHeader("Gen_ContrabandTravel");
		Dialog.Text = "Lo que quieras.";
		Link.l1 = "";
		Link.l1.go = "Exit";
		break;

	// ГГ согласен ехать
	case "Travel_agree":
		ReOpenQuestHeader("Gen_ContrabandTravel");
		AddQuestRecord("Gen_ContrabandTravel", "1");
		AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("Gen_ContrabandTravel", "sLoc", GetConvertStr(pchar.GenQuest.contraTravel.CurrentPlace, "LocLables.txt"));
		AddQuestUserData("Gen_ContrabandTravel", "sLocTo", GetConvertStr(pchar.GenQuest.contraTravel.destination.loc, "LocLables.txt"));
		AddQuestUserData("Gen_ContrabandTravel", "sPlaceTo", XI_ConvertString("Colony" + pchar.GenQuest.contraTravel.destination + "Gen"));
		AddQuestUserData("Gen_ContrabandTravel", "sDays", FindRussianDaysString(sti(pchar.GenQuest.contraTravel.days)));
		AddQuestUserData("Gen_ContrabandTravel", "sPrice", pchar.GenQuest.contraTravel.price);

		// активируем квест
		pchar.GenQuest.contraTravel.active = true;
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	// ГГ согласен платить
	case "Travel_pay":
		// денег хватает?
		Sum = sti(pchar.GenQuest.contraTravel.price);
		if (sti(pchar.money) >= Sum)
		{
			AddMoneyToCharacter(pchar, -1 * Sum);
			// ставим флаг оплаты
			pchar.GenQuest.contraTravel.payed = true;
			Dialog.Text = "Un placer hacer negocios contigo. No llegues tarde al barco.";
			Link.l1 = "Lo intentaré.";
			AddQuestRecord("Gen_ContrabandTravel", "2");
			AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("", ""));

			// ставим контру.
			PlaceSmugglersOnShore(PChar.GenQuest.contraTravel.CurrentPlace);
			// корабль на волнах в бухте....
			Sum = sti(pchar.GenQuest.contraTravel.destination.days);
			sld = GetCharacter(NPC_GenerateCharacter("Abracham_Gray", "citiz_46", "man", "man", 5, PIRATE, Sum + 2, true, "hunter"));
			// воскресим...
			sld.nation = PIRATE;
			SetRandomNameToCharacter(sld);
			SetMerchantShip(sld, rand(GOOD_PAPRIKA));
			SetFantomParamHunter(sld);
			SetCaptanModelByEncType(sld, "pirate");
			SetCharacterShipLocation(sld, PChar.GenQuest.contraTravel.CurrentPlace);

			SetTimerCondition("RemoveTravelSmugglers", 0, 0, 1, false);
		}
		// нет, посылаем в сад...
		else
		{
			Dialog.Text = "Parece que no tienes suficiente dinero." Link.l1 = "Qué lástima, volveré más tarde.";
		}
		Link.l1.go = "Exit";
		break;
		////////////////////////////////////////////////////////////////////////////////
		//	END OF Корсарское метро
		////////////////////////////////////////////////////////////////////////////////

	// Jason --> мини-квест Бесчестный конкурент
	case "Shadowtrader_smugglers":
		dialog.text = "Muy interesante. Muestra lo que tienes.";
		link.l1 = "He oído que hay una tienda subterránea donde puedes comerciar con mercancías muy 'especiales' a un precio tentador y tú has ayudado a iniciar esta tienda. Me gustaría hablar con su dueño.";
		link.l1.go = "Shadowtrader_fail";
		link.l2 = "He oído que hay una tienda clandestina donde puedes comerciar mercancías muy 'especiales' a un precio tentador. Tengo que zarpar en unos días y no tengo suficiente dinero para comprar todo lo que necesito en la tienda, así que necesito y quiero ahorrar algo de monedas... algunas personas me dijeron que tú puedes ayudarme con eso.";
		link.l2.go = "Shadowtrader_smugglers_1";
		DeleteAttribute(pchar, "questTemp.Shadowtrader.seeksmugglers");
		DelLandQuestMark(npchar);
		break;

	case "Shadowtrader_fail":
		dialog.text = "¿De qué estás hablando? No te entiendo. No empezamos una tienda aquí, esto es una tontería, ¡ja-ja! Si quieres comerciar, tráenos bienes y hablaremos a nuestra manera habitual... Una tienda, ¡ja!";
		link.l1 = "Mmm...";
		link.l1.go = "exit";
		pchar.questTemp.Shadowtrader = "true";
		AddQuestRecord("Shadowtrader", "3");
		CloseQuestHeader("Shadowtrader");
		DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
		break;

	case "Shadowtrader_smugglers_1":
		dialog.text = "¿Quieres un descuento? Fácil. Ven a la puerta del maestro del puerto cuando esté oscuro. Nuestro hombre te encontrará y te llevará al lugar correcto.";
		link.l1 = "Está bien. ¡Estaré allí!";
		link.l1.go = "Shadowtrader_smugglers_2";
		break;

	case "Shadowtrader_smugglers_2":
		pchar.questTemp.Shadowtrader.SeekTrader = "true";
		AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
		AddQuestRecord("Shadowtrader", "5");
		AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony" + pchar.questTemp.Shadowtrader.City + "Gen"));
		SetFunctionTimerCondition("ShadowtraderTimeSmugglers_Over", 0, 0, 2, false);
		int iNation = pchar.questTemp.Shadowtrader.nation;
		int iRank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 3;
		sld = GetCharacter(NPC_GenerateCharacter("ShadowAgent_1", "citiz_" + (rand(9) + 41), "man", "man", iRank, iNation, 2, true, "quest"));
		SetFantomParamFromRank(sld, iRank, true);
		GiveItem2Character(sld, "blade_04");
		EquipCharacterbyItem(sld, "blade_04");
		LAi_SetCitizenType(sld);
		sld.dialog.Filename = "Common_citizen.c";
		sld.dialog.currentnode = "First time";
		sld.greeting = "cit_common";
		sld.city = pchar.questTemp.Shadowtrader.City;
		LAi_SetImmortal(sld, true);
		ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_town", "goto", "goto1");
		pchar.quest.Shadowtrader_SMG.win_condition.l1 = "locator";
		pchar.quest.Shadowtrader_SMG.win_condition.l1.location = pchar.questTemp.Shadowtrader.City + "_town";
		pchar.quest.Shadowtrader_SMG.win_condition.l1.locator_group = "reload";
		pchar.quest.Shadowtrader_SMG.win_condition.l1.locator = "reload10_back";
		pchar.quest.Shadowtrader_SMG.win_condition.l2 = "Night";
		pchar.quest.Shadowtrader_SMG.function = "ShadowAgent";
		DialogExit();
		break;
	// <-- Бесчестный конкурент
	//--> Торговля по закону
	case "TPZ_smugglers_1":
		dialog.text = "Ja, ¿te ha enviado ese bribón detrás de la barra, verdad?";
		link.l1 = "¿Y eso importa? ¿Puedes conseguirlo o debo buscar a otra persona?";
		link.l1.go = "TPZ_smugglers_2";
		DelLandQuestMark(npchar);
	break;
		
	case "TPZ_smugglers_2":
		dialog.text = "Puedo conseguir lo que sea, ¿entiendes? Siempre que paguen bien. Pero ese maldito gobernador nos tiene totalmente acorralados. Ya no tratamos con alcohol - las botellas hacen ruido, se oyen desde una buena legua, las ganancias son miserables y el riesgo de acabar en la horca es enorme. Así que discúlpame.";
		link.l1 = "Vaya... Y aún así dices que puedes conseguirlo todo.";
		link.l1.go = "TPZ_smugglers_3";		
	break;
		
	case "TPZ_smugglers_3":
		dialog.text = "¡Puedo! Simplemente no quiero. Hay un tipo por aquí, vive justo al lado de la residencia, ¿lo puedes creer? Ja-ja. Qué idiota... ¿En qué estaba? Ah, sí. Él trafica discretamente con algo de licor bajo cuerda. Justo bajo la peluca del gobernador, ja-ja. Pregúntale, tal vez te diga algo. Sus cantidades son pequeñas, claro, pero es mejor que nada.";
		link.l1 = "No es que hayas ayudado mucho, pero gracias de todos modos.";
		link.l1.go = "TPZ_smugglers_4";		
	break;
	
	case "TPZ_smugglers_4":
			DialogExit();
			AddQuestRecord("TPZ", "3");
			DeleteAttribute(pchar, "questTemp.TPZ_ContraInfo");
			
			// проведаем дом Кристиана
			sld = GetCharacter(NPC_GenerateCharacter("TPZ_Kristian", "citiz_17", "man", "man", 1, FRANCE, -1, false, "quest"));
			sld.name = "Christian";
			sld.lastname = "Deluce";
			LAi_SetOwnerType(sld);
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian";
			ChangeCharacterAddressGroup(sld, "BasTer_houseF3", "barmen", "stay");
			sld.City = "BasTer";
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			AddLandQuestMark(sld, "questmarkmain");
	break;
	//<-- Торговля по закону

	//--> Цена чахотки
	case "Consumption":
		dialog.text = "Hay muchos juerguistas aquí y si no tienes ningún negocio, señor, bebe o habla con ellos. Este lugar está ocupado.";
		link.l1 = "Intentémoslo de nuevo. Te pagaré por tu tiempo y mi curiosidad. Necesito respuestas.";
		link.l1.go = "Consumption_1";
		break;

	case "Consumption_1":
		if (sti(pchar.money) >= 3002)
		{
			dialog.text = "¡Pagará, ja! Mi tiempo no es barato, señor, cuesta 3000 pesos más esta bebida asquerosa que llaman ron por error.";
			link.l1 = "¡Trato hecho! Ahora cuéntame sobre uno de los tuyos que pasó medio año en la prisión y luego murió. ¿Qué ocurrió con él?";
			link.l1.go = "Consumption_2";
		}
		else
		{
			dialog.text = "Será mejor que llenes tus bolsillos con plata o oro, que sería mejor. Luego ven y habla, no tengo tiempo para hablar contigo gratis.";
			link.l1 = "...";
			link.l1.go = "exit";
		}
		break;

	case "Consumption_2":
		AddMoneyToCharacter(pchar, -3002);
		dialog.text = "Recuerdo eso, aunque no entiendo por qué te interesa. El chico realmente se volvió loco detrás de esas rejas. Se convirtió en un borracho y siempre estaba hablando alguna tontería sobre la consumición que se llevaba a la gente y de la que nadie estaba a salvo. Dijo que esa consumición tenía un nombre y ni siquiera te atrevas a decirlo en voz alta. Si lo haces, vendrá y te llevará también a ti.";
		link.l1 = "¿Y qué le pasó después?";
		link.l1.go = "Consumption_3";
		break;

	case "Consumption_3":
		dialog.text = "La historia tiene un final extraño, señor. Al principio, a los locales y marineros les gustaba su cuento, pero eventualmente se hartaron de él. Eso siempre sucede con cualquier fábula. Así que lo provocaron para que dijera el nombre. El chico se resistía y resistía, pero no pudo soportar las burlas y literalmente lo gritó\nNadie sintió nada especial, las velas no se apagaron, pero la pobre alma fue encontrada muerta la próxima mañana detrás de la taberna con la garganta cortada.";
		link.l1 = "No veo ninguna magia aquí. Dime el nombre.";
		link.l1.go = "Consumption_4";
		break;

	case "Consumption_4":
		dialog.text = "Recuerdo el nombre, pero maldita sea, no voy a decirlo en voz alta. Hay algo siniestro en todo esto. ¿No lo ves?";
		link.l1 = "Oye, compadre, has recibido una billetera llena de monedas de mi parte, ¿recuerdas? ¿Serías tan amable de decirme el nombre?";
		link.l1.go = "Consumption_5";
		break;

	case "Consumption_5":
		dialog.text = "Oh no va a terminar bien, señor, confía en mí... (bajando la voz) Dijo, Juan...";
		link.l1 = "¡Maldito seas! ¿Juan? Es solo un nombre común y es bastante popular aquí. ¿Por qué es tan especial?";
		link.l1.go = "Consumption_6";
		break;

	case "Consumption_6":
		dialog.text = "No lo sé, pero el hombre que mencionó este nombre fue asesinado. Confía en mi instinto, algo está muy mal con ese nombre. ¿Eso es todo lo que querías saber?";
		link.l1 = "Supongo que sí. Puedes comprar una bebida para ti mismo. ¡Nos vemos!";
		link.l1.go = "Consumption_7";
		break;

	case "Consumption_7":
		DialogExit();
		DeleteAttribute(pchar, "questTemp.Consumption.Contra");
		pchar.questTemp.Consumption.AskJuan = 0;
		pchar.questTemp.Consumption = "current";
		AddQuestRecord("Consumption", "6");
		break;
	//<-- Цена чахотки

	// Jason --> генератор сбыта бакаута
	case "bakaut":
		dialog.text = "¿Es así? Bien. Mynheer Rosenkraft necesita un lote de sándalo, pero no menos que " + FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)) + ". ¿Tienes suficiente carga?";
		if (GetSquadronGoods(pchar, GOOD_SANDAL) >= sti(pchar.GenQuest.Bakaut.Value))
		{
			link.l1 = "Lo hago. ¿Dónde puedo encontrar al señor Rosenkraft?";
			link.l1.go = "bakaut_1";
		}
		else
		{
			link.l1 = "Hm. No tengo tanto ahora mismo.";
			link.l1.go = "bakaut_no";
		}
		break;

	case "bakaut_no":
		dialog.text = "No molestes al mynheer Rosenkraft entonces. Ven cuando tengas suficiente carga.";
		link.l1 = "Bien.";
		link.l1.go = "exit";
		break;

	case "bakaut_1":
		dialog.text = "Su galeón estará navegando cerca de las costas de " + XI_ConvertString(pchar.GenQuest.Bakaut.Island + "Gen") + " durante varios días. Así que no llegues tarde, podría zarpar hacia otro lugar del archipiélago.";
		link.l1 = "Está bien, aceleraré. ¡Gracias!";
		link.l1.go = "bakaut_2";
		break;

	case "bakaut_2":
		DialogExit();
		sld = characterFromId("Rozencraft");
		sld.DeckDialogNode = "bakaut";
		DeleteAttribute(sld, "DontDeskTalk"); // можно выслать шлюпку
		pchar.GenQuest.Bakaut.Info = "true";
		ReOpenQuestHeader("Bakaut");
		AddQuestRecord("Bakaut", "1");
		AddQuestUserData("Bakaut", "sIsland", XI_ConvertString(pchar.GenQuest.Bakaut.Island + "Gen"));
		AddQuestUserData("Bakaut", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Bakaut.DaysQty)));
		AddQuestUserData("Bakaut", "sQty", FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)));
		// таймер
		pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1 = "Timer";
		pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.hour = sti(GetTime());
		pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.day = GetAddingDataDay(0, 0, sti(pchar.GenQuest.Bakaut.DaysQty));
		pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.Bakaut.DaysQty));
		pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.year = GetAddingDataYear(0, 0, sti(pchar.GenQuest.Bakaut.DaysQty));
		pchar.quest.Bakaut_Rozencraft_Find.function = "Bakaut_RozencraftRemove";
		break;
	// <-- генератор сбыта бакаута

	//--> прибыла инспекция на Святом Милосердии
	case "SantaMisericordia_1":
		dialog.text = "Y necesito vivir hasta mañana. El maldito 'Misericordia' está en la ciudad. Vete.";
		link.l1 = "Tal drama...";
		link.l1.go = "exit";
		break;
		//<-- прибыла инспекция на Святом Милосердии
	}
}
