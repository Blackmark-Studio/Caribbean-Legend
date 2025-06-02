// Хосе Диос - картограф
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "¿Deseas algo?";
		if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "dios")
		{
			link.l3 = TimeGreeting() + "Dime, ¿eres José Dios, el cartógrafo?";
			link.l3.go = "island";
		}
		link.l1 = "No, nada.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "island":
		dialog.text = "Sí, soy yo. No te conozco, señor. ¿Qué quieres de mí?";
		link.l1 = "Mi nombre es " + GetFullName(pchar) + " y me envió Jan Svenson. ¿Lo recuerdas?";
		link.l1.go = "island_1";
		break;

	case "island_1":
		dialog.text = "¡Ah, señor Svenson! ¡Claro que lo recuerdo! Venga, póngase cómodo... ¿Cómo está el respetado Jan?";
		link.l1 = "Gracias, él está bien. Señor Dios, necesito su ayuda. Quiero consultarle sobre un asunto que debe conocer bien debido a su profesión. Jan le recomendó como un experto en geografía de la región del Caribe...";
		link.l1.go = "island_2";
		break;

	case "island_2":
		dialog.text = "Estoy escuchando, Señor. ¿Qué desea saber sobre la geografía del archipiélago?";
		link.l1 = "Dicen que hay una isla o algún otro tipo de formación al noroeste de La Habana, entre Cuba y el Golfo de México. Esta isla nunca ha sido trazada en ningún mapa. Me gustaría saber la fiabilidad de estos rumores.";
		link.l1.go = "island_3";
		break;

	case "island_3":
		dialog.text = "Hum... Has preguntado sobre algo que me inquieta desde hace muchos años. Este lugar que has mencionado ha estado atrayendo las mentes inquisitivas de los geógrafos durante mucho tiempo, pero nadie ha sido lo suficientemente valiente como para explorar esa región.";
		link.l1 = "¿Por qué?";
		link.l1.go = "island_4";
		break;

	case "island_4":
		dialog.text = "La cosa es que el lugar es una especie de anomalía natural. La probabilidad de tormentas en esa región es mucho mayor que en cualquier otro lugar. Tal vez la razón se encuentre en la corriente marina fría, pero esto es solo mi hipótesis. Muchos barcos han desaparecido allí y eso fue suficiente para que los marineros eviten ese lugar, de todos modos, todas las rutas marítimas principales pasan lejos de esa región.";
		link.l1 = "Tengo entendido que tú tampoco conoces la verdad...";
		link.l1.go = "island_5";
		break;

	case "island_5":
		dialog.text = "Exactamente, señor. Pero tengo un par de documentos históricos y algunas pruebas materiales, así que tengo todo el derecho de sospechar una alta probabilidad de la existencia de ese lugar.";
		link.l1 = "¿Puedes contarme más?";
		link.l1.go = "island_6";
		break;

	case "island_6":
		dialog.text = "Claro. La evidencia más importante es el documento histórico con extractos del diario del capitán Alvarado, quien visitó la Isla en 1620. ¡Te cuento una historia bastante interesante!";
		link.l1 = "¿Capitán Alvarado? Es la segunda vez que escucho ese nombre...";
		link.l1.go = "island_7";
		break;

	case "island_7":
		dialog.text = "No estoy sorprendido. La historia del capitán Alvarado ha sido parte del folclore durante años. Cambió, se llenó de rumores, mentiras y sueños, así que aquí está: la leyenda de la Isla de los Barcos Abandonados.\nEl chisme puede cambiar, pero el papel y la tinta no, permanecen intactos durante cientos de años. Aquí, lee esta historia, quizás te ayude a desvelar lo que buscas.";
		link.l1 = "¡Gracias! ¿Tienes algo más?";
		link.l1.go = "island_8";
		break;

	case "island_8":
		dialog.text = "Existe una teoría de que el fondo del mar en esa área se eleva lo suficiente como para formar un vasto bajío. Y ya he mencionado la corriente. También hay una gran acumulación de gaviotas y otras aves marinas según las charlas de los marineros.\nAlvorado mencionó nombres de barcos que formaban parte del escuadrón del almirante Francisco Betancourt, un escuadrón que se perdió hace más de cincuenta años. Dudo que esto sea solo una coincidencia...";
		link.l1 = "Regresaré a mi barco y leeré las notas de Alvarado con cuidado. ¡Gracias por tu ayuda, Señor Dios!";
		link.l1.go = "island_9";
		break;

	case "island_9":
		dialog.text = "De nada. En realidad, no te he ayudado en absoluto, no tienes las coordenadas del lugar y yo tampoco. Ni siquiera puedo probar que hay una isla habitada allí. Pero por lo que entiendo, ¿tienes la intención de explorar esta área?\nSi es así, entonces ten en cuenta que estaré realmente agradecido por cualquier información, especialmente si se proporciona con prueba material. Parece que eres un hombre adinerado, pero encontraré la manera de recompensarte.";
		link.l1 = "Bien. Entonces tenemos un trato, Señor Dios. Tal vez mis notas también sean leídas por alguien en el futuro... Y alguien podría incluso escribir una leyenda...";
		link.l1.go = "island_10";
		break;

	case "island_10":
		dialog.text = "¿Por qué no? Señor " + pchar.name + ", veo que eres un hombre aventurero que viaja mucho, así que quiero pedirte que hagas algo.";
		link.l1 = "¿Sí? Estoy escuchando.";
		link.l1.go = "island_11";
		break;

	case "island_11":
		dialog.text = "Sabes que soy cartógrafo. Así que he estado dibujando mapas del archipiélago caribeño durante dos años, compilando el atlas del almirante para el concurso del Vice Rey de Nueva Granada. Pero los veinticuatro mapas fueron robados de mi casa de la manera más insolente mientras fui capturado por piratas, aquellos de los que el señor Svenson me salvó.\nEstoy seguro de que el ataque fue organizado por uno de mis competidores para adquirir mis mapas. Ha pasado mucho tiempo, pero no he vuelto a ver ni un solo mapa de mi conjunto.";
		link.l1 = "Ya veo. Quieres que te devuelva tus mapas.";
		link.l1.go = "island_12";
		break;

	case "island_12":
		dialog.text = "Exactamente. Tal vez los encuentres durante tus futuras aventuras. Es fácil reconocerlos: mi signo está en cada uno de ellos. Te recompensaré generosamente si, milagrosamente, logras reunir los veinticuatro mapas.";
		link.l1 = "Está bien. Miraré atentamente cada mapa que encuentre en el archipiélago a partir de ahora. Bueno, tengo que irme ahora. Gracias por la interesante conversación y por el documento.";
		link.l1.go = "island_13";
		break;

	case "island_13":
		DialogExit();
		AddQuestRecordInfo("LSC_Alvorado", "1");
		AddQuestRecord("SharkHunt", "4");
		pchar.questTemp.Saga.SharkHunt = "LSC";
		NextDiag.CurrentNode = "Dios";
		AddCharacterExpToSkill(pchar, "Fortune", 50); // везение
		pchar.questTemp.AdmiralMap = "true";
		break;

	case "Dios":
		dialog.text = "¡Ah-ah, eres tú, señor " + GetFullName(pchar) + "¿Tienes algo interesante que contarme?";
		if (CheckAttribute(pchar, "questTemp.AdmiralMap") && CountAdmiralMapFromCharacter() > 0 && CountAdmiralMapFromCharacter() < 24 && !CheckAttribute(npchar, "quest.mapinfo"))
		{
			link.l3 = TimeGreeting() + "¡ Señor Dios, por favor, eche un vistazo al mapa que he encontrado. Debe ser uno de sus mapas según la señal.";
			link.l3.go = "map_info";
		}
		if (CheckAttribute(pchar, "questTemp.AdmiralMap") && CountAdmiralMapFromCharacter() > 23)
		{
			link.l3 = TimeGreeting() + "¡Señor Dios, tengo buenas noticias para usted. Logré reunir el juego completo de sus mapas únicos, tal como quería. Aquí están los veinticuatro mapas.";
			link.l3.go = "amap";
		}
		if (CheckAttribute(pchar, "questTemp.LSC.Dios")) // был в LSC
		{
			link.l4 = TimeGreeting() + "¡Sí, lo he hecho. Estuve en ese lugar místico del que hablábamos!";
			link.l4.go = "LSC";
		}
		link.l9 = "Nada hasta ahora, señor. Solo quería ver cómo le va.";
		link.l9.go = "exit";
		NextDiag.TempNode = "Dios";
		break;

	case "map_info":
		dialog.text = "Muéstrame... (echando un vistazo) ¡Por supuesto! ¡Este es uno de mis mapas para el atlas del almirante! Capitán, realmente te pido que los encuentres todos. Entiendo que es casi imposible, pero aún así... No quiero perder la esperanza.";
		link.l1 = "No lo pierdas, Señor. He encontrado este mapa, así que hay una posibilidad de que también encuentre el resto. Todavía están en el Caribe.";
		link.l1.go = "map_info_1";
		break;

	case "map_info_1":
		dialog.text = "Su optimismo realmente me anima, señor capitán. ¡Quizás aún pueda tener la oportunidad de mostrarle a don Juan de Córdoba quién es el mejor cartógrafo del archipiélago!";
		link.l1 = "Podrás vencer a todos tus competidores malintencionados. Los mapas son realmente maravillosos... ¡Adiós, Señor!";
		link.l1.go = "exit";
		npchar.quest.mapinfo = "true";
		NextDiag.TempNode = "Dios";
		break;

	case "amap":
		Achievment_Set("ach_CL_110");
		dialog.text = "¡No puedo creer lo que ven mis ojos! ¿De verdad los has encontrado? ¿A todos ellos?";
		link.l1 = "Sí. No fue fácil, pero tuve suerte en esta búsqueda. Toma tus mapas. Son tan maravillosos, que me da pena separarme de ellos.";
		link.l1.go = "amap_1";
		break;

	case "amap_1":
		for (i = 1; i <= 24; i++)
		{
			sTemp = IdentifyAdmiralMapLast();
			if (sTemp != "")
				RemoveItems(pchar, sTemp, 1);
		}
		Log_Info("Has entregado el juego completo de mapas de almirante");
		PlaySound("interface\important_item.wav");
		dialog.text = "¡Increíble! ¡Esto es simplemente demasiado increíble! Para ser honesto, nunca creí que este momento llegaría.";
		link.l1 = "Dum spiro, spero, Señor Dios. Ahora puedes enfrentarte a don Cordova. Estoy seguro de que valorará tus talentos en gran medida.";
		link.l1.go = "amap_2";
		break;

	case "amap_2":
		dialog.text = "Tienes mis agradecimientos, ¡Capitán! Ni siquiera te das cuenta del gran servicio que me has hecho. Y como prometí, te recompensaré. También tengo un regalo para ti. Creo que como marinero, lo encontrarás muy útil.";
		link.l1 = "¡Me has intrigado, señor!";
		link.l1.go = "amap_3";
		break;

	case "amap_3":
		GiveItem2Character(pchar, "spyglass5");
		Log_Info("Has recibido un telescopio de barco");
		PlaySound("interface\important_item.wav");
		dialog.text = "¡Aquí! Este es un catalejo de barco de mi diseño. Es único y no encontrarás otro igual en ningún otro lugar. Las lentes fueron hechas en Europa por el maestro más habilidoso de España. Su estuche fue fabricado por un armero amigo. Un trípode especial te ayudará a apuntar el dispositivo a pesar de cualquier balanceo. Puedes ver todo lo que necesitas, ya sea de un barco o un fuerte.";
		link.l1 = "¡Qué regalo tan maravilloso! Gracias, Señor Dios.";
		link.l1.go = "amap_4";
		break;

	case "amap_4":
		dialog.text = "Úselo, señor capitán. Espero que mi catalejo le sirva bien.";
		link.l1 = "¡Sin duda! Estoy ansioso por plantarlo en la cubierta de mi barco y mirar a través de él.";
		link.l1.go = "amap_5";
		break;

	case "amap_5":
		dialog.text = "Te sorprenderás, te lo aseguro... ¡Gracias de nuevo por salvar mis mapas!";
		link.l1 = "Gracias a usted también, señor. Creo que nos volveremos a ver. Pero por ahora, me despido. Iré a probar su magnífico dispositivo. ¡Adiós!";
		link.l1.go = "amap_6";
		link.l2 = "Gracias a usted también, señor. Un anteojo náutico es una cosa única y muy útil para un marinero. Sin embargo, puede que no sea más valioso que un conjunto de sus mapas. Envidio amablemente a Don de Cordova. ¡Ah! Me encantaría tener mapas tan hermosos en el escritorio de mi capitán en mi camarote.";
		link.l2.go = "amapcopy_01";
		break;

	case "amap_6":
		DialogExit();
		NextDiag.CurrentNode = "Dios";
		AddCharacterExpToSkill(pchar, "Fortune", 1000);			 // везение
		AddCharacterExpToSkill(pchar, "Leadership", 1000);		 // харизма
		AddCharacterExpToSkill(pchar, "Sneak", 300);			 // скрытность (раз телескоп дали)
		ChangeCharacterComplexReputation(pchar, "nobility", 10); // репутация-известность
		ChangeCharacterComplexReputation(pchar, "authority", 5); // репутация-авторитет
		ChangeCharacterNationReputation(pchar, SPAIN, 20);
		ChangeOfficersLoyality("good_all", 5);
		DeleteAttribute(pchar, "questTemp.AdmiralMap");
		break;

	case "amapcopy_01":
		AddCharacterExpToSkill(pchar, "Fortune", 1000);			 // везение
		AddCharacterExpToSkill(pchar, "Leadership", 1000);		 // харизма
		AddCharacterExpToSkill(pchar, "Sneak", 300);			 // скрытность (раз телескоп дали)
		ChangeCharacterComplexReputation(pchar, "nobility", 10); // репутация-известность
		ChangeCharacterComplexReputation(pchar, "authority", 5); // репутация-авторитет
		ChangeCharacterNationReputation(pchar, SPAIN, 20);
		ChangeOfficersLoyality("good_all", 5);
		DeleteAttribute(pchar, "questTemp.AdmiralMap");
		dialog.text = "¡Ay, señor, pero los mapas son únicos. Y si comenzara a hacer copias, la singularidad de este atlas se perdería en cuanto Don Juan de Córdoba se enterara de que alguien más tenía los mismos!";
		link.l1 = "Hmm... Señor Dios, ¿habría alguna manera de que hicieras una excepción?";
		link.l1.go = "amapcopy_02";
		break;

	case "amapcopy_02":
		dialog.text = "¿Excepción?";
		link.l1 = "Tanto tú como yo somos personas honestas; tuvimos la oportunidad de convencernos mutuamente de ello. Si usted me hiciera una copia de sus mapas, le juraría que nadie lo sabría jamás. Compréndalo: sus mapas son realmente magníficos, y para mí, como navegante, este atlas es un verdadero tesoro. Además, le pagaría generosamente por su trabajo.";
		link.l1.go = "amapcopy_03";
		break;

	case "amapcopy_03":
		dialog.text = "Señor " + pchar.lastname + ", no dudo ni por un momento que cumplirías tu palabra. Y considerando lo que has hecho por mí, me es muy difícil rechazar tu petición. Además, el hecho de que tú, un excelente marinero, aprecies tanto mis mapas ya es un valioso cumplido para mí como cartógrafo.";
		link.l1 = "Créeme, no exageré ni un poco. ¿Entonces qué dices?";
		link.l1.go = "amapcopy_04";
		break;

	case "amapcopy_04":
		dialog.text = "Muy bien, estoy de acuerdo en hacerte una copia de este atlas. Pero hay un pequeño problema. Cuando robaron mi preciado atlas, los ladrones también se llevaron todas mis herramientas - quizás para asegurarse de que nunca pudiera hacer más mapas o tal vez para empeñarlas con mis competidores. Y si he de hacer más mapas de tal calidad, no puedo usar equipo de papelería ordinario.\nIntenté comprar suministros de escritura en el mercado, pero no tuve suerte - no hay nada a la venta. Si puedes conseguirme los suministros necesarios, haré copias de estos mapas para ti.";
		link.l1 = "No hay problema, te traeré materiales de escritura de calidad. ¿Y qué tal el pago?";
		link.l1.go = "amapcopy_05";
		break;

	case "amapcopy_05":
		dialog.text = "No quiero parecer tacaño, señor... Pero tendré que pedirle tres cofres de doblones por este trabajo. Además, necesitaré un mes para terminarlo - tales mapas no pueden hacerse en un par de horas.";
		link.l1 = "¡Por supuesto, estoy de acuerdo! El valor de tus mapas excede con creces la cantidad que mencionaste.";
		link.l1.go = "amapcopy_06";
		break;

	case "amapcopy_06":
		dialog.text = "Entonces te estaré esperando con los suministros necesarios y con el pago acordado. Tan pronto como traigas todo, comenzaré a trabajar.";
		if (GetCharacterItem(pchar, "chest") >= 3 && GetCharacterItem(pchar, "mineral21") > 0)
		{
			link.l1 = "No tendrás que esperar mucho: por suerte, tengo todo lo que necesitas. Aquí tienes, por favor.";
			link.l1.go = "amapcopy_07";
		}
		link.l2 = "¡No tendrá que esperar mucho, señor!";
		link.l2.go = "amapcopy_exit";
		break;

	case "amapcopy_07":
		dialog.text = "¡Noticias fantásticas! Sabes, para un verdadero cartógrafo, no hay nada más alegre que cuando su trabajo es tan altamente valorado. Debo admitir, me alegra que un verdadero marinero profesional vaya a usar mi obra. Ahora necesito un mes para terminarlas. Después, te estaré esperando en mi lugar.";
		link.l1 = "Volveré en un mes, señor Dios. ¡Y de nuevo, muchas gracias!";
		link.l1.go = "amapcopy_08";
		break;

	case "amapcopy_08":
		TakeNItems(pchar, "chest", -3);
		TakeNItems(pchar, "mineral21", -1);
		Log_info("Entregaste material de escritura y tres cofres con doblones.");
		PlaySound("interface\important_item.wav");
		SetTimerFunction("Amapcopy_comlete", 0, 0, 30);
		pchar.questTemp.AdmiralMapCopy = "wait";
		NextDiag.CurrentNode = "amapcopy_waitmonth";
		DialogExit();
		break;

	case "amapcopy_exit":
		DialogExit();
		NextDiag.CurrentNode = "amapcopy_waitchest";
		break;

	case "amapcopy_waitchest":
		dialog.text = "Saludos, señor " + pchar.lastname + ". ¿Trajiste lo que te pedí?";
		link.l1 = "Todavía no, señor Dios. ¡Pero definitivamente traeré todo!";
		link.l1.go = "amapcopy_exit";
		if (GetCharacterItem(pchar, "chest") >= 3 && GetCharacterItem(pchar, "mineral21") > 0)
		{
			link.l2 = "Sí, señor Dios. Aquí están sus nuevos suministros de escritura y el pago acordado.";
			link.l2.go = "amapcopy_07";
		}
		break;

	case "amapcopy_waitmonth":
		if (CheckAttribute(pchar, "questTemp.AdmiralMapCopy") && pchar.questTemp.AdmiralMapCopy == "complete")
		{
			dialog.text = "¡Y aquí estás, mi querido amigo! ¿Espero que no te importe que te llame así?";
			link.l1 = "En absoluto, amigo mío. Me alegra de verdad que nos hayamos hecho amigos.";
			link.l1.go = "amapcopy_09";
		}
		else
		{
			dialog.text = "¡Bienvenido, señor! Le ruego disculpas, pero los mapas aún no están listos.";
			link.l1 = "Sí, recuerdo que dijiste que necesitarías un mes. Solo pasé a ver cómo estabas.";
			link.l1.go = "amapcopy_waitmonth_01";
		}
		break;

	case "amapcopy_waitmonth_01":
		NextDiag.CurrentNode = "amapcopy_waitmonth";
		DialogExit();
		break;

	case "amapcopy_09":
		dialog.text = "¡Tengo maravillosas noticias para ti! He terminado por fin una copia del atlas del almirante. Me quedaré con el original, ya que todavía tengo la intención de participar en el empleo del Virrey de Nueva Granada. ¡Pero las copias son tuyas! Espero que te sirvan bien.";
		link.l1 = "¡Muchas gracias, señor! ¡No tenéis idea de lo valioso que es vuestro atlas para alguien como yo! ¡Juro por mi honor que nadie sabrá jamás que habéis hecho esta copia para mí!";
		link.l1.go = "amapcopy_10";
		break;

	case "amapcopy_10":
		GiveAdmiralAtlasToCharacter(pchar);
		Log_Info("Has recibido un juego de mapas del almirante.");
		PlaySound("interface\important_item.wav");
		dialog.text = "Me alegra que estés satisfecho. Además, ya que todo ha salido de esta manera, tengo una oferta más para ti.";
		link.l1 = "¿Qué pasa? Estoy escuchando con mucha atención.";
		link.l1.go = "best_map";
		break;

	case "best_map":
		dialog.text = "Mientras dibujaba estos mapas para ti, se me ocurrió que, aunque son buenos para un explorador, no proporcionan todo lo que necesita un capitán de mar. Mira por ti mismo: todas las bahías, cabos y lagunas están representadas con gran precisión, pero no puedes usarlos para trazar un rumbo entre las islas.";
		link.l1 = "Es cierto, no puedes determinar el rumbo por ellos. Pero de ninguna manera me atrevo a quejarme, ¡señor Dios! Has hecho los mapas para mí tal como acordamos, nada menos.";
		link.l1.go = "best_map_01";
		break;

	case "best_map_01":
		dialog.text = "¡Pero también puedo hacerte un mapa del archipiélago! Y no del tipo que puedes comprar a la Compañía Holandesa de las Indias Occidentales, sino un mapa único y excelente.";
		link.l1 = "¡Gracias, señor Dios, pero no necesito tal mapa. Aun así, muchas gracias por la oferta!";
		link.l1.go = "best_map_02";
		link.l2 = "¿Estás bromeando?! ¡Señor Dios, cómo podría negarme? Solo dime qué necesitas, ¡no escatimaré en dinero ni en herramientas!";
		link.l2.go = "best_map_04";
		break;

	case "best_map_02":
		dialog.text = "Bueno, tenía que ofrecerlo. En cualquier caso, fue un placer hacer negocios con usted, señor " + pchar.lastname + ".";
		link.l1 = "¡Igualmente! ¡Buena suerte para ti!";
		link.l1.go = "best_map_03";
		break;

	case "best_map_03":
		DeleteAttribute(pchar, "questTemp.AdmiralMapCopy");
		DialogExit();
		NextDiag.CurrentNode = "Dios";
		break;

	case "best_map_04":
		dialog.text = "Ya me has traído las herramientas, gracias. Necesitaré un mapa regular del archipiélago, y también pido una brújula y un cronómetro en funcionamiento: el mapa debe ser preciso, de lo contrario solo será un estorbo para ti. Y en cuanto al pago, pido un cofre con doblones.";
		link.l1 = "Un mapa regular del archipiélago, una brújula, un cronómetro funcionando, y un cofre con doblones... ¿Por qué necesitas todo esto? Pensé que solo harías una copia, como con tus mapas de islas...";
		link.l1.go = "best_map_05";
		break;

	case "best_map_05":
		dialog.text = "Sí, al igual que con los otros mapas, ya he hecho una copia del mapa general del archipiélago. El cliente fue el mismo - el Virrey de Nueva Granada, Don Juan de Córdoba. Necesitaba este mapa para el capitán de una enorme escuadra que navega entre el Viejo y el Nuevo Mundo a través del Atlántico. Pero el mapa ya está en manos de su dueño.";
		link.l1 = "Ahora entiendo. ¿Necesitarás dibujar este mapa de nuevo?";
		link.l1.go = "best_map_06";
		break;

	case "best_map_06":
		dialog.text = "Exactamente. Por eso necesito un mapa regular para orientarme, así como instrumentos de navegación para mediciones más precisas. Me tomará alrededor de una semana crearla - después de todo, no es la primera vez que dibujo un mapa así. Oh, la condición es la misma que antes: esto debe permanecer entre nosotros. El Vice-Rey puede enfurecerse si se entera de que estoy dibujando tales mapas no solo para él.";
		if (CheckAMapItems())
		{
			link.l1 = "Recuerdo eso, Señor Dios. No te preocupes, nadie descubrirá estos mapas. Y ya tengo todo lo que necesitas conmigo. Aquí, tómalo.";
			link.l1.go = "best_map_07";
		}
		link.l2 = "Recuerdo eso, Señor Dios. No te preocupes, nadie se enterará de estos mapas. Y traeré todo lo que requieres, solo espera.";
		link.l2.go = "best_map_07e";
		break;

	case "best_map_07e":
		DialogExit();
		NextDiag.CurrentNode = "best_map_waititems";
		break;

	case "best_map_waititems":
		dialog.text = "¡Saludos, mi querido amigo! ¿Has traído lo que te pedí?";
		link.l1 = "Aún no, Señor Dios. ¡Pero definitivamente lo traeré!";
		link.l1.go = "best_map_07e";
		if (CheckAMapItems())
		{
			link.l2 = "Sí, Señor Dios. Aquí está todo lo que ha pedido: un mapa regular del archipiélago, una brújula, un cronómetro en funcionamiento y el pago acordado.";
			link.l2.go = "best_map_07";
		}
		break;

	case "best_map_07":
		Log_Info("Entregaste un mapa normal del archipiélago, una boussole, un cronómetro y un cofre con doblones.");
		TakeNItems(pchar, "chest", -1);
		TakeNItems(pchar, "map_normal", -1);
		TakeNItems(pchar, "bussol", -1);
		TakeNItems(pchar, "clock2", -1);
		dialog.text = "Bueno, entonces me pondré a trabajar. Vuelve a verme en una semana, ¡y te prometo que no te arrepentirás!";
		link.l1 = "¡No tengo duda, señor! ¡Nos vemos en una semana!";
		link.l1.go = "best_map_08";
		break;

	case "best_map_08":
		SetTimerFunction("AdmAtlas_comlete", 0, 0, 7);
		NextDiag.CurrentNode = "best_map_wait";
		pchar.questTemp.AdmiralAtlas = true;
		DialogExit();
		break;

	case "best_map_wait":
		if (CheckAttribute(pchar, "questTemp.AdmiralAtlas") && pchar.questTemp.AdmiralAtlas == "complete")
		{
			dialog.text = "Ah, aquí estás, Señor " + pchar.lastname + "¡Me complace informarte que he completado el mapa del archipiélago! Y puedo asegurarte, es tan bueno como el primer dibujo que hice para Don Juan de Córdoba!";
			link.l1 = "Mi amigo... ¡Este mapa es asombroso! ¡Es nada menos que una obra maestra! ¿Cómo puedo agradecerte por todo lo que has hecho por mí?";
			link.l1.go = "best_map_09";
		}
		else
		{
			dialog.text = "¡Saludos, Señor! Debo disculparme, pero el mapa aún no está listo.";
			link.l1 = "Sí, recuerdo que necesitabas una semana. Solo vine a ver cómo estabas.";
			link.l1.go = "best_map_wait_01";
		}
		break;

	case "best_map_wait_01":
		NextDiag.CurrentNode = "best_map_wait";
		DialogExit();
		break;

	case "best_map_09":
		dialog.text = "Ah, vamos, amigo mío. Fue un placer para mí crear tales mapas para un noble capitán que realmente los aprecia. Ah sí, puedes recuperar tu copia del mapa regular. ¡Buena suerte en alta mar!";
		link.l1 = "¡Muchas gracias! Tienes razón, estos mapas son invaluables para mí. ¡Adiós, Señor Dios!";
		link.l1.go = "best_map_10";
		break;

	case "best_map_10":
		TakeNItems(pchar, "Map_Best", 1);
		TakeNItems(pchar, "map_normal", 1);
		Log_Info("¡Ha recibido un mapa del archipiélago excelente!");
		PlaySound("interface\important_item.wav");
		NextDiag.CurrentNode = "Dios";
		DialogExit();
		break;

	case "LSC":
		dialog.text = "¿De verdad?! ¿Lo has encontrado? Ponte cómodo, creo que la conversación que se avecina tomará un tiempo, ¿verdad?";
		link.l1 = "Tengo mucho que contarte sobre la isla. Pero primero, quiero que me prometas algo. Veo que eres un hombre de honor, así que estoy seguro de que cumplirás tu palabra...";
		link.l1.go = "LSC_1";
		break;

	case "LSC_1":
		dialog.text = "¿De qué estás hablando, Capitán?";
		link.l1 = "Hay gente viviendo allí... y no estarán contentos si alguien se entromete en su vida. No creo que una posible llegada de algún escuadrón de 'investigación' sea bienvenida.";
		link.l1.go = "LSC_1_1";
		break;

	case "LSC_1_1":
		dialog.text = "";
		link.l1 = "Así que quiero que me des tu palabra de honor de que no publicarás ninguna información que pueda usarse para encontrar la Isla en los diez años siguientes a nuestra conversación. Puedes publicar cualquier información sobre los lugareños, su vida y demás, solo no reveles la ubicación de la isla.";
		link.l1.go = "LSC_2";
		break;

	case "LSC_2":
		dialog.text = "Estoy de acuerdo, Capitán. Le doy la palabra de un noble de que no le diré a nadie ni la ubicación de la Isla ni ninguna información que pueda perjudicar a sus habitantes en los próximos diez años.";
		link.l1 = "Escucha mi historia entonces. Escríbela si quieres. Así que, la Isla está hecha de muchos barcos naufragados cuyos cascos yacen sobre un amplio bajío...";
		link.l1.go = "LSC_3";
		break;

	case "LSC_3":
		DialogExit();
		SetLaunchFrameFormParam("Dos horas después...", "LSC_FinalDiosStory", 0, 5);
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 2, 10); // крутим время
		RecalculateJumpTable();
		break;

	case "LSC_4":
		dialog.text = "¡Increíble! ¡Me has contado información muy valiosa, capitán! ¡Los descendientes del almirante de Betancourt están viviendo en la Isla! Ahora sabemos qué sucedió con su escuadrón. Y hay un lugar menos en blanco en el mapa del archipiélago caribeño ahora... Muchas gracias por tu historia, " + pchar.name + ".";
		link.l1 = "¿Ves ahora por qué te he pedido que seas muy cuidadoso al relatar mi información?";
		link.l1.go = "LSC_5";
		break;

	case "LSC_5":
		dialog.text = "Ya veo. Puedes estar seguro de que cumpliré mi palabra. Dime... ¿tienes algún atributo material de la Isla?";
		if (CheckCharacterItem(pchar, "LSC_navigation_map"))
		{
			link.l1 = "Tengo direcciones de navegación a la Isla de los Barcos Abandonados. Aquí, echa un vistazo. Te permiten navegar un pequeño barco a través de los arrecifes y escombros y desembarcar de manera segura en la Isla. Es imposible llegar a la Isla sin esas direcciones.";
			link.l1.go = "LSC_6";
		}
		else
		{
			link.l1 = "Lamentablemente, no tengo ninguno.";
			link.l1.go = "LSC_7_1";
		}
		break;

	case "LSC_6":
		Log_Info("Has entregado las coordenadas de navegación");
		PlaySound("interface\important_item.wav");
		dialog.text = "(mirando) ¡Qué documento tan excelente! Fue elaborado por un hombre experto en cartografía. Ni yo podría hacerlo mejor. ¡Increíble! Capitán, ¿por qué no me da estas direcciones de navegación? Una historia es una historia, pero este papel debe ser mostrado a los geógrafos más famosos del Viejo Mundo.";
		link.l1 = "Señor Dios, por desgracia, necesito este documento para mí mismo. Como ya he dicho antes, es imposible pasar por los arrecifes que rodean la Isla sin él. Pero puedes hacer una copia de las instrucciones si lo deseas, y estaré encantado si también las tienes en tu posesión.";
		link.l1.go = "LSC_10";
		// link.l2 = "Señor Dios, lamentablemente, necesito este objeto para mí. Como he dicho, es imposible pasar por los arrecifes alrededor de la Isla sin él. Lo sacrificaría en nombre de la ciencia, pero... Estoy seguro de que lo entiende.";
		// link.l2.go = "LSC_7";
		break;

	case "LSC_7":
		Log_Info("Has recibido las coordenadas de navegación");
		PlaySound("interface\important_item.wav");
		dialog.text = "Absolutamente. Es tu derecho, aunque es una pena... De todos modos, ¡gracias por tu historia! Has hecho un gran servicio para geógrafos, cartógrafos y otros curiosos.";
		link.l1 = "De nada, señor. Bueno, ahora debo irme. Adiós.";
		link.l1.go = "LSC_8";
		break;

	case "LSC_7_1":
		dialog.text = "Qué lástima... De todos modos, ¡gracias por tu historia! Has prestado un gran servicio a geógrafos, cartógrafos y otras personas curiosas.";
		link.l1 = "De nada, Señor. Bueno, tengo que irme ahora. Adiós.";
		link.l1.go = "LSC_8";
		break;

	case "LSC_8":
		dialog.text = "Claro, " + pchar.name + ". Has dedicado mucho de tu tiempo para mí. ¡Envía mis saludos al Señor Svenson!";
		link.l1 = "Adiós, Señor Dios.";
		link.l1.go = "LSC_9";
		break;

	case "LSC_9":
		DialogExit();
		NextDiag.CurrentNode = "Dios";
		AddCharacterExpToSkill(pchar, "Fortune", 400);			 // везение
		AddCharacterExpToSkill(pchar, "Leadership", 500);		 // харизма
		ChangeCharacterComplexReputation(pchar, "nobility", 5);	 // репутация-известность
		ChangeCharacterComplexReputation(pchar, "authority", 2); // репутация-авторитет
		ChangeCharacterComplexReputation(pchar, "fame", 3);
		ChangeCharacterNationReputation(pchar, SPAIN, 5);
		DeleteAttribute(pchar, "questTemp.LSC.Dios");
		LAi_SetOwnerType(npchar);
		break;

	case "LSC_10":
		Log_Info("Has recibido las coordenadas de navegación");
		PlaySound("interface\important_item.wav");
		dialog.text = "¡Muchas gracias! Eso es muy amable de tu parte. Dame un poco de tiempo...";
		link.l1 = "...";
		link.l1.go = "LSC_11";
		break;

	case "LSC_11":
		DialogExit();
		SetLaunchFrameFormParam("Dos horas después", "", 0.1, 3.0);
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 2, 0);
		npchar.dialog.currentnode = "LSC_12";
		LAi_SetActorType(npchar);
		LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;

	case "LSC_12":
		// RemoveItems(pchar, "LSC_navigation_map", 1);
		dialog.text = "¡Muchas gracias! Fue muy amable de tu parte. Ahora tenemos no solo pruebas orales sino también materiales... No te dejaré sin recompensa, Capitán. Tengo un pequeño obsequio para ti.";
		link.l1 = "¿Qué tipo de regalo?";
		link.l1.go = "LSC_13";
		break;

	case "LSC_13":
		sld = characterFromId("Pirates_shipyarder");
		sld.quest.sextant = "true"; // атрибут Алексу на хронометр
		GiveItem2Character(pchar, "sextant1");
		PlaySound("interface\important_item.wav");
		dialog.text = "Me apasiona no solo la cartografía y la geografía, sino también las matemáticas y la astronomía. Me llevó un año intentar crear una herramienta universal para determinar la latitud y la longitud. Y he hecho algunos progresos. Aquí, echa un vistazo:\nEste es mi sextante. Lo diseñé yo mismo. El problema es que no funciona. Requiere un cronómetro extremadamente preciso. Incluso aquellos que fueron hechos por los mejores artesanos dan errores inaceptables con el tiempo. Por lo tanto, mi herramienta no vale nada por ahora.\nPero ya que viajas mucho, quizás encuentres un cronómetro lo suficientemente preciso para que el sextante funcione. Una vez que encuentres tal reloj, no necesitarás una Boussole, una brújula, un astrolabio, relojes de arena y otros cronómetros deficientes: mi herramienta los reemplazará a todos.";
		link.l1 = "Gracias, Señor Dios. Esperemos que encuentre un cronómetro que haga funcionar su invento. Me gustaría tener tal dispositivo... en buen estado. Bueno, tengo que irme ahora. Adiós.";
		link.l1.go = "LSC_8";
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	//--> блок реагирования на попытку залезть в сундук
	case "Man_FackYou":
		dialog.text = LinkRandPhrase("Estás " + GetSexPhrase("¡un ladrón, veo! Guardias, apresadlo", "¡Un ladrón, veo! Guardias, captúrenla") + "¡¡¡", "¡No me lo puedo creer! Me di la vuelta un segundo, ¡y ya estás hurgando en mis pertenencias! ¡Detengan al ladrón!!!", "¡Guardias! ¡Robo! ¡Detened al ladrón!!!");
		link.l1 = "¡Aaaah, diablo!!!";
		link.l1.go = "fight";
		break;

	case "fight":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_SetOwnerTypeNoGroup(npchar);
		LAi_group_Attack(NPChar, Pchar);
		if (rand(3) != 1)
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}

bool CheckAMapItems()
{
	return GetCharacterItem(pchar, "chest") &&
		   GetCharacterItem(pchar, "map_normal") &&
		   GetCharacterFreeItem(pchar, "bussol") &&
		   GetCharacterFreeItem(pchar, "clock2");
}