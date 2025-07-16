// Оле Кристиансен - Белый Мальчик
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "¿Qué quieres?";
		link.l1 = "Nada.";
		NextDiag.TempNode = "First time";
		break;

	// в магазине - первая встреча
	case "store":
		dialog.text = "Ups... Hola, tío. ¿Tienes una cuenta blanca? Dame la cuenta blanca...";
		link.l1 = "Mm. Buen día. ¿Eres tú... el Chico Blanco?";
		link.l1.go = "store_1";
		break;

	case "store_1":
		dialog.text = "¡Cuentas! ¡Cuenta blanca para el chico blanco! ¿Tienes una cuenta blanca, tío?";
		if (CheckCharacterItem(pchar, "jewelry52"))
		{
			link.l1 = "Hm, no tengo cuentas, pero puedo darte esta perla. Es blanca y es como la cuenta. ¿Te parece bien?";
			link.l1.go = "store_2";
		}
		link.l2 = "No, no tengo cuentas ni blancas ni rojas. No soy una chica ni un indio para llevar cuentas. Dime...";
		link.l2.go = "pearl";
		sld = characterFromId("Axel");
		sld.quest.ole_pearl = "true";
		break;

	case "pearl":
		dialog.text = "¡Cuenta! ¡Cuenta blanca! Sin cuenta, no hay charla. Mal tío... ¡Dame una cuenta!";
		link.l1 = "¡Maldita sea! ¡Qué tipo tan loco! Ojo de Serpiente y Chimiset tenían razón - él es un cabeza hueca... ¿Qué tipo de abalorio necesita?";
		link.l1.go = "exit";
		NextDiag.TempNode = "pearl_repeat";
		break;

	case "pearl_repeat":
		dialog.text = "Da una cuenta, tío. Buen tío... ¡Cuenta blanca!";
		if (CheckCharacterItem(pchar, "jewelry52"))
		{
			link.l1 = "Aquí, toma tu cuenta. ¿Es eso lo que quieres?";
			link.l1.go = "store_2";
		}
		link.l2 = "Ah, maldición...";
		link.l2.go = "exit";
		NextDiag.TempNode = "pearl_repeat";
		break;

	case "store_2":
		RemoveItems(pchar, "jewelry52", 1);
		PlaySound("interface\important_item.wav");
		dialog.text = "¡Sí, sí! ¡Es verdad! ¡El tío me dio una cuenta! ¡Gracias, buen hombre! Ahora Ole tiene una cuenta más. Pronto veré a mamá...";
		link.l1 = "Me alegro por ti. Bueno, ¿podemos hablar ahora?";
		link.l1.go = "store_3";
		sld = characterFromId("Axel");
		DeleteAttribute(sld, "quest.ole_pearl");
		break;

	case "store_3":
		dialog.text = "Claro, buen hombre. ¿Eres un buen hombre, tío? Seremos amigos. Ole estará encantado de hablar. ¿Cómo te llamas?";
		link.l1 = "Mi nombre es " + pchar.name + " . Ole, un hombre me habló de ti y ya no está aquí. Dijo que le habías ayudado y que puedes ayudarme a mí.";
		link.l1.go = "store_4";
		break;

	case "store_4":
		dialog.text = "Tío le dio una cuenta a Ole - es un buen tío. A Ole le gusta ayudar a la buena gente. No hay mucha gente buena - malos tíos están por todas partes. Te ayudaré, seguro. Me gusta ayudar.";
		link.l1 = "¡Genial! Bueno, ahora somos amigos. Oye, dime, ¿recuerdas a un hombre con piel roja y un magnífico sombrero con plumas? Me dijo que lo salvaste hace mucho tiempo.";
		link.l1.go = "store_5";
		break;

	case "store_5":
		dialog.text = "Recuerdo a ese tío. Es un buen hombre. Lo salvé. Lo llevé a la estatua. Y recientemente he salvado a otro buen hombre del almacén con comida. Lo he salvado de los tíos del mal almirante. Lo habrían matado. Quería llevarlo a la estatua también, pero se ha negado. Totalmente.";
		link.l1 = "¿Del compartimento de carga? Jeje, supongo que sé a quién te refieres... Y conozco a ese tío. Dime, Ole, ¿quién es ese hombre que has salvado?";
		link.l1.go = "store_6";
		break;

	case "store_6":
		dialog.text = "Su nombre es tío Nathan. Está enfermo, muy-muy enfermo. Apenas podía caminar cuando Ole lo encontró.";
		link.l1 = "Claro... Es extraño que él siquiera pudiera hacerlo.";
		link.l1.go = "store_7";
		break;

	case "store_7":
		dialog.text = "No, no es extraño. Lo encontré y le di un poco de ron de fuego. Nadé dentro del agujero porque hay comida en ese barco. Los hombres malos cierran la puerta, pero yo siempre la abro. Je-je-je... Tontos hombres malos. Atraen cangrejos, lo sé. Hombres malos\nLlegué allí y encontré a Nathan. No se sentía bien. Tenía ron de fuego - le di para que lo bebiera, y se sintió mejor. Luego le di la tintura, siempre llevo una de esas, por si un cangrejo aterrador muerde a Ole. El buen tío Chimiset me dijo que lo hiciera...";
		link.l1 = "¿Le diste un antídoto y ron? Je, no eres tan tonto como todos piensan. Bien hecho, Ole.";
		link.l1.go = "store_8";
		break;

	case "store_8":
		dialog.text = "Los tíos malvados consideran a Ole un tonto y se burlan de él: Ole el tonto... Ole no es tonto, sólo tiene que recoger todas las cuentas blancas o su madre lo echará. ¿Me darás otra cuenta más tarde?";
		link.l1 = "Hm... Claro, Ole, somos amigos. Dime, ¿cómo ibas a enviar a Hawk... tío Nathan a la estatua? El tío Chimiset me dijo que se hundió con el barco...";
		link.l1.go = "store_9";
		break;

	case "store_9":
		dialog.text = "La estatua está en el fondo. Ole lo sabe. Pero no es profundo y el buen tío Henrik puede enviar al tío Nathan allí. El tío Henrik sabe cómo caminar bajo el agua. Pero hay muchos cangrejos aterradores. Ole les teme. Muerden dolorosamente.";
		link.l1 = "¿Tío Henrik? ¿Quién es él?";
		link.l1.go = "store_10";
		break;

	case "store_10":
		dialog.text = "Tío Henrik vive entre los malvados tíos Narvales. Todos lo conocen. Puede caminar bajo el agua y enseña a los tíos Narvales cómo bucear allí. Tío Henrik es amable, le dio una cuenta blanca a Ole.";
		link.l1 = "¿Y cómo te dejan entrar los Narvales? ¿O su territorio está abierto para ti?";
		link.l1.go = "store_11";
		break;

	case "store_11":
		dialog.text = "Tee-hee... Los tíos malvados no dejan que Ole entre, pero Ole puede entrar en cualquier habitación de sus barcos por la noche. Son grandes y ruidosos, pero Ole es silencioso y cuidadoso. Y conocí al tío Henrik mientras nadaba alrededor del barco desde el que el tío Henrik se zambulle. El tío Henrik le dio una cuenta blanca a Ole y ahora somos amigos.";
		link.l1 = "Interesante... Yo también quiero ser amigo del tío Henrik.";
		link.l1.go = "store_12";
		break;

	case "store_12":
		dialog.text = "¿Quieres bucear e ir a la estatua? Está allí, en el naufragio del viejo barco. Hay muchos cangrejos grandes y aterradores. ¿No les temes? Pueden morder.";
		link.l1 = "No, no les temo. Ya he matado a uno, así que más les vale tenerme miedo a mí.";
		link.l1.go = "store_13";
		break;

	case "store_13":
		dialog.text = "Oh, " + pchar.name + " ¡es muy valiente! Entonces debes ir con el tío Henrik, él te enseñará a caminar en el fondo y matarás a todos los cangrejos allí. También encontrarás allí otra cuenta grande para Ole. ¿verdad?";
		link.l1 = "Claro, lo haré. Pero primero necesito encontrar al tío Henrik.";
		link.l1.go = "store_14";
		break;

	case "store_14":
		dialog.text = "¿Y por qué buscarle? Vive en el barco llamado 'San Gabriel', en el taller. Pero los malvados tíos Narvales pueden no darte la bienvenida.";
		link.l1 = "Me ocuparé de los malvados tíos yo mismo. Y la última pregunta, ¿dónde está el tío Nathan ahora? Lo he estado buscando y él es la razón por la que estoy aquí.";
		link.l1.go = "store_15";
		break;

	case "store_15":
		dialog.text = "Escondo al tío Nathan en mi santuario en la 'Fernanda'. Está muy lejos y nadie vive allí. Todos piensan que se hundirá pronto, pero Ole sabe lo contrario. Salvé al tío Nathan y lo llevé allí. \nTodavía está muy enfermo y bebe ron de fuego todo el tiempo. Apenas puede caminar y no puede levantar nada más pesado que cinco libras. Me siento mal por el tío Nathan, le llevo ron de fuego de los cofres y comida de la bodega de los hombres malos del almirante. También le cocino ratas que atrapo. ¡Ratas muy sabrosas!";
		link.l1 = "¿Ratas sabrosas? Ya veo. Entonces, ¿está Nathan en el barco llamado... cómo dijiste - la 'Fernanda'? No la conozco...";
		link.l1.go = "store_16";
		break;

	case "store_16":
		dialog.text = "Tío " + pchar.name + ",  acabo de decirte que no está lejos de aquí. Tienes que nadar para llegar a ella. Hay una puerta en su parte trasera, pero el tío Nathan no la abre. Ole le dijo que no lo hiciera. Pero si eres amigo del tío Nathan, te diré cómo abrirla. Llama a la puerta así: toc-toc... toc-toc. Entonces él la abrirá.";
		link.l1 = "Lo recordaré. ¡Gracias, Ole! ¡Realmente me has ayudado! No sé cómo agradecerte debidamente.";
		link.l1.go = "store_17";
		break;

	case "store_17":
		dialog.text = "Tráeme otra cuenta blanca. Si la encuentras, por supuesto.";
		link.l1 = "¡Ah, sí! ¡Cuentas blancas! Bien. ¡Nos vemos, Ole!";
		link.l1.go = "store_18";
		break;

	case "store_18":
		DialogExit();
		LAi_SetLoginTime(npchar, 12.0, 21.99);
		LAi_SetCitizenType(npchar);
		LAi_group_MoveCharacter(npchar, "LSC_CITIZEN");
		sld = characterFromId("Nathaniel");
		sld.dialog.currentnode = "diffindoor";
		sld.greeting = "Nathaniel_ill";			 // ноду и вякалку Натану
		pchar.questTemp.LSC.DiffIndoor = "true"; // атрибут прохода к Натану
		pchar.questTemp.LSC = "mechanic";		 // флаг на разговор с Механиком
		NextDiag.CurrentNode = "ole";
		AddQuestRecord("LSC", "6");
		break;

	case "ole":
		dialog.text = "Ah, tío " + pchar.name + "¡Me alegra verte! ¿Cómo te va?";
		link.l1 = "Gracias, Ole, estoy bien. Me alegra verte también.";
		link.l1.go = "exit";
		link.l2 = "Escucha, Ole, has dicho que los piratas del almirante cierran la puerta del compartimento de carga y tú siempre la abres... Todos los cofres allí están cerrados y has dicho que tomas ron para el tío Nathan de ellos. ¿Cómo puedes hacer eso?";
		link.l2.go = "lock";
		NextDiag.TempNode = "ole";
		break;

	case "lock":
		dialog.text = "Ole tiene un juego de llaves finas. Abren cualquier puerta o cofre. Bueno, no todas. Algunas no pueden abrirse, pero la mayoría sí. Ole las encontró en la cabina del malvado tío Jurgen. Él trabaja con su martillo todos los días cerca de su horno. Hace cerraduras y llaves. Y también hace mosquetes grandes y aterradores para los malvados Narvales.";
		link.l1 = "Ya veo. Ole, ¿puedes venderme esas llaves? Puedo pagarlas...";
		link.l1.go = "lock_1";
		break;

	case "lock_1":
		dialog.text = "Está bien, tío " + pchar.name + ", te venderé las llaves. Solo dejaré una para mí. Abre la habitación del almirante. Hay mucha comida y ron para el tío Nathan. De todos modos, ya no quedan más cuentas ni ron en los cofres.";
		link.l1 = "¿Cuánto quieres por ellos?";
		link.l1.go = "lock_2";
		break;

	case "lock_2":
		dialog.text = "Primero, dime, tío " + pchar.name + ", ¿tienes un gran barco?";
		link.l1 = "Sí, la he visto. Pero ella no está aquí, está en el anillo exterior. Pero pronto dejaré la isla y regresaré aquí en mi gran barco por el tío Nathan.";
		link.l1.go = "lock_3";
		break;

	case "lock_3":
		dialog.text = "¿Para el tío Nathan? ¡Oh, eso es maravilloso! Escucha, prométeme entonces llevarme de aquí en tu gran barco y dejarme navegar contigo tanto como necesite. Puedo ser útil. Puedo atrapar y cocinar ratas... Además, dame cinco cuentas blancas. Y te daré las llaves.";
		if (GetCharacterItem(pchar, "jewelry52") >= 5)
		{
			link.l1 = "¡Claro! Aquí están tus cuentas. Tómalas.";
			link.l1.go = "lock_4";
		}
		link.l2 = "¿Atrapar y cocinar ratas? ¡Je! Una habilidad interesante. Claro, Ole, tenemos un trato. Te traeré cinco cuentas y mi palabra.";
		link.l2.go = "exit";
		NextDiag.TempNode = "ole_1";
		break;

	case "ole_1":
		dialog.text = "Ah, tío " + pchar.name + "¡Me alegra verte! ¿Cómo estás?";
		link.l1 = "Gracias, Ole, estoy bien. Me alegra verte también.";
		link.l1.go = "exit";
		if (GetCharacterItem(pchar, "jewelry52") >= 5)
		{
			link.l2 = "Te he traído cinco cuentas blancas para tus llaves.";
			link.l2.go = "lock_4";
		}
		NextDiag.TempNode = "ole_1";
		break;

	case "lock_4":
		RemoveItems(pchar, "jewelry52", 5);
		PlaySound("interface\important_item.wav");
		dialog.text = "¡Cuentas! ¡Cuentas blancas! Tío " + pchar.name + "  ¡ha dado cuentas a Ole! ¡Pronto te veré, mamá!... Tío " + pchar.name + ", ¿me prometes que me sacarás de aquí cuando regreses?";
		link.l1 = "Lo hago, Ole. Aún no he comido ratas. Te llevaré conmigo.";
		link.l1.go = "lock_5";
		break;

	case "lock_5":
		GiveItem2Character(pchar, "keys_skel");
		AddCharacterExpToSkill(pchar, "Sneak", 200);
		dialog.text = "Gracias, gracias, buen tío " + pchar.name + "¡Toma tus llaves! Es fácil usarlas, solo insértalas una por una y prueba. Una de ellas eventualmente abrirá una cerradura que necesitas. Si no lo hace, entonces la cerradura es demasiado complicada y definitivamente necesitarás una llave especial.";
		link.l1 = "Ya veo. Supongo que me encargaré de ello.";
		link.l1.go = "lock_6";
		break;

	case "lock_6":
		dialog.text = "Espera, tío " + pchar.name + "¡Tengo una llave más! Es bonita e inteligente. El malvado tío Jurgen no hace llaves como esta. No sé qué abre, pero quizás tú lo descubras. Mira, es una llave muy bonita, seguramente no has visto nada como esta antes.";
		link.l1 = "Muéstrame... Sí, la llave es muy interesante. Pero ¿de qué sirve si no sabes qué se puede abrir con ella?";
		link.l1.go = "lock_7";
		break;

	case "lock_7":
		dialog.text = "Tío " + pchar.name + ", eres muy extraño. ¿De qué sirve? Si hay una llave, entonces en algún lado está la cerradura. Si hay una cerradura, entonces en algún lado está la moneda. He encontrado la llave en la isla. Significa que la cerradura también está aquí. No hay duda de eso. Es una llave inteligente y solo artículos muy valiosos están cerrados con tal llave. Ole lo sabe.";
		link.l1 = "Para ser honesto, eres gracioso, Ole. Está bien, lo compraré. ¿Quieres cuentas por ello?";
		link.l1.go = "lock_8";
		break;

	case "lock_8":
		dialog.text = "Sí, Ole quiere cinco cuentas. ¿Se las darás, tío?" + pchar.name + "?";
		if (GetCharacterItem(pchar, "jewelry52") >= 5)
		{
			link.l1 = "Aquí, toma tus cuentas.";
			link.l1.go = "key";
		}
		link.l2 = "No los tengo, pero te traeré cuentas con seguridad.";
		link.l2.go = "exit";
		NextDiag.TempNode = "ole_2";
		break;

	case "key":
		RemoveItems(pchar, "jewelry52", 5);
		PlaySound("interface\important_item.wav");
		GiveItem2Character(pchar, "sant_anna_key");
		AddCharacterExpToSkill(pchar, "Fortune", 200);
		dialog.text = "¡Cuentas! ¡Cuentas blancas para el chico blanco! ¡Para su mamá! Aquí, tío " + pchar.name + ", toma la llave. Y encontrarás la cerradura, Ole lo sabe. Eres valiente, ni siquiera temes a los cangrejos aterradores.";
		link.l1 = "¡Oh, no me hagas reír, Ole! Gracias por la llave. ¡Nos vemos!";
		link.l1.go = "exit";
		NextDiag.TempNode = "ole_3";
		break;

	case "ole_2":
		dialog.text = "Ah, tío " + pchar.name + "¡Me alegra verte! ¿Cómo te va?";
		link.l1 = "Gracias, Ole, estoy bien. Me alegra verte también.";
		link.l1.go = "exit";
		if (GetCharacterItem(pchar, "jewelry52") >= 5)
		{
			link.l2 = "Te he traído cinco cuentas blancas para tu llave.";
			link.l2.go = "key";
		}
		NextDiag.TempNode = "ole_2";
		break;

	case "ole_3":
		dialog.text = "Ah, tío " + pchar.name + "¡Me alegra verte! ¿Cómo te va?";
		link.l1 = "Gracias, Ole, estoy bien. Me alegra verte también.";
		link.l1.go = "exit";
		NextDiag.TempNode = "ole_3";
		break;

	case "return":
		dialog.text = "Oh, tío " + pchar.name + ", ¡has regresado! ¡Has vuelto al gran barco! ¿Me llevarás de aquí? Tío " + pchar.name + ", me lo has prometido, ¿recuerdas?";
		link.l1 = "¡Claro que sí, Ole. Bienvenido a bordo! Supongo que las ratas están en problemas, ¡ja-ja!";
		link.l1.go = "return_1";
		link.l2 = "¿De veras? ¿Y cuándo te lo prometí? No recuerdo haber hecho promesas así...";
		link.l2.go = "return_3";
		break;

	case "return_1":
		dialog.text = "¡Gracias, tío! ¡Ole será útil, ya verás! Oh, ¿tal vez veré a mamá? ¡Estoy en camino ahora!";
		link.l1 = "No te apresures así, Ole. Puedes empacar tus cosas. No voy a zarpar de inmediato.";
		link.l1.go = "return_2";
		break;

	case "return_2":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LSC_SetOlePassenger", 10.0);
		break;

	case "return_3":
		dialog.text = "¡Me lo has prometido, sí lo has hecho! ¡Has prometido sacar a Ole de aquí! ¡Malvado tío! ¡Has engañado a Ole! ¡Malo tío!";
		link.l1 = "...";
		link.l1.go = "return_4";
		break;

	case "return_4":
		DialogExit();
		LAi_SetActorType(npchar);
		npchar.lifeday = 0;
		LAi_ActorRunToLocation(npchar, "reload", "reload45", "none", "", "", "", 20.0);
		ChangeCharacterComplexReputation(pchar, "nobility", -5);
		ChangeCharacterComplexReputation(pchar, "authority", -3);
		if (GetCharacterIndex("Mary") != -1) // Мэри
		{
			sld = characterFromId("Mary");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		else // иначе завершение
		{
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		}
		break;

	// Блудный сын
	case "givemepearl":
		dialog.text = "Tío, tío... Necesito una cuenta blanca más. ¡Por favor, dale una cuenta blanca a Ole!";
		if (CheckCharacterItem(pchar, "jewelry52"))
		{
			link.l1 = "Sabía que lo pedirías. Aquí, toma tu cuenta. ¿Satisfecho?";
			link.l1.go = "givemepearl_yes";
		}
		link.l2 = "Oh, y qué dolor de cabeza... No tengo más cuentas, Ole, ¡no las tengo!";
		link.l2.go = "givemepearl_no";
		DeleteAttribute(npchar, "pearl_date");
		break;

	case "givemepearl_yes":
		RemoveItems(pchar, "jewelry52", 1);
		PlaySound("interface\important_item.wav");
		AddCharacterExpToSkill(pchar, "Fortune", 50);
		dialog.text = "¡Gracias! Buen, buen tío " + pchar.name + ". ¡Ole tiene una cuenta más y no quedan muchas cuentas! Y me iré a mamá...";
		link.l1 = "Oh, ¿y por qué eres tan extraño...?";
		link.l1.go = "givemepearl_yes_1";
		break;

	case "givemepearl_yes_1":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
		SaveCurrentNpcQuestDateParam(npchar, "pearl_date");
		npchar.quest.pearlqty = sti(npchar.quest.pearlqty) + 1;
		NextDiag.CurrentNode = "givemepearl_repeat";
		break;

	case "givemepearl_repeat":
		dialog.text = "¡Gracias por una cuenta, buen tío " + pchar.name + "!";
		link.l1 = "De nada...";
		link.l1.go = "exit";
		NextDiag.TempNode = "givemepearl_repeat";
		break;

	case "givemepearl_no":
		dialog.text = "¿No hay cuenta? Pero, ¿cómo es eso, tío " + pchar.name + "? Solo quedan unas cuentas más... tengo que recogerlas. Aterrizaré en ese caso. ¡Buscaré cuentas...!";
		if (CheckCharacterItem(pchar, "jewelry52"))
		{
			link.l1 = "¿Y adónde vas a ir? ¿Qué harás solo? No, no quiero ser responsable de tu destino. Espera, voy a revisar mis bolsillos... ¡Aquí! Toma tu cuenta y quédate conmigo. ¿Satisfecho?";
			link.l1.go = "givemepearl_yes";
		}
		link.l2 = "Es tu derecho, Ole. Si estás aburrido de navegar conmigo, entonces no te detendré. Tuvimos un acuerdo. Sin embargo, has estado capturando esas tarifas bien...";
		link.l2.go = "givemepearl_no_1";
		break;

	case "givemepearl_no_1":
		dialog.text = "Adiós, tío " + pchar.name + ". Ole necesita cuentas blancas o nunca regresará con su mamá...";
		link.l1 = "Oh, lo siento mucho por ti, pero ¿qué puedo hacer? Ve, Ole. Buena suerte.";
		link.l1.go = "givemepearl_exit";
		break;

	case "givemepearl_exit": // Оле уходит - квест не довели до конца
		DialogExit();
		RemovePassenger(Pchar, npchar);
		npchar.lifeday = 0;
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
		DeleteAttribute(pchar, "GenQuest.Ole");
		break;

	case "mother":
		dialog.text = "Tío " + pchar.name + "¡Necesito una cuenta blanca más. La última. Por favor, dásela a Ole!";
		if (CheckCharacterItem(pchar, "jewelry52"))
		{
			link.l1 = "Sabía que lo pedirías. Aquí, toma tu cuenta. ¿Satisfecho?";
			link.l1.go = "mother_1";
		}
		link.l2 = "Oh, y qué dolor de cabeza... No tengo más cuentas, ¡Ole, no tengo!";
		link.l2.go = "givemepearl_no_1";
		break;

	case "mother_1":
		RemoveItems(pchar, "jewelry52", 1);
		PlaySound("interface\important_item.wav");
		dialog.text = "Gracias, gracias, buen tío " + pchar.name + ". ¡Ahora Ole tiene todas las cuentas. Sí, todas ellas! Ahora Ole puede llevarlas a mamá y ella no enviará a Ole lejos...";
		link.l1 = "Escucha, ¿quién es esa madre de la que siempre hablas? Y explícame al fin por qué necesitas esas perlas... ¿cuentas blancas? ¿Y qué significa?... ¿Las tienes todas?";
		link.l1.go = "mother_2";
		break;

	case "mother_2":
		dialog.text = "Buen tío " + pchar.name + " ha ayudado a Ole a recoger cuentas para su mamá... Ole era pequeño cuando rompió el collar de cuentas blancas de su mamá. Todas cayeron al agua. Mamá se enojó tanto con Ole, y él no puede volver a casa hasta que recoja todas las cuentas perdidas\nRecuerdo cuántas había. Cinco veces diez cuentas. Ahora Ole las tiene todas. Tío " + pchar.name + ", por favor, ¡llévame a casa! Quiero hacer feliz a mamá, devolver las cuentas. ¡Llévame a casa!";
		link.l1 = "Jesús, qué historia tan increíble... Llegaste a la Isla siendo un niño. ¿Te expulsaron de la tuya porque rompiste el collar de perlas de tu madre? Espeluznante...";
		link.l1.go = "mother_3";
		break;

	case "mother_3":
		dialog.text = "Llévame con mi mamá, buen tío " + pchar.name + " Quiero verla. Se complacerá al ver las cuentas.";
		link.l1 = "Me gustaría, pero ¿sabes dónde está tu hogar? ¿Dónde vive tu madre?";
		link.l1.go = "mother_4";
		break;

	case "mother_4":
		dialog.text = "Vive en la isla, en la casa con el tejado rojo.";
		link.l1 = "¡De verdad! ¿Acaso sabes cuántas islas hay aquí y cuántas casas tienen un techo rojo? ¿Cómo se llama esa isla? Dame detalles...";
		link.l1.go = "mother_5";
		break;

	case "mother_5":
		dialog.text = "No sé su nombre. Sé que era una isla, ¡mamá le decía a papá que estábamos en la isla! Y vivíamos en la casa con el techo rojo. Casa bonita, una grande. Llévame con mamá, tío " + pchar.name + ". Por favor...";
		link.l1 = "Oh,   bien.   Buscaremos   una   casa   así   en   cada   isla   y   preguntaremos   por   tu   madre.   ¿Cómo   se   llama?";
		link.l1.go = "mother_6";
		break;

	case "mother_6":
		dialog.text = "¿Su nombre? Eres tan extraño, tío " + pchar.name + ". El nombre de la madre es madre. ¿Es diferente el nombre de tu madre?";
		link.l1 = "Oh, Dios, por favor, envíame algo de paciencia... Bien, Ole. Intentaremos encontrar tu hogar. Ahora ve al barco.";
		link.l1.go = "mother_7";
		break;

	case "mother_7":
		dialog.text = "Gracias, tío " + pchar.name + "¡Eres muy, muy amable y bueno! ¡Pronto Ole verá a mamá!";
		link.l1 = "Oh...";
		link.l1.go = "mother_8";
		break;

	case "mother_8":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
		DeleteAttribute(npchar, "pearl_date");
		// ставим Агнес Кристиансен и открываем ее дом в Мариго
		LocatorReloadEnterDisable("Marigo_town", "houseSp2", false);
		sld = GetCharacter(NPC_GenerateCharacter("Agnes", "women_18", "woman", "towngirl", 10, HOLLAND, -1, true, "quest"));
		SetFantomParamFromRank(sld, 10, true);
		sld.name = "Agnes";
		sld.lastname = "Christiansen";
		sld.dialog.FileName = "Quest\LSC\OtherNPC.c";
		sld.dialog.currentnode = "agnes";
		// sld.greeting = "";
		LAi_SetOwnerType(sld);
		LAi_SetImmortal(sld, true);
		ChangeCharacterAddressGroup(sld, "Marigo_houseSp2", "barmen", "stay");
		LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
		break;

	case "home":
		dialog.text = "Madre... Madre, ¡mamá! ¡He vuelto!";
		link.l1 = "Hijo...";
		link.l1.go = "home_1";
		break;

	case "home_1":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_SetActorType(pchar);
		SetMusic("music_romantic");
		bDisableCharacterMenu = true; // лоченые интерфейсы
		locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
		Pchar.FuncCameraFly = "";
		DoQuestFunctionDelay("LSC_OleReturnHome", 18.0);
		break;

	case "home_2":
		dialog.text = "Mamá, ¡te he traído cuentas blancas! ¡Las he recogido todas! Volverás a tener un collar. ¿Sigues enojada conmigo?";
		link.l1 = "Dios...(llora) ¡Ole! Hijo, ¿por qué? ¿Por qué te fuiste? ¡No me importan esas perlas!";
		link.l1.go = "home_3";
		break;

	case "home_3":
		sld = characterFromId("Blaze");
		dialog.text = "Mamá, aquí... tómelos. Los he estado coleccionando por mucho tiempo. Buenas personas me han estado ayudando, especialmente el tío " + sld.name + ". Me llevó en su gran barco, me ayudó a recoger cuentas y me trajo a casa...";
		link.l1 = "Vaya... Realmente has crecido, pero sigues siendo un niño... ¡Déjame abrazarte, hijo! Lo siento, por favor perdóname por ese maldito collar. ¡Nunca te dejaré solo, nunca! Viviremos juntos y cuidaré de ti... Me expiaré, ¡lo prometo!...";
		link.l1.go = "home_4";
		break;

	case "home_4":
		dialog.text = "Mamá, te extrañé... Quiero quedarme contigo. ¿Todavía estás enojada conmigo? ¿Por qué estás llorando?";
		link.l1 = "(llora) No, no... Lo siento mucho, por favor, ¡perdóname, hijo!...";
		link.l1.go = "home_5";
		break;

	case "home_5": // перекидываем pchar
		DialogExit();
		LAi_SetStayType(pchar);
		SetMainCharacterIndex(GetCharacterIndex("Blaze"));
		PChar = GetMainCharacter();
		LAi_SetPlayerType(PChar);
		sld = characterFromId("Agnes");
		sld.dialog.currentnode = "agnes_11";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;

	case "final":
		dialog.text = "Tío " + pchar.name + "¡Es tan bueno que hayas venido! Gracias por llevarme con mi mamá. Es tan bueno estar aquí con ella... ¿No es genial estar en casa, verdad, tío?" + pchar.name + "?";
		link.l1 = "Sí. Ole. Así es. Me alegra que estés feliz.";
		link.l1.go = "exit";
		NextDiag.TempNode = "final";
		break;

		//----------------------------------------- специальные реакции -----------------------------------------------
		// замечание по обнажённому оружию
	case "LSCNotBlade":
		dialog.text = LinkRandPhrase("Escucha, será mejor que guardes tu arma. Me pone nervioso.", "Sabes, correr con la hoja no se tolera aquí. Guárdala.", "Escucha, no te hagas el caballero medieval corriendo con una espada por ahí. Guárdala, no te queda bien...");
		link.l1 = LinkRandPhrase("Bien.", "Bien.", "Como dices...");
		link.l1.go = "exit";
		NextDiag.TempNode = "First Time";
		break;

	case "CitizenNotBlade":
		if (loadedLocation.type == "town")
		{
			dialog.text = NPCharSexPhrase(NPChar, "Escucha, soy ciudadano de la ciudad y te pediría que mantuvieras tu espada bajo control.", "Escucha, soy ciudadano de la ciudad y te pediría que mantuvieras tu espada en su lugar.");
			link.l1 = LinkRandPhrase("Bien.", "Bien.", "Como dices...");
		}
		else
		{
			dialog.text = NPCharSexPhrase(NPChar, "Ten cuidado, amigo, al correr con un arma. Puedo ponerme nervioso...", "No me gusta cuando los hombres caminan frente a mí con sus armas listas. Me asusta...");
			link.l1 = RandPhraseSimple("Entendido.", "Me lo estoy llevando.");
		}
		link.l1.go = "exit";
		NextDiag.TempNode = "First Time";
		break;
		// <-- специальные реакции

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
