// разговор с капитаном на палубе  Boal
// homo 25/06/06
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	// belamour рыбацкое судно
	int i, iTemp, iQty;
	string sTemp;
	// homo Осады
	aref aData;
	makearef(aData, NullCharacter.Siege);
	string sCap, sGroup;
	string fort;
	bool bOk, bOk1, bOk2;

	if (CheckAttribute(aData, "nation"))
	{
		sCap = NationShortName(sti(aData.nation)) + "SiegeCap_";
		sGroup = "Sea_" + sCap + "1";

		// string myships  = GetCompanionQuantity(PChar);
		// string escships = Group_GetCharactersNum(sGroup);

		switch (sti(aData.conation))
		{
		case 0:
			fort = "English fort";
			break;
		case 1:
			fort = "French fort";
			break;
		case 2:
			fort = "Spanish fort";
			break;
		case 3:
			fort = "Dutch fort";
			break;
		case 4:
			fort = "Pirate fort";
			break;
		}
		int ifortPower = sti(colonies[FindColony(aData.colony)].FortValue);
		int fortDamage = CheckFortInjuri();
		int SquadronDamage = CheckSquadronInjuri();
	}

	int iMoney;
	ref sld;

	if (CheckNPCQuestDate(npchar, "Card_date"))
	{
		SetNPCQuestDate(npchar, "Card_date");
		npchar.money = 3000 + rand(10) * makeint(100 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
	}
	else
	{
		if (sti(npchar.money) > CAP_MAX_MONEY || sti(npchar.money) < CAP_MIN_MONEY)
		{
			npchar.money = CAP_MIN_MONEY + rand(CAP_NORM);
		}
	}
	// homo 26/06/06
	ProcessCommonDialogRumors(NPChar, Link, Diag);
	switch (Dialog.CurrentNode)
	{
	case "Exit":
		DialogExit();
		Diag.CurrentNode = Diag.TempNode;
		break;

	case "First time":
		if (!bDisableMapEnter)
		{
			//--> Jason эскорт 2 уровень
			if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "begin" && NPChar.id == "WMCaptain")
			{
				dialog.text = "¡Hola, capitán. Maldita sea, no tienes idea de cuánto me alegra verte!";
				link.l1 = "Hola. Permíteme presentarme, " + GetFullName(PChar) + ". Me alegra verte vivo y enérgico también, he venido aquí específicamente para buscarte a ti y a tu barco.";
				link.l1.go = "WM_Captain";
				break;
			}
			if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "wait" && NPChar.id == "WMCaptain")
			{
				dialog.text = "¿Has traído el material que solicité?";
				if (sti(pchar.questTemp.WPU.Escort.Planks) - GetSquadronGoods(pchar, GOOD_PLANKS) <= 0 && sti(pchar.questTemp.WPU.Escort.Sailcloth) - GetSquadronGoods(pchar, GOOD_SAILCLOTH) <= 0 && sti(pchar.questTemp.WPU.Escort.Linen) - GetSquadronGoods(pchar, GOOD_COTTON) <= 0)
				{
					link.l1 = "Sí. Todo lo que necesitas para reparar tu barco está en mi bodega.";
					link.l1.go = "WM_Captain_5";
				}
				else
				{
					link.l1 = "No, todavía estoy trabajando en ello.";
					link.l1.go = "exit";
				}
				break;
			}
			if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "toCap" && NPChar.id == "WMCaptain")
			{
				dialog.text = "¡Ahoy, " + GetAddress_Form(NPChar) + ". Mi nombre es " + GetFullName(NPChar) + ", soy el capitán de este barco. Permíteme expresar mi más sincera gratitud por tu ayuda en la lucha contra esta maldita escoria pirata: si no hubieras intervenido, las cosas podrían haber resultado bastante sombrías para nosotros. ¡Realmente nos salvaste, maldita sea!";
				link.l1 = "No fue nada, " + GetAddress_FormToNPC(NPChar) + ". Permíteme presentarme, " + GetFullName(PChar) + ", vine a ti a petición del maestro del puerto " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Escort.StartCity + "Gen") + ". Me informó sobre las desgracias de tu caravana y me envió a encontrar tu barco.";
				link.l1.go = "VSP_Captain";
				break;
			}
			//<-- эскорт 2 уровень

			if (CheckAttribute(NPChar, "surrendered"))
			{
					Pchar.GenQuest.MoneyForCaptureShip = makeint(Group_GetLiveCharactersNum( GetGroupIDFromCharacter(NPChar)))*(8 - sti(RealShips[sti(NPChar.Ship.Type)].Class))*(1+rand(10))*500);
					if(HasShipTrait(pchar, "trait14")) Pchar.GenQuest.MoneyForCaptureShip = makeint(sti(Pchar.GenQuest.MoneyForCaptureShip) * 1.35);
					dialog.text = "Espera, podrías matarme de esta manera. ¿Qué quieres de mí?";
					// выкуп
					link.l1 = "Resolvamos este asunto pacíficamente. Supongo que el rescate será la mejor decisión. Una suma de " + Pchar.GenQuest.MoneyForCaptureShip + " pesos me vendrán bien, " + GetAddress_FormToNPC(NPChar) + ". ¡Y después de eso puedes perderte!";
					link.l1.go = "surrender1";
					// обираем до нитки
					link.l2 = "Me gustaría ver lo que tienes en tu bodega. Y después de eso, tú y tu tripulación pueden ir a donde quieran.";
					link.l2.go = "surrender2";
					break;
			}

			// Голландский Гамбит, против всех
			if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetingStivesant" && NPChar.id == "Stivesant")
			{
				dialog.text = "Hola, señor. Es un placer verle. Probablemente el Capitán Longway vendrá a bordo más tarde, ¿verdad?";
				link.l1 = "Buenas tardes, señor Stuyvesant. Permítame presentarme, " + GetFullName(pchar) + ". Longway no vendrá, él no está en 'Meifeng'.";
				link.l1.go = "Stivesant_1";
				pchar.quest.QuestShipsTerms_Over.over = "yes"; // снять таймер
				break;
			}
			if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FleutOnTrinidad" && NPChar.id == "Keller")
			{
				DelLandQuestMark(npchar);
				dialog.text = "Ahoy, capitán. ¿Qué te ha traído a mi filibote?";
				link.l1 = "Buenas tardes, señor Keller. Permítame presentarme, " + GetFullName(pchar) + ". He venido a pedir tu ayuda en un asunto inusual.";
				link.l1.go = "Keller_1";
				break;
				// Голландский гамбит
			}
			// belamour рыбацкое судно -->
			if (npchar.id == "FishingBoatCap")
			{
				if (!CheckAttribute(pchar, "GenQuest.FishingBoatSecondTime"))
				{
					Dialog.text = TimeGreeting() + ", " + GetAddress_Form(NPChar) + "¡Yo soy el capitán de " + GetFullName(NPChar) + ". ¿Qué te trae a bordo de mi barco?";
					link.l1 = "Y buen día para ti. ¿Qué haces en esta bahía?";
					link.l1.go = "FishingBoat";
					break;
				}
				else
				{
					Diag.CurrentNode = "first time";
					dialog.text = "¿Algo más que te gustaría discutir?";
					link.l1 = "Quería " + GetSexPhrase("preguntarte", "preguntarte") + " por las últimas noticias del archipiélago.";
					link.l1.go = "rumours_capitan";
					if (CheckAttribute(pchar, "GenQuest.FishingBoatDialogEnb"))
					{
						link.l2 = "Muéstrame de nuevo, por favor, qué tipo de baratijas tienes a la venta. ";
						link.l2.go = "Торговля";
						if (pchar.GenQuest.FishingBoatDialogEnb != "no special goods")
						{
							link.l3 = "Hmm, quizás deberías buscar un poco más en la bodega, ¿tal vez encuentres algo para vender?";
							link.l3.go = "Особые товары";
						}
					}
					link.l4 = "¡Nada especial, solo vine a saludarte!";
					link.l4.go = "exit";
					break;
				}
			}
			// <-- рыбацкое судно

			// belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			//  генерал губернатор
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				Dialog.text = "Gobernador General, Su Gracia, ¡saludos! ¿Qué puedo hacer por usted?";
				link.l1 = "¡Tengo negocios para ti!";
				link.l1.go = "quests";
				link.l2 = "¡Nada especial, solo vine a saludarte!";
				link.l2.go = "exit";
				break;
			}
			// вице адмирал
			if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
			{
				Dialog.text = "¡Bienvenido a bordo de mi barco, Vicealmirante! ¿Qué puedo hacer por ti?";
				link.l1 = "¡Tengo negocio para ti!";
				link.l1.go = "quests";
				link.l2 = "¡Nada especial, solo vine a saludarte!";
				link.l2.go = "exit";
				break;
			}
			// Офицер с патентом
			if (IsOfficerFullEquip() && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
			{
				Dialog.text = "¡Encantado de ver a un compañero de trabajo, Capitán! ¿Cómo puedo ayudar?";
				link.l1 = "¡Tengo negocios para ti!";
				link.l1.go = "quests";
				link.l2 = "¡Nada especial, solo vine a saludarte!";
				link.l2.go = "exit";
				break;
			}
			// <-- legendary edition
			if (CheckAttribute(NPChar, "EncType") && NPChar.EncType == "war")
			{
				Dialog.text = TimeGreeting() + ", " + GetAddress_Form(NPChar) + " ¡Yo soy " + GetFullName(NPChar) + " el capitán de un barco perteneciente a la " + NationKingsName(NPChar) + ". flota. ¿Qué te ha traído a bordo de mi barco?";
			}
			else
			{
				Dialog.text = TimeGreeting() + ", " + GetAddress_Form(NPChar) + ". ¡Soy el capitán " + GetFullName(NPChar) + ". ¿Qué te ha traído a bordo de mi barco?";
			}
			link.l1 = "Mi nombre es " + GetFullName(Pchar) + ". ¡Te traigo algunos asuntos que te atañen!";
			link.l1.go = "quests";
			link.l2 = "Oh, nada, ¡solo vine" + GetSexPhrase("", "") + " para saludarte!";
			link.l2.go = "exit";
		}
		else
		{
			Dialog.text = "¿No te has dado cuenta, " + GetAddress_Form(NPChar) + "¿, que estamos en una batalla? ¡No es momento para hablar!";
			link.l1 = "¡Totalmente de acuerdo! Regresaré a mi barco.";
			link.l1.go = "exit";
		}
		Diag.TempNode = "first time";
		break;

	case "quests":
		// belamour рыбацкое судно -->
		if (npchar.id == "FishingBoatCap")
		{
			if (!CheckAttribute(pchar, "GenQuest.FishingBoatSecondTime"))
			{
				Dialog.text = TimeGreeting() + ", " + GetAddress_Form(NPChar) + ". ¡Soy el capitán " + GetFullName(NPChar) + ". ¿Qué te trae a bordo de mi barco?";
				link.l1 = "Y buen día para ti. ¿Qué haces en esta bahía?";
				link.l1.go = "FishingBoat";
				break;
			}
			else
			{
				dialog.text = "¿Hay algo más que te gustaría discutir?";
				link.l1 = "Quería " + GetSexPhrase("preguntarte", "preguntarte") + " por las últimas noticias del archipiélago.";
				link.l1.go = "rumours_capitan";
				if (CheckAttribute(pchar, "GenQuest.FishingBoatDialogEnb"))
				{
					link.l2 = "Muéstrame de nuevo, por favor, qué tipo de baratijas tienes a la venta. ";
					link.l2.go = "Торговля";
					if (pchar.GenQuest.FishingBoatDialogEnb != "no special goods")
					{
						link.l3 = "Hmm, quizás deberías buscar un poco más en la bodega, ¿tal vez encuentres algo para vender?";
						link.l3.go = "Особые товары";
					}
				}
				link.l4 = "¡Nada especial, solo vine a saludarte!";
				link.l4.go = "exit";
				break;
			}
		}
		// <-- рыбацкое судно
		if (!CheckAttribute(NPChar, "MainCaptanId") || NPChar.MainCaptanId == pchar.GenQuest.CaptainId)
		{
			Dialog.text = "Te estoy escuchando muy atentamente, " + GetAddress_Form(NPChar) + ".";
			link.l1 = "Quiero saber las últimas noticias del archipiélago.";
			// homo 25/06/06
			link.l1.go = "rumours_capitan";
			// belamour legendary edition
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
			if (CheckAttribute(NPChar, "EncGroupName") && !bOk) // только для фантомов грабеж
			{
				link.l2 = RandPhraseSimple("¿Tienes alguna idea de quién soy? Creo que queda perfectamente claro que mis armas pueden convertir tu vieja bañera un colador. Resolvamos esto de manera pacífica. El rescate me parece una buena decisión.", "Solo nosotros... y el mar... ¿Qué te parece si aplacas a mis hombres... por tu propia seguridad?");
				link.l2.go = "Talk_board";
			}
			if (CheckAttribute(NPChar, "Ship.Mode") && NPChar.Ship.Mode == "Trade")
			{
				link.l3 = "¿De dónde vienes?";
				link.l3.go = "price_1";
				link.l4 = "¿Quieres comerciar?";
				link.l4.go = "Trade_1";
			}
			//--> квест мэра, поиски пирата
			if (CheckAttribute(pchar, "GenQuest.DestroyPirate"))
			{
				link.l6 = "Estoy buscando un barco pirata que actúa en estas aguas. ¿Has visto algo sospechoso?";
				link.l6.go = "MQ_step_1";
			}
			//<-- квест мэра, поиски пирата
			link.l5 = "¿Quieres relajarte?";
			link.l5.go = "Play_Game";
			link.l9 = "Supongo que debería irme.";
			link.l9.go = "exit";
		}
		else
		{
			Dialog.text = "No estoy autorizado para tratar contigo. Habla con el comandante de nuestra escuadra. Su nombre es " + GetFullName(characterFromID(NPChar.MainCaptanId)) + ", puedes encontrarlo en el " + XI_ConvertString(RealShips[sti(characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Type)].BaseName) + " '" + characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Name + "'.";
			link.l1 = "Gracias. Haré como dices.";
			link.l1.go = "exit";
			Diag.TempNode = "Go_away_Good";
		}
		break;
	case "Trade_1":
		dialog.text = "¿Por qué no?";
		link.l1 = "Vamos a ver las mercancías.";
		link.l1.go = "Trade_2";
		link.l2 = "He cambiado de opinión.";
		link.l2.go = "exit";
		break;

	case "Trade_2":
        Partition_GetCargoCostCoeff("after");
		FillShipStore(NPChar);
		pchar.shiptrade.character = NPChar.id;
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		DeleteAttribute(pchar, "PriceList.StoreManIdx"); // не вести лог по кораблям
		LaunchStore(SHIP_STORE);
		break;

	case "Play_Game":
		dialog.text = "¿Qué estás sugiriendo?";
		link.l1 = "¿Quieres jugar una partida de cartas por algo de dinero serio?";
		link.l1.go = "Card_Game";
		link.l2 = "¿Qué tal si tiramos unos dados en el póker-joker?";
		link.l2.go = "Dice_Game";
		link.l10 = "Lo siento, pero tengo algunos asuntos que atender.";
		link.l10.go = "exit";
		break;
	// карты -->
	case "Card_Game":
		if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
		{
			SetNPCQuestDate(npchar, "Card_date_Yet");
			dialog.text = "¡No voy a apostar con truhanes!";
			link.l1 = "Como desees.";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "¿Por qué no? Ciertamente no me importaría un descanso...";
			link.l1 = "Excelente.";
			link.l1.go = "Cards_begin";
			link.l2 = "¿Cuáles son las reglas?";
			link.l2.go = "Cards_Rule";
		}
		break;

	case "Cards_Rule":
		dialog.text = CARDS_RULE;
		link.l1 = "¡Bueno, ¡comencemos entonces!";
		link.l1.go = "Cards_begin";
		link.l3 = "No, no es para mí...";
		link.l3.go = "exit";
		break;

	case "Cards_begin":
		Dialog.text = "Vamos a acordar la apuesta, primero.";
		link.l1 = "Juguemos por 100 pesos.";
		link.l1.go = "Cards_Node_100";
		link.l2 = "Juguemos por 500 pesos.";
		link.l2.go = "Cards_Node_500";
		link.l3 = "Supongo que debería irme.";
		link.l3.go = "exit";
		break;

	case "Cards_Node_100":
		if (sti(pchar.Money) < 300)
		{
			dialog.text = "¿Estás bromeando o qué? ¡No tienes dinero!";
			link.l1 = "Sucede.";
			link.l1.go = "exit";
			break;
		}
		if (sti(npchar.Money) < 300)
		{
			dialog.text = "Bueno, eso es suficiente, o no tendré suficiente dinero para mantener el barco...";
			link.l1 = "Lástima.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "Bien, juguemos por 100 monedas.";
		link.l1 = "¡Comencemos!";
		link.l1.go = "Cards_begin_go";
		pchar.GenQuest.Cards.npcharIdx = npchar.index;
		pchar.GenQuest.Cards.iRate = 100;
		pchar.GenQuest.Cards.SitType = false;
		break;

	case "Cards_Node_500":
		if (sti(pchar.Money) < 1500)
		{
			dialog.text = "¿Estás bromeando o qué? ¡No tienes 1500 pesos!";
			link.l1 = "¡Los encontraré!";
			link.l1.go = "exit";
			break;
		}
		if (sti(npchar.Money) < 1500)
		{
			dialog.text = "No, estas apuestas sin duda me harán perder al final.";
			link.l1 = "Como desees.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "Bien, juguemos por 500 monedas.";
		link.l1 = "¡Empecemos!";
		link.l1.go = "Cards_begin_go";
		pchar.GenQuest.Cards.npcharIdx = npchar.index;
		pchar.GenQuest.Cards.iRate = 500;
		pchar.GenQuest.Cards.SitType = false;
		break;

	case "Cards_begin_go":
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		LaunchCardsGame();
		break;
	// карты <--
	//  Dice -->
	case "Dice_Game":
		if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
		{
			SetNPCQuestDate(npchar, "Dice_date_Yet");
			dialog.text = "¡No voy a apostar con truhanes!";
			link.l1 = "Como deseas.";
			link.l1.go = "exit";
		}
		else
		{
			if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
			{
				dialog.text = "¡Por qué no! Relajarse siempre es bueno para la salud... pero no siempre para la bolsa...";
				link.l1 = "Excelente.";
				link.l1.go = "Dice_begin";
				link.l2 = "¿Cuáles son las reglas de nuestro juego?";
				link.l2.go = "Dice_Rule";
			}
			else
			{
				dialog.text = "No, ya he terminado por hoy. Tengo cosas que hacer.";
				link.l1 = "Como deseas.";
				link.l1.go = "exit";
			}
		}
		break;

	case "Dice_Rule":
		dialog.text = DICE_RULE;
		link.l1 = "¡Bueno, comencemos entonces!";
		link.l1.go = "Dice_begin";
		link.l3 = "No, no es para mí...";
		link.l3.go = "exit";
		break;

	case "Dice_begin":
		Dialog.text = "Aceptemos la apuesta, primero.";
		link.l1 = "Juguemos por 50 pesos.";
		link.l1.go = "Dice_Node_100";
		link.l2 = "Juguemos por 200 pesos.";
		link.l2.go = "Dice_Node_500";
		link.l3 = "Supongo que debería irme.";
		link.l3.go = "exit";
		break;

	case "Dice_Node_100":
		// belamour legendary edition
		bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
		bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
		bOk = bOk1 || bOk2;
		if (!CheckDiceGameSmallRate() && !bOk)
		{
			dialog.text = "Eres bien conocido como" + GetSexPhrase(" un tramposo", " una tramposa") + ". Nunca tiraré los dados contigo.";
			link.l1 = "¡Todo son mentiras! Bueno, que así sea.";
			link.l1.go = "exit";
			break;
		}

		if (sti(pchar.Money) < 300)
		{
			dialog.text = "¿Estás bromeando o qué? ¡No tienes dinero!";
			link.l1 = "Sucede.";
			link.l1.go = "exit";
			break;
		}
		if (sti(npchar.Money) < 300)
		{
			dialog.text = "¡Eso es suficiente! He terminado con el juego antes de que me etiqueten como un peculador y me obliguen a abandonar el barco.";
			link.l1 = "Lástima.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "Bien, juguemos por 50 monedas.";
		link.l1 = "¡Empecemos!";
		link.l1.go = "Dice_begin_go";
		pchar.GenQuest.Dice.npcharIdx = npchar.index;
		pchar.GenQuest.Dice.iRate = 50;
		pchar.GenQuest.Dice.SitType = false;
		break;

	case "Dice_Node_500":
		// belamour legendary edition
		bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
		bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
		bOk = bOk1 || bOk2;
		if (!CheckDiceGameSmallRate() && !bOk)
		{
			dialog.text = "Eres bien conocido como" + GetSexPhrase(" un tramposo", " una tramposa") + ". Nunca tiraré los dados contigo.";
			link.l1 = "¡Todo son mentiras! Bueno, que así sea.";
			link.l1.go = "exit";
			break;
		}
		if (!CheckDiceGameBigRate())
		{
			dialog.text = "Escuché que eres un jugador muy bueno. No jugaré a altas apuestas contigo.";
			link.l1 = "¿Deberíamos reducir la apuesta, tal vez?";
			link.l1.go = "Dice_Node_100";
			link.l2 = "Lo siento, pero tengo que irme.";
			link.l2.go = "exit";
			break;
		}

		if (sti(pchar.Money) < 1500)
		{
			dialog.text = "¿Estás bromeando o qué? ¡No tienes 1500 pesos!";
			link.l1 = "¡Los encontraré!";
			link.l1.go = "exit";
			break;
		}
		if (sti(npchar.Money) < 1500)
		{
			dialog.text = "No, estas apuestas seguramente me acabarán al final.";
			link.l1 = "Como desees.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "Bien, juguemos por 200 monedas.";
		link.l1 = "¡Empecemos!";
		link.l1.go = "Dice_begin_go";
		pchar.GenQuest.Dice.npcharIdx = npchar.index;
		pchar.GenQuest.Dice.iRate = 200;
		pchar.GenQuest.Dice.SitType = false;
		break;

	case "Dice_begin_go":
		SetNPCQuestDate(npchar, "Dice_date_begin");
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		LaunchDiceGame();
		break;
	// Dice <--
	case "price_1":
		if (CheckNPCQuestDate(npchar, "trade_date"))
		{
			SetNPCQuestDate(npchar, "trade_date");
			iMoney = findPriceStoreMan(NPChar);
			if (iMoney == -1)
			{
				Dialog.Text = "¿Por qué quieres saberlo? Esta es mi privacidad.";
				Link.l1 = "Como desees.";
				Link.l1.go = "exit";
			}
			else
			{
				sld = &Characters[iMoney];
				pchar.PriceList.ShipStoreIdx = iMoney;

				Dialog.Text = "Vengo de la ciudad de " + GetCityName(sld.City) + ".";
				Link.l1 = "¿Cuáles son los precios de los productos en la tienda?";
				Link.l1.go = "price_2";
				Link.l9 = "Debería irme.";
				Link.l9.go = "exit";
			}
		}
		else
		{
			Dialog.Text = "Ya te he contado todo. No me molestes por nada.";
			Link.l1 = "Sí, tienes razón. Adiós.";
			Link.l1.go = "exit";
		}
		break;

	case "price_2":
		sld = &Characters[sti(pchar.PriceList.ShipStoreIdx)];
		SetPriceListByStoreMan(&Colonies[FindColony(sld.City)]);
		Dialog.Text = "Aquí tienes... (has recibido la lista de precios)";
		Link.l1 = "¡Muchas gracias!";
		Link.l1.go = "exit";
		PlaySound("interface\important_item.wav");
		break;

	case "Talk_board":
		if ((Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName)) > GetCompanionQuantity(PChar) && rand(11) > GetCharacterSkillToOld(PChar, SKILL_FORTUNE))
		{
			Dialog.text = "¡Ja-ja-ja! Buen chiste, tengo más barcos. Regresa a tu barco y ahógate con él.";
			link.l1 = "Más no significa más fuerte, compañero.";
			link.l1.go = "Boarding";
		}
		else
		{
			if (rand(21) > (GetSummonSkillFromNameToOld(PChar, SKILL_GRAPPLING) + GetSummonSkillFromNameToOld(PChar, SKILL_LEADERSHIP)))
			{
				Dialog.text = "Capitán, no deberías haber hecho tus sucios negocios a bordo de mi barco. Pero mostraré misericordia y te permitiré regresar a tu barco para hundirte con él.";
				link.l1 = "¡Veremos, quién se convertirá en comida de tiburón hoy!";
				link.l1.go = "Boarding";
			}
			else
			{
				Pchar.GenQuest.MoneyForCaptureShip = makeint(100 + (Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName)) * (8 - sti(RealShips[sti(NPChar.Ship.Type)].Class)) * (1 + rand(10)) * 500);
				if(HasShipTrait(pchar, "trait14")) Pchar.GenQuest.MoneyForCaptureShip = makeint(sti(Pchar.GenQuest.MoneyForCaptureShip) * 1.35);
				Dialog.text = RandSwear() + "Sí, he oído mucho sobre tus atrocidades. Que así sea, pero recuerda " + XI_ConvertString(NationShortName(sti(NPChar.nation)) + "hunter") + "¡no dejaré que quede impune!";
				link.l1 = "Excelente. Una suma de " + Pchar.GenQuest.MoneyForCaptureShip + " pesos me vendrán bien, " + GetAddress_FormToNPC(NPChar) + ".";
				link.l1.go = "Capture";
				link.l2 = "Oh, no importa. Simplemente estaba bromeando" + GetSexPhrase("", "") + "¡!";
				link.l2.go = "exit";
			}
		}
		// тут нужен учёт запрета повторного наезда
		Diag.TempNode = "Go_away";
		sld = characterFromId(pchar.GenQuest.CaptainId);
		sld.talk_date_Go_away = lastspeakdate(); // boal злопамятность :)
		break;

	case "surrender1":
		Diag.TempNode = "surrender_goaway";
		Dialog.Text = "¡Aquí tienes y ahora lárgate!";
		Link.l1 = "¡Bien! Y también te mantienes saludable, amigo!";
		Link.l1.go = "exit";
		sld = characterFromId(pchar.GenQuest.CaptainId);
		sld.talk_date_Go_away = lastspeakdate();
		AddMoneyToCharacter(pchar, sti(Pchar.GenQuest.MoneyForCaptureShip));
		ChangeCharacterComplexReputation(pchar, "nobility", -2);
		ChangeCharacterComplexReputation(pchar, "authority", 1.0);
		AddCharacterExpToSkill(pchar, "Leadership", 20);
		ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", GetIntByCondition(HasShipTrait(pchar, "trait23"), 7 + rand(10), 3 + rand(5)));
		break;

	case "surrender_goaway":
		Dialog.Text = "¿Qué más quieres de mí?";
		Link.l1 = "Nada.";
		Link.l1.go = "exit";
		Diag.TempNode = "surrender_goaway";
		break;

	case "surrender2":
		dialog.text = "Parece que no tengo otra opción más que someterme a ti.";
		link.l1 = "¡Avanza, ahora!";
		link.l1.go = "surrender3";
		break;

	case "surrender3":
		Diag.TempNode = "surrender_goaway";
		sld = characterFromId(pchar.GenQuest.CaptainId);
		sld.talk_date_Go_away = lastspeakdate();
		DialogExit();
		LaunchTransferMain(pchar, sld, "Transfer");
		break;

	case "rumours":
		Dialog.Text = SelectRumour(); // to_do
		Link.l1 = RandPhraseSimple(RandSwear() + "Esto es muy interesante. ¿Otra pregunta?", "Solo otro asunto.");
		Link.l1.go = "quests";
		Link.l2 = RandPhraseSimple("Gracias, y debería irme.", "Todo lo mejor.");
		Link.l2.go = "exit";
		Diag.TempNode = "quests";
		break;

	case "Go_away":
		Dialog.Text = "¡Sal de mi barco!";
		Link.l1 = "Ya me estoy yendo.";
		Link.l1.go = "exit";
		Diag.TempNode = "Go_away";
		break;

	case "Go_away_Good":
		Dialog.Text = "Nuestra conversación ha terminado. No voy a contarte nada nuevo " + GetAddress_Form(NPChar) + ".";
		Link.l1 = "Está bien. ¡Nos vemos en el mar!";
		Link.l1.go = "exit";
		Diag.TempNode = "Go_away_Good";
		break;

	case "Capture":
		Diag.TempNode = "Go_away";
		Dialog.Text = "¡Aquí tienes y ahora lárgate!";
		Link.l1 = "¡Bueno!";
		Link.l1.go = "exit";
		AddMoneyToCharacter(pchar, sti(Pchar.GenQuest.MoneyForCaptureShip));
		ChangeCharacterComplexReputation(pchar, "nobility", -5);
		AddCharacterExpToSkill(pchar, "Leadership", 20);
		ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", GetIntByCondition(HasShipTrait(pchar, "trait23"), 7 + rand(10), 3 + rand(5)));
		break;

	case "Boarding":
		if (CheckAttribute(NPChar, "MainCaptanId"))
		{
			PChar.StartBattleAfterDeck = true;
			PChar.StartBattleMainCaptanId = NPChar.MainCaptanId;
			PChar.StartBattleEncGroupName = NPChar.EncGroupName;
		}
		DialogExit();
		Diag.CurrentNode = Diag.TempNode;
		break;

	case "QuestAboardCabinDialog": // тестовый диалог, в игре не работает, для метода SetQuestAboardCabinDialog
		Diag.TempNode = "QuestAboardCabinDialog";
		Dialog.Text = "Espera, podrías matarme de esta manera. ¿Qué quieres de mí?";
		Link.l1 = "¡Para matarte!";
		Link.l1.go = "QuestAboardCabinDialog_1";
		Link.l2 = "¡Ríndete!";
		Link.l2.go = "QuestAboardCabinDialog_2";
		Link.l3 = "Danos el mapa, Billy (c)";	 // предмет, далее не ясно или  QuestAboardCabinDialog_1 или QuestAboardCabinDialog_2
		Link.l3.go = "QuestAboardCabinDialog_3"; // можно закодить покидание корабля, но экипаж уже вырезан и тп...
		break;

	case "QuestAboardCabinDialog_1":
		Dialog.Text = "¡Bueno, veremos, bastardo!";
		Link.l1 = "¿Y qué tengo que ver?";
		Link.l1.go = "exit";
		// тут можно восстановить НР противника (NPChar) или добавить парочку гардов против ГГ
		LAi_SetCurHPMax(NPChar);
		AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattle"); // тут ругань обратно
		break;

	case "QuestAboardCabinDialog_2":
		Dialog.Text = "¡Bien, ganaste!";
		Link.l1 = "¡Decisión inteligente!";
		Link.l1.go = "exit";
		AddDialogExitQuestFunction("QuestAboardCabinDialogSurrender");
		break;

	case "QuestAboardCabinDialog_3":
		Dialog.Text = "¡Espero que te atragantes con eso!";
		Link.l1 = "Muy bien, ponte las esposas y cierra la boca, prisionero.";
		if (rand(1) == 1) // пример!!!
		{
			Link.l1.go = "QuestAboardCabinDialog_2";
		}
		else
		{
			Link.l1.go = "QuestAboardCabinDialog_3_1";
		}
		TakeNItems(NPChar, "Chest", -1);
		TakeNItems(pchar, "Chest", 1);
		break;

	case "QuestAboardCabinDialog_3_1":
		Dialog.Text = "" + GetSexPhrase("Llegó aquí", "Vino aquí") + ", hizo un desastre" + GetSexPhrase("", "") + ",y se llevaron todo" + GetSexPhrase("", "") + ", ¿ahora quieres hacerme un esclavo? ¡Jamás!";
		Link.l1 = "Entonces prepárate para morir.";
		Link.l1.go = "QuestAboardCabinDialog_1";
		break;
	// eddy. квест мэра, поиски пирата
	case "MQ_step_1":
		Dialog.Text = "No, no he visto ningún barco sospechoso que pareciera de piratas.";
		Link.l1 = "Lo veo.";
		Link.l1.go = "exit";
		break;

	// homo Наводка на купца
	case "MerchantTrap_Abordage":

		Dialog.Text = "En el nombre de " + NationKingsName(NPChar) + " ríndete, " + GetSexPhrase("pirata asqueroso", "¡perra asquerosa!") + "¡Entonces tu vida será perdonada hasta un tribunal justo, donde serás juzgado por todo " + NationNameSK(sti(NPChar.nation)) + "barcos que has saqueado" + GetSexPhrase("", "") + ".";
		Link.l1 = "¡Al diablo contigo! ¡Deberías rendirte!";
		Link.l1.go = "exit";
		LAi_SetCurHPMax(NPChar);
		AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattleNoParam"); // тут ругань обратно
		break;

	case "Siegehelp":
		ref rchar = Group_GetGroupCommander(sGroup);
		if (NPChar.id == rchar.id)
		{
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Su Excelencia, Gobernador General! Le escucho atentamente, pero le ruego que sea breve: estamos luchando con " + fort + ", y necesito dirigir el curso de la batalla.";
			}
			else
			{
				if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
				{
					dialog.text = "¡Vicealmirante! Te escucho atentamente, pero tengo poco tiempo: estamos luchando con " + fort + ", y necesito dirigir el curso de la batalla.";
				}
				else
				{
					dialog.text = "Te estoy escuchando, pero vamos a exponer rápidamente el propósito de tu visita, estamos luchando con " + fort + ", y necesito dirigir el curso de la batalla.";
				}
			}
			link.l1 = "Por eso estoy aquí, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "attack_fort";

			link.l2 = "En ese caso no tomaré más de tu tiempo. Adiós, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l2.go = "exit";
		}
		else
		{
			Dialog.text = "No estoy autorizado para tratar contigo. Habla con el comandante de nuestro escuadrón. Su nombre es " + GetFullName(rchar) + ", puedes encontrarlo en " + XI_ConvertString(RealShips[sti(rchar.Ship.Type)].BaseName) + "''" + rchar.Ship.Name + "''.";
			link.l1 = "Gracias. Haré como dices.";
			link.l1.go = "exit";
		}
		Diag.TempNode = "Siegehelp";

		break;

	case "attack_fort":
		dialog.text = "¿Y qué quieres decir?";
		link.l1 = "Puedo ayudarte a aplastar el fuerte de la colonia de " + GetConvertStr(aData.Colony + " Pueblo", "LocLables.txt") + " y captura la ciudad, y un botín, resultando en el caso de nuestro éxito, nos dividimos entre nosotros.";
		link.l1.go = "Siegehelp_1";
		link.l2 = "En realidad, mis asuntos apenas valen tu tiempo. Adiós, " + GetAddress_FormToNPC(NPChar) + ".";
		link.l2.go = "exit";
		Diag.TempNode = "Siegehelp_0";
		break;

	case "Siegehelp_0":
		Dialog.text = "¿Tú otra vez? Creí que ya habíamos discutido todo.";
		link.l1 = "Tienes razón. Supongo que lo he olvidado" + GetSexPhrase("", "") + ".";
		link.l1.go = "exit";
		NPChar.DeckDialogNode = "Siegehelp_0";
		Diag.TempNode = "Siegehelp_0";

		break;

	case "Siegehelp_1":
		SiegeResult("");
		// belamour legendary edition
		bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
		bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
		bOk = bOk1 || bOk2;
		if (sti(aData.win) == 0 || bOk)
		{
			dialog.text = "¿Y qué parte del botín esperas recibir?";
			link.l1 = "La mitad.";
			link.l1.go = "Big_part";
			link.l2 = "Un tercio.";
			link.l2.go = "Middle_part";
			link.l3 = "Un cuarto.";
			link.l3.go = "Small_part";
		}
		else
		{
			dialog.text = "¡No necesito tus servicios, capitán! Tomaré esta colonia por mi cuenta y no necesito ayuda para hacerlo.";
			link.l1 = "¿Por qué estás tan seguro, " + GetAddress_FormToNPC(NPChar) + "?, cualquiera puede tener un golpe de mala suerte.";
			link.l1.go = "attack_fort_03";
			link.l2 = "En ese caso, no tomaré más de tu tiempo, " + GetAddress_FormToNPC(NPChar) + ". ¡Adiós!";
			link.l2.go = "exit";
		}
		Diag.TempNode = "Siegehelp_0";

		break;

	case "attack_fort_03":
		if ((sti(aData.iSquadronPower) * SquadronDamage - (ifortPower)*fortDamage) < 4000)
		{
			dialog.text = "Por otro lado, mis barcos están bastante dañados en esta batalla, y ciertamente no vendrían mal refuerzos. Si estás de acuerdo en " + GetPart(4) + ", entonces, supongo, podríamos llegar a un acuerdo.";
			link.l1 = "Eso me conviene, " + GetAddress_FormToNPC(NPChar) + ". Intentaré asaltar el fuerte, y tú nos apoyarás con el fuego de los cañones de tu barco.";
			link.l1.go = "attack_fort_04";
			aData.PartAttaksFort = 4;
			link.l2 = "No soy tan barato, " + GetAddress_FormToNPC(NPChar) + ". Lo siento por la distracción" + GetSexPhrase("", "") + " te apartas de asuntos urgentes. ¡Adiós!";
			link.l2.go = "exit";
		}
		else
		{
			dialog.text = "Hay suficientes barcos en mi escuadra para reducir este fuerte a polvo, es solo cuestión de tiempo. Y ahora, ¿podrías por favor abandonar mi barco? ¡La victoria me espera!";
			link.l1 = "Bueno, en ese caso, " + GetAddress_FormToNPC(NPChar) + ", permíteme tomar mi licencia. ¡Adiós!";
			link.l1.go = "exit";
		}
		Diag.TempNode = "Siegehelp_0";
		break;
	case "Big_part":
		if ((sti(aData.iSquadronPower) * SquadronDamage - (ifortPower)*fortDamage) <= -1500)
		{
			dialog.text = "Los cañones del fuerte han dañado gravemente mis barcos, y seguramente seremos el bando perdedor en la próxima batalla. Acepto tu ayuda y estoy de acuerdo con tus términos.";
			link.l1 = "Excelente, " + GetAddress_FormToNPC(NPChar) + ", en ese caso intentaremos asaltar el fuerte, y tú nos apoyarás con el fuego de los cañones de tu barco.";
			link.l1.go = "attack_fort_04";
			aData.PartAttaksFort = 2;
		}
		else
		{
			// belamour legendary edition
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
			bOk = bOk1 || bOk2;
			if (bOk)
			{
				dialog.text = "Su Excelencia, todavía necesito informar sobre el progreso de la operación ... Al menos " + GetPart(4) + ".";
			}
			else
			{
				dialog.text = "¿No es demasiado, capitán? Tienes " + GetNumShips(GetCompanionQuantity(PChar)) + ", y mi escuadrón tiene " + GetNumShips(Group_GetCharactersNum(sGroup)) + ". Puedo ofrecerte " + GetPart(4) + ". Y considéralo justo.";
			}
			aData.PartAttaksFort = 4;
			link.l1 = "Estoy de acuerdo" + GetSexPhrase("", "") + ", " + GetAddress_FormToNPC(NPChar) + ", en ese caso asaltaré el fuerte, y tú nos apoyarás con el fuego de los cañones de tu barco.";
			link.l1.go = "attack_fort_04";
			link.l2 = "Lamentablemente, no lo creo, " + GetAddress_FormToNPC(NPChar) + ". No hay más de qué hablar. Adiós.";
			link.l2.go = "exit";
		}
		Diag.TempNode = "Siegehelp_0";
		break;

	case "attack_fort_04":
		dialog.text = "Tan pronto como el fuerte sea capturado, comenzaremos a desplegar equipos de desembarco en la costa, y luego continuaremos luchando en la ciudad misma, donde espero encontrarme contigo.";
		link.l1 = "Que así sea. Hasta pronto, " + GetAddress_FormToNPC(NPChar) + ".";
		link.l1.go = "exit";
		Diag.TempNode = "Siegehelp_0";
		PChar.quest.Union_with_Escadra = "Yes";
		break;

	case "Middle_part":
		if ((sti(aData.iSquadronPower) * SquadronDamage - (ifortPower)*fortDamage) <= -600)
		{
			dialog.text = "Creo que aceptaré tus condiciones. La operación conjunta aumentará mis posibilidades de ganar esta lucha. Si todo va según lo planeado, recibirás tu parte del botín.";
			link.l1 = "Es estupendo que hayamos llegado a un acuerdo, " + GetAddress_FormToNPC(NPChar) + ". Ordenaré a mis hombres que asalten el fuerte inmediatamente.";
			link.l1.go = "attack_fort_04";
			aData.PartAttaksFort = 3;
		}
		else
		{
			// belamour legendary edition
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
			bOk = bOk1 || bOk2;
			if (bOk)
			{
				dialog.text = "Su Excelencia, todavía necesito informar sobre el progreso de la operación ... Al menos " + GetPart(4) + ".";
			}
			else
			{
				dialog.text = "¿No es demasiado, capitán? Tienes " + GetNumShips(GetCompanionQuantity(PChar)) + ", y mi escuadrón tiene " + GetNumShips(Group_GetCharactersNum(sGroup)) + ". Puedo ofrecerte " + GetPart(4) + ". Y considéralo justo.";
			}
			link.l1 = "Yo " + GetSexPhrase("de acuerdo", "de acuerdo") + ", " + GetAddress_FormToNPC(NPChar) + ", en ese caso asaltaré el fuerte, y tú nos apoyarás con el fuego de los cañones de tu barco.";
			link.l1.go = "attack_fort_04";
			aData.PartAttaksFort = 4;
			link.l2 = "Lamentablemente, no lo creo, " + GetAddress_FormToNPC(NPChar) + ". No hay nada más que discutir. Adiós.";
			link.l2.go = "exit";
		}
		Diag.TempNode = "Siegehelp_0";
		break;

	case "Small_part":
		dialog.text = "Mis barcos están cansados, y cualquier fuerza fresca es bienvenida en esta situación. Acepto tu ayuda y estoy de acuerdo con tus términos.";
		link.l1 = "Estoy contento" + GetSexPhrase("", "") + ", " + GetAddress_FormToNPC(NPChar) + ".. Ordenaré inmediatamente a mis hombres que comiencen el asalto al fuerte.";
		link.l1.go = "attack_fort_04";
		aData.PartAttaksFort = 4;
		Diag.TempNode = "Siegehelp_0";
		break;

	case "Talk_Capture_City":
		AfterTownBattle(); // все, все свободны
		LAi_LoginInCaptureTown(NPChar, false);
		aData.win = 1;
		EndOfTheSiege("End");
		NPChar.location = "";
		int ilt = makeint(sti(aData.loot) / sti(aData.PartAttaksFort));
		dialog.text = "¡Hola, capitán! Ciertamente fue una batalla dura, pero logramos romper la furiosa resistencia de los defensores del pueblo. Hemos saqueado " + sti(aData.loot) + " pesos. Según nuestro trato, tu parte es " + ilt + ". Por favor, acepta este dinero; sin duda te mereces hasta la última moneda. Y ahora, por favor, discúlpeme, pero debo volver a mis asuntos.";
		link.l1 = "En ese caso, te dejaré, " + GetAddress_FormToNPC(NPChar) + ". ¡Adiós!";
		link.l1.go = "exit";
		// AddDialogExitQuest("End_Siege_and_Attaks_City");

		Diag.TempNode = "no_return_02";
		AddMoneyToCharacter(PChar, ilt);
		ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
		ChangeCharacterComplexReputation(PChar, "nobility", 10);
		AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 80);
		AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 100);
		AddCharacterExpToSkill(GetMainCharacter(), "Defence", 100);
		AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 100);
		AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 100);
		AddCharacterExpToSkill(GetMainCharacter(), "Fortune", 80);
		aData.loot = sti(aData.loot) - ilt;
		if (CheckAttribute(PChar, "quest.LeaveTown"))
			Pchar.quest.LeaveTown.over = "yes";
		//--> слухи
		SiegeRumour("Me han dicho que habías ayudado a nuestro escuadrón en el asalto al " + NationNameSK(sti(aData.conation)) + " colonia, " + GetConvertStr(aData.Colony + " Town", "LocLables.txt") + "! Le estamos muy agradecidos, " + GetAddress_Form(NPChar) + ".", "", sti(aData.nation), -1, 30, 3);
		//<-- слухи
		break;

	case "no_return_02":
		dialog.text = "¡Ahoy, capitán! ¿Tienes algún asunto conmigo?";
		link.l1 = "No, " + GetAddress_FormToNPC(NPChar) + ". ¡Adiós!";
		link.l1.go = "exit";
		Diag.TempNode = "no_return_02";
		break;

	case "GoldSquadron":
		ref rch = Group_GetGroupCommander("Sea_Head_of_Gold_Squadron");
		if (NPChar.id == rch.id)
		{
			dialog.text = "Te escucho, pero por favor sé rápido sobre el objetivo de tu visita, no tengo mucho tiempo. Tengo una misión importante y secreta, y también se me ha ordenado hundir todos los barcos sospechosos en alta mar, que podrían representar algún peligro para nuestro convoy.";
			link.l1 = "En ese caso, no tomaré más de tu tiempo. Buena suerte, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "exit";
		}
		else
		{
			Dialog.text = "No estoy autorizado para tratar contigo. Habla con el comandante de nuestro escuadrón. Su nombre es " + GetFullName(rch) + ", puedes encontrarlo en " + XI_ConvertString(RealShips[sti(rch.Ship.Type)].BaseName) + "''" + rch.Ship.Name + "''.";
			link.l1 = "Gracias. Haré como dices.";
			link.l1.go = "exit";
		}
		Diag.TempNode = "GoldSquadron";
		break;

	case "WM_Captain":
		dialog.text = "Encantado de conocerte, y mi nombre es " + GetFullName(npchar) + ". ¿Así que has venido a ayudarnos? En ese caso estoy especialmente contento, ya que nuestra situación actual es verdaderamente crítica, estamos solos en las costas de una isla deshabitada, el barco apenas es apto para navegar, la tripulación ha sufrido grandes pérdidas...";
		link.l1 = "Como he oído, tuviste una batalla con piratas, y luego estaba esa tormenta...";
		link.l1.go = "WM_Captain_1";
		pchar.quest.DesIsland_Over.over = "yes"; // снять прерывание
		break;

	case "WM_Captain_1":
		dialog.text = "Correcto. Mi barco fue gravemente dañado en la batalla, incluso tuvimos que enfrentarnos a un ataque de abordaje liderado por esos bastardos piratas. Más tarde, una tormenta nos atrapó... oh, no quiero ni pensar en ello. Nos arrastró hasta esta inhóspita orilla. Habíamos estado rezando todo un día a la Virgen Bendita para que nos salvara de la tormenta y mantuviera nuestras cadenas de ancla en una pieza\nY aquí estamos. Hemos estado reparando nuestro barco durante una semana, pero míralo tú mismo: sólo quedan cincuenta hombres y también nos falta madera. ¿Y de dónde se supone que la obtendremos? ¿De la jungla? Obviamente. Trabajando duro cada día y aun así sólo tenemos la quinta parte del material total necesario\nNavegar con tanto daño es como suicidarse. Ahora ves cómo nos va por aquí, capitán...";
		link.l1 = "Sí... Tu situación es envidiable. Pensemos qué podríamos emprender y cómo puedo ayudarte.";
		link.l1.go = "WM_Captain_2";
		break;

	case "WM_Captain_2":
		dialog.text = "Eh, desearía que tuviéramos suficientes tablas y tela de vela, en ese caso podríamos reparar nuestro barco en una semana\nCapitán, ya que has venido aquí a propósito, ¿quizás podrías visitar el puerto más cercano y comprar los materiales que necesitamos? Esto resolvería nuestro problema. No te preocupes por las monedas, compensaré todos los gastos.";
		link.l1 = "Por supuesto. ¿Qué exactamente necesitas entregar, y cuánto?";
		link.l1.go = "WM_Captain_3";
		break;

	case "WM_Captain_3":
		pchar.questTemp.WPU.Escort.Planks = 300 + hrand(5) * 10;
		pchar.questTemp.WPU.Escort.Sailcloth = 150 + hrand(10) * 10;
		pchar.questTemp.WPU.Escort.Linen = 70 + hrand(7) * 10;
		dialog.text = "Ya he resuelto todo esto. Considerando lo que ya tenemos, necesito " + FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Planks)) + " tablones, " + FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Sailcloth)) + " tela de vela y " + FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Linen)) + " algodón. Con estos materiales, lograríamos reparar el barco en una semana y luego podríamos zarpar.";
		link.l1 = "Bien. Te traeré todos los materiales que necesitas. Espera por mí, no volveré más tarde de diez días.";
		link.l1.go = "WM_Captain_4";
		break;

	case "WM_Captain_4":
		dialog.text = "¡Muchas gracias, capitán! Ahora eso es un alivio para mi mente. ¡Estaremos esperando y rezando por tu exitoso regreso!";
		link.l1 = "No te preocupes. Pronto tendrás todo lo que necesitas para la reparación.";
		link.l1.go = "exit";
		AddQuestRecord("Escort", "27");
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		AddQuestUserData("Escort", "sIsland", XI_ConvertString("Colony" + pchar.questTemp.WPU.Current.TargetIslandID));
		AddQuestUserData("Escort", "sQty1", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Planks)));
		AddQuestUserData("Escort", "sQty2", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Sailcloth)));
		AddQuestUserData("Escort", "sQty3", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Linen)));
		Diag.TempNode = "WM_Captain_again";
		SetFunctionTimerCondition("WM_Captain_Over", 0, 0, 11, false);
		pchar.questTemp.WPU.Escort = "wait";
		break;

	case "WM_Captain_again":
		dialog.text = "¡Estaremos esperando ansiosos por su regreso, capitán!";
		link.l1 = "¡Levad anclas!";
		link.l1.go = "exit";
		Diag.TempNode = "WM_Captain_again";
		break;

	case "WM_Captain_5":
		dialog.text = "¡Excelente! ¡Ahora podemos comenzar a reparar el barco!";
		link.l1 = "Mis hombres te echarán una mano, de esta manera será más rápido. Además, debo acompañarte a la colonia de " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Escort.StartCity) + ", así que cuanto antes terminemos con las reparaciones, mejor para mí.";
		link.l1.go = "WM_Captain_6";
		break;

	case "WM_Captain_6":
		pchar.questTemp.WPU.Current.TargetIslandID.Shore = SelectQuestShoreLocationFromSea(pchar.questTemp.WPU.Current.TargetIslandID);
		dialog.text = "Realmente, no tengo idea de cómo agradecerte adecuadamente, capitán... Por favor, ordena descargar los materiales en una cala llamada " + XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore) + ", allí tenemos todo listo para reparar.";
		link.l1 = "Bien. Nos encontraremos en la orilla.";
		link.l1.go = "exit";
		AddQuestRecord("Escort", "29");
		AddQuestUserData("Escort", "sShore", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore + "Gen"));
		pchar.quest.DisasterShip_WMC.win_condition.l1 = "location";
		pchar.quest.DisasterShip_WMC.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID.Shore;
		pchar.quest.DisasterShip_WMC.function = "RepairShip_Prepare";
		Diag.TempNode = "WM_Captain_repeat";
		break;

	case "WM_Captain_repeat":
		dialog.text = "¿Cuándo comenzaremos las reparaciones, capitán? Te estaré esperando en la orilla.";
		link.l1 = "Sí, por supuesto. Me voy ahora.";
		link.l1.go = "exit";
		Diag.TempNode = "WM_Captain_repeat";
		break;

	case "Repair_start":
		dialog.text = "Bueno, todo parece estar listo para la reparación. Creo que deberíamos terminar en unos cinco días.";
		link.l1 = "¡Muy bien! De todas formas iba a explorar esta isla, así que haré buen uso de este tiempo.";
		link.l1.go = "Repair_start_1";
		break;

	case "Repair_start_1":
		DialogExit();
		pchar.quest.WM_Captain_Over.over = "yes"; // снять прерывание
		sld = characterFromId("WMCaptain");
		LAi_SetImmortal(sld, false);
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
		RemoveCharacterGoods(pchar, GOOD_PLANKS, sti(pchar.questTemp.WPU.Escort.Planks));
		RemoveCharacterGoods(pchar, GOOD_SAILCLOTH, sti(pchar.questTemp.WPU.Escort.Sailcloth));
		RemoveCharacterGoods(pchar, GOOD_COTTON, sti(pchar.questTemp.WPU.Escort.Linen));
		DoQuestFunctionDelay("RepairShip_WithoutMasts", 5.0);
		break;

	case "Repair_end":
		dialog.text = "Bueno, eso es todo. Hemos terminado con las reparaciones y el barco está listo para zarpar. ¿Cuándo partimos, capitán?";
		link.l1 = "Si estás listo, no veo razón para quedarnos aquí. ¡Levad anclas!";
		link.l1.go = "Repair_end_1";
		break;

	case "Repair_end_1":
		DialogExit();
		sld = characterFromId("WMCaptain");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0);
		AddQuestRecord("Escort", "30");
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony" + pchar.questTemp.WPU.Escort.StartCity));
		SetFunctionTimerCondition("DisasterShipWM_Over", 0, 0, 25, false);
		log_info("Tienes 25 días para escoltar al " + pchar.questTemp.WPU.Escort.ShipBaseName + " '" + pchar.questTemp.WPU.Escort.ShipName + "' al puerto de " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Escort.StartCity + "Gen") + "");
		pchar.quest.DisasterShip_final.win_condition.l1 = "location";
		pchar.quest.DisasterShip_final.win_condition.l1.location = pchar.questTemp.WPU.Escort.StartCity + "_town";
		pchar.quest.DisasterShip_final.function = "WMShip_final";
		break;

	case "WMShip_final":
		pchar.quest.Escort_fail.over = "yes";
		pchar.quest.DisasterShipWM_Over.over = "yes";																																		  // снимаем оба прерывания
		RemoveCharacterCompanion(Pchar, characterFromID("WMCaptain"));																														  // удаляем компаньона
		pchar.questTemp.WPU.Escort.LevelUp_1Money = sti(pchar.questTemp.WPU.Escort.Planks) * 15 + sti(pchar.questTemp.WPU.Escort.Sailcloth) * 9 + sti(pchar.questTemp.WPU.Escort.Linen) * 45; // деньги за материалы
		dialog.text = "Quiero agradecerte una vez más, capitán, nos ayudaste enormemente a mí y a mi tripulación a salir de ese apuro. Como prometí, compensaré los costos de los materiales necesarios para reparar mi barco. Aquí están " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money)) + ", por favor, tómalos. Y este es mi regalo personal para ti.";
		link.l1 = "Estaba feliz de ayudarte.";
		link.l1.go = "WMShip_final_1";
		break;

	case "WMShip_final_1":
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.LevelUp_1Money));
		TakeNItems(pchar, "obereg_" + (hrand(10) + 1), 1);
		dialog.text = "Y ahora, es hora de decir adiós, capitán. No olvides visitar la autoridad portuaria, te están esperando. ¡Hasta luego!";
		link.l1 = "Que tengas un buen día, " + npchar.name + ".";
		link.l1.go = "WMShip_final_2";
		break;

	case "WMShip_final_2":
		chrDisableReloadToLocation = false;
		bDisableFastReload = false;
		DialogExit();
		sld = characterFromId("WMCaptain");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
		if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM"))
			AddQuestRecord("Escort", "31");
		if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1VSP"))
			AddQuestRecord("Escort", "37");
		if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1S"))
			AddQuestRecord("Escort", "40");
		AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money)));
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony" + pchar.questTemp.WPU.Escort.StartCity + "Gen"));
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		break;

	case "VSP_Captain":
		dialog.text = "¿Es eso así? Y yo pensaba que nos habían olvidado. Sí, mi barco obtuvo lo peor de todo. Nos dejaron luchar contra los elementos de la naturaleza después de que la tormenta obligó a los piratas a detener un ataque a nuestra caravana. Fuimos llevados a esta costa inhóspita\nPasamos unos días reparando y descansando. Estos paganos nos atacaron de nuevo, tan pronto como íbamos a zarpar\nY luego la tormenta nos golpeó de nuevo, pensaba que el Señor finalmente decidió acabar con nosotros, pero tú llegaste. ¡Gracias a la Santa María! ¡Gracias de nuevo, capitán!";
		link.l1 = "Todo ha terminado, " + GetAddress_FormToNPC(NPChar) + ". Ahora debo escoltarte a " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Escort.StartCity + "Gen") + ", para protegerlo de otros posibles problemas. ¿Estás listo para ir ahora? La tormenta ya ha comenzado a disminuir.";
		link.l1.go = "VSP_Captain_1";
		break;

	case "VSP_Captain_1":
		dialog.text = "¡Pero por supuesto! Cuanto antes dejemos este lugar, más tranquilos estarán mis hombres, ya han sufrido demasiado. ¡Zarpemos!";
		link.l1 = "Solo sigue mi barco, y calma a tu tripulación, no hay nada que temer ahora.";
		link.l1.go = "VSP_Captain_2";
		break;

	case "VSP_Captain_2":
		pchar.quest.DisasterShip_GetOut.over = "yes";
		DialogExit();
		Group_DelCharacter("WMShip", "WMCaptain"); // иначе будет клон
		sld = characterFromId("WMCaptain");
		LAi_SetImmortal(sld, false);
		SetCharacterRemovable(sld, false);
		sld.CompanionEnemyEnable = false; // всегда друзья
		SetCompanionIndex(pchar, -1, sti(sld.index));
		sld.loyality = MAX_LOYALITY;
		AddQuestRecord("Escort", "36");
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		SetFunctionTimerCondition("DisasterShipWM_Over", 0, 0, 25, false);
		log_info("Tienes 25 días para escoltar al " + pchar.questTemp.WPU.Escort.ShipBaseName + " '" + pchar.questTemp.WPU.Escort.ShipName + "' al puerto de" + XI_ConvertString("Colony" + pchar.questTemp.WPU.Escort.StartCity + "Gen") + "");
		pchar.questTemp.WPU.Escort = "win";
		pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death"; // прерывание на потопление сопровождаемого
		pchar.quest.Escort_fail.win_condition.l1.character = "WMCaptain";
		pchar.quest.Escort_fail.function = "DisasterShipWM_failed";
		pchar.quest.DisasterShip_final.win_condition.l1 = "location";
		pchar.quest.DisasterShip_final.win_condition.l1.location = pchar.questTemp.WPU.Escort.StartCity + "_town";
		pchar.quest.DisasterShip_final.function = "WMShip_final";
		Diag.currentnode = "VSP_Captain_again";
		Delete_EscortStorm(); // уберем шторм
		break;

	case "VSP_Captain_again":
		dialog.text = "¿Deberíamos zarpar, capitán?";
		link.l1 = "Claro. Regresaré a mi barco ahora.";
		link.l1.go = "exit";
		Diag.TempNode = "VSP_Captain_again";
		break;

	case "VSPShip_final":
		pchar.quest.Escort_fail.over = "yes";
		pchar.quest.DisasterShipWM_Over.over = "yes";				   // снимаем оба прерывания
		RemoveCharacterCompanion(Pchar, characterFromID("WMCaptain")); // удаляем компаньона
		pchar.questTemp.WPU.Escort.LevelUp_1Money = 10000 + sti(pchar.rank) * 200;
		dialog.text = "Quiero agradecerte una vez más, capitán, nos ayudaste enormemente a mí y a mi tripulación a salir de este aprieto. Aquí están" + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money)) + ". Toda la tripulación contribuyó, así que ni siquiera pienses en renunciar a ello. Y este es mi regalo personal para ti.";
		link.l1 = "¡Estaba feliz de ayudarte!";
		link.l1.go = "WMShip_final_1";
		break;

	case "SShip_final":
		pchar.questTemp.WPU.Escort.LevelUp_1Money = 5000 + sti(pchar.rank) * 100;
		RemovePassenger(Pchar, npchar); // удаляем пассажира
		dialog.text = "Quiero agradecerte de nuevo, capitán, por salvar nuestros traseros de este lío. Aquí, acepta estas monedas, " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money)) + " y aquí, toma este regalo. No es mucho, pero es todo lo que puedo hacer para agradecerte por lo que has hecho. Por favor, no rechaces la oferta\nMi antigua tripulación está asombrada por ti y tu lucha con los indios y piratas. Todos ellos desean unirse a ti. ¿Espero que no rechaces una solicitud de servicios leales de marineros que acaban de perder su barco?";
		link.l1 = "Por supuesto, no. Lo guardaré con gusto. ¡Estaba feliz de ayudarte!";
		link.l1.go = "WMShip_final_1";
		break;

	// Голландский Гамбит
	case "Stivesant_1":
		DelLandQuestMark(npchar);
		dialog.text = "Bien. Pero, señor, ¿podría explicar qué está pasando aquí? ¿Cómo es que estás al mando de 'Meifeng'? ¿Le pasó algo a Longway?";
		link.l1 = "Tengo todas las explicaciones que necesitas y también alguna que otra información importante.";
		link.l1.go = "Stivesant_2";
		break;

	case "Stivesant_2":
		dialog.text = "Entonces estoy todo oídos.";
		link.l1 = "Hubo un golpe de estado en Willemstad. Lucas Rodenburg tomó el lugar del gobernador y ha metido a Matthias Beck en prisión bajo una ridícula sospecha de que tenía conexiones con la inteligencia británica.";
		link.l1.go = "Stivesant_3";
		break;

	case "Stivesant_3":
		dialog.text = "Hmm... Mynheer, las cosas que me estás contando son realmente sorprendentes. Había recibido noticias de Willemstad no hace mucho tiempo, y no había nada de eso en ellas.";
		link.l1 = "Por favor, escúchame, señor Stuyvesant. Debes haber obtenido las noticias a través de Rodenburg, y él debe estar seguro de que no llegarás a Curazao.";
		link.l1.go = "Stivesant_4";
		break;

	case "Stivesant_4":
		dialog.text = "Señor, me gusta cada vez menos lo que dices. ¿Quién eres tú?";
		link.l1 = "Soy solo un capitán y solo un hombre no indiferente al destino de los colonos holandeses. Lucas Rodenburg ordenó a Longway destruir tu barco y matarte también. Y dado que 'Meifeng' no te habría hecho sospechar, lo habría llevado a cabo sin ningún esfuerzo.";
		link.l1.go = "Stivesant_5";
		break;

	case "Stivesant_5":
		dialog.text = "Entonces, ¿quieres decir que Lucas...?";
		link.l1 = "Decidieron quitarte del poder de la manera más fácil posible: simplemente eliminándote. Excepto por ti, no hay otra persona en la región capaz de oponer alguna resistencia significativa a la influencia de Rodenburg en el Archipiélago.";
		link.l1.go = "Stivesant_6";
		break;

	case "Stivesant_6":
		dialog.text = "¡No puedo creerlo!";
		link.l1 = "No caí en esa tontería con Beck conectado con el servicio de inteligencia inglés y emprendí mi propia investigación. Descubrí que 'Meifeng', cargado con despiadados asesinos, zarpó hacia Philipsburg. Los perseguí y les di batalla. Longway fue capturado, y él me dio toda esta información, incluyendo tu paradero.";
		link.l1.go = "Stivesant_7";
		break;

	case "Stivesant_7":
		dialog.text = "Hm... Eso parece probable. Nadie, excepto Rodenburg, sabía o podría saber sobre mi horario y ruta. ¡Maldición! ¡Es traición! ¿Dónde está Longway?!";
		link.l1 = "Lo liberé a cambio de su confesión voluntaria. Debo decir, no estaba demasiado ansioso por llevar a cabo la orden de Rodenburg, pero tampoco podía ignorarla. También dijo que no volvería a servir a Rodenburg, este último sucio asunto hizo que su copa se desbordara.";
		link.l1.go = "Stivesant_8";
		break;

	case "Stivesant_8":
		dialog.text = "Está bien... Capitán " + GetFullName(pchar) + ", irás a Willemstad conmigo. Navegarás en 'Meifeng' delante de mi barco. Si lo que has dicho es verdad, Lucas debe ser arrestado, y proporcionarás tu asistencia en esto. Pero si me has mentido... Solo tienes a ti mismo para culpar.";
		link.l1 = "Para mí, no tiene sentido mentirte, señor. ¡Vamos, apresurémonos!";
		link.l1.go = "Stivesant_9";
		break;

	case "Stivesant_9":
		DialogExit();
		Diag.CurrentNode = "Stivesant_10";
		AddQuestRecord("Holl_Gambit", "3-52");
		pchar.questTemp.HWIC.Self = "WayWithStivesant";
		Group_DelCharacter("Stivesant_Halleon", "Stivesant");
		SetCharacterRemovable(npchar, false);
		npchar.CompanionEnemyEnable = false; // всегда друзья
		SetCompanionIndex(pchar, -1, sti(npchar.index));
		npchar.loyality = 40;
		DeleteAttribute(npchar, "LifeDay");
		pchar.quest.Seek_Piter.win_condition.l1 = "location";
		pchar.quest.Seek_Piter.win_condition.l1.location = "Villemstad_town";
		pchar.quest.Seek_Piter.win_condition.l2 = "Day";
		pchar.quest.Seek_Piter.function = "StivesantOnStreet";
		pchar.quest.Terms_Over.win_condition.l1 = "Timer";
		pchar.quest.Terms_Over.win_condition.l1.date.hour = sti(GetTime());
		pchar.quest.Terms_Over.win_condition.l1.date.day = GetAddingDataDay(0, 0, 15);
		pchar.quest.Terms_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 15);
		pchar.quest.Terms_Over.win_condition.l1.date.year = GetAddingDataYear(0, 0, 15);
		pchar.quest.Terms_Over.function = "QuestShipsTerms_Over";
		AddMapQuestMarkCity("Villemstad", false);
		break;

	case "Stivesant_10":
		dialog.text = "Capitán, ve a 'Meifeng'. Es hora de zarpar.";
		link.l1 = "Sí, señor, por supuesto.";
		link.l1.go = "exit";
		Diag.TempNode = "Stivesant_10";
		break;

	case "Keller_1":
		dialog.text = "¡Muy interesante! Por favor, cuenta tu historia. Haré lo posible para ayudar.";
		link.l1 = "Señor Keller, ¿recuerdas cómo te encontraste con un filibote en tu camino a Willemstad hace varios meses? Había una familia de refugiados judíos en él. Cenaste a bordo de ese barco y luego continuaste tu viaje.";
		link.l1.go = "Keller_2";
		break;

	case "Keller_2":
		dialog.text = "Sí, supongo que sí... Sí, lo recuerdo bastante claro ahora. Entonces, ¿cuál es el trato?";
		link.l1 = "El filibote fue hundido por piratas ese mismo día. Solo dos refugiados lograron salvarse, Salomón y su hija Abigail. Encontraron refugio en una isla a solo unas millas de donde ocurrió el ataque. Necesito encontrar esa isla. ¿Podrías recordar dónde encontraste ese filibote? Esto es muy importante.";
		link.l1.go = "Keller_3";
		break;

	case "Keller_3":
		dialog.text = "¿Y eso es todo lo que necesitas? Conozco esta isla. Está muy cerca, entre Trinidad y Curazao. Una pequeña isla desierta deshabitada. Ni siquiera hay indígenas allí.";
		link.l1 = "¿Y sabes sus coordenadas aproximadas?";
		link.l1.go = "Keller_4";
		break;

	case "Keller_4":
		dialog.text = "Puedo decirte las coordenadas exactas. Está en 12 48' Norte y 64 41' Oeste. Búscalo allí. La isla es bastante pequeña, pero deberías poder localizarla fácilmente.";
		link.l1 = "¡Gracias, mi señor Keller! Me has ayudado mucho. Adiós.";
		link.l1.go = "Keller_5";
		break;

	case "Keller_5":
		DialogExit();
		Diag.CurrentNode = "Keller_6";
		pchar.quest.Keller_fail.over = "yes";
		pchar.questTemp.HWIC_Coordinates = "true"; // атрибут координат на поиск острова через каюту
		DeleteAttribute(pchar, "questTemp.HWICMC");
		AddQuestRecord("Holl_Gambit", "3-66");
		break;

	case "Keller_6":
		dialog.text = "¿Deseaba algo más, capitán?";
		link.l1 = "No, gracias. Ya estaba volviendo a mi barco.";
		link.l1.go = "exit";
		Diag.TempNode = "Keller_6";
		break;

	// belamour рыбацкое судно -->
	case "FishingBoat":
		pchar.GenQuest.FishingBoatSecondTime = true;
		dialog.text = "Nada especial, esto es un barco de pesca, aquí pescamos. De alguna manera tienes que ganarte la vida.";
		link.l1 = "Sí, estoy de acuerdo, estos son los tiempos...";
		link.l1.go = "FishingBoat_1";
		break;

	case "FishingBoat_1":
		Diag.TempNode = "FishingBoat_1";
		dialog.text = "¿Entonces qué quieres?";
		link.l1 = "Quería" + GetSexPhrase("", "") + " para averiguar las últimas noticias del archipiélago.";
		link.l1.go = "rumours_capitan";
		link.l2 = "¿Cómo están tus capturas hoy? ¿Puedes vender? No me vendrían mal provisiones...";
		link.l2.go = "FishingBoat_2";
		link.l3 = "¡Nada especial, solo vine a saludarte!";
		link.l3.go = "exit";

		break;

	case "FishingBoat_2":
		if (GetDataDay() < 11)
		{
			if (sti(RealShips[sti(npchar.ship.type)].basetype) == SHIP_TARTANE)
				iTemp = 100 + hrand(100);
			else
				iTemp = 200 + hrand(100);
			iMoney = sti(GetCurrentIslandGoodsPrice(GOOD_FOOD) * 0.66);
			pchar.GenQuest.FishingBoatITemp = iTemp;
			pchar.GenQuest.FishingBoatIMoney = iMoney;

			dialog.text = "La pesca es buena hoy, solo tenemos tiempo para sacar las redes. Podemos vendértelo, incluso más barato que en una tienda, de todos modos, vendemos pescado al comerciante. Si traducimos todo esto en provisiones... Ahora tenemos " + iTemp + " de ello, podemos venderlo a un precio de " + iMoney + " pesos cada uno. ¿Cuánto vas a tomar?";
			link.l1.edit = 3;
			link.l1 = "";
			link.l1.go = "Количество вбитого провианта";
			link.l2 = "Sabes, he cambiado de opinión acerca de comprar tus provisiones.";
			link.l2.go = "exit";
		}
		if (GetDataDay() > 10 && GetDataDay() < 21)
		{
			Diag.TempNode = "FishingBoat_1";
			dialog.text = "Sí, algo, para ser honesto, no hay pescado en absoluto ... Casi nada se pescó hoy. Pero los arpones quedaron superfluos, pensaban atrapar algún pez grande o una ballena, si tenías suerte ... ¿Quizás necesitas arpones?";
			link.l1 = "No, no estoy interesado en arpones.";
			link.l1.go = "exit";
			link.l2 = "Hmm, un arpón también es una cosa útil en las manos correctas. Probablemente compraré.";
			link.l2.go = "Гарпуны";
		}
		if (GetDataDay() > 20)
		{
			dialog.text = "Sí, algo, para ser honesto, no hay pescado en absoluto ... Casi nada se pescó hoy. Así que no hay mucho que vender. A menos que ... Tengo unas cuantas baratijas, tal vez algo te interese. ¿Te gustaría ver?";
			link.l1 = "No, no estoy interesado en baratijas.";
			link.l1.go = "exit";
			link.l2 = "Es una lástima que no haya captura. Bueno, al menos echemos un vistazo a tus baratijas, de repente algo atraerá ...";
			link.l2.go = "Торговля";
		}
		break;

	case "Количество вбитого провианта":
		Diag.TempNode = "FishingBoat_1";
		iQty = sti(dialogEditStrings[3]);
		iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
		pchar.GenQuest.FishingBoatIQty = iQty;
		iMoney = makeint(pchar.GenQuest.FishingBoatIMoney);
		if (iQty > iTemp)
		{
			dialog.text = "Eres demasiado... ¡No tengo tanto! ¿Puedes comprar menos?";
			link.l1.edit = 3;
			link.l1 = "";
			link.l1.go = "Количество вбитого провианта повтор";
			link.l2 = "Sabes, he cambiado de opinión acerca de comprar tus provisiones.";
			link.l2.go = "exit";
		}
		if (iQty < 1)
		{
			dialog.text = "¿Estás bromeando? ¿Necesitas provisiones o no? Si es así, ¿cuánto?";
			link.l1.edit = 3;
			link.l1 = "";
			link.l1.go = "Количество вбитого провианта повтор";
			link.l2 = "Sabes, he cambiado de opinión acerca de comprar tus provisiones.";
			link.l2.go = "exit";
		}
		if (iQty > 0 && iQty <= iTemp)
		{
			dialog.text = "¡Trato hecho! " + sti(iQty * iMoney) + " pesos.";
			if (sti(pchar.money) < iQty * iMoney)
			{
				link.l1 = "Hmm, no tengo tanto dinero. Otra vez.";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "¡Trato hecho! Arrastra las mercancías a mi barco.";
				link.l1.go = "Удачная покупка";
				link.l2 = "Sabes, he cambiado de opinión sobre comprar tus provisiones.";
				link.l2.go = "exit";
			}
		}
		break;

	case "Количество вбитого провианта повтор":
		Diag.TempNode = "FishingBoat_1";
		iQty = sti(dialogEditStrings[3]);
		iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
		pchar.GenQuest.FishingBoatIQty = iQty;
		iMoney = makeint(pchar.GenQuest.FishingBoatIMoney);
		if (iQty > iTemp)
		{
			dialog.text = "Eres demasiado... ¡No tengo tanto! ¿Puedes comprar menos?";
			link.l1.edit = 3;
			link.l1 = "";
			link.l1.go = "Количество вбитого провианта";
			link.l2 = "Sabes, he cambiado de opinión acerca de comprar tus provisiones.";
			link.l2.go = "exit";
		}
		if (iQty < 1)
		{
			dialog.text = "¿Me estás tomando el pelo? ¿Necesitas provisiones o no? Si es así, ¿cuánto?";
			link.l1.edit = 3;
			link.l1 = "";
			link.l1.go = "Количество вбитого провианта";
			link.l2 = "Sabes, he cambiado de opinión sobre comprar tus provisiones.";
			link.l2.go = "exit";
		}
		if (iQty > 0 && iQty <= iTemp)
		{
			dialog.text = "¡Trato hecho! " + sti(iQty * iMoney) + " pesos.";
			if (sti(pchar.money) < iQty * iMoney)
			{
				link.l1 = "Hmm, no tengo tanto dinero. Otro tiempo.";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "¡Trato hecho! Arrastra las mercancías a mi barco.";
				link.l1.go = "Удачная покупка";
				link.l2 = "Sabes, he cambiado de opinión sobre comprar tus provisiones.";
				link.l2.go = "exit";
			}
		}
		break;

	case "Удачная покупка":
		Diag.TempNode = "First time";
		Diag.CurrentNode = "First time";
		iQty = makeint(pchar.GenQuest.FishingBoatIQty);
		iMoney = makeint(pchar.GenQuest.FishingBoatIMoney);
		iTemp = iQty * iMoney;
		DialogExit();
		SetCharacterGoods(pchar, GOOD_FOOD, GetCargoGoods(pchar, GOOD_FOOD) + iQty);
		AddMoneyToCharacter(pchar, -iTemp);
		break;

	case "Гарпуны":
		Diag.TempNode = "FishingBoat_1";
		iTemp = 5 + hrand(5);
		pchar.GenQuest.FishingBoatITemp = iTemp;
		dialog.text = "Tenemos " + iTemp + " trozos. Podemos vender por cien pesos un arpón. ¿Cuánto necesitas?";
		link.l1.edit = 3;
		link.l1 = "";
		link.l1.go = "Количество вбитых гарпунов";
		link.l2 = "Sabes, he cambiado de opinión, no necesito los arpones.";
		link.l2.go = "exit";
		break;

	case "Количество вбитых гарпунов":

		iQty = sti(dialogEditStrings[3]);
		iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
		pchar.GenQuest.FishingBoatIQty = iQty;
		Diag.TempNode = "FishingBoat_1";
		if (iQty > iTemp)
		{
			dialog.text = "Eres demasiado... ¡No tengo tanto! ¿Puedes comprar menos?";
			link.l1.edit = 3;
			link.l1 = "";
			link.l1.go = "Количество вбитых гарпунов заново";
			link.l2 = "Sabes, he cambiado de opinión, no necesito los arpones.";
			link.l2.go = "exit";
		}
		if (iQty < 1)
		{
			dialog.text = "¿Te estás burlando de mí? ¿Necesitas arpones o no? Si es así, ¿cuántos?";
			link.l1.edit = 3;
			link.l1 = "";
			link.l1.go = "Количество вбитых гарпунов заново";
			link.l2 = "Sabes, he cambiado de opinión, no necesito los arpones.";
			link.l2.go = "exit";
		}
		if (iQty > 0 && iQty <= iTemp)
		{
			dialog.text = "¡Trato hecho! " + sti(iQty * 100) + " pesos.";
			if (sti(pchar.money) < iQty * 100)
			{
				link.l1 = "Hmm, no tengo tanto dinero. Otra vez.";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "¡Trato hecho! Encontraré un uso para ellos.";
				link.l1.go = "Удачная покупка гарпунов";
				link.l2 = "Sabes, he cambiado de opinión, no necesito los arpones.";
				link.l2.go = "exit";
			}
		}
		break;

	case "Количество вбитых гарпунов заново":
		iQty = sti(dialogEditStrings[3]);
		iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
		pchar.GenQuest.FishingBoatIQty = iQty;
		Diag.TempNode = "FishingBoat_1";
		if (iQty > iTemp)
		{
			dialog.text = "Eres demasiado... ¡No tengo tanto! ¿Podrías comprar menos?";
			link.l1.edit = 3;
			link.l1 = "";
			link.l1.go = "Количество вбитых гарпунов";
			link.l2 = "Sabes, he cambiado de opinión, no necesito los arpones.";
			link.l2.go = "exit";
		}
		if (iQty < 1)
		{
			dialog.text = "¿Estás bromeando? ¿Necesitas arpones o no? Si es así, ¿cuántos?";
			link.l1.edit = 3;
			link.l1 = "";
			link.l1.go = "Количество вбитых гарпунов";
			link.l2 = "Sabes, he cambiado de opinión, no necesito los arpones.";
			link.l2.go = "exit";
		}
		if (iQty > 0 && iQty <= iTemp)
		{
			dialog.text = "¡Trato hecho! " + sti(iQty * 100) + " pesos.";
			if (sti(pchar.money) < iQty * 100)
			{
				link.l1 = "Umm, no tengo tanto dinero. Otra vez.";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "¡Trato hecho! Encontraré un uso para ellos.";
				link.l1.go = "Удачная покупка гарпунов";
				link.l2 = "Sabes, he cambiado de opinión, no necesito los arpones.";
				link.l2.go = "exit";
			}
		}
		break;

	case "Удачная покупка гарпунов":
		DialogExit();
		Diag.TempNode = "First time";
		Diag.CurrentNode = "First time";
		iQty = makeint(pchar.GenQuest.FishingBoatIQty);
		TakeNItems(pchar, "slave_01", iQty);
		AddMoneyToCharacter(pchar, -iQty * 100);

		break;

	case "Торговля":
		DialogExit();
		Diag.TempNode = "First time";
		Diag.CurrentNode = "First time";
		if (!CheckAttribute(pchar, "GenQuest.FishingBoatDialogEnb"))
			pchar.GenQuest.FishingBoatDialogEnb = true;
		LaunchItemsTrade(NPChar, 0);
		break;

	case "Особые товары":
		if (hrand(2, "&SpeGoo") == 0)
		{
			Diag.TempNode = "First time";
			Diag.CurrentNode = "First time";
			pchar.GenQuest.FishingBoatDialogEnb = "no special goods";
			dialog.text = "No, no hay nada más. ¡Es un barco de pesca! ¿Qué más podría estar aquí?";
			link.l1 = "Bien, lo entiendo.";
			link.l1.go = "exit";
		}
		else if (hrand(2, "&SpeGoo") == 1)
		{
			if (ChangeContrabandRelation(pchar, 0) > 5)
			{

				dialog.text = "Bueno ... Tengo aquí una pequeña cosa ... La guardé, pensé en vendérsela a alguien. ¡Pero cobraré mucho por ella! Y no ofreceré una segunda vez. ¿Vas a ver?";
				link.l1 = "Muéstrame, veamos qué tipo de cosita.";
				link.l1.go = "Особые товары предметы";
			}
			else
			{
				Diag.TempNode = "First time";
				Diag.CurrentNode = "First time";
				pchar.GenQuest.FishingBoatDialogEnb = "no special goods";
				dialog.text = "No, no hay nada más. ¡Es un barco de pesca! ¿Qué más podría estar aquí?";
				link.l1 = "Bien, lo entiendo. ";
				link.l1.go = "exit";
			}
		}
		else
		{
			pchar.GenQuest.FishingBoatDialogEnb = "no special goods";
			Diag.TempNode = "First time";
			Diag.CurrentNode = "First time";
			if (ChangeContrabandRelation(pchar, 0) > 5)
			{
				if (GetDataDay() < 8)
				{
					iMoney = GetStoreGoodsPrice(&Stores[SantaCatalina_STORE], GOOD_SANDAL, PRICE_TYPE_BUY, pchar, 1);
					iTemp = GOOD_SANDAL;
					sTemp = "tablones de madera";
				}
				if (GetDataDay() > 7 && GetDataDay() < 15)
				{
					iMoney = GetStoreGoodsPrice(&Stores[PortSpein_STORE], GOOD_OIL, PRICE_TYPE_BUY, pchar, 1);
					iTemp = GOOD_OIL;
					sTemp = "barriles de resina para barco";
				}
				if (GetDataDay() > 14 && GetDataDay() < 22)
				{
					iMoney = GetStoreGoodsPrice(&Stores[BasTer_STORE], GOOD_ROPES, PRICE_TYPE_BUY, pchar, 1);
					iTemp = GOOD_ROPES;
					sTemp = "rollos de cuerdas barco";
				}
				if (GetDataDay() > 21)
				{
					iMoney = GetStoreGoodsPrice(&Stores[Villemstad_STORE], GOOD_SHIPSILK, PRICE_TYPE_BUY, pchar, 1);
					iTemp = GOOD_SHIPSILK;
					sTemp = "rollos de seda de barco";
				}
				iQty = 20 + sti(rand(6) * 5);
				pchar.GenQuest.FishingBoatITemp = iTemp;
				pchar.GenQuest.FishingBoatIMoney = iMoney;
				pchar.GenQuest.FishingBoatIQty = iQty;

				dialog.text = "Bueno ... Tengo una buena aquí ... Puramente por casualidad la encontré en la orilla de la bahía. Es " + iQty + " " + sTemp + ". El precio por pieza es " + iMoney + ". Pero solo venderé todo de una vez y no ofreceré una segunda vez. Y para que ningún forastero lo sepa ... ¿entiendes?";
				link.l1 = "No, no quiero los bienes dudosos, gracias. No le diré a nadie, no te preocupes.";
				link.l1.go = "exit";
				if (sti(pchar.money) >= iMoney * iQty)
				{
					link.l2 = "Te entiendo. Pero las mercancías valen la pena. Me lo llevo. Haz que lo entreguen en mi barco.";
					link.l2.go = "Купили стратегический товар";
				}
			}
		}
		break;

	case "Особые товары предметы":
		pchar.GenQuest.FishingBoatDialogEnb = "no special goods";
		Diag.TempNode = "First time";
		Diag.CurrentNode = "First time";
		if (ChangeContrabandRelation(pchar, 0) > 5)
		{
			switch (GetDataDay())
			{
			case 21:
				sTemp = "mushket1";
				break;
			case 22:
				sTemp = "cirass5";
				break;
			case 23:
				sTemp = "blade_16";
				break;
			case 24:
				sTemp = "blade_04";
				break;
			case 25:
				sTemp = "blade_06";
				break;
			case 26:
				sTemp = "compass1";
				break;
			case 27:
				sTemp = "clock2";
				break;
			case 28:
				sTemp = "pistol4";
				break;
			case 29:
				sTemp = "pistol2";
				break;
			case 30:
				sTemp = "obereg_9";
				break;
			case 31:
				sTemp = "obereg_10";
				break;
			}
			pchar.GenQuest.FishingBoatSTemp = sTemp;
			dialog.text = "Es " + GetConvertStr("itmname_" + sTemp, "Descripción de los ítems.txt") + ". Logré conseguir ... bueno, no importa de dónde. Pensé en venderlo a algún conocedor. ¡Te lo daré por solo 10 000 pesos! ¿Lo tomarás?";
			if (sti(pchar.money) > 9999)
			{
				link.l1 = "¡Lo tomaré, por supuesto! La cosa está de pie. ";
				link.l1.go = "Купили особый товар";
			}
			link.l2 = "No, no lo necesito. No lo tomaré. ";
			link.l2.go = "exit";
		}

		break;

	case "Купили особый товар":
		Diag.TempNode = "First time";
		Diag.CurrentNode = "First time";
		DialogExit();
		sTemp = pchar.GenQuest.FishingBoatSTemp;
		if (GetDataDay() != 23 || GetDataDay() != 24 || GetDataDay() != 25)
		{
			TakeNItems(pchar, sTemp, 1);
		}
		else
		{
			sTemp = GetGeneratedItem(sTemp);
			GiveItem2Character(pchar, sTemp);
		}
		AddMoneyToCharacter(pchar, -10000);
		break;

	case "Купили стратегический товар":
		Diag.TempNode = "First time";
		Diag.CurrentNode = "First time";
		iQty = makeint(pchar.GenQuest.FishingBoatIQty);
		iMoney = makeint(pchar.GenQuest.FishingBoatIMoney);
		iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
		DialogExit();
		SetCharacterGoods(pchar, iTemp, GetCargoGoods(pchar, iTemp) + iQty);
		AddMoneyToCharacter(pchar, -iMoney * iQty);
		break;
		// <-- рыбацкое судно
	}
}

string GetNumShips(int ship)
{
	string numships;
	switch (ship)
	{
	case 0:
		numships = "sin barcos";
		break;
	case 1:
		numships = "un barco";
		break;
	case 2:
		numships = "dos barcos";
		break;
	case 3:
		numships = "tres barcos";
		break;
	case 4:
		numships = "cuatro barcos";
		break;
	case 5:
		numships = "cinco barcos";
		break;
	case 6:
		numships = "seis barcos";
		break;
	}
	return numships;
}

string GetPart(int part)
{
	string numpart;
	switch (part)
	{
	case 0:
		numpart = "";
		break;
	case 1:
		numpart = "todo el botín";
		break;
	case 2:
		numpart = "la mitad del botín";
		break;
	case 3:
		numpart = "un tercio del botín";
		break;
	case 4:
		numpart = "la cuarta parte del botín";
		break;
	}
	return numpart;
}

int findPriceStoreMan(ref NPChar)
{
	ref ch;
	int n;
	int storeArray[40];
	int howStore = 0;

	for (n = 0; n < MAX_CHARACTERS; n++)
	{
		makeref(ch, Characters[n]);
		if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") // магазин
		{
			// if (sti(ch.nation) !=  sti(NPChar.nation)) continue;
			if (ch.location == "none")
				continue; // фикс для новых, невидимых до поры островов
			storeArray[howStore] = n;
			howStore++;

			// homo 05/09/06
			if (CheckAttribute(NPChar, "FromColony") && NPChar.FromColony == ch.City)
				return n;
			//
		}
	}
	if (howStore == 0)
	{
		return -1;
	}
	else
	{
		return storeArray[rand(howStore - 1)];
	}
}
