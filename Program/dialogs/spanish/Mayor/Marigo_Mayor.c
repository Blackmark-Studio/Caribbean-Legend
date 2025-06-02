// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué quieres? Pregunta sin rodeos.", "Te escucho, ¿cuál es la pregunta?"), "Esta es la segunda vez que tratas de preguntar...", "Esta es la tercera vez que intentas preguntar...", "¿Cuándo va a terminar esto?! ¡Soy un hombre ocupado, trabajando en asuntos de la colonia y todavía me estás molestando!", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "Ahora no. Lugar y momento equivocados."), "Verdad... Pero más tarde, no ahora...", "Preguntaré... Pero un poco más tarde...", "Lo siento, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		// Jason, Португалец
		if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToGovernor")
		{
			link.l1 = "¡Su Gracia, tengo noticias absolutamente excelentes y urgentes para usted! ¡He capturado a Bartolomeo el Portugués, el bastardo está bajo guardia y busca un juicio justo! Y estoy buscando alguna modesta gratitud de la Compañía...";
			link.l1.go = "Portugal";
		}
		// Португалец

		// Addon-2016 Jason ФМК-Сент-Кристофер
		if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "governor")
		{
			link.l1 = "Insististe en verme, señor gobernador...";
			link.l1.go = "FMQN";
		}
		if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_battle_complete")
		{
			link.l1 = "Estoy aquí por el asunto de los espías ingleses, señor gobernador...";
			link.l1.go = "FMQN_7";
		}
		break;

	case "Cupture_after":
		dialog.text = RandPhraseSimple("Ya lo has tomado todo. ¿Qué más quieres?", "¿Queda algo que no hayas agarrado?");
		link.l1 = RandPhraseSimple("Solo echando un vistazo...", "Solo comprobando, podría olvidar llevarme algo...");
		link.l1.go = "exit";
		NextDiag.TempNode = "Cupture_after";
		break;

	// Jason, Португалец
	case "Portugal":
		dialog.text = "Bartolomeo... ¿Bart el Portugués está en mi ciudad? ¡¿Vivo?!!";
		link.l1 = "Lo está, su Gracia, y está bajo una guardia confiable. Se lo entregaré después de recibir un recibo por la cabeza de Bart que fue prometido por la Compañía. Los doblones de oro también estarían bien...";
		link.l1.go = "Portugal_1";
		break;

	case "Portugal_1":
		dialog.text = "¡Bill, doblones? ¿Estás loco?! ¿En qué estabas pensando al traer a esta bestia a mi ciudad?! Si él está aquí, entonces su fragata no está lejos de la isla y su tripulación puede estar en la ciudad misma, ¡ahora mismo!";
		link.l1 = "He matado a los que estaban con él, no sé sobre los otros, pero supongo que no importa realmente porque Bartolomeo es...";
		link.l1.go = "Portugal_2";
		break;

	case "Portugal_2":
		dialog.text = "¡Sí lo hace! ¿De verdad no entiendes lo que has hecho? ¡El 'Albatross' está cerca de la isla y has capturado al pirata cuya brutalidad asusta incluso a su propia gente sedienta de sangre! ¡Aléjate de aquí! ¡Aléjate de la isla! ¡Y llévate a este monstruo contigo!";
		link.l1 = "Pero escucha, ¿qué hay de la recompensa prometida y...?";
		link.l1.go = "Portugal_3";
		break;

	case "Portugal_3":
		dialog.text = "¡No quiero ver mi ciudad ardiendo por tu avaricia y la venganza de la Compañía! ¡Solo hay reclutas frescos en mi fuerte y la mitad de ellos se escaparán tan pronto como se enteren de quién y por qué está atacando sus baluartes! Y entonces comenzará la masacre... ¡No voy a arriesgarme, ¿me oyes?! ¡Lárgate y entrégalo a Curazao tú mismo si la Compañía quiere tanto su cabeza!\n¡Hazlo inmediatamente antes de que sea demasiado tarde! Y puedes hacer con él lo que quieras, incluso tirarlo por la borda de tu barco, ¡solo no lo hagas en mi ciudad!\n¡Hans! ¡Hans, ¿dónde estás, idiota perezoso?! ¡Tráeme una poción de valeriana o algo y alguien, por el amor de Dios, por favor saque a este aventurero de mi residencia!";
		link.l1 = "Pero su Gracia...";
		link.l1.go = "Portugal_4";
		break;

	case "Portugal_4":
		DialogExit();
		DoQuestReloadToLocation("Marigo_town", "reload", "reload3_back", "PortugalOutResidence");
		break;

	// Addon-2016 Jason ФМК-Сент-Кристофер
	case "FMQN":
		DelLandQuestMark(npchar);
		dialog.text = "¡Muy bien! Dígame, capitán, ¿encontró algún buque militar o mercante inglés al acercarse a nuestra isla?";
		link.l1 = "No, señor. No vi ni buques militares ni comerciales bajo la bandera inglesa en vuestras aguas.";
		link.l1.go = "FMQN_1";
		break;

	case "FMQN_1":
		dialog.text = "Ya veo. ¿Cuánto tiempo esperas quedarte aquí?";
		link.l1 = "Tres días más o menos...";
		link.l1.go = "FMQN_2";
		break;

	case "FMQN_2":
		dialog.text = "En ese caso, tengo una oferta para usted. Según nuestra inteligencia, existe el riesgo de espías ingleses aquí. Daré diez mil pesos como recompensa por cualquier información sobre embarcaciones y personas sospechosas en la isla, en la ciudad, sus alrededores, en las costas, etc. La recompensa se incrementará significativamente en caso de asistir a las autoridades en la detención o eliminación de un enemigo.\nTodo capitán civil es bienvenido a participar en la investigación y a patrullar las costas y la selva en busca de espías.\nEs posible que encontréis nuestro corbeta militar, el Zeepard, no temáis, está de patrulla. Podéis dirigiros a su capitán en caso de encontrar a los británicos.";
		link.l1 = "¡Ay, su Excelencia, pero estoy aquí solo con intenciones pacíficas de comercio. Tendré que dejar esta isla tan pronto como me reabastezca y termine mis asuntos aquí!";
		link.l1.go = "FMQN_3";
		link.l2 = "¡Una oferta tentadora! Creo que participaré y saquearé las aguas y costas de tu isla. Incluso podría quedarme aquí por un tiempo.";
		link.l2.go = "FMQN_5";
		break;

	case "FMQN_3":
		dialog.text = "Es solo información por nada, capitán. Sin presiones. Sabes a quién dirigirte en caso de que veas algo sospechoso.";
		link.l1 = "Muy bien, mynheer, lo tengo. ¡Adiós!";
		link.l1.go = "FMQN_4";
		break;

	case "FMQN_4":
		DialogExit();
		pchar.questTemp.FMQN = "way_eng_1";
		AddQuestRecord("FMQ_Nevis", "8");
		chrDisableReloadToLocation = false;
		FMQN_SetSoldiersInCave();
		break;

	case "FMQN_5":
		dialog.text = "¡Espléndido, capitán! Ya que lo tomáis tan en serio, aseguraos de hablar también con nuestro comandante. Él es responsable de capturar a los espías y podría daros información adicional.";
		link.l1 = "Bien, señor. Iré a verlo.";
		link.l1.go = "FMQN_6";
		break;

	case "FMQN_6":
		DialogExit();
		pchar.questTemp.FMQN = "way_div";
		AddQuestRecord("FMQ_Nevis", "9");
		chrDisableReloadToLocation = false;
		AddLandQuestMarkToPhantom("marigo_prison", "marigoJailOff");
		break;

	case "FMQN_7":
		DelLandQuestMark(npchar);
		dialog.text = "Hemos estado esperándote, Mynheer " + GetFullName(pchar) + ". Permítame expresar nuestro agradecimiento por sus acciones al eliminar al peligroso grupo de asalto inglés. Acepte estos diez mil pesos. Además: 200 piezas de seda serán cargadas en la bodega de su barco y una recompensa muy especial: una licencia de tres años de la Compañía Holandesa de Comercio de las Indias Occidentales. Este es un documento extremadamente valioso, espero que lo sepa.";
		link.l1 = "¡Por supuesto! Una licencia de tres años, esto es ciertamente grande.";
		link.l1.go = "FMQN_8";
		break;

	case "FMQN_8":
		dialog.text = "Por favor, toma tu recompensa. Además, puedes contar con la gratitud de todos los ciudadanos y autoridades holandesas. Eres una sensación en Philipsburg, estaríamos encantados de verte de nuevo.";
		link.l1 = "Escuchar palabras tan cálidas es más valioso que la licencia. Gracias, ha sido un placer. Y ahora, debo continuar mi camino. ¡Adiós!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("FMQN_HollandBattleComplete");
		break;

	// Jason НСО
	case "tomas":
		dialog.text = "¡Nos rendimos! En el nombre de todo lo sagrado, te ruego, no saques y saqueen Philipsburg y sus ciudadanos. ¡Estoy dispuesto a escuchar tus demandas!";
		link.l1 = "No se preocupe por los ciudadanos, señor. Los súbditos de la Corona Francesa no deben temer a los soldados franceses.";
		link.l1.go = "tomas_1";
		break;

	case "tomas_1":
		dialog.text = "¿La Corona Francesa?";
		link.l1 = "Exactamente. Esta isla pertenece a Francia, y ustedes son solo inquilinos aquí. Inquilinos insolentes, que creyeron que esta isla podría ser de su propiedad. A partir de hoy, la autoridad holandesa en San Martín ha llegado a su fin. ¿Está claro?";
		link.l1.go = "tomas_2";
		break;

	case "tomas_2":
		dialog.text = "Pero... Pero, ¿qué sucederá con nosotros, con los soldados holandeses que se rindieron ante usted, y los heridos? ¿Y qué...?";
		link.l1 = "Eso dependerá solo de usted, Mynheer Thomas. Si me hace un favor, entonces permitiré que todos aquellos que se rindieron lleven a sus heridos y partan de aquí en un barco o barcos que encontraremos en los muelles, hacia Curazao, hacia Mynheer Stuyvesant.";
		link.l1.go = "tomas_2_1";
		break;

	case "tomas_2_1":
		dialog.text = "";
		link.l1 = "De lo contrario, serás mantenido en las bodegas de mis barcos y en los casamatas de Saint Kitts. Además, algunos funcionarios importantes holandeses tendrán que ser colgados, solo para asegurarnos de que Stuyvesant pierda su interés en conquistar nuestras colonias...";
		link.l1.go = "tomas_3";
		break;

	case "tomas_3":
		dialog.text = "(tartamudeando) ¿Qué... Qué... sobre qué cl...ase de f-fav...or?";
		link.l1 = "En las profundidades de la isla yace una manzana de la discordia: una mina de sal. Sé que no solo hay mineros y esclavos, sino también soldados holandeses, armados hasta los dientes. Deben ser de la Guardia de la Compañía, ¿no es así, Mynheer? Les ofreceré rendirse, o usaré la fuerza en caso de que se nieguen. Necesito un guía que me muestre el camino a la mina. Encuéntrame un guía así.";
		link.l1.go = "tomas_4";
		break;

	case "tomas_4":
		dialog.text = "¿M-m-m-ina de s-s-sal?";
		link.l1 = "Exactamente. No temas, Mynheer Thomas, si los guardias de la mina son lo suficientemente sabios como para rendir sus armas, les daré la oportunidad de abandonar la isla. No necesito un derramamiento de sangre innecesario. No te preocupes, tu conciencia estará tranquila: incluso si no me dices dónde está la mina, la isla de San Martín es lo suficientemente pequeña como para que pueda encontrar la mina sin tu ayuda, solo que no quiero perder mi tiempo vagando por matorrales y pantanos. Así que este trato es más beneficioso para ti que para mí.";
		link.l1.go = "tomas_5";
		break;

	case "tomas_5":
		dialog.text = "Es... está bien, te diré cómo llegar a la mina, p-pero debes d-da...rme tu palabra de que todos... todos nosotros abandonaremos esta isla.";
		link.l1 = "Te doy mi palabra como oficial y noble.";
		link.l1.go = "tomas_6";
		break;

	case "tomas_6":
		dialog.text = "En la bahía de Grand Case... en su extremo, cerca del agua, hay... hay piedras. Allí... allí, detrás de ellas, a lo largo de la costa, hay un pasaje junto al agua, allí... es poco profundo allí, hasta la cintura o menos. Necesitas rodear la roca y llegarás a una gran playa, donde... donde no puedes atracar tu barco debido a los arrecifes alrededor. Desde esta playa hay un camino directo... a... a la mina.";
		link.l1 = "Excelente. Me pongo en marcha. Y usted, señor, permanecerá aquí bajo la atenta vigilancia de mis soldados hasta que regrese.";
		link.l1.go = "tomas_7";
		break;

	case "tomas_7":
		DialogExit();
		SetReturn_Gover_Dialog_Exit(NPChar);
		LAi_SetActorType(npchar);
		pchar.quest.Patria_BastionGate.win_condition.l1 = "location";
		pchar.quest.Patria_BastionGate.win_condition.l1.location = "Shore40";
		pchar.quest.Patria_BastionGate.function = "Patria_BastionShore";
		AfterTownBattle();
		AddQuestRecord("Patria", "50_1");
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
