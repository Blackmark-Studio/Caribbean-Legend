// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué tipo de preguntas?", "¿Qué quieres, " + GetAddress_Form(NPChar) + "?"), "Ya has intentado hacerme una pregunta " + GetAddress_Form(NPChar) + "...", "Has estado hablando sobre alguna cuestión por tercera vez hoy...", "Mira, si no tienes nada que contarme sobre los asuntos del puerto, entonces no me molestes con tus preguntas.", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión.", "No tengo nada de qué hablar."), "No importa.", "De hecho, ya es la tercera vez...", "Lo siento, pero no me interesan los asuntos del puerto por ahora.", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";

		// belamour legengary edition на пару с Акулой -->
		if (CheckAttribute(pchar, "questTemp.SharkGoldFleet"))
		{
			if (pchar.questTemp.SharkGoldFleet == "toCarPortOffice" || pchar.questTemp.SharkGoldFleet == "start" || pchar.questTemp.SharkGoldFleet == "afterGvik" || pchar.questTemp.SharkGoldFleet == "buyincar")
			{
				link.l1 = "El hecho es que voy a ir a Portobello cualquier día de estos con un cargamento de mercancías compradas a usted en la colonia. Pensé: tal vez tenga algún tipo de carga o negocio que pueda hacer en el camino... Por una tarifa, por supuesto.";
				link.l1.go = "SharkGoldFleet";
			}
			if (pchar.questTemp.SharkGoldFleet == "LightVar")
			{
				if (!bImCasual)
					pchar.quest.SharkGoldFleetToCPO10.over = "yes";
				link.l1 = "Hola de nuevo. Entregué tu carta a Portobello. Allí me pidieron que te diera una respuesta.";
				link.l1.go = "SharkGoldFleet_09";
			}
			if (pchar.questTemp.SharkGoldFleet == "DifficultVar")
			{
				if (!bImCasual)
					pchar.quest.SharkGoldFleetToCPO10.over = "yes";
				link.l1 = "Hola. He venido a usted desde Portobello. Su colega de la autoridad portuaria me pidió que le entregara esta carta.";
				link.l1.go = "SharkGoldFleet_13";
			}
		}
		//<-- на пару с Акулой
		break;

	// belamour на пару с Акулой -->
	case "SharkGoldFleet":
		if (CheckAttribute(pchar, "questTemp.SharkGoldFleet.Fail21"))
		{
			pchar.questTemp.SharkGoldFleet = "toCurierDie";
			AddQuestRecord("SharkGoldFleet", "5");
			SGF_CreateCurierInWorld("");
			dialog.text = "Gracias por tu preocupación, pero no tengo tales casos. De hecho, había un encargo, pero llegaste literalmente un par de días tarde: envié un lugre mensajero de alta velocidad para este propósito.";
			link.l1 = "Entendido... Bueno, gracias por eso.";
			link.l1.go = "exit";
		}
		else
		{
			if (!bImCasual)
				pchar.quest.SharkGoldFleet21.over = "yes";
			if (!bImCasual)
				pchar.quest.SharkGoldFleet30.over = "yes";
			if (GetCompanionQuantity(pchar) > 1)
			{
				pchar.questTemp.SharkGoldFleet = "toCurierWait";
				AddQuestRecord("SharkGoldFleet", "10");
				SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1 + rand(2), false);
				dialog.text = "Veo que no tienes ni un solo barco. Debes ser un comerciante rico. Hmm... Pero conozco a todos los comerciantes locales con escuadrones de vista, pero a ti no te conozco. Así que no me culpes, pero no puedo confiarte nada serio.";
				link.l1 = "Entendido... Bueno, gracias por eso.";
				link.l1.go = "exit";
			}
			else
			{
				if (sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
				{
					pchar.questTemp.SharkGoldFleet = "toCurierWait";
					AddQuestRecord("SharkGoldFleet", "11");
					SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1 + rand(2), false);
					dialog.text = "Mm... Tengo una tarea. Solo que ahora tu barco no encaja. Necesito un barco que sea rápido y poderoso al mismo tiempo, y el tuyo no cumple completamente con estos requisitos. Al menos al mismo tiempo. Así que, por favor, perdóname.";
					link.l1 = "Entendido... Bueno, gracias por eso.";
					link.l1.go = "exit";
				}
				else
				{
					if (!CheckAttribute(pchar, "questTemp.SharkGoldFleet.LicenceOk"))
					{
						pchar.questTemp.SharkGoldFleet = "toCurierWait";
						AddQuestRecord("SharkGoldFleet", "12");
						SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1 + rand(2), false);
						dialog.text = "Tengo algo que hacer... Y tú tienes un buen barco. Solo que no parece un mercante. Y, por lo que puedo ver, no tienes una licencia a largo plazo de la Compañía Holandesa de las Indias Occidentales. No te ofendas, pero no pareces un mercante. No puedo correr ese riesgo.";
						link.l1 = "Entendido... Bueno, gracias por eso.";
						link.l1.go = "exit";
					}
					else
					{
						if (pchar.questTemp.SharkGoldFleet != "toCarPortOffice" || GetSquadronGoods(pchar, GOOD_COFFEE) < 300 || GetSquadronGoods(pchar, GOOD_CHOCOLATE) < 300)
						{
							pchar.questTemp.SharkGoldFleet = "toCurierWait";
							AddQuestRecord("SharkGoldFleet", "13");
							SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1 + rand(2), false);
							dialog.text = "Tengo algo que hacer... Y tienes un buen barco. Solo que ahora no entiendo con qué vas a comerciar... Dijiste que ibas a Portobello a vender las mercancías, pero, hasta donde yo sé, no las compraste de nosotros en la colonia. No te ofendas, pero no pareces un comerciante. No puedo correr ese riesgo.";
							link.l1 = "Entendido... Pues, gracias por eso.";
							link.l1.go = "exit";
						}
						else
						{
							dialog.text = "Tengo algo que hacer. Claro, no te conozco... Pero, a decir verdad, solo recuerdo a los mercaderes con escuadrones a su nombre. El resto no. Sí, y tienes una licencia a largo plazo, se nota de inmediato que eres un mercader experimentado. Sin embargo, tu barco es interesante. ¿Por qué comerciarías en una fragata?";
							link.l1 = "¡Ja, este no es un bergantín ordinario! Puede alcanzar una velocidad muy alta incluso con la bodega llena. Siempre es más fácil escapar de los piratas que luchar contra ellos, ¿verdad? Aunque mi embarcación tiene una capacidad menor que las naves mercantes comunes, el riesgo es mucho menor.";
							link.l1.go = "SharkGoldFleet_01";
						}
					}
				}
			}
		}
		break;

	case "SharkGoldFleet_01":
		dialog.text = "Hmm, ¡pero tienes razón! Los españoles saben construir barcos, ¿no es así? Sí, sí, inmediatamente vi que este hermoso había salido de los astilleros. Y sí, hoy me dijeron que compraste un lote de café y cacao de nuestro comerciante para revender en Portobello. Buen negocio, te digo. La gente no familiarizada con el comercio no sabe que estos productos son baratos aquí, gracias a las plantaciones, y en Portobello tienen gran demanda, ya que desde allí van a la metrópoli.";
		link.l1 = "Bueno, de eso se trata todo, señor. Por unos pocos pesos, no llevaría mi barco tan lejos.";
		link.l1.go = "SharkGoldFleet_02";
		break;

	case "SharkGoldFleet_02":
		dialog.text = "Bueno, para decirte la verdad, sí tengo un negocio para ti. Y es muy bueno que tengas un barco tan rápido, que además pueda defenderse en caso de emergencia.";
		link.l1 = "Espera, señor... ¿Tu caso sugiere que tengo que luchar...?";
		link.l1.go = "SharkGoldFleet_03";
		break;

	case "SharkGoldFleet_03":
		dialog.text = "¡No, no! De hecho, mi tarea es lo más simple posible. Necesito que entregues una carta a la Autoridad Portuaria en Portobello. La carta está sellada y no puede ser abierta. Tampoco hay necesidad de hablar de ella, correspondencia... personal. Entrégala personalmente. El plazo es de diez días. Después será irrelevante.";
		link.l1 = "¿Tan simple? ¿Y cuánto recibiré por ello?";
		link.l1.go = "SharkGoldFleet_04";
		break;

	case "SharkGoldFleet_04":
		dialog.text = "Cinco mil pesos. Considéralo por no tener que enviar un lugre de mensajería a Portobello.";
		link.l1 = "¿Y cuáles eran tus preguntas sobre mí y mi barco?";
		link.l1.go = "SharkGoldFleet_05";
		break;

	case "SharkGoldFleet_05":
		dialog.text = "Olvídalo. Es solo que la correspondencia es lo suficientemente importante, y debo estar seguro de que llegará al destinatario. Y así, nada especial. Burocracia... Para una persona ordinaria, estos documentos no tienen interés.";
		link.l1 = "Bueno, de acuerdo. Vamos a conseguir tus papeles aquí. Tan pronto como llegue a Portobello, se los llevaré a tu colega. Lo haré en diez días, no te preocupes.";
		link.l1.go = "SharkGoldFleet_06";
		break;

	case "SharkGoldFleet_06":
		dialog.text = "Un segundo. Lo siento, he olvidado completamente tu nombre. ¿Puedes decírmelo, por favor? Necesito anotarlo en los documentos.";
		link.l1 = "Mi nombre es Andreas García.";
		link.l1.go = "SharkGoldFleet_07";
		break;

	case "SharkGoldFleet_07":
		dialog.text = "Gracias. Entonces...  Estupendo. Recuerda que eres tú quien debe entregar este documento y directamente en las manos del destinatario. Aquí tienes. La recompensa te la dará el jefe de la Autoridad Portuaria en Portobello. ¡Buen viaje!";
		link.l1 = "¡Gracias! Ahora, discúlpeme.";
		link.l1.go = "SharkGoldFleet_08";
		break;

	case "SharkGoldFleet_08":
		DialogExit();
		if (!bImCasual)
			SetFunctionTimerCondition("SharkGoldFleetToPB10", 0, 0, 10, false);
		else
			NewGameTip("Exploration mode: el temporizador está desactivado.");
		AddCharacterSkillDontClearExp(pchar, SKILL_LEADERSHIP, 1);
		AddCharacterSkillDontClearExp(pchar, SKILL_SNEAK, 1);
		TakeNItems(pchar, "letter_1", 1);
		ChangeItemDescribe("letter_1", "itmdescr_letter_SharkGoldFleet_1");
		AddQuestRecord("SharkGoldFleet", "14");
		pchar.questTemp.SharkGoldFleet = "toPBPortOffice";
		break;

	case "SharkGoldFleet_09":
		RemoveItems(PChar, "letter_2", 1);
		ChangeItemDescribe("letter_2", "itmdescr_letter_2");
		dialog.text = "¡Estupendo! Me ayudaste mucho. ¿Hubo alguna dificultad?";
		link.l1 = "No, no hubo dificultades. Es cierto, tu colega te maldijo: dijo que todos ustedes son unos tacaños aquí, porque no están enviando un barco mensajero, sino comerciantes de paso, e incluso colgando el pago al destinatario. Amenazó con que escribiría una queja a La Habana...";
		link.l1.go = "SharkGoldFleet_10";
		break;

	case "SharkGoldFleet_10":
		dialog.text = "¡¿Qué?! ¿Soy yo el cascarrabias?! ¿Qué se cree que es? ¡Primero, quédese con sus cinco... no, seis mil pesos! ¡Estoy llorando honestamente!";
		link.l1 = "Gracias. Es agradable ver que tu colega estaba equivocado en su opinión sobre ti.";
		link.l1.go = "SharkGoldFleet_11";
		break;

	case "SharkGoldFleet_11":
		AddMoneyToCharacter(pchar, 6000);
		dialog.text = "Y en segundo lugar, ¡este sinvergüenza parece haber olvidado cómo hace dos meses me cargó todos los gastos del mantenimiento de un barco mercante que fue de Caracas a Portobello, y de allí a La Habana! ¡Y acordamos que él pagaría por la segunda parte del viaje! ¡Y nunca devolvió la deuda, pero prometió que liquidaría todo el mes pasado! ¡Y todavía soy un avaro... Sí, yo mismo escribiré una queja contra él a La Habana!";
		link.l1 = "Bueno, tienes las pasiones del astillero de Madrid, por supuesto...";
		link.l1.go = "SharkGoldFleet_12";
		break;

	case "SharkGoldFleet_12":
		AddQuestRecord("SharkGoldFleet", "20");
		AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date)
			pchar.questTemp.SharkGoldFleet = "LightVarToShark";
		SetFunctionLocationCondition("SharkGoldFleetToShark", "Curacao", false);
		dialog.text = "No, pensándolo bien ... ¡Qué insolente! Bien, trataré con él de nuevo ... Y ahora te pido disculpas: tengo asuntos urgentes por delante. ¡Fue un placer hacer negocios contigo!";
		link.l1 = "¡Y buena suerte para usted!";
		link.l1.go = "exit";
		break;

	case "SharkGoldFleet_13":
		RemoveItems(PChar, "letter_2", 1);
		ChangeItemDescribe("letter_2", "itmdescr_letter_2");
		dialog.text = "¡Estupendo! Me ayudaste mucho. Aunque envié un lugre mensajero a ellos, y me devolvieron la respuesta con un barco de paso. Sí... Y después de eso aún se quejan de que aquí tenemos tacaños sentados.";
		link.l1 = "Bueno, tal vez se ahorraron el dinero para el mensajero ...";
		link.l1.go = "SharkGoldFleet_14";
		break;

	case "SharkGoldFleet_14":
		AddMoneyToCharacter(pchar, 5000);
		AddQuestRecord("SharkGoldFleet", "20");
		AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date)
			pchar.questTemp.SharkGoldFleet = "DifficultVarToShark";
		SetFunctionLocationCondition("SharkGoldFleetToShark", "Curacao", false);
		dialog.text = "¡No 'quizás', sino definitivamente, te lo digo! Bien, no importa. Aquí, toma tu trabajo. Y ahora tengo mucho trabajo, discúlpame.";
		link.l1 = "Bueno, tal vez se ahorraron el dinero para el mensajero ...";
		link.l1.go = "exit";
		break;
		// <-- на пару с Акулой
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
