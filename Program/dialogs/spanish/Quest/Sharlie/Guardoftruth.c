// диалоги НПС по квесту 'В поисках Стража Истины'
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "¿Cómo puedo ayudarle?";
		link.l1 = "Lo siento, no es nada.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	// пленный испанец
	case "spa_prisoner":
		PlaySound("Voice\Spanish\Ransack_1.wav");
		dialog.text = "¿Qué quieres? ¿Otro interrogatorio? ¡Vete al diablo!";
		link.l1 = "Señor, ¿cuál es su nombre?";
		link.l1.go = "spa_prisoner_1";
		break;

	case "spa_prisoner_1":
		dialog.text = "¿Qué diablos te importa el nombre del hombre al que vas a colgar o disparar? ¡Bastardo! Fui lo suficientemente imprudente como para caer en tus manos después de todo...";
		link.l1 = "Señor, identifíquese. No puedo hablar con un hombre sin saber cuál es su nombre.";
		link.l1.go = "spa_prisoner_2";
		break;

	case "spa_prisoner_2":
		dialog.text = "Don " + GetFullName(npchar) + ". Listo, ¿estás feliz? Ahora, ¿con quién tengo el placer de hablar?";
		link.l1 = "Mi nombre es " + GetFullName(pchar) + ". ¿Has oído hablar de mí antes?";
		link.l1.go = "spa_prisoner_3";
		break;

	case "spa_prisoner_3":
		dialog.text = "¡No, carajo! ¿Acaso parezco conocer a todos los vagabundos errantes en las Indias Occidentales o qué?";
		link.l1 = "Basta. Hagámoslo sin insultos y comportémonos como caballeros. Tu destino dependerá de lo que puedas contarme. Si me dices algo interesante, solicitaré tu liberación bajo mi custodia. Eso te permitirá escapar de la bala de mosquete, o la horca que te espera ahora mismo.";
		link.l1.go = "spa_prisoner_4";
		break;

	case "spa_prisoner_4":
		dialog.text = "¡Dios mío, esa es una oferta que no puedo rechazar! ¿Qué le gustaría saber, señor?";
		link.l1 = "¿Quién organizó un ataque tan grande en Saint-Pierre y por qué?";
		link.l1.go = "spa_prisoner_5";
		break;

	case "spa_prisoner_5":
		dialog.text = "Barón Ramón de Mendoza y Riba, el comandante de la guarnición de la Isla de Providencia. Despachó un escuadrón para atacar y saquear la colonia, apoderándose de cualquier objeto valioso que pudiéramos encontrar.";
		link.l1 = "¿Cuál fue tu tarea inmediata en el ataque? Específicamente, ¿cuáles fueron tus órdenes?";
		link.l1.go = "spa_prisoner_6";
		break;

	case "spa_prisoner_6":
		dialog.text = "Soy el comandante del batallón de soldados. Nuestras órdenes eran tomar el fuerte y asegurar que sus baterías no dispararan sobre nuestras barcas de desembarco al acercarse al pueblo. Después de eso, mis hombres participaron en el ataque a Saint-Pierre en sí mismo.";
		link.l1 = "¿Fuiste informado de los objetos de valor ubicados en la ciudad? ¿De la cantidad y calidad?";
		link.l1.go = "spa_prisoner_7";
		break;

	case "spa_prisoner_7":
		dialog.text = "No teníamos información exacta sobre la cantidad, pero el Barón de Mendosa y Riba nos dijo que hay plata almacenada bajo el fuerte, y que los almacenes del puerto tienen materias primas estratégicas vitales para el esfuerzo bélico: sándalo y seda de barco.";
		link.l1 = "¿Encontraste esos objetos de valor?";
		link.l1.go = "spa_prisoner_8";
		break;

	case "spa_prisoner_8":
		dialog.text = "No. No encontramos ninguno de los dos. Los almacenes estaban llenos de mercancías coloniales típicas y debajo del fuerte había pólvora, armamento y plomo. Pero no tuvimos tiempo suficiente para realizar una búsqueda más exhaustiva... llegaron los refuerzos franceses rugiendo y nos vimos obligados a dar batalla.";
		link.l1 = "¿No te pareció extraño que no encontraras los objetos de valor?";
		link.l1.go = "spa_prisoner_9";
		break;

	case "spa_prisoner_9":
		dialog.text = "Por supuesto, pero no suelo cuestionar órdenes.";
		link.l1 = "Escucha lo que estoy a punto de decirte. El Fuerte de Saint-Pierre nunca ha contenido plata, y esos almacenes nunca han guardado sándalo y seda. Piense bien, señor, antes de responder, porque si su respuesta no me agrada, me daré la vuelta y saldré de aquí dejándolo a su suerte... una suerte lamentable.";
		link.l1.go = "spa_prisoner_10";
		break;

	case "spa_prisoner_10":
		dialog.text = "Estoy escuchando.";
		link.l1 = "No creo que el único objetivo de tu incursión fuera un simple robo. Saint-Pierre es una colonia modesta y relativamente pobre para enviar todo un escuadrón aquí liderado por un navío de primera clase. Seguramente tú, tu comandante o alguien más tenía órdenes adicionales o directrices. ¿Qué te dijeron? Piensa bien antes de responder...";
		link.l1.go = "spa_prisoner_11";
		break;

	case "spa_prisoner_11":
		dialog.text = "";
		link.l1 = "¿Vas a quedarte callado? Está bien. Piénsalo por un momento, esperaré.";
		link.l1.go = "spa_prisoner_12";
		break;

	case "spa_prisoner_12":
		dialog.text = "Señor, ¿mi vida va a depender de mi respuesta?";
		link.l1 = "Correcto.";
		link.l1.go = "spa_prisoner_13";
		break;

	case "spa_prisoner_13":
		dialog.text = "Tengo algo... Pero debes jurarme que me sacarás de aquí, y me rescatarás y enviarás de vuelta a España.";
		link.l1 = "Si me dices algo digno de mi atención, juro por la Santa Cruz, que serás llevado a bordo de mi navío para pedir rescate y escaparás de la ejecución.";
		link.l1.go = "spa_prisoner_14";
		break;

	case "spa_prisoner_14":
		dialog.text = "Está bien. Don Diego de Montoya instruyó a nuestro batallón de soldados que debemos, con total secreto e importancia, encontrar y capturar a un hombre llamado Miguel Dichoso, que se encuentra en algún lugar de Saint-Pierre bajo la protección de las autoridades.";
		link.l1 = "Sigue adelante. ¿Quién es Diego de Montoya?";
		link.l1.go = "spa_prisoner_15";
		break;

	case "spa_prisoner_15":
		dialog.text = "El oficial al mando del escuadrón. Huyó poco después de tu... dramática llegada.";
		link.l1 = "¿Quién es él? ¿Este, 'Don Diego'?";
		link.l1.go = "spa_prisoner_16";
		break;

	case "spa_prisoner_16":
		dialog.text = "Solo sé que es un representante autorizado del Barón de Mendosa y Riba, su mano derecha y agente para tareas críticas.";
		link.l1 = "Interesante... ¿Y quién es Miguel Dichoso, el hombre a quien aparentemente se organizó toda esta catástrofe para atrapar? Debe ser un mal hombre, ¿eh?";
		link.l1.go = "spa_prisoner_17";
		break;

	case "spa_prisoner_17":
		dialog.text = "¿Recuerda su juramento, señor?";
		link.l1 = "Sí. Y afirmo que si continúas contando tu historia, serás entregado como testigo clave a mi barco y luego... bueno, encontraré la manera de llevarte a un asentamiento español. Pero no antes de que me cuentes todo lo que sabes.";
		link.l1.go = "spa_prisoner_18";
		break;

	case "spa_prisoner_18":
		dialog.text = "Miguel Dichoso es el antiguo compañero de armas del barón, sin embargo, algunos dicen que Miguel lo traicionó. El Señor de Mendosa y Riba lo quiere vivo, así que se nos dio la orden de no matar a Dichoso bajo ninguna circunstancia.";
		link.l1 = "¿Dichoso es también un español?";
		link.l1.go = "spa_prisoner_19";
		break;

	case "spa_prisoner_19":
		dialog.text = "Sí. Don Diego de Montoya nos dio una descripción aproximada y ordenó que cualquier hombre que se pareciera a Dichoso tenía que ser entregado directamente a él. Pero dado el poco tiempo que tuvimos antes de vuestro contraataque, nunca tuvimos tiempo para buscar.";
		link.l1 = "¿Conocías a Dichoso personalmente?";
		link.l1.go = "spa_prisoner_20";
		break;

	case "spa_prisoner_20":
		dialog.text = "No, solo de reputación. Nunca he visto al hombre antes. Algunos de mis compañeros oficiales lo conocían personalmente. Todos ellos están muertos.";
		link.l1 = "¿Qué tan gravemente traicionó Dichoso a tu 'Don Mendosa' para que decidiera enviarle toda una escuadra tras él?";
		link.l1.go = "spa_prisoner_21";
		break;

	case "spa_prisoner_21":
		dialog.text = "Te lo diré. El barón llegó hace poco al Caribe desde España. Sus órdenes eran asegurar la seguridad de los convoyes de la Flota del Tesoro Español, pero en cambio miró hacia el interior... buscando oro indio. Su cabeza fue girada por rumores de tesoros ocultos. Decidió que una antigua ciudad maya existe en algún lugar profundamente en las selvas de Yucatán: Tayasal, la legendaria ciudad de oro.\nEl barón envió varias expediciones para encontrar la ciudad, pero todas ellas fueron completamente aniquiladas en la selva salvaje. No cabe duda de que cada uno de ellos fue masacrado por el pueblo marcial Itza que vive allí.\nFinalmente, el Inquisidor Vincento tuvo suficiente de las fantasías de Don Mendosa, y la muerte sin sentido de buenos soldados. El inquisidor informó a Madrid sobre la situación. El virrey prohibió a Don Mendosa buscar la ciudad mítica y concentrarse en sus deberes. Fue entonces cuando apareció Miguel Dichoso.\nConvenció al barón para organizar otra expedición que sorprendentemente fue un éxito. Encontraron ruinas de una ciudad antigua y un montón de oro incrustado con joyas. Pero en su regreso fueron atacados por la tribu Miskito.\nTodos excepto Miguel perecieron, los dardos indios están empapados con algún veneno local, incluso un pequeño rasguño lleva a una muerte segura y agonizante en pocos días. Dichoso regresó a Providencia con el tesoro que pudo llevar.\n¡Carajo! El barón estaba indescriptiblemente feliz, envió cartas urgentes a Madrid y al Padre Vincento en Santiago, sin duda quería restregar su éxito en la cara del Reverendo Padre. Luego se preparó una fragata para entregar el tesoro de regreso a España. Dichoso se ofreció para escoltarla.";
		link.l1 = "Déjame adivinar. ¿No entregó el oro?";
		link.l1.go = "spa_prisoner_22";
		break;

	case "spa_prisoner_22":
		dialog.text = "¡Correcto, señor! La fragata desapareció sin dejar rastro junto con toda la carga y la tripulación, incluido Dichoso. El barón estaba furioso. Una vez más fue humillado frente al Escorial para gran satisfacción del Padre Vincento. Ahora Don Mendosa es un hombre obsesionado con recuperar su orgullo herido, su tesoro perdido, y a Miguel Dichoso.";
		link.l1 = "¿No es posible que la fragata haya quedado atrapada en una tormenta y naufragado? ¿O capturada por piratas?";
		link.l1.go = "spa_prisoner_23";
		break;

	case "spa_prisoner_23":
		dialog.text = "El barón juró en el calor del momento que estaba seguro de que Dichoso lo traicionó. No sé los detalles. Después de varias semanas, Don Diego de Montoya llegó con nueva información, de que Miguel Dichoso podría estar en St. Pierre.";
		link.l1 = "Mm. Interesante. Esos tesoros indios otra vez. Todo parece estar sospechosamente ligado a ellos... Entonces, ¿no encontraste a Dichoso?";
		link.l1.go = "spa_prisoner_24";
		break;

	case "spa_prisoner_24":
		dialog.text = "No. Y honestamente me sorprendería si alguna vez estuvo aquí. El barón está tan obsesionado con la idea de capturar a Dichoso que creería incluso en las fantasías más descabelladas.";
		link.l1 = "Dime, " + npchar.name + ", ¿cómo se enteró Don Mendosa sobre esta... eh... ciudad de Tayasal? No lo soñó, ¿verdad? ¿Hubo algunos hechos o algo más?";
		link.l1.go = "spa_prisoner_25";
		break;

	case "spa_prisoner_25":
		dialog.text = "Fue el Padre Vincento quien primero escuchó sobre la supuesta existencia de Tayasal y la ciudad de oro. Dónde lo descubrió, no tengo ni idea...";
		link.l1 = "Eso es un desarrollo interesante. El Padre Vincento elaboró la teoría de la existencia de Tayasal por sí mismo, informó a España por sí mismo y comenzó a echar moscas en la pomada del barón...";
		link.l1.go = "spa_prisoner_26";
		break;

	case "spa_prisoner_26":
		dialog.text = "Como buen católico, deberías saber cómo trabajan estos reverendos padres del Santo Tribunal... No informó a Madrid sin motivo. Tiene algún plan, pero la llegada del barón aparentemente no formaba parte de sus planes. De todos modos, no sé más al respecto. Nunca he tenido el deseo de tratar con la Inquisición.";
		link.l1 = "Está bien. Me has dado mucha información interesante, " + npchar.name + ", y fiel a mi juramento, te sacaré de aquí. Volveré por ti más tarde, pero por ahora... déjame pensar un poco sobre lo que me has contado...";
		link.l1.go = "spa_prisoner_27";
		break;

	case "spa_prisoner_27":
		DialogExit();
		pchar.questTemp.Guardoftruth = "think";
		LAi_CharacterDisableDialog(npchar); // запрет диалога
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "goto", "goto3", "GuardOT_MCthink", -1);
		break;

	case "spa_prisoner_28":
		PlaySound("Voice\Spanish\Ransack_2.wav");
		dialog.text = "¿Señor? ¿Cumplirá con su promesa?";
		link.l1 = "Siempre cumplo mis promesas. Hoy es tu día de suerte, " + npchar.name + "Vienes conmigo a Santiago en Cuba. Te contaré más sobre mi plan cuando lleguemos. Pero por ahora, bienvenido a bordo. Serás acompañado al puerto y llevado a mi barco.";
		link.l1.go = "spa_prisoner_29";
		break;

	case "spa_prisoner_29":
		dialog.text = "Tienes mi gratitud, capitán. Me alegra que seas un caballero de palabra.";
		link.l1 = "Puedes expresar tu gratitud más tarde. Serás mi invitado, pero bajo vigilancia. No lo tomes a mal, aún te necesito.";
		link.l1.go = "spa_prisoner_30";
		break;

	case "spa_prisoner_30":
		dialog.text = "Entiendo, señor. Le doy mi palabra como oficial español de que no haré ningún intento de escapar.";
		link.l1 = "Que Dios proteja a los cautos. Nos vemos a bordo.";
		link.l1.go = "spa_prisoner_31";
		break;

	case "spa_prisoner_31":
		DialogExit();
		pchar.questTemp.Guardoftruth = "cuba";
		LAi_CharacterDisableDialog(npchar); // запрет диалога
		chrDisableReloadToLocation = false; // открыть локацию
		pchar.quest.GuardOT_exitbase.win_condition.l1 = "ExitFromLocation";
		pchar.quest.GuardOT_exitbase.win_condition.l1.location = pchar.location;
		pchar.quest.GuardOT_exitbase.function = "GuardOT_ExitFrombase";
		AddQuestRecord("Guardoftruth", "4");
		break;

	case "spa_prisoner_32":
		PlaySound("Voice\Spanish\Serve_senior.wav");
		dialog.text = "Capitán, ¿cuáles son sus objetivos aquí en Cuba? ¿Está aquí para dejarme? Ni siquiera me atrevo a esperar eso...";
		link.l1 = "Eso es exactamente correcto, estoy aquí para devolver a tus compatriotas. Ahora, la razón de mi llegada aquí es un poco más complicada que solo eso. Pero eso ya no te concierne. Te dejaré ir ahora mismo sin ningún rescate, pero con la condición de que me jures dos cosas.";
		link.l1.go = "spa_prisoner_33";
		break;

	case "spa_prisoner_33":
		dialog.text = "¿Qué sería?";
		link.l1 = "La primera es que te daré una carta sellada. Entregarás personalmente esa carta al Inquisidor de Santiago, el Padre Vincento. Si te pregunta de quién es la carta y cómo la conseguiste, dile la verdad...";
		link.l1.go = "spa_prisoner_34";
		break;

	case "spa_prisoner_34":
		dialog.text = "";
		link.l1 = "El segundo es que no ayudarás ni asistirás en ningún intento de encontrarme y atacar mi barco al menos por una semana. ¿De acuerdo?";
		link.l1.go = "spa_prisoner_35";
		break;

	case "spa_prisoner_35":
		dialog.text = "¿Eso es todo?";
		link.l1 = "Sí, eso es todo. Cumple mis condiciones y eres libre de irte.";
		link.l1.go = "spa_prisoner_36";
		break;

	case "spa_prisoner_36":
		dialog.text = "Te juro, señor, que entregaré la carta al Padre Vincento personalmente y que no emprenderé acciones de ningún tipo que puedan provocar la agresión de la guarnición de Santiago contra ti o tu barco. Ten la seguridad de que cumpliré mi palabra. Soy un español y respeto a los adversarios fuertes y nobles.";
		link.l1 = "Está bien, Don " + GetFullName(npchar) + ", acepto tu juramento y te dejo ir ahora mismo. Aquí, toma esta carta para el Inquisidor. Ahora eres libre.";
		link.l1.go = "spa_prisoner_37";
		break;

	case "spa_prisoner_37":
		Log_Info("¡Has entregado la carta!");
		PlaySound("interface\important_item.wav");
		dialog.text = "Adiós, señor. Espero que nunca volvamos a encontrarnos en el campo de batalla. Me dolería terriblemente.";
		link.l1 = "Adiós...";
		link.l1.go = "spa_prisoner_38";
		break;

	case "spa_prisoner_38":
		DialogExit();
		RemovePassenger(pchar, npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
		chrDisableReloadToLocation = false; // открыть локацию
		AddQuestRecord("Guardoftruth", "5");
		pchar.quest.GuardOT_mayak.win_condition.l1 = "Timer";
		pchar.quest.GuardOT_mayak.win_condition.l1.date.hour = sti(GetTime() - (rand(4)));
		pchar.quest.GuardOT_mayak.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.GuardOT_mayak.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.GuardOT_mayak.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.GuardOT_mayak.win_condition.l2 = "location";
		pchar.quest.GuardOT_mayak.win_condition.l2.location = "mayak9";
		pchar.quest.GuardOT_mayak.function = "GuardOT_CreateVinsentoAgent";
		AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;

	case "spa_prisoner_39":
		dialog.text = "¡Dios mío, qué encuentro tan afortunado! Hola, monsieur " + GetFullName(pchar) + ". Veo que te has convertido en un huésped bienvenido en Santiago. ¿Estás trabajando para la Santa Inquisición?";
		link.l1 = "Saludos, señor " + npchar.name + ". Pensé que nunca volveríamos a vernos, al menos no en circunstancias amistosas. No, solo he pasado a visitar al Padre Vincento. ¿Y tú? ¿Sirves ahora en Santiago?";
		link.l1.go = "spa_prisoner_40";
		break;

	case "spa_prisoner_40":
		dialog.text = "Después de que me liberaste del arresto, me vi obligado a quedarme en Santiago, no es seguro para mí regresar a Providencia... pero como puedes ver, he cumplido mi palabra. No hay naves españolas persiguiéndote...";
		link.l1 = "Me alegra que ambos seamos hombres de palabra.";
		link.l1.go = "spa_prisoner_41";
		break;

	case "spa_prisoner_41":
		dialog.text = "Escuche, capitán, ¿le importaría levantar un vaso de ron, por así decirlo, a nuestra reunión? Nunca pensé que le ofrecería eso a un francés, pero usted, señor, es una excepción.";
		link.l1 = "¡Por supuesto! No me importaría enjuagarme la boca con un poco de ron. Vamos a la taberna.";
		link.l1.go = "spa_prisoner_42";
		break;

	case "spa_prisoner_42":
		DialogExit();
		NextDiag.CurrentNode = "spa_prisoner_43";
		FreeSitLocator("Santiago_tavern", "sit_front4");
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Santiago_tavern", "sit", "sit_front4", "GuardOT_SpaOfficerInTavern", -1);
		break;

	case "spa_prisoner_43":
		LAi_SetSitType(Pchar);
		dialog.text = "¡Ah, salud!";
		link.l1 = "¿A qué brindamos, señor oficial?";
		link.l1.go = "spa_prisoner_44";
		break;

	case "spa_prisoner_44":
		dialog.text = "Brindemos por algo neutral, pero que nos concierne a ambos. Por ejemplo, ¡el galante y exitoso servicio a la nación! ¡Cada uno tiene la suya!";
		link.l1 = "Y brindemos también por que nuestros monarcas lleguen a un acuerdo entre ellos, y que los franceses y los españoles dejen de pelear tanto en casa como en el Caribe.";
		link.l1.go = "spa_prisoner_45";
		break;

	case "spa_prisoner_45":
		dialog.text = "¡Bien dicho, capitán! ¡Por la paz! ¡Te mostraré cómo beber al estilo español! ¡Arriba, abajo, al centro y para dentro!";
		link.l1 = "Por la paz... (bebiendo)";
		link.l1.go = "spa_prisoner_46";
		break;

	case "spa_prisoner_46":
		dialog.text = "¡Ajá! El ron cubano es verdaderamente el mejor del Caribe...";
		link.l1 = "Estoy de acuerdo. Dime, ¿intentaron castigarte por ser capturado en Saint-Pierre?";
		link.l1.go = "spa_prisoner_47";
		break;

	case "spa_prisoner_47":
		dialog.text = "Afortunadamente solo recibí una palmada en la muñeca. Ese desastre ya quedó atrás. Después de todo, necesitan oficiales aquí en las colonias.";
		link.l1 = "Y tu comandante... ¿cómo se llamaba? Diego, ¿verdad? ¿Cómo le fue en la incursión infructuosa? ¿Lo degradaron?";
		link.l1.go = "spa_prisoner_48";
		break;

	case "spa_prisoner_48":
		dialog.text = "¡Oh, no! Nuestro querido Diego de Montoya es intocable mientras tenga a Don Ramón de Mendosa y Riba detrás de él. Por cierto, Don Diego estuvo en Santiago justo ayer. Llegó desde San José.";
		link.l1 = "¿No me digas? ¡Intrigante! Menos mal que no nos encontramos en la calle. Me temo que ese asunto podría haber terminado en un duelo, ¡jaja!";
		link.l1.go = "spa_prisoner_49";
		break;

	case "spa_prisoner_49":
		dialog.text = "Don Diego no tiene tiempo para usted ahora, capitán. Tiene demasiado en juego en este momento como para arriesgar su vida en un duelo. Ha ideado un plan junto con el Barón Mendosa en Tierra Firme occidental. Ha reunido un escuadrón en La Habana y está buscando zarpar de regreso a España en cualquier momento.";
		link.l1 = "¿Eres parte de su tripulación también?";
		link.l1.go = "spa_prisoner_50";
		break;

	case "spa_prisoner_50":
		dialog.text = "No. Mañana parto a la guarnición en San Juan, que está en Puerto Rico. Ya no soy bienvenido en Providencia con Don Mendosa allí.";
		link.l1 = "Bueno, entonces brindemos por tu nuevo destino y que no te esperen allí más que tiempos felices y bellas damas.";
		link.l1.go = "spa_prisoner_51";
		break;

	case "spa_prisoner_51":
		dialog.text = "Muchas gracias, monsieur. Todos los buenos deseos para usted también. Ah, creo que es hora de que me vaya. Terminaré esta bebida y luego me despediré de usted.";
		link.l1 = "Vaya con Dios, señor " + npchar.name + ". Quizás nos volvamos a encontrar en paz.";
		link.l1.go = "spa_prisoner_52";
		break;

	case "spa_prisoner_52":
		DialogExit();
		AddDialogExitQuest("GuardOT_SpaOfficerOutTavern");
		break;

	case "spa_prisoner_53":
		PlaySound("Voice\Spanish\other\OZGi-07.wav");
		dialog.text = "Como le dije, don Diego: el pez mordió el anzuelo... Oh, parece que nos encontramos de nuevo, monsieur. Por desgracia, no bajo los auspicios pacíficos que deseábamos.";
		link.l1 = "¿" + npchar.name + "? No esperaba esto. Por alguna razón, pensé que eras un oficial honesto y noble. Resulta que estaba equivocado.";
		link.l1.go = "spa_prisoner_54";
		break;

	case "spa_prisoner_54":
		dialog.text = "¿Qué te hace pensar que estás equivocado? He cumplido mi palabra, no juré amistad eterna contigo. Nada ha cambiado, monsieur. Aún eres un enemigo de España y mi enemigo personal. Esto no es Santiago, aquí no está el Padre Vincento, y su pequeña carta de salvo conducto no te va a ayudar...";
		link.l1 = "¿Oh, es así? Me parece que tener una conversación amistosa con un poco de ron, mientras intentas atraerme a una trampa, es bastante traicionero, ¿no crees, señor " + npchar.name + "?";
		link.l1.go = "spa_prisoner_55";
		break;

	case "spa_prisoner_55":
		dialog.text = "¿Te atreves a llamarme traidor, desgraciado?!";
		link.l1 = "... ";
		link.l1.go = "spa_prisoner_56";
		break;

	case "spa_prisoner_56":
		DialogExit();
		sld = CharacterFromID("Diego");
		sld.dialog.currentnode = "shore";
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

	// посланец Винсенто
	case "vinsentoagent":
		PlaySound("Voice\Spanish\other\Master_01.wav");
		dialog.text = "¡Eh, tú! Sí, sí, ¡tú! ¿" + GetFullName(pchar) + "?";
		link.l1 = "Sí, compañero. Soy yo.";
		link.l1.go = "vinsentoagent_1";
		break;

	case "vinsentoagent_1":
		dialog.text = "Tengo una carta de una persona importante. Ya sabes quién es.";
		link.l1 = "Lo sé, dámela.";
		link.l1.go = "vinsentoagent_2";
		break;

	case "vinsentoagent_2":
		GiveItem2Character(pchar, "specialletter");
		ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
		sld = ItemsFromID("specialletter");
		sld.text = "Letter_Vincento";
		dialog.text = "Ahí tienes. ¿Qué tal unas monedas por mis molestias?";
		if (sti(Pchar.money) >= 2000)
		{
			link.l1 = "Toma un poco de plata. Te lo has ganado honestamente.";
			link.l1.go = "vinsentoagent_2_1";
			AddCharacterExpToSkill(pchar, "Leadership", 50);
		}
		else
		{
			link.l1 = "¿Intentas engañarme, compañero? Ya te pagaron por la entrega.";
			link.l1.go = "vinsentoagent_2_2";
		}
		break;

	case "vinsentoagent_2_1":
		AddMoneyToCharacter(pchar, -2000);
		dialog.text = "Gracias, muchacho. Un placer tratar con un caballero generoso.";
		link.l1 = "Está bien, piérdete, y no digas una palabra de lo que ocurrió aquí.";
		link.l1.go = "vinsentoagent_3";
		break;

	case "vinsentoagent_2_2":
		dialog.text = "El lobo de La Habana es tu amigo...";
		link.l1 = "¿Eh?  ¿Todavía estás aquí...?";
		link.l1.go = "vinsentoagent_3";
		break;

	case "vinsentoagent_3":
		DialogExit();
		npchar.lifeday = 0;
		LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
		chrDisableReloadToLocation = false; // открыть локацию
		break;

	// боцман Гая Марше
	case "boatsvandega":
		dialog.text = "¡Bienvenido a bordo del 'Admirable', capitán " + GetFullName(pchar) + "!";
		link.l1 = TimeGreeting() + " ¡Sorprendente! ¿Me conoces?";
		link.l1.go = "boatsvandega_1";
		break;

	case "boatsvandega_1":
		dialog.text = "¿Quién en las colonias francesas no ha oído hablar del gran capitán " + GetFullName(pchar) + "?, ¡el que pateó los dientes de un escuadrón español liderado por un acorazado que atacaba Saint-Pierre, y mató a todo el grupo de asalto enemigo! ¡Eres un héroe nacional!";
		link.l1 = "Vamos, vamos. 'Un héroe'... Solo soy un soldado cumpliendo su deber con Francia.";
		link.l1.go = "boatsvandega_2";
		break;

	case "boatsvandega_2":
		dialog.text = "No creo que muchos soldados pudieran haber hecho lo que hiciste, capitán... Eh, me gustaría invitarte a beber poco de ron en la taberna, pero por desgracia: el capitán ha prohibido que los hombres beban siquiera una gota de ron, y no quiero dar un mal ejemplo...";
		link.l1 = "Mm... ¿Así que tú no eres capitán?";
		link.l1.go = "boatsvandega_3";
		break;

	case "boatsvandega_3":
		dialog.text = "¿Parezco un capitán? ¡Ja-ja-ja! No, solo soy el contramaestre. Me llamo Serge Degas. Nuestro capitán, Gaius Marchais, pasa todo el día en la taberna, mientras nosotros estamos aquí esperando alguna caravana de 'mercaderes'. El capitán debe un subsidio a los marineros, y a nosotros también, toda la tripulación está completamente sin un centavo..";
		link.l1 = "¿Qué pasa? ¿La caravana de vainilla española no aparece para que le saquen las plumas?";
		link.l1.go = "boatsvandega_4";
		break;

	case "boatsvandega_4":
		dialog.text = "¡De ninguna manera! Nuestro capitán puso fin a la piratería después de capturar este galeón. Verás, escuchó que una caravana comercial hacia Europa hará una parada en Guadalupe pronto y estarán comprando vainilla. Así que llenó nuestras bodegas con vainilla hasta el tope en Bridgetown. Pensó que podría venderla a trescientos pesos la caja, sí, ¡iluso!\nPor supuesto, no hay caravana de vainilla cuando llegamos, y vender vainilla a los lugareños sería una pérdida. Así que aquí estamos, esperando a los ‘comerciantes’, estoy seguro de que aparecerán aquí un día o en tres años... el Capitán se sienta en la taberna todo el día, siendo una real molestia y fastidiando a todos. Solo regresa al barco para desmayarse. Ahora, finalmente, está listo para vender por doscientos pesos solo para cubrir costos.\nTodo nuestro dinero fue puesto en esa carga. Un día, la tripulación lo va a atar y vender la vainilla barata solo para cubrir nuestras deudas... Juro que puedo ver que sucederá cualquier día de estos.";
		link.l1 = "Sí... ¿qué le preocupa a tu capitán?";
		link.l1.go = "boatsvandega_5";
		break;

	case "boatsvandega_5":
		dialog.text = "Bueno, si un trabajo vale la pena hacerlo, vale la pena hacerlo bien. Él no hace ni lo uno, ni lo otro. Es un terrible negociante. Habría sido diferente si también transportara carga, pero quería sentirse como un verdadero comerciante. Espero que una noche se caiga por la borda...";
		link.l1 = "Te entiendo, Serge. No te preocupes, estoy seguro de que algún día tu... caravana aparecerá.";
		link.l1.go = "boatsvandega_6";
		break;

	case "boatsvandega_6":
		dialog.text = "Oh, no creo en los milagros, capitán. Tal vez nos volvamos a encontrar algún día y bebamos un poco de ron... lo que no daría por un poco de ron ahora mismo...";
		link.l1 = "Buena suerte, camarada.";
		link.l1.go = "boatsvandega_7";
		break;

	case "boatsvandega_7":
		DialogExit();
		NextDiag.currentnode = "boatsvandega_8";
		npchar.DeckDialogNode = "boatsvandega_8";
		// активируем каракку
		sld = characterFromId("GOT_Gevarra");
		sld.Dialog.Filename = "Quest\Sharlie\Guardoftruth.c";
		sld.DeckDialogNode = "gevarra";
		AddQuestRecord("Guardoftruth", "16");
		break;

	case "boatsvandega_8":
		dialog.text = "¡Eh, capitán, seguro que me gustaría un sorbo de ron!";
		link.l1 = "...";
		link.l1.go = "exit";
		NextDiag.TempNode = "boatsvandega_8";
		break;

	// Гай Марше
	case "marshe_tavern":
		PlaySound("Voice\Spanish\tavern\Kontrabandisti-15.wav");
		dialog.text = NPCStringReactionRepeat("¡Oh! ¿No serás tú del barco mercante? ¿No? Oh, mis disculpas. Por supuesto que no... Mi error.", "No estoy de humor, monsieur, así que búscate a otro con quien hablar.", "¿Ah, tú otra vez?!", "Ajá...", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("No te preocupes, amigo. Sucede.", " Toma un poco de ron, capitán.  Aliviará un poco tus problemas... ", "No te pongas nervioso, compañero. Es malo para tu salud.", "Está bien, está bien. Me voy.", npchar, Dialog.CurrentNode);
		link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		NextDiag.TempNode = "marshe_tavern";
		break;

	case "marshe_lay":
		PlaySound("Voice\Spanish\citizen\convict-07.wav");
		dialog.text = "A argh... Mm... ¿Qué demonios? ¿Qué es esto?..";
		link.l1 = "Silencio, amigo... No hagas ruido...";
		link.l1.go = "marshe_lay_1";
		break;

	case "marshe_lay_1":
		PlaySound("Voice\Spanish\citizen\convict-08.wav");
		dialog.text = "¿Eh? ¿Qué? ¡Maldita sea!";
		link.l1 = "";
		link.l1.go = "marshe_lay_2";
		break;

	case "marshe_lay_2":
		DialogExit();
		LAi_SetgroundSitType(npchar);
		NextDiag.currentnode = "marshe_sitground";
		break;

	case "marshe_sitground":
		PlaySound("Voice\Spanish\EvilPirates07.wav");
		dialog.text = "¡Aaah! ¿Quién eres tú? ¿Qué quieres de mí?";
		link.l1 = "Si no te callas, te romperé los dientes, ¿entiendes? ¿Dónde están los sagrados recipientes que agarraste cuando tomaste este barco?";
		link.l1.go = "marshe_sitground_1";
		break;

	case "marshe_sitground_1":
		dialog.text = "¿Tomar este barco? ¡No sé de qué estás hablando! ¡Este es mi barco!";
		link.l1 = "¿Tu barco? Hasta no hace mucho se llamaba 'Santa Margarita' y navegaba bajo la bandera española... Te pregunto, ¿dónde están esos santos recipientes? ¿Un ostensorio de oro, una cruz incrustada con lazurita y un incensario de oro? ¿Qué hiciste con ellos? No los vendiste, ¿verdad?";
		link.l1.go = "marshe_sitground_2";
		break;

	case "marshe_sitground_2":
		dialog.text = "¡Oh Dios, no creo lo que oigo!.. ¿eres español? ¡Oh, no... no eres español! ¡Eres francés! ¡Eso es aún peor! ¡Te has vendido a esos viles castellanos! ¿Cuánto están pagando por las almas de los franceses estos días? ¡No te diré nada, traidor! ¡No pondrás tus manos en esas baratijas!";
		link.l1 = "No sueltas palabra ¿eh? Eso me parece bien. Este no es el mejor lugar para interrogar de todos modos... Te vamos a amordazar para que no chilles y luego iremos a mi bote... eventualmente hablarás, camarada. No tengo duda de eso.";
		link.l1.go = "marshe_sitground_3";
		break;

	case "marshe_sitground_3":
		dialog.text = "¡Traidor español! Más te vale...";
		link.l1 = "Silencio, canalla... Sígueme de cerca o te derribaré y te arrastraré por la cubierta de los pies.";
		link.l1.go = "marshe_sitground_4";
		break;

	case "marshe_sitground_4":
		DialogExit();
		RemoveAllCharacterItems(npchar, true);
		ChangeCharacterAddressGroup(npchar, "Deck_Galeon_Ship", "goto", "stand");
		LAi_SetActorType(npchar);
		LAi_ActorFollow(npchar, pchar, "", -1);
		pchar.quest.GuardOT_marchfromgaleon.win_condition.l1 = "locator";
		pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.location = "Deck_Galeon_Ship";
		pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator_group = "reload";
		pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator = "reload2";
		pchar.quest.GuardOT_marchfromgaleon.function = "GuardOT_ExitGaleon";
		break;

	// капитан каракки - Карлос Геварра
	case "gevarra":
		dialog.text = "¿Cómo puedo ayudarle, señor?";
		link.l1 = "¿Cómo van las cosas, capitán? ¿Qué le trae a Basse-Terre? Según tengo entendido, ¿es usted un español que navega bajo la bandera holandesa?";
		link.l1.go = "gevarra_1";
		break;

	case "gevarra_1":
		dialog.text = "¿Cuál es el problema, señor? Sí, soy español. Es fácil adivinarlo por el nombre y el tipo de mi barco, pero estoy aquí de manera bastante legal. Tengo una licencia de la Compañía Holandesa de las Indias Occidentales, así que...";
		link.l1 = "¡No te pongas nervioso, señor! En realidad estamos muy contentos de que seas español... Dime, ¿estás aquí para importar o exportar?";
		link.l1.go = "gevarra_2";
		break;

	case "gevarra_2":
		dialog.text = "He traído mercancía de La Habana y la he vendido en el mercado. Ahora, estoy esperando un transporte lucrativo para evitar navegar de regreso con la bodega vacía.";
		link.l1 = "¡Señor, tengo una propuesta de negocio para usted! Podría ganar buen dinero si me ayuda. ¿Lo discutimos? ¿Cómo se llama, por cierto?";
		link.l1.go = "gevarra_3";
		break;

	case "gevarra_3":
		dialog.text = "Carlos. Capitán Carlos Guevara. ¿Cuál es tu oferta?";
		link.l1 = "Necesito comprar un lote de vainilla y enviarlo a Cuba, a un hombre llamado " + pchar.questTemp.Guardoftruth.LMname + ", el vigilante del faro de Santiago. Sin embargo, tengo un problema serio. En primer lugar, ninguna tienda tiene la cantidad de vainilla que necesito...";
		link.l1.go = "gevarra_4";
		break;

	case "gevarra_4":
		dialog.text = "";
		link.l1 = "En segundo lugar, debo partir inmediatamente hacia Saint Christopher, y no sé cuánto tiempo estaré fuera. Estoy perdiendo dinero cada día, ¿entiendes? ¡Es una maldita vergüenza!";
		link.l1.go = "gevarra_5";
		break;

	case "gevarra_5":
		dialog.text = "Entiendo. Qué lástima, señor. No se puede ganar todo el dinero del mundo, al fin y al cabo. Entonces, ¿qué quieres de mí?";
		link.l1 = "Mira por allí. ¿Ves ese galeón? Está cargado de vainilla que necesito con urgencia. El problema es que el capitán del galeón se ha metido en la cabeza unas tonterías sobre una caravana de especias que llegará aquí pronto, y comprará su carga con ganancia, ¡a casi trescientos pesos por caja!";
		link.l1.go = "gevarra_6";
		break;

	case "gevarra_6":
		dialog.text = "Sí, hay muchos hombres ingenuos por aquí estos días, un tonto y su dinero pronto se separan...";
		link.l1 = "Ingenuo es una cosa, ¡pero es completamente imbécil! Le ofrecí comprar su vainilla por doscientos diez pesos, ni siquiera sacaría doscientos en una tienda aquí. Y, ¿puedes creerlo? ¡Me dijo que me largara! Dijo que solo la vendería a doscientos cincuenta.";
		link.l1.go = "gevarra_7";
		break;

	case "gevarra_7":
		dialog.text = "¡Ja ja! ¡Qué idiota!";
		link.l1 = "¡Sí! Básicamente eso le dije. Por supuesto, se enojó conmigo... pero realmente necesito esa vainilla. Aquí está mi propuesta, señor. No soy un comerciante, pero creo que usted es un verdadero maestro del arte del trato. Y tiene una bodega espaciosa...";
		link.l1.go = "gevarra_8";
		break;

	case "gevarra_8":
		dialog.text = "";
		link.l1 = "Haz que este maldito tonto te venda la carga. No me la va a vender a mí ahora, después de que lo insulté en su cara. Estoy dispuesto a pagar doscientos diez pesos por caja. Si logras bajar el precio, quédate con la diferencia. Y por eso alquilaré tu barco para entregar la vainilla a Santiago.";
		link.l1.go = "gevarra_9";
		break;

	case "gevarra_9":
		dialog.text = "¿Cuánto estás dispuesto a pagarme por el envío?";
		link.l1 = "¿Cuánto quieres?";
		link.l1.go = "gevarra_10";
		break;

	case "gevarra_10":
		dialog.text = "Santiago está bastante lejos...treinta mil pesos.";
		link.l1 = "Eso es demasiado, amigo. Encuéntrame a mitad de camino aquí.";
		link.l1.go = "gevarra_11";
		break;

	case "gevarra_11":
		dialog.text = "De acuerdo, está en mi camino de todos modos... Veinticinco mil y ni un peso menos.";
		link.l1 = "Está bien. El capitán del galeón se llama Gaius Marchais. Pasa todo el día refunfuñando en la taberna. Espero que logres convencerlo de desprenderse de sus especias.";
		link.l1.go = "gevarra_12";
		break;

	case "gevarra_12":
		dialog.text = "He hecho negocios con imbéciles más grandes antes. Le contaré todos los detalles sobre quién está difundiendo los rumores sobre la caravana que supuestamente iba a comprar la mercancía a precios exorbitantes. Una vez que lo convenza de que todo es producto de su imaginación, venderá, estoy seguro de ello.";
		link.l1 = "Entonces, ¿tenemos un trato?";
		link.l1.go = "gevarra_13";
		break;

	case "gevarra_13":
		iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty) * 210 + 25000;
		dialog.text = "Tenemos un trato si tienes el dinero para pagar la vainilla y el envío. Como dice el encantador dicho irlandés: 'Muéstrame el dinero.'";
		if (sti(Pchar.money) >= iTemp)
		{
			link.l1 = "Aquí tienes, echa un vistazo. Todo está aquí.";
			link.l1.go = "gevarra_14";
		}
		else
		{
			link.l1 = "Tengo la plata en mi barco. ¡Iré a buscarla y volveré enseguida!";
			link.l1.go = "gevarra_14_no";
		}
		break;

	case "gevarra_14_no":
		DialogExit();
		NextDiag.currentnode = "gevarra_wait";
		npchar.DeckDialogNode = "gevarra_wait";
		break;

	case "gevarra_wait":
		iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty) * 210 + 25000;
		dialog.text = "¿Has traído el dinero?";
		if (sti(Pchar.money) >= iTemp)
		{
			link.l1 = "Aquí tienes, echa un vistazo. Está todo aquí.";
			link.l1.go = "gevarra_14";
		}
		else
		{
			link.l1 = "¡Lo estoy consiguiendo ahora mismo!";
			link.l1.go = "exit";
		}
		break;

	case "gevarra_14":
		if (stf(environment.time) < 24.0)
		{
			sTemp = "mañana";
			iTemp = 1;
		}
		else
		{
			sTemp = "hoy";
			iTemp = 0;
		}
		if (stf(environment.time) > 21.0 && stf(environment.time) < 7.0)
		{
			dialog.text = "¡Estupendo! Disfruto haciendo negocios con socios sensatos. Vuelve " + sTemp + " para las diez de la mañana. Creo que para ese momento nuestro amigo mutuo Gaius habrá recuperado el sentido.";
			link.l1 = "¡Genial! ¡Nos vemos más tarde!";
			link.l1.go = "gevarra_15";
			pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour = 10.0;
			pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day = GetAddingDataDay(0, 0, iTemp);
			pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
			pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year = GetAddingDataYear(0, 0, iTemp);
			pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
		}
		else
		{
			dialog.text = "¡Estupendo! Disfruto hacer negocios con socios sensatos. Me voy a la orilla. Vuelve en tres horas. Creo que para ese momento nuestro amigo mutuo Gaius habrá entrado en razón...";
			link.l1 = "¡Genial! ¡Nos vemos más tarde!";
			link.l1.go = "gevarra_15";
			pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour = sti(GetTime() + 3);
			pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
		}
		break;

	case "gevarra_15":
		iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty) * 210 + 25000;
		DialogExit();
		NextDiag.currentnode = "gevarra_time";
		npchar.DeckDialogNode = "gevarra_time";
		AddMoneyToCharacter(pchar, -iTemp); // деньги сразу списываем
		bQuestDisableMapEnter = true;
		pchar.GenQuest.MapClosedNoBattle = true;
		AddQuestRecord("Guardoftruth", "17");
		AddCharacterExpToSkill(pchar, "Sneak", 50);
		break;

	case "gevarra_time":
		dialog.text = "Señor, recuerdo bien mi papel. No se preocupe, puede que sea un hueso duro de roer, pero lo haré hablar.";
		link.l1 = "Gracias.";
		link.l1.go = "exit";
		NextDiag.TempNode = "gevarra_time";
		break;

	case "gevarra_16":
		dialog.text = "Está hecho, señor. El pobre hombre estaba encantado de que quisiera comprar su vainilla. Sus manos temblaban de felicidad mientras contaba un adelanto, o tal vez eso era solo por el ron. Cargaremos la mercancía en la playa de Capster al mediodía de mañana, para evitar cualquier atención no deseada de los agentes de aduana en el puerto.\nZarparé inmediatamente hacia Santiago tan pronto como tenga la carga a bordo. Contactaré a su socio en el faro, y le entregaré la vainilla después de la entrega allí. ¿Algún mensaje que quiera que le transmita?";
		link.l1 = "Sí. Aquí tienes una carta. ¿Dices que el trato será en la Playa Capster mañana al mediodía? Muy bien, entonces, fondearé justo frente al cabo, inaccesible desde la isla por si acaso ocurre algo.";
		link.l1.go = "gevarra_17";
		break;

	case "gevarra_17":
		Log_Info("¡Entregaste la carta!");
		PlaySound("interface\important_item.wav");
		dialog.text = "Puedes confiar en mí, señor. Soy un hombre honesto. Además, no tengo deseo de pelear contigo, y un comerciante no es nada sin su reputación. Pero si deseas observar y verificar, no es un problema para mí.";
		link.l1 = "Estoy agradecido, señor. Vigilaré el trato mañana, y tan pronto como zarpen, me ocuparé de mis asuntos en Saint-Christopher.";
		link.l1.go = "gevarra_18";
		break;

	case "gevarra_18":
		DialogExit();
		NextDiag.currentnode = "gevarra_exit";
		npchar.DeckDialogNode = "gevarra_exit";
		bQuestDisableMapEnter = true;
		pchar.GenQuest.MapClosedNoBattle = true;
		pchar.GenQuest.CannotWait = true; // запрет ожидания
		AddQuestRecord("Guardoftruth", "18");
		pchar.quest.GuardOT_gotoshore.win_condition.l1 = "ExitFromSea";
		pchar.quest.GuardOT_gotoshore.function = "GuardOT_TradeComplete";
		break;

	case "gevarra_exit":
		dialog.text = "Capitán, le aseguro: no le fallaré y cumpliré las condiciones de nuestro trato en su totalidad.";
		link.l1 = "... ";
		link.l1.go = "exit";
		NextDiag.TempNode = "gevarra_exit";
		break;

	// матросы Марше
	case "marshe_sailor":
		dialog.text = LinkRandPhrase("¡Hip! ¡H-hurra! ¡El buen capitán por fin nos dio nuestro pago! ¡Tres hurras por el capitán! ¡Hip!", "¿Viene en pintas? ¡Me llevo una!", "¡Que nuestras bolsas estén llenas y nuestras mozas aún más! ¡Hurra!", "¡Y allí yacen, todos buenos hombres muertos, hip! Como el amanecer en una taberna de borrachos. ¡Yo-ho-ho y una botella de ron!", "¡Yo-ho-ho y una botella de ron!");
		link.l1 = LinkRandPhrase("Sí, colega.", "¿No crees que ya has tomado suficiente ron?", "A beber, el diablo se han encargado del resto...");
		link.l1.go = "exit";
		break;

	case "galeonguard":
		PlaySound("Voice\Spanish\EvilPirates01.wav");
		dialog.text = "¡A las armas! ¡Alto! ¡Alarma! ¡Repelan abordajes!";
		link.l1 = "...";
		link.l1.go = "galeonguard_1";
		break;

	case "galeonguard_1":
		DialogExit();
		DeleteAttribute(pchar, "GenQuest.CantRun");
		CheckAndSetOverloadMode(GetMainCharacter());
		DeleteAttribute(pchar, "questTemp.Guardoftruth.Attack");
		LAi_RemoveCheckMinHP(pchar);
		GuardOT_GaleonGuardFightAdd();
		for (i = 1; i <= 8; i++)
		{
			sld = characterFromId("GuardOT_galeonguard_" + i);
			LAi_SetWarriorTypeNoGroup(sld);
			LAi_group_MoveCharacter(sld, "GaleonFight");
		}
		LAi_group_FightGroups("GaleonFight", LAI_GROUP_PLAYER, true);
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	// англичане в бухте
	case "dominica_hunter":
		dialog.text = "¡Har-har! ¿También vienes por el tesoro de Rollie el Cap, eh? Hemos estado buscando y buscando, y buscando, y simplemente no pudimos encontrarlo. ¡Ojalá al menos uno de estos imbéciles adivinara nadar detrás de la cascada hasta la saliente!";
		link.l1 = "Eres uno de los hombres del Coronel Fox, ¿verdad?";
		link.l1.go = "dominica_hunter_1";
		break;

	case "dominica_hunter_1":
		dialog.text = "Puede que tenga lazos con los Sea Foxes. No necesitas saber, no tiene sentido. No necesitas saber nada ahora mismo. Has encontrado mi tesoro, por lo cual te debemos un gran agradecimiento...";
		link.l1 = "Ya veo. No eres un Sea Fox, más bien un perro marino... o chacal. ¿Qué te queda mejor?";
		link.l1.go = "dominica_hunter_2";
		break;

	case "dominica_hunter_2":
		dialog.text = "¡Parece que tenemos un filósofo natural entre nosotros, muchachos. Un verdadero experto en el reino animal!";
		link.l1 = "¿Quieres inspeccionar la agudeza de mi sable, chacal?";
		link.l1.go = "dominica_hunter_3";
		break;

	case "dominica_hunter_3":
		DialogExit();
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		for (i = 1; i <= 8; i++)
		{
			sld = characterFromId("GuardOT_DH_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "GuardOT_HuntersDie");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	// Белинда Риберо
	case "belinda":
		dialog.text = TimeGreeting() + ", señor. ¿Cómo puedo ayudarle?";
		link.l1 = "Hola. ¿Eres Donna Belinda de Ribero?";
		link.l1.go = "belinda_1";
		break;

	case "belinda_1":
		dialog.text = "Sí, lo soy. ¿Con quién tengo el honor de hablar?";
		link.l1 = "Capitán " + GetFullName(pchar) + ", señora. Por favor, no se deje intimidar por mi apellido francés, en este momento estoy cumpliendo una asignación del Reverendo Inquisidor de Santiago, el Padre Vincento.";
		link.l1.go = "belinda_2";
		break;

	case "belinda_2":
		dialog.text = "¡Qué interesante! He oído que el Santo Tribunal y la Compañía de Jesús están llenos de una gran multitud de personas, de todas clases y nacionalidades, pero nunca había conocido personalmente a un extranjero que trabajara para ellos hasta ahora. ¿Qué puedo hacer por usted, señor?";
		link.l1 = "Posees un objeto que al Reverendo Padre le interesa mucho. Un ostensorio dorado, una custodia que has adquirido recientemente del banquero en Willemstad.";
		link.l1.go = "belinda_3";
		break;

	case "belinda_3":
		dialog.text = "Estás muy bien informado, señor. Bueno, sabiendo para quién trabajas, esto no debería sorprenderme. Sí, compré el ostensorio, ciertamente no debería haberse quedado en la tienda de un comerciante junto a baratijas robadas, y mercancías empeñadas como si fuera una chuchería sin valor.";
		link.l1 = "¿Tiene la custodia, señora?";
		link.l1.go = "belinda_4";
		break;

	case "belinda_4":
		dialog.text = "Sí. Tenía la intención de regalarlo a nuestra iglesia parroquial, pero tanto ha caído sobre mí aquí... No pude... oh, lo siento...";
		link.l1 = "¿Está llorando, señora? ¿Mis palabras le han causado pesar? Si es así, le ruego que me perdone.";
		link.l1.go = "belinda_5";
		break;

	case "belinda_5":
		dialog.text = "Oh, por favor, señor... Regresemos a nuestra conversación. Según entiendo, ¿el Padre Vincento necesita esta custodia? ¿Te gustaría que te la entregue?";
		link.l1 = "Esta preciada vasija estaba destinada a la catedral de Santiago, pero fue capturada por un pirata común y vendida a un usurero junto con varios otros objetos sagrados. Mi tarea es devolver lo que fue robado a donde pertenece. Por supuesto, le compensaré completamente por sus gastos.";
		link.l1.go = "belinda_6";
		break;

	case "belinda_6":
		dialog.text = "¡Oh, no debes hacerlo! ¿Realmente crees que este dinero significa tanto para mí? Compré este ostensorio para la Santa Madre Iglesia y no dudaré en entregarlo a su verdadero dueño, ni siquiera por mencionar a un miembro de la Compañía de Jesús al servicio del Padre Vincento. Pero, otra cosa me preocupa profundamente. ¿Podrías ayudar a una fiel hija de la Iglesia en su necesidad?";
		link.l1 = "Eres una dama noble, señora. ¿Qué problemas le preocupan? ¿Cómo puedo ayudarla?";
		link.l1.go = "belinda_7";
		break;

	case "belinda_7":
		dialog.text = "¡Oh, pero señor... No me atrevería a pedirle ayuda a un hermano jesuita en persona. Siempre están tan ocupados...";
		link.l1 = "Ya lo hiciste. ¿Qué pasa?";
		link.l1.go = "belinda_8";
		break;

	case "belinda_8":
		dialog.text = "¿Puedes prometerme, como representante de la Santa Iglesia, que nadie jamás descubrirá lo que te estoy pidiendo?";
		link.l1 = "Le doy mi solemne juramento, señora. No es el sello del confesionario, pero no diré una palabra de esto a ninguna alma.";
		link.l1.go = "belinda_9";
		break;

	case "belinda_9":
		dialog.text = "Muy bien. Confío en ti. Mi muy querido amigo Esteban Sosa se ha metido en problemas. Fue capturado por bandidos mientras viajaba, y exigen un rescate de cien mil pesos. No poseo tanto dinero, y solo logré reunir aproximadamente la mitad de la suma de mis ahorros. No puedo pedir ayuda a nadie en tal asunto porque juraron que lo matarían si lo hacía.\nAdemás, me preocupo por mi querido... amigo, y temo lo peor. Podrían matarlo tan pronto como reciban el dinero para asegurarse de que no les cuente a los guardias sobre ellos. Tal vez tú, un valiente capitán, un cristiano y un hermano de la Sociedad, podrías persuadir a los bandidos de aceptar el dinero que tengo, y no hacerle daño...";
		link.l1 = "¿Cuándo y dónde se llevará a cabo el intercambio?";
		link.l1.go = "belinda_10";
		break;

	case "belinda_10":
		dialog.text = "Su cabecilla es un hombre llamado Bartie el Destripador. Dijo que esperaría el rescate de Esteban cada noche desde las once de la noche hasta la medianoche en la entrada de la cueva en la jungla...";
		link.l1 = "Esas son condiciones inusualmente específicas...";
		link.l1.go = "belinda_11";
		break;

	case "belinda_11":
		dialog.text = "Aparentemente querían que reuniera todo el rescate rápidamente, y no querían que pidiera ayuda a nadie... pero no puedo encontrar tanto dinero, ¡nunca podré hacerlo!";
		link.l1 = "No llore, señora. Intentaré ayudarla. Un hermano de la Sociedad de Jesús nunca dejaría a una mujer cristiana justa en peligro.";
		link.l1.go = "belinda_12";
		break;

	case "belinda_12":
		dialog.text = "Debo poner mi fe en ti... Pero capitán, Bartie el Destripador también dijo que si el portador del rescate no viene solo o si voy a los guardias, ¡inmediatamente matará al pobre Esteban!";
		link.l1 = "Tendré eso en cuenta.";
		link.l1.go = "belinda_13";
		break;

	case "belinda_13":
		dialog.text = "Aquí, toma esto. Son los cincuenta mil pesos que pude reunir. Convence a esos bandidos de que acepten al menos esto. ¡Diles que no tengo un solo peso más! ¡Trae de vuelta a Esteban! Una vez que lo hagas, con gusto te daré la ostensorio para el Padre Vincento.";
		link.l1 = "Haré todo lo que pueda, señora. Esperemos lo mejor.";
		link.l1.go = "belinda_14";
		break;

	case "belinda_14":
		dialog.text = "¡Que Dios te ayude, valiente capitán! ¡Rezaré por ti!";
		link.l1 = "...";
		link.l1.go = "belinda_15";
		break;

	case "belinda_15":
		AddMoneyToCharacter(pchar, 50000);
		DialogExit();
		NextDiag.CurrentNode = "belinda_16";
		AddQuestRecord("Guardoftruth", "31");
		bQuestDisableMapEnter = true;											 // закрыть карту
		locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = true; // энкаутеры закрыть
		LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", true);
		LAi_LocationDisableOfficersGen("Cumana_Cave", true);
		pchar.quest.GuardOT_gotocave.win_condition.l1 = "location";
		pchar.quest.GuardOT_gotocave.win_condition.l1.location = "Cumana_CaveEntrance";
		pchar.quest.GuardOT_gotocave.win_condition.l2 = "HardHour";
		pchar.quest.GuardOT_gotocave.win_condition.l2.hour = 23.00;
		pchar.quest.GuardOT_gotocave.function = "GuardOT_InCaveEntrance";
		break;

	case "belinda_16":
		dialog.text = "¿Tienes alguna noticia, capitán?";
		link.l1 = "Aún no. Sólo espere, señora. No le fallaré.";
		link.l1.go = "exit";
		NextDiag.TempNode = "belinda_16";
		break;

	case "belinda_17":
		dialog.text = "¿Tienes alguna noticia, capitán?";
		link.l1 = "Sí, señora. Me temo que no son buenas noticias.";
		link.l1.go = "belinda_18";
		break;

	case "belinda_18":
		dialog.text = "¡Dime, no me hagas esperar! ¿Te encontraste con los bandidos?";
		if (sti(Pchar.money) >= 50000)
		{
			link.l1 = "Aquí, toma tus cincuenta mil de vuelta. No los necesitaba. Toma también este anillo. Creo que te resultará familiar.";
			link.l1.go = "belinda_19_1";
		}
		link.l2 = "Aquí, toma este anillo. Creo que lo encontrarás familiar.";
		link.l2.go = "belinda_19_2";
		break;

	case "belinda_19_1":
		RemoveItems(pchar, "jewelry29", 1);
		PlaySound("interface\important_item.wav");
		AddMoneyToCharacter(pchar, -50000);
		dialog.text = "Eso... sí, es familiar. ¿Qué le pasó a Esteban?";
		link.l1 = "He encontrado a los bandidos en la cueva, como me dijiste. 'Bartie el Destripador' y Esteban Sosa son el mismo hombre. Él organizó el secuestro para extorsionarte. Me habló de tu... relación. También dijo que no quiere verte más. Tomé el anillo que le diste como prueba.";
		link.l1.go = "belinda_20";
		break;

	case "belinda_19_2":
		dialog.text = "Esto... sí, sí lo sé. ¿Qué le pasó a Esteban?";
		link.l1 = "Encontré a los bandidos en la cueva, como me dijiste. Me atacaron, me ataron y se llevaron tu dinero. 'Bartie el Destripador' y Esteban Sosa son el mismo hombre. Escenificó el secuestro para extorsionarte. Me habló sobre tu... relación. Esteban me dejó ir y me dio este anillo como prueba. Dijo que nunca volverás a verlo.";
		link.l1.go = "belinda_20";
		npchar.quest.nomoney = true;
		break;

	case "belinda_20":
		if (CheckAttribute(npchar, "quest.nomoney"))
			sTemp = "";
		else
			sTemp = "Le di una lección, pero no lo maté por respeto a ti.";
		dialog.text = "¡Dios mío! ¡No creo lo que oigo! ¿Por qué me pasa todo esto a mí? ¿Por qué? ¿Qué hice yo para que él...?";
		link.l1 = "Señora, le suplico, no se atormente por esto. Ese bribón no vale ni una sola de sus lágrimas. " + sTemp + "";
		link.l1.go = "belinda_21";
		break;

	case "belinda_21":
		if (CheckAttribute(npchar, "quest.nomoney"))
			sTemp = "";
		else
			sTemp = "Y además, aquí tienes un regalo para que te animes.";
		dialog.text = "Ah... Intentaré calmarme. Señor, debo agradecerle por su ayuda. Aquí, tome su ostensorio. " + sTemp + "Vaya con Dios.";
		link.l1 = "Gracias, señora. No se preocupe, nadie se enterará de lo que sucedió en la cueva. Nosotros, los jesuitas, siempre cumplimos nuestra palabra. Ahora, si me permite, debo irme.";
		link.l1.go = "belinda_22";
		break;

	case "belinda_22":
		DialogExit();
		AddQuestRecord("Guardoftruth", "33");
		bQuestDisableMapEnter = false;
		DeleteAttribute(pchar, "GenQuest.CannotWait");
		LAi_CharacterDisableDialog(npchar);
		npchar.lifeday = 3;
		GiveItem2Character(pchar, "jewelry33");
		Log_Info("¡Has recibido un ostensorio de oro!");
		PlaySound("interface\important_item.wav");
		if (CheckAttribute(npchar, "quest.nomoney"))
		{
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			OfficersReaction("bad");
		}
		else
		{
			Log_Info("¡Has recibido un amuleto!");
			GiveItem2Character(pchar, "amulet_7");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
			ChangeCharacterNationReputation(pchar, SPAIN, 3);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		}
		break;

	// бандит Эстебана
	case "bandos_mush":
		PlaySound("Voice\Spanish\EvilPirates08.wav");
		dialog.text = "¡Alto ahí, camarada!";
		link.l1 = "Estoy parado justo aquí.";
		link.l1.go = "bandos_mush_1";
		break;

	case "bandos_mush_1":
		dialog.text = "¿Trajiste el dinero?";
		link.l1 = "Qué pregunta tan tonta. No, estoy aquí recogiendo Manga Rosa... ¿Por qué más crees que habría venido aquí?";
		link.l1.go = "bandos_mush_2";
		break;

	case "bandos_mush_2":
		dialog.text = "¡Oh-ho-ho! ¡Un comediante! Anda a la cueva, Bartie te ha estado esperando.";
		link.l1 = "Eres claramente un guardia experimentado... con esa actitud serías apto para proteger al mismísimo Rey Felipe. Me presentaré yo mismo.";
		link.l1.go = "bandos_mush_3";
		break;

	case "bandos_mush_3":
		DialogExit();
		chrDisableReloadToLocation = false; // открыть локацию
		LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", true);
		LAi_SetWarriorType(npchar);
		LAi_CharacterDisableDialog(npchar);
		pchar.GenQuest.CannotWait = true; // запрет ожидания
		pchar.quest.GuardOT_incave.win_condition.l1 = "location";
		pchar.quest.GuardOT_incave.win_condition.l1.location = "Cumana_Cave";
		pchar.quest.GuardOT_incave.function = "GuardOT_InCumanaCave";
		break;

	// Эстебан-Барти
	case "barty":
		PlaySound("Voice\Spanish\EvilPirates04.wav");
		dialog.text = "Me hiciste esperar... ¿Tienes el dinero contigo?";
		link.l1 = "¿Eres Bartie el Destripador? No pareces un bandido común para mí.";
		link.l1.go = "barty_1";
		break;

	case "barty_1":
		dialog.text = "¿Por qué te importa cómo me veo? ¿Tienes el maldito dinero o no?";
		link.l1 = "¿Dónde está el rehén?";
		link.l1.go = "barty_2";
		break;

	case "barty_2":
		dialog.text = "Obtendrás a tu rehén. Vamos, dame el dinero. No me hagas enfadar, muchacho.";
		link.l1 = "Bartie, ¿tengo pinta de ser un tonto? Hasta que vea a Esteban Sosa vivo y coleando, no vas a ver un solo peso. ¿Dónde está?";
		link.l1.go = "barty_3";
		break;

	case "barty_3":
		dialog.text = "¡Oh!, te estás empecinando, ¿eh? Muy bien, vamos a darte una buena lección... ¡Muchachos, vamos a hacerle a este indeseable un nuevo agujero!";
		link.l1 = "¡Bastardo!";
		link.l1.go = "barty_4";
		break;

	case "barty_4":
		DialogExit();
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		GuardOT_InCumanaCaveEnemyAdd();
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		for (i = 1; i <= 2; i++)
		{
			sld = characterFromId("GOT_bandos_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "GuardOT_CumanaCaveBandosDie");
		AddDialogExitQuest("MainHeroFightModeOn");
		// офицеров насильно
		LAi_LocationDisableOfficersGen("Cumana_Cave", false); // офицеров пускать
		DoQuestFunctionDelay("GuardOT_SetOfficerCumanaCave", 3.0);
		break;

	case "barty_5":
		PlaySound("Voice\Spanish\EvilPirates06.wav");
		dialog.text = "";
		link.l1 = "¿Ya es suficiente baile para ti? ¿Dónde está Esteban Sosa? ¡Vamos, dímelo o te mantendré la cabeza bajo el agua hasta que las burbujas se detengan!";
		link.l1.go = "barty_6";
		break;

	case "barty_6":
		dialog.text = "¡No... No me hagas daño, por favor! Soy Esteban Sosa.";
		link.l1 = "¿Qué?";
		link.l1.go = "barty_7";
		break;

	case "barty_7":
		dialog.text = "Sí, sí. No soy Bartie el Destripador. Solo soy...";
		link.l1 = "¡Canalla! ¿Así que decidiste sacarle cien mil pesos a la señora de Ribero 'secuestrándote' a ti mismo?!";
		link.l1.go = "barty_8";
		break;

	case "barty_8":
		dialog.text = "Necesitas entenderme, de hombre a hombre. Belinda... ¡De verdad me tiene harto con su amor obsesivo! ¡Está todo el tiempo encima de mí, día y noche, hombre! ¡Incluso su marido empezó a sospechar de nosotros y está medio ciego!";
		link.l1 = "¡Vaya, qué sorpresa! ¿Entonces son amantes?";
		link.l1.go = "barty_9";
		break;

	case "barty_9":
		dialog.text = "Ya no más. Acabo de huir de ella.";
		link.l1 = "Y decidiste llevarte algunas monedas para el camino, ¿eh? Bueno, ¿qué debería hacer contigo ahora? ¿Esconder tu cuerpo en la jungla como intentaste hacer conmigo?";
		link.l1.go = "barty_10";
		break;

	case "barty_10":
		dialog.text = "¡No! ¡No quería derramar sangre, lo juro!";
		link.l1 = "¿Es por eso que me lanzaste a tus perros?";
		link.l1.go = "barty_11";
		break;

	case "barty_11":
		dialog.text = "¡Solo íbamos a vaciar tus bolsillos, eso es todo!";
		link.l1 = "¿Y dejarme desnudo en la selva? ¡Debería colgarte del palo mayor de mi barco, bribón! Pero no haré eso, solo por respeto a la buena mujer que tuvo la desgracia de enredarse contigo. ¿Sabes qué? Debería llevarte a ella, y dejar que ella decida qué hacer contigo.";
		link.l1.go = "barty_12";
		break;

	case "barty_12":
		dialog.text = "¡No, cualquier cosa menos eso! ¡No voy a volver a Cumaná!";
		link.l1 = "¿Preferirías quedarte en esta cueva para siempre?";
		link.l1.go = "barty_13";
		break;

	case "barty_13":
		dialog.text = "¡Perdóname, señor! ¡Déjame ir y zarparé lejos de aquí y nunca volveré a Cumana! ¡No voy a esperar a que el esposo de Belinda me haga pedazos en un duelo, o envíe un asesino tras de mí!";
		link.l1 = "Está bien. Por el bien de la Señora de Ribero, no voy a llevarte a ella. Pero no pienses ni por un segundo que todo esto va a quedar oculto. Ella va a descubrir el patético pedazo de mierda con el que decidió coquetear. ¿Qué cosa tienes que ella pueda reconocer?";
		link.l1.go = "barty_14";
		break;

	case "barty_14":
		dialog.text = "Aquí. Este anillo de turquesa. Ella misma me lo dio.";
		link.l1 = "Perfecto. ¡Dámelo y sal de mi vista!";
		link.l1.go = "barty_15";
		// belamour legendary edition -->
		link.l2 = "Perfecto. Y sabes, Sosa, he cambiado de opinión. Ahora sirvo a la Sociedad de Jesús. Como dicen las Escrituras, 'Debes expulsar al malvado de entre vosotros.' Y tú eres un narcisista malvado, un criminal, y un pedazo de mierda inútil. Creo que te ahogaré en esta cueva. Requiescat in pace.";
		link.l2.go = "barty_15a";
		break;

	case "barty_15a":
		DialogExit();
		GiveItem2Character(pchar, "jewelry29");
		Log_Info("¡Has recibido un anillo con turquesa!");
		PlaySound("interface\important_item.wav");
		LAi_SetActorType(pchar);
		// если не надет пистоль или мушкет, то выдадим строевой -->
		if (!CheckAttribute(pchar, "equip." + GUN_ITEM_TYPE) || !CheckAttribute(pchar, "equip." + MUSKET_ITEM_TYPE))
		{
			GiveItem2Character(pchar, "pistol1");
			EquipCharacterbyItem(pchar, "pistol1");
		}
		LAi_ActorAnimation(pchar, "Shot", "RIP_Sosa", 1.0);
		break;

	case "barty_15":
		DialogExit();
		ChangeCharacterComplexReputation(pchar, "nobility", 5);
		// <-- legendary edition
		GiveItem2Character(pchar, "jewelry29");
		Log_Info("¡Has recibido un anillo con turquesa!");
		PlaySound("interface\important_item.wav");
		chrDisableReloadToLocation = false;												  // открыть локацию
		LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", false);					  // офицеров пускать
		locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = false;		  // энкаутеры открыть
		locations[FindLocation("Cumana_Cave")].DisableEncounters = false;				  // patch
		LAi_LocationFightDisable(&Locations[FindLocation("Cumana_CaveEntrance")], false); // разрешить драться
		DeleteAttribute(pchar, "GenQuest.CannotWait");									  // можно мотать время
		LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", false);
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
		npchar.lifeday = 0;
		sld = characterFromId("GOT_Belinda");
		sld.dialog.currentnode = "Belinda_17";
		AddQuestRecord("Guardoftruth", "32");
		break;

	// охотники
	case "spa_hunter":
		dialog.text = "Tienes lo que necesitamos, compañero...";
		link.l1 = "¿De verdad? ¿Y qué sería eso?";
		link.l1.go = "spa_hunter_1";
		break;

	case "spa_hunter_1":
		dialog.text = "No pregunté, niño rico. Solo me han ordenado tomar tus pertenencias, absolutamente todo lo que llevas contigo. ¿Lo haremos por las buenas o por las malas? La elección es tuya.";
		link.l1 = "Crees que eres un guerrero, ¿eh? No tienes ni idea de con quién te estás enfrentando. Me como a escoria como tú para desayunar.";
		link.l1.go = "spa_hunter_2";
		break;

	case "spa_hunter_2":
		dialog.text = "Eres un verdadero bufón, ¿verdad, ranita? ¡Bueno, entonces, veamos cómo se ve tu sangre en el suelo!";
		link.l1 = "¡Se verá igual que el tuyo, idiota! ¡Déjame darte una lección de anatomía!";
		link.l1.go = "spa_hunter_3";
		break;

	case "spa_hunter_3":
		DialogExit();
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		for (i = 1; i <= 5; i++)
		{
			sld = characterFromID("GOT_santiagoband_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "GuardOT_SantiagoBandDie");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "cabin_hunter":
		dialog.text = "¡Ja ja, muy bien, camarada... Vacía tus bolsillos de inmediato! Si eres un buen muchacho y escuchas, te quedarás entero, ¿entendido?";
		link.l1 = "¡Maldita sea, ustedes otra vez? ¿También vinieron hasta aquí? ¡¿Quién demonios los contrató?!";
		link.l1.go = "cabin_hunter_1";
		break;

	case "cabin_hunter_1":
		dialog.text = "No es asunto tuyo. Ahora ríndete y vive, o lucha y simplemente tomaremos tu botín de tu cadáver. ¿Qué te parece ese trato?";
		link.l1 = "Tengo una contraoferta. ¿Qué tal si tomo tu botín de tu cadáver?";
		link.l1.go = "cabin_hunter_2";
		break;

	case "cabin_hunter_2":
		DialogExit();
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
		for (i = 1; i <= 2; i++)
		{
			sld = CharacterFromID("GOT_cabinband_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "GuardOT_CabinBandosDie");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	// командир абордажников
	case "batabano_officer":
		dialog.text = "¡Esperando órdenes, capitán!";
		link.l1 = "Muévanse a través de la jungla hacia el Cabo San Antonio. Tomen el sendero a la izquierda y sigan recto. Mantengan las cabezas bajas y prepárense para una emboscada en la orilla. Estén listos. Yo iré por mar y los encontraré allí. ¿Cuánto tiempo les tomará llegar allí?";
		link.l1.go = "batabano_officer_1";
		break;

	case "batabano_officer_1":
		dialog.text = "¡Estaremos allí en seis horas, capitán!";
		link.l1 = "Bien. ¡Adelante!";
		link.l1.go = "batabano_officer_2";
		break;

	case "batabano_officer_2":
		DialogExit();
		LocatorReloadEnterDisable("Shore13", "boat", false);
		for (i = 1; i <= 10; i++)
		{
			sld = characterFromID("GuardOT_Oursoldier_" + i);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 20.0);
		}
		AddQuestRecord("Guardoftruth", "48");
		// на мыс
		pchar.quest.GuardOT_sanantonio.win_condition.l1 = "Ship_location";
		pchar.quest.GuardOT_sanantonio.win_condition.l1.location = "Shore15";
		pchar.quest.GuardOT_sanantonio.function = "GuardOT_SanantonioArrive";
		// на время, специально для дебилов, не читающих диалоги и СЖ
		pchar.quest.GuardOT_sanantoniotimer.win_condition.l1 = "Timer";
		pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.hour = sti(GetTime() + 6);
		pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
		pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
		pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
		pchar.quest.GuardOT_sanantoniotimer.function = "GuardOT_SanAntonio_Timer";
		break;

	// наёмник Патерсона
	case "housemercen":
		dialog.text = "¡Bastardo tenaz! Todavía está vivo... ¡Sabía que deberíamos haber usado más pólvora! Está bien, te acabaré, hijo de mala madre...";
		link.l1 = "...";
		link.l1.go = "housemercen_1";
		break;

	case "housemercen_1":
		DialogExit();
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
		bDisableCharacterMenu = false;											   // разлочим F2
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		if (MOD_SKILL_ENEMY_RATE < 5)
			LAi_group_SetCheck("EnemyFight", "GuardOT_HouseMercenDie");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
