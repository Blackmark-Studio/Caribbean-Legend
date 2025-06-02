// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
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
		link.l1 = "Ah, lo haré.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "seafox":
		DelMapQuestMarkCity("Charles");
		LAi_SetImmortal(npchar, false);
		DelLandQuestMark(npchar);
		LAi_RemoveLoginTime(npchar);
		PlaySound("Voice\Spanish\LE\SeaFox\SeaFox_01.wav");
		dialog.text = TimeGreeting() + ", capitán. (saluda) Permítame presentarme - Teniente " + GetFullName(npchar) + ", Regimiento Marítimo de Infantería de Antigua, guarnecido en St. Johns. Tengo un favor que pedir.";
		link.l1 = "Saludos Teniente Gretton. Mi nombre es " + GetFullName(pchar) + ". ¿Qué clase de favor?";
		link.l1.go = "seafox_1";
		break;

	case "seafox_1":
		dialog.text = "Permíteme explicarte brevemente la situación. Cuatro de mis hombres y yo navegábamos desde St. Johns hacia Sint-Maarten cuando una tormenta azotó nuestro barco. El mal tiempo no duró mucho, pero fue suficiente para que nuestra vieja nave empezara a hacer agua. Tuvimos que cambiar de rumbo y detenernos aquí para reparaciones. Eso nos está tomando un tiempo que no poseemos.\nTenemos prisa por llegar a Sint-Maarten, específicamente a la playa de Grand Case. Ayúdame, capitán, y te lo recompensaré generosamente. ¡Dos días de travesía por un pago generoso!";
		link.l1 = "Generosa debería ser la paga en verdad, teniente, si quiere que inserte clandestinamente marines ingleses en una isla holandesa.";
		link.l1.go = "seafox_2";
		break;

	case "seafox_2":
		dialog.text = "No te preocupes. Francia no está en guerra con los holandeses, así que no debería haber peligro. Sólo déjanos en la playa y eso será todo. Sólo queremos explorar un poco la isla. ¿Trato hecho?";
		link.l1 = "Está bien, estoy dentro. No está tan lejos de aquí. Vamos a escuchar sobre esa paga.";
		link.l1.go = "seafox_3";
		link.l2 = "Lamento, pero tengo un asunto urgente en otra dirección y preferiría no molestar a los holandeses.";
		link.l2.go = "seafox_exit";
		break;

	case "seafox_exit":
		dialog.text = "Como digas, capitán. Seguiré buscando entonces. ¡Adiós y que Dios te acompañe!";
		link.l1 = "Adiós, teniente.";
		link.l1.go = "seafox_exit_1";
		break;

	case "seafox_exit_1":
		DialogExit();
		chrDisableReloadToLocation = false;
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
		npchar.lifeday = 0;
		break;

	case "seafox_3":
		GiveItem2Character(pchar, "purse2");
		Log_Info("Has recibido un monedero de doblones");
		dialog.text = "Diez mil piezas de a ocho. Aquí tienes un adelanto.";
		link.l1 = "Bien. Suban a sus hombres a bordo, no perdamos más tiempo.";
		link.l1.go = "seafox_4";
		break;

	case "seafox_4":
		dialog.text = "¡Aye aye, capitán!";
		link.l1 = "...";
		link.l1.go = "seafox_5";
		break;

	case "seafox_5":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "FMQN_SailMaarten", 10.0);
		AddQuestRecord("FMQ_Nevis", "1");
		pchar.questTemp.FMQN = "begin";
		
		chrDisableReloadToLocation = false;
			sld = CharacterFromID("FMQN_seafox_1");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", "", "", "", "", 10.0); // англичане на борт
			sld.location = "None";
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.FMQN_sailing.win_condition.l1 = "location";
			pchar.quest.FMQN_sailing.win_condition.l1.location = "Shore40";
			pchar.quest.FMQN_sailing.win_condition.l2 = "Ship_location";
			pchar.quest.FMQN_sailing.win_condition.l2.location = "Shore40";
			pchar.quest.FMQN_sailing.function = "FMQN_ArriveMaarten";
			if(bImCasual)
			{
				NewGameTip(StringFromKey("FMQ_69"));
			}
			else SetFunctionTimerCondition("FMQN_SailingLate", 0, 0, 10, false);
			for(i = 0; i < MAX_LOCATIONS; i++)
			{	
				sld = &Locations[i];
				if (CheckAttribute(sld, "islandId") && sld.islandId == "SentMartin")
				{
					sld.DisableEncounters = true;	
				}
			}
			sld = &Locations[FindLocation("Shore40")];
			sld.QuestlockWeather = "23 Hour";
			AddMapQuestMarkShore("Shore40", true);
		break;

	case "seafox_6":
		PlaySound("Voice\Spanish\LE\SeaFox\SeaFox_02.wav");
		dialog.text = "¡Gracias por el tranquilo viaje, capitán! Lamento mucho esto, pero no puedo pagarle en este preciso momento... se suponía que habría un lugre nuestro en esta área, pero no está aquí. Como puede ver claramente. Debo pedirle su ayuda una vez más. ¿Podría esperar alrededor de esta bahía por dos o tres días? Tenemos que ir y echar un vistazo. Una vez que regresemos, llévenos a Antigua. El Coronel Fox le recompensará generosamente.";
		link.l1 = "Por supuesto que lo hará. Y aquí estaba yo esperando que esto fuera sin problemas.";
		link.l1.go = "seafox_7";
		break;

	case "seafox_7":
		dialog.text = "Por favor, no se frustre, capitán. Sé cómo debe sentirse, pero ay: no tengo dinero en absoluto. Le prometo que recibirá compensación por ambos viajes y por esperarnos aquí. ¡Así como los agradecimientos del propio Coronel Fox!";
		link.l1 = "No puedo simplemente dejarte a tu suerte... Muy bien, Teniente Gretton. Esperaré tres días, pero no más.";
		link.l1.go = "seafox_8";
		break;

	case "seafox_8":
		dialog.text = "¡Gracias señor! Nos dirigimos tierra adentro. Juro que estaremos de vuelta en 72 horas, ni un minuto más.";
		link.l1 = "Buen viaje, teniente. No te atrapen.";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("FMQN_EnglishmanGo");
		break;

	case "seafox_9":
		DelLandQuestMark(npchar);
		PlaySound("Voice\Spanish\LE\SeaFox\SeaFox_02.wav");
		dialog.text = "¡Qué encuentro tan fortuito! Pensé que nos estarías esperando en la Playa Grand Case, Capitán de Maure!";
		link.l1 = "Hola teniente, la sorpresa es mutua. No esperaba verte vestido como un soldado holandés.";
		link.l1.go = "seafox_10";
		break;

	case "seafox_10":
		dialog.text = "Es nuestro disfraz... ¿Por qué estás aquí afuera, señor?";
		link.l1 = "Ese es un disfraz peligroso, camarada. Los espías pueden ser ejecutados sumariamente sin juicio. Y hablando de ejecuciones, si quieres evitar la tuya, será mejor que escuches.";
		link.l1.go = "seafox_11";
		break;

	case "seafox_11":
		dialog.text = "Tienes mi completa atención.";
		link.l1 = "Navegué a Philipsburg y hablé con los locales después de que desembarcaste. Los holandeses están tras de ti. Saben sobre tu misión de rescatar a esos oficiales ingleses de alto rango capturados.";
		link.l1.go = "seafox_12";
		break;

	case "seafox_12":
		dialog.text = "¡Maldición y truenos! ¿Cómo diablos se enteraron de esto?";
		link.l1 = "Uno de los oficiales ingleses capturados. A cambio de su libertad, contó a los holandeses todo lo que sabía sobre la operación de rescate. Todo Philipsburg está listo para que tú y tus hombres intenten entrar en la ciudad. Para empeorar las cosas, un corbeta holandesa está patrullando el mar alrededor de Sint-Maartin. Es una trampa, teniente.";
		link.l1.go = "seafox_13";
		break;

	case "seafox_13":
		dialog.text = RandSwear() + "¡Ese villano deshonroso! ¡Descubriré quién es ese traidor y lo denunciaré ante el Parlamento!";
		link.l1 = "Eso tendrá que esperar, Sr. Gretton. Vuelva esta noche a la playa de Grand Case y regrese a mi barco antes de que lo atrapen.";
		link.l1.go = "seafox_14";
		break;

	case "seafox_14":
		dialog.text = "¿Y abandonar a caballeros ingleses dentro de una prisión holandesa? Preferiría morir, señor. No fallaré al Coronel Fox.";
		link.l1 = "Hum, ¿crees que los holandeses te dejarán elegir entre la horca o un pelotón de fusilamiento después de capturarte?";
		link.l1.go = "seafox_15";
		break;

	case "seafox_15":
		dialog.text = "No creas que te dejarán zarpar de aquí así como así, Capitán de Maure. Ambos estamos metidos hasta el cuello en esto.";
		link.l1 = "Maldita sea, probablemente tengas razón. Esa corbeta se nos echará encima en cuanto levemos anclas...";
		link.l1.go = "seafox_16";
		break;

	case "seafox_16":
		dialog.text = "Los holandeses pueden saber que venimos, pero no saben *cómo* venimos. Ya nos hemos encargado del disfraz: mira este uniforme. Hermoso, ¿verdad? Si nuestro plan no hubiera sido traicionado, simplemente habríamos ido a la prisión, los habríamos tomado por sorpresa y matado a todos dentro. Pero ciertamente están tendiendo una emboscada allí. Así que improvisamos. \nCapitán, ve a la iglesia de Philipsburg y encuentra a un predicador allí llamado Filippe Jacobsen. Debería estar allí de seis a diez de la mañana. Filippe es uno de los nuestros en el interior. \nDile esta contraseña: '¿Hace cuánto confesaron los marineros cautivos?'. Después de eso, cuéntale sobre la situación y exige su ayuda en nombre del Coronel Fox. Luego me entregas su respuesta. Simple y sin riesgo para ti.";
		link.l1 = "Parece bastante malditamente arriesgado preguntar sobre la confesión en una iglesia calvinista holandesa, teniente. El pastor intentará colgarme por ser papista. Está bien, cuéntame sobre estos uniformes... ¿los tomaste de una patrulla holandesa?";
		link.l1.go = "seafox_17";
		break;

	case "seafox_17":
		dialog.text = "Sí, señor.";
		link.l1 = "¿Y dónde están ahora?";
		link.l1.go = "seafox_18";
		break;

	case "seafox_18":
		dialog.text = "Detenidos como rehenes en los arbustos no muy lejos de esta cueva.";
		link.l1 = "Entendido. Manténlos a salvo, voy hacia el pueblo. Espérame aquí y mantente bajo perfil - los holandeses están peinando la jungla así como los mares buscándote.";
		link.l1.go = "seafox_19";
		break;

	case "seafox_19":
		dialog.text = "Seremos silenciosos como ratones de iglesia, capitán. ¡Por favor, date prisa!";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("FMQN_ToChurch");
		break;

	case "seafox_20":
		PlaySound("Voice\Spanish\soldier_common_4.wav");
		DelLandQuestMark(npchar);
		dialog.text = "¿Has vuelto? Capitán, ¿qué haces aquí? ¡Ve a la ciudad, estás llamando la atención sobre nuestro escondite!";
		link.l1 = "He regresado del pueblo. ¿Qué clase de juegos están jugando ustedes, ingleses?";
		link.l1.go = "seafox_21";
		break;

	case "seafox_21":
		dialog.text = "¿Le ruego me disculpe?";
		link.l1 = "Fui a la iglesia. Un gran edificio, bonito y austero, justo como les gusta a esos iconoclastas holandeses. ¿Adivina qué, teniente? No hay ningún predicador llamado Filippe Jacobsen.";
		link.l1.go = "seafox_22";
		break;

	case "seafox_22":
		dialog.text = "Eso es imposible, él visita el lugar cada mañana-";
		link.l1 = "¡Cállate y escúchame! ¡Si tu Jacobsen siquiera existe, no va a la iglesia! ¡Nunca lo han visto! ¡Ni por la mañana, ni por la noche! ¡Maldita sea! ¿Por qué acepté siquiera este maldito trabajo? ¡Liderado por un imbécil novato hijo de puta, un teniente tonto y mequetrefe mojado detrás de las orejas!";
		link.l1.go = "seafox_23";
		break;

	case "seafox_23":
		dialog.text = "Señor, exijo satisfacción por ese insulto. Después de salir de aquí, nos batiremos en duelo según las costumbres de-";
		link.l1 = "" + RandSwear() + "";
		link.l1.go = "seafox_24";
		break;

	case "seafox_24":
		PlaySound("Ambient\Jail\chain.wav");
		PlaySound("Ambient\Land\door_001.wav");
		dialog.text = "¡Cállense todos de una puta vez!!! ... Acabo de escuchar algo.";
		link.l1 = "";
		link.l1.go = "seafox_25";
		break;

	case "seafox_25":
		PlaySound("Voice\Spanish\LE\SeaFox\SeaFox_04.wav");
		dialog.text = "¡Rayos, alguien está afuera! ¡Tú! ¡Tú trajiste a los holandeses de vuelta aquí, canalla! ¡Traidor!";
		link.l1 = "" + RandSwear() + "!!!";
		link.l1.go = "exit";
		AddDialogExitQuest("FMQN_HollandBattleFight");
		break;

	case "seafox_26":
		DelLandQuestMark(npchar);
		pchar.quest.FMQN_fail1.over = "yes";
		PlaySound("Voice\Spanish\LE\SeaFox\SeaFox_02.wav");
		dialog.text = "Me alegra verte, señor, ¿qué noticias?";
		link.l1 = "Me encontré con tu hombre. Esta noche entregará un poco de vino 'sazonado' a la guarnición de la prisión. Consiguió una poción de una gitana, no es letal, pero dormirán como muertos. Necesitas entrar allí esta noche y sacar a tus caballeros capturados. Por cierto, esta entrega de vino me costó veinticinco doblones. Asegúrate de mencionarlo en el informe.";
		link.l1.go = "seafox_27";
		break;

	case "seafox_27":
		dialog.text = "No te preocupes por el dinero. Capitán, le pediría que se una a nosotros en esta operación y nos muestre el camino a la prisión. Ya ha estado en Philipsburg, así que conoce la ciudad mejor que nosotros. No es necesario que entre a la prisión con nosotros, nosotros nos encargaremos de la fuga. Solo llévenos hasta la puerta.";
		link.l1 = "¡Malditos sean mis ojos, Sr. Gretton, este trabajo sigue mejorando cada vez más! Más vale que el pago aumente proporcionalmente.";
		link.l1.go = "seafox_28";
		break;

	case "seafox_28":
		dialog.text = "Sin duda lo es, capitán. No se arrepentirá de ayudarnos. ¿Está su navío en la Playa de Grand Case?";
		if (pchar.location.from_sea == "Shore40")
		{
			link.l1 = "Sí.";
			link.l1.go = "seafox_29";
		}
		else
		{
			link.l1 = "No.";
			link.l1.go = "seafox_29x";
		}
		break;

	case "seafox_29":
		dialog.text = "Bien. Entonces prepárate y reúnete con nosotros en las puertas de la ciudad a las once en punto de la noche.";
		link.l1 = "Nos vemos allí.";
		link.l1.go = "seafox_30";
		break;

	case "seafox_29x":
		dialog.text = "Asegúrate de llevarla allí, porque tenemos que sacar a nuestros hombres a través de la jungla. Navegar desde el puerto o la Bahía de Simpson es imposible debido al fuerte. Prepara todo y reúnase con nosotros en las puertas de la ciudad a las once en punto de la noche.";
		link.l1 = "Nos vemos allí.";
		link.l1.go = "seafox_30";
		break;

	case "seafox_30":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		AddDialogExitQuestFunction("FMQN_EnglandPrepare");
		break;

	case "seafox_31":
		PlaySound("Voice\Spanish\Gr_hovernor01.wav");
		dialog.text = "¿Listo, capitán?";
		link.l1 = "Sí.";
		link.l1.go = "seafox_32";
		break;

	case "seafox_32":
		dialog.text = "Entonces, pongámonos en marcha.";
		link.l1 = "... ";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("FMQN_EnglandReload");
		break;

	case "seafox_33":
		dialog.text = "¡Chsss... Capitán! Está hecho, ¡vámonos al diablo de aquí!..";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuest("FMQN_EnglandRunToJungle");
		break;

	case "seafox_34":
		dialog.text = "¡No sé cómo lo logramos, pero lo hicimos! Nada de esto hubiera sido posible sin su ayuda, señor. Ahora viene la parte relativamente fácil: debemos salir de Sint-Maartin vivos y enteros. ¡Vamos a la Playa de Grand Case!";
		link.l1 = "¡Vamos a movernos!";
		link.l1.go = "exit";
		AddDialogExitQuest("FMQN_EnglandRunToShore");
		break;

	case "seafox_35":
		PlaySound("Voice\Spanish\LE\SeaFox\SeaFox_05.wav");
		dialog.text = "Capitán de Maure... señor, ¡gracias por su asistencia! Le ruego, por favor, que no zarpe inmediatamente, sino que se quede aquí un día más mientras informo al Coronel Fox. Visítelo mañana, su oficina está en el palacio del gobernador.";
		link.l1 = "Muy bien, teniente Gretton. Por favor, haga que valga la pena. Va a llevar mucho tiempo reparar mi reputación con los holandeses por su escapada.";
		link.l1.go = "seafox_36";
		break;

	case "seafox_35x":
		PlaySound("Voice\Spanish\LE\SeaFox\SeaFox_05.wav");
		dialog.text = "¡Gracias por tu ayuda, capitán! ¡Eres un verdadero héroe! Es una tragedia que el teniente Gretton no lo haya logrado. Murió como un verdadero caballero y un hijo de Inglaterra. Pediría quedarme aquí un día más mientras informo al coronel Fox. Visítalo mañana, su oficina está en el palacio del gobernador.";
		link.l1 = "Muy bien. Por favor, haz que valga la pena. Va a llevar mucho tiempo reparar mi reputación con los holandeses por culpa de tu escapada.";
		link.l1.go = "seafox_36";
		break;

	case "seafox_36":
		dialog.text = "No se preocupe, señor. Le daré el mayor crédito posible en mi informe. (saluda) ¡Fue un placer, señor!";
		link.l1 = "...";
		link.l1.go = "seafox_37";
		break;

	case "seafox_37":
		DialogExit();
		npchar.lifeday = 0;
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", -1);
		pchar.quest.FMQN_eng_reward.win_condition.l1 = "Timer";
		pchar.quest.FMQN_eng_reward.win_condition.l1.date.hour = 6.0;
		pchar.quest.FMQN_eng_reward.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.FMQN_eng_reward.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.FMQN_eng_reward.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.FMQN_eng_reward.function = "FMQN_EnglandReward";
		AddQuestRecord("FMQ_Nevis", "28");
		break;

	case "soldier":
		PlaySound("Voice\Spanish\soldier_common_2.wav");
		dialog.text = "¿Capitán " + GetFullName(pchar) + "?";
		link.l1 = "Mm... Sí, ¿qué puedo hacer por ti?";
		link.l1.go = "soldier_1";
		break;

	case "soldier_1":
		dialog.text = "La oficina del puerto nos ha informado sobre la reciente llegada de su barco. Su Excelencia, Mynheer Martin Thomas, el gobernador de Philipsburg, desea verlo. ";
		link.l1 = "¿Para qué? ¿Estoy bajo arresto?";
		link.l1.go = "soldier_2";
		break;

	case "soldier_2":
		AddLandQuestMark(characterFromId("Marigo_Mayor"), "questmarkmain");
		dialog.text = "¡Oh no, no, señor capitán, no está bajo arresto! El gobernador ha ordenado invitar a cada capitán recién llegado a su palacio para tomar café y presentaciones. ¡Sígame!";
		link.l1 = "Suena como una oferta que no puedo rechazar. Guía el camino.";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("FMQN_ReloadToGovernor");
		break;

	case "hol_officer":
		PlaySound("Voice\Spanish\hol_gov_complete.wav");
		dialog.text = "Mynheer, muéstranos dónde viste a esos soldados ingleses.";
		link.l1 = "Se esconden en una cueva en la jungla, como vulgares bandidos.";
		link.l1.go = "hol_officer_1";
		break;

	case "hol_officer_1":
		dialog.text = "¡Guía, te seguimos!";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuest("FMQN_HollandBattleMarch");
		break;

	case "hol_officer_2":
		PlaySound("Voice\Spanish\hol_gov_quest.wav");
		dialog.text = "¡Espera, capitán! ¿Mencionaste que te habías encontrado con los espías allí - cerca de la entrada de la cueva?";
		link.l1 = "Sí. Brevemente los vi entrar después de que hablaron conmigo.";
		link.l1.go = "hol_officer_3";
		break;

	case "hol_officer_3":
		dialog.text = "Lo más probable es que todavía estén ahí dentro. Si atacamos todos a la vez, se retirarán a la cueva. Será una pesadilla sacarlos de allí... Vamos a ser astutos. Capitán, usted vaya solo y distráigalos. Yo y mis hombres nos moveremos a ese pozo seco a la vuelta de la esquina. Conduce directamente al interior de la cueva. Los malditos no nos verán venir por detrás. Entra y si los espías todavía están allí, háblales, hazles preguntas estúpidas y mantenlos ocupados. Una vez que tengas toda su atención, maldice tan suciamente como puedas. Eres un marinero, así que eso debería salirte naturalmente. Ese será nuestra señal. Dos de mis hombres guardarán la entrada principal para impedir que escapen por ahí. Los atraparemos.";
		link.l1 = "Tu plan suena terriblemente peligroso para mi salud. Según lo veo, solo intentarán matarme primero.";
		link.l1.go = "hol_officer_4";
		break;

	case "hol_officer_4":
		dialog.text = "No te preocupes, capitán. Tu objetivo es gritar tan fuerte como puedas tan pronto como veas al grupo de ataque enemigo. Si te atacan, corre y sigue gritando. Mis hombres están bien entrenados, así que no te preocupes, acabarán con esos espías antes de que te hagan daño.";
		link.l1 = "Más les vale. Voy a entrar allí.";
		link.l1.go = "exit";
		AddDialogExitQuest("FMQN_HollandBattlePosition");
		break;

	case "hol_officer_5":
		PlaySound("Voice\Spanish\hol_gov_common.wav");
		dialog.text = "Malditos bastardos eran... Bien hecho, capitán, los perros ingleses han sido eliminados. Nuestro comandante y el gobernador estarán complacidos.";
		link.l1 = "Te tomaste tu dulce tiempo, mynheer...";
		link.l1.go = "hol_officer_6";
		break;

	case "hol_officer_6":
		dialog.text = "Maldita soga, tenía un cubo al final que hacía un ruido infernal. Tuvimos que tener cuidado.";
		link.l1 = "Sí... la cuerda. Lo que sea. Una de tus patrullas desaparecidas está atada allá en los arbustos. Deberían seguir con vida.";
		link.l1.go = "hol_officer_7";
		break;

	case "hol_officer_7":
		dialog.text = "Me encargaré de ellos. Deberías ir a la ciudad y descansar un poco. Visita a nuestro gobernador mañana, tendrá mi informe con una brillante recomendación de ti para entonces.";
		link.l1 = "Lo haré. Que Dios te acompañe, mynheer.";
		link.l1.go = "exit";
		AddDialogExitQuest("FMQN_HollandBattleRest");
		break;

	case "monk":
		DelLandQuestMark(npchar);
		DelLandQuestMarkToPhantom();
		if (GetCharacterIndex("marigojailoff") != -1)
		{
			DelLandQuestMark(characterFromId("marigojailoff"));
		}
		pchar.questTemp.FMQN = "way_eng_2";
		dialog.text = "¿Qué puedo hacer por ti, hijo mío?";
		link.l1 = "Hola pastor, solo por curiosidad, ¿hace cuánto tiempo confesaron los marineros cautivos?";
		link.l1.go = "monk_1";
		break;

	case "monk_1":
		dialog.text = "Ayer por la tarde, hijo mío... (susurrando) ¿Supongo que sabes que el plan ha sido traicionado?";
		link.l1 = "No estaría aquí de otra manera. El teniente Casper Gratton y sus hombres están en la jungla en este momento. Todos están vestidos como soldados holandeses, pero necesitamos ayuda adicional ya que los guardias de la prisión los están esperando.";
		link.l1.go = "monk_2";
		break;

	case "monk_2":
		dialog.text = "(en voz alta) ¡Recé todos los días para salvar su alma anglicana de la condenación! (susurrando) Tengo un plan, pero necesito dos docenas de doblones de oro para conseguir todo lo que necesito.";
		link.l1 = "Plan caro. ¿Para qué es el dinero?";
		link.l1.go = "monk_3";
		break;

	case "monk_3":
		dialog.text = "Ser guardia de prisión es un deber aburrido. Para mantener la moral, el oficial a cargo ordena un poco de vino cada noche para acompañar su cena. El vino se trae de un almacén al que tengo acceso. Hay una gitana en el pueblo que me debe un favor, ella nos hará una poción para dormir. Todo lo que necesito es comprar unas pocas botellas de buen vino, añadir la poción y cambiar las botellas en el almacén. Por eso necesito el oro.";
		if (PCharDublonsTotal() >= 24)
		{
			link.l1 = "Tengo los doblones. Tómalos.";
			link.l1.go = "monk_4";
		}
		else
		{
			link.l1 = "Déjame volver a mi barco y conseguirte algo.";
			link.l1.go = "monk_wait";
		}
		break;

	case "monk_wait":
		DialogExit();
		npchar.dialog.currentnode = "monk_repeat";
		break;

	case "monk_repeat":
		dialog.text = "Ah, hijo mío, ¿tienes la 'donación' de la que hablamos?";
		if (PCharDublonsTotal() >= 24)
		{
			link.l1 = "Sí, aquí.";
			link.l1.go = "monk_4";
		}
		else
		{
			link.l1 = "Lo conseguiré pronto...";
			link.l1.go = "monk_wait";
		}
		break;

	case "monk_4":
		RemoveDublonsFromPCharTotal(24);
		dialog.text = "Espléndido. Ven a verme a la misma hora mañana - te diré los resultados.";
		link.l1 = "Muy bien...";
		link.l1.go = "monk_5";
		break;

	case "monk_5":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		AddQuestRecord("FMQ_Nevis", "18");
		pchar.quest.FMQN_monk.win_condition.l1 = "Timer";
		pchar.quest.FMQN_monk.win_condition.l1.date.hour = 6.0;
		pchar.quest.FMQN_monk.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.FMQN_monk.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.FMQN_monk.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.FMQN_monk.function = "FMQN_EnglandMonkPlan";
		pchar.quest.FMQN_fail.win_condition.l1 = "Timer";
		pchar.quest.FMQN_fail.win_condition.l1.date.hour = 11.0;
		pchar.quest.FMQN_fail.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.FMQN_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.FMQN_fail.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.FMQN_fail.function = "FMQN_EnglandFail";
		pchar.questTemp.FMQN = "way_eng_3";
		break;

	case "monk_6":
		DelLandQuestMark(npchar);
		pchar.quest.FMQN_fail.over = "yes";
		dialog.text = "Saludos, hijo mío.";
		link.l1 = "Lo mismo para usted, pastor. ¿Alguna novedad?";
		link.l1.go = "monk_6x";
		break;

	case "monk_6x":
		dialog.text = "Sí. Está hecho. El vino ha sido 'sazonado' y los guardias recibirán un regalo especial esta noche. Cenan a las nueve de la noche, estarán todos dormidos a medianoche. Esta es tu única oportunidad para hacer el trabajo, no hay segundas oportunidades. Ten cuidado, no puedes confiar completamente en tu disfraz holandés.";
		link.l1 = "Entendido. No perdamos tiempo. Adiós.";
		link.l1.go = "monk_7";
		break;

	case "monk_7":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		npchar.lifeday = 0;
		AddQuestRecord("FMQ_Nevis", "20");
		sld = CharacterFromID("FMQN_seafox_1");
		sld.dialog.currentnode = "seafox_26";
		LAi_CharacterEnableDialog(sld);
		sld.talker = 9;
		AddLandQuestMark(sld, "questmarkmain");
		pchar.quest.FMQN_fail1.win_condition.l1 = "Timer";
		pchar.quest.FMQN_fail1.win_condition.l1.date.hour = 20.0;
		pchar.quest.FMQN_fail1.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
		pchar.quest.FMQN_fail1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
		pchar.quest.FMQN_fail1.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
		pchar.quest.FMQN_fail1.function = "FMQN_EnglandFail";
		pchar.questTemp.FMQN = "way_eng_4";
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
