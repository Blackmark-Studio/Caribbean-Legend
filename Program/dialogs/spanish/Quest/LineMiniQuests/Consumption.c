// диалоги по квесту Цена чахотки
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	string sStr;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		if (pchar.questTemp.Consumption == "final")
		{
			dialog.text = "¡Capitán! ¡He oído que te hiciste a la mar! ¿Qué pasó? ¿Descubriste algo? ¡Por favor, cuéntamelo, suéltalo de una vez!";
			if (CheckAttribute(pchar, "questTemp.Consumption.TakeMoney"))
			{ // взял деньги
				link.l1 = "No, mi belleza, esta incursión se hizo a petición de Su Gracia el gobernador. Lo siento mucho, pero Angelo murió en las casamatas del fuerte - ahora no hay duda de eso. ¡Mantente firme! ";
				link.l1.go = "Waitress";
			}
			else
			{ // убил Хуана
				if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
				{
					link.l1 = "Tenías razón. Tu hermano fue secuestrado. El comandante había estado vendiendo prisioneros como ganado a un traficante de esclavos apodado Consumo. Pero alcancé su barco, y ahora yace en el fondo, y tu hermano Ángelo llegará a tierra pronto. Desafortunadamente, no tengo tantas chalupas como se necesita para llevar a todos los pasajeros a tierra de una vez.";
					link.l1.go = "Waitress_2";
				}
				else
				{ // отпустил Хуана
					link.l1 = "Tenías razón. Tu hermano fue secuestrado. El comandante había estado vendiendo prisioneros como ganado a un traficante apodado Consumo. Pero alcancé su barco, a pesar de que no logré matar a ese bastardo, tu hermano Angelo llegará a tierra pronto. Desafortunadamente, no tengo tantas chalupas como se necesitan para que todos los pasajeros lleguen a tierra al mismo tiempo.";
					link.l1.go = "Waitress_2";
				}
				sld = characterFromId("ConAndjelo");
				sld.lifeday = 0;
				RemovePassenger(Pchar, sld);
			}
		}
		else
		{
			dialog.text = "¿Lograste averiguar algo sobre el destino de Angelo, capitán?";
			link.l1 = "Aún no. Pero creo que pronto tendré noticias. Solo necesitas esperar. ";
			link.l1.go = "exit";
		}
		NextDiag.TempNode = "First time";
		break;
	case "without_moneysss": // лесник  если Гг нажрался..сволочь:D:D:D
		dialog.text = "Señor, prometiste encontrar a mi hermano... ¿Por qué estás perdiendo el tiempo bebiendo aquí?";
		link.l1 = "Ohh..Sí, claro..hic... Relájate, muchacha... Jesús tiene el control..'slurp'... Jesús tiene el control. Ya me he ido...hic..";
		link.l1.go = "exit";
		break;

	case "Servant":
		dialog.text = "Buenas tardes, señor. ¿Cuál es su negocio aquí?";
		link.l1 = "He traído un despacho para el señor comandante, pero debo entregárselo personalmente.";
		link.l1.go = "Servant_1";
		break;

	case "Servant_1":
		dialog.text = "Entonces ve a buscarlo en el fuerte.";
		link.l1 = "Este despacho es demasiado importante y no es para ojos y oídos de soldados. Tal vez llegué demasiado temprano, pero puedo esperarle aquí. ¡Créeme, es muy importante!";
		link.l1.go = "Servant_2";
		break;

	case "Servant_2":
		if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < 40)
		{
			notification("Skill Check Failed (40)", SKILL_SNEAK);
			dialog.text = "El señor comandante suele advertirme sobre todos los asuntos importantes que requieren cambiar la rutina... Sabes, de hecho, me advirtió sobre este caso en particular.";
			link.l1 = "¿Y qué dijo?";
			link.l1.go = "Servant_3";
		}
		else
		{
			notification("Skill Check Passed", SKILL_SNEAK);
			dialog.text = "Está bien, te creo. Y te creeré aún más cuando el señor comandante llegue para confirmar tus palabras. Pero antes de eso, te estaré vigilando constantemente.";
			link.l1 = "Puedes observarme tanto como quieras...";
			link.l1.go = "Servant_4";
		}
		break;

	case "Servant_3":
		dialog.text = "Él me dijo que llamara a los guardias de la guarnición en tales casos. Pero probablemente nos las arreglaremos por nosotros mismos. ¡Chicos! ¡Vamos a destriparlo!";
		link.l1 = "¡Mierda!";
		link.l1.go = "Servant_fight";
		break;

	case "Servant_4":
		DialogExit();
		NextDiag.CurrentNode = "Servant_repeat";
		LAi_SetOwnerType(npchar);
		chrDisableReloadToLocation = false;
		break;

	case "Servant_repeat":
		dialog.text = "¿Qué más quieres? ¿Has decidido darme el mensaje?";
		link.l1 = "No, esperaré al comandante...";
		link.l1.go = "exit";
		NextDiag.TempNode = "Servant_repeat";
		break;

	case "Servant_fight":
		int iRank = sti(pchar.rank) + 5;
		int iScl = 15 + 2 * sti(pchar.rank);
		DialogExit();
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		chrDisableReloadToLocation = true;
		for (i = 9; i <= 11; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Conservant_" + i, "citiz_" + i, "man", "man", iRank, SPAIN, -1, true, "quest"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol1", "bullet", iScl * 2);
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "PortSpein_houseF2", "goto", "goto5");
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Consumption_AfterHouseFight");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	// попытка залезть в сундук
	case "Man_FackYou":
		dialog.text = "¡Eres un ladrón! ¿O, tal vez, un espía? ¡Muchachos, abajo rápido!";
		link.l1 = "¡Gah, demonio!";
		link.l1.go = "Servant_fight";
		break;

	case "Sergio":
		dialog.text = "Disculpe, ¿puedo hablar con usted?";
		link.l1 = "Para ser honesto, tengo prisa. ¿Qué quieres?";
		link.l1.go = "Sergio_1";
		break;

	case "Sergio_1":
		dialog.text = "Escuché que andas preguntando sobre un hombre llamado Juan y una enfermedad en nuestra prisión...";
		link.l1 = "De hecho lo hice... podrías explicarte.";
		link.l1.go = "Sergio_2";
		break;

	case "Sergio_2":
		dialog.text = "¡Tranquilo, tranquilo! ¡Calma y no toques tu espada! ¡Estamos del mismo lado aquí! No sé por qué te importarían nuestros problemas, ¡pero esto debe detenerse! ¡No puedo guardar silencio más!";
		link.l1 = "¿Guardar silencio? ¿Sobre qué? ¿Qué sabes sobre el consumo?";
		link.l1.go = "Sergio_3";
		break;

	case "Sergio_3":
		dialog.text = "Yo sé mucho, si no todo, y me explicaré, pero no aquí. Reunámonos por la noche cuando las luces estén apagadas, soy asistente médico, así que tengo permiso para salir del fuerte. Nos encontraremos más allá de las puertas de la ciudad, y te contaré todo. Te suplico: deja de hacer preguntas, antes de que llames su atención, si es que no lo has hecho ya... Tengo que irme ahora. Recuerda, por la noche más allá de las puertas de la ciudad.";
		link.l1 = "Está bien, estaré allí. ¡Oye! Espera...";
		link.l1.go = "Sergio_4";
		break;

	case "Sergio_4":
		DialogExit();
		AddQuestRecord("Consumption", "8");
		LAi_ActorRunToLocation(npchar, "reload", "gate_back", "none", "", "", "OpenTheDoors", -1);
		pchar.quest.Consumption3.win_condition.l1 = "location";
		pchar.quest.Consumption3.win_condition.l1.location = "PortSpein_Exittown";
		pchar.quest.Consumption3.win_condition.l2 = "Hour";
		pchar.quest.Consumption3.win_condition.l2.start.hour = 0;
		pchar.quest.Consumption3.win_condition.l2.finish.hour = 3;
		pchar.quest.Consumption3.function = "Consumption_MeetSergio";
		pchar.quest.Consumption4.win_condition.l1 = "Timer";
		pchar.quest.Consumption4.win_condition.l1.date.hour = sti(GetTime());
		pchar.quest.Consumption4.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.Consumption4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.Consumption4.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.Consumption4.function = "Consumption_FailSergio";
		locations[FindLocation("PortSpein_Exittown")].DisableEncounters = true; // энкаутеры закрыть
		LAi_LocationDisableOfficersGen("PortSpein_Exittown", true);				// офицеров не пускать
		break;

	case "Sergio_5":
		dialog.text = "Gracias a Dios, estás aquí... ¿Espero que no te hayan seguido?";
		link.l1 = "¿Por qué? Eres demasiado suspicaz, quizás incluso más que el señor comandante, así que será mejor que vayas al grano... ¿Qué sabes sobre Juan?";
		link.l1.go = "Sergio_6";
		break;

	case "Sergio_6":
		dialog.text = "Mi nombre es Sergio Saldo. Sirvo como asistente médico en nuestro fuerte y...";
		link.l1 = "";
		link.l1.go = "Sergio_6_1";
		break;

	case "Sergio_6_1":
		dialog.text = "";
		link.l1 = "¡Espera! ¿Escuchaste eso?";
		link.l1.go = "Sergio_7";
		Play3DSound("lomanie_vetki", -33.25, 1.00, 3.73) break;

	case "Sergio_7":
		dialog.text = "¿Qué?! ¿Dónde?";
		link.l1 = "Mierda, no estamos solos aquí... ¿A quién trajiste contigo, escoria?";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Consumption_CreateBandits");
		break;

	case "Bandit":
		dialog.text = "¡Nos han notado! ¡Tú tomas al médico, y yo me encargo del otro!";
		link.l1 = "...";
		link.l1.go = "Bandit_1";
		break;

	case "Bandit_1":
		DialogExit();
		sld = characterFromId("Sergio");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		for (i = 1; i <= 3; i++)
		{
			sld = characterFromId("Conbandit_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Conbandit_AfterFight");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "Sergio_8":
		dialog.text = "Guarda tu espada, ¡se acabó! ¡Has visto por ti mismo que también intentaron matarme a mí!";
		link.l1 = "Bueno, parece demasiado sofisticado para un juego sucio, así que no estás con ellos. ¿En qué nos quedamos? Eres un médico de prisión, ¿verdad?";
		link.l1.go = "Sergio_9";
		break;

	case "Sergio_9":
		dialog.text = "Sí. Sirvo como médico de la prisión. Solía estudiar medicina cuando era joven, y no hay muchas personas educadas aquí. ¡Por eso sé mejor que nadie lo que está pasando en la prisión!";
		link.l1 = "¿Qué está pasando entonces? ¿Qué hay de los prisioneros? ¿Sabes algo sobre su repentina desaparición?";
		link.l1.go = "Sergio_10";
		break;

	case "Sergio_10":
		dialog.text = "Nuestro comandante los vende... los vende como ganado a un traficante de esclavos llamado Juan. Elige a aquellos a quienes no van a buscar: indigentes, marineros de barcos al azar. Y luego, de repente, 'mueren de consunción' - puedes imaginarte el resto...";
		link.l1 = "¡Ese Juan es humano, después de todo! ¿Qué sabes de él?";
		link.l1.go = "Sergio_11";
		break;

	case "Sergio_11":
		dialog.text = "Un poco. Solía hacer sus sucios negocios en Marruecos junto con piratas berberiscos, le gusta contar historias sobre esos tiempos cuando nos visita. Fue allí donde obtuvo su apodo - Consumo. No quiero pensar en sus orígenes.\nViene aquí cada mes y se lleva a todos los prisioneros a bordo.";
		link.l1 = "¡'Consumo!' ¡Y me acusaron de ser cínico! Entonces por eso... ¡Ese señor comandante tuyo es un verdadero imbécil!";
		link.l1.go = "Sergio_12";
		break;

	case "Sergio_12":
		dialog.text = "Por lo que entiendo, necesitas a alguien de entre los prisioneros perdidos, de lo contrario, ¿cómo sabrías de esta historia, no es así? Si es así, deberías darte prisa: esta noche es la última de este mes. ¡Ya he firmado los papeles declarando la muerte de tres personas más, y Juan zarpará mañana antes del mediodía, cuando los reciba!";
		link.l1 = "¿Qué has firmado? No te sigo del todo...";
		link.l1.go = "Sergio_13";
		break;

	case "Sergio_13":
		dialog.text = "¡Tuve que hacerlo, como lo había estado haciendo durante varios meses ya! Por eso vine aquí para detener esto. ¿Sabes cómo murió el Doctor Pinero? ¿El que había tratado a los prisioneros antes que yo?";
		link.l1 = "Creo que me dijeron que murió de tisis, ¿no es así? Entonces, estás obligado a hacerlo. Eso es lógico, pero ¿por qué nadie contactó a las autoridades respecto a este asunto?";
		link.l1.go = "Sergio_14";
		break;

	case "Sergio_14":
		dialog.text = "¿Y quién creerá en esto? No poseo ninguna prueba y esos soldados que se supone deben custodiar a los prisioneros están siendo generosamente pagados, así que no les importaría incluso si estuvieran vendiendo gente a los caribes como comida.\nA nadie le importa un comino los prisioneros y eso es un as en la manga del comandante. ¡Pero tú puedes detener esto, al menos por algún tiempo, eliminando a Juan!";
		link.l1 = "Por lo que entiendo, esos tipos en tierra eran sus hombres, ¿no es así? ¿Cómo puedo encontrarlo?";
		link.l1.go = "Sergio_15";
		break;

	case "Sergio_15":
		dialog.text = "Probablemente has llamado la atención de alguien con tus preguntas... ¡Te dije que fueras más cuidadoso! Pero eso no es importante ahora. No sé nada sobre el barco de Juan, pero los prisioneros siempre son enviados a Punta Galera, que está en la parte norte de la isla. Supongo que el barco del negrero debería estar cerca y podrías alcanzarlo. Sus mensajeros han mencionado hoy que planea zarpar mañana al mediodía.";
		if (!CheckCharacterItem(pchar, "letter_consumption"))
		{
			link.l1 = "Gracias, Sergio, eres un verdadero oficial y un hombre de honor. Levantaré el ancla ahora mismo, y encontraré ese barco inmundo. Debes regresar al fuerte antes de que empiecen a buscarte.";
			link.l1.go = "Sergio_16";
		}
		else
		{
			link.l1 = "Bueno, eso es todo lo que necesito saber. Tengo que levantar el ancla ahora mismo si no quiero buscar ese 'Consumo' por todo el Nuevo Mundo. Mientras tanto, puedes estudiar esto.";
			link.l1.go = "Sergio_17";
		}
		break;

	case "Sergio_16":
		dialog.text = "¡Buena suerte, capitán! No te preocupes por mí - lo más importante es detener esto al menos por un tiempo. ¡Te deseo suerte!";
		link.l1 = "Mis cañones son el mejor remedio para la dolencia y la mezquindad. ¡Juro que todos los prisioneros estarán en tierra antes del amanecer, y el barco de Juan descansará en el fondo del mar!";
		link.l1.go = "Sergio_19";
		break;

	case "Sergio_17":
		RemoveItems(PChar, "letter_consumption", 1);
		Log_Info("Has entregado la carta");
		PlaySound("interface\important_item.wav");
		dialog.text = "¿Qué es esto? Aquí está el nombre del coronel y un monograma 'J'? ¡Increíble! ¿De dónde lo sacaste?";
		link.l1 = "Más te vale no saber eso, pero creo que lo usarás de la mejor manera posible.";
		link.l1.go = "Sergio_18";
		break;

	case "Sergio_18":
		dialog.text = "¡Lo haré, lo juro por todo lo sagrado! ¡El coronel irá a la horca antes de fin de mes! ¡Me encargaré personalmente de ello!";
		link.l1 = "Me temo que esto terminará en un castigo disciplinario, que, según entiendo, no será el primero en su vida. ¿Quizás sea mejor dispararle a ese perro? Es un remedio muy eficiente... Tengo que irme ahora, no quiero hacer esperar a 'Consumption'.";
		link.l1.go = "Sergio_19";
		break;

	case "Sergio_19":
		DialogExit();
		AddQuestRecord("Consumption", "11");
		LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
		pchar.quest.Consumption5.win_condition.l1 = "location";
		pchar.quest.Consumption5.win_condition.l1.location = "Trinidad";
		pchar.quest.Consumption5.function = "Consumption_CreateJuan";
		pchar.quest.Consumption6.win_condition.l1 = "HardHour";
		pchar.quest.Consumption6.win_condition.l1.hour = 13;
		pchar.quest.Consumption6.function = "Consumption_FailJuan";
		// Сержио теперь наш друг и будет торговать смолами
		SetFunctionTimerCondition("Oil_PrepareSergio", 0, 0, 20, false); // таймер
		break;

	// генератор торговли смолами
	case "Sergio_20":
		dialog.text = "¡Oh, qué encuentro tan afortunado! Señor " + GetFullName(pchar) + "¡ Estoy tan contento de verte!";
		link.l1 = "¡Señor Sergio! ¡No esperaba encontrarlo! ¿Cómo está usted? ¿Cómo está el buen viejo comandante?";
		link.l1.go = "Sergio_21";
		break;

	case "Sergio_21":
		dialog.text = "Estoy bien, y el señor comandante ha ido a las minas de Los-Teques - sus sucias maquinaciones con Juan Consumo han sido reveladas.";
		link.l1 = "¿¡Minas!? ¡Por mi alma! Nunca pensé que se haría justicia en su caso...";
		link.l1.go = "Sergio_22";
		break;

	case "Sergio_22":
		dialog.text = "Ah, si tan solo fuera así, capitán... Solo fue transferido y degradado. Ahora sirve en la guarnición, y ni siquiera fue despojado de su rango de oficial. Bueno, al menos San José se libró de esta escoria.";
		link.l1 = "Bueno, hasta ahora todo bien. Aunque esperaba más.";
		link.l1.go = "Sergio_23";
		break;

	case "Sergio_23":
		dialog.text = "Yo también... Pero olvidémonos de ese canalla - no merece que se hable de él. Señor, tan pronto como supe que su barco estaba a punto de entrar al puerto, me apresuré al muelle con toda celeridad. Tengo un trato para usted.";
		link.l1 = "¿De veras? Estoy escuchando.";
		link.l1.go = "Sergio_24";
		break;

	case "Sergio_24":
		if (startHeroType == 1)
			sStr = "French";
		if (startHeroType == 2)
			sStr = "Spanish";
		if (startHeroType == 3)
			sStr = "English";
		if (startHeroType == 4)
			sStr = "English";
		dialog.text = "Capitán, parece ser un hombre de confianza. Otra cosa muy significativa es que usted es " + sStr + " y tienes tu propio barco. Sugiero que concluyamos un acuerdo comercial.";
		link.l1 = "¡Suena prometedor! ¿Qué tipo de acuerdo?";
		link.l1.go = "Sergio_25";
		break;

	case "Sergio_25":
		dialog.text = "Más vale que discutamos esto en otro lugar, en el faro, en la cabaña del guardián. Él es un viejo amigo mío y confío en él. Ven al faro de San José hoy o mañana. Te esperaré allí. ¡Estoy seguro de que encontrarás mi propuesta muy interesante!";
		link.l1 = "¡Está bien, señor Sergio. Te veré allí!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Oil_SergioRuntoMayak");
		break;

	case "Sergio_26":
		chrDisableReloadToLocation = true;				   // закрыть локацию
		pchar.quest.Oil_SetSergioToMayakOver.over = "yes"; // снять прерывание
		dialog.text = "Bienvenido de nuevo, señor. Permítame explicarle este asunto. ";
		link.l1 = "Soy todo oídos. ";
		link.l1.go = "Sergio_27";
		break;

	case "Sergio_27":
		dialog.text = "Como ya podrás saber, no soy solo un soldado, sino también un médico. ¿Por qué? Porque soy un hombre bien educado. Mi educación me impidió perder el tiempo aquí con mujeres y bebidas. En lugar de eso, organicé varias expediciones y logré encontrar un yacimiento de resina no muy lejos de aquí\nEste es un recurso de importancia estratégica, esta isla es el único lugar donde se puede encontrar la resina especial que se utiliza para construir barcos sólidos y duraderos\nUn gobernador y un comandante me ordenaron vender toda la resina a la armada española\nEl problema es que me pagan la mitad de su precio de mercado y no puedo venderla en otro lugar. Por lo tanto, te ofrezco comprarla de mí. Es una mercancía muy importante y muy difícil de conseguir.";
		link.l1 = "¿Cuáles son las condiciones de nuestro acuerdo? ";
		link.l1.go = "Sergio_28";
		break;

	case "Sergio_28":
		dialog.text = "Según mis cálculos, podré recolectar 60 barriles por mes sin levantar sospechas. Hagamos un trato: cada quinto día de cada mes visitaré este faro para beber con mi amigo. Ven y únete a nosotros si quieres comprar la resina. Diez doblones de oro por barril\nPagas por todo el lote y te lo llevas de una vez. Sin presiones, depende de ti. Entonces, ¿trato hecho?";
		link.l1 = "¡Me parece un maldito buen trato! ¡Por supuesto, es un trato!";
		link.l1.go = "Sergio_29";
		break;

	case "Sergio_29":
		dialog.text = "Maravilloso. Entonces, cada cinco de mes beberé una botella de vino canario con mi viejo amigo, el guardián, y te esperaremos.";
		link.l1 = "Bien. Hagámoslo de esa manera.";
		link.l1.go = "Sergio_30";
		break;

	case "Sergio_30":
		dialog.text = "Me alegra que hayamos llegado a un acuerdo. ¡Nos vemos, capitán!";
		link.l1 = "¡Buena suerte en tu negocio de resina, señor!";
		link.l1.go = "Sergio_31";
		break;

	case "Sergio_31":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
		pchar.questTemp.OilTrade = "true";
		pchar.quest.Oil_fail.win_condition.l1 = "NPC_Death";
		pchar.quest.Oil_fail.win_condition.l1.character = "Sergio";
		pchar.quest.Oil_fail.function = "Oil_TradeFail";
		AddQuestRecordInfo("Unique_Goods", "4");
		break;

	case "oil_trade":
		dialog.text = "¡Hola, señor capitán! Ha venido por un lote de resina, supongo.";
		link.l1 = "Así es, señor Sergio. ¿Está todo listo?";
		link.l1.go = "oil_trade_1";
		link.l2 = "Señor Sergio, no estoy de humor para comerciar. Tal vez más tarde.";
		link.l2.go = "oil_trade_exit";
		break;

	case "oil_trade_exit":
		DialogExit();
		NextDiag.CurrentNode = "oil_trade";
		break;

	case "oil_trade_1":
		if (CheckAttribute(pchar, "questTemp.UpgradeOil"))
		{
			dialog.text = "Sí. ¿Tienes 2550 doblones contigo?";
			if (PCharDublonsTotal() >= 2550)
			{
				link.l1 = "Claro. Aquí tienes.";
				link.l1.go = "oil_trade_2";
			}
			else
			{
				link.l1 = "¡Mala suerte! He olvidado el dinero en mi barco. ¡Lo traeré aquí de inmediato!";
				link.l1.go = "oil_trade_exit";
			}
		}
		else
		{
			dialog.text = "Sí. ¿Tienes seiscientos doblones contigo?";
			if (PCharDublonsTotal() >= 600)
			{
				link.l1 = "Claro. Aquí tienes.";
				link.l1.go = "oil_trade_2";
			}
			else
			{
				link.l1 = "¡Qué mala suerte! He olvidado el dinero en mi barco. ¡Lo traeré aquí de inmediato!";
				link.l1.go = "oil_trade_exit";
			}
		}
		if (sti(pchar.questTemp.SergioOil) >= 1 && !CheckAttribute(pchar, "questTemp.SergioOilBlock")) // увеличить объём поставок смолами
		{
			link.l4 = "Señor Sergio, quiero comprar más resina. ¿Podría proporcionar lotes, digamos, cinco veces más grandes?";
			link.l4.go = "UpgradeOil";
		}
		if (sti(pchar.questTemp.SergioOil) >= 1 && CheckAttribute(pchar, "questTemp.SergioOilPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок смолами, если в первый раз не принесли
		{
			link.l4 = "Aquí, como prometido, Señor Sergio, tres mil doblones, como solicitó. Estoy seguro de que con su previsión y mi inversión, esta empresa nos traerá considerables beneficios a ambos.";
			link.l4.go = "UpgradeOil_Agreed";
		}
		break;

	case "oil_trade_2":
		chrDisableReloadToLocation = true; // закрыть локацию
		if (CheckAttribute(pchar, "questTemp.UpgradeOil"))
			RemoveDublonsFromPCharTotal(2550);
		else
			RemoveDublonsFromPCharTotal(600);
		PlaySound("interface\important_item.wav");
		dialog.text = "Es un placer tratar con usted, capitán. Mi gente le ayudará a cargar los barriles en su barco.";
		link.l1 = "¡Gracias!";
		link.l1.go = "oil_trade_3";
		break;

	case "oil_trade_3":
		dialog.text = "El trato sigue en pie. Si necesitas otro lote, vuelve en un mes.";
		link.l1 = "Está bien, Sergio. Nos vemos.";
		link.l1.go = "oil_trade_4";
		break;

	case "oil_trade_4":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
		if (CheckAttribute(pchar, "questTemp.UpgradeOil"))
			AddCharacterGoods(pchar, GOOD_OIL, 300);
		else
			AddCharacterGoods(pchar, GOOD_OIL, 60);
		AddCharacterExpToSkill(pchar, "Commerce", 200);
		pchar.questTemp.SergioOil = sti(pchar.questTemp.SergioOil) + 1; // счётчик покупок
		break;

	case "UpgradeOil":
		if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
		{
			dialog.text = "Señor" + GetSexPhrase("", "ita") + ", tu deseo de comprar más resina ciertamente muestra confianza en nuestro negocio. Sin embargo, hay una complicación.\nCon volúmenes incrementados viene un mayor riesgo de atraer la atención de las autoridades de la isla, y controlar tales envíos requiere personas y medidas de seguridad, lo cual, admito, no es barato. Si estás dispuesto a añadir tres mil doblones al precio, como un pago único, contrataré personas de confianza que puedan proteger la carga y evitar filtraciones de información. Entonces nuestra ruta será más segura, y puedo suministrarte trescientas barricas de resina mensualmente. Para compensar tu inversión te ofreceré, como comprador al por mayor, un descuento del quince por ciento en todos los envíos futuros.";
			link.l1 = "¿Tres mil doblones para asegurar los envíos? Señor Sergio, no lo ocultaré, este precio parece increíble, ¡como si estuviera proponiendo una conspiración en el Escorial en lugar de simplemente asegurar la carga de resina!";
			link.l1.go = "UpgradeOil_1";
			notification("Skill Check Passed", SKILL_COMMERCE);
		}
		else
		{
			dialog.text = "Señor" + GetSexPhrase("", "ita") + ", aprecio tu interés, pero transacciones tan grandes requieren experiencia y precaución. Admitidamente, tu nivel en el comercio aún no es lo suficientemente alto para manejar tal volumen. Te aconsejo que adquieras un poco más de experiencia y vuelvas a mí cuando estés listo para más paridades. Entonces tal vez discutiremos el asunto a fondo.";
			link.l1 = "Bien. Volveremos a este asunto más tarde.";
			link.l1.go = "oil_trade_exit";
			notification("Skill Check Failed (80)", SKILL_COMMERCE);
		}
		break;

	case "UpgradeOil_1":
		dialog.text = "Señor" + GetSexPhrase("", "ita") + ", entiendo tu preocupación. Pero sabes que la seguridad nunca es barata, especialmente con mercancías tan raras. Además, no solo garantizo que no habrá filtraciones, sino que ofrezco un descuento que compensará tu inversión con el tiempo. ¿No es un compromiso razonable?";
		link.l1 = "Lo admito: en nuestro negocio, la fiabilidad y el secreto son costosos y el descuento hace que nuestro potencial trato sea algo más atractivo. Pero aún así, tres mil doblones es una suma excesiva. ¿Quizás podrías reducirla un poco?";
		link.l1.go = "UpgradeOil_2";
		break;

	case "UpgradeOil_2":
		dialog.text = "Lamento, pero las medias tintas son inaceptables en tales asuntos. O aseguramos una protección completa, o lo arriesgamos todo. La suma sigue siendo la misma, y solo de esta manera puedo garantizar fiabilidad y confidencialidad. No querrías que toda la flota real persiguiera primero a mí y luego a ti, ¿verdad?";
		if (PCharDublonsTotal() >= 3000)
		{
			link.l1 = "Muy bien, Señor Saldo, me ha convencido. La seguridad y la fiabilidad valen su precio. Tres mil doblones. Aquí tiene.";
			link.l1.go = "UpgradeOil_Agreed";
		}
		link.l2 = "Señor Saldo, me ha convencido de la necesidad de estas medidas. Sin embargo, tres mil doblones es una suma seria, y no la tengo en este momento. Tendré que esperar hasta reunir la cantidad requerida.";
		link.l2.go = "UpgradeOil_4";
		link.l3 = "¡Por tal cantidad de dinero, uno podría sobornar a toda una flota y a todos los soldados del continente, por no hablar de contratar guardias para un modesto cargamento de resina! Le pido disculpas, pero no puedo aceptar tal oferta. Dejemos todo como está, sin excesos ni gastos adicionales.";
		link.l3.go = "UpgradeOil_3";
		break;

	case "UpgradeOil_Agreed":
		dialog.text = "Bueno, señor, veo que nuestra confianza es mutua. Asegúrese de que el caso será manejado adecuadamente. Ahora, a los detalles: 300 barriles de aceite, como de costumbre, el 5 de cada mes, lo estarán esperando aquí en el Faro de Trinidad. Puede canjear todo el lote por 2550 doblones.";
		link.l1 = "Eso es genial, Señor Sergio. No me defraudes.";
		link.l1.go = "UpgradeOil_Agreed_1";
		RemoveDublonsFromPCharTotal(3000);
		AddQuestRecordInfo("Unique_Goods", "4_1");
		pchar.questTemp.UpgradeOil = true;
		pchar.questTemp.SergioOilBlock = true;
		DeleteAttribute(pchar, "questTemp.SergioOilPotom");
		break;

	case "UpgradeOil_Agreed_1":
		dialog.text = "No lo dudes, señor" + GetSexPhrase("", "ita") + ". Todo estará organizado al más alto nivel, y nuestro trabajo conjunto traerá beneficios.";
		link.l1 = "Nos vemos.";
		link.l1.go = "oil_trade_exit";
		break;

	case "UpgradeOil_3":
		DialogExit();
		pchar.questTemp.SergioOilBlock = true;
		NextDiag.CurrentNode = "oil_trade";
		break;

	case "UpgradeOil_4":
		dialog.text = "Ven cuando tengas la suma completa. Estaré encantado de hacer un nuevo trato contigo.";
		link.l1 = "De acuerdo.";
		link.l1.go = "oil_trade_exit";
		pchar.questTemp.SergioOilBlock = true;
		pchar.questTemp.SergioOilPotom = true;
		break;
		// <-- генератор смол

	case "Juan_abordage":
		dialog.text = "¿Quién diablos eres tú!?";
		link.l1 = "Me llamo " + GetFullName(pchar) + ", en cuanto a ti, Consumo, el diablo te espera, ¡y muy pronto tendrá tu alma!";
		link.l1.go = "Juan_abordage_1";
		break;

	case "Juan_abordage_1":
		if (CheckAttribute(pchar, "questTemp.Consumption.House"))
		{
			dialog.text = "¡Este barco va a estallar - ya hay una mecha ardiendo en la sala de pólvora, ¿por qué deberíamos morir ambos? Bajemos las espadas. Tendrás tiempo suficiente para salir, y yo saltaré del barco, Punta Galera está a tiro de piedra de aquí. ¡Si necesitas oro, llévatelo! Quinientos doblones, en efectivo sobre la mesa y te olvidas de mí, y yo me olvido de ti. ¿Trato hecho?";
			link.l1 = "¿Oro? No comencé todo esto por dinero, Juan, sino por matar a la escoria, y tú eres la mayor recompensa por sí mismo.";
			link.l1.go = "Juan_abordage_2";
			link.l2 = "¿Quinientos doblones? Te estás burlando de mí, Consumption. Creo que aquí tienes al menos el doble... Dame mil ahora mismo y puedes irte al infierno, de lo contrario...";
			link.l2.go = "Juan_abordage_3";
		}
		else
		{
			dialog.text = "La nave está a punto de volar, así que tendré buena compañía, ¿qué opinas?";
			link.l1 = "¡Hablas demasiado, Consumption, vamos al grano!";
			link.l1.go = "Juan_abordage_5";
		}
		break;

	case "Juan_abordage_2":
		dialog.text = "Podríamos haber tenido un acuerdo... ¡Eh, lo que sea!";
		link.l1 = "Llevaste a estas pobres personas de sus celdas, y no pudieron ni resistirse ni huir. Eres un cobarde, Consumption, y ahora morirás como un cobarde.";
		link.l1.go = "Juan_abordage_5";
		break;

	case "Juan_abordage_3":
		dialog.text = "Tienes buen ojo para los negocios, amigo... Aquí, esto es todo lo que tengo. No es mucho para una vida, ¿verdad?";
		link.l1 = "Tu vida no vale ni una bala, así que parece que es el negocio más rentable de mi vida. Ahora, lárgate.";
		link.l1.go = "Juan_abordage_4";
		TakeNItems(pchar, "gold_dublon", 1000);
		Log_Info("Has recibido 1000 doblones");
		PlaySound("interface\important_item.wav");
		ChangeCharacterComplexReputation(pchar, "nobility", -10);
		OfficersReaction("bad");
		pchar.questTemp.Consumption.TakeMoney = "true"; // атрибут для диалога
		break;

	case "Juan_abordage_4":
		DialogExit();
		chrDisableReloadToLocation = true;
		sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
		Lai_SetPlayerType(pchar);
		LAi_RemoveCheckMinHP(sld);
		LAi_SetImmortal(sld, true);
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "ConJuan_AfterFight_1", 10.0);
		break;

	case "Juan_abordage_5":
		dialog.text = "Es una lástima que no tengas tiempo para salvar a todos y matarme, ¿verdad? La mecha está ardiendo, y el tiempo pasa...";
		link.l1 = "¡Maldita sea! Tengo que sacar a la gente de aquí... ¡Lárgate, escoria, tarde o temprano obtendrás lo que mereces!";
		link.l1.go = "Juan_abordage_4";
		link.l2 = "Lo intentaré de todos modos...";
		link.l2.go = "Juan_abordage_6";
		ChangeCharacterComplexReputation(pchar, "nobility", 5);
		OfficersReaction("good");
		sld = GetCharacter(NPC_GenerateCharacter("ConAndjelo", "citiz_9", "man", "man", 5, SPAIN, -1, true, "quest"));
		sld.name = "Angelo";
		sld.lastname = "";
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, false);
		break;

	case "Juan_abordage_6":
		// LAi_SetCurHPMax(NPChar);
		// LAi_GetCharacterMaxEnergy(NPChar);
		QuestAboardCabinDialogExitWithBattle("ConJuan_AfterFight_2");
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		pchar.questTemp.Consumption.KillJuan = "true"; // атрибут для диалога
		break;

	case "Waitress":
		dialog.text = "Ah... Estoy sin palabras... ¡Qué pesadilla!";
		link.l1 = "Desgraciadamente, no pude hacer nada. Lo siento, muchacha. Adiós.";
		link.l1.go = "Waitress_1";
		break;

	case "Waitress_1":
		DialogExit();
		AddQuestRecord("Consumption", "16");
		AddQuestUserData("Consumption", "sSex", GetSexPhrase("", ""));
		Consumption_Close();
		break;

	case "Waitress_2":
		dialog.text = "¡Increíble! Tú... ¿realmente lo salvaste? No tengo idea de cómo agradecerte.";
		if (CheckAttribute(npchar, "quest.Consumption.sex"))
		{
			link.l1 = "Me lo puedo imaginar, belleza. Pero mi parte del trato ya está hecha - solo queda una pequeña cosa.";
			link.l1.go = "Waitress_3";
		}
		link.l2 = "El deber llamó y actué. Eso es todo.";
		link.l2.go = "Waitress_5";
		if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
			AddQuestRecord("Consumption", "18");
		else
			AddQuestRecord("Consumption", "17");
		break;

	case "Waitress_3":
		dialog.text = "¡Oh Dios! Tienes razón. Para él, como prometí... Sube a la habitación - no tenemos mucho tiempo.";
		link.l1 = "¡Apresurémonos, entonces!";
		link.l1.go = "Waitress_4";
		break;

	case "Waitress_4": // благодарность натурой
		DialogExit();
		LocatorReloadEnterDisable("PortSpein_tavern", "reload1_back", true);  // закрыть таверну
		LocatorReloadEnterDisable("PortSpein_tavern", "reload2_back", false); // открыть комнату
		bDisableFastReload = true;											  // закрыть переход
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "PortSpein_tavern_upstairs", "goto", "goto3", "ConsumptionSexWaitress", -1);
		pchar.questTemp.Consumption.Sex = "true";
		break;

	case "Waitress_sex":
		dialog.text = "¡Aquí estoy, mi valiente caballero! Y mira lo que he traído conmigo.";
		link.l1 = "Vaya vaya, estoy impresionado, ¡abramos ese vino de cereza! Luego abriremos algo más... Después de todo, es tu día de suerte... ¡Ja-ja!";
		link.l1.go = "Waitress_sex_1";
		break;

	case "Waitress_sex_1":
		DialogExit();
		DoQuestCheckDelay("PlaySex_1", 0.1);
		break;

	case "Waitress_5":
		if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
		{
			dialog.text = "¡Eres un verdadero caballero! ¡Caballero! Aquí, no lo tomes como un insulto, pero quiero que lo aceptes. Reuní este dinero para rescatar a Angelo, pero ahora no es importante. Por favor, no te niegues, ¡acéptalo!";
			link.l1 = "Bueno, recordaré tus ojos, señorita - son mucho más hermosos cuando brillan con lágrimas de felicidad y no de dolor. Acepto tu regalo. Adiós, y buena suerte a ti y a Angelo.";
			link.l1.go = "Waitress_6";
			AddMoneyToCharacter(pchar, 5000);
		}
		else
		{
			dialog.text = "¡Eres un verdadero caballero! ¡Caballero! ¡Se lo contaré a todos! ¡Siempre te recordaré!";
			link.l1 = "Bueno, y recordaré tus ojos, señorita - son mucho más hermosos cuando brillan con lágrimas de felicidad y no de dolor. Que siempre seas feliz. ¡Adiós!";
			link.l1.go = "Waitress_6";
		}
		break;

	case "Waitress_6":
		DialogExit();
		ChangeCharacterComplexReputation(pchar, "nobility", 3);
		Consumption_Close();
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
