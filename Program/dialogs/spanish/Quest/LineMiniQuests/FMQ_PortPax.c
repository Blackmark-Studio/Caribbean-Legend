// Addon-2016 Jason, французские миниквесты (ФМК) Порт-о-Пренс
void ProcessDialogEvent()
{
	ref sld, NPChar;
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
		dialog.text = "Un error evidente. Informa a los desarrolladores sobre ello.";
		link.l1 = "Oh, lo haré.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "officer":
		PlaySound("Voice\Spanish\z_arest_02.wav");
		dialog.text = "¿Qué diablos está pasando aquí, caballeros? Escuché una pelea.";
		link.l1 = "Hola oficial, escuché a una mujer gritar y...";
		link.l1.go = "officer_1";
		break;

	case "officer_1":
		DialogExit();
		sld = CharacterFromID("FMQP_noble");
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "officer_2":
		dialog.text = "";
		link.l1 = "" + GetFullName(pchar) + ". Capitán " + GetFullName(pchar) + ".";
		link.l1.go = "officer_3";
		break;

	case "officer_3":
		dialog.text = "Eres libre de irte por ahora, capitán. Puedo ver lo que sucedió aquí, te llamaremos en caso de tener preguntas.";
		link.l1 = "Muy bien...";
		link.l1.go = "officer_4";
		break;

	case "officer_4":
		DialogExit();
		sld = CharacterFromID("FMQP_noble");
		sld.Dialog.currentnode = "noble_3";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "officer_5":
		PlaySound("Voice\Spanish\z_arest_02.wav");
		dialog.text = "¿Qué diablos está pasando aquí, caballeros? Escuché peleas.";
		link.l1 = "Gracias, oficial, escuché a una mujer gritando por ayuda y vi a este caballero siendo atacado por dos sinvergüenzas. Traté de salvar al pobre hombre pero, ay, llegué demasiado tarde. ¡Los malditos lo mataron!";
		link.l1.go = "officer_6";
		break;

	case "officer_6":
		dialog.text = "¡Malditos sean mis ojos...! ¡Es un español! ¿Por qué estaría él aquí? Hm. ¿Y quién eres tú entonces, señor?";
		link.l1 = "" + GetFullName(pchar) + ". Capitán " + GetFullName(pchar) + ".";
		link.l1.go = "officer_7";
		break;

	case "officer_7":
		dialog.text = "Capitán, eres libre de irte por ahora. Tus palabras coinciden con las del testigo. Te llamaremos si es necesario.";
		link.l1 = "Muy bien...";
		link.l1.go = "officer_8";
		break;

	case "officer_8":
		DialogExit();
		DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
		break;

	case "noble":
		dialog.text = "¡Permítame explicarle todo, señor! Me llamo Don Domingo Ortiz Albalate de Santo Domingo. Vine a Port-au-Prince por una invitación de una joven señorita y me detuve en esta taberna esperando la cita acordada. Mientras estaba en mis propios asuntos, fui atacado por estos dos malditos ladrones. Estaría cenando con los ángeles ahora mismo si no fuera por este Buen Samaritano que pasó por aquí.";
		link.l1 = "¿Don Domingo Ortiz Albalate? ¿Eres español?";
		link.l1.go = "noble_1";
		break;

	case "noble_1":
		dialog.text = "¡Tan español como el mismo Rey Felipe, ja! También me gustaría señalar que mis papeles están en buen orden. ¡Soy noble de España, no un sucio pirata!";
		link.l1 = "¡Don Domingo, nuestras más sinceras disculpas por este desafortunado incidente! Por favor, acompáñenos para algunas preguntas y una botella de vino en la guarnición. Nos encargaremos de todo. En cuanto a usted...";
		link.l1.go = "noble_2";
		break;

	case "noble_2":
		DialogExit();
		sld = CharacterFromID("FMQP_off");
		sld.Dialog.currentnode = "officer_2";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "noble_3":
		PlaySound("Voice\Spanish\LE\Domingo\Domingo_01.wav");
		dialog.text = "¡Señor Capitán! ¡Señor Capitán! ¡Juro por Santiago y la Santísima Virgen que usted es un hombre noble, y un verdadero hijo de Castilla siempre recompensa tal nobleza! Me gustaría verlo recompensado más tarde cuando termine mis asuntos aquí. Por favor, honre mi humilde hogar en Santo Domingo con una visita. ¡Está cerca de las puertas de la ciudad. Haré un banquete para usted, mi buen caballero Carlos! ¡Recuerde mi nombre, es Don Domingo Ortiz Albalate!";
		link.l1 = "...";
		link.l1.go = "noble_4";
		break;

	case "noble_4":
		DialogExit();
		AddMapQuestMarkCity("santodomingo", true);
		DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "FMQP_AfterFightInTown");
		break;

	case "noble_5":
		dialog.text = "Capitán " + GetFullName(pchar) + "¿¡Oh Madre de Dios! ¡Qué desastre! ¡Esto es una masacre! ¿Qué ocurrió aquí, buen amigo? ¿Quiénes son estos hombres?";
		link.l1 = "Me alegra verte, Don Domingo. Estos son... Vine aquí para hacerte una visita. ¿Ves a ese tipo de allí? Ese es Ugo, tu sirviente y él...";
		link.l1.go = "noble_6";
		break;

	case "noble_6":
		dialog.text = "¿Ugo?! ¡Oh, no, fuiste engañado, capitán!";
		link.l1 = "Lo entiendo, parece que me pasa mucho. Tres canallas irrumpieron en tu casa, asesinaron a tu leal hombre Ugo - encontré su cadáver arriba y luego prepararon una emboscada para ti. Mi llegada no estaba en sus planes. No sobrevivieron a nuestro encuentro.";
		link.l1.go = "noble_7";
		break;

	case "noble_7":
		dialog.text = "¡Santa María, ora pro nobis! ¡Manejas tu espada como los maestros de esgrima de Toledo! ¡Es bueno que estés de mi lado! ¡Oh, mi pobre Ugo! Me crió desde que era un niño y ahora... ¡ser asesinado por esos malditos canallas!";
		link.l1 = "Don Domingo, parece que no estás fuera de peligro. Tu hombre Ugo sabía algo, lee esta nota. La encontré sobre una mesa.";
		link.l1.go = "noble_8";
		break;

	case "noble_8":
		ChangeItemDescribe("letter_parol", "itmdescr_letter_parol");
		RemoveItems(pchar, "letter_parol", 1);
		dialog.text = "Dámelo... (leyendo) Eso no puede ser... ¡oh, no! ¡Esto es increíble! Tío Luis... Pero...";
		link.l1 = "¿Alguna pista sobre quién hizo esto?";
		link.l1.go = "noble_9";
		break;

	case "noble_9":
		dialog.text = "Solo sospechas... ¡horribles sospechas mi amigo! ¿Cómo pudo el hermano de mi madre hacer tal cosa?";
		link.l1 = "¿Te importaría ponerme al tanto? Lo siento, Don Domingo, pero en mi experiencia, los parientes son a menudo los peores enemigos que un hombre puede tener...";
		link.l1.go = "noble_10";
		break;

	case "noble_10":
		dialog.text = "¡Sí, tienes razón, Carlos! ¡Te lo contaré todo! ¡Ya me has salvado dos veces y parece que eres el único hombre en quien puedo confiar ahora mismo! Pero salgamos de este lugar horrible, me da náuseas. Debo notificar al alcalde sobre este lío, ellos se encargarán del pobre Ugo. ¿Qué te parece si tomamos un poco de vino en la taberna para calmar los nervios?";
		link.l1 = "¡Tus nervios ciertamente lo necesitan más que los míos, guía el camino, señor!";
		link.l1.go = "noble_11";
		break;

	case "noble_11":
		DialogExit();
		chrDisableReloadToLocation = false;
		DoQuestReloadToLocation("Santodomingo_tavern", "sit", "sit_base2", "FMQP_InSantoDomingoTavern");
		break;

	case "noble_12":
		LAi_SetSitType(pchar);
		dialog.text = "Entonces, mi amigo, permíteme contarte una... versión abreviada de la historia de mi familia. Mi madre, Doña Isabella Ortiz, se casó con mi padre, el Marqués Ricardo Albalate, y tomó su apellido según la costumbre. Su hermano, Luis Ortiz, era comandante de la guarnición en las colonias, pero después del matrimonio de mi madre, mi padre lo nombró administrador de una plantación de azúcar no lejos de Portobello.\nEra una plantación enorme y rica, muy rentable en verdad. Tras la trágica muerte de mis padres en el mar hace unos años, yo, como su único hijo, heredé todo, incluida la plantación. Mi tío ha mantenido su posición y yo estaba bastante contento con la renta que me pagaba. Siempre era puntual con sus pagos.";
		link.l1 = "Entonces, ¿crees que tu tío...?";
		link.l1.go = "noble_13";
		break;

	case "noble_13":
		dialog.text = "Sí. Actualmente, él no es más que un arrendatario. Yo soy el dueño de la plantación, no él. ¡Pero! Si algo me sucede, se convertirá en su propiedad.";
		link.l1 = "Sabes, Domingo, conocí a hombres que asesinarían a todos sus parientes a sangre fría por un premio mucho menos jugoso que ese.";
		link.l1.go = "noble_14";
		break;

	case "noble_14":
		dialog.text = "Tú claramente necesitas mejor compañía, Carlos. Mi querido Ugo mencionó los papeles de mi tío en su última nota... Esto es una pista directa. ¡Oh, no quiero creer esto! Pero... mi prima, Margarita Ortiz, que vive en España, se comprometió hace poco. ¿Podría ser la causa mi buen capitán?";
		link.l1 = "Tu querido tío podría de repente necesitar algo de dinero...";
		link.l1.go = "noble_15";
		break;

	case "noble_15":
		dialog.text = "¿Dinero?! Pero, por supuesto... ¡pero no olvides el título de marqués! ¡Eso haría a mi prima un partido adecuado para su futuro esposo! ¡Jesucristo! ¡Qué estúpido fui!";
		link.l1 = "Ese título de nobleza tiene más valor que la plantación de azúcar.";
		link.l1.go = "noble_16";
		break;

	case "noble_16":
		dialog.text = "¡Espera, mi amigo! ¡Acabo de recordar que este no fue el primer intento contra mi vida! ¡Tuve un encuentro con un mendigo en la calle hace unas semanas! El borracho canalla me ofendió de una manera que no pude ignorar. Resultó ser un maldito buen espadachín, desenvainó el acero e incluso logró herirme con un florete antes de que lo matara.";
		link.l1 = "¿Y cómo demonios terminaste en una taberna en Puerto Príncipe? ¿Mencionaste a alguna joven señorita?";
		link.l1.go = "noble_17";
		break;

	case "noble_17":
		dialog.text = "(poniéndose rojo) Señor... Sí capitán, había una joven y bonita señorita en la escena... ahora veo que ella solo era el cebo para la trampa. ¡Malditos, malditos están por todas partes, no se puede confiar en nadie! Pobre Ugo... ahora está muerto.";
		link.l1 = "Deberías hacer algo al respecto, Domingo. ¿Qué tal huir a España?";
		link.l1.go = "noble_18";
		break;

	case "noble_18":
		dialog.text = "¿A España? ¿Y dejar mi plantación a ese bribón? ¡Capitán, soy el Marqués Domingo Ortiz Albalate!";
		link.l1 = "Pero...";
		link.l1.go = "noble_19";
		break;

	case "noble_19":
		dialog.text = "Mi amigo Carlos, ¿puedo pedirte ayuda? Con Ugo muerto, no tengo a nadie de confianza a mi lado. ¡Ya me has salvado dos veces! ¡Dos veces! Te debo mucho, estoy en deuda contigo para siempre y aun así me atrevo a pedirte otro favor. ¡Juro por la Madre Bendita, que haré que valga la pena!";
		link.l1 = "Muy bien, eres un buen hombre para ser español. ¿Qué puedo hacer por ti, Domingo?";
		link.l1.go = "noble_20";
		break;

	case "noble_20":
		dialog.text = "¡Vamos a mi plantación en Portabello! Sé que mi tío está en Cartagena en este momento. Ugo mencionó algunos papeles, ¡así que revisemos los libros y documentos de Don Luis Ortiz! Podríamos encontrar algo que nos ayude a sacar su vil conspiración a la luz. Está bastante lejos de Portobello, pero te pagaré en su totalidad por el viaje.";
		link.l1 = "Sería absurdo rechazarle en este punto, Don Domingo. Estoy demasiado involucrado para echarme atrás ahora.";
		link.l1.go = "noble_21";
		break;

	case "noble_21":
		AddMoneyToCharacter(pchar, 20000);
		dialog.text = "¡Gracias a Dios, sabía que me ayudarías, amigo! Aquí, toma estos veinte mil pesos como pago por el viaje a . ¿Cuándo zarpamos? ¡Debemos apresurarnos antes de que mi tío regrese de Cartagena!";
		link.l1 = "Entonces no perdamos tiempo.";
		if (CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 20)
			link.l1.go = "noble_22";
		else
			link.l1.go = "noble_22x";
		break;

	case "noble_22x":
		GiveNationLicence(HOLLAND, 20);
		dialog.text = "Aquí tienes una licencia de la Compañía Holandesa de las Indias Occidentales. Tiene una vigencia de veinte días, solo pongamos tu nombre en ella. Hecho. Esto debería ayudarnos a evitar cualquier problema con la Guarda Costera.";
		link.l1 = "¡Excelente!";
		link.l1.go = "noble_22";
		break;

	case "noble_22":
		dialog.text = "¿Ahora se me permite subir a bordo de tu barco, mi amigo?";
		link.l1 = "Considérate un huésped de honor. Tan pronto como tengamos el viento adecuado, zarpamos.";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("FMQP_OnBoard");
		AddMapQuestMarkCity("portobello", true);
		break;

	case "noble_23":
		dialog.text = "Así que Capitán Carlos, aquí estamos. Ahora debemos encontrar la casa de mi tío y ver qué hay dentro.";
		link.l1 = "Don Domingo, ¿debemos esperar algún problema con la guardia?";
		link.l1.go = "noble_24";
		break;

	case "noble_24":
		dialog.text = "No. Aunque... hm. Existe la posibilidad de que Luis los haya vuelto contra mí. En cualquier caso, la discreción es siempre la mejor parte del valor. Vamos a encontrar la casa que necesitamos.";
		link.l1 = "¿No lo sabes ya? Es tu plantación.";
		link.l1.go = "noble_25";
		break;

	case "noble_25":
		dialog.text = "Hum.. Para ser completamente honesto, la última vez que estuve aquí, sólo tenía ocho años. ¡Sin embargo, tengo la intención de arreglar esto lo antes posible!";
		link.l1 = "Ya veo. Entonces, empecemos a buscar. La casa de tu tío debe ser la más grande aquí.";
		link.l1.go = "noble_26";
		break;

	case "noble_26":
		DialogExit();
		chrDisableReloadToLocation = false;
		LAi_SetActorType(npchar);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		AddQuestRecord("FMQ_Portpax", "7");
		break;

	case "noble_27":
		dialog.text = "¿Qué tienes aquí, mi amigo?";
		link.l1 = "Échale un vistazo, Don Domingo. Parece que son registros contables. Esto podría ser interesante.";
		link.l1.go = "noble_28";
		break;

	case "noble_28":
		ChangeItemDescribe("Almanac", "itmdescr_Almanac");
		RemoveItems(pchar, "Almanac", 1);
		dialog.text = "(leyendo) Mmm... Sí. Mira esto... ¡Ay caramba! ¡Cien mil pesos! ¡Y otros ciento cincuenta mil! Y aquí... (pasando páginas) ¡Tío Luis!";
		link.l1 = "¿Algo de interés?";
		link.l1.go = "noble_29";
		break;

	case "noble_29":
		dialog.text = "¡Algo de interés! ¡Mi preciado tío tenía un ingreso cinco veces mayor de lo que me decía! ¡Ladrón! ¡Malversador!";
		link.l1 = "No puedo decir que estoy sorprendido. No puedes confiar completamente en nadie sin comprobar el verdadero estado del negocio de vez en cuando. Eso es simplemente sentido común.";
		link.l1.go = "noble_30";
		break;

	case "noble_30":
		dialog.text = "Sentido común para los hombres comunes, quizás. ¡Mi crianza me ha cegado a tal engaño en caballeros que pensaba honorables! ¡Tienes razón como siempre, Carlos! ¡Mi propio tío me está robando! ¡Mierda! Esto es culpa mía, pero lo arreglaré. ¡Soy dueño de esta plantación y mi tío ha sido relevado de su deber desde hoy! ¡Él no es nadie! ¡Lo veré pasar por la quilla!";
		link.l1 = "Don Domingo... ¿No cree usted que su tío podría estar en desacuerdo con tal decisión?";
		link.l1.go = "noble_31";
		break;

	case "noble_31":
		dialog.text = "¡Me importa un comino si está de acuerdo o no! ¡Soy el marqués Domingo Ortiz Albalate y Luis Ortiz no es más que un arrendatario, y un antiguo arrendatario en eso! Y él...";
		link.l1 = "Tranquilízate, señor. Eres un rostro desconocido aquí y yo soy un francés navegando bajo licencia holandesa con un... pasado turbio con las patrullas antipiratería españolas. En cuanto a tu tío, prácticamente posee esta ciudad. Piensa en los guardias y el gobernador. ¿Crees que elegirán tu lado?";
		link.l1.go = "noble_32";
		break;

	case "noble_32":
		dialog.text = "Golpeas el punto con un estoque... Tal vez... No. ¡Los soldados españoles nunca se atreverán a levantar la mano contra un noble! ¡Mi tío puede desafiarme si se atreve!";
		link.l1 = "Aún así, sugiero tomar otro camino. ¿Qué tal la corte de justicia?";
		link.l1.go = "noble_33";
		break;

	case "noble_33":
		dialog.text = "¡Ja! Tienes razón, Carlos. Vamos a hablar con las autoridades competentes. Mi tío cometió un error al anotar detalles exactos en sus notas sobre sus tratos con contrabandistas. Compró esclavos de ellos a muy bajo precio. Estos libros nos harán un gran servicio, dudo que el bastardo pueda hacerme daño de alguna manera mientras esté sentado en las mazmorras. ¡Vamos, amigo mío! ¡A !";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("FMQP_PrepareUncle");
		break;

	case "noble_34":
		//PlaySound("Voice\Spanish\LE\Domingo\Domingo_04.wav");
		dialog.text = "¡Esto no es más que una vil y descarada mentira! ¿Cómo se atreve a mancillar el buen nombre de mis padres con su lengua indigna? ¡Maldito sea él, haré que pague por esto! ¡Desenvaina tu espada, asesino!";
		link.l1 = "";
		link.l1.go = "noble_35";
		break;

	case "noble_35":
		DialogExit();
		sld = CharacterFromID("FMQP_Uncle");
		sld.Dialog.currentnode = "uncle_3";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

	case "noble_36":
		PlaySound("Voice\Spanish\LE\Domingo\Domingo_05.wav");
		dialog.text = "Tío Luis está en el lugar adecuado reservado para su alma: en el infierno... ¡Carlos, fuiste enviado a mí por mi ángel guardián! Me alegra que no hayas confiado en la palabra de este sinvergüenza. Para ser honesto, temía que simplemente me dejaras aquí solo para luchar contra este canalla.\nSí señor, yo mismo no soy perfecto, pero esto... ¡esta sucia mentira sobre que contraté piratas para asesinar a mis propios padres! Acusarme de esto... ¡esto! ¡Bah! Un destino bien merecido.";
		link.l1 = "Alegra me que lo hayamos logrado, Don Domingo. ¿Y ahora qué? Espero que no hayamos infringido la ley española.";
		link.l1.go = "noble_37";
		break;

	case "noble_37":
		dialog.text = "¿Con la ley? ¡Ja, ja! No, Carlos, mostraré este excelente libro de contabilidad con todas las operaciones de contrabando de mi tío. No olvides los varios intentos de acabar con mi vida, tenemos un gran número de testigos después de su último intento justo ahora. No te preocupes por ello, mi buen amigo. ¡Esta es mi ciudad, es hora de mostrárselo a todos!";
		link.l1 = "Por favor, muévase con cautela, señor. Que piensen mejor de usted de lo que pensaban de su difunto tío.";
		link.l1.go = "noble_38";
		break;

	case "noble_38":
		dialog.text = "Eso es el plan, capitán. Pero no mostraré piedad a nadie que se atreva a oponerse a mí. ¡Permíteme expresar mi sincera gratitud hacia ti, Carlos! Por favor, ve a la taberna, descansa, toma una copa o dos. Me encantaría unirme a ti, pero tenías razón. Es hora de ser más sabio y tomar control de la plantación yo mismo. ¡Ven a verme aquí mañana, capitán!";
		link.l1 = "Muy bien, Don Domingo. Nos vemos mañana.";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("FMQP_PlantatonPause");
		break;

	case "noble_39":
		DelLandQuestMark(npchar);
		PlaySound("VOICE\Spanish\LE\Domingo\Domingo_05.wav");
		dialog.text = "¡Ah, aquí estás, mi buen amigo!";
		link.l1 = "¿Cómo estáis, don Domingo? ¿Cómo va vuestra plantación?";
		link.l1.go = "noble_40";
		break;

	case "noble_40":
		dialog.text = "La plantación es estupenda, no puedo decir lo mismo del dinero - resulta que mi querido tío había estado transfiriendo todo el dinero al banco de Cartagena. Llevará mucho tiempo con abogados recuperar mi oro. Pero está bien, puedo hacerlo. No te pongas triste, capitán, cumpliré mis promesas de recompensarte por tu nobleza, honestidad y amistad.";
		link.l1 = "Jamás pensé en una recompensa cuando estaba luchando a tu lado, señor...";
		link.l1.go = "noble_41";
		break;

	case "noble_41":
		dialog.text = "¡Sé eso, capitán, y esto dice mucho de tu carácter! Cualquier buena acción debe ser recompensada. Así que, aunque no tengo dinero en este momento, daré órdenes para cargar tu barco con mercancías de mi plantación. Me refiero al café, un gran lote de él. Estoy seguro de que podrás venderlo con gran ganancia.";
		link.l1 = "¡Oh! Esto es agradable..";
		link.l1.go = "noble_42";
		break;

	case "noble_42":
		dialog.text = "Además, tengo algunos artículos de poco valor para mí, pero de gran valor para cualquier marinero como tú. Un buen catalejo y tres amuletos. Por favor, acepta estos, ahora son todos tuyos.";
		link.l1 = "¡Gratitud!";
		link.l1.go = "noble_43";
		break;

	case "noble_43":
		Log_Info("Has recibido un buen catalejo");
		Log_Info("Has recibido tres amuletos");
		PlaySound("interface\important_item.wav");
		dialog.text = "Finalmente, te obsequio con mi estoque como muestra de mi inmensa gratitud hacia ti. Ella me sirvió bien, ahora deja que te sirva aún mejor. Mírala y recuerda a tu buen amigo español - marqués Domingo Albalate!";
		link.l1 = "¡Muchas gracias, señor! No esperaba...";
		link.l1.go = "noble_44";
		break;

	case "noble_44":
		Log_Info("Has recibido la Espada Pequeña");
		PlaySound("interface\important_item.wav");
		RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
		dialog.text = "Y ahora, ay, tengo que despedirme. Debo ir a  para ver al gobernador y luego a Cartagena... En resumen, mi existencia despreocupada ha terminado, es hora de vivir como un hombre adulto.";
		link.l1 = "Bueno, ahora eres mucho más listo...";
		link.l1.go = "noble_45";
		break;

	case "noble_45":
		dialog.text = "Es cierto. ¡Fue un placer, mi amigo! Ven a visitarme alguna vez. ¡Buen viento en el mar!";
		link.l1 = "Lo mismo para usted en su negocio de plantación, don Domingo!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("FMQP_ReceiveReward");
		break;

	case "noble_46":
		PlaySound("Voice\Spanish\YoungMan02.wav");
		dialog.text = "Eh, ¡llegamos tarde señor! Qué lástima, mi buen viejo tío ya ha hecho una limpieza decente entre sus papeles. Parece que le hablaron de Santo Domingo y tomó medidas de precaución... ¡Pero no voy a dejarlo así! Debería ver al gobernador de  para iniciar un procedimiento legal contra mi tío. Estoy harto de que maneje mi riqueza.";
		link.l1 = "Buena decisión.";
		link.l1.go = "noble_47";
		break;

	case "noble_47":
		dialog.text = "¡Quiero agradecerle, capitán! ¡Fue un placer! Le regalo mi estoque como muestra de mi gratitud hacia usted. Ella me sirvió bien, ahora que le sirva a usted aún mejor. Mírela y recuerde a su buen amigo español - marqués Domingo Albalate!";
		link.l1 = "¡Muchas gracias señor! No esperaba...";
		link.l1.go = "noble_48";
		break;

	case "noble_48":
		Log_Info("Has recibido la Espada Pequeña");
		PlaySound("interface\important_item.wav");
		RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
		GiveItem2Character(pchar, GetGeneratedItem("blade_16")); // belamour legendary edition используем GetGeneratedItem иначе пачка одинаковых клинков из первой части массива
		dialog.text = "Y ahora, ay, tengo que despedirme. Debo ir a . Mi existencia despreocupada ha terminado, es hora de vivir como un hombre adulto. ¡Buen viento y buena mar!";
		link.l1 = "¡Buena suerte con tu tío, don Domingo! ¡Estoy seguro de que prevalecerás!";
		link.l1.go = "noble_49";
		break;

	case "noble_49":
		DialogExit();
		chrDisableReloadToLocation = false;
		LocatorReloadEnterDisable("PortoBello_Plantation", "reload2_back", false);
		npchar.lifeday = 0;
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 40.0);
		pchar.questTemp.FMQP = "fail";
		AddQuestRecord("FMQ_Portpax", "13");
		CloseQuestHeader("FMQ_Portpax");
		sld = &Locations[FindLocation("PortoBello_Plantation")];
		sld.soldiers = true;
		break;

	case "uncle":
		PlaySound("Voice\Spanish\OliverTrast02.wav");
		dialog.text = "Parece que llegué a tiempo. Mi despreocupado sobrino y su ángel guardián, el capitán " + GetFullName(pchar) + ". No te sorprendas tanto, francés, sé quién eres.";
		link.l1 = "¿Luis Ortiz?";
		link.l1.go = "uncle_1";
		break;

	case "uncle_1":
		dialog.text = "Estás en lo correcto, capitán, pero todo lo demás lo tienes mal. No deberías meter las narices en asuntos familiares de otros hombres. Ni siquiera tienes idea de a quién estás protegiendo. Mi sobrino disoluto Domingo es un libertino sin valor, el visitante número uno de cada taberna y burdel que se acuesta o al menos intenta acostarse con cada muchacha en el horizonte. Le pago su alquiler cada mes y lo desperdicia en días siempre demandando más y más. Una y otra vez. Su comportamiento constante y poco digno enloqueció a su madre y a mi hermana\nEscuché rumores de que este chico travieso incluso contrató y dirigió a algunos corsarios ingleses hacia un cierto barco del Marqués Ricardo Albalate que hundieron junto con ese hombre digno y mi querida hermana. Domingo quería tanto el dinero de nuestra familia que mataría por ello... Tristemente, no logré desenterrar suficiente evidencia para enviar a este sinvergüenza a la horca.";
		link.l1 = "";
		link.l1.go = "uncle_2";
		break;

	case "uncle_2":
		DialogExit();
		sld = CharacterFromID("FMQP_noble");
		sld.Dialog.currentnode = "noble_34";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

	case "uncle_3":
		dialog.text = "Típico. Gritos, golpes de espadas y jarros, lleno de ruido y furia, significando nada. ¿Cuánto te pagó, capitán, por tu protección?";
		link.l1 = "Por lo que entiendo, después de que no pudiste encontrar pruebas contra tu sobrino, comenzaste a enviar asesinos tras él. Parece que una simple demanda habría sido suficiente.";
		link.l1.go = "uncle_4";
		break;

	case "uncle_4":
		dialog.text = "Hablas mentiras. Domingo aquí ha hecho una cantidad ilimitada de enemigos. Ha dejado un rastro de amantes despechadas y maridos cornudos a su paso. ¡Me pregunto cómo ha logrado sobrevivir tanto tiempo! Pregúntale, ¿cuántas bodas ha arruinado? ¿Cuántos prometidos insultados ha herido o matado?";
		link.l1 = "Su sirviente Ugo...";
		link.l1.go = "uncle_5";
		break;

	case "uncle_5":
		dialog.text = "¡Ah Ugo! ¡El peor bribón de todos! Ugo amaba a su maestro granuja. Todos los crímenes de su maestro no eran más que travesuras de niños para él. Recuerda, francés, el negocio familiar es solo para la familia. Aquellos que se entrometen y fisgonean se encontrarán en aguas calientes.";
		link.l1 = "Ahora me estás amenazando.";
		link.l1.go = "uncle_6";
		break;

	case "uncle_6":
		int icpy = GetOfficersQuantity(pchar);
		iTotalTemp = 10000 + 10000 * icpy;
		dialog.text = "No una amenaza, capitán, una promesa. Mira aquí, muchacho, has llegado lejos, pero como te tomo por una víctima engañada y no como un enemigo, escucha mi oferta simple y generosa: retírate. No quiero derramar sangre aquí. No necesitamos tu ayuda para resolver nuestros asuntos familiares. Incluso estoy dispuesto a compensar los problemas que has tenido por culpa de mi idiota sobrino -" + FindRussianMoneyString(iTotalTemp) + "reales de a ocho. Tómalo y déjanos enteros. Rechaza mi oferta y te devolveremos a tu barco en finas rodajas.";
		link.l1 = "'La familia primero' es lo que siempre digo. No es asunto mío entonces, entrega el dinero y 'vaya con Dios.'";
		link.l1.go = "uncle_7";
		link.l2 = "Tu historia apesta más que el abono de tu plantación. Don Domingo puede que no sea un santo, ¡pero tú, señor, eres un diablo!";
		link.l2.go = "uncle_8";
		break;

	case "uncle_7":
		AddMoneyToCharacter(pchar, iTotalTemp);
		dialog.text = "Sabía que eras un hombre razonable. Toma tu dinero y adiós, capitán. Intenta no hurgar en la ropa sucia de los demás en el futuro; nunca lo aprecian.";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("FMQP_UncleExit");
		break;

	case "uncle_8":
		dialog.text = "¿Un demonio? ¡Pues, me deleitaré enviándote al infierno!";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuest("FMQP_UncleFight");
		break;

	case "ugo":
		pchar.quest.FMQP_SantoDomingoOver.over = "yes";
		PlaySound("Voice\Spanish\Serve_senior.wav");
		dialog.text = TimeGreeting() + " señor. ¿Cómo puedo ser de servicio?";
		link.l1 = "Saludos. Perdón, pero ¿es esta la residencia del Señor Domingo Albalate?";
		link.l1.go = "ugo_1";
		break;

	case "ugo_1":
		dialog.text = "Sí, esta es la casa de Albalate. Es modesta pero cómoda. Mi nombre es Ugo, sirvo al joven amo. ¿Estás aquí por él?";
		link.l1 = "Sí, señor. Don Domingo me invitó a su casa no hace mucho. Fue muy persuasivo. ¿Puedo verlo?";
		link.l1.go = "ugo_2";
		break;

	case "ugo_2":
		dialog.text = "¡Ay, mi buen caballero, Don Domingo no está en casa en este momento! Personalmente, me gustaría saber yo mismo dónde encontrar a ese travieso... eh, perdón, joven señor. ¿Puedo preguntar qué necesita de él?";
		link.l1 = "Bueno... Ayudé a Don Domingo por casualidad. Fue atacado por dos bribones en una taberna de Puerto Príncipe. Asistí a su amo para defenderse de esos... ¿cómo los llamó él... maldita canalla? Don Domingo me invitó a visitarlo aquí después de que terminara con la investigación. Pensé que todo debería estar resuelto ya, así que esperaba encontrarlo en casa.";
		link.l1.go = "ugo_3";
		break;

	case "ugo_3":
		dialog.text = "¡Madre de Dios! ¡Qué historias tan espantosas cuentas aquí! Debo ver al comandante inmediatamente, ¡para advertirle sobre los peligros que enfrenta Don Domingo ahora mismo! ¡Señor, debe irse y yo debo apresurarme!";
		link.l1 = "Tómalo con calma, Ugo. Tu joven amo está a salvo. Mencionó que sus documentos están en orden, se suponía que ya debían liberarlo, por eso estoy aquí. Creo que deberíamos verlo pronto.";
		link.l1.go = "ugo_4";
		break;

	case "ugo_4":
		dialog.text = "¡Oh! ¿Cómo pudiste? Mi joven amo, ese chico ingenuo, ¿y en manos de esos franceses comedores de ranas?! ¿Sin mencionar a los ladrones que amenazan su vida? No, debo ver al comandante. ¡Señor, por favor, vaya!";
		link.l1 = "Está bien, está bien, no seas tan insistente. Me voy.";
		link.l1.go = "ugo_exit";
		link.l2 = "Señor, ¿por qué tan nervioso? Ya le dije que no hay peligro para su amo. Déjeme quedarme aquí y esperar la llegada del Señor Domingo, estoy muy cansado de mi largo viaje y agradecería su hospitalidad. Me gustaría un poco de agua fresca y un baño caliente para enjuagar la brisa salada de mi garganta. Luego puede ir al cuartel y hacer lo que quiera.";
		link.l2.go = "ugo_5";
		break;

	case "ugo_exit":
		DialogExit();
		LocatorReloadEnterDisable("Santodomingo_town", "houseSp4", true);
		DoQuestReloadToLocation("SantoDomingo_town", "reload", "houseSp4", "FMQP_SDMFail");
		break;

	case "ugo_5":
		dialog.text = "¡Señor, salga de esta casa de inmediato!";
		link.l1 = "Ugo, realmente dudo que a un sirviente se le permita hablar de esta manera con un caballero visitante. ¡También dudo que Don Domingo apruebe tal trato a un hombre que le salvó la vida!";
		link.l1.go = "ugo_6";
		break;

	case "ugo_6":
		dialog.text = "¿De veras? (llamando arriba) Muchachos, bajad, ¡tenemos un problema!";
		link.l1 = "¿Qué diablos?";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("FMQP_SantoDomingoFight");
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
