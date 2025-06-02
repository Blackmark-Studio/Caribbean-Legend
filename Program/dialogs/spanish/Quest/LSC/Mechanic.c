// Хенрик Ведекер. Он же Механик.
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
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

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		if (npchar.quest.meeting == "0")
		{
			dialog.text = "Buen día, señor. Nunca lo he visto antes. ¿Es usted un recién llegado? ¿Y es la primera vez que decide visitar esta plataforma?";
			link.l1 = TimeGreeting() + ". Mi nombre es " + GetFullName(pchar) + "Soy un recién llegado aquí y solo estoy mirando, conociendo a la gente...";
			link.l1.go = "meeting";
			npchar.quest.meeting = "1";
		}
		else
		{
			if (pchar.questTemp.LSC == "platinum_wait")
			{
				dialog.text = "Escucha, " + pchar.name + ", si sigues distrayéndome nunca terminaré las reparaciones.";
				link.l1 = "Sí, sí, recuerdo eso. ¡Lamento molestarte!";
				link.l1.go = "exit";
				break;
			}
			// возвращение блудного скафандра
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "¡Ah! ¡Mira eso! ¡El ahogado ha regresado del otro mundo! Ahora dime, ¿cómo pudiste hacer tal truco? Han realizado un funeral para ti y te han enterrado en tu ausencia, por si no lo sabías...";
				link.l1 = "Lástima, no voy a morir todavía. El truco es simple: solo toqué el ídolo de Kukulcán en el fondo. Me teletransportó a Dominica, justo al pueblo de los Caribes...";
				link.l1.go = "return";
				break;
			}

			dialog.text = "Ah, " + GetFullName(pchar) + ". ¡" + TimeGreeting() + "!";
			// квестовые ветки
			if (pchar.questTemp.LSC == "mechanic")
			{
				link.l4 = "Henrik, tengo un negocio para ti. Un negocio muy importante. Ole Christiansen me ha hablado de ti. También lo llaman el Chico Blanco.";
				link.l4.go = "mechanic_1";
			}
			if (pchar.questTemp.LSC == "platinum" && GetCharacterItem(pchar, "jewelry10") >= 11)
			{
				link.l4 = "Henrik, te he traído suficiente cantidad de 'plata'. Exactamente como pediste: uno de los tuyos más diez piezas extra. Aquí, tómalo.";
				link.l4.go = "mechanic_15";
			}
			if (pchar.questTemp.LSC == "underwater_check")
			{
				link.l4 = "Yo de nuevo, Henrik. ¿Cómo está tu traje? ¿Pudiste repararlo?";
				link.l4.go = "mechanic_20";
			}
			if (pchar.questTemp.LSC == "platinum_add_wait" && GetCharacterItem(pchar, "jewelry10") >= sti(pchar.questTemp.LSC.PtAddQty))
			{
				link.l4 = "Tengo suficiente metal, el que pediste. Tómalo.";
				link.l4.go = "mechanic_23";
			}
			if (pchar.questTemp.LSC == "underwater_prepare")
			{
				link.l4 = "Buen día, Henrik. Entonces, ¿el traje está listo para una inmersión?";
				link.l4.go = "immersion";
			}
			if (pchar.questTemp.LSC == "underwater_natan" && CheckAttribute(pchar, "questTemp.LSC.NatanTalk"))
			{
				link.l4 = "Se acabó, he resuelto mis problemas y estoy listo para bucear. ¿Cuándo empezamos?";
				link.l4.go = "immersion_1";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.UW_ready"))
			{
				link.l5 = "Hola, Henrik. Entonces, ¿el traje está listo para un buceo?";
				link.l5.go = "immersion_next";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.UW_end") && CheckCharacterItem(pchar, "underwater"))
			{
				link.l5 = "Quiero devolver tu traje.";
				link.l5.go = "immersion_next_2";
			}
			// квестовые ветки
			link.l1 = LinkRandPhrase("¿Tienes algo interesante que decir?", "¿Ha sucedido algo nuevo en la isla?", "¿Me contarás los últimos cotilleos?");
			link.l1.go = "rumours_LSC";
			link.l3 = "Solo quería saber cómo estás.";
			link.l3.go = "exit";
		}
		NextDiag.TempNode = "First time";
		break;

	case "meeting": // первая встреча
		dialog.text = "Y yo soy Henrik Vedecker. Aunque, la mayoría de los lugareños me conocen como el Mecánico y en realidad es una definición muy cierta.";
		if (pchar.questTemp.LSC == "mechanic")
		{
			link.l1 = "¿Eres el Henrik Vedecker? ¡Encantado de conocerte! Te estaba buscando.";
			link.l1.go = "mechanic";
		}
		else
		{
			link.l1 = "Debes ser el comodín de todos los oficios, ¿verdad?";
			link.l1.go = "meeting_1";
		}
		NextDiag.TempNode = "First time";
		break;

	case "meeting_1":
		dialog.text = "Oh, sí, los Narvales realmente aprecian mis habilidades. Mis herramientas les permiten obtener muchos objetos valiosos de los barcos perdidos del anillo exterior, para que puedan comprar provisiones del almirante Dodson\nDe hecho, la ciencia y las exploraciones son mi pasión. Por lo tanto, me disculpo si no puedo dedicarte suficiente tiempo - mis experimentos ocupan casi todo.";
		link.l1 = "Ya veo. No voy a molestarte sin razón, señor Vedecker, te lo aseguro. ¡Me alegra mucho conocerte!";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "mechanic":
		dialog.text = "¿Lo fuiste? ¿Y por qué?";
		link.l1 = "Ole Christiansen me ha hablado de ti. También lo llaman el Chico Blanco.";
		link.l1.go = "mechanic_1";
		break;

	case "mechanic_1":
		dialog.text = "¡Ah, ese tipo gracioso! Sí, sí, lo conozco. ¿Y qué te dijo?";
		link.l1 = "Lo siento si mi próxima pregunta suena estúpida, pero... te la haré de todos modos. Ole me dijo que podrías enseñarme a bucear hasta el fondo, bajo el agua. No te rías de mí, por favor, si solo es su imaginación.";
		link.l1.go = "mechanic_2";
		break;

	case "mechanic_2":
		dialog.text = "Es cierto. Yo mismo he estado en el fondo varias veces. Aunque ya no me sumerjo, el banco está plagado de cangrejos gigantes hoy en día y, seguramente, como puedes ver, no soy capaz de luchar contra ellos, soy un científico, no puedo luchar contra esas cosas.\nAdemás, también hubo otros dos hombres, dos Narvales, que solían bucear, pero finalmente dejaron de hacerlo: saquear las bodegas de los barcos del anillo exterior resultó ser más seguro que bucear en un lugar infestado de cangrejos gigantes.\nAhora usan mi equipo raramente, ni una sola inmersión en los últimos meses debido a la fractura del traje...";
		link.l1 = "¿Realmente tienes un traje con el que puedas bucear hasta el fondo? ¿Te he escuchado mal?";
		link.l1.go = "mechanic_3";
		break;

	case "mechanic_3":
		dialog.text = "Tus oídos están en el lugar correcto, joven. He inventado y confeccionado el traje yo mismo. Está hecho de lona gruesa completamente impermeable, partes metálicas y un casco de acero forjado por mí y Jurgen en su herrería\nTambién reforcé el traje con una placa de metal en el pecho, rodilleras, piezas de pecho y botas para una mejor protección contra los cangrejos y peso extra\nTanques especiales, llenos de aire a presión, proporcionan función de soporte vital y la capacidad de pasar un tiempo bajo el agua. El traje es único, y estoy bastante orgulloso de él.";
		link.l1 = "Eso es espléndido. Pero, ¿mencionaste que el traje está dañado?";
		link.l1.go = "mechanic_4";
		break;

	case "mechanic_4":
		dialog.text = "Desafortunadamente, así es. Varias partes del traje estaban conectadas por placas de metal para lograr flexibilidad y protección adicional, pero el agua del mar las afectó gravemente. Las placas se oxidaron por años de uso y han perdido sus habilidades de protección contra el agua. \nEs bueno que me haya dado cuenta del daño y haya evitado que la gente muriera. Incluso el traje seco contenía algo de sal y agua, habían terminado su nefasto trabajo por completo.";
		link.l1 = "Bueno... ¡Pero puedes reparar el traje! Puedes reemplazar las piezas viejas y oxidadas por las nuevas... ¿Verdad?";
		link.l1.go = "mechanic_5";
		break;

	case "mechanic_5":
		dialog.text = "¿Para qué propósito? ¿Para reemplazarlos de nuevo un año después? ¿Sabes lo difícil que es este trabajo? ¿Componer el traje con juntas flexibles y hacerlo impermeable? Es al menos una semana de trabajo sin descanso.";
		link.l1 = "¿Y esa es la razón por la cual estás dispuesto a desechar tu invento?";
		link.l1.go = "mechanic_6";
		break;

	case "mechanic_6":
		dialog.text = "No, por supuesto que no. Tengo una idea. Necesito hacer las juntas de un metal que no pueda ser destruido por el agua y la sal. Y sé qué metal puede ayudar...";
		link.l1 = "¿Entonces cuál es el problema?";
		link.l1.go = "mechanic_7";
		break;

	case "mechanic_7":
		dialog.text = "El problema es que este metal es muy raro. Solo tengo una pieza, lo cual ciertamente no es suficiente. Necesito al menos diez piezas más o incluso quince.";
		link.l1 = "¿Y de qué metal... estás hablando?";
		link.l1.go = "mechanic_8";
		break;

	case "mechanic_8":
		dialog.text = "¡Oh, este es un metal único, realmente subestimado por muchos. Tiene alta durabilidad, plasticidad y es absolutamente inmune a la exposición: ni el agua ni la sal pueden dañarlo! \nQuizás ya hayas visto el metal antes. Es blanco, parece plata, ¡por eso los españoles lo llamaron 'plata'. ¡Ja! ¡Es cien veces mejor que la plata! ¡Incluso mejor que el oro! Algún día lo entenderán, pero el momento adecuado aún no ha llegado.";
		link.l1 = "Escucha, ¿por qué no puedes usar otros tipos de metal en su lugar? ¿Por qué no usas oro para hacer esas placas? Nunca he oído que el oro pueda oxidarse o arruinarse.";
		link.l1.go = "mechanic_9";
		break;

	case "mechanic_9":
		dialog.text = "Tienes una mente flexible y vivaz, joven. Es bueno saberlo. Desafortunadamente, tu propuesta no funcionará. La idea del oro fue lo primero que se me ocurrió. Pero el oro es demasiado blando para unir diferentes partes del traje. \nAy, el platino es el único material que servirá. Fabricaré las piezas solo con él, aunque me lleve años reunir suficiente. Pero he visto piezas de este metal antes en la Isla; a menudo se mezcla con plata debido a su apariencia.";
		link.l1 = "Hum. Y si te ayudo a encontrar suficiente de esta... 'plata', ¿me prestarás el traje para que pueda bucear bajo el agua?";
		link.l1.go = "mechanic_10";
		break;

	case "mechanic_10":
		dialog.text = "¡No hace falta preguntar! Claro que sí. Ya te he dicho que no me sumergiría allí por los cangrejos y nadie más quiere hacerlo tampoco.";
		link.l1 = "Entonces muéstrame este trozo de metal para ayudarme a entender lo que necesito encontrar.";
		link.l1.go = "mechanic_11";
		break;

	case "mechanic_11":
		dialog.text = "¿Así que vas a buscarlo? Excelente. Aquí, toma este pedazo como ejemplo. Búscalo entre el mineral de plata y las pepitas. No será fácil encontrarlo, pero lo manejarás. Hay pequeñas oscuridades en la plata, pero nuestro metal es claro y mucho más duro que la plata. La forma más fácil de probarlo sería rascar la moneda de plata sobre él, si la moneda se daña, entonces lo has encontrado.";
		link.l1 = "Bien. Voy a buscarlo de inmediato. ¿Tienes alguna sugerencia de dónde debería buscarlo?";
		link.l1.go = "mechanic_12";
		break;

	case "mechanic_12":
		GiveItem2Character(pchar, "jewelry10");
		PlaySound("interface\important_item.wav");
		Log_Info("Has recibido un lingote de platino");
		dialog.text = "Lamentablemente, no lo sé. Si supiera dónde encontrarlo, lo haría yo mismo. Pero puedo darte un consejo. Busca en los barcos de los Rivados. No los visito, así que es muy probable que ellos lo tengan.";
		link.l1 = "Lo consideraré, Henrik. Espero tener suerte.";
		link.l1.go = "mechanic_13";
		break;

	case "mechanic_13":
		dialog.text = "Recoge diez piezas más. Es el mínimo para reparar el traje. ¡Buena suerte!";
		link.l1 = "Gracias. ¡Adiós, Mecánico!";
		link.l1.go = "mechanic_14";
		break;

	case "mechanic_14":
		DialogExit();
		pchar.questTemp.LSC = "platinum";
		AddQuestRecord("LSC", "7");
		if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) >= 65 || rand(2) == 1)
			pchar.questTemp.LSC.PtAddQty = 0;
		else
			pchar.questTemp.LSC.PtAddQty = rand(4);
		break;

	case "mechanic_15":
		RemoveItems(pchar, "jewelry10", 11);
		dialog.text = "Bueno, bueno, muéstrame... ¡Excelente! ¡Bien hecho, joven! ¿Fue difícil?";
		link.l1 = "No realmente...";
		link.l1.go = "mechanic_16";
		break;

	case "mechanic_16":
		dialog.text = "Bueno, ahora puedo comenzar las reparaciones. No desperdiciaré el tiempo y empezaré mañana. Estás muy ansioso por bucear, ¿verdad?";
		link.l1 = "En efecto. Realmente quiero explorar el mundo submarino.";
		link.l1.go = "mechanic_17";
		break;

	case "mechanic_17":
		dialog.text = "Eso es muy bueno, porque tendré una petición para ti cuando organicemos tu inmersión. Pero hablaremos de eso más tarde. Ven a verme en cinco días, espero haber terminado las reparaciones.";
		link.l1 = "Está bien. ¡Te deseo suerte!";
		link.l1.go = "mechanic_18";
		break;

	case "mechanic_18":
		dialog.text = "La suerte es necesaria, sin duda, pero la reparación del traje requerirá principalmente habilidades. Además, necesitaré pasar un día cerca del horno con Jurgen para hacer placas con el metal que me has traído.";
		link.l1 = "Entonces no te molestaré. Nos vemos en cinco días. ¡Adiós!";
		link.l1.go = "mechanic_19";
		break;

	case "mechanic_19":
		DialogExit();
		pchar.questTemp.LSC = "platinum_wait";
		AddQuestRecord("LSC", "8");
		SetFunctionTimerCondition("LSC_PrepareUnderwater_Check", 0, 0, 5, false); // таймер
		AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;

	case "mechanic_20":
		if (sti(pchar.questTemp.LSC.PtAddQty) == 0)
		{
			dialog.text = "Sí. Jurgen y yo hicimos un trabajo infernal y la cantidad de piezas que trajiste fue suficiente para hacerlo. El traje está reparado y preparado. Solo necesito realizar varias pruebas, pero estoy seguro de que está bien. Ven mañana a las 10 a.m. - Llenaré los tanques con aire y podrás hacer lo que quieras.";
			link.l1 = "¡Excelente! Espero con ansias hacerlo. ¡Nos vemos mañana, Henrik!";
			link.l1.go = "mechanic_24";
			DeleteAttribute(pchar, "questTemp.LSC.PtAddQty");
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		}
		else
		{
			dialog.text = "Tengo que decepcionarte, " + pchar.name + " . Como suponía, no hay suficiente metal. Necesito " + FindRussianQtyString(sti(pchar.questTemp.LSC.PtAddQty)) + " más piezas para terminar la reparación. Tengo que pedirte ayuda de nuevo.";
			link.l1 = "Bueno, no esperaba tal giro de los acontecimientos. Está bien, intentaré encontrar las pepitas que te faltan.";
			link.l1.go = "mechanic_21";
		}
		break;

	case "mechanic_21":
		dialog.text = "Te esperaré. Puedes estar seguro de que esta cantidad seguramente será suficiente. Solo tráelos y terminaré el trabajo en un día.";
		link.l1 = "Eso espero... ¡Nos vemos!";
		link.l1.go = "mechanic_22";
		break;

	case "mechanic_22":
		DialogExit();
		pchar.questTemp.LSC = "platinum_add_wait";
		AddQuestRecord("LSC", "9");
		AddQuestUserData("LSC", "sQty", FindRussianQtyString(sti(pchar.questTemp.LSC.PtAddQty)));
		break;

	case "mechanic_23":
		RemoveItems(pchar, "jewelry10", sti(pchar.questTemp.LSC.PtAddQty));
		dialog.text = "¡Espléndido! Ahora el traje será restaurado. Solo necesito realizar varias pruebas, pero estoy seguro de que está bien. Ven mañana a las 10 a.m. - Llenaré los tanques con aire y podrás hacer lo que quieras.";
		link.l1 = "¡Excelente! Espero hacerlo. ¡Nos vemos mañana, Henrik!";
		link.l1.go = "mechanic_24";
		break;

	case "mechanic_24":
		DialogExit();
		if (CheckAttribute(pchar, "questTemp.LSC.PtAddQty"))
		{
			iTemp = 2;
			sTemp = "pasado mañana";
			DeleteAttribute(pchar, "pchar.questTemp.LSC.PtAddQty");
		}
		else
		{
			iTemp = 1;
			sTemp = "mañana";
		}
		if (!CheckAttribute(pchar, "questTemp.LSC.NatanTalk"))
			string sText = "Pero tengo que encontrar a Nathaniel Hawk antes de sumergirme..."; // не было разговора с Натаном
		else
			sText = "";
		AddQuestRecord("LSC", "10");
		AddQuestUserData("LSC", "sText1", sTemp);
		AddQuestUserData("LSC", "sText2", sText);
		pchar.quest.LSC_prepunderwater.win_condition.l1 = "Timer";
		pchar.quest.LSC_prepunderwater.win_condition.l1.date.hour = 10;
		pchar.quest.LSC_prepunderwater.win_condition.l1.date.day = GetAddingDataDay(0, 0, iTemp);
		pchar.quest.LSC_prepunderwater.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
		pchar.quest.LSC_prepunderwater.win_condition.l1.date.year = GetAddingDataYear(0, 0, iTemp);
		pchar.quest.LSC_prepunderwater.function = "LSC_PrepareUnderwater";
		pchar.questTemp.LSC = "wait";
		break;

	case "immersion":
		dialog.text = "Sí, el traje está listo y lleno de aire. Puedes bucear.";
		if (!CheckAttribute(pchar, "questTemp.LSC.NatanTalk")) // не было разговора с Натаном
		{
			link.l1 = "Bueno. Pero no puedo bucear ahora, necesito resolver un problema sobre mi... amigo, Nathan Hawk. No puedo encontrarlo. ¿Puede esperar el traje un poco?";
			link.l1.go = "natan";
		}
		else
		{
			link.l1 = "¡Espléndido! ¿Cuándo empezamos? ¿Ahora?";
			link.l1.go = "immersion_1";
		}
		break;

	case "natan":
		dialog.text = "Claro. Puede esperar. ¿No estarás buscando a tu amigo durante un año?";
		link.l1 = "Claro, no lo haré. Quizás lo encuentre incluso hoy. Te visitaré justo después de terminar mis asuntos con él.";
		link.l1.go = "natan_1";
		break;

	case "natan_1":
		dialog.text = "Sí, por favor. Ven cuando estés listo para bucear.";
		link.l1 = "¡Gracias!";
		link.l1.go = "exit";
		pchar.questTemp.LSC = "underwater_natan";
		break;

	case "immersion_1":
		dialog.text = "Ahora mismo si quieres. Pero déjame darte una pequeña instrucción primero. Comenzarás tu inmersión desde la plataforma 'Phoenix', puedes llegar allí desde la popa del San Gabriel. Hay un elevador que te llevará al fondo y de regreso. Esta es la única forma de volver\nAsí que será mejor que recuerdes la ubicación del elevador bajo el agua y no te pierdas. Los tanques del traje tienen suficiente aire para veinte minutos de inmersión. Vigila tu tiempo o te asfixiarás\nNo te alejes demasiado del elevador o no podrás regresar a tiempo y que Dios te salve de dejar nuestro bajío - te aplastarán como a un lenguado\nTen cuidado y vigila los cangrejos. Si te acercas demasiado, te atacarán. No arriesgues si no tienes que hacerlo, no podrás matar a todo un grupo de ellos y huir rápidamente no es una opción allá abajo.";
		link.l1 = "Me encargaré de los cangrejos. Yo me ocupo del resto. No te sumerjas más profundo, no te alejes mucho del cabrestante y no olvides el tiempo. ¿Cuándo puedo sumergirme?";
		link.l1.go = "immersion_2";
		break;

	case "immersion_2":
		dialog.text = "Cuando quieras, pero solo de 7 a.m. a 9 p.m. No podrás ver nada en la oscuridad.";
		link.l1 = "Entendido.";
		link.l1.go = "immersion_4";
		break;

	case "immersion_4":
		dialog.text = "Así es. Toma el traje de la habitación en la plataforma. Quítatelo después de una inmersión y tráemelo. Lo llenaré de aire de nuevo. Pero no intentes bucear más de una vez al día, incluso los 20 minutos de buceo y respiración de aire comprimido son malos para tu salud.";
		link.l1 = "Bueno, entonces no me sumergiré más de una vez al día.";
		link.l1.go = "immersion_5";
		break;

	case "immersion_5":
		dialog.text = "Me alegra que lo entiendas. ¡Ahora ve y buena suerte!";
		link.l1 = "¡Gracias!";
		link.l1.go = "immersion_6";
		break;

	case "immersion_6":
		DialogExit();
		pchar.questTemp.LSC = "first_immersion"; // флаг на первое погружение
		pchar.questTemp.LSC.immersion = "true";	 // погружение возможно
		pchar.quest.LSC_takeUnderwater.win_condition.l1 = "locator";
		pchar.quest.LSC_takeUnderwater.win_condition.l1.location = "FenixPlatform";
		pchar.quest.LSC_takeUnderwater.win_condition.l1.locator_group = "item";
		pchar.quest.LSC_takeUnderwater.win_condition.l1.locator = "armor";
		pchar.quest.LSC_takeUnderwater.function = "LSC_takeUnderwater"; // выдача костюма
		pchar.quest.LSC_UnderwaterDolly.win_condition.l1 = "locator";
		pchar.quest.LSC_UnderwaterDolly.win_condition.l1.location = "Underwater";
		pchar.quest.LSC_UnderwaterDolly.win_condition.l1.locator_group = "quest";
		pchar.quest.LSC_UnderwaterDolly.win_condition.l1.locator = "dolly";
		pchar.quest.LSC_UnderwaterDolly.function = "LSC_FindUnderwaterDolly"; // нашли статую
		NextDiag.CurrentNode = "after_first_immersion";						  // нода после первого погружения
		AddQuestRecord("LSC", "11");
		QuestPointerToLoc("UnderWater", "quest", "dolly");
		break;

	case "after_first_immersion":
		if (CheckAttribute(pchar, "questTemp.LSC.immersion"))
		{
			dialog.text = "Entonces, ¿por qué sigues aquí? El traje te está esperando.";
			link.l1 = "Sí, sí. Estoy en camino.";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "Entonces, ¿cómo fue la primera inmersión?";
			if (CheckAttribute(pchar, "questTemp.LSC.FindDolly"))
			{
				link.l1 = "Excelente y estoy satisfecho con los resultados. He encontrado un ídolo de piedra en el galeón hundido. Escuché que los Rivados le habían hecho algunas ofrendas sacrificiales antes. Dime, Henrik, ¿conoces a alguien que pueda decirme más sobre ello?";
				link.l1.go = "af_immersion_1";
			}
			else
			{
				link.l1 = "Está bien. ¡Lo hice! Fue realmente interesante, aunque un poco emocionante.";
				link.l1.go = "af_immersion_2";
			}
		}
		NextDiag.TempNode = "after_first_immersion";
		break;

	case "af_immersion_1":
		dialog.text = "¿Te interesa nuestra historia? Ve a Antonio Betancourt. Nació aquí. Vive en el filibote Pluto. Si él no sabe nada al respecto, entonces nadie lo sabe.";
		link.l1 = "¡Excelente! Definitivamente le haré una visita.";
		link.l1.go = "af_immersion_2";
		pchar.questTemp.LSC.Betancur = "true";
		AddQuestRecord("LSC", "14");
		break;

	case "af_immersion_2":
		dialog.text = "Deja el traje aquí. Vuelve mañana o cualquier otro día, voy a llenarlo de aire.";
		if (CheckCharacterItem(pchar, "underwater"))
		{
			link.l1 = "Claro. Aquí tienes tu traje. ¡Gracias!";
			link.l1.go = "af_immersion_3";
		}
		else
		{
			link.l1 = "Claro. ¡Lo traeré de inmediato!";
			link.l1.go = "af_immersion_wait";
		}
		break;

	case "af_immersion_wait":
		dialog.text = "Bueno, ¿me has traído mi equipo?";
		if (CheckCharacterItem(pchar, "underwater"))
		{
			link.l1 = "Claro.  Aquí tienes tu traje.  ¡Gracias!";
			link.l1.go = "af_immersion_3";
		}
		else
		{
			link.l1 = "¡Lo haré de inmediato!";
			link.l1.go = "exit";
		}
		NextDiag.TempNode = "af_immersion_wait";
		break;

	case "af_immersion_3":
		DialogExit();
		RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
		RemoveItems(pchar, "underwater", 1);
		LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false);
		SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
		NextDiag.CurrentNode = "First time";
		// даем старт мини-квестам с крабикусами
		sld = characterFromId("Carpentero");
		if (!CheckAttribute(sld, "quest.crab"))
			sld.quest.crab = "begin";
		if (GetCharacterIndex("LSC_Jacklin") != -1)
		{
			sld = characterFromId("LSC_Jacklin");
			sld.quest.crab = "true";
		}
		break;

	// блок погружений, за искл. первого
	case "immersion_next":
		if (CheckAttribute(npchar, "quest.guarantee")) // требует залог
		{
			dialog.text = "Sí, por supuesto. El traje fue probado y lleno de aire. ¿Tienes el compromiso contigo? ¿500 000 pesos?";
			if (sti(pchar.money) >= 500000)
			{
				link.l1 = "Sí, claro. Aquí, tómalo.";
				link.l1.go = "immersion_next_pay";
			}
			else
			{
				link.l1 = "¡Uy! Me he olvidado de eso. Lo traeré de inmediato...";
				link.l1.go = "exit";
			}
		}
		else
		{
			dialog.text = "Sí, claro. El traje fue probado y lleno de aire. Revisa la plataforma 'Phoenix' como siempre.";
			link.l1 = "Entonces me zambulliré. ¡Gracias!";
			link.l1.go = "immersion_next_1";
		}
		break;

	case "immersion_next_1":
		DialogExit();
		DeleteAttribute(pchar, "questTemp.LSC.UW_ready");
		LocatorReloadEnterDisable("LostShipsCity_town", "reload72", false); // открываем вход в Феникс
		pchar.questTemp.LSC.immersion = "true";								// погружение возможно
		pchar.quest.LSC_takeUnderwater.win_condition.l1 = "locator";
		pchar.quest.LSC_takeUnderwater.win_condition.l1.location = "FenixPlatform";
		pchar.quest.LSC_takeUnderwater.win_condition.l1.locator_group = "item";
		pchar.quest.LSC_takeUnderwater.win_condition.l1.locator = "armor";
		pchar.quest.LSC_takeUnderwater.function = "LSC_takeUnderwater"; // выдача костюма
		break;

	case "immersion_next_2":
		dialog.text = "Bien. Vuelve mañana o más tarde. Voy a preparar el traje.";
		link.l1 = "¡Gracias, Mecánico!";
		link.l1.go = "immersion_next_3";
		break;

	case "immersion_next_3":
		DialogExit();
		DeleteAttribute(pchar, "questTemp.LSC.UW_end");
		RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
		RemoveItems(pchar, "underwater", 1);
		if (CheckAttribute(npchar, "quest.guarantee"))
			AddMoneyToCharacter(pchar, 500000); // возврат залога
		LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false);
		SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
		break;

	case "immersion_next_pay":
		AddMoneyToCharacter(pchar, -500000);
		dialog.text = "Recibirás tu dinero de vuelta cuando devuelvas el traje. Trato justo.";
		link.l1 = "¡Gracias, Mecánico! Ahora me voy a zambullir.";
		link.l1.go = "immersion_next_1";
		break;
		// блок погружений

		//--------------------------------------вернулся на Остров---------------------------------------------
	case "return":
		dialog.text = "¡Espera un segundo, por favor! ¿Qué estatua? A-ah, ahora lo entiendo. ¿Te refieres a ese ídolo en el barco hundido 'San-Geronimo', no es así? ¿Entonces esas historias de los Rivados son ciertas?";
		link.l1 = "¡Exactamente! Y no hay cuentos. Conozco dos ídolos más en el archipiélago que teletransportan a las personas que los tocan de uno a otro, en círculo.";
		link.l1.go = "return_1";
		break;

	case "return_1":
		dialog.text = "Ya veo, ya veo. Tendré que confiar en ti, aunque tus palabras son un disparate anticientífico. Teletransportes, estatuas... ¡ja! ¿Y quién podría siquiera pensar en eso, cómo funcionan tales cosas?";
		link.l1 = "Solo confía en mí y no intentes encontrar lógica aquí. No estoy mintiendo.";
		link.l1.go = "return_2";
		break;

	case "return_2":
		dialog.text = "Está bien. Pero espero que no hayas perdido el traje durante esa teleportación tuya.";
		if (CheckCharacterItem(pchar, "underwater"))
		{
			link.l1 = "Claro, no lo hice. Me ha salvado de los caribes, por así decirlo. Aquí está.";
			link.l1.go = "return_4";
		}
		else
		{
			link.l1 = "Claro, no lo hice. Me ha salvado de los caribes, por así decirlo. Pero no lo tengo conmigo ahora.";
			link.l1.go = "return_3";
		}
		break;

	case "return_3":
		dialog.text = "¡Entonces tráemelo, maldita sea! No hablaremos hasta que me lo devuelvas, ¡sábelo!";
		link.l1 = "¡Cálmate, Mecánico! ¡Te lo devolveré!";
		link.l1.go = "exit";
		NextDiag.TempNode = "return_underwater";
		break;

	case "return_underwater":
		if (CheckCharacterItem(pchar, "underwater"))
		{
			dialog.text = "¡Ah, de hecho has traído mi traje! Gracias, ya empezaba a preocuparme por él.";
			link.l1 = "No había necesidad de preocuparse por ello. Te he prometido devolvértelo.";
			link.l1.go = "return_4";
		}
		else
		{
			dialog.text = "No te atrevas a venir aquí hasta que no tengas mi traje.";
			link.l1 = "Está bien, está bien.";
			link.l1.go = "exit";
		}
		NextDiag.TempNode = "return_underwater";
		break;

	case "return_4":
		DeleteAttribute(pchar, "questTemp.LSC.UW_end");
		RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
		RemoveItems(pchar, "underwater", 1);
		SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
		dialog.text = "Muy bien. He comenzado a pensar en hacer uno nuevo, pero sería un trabajo de al menos un año... Me alegra que hayas mostrado una buena economía y devuelto mi propiedad en una sola pieza. Incluso te daré un regalo.";
		link.l1 = "¿Hablas en serio?";
		link.l1.go = "return_5";
		break;

	case "return_5":
		dialog.text = "¡Claro que sí! Me ayudaste a reparar el traje y no lo tiraste a la primera ocasión. Lo has cuidado y finalmente me lo has devuelto. De todas formas, aquí tienes una buena caja de herramientas. Aprende a usarla. Podrás hacer muchas cosas útiles con su ayuda.";
		link.l1 = "¿Y qué más podría esperar del Mecánico? ¡Claro, la caja de herramientas! Muchas gracias, Henrik, estoy conmovido... No merecía tal regalo.";
		link.l1.go = "return_6";
		break;

	case "return_6":
		GiveItem2Character(pchar, "mechanic_tool");
		Log_Info("Has recibido una caja de herramientas");
		PlaySound("interface\important_item.wav");
		dialog.text = "Conozco mejor lo que merecías y lo que no. ¡Toma! Te será útil. Pero te daré el traje de nuevo solo si prometes 500 000 pesos debido a tu costumbre de teletransportarte mediante ídolos.";
		link.l1 = "¡Vaya! Bueno, entiendo eso... medidas de precaución...";
		link.l1.go = "return_7";
		break;

	case "return_7":
		dialog.text = "Claro. ¿Y qué si un día escapas con él? Entonces el dinero será mi compensación.";
		link.l1 = "Está bien, Henrick. Estoy de acuerdo. Para ser honesto, pensé que nunca me lo volverías a dar.";
		link.l1.go = "return_8";
		break;

	case "return_8":
		dialog.text = "No hay ninguna posibilidad. Promete medio millón y será todo tuyo.";
		link.l1 = "¡Trato hecho! ¿Puedo llevarlo como de costumbre para bucear entonces? ¿Desde mañana?";
		link.l1.go = "return_9";
		break;

	case "return_9":
		dialog.text = "Exactamente.";
		link.l1 = "¡Gracias! ¡Nos vemos, Henrik!";
		link.l1.go = "return_10";
		break;

	case "return_10":
		DialogExit();
		AddQuestRecord("LSC", "26");
		npchar.quest.return_isl = "true";
		npchar.quest.guarantee = "true"; // залог за скафандр
		NextDiag.CurrentNode = "First time";
		break;
		//----------------------------------------- специальные реакции -----------------------------------------------
		// обнаружение ГГ в сундуках
	case "Man_FackYou":
		dialog.text = LinkRandPhrase("¿Qué haces ahí, eh? ¡Ladrón!", "¡Solo mira eso! Tan pronto como me perdí en la contemplación, decidiste revisar mi cofre.", "¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!");
		link.l1 = "¡Maldita sea!";
		link.l1.go = "fight";
		break;

	case "Woman_FackYou":
		dialog.text = "¿Qué?! ¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!";
		link.l1 = "¡Chica insensata!...";
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
		dialog.text = LinkRandPhrase("Escucha, será mejor que guardes tu arma. Me pone nervioso.", "Sabes, correr con la espada no se tolera aquí. Guárdala.", "Escucha, no te hagas el caballero medieval corriendo con una espada. Guárdala, no te queda bien...");
		link.l1 = LinkRandPhrase("Bien.", "Por supuesto.", "Como dices...");
		link.l1.go = "exit";
		NextDiag.TempNode = "First Time";
		break;

	case "CitizenNotBlade":
		if (loadedLocation.type == "town")
		{
			dialog.text = NPCharSexPhrase(NPChar, "Escucha, soy ciudadano de la ciudad y te pediría que envaines tu espada.", "Escucha, soy ciudadano de la ciudad y te pediría que envaines tu espada");
			link.l1 = LinkRandPhrase("Bien.", "Claro.", "Como dices...");
		}
		else
		{
			dialog.text = NPCharSexPhrase(NPChar, "Ten cuidado, amigo, al correr con un arma. Puedo ponerme nervioso...", "No me gusta cuando la gente camina frente a mí con sus armas listas. Me asusta...");
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
