// диалоги персонажей по квесту Долго и счастливо
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "First time":
		dialog.text = "¿Qué necesitas?";
		link.l1 = "Nada.";
		link.l1.go = "exit";
		break;

	// вестовой капитан в порту
	case "cureer":
		dialog.text = "Monsieur de Maure, ¡qué suerte! ¡Te he estado buscando durante meses!";
		link.l1 = "Mi querida, no compro mapas falsos, información dudosa ni ron casero, ¡gracias! ¿O eres un cazarrecompensas? ¿Y cuánto vale mi cabeza ahora?";
		link.l1.go = "cureer_1";
		break;

	case "cureer_1":
		dialog.text = "¡Oh, monsieur, yo... yo no comerció con chatarra ni mato gente - no toques la espada, no la necesitarás, ¡no pretendo hacer daño! Todo es mucho más prosaico - soy capitán de un barco de mensajería. Distribuyo correo. ¡Y para usted, tengo una correspondencia importante!";
		link.l1 = "¿Una carta? ¿Quién es el remitente, si se puede saber?";
		link.l1.go = "cureer_2";
		break;

	case "cureer_2":
		dialog.text = "Un abad me lo entregó y pidió que lo llevara al capitán de Maure personalmente, de mano en mano. Ya había perdido toda esperanza de encontrarte y quería dejarlo en la oficina del puerto en Saint-Pierre, ¡pero qué suerte, aquí estás!";
		link.l1 = "Sí, aquí estoy, estoy esperando - dame la carta.";
		link.l1.go = "cureer_3";
		break;

	case "cureer_3":
		dialog.text = "Hay un problema... El abad dijo que la entrega sería pagada por el destinatario. Así que debes nueve mil doscientos pesos.";
		link.l1 = "¡Por semejante cantidad de dinero, debería haber sido traído a mí en mar abierto directamente a la cabina, junto con el café de la mañana! Puedes quedarte la carta para ti.";
		link.l1.go = "cureer_6";
		if (sti(pchar.money) >= 9200)
		{
			link.l2 = "¿Y por qué no me dediqué a la entrega de correo? ¡Esto es más rentable que la piratería! Aquí tienes tu plata, querida, dame el sobre.";
			link.l2.go = "cureer_4";
		}
		break;

	case "cureer_4":
		AddMoneyToCharacter(pchar, -9200);
		dialog.text = "¡Un placer tratar con usted! ¡El Abad Benoit le envía los mejores deseos! ¡Adiós monsieur de Maure!";
		link.l1 = "";
		link.l1.go = "cureer_5";
		break;

	case "cureer_5":
		DialogExit();
		chrDisableReloadToLocation = false;
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
		LongHappy_RecibeLetter();
		break;

	case "cureer_6":
		dialog.text = "Como desees. Dejaré el sobre en la oficina del puerto. Pero afectará el precio, te advierto. Y sí, el Abad Benoit te envía los mejores deseos.";
		link.l1 = "¿La carta del Abad Benoit? ¡¿Por qué no lo dijiste desde el principio?! ¡Debe ser importante!";
		link.l1.go = "cureer_7";
		break;

	case "cureer_7":
		dialog.text = "Así que recógelo del jefe del puerto. No olvides tomar un préstamo por adelantado. Adiós, capitán de Maure.";
		link.l1 = "Conocí a piratas más sinceros que tú. Buena suerte, mi querido.";
		link.l1.go = "cureer_8";
		break;

	case "cureer_8":
		DialogExit();
		chrDisableReloadToLocation = false;
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
		pchar.questTemp.LongHappy = "portman";
		break;

	// испанский офицер в Сантьяго
	case "spa_officer":
		dialog.text = "Padre Santo, hoy ha llegado más temprano de lo habitual. Por favor, su escolta le espera. Y usted, señor de Maure - el padre Vincento se enteró de que estaba en la ciudad y le insta a unirse a él para cenar.";
		link.l1 = "Temo que el Inquisidor cenará solo. Espero que esto no le quite el apetito. Y el Abad Benoit también le privará de su compañía. Sabes quién soy, así que te recomiendo que nos dejes pasar sin ningún conflicto y le des mis mejores deseos al Padre Palotti.";
		link.l1.go = "spa_officer_1";
		break;

	case "spa_officer_1":
		if (sti(pchar.reputation.nobility) > 80 || sti(pchar.reputation.nobility) < 20) // провести учёт чести и известности
		{
			dialog.text = "Sí, he oído mucho sobre ti, y tengo instrucciones claras de no convertir la ciudad en un baño de sangre si te pones terco. Puedes pasar. Pero el padre Vincento estará... insatisfecho. Ten esto en cuenta.";
			link.l1 = "Actuaste razonablemente, monsieur. Sobreviviré, de alguna manera, el dolor en mi corazón causado por la insatisfacción del padre-inquisidor. ¡Que tengas una buena noche!";
			link.l1.go = "spa_officer_2";
		}
		else
		{
			dialog.text = "Sí, he oído hablar de ti... muchas cosas interesantes. Sin embargo, rechazar tales invitaciones es peligroso para la salud, señor. Al igual que secuestrar a los invitados del padre Vincento. ¡Deténganlos!";
			link.l1 = "Todos han hecho su elección. Lamento que haya llegado a esto. ¡A las armas, caballero!";
			link.l1.go = "spa_officer_3";
		}
		break;

	case "spa_officer_2":
		DialogExit();
		chrDisableReloadToLocation = false;
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
		for (i = 1; i <= 4; i++)
		{
			sld = characterFromId("LH_escort_" + i);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3_back", "none", "", "", "", 15.0);
		}
		ChangeCharacterComplexReputation(pchar, "authority", 3);
		pchar.quest.longhappy_santiago2.win_condition.l1 = "location";
		pchar.quest.longhappy_santiago2.win_condition.l1.location = "Cuba1";
		pchar.quest.longhappy_santiago2.function = "LongHappy_SantiagoSail";
		pchar.quest.longhappy_santiago3.win_condition.l1 = "location";
		pchar.quest.longhappy_santiago3.win_condition.l1.location = "Cuba2";
		pchar.quest.longhappy_santiago3.function = "LongHappy_SantiagoSail";
		break;

	case "spa_officer_3":
		DialogExit();
		chrDisableReloadToLocation = false;
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
		for (i = 1; i <= 4; i++)
		{
			sld = characterFromId("LH_escort_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			LAi_group_Attack(sld, Pchar);
		}
		SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
		LAi_SetFightMode(pchar, true);
		ChangeCharacterNationReputation(pchar, SPAIN, -20);
		ChangeCharacterComplexReputation(pchar, "nobility", -3);
		pchar.quest.longhappy_santiago2.win_condition.l1 = "location";
		pchar.quest.longhappy_santiago2.win_condition.l1.location = "Cuba1";
		pchar.quest.longhappy_santiago2.function = "LongHappy_SantiagoSail";
		pchar.quest.longhappy_santiago3.win_condition.l1 = "location";
		pchar.quest.longhappy_santiago3.win_condition.l1.location = "Cuba2";
		pchar.quest.longhappy_santiago3.function = "LongHappy_SantiagoSail";
		break;

	case "Guests_block":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		break;

	// Ян Свенсон патер
	case "Svenson":
		dialog.text = "¡Charles, felicidades! Sabes - siempre me has caído bien, y Helen para mí es como una hija, así que estoy feliz por ambos. Maldita sea... soltar una lágrima en una iglesia es todo lo que siempre he querido, ¿me estoy haciendo viejo o qué?";
		link.l1 = "Todo está bien, Jan, casi lloro cerca del altar. ¿Incienso, quizás?";
		link.l1.go = "Svenson_1";
		break;

	case "Svenson_1":
		dialog.text = "¡Claro, alcanfor, maldita sea! He estado pensando, ¡por qué me pican los ojos y me escuece la nariz! Bien, hablaremos en Sharptown, abrazaremos a Gladys y nos iremos a los demás. Tienen unas caras como si estuviéramos firmando la Paz de Westfalia.";
		link.l1 = "Gracias por venir aquí, Jan. Me alegra verte, y significa mucho para Helen.";
		link.l1.go = "Guests_block";
		break;

	// Ян Свенсон на Исла Тесоро
	case "Svenson_2":
		pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count) + 1;
		dialog.text = "¡Aquí estás, finalmente, Charles! Mi corbeta te adelantó por casi un día... bastante motivo para estar orgulloso.";
		link.l1 = "Eres bienvenido Jan, pero ¿dónde está Gladys, y tu esposa?";
		link.l1.go = "Svenson_3";
		break;

	case "Svenson_3":
		dialog.text = "Mandé a Gladys de vuelta a Blueveld en un barco mercante - no aprueba todas estas fiestas deslumbrantes. Joanna no pudo llegar, ¡oh, no tuve tiempo de contártelo en Martinica! Imagínate, en mi vejez, me convertiré en un padre legítimo, ¿qué te parece? Mira, si te das prisa, ¡nuestras crías tendrán casi la misma edad, jajaja!";
		link.l1 = "¡Jan, mis felicitaciones, esas son buenas noticias! ¡Debemos brindar por ello!";
		link.l1.go = "Svenson_4";
		break;

	case "Svenson_4":
		dialog.text = "¡Definitivamente! Pero primero, ¡por ti y tu media naranja! ¡Eh, tú, cállate!!! ¡El viejo Forest Devil debe dar un discurso!\nKhe-khe... Así que, nuestros queridos Monsieur y Madame de Maure... ¡Al diablo! ¡No puedo hablar así! Charles, Helen, para mí, ustedes dos son como mis propios hijos, y sé que en esta sala no hay nadie que no esté feliz por vuestra unión. ¡Así que brindemos, mis hermanos, por la felicidad de nuestros fieles amigos, por el viento favorable en sus velas y por el amor de la Dama Fortuna, tan fuerte como sus sentimientos el uno por el otro!!! ¡Salud!";
		link.l1 = "¡Salud! Gracias, Jan... oh, este ron es mucho más fuerte de lo habitual... ¿Qué le mezcló Nathan?";
		link.l1.go = "Svenson_5";
		break;

	case "Svenson_5":
		dialog.text = "No tengo idea, pero parece acertado. El Viejo Hawk es generalmente un experto en bebidas. Vamos, ve con los demás, necesito preparar bebidas para un buen centenar de almas ansiosas por saciarse.";
		link.l1 = "¡Forest Devil sirviendo bebidas - qué vista! Gracias por encargarte de la organización de la fiesta. Definitivamente regresaré, tan pronto como me haya reunido con todos - tal vez alguien necesite ayuda.";
		link.l1.go = "Svenson_6";
		break;

	case "Svenson_6":
		DialogExit();
		npchar.dialog.currentnode = "Svenson_6_1";
		if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed))
			LongHappy_IslaTesoroToVine();
		break;

	case "Svenson_6_1":
		dialog.text = "¿Todo está bien, Charles?";
		link.l1 = "Perfecto, Jan!";
		link.l1.go = "Svenson_6";
		break;

	case "Svenson_7":
		pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count) + 1;
		dialog.text = "¡Y aquí estás, finalmente! ¿Cómo te fue en Martinica? ¿Sientes que tu vida ha cambiado para siempre?";
		link.l1 = "Ha cambiado mucho antes, Jan. Pero todo salió sorprendentemente bien. ¿Dónde está Joahnna y...?";
		link.l1.go = "Svenson_8";
		break;

	case "Svenson_8":
		dialog.text = "¿Helen? La muchacha zarpó tan pronto como se enteró de lo que estábamos tramando y navegó hacia el horizonte. Te envió todo tipo de cálidas felicitaciones, pero aun así... le rompiste el corazón, oh, realmente lo hiciste. Sin embargo, todo estará bien, es solo la juventud.";
		link.l1 = "Bueno, el corazón quiere lo que quiere, lo entiendes.";
		link.l1.go = "Svenson_9";
		break;

	case "Svenson_9":
		dialog.text = "Yo sí. Bueno, Joahnna no pudo llegar, imagínate - en mi vejez, me convertiré en un padre legal, ¿qué te parece eso? Mira, si te apresuras, nuestros descendientes tendrán casi la misma edad, ¡jajaja!";
		link.l1 = "¡Jan, mis felicitaciones, esas son buenas noticias! ¡Deberíamos beber por ello!";
		link.l1.go = "Svenson_10";
		break;

	case "Svenson_10":
		dialog.text = "¡Definitivamente! Pero primero, ¡a ti y a tu media naranja! ¡Oye, tú allí, cállate!!! ¡El viejo Forest Devil debe dar un discurso!\n¡Charles y Mary, todo el Hermandad está levantando copas en su honor ahora! La felicidad de los verdaderos amigos complace el alma de cualquier lobo de mar, casi tanto como el esplendor del oro español, ¡ja-ja! ¡Naveguen bien, y que los vientos favorables los sigan en su viaje familiar!!! ¡Salud!";
		link.l1 = "¡Salud! Gracias Jan... oh, este ron es mucho más fuerte de lo habitual... ¿Qué le mezcló Nathan?";
		link.l1.go = "Svenson_11";
		break;

	case "Svenson_11":
		dialog.text = "Tengo ni idea, pero parece acertado. El Viejo Hawk es generalmente un experto en bebidas. Vamos, ve con los demás, necesito preparar bebidas para un buen centenar de almas ansiosas por saciarse.";
		link.l1 = "Esta taberna definitivamente necesita ser renombrada - '¡El mismo Forest Devil estaba aquí detrás del mostrador'! Gracias, Jan, definitivamente regresaré, tan pronto como pase por todos - tal vez, alguien necesite ayuda.";
		link.l1.go = "Svenson_6";
		break;

	case "Svenson_12":
		dialog.text = "¿Cómo te va, Charles? ¿Cómo va la boda?";
		link.l1 = "Muy conmovedor, Jan. Me alegra que hayamos logrado traernos a todos aquí. Parece que los barriles de ron de Hawk empiezan a mostrar su fondo, ¿verdad?";
		link.l1.go = "Svenson_13";
		break;

	case "Svenson_13":
		dialog.text = "¡Sí, lo están! Así que es hora de abrir lo que trajiste aquí. Y otra cosa: esos tipos que me ayudaron al principio se emborracharon demasiado en la habitación de atrás. Parece que todavía estás de pie, novio, ¿puedes traer una caja de otro jerez?";
		link.l1 = "Claro, solo dime a dónde ir. Tal vez encuentre algunas cabezas sobrias en el camino para ayudarme. Aunque, la mayoría de mis muchachos probablemente ya estén borrachos como una cuba.";
		link.l1.go = "Svenson_14";
		break;

	case "Svenson_14":
		dialog.text = "El vino estaba amontonado en las bodegas bajo el astillero, ¿los recuerdas? Hawk dijo que lo guardáramos en el corredor lejano, ''para guardar hasta las fiestas'' - dice él. También dice que allí está la temperatura y humedad perfectas, dice que sería un lugar perfecto para una bodega. Bueno, es un gran snob.";
		link.l1 = "Hizo una decisión correcta, Jan. Me iré, pero primero, dime, ¿viste a mi esposa?";
		link.l1.go = "Svenson_15";
		break;

	case "Svenson_15":
		dialog.text = "Ella y Dannie fueron a algún lugar. Deja que las chicas hablen, Charles, y nosotros tenemos que empezar una verdadera fiesta. Ve a las bodegas mientras yo me ocupo de la comida. ¡Porque huele como que pronto estaremos comiendo carbón en lugar de costillas de cordero!";
		link.l1 = "Está bien, ve a salvar la carne, yo traeré nuestro vino.";
		link.l1.go = "Svenson_16";
		break;

	case "Svenson_16":
		DialogExit();
		npchar.dialog.currentnode = "Svenson_6_1";
		LongHappy_IslaTesoroToVineGo();
		break;

	case "Svenson_17":
		dialog.text = "¡Charles, Nathan, qué ocurrió, ¿empezaron una pelea de borrachos?!";
		link.l1 = "No, Jan, luchamos juntos contra unos cúteres armados en las mazmorras. Nos encargamos de ellos, pero solo eran exploradores, ¡el escuadrón principal está justo detrás de nosotros!";
		link.l1.go = "Svenson_18";
		break;

	case "Svenson_18":
		dialog.text = "¿Escuadrón? ¿De qué estás hablando?! ¡Marcus, ven aquí! Charles, vamos, cuéntanos todo.";
		link.l1 = "Como dije: hay unos bastardos en las mazmorras bajo el astillero. Bien armados. Nathan y yo luchamos contra ellos y milagrosamente los derribamos a todos. Pero hay más de camino - escuché que uno de ellos fue enviado por ayuda. Y sí, uno de ellos recordó a algún Jacques.";
		link.l1.go = "Svenson_19";
		break;

	case "Svenson_19":
		DialogExit();
		sld = characterFromId("Terrax");
		sld.dialog.currentnode = "Terrax_7";
		ChangeCharacterAddressGroup(sld, "Pirates_tavern", "tables", "stay8");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

	case "Svenson_20":
		dialog.text = "Reconozco sus caras... este, y ese bastardo tirado junto a la puerta. Son matones de Jacques el Amable. No recuerdo sus nombres, pero lo sé con certeza.";
		link.l1 = "¿Así que esto es culpa de Barbazon? ¿Está fuera de sí o qué?";
		link.l1.go = "Svenson_21";
		break;

	case "Svenson_21":
		dialog.text = "No sé, pero parece que el Kindman decidió aprovechar la oportunidad y organizar una reorganización radical entre los barones de la Hermandad.";
		link.l1 = "En este caso, espero que él mismo aparezca - he estado soñando tanto tiempo con hacerle un par de agujeros en el cuerpo. ¡Bastardo, arruinó mi boda, solo piénsalo! ¡Vamos, a las calles! ¡Daremos una bienvenida adecuada a nuestros invitados!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("LongHappy_TavernReload");
		break;

	case "Svenson_22":
		dialog.text = "¡Y aquí está nuestro héroe cansado! ¡Ja, Charles, fue algo! ¡Jacques, qué rata! ¡Mira cómo lo arregló todo, casi lo logra!";
		link.l1 = "Sí, probablemente, deberíamos haber matado a ese bastardo cuando terminamos con Jackman. Sin embargo, se acabó. Barbazon está muerto.";
		link.l1.go = "Svenson_23";
		break;

	case "Svenson_23":
		if (CheckAttribute(pchar, "questTemp.LongHappy.SvensonsShipSink"))
			dialog.text = "Bueno, no puedo decir que todo haya terminado, ¡nuestra vida sigue! Aunque me siento completamente destrozado. Soy demasiado viejo para saltar al mar desde un barco cubierto de fuego y nadar una hora entera hasta la orilla, cuidándome de los tiburones. Espero que todavía tengamos algo de ron...";
		else
			dialog.text = "Bueno, no puedo decir que todo haya terminado, ¡nuestra vida continúa! ¡Maldita sea, me siento diez años más joven! ¡Hace mucho tiempo que no peleaba así! Espero que tus reservas de ron y vino no hayan sido robadas durante el caos, ¡necesitamos beber por ello bien!";
		link.l1 = "Sí, yo también bebería, pero primero tengo que revisar la residencia, no sé si te lo han dicho o no...";
		link.l1.go = "Svenson_24";
		break;

	case "Svenson_24":
		if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
		{
			dialog.text = "¿Es sobre tu compañero indio? Sí, escuché, ¿cómo sucedió?";
			link.l1 = "Se lanzó para cubrir a mi esposa y a Dannielle de una bala disparada por un bastardo. Deberíamos irnos, te lo contaré por el camino.";
		}
		else
		{
			dialog.text = "¿Es sobre Nathan? Sí, escuché, solo que no entendí cómo sucedió.";
			link.l1 = "Saltó para cubrir a nuestras esposas de una bala disparada por un bastardo. Debemos irnos, te lo contaré en el camino.";
		}
		link.l1.go = "Svenson_25";
		break;

	case "Svenson_25":
		DialogExit();
		DoQuestReloadToLocation("Pirates_townhall", "goto", "goto4", "LongHappy_DannyInResidence");
		break;

	case "Svenson_26":
		if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
		{
			dialog.text = "Mantente fuerte, Charles. Lo siento mucho por tus muchachos. Hoy, muchos buenos hombres se han ido, y por cada uno de ellos, en el infierno, Barbazon obtendrá más aceite en su caldera.";
			link.l1 = "No tiene sentido... ¡maldita sea! Es difícil, Jan... Ya he perdido amigos, pero no puedo acostumbrarme. No sé si puedo seguir adelante.";
			link.l1.go = "Svenson_28";
		}
		else
		{
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "¿Ese tipo tranquilo, el médico? Lo siento, Charles, sinceramente. Era un buen tipo.";
				link.l1 = "Sí, Jan, yo también. Pero, me temo, el mundo de la ciencia ha perdido mucho más que yo. Era un genio... sofisticado, como todos ellos, pero... maldición...";
				link.l1.go = "Svenson_27";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
					sTemp = "tu colega indio";
				else
					sTemp = "Nathan";
				dialog.text = "Bueno, parece que ha terminado. Hoy, muchos buenos muchachos se han ido, y por cada uno de ellos, en el infierno, Barbazon recibirá más aceite en su caldera, pero " + sTemp + " estará bien y esto es lo principal.";
				link.l1 = "Tienes razón, Jan, y es un gran alivio para mi mente. ¿Cómo están los otros barones? ¿Están bien?";
				link.l1.go = "Svenson_32";
			}
		}
		break;

	case "Svenson_27":
		dialog.text = "El último inmundo de Jacques Barbazon. Tienes razón, si lo hubiéramos matado antes todo podría haber sido de otra manera.";
		link.l1 = "¿Pero de qué sirve lamentarse del pasado? El pasado no se puede cambiar. ¿Cómo están los otros barones? ¿Todos sobrevivieron?";
		link.l1.go = "Svenson_32";
		break;

	case "Svenson_28":
		dialog.text = "Nadie puede acostumbrarse a esto. ¿Brindamos por nuestros muchachos? Encontré una botella en la mesa, milagrosamente sobrevivió a este lío.";
		link.l1 = "¡Sirve, yo... Maldita sea... mil maldiciones!";
		link.l1.go = "Svenson_29";
		break;

	case "Svenson_29":
		dialog.text = "Dime sobre ellos. Este médico parecía inteligente. Se expresó con tanta sabiduría.";
		link.l1 = "Lo hizo. Pero, me temo, el mundo de la ciencia ha perdido mucho más que yo. Era un genio... sofisticado, como todos ellos. ¡El maestro de los milagros!";
		link.l1.go = "Svenson_30";
		break;

	case "Svenson_30":
		dialog.text = "¿Sobre el indio? ¿Dónde lo encontraste?";
		link.l1 = "Lo rescaté de la prisión en Guadalupe, casi inmediatamente después de mi llegada. Una historia realmente divertida y estúpida. Así que, se quedó conmigo. Él lo eligió, le di libertad pero se quedó a mi lado - lo salvé y pensó que me debía hasta el final de su vida. Lacónico, vestido de manera extraña, pero más fiel que cualquier caballero, tenía un talento también, podía acertar a una moneda con un mosquete en el aire a cualquier distancia.";
		link.l1.go = "Svenson_31";
		break;

	case "Svenson_31":
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			sld = characterFromId("Helena");
		else
			sld = characterFromId("Mary");
		dialog.text = "Bueno, te pagó la deuda, qué puedo decir. Salvado " + sld.name + " y Dannielle de ese bastardo. Me parece que es un final digno para un guerrero tan valiente.";
		link.l1 = "Lo es, Jan. Brindemos por la memoria de los caídos... Que encuentren la paz. ¿Cómo están los otros barones? ¿Están bien?";
		link.l1.go = "Svenson_32";
		break;

	case "Svenson_32":
		dialog.text = "Esta noche nos ha costado caro. Ni siquiera sé cuándo se recuperarán los Hermanos de esta masacre. Kindman eligió perfectamente el momento y el lugar para atacar. Casi lo logró - solo un poco más y todo habría terminado. Pero perdimos mucho menos de lo que podríamos haber perdido.";
		link.l1 = "";
		if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
			link.l1.go = "Svenson_33";
		else
			link.l1.go = "Svenson_35";
		break;

	case "Svenson_33":
		dialog.text = "Shark está en la enfermería, su barco recibió una andanada de veinticuatro libras. Voló por la borda, se rompió un par de costillas, tragó agua de mar, pero vive, en unos días estará como nuevo.";
		link.l1 = "";
		if (CheckAttribute(pchar, "questTemp.LongHappy.BigMarry"))
			link.l1.go = "Svenson_34"; // был Венсан
		else
			link.l1.go = "Svenson_36"; // на завершение
		break;

	case "Svenson_34":
		if (CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive"))
			dialog.text = "Bernard solo recibió un par de rasguños - estaba defendiendo la costa y limpiando las catacumbas. Ahora, está en el puerto, organizando hospitales para los heridos y funerales para aquellos que no tuvieron suerte.";
		else
			dialog.text = "Bernard no tuvo suerte, estaba despejando las casas después del ataque desde las catacumbas y se topó con un montón de estos bastardos en los almacenes. Le alcanzó una bala, directo en la cabeza. Es una lástima, era un buen capitán... Tyrex estará furioso cuando se entere.";
		link.l1 = "";
		link.l1.go = "Svenson_36"; // на завершение
		break;

	case "Svenson_35":
		if (CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive"))
			dialog.text = "Bernard solo tiene un par de rasguños - estaba defendiendo la costa y limpiando las catacumbas. Ahora, está en el puerto, organizando hospitales para los heridos y funerales para los que no tuvieron suerte.";
		else
			dialog.text = "Bernard tuvo mala suerte, estaba despejando las casas después del ataque desde las catacumbas y se topó con un montón de estos bastardos en los almacenes. Recibió una bala, directo en la cabeza. Es una lástima, era un buen capitán... Tyrex se enfurecerá cuando lo descubra.";
		link.l1 = "";
		link.l1.go = "Svenson_36"; // на завершение
		break;

	case "Svenson_36":
		dialog.text = "Sobre Hawk sabes. Dannie no le permitirá dejar la isla por al menos un mes, eso es seguro. Tenía un asunto en nuestras mentes... oh, bueno.";
		link.l1 = "";
		if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner"))
			link.l1.go = "Svenson_37";
		else
			link.l1.go = "Svenson_38";
		break;

	case "Svenson_37":
		if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Free"))
		{
			dialog.text = "Marcus está bien como siempre. Tan pronto como desembarcó, inmediatamente comenzó a sacudirles las almas a los centinelas que pasaron por alto toda esta inmundicia. Aún logra comandar la restauración del orden en el pueblo. Hombre de hierro, no de otra manera.";
			link.l1 = "El hierro es más blando. Supongo que nuestro barón está hecho de un metal que aún es desconocido para la ciencia, ¡jaja!";
		}
		else
		{
			pchar.questTemp.LongHappy.Terrax.Lost = "true";
			dialog.text = "Solo con Marcus es incomprensible, su barco fue abordado, pero los sobrevivientes afirman que logró saltar por la borda. Ya envié los botes para buscar en la bahía. Espero que resulte que nuestro barón sea lo suficientemente duro como para no rendirse tan fácilmente.";
			link.l1 = "Eso es malo, pero es demasiado pronto para llorar por él, Marcus no se rendiría con nosotros tan fácilmente. Esperemos el resultado de las búsquedas.";
		}
		link.l1.go = "Svenson_39";
		break;

	case "Svenson_38":
		if (CheckAttribute(pchar, "questTemp.LongHappy.TerraxShipSink"))
		{
			dialog.text = "Marcus nadó hasta la orilla después de que su barco se hundiera. Bueno, Tyrex no es de esos que se ahogan por una insignificancia así. Ahora está en algún lugar del pueblo. Probablemente sacudiendo las almas de los centinelas que pasaron por alto toda esta inmundicia. Hombre de hierro, no de otra manera.";
			link.l1 = "El hierro se hundiría. Supongo que nuestro barón está hecho de un material que aún es desconocido para la ciencia, ¡jajaja!";
		}
		else
		{
			dialog.text = "Marcus está bien como siempre. Tan pronto como desembarcó, inmediatamente comenzó a sacudir las almas de los centinelas que pasaban por alto toda esta inmundicia. Todavía logra comandar la restauración del orden en la ciudad. Hombre de hierro, no hay otra manera.";
			link.l1 = "El hierro es más blando. Supongo que nuestro barón está hecho de un metal que aún es desconocido para la ciencia, ¡jaja!";
		}
		link.l1.go = "Svenson_39";
		break;

	case "Svenson_39":
		dialog.text = "Eso es todo. Bueno, pudo haber sido peor. Incluso tu boda, Charles, salió... peleando. Lo importante es que ambos están vivos. Un pequeño consejo, en general... ama... ¡y no te atrevas a rendirte en luchar por ello!";
		link.l1 = "Gracias, Jan. Gracias a todos ustedes... Debo admitir, olvidé que comenzamos con una celebración.";
		link.l1.go = "Svenson_40";
		break;

	case "Svenson_40":
		dialog.text = "Entonces, aquí tienes un recordatorio.";
		link.l1 = "Sí, fue una... fiesta salvaje.";
		if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum"))
			link.l1.go = "Svenson_41";
		else
			link.l1.go = "Svenson_43";
		break;

	case "Svenson_41":
		dialog.text = "Oh, sí, seguro que lo fue, espera un minuto. Hay algo: parecía que tenías un tipo indio contigo, ¿verdad?, siempre a tu lado o mirando alrededor como si alguien te estuviera apuntando. Vestido de manera divertida y muy notable en grandes multitudes.";
		link.l1 = "Sí, Tichingitu, desapareció al principio de este lío, estoy empezando a preocuparme para ser honesto. ¿Sabes algo?";
		link.l1.go = "Svenson_42";
		break;

	case "Svenson_42":
		pchar.questTemp.LongHappy.Tichingitu_Wife = "true";
		dialog.text = "Así parece. Nuestro tabernero estaba haciendo ruido de que su sobrina había sido secuestrada, supuestamente antes del ataque. Dice que la vieron con una especie de indio, él la llevaba sobre su hombro a lo largo de la costa al este del pueblo. No noté entre la escoria de Kindman a ningún indio, pero me acordé del tuyo cuando lo oí, así que no dije nada. Deberías ir, buscarlo o algo, antes de que se meta en algún lío. Porque el tabernero amenaza con matarlo si lo encuentra primero. Es un buen hombre, pero por su sobrina desatornillará cualquier cabeza.";
		link.l1 = "Sí, conozco a ese tipo, no te preocupes, y gracias Jan, iré a buscarle de inmediato.";
		link.l1.go = "Svenson_43";
		break;

	case "Svenson_43":
		dialog.text = "Bueno, en general, algo así... Lo siento, soy pésimo con los discursos. Y ahora es aún peor - esta noche nos ha exprimido a todos. Todos deberíamos descansar al menos un día - luego decidiremos cómo proceder.";
		link.l1 = "Tienes razón, Jan. Debería irme, necesito despejar mi mente.";
		link.l1.go = "Svenson_44";
		break;

	case "Svenson_44":
		DialogExit();
		DoQuestReloadToLocation("Pirates_town", "reload", "reload3", "LongHappy_WifeInTown");
		break;

	case "Svenson_45":
		dialog.text = "Te ves bien, Charles. ¿Has dormido bien?";
		link.l1 = "Sí, nos dieron una casa acogedora en las afueras del pueblo. Incluso pensé que había soñado con toda la locura que ocurrió ayer. Y aquí estás Jan, te ves horrible. ¿Qué más ocurrió?";
		link.l1.go = "Svenson_46";
		break;

	case "Svenson_46":
		dialog.text = "Oh no es nada, es solo que aún no he dormido. Sabes... poner en orden la ciudad después de todo lo que pasó aquí es una tarea ardua.";
		link.l1 = "¿Cómo están Dannie y Nathan? ¿Dónde está todo el mundo?";
		link.l1.go = "Svenson_47";
		break;

	case "Svenson_47":
		dialog.text = "Teniendo descanso. No los molestes, Dannie advirtió a todos que hoy se ha llevado pistolas a la cama... Dodson está en el mar, salió a buscar más barcos para asegurar la isla y que esto no vuelva a suceder, otros están enterrando a los difuntos al norte de la isla.";
		link.l1 = "";
		link.l1.go = "Svenson_48";
		break;

	case "Svenson_48":
		if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner") && !CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Free"))
			dialog.text = "Marcus aún no ha sido encontrado, pero podemos manejarlo, no te preocupes. Has hecho tanto por todos nosotros, así que no te preocupes. Tyrax volverá tarde o temprano - lo encontraremos.";
		else
			dialog.text = "Marcus terminó aquí y se marchó rápidamente en el lanchón de alguien hacia La Española. Es necesario resolver algunos asuntos que surgieron tras la muerte de Barbazon. Envió saludos y los mejores deseos para ti y tu esposa.";
		link.l1 = "";
		link.l1.go = "Svenson_49";
		break;

	case "Svenson_49":
		dialog.text = "Pues bien, los Hermanos resistieron este golpe. Pronto, nos levantaremos aún más fuertes de lo que éramos. Kindman y Jackman han estado sacudiendo nuestra unidad durante demasiado tiempo, ahora se han ido y mi corazón siente que haremos que el Caribe tiemble más de una vez. La Edad de Oro está llegando para aquellos a quienes las leyes y los reyes no les son amables, recuerden mis palabras.";
		link.l1 = "Eso sería agradable. No estoy seguro de que pueda soportar más el Viejo Mundo. Nunca pensé, cuando vine aquí, que me enamoraría de la libertad del mar, de esos colores locos de atardeceres y amaneceres, que encontraría a la mejor mujer del mundo y... amigos a quienes confiaría mi vida.";
		link.l1.go = "Svenson_50";
		break;

	case "Svenson_50":
		dialog.text = "Bueno, conoces el rumbo, solo decide. En nuestros hogares siempre eres bienvenido.";
		link.l1 = "Gracias, Jan. Significa mucho para mí.";
		if (CheckAttribute(pchar, "questTemp.Mtraxx"))
		{
			if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
				link.l1.go = "Svenson_51";
			else
				link.l1.go = "Svenson_54";
		}
		else
			link.l1.go = "Svenson_54";
		break;

	case "Svenson_51":
		pchar.questTemp.LongHappy.Baron = "true";
		dialog.text = "Pero primero, queda algo importante. Charles, mientras dormías, nos reunimos y decidimos. Dado que Barbazon está muerto, los Hermanos necesitan un nuevo barón. Como había una clara mayoría de nosotros aquí, y la decisión fue tomada por unanimidad, aquí está. Felicitaciones - eres el nuevo Barón de Le Francois. Pero espera... Entiendo - eres una persona secular, y no tienes tiempo para manejar los asuntos en este hermoso lugar, así que pusimos a una persona de confianza allí, y tú haces lo que quieras. Solo recuerda - tu voz está en los Hermanos ahora.";
		link.l1 = "Jan, yo... estoy sin palabras... Es un gran honor, ni siquiera sé...";
		link.l1.go = "Svenson_52";
		break;

	case "Svenson_52":
		dialog.text = "¡Vamos! Te has demostrado perfectamente entonces con Tyrex, y luego con toda esta historia con el legado de Sharp. Eres la bendición de Dios mismo. Para ti nada cambiará - haz lo planeado, y en tu ausencia, tu hombre se encargará de todos los asuntos.\nHay un tipo prometedor, Jan David, es uno de los Bucaneros. Francés, un tipo honesto, con una mente brillante y sabe cómo usarla, como tú. Pero me llevará algo de tiempo encontrarlo - parece que fue capturado por los españoles, pero esto se puede resolver, no te preocupes. Me aseguraré de que te envíe tu parte tan pronto como se sienta cómodo con el negocio.";
		link.l1 = "No esperaba realmente que todo fuera así. Bueno, ya que ya lo decidiste, que así sea. ¡El Barón Pirata Charles de Maure!";
		link.l1.go = "Svenson_53";
		break;

	case "Svenson_53":
		dialog.text = "¡Viva el barón! Si alguien merece el nombre, deberías ser tú. Llévalo con orgullo, y no olvides - ahora eres uno de los nuestros, no importa lo hermoso que sea el uniforme que lleves, aquí, justo debajo de él late el corazón de un verdadero pirata.";
		link.l1 = "No sé, tal vez estés exagerando... Pero haré todo lo posible para justificar tu confianza.";
		link.l1.go = "Svenson_54";
		break;

	case "Svenson_54":
		dialog.text = "¿Qué vas a hacer ahora? ¿Volver a Europa, volver a tu padre, para presentarle a tu esposa?";
		if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") || CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
		{
			link.l1 = "Sí, pero primero debo despedirme de alguien... Sabes a qué me refiero.";
			link.l1.go = "Svenson_56";
		}
		else
		{
			link.l1 = "Quizás no tan pronto. Una vez más navegaré por el archipiélago, quiero respirar este aire de Libertad por última vez.";
			link.l1.go = "Svenson_55";
		}
		break;

	case "Svenson_55":
		dialog.text = "Tienes un barco, puedes zarpar a casa cuando quieras.";
		link.l1 = "Eso espero. Gracias Jan, gracias a todos vosotros y hasta luego, ¡mi viejo amigo! ¡Saluda a los Halcones y al Shark!";
		link.l1.go = "Svenson_58";
		break;

	case "Svenson_56":
		if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			sTemp = "Se merecen";
		else
			sTemp = "Merece";
		dialog.text = "Sí, es difícil, pero tenemos que hacerlo. ¿Al mar?";
		link.l1 = "No, navegaré a Antigua. " + sTemp + " descansar en paz en un lugar que se convirtió en nuestro hogar, por un tiempo.";
		link.l1.go = "Svenson_57";
		break;

	case "Svenson_57":
		dialog.text = "Di algunas palabras amables de mi parte también. Y no te preocupes, podemos manejarlo por nuestra cuenta desde ahora. Todo va a estar bien.";
		link.l1 = "Gracias Jan. ¡Hasta pronto, mi viejo amigo! ¡Dale mis saludos a los Halcones y al Shark!... Bueno, Antigua será.";
		link.l1.go = "Svenson_58";
		break;

	case "Svenson_58":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_IslaMarryComplete", 10.0);
		break;

	case "Svenson_":
		dialog.text = "";
		link.l1 = "";
		link.l1.go = "Svenson_";
		break;

	// Глэдис
	case "Gladis":
		dialog.text = "Joven, hoy has crecido aún más a mis ojos. Has hecho tanto por Helen, que ninguna palabra de gratitud será suficiente. Solo espero que sigas cuidando de ella. Si su padre estuviera vivo y viera esto, cuán feliz habría estado... oh, lo siento.";
		link.l1 = "Está bien, Gladys. Cruzaste el archipiélago para apoyar a Helen en este día. Ambos apreciamos mucho tu visita con Jan, gracias.";
		link.l1.go = "Guests_block";
		break;

	// Форже - патер Мэри
	case "forge":
		dialog.text = "Monsieur de Maure,  me disculpo por la familiaridad, pero lo diré de esta manera, ¡Charles, amigo mío, estoy sinceramente feliz por ti! Si puedo hacer algo por ti o tu prometida, ¡solo dilo!";
		link.l1 = "Le agradezco, Barón, estoy tan feliz, y los viñedos que mi padre quería como dote, creo que puedo redimirme - afortunadamente, mi situación financiera durante mi estancia en el Nuevo Mundo ha mejorado considerablemente.";
		link.l1.go = "forge_1";
		break;

	case "forge_1":
		dialog.text = "Sí, supongo que puedes permitirte casi cualquier cosa que desees, Charles. Discúlpame, pero haré mi contribución como el padre representante - Hoy, voy a escribir a mi buen amigo el Ministro de Finanzas. A tu elegida se le otorgará el título de nobleza, y, creo, encontraremos alguna buena propiedad para ella, digamos en Gascuña, entre aquellas que fueron confiscadas por deudas, y se la asignaremos retroactivamente. ¡Así que nadie se atreverá a decir que el Chevalier de Monper encontró una esposa de baja posición!";
		link.l1 = "No creo que me preocupen tales chismes, pero gracias, Barón. Aún así, no deberías";
		link.l1.go = "forge_2";
		break;

	case "forge_2":
		dialog.text = "¡Más de lo que debería! Ahora ve, Charles, comparte tu atención con el resto de los invitados. Y una vez más, ¡acepta mis más sinceras felicitaciones!";
		link.l1 = "Mi esposa y yo te agradecemos. Nos vemos, Barón.";
		link.l1.go = "Guests_block";
		break;

	// Форже - патер ГГ
	case "forge_3":
		dialog.text = "Monsieur de Maure, me disculpo por la familiaridad, pero lo diré de esta manera, ¡Charles, amigo mío, me alegro sinceramente por ti! Si puedo hacer algo por ti o por tu novia, ¡solo dilo!";
		link.l1 = "Gracias, Barón, pero ya ha hecho mucho por mí. Nos basta con que haya respondido a la invitación.";
		link.l1.go = "forge_4";
		break;

	case "forge_4":
		dialog.text = "¡Cómo podría no haber respondido, Charles! Pero escucha, quiero presentarte a ti y a tu hermosa novia un regalo digno, pero no puedo pensar en nada que no puedas conseguir por ti mismo con dinero o una espada. Por lo tanto, escribiré a mi amigo el Ministro de Finanzas en París, y para cuando llegues a Europa, te estarán esperando para firmar el rescripto real de la exaltación del nombre de de Monper en el título de Barones de Monper. No, ni una palabra, esto es lo menos que puedo hacer por ti.";
		link.l1 = "No sé ni qué decir, Barón... Padre estará tan feliz. Sinceramente, gracias.";
		link.l1.go = "Guests_block";
		break;

	// Форже гость
	case "forge_5":
		dialog.text = "¡Charles, por favor, acepta mis sinceras felicitaciones! ¡Tu elegida es simplemente un milagro! Creo que hoy la moda colonial ha recibido un fuerte... empujón hacia una nueva dirección. ¡Tu originalidad siempre me ha fascinado! ¡Que tú y tu hermosa mitad viváis felices para siempre!";
		link.l1 = "Gracias, Barón. Nos ha honrado con su visita.";
		link.l1.go = "forge_6";
		break;

	case "forge_6":
		dialog.text = "¿Cómo podría alejarme, amigo mío? Hemos pasado por mucho juntos y estoy orgulloso de llamarte mi amigo, Charles. Recuerda: mis puertas siempre están abiertas para ti, pase lo que pase.";
		link.l1 = "Como las puertas de la familia de Monper siempre estarán abiertas para usted, Barón.";
		link.l1.go = "Guests_block";
		break;

	// Пуанси патер Мэри
	case "puancie":
		dialog.text = "Charles, mi amigo, este es un día muy importante, y me alegra que me hayas invitado a compartirlo contigo. Tú y yo hemos recorrido un camino largo y difícil, y convertirme en el padre representativo de la señorita... por favor, perdóname - Madame de Maure, es un honor para mí, créeme. ¡De todo corazón te deseo felicidad!\nY por favor, házmelo saber cuando vayas a Europa - yo, como el padre representativo de tu elegida, enviaré a tu padre todos los regalos de boda necesarios. Créeme, nadie dirá que la novia del caballero de Monper es pobre o indigna!";
		link.l1 = "Si me permite preguntar, Chevalier, a un par de millas al norte de la finca de Monper, hay buenos viñedos, pertenecen a la familia La Brigne y yo...";
		link.l1.go = "puancie_1";
		break;

	case "puancie_1":
		dialog.text = "¡Ni una palabra más, mi amigo, ni una palabra! Inmediatamente escribiré a mi representante autorizado en Lyon - para tu llegada, estos viñedos serán entregados a tu elegido.";
		link.l1 = "Gracias, Chevalier. Tienes razón - nuestra... amistad, pasó por... mucho. Pero, estoy realmente contento de que compartieras este día con nosotros. ¡Nos vemos y gracias de nuevo!";
		link.l1.go = "Guests_block";
		break;

	// Пуанси патер ГГ
	case "puancie_2":
		dialog.text = "Charles, mi amigo, este es un día muy importante, y me alegra que me hayas invitado a compartirlo contigo. Hemos recorrido un camino largo y difícil, y testificar hoy en tu boda es un honor para mí. ¡Con todo mi corazón te deseo felicidad! Y avísame cuando vayas a Europa - enviaré a tu padre dignos regalos de boda.";
		link.l1 = "No hay necesidad de esto, Chevalier. Gracias por responder a mi invitación.";
		link.l1.go = "puancie_3";
		break;

	case "puancie_3":
		Log_Info("Tienes las gemas");
		PlaySound("interface\important_item.wav");
		TakeNItems(pchar, "jewelry2", 50);
		TakeNItems(pchar, "jewelry3", 50);
		TakeNItems(pchar, "jewelry4", 50);
		dialog.text = "¡Como dije, es un honor para mí! Pero espera, mi amigo, me gustaría presentarte algo en esta ocasión - estoy seguro de que esto complacerá tanto a ti como a tu elegida. Hermosas piedras de nuestras minas en Nueva Guayana - escoge un marco decente y madame de Maure brillará incluso en la recepción real. Si la convences de llevar un vestido, por supuesto...";
		link.l1 = "Oh, realmente no deberías, caballero. Gracias de nuevo.";
		link.l1.go = "Guests_block";
		break;

	// Пуанси гость
	case "puancie_4":
		dialog.text = "¡Charles, mi amigo, permíteme felicitarte! Hemos recorrido un camino largo y difícil, y sinceramente me alegra estar aquí hoy. Nuestro Señor es testigo: ¡te mereces tu felicidad! Cuídala y protégela, ¡deseándote muchos años felices por venir!";
		link.l1 = "Gracias, Chevalier, mi esposa y yo estamos muy agradecidos.";
		link.l1.go = "Guests_block";
		break;

	// Фадей патер
	case "fadey":
		dialog.text = "Charles, ¡qué celebración, y cuántas personas importantes! Permíteme desearte de todo corazón felicidad y buena salud, ¡y hijos para alegría! Como decimos - '¡gor'ko'!'";
		link.l1 = "Gracias, Fadey, me honraste al aceptar venir.";
		link.l1.go = "fadey_1";
		break;

	case "fadey_1":
		dialog.text = "Pero, no entiendo del todo por qué hay tanta gente como si no estuviéramos concluyendo un matrimonio, sino un gran acuerdo comercial, y todavía no hay suficientes cervezas y vodka para mi gusto aquí... ¡jaja! Bueno, estoy bromeando, Charles, ¿por qué te has puesto completamente pálido? ¡Dame un abrazo, capitán casado!";
		link.l1 = "¡Vaya... Fadey, eres fuerte como un oso!";
		if (CheckAttribute(pchar, "questTemp.Persian"))
		{
			if (pchar.questTemp.Persian == "time" || pchar.questTemp.Persian == "end")
				link.l1.go = "fadey_2";
			else
				link.l1.go = "Guests_block";
		}
		else
			link.l1.go = "Guests_block";
		break;

	case "fadey_2":
		GiveItem2Character(pchar, "blade_22");
		GiveItem2Character(pchar, "blade_23");
		GiveItem2Character(pchar, "blade_24");
		Log_Info("Tienes tres sables persas");
		PlaySound("interface\important_item.wav");
		dialog.text = "Espera, Charles, no te vayas - no es digno que el invitado venga a la boda sin regalos. Aquí, tómalo. Sé que trataste de encontrar todas estas espadas, y algunas, obviamente, te gustaron. Así que acéptalas - cuélgalas en una finca familiar y recuerda a Fadey Moskovit con una buena palabra.";
		link.l1 = "¡Este es un verdadero regalo! Gracias, Fadey. Estas son realmente armas maravillosas, y ocuparán su merecido lugar en la hacienda de Monper, ¡lo prometo!";
		link.l1.go = "Guests_block";
		break;

	// Фадей гость
	case "fadey_3":
		dialog.text = "¡Charles, qué celebración, y cuántas personas importantes! ¡Permíteme desearte de todo corazón felicidad y buena salud, y niños para alegría! Como decimos - '¡gor'ko'! ¡Dame un abrazo, capitán casado!";
		link.l1 = "¡Vaya... Fadey, eres fuerte como un oso!";
		link.l1.go = "Guests_block";
		break;

	// Проспер Трубаль
	case "Prosper":
		dialog.text = "¡Charles, no podía perdérmelo, te felicito a ti y a tu elegido con todo mi corazón! ¡Sed felices! Sabes, hace un par de meses casé a mi hija, con una buena persona y enamorada, pero sinceramente, me molestó que no fueras tú... Bueno, está bien... de qué estoy hablando, ¡felicidades! ¡Que viváis felices para siempre!";
		link.l1 = "Gracias, Prosper, me alegra que hayas venido.";
		link.l1.go = "Guests_block";
		break;

	// Тичингиту
	case "Tichingitu":
		dialog.text = "¡Felicidades, capitán! Un rito extraño, pero hermoso - a Tichingitu le gustó. Aunque, el capitán debería simplemente secuestrar a su squaw, y enviar un rescate a sus familiares.";
		if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			link.l1 = "Bueno, de alguna manera lo hice, y es solo una formalidad. ¡Gracias, mi amigo!";
		else
			link.l1 = "Bueno, de alguna manera lo hice, y es solo una formalidad. ¡Gracias, mi amigo! Tú y yo hablaremos más en Sharptown - habrá mucha menos oficialidad y más diversión sincera, ¡lo prometo!";
		link.l1.go = "Tichingitu_1";
		break;

	case "Tichingitu_1":
		dialog.text = "¿Aguardiente otra vez? Tichingitu no puede decir que le guste. Tal vez, un abordaje de celebración sea mejor, o al menos bailar alrededor de una hoguera.";
		if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			link.l1 = "Espero que no termine en danzas alrededor de la hoguera, y preferiría evitar abordajes. Bien, ten paciencia, ya falta poco, y luego nos dirigiremos a la taberna.";
		else
			link.l1 = "Me temo que falta mucho tiempo para que termine el baile alrededor de la hoguera, y preferiría evitar los abordajes. Bien, ten paciencia, ya queda poco, y luego zarparemos hacia Sharptown.";
		link.l1.go = "Guests_block";
		break;

	case "Tichingitu_2":
		pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count) + 1;
		dialog.text = "¡Capitán, enhorabuena otra vez! A Tichingitu le gusta esta celebración más que la anterior. El capitán sabe cómo elegir amigos: aquí hay más sinceridad, menos hipocresía y pelo falso.";
		link.l1 = "¡Gracias, mi amigo! Solo no bebas el agua de fuego, es muy fuerte aquí.";
		link.l1.go = "Tichingitu_4";
		link.l2 = "¡Gracias, mi amigo! ¿Tomamos una copa? Sé que no te gusta, ¡pero hoy deberías probarla!";
		link.l2.go = "Tichingitu_3";
		break;

	case "Tichingitu_3":
		pchar.questTemp.LongHappy.Tichingitu_Rum = "true";
		dialog.text = "Tichingitu no gusta del agua de fuego, pero si el capitán insiste, hoy es posible hacerlo. ¡A tu felicidad, y a tu squaw!";
		link.l1 = "¡Y a ti, Tichingitu! ¡A tu amistad y lealtad!";
		link.l1.go = "Tichingitu_4";
		break;

	case "Tichingitu_4":
		DialogExit();
		npchar.dialog.currentnode = "Tichingitu_4_1";
		if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
		{
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_57";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		else
		{
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed))
				LongHappy_IslaTesoroToVine();
		}
		break;

	case "Tichingitu_4_1":
		dialog.text = "Buena fiesta, capitán.";
		link.l1 = "Me alegra que estés satisfecho.";
		link.l1.go = "Tichingitu_4";
		break;

	case "Tichingitu_5":
		dialog.text = "Capitán, ¿salió a mirar las estrellas? La noche promete ser muy hermosa. A Tichingitu le encanta la noche sobre el mar. Es muy apacible.";
		link.l1 = "¡Me alegra ver que todavía estás en pie, amigo mío! Nathaniel y yo necesitamos tu ayuda: los muchachos de la taberna se han quedado sin bebidas, necesitamos traer unas cajas de bebidas del almacén bajo el astillero.";
		link.l1.go = "Tichingitu_6";
		break;

	case "Tichingitu_6":
		dialog.text = "Lidere, capitán. Tichingitu te sigue, como siempre.";
		link.l1 = "¡De acuerdo, vamos!";
		link.l1.go = "Tichingitu_7";
		break;

	case "Tichingitu_7":
		DialogExit();
		chrDisableReloadToLocation = false;
		LAi_SetActorType(npchar);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		break;

	case "Tichingitu_8":
		dialog.text = "Capitán, hay gente, y están armados, Tichingitu oye el ruido de sus armas y se están volviendo más ruidosos a cada segundo. No me gusta. Vamos a escondernos.";
		link.l1 = "Vamos, compañero - esto es Sharptown, aquí incluso al retrete la gente va armada con pistolas. Oye Nathan... ¡bueno, mierda! Ahí va una botella menos. ¡Si sigue así, romperás todas las botellas! ¡Ponte de pie, maldito seas! ¡Ja-Ja!";
		link.l1.go = "Tichingitu_9";
		break;

	case "Tichingitu_9":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		LongHappy_SetBandosInDungeon();
		break;

	case "Tichingitu_10":
		dialog.text = "Capitán... tú... La cabeza de Tichingitu está destrozada como un mástil en la tormenta. ¿Qué sucedió?";
		link.l1 = "¡Quería preguntarte lo mismo! ¿Dónde has estado todo este tiempo?!";
		link.l1.go = "Tichingitu_11";
		break;

	case "Tichingitu_11":
		dialog.text = "Tichingitu se despertó hace una hora por los gritos de esta chica. Corría por la playa casi desnuda y gritaba algo sobre los secuestradores y salvajes... Pero no hay nadie aquí excepto nosotros. ¿Tienes agua? ¿No la ardiente otra vez, Tichingitu la odia ahora?";
		link.l1 = "Había un frasco en algún lugar, si no lo perdí en una batalla... aquí tienes. ¿Cómo lograste hacer esto? Su tío, un tabernero, está buscando a un indio que ha secuestrado a su sobrina, y amenaza con arrancarle la cabeza vacía emplumada. ¿De quién crees que está hablando?";
		link.l1.go = "Tichingitu_12";
		break;

	case "Tichingitu_12":
		dialog.text = "Tichingitu recordó. Ella estaba ayudando al Forest Devil en la taberna con la boda. Bebimos agua de fuego contigo, y Tichingitu quería más. Y luego, esta squaw... ella era tan linda y... Capitán, ¡creo que recordé! Tichingitu quería casarse con ella... Quería construir una canoa y llevársela... ¡Espíritus de misericordia! Muy mala gente vino con agua de fuego. ¡Quizás, los demonios o espíritus malignos! Tichingitu nunca más...";
		link.l1 = "¿Llevarla lejos? ¿Construir una canoa? ¡Ahah, eres un romántico, mi amigo... Ja-ja... ja-ja-ja-ja-ja-ja oh, no puedo parar... no puedo parar de reír!";
		link.l1.go = "Tichingitu_13";
		break;

	case "Tichingitu_13":
		dialog.text = "Capitán, Tichingitu ha robado a la india, sí... pero, ¿podemos, bueno... no casarnos ahora? Ella es... ruidosa, como un pájaro papagayo, y... no tan hermosa.";
		link.l1 = "Sí, amigo mío, las mujeres, divirtiéndose toda la noche, son una vista miserable por la mañana. No te preocupes, héroe-amante, se nos ocurrirá algo. Vamos, tenemos que volver a Sharptown, te perdiste tu abordaje de vacaciones...";
		link.l1.go = "Tichingitu_14";
		break;

	case "Tichingitu_14":
		dialog.text = "¿Un abordaje? El capitán ha mencionado una batalla antes. Los pensamientos todavía no obedecen a Tichingitu. ¿Qué pasó en el pueblo?";
		link.l1 = "Una verdadera batalla en tierra y mar. Los cañones dispararon toda la noche, supongo, probablemente se escucharon incluso en San José. Sin embargo, tú estabas ocupado con otra 'batalla', todo está bien, puedo entenderlo... Vamos, te contaré todo en el camino.";
		link.l1.go = "Tichingitu_15";
		break;

	case "Tichingitu_15":
		DialogExit();
		chrDisableReloadToLocation = false;
		LAi_SetActorType(npchar);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		sld = characterFromId("LH_waitress");
		LAi_SetActorType(sld);
		LAi_ActorFollowEverywhere(sld, "", -1);
		pchar.quest.longhappy_shoregirl1.win_condition.l1 = "location";
		pchar.quest.longhappy_shoregirl1.win_condition.l1.location = "Pirates_town";
		pchar.quest.longhappy_shoregirl1.function = "LongHappy_ReturnShoreGirl";
		break;

	case "Tichingitu_16":
		dialog.text = "Gracias, capitán... Tichingitu nunca...";
		link.l1 = "Sí, 'el corcel de las lejanas llanuras', definitivamente no deberías beber más. Ve a dormir. Yo también ya me caigo de cansancio.";
		link.l1.go = "Tichingitu_17";
		break;

	case "Tichingitu_17":
		DialogExit();
		npchar.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
		LAi_SetImmortal(npchar, false);
		npchar.OfficerWantToGo.DontGo = true;
		npchar.CompanionDisable = true;
		npchar.loyality = MAX_LOYALITY;
		AddPassenger(pchar, npchar, false);
		SetCharacterRemovable(npchar, true);
		LAi_SetOfficerType(npchar);
		npchar.Payment = true;
		npchar.DontClearDead = true;
		npchar.dialog.currentnode = "Tichingitu_officer";
		LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			sld = characterFromId("Helena");
		else
			sld = characterFromId("Mary");
		sld.dialog.currentnode = "LongHappy_55";
		ChangeCharacterAddressGroup(sld, "Pirates_town", "goto", "goto2");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

	case "Tichingitu_18":
		dialog.text = "¡Capitán, felicidades de nuevo! A Tichingitu le gusta esta celebración más que la anterior. El capitán sabe elegir amigos: aquí hay más sinceridad, menos hipocresía y pelo falso.";
		link.l1 = "Y mucho más agua de fuego. Por cierto, ¿beberás conmigo? Sé que no te gusta, ¡pero tenemos una ocasión inusual!";
		link.l1.go = "Tichingitu_19";
		break;

	case "Tichingitu_19":
		dialog.text = "Tichingitu no le gusta el agua ardiente, pero si el capitán insiste, hoy es posible hacerlo. ¡Por tu felicidad, y tu squaw! Que caminéis el mismo sendero, y que el sol y la luna siempre brillen sobre él.";
		link.l1 = "Gracias, mi amigo. ¡Salud a ti, Tichingitu! ¡A nuestra amistad!";
		link.l1.go = "Tichingitu_4";
		break;

	// губернаторы
	// Сен Пьер
	case "FortFrance_Mayor":
		if (pchar.questTemp.GoldenGirl == "end")
		{
			dialog.text = "Gran ... celebración, estoy muy feliz por ti, Charles. Aunque, todavía no te entiendo... Tener una rosa invaluable en tus manos y cambiarla por... una flor silvestre. Pero el corazón quiere lo que quiere... Sé feliz mi amigo. ¡Que vivas feliz para siempre!";
			link.l1 = "En la flor que sostienes, lo más hermoso es tu sentimiento hacia ella. Sin él, es solo un bulto de carne que se desvanece. Me alegra que hayas venido, Su Gracia.";
			link.l1.go = "FortFrance_Mayor_1";
		}
		else
		{
			dialog.text = "¡Un día maravilloso, mi amigo, y una ocasión maravillosa! ¡Acepta mis sinceras felicitaciones! Me casé tres veces, y cada vez temblaba como la primera, ah, juventud...";
			link.l1 = "Monsieur, aún estás lejos de la vejez, no te desanimes. ¡Gracias por venir, Jacques!";
			link.l1.go = "Guests_block";
		}
		break;

	case "FortFrance_Mayor_1":
		dialog.text = "Espera, Charles. Me malinterpretaste, ¡estoy sinceramente feliz con todo mi corazón! Y sí... aquí, tómalo. Nuestro común... Amigo, realmente pidió que lo recibieras exactamente hoy.";
		link.l1 = "Sospecho   que sé de   quién es. Gracias y hasta pronto.";
		link.l1.go = "Guests_block";
		if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
		{
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
					AddQuestRecordInfo("Letter_Marquesa", "2-1");
				else
					AddQuestRecordInfo("Letter_Marquesa", "1-1");
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
					AddQuestRecordInfo("Letter_Marquesa", "4-1");
				else
					AddQuestRecordInfo("Letter_Marquesa", "3-1");
			}
		}
		else
		{
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
					AddQuestRecordInfo("Letter_Marquesa", "2");
				else
					AddQuestRecordInfo("Letter_Marquesa", "1");
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
					AddQuestRecordInfo("Letter_Marquesa", "4");
				else
					AddQuestRecordInfo("Letter_Marquesa", "3");
			}
		}
		break;

	// Бас Тер
	case "BasTer_Mayor":
		dialog.text = "Un encantador liturgia, ¿verdad, Charles? ¡Estoy sinceramente feliz por ti! De mi parte personalmente y de todos los ciudadanos de Basse-Terre, te digo nuestras felicitaciones a ti y a tu... encantadora esposa. ¡Sois una pareja maravillosa! ¡Que viváis felices para siempre!";
		link.l1 = "Gracias, Su Gracia. Me alegra que le haya gustado.";
		link.l1.go = "Guests_block";
		break;

	// Порт Принс
	case "PortPax_Mayor":
		dialog.text = "¡Qué servicio tan maravilloso, monsieur de Maure, simplemente maravilloso! Y la novia es tan... original en este atuendo. En nombre de todos los residentes de nuestra ciudad, ¡aceptad mis más sinceras felicitaciones! ¡Os deseo muchos años felices por venir!";
		link.l1 = "Gracias, Su Gracia.";
		link.l1.go = "Guests_block";
		break;

	// Тортуга
	case "Tortuga_Mayor":
		dialog.text = "Tan lindos - tú y tu novia, monsieur de Maure, ¡se veían tan inusuales! Sin embargo, eres un hombre inusual. Te deseo una larga y feliz vida familiar. ¡Que viváis felices para siempre!";
		link.l1 = "Estoy muy agradecido a usted, Su Gracia.";
		link.l1.go = "Guests_block";
		break;

	// д'Ойли
	case "PortRoyal_Mayor":
		PlaySound("Voice\Spanish\LE\Doily\Edvard_Doily_03.wav");
		dialog.text = "¡Mis más sinceras felicitaciones a usted y a su encantadora esposa! ¡De parte de todos los ciudadanos de las colonias británicas!";
		link.l1 = "¡Gracias por la visita y por las amables palabras, coronel!";
		link.l1.go = "Guests_block";
		break;

	// Исла Тесоро
	// Тиракс
	case "Terrax":
		if (CheckAttribute(pchar, "questTemp.Mtraxx"))
		{
			if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
			{
				dialog.text = "¿Y qué hace este petimetre casado en mi playa pirata, eh?! Dime, monsieur, ¿qué hiciste con mi viejo amigo - el rudo Pirata Charlie Prince?";
				link.l1 = "Charlie Prince está muerto, lo recuerdas, Marcus... ¡Ja-ja-ja ven aquí, diablo del mar! ¡Me alegra verte! ¿Cómo están aquí, muchachos, todos se han reunido?";
				link.l1.go = "Terrax_1_1";
			}
			else // 28-03-20
			{
				dialog.text = "¿Y qué hace este petimetre casado en mi playa pirata, eh?! Dime, monsieur, ¿qué hiciste con mi viejo amigo - el rudo capitán Charles de Maure?";
				link.l1 = "¡Ahoy, Marcus, me alegra verte también! ¿Cómo os va por aquí, se han reunido todos?";
				link.l1.go = "Terrax_1";
			}
		}
		else
		{
			dialog.text = "¿Y qué hace este petimetre casado en mi playa pirata, eh? ¡Dime, monsieur, qué hiciste con mi viejo amigo, el duro Capitán Charles de Maure?";
			link.l1 = "¡Ahoy, Marcus, me alegra verte también! ¿Cómo lo están pasando aquí, se han reunido todos?";
			link.l1.go = "Terrax_1";
		}
		break;

	case "Terrax_1":
		dialog.text = "Sí, Forest Devil llegó justo ayer e inmediatamente comenzó a dar órdenes - así que los invitados están aquí y todo está listo para la celebración. Tu barco fue visto cerca de los arrecifes, y los muchachos no pudieron resistir - se lanzaron a la taberna y, lo más probable, ya han abierto ese barril de Hawk. ¡Apúrate, tal vez aún tengamos la oportunidad de beber un vaso - Nathaniel se jactó de que era algún tipo de ron especial!";
		link.l1 = "¡Ahora así es como lo hacemos, del barco directo a la fiesta! Esperaré a mi mejor mitad y estamos justo detrás de ti, ¡Marcus!";
		link.l1.go = "Terrax_2";
		break;

	case "Terrax_1_1":
		dialog.text = "Sí, Forest Devil llegó justo ayer e inmediatamente comenzó a dar órdenes - así que los invitados están aquí y todo está listo para la celebración. Tu barco fue visto cerca de los arrecifes, y los muchachos no pudieron resistirse - se lanzaron a la taberna y, lo más probable, ya han abierto ese barril de Hawk. ¡Apúrate, tal vez aún tengamos la oportunidad de beber un vaso - Nathaniel presumió que era algún tipo de ron especial!";
		link.l1 = "¡Ahora así lo hacemos - desde el barco directamente a la fiesta! Esperaré a mi mejor mitad y estamos justo detrás de ti, ¡Marcus!";
		link.l1.go = "Terrax_2";
		break;

	case "Terrax_2":
		DialogExit();
		DoQuestReloadToLocation("Pirates_tavern", "reload", "reload1", "LongHappy_IslaTesoroTavern");
		break;

	case "Terrax_3":
		pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count) + 1;
		dialog.text = "Casada con Charles de Maure - todavía no puedo acostumbrarme... Primero Svenson, ahora tú, ¿y luego qué? ¿El pastor Marlow, o Jacques el Bondadoso?";
		link.l1 = "Te olvidaste de los Hawks. ¿Y tú, Marcus? ¿No estás cansado de ser un lobo de mar solitario?";
		link.l1.go = "Terrax_4";
		break;

	case "Terrax_4":
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
		{
			dialog.text = "Dannie y Nathan son un caso de larga data - ya me he acostumbrado a esto, ¡pero me sorprendiste, no hay nada que decir! Sin embargo, la pupila de Forest Devil es hermosa - no hay nada que decir, siempre lista para usar tanto la palabra como la pistola, y puede manejar cualquier tormenta. Es poco probable que pudieras encontrar una mujer más digna. ¡Eres un afortunado, capitán - cuida de ella!";
		}
		else
		{
			dialog.text = "Dannie y Nathan son un caso de larga data - ya me he reconciliado con esto, ¡pero me sorprendiste, no hay nada que decir! Aunque, como escuché, tu Mary sabe mucho sobre espadas y claramente sabe cómo usarlas, ¡mis respetos! Una verdadera compañera de guerra. Te contaré un secreto, por el bien de tal dama, yo mismo reconsideraría mis convicciones de soltero. Eres un afortunado, capitán, ¡cuídala bien!";
		}
		link.l1 = "Lo sé, ella es un milagro y estoy de nuevo en el séptimo cielo de felicidad, ¡igual que aquellos días cuando nos conocimos por primera vez!";
		link.l1.go = "Terrax_5";
		break;

	case "Terrax_5":
		dialog.text = "¡Pues bien, un brindis!... ¡Por el amor!... ¡Pero no por el que nos lleva al umbral y al horizonte!... ¡Sino por el que nos espera en este umbral! ¡Por el amor, el que nos hace volver a él, incluso desde el fin del mundo y desde las montañas doradas! ¡Vive con él y sé feliz!";
		link.l1 = "¡Gran brindis, Marcus, gracias!";
		link.l1.go = "Terrax_6";
		break;

	case "Terrax_6_1":
		dialog.text = "¡Salud, por tu boda, camarada!";
		link.l1 = "Gracias, Marcus...";
		link.l1.go = "Terrax_6";
		break;

	case "Terrax_6":
		DialogExit();
		npchar.dialog.currentnode = "Terrax_6_1";
		if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed))
			LongHappy_IslaTesoroToVine();
		break;

	case "Terrax_7":
		dialog.text = "¿Jacques? Esto definitivamente no es bueno...";
		link.l1 = "Marcus, ¿crees que...?";
		link.l1.go = "Terrax_8";
		break;

	case "Terrax_8":
		dialog.text = "¡No hay tiempo! ¡Están detrás de las puertas! ¡Todos, a las armas!";
		link.l1 = "¡Allá vamos!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("LongHappy_TavernFight");
		break;

	case "Terrax_9":
		dialog.text = "¡No recuerdo la última vez que me divertí tanto en una fiesta! ¡Todavía no se ha acabado! ¿Oyes eso? ¡Alguien está disparando afuera! ¡Ensuciemos las calles con su sangre!";
		link.l1 = "¡Espera! ¿Quién diablos son ellos!? ¿Y qué demonios quieren?!";
		link.l1.go = "Terrax_10";
		break;

	case "Terrax_10":
		DialogExit();
		sld = characterFromId("Svenson");
		sld.dialog.currentnode = "Svenson_20";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

	// Натаниэль Хоук
	case "Nathaniel":
		pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count) + 1;
		dialog.text = "¡Capitán casado de Maure, pocas veces he encontrado razones más sinceras para un brindis! Levantad la copa - esto no es una bebida común de repollo. ¡Está infusionada con té negro de las Indias Orientales y sazonada con auténticas especias persas!";
		link.l1 = "Y he estado pensando por qué me quema la garganta como si hubiera bebido plomo fundido. Bueno, Nathan, salud...";
		link.l1.go = "Nathaniel_1";
		break;

	case "Nathaniel_1":
		dialog.text = "¡Esperad, primero un brindis! ¡Eh, caballeros, levantad vuestras jarras! Hoy, nuestro amigo y socio Charles de Maure está entrando en el camino de la vida familiar. Aceptad de nosotros las más profundas condole... ¡oh, Dannie por favor, baja el arma! ¡Felicidades, por supuesto! Ahora, sois las velas del mismo barco, así que llevadla a través de cualquier tormenta hasta las costas más fértiles!";
		link.l1 = "Gracias, Nathan, sinceramente. Tú y Danielle sois un ejemplo a seguir.";
		link.l1.go = "Nathaniel_2";
		break;

	case "Nathaniel_2":
		dialog.text = "Es agradable escuchar eso. Mi esposa y yo quizás no seamos la mejor pareja del mundo, pero somos felices juntos, y has hecho tanto por nosotros que, si me preguntas, eres parte de mi familia, y estaré aquí para ti siempre que me necesites. ¡Sé feliz, y por favor, tómate un trago!";
		link.l1 = "¡Entonces, bebamos! Oh... este ron debería tener su lugar en el arsenal de la Santa Inquisición. ¡Maldita sea! Quema todo el camino... ¡aghhh! ¡Uf!... ¡Me gusta!";
		link.l1.go = "Nathaniel_3";
		break;

	case "Nathaniel_3":
		DialogExit();
		npchar.dialog.currentnode = "Nathaniel_3_1";
		if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed))
			LongHappy_IslaTesoroToVine();
		break;

	case "Nathaniel_3_1":
		dialog.text = "¡Te pareces tanto a mí y a Dannie de hace veinte años!";
		link.l1 = "¡Una copa más, Nathan!";
		link.l1.go = "Nathaniel_3";
		break;

	case "Nathaniel_4":
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			sld = characterFromId("Helena");
		else
			sld = characterFromId("Mary");
		dialog.text = "¿Qué!? ¿Te envió Jan a las bodegas a traer vino? Demos un paseo, te ayudaré un poco, y el aire fresco será útil.";
		link.l1 = "¿Pero dónde están Dannie y " + sld.name + "¿Jan me dijo que se habían ido a tener una charla?";
		link.l1.go = "Nathaniel_5";
		break;

	case "Nathaniel_5":
		dialog.text = "Sí, Dannie sabe que la presencia de incluso la mejor compañera de armas aún no dará a los caballeros un momento afortunado para relajarse al máximo. Así que escucharon todos los cumplidos que recibieron y fueron a la residencia para dejar que los chicos se diviertan.";
		link.l1 = "¡Pues bien, movámonos! Logré beber un par de jarras, pero maldita sea, ¡ahora es realmente hora de emborracharse como es debido!";
		link.l1.go = "Nathaniel_6";
		break;

	case "Nathaniel_6":
		DialogExit();
		LAi_ActorFollowEverywhere(npchar, "", -1);
		chrDisableReloadToLocation = false; // открыть локацию
		bDisableFastReload = true;			// закрыть переход
		pchar.quest.longhappy_isla_vine.win_condition.l1 = "location";
		pchar.quest.longhappy_isla_vine.win_condition.l1.location = "Pirates_town";
		pchar.quest.longhappy_isla_vine.function = "LongHappy_IslaTesoroToAlexus";
		break;

	case "Nathaniel_7":
		PlaySound("ambient\jail\jail_door2.wav");
		dialog.text = "Entonces, aquí está el cofre. Tomamos tanto como podamos cargar y volvemos, antes de que ese viejo gruñón nos encierre aquí.";
		link.l1 = "Exageras, Nathan. No es tan malo... Espera, ¿oíste eso?";
		link.l1.go = "Nathaniel_8";
		break;

	case "Nathaniel_8":
		PlaySound("ambient\jail\jail_door2.wav");
		dialog.text = "Jan probablemente encontró más tipos y los envió a ayudarnos. ¡Maldición!";
		link.l1 = "Vamos, las botellas se rompen por fortuna. Toma una más y vámonos.";
		link.l1.go = "Nathaniel_9";
		break;

	case "Nathaniel_9":
		DialogExit();
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true); // запретить драться
		LAi_SetActorType(npchar);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		if (!CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum") && GetCharacterIndex("Tichingitu") != -1)
		{
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_8";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		else
			LongHappy_SetBandosInDungeon();
		break;

	case "Nathaniel_10":
		dialog.text = "¿Qué diablos está pasando, quiénes son esos bastardos? ¿Entiendes algo, Charles?";
		link.l1 = "No lo sé, Nathan, pero uno de ellos ha ido a buscar ayuda, y parece que oigo más pasos. ¡Tenemos que volver a la taberna!";
		link.l1.go = "Nathaniel_11";
		break;

	case "Nathaniel_11":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		chrDisableReloadToLocation = false;
		pchar.quest.longhappy_totavern.win_condition.l1 = "location";
		pchar.quest.longhappy_totavern.win_condition.l1.location = "Pirates_tavern";
		pchar.quest.longhappy_totavern.function = "LongHappy_TavernAlarm";
		break;

	case "Nathaniel_12":
		LongHappy_TownRepose();
		dialog.text = "Derrotamos a esos bastardos, pero los cañones retumban desde el mar, ¿lo oyes? Solo tenemos dos tripulaciones listas para la batalla, en la fragata de Marcus y la corbeta de Jan. Yo, Dannie y otros hemos desembarcado a nuestros hombres - después de todo es una boda - así que el Centurión está fuera. ¿Qué hay de tu barco? ¡Tenemos que decidir qué hacer y rápido!";
		link.l1 = "He desembarcado a la mitad de la tripulación, espero que el resto esté sobrio. Pero primero, tengo que encontrar a mi esposa y asegurarme de que esté bien.";
		link.l1.go = "Nathaniel_13";
		break;

	case "Nathaniel_13":
		dialog.text = "Sí, Dannie también no se ve por ningún lado. Entonces actuamos así - Tyrex y Svenson ya se han apresurado al puerto, llegarán a sus barcos en botes. Nosotros vamos a la residencia por las esposas, el resto - que organicen la defensa en la orilla. ¿Puedes enviar a algunos de tus oficiales para reunir gente en tu barco? Ayuda allí obviamente no vendría mal.";
		link.l1 = "¡Bien, todos, movámonos! ¡Cada segundo cuenta!";
		link.l1.go = "Nathaniel_14";
		break;

	case "Nathaniel_14":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		chrDisableReloadToLocation = false;
		LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
		break;

	case "Nathaniel_15":
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			sld = characterFromId("Helena");
		else
			sld = characterFromId("Mary");
		dialog.text = "¡Más rápido, arriba! Dannie y " + sld.name + " ¡deben estar allí! Y si esos bastardos les hacen daño...";
		link.l1 = "¡Ni lo pienses! ¡Arriba! ¡Vamos!";
		link.l1.go = "Nathaniel_16";
		break;

	case "Nathaniel_16":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		chrDisableReloadToLocation = false;
		LocatorReloadEnterDisable("Pirates_townhall", "reload1_back", true);
		pchar.quest.longhappy_isla_bedroom.win_condition.l1 = "location";
		pchar.quest.longhappy_isla_bedroom.win_condition.l1.location = "Location_reserve_04";
		pchar.quest.longhappy_isla_bedroom.function = "LongHappy_IslaTesoroBedroom";
		break;

	case "Nathaniel_17":
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			sld = characterFromId("Helena");
		else
			sld = characterFromId("Mary");
		dialog.text = "¡Maldita sea! ¡Tu compañero, se lanzó directamente al cañón para que ese bastardo no disparara a las chicas!";
		link.l1 = "Y le dieron una bala... Espera, Nathan... ¡está respirando! ¡Todavía está vivo! ¡Maldita sea, necesito a Gino!" + sld.name + ", cariño, ¿cómo estás?";
		link.l1.go = "Nathaniel_18";
		break;

	case "Nathaniel_18":
		DialogExit();
		npchar.dialog.currentnode = "Nathaniel_19";
		sld = characterFromId("Danielle");
		sld.dialog.currentnode = "Danielle_7_1";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;

	case "Nathaniel_18":
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			sld = characterFromId("Helena");
		else
			sld = characterFromId("Mary");
		dialog.text = "¡Estamos bien, Charles! Voy a desatarla. Oigo disparos en el puerto, tú y Nathan deben ir allí, de lo contrario, Barbazon destruirá todos nuestros barcos. ¡No pierdan tiempo!";
		link.l1 = "Encontraré a Gino y lo enviaré aquí, él ayudará... ¡debe hacerlo!" + sld.name + ", querida, quédate aquí, cuida de él, ambos ustedes.";
		link.l1.go = "Nathaniel_19";
		break;

	case "Nathaniel_19":
		dialog.text = "¡Charles, date prisa! ¡sea lo que sea que decidas, el tiempo ahora vale su peso en oro! ¡Si los barcos de Jacques llegan a la costa, todo será en vano!";
		link.l1 = "Sí, lo sé. ¡Maldito bastardo!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("LongHappy_OutOfBedroom");
		break;

	case "Nathaniel_20":
		dialog.text = "¡Más rápido, no tenemos tiempo para charlas!";
		link.l1 = "";
		link.l1.go = "Nathaniel_20_1";
		break;

	case "Nathaniel_20_1":
		DialogExit();
		npchar.dialog.currentnode = "Nathaniel_20";
		break;

	case "Nathaniel_21":
		dialog.text = "¡Mierda! Perdóname, Charles. Estábamos atrapados arriba, había una docena de esos bastardos... Es una lástima que no llegué a tiempo, pero veo que te encargaste de la situación de la mejor manera posible.";
		link.l1 = "No puedo decir que fue fácil, pero, ¡carajo!, ¡recibí un gran placer cuando maté a este 'buen hombre'! ¡Es hora de ir a tierra, Nathan, nuestra gente nos espera allí!";
		link.l1.go = "Nathaniel_22";
		break;

	case "Nathaniel_22":
		dialog.text = "Sí, necesitamos visitar a tu muchacho indio, terminar aquí e ir a Sharptown.";
		link.l1 = "Tienes razón, estoy detrás de ti.";
		if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner"))
			link.l1.go = "Nathaniel_23";
		else
			link.l1.go = "Nathaniel_25";
		break;

	case "Nathaniel_23":
		dialog.text = "Por cierto, ¡encontramos a Marcus! Estaba en la bodega de carga, atado e inconsciente.";
		link.l1 = "¿Está vivo?";
		link.l1.go = "Nathaniel_24";
		break;

	case "Nathaniel_24":
		dialog.text = "Está en mal estado, pero estará bien. Tyrex es más fuerte que un clavo para un ataúd, así que no te preocupes, ya ha sido trasladado a tu barco y ha pedido un sable.";
		link.l1 = "¡Finalmente, buenas noticias! Muy bien, terminemos aquí y volvamos.";
		link.l1.go = "Nathaniel_25";
		break;

	case "Nathaniel_25":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;

	// Даниэль Хоук
	case "Danielle":
		dialog.text = "Hola, Charles. Déjame verte, ¡te has vuelto más guapo, no puedo quejarme! ¡Casi como Nathan, hace unos diez años! Entra, no te quedes en la puerta, ¡todos te han estado esperando!";
		link.l1 = "¡Gracias, Dannie, me alegra mucho verte! ¡Iré a verte a ti y a Nathan un poco más tarde y entonces hablaremos!";
		link.l1.go = "Danielle_1";
		break;

	case "Danielle_1":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocator(npchar, "tables", "stay1", "LongHappy_DannyNorm", -1);
		break;

	case "Danielle_2":
		pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count) + 1;
		dialog.text = "Charles, siéntate, ¡Nathan y yo estamos tan felices por ti! Marcus, Jan y mi esposo han preparado algo para ti - pero los regalos esperarán. Por ahora, permíteme felicitarte y desearte felicidad. ¡Tu elegida es simplemente un milagro! Dime, no lograste que ella llevara un vestido blanco allá en Martinica, ¿verdad?";
		link.l1 = "Gracias, Dannie. Sí, resultó gracioso con el vestido - estoy seguro de que en la alta sociedad nuestra boda dio lugar a muchos rumores escandalosos. Todos honestamente desviaron la mirada y fingieron que no pasaba nada fuera de lo común. Modales y todo eso - pero no me importan los chismes, la amo y eso es lo más importante.";
		link.l1.go = "Danielle_3";
		break;

	case "Danielle_3":
		dialog.text = "¡Tienes toda la razón! Yo también caminé hacia el altar, con una espada y con un par de pistolas detrás del cinto. Pero fue en Port Royal, incluso antes de que se convirtiera en una digna residencia colonial. Había tanta diversión en esos tiempos, incluso más que en Tortuga bajo Levasseur y nadie se sorprendía... eh. Sin embargo, estoy charlando todo el tiempo - ve a saludar a los invitados, todos han estado esperándote aquí, ¡dame solo un abrazo!";
		link.l1 = "¡Ah, Dannie, cómo podría siquiera negarte, ja-ja! ¡Ni te imaginas lo contentos que estamos mi esposa y yo de veros a todos!";
		link.l1.go = "Danielle_4";
		break;

	case "Danielle_4":
		DialogExit();
		npchar.dialog.currentnode = "Danielle_4_1";
		if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed))
			LongHappy_IslaTesoroToVine();
		break;

	case "Danielle_4_1":
		dialog.text = "¡Sois una pareja hermosa, Charles!";
		link.l1 = "Gracias, Dannie...";
		link.l1.go = "Danielle_4";
		break;

	case "Danielle_5":
		dialog.text = "Charles, tiene razón... no tienes elección. No creo en la misericordia de Jacques el Bondadoso, si trata con Tyrex y los demás. Sabes lo que debe hacerse.";
		link.l1 = "";
		link.l1.go = "Danielle_6";
		break;

	case "Danielle_5_1":
		dialog.text = "¡No le escuches! Si el Kindman decidió hacer tal locura, ¡no perdonará a nadie!";
		link.l1 = "";
		link.l1.go = "Danielle_6_1";
		break;

	case "Danielle_6":
		DialogExit();
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			sld = characterFromId("Helena");
		else
			sld = characterFromId("Mary");
		sld.Dialog.currentnode = "LongHappy_39";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;

	case "Danielle_6_1":
		DialogExit();
		sld = characterFromId("LH_Dussak");
		sld.dialog.currentnode = "Dussak_5";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;

	case "Danielle_7_1":
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			sld = characterFromId("Helena");
		else
			sld = characterFromId("Mary");
		dialog.text = "¡Estamos bien, Charles! La desataré. Oigo cañones en el puerto, tú y Nathan deben ir allá, de lo contrario Barbazon hundirá nuestros barcos como patitos en un barril. ¡No debéis perder ni un minuto!";
		link.l1 = "Encontraré a Gino y lo enviaré aquí, él ayudará... ¡debe hacerlo, maldita sea!" + sld.name + ", querida, quédate aquí, cuida de Tichingitu.";
		link.l1.go = "Danielle_8_1";
		break;

	case "Danielle_7":
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			sld = characterFromId("Helena");
		else
			sld = characterFromId("Mary");
		dialog.text = "Nathan, ¡no!!!";
		link.l1 = "Él aprovechó el momento y corrió hacia el cañón para cubrirte, Dannie... " + sld.name + ", cariño, ¿cómo estás?";
		link.l1.go = "Danielle_8";
		break;

	case "Danielle_8":
		DialogExit();
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			sld = characterFromId("Helena");
		else
			sld = characterFromId("Mary");
		sld.Dialog.currentnode = "LongHappy_41";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;

	case "Danielle_8_1":
		DialogExit();
		sld = characterFromId("Nathaniel");
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;

	case "Danielle_9":
		dialog.text = "¡Sí, Charles, está vivo! El corazón apenas late, ¡pero está vivo! ¿Qué debemos hacer?!";
		link.l1 = "¡Necesitamos a Gino, inmediatamente! Lo encontraré y lo enviaré aquí, él ayudará... ¡debe hacerlo!";
		link.l1.go = "Danielle_10";
		break;

	case "Danielle_10":
		dialog.text = "¡Charles, no tenemos tiempo! ¡Si los barcos de Jacques llegan a la costa, todo será en vano! Mi esposo... hizo lo que debía. Ahora es tu turno. Yo me quedaré con él. ¡Vosotros dos debéis ir a buscar a Gino!";
		link.l1 = "Sí, lo sé. ¡Maldito bastardo, pagará por esto!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("LongHappy_OutOfBedroom");
		break;

	case "Danielle_11":
		dialog.text = "¡Aquí estás al fin! ¿Todos están bien?";
		if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
		{
			link.l1 = "Estamos bien, Dannie, no te preocupes. Jacques está muerto, sus barcos están en el fondo. ¿Cómo está Tichingitu?";
			link.l1.go = "Danielle_17";
		}
		else
		{
			link.l1 = "Estamos bien, Dannie, no te preocupes. Jacques está muerto, sus barcos están en el fondo. ¿Cómo está Nathan?";
			link.l1.go = "Danielle_12";
		}
		break;

	case "Danielle_12":
		if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
		{
			dialog.text = "¡Está bien! ¡Tu médico italiano es un genio! Nathan está durmiendo arriba, pero, según Gino, nada le amenaza. Una semana o dos en la cama, vino tinto, y, como él dijo 'la visita de una dama bien dispuesta hacia él' ejem... En general - todo está bien, nos has salvado de nuevo, Charles, ¿cómo puedo agradecerte?";
			link.l1 = "Fue Nathaniel quien salvó a mi esposa y a ti. Y siempre le estaré en deuda por esto. No puedes ni imaginar lo contento que estoy de escuchar que se está recuperando. Déjalo descansar, te veré más tarde.";
			link.l1.go = "Danielle_13";
		}
		else
		{
			dialog.text = "Está bien, la bala pasó de largo, y nuestro cirujano del 'Centurión' no estaba lejos. Se estaba escondiendo de todo este lío. Así que Nathan vivirá, un par de semanas en cama, ¡poca cosa!";
			link.l1 = "Dannie, él cubrió a mi esposa y a ti de una bala y siempre le deberé por esto. No puedes ni imaginar lo contento que estoy de saber que se está recuperando. Déjalo descansar, te veré más tarde.";
			link.l1.go = "Danielle_14";
		}
		break;

	case "Danielle_13":
		dialog.text = "¡Por supuesto! Pero debo dejarte, tengo que ir a mi esposo... ¿No te importa si le prestamos a tu amigo? Cuando Nathan mejore, yo misma lo llevaré a Antigua. El Centurión de algún modo sobrevivió milagrosamente, solo necesita reclutar un nuevo equipo.";
		link.l1 = "Está bien, Dannie, saluda a Gino y Nathan. Debo irme.";
		link.l1.go = "Danielle_23";
		break;

	case "Danielle_14":
		dialog.text = "Por supuesto, Charles, pero... Tengo malas noticias. Ese italiano, Guineili, que estaba en tu boda... Su cuerpo fue encontrado en una habitación de la taberna. Yo... lo siento, Charles.";
		link.l1 = "¿Qué? ¿Gino?! ¡No! ¿Cómo?";
		link.l1.go = "Danielle_15";
		break;

	case "Danielle_15":
		dialog.text = "No lo sé, probablemente uno de esos bastardos que pasaron por las catacumbas y atacaron el pueblo. Aparentemente, estaban escondidos allí, esperando un momento para escapar, y lo encontraron...";
		link.l1 = "¡Maldición! No, no lo creo...";
		link.l1.go = "Danielle_16";
		break;

	case "Danielle_16":
		pchar.questTemp.LongHappy.Jino_died = "true";
		dialog.text = "Lo siento, Charles. Fue una maldita carnicería, y él no era un luchador... Si quieres, enviaremos su cuerpo a tu barco, llévalo a casa y entiérralo como debe ser. Lo siento mucho...";
		link.l1 = "Gracias, Dannie. Da la orden de cargar el cuerpo en un barco. Debo irme ahora... Necesito pensar. Y saluda a Nathan.";
		link.l1.go = "Danielle_23";
		break;

	case "Danielle_17":
		if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
		{
			dialog.text = "¡Está bien! ¡Tu médico italiano es un genio! Está durmiendo en la habitación de arriba, y Gino lo está cuidando. Dice 'una semana o dos y estará bien'.";
			link.l1 = "¡Grandes noticias! ¿Supongo que no puedo visitarlo ahora mismo?";
			link.l1.go = "Danielle_18";
		}
		else
		{
			dialog.text = "Lo siento mucho, Charles. Encontré a nuestro cirujano del Centurión, pero no pudo hacer nada... Tu amigo murió hace un par de horas.";
			link.l1 = "¿Tichingitu?! ¡No! ¡No lo creo!!!";
			link.l1.go = "Danielle_19";
		}
		break;

	case "Danielle_18":
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			sld = characterFromId("Helena");
		else
			sld = characterFromId("Mary");
		dialog.text = "No, el italiano prohibió estrictamente molestarlo, déjalo descansar, y Gino debería descansar después de todas las preocupaciones. Incluso le dije " + sld.name + " salir a dar un paseo cuando nos enteramos de que todo iba a estar bien\nY una cosa más... tu amigo, él me cubrió de la bala. Ni siquiera sé cómo agradecérselo, dile que a partir de ahora él también es parte de nuestra familia, y tú, ¡tú nos salvaste de nuevo, Charles!";
		link.l1 = "Bien está lo que bien acaba, Dannie. Ve con Nathan, que te ha estado esperando, y yo tomaré un pequeño descanso aquí y buscaré mi " + sld.name + ".";
		link.l1.go = "Danielle_23";
		break;

	case "Danielle_19":
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			sld = characterFromId("Helena");
		else
			sld = characterFromId("Mary");
		dialog.text = "Lo siento, hice todo lo que pude, y " + sld.name + ", también. Nos cubrió de esa bala, y nunca olvidaré eso, créeme.";
		link.l1 = "... Hace mucho tiempo dijo que moriría por mí... Supongo que nunca supo que sacrificaría su vida por todos nosotros... y ahora es un héroe y lo recordaré como nada menos... ¿Dónde está " + sld.name + "¿Está ella bien?";
		link.l1.go = "Danielle_20";
		break;

	case "Danielle_20":
		dialog.text = "No puedo decirlo así... quiero decir, físicamente sí. Pero... ya sabes... Dijo que salió a dar un paseo, para despejarse la mente. Probablemente te vio atracado y volverá pronto.";
		link.l1 = "¡Maldición sobre ti, Jacques Barbazon... Deberíamos haberlo matado antes!";
		link.l1.go = "Danielle_21";
		break;

	case "Danielle_21":
		dialog.text = "Espera... eso no es todo aún. Ese italiano, ¿Guineili, sí? Ese joven callado. Él fue... su cuerpo fue encontrado en una taberna... No sé, probablemente uno de esos malditos que pasaron por las catacumbas y atacaron la ciudad. Aparentemente, se estaban escondiendo allí, buscando un momento para escapar, y lo encontraron a él...";
		link.l1 = "¿Y Gino también?! Hoy es verdaderamente un día lluvioso...";
		link.l1.go = "Danielle_22";
		break;

	case "Danielle_22":
		pchar.questTemp.LongHappy.Tichingitu_died = "true";
		dialog.text = "Lo siento, Charles... Si quieres, enviaremos sus cuerpos a tu barco, lleva a los muchachos a casa y entiérralos como debe ser. Lo siento mucho...";
		link.l1 = "Gracias Dannie. Hazlo... Debería irme... Necesito... pensar.";
		link.l1.go = "Danielle_23";
		break;

	case "Danielle_23":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
		sld = characterFromId("Svenson");
		sld.dialog.currentnode = "Svenson_26";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;

	// Додсон
	case "Dodson":
		pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count) + 1;
		dialog.text = "Charles, ¿puedes siquiera imaginar cuántos corazones de chicas rompiste con esta boda tuya? Sí, la mitad de las chicas del archipiélago deben haber llorado después de tu boda, ¡jaja!";
		link.l1 = "¿Qué puedo hacer? Solo necesitaba una y la conseguí. Pero es demasiado temprano para que las chicas se molesten, porque todavía te tienen a ti, Stiven.";
		link.l1.go = "Dodson_1";
		break;

	case "Dodson_1":
		dialog.text = "¡Y eso es cierto! Terminaremos aquí y me ocuparé de ellos de inmediato, ¡maldición! Vamos, Charles, bebamos por tu suerte y vida familiar. Así que, como dicen, ¡felices para siempre!";
		link.l1 = "¡Gracias, mi amigo!";
		link.l1.go = "Dodson_2";
		break;

	case "Dodson_2":
		DialogExit();
		npchar.dialog.currentnode = "Dodson_2_1";
		if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed))
			LongHappy_IslaTesoroToVine();
		break;

	case "Dodson_2_1":
		dialog.text = "¡Por una feliz vida familiar, ja-ja!";
		link.l1 = "¡Salud!";
		link.l1.go = "Dodson_2";
		break;

	// Венсан
	case "Vensan":
		pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count) + 1;
		dialog.text = "Charles, ¿puedes siquiera imaginar cuántos corazones de chicas rompiste con esta boda tuya? Sí, la mitad de las chicas del archipiélago debieron haber llorado tras tu boda, ¡jaja!";
		link.l1 = "¿Qué puedo hacer? Solo necesitaba una y la conseguí. Pero es demasiado pronto para que las chicas se disgusten, porque aún te tienen a ti, Bernard.";
		link.l1.go = "Vensan_1";
		break;

	case "Vensan_1":
		dialog.text = "¡Y eso es cierto! Terminamos aquí e inmediatamente me ocupo de ellos, ¡maldita sea! Vamos, Charles, bebamos por tu suerte y vida familiar. Así que, como dicen, ¡felices para siempre!";
		link.l1 = "¡Felices para siempre!";
		link.l1.go = "Vensan_2";
		break;

	case "Vensan_2":
		DialogExit();
		npchar.dialog.currentnode = "Vensan_2_1";
		if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed))
			LongHappy_IslaTesoroToVine();
		break;

	case "Vensan_2_1":
		dialog.text = "¡Por una vida familiar feliz, ja ja!";
		link.l1 = "¡Gran brindis!";
		link.l1.go = "Vensan_2";
		break;

	case "Vensan_3":
		pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count) + 1;
		dialog.text = "Ja, Charles, ¡así que tú también te has casado y te has vuelto aburrido, como nuestro viejo Nathan! Asuntos apasionantes y todo lo demás ahora están en el pasado, ¿eh? ¡Hombre de familia ejemplar!";
		link.l1 = "¡Sigue esperando, Bernard! ¡Mi esposa no es de las que se aburrirá sentada bajo la ventana de un naufragio familiar! ¡Lo único que cambiará es la plenitud de las bolsas de las chicas del burdel desde aquí hasta Curazao!";
		link.l1.go = "Vensan_4";
		break;

	case "Vensan_4":
		dialog.text = "¡No es una gran pérdida, digo yo! Mejor tener una moneda de oro que una bolsa de níqueles. ¡Tomemos un trago! ¡Salud por ti y tu esposa! ¡Guarda tu oro y sé feliz!";
		link.l1 = "Gracias, Bernard. Oh, este es un ron realmente fuerte. ¡Uf!";
		link.l1.go = "Vensan_5";
		break;

	case "Vensan_5":
		DialogExit();
		npchar.dialog.currentnode = "Vensan_5_1";
		if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed))
			LongHappy_IslaTesoroToVine();
		break;

	case "Vensan_5_1":
		dialog.text = "A tu novia, quiero decir, ¡ya una esposa!";
		link.l1 = "¡Gracias!";
		link.l1.go = "Vensan_5";
		break;

	case "Vensan_6":
		dialog.text = "¡Llegas justo a tiempo, Charles, gracias!";
		link.l1 = "¿Dónde está la diversión aquí? Pensé que ya estaban cargando los barcos en el puerto.";
		link.l1.go = "Vensan_7";
		break;

	case "Vensan_7":
		dialog.text = "Marcus me dejó para organizar una defensa en la costa. Nos faltan hombres, los muchachos en el puerto necesitan pólvora. Pensé en pasar, tomar un par de barriles... y luego estos matones. Ja, se escondieron, supongo, querían esperar o robar a alguien. Y todavía estoy lleno de ron de Hawk, así que sin ti no sé si ahora estaría respirando o no.";
		link.l1 = "De nada. Bien, Bernard, asegúrate de que la ciudad esté segura. Yo debo irme, ¡cuídate!";
		link.l1.go = "Vensan_8";
		break;
		
		case "Vensan_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.LongHappy.Vensan_alive = "true";
		break;

		// Джино
		case "Jino":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count) + 1;
			dialog.text = "¡Capitán, permítame felicitarle de todo corazón a usted y a su amada en este día tan auspicioso! ¡Sean felices y cuídense mutuamente!";
			link.l1 = "Gracias, Gino. ¡Me alegra que hayas decidido venir! Espero que mi color... no te moleste.";
			link.l1.go = "Jino_1";
		break;
		
		case "Jino_1":
			dialog.text = "Este es... un viaje muy educativo. Debo decir que no he salido de Antigua durante mucho tiempo, y en esta sociedad no me resulta fácil sentirme cómodo. Pero, siempre supiste cómo entender a las personas, así que intentaré mantener la calma, ya que confío en ti.";
			link.l1 = "¿Quizás necesites beber algo más fuerte? ¿Relájate y encuentra a alguien con quien hablar?";
			link.l1.go = "Jino_2";
		break;
		
		case "Jino_2":
			dialog.text = "Gracias, capitán, ya tengo suficiente vino diluido. El alcohol, debo advertirle, no es muy bueno para el hígado y posiblemente para el corazón. En cuanto a las conversaciones, intenté discutir las propiedades curativas del Chirik-Sanango con ese caballero de allí, también se le llama Manaka. Los nativos de Tierra Firme lo utilizan para...";
			link.l1 = "Déjame adivinar, ¿ese caballero no pudo sostener la conversación? Gino, por mi bien y solo por hoy, prueba el ron que Jan está sirviendo allá en el mostrador.  Si puedes adivinar todos sus ingredientes, Nathaniel Hawk, que está allí, quedará extremadamente impresionado. Estoy seguro de que estará encantado de estar en tu compañía, así como Svenson, el hombre en el mostrador, ambos respetan a las personas educadas.";
			link.l1.go = "Jino_3";
		break;
		
		case "Jino_3":
			DialogExit();
			npchar.dialog.currentnode = "Jino_3_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.HambitOfficer"))
				{
					sld = characterFromId(pchar.questTemp.LongHappy.HambitOfficer);
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Baker") != -1)
					{
						sld = characterFromId("Baker");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						if (GetCharacterIndex("Tichingitu") != -1)
						{
							sld = characterFromId("Tichingitu");
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", -1, 0);
						}
						else
						{
							sld = characterFromId("Mary");
							sld.dialog.currentnode = "LongHappy_57";
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", -1, 0);
						}
					}
				}
			}
			else (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Jino_3_1":
		dialog.text = "¡A tu salud y a la salud de tu encantadora esposa!";
		link.l1 = "¡Gracias, amigo!";
		link.l1.go = "Jino_3";
		break;
		
		case "Jino_4":
			dialog.text = "¡Capitán, eres tú, gracias a Dios! Esas personas enmascaradas, las vi y me escondí aquí, y trataron de romper la puerta...";
			link.l1 = "Está bien, Gino, nadie te va a hacer daño ya. Es una gran suerte que te encontré, necesito tu ayuda. Mi amigo está herido - le han disparado y ha perdido mucha sangre. ¡Debemos darnos prisa!";
			link.l1.go = "Jino_5";
		break;
		
		case "Jino_5":
			dialog.text = "Disparo... sangre... bien, capitán. Mientras venía aquí, agarré mi cofre de campamento con todas las herramientas en caso de una herida. Llévame con él, veré qué se puede hacer. Y estos... hombres enmascarados, ¿quizás se han escondido en otro lugar?";
			link.l1 = "Estoy seguro, eran los últimos. Gino, hay batalla en el puerto y debo ir allí ahora mismo. Tienes que llegar a la residencia por tu cuenta, no está lejos. La casa grande está a la vuelta de la esquina, no la perderás. No tengas miedo, las calles están llenas de nuestra gente, ¡y date prisa, te lo suplico!";
			link.l1.go = "Jino_6";
		break;
		
		case "Jino_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 7.0);
			LocatorReloadEnterDisable("Pirates_tavern", "reload1_back", false);
			pchar.questTemp.LongHappy.Jino_alive = "true";
			AddQuestRecord("LongHappy", "18");
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim")) sld = characterFromId("Tichingitu");
			else sld = characterFromId("Nathaniel");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName1", sTemp);
		break;
		
		case "Jino_7":
			dialog.text = "¡Capitán, permítame felicitarle de todo corazón a usted y a su amada en este día tan auspicioso! Sean felices y cuídense mutuamente.";
			link.l1 = "Gracias, Gino. ¡Me alegra que hayas decidido venir! ¿El viaje fue tranquilo?";
			link.l1.go = "Jino_8";
		break;
		
		case "Jino_8":
			dialog.text = "Todo está bien, capitán, gracias por preocuparse. Debo decir - no he salido de Antigua durante mucho tiempo, y entre la élite yo... no me siento muy cómodo. Pero la razón para venir no me dejó elección. Por cierto, el servicio fue excelente, ¡estoy muy contento por ambos! La novia en este atuendo es encantadora, ¿es esta una nueva moda? Resulta que me quedé atrás en la vida, pero me gusta, de verdad.";
			link.l1 = "La moda... De alguna manera sí, o al menos, lo será pronto. Bien, diviértete, Gino, y si los nobles interlocutores te aburren, entonces ven al puerto. Toda la tripulación está en la taberna. Los muchachos estarán felices de verte.";
			link.l1.go = "Guests_block";
		break;
		
		case "Jino_9":
			dialog.text = "¡Capitán, una vez más, le felicito a usted y a su hermosa esposa! ¡Largos y felices años para ustedes juntos!";
			link.l1 = "Gracias, Gino. ¡Me alegra que hayas venido! Espero que mi color... no te moleste.";
			link.l1.go = "Jino_10";
		break;
		
		case "Jino_10":
			dialog.text = "Esta sociedad no es fácil para mí para sentirme cómodo. Pero, siempre supiste elegir a la gente, así que intentaré mantener la calma, ya que confío en ti..";
			link.l1 = "¿Quizás necesites beber algo más fuerte? ¿Relajarte y encontrar alguien con quien hablar?";
			link.l1.go = "Jino_11";
		break;
		
		case "Jino_11":
			dialog.text = "Gracias, capitán, tengo suficiente vino diluido. El alcohol, debo advertirle, no es muy bueno para el hígado y posiblemente para el corazón. En cuanto a las conversaciones, intenté discutir las propiedades curativas del Chirik-Sanango con ese caballero, también se le llama Manaka. Los nativos de Tierra Firme lo usan para...";
			link.l1 = "Déjame adivinar, ¿ese caballero no pudo sostener la discusión? Gino, por mi bien y solo hoy, prueba el ron que Jan está sirviendo allá en el mostrador. Si puedes adivinar todos sus ingredientes, Nathaniel Hawk, allá, quedará extremadamente impresionado. Estoy seguro de que también estará encantado de estar en tu compañía, al igual que Svenson, el hombre en el mostrador, ambos respetan a las personas educadas.";
			link.l1.go = "Jino_3";
		break;

	// Лонгвэй
	case "Longway":
		pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count) + 1;
		dialog.text = "'Solo ahora en un país extraño, sintiéndome un forastero, en este brillante día de fiesta, siento doblemente nostalgia por mis parientes'.";
		link.l1 = "¡Longway, nunca pensé que eras un maestro de la palabra!";
		link.l1.go = "Longway_1";
		break;

	case "Longway_1":
		dialog.text = "Lo siento, Capitán, he estado reflexionando mucho. Estas son palabras de Wang Wei, un poeta que vivió en un período de la dinastía Tang, que gobernó hace mucho tiempo en mi tierra natal.";
		link.l1 = "Estas palabras son tan hermosas. Espero que algún día vuelvas a ver tu tierra natal...";
		link.l1.go = "Longway_2";
		break;

	case "Longway_2":
		dialog.text = "''¿Es posible garantizar y saber que bajo el arco de misteriosas losas de piedra es imposible, al intentar hacerlo, encontrar un pasaje, más allá del cual se encuentra el valle de U-lin?' \nNo, Capitán, lo sabes - Longway no va a regresar a casa. Ahora, aquí está mi hogar y ¡tenemos un gran evento aquí hoy! ¡Envío mis mejores deseos para ti y tu hermosa novia! Que vuestra felicidad sea tan larga como el río Yangtsé, tachonado con diamantes de estrellas, entre las perlas del loto.";
		link.l1 = "Gracias, mi viejo amigo. Tus palabras no son menos hermosas que las de Wang Wei.";
		link.l1.go = "Longway_3";
		break;

	case "Longway_3":
		dialog.text = "¡Tomemos un trago, Capitán! Este ron quita la tristeza y refresca la alegría no peor que el maotai.";
		link.l1 = "¡A tu salud, Longway!";
		link.l1.go = "Longway_4";
		break;

	case "Longway_4":
		DialogExit();
		npchar.dialog.currentnode = "Longway_4_1";
		if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
		{
			if (GetCharacterIndex("Baker") != -1)
			{
				sld = characterFromId("Baker");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				if (GetCharacterIndex("Tichingitu") != -1)
				{
					sld = characterFromId("Tichingitu");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					sld = characterFromId("Mary");
					sld.dialog.currentnode = "LongHappy_57";
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
			}
		}
		else
		{
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed))
				LongHappy_IslaTesoroToVine();
		}
		break;

	case "Longway_4_1":
		dialog.text = "¡Gran boda, capitán!";
		link.l1 = "¡Bebe y diviértete!";
		link.l1.go = "Longway_4";
		break;

	// Книппель
	case "Knippel":
		pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count) + 1;
		if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
		{
			dialog.text = "¡Dame un disparo de cadena! ¡Todos nuestros muchachos te felicitan! ¿Cómo fue el servicio?";
			link.l1 = "¡Todo está bien, Charlie! ahora estoy oficialmente casado y respetable, y mi primer oficial es madame de Monper ahora.";
		}
		else
		{
			dialog.text = "¡Golpéame con una bala encadenada, qué evento, capitán! ¡Casi todos los barones de la Hermandad están aquí! ¡Supongo que cada puritano español imagina el Infierno así! Y el ron, es algo especial, ¡bala encadenada a mi barril!";
			link.l1 = "Sí, la gente aquí no es la más respetuosa de la ley, pero nosotros mismos no somos ángeles, Charlie, y cada una de estas personas me es querida a su manera.";
		}
		link.l1.go = "Knippel_1";
		break;

	case "Knippel_1":
		if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
		{
			dialog.text = "¡Es maravilloso, andanada de cadenas a mi trasero! Capitán, quiero decir, esta celebración es en tu honor, bueno, yo... yo, felicito, quiero decir... también... Felicidad y... esto, no soy bueno en discursos. ¡Pero debes saber que todos te amamos a ambos y te seguiremos incluso hasta el infierno, capitán!";
			link.l1 = "Gracias, viejo amigo.";
		}
		else
		{
			dialog.text = "Espera, quiero decir... ¿Qué quiero decir, bola encadenada a mi trasero? ¡Capitán, quise decir que este día es en tu honor, bueno, yo... Te felicito... y también... Te deseo felicidad y... y lo siento, capitán, podría estar un poco demasiado borracho para dar un discurso, bola encadenada a mi cuello, no he estado sobrio en un tiempo ja-ja-ja!";
			link.l1 = "¡Ja! Está bien... gracias, viejo amigo.";
		}
		link.l1.go = "Knippel_2";
		break;

	case "Knippel_2":
		Log_Info("Tienes las gemas");
		PlaySound("interface\important_item.wav");
		TakeNItems(pchar, "jewelry4", 20);
		dialog.text = "¡Ah! Y sí, capitán, acepte esto, por favor. Para usted y su dama. He guardado estas piedras para tiempos difíciles... Entiendo que no le falta oro, pero no estarán de más, ¿verdad?";
		link.l1 = "¡Charlie, eres realmente un alma generosa, y estos esmeraldas se verán espléndidos en los pendientes de la familia de madame de Monper!";
		link.l1.go = "Knippel_3";
		break;

	case "Knippel_3":
		dialog.text = "Bueno, brindemos por esto, metralla a mi... hm. Solo sé feliz, tanto tú como tu belleza, ¡capitán!";
		link.l1 = "¡Lo haremos, Charlie!";
		link.l1.go = "Knippel_4";
		break;

	case "Knippel_4":
		DialogExit();
		npchar.dialog.currentnode = "Knippel_4_1";
		if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
		{
			if (GetCharacterIndex("Baker") != -1)
			{
				sld = characterFromId("Baker");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				if (GetCharacterIndex("Tichingitu") != -1)
				{
					sld = characterFromId("Tichingitu");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					sld = characterFromId("Mary");
					sld.dialog.currentnode = "LongHappy_57";
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
			}
		}
		else
		{
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed))
				LongHappy_IslaTesoroToVine();
		}
		break;

	case "Knippel_4_1":
		dialog.text = "¡Gran boda, capitán!";
		link.l1 = "¡Bebe y diviértete!";
		link.l1.go = "Knippel_4";
		break;

	// Тонзаг
	case "Tonzag":
		pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count) + 1;
		dialog.text = "Jamás pensé, capitán, que te vería casado. Normalmente, el camino que hemos elegido conduce por un sendero solitario directo a una tumba solitaria. En mi memoria, eres el primero que ha logrado salir de él. Vale la pena un brindis extra, ¿no es así?";
		link.l1 = "¡Esto es todo, camarada! Y realmente, me alegra que esta parte de mi vida haya quedado atrás. ¡Salud!";
		link.l1.go = "Tonzag_1";
		break;

	case "Tonzag_1":
		dialog.text = "¡Salud por vosotros y vuestra larga y feliz vida juntos! Maldición, mirándoos, recuerdo que yo mismo una vez estuve casado.";
		link.l1 = "¿Tú? ¿Casado? ¡Cosas interesantes me estás contando! Pero, ¿qué pasó?";
		link.l1.go = "Tonzag_2";
		break;

	case "Tonzag_2":
		dialog.text = "¿Qué, crees que siempre fui un viejo cíclope oliendo a pólvora y sangre, capitán? Pero no. Madame Tonzag ella... ella me amaba, supongo. Pero luego, sucedió una historia desagradable. En la cual la pareja Tonzag murió y solo el Calvo Gaston con un conjunto de cicatrices logró sobrevivir.";
		link.l1 = "Lo siento, Hércules, no lo sabía...";
		link.l1.go = "Tonzag_3";
		break;

	case "Tonzag_3":
		dialog.text = "Olvídalo, capitán, esa historia ocurrió hace mucho tiempo. Pero ahora, al mirarte, creo que mi historia aún puede tener un buen final. Así que, ¡bebamos por ello!";
		link.l1 = "Permíteme, camarada. Sabes, desde el día en que te conocí, siempre te he mirado como miraría a mi propio padre, así que tal vez algún día tengas la oportunidad de ser un gran abuelo. De todos modos, ¡Salud! Debo ocuparme del resto, hablaremos más tarde.";
		link.l1.go = "Tonzag_4";
		break;

	case "Tonzag_4":
		DialogExit();
		npchar.dialog.currentnode = "Tonzag_4_1";
		if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
		{
			if (GetCharacterIndex("Baker") != -1)
			{
				sld = characterFromId("Baker");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				if (GetCharacterIndex("Tichingitu") != -1)
				{
					sld = characterFromId("Tichingitu");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					sld = characterFromId("Mary");
					sld.dialog.currentnode = "LongHappy_57";
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
			}
		}
		else
		{
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed))
				LongHappy_IslaTesoroToVine();
		}
		break;

	case "Tonzag_4_1":
		dialog.text = "¡Gran celebración, Capitán!";
		link.l1 = "¡Bebe y diviértete!";
		link.l1.go = "Tonzag_4";
		break;

	// Бейкер
	case "Baker":
		pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count) + 1;
		dialog.text = "¡Aquí está nuestro capitán! ¡Felicitaciones, tú y tu esposa son una hermosa pareja! ¡Qué viváis felices para siempre!";
		link.l1 = "Gracias, Raymond.";
		link.l1.go = "Baker_1";
		break;

	case "Baker_1":
		sTemp = "Sharptown";
		if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			sTemp = "Sent Pierre";
		dialog.text = "Parece que estás demasiado sobrio para tu propia boda, capitán. ¿Te gustaría arreglarlo? He tomado una botella de excelente jerez en el bar. ¡La mezcla con ron va de maravilla!";
		link.l1 = "Me gustaría, pero alguien tiene que vigilar las cosas aquí. De lo contrario, en " + sTemp + " no solo la taberna se echará de menos cuando llegue la mañana.";
		link.l1.go = "Baker_2";
		break;

	case "Baker_2":
		DialogExit();
		npchar.dialog.currentnode = "Baker_2_1";
		if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
		{
			if (GetCharacterIndex("Tichingitu") != -1)
			{
				sld = characterFromId("Tichingitu");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				sld = characterFromId("Mary");
				sld.dialog.currentnode = "LongHappy_57";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		}
		else
		{
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed))
				LongHappy_IslaTesoroToVine();
		}
		break;

	case "Baker_2_1":
		dialog.text = "¡Excelente comida y excelente ron, capitán! ¡Salud por usted y su joven esposa!";
		link.l1 = "¡Gracias!";
		link.l1.go = "Baker_2";
		break;

	// Алексус
	case "Alexus":
		dialog.text = "Jóvenes, ¿por qué están entrando sin permiso, se puede saber? El astillero está cerrado, ¿acaso no se nota? Vuelvan mañana.";
		link.l1 = "Maestro, lamento molestarlo, solo pasaremos por las mazmorras. Hay suministros para la boda, la taberna casi se queda sin bebidas.";
		link.l1.go = "Alexus_1";
		break;

	case "Alexus_1":
		dialog.text = "Oh, ¡Charles de Maure y Nathan Hawk en persona! Están celebrando la boda de alguien, ¿verdad? Está bien, vayan a buscar su licor. Los jóvenes deben divertirse, esta es la ley en cualquier época. Solo no hagan ruido con las botellas al regresar, ¡voy a dormir!";
		link.l1 = "Gracias, amo, seremos tan silenciosos como el río más tranquilo.";
		link.l1.go = "Alexus_2";
		break;

	case "Alexus_2":
		DialogExit();
		npchar.dialog.currentnode = "Alexus_2_1";
		LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
		pchar.GenQuestBox.Bermudes_Dungeon = true;
		pchar.GenQuestBox.Bermudes_Dungeon.box3.items.potionwine = 100;
		pchar.quest.longhappy_isla_box.win_condition.l1 = "locator";
		pchar.quest.longhappy_isla_box.win_condition.l1.location = "Bermudes_Dungeon";
		pchar.quest.longhappy_isla_box.win_condition.l1.locator_group = "box";
		pchar.quest.longhappy_isla_box.win_condition.l1.locator = "box3";
		pchar.quest.longhappy_isla_box.function = "LongHappy_IslaTesoroDungeon";
		break;

	case "Alexus_2_1":
		dialog.text = "Vamos, no te quedes ahí, ¡ve! Bueno, capitán, ¿estás contento con todo?";
		link.l1 = "...";
		link.l1.go = "Alexus_2_2";
		break;

	case "Alexus_2_2":
		DialogExit();
		npchar.dialog.currentnode = "Alexus_2_1";
		break;

	// пиратус в подземелье
	case "DungeonPirate":
		dialog.text = "¡¿Qué carajo?! Jacques dijo '¡Nadie baja aquí'! Hugo - corre de vuelta, llama a los demás, despejaremos el camino. ¡Mátenlos, muchachos!";
		link.l1 = "¡Mierda!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("LongHappy_BandosInDungeonFight");
		break;

	// киллеры
	case "killer":
		dialog.text = "¡Muchachos, olvidad los cofres, tenemos visitantes!";
		link.l1 = "Pensé que bastardos como tú habían sido asesinados con Jackman. ¡Bien, terminemos esto!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("LongHappy_ResidenceFight");
		break;

	case "killer_1":
		dialog.text = "¡Mierda... Nos han encontrado! ¡Alarma!";
		link.l1 = "¡Fuera de mi camino, cabrón!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("LongHappy_TavernKillerFight");
		break;

	// Ангерран
	case "Shivo":
		dialog.text = "Monsieur de Maure, buenas noches, ¿o ya es casi de mañana? Entre, tome asiento.";
		link.l1 = "¡Angerran De Chievous! ¡No me sorprende verte! ¡El insignificante, capaz de pelear solo con mujeres! ¿También las ataste? ¡Ahora voy a terminar lo que comencé en ese duelo en Martinica!";
		link.l1.go = "Shivo_1";
		break;

	case "Shivo_1":
		dialog.text = "Tranquilízate, joven, ¿ves esta pistola? Hay dos cañones. Quizás no sea bueno en esgrima, pero disparo con bastante precisión; baja tu espada o te perderás a un par de bellas damas, te lo aseguro.";
		link.l1 = "Miserable... Maldito seas.";
		link.l1.go = "Shivo_2";
		break;

	case "Shivo_2":
		dialog.text = "Y tú, monsieur pirata, baja tu arma también, así mismo, sí. Y ahora - siéntate, puedes servir el vino - allí en la mesa. Tendremos que esperar un poco hasta que monsieur Barbazon termine de destrozar los barcos de tus amigos, los barones piratas. Luego decidiremos cómo tú y yo resolveremos nuestras... hm, diferencias.";
		link.l1 = "¿Resolver desacuerdos? ¿Y cómo? ¿Quieres un duelo?";
		link.l1.go = "Shivo_3";
		break;

	case "Shivo_3":
		dialog.text = "No seas tan gracioso, Charles. Tú y madame Botot me habéis causado muchos problemas, y tengo la intención de pagaros con creces. Aunque ella me causó muchos más problemas que tú... sin embargo, si tú y el imponente monsieur pirata os quedáis quietos, entonces os doy mi palabra de honor: vuestras esposas seguirán con vida. Creo que en las colonias españolas de Tierra Firme tales esclavos son valorados. Incluso extraoficialmente. Pero esto sigue siendo vida, ¿no es así?";
		link.l1 = "¡Angerran, eres un cobarde, un bastardo y... Mierda, aún no hay palabras adecuadas para ti en ningún idioma!";
		link.l1.go = "Shivo_4";
		break;

	case "Shivo_4":
		dialog.text = "Lo sabes, no tienes elección. Solo puedo prometer que será rápido. Así que, si amas a estas mujeres, compórtate, salva sus vidas y alivia tu destino. Y sí, cierra la puerta si no te cuesta mucho. Gracias.";
		link.l1 = "";
		link.l1.go = "Shivo_5";
		break;

	case "Shivo_5":
		DialogExit();
		sld = characterFromId("Danielle");
		sld.dialog.currentnode = "Danielle_5";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;

	case "Shivo_6":
		dialog.text = "Qué damas tan belicosas. Aún así, les pediré que sean prudentes. Nunca me gustó matar mujeres.";
		link.l1 = "";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("LongHappy_BedroomShot");
		break;

	case "Shivo_7":
		dialog.text = "Mierda...";
		link.l1 = "¡Muere, bastardo!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("LongHappy_BedroomFight");
		break;

	// Дюссак
	case "Dussak":
		dialog.text = "¡Capitán Charles de Maure, barón Hawk - qué agradable sorpresa! Permítame presentarme - Mauritz Dussak, ese es mi nombre.";
		link.l1 = "¡Quítate de mi camino, bastardo! ¿Dónde está mi esposa?!";
		link.l1.go = "Dussak_1";
		break;

	case "Dussak_1":
		dialog.text = "¡Calma, caballeros! ¿Ven este cañón? Hay dos troncos. Me apodaron así por una razón - me encantan los sables, claro... pero también disparo bien, créanme. ¡Dejad vuestras espadas, o perderéis a un par de vuestras damas!";
		link.l1 = "Voy a masacrarte como a un cerdo, escoria...";
		link.l1.go = "Dussak_2";
		break;

	case "Dussak_2":
		dialog.text = "Pero ya serás viudo. ¿No lo quieres? Entonces cálmate y baja tu arma. Barón Hawk, por favor, cierra la puerta. Y nos calmaremos y esperaremos un poco mientras Jacques Barbazon allá en el puerto termine con los líderes de la Hermandad.";
		link.l1 = "¿Y qué sigue? ¿Nos abrazaremos y nos iremos juntos hacia el atardecer?";
		link.l1.go = "Dussak_3";
		break;

	case "Dussak_3":
		dialog.text = "No lo creo. Por tu cautiverio, Jacques me cubrirá de oro, con suerte, tal vez me convierta en barón. En cuanto a tus mujeres, tal vez las dejemos ir, pero respecto a ti - ay de mí... Si tienes suerte, pediré el derecho de matarte personalmente, capitán. Eres un espadachín famoso - sería interesante probarte. Sabes, también me considero un maestro.";
		link.l1 = "¿Un maestro en irrumpir en casas de noche y atar a mujeres medio dormidas? ¡Eres un gusano, y además un maldito gusano!";
		link.l1.go = "Dussak_4";
		break;

	case "Dussak_4":
		DialogExit();
		sld = characterFromId("Danielle");
		sld.dialog.currentnode = "Danielle_5";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;

	case "Dussak_5":
		dialog.text = "Escucha, señora, nunca he matado mujeres, no me hagas empezar, ¿de acuerdo? Estás poniendo nervioso al capitán y a tu esposo... ¡Maldita sea!";
		link.l1 = "";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("LongHappy_BedroomShot");
		break;

	case "Dussak_6":
		dialog.text = "Merdo...";
		link.l1 = "¡Muere, bastardo!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("LongHappy_BedroomFight");
		break;

	// Барбазон
	case "Barbazon_boarding":
		dialog.text = "¡Maldito francés, ¿no había ningún sable o bala?!";
		link.l1 = "Sabes, Jacques, tengo ambos para ti. Honestamente, casi me arrepiento de haberte dejado con vida cuando me enteré de tus trucos con Jackman. Pero ahora voy a arreglar eso.";
		link.l1.go = "Barbazon_boarding_1";
		break;

	case "Barbazon_boarding_1":
		dialog.text = "¿Eres tan valiente solo cuando caminas con un grupo de tus muchachos? ¡Cambiemos la situación! Trataré con los barones más tarde, pero tú no saldrás vivo de aquí, ¡rata!";
		link.l1 = "Esperado...";
		link.l1.go = "Barbazon_boarding_2";
		break;

	case "Barbazon_boarding_2":
		DialogExit();
		LAi_SetCurHPMax(npchar);
		AddItems(npchar, "potion2", 1);
		QuestAboardCabinDialogFree();
		LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "LongHappy_BarbAfterFight");
		AddDialogExitQuest("MainHeroFightModeOn");
		// подкрепление
		sld = GetCharacter(NPC_GenerateCharacter("LH_BarbCabinHelper", "citiz_57", "man", "man", 35, PIRATE, 0, true, "quest"));
		FantomMakeCoolFighter(sld, 35, 70, 70, "blade_21", "pistol4", "bullet", 300);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		AddItems(sld, "potion2", 2);
		break;

	// официантка
	case "waitress":
		dialog.text = "¡Capitán, ayúdeme, este salvaje, me ha secuestrado! Yo... necesito regresar a casa, ¡tío probablemente ya haya puesto toda la ciudad patas arriba!";
		link.l1 = "Tranquilízate, belleza, todo estará bien. Hazte a un lado, necesito hablar con tu 'salvaje'.";
		link.l1.go = "waitress_1a";
		break;

	case "waitress_1a":
		DialogExit();
		sld = characterFromId("Tichingitu");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

	case "waitress_1":
		dialog.text = "¡Gracias, capitán! ¡Me has salvado! Cuando desperté esta mañana en esta playa, yo... no puedo creer que iba a casarme con este salvaje, él...";
		if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 94)
		{
			link.l1 = "Sí, la mañana es un severo martillo para el cristal de esperanza de la noche. Entiende. Pero él es de la tribu Muscogue, y vive según las duras leyes de su tierra. Te robó con tu consentimiento, y pasasteis la noche juntos. Así que ahora, a los ojos de sus dioses, sois marido y mujer. Vamos a empacar tus cosas, y yo resolveré el asunto del rescate con tu tío.";
			link.l1.go = "waitress_2";
		}
		link.l2 = "Lo siento por esto. Tichingitu vive según las leyes de su tribu, pero es una buena persona. Por favor, olvida esta historia de secuestro.";
		link.l2.go = "waitress_5";
		break;

	case "waitress_2":
		dialog.text = "¿Esposa? ¿A los ojos de sus Dioses?! No, capitán, se lo ruego, ¡sálveme de esto! Fue solo... una aventura, él era tan galante y amable, no como esos palurdos... ¿Pero casarme? ¡Soy demasiado joven para mudarme a una choza con un salvaje!";
		link.l1 = "Él es mi oficial y mi mejor amigo, así que no te preocupes, le pago bien, y tendrás la mejor cabaña que jamás quisiste. Tichingitu es un buen cazador, él conseguirá comida para ti, y tú darás a luz y cuidarás a los niños.";
		link.l1.go = "waitress_3";
		break;

	case "waitress_3":
		dialog.text = "¿Niños? ¿Procurar comida? ¡No capitán, por favor no me hagas esto, te lo suplico!";
		link.l1 = "Bueno, tal vez pueda convencerlo. Pero no será fácil. La tribu Muskogue se toma muy en serio estas cosas, si alguien descubre que robó a una squaw y no se casó...";
		link.l1.go = "waitress_4";
		break;

	case "waitress_4":
		dialog.text = "¡Tienes que intentarlo, por favor! No se lo diré a nadie, ¡nadie lo sabrá! Le mentiré al tío, ¡no es la primera vez!";
		link.l1 = "Bien, deberías irte, hermosa india. Intentaré mantener alejado a mi amigo.";
		link.l1.go = "waitress_7";
		break;

	case "waitress_5":
		dialog.text = "¡Me robó como... como una cabra de un granero! ¡Se lo contaré a todos! ¡El tío lo matará! ¡Es terrible cuando está enojado! Solía robar barcos españoles, ¡con él no se hacen bromas!";
		link.l1 = "Está bien, calla, hermosa dama, calla. ¿Quizás veinte mil 'razones' para perdonarlo serán más elocuentes que mis palabras? ¿O debería dárselas a tu tío, como un rescate por una esposa? Después de todo, todos están en la isla, ¿verdad? Mañana podemos organizar otra boda...";
		link.l1.go = "waitress_6";
		break;

	case "waitress_6":
		if (sti(Pchar.money) >= 20000)
			AddMoneyToCharacter(pchar, -20000);
		dialog.text = "No no, capitán, ¡espera! Me has convencido. Idearé algo para que mi tío no se enfade. ¡Adiós! Y adiós a ti, mi corcel de las lejanas llanuras. Búscame la próxima vez que nos visites...";
		link.l1 = "Eso es. Me alegra que estemos de acuerdo. Corre a casa, belleza.";
		link.l1.go = "waitress_7";
		break;

	case "waitress_7":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
		npchar.lifeday = 0;
		sld = characterFromId("Tichingitu");
		sld.dialog.currentnode = "Tichingitu_16";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

	// тавернщик Сен Пьер
	case "tavernkeeper":
		dialog.text = "Bueno, Capitán, ¿estás contento con todo? ¡El mejor ron, costillas de cordero, jamones de cerdo e incluso un excelente vino de mis reservas personales para tu amigo científico! Y, ¡mis felicitaciones para ti y tu hermosa esposa!";
		link.l1 = "¡Gracias! Debo admitir que organizaste todo a la perfección. Espero que tengas suficientes reservas de ron en tus bodegas, la mañana está lejos.";
		link.l1.go = "tavernkeeper_1";
		break;

	case "tavernkeeper_1":
		dialog.text = "No te preocupes por esto, si los barriles muestran el fondo, enviaré a un asistente al almacén del puerto. Diviértete, monsieur, y no te preocupes por nada.";
		link.l1 = "Bien, " + npchar.name + " Entonces iré a mis invitados.";
		link.l1.go = "tavernkeeper_2";
		break;

	case "tavernkeeper_2":
		DialogExit();
		npchar.dialog.currentnode = "tavernkeeper_3";
		break;

	case "tavernkeeper_3":
		dialog.text = "¿Qué desea, capitán? ¿Costillas fritas, jamón ahumado o falda? ¿Quizás vino para su media naranja?";
		link.l1 = "";
		link.l1.go = "tavernkeeper_2";
		break;

	// моряки в таверне Сен Пьер
	case "sailor":
		dialog.text = RandPhraseSimple(LinkRandPhrase("¡A la salud del capitán y su esposa!", "¡Que vivas feliz para siempre, capitán!", "¡Larga vida y felicidad para ambos!"), LinkRandPhrase("¡Hurra por el capitán y su belleza!", "¡Que la suerte siga al capitán y a su cónyuge toda su vida!", "¡Viento en popa a tu vida familiar, capitán!"));
		link.l1 = LinkRandPhrase("¡Gracias!", "¡Gracias!", "¡Salud!");
		link.l1.go = "sailor_1";
		break;

	case "sailor_1":
		DialogExit();
		npchar.dialog.currentnode = "sailor";
		break;

	// босс Ле Франсуа
	case "JanDavid":
		if (sti(pchar.GenQuest.Piratekill) > 20)
		{
			dialog.text = RandPhraseSimple("¿Estás loco? ¿Querías jugar a ser carnicero? Todos los piratas están enfadados contigo, amigo, así que será mejor que dejes este lugar.", "Me parece, camarada, que te has vuelto loco. ¿Querías estirar un poco las manos? Sin ofender, pero no tienes nada que hacer aquí. ¡Lárgate!");
			link.l1 = RandPhraseSimple("Escucha, quiero arreglar la situación...", "Ayúdame a resolver el problema...");
			link.l1.go = "pirate_town";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.LongHappy.Baron"))
		{
			if (!CheckAttribute(npchar, "quest.Baron"))
			{
				dialog.text = "Ah, he estado esperando tu visita, jefe. Jan Svenson advirtió que definitivamente vendrías a verificar cómo van las cosas en Le Francois. Tomé todo en mis propias manos y juro por el trueno, ¡este pueblo vivirá mejor que con el maldito Kindman, que los demonios se diviertan con él en los sótanos más oscuros del infierno!";
				link.l1 = "¿Eres Jean David, verdad? Svenson dijo algo sobre mi parte...";
				link.l1.go = "JanDavid_2";
			}
			else
			{
				dialog.text = TimeGreeting() + " jefe. Todo está bien en Le Francois, como siempre. ¿Por qué has venido? ¿Puedo ayudarte con algo?";
				link.l1 = "Solo pasé a ver cómo van las cosas.";
				link.l1.go = "JanDavid_1";
				if (sti(pchar.questTemp.LongHappy.BaronMoney) > 0)
				{
					link.l2 = "¿Qué hay de mi parte?";
					link.l2.go = "JanDavid_5";
				}
			}
		}
		else
		{
			dialog.text = TimeGreeting() + " camarada.¿Por qué has venido? ¿Puedo ayudarte con algo?";
			link.l1 = "Solo pasé a saludar.";
			link.l1.go = "JanDavid_1";
		}
		break;

	case "JanDavid_1":
		DialogExit();
		npchar.dialog.currentnode = "JanDavid";
		break;

	case "JanDavid_2":
		npchar.quest.Baron = "true";
		dialog.text = "¡A su servicio, jefe! En cuanto a la parte - el quinto de cada mes, se le descontará una parte de las monedas de oro de las hazañas de nuestros muchachos, y esperará por usted tanto como necesite. A partir del próximo mes puede venir por ellas.";
		link.l1 = "¡Bien!";
		link.l1.go = "JanDavid_3";
		break;

	case "JanDavid_3":
		dialog.text = "Y yo me encargaré del resto. Forest Devil dijo que no tendrías tiempo para ocuparte de cosas tan pequeñas como Le Francois...";
		link.l1 = "Te lo dijeron correctamente. Bien, Jean, confío en ti, espero que no me defraudes.";
		link.l1.go = "JanDavid_4";
		break;

	case "JanDavid_4":
		dialog.text = "Todo estará bien, jefe. Todo está bajo control aquí, ja-ja, ¡y que no beba ron hasta el fin de los días si estropeo algo!";
		link.l1 = "Bien, ¡nos vemos!";
		link.l1.go = "JanDavid_1";
		// запуск отчисления доли
		pchar.questTemp.LongHappy.BaronPart = "true";
		pchar.questTemp.LongHappy.BaronMoney = 0;
		break;

	case "JanDavid_5":
		dialog.text = "Esperándote, jefe. Durante este tiempo hemos recogido para ti " + FindRussianMoneyString(sti(pchar.questTemp.LongHappy.BaronMoney)) + ". Tómalo.";
		link.l1 = "Ja, no está mal. Bien hecho, Jean.";
		link.l1.go = "JanDavid_6";
		break;

	case "JanDavid_6":
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.LongHappy.BaronMoney));
		pchar.questTemp.LongHappy.BaronMoney = 0;
		dialog.text = "Hago lo mejor que puedo, jefe. Vuelve el próximo mes o cuando quieras - tu dinero estará seguro conmigo.";
		link.l1 = "Bien, nos vemos, Jean.";
		link.l1.go = "JanDavid_1";
		break;

	case "pirate_town":
		dialog.text = "¿Resolver el problema? ¿Tienes alguna idea de lo que has hecho? De todos modos, tráeme un millón de pesos y persuadiré a los muchachos para que olviden tu fechoría. Si no te gusta la idea, entonces puedes irte al infierno.";
		if (sti(Pchar.money) >= 1000000)
		{
			link.l1 = "Bien, estoy listo para pagar.";
			link.l1.go = "pirate_town_pay";
		}
		link.l2 = "Entendido. Me voy.";
		link.l2.go = "pirate_town_exit";
		break;

	case "pirate_town_exit":
		DialogExit();
		bDisableFastReload = true; // закрыть переход
		pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
		pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
		pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;

	case "pirate_town_pay":
		dialog.text = "¡Bien! Considérate limpio de nuevo. Pero espero que no vuelvas a hacer cosas tan repugnantes.";
		link.l1 = "No lo haré.  Demasiado caro para mí.  Adiós...";
		link.l1.go = "exit";
		AddMoneyToCharacter(pchar, -1000000);
		pchar.GenQuest.Piratekill = 0;
		break;
	}
}
