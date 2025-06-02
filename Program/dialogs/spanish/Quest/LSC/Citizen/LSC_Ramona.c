// Рамона Лоцано - горячая испанская сеньорита
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
		if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
		{
			dialog.text = "No quiero hablar contigo. Atacas a civiles pacíficos sin razón alguna y los provocas a pelear. ¡Piérdete!";
			link.l1 = "Mm...";
			link.l1.go = "exit";
			break;
		}
		if (npchar.quest.meeting == "0")
		{
			dialog.text = "¡Hola, hola! ¿Recién llegado? ¿O te escondías en las bodegas de carga, ya que es la primera vez que veo tu cara por aquí?";
			link.l1 = TimeGreeting() + ". Esconderme en las bodegas de carga no es lo mío. Prefiero el lugar del capitán... Sí, soy un recién llegado aquí.";
			link.l1.go = "meeting";
			npchar.quest.meeting = "1";
		}
		else
		{
			dialog.text = "Ah, " + pchar.name + "¡ " + TimeGreeting() + "¡Me alegra verte! ¿Qué dices?";
			link.l1 = LinkRandPhrase("¿Tienes algo interesante que decir?", "¿Ha pasado algo nuevo en la isla?", "¿Me contarás los últimos chismes?");
			link.l1.go = "rumours_LSC";
			link.l2 = "Quiero hacerte algunas preguntas sobre la isla.";
			link.l2.go = "int_quests"; // информационный блок
			link.l5 = "Solo quería saber cómo te va. ¡Nos vemos!";
			link.l5.go = "exit";
		}
		NextDiag.TempNode = "First time";
		break;

	case "meeting": // первая встреча
		dialog.text = "Bueno, entonces vamos a conocernos... capitán. Soy Ramona Lozano, pero ni se te ocurra llamarme señora Lozano, lo odio. ¿Cuál es tu nombre?";
		link.l1 = "" + GetFullName(pchar) + ". Un placer conocerte, Ramona.";
		link.l1.go = "meeting_1";
		break;

	case "meeting_1":
		dialog.text = "¿Estás realmente complacido o solo estás siendo cortés, " + GetFullName(pchar) + "¿Dime, eres realmente un capitán o estabas bromeando?";
		link.l1 = "¡Oh, tantas preguntas a la vez! ¿Puedo responderlas en orden? Primero, estoy realmente complacido, no conozco chicas bonitas todos los días, segundo, soy un capitán, es cierto. Pero mi barco está cerca de las costas de Tierra Firme occidental ahora...";
		link.l1.go = "meeting_2";
		break;

	case "meeting_2":
		dialog.text = "¡Qué divertido! ¿Y cómo es eso, capitán? Estás aquí, pero tu barco está cerca de las costas del Continente. ¿No tienes miedo de que tu tripulación se disperse y te quiten la nave?";
		link.l1 = "He navegado aquí en una barca para... exploración, pero todo salió mal y me encontré en vuestra Isla. Luego chocamos con algunos escombros en la oscuridad, volcamos y ¡voilá! Aquí estoy. Mi barco me esperará tanto como yo quiera. Dannie Hawk podrá controlar a mis hombres.";
		link.l1.go = "meeting_3";
		break;

	case "meeting_3":
		dialog.text = "¿Dannie Hawk? ¿La Danielle Hawk? ¿Quieres decir que navegas con ella?";
		link.l1 = "Mierda flota, Dannie me sirve como mi oficial. Ella quedó al mando mientras estoy ausente... ¿Cómo la conoces?";
		link.l1.go = "meeting_4";
		break;

	case "meeting_4":
		dialog.text = "¡Ja! Todos en las colonias españolas conocen a la pirata Danielle Hawk y a su esposo, Nathaniel. Sí, usted, señor " + GetFullName(pchar) + ",  debes ser un tipo duro... ¿Eres pirata entonces? No te preocupes, me llevo bien con los de tu clase. Me gustan los tipos duros.";
		link.l1 = "Bueno, en realidad no soy un pirata... Solo estoy trabajando en este momento con Jan Svenson y buscando al esposo de Dannie, Nathaniel.";
		link.l1.go = "meeting_5";
		break;

	case "meeting_5":
		dialog.text = "¿Y ahora vas a decirme que no eres un pirata? Trabajando para Forest Devil, tu primer oficial es Dannie Hawk y estás buscando a Nathan Hawk... y estoy seguro de que has venido aquí por el almirante. ¿Verdad?";
		link.l1 = "Ramona, puedes llamarme pirata si quieres, estoy bien con eso. Incluso puedes llamarme ancla, solo no me lances al agua...";
		link.l1.go = "meeting_6";
		break;

	case "meeting_6":
		dialog.text = "Parece que eres uno de los tipos realmente serios, " + pchar.name + " . Bien, tengo que irme. ¡Nos vemos! Tengo la sensación de que podríamos ser amigos... unos amigos muy cercanos.";
		link.l1 = "¿Por qué no? ¡Buena suerte!";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

		//--------------------------------------- блок вопросов и ответов ---------------------------------------------
	case "int_quests":
		dialog.text = "¿Oh, de verdad? Bueno, pregunta, responderé si puedo...";
		if (!CheckAttribute(npchar, "quest.answer_1"))
		{
			link.l1 = "¿Cómo llegaste aquí?";
			link.l1.go = "ansewer_1";
		}
		if (!CheckAttribute(npchar, "quest.answer_2"))
		{
			link.l2 = "Seguro, nunca has intentado escapar de aquí...";
			link.l2.go = "ansewer_2";
		}
		if (!CheckAttribute(npchar, "quest.answer_3"))
		{
			link.l3 = "¿Cómo vives aquí?";
			link.l3.go = "ansewer_3";
		}
		if (!CheckAttribute(npchar, "quest.answer_4"))
		{
			link.l4 = "¿Qué haces aquí? Supongo que la comida no es gratis, ¿verdad?";
			link.l4.go = "ansewer_4";
		}
		link.l10 = "Sin preguntas. Perdón...";
		link.l10.go = "exit";
		break;

	case "ansewer_1":
		dialog.text = "Es una larga historia... La culpa es de mi padrastro. Hace cuatro años vivía en La Habana y ni siquiera podía imaginar cómo las cosas cambiarían para mí. Mi madre murió y yo era el heredero legítimo. No éramos ricos, pero teníamos bastante dinero, más que suficiente para vivir decentemente. A mi padrastro no le gustó eso y decidió deshacerse de mí\nPor supuesto, lo descubrí solo después de que dos matones contratados me atacaran justo detrás de las puertas de la ciudad. Esos tontos me dijeron ellos mismos quién los contrató para matarme y por qué. Afortunadamente, no eran profesionales, estaría tirado en los arbustos con la garganta cortada si así fuera. Los idiotas decidieron divertirse un poco primero\nEl destino me salvó ese día, un capitán como tú pasaba por las puertas. Vio el espectáculo y mató a la escoria de inmediato. No tuvieron ninguna oportunidad. Le conté lo que me pasó y por qué. Lloré un poco... Sabía que no tenía a dónde ir, así que me llevó en su barco para vivir. Primero temporalmente, y luego\nCreo que me habría quedado con él, pero dos meses después luchó contra una patrulla, perdió un mástil, fue atrapado por un fuerte vendaval y encontró la paz en el fondo del anillo exterior. Sobreviví a pesar de todo y me uní a la comunidad de la Isla.";
		link.l1 = "Triste historia, no tengo nada que decir...";
		link.l1.go = "int_quests";
		npchar.quest.answer_1 = "true";
		break;

	case "ansewer_2":
		dialog.text = "Por supuesto que no. Porque es imposible. Vi a un hombre que intentó dejar este lugar en un bote... regresó dos días después. Atado a los restos de un mástil para salvarse de ahogarse. Estaba azul y absolutamente muerto\nAsí que dime, " + pchar.name + ", ¿qué se supone que debo hacer tan pronto como me aleje de aquí? La Habana es demasiado peligrosa para mí, el padrastro intentará matarme de nuevo. No tengo casa, ni dinero. ¿A dónde debería ir? ¿Al burdel?";
		link.l1 = "¿Aún quieres regresar al archipiélago?";
		link.l1.go = "ansewer_2_1";
		break;

	case "ansewer_2_1":
		dialog.text = "¿Y cómo crees? Claro que quiero. Pero es imposible y ya te lo he dicho por qué. Eh, si tan solo alguien pudiera encargarse de mi padrastro... con acero afilado o una bala, entonces habría alguna posibilidad para mí de volver a la vida normal. Pero ¿quién se atrevería a hacer eso si mi padrastro es el mejor amigo del alcalde de La Habana? ¿Y por qué estamos hablando de eso? No hay salida de aquí...";
		link.l1 = "Ya veremos. El tiempo llegará...";
		link.l1.go = "int_quests";
		npchar.quest.answer_2 = "true";
		// сюда направление на квест
		break;

	case "ansewer_3":
		dialog.text = "Vivo de alguna manera. No hay otra opción. Mis amigos son principalmente hombres porque dos de nuestras bellezas casaderas, Gillian y Tanneke no me gustan por mi carácter y me enferma su decencia de fachada. Natalie era una buena chica hasta que empezó a pasar mucho tiempo con esos retrasados, la estupidez es contagiosa.";
		link.l1 = "Veo...";
		link.l1.go = "int_quests";
		npchar.quest.answer_3 = "true";
		break;

	case "ansewer_4":
		dialog.text = "Trabajo como otras chicas. Nuestro objetivo principal es ayudar a los hombres. Hay mucho trabajo para las mujeres en la Isla, así que estoy bastante ocupada. Y a menudo recibo regalos, es algo habitual aquí. Pero no pienses mal de mí, no soy una cualquiera. Fui bien educada en una familia decente. Simplemente no me hago la santa como algunas lo hacen.";
		link.l1 = "No pensé nada malo de ti...";
		link.l1.go = "int_quests";
		npchar.quest.answer_4 = "true";
		break;
		// <-- блок вопросов и ответов

		//----------------------------------------- специальные реакции -----------------------------------------------
		// обнаружение ГГ в сундуках
	case "Man_FackYou":
		dialog.text = LinkRandPhrase("¿Qué estás haciendo ahí, eh? ¡Ladrón!", "¡Mira eso! Tan pronto como me perdí en mis pensamientos, decidiste revisar mi cofre.", "¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!");
		link.l1 = "¡Maldita sea!";
		link.l1.go = "fight";
		break;

	case "Woman_FackYou":
		dialog.text = "¿Qué?! ¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!";
		link.l1 = "¡Chiquilla insensata!";
		link.l1.go = "exit_setOwner";
		LAi_group_Attack(NPChar, Pchar);
		break;

	case "fight":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_SetOwnerTypeNoGroup(npchar);
		LAi_group_Attack(NPChar, Pchar);
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "exit_setOwner":
		LAi_SetOwnerTypeNoGroup(npchar);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	// замечание по обнажённому оружию
	case "LSCNotBlade":
		dialog.text = LinkRandPhrase("Escucha, será mejor que guardes tu arma. Me pone nervioso.", "Sabes, correr con la hoja no se tolera aquí. Guárdala.", "Escucha, no te pongas a hacer de caballero medieval corriendo con una espada. Guárdala, no te queda bien...");
		link.l1 = LinkRandPhrase("Bien.", "Claro.", "Como usted diga...");
		link.l1.go = "exit";
		NextDiag.TempNode = "First Time";
		break;

	case "CitizenNotBlade":
		if (loadedLocation.type == "town")
		{
			dialog.text = NPCharSexPhrase(NPChar, "Escucha, soy ciudadano de la ciudad y te pediría que mantengas tu espada abajo.", "Escucha, soy ciudadano de la ciudad y te pediría que mantuvieras tu espada abajo.");
			link.l1 = LinkRandPhrase("Bien.", "Por supuesto.", "Como dices...");
		}
		else
		{
			dialog.text = NPCharSexPhrase(NPChar, "Ten cuidado, camarada, al correr con un arma. Puedo ponerme nervioso...", "No me gusta cuando los hombres caminan delante de mí con sus armas listas. Me asusta...");
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
