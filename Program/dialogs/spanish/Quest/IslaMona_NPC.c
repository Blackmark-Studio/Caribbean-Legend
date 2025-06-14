void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "¿Qué necesitas?";
			link.l1 = "Nada.";
			link.l1.go = "exit";
		break;
		
		// Родриго Хименес
		case "Himenes_exit":
			dialog.text = "¿Algo más, capitán?";
			link.l1 = "Nada por ahora...";
			link.l1.go = "Himenes_exit_1";
		break;
		
		case "Himenes_exit_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
		break;
		
		case "Himenes":
			dialog.text = "¡Ja-ja-ja! ¡Señor Jesucristo! ¡Gloria a Santiago el Protector! ¡Gloria a la Virgen María! ¡Estamos salvados! ¡Ja-ja-ja!";
			link.l1 = "¡Españoles! ¡A las armas!";
			link.l1.go = "Himenes_1_1";
			link.l2 = "Hola. ¿Entiendo que tienes problemas? ¿Quién eres?";
			link.l2.go = "Himenes_2";
		break;
		
		case "Himenes_1_1":
			AddComplexSelfExpToScill(100, 100, 100, 100);
			dialog.text = "¡Ja-ja-ja-ja-ja-ja-ja-ja!";
			link.l1 = "Está bien, cálmate. Es solo una costumbre.";
			link.l1.go = "Himenes_2";
		break;
		
		case "Himenes_2":
			dialog.text = "¡Ja, ja! Señor, mi nombre es Rodrigo Jiménez. Soy un agrimensor y, por voluntad del destino, el jefe de esta gente desafortunada.";
			link.l1.go = "Himenes_3";
		break;
		
		case "Himenes_3":
			dialog.text = "Nos... desembarcaron aquí. Pero, señor, ¡no somos criminales! ¡Ja-ja-ja-ja!";
			link.l1 = "¿Qué es gracioso?";
			link.l1.go = "Himenes_4";
		break;
		
		case "Himenes_4":
			dialog.text = "Ah... ¡Mis disculpas, señor! Es toda mi aflicción, desde la infancia me río cuando estoy muy nervioso. Ja.";
			link.l1 = "¿Y fuiste elegido como el líder?.. Está bien. La gente no llega a islas deshabitadas sin razón, señor. ¿Te importa explicarlo? Solo te doy una oportunidad.";
			link.l1.go = "Himenes_5";
		break;
		
		case "Himenes_5":
			string nationManName[4];
			nationManName[0] = "English";
			nationManName[1] = "French";
			nationManName[2] = "Si usted está viendo esto, es un error";
			nationManName[3] = "Spaniard";
			dialog.text = "Lo siento, me temo que no entendí su nombre, señor. ¿Es usted inglés?";
			link.l1 = nationManName[sti(pchar.BaseNation)]+"¿Es tan importante? No nos preocupemos por mi nombre por ahora.";
			link.l1.go = "Himenes_6";
		break;
		
		case "Himenes_6":
			dialog.text = "De hecho, al ser reconocidos como herejes por la Iglesia Católica Española, debemos comparecer ante el justo tribunal de la Santa Inquisición. Por eso tu nacionalidad es tan importante para nosotros. Un capitán español estaría obligado a entregarnos a las autoridades locales. ¡No sobreviviríamos a tal cosa de nuevo! ¡Ja-ja!";
			if (sti(pchar.BaseNation) == SPAIN) dialog.text = "¡Ja-ja-ja-ja-ja-ja! Tal es nuestra suerte, bueno, no tenemos nada que perder de todos modos. "+dialog.text;
			link.l1 = "Bueno, afortunadamente para ti, los asuntos de la Inquisición no me conciernen. ¿Y qué? ¿Sois paganos?";
			link.l1.go = "Himenes_7";
		break;
		
		case "Himenes_7":
			dialog.text = "No, ¡te lo juro! Nuestra comunidad se dedicó a la artesanía y el comercio en la gloriosa ciudad de Cádiz durante cincuenta años. Todo iba bien, incluso adquirimos un barco y una licencia para comerciar con las colonias de nuestro Imperio. Ahora entiendo que en ese entonces cruzamos alguna línea y estábamos completamente desprevenidos para nuestros nuevos competidores... y sus métodos.";
			link.l1 = "¿No compartiste comercio con alguien en Europa y, como resultado, toda la comunidad quedó atrapada en una isla desierta en el Caribe? Y pensé que yo tenía problemas de vida...";
			link.l1.go = "Himenes_8";
		break;
		
		case "Himenes_8":
			dialog.text = "Lamentablemente, ese es el caso. Nuestra comunidad fue fundada por judíos que se convirtieron a la nueva fe y se les concedió la oportunidad de regresar a casa a España. Esta antigua historia fue suficiente para acusaciones y escrutinio oficial.";
			link.l1 = "Y así escapaste...";
			link.l1.go = "Himenes_9";
		break;
		
		case "Himenes_9":
			dialog.text = "¡Sí! ¡Ja-ja-ja! ¡En nuestro propio barco! Nos dirigíamos a Curazao para construir un nuevo hogar y un nuevo negocio. Sin embargo, subestimamos la persistencia de la Inquisición y pagamos caro por ello. Su mensajero nos interceptó no muy lejos de aquí y ordenó al capitán que nos devolviera a casa...";
			link.l1 = "¡Maldita sea!";
			link.l1.go = "Himenes_10";
		break;
		
		case "Himenes_10":
			dialog.text = "¡Hay más! ¡Ja! Nuestro capitán no quiso molestarse en llevarnos de vuelta a través del Atlántico ni liberarnos bajo su responsabilidad en el puerto más cercano. Y, tomando una decisión verdaderamente salomónica, nos dio comida, nos dejó aquí, y así quedó la cosa.";
			link.l1 = "Una historia trágica, sin duda alguna. Resumamos: no puedes regresar a casa, las colonias amigas te delatarán, y los puertos extranjeros tampoco te recibirán - no hay fin a la guerra en esta región. ¿Cuáles son tus planes?";
			link.l1.go = "Himenes_11";
		break;
		
		case "Himenes_11":
			dialog.text = "Ha pintado un cuadro tan sombrío, señor, que estoy sin palabras. Es como si no hubiera mejor lugar para nosotros que esta isla.";
			link.l1 = "No lo creo, hay una isla mejor.";
			link.l1.go = "Himenes_12";
		break;
		
		case "Himenes_12":
			dialog.text = "¿De verdad? ¿Es español?";
			link.l1 = "Es mío. Por destino, heredé un antiguo escondite de piratas en una isla deshabitada. Ahora es mi base, y quiero expandirla, explorar la isla, y si es posible, construir una fábrica allí.";
			link.l1.go = "Himenes_13";
		break;
		
		case "Himenes_13":
			dialog.text = "¿Eres un pirata?";
			link.l1 = "Sí.";
			link.l1.go = "Himenes_14_1";
			link.l2 = "No.";
			link.l2.go = "Himenes_14_2";
		break;
		
		case "Himenes_14_1":
			dialog.text = "¡Nuevo Mundo! En efecto, aquí estamos. En casa dicen que los piratas son verdaderos demonios y ni siquiera humanos. Comen niños, violan mujeres y despellejan a buenos católicos. ¿Es eso cierto?";
			link.l1 = "Depende del día de la semana. Hablemos de esto en otro momento. Estoy buscando gente. Individuos trabajadores y capaces dispuestos a vivir lejos de la civilización durante varios años. ¿Te interesaría algo así?";
			link.l1.go = "Himenes_15";
		break;
		
		case "Himenes_14_2":
			dialog.text = "Qué lástima, ya que soy un criminal, me gustaría ver al menos a un pirata.";
			link.l1 = "Tal vez tengas una oportunidad así nuevamente. Hablemos de ello en otra ocasión. Estoy buscando personas trabajadoras y capaces dispuestas a vivir lejos de la civilización durante varios años. ¿Estarías interesado en algo así?";
			link.l1.go = "Himenes_15";
		break;
		
		case "Himenes_15":
			dialog.text = "No tenemos otra salida. Pero en realidad no es una mala opción. Lo aceptaremos si nos permites vivir y trabajar en paz. ¡Y promete enviarnos a casa algún día! Danos tu palabra, señor, y dinos tu nombre...";
			link.l1 = "Soy el capitán "+GetFullName(pchar)+", y te doy mi palabra.";
			link.l1.go = "Himenes_16";
		break;
		
		case "Himenes_16":
			dialog.text = "¡Ja, ja! ¡Estamos salvados! ¡Así sea! Somos varias familias, unas 30 personas. Todos son alfabetizados, entrenados en oficios y comercio.";
			link.l1 = "El destino ha decidido... ¡Por favor, sube a bordo!";
			link.l1.go = "Himenes_17";
		break;
		
		case "Himenes_17":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto1", "none", "", "", "", 10.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			IslaMona_TerksHimenesOnBoard();
		break;
		
		case "Himenes_18":
			dialog.text = "Encantado de conocerte, señor Rodgar. Parece que tendremos que vivir y trabajar juntos durante mucho tiempo... ¡Dios mío!, ¿cómo soportas este calor?";
			link.l1 = "";
			link.l1.go = "Himenes_19";
		break;
		
		case "Himenes_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_14";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Himenes_20":
			dialog.text = "Si no te importa, intervendré: Capitán, danos un día para instalarnos y revisar rápidamente el inventario y la tierra. Estoy seguro de que el Señor Rodgar tiene muchas ideas sobre qué hacer con esta parcela de tierra. Creo que formaremos un buen equipo.";
			link.l1 = "No tienes realmente una elección, Hymenese. ¡Ja-ja.!";
			link.l1.go = "Himenes_21";
		break;
		
		case "Himenes_21":
			dialog.text = "¡Ja-ja-ja-ja-ja-ja!";
			link.l1 = "";
			link.l1.go = "Himenes_22";
		break;
		
		case "Himenes_22":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_16";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Himenes_23":
			dialog.text = "¿Sí, Capitán?";
			link.l1 = "¿Hymenese, alguna buena nueva para mí?";
			link.l1.go = "Himenes_24";
		break;
		
		case "Himenes_24":
			dialog.text = "Capitán, esto es una pesadilla. Tu casa no está mal, por supuesto. Pero por lo demás... ¡Es imposible vivir en estas chozas, rodeadas de maleza, y el señor Rodgar ni siquiera sabe lo que está pasando en el otro extremo de la isla! ¡Increíble! ¡Ja-ja!";
			link.l1 = "¿Estás nervioso o en realidad te estás riendo de esto ahora mismo?";
			link.l1.go = "Himenes_25";
		break;
		
		case "Himenes_25":
			dialog.text = "¡Por supuesto, es gracioso! ¿Qué estuvieron haciendo todos estos años? Ante todo, necesitamos terminar de construir un par de casas y arreglar estas chozas hasta un estado aceptable. La gente necesita vivir decentemente para trabajar diligentemente. Además, pediré a los piratas que realicen un reconocimiento completo de la isla. Tal vez este lugar sea rico no sólo en rocas y arena. Cuando todo esté hecho, podré decirte exactamente qué hacer con esta tierra.";
			link.l1 = "¡Suena genial! ¿Qué se requiere de mí?";
			link.l1.go = "Himenes_26";
		break;
		
		case "Himenes_26":
			AddQuestRecordInfo("IslaMonaData", "1");
			dialog.text = "Materiales para casas, muebles y refugios temporales. He calculado todo. Aquí, toma la lista.";
			link.l1 = "Impresionante...";
			link.l1.go = "Himenes_27";
		break;
		
		case "Himenes_27":
			dialog.text = "¿De veras? ¡Señor, hemos construido catedrales! Ahora eso sí que es impresionante....";
			link.l1 = "¡Estoy inclinado a creerte! Solo no construyas accidentalmente una catedral aquí. ¿Tendré que traer mucho material aquí cada vez?";
			link.l1.go = "Himenes_28";
		break;
		
		case "Himenes_28":
			dialog.text = "No, estos materiales nos sostendrán por un tiempo, pero aún necesitaremos traer algunas cosas más adelante. Si quieres intentar evitar tales problemas en el futuro, trae el doble de materiales.";
			link.l1 = "Bueno, me convenciste. Veré qué puedo hacer. ¿Algún plazo?";
			link.l1.go = "Himenes_29";
		break;
		
		case "Himenes_29":
			dialog.text = "No, señor. Pero le pido amablemente que no se demore - este es el trabajo que debe hacerse para que las cosas avancen. Y la gente necesita un lugar donde vivir también. Cargue los materiales en el almacén y no olvide informarme cuando todo esté listo. ¡Oh, casi lo olvido! Hable con el señor Rodgar sobre explorar la isla.";
			link.l1 = "¡De acuerdo!";
			link.l1.go = "Himenes_30";
		break;
		
		case "Himenes_30":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
			pchar.questTemp.IslaMona = "stalk";
			AddQuestRecord("IslaMona", "6");
		break;
		
		case "Himenes_31":
			dialog.text = "¿Sí, Capitán?";
			if (IslaMona_CheckBuild()) // привез товары на стройку
			{
				link.l1 = "Hola, Hymenez. Revisa el almacén.";
				link.l1.go = "Himenes_32_1";
			}
			else // не привез товары на стройку
			{
				link.l1 = "Hola, Hymenez. Mis hombres han rastreado toda la isla. ¿Qué dices?";
				if (CheckAttribute(pchar, "questTemp.IslaMona.Food")) link.l1.go = "Himenes_32_2"; // привез еду и лекарства
				else link.l1.go = "Himenes_32_3";
			}
		break;
		
		case "Himenes_32_1":
			IslaMona_RemoveBuild(); // сразу удаляем товары со склада
			dialog.text = "¡Has manejado esta responsabilidad con gran éxito! Si alguna vez estás en Cádiz, ven a trabajar para mí como almacenista.";
			link.l1 = "¡Voy en camino! Dime, compadre, ¿qué vas a hacer ahora?";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Food")) link.l1.go = "Himenes_34_1"; // привез еду и лекарства
			else link.l1.go = "Himenes_34_2";
		break;
		
		case "Himenes_32_2":
			dialog.text = "Señor Capitán, tratemos primero con la vivienda y los suministros. Haremos planes después. Espero los bienes de su lista en el almacén.";
			link.l1 = "Está bien, entiendo. Primero, necesitamos construir casas y arreglar este lugar. Las mercancías llegarán pronto.";
			link.l1.go = "Himenes_33";
		break;
		
		case "Himenes_32_3":
			dialog.text = "Capitán, primero tratemos con la vivienda y los suministros. Podemos hacer planes más tarde. Estoy esperando las mercancías de su lista en el almacén. Y su amigo pirata también espera provisiones y medicinas.";
			link.l1 = "Está bien, lo entiendo. Primero, necesitamos construir casas y ordenar este lugar. Las mercancías llegarán pronto. Y para mi amigo pirata también.";
			link.l1.go = "Himenes_33";
		break;
		
		case "Himenes_33":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_31";
		break;
		
		case "Himenes_34_1":
			dialog.text = "Denos seis meses, Capitán, y no reconocerá este lugar.";
			link.l1 = "¿Estás diciendo que en seis meses no habrá ni tú, ni el asentamiento, ni los materiales aquí? ¡Hasta luego!";
			link.l1.go = "Himenes_37"; // все выполнил
		break;
		
		case "Himenes_34_2":
			dialog.text = "Comenzaremos a trabajar tan pronto como arregles tus asuntos con este bandido. Te pidió provisiones y medicinas, y estoy de acuerdo con él: es una demanda razonable.";
			link.l1 = "Le transmitiré tus palabras.";
			link.l1.go = "Himenes_35";
			AddQuestRecord("IslaMona", "11");
		break;
		
		case "Himenes_35":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_36";
		break;
		
		case "Himenes_36":
			dialog.text = "¿Bueno, Capitán? ¿Hiciste todo lo que te pidió tu pirata?";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Food"))
			{
				link.l1 = "He resuelto todos los problemas con Rodgar. El reconocimiento de la isla ha comenzado, las provisiones y medicinas están en el almacén. Ahora es tu turno.";
				link.l1.go = "Himenes_34_1";
			}
			else
			{
				link.l1 = "No te preocupes, lo resolveremos. Yo me encargo de esto.";
				link.l1.go = "Himenes_35";
			}
		break;
		
		case "Himenes_37":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
			DeleteAttribute(pchar, "questTemp.IslaMona.Food");
			pchar.questTemp.IslaMona = "build";
			AddQuestRecord("IslaMona", "12");
			SetFunctionTimerCondition("IslaMona_BuildDone", 0, 0, 180, false);
		break;
		
		case "Himenes_38":
			dialog.text = "¡Señor Capitán! ¿Qué opinas? ¡Ja-ja-ja?";
			link.l1 = "Es mucho más agradable. ¡Informa, Jiménez!";
			link.l1.go = "Himenes_39";
		break;
		
		case "Himenes_39":
			dialog.text = "¡Ahora puedes vivir aquí! Limpiamos y reconstruimos todas las casas, excepto la tuya, por supuesto. No muy lujosas, pero no peores que en nuestro Belice.";
			link.l1 = "Belice ha pertenecido a Inglaterra desde hace mucho tiempo, Himenes.";
			link.l1.go = "Himenes_40";
		break;
		
		case "Himenes_40":
			dialog.text = "No estoy seguro de si las casas lo saben, capitán, ¡ja-ja!";
			link.l1 = "Ahora tienes un lugar para vivir, y el asentamiento parece humano. ¿Qué sigue?";
			link.l1.go = "Himenes_41";
		break;
		
		case "Himenes_41":
			dialog.text = "Mira alrededor, habla con el Señor Janssen y vuelve a mí. Discutiremos los resultados del reconocimiento de la isla y nuestros planes.";
			link.l1 = "¿Desde cuándo empezaste a llamar a Rodgar así? ¿No estabas constantemente en desacuerdo?";
			link.l1.go = "Himenes_42";
		break;
		
		case "Himenes_42":
			dialog.text = "Y todavía los tenemos. Pero tenemos que construir relaciones de trabajo de alguna manera.";
			link.l1 = "Gracias, Rodrigo. Volveré pronto.";
			link.l1.go = "Himenes_43";
		break;
		
		case "Himenes_43":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload6", "none", "", "", "", 10.0); // возможно будет иной локатор в новой локации
			pchar.questTemp.IslaMona = "village";
		break;
		
		case "Himenes_44":
			dialog.text = "Capitán. Señor Janssen.";
			link.l1 = "Vamos, cuéntame sobre los resultados del reconocimiento de la isla.";
			link.l1.go = "Himenes_45";
		break;
		
		case "Himenes_45":
			dialog.text = "Sí, Capitán. Algunos lugares los inspeccioné personalmente con nuestro prospector. Bueno, ¿qué puedo decir...? Isla Mona es una isla pobre, diminuta y bastante poco interesante. Hay muy poco espacio para la construcción, el paisaje es difícil, escarpado, y casi no hay tierra fértil. Tres playas, una cueva inundada, espesos matorrales, un par de loros, una manada de cabras, y nosotros...";
			link.l1 = "¿Hablas en serio? ¿Estás diciendo que el activo más valioso en esta isla es un rebaño de cabras?";
			link.l1.go = "Himenes_46";
		break;
		
		case "Himenes_46":
			dialog.text = "¡Ja-ja-ja-ja! ¡Preguntaría, señor! ¡Ja-ja! ¡No me dejaste terminar!";
			link.l1 = "";
			link.l1.go = "Himenes_47";
		break;
		
		case "Himenes_47":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_38";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_48":
			dialog.text = "";
			link.l1 = "Bien, está bien, cálmate y continúa. Sabes, he invertido mucho en este lugar.";
			link.l1.go = "Himenes_49";
		break;
		
		case "Himenes_49":
			dialog.text = "¡Y no en vano! Hay suficiente agua dulce en la cueva, hay suficiente tierra para cultivar árboles frutales, y se pueden criar cabras. Con la pesca y el esfuerzo de tus camaradas, el problema de la comida se resolverá muy rápidamente.";
			link.l1 = "Entonces, ¿no necesitarás traer más comida aquí? No está mal. Esperaba que este lugar pudiera vivir sin mi constante cuidado. Continuemos.";
			link.l1.go = "Himenes_50";
		break;
		
		case "Himenes_50":
			dialog.text = "Eres acertado en todo, Señor. ¡Pero eso no es toda la noticia! Primero, al Señor Rodgar se le ha ocurrido la idea de construir una taberna. No sé qué te dará eso, pero este bribón trama algo.";
			link.l1 = "¡Quiere emborracharse, eso es lo que quiere!";
			link.l1.go = "Himenes_51";
		break;
		
		case "Himenes_51":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_40";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_52":
			dialog.text = "En segundo lugar, la Bahía del Gobernador resultó ser mucho más profunda de lo que originalmente pensamos. Podemos construir un muelle en toda regla.";
			link.l1 = "No entiendo muy bien cómo me beneficiará, pero eso ya son buenas noticias. ¿Eso no es todo, espero?";
			link.l1.go = "Himenes_53";
		break;
		
		case "Himenes_53":
			dialog.text = "Encontramos un bosque de árboles de bacote. Un lugar ideal para una fábrica.";
			link.l1 = "¡Me estás haciendo feliz, Rodrigo! ¡De verdad, excelentes noticias!";
			link.l1.go = "Himenes_54";
		break;
		
		case "Himenes_54":
			dialog.text = "Eso es todo por ahora, señor. Podríamos tener más ideas en el futuro. Entiendes, ¡las mejores ideas vienen mientras se trabaja! ¿Sobre qué te gustaría preguntar?";
			link.l1 = "Dime sobre el bacote. Suena prometedor.";
			link.l1.go = "Himenes_55";
		break;
		
		case "Himenes_55":
			dialog.text = "En mi estimación, una pequeña fábrica podrá extraer esta valiosa madera durante varios años. Las reservas son modestas, pero el recurso es estratégico. Podemos despejar un sitio en el centro de la isla y construir una casa con un almacén allí. Eso es un comienzo. Además de materiales de construcción, también necesitaremos alrededor de 15 juegos de esposas y mosquetes.";
			link.l1 = "¿Y para qué necesitamos esposas? Y, ¿por qué exactamente quince?";
			link.l1.go = "Himenes_56";
		break;
		
		case "Himenes_56":
			dialog.text = "Es un trabajo duro, señor. Diría incluso que es trabajo de esclavos.";
			link.l1 = "Entiendo. Je-je...";
			link.l1.go = "Himenes_57_1";
			link.l2 = "¿Te has vuelto loco? ¡No me convertiré en un dueño de esclavos!";
			link.l2.go = "Himenes_57_2";
		break;
		
		case "Himenes_57_1":
			dialog.text = "";
			link.l1 = "¿Y por qué necesitamos un mosquete? ¿Y por qué solo uno?";
			link.l1.go = "Himenes_59";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Himenes_57_2":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_42";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "Himenes_58":
			dialog.text = "Estoy de acuerdo con el pirata, señor. No le entiendo, capitán. Toda la economía de esta región se basa en el trabajo esclavo, y así seguirá siendo durante muchos años. ¿Cómo somos nosotros mejores?";
			link.l1 = "Tomaré una decisión. Mientras tanto, dime por qué necesitas un mosquete. ¿Y por qué exactamente uno?";
			link.l1.go = "Himenes_59";
		break;
		
		case "Himenes_59":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_44";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_60":
			dialog.text = "Por supuesto, la fábrica requerirá mantenimiento. Con su construcción, esta isla tendrá una economía con usted como su principal socio comercial. Nosotros alimentaremos a los esclavos, pero usted tendrá que pagar por la seguridad y la producción de su propio bolsillo. Los colonos tomarán cien doblones y cinco botellas de vino por cada lote. Para asuntos de seguridad, negocie con el Señor Janssen.";
			link.l1 = "";
			link.l1.go = "Himenes_61";
		break;
		
		case "Himenes_61":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_46";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_62":
			dialog.text = "cuarenta medidas cada mes. Y el oro es para el futuro. Un día nos sacarás de aquí, ¿recuerdas tu promesa? Cualquier trabajo debe ser pagado, y con tus doblones, pagaremos a cazadores y artesanos por su trabajo en el asentamiento. Así, tendremos comercio, y con él, ¡civilización!";
			link.l1 = "¡Así se habla! ¡Muy bien! Por ahora, todo suena lo suficientemente convincente...";
			link.l1.go = "Himenes_63";
		break;
		
		case "Himenes_63":
			dialog.text = "¿Qué más te interesa?";
			link.l1 = "Entonces, ¿cuál es la historia con la taberna? ¿Por qué no construir un teatro?";
			link.l1.go = "Himenes_64";
		break;
		
		case "Himenes_64":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_48";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_65":
			dialog.text = "Capitán, le advertí que no le gustaría la idea de la casa. Pero es la única opción. Tiene la casa más grande en... ejem, el pueblo, reconstruiremos el primer piso en un salón, colocaremos mesas y una cocina. Almacenaremos bebidas y comida en las cuevas bajo la casa. Tenemos gente para cocinar y tocar música. El segundo piso seguirá siendo suyo, y no lo tocaremos. Nosotros mismos moveremos todas sus cosas del primer piso al piso superior.";
			link.l1 = "Está bien. Entonces, ¿qué exactamente nos dará la taberna?";
			link.l1.go = "Himenes_66";
		break;
		
		case "Himenes_66":
			dialog.text = "Obtendremos algo de vida cultural, y tendrás la oportunidad de tener a unas trescientas personas en reserva justo en el corazón del Caribe.";
			link.l1 = "Interesante... Lo pensaré.";
			link.l1.go = "Himenes_67";
		break;
		
		case "Himenes_67":
			dialog.text = "¿Qué más te interesa?";
			link.l1 = "Bueno, ¿qué hay del muelle?";
			link.l1.go = "Himenes_68";
		break;
		
		case "Himenes_68":
			dialog.text = "Es simple. Limpiaremos la Bahía del Gobernador de arrecifes, instalaremos luces de señalización y construiremos un muelle. El señor Janssen afirma que podrás refugiar tres barcos en la bahía, o un barco de primera clase. Y será más agradable para ti regresar aquí, sin arrastrar el bote por la playa cada vez.";
			link.l1 = "Eso estaría bien.";
			link.l1.go = "Himenes_69";
		break;
		
		case "Himenes_69":
			dialog.text = "¿Qué te gustaría saber?";
			link.l1 = "Eso es todo por ahora. Volveré cuando decida qué construir.";
			link.l1.go = "Himenes_70";
		break;
		
		case "Himenes_70":
			dialog.text = "Señor Capitán, tome este documento. Me tomé la libertad de escribir todos los detalles para no repetirlos una docena de veces. Estúdielo, traiga materiales y establezca la tarea.";
			link.l1 = "Gracias, Rodrigo.";
			link.l1.go = "Himenes_71";
		break;
		
		case "Himenes_71":
			DialogExit();
			IslaMona_HouseDialogFin();
		break;
		
		case "Himenes_72": // нода Хименеса строителя и управляющего факторией
			if (CheckAttribute(pchar, "questTemp.IslaMona.RecordPart")) // после защиты Исла Моны - нужно еще 10 рабов
			{
				dialog.text = "Señor Capitán, necesitamos 10 esclavos para trabajar en la fábrica, ya te lo dije... ¿lo has olvidado?";
				if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 10)
				{
					link.l1 = "Ya están entregados. Descárgalos y comienza la producción.";
					link.l1.go = "Himenes_plantation_12";
				}
				else
				{
					link.l1 = "Mi memoria está intacta. Los traeré pronto.";
					link.l1.go = "Himenes_plantation_14";
				}
				break;
			}
			dialog.text = "Entonces, señor capitán, ¿qué dice?";
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Harbour"))
			{
				link.l1 = "Quiero una bahía limpia y un muelle seguro. Será la base para mi flota.";
				link.l1.go = "Himenes_harbour";
			}
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Tavern"))
			{
				link.l2 = "Adelante y construye la taberna. Todos lo apreciarán, y podré mantener una reserva aquí.";
				link.l2.go = "Himenes_tavern";
			}
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Plantation"))
			{
				link.l3 = "Comienza a construir la plantación. Es hora de recuperar las inversiones.";
				link.l3.go = "Himenes_plantation";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation.Slave") && IslaMona_CheckSlave())
			{
				link.l4 = "Rodrigo, los especialistas y equipos especialmente valiosos han sido entregados a la fábrica. Puedes empezar a trabajar.";
				link.l4.go = "Himenes_plantation_7";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Factory.Part") && sti(pchar.questTemp.IslaMona.Factory.Part) > 0)
			{
				link.l4 = "Rodrigo, he venido por mi sándalo.";
				link.l4.go = "Himenes_bacaut";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done" && CheckAttribute(pchar, "questTemp.IslaMona.Tavern") && pchar.questTemp.IslaMona.Tavern == "done" && CheckAttribute(pchar, "questTemp.IslaMona.Factory") && !CheckAttribute(pchar, "questTemp.IslaMona.Church"))
			{
				link.l5 = "Rodrigo, ¿hemos terminado nuestra gran construcción?";
				link.l5.go = "Himenes_church";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Church") && pchar.questTemp.IslaMona.Church == "start" && IslaMona_CheckChurch())
			{
				link.l5 = "Rodrigo, construyamos tu iglesia.";
				link.l5.go = "Himenes_church_10";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Church") && pchar.questTemp.IslaMona.Church == "Wait_candles" && IslaMona_CheckCandles())
			{
				link.l5 = "Rodrigo, traje tus objetos de la iglesia.";
				link.l5.go = "Himenes_church_10_3";
			}
			link.l10 = "Nada por ahora...";
			link.l10.go = "Himenes_73";
		break;
		
		case "Himenes_harbour":
			if (IslaMona_CheckHarbour())
			{
				dialog.text = "Los materiales están disponibles, todo está listo. La construcción tomará 4 meses.";
				link.l1 = "No tienes prisa, ¿verdad? Bueno, buena suerte, Rodrigo.";
				link.l1.go = "Himenes_harbour_1";
			}
			else
			{
				dialog.text = "Me temo que no hay suficientes materiales en el almacén. Por favor, revisa la lista de nuevo.";
				link.l1 = "Me encargaré de ello.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_tavern":
			if (IslaMona_CheckTavern())
			{
				dialog.text = "Los materiales están disponibles, todo está listo. La construcción tomará 3 meses.";
				link.l1 = "No tienes prisa, ¿verdad? Bueno, buena suerte, Rodrigo.";
				link.l1.go = "Himenes_tavern_1";
			}
			else
			{
				dialog.text = "Me temo que no hay suficientes materiales en el almacén. Por favor, revisa la lista de nuevo.";
				link.l1 = "Me encargaré de ello.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_plantation":
			if (IslaMona_CheckPlantation())
			{
				dialog.text = "Los materiales están disponibles, todo está listo. La construcción tomará 6 meses.";
				link.l1 = "No tienes prisa, ¿verdad? Buena suerte, Rodrigo.";
				link.l1.go = "Himenes_plantation_1";
			}
			else
			{
				dialog.text = "Me temo que no hay suficientes materiales en el almacén. Por favor, revisa la lista de nuevo.";
				link.l1 = "Me encargaré de ello.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_73":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_harbour_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemoveHarbour();
			pchar.questTemp.IslaMona.Harbour = "true";
			SetFunctionTimerCondition("IslaMona_BuildHarbour", 0, 0, 120, false);
		break;
		
		case "Himenes_harbour_2":
			dialog.text = "Bienvenido, Capitán. ¿Qué le parece su nuevo puerto?";
			if (stf(environment.time) > 22.0 || stf(environment.time) < 5.0)
			{
				link.l1 = "¡Está oscuro, Rodrigo! ¡Casi chocamos con tu alabado muelle! ¡Bien hecho por al menos iluminarlo!";
				link.l1.go = "Himenes_harbour_3";
			}
			else
			{
				link.l1 = "¡No está mal, Rodrigo! Parece una cosa pequeña, pero es agradable caminar por estas tablas hasta la orilla. Y la bahía se ha vuelto más fácil de navegar. Entonces, supongo que ahora puedo acomodar más barcos en esta pequeña bahía, ¿verdad?";
				link.l1.go = "Himenes_harbour_4";
			}
		break;
		
		case "Himenes_harbour_3":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_51";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_harbour_4":
			sld = characterFromId("Islamona_carpenter");
			sld.portman.info = "true"; // если вдруг до сих пор не говорил об условиях стоянки
			pchar.questTemp.IslaMona.Harbour = "done"; // флаг - пристань построена и сдана
			dialog.text = "Sí, Capitán. Debo decir, hay un cierto orgullo en ello. No dude en avisarme cómo le gustaría continuar con nuestro gran proyecto de construcción.";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation") && pchar.questTemp.IslaMona.Plantation == "complete") // если пересеклось со сдачей фактории
			{
				link.l1 = "Hablando de construcción.  Mi fábrica también debería estar terminada para ahora.  ¿Verdad, Rodrigo?";
				link.l1.go = "Himenes_plantation_2";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "Himenes_harbour_5";
			}
		break;
		
		case "Himenes_harbour_5":
			DialogExit();
			IslaMona_HarbourClear();
		break;
		
		case "Himenes_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemoveTavern();
			pchar.questTemp.IslaMona.Tavern = "true";
			SetFunctionTimerCondition("IslaMona_BuildTavern", 0, 0, 90, false);
		break;
		
		case "Himenes_tavern_2":
			dialog.text = "¡H-hip! ¡Capitán! ¡Estamos celebrando aquí!";
			link.l1 = "Rodgar. Rodrigo. ¡Oh, maldición!";
			link.l1.go = "Himenes_tavern_3";
		break;
		
		case "Himenes_tavern_3":
			dialog.text = "¿Qué sucede, c-c-capitán? ¿No te gusta el color de las paredes?";
			link.l1 = "¡Ahora me doy cuenta de que ustedes dos comparten el mismo nombre! ¡Ja-ja-ja! ¡Un español y un pirata, con el mismo nombre, construyeron una taberna en una isla desierta y beben juntos como si los dioses indios fueran a devorar a todos y acabar con el mundo al amanecer! ¡Ja-ja! ¡Estoy con ustedes!";
			link.l1.go = "Himenes_tavern_4";
		break;
		
		case "Himenes_tavern_4":
			dialog.text = "¡Ja-ja-ja! ¡Tan cierto! ¡Punto!";
			link.l1 = "¡Gol!";
			link.l1.go = "Himenes_tavern_5";
		break;
		
		case "Himenes_tavern_5":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_ReloadTavern();
		break;
		
		case "Himenes_plantation_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemovePlantation();
			pchar.questTemp.IslaMona.Plantation = "true";
			SetFunctionTimerCondition("IslaMona_BuildPlantation", 0, 0, 180, false);
		break;
		
		case "Himenes_plantation_2":
			dialog.text = "Todo está listo. ¿Vamos? Déjame mostrarte tu fábrica.";
			link.l1 = "Lidera el camino.";
			link.l1.go = "Himenes_plantation_3";
		break;
		
		case "Himenes_plantation_3":
			DialogExit();
			pchar.questTemp.IslaMona.Plantation.Harbour = "true"; // наложилась сдача пристани и фактории
			IslaMona_PlantationGo();
		break;
		
		case "Himenes_plantation_4":
			dialog.text = "Capitán, casi todo está listo para empezar las operaciones. Viviendas para los trabajadores, almacén para materias primas, área de procesamiento - se ha construido una fábrica digna. Ya hemos marcado los árboles más prometedores para la tala en la jungla. Trae quince trabajadores y el inventario acordado - 15 grilletes y mosquetes, y empezaremos a trabajar.";
			link.l1 = "¿Nosotros? ¿Te refieres a los esclavos?";
			link.l1.go = "Himenes_plantation_5";
		break;
		
		case "Himenes_plantation_5":
			dialog.text = "¡Ja! Esclavos... Los esclavos cortarán, los colonos procesarán y los piratas vigilarán. Todos tendrán trabajo: te has embarcado en una empresa seria, Capitán.";
			link.l1 = "Casi como la tierra prometida, ¿eh? Espera los bienes, es hora de que vaya a cazar.";
			link.l1.go = "Himenes_plantation_6";
		break;
		
		case "Himenes_plantation_6":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Plantation.Slave = "true"; // привезти рабов, кандалы и мушкет для запуска фактории
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "IslaMona_factoria_residence", "sit", "sit1", "IslaMona_PlantationHouse", -1);
			sld = characterFromId("Islamona_carpenter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5);
			pchar.questTemp.IslaMona.Plantation = "done"; // флаг - фактория построена и сдана
		break;
		
		case "Himenes_plantation_7":
			dialog.text = "Un destino triste... Nunca dejarán este lugar.";
			link.l1 = "Rodgar... ¡Quiero decir, Rodrigo! En primer lugar, podrían irse. Y en segundo lugar, si hubieras conocido a alguien más en Terks, tu destino no sería mejor.";
			link.l1.go = "Himenes_plantation_8";
		break;
		
		case "Himenes_plantation_8":
			dialog.text = "Lo sé muy bien, Capitán. Y no lo olvido. Déjeme contarle sobre el funcionamiento de esta fábrica. A partir del próximo mes, el día quince, entregaremos cuarenta troncos de bacout procesado. Por supuesto, no tiene que venir por cada entrega todos los meses - todos los lotes serán almacenados y lo estarán esperando aquí mismo, en la fábrica.";
			link.l1 = "Entonces, ¿puedo recoger varios lotes a la vez?";
			link.l1.go = "Himenes_plantation_9";
		break;
		
		case "Himenes_plantation_9":
			dialog.text = "Dentro de lo razonable, por supuesto - no te alejes por mucho tiempo. La gente no trabajará años sin paga, sin saber si su único cliente sigue vivo o no. Creo que entregaremos seis lotes antes de suspender las operaciones.";
			link.l1 = "¿Tengo que recoger todas las mercancías de una vez? ¿Y el precio, recuérdame?";
			link.l1.go = "Himenes_plantation_10";
		break;
		
		case "Himenes_plantation_10":
			dialog.text = "Sí, todo de una vez. El precio de un tronco estándar de bacout es de diez doblones. Además, por cada lote, tendrás que dar cinco botellas de buen ron y el mismo número de botellas de vino. Rodgar afirma que no encontrarás tales precios en ningún otro lugar del mundo.";
			link.l1 = "¡Ciertamente, estoy de acuerdo! Gracias, Rodrigo. ¡Pongámonos a trabajar!";
			link.l1.go = "Himenes_plantation_11";
		break;
		
		case "Himenes_plantation_11":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			DeleteAttribute(pchar, "questTemp.IslaMona.Plantation.Slave");
			AddQuestRecordInfo("Unique_Goods", "5");
			IslaMona_RemoveSlave();
		break;
		
		case "Himenes_plantation_12":
			dialog.text = "¡Excelente! ¡Ahora empezaremos a trabajar de nuevo!";
			link.l1 = "Bien.";
			link.l1.go = "Himenes_plantation_13";
		break;
		
		case "Himenes_plantation_13":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_FactoryReActivar(); // запустить факторию
		break;
		
		case "Himenes_plantation_14":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_bacaut":
			dialog.text = "Por supuesto, capitán, tómelo. Tenemos los siguientes lotes listos para la próxima fecha: "+sti(pchar.questTemp.IslaMona.Factory.Part)+", eso es "+sti(pchar.questTemp.IslaMona.Factory.Goods)+" troncos. Por lo tanto, nos debes "+sti(pchar.questTemp.IslaMona.Factory.Dublon)+"  doblones, "+sti(pchar.questTemp.IslaMona.Factory.Bottle)+"botellas de ron, y "+sti(pchar.questTemp.IslaMona.Factory.Bottle)+" botellas de vino, ¿tienes todo eso?";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.IslaMona.Factory.Dublon) && PCharItemsTotal("potionrum") >= sti(pchar.questTemp.IslaMona.Factory.Bottle) && PCharItemsTotal("potionwine") >= sti(pchar.questTemp.IslaMona.Factory.Bottle))
			{
				link.l1 = "Por supuesto. Aquí está tu pago.";
				link.l1.go = "Himenes_bacaut_1";
			}
			else
			{
				link.l1 = "Parece que no tengo todo. Lo traeré de inmediato.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_bacaut_1":
			if (IslaMona_CheckBacautSpace())
			{
				dialog.text = "Excelente. Transportaremos el bacalao desde la fábrica a tu almacén, desde donde podrás recogerlo cuando quieras.";
				link.l1 = "Estupendo. Prepara el siguiente lote.";
				link.l1.go = "Himenes_bacaut_2";
			}
			else
			{
				dialog.text = "¡Espera, capitán! Tu almacén está lleno - no podremos cargar todo el tabaco cosechado allí. Libera espacio en el almacén - luego vuelve a verme.";
				link.l1 = "Está bien, me encargaré de ello.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_bacaut_2":
			dialog.text = "¡Por supuesto, capitán!";
			link.l1 = "... ";
			link.l1.go = "Himenes_73";
			IslaMona_FactoryTrade();
		break;
		
		case "Himenes_church":
			dialog.text = "¡Ja! Capitán, me temo que construir algo más sería una locura y extravagancia innecesaria. A menos que...";
			link.l1 = "¿A menos que qué?";
			link.l1.go = "Himenes_church_1";
		break;
		
		case "Himenes_church_1":
			dialog.text = "Capitán, es incómodo para mí preguntar sobre esto... ¡Ya has invertido una suma enorme en este lugar!";
			link.l1 = "¿Un burdel?";
			link.l1.go = "Himenes_church_2_1";
			link.l2 = "¿Una iglesia?";
			link.l2.go = "Himenes_church_2_2";
		break;
		
		case "Himenes_church_2_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "¡Juro por San Santiago, que no estaría mal! Pero en la primera noche, nuestras mujeres lo quemarían. Junto con nosotros. No, capitán, hablo de una iglesia. Sí, tenemos viviendas decentes y paga, el mar y entretenimiento, familias y amigos. Pero aún falta algo, ¿entiende?";
			link.l1 = "Me lo puedo imaginar.";
			link.l1.go = "Himenes_church_3";
		break;
		
		case "Himenes_church_2_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			AddCharacterExpToSkill(pchar, "Defence", 500);
			dialog.text = "Me ves a través, capitán. Sí, tenemos alojamiento decente y paga, el mar y entretenimiento, familias y amigos. Pero aún así, falta algo, ¿entiendes?";
			link.l1 = "Me lo imagino.";
			link.l1.go = "Himenes_church_3";
		break;
		
		case "Himenes_church_3":
			dialog.text = "Exactamente. No podemos construir la Casa de Dios sin tu ayuda. Un lugar así debe ser especial, debe ser de otro mundo. Y por lo tanto, debería ser caro. Necesitaremos velas, lingotes de oro, ámbar y, por supuesto, materiales de construcción, y no baratos. No te traerá ningún beneficio, así que no me atrevo a pedirlo.";
			link.l1 = "Entonces, ¿necesitas traer a un sacerdote aquí?";
			link.l1.go = "Himenes_church_4";
		break;
		
		case "Himenes_church_4":
			dialog.text = "No.";
			link.l1 = "¿Ya tenéis un sacerdote entre vosotros?";
			link.l1.go = "Himenes_church_5";
		break;
		
		case "Himenes_church_5":
			dialog.text = "No, capitán. Y creo que ya entiendes todo.";
			link.l1 = "Entonces, ¿tuvieron los santos padres de la Inquisición una razón para perseguirte? ¿Sois herejes?";
			link.l1.go = "Himenes_church_6";
		break;
		
		case "Himenes_church_6":
			dialog.text = "Por las leyes canónicas, somos los peores de los herejes. No creemos que comunicarse con Dios requiera necesariamente un intermediario de este mundo.";
			link.l1 = "¿De este mundo?";
			link.l1.go = "Himenes_church_7";
		break;
		
		case "Himenes_church_7":
			dialog.text = "Capitán,  no somos satanistas, y nuestra comunidad no es una secta. Somos cristianos, como usted, pero vemos las cosas con una perspectiva muy amplia. Demasiado amplia, según algunas personas muy educadas y dignas. Si alguna vez encuentra un lugar en su corazón para la apertura y la comprensión, entonces le contaré más. Pero por ahora, solo tome esta lista. Por si acaso.";
			link.l1 = "¡Deberías haberme contado sobre esto antes, Rodrigo! ¡No quiero regresar un buen día y encontrarme con un aquelarre de brujas o el nacimiento de una nueva fe en mi tierra! Mientras esperas, tomaré una decisión.";
			link.l1.go = "Himenes_church_8_1";
			link.l2 = "Impresionante lista. ¡Empiezo a entender por qué los santos padres necesitan tanto dinero! Pensaré en tu oferta, Rodrigo, y tomaré una decisión.";
			link.l2.go = "Himenes_church_8_2";
		break;
		
		case "Himenes_church_8_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			dialog.text = "";
			link.l1 = "Si es positivo, traeré todos los bienes de tu lista al almacén, y pondré los tesoros sobre la mesa para ti.";
			link.l1.go = "Himenes_church_9";
		break;
		
		case "Himenes_church_8_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			dialog.text = "";
			link.l1 = "Si es positivo, traeré todos los bienes de tu lista al almacén, y te pondré los tesoros sobre la mesa.";
			link.l1.go = "Himenes_church_9";
		break;
		
		case "Himenes_church_9":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "start";
			AddQuestRecord("IslaMona", "14");
			AddQuestRecordInfo("IslaMonaData", "3");
		break;
		
		case "Himenes_church_10":
			dialog.text = "En nombre de toda nuestra comunidad, te agradezco, capitán. ¡No te arrepentirás de esto, lo juro!";
			link.l1 = "Solo lo lamentaré si construyes algo completamente destartalado.";
			link.l1.go = "Himenes_church_10_1";
		break;
		
		case "Himenes_church_10_1":
			dialog.text = "¡Capitán, todos los materiales de construcción están en stock! Comenzaremos la construcción una vez que traiga los artículos de lujo enumerados. Se utilizarán para joyería y herramientas rituales. De nuevo, ¡muchas gracias, Capitán! ¡Muchas gracias!";
			link.l1 = "¡De nada!";
			link.l1.go = "Himenes_church_10_2";
		break;
		
		case "Himenes_church_10_2":
			DialogExit();
			IslaMona_RemoveChurch();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "Wait_candles";
			pchar.questTemp.IslamonaChurch.GoldNugget = 50;
			pchar.questTemp.IslamonaChurch.Candle = 100;
			pchar.questTemp.IslamonaChurch.Amber = 30;
			pchar.questTemp.IslamonaChurch.BlueAmber = 1;
		break;
		
		case "Himenes_church_10_3":
			IslaMona_RemoveCandles();
			string sAdd = "";
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Candle"))
			{
				sAdd += " "+sti(pchar.questTemp.IslamonaChurch.Candle)+ " candles,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Amber"))
			{
				sAdd += " "+sti(pchar.questTemp.IslamonaChurch.Amber)+ " amber,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.GoldNugget"))
			{
				sAdd += " "+ sti(pchar.questTemp.IslamonaChurch.GoldNugget) + " ingots,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.BlueAmber"))
			{
				sAdd += " and one blue amber"
			}
			if(sAdd == "")
			{
				dialog.text = "¡Muchísimas gracias, capitán! Todo está listo, estamos comenzando la construcción. Regrese en un par de meses para el primer servicio. ¡Ah, y una cosa más, las uvas están maduras! Haremos vino casero, celebraremos y festejaremos en su honor.";
				link.l1 = "Creo que todos merecemos una celebración. Regresaré en dos meses.";
				link.l1.go = "Himenes_church_12";
			}
			else
			{
				dialog.text = "Capitán, todavía hay "+sAdd+" izquierdo.";
				link.l1 = "Claro, solo dame un poco más de tiempo, por favor. Honestamente, si no fuera por las velas, pensaría que vas a enterrar un tesoro.";
				link.l1.go = "Himenes_church_11";
			}
		break;
		
		case "Himenes_church_11":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_church_12":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "build";
			AddQuestRecord("IslaMona", "15");
			//IslaMona_RemoveChurch();
			SetFunctionTimerCondition("IslaMona_ChurchComplete", 0, 0, 60, false);
		break;
		
		case "Himenes_church_13":
			dialog.text = "¡Ja-ja-ja-ja-ja-ja-ja-ja-ja-ja-ja!";
			link.l1 = "Y aquí pensé que te habías deshecho de ese hábito idiota.";
			link.l1.go = "Himenes_church_14";
		break;
		
		case "Himenes_church_14":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (i >= 50) sTemp = "que no tendremos que estar aquí sentados durante semanas esperando a que se desarrollen los acontecimientos.";
			else sTemp = "que no todos tendrán que participar en la batalla.";
			dialog.text = "Ja-ja-ja-ja-ja... ja. ¡Yo también lo pensé, capitán! Rodgar tiene razón, tu presencia ya significa, "+sTemp+"";
			link.l1 = "Ya sé lo que pasó. ¿Hay alguna baja?";
			if (GetCharacterIndex("Mirabella") != -1) link.l1.go = "Himenes_church_15";
			else link.l1.go = "Himenes_church_16";
		break;
		
		case "Himenes_church_15":
			DialogExit();
			sld = characterFromId("Mirabella"); 
			sld.dialog.currentnode = "mirabelle_44";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_16":
			dialog.text = "No te preocupes tanto, Rodgar. No es tu culpa, los fusileros llegaron demasiado rápido. De todas formas, no habríamos podido mantenerlos detrás de nuestras líneas, y no hubo tiempo de pasarlos a todos por la espada.";
			link.l1 = "¿Qué pasa con los españoles?";
			link.l1.go = "Himenes_church_17";
		break;
		
		case "Himenes_church_17":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Force")) // решил проблему самостоятельно
			{
				dialog.text = "Solo tres de ellos llegaron a nosotros, y solo uno sobrevivió. ¡El capitán mismo! Aparentemente, un marino militar muy serio. Pero no puede ayudarnos aún, tendrá que quedarse en la cama al menos un par de días más. Por cierto, capitán, oímos disparos y, a juzgar por su aspecto, usted también.";
				link.l1 = "Podría decirse que sí. Los invitados no invitados claramente no esperaban una visita tan inesperada y fueron arrojados de nuevo al mar.";
				link.l1.go = "Himenes_church_20";
			}
			else
			{
				dialog.text = "Solo tres de ellos llegaron hasta nosotros, y solo uno sobrevivió. ¡El capitán mismo! Por lo visto, un marinero militar muy serio. Pero aún no puede ayudarnos - tendrá que quedarse en cama al menos un par de días más.";
				if (i >= 50) 
				{
					link.l1 = "La última vez, dejé a bastantes de mis hombres aquí de guardia, así que debería haber muchos más de vosotros que de fusileros. ¿Por qué no los arrojasteis a todos al mar de una vez?";
					link.l1.go = "Himenes_church_17_1";
				}
				else 
				{
					link.l1 = "Bien, resolvamos este problema. El plan es este: los atraeré para un asalto abierto, y ahora mismo. No tiene sentido demorarse. Prepárense con perdigones y mosquetes, piratas en las puertas, el resto se queda en casa y manténganse firmes.";
					link.l1.go = "Himenes_church_18";
				}
			}
		break;
		
		case "Himenes_church_17_1":
			dialog.text = "Capitán, son todos soldados profesionales, con un comandante. Y nosotros ni siquiera tenemos armas adecuadas. Sí, por supuesto, podríamos haberlos superado en número, pero habríamos perdido al menos el doble de personas, y cada persona es valiosa y necesaria aquí.";
			link.l1 = "Está bien, resolvamos este problema. El plan es el siguiente: los atraeré para un asalto abierto, y ahora mismo. No tiene sentido retrasarlo. Prepárense con perdigones y mosquetes, piratas en las puertas, el resto queda en casa y manténganse firmes.";
			link.l1.go = "Himenes_church_18";
		break;
		
		case "Himenes_church_18":
			dialog.text = "¡Capitán, estamos listos para luchar!";
			link.l1 = "Lo sé, Rodrigo. Pero no me dejaste terminar: si siquiera un enemigo logra atravesar las puertas, debéis abalanzaros sobre él desde todos los lados. Y en la batalla, vuestras posibilidades de recibir una bala o un fragmento disminuyen. ¿Alguna otra pregunta?";
			link.l1.go = "Himenes_church_19";
		break;
		
		case "Himenes_church_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_68";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_20":
			dialog.text = "¡Bien hecho! Es desagradable, por supuesto, que un destino tan desafortunado haya caído sobre tus compatriotas. Pero estoy agradecido de que una vez más hayas tomado nuestro lado.";
			link.l1 = "No fue fácil, Rodrigo. La gente normal lo llamará traición, y tendrán razón.";
			link.l1.go = "Himenes_church_20_1";
			link.l2 = "Esta es mi tierra, Rodrigo. Necesita ser defendida siempre y no importa de quién.";
			link.l2.go = "Himenes_church_20_2";
		break;
		
		case "Himenes_church_20a":
			dialog.text = "Sí, el viejo Rodrigo no esperaba, cuando dejó Cádiz, que tales aventuras lo aguardaban en el Nuevo Mundo.";
			link.l1 = "No me lo digas. A veces todavía tengo exactamente los mismos pensamientos.";
			link.l1.go = "Himenes_church_20b";
		break;
		
		case "Himenes_church_20b":
			dialog.text = "Es desagradable, por supuesto, que un destino tan desafortunado haya caído sobre tus compatriotas. Pero estoy agradecido de que una vez más hayas tomado nuestro lado.";
			link.l1 = "No fue fácil, Rodrigo. La gente normal lo llamará traición, y tendrán razón.";
			link.l1.go = "Himenes_church_20_1";
			link.l2 = "Esta es mi tierra, Rodrigo. Necesita ser defendida siempre y sin importar de quién.";
			link.l2.go = "Himenes_church_20_2";
		break;
		
		case "Himenes_church_20_1":
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			dialog.text = "Entiendo, capitán. Permítame entonces darle un breve resumen de la situación en nuestro asentamiento durante su ausencia.";
			link.l1 = "¿De verdad? Espera... ¿Capitán?";
			link.l1.go = "Himenes_church_21";
		break;
		
		case "Himenes_church_20_2":
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			dialog.text = "Entiendo, capitán. Permítame entonces darle un breve resumen de la situación en nuestro asentamiento durante su ausencia.";
			link.l1 = "¿De veras? Espera... ¿Capitán?";
			link.l1.go = "Himenes_church_21";
		break;
		
		case "Himenes_church_21":
			dialog.text = "No quería ofender. Es solo que Rodgar dice esa palabra tan deliciosamente que yo también quería intentarlo. Muy... Pirata.";
			link.l1 = "Sin problema, solo sorprendido. ¿Entonces qué pasó aquí?";
			link.l1.go = "Himenes_church_22";
		break;
		
		case "Himenes_church_22":
			dialog.text = "Primero, construimos la iglesia. Tardará un minuto, entra. Hay algo que ver. Has hecho una gran obra, capitán. Puede que no te lo parezca, pero poder comunicarse con Dios es muy, muy importante para nosotros. Desde este día en adelante, llamamos a Isla Mona nuestro hogar.";
			link.l1 = "¿Hogar, dulce hogar? Definitivamente echaré un vistazo. ¿Llevé todas esas velas para nada?";
			link.l1.go = "Himenes_church_23";
		break;
		
		case "Himenes_church_23":
			dialog.text = "¡No por nada! En segundo lugar, la fábrica fue arruinada - perdimos toda la mano de obra. Tendrás que traer un nuevo lote de esclavos. Afortunadamente, después de reevaluar la eficiencia del trabajo, llegamos a la conclusión de que diez esclavos serán más que suficientes. Así que, menos molestias para ti.";
			link.l1 = "Está bien. ¿Algo más?";
			link.l1.go = "Himenes_church_24";
		break;
		
		case "Himenes_church_24":
			dialog.text = "Todo está listo para la celebración. Bueno, casi: necesitamos limpiar aquí, enterrar los cuerpos de esas almas desafortunadas... Así que ven a la iglesia mañana y comenzaremos.";
			link.l1 = "¿A la iglesia? Lugar extraño para comenzar la fiesta. ¿Piensas proponer matrimonio, Rodrigo?";
			link.l1.go = "Himenes_church_25";
		break;
		
		case "Himenes_church_25":
			dialog.text = "¡Ja, ja! No, capitán, aunque a algunas de nuestras chicas no les importaría. No nos importa si lo hace.";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && IsOfficer(characterFromId("Mary")))
			{
				link.l1 = "";
				link.l1.go = "Himenes_church_25_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1 && IsOfficer(characterFromId("Helena")))
				{
					link.l1 = "";
					link.l1.go = "Himenes_church_25_2";
				}
				else
				{
					link.l1 = "De acuerdo, mañana iremos a la iglesia. A rezar, por supuesto.";
					if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Common") || CheckAttribute(pchar, "questTemp.IslaMona.Defend.Force")) link.l1.go = "Himenes_church_28";
					else link.l1.go = "Himenes_church_26";
				}
			}
		break;
		
		case "Himenes_church_25_1":
			DialogExit();
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "IslaMona";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_25_2":
			DialogExit();
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "IslaMona";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_26":
			dialog.text = "Y una cosa más, capitán. Antes de la celebración, ve y trata con el prisionero primero. La decisión debe tomarse, y entiendo que será desagradable de todos modos.";
			link.l1 = "Está bien. Iré ahora mismo.";
			link.l1.go = "Himenes_church_27";
		break;
		
		case "Himenes_church_27":
			DialogExit();
			DoQuestReloadToLocation("IslaMona_factoria", "reload", "reload1", "IslaMona_DefFraPrisoner"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
		break;
		
		case "Himenes_church_28":
			DialogExit();
			WaitDate("", 0, 0, 0, 3, 5); //крутим время
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			IslaMona_DefBattleLightClear();
			DoQuestReloadToLocation("IslaMona_town", "quest", "detector1", "");
		break;
		
		case "Himenes_church_29":
			dialog.text = "¡Todos están aquí! Señor, no sabemos qué quería usted inicialmente de este lugar y cómo lo ve para usted ahora. Para nosotros, primero fue un refugio forzado, y ahora se ha convertido en un verdadero hogar. Aquí viven sus marineros, piratas y herejes españoles fugitivos. En cualquier otro lugar del mundo, ya nos habríamos degollado unos a otros. Pero aquí somos amigos, trabajamos y disfrutamos de la vida. Isla Mona no es el punto final en el mapa de este mundo para ninguno de nosotros, pero quizás aquí pasaremos los años más felices y fructíferos de nuestras vidas. Y este es su mérito, su tierra y su gente. Muchas gracias, "+pchar.name+".";
			link.l1 = "";
			link.l1.go = "Himenes_church_30";
			locCameraFromToPos(-4.11, 1.55, 1.09, true, -4.55, -0.20, 3.08);
		break;
		
		case "Himenes_church_30":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_86";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		case "Himenes_church_31":
			dialog.text = "Está bien, está bien. Capitán, hemos reunido regalos para usted: una multitud de cosas útiles y simplemente agradables. Algunas las trajimos con nosotros, y otras las hicimos nosotros mismos. Acepte este regalo con un corazón puro, y el resto se lo daremos con nuestro arduo trabajo.";
			link.l1 = "Gracias... No esperaba esto. Tan pocos momentos brillantes y simple humanidad en mi odisea... Significa mucho para mí, créeme.";
			link.l1.go = "Himenes_church_32";
			locCameraFromToPos(-4.11, 1.55, 1.09, true, -4.55, -0.20, 3.08);
		break;
		
		case "Himenes_church_32":
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "GunEchin", 10);
			TakeNItems(pchar, "slave_01", 10);
			TakeNItems(pchar, "grenade", 10);
			TakeNItems(pchar, "obereg_7", 1);
			TakeNItems(pchar, "purse3", 1);
			TakeNItems(pchar, "jewelry47", 1);
			TakeNItems(pchar, "jewelry52", 1);
			TakeNItems(pchar, "berserker_potion", 1);
			TakeNItems(pchar, "potion5", 10);
			TakeNItems(pchar, "cannabis7", 1);
			dialog.text = "¡Y ahora, de vuelta al trabajo!";
			link.l1 = "No, ahora es, ¡a la taberna! ¡Rodrigo, vamos!";
			link.l1.go = "Himenes_church_33_1";
			link.l2 = "Sí, saboreemos este maravilloso momento un poco más.";
			link.l2.go = "Himenes_church_33_2";
		break;
		
		case "Himenes_church_33_1":
			DialogExit();
			DoQuestReloadToLocation("IslaMona_Town", "sit", "sit_base2", "IslaMona_ChurchToTavern"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
		break;
		
		case "Himenes_church_33_2":
			DialogExit();
			LAi_SetActorType(pchar);
			ChangeShowIntarface();
			ResetSound();
			SetMusic("music_terrain");
			InterfaceStates.Buttons.Save.enable = false;
			bDisableCharacterMenu = true;
			pchar.GenQuest.FrameLockEsc = true;
			locCameraRotateAroundHero(0.0, 1.5, 0.0, 0.005, 0.0, 1.5, 0.0, 10000);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("IslaMona_ChurchTavernExit", 45.0);
		break;
		
		case "Himenes_74":
			dialog.text = "¡Ja, ja! ¡Hic!";
			link.l1 = "Por cierto, veo que casi has dejado de reírte a carcajadas por todo y por nada. ¿El aire fresco del Caribe?";
			link.l1.go = "Himenes_75";
		break;
		
		case "Himenes_75":
			dialog.text = "Más bien la influencia corruptora de Rodgar. Viéndolo, aprendí a mandar todo al carajo.";
			link.l1 = "";
			link.l1.go = "Himenes_76";
		break;
		
		case "Himenes_76":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_90";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_77":
			dialog.text = "Conozco a muchas personas respetables de allí.";
			link.l1 = "";
			link.l1.go = "Himenes_78";
		break;
		
		case "Himenes_78":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_93";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_79":
			dialog.text = "Nope,  prefiero seguir bebiendo ron y mirándote con desprecio.";
			link.l1 = "";
			link.l1.go = "Himenes_80";
		break;
		
		case "Himenes_80":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_96";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_81":
			dialog.text = "¡Capitán! ¡Hic!";
			link.l1 = "Hola a ti también, Rodrigo. ¿Tuviste una noche llena de acontecimientos, veo?";
			link.l1.go = "Himenes_82";
		break;
		
		case "Himenes_82":
			dialog.text = "Mejor... no preguntes. Un mes... no beberé. Oh. ¡Tengo noticias! El capitán...recobró el juicio.";
			link.l1 = "¿El único español sobreviviente?";
			link.l1.go = "Himenes_83";
		break;
		
		case "Himenes_83":
			dialog.text = "¡Hic! ¡Ay! Sí, lo pusieron en la factoría, en una casa bajo custodia.";
			link.l1 = "Correcto. Iré a él. Cuida de no exagerar.";
			link.l1.go = "Himenes_84";
		break;
		
		case "Himenes_84":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10); /// ОН ИДЕТ НА ВЫХОД, ПОСТАВИТЬ ПРАВИЛЬНЫЙ ЛОКАТОР
			IslaMona_ChurchSetHispanos();
		break;
		
		case "Himenes_85":
			dialog.text = "Me di un chapuzón, y ¡todo está como nuevo! Viviremos y trabajaremos. Intentaré que la factoría funcione el mayor tiempo posible. Bueno, y hacer reparaciones, trabajos menores de construcción. Quizás incluso decidir sobre los hijos con la mía.";
			link.l1 = "¡Feliz por todos vosotros! Fue una aventura muy nerviosa, costosa... y maravillosa, y me alegra que nos haya salido bien. ¡Buena suerte a todos, y a los que zarpamos, aún más suerte!";
			link.l1.go = "Himenes_86";
		break;
		
		case "Himenes_86":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_Final", -1);
			sld = characterFromId("Islamona_carpenter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		// солдат в бухте
		case "Capral":
			dialog.text = "¡Alto! Cabo "+GetFullName(npchar)+". ¡Has aterrizado en una zona de combate! ¡Identifícate inmediatamente y declara el propósito de tu presencia aquí!";
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				link.l1 = "¡Cabo, retirese!"+GetFullName(pchar)+", capitán de la Marina Francesa. ¡Le ordeno que me escolte hasta su oficial superior. ¡Cumpla la orden!";
				link.l1.go = "Capral_1";
			}
			else
			{
				link.l1 = ""+GetFullName(pchar)+", capitán del barco llamado '"+pchar.ship.name+"'. Llegué a esta isla completamente por casualidad - para posibles reparaciones y para reabastecer suministros de agua fresca.";
				link.l1.go = "Capral_3";
			}
		break;
		
		case "Capral_1":
			if(IsUniformEquip())
			{
				dialog.text = "¡Sí, señor, Capitán! Por favor, sígame. Solo le ruego, ¡tenga cuidado! Esta isla está plagada de bandidos.";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Le ruego me disculpe, Capitán. No lleva el uniforme, así que estoy obligado a verificar su patente de oficial.";
				link.l1 = "¿Ves? ¿Satisfecho? ¡Ahora - apresúrate a cumplir la orden, cabo!";
			}
			link.l1.go = "Capral_2";
		break;
		
		case "Capral_2":
			DialogExit();
			AddQuestRecord("IslaMona", "16");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_DefReloadFactory", 20.0);
		break;
		
		case "Capral_3":
			dialog.text = "Tendrás que venir conmigo, capitán. Nuestro oficial superior hablará contigo. A partir de este momento, tu barco se considera requisado temporalmente para las necesidades de la Marina Francesa. Notifica inmediatamente a la guardia actual y sígueme.";
			link.l1 = "¿Requisar el barco Charle Prince? ¡No lo creo!";
			link.l1.go = "Capral_5";
			link.l2 = "Parece que no tengo opción. Haré lo que dices.";
			link.l2.go = "Capral_4";
		break;
		
		case "Capral_4":
			DialogExit();
			AddQuestRecord("IslaMona", "18");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_DefReloadFactory", 5.0);
		break;
		
		case "Capral_5":
			DialogExit();
			DoQuestFunctionDelay("IslaMona_DefKillCapral", 1.0);
		break;
		
		case "Capral_6":
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				dialog.text = "Señor Capitán, el camino al campamento enemigo está a nuestra derecha. Le escoltaré.";
				link.l1 = "Relájate, cabo. Prefiero ir solo.";
			}
			else
			{
				dialog.text = "Capitán, el camino al campamento enemigo está a nuestra derecha. No te perderás.";
				link.l1 = "Gracias por tu preocupación.";
			}
			link.l1.go = "Capral_7";
		break;
		
		case "Capral_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			IslaMona_DefGotoMarch();
			pchar.quest.islamona_def_killslaves.win_condition.l1 = "location";
			pchar.quest.islamona_def_killslaves.win_condition.l1.location = "IslaMona_town";
			pchar.quest.islamona_def_killslaves.function = "IslaMona_DefKillSlaves";
		break;
		
		case "FraOfficer":
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				dialog.text = "Capitán "+GetFullName(pchar)+"¡Gracias a Dios! Permitidme que me presente - Teniente "+GetFullName(npchar)+". ¡Un gran admirador suyo! No sé qué está haciendo en este miserable pedazo de tierra, ¡pero ha llegado justo a tiempo!\nDebo decir, Capitán, que se ha vuelto muy popular entre nuestros oficiales. Aunque a muchos les molesta su... 'especial' estilo de servicio, todos coinciden en que su patente hace nuestra flota más fuerte. Actualmente estamos en una situación completamente estancada, así que la asistencia de alguien como usted será difícil de sobrestimar.";
				link.l1 = "¿Qué puedo hacer? ¿Y qué está pasando aquí?";
				link.l1.go = "FraOfficer_1";
			}
			else
			{
				dialog.text = "Capitán "+GetFullName(pchar)+"  Tu nombre ha sido mencionado varias veces en los informes de la flota. Y siempre en un tono muy dudoso. Sin embargo, ahora tienes la oportunidad de interrumpir esta tendencia menos honorable y servir a la madre patria.";
				link.l1 = "¿Qué puedo hacer? Y ¿qué está pasando aquí?";
				link.l1.go = "FraOfficer_8";
			}
		break;
		
		case "FraOfficer_1":
			dialog.text = "Estábamos en el 'Guerrero', una misión rutinaria - cazando a unos asaltantes españoles particularmente audaces. El caso es generalmente muy simple: el espía proporciona la área y datos sobre el objetivo, y uno lo atrapa desde el horizonte. No hay nada especial que contar, y todo terminó muy mal: los españoles nos encontraron primero y atacaron, a pesar de que ellos mismos estaban en un corbeta. Si hubiéramos tenido algo más serio, no nos habríamos ido al fondo con nosotros... pero al menos logramos volarles todo el casco. Solo mi escuadrón sobrevivió. Los castellanos, sin embargo, también tuvieron a alguien que sobrevivió. ¡Pero no por mucho tiempo, jaja!";
			if (CheckAttribute(pchar, "questTemp.IslamonaSpaOfficer"))
			{
				link.l1 = "¿La fragata 'Guerrero'? ¿El capitán Shocke murió?";
				link.l1.go = "FraOfficer_1_1";
			}
			else
			{
				link.l1 = "";
				link.l1.go = "FraOfficer_2";
			}
		break;
		
		case "FraOfficer_1_1":
			dialog.text = "No me sorprende que preguntaras por él, Capitán. Escuché sobre tu participación en la intercepción del 'Alcantara'. ¡Una gran hazaña! Ya entonces sentaste las bases para tu patente. ¡El Comandante Shocke no murió, todo lo contrario! Fue ascendido, y a petición suya, enviado a servir en el Mediterráneo. Solo podemos envidiarlo en una situación como la nuestra ahora. Así que, en realidad, sobre nuestra situación...";
			link.l1 = "";
			link.l1.go = "FraOfficer_2";
		break;
		
		case "FraOfficer_2":
			dialog.text = "Encontramos un asentamiento en la isla - una guarida de bandidos bastante poblada para - solo escucha - piratas y españoles. ¡Increíble! Sabes, generalmente estos bastardos solo se cortan y cuelgan entre sí, pero aquí, he aquí: en el mismo centro del archipiélago, trabajan juntos como una familia para extraer madera de bucanero. ¿Has visto el muelle que se han construido? Los invitados no vienen a esta raza en botes de remos. Nuestra tarea es extremadamente clara: con tu ayuda, capturamos el asentamiento, tomamos la madera de bucanero y prisioneros, y tú te llevas a todos a Capsterburgo. Mientras tanto, las autoridades resolverán las cosas por sí mismas... Y mientras lo resuelven, nos ocuparemos de la madera de bucanero y celebraremos debidamente con otros oficiales de mi escuadrón en casa.";
			link.l1 = "¿Qué te impidió tomar el asentamiento por tu cuenta hasta ahora?";
			link.l1.go = "FraOfficer_3";
		break;
		
		case "FraOfficer_3":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (i >= 50) sTemp = "Probablemente haya muchos más bandidos que nosotros, vimos tiendas en la orilla. ¡Y además de tiendas, también tienen un muro, puertas, cañones!";
			else sTemp = "Probablemente no haya tantos bandidos, de lo contrario ya nos habrían echado de aquí. ¡Pero aún disponen de un muro, puertas, cañones y mucho tiempo!";
			dialog.text = "¿Qué nos impidió?! Solo tenemos doce fusileros y siete marineros. Todos cansados y agotados. Salvamos solo cinco mosquetes, ¡con solo un cartucho cada uno en el mejor de los casos!"+sTemp+"";
			link.l1 = "¿Pero tienes un plan?";
			link.l1.go = "FraOfficer_4";
		break;
		
		case "FraOfficer_4":
			dialog.text = "Escucha, no perdimos el tiempo. Primero, tomamos esta fábrica, capturando así algunos suministros de comida y agua, y lo más importante, ¡un almacén lleno de madera de filibustero y más de una docena de esclavos! No habríamos podido vigilar a los esclavos de todos modos, así que inmediatamente realizamos un reconocimiento por combate, enviándolos a atacar a sus antiguos amos bajo la cobertura de nuestros mosquetes. Así es como descubrimos que los bandidos tienen armas en reserva.";
			link.l1 = "¿Entiendo correctamente que ahora quieres enviarme a mí y a mis hombres a tratar con esta arma en lugar de los esclavos?";
			link.l1.go = "FraOfficer_5";
		break;
		
		case "FraOfficer_5":
			dialog.text = "No, pero puedes ir a los bandidos como parlamento. Tu llegada significa que su guarida está expuesta, y ahora los soldados del rey tienen un barco y refuerzos. Bien, mientras ellos están con las orejas en alto y evaluando la profundidad de su profundidad, te acercarás lo más posible al cañón, lanzarás una granada de mano debajo de él, y no te dejes matar hasta que nuestra gente y tu gente se acerquen. Si no estás seguro de poder manejarlo, intenta enviar a uno de tus hombres en lugar de a ti mismo.";
			link.l1 = "Déjame primero ir a ellos sin una bomba y ofrecerles rendirse. Miraré alrededor, entenderé su ánimo y fuerzas, sembraré la duda en sus almas. Si no se rinden, entonces iré a ellos de nuevo, pero con una bomba.";
			if (CheckCharacterItem(pchar, "patent_fra")) link.l1.go = "FraOfficer_6";
			else link.l1.go = "FraOfficer_6_1";
		break;
		
		case "FraOfficer_6":
			GiveItem2Character(pchar, "grenade");
			//Log_Info("Вы получили гранату");
			PlaySound("interface\important_item.wav");
			dialog.text = "... y para entonces, ya estarán acostumbrados a ti, ¡así que será más fácil llevar a cabo el sabotaje! ¡Astuto! Bueno, no esperaba menos de ti, Capitán. Procede cuando estés listo. Pero aun así, aquí... Podría ser útil.";
			link.l1 = "";
			link.l1.go = "FraOfficer_7";
		break;
		
		case "FraOfficer_6_1":
			dialog.text = "... y para entonces, ya estarán acostumbrados a ti, así que será más fácil llevar a cabo el sabotaje. Eso es lo que haremos. ¡Sigue adelante!";
			link.l1 = "";
			link.l1.go = "FraOfficer_7";
		break;
		
		case "FraOfficer_7":
			DialogExit();
			AddQuestRecord("IslaMona", "19");
			chrDisableReloadToLocation = false;
			pchar.quest.islamona_def_goout.win_condition.l1 = "location";
			pchar.quest.islamona_def_goout.win_condition.l1.location = "IslaMona_Jungle_01";
			pchar.quest.islamona_def_goout.function = "IslaMona_DefCapralTalk";
		break;
		
		case "FraOfficer_8":
			dialog.text = "Hubo una prolongada batalla con los españoles en esta área. Ambos barcos se hundieron, y los sobrevivientes terminaron aquí. Mayormente franceses, pero algunos de nuestros enemigos también lograron sobrevivir. Y no necesitas saber más, lo siento, Capitán. Información secreta, entiendes.";
			link.l1 = "Entendido.";
			link.l1.go = "FraOfficer_9";
		break;
		
		case "FraOfficer_9":
			dialog.text = "Encontramos un asentamiento en la isla - un verdadero nido de bandidos poblado por - escucha bien - piratas y españoles. ¡Increíble! Sabes, por lo general, esos bastardos solo se cortan y cuelgan entre ellos, pero aquí, he aquí: en el mismo centro del archipiélago, trabajan juntos como una familia para extraer madera de bucanero. ¿Has visto el muelle que han construido para sí mismos? Los visitantes no vienen a esta raza en botes de remos. Nuestra tarea es extremadamente clara: con tu ayuda, capturamos el asentamiento, tomamos la madera de bucanero y prisioneros, y tú los llevas a Capsterburgo. Mientras tanto, las autoridades se las arreglarán por sí mismas... Y mientras se las arreglan, incluso podría estar listo para darte la oportunidad de llevarte algo de madera valiosa para tus necesidades.";
			link.l1 = "¿Qué te impidió tomar el asentamiento por tu cuenta hasta ahora?";
			link.l1.go = "FraOfficer_3";
		break;
		
		case "FraOfficer_10":
			dialog.text = "¡Aquí estás! ¿Alguna novedad?";
			link.l1 = "¿Es esta una guardia honoraria?";
			link.l1.go = "FraOfficer_11";
		break;
		
		case "FraOfficer_11":
			dialog.text = "Obviamente, se tomará una decisión en breve sobre nuestras acciones futuras. No quisiera buscar a mi gente por toda la isla para dar nuevas órdenes.";
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				link.l1 = "¡Excelente iniciativa! Tendrás tus órdenes. He realizado un reconocimiento: el enemigo es débil y el cañón está sin municiones. Te ordeno que ataques el escondite de los bandidos inmediatamente, teniente. Deja de cuidar tus manos. Solo otro día en la flota. ¡Ejecuta!";
				link.l1.go = "FraOfficer_12";
			}
			else
			{
				link.l1 = "En mi opinión, podrías haberlos tomado justo después del reconocimiento del 'esclavo' por la fuerza. Su defensa es risible, solo un par de luchadores serios. No hay necesidad de pensar demasiado, podríamos haber estado bebiendo vino de trofeo sentados en una montaña de sándalo.";
				link.l1.go = "FraOfficer_14";
			}
		break;
		
		case "FraOfficer_12":
			dialog.text = "¡Afirmativo, Capitán!";
			link.l1 = "...";
			link.l1.go = "FraOfficer_13";
		break;
		
		case "FraOfficer_13":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -25);
			AddQuestRecord("IslaMona", "22");
			IslaMona_DefAttackLight();
		break;
		
		case "FraOfficer_14":
			dialog.text = "¿Y estos son los resultados de tu reconocimiento? Entiendo que pueda ser extraño esperar demasiado de una persona no militar, ¡pero necesito hechos! ¡Hechos, Capitán, no su opinión!";
			link.l1 = "Me ofendes, Teniente. ¡Reportándome!";
			link.l1.go = "FraOfficer_15";
		break;
		
		case "FraOfficer_15":
			dialog.text = "";
			link.l1 = "Ahora mismo, hay un capitán sobreviviente de un barco español que hundiste contigo. Un comandante experimentado que pronto se recuperará. Si te demoras, se recuperará y organizará la defensa según el manual de ciencia militar, y entonces lo tendremos difícil. Necesitamos apresurarnos - repito, están débiles y desmoralizados.";
			link.l1.go = "FraOfficer_15_1";
			link.l2 = "Pronto llegarán refuerzos - para llevarse la madera del bucanero. No creo que sea un farol: tú mismo viste los muelles y una pila de mercancías listas para entregar en el almacén de la fábrica. Necesitamos apresurarnos - repito, están débiles y desmoralizados. Si te demoras, esperarás la llegada de un barco pirata.";
			link.l2.go = "FraOfficer_15_2";
			link.l3 = "Casi la mitad de los habitantes de este agujero son mujeres. No has estado luchando ni siquiera contra la milicia: no ha habido más de una docena de combatientes contra ti todo este tiempo. Son débiles y están desmoralizados.";
			link.l3.go = "FraOfficer_15_3";
			link.l4 = "El cañón se ha quedado sin munición. He visto bastantes cañones en mi vida y sé distinguir cuándo una dotación está lista para disparar y cuándo no. Sin su artillería, no son más que pobres guerreros; están débiles y desmoralizados.";
			link.l4.go = "FraOfficer_15_4";
			link.l5 = "¡Piensa en los trofeos y la gloria, teniente! Una victoria en solitario sobre un asaltante español, capturar un nido de bandidos y una fuente única de madera de bucanero, ¡todo esto reclama comandar tu propio barco! Repito, están débiles y desmoralizados, ¡es hora de aplastarlos!";
			link.l5.go = "FraOfficer_15_5";
		break;
		
		case "FraOfficer_15_1":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 80)
			{
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Gracias, Capitán. Esta es información valiosa, y tenía razón, no hay necesidad de demorarse aquí. Mis hombres están todos aquí, somos fuertes, entrenados y listos. Todo terminará en media hora. Capitán, por favor prepárese para recibir personas, prisioneros y carga en su barco. No nos quedaremos aquí por mucho tiempo.";
				link.l1 = "Todo está listo, teniente. Solo te estábamos esperando a ti. ¡Nos vemos más tarde!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Skill Check Failed (80)", SKILL_LEADERSHIP);
				dialog.text = "Gracias, Capitán. Esta es información valiosa. En ese caso, diríjase al muelle y prepare su equipo de abordaje. Asaltaremos el nido de los bandidos juntos e inmediatamente. Los mejores de mis hombres y los suyos liderarán la vanguardia - ellos serán los que capturen las puertas. Discutiremos el resto después de inspeccionar nuestras fuerzas juntos. No me decepcione ni a su país, "+GetFullName(pchar)+".";
				link.l1 = "...Que así sea. Hasta luego, teniente.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_2":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 60 && sti(pchar.reputation.nobility) > 41)
			{
				notification("Reputation Check Passed", "None");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Gracias, Capitán. Esta es información valiosa, y tenías razón, no hay necesidad de demorar aquí. Mis hombres están todos aquí, somos fuertes, entrenados y listos. Todo terminará en media hora. Capitán, por favor prepárese para recibir personas, prisioneros y carga en su barco. No nos demoraremos aquí por mucho tiempo.";
				link.l1 = "Todo está listo, teniente. Solo te estábamos esperando. ¡Hasta luego!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(42))+")", "None");
				notification("Skill Check Failed (60)", SKILL_LEADERSHIP);
				dialog.text = "Gracias, Capitán. Esta es información valiosa. En ese caso, dirígete al muelle y prepara a tu equipo de abordaje. Asaltaremos el nido de los bandidos juntos e inmediatamente. Lo mejor de mis hombres y los tuyos liderarán la vanguardia - ellos serán los que capturen las puertas. Hablaremos del resto después de inspeccionar nuestras fuerzas juntos. No me falles a mí ni a tu país, "+GetFullName(pchar)+".";
				link.l1 = "...Así sea. Nos vemos más tarde, Teniente.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_3":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 70 && sti(pchar.reputation.nobility) > 41)
			{
				notification("Reputation Check Passed", "None");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Gracias, Capitán. Esta es información valiosa, y tenía razón, no hay necesidad de demorarse aquí. Mis hombres están todos aquí, somos fuertes, entrenados y listos. Todo terminará en media hora. Capitán, por favor prepárese para recibir gente, prisioneros y cargamento en su barco. No nos demoraremos mucho aquí.";
				link.l1 = "Todo está listo, teniente. Solo estábamos esperando por usted. ¡Nos vemos más tarde!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(42))+")", "None");
				notification("Skill Check Failed (70)", SKILL_LEADERSHIP);
				dialog.text = "Gracias, Capitán. Esta es información valiosa. En ese caso, dirígete al muelle y prepara tu equipo de abordaje. Atacaremos el nido de los bandidos juntos e inmediatamente. Lo mejor de mis hombres y los tuyos liderarán la vanguardia; ellos serán los que capturen las puertas. Discutiremos el resto después de inspeccionar nuestras fuerzas juntos. No me falles, ni a tu país, "+GetFullName(pchar)+".";
				link.l1 = "...Que así sea. Nos vemos más tarde, teniente.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_4":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 60 && sti(pchar.reputation.nobility) > 41)
			{
				notification("Reputation Check Passed", "None");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Gracias, Capitán. Esta es información valiosa, y tenías razón, no hay necesidad de demorarse aquí. Mis hombres están todos aquí, somos fuertes, entrenados y listos. Todo terminará en media hora. Capitán, por favor prepárese para recibir gente, prisioneros y carga en su barco. No nos quedaremos aquí mucho tiempo.";
				link.l1 = "Todo está listo, teniente. Solo te estábamos esperando. ¡Hasta luego!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(42))+")", "None");
				notification("Skill Check Failed (60)", SKILL_LEADERSHIP);
				dialog.text = "Gracias, Capitán. Esta es información valiosa. En ese caso, dirígete al muelle y prepara tu equipo de abordaje. Asaltaremos el nido de los bandidos juntos e inmediatamente. Lo mejor de mis hombres y los tuyos liderarán la vanguardia - ellos serán quienes capturen las puertas. Discutiremos el resto después de inspeccionar nuestras fuerzas juntos. No me defraudes a mí ni a tu país, "+GetFullName(pchar)+".";
				link.l1 = "...Que así sea. Nos vemos más tarde, teniente.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_5":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 90)
			{
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Gracias, Capitán. Esta es información valiosa, y tenía razón, no hay necesidad de demorarse aquí. Mis hombres están todos aquí, somos fuertes, entrenados y listos. Todo terminará en media hora. Capitán, por favor prepárese para recibir a la gente, prisioneros y carga en su barco. No nos demoraremos aquí por mucho tiempo.";
				link.l1 = "Todo está listo, teniente. Solo estábamos esperando por usted. ¡Nos vemos más tarde!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Skill Check Failed (90)", SKILL_LEADERSHIP);
				dialog.text = "Gracias, Capitán. Esta es información valiosa. En ese caso, dirígete al muelle y prepara tu equipo de abordaje. Asaltaremos el nido de bandidos juntos e inmediatamente. Los mejores de mis hombres y los tuyos liderarán la vanguardia - serán ellos quienes capturen las puertas. Discutiremos el resto después de inspeccionar nuestras fuerzas juntos. No me decepciones a mí ni a tu país, "+GetFullName(pchar)+".";
				link.l1 = "...Que así sea. Nos vemos más tarde, teniente.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_16": // французы атакуют сами
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			AddQuestRecord("IslaMona", "24");
			IslaMona_DefAttackLight();
		break;
		
		case "FraOfficer_17": // совместная атака
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -7);
			AddQuestRecord("IslaMona", "23");
			IslaMona_DefAttackCommon();
		break;
		
		case "FraOfficer_18":
			if (CheckCharacterItem(pchar, "patent_fra")) dialog.text = "¡Y yo, idiota, te admiraba! ¡A-agh! El orgullo de Francia, Capitán "+GetFullName(pchar)+"¡¡¡ No eres digno de tu patente!!!";
			else dialog.text = ""+GetFullName(pchar)+", escoria, traidor y maldito pirata! ¡Debería haber adivinado que este miserable antro es tu apestoso dominio! ¡Francia ni olvida ni perdona a hombres como tú!";
			link.l1 = "";
			link.l1.go = "FraOfficer_19";
		break;
		
		case "FraOfficer_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_75";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FraOfficer_20":
			dialog.text = "¿Estás listo, Capitán? ¡Tu escuadrón parece digno!";
			link.l1 = "Gracias, teniente. ¿Comenzamos?";
			link.l1.go = "FraOfficer_21";
		break;
		
		case "FraOfficer_21":
			dialog.text = "¡Sí, procedamos inmediatamente!";
			link.l1 = "...";
			link.l1.go = "FraOfficer_22";
		break;
		
		case "FraOfficer_22":
			DialogExit();
			IslaMona_DefAttackCommonRun();
		break;
		
		// обиженный пират
		case "Pirate":
			dialog.text = "¡Ja! "+GetFullName(pchar)+"¡Qué encuentro! ¡Eh, agárrenlo! ¡Este bastardo es dueño de todo aquí! ¡Esta es su isla!";
			link.l1 = "Qué día es este...";
			link.l1.go = "Pirate_1";
		break;
		
		case "Pirate_1":
			DialogExit();
			IslaMona_DefCheckJungleFight();
		break;
		
		// Алонсо
		case "Alonso":
			dialog.text = "Capitán, ¿cuáles son las órdenes? Hay una señal para prepararse y enviar el grupo de abordaje.";
			link.l1 = "La orden se mantiene. ¡Chicos, síganme, necesitamos limpiar nuestro hogar de invitados no deseados! ¡El premio es mío, todos los trofeos son vuestros!";
			link.l1.go = "Alonso_1";
		break;
		
		case "Alonso_1":
			dialog.text = "¡Hurra!";
			link.l1 = "¡A la batalla!";
			link.l1.go = "Alonso_2";
		break;
		
		case "Alonso_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=5; i++) 
			{
				sld = characterFromId("IM_our_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Common"))
			{
				pchar.quest.islamona_attack_common1.win_condition.l1 = "location";
				pchar.quest.islamona_attack_common1.win_condition.l1.location = "IslaMona_Jungle_01";
				pchar.quest.islamona_attack_common1.function = "IslaMona_DefAttackCommonPrepare";
			}
			else
			{
				LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload3_back", true);
				LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload1_back", true);
				pchar.quest.islamona_attack_force.win_condition.l1 = "location";
				pchar.quest.islamona_attack_force.win_condition.l1.location = "IslaMona_factoria";
				pchar.quest.islamona_attack_force.function = "IslaMona_DefAttackForce";
			}
		break;
		
		// испанский офицер
		case "SpaOfficer":
			dialog.text = "Saludos, señor. ¿Es usted el propietario de esta tierra? Permítame presentarme, Gran Francisco de Alba, antiguo capitán de la corbeta 'Perro Marino'.";
			link.l1 = "Sí, esta es mi tierra. Yo soy "+GetFullName(pchar)+", capitán del barco '"+pchar.ship.name+"¿Grandes? Nunca antes hemos tenido invitados tan distinguidos aquí.";
			link.l1.go = "SpaOfficer_1";
		break;
		
		case "SpaOfficer_1":
			dialog.text = "Oh, Monsieur "+GetFullName(pchar)+"¡Tu nombre es bien conocido! Verás, últimamente tu nombre ha estado apareciendo tan a menudo en los informes de la Casa de Contratación que estaba esperando seriamente órdenes para ocuparme de ti.";
			link.l1 = "¿Tratar conmigo?";
			link.l1.go = "SpaOfficer_2";
		break;
		
		case "SpaOfficer_2":
			dialog.text = "Creo que no tiene sentido fingir. Mi trabajo es buscar y destruir a los enemigos de España y del Rey Felipe en todos los mares del mundo.";
			link.l1 = "Es afortunado que tales órdenes aún no hayan llegado. Obviamente eres un oficial naval muy hábil.";
			link.l1.go = "SpaOfficer_3";
		break;
		
		case "SpaOfficer_3":
			dialog.text = "¡El hecho de que ahora soy un prisionero medio muerto en una pequeña isla repleta de piratas y mis compatriotas huyendo solo confirma tu conclusión, ¡ja-ja! Fue un asunto muy peligroso, pero las órdenes son órdenes. ¡Casi lo logramos! Es profundamente lamentable para mis hombres - los conocía a todos por su nombre, servimos juntos durante muchos años. Pero mi país tendrá que derramar más sangre de sus hijos para mantener su estatus imperial. Nuestra familia lo sabe mejor que la mayoría.";
			if (CheckAttribute(pchar, "questTemp.IslamonaSpaOfficer"))
			{
				link.l1 = "";
				link.l1.go = "SpaOfficer_4";
			}
			else
			{
				link.l1 = "Volvamos a asuntos más urgentes por ahora. ¿Qué voy a hacer contigo, Grand?";
				link.l1.go = "SpaOfficer_5";
			}
		break;
		
		case "SpaOfficer_4":
			dialog.text = "Por cierto, Monsieur de Mor, el 'Guerrero' - ese pequeño barco te era familiar, ¿verdad? Tu audaz operación en Portobello no pasó desapercibida. Atrevida, incluso suicida. Necesitabas dinero desesperadamente, ¿me equivoco? ¡Ja!";
			link.l1 = "Sabes mucho sobre mí, Grand. Pero pasemos a tu destino.";
			link.l1.go = "SpaOfficer_5";
		break;
		
		case "SpaOfficer_5":
			dialog.text = "¿Qué hay que pensar? Como en cualquier buena historia, tienes tres opciones: matarme, dejarme aquí o dejarme libre. Si me dejas libre, te doy la palabra de la familia de Alba de que nunca contaré a nadie sobre este lugar y tu implicación en mis desventuras. Además, seré tu deudor, y hasta que esa deuda sea saldada, nunca lucharé contra ti.";
			link.l1 = "No puedo arriesgarme, Grand.";
			link.l1.go = "SpaOfficer_6";
			link.l2 = "Pasarás algún tiempo aquí. Vivirás y trabajarás en igualdad de condiciones con tus compatriotas.";
			link.l2.go = "SpaOfficer_7";
			link.l3 = "Bienvenido a bordo de mi barco, Grand. Te desembarcaré en el faro de Santiago cuando llegue el momento. Espero que cumplas tu palabra.";
			link.l3.go = "SpaOfficer_8";
		break;
		
		case "SpaOfficer_6":
			dialog.text = "Entiendo, señor. Bueno, en cualquier caso, ya estoy muerto en esa batalla junto con mis hombres. Es un buen final.";
			link.l1 = "";
			link.l1.go = "SpaOfficer_6_1";
		break;
		
		case "SpaOfficer_6_1":
			DialogExit();
			DoQuestFunctionDelay("IslaMona_KillSpanish", 1.0);
		break;
		
		case "SpaOfficer_7":
			dialog.text = "Lo admito, no me gusta ser indeciso. Pero no hay deshonra en ser prisionero, así que acepto tu regalo de vida y viviré en paz con estas gente amable y aparentemente muy feliz. Sin embargo, si alguna vez dejo este lugar, no te deberé nada.";
			link.l1 = "";
			link.l1.go = "SpaOfficer_7_1";
		break;
		
		case "SpaOfficer_7_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			AddQuestRecord("IslaMona", "27");
			IslaMona_FinalPrepare();
		break;
		
		case "SpaOfficer_8":
			dialog.text = "¡Te doy mi palabra y la palabra de la familia de Alba! ¡Nos vemos en el barco!";
			link.l1 = "";
			link.l1.go = "SpaOfficer_8_1";
		break;
		
		case "SpaOfficer_8_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("IslaMona", "28");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
			pchar.quest.islamona_final_mayak.win_condition.l1 = "location";
			pchar.quest.islamona_final_mayak.win_condition.l1.location = "Mayak9";
			pchar.quest.islamona_final_mayak.function = "IslaMona_FinalMayakSpanish";
			pchar.questTemp.IslaMona.Mayak = "true";
			IslaMona_FinalPrepare();
		break;
		
		case "SpaOfficer_9":
			dialog.text = "¡Capitán "+GetFullName(pchar)+"! Me has salvado la vida y me has devuelto a los míos. Comprendo lo difícil que fue correr semejante riesgo; yo nunca me habría atrevido a hacer algo así. Estoy en deuda con usted, señor. Le doy mi palabra de que nunca contaré a nadie las circunstancias de aquella nefasta batalla. Cuando regreses al Viejo Mundo, asegúrate de encontrarme; siempre serás bienvenido en nuestra finca familiar de Madrid. Por ahora, toma esto...";
			link.l1 = "¿Un pedazo de un mapa?";
			link.l1.go = "SpaOfficer_10";
		break;
		
		case "SpaOfficer_10":
			AddMapPart();
			dialog.text = "Eso es todo lo que tenía de valor conmigo. No tengo duda de que encontrarás la otra pieza fácilmente. ¡Adiós! Y buena suerte, amigo mío.";
			link.l1 = "Adiós, Grand. Recuerda tu palabra, ¡y buena suerte para ti!";
			link.l1.go = "SpaOfficer_11";
		break;
		
		case "SpaOfficer_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.IslaMona.Mayak = "done";
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			AddQuestRecord("IslaMona", "29");
			CloseQuestHeader("IslaMona");
		break;
		
		// Диалоги обитателей Исламоны
		// мужское население
		case "island_man":
			dialog.text = LinkRandPhrase("¡Saludos! ¿Cómo estáis, Capitán? Las cosas están yendo bien para nosotros.","¡Trabajar para la comunidad es la mayor alegría!","Tu isla es maravillosa, Capitán, y haremos todo por su prosperidad.");
			link.l1 = LinkRandPhrase("Me alegra oír eso.","Me alegra saber que todo está bien.","Admiro tu entusiasmo, amigo.");
			link.l1.go = "island_man_1";
			if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage"))
			{
				switch(sti(pchar.questTemp.IslaMona.TownStage))
				{
					case 0:
						dialog.text = RandPhraseSimple(RandPhraseSimple("No lo tome como una insolencia, señor, pero vivir aquí es imposible.","Todo es mejor que estar sentado en las celdas de la Inquisición..."),RandPhraseSimple("Gracias por salvarnos, Capitán.","¿Estos... piratas son tus amigos?"));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 1:
						dialog.text = RandPhraseSimple(RandPhraseSimple("¡No está mal aquí! Solo un poco aburrido.","Capitán, es un placer verte. ¡Pasa a visitarnos en algún momento!"),RandPhraseSimple("Alguien encontró calaveras en la playa y las trajo a la reunión matutina. ¿Siempre es así aquí?","Te contaré un secreto, Señor Himenes obviamente se beneficia del aire fresco y la seguridad de este lugar."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 2:
						dialog.text = RandPhraseSimple(RandPhraseSimple("¡No está mal aquí! Solo un poco aburrido.","Capitán, es un placer verle. ¡Pase por aquí en algún momento!"),RandPhraseSimple("Alguien encontró calaveras en la playa y las trajo a la reunión matutina. ¿Siempre es así aquí?","Te diré un secreto, el Señor Himenes obviamente se beneficia del aire fresco y la seguridad de este lugar."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 3:
						dialog.text = RandPhraseSimple(RandPhraseSimple("¡Dios te bendiga, Capitán!","Una vez a la semana, hacemos representaciones en la playa y en la taberna. Pasa por aquí alguna vez."),RandPhraseSimple("Tus marineros nos traen constantemente todo tipo de baratijas a cambio de comida fresca. Gracias por fomentar esto.","Es asombroso cómo este lugar aún no ha sido descubierto. Espero que siga así."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
				}
			}
		break;
		
		case "island_man_1":
			DialogExit();
			npchar.dialog.currentnode = "island_man";
		break;
		
		case "island_man_2":
			dialog.text = "Gracias, señor. Gracias a usted, hemos visto el verdadero Nuevo Mundo. ¡Dios le bendiga!";
			link.l1 = "";
			link.l1.go = "island_man_3";
			locCameraFromToPos(1.64, 1.58, -5.11, false, 2.66, 0.20, -5.74);
		break;
		
		case "island_man_3":
			DialogExit();
			npchar.dialog.currentnode = "island_man";
			sld = characterFromId("Himenes_companion_12");
			sld.dialog.currentnode = "island_woman_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		// женское население
		case "island_woman":
			dialog.text = LinkRandPhrase("Seguridad y paz, ¡eso es lo que me gusta aquí!","¡Un paraíso maravilloso! Bueno, casi...","Estamos felices de encontrar un nuevo hogar aquí, después de tantas penurias.");
			link.l1 = LinkRandPhrase("Me alegro por ti y por tu comunidad.","Sí, a mí también me gusta esta pequeña isla.","Es bueno saber que estás satisfecho.");
			link.l1.go = "island_woman_1";
			if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage"))
			{
				switch(sti(pchar.questTemp.IslaMona.TownStage))
				{
					case 0:
						dialog.text = LinkRandPhrase("Oh... Hola.","Señor, ¿quiénes son esos... hombres rudos con armas?","Gracias por salvarnos, Capitán.");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 1:
						dialog.text = LinkRandPhrase("Nuestros hombres hicieron un gran trabajo - las casas son excelentes. ¡Pero nosotros también trabajamos duro!","Señor Capitán, no se preocupe:   las mujeres de nuestro pequeño clan no temen las dificultades ni las incomodidades temporales.","¡Qué aire aquí! ¡Y el mar! ¡Te sientes más cerca de Dios!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 2:
						dialog.text = LinkRandPhrase("Nuestros hombres hicieron un gran trabajo - las casas son excelentes. ¡Pero nosotros también trabajamos duro!","Señor Capitán, no se preocupe: las mujeres de nuestro pequeño clan no temen las dificultades ni las incomodidades temporales.","¡Qué aire hay aquí! ¡Y el mar! ¡Te sientes más cerca de Dios!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 3:
						dialog.text = LinkRandPhrase("Vuelva más a menudo, Señor Capitán. Siempre me alegra verte.","¡El señor Rodgar es un narrador increíble! ¡Puedes escucharlo hablar por siempre!","Hehe. Dicen que alguien de nuestro grupo ya está esperando un nuevo miembro en la familia. ¡La vida continúa incluso en Isla Mona!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
				}
			}
		break;
		
		case "island_woman_1":
			DialogExit();
			npchar.dialog.currentnode = "island_woman";
		break;
		
		case "island_woman_2":
			dialog.text = "Usted... ¡Muchas gracias, señor! Pase por aquí más a menudo...";
			link.l1 = "";
			link.l1.go = "island_woman_3";
			locCameraFromToPos(-1.86, 1.18, 4.51, true, -1.49, 0.20, 6.13);
		break;
		
		case "island_woman_3":
			DialogExit();
			npchar.dialog.currentnode = "island_woman";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		// пираты Родгара
		case "fort_pirate":
			if(npchar.location == "islamona_factoria")
			{
				dialog.text = dialog.text = RandPhraseSimple(RandPhraseSimple("¡Todo está bien, capitán!","Esclavos bajo control, no te preocupes."),RandPhraseSimple("No tienes que preocuparte, el motín está excluido.","¡Gracias por el ron! ¡Nos pondremos a trabajar!"));
			}
			else
			{
				dialog.text = dialog.text = RandPhraseSimple(RandPhraseSimple("¿Españoles? No esperábamos esto de vosotros.","¡Ahora tenemos que caminar hasta la playa solo para dormir en paz!"),RandPhraseSimple("¿Por qué decidiste todo esto, eh, Capitán?","El jefe confiaba en ti entonces, y no se equivocó. Creeremos en ti de nuevo."));
			}
			link.l1 = "...";
			link.l1.go = "fort_pirate_1";
		break;
		
		case "fort_pirate_1":
			DialogExit();
			npchar.dialog.currentnode = "fort_pirate";
		break;
		
		// посетители таверны
		case "citizen_tavern":
			dialog.text = LinkRandPhrase("Después de un trabajo agotador, no es pecado tomarse un trago o dos...","Casi he terminado y me dirijo a casa, mi esposa debe estar esperando...","¡Ah, es agradable relajarse en nuestra taberna después del trabajo! ¡Todos le estamos agradecidos, capitán!");
			link.l1 = LinkRandPhrase("¡Disfruta tu bebida, compadre, ja-ja!","Relájate, amigo, pero no te pases, o la esposa te regañará, ¡ja-ja!","Tranquilo, amigo, ¡la vida no es solo trabajo!");
			link.l1.go = "citizen_tavern_1";
		break;
		
		case "citizen_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "citizen_tavern";
		break;
		
		case "sailor_tavern":
			if (GetCharacterIndex("Mirabella") != -1) sTemp = "¿Quién es esa mulata tan guapa que vive aquí?";
				else sTemp = "¡Capitán, bonito lugar el que tiene aquí!";
			dialog.text = RandPhraseSimple(RandPhraseSimple("¡Capitán, bonito lugar tienes aquí!","Imagina si de repente nos quedáramos sin ron. Seguro que conseguirías más, ¿verdad?"),RandPhraseSimple("He soñado con unas vacaciones así durante mucho tiempo. Aunque me encantaría un burdel... solo un pensamiento salvaje, Capitán.",sTemp));
			link.l1 = "...";
			link.l1.go = "sailor_tavern_1";
		break;
		
		case "sailor_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor_tavern";
		break;
		
		case "sailor_town":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Gracias por las vacaciones, Capitán.","Bonito lugar has creado aquí, tienes un don para mantener las cosas en orden, Capitán."),RandPhraseSimple("Comida fresca, licor, suelo firme bajo los pies. Es un sueño.","Me gustaría quedarme aquí un poco más."));
			link.l1 = "...";
			link.l1.go = "sailor_town_1";
		break;
		
		case "sailor_town_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor_town";
		break;
		
		// рабы
		case "slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Estoy tan cansado - apenas puedo mantenerme en pie.","¡No tengo más fuerzas para vivir así!"),RandPhraseSimple("Este trabajo es demasiado duro para mí.","¡Los capataces no dejaron ni una célula viva en mi piel!"));				
			link.l1 = "";
			link.l1.go = "slave_1";
		break;
		
		case "slave_1":
			DialogExit();
			npchar.dialog.currentnode = "slave";
		break;
		
		// энкауниеры в домах
		case "HouseMan":
			dialog.text = LinkRandPhrase("¿Puedo ayudarle en algo, capitán?","Entra, prueba algo de paella. ¡Solo, por el amor de Dios, no preguntes de qué está hecha!","Bienvenido, capitán. ¿Qué le parece este lugar?");
			link.l1 = "...";
			link.l1.go = "HouseMan_1";
		break;
		
		case "HouseMan_1":
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			npchar.dialog.currentnode = "HouseMan";
		break;
		
		case "HouseWoman":
			dialog.text = LinkRandPhrase("¡Señor, bienvenido!","Hola, capitán. ¿Te quedarás?","¿Estás aquí por mí? Por favor, entra, sólo ignora el desorden, señor.");
			link.l1 = "...";
			link.l1.go = "HouseWoman_1";
		break;
		case "HouseWoman_1":
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			npchar.dialog.currentnode = "HouseWoman";
		break;
	}
}