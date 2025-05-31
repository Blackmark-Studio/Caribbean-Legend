// Элен МакАртур - сомнительная любовь и офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "¿Qué es?";
			link.l1 = "No, no es nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "After_boarding":
			dialog.text = "¡Gracias por tu ayuda, capitán!";
			link.l1 = "¡Dios mío... Eres incluso más hermosa de lo que imaginé!";
			link.l1.go = "After_boarding_1";
		break;
		
		case "After_boarding_1":
			dialog.text = "¡Al diablo con mi belleza! ¿Sabes cuánto sufrimiento me ha causado? Me cortaría la nariz si no fuera a destruir mi reputación. Ese bastardo no me dejaría salir del corbeta con vida, seguía diciendo que 'sabía demasiado'. Luego ayer me dijo que estaba cansado de esperar y que iba a tomarme por la fuerza.\n¡No podías haber llegado en mejor momento! Pero, ¿dónde están mis modales?, mi nombre es Helen McArthur. Mi papá solía llamarme Rumba porque siempre rompía accidentalmente la fina porcelana que había 'adquirido', así que ahora así me llama mi tripulación.";
			link.l1 = "Mi nombre es "+GetFullName(pchar)+" y estoy aquí para rescatarte. He estado recorriendo el Caribe durante varios días buscándote por el bien de la Srta. Gladys.";
			link.l1.go = "After_boarding_2";
		break;
		
		case "After_boarding_2":
			dialog.text = "¿Señorita Gladys!? ¿Cómo está ella?";
			link.l1 = "Preocupada hasta la médula por ti. Pero la verás pronto, estamos navegando hacia Blueweld. Puedes contarme todo lo que te ha pasado en el camino.";
			link.l1.go = "After_boarding_3";
		break;
		
		case "After_boarding_3":
			dialog.text = "Para ser honesta, "+pchar.name+", me gustaría comer algo y echarme una siesta ahora mismo. Estoy agotada después de todos esos días que pasé en el barco de ese monstruo...";
			link.l1 = "Por supuesto, Sra. McArthur. Ordenaré al mayordomo que le sirva una comida y prepare una cama para usted en sus aposentos privados.";
			link.l1.go = "After_boarding_4";
		break;
		
		case "After_boarding_4":
			DialogExit();
			LAi_SetActorType(npchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			npchar.greeting = "helena_2";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.Saga = "returntoblueveld";
			Island_SetReloadEnableGlobal("Antigua", true);//на остров можно
			bQuestDisableMapEnter = false;//открыть карту
			AddQuestRecord("Saga", "11");
			pchar.quest.Saga_returnBlueveld.win_condition.l1 = "location";
			pchar.quest.Saga_returnBlueveld.win_condition.l1.location = "Santacatalina_town";
			pchar.quest.Saga_returnBlueveld.function = "Saga_returnBlueveld";
			SetFunctionTimerCondition("Helena_ReturnOver", 0, 0, 45, false);
			sld = characterFromId("gladis");
			sld.greeting = "gladis_3";
		break;
		
		case "Return_blueveld":
			pchar.quest.Helena_ReturnOver.over = "yes";
			dialog.text = "Capitán de Maure, le agradezco de nuevo desde el fondo de mi corazón por su oportuno rescate. Debe visitarme a mí y a mi madre. Nuestra casa no está lejos de aquí, a su izquierda viniendo desde el muelle. Y sepa esto "+pchar.name+"¡Nunca te perdonaré si zarpas sin despedirte!";
			link.l1 = "El placer fue todo mío, Srta. McArthur. ¡Me aseguraré de visitarla!";
			link.l1.go = "Return_blueveld_1";
		break;
		
		case "Return_blueveld_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseSp3", "SantaCatalina_houseSp3_bedroom", "goto", "goto1", "OpenTheDoors", -1);
			AddQuestRecord("Saga", "13");
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", false); // открыть кабинет Свенсона
			pchar.questTemp.Saga = "svenson";//идем к Свенсону
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl";
			npchar.dialog.currentnode = "Helena_wait";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_regard";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//закрыть спальню Элен
			// закрыть город до беседы с Глэдис
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);
		break;
		
		case "Helena_wait":
			dialog.text = "¡Ah, ahí estás, Capitán de Maure! Estoy tan contenta de que estés aquí, tengo muchas preguntas para ti.";
			link.l1 = "Lamento, señorita McArthur, pero debemos retrasar un poco nuestra conversación. Necesito obtener más información antes de poder ofrecer respuestas satisfactorias. Por ahora, le pido que no se muestre en la calle. Espero que su espera no sea larga. Confíe en mí y espere.";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.CanDrink")) {
				link.l1.go = "drinking_refuse";
				link.l2 = "Dijiste tú mismo que no me perdonarías si no pasara por aquí.";
				link.l2.go = "drinking_accept";
				
				DeleteQuestCondition("HelenDrinking_NoVisit");
				DeleteAttribute(pchar, "questTemp.HelenDrinking.CanDrink");
			} else {
				link.l1.go = "exit";
				NextDiag.TempNode = "Helena_wait";
			}
		break;
		
		case "Helena_hire":
			dialog.text = "¡Ah, ahí estás, mi capitán! ¡Tus ojos me dicen que tienes noticias para mí!";
			link.l1 = "El capitán Svenson me dijo que quieres navegar conmigo. Aprecio tu deseo, además la señorita Gladys mencionó que extrañas el mar. ¡Bienvenida a bordo, señorita Helen McArthur!";
			link.l1.go = "Helena_hire_1";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend"))
			{
				link.l2 = "El Capitán Svenson me dijo que quieres navegar conmigo. Aprecio tu deseo, además la Sra. Gladys mencionó que has echado de menos el mar. ¡Bienvenida a mi tripulación, Sra. Helen Sharp!";
				link.l2.go = "Helena_hire_2";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 2;
			}
		break;
		
		case "Helena_hire_1":
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			dialog.text = "¡Aye aye, capitán! Odio tener que decir esto, señor, pero puedo defenderme y no toleraré que los hombres se tomen libertades. No me hago responsable de manos cortadas o ojos arrancados.";
			link.l1 = "No te preocupes, tengo una disciplina inquebrantable en mi barco. Sin embargo, debo preguntarte algo...";
			link.l1.go = "Helena_hire_1_1";
		break;
		
		case "Helena_hire_1_1":
			dialog.text = "...¿Sí?";
			link.l1 = "Jan Svenson y yo hemos descubierto que eres el legítimo heredero de Isla Tesoro. ¡Sí, es cierto, no sacudas la cabeza! Tengo la mitad del mapa que prueba tus derechos. No será fácil, pero Jan y yo haremos todo lo posible para ayudarte a convertirte en el legítimo propietario.";
			link.l1.go = "Helena_hire_1_2";
		break;
		
		case "Helena_hire_1_2":
			dialog.text = ""+pchar.name+", ¿hablas en serio? ¡No es amable burlarse así de una pobre chica! ¿Cómo puedo tener derecho a la propiedad de toda una isla?!";
			link.l1 = "Soy absolutamente serio, Sra. McArthur. Y voy a ayudarte a obtener tu derecho de nacimiento. ¡Zarpemos ahora!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_2":
			dialog.text = "¿Q-qué dijiste? ¿Helen Sharp? ¿Por qué Sharp?";
			link.l1 = "Helen, eres la hija de Beatrice Sharp y la única heredera de la dinastía Sharp. Esta es la mitad del mapa que la señora Gladys ha guardado todos estos años. Es la prueba de tus derechos sobre Isla Tesoro. No será fácil, pero Jan Svenson y yo haremos todo lo posible para ayudarte a heredar la isla de tu abuelo.";
			link.l1.go = "Helena_hire_3";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 3;
			notification("Helen approves", "Helena");
			npchar.lastname = "Sharp";
		break;
		
		case "Helena_hire_3":
			dialog.text = "Oh... ¡Mi pobre madre! Ojalá pudiera encontrar su tumba algún día y rezar por su alma allí. Pero... ¡espera! ¡Imposible!";
			link.l1 = "¿Qué sucede, Sra. Sharp?";
			link.l1.go = "Helena_hire_4";
		break;
		
		case "Helena_hire_4":
			dialog.text = "La profecía de la gitana acaba de hacerse realidad... Finalmente la entiendo ahora.";
			link.l1 = "¿Eh? ¿Qué profecía?";
			link.l1.go = "Helena_hire_5";
		break;
		
		case "Helena_hire_5":
			dialog.text = ""+pchar.name+", podrías llamarme ingenua, pero te lo diré de todos modos. Cuando era una niña, una gitana me dijo: 'Tu destino estará en manos del hombre que no tomará la moneda de la viuda, que devolverá el oro del muerto y que nombrará a la madre'\nPensé que todo eso eran tonterías en aquel entonces, pero de alguna manera has logrado cumplir cada parte de la profecía, ¡no hay manera de que supieras eso!";
			link.l1 = "Tu destino, dices... Bueno, tal vez tengas razón. No te decepcionaré. Buscaremos juntas la tumba de tu madre. Y por ahora... ¡Señorita Helen Sharp! ¡Prepárate para la partida y no llegues tarde!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_6":
			dialog.text = "¡Aye-aye, capitán!";
			link.l1 = "...";
			link.l1.go = "Helena_hire_add";
		break;
		
		case "Helena_hire_add":
			LAi_SetImmortal(npchar, false);
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_HireHelena", -1);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);//открыть выходы из города
			pchar.questTemp.Saga = "svenson_wait";
			AddQuestRecord("Saga", "24");
			AddQuestUserData("Saga", "sTimer", AddDaysToDateString(367));
			if(bImCasual) NewGameTip("Modo exploración: el temporizador no está desactivado. ¡Cumple el plazo!");
			SetFunctionTimerCondition("Saga_BaronsQuestsGo", 0, 0, 2, false);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			
			if (pchar.questTemp.HelenDrinking.Result != "no_visit") {
				AddQuestRecord("HelenDrinking", "3");
				
				SetFunctionLocationCondition("HelenDrinking_IslaTesoroAmbush", "Pirates_town", false);
				sld = &locations[FindLocation("Pirates_town")];
				sld.locators_radius.quest.detector1 = 4.0;
			}
		break;
		
		//-->  консультации по морским сражениям в искушении барбазона
		case "sea_bomb":
			dialog.text = "Capitán "+pchar.name+"¡Tengo una idea...";
			link.l1 = ""+npchar.name+"¿No es seguro aquí y te dije que te quedaras en el barco...?";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = "¡Charles, hay tanta pólvora metida en esta vieja bañera que si explota, toda la isla volará directamente a la puerta de San Pedro! No importa si me dices que me esconda o no, ¡así que escúchame!";
			link.l1 = "¡Bien, habla rápido!";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "La corbeta y la fragata. No reconocen el barco de Knive como hostil. Podemos usar su complacencia en contra de ellos. Tomemos algunos barriles de pólvora, coloquemos una mecha y navegaremos hacia los barcos\nNos dejan acercarnos, encenderemos la mecha, dejaremos caer el barril en uno de ellos y nos alejaremos lo más rápido posible. Y luego veremos una explosión espectacular... ¿Qué dices?";
			link.l1 = "Un barco de fuego improvisado... ¡muy astuto! Tu plan es lo suficientemente loco como para que tal vez funcione... si logramos acercarnos lo suficiente sin ser reconocidos.";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "¿Qué tenemos que perder "+pchar.name+"¿No será fácil luchar contra dos barcos a la vez, pero tendremos la oportunidad de igualar las probabilidades...?";
			link.l1 = "Está bien. ¡Sigamos con esto! ¡Muchachos! ¡Tomen tres barriles de pólvora! ¡Vamos a largarnos de aquí al demonio! Me encanta tu imaginación, "+npchar.name+"... Nunca se me habría ocurrido esta idea por mí misma.";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			pchar.questTemp.Saga.BarbTemptation.adviser = "Helena";
		break;
		
		case "fugas":
			dialog.text = "Sí, capitán, ¿cuál es el asunto?";
			link.l1 = "El barco de Jackman está en la Cueva de Sabo-Matila, la fragata pesada 'Centurion'. Este barco fue una vez propiedad de los Hawkes, así que debe haber objetos importantes y documentos en el camarote de Jackman...debemos abordarlo.";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "Más fácil decirlo que hacerlo. ¿Cómo piensas hacer eso en nuestra polacra? Nos superan en hombres y en armas.";
			link.l1 = "Tienes razón. Jackman tiene al menos el doble de hombres que nosotros y todos ellos son espadachines experimentados. Sería una locura atacarlos sin un bombardeo preliminar. Pero una lucha prolongada tampoco es la mejor opción. Así que he estado pensando en qué hacer.";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = ""+pchar.name+", aún no nos han reconocido como enemigos, igual que esos idiotas en los Turcos... Podemos intentar nuestro truco de nuevo...";
			link.l1 = "Helen, acabo de decirte que tenemos que abordar y registrar la fragata, volarla al diablo no es una opción.";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "Espera un minuto, "+pchar.name+", no la hundiremos. Vamos a darle un giro. Escucha, vamos a tomar algunos barriles vacíos de ron y llenarlos con pólvora, metralla y mechas cortas. Luego, nos acercaremos a su fragata y lanzaremos los explosivos improvisados sobre su cubierta.";
			link.l1 = "¡Ja! ¡Tu ingenio femenino sigue sorprendiéndome! ¿En lugar de un barco incendiario, sugieres una fougasse? ¿Crees que podría funcionar?";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "¿Y por qué no? Su francobordo es más alto que el nuestro, pero dos o tres hombres ayudados por una polea podrían izar y lanzar un barril completamente cargado fácilmente. Gritaremos: '¡Aquí hay ron gratis de Knive!' Y los barriles explotarán antes de que puedan siquiera reaccionar.";
			link.l1 = "La metralla explosiva convertirá a sus mejores hombres en la cubierta en picadillo... Maldita sea, suena tentador.";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "Lancemos cinco barriles a la vez desde el alcázar hasta la toldilla. "+pchar.name+", tenemos el elemento sorpresa. ¡No sospecharán nada aún! Y luego zarparemos inmediatamente antes de que tengan la oportunidad de abordarnos.";
			link.l1 = "Bien, intentémoslo. No deben identificarnos antes de que pongamos esos barriles explosivos en su cubierta... No será fácil acercarse. Jackman no es tan gran tonto como lo fue Ghoul.";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "Apostemos, "+pchar.name+"¡Como dije antes, ¿qué tenemos que perder?";
			link.l1 = "Buen punto... ¡A sus puestos, muchachos! ¡Preparen las fougasses y prepárense para luchar!";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		//<--  консультации по морским сражениям
		
	// --> разговор по итогам Саги
		case "result":
			//if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) // не друзья
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 11) {
				Achievment_Set("ach_CL_83");
			}
			
			if (sti(pchar.questTemp.Saga.HelenRelation) < 6)
			{
				dialog.text = "Bueno, mi querido capitán... Es hora de que nos despidamos. Mi servicio ha terminado y es momento de acostumbrarme a ser la Reina Pirata de Isla Tesoro. Espero ser una digna sucesora de mi tío. Gracias por tu ayuda.";
				link.l1 = "Sí, es una lástima separarnos, pero tales son los caprichos del destino. Ahora tienes responsabilidades mucho más importantes que servir en mi barco.";
				link.l1.go = "result_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Mary")) {
					dialog.text = "Me encantaría poder quedarme en tu barco. Cerca de ti... Pero es imposible. Sé feliz, Charles. ¡Y que ella sea digna de ti!";
					link.l1 = "Lo siento, Helen.";
					link.l1.go = "result_mary";
				} else {
					dialog.text = "Es tan extraño, "+pchar.name+"¡Acabo de convertirme en dueña de toda una isla, pero no me siento como la Reina de Isla Tesoro... Supongo que un nuevo jefe de la Hermandad manejará la colonia mejor de lo que lo haría yo. Tengo mucho que aprender.";
					link.l1 = "No te preocupes por eso, Helen, eres una mujer que puede cuidarse sola - tal como me dijiste cuando subiste a bordo por primera vez.";
					link.l1.go = "result_9";
				}
			}
			
			DeleteQuestCondition("HelenDrinking_AtSHDN");
			DeleteQuestCondition("HelenDrinking_InBlueweldAfterCave");
		break;
		
		case "result_mary":
			dialog.text = "Bueno, seguiremos siendo amigos, ¿no?";
			link.l1 = "Por supuesto... Helen, nos encontraremos de nuevo en Isla Tesoro. ¿Debería llevarte a tu isla?";
			link.l1.go = "result_12";
		break;
		
		case "result_1":
			dialog.text = "Tienes razón... Mira, guardé mi parte del botín mientras navegaba en tu barco. Tómalo y ni siquiera intentes rechazar mi oferta, no quiero estar en deuda contigo.";
			link.l1 = "Eh ahora, espera un momento...";
			link.l1.go = "result_2";
		break;
		
		case "result_2":
			dialog.text = "Ya sé lo que vas a decir. Claro, tu ayuda fue mucho más significativa que este mísero cofre de tesoros. Pero esto es todo lo que tengo en mi posesión ahora y debo compensarte. Tómalo, si no lo aceptas tú mismo, lo dejaré en tu camarote.";
			link.l1 = "¿Vas a navegar por tu cuenta ahora? ¿Quizás podría llevarte a Isla Tesoro?";
			link.l1.go = "result_3";
		break;
		
		case "result_3":
			GiveItem2Character(pchar, "chest");
			Log_Info("Has recibido un cofre con doblones");
			PlaySound("interface\important_item.wav");
			dialog.text = " No hay necesidad de eso, "+pchar.name+". Llegaré a la isla por mi cuenta. Tengo mi espada y pistola conmigo, me bastará por un tiempo... Estoy segura de que la Reina de Isla Tesoro no tendrá que preocuparse por los ingresos una vez que llegue allí.";
			link.l1 = "Sí, sí, su majestad. Le deseo suerte en su nueva vida.";
			if (!CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "result_4";
			else link.l1.go = "result_7";
		break;
		
		case "result_4":
			dialog.text = "  Basta de eso, incluso en broma. Sigo siendo Helen para ti. Pero eso no es todo lo que quería decir. He encontrado a mi padre de nuevo, aunque fue un poco extraño. Ha pagado con su buen nombre de noble inglés por mi herencia y eso me molesta. La Mancomunidad Inglesa lo caza y no quiero que tú, "+pchar.name+",  participar en ello.";
			link.l1 = "¡Recobra el sentido, Helen! ¡Él es un bandido y un pirata!";
			link.l1.go = "result_5";
		break;
		
		case "result_5":
			dialog.text = "¿Pirata? ¿Y quién demonios eres tú para decir algo así? ¡Él es mi padre y eso es lo que me importa! Y yo, la hija de un bandido y un pirata, no me importa un carajo lo que la justicia inglesa piense de él. Si intentas hacerle daño a mi padre de alguna manera, olvidaré todo lo bueno que has hecho por mí, que lo sepas. Considera esto una advertencia.";
			link.l1 = "¿Es así? En realidad, chica, harías bien en ser más educada. ¡No noté ninguna queja de tu parte sobre mi actitud pirata mientras salvaba tu bonita piel de las manos de ese violador Donovan, o cuando compartíamos las ganancias de nuestras capturas!";
			link.l1.go = "result_6";
		break;
		
		case "result_6":
			dialog.text = "Yo... lo siento. Lo retiro, perdóname. Perdí la cabeza... Pero aún así, me gustaría seguir siendo tu amiga, lo cual sería imposible si comienzas a perseguir a mi padre.";
			link.l1 = "Entendido. Pero nunca te atrevas a amenazarme, mujer. Deberías saber ya, después de navegar en mi barco, que no temo a nadie ni a nada. Especialmente no toleraré la falta de respeto de una mujer, sea Reina Pirata o no. Puedo ser un caballero, pero incluso mi paciencia tiene sus límites. Ahora que esto está resuelto, adiós. Te deseo suerte.";
			link.l1.go = "result_8";
		break;
		
		case "result_7":
			dialog.text = "Gracias.... Tal vez nos volvamos a encontrar, "+pchar.name+"...";
			link.l1 = "¿Y por qué no? Visitaré Isla Tesoro más de una vez en el futuro. Nos vemos allí... Adiós, Helen.";
			link.l1.go = "result_8";
		break;
		
		case "result_8": // Элен уходит, но её не затираем
			DialogExit();
			RemovePassenger(pchar, npchar);
			//chrDisableReloadToLocation = true;//закрыть локацию  // уже не надо.
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto24", "", "", "", "", 7);//OpenTheDoors лесник . чтобы бежала и исчезла а не стояла.
			AddQuestRecord("Testament", "11");
			CloseQuestHeader("Testament");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться		
			if (CheckAttribute(pchar, "questTemp.LSC.MaryWait")) {
				pchar.questTemp.LSC.Mary = "return";
			}
		break;
		
		case "result_9": // вот тут - ключевой момент, если игрок нашёл Мэри - выбирай, какая девушка милее
			dialog.text = "Estoy segura. "+pchar.name+", Me gustaría quedarme en tu barco si me lo permites. Quedarme contigo...";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "(elegir a Mary) No entiendes, Helen. Todo tu futuro está por delante y no tienes de qué preocuparte. Todo lo que tengo delante es guerra, intrigas políticas y total incertidumbre. Tienes que organizar tu propia vida, no hay lugar para un vagabundo salvaje como yo en ella.";
				link.l1.go = "result_10";
				link.l2 = "(elegir a Helen) Es más de lo que podría esperar, Helen. Por supuesto que no quiero perderte, pero sería mejor que fueras a Isla Tesoro. Quién sabe a dónde me llevará mi destino aún. Ahora mismo, tengo una guerra, intrigas políticas e incertidumbre por delante.";
				link.l2.go = "result_15";
			}
			else
			{
				link.l1 = "Es más de lo que podría esperar, Helen. Por supuesto, no quiero perderte, pero sería mejor para ti ir a Isla Tesoro. Quién sabe a dónde me llevará el destino aún. Ahora mismo, tengo una guerra, intrigas políticas e incertidumbre por delante.";
				link.l1.go = "result_15";
			}
		break;
		
		case "result_10":
			dialog.text = ""+pchar.name+"¡No me mientas! Simplemente no quieres... Dime, ¿quién es ella? ¿Es esa pelirroja buscona de la Ciudad de los Barcos Abandonados, verdad?";
			link.l1 = "¡Helen! ¡Estoy tratando de decirte lo que creo que es mejor para ti! ¿Cómo no entiendes eso?!";
			link.l1.go = "result_11";
		break;
		
		case "result_11":
			dialog.text = "Ah, claro, por supuesto que lo eres... ¿Y cómo pudo ella encantarte, eh? ¿Qué tiene ella que *yo* no tengo? ¿Es realmente tan buena? Eh, "+pchar.name+"... Bueno, es tu decisión, no me queda más que ir a mi isla. No puedo interponerme entre ustedes dos\nGracias por todo lo que has hecho por mí, Charles. Eres el mejor hombre que he conocido. ¿Espero que podamos seguir siendo amigos?";
			link.l1 = "Por supuesto... Helen, te veré de nuevo en Isla Tesoro. ¿Quieres que te lleve allí?";
			link.l1.go = "result_12";
		break;
		
		case "result_12":
			dialog.text = "No hay necesidad. Compraré un nuevo barco. He reunido suficiente dinero para comprar y equipar una goleta mientras servía bajo tu mando. Navegaré de nuevo en un nuevo 'Arcoíris'.";
			link.l1 = "Me alegra, Helen, que fueras tan... ahorrativa. Pero navegar en una goleta no le conviene a la Reina Pirata de Isla Tesoro. Pronto, deberías conseguirte una fragata.";
			link.l1.go = "result_13";
		break;
		
		case "result_13":
			dialog.text = "Quizás, "+pchar.name+". Bien. Iré al astillero, pero primero... dame un beso de despedida... Por favor...?";
			link.l1 = "Helen...";
			link.l1.go = "result_14";
		break;
		
		case "result_14": // прощальный поцелуй
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 12);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 20); //крутим время
			RecalculateJumpTable();
			DoQuestCheckDelay("Saga_HelenaBye", 0.5);
			pchar.questTemp.LSC.Mary = "return"; // к Мэри
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться
		break;
		
		case "result_15":
			dialog.text = "Mi destino es tu destino desde que nos conocimos. ¿No lo entiendes?"+pchar.name+"¡Te seguiré hasta los confines del mundo!";
			link.l1 = "¿Y qué hay de tu padre? ¿Laurence Beltrope? Él es mi enemigo...";
			link.l1.go = "result_16";
		break;
		
		case "result_16":
			dialog.text = "Mi padre es Sean McArthur. Lo amé y lloré su muerte. Era mi único padre. Y ese pirata... ni siquiera quiero hablar de él.";
			link.l1 = "¡Helen... Mi querida Helen!";
			link.l1.go = "result_17";
		break;
		
		case "result_17":
			dialog.text = ""+pchar.name+", ¡siempre he querido decirte que eres el hombre más grandioso que he conocido! Has hecho tanto por mí que nunca podré pagártelo. Quiero quedarme contigo. Para siempre. Me casaré contigo si quieres... Te amo.";
			link.l1 = "¡Estaremos juntos. Lo prometo!"; // а куда же ты теперь денешься :)
			if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) {
				link.l1.go = "result_17A";
			} else {
				link.l1.go = "result_18";
			}
		break;
		
		case "result_17A":
			dialog.text = "¿Prometes que harás algo por mí ahora mismo? ¡Y por favor, no te rías!";
			link.l1 = "¡Lo prometo, querida mía!";
			link.l1.go = "result_17A_1";
		break;
		
		case "result_17A_1":
			dialog.text = "Llámame por mi verdadero nombre. ¡Por favor!";
			link.l1 = "Te amo, Helen Sharp.";
			link.l1.go = "result_18";
		break;
		
		case "result_18":
			dialog.text = ""+pchar.name+", querido... ¡Abrázame! ¡He estado esperando este momento por demasiado tiempo!";
			link.l1 = "Helen, mi querida...";
			link.l1.go = "result_19";
		break;
		
		case "result_19": // романтик-сцена
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, true, true);
			PlayStereoOGG("music_romantic");
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.01, 0.0, 2.0, 0.0, 580);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("Saga_HelenaRomantic", 20.0);
			pchar.GenQuest.MusicContinue = true;
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.																					   
			
			pchar.quest.HelenUpgradeShip.win_condition.l1 = "Timer";
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.day = GetAddingDataDay(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l2 = "location";
			pchar.quest.HelenUpgradeShip.win_condition.l2.location = "PortRoyal_town";
			pchar.quest.HelenUpgradeShip.function = "HelenUpgradeShip";
			
			// Квест Лонгвея "Путеводная звезда", начало 5 этапа
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway") && CheckAttribute(pchar, "questTemp.PZ_Etap5_Start") && !CheckAttribute(pchar, "questTemp.PZ_ProvalFinal"))
			{
				PChar.quest.PZ_Etap5_Start.win_condition.l1 = "location";
				PChar.quest.PZ_Etap5_Start.win_condition.l1.location = "Pirates_town";
				PChar.quest.PZ_Etap5_Start.win_condition = "PZ_Etap5_Start";
				AddMapQuestMarkCity("Pirates", false);
			}
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"¡Eso fue... increíble! No quiero ir a ningún otro lugar... Quedémonos aquí hasta la mañana. ¡El mundo puede esperar!";
			link.l1 = "¡Lo dejaremos esperar, Helen!";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Next morning...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("Saga_HelenaRomantic_5", 4.0);
			pchar.questTemp.Saga.Helena_officer = "true"; // показатель, что Элен - наша навсегда
			
			pchar.GenQuest.BrothelCount = 0;
			
			pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
			pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
			pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
			pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
			
			// Запуск квеста Дороже золота
			SetFunctionTimerCondition("GoldenGirl_Start", 0, 0, 1, false);
		break;
		
	// -------------------------------------------- провалы саги ------------------------------------
		case "failcenturion":
			dialog.text = "¡Capitán! Jackman está muerto... ¿Finalmente está a salvo mi familia?";
			link.l1 = "Sí, Helen, todos están a salvo. Pero el 'Centurión' se hundió y con él todos los documentos que podrían ayudarnos a encontrar la tumba de tu madre y probar tus derechos sobre la Isla Tesoro... Eh... Ahora tendré que asaltar Tortuga por mi cuenta...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = ""+pchar.name+", no te preocupes tanto. No hay nada que podamos hacer al respecto. No te preocupes por mí tampoco, viviré bien sin esa isla. ¡Gracias por todo lo que has hecho por mí!";
			link.l1 = "Suena como si fueras a... dejarme, ¿verdad?";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "Sí, mi capitán. Pude reunir suficiente dinero para comprar y equipar una goleta. Navegaré de nuevo en mi 'Arcoíris'. Nos volveremos a encontrar en Blueweld... Estoy regresando a casa.";
			link.l1 = "Bueno... ¡buena suerte, Helen!";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) // patch-6
			{
				pchar.questTemp.LSC.Mary = "return"; // к Мэри
			}
		break;
		
		case "late_l1":
			dialog.text = "Bueno, mi capitán... Parece que hemos fallado. Adiós. Regreso a casa. He ganado suficiente dinero bajo tu mando para comprarme una nueva goleta. ¡Nos encontraremos de nuevo en el mar!";
			link.l1 = "Buena suerte, Helen. Lo siento por todo. Adiós.";
			link.l1.go = "failcenturion_3";
		break;
		
		case "late_l2":
			dialog.text = "¡Capitán! Jackman está muerto... Entonces, parece que mi familia está a salvo, ¿no es así?";
			link.l1 = "Sí, Helen, es seguro. Pero no estoy feliz, perdí demasiado tiempo e Isla Tesoro es ahora una colonia inglesa. Te quedaste sin tu herencia, así que tendré que asaltar Tortuga yo mismo...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "late_l3":
			dialog.text = ""+pchar.name+", ¿qué te dijo el abogado?";
			link.l1 = " He perdido demasiado tiempo y ahora Isla Tesoro es una colonia inglesa. Te quedaste sin tu herencia, así que tendré que asaltar Tortuga yo mismo... Ay, hemos perdido.";
			link.l1.go = "failcenturion_1";
		break;
	// <-- провалы Саги
		
		// секс - Элен соглашается не всегда (голова болит, а что вы хотели? :)) и сама не требует секса
		case "cabin_sex":
			if (CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "No, cariño, no funcionará.";
				link.l1 = "¡Pues, por qué no?!";
				link.l1.go = "refuse";
				break;
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			if (drand(4) == 0)// вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", no me siento bien hoy. No te sientas mal, por favor, no es tu culpa. No lo hagamos hoy..."," "+pchar.name+", querido, he estado tan cansada en los últimos días. Para ser honesta, solo quiero dormir. Perdóname. Hagámoslo en otro momento.");
				link.l1 = RandPhraseSimple("Bien...","Está bien. Como desees...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(" "+pchar.name+", el ambiente es perfecto, ¡vamos!",""+pchar.name+", claro, ¡sin preguntas! ¡Vamos!");
				link.l1 = RandPhraseSimple("Esa es mi chica...","Eres tan encantadora, Helen...");
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuest("cabin_sex_go");
			}
		break;
		
		case "sex_after":
			dialog.text = LinkRandPhrase(RandPhraseSimple("Fue maravilloso, "+pchar.name+"¡..!","Eras genial como siempre, querido..."),RandPhraseSimple("¡Fue genial, Charles!","¡Lo pasé de maravilla, querido!"),RandPhraseSimple("¡Nunca me aburro contigo, mi capitán!","¡Fuiste maravilloso, querido!"));
			link.l1 = RandPhraseSimple("Te amo...","Siempre es bueno estar contigo, Helen...");
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_officer";
			chrDisableReloadToLocation = false;//открыть локаци.
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+", sabes que siempre me alegra... Pero no es el momento adecuado ahora - tenemos que atrapar a ese canalla Thibaut antes de que escape.";
				link.l1 = "Tienes razón como siempre, Helen...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "No, cariño, no funcionará.";
				link.l1 = "¡Bueno, por qué no?!";
				link.l1.go = "refuse";
				break;
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			if (drand(4) == 0) // вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", no me siento bien hoy. No te sientas herido, por favor. No lo hagamos hoy...",""+pchar.name+", querido, he estado tan cansada los últimos días. Para ser honesta, solo quiero dormir. Perdóname. Hagámoslo en otro momento.");
				link.l1 = RandPhraseSimple("Bien...","Está bien. Como desees...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", ¡Te amo! ¡Vamos!",""+pchar.name+", ¡sí, sí, capitán! ¡Vamos!");
				link.l1 = RandPhraseSimple("Eres mi buena chica...","Eres hermosa, Helen...");
				link.l1.go = "room_sex_go";
			}
		break;
		
		case "room_sex_go":
			DialogExit();
			pchar.quest.sex_partner = Npchar.id;
			chrDisableReloadToLocation = true;
			//npchar.quest.daily_sex_room = true; // для первого раза в таверне чтобы счетчик запустить . лесник
			//npchar.quest.daily_sex_cabin = true;
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			sld = CharacterFromID("Helena");
			ChangeCharacterAddressGroup(sld, loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest3");
			DoFunctionReloadToLocation(loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest4", "GiveKissInRoom");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Helena_officer":
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("Sí, "+pchar.name+"¿?","Sí, mi capitán?","Estoy escuchando, "+pchar.name+"...");
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.CutlassTraining")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.CutlassTraining");
				dialog.text = "¡Mira esto, mi capitán!";
				link.l1 = "¡Vaya, qué agarre! Veo que no perdiste tiempo, Helen.";
				link.l1.go = "cutlass_training";
				NextDiag.TempNode = "Helena_officer";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && sti(pchar.GenQuest.BrothelCount) > 0 && !CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "Querido, sobre tus visitas a las prostitutas.";
				npchar.quest.refusesex = true;
				link.l1 = "¿Qué? ¡Helen, lo tienes todo mal! Yo solo...";
				link.l1.go = "brothel_found";
				NextDiag.TempNode = "Helena_officer";
				SetFunctionTimerCondition("Helena_ClearRefuseSex", 0, 0, 180, false);
				DeleteQuestCondition("Helen_GiveSex");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Helen, voy a visitar la ciudad india perdida de Tayasal. No te mentiré: este viaje es muy peligroso y aún más, incluye teletransportación a través del ídolo. ¿Me... acompañarás?";
				Link.l4.go = "tieyasal";
			}
       ////////////////////////казначей///////////////////////////////////////////////////////////
           		// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Helen, dame un informe completo del barco.";
			    Link.l11.go = "QMASTER_1";
			        
			    // Warship. Автозакупка товара
				Link.l12 = "Quiero que compres ciertos bienes cada vez que estemos atracados.";
				Link.l12.go = "QMASTER_2";
			}
			
            /////////////////////////////////////казначей////////////////////////////////////////////////////////////     			
			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Llegué por su disposición, capitana.";
				Link.l2 = "Helen, necesito darte varias órdenes.";
				Link.l2.go = "Companion_Tasks";
				
				sld = GetCharacter(sti(npchar.RealCompanionIdx));
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Rainbow") && sld.ship.type == pchar.questTemp.HelenDrinking.Rainbow && CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
					DeleteAttribute(link, "");
					dialog.text = "¿Crees que es gracioso?";
					link.l1 = "Bonito barco, ¿verdad? ¡Lo conseguí para ti, Helen! Piensa, ¿qué tipo de hombre en el Caribe le regala un barco de verdad a su dama, eh?";
					link.l1.go = "rainbow";
					
					NextDiag.TempNode = "Helena_officer";
					break;
				}
				
				NextDiag.TempNode = "Helena_officer";// не забыть менять в зависисомости от оффа
				break;
			}																															
			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "Helen, necesito tu consejo.";
				Link.l3.go = "fugas";
			}
			Link.l1 = "Helen, tengo una orden para ti...";
            Link.l1.go = "stay_follow";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && pchar.location == Get_My_Cabin() && GetNpcQuestPastDayWOInit(npchar, "sex_date") >= 1) // mitrokosta - очередные исправления интима
			{
				Link.l2 = RandPhraseSimple("Helena, quedémonos en la cabina juntos a solas... ¿por unas horas? ¿Qué opinas?","Querido, ¿pasamos las próximas horas tête-à-tête? ¿Te gusta esta idea?");
				Link.l2.go = "cabin_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "tavern" && sti(pchar.money) >= 10 && GetNpcQuestPastDayWOInit(npchar, "sex_date") >= 1) // mitrokosta - очередные исправления интима
			{
				Link.l2 = RandPhraseSimple("Helen, ¿por qué no alquilamos una habitación y nos quedamos allí en privado... durante las próximas horas? ¿Qué opinas de eso?","Querido, ¿pasemos las próximas horas tête-à-tête? Alquilaremos una habitación... ¿qué opinas?");
				Link.l2.go = "room_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "town" && sti(pchar.money) >= 1000 && GetNpcQuestPastDayWOInit(npchar, "special_sex_date") >= 30 && !CheckAttribute(npchar, "quest.refusesex"))
			{
				Link.l2 = "Helen, querida, ¿puedo invitarte a pasar un buen rato en la taberna?";
				Link.l2.go = "special_sex";
			}
			if (CheckAttribute(pchar, "questTemp.MysteryPortRoyal_Helena")) {
				link.l4 = "Helen, parece que encontré la última voluntad de tu admirador, Francis. Te dejó su herencia.";
				link.l4.go = "MysteryPortRoyal_Helena_1";
			}
			if (CheckCharacterItem(pchar, "pirate_cutlass") && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
				link.l4 = "Creo que este alfanje es ahora tuyo. Blaise es tu llamado tío...";
				link.l4.go = "give_cutlass";
			}
			link.l9 = "Nada ahora mismo, Helen.";
			NPChar.id = "Helena"; // лесник . Идентификация Элен на всяк. случай . если потеряет сознание.
			link.l9.go = "exit";
			NextDiag.TempNode = "Helena_officer";
		break;
		
		/////////////////////////// ответы для казнаячея - Элен ..(элен казначей - ужас!))///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Charles, querido, ¿estás enfermo o algo así? ¿Qué, esperas que baje, barra la bodega y empiece a contar ratas?";
			Link.l1 = "Bien, lo siento querida, mi error...";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Y quiero mi propio navío de línea, con cien cañones volando a 20 nudos. He sido capitán como tú toda mi vida. Ve y consíguete un maldito intendente y moléstalo con eso.";
			link.l1 = "Sí, tienes razón, Helen. Lo siento por eso.";
			link.l1.go = "exit";
		break;
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Soy toda oídos.";
			Link.l1 = "Sobre nuestra política de abordaje...";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Sobre el barco que comandas...";
			Link.l2.go = "Companion_TaskChange";
			Link.l8 = "Nada hasta ahora.";
			Link.l8.go = "exit";
			 
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "¿Cuál es tu deseo, mi capitán?";
			Link.l1 = "No quiero que abordes nada. Mantente a salvo, tú y tus hombres.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Quiero que abordes los barcos enemigos en la primera oportunidad.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "Sí, mi capitán?";
			Link.l1 = "Agradecería que te abstuvieras de cambiar de barco después de abordar. Es demasiado valiosa para mí.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Si llegas a abordar a alguien, echa un buen vistazo al navío capturado. Si es bueno, siéntete libre de quedártelo para ti.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "Está bien, lo pensaré.";
			Link.l1 = "Lo pensará... Claro, como si pudiera darle órdenes de todos modos.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "Está bien, lo pensaré.";
			Link.l1 = "Lo pensará... Claro, como si pudiera darle órdenes de todos modos.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "Está bien, lo pensaré.";
			Link.l1 = "Lo pensará... Claro, como si pudiera darle órdenes de todos modos.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "Está bien, lo pensaré.";
			Link.l1 = "Lo pensará... Claro, como si pudiera darle órdenes de todos modos.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========//////////////////////////////////////																																			  
		
		case "stay_follow":
            dialog.Text = "¿Órdenes?";
            Link.l1 = "¡Quédate aquí!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "¡Sígueme y no te quedes atrás!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Cambia el tipo de munición para tus armas de fuego.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Elige el tipo de munición:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "¡Enseguida, capitán!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "¡De inmediato, capitán!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		// --> суп из черепахи
		case "terrapin_grot":
			dialog.text = "¡Ahí estás! Finalmente te encontré... ¡Eso fue algo, mi capitán! ¡Nunca había visto correr por un tejado así y un salto desde una altura tan impresionante! ¡Mi corazón estaba a punto de explotar! Un día me matarás con tus trucos, querido... Oh, no estás solo... ¿Quién es esta chica?";
			link.l1 = "Esta es Catherine Fox, la hija del Coronel Fox, el comandante del famoso Regimiento Inglés de Infantería Marítima, los 'Zorros del Mar'. La llevamos a Antigua.";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "¿Es así... Bienvenida a bordo, Sra. Fox! .No, no, no se aferre al brazo del Capitán de Maure, puede caminar perfectamente por su cuenta! Y ahora vamos al bote - necesitamos salir de aquí."; 
			link.l1 = "¡Ja! ¡Gracias, Helen! ¿Qué haría sin ti? ¡Catherine, síguenos!";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- суп из черепахи
		
		// --> калеуче
		case "on_coast":
			dialog.text = "Finalmente te has despertado, querido. ¿Cómo te sientes? Me asustaste casi hasta la muerte...";
			link.l1 = "Helena, ¿qué ha pasado? Me duele la cabeza...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "Cuando entramos en el camarote del capitán, yacías en el suelo inmóvil. ¡Mi corazón casi dejó de latir! Los muchachos te levantaron y te arrastraron de vuelta a nuestro barco, justo a tiempo, ya que los muertos que yacían en la cubierta comenzaron a levantarse de nuevo.\n¡Qué horror! ¡Es casi suficiente para hacerme encontrar a Dios! ¡Eran totalmente inmunes a nuestras espadas y balas! Rápidamente cortamos las cuerdas e intentamos zarpar, pero una andanada desde su barco dañó gravemente nuestro navío y perdimos el control. Luego izaron velas y desaparecieron en un abrir y cerrar de ojos.\nNuestro barco encalló, así que tuvimos que huir a esta costa antes de que la tormenta pudiera destruirlo. Muchos buenos hombres murieron hoy, pero el barco sobrevivió al final... si tan solo no hubiera ordenado abandonarlo...";
			link.l1 = "No es tu culpa, Helen. Era la decisión correcta. ¿Qué haría yo sin ti?";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Te arrastré al bote y luego te llevé a tierra. Parecías muerto, solo tu corazón latía muy débilmente. ¡Mira! Mis manos todavía están temblando";
			link.l1 = "Gracias, amor. Te estoy en deuda. ¿Cuánto tiempo he estado aquí acostada?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "Por todo un día. Lavé y vendé tus heridas, te di medicina y te vertí un poco de ron. ¡Ahora debes recuperarte!";
			link.l1 = "No moriré esta vez, querido. Aunque no me siento bien...blurgh....";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "Dime... ¿Era el verdadero 'Holandés Errante', Charles? ¿Por qué nos atacaron? ¿Y por qué no nos dispararon al acercarse, pero intentaron hundirnos inmediatamente después de abordar?";
			link.l1 = "Su capitán necesitaba ese amuleto, sobre el cual había hablado con Tuttuathapak, un chamán indio. Por qué lo necesitaban, no lo sé... pero tan pronto como su líder consiguió el amuleto, nos deshicieron... ¡Dios Todopoderoso, qué pesadilla tan miserable! ¡Un barco tripulado por muertos vivientes! Imposible de creer...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "¡Ay, ahora fue nuestro turno de encontrarnos con el 'Holandés Errante'. ¡Gah! ¡Me pone la piel de gallina! En el próximo puerto que paremos, iré a la iglesia, encenderé una vela y rezaré a nuestro Señor Jesucristo por nuestra milagrosa liberación. Maldición, me siento tan agradecido que incluso rezaré a algunos santos papistas...";
			link.l1 = "Estaré allí contigo, Helen, hace tiempo que no hago una confesión adecuada... Pero primero tenemos que volver a ese pueblo. Necesito contarle todo a Tuttuathapak. ¡Ese maldito barco nos atacó por el amuleto! Espero que ese diablo de piel roja tenga alguna idea de por qué demonios esos muertos vivientes podrían haberlo necesitado.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "De acuerdo. Pero debemos tener cuidado - tus heridas apenas han sanado.";
			link.l1 = "Pero me ayudarás a sanar más rápido, ¿verdad? Te amo, Helen...";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = "También te amo, mi querido...";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче
		
		// на Тайясаль
		case "tieyasal":
			dialog.text = ""+pchar.name+", te he dicho una vez que ahora compartimos destinos. Tu destino es mi destino. ¿Cuándo partimos?";
			link.l1 = "Me alegra mucho escuchar eso. Te lo contaré un poco más tarde cuando vayamos allí. Necesitamos prepararnos.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "¡Estoy lista, mi capitán! ¡Te seguiré hasta los confines de la Tierra!";
			link.l1 = "Gracias, mi amor...";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "20");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// на Исла Тесоро
		case "islatesoro":
			dialog.text = "¡Oh, "+pchar.name+"¡Me alegra verte! ¿Qué haces aquí en Isla Tesoro?";
			link.l1 = "Lo mismo de siempre - negocios. Solo quería pasar a verte también. ¿Cómo está todo, Helen?";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			DialogExit();
			NextDiag.CurrentNode = "islatesoro";
		break;
		
		// Jason Дороже золота
		case "GoldenGirl":
			dialog.text = "¿Qué le ocurre a nuestro queridísimo gobernador, capitán? ¿A quién le pateamos el trasero esta vez? ¿A los españoles, a los piratas o a alguien peor?";
			link.l1 = "Es peor, Helen, mucho peor. El gobernador tiene la intención de visitar a una cortesana cara y se supone que debo acompañarlo como curiosidad. Le prometió a su amante llevar a un auténtico corsario, aventurero y lobo de mar. Así que me espera una charla aburrida, vino caro y nobles aburridos.";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "Todo lo contrario, una invitación a un agradable evento social, organizado por una dama. Su Excelencia me sorprendió al pedirme que lo acompañara, pero para ser honesto, me alegra poder distraerme del trabajo por un cambio.";
			link.l2.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "¡Ay... así que el temible Capitán Charles de Maure se disfrazará y bailará como un mono domesticado para su diversión? ¡Qué dulce! Tengo una mejor idea. Levemos anclas y larguémonos al diablo de aquí. Si estás de humor para unas merecidas vacaciones, naveguemos hacia Isla Tesoro. Siempre somos bienvenidos allí. Tomar el sol, arena blanca, viejos amigos, ponche de ron, despejar la mente - lo que sea.";
			link.l1 = "Mira, todo esto suena fantástico, y me encantaría... pero más tarde. Le prometí al gobernador, esto es importante para el viejo y...";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "¿Y qué? ¿Crees que tu sangre noble les importa un comino? Puede que no tenga sangre francesa, pero sé todo sobre su 'alta sociedad' y para ellos, Charles de Maure no es un capitán al que los hombres sigan y en quien confíen sus vidas. No es un caballero como ellos. Los verdaderos caballeros no van al mar y luchan en una niebla de humo de pólvora. ¡Charles de Maure es solo un curioso agregado a su banquete. Como un leopardo mascota o un negro doméstico disfrazado! ¡Un juguete elegante! ¿Desde cuándo te sometes a tal trato?!";
			link.l1 = "Helen, por favor, cálmate. Estoy seguro de que puedo soportar algunas miradas incómodas para satisfacer al gobernador y asegurar nuestra futura prosperidad. Es bueno tener amigos poderosos. Después de todo, esto será más fácil que liderar un abordaje. Y estos 'inútiles' no siempre son así. Incluso en la alta sociedad hay gente digna... al menos se supone que sí.";
			link.l1.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "Lo que sea. (se pasa la mano por el cabello) Pero te advierto: de ninguna manera me meteré en un vestido elegante. Si me obligas a ir, llevaré mis calzones. Me importa un comino si todas las damas del Caribe se desmayan de desaprobación.";
			link.l1 = "No iba a obligarte. No tiene sentido que ambos suframos. Pasaré por esta fiesta y luego zarparemos hacia Isla Tesoro. Como recompensa, he estado guardando una caja de excelente madeira española en la bodega de carga...";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "¡Oh ho ho, Charles! ¿Estás diciendo que no soy buena para tan estimada compañía? ¿Que una chica en pantalones arruinaría tu noche? Qué interesante. Muy bien entonces, pero no olvides vestirte como un petimetre. Los monos en vestidos elegantes pueden tocar incluso el corazón de una cortesana. ¡Feliz actuación!";
			link.l1 = "¡Helen, espera! Maldita sea... ¡mujeres!";
			link.l1.go = "GoldenGirl_8";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "Sí, nos merecemos un buen descanso. Pero maldita sea si me aprieto en un vestido elegante para esto. ¿Qué tan lejos crees que llegarán los chismes sobre tu mujer vestida como hombre y marinera?";
			link.l1 = "Ah... No creo que sea una gran idea. ¿Cómo decirlo...? Este no es un evento al que los hombres traigan a sus esposas o a damas respetables...";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_6":
			dialog.text = "¡Ja! ¡Putas y depravación! ¡Simplemente maravilloso, entonces vas a una orgía! ¿Por qué demonios no lo dijiste así? Tienes suerte de que no soy una celosa furibunda y no te voy a disparar justo donde estás. Al menos no ahora.";
			link.l1 = "Helena, por favor, todo lo que estoy haciendo es acompañar a nuestro gobernador, él me lo pidió y fue muy insistente al respecto. No habrá putas cortesanas\nEspera, eso salió mal... quiero decir que habrá putas cortesanas... ¡Oh, maldita sea! ¡Solo estoy rindiendo mis respetos!";
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_7":
			dialog.text = "Te sugiero que te vistas a la moda para 'presentar tus respetos', Capitán de Maure. Es la alta sociedad y todo eso. Es un puro escándalo aparecer allí sin cuello y puños. Incluso para una orgía. Que te diviertas.";
			link.l1 = "¡Helen, espera! Maldita sea...¡mujeres!";
			link.l1.go = "GoldenGirl_9";
		break;
		
		case "GoldenGirl_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_9":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = "Puños y un cuello, Capitán. Y quizás encaje. He oído que está de moda otra vez. ¡Pero qué sé yo!";
			link.l1 = "¡Oh Helen, vamos!";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "¡Mira esto! ¡Mi querido capitán, de vuelta a casa de su orgía!";
			link.l1 = "...";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "¿Todavía aprueban los nobles locales a su nuevo mono? ¡Vaya, dicen que su actuación anoche fue legendaria! ¿Jugando a los dados por barcos y prostitutas, desafiando a principitos nobles a duelos? ¿Sería tan amable de explicar qué diablos está pasando contigo?";
			link.l1 = "¡Helen, déjame explicar! No es tan sencillo. ¡Maldita sea, lo siento, pero nunca pensé que tendría que pasar la noche en casa de Madame Botot. Solo dormí allí, sí, solo lo juro! Y sí, gané una fragata en un juego de cartas. ¿Te imaginas?";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "¡Pues bien! O eres un gran mentiroso, un santo o un necio. Discutiremos las prostitutas y los barcos que ganaste más tarde; ahora cuéntamelo todo sobre el duelo y por qué todos murmuran que desafiaste a un príncipe heredero.";
			link.l1 = "No es un príncipe heredero, solo un bastardo de conde. Es el hijo de un noble muy influyente, el Conde de Levi Vantadur. Mira, ¡yo no comencé esto! Él me desafió primero, y ahora debo ganar el duelo sin herirlo demasiado para evitar la ira de su padre.";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "Oh, ¿'solo el hijo de un conde', eh? ¡¿Hablas en serio ahora mismo, Charles?! ¿Y cómo se supone que hagamos esto? ¿Y si hace trampa? ¡Te matará!";
			link.l1 = "Por eso Su Excelencia me ha proporcionado nobles segundos. Solo los llevaré conmigo; si las cosas salen mal, al menos podré probar que todo fue según el códice del duelo y la ley. Te pido que vigiles la fragata mientras yo no esté.";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "Vamos a asegurarnos de que entendí bien... Estuviste fuera todo un día y una noche y ganaste una ramera y una fragata en un juego de cartas. Y ahora, estás a punto de pelear con un hijo de puta noble al que no puedes matar, mientras *yo* solo me siento aquí y espero. ¿Cómo se supone que debo sentirme con todo esto?!";
			link.l1 = "Helena, escucha, tienes todo el derecho de estar enfadada conmigo y lo siento mucho, pero es solo...";
			link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "¿Sabes qué? Estoy harta de esto. ¡Solo ve y haz lo tuyo! ¡Yo solo desempolvaré tu camarote y lavaré tu ropa sucia! No creas ni por минуту, что ты в безопасности. Мы поговорим об этом, когда все закончится. Я позабочусь о твоем новом фрегате, великий капитан де Мор, не беспокойся. Ах, и капитан де Мор, постарайся не умереть... потому что я планирую убить тебя сама потом. А теперь извини, я собираюсь запереться в своих покоях и выпить бутылку того прекрасного мадеры, что нашла в твоей каюте.";
			link.l1 = "Helen, ¡déjame explicar! Carajo... ¡Aquí vamos de nuevo!";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "¡He oído que la última moda parisina exige que los caballeros ganen barcos y cortesanas en juegos de cartas en lugar de comprarlos! Además, si uno quiere causar una buena impresión, tiene que desafiar a sus antiguos dueños a un duelo. ¿En qué demonios te has metido esta vez?";
			link.l1 = "Elena, no es tan simple. ¡Maldita sea, lo siento, pero nunca pensé que tendría que pasar la noche en casa de Madame Botot! La pasada noche se convirtió en una agotadora y brutal batalla de ingenios. Y sí, gané una maldita fragata en las cartas. ¿Te imaginas?";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "Encantador. ¿Significa eso que ganaste también a una cortesana? Y la fragata que ganaste, ¿qué apostaste contra ella? No nuestro barco, no podrías haber...";
			link.l1 = "Tuve que hacerlo. Mira, no importa ahora, al final gané. Mi oponente me retó a un duelo y me acusó de hacer trampa. Es un bastardo de un noble extremadamente influyente, el Conde de Levi Vantadur. Lo que significa que tendré que hacer mi mejor esfuerzo para no matarlo ni herirlo demasiado.";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "¿Hará él lo mismo? ¿Has perdido la cabeza, Charles? ¿Arriesgar tu barco, arriesgar tu vida, por alguna otra mujer? ¡¿Realmente ella lo vale?! ¿No significo nada para ti?!";
			link.l1 = "Helen, no hay razón para estar celosa, lo juro. Simplemente sucedió. Tenía que hacerlo y el gobernador me proporcionó oficiales nobles como mis segundos para asegurarme de que todo ocurra según las reglas. No puedo llevarte a ti ni a ninguno de nuestros hombres conmigo. Por favor, cuida de la fragata mientras estoy fuera.";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			dialog.text = "¡Simplemente genial! Primero, vas a una orgía con mujeres extrañas y apareces de nuevo a la mañana siguiente, y ni siquiera te di un golpe por eso. Ahora, me dices que casi perdimos nuestro barco en un juego de cartas pero ganaste una cortesana. ¡Y ahora estás a punto de luchar por su 'honor' contra algún hijo de puta de la nobleza al que ni siquiera se te permite matar! ¿Cómo se supone que debo sentirme con todo esto? Dime.";
			link.l1 = "Helen, escucha, tienes todo el derecho de estar enojada conmigo, pero déjame explicarte...";
			link.l1.go = "GoldenGirl_22";
		break;
		
		case "GoldenGirl_22":
			dialog.text = "¿Sabes qué? Ya tuve suficiente de esto. Ve y pelea tu maldito duelo. Yo cuidaré de tu nueva fragata, gran Capitán de Maure, no te preocupes. Ahora discúlpame, voy a encerrarme en mis aposentos y beber una botella de ese buen madeira que encontré en tu camarote. ¡Pero si algo te pasa, juro por Dios que desataré el infierno sobre esta ciudad y enterraré este burdel y el palacio de tu amado Excelencia!";
			link.l1 = "Helen, estará bien, confía en mí... ¡Espera, ¿a dónde vas?! ¡Maldita sea! Aquí vamos de nuevo...";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "Charles, tienes algunas explicaciones que dar. ¿Serías tan amable de decirme qué demonios sucedió? No puse una vigilancia adecuada y los muchachos estaban bebiendo... unos canallas asaltaron nuestro barco y nos ataron mientras dormíamos. Luego, la escoria inmunda empezó a preguntarme hasta dónde llegarías para rescatarme. Al final, me encerraron en la bodega. ¡Perdí la cuenta de los días que he estado esperando!";
			link.l1 = "¡Ese bastardo quería vengarse de la vergüenza que le hice pasar! ¡Tenía miedo de que te hiciera algo! ¡Gracias a Dios que estás bien!";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			dialog.text = "Supongo que tuviste que hacer algo para recuperarme. Algo malo, ¿verdad?";
			link.l1 = "Todo lo que importa es que estás de vuelta conmigo. Te fallé, Helen. ¡Lo siento muchísimo! ¡Espero que puedas encontrar en tu corazón perdonarme!";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "Ya lo hice. He tenido mucho tiempo para pensar en lo que dije... También lo siento, Charles. Si tan solo no hubiera tomado tus tratos con ese marqués tan personalmente. Habría puesto una vigilancia adecuada esa noche, habría estado alerta. ¡Ah! ¡Soy solo una mujer inútil!";
			link.l1 = "Deja de decir eso, el pasado es el pasado. Te amo y nunca te dejaré de nuevo. ¡Lo prometo!";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "Supongo que será mejor no saber exactamente qué hiciste, ¿verdad? Está bien, estamos juntos de nuevo y eso es lo principal.";
			link.l1 = "Tengo ningún secreto para ti. Te contaré...";
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Qué lío... Sé que no tenías elección, pero ¿cómo explicar esto a Di Lu Parkes y sus amigos? ¡Quiero decir, ahora eres un criminal!";
				link.l1 = "Elegí pagar ese precio, pero realmente no tenía opción. No te preocupes, encontraré la manera de arreglarlo y restaurar nuestro buen nombre. Si no, ¡siempre seremos bienvenidos en Isla Tesoro! Puedo arreglármelas si estás conmigo.";
			}
			else
			{
				dialog.text = "Qué historia, Charles... Creo que no tenías elección en el asunto, pero ¿qué sigue? ¿Ese inglés arreglará las cosas o es la guerra? ¿Estás seguro de que no quieres venir a Basse-Terre para presenciar cómo encadenan a ese bastardo?";
				link.l1 = "Sabes, Helen, hace dos semanas nunca lo habría dejado pasar. ¡Pero hoy digo al diablo con él! Ya no me importa su justo castigo. Estamos juntos de nuevo, ¡eso es lo único que importa!";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Sabes que siempre estaré contigo. ¡Ja! No es la primera vez que tú y yo terminamos con el agua hasta el cuello en las sentinas. Lo lograremos de nuevo.";
				link.l1 = "Verdad. ¡Zarpemos, querido! ¡El horizonte nos espera!";
			}
			else
			{
				dialog.text = "¡Me gusta tu forma de pensar, Charles! No más nobles: franceses, británicos, españoles - lo que sea. ¡Creo que nos hemos ganado unas vacaciones!";
				link.l1 = "¡De acuerdo! ¡Sólo tú y yo! ¡No más gobernadores ni bastardos de sangre azul!";
			}
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "¡Aye, aye, Capitán!";
				link.l1 = "";
			}
			else
			{
				dialog.text = "¡Suena encantador! ¡Voy a decirle a los muchachos que es hora de levar anclas! Y Charles...";
				link.l1 = "Lo sé, Helen, lo sé. Me uniré a ti en un momento.";
			}
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
		break;
		
		case "GoldenGirl_32":
			dialog.text = "¡Charles, lo lograste! ¡Los portugueses me lo contaron todo! ¡Qué historia!";
			link.l1 = "¡Gracias a Dios, estás viva, Helen! ¡No tienes idea de lo feliz que estoy de verte de nuevo!";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "Hablando de eso. Me prometiste contarme algo, ¿recuerdas? Algo grande y complicado. Esta es tu oportunidad, Capitán. ¿¡Qué demonios sucedió?!";
			link.l1 = "Te amo, Helen. Lo demás es irrelevante.";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "¡Sí, eso fue útil, pero... Maldita sea, yo también, Charles. Yo también te amo. ¡Dios mío, te he echado tanto de menos!";
			link.l1 = "Yo también. Ven conmigo, no te dejaré esta noche aunque el cielo empiece a caer sobre esta miserable ciudad. Nunca más te dejaré. Jamás.";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "Supongo que sería mejor no saber exactamente qué hiciste, ¿verdad? Aye, estamos juntos de nuevo y eso es lo principal.";
			link.l1 = "Tengo    ningún secreto para ti. Te contaré...";
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = "¡Increíble! ¿Acabas de decir que Francia e Inglaterra están al borde de la guerra entre sí por mi culpa?";
			link.l1 = "No, Helen. Es porque cometí un error de juicio muy grave. Pero tenía que traerte de vuelta y arreglarlo todo.";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "Todo eso es muy conmovedor y romántico, estoy incluso lista para olvidar cómo todo comenzó en primer lugar. Casi lista. Pero en serio, ¿te arrestaron porque los portugueses dieron un nombre equivocado de la maldita bergantín?";
			link.l1 = "¡Todo lo contrario, me dio el correcto! ¡Ojalá supiera cómo logró hacer esto y por qué. Por cierto, ¿dónde está el propio hombre?!";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "Se ha ido. Justo después de traerme aquí. No quería usar la 'hospitalidad' de la cortesana que ganaste, así que hice que Bartholomew alquilara una habitación para mí. La pagó y desapareció sin decir una palabra. Bueno, espera, no, dejó una carta para ti, ¡eso sí!";
			link.l1 = "¿Una carta? ¿De Bartolomé el Portugués? Esto es nuevo. No me gusta hacia dónde va esto...";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "De acuerdo, te dejaré leerlo aquí mientras voy a saludar a los muchachos. Deben estar preocupados. ¡Nunca pensé que extrañaría esas caras largas y sombrías! Mientras tanto, trata de no meterte en otro desastre.";
			link.l1 = "Maldita sea... ¡Todavía no puedo creer que te he traído de vuelta!";
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
		break;
		
		// Jason Долго и счастливо
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = "Arena blanca, agua verde clara, tú, yo y buen vino - ¡Charles, esto es tan romántico! Deberíamos pasear juntos así más a menudo, ¿de acuerdo?";
			link.l1 = "Me alegra que te guste. Creo que deberíamos dedicar más tiempo a esto ahora.";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "Charles, ¿qué estás haciendo y por qué estás de rodillas? Esto es tan repentino...";
			link.l1 = "Helen, te amo. Y quiero vivir contigo cada día que me sea concedido desde arriba. Por lo tanto, aquí y ahora, ante este mar y cielo, te pido - Helen Beatrice Sharp - que me des el honor de estar conmigo ante los hombres y Dios hasta que la muerte nos separe. Yo, Charles de Maure, Caballero de Monper, te pregunto - ¿te casarás conmigo?";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore_ship1")
			{
				dialog.text = "Sabes, nunca me gustaron estas formalidades, pero estoy contigo hasta el fin del mundo. Y en cuanto a tu pregunta, la respuesta es... ¡oh, lo siento, he derramado!";
				link.l1 = "Olvídalo, esto es solo vino y nunca amé esta camisa...";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "¡Charles, por supuesto que sí! ¡Sí, sí, y sí de nuevo!!! Pero espero que no estés planeando retirarnos a algún polvoriento castillo familiar para cultivar nabos hasta el fin de nuestros días?";
				link.l1 = "Bueno, tenemos un castillo familiar, pero no está polvoriento y no nos quedaremos allí. ¡Nuestra vida es la libertad y el horizonte al alcance de nuestras manos!";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestCheckDelay("Helena_LoveSex", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "¡Entonces un brindis por ti, mi capitán, mi esposo, y por nuestra boda!";
			link.l1 = "¡Por ti, mi amor! Y por nuestro futuro juntos, ¡hay tanto por delante para nosotros!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "¡Entonces un brindis por ti, mi capitán, mi esposo, y por mi boda!";
			link.l1 = "¡Por ti, mi amor! Y por nuestro futuro juntos, ¡nos espera tanto por delante!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Helena_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "Entonces, el abad Benoit ha regresado y está listo para casarnos. ¡Pero que sepas que no me pondré un vestido ni siquiera para una ocasión así! ¿Crees que usar calzones causará revuelo?";
			link.l1 = "Helen, te amo con cualquier atuendo, y ellos lo superarán. Primero quería consultarte sobre los invitados y la ceremonia.";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			dialog.text = "Sí, hay un problema - a la mayoría de nuestros mejores amigos, con quienes con gusto compartiríamos este día, no se les permitirá entrar en la ciudad, y mucho menos en la iglesia. Por lo tanto, casémonos aquí con todas las personas importantes, como se espera, y luego zarparemos hacia Isla Tesoro y tendremos una celebración adecuada con nuestros verdaderos amigos, ¿qué te parece?";
			link.l1 = "¡Me parece bien! Hablaré con el Abad Benoit, pero necesitamos enviar invitaciones y más...";
			link.l1.go = "LongHappy_9";
		break;
		
		case "LongHappy_9":
			dialog.text = "Tranquilízate, capitán. ¡Tu querida futura esposa tomará parte de la carga! Arreglaré todo en Isla Tesoro y escribiré a nuestros amigos, solo dime: ¿qué tan grande quieres la boda?";
			link.l1 = "Solo tú, yo y nuestros amigos más cercanos. Después de toda la pompa oficial aquí en Martinica, querremos algo de intimidad sincera.";
			link.l1.go = "LongHappy_10";
			link.l2 = "¡Todos deben recordar este día! ¡Llamen a todos! ¡Nadie se quedará fuera!";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = "Acogedor y amigable - ¡leíste mi mente! Tendremos que visitar Sharptown y yo prepararé todo. Creo que cincuenta barriles de ron y dos docenas de barriles de vino serán suficientes. Además, para comida y entretenimiento necesitaremos trescientas mil piezas de a ocho.";
			link.l1 = "Recuérdame, ¿por qué no manejas las finanzas del barco otra vez? Lo conseguiré todo. Solo una visita rápida al abad y luego zarpamos hacia Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "Entonces, ¿quieres tener una fiesta como verdaderos lobos de mar? ¡De acuerdo! Tendremos que visitar Sharptown y yo prepararé todo. Tendremos que abastecernos seriamente: creo que cien barriles de ron y cincuenta barriles de vino serán suficientes. Y otros gastos nos llevarán al menos quinientas mil piezas de a ocho.";
			link.l1 = "¿Estás invitando a toda la Hermandad de la Costa? ¡Al diablo, hagámoslo! Conseguiré los suministros. Solo una visita rápida al abad y zarpamos hacia Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Helen");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = "Charles, me encargaré de la carga y luego repartiré las invitaciones al barón y llegaré a un acuerdo con el tabernero. No debería tardar mucho.";
			link.l1 = "No te preocupes, querida, me ocuparé de un empleo lucrativo... O simplemente me echaré una siesta en la arena. No pensé que sería más fácil asaltar Tortuga que planear mi propia boda, por el amor de Dios.";
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam("Several hours have passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = "¿Descansaste un poco, Charles? Tengo buenas y malas noticias. La mala noticia es que los lugareños se divirtieron tanto la semana pasada que accidentalmente quemaron la maldita taberna 'El Viejo Carpintero' hasta los cimientos. Aquí está la buena noticia, el barón prometió que será reconstruida más grande y mejor de lo que era para cuando regresemos. He hecho los arreglos, así que podemos zarpar.";
			link.l1 = "Espero que nuestra boda no deje una pila similar de cenizas en el pueblo cuando nos vayamos. ¡Es una maldita pena, me gustaba mucho el 'Viejo Pájaro Carpintero' - acogedor, íntimo, con solo un leve olor a vómito y estopa! Bueno cariño, tienes razón - debemos ponernos en marcha.";
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = "¿Puedes imaginarte que Jan ya está en la ciudad con Gladys? ¡No pensé que alguna vez asistirían a mi boda! ¡Oh Dulce Jesús! ¡Incluso cuando estábamos en esa horrible ciudad templo india, no estaba tan asustada como lo estoy ahora!";
			link.l1 = "Todo está bien, querido, todo está bien. Yo también estoy preocupada, los nervios son normales. Ya que los invitados ya han llegado, debería ir a ver al Padre Benoit y averiguar cuándo comenzará el servicio.";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "Va a ser un día malditamente largo y difícil... Voy a ver a Jan y Gladys.";
			link.l1 = "Me alegra que hayan podido venir. El viejo Svensson te quiere como a su propia hija, y la señora McArthur aún más. Es bueno que estén aquí hoy. Ve y no te preocupes, todo saldrá bien.";
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Helen");
		break;
		
		case "LongHappy_20":
			dialog.text = "Sí.";
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = "Sí.";
			link.l1 = " ";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = "Sí.";
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "";
			link.l1 = "Yo, Charles Henry de Maure, caballero de Monper, te tomo a ti, Helen Beatrice Sharp, como mi esposa, para tener y sostener, desde este día en adelante, para bien o para mal, en la riqueza y en la pobreza, en la salud y en la enfermedad, hasta que la muerte nos separe. Según la Santa Ley de Dios, en la presencia de Dios, hago este voto.";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "Yo, Helen Beatrice Sharp, te tomo a ti, Charles Henry de Maure, para ser mi esposo, para tener y sostener, desde este día en adelante, para bien o para mal, en la riqueza y en la pobreza, en la enfermedad y en la salud, hasta que la muerte nos separe. Según la Santa Ley de Dios, en la presencia de Dios, hago este voto.";
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = "Amén.";
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = "Helena Beatriz de Maure, Madame de Monper - ¡oh me gusta cómo suena, mi queridísimo esposo!";
			link.l1 = "¡No he escuchado nada mejor, mi esposa!";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			dialog.text = "Sabes, pensé que esto no cambiaría nada, y probablemente no lo hizo - te amaba antes y quería vivir contigo el resto de mis días, pero este día, este servicio sagrado... ¡Estoy verdaderamente feliz, Charles! ¡Feliz como nunca antes, y mira a Gladys y Jan - están radiantes! ¡Hay tantas caras felices alrededor! Por cierto, es hora de que pasees entre los invitados y aceptes sus felicitaciones. Vuelve cuando termines, no olvides - nos esperan en Sharptown.";
			link.l1 = "Lo haré de inmediato, cariño. ¡Un beso antes de irme!";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "Hola esposo, ¿ya has hablado con los invitados?";
			link.l1 = "Aún no, ten paciencia, esposa, volveré pronto.";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "Sí, nunca había escuchado tantas felicitaciones de una vez. ¿Y sabes qué? ¡Creo que la mayoría de ellas eran sinceras!";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			dialog.text = "Sí, estos nobles son sorprendentemente sinceros - debo admitir, esperaba más falsedad e hipocresía. O simplemente estoy tan feliz que no noto nada. ¡Pero después de todo, nuestros amigos nos esperan en Sharptown! ¿Cuándo zarpamos?";
			link.l1 = "Ahora mismo. Volaremos sobre las alas de águilas directamente a un banquete amistoso. Espero que no te importe, mi esposa, pasar esta noche en nuestra cabina.";
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "¡Oh sí, mi esposo, eres tan romántico! Y no te retuerzas así, ahora tengo derecho a besarte en público... ¡Ay, podemos irnos ahora!";
			link.l1 = "¡Navegante, pon rumbo a Sharptown y no permitas que nos molesten por ninguna razón! ¡No me importa si una flota de fantasmas se nos viene encima!";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "Oh mi querido esposo, ¡estoy tan feliz! Hoy es un día maravilloso...";
			link.l1 = "";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = "¡Vamos, Charles! ¡Este mentiroso estará muerto antes de tocar el suelo!";
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = "Estoy bien, Charles, está bien. ¿Cómo está Nathan?";
			link.l1 = "  Tanta   sangre...   Dannie,   ¿está   respirando?   ¡Veo   que   está   respirando!";
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = "¡Más rápido, querido, no pierdas tiempo!";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "¿Charles, estás bien? ¡Qué baño de sangre! Lo siento, estábamos atrapados arriba, había una docena de esos bastardos, así que tuve que ocuparme de ellos primero.";
			link.l1 = "Está bien, lo manejé. Me alegra haber podido terminar esa historia con Jacques... finalmente. Obtuvo lo que merecía.";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "Está bien, mi querido, terminemos aquí y regresemos. ¡No puedo dejar de pensar en Nathan, ¿cómo está? ¡Él me protegió de esa bala!";
			link.l1 = "Tienes razón, cariño, yo también me preocupo. Ve, estoy justo detrás de ti.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "¡Encontramos a Marcus! Estaba en la bodega de carga, atado e inconsciente.";
			link.l1 = "¿Está vivo?";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "No te preocupes, amor, el Barón Tyrex vivirá incluso más que nosotros. Apenas se ha despertado y ya está zumbando, sigue pidiendo ron, su sable y el puente, en ese orden.";
			link.l1 = "¡Ese es nuestro viejo Marcus! Déjalo descansar un poco mientras terminamos aquí y luego volvamos a la orilla.";
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Lamento mucho, querido... Primero nuestro fiel amigo Tichingitu, ahora Gino... ¡Barbazon debería haber sido asesinado una docena de veces por todo lo que ha hecho!";
				link.l1 = "Lamentablemente lo hice solo una vez. También me siento mal... Pero ganamos, y él no volverá a herir a nadie nunca más.";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "¡Me siento tan mal por Gino, Charles! ¡Cuando me enteré, no lo podía creer! ¿Cómo estás, amor?";
					link.l1 = "No puedo creerlo tampoco... qué manera de irse... no imaginé que este día terminaría así.";
				}
				else
				{
					dialog.text = "Me pregunto, ¿escribirán los futuros historiadores sobre la gran batalla de la Bahía del Corsario? El día en que los barones de la Hermandad de la Costa se encontraron en batalla abierta - ¡apuesto a que la Guardia Costera Española está secándose las lágrimas de gratitud! Pero, ¡hemos ganado de nuevo! Nuestros amigos están vivos, y nuestros enemigos están muertos - ¡un glorioso regalo de bodas!";
					link.l1 = "Sí, vaya celebración, pero lo logramos, mi ángel. Lo logramos.";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "Vamos, Dannie nos encontró una casa aquí en las afueras de la ciudad, no quiero volver al barco ahora hasta que esté limpio. Nos sentaremos y beberemos por aquellos que no lo lograron.";
			link.l1 = "Sí, Helen, vamos.";
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "¡Me siento tan mal por Gino, Charles! ¡Cuando lo supe, no lo creí! ¿Cómo estás?";
				link.l1 = "No puedo creerlo tampoco... qué manera de irse... No imaginé que este día acabaría así.";
			}
			else
			{
				dialog.text = "¿Has visto a Hawk? Dannie me dejó salir cuando Gino dijo 'el peligro ha pasado'. Me alegra que todo esté bien. Nuestros amigos están vivos, y nuestros enemigos están muertos: ¡un glorioso regalo de bodas!";
				link.l1 = "Yo también, querido. Y ganamos. Barbazon está muerto, los barones están reuniendo lo que queda de sus tripulaciones. La lucha ha terminado.";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "Charles, veo que apenas te mantienes en pie, pero visité la taberna y no creerás lo que escuché del tabernero.";
			link.l1 = "Sí, lo escuché de Jan, él también ha estado allí. Me parece que nuestro querido indio se ha ido por el camino de la guerra. Demos un paseo hasta la Cala Sabo-Matila, algunas personas lo vieron partir en esa dirección.";
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = "¡Dios en el cielo! ¡Ese es el espíritu, Tichingitu! ¡Uf, me estoy partiendo de risa aquí! ¿Por qué nosotros, los europeos, no adoptamos también tal costumbre?! ¡Oh, Charles, casi te duermes de pie! Vamos, Dannie encontró una casa para nosotros aquí en las afueras - necesitas descansar un poco.";
			link.l1 = "Guía el camino... Creo que me he quedado dormida en esa playa antes.";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "tonzag_jailed":
			dialog.text = "... Está bien.";
			link.l1 = "Me alegra oír eso.";
			link.l1.go = "exit";
			link.l2 = "¿De veras?";
			link.l2.go = "tonzag_jailed_1";
			locCameraFromToPos(-15.50, 2.28, -1.23, true, -27.00, -10.60, -22.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Sí.";
			link.l1 = "Es bueno oírlo.";
			link.l1.go = "exit";
			link.l2 = "¡Vamos, puedo ver que algo te molesta!";
			link.l2.go = "tonzag_jailed_2";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "¡Estoy completamente bien, déjalo ir!\n¡Charles, vete al infierno! ¡Odio las mazmorras, te odio a ti, y odio esta maldita isla! ¡Sácame de aquí inmediatamente!\nLo siento... Realmente no me gustan las mazmorras, ¡no me toques!";
			link.l1 = "Lo siento. Todos tememos algo.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "¡AAAA! ¡Déjanos salir de aquí! ¡Charles, haz algo!";
			link.l1 = "¡Recupérate!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
			AddDialogExitQuestFunction("Tonzag_TichingituAfterShot");
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "Mi capitán, el enemigo ha roto el casco en la segunda cubierta y ha lanzado una partida de abordaje. ¡Las batallas están ocurriendo por todo el barco, y la mayoría de las tripulaciones de los cañones han sido neutralizadas! ¡Necesitamos rescatar a nuestra tripulación y a Hercule! ¿Irás tú, o debería ir yo?";
			link.l1 = "¡Esta vez iré yo mismo, Helen! ¡Toma el mando del barco y sáquenos de aquí!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "¡Aye aye, mi Capitán! No te defraudaré, y por favor, ¡ten cuidado!";
			link.l1 = "Lo sé, Helen. ¡Y tú también ten cuidado!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "¡Victoria, mi capitán! La partida de desembarco ha sido eliminada, el enemigo eligió retirarse y se dirigió al sur. La condición del barco es aceptable. Tripulación viva: "+GetCrewQuantity(pchar)+" gente. ¡Informe completado!";
			link.l1 = "Gracias, Helen, y qué...";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "¡Desvístete, vencedor, tu premio es hacer lo que te plazca conmigo!";
			link.l1 = "Uh...";
			link.l1.go = "tonzag_after_victory_2";
			link.l2 = "¡Vamos!";
			link.l2.go = "tonzag_after_victory_2";
		break;
		
		case "tonzag_after_victory_2":
			dialog.text = "¡Oh, hola, Hércules! ¡Perdona, nos has pillado en un momento inoportuno! ¡Pero maldita sea, me alegra verte vivo y cubierto de la sangre de otros, un estado natural para ti, ¿eh?!";
			link.l1 = " ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HelenBoardingDialog");
		break;
		
		case "tonzag_after_victory_3":
			dialog.text = "";
			link.l1 = "Bueno, Helen, ¡eres algo!";
			link.l1.go = "tonzag_after_victory_4";
		break;
		
		case "tonzag_after_victory_4":
			dialog.text = "Aún no he empezado, mi capitán. ¿Celebramos?";
			link.l1 = "¡No necesito convencerme!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_dead":
			dialog.text = "No mires, no mires, no mires... ¡Este es otro mundo, mi capitán! ¡No puede ser así!";
			link.l1 = "Creo que este es nuestro mundo ahora, querido. Y tienes razón, no nos demoremos...";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
		break;
		
		// Jason Исла Мона
		case "IslaMona":
			dialog.text = "Tengo miedo de que esta pandemia esté afectando a tus chicas, Rodrigo. ¡Mantenlas ocupadas con el tejido o algo así!";
			link.l1 = "Esta conversación claramente no lleva a ninguna parte. Acordamos que iremos a la iglesia mañana. A rezar... por supuesto.";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_2":
			dialog.text = "¡Estoy orgullosa de ti, mi amor!";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			sld = characterFromId("Himenes_companion_1");
			sld.dialog.currentnode = "island_man_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_4":
			dialog.text = "Bueno, Charles...";
			link.l1 = "¿Qué tienes en mente otra vez, Helen?";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
			dialog.text = "¡El hecho de que la pareja más escandalosa del Caribe posea dos islas enteras! Mi refugio pirata de Isla Tesora y tu tierra prometida - ¿cuánto tiempo crees que pueden durar cuando la civilización finalmente llegue a las Indias Occidentales?";
			link.l1 = "El tiempo suficiente para durar toda nuestra vida, querido. ¿Y después? No podemos controlar lo que sucederá entonces. Otros contarán nuestra historia. Lo más importante es que tú y yo estamos aquí y ahora, juntos y felices.";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
			dialog.text = " Hablando de la felicidad... Estoy a punto de subir ahora: necesito encender las velas, hacer la cama, tal vez escribir en mi diario...";
			link.l1 = "Me quedaré aquí un poco más, y luego subiré para ayudarte a 'hacer la cama'.";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
			dialog.text = "No te tardes demasiado...";
			link.l1 = " ";
			link.l1.go = "IslaMona_8";
		break;
		
		case "IslaMona_8":
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
			DoQuestCheckDelay("Helena_LoveSex", 2.5);
			NextDiag.CurrentNode = "sex_after";
			pchar.questTemp.IslaMona.Doorlock = "true";
		break;
		
		case "drinking_refuse":
			dialog.text = "¿Estás realmente tan ocupado? Qué pena, pero lo entiendo. Encontraré otra cosa con чем ocuparme.";
			link.l1 = "";
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_wait";
			
			pchar.questTemp.HelenDrinking.Result = "no_visit";
			CloseQuestHeader("HelenDrinking");
		break;
		
		case "drinking_accept":
			dialog.text = "Es agradable que lo recuerdes. Quería decirte que estoy muy agradecida. No todos los días alguien te salva de... ya sabes qué. Vamos a tomar algo. Invito yo.";
			link.l1 = "Helen... ¿Qué dirá Gladys?";
			link.l1.go = "drinking_accept_1";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToHouse");
		break;
		
		case "drinking_accept_1":
			dialog.text = "Muy gracioso, Charles. Vamos, y no me molestes.";
			link.l1 = "¿Es esta una cita?";
			link.l1.go = "drinking_accept_1_1";
			link.l2 = "Ya voy, no hay necesidad de ponerse gruñón.";
			link.l2.go = "drinking_accept_1_2";
		break;
		
		case "drinking_accept_1_1":
			dialog.text = "¡Ja, ja! ¡Eso quisieras! ¡Tendría que emborracharme por completo!";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "drinking_accept_1_2":
			dialog.text = "Eso es mejor.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "drinking_in_tavern":
			dialog.text = "";
			link.l1 = "... tenía muchas virtudes, pero no podía aguantar el alcohol. Así nos conocimos.";
			link.l1.go = "drinking_in_tavern_1";
			link.l2 = "... mi padre insistió en el servicio militar. Cedí y fui a París con una carta de recomendación. Pero nunca llegué a la dirección designada y me convertí en artista.";
			link.l2.go = "drinking_in_tavern_2";
		break;
				
		case "drinking_in_tavern_1":
			dialog.text = "Ah, ahora entiendo de qué virtudes hablas. ¿Cómo se llamaba?";
			link.l1 = "Lulú.";
			link.l1.go = "drinking_in_tavern_1_1";
		break;
		
		case "drinking_in_tavern_1_1":
			dialog.text = "Lulú... Con estas historias, has arruinado París para mí por completo. Pensé que era una ciudad de gran vida, pero solo suena como un gran burdel elegante.";
			link.l1 = "¿Condenas los burdeles?";
			link.l1.go = "drinking_in_tavern_1_2";
		break;
		
		case "drinking_in_tavern_1_2":
			dialog.text = "Sí, Capitán, y no entiendo a los hombres que las visitan.";
			link.l1 = "(mirar la jarra)";
			link.l1.go = "drinking_in_tavern_1_4";
			link.l2 = "(tiene una tos terrible)";
			link.l2.go = "drinking_in_tavern_1_4";
			link.l3 = "Eh... cada uno a lo suyo... ¿supongo?";
			link.l3.go = "drinking_in_tavern_1_4";
		break;
		
		case "drinking_in_tavern_1_4":
			dialog.text = "(ríe) ¡Ja! ¡Deberías haber visto tu cara! ¿Asustado? ¡Levantemos otra! ¡A París!";
			link.l1 = "¡A París!";
			link.l1.go = "drinking_in_tavern_3";
		break;
		
		case "drinking_in_tavern_2":
			dialog.text = "(ríe) ¿T-tú? ¿Un artista? Entonces, la belleza y el orgullo de la flota inglesa, un violador y simplemente un hijo de perra Donovan, murió a manos de un artista parisino? ¡Ah, qué lástima que no llevabas tu impoluto jabot para el abordaje y no golpeaste a esa escoria con un bastón!";
			link.l1 = "Sí, muy desafortunado. Justo ese día el jabot estaba en la lavandería.";
			link.l1.go = "drinking_in_tavern_2_1";
		break;
		
		case "drinking_in_tavern_2_1":
			dialog.text = "(ríe) Bueno, gracias, Charles. No sé cómo irá el resto de la noche, pero la velada ya ha sido estupenda. Incluso podría permitirte pintar mi retrato. Pero, ojo, ¡no en el mismo estilo en que pintabas a tus chicas parisinas!";
			link.l1 = "¡Ja! Eso es si acepto pintarte.";
			link.l1.go = "drinking_in_tavern_3";
		break;
		
		case "drinking_in_tavern_3":
			dialog.text = "Disculpa, mi capitán, escuchando sobre tus aventuras y la vida de nobles... cortesanos de ambos sexos. ¡Muerde de tiburón, nunca creeré que no pudiste encontrar algo más valioso que hacer con tu tiempo! Ni se te ocurra decirme que todo lo que hiciste fue manchar lienzos y derrochar el dinero de papá. No habrías sobrevivido un día con nosotros si eso fuera cierto.";
			link.l1 = "Tenía... otros intereses.";
			link.l1.go = "drinking_in_tavern_" + pchar.HeroParam.HeroType;
		break;
		
		case "drinking_in_tavern_herotype_3":
			dialog.text = "";
			link.l1 = "Combiné la vida en la corte con el servicio militar, pero no... jeje, no exactamente de la manera que mi padre quería, por supuesto. Un par de escapadas por la ventana y una pelea - y me hice amigo de los guardias. Y naturalmente aprendí muchas cosas, endurecí mi cuerpo. Los camaradas mayores me enseñaron a recibir un golpe, llevar armadura, manejar una espada y relajarme adecuadamente. La última parte especialmente me convenía, por supuesto. No lo creerás, pero no todos pueden blandir una espada desde la mañana hasta el mediodía y luego beber desde el mediodía hasta la mañana siguiente.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_1":
			dialog.text = "";
			link.l1 = "¿Crees que fue fácil en la capital para un noble con mala reputación y una bolsa vacía, perdiendo la carta de recomendación de papá el primer día? Tuve que imponerme y no dejar que nadie se burlara de mí. Las lecciones de esgrima en casa no se olvidaron, y respondía a cualquier mirada de reojo con un duelo. Luego realmente me enganché. Aun así, no maté a nadie y logré salir de París antes de toparme con un luchador experimentado que me hubiera acabado.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_4":
			dialog.text = " ";
			link.l1 = "Pasé mucho tiempo en los cementerios. No pienses nada malo - era simplemente un pasatiempo popular en mi círculo social. Para mostrar coraje, íbamos a un cementerio por la noche, poníamos botellas vacías en la cerca y les disparábamos con un cronómetro. Durante la noche, gastábamos cien balas y una caja de champán. Ahora, por supuesto, me avergüenzo de tal comportamiento, pero entonces el ganador se llevaba un buen bote y obtenía algunos... favores del lado femenino de la corte. Todo se utilizaba - incluso jugueteé un poco con mezclas de pólvora. Pero por qué ninguno de nosotros pensó en aprender a hacer cartuchos de papel - nunca lo sabré.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_2":
			dialog.text = "";
			link.l1 = "Estudié, y con bastante diligencia - estuve incluso cerca de entrar en la Sorbona. Trabajé en una oficina hasta que se volvió aburrido, y en general - hice un poco de todo. El maestro, un viejo amigo de mi padre, prefería la práctica a la teoría, así que pude ver París desde todos los ángulos y hablar con diferentes personas: desde bandidos hasta nobles. Todo eso terminó siendo útil aquí.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_4":
			dialog.text = "¿Y... eso es todo? Así que todavía hay algo en ti, mi capitán. Algo que aún no has visto en ti mismo. ¡Por ti!";
			link.l1 = "¡Buen brindis!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TavernChange");
		break;
		
		case "drinking_my_background":
			dialog.text = "";
			link.l1 = "Cuéntame tu historia, Helen. Mis aventuras en la Capital palidecen en comparación con una muchacha de menos de treinta años comandando un bergantín con cien hombres a bordo.";
			link.l1.go = "drinking_my_background_1";
		break;
		
		case "drinking_my_background_1":
			dialog.text = "Menos de treinta, ¿eh, Charles? ¡Por un comentario tan fuerte, tendrás que pagar la próxima ronda! Todos mis chicos están muertos, y ya no mando un balandro. Francamente, no sé si volveré a comandar alguno.";
			link.l1 = "Lamento, Helen. No quise tocar una fibra sensible. Pero ¿por qué piensas que tu carrera de capitán ha terminado?";
			link.l1.go = "drinking_my_background_2";
		break;
		
		case "drinking_my_background_2":
			dialog.text = "Porque mi tripulación está muerta, y otra distinta nunca me aceptará. ¡Eh! Bien, mi capitán, me has contado mucho sobre tu vida; ¡ahora es mi turno! La verdad no está en el fondo de esta taza, así que prescindamos del misterio.";
			link.l1 = "";
			link.l1.go = "drinking_my_background_3";
		break;
		
		case "drinking_my_background_3":
			dialog.text = "Mi caso, Charles, es único. Mi padre fue uno de los mejores marineros de estas partes, muy respetado por el Diablo del Bosque, su tripulación lo adoraba, y él me amaba más que a la propia vida.";
			link.l1 = "";
			link.l1.go = "drinking_my_background_4";
		break;
		
		case "drinking_my_background_4":
			dialog.text = "Llévate incluso una de estas cosas, y él me habría enviado a Londres a vivir en... civilización, o me habría dejado marchitarme aquí como mi madre. Al principio todo salió genial: quería libertad, libertad real, Charles, y un hábil mando de un barco de guerra con una tripulación leal te da exactamente eso. Y mi padre me dio todo lo que pudo. Salí al mar con él a los doce años, pasé los primeros seis meses persiguiendo ratas en la bodega, y solo entonces se me permitió trabajar con los marineros.";
			link.l1 = "¿Sean MacArthur te convirtió en una rata de barco? Lo siento, Helen, ¡pero no hay vuelta atrás para eso! ¿Cómo te aceptó la tripulación?";
			link.l1.go = "drinking_my_background_5";
		break;
		
		case "drinking_my_background_5":
			dialog.text = "Bueno, ¿quizás exagero un poco en aras de una buena historia? La tripulación de mi padre me aceptó; reunió a buena gente. Pero desde entonces, tengo miedo... de las bodegas y de cualquier pequeño espacio oscuro en general. ¡Ja! ¡Svensson casi mata a mi padre cuando se enteró!";
			link.l1 = "Él es importante para ti. Claramente jugó un papel en tu destino, no menos que Sean.";
			link.l1.go = "drinking_my_background_6";
		break;
		
		case "drinking_my_background_6":
			dialog.text = "Sí. Todos los barones le dijeron directamente a mi padre que era un tonto, pero fue el Diablo del Bosque quien le dio su aprobación y le estrechó la mano después de que rompí el récord de la tripulación al trepar al mástil. Ese momento se quedará conmigo para siempre: los gritos triunfantes de la tripulación y, dondequiera que mirara, el limpio horizonte del mar. Y la mirada aprobatoria de mi padre, no pude verla, pero la sentí con todo mi corazón.";
			link.l1 = "Mi triunfo terminó conmigo cayendo del aparejo el primer día rumbo a Guadalupe.";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.TakeFolke")) {
				link.l1 = link.l1+" Mi timonel, Deluc, también tenía una mirada muy reveladora."}
			link.l1.go ="drinking_my_background_7";
		break;
		
		case "drinking_my_background_7":
			dialog.text = "Ah-ha-ha! I can imagine! Don't worry, that was a long time ago; now you're a real sea wolf!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_8";
		break;
		
		case "drinking_my_background_8":
			dialog.text = "¡A nuestros triunfos!";
			link.l1 = "¡Oíd, oíd!";
			link.l1.go = "drinking_my_background_12";
		break;
		
		case "drinking_my_background_12":
			dialog.text = "... Y luego fui ascendiendo poco a poco en el escalafón, serví en la mesa del capitán en los consejos con mi padre y los oficiales. Aprendí mucho. A partir de los quince años, empezaron a llevarme a campañas militares, y maté a un hombre en mi primera batalla. Fue una campaña repugnante; no deberíamos haber zarpado un lunes... ¡Realmente no debimos!";
			link.l1 = "¿A los quince? Me asustas, Helena.";
			link.l1.go = "drinking_my_background_13";
		break;
		
		case "drinking_my_background_12":
			dialog.text = "No entendí ni siquiera qué pasó. El mercader holandés tenía su vanguardia - mercenarios de la Compañía. Decidieron jugar con audacia y contraatacaron nuestra cubierta de popa. Y yo, tonta, sin ningún miedo por mi vida, saqué mi cabeza rubia. Inmediatamente recibí un golpe con la culata de una pistola. Pero un momento antes logré clavar mi estoque en algún tonto de la Compañía.";
			link.l1 = "¡Por Dios, ¿y qué hay de Sean? ¿Cómo no te echó a tierra después de eso?";
			link.l1.go = "drinking_my_background_13";
		break;
		
		case "drinking_my_background_13":
			dialog.text = "Mi padre tampoco salió indemne de aquella batalla, y la visión de mi cabeza tonta y agrietada ciertamente no ayudó. Empezó a decaer lentamente, y probablemente nadie lo notó excepto yo. Y luego se fue. Según su testamento, heredé el Arcoíris con su tripulación y fondos suficientes para mantener el barco a flote durante un año.";
			link.l1 = "¿Y te aceptó la tripulación como capitán?";
			link.l1.go = "drinking_my_background_14";
		break;
		
		case "drinking_my_background_14":
			dialog.text = " No vivimos en un cuento de hadas, mi capitán. Algunos recibieron la voluntad de mi padre con hostilidad - las cosas tomaron un giro desagradable\nSi al menos un marinero hubiera dejado el Arcoíris, negándose a servir bajo mi mando, habría sido muy malo para mi imagen. Pero Svensson intervino y puso a todos en su lugar. Nadie dejó la tripulación abiertamente... en aquel entonces. Durante siete años, comandé a mi belleza, transporté mercancías dudosas para el Diablo del Bosque, busqué tesoros, viví... Pero ahora, todo eso es parte del pasado.";
			link.l1 = "No en el pasado. ¡Creo que estás destinado a navegar bajo tu propia bandera de nuevo! ¡Brindemos por eso!";
			link.l1.go = "drinking_my_background_sea";
			link.l2 = "Puede que no recuperemos el barco, pero tu estoque sigue contigo.";
			link.l2.go = "drinking_my_background_land";
		break;
		
		case "drinking_my_background_sea":
			dialog.text = "Sabes, cuando lo dices así, yo también lo creo. ¡Vamos a beber!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_15";
			
			AddCharacterSkill(npchar, SKILL_COMMERCE, 5);
			AddCharacterSkill(npchar, SKILL_ACCURACY, 5);
			AddCharacterSkill(npchar, SKILL_CANNONS, 5);
			AddCharacterSkill(npchar, SKILL_SAILING, 5);
			AddCharacterSkill(npchar, SKILL_REPAIR, 5);
			AddCharacterSkill(npchar, SKILL_GRAPPLING, 5);
			AddCharacterSkill(npchar, SKILL_DEFENCE, 5);
			notification("Naval Skills +", "Helena");
			
			pchar.questTemp.HelenDrinking.Background = "sea";
		break;
		
		case "drinking_my_background_land":
			dialog.text = "¿Pero me traerá felicidad mi espada? La respuesta probablemente esté en el fondo de esta jarra. ¡Bebamos!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_15";
			
			AddCharacterSkill(npchar, SKILL_F_LIGHT, 5);
			AddCharacterSkill(npchar, SKILL_FENCING, 5);
			AddCharacterSkill(npchar, SKILL_F_HEAVY, 5);
			AddCharacterSkill(npchar, SKILL_PISTOL, 5);
			AddCharacterSkill(npchar, SKILL_FORTUNE, 5);
			AddCharacterSkill(npchar, SKILL_LEADERSHIP, 5);
			AddCharacterSkill(npchar, SKILL_SNEAK, 5);
			notification("Personal Skills +", "Helena");
			
			pchar.questTemp.HelenDrinking.Background = "land";
		break;
		
		case "drinking_my_background_15":
			dialog.text = "He estado pensando en tu vida en Europa... Mira, eres un petimetre de ciudad, y yo solo soy una chica normal, pero ya nos hemos hecho un nombre en el rincón más peligroso del mundo.";
			link.l1 = "¡Parece un brindis! Entonces, ¿hay algo que nos une?";
			link.l1.go = "drinking_my_background_16";
		break;
		
		case "drinking_my_background_16":
			dialog.text = "Bueno, yo me sostengo sobre los hombros de mi padre. No sé tú, pero quizás tu familia también ha tenido no menos influencia sobre ti. ¿Quizás aún no te has dado cuenta?";
			link.l1 = "Le preguntaré a mi querido hermano una vez que lo saque de la prisión.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TavernEmpty");
		break;
		
		case "drinking_game":
			dialog.text = "Bueno, eso es todo, mi capitán. Hemos intercambiado historias, es hora de dar por terminada la noche.";
			link.l1 = "Hmm, esperaba un final diferente para la velada.";
			link.l1.go = "drinking_game_1";
		break;
		
		case "drinking_game_1":
			dialog.text = "La noche aún no ha terminado. Te propongo un juego: si juegas bien tus cartas, tal vez tus plegarias sean respondidas.";
			link.l1 = "¿Vamos a jugar a las cartas? ¡Estoy dentro!";
			link.l1.go = "drinking_game_2";
		break;
		
		case "drinking_game_2":
			dialog.text = "Tranquilo, lobo de mar. No jugaré al strip póker contigo.";
			link.l1 = "Sí, tienes razón, Helen. No tenemos privacidad aquí.";
			link.l1.go = "drinking_game_3";
		break;
		
		case "drinking_game_3":
			dialog.text = "Eso no es lo único que nos falta, Charles... No es un juego de cartas, pero no te preocupes, apuesto a que eres un maestro en ello. 'Yo Nunca' - ¿has oído hablar de él?";
			link.l1 = "Familiar. De la vida pasada. ¿Y lo tocas a menudo?";
			link.l1.go = "drinking_game_4";
		break;
		
		case "drinking_game_4":
			dialog.text = "Siempre quise intentarlo, pero no tenía con quién jugar.";
			link.l1 = "Es un juego bastante audaz para nuestra primera bebida compartida. ¿Estás seguro?";
			link.l1.go = "drinking_game_5";
			link.l2 = "Por cierto, ¿dónde está todo el mundo? ¿Estamos solos aquí?";
			link.l2.go = "drinking_game_6";
		break;
		
		case "drinking_game_5":
			dialog.text = "Sí, después de los recientes eventos, necesito vivir un poco. Hacer algo tonto, ¿sabes?";
			link.l1 = "No, siempre termina mal, Rumba.";
			link.l1.go = "drinking_game_refuse";
			link.l2 = "¡Comencemos! ¡Las damas primero!";
			link.l2.go = "drinking_game_accept";
		break;
		
		case "drinking_game_6":
			dialog.text = "Los envié a todos a casa - no hay necesidad de permitir que los forasteros escuchen.";
			link.l1 = "No, siempre termina mal, Rumba.";
			link.l1.go = "drinking_game_refuse";
			link.l2 = "¡Hagámoslo! ¡Las damas primero!";
			link.l2.go = "drinking_game_accept";
		break;
		
		case "drinking_game_refuse":
			dialog.text = "Lástima, pero quizá tengas razón. ¿Otro trago entonces?";
			link.l1 = "¡Comencemos! ¡Las damas primero!";
			link.l1.go = "drinking_game_refuse_1";
		break;
		
		case "drinking_game_refuse_1":
			dialog.text = "He hecho los arreglos - la habitación de arriba es tuya. Estaba ocupada por un importante oficial francés, pero los chicos del Demonio del Bosque le pidieron amablemente que dejara el lugar. Ve a descansar un poco - no te dejaré deambular por la calle, o peor aún, salir al mar, en este estado.";
			link.l1 = "¡Sí, señora!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToTavernRoom");
		break;
		
		case "drinking_game_accept":
			dialog.text = "¡Ja! ¡Hic! ¡Significa que estás comenzando!";
			link.l1 = "¡Cuidado, cariño! Hmm. ¡Nunca he perseguido ratas en la bodega!";
			link.l1.go = "drinking_game_accept_1";
		break;
		
		case "drinking_game_accept_1":
			dialog.text = "¿Así que así es como es? ¡Hay que estar en guardia contigo! (Bebe)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_2";
		break;
		
		case "drinking_game_accept_2":
			dialog.text = "¡Brr! Solo el recuerdo de eso... Bueno, prepárate, guapo: ¡nunca me he caído de los obenques!";
			link.l1 = " ";
			link.l1.go = "drinking_game_accept_3";
		break;
		
		case "drinking_game_accept_3":
			dialog.text = "";
			link.l1 = "¡Buen intento! ¡Permítame, mademoiselle, brindar por usted! (Bebe)";
			link.l1.go = "drinking_game_accept_4";
		break;
		
		case "drinking_game_accept_4":
			dialog.text = "";
			link.l1 = "Nunca he sido supersticiosa.";
			link.l1.go = "drinking_game_accept_5";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 1;
			SetCamShuttle(loadedLocation);
			SetPitch(0.95);
		break;
		
		case "drinking_game_accept_5":
			dialog.text = "¡Y te llamas a ti mismo marinero! Sabes muy bien qué clase de gente somos. Nunca se sabe qué traerá el viaje, no se sabe cuándo ni dónde verás tierra, si es que la ves. ¡Tienes que buscar respuestas más allá de los mapas y las herramientas de navegación! ¡A tu salud! (Bebe)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_6";
		break;
		
		case "drinking_game_accept_6":
			dialog.text = "Y las chicas que pintaste en persona... ¿Les gustó el resultado?";
			link.l1 = "No siempre les gustaban las pinturas, pero, um... el resultado - siempre.";
			link.l1.go = "drinking_game_accept_7";
		break;
		
		case "drinking_game_accept_7":
			dialog.text = "¡Charles! Si nos hubiéramos encontrado en aquel entonces, te habría disparado o tomado como rehén para pedir rescate. Y, por cierto, nunca he cogido pinceles.";
			link.l1 = "¡Eh! Bueno, eso es completamente banal. Querida Helen, si empiezo a enumerar cosas que nunca has emprendido...";
			link.l1.go = "drinking_game_accept_8";
		break;
		
		case "drinking_game_accept_8":
			dialog.text = "Está bien, de acuerdo, jugaré limpio. Tu turno, mi capitán.";
			link.l1 = "(Bebe) ¡Hic! Hmm... Nunca había tenido modelos que me golpearan en la cabeza con la empuñadura de una pistola.";
			link.l1.go = "drinking_game_accept_9";
		break;
		
		case "drinking_game_accept_9":
			dialog.text = "(Sorbe) Uf. Estamos jugando a este juego de manera equivocada, querido. Pensé que estaríamos bebiendo y conociéndonos, pero en cambio estamos intercambiando pullas y... y... Hip. ¡Maldita sea!";
			link.l1 = " ";
			link.l1.go = "drinking_game_accept_10";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 2;
			SetCamShuttle(loadedLocation);
			SetPitch(0.90);
		break;
		
		case "drinking_game_accept_10":
			dialog.text = "¡Hagámoslo más interesante! Y preferiblemente algo que no sea de lo que estábamos hablando hace una hora.";
			link.l1 = "Nunca me he despertado en un lugar desconocido después de una juerga.";
			link.l1.go = "drinking_game_accept_11";
		break;
		
		case "drinking_game_accept_10":
			dialog.text = "¡Ay! ¡Maldita sea, Charles! (Bebe)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_11";
		break;
		
		case "drinking_game_accept_11":
			dialog.text = "Yo... Hic... no puedo creerlo. Confieso, culpable - la pequeña Rumba solía tocar fondo. ¡Pero nunca he estado en prisión!";
			link.l1 = "¿Cómo lo hiciste...?";
			link.l1.go = "drinking_game_accept_12";
		break;
		
		case "drinking_game_accept_12":
			dialog.text = "¡Jajaja! ¡Bebe, bebe!";
			link.l1 = "Lamentaré esto. (Bebe)";
			
			if (IsCharacterEquippedArtefact(pchar, "totem_01")) {
				link.l1.go = "drinking_game_accept_13";
			} else {
				link.l1.go = "exit";
				AddDialogExitQuestFunction("HelenDrinking_LightsOut");
			}
		break;
		
		case "drinking_game_accept_13":
			dialog.text = "Vamos, mi querido. ¡La última pregunta y la última oportunidad para vencerme!";
			link.l1 = "No... Yo... Vamos a tomar un poco de aire fresco.";
			link.l1.go = "drinking_game_enough";
			link.l2 = " A menudo he bebido, pero nunca así... Nunca me he emborrachado t-tanto con una chica. Juro por mi p-palabra, b-beber es realmente un g-gran pecado...";
			link.l2.go = "drinking_game_accept_14";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 3;
			SetCamShuttle(loadedLocation);
			SetPitch(0.85);
		break;
		
		case "drinking_game_enough":
			dialog.text = "¡Eh!";
			link.l1 = "";
			link.l1.go = "drinking_game_refuse_1";
		break;
		
		case "drinking_game_accept_14":
			dialog.text = "";
			link.l1 = "¿E-espera... no estás bebiendo?";
			link.l1.go = "drinking_game_accept_15";
		break;
		
		case "drinking_game_accept_15":
			dialog.text = "¡Ja-ja-ja! ¡Eso es hilarante! Tienes un objetivo elevado, mi capitán. Que te sea... ¡hip!... conocido...";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_16";
		break;
		
		case "drinking_game_accept_16":
			dialog.text = "Que tengo la desgracia de vivir en una tripulación compuesta solo por hombres, y debo comportarme con cuidado. Soy una chica honesta.";
			link.l1 = "Me a-alegro por ti, H-Helen.";
			link.l1.go = "drinking_game_accept_17";
		break;
		
		case "drinking_game_accept_17":
			dialog.text = "Serás aún más feliz, ¡porque gané! Pero, para ser honesta, nunca me he emborrachado tanto con un hombre tampoco.";
			link.l1 = "(Bebe en silencio) P-por ti. Felicitaciones... h-hic...";
			link.l1.go = "drinking_game_accept_18";
		break;
		
		case "drinking_game_accept_18":
			dialog.text = "¡Eh-eh-eh! Capitán, ¿a dónde va? ¿Ofendido, tal vez?";
			link.l1 = "T-tengo... un descanso? Solo voy a buscar mi e-espada...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_ExitTavern");
		break;
		
		case "drinking_at_svenson":
			dialog.text = "Capitán, ¿estás listo? No hay vuelta atrás, y si algo sale mal, haré que te cases conmigo.";
			link.l1 = "¡Uf! ¡Déjame al menos tomar un poco de aire fresco! ¿Estás segura de esto, Helen?";
			link.l1.go = "drinking_at_svenson_1";
		break;
		
		case "drinking_at_svenson_1":
			dialog.text = "¡Sí, maldita sea, y no te quedes ahí como un poste! ¡Necesito perderme, aunque sea solo por una noche!";
			link.l1 = "Me temo que después de esta noche, seré yo quien quiera perderse. Vámonos antes de que despertemos a todo el pueblo.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_EnterSvenson");
		break;
		
		case "drinking_give_key":
			dialog.text = "Capitán, toma la llave y sube las escaleras. Debería haber un cofre; probablemente lo viste cuando lo tenía Svensson. Coge el barril y regresa inmediatamente.";
			link.l1 = "Espera, querida, ¿por qué tengo que robar a tu jefe?";
			link.l1.go = "drinking_give_key_1";
			
			GiveItem2Character(pchar, "key3");
			PlaySound("interface\important_item.wav");
		break;
		
		case "drinking_give_key_1":
			dialog.text = "No seas tonto. Llevo aquí desde niño; si vuelven los dueños, puedo encargarme y cubrirte. ¡Vamos, no bajes la vela ahora!";
			link.l1 = "¡Aguda como un cuchillo, una verdadera contrabandista! Espera, seré rápido.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GotKey");
		break;
		
		case "drinking_got_whiskey":
			dialog.text = "¿Entendido?";
			link.l1 = "¡Por supuesto! No es el primer cofre que vacié, y ciertamente no será el último.";
			link.l1.go = "drinking_got_whiskey_1";
		break;
		
		case "drinking_got_whiskey_1":
			dialog.text = "¡Estoy orgullosa de ti! ¡Jaja! ¡Whiskey irlandés de primera, 'Bushmills'! No nos servirán tal bebida en la taberna.";
			link.l1 = "Suena bien, pero ¿Svensson no notará que falta?";
			link.l1.go = "drinking_got_whiskey_2";
		break;
		
		case "drinking_got_whiskey_2":
			dialog.text = "Definitivamente lo notará, pero él mismo no lo bebe. Parece que lo ha guardado como regalo para su compañero pirata Dodson, y Dodson o bien desapareció o mató a alguien...";
			link.l1 = "¡Eso es terrible! Tal regalo no debe desperdiciarse. ¡Toma el barril y cambiemos de escenario!";
			link.l1.go = "drinking_got_whiskey_3";
		break;
		
		case "drinking_got_whiskey_3":
			dialog.text = "Bien dicho, capitán. Una cosa más, dime, ¿tomaste algo más del cofre? Responde honestamente.";
			if (HelenDrinking_RobbedSvenson()) {
				link.l1 = "Tomé algo, un hábito, ya sabes.";
				link.l1.go = "drinking_got_whiskey_notbelieve";
			}
			
			link.l2 = "No. No estoy segura de si soy pirata, pero definitivamente no soy ladrona.";
			link.l2.go = "drinking_got_whiskey_believe";
			
			if (HelenDrinking_RobbedSvenson()) {
				link.l2.go = "drinking_got_whiskey_notbelieve";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 2;
				notification("Helen disapproves", "Helena");
				pchar.questTemp.HelenDrinking.RobbedSvenson = true;
			}
		break;
		
		case "drinking_got_whiskey_believe":
			dialog.text = "De alguna manera te creo... ¡un tonto que soy!";
			link.l1 = "";
			link.l1.go = "drinking_get_out";
		break;
		
		case "drinking_got_whiskey_notbelieve":
			dialog.text = "Ve y asegúrate de que no hayas tomado nada por alguna razón.";
			link.l1 = "";
			link.l1.go = "exit";
			if (!HelenDrinking_RobbedSvenson()) {
				AddDialogExitQuestFunction("HelenDrinking_JoanEnter");
				TakeItemFromCharacter(pchar, "cask_whisky");
				sld = ItemsFromID("cask_whisky");
				sld.price = sld.pricebak;
				DeleteAttribute(sld, "pricebak");
			}
			
			NextDiag.TempNode = "drinking_got_whiskey_notbelieve";
		break;
		
		case "drinking_get_out":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_JoanEnter");
			TakeItemFromCharacter(pchar, "cask_whisky");
			sld = ItemsFromID("cask_whisky");
			sld.price = sld.pricebak;
			DeleteAttribute(sld, "pricebak");
		break;
		
		case "drinking_at_fort":
			dialog.text = "¡Eh, eh, querida! ¡Concéntrate! ¡Mi rostro, besado por la brisa del mar, está justo aquí!";
			link.l1 = "Uf, bueno, ¡tu disfraz es algo! Debes haber ahorrado mucho dinero en material de costura. Y yo... ¡hic! ¡He visto mucho! Pero esto... Pero esto es lo mejor que he visto.";
			link.l1.go = "drinking_at_fort_1";
			locCameraFromToPos(-1.65, 44.45, 76.64, true, -5.93, 42.10, 70.13);
		break;
		
		case "drinking_at_fort_1":
			dialog.text = "¡Todos dicen eso, pero por alguna razón, te creo! ¿De verdad te gusta?";
			link.l1 = "Bueno, por supuesto, acentúa muy favorablemente tu figura, aunque...";
			link.l1.go = "drinking_at_fort_2";
		break;
		
		case "drinking_at_fort_2":
			dialog.text = "¡Oh, ahora lo has arruinado todo!";
			link.l1 = "...aunque no tengo duda de que entre la gente común, ¡inspira asombro!";
			link.l1.go = "drinking_at_fort_3";
		break;
		
		case "drinking_at_fort_3":
			dialog.text = "Estoy bastante asombrada por este extraño hábito tan extendido entre la gente común y no tan común de llevar ropa europea tan densa con este calor. Eso hace que nuestros pueblos parezcan aún más cómicos... Me gusta mi atuendo, Charles. En él, me siento hermosa, y eso es importante para una mujer.";
			link.l1 = "Seguirías siendo igual de hermosa sin ese atuendo, Helen.";
			link.l1.go = "drinking_at_fort_4";
		break;
		
		case "drinking_at_fort_4":
			dialog.text = "¡Cuidado, mi capitán! ¡Decir cosas tan dulces puede corromper a una pobre chica!";
			link.l1 = "Si ella no está en contra, entonces yo tampoco estoy en contra.";
			link.l1.go = "drinking_at_fort_5";
		break;
		
		case "drinking_at_fort_5":
			dialog.text = "¡Ji-ji! Mejor pregúntame sobre otra cosa. Me gusta cuando te pones curioso.";
			link.l1 = "Entonces, dejemos espacio para una pregunta sobre tu atuendo. No creo que los lobos de mar puedan tomar en serio a un capitán con tal vestimenta.";
			link.l1.go = "drinking_at_fort_6";
		break;
		
		case "drinking_at_fort_6":
			dialog.text = "Y no creo que los lobos de mar, en general, puedan ver a una mujer como capitán, así que mi atuendo probablemente no agregó a mis problemas. O tal vez no tuvo tiempo de añadirlos ya que es algo nuevo. ¡Lo cosí yo misma!\n¡Ja-ja-ja! Solía usar uno de esos... ¿cómo se llaman? ¡Nuestros militares aún los usan! B-r-r... Ver uno de esos ahora me da náuseas.";
			link.l1 = "¿Uniformes?";
			link.l1.go = "drinking_at_fort_7";
		break;
		
		case "drinking_at_fort_7":
			dialog.text = "¡Oh, exactamente, un uniforme! ¡Un uniforme rojo! Como el que lleva ese tipo.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.GenQuest.BlockDialogCamera = true;
			AddDialogExitQuestFunction("HelenDrinking_OfficerAtFort");
		break;
		
		case "drinking_at_fort_7_1":
			dialog.text = "Oh, lo siento, Mayor, déjame invitarte a un buen whisky irlandés como una... ¡hic!... disculpa.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog2");
		break;
		
		case "drinking_at_fort_7_2":
			dialog.text = "Charles no se meterá en problemas, ¿verdad, Mayor? ¡Dime que no lo hará, por favorcito!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog4");
		break;
		
		case "drinking_at_fort_8":
			dialog.text = "¡Estoy tan contenta! ¡Vamos a beber!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToVillage");
		break;
		
		case "drinking_at_miskito":
			dialog.text = "¡Uf. Mira lo que tengo!";
			link.l1 = "Helena... ¿Estás planeando usar eso... para animarte?.. ¡Ni lo pienses! ¡La datura puede apoderarse por completo de una persona, drenar su fuerza, aplastar su voluntad! Antes de que te des cuenta, eres un cadáver viviente, y luego muy rápidamente, uno muerto...";
			link.l1.go = "drinking_at_miskito_1";
		break;
		
		case "drinking_at_miskito_1":
			dialog.text = "Charles, pero... ahora mismo...";
			link.l1 = "Sin peros. Lamento ser dura, pero esto no es una broma. Te lo estoy quitando. No puedo creer en qué estabas pensando... Aquí, bebe esto y reacciona.";
			link.l1.go = "drinking_at_miskito_2";
			
			GiveItem2Character(pchar, "cannabis7");
			PlaySound("interface\important_item.wav");
		break;
		
		case "drinking_at_miskito_2":
			dialog.text = "Lo siento, Charles. Tienes toda la razón, lo sé. Una debilidad momentánea. No volverá a suceder. Gracias por salvarme de la tentación del diablo...";
			link.l1 = "Olvidémonos de eso... Ahora, dime, ¿cómo lograste ganarte el respeto en el pueblo, mantener buenas relaciones con los oficiales de la guarnición y hacerte amigo de los nativos?";
			link.l1.go = "drinking_at_miskito_3";
		break;
		
		case "drinking_at_miskito_3":
			dialog.text = "Respetan a Svensson, y algo de eso se me transfiere a mí. Nuestro pequeño pueblo sobrevive únicamente gracias a los tratos de Jan. Comparte una parte de las ganancias de sus plantaciones de cacao con los casacas rojas, y los Miskito le deben toda su subsistencia.";
			link.l1 = "¿Cómo sucedió eso?";
			link.l1.go = "drinking_at_miskito_4";
		break;
		
		case "drinking_at_miskito_4":
			dialog.text = "Cuando los castellanos estaban al mando, no molestaban mucho a los indios. Pero después de que echaron a los nobles Hidalgos, nuestra gente decidió tomar el control de los bosques locales. Jan resolvió el asunto de manera bastante decisiva en ese entonces - ¡incluso envió gente a Londres! Por supuesto, no por bondad de su corazón: extraer cacao en un bosque donde cada arbusto te odia es una empresa desesperada. Pero ahora, los indios no solo ayudan a Jan a contrabandear de Porto Bello a Blueweld, sino que también talan sus propios bosques por una miseria. ¡Bravo, Diablo del Bosque, bravo!";
			link.l1 = "Suena como si no aprobaras del todo sus métodos.";
			link.l1.go = "drinking_at_miskito_5";
		break;
		
		case "drinking_at_miskito_5":
			dialog.text = "Amo y respeto al pueblo Miskito, pero también respeto la estrategia de Jan. No vivimos en un cuento de hadas, mi capitán.";
			link.l1 = "Hum... Veo que tu relación con Svensson es más complicada de lo que parece a primera vista...";
			link.l1.go = "drinking_at_miskito_6";
		break;
		
		case "drinking_at_miskito_6":
			dialog.text = "Incluso más de lo que usted sabe. Su esposa tiene una buena razón para ser venenosa conmigo... Jan me ha estado observando desde que tenía unos quince años. Fue más o menos cuando empecé a caminar por las cubiertas del Rainbow como un igual, y al parecer, algo hizo clic en la mente del Forest Devil en ese entonces... Pero he dicho demasiado, mi capitán. No ahondemos en este tema; cotillear sobre nuestro patrón no es muy decente.";
			link.l1 = "Entonces cambiemos de tema. Quise decir que claramente encajas en esta compañía, y te consideran uno de los suyos.";
			link.l1.go = "drinking_at_miskito_7";
		break;
		
		case "drinking_at_miskito_7":
			dialog.text = "Resulta que es mucho más fácil para mí estar en compañía de indios, gitanos y otros inadaptados decentes. Los guisos de mamá, las fogatas en la playa y la pasarela del Rainbow - me he construido un pequeño mundo acogedor, Capitán. Lástima que todo se vino abajo justo cuando pensé que lo tenía todo resuelto.";
			link.l1 = "El barril está casi vacío... ¿Una última ronda?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToShipyard");
		break;
		
		case "drinking_at_perlas":
			dialog.text = "Es tan bueno... Me alegra que hayas aceptado pasar tiempo conmigo, Capitán. Realmente lo necesitaba. Creo que tú también.";
			link.l1 = "Sí, ha pasado un buen rato desde que me relajé así. ¡Será algo para recordar!";
			link.l1.go = "drinking_at_perlas_1";
		break;
		
		case "drinking_at_perlas_1":
			dialog.text = "Probablemente piensas que el diablo sabe qué sobre mí en este momento. Soy una persona muy reservada por naturaleza, Charles. Yo solo... maldita sea, solo quería sentirme viva. ¡Solo quería hablar con alguien!";
			link.l1 = "¿Qué pasa con Gladys? ¿Jan?";
			link.l1.go = "drinking_at_perlas_2";
		break;
		
		case "drinking_at_perlas_2":
			dialog.text = "Todo lo que hace mamá es llorar, y Jan parece una persona diferente ahora. Tal vez estoy imaginando cosas, no lo sé, pero es como si ahora se avergonzara de mí. Perdóname, yo... (solloza).\nEso es suficiente, chica. Lo siento, me dejé llevar un poco.";
			link.l1 = " No hay necesidad de disculparse. Entiendo todo, o al menos creo que lo hago.";
			link.l1.go = "drinking_at_perlas_3";
		break;
		
		case "drinking_at_perlas_3":
			dialog.text = "Estoy diciendo todo esto porque apenas nos hemos conocido, y no estoy acostumbrada a ser tan abierta ni siquiera con aquellos que he conocido durante mucho tiempo. Me llaman Rumba, aparentemente por mi carácter, pero como puedes ver, es un nombre equivocado. ¿Ya se acabó el licor?";
			link.l1 = "Hace un rato, y ya está amaneciendo.";
			link.l1.go = "drinking_at_perlas_4";
		break;
		
		case "drinking_at_perlas_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend") && !CheckAttribute(pchar, "questTemp.HelenDrinking.RobbedSvenson")) {
				dialog.text = "Lo siento, mi capitán, si tenías otras expectativas para nuestra velada. Yo... No puedo. No hoy.";
			} else {
				dialog.text = "Entonces gracias por la velada, Capitán. Quién sabe, tal vez lo repitamos.";
			}
			link.l1 = "Por supuesto, Helen.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_PoormanTalk");
		break;
		
		case "ambush":
			dialog.text = "Gracias por traerme aquí, Capitán. Demos un vistazo alrededor, ¿de acuerdo? Examinar mi herencia.";
			link.l1 = "¿No has estado aquí antes?";
			link.l1.go = "ambush_1";
		break;
		
		case "ambush_1":
			dialog.text = "No, está bastante lejos; además, no soy pirata. Este lugar nunca ha sido particularmente fascinante, y después de que mataron a Blaise... Es mejor no quedarse aquí.";
			link.l1 = "No lo haremos. Ya me arrepiento de haberte traído aquí.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPrepareAmbush");
		break;
		
		case "after_ambush":
			switch (pchar.questTemp.HelenDrinking.IslaTesoroAmbush) {
				case "A":
					if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedB") && !CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedC")) {
						dialog.text = "¿Tenía que hacerlo, Capitán? ¿Por qué tanta prisa en pelear? Bueno, uno no debería limitarse a un solo ganador, supongo. Vamos, echemos un vistazo a la residencia; no hay nada más que valga la pena ver aquí de todos modos.";
						pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
						notification("Helen disapproves", "Helena");
					} else {
						dialog.text = "Enhorabuena, mi capitán, por intentar resolver el problema con sensatez antes de meterse en una pelea. Vamos, echemos un vistazo a la residencia; de todas formas no hay nada más que merezca la pena ver aquí.";
					}
					
					link.l1 = "¿Qué hay de ese enorme barco sacado a la orilla?";
					link.l1.go = "after_ambush_1";
				break;
				
				case "B":
					dialog.text = "¡Engañó hábilmente a esos tontos, mi capitán! Casi me parto de risa, ¡de verdad! Vamos, echemos un vistazo a la residencia; de todos modos no hay nada más que merezca la pena ver aquí.";
					pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
					notification("Helen approves", "Helena");
					
					link.l1 = "¿Qué hay de ese enorme barco varado en la orilla?";
					link.l1.go = "after_ambush_1";
				break;
				
				case "C":
					dialog.text = "¡Espera, deja que una chica recupere el aliento! ¿Eres realmente el tal Charlie Prince?";
					pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
					notification("Helen approves", "Helena");
					
					link.l1 = "Hubo un período así en mi biografía, sí. ¿Estás impresionado?";
					link.l1.go = "after_ambush_c";
				break;
			}
		break;
		
		case "after_ambush_1":
			dialog.text = "Sí, tienes razón. Me encantaría explorarlo, pero para ser honesta, Charles, me da un poco de miedo. Vamos.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroGoToResidence");
		break;
		
		case "after_ambush_c":
			dialog.text = "¡Dios mío, sí! Asegúrate de contarme todo más tarde, ¿de acuerdo? Porque solo he escuchado historias... historias muy indecentes!";
			link.l1 = "Te contaré todo... casi todo.";
			link.l1.go = "after_ambush_c_1";
		break;
		
		case "after_ambush_c_1":
			dialog.text = "¡Estaré esperando ansiosamente! Vamos, echemos un vistazo a la residencia; de todas formas no hay nada más que merezca la pena ver aquí.";
			link.l1 = "¿Qué pasa con ese enorme barco varado en la orilla?";
			link.l1.go = "after_ambush_1";
		break;
		
		case "ambush_inresidence":
			dialog.text = "¡Un tugurio estrecho y frío con demandas absurdas.  Ya me siento como si estuviera en una trampa!";
			link.l1 = "Veo que hasta ahora no estás satisfecho con la potencial propiedad?";
			link.l1.go = "ambush_inresidence_1";
		break;
		
		case "ambush_inresidence_1":
			dialog.text = "No, Charles. Quizás soy demasiado quisquillosa, pero por ahora, simboliza todo lo que temo y odio. Espero poder alquilarlo... Aunque, no estoy segura de dónde gastaré el dinero.";
			link.l1 = "No subestimes el valor del alquiler. Yo no tengo alquiler, y a menudo tengo que ingeniármelas para pagar a mi tripulación. Te comprarás un nuevo barco, 'Arcoíris II' - suena bien, ¿no crees?!";
			link.l1.go = "ambush_inresidence_sea";
			link.l2 = "Hay muchas maneras de gastar dinero en ti misma. Empieza con una espada personalizada y una botella de excelente vino. Date un gusto, Helen, te lo mereces.";
			link.l2.go = "ambush_inresidence_land";
		break;
		
		case "ambush_inresidence_sea":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Background") && pchar.questTemp.HelenDrinking.Background == "sea") {
				dialog.text = "Gracias, mi capitán. Me complace oír eso. Es especialmente agradable escucharlo por segunda vez. Me conoces bien.";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 3;
				notification("Helen approves", "Helena");
			} else {
				dialog.text = "Gracias, mi capitán. Me alegra oír eso.";
			}
			
			link.l1 = "";
			link.l1.go = "ambush_inresidence_2";
			
			sld = CharacterFromID("Helena");
			
			AddCharacterSkill(sld, SKILL_COMMERCE, 5);
			AddCharacterSkill(sld, SKILL_ACCURACY, 5);
			AddCharacterSkill(sld, SKILL_CANNONS, 5);
			AddCharacterSkill(sld, SKILL_SAILING, 5);
			AddCharacterSkill(sld, SKILL_REPAIR, 5);
			AddCharacterSkill(sld, SKILL_GRAPPLING, 5);
			AddCharacterSkill(sld, SKILL_DEFENCE, 5);
		break;
		
		case "ambush_inresidence_land":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Background") && pchar.questTemp.HelenDrinking.Background == "land") {
				dialog.text = "¿Crees que lo merezco? Nunca he gastado dinero en tales bagatelas, pero supongo que siempre hay una primera vez para todo. Veo que no dejarás de intentar hacerme olvidar del mar, ¿eh, Capitán? Quizás tengas razón...";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 3;
				notification("Helen disapproves", "Helena");
			} else {
				dialog.text = "¿Crees que lo merezco? Nunca he gastado dinero en tales nimiedades, pero supongo que siempre hay una primera vez para todo.";
			}
			link.l1 = "";
			link.l1.go = "ambush_inresidence_2";
			
			sld = CharacterFromID("Helena");
			
			AddCharacterSkill(sld, SKILL_F_LIGHT, 5);
			AddCharacterSkill(sld, SKILL_FENCING, 5);
			AddCharacterSkill(sld, SKILL_F_HEAVY, 5);
			AddCharacterSkill(sld, SKILL_PISTOL, 5);
			AddCharacterSkill(sld, SKILL_FORTUNE, 5);
			AddCharacterSkill(sld, SKILL_LEADERSHIP, 5);
			AddCharacterSkill(sld, SKILL_SNEAK, 5);
		break;
		
		case "ambush_inresidence_2":
			dialog.text = "En cualquier caso, la inspección está completa. No parece haber objetos de valor aquí - la chusma ya ha conseguido saquearlo todo, y estoy segura de que el segundo piso está en las mismas condiciones.";
			link.l1 = "Es como si hubieras cambiado, Helen. La última vez que pasamos el rato, estabas... no sé, ¿más abierta?";
			link.l1.go = "ambush_inresidence_3";
		break;
		
		case "ambush_inresidence_3":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6) {
				dialog.text = "Nada ha cambiado, mi capitán, pero mucho ha caído sobre los hombros de una pobre chica, ¡jaja! No quise ofenderte. Solo necesito pensar en muchas cosas ahora mismo. Sabes, giros tan bruscos en la vida no ocurren todos los días. ¡Y todavía tenemos mucho tiempo juntos!";
				link.l1 = "¡Me alegra oír eso! Salgamos de aquí.";
			} else {
				dialog.text = "Mucho ha cambiado, Capitán. Me temo que ahora tengo que ser más maduro y ver la vida de otra manera. No es un cuento de hadas sobre una princesa y una herencia; es la gran política, y aún tengo que darme cuenta de mi lugar en ella. Y el lugar de mi familia también.";
				link.l1 = "Me alegra que hayamos aclarado eso. Vámonos de aquí.";
			}
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroBeforeExit");
		break;
		
		case "ambush_inresidence_wait":
			dialog.text = "¿Sí?";
			if (CheckCharacterItem(pchar, "pirate_cutlass")) {
				link.l1 = "¡Oye, no todo ha sido saqueado! ¡Mira, Helen! Este sable parece ser legendario, dado que incluso la chusma local dudó en llevárselo.";
				link.l1.go = "ambush_inresidence_give_cutlass";
			}
			
			link.l2 = "No,   nada.";
			link.l2.go = "exit";
			
			NextDiag.TempNode = "ambush_inresidence_wait";
		break;
		
		case "ambush_inresidence_give_cutlass":
			dialog.text = "¡Vaya, esto es... la legendaria alfanje del propio Blaise! Los piratas lo respetaban demasiado como para llevarse el sable de su hogar incluso después de su muerte. Se llevaron el dinero y los objetos de valor, por supuesto, pero incluso los futuros pájaros de la horca tienen restos de honor...";
			link.l1 = "Parece que alguien está claramente poniendo orden aquí. Como si el dueño fuera a volver... ¡Esto no es un hogar, es un monumento!";
			link.l1.go = "ambush_inresidence_give_cutlass_1";
		break;
		
		case "ambush_inresidence_give_cutlass_1":
			dialog.text = "Gracias por la aguda observación, Charles. Has arruinado por completo este lugar a mis ojos, ¡ja-ja!";
			link.l1 = "Creo que este sable es ahora tuyo. Blaise es tu supuesto tío...";
			link.l1.go = "ambush_inresidence_give_cutlass_2";
		break;
		
		case "ambush_inresidence_give_cutlass_2":
			dialog.text = "Estás añadiendo aún más horror a esto, mi capitán. Yo... no puedo. Temo que si lo acepto, mi vida pasada llegará a un final completo.";
			link.l1 = "Entonces no lo tomes como parte de la herencia, sino como un regalo de un hombre apuesto.";
			link.l1.go = "ambush_inresidence_give_cutlass_3";
		break;
		
		case "ambush_inresidence_give_cutlass_3":
			dialog.text = "¿Quién podría ser? ¡Es broma! Gracias por disipar mis pensamientos oscuros, mi capitán. ¡Prometo que entrenaré mucho para ser digna de esta espada!";
			link.l1 = "Eres digno del arma más fina, Helen. Vámonos, hemos terminado aquí.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GiveCutlass");
		break;
		
		case "give_cutlass":
			dialog.text = "¡Vaya, esto es... la legendaria espada de Blaise mismo! Los piratas lo respetaban tanto que ni siquiera después de su muerte se atrevieron a tomar el sable de su hogar. Se llevaron el dinero y las cosas de valor, por supuesto, pero incluso esos futuros ahorcados tienen restos de honor.  Yo... no puedo. Temo que si lo acepto, mi vida pasada llegará a su fin completo.";
			link.l1 = "Entonces no lo tomes como parte de la herencia, sino como un regalo de un hombre apuesto.";
			link.l1.go = "give_cutlass_1";
		break;
		
		case "give_cutlass_1":
			dialog.text = "¿Quién podría ser? ¡Es broma! Gracias por disipar mis pensamientos oscuros, mi capitán.";
			link.l1 = "Eres digno del arma más fina, Helen. Me alegra que te guste.";
			link.l1.go = "give_cutlass_2";
		break;
		
		case "give_cutlass_2":
			dialog.text = "¡Prometo entrenar mucho para ser digno de esta espada!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GiveCutlass");
		break;
		
		case "arrive":
			dialog.text = "¡Mi capitán! ¡Charlie!";
			link.l1 = "¿Charlie? ¡Eso es nuevo! Me alegra verte, querido.";
			link.l1.go = "arrive_1";
		break;

		case "arrive_1":
			dialog.text = "¡Me he resbalado accidentalmente, ja! Me alegra verte también...";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog1");
		break;

		case "arrive_2":
			dialog.text = "¡Así que tanto por la solidaridad entre hermanas! Mi capitán, yo... realmente estaba muy preocupada y te extrañé mucho.";
			link.l1 = "¿Y por qué tuviste que correr a casa?";
			link.l1.go = "arrive_3";
		break;

		case "arrive_3":
			dialog.text = "Para... ¡Oh, cierto! Tengo un pequeño regalo para ti, ¡aquí!";
			link.l1 = "Tres amuletos... Helen, ¿por qué? ¿Querías seguirme?";
			link.l1.go = "arrive_4";
			
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Indian);
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Amulet);
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Obereg);
		break;

		case "arrive_4":
			dialog.text = "¡Ven aquí, tonto!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FirstKiss");
		break;

		case "after_kiss":
			dialog.text = "¡No te atrevas a arruinar este momento - lo he imaginado toda mi vida!";
			link.l1 = "No lo haré, Helen.";
			link.l1.go = "after_kiss_a";
			link.l2 = "¿Has estado esperando toda tu vida para conocerme? ¡Halagado!";
			link.l2.go = "after_kiss_b";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l3 = "Helena, hay algo... En la Isla de la Justicia, conocí a una mujer, y...";
				link.l3.go = "after_kiss_c";
			}
			locCameraFromToPos(-19.00, 1.56, 19.07, true, -11.19, -0.90, 17.49);
		break;
		
		case "after_kiss_a":
			dialog.text = "¡Maldita sea, tienes razón! ¡Me lo contarás todo, todo! Te estaré esperando en el barco, mi capitán!";
			link.l1 = "¡Espera!...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "after_kiss_b":
			dialog.text = "¡Necio! ¿Quieres ofenderme? ¡Está bien, me has ofendido! ¡Ja-ja! Iré al barco por ahora, antes de que Danny se burle más de mí...";
			link.l1 = "¡Espera!...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "after_kiss_c":
			dialog.text = "¡Necio! ¡Te pedí que no arruinaras el momento! Conociste... bien, conociste, pero aún no veo un anillo en tu dedo. Pero no pienses que te saldrás con la tuya, estaré esperando una historia detallada cuando regreses al barco.";
			link.l1 = "¡Espera!...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "loot_good":
			dialog.text = "Mi capitán, ¿cuáles son las novedades? Puedo ver por tu cara pálida que el abogado decidió lanzarte más problemas en lugar de ayudar.";
			link.l1 = "Tienes razón, Helen. Loxley exigió un adelanto impresionante, y el caso en sí me costará una suma considerable. Voy a sacudir a Jan - ¡ya me harté! ¡Es como si los Hermanos decidieran pasarme todos sus gastos a mí!";
			link.l1.go = "loot_good_1";
		break;
		
		case "loot_good_1":
			dialog.text = "No hay malicia en ello, Charles. Así son ellos - no moverán un dedo a menos que tengan que hacerlo. Estoy segura de que Jan te ayudará, y yo tampoco me quedaré de brazos cruzados.";
			link.l1 = "Lo sé, Helen. Dime qué tienes en mente.";
			link.l1.go = "loot_good_2";
		break;
		
		case "loot_good_2":
			dialog.text = "Solía trabajar para Jan, contrabandeando madera valiosa por todo Maine. Pero soy una chica ingeniosa, y he apartado algo para mí durante todos esos viajes.";
			link.l1 = "¿Y Jan no se enteró? ¡Astuto!";
			link.l1.go = "loot_good_3";
		break;
		
		case "loot_good_3":
			dialog.text = "Tenía un buen tesorero. En resumen, he reunido una cantidad decente de dinero, y lo he escondido no muy lejos de aquí. ¿Vas a ver a Jan ahora? Entonces visitemos San Juan del Norte. Hay una cueva cerca, y solo necesitaremos algunos marineros para ayudarnos, así no tendremos que cargar todo nosotros mismos.";
			link.l1 = "Ya lo has resuelto todo, ¿verdad? Gracias, Helen, definitivamente te visitaremos si tenemos tiempo.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_CreateLoot");
		break;
		
		case "loot_bad":
			dialog.text = "Mi capitán, ¿qué noticias hay? Puedo decir por tu rostro pálido que el abogado decidió lanzarte más problemas en lugar de ayudarte.";
			link.l1 = "Tienes razón, Helen. Loxley exigió un adelanto impresionante, y el caso en sí me costará una suma considerable. Voy a sacudir a Jan - ¡ya es suficiente! ¡Es como si la Hermandad decidiera pasarme todos sus gastos a mí!";
			link.l1.go = "loot_bad_1";
		break;
		
		case "loot_bad_1":
			dialog.text = "¿Pensaste que estabas en un cuento de hadas? No te preocupes, todos estamos en el mismo barco aquí, y te echaré una mano. Al fin y al cabo, tengo derecho a una herencia, ¿no es así?";
			link.l1 = "Es cierto... ¡Dime, ¿qué pasa por tu mente!";
			link.l1.go = "loot_bad_2";
		break;
		
		case "loot_bad_2":
			dialog.text = "Tengo algo escondido en San Juan del Norte. Hay una cueva cerca - solo necesitamos reclutar a algunos marineros para no tener que cargar todo nosotros mismos.";
			link.l1 = "Ya lo has resuelto todo, ¿verdad? Gracias, Helen, definitivamente visitaremos si tenemos tiempo.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_CreateLoot");
		break;
		
		case "shdn":
			dialog.text = "¡Esto es todo, Charles! Pero tendrás que ir solo - ¡odio las cuevas!";
			link.l1 = "Como cualquier espacio cerrado, lo sé, Helen. Espérame aquí.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoForLoot");
		break;
		
		case "shdn_ambush":
			dialog.text = "¡Tenemos un problema! Un escuadrón de soldados viene en esta dirección, y parecen amenazantes. Ten cuidado, Charles, no son solo guardias costeros ordinarios - ¡hay un oficial francés entre ellos! Te ruego, no hagas nada imprudente.";
			link.l1 = "¿Cuándo he hecho yo algo tonto?!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SpawnAmbushSoldiers");
		break;
		
		case "shdn_ambush_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6) {
				dialog.text = "Ja, la segunda opción suena más tentadora, pero espero que no estés demasiado orgulloso de ti mismo, ¿Charles?";
			} else {
				dialog.text = "No puedo decir que me sorprende, Charles...";
			}
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog1");
		break;
		
		case "shdn_ambush_2":
			dialog.text = "¿Has terminado? ¡Ahora es mi turno de hablar!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_HelenKillFrancois");
		break;
		
		case "shdn_ambush_3":
			dialog.text = "¡Mi nombre es Helen MacArthur! ¡Capitán, usted sabe quién soy y para quién trabajo! ¡Informe a su gente, especialmente a este idiota engreído tirado en el suelo, sobre los resultados de hoy, que ahora anunciaré!";
			link.l1 = "";
			link.l1.go = "exit";
			CharacterTurnToLoc(npchar, "quest", "richard");
			sld = CharacterFromID("HelenDrinking_Richard");
			CharacterTurnByChr(sld, npchar);
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath2");
		break;
		
		case "shdn_ambush_4":
			dialog.text = "¿Protestar? No me importa si escribes al mismo Cromwell. Primero, el señor de Maure no perdió su honor hoy.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_5";
			CharacterTurnToLoc(npchar, "quest", "richard");
		break;
		
		case "shdn_ambush_5":
			dialog.text = "Segundo, al coronel de Tavann le disparó una chica con un atuendo muy picante por llamarla prostituta.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_6";
		break;
		
		case "shdn_ambush_6":
			dialog.text = "Tercero, retiras inmediatamente a tus soldados y olvidas lo que sucedió a menos que quieras que el Diablo del Bosque se entere.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_7";
		break;
		
		case "shdn_ambush_7":
			locCameraSleep(false);
			dialog.text = "Sin preguntas, veo. Que tenga un buen día, Capitán.";
			link.l1 = "¡Dios mío, Helen, estás en llamas!";
			link.l1.go = "shdn_ambush_8";
		break;
		
		case "shdn_ambush_8":
			dialog.text = "Más tarde, Charles. Salgamos de aquí antes de que se recuperen del susto. Yo también estoy temblando por completo. ¿Podemos hablar en Blueweld?";
			link.l1 = "De acuerdo.";
			link.l1.go = "exit";
			CharacterTurnByChr(npchar, pchar);
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath3");
		break;
		
		case "duel_victory":
			dialog.text = "Salgamos de aquí antes de que se recuperen del shock. Todavía necesitamos recuperar la madera de hierro, ¿recuerdas? Podemos hablar en Blueweld.";
			link.l1 = "¡Vaya! ¿Ni siquiera una felicitación? Bien, vamos.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_DuelVictory1");
		break;
		
		case "after_cave":
			dialog.text = "Finalmente, en casa...";
			link.l1 = "¿Qué piensas sobre lo que sucedió?";
			link.l1.go = "after_cave_1";
		break;
		
		case "after_cave_1":
			dialog.text = " No entiendo los duelos. Un pasatiempo de hombres, que generalmente termina con dos cadáveres, y en un día afortunado, incluso más. Y el honor... Creo que el honor se construye sobre el deseo de evitar el conflicto hasta el final, ya que rara vez resulta ser digno. ¡Ja! Solo escúchame, ¡estoy diciendo tonterías!";
			link.l1 = "Esa es una perspectiva interesante, Helen. Aunque no todos estarían de acuerdo con ella.";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Duel")) {
				link.l1.go = "after_cave_duel";
			} else {
				link.l1.go = "after_cave_notduel";
			}
		break;
		
		case "after_cave_duel":
			dialog.text = "Es una lástima que hayas caído en su trampa. El coronel estaba claramente obsesionado, y los demás solo buscaban espectáculo y material para chismes. Bueno, no te lo restregaré - ya has tenido bastante por hoy.";
			link.l1 = "Sí, después de los duelos, siempre hay una sensación de vacío. Suficientes aventuras por hoy. ¿Qué quieres hacer después?";
			if (sti(pchar.questTemp.Saga.HelenRelation) == 7 || sti(pchar.questTemp.Saga.HelenRelation) == 8) {
				link.l1.go = "after_cave_mild";
			} else {
				if (sti(pchar.questTemp.Saga.HelenRelation) < 7) {
					link.l1.go = "after_cave_cold";
				} else {
					link.l1.go = "after_cave_lewd";
				}
			}
		break;
		
		case "after_cave_notduel":
			dialog.text = "¡Uf! Solo quería decir que estoy orgullosa de nosotros. Mostraste verdadero coraje hoy, mi capitán. No sucumbiste a la histeria de la tripulación que solo quería mandarte por una vez. Te mantuviste firme contra la pretensión del uniforme rojo y la obsesión del azul. El coronel claramente buscaba la muerte, pero no obtuvo más que una herida en un lugar inapropiado, ¡ja-ja!";
			link.l1 = "Gracias, Helen. Nos alejaste del golpe con maestría, como un verdadero oficial naval. ¿Estás orgullosa de ti misma?";
			link.l1.go = "after_cave_notduel_1";
		break;
		
		case "after_cave_notduel_1":
			dialog.text = "Sí, lo necesitaba. Es una pena que fuera un uniforme azul y no uno rojo, pero al menos la persona que lo llevaba recibió lo que merecía.";
			link.l1 = "Esa persona es realmente insignificante, lo admito. Suficientes aventuras por hoy. ¿Qué quieres hacer ahora?";
			if (sti(pchar.questTemp.Saga.HelenRelation) == 7 || sti(pchar.questTemp.Saga.HelenRelation) == 8) {
				link.l1.go = "after_cave_mild";
			} else {
				if (sti(pchar.questTemp.Saga.HelenRelation) < 7) {
					link.l1.go = "after_cave_cold";
				} else {
					link.l1.go = "after_cave_lewd";
				}
			}
		break;
		
		case "after_cave_mild":
			dialog.text = "Estoy regresando a casa, mi capitán. Extrañaba a mi ma... Gladys. ¡Lástima que está en casa ahora, de lo contrario, te habría invitado!";
			link.l1 = "¡De veras, qué lástima!";
			link.l1.go = "after_cave_mild_1";
		break;
		
		case "after_cave_mild_1":
			dialog.text = "No te pongas tan molesto. Pronto, mi querido. Mientras tanto...";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SecondKiss");
		break;
		
		case "after_second_kiss":
			locCameraFromToPos(4.97, 3.71, 16.06, true, 5.09, 1.25, 11.67);
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Kiss")) {
				dialog.text = "M-m-m, este es incluso mejor que el primero. ¿Recuerdas? ¿Por el ídolo?";
				link.l1 = "Eso no es algo que uno olvide, querido.";
				link.l1.go = "after_second_kiss_1";
			} else {
				dialog.text = "¡Ni se te ocurra arruinar este momento, lo he estado imaginando toda mi vida!";
				link.l1 = "No lo haré, Helen.";
				link.l1.go = "after_second_kiss_a";
				link.l2 = "¿Has estado esperando toda tu vida para conocerme? ¡Halagado!";
				link.l2.go = "after_second_kiss_b";
			}
		break;
		
		case "after_second_kiss_1":
			dialog.text = "¡Ohh! ¡Contrólate, chica! Hasta que nos volvamos a encontrar, mi capitán.";
			link.l1 = "Hasta entonces, Helen.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_second_kiss_a":
			dialog.text = "¡Maldita sea, tienes razón! Nos veremos pronto, mi capitán.";
			link.l1 = "Hasta que nos volvamos a encontrar, Helen. Oh Dios, qué chica...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_second_kiss_b":
			dialog.text = "¡Necio! ¿Quieres ofenderme? ¡Está bien, estoy ofendida! ¡Ja-ja! Nos veremos pronto, mi capitán.";
			link.l1 = "Hasta que nos volvamos a encontrar, Helen. Oh Dios, qué chica...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_cave_cold":
			dialog.text = "Me dirijo a casa, capitán. ¿Supongo que el asunto del dinero con el abogado ya está resuelto? Tenemos obstáculos difíciles por delante, así que intentemos mantenernos alejados de los problemas de ahora en adelante. Los problemas nos encontrarán por sí mismos.";
			link.l1 = "¿En serio?";
			link.l1.go = "after_cave_cold_1";
		break;
		
		case "after_cave_cold_1":
			dialog.text = "Perdón por ser directa, Capitán. Mi destino también se está decidiendo ahora, ¿sabes?";
			link.l1 = "Lo sé, intentaré manejarlo con la mayor dignidad posible. Nos vemos en el barco, Helen.";
			link.l1.go = "after_cave_cold_2";
		break;
		
		case "after_cave_cold_2":
			dialog.text = "¡Aye aye, Cap!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveCold");
		break;
		
		case "after_cave_lewd":
			dialog.text = "¿Qué sigue? Te lo mostraré.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SecondKiss");
		break;
		
		case "after_second_kiss1":
			locCameraFromToPos(4.97, 3.71, 16.06, true, 5.09, 1.25, 11.67);
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Kiss")) {
				dialog.text = "M-m-m, este es incluso mejor que el primero. ¿Recuerdas? ¿Junto al ídolo?";
				link.l1 = "Eso no es algo que se olvide, querido.";
				link.l1.go = "after_second_kiss1_1";
			} else {
				dialog.text = "¡Ni se te ocurra arruinar este momento, lo he estado imaginando toda mi vida!";
				link.l1 = "No lo haré, Helen.";
				link.l1.go = "after_second_kiss1_a";
				link.l2 = "¿Has estado esperando toda tu vida para conocerme? ¡Halagado!";
				link.l2.go = "after_second_kiss1_b";
			}
		break;
		
		case "after_second_kiss1_1":
			dialog.text = "¡Maldita sea! ¡Vaya! Gladys no está en casa ahora. ¿Quieres entrar?";
			link.l1 = "¿Invitándome a pasar? ¿Y qué estaremos haciendo?";
			link.l1.go = "after_cave_lewd_accept";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l2 = "No, Helen. Otra mujer me espera en la Isla de la Justicia. No puedo hacerle eso a ella.";
				link.l2.go = "after_cave_lewd_refuse_mary";
			}
			link.l3 = "Otra vez, mi querido. Realmente lo deseo, pero hoy casi me agoté. Nos pondremos al día y compensaremos el tiempo perdido diez veces.";
			link.l3.go = "after_cave_lewd_refuse_head";
		break;
		
		case "after_second_kiss1_a":
			dialog.text = "¡Maldita sea, es cierto! ¡Vaya! Gladys no está en casa ahora. ¿Quieres entrar?";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l1 = "No, Helen. Otra mujer me espera en la Isla de la Justicia. No puedo hacerle eso a ella.";
				link.l1.go = "after_cave_lewd_refuse_mary";
			}
			link.l2 = "Otro momento, mi querido. Realmente lo deseo, pero hoy casi me mata. Nos pondremos al día y compensaremos el tiempo perdido diez veces.";
			link.l2.go = "after_cave_lewd_refuse_head";
			link.l3 = "¿Invitándome a pasar? ¿Y qué haremos?";
			link.l3.go = "after_cave_lewd_accept";
		break;
		
		case "after_second_kiss1_b":
			dialog.text = "¡Tonto! ¿Quieres ofenderme? ¡Está bien, estoy ofendida! ¡Ja, ja! Vas a tener que compensarlo, mi capitán. ¡Vaya! Gladys no está en casa ahora. ¿Quieres entrar?";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l1 = "No, Helen. Otra mujer me espera en la Isla de la Justicia. No puedo hacerle eso a ella.";
				link.l1.go = "after_cave_lewd_refuse_mary";
			}
			link.l2 = "En otra ocasión, mi querido. Realmente lo deseo, pero hoy casi me acaba. Nos pondremos al día y compensaremos el tiempo perdido diez veces más.";
			link.l2.go = "after_cave_lewd_refuse_head";
			link.l3 = "¿Invitándome a pasar? ¿Y qué haremos?";
			link.l3.go = "after_cave_lewd_accept";
		break;
		
		case "after_cave_lewd_refuse_mary":
			dialog.text = "¿Ah, entonces no soy lo suficientemente hábil en el arte de la seducción? ¿Y ella sí lo es? ¿Quién es ella?";
			link.l1 = "Su nombre es Mary Casper, y la amo.";
			link.l1.go = "after_cave_lewd_refuse_mary_1";
		break;
		
		case "after_cave_lewd_refuse_mary_1":
			dialog.text = "Esa pelirroja con el uniforme rojo? En el uniforme rojo... Bueno, si necesitaba una señal, aquí está. No está destinado a ser. Y no te preocupes, capitán, eso no afectará mi servicio en tu barco.";
			link.l1 = "Lo siento, Helen.";
			link.l1.go = "exit";
			
			pchar.questTemp.HelenDrinking.Mary = true;
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveRefuseMary");
		break;
		
		case "after_cave_lewd_refuse_head":
			dialog.text = "¡Oh, mi capitán! ¡Es peligroso dejar a una mujer en tal estado! Te tomo la palabra, y ahora corre... Necesito estar sola ahora y tratar de lidiar con mi problema... ¡por mi cuenta! ¡Nos vemos en el barco!";
			link.l1 = "¡Qué chica!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveRefuseMild");
		break;
		
		case "after_cave_lewd_accept":
			dialog.text = "No te preocupes, querida, te guiaré si te pierdes.";
			link.l1 = "Bueno entonces... ¡adelante!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveAccept");
		break;
		
		case "after_cave_bedroom":
			dialog.text = "No digas nada, te lo ruego.";
			link.l1 = "...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveSex1");
		break;
		
		case "after_cave_sex":
			dialog.text = "... por supuesto, hasta hoy, mi comprensión de este tema se basaba únicamente en las conversaciones vulgares de la tripulación del 'Arcoíris', si es que se les puede llamar conversaciones, por supuesto.";
			link.l1 = "¿Y cómo fue? ¿La realidad cumplió con tus expectativas?";
			link.l1.go = "after_cave_sex_1";
		break;
		
		case "after_cave_sex_1":
			dialog.text = "Lo disfruté mucho, pero siento que no lo he experimentado completamente. Y cómo...";
			link.l1 = "¡Déjame mostrarte! ¿Continuamos?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveSex2");
		break;
		
		case "after_cave_sex_again":
			dialog.text = "¡Oh, ahora entiendo! Fue simplemente maravilloso, mi capitán!";
			link.l1 = "¡Me sorprendiste, por decir lo menos!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveGladysEnter");
		break;
		
		case "after_cave_gladys":
			dialog.text = "¡Ja-ja-ja! ¡Esa es buena, seguro! Ahora o se tapará los oídos con cera o correrá a la plataforma más alta del fuerte!";
			link.l1 = "¡Eso fue inesperado pero muy divertido, ah-ja-ja!";
			link.l1.go = "after_cave_gladys_1";
			locCameraFromToPos(-0.62, 1.93, -0.39, true, -2.46, -1.20, 1.01);	// Sinistra - постельная камера
		break;
		
		case "after_cave_gladys_1":
			dialog.text = "¿Listo, mi capitán?";
			link.l1 = "¿Ya?! No, Helen, ten piedad de mí, por favor. La aparición repentina de Gladys definitivamente no ayudó al ambiente.";
			link.l1.go = "after_cave_gladys_2";
		break;
		
		case "after_cave_gladys_2":
			dialog.text = "Bueno, qué se le va a hacer... Aunque...";
			link.l1 = "¡No, no, baja las velas!";
			link.l1.go = "after_cave_gladys_3";
		break;
		
		case "after_cave_gladys_3":
			dialog.text = "De acuerdo, entonces quedémonos juntos un rato. Nuestro futuro es tan turbio y aterrador, pero por primera vez en mucho tiempo, no tengo miedo de nada más. Sé que algún nuevo temor se colará, pero no hoy. No hoy, mi capitán.";
			link.l1 = "No hoy, mi querido. No hoy.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveFin");
		break;
		
		case "give_potions":
			dialog.text = "¿Permiso para hablar, Capitán?";
			link.l1 = "¿Sí, Helen?";
			link.l1.go = "give_potions_1";
		break;
		
		case "give_potions_1":
			dialog.text = "Conozco a este Ojo de Serpiente - es un buen hombre, pero un poco raro. Regularmente envía a las personas en misiones por sabe Dios qué. Veo que tú también has recibido ese dudoso honor.";
			if (!CheckAttribute(CharacterFromID("SnakeEye"), "quest.amulet")) {
				link.l1 = "Así es, necesito llevarle tres amuletos, o de lo contrario no podrá ayudarme a llegar al lugar de Hawk. ¿Pero sabes qué es lo gracioso? ¡Ya los tenía conmigo! ¿Quizás él lo sabía desde el principio?";
				link.l1.go = "give_potions_already";
			} else {
				link.l1 = "Así es, necesito llevarle tres amuletos, o de lo contrario no podrá ayudarme a llegar al lugar de Hawk. No puedo averiguar dónde encontrarlos ahora, y el tiempo se está acabando.";
				link.l1.go = "give_potions_3";
			}
		break;
		
		case "give_potions_already":
			dialog.text = "¡Oh, qué pena! Me alegra que no hayas tenido que correr por ahí consiguiendo esos amuletos de los fareros, pero esperaba que por una vez pudiera serte útil, esperaba demostrar mi valía.";
			link.l1 = "Tonterías, Helen. No necesitas demostrarme nada.";
			link.l1.go = "give_potions_4";
		break;
		
		case "give_potions_3":
			dialog.text = "¡Te ayudaré! Admito que esperaba que, por una vez, pudiera serte útil, esperaba demostrar mi valía.";
			link.l1 = "Tonterías, Helen. No necesitas probarme nada.";
			link.l1.go = "give_potions_4";
		break;
		
		case "give_potions_4":
			dialog.text = "Sin embargo, quiero ayudarte. Aquí, toma la llave de mi habitación... Quiero decir, ¡del cofre en mi habitación! No hay mucho, pero para ti será útil. Y... Charles, solo intenta no reírte a carcajadas ahora mismo.";
			link.l1 = "Eh, no iba a hacerlo. ¿Veo que te interesan estas cosas?";
			link.l1.go = "give_potions_5";
		break;
		
		case "give_potions_5":
			dialog.text = "Soy una marinera, mi capitán, igual que tú. En nuestro negocio, debemos hacer todo lo posible para que la Dama Fortuna esté de nuestro lado.";
			link.l1 = "Gracias, Helen. Realmente lo aprecio.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GivePotionsKey");
		break;
		
		case "upgrade":
			dialog.text = "¡Querido, tengo un regalo para ti!";
			link.l1 = "Veo, allí está - de pie y sonriendo!";
			link.l1.go = "upgrade_1";
		break;
		
		case "upgrade_1":
			dialog.text = "¡Ah-ja, basta! Una vez entregué un buen lote de seda al constructor naval local, así que ahora me debe una revisión completa del barco. Pensé en darle el 'Arcoíris' para este trabajo, pero no estaba destinado a ser. Tu embarcación, por otro lado, podría realmente beneficiarse de tal cuidado, ¿no crees?";
			link.l1 = "¡En verdad, un regalo espléndido, Helen, justo en tu callejón!";
			link.l1.go = "upgrade_2";
		break;
		
		case "upgrade_2":
			dialog.text = "Me alegra que te guste. Visítalo en cualquier momento y dile que te envié yo. Ellos harán su mejor trabajo.";
			link.l1 = "¡Definitivamente!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
			AddDialogExitQuestFunction("HelenUpgradeShip1");
		break;
		
		case "give_sex":
			dialog.text = "¿Permiso para hablar, mi capitán?";
			link.l1 = "Por supuesto, mi querido.";
			link.l1.go = "give_sex_1";
		break;
		
		case "give_sex_1":
			dialog.text = LinkRandPhrase("Tu dama te echa de menos y exige atención. ¿Puedo pedir que le prepares una habitación y le dediques algo de tiempo?","Informe: se requiere su presencia en una cama en la taberna local. Solo cinco minutos de su tiempo, pero la tripulación espera que se quede más tiempo.","¡Motín en el barco, mi capitán! Me han encomendado entregarte una marca negra en privado. ¡Ven conmigo de inmediato!");
			link.l1 = "¡Je-je, ejem! ¡Tu solicitud ha sido concedida, Oficial Sharp!";
			link.l1.go = "give_sex_1_yes";
			link.l2 = "No hoy, querido. Demasiado está sucediendo ahora mismo.";
			link.l2.go = "give_sex_1_no";
		break;
		
		case "give_sex_1_yes":
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			DialogExit();
			AddDialogExitQuestFunction("Helen_GiveSexGoToTavern");
		break;
		
		case "give_sex_1_no":
			dialog.text = "¿Oh, y qué harías que haga una pobre chica, eh? Está bien, mi querido, en otra ocasión entonces.";
			link.l1 = "";
			link.l1.go = "give_sex_2_no";
		break;
		
		case "give_sex_2_no":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			npchar.location = "None";
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			chrDisableReloadToLocation = false;
			
			pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
			pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
			pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
			pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
		break;
		
		case "special_sex":
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			SaveCurrentNpcQuestDateParam(npchar, "special_sex_date");
			
			dialog.text = "¡Ja! ¡No tienes que pedírmelo dos veces! ¡Por supuesto, vamos!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Helen_GiveSexGoToTavern");
		break;
		
		case "rainbow":
			dialog.text = "¡Te arrojaré por la borda ahora mismo!";
			link.l1 = "¡Eh, eh, eh! ¡Cálmate, querida!";
			link.l1.go = "rainbow_1";
		break;
		
		case "rainbow_1":
			dialog.text = "¡Ven aquí, bribón!";
			link.l1 = "¡Solo bromeaba, Helen! ¡No quise ofenderte!";
			link.l1.go = "rainbow_2";
		break;
		
		case "rainbow_2":
			dialog.text = "¿De verdad? Chúpate esa, bromista...";
			link.l1 = "¡Eres la más hermosa, y te amo locamente!";
			link.l1.go = "rainbow_3";
		break;
		
		case "rainbow_3":
			dialog.text = "Piérdete, Charles.";
			link.l1 = "";
			link.l1.go = "exit";
			
			DeleteAttribute(pchar, "questTemp.HelenDrinking.Rainbow");
			Achievment_Set("ach_CL_84");
		break;
		
		case "joan":
			dialog.text = "¡La descarada eres tú! Agradece que Jan te hizo una mujer honesta, o todavía estarías abriendo las piernas para cada transeúnte.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog2");
		break;
		
		case "joan_1":
			dialog.text = "¡Ramera! ¡Vamos, Charles!";
			link.l1 = "";
			link.l1.go = "exit";
			
			ResetSound();
			SetMusic("helendrinking_shanty");
			pchar.questTemp.lockedMusic = true;
			AddDialogExitQuestFunction("HelenDrinking_GoToFort");
		break;
		
		case "cutlass_training":
			dialog.text = "¡El alfanje encaja perfectamente en mi mano! No sé cómo explicarlo... Siempre tuve problemas con otros tipos de armas blancas, como estoques y espadas. ¡Pero este alfanje es otra historia! ¡Se siente increíble! ¡Gracias, Charles!";
			link.l1 = "El destino tiene una manera de encontrarnos. ¡Me alegro por ti, Helen!";
			link.l1.go = "exit";
			notification("Medium Weapons +", "Helena");
		break;
		
		case "brothel_found":
			dialog.text = "Guarda tus historias para otro, no funcionarán conmigo. ¿Acaso parezco una ingenua tonta enamorada? Quiero decir, ESTOY locamente enamorada de ti, pero llamarme tonta sería exagerado\n Escucha, querido, haz lo que desees, pero ten en cuenta que no encontrarás una mujer mejor que yo. Si quieres buscarla en burdeles, adelante, pero entonces desapareceré de tu vida para siempre.";
			link.l1 = "Helen, yo...";
			link.l1.go = "brothel_found_1";
		break;
		
		case "brothel_found_1":
			dialog.text = "Entiendo todo, Charles. Tú solo me amas a mí, y estos son solo impulsos naturales. ¿Sabes cuál es mi impulso natural? El respeto de mi hombre. Una mujer puede no estar satisfecha solo con amor, querido. Olvidemos este malentendido por ahora, pero reflexiona un poco sobre mis palabras. ¿De acuerdo?";
			link.l1 = "Está bien, Helen.";
			link.l1.go = "exit";
		break;
		
		case "refuse":
			dialog.text = "Sabes cómo va esto. Deja que una chica se enfríe primero.";
			link.l1 = "Suspiro...";
			link.l1.go = "exit";
		break;
		
		// Тайна Порт-Рояля
		case "MysteryPortRoyal_Helena_1":
			dialog.text = "Francis... lo recuerdo. Siempre esperaba mi llegada a Port Royal y era un romántico empedernido. Disfrutaba pasar tiempo con alguien ajeno al mar – todos esos poemas y serenatas... Era algo nuevo. Un destello de un mundo que nunca conocí\nFrancis era rico, inteligente y apuesto – un gran partido. Cualquier chica del lugar habría enloquecido con su atención, pero en aquel entonces, mi única preocupación era mantener a flote el Arcoíris.";
			link.l1 = "Parece que el alma sensible de un poeta no pudo soportar tu rechazo. En todas sus cartas solo hablaba de ti, recordando los lugares donde se encontraron. Puedo entregarte todo lo que te dejó, si lo deseas.";
			link.l1.go = "MysteryPortRoyal_Helena_2";
		break;
		
		case "MysteryPortRoyal_Helena_2":
			dialog.text = "No sabía que estaba enfermo. Todo esto parece una tontería ahora. Y sobre su regalo... Ya he tenido suficiente con testamentos y herencias. Créeme, ahora tengo todo lo que necesito, y más. Mejor quédate con ello.";
			link.l1 = "Su legado, de una forma u otra, seguirá beneficiándote, así que, sin quererlo, me he convertido en el ejecutor de su última voluntad. Vaya historia.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.MysteryPortRoyal_Helena");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

bool HelenDrinking_RobbedSvenson() {
	sld = &locations[FindLocation("SantaCatalina_houseS1_residence")];
	if (!CheckAttribute(sld, "private1.items.chest")) { 
		return true;
	}
	
	if (sti(sld.private1.items.chest) < 2) {
		return true;
	}
	
	return false;
}
