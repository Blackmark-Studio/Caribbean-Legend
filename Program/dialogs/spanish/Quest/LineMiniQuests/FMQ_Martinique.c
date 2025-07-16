// Addon-2016 Jason, французские миниквесты (ФМК) Мартиника
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
		dialog.text = "Un error obvio. Informa a los desarrolladores sobre ello.";
		link.l1 = "Oh, lo haré.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	// квестодатель
	case "carpenter":
		DelMapQuestMarkCity("Fortfrance");
		LAi_SetImmortal(npchar, false);
		npchar.lifeday = 0;
		DelLandQuestMark(npchar);
		dialog.text = TimeGreeting() + ", capitán. Permítame presentarme, " + GetFullName(npchar) + " Aunque ya nos hemos encontrado hace poco, dudo que me recuerdes.";
		link.l1 = "Saludos, monsieur. ¿Y dónde podría haberte visto antes?";
		link.l1.go = "carpenter_1";
		break;

	case "carpenter_1":
		sTemp = "lugger 'Adeline'";
		if (pchar.questTemp.Sharlie.Ship == "sloop")
			sTemp = "balandro 'Black Dog'";
		dialog.text = "Nuestro astillero. Has comprado " + sTemp + ". ¿Recuerdas ahora? Soy carpintero allí.";
		link.l1 = "Sí, realmente compré ese barco. Entonces, ¿qué quieres, monsieur " + GetFullName(npchar) + "?";
		link.l1.go = "carpenter_2";
		break;

	case "carpenter_2":
		sld = characterFromId("FortFrance_shipyarder");
		AddLandQuestMark(sld, "questmarkmain");
		dialog.text = "Nuestro constructor de barcos " + GetFullName(sld) + " quiere hablar contigo. Creo que tiene algún tipo de propuesta de negocio. Vio tu barco en nuestro puerto y me envió a encontrarte. ¿Aceptarías amablemente la invitación?";
		link.l1 = "Está bien. Haré una visita a tu jefe una vez que termine mis asuntos en la ciudad.";
		link.l1.go = "carpenter_3";
		break;

	case "carpenter_3":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "none", "", "", "", 10.0);
		chrDisableReloadToLocation = false;
		pchar.questTemp.FMQM = "begin";
		AddQuestRecord("FMQ_Martinique", "1");
		SetFunctionTimerCondition("FMQM_Denial", 0, 0, 2, false);
		break;

	case "officer":
		PlaySound("Voice\Spanish\soldier_arest_1.wav");
		dialog.text = "Bueno, bueno... ¡Contrabandistas frescos en mi red!";
		link.l1 = "Eh...";
		link.l1.go = "officer_1";
		break;

	case "officer_1":
		dialog.text = "¡Corta el rollo! Hay varios barriles de resina dentro de este astillero. Capitán, los ha entregado a su compañero de fechorías. ¡Ambos están arrestados y confisco la carga en nombre de la ley!";
		link.l1 = "...";
		link.l1.go = "officer_2";
		break;

	case "officer_2":
		DialogExit();
		LAi_SetActorType(npchar);
		sld = characterFromId("FortFrance_shipyarder");
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

	case "officer_3":
		dialog.text = "¡No te hagas el tonto, maestro! ¿Qué barriles? ¡Sabes que estoy hablando de los mismos barriles que descargaste recientemente de la nave de este marinero! ¡Ambos se pudrirán en las mazmorras! Muévanse, cabrones...";
		link.l1 = "";
		link.l1.go = "officer_4";
		break;

	case "officer_4":
		DialogExit();
		LAi_SetActorType(npchar);
		sld = characterFromId("FortFrance_shipyarder");
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

	case "officer_5":
		PlaySound("Voice\Spanish\soldier\soldier arest-02.wav");
		dialog.text = "Esta resina, mi querido maestro constructor naval, es un bien de valor estratégico que está bajo el control directo de nuestro gobernador. ¡Ya que afirmas que es toda tuya, que así sea! Estás bajo arresto, pasarás esta noche en nuestras cómodas mazmorras y mañana nos darás un informe detallado de cómo las conseguiste y con qué propósito. No te preocupes, eventualmente lo sabremos todo. Tú, capitán, eres libre de irte. Es tu día de suerte.";
		link.l1 = "";
		link.l1.go = "officer_6";
		break;

	case "officer_6":
		DialogExit();
		LAi_SetActorType(pchar);
		LAi_ActorTurnToCharacter(pchar, characterFromID("FMQM_officer"));
		sld = characterFromId("FortFrance_shipyarder");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1", "FortFrance_town", "officers", "reload5_3", "FMQM_ArestContinue", 8);
		break;

	case "officer_7":
		PlaySound("Voice\Spanish\soldier_arest_2.wav");
		dialog.text = "Sabía que había algo mal con este barco... Parece que te he subestimado, capitán.";
		link.l1 = "Exactamente, teniente. No soy tan estúpido. Tu alegre cooperación con el constructor naval está comprometida ahora.";
		link.l1.go = "officer_8";
		DelLandQuestMark(npchar);
		break;

	case "officer_8":
		dialog.text = "Ya veo. Felicitaciones, debes ser talentoso ya que lograste rastrearme y sorprenderme. Ahora dime qué quieres.";
		link.l1 = "¿No está claro? Necesito que me devuelvas mi resina. La resina que tú y tu compañero me han robado.";
		link.l1.go = "officer_9";
		break;

	case "officer_9":
		dialog.text = "Está bien. Puedes tenerlo, pero solo la mitad de tu lote. Eso es todo lo que tengo guardado aquí. Espero que te sea suficiente, ya que es todo lo que puedo ofrecer.";
		link.l1 = "¿Todavía intentas engañarme? Compénsame la otra mitad con oro o con mercancías escondidas detrás de ti.";
		link.l1.go = "officer_10";
		break;

	case "officer_10":
		dialog.text = "No es una opción. Dirígete a nuestro amigo común por la otra mitad.";
		link.l1 = "¿Me estás jodiendo? ¿De verdad crees que " + GetFullName(characterFromId("FortFrance_shipyarder")) + "¿me devolverá mis barriles? Eso es ridículo.";
		link.l1.go = "officer_11";
		break;

	case "officer_11":
		dialog.text = "Capitán, llévese toda la resina que tengo, salve su vida y lárguese de aquí. Puedo añadir a este trato mi promesa de no causarle problemas en Saint-Pierre. Esa es mi oferta final.";
		link.l1 = "¿Desde cuándo mi vida es parte del trato? ¡Ja!";
		link.l1.go = "officer_12";
		break;

	case "officer_12":
		dialog.text = "Parece que todavía te sientes invencible después de la pelea, capitán. Déjame explicarte esto: esos eran novatos, sin entrenamiento y desmotivados, no tienes ninguna oportunidad contra mi escuadrón. Podría matarte aquí mismo sin ningún regateo, pero valoro la vida de mis hombres. Alguien de ellos podría resultar herido o incluso muerto en el proceso de matarte. Así que o aceptas mi generosa oferta o te quedas aquí para siempre. Es hora de elegir.";
		link.l1 = "Que te den, teniente, pero me veo obligado a aceptar tus términos. Estoy gravemente en desventaja aquí.";
		link.l1.go = "officer_13";
		link.l2 = "¿Demasiado confiado, teniente? Supongo que debería enseñarte a ti y a tus mercenarios una lección. ¡Maldito perro resinoso!";
		link.l2.go = "officer_15";
		break;

	case "officer_13":
		dialog.text = "Eres un hombre razonable, capitán. Toma tus barriles y piérdete. Debo advertirte, señalarme con el dedo frente al gobernador no servirá de nada. Hoy cambiaré la ubicación de mi escondite. Ahorra tu tiempo.";
		link.l1 = "No iba a hacerlo. Entiendo la futilidad de dirigirse a las autoridades.";
		link.l1.go = "officer_14";
		break;

	case "officer_14":
		dialog.text = "Date prisa, no tengo mucho tiempo que perder.";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("FMQM_PeaceExit");
		break;

	case "officer_15":
		DialogExit();
		AddDialogExitQuestFunction("FMQM_BattleExit");
		break;

	case "greguar":
		PlaySound("Voice\Spanish\LE\Greguar\Greguar_02.wav");
		dialog.text = "¡Oh! ¡Qué encuentro! ¡Saludos, monsieur! ¿Pasando una gran noche?";
		link.l1 = "Buenas noches... ¡ah, eres tú! Te recuerdo, nos conocimos el primer día de mi llegada al Caribe. Monseñor Gregoire Valinnie.";
		link.l1.go = "greguar_1";
		break;

	case "greguar_1":
		dialog.text = "Me alegra que todavía lo recuerdes. Veo que ahora eres capitán. Capitán " + GetFullName(pchar) + "¡Felicitaciones!";
		link.l1 = "Gracias...";
		link.l1.go = "greguar_2";
		break;

	case "greguar_2":
		dialog.text = "Pareces preocupado, capitán. ¿Qué ocurrió aquí? ¿Pasa algo malo?";
		link.l1 = "Algo está mal...";
		link.l1.go = "greguar_3";
		break;

	case "greguar_3":
		dialog.text = "Monsieur, en lugar de quedarnos en medio de la calle, vayamos a una taberna. Te vendría bien una pinta o dos. Podemos hablar allí. ¡Vamos!";
		link.l1 = "...";
		link.l1.go = "greguar_4";
		break;

	case "greguar_4":
		DialogExit();
		NextDiag.CurrentNode = "greguar_5";
		FreeSitLocator("Fortfrance_tavern", "sit_front4");
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Fortfrance_tavern", "sit", "sit_front4", "FMQM_InTavern", -1);
		break;

	case "greguar_5":
		LAi_SetSitType(Pchar);
		dialog.text = "Vierte, capitán...";
		link.l1 = "Adelante..";
		link.l1.go = "greguar_6";
		break;

	case "greguar_6":
		LAi_Fade("", "");
		WaitDate("", 0, 0, 0, 1, 20);
		RecalculateJumpTable();
		dialog.text = "Uff... Ahora, por favor dime, ¿qué te pasa? Pareces como ese tipo al que ahorcaron la semana pasada. Tenía la misma cara mientras estaba en la horca.";
		link.l1 = "Vea, monseniour Gregoire... Digamos que tengo problemas en el trabajo.";
		link.l1.go = "greguar_7";
		break;

	case "greguar_7":
		dialog.text = "Capitán, puedes compartir todo conmigo. No voy a delatarte al gobernador o al comandante, puedes confiar en mí para eso. ¿No confías en mí?";
		link.l1 = "Confío en usted, monsieur.";
		link.l1.go = "greguar_8";
		break;

	case "greguar_8":
		dialog.text = "Entonces confiesa y alivia un poco tu alma. Podría estar en una posición para ayudarte.";
		link.l1 = "Un constructor de barcos me contrató para saquear una caravana española que zarpó de Trinidad. Tenía una gran necesidad de resina, ese era mi objetivo y prometió pagar quince doblones por barril. Rastreé la caravana, la saqué y traje las mercancías aquí. Pusieron mi nave en reparaciones y descargaron los barriles en el astillero. Estábamos a punto de cerrar nuestro trato cuando apareció ese oficial... Me pregunto cómo pudo enterarse.";
		link.l1.go = "greguar_9";
		break;

	case "greguar_9":
		dialog.text = "";
		link.l1 = "Eso fue todo, nos tenían. Creo que debo darle crédito al constructor de barcos - echó toda la culpa sobre sí mismo, les dijo que la resina es de su propiedad y que yo no tengo nada que ver con eso. Al final, lo arrestan y mi dinero se ha esfumado. El lío con la caravana española fue una pérdida de tiempo y dinero, aunque tuve suerte de no acabar en prisión. Sirve otro trago, monseñor Gregoire.";
		link.l1.go = "greguar_10";
		break;

	case "greguar_10":
		dialog.text = "¿Entonces, el constructor de barcos está arrestado?";
		link.l1 = "Bueno, sí. Lo llevaron a la prisión el mismo oficial del que estaba hablando. Deberías haberlos visto.";
		link.l1.go = "greguar_11";
		break;

	case "greguar_11":
		dialog.text = "Sí, los vi a ambos, aunque no tenía idea de que el teniente Felicien Gronier pudiera arrestar a su viejo amigo.";
		link.l1 = "¿Qu... qué acabas de decir?";
		link.l1.go = "greguar_12";
		break;

	case "greguar_12":
		dialog.text = "Has oído bien. El teniente Felicien Gronier y el constructor naval " + GetFullName(characterFromId("FortFrance_shipyarder")) + " son viejos amigos. Solían servir juntos en el ejército en Europa. Gronier se ha quedado en el ejército y " + GetFullName(characterFromId("FortFrance_shipyarder")) + "ha logrado iniciar su propio negocio.";
		link.l1 = "Entonces se conocen... Ahora lo veo...";
		link.l1.go = "greguar_13";
		break;

	case "greguar_13":
		dialog.text = "Mi querido " + pchar.name + ", parece que te han engañado. Eres todavía un novato aquí y lo han aprovechado. Apuesto cien doblones a que monsieur " + GetFullName(characterFromId("FortFrance_shipyarder")) + " estará paseando por su astillero de nuevo en tres días o menos.";
		link.l1 = "Parece que tienes razón, monsieur. Me han jodido. No hay manera de que ese oficial pudiera saber sobre la resina. Y el momento fue perfecto también.";
		link.l1.go = "greguar_14";
		break;

	case "greguar_14":
		dialog.text = "Este es el Caribe, monseñor " + pchar.name + " Acostúmbrate. Olvídate de las apariencias, la peor escoria aquí siempre parece un noble honorable.";
		link.l1 = "Escuché esta línea en algún lugar antes... ¿Qué debería hacer con ellos? ¿Debería dirigirme al gobernador?";
		link.l1.go = "greguar_15";
		break;

	case "greguar_15":
		dialog.text = "Temo que en este caso " + GetFullName(characterFromId("FortFrance_astillero")) + " contará otra historia a ellos y terminarás en prisión.";
		link.l1 = "Figuras. ¡Muy bien entonces! Ya que la ley no está de mi lado, ¡lo haré a mi manera, maldita sea! No voy a rendirme así como así.";
		link.l1.go = "greguar_16";
		break;

	case "greguar_16":
		dialog.text = "Por favor, cálmate " + pchar.name + ". Es la ira y el ron hablando, no tú. Duerme un poco y luego piénsalo de nuevo. Quizás sería mejor que lo dejaras pasar. Teniente Felicien Gronier y " + GetFullName(characterFromId("FortFrance_astillero")) + " son personas poderosas aquí, están muy por encima de tu nivel. No hagas nada estúpido.";
		link.l1 = "Lo veremos. Gracias por ilustrarme. Es bueno haberte conocido.";
		link.l1.go = "greguar_17";
		break;

	case "greguar_17":
		dialog.text = "Ten cuidado. Ten en mente lo que te he dicho.";
		link.l1 = "Lo haré. ¡Ahora tomemos un último trago!";
		link.l1.go = "exit";
		AddDialogExitQuest("FMQM_OutTavern");
		break;

	case "greguar_18":
		PlaySound("Voice\Spanish\LE\Greguar\Greguar_03.wav");
		dialog.text = "¡Capitán " + GetFullName(pchar) + "!";
		link.l1 = "¡Oh, monsieur Gregoire! ¡Usted otra vez!";
		link.l1.go = "greguar_19";
		break;

	case "greguar_19":
		dialog.text = "Sí. Después de nuestra charla en la taberna hice averiguaciones sobre el teniente Felicien Gronier. Resulta que solicitó un permiso de diez días no hace mucho. Su petición fue aprobada. Lo vi hoy, tomó un bote hacia una tartana que pronto zarpó hacia Guadalupe. Se llama el Topaz\nTe he contado todo, ahora es tu decisión. Estoy seguro de que puedes ver el patrón en la repentina solicitud de Gronier para tomar un permiso y alejarse de la isla en una tartana recién construida.";
		link.l1 = "¡Demonios, ahora todo está claro para mí, eso es seguro! ¡Este tartán tiene mi resina almacenada en la bodega de carga! ¡Monsieur Gregoire, gracias, realmente me has ayudado! ¿Hay algo que pueda hacer por ti a cambio?";
		link.l1.go = "greguar_20";
		break;

	case "greguar_20":
		dialog.text = "Vamos, amigo mío. Somos caballeros, debemos ayudarnos mutuamente. Así es como vivimos. Creo que habrías hecho lo mismo si estuvieras en mi lugar. No pierdas ni un minuto, navega hacia el norte y encuentra al oficial. No entres en combate, solo síguelo y averigua qué está tramando. ¡Rápido, capitán!";
		link.l1 = "¡Gracias de nuevo!";
		link.l1.go = "exit";
		AddDialogExitQuest("FMQM_HurryToSea");
		break;

	case "pirate":
		dialog.text = "¿Qué estás mirando? ¿Qué quieres aquí?";
		link.l1 = "Eh compadre, estoy tras mis mercancías. ¿Ves esos barriles de allí? Es mi resina por la que no me pagaron ni un centavo.";
		link.l1.go = "pirate_1";
		DelLandQuestMark(characterFromId("FMQM_Enemy_crew_2"));
		break;

	case "pirate_1":
		dialog.text = "¿Eres un idiota o qué? ¡Piérdete mientras aún puedas!";
		link.l1 = "Puse demasiado esfuerzo en conseguir esta resina para permitir que unos miserables sucios me detengan.";
		link.l1.go = "pirate_2";
		break;

	case "pirate_2":
		dialog.text = "¡Te enterraremos con ese elegante traje aquí mismo!";
		link.l1 = "¡Qué amable de tu parte proponer un entierro, pero me temo que tendremos que dejarte aquí en la playa para que las gaviotas se coman tus tripas!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("FMQM_ShoreFight");
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
