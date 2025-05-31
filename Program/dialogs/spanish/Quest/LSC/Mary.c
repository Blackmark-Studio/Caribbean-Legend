// Мэри Каспер - взаимная любовь и офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	int iTime, iAddTime;
	string sTemp, sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_", 0) != -1)
	{
		i = findsubstr(sAttr, "_", 0);
		NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
		Dialog.CurrentNode = "SetGunBullets2";
	}

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "¿Qué necesitas?";
		link.l1 = "No, no es nada.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

		// ---------------------------------покушение на Акулу - вариант R --------------------------------
		// разговор в каюте Адольфа
	case "Cabin":
		dialog.text = "Marcello, lo conozco. Es amigo de Rivados y de los piratas. Adolf nunca trabajaría con él. Huele el aire... ¿sientes el olor a pólvora? Y hay sangre en la pared... ¡Él mató a Adolf y ahora intenta engañarnos! ¡Debe estar trabajando para el almirante! ¡Mátalo!";
		link.l1 = "Por favor, Mary, cuéntame más sobre tus aventuras, sí, ¿eh?";
		link.l1.go = "Cabin_fight";
		break;

	case "Cabin_fight":
		chrDisableReloadToLocation = true;										   // закрыть локацию
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
		DialogExit();
		sld = characterFromId("Marchello");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack"))
		{
			for (i = 1; i <= 3; i++)
			{
				sld = characterFromId("CyclopGuard_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "LSC_CyclopNMaryDie");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	// на улице
	case "Town":
		dialog.text = "Oh, disculpa... ¿Puedo pedirte que me ayudes?";
		link.l1 = "Hum. Siempre estoy listo para ayudar a una dama hermosa. ¿Cuál es el problema?";
		link.l1.go = "Town_1";
		break;

	case "Town_1":
		dialog.text = "Verás, compré un cofre lleno de todo tipo de piezas de metal de Sessile Gallard. Ella vive en el 'Eva'. Jurgen prometió forjarme algo bueno, sí, ¿eh?... Lo compré, aye, pero no puedo llevárselo. ¡Qué tonta soy!\nQuizás podrías ayudarme a llevar el cofre desde el 'Eva' hasta el bloque de Narwhal en el 'Esmeralda'? ¡Por favor, te estaría muy agradecida!";
		link.l1 = "¿Y eso es todo? Claro, señorita, te ayudaré. No es mucha molestia.";
		link.l1.go = "Town_2";
		break;

	case "Town_2":
		dialog.text = "¡Gracias! Te mostraré el cofre.";
		link.l1 = "Milady...";
		link.l1.go = "Town_3";
		break;

	case "Town_3":
		DialogExit();
		LAi_SetActorType(pchar);
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocator(npchar, "reload", "reload41", "LSC_EnterAevaWithMary", -1);
		LAi_ActorFollow(pchar, npchar, "", -1);
		break;

	case "Town_4":
		dialog.text = "Y aquí estamos... Ahora dime, bastardo, ¿dónde está la llave?!";
		link.l1 = "¡Vaya! Ja, parece que no se necesita ayuda... Mary.";
		link.l1.go = "Town_5";
		break;

	case "Town_5":
		dialog.text = "¿Muchacho listo, eh? ¡Menos charla, maldito seas! ¿Dónde está la llave? ¡Dámela o te arrepentirás!";
		link.l1 = "¡Qué grosera! ¡Qué mala lengua tiene una chica tan hermosa! ¿Qué llave?";
		link.l1.go = "Town_6";
		break;

	case "Town_6":
		dialog.text = "La llave que le quitaste a Adolf Barbier. Y no lo niegues, te vieron salir de su camarote. Adolf está muerto y fue obra tuya... Ahora, ¡dame la llave!";
		link.l1 = "Entonces fuiste tú después de todo... ¡Eso fue un error, chica, un error muy grande!";
		link.l1.go = "Town_7";
		break;

	case "Town_7":
		PlaySound("Voice\Spanish\LSC\Mary Casper-04.wav");
		dialog.text = "¿Qué dijiste?… ¡Maldita sea, no eres un ladrón cualquiera! ¡Él trabaja para el almirante! ¡Derríbenlo, muchachos!";
		link.l1 = "...";
		link.l1.go = "Cabin_fight";
		break;

		// ---------------------------------покушение на Акулу - вариант N --------------------------------
	case "caroline":
		dialog.text = "¡Chad, ese es él! ¡Maldita sea, ha traído un ayudante aquí! ¡Muchachos, mátenlos a todos!";
		link.l1 = "...";
		link.l1.go = "caroline_1";
		break;

	case "caroline_1":
		DialogExit();
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
		// Акулу к бою
		sld = characterFromId("Dodson");
		LAi_SetImmortal(sld, false);
		LAi_SetWarriorType(sld);
		sld.cirassId = Items_FindItemIdx("cirass1");
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		// устанавливаем 4 толстых нарвалов
		int iRank = 20 + MOD_SKILL_ENEMY_RATE * 2;
		int iScl = 65;
		for (i = 1; i <= 4; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("MaryGuard_" + i, "citiz_5" + (i + 4), "man", "man", iRank, PIRATE, -1, true, "soldier"));
			if (i == 4)
			{
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "topor_07", "pistol11", "bullet", iScl * 2);
				sld.DontClearDead = true;
				sld.SaveItemsForDead = true;
			}
			else
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl * 2);
			if (i < 3)
				ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload3");
			else
				ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload2");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		// Мэри и Чада к бою
		sld = characterFromId("Capper");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "LSC_MarynChadDie");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

		// ---------------------------------покушение на Акулу - вариант M --------------------------------
	case "mary":
		dialog.text = "Estás justo a tiempo... Nunca habría podido con ellos yo sola... ¡Uf! Para ser honesta, pensé que estaba acabada.";
		link.l1 = "¡Luchaste como una valquiria! Nunca he visto a una chica tan hermosa pelear con tanto vigor...";
		link.l1.go = "mary_1";
		break;

	case "mary_1":
		dialog.text = "Ja-ja, eres todo un caballero, ¿verdad?: haciendo cumplidos con un sable aún en la mano. Gracias por tu ayuda. ¡Me has salvado la vida, sí, ¿eh?! Preséntate, caballero, que nunca te había visto antes. ¿Eres nuevo aquí?";
		link.l1 = "Mi nombre es " + GetFullName(pchar) + ", pero las bellas damas pueden llamarme " + pchar.name + ". . ¿Soy nueva aquí? Hm... Lo soy.";
		link.l1.go = "mary_2";
		break;

	case "mary_2":
		dialog.text = "Se nota, seguramente habría notado a un hombre tan apuesto por aquí. Mi nombre es Mary, Mary Casper. Aunque me llaman Mary la Pelirroja. Es porque soy pelirroja, sí, ¿eh?";
		link.l1 = "Me alegra conocerte, Mary...";
		link.l1.go = "mary_3";
		break;

	case "mary_3":
		dialog.text = "¡Oh, estoy doblemente agradecida... considerando que habría muerto si no fuera por ti! Ese bastardo de Chad no estaba fanfarroneando. ¡Qué alimaña! Y fui una tonta por dejar las puertas inferiores abiertas. Así es como entraste, ¿verdad?";
		link.l1 = "Sí. Estaba nadando alrededor de la isla tratando de encontrar un lugar para salir, sí, ¿eh?";
		link.l1.go = "mary_4";
		break;

	case "mary_4":
		dialog.text = "Ya veo. Esta puerta sin cerrar casi me mata. Jurgen mismo forjó las cerraduras para mí, no puedes abrirlas sin la llave correcta y forzarlas no servirá. Además, no me quedaré quieta mientras alguien intenta entrar - ¡cuatro cañones de mi pistola dejarán cuatro agujeros en una puerta o en un cuerpo, ja-ja!\nPero el maldito Chad no me deja en paz. Ya ha enviado matones para 'persuadirme' de tomar su lado, definitivamente va en serio. Si no fuera por ti, habría dicho que sí. Tendré que quedarme aquí bajo asedio, sí, ¿eh?" + pchar.name + ", ¡sí, ¿eh?! Gracias a Dios que lo predije, tengo suficientes provisiones y Jurgen es mi vecino, no me peleé con él.";
		link.l1 = "Mary, ¿por qué no me cuentas más sobre tus problemas? Veo que necesitas mi ayuda, pero no entendí nada de lo que salió de tus labios.";
		link.l1.go = "mary_5";
		break;

	case "mary_5":
		dialog.text = "¡Ay, necesito ayuda, sí, ¿eh?! Ahora estoy sola. Tuve una disputa con Donald, luego resultó que Chad es un villano. Oh, lo siento, estoy parloteando otra vez. Bueno, te contaré sobre la situación en la que me encuentro...";
		link.l1 = "Ten en cuenta que soy nuevo aquí, así que todavía no entiendo mucho. ¿Quién es ese Chad que intenta 'persuadirte' o matarte? ¿Quién es Donald?";
		link.l1.go = "mary_6";
		break;

	case "mary_6":
		dialog.text = "Chad es un pirata de la tripulación del almirante Shark Dodson, un carcelero en el 'Tartarus'...";
		link.l1 = "¡Espera! ¿Qué dijiste? ¿Shark Dodson? ¿Está aquí?";
		link.l1.go = "mary_7";
		break;

	case "mary_7":
		dialog.text = "Debes haber llegado esta noche ya que no lo sabes. ¿Dónde más estaría Shark, sino aquí? Mis problemas comenzaron cuando él llegó aquí hace varios meses. Aunque, lo admito, todo esto es culpa de los Narvales y los Rivados. Cuando Shark vino aquí con su tripulación, quería establecer una base, pero a nuestra gente y a los Rivados realmente no les gustó la idea. Atacaron el bergantín de Shark por la noche y le prendieron fuego\n¡Mejor que no lo hubieran hecho! La tripulación de Shark está llena de demonios, no de hombres, sí, ¿eh? Primero, destruyeron los botes hostiles, luego desembarcaron y empezaron una verdadera masacre. Los Narvales se retiraron y los Rivados huyeron tan rápido como pudieron. Finalmente, los piratas capturaron San Agustín donde se guardan la mayoría de las provisiones y suministros de la Isla, luego tomaron el Tartarus\nShark encarceló a nuestro líder Alan Milrow, quien también era mi... mi amigo cercano, y al hechicero Rivados Chimiset. Los envió a pudrirse en las jaulas del Tartarus como bestias. Es fácil nadar hasta el Tartarus desde aquí y logré visitar a Alan unas cuantas veces. Allí conocí a Chad Kapper, Shark lo asignó como carcelero. Le pedí a Chad que liberara a Alan, le prometí dinero, pero tenía miedo de enfrentarse al almirante\nY luego Alan fue asesinado en prisión. Chad me dijo que Shark hizo esto, sí, ¿eh? Así que fui a Donald, quien fue elegido líder en lugar de Alan, y exigí atacar a los piratas de inmediato, pero se negó, dijo que esos demonios del mar eran demasiado duros para nosotros. Fue entonces cuando le dije que se fuera al diablo\nMi gente no sirvió para nada en este asunto, así que hice un trato con Kapper, la escoria quería tomar el lugar de Shark. Teníamos un plan: atraer al almirante de su fortaleza a algún lugar sombrío y matarlo allí. También encontramos a un francotirador con un buen rifle. Podía dispararle al almirante desde el mástil del Fury\nAhora la parte interesante es que, anteayer, visité el Tartarus por la noche, quería decirle algo importante a Chad sobre nuestro plan. Nadé hasta el barco y accidentalmente escuché a Chad hablando con dos Narvales. Resultó que Shark no mató a Alan. Chad lo hizo. Luego, secretamente difundió rumores sobre la implicación del almirante\nLo asesinó por mi culpa. Primero, quería tomarme como juguete en su cama. Segundo, quería usarme para deshacerse de Shark, sabía que siempre buscaría venganza. ¿Puedes imaginarlo? ¡Qué cobarde!";
		link.l1 = "Sí, ¿eh?, he conocido a tipos como él...";
		link.l1.go = "mary_8";
		break;

	case "mary_8":
		dialog.text = "¡Él es peor que un canalla! Es que… me faltan las palabras para describir a ese monstruo. Me fui esa vez, lo encontré a la mañana siguiente y le dije todo lo que pensaba de él. Sí, ¿eh? Le dije que no tendría nada que ver con su complot contra el almirante.";
		link.l1 = "Y no le gustó, obviamente... Eso fue hecho con ira, Mary. Deberías ser más cautelosa.";
		link.l1.go = "mary_9";
		break;

	case "mary_9":
		dialog.text = "No puedo, no pude mantener la boca cerrada. ¡El bastardo mató a Alan e intentó usarme para lograr sus sucios objetivos! ¡Escoria! Sí, claro, se enfadó y prometió que me arrepentiría de eso. ¡Le dije que le cortaría las pelotas y se las daría de comer a los cangrejos! \nAmenazó con enviar a sus compinches Narval detrás de mí si no cambiaba de opinión. Me reí, no pensé que un Narval se atrevería a levantarme la mano.";
		link.l1 = "   Parece que te has equivocado.   ";
		link.l1.go = "mary_10";
		break;

	case "mary_10":
		dialog.text = "Sí, ¿eh? " + pchar.name + "Subestimé a Chad y me sobreestimé a mí misma. Encontró a los bastardos que se atreverían a atacar a una chica solitaria en su propia cabaña. ¿Y qué debo hacer ahora? No puedo confiar en nadie. Ni siquiera en mi propia gente. Estos dos son Narvales, los conocía a ambos, sí, ¿eh? Mientras Chad esté vivo, estoy en peligro, sin duda enviará a más.\nTengo miedo de salir, el francotirador que encontramos para asesinar a Shark puede dispararme desde el territorio de Rivados y escapar fácilmente. No iré con Donald, no me escuchará.\n¿Almirante? ¡No puedo explicar mi papel en la preparación de su asesinato! ¡Me enviará a pudrirme en las celdas del 'Tartarus', estoy segura! Maldición, estoy atrapada. Me quedaré aquí con mis armas cargadas hasta que se acaben los suministros y luego... ¡no tengo ni idea de lo que será de mí!";
		link.l1 = "Bueno, en ese caso no tengo otra opción, más que ayudarte, sí, ¿eh? Tu situación encaja con mis planes aquí de todos modos...";
		link.l1.go = "mary_11";
		break;

	case "mary_11":
		dialog.text = "¿Tienes la intención de ayudarme? ¿Pero cómo? ¿Vas a matar a Chad?";
		link.l1 = "Esa parte del plan, seguro.";
		link.l1.go = "mary_12";
		break;

	case "mary_12":
		dialog.text = "Escucha, " + pchar.name + ", Aprecio tus intenciones, pero Chad está fuera de tu alcance. Es uno de los amigos más confiables del almirante e incluso si llegas a él, los piratas dShark te matarán, no conocen la verdad, sí, ¿eh?";
		link.l1 = "Tranquilo. Tendré que hablar con Shark de todos modos.";
		link.l1.go = "mary_13";
		break;

	case "mary_13":
		dialog.text = "¿Así que tú también eres un pirata?! Cuéntame sobre ti, mírate: irrumpiste en mi lugar, me salvaste la vida, prometiste ayudarme todo apuesto, ¡y sin embargo no sé nada de ti!";
		link.l1 = "Está bien... No soy un pirata, pero actualmente trabajo con cierto barón pirata Jan Svenson. Vine aquí para encontrar a Nathaniel Hawk. ¿Has oído hablar de él?";
		link.l1.go = "mary_14";
		break;

	case "mary_14":
		dialog.text = "No, ¿quién es él?";
		link.l1 = "Él es otro pirata famoso. Es una pena que no lo hayas conocido, debe estar aquí en algún lugar. Yo también estaba buscando al Shark, pero no esperaba encontrarlo aquí.";
		link.l1.go = "mary_15";
		break;

	case "mary_15":
		dialog.text = "¿Pero cómo llegaste aquí? Te ves demasiado bien para ser un sobreviviente de un naufragio.";
		link.l1 = "¿Y por qué pensarías que naufragué?";
		link.l1.go = "mary_16";
		break;

	case "mary_16":
		dialog.text = "Esa es la única manera de llegar aquí. Sólo Shark de alguna manera navegó hasta aquí.";
		link.l1 = "Bueno, como puedes ver, Shark no era el único.";
		link.l1.go = "mary_17";
		break;

	case "mary_17":
		dialog.text = "Entonces, ¿tienes un barco? ¡Genial!";
		link.l1 = "No te emociones tan pronto, Mary. Llegué aquí en una barca, pero se hundió hasta el fondo.";
		link.l1.go = "mary_18";
		break;

	case "mary_18":
		dialog.text = "A-ah... Bueno, como dije - un naufragio. Ahora estás atrapado aquí con nosotros, sí, ¿eh?";
		link.l1 = "Mary, déjame contarte mi plan. Mencionaste que Chad planeaba matar a Shark. Necesito a Shark vivo, Jan y yo vamos a convertirlo en el jefe de los piratas. Por eso tengo que advertirle, porque según tu historia, estoy seguro de que Chad lo intentará con o sin tu ayuda.";
		link.l1.go = "mary_19";
		break;

	case "mary_19":
		dialog.text = "Sí, probablemente. Tiene los hombres para hacerlo realidad...";
		link.l1 = "Significa que mi objetivo principal es ganarme la confianza de Shark y salvarlo. Luego, llegaré a Chad, oficialmente. ¿Tienes alguna prueba para demostrar sus intenciones?";
		link.l1.go = "mary_20";
		break;

	case "mary_20":
		dialog.text = "Tengo su carta que fue traída aquí por uno de estos... idiotas en el suelo. Hay amenazas y detalles que al almirante podrían interesarle. ¡Espera! ¿Y qué hay de mí? ¡Shark descubrirá que estaba trabajando con Chad!";
		link.l1 = "Mary, ¿vas a sentarte aquí para siempre armada con pistolas y esconder tu dulce rostro de todos? ¿De verdad piensas que soy uno de esos idiotas que quieren muerta a una hermosa dama? Muéstrame la carta primero, vamos a ver qué puedo hacer...";
		link.l1.go = "mary_21";
		break;

	case "mary_21":
		GiveItem2Character(pchar, "letter_chad_1");
		RemoveItems(npchar, "letter_chad_1", 1);
		dialog.text = "Aquí. ¿Qué opinas?";
		link.l1 = "Espera... (leyendo). Sí, parece que Chad es un tipo especial de bastardo destinado a infectar esta Tierra. Esta carta será suficiente para que Shark esté ansioso por ponerle una soga al cuello de Chad él mismo. No te preocupes, milady, me aseguraré de que Shark no sospeche nada de ti. De todos modos, estará demasiado ocupado con Chad.";
		link.l1.go = "mary_22";
		break;

	case "mary_22":
		dialog.text = "¿Lo harás? ¡Prométemelo, sí, ¿eh?! ¡Jura que no me traicionarás!";
		link.l1 = "Mary, te lo juro, no te traicionaré. No te preocupes por eso, no te salvé solo para ver que eso suceda\nChad no te dejará en paz, eso es seguro, sabes demasiado. Quédate aquí hasta que él esté muerto.";
		link.l1.go = "mary_23";
		break;

	case "mary_23":
		dialog.text = "Sí, me quedaré aquí. No quiero que me dispare un francotirador ni que me apuñalen por la espalda, sí, ¿eh?";
		link.l1 = "Buena chica. Cierra todas las puertas, incluidas las de abajo. ¿Sólo tienes una llave?";
		link.l1.go = "mary_24";
		break;

	case "mary_24":
		dialog.text = "No. Hay otro. ¿Lo quieres?";
		link.l1 = "Sí. ¿Confías en mí?";
		link.l1.go = "mary_25";
		break;

	case "mary_25":
		dialog.text = "Bueno, si el caballero que acaba de salvarme la vida me traiciona, no hay razón alguna para vivir... Tómalo.";
		link.l1 = "No temas, belleza. No te fallaré. Te veré tan pronto como resuelva este lío. Espero que no tarde mucho, sí, ¿eh?";
		link.l1.go = "mary_26";
		break;

	case "mary_26":
		GiveItem2Character(pchar, "key_mary");
		dialog.text = "Está bien, puedo mantener este lugar por unas semanas.";
		link.l1 = "Estupendo. No perderé tiempo entonces. Sacaré los cadáveres y hablaré con Shark. Está en el 'San Augustine', ¿verdad?";
		link.l1.go = "mary_27";
		break;

	case "mary_27":
		dialog.text = "Sí, él siempre está allí. Y sal de la misma manera que llegaste, no permitiré que pises la cubierta superior del 'Ceres Smithy'.";
		link.l1 = "Interesante, ¿y por qué es eso?";
		link.l1.go = "mary_28";
		break;

	case "mary_28":
		dialog.text = "Porque no podrás ayudarme si mueres. Este es el territorio de los Narvales y te matarán por ser un forastero.";
		link.l1 = "Mm... Entendido. Bueno, Mary, nos vemos. Volveré tan pronto como sea seguro, sí, ¿eh?";
		link.l1.go = "mary_29";
		break;

	case "mary_29":
		dialog.text = "Puedes verme cuando quieras, no tengo problema con eso. (risas)";
		link.l1 = "¡Adiós, hermosa!";
		link.l1.go = "mary_30";
		break;

	case "mary_30":
		DialogExit();
		LAi_SetOwnerType(npchar);
		NextDiag.CurrentNode = "mary_wait";
		npchar.greeting = "mary_3";
		AddQuestRecord("SharkHunt", "31");
		AddQuestRecordInfo("Chad_Mary_letter", "2");
		LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
		LocatorReloadEnterDisable("CeresSmithy", "reload7", false); // открываем выходы
		break;

	case "mary_wait":
		dialog.text = "Hola, " + pchar.name + ", ¿alguna buena noticia para mí? ¿Estás bien, sí, ¿eh?";
		if (pchar.questTemp.Saga.SharkHunt == "mary_whiskey")
		{
			link.l1 = "El problema con el almirante está resuelto. No tiene interés en perseguirte, la traición de Chad es lo único que le preocupa.";
			link.l1.go = "letters";
		}
		else
		{
			link.l1 = "Aún no, Mary. Pero haré todo lo que pueda.";
			link.l1.go = "exit";
		}
		NextDiag.TempNode = "mary_wait";
		break;

	case "letters":
		dialog.text = "¡Oh, gracias a Dios! Gracias, no lo olvidaré, sí, ¿eh? Al menos no hay amenaza del almirante. ¿Y qué hay de Chad? ¿Qué hizo Shark?";
		link.l1 = "Hemos convencido a los Rivados para atacarlo. Layton Dexter sacó a los guardias del 'Tartarus' y le dio la llave a Black Eddie. Los hombres de negro liberaron a su hechicero Chimiset, pero no lograron matar a Chad. Mataron a dos de sus amigos Narwhal, pero él escapó y está escondido en algún lugar.";
		link.l1.go = "letters_1";
		break;

	case "letters_1":
		dialog.text = "¡Maldita sea! Eso significa que debo ser aún más cuidadoso ahora...";
		link.l1 = "Tranquila, Mary. Estoy seguro de que tiene personas más amenazantes de las que preocuparse. Probablemente sabe quién incitó a los Rivados a atacarlo. Hará cualquier cosa por matar a Shark, no a ti.";
		link.l1.go = "letters_2";
		break;

	case "letters_2":
		dialog.text = "¿De verdad lo crees? Chad no es de los que dejan pasar las cosas tan fácilmente. Ah, estoy demasiado cansada para seguir teniendo miedo...";
		link.l1 = "Hum. No pensé que eres el tipo de dama que se asusta fácilmente.";
		link.l1.go = "letters_3";
		break;

	case "letters_3":
		dialog.text = "¡Ja! ¿Acaso no lo soy? No tengo miedo de luchar cara a cara, pero ¿sentarme en mi trasero esperando a ser asesinada? Eso sí que me da mucho miedo, sí, ¿eh?" + pchar.name + ", ¡sí, ¿eh!?...";
		link.l1 = "Confía en mí, Mary: Kapper tiene las manos llenas con el almirante en este momento... Necesito tu consejo.";
		link.l1.go = "letters_4";
		break;

	case "letters_4":
		dialog.text = "¿Mi consejo? ¿Qué tipo de consejo?";
		link.l1 = "Eddie encontró dos cartas escritas por Chad. Léelas, tal vez sepas qué está tramando. Después de todo, estabas en el plan con Chad...";
		link.l1.go = "letters_5";
		break;

	case "letters_5":
		RemoveItems(pchar, "letter_chad", 1);
		RemoveItems(pchar, "letter_chad_1", 1);
		dialog.text = "Entrégalos aquí... (leyendo). Axel es nuestro comerciante en 'Esmeralda', sí, ¿eh? Chad quería comprarle whisky por alguna razón. ¡Extraño! Chad solo bebe ron, dice que el whisky es 'el aguardiente de los campesinos'...";
		link.l1 = "¿Y qué hay de la segunda carta?";
		link.l1.go = "letters_6";
		break;

	case "letters_6":
		dialog.text = "¿Marcello? Marcello Cyclops, un antiguo cazador real. Es la razón principal por la que me niego a dejar esta cabaña.";
		link.l1 = "¿Es el francotirador que has contratado?";
		link.l1.go = "letters_7";
		break;

	case "letters_7":
		dialog.text = "Sí. Marcello puede disparar a una mosca a doce metros, a pesar de que le falta un ojo, sí, ¿eh? Su misión era abatir al Shark usando un stutzen de largo alcance desde el bauprés de la Santa Florentina, o la plataforma del Furia...";
		link.l1 = "Así que parece que Chad decidió eliminar a Shark. Pero entonces, ¿cuál es el propósito de Eva? ¿Cecille? ¿Bebidas?";
		link.l1.go = "letters_8";
		break;

	case "letters_8":
		dialog.text = "Eva es un barco neutral y Cecille es Cecille Halard, una anciana divertida que vive allí. Se mudó allí hace poco desde la Santa Florentina. Orelie Bertine es una amiga suya. Vivieron aquí juntas antes de que yo naciera, sí, ¿eh?";
		link.l1 = "Mm. Tonterías. Dos grandulones escondiéndose de una anciana para beberse un barril de whisky juntos. Tonterías... ¡No es el mejor momento para beber, Chad!";
		link.l1.go = "letters_9";
		break;

	case "letters_9":
		dialog.text = "Ya te dije que él no bebe whisky. Solo ron, algo no cuadra.";
		link.l1 = "Está bien, lo que sea. ¿Sabes dónde encontrar al Cíclope?";
		link.l1.go = "letters_10";
		break;

	case "letters_10":
		dialog.text = "No. Es muy reservado. Dispara a las aves todos los días en el anillo exterior y nadie sabe dónde duerme. A menudo visitaba Rivados antes.";
		link.l1 = "Qué mala suerte... Bueno, iré a hablar con Axel entonces. Quizás él lo entienda mejor. ¡Nos vemos, Mary! ¡Cierra la puerta!";
		link.l1.go = "letters_11";
		break;

	case "letters_11":
		dialog.text = "" + pchar.name + "¡Por favor, encuentra a Chad. Date prisa, no he dormido desde el último ataque.";
		link.l1 = "Espera, querida. Haré lo mejor que pueda.";
		link.l1.go = "letters_12";
		break;

	case "letters_12":
		DialogExit();
		NextDiag.CurrentNode = "mary_wait";
		pchar.questTemp.Saga.SharkHunt = "trader_whiskey"; // флаг на магазин - поиск виски
		AddQuestRecord("SharkHunt", "35");
		break;

	case "happy":
		dialog.text = "" + pchar.name + "¡¿Cómo llegó aquí?! ¿Vino a...";
		link.l1 = "Sí, ¿eh?, para matarte, Mary. Vino aquí a través del camarote de Jurgen y usó una cuerda para bajar aquí.";
		link.l1.go = "happy_1";
		break;

	case "happy_1":
		dialog.text = "¡Ah! ¡Soy tan tonta por haber olvidado ese camino! Chad le enseñó, estoy segura, sí, ¿eh?";
		link.l1 = "Lo más probable. Apenas lo logré. Él venía tras de ti.";
		link.l1.go = "happy_2";
		break;

	case "happy_2":
		dialog.text = "Y yo estaba durmiendo. Me habría matado en un segundo... Pero, ¿cómo supiste que él venía para acá?";
		link.l1 = "Lo hice... Acabo de hacerlo, Mary.";
		link.l1.go = "happy_3";
		break;

	case "happy_3":
		dialog.text = "Me has salvado de nuevo, guapo. Siempre llegas en el momento perfecto, sí, ¿eh? ¿Cómo lo haces?";
		link.l1 = "Bueno, no lo sé. Uno de mis muchos talentos. Tu asedio ha terminado: Chad Kapper está muerto y también todos sus amigos. Cíclope fue el último de su podrida tripulación, sí, ¿eh?";
		link.l1.go = "happy_4";
		break;

	case "happy_4":
		dialog.text = "¿De verdad? ¿Es cierto, sí, ¿eh?" + pchar.name + "¿No me estás engañando, sí, ¿eh?";
		link.l1 = "No, en absoluto. Eh, necesito descansar un poco después de los eventos de los últimos días...";
		link.l1.go = "happy_5";
		break;

	case "happy_5":
		dialog.text = "¡Por fin puedo respirar libremente ahora! Gracias... ¡Muchas gracias! Eres mi héroe, sí, ¿eh?";
		link.l1 = "Me encanta cómo suena eso, ser tu héroe, quiero decir. Solo me alegra que estés a salvo al fin, sí, ¿eh?";
		link.l1.go = "happy_6";
		break;

	case "happy_6":
		dialog.text = "¿Entonces?";
		link.l1 = "¿Qué pasa, bonita?";
		link.l1.go = "happy_7";
		break;

	case "happy_7":
		dialog.text = "¿Por qué estás ahí parado? Vamos, caballero.";
		link.l1 = "¿Y hacer qué?";
		link.l1.go = "happy_8";
		break;

	case "happy_8":
		dialog.text = "Realmente eres un caballero... Ven aquí, abrázame, bésame al fin, quieres esto, lo veo, sí, ¿eh?";
		link.l1 = "Mary...";
		link.l1.go = "happy_9";
		break;

	case "happy_9":
		DialogExit();
		LAi_Fade("LSC_MaryRomantic_1", "");
		LAi_SetActorType(npchar);
		LAi_SetActorType(pchar);
		StartQuestMovie(true, false, true);
		PlayStereoOGG("music_romantic");
		pchar.questTemp.LSC.MaryBye = "true"; // атрибут обязательного прощания перед телепортацией
		LocatorReloadEnterDisable("LostShipsCity_town", "reload62", false);
		LocatorReloadEnterDisable("LostShipsCity_town", "reload63", false); // открываем Церес снаружи
		break;

	case "happy_10":
		dialog.text = "No me dejes...";
		link.l1 = "Estoy aquí, Mary, querida...";
		link.l1.go = "happy_11";
		break;

	case "happy_11":
		dialog.text = "Todo puede esperar. El almirante puede esperar, tus piratas pueden esperar. Esta noche es solo para nosotros dos, sí, ¿eh?!";
		link.l1 = "Por supuesto...";
		link.l1.go = "happy_12";
		break;

	case "happy_12":
		dialog.text = "Y todas las noches siguientes después de eso también...";
		link.l1 = "Sí, Mary.";
		link.l1.go = "happy_13";
		break;

	case "happy_13":
		DialogExit();
		LSC_MaryLoveWaitTime();
		SetLaunchFrameFormParam("Next morning...", "", 0, 4);
		LaunchFrameForm();
		DoQuestCheckDelay("LSC_MaryRomantic_5", 4.0);
		break;

		// ----------------------------------вместе с Мэри на Церес Смити------------------------------------------
	case "LSC_love":
		if (pchar.questTemp.LSC.Mary == "return") // эта нода важнее даже ругани с нарвалами
		{
			dialog.text = "" + pchar.name + "¡ Has vuelto... sin ella. Así que no pudo apartarte de mí!";
			link.l1 = "Mary, tus sospechas eran irrazonables. Tú eres la única para mí. Siempre estuve contigo en mis pensamientos y en mis sueños.";
			link.l1.go = "adversary_hire_return";
			break;
		}
		if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
		{
			dialog.text = "" + pchar.name + ", ¿por qué estás peleando con los Narvales? Vivo en sus territorios, de hecho, soy uno de ellos por si lo has olvidado. Por favor, ve a Fazio y haz las paces, te lo ruego, sí, ¿eh?";
			link.l1 = "Está bien, Mary, haré lo que me pides, sí, ¿eh?";
			link.l1.go = "exit";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.LSC.FindDolly")) // нашёл статую - прощается
		{
			dialog.text = "" + pchar.name + ", algo te preocupa. ¿Qué pasa?";
			link.l1 = "Mary, necesito hablar contigo.";
			link.l1.go = "dolly";
			break;
		}
		if (CheckAttribute(npchar, "quest.donald"))
		{
			dialog.text = "" + pchar.name + "¡Todos los Narvales están hablando de ti!";
			link.l1 = "¿De verdad, mi amor?";
			link.l1.go = "donald";
			break;
		}
		if (CheckAttribute(npchar, "quest.talisman")) // подарок
		{
			dialog.text = "" + pchar.name + "¡Este mandoble es increíble! ¡Gracias de nuevo!.. Yo también quiero darte un regalo. Claro, no se compara con el tuyo, pero quiero que lo aceptes, sí, ¿eh?";
			link.l1 = "Mary, el valor de un regalo no importa... Gracias, mi amor";
			link.l1.go = "talisman";
			break;
		}
		if (stf(environment.time) >= 5.0 && stf(environment.time) < 10.0) // утро
		{
			dialog.text = "Tengo un día ocupado por delante, " + pchar.name + "¿Buena suerte?";
			if (CheckAttribute(npchar, "quest.narval_blade"))
			{
				link.l3 = "Mary, necesitamos ir a ver a Jurgen hoy.";
				link.l3.go = "narval";
			}
			link.l1 = "¡Gracias, Mary! No tengo ninguna duda al respecto.";
			link.l1.go = "exit";
			link.l2 = "No, Mary. Quiero descansar un poco aquí. ¿Estás de acuerdo con eso, sí, ¿eh?";
			link.l2.go = "rest_morning"; // отдых
		}
		else
		{
			dialog.text = "Bueno, " + pchar.name + ", ¿cómo te va? ¿Corriendo por la isla como de costumbre?";
			link.l1 = "Sí, Mary. Hay muchas cosas por hacer...";
			link.l1.go = "LSC_love_1";
		}
		NextDiag.TempNode = "LSC_love";
		break;

	case "LSC_love_1":
		if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) // вечер
		{
			dialog.text = "Ya es de noche, " + pchar.name + ", ¿de qué cosas estás hablando? Quédate aquí, tomemos unos tragos y relajémonos, ¡sí, ¿eh?! ¡Puede esperar hasta la mañana!";
			link.l1 = "(riendo) Por supuesto, amor, no digas más...";
			link.l1.go = "LSC_love_evening";
			if (sti(pchar.money) >= 500)
			{
				link.l2 = "¡Mary, vamos a la taberna hoy!";
				link.l2.go = "LSC_tavern";
			}
			link.l3 = "Mary, querida, estoy muy ocupado ahora. Volveré un poco más tarde.";
			link.l3.go = "LSC_love_2";
			break;
		}
		if (stf(environment.time) >= 10.0 && stf(environment.time) < 18.0) // день
		{
			dialog.text = "No olvides visitarme por la tarde. Y ni se te ocurra evitarme, sí, ¿eh?";
			if (CheckAttribute(npchar, "quest.narval_blade"))
			{
				link.l3 = "Mary, tenemos que ir a ver a Jurgen hoy.";
				link.l3.go = "narval";
			}
			link.l1 = "Claro, Mary, ¿cómo podría? Seguro que te visitaré.";
			link.l1.go = "exit";
			link.l2 = "No, Mary. Quiero descansar aquí esta noche. ¿Te parece bien, sí, ¿eh?";
			link.l2.go = "rest_afternoon"; // отдых
			NextDiag.TempNode = "LSC_love";
			break;
		}
		dialog.text = "¿De qué estás hablando? ¡Ya es de noche! No, no vas a ninguna parte, te quedarás aquí, conmigo, sí, ¿eh?";
		link.l1 = "(riendo) como quieras, cariño...";
		link.l1.go = "LSC_love_night";
		NextDiag.TempNode = "LSC_love";
		break;

	case "LSC_love_2":
		dialog.text = "No siquiera...";
		link.l1 = "¡Vaya, eres todo un caballero: apenas guardaste tu sable y ya me colmas de halagos. Muchas gracias por tu ayuda. De verdad me has salvado, sí, ¿eh? Preséntate, por favor, caballero, que es la primera vez que te veo. ¿Llevas mucho tiempo en la isla?";
		link.l1.go = "exit";
		NextDiag.TempNode = "LSC_love";
		break;

	// сходить в таверну
	case "LSC_tavern":
		dialog.text = LinkRandPhrase("Una gran idea, " + pchar.name + "¡De acuerdo, sí, ¿eh?! ¡Estoy de acuerdo!", "¡Aye, vamos, sí, ¿eh?" + pchar.name + "¡Sancho tiene una excelente colección de vinos, hay mucho de donde elegir!", "¡Oh, me encantaría, sí, ¿eh?! Siempre es divertido en la taberna de Sancho y tiene una gran selección de vinos.");
		link.l1 = "¡Vamos!";
		link.l1.go = "LSC_love_tavern";
		break;

	// --> отдых
	case "rest_morning":
		dialog.text = "Por supuesto, " + pchar.name + "¿Seguro, descansa un poco, sí, ¿eh?";
		link.l1 = "Me quedaré hasta el mediodía...";
		link.l1.go = "rest_day";
		link.l2 = "Me quedaré hasta la noche...";
		link.l2.go = "rest_evening";
		break;

	case "rest_afternoon":
		dialog.text = "Por supuesto, " + pchar.name + "¿Seguro, descansa un poco, sí, ¿eh?";
		link.l1 = "Me quedaré hasta la noche...";
		link.l1.go = "rest_evening";
		break;

	case "rest_day":
		DialogExit();
		iTime = sti(environment.time);
		iAddTime = 13 - iTime;
		WaitDate("", 0, 0, 0, iAddtime, 5);
		RecalculateJumpTable();
		LAi_Fade("", "");
		if (CheckAttribute(pchar, "questTemp.LSC.MaryBye"))
			NextDiag.CurrentNode = "LSC_love";
		else
			NextDiag.CurrentNode = "LSC_love_3";
		break;

	case "rest_evening":
		DialogExit();
		iTime = sti(environment.time);
		iAddTime = 18 - iTime;
		WaitDate("", 0, 0, 0, iAddtime, 5);
		RecalculateJumpTable();
		LAi_Fade("", "");
		if (CheckAttribute(pchar, "questTemp.LSC.MaryBye"))
			NextDiag.CurrentNode = "LSC_love";
		else
			NextDiag.CurrentNode = "LSC_love_3";
		break;
		// <-- отдых

		//--> если скоро уходит через портал
	case "LSC_love_3":
		if (pchar.questTemp.LSC.Mary == "return") // эта нода важнее даже ругани с нарвалами
		{
			dialog.text = "" + pchar.name + "¡Has vuelto... sin ella. Así que no pudo llevarte lejos de mí!";
			link.l1 = "Mary, tus sospechas eran infundadas. Eres la única para mí. Siempre estuve contigo en mis pensamientos y en mis sueños.";
			link.l1.go = "adversary_hire_return";
			break;
		} // 291112
		if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
		{
			dialog.text = "" + pchar.name + ", ¿por qué estás luchando con los narvales? Vivo en sus territorios, de hecho, soy uno de ellos, por si lo olvidaste. Por favor, ve a Fazio y haz las paces, te lo suplico.";
			link.l1 = "Está bien, Mary, haré lo que me pides, sí, ¿eh?";
			link.l1.go = "exit";
			break;
		}
		if (CheckAttribute(npchar, "quest.talisman")) // подарок
		{
			dialog.text = "" + pchar.name + "¡Este alfanje es increíble! Gracias de nuevo!.. Quiero darte un regalo también. Por supuesto, no se compara con el tuyo en valor, pero quiero que lo aceptes, sí, ¿eh?";
			link.l1 = "Mary, el valor de un regalo no importa... Gracias, mi amor";
			link.l1.go = "talisman";
			break;
		}
		if (stf(environment.time) >= 5.0 && stf(environment.time) < 10.0) // утро
		{
			dialog.text = "¿Ya te vas, sí, ¿eh?" + pchar.name + "¿Buena suerte y no te olvides de mí, sí, ¿eh?";
			if (CheckAttribute(npchar, "quest.narval_blade"))
			{
				link.l3 = "Mary, deberíamos ir a ver a Jurgen hoy.";
				link.l3.go = "narval";
			}
			link.l1 = "Por supuesto, Mary.";
			link.l1.go = "exit";
			link.l2 = "No, Mary. Quiero descansar un poco aquí. ¿Te parece bien?";
			link.l2.go = "rest_morning"; // отдых
		}
		else
		{
			dialog.text = "¿No vas a tu cosa de Kukulcán, sí, ¿eh?" + pchar.name + "?";
			link.l1 = "Todavía no, aún preparándome.";
			link.l1.go = "LSC_love_4";
		}
		NextDiag.TempNode = "LSC_love_3";
		break;

	case "LSC_love_4":
		if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) // вечер
		{
			dialog.text = "Ya es de noche, " + pchar.name + "¿Por qué no te quedas aquí? Quiero estar contigo.";
			link.l1 = "Está bien, cariño, me quedo...";
			link.l1.go = "LSC_love_evening";
			if (sti(pchar.money) >= 500)
			{
				link.l2 = "¡Mary, vamos a la taberna hoy!";
				link.l2.go = "LSC_tavern";
			}
			break;
		}
		if (stf(environment.time) >= 10.0 && stf(environment.time) < 18.0) // день
		{
			dialog.text = "Buena suerte y no te olvides de mí... Ven a verme por la noche si puedes, sí, ¿eh?";
			if (CheckAttribute(npchar, "quest.narval_blade"))
			{
				link.l3 = "Mary, deberíamos ver a Jurgen hoy.";
				link.l3.go = "narval";
			}
			link.l1 = "Muy bien, querida.";
			link.l1.go = "exit";
			link.l2 = "Mary, quiero descansar un poco aquí. ¿Estás de acuerdo con eso, sí, ¿eh?";
			link.l2.go = "rest_afternoon"; // отдых
			NextDiag.TempNode = "LSC_love_3";
			break;
		}
		dialog.text = "¿De qué estás hablando? ¡Es de noche! No, no vas a ninguna parte, te quedarás aquí, sí, ¿eh?";
		link.l1 = "(riendo) Está bien, me quedaré...";
		link.l1.go = "LSC_love_night";
		NextDiag.TempNode = "LSC_love_3";
		break;
		// <-- скоро уходит через портал

		// --> взаимоотношения - секс и прочее
	case "LSC_love_tavern":
		DialogExit();
		sld = ItemsFromID("potionrum");
		sld.shown = true;
		sld.startLocation = "FleuronTavern";
		sld.startLocator = "bottle";
		DoQuestReloadToLocation("FleuronTavern", "quest", "sit2", "LSC_MaryTavern");
		break;

	case "LSC_love_evening":
		DialogExit();
		// if(CheckAttribute(PChar, "IsMushketer")) SetMainCharacterToMushketer("", false);
		LSC_MaryEveneng();
		break;

	case "LSC_love_night":
		DialogExit();
		LSC_MaryLove();
		break;

	case "LSC_love_morning":
		if (CheckAttribute(npchar, "quest.hire"))
		{
			dialog.text = "Capitán " + pchar.name + "¡La oficial Mary Casper está lista para servir bajo tu mando!";
			link.l1 = "¡Bien hecho, oficial! Te ordeno que subas a bordo del barco inmediatamente. Pero primero: ¡besa a tu capitán!";
			link.l1.go = "LSC_mary_hire";
		}
		else
		{
			dialog.text = "Eso fue increíble, amor... ¡Buenos días!";
			link.l1 = "¡Buenos días, cariño! ¡Eres maravilloso!";
			link.l1.go = "LSC_love_morning_1";
		}
		break;

	case "LSC_love_morning_1":
		DialogExit();
		LAi_SetOwnerType(npchar);
		if (CheckAttribute(pchar, "questTemp.LSC.MaryBye"))
			NextDiag.CurrentNode = "LSC_love";
		else
			NextDiag.CurrentNode = "LSC_love_3";
		break;
	// <-- взаимоотношения

	// стал другом нарвалам
	case "donald":
		dialog.text = "¿Has hablado con Donald? ¿Es cierto que el almirante quería aliarse con Rivados y luchar contra los Narvales? ¿Es cierto que lo has disuadido de ello? Habrá paz entre los piratas y los Narvales, ¿verdad?";
		link.l1 = "Sí, Mary. Así es.";
		link.l1.go = "donald_1";
		break;

	case "donald_1":
		dialog.text = "" + pchar.name + ", me faltan las palabras... También dicen que Donald te considera un amigo. Podrías convertirte en uno de los Narwhals, sí, ¿eh?";
		link.l1 = "Ve a ver a Donald cuando puedas, él también quiere hacer las paces contigo. Te pide que lo perdones por sus palabras y por no haber podido protegerte de esos dos bastardos.";
		link.l1.go = "donald_2";
		break;

	case "donald_2":
		dialog.text = "¡Al diablo con Donald! Aunque me alegra escuchar eso, por supuesto. Lo veré. ¡Pero tú! Yo... no, no así... Estoy orgullosa de ti, sí, ¿eh?";
		link.l1 = "¡Santo cielo, Mary... tú eres... ah, haces que mi corazón se acelere!";
		link.l1.go = "exit";
		NextDiag.TempNode = "LSC_love";
		DeleteAttribute(npchar, "quest.donald");
		break;

	// ноды прощания
	case "dolly":
		dialog.text = "¡Hablemos! ¿Estás en problemas?";
		link.l1 = "No. Mary, ¿recuerdas la noche en que nos conocimos? Después de que lidiamos con esos dos bastardos, te dije que había llegado aquí en un barco.";
		link.l1.go = "dolly_1";
		break;

	case "dolly_1":
		dialog.text = "Recuerdo, sí. Tu barca se hundió y tuviste que nadar hasta aquí... ¡sí, ¿eh?!";
		link.l1 = "Mentí. Habrías pensado que estoy loca si te hubiera dicho la verdad entonces. No había ninguna barca. Usé una fuerza inexplicable de un dios indio 'Kukulcán' para llegar a este lugar.";
		link.l1.go = "dolly_2";
		break;

	case "dolly_2":
		dialog.text = "" + pchar.name + "... ¿De qué estás hablando? ¿Kukulcán?";
		link.l1 = "Mary, querida, debes creerme, porque no hay nada racional en ello, y no puedo compartir esto con nadie más que contigo. Nathaniel Hawk desapareció al tocar el ídolo indio, lo estaban persiguiendo y eso lo salvó...";
		link.l1.go = "dolly_3";
		break;

	case "dolly_3":
		dialog.text = "";
		link.l1 = "Estaba buscando a Nathaniel. Hablé con un chamán indio y tuve que hacer lo mismo que Hawk. Me teletransporté dentro de la bodega de carga del 'San Augustine', salí por un agujero en su casco, y el destino me trajo hasta ti.";
		link.l1.go = "dolly_4";
		break;

	case "dolly_4":
		dialog.text = "¿Se supone que esta es una historia divertida de nuestro primer encuentro, que contaremos a nuestros hijos algún día? ¿O te has vuelto loco?";
		link.l1 = "Lo digo en serio, Mary. Entiendo que sea difícil de creer, y debe parecerte una locura, pero por favor, confía en mí.";
		link.l1.go = "dolly_5";
		break;

	case "dolly_5":
		dialog.text = "Parece que las historias de Eric eran ciertas...";
		link.l1 = "¿Quién es Eric? ¿Y qué te dijo?";
		link.l1.go = "dolly_6";
		break;

	case "dolly_6":
		dialog.text = "Eric era uno de los lugareños, un viejo marinero. Ya está muerto. Cuando era niña, solía contarme historias sobre un ídolo dorado, un santuario donde los Rivados sacrificaban hombres. Aquí, en la Isla\nAquellos que lo tocaban, desaparecían y nunca más se les volvía a ver. Pensé que eran solo cuentos, destinados a asustar a los niños.";
		link.l1 = "Es verdad, Mary. Eric no estaba mintiendo.";
		link.l1.go = "dolly_7";
		break;

	case "dolly_7":
		dialog.text = "Afortunadamente, el barco con ese ídolo terrible se había hundido. Nunca lo he visto con mis propios ojos.";
		link.l1 = "Lo he encontrado, descansando en el fondo.";
		link.l1.go = "dolly_8";
		break;

	case "dolly_8":
		dialog.text = "¿Te zambulliste allí? ¿Te dio ese maldito inventor Vedecker su traje? ¡Hay cangrejos arrastrándose por ahí, sí, ¿eh?! ¡Maldito! ¡poniéndote en peligro de esa manera!";
		link.l1 = "Mary, no te preocupes por mí. Puedo lidiar con los monstruos. No son tan amenazantes como dicen. He estado buscando la estatua desde mi primer día en esta isla y, por fin, la he encontrado.";
		link.l1.go = "dolly_9";
		break;

	case "dolly_9":
		dialog.text = "¿Y qué pasará ahora?";
		link.l1 = "Esta es la única salida de aquí. Llegué a este lugar a través de un ídolo como este, y lo usaré de nuevo para regresar... ¡Mary! ¿Estás llorando? ¡Mary! ¡Deja eso!";
		link.l1.go = "dolly_10";
		break;

	case "dolly_10":
		if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
			sTemp = "Shark, ";
		else
			sTemp = "";
		dialog.text = "¿Por qué debería? Lloraré, quiero llorar, sí, ¿eh?... (sollozando) ¡Estas cosas siempre les pasan a mis hombres! ¡Estaré sola otra vez!";
		link.l1 = "¿Qué crees que me pasará? ¿De verdad piensas que te dejaría aquí?! Volveré por ti, en un barco. Necesito llevarte tanto a ti como a " + sTemp + "Nathaniel vuelve conmigo. ¿Me seguirás al mundo exterior?";
		link.l1.go = "dolly_11";
		break;

	case "dolly_11":
		dialog.text = "(entre lágrimas) Por supuesto... Claro, lo haré... Volverás por mí, ¿sí, eh? ¿Cómo demonios planeas regresar a la isla? Solo Shark sabe cómo navegar hasta aquí. Y no te atrevas a olvidarte de mí, o te daré una paliza cuando te encuentre, ¿sí, eh?";
		link.l1 = "¡Mary, basta ya con esos pensamientos alocados tuyos! Por supuesto que volveré por ti, ¿quién más mantendrá mi corazón latiendo de la misma manera desde el día en que te conocí? No te preocupes, mi amor, Shark me ha compartido las coordenadas y las indicaciones. Encontraré el camino hacia ti.";
		link.l1.go = "dolly_12";
		break;

	case "dolly_12":
		dialog.text = "Has dicho que una estatua te ha traído aquí directamente desde el continente, pero ¿y si esta estatua te lleva a otra parte, a África quizás? ¿Qué haré yo sin ti entonces, sí, ¿eh?!";
		link.l1 = "Kukulcan es un dios indio, me llevará a algún lugar dentro del Caribe o el continente. Solo necesito encontrar un asentamiento, luego será fácil para mí encontrar mi barco y tripulación.";
		link.l1.go = "dolly_13";
		break;

	case "dolly_13":
		dialog.text = "(llora) Prométeme... no, júrame que volverás, sí, ¿eh?";
		link.l1 = "Mary, querida, te juro que regresaré. Y te sacaré de este maldito lugar. No necesitas extrañarme por mucho tiempo. Basta de lágrimas, sí, ¿eh?";
		link.l1.go = "dolly_14";
		break;

	case "dolly_14":
		dialog.text = "Está bien, " + pchar.name + "... ... Vuelve a mí, te estaré esperando, sí, ¿eh? ¿Cuándo te vas a ir?";
		link.l1 = "No lo sé aún. Necesito prepararme primero, luego bucearé y tocaré la estatua. Te dirán que me he ahogado - no les creas. Todo estará bien.";
		link.l1.go = "dolly_15";
		break;

	case "dolly_15":
		dialog.text = "Lo entiendo. " + pchar.name + ", querida, abrázame... Bésame...";
		link.l1 = "Mary... Mi querida Mary...";
		link.l1.go = "dolly_16";
		break;

	case "dolly_16":
		DialogExit();
		DeleteAttribute(pchar, "questTemp.LSC.MaryBye"); // можно телепортироваться
		DeleteAttribute(pchar, "questTemp.LSC.FindDolly");
		SetMusic("music_romantic");
		SetLaunchFrameFormParam("", "", 0, 15);
		SetLaunchFrameFormPic("loading\inside\kiss.tga");
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 1, 10); // крутим время
		RecalculateJumpTable();
		NextDiag.CurrentNode = "LSC_love_3";
		npchar.greeting = "mary_5";
		break;

	// дарим Мэри палаш Нарвал
	case "narval":
		dialog.text = "¿Jurgen? ¿Por qué?";
		link.l1 = "Lo verás. Esto va a ser una agradable sorpresa.";
		link.l1.go = "narval_1";
		break;

	case "narval_1":
		dialog.text = "¡Oh, qué interesante! ¿Agradable? ¡Esto es genial, sí, ¿eh?! ¡Vayamos, antes de que muera de curiosidad!";
		link.l1 = "Te va a gustar, estoy segura. ¡Vamos!";
		link.l1.go = "narval_2";
		break;

	case "narval_2":
		DialogExit();
		NextDiag.CurrentNode = "narval_wait";
		LocatorReloadEnterDisable("CeresSmithy", "reload6", true);
		LocatorReloadEnterDisable("CeresSmithy", "reload7", true);
		pchar.quest.LSC_PresentMary.win_condition.l1 = "ExitFromLocation";
		pchar.quest.LSC_PresentMary.win_condition.l1.location = pchar.location;
		pchar.quest.LSC_PresentMary.function = "LSC_GotoPresentMary";
		break;

	case "narval_wait":
		dialog.text = "Vamos, " + pchar.name + "¡";
		link.l1 = "Seguro...";
		link.l1.go = "exit";
		NextDiag.TempNode = "narval_wait";
		break;

	case "narval_3":
		dialog.text = "Pues, " + pchar.name + ", ¿qué sorpresa tienes para mí?";
		link.l1 = "¡Mary! Jurgen y yo decidimos hacerte un regalo de parte de ambos. Esta es una hoja única, una espada ancha que lleva el nombre de Narval. Solo hay dos espadas así en el mundo: la primera fue propiedad de Alan Milrow, esta será tuya. Está hecha de un acero especial, forjada con el toque magistral de Jurgen, que nunca se desafilará ni se oxidará.";
		link.l1.go = "narval_4";
		break;

	case "narval_4":
		DialogExit();
		LAi_SetActorType(pchar);
		SetMainCharacterIndex(GetCharacterIndex("Schmidt"));
		PChar = GetMainCharacter();
		LAi_SetPlayerType(PChar);
		sld = characterFromId("Mary");
		sld.dialog.currentnode = "narval_5";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;

	case "narval_5":
		dialog.text = "";
		link.l1 = "Querida nuestra... Todos los Narvales saben cuánto has sufrido. Supongo que mereces llevar este alfanje, un símbolo del clan Narval. Llénate de orgullo al portarlo. Esta espada será una amenaza para tus enemigos y te protegerá en la batalla.";
		link.l1.go = "narval_6";
		break;

	case "narval_6":
		PlaySound("interface\important_item.wav");
		sld = characterFromId("Mary");
		RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
		RemoveItems(sld, "blade_17", 1);
		sTemp = GetBestGeneratedItem("blade_31");
		GiveItem2Character(sld, sTemp);
		EquipCharacterbyItem(sld, sTemp);
		sld = characterFromId("Blaze");
		dialog.text = "¿Jurgen? ¿Esto... es para mí?...";
		link.l1 = "Sí, ¿eh? Mary. " + sld.name + "me pidió que la hiciera para ti, y trajo un hierro único del fondo del mar, ningún acero igualará el peso ni la fuerza de este material. He puesto mi alma en esta espada, tal como lo hice una vez con la de Alan.";
		link.l1.go = "narval_7";
		break;

	case "narval_7":
		dialog.text = "No sé qué decir... ¡Gracias, Jurgen! ¡Gracias, sí, ¿eh?! Lo llevaré con orgullo y estaré a la altura del valor de la espada, lo juro, sí, ¿eh?! No he estado entrenando lo suficiente con espadas anchas, pero ahora entrenaré duro, sí, ¿eh?";
		link.l1 = "De eso no tengo duda, muchacha.";
		link.l1.go = "narval_8";
		break;

	case "narval_8":
		DialogExit();
		LAi_SetStayType(pchar);
		SetMainCharacterIndex(GetCharacterIndex("Blaze"));
		PChar = GetMainCharacter();
		LAi_SetPlayerType(PChar);
		sld = characterFromId("Mary");
		sld.dialog.currentnode = "narval_9";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;

	case "narval_9":
		dialog.text = "" + pchar.name + "... espera, no... ¡Eres el mejor hombre que he conocido! ¡Eres increíble, sí, ¿eh?! ¿Sabes cuánto significa esto para mí? ¡Esta espada es el mejor regalo que podría haber recibido jamás! Ya has hecho tanto por mí, me has salvado la vida dos veces, y aún así no dejas de sorprenderme. ¡Gracias, mi amor!";
		link.l1 = "No podría haber sido de otra manera, Mary. ¡Seguiré sorprendiéndote cada día, hasta mi último aliento! Tu sonrisa me trae alegría y me alegra que te guste el regalo.";
		link.l1.go = "narval_10";
		break;

	case "narval_10":
		dialog.text = "(se ríe) ¡Gracias! ¡Qué hoja tan maravillosa, sí, ¿eh? Se necesita una mano firme para blandirla... ¡No puedo esperar para empezar a entrenar con ella!";
		link.l1 = "No veo problema. ¡Apresúrate a tu camarote y prueba tu nuevo espadón!";
		link.l1.go = "narval_11";
		break;

	case "narval_11":
		dialog.text = "Eso es lo que voy a hacer. ¡Gracias de nuevo, caballero!" + pchar.name + " ... Ven a verme esta noche, cuando estés listo... (risitas) ";
		link.l1 = "Por supuesto, mi señora. Te veré por la noche.";
		link.l1.go = "narval_12";
		break;

	case "narval_12":
		DialogExit();
		EndQuestMovie();
		sld = characterFromId("Schmidt");
		sld.dialog.currentnode = "Jurgen";
		DeleteAttribute(sld, "quest.narval_blade");
		DeleteAttribute(npchar, "quest.narval_blade");
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload2", "CeresSmithy", "goto", "goto10", "LSC_MaryReturnNormal", -1);
		LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
		LocatorReloadEnterDisable("CeresSmithy", "reload7", false); // открываем проход через трюм
		// владение Нарвалом повышает скилл ТО у Мэри и открывает перк тяжелой руки
		SetSelfSkill(npchar, 95, 50, 90, 90, 50);
		SetCharacterPerk(npchar, "HardHitter");
		npchar.quest.talisman = "true";
		npchar.quest.blade31 = "true";
		break;

	// Мэри дарит талисман
	case "talisman":
		dialog.text = "Aquí, mira. Lo encontré en uno de los barcos en el anillo exterior dentro del cofre de un capitán. Cada marinero experimentado dice que este objeto es extremadamente valioso para un navegante, puede proteger un barco de las peores tormentas. Algunos incluso estaban ansiosos por comprarlo, pero no lo he vendido... Quiero que tengas este amuleto, cariño. Úsalo para mantenerte seguro en el mar.";
		link.l1 = "¡Gracias, Mary! Muy considerado de tu parte, ¡te amo!";
		link.l1.go = "talisman_1";
		break;

	case "talisman_1":
		GiveItem2Character(pchar, "talisman2");
		PlaySound("interface\important_item.wav");
		Log_Info("Has recibido un talismán de 'Jonás'");
		dialog.text = "¿De verdad? ¿Te gusta? ¡Oh, eso es genial! Estoy tan contenta, sí, ¿eh?";
		link.l1 = "Este es un talismán muy raro y valioso. ¡Por supuesto que me gusta! ¡Gracias, querido!";
		link.l1.go = "talisman_2";
		break;

	case "talisman_2":
		DialogExit();
		DeleteAttribute(npchar, "quest.talisman");
		break;

		// --------------------------------------вернулся на Остров---------------------------------------------
	case "return":
		dialog.text = "" + pchar.name + "... Has vuelto. He estado esperándote, mirando al horizonte todos los días, sí, ¿eh? Has regresado a mí...";
		link.l1 = "Sí, ¿eh? Mary. Estoy aquí como lo prometí. ¡Deja que te abrace, querida!";
		link.l1.go = "return_1";
		break;

	case "return_1":
		dialog.text = "Ah, " + pchar.name + "¡Ni te imaginas cómo me sentí! Los narvales hablaban de tu muerte, decían que te habías ahogado. Todos estaban seguros de que estabas muerto. Yo seguía diciéndoles que estabas vivo... Por supuesto, nadie me creía, pensaban que me había vuelto loca después de todo lo que ha pasado.";
		link.l1 = "Mary... ¡Querida mía! ¿Qué te pasa? Estás temblando... ¿Tienes frío?";
		link.l1.go = "return_2";
		break;

	case "return_2":
		dialog.text = "No, no tengo frío. Es sólo que... no quiero hablar de eso aquí. Ven a mi camarote cuando termines. Quiero estar contigo a solas, sí, ¿eh? ¿No vas a ver al almirante y a Nathaniel ahora?";
		link.l1 = "Sí. Tengo que hablar con Shark y, por supuesto, llevar a Danielle a Nathaniel. No tomará mucho tiempo. Te veré pronto, Mary.";
		link.l1.go = "return_3";
		break;

	case "return_3":
		dialog.text = "Estoy deseando... verte. Ven lo antes posible, sí, ¿eh?";
		link.l1 = "...";
		link.l1.go = "return_4";
		break;

	case "return_4":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload62", "CeresSmithy", "goto", "goto11", "LSC_MaryWaitInCabin", 20.0);
		break;

	case "adversary":
		dialog.text = "" + pchar.name + "¡Por fin. Tenemos que hablar, sí, ¿eh?";
		link.l1 = "¿Qué sucede, Mary? ¡Veo que algo te preocupa! ¿Qué pasó?";
		link.l1.go = "adversary_1";
		break;

	case "adversary_1":
		dialog.text = "Ella sucedió... " + pchar.name + ", ¿quién es esa ramera en tu barco?";
		link.l1 = "¿Quién? ¿Hablas de Danielle? Pero ya sabes...";
		link.l1.go = "adversary_2";
		break;

	case "adversary_2":
		dialog.text = "No, no Danielle. Quiero decir a esa rubia, apenas cubierta con ropa, que está paseando por la cubierta de tu barco. ¡La vi a través del catalejo, sí, ¿eh?";
		link.l1 = "¡A-ah! Esa es Helen McArthur. Ella está involucrada en esta extraña historia al igual que Danielle. Ella está sirviendo como mi oficial. Temporalmente, por supuesto.";
		link.l1.go = "adversary_3";
		break;

	case "adversary_3":
		dialog.text = "¿Oficial? ¡¿Ella es una oficial?!";
		link.l1 = "Bueno, sí. ¿Qué hay de malo en eso?.. ¡Mary, maldita sea! ¡Estás celosa!";
		link.l1.go = "adversary_4";
		break;

	case "adversary_4":
		dialog.text = "¿Qué pensaste?... (entre lágrimas) Te estuve esperando todo este tiempo, no dormí por tu culpa, y te atreves a volver aquí con alguna bruja...";
		link.l1 = "¡Mary! ¡Deja de llorar! ¿Qué te pasa? Puedes destripar a cualquier hombre sin vacilar, pero tus ojos siempre están llorosos... Mary, querida, Helen es solo una oficial, sirviendo temporalmente hasta que se haga justicia y nuestros objetivos comunes se logren, nada más.";
		link.l1.go = "adversary_5";
		break;

	case "adversary_5":
		if (CheckAttribute(npchar, "quest.blade31"))
		{
			sTemp = "He estado entrenando duro con la espada ancha que me diste, y en tu ausencia la he dominado a la perfección.";
			notification("Heavy Weapons +", "Mary");
		}
		else
			sTemp = "He estado entrenando duro con estoques y los domino a la perfección.";
		dialog.text = "(llorando) Oficial... Entonces yo también quiero ser tu oficial, ¡sí, ¿eh?! ¡Puedo luchar, lo sabes!" + sTemp + " ¡Y disparo bien! Puede que no tenga habilidades navales, pero aprendo rápido, tengo talento, sí, ¿eh?";
		// проход первый - ГГ либо соглашается, либо нет, отказ ведет к полному разрыву
		link.l1 = "(de acuerdo) Mary... Quería ofrecerte el puesto yo mismo. ¡No hay mejor, más hábil y fogosa doncella que tú! ¡Te quiero a mi lado!";
		link.l1.go = "adversary_hire";
		link.l2 = "(negar) ¡Mary! ¡Ser oficial abordo es demasiado peligroso! No entiendes lo que estás pidiendo. No puedo arriesgar tu vida.";
		link.l2.go = "adversary_fail";
		break;

	// отказ
	case "adversary_fail":
		dialog.text = "¿No puedes? ¿Así que esa rubia zorra puede ser oficial y yo no? Me estás mintiendo, sí, ¿eh?" + pchar.name + ", ¡simplemente no quieres estar conmigo! (llorando) ¿Es esa chica mejor que yo, sí, ¿eh?";
		link.l1 = "¡Mary, no entiendes!";
		link.l1.go = "adversary_fail_1";
		break;

	case "adversary_fail_1":
		dialog.text = "¡Lo hago! ¡Vi sus ojos brillantes puestos en ti! Ella no es solo una oficial, sí, ¿eh? Lo entiendo (sollozando). Por supuesto, no puedo competir con ella - sabe cómo manejar un barco...";
		link.l1 = "¡Mary, de qué estás hablando!";
		link.l1.go = "adversary_fail_2";
		break;

	case "adversary_fail_2":
		dialog.text = "Se acabó... (llorando) ¡Vete! ¡Vete con tu ramera! Y yo me quedaré aquí... ¡No me voy a ninguna parte! ¡Dame mi llave!";
		link.l1 = "Pero Mary...";
		link.l1.go = "adversary_fail_3";
		break;

	case "adversary_fail_3":
		RemoveItems(pchar, "key_mary", 1);
		dialog.text = "Vete...";
		link.l1 = "¡Hola, marinero! Me alegra verte por aquí, sí, ¿eh?";
		link.l1.go = "adversary_fail_4";
		break;

	case "adversary_fail_4": // обидел Мэри - больше от неё ничего не получишь
		DialogExit();
		LAi_CharacterDisableDialog(npchar); // запрет диалога
		for (i = 0; i <= 3; i++)
		{
			LocatorReloadEnterDisable("LostShipsCity_town", "reload6" + i, true); // закрываем вход к Мэри
		}
		DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload62", "");
		pchar.questTemp.LSC.Mary = "fail";
		AddQuestRecord("LSC", "23");
		bQuestDisableMapEnter = false;				   // открыть карту
		DeleteAttribute(pchar, "GenQuest.CannotWait"); // можно мотать время
		break;

	// соглашаемся
	case "adversary_hire":
		// проход второй - смотрим, Элен может стать подругой или нет
		bOk = (CheckAttribute(pchar, "questTemp.HelenDrinking.GaveCutlass")) && (sti(pchar.questTemp.Saga.HelenRelation) >= 6);
		if (bOk || sti(pchar.questTemp.Saga.HelenRelation) >= 5 || CharacterIsAlive("Longway"))
		{
			dialog.text = "¿De verdad? ¿Realmente me querías como tu oficial, sí, ¿eh?" + pchar.name + ", ¡maldita sea, no puedes imaginar lo feliz que estoy! Quiero ser tu oficial tanto... pero no en el mismo barco con esa rubia, sí, ¿eh?";
			link.l1 = "¡Mary, pero por qué, sí, ¿eh?!";
			link.l1.go = "adversary_hire_no";
		}
		else
		{
			dialog.text = "¿De verdad? ¿De verdad me querías como tu oficial, sí, ¿eh?" + pchar.name + ", ¡maldita sea, no te imaginas lo feliz que estoy! Lo juro, no te defraudaré, ¡ya verás!";
			link.l1 = "Jesús, Mary, querida, eres un tesoro. Hace un minuto llorabas y ahora tu rostro brilla. Y, Mary, no eres solo otro oficial para mí. Eres más que eso y dudo que puedas, de alguna manera, decepcionarme, sí, ¿eh?";
			link.l1.go = "adversary_hire_yes";
		}
		break;

	case "adversary_hire_no": // Мэри не пойдёт, пока не ГГ не расстанется с Элен. Выбирай, кто тебе милее...
		dialog.text = "Puede que solo la consideres como tu oficial, aunque dudo que ella solo te vea como su capitán. Vi las miradas que te daba, conozco esa mirada, ¡sí, ¿eh?! ¡Solo yo puedo darte esas miradas!";
		link.l1 = "Mary, querida, pero ya te he dicho, no tengo sentimientos por ella, ¡y eso es todo! ¡No hay nada entre nosotros! ¡Lo juro, maldita sea! Necesito su ayuda para lidiar con el lío dentro de la Hermandad de la Costa. Jan Svenson no me ayudará a capturar Tortuga si no la ayudo, ¡y lo necesito!";
		link.l1.go = "adversary_hire_no_1";
		break;

	case "adversary_hire_no_1":
		dialog.text = "" + pchar.name + "Sí, ¿eh?, querido, abrázame... Lo siento. Te creo. Pero no podré quedarme cerca de ella y verla intentar coquetear contigo, sí, ¿eh? ¡Eventualmente tomaré mi espada y la partiré en dos!";
		link.l1 = "Sí, ¿eh? Definitivamente puedes hacer eso... Tienes bastante temperamento, ¿eh?";
		link.l1.go = "adversary_hire_no_2";
		break;

	case "adversary_hire_no_2":
		dialog.text = "Y si la mato, me dejarás, sí, ¿eh?... Nunca me lo perdonaría.";
		link.l1 = "¿Qué propones entonces, Mary? ¿Qué debo hacer con ella?";
		link.l1.go = "adversary_hire_no_3";
		break;

	case "adversary_hire_no_3":
		dialog.text = "Has dicho que ella es una oficial temporal. Me uniré a ti tan pronto como la dejes en tierra. Varada en alguna isla deshabitada, espero (ríe) Te seguiré hasta el fin del mundo, sí, ¿eh?" + pchar.name + ", querido, ¿realmente es mejor que yo?";
		link.l1 = "¡Tonterías! Deja de hablar así, Mary, querida, ¡no hay mujer mejor que tú!...";
		link.l1.go = "adversary_hire_no_4";
		break;

	case "adversary_hire_no_4":
		dialog.text = "Entonces demuéstramelo.  No quiero compartirte, " + pchar.name + "¡Prefiero estar sola que compartirte con otra, sí, ¿eh?...";
		link.l1 = "Está bien, Mary. Hagamos un trato. No puedo deshacerme de Helen ahora, es importante para esta misión. La ayudaré con sus problemas, la convertiré en señora de la Isla Tesoro, la dejaré ir, y no quedará nada entre nosotros. Con suerte, no tomará más de un mes o dos. ¿Me esperarás tanto tiempo, sí, ¿eh?";
		link.l1.go = "adversary_hire_no_5";
		break;

	case "adversary_hire_no_5":
		dialog.text = "Por supuesto que lo haré, sí, ¿eh? Es mi decisión... Si regresas a mí, eso significa que me has elegido a mí en lugar de a ella. Y si no regresas... entonces ese es mi destino. Me quedaré aquí y fundaré mi propio clan. Clan Casper...";
		link.l1 = "Llorando otra vez? Mary, vamos. ¡Basta de tonterías! ¿De qué estás hablando? ¿Qué clan...? Chica tonta, por supuesto que volveré, no me atrevería a dejarte entre estos barcos podridos y viejos. ¡Inundarías la isla con tus lágrimas, sí, ¿eh?";
		link.l1.go = "adversary_hire_no_6";
		break;

	case "adversary_hire_no_6":
		dialog.text = "Regresa lo antes posible entonces... " + pchar.name + ", cariño, bésame, por favor...";
		link.l1 = "Volveré. ¡Lo prometo!"; // ага, а мы посмотрим, обманешь или нет
		link.l1.go = "adversary_hire_no_7";
		break;

	case "adversary_hire_no_7":
		DialogExit();
		SetMusic("music_romantic");
		SetLaunchFrameFormParam("", "", 0, 15);
		SetLaunchFrameFormPic("loading\inside\kiss.tga");
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 1, 10); // крутим время
		RecalculateJumpTable();
		NextDiag.CurrentNode = "LSC_love"; // оставляем штучки с Мэри на Острове в силе
		pchar.questTemp.LSC.MaryWait = "true";
		AddQuestRecord("LSC", "22");
		bQuestDisableMapEnter = false;				   // открыть карту
		DeleteAttribute(pchar, "GenQuest.CannotWait"); // можно мотать время
		break;

	// повторный разговор после расставания с Элен
	case "adversary_hire_return":
		dialog.text = "¿Te estás burlando de mí? " + pchar.name + ", ¿de verdad no te has olvidado de mí, sí, ¿eh?";
		link.l1 = "¡Por supuesto! ¿Te he engañado alguna vez? He pasado por mucho durante nuestra separación y no tengo intención de separarme de nuevo de ti... mi talismán.";
		link.l1.go = "adversary_hire_yes";
		DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
		break;

	case "adversary_hire_yes": // Элен заведомо не друг - Мэри идёт сразу, либо если выбрал Мэри
		dialog.text = "¿De verdad? " + pchar.name + "¡Siempre te seguiré! Nunca te mentiré, nunca te traicionaré, lo juro!";
		link.l1 = "Te creo, querida... Yo tampoco lo haré."; // а куда же ты денешься )
		link.l1.go = "adversary_hire_yes_1";
		break;

	case "adversary_hire_yes_1":
		dialog.text = "" + pchar.name + ", cariño, abrázame... Estaremos juntos, ¿verdad? ¡Dímelo!";
		link.l1 = "Sí, estaremos juntos, Mary. Para siempre, sí, ¿eh?";
		link.l1.go = "adversary_hire_yes_2";
		break;

	case "adversary_hire_yes_2":
		dialog.text = "¿Igual que Danielle y Nathaniel?";
		link.l1 = "(riendo) Sí, justo como ellos.";
		link.l1.go = "adversary_hire_yes_3";
		break;

	case "adversary_hire_yes_3":
		dialog.text = "" + pchar.name + "... ¡Te amo! Me casaré contigo si quieres, sí, ¿eh? ...";
		link.l1 = "Querida Mary... Por supuesto, hablaremos de ello más tarde. Tu vida en este cementerio de barcos ha terminado, primero saquémosla de aquí, bienvenida a bordo de mi nave y al gran mundo, mi amor.";
		link.l1.go = "adversary_hire_yes_4";
		break;

	case "adversary_hire_yes_4":
		dialog.text = "Pasemos nuestra última noche en esta isla juntos, en 'Ceres Smithy'. Solo nosotros dos. Solo tú y yo... No te dejaré ir a ningún lado hasta que amanezca, sí, ¿eh?";
		link.l1 = "Bueno, no estamos en mi barco, así que seguiré tus órdenes... ¡Mi querida Mary!";
		link.l1.go = "adversary_hire_yes_5";
		break;

	case "adversary_hire_yes_5":
		DialogExit();
		npchar.quest.hire = "true";
		LAi_SetActorType(npchar);
		LAi_SetActorType(pchar);
		SetMusic("music_romantic");
		DoQuestCheckDelay("LSC_LastNight_CS", 3.0);
		bQuestDisableMapEnter = false;				   // открыть карту
		DeleteAttribute(pchar, "GenQuest.CannotWait"); // можно мотать время
		break;

	case "LSC_mary_hire":
		dialog.text = "¡A la orden, señor!";
		link.l1 = "...";
		link.l1.go = "LSC_mary_hire_1";
		break;

	case "LSC_mary_hire_1":
		DialogExit();
		DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload62", "LSC_Mary_hire");
		if (pchar.questTemp.LSC.Mary != "return")
			AddQuestRecord("LSC", "24");
		pchar.questTemp.LSC.Mary = "officer";
		RemoveItems(pchar, "key_mary", 1);
		break;

		// --> консультации по морским сражениям
	case "sea_bomb":
		dialog.text = "" + pchar.name + "¡Tengo una idea...";
		link.l1 = "" + npchar.name + "¿No es seguro aquí y te he ordenado que te quedes en el barco...?";
		link.l1.go = "sea_bomb_1";
		break;

	case "sea_bomb_1":
		dialog.text = "" + pchar.name + ", hay tanta pólvora en esta vieja bañera, si explota, toda la isla volará por los aires. Ahora da igual dónde quedarse. ¡Solo escúchame!";
		link.l1 = "Estoy escuchando, por favor, hazlo rápido.";
		link.l1.go = "sea_bomb_2";
		break;

	case "sea_bomb_2":
		dialog.text = "La corbeta pirata y la fragata. Creen que somos uno de los suyos... Cuchillo, sí, ¿eh? Esto podría ser una oportunidad para nosotros. Tomemos unos barriles de pólvora, una mecha y naveguemos hacia ellos.\nCuando nos dejen acercarnos, encendemos la mecha, lanzamos el barril a uno de los barcos y nos alejamos lo más rápido que podamos. Debe ser una oportunidad perfecta para ver algunos fuegos artificiales... ¿Qué opinas?";
		link.l1 = "Arriesgado, sin embargo, tu plan podría funcionar... Solo si no logran reconocernos.";
		link.l1.go = "sea_bomb_3";
		break;

	case "sea_bomb_3":
		dialog.text = "Arriesguémonos, " + pchar.name + "?";
		link.l1 = "Está bien. ¡Sigamos con esto! ¡Muchachos! ¡Tomen tres barriles de pólvora! ¡Vamos a largarnos de aquí al diablo! Me encanta tu imaginación, " + npchar.name + "... Nunca se me habría ocurrido esta idea a mí misma.";
		link.l1.go = "sea_bomb_4";
		break;

	case "sea_bomb_4":
		dialog.text = "Te lo dije, tengo mis talentos, sí, ¿eh?";
		link.l1 = "...";
		link.l1.go = "sea_bomb_5";
		break;

	case "sea_bomb_5":
		chrDisableReloadToLocation = false;
		DialogExit();
		LAi_SetOfficerType(npchar);
		LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		npchar.dialog.currentnode = "Mary_officer";
		pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
		AddQuestRecord("BarbTemptation", "15");
		AddQuestUserData("BarbTemptation", "sName", "Mary");
		pchar.questTemp.Saga.BarbTemptation.adviser = "Mary";
		break;

	case "fugas":
		dialog.text = "Sí, claro, cariño. Siempre estoy lista para ayudar, sí, ¿eh? ¿Qué sucede?";
		link.l1 = "La nave de Jackman está en la Cala Sabo-Matila, la fragata pesada 'Centurion'. Esta nave fue una vez propiedad de los Hawkes, así que debe haber artículos importantes y documentos en la cabina de Jackman...debemos abordarla.";
		link.l1.go = "fugas_1";
		break;

	case "fugas_1":
		dialog.text = "Ya veo. ¿Cómo piensas hacer eso con nuestro pajarito? Ellos tienen más hombres y cañones. He mirado a través del catalejo, sí, ¿eh?";
		link.l1 = "Tienes razón. Jackman tiene al menos el doble de hombres que nosotros, y todos son hábiles asesinos y mercenarios. Sería una locura abordar sin las preparaciones adecuadas. Una batalla prolongada en el mar tampoco es una opción. Así que he estado pensando en otras opciones para cumplir la tarea.";
		link.l1.go = "fugas_2";
		break;

	case "fugas_2":
		dialog.text = "" + pchar.name + ", todavía no nos han reconocido como enemigos, igual que esos idiotas en Turks... Podemos intentar nuestro truco de nuevo...";
		link.l1 = "Mary, acabo de decirte que debemos abordar la fragata, hundirla no es una opción.";
		link.l1.go = "fugas_3";
		break;

	case "fugas_3":
		dialog.text = "Lo sé, " + pchar.name + ". no la hundiremos. Escucha, vamos a tomar unos cuantos barriles vacíos de ron y los llenaremos con pólvora, metralla y mechas cortas. Luego nos acercaremos a su fragata y lanzaremos los explosivos improvisados en su cubierta.";
		link.l1 = "¡Ja! ¿Realmente crees que funcionará?";
		link.l1.go = "fugas_4";
		break;

	case "fugas_4":
		dialog.text = "¿Y por qué no? Su francobordo es más alto que el nuestro, pero dos o tres hombres ayudados por una polea podrían izar y lanzar un barril completamente cargado fácilmente. Gritaremos: '¡Aquí hay ron gratis de Knive!' Y los barriles explotarán antes de que puedan siquiera reaccionar.";
		link.l1 = "La metralla explosiva convertirá a sus mejores hombres en cubierta en picadillo... Maldita sea, suena tentador.";
		link.l1.go = "fugas_5";
		break;

	case "fugas_5":
		dialog.text = "Usemos cinco barriles." + pchar.name + ", tenemos el elemento sorpresa. ¡No sospecharán nada! Sin embargo, debemos zarpar inmediatamente antes de que aborden.";
		link.l1 = "Bueno, intentémoslo. No deben identificarnos antes de que lancemos los barriles... Maldita sea, no será fácil acercarnos a ellos. Jackman no es un idiota como lo fue Ghoul.";
		link.l1.go = "fugas_6";
		break;

	case "fugas_6":
		dialog.text = "Arriesguémonos, " + pchar.name + "¡No dolerá de todos modos!";
		link.l1 = "Buen punto, no tenemos nada que perder... ¡Prepara las fougasses!";
		link.l1.go = "fugas_7";
		break;

	case "fugas_7":
		dialog.text = "¡Lo haré, mi capitán! Los prepararé perfectamente, sí, ¿eh?";
		link.l1 = "¡Oye, no te dejaron aturdir a esos cangrejos en la isla, así que aquí estoy dejándote reventar algunos traseros de piratas aquí eh... Mary, eres maravillosa!";
		link.l1.go = "fugas_8";
		break;

	case "fugas_8":
		dialog.text = "Gracias, " + pchar.name + "¡No te defraudaré!";
		link.l1 = "En eso, no tengo duda. Espero que seamos nosotros los que no te defraudemos estropeando este plan tuyo... ¡A las armas!";
		link.l1.go = "fugas_9";
		break;

	case "fugas_9":
		DialogExit();
		npchar.dialog.currentnode = "Mary_officer";
		pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
		AddQuestRecord("BarbTemptation", "21");
		DeleteAttribute(npchar, "quest.fugas");
		break;
	// <-- консультации по морским сражениям

	// --> суп из черепахи
	case "terrapin_grot":
		dialog.text = "¡Ahí estás! Me costó encontrarte... ¡Eso fue increíble, capitán! ¡Nunca antes había visto un salto tan impresionante! ¡Siempre eres mi héroe! Aunque admito que casi me das un infarto\nUn día me matarás con esos trucos tuyos, querido... Pues bien, ¿quién diablos sería ella? Oh " + pchar.name + ", te dejo escapar de mí solo por un momento, y al siguiente, ya estás rodeado de hordas de rameras, sí, ¿eh?";
		link.l1 = "Mary, esta 'zorra' es Catherine Fox, hija del coronel Fox, el comandante de los Zorros del Mar. Debemos llevarla a Antigua.";
		link.l1.go = "terrapin_grot_1";
		break;

	case "terrapin_grot_1":
		dialog.text = "¿Oh, de verdad? ¡Qué delicia! Bueno, vas a contarme sobre ella... esta noche, cuando pasemos la noche juntos, a solas. Ahora, vámonos, ¡tenemos que apresurarnos!";
		link.l1 = "Eres la mejor, Mary. ¿Qué haría sin ti? ¡Catherine, vamos!";
		link.l1.go = "terrapin_grot_2";
		break;

	case "terrapin_grot_2":
		DialogExit();
		npchar.dialog.currentnode = "Mary_officer";
		LAi_SetOfficerType(npchar);
		LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		Terrapin_GotoShip();
		break;
	// <-- суп из черепахи

	// --> калеуче
	case "on_coast":
		dialog.text = "Finalmente estás despierto, mi amor... ¡Bastardo! ¡No vuelvas a asustarme así, sí, ¿eh?!";
		link.l1 = "Mary... querida, ¿qué ha pasado? Me duele la cabeza...";
		link.l1.go = "on_coast_1";
		break;

	case "on_coast_1":
		dialog.text = "Cuando entramos en la cabina del capitán, estabas tirado en el suelo, quieto como un cadáver. ¡Mi corazón latía a mil! Los chicos te levantaron y te arrastraron hasta nuestro barco, justo a tiempo, porque los muertos que yacían en la cubierta comenzaron a levantarse de nuevo\n ¡Qué pesadilla! ¡No podíamos hacer nada contra ellos! Rápidamente cortamos las amarras e intentamos zarpar, pero una andanada de su barco dañó gravemente el nuestro y perdimos el control. ¡Eran unos verdaderos demonios, sí, ¿eh?! Y luego izaron velas y desaparecieron en un abrir y cerrar de ojos\nNuestro barco encalló, así que tuvimos que huir a esta orilla antes de que la tormenta pudiera destruirlo. Hoy murieron muchas buenas personas, pero al final el barco sobrevivió...";
		link.l1 = "Buen trabajo, Mary... ¿Qué haría sin ti?";
		link.l1.go = "on_coast_2";
		break;

	case "on_coast_2":
		dialog.text = "Quizás te habrías ahogado, o te habrías quedado en ese barco, y los muertos te habrían destrozado... ¡Mis manos todavía están temblando!";
		link.l1 = "Gracias, amor. ¿Cuánto tiempo he estado inconsciente?";
		link.l1.go = "on_coast_3";
		break;

	case "on_coast_3":
		dialog.text = "Por todo un día. Limpié tus heridas, te di medicina y te vertí un poco de ron. Deberías recuperarte pronto. ¡Y no te atrevas a morirte en mis narices!";
		link.l1 = "Prometo que no moriré esta vez, querida. Aunque no me siento muy bien...";
		link.l1.go = "on_coast_4";
		break;

	case "on_coast_4":
		dialog.text = "Eso es seguro... ¿Era el 'Holandés Errante', capitán? ¿Por qué nos atacaron? ¿Y por qué no dispararon antes de abordarnos?";
		link.l1 = "Su capitán necesitaba el amuleto, del que hablé con Tuttuathapak, el chamán indio. Por eso necesitaban abordarnos, pero en cuanto su capitán tomó el amuleto, ya no nos necesitaban más... ¡Qué pesadilla! ¡Un barco tripulado por los muertos! Increíble...";
		link.l1.go = "on_coast_5";
		break;

	case "on_coast_5":
		dialog.text = "Sí, ¿eh? Parece que el 'Holandés Errante' vendría por nosotros tarde o temprano. Cuando tenga la oportunidad, iré a la iglesia, encenderé una vela por nuestra milagrosa liberación y rezaré a nuestro Señor...";
		link.l1 = "Yo también, Mary, supongo. Necesito volver a ese pueblo. Informar a Tuttuathapak de lo que sucedió. ¡Ese barco nos atacó por el amuleto! Espero que ese diablo de piel roja tenga una explicación de por qué demonios esos muertos vivientes lo necesitaban en primer lugar.";
		link.l1.go = "on_coast_6";
		break;

	case "on_coast_6":
		dialog.text = "Está bien. Pero ten cuidado: tus heridas apenas han sanado, sí, ¿eh?";
		link.l1 = "Eres toda la medicina que necesito. Y... Mary, te amo...";
		link.l1.go = "on_coast_7";
		break;

	case "on_coast_7":
		dialog.text = "Yo también te amo, mi amor...";
		link.l1 = "¡Vaya, eres todo un caballero: apenas guardaste tu sable y ya me colmas de halagos. Muchas gracias por tu ayuda. De verdad me has salvado, sí, ¿eh? Preséntate, por favor, caballero, que es la primera vez que te veo. ¿Llevas mucho tiempo en la isla?";
		link.l1.go = "on_coast_8";
		break;

	case "on_coast_8":
		chrDisableReloadToLocation = false; // открыть локацию
		DialogExit();
		npchar.dialog.currentnode = "Mary_officer";
		LAi_SetOfficerType(npchar);
		LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче

		// --> Мэри вне LSC
		// секс - Мэри не отказывает никогда
	case "cabin_sex":
		dialog.text = RandPhraseSimple("" + pchar.name + ", no hay mayor felicidad para mí que estar en tus brazos, sí, ¿eh?... ¡Vamos!", "" + pchar.name + "Me gustaría estar contigo cada momento del día si fuera posible. ¡Vamos!");
		link.l1 = RandPhraseSimple("Eres el mejor, mi amor...", "Eres maravilloso, mi talismán...");
		link.l1.go = "exit";
		pchar.quest.sex_partner = Npchar.id;
		AddDialogExitQuest("cabin_sex_go");
		break;

	case "sex_after":
		dialog.text = RandPhraseSimple("Querido, estuviste increíble... ¡siempre lo estás!", "¡Fue genial!");
		link.l1 = RandPhraseSimple("Me alegra que estés feliz, mi amor...", "Te amo, Mary...");
		link.l1.go = "exit";
		NextDiag.TempNode = "Mary_officer";
		chrDisableReloadToLocation = false; // открыть локацию
		npchar.quest.daily_sex = true;
		DeleteAttribute(npchar, "quest.iwantsex"); // belamour для бесконфликтности квестов
		SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
		break;

	case "room_sex":
		if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
		{
			dialog.text = "" + pchar.name + ", no hay mayor felicidad para mí que estar en tus brazos, sí, ¿eh?... Pero este no es el mejor momento - tenemos que atrapar a ese canalla de Thibaut antes de que se escape.";
			link.l1 = "Tienes razón como siempre, mi chica...";
			link.l1.go = "exit";
			break;
		}
		dialog.text = RandPhraseSimple("" + pchar.name + ", no hay mayor felicidad para mí que estar en tus brazos, sí, ¿eh? ¡Vamos!", "" + pchar.name + "Me gustaría estar contigo cada momento si fuera posible. ¡Vámonos!");
		link.l1 = RandPhraseSimple("Eres la mejor, mi chica...", "Eres maravilloso, mi talismán pelirrojo...");
		link.l1.go = "room_sex_go";
		break;

	case "room_sex_go":
		DialogExit();
		pchar.quest.sex_partner = Npchar.id;
		chrDisableReloadToLocation = true; // закрыть локацию
		if (sti(pchar.money) >= 10)
			AddMoneyToCharacter(pchar, -10);
		if (npchar.chr_ai.type == "actor")
		{
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		}
		if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs", 0) == -1)
		{
			// DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
			DoFunctionReloadToLocation(pchar.location + "_upstairs", "quest", "quest4", "GiveKissInRoom");
			ChangeCharacterAddressGroup(npchar, pchar.location + "_upstairs", "quest", "quest3");
		} // patch-8
		// DoQuestCheckDelay("Mary_LoveSex", 2.5);
		NextDiag.CurrentNode = "sex_after";
		npchar.greeting = "mary_hire";
		break;

	// требует секса, если давно не давал
	case "givemesex":
		dialog.text = RandPhraseSimple("" + pchar.name + ", ha pasado demasiado tiempo desde que tuvimos sexo... Te has olvidado completamente de mí, sí, ¿eh? Cariño, quiero relajarme, busquemos una habitación para la noche y dejemos nuestros problemas para otro día!", "" + pchar.name + ", ¡has estado demasiado ocupado y empiezo a pensar que te has olvidado por completo de mí! Cariño, quiero... quedarme contigo en privado. Consigamos una habitación para esta noche, sí, ¿eh?", "" + pchar.name + ", ¿has perdido la cabeza? Quiero pasar la noche contigo, tomar un poco de vino y relajarme. ¡Has estado demasiado ocupado en el mar y te has olvidado por completo de mí!");
		link.l1 = "Mary, querida, ¿de qué hablas con eso de 'completamente olvidado de mí'? Chiquilla tonta... Pero realmente he estado demasiado ocupado, los problemas que requieren mi atención son interminables. Perdóname, mi amor. Vamos arriba, soy todo tuyo por la noche, el mundo puede esperar.";
		link.l1.go = "room_sex_go";
		// belamour legendary edition -->
		link.l2 = RandPhraseSimple(RandPhraseSimple("No hoy, querido. Tengo dolor de cabeza.", "Mary, cariño, ¿cómo podría olvidarme de ti? Vamos, después - tenemos trabajo que hacer..."), RandPhraseSimple("Siempre estás en mi mente, Mary, pero no podemos permitirnos relajarnos ahora mismo.", "Mary " + npchar.lastname + ", no tenemos tiempo para tonterías hoy"));
		link.l2.go = "room_sex_goNS";
		break;

	case "room_sex_goNS":
		if (sti(pchar.reputation.fame) > 60)
		{
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			if (npchar.chr_ai.type == "actor")
			{
				LAi_SetOfficerType(npchar);
				LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			}
			NextDiag.TempNode = "Mary_officer";
			chrDisableReloadToLocation = false;
			npchar.quest.daily_sex = true;
			DeleteAttribute(npchar, "quest.iwantsex");
			SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
			pchar.quest.Mary_giveme_sex.over = "yes";
			pchar.quest.Mary_giveme_sex1.over = "yes";
			dialog.text = "Bueno ... ¿Qué más puedo decir ... Sí, capitán?";
			link.l1 = "Veo que eres valiente. Te has enfrentado a muchas tormentas y aun así te mantienes firme. ¿Sí?";
			link.l1.go = "exit";
		}
		else
		{
			if (bImCasual)
				Log_Info("Para rechazar que Mary se haga más famosa");
			ChangeCharacterComplexReputation(pchar, "authority", -2);
			dialog.text = "Carlos...";
			link.l1 = "Mary, querida, ¿de qué estás hablando - 'completamente te has olvidado de mí'? Muchacha tonta... Pero realmente he estado ocupado, esos problemas son interminables. Perdóname, mi chica. ¡Vamos arriba, el mundo puede esperar!";
			link.l1.go = "room_sex_go";
		}
		break;
	// <-- legendary edition
	// ругается за то, что ходил по борделям, ГГ изворачивается
	case "brothel":
		dialog.text = "¡Ahí está! Ya no te gusto, ¿verdad? ¡Dímelo!";
		link.l1 = "¿Qué?! Mary, ¿qué tonterías estás diciendo? ¿Por qué piensas eso?";
		link.l1.go = "brothel_1";
		break;

	case "brothel_1":
		dialog.text = "Entonces, ¿por qué has estado visitando a esas fulanas, esas zorras de burdel? ¡Sé que lo hiciste, no me mientas! No te gusta algo de mí cuando hacemos el amor, ¿sí, eh? (llorando) Dime...";
		link.l1 = "Mary, Mary... cálmate, por favor, mi niña. Sí, he estado en el burdel unas cuantas veces, pero solo por asuntos de negocios. ¡No estaba buscando divertirme!";
		link.l1.go = "brothel_2";
		break;

	case "brothel_2":
		dialog.text = "¿Y qué clase de 'asuntos de negocios' te habían traído arriba al cuarto del placer? (sollozando) Estás mintiendo, " + pchar.name + "¡";
		link.l1 = "Mary, querida, deja eso ya... Realmente tuve algunos asuntos de negocios con la dueña del burdel. Y he subido unas cuantas veces. La última vez por un asunto personal del gobernador - me pidió que encontrara su anillo de bodas. ¿Cómo podría negarme a Su Excelencia?";
		link.l1.go = "brothel_3";
		break;

	case "brothel_3":
		dialog.text = "";
		link.l1 = "¿Y cómo podría explicarle a la patrona que necesito mirar debajo de la cama de arriba? No pude. Así que tuve que comprar una ramera por la noche para que me permitieran subir... La segunda vez, me dijeron que un comerciante había perdido sus documentos del barco allí. Tuve que pagar de nuevo por una chica, para poder registrar la habitación, y me pagaron bien por los documentos...";
		link.l1.go = "brothel_4";
		break;

	case "brothel_4":
		dialog.text = "";
		link.l1 = "La tercera vez estaba ayudando al comandante local: tuve que preguntar a las prostitutas sobre un oficial de la guarnición. Ese oficial era sospechoso de espionaje y de tener conexiones con piratas. Finalmente, lo atrapamos y recibí una buena recompensa...";
		link.l1.go = "brothel_5";
		break;

	case "brothel_5":
		dialog.text = "";
		link.l1 = "¿Ves ahora? Te digo, todo era cuestión de negocios. Mary, eres tú a quien amo y necesito. ¡Eres la mejor, lo juro! ¿De verdad crees que me metería con alguna ramera sucia del puerto, teniendo a ti? ¿Cómo pudiste siquiera pensar eso de mí?";
		link.l1.go = "brothel_6";
		break;

	case "brothel_6":
		dialog.text = "" + pchar.name + " ... ¿Es todo verdad? ¿Eres honesto conmigo? ¿No has estado con ellos?";
		link.l1 = "Mary, querida, eres la única mujer a la que amo, es verdad. Acércate, querida. Déjame abrazarte... Seca tus lágrimas y, por favor, ¡deja de estar celosa! Nunca volveré a visitar los burdeles, si eso es lo que quieres, sí, ¿eh?";
		link.l1.go = "brothel_7";
		break;

	case "brothel_7":
		dialog.text = "¡Sí, eso es lo que quiero!... " + pchar.name + ", Estoy celosa porque te amo... Y no quiero perderte, ¡sí, ¿eh?! ¿Me oyes? ¡Mataré a cualquier zorra que se atreva a acercarse un centímetro a ti!";
		link.l1 = "Tranquila... No hay necesidad de matar a nadie. Y no me perderás, te lo prometo. Todo está bien, cálmate. Eres mi única y la mejor chica del mundo... Confía en mí, eso eres.";
		link.l1.go = "brothel_8";
		break;

	case "brothel_8":
		DialogExit();
		SetLaunchFrameFormParam("", "", 0, 5);
		SetLaunchFrameFormPic("loading\inside\kiss.tga");
		LaunchFrameForm();
		pchar.GenQuest.BrothelLock = true; // все, больше не походишь по борделям :)
		DeleteAttribute(pchar, "GenQuest.BrothelCount");
		break;

	// на Тайясаль
	case "tieyasal":
		dialog.text = "" + pchar.name + "¿qué pregunta tan extraña? Te amo. Me salvaste. Soy tu talismán pelirrojo - ¿realmente crees que te dejaré ir allí solo? ¡Ni lo pienses, sí, ¿eh?! ¡Estoy contigo! ¿Cuándo partimos?";
		link.l1 = "Tienes razón, querida, fue una pregunta extraña... Te lo contaré más tarde cuando nos vayamos. Primero necesitamos prepararnos.";
		link.l1.go = "tieyasal_1";
		break;

	case "tieyasal_1":
		dialog.text = "¡Estoy lista, mi capitán! ¡Te seguiré hasta el fin del mundo!";
		link.l1 = "Gracias, mi amor...";
		link.l1.go = "tieyasal_2";
		break;

	case "tieyasal_2":
		DialogExit();
		AddQuestRecord("Tieyasal", "19");
		npchar.quest.Tieyasal = "teleport";
		break;

	// Jason Дороже золота
	case "GoldenGirl":
		pchar.quest.Mary_giveme_sex1.over = "yes";	   // fix 22-03-20
		pchar.questTemp.GoldenGirl.MaryBlock = "true"; // fix 22-03-20
		dialog.text = "¿Cuál es todo este alboroto esta vez, Capitán? ¿Españoles, piratas o algo peor?";
		link.l1 = "Es peor, Mary, mucho peor. El gobernador tiene la intención de visitar a una cortesana extremadamente cara y se supone que debo acompañarlo como persona de interés, tal como prometí a la madama. Charlas aburridas, vino carísimo y nobles insulsos.";
		link.l1.go = "GoldenGirl_1";
		link.l2 = "Todo lo contrario, una carga de invitación a un evento social, dirigido por una dama noble. Su Excelencia me tomó por sorpresa cuando me pidió que lo acompañara, pero para ser honesta, espero poder distraerme de las cosas.";
		link.l2.go = "GoldenGirl_3";
		break;

	case "GoldenGirl_1":
		dialog.text = "¿De verdad?! ¿Una cortesana? ¿Lo dices como si no fuera gran cosa, eh? ¿Solo divirtiéndote un poco con Su Excelencia? Charles, ¿estás fu...";
		link.l1 = "¡María, cálmate, por favor! No es que vaya allí para… ¡no es un burdel! Bueno, es un burdel, pero maldita sea si no soy un noble y un hombre de palabra. ¿De verdad no confías en mí? El gobernador solo me pidió un pequeño favor y debo complacerlo, eso es todo.";
		link.l1.go = "GoldenGirl_2";
		break;

	case "GoldenGirl_2":
		dialog.text = "Sí, ¿eh? He oído hablar de un par de 'nobles' así. Los he visto en tu compañía también. ¡La compañía femenina es una necesidad diaria para ellos! 'Altas' sociedades, 'Entretenimiento' digno, ¡mis narices! Ni siquiera un matrimonio los detiene de visitar a estas... damas. Maldita sea, no tenía idea de que eras igual que ellos. Ni siquiera somos... ¡Al diablo contigo, con todos ustedes!";
		link.l1 = "¡Mary, espera! Mierda...";
		link.l1.go = "GoldenGirl_6";
		break;

	case "GoldenGirl_3":
		dialog.text = "Nos hemos ganado unas vacaciones, sí, ¿eh? ¿Crees que pueden soportar ver a una dama vestida con un abrigo rojo? ¿Imaginas todos los susurros en las esquinas? Alguien seguramente se desmayará, sería divertido, ¿verdad?";
		link.l1 = "Mary, querida, este no es el tipo de fiesta a la que llevas a una dama... al menos no una dama como tú. Bueno, es un poco complicado pero déjame explicar...";
		link.l1.go = "GoldenGirl_4";
		break;

	case "GoldenGirl_4":
		dialog.text = "Vaya, no te molestes. Solo dímelo directamente: no soy lo suficientemente buena para esos imbéciles con pelucas. Una chica sencilla, para divertirse, ¿eh? ¿Te da vergüenza mostrarte conmigo cerca? No soy lo suficientemente buena para las fiestas elegantes, ¿verdad, honorable monsieur Charles de Maure?";
		link.l1 = "No, en absoluto. Eres increíble y no me importa la impresión que causamos a la gente a nuestro alrededor. El gobernador está tratando de resolver sus problemas con mi ayuda, como siempre. Seré como un trofeo valioso en la sala. Un invitado interesante para impresionar a los nobles inútiles.";
		link.l1.go = "GoldenGirl_5";
		break;

	case "GoldenGirl_5":
		dialog.text = "Entonces, no soy bueno para ti, ¿eh? Ya veo, está bien, los nobles son para los nobles, los plebeyos son para simple diversión. Buena suerte con tu clase alta. Hablaré contigo cuando vuelvas a nuestra humilde tierra, sí, ¿eh?";
		link.l1 = "¡Mary, espera! Maldita sea...";
		link.l1.go = "GoldenGirl_7";
		break;

	case "GoldenGirl_6":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 10.0);
		pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;

	case "GoldenGirl_7":
		DialogExit();
		LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 10.0);
		pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;

	case "GoldenGirl_10":
		dialog.text = "Buena suerte con tu clase alta. Hablaré contigo cuando vuelvas a nuestro humilde suelo, sí, ¿eh?";
		link.l1 = "¡Mary, vamos!";
		link.l1.go = "GoldenGirl_11";
		break;

	case "GoldenGirl_11":
		DialogExit();
		NextDiag.CurrentNode = "GoldenGirl_10";
		break;

	case "GoldenGirl_12":
		dialog.text = "Mira esto, ¡sí! ¡Nuestro capitán perdido en la alta sociedad!";
		link.l1 = "¡Vaya, eres todo un caballero: apenas guardaste tu sable y ya me colmas de halagos. Muchas gracias por tu ayuda. De verdad me has salvado, sí, ¿eh? Preséntate, por favor, caballero, que es la primera vez que te veo. ¿Llevas mucho tiempo en la isla?";
		if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1"))
			link.l1.go = "GoldenGirl_13";
		else
			link.l1.go = "GoldenGirl_17";
		break;

	case "GoldenGirl_13":
		dialog.text = "Desapareciste en el burdel todo el día y ahora la gente del pueblo está hablando. Charles, dame solo una buena razón por la que debería hablar contigo ahora en lugar de, digamos, mostrarte el Narval por tu... ¿barriga? ¡No te importo mucho, sí, ¿eh?!";
		link.l1 = "Mary, te explicaré todo, pero más tarde. Debo prepararme y salir a un duelo. Si sobrevivo a esto, siéntete libre de matarme. Mientras tanto, por favor cuida de nuestro nuevo barco, sí, ¿eh? Lo gané como premio en un juego de cartas anoche.";
		link.l1.go = "GoldenGirl_14";
		break;

	case "GoldenGirl_14":
		dialog.text = "Olvídate del barco, dijiste algo sobre un duelo, ¿sí, eh? Los lugareños cuentan toda clase de historias de mierda que no escucho. Dicen que debes pelear ya sea con el hijo del rey o con el maldito Papa mismo. Dime ahora, ¿qué diablos está pasando?";
		link.l1 = "Este hombre es un bastardo de un noble muy influyente, el Conde de Levi Vantadur. Fue él quien me retó en primer lugar, y debo ganar el duelo sin hacerle daño, para evitar la ira de su padre.";
		link.l1.go = "GoldenGirl_15";
		break;

	case "GoldenGirl_15":
		dialog.text = "¿Mientras yo estaré sentado en mi trasero en la bañera que acabas de ganar? ¿Te has vuelto loco, Charles?";
		link.l1 = "Tengo miedo de que tenga que ser así. El gobernador me proporcionó un par de oficiales nobles para que sean mis segundos y así evitar cualquier confusión después. No puedo llevarte a ti ni a ninguno de los muchachos conmigo por el bien de la integridad oficial del duelo. Esto es demasiado serio, lo siento.";
		link.l1.go = "GoldenGirl_16";
		break;

	case "GoldenGirl_16":
		dialog.text = "¿Sabes lo que voy a hacer ahora? ¡Iré a ese maldito barco y me emborracharé como es debido, sí, ¿eh?! Haz lo que te plazca, pero si ese noble hijo de puta no logra matarte, ¡te juro que lo haré yo misma!";
		link.l1 = "Mary, todo estará bien, confía en mí. Ahora, espera... ¡Maldita sea! ¡Aquí vamos de nuevo!";
		link.l1.go = "GoldenGirl_21";
		break;

	case "GoldenGirl_17":
		dialog.text = "¡Ahí estás! ¡No hemos recibido ni una sola palabra de ti en todo el día! Estábamos preocupados al escuchar los chismes que circulan en el mercado. Dicen que has estado apostando por barcos y mujeres, ¡e incluso te has batido en duelo con algún tipo de príncipe coronado o incluso con el mismo Papa! ¿Qué demonios está pasando?";
		link.l1 = "Es complicado, Mary. Me llevará un tiempo explicarlo. Sin embargo, logré ganar una fragata. Tendrás que cuidarla mientras resuelvo mi disputa con su anterior dueño.";
		link.l1.go = "GoldenGirl_18";
		break;

	case "GoldenGirl_18":
		dialog.text = "¿Así que tenían razón sobre el duelo, sí, ¿eh? ¿Quién es ese noble arrogante, maldita sea? ¿Por qué estás peleando con él?";
		link.l1 = "Tengo que hacerlo. Es complicado, pero en resumen: le gané su barco y su... dama. Me acusó públicamente de hacer trampa y me retó a un duelo. Este hombre es un bastardo de un noble muy influyente, el Conde de Levi Vantadur. Tendré que hacer todo lo posible para evitar hacerle daño.";
		link.l1.go = "GoldenGirl_19";
		break;

	case "GoldenGirl_19":
		dialog.text = "¿Una dama? Puedo entender apostar por un barco, pero... ¿una mujer, de verdad? Decían la verdad en las calles, ¿eh? ¡¿Lo admites así nomás?! ¿Como si yo fuera una de tus marineros idiotas?";
		link.l1 = "¡Maldita sea, Mary, no es así en absoluto! Él la ganó del gobernador, yo la recuperé de él para liberarla, eso es todo. No hay nada más, ¡lo juro!";
		link.l1.go = "GoldenGirl_20";
		break;

	case "GoldenGirl_20":
		dialog.text = "Bueno, tal vez es normal entre vosotros, los nobles, pero yo no soy así, ¡sí, ¿eh?! Haz lo que quieras, di lo que te plazca... ¡ve y muere por ella si quieres! Yo iré a la maldita nave que ganaste y me emborracharé. Creí que esto era real y... duraría para siempre. ¡Supongo que esperaba demasiado!";
		link.l1 = "¡Mary, me importa un bledo esa mujer! Solo espera, por favor... ¡Maldición! Aquí vamos de nuevo...";
		link.l1.go = "GoldenGirl_21";
		break;

	case "GoldenGirl_21":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;

	case "GoldenGirl_24":
		dialog.text = "¡Charles, viniste por mí, sí, ¿eh?! ¡Lo sabía, nunca lo dudé! ¡Estoy tan feliz de verte!";
		link.l1 = "¡Yo también, Mary! Me ha estado matando todo este tiempo. ¡Gracias a Dios que estás bien!";
		link.l1.go = "GoldenGirl_25";
		break;

	case "GoldenGirl_25":
		if (pchar.questTemp.GoldenGirl == "alarm_fin")
		{
			dialog.text = "Por cierto, ¿qué hiciste exactamente para que me liberaran tan fácilmente? ¡Sin una buena pelea o disparos, sí, ¿eh?! Oh, y vi a una dama hermosa en la cubierta cuando me sacaban. ¿Qué pasó, Charles?";
		}
		else
		{
			dialog.text = "¿Qué hiciste exactamente para que me soltaran así nada más? ¡Sin pelea, sin disparos, sí, ¿eh?! Vi algunos pavos reales británicos en cubierta cuando me sacaban. ¿De qué iba todo eso, Charles?";
		}
		link.l1 = "Todo lo que importa es que estás de vuelta conmigo. Te fallé, Mary. ¡Lo siento mucho! ¡Espero que puedas encontrar en tu corazón el perdonarme! Odio cómo dejamos las cosas entre nosotros la última vez.";
		link.l1.go = "GoldenGirl_26";
		break;

	case "GoldenGirl_26":
		dialog.text = "Ya lo hice. Yo también lo siento, ¡sí, ¿eh?! Si tan solo no me hubiera tomado tus tratos con esa dama tan personalmente... Habría puesto una vigilancia adecuada esa noche. ¡Nunca nos habrían derribado tan fácilmente! ¡Qué estúpido fui!";
		link.l1 = "El pasado es el pasado. Te amo y nunca te dejaré así de nuevo. ¡Lo prometo!";
		link.l1.go = "GoldenGirl_27";
		break;

	case "GoldenGirl_27":
		dialog.text = "Sabía que nunca me abandonarías, sí, ¿eh? ¡Perdona por haber dudado de ti, Charles! Parece que es mejor que no sepa exactamente lo que hiciste, ¿eh? Estamos juntos de nuevo y eso es lo único que importa.";
		link.l1 = "No tengo secretos para ti. Te contaré...";
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
			dialog.text = "¡Vaya historia... dudo que alguien más la creería, sí, ¿eh? ¡Lo supe desde el principio! ¡Sabía que tu 'noche traviesa' era un asunto divertido! Todos esos pavos reales nobles... ¡bestias sin corazón! Al menos no me equivoqué contigo, sabía que eras diferente, sí, ¿eh?";
			link.l1 = "Estoy bastante seguro de que mucha gente por ahí me considera mucho peor. Un verdadero monstruo sacado de cuentos de hadas.";
		}
		else
		{
			dialog.text = "¡Vaya historia... dudo que alguien más la creería, sí, ¿eh? ¡Lo supe desde el principio! ¡Supe que tu 'noche traviesa' era un juego! Política, espías, con-ju-ras. Y una vez más, nos salvaste a todos, sí, ¿eh? ¡Mi héroe!";
			link.l1 = "No estoy seguro de eso. Es probable que la guerra con Gran Bretaña comience en unas pocas semanas. Pero hice lo que tenía que hacer, Mary. Eres todo para mí.";
		}
		link.l1.go = "GoldenGirl_29";
		break;

	case "GoldenGirl_29":
		if (pchar.questTemp.GoldenGirl == "alarm_fin")
		{
			dialog.text = "No me importa lo que piensen los demás, si ese es el caso, ¡serás mi monstruo, Charles! Los demás deberían o bien ir a llorar por ello o enfrentarse a mí. ¡Recuerda que siempre estaré a tu lado, sí, ¿eh?!";
		}
		else
		{
			dialog.text = "Lo sé, Charles. Siempre lo supe, pero es tan agradable oírte decirlo. Sabe esto: siempre permaneceré a tu lado, sí, ¿eh?";
		}
		link.l1 = "Jamás lo dudé, Mary. Vamos, los muchachos están preocupados. Es hora de izar las velas y largarnos de aquí. Estás a mi lado de nuevo, y el horizonte no se irá a ninguna parte por sí solo.";
		link.l1.go = "GoldenGirl_30";
		break;

	case "GoldenGirl_30":
		dialog.text = "¡Sí, sí, capitán!";
		link.l1 = "";
		link.l1.go = "GoldenGirl_31";
		break;

	case "GoldenGirl_31":
		DialogExit();
		npchar.dialog.currentnode = "Mary_officer";
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
		GoldenGirl_MaryBlockDelete(); // fix 22-03-20
		break;

	case "GoldenGirl_32":
		dialog.text = "¡Charles, ¿eres realmente tú?! ¡Casi perdí toda esperanza, sí, ¿eh?! ¡Dios, te extrañé tanto! Por favor, por favor, perdóname, sí, ¿eh?";
		link.l1 = "No, perdóname, no lo vi venir... ¡Gracias a Dios que llegaste, Mary! ¡Estoy tan feliz!";
		link.l1.go = "GoldenGirl_33";
		break;

	case "GoldenGirl_33":
		dialog.text = "Hablando de perdón, para ser completamente honesta, estoy debatiendo si debería dispararte o abrazarte. Será mejor que me digas qué demonios está pasando, sí, ¿eh?";
		link.l1 = "Te amo, Mary. Esto es todo lo que quería decirte.";
		link.l1.go = "GoldenGirl_34";
		break;

	case "GoldenGirl_34":
		dialog.text = "Sí, como si eso fuera útil, pero... Maldita sea, yo también, Charles. Yo también te amo, sí, ¿eh? ¡Dios, por fin estamos juntos!";
		link.l1 = "Y no quiero pasar el tiempo que tenemos hablando de cosas que no importan. Ven conmigo y no me atreveré a dejarte esta noche. Incluso si el cielo comienza a caer sobre esta miserable ciudad. No te dejaré nunca más. Jamás.";
		link.l1.go = "GoldenGirl_35";
		break;

	case "GoldenGirl_35":
		dialog.text = "Parece que es mejor no saber exactamente qué hiciste, ¿eh? Estamos juntos de nuevo y eso es lo único que importa.";
		link.l1 = "No tengo secretos para ti. Te diré...";
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
		dialog.text = "¿Estás diciendo que esta... marquesa te ayudó a traerme de vuelta? ¿Y casi iniciaste una guerra entre Inglaterra y Francia, sí, ¿eh? No me malinterpretes, esto es muy romántico y todo, pero ¿qué pasará ahora? ";
		link.l1 = "No tengo idea, Mary. Estamos juntos de nuevo, lo demás es irrelevante. Si los poderosos no logran ocultarlo... bueno, estoy listo para cumplir con mi deber ante la Corona.";
		link.l1.go = "GoldenGirl_37";
		break;

	case "GoldenGirl_37":
		dialog.text = "¿Y esa marquesa tuya? ¿La trajiste de vuelta también? El portugués habló maravillas de ella. Me aseguró que resististe sus avances como el castillo de la Bastilla. ¡Quiero creerle, sí, eh, pero debo escucharlo de ti!";
		link.l1 = "No hay nada entre madame Botot y yo, Mary. Yo la ayudé, ella me ayudó, eso es todo. Hablando de Bartholomew, ¿dónde está?";
		link.l1.go = "GoldenGirl_38";
		break;

	case "GoldenGirl_38":
		dialog.text = "Se ha ido, sí, ¿eh? Zarpó inmediatamente después de traerme aquí. Nunca iría a ese maldito burdel, así que me alquiló una habitación, pagó por adelantado un par de semanas y simplemente se marchó. ¡Oh, casi lo olvido, sí, ¿eh?! ¡Tengo una carta para ti!";
		link.l1 = "¿Una carta? ¿De Bartolomé el Portugués? Esto es algo nuevo. No me gusta hacia dónde va esto...";
		link.l1.go = "GoldenGirl_39";
		break;

	case "GoldenGirl_39":
		dialog.text = "Adelante, léelo. Iré a ver a los muchachos. Probablemente estaban preocupados. ¿Todos lo lograron? Espero que no te importe que tomemos un vaso o dos abajo. ¡No te metas en otro lío, sí, ¿eh?!";
		link.l1 = "Claro, pero por favor ten cuidado con ellos, Mary. Preferiría pasar tiempo contigo esta noche, en lugar de tener que llevar cuerpos borrachos de vuelta al barco. ¡Dios, todavía no puedo creer que te recuperé!";
		link.l1.go = "GoldenGirl_40";
		break;

	case "GoldenGirl_40":
		DialogExit();
		npchar.dialog.currentnode = "Mary_officer";
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
		GoldenGirl_MaryBlockDelete(); // fix 22-03-20
		break;

	// Jason Долго и счастливо
	case "LongHappy":
		RemoveItems(pchar, "potionwine", 2);
		dialog.text = "La playa, tú, yo, y buen vino - ¡Charles, eso es tan romántico! Deberíamos hacer esto más a menudo, sí, ¿eh?";
		link.l1 = "Me alegra que te guste. Creo que a partir de ahora haremos más tiempo el uno para el otro para ocasiones como esta.";
		link.l1.go = "LongHappy_1";
		break;

	case "LongHappy_1":
		dialog.text = "¿De qué estás hablando? ¿Pasó algo con el barco, sí, ¿eh? ¿Por qué estás de rodillas, mi amor?";
		link.l1 = "Porque te amo, Mary. Tú lo sabes, yo lo sé, todos lo saben. Así que aquí y ahora, ante el mar y el cielo, te pido, Mary Casper, que me des el honor de estar a mi lado ante la gente y Dios por tantos días como nos sean dados desde arriba. Yo, Charles de Maure, caballero de Monper, te pregunto: ¿te convertirás en mi esposa?";
		link.l1.go = "LongHappy_2";
		break;

	case "LongHappy_2":
		if (pchar.location == "Shore36")
		{
			dialog.text = "Soñaba con escucharlo, sí, ¿eh? Yo... ya sabes mi respuesta, Charles... ¡oh, lo siento!";
			link.l1 = "Ay, qué más da, esto es solo vino y nunca me gustó esta camisa...";
			link.l1.go = "LongHappy_3";
		}
		else
		{
			dialog.text = "¡Charles, por supuesto que sí! ¡Sí, sí, mil veces sí! ¡Tú... este lugar... nada puede hacerme más feliz! ¡Oh Dios, estoy tan feliz, sí, ¿eh?!";
			link.l1 = "Me has hecho feliz, Mary. ¡Y quiero brindar por ti, mi ardiente Sol Caribeño!";
			link.l1.go = "LongHappy_4";
		}
		break;

	case "LongHappy_3":
		DialogExit();
		chrDisableReloadToLocation = true; // закрыть локацию
		DoQuestCheckDelay("Mary_LoveSex", 1.0);
		npchar.dialog.currentnode = "LongHappy_5";
		LAi_SetStayType(npchar);
		break;

	case "LongHappy_4":
		dialog.text = "Bebo por ti, mi capitán y futuro esposo, sí, ¿eh? ¡Eres lo mejor que me ha pasado!";
		link.l1 = "¡Pero esto es solo el comienzo - a nosotros! ¡Y a nuestro futuro juntos! ¡Hay tanto por delante!";
		link.l1.go = "LongHappy_6";
		break;

	case "LongHappy_5":
		dialog.text = "Bebo por ti, mi capitán y futuro esposo, sí, ¿eh? ¡Eres lo mejor que me ha pasado nunca!";
		link.l1 = "Pero esto es solo el comienzo - ¡por nosotros! Y por nuestro futuro juntos! ¡Hay tanto por delante de nosotros!";
		link.l1.go = "LongHappy_6";
		break;

	case "LongHappy_6":
		DialogExit();
		chrDisableReloadToLocation = false;
		npchar.dialog.currentnode = "Mary_officer";
		LongHappy_MarryToSenPierre();
		break;

	case "LongHappy_7":
		dialog.text = "Charles, el abad Benoit en Martinica de nuevo, así que podemos proceder, ¿verdad? Pero no me pondré un vestido, ni siquiera por el bien de un servicio religioso, espero que no te ofendas, sí, ¿eh?";
		link.l1 = "Mary, te amo con cualquier atuendo y... bueno, ya sabes. Puedes usar lo que quieras, yo me encargaré de cualquiera que tenga un problema con eso. Pero solo quería consultarte sobre los invitados y la ceremonia.";
		link.l1.go = "LongHappy_8";
		break;

	case "LongHappy_8":
		if (LongHappy_CheckSaga())
		{
			dialog.text = "Sabes, la mayoría de aquellos que pueden alegrarse sinceramente por nuestra felicidad ni siquiera podrán entrar en esta ciudad, y mucho menos en la iglesia, sí, ¿eh? Por lo tanto, casémonos aquí con todas las personas importantes, como se espera, y luego navegaremos a Isla Tessoro y lo celebraremos adecuadamente con verdaderos amigos. ¿Qué te parece, sí, ¿eh?";
			link.l1 = "¡Gran opción! Entonces, hagámoslo. Hablaré con el Abad Benoit, pero necesitamos enviar invitaciones y más...";
			link.l1.go = "LongHappy_9";
		}
		else // Сага провалена по времени или утоплен Центурион
		{
			dialog.text = "Sabes, no tengo muchos amigos aparte de nuestros compañeros de la tripulación. Así que invita a quienes consideres necesarios, y yo estaré feliz con lo que haya, sí, ¿eh?";
			link.l1 = "Como dices, cariño. Hablaré con el Abad Benoit y organizaré todo, eres digna de la ceremonia más magnífica.";
			link.l1.go = "LongHappy_9a";
		}
		break;

	case "LongHappy_9":
		dialog.text = "No te preocupes, como buena esposa, me encargaré de parte de la preparación, sí, ¿eh? Escribiré a nuestros amigos y lo arreglaré todo, pero primero dime: ¿cómo ves esta boda?";
		link.l1 = "Mi ideal eres tú, yo y nuestros amigos más cercanos. Después de todas las caras oficiales aquí en Martinica, querremos algo de sinceridad.";
		link.l1.go = "LongHappy_10";
		link.l2 = "Debemos recordar este día. ¡Llama a todos! ¡Nadie se quedará fuera!";
		link.l2.go = "LongHappy_11";
		break;

	case "LongHappy_9a":
		dialog.text = "Contigo, tener una ceremonia con un capellán de barco en el alcázar, bajo el atardecer en el mar, sería suficiente, sí, ¿eh? Pero, si esto es lo que quieres, ¡celebraremos! Charles... voy a llorar ahora, abrázame, sí, ¿eh?...";
		link.l1 = "Mary...";
		link.l1.go = "LongHappy_9b";
		break;

	case "LongHappy_9b":
		dialog.text = "Eso es, estoy tranquila, sí, ¿eh? Lo siento, todo esto es tan inusual. Pero Charles, como buena esposa, me encargaré de la organización. También necesitamos organizar una fiesta para los muchachos, sí, ¿eh? pero es poco probable que toda la tripulación quepa en la iglesia. Haré arreglos con la taberna, pero necesitaremos licor y dinero - ya sabes cómo les gusta festejar a los marineros.";
		link.l1 = "Está bien, eso es lo que vamos a hacer. ¿Qué tengo que preparar?";
		link.l1.go = "LongHappy_9c";
		break;

	case "LongHappy_9c":
		pchar.questTemp.LongHappy.MarryMoney = 100000;
		pchar.questTemp.LongHappy.MarryRum = 100;
		if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
		{
			pchar.questTemp.LongHappy.MarryMoney = 200000;
			pchar.questTemp.LongHappy.MarryRum = 150;
		}
		if (GetCompanionQuantity(pchar) > 1)
		{
			pchar.questTemp.LongHappy.MarryMoney = 300000;
			pchar.questTemp.LongHappy.MarryRum = 200;
		}
		dialog.text = "Creo, " + sti(pchar.questTemp.LongHappy.MarryMoney) + " pesos serán suficientes, sí, ¿eh? " + sti(pchar.questTemp.LongHappy.MarryRum) + "barriles de ron, no hay nada peor que quedarse sin bebidas. Tan pronto como recojas todo lo que necesitamos, ven a la taberna, yo me encargaré del resto.";
		link.l1 = "Está bien, cariño, lo haré.";
		link.l1.go = "LongHappy_9d";
		break;

	case "LongHappy_9d":
		DialogExit();
		npchar.dialog.currentnode = "Mary_officer";
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
		AddQuestRecord("LongHappy", "10_1");
		AddQuestUserData("LongHappy", "sName", "Mary");
		LongHappy_MarryGoToBenua();
		break;

	case "LongHappy_10":
		pchar.questTemp.LongHappy.SmallMarry = "true";
		dialog.text = "Entendido, vamos a hacerlo. Pero tendremos que visitar Sharptown y preparar todo. Creo que cincuenta barriles de ron y un par de docenas de barriles de vino serán suficientes, sí, ¿eh? Pero, por si acaso, necesitaré trescientos mil pesos.";
		link.l1 = "Es mucho, pero la ocasión lo merece. Lo reuniré, no te preocupes. Ahora, voy a pasar por el abad y luego iré a Sharptown.";
		link.l1.go = "LongHappy_12";
		break;

	case "LongHappy_11":
		pchar.questTemp.LongHappy.BigMarry = "true";
		dialog.text = "¡Genial, reuniremos a todos, sí, ¿eh?! Pero tendremos que visitar Sharptown y preparar todo - ¡necesitaremos un galeón lleno de licor! Creo que cien barriles de ron y cincuenta barriles de vino serán suficientes. Pero, por si acaso, añadiré quinientos mil pesos. Si la celebración termina rápido, ¿qué clase de celebración es esa, verdad?";
		link.l1 = "Sí, ¿eh? Nuestros amigos no deben morir de sed - conseguiré todo, ¡no te preocupes! Ahora, voy a pasar por el abad y luego iré a Sharptown.";
		link.l1.go = "LongHappy_12";
		break;

	case "LongHappy_12":
		DialogExit();
		npchar.dialog.currentnode = "Mary_officer";
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
		AddQuestRecord("LongHappy", "10");
		AddQuestUserData("LongHappy", "sName", "Mary");
		LongHappy_MarryGoToBenua();
		break;

	case "LongHappy_13":
		dialog.text = "Todo está listo, Charles, ¿verdad? Me encargaré de que descarguen la bebida, iré a la taberna local, me reuniré con el barón y entregaré las invitaciones. Espera aquí, sí, ¿eh?";
		link.l1 = "¡Tú estás al timón, querido! Entonces, me dedicaré a holgazanear por algún lado. Realmente no pensé que preparar expediciones a la selva de Tierra Firme sería más fácil que una boda, sí, ¿eh?";
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
		dialog.text = "Ya terminamos aquí, Charles, ¡sí, ¿eh?! Arreglé todo, créeme, ¡será maravilloso! Una cosa es embarazosa: la taberna local se quemó durante alguna fiesta hace una semana. Pero casi está reconstruida, más grande y mejor que la antigua, ¡sí, ¿eh?! Deberíamos poder caber todos.";
		link.l1 = "¡Espero que no quememos este! ¡Realmente me gustaba el 'Viejo Pájaro Carpintero'! De todos modos, aún tenemos mucho por hacer. Es hora de zarpar. Y sí, Mary, eres la mejor, lo sabes, ¿verdad?";
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
		dialog.text = "Así que aquí vamos, ¿eh? Los invitados han llegado, la iglesia está lista. Sé que estamos más cerca que muchos esposos, y estas son solo unas pocas palabras importantes en un hermoso salón, pero maldita sea, en esa antigua ciudad aborigen estaba menos preocupado, sí, ¿eh?";
		link.l1 = "Es absolutamente normal, mi amor, absolutamente normal. Yo también estoy nerviosa. Creo que el padre Benoit ya está esperando, iré a él y averiguaré cuándo comenzará el servicio.";
		link.l1.go = "LongHappy_18";
		break;

	case "LongHappy_18":
		dialog.text = "Está bien, daré un paseo por el pueblo un rato, quiero prepararme, sí, ¿eh? Charles, entiendes que no hay vuelta atrás, ¿verdad?";
		link.l1 = "Mary, querida, para mí, no había vuelta atrás desde que nos conocimos. He estado esperando este día con todo mi corazón. No te preocupes, todo saldrá bien.";
		link.l1.go = "LongHappy_19";
		break;

	case "LongHappy_19":
		DialogExit();
		pchar.GenQuest.CannotWait = true; // запрет ожидания
		LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
		AddQuestRecord("LongHappy", "14");
		AddQuestUserData("LongHappy", "sName", "Mary");
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
		link.l1 = "";
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
		link.l1 = "Yo, Charles Henry de Maure, caballero de Monper, te tomo a ti, Mary Casper, como mi esposa, para tener y sostener, desde este día en adelante, en lo bueno y en lo malo, en la riqueza y en la pobreza, en la salud y en la enfermedad, hasta que la muerte nos separe. Según la Santa Ley de Dios, en presencia de Dios, hago este voto.";
		link.l1.go = "LongHappy_27";
		break;

	case "LongHappy_27":
		dialog.text = "Yo, Mary Casper, te tomo a ti, Charles de Maure, como mi esposo, para tenerte y sostenerte, desde este día en adelante, en lo bueno y en lo malo, en la riqueza y en la pobreza, en la salud y en la enfermedad, hasta que la muerte nos separe. Según la Santa Ley de Dios, en la presencia de Dios, hago este voto.";
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
		dialog.text = "¡Esto es increíble, sí, ¿eh?! Estoy... estoy llorando, lo siento Charles, yo... mi nariz se ha puesto roja, ¿verdad?";
		link.l1 = "Mary de Maure, mi esposa, eres hermosa hoy, como todos los demás días.";
		link.l1.go = "LongHappy_32";
		break;

	case "LongHappy_32":
		if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			dialog.text = "Gracias, Charles, gracias... ¡Todo es tan solemne y maravilloso! ¡Este es el mejor día de mi vida, sí, ¿eh?! ¡Mira, qué felices están todos! Pero es hora de que te pasees entre los invitados y aceptes las felicitaciones. Cuando termines, vuelve, y veamos cómo están los chicos en la taberna.";
		else
			dialog.text = "Gracias, Charles, gracias... ¡Todo es tan solemne y maravilloso! ¡Este es el mejor día de mi vida, sí, ¿eh?! ¡Mira, qué contentos están todos! Pero, es hora de que pasees entre los invitados y aceptes las felicitaciones. Cuando termines, vuelve, nos esperan en Sharptown.";
		link.l1 = "Lo haré de inmediato, cariño. ¡Un beso y me voy!";
		link.l1.go = "LongHappy_33";
		break;

	case "LongHappy_33":
		DialogExit();
		LongHappy_MarryKiss();
		break;

	case "LongHappy_34":
		dialog.text = "Charles, mi amor, ¿ya has hablado con los invitados?";
		link.l1 = "Todavía no, ten paciencia, cariño, volveré pronto.";
		link.l1.go = "LongHappy_34_1";
		link.l2 = "Sí, ¿eh? Nunca había escuchado tantas felicitaciones de una vez. ¡Y sabes qué! La mayoría las dijo con sinceridad.";
		link.l2.go = "LongHappy_35";
		break;

	case "LongHappy_34_1":
		DialogExit();
		npchar.dialog.currentnode = "LongHappy_34";
		break;

	case "LongHappy_35":
		if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
		{
			dialog.text = "¡Sí, sí! También me dijeron muchas cosas agradables. No todos, por supuesto, algunos están claramente sorprendidos por mi atuendo, sí, ¿eh? Pero estoy tan feliz, que la mitad de las cosas que dicen simplemente pasan de largo. Y en general, todos son tan encantadores. Charles, los chicos de la taberna ya nos esperan - deberíamos ir a ellos. Estarán felices de felicitar a su capitán, sí, ¿eh?";
			link.l1 = "Nos vamos ahora mismo. Pero me gustaría terminar este día en un lugar más romántico que la habitación de la taberna del puerto. Espero, esposa mía, que no te importe pasar esta noche en nuestra cabina. Además, ahora no hay vigilancia en el barco...";
		}
		else
		{
			dialog.text = "¡Sí, sí! ¡También me dijeron tantas cosas agradables! No todos, por supuesto, algunos claramente se sorprenden por mi atuendo, ¡sí, ¿eh?! Pero estoy tan feliz, que la mitad de las cosas que la gente dice simplemente pasan de largo. Y en general, todos son tan simpáticos. ¡Charles! Pero nos esperan en Sharptown, ¿cuándo zarparemos?";
			link.l1 = "Ahora mismo. ¡No podemos permitir que nuestros invitados se beban todas las provisiones! Espero, mi esposa, que no te importe pasar esta noche en nuestra cabina, sí, ¿eh?";
		}
		link.l1.go = "LongHappy_36";
		break;

	case "LongHappy_36":
		dialog.text = "¡Incluso en una choza en una isla desierta, pero solo contigo, por supuesto!";
		if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			link.l1 = "Lo sé. Yo también te amo. Vamos, antes de que los chicos beban todo nuestro ron y prendan fuego a la taberna.";
		else
			link.l1 = "Yo también. Yo también te amo. Entonces, ¡zarpemos!";
		link.l1.go = "LongHappy_37";
		break;

	case "LongHappy_37":
		DialogExit();
		npchar.dialog.currentnode = "LongHappy_38";
		LongHappy_MarryComplete();
		break;

	case "LongHappy_38":
		dialog.text = "¡Oh, mi querido, estoy tan feliz! Hoy es un día maravilloso...";
		link.l1 = "";
		link.l1.go = "LongHappy_38_1";
		break;

	case "LongHappy_38_1":
		DialogExit();
		npchar.dialog.currentnode = "LongHappy_38";
		break;

	case "LongHappy_39":
		dialog.text = "¡Arráncale la cabeza sucia, Charles!";
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
		dialog.text = "Estoy bien, sí, ¿eh? ¿Cómo está Nathan, sigue con vida?";
		link.l1 = "Tanta sangre... Dannie, ¿está respirando? ¡Lo veo respirar!";
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
		dialog.text = "¡Ganamos, sí, ¿eh?! Perdóname, llego tarde. Estábamos atrapados arriba, había una docena de esos bastardos, así que estaba un poco ocupada, sí, ¿eh?";
		link.l1 = "Está bien, lo manejé. Me alegra haber podido terminar esa historia con Jacques... finalmente. Él obtuvo lo que merecía.";
		link.l1.go = "LongHappy_45";
		break;

	case "LongHappy_45":
		dialog.text = "¡Entonces termina aquí y regresa a Sharptown! Deberíamos ver cómo está Nathan, ¡sí, ¿eh? Arriesgó su vida por nosotros!";
		link.l1 = "Tienes razón, mi amor. Ve, estoy justo detrás de ti.";
		if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner"))
			link.l1.go = "LongHappy_46";
		else
			link.l1.go = "LongHappy_48";
		break;

	case "LongHappy_46":
		dialog.text = "Por cierto, cariño, encontramos a Marcus, ¡sí, ¿eh?! Estaba en la bodega de carga, atado e inconsciente.";
		link.l1 = "¿Está vivo?";
		link.l1.go = "LongHappy_47";
		break;

	case "LongHappy_47":
		dialog.text = "Está herido, pero estará bien. ¡No puedes quebrar a nuestro barón, sí, ¿eh?! Apenas se ha despertado y ya está ansioso por la batalla.";
		link.l1 = "¡Este es nuestro buen viejo Marcus! Bueno, termina aquí y a la orilla.";
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
			dialog.text = "Lo siento mucho, Charles, sí, ¿eh? Yo... salí a dar un paseo. Vi que habías regresado, escuché que todos estaban llenos de vida por la victoria, pero yo... ¡Pero qué me pasa, sí, ¿eh?!";
			link.l1 = "Todo va a estar bien, amor, todo va a estar bien. Yo también estoy triste. Pero ganamos, y Jacques Barbazon pagó por todo lo que ha hecho.";
			link.l1.go = "LongHappy_50";
		}
		else
		{
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Me siento tan mal por Gino, Charles, ¡sí, ¿eh?! ¡Cuando me enteré, no lo creí! ¿Cómo estás?";
				link.l1 = "No puedo creerlo tampoco... resultó tan estúpido, no imaginé este día así.";
			}
			else
			{
				dialog.text = "¡Ganamos de nuevo, sí, ¿eh?! ¡Mi esposo es una tormenta para los barones rebeldes de la Cofradía de los Hermanos de la Costa! Los amigos están vivos y los enemigos muertos - un regalo glorioso, sí, ¿eh?!";
				link.l1 = "Sí, qué celebración, pero lo logramos, mi amor. Lo logramos, sí, ¿eh?";
			}
			link.l1.go = "LongHappy_50";
		}
		break;

	case "LongHappy_50":
		dialog.text = " Apenas te mantienes en pie, sí, ¿eh? Vamos, Dannie nos encontró una casa aquí en las afueras, no quiero volver al barco ahora. Nos sentaremos y beberemos por nuestros amigos caídos. Todo esto es demasiado para una cabeza sobria, sí, ¿eh?";
		link.l1 = "Sí, Mary, vámonos.";
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
			dialog.text = "Me siento tan mal por Gino, Charles, ¡sí, ¿eh?! ¡Cuando me enteré, no podía creerlo! ¿Cómo estás?";
			link.l1 = "No puedo creerlo tampoco... resultó tan estúpido, no imaginé este día así.";
		}
		else
		{
			dialog.text = "Lamento llegar tarde, mi querido, sí, ¿eh? Fui a dar un paseo, luego vi cómo te acercabas y corrí lo más rápido que pude. Dannielle me tranquilizó cuando Gino dijo 'el peligro ha pasado', sí, ¿eh? ¡Estoy tan contenta de que todo esté bien ahora!";
			link.l1 = "Yo también, cariño. Y ganamos. Barbazon está muerto, los barones están reuniendo lo que queda de sus tripulaciones. La lucha ha terminado.";
		}
		link.l1.go = "LongHappy_53";
		break;

	case "LongHappy_53":
		dialog.text = "Charles, te veo apenas mantenido en pie, pero nadie puede encontrar a Tichingitu.";
		link.l1 = "Jan me dio una especie de pista... Me parece que nuestro áspero maskogue fue a divertirse. Vamos a dar un paseo hasta la Ensenada de Sabo-Matila, algunas personas lo vieron irse en esa dirección.";
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
		dialog.text = "Bueno, ¡ese es nuestro nativo rígido, sí, ¿eh?! Vamos, Dannie nos encontró una casa aquí en las afueras - estás caminando dormido en este punto, Charles, sí, ¿eh?";
		link.l1 = "Ahí está ... secuéstrame, mi hermosa india. Y que todo parezca un mal sueño mañana.";
		link.l1.go = "LongHappy_56";
		break;

	case "LongHappy_56":
		DialogExit();
		DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;

	case "LongHappy_57":
		dialog.text = "No me malinterpretes, mi esposo, en la iglesia todo fue simplemente lujoso, pero aquí la atmósfera es claramente más acogedora, sí, ¿eh? Bueno, eso es todo, Charles, ahora que todos los problemas han quedado atrás, podemos relajarnos.";
		link.l1 = "Bueno, no es exactamente 'todo', mi esposa - ¡nuestra vida continúa juntos! En general, se puede decir que apenas ha comenzado hoy. Así que, vamos, tomemos una copa con nuestros muchachos, y luego - bueno, ya recuerdas: la cabina, el vino, y nosotros...";
		link.l1.go = "LongHappy_58";
		break;

	case "LongHappy_58":
		DialogExit(); // телепорт в каюту
		DoQuestReloadToLocation("My_Cabin", "rld", "loc1", "LongHappy_InSPcabin");
		break;

	case "LongHappy_59":
		dialog.text = "Mi esposo... Suena tan dulce, sí, ¿eh? ¡Ahora eres mío, para siempre!";
		link.l1 = "Ya he sido tuya desde hace mucho tiempo, y lo seré para siempre, mi amor...";
		link.l1.go = "LongHappy_60";
		break;

	case "LongHappy_60":
		DialogExit();
		DoQuestCheckDelay("Mary_LoveSex", 1.0);
		npchar.dialog.currentnode = "LongHappy_61";
		LAi_SetStayType(npchar);
		break;

	case "LongHappy_61":
		dialog.text = "¡Estoy tan feliz, Charles! Y ahora, tenemos que seguir moviéndonos de nuevo, ¿verdad?";
		link.l1 = "¡Claro, cariño! Lado a lado, juntos y para siempre, sí, ¿eh?";
		link.l1.go = "LongHappy_62";
		break;

	case "LongHappy_62":
		DialogExit();
		LAi_SetOfficerType(npchar);
		npchar.dialog.currentnode = "Mary_officer";
		DoQuestReloadToLocation("FortFrance_town", "reload", "reload1", "LongHappy_InSPComplete");
		break;

	// Jason Исла Мона
	case "IslaMona":
		dialog.text = "Me temo que esta pandemia está afectando a tus chicas, Rodrigo. ¡Mantenlas ocupadas con el tejido o algo así!";
		link.l1 = "Esta conversación claramente no va a ninguna parte. Acordamos que iremos a la iglesia mañana. A rezar... por supuesto.";
		link.l1.go = "IslaMona_1";
		break;

	case "IslaMona_1":
		DialogExit();
		LAi_SetOfficerType(npchar);
		npchar.dialog.currentnode = "Mary_officer";
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
		npchar.dialog.currentnode = "Mary_officer";
		sld = characterFromId("Himenes_companion_1");
		sld.dialog.currentnode = "island_man_2";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "IslaMona_4":
		dialog.text = "Bueno, Charles...";
		link.l1 = "¿Qué tienes en mente otra vez, Mary?";
		link.l1.go = "IslaMona_5";
		break;

	case "IslaMona_5":
		dialog.text = "(se ríe) El hecho de que Alan y yo queríamos hacer lo mismo en la isla que tú has hecho aquí";
		link.l1 = "¿Tu... Alan?";
		link.l1.go = "IslaMona_6";
		break;

	case "IslaMona_6":
		dialog.text = "¡Sí, era todo un soñador, los dos podrían haber sido grandes amigos si él estuviera vivo, sí, ¿eh?";
		link.l1 = "¡Bueno, nuestros gustos coincidieron en una cosa con seguridad!";
		link.l1.go = "IslaMona_7";
		break;

	case "IslaMona_7":
		dialog.text = "¿Qué? ¡Ja-ja-ja! ¡Para, Charles!\nDe cualquier manera, esto es increíble, les hemos dado a estas personas tanta alegría, sí, ¿eh?";
		link.l1 = "Les dimos una oportunidad de ser felices, pero el resto, lo han hecho por su cuenta. Entonces, ¿en qué estás pensando?";
		link.l1.go = "IslaMona_8";
		break;

	case "IslaMona_8":
		dialog.text = "Ven a buscarme más tarde y lo descubrirás...";
		link.l1 = "¡Claro que sí lo haré!";
		link.l1.go = "IslaMona_9";
		break;

	case "IslaMona_9":
		DialogExit();
		LAi_SetOfficerType(npchar);
		LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
		ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
		DoQuestCheckDelay("Mary_LoveSex", 2.0);
		NextDiag.CurrentNode = "sex_after";
		npchar.greeting = "mary_hire";
		pchar.questTemp.IslaMona.Doorlock = "true";
		break;

	case "tonzag_jailed":
		dialog.text = "Me gusta la oscuridad y los espacios estrechos. Me hace sentir calma. Finalmente, puedo reunir mis pensamientos\nEs como si todas las preocupaciones y problemas... se fueran, ¡sí! Realmente extraño esta sensación...";
		link.l1 = "Necesitas ver a un médico.";
		link.l1.go = "tonzag_jailed_1";
		link.l2 = "Correcto. Es como si estuvieras de vuelta en 'Ceres Smithy'.";
		link.l2.go = "tonzag_jailed_2";
		locCameraFromToPos(-15.50, 2.28, -1.23, true, -27.00, -10.60, -22.70);
		break;

	case "tonzag_jailed_1":
		dialog.text = "… Lástima que no esté sola. En silencio, en la oscuridad y en soledad, sí, ¿eh? Eso sería perfecto.";
		link.l1 = "Mantén el ritmo, Mary Casper.";
		link.l1.go = "exit";
		break;

	case "tonzag_jailed_2":
		dialog.text = "Una vez un cangrejo se metió en mi cama - Lo corté y me lo comí. Sí, ¿eh?";
		link.l1 = "Mantén el rumbo, Mary Casper.";
		link.l1.go = "exit";
		break;

	case "tonzag_aftershot":
		dialog.text = "¡Canalla enmascarado! ¡Ay! Ayúdame, querido - ¡necesitamos romper las barras!";
		link.l1 = "¡Silencio! ¡Estoy tratando de averiguar qué hacer!";
		link.l1.go = "exit";

		NextDiag.TempNode = "Mary_officer";
		AddDialogExitQuestFunction("Tonzag_TichingituAfterShot");
		break;

	case "tonzag_after_boarding":
		dialog.text = "¡Querido, esos diablos enmascarados están por todas partes! Han hecho un gran agujero en el casco y están arrastrándose por él como esos cangrejos. ¡Tenemos que cortarlos a todos, sí, ¿eh?!";
		link.l1 = "¡Mary, quédate aquí, encuentra al oficial superior y toma el mando! ¡Saca el barco de la batalla; no resistiremos otro abordaje!";
		link.l1.go = "tonzag_after_boarding_1";
		DelLandQuestMark(npchar);
		break;

	case "tonzag_after_boarding_1":
		dialog.text = "¿Y adónde vas? ¡No pienso dejarte ir!";
		link.l1 = "¡Necesito ayudar a Hércules y a nuestra tripulación! ¡Confía en mí, Mary!";
		link.l1.go = "tonzag_after_boarding_2";
		break;

	case "tonzag_after_boarding_2":
		dialog.text = "¡Aye aye, querida!";
		link.l1 = "";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;

	case "tonzag_after_victory":
		dialog.text = "¡Victoria, sí! ¡Ven a mí, querida! ¡Te quiero por una hora o dos!";
		link.l1 = "Eh...";
		link.l1.go = "tonzag_after_victory_1";
		link.l2 = "¡Vamos!";
		link.l2.go = "tonzag_after_victory_1";
		break;

	case "tonzag_after_victory_1":
		dialog.text = "¡Hola, Hércules! ¡Estoy tan contenta de verte, barba gris!";
		link.l1 = "";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("Tonzag_MaryBoardingDialog");
		break;

	case "tonzag_after_victory_2":
		dialog.text = "";
		link.l1 = "¡Mary, Mary, espera! ¡Necesito tu informe!";
		link.l1.go = "tonzag_after_victory_3";
		break;

	case "tonzag_after_victory_3":
		dialog.text = "¿Eh? ¡Bueno, ganamos, sí! Esa maldita nave huyó. ¡Le partí el cráneo a un bastardo en dos!\n¡Uf, malditos botones!";
		link.l1 = "Oh, Mary...";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;

	case "tonzag_dead":
		dialog.text = "Oh Dios, ¡no me mires, querido! Voy a... ¡uf!";
		link.l1 = "¡Aguanta, chica! ¡Estoy aquí!";
		link.l1.go = "exit";

		NextDiag.TempNode = "Mary_officer";
		break;

	//--> ----------------------------------- офицерский блок ------------------------------------------
	case "Mary_officer":
		// если шлялся по борделям - устроит небольшой скандал
		if (sti(pchar.GenQuest.BrothelCount) >= 3 && LAi_grp_playeralarm == 0)
		{
			dialog.Text = "" + pchar.name + "¡Necesito hablar contigo, sí, ¿eh! En serio!";
			Link.l1 = "¿Qué sucedió, Mary? ¿Hay un problema?";
			Link.l1.go = "brothel";
			break;
		}
		ref rLoc = &Locations[FindLocation(pchar.location)];
		dialog.text = LinkRandPhrase("¡Te escucho, mi querido capitán!", "Sí, " + pchar.name + "¡Estoy toda oídos!", "¿Tienes alguna tarea para mí, " + pchar.name + "?");
		if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
		{
			Link.l4 = "Mary, voy a visitar la antigua ciudad india de Tayasal. No te mentiré: este viaje es muy peligroso y más aún - incluye teleportación a través del ídolo del que te hablé. ¿Me... seguirás?";
			Link.l4.go = "tieyasal";
		}
		////////////////////////казначей///////////////////////////////////////////////////////////
		// boal отчёт о корабле
		if (CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
		{
			Link.l11 = "Mary, dame un informe completo del barco.";
			Link.l11.go = "QMASTER_1";

			// Warship. Автозакупка товара
			Link.l12 = "Quiero que compres ciertos bienes cada vez que estemos atracados.";
			Link.l12.go = "QMASTER_2";
		}

		if (CheckAttribute(npchar, "quest.fugas"))
		{
			Link.l3 = "Mary, necesito tu consejo.";
			Link.l3.go = "fugas";
		}
		Link.l1 = "Mary, tengo una orden para ti...";
		Link.l1.go = "stay_follow";
		if (pchar.location == Get_My_Cabin() && !CheckAttribute(npchar, "quest.daily_sex"))
		{
			Link.l2 = RandPhraseSimple("Querido, te deseo ahora mismo. ¿Estás de acuerdo con eso, sí, ¿eh?", "Mary, ¿qué tal si... nos quedamos juntos un rato? Solo nosotros dos, sí, ¿eh?");
			Link.l2.go = "cabin_sex";
		}
		if (rLoc.type == "tavern" && !CheckAttribute(npchar, "quest.daily_sex") && sti(pchar.money) >= 10)
		{
			Link.l2 = RandPhraseSimple("Mary, ¿rentamos una habitación y nos quedamos juntos?", "Amor, quiero quedarme contigo en privado... ¿qué tal si alquilamos una habitación y nos olvidamos de todo por unas horas, sí, ¿eh?");
			Link.l2.go = "room_sex";
		}
		link.l9 = "No es nada hasta ahora, Mary.";
		link.l9.go = "exit";
		NextDiag.TempNode = "Mary_officer";
		break;

	/////////////////////////// ответы для казначея ///////////////////////////////////
	case "QMASTER_1":
		dialog.Text = "¡Charles, es una belleza, sí, ¿eh?! Arreglamos ese pequeñísimo agujero bajo la línea de flotación y secamos las velas. ¿Qué- qué esperabas? No me mires así, nunca he estudiado para ser intendente.";
		Link.l1 = "Lo siento, Mary, realmente no lo pensé bien, sí, ¿eh?";
		Link.l1.go = "exit";
		break;

	case "QMASTER_2":
		dialog.text = "¡Charles, pero estoy bien! Ya tengo mi guardarropa y mi espada. Pero gracias por preguntar, es muy amable de tu parte, sí, ¿eh?";
		link.l1 = "Pero ni siquiera... Sea como sea, olvídalo, querido, estamos bien.";
		link.l1.go = "exit";
		break;

	case "stay_follow":
		dialog.Text = "¿Órdenes?";
		Link.l1 = "¡Quédate aquí!";
		Link.l1.go = "Boal_Stay";
		Link.l2 = "¡Sígueme y no te quedes atrás!";
		Link.l2.go = "Boal_Follow";
		sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
		if (sGun != "")
		{
			rItm = ItemsFromID(sGun);
			if (CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
			{
				Link.l3 = "Mary, cambia la munición para las armas de fuego.";
				Link.l3.go = "SetGunBullets";
			}
		}
		break;

	case "SetGunBullets":
		Dialog.Text = "Eligiendo el tipo de munición:";
		sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
		rItm = ItemsFromID(sGun);
		makearef(rType, rItm.type);
		for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
		{
			sAttr = GetAttributeName(GetAttributeN(rType, i));
			sBullet = rItm.type.(sAttr).bullet;
			rItem = ItemsFromID(sBullet);
			attrL = "l" + i;
			Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
			;
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
		notification(GetFullName(NPChar) + " " + XI_ConvertString("AmmoSelectNotif") + GetConvertStr(rItem.name, "ItemsDescribe.txt") + "", "AmmoSelect");
		DeleteAttribute(NPChar, "SetGunBullets");
		DialogExit();
		break;

	case "Boal_Stay":
		Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
		AddDialogExitQuestFunction("LandEnc_OfficerStay");
		dialog.Text = "¡Enseguida, mi capitán!";
		Link.l1 = "¡Vaya, eres todo un caballero: apenas guardaste tu sable y ya me colmas de halagos. Muchas gracias por tu ayuda. De verdad me has salvado, sí, ¿eh? Preséntate, por favor, caballero, que es la primera vez que te veo. ¿Llevas mucho tiempo en la isla?";
		Link.l1.go = "Exit";
		Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
		break;

	case "Boal_Follow":
		SetCharacterTask_FollowCharacter(Npchar, PChar);
		dialog.Text = "¡De inmediato, mi capitán!";
		Link.l1 = "¿Cómo te encuentras hoy, sí, ¿eh?";
		Link.l1.go = "Exit";
		break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
