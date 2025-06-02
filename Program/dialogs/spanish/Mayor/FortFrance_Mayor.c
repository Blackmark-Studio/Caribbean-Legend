// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué quieres? Pregunta lo que desees.", "Te escucho, ¿cuál es la pregunta?"), "Es la segunda vez que intentas preguntar...", "Es la tercera vez que intentas preguntar de nuevo...", "¿Cuándo va a terminar?! ¡Soy un hombre ocupado, trabajando en los asuntos de la colonia y tú sigues intentando preguntar algo!", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "Ahora no. Lugar y momento equivocados."), "Es cierto... Pero más tarde, no ahora...", "Preguntaré... Pero un poco más tarde...", "Lo siento, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		/* //--> Бремя гасконца
		if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
		{
			link.l1 = "Monsieur, he encontrado el cadáver de un bandido en la jungla. Ha sido asesinado por los indios. Había pendientes en su cuerpo, parece que fueron traídos aquí desde Europa. ¿Quizás pertenecían a uno de los nobles de su ciudad?";
			link.l1.go = "Sharlie_junglejew";
		}
		//<-- Бремя гасконца */
		//--> Sinistra, Травля крысы
		if (CheckAttribute(pchar, "questTemp.TK_Potopil"))
		{
			link.l1 = "¡Su Excelencia, la tarea está cumplida! Sin embargo, lamento informarle que el criminal no sobrevivió al enfrentamiento, y por lo tanto no enfrentará la ejecución.";
			link.l1.go = "TK_Potopil";
		}
		if (CheckAttribute(pchar, "questTemp.TK_Plen"))
		{
			link.l1 = "¡Su Excelencia, la tarea está completa! El prisionero aguarda su destino en mi celda.";
			link.l1.go = "TK_Plen";
		}
		//<-- Травля крысы
		// Jason НСО
		if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
		{
			link.l1 = "He llegado por orden del Gobernador General Philippe de Poincy para tomar el mando de vuestra fragata armada.";
			link.l1.go = "patria";
		}
		if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < 5)
		{
			link.l1 = "Estoy listo para llevar la fragata a mi escuadrón.";
			link.l1.go = "patria_2";
		}
		// Jason Дороже золота
		if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "message")
		{
			link.l1 = "He llegado a su invitación, Monsieur...";
			link.l1.go = "goldengirl";
		}
		if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "girl_prisoner")
		{
			link.l1 = "Fue desafortunado, Monsieur";
			link.l1.go = "goldengirl_10";
		}
		// andre39966 ===> В плену великого улова.
		if (CheckAttribute(pchar, "questTemp.VPVL_Magor_Dialogue"))
		{
			link.l1 = "Excelencia, he llegado a poseer información sobre comercio ilícito que pronto tendrá lugar en estas costas. Me aventuro a decir que este asunto podría resultar digno de su atención.";
			link.l1.go = "VPVL_Magor_1";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.VPVL_GovernorDialogueAvailable"))
		{
			link.l1 = "Excelencia, vengo en busca de noticias sobre aquel navío contrabandista del que hablamos.";
			link.l1.go = "VPVL_Magor_4";
		}
		//  <=== В плену великого улова.  
	break;

	case "Sharlie_junglejew":
		dialog.text = "Vamos a ver qué tienes... ¡Increíble! ¡Es simplemente increíble, Charles! Estos son los pendientes de mi esposa. Se los regalé antes de dejar Europa y venir a las colonias. Desaparecieron hace unos meses en circunstancias misteriosas. ¡Sabía que fueron robados!\nCharles, me alegra mucho que vinieras directamente a mí y no vendieras algo que estimo tanto a los comerciantes. Te recompensaré por tu favor. Según escuché, ¿piensas comprar un barco? Ya que decidiste participar en la navegación, sin duda necesitarás un mapa de nuestro archipiélago. Aquí, tómalo. ¡Estoy seguro de que te será útil!";
		link.l1 = "¡Gracias, su Gracia!";
		link.l1.go = "Sharlie_junglejew_1";
		break;

	case "Sharlie_junglejew_1":
		DialogExit();
		PlaySound("interface\important_item.wav");
		RemoveItems(pchar, "jewelry25", 1);
		GiveItem2Character(pchar, "map_normal");
		AddQuestRecord("SharlieE", "2");
		CloseQuestHeader("SharlieE");
		DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
		if (!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
		{
			DelLandQuestMark(npchar);
		}
	break;

	//--> Sinistra, Травля крысы
	case "TK_Potopil":
		dialog.text = "Eso es desafortunado, Charles, pero debemos conformarnos con la situación actual. Aquí está tu recompensa: cinco mil pesos, después de impuestos.";
		link.l1 = "Me complace servir a Saint-Pierre y a usted personalmente. Aunque la batalla fue difícil, encontré cierto disfrute en ella.";
		link.l1.go = "TK_Potopil_3";
		link.l2 = "Fue una batalla desafiante, su Excelencia. Mi barco sufrió daños significativos. ¿Sería posible compensarme por mis pérdidas?";
		link.l2.go = "TK_Potopil_4";
		DeleteAttribute(pchar, "questTemp.TK_Potopil");
		AddCharacterExpToSkill(pchar, "Accuracy", 20);
		AddCharacterExpToSkill(pchar, "Cannons", 20);
		AddCharacterExpToSkill(pchar, "Grappling", 20);
		AddCharacterExpToSkill(pchar, "Defence", 20);

		CloseQuestHeader("TravlyaKrys");
		break;

	case "TK_Potopil_3":
		dialog.text = "¡Bravo, Charles! No tengo duda de que ascenderás mucho en nuestras filas.";
		link.l1 = "Hasta que nos volvamos a encontrar, su Excelencia.";
		link.l1.go = "exit";
		AddMoneyToCharacter(pchar, 5000);
		ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;

	case "TK_Potopil_4":
		dialog.text = "Debo decir que estoy un poco sorprendido por tu solicitud, Charles... Muy bien, considera otros dos mil pesos de mi parte personalmente como un gesto de buena voluntad. Adiós.";
		link.l1 = "Gracias, su Excelencia.";
		link.l1.go = "exit";
		AddMoneyToCharacter(pchar, 7000);
		ChangeCharacterComplexReputation(pchar, "nobility", -2);
		ChangeCharacterNationReputation(pchar, FRANCE, 2);
		break;

	case "TK_Plen":
		dialog.text = "¡Excelente, Charles! Te complacerá saber que tu éxito ayudará a tus amigos malteses en una operación delicada... Aquí tienes tu recompensa: ocho mil pesos, después de impuestos.";
		link.l1 = "Me complace servir a Saint-Pierre, a la Orden, y a usted personalmente. Aunque la pelea fue desafiante, encontré cierta satisfacción en ella.";
		link.l1.go = "TK_Plen_3";
		link.l2 = "Fue una dura batalla, su Excelencia. Mi barco sufrió daños considerables. ¿Podría solicitar compensación por mis pérdidas?";
		link.l2.go = "TK_Plen_4";
		AddCharacterExpToSkill(pchar, "Accuracy", 20);
		AddCharacterExpToSkill(pchar, "Cannons", 20);
		AddCharacterExpToSkill(pchar, "Grappling", 20);
		AddCharacterExpToSkill(pchar, "Defence", 20);
		CloseQuestHeader("TravlyaKrys");
		DeleteAttribute(pchar, "questTemp.TK_Plen");
		sld = CharacterFromID("TK_Heiter2");
		RemovePassenger(pchar, sld);
		sld.lifeday = 0;
		break;

	case "TK_Plen_3":
		dialog.text = "¡Bravo, Charles! Estoy seguro de que llegarás lejos.";
		link.l1 = "Hasta que nos volvamos a encontrar, su Excelencia";
		link.l1.go = "exit";
		AddMoneyToCharacter(pchar, 8000);
		ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;

	case "TK_Plen_4":
		dialog.text = "Supongo que te lo has ganado. Guarda otros dos mil de mí personalmente como un gesto de buena voluntad. Gracias, mi amigo.";
		link.l1 = "Gracias, su Excelencia.";
		link.l1.go = "exit";
		AddMoneyToCharacter(pchar, 10000);
		ChangeCharacterComplexReputation(pchar, "nobility", -2);
		ChangeCharacterNationReputation(pchar, FRANCE, 2);
		break;
	//<-- Травля крысы

	// Jason НСО
	case "patria":
		if (GetCompanionQuantity(pchar) > 4)
		{
			dialog.text = "La nave está lista, pero no tienes un lugar libre para ella en tu escuadrón. Capitán, reduce tu escuadrón y regresa, entonces te entregaré el bergantín de inmediato.";
			link.l1 = "Bien.";
			link.l1.go = "patria_1";
		}
		else
		{
			dialog.text = "Sí, por supuesto, el barco está listo para zarpar. Su capitán está al tanto y seguirá todas sus órdenes.";
			link.l1 = "Entonces zarpamos. Adiós, Su Gracia.";
			link.l1.go = "patria_3";
		}
		break;

	case "patria_1":
		DialogExit();
		npchar.quest.frigate.wait = "true";
		break;

	case "patria_2":
		DeleteAttribute(npchar, "quest.frigate.wait");
		dialog.text = "Excelente. Prepárate para recibir tu nuevo barco.    Su capitán está al tanto y seguirá todas tus órdenes.";
		link.l1 = "Entonces zarpamos. Adiós, Su Gracia.";
		link.l1.go = "patria_3";
		break;

	case "patria_3":
		DialogExit();
		npchar.quest.frigate = "true";
		Patria_BastionFrigateMrt(); // присоединяем фрегат
		break;

	// Jason Дороже золота
	case "goldengirl":
		dialog.text = "¡Capitán Charles de Maure, por fin!¡He estado esperando ansiosamente por usted! Por favor, entre, únase a mí.";
		link.l1 = "Buen día para usted también, Su Excelencia. Siempre hay una razón detrás de su cortesía. ¿Cuál es esta vez? ¿Piratas, españoles, caníbales pieles rojas?";
		link.l1.go = "goldengirl_1";
		break;

	case "goldengirl_1":
		dialog.text = "No te pongas irónico, Capitán. No es mi culpa que siempre nos metamos en problemas, tú y yo. Pero, por favor, no te preocupes, esta vez no habrá disparos... probablemente.";
		link.l1 = "Me intrigas, continúa. ¿Cómo puedo ayudar?";
		link.l1.go = "goldengirl_2";
		break;

	case "goldengirl_2":
		dialog.text = "¿Has oído hablar del fino establecimiento de Madame Botot? Durante el asedio nuestro... burdel se quemó hasta los cimientos. Un día cierta dama se ofreció a reconstruirlo.";
		link.l1 = "¿Un incendio en un burdel y sin mí? Por cierto, también me dispararon los españoles ese día.";
		link.l1.go = "goldengirl_3";
		break;

	case "goldengirl_3":
		dialog.text = "¡Maldita sea, Charles, ¿qué te pasa hoy? ¡Tu ingenio es inapropiado! Aunque no sea un asunto de Estado, sigue siendo un asunto importante, para mí, personalmente. ¡Necesito tu ayuda! ¡Por el amor de Dios, cálmate y escúchame!";
		link.l1 = "Perdóneme, Su Excelencia. Estoy sintiendo un gran alivio, eso es todo. Para ser honesto, me cansé de toda esta constante batalla y lucha. Esperaba que me arrastrara a otro círculo de violencia. Por favor, continúe. Nunca he oído hablar de esta Madame Botot.";
		link.l1.go = "goldengirl_4";
		break;

	case "goldengirl_4":
		dialog.text = "Correcto, así que esta honorable dama elevó el establecimiento a un nivel completamente nuevo. Ahora es un lugar de alta y noble sociedad, no un agujero de ratas, como solía ser. Un lugar de vicios distinguidos, vino caro y juego ilimitado. ¡Lo verás todo por ti mismo!";
		link.l1 = "Su Excelencia, no soy un mojigato y su descripción fue muy colorida, pero ¿por qué me está contando esto?";
		link.l1.go = "goldengirl_5";
		break;

	case "goldengirl_5":
		dialog.text = "¡Porque estás en la lista!, ¿por qué más? Mira, me siento culpable por la Marquesa y prometí presentarte a ella en una de sus fiestas mañana. Juliana no hace esto a menudo, así que por favor sé lo suficientemente amable para unirte a nosotros. No habrá peleas, disparos ni persecuciones esta vez, lo prometo. Todo será cortés y digno: vino, mujeres hermosas, cartas y otros placeres nobles.";
		link.l1 = "Cartas y prostitutas. Ha pasado un tiempo desde entonces, en otra vida. Sin embargo, todavía no te sigo. ¿Por qué yo?";
		link.l1.go = "goldengirl_6";
		break;

	case "goldengirl_6":
		dialog.text = "¿Eres sordo? Juliana Botot, ella... colecciona rostros brillantes y famosos. Hacen que sus fiestas sean especiales y frescas. Te has hecho un buen nombre, la Marquesa había esperado mucho tiempo para tenerte como su invitado. Mi paso en falso le dio una oportunidad y no la tomaré si se niega a recibirme de nuevo. ¡Esto es todo lo que obtengo si no te entrego a ella!";
		link.l1 = "Su Excelencia, usted es un apuesto viudo y gobernador... ¿Por qué le importa la opinión de alguna cortesana? Son ellas quienes deberían buscar su favor, no al revés.";
		link.l1.go = "goldengirl_7";
		break;

	case "goldengirl_7":
		dialog.text = "La marquesa Botot está bajo la protección del conde Henry de Levi-Vantadur, quien, por la gracia de Su Majestad, es el jefe de los estados de Nueva Francia en América del Norte. Créeme, Charles, nadie aquí quiere cruzarse con él.";
		link.l1 = "Casi me tenías, pensé que esto era solo sobre lujuria y amor. Ahora veo que se trataba de política todo el tiempo. Trivial, pero esperado. Muy bien, te ayudaré. Será dulce volver a los días de mi juventud solo por una noche.";
		link.l1.go = "goldengirl_8";
		break;

	case "goldengirl_8":
		dialog.text = "Capitán, sin duda eres un hombre experimentado, sin embargo, no intentes hacerte pasar por un anciano. No se trata solo de política. Valoro la presencia de Juliana y estoy agradecido por tu ayuda. Es importante para mí personalmente, de verdad. Ven al lugar de la marquesa Botot después del anochecer, mañana. Te prometo que la política no estropeará la noche.";
		link.l1 = "Vino, cartas, mujeres. Como en los buenos tiempos. ¡Adiós, Su Excelencia!";
		link.l1.go = "goldengirl_9";
		break;

	case "goldengirl_9":
		DialogExit();
		bDisableFastReload = true; // закрыть переход
		pchar.quest.GoldenGirl_bronca.win_condition.l1 = "location";
		pchar.quest.GoldenGirl_bronca.win_condition.l1.location = "FortFrance_town";
		pchar.quest.GoldenGirl_bronca.function = "GoldenGirl_GirlAngry";
		if (bImCasual)
			NewGameTip("Modo exploración: el temporizador no está desactivado. ¡Cumple el plazo!");
		SetFunctionTimerCondition("GoldenGirl_TimeOver", 0, 0, 2, false);	 // таймер до завтрашней полуночи
		SetFunctionTimerCondition("GoldenGirl_BrothelDoor", 0, 0, 1, false); // таймер на закрытие дверей борделя
		pchar.quest.GoldenGirl_eventstart.win_condition.l1 = "Timer";
		pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.hour = 21.00;
		pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.GoldenGirl_eventstart.win_condition.l2 = "location";
		pchar.quest.GoldenGirl_eventstart.win_condition.l2.location = "FortFrance_SecBrRoom"; // возможно закрыть бордель и вход только через боковую комнату
		pchar.quest.GoldenGirl_eventstart.function = "GoldenGirl_Party";					  // таймер на начало вечеринки
		pchar.questTemp.GoldenGirl = "brothel";
		AddQuestRecord("GoldenGirl", "2");
		break;

	case "goldengirl_10":
		dialog.text = "¡Charles, qué ha pasado, pareces salido del infierno!";
		link.l1 = "Angerran, maldito, Chievous, Excelencia. Robó mi fragata anoche. Ejecutó a mi tripulación de premio y zarpó en la niebla.";
		link.l1.go = "goldengirl_11";
		break;

	case "goldengirl_11":
		dialog.text = "Es un giro desagradable de los acontecimientos, lo entiendo, pero créame, tal resultado es bastante satisfactorio. No estás en necesidad urgente de barcos y hombres, mientras que de Levi Vantadur pagará una suma considerable para ocultar la verdad detrás de cierto duelo reciente. O recordará nuestro papel en ocultarlo gratuitamente, lo cual también vale bastante. De Chievous hizo cosas deshonestas dos veces, pero ahora está lejos mientras que todavía tenemos buenas cartas contra él.";
		link.l1 = "Tres veces, su Excelencia. Angerran admitió haber hecho trampa durante nuestro juego de cartas. Pero no me pagará con dinero, si es eso lo que quiere decir. Ha cruzado la línea. Había una cierta persona en ese barco esta mañana... ¡ella es muy querida para mí! ¡No dejaré que ese bastardo le haga daño alguno! ¿Oyes eso, Jacques? ¡No lo permitiré!";
		link.l1.go = "goldengirl_12";
		break;

	case "goldengirl_12":
		dialog.text = "Creo que sé de quién hablas, recuerdo haberte visto con alguna... chica, vestida como un hombre y armada hasta los dientes como un pirata. ¡Charles, no seas idiota! Tuviste suerte, evitaste grandes problemas y ¿qué, estás tratando de meterte en ellos de nuevo? Déjalo ir. ¡De Chievous está huyendo, gracias a Dios! Y respecto a tu 'novia en armas', toma el consejo de tu amigo, ve a ver a Julianna y olvídate de todo esto.";
		link.l1 = "Fuera de discusión, su Excelencia. Algunas cosas están simplemente más allá de su comprensión, ¿de acuerdo? Ahora dígame todo lo que sabe sobre el bastardo. ¿A dónde podría ir desde Saint-Pierre? Y no intente disuadirme de nuevo: ¡me he jodido con la Compañía Holandesa, jodido con los barones piratas, con los gobernadores generales, incluso con la Santa Inquisición! No soy un hombre fácil de asustar. ¡La recuperaré cueste lo que cueste!";
		link.l1.go = "goldengirl_13";
		break;

	case "goldengirl_13":
		dialog.text = "Charles, ¿alguna vez has pensado en la cuestión de quién nombra a los gobernadores generales? ¡Este es un mundo absolutamente diferente! Apenas lo has tocado, está más allá de tu comprensión, eres como un niño dentro de un almacén de pólvora. Y me estás pidiendo que te pase una vela encendida. En cuanto a los gobernadores generales: de Poincy nunca cruza al conde ni en asuntos de moneda ni en asuntos de política. Rey Vice, el término tan popular entre los plebeyos, le vendría muy bien a Henri de Levi Vantadur.";
		link.l1 = "Y aquí estoy, con la intención de desollar a su único heredero varón, sé lo que estoy arriesgando aquí. Ahora, solo dime: ¿hay algo útil que sepas que podría ayudarme?";
		link.l1.go = "goldengirl_14";
		break;

	case "goldengirl_14":
		dialog.text = "En otro día, consideraría este movimiento hacia tu pistola como el fin de nuestra amistad, Charles. Pero entiendo tu estado mental actual. Por eso estoy dispuesto a olvidar esto. No sé nada que te sea útil, la fragata se dirigió al oeste temprano en la mañana. Deberías visitar al Marqués... ¡Espera, no así! Julianna sabe mucho sobre tu enemigo y estuvo personalmente... relacionada con su padre por un tiempo. Pregúntale a ella. A diferencia de mí, ella no te detendrá.";
		link.l1 = "Ese es el plan. Nos vemos, Excelencia. Gracias por su tiempo.";
		link.l1.go = "goldengirl_15";
		break;

	case "goldengirl_15":
		DialogExit();
		LocatorReloadEnterDisable("FortFrance_town", "reload9_back", false);
		LocatorReloadEnterDisable("FortFrance_town", "reload91", false);
		sld = characterFromId("Julianna");
		sld.dialog.currentnode = "Julianna_58";
		LAi_SetOwnerType(sld);
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
		pchar.questTemp.GoldenGirl = "find_girl";
	break;
		
	// В плену великого улова, andre39966
	case "VPVL_Magor_1":
		dialog.text = "¿Contrabando, dice? Hmm... muy intrigante. Le ruego, ilumíneme con los detalles de su descubrimiento.";
		link.l1 = "Hace tres días, una embarcación cargada de contrabando debía echar el ancla en la Bahía de Le Marin. El barco no llegó a su cita, pero tengo buenas razones para creer que aún arribará a puerto dentro de poco. Quizás vuestros hombres podrían preparar un recibimiento adecuado para estos bandidos cuando lleguen, Excelencia.";
		link.l1.go = "VPVL_Magor_2";
		pchar.questTemp.VPVL_DontSpawnSmugglersShip = true; 
		DelLandQuestMark(npchar);
	break;
		
	case "VPVL_Magor_2":
		dialog.text = "¿Un navío sin nombre transportando carga sin especificar... Y presume que debo enviar las fuerzas de Su Majestad basándome en información tan nebulosa?";
		link.l1 = "Excelencia, reconozco que los detalles son escasos. Pero le ruego me permita relatar cómo esta información llegó a mi poder. (cuenta)";
		link.l1.go = "VPVL_Magor_3";
	break;
		
	case "VPVL_Magor_3":
		dialog.text = "Muy bien, pondremos a prueba su información. Si efectivamente un navío con contrabando echa el ancla frente a las costas de Le Marin, usted, Capitán, será generosamente recompensado por su servicio a la Corona. Vuelva a verme dentro de tres días. Para entonces, la niebla de la incertidumbre se habrá disipado.";
		link.l1 = "Perfecto. Entonces nos veremos dentro de tres días.";
		link.l1.go = "VPVL_Delete_Spawn_Ship";
		AddDialogExitQuest("VPVL_SetGovernorDialogueFlag");
		AddQuestRecord("VPVL", "6");
	break;
		
	case "VPVL_Magor_4":
		dialog.text = "¡Ah, Capitán! Un placer recibirle una vez más. Su información resultó, en efecto, muy valiosa. Mis hombres interceptaron la embarcación exactamente donde usted indicó. Aquí tiene—ciento cincuenta doblones españoles, recién acuñados y de gran peso en la bolsa. Acéptelos con mi gratitud.";
		link.l1 = "Estoy muy agradecid"+GetSexPhrase("o","a")+" por su consideración, Excelencia. Me alegra que mi fragmento de información haya servido a los intereses de la Corona. Si surge nuevamente la oportunidad, sepa que mi brazo armado y mi ojo perspicaz quedan a su disposición.";
		link.l1.go = "VPVL_Delete_Flag";
		AddItems(PChar, "gold_dublon", 150);
		ChangeCharacterNationReputation(pchar, FRANCE, 5);
		DelLandQuestMark(npchar);
	break;
		
	case "VPVL_Delete_Flag":
		DialogExit();
		DeleteAttribute(pchar, "questTemp.VPVL_GovernorDialogueAvailable");
		DeleteAttribute(pchar, "questTemp.VPVL_DontSpawnSmugglersShip");
	break;
		
	case "VPVL_Delete_Spawn_Ship":
		DialogExit();
		DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
		AddDialogExitQuest("VPVL_KillCapitanOfSmuggler");
	break;
	// <=== В плену великого улова
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
