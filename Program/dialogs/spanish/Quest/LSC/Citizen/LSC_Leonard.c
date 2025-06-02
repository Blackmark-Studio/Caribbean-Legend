// Леонард Маскетт - пьяница
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iPeso, iDubl;
	string sPeso, sDubl;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
		{
			dialog.text = "No quiero hablar contigo. Atacas a civiles pacíficos sin motivo y los provocas a pelear. ¡Piérdete!";
			link.l1 = "Mm...";
			link.l1.go = "exit";
			break;
		}
		// --> пей до дна
		if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_3") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.facio"))
		{
			dialog.text = "Compañero, llegas justo a tiempo... Quiero hablar contigo... sobre un negocio. Uno importante.";
			link.l1 = "¿De verdad? Parece que no estás borracho. ¿Ha pasado algo? Es raro verte sobrio.";
			link.l1.go = "facio";
			break;
		}
		// <-- пей до дна
		if (npchar.quest.meeting == "0")
		{
			dialog.text = "¡A-a... hic! Hola, amigo...";
			link.l1 = TimeGreeting() + "  Parece que ya has tenido suficiente, amigo.";
			link.l1.go = "meeting";
			npchar.quest.meeting = "1";
		}
		else
		{
			dialog.text = "Ah, " + GetFullName(pchar) + "¡Hic! ¿Qué quieres?";
			link.l1 = LinkRandPhrase("¿Tienes algo interesante que contar?", "¿Ha ocurrido algo nuevo en la isla?", "¿Me contarás los últimos chismes?");
			link.l1.go = "rumours_LSC";
			link.l2 = "Quiero hacerte unas preguntas sobre la isla.";
			link.l2.go = "int_quests"; // информационный блок
			link.l5 = "Solo quería saber cómo estás. ¡Nos vemos!";
			link.l5.go = "exit";
		}
		NextDiag.TempNode = "First time";
		break;

	case "meeting": // первая встреча
		dialog.text = "¡Sí! ¿Suficiente? ¡No-o! ¡Soy un borracho loco, hi-hic! ¡Sí, Leonard Musket está borracho y eso es lo correcto!";
		link.l1 = "¿Aficionado a las bebidas, eh? Sí, mi nombre es " + GetFullName(pchar) + "Encantado de conocerte.";
		link.l1.go = "meeting_1";
		break;

	case "meeting_1":
		dialog.text = "Si tú lo dices. Todos aquí... hic, nos encontramos.";
		link.l1 = "Está bien, parece que no estás de humor para hablar. ¡Nos vemos!";
		link.l1.go = "exit";
		link.l2 = LinkRandPhrase("¿Tienes algo interesante que decir?", "¿Ha sucedido algo nuevo en la isla?", "¿Me contarás los últimos chismes?");
		link.l2.go = "rumours_LSC";
		link.l3 = "Quiero hacerte unas preguntas sobre la isla.";
		link.l3.go = "int_quests"; // информационный блок
		NextDiag.TempNode = "First time";
		break;

	// --> пей до дна
	case "facio":
		dialog.text = "Sí, amigo, estoy casi sobrio. Y eso es porque tengo un asunto para ti, uno importante. Y parece que puedes hacerlo...";
		link.l1 = "¿Qué? ¿Qué tienes en mente? ¡Habla y no me hagas perder el tiempo por nada!";
		link.l1.go = "facio_1";
		npchar.quest.facio = "true";
		break;

	case "facio_1":
		dialog.text = "Amigo, ¿quieres ganar algo de dinero? ¿Pesos de plata, doblones de oro? Te diré cómo. Pero tendrás que compartir conmigo, trabajaremos juntos.";
		link.l1 = "Siempre quiero hacerlo. Pero todo depende de tu propuesta: no hago ningún trabajo, incluso si es muy rentable.";
		link.l1.go = "facio_2";
		break;

	case "facio_2":
		dialog.text = "El negocio no es realmente legal, claro, pero es rentable... y podremos castigar a un hombre que se ha vuelto demasiado exigente. No se empobrecerá, tiene demasiado dinero. Todos comparten con él, así que ahora es su turno de hacer lo mismo. Dime, ¿puedes manejar el ron? ¿Cuánto eres capaz de beber antes de caer bajo la mesa?";
		link.l1 = "Depende. No estoy seguro de que tenga el hábito de beber como un loco... ¿Vas a contarme los detalles al fin?";
		link.l1.go = "facio_3";
		break;

	case "facio_3":
		dialog.text = "Estoy llegando al punto, simplemente no lo ves todavía. Bien. Seré específico. Hay un bastardo gordo y feo en la Isla, Giuseppe Fazio. Una rara escoria. Despelleja vivos a los Narvales, Rivados y a los lugareños. Lo he estado vigilando por un tiempo y finalmente tengo algo.  \nHay dos cofres en su cabaña en Carolina: el primero contiene papeles, el segundo contiene oro y plata. Ambos están cerrados con diferentes llaves. El gordo siempre lleva las llaves consigo.";
		link.l1 = "Bueno, ¿parece que vas a robar a Fazio? No participaré en eso. Y será mejor que te alegres de que no se lo cuente a nadie. Si quieres revisar el cofre del gordo, deberías encontrar otro compañero.";
		link.l1.go = "facio_exit";
		link.l2 = "¡Ja! ¡Interesante! Continúa...";
		link.l2.go = "facio_4";
		break;

	case "facio_exit":
		dialog.text = "Qué mal, realmente mal... Hay mucho oro, suficiente para ambos. Bien, nos vemos por ahí...";
		link.l1 = "Adiós.";
		link.l1.go = "exit";
		break;

	case "facio_4":
		dialog.text = "Dos puertas conducen a su camarote. Una de ellas siempre está cerrada con llave. Pero la llave que abre el cofre con oro también abre la puerta. No sé cuál es el sentido de todo esto, pero es un hecho. Solo necesitas una llave para abrir el camarote y obtener el oro. Una pregunta lógica surge a continuación: ¿cómo adquirir la llave? Así que tengo un plan\nUn plan excelente, si sale bien, Fazio nunca se dará cuenta de lo que pasó y a quién culpar. Pensarán que fue el ladrón misterioso. El problema es que necesito un socio con cabeza de hierro para llevarlo a cabo. ¿Me sigues?";
		link.l1 = "Estoy escuchando. Continúa.";
		link.l1.go = "facio_5";
		break;

	case "facio_5":
		dialog.text = "Fazio ama sentarse en la taberna de Sancho y disfrutar de un buen trago, pero su corpulencia es demasiado pesada para que el ron haga su trabajo. Así que se le ocurrió un juego de beber, donde la gente intenta beber más que él. Si le propones jugar a este juego, sin duda aceptará\nY luego viene la parte divertida. Haces una apuesta con él, vas a la taberna, agarras ron y bebes hasta que uno de ustedes caiga sobre la mesa. Si te rajas, todo el plan fracasará, no podré hacerlo solo\nPor eso pregunté por tu cabeza. Si logras que Fazio gruña y gima como un cerdo, considera que está hecho. Estaré cerca todo el tiempo. Cuando termine, tomaré sus llaves\nLuego trasladamos al gordo a una cama arriba y nos colamos en su camarote mientras duerme. Devolveré la llave justo después de que saquemos el botín de su cofre, ni siquiera se dará cuenta de que fue robado\nYo me encargaré de adquirir y devolver la llave, tu misión es emborrachar a Fazio e infiltrarte en su propiedad. Me quedaré de guardia por si aparece alguien, así tendrás tiempo suficiente para escapar por la puerta trasera\nNos dividiremos el contenido del cofre a partes iguales, eso sería justo. Entonces, ¿estás dentro?";
		link.l1 = "¡Buen plan! ¡Claro, intentémoslo!";
		link.l1.go = "facio_6";
		link.l2 = "No, amigo. Paso. Temo que no podré beber tanto para mantenerme en pie y superar a Fazio en beber. Busca otro compañero, un poco más fuerte que yo.";
		link.l2.go = "facio_exit";
		break;

	case "facio_6":
		dialog.text = "Me alegra haber acertado contigo. Ahora ve a Fazio y organiza una reunión en la taberna por la noche después de las nueve. ¡Espero que logres emborrachar a ese cerdo! Buena suerte y nos vemos por la noche.";
		link.l1 = "Lo intentaré... ¡Adiós!";
		link.l1.go = "facio_7";
		break;

	case "facio_7":
		DialogExit();
		NextDiag.CurrentNode = "facio_wait";
		pchar.questTemp.LSC.Drink = "begin";
		pchar.questTemp.LSC.Drink.Chance = hrand(100); // итог бухалова
		if (CheckAttribute(pchar, "questTemp.CanDrink"))
			pchar.questTemp.LSC.Drink.Chance = sti(pchar.questTemp.LSC.Drink.Chance) + 50;
		SetFunctionTimerCondition("LSC_DrinkOver", 0, 0, 3, false); // 3 дня
		AddQuestRecord("LSC_Drink", "1");
		break;

	case "facio_wait":
		dialog.text = "Amigo, cuento contigo. Durante la bebida ese gordo...";
		link.l1 = "Claro...";
		link.l1.go = "exit";
		NextDiag.TempNode = "facio_wait";
		break;

	case "result_0":
		dialog.text = "Está hecho, ese cerdo gordo está durmiendo arriba. Tengo la llave. ¡Lo estás haciendo bien, pareces estar lo suficientemente sobrio!";
		link.l1 = "¿Es así? Ha pasado mucho tiempo desde que me embriagué tanto. Me siento un poco mareado... ¿Vamos?";
		link.l1.go = "result_win";
		break;

	case "result_1":
		dialog.text = "Está hecho, ese cerdo gordo está durmiendo arriba. Tengo la llave. Lo estás haciendo bien, realmente lograste emborrachar a ese cerdo...";
		link.l1 = "Lo he hecho, pero ha pasado mucho tiempo desde que me embriagué tanto. Tengo la cabeza dando vueltas... ¿Vamos entonces?";
		link.l1.go = "result_win";
		break;

	case "result_2":
		dialog.text = "Eh, compadre, no has logrado beber más que el gordo... Qué pena. Bueno, al menos lo hemos intentado...";
		link.l1 = "¡M-maldita sea, es como un... barril sin f-fondo. Argh, necesito des-descansar... Se acabó, ¡lárgate! ¡Hic!..";
		link.l1.go = "result_fail";
		break;

	case "result_win":
		dialog.text = "Sí. ¡Vamos! ¡Sígueme a 'Carolina'! Y no te despistes, ¡no tenemos mucho tiempo!";
		link.l1 = "¡Vamos!";
		link.l1.go = "result_win_1";
		break;

	case "result_win_1":
		DialogExit();
		NextDiag.CurrentNode = "result_win_2";
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload6", "LostShipsCity_town", "reload", "reload39", "LSC_DrinkGotoCarolina", -1);
		AddQuestRecord("LSC_Drink", "3");
		break;

	case "result_win_2":
		pchar.quest.LSC_Drink1.over = "yes"; // снять таймер
		dialog.text = "Aquí. Toma la llave. El cofre que necesitas está a la izquierda de la entrada. Toma tanto como puedas rápidamente. No olvides cerrarlo de nuevo. Si veo algo, golpearé la puerta tres veces. Escapa por la galería trasera en ese caso.";
		link.l1 = "Está bien. ¡Mantente alerta!";
		link.l1.go = "result_win_3";
		break;

	case "result_win_3":
		DialogExit();
		GiveItem2Character(pchar, "key_facioQ");
		NextDiag.CurrentNode = "result_grabbing";
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "reload", "reload25", "LSC_DrinkGotoCarolina_3", -1);
		break;

	case "result_grabbing":
		// считаем деньги и дублоны взятые из сундука
		iPeso = sti(pchar.money) - sti(pchar.questTemp.LSC.Drink.Money);
		iDubl = GetCharacterItem(pchar, "gold_dublon") - sti(pchar.questTemp.LSC.Drink.Dublon);
		if (iPeso <= 0)
			sPeso = "ni un solo peso";
		else
			sPeso = "" + FindRussianMoneyString(iPeso) + "";
		if (iDubl <= 0)
			sDubl = "ni un solo doblón";
		else
			sDubl = "" + iDubl + " doubloons";
		if (iPeso <= 10000 && iDubl <= 10)
			sTotalTemp = "Qué miserable botín... ¿Y nos arriesgamos por él? Eh... Bien, compartamos lo que tenemos.";
		else
		{
			if (iPeso <= 50000 && iDubl <= 100)
				sTotalTemp = "Pensé que habría mucho más... El riesgo no valía la pena. Eh... Bien, compartamos lo que tenemos.";
			else
			{
				if (iPeso <= 100000 && iDubl <= 300)
					sTotalTemp = "Hm. No está mal. Pero pensé que tendríamos más. Bien, compartámoslo.";
				else
				{
					if (iPeso <= 150000 && iDubl <= 500)
						sTotalTemp = "¡Excelente! ¡Lo hemos hecho bien, compañero! ¡Esto es un montón de monedas! ¡Compartámoslas!";
					else
					{
						sTotalTemp = "¡Vaya! Nunca había pensado que el alijo del gordo fuera tan enorme. ¡Bien hecho, compañero! ¡Compartámoslo!";
					}
				}
			}
		}
		dialog.text = "¡Por fin! ¿Qué lograste sacar del cofre de ese canalla? ¡Muéstramelo, espero con impaciencia!";
		if (iPeso <= 0 && iDubl <= 0)
		{
			link.l1 = "No había nada en absoluto. Solo unos pocos restos, amuletos y esas cosas.";
			link.l1.go = "grabbing_0";
		}
		else
		{
			link.l1 = "He tomado del cofre " + sPeso + " y " + sDubl + ".";
			link.l1.go = "grabbing_1";
		}
		break;

	case "grabbing_0":
		dialog.text = "¡Imposible! Parece que todo fue en vano... Quizás ese bastardo ha puesto su botín en otro cofre. ¡Eh! Bien, dame la llave y la devolveré a su dueño antes de que la extrañe. Adiós, camarada...";
		link.l1 = "...";
		link.l1.go = "grabbing_exit";
		AddQuestRecord("LSC_Drink", "6");
		break;

	case "grabbing_1":
		dialog.text = sTotalTemp;
		link.l1 = "Compartamos...";
		link.l1.go = "grabbing_part";
		break;

	case "grabbing_part":
		iPeso = makeint((sti(pchar.money) - sti(pchar.questTemp.LSC.Drink.Money)) / 2);
		iDubl = makeint((GetCharacterItem(pchar, "gold_dublon") - sti(pchar.questTemp.LSC.Drink.Dublon)) / 2);
		AddMoneyToCharacter(pchar, -iPeso);
		RemoveItems(pchar, "gold_dublon", iDubl);
		Log_Info("Has entregado " + iDubl + " doblones");
		PlaySound("interface\important_item.wav");
		dialog.text = "Está bien, dame la llave y la devolveré a su dueño antes de que la eche de menos. Adiós, camarada...";
		link.l1 = "Buena suerte, amigo...";
		link.l1.go = "grabbing_exit";
		AddSimpleRumourCityTip("Fazio se quejaba de que alguien le había limpiado el pecho. Parece que el misterioso ladrón lo hizo.", "LostShipsCity", 3, 1, "LSC", "");
		AddSimpleRumourCityTip("¿Te has enterado? ¡Han robado a Fazio! Le robaron estando borracho después de jugar contigo.", "LostShipsCity", 3, 1, "LSC", "");
		AddSimpleRumourCityTip("¡Tienes una cabeza fuerte! ¡Para beber tanto ron y mantenerte en pie! Eso es algo...", "LostShipsCity", 3, 2, "LSC", "");
		AddQuestRecord("LSC_Drink", "5");
		break;

	case "grabbing_exit":
		DialogExit();
		RemoveItems(pchar, "key_facioQ", 1);
		int n = Findlocation("CarolineBank");
		locations[n].private2.QuestClosed = true;					 // запираем сундук
		LocatorReloadEnterDisable("CarolineBank", "reload1", false); // на галерею
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload38", "FleuronTavern", "goto", "goto2", "OpenTheDoors", 15.0);
		pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
		pchar.quest.LSC_Drink4.win_condition.l1.date.hour = sti(GetTime() + 5);
		pchar.quest.LSC_Drink4.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
		pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
		pchar.quest.LSC_Drink4.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
		pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
		break;

	case "result_fail":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1", "LostShipsCity_town", "goto", "goto05_2", "", 10);
		chrDisableReloadToLocation = false; // открыть локацию
		n = Findlocation("CarolineBank");
		locations[n].private2.QuestClosed = true; // запираем сундук
		pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
		pchar.quest.LSC_Drink4.win_condition.l1.date.hour = sti(GetTime() + 5);
		pchar.quest.LSC_Drink4.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
		pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
		pchar.quest.LSC_Drink4.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
		pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
		AddQuestRecord("LSC_Drink", "4");
		break;
		// <-- пей до дна

		//--------------------------------------- блок вопросов и ответов ---------------------------------------------
	case "int_quests":
		dialog.text = "¿De verdad?... ¡hic! Estoy escuchando...";
		if (!CheckAttribute(npchar, "quest.answer_1"))
		{
			link.l1 = "¿Cómo terminaste aquí?";
			link.l1.go = "ansewer_1";
		}
		if (!CheckAttribute(npchar, "quest.answer_2"))
		{
			link.l2 = "¿Siempre bebes? ¿Y dónde encuentras monedas para las bebidas?";
			link.l2.go = "ansewer_2";
		}
		if (!CheckAttribute(npchar, "quest.answer_3"))
		{
			link.l3 = "¿Qué puedes decirme sobre los lugareños?";
			link.l3.go = "ansewer_3";
		}
		if (!CheckAttribute(npchar, "quest.answer_4"))
		{
			link.l4 = "¿Te gustaría dejar este lugar e ir al continente?";
			link.l4.go = "ansewer_4";
		}
		link.l10 = "Sin preguntas. Perdón...";
		link.l10.go = "exit";
		break;

	case "ansewer_1":
		dialog.text = "¡Sí! Te juro, no lo recuerdo. Sí, sí, ¡no lo recuerdo! Fue hace mucho tiempo. Estaba navegando por algún lugar de alguna manera y finalmente terminé aquí. ¡Hic!";
		link.l1 = "Mmm... Está bien, está bien.";
		link.l1.go = "int_quests";
		npchar.quest.answer_1 = "true";
		break;

	case "ansewer_2":
		dialog.text = "Sí, soy un borracho... Bebiendo, maldita sea, porque no me queda nada más que hacer... Verás, camarada, estoy acabado. La botella de ron es lo único que quiero. Así que seguiré bebiendo. Y dinero... je-je, el ron no cuesta mucho. De todos modos, ni siquiera tengo que comprarlo\nHay un lugar lleno de ron, pero necesitas nadar si quieres conseguirlo, por eso solo compro ron cuando estoy demasiado borracho para nadar... ¡hic! Jijijijijiji, no, no te diré dónde nadar, je-je, ni lo preguntes...";
		link.l1 = "Maravilloso.";
		link.l1.go = "int_quests";
		npchar.quest.answer_2 = "true";
		break;

	case "ansewer_3":
		dialog.text = "¿Qué puedo decir, hip... sobre ellos? Buena gente para hablar y beber. Giuseppe Fazio es un hombre tan importante, un pez gordo, sus cofres están llenos de oro... y sin embargo, respeta al viejo Leo, le compra bebidas en la taberna. Aunque, a veces también pide algo a cambio, pero es nada, ¡hip!\n¡Eh, no sabes cuántos doblones tiene Fazio, ja-ja-ja! Suficiente para pasar el resto de tu vida en la mejor casa de todo el Caribe sin trabajar y bebiendo el mejor ron del mundo. Pero él se queda aquí, en la Isla. Parece que aún no hay suficiente dinero para él...";
		link.l1 = "Entendido...";
		link.l1.go = "int_quests";
		npchar.quest.answer_3 = "true";
		SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;

	case "ansewer_4":
		dialog.text = "¿Irme? ¡Hic! ¿Por qué? No, no quiero ir ni al continente ni a la pobre isla. ¿Hay algún ron gratis? ¡No! No hay ron gratis, ¡hic! Y eso significa que no tengo nada que hacer allí... Amigo, me siento bien aquí. Te diré más: pregunta a la gente si quieren dejar este lugar. Nadie quiere, excepto dos o tres, ¡hic!";
		link.l1 = "Interesante...";
		link.l1.go = "int_quests";
		npchar.quest.answer_4 = "true";
		break;
		// <-- блок вопросов и ответов

		//----------------------------------------- специальные реакции -----------------------------------------------
		// обнаружение ГГ в сундуках
	case "Man_FackYou":
		dialog.text = LinkRandPhrase("¿Qué estás haciendo ahí, eh? ¡Ladrón!", "¡Solo mira eso! ¡Tan pronto como me perdí en la contemplación, decidiste revisar mi cofre!", "¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!");
		link.l1 = "¡Mierda!";
		link.l1.go = "fight";
		break;

	case "Woman_FackYou":
		dialog.text = "¿Qué?! ¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!";
		link.l1 = "¡Chica tonta!";
		link.l1.go = "exit_setOwner";
		LAi_group_Attack(NPChar, Pchar);
		break;

	case "fight":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_SetOwnerTypeNoGroup(npchar);
		LAi_group_Attack(NPChar, Pchar);
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "exit_setOwner":
		LAi_SetOwnerTypeNoGroup(npchar);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	// замечание по обнажённому оружию
	case "LSCNotBlade":
		dialog.text = LinkRandPhrase("Escucha, será mejor que guardes tu arma. Me pone nervioso.", "Sabes, correr con la espada desenvainada no se tolera aquí. Guárdala.", "Escucha, no juegues al caballero medieval corriendo con una espada. Guárdala, no te queda bien...");
		link.l1 = LinkRandPhrase("Bien.", "Está bien.", "Como usted diga...");
		link.l1.go = "exit";
		NextDiag.TempNode = "First Time";
		break;

	case "CitizenNotBlade":
		if (loadedLocation.type == "town")
		{
			dialog.text = NPCharSexPhrase(NPChar, "Escucha, soy ciudadano de la ciudad y te pediría que mantengas tu espada envainada.", "Escucha, soy ciudadano de la ciudad y te pediría que bajes tu espada.");
			link.l1 = LinkRandPhrase("Bien.", "Está bien.", "Como usted diga...");
		}
		else
		{
			dialog.text = NPCharSexPhrase(NPChar, "Ten cuidado, camarada, al correr con un arma. Puedo ponerme nervioso...", "No me gusta cuando los hombres caminan frente a mí con sus armas listas. Me asusta...");
			link.l1 = RandPhraseSimple("Entendido.", "Me lo estoy llevando.");
		}
		link.l1.go = "exit";
		NextDiag.TempNode = "First Time";
		break;
		// <-- специальные реакции

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
