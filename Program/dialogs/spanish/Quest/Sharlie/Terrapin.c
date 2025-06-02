// НПС по квесту Суп из черепахи
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "¿Qué necesitas?";
		link.l1 = "No, nada.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	// денщик Фокса - Бенджамин Джонс
	case "BenjaminJons":
		if (CheckAttribute(PChar, "questTemp.Terrapin.Benjamin") && pchar.questTemp.Terrapin == "baster")
		{
			dialog.text = "El señor coronel está en el campo realizando un ejercicio militar en este momento. ¿Qué quieres de él, capitán?";
			link.l1 = "Esta vez, Ben, eres tú a quien necesito. Tengo malas noticias sobre tu hermana Molly. Esa hermosa chica aparentemente está en serios problemas. Ha sido capturada por piratas de Tortuga. Necesita ayuda y ha pedido que te advierta. El hombre que se encargó de transmitir el mensaje fue asesinado, pero antes de su muerte, logró contarme sobre tu hermana.";
			link.l1.go = "sister";
			break;
		}
		sld = characterFromId("Fox");
		if (sld.location == pchar.location)
		{
			dialog.text = "Si te diriges al Coronel Fox, entonces da media vuelta de 360 grados y márchate. No está recibiendo visitas.";
			link.l1 = "Muy bien entonces.";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "El coronel no está aquí. Vuelve más tarde.";
			link.l1 = "Está bien...";
			link.l1.go = "exit";
		}
		NextDiag.TempNode = "BenjaminJons";
		break;

	case "sister":
		dialog.text = "¡Ja! Eres el primer hombre que ha llamado 'hermosa' a mi hermana. Dios le dio el cuerpo de un granadero y el cuerno de Jericó en lugar de una voz. Nuestra Molly puede defenderse sola. \nPero la creatividad de nuestro Señor no se detuvo solo en todo lo que está debajo de su barbilla. No no, lo mejor que hizo fue poner la cara peluda y llena de viruelas de nuestro difunto padre sobre sus pechos. Y debo decir, señor, que el rostro de mi viejo solía hacer desmayar a los caballos.";
		link.l1 = "Veo que no estás particularmente molesto...";
		link.l1.go = "sister_1";
		break;

	case "sister_1":
		dialog.text = "¿Y por qué iba a aparecer en Tortuga? Molly es una sirvienta de Catherine Fox, la hija de nuestro valiente coronel. Catherine venía de Europa para visitar a su padre en su cumpleaños. Pero la escuadra con la que navegaba su barco se ha retrasado.\nSi quieres ver a la verdadera Molly Jones y a su señora, que por cierto es muy hermosa, ven aquí en un mes. Ni un día antes.";
		link.l1 = "¿Resulta que tu hermana Molly Jones ha estado sirviendo a la señora Fox y en este momento reside al otro lado del Atlántico?";
		link.l1.go = "sister_2";
		break;

	case "sister_2":
		dialog.text = "¡Exactamente así! El último mensajero nos informó que un escuadrón naval enviado por el mismo Lord Protector Cromwell debía partir de Londres hace solo un mes. El bergantín 'Albatross' con Catherine a bordo iba a acompañarlos. Sabremos si es realmente así del próximo barco de correo. Aunque los barcos aún no han llegado y el coronel había prohibido estrictamente que el 'Albatross' navegara solo.\n¿Sabías que su amada esposa murió durante un ataque de corsarios franceses? No fue fácil para el coronel y todavía teme los peligros del alta mar... Así que no puedo ayudarte con Molly Jones, ¡capitán! ¡Hay muchas chicas colonas llamadas Molly! Además, tener el apellido Jones en Gran Bretaña es como no tener apellido en absoluto.\n¡Todos los lobos de mar en Antigua me conocen a mí y a mi comandante! No me sorprende que alguna pobre chica que se metió en problemas quiera mi ayuda. Me gustaría, pero no tengo moneda para un rescate. El coronel me debe tres meses de salario, mi paga junto con la de todos los demás llega con el 'Albatross'.";
		link.l1 = "Aparentemente estoy equivocado entonces. Pero gracias de todos modos por la aclaración.";
		link.l1.go = "sister_3";
		break;

	case "sister_3":
		dialog.text = "Para nada, capitán.";
		link.l1 = "...";
		link.l1.go = "sister_4";
		break;

	case "sister_4":
		DialogExit();
		AddQuestRecord("Terrapin", "3");
		pchar.questTemp.Terrapin.Catherina = "take"; // возможен вариант с Кати
		DeleteAttribute(pchar, "questTemp.Terrapin.Benjamin");
		break;

	// Робер Мартэн
	case "Rober":
		PlaySound("Voice\Spanish\sharlie\Rober Marten-01.wav");
		dialog.text = "¿Qué quieres?! No estoy de humor para charlas sin sentido.";
		if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "rober")
		{
			link.l1 = "Tengo un negocio para ti, capitán. Veo que no estás de buen humor y tal vez mi propuesta te alegre un poco.";
			link.l1.go = "rober_1";
		}
		else
		{
			link.l1 = "Cálmate, bebe un poco de ron. Mi error, camarada. Lo siento.";
			link.l1.go = "exit";
		}
		NextDiag.TempNode = "Rober";
		break;

	case "rober_1":
		DelMapQuestMarkCity("BasTer");
		pchar.quest.Terrapin_LateBaster.over = "yes"; // снять таймер
		dialog.text = "¡El sonido es bastante atractivo! Y tu cara parece que la he visto en algún lugar antes... Simplemente no puedo recordar dónde te vi. ¡Cuéntamelo!";
		link.l1 = "Estoy al tanto de tus negocios con Thibaut... ¡Relájate, camarada! No tienes que temerme. Tengo un trato que proponerte.";
		link.l1.go = "rober_2";
		break;

	case "rober_2":
		dialog.text = "¡Maldita sea al infierno! ¡Que le den a ese cerdo borracho!... No logré...";
		link.l1 = "Tienes razón. Tu marinero tenía una boca grande, pero sus rumores no han llegado más allá de mí. Y esos rumores no irán más lejos ya que eres tú quien se ha encargado de eso, ¿no es así?";
		link.l1.go = "rober_3";
		break;

	case "rober_3":
		dialog.text = "¡Caramba! ¡Ahora te reconozco! ¡Eres el hombre que hizo un desastre con el Coronel Doiley y se apoderó de toda su isla! Estuviste involucrado en algún gran negocio con la Compañía Holandesa de las Indias Occidentales, te codeas con un barón de Tierra Firme occidental... Tu nombre es... " + GetFullName(pchar) + ", ¿verdad?";
		link.l1 = "Posees información bastante precisa. Sí, soy yo. Pero, ¿podrías calmarte un segundo, Robert?";
		link.l1.go = "rober_4";
		break;

	case "rober_4":
		PlaySound("Voice\Spanish\sharlie\Rober Marten-02.wav");
		dialog.text = "¡Argh! Bueno, ¿cómo puedo calmarme cuando uno de los perros de mar más famosos del archipiélago se ha interesado en mí y no solo eso, ¡también ha descubierto mi negocio! ¿Qué demonios se me ocurrió atacar este bergantín? ¿Qué quieres de mí?";
		link.l1 = "Cierra la boca y escúchame. Me parece que ambos queremos la cabeza de Levasseur en un plato. Ese fanfarrón pomposo se ha crecido demasiado y ha enfurecido a gente seria. Tengo la intención de alterar el equilibrio de poder en la isla y poner a de Poincy en su lugar, pero no quiero derramar sangre innecesaria de ningún hombre de mi tierra natal, especialmente por algún ladrón sucio. Puedes ayudarme. Y yo puedo ayudarte a ti y a Thibaut a conservar vuestros privilegios.";
		link.l1.go = "rober_5";
		break;

	case "rober_5":
		dialog.text = "¡Espera, espera! ¡No puedo creer mis oídos! La fortuna me sonríe hoy. Tienes razón, compartimos objetivos. Contigo, puede ponerse mucho más interesante... Thibaut es un buen espadachín, pero no tiene las agallas para cortarle el cuello a su tío... Pero un tiburón astuto como tú podría hacerlo. Tu fama es bien conocida\nNo necesito tus garantías, pero te ayudaré a cambio de la chica. La necesito como mi rehén hasta que termine mis asuntos en el Caribe. Pronto, fragatas inglesas comenzarán a acosarme. ¡Qué demonios me llevó a atacar ese bergantín! Parecía una presa tan fácil separada de la escuadra...";
		link.l1 = "¿Qué tenía de especial ella? ¿La chica que estabas ocultando de Levasseur?";
		link.l1.go = "rober_6";
		break;

	case "rober_6":
		dialog.text = "Sí. Debes convencer a Thibaut, para que deje ir a la chica. Le pedí que la cuidara mientras averiguaba quién demonios era, pero esta 'Señorita Jones', o como sea que se llame, le ha dado completamente la vuelta a la cabeza y ahora ¡Henry incluso la está escondiendo de mí! Trae a esa sirena hechicera a mí y organizaré una reunión para ti con Levasseur fuera de la ciudad. En ese momento, tendrás la oportunidad de emboscarlo. Estaré esperando en la Playa del Ojo de Pez.";
		link.l1 = "Trato hecho. Ahora dime cómo atrapar a Thibaut.";
		link.l1.go = "rober_7";
		break;

	case "rober_7":
		dialog.text = "La gente en la taberna puede mostrarte el camino a su casa. Henri es bastante notable. Amenázalo con exponerlo y haz que traiga a la chica a mí. Ese mismo día le haré saber a Levasseur que su sobrino esconde una rara belleza en la mazmorra de la ciudad\nMi mensajero te encontrará en la taberna. Después de que falle en encontrar a Henri, el gobernador irá a la mazmorra con un pequeño escuadrón y tendrás una buena oportunidad de charlar con él.";
		link.l1 = "¿Dónde debo entregar a la chica?";
		link.l1.go = "rober_8";
		break;

	case "rober_8":
		dialog.text = "Dile que la entregue él mismo a la playa. Le diré un par de cosas mientras estoy allí...";
		link.l1 = "De acuerdo. Considéralo un trato. ¡Nos vemos en Tortuga!";
		link.l1.go = "rober_9";
		break;

	case "rober_9":
		dialog.text = "Si todo sale según lo planeado, nunca nos volveremos a ver. Al menos eso espero. ¡Adiós!";
		link.l1 = "Entendido.";
		link.l1.go = "rober_10";
		break;

	case "rober_10":
		chrDisableReloadToLocation = true; // закрыть локацию
		DialogExit();
		LAi_SetActorType(npchar);
		ChangeCharacterAddressGroup(npchar, "Baster_tavern", "goto", "goto2");
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
		if (CheckAttribute(pchar, "questTemp.Terrapin.Catherina"))
			AddQuestRecord("Terrapin", "6");
		else
			AddQuestRecord("Terrapin", "5");
		pchar.questTemp.Terrapin = "tortuga";
		// создаем Тибо
		float fMft = MOD_SKILL_ENEMY_RATE / 10;
		sld = GetCharacter(NPC_GenerateCharacter("Tibo", "Tibo", "man", "man", 35, FRANCE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 35, 100, 100, "blade_18", "pistol4", "bullet", 250);
		GiveItem2Character(sld, "cirass7");
		EquipCharacterbyItem(sld, "cirass7");
		sld.name = "Henry";
		sld.lastname = "Thibaut";
		sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
		sld.dialog.currentnode = "tibo";
		sld.greeting = "Tibo";
		sld.SaveItemsForDead = true;
		sld.DontClearDead = true;
		TakeNItems(sld, "potion2", 8);
		TakeNItems(sld, "potion3", 5);
		SetCharacterPerk(sld, "Energaiser");
		SetCharacterPerk(sld, "BasicDefense");
		SetCharacterPerk(sld, "BasicDefense");
		SetCharacterPerk(sld, "AdvancedDefense");
		SetCharacterPerk(sld, "CriticalHit");
		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "Sliding");
		SetCharacterPerk(sld, "BladeDancer");
		SetCharacterPerk(sld, "SwordplayProfessional");
		SetCharacterPerk(sld, "Gunman");
		SetCharacterPerk(sld, "GunProfessional");
		sld.MultiFighter = 1.0 + fMft; // мультифайтер
		if (bImCasual)
		{
			NewGameTip("Modo exploración: se duplica la duración de las misiones");
			SetFunctionTimerCondition("Terrapin_LateTortuga", 0, 0, 40, false); // таймер
		}
		else
			SetFunctionTimerCondition("Terrapin_LateTortuga", 0, 0, 20, false); // таймер
		SetFunctionLocationCondition("Tonzag_AtTortuga", "Tortuga_town", false);
		break;

	case "rober_abordage":
		dialog.text = "¡Argh! No lo vi venir... Has venido por mi alma, ¿verdad, compañero? ¡Hice todo según lo acordado! ¿Qué demonios?!";
		link.l1 = "Tienes una sentencia sobre ti, Robert. La sentencia me fue dada para ejecutar. Así que estoy cumpliendo con mi asignación.";
		link.l1.go = "rober_abordage_1";
		break;

	case "rober_abordage_1":
		dialog.text = "¡Demonio! ¡Esto es imposible! ¡No pudo haberlo descubierto todo tan rápido! ¿Y cómo siquiera lo descubrió?";
		link.l1 = "¿Te refieres a Fox? No. Él no me envió. El coronel aún ni siquiera sabe que cortaste a su hija. Tu viejo camarada Henry Thibaut es el que quiere verte muerto. Él me contrató.";
		link.l1.go = "rober_abordage_2";
		break;

	case "rober_abordage_2":
		dialog.text = "¡Ese maldito catamita! Debería haberlo echado a los cangrejos mientras estaba en el 'Voltigeur'... ¿Cuánto te prometió ese bastardo?";
		link.l1 = "No es todos los días que un hombre llega a conocer el precio por su cabeza, ¿verdad, Robert? Thibaut te valoró en un cuarto de millón, pero lo convencí de que vales más. Valés trescientos mil pesos de plata, amigo mío. ¿No te alegra?";
		link.l1.go = "rober_abordage_3";
		break;

	case "rober_abordage_3":
		dialog.text = "Espera un segundo... ¡Hagamos un trato! ¡Te pagaré más!";
		link.l1 = "¿Con qué dinero, Robert? Estoy absolutamente seguro de que estás mintiendo. No tienes tanto dinero como Henry me prometió. Y eso no es lo principal de todos modos. Si no fuera por un hecho, habría rechazado su propuesta de cazarte y acabar con tus sucios asuntos con Thibaut.";
		link.l1.go = "rober_abordage_4";
		break;

	case "rober_abordage_4":
		dialog.text = "¿Qué hecho es ese?";
		link.l1 = "Mataste a Catherine Fox. La culpa de esa pobre chica no era más que haber nacido hija del Coronel Fox. ¡Odio a los cobardes despreciables como tú que condenan a muerte a mujeres indefensas! No voy a hacer ningún trato contigo. Ni siquiera lo consideraré. No malgastes tu aliento.";
		link.l1.go = "rober_abordage_5";
		break;

	case "rober_abordage_5":
		PlaySound("Voice\Spanish\sharlie\Rober Marten-03.wav");
		dialog.text = "¡Maldita sea! ¿Qué más podría hacer?! ¡No podía dejarla vivir y esconderla eternamente en el barco! ¿Y tú quién eres... bribón, bastardo, asesino, para darme lecciones de moral? ¡Mírate a ti mismo! ¡A tus 'métodos'! ¡No eres mejor que yo!";
		link.l1 = "Basta. ¡Martene, saca tu espada! Es hora de que terminemos esto.";
		link.l1.go = "rober_abordage_6";
		break;

	case "rober_abordage_6":
		dialog.text = "¡Te veré en el infierno!";
		link.l1 = "...";
		link.l1.go = "rober_abordage_7";
		break;

	case "rober_abordage_7":
		DialogExit();
		QuestAboardCabinDialogFree();
		LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	// Тибо, вариант без Кати
	case "tibo":
		pchar.quest.Terrapin_LateTortuga.over = "yes"; // снять таймер
		PlaySound("Voice\Spanish\sharlie\Henry Thibault-02.wav");
		dialog.text = "¡Señor, no recuerdo haberlo invitado aquí!";
		link.l1 = TimeGreeting() + ", Monsieur Thibaut. Estoy aquí en nombre de un hombre que usted conoce, el Capitán Robert Martene.";
		link.l1.go = "tibo_1";
		break;

	case "tibo_1":
		dialog.text = "¿Hm. ¿Y? ¿Entonces?";
		link.l1 = "El Capitán Martene solicita el placer de tu compañía ahora mismo en la Playa Fisheye. Pero no solo. También agradecería ver a Molly Jones en tu compañía. ¿Entiendes lo que quiero decir?";
		link.l1.go = "tibo_2";
		break;

	case "tibo_2":
		PlaySound("Voice\Spanish\sharlie\Henry Thibault-01.wav");
		dialog.text = "¡Ay, señor, no lo sé! Nunca he oído hablar de ninguna Molly Jones y Robert nunca ha tenido necesidad de enviarme un... plenipotenciario a quien nunca antes había visto. Para su información, monsieur, soy el segundo hombre en esta ciudad después del gobernador, señor. Quiero que lo recuerde...";
		link.l1 = "La vida es una bestia impredecible, Henry... Ahora mismo eres el segundo hombre en la isla y en un par de horas podrías estar encadenado en las casamatas... Todo por la vida de alguien que no te daría ni un solo peso. Has desobedecido la orden de tu tío, ¿no es así, monsieur Thibaut? ¿Qué es más importante para ti: una chica lasciva o tu vida?";
		link.l1.go = "tibo_3";
		break;

	case "tibo_3":
		dialog.text = "¡Por qué tú... Mientes! ¡Estás hablando tonterías!";
		link.l1 = "Tú, al igual que cualquiera, debes saber cuán ardiente puede ser el temperamento de tu tío. Levasseur descubrirá que estás escondiendo a la chica antes de que se ponga el sol. No me preguntes cómo lo supo Robert, solo escucha mis palabras: está muerto de miedo y listo para zarpar de inmediato. Ni siquiera se atrevió a entrar en el pueblo y me pagó una fuerte suma para entregarte este mensaje.";
		link.l1.go = "tibo_4";
		break;

	case "tibo_4":
		dialog.text = "Maldita sea... ¡No puede ser!";
		link.l1 = "Depende de usted, señor. Martene no le esperará más de dos horas. Valora su cabeza sobre sus propios hombros. Es solo como un signo de su amistad que todavía está merodeando por la costa de Tortuga y no escondido en algún lugar con los holandeses.";
		link.l1.go = "tibo_5";
		break;

	case "tibo_5":
		dialog.text = "¡Caramba! ¿Cómo pudo mi tío averiguarlo?";
		link.l1 = "Lenguas, Henry. Lenguas que parlotean. Incluso yo sé que tú y Robert agarraron a la belleza que salió del bergantín inglés capturado por tu compañero. La escondieron de Levasseur...tsk tsk. ¿Realmente dudas que soy el único informado sobre esta historia?";
		link.l1.go = "tibo_6";
		break;

	case "tibo_6":
		dialog.text = "Parece que está diciendo la verdad, señor. Dile a Martene...";
		link.l1 = "No creo que entiendas, Henry. Martene no va a esperarte. Tu única esperanza es sacar a esa chica de aquí, la razón por la que tanto tú como Robert tienen la soga al cuello. Corre hacia donde la escondes, tómala por sus bonitas manitas y llévala al Voltigeur. Encuéntrala rápido, y tráela aún más rápido. Tu tío no oirá ni una palabra de esto de mi parte.";
		link.l1.go = "tibo_7";
		break;

	case "tibo_7":
		dialog.text = "Está bien. Entonces lo haremos. ¡Gracias por su benevolencia, señor!";
		link.l1 = "No hay necesidad de agradecerme, monsieur. Mi trabajo está pagado... Solo quiero que salgas del lío antes de que estés cocido.";
		link.l1.go = "tibo_8";
		break;

	case "tibo_8":
		chrDisableReloadToLocation = true; // закрыть локацию
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
		pchar.quest.Terrapin_wait.win_condition.l1 = "Timer";
		pchar.quest.Terrapin_wait.win_condition.l1.date.hour = sti(GetTime() + 3);
		pchar.quest.Terrapin_wait.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
		pchar.quest.Terrapin_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
		pchar.quest.Terrapin_wait.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
		pchar.quest.Terrapin_wait.win_condition.l2 = "location";
		pchar.quest.Terrapin_wait.win_condition.l2.location = "Tortuga_tavern";
		pchar.quest.Terrapin_wait.function = "Terrapin_SetEnvoy";
		pchar.questTemp.Terrapin = "cave";
		AddQuestRecord("Terrapin", "8");
		SetFunctionTimerCondition("Terrapin_ReturnTibo", 0, 0, 10, false);
		if (bImCasual)
		{
			NewGameTip("Modo exploración: se duplica la duración de las misiones");
			SetFunctionTimerCondition("Terrapin_LateDungeon", 0, 0, 4, false);
		}
		else
			SetFunctionTimerCondition("Terrapin_LateDungeon", 0, 0, 2, false);
		break;

	// вариант с Кати
	case "tibo_9":
		pchar.quest.Terrapin_LateTortuga.over = "yes"; // снять таймер
		PlaySound("Voice\Spanish\sharlie\Henry Thibault-02.wav");
		dialog.text = "¡Señor, no recuerdo haberlo invitado aquí!.";
		link.l1 = TimeGreeting() + ", Monsieur Thibaut. He llegado de parte de un hombre que usted conoce. Su nombre es el Capitán Robert Martene.";
		link.l1.go = "tibo_10";
		break;

	case "tibo_10":
		dialog.text = "¿Hm. Y? ¿Entonces?";
		link.l1 = "El Capitán Martene solicita el placer de tu compañía en este momento en la Playa Ojo de Pez. Pero no solo. También agradecería ver a Molly Jones en tu compañía. ¿Entiendes lo que quiero decir?";
		link.l1.go = "tibo_11";
		break;

	case "tibo_11":
		dialog.text = "Ay, señor, no lo hago.";
		link.l1 = "Eso es lo que esperaba que dijeras. Por supuesto, dudo que hayas sido presentado previamente a la hija del Coronel Fox, conoces al Coronel Fox, por supuesto, comandante de los notoriamente temidos Zorros del Mar... ¿el terror de los enemigos de Inglaterra en el Caribe? ¡Tú y Robert habéis alborotado tal avispero que es un milagro que aún no os hayan picado! La chica Molly Jones que capturaste del bergantín inglés, que has estado ocultando de Levasseur, ¡es la hija del Coronel Fox, Catherine Fox!";
		link.l1.go = "tibo_12";
		break;

	case "tibo_12":
		dialog.text = "¿Q-quién?";
		link.l1 = "Te has puesto bastante pálido, señor. Ahora escúchame atentamente, Henry, y presta atención: tú y tu compañero Robert están hasta el cuello de mierda. En cualquier momento, el escuadrón naval de Cromwell llegará al Caribe. Estarán cazándote. Su buque insignia, por sí solo, es capaz de convertir a tu alabado La Roche y a su tripulación en astillas y carne picada en un par de horas. ¿Qué opinas? ¿Valió la pena el ataque a ese bergantín inglés y el cautiverio de la hija de Fox?";
		link.l1.go = "tibo_13";
		break;

	case "tibo_13":
		dialog.text = "";
		link.l1 = "Pero eso no es todo. Tus artimañas se han hecho conocidas no solo por mí. Tu querido tío, el gobernador, descubrirá que estás transgrediendo sus estrictas órdenes y has ocultado a una muchacha de él, que el viejo lujurioso definitivamente habría querido para sí mismo. ¿Qué piensas, Henry? ¿Qué te hará tu tío? Debes saber mejor que nadie lo fogoso que es su temperamento...";
		link.l1.go = "tibo_14";
		break;

	case "tibo_14":
		dialog.text = "¡Todas mentiras!";
		link.l1 = "¿Es así? Mi querido Henry, puedes preguntarle a tu amigo Martene. Él fue quien me envió. Levasseur descubrirá que estás escondiendo a la chica antes de que se ponga el sol. No me preguntes cómo Robert lo averiguó, solo escucha mis palabras: está cagado de miedo y listo para levar anclas y zarpar de inmediato. Ni siquiera se atrevió a entrar en la ciudad. Por eso me pidió que te entregara este mensaje.";
		link.l1.go = "tibo_15";
		break;

	case "tibo_15":
		dialog.text = "";
		link.l1 = "Martene no te esperará más de dos horas. Valora mucho su propia cabeza. Es solo como una señal de tu amistad que todavía está rondando las costas de Tortuga y no escondiéndose en algún lugar con los holandeses. Sin embargo, ese pobre diablo Robert ni siquiera sospecha quién es realmente Molly Jones. ¡Sabes, ustedes dos realmente me asombran con su increíble ignorancia de la moda y apariencia femeninas! ¡Ni siquiera podríais distinguir a una dama noble de su sirvienta!";
		link.l1.go = "tibo_16";
		break;

	case "tibo_16":
		dialog.text = "¿Qué quieres?";
		link.l1 = "¡Por fin algunas palabras sabias del joven advenedizo! Muy bien, Thibaut: ve donde la estás escondiendo ahora mismo, tómala suavemente por sus manos blancas como el lirio, y camina rápidamente con ella hasta la Playa Fisheye donde está el Voltigeur de Martene. Dile que tus planes han cambiado...";
		link.l1.go = "tibo_17";
		break;

	case "tibo_17":
		dialog.text = "";
		link.l1 = "Martene debe cumplir su promesa conmigo, ni siquiera debería intentar llevarse a la chica en su propio barco. Ella se quedará en la playa y me esperará. Dile a Robert que si no cumple con sus obligaciones, o se lleva a Catherine, o si un solo cabello se cae de su bonita cabecita, pasaré el resto de mi vida encontrándola. Y cuando la encuentre, la entregaré al Coronel Fox... viva. Pero para vosotros dos... os traeré de vuelta en pedazos. Sí, por cierto, eso te incluye a ti también, Thibaut.";
		link.l1.go = "tibo_18";
		break;

	case "tibo_18":
		dialog.text = "";
		link.l1 = "Quién soy y cuáles son mis oportunidades, puedes preguntarle a Robert. Él está bien informado. Si ambos hacen lo que dije, entonces todos ganamos. Robert podrá continuar su negocio pirata y tú conservarás todos tus privilegios y recibirás la herencia de tu querido viejo tío cuando estire la pata. En cuanto a mí... tampoco saldré perdiendo. ¿Está todo claro?";
		link.l1.go = "tibo_19";
		break;

	case "tibo_19":
		PlaySound("Voice\Spanish\sharlie\Henry Thibault-03.wav");
		dialog.text = "¡Preferiría arder en el fuego del infierno, antes que jugar a ser un títere para tí! ¡Sin vergüenza!... " + GetFullName(pchar) + "¿Cómo no te reconocí desde el principio? ¡Butcher! ¡No planeas dejarme a mí o a Robert con vida! ¡Tus 'métodos' son bien conocidos! ¡No hay manera de que entregue a Molly... o Catherine, para el caso, a una escoria como tú! ¡No saldrás vivo de Tortuga, cabrón!";
		link.l1 = "...";
		link.l1.go = "tibo_20";
		break;

	case "tibo_20":
		dialog.text = "";
		link.l1 = "¡Detente, cobarde!";
		link.l1.go = "tibo_21"; // patch
		break;

	case "tibo_21":
		chrDisableReloadToLocation = true; // закрыть локацию
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload_window", "none", "", "", "Terrapin_LevasserRoomEnter", 5); // patch
		LAi_SetActorType(pchar);
		LAi_ActorTurnToLocator(pchar, "reload", "reload_window");
		LAi_RemoveLoginTime(npchar);
		break;

	case "tibo_22":
		pchar.quest.Terrapin_TiboCallOver.over = "yes"; // снять прерывание
		pchar.quest.Terrapin_tibo_call.over = "yes";	// снять прерывание
		PlaySound("Voice\Spanish\sharlie\Henry Thibault-04.wav");
		dialog.text = "¡Bueno, finalmente! Capitán " + GetFullName(pchar) + ", me complace mucho que hayas venido. Entra, siéntate. ¿Algo de beber? Tengo una propuesta de negocio bastante lucrativa para ti, amigo mío...";
		link.l1 = "Bueno, parece que estás de buenos ánimos hoy, Monsieur Thibaut... No nos quedemos aquí sentados. Vayamos directo al meollo del asunto.";
		link.l1.go = "tibo_23";
		break;

	case "tibo_23":
		dialog.text = "La propuesta concierne a mi antiguo amigo y compañero que conoces como Robert Martene, antiguo capitán del galeón 'Voltigeur'...";
		link.l1 = "Entonces, ¿tú y Robert ya no sois compañeros? Un desarrollo fascinante.";
		link.l1.go = "tibo_24";
		break;

	case "tibo_24":
		dialog.text = "Capitán, por favor, escuche mis motivos para buscar su ayuda y todo quedará claro. Como usted mismo sabe, Martene se enfrentó a un bergantín inglés y capturó como prisionera a una inglesa, una sirvienta conocida como Molly Jones, la razón por la que todo este lío se desató.";
		link.l1 = "Por supuesto, lo sé. Según entiendo, ¿has cumplido mis recomendaciones y llevado a la chica al barco de Martene?";
		link.l1.go = "tibo_25";
		break;

	case "tibo_25":
		dialog.text = "Sí, lo hice. Pero lo lamento cada día. Déjame decirte que Molly es una chica muy encantadora y hermosa, nunca había conocido a nadie como ella antes. Debo admitir que me enamoré de ella. ¡A ella también le gustaba yo, lo dijo ella misma! No podía dejar que mi tío se la llevara\nCuando la escoltaba al 'Voltigeur', esperaba que mi tío se calmara tan pronto como supiera que nadie le está escondiendo chicas, el viejo lujurioso. Luego Robert la llevaría de vuelta a Tortuga, para que pudiera trasladarla a mi lugar con seguridad. De todos modos, ese fue el acuerdo que hice con Martene. Pero resultó de manera diferente\nCuando supe que mi tío había sido asesinado, no había razón para esconder a Molly, así que esperé pacientemente a que llegara el 'Voltigeur' con Molly a bordo.";
		link.l1 = "¿Llegó ella?";
		link.l1.go = "tibo_26";
		break;

	case "tibo_26":
		dialog.text = "Sí. Desafortunadamente, Molly no estaba en el barco. Robert estaba conmocionado, como si se hubiera enfrentado al mismo Lucifer. Durante su efímera expedición, de alguna manera descubrió un detalle terrible: la chica, Molly, no era en absoluto Molly Jones, ¡sino Catherine Fox! ¡La misma hija del Coronel Fox, comandante de los Zorros del Mar, el regimiento de marinos de élite ingleses! ¡Sabes lo que eso significa!";
		link.l1 = "¡Malditos sean mis ojos, qué tal! Sin duda entonces, Robert tiene algo de qué temer. Pero ¿cómo pudo haber sucedido así?";
		link.l1.go = "tibo_27";
		break;

	case "tibo_27":
		dialog.text = "Cuando Catherine fue llevada al cautiverio, intencionadamente ocultó su identidad haciéndose pasar por Molly Jones, una sirvienta que murió durante el abordaje. Temía que Martene descubriera quién era realmente. Y logró engañarlo. Pero durante el último viaje, Robert de algún modo descubrió quién es ella realmente. Dijo que encontró algunas cartas suyas, o documentos...";
		link.l1 = "¿Y dónde está la chica ahora si no se embarcó en el 'Voltigeur'?";
		link.l1.go = "tibo_28";
		break;

	case "tibo_28":
		dialog.text = "Está muerta. Asustado por el inminente castigo de Fox por atacar al bergantín inglés, Martene decidió esconder la única prueba restante en el agua. Ella era la última testigo de su ataque al 'Albatros'.";
		link.l1 = "Entonces bien podría haber asesinado a todos sus marineros... Como Fernand Luc. De lo contrario, un día se emborracharán y abrirán demasiado la boca en la taberna...";
		link.l1.go = "tibo_29";
		break;

	case "tibo_29":
		dialog.text = "Siente que toda su tripulación le ha jurado lealtad con sangre. Tal vez tenga razón en parte. ¡Pero conozco al Coronel Fox! ¡Seguirá escarbando hasta el fin de sus días para averiguar quién secuestró a su hija!";
		link.l1 = "No lo dudo. Especialmente después de que un pirata francés mató a su esposa. Ahora su hija también... Por cierto, ¿está usted absolutamente seguro, monsieur, de que Catherine está realmente muerta? Tal vez Robert la escondió de usted en algún lugar.";
		link.l1.go = "tibo_30";
		break;

	case "tibo_30":
		dialog.text = "Estoy seguro. Hablé con un marinero del 'Voltigeur'. Le creí. Lo vio con sus propios ojos, cómo le cortaron el cuello a la chica y luego le ataron una bala de cañón a los pies y la lanzaron por la borda.";
		link.l1 = "¡Dios en el cielo! Esa pobre mujer... ¿qué quieres de mí, Henry?";
		link.l1.go = "tibo_31";
		break;

	case "tibo_31":
		dialog.text = "No puedo dormir por las noches desde aquel día. Veo a Molly todo el tiempo ante mis ojos... Catherine, más bien. La conduje a su muerte, " + GetFullName(pchar) + "¡No puedo perdonarme por eso! Además, no me hago ilusiones sobre Fox. Ese hombre no es complaciente y no creo ni que duerma. Tarde o temprano, seguirá el rastro de Martene, hará que alguien hable, y cuando descubra quién mató a su hija, se desatará el infierno. Le irá mal a cualquiera que, de una u otra manera, esté relacionado con toda la historia.";
		link.l1 = "Eso me incluye a mí.";
		link.l1.go = "tibo_32";
		break;

	case "tibo_32":
		dialog.text = "Aye, yo también. Por eso quiero que encuentres a Martene antes que Fox. Encuentra a ese bastardo y mátalo. Y hazlo sufrir primero si puedes. Por la pobre Catherine. Cuando lo hayas hecho, corta ese anillo gordo que lleva en la mano con el dedo dentro y tráemelo como prueba\nConozco bien su dedo torcido y ese anillo. Si haces eso, te pagaré un cuarto de millón en plata.";
		link.l1 = "¿Parece que has recibido una gran herencia de tu querido tío que descansa en paz, eh? Dime, Henry, ¿por qué decidiste pedirme ayuda con este asunto?";
		link.l1.go = "tibo_33";
		break;

	case "tibo_33":
		dialog.text = "Porque también he aprendido algunas cosas sobre ti, " + GetFullName(pchar) + ". Fue fácil, eres un hombre famoso. Sin embargo, se desconoce para quién realmente trabajas, ya sea para de Poincy, para los holandeses, para los ingleses o para el barón Jan Svenson... Pero una cosa está clara: tomas trabajos delicados y discretos y los llevas a cabo. Luego te pagan generosamente por ellos. Y lo mejor de todo es que no estás conectado con los españoles\nDespués de todo, también participaste en los eventos tras los cuales heredé la fortuna de mi tío. No lo niegues... Un cuarto de millón es buen dinero. Te diré dónde encontrar a Martene. Solo tienes que interceptar su barco y abordarlo.";
		link.l1 = "Otros cien mil y me encargaré de Martene por ti.";
		link.l1.go = "tibo_34";
		link.l2 = "¡Ay, Monsieur Thibaut, tendrás que resolver tu problema con Martene y el Coronel Fox sin mi participación! Yo, por mi parte, te prometo que no enviaré ninguna palabra al coronel sobre el destino de su hija y aquellos que son culpables de su muerte. Todo lo mejor, señor.";
		link.l2.go = "tibo_exit";
		break;

	case "tibo_exit":
		DialogExit();
		AddQuestRecord("Sharlie", "26");
		NextDiag.CurrentNode = "tibo_over";
		break;

	case "tibo_34":
		dialog.text = "Señor, tema a Dios... ¡No tengo millones guardados en cofres del tesoro, créame! Entiendo que sus servicios cuestan dinero, por eso le ofrecí doscientos cincuenta mil de inmediato...Bien...Está bien, ¿qué tal si agrego otros cincuenta mil de oro? ¡No puedo ofrecerle más!";
		link.l1 = "Está bien. Tienes un trato. ¿Dónde fue el último lugar donde viste a Martene?";
		link.l1.go = "tibo_35";
		break;

	case "tibo_35":
		dialog.text = "Navegó hacia el sur hasta la Tierra Firme Española en Caracas y logró obtener una audiencia con Don Diego Francisco de Kerres, el gobernador. Parece que lo sobornó de alguna manera porque Don Diego le otorgó a Robert la protección de la corona española. Vendió el 'Voltigeur' y ahora es el capitán del pesado galeón 'Infanta'. Debía tener realmente buenos ahorros, ya que pudo permitirse sobornar al gobernador y comprar y equipar un gran barco militar como ese\nAsí que, lo siguiente es que navegará desde Caracas a Santo Domingo en su nuevo barco como parte de un escuadrón español. Eso es todo lo que mi agente logró averiguar. La única oportunidad de atrapar a Martene es alcanzar a ese escuadrón español\nSi llegan a Santo Domingo, todo habrá terminado. No hay pista de adónde irá Robert después. Desaparecerá como un conejo en su madriguera y nunca lo encontraremos.";
		link.l1 = "Entendido. Los interceptaré.";
		link.l1.go = "tibo_36";
		break;

	case "tibo_36":
		dialog.text = "¡Y no te olvides del dedo con el anillo! ¡Esa es una condición obligatoria de nuestro acuerdo! ¡Quiero estar absolutamente seguro de que Robert está muerto!";
		link.l1 = "Está bien. No perdamos tiempo, ¡zarparé de inmediato!";
		link.l1.go = "tibo_37";
		break;

	case "tibo_37":
		DialogExit();
		AddQuestRecord("Sharlie", "27");
		Terrapin_CreateRoberConvoy();
		if (bImCasual)
			NewGameTip("Modo exploración: el temporizador no está desactivado. ¡Cumple el plazo!");
		NextDiag.CurrentNode = "tibo_time";
		break;

	case "tibo_time":
		dialog.text = "¿Sigue Martene apestando el Caribe con su presencia, capitán?";
		link.l1 = "¡No le queda mucho tiempo!";
		link.l1.go = "exit";
		NextDiag.TempNode = "tibo_time";
		break;

	case "tibo_38":
		dialog.text = "¿Está Martene apestando el Caribe con su presencia, capitán?";
		link.l1 = "Ya no más. No debes temer al Coronel Fox y tu Catherine está vengada. Aquí está tu prueba.";
		link.l1.go = "tibo_39";
		break;

	case "tibo_39":
		RemoveItems(pchar, "finger", 1);
		dialog.text = "Sí... Ese es el dedo de Martene, sin duda. Nunca dejas de impresionar, Capitán " + GetFullName(pchar) + "¡Realmente mereces la reputación que te han dado!";
		link.l1 = "Pasemos al pago, ¿te parece, Thibaut?";
		link.l1.go = "tibo_40";
		break;

	case "tibo_40":
		AddMoneyToCharacter(pchar, 250000);
		TakeNItems(pchar, "gold_dublon", 500);
		Log_Info("Has recibido 500 doblones");
		PlaySound("interface\important_item.wav");
		dialog.text = "Todo está listo. Aquí, toma tu recompensa.";
		link.l1 = "Mi gratitud. Me alegra que pudieras tener eso listo con antelación. Bueno Henry, espero que no te metas en más líos como este y elijas mejores amigos en el futuro. ¡Todo lo mejor!";
		link.l1.go = "tibo_41";
		break;

	case "tibo_41":
		dialog.text = "¡Gracias por tu ayuda, capitán! Recomendaré tus servicios a todos mis amigos. ¡Buena suerte!";
		link.l1 = "...";
		link.l1.go = "tibo_42";
		break;

	case "tibo_42":
		DialogExit();
		AddQuestRecord("Sharlie", "31");
		NextDiag.CurrentNode = "tibo_stop";
		break;

	case "tibo_stop":
		dialog.text = "Sí, monsieur " + GetFullName(pchar) + "¿Tienes algún asunto conmigo?";
		link.l1 = "No, monsieur Thibaut. Solo decidí pasar un momento. ¡Adiós!";
		link.l1.go = "exit";
		NextDiag.TempNode = "tibo_stop";
		break;

	case "tibo_late":
		dialog.text = "Ah, " + GetFullName(pchar) + "...¡Vamos, ¿qué te está retrasando tanto?! Ahora, ¿quién diablos sabe dónde está Robert Martene? Si el Coronel Fox logra averiguarlo todo, creo que estaré en serios problemas...";
		link.l1 = "Ya veo. Llegué demasiado tarde. Mis disculpas, Monsieur Thibaut, pero me retrasaron asuntos muy urgentes. No voy a desperdiciar su tiempo. Adiós.";
		link.l1.go = "exit";
		NextDiag.TempNode = "tibo_over";
		break;

	case "tibo_over":
		dialog.text = "¿Qué quieres, " + GetFullName(pchar) + "? No tengo tiempo para charlar. Tengo peces más grandes que freír. Tengo que encontrar a Martene antes de que lo haga Fox...";
		link.l1 = "Sí, sí. Estoy en camino.";
		link.l1.go = "exit";
		NextDiag.TempNode = "tibo_over";
		break;

	// посланник от Мартэна
	case "envoy":
		dialog.text = "¿Eres el Capitán " + GetFullName(pchar) + "?";
		link.l1 = "Has venido al hombre adecuado, camarada. Soy todo oídos.";
		link.l1.go = "envoy_1";
		break;

	case "envoy_1":
		dialog.text = "Tu acreedor me ha pedido que te diga que el trabajo está hecho y el pez nadará en la red en menos de una hora. Así que date prisa.";
		link.l1 = "Entiendo. ¡Gracias!";
		link.l1.go = "envoy_2";
		break;

	case "envoy_2":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
		AddQuestRecord("Terrapin", "9");
		pchar.quest.Terrapin_cave.win_condition.l1 = "Timer";
		pchar.quest.Terrapin_cave.win_condition.l1.date.hour = sti(GetTime() + 1);
		pchar.quest.Terrapin_cave.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
		pchar.quest.Terrapin_cave.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
		pchar.quest.Terrapin_cave.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
		pchar.quest.Terrapin_cave.win_condition.l2 = "location";
		pchar.quest.Terrapin_cave.win_condition.l2.location = "Tortuga_cave";
		pchar.quest.Terrapin_cave.function = "Terrapin_LevasserInCave";
		break;

	// Левассер в пещере
	case "levasser_cave":
		pchar.quest.Terrapin_LateDungeon.over = "yes"; // снять таймер
		dialog.text = "¿Por qué demonios andas por aquí? ¿Quién eres tú? ¡Respóndeme ahora!";
		link.l1 = "¿Quién demonios eres tú y por qué me estás haciendo preguntas tan estúpidas?";
		link.l1.go = "levasser_cave_1";
		break;

	case "levasser_cave_1":
		dialog.text = "¡¿Qué?! ¡Escuincle mocoso! ¿Quién soy yo? Soy el gobernador de esta isla, François Levasseur, Señor de Renet de Boidouflet de Lettre. ¡Y todo en esta isla está bajo mi jurisdicción! Eso te incluye a ti mientras estés en mi territorio, cachorro.";
		link.l1 = "Vaya, vaya... ¿El lobo feroz en persona, eh? Estás un poco perdido, Levasseur, Señor de Renet de lo que fuera. Tu tiempo se ha acabado. Por orden del gobernador general François Longvilliers de Poincy has sido destituido de tu cargo y condenado a muerte inmediata. ¡Soy tu juez y tu verdugo al mismo tiempo! ¿Alguna última palabra?";
		link.l1.go = "levasser_cave_2";
		break;

	case "levasser_cave_2":
		dialog.text = "";
		link.l1 = "Supongo que no vas a rendirte y pedir clemencia no te servirá de nada, ¡así que adelante, ¡desenvaina tu acero!";
		link.l1.go = "levasser_cave_3";
		break;

	case "levasser_cave_3":
		dialog.text = "¡Maldición! ¡Es un agente de Poincy! ¡Desenvainen sus espadas! ¡Mátenlo!";
		link.l1 = "Bailemos.";
		link.l1.go = "levasser_cave_4";
		break;

	case "levasser_cave_4":
		LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_cave")], false); // разрешить драться
		DialogExit();
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		for (i = 2; i <= 4; i++)
		{
			sld = characterFromId("TerrapinGuard" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		// подкрепление
		int iRank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 7;
		int iScl = 30 + 2 * sti(pchar.rank);
		for (i = 5; i <= 9; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("TerrapinGuard" + i, "citiz_5" + i, "man", "man", iRank, PIRATE, -1, true, "quest"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl * 2 + 50);
			ChangeCharacterAddressGroup(sld, "Tortuga_cave", "goto", "goto" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Terrapin_LevasserCaveDied");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	// Левассер в комнате таверны
	case "levasser_room":
		dialog.text = "¿Qué diablos haces aquí? ¿Quién eres tú? ¡Respóndeme, ahora!";
		link.l1 = "¡Qué me dices! No me lo esperaba... ¿Monsieur Levasseur en persona, supongo?";
		link.l1.go = "levasser_room_1";
		break;

	case "levasser_room_1":
		dialog.text = "¡Sí, soy el gobernador de esta isla, François Levasseur, Señor de Renet de Boidouflet de Lettre! ¡Y todo en esta isla está bajo mi jurisdicción! ¡Incluyéndote a ti mientras caminas por mi territorio, canalla! ¡Responde a las preguntas! Sargento, cierre esta puerta. ¡Este hombre no trae nada bueno!";
		link.l1 = "Es usted increíblemente perspicaz, monsieur Levasseur, Señor de Renet de lo que sea. Mi presencia aquí no le resultará un deleite. ¡Por orden del gobernador general Francois Longvillier de Poincy, ha sido destituido de su cargo y sentenciado a muerte inmediata! ¡Soy su juez y su verdugo en uno!";
		link.l1.go = "levasser_room_2";
		break;

	case "levasser_room_2":
		dialog.text = "";
		link.l1 = "Supongo que no vas a rendirte y pedir misericordia no te servirá, ¡así que adelante y desenfunda el acero! Eres mi trabajo, nada personal. Solo sirviendo a la Corona, ¡ja! Sargento, no le aconsejo interferir mientras llevo a cabo las órdenes del gobernador general.";
		link.l1.go = "levasser_room_3";
		break;

	case "levasser_room_3":
		dialog.text = "¡No le escuches, sargento! ¡Es un agente español! ¡Mátenlo! ¡Guardias, ayuden! ¡Hay españoles aquí!";
		link.l1 = "De hecho, nunca he estado en España, solo en Narbona.";
		link.l1.go = "levasser_room_4";
		break;

	case "levasser_room_4":
		LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], false); // разрешить драться
		DialogExit();
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		for (i = 1; i <= 2; i++)
		{
			sld = characterFromId("TerrapinGuard" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Terrapin_LevasserRoomDied");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	// девушка на балконе
	case "roof_girl":
		dialog.text = "¡Ay! ¡Ayudadme! ¡Soldados!";
		link.l1 = "¡Cállate, imbécil! ¡Si no gritas, no te haré nada!";
		link.l1.go = "roof_girl_1";
		break;

	case "roof_girl_1":
		dialog.text = "¡No me mates!";
		link.l1 = "¡No seas estúpido! Un hombre acaba de pasar por aquí hace diez minutos. Un noble bien vestido. ¿Dónde se esconde? ¡Y ni se te ocurra decirme que no lo viste!";
		link.l1.go = "roof_girl_2";
		break;

	case "roof_girl_2":
		dialog.text = "¿Monsieur Thibaut?";
		link.l1 = "¡Bueno, entonces, lo conoces! ¿A dónde se fue? ¿Vas a responder o debería darte una buena sacudida para que funcione tu cabeza?";
		link.l1.go = "roof_girl_3";
		break;

	case "roof_girl_3":
		dialog.text = "¡Oh no, por favor no me hagas daño! Monsieur Thibaut huyó, por allí hacia el mar. Y saltó del aparejo directamente al agua. Probablemente murió, está tan alto...";
		link.l1 = "No lo creo. No es del tipo que se suicidaría. Deberías entrar. Es peligroso estar aquí afuera esta noche..";
		link.l1.go = "roof_girl_4";
		break;

	case "roof_girl_4":
		dialog.text = "¡Ay! ¡Ay! ¡No disparen!";
		link.l1 = "¿Qué?!";
		link.l1.go = "roof_girl_5";
		break;

	case "roof_girl_5":
		DialogExit();
		LAi_SetActorType(pchar);
		PlaySound("People Fight\MushketShot.wav");
		DoQuestCheckDelay("Terrapin_GirlShot", 1.0);
		break;

	// Кати
	case "kathy":
		PlaySound("Voice\Spanish\Armo02.wav");
		dialog.text = "¿Quién eres? ¿Has venido a matarme o...peor?";
		link.l1 = "Nada de eso, madame. Te devolveré, Catherine Fox, a tu padre en St. John's. Si él te da una paliza después de eso por desobedecer sus órdenes, entonces mi culpa será repetida. Sin embargo, espero que el coronel esté contento de ver a su hija viva a pesar de toda la preocupación que le has causado.";
		link.l1.go = "kathy_1";
		break;

	case "kathy_1":
		dialog.text = "¡Gracias a Dios! ¡Debo estar soñando! ¿No sabes quién soy? ¿Eres francés y católico y, sin embargo, has decidido venir aquí para salvarme de las manos de mis propios compatriotas? ¿Has arriesgado tu vida solo por la hija del Coronel Fox?";
		link.l1 = "Mi razón original para estar aquí en Tortuga era bastante diferente. Pero tampoco podía dejar a una bella dama en manos de una banda de ladrones y rufianes.";
		link.l1.go = "kathy_2";
		break;

	case "kathy_2":
		dialog.text = "¡Eres un noble caballero! ¿Cuál es tu nombre, monsieur?";
		link.l1 = "" + GetFullName(pchar) + ". Capitán " + GetFullName(pchar) + ".";
		link.l1.go = "kathy_3";
		break;

	case "kathy_3":
		dialog.text = "Dime capitán, ¿realmente me llevarás con mi padre en San Juan?";
		link.l1 = "Sí, aunque no le caen bien los franceses. Bueno, le recordaré que también hay ingleses que son unos sinvergüenzas, ¡incluyendo a oficiales ingleses! Fui testigo de al menos uno de ellos... Richard Fleetwood era su nombre.";
		link.l1.go = "kathy_4";
		break;

	case "kathy_4":
		dialog.text = "Si llegamos a Antigua, haré todo lo que pueda para convencer a mi padre de que hay verdaderos caballeros entre los franceses.";
		link.l1 = "Agradecería mucho eso... Está bien, espero que mis ángeles guardianes hayan vigilado mi rastro por los tejados de la ciudad y ya estén buscando nuestro regreso.";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Terrapin_OwrInGrot");
		break;

	case "kathy_5":
		PlaySound("Voice\Spanish\Armo01.wav");
		dialog.text = "¡No podía creer que fueras a cumplir tu promesa hasta ahora! Tantas cosas horribles y asquerosas me han sucedido últimamente... Te agradezco, capitán, por devolverme la fe en las personas y la caballerosidad. ¡Deberías visitar a mi padre cuando puedas!\nÉl respeta a hombres como tú. Y no importa que seas francés. Haré todo lo posible para persuadir a mi padre de reconsiderar su actitud hacia tu nación.";
		link.l1 = "Gracias, Catherine. Tal vez aproveche tu cortesía.";
		link.l1.go = "kathy_6";
		break;

	case "kathy_6":
		dialog.text = "Espero que lo hagáis, capitán. Un enorme agradecimiento a vos una vez más por lo que habéis hecho por mí. Nunca lo olvidaré.";
		link.l1 = "Vamos, apresúrate a ver a tu padre. Estará encantado de verte. Quizás ya haya regresado del campo. Bueno, de todos modos, es hora de que me vaya. ¡Adiós!";
		link.l1.go = "kathy_7";
		break;

	case "kathy_7":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 10.0);
		npchar.lifeday = 0;
		SetFunctionTimerCondition("Terrapin_ReturnFox", 0, 0, 3, false); // Фокса на место
		pchar.questTemp.Terrapin_KathyReward = "true";					 // награда за спасение Кати 160912
		break;

	// наш матрос
	case "terrapin_grot":
		dialog.text = "¡Ahí estás, capitán! ¡Nos tenías preocupados! ¡Un salto como ese por los tejados de tejas y otro desde una altura que revuelve el estómago fue digno de ver! Dios como nuestro testigo, estábamos preocupados de que no lo lograras... ¡Bienvenido de nuevo a bordo, capitán, el bote está listo!";
		link.l1 = "Genial. ¡Catherine, sígueme!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Terrapin_GotoShip");
		break;

	case "tibo_sailor":
		dialog.text = "Hola, monsieur. ¿Eres tú el capitán " + GetFullName(pchar) + "?";
		link.l1 = "Sí, ese soy yo. ¿Qué está pasando?";
		link.l1.go = "tibo_sailor_1";
		break;

	case "tibo_sailor_1":
		dialog.text = "Uf, apenas te alcancé... He venido a ti en nombre de un caballero que conoces por el nombre de Henry Thibaut.";
		link.l1 = "¿Henry? ¿Y qué quiere él? ¿Compartir su alegría por recibir de repente una herencia tras la muerte de su querido tío difunto?";
		link.l1.go = "tibo_sailor_2";
		break;

	case "tibo_sailor_2":
		dialog.text = "Monsieur Thibaut ha solicitado urgentemente que lo visites en su mansión en Tortuga lo antes posible. Tiene un trabajo bien remunerado para ti. También me dijo que te mencionara un nombre: Robert Martene. Eso debería encender tu interés.";
		link.l1 = "¿Ah, sí? ¿Y qué le dio a Enrique esa idea?";
		link.l1.go = "tibo_sailor_3";
		break;

	case "tibo_sailor_3":
		dialog.text = "Además, si eso no te convenció para visitarlo ya, él además solicitó que añadiera lo siguiente: 'Robert Martene debe morir'.";
		link.l1 = "Está bien, está bien... Ahora se pone interesante. Dos amigos jurados acaban de tener una pelea... Como dices, intentaré visitar a Henry cuando tenga la oportunidad.";
		link.l1.go = "tibo_sailor_4";
		break;

	case "tibo_sailor_4":
		dialog.text = "Monsieur Thibaut le ha pedido que no se demore con su visita. 'El pez se escapará de la red en diez días' fueron sus palabras exactas...";
		link.l1 = "Él y Robert tienen la misma manera de hablar. Está bien, le haré una visita a Henry.";
		link.l1.go = "tibo_sailor_5";
		break;

	case "tibo_sailor_5":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
		if (bImCasual)
			NewGameTip("Modo exploración: el temporizador no está desactivado. ¡Cumple el plazo!");
		SetFunctionTimerCondition("Terrapin_TiboCallOver", 0, 0, 10, false);
		AddQuestRecord("Sharlie", "25");
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
