// диалоги персонажей по квесту Дороже золота
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
			dialog.text = "¿Qué quieres?";
			link.l1 = "Debería irme...";
			link.l1.go = "exit";
		break;
		
		// вестовой в Сен Пьере
		case "fraofficer":
			dialog.text = "¡Capitán Charles de Maure! ¡Al fin! ¡Su Excelencia Jacques Dille do Parkuet exige verte! ¡Esto es urgente!";
			link.l1 = "¿Por qué no me sorprende? Muy bien, por favor dígale a Su Excelencia que llegaré pronto.";
			link.l1.go = "fraofficer_1";
		break;
		
		case "fraofficer_1":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", true);//закрыть выходы из города
			LAi_LocationDisableOfficersGen("FortFrance_townhall", true);//офицеров не пускать
			pchar.questTemp.GoldenGirl = "message";
			AddQuestRecord("GoldenGirl", "1");
		break;
		
		// маркиза Джулиана Бото
		case "Julianna":
			dialog.text = "¡Mis ojos deben estar engañándome si es el mismo Charles de Maure! No hago tales recepciones muy a menudo y estoy encantado de que hayas logrado encontrar algo de tiempo para mi humilde claustro. ¡Qué suerte la mía! ¡Esto merece un brindis!";
			link.l1 = "Mis respetos, señora. Perdóneme si mi manera de ser le resulta algo decepcionante; hace mucho, mucho tiempo que no asistía a este tipo de... eventos. El protocolo en un barco se reduce a la subordinación, pañuelos limpios y una taza regular de café refrescante cada mañana.";
			link.l1.go = "Julianna_1";
		break;
		
		case "Julianna_1":
			dialog.text = "Tan encantador, Capitán, todavía llevas contigo tu brillo parisino. Puedo ver su mirada tímida bajo esa máscara curtida y salada. No te preocupes, estoy tan contento de finalmente conocerte que puedo perdonarte muchas cosas. Por ahora. Veremos cómo nos va en el futuro. ¿Vino? ¿Tinto o blanco?";
			link.l1 = "Un momento perfecto para un chiste de ron, pero, ay, no estoy de humor, lo siento. Con gusto beberé cualquier cosa que tus bonitas manos me sirvan.";
			link.l1.go = "Julianna_2";
		break;
		
		case "Julianna_2":
			dialog.text = "Buena esa. Pero insisto. El gusto por el vino puede decir mucho sobre un hombre y tengo la intención de aprender todo sobre ti esta noche. Así que pregunto nuevamente: ¿tinto o blanco?";
			link.l1 = "Tenga a su manera. Veo que está bebiendo tinto. Lo mismo para mí - me gustaría aprender algo sobre usted también.";
			link.l1.go = "Julianna_3";
			link.l2 = "En ese caso, tomaré blanco pero tú elige. Esto debería funcionar en ambos sentidos, ¿no estás de acuerdo?";
			link.l2.go = "Julianna_4";
		break;
		
		case "Julianna_3":
			pchar.questTemp.GoldenGirl.Vine = "red";
			dialog.text = "Espléndido, ¿entonces es mi turno ahora? Este es un Pinot Noir de Borgoña, los vinicultores lo llaman 'una chica traviesa'. No es una variedad fácil de manejar y su regusto también puede ser bastante engañoso. ¿Satisfecho?";
			link.l1 = "¿Pinot Noir, eh? Me vale. Poco fiable y misterioso, un sabor desalentador al principio, pero déjalo respirar un rato y te sorprenderás. Un baile ligero de matices y sabores, una elección de un conocedor experimentado. Las primeras impresiones engañan, ¿verdad? ¡Bebo por tus ojos, señora!";
			link.l1.go = "Julianna_5";
		break;
		
		case "Julianna_4":
			pchar.questTemp.GoldenGirl.Vine = "white";
			dialog.text = "Espléndido, ¿entonces es mi turno ahora? Tengo un maravilloso Sauvignon Blanc, directamente del valle del Loira. Bastante salvaje, casi puedes sentir cómo estalla en tu lengua. Y la guinda del pastel: una nota de pólvora. Supongo que compartes algo en común.";
			link.l1 = "Esperaba algo mejor, tal vez algo como un Riesling. Bueno, tomemos a este bruto simple que huele a verano y pólvora. ¿Alguna vez has oído que algunos lo confunden con pipí de gato? Beberé por tu sonrisa, tan brillante como estos zafiros.";
			link.l1.go = "Julianna_5";
		break;
		
		case "Julianna_5":
			dialog.text = "¡Notable, Charles! ¿Puedo llamarte así? No me equivoqué contigo, en otro día serías la estrella de mi noche. Pero, ay, mi Capitán, hoy tienes una fuerte competencia. Parece que estamos al borde de un escándalo por allá, ¿lo ves?";
			link.l1 = "Estoy oyendo voces airadas. ¿Quién es este desagradable monsieur y qué hizo para disgustar a nuestro queridísimo gobernador?";
			link.l1.go = "Julianna_6";
		break;
		
		case "Julianna_6":
			dialog.text = "Este 'desagradable' señor es Angerran de Chievous, un bastardo no reconocido del Conde de Levi Vantadur. Estás entreteniendo su tema de discusión. De Chievous ha estado tratando de ganarse mi favor durante años, y me siguió aquí, pensando que puede reemplazar a su padre para mí. Aunque no es un hijo legítimo, es rico y poderoso. La terquedad es otra de sus características, para algunas personas reemplaza la sabiduría. Justo antes de tu llegada, él y Jacques comenzaron a discutir sobre el tema obvio. ¡Su Excelencia siempre me protege de una manera muy conmovedora, deberías ver! Vamos, observemos y veamos cómo termina esta vez.";
			link.l1 = "Huelo problemas en el aire... ¿Por qué siempre hay una trampa, incluso en una noche tan maravillosa...?";
			link.l1.go = "Julianna_7";
		break;
		
		case "Julianna_7":
			dialog.text = "¿Perdón, Charles?";
			link.l1 = "Olvídalo. Por favor, preséntame a tu amigo entrometido, luego veremos...";
			link.l1.go = "Julianna_8";
		break;
		
		case "Julianna_8":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "quest", "quest1", "GoldenGirl_PartyTalk", -1);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
		break;
		
		case "Julianna_9":
			dialog.text = "Monsieur, permítame presentarle a mi querido invitado: ¡el Capitán Charles de Maure, en carne y hueso, nos ha honrado con su visita! No es frecuente que figuras tan famosas nos visiten aquí.";
			link.l1 = "... ";
			link.l1.go = "Julianna_10";
		break;
		
		case "Julianna_10":
			DialogExit();
			sld = characterFromId("FortFrance_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "Julianna_11":
			dialog.text = "¡Charles, no me gusta hacia dónde va esto! Jacques es sordo a mis argumentos mientras Angerran seguramente trama algo. ¡Esta pelea tenía un propósito y necesito tu ayuda!";
			link.l1 = "Me temo que no te entiendo... ¿Qué puedo hacer aquí? Ya se negó a batirse en duelo conmigo...";
			link.l1.go = "Julianna_12";
		break;
		
		case "Julianna_12":
			dialog.text = "Capitán, por favor, no me decepcione. Hace un momento era usted un virtuoso de las conversaciones, y ahora su mundo se divide entre cosas que puede pinchar con una espada y cosas que no puede. ¡Piense fuera de la caja! Arruinemos la obra de Angerran. Quiere desafiar al pobre Jacques por su cuenta, ¡pero eso es simplemente aburrido! ¡Hagamos un torneo! Varios caballeros aquí pueden respaldar apuestas serias y su suerte ya es conocida como legendaria. ¿Quizás las cartas la favorecerán esta noche?";
			link.l1 = "No veo del todo cómo evitará que de Chievous luche contra nuestro dulce gobernador, pero estoy dentro, mi señora. Cualquier cosa para borrar esa pequeña sonrisa suya.";
			link.l1.go = "Julianna_13";
		break;
		
		case "Julianna_13":
			dialog.text = "Espléndido, ahora ve a la mesa y come algo, será una noche larga. Una vez que estés listo, encuéntrame en el salón, necesitaremos más espacio para esto. Mientras tanto, montaré un espectáculo, persuadiendo a otros para que me den espectáculos y juegos de altas apuestas. Incluso podría gritarles para que estos gallos noten a una dama ahogándose en el aburrimiento. Por favor, no interfieras, nadie debe saber que estamos en el mismo equipo esta noche. ¡Nos vemos más tarde, mi Capitán!";
			link.l1 = "Lo que digáis, madame, lo que digáis...";
			link.l1.go = "Julianna_14";
		break;
		
		case "Julianna_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "barmen", "stay", "GoldenGirl_JulianaPause", -1);
			AddQuestRecord("GoldenGirl", "4");
		break;
		
		case "Julianna_15":
			dialog.text = "¡Bueno, felicítame, funcionó! Un poco de orgullo, algo de prejuicio y ¡voilá! Haz una cara aburrida, nos están observando. Que piensen que estás interesado en beber, no en mí\nEstá a punto de comenzar un torneo, las apuestas son altas, sin segundas oportunidades ni revanchas. De alguna manera sé que estás acostumbrado a esto. Lo manejarás. Recuerda, Angerran definitivamente está tramando algo, hará un movimiento contra nuestro amigo Jacques, pero no consideró tu llegada. Sé mi as bajo la manga, porque ver su cara de autosuficiencia nunca es una buena señal. Tenemos ocho jugadores, pero me aseguré de que no te enfrentaras a él hasta la final\n¡Oh! ¡Tu primer oponente! Coronel y Comandante de nuestro fuerte. Mar contra tierra, ¡un desafío digno para invitados con experiencia militar! ¡Aplausos!";
			link.l1 = "";
			link.l1.go = "Julianna_16";
		break;
		
		case "Julianna_16":
			DialogExit();
			DoQuestCheckDelay("GoldenGirl_CreateColonel", 0.5);
		break;
		
		case "Julianna_17":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) 
			{
				dialog.text = "Lo hiciste de maravilla, Charles, simplemente espléndido. Angerran y Jacques están a punto de enfrentarse en cualquier momento. Es una pena que no escucharan y pospusieran el torneo por una semana. ¡Podría reunir una fiesta verdaderamente estelar cuyos chismes viajarían hasta París! Bueno, quizás la próxima vez. Parece que tu próximo oponente es un competidor digno de tu suerte, un verdadero lobo de mar, ¡el Capitán Moreno! ¡Capitanes, por favor!";
				link.l1 = "";
			}
			else
			{
				dialog.text = "¡Ay, tu suerte te falló, Capitán! Lo siento, pero el juego ha terminado para ti. Angerran ya está jugando contra Jacques, así que debo irme. Adiós.";
				link.l1 = "Fue un placer... señora.";
			}
			link.l1.go = "Julianna_18";
		break;
		
		case "Julianna_18":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) GoldenGirl_CreateCaptainMoreno();
			else GoldenGirl_CardsFail();
		break;
		
		case "Julianna_19":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) 
			{
				dialog.text = "¡Te felicito por tu merecida victoria, Capitán! Aún no está claro quién te enfrentará en nuestra final... Vamos a apartarnos un poco. Baja la voz y observa esa mesa. ¡Mira, ahí va! ¡Estoy empezando a ver lo que Angerran trama! Ya dejó sin dinero al dulce Jacques, pero no lo deja levantarse de la mesa. Cuando pasé, el pobre diablo apostaba unos documentos por todo un barco con carga. Lamentablemente, la suerte no está de su lado esta noche. O alguien le dijo que no lo estuviera.";
				link.l1 = "¿Crees que de Chievous está haciendo trampa?";
				link.l1.go = "Julianna_21";
			}
			else
			{
				dialog.text = "Por desgracia, vuestra suerte os ha fallado, Capitán. Lo siento, pero el juego ha terminado para vos. Angerran ya está jugando contra Jacques, así que debo irme. Adiós.";
				link.l1 = "Fue un placer... señora.";
				link.l1.go = "Julianna_20";
			}
		break;
		
		case "Julianna_20":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			GoldenGirl_CardsFail();
		break;
		
		case "Julianna_21":
			dialog.text = "Definitivamente podría si quisiera, pero no tengo pruebas. Nuestro querido gobernador es bueno con las cartas, pero su oponente también lo es. Angerran ni siquiera parpadeó cuando apostó su fragata, imagina eso. Si tuviéramos este duelo en París o en Lyon, se convertiría en leyenda, ¡Carlos! Sin embargo, podría estar teniendo suerte esta noche. Acerquémonos a ellos y veamos por nosotros mismos.";
			link.l1 = "...";
			link.l1.go = "Julianna_22";
		break;
		
		case "Julianna_22":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(pchar, "quest", "quest3", "GoldenGirl_Talking", -1); 
			LAi_ActorFollow(npchar, pchar, "", 10.0);
		break;
		
		case "Julianna_23":
			dialog.text = "Charles, sostenme o caeré... O no lo haré - estos idiotas ni siquiera notarán que me desmayo. ¿Viste esto? Jacques, ¡maldita sea tu estupidez! ¡Como un niño, Jesús! ¡Un niño imbécil!";
			link.l1 = "Marquesa, no creo que te siga.  ¿Qué está pasando en esa mesa ahora? ¿En qué están apostando?";
			link.l1.go = "Julianna_24";
		break;
		
		case "Julianna_24":
			dialog.text = "Sobre mí, Charles. Nuestro dulce y tonto Jacques apostó por mí. Angerran encontró su único punto débil y lo atacó en el momento justo.";
			link.l1 = "¡Maldita sea! Pero soy el siguiente en el torneo, ¡podría ganar su maldito barco de vuelta apostando! ¿Por qué?";
			link.l1.go = "Julianna_25";
		break;
		
		case "Julianna_25":
			dialog.text = "Porque Angerran lo había pensado muy bien y planeado todo. Escúchame, no tenemos mucho tiempo. Tienes que hacerle lo mismo a él. ¡Desnúdalo de todo, quítale todo su dinero, todos sus barcos, provócalo! ¡Haz que pierda la cabeza por la reputación, el honor, la pasión, por cualquier cosa! Has visto cómo se hace esta noche. Acorrálalo y oblígalo a hacer una apuesta. ¡Te lo suplico, Charles! Estoy dispuesto a todo, pero no voy a ir a él. ¡No así! Ni siquiera el Conde Vantadur se enfrentará a una victoria legítima en las cartas, ni siquiera moverá un dedo para ayudarme. Mira, las cartas son jodidamente sagradas para la nobleza, ¡malditos sean! Eres mi última y única esperanza, ¡Charles!";
			link.l1 = "No entierre a nuestro gobernador todavía, señora. ¿Tal vez recupere su barco? La Dama Fortuna es una... mujer caprichosa.";
			link.l1.go = "Julianna_26";
		break;
		
		case "Julianna_26":
			dialog.text = "Aún no lo entiendes, ¿verdad? ¡La suerte no tiene lugar en esa mesa! Angerran de Chievous toma todas las decisiones. Descubrió una manera de tenerme y mantener a su padre alejado de esto. No tengo idea de cuánto tiempo lleva planeándolo, pero casi ha ganado ya. Él domina el juego y solo tenemos una oportunidad para romperlo. ¡Aquí, toma esto! Voy a hacerme el desmayado, te daré un minuto o dos. Úsalo sabiamente.";
			link.l1 = "¡Marquesa... Alguien, por favor, ayude! ¡La señora no se siente bien! ¡Rápido!";
			link.l1.go = "Julianna_27";
		break;
		
		case "Julianna_27":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_5";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			GiveItem2Character(pchar, "obereg_5");
			GiveItem2Character(pchar, "totem_13");
			Log_Info("Has recibido el amuleto 'Tortuga'.");
			Log_Info("Has recibido el amuleto 'Joker'.");
			PlaySound("interface\important_item.wav");
		break;
		
		case "Julianna_28":
			dialog.text = "No, no estoy bien... Hace un poco de bochorno aquí... Lo siento mucho, caballeros. Los dejaré un momento para tomar aire fresco. Pueden continuar sin mí.";
			link.l1 = "...";
			link.l1.go = "Julianna_29";
		break;
		
		case "Julianna_29":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto1", "", 10.0); // уходит
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = characterFromId("FortFrance_Mayor");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
		break;
		
		case "Julianna_30":
			dialog.text = "No en este momento y no en Saint-Pierre, pero conozco a alguien. Te prometo, Angerran, que esta será una pintura digna...";
			link.l1 = "...";
			link.l1.go = "Julianna_31";
		break;
		
		case "Julianna_31":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_21";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_32":
			dialog.text = "¡Angerran, eres imposible! ¡Aprende a perder! Esto es solo un juego y no puedes predecirlo todo. Termina tu vino y vístete: las reglas siguen siendo las mismas: un derrotado abandona nuestra cómoda fiesta.";
			link.l1 = "Marquesa, espera...";
			link.l1.go = "Julianna_33";
		break;
		
		case "Julianna_33":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_24";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_34":
			dialog.text = "¡Esto está yendo demasiado lejos, caballeros! ¡Deténganse de inmediato! Todos estamos muy cansados después de la noche agotadora y me temo que tengo que pedir a mis invitados que se despidan. Pueden continuar su discusión mañana como corresponde a hombres de honor, a menos que cambien de opinión. Pero nadie va a tocar armas aquí, ¿está claro?";
			link.l1 = "...";
			link.l1.go = "Julianna_35";
		break;
		
		case "Julianna_35":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_36":
			dialog.text = "Charles, me temo que también tendré que pedirte que te retires. Sube las escaleras y busca una habitación para ti. Arreglaré todo. Estoy agradecido por todo lo que has hecho por mí más allá de cualquier medida, pero necesito algo de tiempo para mí mismo y debes estar terriblemente cansado.";
			link.l1 = "No está tan mal, señora, pero no le diré que no a una cama. Esta fiesta casual me golpeó más fuerte que una enorme escuadra naval enemiga. Entiendo que todo esto tampoco fue fácil para usted, marquesa. Descanse un poco y no se preocupe, no me debe nada. Todo lo que necesito ahora es dormir.";
			link.l1.go = "Julianna_37";
		break;
		
		case "Julianna_37":
			dialog.text = "Me aseguraré de que te despierten al mediodía. Ya es el amanecer, así que ya no puedo desearte buenas noches. Que duermas bien.";
			link.l1 = "Tú también, marquesa.";
			link.l1.go = "Julianna_38";
		break;
		
		case "Julianna_38":
			DialogExit();
			GoldenGirl_SleepInBrothel();
		break;
		
		case "Julianna_39":
			dialog.text = "Ahí estás, Charles. Para ser honesto, no dormí nada, pero tú pareces bien descansado. ¿Cómo dormiste? El desayuno está en camino.";
			link.l1 = "La hospitalidad de usted es legendaria, señora, pero me temo que no tengo tiempo para disfrutarla. Su Excelencia, los segundos de de Chievous, los barcos que gané - todo ello, me está esperando.";
			link.l1.go = "Julianna_40";
		break;
		
		case "Julianna_40":
			dialog.text = "Tú no solo ganaste los barcos. Esta es otra cosa de la que quería hablar contigo, Charles...";
			link.l1 = "No soy ni Jacques ni Angerran, marquesa. No juego con mujeres para ganar su favor. No me debes nada.";
			link.l1.go = "Julianna_41";
			link.l2 = "Eres de mi protección, marquesa. Ni Jacques ni Angerran te molestarán jamás, puedo prometerte eso.";
			link.l2.go = "Julianna_42";
		break;
		
		case "Julianna_41":
			pchar.questTemp.GoldenGirl.J1 = "true";
			dialog.text = "Eres o fabulosamente honorable o estás enamorado, Charles. Y no de mí. Pero de nuevo, te estoy eternamente agradecida con todo mi corazón. Si puedo ser de alguna ayuda para ti, solo dímelo.";
			link.l1 = "Julianne, el tiempo se acaba y me enfrento a la tarea más difícil por delante. De Chievous es un granuja y hasta un duelo honesto puede terminar rápidamente como el que observamos anoche. Hablemos más tarde cuando todo esto haya terminado de una vez por todas. Te agradezco por la oportunidad de dormir en silencio y espero verte de nuevo.";
			link.l1.go = "Julianna_43";
		break;
		
		case "Julianna_42":
			pchar.questTemp.GoldenGirl.J2 = "true";
			dialog.text = "Te estoy agradecida con todo mi corazón, Charles... Créeme, ser tu premio es una especie de victoria para mí también. ¿Qué te parece si continuamos esta conversación en un entorno más... privado?";
			link.l1 = "Julianne, el tiempo se acaba y me enfrento a la tarea más incómoda por delante. De Chievous es un bribón y hasta un duelo honesto puede terminar rápidamente como el que observamos anoche. Hablemos más tarde cuando todo esto haya terminado para bien. Te agradezco por darme la oportunidad de dormir en silencio y espero verte de nuevo.";
			link.l1.go = "Julianna_43";
		break;
		
		case "Julianna_43":
			dialog.text = "No te retrasaré más entonces, mi Capitán. Recuerda, sin embargo, que Angerran es peligroso. No puedo juzgar sus capacidades de combate, pero participó en varias guerras y luchó en Rocroi. También escuché sobre un par de duelos que ganó, principalmente con pistolas. Sobre todo, es un tipo engañoso como tú mismo notaste. ¡Te ruego que tengas cuidado y por favor ven a verme después!";
			link.l1 = "El cuidado te sienta de maravilla, marquesa. Créeme, de Chievous no es el primer bastardo que se interpone en mi camino. Me las arreglaré. Ahora realmente debería ir a ver a Su Excelencia y discutir el asunto del duelo.";
			link.l1.go = "Julianna_44";
		break;
		
		case "Julianna_44":
			dialog.text = "¡Buen viento, mi Capitán! Y dile a Jacques que se mantenga lo más lejos posible de las puertas de mi hogar.";
			link.l1 = "Tienes mi palabra. ¡Hasta luego, marquesa!";
			link.l1.go = "Julianna_45";
		break;
		
		case "Julianna_45":
			DialogExit();
			GoldenGirl_ToGovernor();
		break;
		
		case "Julianna_46":
			dialog.text = "¡Capitán, lo lograste, qué alivio! ¿Cómo te fue? ¡¿Estás sangrando?!";
			link.l1 = "No es mi sangre... al menos no toda. Marquise, ¿dónde está de Chievous?";
			link.l1.go = "Julianna_47";
		break;
		
		case "Julianna_47":
			dialog.text = "Estaba a punto de preguntarte lo mismo, ¿no lo derribaste? ¿Qué pasó? ¿Por qué veo a la mitad de los guardias del pueblo afuera?";
			link.l1 = "Dije al gobernador que podrías estar en peligro. De Chievous resultó herido y huyó, desató a sus matones sobre nosotros. Fue una masacre. Aunque, historias como esta no son para tus bellos oídos. Se acabó. Estás libre de él y de nuestro 'dulce' Jacques.";
			link.l1.go = "Julianna_48";
		break;
		
		case "Julianna_48":
			dialog.text = "Esto es tan malo, Charles. Enemigos como Angerran de Chievous deben ser eliminados para siempre cuando tienes la oportunidad. Conocí al hombre durante muchos años, no es del tipo que perdona. Tarde o temprano, encontrará la manera de vengarse. Pero no me gusta cómo te encorvas, ¿te atendieron la herida?";
			link.l1 = "Solo un rasguño, ha sido mucho peor. Duele un poco, eso es todo. Gracias por preocuparse por mí, señora, pero debo irme...";
			link.l1.go = "Julianna_49";
		break;
		
		case "Julianna_49":
			dialog.text = "Capitán, apostaste por mí, arriesgando tus barcos y riquezas, luchaste por mí en un trato, arriesgando tu vida y carrera. Lo mínimo que podría hacer por ti es cuidar tus heridas y darte un lugar para descansar con seguridad. ¡No! No quiero escuchar más de esto. Toma mi mano y sígueme arriba. Tu habitación te está esperando.";
			link.l1 = "Estoy aceptando su oferta, señora, gracias. Pero preferiría no cargarle con mi peso. Subiré yo mismo.";
			link.l1.go = "Julianna_50";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.J2") && pchar.questTemp.GoldenGirl.Vine == "red")
			{
				link.l2 = "Marquesa, eres mi ángel guardián. Me temo que soy yo quien te debe ahora.";
				link.l2.go = "Julianna_52";
			}
		break;
		
		case "Julianna_50":
			dialog.text = "¡Carlos, eres un ejemplo de caballerosidad! ¡Juro por Dios, si sigues así, perderé la cabeza! Muy bien, mi caballero, enviaré a Denise contigo, ella cuidará de tus heridas como cualquier médico competente lo haría.";
			link.l1 = "Gracias, marquesa. Si mi corazón no estuviera ya ocupado, con gusto seguiría el juego. ¡Pero ay! ¡Buenas noches!";
			link.l1.go = "Julianna_51";
		break;
		
		case "Julianna_51":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_Brothel_room", "goto", "goto1", "GoldenGirl_WithoutJulianna"); // найти нужные локаторы
		break;
		
		case "Julianna_52":
			dialog.text = "En este caso, exijo que me complazcas de inmediato. Tómame de la mano y haz lo que digo. ¡Denise! ¡Trae lino, vino caliente y algo de comer arriba! Vamos, mi Capitán. Y recuerda - esta vez no hay discusiones!";
			link.l1 = "Como usted diga, marquesa, soy todo suyo.";
			link.l1.go = "Julianna_53";
		break;
		
		case "Julianna_53":
			DialogExit();
			pchar.questTemp.GoldenGirl.JulianaSex = "true";
			DoQuestReloadToLocation("FortFrance_Brothel_room", "goto", "goto1", "GoldenGirl_KissJulianna");
			sld = characterFromId("Julianna");
			ChangeCharacterAddressGroup(sld, "FortFrance_Brothel_room", "goto", "goto2");
		break;
		
		case "Julianna_54":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Buenos días, Charles. ¿Cómo están esos 'rasguños' tuyos?";
				link.l1 = "Gracias a tus esfuerzos me siento renacido. Por favor acepta mi más sincera gratitud, Julianna.";
				link.l1.go = "Julianna_56";
			}
			else
			{
				dialog.text = "Buenos días, mi héroe. ¿Cómo están esos 'rasguños' tuyos?";
				link.l1 = "Gracias por su preocupación, señora, estoy totalmente bien. Pagaría una fortuna para que su Denise sirviera como médico de mi barco. ¡Es un milagro!";
				link.l1.go = "Julianna_55";
			}
		break;
		
		case "Julianna_55":
			dialog.text = "Temo que no será fácil de arreglar. Pero nunca me atrevería a despertarte sin una razón seria. Créeme, cuidé tu sueño sin miedo, pero este hombre abajo es muy persistente. Dice que es uno de tu tripulación y que esto es urgente.";
			link.l1 = "¿Mi tripulación? ¡Hiciste bien en despertarme, marquesa! Me pondré en camino de inmediato.";
			link.l1.go = "Julianna_57";
		break;
		
		case "Julianna_56":
			dialog.text = "En diferentes circunstancias lo haría, mi capitán, pero tendremos que posponerlo. Te espera un monsieur extremadamente inculto abajo. Dice que es uno de tu tripulación y que es urgente.";
			link.l1 = "Volveremos a ello, Madame, cuando regrese. Espero que esto no sea sobre los españoles sitiando de nuevo.";
			link.l1.go = "Julianna_57";
		break;
		
		case "Julianna_57":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_town", "reload", "reload9_back", "GoldenGirl_BadNews");
		break;
		
		case "Julianna_58":
			dialog.text = "¡Charles, has vuelto! ¿Qué noticias trajo tu hombre? ¡Ni siquiera te despediste!";
			link.l1 = "Mis disculpas, marquesa. De Chievous jugó sucio otra vez. Robó mi barco y zarpó esta noche. Uno de mis oficiales de confianza estaba en ese barco y no puedo dejarla en manos de ese bastardo.";
			link.l1.go = "Julianna_59";
		break;
		
		case "Julianna_59":
			dialog.text = "¿Ella? ¿Tienes a una mujer oficial a bordo de tu barco? Esto va en contra de todo lo que sé sobre la navegación. ¿Qué te hace pensar que aún vive?";
			link.l1 = "Espero. Julianna, la esperanza es todo lo que tengo hasta ahora. Debo aprender más sobre Angerran de Chievous. ¡Debo averiguar a dónde fue! ¡Debo traerla de vuelta!";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) link.l1.go = "Julianna_62";
			else link.l1.go = "Julianna_60";
		break;
		
		case "Julianna_60":
			dialog.text = "¡Ahora veo! ¡De verdad estás enamorado, mi caballero! Con gusto daría la mitad de mi vida por tal lealtad y apego sin pensarlo dos veces.";
			link.l1 = "No hice ningún voto, pero esta mujer significa mucho para mí, marquesa.";
			link.l1.go = "Julianna_61";
		break;
		
		case "Julianna_61":
			dialog.text = "Este celo es conmovedor. Escucha esto, Charles, ¡estoy lista para ponerme celosa por ti! Pero ¿qué cortesana puede permanecer sorda a la voz del verdadero amor? Además, me salvaste, mi caballero, por supuesto que te ayudaré. Pregunta lo que quieras.";
			link.l1 = "Gracias. Has conocido a de Chievous durante bastante tiempo. ¿A dónde podría ir después de todo ese alboroto para esperar la ira de su padre?";
			link.l1.go = "Julianna_64";
		break;
		
		case "Julianna_62":
			dialog.text = "¿Y si puedo seducirte con un brunch? No pensaste en esta... chica durante dos días, ¿quizás pueda esperar un día más?";
			link.l1 = "Marquesa, me doy cuenta de cómo puedo parecer a tus ojos, pero lo hecho, hecho está. Aunque no hice ningún voto, mi corazón le pertenece a ella. Te suplico que me entiendas y me ayudes.";
			link.l1.go = "Julianna_63";
		break;
		
		case "Julianna_63":
			dialog.text = "¡Vamos, Charles! ¿Defendiéndote con un discurso de amor ante una cortesana? ¡No me he reído así en mucho tiempo! ¡Eres tan increíble! Tranquilo, lo que pasó en esta casa, se queda en esta casa. Recuerdo lo que te debo. Pregunta lo que quieras.";
			link.l1 = "Gracias. Has conocido a de Chievous desde hace bastante tiempo. ¿A dónde podría ir después de todo ese alboroto para esperar la ira de su padre?";
			link.l1.go = "Julianna_64";
		break;
		
		case "Julianna_64":
			dialog.text = "La verdad sea dicha, aunque invitar a Angerran de Chievous puede no ser lo más placentero, sigue siendo muy útil políticamente. Es un huésped bienvenido en cualquier lugar, incluidas las naciones aliadas con Francia. Pero sólo conozco a un hombre cercano que siempre le tenderá una mano y le ofrecerá un santuario. François de Lyon, el gobernador de nuestra colonia de Guadalupe. Es un viejo asociado del conde de Levi Vantadur y siempre ha tenido una debilidad por este bastardo.";
			link.l1 = "¡Guadalupe, pues! ¡Es la mejor pista que podría atreverme a esperar! Si zarpamos esta noche, estaremos solo un día detrás de ellos.";
			link.l1.go = "Julianna_65";
		break;
		
		case "Julianna_65":
			dialog.text = "Espera, Charles, hay algo más. Recibí una carta para ti hace poco. Supuse que tenía algo que ver con el duelo, pero ya no estoy seguro. Aquí está.";
			link.l1 = "Sin sello, pero el papel es caro. No me gusta esto...";
			link.l1.go = "Julianna_66";
		break;
		
		case "Julianna_66":
			DialogExit();
			AddQuestRecordInfo("GG_Letter_1", "1");
			chrDisableReloadToLocation = true;
			npchar.dialog.currentnode = "Julianna_67";
			LAi_SetStayType(npchar);
		break;
		
		case "Julianna_67":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "¡Vamos, Charles! No me dejes en suspenso, ¿es de él?";
			link.l1 = "Sí, es de él. ¡Ella está viva! La capturó mientras robaba mi barco. Ahora sugiere que nos encontremos y hablemos de esto en un entorno civilizado. Tal como has dicho, Guadalupe, Basse-Terre.";
			link.l1.go = "Julianna_68";
		break;
		
		case "Julianna_68":
			dialog.text = "Monseniour de Lyons definitivamente elegirá al hijo de Leve Vantadur sobre ti. ¡De Chievous podría tenderte una trampa de nuevo! Has hecho un enemigo muy poderoso al defenderme, Charles. Desearía poder ayudarte, pero temo que todo lo que puedo hacer es pedirte que tengas cuidado.";
			link.l1 = "Julianne, nunca habría llegado al Nuevo Mundo si siempre hubiera elegido el enfoque directo. Los negocios turbios no son mi campo más fuerte, pero sé cómo seguir la corriente.";
			link.l1.go = "Julianna_69";
		break;
		
		case "Julianna_69":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
			LAi_SetOwnerType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			chrDisableReloadToLocation = false;
			GoldenGirl_ToBaster();
		break;
		
		case "Julianna_70":
			dialog.text = "¿Alguna noticia, capitán?";
			link.l1 = "¡Ay, nada...";
			link.l1.go = "Julianna_71";
		break;
		
		case "Julianna_71":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
		break;
		
		case "Julianna_72":
			dialog.text = "¡Bienvenido de vuelta, Charles! Me alegra que estés vivo y coleando. ¿Qué novedades?";
			link.l1 = "Todo lo que sabíamos sobre las capacidades de de Chievous resultó ser una grave subestimación. El canalla tiene a mi... oficial cautivo, y solo tengo dos semanas para reunir el rescate. Temo que no pueda suceder sin tu ayuda.";
			link.l1.go = "Julianna_73";
		break;
		
		case "Julianna_73":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Charles, tu amor es como una anémona, sin embargo, te debo mucho y te ayudaré lo mejor que pueda. ¿Cómo puedo servirte?";
			}
			else
			{
				dialog.text = "Charles, ya te dije que nunca olvidaré lo que hiciste por mí. Haré lo que pueda para recompensarte. Estoy listo, sin embargo, no entiendo bien cómo puedo serte útil en esto.";
			}
			link.l1 = "Por favor, siéntate, Julianna. Mira, el rescate de Angerran... eres tú. Y no me refiero a un patrocinio oficial, me refiero a como un cautivo atado en su bodega de carga.";
			link.l1.go = "Julianna_74";
		break;
		
		case "Julianna_74":
			dialog.text = "Estoy sin palabras... Pero tu cara me dice que no es una broma. ¿Perdió la cabeza?";
			link.l1 = "Más bien, cree que lo hice. Está lo suficientemente desesperado como para cruzar todas las líneas posibles.";
			link.l1.go = "Julianna_75";
		break;
		
		case "Julianna_75":
			dialog.text = "¿Y qué, me estás pidiendo a mí? ¿Que no grite durante mi secuestro? Capitán, ¿no crees que esto es un poco demasiado pedir? Te debo mucho, pero salvar el amor de otra persona entregando mi propia vida en manos de un bastardo sin gloria... Tú eres la caballería aquí, mientras que yo soy una mujer extremadamente realista y materialista.";
			link.l1 = "Me temo, señora, que eso es exactamente lo que le estoy pidiendo. Empaque sus cosas, nos vamos. Lamento profundamente esto, pero el tiempo apremia.";
			link.l1.go = "Julianna_76";
			link.l2 = "Marquesa, no secuestro a mujeres que confían en mí. Y esta podría ser nuestra oportunidad.";
			link.l2.go = "Julianna_81";
		break;
		
		case "Julianna_76":
			dialog.text = "Eres todo un caja de sorpresas, Charles. ¿Lo oíste? Esa fue toda la gracia que tenía para ti, se acaba de romper. Amor o no, no permitiré que me secuestres. ¡Guardias! ¡¡¡Ayuda!!! ¡¡¡Alguien!!!!";
			link.l1 = "Y aquí pensé que éramos amigos.";
			link.l1.go = "Julianna_77";
		break;
		
		case "Julianna_77":
			DialogExit();
			LAi_SetActorType(npchar);
			GoldenGirl_PatrolInBrothel();
		break;
		
		case "Julianna_78":
			dialog.text = "¡Esto es un ultraje! ¿En qué has convertido mi salón?! ¿Qué clase de horror demoníaco es este? ¡Charles, vuelve en ti! ¡Eres un noble, no un maldito pirata!!";
			link.l1 = "Ya te he pedido disculpas. Te pedí que no complicaras más las cosas, pero no me escuchaste. Créeme, no me gusta lo que estoy haciendo, pero no tengo otra opción. Haré lo que sea necesario por el bien de esa mujer.";
			link.l1.go = "Julianna_79";
		break;
		
		case "Julianna_79":
			dialog.text = "¿Qué clase de dama elegiría a un caballero tal como tú? ¡Iré yo misma, mantén tus manos alejadas de mí! No estás robando una vaca, ¡así que muestra algo de dignidad!";
			link.l1 = "Bien. Ven conmigo, señora. Quédate detrás de mí y agacha la cabeza - quizás empiecen a disparar.";
			link.l1.go = "Julianna_80";
		break;
		
		case "Julianna_80":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.greeting = "Marquesa_again";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.goldengirl_alarm.win_condition.l1 = "location";
			pchar.quest.goldengirl_alarm.win_condition.l1.location = "FortFrance_Town";
			pchar.quest.goldengirl_alarm.function = "GoldenGirl_AlarmSP";
			pchar.quest.goldengirl_dominica_alarm.win_condition.l1 = "location";
			pchar.quest.goldengirl_dominica_alarm.win_condition.l1.location = "Dominica";
			pchar.quest.goldengirl_dominica_alarm.function = "GoldenGirl_DominicaAlarm";
			ChangeCharacterComplexReputation(pchar, "nobility", -15);
			ChangeCharacterNationReputation(pchar, FRANCE, -50);
			ChangeOfficersLoyality("bad_all", 5);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "14");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			pchar.questTemp.GoldenGirl = "dominica_alarm"; // флаг - силовое решение
			pchar.questTemp.GoldenGirl.Julianna_Prisoner = "true";
		break;
		
		case "Julianna_81":
			dialog.text = "Por un momento pensé que no te conozco en absoluto, Charles. Esa mirada... Pero ¿qué estás a punto de hacer entonces? ¿De qué oportunidad hablaste?";
			link.l1 = "¿Por qué el bastardo me usa para llegar a ti? ¿Por qué orquestó ese juego de cartas en lugar de simplemente tomar lo que quería? ¿De qué tiene miedo?";
			link.l1.go = "Julianna_82";
		break;
		
		case "Julianna_82":
			dialog.text = "Nada. Por desgracia, las razones detrás de todo eso son primitivas y aburridas. El Conde Henri todavía tiene un punto débil por mí. Angerran arriesgaría mucho si me hiciera algo contra mi voluntad. Lo siento, Charles, pero es un callejón sin salida. Él negará todo y se saldrá con la suya. Nadie creerá las palabras de ti, el secuestrador, mientras su padre te destruirá.";
			link.l1 = "¡Maldita sea! Ojalá no hubiera llegado a esto... Prepárate, marquesa, debemos irnos. Y sí, te pido que guardes silencio.";
			link.l1.go = "Julianna_76";
			link.l2 = "Pero el bastardo debe tener otras debilidades además de su padre, ¿verdad? No es perfecto, todo lo contrario, ¡es el opuesto de perfecto!";
			link.l2.go = "Julianna_83";
		break;
		
		case "Julianna_83":
			dialog.text = "No sé si esto será útil para... nosotros. Angerran tuvo algunos tratos con el barón pirata. ¿Jacques Baraban?";
			link.l1 = "Es Barbazon, señora. ¡Linda pareja, los dos! Pero Jacques el Amable no me tiene cariño y no puedo lanzar un asalto a Le François sin una certeza sólida.";
			link.l1.go = "Julianna_84";
		break;
		
		case "Julianna_84":
			if (CheckAttribute(pchar, "questTemp.Portugal.GG1"))
			{
				dialog.text = "Eres demasiado directo otra vez, mi caballero. ¿Recuerdas al capitán Moreno? ¿Tu segundo adversario en el juego? Apuesto a que vino aquí por Angerran. Debe saber algo valioso para nosotros.";
				link.l1 = "¿Capitán Moreno, ¡ja! Sí, por supuesto. ¿Todavía está aquí en la ciudad? ¿Dónde puedo encontrarlo?";
				link.l1.go = "Julianna_85";
			}
			else
			{
				dialog.text = "Estás siendo demasiado directo nuevamente, mi caballero. Siempre hay alguien que sabe algo y no todos pueden mantener la boca cerrada en ciertas situaciones. Mis... pupilos escuchan cosas, en esta casa. Dame un día y aprenderé más o te encontraré a alguien que lo haga.";
				link.l1 = "Marquesa, pensé que la preocupación te sienta bien, pero la ira te sienta aún mejor. ¡Gracias, estás instalando una esperanza en mí!";
				link.l1.go = "Julianna_86";
			}
		break;
		
		case "Julianna_85":
			pchar.questTemp.GoldenGirl.Portugal = "true";
			dialog.text = "Sí, todavía está aquí y te ahorraré correr buscándolo. Ven aquí mañana por la noche: el capitán Moreno te estará esperando aquí, en esta habitación. Ojalá pudiera hacer más que eso, pero no puedo, Charles.";
			link.l1 = "Ya es más que suficiente, marquesa. Con él de mi lado, las cosas serán mucho más fáciles. Gracias. Nos vemos mañana por la noche.";
			link.l1.go = "Julianna_87";
		break;
		
		
		case "Julianna_86":
			pchar.questTemp.GoldenGirl.Portugal = "false";
			dialog.text = "Desearía haber escuchado eso de ti en una situación diferente, Charles. Ven a verme mañana por la noche. Espero poder conseguir lo que necesitas.";
			link.l1 = "¡Gracias de nuevo, Julianna! Entonces, mañana por la noche.";
			link.l1.go = "Julianna_87";
		break;
		
		case "Julianna_87":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
			LAi_SetOwnerType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			SetFunctionTimerCondition("GoldenGirl_JuliannaOneDay", 0, 0, 1, false); // таймер
		break;
		
		case "Julianna_88":
			pchar.quest.GoldenGirl_JuliannaOneDayFail.over = "yes"; //снять прерывание
			if (pchar.questTemp.GoldenGirl.Portugal == "true")
			{
				dialog.text = "¡Aquí estás, amigo mío! El Capitán Moreno ya te está esperando.";
				link.l1 = "...";
				link.l1.go = "Julianna_89";
			}
			else
			{
				dialog.text = "Charles, creo que encontré algo. ¿Recuerdas al capitán Moreno? ¿Aquel que jugó contra ti aquella fatídica noche?";
				link.l1 = "Yo sí, qué vagabundo. ¿Qué hay de él?";
				link.l1.go = "Julianna_102";
			}
		break;
		
		case "Julianna_89":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_9";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			chrDisableReloadToLocation = true;
		break;
		
		case "Julianna_90":
			dialog.text = "Siempre lo supe, Bartolomeo de la Cueva. Por eso llegaste a mi fiesta en primer lugar. Era como añadir jalapeños a la cena de uno. Sé que tú y tus muchachos han estado husmeando en esta isla durante un par de semanas. Sé que esto debe estar de alguna manera conectado con el barón pirata de Le Francois y Angerran de Chievous. Cuéntale a mi amigo todo al respecto y mantendremos tu legendario nombre en secreto a cambio. De lo contrario, llamaré a los guardias que ya están parados detrás de las puertas. Los llamé cuando llegaste.";
			link.l1 = "...";
			link.l1.go = "Julianna_91";
		break;
		
		case "Julianna_91":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_92":
			dialog.text = "¡No solo ellos! ¡Angerran me regaló un collar, uno hermoso! Perlas grandes y limpias, incluyendo esta, oscura como la noche sureña, en el medio. ¡Pero lo encargó a los joyeros locales!";
			link.l1 = "...";
			link.l1.go = "Julianna_93";
		break;
		
		case "Julianna_93":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_18";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_94":
			dialog.text = "Apuesto a que no lo hizo solo para complacerme con un regalo lujoso. Aunque, ese regalo fue su último recurso para ganarse mi favor dentro de los límites de la decencia. Angerran no tiene títulos ni tierras, incluso su fragata sigue siendo suya solo hasta que su padre decida lo contrario. Hace uso del poder y la influencia, pero no tiene una fuente de ingresos propia. ¿Quizás se cansó de esperar las donaciones de su padre y decidió arreglar su estado financiero?";
			link.l1 = "¡Espere, señora! ¡El juego de cartas! Si tenemos razón y de Chievous planeó todo de antemano, debe haber necesitado mucho dinero para las apuestas con el fin de acorralar a nuestro gobernador lo suficiente. Pedirle tal cantidad a un padre podría atraer su atención no deseada al asunto. Robar tesoros ya robados a los corsarios parece una manera silenciosa y segura de obtener la moneda necesaria. ¡Nadie lo sabría!";
			link.l1.go = "Julianna_95";
		break;
		
		case "Julianna_95":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_21";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_96":
			dialog.text = "A nosotros, Charles! Angerran no debe salirse con la suya esta vez. Su posición sobre mí ha ido demasiado lejos y me gustaría ayudarte a solucionarlo.";
			link.l1 = "";
			link.l1.go = "Julianna_97";
		break;
		
		case "Julianna_97":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_23";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_98":
			dialog.text = "¡Un pirata perdedor y una cortesana casi enamorada! Charles, ¡tienes un equipo de ensueño para ti!";
			link.l1 = "Sin embargo, gracias, a ambos. ¡Sinceramente! Ahora necesito pensar en esto un poco y elaborar un plan.";
			link.l1.go = "Julianna_99";
		break;
		
		case "Julianna_99":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_25";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_100":
			dialog.text = "Esta casa tiene todo lo que sus huéspedes desean. Haré los arreglos. Únete a nosotros cuando estés listo, Charles.";
			link.l1 = "Muy bien, señora.";
			link.l1.go = "Julianna_101";
		break;
		
		case "Julianna_101":
			DialogExit(); // фин 3
			AddQuestRecord("GoldenGirl", "22");
			npchar.Dialog.currentnode = "Julianna_119";
			LAi_SetOwnerType(npchar);
		break;
		
		case "Julianna_102":
			dialog.text = "Nada, pero alguien en el pueblo lo está buscando. Están preguntando activamente por ti y otros huéspedes de esa noche. No sé qué está pasando todavía, pero estoy seguro de que te has metido en algo más grande de lo que piensas.";
			link.l1 = "¿Algo más grande? ¿Qué quieres decir, Julianne?";
			link.l1.go = "Julianna_103";
		break;
		
		case "Julianna_103": // запускаем Кортни
			chrDisableReloadToLocation = true;
			DialogExit();
			sld = characterFromId("Cortny");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_104":
			dialog.text = "Angerran... quiero decir, Monseniour de Chievous me regaló un maravilloso collar de perlas. Una de las perlas era negra como la noche. Pensé que era solo una falsificación con una bonita historia detrás. Nunca lo usé, no quería dar falsas esperanzas, pero es tan hipnotizantemente hermoso.";
			link.l1 = "";
			link.l1.go = "Julianna_105";
		break;
		
		case "Julianna_105":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_106":
			dialog.text = "¿Qué harás, Charles? ¿Tienes alguna idea de lo que está pasando?";
			link.l1 = "Aún no, pero lo haré. De Chievous está metido en algo serio hasta el cuello y esta es mi oportunidad. Su tierra natal no se atreverá a tocarlo, pero las autoridades británicas tal vez sí. Prefiero no secuestrarte, Julianne.";
			link.l1.go = "Julianna_107";
		break;
		
		case "Julianna_107":
			dialog.text = "Eres muy amable, Charles, pero no muy gracioso.";
			link.l1 = "";
			link.l1.go = "Julianna_108";
		break;
		
		case "Julianna_108":
			DialogExit();
			chrDisableReloadToLocation = false;
			pchar.quest.goldengirl_time_cortny.win_condition.l1 = "Timer";
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.hour  = 20.00;
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.function = "GoldenGirl_TimeCortny";
			pchar.quest.goldengirl_time_cortny.win_condition.l1 = "Timer";
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.hour  = 23.00;
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.function = "GoldenGirl_TimeCortnyFail";
			if(bImCasual) NewGameTip("Modo exploración: el temporizador no está desactivado. ¡Cumple el plazo!");
			AddQuestRecord("GoldenGirl", "17");
		break;
		
		case "Julianna_109":
			dialog.text = "Charles, ¿aprendiste algo? Pareces nervioso... ¿Qué pasa?";
			link.l1 = "¡Maldita sea! Ojalá las cosas fueran diferentes... Empaca tus cosas, deberíamos irnos, Marquesa. Por favor, no causes problemas.";
			link.l1.go = "Julianna_76";
		break;
		
		case "Julianna_110":
			pchar.quest.goldengirl_time_cortny_fail.over = "yes"; //снять прерывание
			dialog.text = "Charles, entra. El baronet ya está aquí y tuvimos una charla agradable. Le estaba contando sobre tu interés en los acontecimientos actuales.";
			link.l1 = "Julianne, no estoy tan seguro de que haya sido prudente...";
			link.l1.go = "Julianna_111";
		break;
		
		case "Julianna_111":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_112":
			dialog.text = "Baronet, ¡parece que tus hombres dejaron caer algo detrás de la puerta! ¿Serías tan amable de decirles que se comporten mejor?";
			link.l1 = "";
			link.l1.go = "Julianna_113";
		break;
		
		case "Julianna_113":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_114":
			dialog.text = "¡Horrible! ¿Qué hacemos ahora?!";
			link.l1 = "¡Maldita sea! Ojalá las cosas fueran diferentes... Empaca tus cosas, deberíamos irnos, Marquesa. Por favor, no causes problemas.";
			link.l1.go = "Julianna_76";
		break;
		
		case "Julianna_115":
			dialog.text = "¡Dios todopoderoso! ¿Qué habéis hecho con mi sala de estar, caballeros? ¡Esto parece una pesadilla medieval! ¿Quiénes son estas personas? ¿Y dónde están los guardias?";
			link.l1 = "¿Estás bien, Julianne? Bien. Apuesto a que los guardias están gastando su bien merecido soborno en una taberna. Baronet, mis felicitaciones - has logrado cabrear a Goodman Jack de verdad. Un intento de asesinato tan desordenado y mal preparado no es para nada su estilo.";
			link.l1.go = "Julianna_116";
		break;
		
		case "Julianna_116":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_21";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_117":
			dialog.text = "Me disculpo por interrumpir vuestra emocionante discusión, pero a menos que alguno de vosotros esté herido, movámonos a un gabinete. Un espectáculo como este no es muy reconfortante para una dama... ¡Solo el techo está libre de sangre!";
			link.l1 = "Entonces suba las escaleras, marquesa. Realmente debería acostarse un rato y alejarse de toda esta sangre. El baronet Cortney y yo hablaremos de esto. ¿Continuamos?";
			link.l1.go = "Julianna_118";
		break;
		
		case "Julianna_118":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto2", "", 20.0);
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_24";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_119":
			dialog.text = "Charles, ¿estás listo para compartir tu plan con nosotros?";
			link.l1 = "Casi. Dime, ¿es de Chievous un tipo pedante? ¿Mantiene sus libros y registros en orden?";
			link.l1.go = "Julianna_120";
		break;
		
		case "Julianna_120":
			dialog.text = "¡Angerran es el colmo de la dilación cuando se trata de finanzas! Firma más papeles que cualquier banquero que conozco. Supongo que ha sido así desde su infancia, cuando no sabía quién era su padre y vivía en la pobreza en las calles.";
			link.l1 = "¡Espléndido! ¡Ahora, necesitamos su bitácora y sus libros! Servirán como prueba viable para los británicos. ¡Debemos averiguar cómo conseguirlos! Ojalá hubiera sabido esto cuando tenía su barco en mi posesión... suspira.";
			link.l1.go = "Julianna_121";
		break;
		
		case "Julianna_121":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_27";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_122":
			dialog.text = "Espera, Charles, ¿realmente piensas que después de todo lo que ha pasado permitiré venderme a de Chievous como una cabra de granja?";
			link.l1 = "No te preocupes, Julianne, solo tomará unos pocos días. Prometo que te tratarán como un jarrón inestimable de China. Corrígeme si me equivoco, pero de Chievous nunca se mostrará para el intercambio, ¿verdad? ";
			link.l1.go = "Julianna_123";
		break;
		
		case "Julianna_123":
			dialog.text = "Estoy seguro de ello. Angerran estará esperando bajo el ala de Francois de Lyons y nunca se atreverá a encontrarse contigo en mar abierto. Pero sobre esta captura mía...";
			link.l1 = "";
			link.l1.go = "Julianna_124";
		break;
		
		case "Julianna_124":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_29";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_125":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Charles, lamento interrumpir, pero ¿no olvidaste preguntar mi opinión sobre todo esto? Semanas dentro de esos ataúdes chirriantes... ¿Te das cuenta siquiera de lo que me estás pidiendo? Evidentemente estás apegado a esa... chica, ¡pero yo no soy uno de tus tripulantes! Lo siento, pero todo esto no suena a una historia de amor seria.";
				link.l1 = "Me temo, marquesa, que tendré que insistir. No puedo permitirme perderla.";
				link.l1.go = "Julianna_127";
				link.l2 = "Todos cometemos errores, Julianna. Tú, más que nadie, deberías saberlo. Te pido que me ayudes.";
				link.l2.go = "Julianna_126";
			}
			else
			{
				dialog.text = "Charles, lamento interrumpir, pero ¿no olvidaste preguntarme mi opinión sobre todo esto? Semanas dentro de esos ataúdes chirriantes... ¿Te das cuenta siquiera de qué me estás pidiendo?! Tus sentimientos son dignos de la literatura clásica sobre caballería, pero yo soy solo una cortesana común. Te admiro y quiero ayudarte, ¡pero todo tiene un límite!";
				link.l1 = "";
				link.l1.go = "Julianna_128";
			}
		break;
		
		case "Julianna_126":
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", -1);
			if(sti(pchar.reputation.nobility) > 65)
			{
				pchar.questTemp.GoldenGirl.Julianna_Helper = "true";
				dialog.text = "Entiendo, Charles. Quiero creer en el amor verdadero perfecto, pero supongo que no hay tal cosa en este mundo.";
				link.l1 = "Gracias, marquesa. Haré todo bien esta vez. Aprendí mucho de esta historia, y rezo para no pagar un precio demasiado terrible por lo que he hecho.";
				link.l1.go = "Julianna_129";
			}
			else
			{
				dialog.text = "Has tomado tu decisión, te he apoyado todo el tiempo, pero basta es basta. Sacrificarlo todo por el bien de un amor que ya habías abandonado en mi dormitorio. Todo esto es muy conmovedor, Charles, pero no soy tan joven e ingenua.";
				link.l1 = "Me temo, marquesa, que tendré que insistir. No puedo permitirme perderla.";
				link.l1.go = "Julianna_127";
			}
		break;
		
		case "Julianna_127":
			pchar.questTemp.GoldenGirl.Julianna_Prisoner = "true";
			dialog.text = "Bien, Capitán, haz lo que quieras. No te resistiré, pero ten en cuenta que lo hago en contra de mi voluntad.";
			link.l1 = "Piénsame lo que quieras, Julianna, me lo he ganado. Pero la recuperaré sin importar el costo\n¡Julianna, escucha, sé lo que te estoy pidiendo! Dejar todo atrás y permitir que otros te arrastren a una apuesta dudosa. ¡Pero en este momento eres mi única esperanza! ¡Necesito tu ayuda en esto y estaré en deuda contigo hasta que muera!";
			link.l1.go = "Julianna_129";
		break;
		
		case "Julianna_128":
			pchar.questTemp.GoldenGirl.Julianna_Helper = "true";
			dialog.text = "Muy bien, Capitán. Al final, Angerran debe ser eliminado de una vez por todas. Te ayudaré, pero dime, ¿cómo piensas rescatarme de su barco?";
			link.l1 = "...";
			link.l1.go = "Julianna_129";
		break;
		
		case "Julianna_129":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_31";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_130":
			dialog.text = "Espera. Puedes llevarte mi perla del collar, ¿los ingleses están buscando perlas negras, verdad? Esta hará que te escuchen. ¿Qué sigue?";
			link.l1 = "Después llevaré al investigador a bordo y navegaremos a Guadalupe. Realizaremos una búsqueda oficial en la fragata de Chievous cuando regrese contigo a bordo. El asunto de Mercury fue un incidente serio que involucró a nuestro aliado, ¡por lo tanto De Lyon tendrá que permitirlo!";
			link.l1.go = "Julianna_131";
		break;
		
		case "Julianna_131":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_33";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_132":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Él dirá a todos que fueron sus hombres quienes me salvaron del cautiverio. Y ten en cuenta, Capitán, aún tengo que decidir qué les diré.";
				link.l1 = "Decir nada estaría bien, marquesa. Créeme, te sacaré a rastras y haré que Angerran pague por todo.";
			}
			else
			{
				dialog.text = "Les diré que fui secuestrado por extraños, justo desde mi casa, para ser llevado a bordo del barco de Angerran. Parecerá que pagó a mercenarios para secuestrarme.";
				link.l1 = "Otro clavo para el ataúd de Angerran, marquesa.";
			}
			link.l1.go = "Julianna_133";
		break;
		
		case "Julianna_133":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_35";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_134":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Dame tiempo hasta la mañana, a menos que quieras llevarme en un saco. Envía a un par de hombres para ayudarme también; una mujer de estatura no puede viajar sin comodidades. Charles, me salvaste y te ayudaré, además, por favor, acepta esta perla negra invaluable, mi regalo para ti. Si esto funciona, estaremos a mano.";
				link.l1 = "Como digáis, marquesa. ¡Que Dios os acompañe, a ambos! Nos vemos aquí de nuevo cuando todo haya terminado.";
			}
			else
			{
				dialog.text = "Estaré listo para partir al amanecer. No voy a andar dando tumbos en un almacén de carga, así que asegúrate de prepararme una habitación decente, o como sea que lo llames. Charles, aquí, toma esto. Esta es una valiosa perla negra. Me doy cuenta de que cuesta más que este lugar, pero algunas cosas no pueden medirse en oro. Espero que te sea de utilidad. ¡Que Dios te ayude!";
				link.l1 = "¡Viento en popa, a ambos! Nos vemos aquí de nuevo cuando todo haya terminado.";
			}
			link.l1.go = "Julianna_135";
		break;
		
		case "Julianna_135":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
			sld = characterFromId("GG_Moreno");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "23");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			chrDisableReloadToLocation = false;
			pchar.questTemp.GoldenGirl = "antigua";
			// убрать фрегат Шиво
			pchar.quest.goldengirl_AngerranCap_AfterBattle.over = "yes";
			Group_DeleteGroup("GG_AngerranGroup");
			sld = characterFromId("GG_AngerranCap");
			sld.lifeday = 0;
			GiveItem2Character(pchar, "blackpearl"); // черная жемчужина 
		break;
		
		case "Julianna_136":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Felicitaciones, Capitán.  Tu plan tuvo éxito. ¡Qué escándalo tan enorme has orquestado! Los ingleses se llevaron a Angerran y su barco con todo su contenido, excluyéndome a mí.";
				link.l1 = "El señor William ni siquiera vino a despedirse. Prometió disculparse.";
				link.l1.go = "Julianna_137";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
				else sld = characterFromId("Mary");
				dialog.text = "¡Charles, lo logramos! ¡Te liberarán en cualquier momento! Sin embargo, debemos abandonar la isla lo más rápido posible. El gobernador está muy molesto por el reciente arresto de Angerran.";
				link.l1 = "Me alegra verte, Julianne. ¿Cómo estás? ¿Cómo fue el intercambio? ¿Está bien ella?";
				link.l1.go = "Julianna_140";
			}
		break;
		
		case "Julianna_137":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Supongo que ha estado demasiado ocupado para eso. Como nuestro gobernador en este momento. Será mejor que abandones la ciudad antes de que recuerde tu existencia. Amaba al hijo de Henri, pero los papeles británicos lo acorralaron por completo. No esperaría a que decida descargar toda su frustración sobre ti.";
			link.l1 = "Justo. Además, ella me está esperando en Martinica. ¿Cómo fue el intercambio? ¿Está bien?";
			link.l1.go = "Julianna_138";
		break;
		
		case "Julianna_138":
			dialog.text = "Perdóname, pero no quiero hablar de eso. Pregúntale a ella en su lugar. Adiós, Capitán. Volveré por mi cuenta. Necesito descansar del mar - François es un anfitrión bastante agradable cuando no lo molestan los aburridos oficiales británicos.";
			link.l1 = "Lo siento mucho por todo esto, Madame. Gracias por su cooperación de todos modos. Me complace saber que ha hecho un nuevo... amigo.";
			link.l1.go = "Julianna_139";
		break;
		
		case "Julianna_139":
			dialog.text = "Gracias a ti también, Charles, por cumplir tu palabra. Encuentra a Bartholomew en mi casa en Saint-Pierre. Adiós. Nos volveremos a ver.";
			link.l1 = "Adiós, Julianne. Que Dios te dé buena mar.";
			link.l1.go = "Julianna_143";
		break;
		
		case "Julianna_140":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "No la he visto, pero Bartholomew la tomó viva y sana. ¡Ese inglés arrestó a de Chievous y confiscó su propiedad justo bajo las narices del gobernador, ni siquiera dijo una palabra! ¡Milagro!";
			link.l1 = "Sabes, salió sorprendentemente bien, considerando el trasfondo de este arresto. Aunque, todavía debería volverse en nuestra contra más tarde. ¡Lo que sea! Debo ir a Martinica de inmediato, debo verla lo antes posible.";
			link.l1.go = "Julianna_141";
		break;
		
		case "Julianna_141":
			dialog.text = "Sin duda, ustedes dos tienen mucho que decirse. Oh, Charles, desearía tener a un hombre con tal fuego en sus ojos a mi lado. Apresurémonos, realmente extraño un baño caliente y sábanas limpias. Bartholomew nos estará esperando en mi casa en Saint-Pierre.";
			link.l1 = "Sí, el romance de los viajes por mar está sobrevalorado. Tendrás mi camarote, marquesa, es lo menos que puedo hacer. Vamos.";
			link.l1.go = "Julianna_142";
		break;
		
		case "Julianna_142":
			dialog.text = "Tú ya has hecho por mí todo lo que podías, Charles. Has hecho que una mujer cínica vuelva a creer.";
			link.l1 = "Yo también, Julianne. Yo también.";
			link.l1.go = "Julianna_143";
		break;
		
		case "Julianna_143":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto13", "none", "", "", "GoldenGirl_BasterReloadJail", 7.0);
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				ChangeCharacterComplexReputation(pchar, "fame", 15);
				ChangeCharacterComplexReputation(pchar, "nobility", -10);
				ChangeCharacterNationReputation(pchar, ENGLAND, 10);
			}
			else
			{
				ChangeCharacterComplexReputation(pchar, "fame", 15);
				ChangeCharacterNationReputation(pchar, ENGLAND, 20);
			}
		break;
		
		case "Julianna_144":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "¡Charles, me alegra tanto que hayas venido! ¿Cómo está esa dama tuya? ¿Está bien?";
				link.l1 = "Todo está bien, gracias a ti, Julianne. Quería decírtelo de nuevo. Eres una mujer maravillosa y estaré eternamente en deuda contigo por todo tu valor e ingenio.";
				link.l1.go = "Julianna_145";
			}
			else
			{
				dialog.text = "¡Charles, estoy tan contento de que hayas venido! ¿Cómo está esa dama tuya? ¿Está bien?";
				link.l1 = "Todo está bien, gracias a ti, Julianne. Quería decírtelo de nuevo. Eres una mujer maravillosa y estaré eternamente en deuda contigo por todo tu coraje e ingenio.";
				link.l1.go = "Julianna_148";
			}
		break;
		
		case "Julianna_145":
			dialog.text = "Tal vez sea yo quien esté en deuda contigo. Después de todo, me salvaste de dos clientes extremadamente molestos. Creo que todavía te debo una. Pide lo que quieras, Charles.";
			link.l1 = "En ese caso, tengo un pequeño favor que pedirte, mi señora. Puedes hacer algo para estar a mano.";
			link.l1.go = "Julianna_146";
		break;
		
		case "Julianna_146":
			dialog.text = "Soy todo oídos, mi Capitán. ¿Qué ocurre?";
			link.l1 = "La gente comete errores, pero eso no hace que el mundo sea malo. Recuerda eso y sé feliz, Julianne. Mereces ser feliz.";
			link.l1.go = "Julianna_147";
		break;
		
		case "Julianna_147":
			dialog.text = "Yo... lo intentaré, Charles. Gracias. ¿Vendrás a visitarme de vez en cuando... como amigo? ¡Siempre serás bienvenido en mi casa!";
			link.l1 = "Agradezco, marquesa. Adiós y recuerda lo que me prometiste.";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_148":
			dialog.text = "Aparentemente, no lo suficientemente maravilloso... pero me alegra que haya terminado bien para ti. No me debes nada, ¡después de lo que hiciste no puedo agradecerte lo suficiente! Ven a verme cuando estés en tierra. ¡Siempre serás bienvenido en mi casa, como un amigo!";
			link.l1 = "Gracias, marquesa. Le deseo todo lo mejor. ¡Adiós!";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_149":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_150";
		break;
		
		case "Julianna_150":
			dialog.text = "Charles, mi amigo, eres tan grosero, ¡visitándome tan raramente! Te eché de menos, ¿sabes eso? ¿Te apetece un poco de vino? ¡Estoy ansioso por escuchar emocionantes historias de primera mano! ¡Y probar tu famosa fortuna!";
			link.l1 = "Marquesa, solo quería saludar y asegurarme de que estés bien.";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "Julianna_";
		break;
		
		// Жак Дьель дю Парке
		case "governor":
			dialog.text = "¡Y ahí estás, mi amigo! ¡Me alegra verte de nuevo!";
			link.l1 = "...";
			link.l1.go = "governor_1";
		break;
		
		case "governor_1":
			DialogExit();
			sld = characterFromId("Angerran");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "governor_2":
			dialog.text = "Bueno, la forma en que tratas a mi amigo me deja sin elección, monsieur. Acepto tu desafío. ¿Hora y lugar?";
			link.l1 = "Aquí y ahora. Llama a los sirvientes, diles que traigan velas, un crepúsculo acogedor como este no servirá. ¡Este lugar debe estar tan brillante como el día!";
			link.l1.go = "governor_3";
		break;
		
		case "governor_3":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_4";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			sld = characterFromId("Angerran");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
		break;
		
		case "governor_4":
			dialog.text = "Mi amigo, por favor, no te lo tomes demasiado a pecho. Angerran es un pedazo de trabajo desagradable, eso es cierto, pero no deberías arremeter contra él. Déjamelo a mí.";
			link.l1 = "¿Está seguro, su Excelencia? Está tan borracho como mi contramaestre después de una semana en tierra, pero sin duda sabe manejar su espada. Puedo darme cuenta de esas cosas de inmediato.";
			link.l1.go = "governor_5";
		break;
		
		case "governor_5":
			dialog.text = "¡Dios me libre, Charles! No voy a batirme en duelo con él. Apostaremos, las cartas son las armas de los hombres civilizados. Lo dejaré seco y te lo enviaré suplicando un préstamo para un regreso seguro a Quebec.";
			link.l1 = "Eso es un plan sólido, de acuerdo. Pero si me preguntas, yo preferiría al bastardo muerto, no pobre. ¡Buen viento, Su Excelencia!";
			link.l1.go = "governor_6";
		break;
		
		case "governor_6":
			DialogExit();
			sld = characterFromId("FortFrance_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_11";
			sld.greeting = "Marquesa_needhelp";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "governor_7":
			dialog.text = "¡Maldita sea, Angerran, no hay forma de que sea un diez allí! ¡De ninguna manera!";
			link.l1 = "¿Fue eso una acusación? Fue tu trato, monsieur.";
			link.l1.go = "governor_8";
		break;
		
		case "governor_8":
			dialog.text = "No lo fue. Estoy solo... un poco demasiado emocionado y pido disculpas. Fue un accidente y exijo una oportunidad para una revancha. ¡Este barco, yo... debo recuperarlo! O al diablo con el juego, solo dime por cuánto estarías dispuesto a vendérmelo. ¡Dime el precio y lo verás pagado mañana antes del mediodía!";
			link.l1 = "¡Ay, pero creo con todo mi corazón que no se puede recuperar el botín del juego! Solo puedes ganarlo de nuevo. El filibote es mío ahora y no tengo intención de venderlo. Lamento que tu pasión te haya puesto en tal posición, a veces deberíamos ser más realistas sobre nuestras capacidades... ¿Quizás tienes más papeles del barco?";
			link.l1.go = "governor_9";
		break;
		
		case "governor_9":
			dialog.text = "Eres un sinvergüenza, Angerran, y me tienes acorralado. Creo que puedo ofrecer una participación que aceptarás.";
			link.l1 = "...";
			link.l1.go = "governor_10";
		break;
		
		case "governor_10":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_23";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "governor_11":
			dialog.text = "¡Charles, eres mi única esperanza, te ruego que me ayudes! Ese filibote y su... cargamento ya han sido vendidos a la Compañía Holandesa. Debo entregarles todos los documentos mañana. Pensé que me quedaría aquí toda la noche, así que los traje conmigo. ¡Me enfrentaré a una situación desastrosa si el trato se cancela!";
			link.l1 = "Pero 'dulce Jacques', ¿no estás de acuerdo en que la mujer que favoreciste enfrenta una situación aún más desastrosa ahora? He tenido mi parte de juegos de azar y entiendo algo como apostar por un barco, incluso si no es tuyo. ¡¿Pero apostar por una dama?! ¡Me has sorprendido, de verdad! ¿Y ahora todo lo que te importa es el destino de tu trato?";
			link.l1.go = "governor_12";
		break;
		
		case "governor_12":
			dialog.text = "No me juzgues, Charles. Favorecer a una ex amante de un poderoso conde e incluso enamorarse un poco no es nada comparado con deberle un millón de pesos a Peter Stuyvesant. ¿Cómo le explico esto a su agente? ¡Imagina todo el daño a mi reputación!";
			link.l1 = "Tuve una deuda similar antes, y no saqué nada de ella. Sin embargo, me fue bien. Así que tú también podrás resolverlo. Nos vemos, Jacques. No prometo nada y ni siquiera preguntaré qué tipo de carga hay en ese filibote.";
			link.l1.go = "governor_13";
		break;
		
		case "governor_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto5", "", 10.0); // уходит
			LocatorReloadEnterDisable("FortFrance_SecBrRoom", "reload3", false); // открыть доступ в малую комнату
		break;
		
		case "governor_14":
			dialog.text = "Ahí estás, Charles. Estaba a punto de enviarte a buscar. De Chievous insiste en un duelo y ya rechaza cualquier posibilidad de reconciliación. Lo hiciste bien con las cartas, pero ¿estás seguro de que quieres seguir haciendo esto?";
			link.l1 = "Tengo la molesta sospecha, Su Excelencia, de que usted quería este resultado desde el principio. Así que digo que sí. Esto debe resolverse de una vez por todas. ¿Qué hay de los términos del duelo?";
			link.l1.go = "governor_15";
		break;
		
		case "governor_15":
			dialog.text = "Eres demasiado egocéntrico, amigo mío. Algunas partes de nuestro mundo aún no giran a tu alrededor. Créeme, estoy profundamente decepcionado de cómo salió todo anoche. Mucho. Pero primero, hablemos del destino de tus... ganancias.";
			link.l1 = "Bien. ¿Quieres saber cómo devolver el filibote o cómo está Madame Julianne?";
			link.l1.go = "governor_16";
		break;
		
		case "governor_16":
			dialog.text = "Puedo ver que has cambiado tu ironía inapropiada por rencor. Charles, estamos del mismo lado en esto, no lo olvides.";
			link.l1 = "Argumento discutible, Su Excelencia. Para decirlo suavemente. Ahora, ¿por dónde empezamos: el barco o la dama?";
			link.l1.go = "governor_17";
		break;
		
		case "governor_17":
			dialog.text = "El trato de Stuyvesant, por supuesto... su agente me ha estado esperando toda la mañana y me estoy quedando sin excusas. Necesito los papeles del filibote, Charles.";
			link.l1 = "Está bien. Es tuyo. No creo que de Chievous haya jugado honestamente, por lo tanto, puedes recuperar tu propiedad por la mitad de su precio. 150 000.";
			link.l1.go = "governor_18";
			link.l2 = "Me encantaría complacerte. ¿Cuál fue el costo del navío, dijiste? ¿500 000? Me parece bien.";
			link.l2.go = "governor_19";
		break;
		
		case "governor_18":
			AddMoneyToCharacter(pchar, 135000);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			dialog.text = "Ahora, serán cuatrocientos sesenta mil pesos, impuestos incluidos. Trato. 135 000.";
			link.l1 = "Escucha... Me estoy cansando de discutir. Así que paga, toma tus documentos y acaba con esto.";
			link.l1.go = "governor_20";
		break;
		
		case "governor_19":
			AddMoneyToCharacter(pchar, 300000);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			dialog.text = "No tienes piedad de los viejos amigos, ¿verdad Charles? Ahora, con todos los impuestos incluidos...";
			link.l1 = "La deuda de cartas y la amistad no tienen nada en común, Su Excelencia. Usted mismo pagará impuestos como comprador o vendo el barco en Le Francois. Fíjese, no estoy aprovechándome de su posición... todavía.";
			link.l1.go = "governor_20";
		break;
		
		case "governor_20":
			dialog.text = "Está bien, que así sea. Ahora, el duelo. No necesito problemas con el conde de Levi Vantadur, por lo tanto, todo debe ser tan legalmente correcto como sea posible. ¿Me oyes, Charles? ¡De acuerdo con la ley! Enviaré a dos oficiales de mi guarnición para que te acompañen - ambos son hombres nobles y respetados. Ellos serán tus segundos en lugar de tus habituales... compañeros. ¡Quiero que todo esté muy claro hasta que el asunto esté resuelto!";
			link.l1 = "Qué amable de tu parte. ¿Y qué si nuestro buen amigo decide jugar sucio? Prefiero confiar mi espalda a personas a las que llamo amigos, y aquellos que saben qué hacer en tales situaciones, en lugar de a personas que nacieron en las familias adecuadas.";
			link.l1.go = "governor_21";
		break;
		
		case "governor_21":
			dialog.text = "Charles, deja de comportarte como si este duelo fuera solo entre tú y yo. Esto es un asunto serio. De Chievous no es un hombre al que matas y te sales con la tuya. Cualquier resultado será seguido de investigaciones, incluso de un juicio quizás. Necesitaremos testigos de confianza. Mira, ¡estoy cuidando de ti! Lo más importante, sin embargo, es que no puedes matarlo. Entiendo, Angerran está decidido y probablemente es un buen luchador, pero, Charles, ¡no puedes matarlo! Hiérele, humíllalo incluso, pero detente ahí. Si lo matas, habrá consecuencias y ninguno de nosotros podrá esquivarlas o sobrevivir a ellas. Aunque el conde de Levi Vantadur nunca reconoció oficialmente a su bastardo, no tiene otros hijos. Su ira no tendrá fin.";
			link.l1 = "Maravilloso, ¿así que prefiero dejarme matar antes que permitir que el conde enfurecido te saque de tu puesto de gobernador?";
			link.l1.go = "governor_22";
		break;
		
		case "governor_22":
			dialog.text = "Me temo que si no escuchas, no viviremos mucho más que Angerran de Chievous. Recuerda eso y ten cuidado. El duelo está fijado para las diez de la noche más allá de las puertas de la ciudad. Mis oficiales te encontrarán allí. Ahora, el último asunto: Madame Julianne Botot, ¿cómo está ella?";
			link.l1 = "¿Quieres saber si ya me aproveché de mi premio? No, Excelencia, aún no o nunca, no importa. Lo que importa es que estás fuera de la casa de la marquesa para siempre. Ella fue muy clara al respecto. No puedo juzgarla por ello. Julianne elegirá a su próximo patrocinador ella misma.";
			link.l1.go = "governor_23";
		break;
		
		case "governor_23":
			dialog.text = "Sabes cómo sorprender, Charles. Como sea, tengo una reunión tediosa con el agente de la Compañía a la que debo asistir. Deberías ir también, prepárate y recuerda lo que te advertí.";
			link.l1 = "Sin duda lo intentaré, Excelencia. Pero es una pelea, así que no prometo nada. Gracias por ayudarme.";
			link.l1.go = "governor_24";
		break;
		
		case "governor_24":
			DialogExit();
			GoldenGirl_GovernorOut();
		break;
		
		case "governor_25":
			dialog.text = "¡Vives, Charles! Qué alivio, ¿cómo te fue? ¿Es esto sangre?! ¿Lo logró de Chievous?";
			link.l1 = "Lamentablemente, sí. Está herido, pero no gravemente. Tuvo que huir, pero también lanzó a sus matones contra nosotros. En resumen, parte de esta sangre no es mía.";
			link.l1.go = "governor_26";
		break;
		
		case "governor_26":
			dialog.text = "¡Bastardo! ¿Y mis hombres? ¿Están vivos para testificar lo que ocurrió?";
			if (sti(pchar.questTemp.GoldenGirl.Officer) > 1)
			{
				link.l1 = "Están bien, Excelencia. Un poco golpeados, pero vivirán.";
				link.l1.go = "governor_27_1";
			}
			else
			{
				if (sti(pchar.questTemp.GoldenGirl.Officer) == 1)
				{
					link.l1 = "No todos ellos, Excelencia. Un caballero no lo logró - de Chievous se tomó la molestia de traer mosqueteros. No pude hacer nada.";
					link.l1.go = "governor_27_2";
				}
				else 
				{
					link.l1 = "Fue un infierno desatado allí, Excelencia. Ambos valientes caballeros cayeron en combate. Si no fuera por ellos, las cosas se hubieran puesto feas para mí. De Chievous orquestó una emboscada de puta madre.";
					link.l1.go = "governor_27_3";
				}
			}
		break;
		
		case "governor_27_1":
			dialog.text = "¡Espléndido! Obtendré sus testimonios escritos en presencia de testigos fiables. ¡De Chievous pagará por esto!";
			link.l1 = "No creo que podamos hacerle el más mínimo daño a su nombre. Preferiría encontrarlo y terminar el trabajo yo mismo a pesar de todas tus advertencias. Un cobarde así no merece vivir.";
			link.l1.go = "governor_28";
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
			ChangeCharacterComplexReputation(pchar, "authority", 6);
			ChangeCharacterComplexReputation(pchar, "fame", 6);
		break;
		
		case "governor_27_2":
			dialog.text = "Terrible. Pero obtendremos el testimonio escrito de al menos un testigo. ¡De Chievous pagará por esto!";
			link.l1 = "No creo que podamos hacerle ni el más mínimo daño a su nombre. Prefiero encontrarlo para terminar el trabajo yo mismo a pesar de todas tus advertencias. Un cobarde así no merece vivir.";
			link.l1.go = "governor_28";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "governor_27_3":
			dialog.text = "¡Maldito sea! ¡Eran buenos hombres, Charles! ¡Te juro, el bastardo pagará!";
			link.l1 = "No creo que podamos hacerle ni el más mínimo daño a su nombre. Preferiría encontrarlo yo mismo para terminar el trabajo a pesar de todas tus advertencias. Un cobarde así no merece vivir.";
			link.l1.go = "governor_28";
		break;
		
		case "governor_28":
			dialog.text = "Olvídalo, Charles. El bastardo hizo todo el daño necesario él mismo. Apostaría a que está huyendo ahora, escondiéndose en la mugre de alguna pobre colonia. Es poco probable que ahora sea una amenaza para ti. Esta villanía fue solo la mordida de una serpiente huyendo. Tú también pareces herido, ¿necesitas un médico?";
			link.l1 = "Gracias por sus preocupaciones, Excelencia, pero estoy bien.";
			link.l1.go = "governor_29";
		break;
		
		case "governor_29":
			dialog.text = "Bueno saberlo. Ahora puedes respirar libremente, esta historia ha terminado. Relájate y vuelve a tus asuntos. Por cierto, sobre eso... No terminamos nuestra conversación anterior sobre tus recientes ganancias. ¿Has decidido qué harás con... ello?";
			link.l1 = "No te sigo del todo, Jacques. ¿Qué eso? ¿Te refieres a la marquesa? ¡Mierda! ¡Madame Botot! ¡De Chievous está huyendo, ya no es una amenaza para mí, pero está desesperado y puede hacer cualquier cosa! ¡Debo irme! ¡Envía a los guardias a la casa de la marquesa! ¡Ahora!";
			link.l1.go = "governor_30";
		break;
		
		case "governor_30":
			DialogExit();
			GoldenGirl_ToJulianna();
		break;
		
		case "governor_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "governor_";
		break;
		
		case "Angerran":
			if (pchar.questTemp.Sharlie == "escape")
			{
				dialog.text = "¿Un capitán famoso, dices? ¿El que repelió el asalto español y casi arrasó este pequeño pueblo? Ya veo. ¿Qué vas a beber?";
			}
			else
			{
				dialog.text = "¿Un capitán famoso, dices? Nunca he oído hablar de ti... ¿Qué vas a beber?";
			}
			link.l1 = "...";
			if (pchar.questTemp.GoldenGirl.Vine == "red") link.l1.go = "Angerran_1";
			else link.l1.go = "Angerran_2";
		break;
		
		case "Angerran_1":
			dialog.text = "¿Pinot Noir, lo mismo que nuestra hermosa anfitriona? ¿Estás seguro de que puedes saborear adecuadamente después de toda esta sal marina? Normalmente, la gente de tu calibre prefiere beber cosas que puedan disolver una vieja bota.";
			link.l1 = "Si esto fue una sugerencia para pasar juntos las puertas, entonces estoy dentro. Tú tampoco me agradas y me alegra que el sentimiento sea mutuo. Dejemos de hablar, no eres bueno en ello de todos modos. Te dejo la elección de términos y armas.";
			link.l1.go = "Angerran_3";
		break;
		
		case "Angerran_2":
			dialog.text = "¿Un ramo de tierra y meado de gato? ¡Encantador! Ni siquiera maduran esta mierda agria en barriles, porque nunca se convertirá en vino, jamás. Dime, ¿es que la sal marina endurece tanto el sabor?";
			link.l1 = "Si esto era una sugerencia para pasar juntos por las puertas, entonces estoy dentro. Tú tampoco me caes bien y me alegra que el sentimiento sea mutuo. Deja de hablar, de todos modos no eres bueno en eso. Te dejo a ti la elección de términos y armas.";
			link.l1.go = "Angerran_3";
		break;
		
		case "Angerran_3":
			dialog.text = "¡Ja, qué valiente muchacho! Ahora, calma tu temperamento y mantén la distancia. No estamos en una taberna y yo no soy un compañero de bebida tuyo. Estás muy por debajo de mi clase, ni siquiera deberíamos estar hablando, pero la dama lo pidió. Ahora, Jacques y yo tenemos un asunto pendiente...";
			link.l1 = "";
			link.l1.go = "Angerran_4";
		break;
		
		case "Angerran_4": // перекидываем pchar на Ангеррана и говорим с губером
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Angerran"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "Angerran_5":
			dialog.text = "¿Julianne, estás bien? ¡Agua, imbéciles! ¡Traed agua!";
			link.l1 = "... ";
			link.l1.go = "Angerran_6";
		break;
		
		case "Angerran_6":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_28";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Angerran_7":
			dialog.text = "Tienes toda la razón, está bochornoso aquí. Ha sido un juego muy entretenido hasta ahora, pero hagamos una pequeña pausa antes del final. Adiós, adiós Jacques, ¿recuerdas los términos de nuestro torneo?\nY aquí tenemos a Charles de Maure, ¿correcto? Un capitán con un gusto pobre por el vino, te recuerdo. No te preocupes, después de que termine aquí, solo beberás agua. Así que tómate tu tiempo, disfruta el momento, bebe algo. Cuando estés listo, ven a unirte a mí en esta pequeña sala. Terminaremos la noche en un ambiente más cómodo...";
			link.l1 = "Esperándolo con ansias, 'monsieur'.";
			link.l1.go = "Angerran_8";
		break;
		
		case "Angerran_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto6", "GoldenGirl_AngerranCards", 10.0); // уходит
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Angerran_9":
			dialog.text = "Ahí estás, por fin. ¿Listo para desprenderte de tu dinero?";
			link.l1 = "¡Preferiría añadir el tuyo a ellos. Por favor!";
			link.l1.go = "Angerran_10";
		break;
		
		case "Angerran_10":
			dialog.text = "Bien dicho, ay, nuestro querido gobernador insistió en cambiar las reglas justo antes de su vergonzosa derrota. Ahora estamos obligados a añadir algo más al dinero en juego. Las apuestas deben ser reconocidas como iguales por ambas partes. Mi apuesta es el filibote con plata.";
			link.l1 = "Vamos, esto es aburrido - puedo conseguir cinco de ellos con oro en unas pocas semanas de saqueo. Dame algo más grande.";
			link.l1.go = "Angerran_11";
		break;
		
		case "Angerran_11":
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = "Sí, he visto tu barco, debo admitir que realmente es un espectáculo para contemplar. Entonces, elevémoslo, dos barcos contra uno. ¿Mi fragata y filibote con plata contra tu barco?";
				link.l1 = "¡Un juego digno! La señora Botot estaba equivocada... ESTE duelo vivirá en las leyendas. ¡Trato hecho!";
			}
			else
			{
				if (sti(RealShips[sti(pchar.ship.type)].Class) <= 3)
				{
					dialog.text = "Mira esto, ¡nuestro capitán es un chico travieso! Sin embargo, el corso es sagrado. ¿Qué tal un buque de guerra entonces? Una fragata, 48 cañones. Más rápida que muchas corbetas - un producto de los astilleros reales, mejorada aún más por los mejores constructores navales del mundo. Los cañones culverinos que lleva tienen un excelente alcance y precisión. ¿Qué dices?";
					link.l1 = "¡Mucho mejor, estoy dentro! ¡Vamos!";
				}
				else
				{
					dialog.text = "Escuché que anclaste aquí, capitán. Agradece que haya aceptado tu vieja bañera como apuesta. Ven entonces, a menos que te niegues.";
					link.l1 = "Tienes razón. Vamos.";
				}
			}
			link.l1.go = "Angerran_12";
		break;
		
		case "Angerran_12":
			DialogExit();
			npchar.money = 200000;
			pchar.questTemp.GoldenGirl.Game.G3 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "Angerran_13":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
				{
					dialog.text = "Juego terminado, Capitán, conseguiste lo que querías. Presume si quieres. Sugiero que discutamos los términos de la compra de mi fragata mañana al mediodía.";
					link.l1 = "¿Eso es todo? Sinceramente creo, igual que tú, que lo que se pierde en una apuesta no se puede comprar, solo recuperar. O puedo venderla como leña a los pescadores locales y contarles todo sobre tu generosa donación.";
					link.l1.go = "Angerran_15";
				}
				else
				{
					if (sti(RealShips[sti(pchar.ship.type)].Class) <= 3)
					{
						dialog.text = "Así que la Fortuna tuvo su palabra. Esto resultó de lo más curioso. Felicitaciones, Capitán de Maure. Sugiero que discutamos los términos de la compra de mi fragata mañana al mediodía.";
						link.l1 = "¿Tan pronto? Estamos decepcionando a otros huéspedes, monsieur. Si no recuerdo mal, todavía tenéis un barco más. Sinceramente creo, al igual que vos, que lo que se pierde en una apuesta no puede comprarse, solo recuperarse ganando.";
						link.l1.go = "Angerran_16";
					}
					else
					{
						dialog.text = "Así que la Fortuna tuvo su palabra. Esto resultó ser de lo más curioso. Felicitaciones, Capitán de Maure. Te ganaste una bebida decente, prueba el Sangiovese. Supongo que Jacques te pagará bien por esta bañera, parece que le tiene afecto, un afecto mucho mayor que a otras ciertas cosas. Será suficiente para comprar un buen vino.";
						link.l1 = "¿Ya te rindes? Estamos decepcionando a los otros invitados, monsieur. Si mal no recuerdo, todavía tienes un barco más. Apunto tu fragata contra mi filibote con plata, ya que consideraste mi propio barco demasiado modesto.";
						link.l1.go = "Angerran_17";
					}
				}
			}
			else
			{
				dialog.text = "Mala suerte, Capitán. No obstante, aprecio tu valentía, además estoy de buen humor hoy. Tomaré tu oro, pero puedes quedarte con tu barco. Sal de mi vista y por favor evita jugar en el futuro. Algún día, te matará.";
				link.l1 = "Muy noble de tu parte, no lo esperaba. Adiós, monsieur de Chievous.";
				link.l1.go = "Angerran_14";
			}
		break;
		
		case "Angerran_14":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			GoldenGirl_CardsFail();
		break;
		
		case "Angerran_15":
			dialog.text = "Hay una diferencia notable entre regodearse y burlarse de su oponente derrotado, monsieur de Maure.";
			link.l1 = "¿Ya te consideras derrotado? Pero todo empezó tan bien... ¡ah! Señora Botot, crea que su salón acaba de obtener otra rica historia sobre las diferencias entre decir y hacer.";
			link.l1.go = "Angerran_15_1";
		break;
		
		case "Angerran_15_1":
			dialog.text = "¿Qué más quieres? No tengo más barcos a mi disposición ni suficiente dinero para cubrir siquiera un barco. Apostar doblones no es serio después de todo lo que hemos visto esta noche también.";
			link.l1 = "¿Eres menos ingenioso que nuestro dulce Jacques Dille do Parkuet? Te estoy regalando la más hermosa oportunidad para demostrar que no todo el amor está en venta. La fortuna tampoco vende su favor. El barco de plata y tu fragata contra lo que valoras más que el oro.";
			link.l1.go = "Angerran_15_2";
		break;
		
		case "Angerran_15_2":
			dialog.text = "Capitán, esto ni siquiera es gracioso. Terminemos con esto, que el amanecer se acerca. Discutiremos la compra de mi fragata mañana.";
			link.l1 = "Tienes razón, lo has conseguido, ¡tres barcos! Incluyendo un auténtico navío de guerra contra la dama más... bueno, costosa del Nuevo Mundo. ¿Puedes siquiera rechazar semejante apuesta?";
			link.l1.go = "Angerran_15_3";
		break;
		
		case "Angerran_15_3":
			dialog.text = "Sería una locura. Aunque, es una locura, monsieur de Maure. Por favor. Pero recuerda, fue tu idea.";
			link.l1 = "¡Esta será la leyenda que saborearán durante un año a puerta cerrada! ¡Oye tú, más vino y velas! ¡El juego debe continuar!";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_16":
			dialog.text = "Recientemente asumiste que este filibote era una apuesta indigna contra nuestros barcos. ¿Qué ha cambiado?";
			link.l1 = "Me aburrí. Añadamos algo de picante a nuestro duelo: tu fragata y mi barco contra...";
			link.l1.go = "Angerran_16_1";
		break;
		
		case "Angerran_16_1":
			dialog.text = "¿El filibote que valoraste tan mal? ¿Acaso tienes fiebre? No te ves muy bien.";
			link.l1 = "Estoy perfectamente bien, gracias. No escuchaste. Apuestas de dos a uno no son tan espectaculares, así es, ¡así que igualemos las probabilidades! No todos los objetos de valor pueden medirse en oro, ¿no estás de acuerdo? ¿O quizás simplemente prefieres no luchar contra el viento, si algo no va según tu plan y cambias de rumbo? Lástima entonces, parece que me equivoqué contigo. Madame Botot, creo que tu salón acaba de recibir otra rica historia sobre las diferencias entre decir y hacer...";
			link.l1.go = "Angerran_16_2";
		break;
		
		case "Angerran_16_2":
			dialog.text = "No intentes ponerme de los nervios, monsieur de Maure, eres demasiado ingenuo para eso.";
			link.l1 = "En efecto. La falta de voluntad no es un pecado... a menos que seas un militar, por supuesto. O un noble, el honor de la familia, como quizá sepas, es una carga a veces. Sin embargo, es poco probable que estés familiarizado con tales dilemas.";
			link.l1.go = "Angerran_16_3";
		break;
		
		case "Angerran_16_3":
			dialog.text = "¿Estás tratando de iniciar un duelo o continuar un juego?";
			link.l1 = "Ambos servirán. Daré crédito a la colección de vinos del Marqués mientras te recompones.";
			link.l1.go = "Angerran_16_4";
		break;
		
		case "Angerran_16_4":
			dialog.text = "Que así sea. Esta noche debe terminar como es debido. ¡Dos grandes barcos contra la vieja bañera llena de plata y la mejor mujer de la Nueva Francia! Respira más profundamente, monsieur de Maure, esta apuesta se convertirá en una leyenda entre los chismes de la alta sociedad.";
			link.l1 = "Vuestra derrota se convertirá en leyenda, de hecho, monsieur de Chievous. ¡Traednos más vino y velas! ¡Hagámoslo!";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_17":
			dialog.text = "Perdiste la cabeza por la suerte, monsieur de Maure. Aquí estás arriesgando, el favor de la falta es breve.";
			link.l1 = "La brevedad del favor es un camino al verdadero amor. Lo mismo puede decirse de la lealtad comprada. Solo conduce al desprecio o al aburrimiento.";
			link.l1.go = "Angerran_17_1";
		break;
		
		case "Angerran_17_1":
			dialog.text = "Vuestros intentos de irritarme me divierten. Sería mejor que le preguntases a la señora Juliana sobre cosas como favores, amor y todo lo demás que puedes comprar o no. Pero date prisa, se va de la ciudad mañana.";
			link.l1 = "Al menos tu conocimiento del tema es unilateral. No puedes ganar el favor de la Dama Fortuna ni ganando ni pagando aquí, por lo tanto no puedes conocer su amor. Se necesita coraje, monsieur, y una voluntad inquebrantable para arriesgarse. Sin mencionar que más... terrenales damas valoran estas cosas también. Llamo a dos de mis barcos contra uno de los tuyos, ¿estás dentro?";
			link.l1.go = "Angerran_17_2";
		break;
		
		case "Angerran_17_2":
			dialog.text = "¿Deseas continuar con tanto entusiasmo? Bien, lo que sea. Pero al menos añadamos algo de drama, monsieur de Maure. ¿Decías algo sobre amor y precios? Propongo igualar nuestras apuestas: esa bañera tuya y el filibote de plata contra mi fragata y la mejor mujer de la Nueva Francia. ¿Qué dices ahora?";
			link.l1 = "¡Yo digo que definitivamente sabéis cómo jugar con estilo, monsieur! ¡Más vino y velas! ¡Vamos!";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_18":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game"); // fix 22-03-20
			npchar.money = 70000; // на 2 кона
			pchar.questTemp.GoldenGirl.Game.G4 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "Angerran_19":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "¡Increíble, monsieur de Maure, esto es simplemente increíble!";
				link.l1 = "Sí, claro, Europa no había conocido tal derrota desde la Batalla de Rocroi, monsieur de Chievous. Un artista que vive en algún lugar dentro de mí tiembla de deseo por retratar tal momento histórico. Es una pena que ya no dibuje como lo hacía en mi juventud. Pero tal vez madame Julianne deba tener un artista talentoso cerca, ¿no es así?";
				link.l1.go = "Angerran_20";
			}
			else
			{
				dialog.text = "Mala suerte, Capitán. No obstante, aprecio su valentía, además hoy estoy de buen humor. Tomaré su oro pero puede quedarse con su barco. Fuera de mi vista y por favor evite apostar en el futuro. Algún día, eso lo matará.";
				link.l1 = "Muy noble de tu parte, no lo esperaba. Adiós, monsieur de Chievous.";
				link.l1.go = "Angerran_14";
			}
		break;
		
		case "Angerran_20":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_30";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_21":
			dialog.text = "No, no entiendes. Esto es tan increíble, que simplemente no puede ser.";
			link.l1 = "Todos hemos visto las cartas, monsieur de Chievous - La Fortuna nunca miente.";
			link.l1.go = "Angerran_22";
		break;
		
		case "Angerran_22":
			dialog.text = "La fortuna no, pero tú, monsieur de Maure, ¡sí! Me parece que detrás de tu insolencia había un plan, no solo pasión. Eres un mentiroso y un tramposo, y estoy listo para confirmarlo ante todos los invitados.";
			link.l1 = "...";
			link.l1.go = "Angerran_23";
		break;
		
		case "Angerran_23":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_32";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_24":
			dialog.text = "";
			link.l1 = "Monsieur de Chievous, ¿lo oí bien? ¿Estás listo para confirmar tus sospechas no solo con palabras? Parece que tus insultos están yendo demasiado lejos y yo, a diferencia de ti, valoro el honor de mi familia.";
			link.l1.go = "Angerran_25";
		break;
		
		case "Angerran_25":
			dialog.text = "Hijo segundo, ¡un tramposo y un estafador no me hablará sobre el honor de la familia! ¡Cállate, Julianne, te hablaré más tarde! Charles de Maure, ¡insisto en que me des satisfacción de inmediato! ¿Espada o pistola?";
			link.l1 = "Ambos. Para ser honesto, me alegra que hayas cambiado de opinión. ¿Recuerdas que te sugerí dar un paseo más allá de las puertas? ¿Qué dijiste sobre mi clase indigna? Tal vez el juego de cartas te regaló algo de valor después de todo.";
			link.l1.go = "Angerran_26";
		break;
		
		case "Angerran_26":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_34";
			sld.greeting = "Marquesa_vecherkonchen";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_27":
			dialog.text = "Demasiado honor, pero estoy de acuerdo con la marquesa. Te acabaré como un noble, de Maure, aunque no merezcas esto. Te desafío a un duelo mañana al mediodía, a través de Su Excelencia el gobernador. Ven a verle tú mismo o envía a tus segundos para discutir los términos. Nos vemos. Señora, mis respetos.";
			link.l1 = "...";
			link.l1.go = "Angerran_28";
		break;
		
		case "Angerran_28":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0); // уходит
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_36";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_29":
			dialog.text = "Y ahí estás, el favorito de la fortuna. ¿Te ocupaste de tus asuntos, espero? ¿No olvidaste confesarte? Dicen que el infierno puede ser bastante incómodo sin eso.";
			link.l1 = "Hablar es barato, monsieur. No sabes jugar bien a las cartas, ahora pongamos a prueba tu habilidad con la espada... ¡Bailemos!";
			link.l1.go = "Angerran_30";
		break;
		
		case "Angerran_30":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ExitTown")], false);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GG_SecundantGG_"+i);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GG_SecundantAG_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocator(sld, "goto", "goto1"+(7+i), "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			}
			LAi_group_Delete("EnemyFight");
			LAi_SetCheckMinHP(npchar, 10, true, "GoldenGirl_Duel"); 
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Angerran_31":
			dialog.text = "Buen.. golpe, maldición. ¡Pero aún vivo!";
			link.l1 = "Tu herida no tiene buen aspecto, pero deberías mostrarte a un médico de todos modos. Claramente, no puedes seguir así, morirás si lo haces. Parece que hemos terminado aquí. Gané, y no hice trampa. Te devolveré tu barco y te irás de San Pedro. Nunca volveremos a vernos.";
			link.l1.go = "Angerran_32";
		break;
		
		case "Angerran_32":
			dialog.text = "¡Qué enorme caballerosidad! Mira, monsieur de Maure, puedes ser un espadachín natural, pero definitivamente hiciste trampa en las cartas. Manipulé la baraja tres veces. ¡Tres veces, maldita sea! Ningún milagro en el mundo podría salvarte, ¡pero ganaste de todos modos! Ojalá supiera cómo lo hiciste... En fin, pronto le contarás al Diablo todo al respecto. ¡Atacad, muchachos!";
			link.l1 = "¡Maldito seas! ¡Te mostré misericordia y así es como me lo pagas! ¡Monsieurs, a las armas!";
			link.l1.go = "Angerran_33";
		break;
		
		case "Angerran_33":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 20.0);
			LAi_RemoveCheckMinHP(npchar); 
            LAi_SetCurHPMax(npchar);
            LAi_SetImmortal(npchar, false); // Captain Beltrop, снимаем проверку на жизнь и восстанавливаем её
			GoldenGirl_DuelNext();
		break;
		
		case "Angerran_34":
			dialog.text = "Admito, Monseniour de Maure, que estoy un poco sorprendido de verte aquí. ¿Eso significa que no me equivoqué contigo y que la salvaje doncella significa algo para ti?";
			link.l1 = "Me pregunto cuál es la postura de tu buen amigo de Lyons sobre el secuestro de oficiales de capitanes respetados de nuestra Armada. ¿Quizás deberíamos invitarlo a unirse a nosotros y contarle toda la historia?";
			link.l1.go = "Angerran_35";
		break;
		
		case "Angerran_35":
			dialog.text = "Eso no te ayudará en lo más mínimo, créeme. Además, traté a tu ramera mejor que a un general capturado. Por ahora. Pero todo puede cambiar y depende de ti, Charles.";
			link.l1 = "No recuerdo que hayamos tenido un trago de amantes contigo. No me vengas con Charles, Monseñor de Chievous. Ve directo al grano y dime qué quieres de mí.";
			link.l1.go = "Angerran_36";
		break;
		
		case "Angerran_36":
			dialog.text = "¿De ti? ¡Nada, Dios me libre! Tú y yo solo resolvimos una pelea desafortunada después de algún escandaloso juego de cartas, tomamos unas copas y salimos de esta habitación como viejos amigos.";
			link.l1 = "Angerran, pareces bien a pesar de tu reciente herida y cada minuto de esta charla inútil me hace querer arreglar eso. Incluso la idea de estropear estas finas alfombras de Francois de Lyons se vuelve cada vez más atractiva para mí.";
			link.l1.go = "Angerran_37";
		break;
		
		case "Angerran_37":
			dialog.text = "Pero el buen viejo Francois ama estas alfombras, Charles. Todo el mundo ama algo. Ya que estás aquí, debes amar a tu pequeña novia en armas. Estoy dispuesto a devolvértela a cambio de mi propiedad. Arruinaste el juego y aunque no suelo perdonar tales transgresiones, puedo hacer una excepción por ti. Me darás el premio que tanto deseo y yo te daré lo mismo. Luego nos separaremos hermosamente. Tanto por amor.";
			link.l1 = "¿Crees que llevo a la marquesa como una maldita joya en mi bolso? ¡Tonterías! ¿Cómo podría dártela?";
			link.l1.go = "Angerran_38";
		break;
		
		case "Angerran_38":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "No me importa en absoluto, Charles. Tienes dos semanas para encargarte de ello. Y sí, quiero que este premio se reciba en secreto. Digamos, algún capitán que haya ganado una cortesana ridículamente cara, pero que no logró ganarse su favor de todos modos, podría hacer algo estúpido al respecto, ¿verdad? ¿Crees que ya estás lo suficientemente desesperado, Charles?";
			link.l1 = "Quiero ver a mi oficial primero para asegurarme de que aún vive.";
			link.l1.go = "Angerran_39";
		break;
		
		case "Angerran_39":
			dialog.text = "Fuera de cuestión. Tendrás que confiar en mi palabra. Ella está en un lugar seguro y se quedará allí hasta que obtenga mi premio. Pero si sigues insistiendo en verla antes de tiempo, con gusto te complaceré enviándote alguna parte de ella. ¿Cuáles son tus favoritas? ¿Una oreja, una nariz, un par de dedos?";
			link.l1 = "Ponle una mano encima, escoria, y te estrangularé con mis propias manos, ¡lo juro por Dios! ¡No me pongas a prueba, maldita sea!";
			link.l1.go = "Angerran_40";
		break;
		
		case "Angerran_40":
			dialog.text = "Tranquilízate. Todo lo que está a punto de suceder es completamente culpa tuya. No me gusta la violencia, la uso solo cuando es necesario. No me obligues. Solo entrégame mi premio en Cabo Scott en Dominica en menos de dos semanas y obtendrás lo que es tuyo. No me importa cómo lo harás. Si quieres robar, roba, al fin y al cabo eres un pirata, solo que bien vestido.";
			link.l1 = "Eres totalmente delirante, hay una gran diferencia entre un pirata y un maldito traficante de esclavos...";
			link.l1.go = "Angerran_41";
		break;
		
		case "Angerran_41":
			dialog.text = "Respira más profundo, estamos a punto de desfilar con estilo frente al viejo François. Somos amigos ahora, ¿recuerdas? Sonríe Charles, ¡vamos! Vamos a separarnos. Cabo Scott, Dominica, en dos semanas. No llegues tarde.";
			link.l1 = "Nos vemos allí.";
			link.l1.go = "Angerran_42";
		break;
		
		case "Angerran_42":
			DialogExit();
			DoQuestReloadToLocation("Baster_townhall", "goto", "goto1", "GoldenGirl_AfterBaster");
		break;
		
		case "Cortny":
			PlaySound("VOICE\Spanish\LE\Cortny\Cortny_01.wav");
			dialog.text = "Buenas noches, señora Botot, capitán de Maure. Le pido que mantenga la calma.";
			link.l1 = "¡Marquesa, detrás de mí, ahora! ¡Monsieur, ¿qué significa esto?!";
			link.l1.go = "Cortny_1";
		break;
		
		case "Cortny_1":
			PlaySound("VOICE\Spanish\LE\Cortny\Cortny_02.wav");
			dialog.text = "Tengo una docena de hombres detrás de la puerta y poderes de emergencia autorizados por vuestro Estado. Los guardias no le ayudarán. Por lo tanto, por favor, guarde su espada, señor. Solo quiero hablar. Por ahora.";
			link.l1 = "Monsieur, ¿quién eres y cómo llegaste aquí?! ¡Deberías explicarte!";
			link.l1.go = "Cortny_2";
		break;
		
		case "Cortny_2":
			dialog.text = "Permitidme que me presente - sir William Cortney, Baronet Cortney. Ahora calmémonos todos y hablemos.";
			link.l1 = "Bien, Señor Cortney, somos todo oídos.";
			link.l1.go = "Cortny_3";
		break;
		
		case "Cortny_3":
			dialog.text = "Por favor, discúlpame por estar escuchando a escondidas, pero las circunstancias actuales no me dejan otra opción. Aunque permanezco anónimo aquí en Saint-Pierre, estoy llevando a cabo una investigación de suma importancia en nombre de la Corona de Inglaterra. Sobre un barco mensajero perdido en el mar. ¿Alguna vez has oído hablar de un bergantín llamado Regina?";
			link.l1 = "No lo he hecho y no sigo tus insinuaciones oscuras, Monseñor. Soy un capitán honesto...";
			link.l1.go = "Cortny_4";
		break;
		
		case "Cortny_4":
			dialog.text = "No me importa un comino tus pequeños tratos turbios, señor. Investigué un poco sobre usted y, para ser honesto, lo hice mi primer sospechoso cuando escuché que visitó Martinica justo después de que el Regina desapareciera. Sin embargo, usted no es un idiota y sus hombres no jugaron con perlas aquí. Por lo tanto, está fuera de mis sospechas, por ahora.";
			link.l1 = "¿Perlas? ¿De qué perlas estás parloteando?";
			link.l1.go = "Cortny_5";
		break;
		
		case "Cortny_5":
			dialog.text = "Perlas seleccionadas a mano, de gran tamaño, de las operaciones de la costa oeste española. Las perlas también son negras, lo que significa que son extremadamente raras, ¿alguna vez has oído hablar de algo así?";
			link.l1 = "Supongo, pero siempre pensé que es solo otra historia de marineros. Igual que las historias sobre El Holandés Errante. Julianne, ¿qué pasa?";
			link.l1.go = "Cortny_6";
		break;
		
		case "Cortny_6":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_104";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_7":
			dialog.text = "Tengo que pedirle que lo presente aquí, señora. Es un asunto de suma importancia. Mientras tanto, usted, señor, debe contarme todo sobre el capitán Moreno. Sospecho que fue él quien le dio esa pista. Estoy muy curioso por conocer su papel en esta obra.";
			if (CheckAttribute(pchar, "questTemp.Portugal"))
			{
				link.l1 = "Moreno no es su verdadero nombre, Monseñor Cortney. Su nombre es Hernando Vásquez, también conocido como el Don Sangriento, un pirata español que solía ser contramaestre del Albatros, la nave del infame Bartolomé el Portugués.";
				link.l1.go = "Cortny_8";
			}
			else
			{
				link.l1 = "Solo intercambiamos un par de palabras. No tengo mucho que contar. Parecía un verdadero lobo de mar.";
				link.l1.go = "Cortny_9";
			}
		break;
		
		case "Cortny_8":
			dialog.text = "Vaya, vaya. ¿Y puedo preguntar cómo lo sabes?";
			link.l1 = "Solía conocer a su capitán. De hecho, fui yo quien lo capturó y lo entregó a los holandeses. Es una larga historia. Es una pena que no atrapara al propio Vásquez en aquel entonces...";
			link.l1.go = "Cortny_10";
		break;
		
		case "Cortny_9":
			dialog.text = "Eres un lobo de mar tú mismo, señor. No creo que no hayas notado más.";
			link.l1 = "Solo un ligero acento, la forma en que se veía y se comportaba. Apuesto a que es español, Monseñor Cortney.";
			link.l1.go = "Cortny_10";
		break;
		
		case "Cortny_10":
			dialog.text = "Eso es un rompe-juegos, señor. Y es malo. Señora, ¿encontró el collar? Déjeme inspeccionarlo\nSí, en efecto, esta es una de las perlas negras españolas. Mire, esta palabrería marinera es bastante real. Todo lo que queda es averiguar cómo ese de Chievous consiguió una de estas. Por cierto, ¿no es él un bastardo del Duque de Levy Vantadur?";
			link.l1 = "Es él, sin duda. Hasta donde sabemos, tuvo tratos con el barón pirata en Le Francois. ¿Quizás le compró esta perla?";
			link.l1.go = "Cortny_11";
		break;
		
		case "Cortny_11":
			dialog.text = "Tal vez sí. Pero no me gusta para nada el rastro español en esto. De todos modos, gracias por tu cooperación. Me temo que debo visitarte de nuevo mañana a la misma hora del día. También pediría la presencia del capitán de Maure. Quizás tenga más preguntas para ti. Debería ir a Le Francois ahora.";
			link.l1 = "Monsieur Cortney, espera. ¿Quizás podría unirme a ti? Jacques Barbazon no ha ganado su apodo por ser una persona amorosa y gentil, además este asunto también tiene cierto interés para mí.";
			link.l1.go = "Cortny_12";
		break;
		
		case "Cortny_12":
			dialog.text = "Capitán, me conmueve su preocupación pero es un no. Esto es un asunto de Estado. ¡El canalla sabe su lugar y no se atrevería a poner una mano sobre el emisario de la Corona, de lo contrario su patético pueblo dejará de existir! Me disculpo por la intromisión nuevamente, señora. Buenas noches.";
			link.l1 = "Nos vemos mañana por la noche, Baronet.";
			link.l1.go = "Cortny_13";
		break;
		
		case "Cortny_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_106";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_14":
			PlaySound("VOICE\Spanish\LE\Cortny\Cortny_03.wav");
			dialog.text = "No te enojes con ella, Capitán. Puedo ser muy persuasiva. Tu historia es impresionante, de verdad. Creo que podría tener un uso para ti.";
			link.l1 = "Pareces contento, ¿cómo te fue en Le Francois?";
			link.l1.go = "Cortny_15";
		break;
		
		case "Cortny_15":
			dialog.text = "Como esperaba, ese barón tuyo fue manso como un cordero. Me contó todo lo que quería escuchar. Como dije, puedo ser extremadamente persuasivo.";
			link.l1 = "";
			link.l1.go = "Cortny_16";
		break;
		
		case "Cortny_16":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_112";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_17":
			dialog.text = "Hoy vine aquí solo, no hay hombres míos detrás de esa puerta. ¡¿Qué demonios?!";
			link.l1 = "Tengo un mal presentimiento sobre esto. ¡Julianne, ponte detrás de mí, ahora! Baronet, ¿acaso los emisarios de la Corona pelean tan bien como hablan?";
			link.l1.go = "Cortny_18";
		break;
		
		case "Cortny_18":
			DialogExit();
			GoldenGirl_CortnyBandosFight();
		break;
		
		case "Cortny_19":
			PlaySound("VOICE\Spanish\LE\Cortny\Cortny_03.wav");
			dialog.text = "¡Sabes manejar una espada, Capitán! Eh, para ser honesto, no fue un paseo por el parque. ¿Quién diablos eran esas personas?!";
			link.l1 = "Deberíamos preguntar a sus amigos - oigo más pasos. Ojalá fueran los guardias...";
			link.l1.go = "Cortny_20";
		break;
		
		case "Cortny_20":
			DialogExit();
			GoldenGirl_CortnyMercenFight();
		break;
		
		case "Cortny_21":
			dialog.text = "¡Increíble! ¿Crees que el bastardo se atrevió a hacer todo esto?! ¡Pagará, lo juro!";
			link.l1 = "Respira. Barbazon se escabullirá de cualquier acusación. Te dirá que fue solo una redada ordinaria de ladronzuelos en una casa adinerada. Además, ¡es un maldito pirata, qué le importan las autoridades! Sin embargo, ahora estoy seguro de que lograste aprender algo verdaderamente valioso. Te pido que compartas este conocimiento conmigo.";
			link.l1.go = "Cortny_22";
		break;
		
		case "Cortny_22":
			dialog.text = "No puedo realmente decir que no, ¿verdad? ¿De lo contrario, el próximo intento podría ser un éxito? Está bien, fingiré que no noté un signo de amenaza en tu tono. Digamos que te estoy devolviendo un favor. Jacques el Amable no vendió perlas a tu noble bastardo. Estaba comprando. Eso es todo.";
			link.l1 = "¿Así que fue de Chievous quien interceptó la Regina? Es un granuja, pero es difícil creer que se rebajaría a la piratería común.";
			link.l1.go = "Cortny_23";
		break;
		
		case "Cortny_23":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_117";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_24":
			dialog.text = "Uno apenas llamaría a la Regina un premio regular de un pirata, Capitán. Suponemos que tenía al menos media docena de perlas negras. Incluso una sola perla negra no tiene precio. Absolutamente tengo que conocer a ese señor de Chievous a toda costa.";
			link.l1 = "Puedo ser de alguna ayuda aquí, Monseniour. Pero déjame aclarar algo primero. No parecía interesarme el collar de madam Botot, por lo tanto, las perlas no son la razón por la que estás aquí. ¿Qué más tenía a bordo la Regina?";
			link.l1.go = "Cortny_25";
		break;
		
		case "Cortny_25":
			dialog.text = "Muy bien, supongo que tendré que contarte más considerando... las circunstancias. Verás, la carga no es tan importante en comparación con el propio barco. El bergantín mensajero la Regina había sido asignado a un puerto de San José, Trinidad. Su capitán solía reunir información y hacía algunos... recados para nosotros\nEl último recado de él fue transportar el botín que nuestros corsarios lograron extraer de las operaciones de perlas españolas. Nos tomó tres años de esfuerzos conseguir esa pista. Las perlas negras son ciertamente significativas, pero perder la Regina es fatal. No fue un accidente, alguien que sabía sobre sus perlas también debió haber sabido sobre el resto.";
			link.l1 = "¡Espléndido, así que al final se trata de negocios de los servicios de inteligencia! ¿Temes que toda la red de espías que construiste esté en peligro? Ahora puedo ver todo el alcance de tus problemas.";
			link.l1.go = "Cortny_26";
		break;
		
		case "Cortny_26":
			dialog.text = "¿Alguna vez has oído hablar de John Thurloe? Es el jefe de la inteligencia de la Corona. Un día estaré en Londres, informándole, personalmente, sobre el destino del Regina. Debo encontrar dónde está la filtración y... encargarme de la fuente. Además, está también ese misterioso capitán Moreno tuyo. ¡Si los españoles rastrearon nuestra red de espionaje colonial, años de arduo y laborioso trabajo se irán al garete!";
			link.l1 = "Sabes que todo eso empieza a tener sentido si miras el panorama completo. Empiezo a pensar que alguien con acento español le contó a de Chievous sobre el Regina y las perlas negras.";
			link.l1.go = "Cortny_27";
		break;
		
		case "Cortny_27":
			dialog.text = "Pensamos igual. No hay mejor manera de explotar una red de espías expuesta. Un incidente diplomático con un hombre de tan alta posición involucrado... Tal incidente puede dañar seriamente las relaciones entre Gran Bretaña y Francia, todo lo que necesitas es proporcionar las pistas correctas y simplemente esperar un escándalo internacional. Tal vez incluso esa pista sobre las perlas negras también nos fue alimentada deliberadamente.";
			link.l1 = "¿Esos malditos castellanos, verdad? Entonces, ¿qué hacemos con de Chievous?";
			link.l1.go = "Cortny_28";
		break;
		
		case "Cortny_28":
			dialog.text = "Para ser honesto, no tengo idea. Si es una provocación española, sería prudente simplemente ignorarla. Pero debo averiguar cómo se enteró de la Regina y qué tan mal se ve para nuestra red en las colonias españolas. También te debo la vida y tengo la intención de pagártela.";
			link.l1 = "Honestidad por honestidad, Baronet. Podría usar cualquier ayuda que pueda obtener. Ya estoy lo suficientemente desesperado como para considerar secuestrar a la marquesa.";
			link.l1.go = "Cortny_29";
		break;
		
		case "Cortny_29":
			dialog.text = "¿Te das cuenta de que así es como de Chievous cubre sus huellas? Será tan fácil cargar toda esa confusión sobre ti, incluida la desaparición del Regina. Por lo tanto, propongo lo siguiente. La marquesa Botot me dijo que de Chievous no asistirá al intercambio y permanecerá a salvo en Basse-Terre. O se dio cuenta del lío en el que se metió o está empezando a sospechar algo. Será tan cuidadoso como un ratón de cocina. Por eso iré contigo a Dominica.";
			link.l1 = "¡Pero su prisionera es mi prioridad, no puedo arriesgar su vida! ¡Es una rehén esperando un intercambio!";
			link.l1.go = "Cortny_30";
		break;
		
		case "Cortny_30":
			dialog.text = "No te preocupes - presionaré a Jacques Dille do Parkuet y conseguiré una orden de arresto para el barco de de Chievous. Dudo que sus hombres sean plenamente conscientes de la situación en la que se encuentran, de lo contrario habrían sido más cuidadosos con esas perlas. Iremos hacia ellos en un bote y les presentaremos la orden directamente.";
			link.l1 = "Sí, recuerdo tu don de coerción, Monseñor, pero es un riesgo. Y uno pesado.";
			link.l1.go = "Cortny_31";
		break;
		
		case "Cortny_31":
			dialog.text = "Tienes toda la razón, pero tendrás que aceptarlo si deseas mi ayuda. Una vez que terminemos en Dominica, iré a Basse-Terre y exigiré al gobernador de Lyon que entregue a tu adversario. Mis poderes lo permiten. No podemos permitir que de Chievous se escape sigilosamente.";
			link.l1 = "¿De veras estás preparado para esto, Monseniour? Podría empezar una guerra, ¿verdad?";
			link.l1.go = "Cortny_32";
		break;
		
		case "Cortny_32":
			dialog.text = "Apuesto a que nunca permitirán que eso suceda. Definitivamente, es un no, ya que ya conocemos la verdad. La política es una puta, Capitán. Prometo que presentaré a de Chievous a las mazmorras británicas, solo para usted personalmente. Eso suena como una solución que incluso su padre consideraría un precio razonable.";
			link.l1 = "No puedo decir que me guste tu plan, pero no veo otro.";
			link.l1.go = "Cortny_33";
		break;
		
		case "Cortny_33":
			dialog.text = "Te aseguro que lo lograremos. Debo ir ahora a ver a un gobernador y dar órdenes a mis hombres. Si ves a la marquesa, dile que puede quedarse con la perla en agradecimiento por su ayuda en la investigación.";
			link.l1 = "Gracias, Baronet. Nos vemos en mi barco, zarpamos pronto.";
			link.l1.go = "Cortny_34";
		break;
		
		case "Cortny_34":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "GoldenGirl_CortnyPassenger", 15.0);
		break;
		
		case "Cortny_35":
			PlaySound("VOICE\Spanish\LE\Cortny\Cortny_02.wav");
			dialog.text = "William Cortney, Barón Cortney, a su servicio. Por el poder que me confiere el Imperio Británico con todo el apoyo de su fiel aliado Francia, su nave queda arrestada. Aquí están los documentos, por favor asegúrese de leerlos y dígale a sus hombres que mantengan las manos alejadas de las armas. Está detenido pero aún no arrestado. Si no hace nada estúpido, será liberado en el primer puerto.";
			link.l1 = "Baronet, debo recuperar a mi... ¡mi oficial!";
			link.l1.go = "Cortny_36";
		break;
		
		case "Cortny_36":
			PlaySound("VOICE\Spanish\LE\Cortny\Cortny_04.wav");
			dialog.text = "No te preocupes, Capitán, la llevaré a tu barco. Te pido que regreses al bote ahora. Tomaré el mando de este barco y navegaré hacia Basse-Terre. Siéntete libre de dejarnos si no tienes intenciones de burlarte de tu archienemigo personalmente. Solo te pido que me transfieras a algunos de tus hombres para ayudarnos a llegar a Guadalupe.";
			link.l1 = "Muy bien, Monseñor. Preferiría que no. Envíale mis peores saludos. ¡Adiós y gracias de nuevo!";
			link.l1.go = "Cortny_37";
		break;
		
		case "Cortny_37":
			DialogExit();
			DoQuestReloadToLocation("Shore27", "goto", "goto13", "GoldenGirl_DominicaCortnyFinal");
		break;
		
		case "Cortny_38":
			PlaySound("VOICE\Spanish\LE\Cortny\Cortny_04.wav");
			dialog.text = "Charles, me alegra verte. Esperaba tu regreso, pero nunca realmente creí en ello.";
			link.l1 = "Asimismo, Baronet. ¿Viniste a visitar a la Marquesa? ¿Dónde está ella, por cierto?";
			link.l1.go = "Cortny_39";
		break;
		
		case "Cortny_39":
			dialog.text = "¿Todavía no lo entiendes, verdad? Ella huyó. Además, Angerran de Chievous te envía sus sinceras disculpas. Logré persuadirlo de que nunca fuiste parte del juego, sino solo otra víctima del mismo. Al igual que él. El buen hombre no se molestó en escribir, pero lamenta profundamente cómo fueron las cosas.";
			link.l1 = "¡Profundamente apenado, ¿no es así?! ¿De qué estamos hablando, Monseñor?";
			link.l1.go = "Cortny_40";
		break;
		
		case "Cortny_40":
			dialog.text = "Tú y yo, pasamos por alto lo principal. ¿Cómo se enteró de las perlas? ¿Quién invitó a ese capitán español a esta misma casa? ¿Quién podría mover al bastardo a perseguir tal premio?";
			link.l1 = "¿En serio? No puede ser...";
			link.l1.go = "Cortny_41";
		break;
		
		case "Cortny_41":
			dialog.text = "Definitivamente puede. La marquesa jugó su papel a la perfección, casi lo logró por completo. Sin embargo, gracias a una investigación nuestra, me acerqué a de Chievous no como a un ladrón y pirata, sino como a una víctima de engaño que es. Se dio cuenta de en qué lo había metido bastante rápido, pero no tenía pruebas y decidió actuar por su cuenta. Sabes lo que pasó después.";
			link.l1 = "¿Quieres decir que todo eso había sido orquestado por la Marquesa? ¡De Chievous lo compró como un infante descuidado!";
			link.l1.go = "Cortny_42";
		break;
		
		case "Cortny_42":
			dialog.text = "Precisamente. ¡La pasión es algo muy peligroso, Charles! ¿Recuerdas aquella noche cuando apostaste en esta misma casa? Angerran iba a obtener las pruebas que necesitaba de la marquesa ganando su patrocinio. Sí, hizo trampa, pero estaba desesperado tras años de pasión sin esperanza terminados por la traición más devastadora. ¡Pero tú te entrometiste, te proclamaste su campeón y tuviste éxito en ese papel! De Chievous pensó que tú y ella estaban de acuerdo. Robó un barco que había perdido contigo para evitar que obtuvieras sus registros. Usó a tu oficial para intentar enfrentarla a ella y a ti, sus enemigos mortales, como él creía.";
			link.l1 = "¡Me he quedado sin palabras!";
			link.l1.go = "Cortny_43";
		break;
		
		case "Cortny_43":
			dialog.text = "¡Ahora sabes cómo es, Charles! La Marquesa es inteligente, de una belleza impresionante y no menos peligrosa. No sé cuánto tiempo manipuló a las mejores personas de Nueva Francia. Muchos años, diría yo. De todos modos, ya no te concierne. Fue un placer verte de nuevo, pero tengo más habitaciones que poner patas arriba, es una gran casa. Probablemente no encontremos nada, pero al menos tenemos que intentarlo. \nUna cosa más antes de que nos separemos. Aquí, toma esto. Un recuerdo para recordar. Quizás se lo regales a tu amiga cuando estés listo. Eres muy afortunado, ¿sabes? Especialmente en comparación con de Chievous, ¡pobre diablo!";
			link.l1 = "Tienes razón, así es. ¡Adiós y que Dios te acompañe en tus búsquedas, Baronet!";
			link.l1.go = "Cortny_44";
		break;
		
		case "Cortny_44":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_Town", "reload", "reload9", "GoldenGirl_SPFinal");
		break;
		
		case "Cortny_45": // фин 3
			PlaySound("VOICE\Spanish\LE\Cortny\Cortny_03.wav");
			dialog.text = "¡Qué bonito día tenemos hoy!, ¿eh Capitán? He oído hablar de tus hazañas, pero nunca imaginé que fueras un pirata banal. ¡Qué insolencia venir a St. John's después de lo que hiciste!";
			link.l1 = "Puede que sea un pirata, eso es muy cierto, señor, pero ¿parezco un idiota? ¿Por qué diablos vendría aquí después de saquear el Mercury y quitarle las perlas españolas?";
			link.l1.go = "Cortny_46";
		break;
		
		case "Cortny_46":
			dialog.text = "Lo admito, esta es la única razón por la que estás teniendo esta conversación ahora en lugar de columpiarte en una soga. Verás, hay un pequeño detalle que ocultamos en este caso. Y no me refiero a la perla que encontramos contigo. Es el nombre de la bergantina.";
			link.l1 = "¿Significado?";
			link.l1.go = "Cortny_47";
		break;
		
		case "Cortny_47":
			PlaySound("VOICE\Spanish\LE\Cortny\Cortny_04.wav");
			dialog.text = "Un bergantín correo, la Regina había sido asignada al puerto de San José durante los últimos dos años. Su capitán reunía información para nosotros y también realizaba... encargos de todo tipo. Oficialmente la estamos buscando con el pretexto de la pérdida del correo diplomático que llevaba. No es una artimaña muy elaborada, lo admito. Aun así, no podrías averiguar el verdadero nombre del barco sin buscar adecuadamente en el camarote del capitán.";
			link.l1 = "Estaba ciego pero ahora veo. Por favor, escúcheme, señor, ¡voy a explicarlo!";
			link.l1.go = "Cortny_48";
		break;
		
		case "Cortny_48":
			dialog.text = "Bueno, esfuérzate más, capitán. Tu vida pende de un hilo.";
			link.l1 = "¡No tengo nada que ver con esta historia de espías! Tampoco los españoles. Tu red está segura, no te preocupes. Sin embargo, tuviste una filtración y alguien la aprovechó. Y luego, me metí en una disputa con ese alguien. Encontré pruebas de su implicación en el asunto del Mercury y quería usarlas para vencerlo.";
			link.l1.go = "Cortny_48_1";
		break;
		
		case "Cortny_48_1":
			dialog.text = "";
			link.l1 = "¡Que Dios sea testigo, pensé en este caso como una acción ordinaria de piratería, ni siquiera podía imaginar que la inteligencia de la Corona tuviera algo que ver con esto! Todo lo que tengo es esta perla, pero sé muy bien cuándo y dónde puedes encontrar más.";
			link.l1.go = "Cortny_49";
		break;
		
		case "Cortny_49":
			dialog.text = "¿Has oído hablar de John Thurloe? Es el jefe de inteligencia de la Corona. Un día estaré en Londres, informándole personalmente sobre el destino del Mercury. Por lo tanto, dame el nombre de ese miserable adversario tuyo.";
			link.l1 = "Angerran de Chievous, Conde de Levy Vantadur bastardo. Supongo que consideraba al Mercury solo como un transportador del botín de los corsarios. Podría haber sabido de las perlas, pero no tenía idea de la conexión con la inteligencia británica.";
			link.l1.go = "Cortny_50";
		break;
		
		case "Cortny_50":
			dialog.text = "¡No decepcionas, Capitán, te lo concedo! ¡Qué elección de entretenimiento y enemigos! Muy bien. ¿Qué otras evidencias además de la perla tienes?";
			link.l1 = "De Chievous tiene una fragata. Yo solía poseerla... solo por una noche, pero logré aprender algo. Es un hombre extremadamente pedante, aprenderás todo sobre su ataque al Mercury de su bitácora. Estoy bastante seguro de que todavía posee una parte del botín también. Tal vez incluso más perlas negras si había más de una.";
			link.l1.go = "Cortny_51";
		break;
		
		case "Cortny_51":
			dialog.text = "Más de una, puedes contar con eso. Nunca pondríamos en riesgo a la Regina por un lote de perlas comunes. Espero que te des cuenta de que absolutamente debo hablar con Monseniour de Chievous. Me importa un comino las perlas, pero debo averiguar más sobre la fuga. Mis superiores me enterrarán si no les entrego una imagen completa.";
			link.l1 = "Me encantaría organizar una reunión para usted, ¡pero debemos darnos prisa! En este mismo momento, la fragata de de Chievous se dirige a Guadalupe, donde su dueño reside actualmente bajo la protección del gobernador. Estoy seguro de que es consciente de lo que ha hecho y huirá del Nuevo Mundo lo antes posible.";
			link.l1.go = "Cortny_52";
		break;
		
		case "Cortny_52":
			dialog.text = "Estas son acusaciones muy serias de personas muy serias, Capitán. ¿Te das cuenta de qué tipo de... tormenta de mierda podría desencadenarse después? ¿Un ataque de bandidos a un barco que enarbola la bandera de un aliado? Esto puede complicar seriamente las relaciones entre dos grandes naciones. Me cuesta imaginar hasta qué punto logró irritarte para que estés dispuesto a arriesgar tanto.";
			link.l1 = "Él me quitó algo, milord. Algo que valoro más que nada. Más que mi vida. Debo arreglar eso. Si conduce a la guerra, entonces estaré sirviendo a mi país bajo su bandera. No obstante, de Chievous obtendrá lo que merece y él es el único que debe ser culpado.";
			link.l1.go = "Cortny_53";
		break;
		
		case "Cortny_53":
			dialog.text = "¿Alguien te ha dicho alguna vez que eres un hombre de gran peligro, Capitán? ¿Listo para empezar una guerra en la mitad del globo para alcanzar tu objetivo? Muy bien, hagámoslo a tu manera. Iré a Basse-Terre contigo. No puedo dejar pasar tal rastro. Enviaré a un escriba para que anote tus pruebas mientras preparo mi navío.";
			link.l1 = "Gracias, señor. ¡Pero no tenemos tiempo que perder aquí, le advierto!";
			link.l1.go = "Cortny_54";
		break;
		
		case "Cortny_54":
			dialog.text = "Capitán de Maure, llegaremos a tiempo, no tengo duda en usted. Sin embargo, si esta aventura no resulta... ¿me entiende? No puedo prometerle ni siquiera una tumba decente.";
			link.l1 = "Sí, milord. Le entiendo completamente.";
			link.l1.go = "Cortny_55";
		break;
		
		case "Cortny_55":
			DialogExit();
			npchar.dialog.currentnode = "Cortny_56";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto13", "Baster_Townhall", "goto", "goto4", "GoldenGirl_ReloadToBaster", 10.0);
		break;
		
		case "Cortny_56":
			dialog.text = "La suerte está echada, Capitán. Exigí una reunión con Angerran de Chievous. Su fragata será registrada inmediatamente a su llegada. François de Lyon tiene sus dudas, pero los sellos en mis papeles lo retienen por ahora. Le pido que se quede en la ciudad hasta que la situación se resuelva.";
			link.l1 = "Claro, milord, entiendo.";
			link.l1.go = "Cortny_57";
		break;
		
		case "Cortny_57":
			dialog.text = "Entonces espero que entiendas esto también. Entrega tu espada a los caballeros de allí y síguelos para que esté seguro de que cumplirás tu promesa.";
			link.l1 = "Increíble... ¿milord Cortney, de veras estás hablando en serio?";
			link.l1.go = "Cortny_58";
		break;
		
		case "Cortny_58":
			dialog.text = "Totalmente serio. Sigues siendo uno de mis principales sospechosos y dejarte ir en estas circunstancias sería muy estúpido de mi parte. Me disculparé contigo de la manera que considere adecuada, cuando y si tus palabras resultan ser ciertas.";
			link.l1 = "";
			link.l1.go = "Cortny_59";
		break;
		
		case "Cortny_59":
			DialogExit();
			GoldenGirl_BasterArest();
		break;
		
		case "comendant":
			dialog.text = "Saludos, monsieur de Maure. ¿Vamos?";
			link.l1 = "Con mucho gusto, ¿cuáles son las reglas? Para ser honesto, estaba demasiado ocupado con la comida y probablemente malinterpreté los términos.";
			link.l1.go = "comendant_1";
		break;
		
		case "comendant_1":
			dialog.text = "Las reglas son simples. 10 000 pesos por carta, jugamos hasta que uno de nosotros se rinda. No se aceptan recibos ni créditos.";
			link.l1 = "Me sirve. Hagámoslo, Coronel.";
			link.l1.go = "comendant_2";
		break;
		
		case "comendant_2":
			DialogExit();
			npchar.money = 70000;
			pchar.questTemp.GoldenGirl.Game.G1 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "comendant_3":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "¡Maldita sea! ¡Nunca más! Muy bien, monsieur de Maure, buena suerte en la próxima ronda.";
				link.l1 = "Es un placer, Coronel. Adiós.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
				{
					dialog.text = "Luchaste bien, pero la Dama Fortuna tenía su propio plan. Adiós, monsieur de Maure. Gracias por el juego.";
					link.l1 = "Sí, supongo que me sobreestimé en esto. Adiós, Coronel.";
				}
				else
				{
					dialog.text = "¡Has decidido renunciar a seguir jugando y así has admitido la derrota! Luchaste gloriosamente, pero la fortuna juzgó de otra manera. Adiós, monsieur de Maure, gracias por el juego.";
					link.l1 = "Sí, supongo que me sobreestimé en esto. Adiós, Coronel.";
				}
			}
			link.l1.go = "comendant_4";
		break;
		
		case "comendant_4":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 20.0);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// Португалец или Васкез
		case "moreno":
			if (CheckAttribute(pchar, "questTemp.Portugal")) // был квест
			{
				if (CheckAttribute(pchar, "questTemp.Portugal.GG1")) // португалец
				{
					dialog.text = "¡Capitán Charles de Maure, qué maldita sorpresa!";
					link.l1 = "¡Capitán. ¡Moreno, mi trasero! ¿Qué te trae por aquí?!";
					link.l1.go = "moreno_1";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Portugal.GG2")) // васкез враждебный
					{
						pchar.questTemp.GoldenGirl.Vaskez = "true";
						dialog.text = "Capitán Charles de Maure, un placer.";
						link.l1 = "¿Nos hemos encontrado antes, monsieur... Moreno?";
						link.l1.go = "moreno_5";
					}
					else // васкез нейтральный
					{
						dialog.text = "Capitán Charles de Maure, mi placer.";
						link.l1 = "¿Nos hemos   encontrado antes, monsieur... Moreno?";
						link.l1.go = "moreno_4";
					}
				}
			}
			else  // васкез нейтральный
			{
				dialog.text = "Capitán Charles de Maure, un placer.";
				link.l1 = "¿Nos hemos visto antes, monsieur... Moreno?";
				link.l1.go = "moreno_4";
			}
		break;
		
		case "moreno_1":
			dialog.text = "Es una larga historia. Lo mismo de siempre, capitán. Puedo ver en tus ojos que tienes preguntas. Solo manténlo en secreto y finge que te burlas de un simple marinero.";
			link.l1 = "Sí, este traje elegante te queda bien, mi simple amigo. Diría que sabes cómo llevarlo.";
			link.l1.go = "moreno_3";
		break;
		
		case "moreno_3":
			dialog.text = "Solo en raras ocasiones, con suerte. El día de hoy. Apostemos, Capitán. La gente está mirando, no es cortés hacerles esperar.";
			link.l1 = "Correcto, hablaremos más tarde. Trato... capitán Moreno, si es tan amable.";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_4":
			dialog.text = "Te conozco un poco, pero esto es irrelevante. Reparte las cartas, Capitán de Maure, la gente quiere un espectáculo.";
			link.l1 = "Curioso. Especialmente tu acento español junto con los elogios de madam Botot hacia ti. Muy bien. Mar contra mar, ¡hagámoslo!";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_5":
			dialog.text = "Te recordé bien. Cuando tú y mi ex capitán atravesaron a mis muchachos en Le Francois. El bastardo recibió lo que merecía de todos modos, no sin tu ayuda, si mal no recuerdo. Pero no esperes mi gratitud, mataste a Franz Garke y no te perdonaré por él.";
			link.l1 = "¿El contramaestre del portugués? ¿El Maldito Don, verdad? Esta noche no hace más que mejorar y mejorar. ¡Vamos a hacerlo!";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_6":
			DialogExit();
			npchar.money = 110000;
			pchar.questTemp.GoldenGirl.Game.G2 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "moreno_7":
			if (!CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win") && !CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
			{
				dialog.text = "¡Decidiste renunciar a seguir jugando y así admitiste la derrota! Supongo que Lady Fortuna tuvo su palabra. Adiós, Capitán.";
				link.l1 = "Igualmente, monsieur Moreno. Gracias por el juego.";
				link.l1.go = "moreno_8";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Portugal")) // был квест
			{
				if (CheckAttribute(pchar, "questTemp.Portugal.GG1")) // португалец
				{
					dialog.text = "Tengo entendido que la Dama Fortuna ha hablado. Adiós, Capitán, tal vez nos volvamos a encontrar.";
					link.l1 = "Asimismo, monsieur Moreno. Gracias por el juego.";
					link.l1.go = "moreno_8";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Portugal.GG2")) // васкез враждебный
					{
						dialog.text = "Tengo entendido que la Dama Fortuna ha hablado. Adiós, Capitán, tal vez nos volvamos a encontrar en diferentes circunstancias, je-je.";
						link.l1 = "Esperando con ansias, monsieur Moreno.";
						link.l1.go = "moreno_8";
					}
					else // васкез нейтральный
					{
						dialog.text = "Eso es. La fortuna ha decidido, Capitán. Adiós.";
						link.l1 = "Adiós, señor Moreno.";
						link.l1.go = "moreno_8";
					}
				}
			}
			else  // васкез нейтральный
			{
				dialog.text = "Eso es. La fortuna ha decidido, Capitán. Adiós.";
				link.l1 = "Adiós, monsieur Moreno.";
				link.l1.go = "moreno_8";
			}
		break;
		
		case "moreno_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 20.0);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "moreno_9":
			dialog.text = "¡Qué agradable verte, señor capitán de Maure! Para ser honesto, esperaba ver cualquier cosa, incluso todo un destacamento de guardias, pero no a ti.";
			link.l1 = "Monsieur Moreno, ¿estáis teniendo algunos problemas con los oficiales locales? Por cierto, es un placer veros también, ¡ja-ja!";
			link.l1.go = "moreno_10";
		break;
		
		case "moreno_10":
			dialog.text = "Yo digo, no se puede rechazar la invitación de nuestras anfitrionas. Al menos, no ese tipo de invitación. Vamos Charles, deja de hacer comedia. La marquesa se aseguró de que yo sepa que ella conoce mi verdadera identidad.";
			link.l1 = "...";
			link.l1.go = "moreno_11";
		break;
		
		case "moreno_11":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_90";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_12":
			dialog.text = "¡Señora, usted es encantadora! Este nuevo amigo suyo ya intentó entregarme una vez. De hecho, no salió muy bien, y en realidad me ha salvado el trasero tantas veces que he perdido la cuenta. De todos modos, ahora le debo una, así que no hay necesidad de amenazas, no se preocupe.";
			link.l1 = "Aprecio esto, Bartholomew. Angerran de Chievous me acorraló en una posición extremadamente incómoda y absolutamente tengo que derribarlo. La vida de... alguien muy querido para mí depende de eso. Confía en mí, esta vez nada me detendrá.";
			link.l1.go = "moreno_13";
		break;
		
		case "moreno_13":
			dialog.text = "¡Basta, Capitán, somos amigos, ¿verdad? ¿Recuerdas aquella carrera a través de la mitad del Archipiélago? Tal hazaña significa mucho para mí. Haré lo mejor que pueda para ayudarte. ¿Has oído hablar del Mercury?";
			link.l1 = "Ahora, ¿qué es eso? ¿Un barco?";
			link.l1.go = "moreno_14";
		break;
		
		case "moreno_14":
			dialog.text = "Un bergantín británico, para ser preciso. Su función era transportar el botín de los corsarios del coronel D'Oyley que saquearon las operaciones españolas de perlas en la Costa Occidental. Las que ocasionalmente pescan perlas negras legendarias, ¿has oído hablar de eso? Si mi fuente de información es fiable, varias de esas perlas habían sido almacenadas en el Mercury. Hace un mes tendí una emboscada entre Martinica y Guadalupe, esperando a esos finos caballeros. ¡Pero fue en vano! Pasamos una semana en el mar hasta que tuvimos que admitir el fracaso.";
			link.l1 = "Vale, así que tu fuente no era fiable después de todo y no obtuviste ningún premio para ti. ¿Qué tiene que ver de Chievous con todo esto?";
			link.l1.go = "moreno_15";
		break;
		
		case "moreno_15":
			dialog.text = "Tuve los mismos pensamientos hasta que descubrí que el Mercury nunca apareció en Antigua. ¡Imagina mi sorpresa cuando lo vieron cerca de Curazao y de ninguna manera podría pasarme cerca de Martinica! ¡Los británicos están furiosos! ¡Imagínate perder tal premio y todo! En cualquier caso, me dio curiosidad y comencé a investigar, sobre ese alguien especial que arruinó la diversión para todos. Tal botín no puede ser vendido rápidamente, así que fui a Le Francois para encontrar al bastardo y obtener lo que me debía.";
			link.l1 = "Tu historia me suena. ¿Alguna vez has oído la palabra 'Karma'? Definitivamente sabes cómo encontrar problemas a tus espaldas. Pero todavía no veo cómo eso puede ser de alguna utilidad para mí.";
			link.l1.go = "moreno_16";
		break;
		
		case "moreno_16":
			dialog.text = "No te apresures, Capitán, estoy a punto de contarte la mejor parte de mi historia. Ese amigo tuyo, mal aseado pero bien vestido, sus muchachos dejaron un rastro notable de grandes perlas en las tiendas locales. Un orgullo de las operaciones de perlas españolas que desperdiciaron en gran cantidad.";
			link.l1 = "...";
			link.l1.go = "moreno_17";
		break;
		
		case "moreno_17":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_92";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_18":
			dialog.text = "¿Escuchaste, capitán?";
			link.l1 = "¿Crees que de Chievous compró perlas robadas a Jacques el Amable y sus muchachos? Me temo que esto... no es suficiente.";
			link.l1.go = "moreno_19";
		break;
		
		case "moreno_19":
			dialog.text = "Lo es, cap. ¡No compró, estaba vendiendo! Hablé con Barbazón sobre esto y me confirmó que compró un lote significativo de perlas perfectas de algún socio suyo. Luego las envió a Europa. También tenemos esa perla negra en el collar y el hecho de que el barco de de Chievous pasó por trabajos de reparación. Los trabajadores me dijeron que su fragata tenía agujeros de doce libras. ¿Quién en su sano juicio atacaría una fragata con semejantes bichos?";
			link.l1 = "¡Suena como nuestro bergantín! Además, recuerdo a de Chievous jactándose de lo rápida que es su fragata. Pero ¿por qué esta locura? Estamos en paz con Gran Bretaña, ¿por qué arriesgar tanto y para qué? Las perlas negras son extremadamente raras, sí, pero no imposibles de conseguir.";
			link.l1.go = "moreno_20";
		break;
		
		case "moreno_20":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_94";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_21":
			dialog.text = "¡Y ahí es donde se equivocó! Los británicos ya habían comenzado una investigación oficial sobre la desaparición del Mercury, aunque la llaman un barco mensajero desaparecido con alguna documentación importante a bordo. Cualquier pista será generosamente recompensada, cualquier responsable será severamente castigado. La mejor parte es que han enviado a un noble oficial especial a Antigua que ahora está incansablemente investigando el caso. No recuerdo su nombre, tan pomposo como su cara arrogante, ¡pero me alegra que no me esté cazando a mí!";
			link.l1 = "¡Eso sí que es algo! Parece que quieren esas perlas negras desesperadamente. Me pregunto cuántas de ellas tenían en el Mercury y cómo todo este conocimiento puede serme útil.";
			link.l1.go = "moreno_22";
		break;
		
		case "moreno_22":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_96";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_23":
			dialog.text = "¿Por qué, la escoria logró cabrearte también, marquesa? ¡Miserable guiñón! ¡Yo también estoy contigo en esto, Capitán de Maure! ¡Nadie se atreve a robar el botín a Bartolomeo el Portugués!";
			link.l1 = "";
			link.l1.go = "moreno_24";
		break;
		
		case "moreno_24":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_98";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_25":
			dialog.text = "Necesito un buen trago después de tanta charla. Marquesa, ya que somos amigos ahora...";
			link.l1 = "No creo que tengan ron en esta casa, Bartholomew.";
			link.l1.go = "moreno_26";
		break;
		
		case "moreno_26":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_100";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_27":
			dialog.text = "¡Sí, claro, solo pon su fragata en la mira de ese investigador británico! ¡Si este es nuestro plan, entonces no reconozco a nuestro buen viejo capitán de Maure!";
			link.l1 = "Te reirás, pero ese es el plan. Necesitaré ayuda de ambos. Señora, usted será prisionera del pirata que contraté - Bartholomew, esa es su parte.";
			link.l1.go = "moreno_28";
		break;
		
		case "moreno_28":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_122";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_29":
			dialog.text = "¡Y sobre esta villanía mía también! ¡Bartolomeo el Portugués nunca secuestró a una mujer!";
			link.l1 = "Y no lo hará, pero así parecerá para los hombres de de Chievous. Además, no hay necesidad de decirles tu nombre. Lleva a nuestra dama a bordo y reúnete con la fragata de Angerran cerca de Cabo Scott. Intercambia a Julianna por mi oficial y regresa a Martinica. Luego espera a la marquesa y a mí.";
			link.l1.go = "moreno_30";
		break;
		
		case "moreno_30":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_125";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_31":
			dialog.text = "Todo esto fue muy fascinante y todo, eres un caballero natural, Charles. Pero ¿cómo diablos se supone que debemos devolverla después del intercambio?";
			link.l1 = "Manejaré esto. No tenemos mucho tiempo, así que dividámonos. Tú y la marquesa iréis a Dominica mientras yo me apresuro a St. John's. Encontraré al Coronel D'Oyley o a ese investigador británico y le diré quién es responsable de la desaparición del Mercury.";
			link.l1.go = "moreno_32";
		break;
		
		case "moreno_32":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_130";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_33":
			dialog.text = "¿Has pensado en el huracán de problemas que seguramente seguirá después de tal incidente, Capitán? En este momento, Antigua es un nido de avispas y me estás diciendo que le lance una piedra. ¡Recuerdo guerras que empezaron por menos!";
			link.l1 = "Un problema a la vez... ¡La traeré de vuelta a toda costa! ¡Deja a de Levy Vantadur resolver todo el desorden por su cuenta si es tan poderoso como dicen! Además, de Chievous tendrá dificultades para explicar cómo Madame Botot terminó a bordo de su barco.";
			link.l1.go = "moreno_34";
		break;
		
		case "moreno_34":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_132";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_35":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "¿Lista? ¡A una oración! Marquesa, ¿estás lista para ser secuestrada?";
			}
			else
			{
				dialog.text = "¿Lista? ¡En una oración! Marquise, ¿cuánto tiempo te tomará empacar?";
			}
			link.l1 = "";
			link.l1.go = "moreno_36";
		break;
		
		case "moreno_36":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_134";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "secundant": // fix 22-03-20
			dialog.text = TimeGreeting()+", monsieur de Maure. Mi nombre es "+GetFullName(npchar)+", y esto es "+GetFullName(characterFromId("GG_SecundantGG_2"))+" Su Excelencia nos pidió que presenciáramos tu duelo con monsieur de Chievous.";
			link.l1 = "Buenas noches, caballeros. Espero que todo salga bien y que nadie muera esta noche. Pero estén preparados para cualquier cosa de todos modos. Este 'caballero' puede ser una decepción.";
			link.l1.go = "secundant_1";
		break;
		
		case "secundant_1":
			dialog.text = "Tu inquietud es infundada. Según los términos preestablecidos de este duelo, bajo ninguna circunstancia los segundos pueden interferir. Pero gracias por advertirnos de todos modos. Tu oponente ha llegado. Buena suerte, Capitán. Su Excelencia me pidió que te dijera que rezará por tu... prudencia.";
			link.l1 = "Estoy seguro, me ayudará bastante. Sea como sea, comencemos.";
			link.l1.go = "secundant_2";
		break;
		
		case "secundant_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto8", "", 5); 
			sld = characterFromId("Angerran");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			for (i=1; i<=2; i++)
			{
				ref chr = characterFromId("GG_SecundantAG_"+i);
				LAi_SetActorType(chr);
				LAi_ActorFollow(chr, sld, "", 10.0);
			}
		break;
		
		case "sailor":
			dialog.text = "Capitán, tenemos un problema. Nuestro barco está... pues, ya no está.";
			link.l1 = "¿Espera, qué?! ¿Cómo, quién? Se suponía que una unidad de guardia completa debía estar apostada en ella, ¡así que de qué demonios estás hablando?!";
			link.l1.go = "sailor_1";
		break;
		
		case "sailor_1":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "No, Cap, no el barco. Ella brilla. La fragata que ganaste ayer, así que ahora también es nuestra, ¿eh? Solo enviamos una tripulación de premio de una docena allí. Dijo que eso sería suficiente.";
			link.l1 = "¡Simplemente para de joder y cuéntame exactamente qué pasó desde el principio!";
			link.l1.go = "sailor_2";
		break;
		
		case "sailor_2":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Ni idea, Capitán. La fragata zarpó en las brumas de la mañana. La guardia notó su ausencia unas horas después cuando la niebla ya no estaba.";
			link.l1 = "¡Simplemente no puede ser! ¡Ella nunca me haría esto! Aunque... maldición, tuvimos una pelea hace poco. ¿Podría ella...?";
			link.l1.go = "sailor_3";
		break;
		
		case "sailor_3":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Uno teme que sea aún peor, Capitán. Los pescadores encontraron a dos de nuestros muchachos del equipo del premio temprano en la mañana. Ambos muertos, con la garganta cortada.";
			link.l1 = "¡Pesadilla maldita! ¡De Chievous! ¡Robó su barco mientras yo estaba ocupado con la marquesa! Espero que ella viva... Si pierde un solo cabello, yo...";
			link.l1.go = "sailor_4";
		break;
		
		case "sailor_4":
			dialog.text = "¿Darás las órdenes a los muchachos para que se preparen, Capitán? Podemos zarpar en dos horas, todos han estado nerviosos toda la mañana, especialmente tu segundo al mando, apenas logramos detenerlo de zarpar tras ellos.";
			link.l1 = "Demasiado pronto para eso. Debo... pensar esto detenidamente y hablar con alguien. ¡Sí! ¡Prepara el barco! Quiero que todos estén listos, zarpamos tan pronto como regrese.";
			link.l1.go = "sailor_5";
		break;
		
		case "sailor_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			GoldenGirl_GirlPrisoner();
		break;
		
		case "off_brothel":
			dialog.text = "Capitán de Maure, ¿qué está pasando? ¿Alguien atacó a la señora?";
			link.l1 = "No deberías haber venido aquí. Bueno, Dios es mi testigo, no quería esto.";
			link.l1.go = "off_brothel_1";
		break;
		
		case "off_brothel_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("GG_PatrolBrl_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GoldenGirl_BrothelAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Cap_Nayad":
			dialog.text = "Monsieur, casi habíamos perdido la esperanza de tenerlo aquí. Veo a la marquesa Botot en su chalupa. Ni siquiera voy a preguntar cómo sucedió. Su compañera lo está esperando. Ella está sana y salva, llévela y váyase al diablo de aquí.";
			link.l1 = "¡Si le pones un dedo encima, destrozaré tu vieja bañera en pedazos!";
			link.l1.go = "Cap_Nayad_1";
		break;
		
		case "Cap_Nayad_1":
			dialog.text = "Qué inesperada muestra de cuidado. No te preocupes, fue tratada como una reina prisionera. Tus amenazas no me preocupan. Por cierto, el Chevalier de Chievous te envía saludos.";
			link.l1 = "Que se joda él y sus saludos. ¿Dónde está mi... oficial? Comencemos el intercambio.";
			link.l1.go = "Cap_Nayad_2";
		break;
		
		case "Cap_Nayad_2":
			DialogExit();
			DoQuestReloadToLocation("Shore27", "goto", "goto13", "GoldenGirl_DominicaAlarmFinal");
		break;
		
		case "Cap_Nayad_3":
			dialog.text = "Monsenior, casi perdimos la esperanza de tenerte aquí. Tu compañera te está esperando. Ella está sana y salva... espera, ¿quién demonios es este? ¿Dónde está la marquesa?";
			link.l1 = "";
			link.l1.go = "Cap_Nayad_4";
		break;
		
		case "Cap_Nayad_4":
			DialogExit();
			LAi_SetActorType(npchar);
			chrDisableReloadToLocation = true;
			GoldenGirl_CortnySetOnDeck();
		break;
		
		case "antigua_officer":
			dialog.text = "Tu espada, señor. Y nada de chanzas, mis muchachos están un poco nerviosos últimamente. No querrás recibir una bala, ¿verdad?";
			link.l1 = "¿Hablas en serio? Está bien, tómalo, pero ten cuidado, cuesta más que tus barracas. ¡Exijo una reunión con el baronet Cortney, su Excelencia!";
			link.l1.go = "antigua_officer_1";
		break;
		
		case "antigua_officer_1":
			dialog.text = "No te preocupes, estoy seguro de que encontrará algo de tiempo para hacerte una visita.";
			link.l1 = "Cuando intentas ayudar a alguien...";
			link.l1.go = "antigua_officer_2";
		break;
		
		case "antigua_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("SentJons_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 1, 0, 10); //крутим время
			RecalculateJumpTable();
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_45"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto13");
			DoQuestFunctionDelay("GoldenGirl_CortnyInJail", 10.0);
			bDisableCharacterMenu = true;//лочим F2
		break;
		
		case "baster_officer":
			dialog.text = "No me gusta esto tampoco, Monseñor. Ay, este insolente británico tiene tal autoridad que ni siquiera Monseñor de Lyon puede hacer mucho al respecto. Me disculpo, Capitán, entregue su espada por favor.";
			link.l1 = "Espero que Monsieur de Chievous no comparta la misma celda conmigo. Vamos, caballeros, estoy muerto de cansancio. Finalmente, algo de sueño.";
			link.l1.go = "baster_officer_1";
		break;
		
		case "baster_officer_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("Baster_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			RecalculateJumpTable();
			sld = characterFromId("Cortny");
			sld.lifeday = 0; // Captain Beltrop, убираем Кортни
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_136"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "Baster_prison", "goto", "goto13");
			DoQuestFunctionDelay("GoldenGirl_JuliannaInJail", 7.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "24");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
		break;
		
		case "statist_1":
			dialog.text = "No quiero parecer descortés, monsieur, pero no tengo tiempo para hablar ahora, ya ves lo que está pasando. ¡No quiero perderme nada!";
			link.l1 = "Como desees, monsieur.";
			link.l1.go = "statist_1a";
		break;
		
		case "statist_1_1":
			dialog.text = "¡Esta velada pasará a la historia, lo siento! ¡La gente lo discutirá desde aquí hasta Versalles! Mi Marianne estará encantada y querrá saber todos los detalles. Por favor, monsieur, apártese, está bloqueando mi vista.";
			link.l1 = "Ya me voy, monsieur, disfruta del espectáculo, y saluda a la inolvidable Marianne... quienquiera que sea.";
			link.l1.go = "statist_1a";
		break;
		
		case "statist_1a":
			DialogExit();
			npchar.dialog.currentnode = "statist_1_1"; 
		break;
		
		case "statist_2":
			dialog.text = "¡Ja! ¡Así que aquí está monsieur de Maure! Perdóneme... ¡capitán Charles de Maure! Únase a mí, por favor, aquí hay una magnífica selección de vinos del buen Viejo Mundo. ¿Con qué quiere comenzar la velada: hay una novedad - Cabernet Sauvignon de las orillas de nuestra amada Gironda, o la clásica imperecedera - Sangiovese italiano?";
			link.l1 = "Gracias, monsieur, beberé contigo, pero un poco más tarde.";
			link.l1.go = "statist_2a";
		break;
		
		case "statist_2_1":
			dialog.text = "Oh, ¡capitán de Maure! ¿Te gustaría un poco más de vino... hipo? Mira lo que nos acaban de servir: Syrah del año 1643, recién traído de las colinas del norte del Valle del Ródano. ¡Esto es, maldita sea, una verdadera joya! Y el año fue excelente en todos los aspectos, te digo... ¡una sola derrota de los españoles en el Cabo Gat lo vale! Por cierto... ¿por qué todos se agitan así, sabes? ¿Alguien se siente mal? Bueno - lo que sea, ¡salud...";
			link.l1 = "Bueno, al menos alguien rinde homenaje a las delicias. Au Revoir, Monsieur.";
			link.l1.go = "statist_2a";
		break;
		
		case "statist_2a":
			DialogExit();
			npchar.dialog.currentnode = "statist_2_1"; 
		break;
		
		case "statist_3":
			dialog.text = "¡Oh, capitán Charles de Maure, he oído hablar de usted, como todos en esta ciudad! Permítame presentarme, "+GetFullName(npchar)+", ¡conocerte es un gran honor, créeme! ¿De verdad tienes buenas relaciones con nuestro gobernador? ¿Puedes presentarnos? Quiero expresar mi más profundo respeto hacia él y...";
			link.l1 = "Tal vez más tarde. Que tengas una buena noche, monsieur.";
			link.l1.go = "statist_3a";
		break;
		
		case "statist_3_1":
			dialog.text = "Monsieur de Maure, ¿has visto esto?! Nuestro estimado gobernador y monsieur de Chievous él mismo, ¡pensé que se matarían aquí mismo! ¡Grandioso! La marquesa Botot se ha superado hoy, ¡es todo tan malditamente emocionante! Estoy impaciente por la continuación. Por cierto, ¿quizás ahora es el momento adecuado? Me prometiste presentarme... ";
			link.l1 = "No recuerdo haber prometido nada. Lo siento, pero tengo que irme.";
			link.l1.go = "statist_3a";
		break;
		
		case "statist_3a":
			DialogExit();
			npchar.dialog.currentnode = "statist_3_1"; 
		break;
		
		case "statist_4":
			dialog.text = "Monsieur de Maure, ¡por fin llegaste al salón de la brillante madame Botot! Ya ha rumoreado un par de veces que quería verte. ¿Lograste evaluar a sus 'alumnos'? Sí, estrellas como la marquesa no son para simples mortales como tú y yo. Pero créeme: estas damas son verdaderas obras de arte. Quizás, menos asombrosas, pero aún así - como Miguel Ángel y, digamos, Tiziano.";
			link.l1 = "Una comparación interesante, monsieur. Bien, te dejo para que disfrutes de la noche....";
			link.l1.go = "statist_4a";
		break;
		
		case "statist_4_1":
			dialog.text = "No, siempre es divertido aquí, pero ahora el aire claramente huele a un escándalo lujoso, ¿lo sientes? Lady Jacqueline me espera arriba, pero aún no puedo alejarme de las mesas de juego. Su Señoría y monsieur de Chievous son oponentes dignos y están extremadamente decididos. ¡Parece que las apuestas hoy no solo volarán a las estrellas, sino que romperán el firmamento hasta los diablos!";
			link.l1 = "Los demonios están abajo, monsieur. Debe haber ángeles detrás del firmamento del cielo.";
			link.l1.go = "statist_4a";
		break;
		
		case "statist_4a":
			DialogExit();
			npchar.dialog.currentnode = "statist_4_1"; 
		break;
		
		case "statist_5":
			dialog.text = "¡Bueno, al menos una reunión agradable! Ya nos hemos conocido, capitán de Maure, pero difícilmente lo recuerde. "+GetFullName(npchar)+" - Yo era el capitán de la sexta compañía de infantería de la guarnición, luché contigo en nuestras calles contra los españoles. En verdad, me llevé una bala en la rodilla y la mayor parte de la batalla estuve admirando cómo se quemaba este mismo burdel, mientras yacía en una zanja. Ahora aquí, de nuevo un civil, y de nuevo lo admiro, pero ahora desde dentro.";
			link.l1 = "Encantado de conocerte, monsieur. Ese día fue realmente caluroso, pero admito que, desde ese día, ¡este lugar se volvió significativamente más hermoso!";
			link.l1.go = "statist_5a";
		break;
		
		case "statist_5_1":
			dialog.text = "¿Y cómo te gusta la atmósfera aquí, capitán? ¡Parece que estos tontos seculares decidieron hacer un maldito lío! Interesante, ¿puede jugarse la silla del gobernador como una apuesta en cartas? Recuerda mis palabras: esto terminará con acero. Es una pena, con mi rodilla, tales entretenimientos ya no son para mí. Sin embargo, en algún lugar vi a Jacqueline - su caballero está seriamente apasionado por lo que está sucediendo... Supongo que iré a probar mi suerte, mientras todo está todavía tranquilo aquí.";
			link.l1 = "Buena decisión, te deseo éxito, monsieur. Y tengo que volver a... idiotas.";
			link.l1.go = "statist_5a";
		break;
		
		case "statist_5a":
			DialogExit();
			npchar.dialog.currentnode = "statist_5_1"; 
		break;
	}
} 
