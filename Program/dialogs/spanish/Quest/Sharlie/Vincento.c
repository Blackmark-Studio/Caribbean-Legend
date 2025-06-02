// отец Винсенто
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "santiago")
		{
			dialog.text = "Por fin veo al famoso capitán francés " + GetFullName(pchar) + " en carne y hueso. He oído mucho sobre tus hazañas. Eres un valiente soldado y, espero, un hijo leal y fiel de nuestra Madre la Santa Iglesia Católica Romana. Siéntate, hijo mío. No es necesario que te pongas de pie por mí. ¡Dominus vobiscum! ";
			link.l1 = "Et cum spiritu tuo, Su Excelencia. Mi camino aquí fue largo y arduo... Per aspera ad astra y todo eso...";
			link.l1.go = "utensil";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "twoitems" && !CheckAttribute(npchar, "quest.skinmap"))
		{
			dialog.text = "Sí, puedo ver en tus ojos que tienes noticias para mí. Tienes toda mi atención.";
			link.l1 = "Su Excelencia, he encontrado a su secretario desaparecido...";
			link.l1.go = "guardoftruth";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "mayak")
		{
			dialog.text = "¿Me has traído noticias de San José, hijo mío?";
			link.l1 = "Sí, Su Excelencia. Determiné qué le sucedió a nuestro conocido mutuo Miguel Dichoso y su fragata perdida. Tan pronto como su barco entró en el Atlántico rumbo a España, fue atrapado inmediatamente por un vendaval contrario y arrojado de nuevo al Caribe.";
			link.l1.go = "guardoftruth_10";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "begin")
		{
			dialog.text = "Pax vobiscum, hijo mío... ¿Qué puedo hacer por ti?";
			link.l1 = TimeGreeting() + ", Su Excelencia. ¿Tiene alguna noticia sobre nuestro arreglo?" 
			link.l1.go = "guardoftruth_17";
			break;
		}
		dialog.text = "¿Hay algo que desees, hijo mío?";
		link.l1 = "No, nada, Padre.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "utensil":
		dialog.text = "Entrad por la puerta estrecha; porque ancha es la puerta y espacioso el camino que lleva a la perdición, y son muchos los que entran por ella. Porque estrecha es la puerta y difícil el camino que lleva a la vida, y pocos son los que lo encuentran'. El camino de la justicia es siempre difícil, hijo mío. Pero la meta que se alcanza recompensa plenamente al justo por sus obras.";
		link.l1 = "Estoy de acuerdo, Su Excelencia. He completado las tareas que me encomendó. Ya tiene al cobarde pirata que robó los preciosos vasos de la Iglesia. Ahora estoy devolviendo todas las cosas que fueron tomadas: la custodia, la cruz y el incensario. Tómenlos para la parroquia de Santiago.";
		link.l1.go = "utensil_1";
		break;

	case "utensil_1":
		RemoveItems(pchar, "jewelry33", 1);
		RemoveItems(pchar, "jewelry34", 1);
		RemoveItems(pchar, "jewelry35", 1);
		dialog.text = "¡Benedicite! Te agradezco de todo corazón por tu fiel servicio a la Santa Madre Iglesia y a la parroquia de Santiago, hijo mío. Tus obras no quedarán sin recompensa. Los feligreses han recolectado una ofrenda para el valiente guerrero que devolvió sus objetos robados, y con gusto te la entrego en su nombre. 'El obrero es digno de su salario.'";
		link.l1 = "Gracias, Su Excelencia. ¡Qué agradable sorpresa!";
		link.l1.go = "utensil_2";
		break;

	case "utensil_2":
		GiveItem2Character(pchar, "chest");
		Log_Info("Has recibido un cofre de doblones");
		PlaySound("interface\important_item.wav");
		dialog.text = "La fiel servicio a la Madre Iglesia siempre es fielmente recompensado, " + pchar.name + "  Espero, por mi parte, que sigas siendo un guerrero dedicado a la defensa y protección de la cristiandad, pues hay una amenaza mortal que se cierne sobre nosotros como la mítica Espada de Damocles.";
		link.l1 = "¿Qué podría ser eso, Su Excelencia?";
		link.l1.go = "utensil_3";
		break;

	case "utensil_3":
		dialog.text = "Quizás estás destinado a ser nuestro campeón en la próxima batalla contra los poderes oscuros y principados de este mundo, hijo mío, pues hay muchos signos y presagios de que algo malvado se aproxima.";
		link.l1 = "¿Signos y presagios?";
		link.l1.go = "utensil_4";
		break;

	case "utensil_4":
		dialog.text = "Muchos, hijo mío... Uno de ellos es tu ansia de buscar el oro indio perdido del pagano Tayasal, porque lo que se conserva en su tesoro es exactamente lo que representa peligro para todo el mundo cristiano.";
		link.l1 = "¿Podría iluminarme un poco sobre este oro, reverendo Padre? Ya he oído hablar de la historia de su desaparición, pero ¿de qué tipo de amenaza habla usted?";
		link.l1.go = "utensil_5";
		break;

	case "utensil_5":
		dialog.text = "Escucha atentamente, hijo mío, y sabe que todo lo que estás a punto de oír es solo para tus oídos. Mucho antes de que Miguel Dichoso sacara ese tesoro pagano de la antigua ciudad india, hice interrogar a un hombre cautivo de los indios Itza sobre nuestra misión en el Caribe. El pueblo Itza son descendientes de los mayas, un poderoso imperio perdido siglos antes de que incluso Cristóbal Colón y sus hombres pusieran pie por primera vez en el Nuevo Mundo. El Imperio Maya gobernaba las tribus circundantes con mano de hierro, con un poder indescriptible que les fue otorgado a través de tratos infernales con demonios. Magias oscuras compradas con la sangre de generaciones de sacrificios humanos. \nEste hombre Itza sabía sobre Tayasal, una ciudad maya perdida y el increíble mal aún sellado dentro de ella. Nos contó todo lo que sabía. Si esos sellos se abren, las consecuencias serían apocalípticas. Desde ese momento, he hecho todo lo posible para evitar que este terrible mal sea despertado. Escribí al Escorial y a Roma desesperadamente pidiendo ayuda.\nEllos escucharon y enviaron a Don Ramón de Mendoza y Riba, quien estableció su base en Providencia y comenzó a buscar Tayasal. Fue entonces cuando descubrí que el buen Don Mendoza tenía...motivaciones diferentes para encontrar la ciudad perdida. En lugar de prevenir el fin del mundo, buscaba servir a Mammon en lugar de a Cristo.\nEs por eso que Dios lo abandonó y envió al ángel de la muerte a su campamento. Todas sus acciones fueron inútiles y solo llevaron a muertes sin sentido de soldados españoles y conversos indios fieles. Escribí al Escorial pidiendo destituir a Ramón de Mendoza debido a su incompetencia flagrante y estuvieron de acuerdo en relevarlo de sus deberes, pero...";
		link.l1 = "Miguel Dichoso ha llegado.";
		link.l1.go = "utensil_6";
		break;

	case "utensil_6":
		if (CheckAttribute(pchar, "questTemp.Dolly"))
			sTemp = "¿Kukulcan? Sancta Maria, Mater Dei, ora pro nobis! Kukulcan de nuevo, esa vieja serpiente...";
		else
			sTemp = "Hm...";
		dialog.text = "Precisamente. Ese aventurero enviado por el diablo encontró Tayasal junto con los tesoros de los antiguos mayas. Sin embargo, la alegría del Don Mendosa fue efímera. Todos esos tesoros desaparecieron junto con Dichoso en su ruta de regreso a España. Es probable que, junto con todos los lingotes de oro y ornamentos, Miguel se llevara consigo una fuente ancestral de maldad, la máscara aterradora de un antiguo dios demonio maya llamado Kukulcán.";
		link.l1 = sTemp + "¿Pero de qué mal habláis, Su Excelencia? ¿Cómo lo sabéis?";
		link.l1.go = "utensil_7";
		break;

	case "utensil_7":
		dialog.text = "Es un mal que trae la muerte a todos los cristianos bautizados del Caribe, del Nuevo Mundo, y posiblemente del Viejo Mundo también. El fin vendrá como un ladrón en la noche, y nadie siquiera se dará cuenta de lo que ha pasado. ¡Y ya hay presagios de esto por todas partes!";
		link.l1 = "¿Qué presagios? No entiendo...";
		link.l1.go = "utensil_8";
		break;

	case "utensil_8":
		dialog.text = "Hijo mío, ¿acaso estás tan ciego que ni siquiera te das cuenta de ellos? ¡Han estado sucediendo durante veinticinco años, casi sin parar!";
		link.l1 = "Quisiera mencionar humildemente, Su Excelencia, que el curso de mi vida se enumera en exactamente este período de tiempo, sin mencionar que he vivido la mayor parte de mi vida en Europa. Mi ignorancia debería ser ligeramente excusada.";
		link.l1.go = "utensil_9";
		break;

	case "utensil_9":
		dialog.text = "Entiendo, " + pchar.name + ". Ahora, ¿no has notado cosas extrañas sucediendo en todo el Caribe tan pronto como llegaste aquí desde Europa? ¿No te parece extraño que la brujería, la magia negra y otros rituales tengan mucha más fuerza aquí que en casa? Amuletos paganos encantados por chamanes indios poseen un poder real que cualquier hombre puede experimentar solo con sostenerlos.\nIncluso nuestros alquimistas cristianos, ¡que Dios les haga ver el error de sus caminos!, han dominado el arte de fabricar objetos encantados. No se dan cuenta de que están sirviendo al mismo Diablo al hacerlo. ¿No sientes la presencia antinatural de algo infernal acechando justo fuera de tu visión periférica?";
		link.l1 = "Tienes razón, Padre. Al principio me sorprendió, pero ahora supongo que ya me he acostumbrado... ¡Es el Nuevo Mundo después de todo!";
		link.l1.go = "utensil_10";
		break;

	case "utensil_10":
		dialog.text = "Pero no siempre fue así. La oscuridad de la que hablo llegó aquí hace unos veinticinco años y gana más y más poder con cada día que pasa. Eso significa solo una cosa: 'eso' ya ha llegado, 'eso' está entre nosotros, y 'eso' está trabajando...";
		link.l1 = "¿De quién estás hablando? ¿Quién es este misterioso 'ello'?";
		link.l1.go = "utensil_11";
		break;

	case "utensil_11":
		dialog.text = "El enemigo jurado de los cristianos, deseando la destrucción de la Iglesia y toda la cristiandad.";
		link.l1 = "¿Estás hablando del Anticristo?";
		link.l1.go = "utensil_12";
		break;

	case "utensil_12":
		dialog.text = "Ya sea 'el' Anticristo o simplemente 'un' anticristo, no me atrevo a decir. No importa qué nombre lleve esta bestia cuando se viste de carne mortal en grotesca parodia de la Encarnación de Nuestro Salvador. Lo importante es lo que va a hacer. Estoy aquí para detenerlo, y tú vas a ayudarme. Pero nos hemos dejado llevar un poco. Eres un hombre de acción. Probablemente preferirías ir al grano y saltarte la teología, ¿correcto?";
		link.l1 = "Al contrario, he descubierto muchas cosas nuevas e importantes de usted, Su Excelencia. Estoy listo para escuchar más.";
		link.l1.go = "utensil_13";
		break;

	case "utensil_13":
		dialog.text = "Eres cortés y bien educado, hijo mío. Eso es bueno. Ahora volvamos a la razón por la que te conferiste conmigo. Nuestro objetivo colectivo es encontrar los tesoros de Tayasal que tomó Dichoso. Probablemente podremos encontrar un arma entre esos tesoros que podamos usar en la próxima batalla contra el Diablo.";
		link.l1 = "¿Pero puede ser que Dichoso ya haya dejado el Caribe y esté sentado sobre una pila de oro de regreso en España?";
		link.l1.go = "utensil_14";
		break;

	case "utensil_14":
		dialog.text = "No. Tengo pruebas de que estos tesoros todavía están aquí en el Caribe. No necesitas conocer mis fuentes aún, debes confiar en mí. Además, creo que Dichoso le estaba mintiendo al barón.\nSu historia sobre las ruinas de Tayasal no coincide con lo que mi indio Itza me contó bajo interrogatorio. Sin mencionar que el hecho de que Dichoso fuera el único sobreviviente de la emboscada Mosquito fue un poco demasiado conveniente.";
		link.l1 = "Supongo que Don Mendosa también lo cree, ya que asaltó Saint-Pierre tratando de encontrar a Dichoso.";
		link.l1.go = "utensil_15";
		break;

	case "utensil_15":
		dialog.text = "Las acciones del barón no deberían preocuparte, hijo mío. Él está motivado solo por la lujuria por el oro y el beneficio personal. Su codicia será una piedra de molino alrededor de su cuello mientras a su alrededor buenos hombres y mujeres cristianos se enfrentan a las fuerzas del Infierno.";
		link.l1 = "¿Tienes alguna pista sobre dónde deberíamos buscar a Dichoso y el tesoro?";
		link.l1.go = "utensil_16";
		break;

	case "utensil_16":
		dialog.text = "Pienso en ello cada minuto, hijo mío, pero no tengo nada específico que contarte. Pero hay un hombre aquí que nos ayudará, un filósofo natural de Génova. Lo traje aquí conmigo para ayudar a categorizar cosas del Nuevo Mundo que podrían ser útiles para la misión de la Iglesia. Fue testigo del interrogatorio del indio Itza y, según mi mejor juicio, las cosas que escuchó lo impactaron y lo atrajeron perversamente.\nEl Diablo utilizó su curiosidad como un anzuelo envenenado y lo poseyó, cuerpo y alma. El Señor le había dado gran habilidad con la medicina y la alquimia, pero nuestro genovés cayó en la tentación de la magia negra y la hechicería. Habló con mi cautivo Itza varias veces sin mi permiso, luego desapareció. Debemos encontrarlo y salvar su alma.";
		link.l1 = "¿Supongo que se supone que debo encontrarlo?";
		link.l1.go = "utensil_17";
		break;

	case "utensil_17":
		dialog.text = "Sí, hijo mío. Él es el primer paso para encontrar el tesoro y el arma que podemos usar contra las fuerzas malignas que nos amenazan.";
		link.l1 = "¿Quién es este genovés?";
		link.l1.go = "utensil_18";
		break;

	case "utensil_18":
		dialog.text = "Su nombre es Gino Gvineili. Treinta años de edad, más o menos. Un médico y alquimista talentoso. Como dije, ahora estudia la magia negra. Según mi mejor información, se está escondiendo en algún lugar entre las colonias inglesas en el Caribe.\nEncuentra a Gino Gvineili, hijo mío. Si lograste encontrar a ese pirata que robó los vasos de nuestra iglesia, entonces también lograrás encontrar a mi secretario fugitivo y traerlo aquí. Rezaré por la intercesión de San Antonio en tu nombre.";
		link.l1 = "Veo, Su Excelencia. No perderé ni un minuto más. ¡Hasta luego!";
		link.l1.go = "utensil_19";
		break;

	case "utensil_19":
		DialogExit();
		AddQuestRecord("Guardoftruth", "35");
		bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win");
		if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && bOk)
		{
			pchar.questTemp.Guardoftruth = "jino";
			AddQuestUserData("Guardoftruth", "sText", "Casi me traiciono a mí mismo con un grito de sorpresa. El padre Vincento me ordenó que encontrara y le llevara a su secretario fugitivo, un médico alquimista llamado Gino Gvineili. ¡Ese mismo Gino que ocupa la habitación libre del segundo piso de mi casa en St. John's!");
		}
		else
		{
			pchar.questTemp.Guardoftruth = "merdok";
			AddQuestUserData("Guardoftruth", "sText", "Debo encontrar a un hombre llamado Gino Gvineili, escondido en algún lugar de las colonias inglesas del Caribe. Es médico y alquimista. ¿Dónde puede esconderse un hombre como él?");
		}
		break;

	case "guardoftruth":
		dialog.text = "Tenía plena fe en que dirías eso, " + pchar.name + ". Ahora mi fe se ve aún más fortalecida por mi certeza de que has sido enviado a mí por la mano de la Divina Providencia misma. ¿Dónde está mi desdichado, pródigo hijo?";
		link.l1 = "Me temo que no te va a gustar lo que estás a punto de escuchar, pero no tengo otra opción. Tu secretario está muerto.";
		link.l1.go = "guardoftruth_1";
		break;

	case "guardoftruth_1":
		dialog.text = "Que Dios salve su alma y le perdone por sus pecados... ¿Cómo sucedió, hijo mío?";
		link.l1 = "He encontrado a Gino en Antigua. Se estaba escondiendo allí en uno de los viejos edificios construidos bajo el laboratorio. No accedió a venir conmigo tranquilamente. Después de oír tu nombre y ver que estaba dispuesto a usar la fuerza, sacó un frasco de líquido claro de los pliegues de su largo atuendo y lo bebió al instante...";
		link.l1.go = "guardoftruth_2";
		break;

	case "guardoftruth_2":
		dialog.text = "";
		link.l1 = "Y luego ocurrió algo horrible: se puso rojo, luego azul oscuro. Cayó al suelo retorciéndose en un espasmo y en un minuto murió en un dolor horrible. Un fuerte olor a almendras llenó la habitación.";
		link.l1.go = "guardoftruth_3";
		break;

	case "guardoftruth_3":
		dialog.text = "Gino... Pobre tonto... Incluso pasó el último minuto de su vida en pecado al cometer suicidio. Qué pérdida tan trágica. Rezaré por su alma...";
		link.l1 = "Después de que murió, registré su morada y encontré este folio allí. ¿Podría acaso interesarte o tal vez ayudarnos en nuestras búsquedas? Hay algunas notas extrañas y esotéricas de algún tipo aquí...";
		link.l1.go = "guardoftruth_4";
		break;

	case "guardoftruth_4":
		RemoveItems(pchar, "Almanac", 1);
		Log_Info("Has entregado el almanaque");
		PlaySound("interface\important_item.wav");
		dialog.text = "Este es el almanaque del pobre Gino. Había estado escribiendo notas allí sobre todas sus exploraciones. Dámelo, hijo mío, estudiaré lo que está escrito en él. Tal vez encontremos una pista.\nAunque no me devolviste a Gino Gvineili, estoy satisfecho con tus esfuerzos, hijo mío. Ahora tengo algunas noticias para ti.";
		link.l1 = "Tienes mi atención, Padre.";
		link.l1.go = "guardoftruth_5";
		break;

	case "guardoftruth_5":
		dialog.text = "He adquirido información de que la isla de Trinidad fue el último lugar donde se vio la fragata de Dichoso. También sé un tiempo aproximado: principios de abril de 1654.\nVe a Trinidad y trata de averiguar algo sobre el destino de la fragata: hacia dónde se dirigía, qué planes tenía el capitán, cualquier cosa que puedas encontrar. Entiendo que ha pasado mucho tiempo y la memoria de la gente tiene límites, pero un hombre que se ahoga se agarrará a un clavo ardiendo.";
		link.l1 = "Haré todo lo que esté en mi poder.";
		link.l1.go = "guardoftruth_6";
		break;

	case "guardoftruth_6":
		dialog.text = "Déjame ver tu carta de paso seguro. Añadiré permiso para que visites la colonia de San José.";
		link.l1 = "Aquí.";
		link.l1.go = "guardoftruth_6a";
		break;

	case "guardoftruth_6a":
		RemoveItems(pchar, "VerifyPaper", 1);
		dialog.text = "Ahí... eso será todo. No olvides izar la bandera española en tu barco. ¡Adelante y recibe la bendición de Dios, hijo mío!";
		link.l1 = "Un momento, Su Gracia. ¿Podría hacerle una pregunta?";
		link.l1.go = "guardoftruth_7";
		break;

	case "guardoftruth_7":
		dialog.text = "Sí, por supuesto. ¿Qué te gustaría saber?";
		link.l1 = "Durante nuestro último encuentro, hablaste de un indio Itza que te había informado sobre Tayasal. He pensado mucho en ello... Dime, ¿tenía ese hombre algo con él? ¿Objetos de algún tipo, escritos, o algo por el estilo? Esto podría ser útil.";
		link.l1.go = "guardoftruth_8";
		break;

	case "guardoftruth_8":
		dialog.text = "No hay objetos especiales, hijo mío. Un taparrabos, joyas primitivas, una pipa de bambú con algunas hierbas y un trozo de cuero áspero usado como mordaza.\nTodo eso fue enviado a Don Ramón de Mendoza y Riba. Pero te aseguro que no había nada de interés.";
		link.l1 = "Ya veo. Gracias, Padre. ¡Hasta la próxima!";
		link.l1.go = "guardoftruth_9";
		break;

	case "guardoftruth_9":
		DialogExit();
		GiveItem2Character(pchar, "VerifyPaper");
		ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper_A");
		AddQuestRecord("Guardoftruth", "38");
		npchar.quest.skinmap = "true";
		pchar.questTemp.Guardoftruth.Trinidad = "begin";
		break;

	case "guardoftruth_10":
		dialog.text = "Que el Todopoderoso te bendiga y te guarde... ¿Qué terminó sucediendo con Miguel Dichoso? ¿Te enteraste?";
		link.l1 = "Lamentablemente, no lo hice. Lo último que los testigos pudieron decirme fue que la Santa Quiteria fue llevada por vientos huracanados en dirección a Martinica. No se sabe con certeza si el barco fue salvado o si pereció. Pero tengo sospechas de que Miguel Dichoso logró sobrevivir.";
		link.l1.go = "guardoftruth_11";
		break;

	case "guardoftruth_11":
		dialog.text = "¿Qué te hizo decidir eso, hijo mío?";
		link.l1 = "La clave es que la fragata se estaba escondiendo en algún lugar en dirección a Martinica. Y muy recientemente un gallardo caballero llamado Diego de Montoya, uno de los hombres del propio Don Ramón de Mendosa, atacó Saint-Pierre con el objetivo de encontrar a Miguel Dichoso, quien supuestamente se escondía allí.";
		link.l1.go = "guardoftruth_12";
		break;

	case "guardoftruth_12":
		dialog.text = "Entonces, el barón cree que Dichoso se escondió con los franceses...";
		link.l1 = "Conozco bien a Saint-Pierre y al Gobernador Jacques Dyel du Parquet, Su Excelencia. Nadie conocía a un español llamado Miguel Dichoso allí. ¿Puede decirme cómo encontrar a Diego de Montoya? Me gustaría hablar con él sobre Dichoso.";
		link.l1.go = "guardoftruth_13";
		break;

	case "guardoftruth_13":
		dialog.text = "¿Estás seguro de que estaría dispuesto a hablar contigo, hijo mío? No creo que lo haga, a menos que converses con espada y pistola.";
		link.l1 = "¿Acaso tu nombre podría hacerlo más dispuesto?";
		link.l1.go = "guardoftruth_14";
		break;

	case "guardoftruth_14":
		dialog.text = "Oh, " + pchar.name + ". Dudo que el hombre juramentado de Don Mendosa esté dispuesto a llegar a un acuerdo contigo. Ordenarle que llegue a San Diego para una audiencia conmigo podría ser una opción, pero tampoco estoy tan seguro de que Diego sería perfectamente sincero conmigo.";
		link.l1 = "¿Qué acción tomaremos ahora, Padre?";
		link.l1.go = "guardoftruth_15";
		break;

	case "guardoftruth_15":
		dialog.text = "Déjame un rato, hijo mío. Necesito procesar lo que me has contado y también juntar todos los hechos que ya conozco de mis diversas fuentes. Después te diré cuál es nuestro próximo movimiento. Pasa más tarde.";
		link.l1 = "Sí, Su Gracia. Lo haré. Revisaré periódicamente...";
		link.l1.go = "guardoftruth_16";
		break;

	case "guardoftruth_16":
		DialogExit();
		AddQuestRecord("Guardoftruth", "43");
		pchar.questTemp.Guardoftruth.Trinidad = "end";
		pchar.quest.GuardOT_setSpaOfficer.win_condition.l1 = "ExitFromLocation";
		pchar.quest.GuardOT_setSpaOfficer.win_condition.l1.location = pchar.location;
		pchar.quest.GuardOT_setSpaOfficer.function = "GuardOT_SetSpaOfficerInTown";
		NextDiag.CurrentNode = "guardoftruth_wait";
		break;

	case "guardoftruth_wait":
		dialog.text = "Dios te bendiga, hijo mío... ¿Qué puedo hacer por ti?";
		link.l1 = "¿Tiene alguna noticia, Su Excelencia?";
		link.l1.go = "guardoftruth_wait_1";
		break;

	case "guardoftruth_wait_1":
		dialog.text = "Por el momento no, hijo mío. Sin embargo, no desesperes. Mi gente y yo estamos trabajando en ello. Pásate más tarde.";
		link.l1 = "...";
		link.l1.go = "exit";
		NextDiag.TempNode = "guardoftruth_wait";
		break;

	case "guardoftruth_17":
		dialog.text = "Sí, hijo mío. Tengo algo de información sobre Miguel Dichoso. No fue en vano que creí que Dichoso aún estaba vivo y en el Caribe. Parece que Don Diego de Montoya tenía razón. Hemos recibido pruebas de un hombre que conocía a Miguel Dichoso de vista que el caballero desaparecido fue visto en el asentamiento pirata de Le Francois en Martinica en abril de 1654, después de la desaparición de la Santa Quiteria...";
		link.l1 = "¿Así que la fragata naufragó en las costas de Martinica?";
		link.l1.go = "guardoftruth_18";
		break;

	case "guardoftruth_18":
		dialog.text = "Desacelera, hijo mío. No tenemos ninguna información ahora mismo sobre un naufragio en Martinica en ese momento. Y una fragata no es un cúter. Su destrucción seguramente habría atraído cierta atención y creado una gran oportunidad de salvamento para los carroñeros locales.";
		link.l1 = "¿Valdrá la pena buscar en la costa y las playas para encontrar lo que queda del barco?";
		link.l1.go = "guardoftruth_19";
		break;

	case "guardoftruth_19":
		dialog.text = "Hijo mío, Don Diego de Montoya ya ha hecho todo esto sin resultado. Sigue escuchando. Mis fuentes en Providence informan que el Barón está seguro de que el Santa Quiteria todavía navega por el Caribe, aunque bajo un nombre diferente.\nPor eso está cazando a Miguel Dichoso tan desesperadamente. Según sus palabras, el Santa Quiteria fue visto no lejos de Isla Tesoro y recientemente se le ha visto bajo la bandera inglesa escoltado por un escuadrón militar.";
		link.l1 = "¿Qué? Esto es increíble. Dijeron que resistir una tormenta de tal magnitud sería imposible... ¿Y ahora la Santa Quiteria no solo sobrevivió, sino que ahora navega bajo la bandera inglesa? Los dos hechos no cuadran. ¿Qué hizo al Barón decidir que era la Santa Quiteria? ¿Es realmente un barco tan único?";
		link.l1.go = "guardoftruth_20";
		break;

	case "guardoftruth_20":
		dialog.text = "Ah sí. Esta fragata fue construida usando las técnicas más recientes de Europa. Está muy bien armada para su clase, y su velocidad le permite superar a cualquier cosa que pueda superarla en fuego. Eso es lo que me dijo mi fuente.";
		link.l1 = "¿Y acaso ahora no se llama Santa Quiteria?";
		link.l1.go = "guardoftruth_21";
		break;

	case "guardoftruth_21":
		dialog.text = "Eso, desafortunadamente, no lo sé... Ve a Isla Tesoro, " + pchar.name + ", y trata de averiguar algo sobre la fragata de Dichoso. Podríamos lograr encontrar a su antiguo capitán de esa manera también, dos pájaros de un tiro. O dos ratas con una trampa.";
		link.l1 = "¡Considérelo hecho, Su Excelencia!";
		link.l1.go = "guardoftruth_22";
		break;

	case "guardoftruth_22":
		DialogExit();
		AddQuestRecord("Guardoftruth", "59");
		// проверяем, жив ли Акула и где он, если жив
		if (GetCharacterIndex("Dodson") != -1)
		{
			sld = characterFromId("Dodson");
			if (sld.location == "Pirates_townhall")
				pchar.questTemp.Guardoftruth.Archy = "islatesoro";
			else
				pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
		}
		else
			pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
		SetTimerCondition("Map_SetNationCoolHanters", 0, 0, 5, false); // немного развлечений
		break;

	case "tieyasal":
		dialog.text = "Me alegra que hayas decidido verme, hijo mío.";
		link.l1 = "Hola, Su Excelencia. Después de reunirme con Don Alonso de Maldonado, ni siquiera pensé que volvería a verle.";
		link.l1.go = "tieyasal_1";
		break;

	case "tieyasal_1":
		dialog.text = "Don Alonso de Maldonado rompió mis órdenes directas. Le había prohibido estrictamente que te confrontara, hijo mío, sabía cómo terminaría para él. Y lo que preví se ha cumplido. Su misión era escoltarte a Tayasal, ya que había estado allí antes.\nAdemás de eso, su escuadrón y una compañía de soldados españoles debían defenderte contra el ataque de Itza o Mosquito. Alonso actuó indignamente, impulsado por un deseo egoísta de venganza.\nNo solo fracasó en la expedición a Tayasal y condenó a los soldados y barcos que se le confiaron, sino que también plantó las semillas de la desconfianza y el resentimiento contra mí en tu corazón. Te aseguro, hijo mío, estoy completamente de tu lado. Debemos unirnos contra esta oscuridad presente.";
		link.l1 = "Me gustaría creer eso.";
		link.l1.go = "tieyasal_2";
		break;

	case "tieyasal_2":
		dialog.text = "Ten por seguro, " + pchar.name + "Yo, un leal y dedicado servidor de nuestro Señor y Salvador Jesucristo y representante de su Iglesia, estoy motivado por una cosa: detener el fin del mundo hasta que todas las almas hayan tenido la oportunidad de escuchar la palabra de Nuestro Bendito Señor. Y eso significa detener el agente diabólico que actualmente descansa en las manos de un indio poseído por demonios. Sospechaba esto desde el principio y solo ahora estoy completamente seguro. Has sido elegido por el Señor como Su campeón en la batalla contra Satanás.";
		link.l1 = "¿Pero qué te hace decir eso, Padre?";
		link.l1.go = "tieyasal_3";
		break;

	case "tieyasal_3":
		dialog.text = "Has logrado hacer algo que ni yo con la ayuda de todos mis agentes, ni el Barón Mendosa ni Don Diego, ni nadie más ha podido hacer. Has logrado encontrar la maldita isla y buscar el artefacto de Kukulcán en ella. ¿No es así?";
		link.l1 = "Sí, tengo la máscara de Kukulcán.";
		link.l1.go = "tieyasal_4";
		break;

	case "tieyasal_4":
		dialog.text = "¿Y afirmarías que todo esto ha sucedido por accidente? ¿Por coincidencia? 'El corazón del hombre traza su rumbo, pero el Señor dirige sus pasos.' ¡Hijo mío, el Todopoderoso te ha guiado por este camino! ¡Ha fortalecido tu mano en la batalla, dirigido tus pies por el camino correcto y te ha protegido en tiempos de peligro! '¡He aquí, la espada del Señor desciende para juicio sobre Edom, sobre el pueblo que he destinado a la destrucción!'";
		link.l1 = "Ejem... Padre, pero la misión básicamente ya se ha cumplido. Tengo la máscara. ¿No significa eso que la concha poseída de Kukulcán no puede entrar en nuestra historia y cambiarla...?";
		link.l1.go = "tieyasal_5";
		break;

	case "tieyasal_5":
		dialog.text = "Te equivocas, hijo mío. El demonio puede cruzar por ese portal sin importar si tiene esta máscara o no. La máscara solo le facilita llevar a cabo sus oscuros actos. Lo único que puede detenerlo es la destrucción completa de las puertas infernales.";
		link.l1 = "Don Alonso me dijo lo mismo...";
		link.l1.go = "tieyasal_6";
		break;

	case "tieyasal_6":
		dialog.text = "¡Y tenía razón! En el nombre de nuestro Señor Jesucristo y su Bendita Madre, te llamo a tomar la Cruz contra este mal, hijo mío. No puedes rechazar la gran misión que se te ha encomendado. Yo y toda la cristiandad dependemos de ti, hijo mío.";
		link.l1 = "Su Excelencia, esto es demasiado. Realmente me siento... un poco incómodo...";
		link.l1.go = "tieyasal_7";
		break;

	case "tieyasal_7":
		dialog.text = "Tu modestia es halagadora, hijo mío, pero este no es momento para hacerte el virginal rubor. No seas pusilánime ni tengas miedo, porque el Señor tu Dios va delante de ti para darte la victoria. ¡Entra en esta batalla por tus seres queridos, por todos los cristianos... y si no es por ellos, hazlo por ti mismo, porque si ese demonio sale victorioso, perecerás junto con todos los demás!";
		link.l1 = "Supongo que me has convencido, Padre. Había dudado sobre mi situación para emprender una cruzada en Tayasal, pero ahora ya no tengo dudas. ¿Con qué puedes ayudarme?";
		link.l1.go = "tieyasal_8";
		break;

	case "tieyasal_8":
		dialog.text = "Solo dos hombres sabían cómo llegar a Tayasal: Alonso de Maldonado y Miguel Dichoso. Don Alonso está muerto. Y Dichoso... Me dijeron que fue visto recientemente en Sharptown en Isla Tesoro. Quizás todavía esté allí. Debes encontrar a Dichoso y persuadirlo para que sea tu guía.\nA través de oro o fuerza, debes hacer que este hombre te lleve a Tayasal. Allí encontrarás las puertas del infierno, y allí las sellarás.";
		link.l1 = "¿Y qué pasa con los hombres?";
		link.l1.go = "tieyasal_9";
		break;

	case "tieyasal_9":
		dialog.text = "La última compañía de soldados que tuve estaba bajo el mando de Alonso de Maldonado. Ay, no tengo la oportunidad de reunir otra tropa de soldados españoles. He gastado todo mi prestigio con la guarnición. Tendrás que hacerlo con la ayuda de tus propios hombres, hijo mío. Pero te daré la ayuda que pueda con cualquier otra cosa.";
		link.l1 = "¿Qué tipo de ayuda?";
		link.l1.go = "tieyasal_10";
		break;

	case "tieyasal_10":
		dialog.text = "Debemos aprovechar todas las ventajas que tengamos en esta lucha, tanto materiales como espirituales. He solicitado que el Padre Adrián se una a mí aquí en esta capilla dentro de cinco días. Él traerá consigo amuletos sagrados para ti. Amuletos que pueden ayudar a los guerreros de Cristo en la batalla. También te proporcionará todo tipo de pociones. En cuanto a mí, acepta esta espada, hijo mío.\nEsta es una antigua espada de los Caballeros Templarios, un arma formidable de nuestros antepasados. Todavía afilada y resplandeciente con la bendición de la Iglesia. Solo los más grandes caballeros han tenido el honor de empuñarla. Tómala, poseela con orgullo, y aplasta a los enemigos de nuestra Fe con el nombre de Jesucristo en tus labios!";
		link.l1 = "¡Gracias! Esta espada es absolutamente increíble. Estoy sin palabras...";
		link.l1.go = "tieyasal_11";
		break;

	case "tieyasal_11":
		sTemp = GetBestGeneratedItem("blade_32");
		GiveItem2Character(pchar, sTemp);
		sld = ItemsFromID(sTemp);
		sld.Balance = 2.0;
		sld.Weight = 4.5;
		Log_Info("Has recibido el Tanath");
		PlaySound("interface\important_item.wav");
		dialog.text = "Dios te bendiga, " + GetFullName(pchar) + ", en esta batalla que se avecina. Te invisto con la Santa Cruz. Dios todopoderoso, en cuya mano descansa la victoria y que también dio a David fuerzas milagrosas para aplastar a Goliat: humildemente te rogamos que bendigas estas armas con tu misericordia vivificante; y concede a tu siervo " + GetFullName(pchar) + " que quiera llevarlos, para que los utilice libre y victoriosamente en la defensa de la Santa Madre Iglesia contra los ataques de todos los enemigos visibles e invisibles. Por Cristo nuestro Señor. Amén.";
		link.l1 = "¡Amén!";
		link.l1.go = "tieyasal_12";
		break;

	case "tieyasal_12":
		dialog.text = "Y ahora vete, hijo mío. Que Dios te cuide, que nunca te abandone, ni en tu búsqueda, ni en tu camino, ni en la batalla. Busca a Miguel Dichoso y dirígete a Tayasal con su ayuda. No te olvides del Padre Adrián, él te proveerá de cualquier amuleto y remedio que necesites. Y ahora es hora de que yo regrese a Santiago. Adiós, hijo mío. Vaya con Dios.";
		link.l1 = "Adiós, Padre Vincento...";
		link.l1.go = "tieyasal_13";
		break;

	case "tieyasal_13":
		DialogExit();
		NextDiag.CurrentNode = "first time";
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Tieyasal_VinsentoGo", -1);
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
