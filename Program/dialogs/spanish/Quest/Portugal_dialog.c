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

	bool ok;
	int iTest;
	ref rColony;
	string sFrom_sea = "";

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "Error. Díganselo a los desarrolladores.";
		link.l1 = "Claro.";
		link.l1.go = "exit";
		break;

	case "Avendel_tavern":
		pchar.quest.Portugal_BeginOver.over = "yes";
		dialog.text = "¡Oh, otro valiente marinero! Conozco a los de tu calaña, ¡mi maldito ojo está afinado para ti, ja! ¿Pregúntame por qué?";
		link.l1 = "Te preguntaré sobre un asunto diferente, se trata de la deuda que tienes con la dueña del... eh, establecimiento. Ella me ha pedido que te recuerde sobre tu deuda, te sugiero que hagas algo al respecto, de lo contrario, tendrá que acudir a los guardias para hacer lo mismo mañana.";
		link.l1.go = "Avendel_tavern_1";
		DelLandQuestMark(npchar);
		break;

	case "Avendel_tavern_1":
		dialog.text = "Local está... ¡oh, maldición! ¡Johanna, no puede hacerme esto! ¿Estás seguro? ¿De verdad ha dicho que me mandaría a los calabozos por unas malditas monedas?";
		link.l1 = "Absolutamente. Eso es lo que ella ha dicho. Supongo que mi misión ha terminado, adiós, señor Avendell.";
		link.l1.go = "Avendel_tavern_2";
		break;

	case "Avendel_tavern_2":
		dialog.text = "¡Espera! ¡Por favor, espera! Pareces un capitán experimentado. Seguro que tienes algunas monedas, estoy arruinado, solo el buen viejo cantinero llena mi copa a crédito por nuestra vieja amistad. ¡Escucha mi pro... propuesta! Tú pagas mi deuda y yo te doy una tajada. Hay un negocio... un negocio muy lucrativo, ¡maldita sea y que me lleve el diablo! Te juro por mi maldito ancla, solo confía en mí, capitán, ¡como quiera que te llames! Solo redime una pequeña deuda, diez mil pesos y tendrás la oportunidad de ganar suficientes monedas para comprar todos los burdeles del Nuevo-maldito-Mundo. ¿Qué dices? Tú me das, yo te doy, como hacen las personas honestas...";
		link.l1 = "Un tipo andrajoso que promete tesoros. Líbrenme de esa mierda, no hago caridad para gente como tú. Encuentra el dinero o vivirás en las casamatas del fuerte muy pronto. ¡Adiós!";
		link.l1.go = "Avendel_tavern_3";
		link.l2 = "¿Una tajada? ¿Y por qué debería confiar en la palabra de un idiota borracho? ¿Por promesas imaginarias?";
		link.l2.go = "Avendel_tavern_4";
		break;

	case "Avendel_tavern_3":
		DialogExit();
		npchar.lifeday = 0;
		LAi_CharacterDisableDialog(npchar);
		pchar.questTemp.Portugal = "end";
		break;

	case "Avendel_tavern_4":
		dialog.text = "¡Escúchame, capitán! ¡Hic, dispárame si miento! ¡Pero te digo la verdad! ¡Piensa en eso, si me pillas mintiendo, entonces me cortarás las tripas con esa belleza que llevas en el cinturón! ¡Maldita sea, su empuñadura cuesta cinco veces más que mi miserable deuda! ¿Entonces qué dices? ¡No tienes nada que perder!";
		link.l1 = "He tenido suficiente de tus discursos. Adiós.";
		link.l1.go = "Avendel_tavern_3";
		link.l2 = "Está bien, Hugo... Me arriesgaré a creer en esas tonterías que dices. Pero recuerda que tendrás que persuadirme y asegurarte de que mi dinero no fue malgastado en vano cuando regrese, de lo contrario, será tu pellejo el que estará en juego.";
		link.l2.go = "Avendel_tavern_5";
		break;

	case "Avendel_tavern_5":
		dialog.text = "¡No se necesitan amenazas, lo entiendo. Le doy mi palabra, capitán! ¡Seremos ricos! ¡Regrese cuando esta maldita deuda esté pagada y hablaremos! ¡Sí, lo haremos! ¡No se quedará al margen!";
		link.l1 = "Está bien, borraré tu deuda, pero más te vale rezar, Hugo Avendell, para que tu 'propuesta' me satisfaga.";
		link.l1.go = "Avendel_tavern_6";
		break;

	case "Avendel_tavern_6":
		DialogExit();
		pchar.questTemp.Portugal = "HostressMoney";
		Nextdiag.Currentnode = "Avendel_repeat";
		AddLandQuestMark(characterFromId("Marigo_Hostess"), "questmarkmain");
		break;

	case "Avendel_repeat":
		dialog.text = "Capitán, regresa tan rápido como puedas - este negocio podría escaparse.";
		link.l1 = "Sí, sí, pronto pagaré tu deuda.";
		link.l1.go = "exit";
		Nextdiag.TempNode = "Avendel_repeat";
		break;

	case "Avendel_tavern_7":
		pchar.quest.Portugal_BeginOver.over = "yes";
		dialog.text = "¡Has vuelto, capitán! ¡Por la tormenta y maldito trueno de Dios, me alegra tanto verte! ¿Qué hay de mi deuda?";
		link.l1 = "Lo he manejado, ahora es tu turno, Hugo. ¡Cuéntame tu historia e intenta hacerla un poco creíble!";
		link.l1.go = "Avendel_tavern_8";
		DelLandQuestMark(npchar);
		break;

	case "Avendel_tavern_8":
		dialog.text = "¡No te preocupes, capitán! ¿Sabías que soy un cazarrecompensas? O... solía serlo. No tuve la suficiente suerte, supongo. Quizás el mismo Diablo con todas sus hazañas no era tan perdedor como yo. He perdido todo en mi último trabajo... La tripulación se escapó y tuve que vender mi barco por las deudas...";
		link.l1 = "Ya estoy informado sobre tu heroico pasado. Directo al grano, Hugo, no retes mi paciencia.";
		link.l1.go = "Avendel_tavern_9";
		break;

	case "Avendel_tavern_9":
		dialog.text = "Sí, sí, capitán..." + GetFullName(pchar) + ", ¿no es cierto? Yo también sé algo sobre ti. Pero maldito sea yo si es importante. ¿Has oído el nombre de Bartolomeo el Portugués?";
		link.l1 = "Bart el Portugués? Por supuesto que he oído hablar de él. Todos lo han hecho. Es un pirata, un carnicero y una escoria, hasta donde sé. ¿Y cuál es su papel en tu historia?";
		link.l1.go = "Avendel_tavern_10";
		break;

	case "Avendel_tavern_10":
		dialog.text = "¡Él está tomando una maldita parte principal en esto! Lo he estado rastreando durante el último año y medio. La Compañía Holandesa ha puesto un gran precio por su cabeza. Pero he fallado, y lo he perdido todo. Y la Compañía ha triplicado el precio recientemente por él vivo y solo vivo, ¡maldito sea!";
		link.l1 = "Por una buena razón, no es pan comido capturarlo vivo. De todos modos, ¿por qué debería preocuparme por eso, Hugo? ¡Parece que estás tratando de joderme!";
		link.l1.go = "Avendel_tavern_11";
		break;

	case "Avendel_tavern_11":
		dialog.text = "¡Ni siquiera iba a hacerlo, capitán! Sabes, el doctor Peter Van Stal, un hombre muy amable, me ha dado una poción para curar mis dolores de cabeza. Así que, el doctor no estuvo en su casa por casi tres días y...";
		link.l1 = "¡Hugo, mi paciencia casi se ha agotado! Le he prometido a la dama que no te apuñalaré con mi espada, ¡pero mis puños servirán igual de bien! ¡Te juro que ninguna poción podrá curar tu cabeza mañana!";
		link.l1.go = "Avendel_tavern_12";
		break;

	case "Avendel_tavern_12":
		dialog.text = "¡Espera, capitán! ¡Por favor! Escúchame, he visto a unos tipos cerca de la casa del médico y los he reconocido. ¡Son del 'Albatros', una fragata de los malditos portugueses! ¡Y uno de ellos estaba hablando sobre la salud de su capitán! Mira ahora, " + pchar.name + ", ¡Bartolomeo está aquí, en esta ciudad! Justo bajo nuestras narices, o está herido o enfermo, ¡por eso necesitan a un maldito médico!\n¡Dudo que el portugués haya traído a toda su tripulación aquí, pero no puedo empezar este embrollo solo! ¡Seguramente, maldita sea, sabes cómo manejar tu espada maldita! ¡Lleva contigo a unos tipos duros y encontraremos a la rata! ¡Luego lo capturamos y lo entregamos a las autoridades!\n¡Y dos mil buenos doblones de oro estarán en nuestros bolsillos!";
		link.l1 = "No, Hugo, he tenido suficiente de tu charla. No participaré en este lío, aunque tengas razón. Adiós.";
		link.l1.go = "Avendel_tavern_3";
		link.l2 = "Mm, interesante. ¿Sabes dónde se está escondiendo? Si funciona, podemos discutir las participaciones, pero si lo que me estás diciendo es la verdad, ¡entonces debemos apresurarnos ahora!";
		link.l2.go = "Avendel_tavern_13";
		break;

	case "Avendel_tavern_13":
		dialog.text = "No, no sé dónde está, capitán. Estaba demasiado asustado para seguir a esos muchachos. Si el Tuerto me hubiera visto... ¡fuh! Pero juntos, más tus muchachos, seremos capaces de peinar toda esta ciudad, llama a tus hombres y ¡empecemos! ¡Maldita sea, los doblones holandeses nos están esperando! ¡Una maldita oportunidad como esta solo ocurre una vez en la vida, muérdeme un arenque!";
		link.l1 = "Un entusiasmo encomiable... Espero que puedas alejarte de la mesa, un 'gran' cazarrecompensas. Voy a buscar inmediatamente y puedes seguirme si quieres, solo no me molestes demasiado.";
		link.l1.go = "Avendel_tavern_14";
		break;

	case "Avendel_tavern_14":
		DialogExit();
		SetFunctionTimerCondition("Portugal_DoctorOver", 0, 0, 2, false);
		pchar.quest.Portugal_Guard.win_condition.l1 = "location";
		pchar.quest.Portugal_Guard.win_condition.l1.location = "Marigo_houseF1";
		pchar.quest.Portugal_Guard.function = "CreatePortugalGuard";
		AddQuestRecord("Portugal", "1");
		NextDiag.Currentnode = "Avendel_tavern_repeat";
		QuestPointerToLoc("marigo_town", "reload", "houseF1");
		break;

	case "Avendel_tavern_repeat":
		dialog.text = "Sí, sí, capitán, solo déjame terminar mi bebida y me uniré a ti... ¿Dónde empezaremos?";
		link.l1 = "¿Dónde?!... Voy, contigo o sin ti.";
		link.l1.go = "exit";
		Nextdiag.TempNode = "Avendel_tavern_repeat";
		break;

	case "Portugal_guard":
		dialog.text = "¡Casa equivocada, amigo. ¡Piérdete, ahora!";
		link.l1 = "Mm. Y creo que es la casa correcta...";
		link.l1.go = "Portugal_guard_1";
		break;

	case "Portugal_guard_1":
		dialog.text = "Bueno, te lo advertí...";
		link.l1 = "...";
		link.l1.go = "Portugal_guard_2";
		break;

	case "Portugal_guard_2":
		DialogExit();
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
		for (i = 1; i <= 3; i++)
		{
			sld = characterFromId("PortugalGuard_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
		AddDialogExitQuest("MainHeroFightModeOn");
		pchar.quest.Portugal_Doctor.win_condition.l1 = "location";
		pchar.quest.Portugal_Doctor.win_condition.l1.location = "Marigo_RoomHouseF1";
		pchar.quest.Portugal_Doctor.function = "CreatePortugalDoctor";
		break;

	case "Bart_lay":
		dialog.text = "¡A toda vela, volando alto, hijos de... preparen los cañones!... ah-ja-ja... oh mi belleza...";
		link.l1 = "Mm, tiene suerte de estar vivo...";
		link.l1.go = "exit";
		Nextdiag.TempNode = "Bart_lay";
		break;

	case "Portugal_doctor":
		pchar.quest.Portugal_DoctorOver.over = "yes";
		dialog.text = "¡Dios mío, ¿quién eres tú? ¡Por favor, baja tu arma! ¡Hay un hombre enfermo aquí!";
		link.l1 = "Este 'enfermo' tuyo ha matado a más personas de las que has visto en tu vida, doctor. ¡Aléjate!";
		link.l1.go = "Portugal_doctor_1";
		break;

	case "Portugal_doctor_1":
		dialog.text = "¡Él es mi paciente y ni siquiera puede ponerse de pie! ¿No puedes ver eso? ¡Por favor, baja tu espada! ¡Te lo ruego!";
		link.l1 = "¿Y qué le pasa, maldita sea!?";
		link.l1.go = "Portugal_doctor_2";
		break;

	case "Portugal_doctor_2":
		dialog.text = "Supongo que todo es por su herida, un golpe infligido por un arma envenenada de un caribe... ¡y los hombres que lo han traído aquí dijeron que si él muere, yo moriré! ¡Pero estoy haciendo todo lo que puedo, diles eso!";
		link.l1 = "No te preocupes por esos hombres, doctor. Mis muchachos vigilarán tu casa y yo tengo que ir a ver al gobernador. Supongo que se meará de alegría. No salgas de aquí hasta que vuelva, doc.";
		link.l1.go = "Portugal_doctor_3";
		break;

	case "Portugal_doctor_3":
		chrDisableReloadToLocation = false;
		DialogExit();
		LAi_SetStayType(npchar);
		Nextdiag.Currentnode = "Doctor_repeat";
		pchar.quest.Avendel_House.win_condition.l1 = "location";
		pchar.quest.Avendel_House.win_condition.l1.location = "Marigo_houseF1";
		pchar.quest.Avendel_House.function = "AvendelInHouse";
		break;

	case "Doctor_repeat":
		dialog.text = "No me iré, no te preocupes por eso. Entreguémoslo ya a las autoridades y acabemos con esta pesadilla.";
		link.l1 = "Por supuesto, estoy en camino.";
		link.l1.go = "exit";
		Nextdiag.TempNode = "Doctor_repeat";
		break;

	case "Avendel_house":
		dialog.text = "¡Lo hicimos, capitán! ¡Lo hemos encontrado y pronto seremos ricos, tal como te dije! ¿Cuál es nuestro plan?";
		link.l1 = "Eso espero, Hugo. De todos modos, todavía no ha terminado. ¿Supongo que tengo que ir al gobernador y discutir nuestra recompensa?";
		link.l1.go = "Avendel_house_1";
		break;

	case "Avendel_house_1":
		dialog.text = "¡No, no, Capitán! ¡No vayas a ese maldito Thomas! Créeme, este canalla nos quitará al prisionero y, si tenemos suerte, nos invitará a una taza de café. Su Excelencia es un tipo sospechoso, así que si quieres obtener una recompensa completa, tienes que navegar a Curazao. ¡De lo contrario, los portugueses serán llevados al fuerte y nos echarán como mendigos!";
		link.l1 = "Bueno, si realmente estás seguro de eso...";
		link.l1.go = "Avendel_house_2";
		break;

	case "Avendel_house_2":
		dialog.text = "¡Lo estoy, capitán, maldita sea, claro que lo estoy! Pero recuerda que los hombres de Bartolomeo deben estar en algún lugar de la ciudad y tampoco queremos atraer la atención de la guarnición, ¡eso es seguro, maldita sea! Tenemos que decidir cómo llevar a los portugueses a tu barco y cómo hacerlo de manera desapercibida.";
		link.l1 = "Bien... No quiero pelear con su fragata de camino a Willemstad. ¿Tienes alguna idea?";
		link.l1.go = "Avendel_house_3";
		break;

	case "Avendel_house_3":
		dialog.text = "Sí, tengo una. Primero necesitamos encontrarle un traje más noble, luego lo arrastramos por la entrada trasera como un oficial borracho. ¡Nadie sospechará que es un maldito pirata, confía en mí!";
		link.l1 = "Hmm, no estoy seguro de esto, pero no tenemos un mejor plan todavía. Intentaré conseguir un bonito paño para nuestro pasajero. Quédate aquí y vigila a Bart y al doc.";
		link.l1.go = "Avendel_house_4";
		break;

	case "Avendel_house_4":
		DialogExit();
		AddQuestRecord("Portugal", "3");
		LAi_ActorRunToLocation(npchar, "reload", "houseF1", "Marigo_houseF1", "goto", "goto2", "", -1);
		pchar.quest.Portugal_Cloves.win_condition.l1 = "Timer";
		pchar.quest.Portugal_Cloves.win_condition.l1.date.hour = sti(GetTime());
		pchar.quest.Portugal_Cloves.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.Portugal_Cloves.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.Portugal_Cloves.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.Portugal_Cloves.function = "PortugalClovesOver"; // 1 сутки
		pchar.questTemp.Portugal = "Findcloves";
		LAi_SetStayType(npchar);
		npchar.dialog.currentnode = "Avendel_house_guard";
		AddLandQuestMark(characterFromId("Marigo_trader"), "questmarkmain");
		QuestPointerToLoc("marigo_town", "reload", "reload6_back");
		break;

	case "Avendel_house_guard":
		dialog.text = "No te preocupes , capitán. El portugués está bajo mi confiable guardia, je-je...";
		link.l1 = "Me gustaría creer que...";
		link.l1.go = "exit";
		Nextdiag.TempNode = "Avendel_house_guard";
		break;

	case "Portugal_doctor_4":
		dialog.text = "No veo a los soldados, " + GetAddress_Form(NPChar) + ". ¿Dónde están? Dijiste que lo arrestarían tan pronto como les contaras sobre la situación. Entonces, ¿por qué no están aquí los soldados?";
		link.l1 = "No habrá soldados, señor Van Stal. Voy a hacer el trabajo yo mismo y tengo que llevar a su paciente a Curazao lo antes posible.";
		link.l1.go = "Portugal_doctor_5";
		DelLandQuestMark(npchar);
		break;

	case "Portugal_doctor_5":
		dialog.text = "Capitán, escuche, no puedo manejar su herida, todo lo que puedo hacer es bajar un poco la fiebre. Está mayormente inconsciente y delirante, no hay duda de que morirá incluso sin ninguna interferencia y el vaivén del mar lo matará en unos días. Le daré algunas mezclas que ayudarán...";
		link.l1 = "No, doc, tú navegas con nosotros. Primero, soy un inútil en medicina y segundo, dudo que quieras quedarte aquí y explicar a los hombres del portugués adónde ha ido su capitán.";
		link.l1.go = "Portugal_doctor_6";
		break;

	case "Portugal_doctor_6":
		dialog.text = "...Sí, supongo que tienes razón. Pero sabe que este pirata es muy resistente, he visto a personas con solo pequeños rasguños hechos por armas indias y todos murieron en menos de tres días. Y según sus 'amigos', ¡ya lleva una semana en este estado! Sin embargo, afirmo que sobrevivirá por un corto período de tiempo en un barco en mar abierto. ¡Tres días, no más!\nEso es todo el tiempo que tenemos.";
		link.l1 = "Ni siquiera el ave llegará a Curazao en tres días. ¡Pero creo que sé lo que puedo hacer! Hay un... amigo mío, vive en St. John's, Antigua. Sabe cómo curar a la gente de heridas mortales. Él es la única persona que puede ayudarnos ahora. Nuestro objetivo es simple: llegar allí antes de que el portugués muera. Prepara tus cosas, doctor, zarpamos de inmediato y tu paciente será trasladado enseguida.";
		link.l1.go = "Portugal_doctor_7";
		break;

	case "Portugal_doctor_7":
		DialogExit();
		AddQuestRecord("Portugal", "5");
		pchar.quest.Portugal_Cloves.over = "yes";
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		AddPassenger(pchar, npchar, false);
		SetCharacterRemovable(npchar, false);
		sld = characterFromId("Avendel");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, false);
		RemoveItems(PChar, "suit_1", 1);
		sld = characterFromId("Portugal");
		sld.model = "Port_B"; // меняем модель
		ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto6");
		SetFunctionTimerCondition("Portugal_ToAntiguaOver", 0, 0, 4, false);
		pchar.questTemp.Portugal = "ToAntigua";
		QuestPointerDelLoc("marigo_town", "reload", "houseF1");
		// временно для тестов откроем комнату Джино, потом убрать
		LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);
		break;

	case "Avendel_goodbye":
		dialog.text = "Qué lástima, capitán. Hemos perdido, y no veremos ese maldito oro. Adiós.";
		link.l1 = "Adiós, Hugo.";
		link.l1.go = "Avendel_goodbye_1";
		break;

	case "Avendel_goodbye_1":
		DialogExit();
		chrDisableReloadToLocation = false; // открыть локацию
		npchar.lifeday = 0;
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		break;

	case "Portugal_doctor_9":
		dialog.text = "...";
		link.l1 = "Doc, prepara a tu paciente para el desembarco. El bote está listo. ¡Apresúrate!";
		link.l1.go = "Portugal_doctor_10";
		DelLandQuestMark(npchar);
		break;

	case "Portugal_doctor_10":
		dialog.text = "Estoy en camino, " + GetAddress_Form(NPChar) + ".";
		link.l1 = "...";
		link.l1.go = "Portugal_doctor_11";
		break;

	case "Portugal_doctor_11":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Portugal_PerenesliVDom1", -1);
		sld = characterFromId("Portugal");
		ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "quest", "quest1");
		sld = characterFromId("Jino");
		ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "goto", "goto3");
		pchar.quest.Portugal_ToAntiguaOver.over = "yes"; // снять таймер
		pchar.questTemp.Portugal = "TreatmentStart";
		pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
		pchar.quest.Portugal_Ill.win_condition.l1.date.hour = sti(GetTime());
		pchar.quest.Portugal_Ill.win_condition.l1.date.day = GetAddingDataDay(0, 0, 7);
		pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
		pchar.quest.Portugal_Ill.win_condition.l1.date.year = GetAddingDataYear(0, 0, 7);
		pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver"; // не придёт через 7 дня - Португальцу капут
		break;

	case "Avendel_Room":
		dialog.text = "¡Esta casa apesta a putas mezclas! ¡Sería una gran sorpresa si el portugués muere aquí, incluso respirar este hedor puede curar cualquier enfermedad!\n¡Y la tripulación del hombre puede encontrarnos fácilmente gracias a la pestilencia!";
		link.l1 = "Hugo, ahórrame tus bromas. He dejado a pocos hombres en las calles para vigilar la casa, pero un guardia más no será innecesario para nuestro invitado. Vigílalo y trata de dejar de maldecir, o Gino te hará beber alguna mezcla suya, estoy seguro de que puede curar eso.";
		link.l1.go = "Avendel_Room_1";
		break;

	case "Avendel_Room_1":
		dialog.text = "¡No te preocupes, capitán! Vigilaré nuestro dinero de la manera más vigilante, ¡no se escapará incluso si estuviera sano! Y te lo suplico, por favor, ¡no más brebajes!";
		link.l1 = "Ves, puedes ser amable cuando quieres. Mantente alerta, tengo que irme.";
		link.l1.go = "exit";
		chrDisableReloadToLocation = false;
		break;

	case "Avendel_Room_2":
		dialog.text = "¿Ya te vas, capitán? ¡Genial! ¡Es hora! Vi a unos pocos malditos... tipos sospechosos en la calle. No parecen hombres portugueses, aunque estaban buscando algo, tenemos que tener cuidado, ¡capitán!";
		link.l1 = "Bien, gracias por tu advertencia, Hugo. Vamos al barco.";
		link.l1.go = "Avendel_Room_3";
		break;

	case "Avendel_Room_3":
		DialogExit();
		chrDisableReloadToLocation = false;
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		// ставим Португальца
		sld = characterFromId("Portugal");
		ChangeCharacterAddressGroup(sld, "SentJons_HouseF3", "goto", "goto1");
		LAi_SetActorType(sld);
		LAi_ActorFollowEverywhere(sld, "", -1);
		break;

	case "Portugal_hunter":
		dialog.text = "¡Capitán, hemos estado esperando esta reunión por demasiado tiempo! ¿Y quién es ese contigo? ¡Bartolomeo el Portugués en persona, ja, parece que el Intrépido Pierre tenía razón - es él! Aléjate, capitán, vamos a llevárnoslo y nadie saldrá herido.";
		link.l1 = "Lo siento, señor, pero ¿quién demonios eres? ¡Quítate de mi camino o ninguno de ustedes verá el mañana!";
		link.l1.go = "Portugal_hunter_1";
		break;

	case "Portugal_hunter_1":
		dialog.text = "Oh, ¡qué tipo tan amenazante, solo mírenlo muchachos! ¡Ja-ja-ja! Escucha aquí, cachorro, ¡no te interpongas entre Leo Cord y su dinero! Hemos estado siguiendo al portugués por casi medio año y ahora finalmente lo tenemos. Así que baja ese mondadientes tuyo y piérdete mientras aún respiras. No somos tan codiciosos, un hombre muerto servirá igual de bien, ¡ja-ja!";
		link.l1 = "¡Basta. A bailar, caballeros!";
		link.l1.go = "Portugal_hunter_2";
		break;

	case "Portugal_hunter_2":
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешим драться
		DialogExit();
		sld = characterFromId("Portugal");
		LAi_group_Register("Bart_Portugal");
		LAi_group_SetRelation("Bart_Portugal", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
		LAi_group_MoveCharacter(sld, "Bart_Portugal");
		for (i = 1; i <= 5; i++)
		{
			sld = characterFromId("PortugalHunter_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "PortugalHunterDied");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "Avendel_street":
		sld = characterFromId("Portugal");
		if (LAi_GetCharacterHP(sld) > 0)
		{
			dialog.text = "¡Sabía que algo andaba mal aquí! ¡Bien hecho, capitán! Pero es hora de irse, ese maldito Leo Cord tiene muchos bandidos por aquí y un buen barco. ¡Tenemos que alejarnos de esta isla!";
			link.l1 = "Buen punto, Hugo, y estoy muy contento de que ninguna bala se disparara hacia el agujero donde te escondías.";
			link.l1.go = "Avendel_street_1";
		}
		else
		{
			dialog.text = "Qué lástima, capitán. Hemos perdido y no veremos ese maldito oro. Adiós.";
			link.l1 = "Adiós, Hugo.";
			link.l1.go = "Avendel_goodbye_1";
			sld = characterFromId("PortugalDoctor");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			AddQuestRecord("Portugal", "35");
			CloseQuestHeader("Portugal");
			pchar.questTemp.Portugal = "end";
		}
		break;

	case "Avendel_street_1":
		dialog.text = "¡Yo... yo estaba asegurando nuestra retaguardia, capitán! Estabas manejándote bien sin mí, pero ¿y si alguien nos hubiera atacado desde el otro lado de la calle? No tendrías tiempo para correr al barco.";
		link.l1 = "¿Quizás por eso no tuviste éxito en tu profesión? ¡Qué más da, basta de charla, tenemos que llegar al barco! ¡El tiempo se acaba!";
		link.l1.go = "Avendel_street_2";
		break;

	case "Avendel_street_2":
		DialogExit();
		LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
		AddQuestRecord("Portugal", "8");
		pchar.quest.Portugal_seahunter.win_condition.l1 = "location";
		pchar.quest.Portugal_seahunter.win_condition.l1.location = "Antigua";
		pchar.quest.Portugal_seahunter.function = "PortugalSeaHunter";
		pchar.quest.Portugal_martinique.win_condition.l1 = "location";
		pchar.quest.Portugal_martinique.win_condition.l1.location = "FortFrance_town";
		pchar.quest.Portugal_martinique.function = "PortugalOnMartinique";
		break;

	case "Portugal_doctor_12":
		dialog.text = "Capitán, el portugués se siente muy mal, ¡debemos detenernos!";
		link.l1 = "Por eso estamos aquí, mynheer van Stal, nuestro viaje casi ha terminado. Alquilaré una habitación en la taberna y nuestro prisionero se quedará allí por unos días.";
		link.l1.go = "Portugal_doctor_13";
		break;

	case "Portugal_doctor_13":
		DialogExit();
		LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 5);
		break;

	case "Portugal_doctor_14":
		dialog.text = "Mynheer capitán, yo cuidaré del portugués, necesita descansar completamente.";
		link.l1 = "Lo tengo, doc, está bien. Maldita sea, ¿por cuánto tiempo debo cuidar de este pirata? ¡Eso es malo para él, eso no es lo que necesita! Parece que me contrataron como niñera y... agh, perdóneme, doctor, es simplemente demasiado... Nos vemos más tarde.";
		link.l1.go = "Portugal_doctor_15";
		break;

	case "Portugal_doctor_15":
		DialogExit();
		AddQuestRecord("Portugal", "15");
		pchar.quest.Portugal_patrol.win_condition.l1 = "location";
		pchar.quest.Portugal_patrol.win_condition.l1.location = "FortFrance_town";
		pchar.quest.Portugal_patrol.function = "CreateFrancePatrol";
		break;

	case "Portugal_patrol":
		dialog.text = "Monsieur, ¿es usted el capitán " + GetFullName(pchar) + ", cuyo barco acaba de llegar a nuestro puerto hoy?";
		link.l1 = "Eres correcto, ¿cómo puedo ayudarte?";
		link.l1.go = "Portugal_patrol_1";
		break;

	case "Portugal_patrol_1":
		dialog.text = "Su Excelencia Jacques Dille du Parquet, el gobernador de nuestra colonia, le está esperando. ¡El asunto es urgente!";
		link.l1 = "Está bien, monsieur, visitaré a su Excelencia hoy.";
		link.l1.go = "Portugal_patrol_2";
		break;

	case "Portugal_patrol_2":
		DialogExit();
		chrDisableReloadToLocation = false; // открыть локацию
		pchar.questTemp.Portugal = "MartiniqueGovernor";
		LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
		AddQuestRecord("Portugal", "9");
		break;

	case "Avendel_seapatrol":
		dialog.text = "Hemos llegado a Martinica, capitán! Nuestro dinero no está tan lejos ahora...";
		link.l1 = "Solo si los portugueses vivirán hasta que lleguemos a Willemstad. Hugo, tengo que ir al barco, así que tendrás que vigilar al doctor y a su paciente.";
		link.l1.go = "Avendel_seapatrol_1";
		break;

	case "Avendel_seapatrol_1":
		dialog.text = "¿Ir al barco? ¿Por qué? ¿Me prestarás algunos de tus hombres para ayudarme? ¿Qué pasa si algo ocurre mientras estás fuera?";
		link.l1 = "Lo siento, pero no. Dudo que algo pueda amenazarte aquí. La guarnición está alerta y hay más soldados en las calles de lo habitual, así que si algo sale mal, llámalos. Han visto un gran barco no muy lejos de esta isla, uno pirata, quizás. Y Su Excelencia el gobernador me ha pedido fortificar la isla patrullando con mi barco.";
		link.l1.go = "Avendel_seapatrol_2";
		break;

	case "Avendel_seapatrol_2":
		dialog.text = "¿Un barco? ¿Pirata? ¡Podría ser el Albatros! ¡O algún colega de nuestro viejo amigo Leo Cord!";
		link.l1 = "O quizás es solo un barco pirata ordinario. No obstante, Hugo, si este navío está aquí por nuestras cabezas, entonces será mejor que la enfrente con la patrulla a mi lado y por el oro del gobernador. Es mucho mejor que vigilar nuestras espaldas durante el resto del viaje. Si esta alarma es falsa, sin embargo, entonces simplemente me librará de sentar mi trasero en la taberna por unos días.";
		link.l1.go = "Avendel_seapatrol_3";
		break;

	case "Avendel_seapatrol_3":
		dialog.text = "Piénsalo, capitán, ¿es sensato dejar al mal... al portugués desprotegido mientras su fragata podría estar navegando por ahí? ¡Estás arriesgando nuestra recompensa al aceptar la tarifa del gobernador!";
		link.l1 = "¡Basta de hablar, Hugo Avendell! ¡Soy el capitán aquí y la decisión final es mía! Así que haz lo que te ordeno. Ve a la taberna y vigila al doctor y al portugués hasta que regrese.";
		link.l1.go = "Avendel_seapatrol_4";
		break;

	case "Avendel_seapatrol_4":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
		chrDisableReloadToLocation = false;									// открыть локацию
		LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", true); // закрыть таверну
		break;

	case "Avendel_seapatrol_5":
		dialog.text = "¡Has vuelto, capitán, por fin! Me temo que tengo malas noticias para ti: ¡el portugués se ha ido y también el médico!";
		link.l1 = "¿Cómo?! ¿Y qué estabas haciendo entonces, cabeza hueca?!";
		link.l1.go = "Avendel_seapatrol_6";
		break;

	case "Avendel_seapatrol_6":
		dialog.text = "Puedo apostar que ese barco era el 'Albatros'. He visto a los portugueses, entraron en la taberna y yo... yo huí. Lo siento, pero encontrarme con el Perro Tuerto era demasiado incluso por tanto dinero.";
		link.l1 = "¡Mierda! ¿Me dices al menos qué pasó en la taberna?";
		link.l1.go = "Avendel_seapatrol_7";
		break;

	case "Avendel_seapatrol_7":
		dialog.text = "Te dije que no vi nada. Me escapé por la cocina tan pronto como vi a Franz Garcke y sus hombres... ¡Estaba demasiado cerca! Sucedió ayer por la tarde y no sabía cómo avisarte...";
		link.l1 = "Sí, eres un hombre muy valiente y lleno de recursos... Bien, te daremos una oportunidad más, vamos a encontrarlos. He estado protegiendo a este canalla durante demasiado tiempo y ahora lo considero como mi propiedad. Todavía tenemos algo de tiempo para atraparlos, así que empecemos por la taberna, tal vez alguien haya visto más que tus talones al correr. ¡Ve, prepárate!";
		link.l1.go = "Avendel_seapatrol_8";
		break;

	case "Avendel_seapatrol_8":
		DialogExit();
		bQuestDisableMapEnter = false;				   // открыть карту
		DeleteAttribute(pchar, "GenQuest.CannotWait"); // можно мотать время
		chrDisableReloadToLocation = false;
		LAi_ActorFollowEverywhere(npchar, "", -1);
		SetFunctionTimerCondition("MartiniquePortugalOver", 0, 0, 2, false); // таймер
		sld = characterFromId("PortugalDoctor");
		sld.lifeday = 0; // убираем доктора
		RemovePassenger(Pchar, sld);
		sld = characterFromId("Portugal");
		ChangeCharacterAddressGroup(sld, "none", "", "");					  // Португальца спрячем
		LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", true); // комнату закроем
		AddQuestRecord("Portugal", "12");
		break;

	case "Avendel_seapatrol_9":
		dialog.text = "¿Lo ha escuchado, capitán? Hablaba del Perro Tuerto, le he contado sobre él recientemente. Y el castellano ceceante es Hernando Vasquez, el maldito Don - el carnicero de Vera Cruz, ¡no lo he visto!";
		link.l1 = "Relájate, Hugo. Estoy seguro de que Bartholomeo todavía está en la isla, podría haberse mejorado, pero aún está demasiado débil. ¡Y creo que sé dónde encontrarlo! Los atraparemos, no me alejaré de mi recompensa. Si no eres un cobarde, entonces sígueme, esto aún no ha terminado.";
		link.l1.go = "Avendel_seapatrol_10";
		break;

	case "Avendel_seapatrol_10":
		DialogExit();
		bDisableFastReload = false;						// открыть быстрый переход
		pchar.questTemp.Portugal = "PortugalLeFransua"; // в Ле Франсуа
		AddQuestRecord("Portugal", "13");
		LAi_LocationDisableOfficersGen("LeFransua_tavern", true); // офицеров не пускать
		break;

	case "LeFransua_pirate":
		dialog.text = "Preguntas demasiadas cosas, capitán... Espera, ¿no eres tú ese tipo astuto de Philipsburg? Has estado huyendo de nosotros por demasiado tiempo y ahora mira - aquí estás...";
		link.l1 = "¡Qué lástima por ti, escoria!";
		link.l1.go = "LeFransua_pirate_1";
		break;

	case "LeFransua_pirate_1":
		DialogExit();
		pchar.quest.MartiniquePortugalOver.over = "yes"; // снять таймер
		chrDisableReloadToLocation = true;
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		for (i = 1; i <= 3; i++)
		{
			sld = characterFromId("LeFransuaPirate_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "LeFransuaAfterFight");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "FranzGarke":
		dialog.text = "... tú, miserable mierda de cangrejo, nos lo dirás todo, puedes confiar en mí para eso, ¡maldita rata! Luego serás colgado en el vergajo en lugar de en el juanete... ¿Y quién diablos eres tú? ¡Malditos simios, no se puede confiar en ellos! Siempre tengo que hacerlo todo yo mismo...";
		link.l1 = "¿Os estoy molestando, caballeros?";
		link.l1.go = "FranzGarke_1";
		break;

	case "FranzGarke_1":
		DialogExit();
		chrDisableReloadToLocation = true;
		sld = characterFromId("FranzGarke");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "LeFransua_PortugalTalk");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "Portugal_LFTalk":
		dialog.text = "Me gusta tu sincronización... ¿Supongo que debo darte las gracias por mantenerme vivo hasta hoy?";
		link.l1 = "Eres correcto. Mi nombre es " + GetFullName(pchar) + " y tú, portugués, sigues siendo mi prisionero. Así que no me hagas preguntas, tenemos que irnos.";
		link.l1.go = "Portugal_LFTalk_1";
		break;

	case "Portugal_LFTalk_1":
		dialog.text = "Espera, capitán... hay muchos hombres de Vasquez en la ciudad, no nos dejarán ir así como así. Dame una espada y tendremos muchas mejores posibilidades.";
		link.l1 = "¿No estás en buenos términos con tus compañeros, eh? Bien, una hoja extra siempre es bienvenida, ¡toma el arma del cadáver y mantente cerca de mí!";
		link.l1.go = "Portugal_LFTalk_2";
		link.l2 = "¡Ni pienses que te daré un arma para que puedas atacarme cuando te dé la espalda! Solo quédate cerca de mí.";
		link.l2.go = "Portugal_LFTalk_4";
		pchar.quest.Portugal_LeFransua.win_condition.l1 = "location";
		pchar.quest.Portugal_LeFransua.win_condition.l1.location = "LeFransua_town";
		pchar.quest.Portugal_LeFransua.function = "CreateVaskezsPirates";
		bDisableFastReload = true; // закрыть переход
		break;

	case "Portugal_LFTalk_2":
		dialog.text = "No te preocupes, capitán, prefiero morir que caer de nuevo en las manos de Vásquez.";
		link.l1 = "Bueno, la cosa es que no quiero que mueras, todavía. ¡Vamos, el tiempo se acaba!";
		link.l1.go = "Portugal_LFTalk_3";
		break;

	case "Portugal_LFTalk_3":
		DialogExit();
		GiveItem2Character(npchar, "blade_17");
		EquipCharacterbyItem(npchar, "blade_17");
		GiveItem2Character(npchar, "pistol6");
		EquipCharacterbyItem(npchar, "pistol6");
		TakeNItems(npchar, "bullet", 50);
		AddItems(npchar, "gunpowder", 50);
		TakeNItems(npchar, "potion2", 3);
		LAi_SetCharacterUseBullet(npchar, GUN_ITEM_TYPE, "bullet");
		pchar.questTemp.Portugal.Condition1 = "true";
		LAi_SetActorType(npchar);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		break;

	case "Portugal_LFTalk_4":
		dialog.text = "Demasiado malo, habría ayudado al Tuerto si quisiera verte muerto...";
		link.l1 = "Pero tú tampoco me ayudaste, ¡así que cállate y muévete!";
		link.l1.go = "Portugal_LFTalk_5";
		break;

	case "Portugal_LFTalk_5":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		break;

	case "Vaskezs_pirate":
		PlaySound("Voice\Spanish\EvilPirates01.wav");
		dialog.text = "¡A las armas! ¡Son ellos! ¡Mátenlos a todos!";
		link.l1 = "Allá vamos de nuevo... ¡Venid entonces, bastardos!";
		link.l1.go = "Vaskezs_pirate_1";
		break;

	case "Vaskezs_pirate_1":
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешим драться
		DialogExit();
		if (CheckAttribute(pchar, "questTemp.Portugal.Condition1"))
		{
			sld = characterFromId("Portugal");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		for (i = 1; i <= 9; i++)
		{
			sld = characterFromId("VaskezsPirate_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "VaskezsPiratesDied");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "Avendel_LeFransua":
		chrDisableReloadToLocation = false;
		bDisableFastReload = false; // открыть переход
		sld = characterFromId("Portugal");
		if (LAi_GetCharacterHP(sld) > 0)
		{
			dialog.text = "¡Espléndido! Has matado al Perro Tuerto, ¡eso es lo que llamo una obra maestra! ¿Cuántos de sus hombres enviaste a arder en el infierno?";
			link.l1 = "Luchaba, no contaba. ¿Y dónde has estado, Hugo?";
			link.l1.go = "Avendel_LeFransua_1";
		}
		else
		{
			dialog.text = "Qué lástima, capitán. Hemos perdido y no veremos ese maldito oro. Adiós.";
			link.l1 = "Adiós, Hugo.";
			link.l1.go = "Avendel_goodbye_1";
			RemovePassenger(Pchar, npchar);
			CloseQuestHeader("Portugal");
			pchar.questTemp.Portugal = "end";
		}
		break;

	case "Avendel_LeFransua_1":
		dialog.text = "Yo... estaba asegurando la retirada segura... protegiendo nuestra retaguardia, por así decirlo.";
		link.l1 = "Bueno, eso es todo, Hugo Avendell, tu cobardía ha superado todas mis expectativas, ¿tienes idea de lo difícil que fue esa pelea para nosotros? ¡Apenas lo logramos!";
		link.l1.go = "Avendel_LeFransua_2";
		break;

	case "Avendel_LeFransua_2":
		dialog.text = "Tranquilízate, capitán... Admito que me estaba escondiendo. ¡Pero he encontrado esta oportunidad para ti! Recuerda, ¡fui yo quien te llevó hasta los portugueses! Bueno... considerando tu justa indignación, estoy de acuerdo en quedarme solo con un tercio de la recompensa.";
		link.l1 = "¡Eso es simplemente glorioso! ¿Estás regateando ahora? No, mi amigo, tu parte en este negocio ha terminado. Has perdido tu dinero en la taberna de Saint-Pierre. Lo has dejado allí y te has escapado, así que esto se ha acabado para ti ahora.";
		link.l1.go = "Avendel_LeFransua_3";
		break;

	case "Avendel_LeFransua_3":
		dialog.text = "Capitán, claramente estás exagerando... Está bien, acepto por una cuarta parte... ¡por una quinta! ¡Diez por ciento!";
		link.l1 = "¡No pongas a prueba mi paciencia! ¡Lárgate! No necesito cobardes en mi tripulación, especialmente ahora que el tiempo apremia.";
		link.l1.go = "Avendel_LeFransua_4";
		break;

	case "Avendel_LeFransua_4":
		dialog.text = "" + pchar.name + ", ¿no crees que es un poco injusto?";
		link.l1 = "Causa y efecto, Hugo... Has tomado tu decisión, así que adiós. Saca una conclusión y no te lances a aventuras como esa, claramente no son para ti.";
		link.l1.go = "Avendel_LeFransua_5";
		break;

	case "Avendel_LeFransua_5":
		DialogExit();
		LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
		sld = characterFromId("Portugal");
		sld.dialog.currentnode = "Portugal_LeFransua";
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		pchar.questTemp.Portugal.GG2 = "true"; // Jason Дороже золота
		break;

	case "Portugal_LeFransua":
		dialog.text = "¿Soltando lastre, capitán? ¡Así es, ja...! Vasquez sigue libre y hay muchos hombres y cañones en el Albatros, apuesto mis finos pantalones contra un viejo pañuelo a que Hernando no nos dejará escapar.";
		link.l1 = "Bueno, parece que tendremos que ir a saludarlo nosotros mismos. Vaya, monsieur portugués, y trate de mantener la boca cerrada. Vamos a levar anclas lo antes posible.";
		link.l1.go = "Portugal_LeFransua_1";
		break;

	case "Portugal_LeFransua_1":
		DialogExit();
		chrDisableReloadToLocation = false;
		LAi_ActorFollowEverywhere(npchar, "", -1);
		pchar.quest.Portugal_LeFransua1.win_condition.l1 = "location";
		pchar.quest.Portugal_LeFransua1.win_condition.l1.location = "Martinique";
		pchar.quest.Portugal_LeFransua1.function = "CreateVaskezsFrigate";
		break;

	case "VaskezsHelper_abordage":
		dialog.text = "¿Qué estás esperando, maldita sea?!";
		link.l1 = "¿Dónde está Hernando Vásquez? Habla y te perdonaré la vida.";
		link.l1.go = "VaskezsHelper_abordage_1";
		break;

	case "VaskezsHelper_abordage_1":
		dialog.text = "¡Vete al infierno con tus malditas preguntas!";
		link.l1 = "Después de ti...";
		link.l1.go = "VaskezsHelper_abordage_2";
		break;

	case "VaskezsHelper_abordage_2":
		DialogExit();
		QuestAboardCabinDialogExitWithBattle("");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "Portugal_treasure":
		bQuestDisableMapEnter = false;
		if (CheckAttribute(pchar, "questTemp.Portugal.Condition1") && CheckAttribute(pchar, "questTemp.Portugal.Condition2"))
		{
			dialog.text = "¡Y aquí estás, mi valiente amigo, por fin podemos tener una charla decente! Felicitaciones, capitán - matar al Perro Tuerto y destruir el 'Albatros' no fue tarea fácil. En verdad, has hecho tanto por salvar mi vida... Quizás, ¿debería incluso agradecerte?";
			link.l1 = "Me lo agradecerás cuando estés bailando en la horca o lo que sea que te hayan preparado en Willemstad.";
			link.l1.go = "Portugal_treasure_6";
		}
		else
		{
			dialog.text = "¡Y aquí estás, mi valiente amigo, por fin podemos hablar! ¡Enhorabuena, capitán, matar al Perro Tuerto merece una canción honorable! En realidad, has hecho tanto por salvar mi vida... Quizás, ¿debería incluso agradecerte?";
			link.l1 = "Me lo agradecerás cuando estés bailando en la horca o lo que sea que hayan preparado para ti en Willemstad.";
			link.l1.go = "Portugal_treasure_1";
		}
		break;

	case "Portugal_treasure_1":
		dialog.text = "¡Increíble! Has estado salvando mi vida durante las últimas dos semanas, me has llevado a tu hogar y me has protegido en las peleas... ¿y ahora vas a enviarme a la muerte? Apenas puedo creerlo... De hecho, casi te considero mi amigo ahora, ja-ja.";
		link.l1 = "¿Un pirata que apela al honor? Portugués, ¿me tomas el pelo? ¡Te estaba guardando solo para un propósito: llevar al asesino y sinvergüenza ante el tribunal de justicia!";
		link.l1.go = "Portugal_treasure_2_1";
		link.l2 = "Amigo mío... suena a burla. Pero, no obstante, tienes razón. Sería extraño que hiciera eso, portugués...";
		link.l2.go = "Portugal_treasure_2_2";
		break;

	case "Portugal_treasure_2_1":
		dialog.text = "Oh, suficiente, capitán. ¡Apuesto a que estabas haciendo todo eso solo para obtener el dinero que la Compañía prometió por el placer de verme viva! No intente ser más honesto de lo que realmente es, señor, no le queda bien.";
		link.l1 = "Solo yo puedo juzgarme a mí mismo. Así que terminemos esta conversación. Es hora de navegar hacia Willemstad.";
		link.l1.go = "Portugal_treasure_3";
		break;

	case "Portugal_treasure_2_2":
		dialog.text = "Parece que aún se puede encontrar algo de honestidad en la gente hoy en día... Lástima que el dinero siempre interfiera, ¿eh, capitán?";
		link.l1 = "Es extraño escuchar eso de un bucanero condenado, portugués. Te dejaré ir... no me preguntes por qué, solo vete al diablo en el primer puerto. Y recuerda que no seré tan amable si nos volvemos a encontrar.";
		link.l1.go = "Portugal_treasure_4";
		break;

	case "Portugal_treasure_3":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);			  // запрет диалога
		pchar.questTemp.Portugal.Villemstad = "true"; // сдать губернатору
		AddQuestRecord("Portugal", "21");
		break;

	case "Portugal_treasure_4":
		dialog.text = "¿De veras? ¡Me gustaría eso, capitán! ¿No ordenará traer aquí un poco de ron? Sabes, solo para celebrar sus cualidades caballerescas, nuestra relación y el aplazamiento de mi sentencia?";
		link.l1 = "No hagas chistes malvados, sigues siendo mi prisionero hasta la primera costa. Adiós.";
		link.l1.go = "Portugal_treasure_5";
		break;

	case "Portugal_treasure_5":
		DialogExit();
		LAi_CharacterDisableDialog(npchar); // запрет диалога
		pchar.quest.Remove_Portugal.win_condition.l1 = "Location_Type";
		pchar.quest.Remove_Portugal.win_condition.l1.location_type = "town";
		pchar.quest.Remove_Portugal.function = "RemovePortugal";
		AddQuestRecord("Portugal", "20");
		break;

	case "Portugal_treasure_6":
		dialog.text = "Veo... así que es la horca entonces. Eso era de esperar. Entonces escucha lo que te diré, capitán. Estabas tan ansioso por mantenerme vivo para ejecutarme adecuadamente más tarde y lo aprecio. Supongo que sería estúpido de mi parte pedirte que cambies de opinión así como así, ¿verdad? ¿Y qué dirás si te ofrezco algo a cambio? Un trato por así decirlo, ¿eh?";
		link.l1 = "No diré nada, portugués. Eres un pirata y un bastardo. Responderás por tus crímenes en Willemstad.";
		link.l1.go = "Portugal_treasure_2_1";
		link.l2 = "¿Un trato? ¿Qué puedes ofrecer?";
		link.l2.go = "Portugal_treasure_7";
		link.l3 = "No necesito tu trato, simplemente piérdete en el primer puerto. Es tu día de suerte.";
		link.l3.go = "Portugal_treasure_4";
		break;

	case "Portugal_treasure_7":
		dialog.text = "Tú sabes, tal persistente salvamento de mi vida a pesar de las razones desagradables detrás de ello todavía merece algo de gratitud. Y Bartolomeo el Portugués sabe algo sobre ser agradecido. Ahora escucha, un mes antes de que tú y yo nos conocimos, capturamos un barco de la Compañía. Lucharon como demonios hasta el último hombre. Pero sus bodegas solo tenían balas de cañón y ratas\nA mi tripulación no le gustó, sin embargo, encontré un cofre muy interesante y papeles dentro de la cabina del capitán. Era un barco mensajero, entregando muestras de minas en algún lugar de la Amazonia. ¡Diamantes y rubíes puros, una verdadera fortuna!";
		link.l1 = "Un premio interesante... Ahora veo por qué la Compañía está tan interesada en ti, pero ¿cuál es el punto de tu historia?";
		link.l1.go = "Portugal_treasure_8";
		break;

	case "Portugal_treasure_8":
		dialog.text = "Mis primeros oficiales Vazquez y Franz Garcke habían mantenido a la tripulación en orden, así que decidí arriesgarme. Escondí las piedras de ellos y quemé los papeles. Los holandeses habían dañado gravemente nuestro aparejo durante el abordaje y tuvimos que llevar el 'Albatros' dentro de una pequeña bahía de una pequeña isla en el norte. Me adentré solo en la jungla mientras toda la tripulación reparaba la fragata.\nEnterré las piedras, mantenerlas a bordo era demasiado arriesgado considerando las circunstancias. Mi plan era escapar de mi querida tripulación en el primer puerto, comprar o robar un pequeño bote y navegar hacia la isla, recoger mi premio, y luego... ¡adiós a mi vieja vida! Europa, una mansión decente, una esposa ardiente, ya sabes el resto...";
		link.l1 = "Déjame adivinar, algo salió mal.";
		link.l1.go = "Portugal_treasure_9";
		break;

	case "Portugal_treasure_9":
		dialog.text = "¡Todo salió mal! La maldita isla resultó ser el hogar de una horda de caníbales locales. Nos atacaron en cuanto regresé a la orilla. Tuvimos que zarpar lo más pronto posible, fue entonces cuando me golpearon. Pensé que solo era un rasguño.\nUnos días después, estaba tirado medio muerto en fiebre y, al parecer, dije algo sobre las piedras. Franz y Vázquez se dieron cuenta de que había escondido algo en la isla, pero no sabían la ubicación exacta. No les gustaba la idea de vagar por ahí y ser constantemente disparados por los indios. Así que los bastardos me arrastraron al puerto más cercano, ya que nuestro médico fue asesinado durante nuestra pelea con los holandeses, necesitaban uno nuevo.\nAsí es como terminé en la casa de ese médico, querían devolverme a la conciencia el tiempo suficiente para torturarme y averiguar la ubicación de las piedras. Creo que, después, me cortarían y alimentarían a los cangrejos con mi jugosa carne.";
		link.l1 = "No puedo decir que los juzgue - estabas tratando de engañar a tus hombres. Así que pregunto de nuevo, ¿por qué me cuentas eso?";
		link.l1.go = "Portugal_treasure_10";
		break;

	case "Portugal_treasure_10":
		dialog.text = "Estos perros no eran personas, créeme, todos ellos están ahora en su merecido lugar: el infierno, ¡ja-ja! Como pago por mi libertad y mi vida, puedo decirte la ubicación exacta de los tesoros holandeses.";
		link.l1 = "No, Bart, tu traición me ha convencido totalmente de tu vileza. Willemstad y una retribución legal te están esperando. No hay trato.";
		link.l1.go = "Portugal_treasure_2_1";
		link.l2 = "¿Y se supone que debo creer que esas gemas existen? Sea como sea, no perderé nada de todos modos... El trato fue el comienzo de esta historia y el trato será su fin. Acepto tus términos, portugués.";
		link.l2.go = "Portugal_treasure_11";
		break;

	case "Portugal_treasure_11":
		dialog.text = "Considera esto como mi modesta gratitud. ¡Eh, desearía saber cuánto cuesta la piel de Bartolomeo el Portugués en relucientes pesos, ja! Entiendo que tus objetivos eran estrictamente prácticos, pero aun así, gracias, capitán, por todo, ja-ja\nSon los Turcos, la jungla no muy lejos de sus costas. Encuentra un árbol seco y torcido, solo hay un árbol así allí. He enterrado el cofre cerca de él. Así que no olvides llevar una pala. Buena caza...";
		link.l1 = "Está bien, recordaré eso y puedes tomar un bote ahora mismo y alejarte de mi barco. Adiós.";
		link.l1.go = "Portugal_treasure_12";
		break;

	case "Portugal_treasure_12":
		dialog.text = "Una última cosa, capitán. Supongo que todavía hay muchos salvajes, pero no son solo ellos los que deberían preocuparte. Vasquez no estaba en el 'Albatros', ¿verdad? El Maldito Don es demasiado astuto... cuida tu espalda hasta que lo veas colgado o con una bala en la cabeza.";
		link.l1 = "Gracias por tu advertencia, portugués. Ahora, ¿serías tan amable de abandonar mi barco ya... no pongas a prueba mi paciencia?";
		link.l1.go = "Portugal_treasure_13";
		break;

	case "Portugal_treasure_13":
		DialogExit();
		LAi_SetImmortal(npchar, false);
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 2.0);
		AddQuestRecord("Portugal", "23");
		pchar.quest.Portugal_Terks.win_condition.l1 = "location";
		pchar.quest.Portugal_Terks.win_condition.l1.location = "Terks_Jungle_01";
		pchar.quest.Portugal_Terks.function = "CreateHollIndBattle";
		break;

	case "Avendel_Marigo":
		pchar.quest.SetAvendelMarigoOver.over = "yes"; // снять таймер
		dialog.text = "¡Oh, y quién es este! Capitán " + pchar.name + " ¡él mismo! ¿Quieres un trago?";
		link.l1 = "Sabes, en realidad me alegra verte de nuevo. Pero quizás fui demasiado brusco contigo en Martinica.";
		link.l1.go = "Avendel_Marigo_1";
		break;

	case "Avendel_Marigo_1":
		dialog.text = "¡Lo que sea, capitán! Lo que pasó, pasó... Pero a decir verdad, realmente te había dado una razón para echarme... ¡Pero oye, no vas a creer quién es el invitado en Phillipsburg hoy!";
		link.l1 = "No me digas que es...";
		link.l1.go = "Avendel_Marigo_2";
		break;

	case "Avendel_Marigo_2":
		dialog.text = "¡No, no, capitán, no son los portugueses! Y no es algún bastardo herido otra vez. ¡Es mucho mejor! ¡Es Hernando Vásquez... el mismísimo Don Sangriento! Ha sido huésped del gobernador durante los últimos días.";
		link.l1 = "¿Vasquez? ¿El invitado del gobernador? Ahora veo. Hugo, cuéntame más sobre eso, ¿qué demonios está pasando aquí?";
		link.l1.go = "Avendel_Marigo_3";
		break;

	case "Avendel_Marigo_3":
		pchar.questTemp.Portugal.AvMoney = 10000;
		dialog.text = "Bueno, sé mucho... pero gracias a nuestro viaje, estoy en bancarrota otra vez. ¿Quizás tu necesidad de esta información valga unos cuantos pesos?";
		link.l1 = "¡Hugo, sigues siendo un extorsionista y un canalla! Habla lo que tienes, toma 5000 pesos solo por el bien de nuestra vieja amistad.";
		link.l1.go = "Avendel_Marigo_4_1";
		if (sti(pchar.money) >= 10000)
		{
			link.l2 = "De alguna manera no me sorprende. ¡Aquí, toma 10000 pesos y será mejor que esperes que tu información cueste tanto dinero!";
			link.l2.go = "Avendel_Marigo_4_2";
		}
		link.l3 = "Tengo una propuesta mejor para ti. ¿Qué tal si te unes a mi tripulación? Supongo que tienes talento para hacer y encontrar tratos rentables, así que si estás harto de fingir ser un valiente luchador, eres más que bienvenido a tomar el puesto de mi intendente.";
		link.l3.go = "Avendel_Marigo_4_3";
		break;

	case "Avendel_Marigo_4_1":
		pchar.questTemp.Portugal.AvMoney = 15000;
		dialog.text = "No, capitán, ¡no va a funcionar así! Has arrebatado una gran suma con ese maldito portugués, estoy seguro. Así que considera eso como mi parte, no seas tan codicioso. ¡15000 monedas y ni un solo peso menos!";
		if (sti(pchar.money) >= 15000)
		{
			link.l1 = "¡Al diablo contigo, llévatelos!";
			link.l1.go = "Avendel_Marigo_4_2";
		}
		link.l2 = "Bueno, y dicen que la avaricia es buena... ¿No es eso demasiado para ti, eh?";
		link.l2.go = "Avendel_Marigo_wait";
		break;

	case "Avendel_Marigo_4_2":
		AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Portugal.AvMoney));
		dialog.text = "¡Ahora ese es el premio para mí! ... Escucha, Vasquez navegaba conmigo en el mismo barco, sin embargo, mientras yo limpiaba las cubiertas como pago por el viaje, él descansaba en una cabina, así que gracias a Dios rara vez nos veíamos y no me reconoció. Pero he comenzado a seguir a este diablo de inmediato... Una historia interesante ha sucedido con él.";
		link.l1 = "¡Adelante! ¿Qué está haciendo en el palacio del gobernador?";
		link.l1.go = "Avendel_Marigo_5";
		break;

	case "Avendel_Marigo_5":
		dialog.text = "No sé mucho, pero la guarnición ha estado en alerta durante unos días después de su llegada y el enorme buque de guerra levantó anclas de repente y se fue con gran prisa, creo que navegó hacia el noroeste. Toda la ciudad estaba perdida en conjeturas y cotilleos...";
		link.l1 = "¡Así que ese era el barco que encontré! Intrigante... No te desvíes del tema, Hugo, continúa tu historia, por favor.";
		link.l1.go = "Avendel_Marigo_6";
		break;

	case "Avendel_Marigo_6":
		dialog.text = "Bueno, como dije, el barco se había ido y Vasquez se había convertido en una especie de huésped de nuestro gobernador Martin Thomas. Lo veo a veces en el pueblo, siempre está en compañía de algunos soldados. No sé si es su escolta o convoy, ja-ja. Pero solo las personas en la residencia podrían contarte más sobre el Don.";
		if (CheckAttribute(pchar, "questTemp.Portugal.AvOfficer"))
		{
			link.l1 = "Quizás tengas razón. Pero hemos hecho un trato, ¿recuerdas? No juegues al héroe, ve a mi barco y espera mi regreso. Intentaré hablar con nuestro hospitalario gobernador.";
			link.l1.go = "Avendel_hire";
		}
		else
		{
			link.l1 = "Bueno, eso fue interesante. Realmente me has ayudado, Hugo. Bebe tu ron, el resto no es de tu incumbencia.";
			link.l1.go = "Avendel_Marigo_del";
		}
		AddDialogExitQuestFunction("InMarigoResidence");
		break;

	case "Avendel_Marigo_4_3":
		dialog.text = "¿Hablas en serio, capitán? ¿Qué te pasa? Me has ahuyentado apuntándome con una pistola en la cara y ahora vienes con tales propuestas?";
		if (sti(pchar.money) >= 10000)
		{
			link.l1 = "Olvida eso, no he sido yo mismo y lo siento, la codicia me consumió, supongo. Aquí, toma 10000 pesos y dime lo que sabes sobre Vásquez, tengo prisa.";
			link.l1.go = "Avendel_Marigo_4_2";
		}
		link.l2 = "Tal vez, debería disculparme por ese asunto. Eres un luchador patético, pero manejas bien las monedas. Repito mi propuesta, ¿qué dices?";
		link.l2.go = "Avendel_Marigo_7";
		break;

	case "Avendel_Marigo_7":
		pchar.questTemp.Portugal.AvMoney = 20000;
		pchar.questTemp.Portugal.AvOfficer = "true";
		dialog.text = "¿Qué puedo decir... Aceptaré, pero solo después de recibir mi parte, capitán. ¿Diez por ciento, recuerdas? Has recibido dos mil por ese canalla, así que si me pides unirme a tu tripulación, será mejor que empieces por saldar tus deudas. ¡Diez por ciento y sin discusiones!";
		link.l1 = "Eres un bribón, Hugo. No tengo tanto conmigo ahora, pero volveré pronto. Quédate aquí.";
		link.l1.go = "Avendel_Marigo_wait";
		if (sti(pchar.money) >= 20000)
		{
			link.l2 = "¡Espero que justifiques mis expectativas con ese agarre para los negocios tuyo, ja! ¡Toma tu parte!";
			link.l2.go = "Avendel_Marigo_4_2";
		}
		break;

	case "Avendel_Marigo_wait":
		dialog.text = "Es tu decisión, capitán. Me quedaré aquí por un rato. Regresa si cambias de opinión.";
		link.l1 = "Bien, Hugo.";
		link.l1.go = "exit";
		NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;

	case "Avendel_Marigo_repeat":
		dialog.text = "¿Ha cambiado de opinión, capitán? Entonces espero mi dinero.";
		if (sti(pchar.money) >= sti(pchar.questTemp.Portugal.AvMoney))
		{
			link.l1 = "¡Toma tus monedas, bribón ja-ja!";
			link.l1.go = "Avendel_Marigo_4_2";
		}
		link.l2 = "No tengo tal suma todavía.";
		link.l2.go = "exit";
		NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;

	case "Avendel_Marigo_del":
		DialogExit();
		npchar.lifeday = 0;
		LAi_CharacterDisableDialog(npchar);
		break;

	case "Avendel_hire":
		DialogExit();
		LAi_SetImmortal(npchar, false); // patch-8
		SetCharacterRemovable(npchar, true);
		npchar.quest.OfficerPrice = sti(pchar.rank) * 1000;
		Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
		npchar.loyality = 25;
		npchar.dialog.FileName = "Enc_Officer_dialog.c";
		AddDialogExitQuestFunction("LandEnc_OfficerHired");
		NextDiag.CurrentNode = NextDiag.TempNode;
		break;

	case "Servant":
		// pchar.quest.InMarigoResidenceOver.over = "yes"; //снять таймер
		dialog.text = "Buen día, capitán. ¿Quieres algo?";
		link.l1 = "No, no, solo estoy esperando, ¿cuándo estará libre el señor Thomas? Estoy esperando una audiencia... sí. Dime, ¿su Excelencia realmente considera amigo al famoso pirata Hernando Vasquez?";
		link.l1.go = "Servant_1";
		break;

	case "Servant_1":
		dialog.text = "No os preocupéis, señor, debería ser liberado en cualquier momento ahora, ¡y por supuesto que no, señor! Este bandido se ha rendido a las autoridades, pero de alguna manera no fue ahorcado. Quizás compró su vida traicionando a sus antiguos compañeros de crimen... No estoy seguro. Ha estado encarcelado durante varios días aquí... ¡Eso fue una pesadilla, señor! ¡Esa bestia en forma humana estaba viviendo en nuestra mansión!";
		link.l1 = "¡Una pesadilla es! ¿Qué podría decir esa bestia al señor Thomas para evitar la horca? ¡Ni siquiera puedo imaginarlo!";
		link.l1.go = "Servant_2";
		break;

	case "Servant_2":
		dialog.text = "No sé tampoco, pero puedo decirte en secreto que todos los sirvientes se alegraron cuando su Excelencia se deshizo de tal huésped...";
		link.l1 = "¿Te deshiciste de él? ¿Por fin obtuvo lo que merecía?";
		link.l1.go = "Servant_3";
		break;

	case "Servant_3":
		dialog.text = "Aún no. Hace unos días lo llevaron a un bergantín militar que zarpó hacia Willemstad. Verás, parece que el señor Thomas perdió interés en el sinvergüenza, parece que intentó engañarlo.\nTambién dicen que atraparon a su ex capitán, ¡Bartolomeo el Portugués! ¡Imagínate eso! Parece que la Compañía quiere colgarlos juntos. Los rumores dicen que el juicio será en un mes, pero ¿por qué esperar tanto tiempo?";
		link.l1 = "¿Los portugueses?! Hm... gracias por hacerme compañía amigo... parece que el señor Thomas está libre ahora, me retiraré.";
		link.l1.go = "Servant_4";
		break;

	case "Servant_4":
		DialogExit();
		npchar.lifeday = 0;
		LAi_CharacterDisableDialog(npchar);
		AddQuestRecord("Portugal", "31");
		pchar.questTemp.Portugal = "SeekPortVillemstad";
		// SetFunctionTimerCondition("InMarigoResidenceOver", 0, 0, 30, false);
		colonies[FindColony("Villemstad")].jail = 0;
		sld = characterFromId("Portugal");
		sld.model = "Port_A"; // меняем модель
		sld.dialog.currentnode = "Portugal_free";
		LAi_SetStayType(sld);
		ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto9");
		sld = GetCharacter(NPC_GenerateCharacter("PortHolOfficer", "off_hol_4", "man", "man", 35, HOLLAND, 30, true, "soldier"));
		FantomMakeCoolFighter(sld, sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 10, 100, 100, "blade_19", "pistol3", "grapeshot", 100);
		SetCharacterPerk(sld, "SwordplayProfessional");
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
		ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto23");
		LAi_LocationDisableOfficersGen("Villemstad_prison", true); // офицеров не пускать
		break;

	case "Vaskez":
		dialog.text = "Ahora estáis muertos... ¡los dos!";
		link.l1 = "...";
		link.l1.go = "Vaskez_1";
		break;

	case "Vaskez_1":
		DialogExit();
		LAi_ActorAnimation(npchar, "shot", "VaskezFight", 2.0);
		break;

	case "Portugal_free":
		if (LAi_group_GetTarget(pchar) <= 0)
		{
			dialog.text = "¡Ahora este es a quien no esperaba ver, capitán! Pero no parece una visita amistosa, toda esta sangre, ruido y un tiroteo, ¿o es algún tipo de celebración con fuegos artificiales, eh?";
			link.l1 = "¡Deja de hacer tus malditos chistes, portugués! No me gusta cómo has usado la libertad que compraste de mí. ¡He puesto demasiado esfuerzo en salvar tu patético trasero para que te atrapen tan estúpidamente justo después de nuestra separación!";
			link.l1.go = "Portugal_free_1";
			// belamour legendary edition -->
			link.l2 = "¡Pues estaba aburrido! Así que vine aquí a visitarte. ¿Estás cómodo aquí amigo?";
			link.l2.go = "Portugal_free_1a";
			// <-- legendary edition
		}
		else
		{
			dialog.text = "¡Ten cuidado, amigo! Eh, qué lástima que no puedo ayudarte.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Portugal_free";
		}
		break;
	// belamour legendary edition -->
	case "Portugal_free_1a":
		AddCharacterExpToSkill(pchar, "Fortune", 100);
		dialog.text = "Entonces la nobleza a veces no se ve afectada por las monedas, ¿eh? Ja... ¡CUIDADO, JUSTO DETRÁS DE TI!";
		link.l1 = "¡Agh, no esta mierda otra vez!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("CreateErnandoVaskez");
		NextDiag.TempNode = "Portugal_free";
		break;

	case "Portugal_free_1":
		AddCharacterExpToSkill(pchar, "Leadership", 100);
		// <-- legendary edition
		dialog.text = "Entonces, la nobleza a veces no se ve afectada por monedas, ¿eh? Ja... ¡CUIDADO, JUSTO DETRÁS DE TI!";
		link.l1 = "¡Agh, no esta mierda otra vez!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("CreateErnandoVaskez");
		NextDiag.TempNode = "Portugal_free";
		break;

	case "Portugal_free_2":
		dialog.text = "¡Y te advertí que este tipo era un problema!";
		link.l1 = "¡Casi logró dispararme por la espalda y matarme! ¿Cómo logró pasar?";
		link.l1.go = "Portugal_free_3";
		break;

	case "Portugal_free_3":
		dialog.text = "Vi que tenía una ganzúa, parece que alguien se la había dado... siempre tenía conexiones en los estratos bajos. Bueno, capitán, creo que deberíamos dejar este lugar, ¿no está de acuerdo?";
		link.l1 = "¡No me digas! Bien, apresurémonos antes de que toda la guarnición llegue aquí. Romperé tu cerradura en un segundo...";
		link.l1.go = "Portugal_free_4";
		break;

	case "Portugal_free_4":
		DialogExit();
		InterfaceStates.Buttons.Save.enable = true; // разрешить сохраняться
		chrDisableReloadToLocation = false;
		DoQuestReloadToLocation("Villemstad_Exittown", "rld", "loc17", "PortugalFree");
		break;

	case "Portugal_free_5":
		dialog.text = "Sabes, capitán, este aire fresco... empiezas a valorarlo solo después de pasar unas semanas en un calabozo justo después de que el bote de tu barco fuera encontrado por la patrulla. Supongo que todavía te debo por mi rescate.";
		link.l1 = "No hay necesidad, portugués. No soy un caballero honorable, solo... Hago lo que creo que es correcto y debe hacerse.";
		link.l1.go = "Portugal_free_6";
		break;

	case "Portugal_free_6":
		dialog.text = "Ja, ¡y esa es una calidad perfecta! Pero insisto, aquí, tómalo... esto es lo único que pude esconder en la prisión... Sí, lo has adivinado. Este es mi talismán. Siempre me dio suerte en el mar. Eres un buen marinero y tú o tu navegante podrán usarlo, estoy seguro de ello.";
		link.l1 = "Sí, y tuviste la suerte de caer directamente en las manos de los holandeses con ese talismán.";
		link.l1.go = "Portugal_free_7";
		break;

	case "Portugal_free_7":
		dialog.text = "¡Oye! Sigo vivo, ¿verdad? Y solo para que lo sepas, ya no estoy en prisión. Tómalo, capitán, es hora de que el talismán te sirva. ¡Y te agradezco de nuevo!";
		link.l1 = "Adiós entonces, portugués. Y, por favor, ¡intenta mantenerte alejado de la horca! ¡Solo por el bien de mi arduo trabajo, ja-ja!";
		link.l1.go = "Portugal_free_8";
		break;

	case "Portugal_free_8":
		TakeNItems(pchar, "talisman2", 1);
		Log_Info("Has recibido el talismán");
		PlaySound("interface\important_item.wav");
		DialogExit();
		LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
		npchar.lifeday = 0;
		LAi_LocationDisableOfficersGen("Villemstad_prison", false); // офицеров пускать
		AddQuestRecord("Portugal", "34");
		CloseQuestHeader("Portugal");
		pchar.questTemp.Portugal = "end";
		pchar.questTemp.Portugal.GG1 = "true"; // Jason Дороже золота
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
