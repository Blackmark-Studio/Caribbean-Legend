// лидер клана ривадос - Чёрный Эдди
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "¿Qué haces en el territorio de los Rivados, hombre blanco?";
		link.l1 = "Solo estoy conociendo a los lugareños. Disculpa si te he molestado.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "Friend":
		dialog.text = "¡Me alegra saludar a un amigo de los Rivados y también a un buen hombre! Chimiset me contó lo que hiciste por él. Todos los Rivados, incluyéndome a mí, te debemos ahora. Permíteme presentarme - Edward Black, también conocido como Eddie el Negro, el jefe de la banda Rivados.";
		link.l1 = "" + GetFullName(pchar) + " . Aunque creo que Chimiset ya te ha hablado de mí. Te prometió contarte...";
		link.l1.go = "Friend_1";
		break;

	case "Friend_1":
		dialog.text = "Y lo ha hecho. Ahora puedes visitar nuestros barcos libremente. Los guardias no te detendrán y estaremos encantados de verte. Ten cuidado con los Narvales, ya deben haberse enterado de que salvaste a Chimiset, y no les gustará, ya que somos enemigos.";
		link.l1 = "Lo consideraré. ¡Gracias por la cálida bienvenida, Eddie! Ahora, por favor, permíteme hablar con Chimiset.";
		link.l1.go = "Friend_2";
		break;

	case "Friend_2":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocator(npchar, "goto", "goto1", "LSC_EddyStay", -1);
		AddSimpleRumourCityTip("Dicen que eres amigo íntimo de Eddie el Negro, el jefe de Rivados. ¿Cómo lo hiciste?", "LostShipsCity", 10, 1, "LSC", "");
		AddSimpleRumourCityTip("Los Rivados te reclaman como su amigo. ¿Cómo lo hiciste?", "LostShipsCity", 10, 1, "LSC", "");
		AddSimpleRumourCityTip("Dicen que los Narvales tienen un precio por tu cabeza. ¿Tienes miedo?", "LostShipsCity", 10, 1, "LSC", "");
		break;

	// --> информационный блок
	case "Total_info": // стал другом
		if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
		{
			dialog.text = "Hermano blanco? ¿Vivo? ¡Me alegra! Entonces, los Narvales mintieron cuando dijeron a todos que te habías ahogado...";
			link.l1 = "También me alegra verte, Eddie. Los rumores sobre mi muerte han sido grandemente exagerados.";
			link.l1.go = "exit";
			npchar.quest.return_isl = "true";
			break;
		}
		dialog.text = "Me alegra verte, " + pchar.name + "¿Alguna noticia?";
		if (!CheckAttribute(npchar, "quest.natan"))
		{
			link.l1 = "Eddie, ¿conoces a un hombre llamado Nathaniel Hawk? Debe estar aquí, hasta donde sé.";
			link.l1.go = "natan";
		}
		if (!CheckAttribute(npchar, "quest.rivados"))
		{
			link.l2 = "Dime más sobre la banda Rivados.";
			link.l2.go = "rivados";
		}
		link.l9 = "Nada especial, realmente. Solo quería decir hola.";
		link.l9.go = "exit";
		break;

	case "natan":
		dialog.text = "¿Nathaniel Hawk? No, no conozco a este hombre. No está ni en los barcos de los Rivados, ni en el territorio neutral. No puedo decir lo mismo sobre la banda de los Narvales, no los visitamos.";
		link.l1 = "Ya veo...";
		link.l1.go = "exit";
		npchar.quest.natan = "true";
		NextDiag.TempNode = "Total_info";
		break;

	case "rivados":
		dialog.text = "La banda de los Rivados fue fundada hace muchos años. Fue el primer clan en esta Ciudad de Barcos Abandonados. Hace más de cincuenta años, la expedición del Almirante Betancourt navegó hasta aquí desde África Occidental con varios grandes barcos de esclavos. Las bodegas del Tártaro estaban llenas de cientos de esclavos negros destinados a las plantaciones del Caribe. Había un hombre entre esos esclavos llamado Pedro Rivados, algunos sacerdotes portugueses le habían enseñado a leer y escribir. Logró liberar a unas pocas docenas de esclavos de sus grilletes y encabezó un motín. Por desgracia, el resto de los esclavos no se unió a él. La revuelta fue sofocada. Los traficantes de esclavos ataron a Rivados de pies y manos y lo dejaron en la bodega del barco para que muriera de hambre y sed. Unos días después, el tiempo empeoró y la escuadra de Betancourt fue arrastrada por una poderosa tormenta. Días después, tras luchar contra el clima, el 'San Agustín' y el 'Tártaro', los únicos dos barcos aún intactos, quedaron atrapados en el medio de esta Isla. Muchos hombres murieron durante esos eventos, negros y blancos, pero muchos más lograron sobrevivir. Los ex-esclavos comenzaron una nueva vida juntos y se llamaron a sí mismos los Rivados en honor a Pedro Rivados, el libertador.";
		link.l1 = "Una historia muy interesante... ¡Gracias!";
		link.l1.go = "exit";
		npchar.quest.rivados = "true";
		NextDiag.TempNode = "Total_info";
		break;
		// <-- информационный блок

	case "capper":
		dialog.text = "¿Qué necesitas en los territorios de los Rivados, hombre blanco?";
		link.l1 = "Mi nombre es " + GetFullName(pchar) + " y estoy aquí por orden del Almirante Dodson. Debo hablar con Eddie el Negro. Según entiendo, eres tú.";
		link.l1.go = "capper_1";
		break;

	case "capper_1":
		dialog.text = "Sí, soy Edward Black, también conocido como Eddie el Negro. Dime, ¿qué necesita el almirante de mí?";
		link.l1 = "Hay un hombre en el 'Tártaro' llamado Chimiset. El almirante está dispuesto a liberarlo.";
		link.l1.go = "capper_2";
		break;

	case "capper_2":
		dialog.text = "Esta es una muy buena noticia. Chimiset es nuestro líder espiritual, y todos los Rivados lo extrañan. Pero entiendo que el almirante quiere algo a cambio de su libertad, ¿verdad?";
		link.l1 = "Nada. Sólo quiere liberarlo como un gesto de buena voluntad. Pero hay un problema...";
		link.l1.go = "capper_3";
		break;

	case "capper_3":
		dialog.text = "Adelante, hombre blanco.";
		link.l1 = "El ex-contramaestre del almirante, el actual carcelero Chad Kapper, se unió a los Narvales, se volvió un renegado y ahora está fuera del control del almirante. Sabemos que Chad planea matar a Chimiset. El almirante no quiere que eso ocurra. Te ofrecemos una operación conjunta para eliminar al traidor y liberar a tu hombre.";
		link.l1.go = "capper_4";
		break;

	case "capper_4":
		dialog.text = "Tus palabras suenan un poco extrañas, pero continúa. ¿Está Chimiset en problemas?";
		link.l1 = "Sí. Chad planea matarlo. Kapper va a usar a los Narvales para apoderarse de la Ciudad. Tenemos que actuar rápidamente si queremos salvar a Chimiset, ya que Chad no sospecha nada por ahora. El Almirante ha retirado a todos los guardias del 'Tártaro', el paso está libre. Aquí está la llave que abre la puerta dentro de la prisión. Tómala.";
		link.l1.go = "capper_5";
		break;

	case "capper_5":
		RemoveItems(pchar, "key_capper", 1);
		dialog.text = "Isla Justicia";
		link.l1 = "Reúne a tus hombres, ve al Tártaro y libera a Chimiset. Todas las cartas están en tus manos.";
		link.l1.go = "capper_6";
		break;

	case "capper_6":
		dialog.text = "Huele a trampa... ¿Y si hay una emboscada? ¿Y si el almirante decidió atacar a los Rivados? ¿Por qué no se ocupa de Kapper él mismo?";
		link.l1 = "Dodson dijo que te importa la vida de Chimiset... Hizo lo suficiente: aquí está la llave y los guardias se han ido. Solo necesitas entrar, tratar con Chad y liberar a tu hombre. Te doy mi palabra de que no hay trampa. Sí, y una última cosa: el almirante quiere la cabeza de Chad a cambio de la vida y la libertad de Chimiset. ¿Tenemos un acuerdo?";
		link.l1.go = "capper_7";
		break;

	case "capper_7":
		dialog.text = "La vida de Chimiset es valorada por los Rivados más allá de toda medida. Nos moveremos al 'Tártaro' inmediatamente. Pero tú te quedarás aquí como nuestro rehén. ¡Y si hay una emboscada, enfrentarás la ira de los Rivados! \n¡Zikomo! Quédate cerca de la puerta y vigila a nuestro invitado. No lo dejes salir. ¡Yo mismo lideraré el ataque al 'Tártaro'!";
		link.l1 = "Buena suerte, Eddie. ¡Y recuerda: necesito la cabeza de Chad Kapper!";
		link.l1.go = "capper_8";
		break;

	case "capper_8":
		DialogExit();
		chrDisableReloadToLocation = true; // закрыть локацию
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LSC_ZikomoNearDoor", 10.0);
		NextDiag.CurrentNode = "chimiset";
		break;

	case "chimiset":
		dialog.text = "¡Chimiset está libre! No estabas mintiendo, hombre blanco, ¡estoy listo para llamarte amigo de los Rivados!";
		link.l1 = "Me alegro. ¿Chad Kapper está muerto?";
		link.l1.go = "chimiset_1";
		break;

	case "chimiset_1":
		dialog.text = "Tengo que pedirte perdón, amigo blanco: hiciste todo lo que pudiste por nosotros, pero te hemos fallado... ¡Te he fallado! Ese maldito Kapper se escapó. Había dos Narvales con él. Los matamos, pero el sucio carcelero se escapó nadando por la puerta inferior hacia los territorios de los Narvales.";
		link.l1 = "Maldita sea... ¿No sabías que había dos salidas del 'Tártaro'?";
		link.l1.go = "chimiset_2";
		break;

	case "chimiset_2":
		dialog.text = "No lo pensamos. Atacamos desde la entrada principal...";
		link.l1 = "Lástima. Contaba con su cabeza. Qué pena. Ahora seguirá actuando en nuestra contra.";
		link.l1.go = "chimiset_3";
		break;

	case "chimiset_3":
		dialog.text = "Admito mi culpabilidad. Pero no pudimos seguirlo hasta los barcos hostiles. Tendrás nuestra amistad y respeto en lugar de la cabeza de Chad. A partir de ahora, se te permite visitar nuestro territorio libremente. La sabiduría de Chimiset también te servirá bien, habla con él si necesitas algo. Habla con él si necesitas. Además, dile al almirante mis seguridades de que aprecié su acción.";
		link.l1 = "Bien.";
		link.l1.go = "chimiset_4";
		break;

	case "chimiset_4":
		dialog.text = "¡Espera! Hemos perdido a Chad, pero he encontrado unos papeles en su escritorio, que él estaba estudiando cuando llegamos. Aquí están. Tal vez los encuentres útiles, hermano blanco.";
		link.l1 = "¡Ja! Quizás... Chad deposita una gran confianza en el papel...";
		link.l1.go = "chimiset_5";
		break;

	case "chimiset_5":
		dialog.text = "Eres siempre un huésped bienvenido aquí, amigo blanco. Todos los Rivados serán informados sobre ello. ¡Buena suerte!";
		link.l1 = "Lo mismo para ti, Eddie...";
		link.l1.go = "chimiset_6";
		break;

	case "chimiset_6":
		DialogExit();
		LAi_ActorGoToLocator(npchar, "goto", "goto1", "LSC_EddyStay", -1);
		sld = CharacterFromID("Zikomo");
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		LAi_warrior_DialogEnable(sld, true);
		GiveItem2Character(pchar, "letter_chad");
		ChangeItemDescribe("letter_chad", "itmdescr_letter_aeva");
		GiveItem2Character(pchar, "letter_chad_1");
		ChangeItemDescribe("letter_chad_1", "itmdescr_letter_axel");
		pchar.questTemp.LSC.rvd_friend = "true";		   // флаг на проход по кораблям ривадос
		pchar.rvd_friend = true;						   // ривадосы не будут останавливать где просят пароль
		pchar.questTemp.Saga.SharkHunt = "dodson_whiskey"; // к Акуле
		sld = CharacterFromID("Dodson");
		sld.dialog.currentnode = "Chad_escape"; // ноду Акуле
		AddQuestRecord("SharkHunt", "33");
		LocatorReloadEnterDisable("LostShipsCity_town", "reload48", true); // закрыть вход к Дональду Гринспи
		for (i = 7; i <= 12; i++)
		{
			sld = CharacterFromID("RivadosSold_" + i);
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
		}
		for (i = 4; i <= 8; i++)
		{
			sld = CharacterFromID("RivadosProt_" + i);
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
		}
		AddSimpleRumourCityTip("¿Ha oído las últimas noticias? La insolencia de los Rivados está fuera de control, ¡han atacado la prisión del almirante y han liberado a su mago!", "LostShipsCity", 3, 2, "LSC", "");
		AddSimpleRumourCityTip("Piénsalo: ¡esos Rivados engreídos se atrevieron a atacar el Tártaro ! Dicen que el carcelero, Chad Kapper, ha escapado a los Narvales...", "LostShipsCity", 3, 2, "LSC", "");
		AddSimpleRumourCityTip("Esto es el colmo de la desfachatez, ¿no? ¡Atacar una instalación militar del almirante! Sí, parece que Eddie el Negro se está haciendo más fuerte...", "LostShipsCity", 3, 2, "LSC", "");
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
