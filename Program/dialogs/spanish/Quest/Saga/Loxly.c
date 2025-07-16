// Альберт Локсли - адвокат
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
	string sTemp, attrLoc;

	attrLoc = Dialog.CurrentNode;
	int iSumm = 0;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	if (findsubstr(attrLoc, "RelationTo_", 0) != -1)
	{
		i = findsubstr(attrLoc, "_", 0);
		npchar.quest.relation = strcut(attrLoc, i + 1, strlen(attrLoc) - 1); // индех в конце
		// проверка на уже договор
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		if (CheckAttribute(Pchar, "GenQuest." + attrLoc) && sti(Pchar.GenQuest.(attrLoc)) == true)
		{
			Dialog.CurrentNode = "RelationYet";
		}
		else
		{
			Dialog.CurrentNode = "RelationAny_Done";
			npchar.quest.relation.summ = CalculateRelationLoyerSum(sti(npchar.quest.relation));
		}
	}

	switch (Dialog.CurrentNode)
	{
	case "First time":
		if (npchar.quest.meeting == "0")
		{
			dialog.text = "Mi nombre es Albert Loxley y soy abogado. Presento los intereses de mi cliente en los juicios. Mis servicios son caros, pero valen la pena, se lo puedo asegurar.";
			if (SandBoxMode)
			{
				if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
				{
					link.l1 = "Estoy en problemas con las autoridades inglesas.";
					link.l1.go = "RelationTo_0";
				}

				if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
				{
					link.l2 = "Estoy en problemas con las autoridades francesas.";
					link.l2.go = "RelationTo_1";
				}
				if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
				{
					link.l3 = "Estoy en problemas con las autoridades españolas.";
					link.l3.go = "RelationTo_2";
				}

				if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
				{
					link.l4 = "Estoy en problemas con las autoridades holandesas.";
					link.l4.go = "RelationTo_3";
				}
				if (ChangeContrabandRelation(pchar, 0) <= 5)
				{
					Link.l5 = "Tuve una disputa con los contrabandistas.";
					Link.l5.go = "contraband";
				}
				Link.l7 = "Gracias, pero, afortunadamente, no necesito los servicios de un abogado hasta ahora.";
				Link.l7.go = "exit";
				NextDiag.TempNode = "Loxly";
				npchar.quest.meeting = "1";
			}
			link.l1 = "Gracias pero, afortunadamente, no necesito los servicios de un abogado por ahora.";
			link.l1.go = "exit";
			npchar.quest.meeting = "1";
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "loxly")
			{
				link.l1 = "Necesito tus servicios. Soy un delegado autorizado de una joven llamada Helen McArthur, ella es la nieta del famoso Nicolas Sharp. Es la única heredera legal que queda tras la muerte de su madre y su tío. Tiene todos los derechos sobre Isla Tesoro según el testamento de su tío. ¿Cuánto pedirías por ayudar a Helen a convertirse en la legítima dueña de la isla?";
				link.l1.go = "saga";
			}
		}
		else
		{
			if (CheckAttribute(pchar, "questTemp.Saga"))
			{
				if (pchar.questTemp.Saga == "loxly") // первое обращение по саге
				{
					dialog.text = "¿Necesita mis servicios, señor? Quedará satisfecho, se lo aseguro.";
					link.l1 = "Sí, los necesito. Soy un delegado autorizado de una joven llamada Helen McArthur, ella es la nieta del famoso Nicolas Sharp. Ella es la única heredera legítima que queda tras la muerte de su madre y su tío. Ella tiene todos los derechos sobre Isla Tesoro según el testamento de su tío. ¿Cuánto pedirías por ayudar a Helen a convertirse en la legítima dueña de la isla?";
					link.l1.go = "saga";
					break;
				}
				if (pchar.questTemp.Saga == "bakaut")
				{
					dialog.text = "Señor, aún no estoy familiarizado con los materiales de su negocio. Por favor, venga a verme más tarde, como ya le he dicho.";
					link.l1 = "Bien.";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.Saga == "molligan" || pchar.questTemp.Saga == "sellbakaut")
				{ // если не выполнил до конца квест по бакауту
					dialog.text = "Señor, desafortunadamente, necesito más tiempo para reunir todos los documentos necesarios en los archivos. No estoy listo aún. Por favor, véame más tarde.";
					link.l1 = "Bien.";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.Saga == "removebakaut") // с бакаутом разобрались
				{
					// четвертая проверка времени
					if (CheckAttribute(pchar, "questTemp.Saga.Late"))
					{
						RemoveItems(pchar, "map_sharp_full", 1);
						dialog.text = "¡Señor, ¿por qué ha estado trabajando tan lentamente?! Todo ha terminado para su principal. El periodo de validación del testamento ha expirado y ahora Isla Tesoro pertenece a Inglaterra. Pronto se convertirá en una base militar." link.l1 = "¡Vaya! Parece que todos mis esfuerzos fueron en vano...";
						link.l1.go = "saga_l3";
					}
					else
					{
						dialog.text = "Ah, aquí estás, señor. Me he familiarizado con los materiales, así que es hora de un pago adelantado. ¿Has traído los doblones contigo?";
						if (CheckAttribute(pchar, "questTemp.Mtraxx.Cartahena.Gold"))
						{
							n = 1000;
						}
						else
						{
							n = 450;
						}
						if (PCharDublonsTotal() >= n)
						{
							link.l1 = "Sí, los tengo. Aquí están tus doblones.";
							link.l1.go = "saga_5";
						}
						else
						{
							link.l1 = "Perdón por mi mala memoria, los he dejado en un cofre en mi barco. Los traeré de inmediato.";
							link.l1.go = "exit";
						}
					}
					break;
				}
				if (pchar.questTemp.Saga == "shadow")
				{
					// пятая проверка времени
					if (CheckAttribute(pchar, "questTemp.Saga.Late"))
					{
						dialog.text = "¡Señor, ¿por qué ha estado trabajando tan lentamente?! Todo ha terminado para su principal. El período de validación del testamento ha expirado y la Isla Tesoro ahora pertenece a Inglaterra. Pronto se convertirá en una base militar." link.l1 = "¡Vaya! Parece que todos mis esfuerzos fueron en vano...";
						link.l1.go = "saga_l3";
					}
					else
					{
						dialog.text = "Señor, ¿pudo encontrar algo que pueda probar la ascendencia de su principal?";
						if (!CheckCharacterItem(pchar, "Letter_beatriss"))
						{
							link.l1 = "Todavía no. Pero estoy trabajando en ello.";
							link.l1.go = "exit";
						}
						else
						{
							link.l1 = "Sí. Realmente tengo pruebas exhaustivas.";
							link.l1.go = "saga_14";
						}
					}
					break;
				}
				if (pchar.questTemp.Saga == "court" && GetNpcQuestPastDayParam(npchar, "court_date") >= 1 && IsOfficer(characterFromId("Helena")))
				{
					// запрет сохранения чтобы ленку не заграбастали себе умники всякие с ГК-  лесник
					InterfaceStates.Buttons.Save.enable = false; // запретить сохраняться
					dialog.text = "Ah, aquí estás, señor. Me alegra verte. Debo admitir que te he estado esperando por bastante tiempo. ¿Es este tu principal?";
					link.l1 = "Sí. Permíteme presentarte a Helen McArthur.";
					link.l1.go = "saga_26";
					break;
				}
				dialog.text = "¿Necesita mis servicios, señor? Quedará satisfecho, se lo aseguro.";
				link.l1 = "Gracias, pero no los necesito por ahora.";
				link.l1.go = "exit";
			}
			if (CheckAttribute(npchar, "quest.waitgold"))
			{
				dialog.text = "Buen día, señor. ¿Supongo que ha traído mi pago?";
				if (PCharDublonsTotal() >= 450)
				{
					link.l1 = "Sí, lo tengo. Aquí están tus doblones.";
					link.l1.go = "saga_36";
				}
				link.l2 = "Sabes, señor Loxley, pensé... Mi punto es que 900 doblones son más que suficientes para tu trabajo.";
				link.l2.go = "saga_38";
				link.l3 = "Recuerdo, señor Loxley. Lo traeré un poco más tarde...";
				link.l3.go = "exit";
				break;
			}
			dialog.text = "¿Necesita mis servicios, señor? Quedará satisfecho, se lo aseguro.";
			link.l1 = "Gracias, pero no los necesito por ahora.";
			link.l1.go = "exit";
		}
		NextDiag.TempNode = "First time";
		break;

	case "saga":
		// третья проверка времени. Отбираем Элен, чистим квестовый лут, даем флаг на Свенсона, вызываем перемены
		if (CheckAttribute(pchar, "questTemp.Saga.Late"))
		{
			RemoveItems(pchar, "map_sharp_full", 1);
			dialog.text = "Señor, debéis haber estado en el mar demasiado tiempo. ¡Isla Tesoro es ahora una base militar de la Armada Inglesa! Sí, el testamento de Sharp existe, pero ha expirado e Isla Tesoro se ha convertido en propiedad de la corona inglesa. ¡Ay!" link.l1 = "¡Vaya! Parece que todos mis esfuerzos fueron en vano...";
			link.l1.go = "saga_l3";
		}
		else
		{
			dialog.text = "¿La dama afirma ser dueña de toda la isla? Hm... Parece que no será un asunto fácil. Isla Tesoro ya es casi una colonia inglesa...";
			link.l1 = "Aún no. Según el testamento, el hombre o la mujer que muestre ambas partes del mapa se convertirá en el dueño de la Isla Tesoro. Tenemos ambas partes del mapa de Sharp, que es la principal prueba de herencia.";
			link.l1.go = "saga_1";
		}
		break;

	case "saga_1":
		dialog.text = "Nicolas Sharp... Bueno, bueno. Necesito visitar un archivo y familiarizarme con los materiales pertinentes a Isla Tesoro. ¿Tienes el mapa contigo?";
		link.l1 = "Tengo, pero te lo daré solo después de que firmemos un contrato. Entonces, ¿qué hay del precio por tus servicios?";
		link.l1.go = "saga_2";
		break;

	case "saga_2":
		sTemp = "";
		if (CheckAttribute(pchar, "questTemp.Mtraxx.Cartahena.Gold"))
			sTemp = " Su estimada participación tampoco pasará desapercibida. Cartagena... Habrá preguntas.";
		dialog.text = "Como dije, no será fácil. Necesitas demostrar el derecho de propiedad de toda una isla, no de un viejo cascarón o una choza. Además, Nicolas Sharp era un pirata y ayudar a piratas o a sus familiares es costoso." + sTemp;
		link.l1 = "¿Vas a decirme una cifra real?";
		link.l1.go = "saga_3";
		break;

	case "saga_3":
		sTemp = "cuatrocientos cincuenta";
		if (CheckAttribute(pchar, "questTemp.Mtraxx.Cartahena.Gold"))
			sTemp = "mil";
		dialog.text = "Señor, la suma final se formará durante el juicio. Todavía no sé qué tan problemático será. Pero estoy listo para estimar un adelanto, " + sTemp + " doblones. Esta cantidad de oro tendrá que ser pagada nuevamente una o dos veces, dependiendo de cómo vaya nuestro negocio.\nTráeme el dinero en una semana, necesito tiempo para revisar los archivos y prepararme. Luego haremos un arreglo. ¿Trato?";
		link.l1 = "Te han recomendado como el mejor abogado del archipiélago, así que tenemos un trato. ¡Nos vemos en una semana!";
		link.l1.go = "saga_4";
		break;

	case "saga_4":
		DialogExit();
		pchar.questTemp.Saga = "bakaut"; // обновляем флаг
		AddQuestRecord("Testament", "2");
		if (CheckAttribute(pchar, "questTemp.Mtraxx.Cartahena.Gold"))
			AddQuestUserData("Testament", "sMoney", "1000");
		else
			AddQuestUserData("Testament", "sMoney", "450");

		if (pchar.questTemp.HelenDrinking.Result != "no_visit")
		{
			bDisableFastReload = true;
			SetFunctionLocationCondition("HelenDrinking_PortRoyalDialog", "PortRoyal_town", false);
		}
		break;

	case "saga_5":
		if (CheckAttribute(pchar, "questTemp.Mtraxx.Cartahena.Gold"))
		{
			RemoveDublonsFromPCharTotal(1000);
			// Log_Info("Has entregado 1450 doblones");
		}
		else
		{
			RemoveDublonsFromPCharTotal(450);
			// Log_Info("Has entregado 450 doblones");
		}
		PlaySound("interface\important_item.wav");
		dialog.text = "Muy bien. Estoy listo para tomar tu caso y representar tus intereses en el tribunal. Ahora vamos al grano. Me fue bien en los archivos y hablé con personas importantes. El caso del legado de Sharp no va a ser fácil. Es bueno que hayas adquirido ambas piezas del mapa. Pero esto podría no ser suficiente.\nEl coronel Doyle tiene grandes planes para Isla Tesoro, ya que no logró tomar el control de Tortuga. Tiene defensas naturales y podría servir como una base militar futura en esta área.";
		link.l1 = "¡Pero Helen tiene todos los derechos sobre la isla según la ley de Inglaterra!";
		link.l1.go = "saga_6";
		break;

	case "saga_6":
		dialog.text = "No sabes quizás que el difunto Sharp hizo una adición a su testamento. Un heredero o herederos deben tener su apellido. Y por lo que recuerdo, tu chica tiene un apellido diferente. Dijiste que era McArthur, ¿verdad?";
		link.l1 = "Este es el apellido de su padrastro, pero Helen tiene todo el derecho de llevar Sharp como su apellido, porque es hija de la difunta Beatrice Sharp, la hija de Nicolas.";
		link.l1.go = "saga_7";
		break;

	case "saga_7":
		dialog.text = "¡Espléndido! Pero, ¿quién puede confirmar eso bajo juramento? ¿Los padres adoptivos de Helen conocían a Beatrice Sharp?";
		link.l1 = "Por lo que entiendo, entonces no lo eran. El señor McArthur la consideraba hija de Gladys y Gladys solo conocía al padre de la niña.";
		link.l1.go = "saga_8";
		break;

	case "saga_8":
		dialog.text = "Eso es una lástima. Verá, no he encontrado ninguna mención en los archivos de que Beatrice Sharp haya tenido descendencia alguna vez. Existe la posibilidad de que no haya ninguna nota oficial sobre el nacimiento del niño en absoluto. Cualquiera puede llamarse a sí mismo nieto de Sharp y reclamar el derecho a llevar su apellido.";
		link.l1 = "¡Pero solo Helen tiene el mapa completo!";
		link.l1.go = "saga_9";
		break;

	case "saga_9":
		dialog.text = "Esta es su carta de triunfo y tal vez sería suficiente si las autoridades locales no tuvieran sus propios planes para Isla Tesoro. Un documento con la letra de Beatrice y su firma está en los archivos. Necesitamos encontrar algún documento escrito por ella que demuestre el hecho del nacimiento de su hija, la hija que fue entregada a esa Gladys... eh, ¿cuál era su apellido?";
		link.l1 = "Chandler. Gladys Chandler de Belice.";
		link.l1.go = "saga_10";
		break;

	case "saga_10":
		dialog.text = "Exactamente. ¿Tienes la oportunidad de encontrar algo así?";
		link.l1 = "Dudo de ello. Han pasado demasiados años. Según la leyenda, el capitán Butcher podría ser el padre de Helen. Quizás, el ex-verdugo de San Juan pueda contarnos algo sobre esto. Fue el último hombre que vio a su padre con vida.";
		link.l1.go = "saga_11";
		break;

	case "saga_11":
		dialog.text = "Mm. Realmente era un hombre entretenido. Hasta donde recuerdo, su nombre era Raymond Baker. Tuve la suerte de charlar con él una vez. Es un hombre inteligente y bien educado. Bueno, intenta encontrar algo en Antigua y yo continuaré mis búsquedas en los archivos, quizás encuentre algo útil.";
		link.l1 = "Bien. Me sirve.";
		link.l1.go = "saga_12";
		break;

	case "saga_12":
		dialog.text = "Dame el mapa de Sharp y date prisa, habla con Baker, tal vez puedas encontrar algunos documentos con su ayuda. Incluso podrías encontrar pruebas de su nacimiento.";
		link.l1 = "Eh, ojalá pudiera. Está bien, nos vemos, señor Loxley.";
		link.l1.go = "saga_13";
		break;

	case "saga_13":
		DialogExit();
		RemoveItems(pchar, "map_sharp_full", 1);
		pchar.questTemp.Saga = "shadow";
		pchar.questTemp.Saga.Shadows = "sentjons";
		AddQuestRecord("Shadows", "1");
		break;

	case "saga_14":
		dialog.text = "¿Es así? Vamos a echar un vistazo a esta evidencia.";
		link.l1 = "Esta es una carta privada escrita por Beatrice Sharp a su hermano. Aquí se dice que dio a luz a una hija y que su padre era, de hecho, Lawrence Beltrope. La niña fue enviada a una joven viuda llamada Gladys Chandler. Lawrence Beltrope también es conocido como el capitán Butcher. Aquí, toma la carta...";
		link.l1.go = "saga_15";
		break;

	case "saga_15":
		RemoveItems(pchar, "Letter_beatriss", 1);
		dialog.text = "";
		link.l1 = "Gladys está lista para confirmarlo bajo juramento. También está lista para confirmar que el padre se presentó como el capitán Butcher.";
		link.l1.go = "saga_16";
		break;

	case "saga_16":
		if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) // Белтроп убит
		{
			dialog.text = "¡Espera un minuto! ¡El Capitán Butcher, el malvado pirata y asesino de súbditos ingleses fue ahorcado en el fuerte de St. John's hace veinte años! Y Lawrence Beltrope, un amigo cercano de Richard Doyle, murió trágicamente no hace mucho. ¡Y lo más importante, Doyle quería hacerle el nuevo gobernador de Sharptown!";
			link.l1 = "¡Ja! Claro, nadie sabe eso... Tengo un testimonio escrito de Raymond Baker, el ex verdugo de St. John's, de que fue obligado bajo amenaza de muerte segura a fingir la ejecución de Butcher. Aquí, echa un vistazo...";
			link.l1.go = "saga_17";
		}
		else
		{
			dialog.text = "¡Espera un minuto! El Capitán Butcher, el malvado pirata y asesino de súbditos ingleses, fue colgado en el fuerte de San Juan hace veinte años. Y Lawrence Beltrope está vivo y vive en una de las mejores mansiones de Port Royal. ¡Y lo más importante, Doyle quiere hacerle el nuevo gobernador de Sharptown!";
			link.l1 = "¡Ja! Claro, nadie sabe eso... Tengo un testimonio escrito de Raymond Baker, el ex verdugo de St. John's, que fue obligado bajo amenaza de muerte a fingir la ejecución de Butcher. Aquí, échale un vistazo...";
			link.l1.go = "saga_17";
		}
		break;

	case "saga_17":
		RemoveItems(pchar, "letter_baker", 1);
		dialog.text = "Mm. Bueno, bueno...";
		link.l1 = "¿No es eso muy hábil? El Capitán Butcher logró mantenerse con vida y regresó a Inglaterra. Cambió su nombre de nuevo a Lawrence Beltrope y ha regresado aquí sin ser notado.";
		if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die"))
			link.l1.go = "saga_18";
		else
			link.l1.go = "saga_22";
		break;

	case "saga_18":
		dialog.text = "¡Pero esto... Esto lo cambia todo! ¡Publicar la carta de Beatrice mostrará que todo este tiempo el gobernador militar ha estado ocultando al pirata fugitivo Butcher, quien debería haber sido arrestado al instante y quien debería haber comparecido ante el tribunal por sus crímenes pasados!\n¡Y el testimonio de Baker destruirá por completo cualquier razón en contra de eso! ¡Esto es magnífico! ¡Con tal as bajo la manga venceremos a Doyle de manera justa y cuadrada!";
		link.l1 = "Me alegra. Confío en ti en esta prueba. También, dime, ¿cómo murió Lawrence Beltrope?";
		link.l1.go = "saga_19";
		break;

	case "saga_19":
		dialog.text = "Esta es una historia espeluznante, señor. Fue encontrado en su propio dormitorio con el rostro torcido. Es demasiado difícil imaginar qué pudo haber asustado tanto a este hombre intrépido. Dicen que estaba cubierto de escarcha. Su cuerpo estaba lleno de heridas desgarradas, de aspecto aterrador, ¡pero ni una sola gota de sangre en el suelo! ¡Imagínate! ¡Ni una sola gota!";
		link.l1 = "Sí, eso parece sacado de una pesadilla. Parece que fue asesinado... Pero ¿quién podría haber hecho eso?";
		link.l1.go = "saga_20";
		break;

	case "saga_20":
		dialog.text = "Es desconocido. Está demasiado enredado... El médico de la guarnición dijo que sus heridas no eran letales. Beltrope murió de miedo, dolor o algo más. De todos modos, esta es una muerte mística.";
		link.l1 = "Ya veo... ¿Y cuándo comenzará el juicio?";
		link.l1.go = "saga_21";
		break;

	case "saga_21":
		dialog.text = "Todo depende de usted, señor. Presentaré todos los documentos ante el tribunal tan pronto como me pague la segunda parte de mi tarifa - 450 doblones. Helen obtendrá sus derechos una semana después de eso.";
		if (PCharDublonsTotal() >= 450)
		{
			link.l1 = "Muy bien. Aquí están tus doblones.";
			link.l1.go = "saga_24";
		}
		else
		{
			link.l1 = "Sí, seguro. Te traeré la suma que necesitas.";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_23";
		}
		break;

	case "saga_23":
		// шестая проверка времени
		if (CheckAttribute(pchar, "questTemp.Saga.Late"))
		{
			dialog.text = "¡Señor, me ha dejado estupefacto! Ha hecho tanto, la isla estaba casi en nuestras manos, ¡pero ahora todo ha terminado por su demora con mi pago! El testamento expiró y ahora Isla Tesoro pertenece a la corona inglesa. Será una base militar." link.l1 = "¡Vaya! Parece que todos mis esfuerzos fueron en vano...";
			link.l1.go = "saga_l3";
		}
		else
		{
			dialog.text = "¿Ha traído la segunda parte de mi honorario, señor?";
			if (PCharDublonsTotal() >= 450)
			{
				link.l1 = "Sí, claro. Aquí están tus doblones.";
				link.l1.go = "saga_24";
			}
			else
			{
				link.l1 = "Disculpad mi mala memoria, los he dejado en un cofre en mi barco. Los traeré enseguida.";
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_23";
			}
		}
		break;

	case "saga_22":
		dialog.text = "¡Pero esto... esto lo cambia todo! ¡Publicar la carta de Beatrice significará que Lawrence Beltrope debe ser arrestado inmediatamente y comparecer en el tribunal por sus crímenes pasados!\n¡Y el testimonio de Baker destruirá por completo cualquier razón en contra de eso! ¡Esto es grandioso! ¡Con tal as en la manga venceremos a Doyle de manera justa y cuadrada!";
		link.l1 = "Estoy muy contento. ¿Cuándo comenzará el juicio?";
		link.l1.go = "saga_21";
		break;

	case "saga_24":
		RemoveDublonsFromPCharTotal(450);
		// Log_Info("Has entregado 450 doblones");
		PlaySound("interface\important_item.wav");
		dialog.text = "Excelente, señor. Un placer hacer negocios con usted. Ahora, aquí está el trato. Vuelva aquí mañana. Sí, sí, ha oído bien, ¡mañana! Después de todo, soy el mejor abogado del archipiélago y tengo conexiones.\nTraiga a su principal, el juicio no ocurrirá sin ella. No llegue tarde y no salga de la ciudad. Y lleve la última parte del pago si puede, estoy completamente seguro de nuestra victoria.";
		link.l1 = "Bien. Estaremos en su oficina mañana, señor Loxley.";
		link.l1.go = "saga_25";
		break;

	case "saga_25":
		DialogExit();
		SaveCurrentNpcQuestDateParam(npchar, "court_date");
		pchar.questTemp.Saga = "court"; // обновляем флаг
		AddQuestRecord("Testament", "10");
		NextDiag.CurrentNode = "First time";
		// закрываем выходы из города
		LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", true);
		// LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", true);// лесник там нет этого пирса
		LocatorReloadEnterDisable("PortRoyal_town", "gate_back", true);
		// pchar.GenQuest.CannotWait = true;//запрет ожидания
		//  снимаем общий таймер Саги!
		pchar.quest.Saga_TimeOver.over = "yes";
		break;

	case "saga_26":
		dialog.text = "¿MacArthur? ¡No, es Sharp! Bueno, sígueme ahora.";
		link.l1 = "...";
		link.l1.go = "saga_27";
		break;

	case "saga_27":
		DialogExit();
		ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto10");
		LAi_SetActorType(npchar);
		LAi_SetActorType(pchar);
		sld = characterFromId("Helena");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(npchar, "reload", "reload1", "Saga_CourtGo", -1);
		LAi_ActorFollow(pchar, npchar, "", -1);
		LAi_ActorFollow(sld, npchar, "", -1);
		NextDiag.CurrentNode = "saga_28";
		// открываем выходы из города
		// LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник рано
		// LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", false);
		// LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false);
		DeleteAttribute(pchar, "GenQuest.CannotWait"); // можно мотать время
		break;

	case "saga_28":
		dialog.text = "Permítame felicitarle, señor, y a su principal. Ella es ahora la legítima gobernante de Isla Tesoro. ¡Vale la pena brindar con champán por esto!";
		link.l1 = "Absolutamente, señor Loxley. Su discurso fue excelentísimo. Pensé que el coronel Doyle sufriría un ataque al corazón cuando usted dijo al tribunal que Lawrence Beltrop es el capitán Butcher.";
		link.l1.go = "saga_29";
		break;

	case "saga_29":
		dialog.text = "Sí, el señor Doyle tendrá que despedirse de su sueño de una base militar en Isla Tesoro. ¿Y qué puede hacer? La ley es la ley y está escrita para todos, incluso para el respetado coronel.";
		if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die"))
		{
			link.l1 = "¿Todos los documentos están en orden y confirman el derecho de Helen a la isla?";
			link.l1.go = "saga_30";
		}
		else
		{
			link.l1 = "He oído que el juez ha ordenado el arresto de Lawrence Beltrop. ¿Supongo que lo van a colgar?";
			link.l1.go = "saga_34";
		}
		break;

	case "saga_30":
		dialog.text = "Claro, señor. He revisado cada coma en ellos. Puedes estar seguro de que están bien.";
		link.l1 = "Muy bien...";
		link.l1.go = "saga_31";
		break;

	case "saga_31":
		dialog.text = "Bueno, mi trabajo está hecho. El caso fue complicado, pero lo hemos ganado juntos. Ahora, Señor, sólo tiene que pagarme la última parte de mi honorario. Sin presión, me doy cuenta de que debe estar ocupado. Pero creo que encontrará tiempo para traerme los últimos 450 doblones dentro de una semana.\nAdemás, un cliente como usted siempre puede contar con descuentos sustanciales. Puedo ayudarle mucho, tengo conexiones en todas las capitales del archipiélago, incluso en las hostiles, así que cualquier problema legal que encuentre puede ser resuelto.";
		link.l1 = "Excelente. Ahora sé a quién preguntar.";
		link.l1.go = "saga_32";
		break;

	case "saga_32":
		dialog.text = "Te garantizo un resultado positivo incluso en las situaciones más difíciles.";
		link.l1 = "Bien. Debo irme ahora, Helen y yo tenemos mucho que hacer.";
		link.l1.go = "saga_33";
		break;

	case "saga_33":
		dialog.text = "Adiós, señor.";
		link.l1 = "Adiós, señor Loxley.";
		link.l1.go = "saga_35";
		break;

	case "saga_34":
		dialog.text = "Supongo que sí, él es el capitán Butcher, un pirata y bandido. Aunque ahora no está en Port Royal. Tuvo la suerte de partir, adentrándose en la isla. Pero la caza ha comenzado y seguro que será atrapado.";
		link.l1 = "Ya veo... ¿Están los documentos en orden?";
		link.l1.go = "saga_30";
		break;

	case "saga_35":
		DialogExit();
		SetFunctionTimerCondition("Saga_RemainGoldLoxly", 0, 0, 10, false); // таймер на оплату услуг
		DoQuestReloadToLocation("PortRoyal_town", "quest", "quest3", "Saga_HelenaIslaTesoro");
		npchar.quest.waitgold = "true";
		pchar.questTemp.Saga = "lastpages";
		NextDiag.CurrentNode = "First time";
		break;

	case "saga_36":
		RemoveDublonsFromPCharTotal(450);
		// Log_Info("Has entregado 450 doblones");
		PlaySound("interface\important_item.wav");
		dialog.text = "¡Espléndido! ¡Fue un placer hacer negocios con usted, señor! Ahora puede solicitar mi ayuda en cualquier asunto y recibir un descuento. Problemas con la ley, recompensa por su cabeza... Bienvenido. Siempre me alegrará verle.";
		link.l1 = "Sería mejor si me mantengo alejado de los problemas, pero... las cosas pasan. Gracias y adiós, señor Loxley.";
		link.l1.go = "saga_37";
		break;

	case "saga_37":
		DialogExit();
		pchar.quest.Saga_RemainGoldLoxly.over = "yes"; // снять таймер
		NextDiag.CurrentNode = "Loxly";				   // услуги адвоката
		break;

	case "saga_38":
		dialog.text = "¿Qué quiere decir, señor? ¿Va a incumplir los términos de nuestro acuerdo?";
		link.l1 = "Exactamente. Yo hice la mayor parte del trabajo. No puedes ni imaginar lo que tuve que hacer para conseguir las pruebas. Y tú solo tomaste esos papeles y fuiste al tribunal. Novecientos doblones son más que suficientes, estoy seguro de eso.";
		link.l1.go = "saga_39";
		break;

	case "saga_39":
		dialog.text = "¡Hablas como un pirata, señor! Bueno, no me empobreceré perdiendo cuatrocientos cincuenta doblones, pero tú tampoco te enriquecerás. De hecho, ¡acabas de perder mucho más! Y quizás pierdas algo en el futuro... ¡Sal de mi casa inmediatamente y no vuelvas a mostrarte aquí jamás!";
		link.l1 = "Y voy a hacer eso. Adiós, señor Loxley.";
		link.l1.go = "exit";
		NextDiag.TempNode = "saga_40";
		pchar.quest.Saga_RemainGoldLoxly.over = "yes";				   // снять таймер
		LocatorReloadEnterDisable("PortRoyal_town", "houseSp4", true); // закроем вход к Локсли
		ChangeCharacterNationReputation(pchar, ENGLAND, -10);
		break;

	case "saga_40":
		dialog.text = "No quiero hablar contigo. ¡Lárgate o llamaré a los guardias!";
		link.l1 = "... ";
		link.l1.go = "exit";
		NextDiag.TempNode = "saga_40";
		break;

	// провалы Саги
	case "saga_l3":
		dialog.text = "Señor, habríamos ganado su caso si hubiera venido a verme antes. El testamento ha expirado. Lo siento.";
		link.l1 = "¡Eh, lo lamento aún más! Bueno, adiós, señor Loxley.";
		link.l1.go = "saga_l3_1";
		// Элен - к разговору
		sld = characterFromId("Helena");
		sld.quest.talk = "late_l3";
		break;

	case "saga_l3_1":
		DialogExit();
		pchar.quest.Saga_Late_3.win_condition.l1 = "Location_Type";
		pchar.quest.Saga_Late_3.win_condition.l1.location_type = "town";
		pchar.quest.Saga_Late_3.function = "Saga_HelenaTalk";
		Saga_ChangesIslatesoro();		  // вызов перестановки на Исла-Тесоро
		pchar.questTemp.Saga = "late_l3"; // для Свенсона
		break;

		//-------------------------------------- адвокатские услуги ------------------------------------------------
	case "Loxly":
		dialog.text = TimeGreeting() + ", señor. Me alegra verlo. ¿Necesita mis servicios?";
		link.l1 = "Sí. Por eso estoy aquí.";
		link.l1.go = "loxly_1";
		link.l2 = "No, afortunadamente no los necesito en este momento. Solo quería saludarte.";
		link.l2.go = "exit";
		NextDiag.TempNode = "Loxly";
		break;

	case "loxly_1":
		dialog.text = "Estoy listo para escucharte. ¿Qué tipo de ayuda necesitas?";
		if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
		{
			link.l1 = "Estoy en problemas con las autoridades inglesas.";
			link.l1.go = "RelationTo_0";
		}

		if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
		{
			link.l2 = "Estoy en problemas con las autoridades francesas.";
			link.l2.go = "RelationTo_1";
		}
		if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
		{
			link.l3 = "Estoy en problemas con las autoridades españolas.";
			link.l3.go = "RelationTo_2";
		}

		if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
		{
			link.l4 = "Estoy en problemas con las autoridades holandesas.";
			link.l4.go = "RelationTo_3";
		}
		if (ChangeContrabandRelation(pchar, 0) <= 5)
		{
			Link.l5 = "Me peleé con los contrabandistas.";
			Link.l5.go = "contraband";
		}
		Link.l7 = "Lo siento, he cambiado de opinión...";
		Link.l7.go = "exit";
		NextDiag.TempNode = "Loxly";
		break;

	case "RelationYet": // уже оплачено
		dialog.text = "Ya estoy trabajando en tu asunto. Todo estará bien, te lo aseguro.";
		Link.l1 = "Gracias. Estaré esperando.";
		Link.l1.go = "exit";
		NextDiag.TempNode = "Loxly";
		break;

	// --> снятие НЗГ
	case "RelationAny_Done":
		iSumm = sti(npchar.quest.relation.summ);
		int iRate = abs(ChangeCharacterNationReputation(pchar, sti(npchar.quest.relation), 0));
		if (iRate <= 10)
			sTemp = "Bueno, yo no llamaría a eso problemas. Sólo un pequeño problema. Arreglaré el asunto enseguida";
		if (iRate > 10 && iRate <= 30)
			sTemp = "Sí, su reputación está ligeramente deteriorada, pero no veo nada crítico. Voy a resolver el asunto de inmediato";
		if (iRate > 30 && iRate <= 60)
			sTemp = "Sí, te equivocaste de camino con las autoridades. No será fácil, pero estoy seguro de que podré resolver sus desacuerdos sin problemas.";
		if (iRate > 60 && iRate <= 90)
			sTemp = "¿Y cómo lo ha hecho, señor? Tus problemas no son sólo graves, son realmente graves. Las autoridades están muy ansiosas por atraparte. Tendré que poner mucho empeño en solucionar tus desavenencias";
		if (iRate > 90)
			sTemp = "Bueno... La situación es catastrófica, se afirma que el enemigo más acérrimo. Será difícil, pero soy el mejor abogado en el Caribe después de todo, así que voy a resolver sus desacuerdos";
		dialog.text = "" + sTemp + " con " + XI_ConvertString(Nations[sti(npchar.quest.relation)].Name + "Abl") + ". Te costará " + FindRussianMoneyString(iSumm) + ".";
		if (sti(pchar.money) >= iSumm)
		{
			link.l1 = "Muy bien, señor Loxley, estoy de acuerdo. Aquí está su dinero y trate de resolver las cosas lo antes posible.";
			link.l1.go = "relation";
		}
		link.l2 = "¡No tengo la suma que estás pidiendo ahora mismo. Volveré más tarde!";
		link.l2.go = "exit";
		NextDiag.TempNode = "Loxly";
		break;

	case "relation":
		dialog.text = "Un placer hacer negocios con usted, señor. Puede respirar libremente de nuevo, su problema desaparecerá en las próximas dos semanas. Por favor, evite cualquier confrontación con " + XI_ConvertString(Nations[sti(npchar.quest.relation)].Name + "Abl") + ", mientras estoy en medio de negociaciones.";
		link.l1 = "Bien, consideraré tu advertencia. ¡Gracias y adiós!";
		link.l1.go = "exit";
		AddMoneyToCharacter(pchar, -sti(npchar.quest.relation.summ));
		ChangeNationRelationFromRelationAgent(npchar);
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		Pchar.GenQuest.(attrLoc) = true;
		Pchar.GenQuest.(attrLoc).loyer = "true";
		NextDiag.TempNode = "Loxly";
		break;
		// <-- снятие НЗГ

	case "contraband":
		npchar.quest.contrasum = makeint(0.3 * stf(Pchar.rank) / stf(Pchar.reputation.nobility) * 60000);
		dialog.Text = "¿Y por qué has hecho eso? Los contrabandistas son buenos muchachos, son honestos a su manera. Todos necesitamos vivir y comer... Está bien, no es gran cosa y solo te costará " + FindRussianMoneyString(sti(npchar.quest.contrasum)) + ".";
		if (sti(Pchar.money) >= sti(npchar.quest.contrasum))
		{
			Link.l1 = "Muy bien, señor Loxley, estoy de acuerdo. Aquí está su dinero y trate de resolver las cosas lo antes posible.";
			Link.l1.go = "Contraband_Agreed";
		}
		Link.l2 = "Ahora mismo no tengo la suma que estás pidiendo. ¡Volveré más tarde!";
		Link.l2.go = "exit";
		break;

	case "Contraband_Agreed":
		dialog.Text = "Excelente, resolveré tu problema. Pronto querrán hacer negocios contigo nuevamente.";
		Link.l1 = "¡Gracias!";
		Link.l1.go = "exit";
		ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
		AddMoneyToCharacter(pchar, -sti(npchar.quest.contrasum));
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
